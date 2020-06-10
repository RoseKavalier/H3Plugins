#include "Hooks.hpp"
#include "H3API.hpp"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

BOOL OpenFileFromDataDir(LPCSTR name, h3::H3File& file)
{
	if (!name)
		return FALSE;
	h3::H3String path(*h3::P_DataPath() + name);
	if (!file.Open(path.String()))
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
	if (!OpenFileFromDataDir(LPCSTR(c->ebx), file) || !file.ReadToBuffer())
		return EXEC_DEFAULT;

	PBYTE buffer = file.ReleaseBuffer();
	c->Local<PBYTE>(8) = buffer;
	c->edi = int(buffer);
	c->return_address = 0x55CB64;
	return NO_EXEC_DEFAULT;
}

_LHF_(MskFromDataFolder_NewGame) // 55D160
{
	h3::H3File file;
	h3::H3Msk msk;
	if (!OpenFileFromDataDir(LPCSTR(c->ecx), file) || !file.Read(msk))
		return EXEC_DEFAULT;

	h3::H3Msk::Msk passability, entrances;
	h3::H3ZStream& strm = c->Arg<h3::H3ZStream>(1);
	if (!strm.Read(passability) || !strm.Read(entrances))
	{
		c->return_address = 0x5040A6; // failed to read
		return NO_EXEC_DEFAULT;
	}

	h3::H3ObjectAttributes& oa = *(h3::H3ObjectAttributes*)c->edi;
	oa.width        = msk.width;
	oa.height       = msk.height;
	msk.colorMask  >> oa.colors;
	passability    >> oa.passability;
	msk.shadowMask >> oa.shadows;
	entrances      >> oa.entrances;

	c->return_address = 0x504131;
	return NO_EXEC_DEFAULT;
}

_LHF_(MskFromDataFolder_LoadTxt)
{
	h3::H3File file;
	h3::H3Msk msk;
	if (!OpenFileFromDataDir(LPCSTR(c->ecx), file) || !file.Read(msk))
		return EXEC_DEFAULT;

	h3::H3LoadedMsk& mask = *(h3::H3LoadedMsk*)c->ebx;
	mask = msk;
	// skip whole bitfield setting, doing it manually
	c->return_address = 0x514AC1;
	return NO_EXEC_DEFAULT;
}

void hooks_init(PatcherInstance* pi)
{
	LoHook* h = pi->CreateLoHook(0x55CA26, DefFromDataFolder);
	// apply last, allowing HDmod hooks to be executed first
	if (h)
		h->ApplyInsert(-1);
	pi->WriteLoHook(0x503E8D, MskFromDataFolder_NewGame);
	pi->WriteLoHook(0x514A15, MskFromDataFolder_LoadTxt);
}