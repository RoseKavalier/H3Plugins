#include "AdvancedCombatInfo.h"

/*
 *
 * Simple structure to store active spell information.
 *
 */
struct SpellDuration
{
	INT32 spell;
	INT32 length;

	BOOL IsShorter(SpellDuration *fastest) { return fastest->length > length; }
};

/*
 *
 * Function that creates advanced combat information dialog
 * based on a single hex number.
 *
 */
void AdvancedCombatInfo(INT32 hex)
{
	H3CombatMonster *mon = P_CombatMgr->squares[hex].GetMonster();
	if (!mon)
		return;
	int spellCount = 0;
	SpellDuration spellsInfo[81]; // where to store spell information
	for (int i = 0; i < 81; i++)
	{
		if (int duration = mon->activeSpellsDuration[i])
		{
			spellsInfo[spellCount].spell = i;
			if (i != H3Spell::DISRUPTING_RAY && i != H3Spell::BIND && i != H3Spell::ACID_BREATH) // infinite duration
				spellsInfo[spellCount].length = duration;
			else
				spellsInfo[spellCount].length = 300; // store last
			spellCount++;
		}
	}

	// sort spells by shortest duration
	SpellDuration *fastest, *cur, temp;
	int fastestIndex;

	for (int i = 0; i < spellCount; i++)
	{
		fastest = &spellsInfo[i];
		fastestIndex = i;
		cur = &spellsInfo[i + 1];

		for (int j = i + 1; j < spellCount; j++)
		{
			if (cur->IsShorter(fastest)) // only swap if current has shorter duration than fastest
			{
				fastest = cur;
				fastestIndex = j;
			}
			cur++;
		}
		if (fastestIndex != i)
		{
			temp = *fastest;
			fastest->length = spellsInfo[i].length;
			fastest->spell = spellsInfo[i].spell;
			spellsInfo[i].length = temp.length;
			spellsInfo[i].spell = temp.spell;
		}
	}

	// dialog dimensions and position
#define xSpacing 50
#define nColumns 8
#define hEdge 20
#define yEdge 20

	int width = 2 * hEdge + nColumns * xSpacing;
	int height = 110 + ((spellCount - 1) / nColumns) * xSpacing;

	int x = (gameWidth - width) / 2; // center X
	int y = (gameHeight - 600) / 2 - 14; // place at top of battlefield

	/////////////////////////////
	//
	//	Create dialog
	//
	/////////////////////////////
	H3Dlg dlg(width, height, x, y, TRUE); // created with a status bar

	/////////////////////////////
	//
	//	Create DEFs and text
	//
	/////////////////////////////
	int _x, _y;
	SpellDuration *sd = spellsInfo;
	for (int i = 0; i < spellCount; i++)
	{
		_x = hEdge + xSpacing * (i % nColumns); // columns, 8 items per row
		_y = yEdge + xSpacing * (i / nColumns); // rows

		dlg.CreateDef(_x, _y, 0, SPELL_SMALL, sd->spell + 1); // + 1 because first frame of spellint.def is blank
		if (sd->spell != H3Spell::DISRUPTING_RAY && sd->spell != H3Spell::BIND && sd->spell != H3Spell::ACID_BREATH) // infinite duration
		{
			sprintf(h3_TextBuffer, "{x}%d", sd->length);
			// _y + 36 means below the spell DEF
			// 20 is for the height of text
			dlg.CreateText(_x, _y + 36, xSpacing, 20, h3_TextBuffer, SMALL_TEXT, TEXT_REGULAR, 0, TextAlignment::TA_HCenter);
		}
	}

	/////////////////////////////
	//
	//	Fill in line blanks
	//
	/////////////////////////////
	int remainder = (nColumns - 1) - ((spellCount - 1) % nColumns);

	if (spellCount == 0) // add a blank line if there are no spells
	{
		remainder = nColumns;
		_x = hEdge - xSpacing;
		_y = yEdge;
	}

	while (remainder > 0)
	{
		_x += xSpacing;
		dlg.CreateDef(_x, _y, 0, SPELL_SMALL, 0); // frame 0 is blank
		remainder--;
	}

	/////////////////////////////
	//
	//	Show some extra info
	//
	/////////////////////////////
	if (dlg.GetHintBar())
	{
		PCHAR status = SP_CombatText->Active();
		H3CreatureFlags *flags = &mon->info.flags;
		if (flags->WAITING)
			status = SP_CombatText->Waiting();
		if (flags->DONE)
			status = SP_CombatText->Moved();
		if (flags->DEFENDING)
			status = SP_CombatText->Defending();

		sprintf(h3_TextBuffer, "{%s:} %s      {%s:} %d      {%s:} %d", SP_CombatText->Status(), status,
			SP_CombatText->Retaliations(), mon->retaliations, SP_CombatText->CastsLeft(), mon->info.spellCharges);
		dlg.GetHintBar()->SetText(h3_TextBuffer);
	}

	/////////////////////////////
	//
	//	Show while right-click
	//
	/////////////////////////////
	dlg.RMB_Show(); // destructor automatically called afterwards
}