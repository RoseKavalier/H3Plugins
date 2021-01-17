#include "DisableHWrules.hpp"

using namespace h3;

DisableHWrulesPlugin DisableHWrules;

DisableHWrulesPlugin& DisableHWrulesPlugin::GetPlugin()
{
    return DisableHWrules;
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

_LHF_(DisableHeroesWorldRulesPlugin)
{
    auto wzx = DisableHWrules.GetInstance("wzx_HW");
    if (wzx)
        wzx->UndoAll();
    return EXEC_DEFAULT;
}


/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void DisableHWrulesPlugin::Start()
{
    Hook(0x4F823F, DisableHeroesWorldRulesPlugin);
}