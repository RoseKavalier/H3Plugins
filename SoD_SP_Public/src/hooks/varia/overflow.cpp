#include "overflow.hpp"
#include "Global.hpp"
#include "sodsp/Log.hpp"

using namespace h3;

using sodsp::ftr::FOptions;
using sodsp::gen::GGameFlags;

/*
 *
 * This hook prevents resources overflow from kingdom income.
 *
 */
_LHF_(DailyResources_OF) // 0x4C7EAD
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.resources_overflow)
	{
		H3Main *main = (H3Main*)c->ebx;
		H3Player *pl = main->players;

		for (int i = 0; i < 8; i++, pl++)
		{
			if (!main->isDead[i])
				pl->playerResources.GainResourcesOF(pl->income);
		}

		c->return_address = 0x4C7EE1;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents resources overflow from collecting resources
 * on the adventure map.
 *
 */
_LHF_(MapResources_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.resources_overflow)
	{
		UINT32 current = c->edx;
		UINT32 gained = c->edi;
		if (current <= INT_MAX && gained <= INT_MAX && (current + gained) > INT_MAX)
			c->edi = INT_MAX - current;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents resources overflow from receiving resources
 * during global events, events and town events.
 *
 */
_LHF_(EventResources_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.resources_overflow)
	{
		UINT32 gained = c->edx;
		UINT32 current = c->eax;
		if (current <= INT_MAX && gained <= INT_MAX && (current + gained) > INT_MAX)
			c->edx = INT_MAX - current;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents resources overflow when using Trade Markets.
 *
 */
_LHF_(MarketResources_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.resources_overflow)
	{
		UINT32 gained = c->esi;
		UINT32 current = c->eax;
		if (current <= INT_MAX && gained <= INT_MAX && (current + gained) > INT_MAX)
			c->esi = INT_MAX - current;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents resources overflow when selling artifacts
 * at the Artifact Merchant.
 *
 */
int __stdcall _HH_ArtifactMerchantSell_OF(HiHook *h, H3Dlg *This, H3Msg *msg)
{
	LOG_HIHOOK;
	BOOL valid = (!F_Multiplayer() && FOptions.resources_overflow && P_Main()->GetPlayer() == P_ActivePlayer());
	H3Resources backup;
	if (valid)
		backup = P_ActivePlayer()->playerResources;

	const int r = THISCALL_2(int, h->GetDefaultFunc(), This, msg);

	if (valid)
	{
		H3Resources& res = P_ActivePlayer()->playerResources;

		for (int i = 0; i < 7; ++i)
			if (backup.begin()[i] > 0 && res.begin()[i] < 0)
				res.begin()[i] = INT_MAX;
	}
	return r;
}

/////////////////////////////////////////////////////
// Primary skill overflow
/////////////////////////////////////////////////////

/*
 *
 * This hook sets $gameStart_flag when heroes are gaining levels at the start of the game.
 * In these cases, primary skill overflow is not active.
 *
 */
int __stdcall _HH_StartupLevelUpPrimaryFlag(HiHook *h, int This)
{
	LOG_HIHOOK;
	GGameFlags.gameStart = TRUE;
	int r = THISCALL_1(int, h->GetDefaultFunc(),This);
	GGameFlags.gameStart = FALSE;
	return r;
}

/*
 *
 * This hook prevents overflow of primary skills during level up. It only triggers
 * if the PSkill was just "increased" to -128
 *
 */
_LHF_(LevelUpPrimary_OF) // for level up
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow && !GGameFlags.gameStart)
	{
		BYTE primary = c->AL();
		if (primary == 0x80) // only activate when going from +127 to -128
			return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from artifacts. It only triggers
 * if you currently have positive PSkill and if the artifact bonus is also positive.
 *
 */
_LHF_(ArtifactPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->CL();
		BYTE artifact = c->DL();
		if (primary > 0x7F && artifact <= 0x7F && (primary - artifact) <= 0x7F)
			c->ecx = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills when visiting a Wandering Scholar.
 * It only triggers if the PSkill is about to increase from +127 to -128.
 *
 */
_LHF_(ScholarPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)c->ebx;
		if (hero->primarySkill[c->edi] == 127)
			return NO_EXEC_DEFAULT; // don't increase
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills when opening Pandora's Box or visiting an Event.
 * It will not trigger if your PSKill is precisely at 127, to allow some freedom for mapmakers.
 *
 */
_LHF_(PandoraPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = ByteAt(c->ebx + c->eax + 0x476);
		BYTE increase = c->CL();
		if (increase != 127)  // overflow allowed if increase is precisely 127
		{
			if (primary <= 0x7F && (primary + increase) > 0x7F)
				c->ecx = (0x7F - primary);
		}
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from relics. It only triggers
 * if you currently have positive PSkill and if the artifact bonus is also positive.
 *
 */
_LHF_(RelicPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		BYTE increase = c->DL();
		if (primary <= 0x7F && increase <= 0x7F && (primary + increase) > 0x7F)
			c->edx = (0x7F - primary);
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills when collecting rewards from Seer Huts.
 *
 */
_LHF_(SeerPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->BL();
		BYTE increase = c->DL();
		if (primary > 0x7F && increase <= 0x7F && (primary - increase) <= 0x7F)
			c->ebx = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills when visiting Arenas.
 * Only triggers at 126 or 127 which would overflow.
 *
 */
_LHF_(ArenaPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->CL();
		if (primary == 0x80 || primary == 0x81)
			c->ecx = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from School of Wars.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(SchoolOfWarPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		if (primary == 0x80)
			c->eax = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Mercenary Camps
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(MercenaryCampPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		if (primary == 0x80)
			c->eax = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Schools of Magic.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(SchoolOfMagicPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->BL();
		if (primary == 0x80)
			c->ebx = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Gardens of Knowledge.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(GardenOfKnowledgePrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		if (primary == 0x80)
			c->eax = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Star Axes.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(StarAxisPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		if (primary == 0x80)
			c->eax = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Marletto Towers.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(MarlettoTowerPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		if (primary == 0x80)
			c->eax = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Wall of Knowledge.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(WallOfKnowledgePrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->BL();
		if (primary == 0x80)
			c->ebx = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Order of Fire.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(OrderOfFirePrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->BL();
		if (primary == 0x80)
			c->ebx = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Hall of Valhalla.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(HallOfValhallaPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		if (primary == 0x80)
			c->eax = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Cage of Warlords.
 * Only triggers at -128 meaning overflow has just occured.
 *
 */
_LHF_(CageOfWarlordsPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		BYTE primary = c->AL();
		if (primary == 0x80)
			c->eax = 0x7F;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Libraries of Enlightenment.
 * Only triggers at 126 or 127 which would overflow.
 *
 */
_LHF_(LibraryOfEnlightenmentPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)(c->esi);

		for (int i = 0; i < 4; i++)
		{
			if (hero->primarySkill[i] == 126 || hero->primarySkill[i] == 127)
				hero->primarySkill[i] = 127;
			else
				hero->primarySkill[i] += 2;
		}
		c->return_address = 0x4A2FCC;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Brimstone Clouds.
 * Only triggers at 126 or 127 which would overflow.
 *
 */
_LHF_(BrimstoneCloudsPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)(c->edx);
		if (hero->primarySkill[2] == 127 || hero->primarySkill[2] == 126)
			return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Earth Guardian.
 * Only triggers between 116 and 127 as the bonus is +12.
 *
 */
_LHF_(EarthGuardianPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)(c->edx);
		if (hero->primarySkill[2] <= 0x7F && hero->primarySkill[2] >= 0x74)
			return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Warlord's Monument.
 * Only triggers between 108 and 127 as the bonus is +20.
 *
 */
_LHF_(WarlordsMonumentPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)(c->edx);
		if (hero->primarySkill[0] <= 0x7F && hero->primarySkill[0] >= 0x6C)
			return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Blood Obelisk.
 * Only triggers between 126 and 127 as the bonus is +2.
 *
 */
_LHF_(BloodObeliskPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)(c->eax);
		if (hero->primarySkill[0] <= 0x7F && hero->primarySkill[0] >= 0x7E)
			return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Glyphs of Fear.
 * Only triggers between 126 and 127 as the bonus is +2.
 *
 */
_LHF_(GlyphsOfFear_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)(c->edx);
		if (hero->primarySkill[1] <= 0x7F && hero->primarySkill[1] >= 0x7E)
			return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

/*
 *
 * This hook prevents overflow of primary skills from Carnivorous Plant.
 * Only triggers between 118 and 127 as the bonus is +10.
 *
 */
_LHF_(CarnivorousPlantPrimary_OF)
{
	LOG_LOHOOK;
	if (!F_Multiplayer() && FOptions.primary_overflow)
	{
		H3Hero *hero = (H3Hero*)(c->eax);
		if ((UINT8)hero->primarySkill[1] > 0x7F || (UINT8)hero->primarySkill[1] < 0x75)
			hero->primarySkill[1] += 10;
		if ((UINT8)hero->primarySkill[0] > 0x7F || (UINT8)hero->primarySkill[0] < 0x75)
			hero->primarySkill[0] += 10;

		c->return_address = 0x463A98;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}


//////////////////////////////////////////////////////////////////////////
// Creature overflow
//////////////////////////////////////////////////////////////////////////

/*
 *
 * These hooks prevent stacks of more tha 32,767 creatures to overflow into negative values.
 * A much simpler fix exists but this was simplest for SoD_SP's scope given
 * HDmod's current way of patching.
 *
 */

static naked_t bridge_creatureOF1;

_H3API_NAKED_FUNCTION_ CreatureOF1(void)
{
	static naked_t return_creatureOF1 = reinterpret_cast<naked_t>(0x44AA5F);

	__asm PUSHFD
	__asm PUSHAD
	if (!F_Multiplayer() || !bridge_creatureOF1)
	{
		if (FOptions.creatures_overflow) // overflow on
		{
			__asm POPAD
			__asm POPFD
			__asm MOV EDI, DWORD PTR DS : [EAX * 4 + ECX + 0x1C]
			__asm MOV DWORD PTR DS : [EAX * 4 + ECX + 0x1C], EBX
			__asm MOV EAX, EDI
		}
		else // old way
		{
			__asm POPAD
			__asm POPFD
			__asm MOV DI, WORD PTR DS : [EAX * 4 + ECX + 0x1C] // old bug here
			__asm MOV DWORD PTR DS : [EAX * 4 + ECX + 0x1C], EBX
			__asm MOVSX EAX, DI
		}
		__asm MOV DWORD PTR DS : [ESI * 4 + EDX + 0x1C], EAX
		__asm JMP return_creatureOF1
	}
	__asm POPAD
	__asm POPFD
	__asm JMP bridge_creatureOF1
}

static naked_t bridge_creatureOF2;
_H3API_NAKED_FUNCTION_ CreatureOF2(void)
{
	static naked_t return_creatureOF2 = reinterpret_cast<naked_t>(0x42D92D);

	__asm PUSHFD
	__asm PUSHAD
	if (!F_Multiplayer() || !bridge_creatureOF2)
	{
		if (FOptions.creatures_overflow) // overflow on
		{
			__asm POPAD
			__asm POPFD
			__asm MOV EDX, DWORD PTR DS : [ESI + 0x1C]
			__asm MOV DWORD PTR SS : [EBP - 0x24], EAX
			__asm MOV DWORD PTR SS : [EBP - 0x1C], EDX
		}
		else // old way
		{
			__asm POPAD
			__asm POPFD
			__asm MOV DX, WORD PTR DS : [ESI + 0x1C]
			__asm MOV DWORD PTR SS : [EBP - 0x24], EAX
			__asm MOV WORD PTR SS : [EBP - 0x1C], DX
		}
		__asm JMP return_creatureOF2
	}
	__asm POPAD
	__asm POPFD
	__asm JMP bridge_creatureOF2
}


static naked_t bridge_creatureOF3;

_H3API_NAKED_FUNCTION_ CreatureOF3(void)
{
	static naked_t return_creatureOF3 = reinterpret_cast<naked_t>(0x42DA3E);

	__asm PUSHFD
	__asm PUSHAD
	if (!F_Multiplayer() || !bridge_creatureOF3)
	{
		if (FOptions.creatures_overflow) // overflow on
		{
			__asm POPAD
			__asm POPFD
			__asm MOV ECX, DWORD PTR DS : [EBP - 0x1C]
		}
		else // old way
		{
			__asm POPAD
			__asm POPFD
			__asm MOVSX ECX, WORD PTR SS : [EBP - 0x1C]
		}
		__asm PUSH EDI
		__asm JMP return_creatureOF3
	}
	__asm POPAD
	__asm POPFD
	__asm JMP bridge_creatureOF3
}

static naked_t bridge_creatureOF4;
_H3API_NAKED_FUNCTION_ CreatureOF4(void)
{
	static naked_t return_creatureOF4 = reinterpret_cast<naked_t>(0x42DADE);

	__asm PUSHFD
	__asm PUSHAD
	if (!F_Multiplayer() || !bridge_creatureOF4)
	{
		if (FOptions.creatures_overflow) // overflow on
		{
			__asm POPAD
			__asm POPFD
			__asm MOV ECX, DWORD PTR DS : [EBP - 0x1C]
		}
		else // old way
		{
			__asm POPAD
			__asm POPFD
			__asm MOVSX ECX, WORD PTR SS : [EBP - 0x1C]
		}
		__asm PUSH EDI
		__asm JMP return_creatureOF4
	}
	__asm POPAD
	__asm POPFD
	__asm JMP bridge_creatureOF4
}

// * both an overflow and underflow
void __stdcall _HH_Whirlpool_OF(HiHook& h, PH3Hero hero)
{
	if (!FOptions.creatures_overflow)
		return STDCALL_1(void, h(), hero);

	if (!P_Main()->IsHuman(hero->owner))
		return;

	if (hero->WearsArtifact(H3Artifact::ADMIRALS_HAT))
		return;

	INT number_stacks = hero->army.GetStackCount();
	if (number_stacks == 0)
		return;

	// * originally code sets this as 99,999,999 which is "easily" overflowable
	UINT64 min_power = UINT64_MAX;
	UINT weakest_index = -1;

	H3Army& army = hero->army;

	for (UINT i = 0; i < 7; ++i)
	{
		H3Army::iterator it = army[i];
		if (it.Count() > 0)
		{
			UINT64 stack_power = UINT64(it.Count()) * UINT64(P_Creatures()[it.Type()].fightValue);
			if (stack_power < min_power)
			{
				weakest_index = i;
				min_power = stack_power;
			}
		}
	}
	// * there is no such check in original code
	// * the -1th creature count happens to be the 7th creature's id
	// * which would be divided by 2
	if (weakest_index == -1)
		return;
	INT32& count = hero->army[weakest_index].Count();
	count >>= 1;
	if (count == 0)
	{
		if (number_stacks == 1)
			count = 1;
		else
			army.type[weakest_index] = -1;
	}

	F_MessageBox(P_AdveventText->GetText(168 + 1));
}

void overflow_init(PatcherInstance * pi)
{
	///////////////////////////////////
	// resources overflow
	///////////////////////////////////
	pi->WriteLoHook(0x4C7EAD, DailyResources_OF);
	pi->WriteLoHook(0x4E38A6, MapResources_OF);
	pi->WriteLoHook(0x4CD43E, EventResources_OF);
	pi->WriteLoHook(0x5ED47B, MarketResources_OF);
	pi->WriteHiHook(0x5EE360, SPLICE_, THISCALL_, _HH_ArtifactMerchantSell_OF);

	///////////////////////////////////
	// primary skill overflow
	///////////////////////////////////
	pi->WriteHiHook(0x4BFCF7, CALL_, THISCALL_, _HH_StartupLevelUpPrimaryFlag);
	pi->WriteLoHook(0x4DAB67, LevelUpPrimary_OF);
	pi->WriteLoHook(0x4E2DFE, ArtifactPrimary_OF);
	pi->WriteLoHook(0x4A4B7F, ScholarPrimary_OF);
	pi->WriteLoHook(0x49F8A2, PandoraPrimary_OF);
	pi->WriteLoHook(0x4E2D73, RelicPrimary_OF);
	pi->WriteLoHook(0x574157, SeerPrimary_OF);
	pi->WriteLoHook(0x49E543, ArenaPrimary_OF);
	pi->WriteLoHook(0x4A786E, SchoolOfWarPrimary_OF);
	pi->WriteLoHook(0x4A35B0, MercenaryCampPrimary_OF);
	pi->WriteLoHook(0x4A31D4, SchoolOfMagicPrimary_OF);
	pi->WriteLoHook(0x4A2410, GardenOfKnowledgePrimary_OF);
	pi->WriteLoHook(0x4A3AC0, StarAxisPrimary_OF);
	pi->WriteLoHook(0x4A1D50, MarlettoTowerPrimary_OF);
	pi->WriteLoHook(0x5BDEA0, WallOfKnowledgePrimary_OF);
	pi->WriteLoHook(0x5BDF55, OrderOfFirePrimary_OF);
	pi->WriteLoHook(0x5BE143, OrderOfFirePrimary_OF);
	pi->WriteLoHook(0x5BE224, CageOfWarlordsPrimary_OF);
	pi->WriteLoHook(0x4A2F92, LibraryOfEnlightenmentPrimary_OF);
	pi->WriteLoHook(0x463976, BrimstoneCloudsPrimary_OF);
	pi->WriteLoHook(0x4639A4, EarthGuardianPrimary_OF);
	pi->WriteLoHook(0x4639D2, WarlordsMonumentPrimary_OF);
	pi->WriteLoHook(0x463A2F, BloodObeliskPrimary_OF);
	pi->WriteLoHook(0x4639FC, GlyphsOfFear_OF);
	pi->WriteLoHook(0x463A64, CarnivorousPlantPrimary_OF);

	//////////////////////////////////////////////////
	// creature overflow at 32767
	//////////////////////////////////////////////////
	if (ByteAt(0x44AA4F) == H3Patcher::mnemonics::JMP)
		bridge_creatureOF1 = (naked_t)FuncAt(0x44AA4F);
	H3Patcher::NakedHook5(0x44AA4F, CreatureOF1);
	if (ByteAt(0x42D922) == H3Patcher::mnemonics::JMP)
		bridge_creatureOF2 = (naked_t)FuncAt(0x42D922);
	H3Patcher::NakedHook5(0x42D922, CreatureOF2);
	if (ByteAt(0x42DA39) == H3Patcher::mnemonics::JMP)
		bridge_creatureOF3 = (naked_t)FuncAt(0x42DA39);
	H3Patcher::NakedHook5(0x42DA39, CreatureOF3);
	if (ByteAt(0x42DAD9) == H3Patcher::mnemonics::JMP)
		bridge_creatureOF4 = (naked_t)FuncAt(0x42DAD9);
	H3Patcher::NakedHook5(0x42DAD9, CreatureOF4);

	//////////////////////////////////////////////////
	// Whirlpool creature~index overflow
	//////////////////////////////////////////////////
	pi->WriteHiHook(0x4AC790, SPLICE_, STDCALL_, _HH_Whirlpool_OF);
}