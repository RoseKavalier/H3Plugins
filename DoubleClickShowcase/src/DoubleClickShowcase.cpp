#include "DoubleClickShowcase.hpp"

using namespace h3;

DoubleClickShowcasePlugin DoubleClickShowcase;

DoubleClickShowcasePlugin& DoubleClickShowcasePlugin::GetPlugin()
{
    return DoubleClickShowcase;
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

int __stdcall DoubleClickShowcasePlugin::_HH_CheckDoubleClick(HiHook* h, h3::H3InputManager* This, int* a2)
{
    auto& msg = This->GetCurrentMessage();
    if (msg.message != MT_DOUBLE_CLICK)
        m_doubleClicked = false;
    else
    {
        msg.message = H3InputManager::eMessageType::MT_LBUTTON_DBLCLK; // reset to h3 default value
        m_doubleClicked = true;
        F_MessageBox("Double-click detected!");
    }

    return THISCALL_2(int, h->GetDefaultFunc(), This, a2);
}

int __stdcall _HH_CheckDoubleClick(HiHook* h, H3InputManager* This, int* a2)
{
    return DoubleClickShowcase._HH_CheckDoubleClick(h, This, a2);
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void DoubleClickShowcasePlugin::Start()
{
    DwordPatch(0x4EC3F2 + 2, MT_DOUBLE_CLICK);
    Hook(0x4EC660, Splice, Thiscall, ::_HH_CheckDoubleClick);
}
