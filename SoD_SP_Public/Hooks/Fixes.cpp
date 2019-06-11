#include "Fixes.h"
#include "AnchorBug.h"
#include "HorizontalScrollbar.h"

//////////////////////////////////////////////////////////////////////////
// AI bugs
//////////////////////////////////////////////////////////////////////////

/*
 *
 * This hook prevents AI from casting Town Portal on Cursed Ground
 *
 */
_LHF_(AI_TP_cursed_check)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.ai_cheats)
	{
		H3Hero *hero = (H3Hero*)c->esi;
		if (hero->GetSpecialTerrain() == NH3Objects::CURSED_GROUND)
		{
			c->return_address = 0x56B6F4;
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents division by 0 during tactics phase when you have no army.
 * When AI has tactics or attacks you, they split their shooters...
 *
 */
_LHF_(AI_split_div0)
{
	LOG_LOHOOK;
	if (c->ebx == 0) // ... if the other hero has no army, it will divide by 0
		c->ebx = 1; // make it 1 to avoid changing much and prevent crash
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents AI from casting Fly if they don't have it.
 *
 */
_LHF_(AI_waterwalk_fly)
{
	LOG_LOHOOK;
	if (!multiplayer_game && c->eax == 0 && SODSP_OPTIONS.ai_cheats)
	{
		H3Hero *hero = (H3Hero *)(c->esi);
		if (!hero->HasSpell(H3Spell::FLY)) // this AI hero does not have the means to cast fly
		{
			if (hero->HasSpell(H3Spell::WATER_WALK)) // this AI hero has access to waterwalk
			{
				if (hero->waterwalkPower == -1) // waterwalk is not cast
					c->return_address = 0x430231;
				else
					c->return_address = 0x430540;
				LOG_LOHOOK;
				return NO_EXEC_DEFAULT;
			} // waterwalk available
		} // fly available
	} // mp game && no angel wings
	return EXEC_DEFAULT;
}

/*
 *
 * The AI was observed to divide by speed = 0 in "Rise of The Sun King"
 *
 */
_LHF_(AI_combat_div0)
{
	LOG_LOHOOK;
	if (c->edi == 0)
		c->edi = 1;
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook [1] allows AI to raise more than one necromancy creature.
 * It skips deletion of loser's army which will be done later.
 *
 */
_LHF_(AI_NecromancyFix)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.AI_necromancy)
	{
		c->return_address = 0x426FED;
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * This hook [2] allows AI to raise more than one necromancy creature.
 * It restores deletion of loser's army which was skipped by @AI_NecromancyFix
 *
 */
void _HH_AI_NecromancyFix(HiHook *h, H3AIQuickBattle *winner, H3AIQuickBattle *loser, int town)
{
	LOG_HIHOOK;
	THISCALL_3(void, h->GetDefaultFunc(), winner, loser, town);
	if (!multiplayer_game && SODSP_OPTIONS.AI_necromancy)
		loser->DeleteCreatures();
	LOG_HIHOOK;
}

/*
 *
 * The AI was observed to deal negative damage in quick battle in "+ The Last Crusade +"
 * when having a large army. This caps damage to 2^31 - 1.
 *
 */
int __stdcall _HH_AI_QB_GetDamage(HiHook *h, H3AIQuickBattle *This, int a1, int a2)
{
	LOG_HIHOOK;
	int r = THISCALL_3(int, h->GetDefaultFunc(), This, a1, a2);

	if (SODSP_OPTIONS.quickbattle_overflow && This->armyStrength > 0 && r < 0)
		r = INT_MAX;
	LOG_HIHOOK;
	return r;
}

/*
 *
 * The AI with very large army may calculate its army strength as negative and lose easy battles.
 * This caps power to 2^31 - 1.
 *
 */
void __stdcall _HH_AI_QB_hugeArmy(HiHook *h, H3AIQuickBattle *This, int a1, int a2, int a3)
{
	LOG_HIHOOK;
	if (SODSP_OPTIONS.quickbattle_overflow && This->armyStrength < 0)
		This->armyStrength = INT_MAX;
	LOG_HIHOOK;
	THISCALL_4(void, h->GetDefaultFunc(), This, a1, a2, a3);
}

/*
 *
 * The AI was observed to spawn creatures during Quick Combat, finishing with more
 * creatures than it started the combat with.
 * This hook is applied before @AI_NecromancyFix.
 *
 */
void __stdcall _HH_AI_PreventCreatureSpawning(HiHook *h, H3AIQuickBattle *This, int a2)
{
	LOG_HIHOOK;
	BOOL valid = (!multiplayer_game && SODSP_OPTIONS.quickbattle_overflow);
	H3Army backup;
	if (valid)
		backup = *This->army;
	THISCALL_2(void, h->GetDefaultFunc(), This, a2);
	if (valid)
	{
		H3Army *army = This->army;
		for (int i = 0; i < 7; i++)
		{
			if (army->type[i] != -1 && army->count[i] > backup.count[i])
				army->count[i] = backup.count[i];
		}
	}
	LOG_HIHOOK;
}

/*
 *
 * The AI with very large army may calculate army strength as negative and enter infinite loops.
 * This caps power to 2^31 - 1.
 *
 */
int __stdcall _HH_AI_GetArmyValue(HiHook *h, H3Army *This)
{
	LOG_HIHOOK;
	int r = THISCALL_1(int, h->GetDefaultFunc(), This);
	if (SODSP_OPTIONS.quickbattle_overflow && r < 0)
		r = INT_MAX - 500; // - 500 is needed as sometimes this is used to calculate experience and if a town/hero is present it will overflow.
	LOG_HIHOOK;
	return r;
}

//////////////////////////////////////////////////////////////////////////
// Turret towers bugs
//////////////////////////////////////////////////////////////////////////

/*
 *
 * These hooks correct the Armorer / Air Shield vs. Arrow Turret bug.
 * A much simpler fix exists but this was simplest for SoD_SP's scope.
 *
 */
static naked_t return_turret1 = (naked_t)0x41E3A6;
naked_function turret_bug1(void)
{
	__asm PUSHFD
	__asm PUSHAD
	if (!multiplayer_game && SODSP_OPTIONS.turrets)
	{
		__asm POPAD
		__asm POPFD
		__asm MOV EAX, 0x443AB0
		__asm CALL EAX
		__asm FMUL QWORD PTR SS : [EBP - 8]
	}
	else
	{
		__asm POPAD
		__asm POPFD
		__asm MOV EAX, 0x443AB0
		__asm CALL EAX
		__asm FDIVR QWORD PTR SS : [EBP - 8]
	}

	__asm JMP return_turret1
}

static naked_t return_turret2 = (naked_t)0x41E4E2;
naked_function turret_bug2(void)
{
	__asm PUSHFD
	__asm PUSHAD
	if (!multiplayer_game && SODSP_OPTIONS.turrets)
	{
		__asm POPAD
		__asm POPFD
		__asm MOV EAX, 0x443AB0
		__asm CALL EAX
		__asm FMUL QWORD PTR SS : [EBP - 8]
	}
	else
	{
		__asm POPAD
		__asm POPFD
		__asm MOV EAX, 0x443AB0
		__asm CALL EAX
		__asm FDIVR QWORD PTR SS : [EBP - 8]
	}
	__asm JMP return_turret2
}

static naked_t return_turret3 = (naked_t)0x465946;
naked_function turret_bug3(void)
{
	__asm PUSHFD
	__asm PUSHAD
	if (!multiplayer_game && SODSP_OPTIONS.turrets)
	{
		__asm POPAD
		__asm POPFD
		__asm MOV EAX, 0x443AB0
		__asm CALL EAX
		__asm FMUL QWORD PTR SS : [EBP - 0x2C]
	}
	else
	{
		__asm POPAD
		__asm POPFD
		__asm MOV EAX, 0x443AB0
		__asm CALL EAX
		__asm FDIVR QWORD PTR SS : [EBP - 0x2C]
	}
	__asm JMP return_turret3
}

//////////////////////////////////////////////////////////////////////////
// GUI errors
//////////////////////////////////////////////////////////////////////////

/*
 *
 * The creature dialog of Faerie Dragon's would show 'Sawmill' for their
 * spell icon hint.
 *
 */
_LHF_(faerie_dialog_hover)
{
	LOG_LOHOOK;
	if (c->eax == 0x0F)
	{
		c->edi = IntAt(0x6A6A00); // "Cast Spell" text ~ taken from 0x46B4FE
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * The creature dialog of Faerie Dragon's would show 'Sawmill' for their
 * spell icon right-click message.
 *
 */
_LHF_(faerie_dialog_RMB)
{
	LOG_LOHOOK
		if (c->esi == 0x0F)
		{
			c->esi = IntAt(0x6A6A00); // "Cast Spell" text ~ taken from 0x46B4FE
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		}
	return EXEC_DEFAULT;
}

/*
 *
 * Alignment of some icons and use of correct icons.
 * Patch by igrik.
 *
 */
void GUI_fixes_by_igrik(PatcherInstance *pi)
{
	// cancel button in tavern
	// iCancel.def to iCN6432.def
	pi->WriteDword(0x5D7AC9 + 1, 0x682A24);

	// cancel button in creature swapmanager window
	// iCancel.def to iCN6432.def
	pi->WriteDword(0x449A40 + 1, 0x682A24);

	/////////////////////////////////////////////
	// fix Faerie Dragon button coordinates
	/////////////////////////////////////////////
	// Y position
	// 0xEC to 0xEB
	pi->WriteByte(0x5F3D9E + 1, 0xEB);

	// X position
	// 0x4A to 0x15
	pi->WriteByte(0x5F3DA3 + 1, 0x15);

	// Y position
	// 0xEC to 0xEB
	pi->WriteByte(0x5F3DF4 + 1, 0xEB);

	// X position
	// 0x4A	to 0x15
	pi->WriteByte(0x5F3DF9 + 1, 0x15);
}

//////////////////////////////////////////////////////////////////////////
// Misc. errors
//////////////////////////////////////////////////////////////////////////

/*
 *
 * Wait Phase Bug [2].
 * Because Wait Phase Bug [1] restores access to a function at all times,
 * portion of its code must be skipped during Wait Phase.
 *
 */
_LHF_(WaitPhaseBug)
{
	LOG_LOHOOK;
	if (P_CombatMgr->waitPhase) // we need to prevent regen abilities or elixir of life to trigger
		c->flags.ZF = TRUE;     // because it was not supposed to act in this phase
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * The nwczion cheat flag is not always reset.
 *
 */
void NWCzionBug()
{
	ByteAt(0x6AAAC4) = 0;
}

/*
 *
 * Called by FindMe at the same time disabled events get hidden.
 *
 * If the dialog to select which creatures to keep is created, the ShowHero() function is called.
 * This function places the hero's data over H3MapItem which normally stores the data for the event.
 * The event's data in turn is stored in H3Hero->objectBelow entries.
 * Normally after visiting the event is complete, there is a check whether the event is a one-time only thing,
 * however if ShowHero() was called then the H3MapItem->setup field only contains the hero ID (0~156) and
 * never the trigger for the single visit of and event.. thus not disabling it.
 * With this fix, we simply emulate the code at 0x4A0C30 to remove the reference to the event.
 * The next time HideHero() is called, it will replace the data of H3MapItem with the now blank hero->objectBelow entries
 *
 */
BOOL RevisitEventBug(H3Hero *hero)
{
	if (SODSP_OPTIONS.event_repeat_bug && (hero->isVisible) && (hero->objectTypeUnder == NH3Objects::EVENT)
		&& ((MapEvent*)& hero->objectBelowSetup)->oneVisit)
	{
		hero->objectTypeUnder = 0; // equivalent to line 0x4A0C30
		hero->objectBelowSetup = 0; // equivalent to line 0x4A0C36
		// line 0x4A0C2A will be handled later by HideHero() when he moves away, focus is changed, hero is dismissed, or killed
		return TRUE;
	}
	return FALSE;
}

/*
 *
 * When opening the creature trade window rapidly, a structure is written upon hover.
 * If you click rapidly in repetition (e.g. revisiting event to spawn creatures),
 * this piece of code may be executed before being populated - resulting in crash to desktop.
 * Observed in "Bug Race".
 *
 */
_LHF_(ViewHeroScreenRapidly)
{
	LOG_LOHOOK;
	if (!c->eax)
		c->eax = (int)((H3TownManager*)c->esi)->bottom;
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * Similar to @RevisitEventBug except for Creature Banks.
 * Instead of being able to spawn creatures, here it results in crash to desktop.
 *
 */
_LHF_(VisitBankBug)
{
	LOG_LOHOOK;
	H3MapItem *mip = (H3MapItem*)c->eax;
	if (mip->objectType == NH3Objects::HERO)
		P_AdventureMgr->MobilizeHero();
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * Earthquake can incorrectly target creature in position 0 and set its flag
 * to CANNOT_MOVE, a.k.a. War Machine. Since a Hero cannot survive with only War Machines,
 * he would be defeated.
 *
 */
_LHF_(EarthquakeBug)
{
	LOG_LOHOOK;
	if (!multiplayer_game && SODSP_OPTIONS.earthquake_bug)
	{
		H3CombatMonster *mon = (H3CombatMonster *)(c->eax - 0x84); // offset is to creature flags
		if (mon->sideIndex == 0)
		{
			LOG_LOHOOK;
			return NO_EXEC_DEFAULT;
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * Proposed by Ben80
 * If wandering monster had upgraded stack, it would only restore creatures of the base type.
 * This apparent bug in the code stems from the fact that the parent function could be used
 * to add extra creatures (see arguments 6, 9, ...) but was only ever used for Pyramid...
 * Pyramid creatures always reset so essentially it's an abandonned feature that was
 * not properly tested.
 *
 */
_LHF_(PreserveMonsterNumber)
{
	LOG_LOHOOK;
	if (!multiplayer_game && c->arg_n(6) == -1 && c->arg_n(9) == -1 && SODSP_OPTIONS.vanish)
	{
		c->esp += 4; // pop edi
		H3Army* monsters = (H3Army*)c->ecx;;
		int monNumber = 0;

		for (int i = 0; i < 7; i++)
			monNumber += monsters->count[i]; // restore count no matter if it is an upgraded creature or not
		c->eax = monNumber;

		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * Heroes set as 'Can be Hired by' players X in the mapeditor are not preserved
 * in certain occasions. This hook maintains the hero's hireability as set in h3m.
 * Observed in "Metataxer's Revenge".
 *
 */
_LHF_(FixHireables)
{
	LOG_LOHOOK;
	if (!multiplayer_game || SODSP_OPTIONS.tavern_heroes)
		return NO_EXEC_DEFAULT;
	return EXEC_DEFAULT;
}

//////////////////////////////////////////////////////////////////////////
// Movement
//////////////////////////////////////////////////////////////////////////

/*
 *
 * A simple update of the hero's max land movement after landing.
 *
 */
_LHF_(UpdateMaxLandMovement)
{
	LOG_LOHOOK;
	H3Hero* hero = (H3Hero*)c->esi;
	hero->maxMovement = hero->MaxLandMovement();
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * After visiting movement boosting objects, the hero's max movement field
 * is boosted but then reset if you view the Hero dialog.
 *
 */
_LHF_(RecalculateMovementAfterVisitObject)
{
	LOG_LOHOOK;
	H3Hero* hero = (H3Hero*)c->edi;
	hero->maxMovement = hero->CalcMaxMovement();
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * After visiting a town, a hero may have gained access to Stables (Castle)
 * or gained a level (Dungeon) and their maximum movement may have changed.
 *
 */
_LHF_(RecaculateMovementAfterExitingTown)
{
	LOG_LOHOOK;
	H3Hero* hero = (H3Hero*)c->eax;
	hero->maxMovement = hero->CalcMaxMovement();
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * When trading artifacts and exiting the trade dialog with the second hero,
 * the maximum movement would not be updated.
 *
 */
void __stdcall _HH_HeroesMeeting(HiHook *h, H3AdventureManager *This, H3Hero *hero, INT second_hero_id_ptr, H3Position position, BOOL8 human)
{
	LOG_HIHOOK;
	H3Hero* second_hero = P_Main->GetHero(PtrAt(second_hero_id_ptr));
	BOOL same_owner = FALSE;
	if (second_hero)
		same_owner = hero->owner == second_hero->owner;

	THISCALL_5(void, h->GetDefaultFunc(), This, hero, second_hero_id_ptr, position.Mixed(), human);

	if (human && same_owner)
		second_hero->maxMovement = second_hero->CalcMaxMovement();
	LOG_HIHOOK;
}

/*
 *
 * Cycles through a player's heroes currently on the map and updates their
 * maximum water movement.
 *
 */
void update_heroes_max_mvmt_in_water()
{
	H3Hero *hero;
	H3Player *me = h3_ActivePlayer;
	H3Main *main = P_Main;
	for (int i = 0; i < 8; i++)
	{
		if ((hero = main->GetHero(me->heroIDs[i])) && hero->flags.in_boat)
			hero->maxMovement = hero->MaxWaterMovement();
	}
}

/*
 *
 * After visiting a Lighthouse, all heroes currently in water
 * need their maximum movement to be updated.
 *
 */
_LHF_(UpdateSeaMvmtLighthouse)
{
	LOG_LOHOOK;
	if ((BYTE)c->arg_n(4)) // only if human
		update_heroes_max_mvmt_in_water();
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

/*
 *
 * Similar to @UpdateSeaMvmtLighthouse but in the case of building a Castle's Lighthouse.
 *
 */
int __stdcall _HH_AfterBuildingLighthouse(HiHook *h, H3Town *This, int building_id)
{
	LOG_HIHOOK;
	int r = THISCALL_2(int, h->GetDefaultFunc(), This, building_id);

	if (h->GetReturnAddress() == 0x5BF262) // only care about when I build it
	{
		if (This->type == H3Town::CASTLE && building_id == H3Town::B_LIGHTHOUSE) // if castle and building a lighthouse
		{
			if (This->owner == h3_CurrentPlayerID) // only care about human
				update_heroes_max_mvmt_in_water();
		}
	}
	LOG_HIHOOK;
	return r;
}

/*
 *
 * Built Lighthouses in Castle towns would apply movement bonus to every hero on the map.
 * A check is made on the castle's owner and the procedure is skipped when necessary.
 *
 */
_LHF_(CastleLighthouseOwnerCheck)
{
	LOG_LOHOOK;
	if (SODSP_OPTIONS.movement_bugs)
	{
		H3Town *town = (H3Town*)(c->ecx);
		H3Hero *hero = (H3Hero*)(c->local_n(1)); // H3Hero is stored in temp variable [LOCAL.1]

		if (hero->owner == town->owner) // normal
			return EXEC_DEFAULT;

		c->return_address = 0x4E4D6C; // skip procedure
		LOG_LOHOOK;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

//////////////////////////////////////////////////////////////////////////
// Hooks init
//////////////////////////////////////////////////////////////////////////

void fixes_init(PatcherInstance * pi)
{
	//////////////////////////////////////////////////
	// AI bugs
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x56B344, AI_TP_cursed_check);		// disallow casting Town Portal on cursed ground for AI
	pi->WriteLoHook(0x43020E, AI_waterwalk_fly);		// disallow AI from casting Fly if they don't have it (v1)
	pi->WriteLoHook(0x42DDA6, AI_split_div0);			// if AI has tactics and shooters, but you have 0 creatures -> crash
	pi->WriteLoHook(0x42437D, AI_combat_div0);			// divides by speed which shouldn't be 0
	pi->WriteLoHook(0x426FE4, AI_NecromancyFix);		// Army is deleted before Necromancy action, so skip army deletion and execute it in HH below
	pi->WriteHiHook(0x426EE0, SPLICE_, THISCALL_, _HH_AI_NecromancyFix);			// this HiHook runs the skipped over code from @AI_NecromancyFix
	pi->WriteHiHook(0x426390, SPLICE_, THISCALL_, _HH_AI_QB_GetDamage);			// don't allow negative damage in QB
	pi->WriteHiHook(0x42443B, CALL_, THISCALL_, _HH_AI_QB_hugeArmy);				// prevent loss to small army
	pi->WriteHiHook(0x4274D4, CALL_, THISCALL_, _HH_AI_PreventCreatureSpawning);	// flag for below hook
	pi->WriteHiHook(0x44A950, SPLICE_, THISCALL_, _HH_AI_GetArmyValue);			// prevent endless turns for negative ai value

	//////////////////////////////////////////////////
	// turret armorer bug
	//////////////////////////////////////////////////
	H3Patcher::NakedHook5(0x41E39E, turret_bug1);
	H3Patcher::NakedHook5(0x41E4DA, turret_bug2);
	H3Patcher::NakedHook5(0x46593E, turret_bug3);

	//////////////////////////////////////////////////
	// GUI errors
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x5F4C99, faerie_dialog_RMB);	// right click on cast-spell icon didn't give correct text
	pi->WriteLoHook(0x5F5320, faerie_dialog_hover); // same as above, but for mouse hover
	pi->WriteByte(0x41DBE8 + 1, 0x5C);				// if AI is teleporting and you had "Don't show enemy moves" on, it would still check if area is visible and show them
	GUI_fixes_by_igrik(pi);							// various DEFs and positions
	pi->WriteByte(0x49E4ED, 0x63);					// Repair Arena Cancel button
	horizontalScrollbar_init(pi);					// horizontal scrollbar using arrows not correctly drawn

	//////////////////////////////////////////////////
	// Misc errors
	//////////////////////////////////////////////////
	pi->WriteLoHook(0x5D52BF, ViewHeroScreenRapidly);	// If you click fast enough in garrison exchange dialog, sourcePage is left as 0 and crash ensues
	pi->WriteLoHook(0x4AC157, VisitBankBug);			// after viewing hero screen during creature reward of creature bank, potential crash
	pi->WriteLoHook(0x465656, EarthquakeBug);			// do not kill the first creature stack while using earthquake
	pi->WriteLoHook(0x4AC5F5, PreserveMonsterNumber);	// prevents the loss of upgraded stack creatures from the total number of wandering monsters
	pi->WriteLoHook(0x446BCD, WaitPhaseBug);			// do not use restore hit points ability a second time in wait phase bug function
	pi->WriteJmp(0x464DF1, 0x464DFB);					// Wait Phase Bug part 1
	pi->WriteWord(0x4F8758, 0x63EB);					// disable F1 HELP button effects ~ glitched in modern OS
	static const PCHAR rogueSound = "rogu";
	pi->WriteDword(0x67448C, rogueSound);				// Rogue Sound instead of gremlin sound
	pi->WriteByte(0x4FD495 + 1, 0xA);					// error check didn't correctly redirect Hero structure calculation

	///////////////////////////////////////////
	// Hero hireability
	///////////////////////////////////////////
	pi->WriteLoHook(0x4D7BF0, FixHireables);			// swap in town, hire in town, etc.
	pi->WriteLoHook(0x4A3D14, FixHireables);			// prison

	////////////////////////////////////////////////////////
	// Movement updates that were missing or movement bugs
	////////////////////////////////////////////////////////
	pi->WriteLoHook(0x49E340, UpdateMaxLandMovement);								// after landing, max movement was not always updated
	pi->WriteLoHook(0x4AA76B, RecalculateMovementAfterVisitObject);					// only for human ~ useless for AI
	pi->WriteLoHook(0x5BE69A, RecaculateMovementAfterExitingTown);					// only for human ~ useless for AI
	pi->WriteHiHook(0x4A2470, SPLICE_, THISCALL_, _HH_HeroesMeeting);				// due to HDmod, you can directly switch to second hero, whose max movement is not updated
	pi->WriteLoHook(0x4A9173, UpdateSeaMvmtLighthouse);								// when visiting a Lighthouse, all human heroes in boats should get their movement updated
	pi->WriteHiHook(0x5BED30, SPLICE_, THISCALL_, _HH_AfterBuildingLighthouse);		// when building Castle Lighthouse, update max water movement
	pi->WriteLoHook(0x4E4D40, CastleLighthouseOwnerCheck);							// castle's lighthouse only applies to its owner

	//////////////////////////////////////////////////
	// Other
	//////////////////////////////////////////////////
	anchorbug_init(pi); // corrects anchor bug in combat
}