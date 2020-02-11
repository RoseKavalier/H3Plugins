#include "improvements.h"
#include "hotkeys.h"
#include "Global.h"
#include "SODSP_Files/Log.h"

using namespace h3;
using SODSP::GENERAL::_SODSP;

using SODSP::TEXT::TSpells;
using SODSP::TEXT::TCombat;
using SODSP::FEATURES::FOptions;
using SODSP::COLOR::ColorsStrings;
using SODSP::GENERAL::GGameFlags;

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
	if (!F_Multiplayer())
	{
		if ((FOptions.double_growth && FOptions.plague) // both options
			|| (FOptions.double_growth && r > 5 && r <= 9) // not plague, but set to double population
			|| (FOptions.plague && r == 10) // not double, but set to plague
			)
			r = 0;
	}
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
	if (!F_Multiplayer() && FOptions.weekly_growth)
		r = 0;
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
	if (F_Multiplayer() || !FOptions.obstacles)
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
	if (F_Multiplayer() || !FOptions.split)
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
	if (!F_Multiplayer() && FOptions.adventure_coordinates)
	{
		H3AdventureManager* adv = P_AdventureMgr;
		H3Position coord = adv->mousePosition;

		int size = adv->map->mapSize;

		int x, y, z;
		coord.GetXYZ(x, y, z);
		if (x >= size || y >= size)
			return EXEC_DEFAULT;

		////////////////////////
		// from v1_15
		///////////////////////
		ShowMovementCost(coord.Mixed(), x, y, z);

		F_sprintf("%s {~%s}(%d, %d, %d)}", h3_TextBuffer, ColorsStrings.adventure_coordinates.String(), x, y, z);
	}
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
	if (!F_Multiplayer() && FOptions.rng)
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
	if (F_Multiplayer() || !FOptions.rng)
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
	if (FOptions.number_format && !F_Multiplayer() && number >= 1000)
	{
		H3String *text = (H3String*)IntAt(c->esp);
		text->Dereference();
		text->FormattedNumber(number);
		return NO_EXEC_DEFAULT;
	}
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
	if (FOptions.number_format && !F_Multiplayer() && abs(number) >= 1000)
	{
		H3String *text = (H3String*)IntAt(c->esp);
		text->Dereference();
		text->FormattedNumber(number);
		text->Append(' ');
		LPCSTR resource = StrAt(c->esp + 0xC);
		text->Append(resource, strlen(resource));
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
	if (!F_Multiplayer() && FOptions.rmb_textbox)
	{
		if (!This->isHuman[mon->side]) // not your creature, since you can left-click your own
			newValue = 0;
	}
	THISCALL_3(void, h->GetDefaultFunc(), This, mon, newValue);
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
	if (!F_Multiplayer() && FOptions.spell_details) {
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
			return NO_EXEC_DEFAULT;
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
static DWORD SPELL_DETAILS;
int __stdcall _HH_spellDetails_flag3(HiHook *h, H3Hero* This, int a1, int a2, int a3)
{
	LOG_HIHOOK;
	if (!F_Multiplayer())
		SPELL_DETAILS |= 1;

	int r = THISCALL_4(int, h->GetDefaultFunc(), This, a1, a2, a3);

	SPELL_DETAILS &= ~1;
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
	if (!F_Multiplayer() && (SPELL_DETAILS & 1) && FOptions.spell_details)
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
	if (!F_Multiplayer() && (SPELL_DETAILS & 1) && FOptions.spell_details)
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
	if (!F_Multiplayer())
		SPELL_DETAILS |= 2;

	int r = THISCALL_5(int, h->GetDefaultFunc(), This, a1, a2, a3, a4);

	SPELL_DETAILS &= ~2;
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
	if (!F_Multiplayer() && (SPELL_DETAILS & 2) && FOptions.spell_details)
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
	if (!F_Multiplayer() && (SPELL_DETAILS & 2) && FOptions.spell_details)
	{
		UINT spell_value = PtrAt(c->esp + 8);
		switch (c->arg_n(2))
		{
		case H3Spell::AIR_ELEMENTAL:
		case H3Spell::EARTH_ELEMENTAL:
		case H3Spell::FIRE_ELEMENTAL:
		case H3Spell::WATER_ELEMENTAL:
			F_sprintf(TSpells()->Elementals(), spell_value);
			break;
		case H3Spell::CURE:
			F_sprintf(TSpells()->Cure(), spell_value);
			break;
		case H3Spell::HYPNOTIZE:
			F_sprintf(TSpells()->Hypnotize(), spell_value);
			break;
		case H3Spell::RESURRECTION:
		case H3Spell::ANIMATE_DEAD:
			F_sprintf(TSpells()->Resurrection(), spell_value);
			break;
		case H3Spell::VISIONS:
			F_sprintf(TSpells()->Visions(), spell_value);
			break;
		case H3Spell::FLY:
		case H3Spell::WATER_WALK:
			F_sprintf(TSpells()->FlyWW(), spell_value);
			break;
		case H3Spell::BLOODLUST:
		case H3Spell::PRECISION:
		case H3Spell::STONE_SKIN:
		case H3Spell::PRAYER:
		case H3Spell::MIRTH:
		case H3Spell::FORTUNE:
		case H3Spell::HASTE:
		case H3Spell::SLAYER:
			F_sprintf(TSpells()->Increase(), spell_value);
			break;
		case H3Spell::WEAKNESS:
		case H3Spell::DISRUPTING_RAY:
		case H3Spell::SORROW:
		case H3Spell::MISFORTUNE:
			F_sprintf(TSpells()->Reduce(), spell_value);
			break;
		case H3Spell::SLOW:
		case H3Spell::SHIELD:
		case H3Spell::AIR_SHIELD:
		case H3Spell::PROTECTION_FROM_AIR:
		case H3Spell::PROTECTION_FROM_FIRE:
		case H3Spell::PROTECTION_FROM_WATER:
		case H3Spell::PROTECTION_FROM_EARTH:
			F_sprintf(TSpells()->ReducePerc(), spell_value);
			break;
		case H3Spell::DIMENSION_DOOR:
		case H3Spell::TOWN_PORTAL:
			F_sprintf(TSpells()->DDTP(), spell_value);
			break;
		case H3Spell::SACRIFICE:
			F_sprintf(TSpells()->Sacrifice(), spell_value);
			break;
		case H3Spell::FIRE_SHIELD:
			F_sprintf(TSpells()->FireShield(), spell_value);
			break;
		default:
			break;
		}
	}
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
	if (!F_Multiplayer() && P_CombatMgr->actionParameter == H3Spell::FORCE_FIELD)
		c->ebx = 0; // forcefield middle hex is always on the right
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
	if (!F_Multiplayer() && FOptions.number_format && resource >= 1000)
	{
		if (resource < 1000000)  // greater/equal one thousand
			F_sprintf("%d,%03d", (resource / 1000) % 1000, resource % 1000);
		else if (resource < 100000000)  // greater/equal one million
			F_sprintf("%d,%03d{k}", (resource / 1000000) % 1000, (resource / 1000) % 1000);
		else if (resource < 1000000000)  // greater/equal 100 million
			F_sprintf("%d{M}", (resource / 1000000) % 1000);
		else // greater/equal one billion
			F_sprintf("%d,%03d{M}", (resource / 1000000000) % 1000, (resource / 1000000) % 1000);
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
	if (!F_Multiplayer() && FOptions.real_kills)
	{
		H3CombatMonster *mon = (H3CombatMonster*)(c->eax - 0x60);
		if (mon->IsClone() || mon->IsSummon())
		{
			c->return_address = 0x470958;
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
	return EXEC_DEFAULT;
}

/*
 *
 * This hook makes AI offensive spells reflectable if Magic Mirror is active on target.
 *
 */
VOID __stdcall _HH_CastSpell_AI_MagicMirror(HiHook* h, H3CombatManager* This, int spellID, int hex, int a3, int newHex, int expertise, int a6)
{
	LOG_HIHOOK;

	if (!F_Multiplayer() &&
		SODSP::FEATURES::FOptions.AI_magic_mirror &&
		!This->IsHumanTurn() &&
		F_SingleTargetSpell(spellID, expertise) &&
		spellID != H3Spell::DISPEL && spellID != H3Spell::SACRIFICE)
	{
		const int side = This->currentActiveSide;
		H3CombatMonster* mon = This->squares[hex].GetMonster();
		if (mon && mon->side != side) // offensive spells only
		{
			INT32 mirror = mon->MagicMirrorEffect();
			if (mirror > 0 && mirror > H3Random::RandBetween(1, 100))
			{
				const int num = This->heroMonCount[side];
				int index{ 0 };
				H3IndexVector indexSelector(0, num - 1);
				while (index >= 0)
				{
					index = indexSelector.ChooseRandom();
					if (index < 0)
						break;
					H3CombatMonster* newMon = &This->stacks[side][index];
					if (!newMon->info.flags.CANNOTMOVE && newMon->type != NH3Creatures::ARROW_TOWER)
					{
						newHex = newMon->position;
						break;
					}
				}
			}
		}
	}
	THISCALL_7(VOID, h->GetDefaultFunc(), This, spellID, hex, a3, newHex, expertise, a6);
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
				q->category = std::max(2 - q->morale + 2 * (q->waiting + combat->waitPhase), 2u);
			if (q->creature->IsDone())
				q->category = 5;
			if (q->speed == 0 || q->cannot_move)
				q->category = 6;
			if (!q->creature->numberAlive)
				q->category = 7;
			if (q->creature == active_creature)
				q->category = 1;
		}
	}

	///////////////////////////////////////////////////////
	// initial sort of creatures: by category, then by speed & position
	///////////////////////////////////////////////////////
	qsort(queue, 42, sizeof(CrQueue), compare_queue);

	for (INT32 i = 1; i < 42; i++)
	{
		CrQueue* fastestInfo = &queue[i];
		INT32 fastest_position = i;

		for (INT32 j = i + 1; j < 42; j++)
		{
			CrQueue* current = &queue[j];
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
		CrQueue tempInfo = queue[i];
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
	H3CombatMonster *our_mon;
	const INT32 mouse_coord = combat->mouse_coord;
	const INT32 column = mouse_coord % 17;
	const INT32 row = mouse_coord / 17 + 'A';
	CHAR new_text[128];
	new_text[0] = 0;
	if (!min_damage && !max_damage) // hovering over one of your own creatures or can't reach enemy
	{
		if ((our_mon = combat->squares[mouse_coord].GetMonster()) && column > 0 && column < 16 && row < (12 + 'A'))
		{
			INT32 maxHP = our_mon->info.hitPoints;
			INT32 lostHP = our_mon->healthLost;
			INT32 currentHP = maxHP - lostHP;

			if (FOptions.creature_hp)
				sprintf(buffer, " {~%s}%d%s}", ColorsStrings.hit_points.String(), currentHP, TCombat()->HP());

			if (FOptions.move_sequence) // show creature move order
			{
				UINT32 battle_sequence[42] = { 0 }; // for 42 creatures, which position will move next
				calculate_queue(battle_sequence, combat);
				_snprintf(new_text, 128, "%s [{~%s}%d}]", new_text, ColorsStrings.move_sequence.String(), battle_sequence[our_mon->Index()]);
			}
		}
		strcat(buffer, new_text);
	}

	if (max_damage || min_damage)
	{
		H3CombatMonster* oppMon = combat->squares[mouse_coord].GetMonster();
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
					_snprintf(new_text, 128, ", {~%s}%s %d})", ColorsStrings.kill_all.String(), TCombat()->Kills(), numberCreatures); // will kill all, print kills in green or user choice
				else  // not all creatures
					_snprintf(new_text, 128, ", {%s} {~%s}%d})", TCombat()->Kills(), ColorsStrings.kill_some.String(), minKills); // will not kill all, print kills in red or user choice
			}
			else // kill different amount
			{
				if (maxKills < numberCreatures) // cannot kill all
					_snprintf(new_text, 128, ", {%s} {~%s}%d} {%s} {~%s}%d})", TCombat()->Kills(), ColorsStrings.kill_some.String(), minKills, TCombat()->To(), ColorsStrings.kill_some.String(), maxKills);
				else // maxKills slays all, but not minKills
					_snprintf(new_text, 128, ", {%s} {~%s}%d} {%s} {~%s}%d})", TCombat()->Kills(), ColorsStrings.kill_some.String(), minKills, TCombat()->To(), ColorsStrings.kill_all.String(), numberCreatures);
			}

			if (FOptions.creature_hp) // show creature remaining hp
				_snprintf(new_text, 128, "%s {~%s}%d%s}", new_text, ColorsStrings.hit_points.String(), currentHP, TCombat()->HP());

			if (FOptions.move_sequence) // show creature move order
			{
				UINT32 battle_sequence[42] = { 0 }; // for 42 creatures, which position will move next
				calculate_queue(battle_sequence, combat);
				_snprintf(new_text, 128, "%s [{~%s}%d}]", new_text, ColorsStrings.move_sequence.String(), battle_sequence[oppMon->Index()]);
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
	if (FOptions.comb_coordinates)
	{
		CHAR coord_text[64];
		if (column > 0 && column < 16 && row < (12 + 'A'))  // we don't care about off-grid coordinates
		{
			INT32 attacking_coordinates = combat->attacker_coord;
			if (combat->move_type == 7)  // melee attack, show destination of attacker as well as defender's location
			{
				if (combat->activeStack->info.flags.DOUBLE_WIDE)
					attacking_coordinates += (combat->currentActiveSide == 0) ? 1 : -1;
				const INT32 attacker_column = attacking_coordinates % 17;
				const INT32 attacker_row = attacking_coordinates / 17 + 'A';
				_snprintf(coord_text, 64, " {~%s}(%c%d—%c%d)}", ColorsStrings.battle_coordinates.String(), (CHAR)attacker_row, attacker_column, (CHAR)row, column);
			}
			else
				_snprintf(coord_text, 64, " {~%s}(%c%d)}", ColorsStrings.battle_coordinates.String(), (CHAR)row, column);

			strcat(buffer, coord_text);
		}
	}

	min_damage = 0;
	max_damage = 0;
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
	if (!F_Multiplayer())
	{
		const int spell_id = c->arg_n(1);
		const int coordinates = c->arg_n(2);
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
			const int side = combat->currentActiveSide;
			H3Hero* our_hero = combat->hero[side];
			H3Hero* enemy_hero = combat->hero[1 - side];
			const INT32 spell_power = combat->heroSpellPower[side];

			const INT32 spell_expertise = our_hero->GetSpellExpertise(spell_id, combat->specialTerrain);
			const INT32 base_damage = P_Spell(spell_id).GetBaseEffect(spell_expertise, spell_power);
			INT32 number_creatures = 0;
			INT32 dead_creatures;
			INT32 damage, real_damage;
			const INT32 max_hp = targetMon->info.hitPoints;
			const INT32 lost_hp = targetMon->healthLost;
			const INT32 current_hp = max_hp - lost_hp;

			switch (spell_id)
			{
			case H3Spell::ICE_BOLT:
			case H3Spell::IMPLOSION:
			case H3Spell::MAGIC_ARROW:
			case H3Spell::LIGHTNING_BOLT:
			case H3Spell::TITANS_LIGHTNING_BOLT:
				damage = real_damage = our_hero->GetRealSpellDamage(base_damage, targetMon, spell_id, enemy_hero);
				if (damage >= current_hp)
				{
					number_creatures++;
					damage -= current_hp;
				}
				if (damage > 0)
					number_creatures += damage / max_hp;

				if (number_creatures < targetMon->numberAlive)
					F_sprintf("%s (%d %s, {%s:} {~%s}%d})", h3_TextBuffer, real_damage, TCombat()->Damage(), TCombat()->Kills(), ColorsStrings.kill_some.String(), number_creatures);
				else
					F_sprintf("%s (%d %s, {~%s}%s: %d})", h3_TextBuffer, real_damage, TCombat()->Damage(), ColorsStrings.kill_all.String(), TCombat()->Kills(), targetMon->numberAlive);
				break;
			case H3Spell::RESURRECTION:
			case H3Spell::ANIMATE_DEAD:
				damage = our_hero->GetSpellSpecialtyEffect(spell_id, targetMon->info.level, base_damage);
				real_damage = damage + base_damage;
				number_creatures = 1 + (real_damage - lost_hp) / max_hp;
				dead_creatures = targetMon->numberAtStart - targetMon->numberAlive;
				if (number_creatures < dead_creatures)
					F_sprintf("%s (%d %s, {%s:} {~%s}%d})", h3_TextBuffer, real_damage, TCombat()->ResurrectHP(), TCombat()->Raises(), ColorsStrings.kill_some.String(), number_creatures);
				else
					F_sprintf("%s (%d %s, {~%s}%s: %d})", h3_TextBuffer, real_damage, TCombat()->ResurrectHP(), ColorsStrings.kill_all.String(), TCombat()->Raises(), dead_creatures);
				break;
			case H3Spell::CURE:
				damage = our_hero->GetSpellSpecialtyEffect(spell_id, targetMon->info.level, base_damage);
				real_damage = damage + base_damage;
				if (real_damage > lost_hp)
					F_sprintf("%s ({~%s}%d %s})", h3_TextBuffer, ColorsStrings.kill_all.String(), lost_hp, TCombat()->ResurrectHP());
				else
					F_sprintf("%s ({~%s}%d %s})", h3_TextBuffer, ColorsStrings.kill_some.String(), real_damage, TCombat()->ResurrectHP());
				break;
			default:
				break;
			}

			///////////////////////////////////////////////
			// Show coordinates
			///////////////////////////////////////////////
			if (FOptions.comb_coordinates)
			{
				const INT32 column = coordinates % 17;
				const INT32 row = coordinates / 17 + 'A';
				if (column && column < 16 && row < (12 + 'A'))
					F_sprintf("%s {~%s}(%c%d)}", h3_TextBuffer, ColorsStrings.battle_coordinates.String(), row, column);
			}

		}
	}
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
	if (!F_Multiplayer() && FOptions.comb_coordinates)
	{
		const DWORD coordinate = c->arg_n(2);
		const char battle_row = (char)(coordinate / 17 + 'A');
		const int battle_column = coordinate % 17;
		F_sprintf("%s {~%s}(%c%d)}", (PCHAR)c->ecx, ColorsStrings.battle_coordinates.String(), battle_row, battle_column);
		c->ecx = (int)h3_TextBuffer;
	}
	return EXEC_DEFAULT;
}

////////////////////////////////////////////////////////////////////////////////////
// Faster spell animation
////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * For spells that are targeted at creatures
 *
 */
char __stdcall _HH_FastSpellAnimation(HiHook* h, H3CombatManager* This, int a2, int a3, int delay, int a5)
{
	if (FOptions.turbo_animation)
	{
		switch (h3_CurrentAnimationSpeed)
		{
		case 1: // reduce duration by half
			delay = delay >> 1;
			break;
		case 2: // almost instantaneous
			delay = delay >> 4;
			break;
		default: // normal duration
			break;
		}
	}

	return THISCALL_5(char, h->GetDefaultFunc(), This, a2, a3, delay, a5);
}

int __stdcall _HH_FastSummonAnimation(HiHook* h, H3WindowManager* This, int x, int y, int width, int height, int delay)
{
	if (FOptions.turbo_animation)
	{
		switch (h3_CurrentAnimationSpeed)
		{
		case 1: // reduce duration by half
			delay = delay >> 1;
			break;
		case 2: // almost instantaneous
			delay = delay >> 4;
			break;
		default: // normal duration
			break;
		}
	}

	return THISCALL_6(int, h->GetDefaultFunc(), This, x, y, width, height, delay);
}

////////////////////////////////////////////////////////////////////////////////////
// Fix high level experience for cheats and Tree of Knowledge
////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * This hook sets a flag to activate hook @FixExperience when nwcneo cheat is used.
 *
 */
int __stdcall _HH_Cheat_flag(HiHook *h, int _this, int a1, int a2, int a3) // 0x004025F5
{
	GGameFlags.levelup_cheats = TRUE;
	LOG_HIHOOK;
	int r = THISCALL_4(int, h->GetDefaultFunc(), _this, a1, a2, a3);
	GGameFlags.levelup_cheats = FALSE;
	return r;
}

/*
 *
 * This hook sets a flag to activate hook @FixExperience when visiting Tree of Knowledge.
 *
 */
int __stdcall _HH_TreeKnowledge_flag(HiHook *h, int _this, int a1, int a2, int a3) // 0x4A65FF
{
	GGameFlags.levelup_treeknowledge = TRUE;
	LOG_HIHOOK;
	int r = THISCALL_4(int, h->GetDefaultFunc(), _this, a1, a2, a3);
	GGameFlags.levelup_treeknowledge = FALSE;
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
	const INT32 experience = c->ecx; // the hero's total experience after the gained ~ not yet applied to hero

	if (GGameFlags.game_start)
		return EXEC_DEFAULT;

	auto hero = reinterpret_cast<H3Hero*>(c->edi);
	const INT32 hero_level = hero->level;

	// logic for gaining experience normally
	if (!GGameFlags.levelup_cheats && !GGameFlags.levelup_treeknowledge)
	{
		// don't change logic if we're not going to level 868.
		if (experience < NH3Levels::LEVEL_868)
			return EXEC_DEFAULT;

		const int skills_left_to_learn = hero->SSkillsLeftToLearn();

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
		else if (experience >= NH3Levels::LEVEL_MAX) // infinite level-ups -> send hero to level 0
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
	else if (GGameFlags.levelup_treeknowledge)
	{
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
		const int skills_left_to_learn = hero->SSkillsLeftToLearn();
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
_LHF_(AIberserk1)
{
	LOG_LOHOOK;
	if (F_Multiplayer() || !FOptions.berserk)
		return EXEC_DEFAULT;

	H3CombatManager *cmb = P_CombatMgr;

	if (!cmb->activeStack)
		return EXEC_DEFAULT;

	if (!cmb->activeStack->activeSpellsDuration[H3Spell::BERSERK] && cmb->IsHumanTurn())
		return EXEC_DEFAULT;

	if (c->DL())
		return EXEC_DEFAULT;

	c->return_address = 0x4B3537;
	return NO_EXEC_DEFAULT;
}

_NAKED_FUNCTION_ AIberserk2(void)
{
	static naked_t return_berserk2a = reinterpret_cast<naked_t>(0x4B37AA);
	static naked_t return_berserk2b = reinterpret_cast<naked_t>(0x4B37BF);

	__asm PUSHFD
	__asm PUSHAD
	if (!F_Multiplayer() && FOptions.berserk)
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

static naked_t bridge_berserk3;

_NAKED_FUNCTION_ AIberserk3(void)
{
	static naked_t return_berserk3 = reinterpret_cast<naked_t>(0x422447);

	__asm PUSHFD
	__asm PUSHAD
	if (!F_Multiplayer() && FOptions.berserk)
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
void RestoreBerserk(PatcherInstance *pi)
{
	if (ByteAt(0x4B352F) == H3Patcher::mnemonics::jmp)
		pi->WriteLoHook(0x4B352F, AIberserk1);
	if (PtrAt(0x4B37A5) == 0x90909090)
		H3Patcher::NakedHook5(0x4B37A5, AIberserk2);
	if (ByteAt(0x422440) == H3Patcher::mnemonics::jmp)
	{
		bridge_berserk3 = reinterpret_cast<naked_t>(FuncAt(0x422440));
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
	pi->WriteDword(0x505C79, 0x74FFFE83);// TEST SI,SI	to		CMP ESI, -1
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
	union floint
	{
		float f;
		UINT32 i;
	}t;

	if (FOptions.turbo_animation) // turbo values
	{
		t.f = 0.20f;
		H3Patcher::DwordPatch(0x63CF7C, t.i);
		t.f = 0.10f;
		H3Patcher::DwordPatch(0x63CF80, t.i);
		t.f = 0.05f;
		H3Patcher::DwordPatch(0x63CF84, t.i);
	}
	else // normal values
	{
		t.f = 1.00f;
		H3Patcher::DwordPatch(0x63CF7C, t.i);
		t.f = 0.63f;
		H3Patcher::DwordPatch(0x63CF80, t.i);
		t.f = 0.40f;
		H3Patcher::DwordPatch(0x63CF84, t.i);
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
	const int current_count = main->mainSetup.seerHuts.Count();
	if (current_count >= 48)
	{
		const int new_count = current_count % 48;
		BYTE *availNames = (BYTE*)c->esi;
		H3SeerHut *seer = &main->mainSetup.seerHuts[current_count - new_count - 1];
		for (int i = 0; i < new_count; i++)
		{
			availNames[seer->seerNameId] = 0;
			seer++;
		}
		c->edi = int(main);
		c->edx = new_count;
		c->return_address = 0x574DB3;
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
	return EXEC_DEFAULT;
}

///////////
// More custom wandering monsters
////////////

/*
 *
 * These patches allow 4096 customized wandering monsters on the adventure map
 * instead of 256; this takes 4 extra bits that were not used by anything
 * in the original code.
 * You can therefore have more custom messages and custom rewards before
 * the game starts to give you duplicated versions due to modulo operation.
 *
 */
void MoreCustomWanderingMonsters()
{
	H3Patcher::DwordPatch(0x4A67BC + 1, 0xFFF);      // grab individual id
	H3Patcher::DwordPatch(0x4A73F0 + 1, 0xFFF);      // grab individual id
	H3Patcher::DwordPatch(0x501C73 + 1, 0xFFF);      // setup from load map
	H3Patcher::DwordPatch(0x501D2D + 1, 0xFFFBFFFF); // setup from load map
}

/*
 *
 * This hook lets you view your own army's details
 * when you have the Catapult selected.
 *
 */
_LHF_(ViewSelfArmyCatapult)
{
	LOG_LOHOOK;

	H3CombatSquare* sq = (H3CombatSquare*)c->ebx;
	H3CombatMonster* mon = sq->GetMonster();
	if (!mon)
		return EXEC_DEFAULT;
	H3CombatManager* combat = (H3CombatManager*)c->esi;
	if (mon->side == combat->currentActiveSide)
	{
		c->return_address = 0x47600C;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook lets you view any hero's biography
 * when holding CTRL while RMB is pressed.
 *
 */
void __stdcall _HH_HeroRmbBiography(HiHook*h, H3AdventureManager* This, int id, int x, int y, bool a5)
{
	if (SODSP::GENERAL::GMessageFlags & H3Msg::MF_Ctrl)
	{
		H3Hero* hero = P_Main->GetHero(id);
		if (hero == nullptr)
			return;
		H3String bio;
		bio.Printf("{%s}\n\n", hero->name);

		if (hero->customBio)
			bio += hero->biography;
		else
			bio += P_HeroDefaultBiography(id);

		// if text is rather long, or too many lines, make it a regular messagebox
		if (bio.Length() >= 600 || bio.Occurrences('\n') > 13)
			F_MessageBox(bio);
		else // rmb messagebox otherwise
			F_MessageBoxRMB(bio);
	}
	else
		THISCALL_5(void, h->GetDefaultFunc(), This, id, x, y, a5);
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
	// [1.18.0]
	pi->WriteHiHook(0x478986, CALL_, THISCALL_, _HH_CastSpell_AI_MagicMirror);
	// [1.18.0]
	pi->WriteLoHook(0x47617B, ViewSelfArmyCatapult); // when you have the catapult active, you can view your own army information

	//////////////////////////////
	// Faster spell animations
	//////////////////////////////
	pi->WriteHiHook(0x496590, SPLICE_, THISCALL_, _HH_FastSpellAnimation); // targeted spells
	pi->WriteHiHook(0x479BED, CALL_, THISCALL_, _HH_FastSummonAnimation); // summon spells

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
	RestoreBerserk(pi);

	//////////////////////////////////////////////////
	// More Seer Huts with repeated names
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x574D5C, MoreSeerHuts); // pick random name
	pi->WriteLoHook(0x574DF2, MoreSeerHuts2); // don't divide by non-positive number

	//////////////////////////////////////////////////////////////////////////
	// Allows 4096 customized wandering monsters (was 256, then duplicates)
	//////////////////////////////////////////////////////////////////////////
	// [1.18.0]
	MoreCustomWanderingMonsters();

	//////////////////////////////////////////////////////////////////////////
	// Allows 256 signposts/ocean bottles to be loaded
	//////////////////////////////////////////////////////////////////////////
	// [1.18.1]
	H3Patcher::BytePatch(0x4B8DDD + 1, 0xB6); // movsx to movzx, signed->unsigned

	//////////////////////////////////////////////////////////////////////////
	// Show hero biography on CTRL+RMB on the adventure map
	//////////////////////////////////////////////////////////////////////////
	// [1.18.2]
	pi->WriteHiHook(0x40A716, CALL_, THISCALL_, _HH_HeroRmbBiography);
}