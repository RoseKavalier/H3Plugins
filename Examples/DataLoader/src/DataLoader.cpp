#include "DataLoader.hpp"

using namespace h3;

DataLoaderPlugin DataLoader;

DataLoaderPlugin& DataLoaderPlugin::GetPlugin()
{
    return DataLoader;
}

//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================

BOOL OpenFileFromDataDir(LPCSTR name, h3::H3File& file)
{
    if (!name)
        return FALSE;
    h3::H3String path(*P_DataPath() + name);
    if (!file.Open(path.String()))
        return FALSE;
    return TRUE;
}

//===================================================================================
//
//                             HOOKS
//
//===================================================================================

_LHF_(DefFromDataFolder)
{
    h3::H3File file;
    if (!OpenFileFromDataDir(LPCSTR(c->ebx), file) || !file.ReadToBuffer())
        return EXEC_DEFAULT;

    PBYTE buffer = file.ReleaseBuffer();
    c->Local<PBYTE>(8) = buffer;
    c->Edi(buffer);
    c->return_address = 0x55CB64;
    return NO_EXEC_DEFAULT;
}

_LHF_(MskFromDataFolder_NewGame) // 55D160
{
    H3File file;
    H3Msk msk;
    if (!OpenFileFromDataDir(LPCSTR(c->ecx), file) || !file.Read(msk))
        return EXEC_DEFAULT;

    H3Msk::Msk passability, entrances;
    auto& strm = c->Arg<H3ZStream>(1);
    if (!strm.Read(passability) || !strm.Read(entrances))
    {
        c->return_address = 0x5040A6; // failed to read
        return NO_EXEC_DEFAULT;
    }

    auto& oa = *c->Edi<H3ObjectAttributes*>();
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
    H3File file;
    H3Msk msk;
    if (!OpenFileFromDataDir(LPCSTR(c->ecx), file) || !file.Read(msk))
        return EXEC_DEFAULT;

    h3::H3LoadedMsk& mask = *(h3::H3LoadedMsk*)c->ebx;
    mask = msk;
    // skip whole bitfield setting, doing it manually
    c->return_address = 0x514AC1_h3;
    return NO_EXEC_DEFAULT;
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void DataLoaderPlugin::Start()
{
    auto h = Create(0x55CA26, ::DefFromDataFolder);
    // apply last, allowing HDmod hooks to be executed first
    if (h)
        h->ApplyInsert(-1);
    Hook(0x503E8D, ::MskFromDataFolder_NewGame);
    Hook(0x514A15, ::MskFromDataFolder_LoadTxt);
}
