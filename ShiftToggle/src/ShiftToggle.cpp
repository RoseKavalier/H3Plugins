#include "ShiftToggle.hpp"

using namespace h3;
using NH3VKey::H3VK_SHIFT;

ShiftTogglePlugin ShiftToggle;

ShiftTogglePlugin& ShiftTogglePlugin::GetPlugin()
{
    return ShiftToggle;
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

int ShiftTogglePlugin::CheckShift(HookContext& c)
{
    if (m_shiftPressed)
    {
        c.return_address = 0x40A985;
        return NO_EXEC_DEFAULT;
    }
    return EXEC_DEFAULT;
}

int ShiftTogglePlugin::ChangeCursor(HookContext& c)
{
    if (m_shiftPressed)
        c.ecx = -1;
    return EXEC_DEFAULT;
}

int ShiftTogglePlugin::ShiftOff(HookContext& c)
{
    POINT p;
    auto msg = c.Edi<H3Msg*>();
    if (msg->IsKeyPress() && msg->KeyPressed() == H3VK_SHIFT)
    {
        m_shiftPressed = FALSE;
        F_GetCursorPosition(p);
        P_AdventureMgr()->previousMousePosition.x = -1;
        P_AdventureMgr()->SimulateMouseOver(p);
    }
    return EXEC_DEFAULT;
}

int ShiftTogglePlugin::DialogsTurnOffShift()
{
    m_shiftPressed = FALSE;
    return EXEC_DEFAULT;
}

int ShiftTogglePlugin::_HH_CheckShift(HiHook* h, H3AdventureManager* This, H3Msg* msg, int a3, int a4, int a5)
{
    POINT p;
    if (msg->KeyPressed() == H3VK_SHIFT && !m_shiftPressed && P_ExecutiveMgr()->last_mgr == P_AdventureMgr()
        && P_AdventureMgr()->dlg->IsTopDialog())
    {
        m_shiftPressed = TRUE;
        F_GetCursorPosition(p);
        This->previousMousePosition.x = -1;
        This->SimulateMouseOver(p);
    }

    return THISCALL_5(int, h->GetDefaultFunc(), This, msg, a3, a4, a5);
}

/*
 *
 * If shift is pressed, pretend we don't have a hero active.
 *
 */
_LHF_(CheckShift)
{
    return ShiftToggle.CheckShift(*c);
}

/*
 *
 * If shift is pressed, pretend we don't have a hero active.
 *
 */
_LHF_(ChangeCursor)
{
    return ShiftToggle.ChangeCursor(*c);
}

/*
 *
 * Check if the Shift key is being pressed.
 * If so, we capture mouse coordinates and simulate a mouseover message.
 *
 */
int __stdcall _HH_CheckShift(HiHook* h, H3AdventureManager* This, H3Msg* msg, int a3, int a4, int a5)
{
    return ShiftToggle._HH_CheckShift(h, This, msg, a3, a4, a5);
}

/*
 *
 * There are normally no checks when keys are unpressed on the adventure map.
 * If shift was being pressed and the shift key is released, we reset the flag
 * and simulate a mouseover message with current cursor position.
 *
 */
_LHF_(ShiftOff)
{
    return ShiftToggle.ShiftOff(*c);
}

/*
 *
 * If holding shift when triggering a dialog
 * then reset to avoid getting stuck.
 *
 */
_LHF_(DialogsTurnOffShift)
{
    return ShiftToggle.DialogsTurnOffShift();
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void ShiftTogglePlugin::Start()
{
    Hook(0x40A7C7, ::CheckShift);
    Hook(0x40E495, ::ChangeCursor);
    Hook(0x408BA0, Splice, Thiscall, ::_HH_CheckShift);
    Hook(0x408928, ::ShiftOff);
    Hook(0x5FFA20, ::DialogsTurnOffShift);
}