/*
 *
 * This page was modified from the plugin by igrik, used with permission.
 * http://forum.df2.ru/index.php?showtopic=30848&view=findpost&p=743178
 *
 * This adds automatic creature upgrade by clicking on creature portraits
 * while holding down the 'A' key.
 *
 */

#include "TownUpgradeHotkey.h"

#define TownUpgradeHotkey 'A'

 /*
  *
  * This function attempts to upgrade the stack of an army at the index position.
  * Returns TRUE if upgrade was sucessful.
  *
  */
BOOL UpgradeArmyStack(H3Army *army, H3Town *town, H3Player *me, INT32 index)
{
	int type = army->type[index];
	if (type == -1 || type == NH3Creatures::SKELETON)
		return FALSE;
	int upgType = h3_GetCreatureUpgrade(type);
	if (upgType == -1)
		return FALSE;
	H3CreatureInformation *cInfo = &P_Creatures[type];
	if (cInfo->town != town->type)
		return FALSE;
	if (!town->IsBuildingBuilt(H3Town::B_DWELL1U + cInfo->level))
		return FALSE;
	H3Resources cost, *pRes = &me->playerResources;
	cInfo->UpgradeCost(&cost, &P_Creatures[upgType], army->count[index]);
	if (!pRes->EnoughResources(&cost))
		return FALSE;
	pRes->RemoveResources(&cost);
	army->type[index] = upgType;
	return TRUE;
}

/*
 *
 * This function gets the relevant H3Army structure (if any) to attempt autoupgrade.
 * Returns TRUE if at least one upgrade was done.
 *
 */
BOOL TryToUpgrade(H3Town *town, int clickID)
{
	BOOL r = FALSE;
	H3Army *army;
	H3Main *main = P_Main;
	H3Player *me = main->GetPlayer();
	if (me == h3_ActivePlayer && me->ownerID == town->owner)
	{
		if (clickID >= 115 && clickID <= 121) // garrison creatures
		{
			if (H3Hero *hero = main->GetHero(town->garrisonHero))
				r = UpgradeArmyStack(&hero->army, town, me, clickID - 115); // if no hero then there are no creatures here!
			else
				r = UpgradeArmyStack(&town->Guards, town, me, clickID - 115); // if no hero then there are no creatures here!
		}
		else if (clickID >= 140 && clickID <= 146) // visiting creatures
		{
			if (H3Hero *hero = main->GetHero(town->visitingHero))
				r = UpgradeArmyStack(&hero->army, town, me, clickID - 140); // if no hero then there are no creatures here!
		}
		else if (clickID == 123) // garrison hero portrait
		{
			if (H3Hero *hero = main->GetHero(town->garrisonHero))
				army = &hero->army;
			else
				army = &town->Guards;
			for (int i = 0; i < 7; i++)
				r += UpgradeArmyStack(army, town, me, i);
		}
		else if (clickID == 125) // visiting hero portrait
		{
			if (H3Hero *hero = main->GetHero(town->visitingHero))  // if no hero then there are no creatures here!
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
	if (!multiplayer_game && GetKeyState(TownUpgradeHotkey) < 0)
	{
		if (H3Town *town = P_TownMgr->town)
		{
			int clickID = c->edi;

			if (TryToUpgrade(town, clickID)) // if at least one upgrade was successful, redraw Town dialog
			{
				P_TownMgr->Draw();
				P_TownMgr->RefreshScreen();
				c->return_address = 0x5D460F;
				LOG_LOHOOK;
				return NO_EXEC_DEFAULT;
			}
		}
	}
	LOG_LOHOOK;
	return EXEC_DEFAULT;
}

void town_upgrade_hotkey_init(PatcherInstance * pi)
{
	pi->WriteLoHook(0x5D45FD, QuickUpgradeInTown);
}