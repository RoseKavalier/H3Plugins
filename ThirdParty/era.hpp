#pragma once
#ifndef _WINDOWS_
// * Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// * use std::min and std::max instead
#define NOMINMAX
#include <Windows.h>
#endif
#include <cstdio>
#include <vector>
#include <string>

namespace era
{
#pragma pack(push, 1)

    /* Hooks, requires at least 5 bytes */
    constexpr int HOOKTYPE_JUMP   = 0;
    constexpr int HOOKTYPE_CALL   = 1;
    constexpr int HOOKTYPE_BRIDGE = 2;

    /*
    Automatically creates safe bridge to high-level function:
      BOOL __stdcall Handler (THookContext* Context);
    Returns "Execute default code" flag. If default code should be executed, it can contain any
    commands except jumps.
    */

    constexpr int OPCODE_JUMP = 0xE9;
    constexpr int OPCODE_CALL = 0xE8;
    constexpr int OPCODE_RET  = 0xC3;

    constexpr int EXEC_DEF_CODE = true;

    /* Erm triggers */
    constexpr int TRIGGER_FU1       = 0;
    constexpr int TRIGGER_FU30000   = 29999;
    constexpr int TRIGGER_TM1       = 30000;
    constexpr int TRIGGER_TM100     = 30099;
    constexpr int TRIGGER_HE0       = 30100;
    constexpr int TRIGGER_HE198     = 30298;
    constexpr int TRIGGER_BA0       = 30300;
    constexpr int TRIGGER_BA1       = 30301;
    constexpr int TRIGGER_BR        = 30302;
    constexpr int TRIGGER_BG0       = 30303;
    constexpr int TRIGGER_BG1       = 30304;
    constexpr int TRIGGER_MW0       = 30305;
    constexpr int TRIGGER_MW1       = 30306;
    constexpr int TRIGGER_MR0       = 30307;
    constexpr int TRIGGER_MR1       = 30308;
    constexpr int TRIGGER_MR2       = 30309;
    constexpr int TRIGGER_CM0       = 30310;
    constexpr int TRIGGER_CM1       = 30311;
    constexpr int TRIGGER_CM2       = 30312;
    constexpr int TRIGGER_CM3       = 30313;
    constexpr int TRIGGER_CM4       = 30314;
    constexpr int TRIGGER_AE0       = 30315;
    constexpr int TRIGGER_AE1       = 30316;
    constexpr int TRIGGER_MM0       = 30317;
    constexpr int TRIGGER_MM1       = 30318;
    constexpr int TRIGGER_CM5       = 30319;
    constexpr int TRIGGER_MP        = 30320;
    constexpr int TRIGGER_SN        = 30321;
    constexpr int TRIGGER_MG0       = 30322;
    constexpr int TRIGGER_MG1       = 30323;
    constexpr int TRIGGER_TH0       = 30324;
    constexpr int TRIGGER_TH1       = 30325;
    constexpr int TRIGGER_IP0       = 30330;
    constexpr int TRIGGER_IP1       = 30331;
    constexpr int TRIGGER_IP2       = 30332;
    constexpr int TRIGGER_IP3       = 30333;
    constexpr int TRIGGER_CO0       = 30340;
    constexpr int TRIGGER_CO1       = 30341;
    constexpr int TRIGGER_CO2       = 30342;
    constexpr int TRIGGER_CO3       = 30343;
    constexpr int TRIGGER_BA50      = 30350;
    constexpr int TRIGGER_BA51      = 30351;
    constexpr int TRIGGER_BA52      = 30352;
    constexpr int TRIGGER_BA53      = 30353;
    constexpr int TRIGGER_GM0       = 30360;
    constexpr int TRIGGER_GM1       = 30361;
    constexpr int TRIGGER_PI        = 30370;
    constexpr int TRIGGER_DL        = 30371;
    constexpr int TRIGGER_HM        = 30400;
    constexpr int TRIGGER_HM0       = 30401;
    constexpr int TRIGGER_HM198     = 30599;
    constexpr int TRIGGER_HL        = 30600;
    constexpr int TRIGGER_HL0       = 30601;
    constexpr int TRIGGER_HL198     = 30799;
    constexpr int TRIGGER_BF        = 30800;
    constexpr int TRIGGER_MF1       = 30801;
    constexpr int TRIGGER_TL0       = 30900;
    constexpr int TRIGGER_TL1       = 30901;
    constexpr int TRIGGER_TL2       = 30902;
    constexpr int TRIGGER_TL3       = 30903;
    constexpr int TRIGGER_TL4       = 30904;
    constexpr int TRIGGER_OB_POS    = 0x10000000;
    constexpr int TRIGGER_LE_POS    = 0x20000000;
    constexpr int TRIGGER_OB_LEAVE  = 0x08000000;

    /* Era Triggers */
    constexpr int TRIGGER_BEFORE_SAVE_GAME          = 77000; // DEPRECATED
    constexpr int TRIGGER_SAVEGAME_WRITE            = 77001;
    constexpr int TRIGGER_SAVEGAME_READ             = 77002;
    constexpr int TRIGGER_KEYPRESS                  = 77003;
    constexpr int TRIGGER_OPEN_HEROSCREEN           = 77004;
    constexpr int TRIGGER_CLOSE_HEROSCREEN          = 77005;
    constexpr int TRIGGER_STACK_OBTAINS_TURN        = 77006;
    constexpr int TRIGGER_REGENERATE_PHASE          = 77007;
    constexpr int TRIGGER_AFTER_SAVE_GAME           = 77008;
    constexpr int TRIGGER_SKEY_SAVEDIALOG           = 77009; // DEPRECATED
    constexpr int TRIGGER_HEROESMEET                = 77010; // DEPRECATED
    constexpr int TRIGGER_BEFOREHEROINTERACT        = 77010;
    constexpr int TRIGGER_AFTERHEROINTERACT         = 77011;
    constexpr int TRIGGER_ONSTACKTOSTACKDAMAGE      = 77012;
    constexpr int TRIGGER_ONAICALCSTACKATTACKEFFECT = 77013;
    constexpr int TRIGGER_ONCHAT                    = 77014;

    constexpr int CONV_LAST = -101;

    // Left-to-right
    constexpr int CONV_PASCAL = CONV_LAST;

    // Left-to-right, first three arguments in EAX, EDX, ECX
    constexpr int CONV_REGISTER = -102;

    // Right-to-left, caller clean-up
    constexpr int CONV_CDECL = -103;

    // Right-to-left
    constexpr int CONV_STDCALL = -104;

    // Right-to-left, first argument in ECX
    constexpr int CONV_THISCALL = -105;

    // Right-to-left, first two arguments in ECX, EDX
    constexpr int CONV_FASTCALL = -106;

    constexpr int CONV_FIRST = CONV_FASTCALL;

    struct THookContext
    {
        int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
        int RetAddr;
    };

    typedef BOOL (__stdcall *THookHandler) (THookContext *Context);

    struct TEvent
    {
        char* Name;
        void* Data;
        int   DataSize;
    };

    typedef int TEventParams[16];
    typedef void (__stdcall *TEventHandler) (TEvent* Event);

    typedef char  TErmZVar[512];


    /* WoG vars */
    int*      v = (int*)      0x887664; // 1..10000
    TErmZVar* z = (TErmZVar*) 0x9271E8; // 1..1000
    int*      y = (int*)      0xA48D7C; // 1..100
    int*      x = (int*)      0x91DA34; // 1..16
    bool*     f = (bool*)     0x91F2DF; // 1..1000
    float*    e = (float*)    0xA48F14; // 1..100

    struct TGameState
    {
        int RootDlgId;
        int CurrentDlgId;
    };

    typedef void  (__stdcall *TWriteAtCode) (int Count, void* Src, void* Dst);
    typedef void* (__stdcall *THook) (void* HandlerAddr, int HookType, int PatchSize, void* CodeAddr);
    typedef void* (__stdcall *TApiHook) (void* HandlerAddr, int HookType, void* CodeAddr);
    typedef void  (__stdcall *TFatalError) (const char* Err);
    typedef int   (__stdcall *TRecallAPI) (THookContext* Context, int NumArgs);
    typedef void  (__stdcall *TRegisterHandler) (TEventHandler Handler, const char* EventName);
    typedef void  (__stdcall *TFireEvent) (const char* EventName, void* EventData, int DataSize);
    typedef void* (__stdcall *TLoadTxt) (const char* Name);
    typedef void  (__stdcall *TExecErmCmd) (const char* CmdStr);
    typedef void  (__stdcall *TReloadErm) ();
    typedef void  (__stdcall *TExtractErm) ();
    typedef void  (__stdcall *TFireErmEvent) (int EventID);
    typedef void  (__stdcall *TClearAllIniCache) ();
    typedef void  (__stdcall *TClearIniCache) (const char* FileName);
    typedef bool  (__stdcall *TReadStrFromIni) (const char* Key, const char* SectionName, const char* FilePath, char* Res);
    typedef bool  (__stdcall *TWriteStrToIni) (const char* Key, const char* Value, const char* SectionName, const char* FilePath);
    typedef bool  (__stdcall *TSaveIni) (const char* FilePath);
    typedef void  (__stdcall *TNameColor) (int Color32, const char* Name);
    typedef void  (__stdcall *TWriteSavegameSection) (int DataSize, void* Data, const char* SectionName);
    typedef int   (__stdcall *TReadSavegameSection) (int DataSize, void* Data, const char* SectionName);
    typedef void  (__stdcall *TGetGameState) (TGameState* GameState);
    typedef int   (__stdcall *TGetButtonID) (const char* ButtonName);
    typedef bool  (__stdcall *TPatchExists) (const char* PatchName);
    typedef bool  (__stdcall *TPluginExists) (const char* PluginName);
    typedef void  (__stdcall *TRedirectFile) ();
    typedef void  (__stdcall *TGlobalRedirectFile) ();
    typedef void  (__stdcall *TRedirectMemoryBlock) (void* OldAddr, int BlockSize, void* NewAddr);
    typedef void* (__stdcall *TGetRealAddr) (void* Addr);
    typedef void  (__stdcall *TSaveEventParams) ();
    typedef void  (__stdcall *TRestoreEventParams) ();
    typedef void  (__stdcall *TReportPluginVersion) (const char* VersionLine);
    typedef const char* (__stdcall *TGetEraVersion) ();
    typedef char* (__stdcall *TTr) (const char* key, const char** params, int highParams);
    typedef void  (__stdcall *TMemFree) (const void* buf);
    typedef void  (__stdcall *TNotifyError) (const char* error);

    /**
     * Replaces original function with the new one with the same prototype and 1-2 extra arguments.
     * Calling convention is changed to STDCALL. The new argument is callable pointer, which can be used to
     * execute original function. The pointer is passed as THE FIRST argument. If custom parameter address
     * is given, the value of custom parameter will be passed to handler as THE SECOND argument. If AppliedPatch
     * pointer is given, it will be assigned an opaque pointer to applied patch data structure. This
     * pointer can be used to rollback the patch (remove splicing).
     * Returns address of the bridge to original function.
     *
     * Example:
     *   int custom_param = 700;
     *   Splice((void*) 0x401000, (void*) MainProc, CONV_STDCALL, 2, &custom_param);
     *   int __stdcall (void* orig_func, int custom_param, int arg1, int arg2) MainProc {...}
     */
    typedef void* (__stdcall *TSplice) (void* OrigFunc, void* HandlerFunc, int CallingConv, int NumArgs, int* CustomParam, void** AppliedPatch);

    /**
     * Calls handler function, when execution reaches specified address. Handler receives THookContext pointer.
     * If it returns true, overwritten commands are executed. Otherwise overwritten commands are skipped.
     * Change Context.RetAddr field to return to specific address after handler finishes execution with FALSE result.
     */
    typedef void* (__stdcall *THookCode) (void* Addr, THookHandler HandlerFunc, void** AppliedPatch);

    const int RESIZE_ALG_NO_RESIZE = 0; // Do not apply any constaints and do not change image dimensions
    const int RESIZE_ALG_STRETCH   = 1; // Assign image width and height to box width and height, scale unproportionally
    const int RESIZE_ALG_CONTAIN   = 2; // Resize image so, that at least one of its dimension become same as box dimension, and the other one less or equal to box dimension
    const int RESIZE_ALG_DOWNSCALE = 3; // Only downscale images proportionally, do not upscale small images
    const int RESIZE_ALG_UPSCALE   = 4; // Only upscale small images proportionally, leave big images as is
    const int RESIZE_ALG_COVER     = 5; // NOT IMPLEMENTED
    const int RESIZE_ALG_FILL      = 6; // Use image as a tile to fill the whole box

    /**
     * Loads Pcx16 resource with rescaling support. Values <= 0 are considered 'auto'. If it's possible, images are scaled proportionally.
     * Resource name (name in binary resource tree) can be either fixed or automatic. Pass empty PcxName for automatic name.
     * If PcxName exceeds 12 characters, it's replaced with valid unique name. Check name field of result.
     * If resource is already registered and has proper format, it's returned with RefCount increased.
     * Result image dimensions may differ from requested if fixed PcxName is specified. Use automatic naming
     * to load image of desired size for sure.
     * Default image is returned in case of missing file and user is notified.
     */
    typedef void* (__stdcall *TLoadImageAsPcx16) (const char* FilePath, const char* PcxName, int Width, int Height, int MaxWidth, int MaxHeight, int ResizeAlg);


    TEventParams* EventParams = NULL;


    TApiHook              ApiHook               = NULL;
    TClearAllIniCache     ClearAllIniCache      = NULL;
    TClearIniCache        ClearIniCache         = NULL;
    TExecErmCmd           ExecErmCmd            = NULL;
    TExtractErm           ExtractErm            = NULL;
    TFatalError           FatalError            = NULL;
    TFireErmEvent         FireErmEvent          = NULL;
    TFireEvent            FireEvent             = NULL;
    TGetButtonID          GetButtonID           = NULL;
    TGetEraVersion        GetEraVersion         = NULL;
    TGetGameState         GetGameState          = NULL;
    TGetRealAddr          GetRealAddr           = NULL;
    TGlobalRedirectFile   GlobalRedirectFile    = NULL;
    THook                 Hook                  = NULL;
    THookCode             HookCode              = NULL;
    TLoadImageAsPcx16     LoadImageAsPcx16      = NULL;
    TLoadTxt              LoadTxt               = NULL;
    TMemFree              MemFree               = NULL;
    TNameColor            NameColor             = NULL;
    TNotifyError          NotifyError           = NULL;
    TPatchExists          PatchExists           = NULL;
    TPluginExists         PluginExists          = NULL;
    TReadSavegameSection  ReadSavegameSection   = NULL;
    TReadStrFromIni       ReadStrFromIni        = NULL;
    TRecallAPI            RecallAPI             = NULL;
    TRedirectFile         RedirectFile          = NULL;
    TRedirectMemoryBlock  RedirectMemoryBlock   = NULL;
    TRegisterHandler      RegisterHandler       = NULL;
    TReloadErm            ReloadErm             = NULL;
    TReportPluginVersion  ReportPluginVersion   = NULL;
    TRestoreEventParams   RestoreEventParams    = NULL;
    TSaveEventParams      SaveEventParams       = NULL;
    TSaveIni              SaveIni               = NULL;
    TSplice               Splice                = NULL;
    TTr                   _tr                   = NULL;
    TWriteAtCode          WriteAtCode           = NULL;
    TWriteSavegameSection WriteSavegameSection  = NULL;
    TWriteStrToIni        WriteStrToIni         = NULL;

    /**
    * Returns translation for given complex key ('xxx.yyy.zzz') with substituted parameters.
    * Pass vector of (parameter name, parameter value) pairs to substiture named parameters.
    * Example: Mod\Lang\*.json file: { "eqs": { "greeting": "Hello, @name@" } }
    * Example: ShowMessage(tr("eqs.greeting", { "name", "igrik" }).c_str());
    *
    * @param  key    Key to get translation for.
    * @param  params Vector of (parameter name, parameter value pairs).
    * @return        Translation string.
    */
    inline std::string GetTranslation(const char *key, const std::vector<std::string>& params)
    {
        constexpr size_t MAX_PARAMS = 64;
        const char* _params[MAX_PARAMS];
        size_t numParams = params.size() <= MAX_PARAMS ? params.size() : MAX_PARAMS;

        for (size_t i = 0; i < numParams; i++)
            _params[i] = params[i].c_str();

        char* buf = _tr(key, _params, int(numParams) - 1);
        std::string str(buf);
        MemFree(buf);
        return str;
    }

    /**
    * Returns translation for given complex key ('xxx.yyy.zzz') as is.
    *
    * @param  key    Key to get translation for.
    * @return        Translation string.
    */
    inline std::string GetTranslation(const char* key)
    {
        char* buf = _tr(key, nullptr, -1);
        std::string str(buf);
        MemFree(buf);
        return str;
    }

    inline std::string IntToStr(int value)
    {
        char buf[64];
        sprintf_s(buf, "%d", value);
        return buf;
    }

    /**
    * Assigns new string value to buffer.
    * @param  Buf      Buffer to change contents of.
    * @param  NewValue New string value.
    * @param  BufSize  Maximal buffer size.
    * @return void
    */
    inline void SetPcharValue (char *Buf, const char *NewValue, int BufSize = -1)
    {
        if (BufSize < 0)
            lstrcpyA(Buf, NewValue);
        else if (BufSize > 0)
        {
                int NumBytesToCopy = lstrlenA(NewValue);
                NumBytesToCopy >= BufSize && (NumBytesToCopy = BufSize - 1);
                memcpy(Buf, NewValue, NumBytesToCopy);
                Buf[NumBytesToCopy] = 0;
        }
    }

    HINSTANCE hEra;
    HINSTANCE hAngel;

    inline void ConnectEra (bool translation_only = false)
    {
        if (!translation_only)
        {
            hAngel                = LoadLibraryA("angel.dll");
            EventParams           = (TEventParams*)         GetProcAddress(hAngel, "EventParams");
            RestoreEventParams    = (TRestoreEventParams)   GetProcAddress(hAngel, "RestoreEventParams");
            SaveEventParams       = (TSaveEventParams)      GetProcAddress(hAngel, "SaveEventParams");
        }
        /***/
        hEra                      = LoadLibraryA("era.dll");
        _tr                       = (TTr)                   GetProcAddress(hEra, "tr");
        MemFree                   = (TMemFree)              GetProcAddress(hEra, "MemFree");
        if (!translation_only)
        {
            ApiHook               = (TApiHook)              GetProcAddress(hEra, "ApiHook");
            ClearAllIniCache      = (TClearAllIniCache)     GetProcAddress(hEra, "ClearAllIniCache");
            ClearIniCache         = (TClearIniCache)        GetProcAddress(hEra, "ClearIniCache");
            ExecErmCmd            = (TExecErmCmd)           GetProcAddress(hEra, "ExecErmCmd");
            ExtractErm            = (TExtractErm)           GetProcAddress(hEra, "ExtractErm");
            FatalError            = (TFatalError)           GetProcAddress(hEra, "FatalError");
            FireErmEvent          = (TFireErmEvent)         GetProcAddress(hEra, "FireErmEvent");
            FireEvent             = (TFireEvent)            GetProcAddress(hEra, "FireEvent");
            GetButtonID           = (TGetButtonID)          GetProcAddress(hEra, "GetButtonID");
            GetEraVersion         = (TGetEraVersion)        GetProcAddress(hEra, "GetVersion");
            GetGameState          = (TGetGameState)         GetProcAddress(hEra, "GetGameState");
            GetRealAddr           = (TGetRealAddr)          GetProcAddress(hEra, "GetRealAddr");
            GlobalRedirectFile    = (TGlobalRedirectFile)   GetProcAddress(hEra, "GlobalRedirectFile");
            Hook                  = (THook)                 GetProcAddress(hEra, "Hook");
            HookCode              = (THookCode)             GetProcAddress(hEra, "HookCode");
            LoadImageAsPcx16      = (TLoadImageAsPcx16)     GetProcAddress(hEra, "LoadImageAsPcx16");
            LoadTxt               = (TLoadTxt)              GetProcAddress(hEra, "LoadTxt");
            NameColor             = (TNameColor)            GetProcAddress(hEra, "NameColor");
            NotifyError           = (TNotifyError)          GetProcAddress(hEra, "NotifyError");
            PatchExists           = (TPatchExists)          GetProcAddress(hEra, "PatchExists");
            PluginExists          = (TPluginExists)         GetProcAddress(hEra, "PluginExists");
            ReadSavegameSection   = (TReadSavegameSection)  GetProcAddress(hEra, "ReadSavegameSection");
            ReadStrFromIni        = (TReadStrFromIni)       GetProcAddress(hEra, "ReadStrFromIni");
            RecallAPI             = (TRecallAPI)            GetProcAddress(hEra, "RecallAPI");
            RedirectFile          = (TRedirectFile)         GetProcAddress(hEra, "RedirectFile");
            RedirectMemoryBlock   = (TRedirectMemoryBlock)  GetProcAddress(hEra, "RedirectMemoryBlock");
            RegisterHandler       = (TRegisterHandler)      GetProcAddress(hEra, "RegisterHandler");
            ReloadErm             = (TReloadErm)            GetProcAddress(hEra, "ReloadErm");
            ReportPluginVersion   = (TReportPluginVersion)  GetProcAddress(hEra, "ReportPluginVersion");
            SaveIni               = (TSaveIni)              GetProcAddress(hEra, "SaveIni");
            Splice                = (TSplice)               GetProcAddress(hEra, "Splice");
            WriteAtCode           = (TWriteAtCode)          GetProcAddress(hEra, "WriteAtCode");
            WriteSavegameSection  = (TWriteSavegameSection) GetProcAddress(hEra, "WriteSavegameSection");
            WriteStrToIni         = (TWriteStrToIni)        GetProcAddress(hEra, "WriteStrToIni");
        }
    }
#pragma pack(pop)
}
