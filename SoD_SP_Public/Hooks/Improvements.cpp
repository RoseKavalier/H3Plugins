#include "Improvements.h"
#include "hotkeys.h"

/*
 *
 * This hook prevents PLAGUE or random creature spawns
 *
 */
int __stdcall _HH_MonthOfTheRng(HiHook *h, int Min, int Max)
{

	LOG_HIHOOK;
	int r = FASTCALL_2(int, h->GetDefaultFunc(), Min, Max);
	// 10 - PLAGUE
	// 6-7-8-9 Population doubles
	// 1-2-3-4-5 regular month
	// does not skip month of the Imp check @ 0x4C8C2E
	if (!multiplayer_game)
	{
		if ((SODSP_OPTIONS.double_growth && SODSP_OPTIONS.plague) // both options
			|| (SODSP_OPTIONS.double_growth && r > 5 && r <= 9) // not plague, but set to double population
			|| (SODSP_OPTIONS.plague && r == 10) // not double, but set to plague
			)
			r = 0;
	}
	LOG_HIHOOK;
	return r;
}

/*
 *
 * This hook prevents weekly +5 population growths.
 *
 */
int __stdcall _HH_WeekOfTheRNG(HiHook *h, int Min, int Max)
{
	LOG_HIHOOK;
	int r = FASTCALL_2(int, h->GetDefaultFunc(), Min, Max);
	// 1 week of the
	// else regular week
	if (!multiplayer_game && SODSP_OPTIONS.weekly_growth)
		r = 0;
	LOG_HIHOOK;
	return r;
}

/*
 *
 * This hook restores original RNG calculation, used by Obstacles algorithm and others.
 *
 */
_LHF_(CombatObstacles) // actually RNG
{
	LOG_LOHOOK;
	if (multiplayer_game || !SODSP_OPTIONS.obstacles)
		return EXEC_DEFAULT;

	static _ptr_ orig_combat_address;
	if (!orig_combat_address)
	{
		HiHook *hh = _SODSP->GetFirstHiHookAt(0x50C7C0);
		if (hh)
			orig_combat_address = hh->GetDefaultFunc();
		else
			orig_combat_address = c->return_address;
	}
	if (c->return_address == orig_combat_address)
		return EXEC_DEFAULT;

	c->return_address = orig_combat_address;
	LOG_LOHOOK;
	return NO_EXEC_DEFAULT;
}

/*
 *
 * This hook restores original wandering monster split seed.
 *
 */
void __stdcall _HH_CreatureSplit(HiHook *h, int This)
{
	LOG_HIHOOK;
	if (multiplayer_game || !SODSP_OPTIONS.split)
		return THISCALL_1(void, h->GetDefaultFunc(), This);
	THISCALL_1(void, 0x50C7B0, This);
}

/*
 *
 * This hook shows current mouse coordinates in the adventure map status bar.
 * It is expanded to show Movement Cost if ALT is pressed.
 *
 */
_LHF_(MapHintCoordinates)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.adventure_coordinates)
	{
		H3Position coord = P_AdventureMgr->mousePosition;
		////////////////////////
		// from v1_15
		///////////////////////
		ShowMovementCost(coord);

		sprintf(h3_TextBuffer, "%s {~%s}(%d, %d, %d)}", h3_TextBuffer, SODSP_COLOR.adventure_coordinates.String(), coord.x, coord.y, coord.z);
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook restores original RNG calculations by using the original
 * RandomSeed function.
 *
 */
_LHF_(OriginalRng)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.rng)
	{
		static DWORD default_rng_address;

		if (!default_rng_address)
		{
			HiHook *hh;
			hh = _SODSP->GetFirstHiHookAt(0x61842C); // HD+
			if (hh)
				default_rng_address = hh->GetDefaultFunc();
			else
				default_rng_address = c->return_address; // regular HD
		}

		if (c->return_address == default_rng_address)
			return EXEC_DEFAULT;

		c->return_address = default_rng_address;
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook restores seed calculation when entering creature banks.
 *
 */
void __stdcall _HH_creatureBankSeed(HiHook *h, int _this)
{
	LOG_HIHOOK;
	if (multiplayer_game || !SODSP_OPTIONS.rng)
		return THISCALL_1(void, h->GetDefaultFunc(), _this);
	return THISCALL_1(void, 0x50C7B0, _this);
}

/*
 *
 * This hook displays monoliths and subterranean gates in the world overview map.
 * The assets exist but no special case was made for them.
 *
 */
_LHF_(ShowPortalsGates)
{
	LOG_LOHOOK;
	DWORD type = ((H3MapItem*)(c->esi))->objectType;
	DWORD value;
	switch (type)
	{
	case NH3Objects::SUBTERRANEAN_GATE:
	case NH3Objects::MONOLITH_ONE_WAY_ENTRANCE:
	case NH3Objects::MONOLITH_TWO_WAY:
		c->Push(c->eax); // overwritten instruction @0x5F857F
		value = 3 + (type == NH3Objects::SUBTERRANEAN_GATE); // monoliths: 3rd frame; subterannean gate: 4th frame
		c->Push(value);
		break;
	default:
		return EXEC_DEFAULT;
	}
	c->return_address = 0x5F85FA;
	LOG_LOHOOK;
	return NO_EXEC_DEFAULT;
}

/*
 *
 * This hook adds commas to resources in textboxes when over 1000.
 * Several attempts were made using HiHooks, even with the SAFE_ subtype
 * but for some reason registers would not be properly maintained resulting
 * in crash some times (not always which is the strange part).
 *
 */
_LHF_(TextboxNumbersFormat)
{
	LOG_LOHOOK;
	INT32 number = IntAt(c->esp + 8);
	if (SODSP_OPTIONS.number_format && !multiplayer_game && number >= 1000)
	{
		H3String *text = (H3String*)IntAt(c->esp);
		text->Dereference();
		text->FormattedNumber(number);
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook adds commas to resources requested by Quests to the
 * Adventure map status bar.
 *
 */
_LHF_(QuestNumbersFormat)
{
	LOG_LOHOOK;
	INT32 number = IntAt(c->esp + 8);
	if (SODSP_OPTIONS.number_format && !multiplayer_game && abs(number) >= 1000)
	{
		H3String *text = (H3String*)IntAt(c->esp);
		text->Dereference();
		text->FormattedNumber(number);
		text->Append(' ');
		PCHAR resource = (PCHAR)PtrAt(c->esp + 0xC);
		text->Append(resource, strlen(resource));
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook will make the monster stats dialog remain open in combat when right-clicking,
 * but only on opposing creatures.
 *
 */
void __stdcall _HH_CombatRmbTextbox(HiHook *h, H3CombatManager *This, H3CombatMonster *mon, BOOL isRightClick)
{
	LOG_HIHOOK;
	BOOL newValue = isRightClick;
	if (!multiplayer_game && SODSP_OPTIONS.rmb_textbox)
	{
		if (!This->isHuman[mon->side]) // not your creature, since you can left-click your own
			newValue = 0;
	}
	THISCALL_3(void, h->GetDefaultFunc(), This, mon, newValue);
	LOG_HIHOOK;
}

/*
 *
 * This hook performs some calculations on non-damage spells that
 * are not normally done when right-clicking in the spellbook.
 *
 */
_LHF_(SpellbookTextCalculations)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.spell_details) {
		switch (c->arg_n(2))
		{
		case H3Spell::SUMMON_BOAT:
		case H3Spell::SCUTTLE_BOAT:
		case H3Spell::VIEW_EARTH:
		case H3Spell::DISGUISE:
		case H3Spell::VIEW_AIR:
		case H3Spell::FORCE_FIELD:
		case H3Spell::QUICK_SAND:
		case H3Spell::EARTHQUAKE:
		case H3Spell::DISPEL:
		case H3Spell::CURSE:
		case H3Spell::FRENZY:
		case H3Spell::COUNTERSTRIKE:
		case H3Spell::BERSERK:
		case H3Spell::FORGETFULNESS:
		case H3Spell::TELEPORT:
		case H3Spell::REMOVE_OBSTACLE:
		case H3Spell::CLONE:
		case H3Spell::ANTI_MAGIC:
		case H3Spell::BLESS:
		case H3Spell::MAGIC_MIRROR:
		case H3Spell::BLIND:
			break;
		default:
			c->return_address = 0x59BFCA;
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
			break;
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook sets a global flag to allow @SpellbookTextOrbs, @SpellbookTextSorcery
 * to compute actual spell effects when inspecting the spellbook.
 *
 */
static DWORD spellDetails;
int __stdcall _HH_spellDetails_flag3(HiHook *h, H3Hero* This, int a1, int a2, int a3)
{
	LOG_HIHOOK;
	if (!multiplayer_game)
		spellDetails |= 1;

	int r = THISCALL_4(int, h->GetDefaultFunc(), This, a1, a2, a3);

	spellDetails &= ~1;
	LOG_HIHOOK;
	return r;
}

/*
 *
 * This hook prevents non-damage spells from being considered for extra
 * damage from elemental Orbs.
 *
 */
_LHF_(SpellbookTextOrbs)
{
	LOG_LOHOOK;
	if (!multiplayer_game && (spellDetails & 1) && SODSP_OPTIONS.spell_details)
	{
		switch (c->arg_n(1))
		{
		case H3Spell::LAND_MINE:
		case H3Spell::FIRE_WALL:
		case H3Spell::MAGIC_ARROW:
		case H3Spell::ICE_BOLT:
		case H3Spell::LIGHTNING_BOLT:
		case H3Spell::IMPLOSION:
		case H3Spell::CHAIN_LIGHTNING:
		case H3Spell::FROST_RING:
		case H3Spell::FIREBALL:
		case H3Spell::INFERNO:
		case H3Spell::METEOR_SHOWER:
		case H3Spell::DEATH_RIPPLE:
		case H3Spell::DESTROY_UNDEAD:
		case H3Spell::ARMAGEDDON:
		case H3Spell::TITANS_LIGHTNING_BOLT:
		case H3Spell::FIRE_SHIELD:
			break;
		default:
			c->return_address = 0x4E5B1E;
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents non-damage spells from being considered for extra
 * damage from Sorcery skill.
 *
 */
_LHF_(SpellbookTextSorcery)
{
	LOG_LOHOOK;
	if (!multiplayer_game && (spellDetails & 1) && SODSP_OPTIONS.spell_details)
	{
		switch (c->arg_n(1))
		{
		case H3Spell::LAND_MINE:
		case H3Spell::FIRE_WALL:
		case H3Spell::MAGIC_ARROW:
		case H3Spell::ICE_BOLT:
		case H3Spell::LIGHTNING_BOLT:
		case H3Spell::IMPLOSION:
		case H3Spell::CHAIN_LIGHTNING:
		case H3Spell::FROST_RING:
		case H3Spell::FIREBALL:
		case H3Spell::INFERNO:
		case H3Spell::METEOR_SHOWER:
		case H3Spell::DEATH_RIPPLE:
		case H3Spell::DESTROY_UNDEAD:
		case H3Spell::ARMAGEDDON:
		case H3Spell::FIRE_SHIELD:
		case H3Spell::TITANS_LIGHTNING_BOLT:
			break;
		default:
			*(BYTE*)(&c->eax) = (BYTE)0;
			break;
		}
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook sets a global flag to allow @SpellbookTextValues, @SpellbookTextCases
 * to use corresponding text when inspecting the spellbook.
 *
 */
int __stdcall _HH_spellDetails_flag4(HiHook *h, int This, int a1, int a2, int a3, int a4)
{
	LOG_HIHOOK;
	if (!multiplayer_game)
		spellDetails |= 2;

	int r = THISCALL_5(int, h->GetDefaultFunc(), This, a1, a2, a3, a4);

	spellDetails &= ~2;
	LOG_HIHOOK;
	return r;
}

/*
 *
 * This hook gets the numerical value associated to specific spells
 * when inspecting the spellbook.
 *
 */
_LHF_(SpellbookTextValues)
{
	LOG_LOHOOK;
	if (!multiplayer_game && (spellDetails & 2) && SODSP_OPTIONS.spell_details)
	{
		H3Hero *hero = (H3Hero*)(c->arg_n(3));
		UINT spell_id = c->arg_n(2);
		UINT spell_expertise = PtrAt(c->ebp - 0x10);
		BYTE hero_id = hero->id;

		INT8 spell_power = hero->GetHeroPrimary(NH3Skills::SPELL_POWER);

		switch (spell_id)
		{
		case H3Spell::AIR_ELEMENTAL:
		case H3Spell::EARTH_ELEMENTAL:
		case H3Spell::FIRE_ELEMENTAL:
		case H3Spell::WATER_ELEMENTAL:
		case H3Spell::VISIONS:
			c->eax *= spell_power;
			break;
		case H3Spell::TOWN_PORTAL:
			c->eax = spell_expertise == 3 ? 200 : 300;
			break;
		case H3Spell::MAGIC_ARROW:
			if (hero_id == NH3Heroes::CIELE)  // for custom specialities, hero_specialty == Specialist_Magic_Arrow
				c->eax += c->eax / 2;
			break;
		case H3Spell::FIRE_WALL:
			if (hero_id == NH3Heroes::LUNA)  // for custom specialities, hero_specialty == Specialist_Fire_Wall
				c->eax += c->eax;
			break;
		case H3Spell::DISRUPTING_RAY:
			if (hero_id == NH3Heroes::AENAIN)  // for custom specialities, hero_specialty == Specialist_Disrupting_ray
				c->eax += 2;
			break;
		case H3Spell::STONE_SKIN:
			if (hero_id == NH3Heroes::DARKSTORN || hero_id == NH3Heroes::LABETHA || hero_id == NH3Heroes::MERIST || hero_id == NH3Heroes::XSI)
				c->eax += 3;
			break;
		case H3Spell::SHIELD:
		case H3Spell::AIR_SHIELD:
		case H3Spell::PROTECTION_FROM_AIR:
		case H3Spell::PROTECTION_FROM_FIRE:
		case H3Spell::PROTECTION_FROM_WATER:
		case H3Spell::PROTECTION_FROM_EARTH:
		case H3Spell::SLOW:
			c->eax = 100 - c->eax;
			break;
		case H3Spell::DIMENSION_DOOR:
			c->eax = spell_expertise == 3 ? 200 : 300;
		default:
			break;
		}
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook gets the relevant text to use with specific spells
 * when inspecting the spellbook.
 *
 */
_LHF_(SpellbookTextCases)
{
	LOG_LOHOOK;
	if (!multiplayer_game && (spellDetails & 2) && SODSP_OPTIONS.spell_details)
	{
		UINT spell_value = PtrAt(c->esp + 8);
		switch (c->arg_n(2))
		{
		case H3Spell::AIR_ELEMENTAL:
		case H3Spell::EARTH_ELEMENTAL:
		case H3Spell::FIRE_ELEMENTAL:
		case H3Spell::WATER_ELEMENTAL:
			sprintf(h3_TextBuffer, SP_SpellText->Elementals(), spell_value);
			break;
		case H3Spell::CURE:
			sprintf(h3_TextBuffer, SP_SpellText->Cure(), spell_value);
			break;
		case H3Spell::HYPNOTIZE:
			sprintf(h3_TextBuffer, SP_SpellText->Hypnotize(), spell_value);
			break;
		case H3Spell::RESURRECTION:
		case H3Spell::ANIMATE_DEAD:
			sprintf(h3_TextBuffer, SP_SpellText->Resurrection(), spell_value);
			break;
		case H3Spell::VISIONS:
			sprintf(h3_TextBuffer, SP_SpellText->Visions(), spell_value);
			break;
		case H3Spell::FLY:
		case H3Spell::WATER_WALK:
			sprintf(h3_TextBuffer, SP_SpellText->FlyWW(), spell_value);
			break;
		case H3Spell::BLOODLUST:
		case H3Spell::PRECISION:
		case H3Spell::STONE_SKIN:
		case H3Spell::PRAYER:
		case H3Spell::MIRTH:
		case H3Spell::FORTUNE:
		case H3Spell::HASTE:
		case H3Spell::SLAYER:
			sprintf(h3_TextBuffer, SP_SpellText->Increase(), spell_value);
			break;
		case H3Spell::WEAKNESS:
		case H3Spell::DISRUPTING_RAY:
		case H3Spell::SORROW:
		case H3Spell::MISFORTUNE:
			sprintf(h3_TextBuffer, SP_SpellText->Reduce(), spell_value);
			break;
		case H3Spell::SLOW:
		case H3Spell::SHIELD:
		case H3Spell::AIR_SHIELD:
		case H3Spell::PROTECTION_FROM_AIR:
		case H3Spell::PROTECTION_FROM_FIRE:
		case H3Spell::PROTECTION_FROM_WATER:
		case H3Spell::PROTECTION_FROM_EARTH:
			sprintf(h3_TextBuffer, SP_SpellText->ReducePerc(), spell_value);
			break;
		case H3Spell::DIMENSION_DOOR:
		case H3Spell::TOWN_PORTAL:
			sprintf(h3_TextBuffer, SP_SpellText->DDTP(), spell_value);
			break;
		case H3Spell::SACRIFICE:
			sprintf(h3_TextBuffer, SP_SpellText->Sacrifice(), spell_value);
			break;
		case H3Spell::FIRE_SHIELD:
			sprintf(h3_TextBuffer, SP_SpellText->FireShield(), spell_value);
			break;
		default:
			break;
		}
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook corrects the placement of the shadow for Forcefield spell.
 *
 */
_LHF_(ForcefieldShadow)
{
	LOG_LOHOOK;
	if (!multiplayer_game && P_CombatMgr->actionParameter == H3Spell::FORCE_FIELD)
		c->ebx = 0; // forcefield middle hex is always on the right
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook adds commas to player resources on the Adventure map status bar.
 * If the number of resources is too large, then Thousands and Millions are used
 * to show a visible approximation.
 *
 */
_LHF_(ShowPlayerResources)
{
	LOG_LOHOOK;
	INT32 resource = IntAt(c->esp + 8);
	if (!multiplayer_game && SODSP_OPTIONS.number_format && resource >= 1000)
	{
		if (resource < 1000000)  // greater/equal one thousand
			sprintf(h3_TextBuffer, "%d,%03d", (resource / 1000) % 1000, resource % 1000);
		else if (resource < 100000000)  // greater/equal one million
			sprintf(h3_TextBuffer, "%d,%03d{k}", (resource / 1000000) % 1000, (resource / 1000) % 1000);
		else if (resource < 1000000000)  // greater/equal 100 million
			sprintf(h3_TextBuffer, "%d{M}", (resource / 1000000) % 1000);
		else // greater/equal one billion
			sprintf(h3_TextBuffer, "%d,%03d{M}", (resource / 1000000000) % 1000, (resource / 1000000) % 1000);
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook hides Clones and Summons deaths from the combat result dialog.
 *
 */
_LHF_(HideCloneSummonDeaths)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.real_kills)
	{
		H3CombatMonster *mon = (H3CombatMonster*)(c->eax - 0x60);
		if (mon->IsClone() || mon->IsSummon())
		{
			c->return_address = 0x470958;
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook shows killed creatures above 9999 in Thousands instead
 * in the combat result dialog.
 *
 */
_LHF_(AbbreviateKilledCount)
{
	LOG_LOHOOK;
	INT32 count = IntAt(c->esp + 8);
	if (count > 9999)
	{
		IntAt(c->esp + 8) = count / 1000;
		IntAt(c->esp + 4) = (int)"%dk";
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////
// Show details on creature hover
////////////////////////////////////////////////////////////////////////////////////
static INT32 min_damage, max_damage;
/*
 *
 * This hook collects the calculated min and max damages.
 * Also doubles damage for double-attack creatures, idea by as239
 *
 */
_LHF_(GetDamage)
{
	LOG_LOHOOK;

	H3CombatMonster *ourMon = (H3CombatMonster *)c->esi;
	if (ourMon->info.flags.DOUBLEATTACK)
	{

		if ((P_CombatMgr->move_type == H3MouseManager::BFC_Shooting || P_CombatMgr->move_type == H3MouseManager::BFC_Half_Damage)) // if ranged, double min damage
			c->edi += c->edi;
		c->eax += c->eax; // always double max damage, it's technically possible
		// ballista and arrow turrets?
	}
	max_damage = c->eax;
	min_damage = c->edi;

	return EXEC_DEFAULT;
}

/*
 *
 * Structure to compare creatures' move order.
 * Some fields aren't absolutely required as they could be calculated during
 * sorting but having them all already calculated in advance reduces the number of
 * instructions to be done during sorting.
 *
 */
struct CrQueue {
	H3CombatMonster *creature; // needed to get active creature
	UINT32 struct_position; // there are 42 creature structures available in combat manager, #s 0,1,2,...,41
	UINT32 speed; // speed of creature in this slot
	UINT32 side; // 0 = left side, 1 = right side
	UINT32 cannot_move; // dead, paralyzed, stoned, blinded, speed = 0 (ignore war machines and turrets for now)
	UINT32 morale; // creature had morale this turn
	UINT32 waiting; // creature is waiting
	UINT32 category; // which of the 4 categories of battle sequence this creature belongs to (main phase, wait+morale phase, wait phase, done phase)
};

/*
 *
 * This function is used with qsort to perform sorting along CrQueue parameters.
 *
 */
int compare_queue(const void *q1, const void *q2)
{
	const struct CrQueue *c1 = (CrQueue*)q1;
	const struct CrQueue *c2 = (CrQueue*)q2;
	// different category
	if (c1->category != c2->category) // lower category first
		return c1->category - c2->category;
	// same speed, same category
	if (c1->speed == c2->speed) // lower position first
		return c1->struct_position - c2->struct_position;
	// same category, not the same speed
	if (c1->category == 2 || c1->category == 5) // sort descending during initial phase or for next turn
		return c2->speed - c1->speed;
	// same category, not the same speed
	if (c1->category == 3 || c1->category == 4) // sort ascending during wait phases
		return c1->speed - c2->speed;
	return 10;
}

/*
 *
 * This function populates an array of 42 digits to show creature's move order
 * based on their battlefield position.
 * e.g. [1, 0, 2, ...] means creature in position 0 gets to move second, position 1 moves 1st, etc.
 *
 */
void calculate_queue(UINT32 battle_sequence[42], H3CombatManager *combat)
{
	CrQueue queue[42]; // 2 * 21
	H3CombatMonster *active_creature = combat->activeStack;
	INT32 active_position;

	///////////////////////////////////////////////////////
	// populate queue
	///////////////////////////////////////////////////////
	for (INT32 j = 0; j < 2; j++)
	{
		for (INT32 i = 0; i < 21; i++)
		{
			CrQueue *q = &queue[i + 21 * j];
			q->creature = &combat->stacks[j][i];
			q->struct_position = i + 21 * j;
			q->speed = q->creature->GetStackSpeed();
			q->side = q->creature->side;
			q->morale = q->creature->HadMorale();
			q->waiting = q->creature->IsWaiting();
			q->cannot_move = 0;

			if (q->creature->activeSpellsDuration[H3Spell::STONE] > 0 ||
				q->creature->activeSpellsDuration[H3Spell::PARALYZE] > 0 ||
				q->creature->activeSpellsDuration[H3Spell::BLIND] > 0
				)
				q->cannot_move = 1;

			//////////////////////////////
			// 6 categories
			//////////////////////////////
			// 1 - active stack
			// 2 - has yet to move
			// 3 - got morale & waited
			// 4 - waited (no morale)
			// 5 - already moved - will be ignored for now; this is the default setting
			// 6 - cannot move - blinded, paralyzed, stoned, not a stack - this category should not show up.
			// 7 - dead / not existent

			q->category = 3; // default category
			if (q->creature->info.speed > 0 && q->cannot_move == 0) // the wait flag vanishes after the normal phase is over! But we can get it from combat phase
				q->category = max(2 - q->morale + 2 * (q->waiting + combat->waitPhase), 2);
			if (q->creature->IsDone())
				q->category = 5;
			if (q->speed == 0 || q->cannot_move)
				q->category = 6;
			if (!q->creature->numberAlive)
				q->category = 7;
			if (q->creature == active_creature)
			{
				active_position = q->struct_position;
				q->category = 1;
			}
		}
	}

	///////////////////////////////////////////////////////
	// initial sort of creatures: by category, then by speed & position
	///////////////////////////////////////////////////////
	qsort(queue, 42, sizeof(CrQueue), compare_queue);

	//////////////////////////////////////////////////////////////////
	// second sort of creatures: alternate sides for same speed
	//////////////////////////////////////////////////////////////////
	CrQueue tempInfo;
	CrQueue *fastestInfo;
	CrQueue *current;
	INT32 fastest_position;
	for (INT32 i = 1; i < 42; i++)
	{
		fastestInfo = &queue[i];
		fastest_position = i;

		for (INT32 j = i + 1; j < 42; j++)
		{
			current = &queue[j];
			// same category, same side, take the lower position
			if (fastestInfo->category == current->category
				&& fastestInfo->side == current->side
				&& fastestInfo->struct_position > current->struct_position
				&& fastestInfo->speed == current->speed
				)
			{
				fastestInfo = current;
				fastest_position = j;
			}
			// same category, same speed - alternate sides.
			if (fastestInfo->category == current->category
				&& fastestInfo->speed == current->speed
				&& fastestInfo->side == queue[i - 1].side
				&& fastestInfo->side != current->side
				)
			{
				fastestInfo = current;
				fastest_position = j;
			}
		}
		// swap the creature in the queue with the fastest found
		tempInfo = queue[i];
		queue[i] = *fastestInfo;
		queue[fastest_position] = tempInfo;
		battle_sequence[fastestInfo->struct_position] = i;
	}
}

/*
 *
 * This hook shows the number of kills when targetting an enemy as well as
 * the remaining hit points of top creature, its probable move order
 * and the coordinates under the mouse cursor in the status bar of combat dialog.
 *
 */
void __stdcall _HH_CombatStatus_ShowKills(HiHook *h, H3Dlg *This, PCHAR buffer, INT a2, INT a3)
{
	LOG_HIHOOK;

	H3CombatManager *combat = P_CombatMgr;
	H3CombatMonster *ourMon, *oppMon;
	INT32 mouseCoord = combat->mouse_coord;
	INT32 column = mouseCoord % 17;
	INT32 row = mouseCoord / 17 + 'A';
	CHAR new_text[128];
	new_text[0] = 0;
	if (!min_damage && !max_damage) // hovering over one of your own creatures or can't reach enemy
	{
		if ((ourMon = combat->squares[mouseCoord].GetMonster()) && column > 0 && column < 16 && row < (12 + 'A'))
		{
			INT32 maxHP = ourMon->info.hitPoints;
			INT32 lostHP = ourMon->healthLost;
			INT32 currentHP = maxHP - lostHP;

			if (SODSP_OPTIONS.creature_hp)
				sprintf(buffer, " {~%s}%d%s}", SODSP_COLOR.hit_points.String(), currentHP, SP_CombatText->HP());
			if (SODSP_OPTIONS.move_sequence) // show creature move order
			{
				UINT32 battle_sequence[42] = { 0 }; // for 42 creatures, which position will move next
				calculate_queue(battle_sequence, combat);
				_snprintf(new_text, 128, "%s [{~%s}%d}]", new_text, SODSP_COLOR.move_sequence.String(), battle_sequence[ourMon->Index()]);
			}
		}
		strcat(buffer, new_text);
	}

	if (max_damage || min_damage)
	{
		oppMon = combat->squares[mouseCoord].GetMonster();
		if (oppMon && column > 0 && column < 16 && row < (12 + 'A'))
		{
			INT32 maxHP = oppMon->info.hitPoints;
			INT32 lostHP = oppMon->healthLost;
			INT32 currentHP = maxHP - lostHP;
			INT32 numberCreatures = oppMon->numberAlive;
			INT32 minKills = 0, maxKills = 0;
			if (min_damage >= currentHP)
			{
				minKills++;
				min_damage -= currentHP;
			}
			if (min_damage > 0)
				minKills += min_damage / maxHP;
			if (max_damage >= currentHP)
			{
				maxKills++;
				max_damage -= currentHP;
			}
			if (max_damage > 0)
				maxKills += max_damage / maxHP;

			if (minKills >= numberCreatures)
				minKills = maxKills = numberCreatures;

			// kill same amount
			if (minKills == maxKills)
			{
				if (minKills >= numberCreatures)
					_snprintf(new_text, 128, ", {~%s}%s %d})", SODSP_COLOR.kill_all.String(), SP_CombatText->Kills(), numberCreatures); // will kill all, print kills in green or user choice
				else  // not all creatures
					_snprintf(new_text, 128, ", {%s} {~%s}%d})", SP_CombatText->Kills(), SODSP_COLOR.kill_some.String(), minKills); // will not kill all, print kills in red or user choice
			}
			else // kill different amount
			{
				if (maxKills < numberCreatures) // cannot kill all
					_snprintf(new_text, 128, ", {%s} {~%s}%d} {%s} {~%s}%d})", SP_CombatText->Kills(), SODSP_COLOR.kill_some.String(), minKills, SP_CombatText->To(), SODSP_COLOR.kill_some.String(), maxKills);
				else // maxKills slays all, but not minKills
					_snprintf(new_text, 128, ", {%s} {~%s}%d} {%s} {~%s}%d})", SP_CombatText->Kills(), SODSP_COLOR.kill_some.String(), minKills, SP_CombatText->To(), SODSP_COLOR.kill_all.String(), numberCreatures);
			}

			if (SODSP_OPTIONS.creature_hp) // show creature remaining hp
				_snprintf(new_text, 128, "%s {~%s}%d%s}", new_text, SODSP_COLOR.hit_points.String(), currentHP, SP_CombatText->HP());

			if (SODSP_OPTIONS.move_sequence) // show creature move order
			{
				UINT32 battle_sequence[42] = { 0 }; // for 42 creatures, which position will move next
				calculate_queue(battle_sequence, combat);
				_snprintf(new_text, 128, "%s [{~%s}%d}]", new_text, SODSP_COLOR.move_sequence.String(), battle_sequence[oppMon->Index()]);
			}
			PCHAR b = buffer;

			while (*b) // set new end at ')'
			{
				if (*b == ')')
				{
					*b = 0;
					break;
				}
				b++;
			}

			strcat(b, new_text); // add #kills text to original text
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// Shows battle coordinates from A1 to K15
	/////////////////////////////////////////////////////////////////////////////
	if (SODSP_OPTIONS.comb_coordinates)
	{
		CHAR coordText[64];
		if (column > 0 && column < 16 && row < (12 + 'A'))  // we don't care about off-grid coordinates
		{
			INT32 attackingCoordinates = combat->attacker_coord;
			INT32 attackerColumn, attackerRow;
			if (combat->move_type == 7)  // melee attack, show destination of attacker as well as defender's location
			{
				if (combat->activeStack->info.flags.DOUBLE_WIDE)
					attackingCoordinates += (combat->currentActiveSide == 0) ? 1 : -1;
				attackerColumn = attackingCoordinates % 17;
				attackerRow = attackingCoordinates / 17 + 'A';
				_snprintf(coordText, 64, " {~%s}(%c%d—%c%d)}", SODSP_COLOR.battle_coordinates.String(), (CHAR)attackerRow, attackerColumn, (CHAR)row, column);
			}
			else
				_snprintf(coordText, 64, " {~%s}(%c%d)}", SODSP_COLOR.battle_coordinates.String(), (CHAR)row, column);

			strcat(buffer, coordText);
		}
	}

	min_damage = 0;
	max_damage = 0;

	LOG_HIHOOK;
	THISCALL_4(void, h->GetDefaultFunc(), This, buffer, a2, a3);
}

/*
 *
 * This hook shows the effect of some spells as well as current mouse coordinates in the combat status bar.
 * Not a HiHook as data needs to be collected from the stack.
 *
 */
_LHF_(BattleSpellText)
{
	LOG_LOHOOK;
	if (!multiplayer_game)
	{
		int spell_id = c->arg_n(1);
		int coordinates = c->arg_n(2);
		H3CombatManager *combat = P_CombatMgr;
		H3CombatMonster *targetMon;
		if (spell_id == H3Spell::RESURRECTION)
			targetMon = combat->GetResurrectionTarget(coordinates);
		else if (spell_id == H3Spell::ANIMATE_DEAD)
			targetMon = combat->GetAnimateDeadTarget(coordinates);
		else
			targetMon = ((H3CombatSquare*)c->edi)->GetMonster();
		if (targetMon)
		{
			H3Hero *ourHero, *enemyHero;
			INT32 spellPower;

			int side = combat->currentActiveSide;
			ourHero = combat->hero[side];
			enemyHero = combat->hero[1 - side];
			spellPower = combat->heroSpellPower[side];

			INT32 spellExpertise = ourHero->GetSpellExpertise(spell_id, combat->specialTerrain);
			INT32 baseDamage = P_Spell[spell_id].GetBaseEffect(spellExpertise, spellPower);
			INT32 numberCreatures = 0;
			INT32 deadCreatures;
			INT32 maxHP, lostHP, currentHP;
			INT32 damage, realDamage;
			maxHP = targetMon->info.hitPoints;
			lostHP = targetMon->healthLost;
			currentHP = maxHP - lostHP;

			switch (spell_id)
			{
			case H3Spell::ICE_BOLT:
			case H3Spell::IMPLOSION:
			case H3Spell::MAGIC_ARROW:
			case H3Spell::LIGHTNING_BOLT:
			case H3Spell::TITANS_LIGHTNING_BOLT:
				damage = realDamage = ourHero->GetRealSpellDamage(baseDamage, targetMon, spell_id, enemyHero);
				if (damage >= currentHP)
				{
					numberCreatures++;
					damage -= currentHP;
				}
				if (damage > 0)
					numberCreatures += damage / maxHP;

				if (numberCreatures < targetMon->numberAlive)
					_snprintf(h3_TextBuffer, 200, "%s (%d %s, {%s:} {~%s}%d})", h3_TextBuffer, realDamage, SP_CombatText->Damage(), SP_CombatText->Kills(), SODSP_COLOR.kill_some.String(), numberCreatures);
				else
					_snprintf(h3_TextBuffer, 200, "%s (%d %s, {~%s}%s: %d})", h3_TextBuffer, realDamage, SP_CombatText->Damage(), SODSP_COLOR.kill_all.String(), SP_CombatText->Kills(), targetMon->numberAlive);
				break;
			case H3Spell::RESURRECTION:
			case H3Spell::ANIMATE_DEAD:
				damage = ourHero->GetSpellSpecialtyEffect(spell_id, targetMon->info.level, baseDamage);
				realDamage = damage + baseDamage;
				numberCreatures = 1 + (realDamage - lostHP) / maxHP;
				deadCreatures = targetMon->numberAtStart - targetMon->numberAlive;
				if (numberCreatures < deadCreatures)
					sprintf(h3_TextBuffer, "%s (%d %s, {%s:} {~%s}%d})", h3_TextBuffer, realDamage, SP_CombatText->ResurrectHP(), SP_CombatText->Raises(), SODSP_COLOR.kill_some.String(), numberCreatures);
				else
					sprintf(h3_TextBuffer, "%s (%d %s, {~%s}%s: %d})", h3_TextBuffer, realDamage, SP_CombatText->ResurrectHP(), SODSP_COLOR.kill_all.String(), SP_CombatText->Raises(), deadCreatures);
				break;
			case H3Spell::CURE:
				damage = ourHero->GetSpellSpecialtyEffect(spell_id, targetMon->info.level, baseDamage);
				realDamage = damage + baseDamage;
				if (realDamage > lostHP)
					sprintf(h3_TextBuffer, "%s ({~%s}%d %s})", h3_TextBuffer, SODSP_COLOR.kill_all.String(), lostHP, SP_CombatText->ResurrectHP());
				else
					sprintf(h3_TextBuffer, "%s ({~%s}%d %s})", h3_TextBuffer, SODSP_COLOR.kill_some.String(), realDamage, SP_CombatText->ResurrectHP());
				break;
			default:
				break;
			}

			///////////////////////////////////////////////
			// Show coordinates
			///////////////////////////////////////////////
			if (SODSP_OPTIONS.comb_coordinates)
			{
				INT32 column = coordinates % 17;
				INT32 row = coordinates / 17 + 'A';
				if (column && column < 16 && row < (12 + 'A'))
					sprintf(h3_TextBuffer, "%s {~%s}(%c%d)}", h3_TextBuffer, SODSP_COLOR.battle_coordinates.String(), row, column);
			}

		}
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook shows the current mouse coordinates when teleport spell is active.
 *
 */
_LHF_(TeleportText)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.comb_coordinates)
	{
		DWORD coordinate = c->arg_n(2);
		char battle_row = (char)(coordinate / 17 + 'A');
		int battle_column = coordinate % 17;
		sprintf(h3_TextBuffer, "%s {~%s}(%c%d)}", (PCHAR)c->ecx, SODSP_COLOR.battle_coordinates.String(), battle_row, battle_column);
		c->ecx = (int)h3_TextBuffer;
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////
// Faster spell animation
////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * This hook sets a flag to trigger turbo spell animation.
 * Used for @FastSpells and @FastSpells2
 *
 */
static BOOL fastSpells;
void __stdcall _HH_fastSpells_flag(HiHook *h, int This, int a1, int a2, int a3, int a4, int a5, int a6)
{
	if (!multiplayer_game)
		fastSpells = TRUE;
	THISCALL_7(void, h->GetDefaultFunc(), This, a1, a2, a3, a4, a5, a6);
	fastSpells = FALSE;
}

/*
 *
 * This hook speeds up spell animations in GDI mode.
 *
 */
_LHF_(FastSpells)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.turbo_animation && fastSpells)
	{
		switch (h3_CurrentAnimationSpeed)
		{
		case 1: // reduce duration by half
			if (c->eax == 4)
			{
				LOG_LOHOOK;
				return NO_EXEC_DEFAULT;
			}
			break;
		case 2: // instantaneous
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		default: // normal duration
			LOG_LOHOOK;
			return EXEC_DEFAULT;
		}
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook speeds up spell animations in True mode.
 *
 */
_LHF_(FastSpells2)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.turbo_animation && P_CombatMgr->action == H3CombatManager::BA_CAST_SPELL)
	{
		switch (h3_CurrentAnimationSpeed)
		{
		case 1: // cut by half
			if (c->esi == 3)
			{
				LOG_LOHOOK;
				return NO_EXEC_DEFAULT;
			}
			break;
		case 2: // instantaneous
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		default: // normal
			LOG_LOHOOK;
			return EXEC_DEFAULT;
		}
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This function searches through HD_MCR.dll to place @FastSpells2 hook.
 *
 */
void place_fast_spells2_hook(PatcherInstance *pi)
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	// fast_spells_2: 8B 5D 0C 89 44 .. 24 54
	///////////////////////////////////////////////////////////////////////////////////////////////
	UINT8 needle_fast_spells_2[] = {
		0x8B, 0x5D, 0x0C,						// MOV EBX, DWORD PTR SS: [EBP + 0C]
		0x89, 0x44/*, 0x24, 0x54*/				// MOV DWOD PTR SS [ESP+54], EAX
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Expected opcode: 0F 8F .. 7C FE FF FF
	///////////////////////////////////////////////////////////////////////////////////////////////
	UINT8 expected_code[] = {
		0x0F, 0x8F /* 0x7C, 0xFE, 0xFF, 0xFF */	// JG [some address prior]
	};
	INT32 radius = 0x50;
	DWORD address = HD_MCR_DLL.NeedleSearchAround(needle_fast_spells_2, sizeof(needle_fast_spells_2), radius, expected_code, sizeof(expected_code));
	if (address)
		pi->WriteLoHook(address, FastSpells2);

}

////////////////////////////////////////////////////////////////////////////////////
// Fix high level experience for cheats and Tree of Knowledge
////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * This hook sets a flag to activate hook @FixExperience when nwcneo cheat is used.
 * $gameStart_flag is defined in overflow.cpp, and recycled here as it pertains to experience.
 *
 */
int __stdcall _HH_Cheat_flag(HiHook *h, int _this, int a1, int a2, int a3) // 0x004025F5
{
	gameStart_flag = 2;
	LOG_HIHOOK;

	int r = THISCALL_4(int, h->GetDefaultFunc(), _this, a1, a2, a3);

	gameStart_flag = 0;
	LOG_HIHOOK;
	return r;
}

/*
 *
 * This hook sets a flag to activate hook @FixExperience when visiting Tree of Knowledge.
 * $gameStart_flag is defined in overflow.cpp, and recycled here as it pertains to experience.
 *
 */
int __stdcall _HH_TreeKnowledge_flag(HiHook *h, int _this, int a1, int a2, int a3) // 0x4A65FF
{
	gameStart_flag = 3;
	LOG_HIHOOK;
	int r = THISCALL_4(int, h->GetDefaultFunc(), _this, a1, a2, a3);

	gameStart_flag = 0;
	LOG_HIHOOK;
	return r;
}

// disable warning due to negative experience definition
#pragma warning(disable:4146)

/*
 *
 * This hook allows fast leveling to the higher experience levels (868+)
 * It assumes primary skill overflow is active.
 *
 */
_LHF_(FixExperience)
{
	LOG_LOHOOK;
	INT32 experience, hero_level;
	experience = c->ecx; // the hero's total experience after the gained ~ not yet applied to hero

	if (gameStart_flag == 1) // game start
	{
		LOG_LOHOOK;
		return EXEC_DEFAULT;
	}

	H3Hero *hero = (H3Hero*)c->edi;
	hero_level = hero->level;

	// logic for gaining experience normally
	if (gameStart_flag != 3 && gameStart_flag != 2)
	{
		// don't change logic if we're not going to level 868.
		if (experience < NH3Levels::LEVEL_868)
		{
			LOG_LOHOOK;
			return EXEC_DEFAULT;
		}
		int skills_left_to_learn = hero->SSkillsLeftToLearn();

		if (hero_level < 868 && experience >= NH3Levels::LEVEL_868 && experience < NH3Levels::LEVEL_3732)
		{
			hero->level = 867 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
		}
		else if (hero_level < 3732 && experience >= NH3Levels::LEVEL_3732 && experience < NH3Levels::LEVEL_5920)
		{
			hero->level = 3731 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
		}
		else if (hero_level < 5920 && experience >= NH3Levels::LEVEL_5920 && experience < NH3Levels::LEVEL_6424)
		{
			hero->level = 5919 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
		}
		else if (hero_level < 6424 && experience >= NH3Levels::LEVEL_6424 && experience < NH3Levels::LEVEL_MAX)
		{
			hero->level = 6423 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
		}
		else if (experience >= NH3Levels::LEVEL_MAX && experience <= 0) // infinite level-ups -> send hero to level 0
		{
			hero->level = -1 - skills_left_to_learn; // one level before 0 ...
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
			c->ecx = 0; // also need to update exp to a stable count
		}
	}

	// tree of knowledge!!!
	// normally experience overflows out of bounds
	// so let's control it instead
	// will not level you up after level 100
	else if (gameStart_flag == 3)
	{
		int skills_left_to_learn = hero->SSkillsLeftToLearn();
		switch (hero_level)
		{
		case 0:
			c->ecx = NH3Levels::LEVEL_1;
			break;
		case 74:
			c->ecx = NH3Levels::LEVEL_88;
			break;
		case 88:
			c->ecx = NH3Levels::LEVEL_100;
			break;
		case 100:
		case 108:
		case 868:
		case 3732:
		case 5920:
		case 6424:
			c->ecx = hero->experience;
			break;
		default:
			break;
		}
	}

	// cheat!!
	// no limits
	else
	{
		int skills_left_to_learn = hero->SSkillsLeftToLearn();
		switch (hero_level)
		{
		case 0:
			c->ecx = NH3Levels::LEVEL_1;
			break;
		case 74:
			c->ecx = NH3Levels::LEVEL_88;
			break;
		case 88:
			c->ecx = NH3Levels::LEVEL_100;
			break;
		case 100:
			c->ecx = NH3Levels::LEVEL_108;
			break;
		case 108:
			c->ecx = NH3Levels::LEVEL_868;
			hero->level = 867 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
			break;
		case 868:
			c->ecx = NH3Levels::LEVEL_3732;
			hero->level = 3731 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
			break;
		case 3732:
			c->ecx = NH3Levels::LEVEL_5920;
			hero->level = 5919 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
			break;
		case 5920:
			c->ecx = NH3Levels::LEVEL_6424;
			hero->level = 6423 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
			break;
		case 6424:
			c->ecx = 0;
			hero->level = -1 - skills_left_to_learn; // bring hero to 1 level before final level-up
			hero->primarySkill[0] = 127; // all stats should be maxed up ~ can be revised if you don't have primary overflow fix
			hero->primarySkill[1] = 127;
			hero->primarySkill[2] = 127;
			hero->primarySkill[3] = 127;
			break;
		}
	}
	LOG_LOHOOK
		return EXEC_DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////
// unFix berserk
////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * These hooks restore AI behavior under the Berserk spell which was altered by HD+.
 *
 */
static naked_t bridge_berserk1;
static naked_t return_berserk1a = (naked_t)0x4B3537;
static naked_t return_berserk1b = (naked_t)0x4B3724;
static naked_t return_berserk2a = (naked_t)0x4B37AA;
static naked_t return_berserk2b = (naked_t)0x4B37BF;
static naked_t bridge_berserk3;
static naked_t return_berserk3 = (naked_t)0x422447;

naked_function AIberserk1(void)
{
	__asm PUSHFD
	__asm PUSHAD
	if (!multiplayer_game && SODSP_OPTIONS.berserk)
	{
		__asm POPAD
		__asm POPFD
		__asm TEST DL, DL
		__asm JNE jump_out
		__asm JMP return_berserk1a
		jump_out :
				 __asm JMP return_berserk1b
	}
	__asm POPAD
	__asm POPFD
	__asm JMP bridge_berserk1
}

naked_function AIberserk2(void)
{
	__asm PUSHFD
	__asm PUSHAD
	if (!multiplayer_game && SODSP_OPTIONS.berserk)
	{
		__asm POPAD
		__asm POPFD
		__asm MOV ECX, DWORD PTR SS : [EBP + 0x14]
			__asm MOV EAX, DWORD PTR SS : [EBP - 0x0C]
			__asm MOV EDX, DWORD PTR DS : [ECX + 4]
			__asm AND EAX, 0x0F
		__asm SHL EAX, 0x0C
		__asm AND DH, 0x0F
		__asm OR EAX, EDX
		__asm LEA EDX, [EBP + 0x14]
			__asm MOV DWORD PTR DS : [ECX + 0x0E], EAX
		__asm MOV EAX, DWORD PTR SS : [EBP + 0x14]
			__asm JMP return_berserk2b
	}
	__asm POPAD
	__asm POPFD
	__asm JMP return_berserk2a
}

naked_function AIberserk3(void)
{
	__asm PUSHFD
	__asm PUSHAD
	if (!multiplayer_game && SODSP_OPTIONS.berserk)
	{
		__asm POPAD
		__asm POPFD
		__asm PUSH EBP
		__asm MOV EBP, ESP
		__asm PUSH EBX
		__asm MOV EBX, DWORD PTR SS : [EBP + 0x0C]
			__asm JMP return_berserk3
	}
	__asm POPAD
	__asm POPFD
	__asm JMP bridge_berserk3
}

/*
 *
 * This function checks if Berserk behavior needs to be restored
 * and applies hooks as necessary.
 *
 */
void RestoreBerserk()
{
	if (ByteAt(0x4B352F) == mnemonics::jmp)
	{
		bridge_berserk1 = (naked_t)FuncAt(0x4B352F);
		H3Patcher::NakedHook5(0x4B352F, AIberserk1);
	}
	if (PtrAt(0x4B37A5) == 0x90909090)
		H3Patcher::NakedHook5(0x4B37A5, AIberserk2);
	if (ByteAt(0x422440) == mnemonics::jmp)
	{
		bridge_berserk3 = (naked_t)FuncAt(0x422440);
		H3Patcher::NakedHook5(0x422440, AIberserk3);
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Hex Patches
////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * Developed by AlexSpl, with minimal contribution from RoseKavalier.
 * These patches enable the use of 65,535 objects in Heroes 3
 * instead of 32,767.
 *
 */
void MoreObjectsPatch_by_AlexSpl(PatcherInstance *pi)
{
	pi->WriteByte(0x49C020 + 1, 0xB7);	// movsx		to		movzx
	pi->WriteByte(0x4A763E + 1, 0xB7);	// movsx		to		movzx
	pi->WriteByte(0x4A9422 + 1, 0xB7);	// movsx		to		movzx
	pi->WriteByte(0x4AA82D + 1, 0xB7);	// movsx		to		movzx
	pi->WriteByte(0x4C9661 + 1, 0xB7);	// movsx		to		movzx

	pi->WriteWord(0x4FD12A, 0xBF0F);	// mov			to		movsx
	pi->WriteWord(0x4FD12E, 0xFF83);	// TEST DI,DI	to		CMP EDI, -1
	pi->WriteByte(0x4FD131 + 1, 0x84);	// JL			to		JE
	pi->WriteByte(0x4FD163 + 1, 0xB7);	// movsx		to		movzx

	pi->WriteWord(0x505C75, 0xBF0F);	// mov			to		movsx
	pi->WriteWord(0x505C79, 0x74FFFE83);// TEST SI,SI	to		CMP ESI, -1
										// JL			to		JE
	pi->WriteByte(0x505C9E + 1, 0xB7);	// movsx		to		movzx

	pi->WriteWord(0x52CD26, 0xBF0F);	// mov			to		movsx
	pi->WriteWord(0x52CD2A, 0xFF83);	// TEST DI,DI	to		CMP EDI, -1
	pi->WriteByte(0x52CD2D, 0x74);		// JL			to		JE
	pi->WriteByte(0x52CD35 + 1, 0xB7);	// movsx		to		movzx
}

/*
 *
 * This function reduces / restores the time required in between combat animations.
 * Not as direct as patching the equivalent DWORD value, but clear in its implementation.
 *
 */
void TurboPatch()
{
	union Flint
	{
		float f;
		UINT32 i;
	};

	Flint t;

	if (SODSP_OPTIONS.turbo_animation) // turbo values
	{
		t.f = 0.20f;
		DwordPatch(0x63CF7C, t.i);
		t.f = 0.10f;
		DwordPatch(0x63CF80, t.i);
		t.f = 0.05f;
		DwordPatch(0x63CF84, t.i);
	}
	else // normal values
	{
		t.f = 1.00f;
		DwordPatch(0x63CF7C, t.i);
		t.f = 0.63f;
		DwordPatch(0x63CF80, t.i);
		t.f = 0.40f;
		DwordPatch(0x63CF84, t.i);
	}
}

////////////////////////////////////////////////////////////////////////////////////
// More Seers
////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * This hook helps to randomly select the name of Seer Huts when there are over 48 of them.
 * In such a case, it replicates the existing code to take into account that the current
 * Seer Hut's id is greater than 48, then restores control to Heroes3 at a stage where
 * the id being greater than 48 matters not.
 *
 */
_LHF_(MoreSeerHuts)
{
	LOG_LOHOOK;
	H3Main *main = P_Main;
	int currentCount = main->mainSetup.seerHuts.Count();
	if (currentCount >= 48)
	{
		int newCount = currentCount % 48;
		BYTE *availNames = (BYTE*)c->esi;
		H3SeerHut *seer = &main->mainSetup.seerHuts.first[currentCount - newCount - 1];
		for (int i = 0; i < newCount; i++)
		{
			availNames[seer->seerNameId] = 0;
			seer++;
		}
		c->edi = (int)main;
		c->edx = newCount;
		c->return_address = 0x574DB3;
		LOG_LOHOOK;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook truncates the seer's id to within the bounds of existing Seer Hut names.
 *
 */
_LHF_(MoreSeerHuts2)
{
	LOG_LOHOOK;
	if (c->edi >= 48)
		c->edi %= 48;
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

void improvements_init(PatcherInstance * pi)
{
	//////////////////////////////////////////////////
	// RNG functions
	//////////////////////////////////////////////////
	pi->WriteHiHook(0x4C848E, CALL_, FASTCALL_, _HH_WeekOfTheRNG);
	pi->WriteHiHook(0x4AC2D6, CALL_, THISCALL_, _HH_CreatureSplit);
	pi->WriteHiHook(0x4ABBA9, CALL_, THISCALL_, _HH_creatureBankSeed);
	pi->WriteHiHook(0x4C8C1E, CALL_, FASTCALL_, _HH_MonthOfTheRng);
	pi->WriteLoHook(0x61842C, OriginalRng);
	pi->WriteLoHook(0x50C7C0, CombatObstacles);

	//////////////////////////////////////////////////
	// Show numbers formatted with commas
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x4F55F8, TextboxNumbersFormat);	// HiHook was more complicated than LoHook
	pi->WriteLoHook(0x571709, QuestNumbersFormat);		// HiHook was more complicated than LoHook

	//////////////////////////////////////////////////
	// Misc.
	//////////////////////////////////////////////////
	pi->WriteHiHook(0x476445, CALL_, THISCALL_, _HH_CombatRmbTextbox);
	pi->WriteLoHook(0x40D0DB, MapHintCoordinates);
	pi->WriteLoHook(0x5A36A5, ForcefieldShadow);
	MoreObjectsPatch_by_AlexSpl(pi);
	TurboPatch();
	pi->WriteJmp(0x5A365D, 0x5A3666); // Show & Hide Forcefield Shadow
	pi->WriteJmp(0x5A37B9, 0x5A37C2); // Show & Hide Forcefield Shadow
	pi->WriteLoHook(0x5591B9, ShowPlayerResources);
	pi->WriteLoHook(0x4708F7, HideCloneSummonDeaths);
	pi->WriteLoHook(0x470D82, AbbreviateKilledCount);

	//////////////////////////////
	// Faster spell animations
	//////////////////////////////
	pi->WriteHiHook(0x5A0140, SPLICE_, THISCALL_, _HH_fastSpells_flag); // all cases
	pi->WriteLoHook(0x6035E3, FastSpells); // fast spells when using GDI format
	place_fast_spells2_hook(pi);

	//////////////////////////////////////////////////
	// Faster leveling and no overflow
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x4E37B5, FixExperience);
	pi->WriteHiHook(0x4025F5, CALL_, THISCALL_, _HH_Cheat_flag);
	pi->WriteHiHook(0x4A65FF, CALL_, THISCALL_, _HH_TreeKnowledge_flag);

	//////////////////////////////////////////////////
	// Extended battle status messages
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x493053, GetDamage);
	pi->WriteHiHook(0x492E4F, CALL_, THISCALL_, _HH_CombatStatus_ShowKills);
	pi->WriteLoHook(0x5A8AD5, TeleportText); // show coordinates when teleporting
	pi->WriteLoHook(0x5A8BF9, BattleSpellText); // LoHook needed for previous function arguments

	//////////////////////////////////////////////////
	// Extended spell descriptions
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x59BFBE, SpellbookTextCalculations);
	pi->WriteHiHook(0x59BFFD, CALL_, THISCALL_, _HH_spellDetails_flag3); // set spell text flag for spellbook_text_orb && spellbook_text_sorcery
	pi->WriteLoHook(0x4E59F1, SpellbookTextOrbs);
	pi->WriteLoHook(0x4E5B24, SpellbookTextSorcery);
	pi->WriteHiHook(0x59D7B6, CALL_, THISCALL_, _HH_spellDetails_flag4); // set spell text flag for spellbook_text_values && spellbook_text_cases
	pi->WriteHiHook(0x59D3BA, CALL_, THISCALL_, _HH_spellDetails_flag4); // set spell text flag for spellbook_text_values && spellbook_text_cases
	pi->WriteLoHook(0x59C002, SpellbookTextValues);
	pi->WriteLoHook(0x59C01C, SpellbookTextCases);

	//////////////////////////////////////////////////
	// View World & View Air show portals and gates
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x5F857F, ShowPortalsGates);
	pi->WriteByte(0x5F854F, 0x62); // extend switch() up to Subterranean gate (103 - 5 = 98)
	pi->WriteByte(0x5F864E, 0); // monolith one way
	pi->WriteByte(0x5F8650, 0); // monolith two ways
	pi->WriteDword(0x5F8686, 0x05050505); // default ~ due to extended switch() values
	pi->WriteByte(0x5F868A, 0); // subterranean gate

	//////////////////////////////////////////////////
	// restore berserk behaviour
	//////////////////////////////////////////////////
	RestoreBerserk();

	///////////////////////////////////////////
	// More Seer Huts with repeated names
	///////////////////////////////////////////
	pi->WriteLoHook(0x574D5C, MoreSeerHuts); // pick random name
	pi->WriteLoHook(0x574DF2, MoreSeerHuts2); // don't divide by non-positive number
}