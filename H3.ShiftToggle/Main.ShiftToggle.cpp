/*
 *
 * This plugin, with the help of AlexSpl and as239,
 * removes the presence of the active hero when
 * the shift key is pressed on the adventure map,
 * allowing you to click on it without any risks.
 *
 */

#include "Hooks.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	static BOOL pluginOn = 0;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!pluginOn)
		{
			pluginOn = TRUE;
			Patcher* p = _P = GetPatcher();
			if (!p)
				break;
			PatcherInstance *pi = _PI = p->CreateInstance("H3.ToggleShift");
			if (!pi)
				break;
			Hooks_init(pi);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}