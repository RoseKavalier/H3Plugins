#include "Hooks.hpp"


using namespace h3;

constexpr CHAR MissingPath[] = "Path not provided.";
constexpr CHAR MissingFileName[] = "File name not provided.";
constexpr CHAR ErrorReadingFile[] = "Could not read file at provided path.";
constexpr CHAR MemoryAllocation[] = "Could not allocate memory.";
constexpr CHAR AlreadyExists[] = "An asset already exists with the provided name.";

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class TempLoHook
{
	LoHook* lh;
public:
	TempLoHook(LoHook* h) :
		lh(h)
	{
		if (lh)
			lh->Apply();
	}
	~TempLoHook()
	{
		if (lh)
			lh->Undo();
	}
};

BOOL ValidateParameters(LPCSTR const filepath, LPCSTR const h3name)
{
	if (!filepath)
	{
		AssetLoaderError = MissingPath;
		return FALSE;
	}

	if (!h3name)
	{
		AssetLoaderError = MissingFileName;
		return FALSE;
	}

	FILE* f = F_fopen(filepath, LPCSTR(0x677D6C)); // rb
	if (f == nullptr)
	{
		AssetLoaderError = ErrorReadingFile;
		return FALSE;
	}
	F_fclose(f);

	if (P_BinaryTree->FindItem(h3name))
	{
		AssetLoaderError = AlreadyExists;
		return FALSE;
	}

	return TRUE;
}

PUINT8 GetFileBuffer(LPCSTR const filepath, DWORD& fileSize)
{
	FILE* f = F_fopen(filepath, LPCSTR(0x677D6C)); // rb
	if (f == nullptr)
		return nullptr;
	fileSize = F_GetFileSize(f);
	PUINT8 fileBuffer = PUINT8(F_malloc(fileSize));
	if (fileBuffer == nullptr)
	{
		AssetLoaderError = MemoryAllocation;
		F_fclose(f);
		return nullptr;
	}

	if (!F_fread(fileBuffer, fileSize, 1, f))
	{
		AssetLoaderError = ErrorReadingFile;
		F_fclose(f);
		F_delete(fileBuffer);
		return nullptr;
	}
	F_fclose(f);
	return fileBuffer;
}

H3LoadedPCX* LoadPcxFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
	H3SEHandler seh;
	try
	{
		if (!ValidateParameters(filepath, h3name))
			return nullptr;

		auto& pcxAlloc = H3ObjectAllocator<H3LoadedPCX>();
		H3LoadedPCX *pcx = pcxAlloc.allocate();
		if (pcx == nullptr)
		{
			AssetLoaderError = MemoryAllocation;
			return nullptr;
		}
		pcxAlloc.construct(pcx, h3name);

		int status = THISCALL_8(int, 0x44F710, pcx, filepath,
			IntAt(0x69E5DC), IntAt(0x69E5E4), IntAt(0x69E5D0),
			IntAt(0x69E5E0), IntAt(0x69E5F0), IntAt(0x69E5D8));
		if (status == 1)
		{
			AssetLoaderError = ErrorReadingFile;
			pcxAlloc.deallocate(pcx);
			return nullptr;
		}
		if (status == 2)
		{
			AssetLoaderError = MemoryAllocation;
			pcxAlloc.deallocate(pcx);
			return nullptr;
		}
		pcx->AddToBinaryTree();
		pcx->IncreaseReferences();
		return pcx;
	}
	catch (H3Exception& e)
	{
		AssetLoaderError = e.what();
		return nullptr;
	}
}

H3WavFile* LoadWavFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
	H3SEHandler seh;
	try
	{
		if (!ValidateParameters(filepath, h3name))
			return nullptr;

		DWORD fileSize;
		PUINT8 fileBuffer = GetFileBuffer(filepath, fileSize);
		if (fileBuffer == nullptr)
			return nullptr;

		auto& wavAlloc = H3ObjectAllocator<H3WavFile>();
		H3WavFile* wav = wavAlloc.allocate();
		if (wav == nullptr)
		{
			F_delete(fileBuffer);
			AssetLoaderError = MemoryAllocation;
			return nullptr;
		}
		wavAlloc.construct(wav, h3name, fileBuffer, fileSize);

		wav->AddToBinaryTree();
		wav->IncreaseReferences();
		return wav;
	}
	catch (H3Exception& e)
	{
		AssetLoaderError = e.what();
		return nullptr;
	}
}

_LHF_(DefFromFile)
{
	DWORD fileSize;
	PUINT8 fileBuffer = GetFileBuffer(defPath, fileSize);
	if (fileBuffer == nullptr)
		return EXEC_DEFAULT;

	c->ref_local_n(8) = int(fileBuffer);
	c->edi = int(fileBuffer);
	c->return_address = 0x55CB64;
	return NO_EXEC_DEFAULT;
}

H3LoadedDEF* LoadDefFromFile(LPCSTR const filePath, LPCSTR const h3name)
{
	H3SEHandler seh;
	try
	{
		if (!ValidateParameters(filePath, h3name))
			return nullptr;

		defPath = filePath;

		// * applies DefHook for the duration of this scope
		TempLoHook tlh(DefHook);
		H3LoadedDEF* def = H3LoadedDEF::Load(h3name);

		// * since H3LoadedDEF::Load() is used, reference is already increased
		//def->IncreaseReferences();
		return def;
	}
	catch (H3Exception& e)
	{
		AssetLoaderError = e.what();
		return nullptr;
	}
}

static class H3AssetLoaderInternal : public H3Plugin::AssetLoader::H3AssetLoader
{
	DWORD m_assetsLoaded;
public:
	virtual INT NumberAdded() override;
	virtual LPCSTR GetLastError() override;
	virtual H3LoadedPCX* LoadPcxFromFile(LPCSTR const filepath, LPCSTR const h3name) override;
	virtual H3WavFile* LoadWavFromFile(LPCSTR const filepath, LPCSTR const h3name) override;
	virtual H3LoadedDEF* LoadDefFromFile(LPCSTR const filepath, LPCSTR const h3name) override;
}InternalAssetLoader;

INT H3AssetLoaderInternal::NumberAdded()
{
	return m_assetsLoaded;
}

LPCSTR H3AssetLoaderInternal::GetLastError()
{
	return AssetLoaderError.String();
}

H3LoadedPCX * H3AssetLoaderInternal::LoadPcxFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
	H3LoadedPCX* pcx = ::LoadPcxFromFile(filepath, h3name);
	if (pcx)
		++m_assetsLoaded;
	return pcx;
}

H3WavFile * H3AssetLoaderInternal::LoadWavFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
	H3WavFile* wav = ::LoadWavFromFile(filepath, h3name);
	if (wav)
		++m_assetsLoaded;
	return wav;
}

H3LoadedDEF * H3AssetLoaderInternal::LoadDefFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
	H3LoadedDEF* def = ::LoadDefFromFile(filepath, h3name);
	if (def)
		++m_assetsLoaded;
	return def;
}


H3Plugin::AssetLoader::H3AssetLoader * GetAssetLoader_()
{
	return &InternalAssetLoader;
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
H3String AssetLoaderError;
LPCSTR defPath;
LoHook* DefHook;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void hooks_init(PatcherInstance* pi)
{
	// * only create, do not apply
	DefHook = pi->CreateLoHook(0x55CA26, DefFromFile);
}


