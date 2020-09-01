/*
 * Created with the H3Plugin Template
 * A HoMM III plugin using the H3API library.
 */

#include "Hooks.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	static BOOL pluginOn = FALSE;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!pluginOn)
		{
			pluginOn = TRUE;

			Patcher *p = _P = GetPatcher();
			if (!p)
				break;

			// * make sure this plugin only installs once
			if (!p->GetInstance(PLUGIN_NAME))
			{
				_PI = p->CreateInstance(PLUGIN_NAME);
				PatcherInstance *pi = _PI;
				if (!pi)
					break;
				hooks_init(pi);
			}
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
	default:
		break;
	}
	return TRUE;
}