#include "AdvancedCombatInfo.hpp"
#include "Global.hpp"

using namespace h3;

using sodsp::txt::TCombat;
using namespace NH3Dlg;
/*
 *
 * Simple structure to store active spell information.
 *
 */
struct SpellDuration
{
	INT32 spell;
	INT32 length;

	bool operator<(SpellDuration& fastest) const { return length < fastest.length; }
};

/*
 *
 * Function that creates advanced combat information dialog
 * based on a single hex number.
 *
 */
void AdvancedCombatInfo(const int hex)
{
	H3SEHandler seh;
	try
	{
		H3CombatMonster *mon = P_CombatMgr()->squares[hex].GetMonster();
		if (!mon)
			return;
		int spell_count = 0;
		SpellDuration spells_info[81]; // where to store spell information
		for (int i = 0; i < 81; i++)
		{
			if (const int duration = mon->activeSpellsDuration[i])
			{
				spells_info[spell_count].spell = i;
				if (i != int(H3Spell::eSpells::DISRUPTING_RAY) && i != int(H3Spell::eSpells::BIND) && i != int(H3Spell::eSpells::ACID_BREATH)) // infinite duration
					spells_info[spell_count].length = duration;
				else
					spells_info[spell_count].length = 300; // store last
				spell_count++;
			}
		}

		// sort spells by shortest duration

		for (int i = 0; i < spell_count; i++)
		{
			auto fastest = &spells_info[i];
			auto fastest_index = i;
			auto cur = &spells_info[i + 1];

			for (int j = i + 1; j < spell_count; j++)
			{
				if (*cur < *fastest) // only swap if current has shorter duration than fastest
				{
					fastest = cur;
					fastest_index = j;
				}
				cur++;
			}
			if (fastest_index != i)
				std::swap(spells_info[i], *fastest);
		}

		// dialog dimensions and position

		constexpr INT x_spacing = 50;
		constexpr INT n_columns = 8;
		constexpr INT h_edge = 20;
		constexpr INT y_edge = 20;
		constexpr INT width = 2 * h_edge + n_columns * x_spacing;

		const int height = spell_count <= 0 ? 110 : 110 + ((spell_count - 1) / n_columns) * x_spacing;

		const auto x = (P_GameWidth() - width) >> 1; // center X
		const auto y = ((P_GameHeight() - 600) >> 1) - 14; // place at top of battlefield

		/////////////////////////////
		//
		//	Create dialog
		//
		/////////////////////////////
		H3Dlg dlg(width, height, x, y, TRUE); // created with a status bar

		/////////////////////////////
		//
		//	Draw DEFs and text
		//
		/////////////////////////////

		auto pcx = dlg.GetBackgroundPcx();
		if (!pcx)
			return;
		H3DefLoader def(Assets::SPELL_SMALL);
		if (!def)
			return;

		auto _x = 0, _y = 0;
		auto sd = spells_info;
		for (auto i = 0; i < spell_count; i++, sd++)
		{
			_x = h_edge + x_spacing * (i % n_columns); // columns, 8 items per row
			_y = y_edge + x_spacing * (i / n_columns); // rows

			def->DrawToPcx16(0, sd->spell + 1, pcx, _x, _y); // + 1 because first frame of spellint.def is blank
			if (sd->spell != int(H3Spell::eSpells::DISRUPTING_RAY) && sd->spell != int(H3Spell::eSpells::BIND) && sd->spell != int(H3Spell::eSpells::ACID_BREATH)) // infinite duration
			{
				F_sprintf("{x}%d", sd->length);
				// _y + 36 means below the spell DEF
				// 20 is for the height of text
				P_SmallFont()->TextDraw(pcx, h3_TextBuffer, _x, _y + 36, x_spacing, 20, TextColor::REGULAR, TextAlignment::HCenter);
			}
		}

		/////////////////////////////
		//
		//	Fill in line blanks
		//
		/////////////////////////////
		auto remainder = (n_columns - 1) - ((spell_count - 1) % n_columns);

		if (spell_count == 0) // add a blank line if there are no spells
		{
			remainder = n_columns;
			_x = h_edge - x_spacing;
			_y = y_edge;
		}

		while (remainder > 0)
		{
			_x += x_spacing;
			def->DrawToPcx16(0, 0, pcx, _x, _y);
			remainder--;
		}

		/////////////////////////////
		//
		//	Show some extra info
		//
		/////////////////////////////
		if (dlg.GetHintBar())
		{
			LPCSTR status = TCombat()->Active();
			H3CreatureFlags& flags = mon->info.flags;
			if (flags.WAITING)
				status = TCombat()->Waiting();
			if (flags.DONE)
				status = TCombat()->Moved();
			if (flags.DEFENDING)
				status = TCombat()->Defending();

			F_sprintf("{%s:} %s      {%s:} %d      {%s:} %d", TCombat()->Status(), status,
				TCombat()->Retaliations(), mon->retaliations, TCombat()->CastsLeft(), mon->info.spellCharges);
			dlg.GetHintBar()->SetText(h3_TextBuffer);
		}

		/////////////////////////////
		//
		//	Show while right-click
		//
		/////////////////////////////
		dlg.RMB_Show(); // destructor automatically called afterwards
	}
	catch (H3Exception& e)
	{
		e.ShowInGame();
	}
}