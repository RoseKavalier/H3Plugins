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
	constexpr INT PIKEMAN             = 0;
	constexpr INT HALBERDIER          = 1;
	constexpr INT ARCHER              = 2;
	constexpr INT MARKSMAN            = 3;
	constexpr INT GRIFFIN             = 4;
	constexpr INT ROYAL_GRIFFIN       = 5;
	constexpr INT SWORDSMAN           = 6;
	constexpr INT CRUSADER            = 7;
	constexpr INT MONK                = 8;
	constexpr INT ZEALOT              = 9;
	constexpr INT CAVALIER            = 10;
	constexpr INT CHAMPION            = 11;
	constexpr INT ANGEL               = 12;
	constexpr INT ARCHANGEL           = 13;
	constexpr INT CENTAUR             = 14;
	constexpr INT CENTAUR_CAPTAIN     = 15;
	constexpr INT DWARF               = 16;
	constexpr INT BATTLE_DWARF        = 17;
	constexpr INT WOOD_ELF            = 18;
	constexpr INT GRAND_ELF           = 19;
	constexpr INT PEGASUS             = 20;
	constexpr INT SILVER_PEGASUS      = 21;
	constexpr INT DENDROID_GUARD      = 22;
	constexpr INT DENDROID_SOLDIER    = 23;
	constexpr INT UNICORN             = 24;
	constexpr INT WAR_UNICORN         = 25;
	constexpr INT GREEN_DRAGON        = 26;
	constexpr INT GOLD_DRAGON         = 27;
	constexpr INT GREMLIN             = 28;
	constexpr INT MASTER_GREMLIN      = 29;
	constexpr INT STONE_GARGOYLE      = 30;
	constexpr INT OBSIDIAN_GARGOYLE   = 31;
	constexpr INT STONE_GOLEM         = 32;
	constexpr INT IRON_GOLEM          = 33;
	constexpr INT MAGE                = 34;
	constexpr INT ARCH_MAGE           = 35;
	constexpr INT GENIE               = 36;
	constexpr INT MASTER_GENIE        = 37;
	constexpr INT NAGA                = 38;
	constexpr INT NAGA_QUEEN          = 39;
	constexpr INT GIANT               = 40;
	constexpr INT TITAN               = 41;
	constexpr INT IMP                 = 42;
	constexpr INT FAMILIAR            = 43;
	constexpr INT GOG                 = 44;
	constexpr INT MAGOG               = 45;
	constexpr INT HELL_HOUND          = 46;
	constexpr INT CERBERUS            = 47;
	constexpr INT DEMON               = 48;
	constexpr INT HORNED_DEMON        = 49;
	constexpr INT PIT_FIEND           = 50;
	constexpr INT PIT_LORD            = 51;
	constexpr INT EFREETI             = 52;
	constexpr INT EFREET_SULTAN       = 53;
	constexpr INT DEVIL               = 54;
	constexpr INT ARCH_DEVIL          = 55;
	constexpr INT SKELETON            = 56;
	constexpr INT SKELETON_WARRIOR    = 57;
	constexpr INT WALKING_DEAD        = 58;
	constexpr INT ZOMBIE              = 59;
	constexpr INT WIGHT               = 60;
	constexpr INT WRAITH              = 61;
	constexpr INT VAMPIRE             = 62;
	constexpr INT VAMPIRE_LORD        = 63;
	constexpr INT LICH                = 64;
	constexpr INT POWER_LICH          = 65;
	constexpr INT BLACK_KNIGHT        = 66;
	constexpr INT DREAD_KNIGHT        = 67;
	constexpr INT BONE_DRAGON         = 68;
	constexpr INT GHOST_DRAGON        = 69;
	constexpr INT TROGLODYTE          = 70;
	constexpr INT INFERNAL_TROGLODYTE = 71;
	constexpr INT HARPY               = 72;
	constexpr INT HARPY_HAG           = 73;
	constexpr INT BEHOLDER            = 74;
	constexpr INT EVIL_EYE            = 75;
	constexpr INT MEDUSA              = 76;
	constexpr INT MEDUSA_QUEEN        = 77;
	constexpr INT MINOTAUR            = 78;
	constexpr INT MINOTAUR_KING       = 79;
	constexpr INT MANTICORE           = 80;
	constexpr INT SCORPICORE          = 81;
	constexpr INT RED_DRAGON          = 82;
	constexpr INT BLACK_DRAGON        = 83;
	constexpr INT GOBLIN              = 84;
	constexpr INT HOBGOBLIN           = 85;
	constexpr INT WOLF_RIDER          = 86;
	constexpr INT WOLF_RAIDER         = 87;
	constexpr INT ORC                 = 88;
	constexpr INT ORC_CHIEFTAIN       = 89;
	constexpr INT OGRE                = 90;
	constexpr INT OGRE_MAGE           = 91;
	constexpr INT ROC                 = 92;
	constexpr INT THUNDERBIRD         = 93;
	constexpr INT CYCLOPS             = 94;
	constexpr INT CYCLOPS_KING        = 95;
	constexpr INT BEHEMOTH            = 96;
	constexpr INT ANCIENT_BEHEMOTH    = 97;
	constexpr INT GNOLL               = 98;
	constexpr INT GNOLL_MARAUDER      = 99;
	constexpr INT LIZARDMAN           = 100;
	constexpr INT LIZARD_WARRIOR      = 101;
	constexpr INT GORGON              = 102;
	constexpr INT MIGHTY_GORGON       = 103;
	constexpr INT SERPENT_FLY         = 104;
	constexpr INT DRAGON_FLY          = 105;
	constexpr INT BASILISK            = 106;
	constexpr INT GREATER_BASILISK    = 107;
	constexpr INT WYVERN              = 108;
	constexpr INT WYVERN_MONARCH      = 109;
	constexpr INT HYDRA               = 110;
	constexpr INT CHAOS_HYDRA         = 111;
	constexpr INT AIR_ELEMENTAL       = 112;
	constexpr INT EARTH_ELEMENTAL     = 113;
	constexpr INT FIRE_ELEMENTAL      = 114;
	constexpr INT WATER_ELEMENTAL     = 115;
	constexpr INT GOLD_GOLEM          = 116;
	constexpr INT DIAMOND_GOLEM       = 117;
	constexpr INT PIXIE               = 118;
	constexpr INT SPRITE              = 119;
	constexpr INT PSYCHIC_ELEMENTAL   = 120;
	constexpr INT MAGIC_ELEMENTAL     = 121;
	constexpr INT NOT_USED1           = 122;
	constexpr INT ICE_ELEMENTAL       = 123;
	constexpr INT NOT_USED2           = 124;
	constexpr INT MAGMA_ELEMENTAL     = 125;
	constexpr INT NOT_USED3           = 126;
	constexpr INT STORM_ELEMENTAL     = 127;
	constexpr INT NOT_USED4           = 128;
	constexpr INT ENERGY_ELEMENTAL    = 129;
	constexpr INT FIREBIRD            = 130;
	constexpr INT PHOENIX             = 131;
	constexpr INT AZURE_DRAGON        = 132;
	constexpr INT CRYSTAL_DRAGON      = 133;
	constexpr INT FAERIE_DRAGON       = 134;
	constexpr INT RUST_DRAGON         = 135;
	constexpr INT ENCHANTER           = 136;
	constexpr INT SHARPSHOOTER        = 137;
	constexpr INT HALFLING            = 138;
	constexpr INT PEASANT             = 139;
	constexpr INT BOAR                = 140;
	constexpr INT MUMMY               = 141;
	constexpr INT NOMAD               = 142;
	constexpr INT ROGUE               = 143;
	constexpr INT TROLL               = 144;
	constexpr INT CATAPULT            = 145;
	constexpr INT BALLISTA            = 146;
	constexpr INT FIRST_AID_TENT      = 147;
	constexpr INT AMMO_CART           = 148;
	constexpr INT ARROW_TOWER         = 149;
	/* HotA */
	constexpr INT CANNON              = 150;
	constexpr INT SEA_DOG             = 151;
	constexpr INT HOTA_UNUSED         = 152;
	constexpr INT NYMPH               = 153;
	constexpr INT OCEANIDS            = 154;
	constexpr INT CREW_MATE           = 155;
	constexpr INT SEA_MAN             = 156;
	constexpr INT PIRATE              = 157;
	constexpr INT CORSAIR             = 158;
	constexpr INT STORMBIRD           = 159;
	constexpr INT AYSSID              = 160;
	constexpr INT SEA_WITCH           = 161;
	constexpr INT SORCERESS           = 162;
	constexpr INT NIX                 = 163;
	constexpr INT NIX_WARRIOR         = 164;
	constexpr INT SEA_SERPENT         = 165;
	constexpr INT HASPID              = 166;
	constexpr INT SATYR               = 167;
	constexpr INT FANGARM             = 168;
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
	constexpr INT KNIGHT       = 0;
	constexpr INT CLERIC       = 1;
	constexpr INT RANGER       = 2;
	constexpr INT DRUID        = 3;
	constexpr INT ALCHEMIST    = 4;
	constexpr INT WIZARD       = 5;
	constexpr INT DEMONIAC     = 6;
	constexpr INT HERETIC      = 7;
	constexpr INT DEATH_KNIGHT = 8;
	constexpr INT NECROMANCER  = 9;
	constexpr INT OVERLORD     = 10;
	constexpr INT WARLOCK      = 11;
	constexpr INT BARBARIAN    = 12;
	constexpr INT BATTLE_MAGE  = 13;
	constexpr INT BEASTMASTER  = 14;
	constexpr INT WITCH        = 15;
	constexpr INT PLANESWALKER = 16;
	constexpr INT ELEMENTALIST = 17;

	/* Knight (Castle) */
	constexpr INT ORRIN        = 0;
	constexpr INT VALESKA      = 1;
	constexpr INT EDRIC        = 2;
	constexpr INT SYLVIA       = 3;
	constexpr INT LORD_HAART   = 4;
	constexpr INT SORSHA       = 5;
	constexpr INT CHRISTIAN    = 6;
	constexpr INT TYRIS        = 7;

	/* Cleric (Castle) */
	constexpr INT RION         = 8;
	constexpr INT ADELA        = 9;
	constexpr INT CUTHBERT     = 10;
	constexpr INT ADELAIDE     = 11;
	constexpr INT INGHAM       = 12;
	constexpr INT SANYA        = 13;
	constexpr INT LOYNIS       = 14;
	constexpr INT CAITLIN      = 15;

	/* Ranger (Rampart) */
	constexpr INT MEPHALA      = 16;
	constexpr INT UFRETIN      = 17;
	constexpr INT JENOVA       = 18;
	constexpr INT RYLAND       = 19;
	constexpr INT THORGRIM     = 20;
	constexpr INT IVOR         = 21;
	constexpr INT CLANCY       = 22;
	constexpr INT KYRRE        = 23;

	/* Druid (Rampart) */
	constexpr INT CORONIUS     = 24;
	constexpr INT ULAND        = 25;
	constexpr INT ELLESHAR     = 26;
	constexpr INT GEM          = 27;
	constexpr INT MALCOM       = 28;
	constexpr INT MELODIA      = 29;
	constexpr INT ALAGAR       = 30;
	constexpr INT AERIS        = 31;

	/* Alchemist (Tower) */
	constexpr INT PIQUEDRAM    = 32;
	constexpr INT THANE        = 33;
	constexpr INT JOSEPHINE    = 34;
	constexpr INT NEELA        = 35;
	constexpr INT TOROSAR      = 36;
	constexpr INT FAFNER       = 37;
	constexpr INT RISSA        = 38;
	constexpr INT IONA         = 39;

	/* Wizard (Tower) */
	constexpr INT ASTRAL       = 40;
	constexpr INT HALON        = 41;
	constexpr INT SERENA       = 42;
	constexpr INT DAREMYTH     = 43;
	constexpr INT THEODORUS    = 44;
	constexpr INT SOLMYR       = 45;
	constexpr INT CYRA         = 46;
	constexpr INT AINE         = 47;

	/* Demoniac (Inferno) */
	constexpr INT FIONA        = 48;
	constexpr INT RASHKA       = 49;
	constexpr INT MARIUS       = 50;
	constexpr INT IGNATIUS     = 51;
	constexpr INT OCTAVIA      = 52;
	constexpr INT CALH         = 53;
	constexpr INT PYRE         = 54;
	constexpr INT NYMUS        = 55;

	/* Heretic (Inferno) */
	constexpr INT AYDEN        = 56;
	constexpr INT XYRON        = 57;
	constexpr INT AXSIS        = 58;
	constexpr INT OLEMA        = 59;
	constexpr INT CALID        = 60;
	constexpr INT ASH          = 61;
	constexpr INT ZYDAR        = 62;
	constexpr INT XARFAX       = 63;

	/* Death Knight (Necropolis) */
	constexpr INT STRAKER      = 64;
	constexpr INT VOKIAL       = 65;
	constexpr INT MOANDOR      = 66;
	constexpr INT CHARNA       = 67;
	constexpr INT TAMIKA       = 68;
	constexpr INT ISRA         = 69;
	constexpr INT CLAVIUS      = 70;
	constexpr INT GALTHRAN     = 71;

	/* Necromancer (Necropolis) */
	constexpr INT SEPTIENNA    = 72;
	constexpr INT AISLINN      = 73;
	constexpr INT SANDRO       = 74;
	constexpr INT NIMBUS       = 75;
	constexpr INT THANT        = 76;
	constexpr INT XSI          = 77;
	constexpr INT VIDOMINA     = 78;
	constexpr INT NAGASH       = 79;

	/* Overlord (Dungeon) */
	constexpr INT LORELEI      = 80;
	constexpr INT ARLACH       = 81;
	constexpr INT DACE         = 82;
	constexpr INT AJIT         = 83;
	constexpr INT DAMACON      = 84;
	constexpr INT GUNNAR       = 85;
	constexpr INT SYNCA        = 86;
	constexpr INT SHAKTI       = 87;

	/* Warlock (Dungeon) */
	constexpr INT ALAMAR       = 88;
	constexpr INT JAEGAR       = 89;
	constexpr INT MALEKITH     = 90;
	constexpr INT JEDDITE      = 91;
	constexpr INT GEON         = 92;
	constexpr INT DEEMER       = 93;
	constexpr INT SEPHINROTH   = 94;
	constexpr INT DARKSTORN    = 95;

	/* Barbarian (Stronghold) */
	constexpr INT YOG          = 96;
	constexpr INT GURNISSON    = 97;
	constexpr INT JABARKAS     = 98;
	constexpr INT SHIVA        = 99;
	constexpr INT GRETCHIN     = 100;
	constexpr INT KRELLION     = 101;
	constexpr INT CRAG_HACK    = 102;
	constexpr INT TYRAXOR      = 103;

	/* Battle Mage (Stronghold) */
	constexpr INT GIRD         = 104;
	constexpr INT VEY          = 105;
	constexpr INT DESSA        = 106;
	constexpr INT TEREK        = 107;
	constexpr INT ZUBIN        = 108;
	constexpr INT GUNDULA      = 109;
	constexpr INT ORIS         = 100;
	constexpr INT SAURUG       = 111;

	/* Beastmaster (Fortress) */
	constexpr INT BRON         = 112;
	constexpr INT DRAKON       = 113;
	constexpr INT WYSTAN       = 114;
	constexpr INT TAZAR        = 115;
	constexpr INT ALKIN        = 116;
	constexpr INT KORBAC       = 117;
	constexpr INT GERWULF      = 118;
	constexpr INT BROGHILD     = 119;

	/* Witch (Fortress) */
	constexpr INT MIRLANDA     = 120;
	constexpr INT ROSIC        = 121;
	constexpr INT VOY          = 122;
	constexpr INT VERDISH      = 123;
	constexpr INT MERIST       = 124;
	constexpr INT STYG         = 125;
	constexpr INT ANDRA        = 126;
	constexpr INT TIVA         = 127;

	/* Planeswalker (Conflux) */
	constexpr INT PASIS        = 128;
	constexpr INT THUNAR       = 129;
	constexpr INT IGNISSA      = 130;
	constexpr INT LACUS        = 131;
	constexpr INT MONERE       = 132;
	constexpr INT ERDAMON      = 133;
	constexpr INT FIUR         = 134;
	constexpr INT KALT         = 135;

	/* Elementalist (Conflux) */
	constexpr INT LUNA         = 136;
	constexpr INT BRISSA       = 137;
	constexpr INT CIELE        = 138;
	constexpr INT LABETHA      = 139;
	constexpr INT INTEUS       = 140;
	constexpr INT AENAIN       = 141;
	constexpr INT GELARE       = 142;
	constexpr INT GRINDAN      = 143;

	/* Special  (Campaign) */
	constexpr INT SIR_MULLICH  = 144;
	constexpr INT ADRIENNE     = 145;
	constexpr INT CATHERINE    = 146;
	constexpr INT DRACON       = 147;
	constexpr INT GELU         = 148;
	constexpr INT KILGOR       = 149;
	constexpr INT LORD_HAART2  = 150;
	constexpr INT MUTARE       = 151;
	constexpr INT ROLAND       = 152;
	constexpr INT MUTARE_DRAKE = 153;
	constexpr INT BORAGUS      = 154;
	constexpr INT XERON        = 155;

	/* HotA*/
	constexpr INT BIDLEY       = 156;
	constexpr INT CORKES       = 157;
	constexpr INT JEREMY       = 158;
	constexpr INT ILLOR        = 159;
	constexpr INT ASTRA        = 160;
	constexpr INT DEREK        = 161;
	constexpr INT LEENA        = 162;
	constexpr INT TARK         = 163;
	constexpr INT EOVACIUS     = 164;
	constexpr INT SPINT        = 165;
	constexpr INT ANDAL        = 166;
	constexpr INT MANFRED      = 167;
	constexpr INT ZILARE       = 168;
	constexpr INT CASMETRA     = 169;
	constexpr INT ANABEL       = 170;
	constexpr INT DARGEM       = 171;
	constexpr INT CASSIOPEIA   = 172;
	constexpr INT MIRIAM       = 173;
	constexpr INT ELMOR        = 174;
	constexpr INT BEATRICE     = 175;
	constexpr INT KINKERIA     = 176;
	constexpr INT RANLU        = 177;
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
	constexpr INT NO_OBJ                      = -1;
	constexpr INT ALTAR_OF_SACRIFICE          = 2;
	constexpr INT ANCHOR_POINT                = 3;
	constexpr INT ARENA                       = 4;
	constexpr INT ARTIFACT                    = 5;
	constexpr INT PANDORAS_BOX                = 6;
	constexpr INT BLACK_MARKET                = 7;
	constexpr INT BOAT                        = 8;
	constexpr INT BORDERGUARD                 = 9;
	constexpr INT KEYMASTER                   = 10;
	constexpr INT BUOY                        = 11;
	constexpr INT CAMPFIRE                    = 12;
	constexpr INT CARTOGRAPHER                = 13;
	constexpr INT SWAN_POND                   = 14;
	constexpr INT COVER_OF_DARKNESS           = 15;
	constexpr INT CREATURE_BANK               = 16;
	constexpr INT CREATURE_GENERATOR1         = 17;
	constexpr INT CREATURE_GENERATOR2         = 18;
	constexpr INT CREATURE_GENERATOR3         = 19;
	constexpr INT CREATURE_GENERATOR4         = 20;
	constexpr INT CURSED_GROUND               = 21;
	constexpr INT CORPSE                      = 22;
	constexpr INT MARLETTO_TOWER              = 23;
	constexpr INT DERELICT_SHIP               = 24;
	constexpr INT DRAGON_UTOPIA               = 25;
	constexpr INT EVENT                       = 26;
	constexpr INT EYE_OF_MAGI                 = 27;
	constexpr INT FAERIE_RING                 = 28;
	constexpr INT FLOTSAM                     = 29;
	constexpr INT FOUNTAIN_OF_FORTUNE         = 30;
	constexpr INT FOUNTAIN_OF_YOUTH           = 31;
	constexpr INT GARDEN_OF_REVELATION        = 32;
	constexpr INT GARRISON                    = 33;
	constexpr INT HERO                        = 34;
	constexpr INT HILL_FORT                   = 35;
	constexpr INT GRAIL                       = 36;
	constexpr INT HUT_OF_MAGI                 = 37;
	constexpr INT IDOL_OF_FORTUNE             = 38;
	constexpr INT LEAN_TO                     = 39;
	constexpr INT DECORATIVE                  = 40;
	constexpr INT LIBRARY_OF_ENLIGHTENMENT    = 41;
	constexpr INT LIGHTHOUSE                  = 42;
	constexpr INT MONOLITH_ONE_WAY_ENTRANCE   = 43;
	constexpr INT MONOLITH_ONE_WAY_EXIT       = 44;
	constexpr INT MONOLITH_TWO_WAY            = 45;
	constexpr INT MAGIC_PLAINS1               = 46;
	constexpr INT SCHOOL_OF_MAGIC             = 47;
	constexpr INT MAGIC_SPRING                = 48;
	constexpr INT MAGIC_WELL                  = 49;
	constexpr INT MARKET_OF_TIME              = 50;
	constexpr INT MERCENARY_CAMP              = 51;
	constexpr INT MERMAID                     = 52;
	constexpr INT MINE                        = 53;
	constexpr INT MONSTER                     = 54;
	constexpr INT MYSTICAL_GARDEN             = 55;
	constexpr INT OASIS                       = 56;
	constexpr INT OBELISK                     = 57;
	constexpr INT REDWOOD_OBSERVATORY         = 58;
	constexpr INT OCEAN_BOTTLE                = 59;
	constexpr INT PILLAR_OF_FIRE              = 60;
	constexpr INT STAR_AXIS                   = 61;
	constexpr INT PRISON                      = 62;
	constexpr INT PYRAMID                     = 63;
	constexpr INT RALLY_FLAG                  = 64;
	constexpr INT RANDOM_ART                  = 65;
	constexpr INT RANDOM_TREASURE_ART         = 66;
	constexpr INT RANDOM_MINOR_ART            = 67;
	constexpr INT RANDOM_MAJOR_ART            = 68;
	constexpr INT RANDOM_RELIC_ART            = 69;
	constexpr INT RANDOM_HERO                 = 70;
	constexpr INT RANDOM_MONSTER              = 71;
	constexpr INT RANDOM_MONSTER_L1           = 72;
	constexpr INT RANDOM_MONSTER_L2           = 73;
	constexpr INT RANDOM_MONSTER_L3           = 74;
	constexpr INT RANDOM_MONSTER_L4           = 75;
	constexpr INT RANDOM_RESOURCE             = 76;
	constexpr INT RANDOM_TOWN                 = 77;
	constexpr INT REFUGEE_CAMP                = 78;
	constexpr INT RESOURCE                    = 79;
	constexpr INT SANCTUARY                   = 80;
	constexpr INT SCHOLAR                     = 81;
	constexpr INT SEA_CHEST                   = 82;
	constexpr INT SEER_HUT                    = 83;
	constexpr INT CRYPT                       = 84;
	constexpr INT SHIPWRECK                   = 85;
	constexpr INT SHIPWRECK_SURVIVOR          = 86;
	constexpr INT SHIPYARD                    = 87;
	constexpr INT SHRINE_OF_MAGIC_INCANTATION = 88;
	constexpr INT SHRINE_OF_MAGIC_GESTURE     = 89;
	constexpr INT SHRINE_OF_MAGIC_THOUGHT     = 90;
	constexpr INT SIGN                        = 91;
	constexpr INT SIRENS                      = 92;
	constexpr INT SPELL_SCROLL                = 93;
	constexpr INT STABLES                     = 94;
	constexpr INT TAVERN                      = 95;
	constexpr INT TEMPLE                      = 96;
	constexpr INT DEN_OF_THIEVES              = 97;
	constexpr INT TOWN                        = 98;
	constexpr INT TRADING_POST                = 99;
	constexpr INT LEARNING_STONE              = 100;
	constexpr INT TREASURE_CHEST              = 101;
	constexpr INT TREE_OF_KNOWLEDGE           = 102;
	constexpr INT SUBTERRANEAN_GATE           = 103;
	constexpr INT UNIVERSITY                  = 104;
	constexpr INT WAGON                       = 105;
	constexpr INT WAR_MACHINE_FACTORY         = 106;
	constexpr INT SCHOOL_OF_WAR               = 107;
	constexpr INT WARRIORS_TOMB               = 108;
	constexpr INT WATER_WHEEL                 = 109;
	constexpr INT WATERING_HOLE               = 110;
	constexpr INT WHIRLPOOL                   = 111;
	constexpr INT WINDMILL                    = 112;
	constexpr INT WITCH_HUT                   = 113;
	constexpr INT BRUSH                       = 114;
	constexpr INT BUSH                        = 115;
	constexpr INT CACTUS                      = 116;
	constexpr INT CANYON                      = 117;
	constexpr INT CRATER                      = 118;
	constexpr INT DEAD_VEGETATION             = 119;
	constexpr INT FLOWERS                     = 120;
	constexpr INT FROZEN_LAKE                 = 121;
	constexpr INT HEDGE                       = 122;
	constexpr INT HILL                        = 123;
	constexpr INT HOLE                        = 124;
	constexpr INT KELP                        = 125;
	constexpr INT LAKE                        = 126;
	constexpr INT LAVA_FLOW                   = 127;
	constexpr INT LAVA_LAKE                   = 128;
	constexpr INT MUSHROOMS                   = 129;
	constexpr INT LOG                         = 130;
	constexpr INT MANDRAKE                    = 131;
	constexpr INT MOSS                        = 132;
	constexpr INT MOUND                       = 133;
	constexpr INT MOUNTAIN                    = 134;
	constexpr INT OAK_TREES                   = 135;
	constexpr INT OUTCROPPING                 = 136;
	constexpr INT PINE_TREES                  = 137;
	constexpr INT PLANT                       = 138;
	constexpr INT BLANK1                      = 139;
	constexpr INT BLANK2                      = 140;
	constexpr INT BLANK3                      = 141;
	constexpr INT BLANK4                      = 142;
	constexpr INT RIVER_DELTA                 = 143;
	constexpr INT BLANK5                      = 144;
	constexpr INT BLANK6                      = 145;
	constexpr INT BLANK7                      = 146;
	constexpr INT ROCK                        = 147;
	constexpr INT SAND_DUNE                   = 148;
	constexpr INT SAND_PIT                    = 149;
	constexpr INT SHRUB                       = 150;
	constexpr INT SKULL                       = 151;
	constexpr INT STALAGMITE                  = 152;
	constexpr INT STUMP                       = 153;
	constexpr INT TAR_PIT                     = 154;
	constexpr INT TREES                       = 155;
	constexpr INT VINE                        = 156;
	constexpr INT VOLCANIC_TENT               = 157;
	constexpr INT VOLCANO                     = 158;
	constexpr INT WILLOW_TREES                = 159;
	constexpr INT YUCCA_TREES                 = 160;
	constexpr INT REEF                        = 161;
	constexpr INT RANDOM_MONSTER_L5           = 162;
	constexpr INT RANDOM_MONSTER_L6           = 163;
	constexpr INT RANDOM_MONSTER_L7           = 164;
	constexpr INT BRUSH2                      = 165;
	constexpr INT BUSH2                       = 166;
	constexpr INT CACTUS2                     = 167;
	constexpr INT CANYON2                     = 168;
	constexpr INT CRATER2                     = 169;
	constexpr INT DEAD_VEGETATION2            = 170;
	constexpr INT FLOWERS2                    = 171;
	constexpr INT FROZEN_LAKE2                = 172;
	constexpr INT HEDGE2                      = 173;
	constexpr INT HILL2                       = 174;
	constexpr INT HOLE2                       = 175;
	constexpr INT KELP2                       = 176;
	constexpr INT LAKE2                       = 177;
	constexpr INT LAVA_FLOW2                  = 178;
	constexpr INT LAVA_LAKE2                  = 179;
	constexpr INT MUSHROOMS2                  = 180;
	constexpr INT LOG2                        = 181;
	constexpr INT MANDRAKE2                   = 182;
	constexpr INT MOSS2                       = 183;
	constexpr INT MOUND2                      = 184;
	constexpr INT MOUNTAIN2                   = 185;
	constexpr INT OAK_TREES2                  = 186;
	constexpr INT OUTCROPPING2                = 187;
	constexpr INT PINE_TREES2                 = 188;
	constexpr INT PLANT2                      = 189;
	constexpr INT RIVER_DELTA2                = 190;
	constexpr INT ROCK2                       = 191;
	constexpr INT SAND_DUNE2                  = 192;
	constexpr INT SAND_PIT2                   = 193;
	constexpr INT SHRUB2                      = 194;
	constexpr INT SKULL2                      = 195;
	constexpr INT STALAGMITE2                 = 196;
	constexpr INT STUMP2                      = 197;
	constexpr INT TAR_PIT2                    = 198;
	constexpr INT TREES2                      = 199;
	constexpr INT VINE2                       = 200;
	constexpr INT VOLCANIC_TENT2              = 201;
	constexpr INT VOLCANO2                    = 202;
	constexpr INT WILLOW_TREES2               = 203;
	constexpr INT YUCCA_TREES2                = 204;
	constexpr INT REEF2                       = 205;
	constexpr INT DESERT_HILLS                = 206;
	constexpr INT DIRT_HILLS                  = 207;
	constexpr INT GRASS_HILLS                 = 208;
	constexpr INT ROUGH_HILLS                 = 209;
	constexpr INT SUBTERRANEAN_ROCKS          = 210;
	constexpr INT SWAMP_FOLIAGE               = 211;
	constexpr INT BORDER_GATE                 = 212;
	constexpr INT FREELANCERS_GUILD           = 213;
	constexpr INT HERO_PLACEHOLDER            = 214;
	constexpr INT QUEST_GUARD                 = 215;
	constexpr INT RANDOM_DWELLING             = 216;
	constexpr INT RANDOM_DWELLING_LVL         = 217;
	constexpr INT RANDOM_DWELLING_FACTION     = 218;
	constexpr INT GARRISON2                   = 219;
	constexpr INT ABANDONED_MINE              = 220;
	constexpr INT TRADING_POST_SNOW           = 221;
	constexpr INT CLOVER_FIELD                = 222;
	constexpr INT CURSED_GROUND2              = 223;
	constexpr INT EVIL_FOG                    = 224;
	constexpr INT FAVORABLE_WINDS             = 225;
	constexpr INT FIERY_FIELDS                = 226;
	constexpr INT HOLY_GROUNDS                = 227;
	constexpr INT LUCID_POOLS                 = 228;
	constexpr INT MAGIC_CLOUDS                = 229;
	constexpr INT MAGIC_PLAINS2               = 230;
	constexpr INT ROCKLANDS                   = 231;
}

namespace NH3PlayerColors
{
	constexpr INT RED    = 0;
	constexpr INT BLUE   = 1;
	constexpr INT TAN    = 2;
	constexpr INT GREEN  = 3;
	constexpr INT ORANGE = 4;
	constexpr INT PURPLE = 5;
	constexpr INT TEAL   = 6;
	constexpr INT PINK   = 7;
}

namespace NH3Resources
{
	constexpr INT WOOD    = 0;
	constexpr INT MERCURY = 1;
	constexpr INT ORE     = 2;
	constexpr INT SULFUR  = 3;
	constexpr INT CRYSTAL = 4;
	constexpr INT GEMS    = 5;
	constexpr INT GOLD    = 6;
}

namespace NH3Skills
{
	constexpr INT ATTACK       = 0;
	constexpr INT DEFENSE      = 1;
	constexpr INT SPELL_POWER  = 2;
	constexpr INT KNOWLEDGE    = 3;

	constexpr INT PATHFINDING  = 0;
	constexpr INT ARCHERY      = 1;
	constexpr INT LOGISTICS    = 2;
	constexpr INT SCOUTING     = 3;
	constexpr INT DIPLOMACY    = 4;
	constexpr INT NAVIGATION   = 5;
	constexpr INT LEADERSHIP   = 6;
	constexpr INT WISDOM       = 7;
	constexpr INT MYSTICISM    = 8;
	constexpr INT LUCK         = 9;
	constexpr INT BALLISTICS   = 10;
	constexpr INT EAGLE_EYE    = 11;
	constexpr INT NECROMANCY   = 12;
	constexpr INT ESTATES      = 13;
	constexpr INT FIRE_MAGIC   = 14;
	constexpr INT AIR_MAGIC    = 15;
	constexpr INT WATER_MAGIC  = 16;
	constexpr INT EARTH_MAGIC  = 17;
	constexpr INT SCHOLAR      = 18;
	constexpr INT TACTICS      = 19;
	constexpr INT ARTILLERY    = 20;
	constexpr INT LEARNING     = 21;
	constexpr INT OFFENSE      = 22;
	constexpr INT ARMORER      = 23;
	constexpr INT INTELLIGENCE = 24;
	constexpr INT SORCERY      = 25;
	constexpr INT RESISTANCE   = 26;
	constexpr INT FIRST_AID    = 27;
}

namespace NH3Terrains
{
	constexpr INT DIRT         = 0;
	constexpr INT SAND         = 1;
	constexpr INT GRASS        = 2;
	constexpr INT SNOW         = 3;
	constexpr INT SWAMP        = 4;
	constexpr INT ROUGH        = 5;
	constexpr INT SUBTERRANEAN = 6;
	constexpr INT LAVA         = 7;
	constexpr INT WATER        = 8;
	constexpr INT ROCK         = 9;
}

namespace NH3VKey
{
	constexpr INT H3VK_ESCAPE        = 1;
	constexpr INT H3VK_1             = 2;
	constexpr INT H3VK_2             = 3;
	constexpr INT H3VK_3             = 4;
	constexpr INT H3VK_4             = 5;
	constexpr INT H3VK_5             = 6;
	constexpr INT H3VK_6             = 7;
	constexpr INT H3VK_7             = 8;
	constexpr INT H3VK_8             = 9;
	constexpr INT H3VK_9             = 10;
	constexpr INT H3VK_0             = 11;
	constexpr INT H3VK_MINUS         = 12;
	constexpr INT H3VK_PLUS          = 13;
	constexpr INT H3VK_BACKSPACE     = 14;
	constexpr INT H3VK_TAB           = 15;
	constexpr INT H3VK_Q             = 16;
	constexpr INT H3VK_W             = 17;
	constexpr INT H3VK_E             = 18;
	constexpr INT H3VK_R             = 19;
	constexpr INT H3VK_T             = 20;
	constexpr INT H3VK_Y             = 21;
	constexpr INT H3VK_U             = 22;
	constexpr INT H3VK_I             = 23;
	constexpr INT H3VK_O             = 24;
	constexpr INT H3VK_P             = 25;
	constexpr INT H3VK_LEFT_BRACKET  = 26;
	constexpr INT H3VK_RIGHT_BRACKET = 27;
	constexpr INT H3VK_ENTER         = 28;
	constexpr INT H3VK_CTRL          = 29;
	constexpr INT H3VK_A             = 30;
	constexpr INT H3VK_S             = 31;
	constexpr INT H3VK_D             = 32;
	constexpr INT H3VK_F             = 33;
	constexpr INT H3VK_G             = 34;
	constexpr INT H3VK_H             = 35;
	constexpr INT H3VK_J             = 36;
	constexpr INT H3VK_K             = 37;
	constexpr INT H3VK_L             = 38;
	constexpr INT H3VK_SEMICOLON     = 39;
	constexpr INT H3VK_APOSTROPHE    = 40;
	constexpr INT H3VK_TILDE         = 41;
	constexpr INT H3VK_SHIFT         = 42;
	constexpr INT H3VK_BACKSLASH     = 43;
	constexpr INT H3VK_Z             = 44;
	constexpr INT H3VK_X             = 45;
	constexpr INT H3VK_C             = 46;
	constexpr INT H3VK_V             = 47;
	constexpr INT H3VK_B             = 48;
	constexpr INT H3VK_N             = 49;
	constexpr INT H3VK_M             = 50;
	constexpr INT H3VK_COMMA         = 51;
	constexpr INT H3VK_PERIOD        = 52;
	constexpr INT H3VK_SLASH         = 53;
	constexpr INT H3VK_RIGHT_SHIFT   = 54;
	constexpr INT H3VK_PRINTSCREEN   = 55; // or * on numpad?

	constexpr INT H3VK_SPACEBAR      = 57;

	constexpr INT H3VK_F2            = 60;
	constexpr INT H3VK_F3            = 61;
	constexpr INT H3VK_F4            = 62;
	constexpr INT H3VK_F5            = 63;
	constexpr INT H3VK_F6            = 64;
	constexpr INT H3VK_F7            = 65;
	constexpr INT H3VK_F8            = 66;
	constexpr INT H3VK_F9            = 67;
	constexpr INT H3VK_F10           = 68;
	constexpr INT H3VK_PAUSE         = 69;
	constexpr INT H3VK_SCROLL_LOCK   = 70;
	constexpr INT H3VK_HOME          = 71;
	constexpr INT H3VK_UP            = 72;
	constexpr INT H3VK_PAGE_UP       = 73;
	constexpr INT H3VK_NUMPAD_MINUS  = 74;
	constexpr INT H3VK_LEFT          = 75;
	constexpr INT H3VK_NUMPAD5       = 76;
	constexpr INT H3VK_RIGHT         = 77;
	constexpr INT H3VK_NUMPAD_PLUS   = 78;
	constexpr INT H3VK_END           = 79;
	constexpr INT H3VK_DOWN          = 80;
	constexpr INT H3VK_PAGE_DOWN     = 81;
	constexpr INT H3VK_INSERT        = 82;
	constexpr INT H3VK_DELETE        = 83;

	constexpr INT H3VK_F11           = 87;
	constexpr INT H3VK_F12           = 88;

	constexpr INT H3VK_LEFT_WIN      = 91;
	constexpr INT H3VK_RIGHT_WIN     = 92;
	constexpr INT H3VK_RIGHT_CLICK   = 93;
}

namespace NH3Dlg
{
	namespace Text
	{
		LPCSTR const TINY    = ((LPCSTR)0x660CB4); // "tiny.fnt"
		LPCSTR const SMALL   = ((LPCSTR)0x65F2F8);   // "smalfont.fnt"
		LPCSTR const MEDIUM  = ((LPCSTR)0x65F2EC);   // "MedFont.fnt"
		LPCSTR const BIG     = ((LPCSTR)0x660B24);   // "bigfont.fnt"
		LPCSTR const VERDANA = ((LPCSTR)0x6700B4);   // "Verd10B.fnt"
	}

	namespace TextAlignment
	{
		constexpr INT HLeft        = 0;
		constexpr INT HCenter      = 1;
		constexpr INT HRight       = 2;
		constexpr INT VTop         = 0;
		constexpr INT VCenter      = 4;
		constexpr INT VBottom      = 8;
		constexpr INT BottomLeft   = HLeft   | VBottom;
		constexpr INT BottomCenter = HCenter | VBottom;
		constexpr INT BottomRight  = HRight  | VBottom;
		constexpr INT MiddleLeft   = HLeft   | VCenter;
		constexpr INT MiddleCenter = HCenter | VCenter;
		constexpr INT MiddleRight  = HRight  | VCenter;
		constexpr INT TopLeft      = HLeft   | VTop;
		constexpr INT TopMiddle    = HCenter | VTop;
		constexpr INT TopRight     = HRight  | VTop;
	};

	namespace TextColor
	{
		constexpr INT SILVER      = 0x00;
		constexpr INT REGULAR     = 0x01;
		constexpr INT HIGHLIGHT   = 0x02;
		constexpr INT GOLD        = 0x03;
		constexpr INT WHITE       = 0x04;
		constexpr INT GREEN       = 0x0D;
		constexpr INT LIGHT_GREEN = 0x0E;
		constexpr INT DARK_GREEN  = 0x0F;
		constexpr INT BLACK       = 0x17;
		constexpr INT BLUE        = 0x18;
		constexpr INT CYAN        = 0x1A;
		constexpr INT RED         = 0x1B;
		constexpr INT PURPLE      = 0x1C;
		constexpr INT YELLOW      = 0x1D;
		constexpr INT GRAY        = 0x36;
		constexpr INT RED2        = 0x37;
		constexpr INT BLUE2       = 0x38;
		constexpr INT TAN         = 0x39;
		constexpr INT DARK_GREEN2 = 0x3A;
		constexpr INT ORANGE      = 0x3B;
		constexpr INT PURPLE2     = 0x3C;
		constexpr INT DARK_CYAN   = 0x3D;
		constexpr INT PINK        = 0x3E;
		constexpr INT GRAY2       = 0x3F;
		constexpr INT YELLOW2     = 0x57;
		constexpr INT DARK_YELLOW = 0x58;
		constexpr INT TAN2        = 0x59;
		constexpr INT TAN3        = 0x5A;
		constexpr INT TAN4        = 0x5B;
		constexpr INT TAN5        = 0x5C;
		constexpr INT CYAN2       = 0x67;
		constexpr INT CYAN3       = 0x68;
		constexpr INT CYAN4       = 0x69;
		constexpr INT CYAN5       = 0x6A;
	}

	namespace Assets
	{
		LPCSTR const DLGBOX           = ((LPCSTR)0x66024C);  // "dialogbox.def" 64x64
		LPCSTR const DIBOXBACK        = ((LPCSTR)0x66025C);  // "diboxback.pcx" 256x256
		LPCSTR const ARTIFACT_DEF     = ((LPCSTR)0x660214);  // "artifact.def" 44x44
		LPCSTR const CREATURE_SMALL   = ((LPCSTR)0x660180);  // "CPRSMALL.def" 32x32
		LPCSTR const PSKILL_42        = ((LPCSTR)0x679D9C);  // "PSKIL42.def" 42x42
		LPCSTR const RESOURCE_DEF     = ((LPCSTR)0x660224);  // "resource.def" 32x32
		LPCSTR const RESOURCE_82      = ((LPCSTR)0x660114);  // "resour82.def" 82x93
		LPCSTR const SPELLS_DEF       = ((LPCSTR)0x660208);  // "spells.def"78x65
		LPCSTR const SSKILL_44        = ((LPCSTR)0x6601D0);  // "Secskill.def" 44x44
		LPCSTR const UN44_DEF         = ((LPCSTR)0x679D90);  // "un44.def"44x44
		LPCSTR const SPELL_SMALL      = ((LPCSTR)0x6700A4);  // "spellint.def" 48x36
		LPCSTR const OVBUTN3          = ((LPCSTR)0x6817C4);  // "OvButn3.def" 108x16
		LPCSTR const HERO_CADRE       = ((LPCSTR)0x65F3DC);  // hpsyyy.pcx 48x32
		LPCSTR const LARGE_HERO_CADRE = ((LPCSTR)0x68C45C);  // TPTavSel.pcx 62x68 ~decal by -2
		LPCSTR const CREATURE_LARGE   = ((LPCSTR)0x6700C0);  // TwCrPort.def 58x64
		LPCSTR const CANCEL_BUTTON    = ((LPCSTR)0x660B04);  // iCancel.def 64x30
		LPCSTR const CAST_SPELL       = ((LPCSTR)0x66FFD4);  // icm005.def 48x36
		LPCSTR const ARTS_ICON        = ((LPCSTR)0x683178);  // AltArt.def 64x32
		LPCSTR const MORALE_42        = ((LPCSTR)0x68C6DC);  // IMRL42.def 42x38
		LPCSTR const LUCK_42          = ((LPCSTR)0x68C6D0);  // ILCK42.def 42x38
		LPCSTR const CREST58          = ((LPCSTR)0x6601FC);  // CREST58.def 58x64
		LPCSTR const TOWN_SMALL       = ((LPCSTR)0x65F318);  // itpa.def 48x32
		LPCSTR const NO_VISION        = ((LPCSTR)0x6885A0);  // SYSOPB8.def 46x32
		LPCSTR const ADVENTURE_CURSOR = ((LPCSTR)0x68164C);  // cradvntr.def 40x40
		LPCSTR const ALT_ART          = ((LPCSTR)0x683178);  // AltArt.def 64x32
		LPCSTR const ON_OFF_CHECKBOX  = ((LPCSTR)0x6700F0);  // sysopchk.def 32x24
		LPCSTR const OKAY_DEF         = ((LPCSTR)0x670160);  // iOkay.def 64x30
		LPCSTR const OKAY32_DEF       = ((LPCSTR)0x682374);  // iOkay32.def 66x32
		LPCSTR const OKAY6432_DEF     = ((LPCSTR)0x65F470);  // iOk6432.def 64x32
		LPCSTR const BOX_64_30_PCX    = ((LPCSTR)0x67016C);  // Box64x30.pcx
		LPCSTR const BOX_66_32_PCX    = ((LPCSTR)0x682380);  // Box66x32.pcx
		LPCSTR const CANCEL_DEF       = ((LPCSTR)0x660B04);  // "iCancel.def" 64x30
		LPCSTR const VIEW_CREATURE    = ((LPCSTR)0x660134);  // iViewCr.def
		LPCSTR const VIEW_MAGNIFIER   = ((LPCSTR)0x68C734);  // VWMag1.def 60x32
		LPCSTR const iSAVE_DEF        = "ISAVE.DEF";         // iSave.def 64x32
		LPCSTR const BOX_64_32_PCX    = ((LPCSTR)0x68C640);  // Box64x32.pcx
		LPCSTR const GAME_TYPE_DEF    = ((LPCSTR)0x683568);  // 32x24
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