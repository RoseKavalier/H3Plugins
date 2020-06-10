#include "patcher_x86.hpp"
#include "varia/GetDLLInfo.hpp"
#include "varia/Fixes.hpp"
#include "igrikPlugins/BattleSpeed.hpp"
#include "igrikPlugins/spell_morale_luck_display.hpp"
#include "igrikPlugins/TownUpgradeHotkey.hpp"
#include "varia/improvements.hpp"
#include "varia/overflow.hpp"
#include "hotkeys/hotkeys.hpp"
#include "Versions.hpp"
#include "sodsp/versionCheck.hpp"
#include "OnEvent/OnEventHooks.hpp"

void hooks_init(PatcherInstance * pi)
{
	// collects various information on other running H3 DLL
	GetDllInfoInit(pi);
	// various bug fixes of Heroes3
	fixes_init(pi);
	// adds functionality that does not disrupt vanilla gameplay
	improvements_init(pi);
	// prevents overflow of creatures, primary skills, resources
	overflow_init(pi);
	// adds 10 speed buttons instead of 3
	battle_speed_init(pi);
	// shows spell duration on icons, as well as morale and luck
	spell_morale_luck_display_init(pi);
	// allows click-upgrade of creatures in town
	town_upgrade_hotkey_init(pi);

	/////////////////////////////////////////////////////
	// The following hooks shall remain private
	/////////////////////////////////////////////////////

	// various events during gameplay
	OnEventHooks_init(pi);
	// adds new hotkeys in various spots
	hotkeys_init(pi);
	// version 1.13+ hooks are stored in this fashion
	versions_init(pi);
	// check if a new version of SoD_SP exists
	versionCheck_init(pi);
}
