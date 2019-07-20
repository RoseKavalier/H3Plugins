/*
 *       ▄███████▄  ▄██████▄  ████████▄     ▄███████▄   ▄███████▄
 *      ███    ███ ███    ███ ███   ▀███   ███    ███   ███    ███
 *      ███    █▀  ███    ███ ███    ███   ███    █▀    ███    ███
 *     ▄███        ███    ███ ███    ███  ▄███          ███    ███
 *     ▀█████████▄ ███    ███ ███    ███  ▀█████████▄ ▀█████████▀
 *             ███ ███    ███ ███    ███          ███   ███
 *       ▄█    ███ ███    ███ ███   ▄███    ▄█    ███   ███
 *     ▄████████▀   ▀██████▀  ████████▀   ▄████████▀   ▄████▀
 */

#include "Main.h"
#include "Hooks.h"
#include "Ini/IniParser.h"

 // * Global Patcher
Patcher *_SODSP;
// * Global Patcher Instance
PatcherInstance *_SODSPI;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	static BOOL pluginOn = FALSE;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!pluginOn)
		{
			pluginOn = TRUE;
			Patcher *p = _SODSP = GetPatcher();
			if (p->GetInstance("SoD_SP"))
				break;
			PatcherInstance *pi = _SODSPI = p->CreateInstance("SoD_SP");
			if (!pi)
			{
				H3Error::_ShowError(L"Plugin instance could not be created.", SODSP::TEXT::TErrorTitle);
				break;
			}

			if (!IniParser_init(pi)) // reads options and sets up hook to read text files
				break;
			hooks_init(pi);		// installs all plugin hooks
			SoD_SP_log(pi);		// installs SoD_SP log hooks

			p->VarInit("SoD_SP.Version", SODSP::VERSIONS::VLONG);
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}