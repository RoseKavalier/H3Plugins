//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//          In preparing these files, several sources were          //
//            consulted, they are listed in no particular           //
//                          order below.                            //
//                                                                  //
//  Source: https://github.com/potmdehex/homm3tools                 //
//  Author: potmdehex and contributors                              //
//                                                                  //
//  Source: https://github.com/redxu/HoMM3_FA                       //
//  Author: redxu                                                   //
//                                                                  //
//  Source: https://github.com/openhomm/openhomm                    //
//  Author: Ershov Stanislav, Fomin Roman, Akulich Alexander        //
//                                                                  //
//  Source: https://github.com/GrayFace/wog                         //
//  Author: GrayFace and WoG team                                   //
//                                                                  //
//  Source: https://github.com/ethernidee/era                       //
//  Author: Berserker                                               //
//                                                                  //
//  Source: https://github.com/ethernidee/era-editor                //
//  Author: Grayface and Berserker                                  //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=3900      //
//  Author: Slava and GrayFace                                      //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=4583      //
//  Author: gamecreator                                             //
//                                                                  //
//  Thanks: patcher_x86 by baratorch and code therein               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3CONSTANTS_H_
#define _H3CONSTANTS_H_

#pragma once

#pragma warning(push)
#pragma warning(disable:4146) // disable unary minus operator unsigned type warning

namespace NH3Creatures
{
	enum eH3Creatures : INT32
	{
		PIKEMAN             = 0,
		HALBERDIER          = 1,
		ARCHER              = 2,
		MARKSMAN            = 3,
		GRIFFIN             = 4,
		ROYAL_GRIFFIN       = 5,
		SWORDSMAN           = 6,
		CRUSADER            = 7,
		MONK                = 8,
		ZEALOT              = 9,
		CAVALIER            = 10,
		CHAMPION            = 11,
		ANGEL               = 12,
		ARCHANGEL           = 13,
		CENTAUR             = 14,
		CENTAUR_CAPTAIN     = 15,
		DWARF               = 16,
		BATTLE_DWARF        = 17,
		WOOD_ELF            = 18,
		GRAND_ELF           = 19,
		PEGASUS             = 20,
		SILVER_PEGASUS      = 21,
		DENDROID_GUARD      = 22,
		DENDROID_SOLDIER    = 23,
		UNICORN             = 24,
		WAR_UNICORN         = 25,
		GREEN_DRAGON        = 26,
		GOLD_DRAGON         = 27,
		GREMLIN             = 28,
		MASTER_GREMLIN      = 29,
		STONE_GARGOYLE      = 30,
		OBSIDIAN_GARGOYLE   = 31,
		STONE_GOLEM         = 32,
		IRON_GOLEM          = 33,
		MAGE                = 34,
		ARCH_MAGE           = 35,
		GENIE               = 36,
		MASTER_GENIE        = 37,
		NAGA                = 38,
		NAGA_QUEEN          = 39,
		GIANT               = 40,
		TITAN               = 41,
		IMP                 = 42,
		FAMILIAR            = 43,
		GOG                 = 44,
		MAGOG               = 45,
		HELL_HOUND          = 46,
		CERBERUS            = 47,
		DEMON               = 48,
		HORNED_DEMON        = 49,
		PIT_FIEND           = 50,
		PIT_LORD            = 51,
		EFREETI             = 52,
		EFREET_SULTAN       = 53,
		DEVIL               = 54,
		ARCH_DEVIL          = 55,
		SKELETON            = 56,
		SKELETON_WARRIOR    = 57,
		WALKING_DEAD        = 58,
		ZOMBIE              = 59,
		WIGHT               = 60,
		WRAITH              = 61,
		VAMPIRE             = 62,
		VAMPIRE_LORD        = 63,
		LICH                = 64,
		POWER_LICH          = 65,
		BLACK_KNIGHT        = 66,
		DREAD_KNIGHT        = 67,
		BONE_DRAGON         = 68,
		GHOST_DRAGON        = 69,
		TROGLODYTE          = 70,
		INFERNAL_TROGLODYTE = 71,
		HARPY               = 72,
		HARPY_HAG           = 73,
		BEHOLDER            = 74,
		EVIL_EYE            = 75,
		MEDUSA              = 76,
		MEDUSA_QUEEN        = 77,
		MINOTAUR            = 78,
		MINOTAUR_KING       = 79,
		MANTICORE           = 80,
		SCORPICORE          = 81,
		RED_DRAGON          = 82,
		BLACK_DRAGON        = 83,
		GOBLIN              = 84,
		HOBGOBLIN           = 85,
		WOLF_RIDER          = 86,
		WOLF_RAIDER         = 87,
		ORC                 = 88,
		ORC_CHIEFTAIN       = 89,
		OGRE                = 90,
		OGRE_MAGE           = 91,
		ROC                 = 92,
		THUNDERBIRD         = 93,
		CYCLOPS             = 94,
		CYCLOPS_KING        = 95,
		BEHEMOTH            = 96,
		ANCIENT_BEHEMOTH    = 97,
		GNOLL               = 98,
		GNOLL_MARAUDER      = 99,
		LIZARDMAN           = 100,
		LIZARD_WARRIOR      = 101,
		GORGON              = 102,
		MIGHTY_GORGON       = 103,
		SERPENT_FLY         = 104,
		DRAGON_FLY          = 105,
		BASILISK            = 106,
		GREATER_BASILISK    = 107,
		WYVERN              = 108,
		WYVERN_MONARCH      = 109,
		HYDRA               = 110,
		CHAOS_HYDRA         = 111,
		AIR_ELEMENTAL       = 112,
		EARTH_ELEMENTAL     = 113,
		FIRE_ELEMENTAL      = 114,
		WATER_ELEMENTAL     = 115,
		GOLD_GOLEM          = 116,
		DIAMOND_GOLEM       = 117,
		PIXIE               = 118,
		SPRITE              = 119,
		PSYCHIC_ELEMENTAL   = 120,
		MAGIC_ELEMENTAL     = 121,
		NOT_USED1           = 122,
		ICE_ELEMENTAL       = 123,
		NOT_USED2           = 124,
		MAGMA_ELEMENTAL     = 125,
		NOT_USED3           = 126,
		STORM_ELEMENTAL     = 127,
		NOT_USED4           = 128,
		ENERGY_ELEMENTAL    = 129,
		FIREBIRD            = 130,
		PHOENIX             = 131,
		AZURE_DRAGON        = 132,
		CRYSTAL_DRAGON      = 133,
		FAERIE_DRAGON       = 134,
		RUST_DRAGON         = 135,
		ENCHANTER           = 136,
		SHARPSHOOTER        = 137,
		HALFLING            = 138,
		PEASANT             = 139,
		BOAR                = 140,
		MUMMY               = 141,
		NOMAD               = 142,
		ROGUE               = 143,
		TROLL               = 144,
		CATAPULT            = 145,
		BALLISTA            = 146,
		FIRST_AID_TENT      = 147,
		AMMO_CART           = 148,
		ARROW_TOWER         = 149,
	/* HotA */
		CANNON              = 150,
		SEA_DOG             = 151,
		HOTA_UNUSED         = 152,
		NYMPH               = 153,
		OCEANIDS            = 154,
		CREW_MATE           = 155,
		SEA_MAN             = 156,
		PIRATE              = 157,
		CORSAIR             = 158,
		STORMBIRD           = 159,
		AYSSID              = 160,
		SEA_WITCH           = 161,
		SORCERESS           = 162,
		NIX                 = 163,
		NIX_WARRIOR         = 164,
		SEA_SERPENT         = 165,
		HASPID              = 166,
		SATYR               = 167,
		FANGARM             = 168,
	};
}

namespace NH3Dispositions
{
	constexpr INT COMPLIANT	 = 0;
	constexpr INT FRIENDLY   = 1;
	constexpr INT AGGRESSIVE = 2;
	constexpr INT HOSTILE    = 3;
	constexpr INT SAVAGE     = 4;
}

namespace NH3Formats
{
	constexpr INT ROE = 0x0E;
	constexpr INT AB  = 0x15;
	constexpr INT SOD = 0x1C;
	constexpr INT CHR = 0x1D;
	constexpr INT WOG = 0x33;
}

namespace NH3Heroes
{
	enum eH3HeroClasses : INT32
	{
		KNIGHT       = 0,
		CLERIC       = 1,
		RANGER       = 2,
		DRUID        = 3,
		ALCHEMIST    = 4,
		WIZARD       = 5,
		DEMONIAC     = 6,
		HERETIC      = 7,
		DEATH_KNIGHT = 8,
		NECROMANCER  = 9,
		OVERLORD     = 10,
		WARLOCK      = 11,
		BARBARIAN    = 12,
		BATTLE_MAGE  = 13,
		BEASTMASTER  = 14,
		WITCH        = 15,
		PLANESWALKER = 16,
		ELEMENTALIST = 17,
	};

	enum eH3Heroes : INT32
	{
		/* Knight (Castle) */
		ORRIN        = 0,
		VALESKA      = 1,
		EDRIC        = 2,
		SYLVIA       = 3,
		LORD_HAART   = 4,
		SORSHA       = 5,
		CHRISTIAN    = 6,
		TYRIS        = 7,

		/* Cleric (Castle) */
		RION         = 8,
		ADELA        = 9,
		CUTHBERT     = 10,
		ADELAIDE     = 11,
		INGHAM       = 12,
		SANYA        = 13,
		LOYNIS       = 14,
		CAITLIN      = 15,

		/* Ranger (Rampart) */
		MEPHALA      = 16,
		UFRETIN      = 17,
		JENOVA       = 18,
		RYLAND       = 19,
		THORGRIM     = 20,
		IVOR         = 21,
		CLANCY       = 22,
		KYRRE        = 23,

		/* Druid (Rampart) */
		CORONIUS     = 24,
		ULAND        = 25,
		ELLESHAR     = 26,
		GEM          = 27,
		MALCOM       = 28,
		MELODIA      = 29,
		ALAGAR       = 30,
		AERIS        = 31,

		/* Alchemist (Tower) */
		PIQUEDRAM    = 32,
		THANE        = 33,
		JOSEPHINE    = 34,
		NEELA        = 35,
		TOROSAR      = 36,
		FAFNER       = 37,
		RISSA        = 38,
		IONA         = 39,

		/* Wizard (Tower) */
		ASTRAL       = 40,
		HALON        = 41,
		SERENA       = 42,
		DAREMYTH     = 43,
		THEODORUS    = 44,
		SOLMYR       = 45,
		CYRA         = 46,
		AINE         = 47,

		/* Demoniac (Inferno) */
		FIONA        = 48,
		RASHKA       = 49,
		MARIUS       = 50,
		IGNATIUS     = 51,
		OCTAVIA      = 52,
		CALH         = 53,
		PYRE         = 54,
		NYMUS        = 55,

		/* Heretic (Inferno) */
		AYDEN        = 56,
		XYRON        = 57,
		AXSIS        = 58,
		OLEMA        = 59,
		CALID        = 60,
		ASH          = 61,
		ZYDAR        = 62,
		XARFAX       = 63,

		/* Death Knight (Necropolis) */
		STRAKER      = 64,
		VOKIAL       = 65,
		MOANDOR      = 66,
		CHARNA       = 67,
		TAMIKA       = 68,
		ISRA         = 69,
		CLAVIUS      = 70,
		GALTHRAN     = 71,

		/* Necromancer (Necropolis) */
		SEPTIENNA    = 72,
		AISLINN      = 73,
		SANDRO       = 74,
		NIMBUS       = 75,
		THANT        = 76,
		XSI          = 77,
		VIDOMINA     = 78,
		NAGASH       = 79,

		/* Overlord (Dungeon) */
		LORELEI      = 80,
		ARLACH       = 81,
		DACE         = 82,
		AJIT         = 83,
		DAMACON      = 84,
		GUNNAR       = 85,
		SYNCA        = 86,
		SHAKTI       = 87,

		/* Warlock (Dungeon) */
		ALAMAR       = 88,
		JAEGAR       = 89,
		MALEKITH     = 90,
		JEDDITE      = 91,
		GEON         = 92,
		DEEMER       = 93,
		SEPHINROTH   = 94,
		DARKSTORN    = 95,

		/* Barbarian (Stronghold) */
		YOG          = 96,
		GURNISSON    = 97,
		JABARKAS     = 98,
		SHIVA        = 99,
		GRETCHIN     = 100,
		KRELLION     = 101,
		CRAG_HACK    = 102,
		TYRAXOR      = 103,

		/* Battle Mage (Stronghold) */
		GIRD         = 104,
		VEY          = 105,
		DESSA        = 106,
		TEREK        = 107,
		ZUBIN        = 108,
		GUNDULA      = 109,
		ORIS         = 100,
		SAURUG       = 111,

		/* Beastmaster (Fortress) */
		BRON         = 112,
		DRAKON       = 113,
		WYSTAN       = 114,
		TAZAR        = 115,
		ALKIN        = 116,
		KORBAC       = 117,
		GERWULF      = 118,
		BROGHILD     = 119,

		/* Witch (Fortress) */
		MIRLANDA     = 120,
		ROSIC        = 121,
		VOY          = 122,
		VERDISH      = 123,
		MERIST       = 124,
		STYG         = 125,
		ANDRA        = 126,
		TIVA         = 127,

		/* Planeswalker (Conflux) */
		PASIS        = 128,
		THUNAR       = 129,
		IGNISSA      = 130,
		LACUS        = 131,
		MONERE       = 132,
		ERDAMON      = 133,
		FIUR         = 134,
		KALT         = 135,

		/* Elementalist (Conflux) */
		LUNA         = 136,
		BRISSA       = 137,
		CIELE        = 138,
		LABETHA      = 139,
		INTEUS       = 140,
		AENAIN       = 141,
		GELARE       = 142,
		GRINDAN      = 143,

		/* Special  (Campaign) */
		SIR_MULLICH  = 144,
		ADRIENNE     = 145,
		CATHERINE    = 146,
		DRACON       = 147,
		GELU         = 148,
		KILGOR       = 149,
		LORD_HAART2  = 150,
		MUTARE       = 151,
		ROLAND       = 152,
		MUTARE_DRAKE = 153,
		BORAGUS      = 154,
		XERON        = 155,

		/* HotA*/
		BIDLEY       = 156,
		CORKES       = 157,
		JEREMY       = 158,
		ILLOR        = 159,
		ASTRA        = 160,
		DEREK        = 161,
		LEENA        = 162,
		TARK         = 163,
		EOVACIUS     = 164,
		SPINT        = 165,
		ANDAL        = 166,
		MANFRED      = 167,
		ZILARE       = 168,
		CASMETRA     = 169,
		ANABEL       = 170,
		DARGEM       = 171,
		CASSIOPEIA   = 172,
		MIRIAM       = 173,
		ELMOR        = 174,
		BEATRICE     = 175,
		KINKERIA     = 176,
		RANLU        = 177,
	};
}

namespace NH3Levels
{
	constexpr INT LEVEL_0    = -2147483648;
	constexpr INT LEVEL_1    = 0;
	constexpr INT LEVEL_2    = 1000;
	constexpr INT LEVEL_3    = 2000;
	constexpr INT LEVEL_4    = 3200;
	constexpr INT LEVEL_5    = 4600;
	constexpr INT LEVEL_6    = 6200;
	constexpr INT LEVEL_7    = 8000;
	constexpr INT LEVEL_8    = 10000;
	constexpr INT LEVEL_9    = 12200;
	constexpr INT LEVEL_10   = 14700;
	constexpr INT LEVEL_11   = 17500;
	constexpr INT LEVEL_12   = 20600;
	constexpr INT LEVEL_13   = 24320;
	constexpr INT LEVEL_14   = 28784;
	constexpr INT LEVEL_15   = 34140;
	constexpr INT LEVEL_16   = 40567;
	constexpr INT LEVEL_17   = 48279;
	constexpr INT LEVEL_18   = 57533;
	constexpr INT LEVEL_19   = 68637;
	constexpr INT LEVEL_20   = 81961;
	constexpr INT LEVEL_21   = 97949;
	constexpr INT LEVEL_22   = 117134;
	constexpr INT LEVEL_23   = 140156;
	constexpr INT LEVEL_24   = 167782;
	constexpr INT LEVEL_25   = 200933;
	constexpr INT LEVEL_26   = 240714;
	constexpr INT LEVEL_27   = 288451;
	constexpr INT LEVEL_28   = 345735;
	constexpr INT LEVEL_29   = 414475;
	constexpr INT LEVEL_30   = 496963;
	constexpr INT LEVEL_31   = 595948;
	constexpr INT LEVEL_32   = 714730;
	constexpr INT LEVEL_33   = 857268;
	constexpr INT LEVEL_34   = 1028313;
	constexpr INT LEVEL_35   = 1233567;
	constexpr INT LEVEL_36   = 1479871;
	constexpr INT LEVEL_37   = 1775435;
	constexpr INT LEVEL_38   = 2130111;
	constexpr INT LEVEL_39   = 2555722;
	constexpr INT LEVEL_40   = 3066455;
	constexpr INT LEVEL_41   = 3679334;
	constexpr INT LEVEL_42   = 4414788;
	constexpr INT LEVEL_43   = 5297332;
	constexpr INT LEVEL_44   = 6356384;
	constexpr INT LEVEL_45   = 7627246;
	constexpr INT LEVEL_46   = 9152280;
	constexpr INT LEVEL_47   = 10982320;
	constexpr INT LEVEL_48   = 13178368;
	constexpr INT LEVEL_49   = 15813625;
	constexpr INT LEVEL_50   = 18975933;
	constexpr INT LEVEL_51   = 22770702;
	constexpr INT LEVEL_52   = 27324424;
	constexpr INT LEVEL_53   = 32788890;
	constexpr INT LEVEL_54   = 39346249;
	constexpr INT LEVEL_55   = 47215079;
	constexpr INT LEVEL_56   = 56657675;
	constexpr INT LEVEL_57   = 67988790;
	constexpr INT LEVEL_58   = 81586128;
	constexpr INT LEVEL_59   = 97902933;
	constexpr INT LEVEL_60   = 117483099;
	constexpr INT LEVEL_61   = 140979298;
	constexpr INT LEVEL_62   = 169174736;
	constexpr INT LEVEL_63   = 203009261;
	constexpr INT LEVEL_64   = 243610691;
	constexpr INT LEVEL_65   = 292332407;
	constexpr INT LEVEL_66   = 350798466;
	constexpr INT LEVEL_67   = 420957736;
	constexpr INT LEVEL_68   = 505148860;
	constexpr INT LEVEL_69   = 606178208;
	constexpr INT LEVEL_70   = 727413425;
	constexpr INT LEVEL_71   = 872895685;
	constexpr INT LEVEL_72   = 1047474397;
	constexpr INT LEVEL_73   = 1256968851;
	constexpr INT LEVEL_74   = 1508362195;
	constexpr INT LEVEL_88   = 1810034207;
	constexpr INT LEVEL_100  = 2073739175;
	constexpr INT LEVEL_108  = 2099639276;
	constexpr INT LEVEL_868  = 2144641867;
	constexpr INT LEVEL_3732 = 2146553679;
	constexpr INT LEVEL_5920 = 2146673313;
	constexpr INT LEVEL_6424 = 2147293156;
	constexpr INT LEVEL_MAX  = 2147400657;
}

namespace NH3Objects
{
	enum eH3Objects : INT32
	{
		NO_OBJ                      = -1,
		ALTAR_OF_SACRIFICE          = 2,
		ANCHOR_POINT                = 3,
		ARENA                       = 4,
		ARTIFACT                    = 5,
		PANDORAS_BOX                = 6,
		BLACK_MARKET                = 7,
		BOAT                        = 8,
		BORDERGUARD                 = 9,
		KEYMASTER                   = 10,
		BUOY                        = 11,
		CAMPFIRE                    = 12,
		CARTOGRAPHER                = 13,
		SWAN_POND                   = 14,
		COVER_OF_DARKNESS           = 15,
		CREATURE_BANK               = 16,
		CREATURE_GENERATOR1         = 17,
		CREATURE_GENERATOR2         = 18,
		CREATURE_GENERATOR3         = 19,
		CREATURE_GENERATOR4         = 20,
		CURSED_GROUND               = 21,
		CORPSE                      = 22,
		MARLETTO_TOWER              = 23,
		DERELICT_SHIP               = 24,
		DRAGON_UTOPIA               = 25,
		EVENT                       = 26,
		EYE_OF_MAGI                 = 27,
		FAERIE_RING                 = 28,
		FLOTSAM                     = 29,
		FOUNTAIN_OF_FORTUNE         = 30,
		FOUNTAIN_OF_YOUTH           = 31,
		GARDEN_OF_REVELATION        = 32,
		GARRISON                    = 33,
		HERO                        = 34,
		HILL_FORT                   = 35,
		GRAIL                       = 36,
		HUT_OF_MAGI                 = 37,
		IDOL_OF_FORTUNE             = 38,
		LEAN_TO                     = 39,
		DECORATIVE                  = 40,
		LIBRARY_OF_ENLIGHTENMENT    = 41,
		LIGHTHOUSE                  = 42,
		MONOLITH_ONE_WAY_ENTRANCE   = 43,
		MONOLITH_ONE_WAY_EXIT       = 44,
		MONOLITH_TWO_WAY            = 45,
		MAGIC_PLAINS1               = 46,
		SCHOOL_OF_MAGIC             = 47,
		MAGIC_SPRING                = 48,
		MAGIC_WELL                  = 49,
		MARKET_OF_TIME              = 50,
		MERCENARY_CAMP              = 51,
		MERMAID                     = 52,
		MINE                        = 53,
		MONSTER                     = 54,
		MYSTICAL_GARDEN             = 55,
		OASIS                       = 56,
		OBELISK                     = 57,
		REDWOOD_OBSERVATORY         = 58,
		OCEAN_BOTTLE                = 59,
		PILLAR_OF_FIRE              = 60,
		STAR_AXIS                   = 61,
		PRISON                      = 62,
		PYRAMID                     = 63,
		RALLY_FLAG                  = 64,
		RANDOM_ART                  = 65,
		RANDOM_TREASURE_ART         = 66,
		RANDOM_MINOR_ART            = 67,
		RANDOM_MAJOR_ART            = 68,
		RANDOM_RELIC_ART            = 69,
		RANDOM_HERO                 = 70,
		RANDOM_MONSTER              = 71,
		RANDOM_MONSTER_L1           = 72,
		RANDOM_MONSTER_L2           = 73,
		RANDOM_MONSTER_L3           = 74,
		RANDOM_MONSTER_L4           = 75,
		RANDOM_RESOURCE             = 76,
		RANDOM_TOWN                 = 77,
		REFUGEE_CAMP                = 78,
		RESOURCE                    = 79,
		SANCTUARY                   = 80,
		SCHOLAR                     = 81,
		SEA_CHEST                   = 82,
		SEER_HUT                    = 83,
		CRYPT                       = 84,
		SHIPWRECK                   = 85,
		SHIPWRECK_SURVIVOR          = 86,
		SHIPYARD                    = 87,
		SHRINE_OF_MAGIC_INCANTATION = 88,
		SHRINE_OF_MAGIC_GESTURE     = 89,
		SHRINE_OF_MAGIC_THOUGHT     = 90,
		SIGN                        = 91,
		SIRENS                      = 92,
		SPELL_SCROLL                = 93,
		STABLES                     = 94,
		TAVERN                      = 95,
		TEMPLE                      = 96,
		DEN_OF_THIEVES              = 97,
		TOWN                        = 98,
		TRADING_POST                = 99,
		LEARNING_STONE              = 100,
		TREASURE_CHEST              = 101,
		TREE_OF_KNOWLEDGE           = 102,
		SUBTERRANEAN_GATE           = 103,
		UNIVERSITY                  = 104,
		WAGON                       = 105,
		WAR_MACHINE_FACTORY         = 106,
		SCHOOL_OF_WAR               = 107,
		WARRIORS_TOMB               = 108,
		WATER_WHEEL                 = 109,
		WATERING_HOLE               = 110,
		WHIRLPOOL                   = 111,
		WINDMILL                    = 112,
		WITCH_HUT                   = 113,
		BRUSH                       = 114,
		BUSH                        = 115,
		CACTUS                      = 116,
		CANYON                      = 117,
		CRATER                      = 118,
		DEAD_VEGETATION             = 119,
		FLOWERS                     = 120,
		FROZEN_LAKE                 = 121,
		HEDGE                       = 122,
		HILL                        = 123,
		HOLE                        = 124,
		KELP                        = 125,
		LAKE                        = 126,
		LAVA_FLOW                   = 127,
		LAVA_LAKE                   = 128,
		MUSHROOMS                   = 129,
		LOG                         = 130,
		MANDRAKE                    = 131,
		MOSS                        = 132,
		MOUND                       = 133,
		MOUNTAIN                    = 134,
		OAK_TREES                   = 135,
		OUTCROPPING                 = 136,
		PINE_TREES                  = 137,
		PLANT                       = 138,
		BLANK1                      = 139,
		BLANK2                      = 140,
		BLANK3                      = 141,
		BLANK4                      = 142,
		RIVER_DELTA                 = 143,
		BLANK5                      = 144,
		BLANK6                      = 145,
		BLANK7                      = 146,
		ROCK                        = 147,
		SAND_DUNE                   = 148,
		SAND_PIT                    = 149,
		SHRUB                       = 150,
		SKULL                       = 151,
		STALAGMITE                  = 152,
		STUMP                       = 153,
		TAR_PIT                     = 154,
		TREES                       = 155,
		VINE                        = 156,
		VOLCANIC_TENT               = 157,
		VOLCANO                     = 158,
		WILLOW_TREES                = 159,
		YUCCA_TREES                 = 160,
		REEF                        = 161,
		RANDOM_MONSTER_L5           = 162,
		RANDOM_MONSTER_L6           = 163,
		RANDOM_MONSTER_L7           = 164,
		BRUSH2                      = 165,
		BUSH2                       = 166,
		CACTUS2                     = 167,
		CANYON2                     = 168,
		CRATER2                     = 169,
		DEAD_VEGETATION2            = 170,
		FLOWERS2                    = 171,
		FROZEN_LAKE2                = 172,
		HEDGE2                      = 173,
		HILL2                       = 174,
		HOLE2                       = 175,
		KELP2                       = 176,
		LAKE2                       = 177,
		LAVA_FLOW2                  = 178,
		LAVA_LAKE2                  = 179,
		MUSHROOMS2                  = 180,
		LOG2                        = 181,
		MANDRAKE2                   = 182,
		MOSS2                       = 183,
		MOUND2                      = 184,
		MOUNTAIN2                   = 185,
		OAK_TREES2                  = 186,
		OUTCROPPING2                = 187,
		PINE_TREES2                 = 188,
		PLANT2                      = 189,
		RIVER_DELTA2                = 190,
		ROCK2                       = 191,
		SAND_DUNE2                  = 192,
		SAND_PIT2                   = 193,
		SHRUB2                      = 194,
		SKULL2                      = 195,
		STALAGMITE2                 = 196,
		STUMP2                      = 197,
		TAR_PIT2                    = 198,
		TREES2                      = 199,
		VINE2                       = 200,
		VOLCANIC_TENT2              = 201,
		VOLCANO2                    = 202,
		WILLOW_TREES2               = 203,
		YUCCA_TREES2                = 204,
		REEF2                       = 205,
		DESERT_HILLS                = 206,
		DIRT_HILLS                  = 207,
		GRASS_HILLS                 = 208,
		ROUGH_HILLS                 = 209,
		SUBTERRANEAN_ROCKS          = 210,
		SWAMP_FOLIAGE               = 211,
		BORDER_GATE                 = 212,
		FREELANCERS_GUILD           = 213,
		HERO_PLACEHOLDER            = 214,
		QUEST_GUARD                 = 215,
		RANDOM_DWELLING             = 216,
		RANDOM_DWELLING_LVL         = 217,
		RANDOM_DWELLING_FACTION     = 218,
		GARRISON2                   = 219,
		ABANDONED_MINE              = 220,
		TRADING_POST_SNOW           = 221,
		CLOVER_FIELD                = 222,
		CURSED_GROUND2              = 223,
		EVIL_FOG                    = 224,
		FAVORABLE_WINDS             = 225,
		FIERY_FIELDS                = 226,
		HOLY_GROUNDS                = 227,
		LUCID_POOLS                 = 228,
		MAGIC_CLOUDS                = 229,
		MAGIC_PLAINS2               = 230,
		ROCKLANDS                   = 231,
	};
}

namespace NH3PlayerColors
{
	enum eH3PlayerColors : INT32
	{
		RED    = 0,
		BLUE   = 1,
		TAN    = 2,
		GREEN  = 3,
		ORANGE = 4,
		PURPLE = 5,
		TEAL   = 6,
		PINK   = 7,
	};
}

namespace NH3Resources
{
	enum eH3Resources : INT32
	{
		WOOD    = 0,
		MERCURY = 1,
		ORE     = 2,
		SULFUR  = 3,
		CRYSTAL = 4,
		GEMS    = 5,
		GOLD    = 6,
	};
}

namespace NH3Skills
{
	enum eH3PrimarySkills : INT32
	{
		ATTACK       = 0,
		DEFENSE      = 1,
		SPELL_POWER  = 2,
		KNOWLEDGE    = 3,
	};

	enum eH3SecondarySkills : INT32
	{
		PATHFINDING  = 0,
		ARCHERY      = 1,
		LOGISTICS    = 2,
		SCOUTING     = 3,
		DIPLOMACY    = 4,
		NAVIGATION   = 5,
		LEADERSHIP   = 6,
		WISDOM       = 7,
		MYSTICISM    = 8,
		LUCK         = 9,
		BALLISTICS   = 10,
		EAGLE_EYE    = 11,
		NECROMANCY   = 12,
		ESTATES      = 13,
		FIRE_MAGIC   = 14,
		AIR_MAGIC    = 15,
		WATER_MAGIC  = 16,
		EARTH_MAGIC  = 17,
		SCHOLAR      = 18,
		TACTICS      = 19,
		ARTILLERY    = 20,
		LEARNING     = 21,
		OFFENSE      = 22,
		ARMORER      = 23,
		INTELLIGENCE = 24,
		SORCERY      = 25,
		RESISTANCE   = 26,
		FIRST_AID    = 27,
	};
}

namespace NH3Terrains
{
	enum eH3Terrain : INT32
	{
		DIRT         = 0,
		SAND         = 1,
		GRASS        = 2,
		SNOW         = 3,
		SWAMP        = 4,
		ROUGH        = 5,
		SUBTERRANEAN = 6,
		LAVA         = 7,
		WATER        = 8,
		ROCK         = 9,
	};
}

namespace NH3VKey
{
	enum eH3VK : INT32
	{
		H3VK_ESCAPE        = 1,
		H3VK_1             = 2,
		H3VK_2             = 3,
		H3VK_3             = 4,
		H3VK_4             = 5,
		H3VK_5             = 6,
		H3VK_6             = 7,
		H3VK_7             = 8,
		H3VK_8             = 9,
		H3VK_9             = 10,
		H3VK_0             = 11,
		H3VK_MINUS         = 12,
		H3VK_PLUS          = 13,
		H3VK_BACKSPACE     = 14,
		H3VK_TAB           = 15,
		H3VK_Q             = 16,
		H3VK_W             = 17,
		H3VK_E             = 18,
		H3VK_R             = 19,
		H3VK_T             = 20,
		H3VK_Y             = 21,
		H3VK_U             = 22,
		H3VK_I             = 23,
		H3VK_O             = 24,
		H3VK_P             = 25,
		H3VK_LEFT_BRACKET  = 26,
		H3VK_RIGHT_BRACKET = 27,
		H3VK_ENTER         = 28,
		H3VK_CTRL          = 29,
		H3VK_A             = 30,
		H3VK_S             = 31,
		H3VK_D             = 32,
		H3VK_F             = 33,
		H3VK_G             = 34,
		H3VK_H             = 35,
		H3VK_J             = 36,
		H3VK_K             = 37,
		H3VK_L             = 38,
		H3VK_SEMICOLON     = 39,
		H3VK_APOSTROPHE    = 40,
		H3VK_TILDE         = 41,
		H3VK_SHIFT         = 42,
		H3VK_BACKSLASH     = 43,
		H3VK_Z             = 44,
		H3VK_X             = 45,
		H3VK_C             = 46,
		H3VK_V             = 47,
		H3VK_B             = 48,
		H3VK_N             = 49,
		H3VK_M             = 50,
		H3VK_COMMA         = 51,
		H3VK_PERIOD        = 52,
		H3VK_SLASH         = 53,
		H3VK_RIGHT_SHIFT   = 54,
		H3VK_PRINTSCREEN   = 55, // or * on numpad?
		H3VK_ALT           = 56,
		H3VK_SPACEBAR      = 57,

		H3VK_F2            = 60,
		H3VK_F3            = 61,
		H3VK_F4            = 62,
		H3VK_F5            = 63,
		H3VK_F6            = 64,
		H3VK_F7            = 65,
		H3VK_F8            = 66,
		H3VK_F9            = 67,
		H3VK_F10           = 68,
		H3VK_PAUSE         = 69,
		H3VK_SCROLL_LOCK   = 70,
		H3VK_HOME          = 71, // numpad7
		H3VK_UP            = 72, // numpad8
		H3VK_PAGE_UP       = 73, // numpad9
		H3VK_NUMPAD_MINUS  = 74,
		H3VK_LEFT          = 75, // numpad4
		H3VK_NUMPAD5       = 76,
		H3VK_RIGHT         = 77, // numpad6
		H3VK_NUMPAD_PLUS   = 78,
		H3VK_END           = 79, // numpad1
		H3VK_DOWN          = 80, // numpad2
		H3VK_PAGE_DOWN     = 81, // numpad3
		H3VK_INSERT        = 82,
		H3VK_DELETE        = 83,

		H3VK_F11           = 87,
		H3VK_F12           = 88,

		H3VK_LEFT_WIN      = 91,
		H3VK_RIGHT_WIN     = 92,
		H3VK_RIGHT_CLICK   = 93,
	};
}

namespace NH3Dlg
{
	namespace Text
	{
		LPCSTR const TINY    = (LPCSTR(0x660CB4)); // "tiny.fnt"
		LPCSTR const SMALL   = (LPCSTR(0x65F2F8));   // "smalfont.fnt"
		LPCSTR const MEDIUM  = (LPCSTR(0x65F2EC));   // "MedFont.fnt"
		LPCSTR const BIG     = (LPCSTR(0x660B24));   // "bigfont.fnt"
		LPCSTR const VERDANA = (LPCSTR(0x6700B4));   // "Verd10B.fnt"
	}

	namespace TextAlignment
	{
		enum eTextAlignment : INT32
		{
			HLeft        = 0,
			HCenter      = 1,
			HRight       = 2,
			VTop         = 0,
			VCenter      = 4,
			VBottom      = 8,
			BottomLeft   = HLeft   | VBottom,
			BottomCenter = HCenter | VBottom,
			BottomRight  = HRight  | VBottom,
			MiddleLeft   = HLeft   | VCenter,
			MiddleCenter = HCenter | VCenter,
			MiddleRight  = HRight  | VCenter,
			TopLeft      = HLeft   | VTop,
			TopMiddle    = HCenter | VTop,
			TopRight     = HRight  | VTop,
		};
	};

	namespace TextColor
	{
		enum eTextColor : INT32
		{
			SILVER      = 0x00,
			REGULAR     = 0x01,
			HIGHLIGHT   = 0x02,
			GOLD        = 0x03,
			WHITE       = 0x04,
			GREEN       = 0x0D,
			LIGHT_GREEN = 0x0E,
			DARK_GREEN  = 0x0F,
			BLACK       = 0x17,
			BLUE        = 0x18,
			CYAN        = 0x1A,
			RED         = 0x1B,
			PURPLE      = 0x1C,
			YELLOW      = 0x1D,
			GRAY        = 0x36,
			RED2        = 0x37,
			BLUE2       = 0x38,
			TAN         = 0x39,
			DARK_GREEN2 = 0x3A,
			ORANGE      = 0x3B,
			PURPLE2     = 0x3C,
			DARK_CYAN   = 0x3D,
			PINK        = 0x3E,
			GRAY2       = 0x3F,
			YELLOW2     = 0x57,
			DARK_YELLOW = 0x58,
			TAN2        = 0x59,
			TAN3        = 0x5A,
			TAN4        = 0x5B,
			TAN5        = 0x5C,
			CYAN2       = 0x67,
			CYAN3       = 0x68,
			CYAN4       = 0x69,
			CYAN5       = 0x6A,
		};
	}

	namespace Assets
	{
		LPCSTR const ARTIFACT_DEF     = (LPCSTR(0x660214));  // "artifact.def" 44x44
		LPCSTR const ARTS_ICON        = (LPCSTR(0x683178));  // AltArt.def 64x32
		LPCSTR const CREATURE_SMALL   = (LPCSTR(0x660180));  // "CPRSMALL.def" 32x32
		LPCSTR const DIBOXBACK        = (LPCSTR(0x66025C));  // "diboxback.pcx" 256x256
		LPCSTR const DLGBOX           = (LPCSTR(0x66024C));  // "dialogbox.def" 64x64
		LPCSTR const HERO_CADRE       = (LPCSTR(0x65F3DC));  // hpsyyy.pcx 48x32
		LPCSTR const PSKILL_42        = (LPCSTR(0x679D9C));  // "PSKIL42.def" 42x42
		LPCSTR const RESOURCE_DEF     = (LPCSTR(0x660224));  // "resource.def" 32x32
		LPCSTR const RESOURCE_82      = (LPCSTR(0x660114));  // "resour82.def" 82x93
		LPCSTR const SPELLS_DEF       = (LPCSTR(0x660208));  // "spells.def"78x65
		LPCSTR const SPELL_SMALL      = (LPCSTR(0x6700A4));  // "spellint.def" 48x36
		LPCSTR const SSKILL_44        = (LPCSTR(0x6601D0));  // "Secskill.def" 44x44
		LPCSTR const UN44_DEF         = (LPCSTR(0x679D90));  // "un44.def"44x44
		LPCSTR const OVBUTN3          = (LPCSTR(0x6817C4));  // "OvButn3.def" 108x16
		LPCSTR const LARGE_HERO_CADRE = (LPCSTR(0x68C45C));  // TPTavSel.pcx 62x68 ~decal by -2
		LPCSTR const CREATURE_LARGE   = (LPCSTR(0x6700C0));  // TwCrPort.def 58x64
		LPCSTR const CANCEL_BUTTON    = (LPCSTR(0x660B04));  // iCancel.def 64x30
		LPCSTR const CAST_SPELL       = (LPCSTR(0x66FFD4));  // icm005.def 48x36
		LPCSTR const MORALE_42        = (LPCSTR(0x68C6DC));  // IMRL42.def 42x38
		LPCSTR const LUCK_42          = (LPCSTR(0x68C6D0));  // ILCK42.def 42x38
		LPCSTR const CREST58          = (LPCSTR(0x6601FC));  // CREST58.def 58x64
		LPCSTR const TOWN_SMALL       = (LPCSTR(0x65F318));  // itpa.def 48x32
		LPCSTR const NO_VISION        = (LPCSTR(0x6885A0));  // SYSOPB8.def 46x32
		LPCSTR const ADVENTURE_CURSOR = (LPCSTR(0x68164C));  // cradvntr.def 40x40
		LPCSTR const ALT_ART          = (LPCSTR(0x683178));  // AltArt.def 64x32
		LPCSTR const ON_OFF_CHECKBOX  = (LPCSTR(0x6700F0));  // sysopchk.def 32x24
		LPCSTR const OKAY_DEF         = (LPCSTR(0x670160));  // iOkay.def 64x30
		LPCSTR const OKAY32_DEF       = (LPCSTR(0x682374));  // iOkay32.def 66x32
		LPCSTR const OKAY6432_DEF     = (LPCSTR(0x65F470));  // iOk6432.def 64x32
		LPCSTR const BOX_64_30_PCX    = (LPCSTR(0x67016C));  // Box64x30.pcx
		LPCSTR const BOX_66_32_PCX    = (LPCSTR(0x682380));  // Box66x32.pcx
		LPCSTR const CANCEL_DEF       = (LPCSTR(0x660B04));  // "iCancel.def" 64x30
		LPCSTR const VIEW_CREATURE    = (LPCSTR(0x660134));  // iViewCr.def
		LPCSTR const VIEW_MAGNIFIER   = (LPCSTR(0x68C734));  // VWMag1.def 60x32
		LPCSTR const iSAVE_DEF        = "ISAVE.DEF";         // iSave.def 64x32
		LPCSTR const BOX_64_32_PCX    = (LPCSTR(0x68C640));  // Box64x32.pcx
		LPCSTR const GAME_TYPE_DEF    = (LPCSTR(0x683568));  // 32x24
	}
	namespace HDassets
	{
		LPCSTR const DLGBLUEBOX       = "DlgBluBo.def";  // 64x64
		LPCSTR const DLGBLUEBACK      = "DlgBluBk.PCX";  // 256x256
		LPCSTR const LINE_SEPARATOR   = "stripe3d.bmp";  // 800x2
		LPCSTR const HD_STATUSBAR_PCX = "HD_TStat.pcx";  // 800x19
		LPCSTR const HERO_FRAME       = "48x32bFr.bmp";  // darken an area for 48x32 def
		LPCSTR const BACKPACK_DEF     = "bckpck.def";    // 52x36
		LPCSTR const BIG_BACKPACK     = "BkPack.bmp";    // 369x369
		LPCSTR const SCROLL_SMALL     = "def.SpScrArt";  // 44x44
		LPCSTR const FRAME_LU         = "hd_fr_lu.bmp";  // 4x4
		LPCSTR const FRAME_LD         = "hd_fr_ld.bmp";  // 4x4
		LPCSTR const FRAME_RU         = "hd_fr_ru.bmp";  // 4x4
		LPCSTR const FRAME_RD         = "hd_fr_rd.bmp";  // 4x4
		LPCSTR const FRAME_U          = "hd_fr_u.bmp";   // 4x4
		LPCSTR const FRAME_D          = "hd_fr_d.bmp";   // 4x4
		LPCSTR const FRAME_L          = "hd_fr_l.bmp";   // 4x4
		LPCSTR const FRAME_R          = "hd_fr_r.bmp";   // 4x4
	}
}

#pragma warning(pop)

#endif /* #define _H3CONSTANTS_H_ */