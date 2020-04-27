#include "Hooks.hpp"
#include "H3API.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)
// used for H3Vector<MskData> at 0x6ABAF0
struct MskData
{
	UINT width;
	UINT height;
	BYTE msk1[8];
	BYTE msk2[8];
};

struct H3Msk
{
	UINT8 width;
	UINT8 height;
	BYTE msk1[6];
	BYTE msk2[6];

	void CopyMsk1(PBYTE dst)
	{
		DwordAt(dst)    = DwordAt(msk1);
		WordAt(dst + 4) = WordAt(msk1 + 4);
	}
	void CopyMsk2(PBYTE dst)
	{
		DwordAt(dst)    = DwordAt(msk2);
		WordAt(dst + 4) = WordAt(msk2 + 4);
	}
};
#pragma pack(pop)

constexpr size_t MSK_SIZE = sizeof(H3Msk);

BOOL GetFileContentsFromDataDir(LPCSTR name, h3::H3File& file)
{
	if (!name)
		return FALSE;
	h3::H3String path(h3::h3_DataPath());
	path += name;
	if (!file.Open(path))
		return FALSE;
	if (!file.ReadToBuffer())
		return FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

_LHF_(DefFromDataFolder)
{
	h3::H3File file;
	if (!GetFileContentsFromDataDir(LPCSTR(c->ebx), file))
		return EXEC_DEFAULT;
	PBYTE buffer = file.ReleaseBuffer();
	c->ref_local_n(8) = int(buffer);
	c->edi = int(buffer);
	c->return_address = 0x55CB64;
	return NO_EXEC_DEFAULT;
}

_LHF_(MskFromDataFolder_LoadGame) // 55D160
{
	h3::H3File file;
	if (!GetFileContentsFromDataDir(LPCSTR(c->ecx), file) || file.Size() < MSK_SIZE)
		return EXEC_DEFAULT;

	h3::H3ObjectAttributes* oa = (h3::H3ObjectAttributes*)c->edi;
	H3Msk* contents            = (H3Msk*)file.begin();
	oa->width                  = contents->width;
	oa->height                 = contents->height;
	PBYTE mask                 = PBYTE(c->local_stack(0x10 / 4));

	contents->CopyMsk1(mask);
	c->return_address = 0x503EEF;
	return NO_EXEC_DEFAULT;
}

_LHF_(MskFromDataFolder_LoadTxt)
{
	h3::H3File file;
	if (!GetFileContentsFromDataDir(LPCSTR(c->ecx), file) || file.Size() < MSK_SIZE)
		return EXEC_DEFAULT;

	H3Msk* contents = (H3Msk*)file.begin();
	MskData* msk    = (MskData*)c->ebx;
	msk->width      = contents->width;
	msk->height     = contents->height;
	PBYTE mask1     = PBYTE(c->local_stack(0x2C / 4));
	PBYTE mask2     = PBYTE(c->local_stack(0x34 / 4));

	contents->CopyMsk1(mask1);
	contents->CopyMsk2(mask2);
	c->return_address = 0x514A71;
	return NO_EXEC_DEFAULT;
}

void hooks_init(PatcherInstance* pi)
{
	LoHook* h = pi->CreateLoHook(0x55CA26, DefFromDataFolder);
	// apply last, allowing HDmod hooks to be executed first
	h->ApplyInsert(-1);
	pi->WriteLoHook(0x503E8D, MskFromDataFolder_LoadGame);
	pi->WriteLoHook(0x514A15, MskFromDataFolder_LoadTxt);
}