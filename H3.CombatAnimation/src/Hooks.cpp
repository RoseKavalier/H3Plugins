#include "Hooks.h"

using namespace h3;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// * milliseconds
constexpr INT TIME_BETWEEN_ANIMATION = 95;

int __stdcall _HH_CycleCombatScreen(HiHook *h, H3CombatManager *combat)
{
	// can't use the default creature time reference
	// it would prevent random animations
	static DWORD last_animations[2][21];

	for (int side = 0; side < 2; ++side)
	{
		// only consider creatures on battlefield
		for (int i = 0; i < combat->heroMonCount[side] && i < 20; ++i)
		{
			auto mon = &combat->stacks[side][i];
			// under these conditions, a creature should not be animated
			if (mon->type == NH3Creatures::ARROW_TOWER
				|| mon->info.flags.CANNOT_MOVE
				|| mon->activeSpellsDuration[H3Spell::BLIND]
				|| mon->activeSpellsDuration[H3Spell::PARALYZE]
				|| mon->activeSpellsDuration[H3Spell::STONE]
				|| mon->numberAlive == 0
				)
				continue;

			// if undergoing a current animation
			if (mon->animation != H3LoadedDef::CG_STANDING)
				continue;

			auto def = mon->def;
			if (!def)
				continue;

			if (def->groupsCount <= 1)
				continue;
			// check the standing defgroup is loaded...
			if (!def->activeGroups[H3LoadedDef::CG_STANDING])
				continue;
			// ... and exists
			auto standing = def->groups[H3LoadedDef::CG_STANDING];
			if (!standing)
				continue;

			// check that enough time has elapsed since last animation
			DWORD time = F_GetTime();
			DWORD &last_animation = last_animations[side][i];
			if (time - last_animation < TIME_BETWEEN_ANIMATION)
				continue;

			// indicate that this creature's frame should be redrawn
			combat->RedrawCreatureFrame[side][i] = TRUE;
			// increase this creature's current frame animation
			++mon->animationFrame %= standing->count;
			// add a bit of randomness for the next animation time reference
			// helps to prevent syncing of similar creature stacks
			last_animation = time + F_MultiplayerRNG(0, 10);
		}
	}
	// draw and refresh creature animations
	combat->RefreshCreatures();
	combat->Refresh();

	return THISCALL_1(int, h->GetDefaultFunc(), combat);
}

_LHF_(ResetDrawingRequest)
{
	auto& cmb = P_CombatMgr();
	F_memset(cmb->RedrawCreatureFrame, 0, sizeof(cmb->RedrawCreatureFrame) + sizeof(cmb->heroAnimation) + sizeof(cmb->heroFlagAnimation));
	return EXEC_DEFAULT;
}

void Hooks_init(PatcherInstance *pi)
{
	pi->WriteHiHook(0x495C50, SPLICE_, THISCALL_, _HH_CycleCombatScreen);
	pi->WriteLoHook(0x4631E6, ResetDrawingRequest);
}