/*
 *
 * This plugin was inspired from WoG's implementation
 * of additional LOD tables. The source code is
 * available at:
 *
 * https://github.com/GrayFace/wog/blob/master/T1/lod.cpp
 * https://github.com/GrayFace/wog/blob/master/T1/lod.h
 *
 * Many thanks to WoG team!
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

			// * make sure this plugin only installs once, not to be used outside SoD
			h3::H3Version game;

			if (!game.sod() || LodTableCheck != h3_SoDLodTable)
				return TRUE;

			Patcher *p = _P = GetPatcher();

			_PI = p->CreateInstance(PLUGIN_NAME);
			PatcherInstance *pi = _PI;

			Hooks_init(pi);
			Variables_init(p);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}