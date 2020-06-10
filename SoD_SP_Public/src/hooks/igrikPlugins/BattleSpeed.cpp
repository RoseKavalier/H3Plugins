/*
 *
 * These hooks were modified from the plugin by igrik, used with permission.
 * https://github.com/igrikRS/HoMM3-Plugins/blob/master/BattleSpeed/BattleSpeed/BattleSpeed.cpp
 *
 * Based on an original idea by MOP, they modify the options dialog's speed panel
 * to have 10 buttons like the sounds panels, easily allowing for 10 different battle speeds.
 *
 */

#include "BattleSpeed.hpp"
#include <H3API.hpp>

using namespace h3;
using namespace h3::H3Patcher;

// * the new button id for battle speed
constexpr UINT BattleSpeedButton = 240;

// * the original button id for battle speed 0
constexpr INT OrigBattleSpeedButton = 230;

// * where the original battle speed coefficients are referenced
constexpr UINT BattleSpeedReferences[] =
{
	0x43F255 + 3,		0x43F392 + 3,		0x441B2A + 3,
	0x441BDC + 3,		0x4466F4 + 3,		0x44670B + 3,
	0x466CD4 + 3,		0x467758 + 3,		0x467BCA + 3,
	0x468093 + 3,		0x473997 + 3,		0x473A49 + 3,
	0x494662 + 3,		0x4B49AC + 3,		0x5A601C + 3,
	0x5A6813 + 3,		0x5A7FE2 + 3,		0x5A8148 + 3,
};

// * new battle speed coefficients
constexpr FLOAT BattleSpeedCoefficients[] =
{
	1.000f, 0.630f, 0.400f, // original speed coefficients
	0.300f,                 // new speed coefficient
	0.200f, 0.100f,	        // old SoD_SP turbo speed coefficients
	0.075f,                 // new speed coefficient
	0.050f,                 // old SoD_SP turbo speed coefficient
	0.025f, 0.010f          // new speed coefficients
};

// * the new number of battle speeds available
constexpr UINT NumberBattleSpeeds = ArraySize(BattleSpeedCoefficients);
_H3API_STATIC_ASSERT_(NumberBattleSpeeds == 10, "There should be 10 battle coefficient speeds");

// * in creation of options dialog, the normal speed button is no longer wanted
void SkipOriginalSpeedButtonCreation()
{
	constexpr UINT skipSpeedButtonCreation  = 0x46E1F0;
	constexpr UINT endSpeedButtonCreation   = 0x46E2EC;
	constexpr BYTE deltaSpeedButtonCreation =
		endSpeedButtonCreation - skipSpeedButtonCreation - 5;
	constexpr BYTE skipSpeedButtonPatch[]   =
		{ jmp , deltaSpeedButtonCreation, 0, 0, 0, nop, nop };
	HexPatch(skipSpeedButtonCreation, skipSpeedButtonPatch);
}

// * in instantiation of options dialog, the normal speed button
// * initialization should be skipped
void SkipOriginalSpeedButtonInit()
{
	constexpr UINT skipSpeedButtonInit    = 0x46F07A;
	constexpr UINT endSpeedButtonInit     = 0x46F0C0;
	constexpr BYTE deltaSpeedButtonInit   =
		endSpeedButtonInit - skipSpeedButtonInit - 2;
	constexpr BYTE skipSpeedButtonPatch[] =
		{ short_jmp , deltaSpeedButtonInit, nop, nop, nop };
	HexPatch(skipSpeedButtonInit, skipSpeedButtonPatch);
}

_LHF_(ModifyBattleOptionsDialog)
{
	H3SEHandler seh;
	try
	{
		auto dlg = PH3BaseDlg(c->ecx);
		auto dlg_pcx = dlg->GetPcx(200); // the id of the dialog's background pcx

		// * modify the existing appearrance by copying
		// * sound sub-region    [(25, 300), (220, 340)]
		// * to speed sub-region [(25, 222), (220, 262)]
		auto pcx = dlg_pcx->GetPcx();
		pcx->DrawToPcx(25, 300, 195, 40, pcx, 25, 222, FALSE);

		// * follows logic of creating buttons for sound widget
		const UINT current_speed = P_CurrentAnimationSpeed();
		int dx = 0;
		for (UINT i = 0; i < NumberBattleSpeeds; ++i)
		{
			auto def = dlg->CreateDef(29 + dx, 225, BattleSpeedButton + i, NH3Dlg::Assets::SYSLB_DEF, i);
			if (i != current_speed)
				def->Hide(); // hides the def, but it remains enabled
			dx += 19;
		}
	}
	catch (H3Exception& e)
	{
		e.ShowInGame();
	}

	return EXEC_DEFAULT;
}

int __stdcall _HH_BattleOptionsDlgProc(HiHook* h, H3Msg& msg)
{
	if (msg.IsLeftClick())
	{
		const UINT id = UINT(msg.item_id);
		if (id >= BattleSpeedButton && id < BattleSpeedButton + NumberBattleSpeeds)
		{
			// * set the new speed
			P_CurrentAnimationSpeed() = id - BattleSpeedButton;

			// * show the new speed being selected
			auto& items = P_BattleOptionsDlg()->GetList();
			for (auto iter : items)
			{
				const int iter_id = iter->GetID();
				if (iter_id >= BattleSpeedButton && iter_id < BattleSpeedButton + NumberBattleSpeeds)
				{
					if (iter_id == id)
						iter->Show();
					else
						iter->Hide();
				}
			}
			P_BattleOptionsDlg()->Redraw();
			return 1;
		}
	}
	else if (msg.IsRightClick())
	{
		// * if right-clicking on new speed buttons, split speeds into three buckets
		// * to show the original speed button hints and replace the clicked id
		const UINT id = UINT(msg.item_id);
		if (id >= BattleSpeedButton && id < BattleSpeedButton + NumberBattleSpeeds)
			msg.item_id = OrigBattleSpeedButton + (id - BattleSpeedButton - 1) / 3;
	}

	return THISCALL_1(int, h->GetDefaultFunc(), &msg);
}

void battle_speed_init(PatcherInstance * pi)
{
	pi->WriteHiHook(0x46F300, SPLICE_, THISCALL_, _HH_BattleOptionsDlgProc); // [1.19.0] {igrik} handles the new speed options buttons
	pi->WriteLoHook(0x4682B9, ModifyBattleOptionsDialog);                    // [1.19.0] {igrik} creates the new speed options buttons
	SkipOriginalSpeedButtonCreation();                                       // [1.19.0] {igrik} skip creation of normal speed button
	SkipOriginalSpeedButtonInit();                                           // [1.19.0] {igrik} skip initialization of normal speed button
	BytePatch(0x50B556 + 2, NumberBattleSpeeds - 1);                         // [1.19.0] {igrik} normalize registry to accept from 0 ~ 9 instead of 0 ~ 2
	AddressOfPatch(BattleSpeedReferences, BattleSpeedCoefficients);          // [1.19.0] {igrik} replace all references
}