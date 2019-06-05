/*
 *
 * This plugin was inspired from ERA's implementation
 * of color tags and is heavily drawn upon its source code
 * which is available at:
 *
 * https://github.com/ethernidee/era/blob/master/Rainbow.pas
 *
 * Many thanks to Berserker!
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
			if (h3_ExeVersion != h3_VersionSOD)
				return TRUE;

			Patcher *p = _P = GetPatcher();

			// * make sure this plugin only installs once
			if (!p->GetInstance("H3.TextColor"))
			{
				_PI = p->CreateInstance("H3.TextColor");
				PatcherInstance *pi = _PI;

				Hooks_init(pi);
				Variables_init(p);
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