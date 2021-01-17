#include "sodsp/Log.hpp"
#include "Global.hpp"
using namespace h3;
using namespace NH3Dlg;
using namespace h3::H3Patcher;

#pragma region EXTRA_BATTLE_SPEED_BUTTONS

//=====================================================
//
//               EXTRA BATTLE SPEED BUTTONS
//
//=====================================================


/*
 *
 * These hooks were modified from the plugin by igrik, used with permission.
 * https://github.com/igrikRS/HoMM3-Plugins/blob/master/BattleSpeed/BattleSpeed/BattleSpeed.cpp
 *
 * Based on an original idea by MOP, they modify the options dialog's speed panel
 * to have 10 buttons like the sounds panels, easily allowing for 10 different battle speeds.
 *
 */

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
constexpr UINT NumberBattleSpeeds = std::size(BattleSpeedCoefficients);
_H3API_STATIC_ASSERT_(NumberBattleSpeeds == 10, "There should be 10 battle coefficient speeds");

// * in creation of options dialog, the normal speed button is no longer wanted
void SkipOriginalSpeedButtonCreation()
{
	constexpr UINT skipSpeedButtonCreation  = 0x46E1F0;
	constexpr UINT endSpeedButtonCreation   = 0x46E2EC;
	constexpr BYTE deltaSpeedButtonCreation =
		endSpeedButtonCreation - skipSpeedButtonCreation - 5;
	constexpr BYTE skipSpeedButtonPatch[]   =
		{ JMP , deltaSpeedButtonCreation, 0, 0, 0, NOP, NOP };
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
		{ SHORT_JMP , deltaSpeedButtonInit, NOP, NOP, NOP };
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

#pragma endregion EXTRA_BATTLE_SPEED_BUTTONS

#pragma region SPELL_LUCK_MORALE_DISPLAY

//=====================================================
//
//           SPELL LUCK MORALE DISPLAY
//
//=====================================================

/*
 *
 * These hooks were modified from the plugin by igrik, used with permission.
 * http://forum.df2.ru/index.php?showtopic=30848&view=findpost&p=731203
 *
 * They add digital display of the values of luck, morale and spell length
 * in all Creature Dialogs as well as in the Creature Panel during combat.
 *
 */

namespace lb
{
	enum igrik_ids : INT
	{
		FirstSpell  = 3000,
		SecondSpell = 3001,
		ThirdSpell  = 3002,
		SpellLength = 3003,
		MoraleText  = 3006,
		LuckText    = 3007,

		FirstIndex = FirstSpell,
		LastIndex  = LuckText,
	};
}

/*
 *
 * This hook adds digital display of luck and morale to creature dialog during combat.
 *
 */
_LHF_(ShowMoraleLuckBonus) // 0x5F3C43 combat
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		H3CombatMonster* mon = (H3CombatMonster*)c->edi;
		INT32 morale = mon->spellsData.morale;
		INT32 luck = mon->spellsData.luck;
		H3Vector<H3DlgText*>* list = (H3Vector<H3DlgText*>*)c->ebx;
		F_sprintf(morale < 1 ? "%d" : "+%d", morale);
		H3DlgText* mrl = H3DlgText::Create(48, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::MoraleText, TextAlignment::BOTTOM_RIGHT);
		if (mrl)
			list->AddSize4(mrl);
		F_sprintf(luck < 1 ? "%d" : "+%d", luck);
		H3DlgText* lck = H3DlgText::Create(101, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::LuckText, TextAlignment::BOTTOM_RIGHT);
		if (lck)
			list->AddSize4(lck);
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook adds digital display of luck and morale to creature dialog on adventure map.
 *
 */
_LHF_(MapMoraleLuckBonus) // 0x5F439B
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		H3Dlg* dlg = PH3Dlg(c->ebx);
		INT32 morale = IntAt(c->ebx + 0x68);
		INT32 luck = IntAt(c->ebx + 0x7C);
		F_sprintf(morale < 1 ? "%d" : "+%d", morale);
		H3DlgText* mrl = H3DlgText::Create(48, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::MoraleText, TextAlignment::BOTTOM_RIGHT);
		if (mrl)
			dlg->GetList().AddSize4(mrl);
		F_sprintf(luck < 1 ? "%d" : "+%d", luck);
		H3DlgText* lck = H3DlgText::Create(101, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::LuckText, TextAlignment::BOTTOM_RIGHT);
		if (lck)
			dlg->GetList().AddSize4(lck);
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook adds digital display of spells duration to creature dialog during combat.
 *
 */
_LHF_(ShowMonsterSpells)
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		INT32 spell_id = IntAt(c->esi);
		if (spell_id >= 0 && spell_id != H3Spell::eSpells::DISRUPTING_RAY) // infinite length
		{
			H3Dlg* dlg = c->Local<PH3Dlg>(10);
			INT32 length = IntAt(c->esi + 12);
			F_sprintf("x%d", length);
			H3DlgText* spl = H3DlgText::Create(c->Local(7), 202, 46, 20, h3_TextBuffer, Text::TINY, 4, lb::SpellLength - c->Local(8), TextAlignment::BOTTOM_RIGHT);
			if (spl)
				dlg->GetList().AddSize4(spl);
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook substitutes the hover item id of created text items to the items that lay beneath.
 *
 */
_LHF_(ShowCorrectSpellInfo)
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		if (c->eax >= lb::FirstIndex && c->eax <= lb::LastIndex)
		{
			switch (c->eax)
			{
			case lb::FirstSpell:
			case lb::SecondSpell:
			case lb::ThirdSpell:
				c->eax = 11; // spells
				break;
			case lb::MoraleText:
				c->eax = 9; // morale
				break;
			case lb::LuckText:
				c->eax = 10; // luck
				break;
			default:
				c->eax = -1; // otherwise
				break;
			}
			c->return_address = 0x5F4B34;
			return NO_EXEC_DEFAULT;
		}
	}

	return EXEC_DEFAULT;
}

/*
 *
 * This hook substitutes the hover item id of created text items to the items that lay beneath.
 *
 */
_LHF_(ShowCorrectSpellInfo2)
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		switch (c->esi)
		{
		case lb::FirstSpell:
			c->esi = 221; // spells
			break;
		case lb::SecondSpell:
			c->esi = 222;
			break;
		case lb::ThirdSpell:
			c->esi = 223;
			break;
		case lb::MoraleText:
			c->esi = 219; // morale
			break;
		case lb::LuckText:
			c->esi = 220; // luck
			break;
		default:
			break;
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook creates text items for the Creature Panel during combat.
 *
 */
_LHF_(CreatePanelSpellInfo)
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		auto list = reinterpret_cast<H3Vector<H3DlgText*>*>(c->esi);
		auto txt = H3DlgText::Create(15, c->ebx + 16, 46, 20, h3_NullString, Text::TINY, 4, c->edi + lb::SpellLength, 10);
		if (txt)
			list->AddSize4(txt);
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook creates text items for the Creature Panel during combat.
 *
 */
_LHF_(CreatePanelSpellInfo2)
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		auto list = reinterpret_cast<H3Vector<H3DlgText*>*>(c->esi);
		auto txt = H3DlgText::Create(15, c->Arg(5) + 16, 46, 20, h3_NullString, Text::TINY, 4, c->ebx + lb::SpellLength, 10);
		if (txt)
			list->AddSize4(txt);
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook adds text to the previously created text items of the Creature Panel.
 *
 */
_LHF_(ShowPanelSpellInfo)
{
	LOG_LOHOOK;
	if (!F_Multiplayer())
	{
		auto dlg = reinterpret_cast<H3Dlg*>(c->edi + 56);
		const INT32 item_id = lb::MoraleText - c->Arg(1);
		const INT32 spell = IntAt(c->esp) - 1;
		auto mon = reinterpret_cast<H3CombatMonster*>(c->esi);
		if (spell >= 0 && spell != H3Spell::eSpells::DISRUPTING_RAY)
			F_sprintf("x%d", mon->activeSpellsDuration[spell]);
		else
			h3_TextBuffer[0] = 0;
		auto it = dlg->GetH3DlgItem(item_id)->CastText();
		if (it)
			it->SetText(h3_TextBuffer);
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook creates a messagebox with OK button
 * when left-clicking on creature luck or morale
 * icons in their information dialog
 *
 */
_LHF_(MoraleLuckInfoLeftClick)
{
	constexpr int MORALE_ID = 219;
	constexpr int LUCK_ID   = 220;
	namespace pic = NH3Dlg::PictureCategories;

	const int id = c->eax;

	if (id == MORALE_ID || id == lb::MoraleText)
	{
		auto dlg = reinterpret_cast<H3MonsterInfoDlg*>(c->ebx);
		LPCSTR morale_format = StrAt(0x6A5830);
		H3String info;
		LPCSTR text_info;
		INT32 picture_type;
		if (dlg->morale == 0)
		{
			picture_type = pic::NEUTRAL_MORALE;
			text_info = StrAt(0x6A5828);
			info.Printf(morale_format, text_info) += StrAt(0x6A53DC);
		}
		else if (dlg->morale < 0)
		{
			picture_type = pic::NEGATIVE_MORALE;
			text_info = StrAt(0x6A582C);
			info.Printf(morale_format, text_info) += dlg->moraleModifiers;
		}
		else // morale > 0
		{
			picture_type = pic::POSITIVE_MORALE;
			text_info = StrAt(0x6A5824);
			info.Printf(morale_format, text_info) += dlg->moraleModifiers;
		}

		F_MessageBox(info, picture_type);
	}
	else if (id == LUCK_ID || id == lb::LuckText)
	{
		auto dlg = reinterpret_cast<H3MonsterInfoDlg*>(c->ebx);
		LPCSTR luck_format = StrAt(0x6A53A0);
		H3String info;
		LPCSTR text_info;
		INT32 picture_type;
		if (dlg->luck == 0)
		{
			picture_type = pic::NEUTRAL_LUCK;
			text_info = StrAt(0x6A5398);
			info.Printf(luck_format, text_info) += StrAt(0x6A53DC);
		}
		else if (dlg->luck < 0)
		{
			picture_type = pic::NEGATIVE_LUCK;
			text_info = StrAt(0x6A539C);
			info.Printf(luck_format, text_info) += dlg->luckModifiers;
		}
		else // luck > 0
		{
			picture_type = pic::POSITIVE_LUCK;
			text_info = StrAt(0x6A5394);
			info.Printf(luck_format, text_info) += dlg->luckModifiers;
		}
		F_MessageBox(info, picture_type);
	}
	return EXEC_DEFAULT;
}

#pragma endregion SPELL_LUCK_MORALE_DISPLAY

#pragma region QUICK_TOWN_UPGRADE

//=====================================================
//
//               QUICK TOWN UPGRADE
//
//=====================================================

/*
 *
 * These hooks were modified from the plugin by igrik, used with permission.
 * http://forum.df2.ru/index.php?showtopic=30848&view=findpost&p=743178
 *
 * This adds automatic creature upgrade by clicking on creature portraits
 * while holding down the 'A' key.
 *
 */

constexpr CHAR TownUpgradeHotkey = 'A';

/*
 *
 * This function attempts to upgrade the stack of an army at the index position.
 * Returns TRUE if upgrade was sucessful.
 *
 */
BOOL UpgradeArmyStack(H3Army* army, H3Town* town, H3Player* me, INT32 index, BOOL individual = FALSE)
{
	int type = army->type[index];
	if (type == -1)
		return FALSE;
	if (!individual && type == NH3Creatures::SKELETON)
		return FALSE;
	int upg_type = F_GetCreatureUpgrade(type);
	if (upg_type == -1)
		return FALSE;
	H3CreatureInformation* c_info = P_Creatures()(type);
	if (c_info->town != town->type)
		return FALSE;
	if (!town->IsBuildingBuilt(H3Town::eBuildings::B_DWELL1U + c_info->level))
		return FALSE;
	H3Resources& player_res = me->playerResources;
	H3Resources cost = c_info->UpgradeCost(P_Creatures()(upg_type), army->count[index]);
	if (player_res < cost)
		return FALSE;
	player_res -= cost;
	army->type[index] = upg_type;
	return TRUE;
}

/*
 *
 * This function gets the relevant H3Army structure (if any) to attempt autoupgrade.
 * Returns TRUE if at least one upgrade was done.
 *
 */
BOOL TryToUpgrade(H3Town* town, int click_id)
{
	BOOL r = FALSE;
	H3Army* army;
	H3Main* main = P_Main();
	H3Player* me = main->GetPlayer();
	if (me == P_ActivePlayer() && me->ownerID == town->owner)
	{
		if (click_id >= 115 && click_id <= 121) // garrison creatures
		{
			if (H3Hero* hero = main->GetHero(town->garrisonHero))
				r = UpgradeArmyStack(&hero->army, town, me, click_id - 115, TRUE); // if no hero then there are no creatures here!
			else
				r = UpgradeArmyStack(&town->Guards, town, me, click_id - 115, TRUE); // if no hero then there are no creatures here!
		}
		else if (click_id >= 140 && click_id <= 146) // visiting creatures
		{
			if (H3Hero* hero = main->GetHero(town->visitingHero))
				r = UpgradeArmyStack(&hero->army, town, me, click_id - 140, TRUE); // if no hero then there are no creatures here!
		}
		else if (click_id == 123) // garrison hero portrait
		{
			if (H3Hero* hero = main->GetHero(town->garrisonHero))
				army = &hero->army;
			else
				army = &town->Guards;
			for (int i = 0; i < 7; i++)
				r += UpgradeArmyStack(army, town, me, i);
		}
		else if (click_id == 125) // visiting hero portrait
		{
			if (H3Hero* hero = main->GetHero(town->visitingHero))  // if no hero then there are no creatures here!
			{
				army = &hero->army;
				for (int i = 0; i < 7; i++)
					r += UpgradeArmyStack(army, town, me, i);
			}
		}
	}

	return r;
}

/*
 *
 * This hook creates checks if the autoupgrade hotkey is held when clicking
 * on creature portraits. If so, an attempt to upgrade is made.
 *
 */
_LHF_(QuickUpgradeInTown)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && GetKeyState(TownUpgradeHotkey) < 0)
	{
		if (H3Town* town = P_TownMgr()->town)
		{
			int click_id = c->edi;

			if (TryToUpgrade(town, click_id)) // if at least one upgrade was successful, redraw Town dialog
			{
				P_TownMgr()->Draw();
				P_TownMgr()->RefreshScreen();
				c->return_address = 0x5D460F;
				return NO_EXEC_DEFAULT;
			}
		}
	}
	return EXEC_DEFAULT;
}
#pragma endregion QUICK_TOWN_UPGRADE

//=====================================================
//
//                  HOOKS INIT
//
//=====================================================

void SoD_SP_Plugin::IgrikHooks()
{
	//==================================
	//      BATTLE SPEED BUTTONS
	//==================================

	Hook(0x46F300, Splice, Thiscall, _HH_BattleOptionsDlgProc);     // [1.19.0] {igrik} handles the new speed options buttons
	Hook(0x4682B9, ModifyBattleOptionsDialog);                      // [1.19.0] {igrik} creates the new speed options buttons
	SkipOriginalSpeedButtonCreation();                              // [1.19.0] {igrik} skip creation of normal speed button
	SkipOriginalSpeedButtonInit();                                  // [1.19.0] {igrik} skip initialization of normal speed button
	BytePatch(0x50B556 + 2, NumberBattleSpeeds - 1);                // [1.19.0] {igrik} normalize registry to accept from 0 ~ 9 instead of 0 ~ 2
	AddressOfPatch(BattleSpeedReferences, BattleSpeedCoefficients); // [1.19.0] {igrik} replace all references

	//==================================
	//      LUCK & MORALE DISPLAY
	//==================================

	Hook(0x5F3C43, ShowMoraleLuckBonus);
	Hook(0x5F439B, MapMoraleLuckBonus);
	Hook(0x5F6BE2, ShowMonsterSpells); // shows length of spells

	Hook(0x5F4B05, ShowCorrectSpellInfo); // mouse hover and RMB
	Hook(0x5F522A, ShowCorrectSpellInfo2);

	Hook(0x46D12B, CreatePanelSpellInfo);
	Hook(0x46D4CB, CreatePanelSpellInfo2);
	Hook(0x46D9F0, ShowPanelSpellInfo);
	Hook(0x5F50F8, MoraleLuckInfoLeftClick); // [1.19.1.0] by RoseKavalier ~ uses IDs from luck & morale display

	//==================================
	//      QUICK TOWN UPGRADE
	//==================================

	Hook(0x5D45FD, QuickUpgradeInTown);
}