/*
 *
 * Collects information about various HoMM3 DLLs.
 *
 */

#include "GetDLLInfo.hpp"
#include "Global.hpp"

using namespace h3;

using namespace sodsp::dll;

void GetDllInfo()
{
	HD_SOD.GetDLLInfo("HD_SOD.dll");
	_HD3_.GetDLLInfo("_hd3_.dll");
	//HD_MCR.GetDLLInfo("HD_MCR.dll");
	HD_TC2.GetDLLInfo("HD_TC2.dll");
}

void GetDllInfoInit(PatcherInstance * pi)
{
	namespace gen = sodsp::gen;

	GetDllInfo();
	gen::GHDmodVersion = gen::_SODSP->VarGetValue("HD.Version.Dword", 0);
}
