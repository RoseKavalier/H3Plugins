//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3_CONSTANTS_HPP_
#define _H3_CONSTANTS_HPP_

#include "H3_Base.hpp"
#include "H3_Config.hpp"

namespace h3
{
#pragma warning(push)
#pragma warning(disable:4146) // disable unary minus operator unsigned type warning

    namespace NH3Artifacts
    {
        enum eArtifacts
        {
            SPELLBOOK                      = 0,
            SPELL_SCROLL                   = 1,
            GRAIL                          = 2,
            CATAPULT                       = 3,
            BALLISTA                       = 4,
            AMMO_CART                      = 5,
            FIRST_AID_TENT                 = 6,
            CENTAUR_AXE                    = 7,
            BLACKSHARD_OF_THE_DEAD_KNIGHT  = 8,
            GREATER_GNOLLS_FLAIL           = 9,
            OGRES_CLUB_OF_HAVOC            = 10,
            SWORD_OF_HELLFIRE              = 11,
            TITANS_GLADIUS                 = 12,
            SHIELD_OF_THE_DWARVEN_LORDS    = 13,
            SHIELD_OF_THE_YAWNING_DEAD     = 14,
            BUCKLER_OF_THE_GNOLL_KING      = 15,
            TARG_OF_THE_RAMPAGING_OGRE     = 16,
            SHIELD_OF_THE_DAMNED           = 17,
            SENTINELS_SHIELD               = 18,
            HELM_OF_THE_ALABASTER_UNICORN  = 19,
            SKULL_HELMET                   = 20,
            HELM_OF_CHAOS                  = 21,
            CROWN_OF_THE_SUPREME_MAGI      = 22,
            HELLSTORM_HELMET               = 23,
            THUNDER_HELMET                 = 24,
            BREASTPLATE_OF_PETRIFIED_WOOD  = 25,
            RIB_CAGE                       = 26,
            SCALES_OF_THE_GREATER_BASILISK = 27,
            TUNIC_OF_THE_CYCLOPS_KING      = 28,
            BREASTPLATE_OF_BRIMSTONE       = 29,
            TITANS_CUIRASS                 = 30,
            ARMOR_OF_WONDER                = 31,
            SANDALS_OF_THE_SAINT           = 32,
            CELESTIAL_NECKLACE_OF_BLISS    = 33,
            LIONS_SHIELD_OF_COURAGE        = 34,
            SWORD_OF_JUDGEMENT             = 35,
            HELM_OF_HEAVENLY_ENLIGHTENMENT = 36,
            QUIET_EYE_OF_THE_DRAGON        = 37,
            RED_DRAGON_FLAME_TONGUE        = 38,
            DRAGON_SCALE_SHIELD            = 39,
            DRAGON_SCALE_ARMOR             = 40,
            DRAGONBONE_GREAVES             = 41,
            DRAGON_WING_TABARD             = 42,
            NECKLACE_OF_DRAGONTEETH        = 43,
            CROWN_OF_DRAGONTOOTH           = 44,
            STILL_EYE_OF_THE_DRAGON        = 45,
            CLOVER_OF_FORTUNE              = 46,
            CARDS_OF_PROPHECY              = 47,
            LADYBIRD_OF_LUCK               = 48,
            BADGE_OF_COURAGE               = 49,
            CREST_OF_VALOR                 = 50,
            GLYPH_OF_GALLANTRY             = 51,
            SPECULUM                       = 52,
            SPYGLASS                       = 53,
            AMULET_OF_THE_UNDERTAKER       = 54,
            VAMPIRES_COWL                  = 55,
            DEAD_MANS_BOOTS                = 56,
            GARNITURE_OF_INTERFERENCE      = 57,
            SURCOAT_OF_COUNTERPOISE        = 58,
            BOOTS_OF_POLARITY              = 59,
            BOW_OF_ELVEN_CHERRYWOOD        = 60,
            BOWSTRING_OF_THE_UNICORNS_MANE = 61,
            ANGEL_FEATHER_ARROWS           = 62,
            BIRD_OF_PERCEPTION             = 63,
            STOIC_WATCHMAN                 = 64,
            EMBLEM_OF_COGNIZANCE           = 65,
            STATESMANS_MEDAL               = 66,
            DIPLOMATS_RING                 = 67,
            AMBASSADORS_SASH               = 68,
            RING_OF_THE_WAYFARER           = 69,
            EQUESTRIANS_GLOVES             = 70,
            NECKLACE_OF_OCEAN_GUIDANCE     = 71,
            ANGEL_WINGS                    = 72,
            CHARM_OF_MANA                  = 73,
            TALISMAN_OF_MANA               = 74,
            MYSTIC_ORB_OF_MANA             = 75,
            COLLAR_OF_CONJURING            = 76,
            RING_OF_CONJURING              = 77,
            CAPE_OF_CONJURING              = 78,
            ORB_OF_THE_FIRMAMENT           = 79,
            ORB_OF_SILT                    = 80,
            ORB_OF_TEMPESTUOUS_FIRE        = 81,
            ORB_OF_DRIVING_RAIN            = 82,
            RECANTERS_CLOAK                = 83,
            SPIRIT_OF_OPPRESSION           = 84,
            HOURGLASS_OF_THE_EVIL_HOUR     = 85,
            TOME_OF_FIRE_MAGIC             = 86,
            TOME_OF_AIR_MAGIC              = 87,
            TOME_OF_WATER_MAGIC            = 88,
            TOME_OF_EARTH_MAGIC            = 89,
            BOOTS_OF_LEVITATION            = 90,
            GOLDEN_BOW                     = 91,
            SPHERE_OF_PERMANENCE           = 92,
            ORB_OF_VULNERABILITY           = 93,
            RING_OF_VITALITY               = 94,
            RING_OF_LIFE                   = 95,
            VIAL_OF_LIFEBLOOD              = 96,
            NECKLACE_OF_SWIFTNESS          = 97,
            BOOTS_OF_SPEED                 = 98,
            CAPE_OF_VELOCITY               = 99,
            PENDANT_OF_DISPASSION          = 100,
            PENDANT_OF_SECOND_SIGHT        = 101,
            PENDANT_OF_HOLINESS            = 102,
            PENDANT_OF_LIFE                = 103,
            PENDANT_OF_DEATH               = 104,
            PENDANT_OF_FREE_WILL           = 105,
            PENDANT_OF_NEGATIVITY          = 106,
            PENDANT_OF_TOTAL_RECALL        = 107,
            PENDANT_OF_COURAGE             = 108,
            EVERFLOWING_CRYSTAL_CLOAK      = 109,
            RING_OF_INFINITE_GEMS          = 110,
            EVERPOURING_VIAL_OF_MERCURY    = 111,
            INEXHAUSTIBLE_CART_OF_ORE      = 112,
            EVERSMOKING_RING_OF_SULFUR     = 113,
            INEXHAUSTIBLE_CART_OF_LUMBER   = 114,
            ENDLESS_SACK_OF_GOLD           = 115,
            ENDLESS_BAG_OF_GOLD            = 116,
            ENDLESS_PURSE_OF_GOLD          = 117,
            LEGS_OF_LEGION                 = 118,
            LOINS_OF_LEGION                = 119,
            TORSO_OF_LEGION                = 120,
            ARMS_OF_LEGION                 = 121,
            HEAD_OF_LEGION                 = 122,
            SEA_CAPTAINS_HAT               = 123,
            SPELLBINDERS_HAT               = 124,
            SHACKLES_OF_WAR                = 125,
            ORB_OF_INHIBITION              = 126,
            VIAL_OF_DRAGON_BLOOD           = 127,
            ARMAGEDDONS_BLADE              = 128,
            ANGELIC_ALLIANCE               = 129,
            CLOAK_OF_THE_UNDEAD_KING       = 130,
            ELIXIR_OF_LIFE                 = 131,
            ARMOR_OF_THE_DAMNED            = 132,
            STATUE_OF_LEGION               = 133,
            POWER_OF_THE_DRAGON_FATHER     = 134,
            TITANS_THUNDER                 = 135,
            ADMIRALS_HAT                   = 136,
            BOW_OF_THE_SHARPSHOOTER        = 137,
            WIZARDS_WELL                   = 138,
            RING_OF_THE_MAGI               = 139,
            CORNUCOPIA                     = 140,
        };

        enum eArtifactSlots
        {
            sHEAD           = 0,
            sSHOULDERS      = 1,
            sNECK           = 2,
            sRIGHT_HAND     = 3,
            sLEFT_HAND      = 4,
            sTORSO          = 5,
            sRIGHT_RING     = 6,
            sLEFT_RING      = 7,
            sFEET           = 8,
            sMISC1          = 9,
            sMISC2          = 10,
            sMISC3          = 11,
            sMISC4          = 12,
            sBALLISTA       = 13,
            sAMMO_CART      = 14,
            sFIRST_AID_TENT = 15,
            sCATAPULT       = 16,
            sSPELLBOOK      = 17,
            sMISC5          = 18,
        };

        enum eArtifactType
        {
            ART_SPECIAL  = 1,
            ART_TREASURE = 2,
            ART_MINOR    = 4,
            ART_MAJOR    = 8,
            ART_RELIC    = 16,
            ART_ALL      = 30 // never special!
        };
    }

    namespace NH3Campaign
    {
        enum eCampaignId
        {
            LONG_LIVE_THE_QUEEN     = 0,
            LIBERATION              = 1,
            SPOILS_OF_WAR           = 2,
            SONG_FOR_THE_FATHER     = 3,
            DUNGEONS_AND_DEVILS     = 4,
            LONG_LIVE_THE_KING      = 5,
            SEEDS_OF_DISCONTENT     = 6,

            ARMAGEDDONS_BLADE       = 7,
            DRAGONS_BLOOD           = 8,
            DRAGON_SLAYER           = 9,
            FESTIVAL_OF_LIFE        = 10,
            FOOLHARDY_WAYWARDNESS   = 11,
            PLAYING_WITH_FIRE       = 12,

            HACK_AND_SLASH          = 13,
            BIRTH_OF_A_BARBARIAN    = 14,
            NEW_BEGINNING           = 15,
            ELIXIR_OF_LIFE          = 16,
            RISE_OF_THE_NECROMANCER = 17,
            UNHOLY_ALLIANCE         = 18,
            SPECTER_OF_POWER        = 19,
        };
    }

    namespace NH3Combat
    {
        enum eFortElements {
            FE_DRAWBRIDGE      = 0,
            FE_DRAWBRIDGE_ROPE = 1,
            FE_MOAT            = 2,
            FE_MOAT_LIP        = 3,
            FE_BACK_WALL       = 4,
            FE_UPPER_TOWER     = 5,  // valid catapult target ~0
            FE_UPPER_WALL      = 6,  // valid catapult target ~1
            FE_UPPER_BUTTRESS  = 7,
            FE_MID_UPPER_WALL  = 8,  // valid catapult target ~2
            FE_GATE            = 9,  // valid catapult target ~3
            FE_MID_LOWER_WALL  = 10, // valid catapult target ~4
            FE_LOWER_BUTTRESS  = 11,
            FE_LOWER_WALL      = 12, // valid catapult target ~5
            FE_LOWER_TOWER     = 13, // valid catapult target ~6
            FE_KEEP            = 14, // valid catapult target ~7
            FE_KEEP_CVR        = 15,
            FE_LOWER_TWR_CVR   = 16,
            FE_UPPER_TWR_CVR   = 17,
        };

        enum eMissiles
        {
            M_UPPER_RIGHT = 0,
            M_RIGHT       = 1,
            M_LOWER_RIGHT = 2,
        };

        enum eBattleAction : INT32
        {
            BA_CANCEL         = 0, // Cancel Action(the stack can do a different action now but it may still be impossible to force it to do most actions through ERM).
            BA_CAST_SPELL     = 1, // Hero casts a spell
            BA_WALK           = 2,
            BA_DEFEND         = 3,
            BA_RETREAT        = 4,
            BA_SURRENDER      = 5,
            BA_WALK_ATTACK    = 6,
            BA_SHOOT          = 7,
            BA_WAIT           = 8,
            BA_CATAPULT       = 9,
            BA_MONSTER_SPELL  = 10,
            BA_FIRST_AID_TENT = 11,
            BA_NOTHING        = 12, //No action(can be to disable stack for this round)
        };

        enum eRelativeOrientation : INT32
        {
            TOP_RIGHT      = 0,
            RIGHT          = 1,
            BOTTOM_RIGHT   = 2,
            BOTTOM_LEFT    = 3,
            LEFT           = 4,
            TOP_LEFT       = 5,
            REVERSE_TOP    = 6, // equivalent to 5 or 0 [attacker vs defender]
            REVERSE_BOTTOM = 7, // equivalent to 3 or 2 [attacker vs defender]
        };

        enum eSquareAccess : UINT8
        {
            INACCESSIBLE = 0,
            CAN_ATTACK   = 1,
            CAN_REACH    = 2,
            ACCESSIBLE   = CAN_ATTACK | CAN_REACH,
        };

        constexpr INT32 COMBATSQUARE_WIDTH  = 44;
        constexpr INT32 COMBATSQUARE_HEIGHT = 42;
    }

    namespace NH3Creatures
    {
        enum eH3Creatures : INT32
        {
            UNDEFINED           = -1,
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
        };
    }

    namespace NH3Dispositions
    {
        constexpr INT32 COMPLIANT  = 0;
        constexpr INT32 FRIENDLY   = 1;
        constexpr INT32 AGGRESSIVE = 2;
        constexpr INT32 HOSTILE    = 3;
        constexpr INT32 SAVAGE     = 4;
    }

    namespace NH3Formats
    {
        constexpr INT32 ROE = 0x0E;
        constexpr INT32 AB  = 0x15;
        constexpr INT32 SOD = 0x1C;
        constexpr INT32 CHR = 0x1D;
        constexpr INT32 WOG = 0x33;
    }

    namespace NH3Heroes
    {
        enum eHeroClasses : INT32
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

        enum eHeroSpecialty : UINT32
        {
            ST_SKILL          = 0,
            ST_CREATURELEVEL  = 1,
            ST_RESOURCE       = 2,
            ST_SPELL          = 3,
            ST_STATICCREATURE = 4,
            ST_SPEED          = 5,
            ST_CONVERSION     = 6,
            ST_DRAGON         = 7,
        };

        enum eHeroIdentity : INT32
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
        };

        enum eHeroRace : INT32
        {
            DEMON      = 0,
            DWARF      = 1,
            EFREET     = 2,
            ELF        = 3,
            GENIE      = 4,
            GNOLL      = 5,
            GOBLIN     = 6,
            HUMAN      = 7,
            LICH       = 8,
            LIZARDMAN  = 9,
            MINOTAUR   = 10,
            OGRE       = 11,
            TROGLODYTE = 12,
            VAMPIRE    = 13,
        };
    }

    namespace NH3Levels
    {
        constexpr INT32 LEVEL_0    = -2147483648;
        constexpr INT32 LEVEL_1    = 0;
        constexpr INT32 LEVEL_2    = 1000;
        constexpr INT32 LEVEL_3    = 2000;
        constexpr INT32 LEVEL_4    = 3200;
        constexpr INT32 LEVEL_5    = 4600;
        constexpr INT32 LEVEL_6    = 6200;
        constexpr INT32 LEVEL_7    = 8000;
        constexpr INT32 LEVEL_8    = 10000;
        constexpr INT32 LEVEL_9    = 12200;
        constexpr INT32 LEVEL_10   = 14700;
        constexpr INT32 LEVEL_11   = 17500;
        constexpr INT32 LEVEL_12   = 20600;
        constexpr INT32 LEVEL_13   = 24320;
        constexpr INT32 LEVEL_14   = 28784;
        constexpr INT32 LEVEL_15   = 34140;
        constexpr INT32 LEVEL_16   = 40567;
        constexpr INT32 LEVEL_17   = 48279;
        constexpr INT32 LEVEL_18   = 57533;
        constexpr INT32 LEVEL_19   = 68637;
        constexpr INT32 LEVEL_20   = 81961;
        constexpr INT32 LEVEL_21   = 97949;
        constexpr INT32 LEVEL_22   = 117134;
        constexpr INT32 LEVEL_23   = 140156;
        constexpr INT32 LEVEL_24   = 167782;
        constexpr INT32 LEVEL_25   = 200933;
        constexpr INT32 LEVEL_26   = 240714;
        constexpr INT32 LEVEL_27   = 288451;
        constexpr INT32 LEVEL_28   = 345735;
        constexpr INT32 LEVEL_29   = 414475;
        constexpr INT32 LEVEL_30   = 496963;
        constexpr INT32 LEVEL_31   = 595948;
        constexpr INT32 LEVEL_32   = 714730;
        constexpr INT32 LEVEL_33   = 857268;
        constexpr INT32 LEVEL_34   = 1028313;
        constexpr INT32 LEVEL_35   = 1233567;
        constexpr INT32 LEVEL_36   = 1479871;
        constexpr INT32 LEVEL_37   = 1775435;
        constexpr INT32 LEVEL_38   = 2130111;
        constexpr INT32 LEVEL_39   = 2555722;
        constexpr INT32 LEVEL_40   = 3066455;
        constexpr INT32 LEVEL_41   = 3679334;
        constexpr INT32 LEVEL_42   = 4414788;
        constexpr INT32 LEVEL_43   = 5297332;
        constexpr INT32 LEVEL_44   = 6356384;
        constexpr INT32 LEVEL_45   = 7627246;
        constexpr INT32 LEVEL_46   = 9152280;
        constexpr INT32 LEVEL_47   = 10982320;
        constexpr INT32 LEVEL_48   = 13178368;
        constexpr INT32 LEVEL_49   = 15813625;
        constexpr INT32 LEVEL_50   = 18975933;
        constexpr INT32 LEVEL_51   = 22770702;
        constexpr INT32 LEVEL_52   = 27324424;
        constexpr INT32 LEVEL_53   = 32788890;
        constexpr INT32 LEVEL_54   = 39346249;
        constexpr INT32 LEVEL_55   = 47215079;
        constexpr INT32 LEVEL_56   = 56657675;
        constexpr INT32 LEVEL_57   = 67988790;
        constexpr INT32 LEVEL_58   = 81586128;
        constexpr INT32 LEVEL_59   = 97902933;
        constexpr INT32 LEVEL_60   = 117483099;
        constexpr INT32 LEVEL_61   = 140979298;
        constexpr INT32 LEVEL_62   = 169174736;
        constexpr INT32 LEVEL_63   = 203009261;
        constexpr INT32 LEVEL_64   = 243610691;
        constexpr INT32 LEVEL_65   = 292332407;
        constexpr INT32 LEVEL_66   = 350798466;
        constexpr INT32 LEVEL_67   = 420957736;
        constexpr INT32 LEVEL_68   = 505148860;
        constexpr INT32 LEVEL_69   = 606178208;
        constexpr INT32 LEVEL_70   = 727413425;
        constexpr INT32 LEVEL_71   = 872895685;
        constexpr INT32 LEVEL_72   = 1047474397;
        constexpr INT32 LEVEL_73   = 1256968851;
        constexpr INT32 LEVEL_74   = 1508362195;
        constexpr INT32 LEVEL_88   = 1810034207;
        constexpr INT32 LEVEL_100  = 2073739175;
        constexpr INT32 LEVEL_108  = 2099639276;
        constexpr INT32 LEVEL_868  = 2144641867;
        constexpr INT32 LEVEL_3732 = 2146553679;
        constexpr INT32 LEVEL_5920 = 2146673313;
        constexpr INT32 LEVEL_6424 = 2147293156;
        constexpr INT32 LEVEL_MAX  = 2147400657;
    }

    namespace NH3Loss
    {
        enum eType : INT8
        {
            NONE         = -1,
            LOSE_TOWN    = 0,
            LOSE_HERO    = 1,
            TIME_EXPIRES = 2,
        };
    }

    namespace NH3Mouse
    {
        enum H3MouseCursorType : INT32
        {
            CURSOR_DEFAULT   = 0,
            CURSOR_ADVENTURE = 1,
            CURSOR_COMBAT    = 2,
            CURSOR_SPELL     = 3,
            CURSOR_ARTIFACT  = 4,
        };

        enum eAdventureMapCursorType
        {
            AMC_ARROWPOINTER         = 0,
            AMC_BUSY_WAIT            = 1,
            AMC_HERO                 = 2,
            AMC_TOWN                 = 3,
            AMC_HORSE                = 4,
            AMC_ATTACK               = 5,
            AMC_BOAT                 = 6,
            AMC_ANCHOR               = 7,
            AMC_HERO_MEETING         = 8,
            AMC_REARING_HORSE        = 9,
            AMC_HORSE2               = 10,
            AMC_ATTACK2              = 11,
            AMC_BOAT2                = 12,
            AMC_ANCHOR2              = 13,
            AMC_HERO_MEETING2        = 14,
            AMC_REARING_HORSE2       = 15,
            AMC_HORSE3               = 16,
            AMC_ATTACK3              = 17,
            AMC_BOAT3                = 18,
            AMC_ANCHOR3              = 19,
            AMC_HERO_MEETING3        = 20,
            AMC_REARING_HORSE3       = 21,
            AMC_HORSE4               = 22,
            AMC_ATTACK4              = 23,
            AMC_BOAT4                = 24,
            AMC_ANCHOR4              = 25,
            AMC_HERO_MEETING4        = 26,
            AMC_REARING_HORSE4       = 27,
            AMC_BOAT_1               = 28,
            AMC_BOAT_2               = 29,
            AMC_BOAT_3               = 30,
            AMC_BOAT_4               = 31,
            AMC_MAP_SCROLL_NORTH     = 32,
            AMC_MAP_SCROLL_NORTHEAST = 33,
            AMC_MAP_SCROLL_EAST      = 34,
            AMC_MAP_SCROLL_SOUTHEAST = 35,
            AMC_MAP_SCROLL_SOUTH     = 36,
            AMC_MAP_SCROLL_SOUTHWEST = 37,
            AMC_MAP_SCROLL_WEST      = 38,
            AMC_MAP_SCROLL_NORTHWEST = 39,
            AMC_ARROW_POINTER        = 40,
            AMC_DIMENSION_DOOR       = 41,
            AMC_SCUTTLE_BOAT         = 42,
        };

        enum eBattleFieldCursorType
        {
            BFC_NULL             = 0,
            BFC_MOVE             = 1,
            BFC_FLY              = 2,
            BFC_SHOOTING         = 3,
            BFC_HERO             = 4,
            BFC_QUESTION_MARK    = 5,
            BFC_ARROW_POINTER    = 6,
            BFC_ATTACK_NORTHEAST = 7,
            BFC_ATTACK_EAST      = 8,
            BFC_ATTACK_SOUTHEAST = 9,
            BFC_ATTACK_SOUTHWEST = 10,
            BFC_ATTACK_WEST      = 11,
            BFC_ATTACK_NORTHWEST = 12,
            BFC_ATTACK_NORTH     = 13,
            BFC_ATTACK_SOUTH     = 14,
            BFC_HALF_DAMAGE      = 15,
            BFC_ATTACK_WALL      = 16,
            BFC_HEAL             = 17,
            BFC_SACRIFICE        = 18,
            BFC_TELEPORT         = 19,
        };
    }

    namespace NH3Objects
    {
        enum eObjectTypes : INT32
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

        enum eCrBank
        {
            CB_CYCLOPS_STOCPILE     = 0,
            CB_DWARVEN_TREASURY     = 1,
            CB_GRIFFIN_CONSERVATORY = 2,
            CB_IMP_CACHE            = 3,
            CB_MEDUA_STORES         = 4,
            CB_NAGA_BANK            = 5,
            CB_DRAGON_FLY_HIVE      = 6,
            CB_SHIPWRECK            = 7,
            CB_DERELICT_SHIP        = 8,
            CB_CRYPT                = 9,
            CB_DRAGON_UTOPIA        = 10,
        };
    }

    namespace NH3PlayerColors
    {
        enum ePlayerColors : INT32
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

    namespace NH3Quest
    {
        enum eQuestType
        {
            QT_NONE             = 0,
            QT_EXPERIENCE_LEVEL = 1,
            QT_PRIMARY_SKILL    = 2,
            QT_DEFEAT_HERO      = 3,
            QT_DEFEAT_MONSTER   = 4,
            QT_BRING_ARTIFACTS  = 5,
            QT_BRING_CREATURES  = 6,
            QT_BRING_RESOURCES  = 7,
            QT_BE_HERO          = 8,
            QT_BE_PLAYER        = 9,
        };

        enum eSeerReward
        {
            SR_NONE            = 0,
            SR_EXPERIENCE      = 1,
            SR_SPELL_POINTS    = 2,
            SR_MORALE          = 3,
            SR_LUCK            = 4,
            SR_RESOURCE        = 5,
            SR_PRIMARY_SKILL   = 6,
            SR_SECONDARY_SKILL = 7,
            SR_ARTIFACT        = 8,
            SR_SPELL           = 9,
            SR_CREATURE        = 10,
        };
    }

    namespace NH3Resources
    {
        enum eResourceType : INT32
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
        enum ePrimarySkills : INT32
        {
            ATTACK       = 0,
            DEFENSE      = 1,
            SPELL_POWER  = 2,
            KNOWLEDGE    = 3,
        };

        enum eSecondarySkills : INT32
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

        enum eSecSkillLevel : INT32
        {
            NONE     = 0,
            BASIC    = 1,
            ADVANCED = 2,
            EXPERT   = 3,
        };
    }

    namespace NH3Spells
    {
        enum eSchool : INT32
        {
            AIR   = 1,
            FIRE  = 2,
            WATER = 4,
            EARTH = 8,
            ALL   = AIR | FIRE | WATER | EARTH,
        };

        enum eTargetType : INT32
        {
            ENEMY    = -1,
            AREA     = 0,
            FRIENDLY = 1,
        };

        enum eSpells
        {
            SUMMON_BOAT           = 0,
            SCUTTLE_BOAT          = 1,
            VISIONS               = 2,
            VIEW_EARTH            = 3,
            DISGUISE              = 4,
            VIEW_AIR              = 5,
            FLY                   = 6,
            WATER_WALK            = 7,
            DIMENSION_DOOR        = 8,
            TOWN_PORTAL           = 9,
            QUICK_SAND            = 10,
            LAND_MINE             = 11,
            FORCE_FIELD           = 12,
            FIRE_WALL             = 13,
            EARTHQUAKE            = 14,
            MAGIC_ARROW           = 15,
            ICE_BOLT              = 16,
            LIGHTNING_BOLT        = 17,
            IMPLOSION             = 18,
            CHAIN_LIGHTNING       = 19,
            FROST_RING            = 20,
            FIREBALL              = 21,
            INFERNO               = 22,
            METEOR_SHOWER         = 23,
            DEATH_RIPPLE          = 24,
            DESTROY_UNDEAD        = 25,
            ARMAGEDDON            = 26,
            SHIELD                = 27,
            AIR_SHIELD            = 28,
            FIRE_SHIELD           = 29,
            PROTECTION_FROM_AIR   = 30,
            PROTECTION_FROM_FIRE  = 31,
            PROTECTION_FROM_WATER = 32,
            PROTECTION_FROM_EARTH = 33,
            ANTI_MAGIC            = 34,
            DISPEL                = 35,
            MAGIC_MIRROR          = 36,
            CURE                  = 37,
            RESURRECTION          = 38,
            ANIMATE_DEAD          = 39,
            SACRIFICE             = 40,
            BLESS                 = 41,
            CURSE                 = 42,
            BLOODLUST             = 43,
            PRECISION             = 44,
            WEAKNESS              = 45,
            STONE_SKIN            = 46,
            DISRUPTING_RAY        = 47,
            PRAYER                = 48,
            MIRTH                 = 49,
            SORROW                = 50,
            FORTUNE               = 51,
            MISFORTUNE            = 52,
            HASTE                 = 53,
            SLOW                  = 54,
            SLAYER                = 55,
            FRENZY                = 56,
            TITANS_LIGHTNING_BOLT = 57,
            COUNTERSTRIKE         = 58,
            BERSERK               = 59,
            HYPNOTIZE             = 60,
            FORGETFULNESS         = 61,
            BLIND                 = 62,
            TELEPORT              = 63,
            REMOVE_OBSTACLE       = 64,
            CLONE                 = 65,
            FIRE_ELEMENTAL        = 66,
            EARTH_ELEMENTAL       = 67,
            WATER_ELEMENTAL       = 68,
            AIR_ELEMENTAL         = 69,
            /* These abilities are not available to heroes */
            STONE                 = 70,
            POISON                = 71,
            BIND                  = 72,
            DISEASE               = 73,
            PARALYZE              = 74,
            AGING                 = 75,
            DEATH_CLOUD           = 76,
            THUNDERBOLT           = 77,
            DRAGONFLY_DISPEL      = 78,
            DEATH_STARE           = 79,
            ACID_BREATH           = 80,
        };
    }

    namespace NH3Terrains
    {
        enum eTerrainType : INT32
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

    namespace NH3Towns
    {
        enum eTownType
        {
            NEUTRAL    = -1,
            CASTLE     = 0,
            RAMPART    = 1,
            TOWER      = 2,
            INFERNO    = 3,
            NECROPOLIS = 4,
            DUNGEON    = 5,
            STRONGHOLD = 6,
            FORTRESS   = 7,
            CONFLUX    = 8,
        };

        enum eBuildings // from ERM help
        {
            B_MAGE_GUILD1              = 0,
            B_MAGE_GUILD2              = 1,
            B_MAGE_GUILD3              = 2,
            B_MAGE_GUILD4              = 3,
            B_MAGE_GUILD5              = 4,
            B_TAVERN                   = 5,
            B_WHARF                    = 6,
            B_FORT                     = 7,
            B_CITADEL                  = 8,
            B_CASTLE                   = 9,
            B_VILAGE_HALL              = 10,
            B_TOWN_HALL                = 11,
            B_CITY_HALL                = 12,
            B_CAPITOL                  = 13,
            B_MARKET                   = 14,
            B_RESOURCE_SILO            = 15,
            B_BLACKSMITH               = 16,
            B_SPEC17                   = 17,
            B_HORDE1                   = 18,
            B_HORDE1U                  = 19,
            B_WHARF2                   = 20,
            B_SPEC21                   = 21,
            B_SPEC22                   = 22,
            B_SPEC23                   = 23,
            B_HORDE2                   = 24,
            B_HORDE2U                  = 25,
            B_GRAIL                    = 26,
            B_DECOR27                  = 27,
            B_DECOR28                  = 28,
            B_DECOR29                  = 29,
            B_DWELL1                   = 30,
            B_DWELL2                   = 31,
            B_DWELL3                   = 32,
            B_DWELL4                   = 33,
            B_DWELL5                   = 34,
            B_DWELL6                   = 35,
            B_DWELL7                   = 36,
            B_DWELL1U                  = 37,
            B_DWELL2U                  = 38,
            B_DWELL3U                  = 39,
            B_DWELL4U                  = 40,
            B_DWELL5U                  = 41,
            B_DWELL6U                  = 42,
            B_DWELL7U                  = 43,

            /* CASTLE */
            B_LIGHTHOUSE               = 17,
            B_STABLES                  = 21,
            B_BROTHERHOOD_OF_THE_SWORD = 22,

            /* RAMPART */
            B_MYSTIC_POND              = 17,
            B_FOUNTAIN_OF_FORTUNE      = 21,
            B_DWARVEN_TREASURY         = 22,

            /* TOWER */
            B_ARTIFACT_MERCHANT        = 17, // same for Dungeon and Conflux
            B_LOOKOUT_TOWER            = 21,
            B_LIBRARY                  = 22,
            B_WALL_OF_KNOWLEDGE        = 23,

            /* INFERNO */
            B_BRIMSTONECLOUDS          = 21,
            B_CASTLE_GATE              = 22,
            B_ORDER_OF_FIRE            = 23,

            /* NECROPOLIS */
            B_VEIL_OF_DARKNESS         = 17,
            B_NECROMANCY_AMPLIFIER     = 21,
            B_SKELETON_TRANSFORMER     = 22,

            /*  DUNGEON */
            B_MANA_VORTEX              = 21,
            B_PORTAL_OF_SUMMONING      = 22,
            B_BATTLE_ACADEMY           = 23,

            /* STRONGHOLD */
            B_ESCAPE_TUNNEL            = 17,
            B_FREELANCERS_GUILD        = 21,
            B_BALLISTA_YARD            = 22,
            B_HALL_OF_VALHALLA         = 23,

            /* FORTRESS */
            B_CAGE_OF_WARLORDS         = 17,
            B_GLYPHS_OF_FEAR           = 21,
            B_BLOOD_OBELISK            = 22,

            /* CONFLUX */
            B_MAGIC_UNIVERSITY         = 21
        };

        enum eNeutralBuildings
        {
            MAGE_GUILD       = 0,
            MAGE_GUILD2      = 1,
            MAGE_GUILD3      = 2,
            MAGE_GUILD4      = 3,
            MAGE_GUILD5      = 4,
            TAVERN           = 5,
            DOCK             = 6,
            CASTLE_FORT      = 7,
            CASTLE_CITADEL   = 8,
            CASTLE_CASTLE    = 9,
            HALL_VILLAGE     = 10,
            HALL_TOWN        = 11,
            HALL_CITY        = 12,
            HALL_CAPITOL     = 13,
            MARKETPLACE      = 14,
            MARKETPLACE_SILO = 15,
            BLACKSMITH       = 16,

        };

        enum eBuildingRequirements
        {
            BLD_REQ_MAGE1         = 0,
            BLD_REQ_MAGE2         = 1,
            BLD_REQ_MAGE3         = 2,
            BLD_REQ_MAGE4         = 3,
            BLD_REQ_MAGE5         = 4,
            BLD_REQ_TAVERN        = 5,
            BLD_REQ_WHARF         = 6,
            BLD_REQ_FORT          = 7,
            BLD_REQ_CITADEL       = 8,
            BLD_REQ_CASTLE        = 9,
            BLD_REQ_VILLAGE_HALL  = 10,
            BLD_REQ_TOWN_HALL     = 11,
            BLD_REQ_CITY_HALL     = 12,
            BLD_REQ_CAPITOL       = 13,
            BLD_REQ_MARKET        = 14,
            BLD_REQ_RESOURCE_SILO = 15,
            BLD_REQ_BLACKSMITH    = 16,
            BLD_REQ_SPEC17        = 17,
            BLD_REQ_HORDE1        = 18,
            BLD_REQ_HORDE1U       = 19,
            BLD_REQ_WHARF2        = 20,
            BLD_REQ_SPEC21        = 21,
            BLD_REQ_SPEC22        = 22,
            BLD_REQ_SPEC23        = 23,
            BLD_REQ_HORDE2        = 24,
            BLD_REQ_HORDE2U       = 25,
            BLD_REQ_GRAIL         = 26,
            BLD_REQ_DECOR27       = 27,
            BLD_REQ_DECOR28       = 28,
            BLD_REQ_DECOR29       = 29,
            BLD_REQ_DWELL1        = 30,
            BLD_REQ_DWELL2        = 31,
            BLD_REQ_DWELL3        = 32,
            BLD_REQ_DWELL4        = 33,
            BLD_REQ_DWELL5        = 34,
            BLD_REQ_DWELL6        = 35,
            BLD_REQ_DWELL7        = 36,
            BLD_REQ_DWELL1U       = 37,
            BLD_REQ_DWELL2U       = 38,
            BLD_REQ_DWELL3U       = 39,
            BLD_REQ_DWELL4U       = 40,
            BLD_REQ_DWELL5U       = 41,
            BLD_REQ_DWELL6U       = 42,
            BLD_REQ_DWELL7U       = 43,
        };

        enum eSpecialBuildings
        {
            /* Castle */
            LIGHTHOUSE = 0,
            GRIFFIN_HORDE,
            ROYAL_GRIFFIN_HORDE,
            UNUSED_CASTLE1,
            STABLES,
            TAVERN_UPGRADE,
            UNUSED_CASTLE2,
            UNUSED_CASTLE3,
            UNUSED_CASTLE4,

            /* Rampart */
            MYSTIC_GARDEN = 0,
            DWARF_HORDE,
            BATTLE_DWARF_HORDE,
            UNUSED_RAMPART1,
            RAINBOW,
            TREASURY,
            UNUSED_RAMPART2,
            TREEFOLK_HORDE,
            BRIAR_TREEFOLK_HORDE,

            /* Tower */
            ARTIFACT_MERCHANTS_TOWER = 0,
            STONE_GARGOYLE_HORDE,
            OBSIDIAN_GARGOYLE_HORDE,
            UNUSED_TOWER1,
            WATCHTOWER,
            LIBRARY,
            WALL_OF_GLYPHIC_KNOWLEDGE,
            UNUSED_TOWER2,
            UNUSED_TOWER3,

            /* Inferno */
            UNUSED_INFERNO1 = 0,
            IMP_HORDE,
            FAMILIAR_HORDE,
            UNUSED_INFERNO2,
            BRIMSTONE_STORMCLOUDS,
            CASTLE_GATE,
            ORDER_OF_FIRE,
            HELL_HOUND_HORDE,
            CERBERUS_HORDE,

            /* Necropolis */
            COVER_OF_DARKNESS = 0,
            SKELETON_HORDE,
            SKELETON_WARRIOR_HORDE,
            UNUSED_NECROPOLIS1,
            NECROMANCY_AMPLIFIER,
            SKELETON_TRANSFORMER,
            UNUSED_NECROPOLIS2,
            UNUSED_NECROPOLIS3,
            UNUSED_NECROPOLIS4,

            /* Dungeon */
            ARTIFACT_MERCHANTS_DUNGEON = 0,
            TROGLODYTE_HORDE,
            INFERNAL_TROGLODYTE_HORDE,
            UNUSED_DUNGEON1,
            MANA_VORTEX,
            PORTAL_OF_SUMMONING,
            ACADEMY_OF_BATTLE_SCHOLARS,
            UNUSED_DUNGEON2,
            UNUSED_DUNGEON3,

            /* Stronghold */
            ESCAPE_TUNNEL = 0,
            GOBLIN_HORDE,
            HOBGOBLIN_HORDE,
            UNUSED_STRONGHOLD1,
            FREELANCERS_GUILD,
            BALLISTA_WORKS,
            HALL_OF_VALHALLA,
            UNUSED_STRONGHOLD2,
            UNUSED_STRONGHOLD3,

            /* Fortress */
            DEFENSE_CAGE = 0,
            GNOLL_HORDE,
            GNOLL_MARAUDER_HORDE,
            UNUSED_FORTRESS1,
            SIEGE_DEFENSE,
            SIEGE_ATTACK,
            UNUSED_FORTRESS2,
            UNUSED_FORTRESS3,
            UNUSED_FORTRESS4,

            /* Conflux */
            ARTIFACT_MERCHANTS = 0,
            PIXIE_HORDE,
            SPRITE_HORDE,
            UNUSED_CONFLUX1,
            MAGIC_UNIVERSITY,
            UNUSED_CONFLUX2,
            UNUSED_CONFLUX3,
            UNUSED_CONFLUX4,
            UNUSED_CONFLUX5,
        };
    }

    namespace NH3Victory
    {
        enum eType : INT8
        {
            NONE                  = -1,
            ACQUIRE_ARTIFACT      = 0,
            ACCUMULATE_CREATURE   = 1,
            ACCUMULATE_RESOURCE   = 2,
            UPGRADE_TOWN          = 3,
            BUILD_HOLY_GRAIL      = 4,
            DEFEAT_HERO           = 5,
            CAPTURE_TOWN          = 6,
            DEFEAT_MONSTER        = 7,
            FLAG_GENERATORS       = 8,
            FLAG_MINES            = 9,
            TRANSPORT_ARTIFACT    = 10,
            FESTIVAL_OF_LIFE      = 11, // You have defeated all of the monsters plaguing this land!
            FOOLHARDY_WAYWARDNESS = 12, // You have managed to survive!
        };
    }

    namespace NH3VKey
    {
        // * modifies equivalent WM_ messages into H3 messages
        enum eMessageType
        {
            MT_KEY_DOWN       = 1,  // 0x100
            MT_KEY_UP         = 2,  // 0x101
            MT_MOUSE_MOVE     = 4,  // 0x200
            MT_LBUTTON_DOWN   = 8,  // 0x201
            MT_LBUTTON_UP     = 16, // 0x202
            MT_LBUTTON_DBLCLK = 8,  // 0x203
            MT_RBUTTON_DOWN   = 32, // 0x204
            MT_RBUTTON_UP     = 64, // 0x205
            MT_RBUTTON_DBLCLK = 32, // 0x206
        };

        enum eVirtualKeys : INT32
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
        enum eClickId
        {
            H3ID_OK     = 30725,
            H3ID_CANCEL = 30726
        };

        namespace Text
        {
            LPCSTR const TINY    = (LPCSTR(0x660CB4)); // "tiny.fnt"
            LPCSTR const SMALL   = (LPCSTR(0x65F2F8)); // "smalfont.fnt"
            LPCSTR const MEDIUM  = (LPCSTR(0x65F2EC)); // "MedFont.fnt"
            LPCSTR const BIG     = (LPCSTR(0x660B24)); // "bigfont.fnt"
            LPCSTR const VERDANA = (LPCSTR(0x6700B4)); // "Verd10B.fnt"
        } // namespace Text

        namespace TextAlignment
        {
            enum eTextAlignment : INT32
            {
                HLEFT         = 0,
                HCENTER       = 1,
                HRIGHT        = 2,
                VTOP          = 0,
                VCENTER       = 4,
                VBOTTOM       = 8,
                BOTTOM_LEFT   = HLEFT   | VBOTTOM,
                BOTTOM_CENTER = HCENTER | VBOTTOM,
                BOTTOM_RIGHT  = HRIGHT  | VBOTTOM,
                MIDDLE_LEFT   = HLEFT   | VCENTER,
                MIDDLE_CENTER = HCENTER | VCENTER,
                MIDDLE_RIGHT  = HRIGHT  | VCENTER,
                TOP_LEFT      = HLEFT   | VTOP,
                TOP_MIDDLE    = HCENTER | VTOP,
                TOP_RIGHT     = HRIGHT  | VTOP,
            };
        } // namespace TextAlignment

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
        } // namespace TextColor

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
            LPCSTR const ICM005_DEF       = (LPCSTR(0x66FFD4));  // 48x36
            LPCSTR const ALTART_DEF       = (LPCSTR(0x683178));  // 64x32
            LPCSTR const VWSYMBOL_DEF     = (LPCSTR(0x68C740));  // 32x32
            LPCSTR const SYSLB_DEF        = (LPCSTR(0x670124));  // 18x36
        } // namespace Assets

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
        } // namespace HDassets

        namespace PictureCategories
        {
            constexpr INT RESOURCE        = 0;  /**< @brief 0..6 wood..gold */
            constexpr INT ARTIFACT        = 8;	/**< @brief */
            constexpr INT SPELL           = 9;	/**< @brief */
            constexpr INT FLAG            = 10;	/**< @brief player flags */
            constexpr INT POSITIVE_LUCK   = 11;	/**< @brief */
            constexpr INT NEUTRAL_LUCK    = 12;	/**< @brief */
            constexpr INT NEGATIVE_LUCK   = 13;	/**< @brief */
            constexpr INT POSITIVE_MORALE = 14;	/**< @brief */
            constexpr INT NEUTRAL_MORALE  = 15;	/**< @brief */
            constexpr INT NEGATIVE_MORALE = 16;	/**< @brief */
            constexpr INT EXPERIENCE      = 17;	/**< @brief */
            constexpr INT SECONDARY_SKILL = 20;	/**< @brief */
            constexpr INT MONSTER         = 21;	/**< @brief */
            constexpr INT TOWN_BUILDINGS  = 22;	/**< @brief by town (22..30 => 0..8) */
            constexpr INT PRIMARY_SKILLS  = 31;	/**< @brief by skill (31..34 => 0..3) */
            constexpr INT SPELL_POINTS    = 35;	/**< @brief */
            constexpr INT MONEY           = 36;	/**< @brief */
        }

        namespace ID
        {
            namespace MainMenu
            {
                constexpr INT32 VTABLE     = 0x63FF60;
                constexpr INT32 NEW_GAME   = 101;
                constexpr INT32 LOAD_GAME  = 102;
                constexpr INT32 HIGH_SCORE = 103;
                constexpr INT32 CREDITS    = 104;
                constexpr INT32 QUIT       = 105;
            } // namespace MainMenu

            namespace HighScore
            {
                constexpr INT32 VTABLE   = 0x63EB98;
                constexpr INT32 EXIT     = 30722;
                constexpr INT32 CAMPAIGN = 1001;
                constexpr INT32 STANDARD = 1002;
                constexpr INT32 RESET    = 1003;
                /* others range from 1004 to 1025 */
            } // namespace HighScore

            namespace LoadGame
            {
                constexpr INT32 VTABLE      = 0x63E6D8;
                constexpr INT32 SINGLE      = 100;
                constexpr INT32 MULTIPLAYER = 102;
                constexpr INT32 CAMPAIGN    = 101;
                constexpr INT32 TUTORIAL    = 103;
                constexpr INT32 QUIT        = 104;
            } // namespace LoadGame

            namespace NewGame
            {
                constexpr INT32 VTABLE      = 0x63E6D8;
                constexpr INT32 SINGLE      = 100;
                constexpr INT32 MULTIPLAYER = 102;
                constexpr INT32 CAMPAIGN    = 101;
                constexpr INT32 TUTORIAL    = 103;
                constexpr INT32 QUIT        = 104;
            } // namespace NewGame

            namespace SelectScenario
            {
                    constexpr INT32 SCENARIO_NAME          = 101;
                    constexpr INT32 EASY_DIFFICULTY        = 107;
                    constexpr INT32 NORMAL_DIFFICULTY      = 108;
                    constexpr INT32 HARD_DIFFICULTY        = 109;
                    constexpr INT32 EXPERT_DIFFICULTY      = 110;
                    constexpr INT32 IMPOSSIBLE_DIFFICULTY  = 111;
                    constexpr INT32 RED_ALLY_FLAG          = 112;
                    constexpr INT32 BLUE_ALLY_FLAG         = 113;
                    constexpr INT32 TAN_ALLY_FLAG          = 114;
                    constexpr INT32 GREEN_ALLY_FLAG        = 115;
                    constexpr INT32 ORANGE_ALLY_FLAG       = 116;
                    constexpr INT32 PURPLE_ALLY_FLAG       = 117;
                    constexpr INT32 TEAL_ALLY_FLAG         = 118;
                    constexpr INT32 PINK_ALLY_FLAG         = 119;
                    constexpr INT32 RED_ENEMY_FLAG         = 120;
                    constexpr INT32 BLUE_ENEMY_FLAG        = 121;
                    constexpr INT32 TAN_ENEMY_FLAG         = 122;
                    constexpr INT32 GREEN_ENEMY_FLAG       = 123;
                    constexpr INT32 ORANGE_ENEMY_FLAG      = 124;
                    constexpr INT32 PURPLE_ENEMY_FLAG      = 125;
                    constexpr INT32 TEAL_ENEMY_FLAG        = 126;
                    constexpr INT32 PINK_ENEMY_FLAG        = 127;
                    constexpr INT32 SHOW_SCENARIOS         = 128;
                    constexpr INT32 ADVANCED_OPTIONS       = 129;
                    constexpr INT32 RANDOM_MAP             = 130;
                    constexpr INT32 SMALL_SIZE             = 137;
                    constexpr INT32 MEDIUM_SIZE            = 138;
                    constexpr INT32 LARGE_SIZE             = 139;
                    constexpr INT32 XLARGE_SIZE            = 140;
                    constexpr INT32 ALL_SIZE               = 141;

                    constexpr INT32 MAP_INDEX_0            = 142;
                    constexpr INT32 MAP_INDEX_1            = 143;
                    constexpr INT32 MAP_INDEX_2            = 144;
                    constexpr INT32 MAP_INDEX_3            = 145;
                    constexpr INT32 MAP_INDEX_4            = 146;
                    constexpr INT32 MAP_INDEX_5            = 147;
                    constexpr INT32 MAP_INDEX_6            = 148;
                    constexpr INT32 MAP_INDEX_7            = 149;
                    constexpr INT32 MAP_INDEX_8            = 150;
                    constexpr INT32 MAP_INDEX_9            = 151;
                    constexpr INT32 MAP_INDEX_10           = 152;
                    constexpr INT32 MAP_INDEX_11           = 153;
                    constexpr INT32 MAP_INDEX_12           = 154;
                    constexpr INT32 MAP_INDEX_13           = 155;
                    constexpr INT32 MAP_INDEX_14           = 156;
                    constexpr INT32 MAP_INDEX_15           = 157;
                    constexpr INT32 MAP_INDEX_16           = 158;
                    constexpr INT32 MAP_INDEX_17           = 159;

                    constexpr INT32 BEGIN                  = 186;
                    constexpr INT32 BACK                   = 188;
                    constexpr INT32 SELECTED_SIZE          = 189;
                    constexpr INT32 SORT_PLAYER            = 190;
                    constexpr INT32 SORT_SIZE              = 191;
                    constexpr INT32 SORT_VERSION           = 192;
                    constexpr INT32 SORT_NAME              = 193;
                    constexpr INT32 SORT_VICTORY           = 194;
                    constexpr INT32 SORT_LOSS              = 195;
                    constexpr INT32 RED_TOWN_LEFT          = 215;
                    constexpr INT32 BLUE_TOWN_LEFT         = 216;
                    constexpr INT32 TAN_TOWN_LEFT          = 217;
                    constexpr INT32 GREEN_TOWN_LEFT        = 218;
                    constexpr INT32 ORANGE_TOWN_LEFT       = 219;
                    constexpr INT32 PURPLE_TOWN_LEFT       = 220;
                    constexpr INT32 TEAL_TOWN_LEFT         = 221;
                    constexpr INT32 PINK_TOWN_LEFT         = 222;
                    constexpr INT32 RED_TOWN_RIGHT         = 223;
                    constexpr INT32 BLUE_TOWN_RIGHT        = 224;
                    constexpr INT32 TAN_TOWN_RIGHT         = 225;
                    constexpr INT32 GREEN_TOWN_RIGHT       = 226;
                    constexpr INT32 ORANGE_TOWN_RIGHT      = 227;
                    constexpr INT32 PURPLE_TOWN_RIGHT      = 228;
                    constexpr INT32 TEAL_TOWN_RIGHT        = 229;
                    constexpr INT32 PINK_TOWN_RIGHT        = 230;
                    constexpr INT32 RED_HERO_LEFT          = 231;
                    constexpr INT32 BLUE_HERO_LEFT         = 232;
                    constexpr INT32 TAN_HERO_LEFT          = 233;
                    constexpr INT32 GREEN_HERO_LEFT        = 234;
                    constexpr INT32 ORANGE_HERO_LEFT       = 235;
                    constexpr INT32 PURPLE_HERO_LEFT       = 236;
                    constexpr INT32 TEAL_HERO_LEFT         = 237;
                    constexpr INT32 PINK_HERO_LEFT         = 238;
                    constexpr INT32 RED_HERO_RIGHT         = 239;
                    constexpr INT32 BLUE_HERO_RIGHT        = 240;
                    constexpr INT32 TAN_HERO_RIGHT         = 241;
                    constexpr INT32 GREEN_HERO_RIGHT       = 242;
                    constexpr INT32 ORANGE_HERO_RIGHT      = 243;
                    constexpr INT32 PURPLE_HERO_RIGHT      = 244;
                    constexpr INT32 TEAL_HERO_RIGHT        = 245;
                    constexpr INT32 PINK_HERO_RIGHT        = 246;
                    constexpr INT32 RED_BONUS_LEFT         = 247;
                    constexpr INT32 BLUE_BONUS_LEFT        = 248;
                    constexpr INT32 TAN_BONUS_LEFT         = 249;
                    constexpr INT32 GREEN_BONUS_LEFT       = 250;
                    constexpr INT32 ORANGE_BONUS_LEFT      = 251;
                    constexpr INT32 PURPLE_BONUS_LEFT      = 252;
                    constexpr INT32 TEAL_BONUS_LEFT        = 253;
                    constexpr INT32 PINK_BONUS_LEFT        = 254;
                    constexpr INT32 RED_BONUS_RIGHT        = 255;
                    constexpr INT32 BLUE_BONUS_RIGHT       = 256;
                    constexpr INT32 TAN_BONUS_RIGHT        = 257;
                    constexpr INT32 GREEN_BONUS_RIGHT      = 258;
                    constexpr INT32 ORANGE_BONUS_RIGHT     = 259;
                    constexpr INT32 PURPLE_BONUS_RIGHT     = 260;
                    constexpr INT32 TEAL_BONUS_RIGHT       = 261;
                    constexpr INT32 PINK_BONUS_RIGHT       = 262;
                    constexpr INT32 RED_BANNER             = 263;
                    constexpr INT32 BLUE_BANNER            = 264;
                    constexpr INT32 TAN_BANNER             = 265;
                    constexpr INT32 GREEN_BANNER           = 266;
                    constexpr INT32 ORANGE_BANNER          = 267;
                    constexpr INT32 PURPLE_BANNER          = 268;
                    constexpr INT32 TEAL_BANNER            = 269;
                    constexpr INT32 PINK_BANNER            = 270;
                    constexpr INT32 RANDOM_SMALL           = 281;
                    constexpr INT32 RANDOM_MEDIUM          = 282;
                    constexpr INT32 RANDOM_LARGE           = 283;
                    constexpr INT32 RANDOM_XLARGE          = 284;
                    constexpr INT32 RANDOM_UNDERGROUND     = 285;
                    constexpr INT32 RANDOM_HUMAN1          = 287;
                    constexpr INT32 RANDOM_HUMAN2          = 288;
                    constexpr INT32 RANDOM_HUMAN3          = 289;
                    constexpr INT32 RANDOM_HUMAN4          = 290;
                    constexpr INT32 RANDOM_HUMAN5          = 291;
                    constexpr INT32 RANDOM_HUMAN6          = 292;
                    constexpr INT32 RANDOM_HUMAN7          = 293;
                    constexpr INT32 RANDOM_HUMAN8          = 294;
                    constexpr INT32 RANDOM_HUMAN_RANDOM    = 295;
                    constexpr INT32 RANDOM_COMPUTER0       = 307;
                    constexpr INT32 RANDOM_COMPUTER1       = 308;
                    constexpr INT32 RANDOM_COMPUTER2       = 309;
                    constexpr INT32 RANDOM_COMPUTER3       = 310;
                    constexpr INT32 RANDOM_COMPUTER4       = 311;
                    constexpr INT32 RANDOM_COMPUTER5       = 312;
                    constexpr INT32 RANDOM_COMPUTER6       = 313;
                    constexpr INT32 RANDOM_COMPUTER7       = 314;
                    constexpr INT32 RANDOM_COMPUTER_RANDOM = 315;
                    constexpr INT32 RANDOM_WATER_NONE      = 326;
                    constexpr INT32 RANDOM_WATER_NORMAL    = 327;
                    constexpr INT32 RANDOM_WATER_ISLANDS   = 328;
                    constexpr INT32 RANDOM_WATER_RANDOM    = 329;
                    constexpr INT32 RANDOM_MONSTER_WEAK    = 331;
                    constexpr INT32 RANDOM_MONSTER_NORMAL  = 332;
                    constexpr INT32 RANDOM_MONSTER_STRONG  = 333;
                    constexpr INT32 RANDOM_MONSTER_RANDOM  = 334;
                    constexpr INT32 MAPS_SCROLLBAR         = 337;
                    constexpr INT32 TIMER_SCROLLBAR        = 338;
                    constexpr INT32 RED_NAME               = 345;
                    constexpr INT32 BLUE_NAME              = 346;
                    constexpr INT32 TAN_NAME               = 347;
                    constexpr INT32 GREEN_NAME             = 348;
                    constexpr INT32 ORANGE_NAME            = 349;
                    constexpr INT32 PURPLE_NAME            = 350;
                    constexpr INT32 TEAL_NAME              = 351;
                    constexpr INT32 PINK_NAME              = 352;
                    constexpr INT32 RED_HERO               = 362;
                    constexpr INT32 BLUE_HERO              = 363;
                    constexpr INT32 TAN_HERO               = 364;
                    constexpr INT32 GREEN_HERO             = 365;
                    constexpr INT32 ORANGE_HERO            = 366;
                    constexpr INT32 PURPLE_HERO            = 367;
                    constexpr INT32 TEAL_HERO              = 368;
                    constexpr INT32 PINK_HERO              = 369;
                    constexpr INT32 RED_TOWN               = 370;
                    constexpr INT32 BLUE_TOWN              = 371;
                    constexpr INT32 TAN_TOWN               = 372;
                    constexpr INT32 GREEN_TOWN             = 373;
                    constexpr INT32 ORANGE_TOWN            = 374;
                    constexpr INT32 PURPLE_TOWN            = 375;
                    constexpr INT32 TEAL_TOWN              = 376;
                    constexpr INT32 PINK_TOWN              = 377;
                    constexpr INT32 RED_BONUS              = 378;
                    constexpr INT32 BLUE_BONUS             = 379;
                    constexpr INT32 TAN_BONUS              = 380;
                    constexpr INT32 GREEN_BONUS            = 381;
                    constexpr INT32 ORANGE_BONUS           = 382;
                    constexpr INT32 PURPLE_BONUS           = 383;
                    constexpr INT32 TEAL_BONUS             = 384;
                    constexpr INT32 PINK_BONUS             = 385;
                    constexpr INT32 PLAYER_FLAGS           = 387;

                    constexpr INT32 TIMER_STYLE     = 3005; // hdmod
                    constexpr INT32 MORE_OPTIONS    = 6999;
                    constexpr INT32 RANDOM_TEMPLATE = 7002;
                    constexpr INT32 TEAM_ALIGNMENT  = 7005;
            }
        } // namespace ID
    } // namespace NH3Dlg
#pragma warning(pop)
}

#endif /* #define _H3_CONSTANTS_HPP_ */