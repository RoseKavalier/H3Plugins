/*
 *
 * This plugin cycles through combat creature's
 * standing animation frames instead of being
 * idle while waiting for the 9000 ms interval
 * semi-random mouse-over animation.
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

			// * not to be used outside SoD
			h3::H3Version game;
			if (!game.sod())
				return TRUE;

			Patcher *p = _P = GetPatcher();

			// * make sure this plugin only installs once
			if (!p->GetInstance(PLUGIN_NAME))
			{
				_PI = p->CreateInstance(PLUGIN_NAME);
				PatcherInstance *pi = _PI;

				Hooks_init(pi);
			}
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}