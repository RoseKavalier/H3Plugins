/*
*
* This plugin adds the ability to have custom battlefields
* when using SoD. It is inspired from the MornBattlefields
* mod by Salamandre, using the beautiful backgrounds
* by the original author, Morn.
*
* http://heroescommunity.com/viewthread.php3?TID=39062
* http://heroescommunity.com/viewthread.php3?TID=22924
*
*/

#include "Hooks.h"
#include "Ini.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	static BOOL pluginOn = 0;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!pluginOn)
		{
			pluginOn = TRUE;

			if (Read_Ini())
			{
				Patcher *p = _P = GetPatcher();
				_PI = p->CreateInstance("H3.Battlefields");
				PatcherInstance *pi = _PI;
				Hooks_init(pi);
			}
			else
				H3Error::_ShowError(L"An error occured while trying to read 'Battlefields.ini'.\n\nThe Plugin will not be loaded.");
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}