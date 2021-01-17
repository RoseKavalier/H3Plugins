#pragma once

#include <Plugin.hpp>
#include <H3API.hpp>

/**
 * Uncomment to show an error message when failing to link up with patcher_x86
 */
//#define SHOW_ERROR_MESSAGE_ON_FAIL

/**
 * @brief A derived Plugin that constructs itself
 */
class BattlefieldsPlugin : public Plugin
{
public:
	BattlefieldsPlugin() : Plugin()
	{
		Status status = Init("H3.Battlefields");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.Battlefields", status);
#endif
	}

	static BattlefieldsPlugin& GetPlugin();

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================

	int NewBattleGrounds(HookContext& c);

private:
	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================
	static constexpr UINT SCENE_COUNT = 20;
	INT32 m_minScene;

	struct CombatScenes
	{
		INT32 count;
		LPCSTR name;
	}m_customScenes[SCENE_COUNT] =
	{
		{ 0, "Lava"      },
		{ 0, "Subterra"  },
		{ 0, "Rough"     },
		{ 0, "Swamp"     },
		{ 0, "Snow"      },
		{ 0, "Grass"     },
		{ 0, "Desert"    },
		{ 0, "Dirt"      },
		{ 0, "Clouds"    },
		{ 0, "Rocklands" },
		{ 0, "Fiery"     },
		{ 0, "Lucid"     },
		{ 0, "Clover"    },
		{ 0, "EvilFog"   },
		{ 0, "Holy"      },
		{ 0, "Cursed"    },
		{ 0, "Magic"     },
		{ 0, "Coast"     },
		{ 0, "Deck"      },
		{ 0, "Boat"      },
	};

	CHAR m_buffer[32];

	bool ReadIni();
};