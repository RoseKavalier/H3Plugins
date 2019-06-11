/*
 *
 * Collects information about various HoMM3 DLLs.
 *
 */

#include "GetDLLInfo.h"

void Get_DLL_info()
{
	HD_SOD_DLL.GetDLLInfo("HD_SOD.dll");
	_HD3_DLL.GetDLLInfo("_hd3_.dll");
	HD_MCR_DLL.GetDLLInfo("HD_MCR.dll");
}

void Get_Dll_info_init(PatcherInstance * pi)
{
	Get_DLL_info();
}
