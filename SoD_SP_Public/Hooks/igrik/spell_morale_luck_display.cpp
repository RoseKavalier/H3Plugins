#include "spell_morale_luck_display.h"

/*
 *
 * These hooks were modified from the plugin by igrik, used with permission.
 * http://forum.df2.ru/index.php?showtopic=30848&view=findpost&p=731203
 *
 * They add digital display of the values of luck, morale and spell length
 * in all Creature Dialogs as well as in the Creature Panel during combat.
 *
 */

 /*
  *
  * This hook adds digital display of luck and morale to creature dialog during combat.
  *
  */
_LHF_(ShowMoraleLuckBonus) // 0x5F3C43 combat
{
	LOG_LOHOOK;
	if (!multiplayer_game)
	{
		H3CombatMonster *mon = (H3CombatMonster *)c->edi;
		INT32 morale = mon->spellsData.morale;
		INT32 luck = mon->spellsData.luck;
		H3Vector<H3DlgText*> *list = (H3Vector<H3DlgText*>*)c->ebx;
		sprintf(h3_TextBuffer, morale < 1 ? "%d" : "+%d", morale);
		H3DlgText *mrl = H3DlgText::Create(48, 209, 20, 20, h3_TextBuffer, TINY_TEXT, 4, 3006, TA_BottomRight);
		if (mrl)
			list->AddSize4(mrl);
		sprintf(h3_TextBuffer, luck < 1 ? "%d" : "+%d", luck);
		H3DlgText *lck = H3DlgText::Create(101, 209, 20, 20, h3_TextBuffer, TINY_TEXT, 4, 3006, TA_BottomRight);
		if (lck)
			list->AddSize4(lck);
	}
	LOG_LOHOOK;
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
	if (!multiplayer_game)
	{
		H3Dlg *dlg = (H3Dlg *)c->ebx;
		INT32 morale = IntAt(c->ebx + 0x68);
		INT32 luck = IntAt(c->ebx + 0x7C);
		sprintf(h3_TextBuffer, morale < 1 ? "%d" : "+%d", morale);
		H3DlgText *mrl = H3DlgText::Create(48, 209, 20, 20, h3_TextBuffer, TINY_TEXT, 4, 3006, TA_BottomRight);
		if (mrl)
			dlg->GetList()->AddSize4(mrl);
		sprintf(h3_TextBuffer, luck < 1 ? "%d" : "+%d", luck);
		H3DlgText *lck = H3DlgText::Create(101, 209, 20, 20, h3_TextBuffer, TINY_TEXT, 4, 3007, TA_BottomRight);
		if (lck)
			dlg->GetList()->AddSize4(lck);
	}
	LOG_LOHOOK;
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
	if (!multiplayer_game)
	{
		INT32 spell_id = IntAt(c->esi);
		if (spell_id >= 0 && spell_id != H3Spell::DISRUPTING_RAY && spell_id != H3Spell::BIND) // infinite length
		{
			H3Dlg *dlg = (H3Dlg *)IntAt(c->ebp - 40);
			INT32 length = IntAt(c->esi + 12);
			sprintf(h3_TextBuffer, "x%d", length);
			H3DlgText *spl = H3DlgText::Create(IntAt(c->ebp - 28), 202, 46, 20, h3_TextBuffer, TINY_TEXT, 4, 3003 - IntAt(c->ebp - 32), TA_BottomRight);
			if (spl)
				dlg->GetList()->AddSize4(spl);
		}
	}
	LOG_LOHOOK;
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
	if (!multiplayer_game)
	{
		if (c->eax >= 3000 && c->eax <= 3007)
		{
			switch (c->eax)
			{
			case 3000:
			case 3001:
			case 3002:
				c->eax = 11; // spells
				break;
			case 3006:
				c->eax = 9; // morale
				break;
			case 3007:
				c->eax = 10; // luck
				break;
			default:
				c->eax = -1; // otherwise
				break;
			}
			c->return_address = 0x5F4B34;
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		}
	}
	LOG_LOHOOK;
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
	if (!multiplayer_game)
	{
		switch (c->esi)
		{
		case 3000:
			c->esi = 221; // spells
			break;
		case 3001:
			c->esi = 222;
			break;
		case 3002:
			c->esi = 223;
			break;
		case 3006:
			c->esi = 219; // morale
			break;
		case 3007:
			c->esi = 220; // luck
			break;
		}
	}
	LOG_LOHOOK;
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
	if (!multiplayer_game)
	{
		H3Vector<H3DlgText*> *list = (H3Vector<H3DlgText*>*)c->esi;
		H3DlgText *txt = H3DlgText::Create(15, c->ebx + 16, 46, 20, h3_NullString, TINY_TEXT, 4, c->edi + 3003, 10);
		if (txt)
			list->AddSize4(txt);
	}
	LOG_LOHOOK;
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
	if (!multiplayer_game)
	{
		H3Vector<H3DlgText*> *list = (H3Vector<H3DlgText*>*)c->esi;
		H3DlgText *txt = H3DlgText::Create(15, IntAt(c->ebp + 24) + 16, 46, 20, h3_NullString, TINY_TEXT, 4, c->ebx + 3003, 10);
		if (txt)
			list->AddSize4(txt);
	}
	LOG_LOHOOK;
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
	if (!multiplayer_game)
	{
		H3Dlg *dlg = (H3Dlg*)(c->edi + 56);
		INT32 itemID = 3006 - IntAt(c->ebp + 8);
		INT32 spell = IntAt(c->esp) - 1;
		H3CombatMonster *mon = (H3CombatMonster*)c->esi;
		if (spell >= 0 && spell != H3Spell::DISRUPTING_RAY && spell != H3Spell::BIND)
			sprintf(h3_TextBuffer, "x%d", mon->activeSpellsDuration[spell]);
		else
			h3_TextBuffer[0] = 0;
		H3DlgItem *it = dlg->GetH3DlgItem(itemID);
		if (it)
			it->SetText(h3_TextBuffer);
	}
	LOG_LOHOOK;
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
