/*
 *
 * These hooks were modified from the plugin by igrik, used with permission.
 * http://forum.df2.ru/index.php?showtopic=30848&view=findpost&p=731203
 *
 * They add digital display of the values of luck, morale and spell length
 * in all Creature Dialogs as well as in the Creature Panel during combat.
 *
 */

#include "spell_morale_luck_display.hpp"
#include <H3API.hpp>
#include "sodsp/Log.hpp"

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
		LastIndex = LuckText,
	};
}

using namespace h3;
using namespace NH3Dlg;

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
		H3CombatMonster *mon = (H3CombatMonster *)c->edi;
		INT32 morale = mon->spellsData.morale;
		INT32 luck = mon->spellsData.luck;
		H3Vector<H3DlgText*> *list = (H3Vector<H3DlgText*>*)c->ebx;
		F_sprintf(morale < 1 ? "%d" : "+%d", morale);
		H3DlgText *mrl = H3DlgText::Create(48, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::MoraleText, TextAlignment::BottomRight);
		if (mrl)
			list->AddSize4(mrl);
		F_sprintf(luck < 1 ? "%d" : "+%d", luck);
		H3DlgText *lck = H3DlgText::Create(101, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::LuckText, TextAlignment::BottomRight);
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
		H3Dlg *dlg = PH3Dlg(c->ebx);
		INT32 morale = IntAt(c->ebx + 0x68);
		INT32 luck = IntAt(c->ebx + 0x7C);
		F_sprintf(morale < 1 ? "%d" : "+%d", morale);
		H3DlgText *mrl = H3DlgText::Create(48, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::MoraleText, TextAlignment::BottomRight);
		if (mrl)
			dlg->GetList().AddSize4(mrl);
		F_sprintf(luck < 1 ? "%d" : "+%d", luck);
		H3DlgText *lck = H3DlgText::Create(101, 209, 20, 20, h3_TextBuffer, Text::TINY, 4, lb::LuckText, TextAlignment::BottomRight);
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
		if (spell_id >= 0 && spell_id != H3Spell::DISRUPTING_RAY && spell_id != H3Spell::BIND) // infinite length
		{
			H3Dlg *dlg = c->Local<PH3Dlg>(10);
			INT32 length = IntAt(c->esi + 12);
			F_sprintf("x%d", length);
			H3DlgText *spl = H3DlgText::Create(c->Local(7), 202, 46, 20, h3_TextBuffer, Text::TINY, 4, lb::SpellLength - c->Local(8), TextAlignment::BottomRight);
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
		if (spell >= 0 && spell != H3Spell::DISRUPTING_RAY && spell != H3Spell::BIND)
			F_sprintf("x%d", mon->activeSpellsDuration[spell]);
		else
			h3_TextBuffer[0] = 0;
		auto it = dlg->GetH3DlgItem(item_id)->CastText();
		if (it)
			it->SetText(h3_TextBuffer);
	}
	return EXEC_DEFAULT;
}

void spell_morale_luck_display_init(PatcherInstance * pi)
{
	pi->WriteLoHook(0x5F3C43, ShowMoraleLuckBonus);
	pi->WriteLoHook(0x5F439B, MapMoraleLuckBonus);
	pi->WriteLoHook(0x5F6BE2, ShowMonsterSpells); // shows length of spells

	pi->WriteLoHook(0x5F4B05, ShowCorrectSpellInfo); // mouse hover and RMB
	pi->WriteLoHook(0x5F522A, ShowCorrectSpellInfo2);

	pi->WriteLoHook(0x46D12B, CreatePanelSpellInfo);
	pi->WriteLoHook(0x46D4CB, CreatePanelSpellInfo2);
	pi->WriteLoHook(0x46D9F0, ShowPanelSpellInfo);
}
