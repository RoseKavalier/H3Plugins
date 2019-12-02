#include "Hooks.h"

using NH3VKey::H3VK_SHIFT;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;
// * a flag to check whether shift key is held down
static BOOL shiftPressed = FALSE;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/*
 *
 * If shift is pressed, pretend we don't have a hero active.
 *
 */
_LHF_(checkShift)
{
	if (shiftPressed)
	{
		c->return_address = 0x40A985;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * If shift is pressed, pretend we don't have a hero active.
 *
 */
_LHF_(changeCursor)
{
	if (shiftPressed)
		c->ecx = -1;
	return EXEC_DEFAULT;
}

/*
 *
 * Check if the Shift key is being pressed.
 * If so, we capture mouse coordinates and simulate a mouseover message.
 *
 */
int __stdcall _HH_CheckShift(HiHook *h, H3AdventureManager* This, H3Msg *msg, int a3, int a4, int a5)
{
	POINT p;
	if (msg->KeyPressed() == H3VK_SHIFT && !shiftPressed && P_Executive->last_mgr == P_AdventureMgr
		&& P_AdventureMgr->dlg->IsTopDialog())
	{
		shiftPressed = TRUE;
		F_GetCursorPosition(p);
		This->previousMousePosition.x = -1;
		This->SimulateMouseOver(p);
	}

	return THISCALL_5(int, h->GetDefaultFunc(), This, msg, a3, a4, a5);
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
	POINT p;
	H3Msg * msg = reinterpret_cast<H3Msg *>(c->edi);
	if (msg->IsKeyPress() && msg->KeyPressed() == H3VK_SHIFT)
	{
		shiftPressed = FALSE;
		F_GetCursorPosition(p);
		P_AdventureMgr->previousMousePosition.x = -1;
		P_AdventureMgr->SimulateMouseOver(p);
	}
	return EXEC_DEFAULT;
}

void Hooks_init(PatcherInstance *pi)
{
	pi->WriteLoHook(0x40A7C7, checkShift);
	pi->WriteLoHook(0x40E495, changeCursor);
	pi->WriteHiHook(0x408BA0, SPLICE_, THISCALL_, _HH_CheckShift);
	pi->WriteLoHook(0x408928, ShiftOff);
}