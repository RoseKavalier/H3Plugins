/*
 *
 * These hooks were modified from the plugin by igrik, used with permission.
 * http://forum.df2.ru/index.php?showtopic=30848&view=findpost&p=743178
 *
 * This adds automatic creature upgrade by clicking on creature portraits
 * while holding down the 'A' key.
 *
 */

#include <H3API.hpp>
#include "TownUpgradeHotkey.hpp"
#include "sodsp/Log.hpp"

using namespace h3;

constexpr CHAR TownUpgradeHotkey = 'A';

 /*
  *
  * This function attempts to upgrade the stack of an army at the index position.
  * Returns TRUE if upgrade was sucessful.
  *
  */
BOOL UpgradeArmyStack(H3Army *army, H3Town *town, H3Player *me, INT32 index, BOOL individual = FALSE)
{
	int type = army->type[index];
	if (type == -1)
		return FALSE;
	if (!individual && type == NH3Creatures::SKELETON)
		return FALSE;
	int upg_type = F_GetCreatureUpgrade(type);
	if (upg_type == -1)
		return FALSE;
	H3CreatureInformation *c_info = P_Creatures()(type);
	if (c_info->town != town->type)
		return FALSE;
	if (!town->IsBuildingBuilt(H3Town::B_DWELL1U + c_info->level))
		return FALSE;
	H3Resources& player_res = me->playerResources;
	H3Resources cost = c_info->UpgradeCost(P_Creatures()(upg_type), army->count[index]);
	if (player_res < cost)
		return FALSE;
	player_res -= cost;
	army->type[index] = upg_type;
	return TRUE;
}

/*
 *
 * This function gets the relevant H3Army structure (if any) to attempt autoupgrade.
 * Returns TRUE if at least one upgrade was done.
 *
 */
BOOL TryToUpgrade(H3Town *town, int click_id)
{
	BOOL r = FALSE;
	H3Army *army;
	H3Main *main = P_Main();
	H3Player *me = main->GetPlayer();
	if (me == P_ActivePlayer() && me->ownerID == town->owner)
	{
		if (click_id >= 115 && click_id <= 121) // garrison creatures
		{
			if (H3Hero *hero = main->GetHero(town->garrisonHero))
				r = UpgradeArmyStack(&hero->army, town, me, click_id - 115, TRUE); // if no hero then there are no creatures here!
			else
				r = UpgradeArmyStack(&town->Guards, town, me, click_id - 115, TRUE); // if no hero then there are no creatures here!
		}
		else if (click_id >= 140 && click_id <= 146) // visiting creatures
		{
			if (H3Hero *hero = main->GetHero(town->visitingHero))
				r = UpgradeArmyStack(&hero->army, town, me, click_id - 140, TRUE); // if no hero then there are no creatures here!
		}
		else if (click_id == 123) // garrison hero portrait
		{
			if (H3Hero *hero = main->GetHero(town->garrisonHero))
				army = &hero->army;
			else
				army = &town->Guards;
			for (int i = 0; i < 7; i++)
				r += UpgradeArmyStack(army, town, me, i);
		}
		else if (click_id == 125) // visiting hero portrait
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
	if (!F_Multiplayer() && GetKeyState(TownUpgradeHotkey) < 0)
	{
		if (H3Town *town = P_TownMgr()->town)
		{
			int click_id = c->edi;

			if (TryToUpgrade(town, click_id)) // if at least one upgrade was successful, redraw Town dialog
			{
				P_TownMgr()->Draw();
				P_TownMgr()->RefreshScreen();
				c->return_address = 0x5D460F;
				return NO_EXEC_DEFAULT;
			}
		}
	}
	return EXEC_DEFAULT;
}

void town_upgrade_hotkey_init(PatcherInstance * pi)
{
	pi->WriteLoHook(0x5D45FD, QuickUpgradeInTown);
}
