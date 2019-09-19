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
			Patcher *p = _P = GetPatcher();

			// * make sure this plugin only installs once
			if (!p->GetInstance("H3.ImageLoader"))
			{
				_PI = p->CreateInstance("H3.ImageLoader");
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