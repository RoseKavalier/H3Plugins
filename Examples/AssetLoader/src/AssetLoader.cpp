#include "AssetLoader.hpp"

using namespace h3;

AssetLoaderPlugin AssetLoader;

AssetLoaderPlugin& AssetLoaderPlugin::GetPlugin()
{
    return AssetLoader;
}

//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================

class TempPatch
{
    Patch* p;
public:
    TempPatch(Patch* patch) :
        p(patch)
    {
        if (patch)
            patch->Apply();
    }
    ~TempPatch()
    {
        if (p)
            p->Undo();
    }
};

static class H3AssetLoaderInternal : public H3Plugin::AssetLoader::H3AssetLoader
{
    DWORD m_assetsLoaded;
public:
    virtual INT NumberAdded() override;
    virtual LPCSTR GetLastError() override;
    virtual H3LoadedPcx* LoadPcxFromFile(LPCSTR const filepath, LPCSTR const h3name) override;
    virtual H3WavFile* LoadWavFromFile(LPCSTR const filepath, LPCSTR const h3name) override;
    virtual H3LoadedDef* LoadDefFromFile(LPCSTR const filepath, LPCSTR const h3name) override;
}InternalAssetLoader;

INT H3AssetLoaderInternal::NumberAdded()
{
    return m_assetsLoaded;
}

LPCSTR H3AssetLoaderInternal::GetLastError()
{
    return AssetLoader.m_errorMessage.String();
}

H3LoadedPcx* H3AssetLoaderInternal::LoadPcxFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
    H3LoadedPcx* pcx = AssetLoader.LoadPcxFromFile(filepath, h3name);
    if (pcx)
        ++m_assetsLoaded;
    return pcx;
}

H3WavFile* H3AssetLoaderInternal::LoadWavFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
    H3WavFile* wav = AssetLoader.LoadWavFromFile(filepath, h3name);
    if (wav)
        ++m_assetsLoaded;
    return wav;
}

H3LoadedDef* H3AssetLoaderInternal::LoadDefFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
    H3LoadedDef* def = AssetLoader.LoadDefFromFile(filepath, h3name);
    if (def)
        ++m_assetsLoaded;
    return def;
}


H3Plugin::AssetLoader::H3AssetLoader* GetAssetLoader_()
{
#pragma _H3API_EXPORT_
    return &InternalAssetLoader;
}

//===================================================================================
//
//                             HOOKS
//
//===================================================================================

bool AssetLoaderPlugin::ValidateParameters(LPCSTR const filepath, LPCSTR const h3name)
{
    if (!filepath)
    {
        m_errorMessage.AssignA(MissingPath);
        return FALSE;
    }

    if (!h3name)
    {
        m_errorMessage.AssignA(MissingFileName);
        return FALSE;
    }

    if (!H3Path::IsFile(filepath))
    {
        m_errorMessage.AssignA(ErrorReadingFile);
        return FALSE;
    }

    if (P_ResourceManager()->FindItem(h3name))
    {
        m_errorMessage.AssignA(AlreadyExists);
        return FALSE;
    }

    return TRUE;
}


PUINT8 AssetLoaderPlugin::GetFileBuffer(LPCSTR const filepath, DWORD& fileSize)
{
    H3File f;
    if (!f.Open(filepath) || !f.ReadToBuffer())
    {
        m_errorMessage.AssignA(ErrorReadingFile);
        return nullptr;
    }

    fileSize = f.Size();
    return f.ReleaseBuffer();
}

H3LoadedPcx* AssetLoaderPlugin::LoadPcxFromFile(LPCSTR const filepath, LPCSTR const h3name)
{
    H3SEHandler seh;
    try
    {
        if (!ValidateParameters(filepath, h3name))
            return nullptr;

        auto& pcxAlloc = H3ObjectAllocator<H3LoadedPcx>();
        H3LoadedPcx* pcx = pcxAlloc.allocate();
        if (pcx == nullptr)
        {
            m_errorMessage.AssignA(MemoryAllocation);
            return nullptr;
        }
        pcxAlloc.construct(pcx, h3name);

        int status = THISCALL_8(int, 0x44F710, pcx, filepath,
            IntAt(0x69E5DC), IntAt(0x69E5E4), IntAt(0x69E5D0),
            IntAt(0x69E5E0), IntAt(0x69E5F0), IntAt(0x69E5D8));
        if (status == 1)
        {
            m_errorMessage.AssignA(ErrorReadingFile);
            pcxAlloc.deallocate(pcx);
            return nullptr;
        }
        if (status == 2)
        {
            m_errorMessage.AssignA(MemoryAllocation);
            pcxAlloc.deallocate(pcx);
            return nullptr;
        }
        pcx->AddToResourceManager();
        pcx->IncreaseReferences();
        return pcx;
    }
    catch (const H3Exception& e)
    {
        m_errorMessage = e.what();
        return nullptr;
    }
}

H3WavFile* AssetLoaderPlugin::LoadWavFromFile(LPCSTR const filepath, LPCSTR const h3name)
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
            m_errorMessage.AssignA(MemoryAllocation);
            return nullptr;
        }
        wavAlloc.construct(wav, h3name, fileBuffer, fileSize);

        wav->AddToResourceManager();
        wav->IncreaseReferences();
        return wav;
    }
    catch (const H3Exception& e)
    {
        m_errorMessage = e.what();
        return nullptr;
    }
}

H3LoadedDef* AssetLoaderPlugin::LoadDefFromFile(LPCSTR const filePath, LPCSTR const h3name)
{
    H3SEHandler seh;
    try
    {
        if (!ValidateParameters(filePath, h3name))
            return nullptr;

        m_defPath = filePath;

        // * applies DefHook for the duration of this scope
        TempPatch tlh(m_defHook);
        H3LoadedDef* def = H3LoadedDef::Load(h3name);

        // * since H3LoadedDef::Load() is used, reference is already increased
        return def;
    }
    catch (const H3Exception& e)
    {
        m_errorMessage = e.what();
        return nullptr;
    }
}

int AssetLoaderPlugin::DefFromFile(HookContext& c)
{
    DWORD file_size;
    PUINT8 fileBuffer = GetFileBuffer(m_defPath, file_size);
    if (fileBuffer == nullptr)
        return EXEC_DEFAULT;

    c.Local<PUINT8>(8) = fileBuffer;
    c.Edi(fileBuffer);
    c.return_address = 0x55CB64;
    return NO_EXEC_DEFAULT;
}

_LHF_(DefFromFile)
{
    return AssetLoader.DefFromFile(*c);
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void AssetLoaderPlugin::Start()
{
    m_defHook = Create(0x55CA26, ::DefFromFile);
}