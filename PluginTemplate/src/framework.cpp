#include "$safeprojectname$.hpp"

using namespace h3;

$safeprojectname$Plugin $safeprojectname$;

$safeprojectname$Plugin& $safeprojectname$Plugin::GetPlugin()
{
	return $safeprojectname$;
}

//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================


//===================================================================================
//
//                             HOOKS
//
//===================================================================================



/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void $safeprojectname$Plugin::Start()
{

}
