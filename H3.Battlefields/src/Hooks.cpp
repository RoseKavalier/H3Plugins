#include "Hooks.h"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

INT minScene;

// * a text buffer to print the scene name
CHAR sceneBuff[32];

// * default background addresses
enum eCombatBackgrounds
{
	CmBkLava_pcx = 0x66D048, // Lava
	CmBkSub_pcx  = 0x66D058, // Subterranean
	CmBkRgh_pcx  = 0x66D064, // Rough
	CmBkSwmp_pcx = 0x66D070, // Swamp
	CmBkSnMt_pcx = 0x66D080, // Snow
	CmBkSnTr_pcx = 0x66D090, // Snow
	CmBkGrMt_pcx = 0x66D0A0, // Grass
	CmBkGrTr_pcx = 0x66D0B0, // Grass
	CmBkDes_pcx  = 0x66D0C0, // Sand
	CmBkDrTr_pcx = 0x66D0CC, // Dirt
	CmBkDrMt_pcx = 0x66D0DC, // Dirt
	CmBkDrDd_pcx = 0x66D0EC, // Dirt
	CmBkMC_pcx   = 0x66D0FC, // Magic Clouds
	CmBkRK_pcx   = 0x66D108, // Rocklands
	CmBkFF_pcx   = 0x66D114, // Fiery Field
	CmBkLP_pcx   = 0x66D120, // Lucid Pools
	CmBkCF_pcx   = 0x66D12C, // Clover field
	CmBkEF_pcx   = 0x66D138, // Evil Fog
	CmBkHG_pcx   = 0x66D144, // Holy Grounds
	CmBkCur_pcx  = 0x66D150, // Cursed ground
	CmBkMag_pcx  = 0x66D15C, // Magic Plains
	CmBkBch_pcx  = 0x66FF40, // Coast
	CmBkDeck_pcx = 0x66FF4C, // Land vs Boat
	CmBkBoat_pcx = 0x66FF5C, // Boat v Boat
};

// * index value of terrains used here
enum eTerrainIndex
{
	TI_LAVA,
	TI_SUBTERRA,
	TI_ROUGH,
	TI_SWAMP,
	TI_SNOW,
	TI_GRASS,
	TI_DESERT,
	TI_DIRT,
	TI_CLOUDS,
	TI_ROCKLANDS,
	TI_FIERY,
	TI_LUCID,
	TI_CLOVER,
	TI_EVILFOG,
	TI_HOLY,
	TI_CURSED,
	TI_MAGIC,
	TI_COAST,
	TI_DECK,
	TI_BOAT,
};

// * structure to hold all custom data
H3CombatScenes CustomScenes[SCENE_COUNT] =
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

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

_LHF_(NewBattleGrounds)
{
	INT sceneID;

	using cb = eCombatBackgrounds;
	using ti = eTerrainIndex;

	// * extract scene type
	switch (c->eax)
	{
	case cb::CmBkLava_pcx:
		sceneID = ti::TI_LAVA;
		break;
	case cb::CmBkSub_pcx:
		sceneID = ti::TI_SUBTERRA;
		break;
	case cb::CmBkRgh_pcx:
		sceneID = ti::TI_ROUGH;
		break;
	case cb::CmBkSwmp_pcx:
		sceneID = ti::TI_SWAMP;
		break;
	case cb::CmBkSnMt_pcx:
	case cb::CmBkSnTr_pcx:
		sceneID = ti::TI_SNOW;
		break;
	case cb::CmBkGrMt_pcx:
	case cb::CmBkGrTr_pcx:
		sceneID = ti::TI_GRASS;
		break;
	case cb::CmBkDes_pcx:
		sceneID = ti::TI_DESERT;
		break;
	case cb::CmBkDrTr_pcx:
	case cb::CmBkDrMt_pcx:
	case cb::CmBkDrDd_pcx:
		sceneID = ti::TI_DIRT;
		break;
	case cb::CmBkMC_pcx:
		sceneID = ti::TI_CLOUDS;
		break;
	case cb::CmBkRK_pcx:
		sceneID = ti::TI_ROCKLANDS;
		break;
	case cb::CmBkFF_pcx:
		sceneID = ti::TI_FIERY;
		break;
	case cb::CmBkLP_pcx:
		sceneID = ti::TI_LUCID;
		break;
	case cb::CmBkCF_pcx:
		sceneID = ti::TI_CLOVER;
		break;
	case cb::CmBkEF_pcx:
		sceneID = ti::TI_EVILFOG;
		break;
	case cb::CmBkHG_pcx:
		sceneID = ti::TI_HOLY;
		break;
	case cb::CmBkCur_pcx:
		sceneID = ti::TI_CURSED;
		break;
	case cb::CmBkMag_pcx:
		sceneID = ti::TI_MAGIC;
		break;
	case cb::CmBkBch_pcx:
		sceneID = ti::TI_COAST;
		break;
	case cb::CmBkDeck_pcx:
		sceneID = ti::TI_DECK;
		break;
	case cb::CmBkBoat_pcx:
		sceneID = ti::TI_BOAT;
		break;
	default:
		return EXEC_DEFAULT;
	}

	// * only trigger if there is a custom background
	if (INT maxValue = CustomScenes[sceneID].count)
	{
		// * pick a random scene (or not, depends on user choice)
		INT randScene = H3Random::RandBetween(minScene, maxValue);
		// * the scene is not default
		if (randScene)
		{
			sprintf(sceneBuff, "%s%02d.pcx", CustomScenes[sceneID].name, randScene);
			c->eax = (int)sceneBuff;
		}
	}

	return EXEC_DEFAULT;
}

void Hooks_init(PatcherInstance *pi)
{
	// * not using h3's random function in order
	// * to avoid contaminating battle rng seed
	srand(F_GetTime());

	pi->WriteLoHook(0x463833, NewBattleGrounds);
}