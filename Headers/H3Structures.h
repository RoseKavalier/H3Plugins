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

#ifndef _H3STRUCTURES_H_
#define _H3STRUCTURES_H_

#pragma once

#include "H3Base.h"
#include "H3BinaryItems.h"

struct _PlayerUnk_;
struct H3AdventureManager;
struct H3Army;
struct H3ArtifactMerchant;
struct H3ArtifactSetup;
struct H3BlackMarket;
struct H3Boat;
struct H3CampaignInfo;
struct H3CastleEvent;
struct H3CombatManager;
struct H3CombatMonster;
struct H3CombatMonsterSpellsData;
struct H3CombatSquare;
struct H3ComboArtifactSetup;
struct H3CreatureBank;
struct H3CreatureBankSetup;
struct H3CreatureBankState;
struct H3CreatureInformation;
struct H3Date;
struct H3DefFrame;
struct H3DefGroup;
struct H3Dwelling;
struct H3Event;
struct H3Garrison;
struct H3GlobalEvent;
struct H3Grail;
struct H3Hero;
struct H3HeroFlags;
struct H3HeroInfo;
struct H3HeroSpecialty;
struct H3InputManager;
struct H3LoadedDEF;
struct H3LoadedPCX;
struct H3LoadedPCX16;
struct H3MagicAnimation;
struct H3Main;
struct H3MainSetup;
struct H3Manager;
struct H3MapArtifact;
struct H3MapInfo;
struct H3MapItem;
struct H3MapResource;
struct H3Mine;
struct H3Monster;
struct H3MonsterAnimation;
struct H3MouseManager;
struct H3MovementManager;
struct H3ObjectAttributes;
struct H3ObjectDetails;
struct H3ObjectDraw;
struct H3Obstacle;
struct H3ObstacleInfo;
struct H3Palette555;
struct H3Palette888;
struct H3PandorasBox;
struct H3Player;
struct H3PlayersInfo;
struct H3PrimarySkills;
struct H3Quest;
struct H3QuestGuard;
struct H3Resources;
struct H3SeerHut;
struct H3SetupHero;
struct H3Signpost;
struct H3SoundManager;
struct H3TileMovement;
struct H3Town;
struct H3TownManager;
struct H3University;
struct H3WallSection;
struct H3WindowManager;
struct MapCampfire;
struct MapCorpse;
struct MapCreatureBank;
struct MapEvent;
struct MapLeanTo;
struct MapLearningStone;
struct MapMagicShrine;
struct MapMagicSpring;
struct MapMine;
struct MapMonolith;
struct MapMonster;
struct MapMysticGarden;
struct MapPyramid;
struct MapScholar;
struct MapShipyard;
struct MapSwanPond;
struct MapTreasureChest;
struct MapTreeOfKnowledge;
struct MapUniversity;
struct MapWagon;
struct MapWarriorsTomb;
struct MapWaterMill;
struct MapWindmill;
struct MapWitchHut;
struct TownTowerLoaded;
struct H3Position;
struct H3NetworkData;

#pragma pack(push, 1)

struct H3NetworkData
{
	// * +0
	INT recipient_id; // -1 means everyone
	INT _f_04;
	// * +8
	INT msg_id;
	// * +C
	INT buffer_size; // sizeof(*this) + extra size of H3NetworkData
	INT _f_10;
	// * +14
	INT short_data;
	// * more fields can be added here if more information is needed to be sent

	INT32 SendData() { return FASTCALL_4(INT32, 0x5549E0, this, 127, 0, 1); }
};

// * stored (x,y,z) coordinates H3format
struct H3Position
{
protected:
	UINT pos;
public:
	// * returns the packed coordinates
	UINT Mixed() const { return pos; }
	// * returns x from coordinates
	UINT8 GetX() { return UnpackX(pos); }
	// * returns y from coordinates
	UINT8 GetY() { return UnpackY(pos); }
	// * returns z from coordinates
	UINT8 GetZ() { return UnpackZ(pos); }
	// * provided variables x, y, z, unpacks the coordinates to those variables
	VOID GetXYZ(INT &x, INT &y, INT &z) { UnpackXYZ(pos, x, y, z); }
	// * modifies x
	VOID SetX(INT16 x)
	{
		pos &= ~0x3FF;
		pos |= (x & 0x3FF);
	}
	// * modifies y
	VOID SetY(INT16 y)
	{
		pos &= ~0x03FF0000;
		pos |= ((y & 0x3FF) << 16);
	}
	// * modifies z
	VOID SetZ(INT16 z)
	{
		pos &= ~0x04000000;
		pos |= ((z & 1) << 26);
	}
	// * modifies x, y and z
	VOID SetXYZ(INT x, INT y, INT z) { pos = Pack(x, y, z); }
	// * Can be used on the stack safely to pack coordinates
	static UINT Pack(INT x, INT y, INT z) { return ((x & 0x3FF) | ((y & 0x3FF) << 0x10) | ((z & 1) << 0x1A)); }
	// * Can be used on the stack safely to unpack coordinates
	static VOID UnpackXYZ(UINT &coord, INT &x, INT &y, INT &z)
	{
		x = UnpackX(coord);
		y = UnpackY(coord);
		z = UnpackZ(coord);
	}
	// * Can be used on the stack safely to unpack X
	static UINT8 UnpackX(UINT &coord) { return coord & 0xFF; }
	// * Can be used on the stack safely to unpack Y
	static UINT8 UnpackY(UINT &coord) { return (coord >> 16) & 0xFF; }
	// * Can be used on the stack safely to unpack Z
	static UINT8 UnpackZ(UINT &coord) { return (coord >> 26) & 1; }
};

// * artifacts as they appear on H3Hero structure
// * also used for artifact enum
struct H3Artifact
{
	INT32 id;
	INT32 subtype; // used for spell scrolls, otherwise -1

	enum eArtifacts
	{
		SPELLBOOK,
		SPELL_SCROLL,
		GRAIL,
		CATAPULT,
		BALLISTA,
		AMMO_CART,
		FIRST_AID_TENT,
		CENTAUR_AXE,
		BLACKSHARD_OF_THE_DEAD_KNIGHT,
		GREATER_GNOLLS_FLAIL,
		OGRES_CLUB_OF_HAVOC,
		SWORD_OF_HELLFIRE,
		TITANS_GLADIUS,
		SHIELD_OF_THE_DWARVEN_LORDS,
		SHIELD_OF_THE_YAWNING_DEAD,
		BUCKLER_OF_THE_GNOLL_KING,
		TARG_OF_THE_RAMPAGING_OGRE,
		SHIELD_OF_THE_DAMNED,
		SENTINELS_SHIELD,
		HELM_OF_THE_ALABASTER_UNICORN,
		SKULL_HELMET,
		HELM_OF_CHAOS,
		CROWN_OF_THE_SUPREME_MAGI,
		HELLSTORM_HELMET,
		THUNDER_HELMET,
		BREASTPLATE_OF_PETRIFIED_WOOD,
		RIB_CAGE,
		SCALES_OF_THE_GREATER_BASILISK,
		TUNIC_OF_THE_CYCLOPS_KING,
		BREASTPLATE_OF_BRIMSTONE,
		TITANS_CUIRASS,
		ARMOR_OF_WONDER,
		SANDALS_OF_THE_SAINT,
		CELESTIAL_NECKLACE_OF_BLISS,
		LIONS_SHIELD_OF_COURAGE,
		SWORD_OF_JUDGEMENT,
		HELM_OF_HEAVENLY_ENLIGHTENMENT,
		QUIET_EYE_OF_THE_DRAGON,
		RED_DRAGON_FLAME_TONGUE,
		DRAGON_SCALE_SHIELD,
		DRAGON_SCALE_ARMOR,
		DRAGONBONE_GREAVES,
		DRAGON_WING_TABARD,
		NECKLACE_OF_DRAGONTEETH,
		CROWN_OF_DRAGONTOOTH,
		STILL_EYE_OF_THE_DRAGON,
		CLOVER_OF_FORTUNE,
		CARDS_OF_PROPHECY,
		LADYBIRD_OF_LUCK,
		BADGE_OF_COURAGE,
		CREST_OF_VALOR,
		GLYPH_OF_GALLANTRY,
		SPECULUM,
		SPYGLASS,
		AMULET_OF_THE_UNDERTAKER,
		VAMPIRES_COWL,
		DEAD_MANS_BOOTS,
		GARNITURE_OF_INTERFERENCE,
		SURCOAT_OF_COUNTERPOISE,
		BOOTS_OF_POLARITY,
		BOW_OF_ELVEN_CHERRYWOOD,
		BOWSTRING_OF_THE_UNICORNS_MANE,
		ANGEL_FEATHER_ARROWS,
		BIRD_OF_PERCEPTION,
		STOIC_WATCHMAN,
		EMBLEM_OF_COGNIZANCE,
		STATESMANS_MEDAL,
		DIPLOMATS_RING,
		AMBASSADORS_SASH,
		RING_OF_THE_WAYFARER,
		EQUESTRIANS_GLOVES,
		NECKLACE_OF_OCEAN_GUIDANCE,
		ANGEL_WINGS,
		CHARM_OF_MANA,
		TALISMAN_OF_MANA,
		MYSTIC_ORB_OF_MANA,
		COLLAR_OF_CONJURING,
		RING_OF_CONJURING,
		CAPE_OF_CONJURING,
		ORB_OF_THE_FIRMAMENT,
		ORB_OF_SILT,
		ORB_OF_TEMPESTUOUS_FIRE,
		ORB_OF_DRIVING_RAIN,
		RECANTERS_CLOAK,
		SPIRIT_OF_OPPRESSION,
		HOURGLASS_OF_THE_EVIL_HOUR,
		TOME_OF_FIRE_MAGIC,
		TOME_OF_AIR_MAGIC,
		TOME_OF_WATER_MAGIC,
		TOME_OF_EARTH_MAGIC,
		BOOTS_OF_LEVITATION,
		GOLDEN_BOW,
		SPHERE_OF_PERMANENCE,
		ORB_OF_VULNERABILITY,
		RING_OF_VITALITY,
		RING_OF_LIFE,
		VIAL_OF_LIFEBLOOD,
		NECKLACE_OF_SWIFTNESS,
		BOOTS_OF_SPEED,
		CAPE_OF_VELOCITY,
		PENDANT_OF_DISPASSION,
		PENDANT_OF_SECOND_SIGHT,
		PENDANT_OF_HOLINESS,
		PENDANT_OF_LIFE,
		PENDANT_OF_DEATH,
		PENDANT_OF_FREE_WILL,
		PENDANT_OF_NEGATIVITY,
		PENDANT_OF_TOTAL_RECALL,
		PENDANT_OF_COURAGE,
		EVERFLOWING_CRYSTAL_CLOAK,
		RING_OF_INFINITE_GEMS,
		EVERPOURING_VIAL_OF_MERCURY,
		INEXHAUSTIBLE_CART_OF_ORE,
		EVERSMOKING_RING_OF_SULFUR,
		INEXHAUSTIBLE_CART_OF_LUMBER,
		ENDLESS_SACK_OF_GOLD,
		ENDLESS_BAG_OF_GOLD,
		ENDLESS_PURSE_OF_GOLD,
		LEGS_OF_LEGION,
		LOINS_OF_LEGION,
		TORSO_OF_LEGION,
		ARMS_OF_LEGION,
		HEAD_OF_LEGION,
		SEA_CAPTAINS_HAT,
		SPELLBINDERS_HAT,
		SHACKLES_OF_WAR,
		ORB_OF_INHIBITION,
		VIAL_OF_DRAGON_BLOOD,
		ARMAGEDDONS_BLADE,
		ANGELIC_ALLIANCE,
		CLOAK_OF_THE_UNDEAD_KING,
		ELIXIR_OF_LIFE,
		ARMOR_OF_THE_DAMNED,
		STATUE_OF_LEGION,
		POWER_OF_THE_DRAGON_FATHER,
		TITANS_THUNDER,
		ADMIRALS_HAT,
		BOW_OF_THE_SHARPSHOOTER,
		WIZARDS_WELL,
		RING_OF_THE_MAGI,
		CORNUCOPIA,
			/* WoG items */
		MAGIC_WAND_,
		GOLD_TOWER_ARROW,
		MONSTERS_POWER,
		HIGHLIGHTED_SLOT,
		ARTIFACT_LOCK,
		AXE_OF_SMASHING,
		MITHRIL_MAIL,
		SWORD_OF_SHARPNESS,
		HELM_OF_IMMORTALITY,
		PENDANT_OF_SORCERY,
		BOOTS_OF_HASTE,
		BOW_OF_SEEKING,
		DRAGON_EYE_RING,
		HARDENED_SHIELD,
		SLAVAS_RING_OF_POWER,
		WARLORDS_BANNER,
		CRIMSON_SHIELD_OF_RETRIBUTION,
		BARBARIAN_LORDS_AXE_OF_FEROCITY,
		DRAGONHEART,
		GATE_KEY,
		BLANK_HELMET,
		BLANK_SWORD,
		BLANK_SHIELD,
		BLANK_HORNED_RING,
		BLANK_GEMMED_RING,
		BLANK_NECK_BROACH,
		BLANK_ARMOR,
		BLANK_SURCOAT,
		BLANK_BOOTS,
		BLANK_HORN
	};

	enum eArtifactSlots
	{
		sHEAD,
		sSHOULDERS,
		sNECK,
		sRIGHT_HAND,
		sLEFT_HAND,
		sTORSO,
		sRIGHT_RING,
		sLEFT_RING,
		sFEET,
		sMISC1,
		sMISC2,
		sMISC3,
		sMISC4,
		sBALLISTA,
		sAMMO_CART,
		sFIRST_AID_TENT,
		sCATAPULT,
		sSPELLBOOK,
		sMISC5
	};
};

// * a reference to the 3 animation speeds of H3
struct H3AnimationSpeed
{
	float delay[3];
};

// * An "array" representing the 7 resources
struct H3Resources
{
	enum H3ResType
	{
		RT_Wood,
		RT_Mercury,
		RT_Ore,
		RT_Sulfur,
		RT_Crystal,
		RT_Gems,
		RT_Gold
	};

	INT32 wood;
	INT32 mercury;
	INT32 ore;
	INT32 sulfur;
	INT32 crystal;
	INT32 gems;
	INT32 gold;

	// * compares current values against cost
	// * returns true if every current value is greater or equal
	BOOL EnoughResources(H3Resources *cost) const;
	// * removes cost resources from current
	VOID RemoveResources(H3Resources *cost);
	// * adds resources to current
	VOID GainResourcesOF(H3Resources *gain);
};

// * The arrangment of 7 creatures on various H3 structures
struct H3Army
{
	INT32 type[7];
	INT32 count[7];

	// * add amount creature of type to slot
	VOID AddStack(INT32 type, INT32 amount, INT32 slot) { THISCALL_4(VOID, 0x44A9B0, this, type, amount, slot); }
	// * Split fromStack based on fraction denominator to toStack
	// * fraction = 2 cuts in half
	VOID SplitFromStackToStack(INT32 fromStack, INT32 toStack, INT32 fraction);
	// * the first type[] index to hold no creature
	INT32 FirstFreeSlot();
	// * the slot position of the n-th existing stack
	INT32 FindExistingByIndex(INT32 n);
	// * the number of existing stacks
	INT32 GetStackCount() { return THISCALL_1(INT32, 0x44A990, this); }
	// * Total number of creatures
	INT32 GetCreaturesCount() { return THISCALL_1(INT32, 0x44AA70, this); }
	// * has at least one creature cre
	BOOL8 HasCreatureType(INT32 cre) { return THISCALL_2(BOOL8, 0x44A850, this, cre); }
	// * not empty
	BOOL HasCreatures() { return THISCALL_1(BOOL, 0x449370, this); }
	// * remove all contents
	VOID Clear() { THISCALL_1(VOID, 0x44A750, this); }
	// * clear contents of stack #0-6
	VOID Clear(INT stack) { THISCALL_2(VOID, 0x44A830, this, stack); }
	// * removes contents and gives creatures
	VOID ClearAndGive(INT type, INT count) { THISCALL_3(VOID, 0x44A770, this, type, count); }
	// * checks if all stacks are flagged as undead
	BOOL8 IsUndeadArmy() { return THISCALL_1(BOOL8, 0x44A7F0, this); }
	// * the number of different creature alignments in an army
	// * the creature array can be empty
	INT32 NumberAlignments(INT8 towns[9]) { return THISCALL_2(INT32, 0x44A880, this, towns); }
	// * AI value total for army
	INT32 GetArmyValue() { return THISCALL_1(INT32, 0x44A950, this); }
};

// * not the hero on the map
struct H3SetupHero
{
	INT8	owner;
	UINT8   _u1[3];
	UINT32  number;  // ???
	UINT32  id;      // = Id
	UINT8   fl_N;    // = has custom name
	CHAR    name[13];
	UINT8   fl_E;    // = has experience
	UINT8   _u2;
	INT32   experience;
	UINT8   fl_P;    //   +20  db   = custom picture
	UINT8   pic;     //   +21  db   = picture id
	UINT8   fl_SS;   //   +22  db   = custom sskills
	UINT8   _u3;
	UINT32  sSNum;   //!   +24  dd   = number of sskills
	UINT8   sSkill[8];//  +28  dd*8
	UINT8   sSLev[8];//   +30  db*8
	UINT8   fl_C;    //   +38  db   = custom creatures
	UINT8   _u4[3];
	UINT32  cType[7];//   +3C  dd*7 = creature types
	UINT16  cNum[7]; //   +58  dw*7 = creature numbers
	UINT8   group;   //   +66  db   = spread/grouped?
	UINT8   fl_A;    //   +67  db   = custom arts?
	H3Artifact  bodyArt[19];//+68  dd*2*13 = equipped artifacts, first UINT32 = id, second is setup (for spellscroll, otherwise -1)
	H3Artifact  backpackArt[64];//+100 dd*2*40
	UINT8   backpackCount;   //   +300 db
	UINT16  x0, y0;   //   +301 2*dw
	UINT8   radius;  //!   +305 db
	UINT8   fl_B;    //   +306 db   = custom biblio?
	UINT8   _u6;
	H3String bibliography;
	UINT8   gender;     //   +318 dd
	UINT8   _u9[3];
	UINT8   fl_SP;   //   +31C db   = custom spells?
	UINT8   _u10[3];
	UINT8   spell[10];//  +320 db*A ?? length is correct ??
	UINT16  _u11;
	UINT8   fl_PS;   //   +32C db   = custom primary skills?
	INT8    pSkill[4];//  +32D db*4 = ADPK
	UINT8   _u12[3];
};

// * Starting Hero default data
struct H3HeroInfo
{
	// * Hero is enabled
	BOOL enabled;
protected:
	// * +4
	INT32 _u1[8];
public:
	// * +24
	INT32 armyType[3];
	// * +30
	// * Small portrait name
	LPCSTR smallPortrait;
	// * +34
	// * Large portrait name
	LPCSTR largePortrait;
protected:
	// * +38
	UINT8 _u2[8];
public:
	// * +40
	// * the default name
	LPCSTR name;
	// * +44
	// * Heroes at start can only get up to 3 stacks
	INT32 armyNum[3][2];
};

// * The specialty structure of heroes
struct H3HeroSpecialty
{
	UINT32  type;
	enum SpecialtyType
	{
		ST_skill,
		ST_creatureLevel,
		ST_resource,
		ST_spell,
		ST_staticCreature,
		ST_speed,
		ST_conversion,
		ST_dragon
	};
	// * +4
	// * the ID of skill, creature, resource, spell, creature to upgrade (Dracon/Gelu)
	UINT32  bonusID;
	// * +8
	// * to be used with creature bonus
	UINT32  attackBonus;
	// * +C
	// * to be used with creature bonus
	UINT32  defenseBonus;
	// * +10
	// * to be used with creature bonus
	UINT32  damageBonus;
	// * +14
	// * the ID of the second creature that can be upgraded
	UINT32  upgrade2;
	// * +18
	// * the ID of the upgraded creature (Enchanters/Sharpshooters)
	UINT32  upgradeTo;
	// * +1C
	// * short specialty name
	LPCSTR	spShort;
	// * +20
	// * full specialty name
	LPCSTR	spFull;
	// * +24
	// * specialty description
	LPCSTR	spDescr;
};

// * the start of the save/load structure used by H3
// * probably some stream or similar
struct H3Streambuf
{
protected:
	struct {
		h3func freeSave;
		// * +4
		h3func loadRegion;
		// * +8
		h3func saveRegion;
	}*vTable;

	// ...

public:
	BOOL Save(PVOID data, UINT data_size);
	BOOL Load(PVOID data, UINT data_size);
};

// * the bitfield flags for heroes
struct H3HeroFlags
{
	// * 0x1
	// * Visited Well
	unsigned well : 1;
	// * 0x2
	// * Visited Stables
	unsigned stables : 1;
	// * 0x4
	// * Visited Buoy
	unsigned buoy : 1; // 0x4
	// * 0x8
	// * Visited Swan Pond
	unsigned swan_pond : 1;
	// * 0x10
	// * Visited idol of fortune on days 1~6, morale bonys
	unsigned idol_fortune_morale : 1;
	// * 0x20
	// * -1 luck from fountain of fortune
	unsigned fountain_fortune1 : 1;
	// * 0x40
	// * visited watering hole
	unsigned watering_hole : 1;
	// * 0x80
	// * visited oasis
	unsigned oasis : 1;
	// * 0x100
	// * visited temple on days 1~6
	unsigned temple : 1;
	// * 0x200
	// * shipwreck morale penalty
	unsigned shipwreck : 1;
	// * 0x400
	// * crypt morale penalty
	unsigned crypt : 1;
	// * 0x800
	// * derelict ship morale penalty
	unsigned derelect_ship : 1;
	// * 0x1000
	// * pyramid morale penalty
	unsigned pyramid : 1;
	// * 0x2000
	// * visited faerie ring
	unsigned faerie_ring : 1;
	// * 0x4000
	// * visited fountain of youth
	unsigned fountain_of_youth : 1;
	// * 0x8000
	// * visited mermaids
	unsigned mermaids : 1;
	// * 0x10000
	// * visited rally flag
	unsigned rally_flag : 1;
	// * 0x20000
	// * hero is in tavern
	// * see 0x4DA4D1
	unsigned in_tavern : 1;
	// * 0x40000
	// * hero is in a boat
	unsigned in_boat : 1;
	// * 0x80000
	unsigned unk1 : 1;
	// * 0x100000
	// * visited sirens
	unsigned sirens : 1;
	// * 0x200000
	// * warrior's tomb morale penalty
	unsigned warrior_tomb : 1;
	// * 0x400000
	// * typed luck cheat
	unsigned luck_cheat : 1;
	// * 0x800000
	// * typed morale cheat
	unsigned morale_cheat : 1;
	// * 0x01000000
	// * typed speed cheat
	unsigned speed_cheat : 1;
	// * 0x02000000
	// * luck bonus from idol of fortune
	unsigned idol_fortune_luck : 1;
	// * 0x04000000
	// * visited temple on day 7, +2 morale
	unsigned temple2 : 1;
	// * 0x08000000
	// * +1 luck from fountain of fortune
	unsigned fountain_fortune2 : 1;
	// * 0x10000000
	// * +2 luck from fountain of fortune
	unsigned fountain_fortune3 : 1;
	// * 0x20000000
	// * +3 luck from fountain of fortune
	unsigned fountain_fortune4 : 1;
	// * 0x40000000
	// * 0x80000000
	unsigned unk4 : 2;
};

// * Hero structure on the adventure map
struct H3Hero
{
	// * +0
	INT16   x;
	// * +2
	INT16   y;
	// * +4
	INT16   z;
	// * +6
	// * used when the current hero is active and appears on H3MapItem
	BOOL8	isVisible;
	// * +7
	// * used to show / hide active hero
	H3Position  mixedPosition;
	// * +B
	// * true if there is an object below the hero
	BOOL8	objectBelow;
	// * +C
	// * the type of H3MapItem under hero
	INT32   objectTypeUnder;
protected:
	// * +10
	// * ??? related to H3MapItem under hero
	UINT32  _flag;
public:
	// * +14
	// * setup of H3MapItem under the hero
	UINT32  objectBelowSetup;
	// * +18
	// * the number of spellpoints
	INT16   spellPoints;
public:
	// * +1A
	// * 0~156, has to match class, cannot be used to change specialty
	INT32	id;
protected:
	h3unk	_f_1E[4]; // set at 4D8DB1, unknown
public:
	// * +22
	// * 0 ~ 7 Red ~ Pink
	INT8	owner;
	// * +23
	// * the hero's name
	CHAR	name[13];
	// * +30
	// * 0 ~ 0x11 Knight ~ Elementalist
	// * 0x12 boat sprite no class - can't navigate water (more sprites after but can crash)
	INT32   hero_class;
	// * +34
	// * the id of the hero's portrait, 0 ~ 156
	UINT8   picture;
	// * +35
	// * the planned x destination
	INT32	dest_x;
	// * +39
	// * the planned y destination
	INT32	dest_y;
	// * +3D
	// * the planned z destination
	INT32	dest_z;
protected:
	h3unk	_f_41[3];
public:
	// * +44
	// * starting x position
	UINT8   patrol_x;
	// * +45
	// * starting y position
	UINT8   patrol_y;
	// * +46
	// * the radius for patrolling, -1 means no range limit
	UINT8   patrolRadius;
protected:
	h3unk	_u3;       // +47 = ???
	UINT8   _flags;    // +48 = ???
public:
	// * +49
	// * the maximum movement points of the hero on a given turn
	INT32   maxMovement;
	// * +4D
	// * the remaining movement points of the hero on a given turn
	INT32   movement;
	// * +51
	// * the current experience of the hero
	INT32	experience;
	// * +55
	// * the current level of the hero
	INT16   level;
protected:
	// * +57
	// * bitfields of 32 visited object types per hero
	H3Bitfield  learningStones;
	// * +5B
	// * bitfields of 32 visited object types per hero
	H3Bitfield  marlettoTower;
	// * +5F
	// * bitfields of 32 visited object types per hero
	H3Bitfield  gardenRevelation;
	// * +63
	// * bitfields of 32 visited object types per hero
	H3Bitfield  mercenaryCamp;
	// * +67
	// * bitfields of 32 visited object types per hero
	H3Bitfield  starAxis;
	// * +6B
	// * bitfields of 32 visited object types per hero
	H3Bitfield  treeKnowldge;
	// * +6F
	// * bitfields of 32 visited object types per hero
	H3Bitfield  libraryEnlightenment;
	// * +73
	// * bitfields of 32 visited object types per hero
	H3Bitfield  arena;
	// * +77
	// * bitfields of 32 visited object types per hero
	H3Bitfield  schoolMagic;
	// * +7B
	// * bitfields of 32 visited object types per hero
	H3Bitfield  schoolWar;
	UINT8	_7F[16];
public:
	// * +8F
	// * the seed for skill tree, 1~255
	UINT8	levelSeed; // +8F
protected:
	UINT8	_f90;
public:
	// * +91
	// * the creatures of the hero
	H3Army army;
	// * +C9
	// * the level of each secondary skill
	INT8   secSkill[28];
	// * +E5
	// * the order in which to display SSkills (1,2,3,...)
	INT8   secSkillPosition[28];
	// * +101
	// * the number of secondary skills the hero has
	INT32  secSkillCount;
	// * +105
	// * temporary hero flags
	H3HeroFlags  flags;
protected:
	UINT8  _u6[4];   // +109
public:
	// * +10D
	// * the number of times dimension door was cast this day
	INT8	dimDoorCastCount; // +10D
	// * +10E
	// * the spell expertise of disguise that was cast
	INT32   disguisePower;  // +10E
	// * +112
	// * the spell expertise of fly that was cast
	INT32	flyPower;	// +112
	// * +116
	// * the spell expertise of waterwalk that was cast
	INT32	waterwalkPower; // +116
protected:
	INT8	_DMorale1; // +11A ???
	INT8	_DLuck;    // +11B
	INT8	isSleeping;	// +11C
	UINT8  _u7[12]; // 11D
	INT32	visionPower; // +129
public:
	// * +12D
	// * the 19 artifacts on a hero
	H3Artifact bodyArtifacts[19];
protected:
	// * +1C5
	// * ?
	UINT8	freeAddSlots;
public:
	// * +1C6
	// * whether an artifact slot is blocked or not
	UINT8	blockedArtifacts[14];
	// * +1D4
	// * the 64 artifacts in the backpack
	H3Artifact backpackArtifacts[64];
	// * +3D1
	// * the number of artifacts in the backpack
	UINT8	backpackCount;
	// * +3D5
	// * male or female
	INT32	gender;
	// * +3D9
	// * has custom bibliography?
	BOOL8	customBiblio;
	// * +3DA
	// * custom bibliography
	H3String bibliography;
	// * +3EA
	// * Spells the hero has learned
	INT8   learned_spell[70];
	// * +430
	// * Spells the hero has access to through artifacts
	INT8   available_spell[70];
	// * +476
	// * the four primary skills, attack, defense, spell power, knowledge
	INT8   primarySkill[4];
protected:
	// * +47A
	// * AI stuff
	UINT8  _u8[24];
public:
	// * calculates maximum daily movement on land
	INT32 MaxLandMovement() { return THISCALL_2(INT32, 0x4E4C00, this, 0); }
	// * calculates maximum daily movement on water
	INT32 MaxWaterMovement() { return THISCALL_2(INT32, 0x4E4C00, this, 1); }
	// * calculates maximum daily movement automatically
	INT32 CalcMaxMovement() { return THISCALL_1(INT32, 0x4E5000, this); }
	// * give an artifact by reference
	VOID GiveArtifact(H3Artifact *art, INT32 slot) { THISCALL_3(VOID, 0x4E2C70, this, art, slot); }
	// * learn secondary skill by given increase
	VOID LearnSecondarySkill(INT32 id, INT32 increase) { return THISCALL_3(VOID, 0x4E5240, this, id, increase); }
	// * returns effect (none, basic, ... expert) of a spell on a given terrain
	INT32 GetSpellExpertise(INT32 spell_id, INT32 special_terrain) { return THISCALL_3(INT32, 0x4E52F0, this, spell_id, special_terrain); }
	// * does this hero own creature of type...?
	BOOL8 HasCreatureType(INT32 type) { return army.HasCreatureType(type); }
	// * the bonus effect on a spell from specialty
	INT32 GetSpellSpecialtyEffect(INT32 spellID, INT32 creatureLevel, INT32 baseDamage) { return THISCALL_4(INT32, 0x4E6260, this, spellID, creatureLevel, baseDamage); }
	// * the bonus effect on a spell from sorcery
	INT32 GetSorceryEffect(INT32 spellID, INT32 baseDamage, H3CombatMonster *mon) { return THISCALL_4(INT32, 0x4E59D0, this, spellID, baseDamage, mon); }
	// * combined effects of a spell on a creature
	INT32 GetRealSpellDamage(INT32 baseDamage, H3CombatMonster *mon, INT32 spellID, H3Hero *enemy);
	// * checks under the hero for special terrain
	INT32 GetSpecialTerrain() { return THISCALL_1(INT32, 0x4E5130, this); }
	// * checks if hero has access to a spell
	BOOL HasSpell(INT32 spell) { return learned_spell[spell] | available_spell[spell]; }
	// * attempts to combine body artifacts into combo
	VOID BuildCombinationArtifact(INT32 combo_id) { THISCALL_3(VOID, 0x4DC1A0, this, combo_id, -1); }
	// * hero loses skill of id
	BOOL UnlearnSkill(INT32 id);
	// * forces recalculation of movement costs on the adventure map
	VOID RecalculateMovement();
	// * is it possible to move to where hero is standing?
	BOOL8 CanFlyOnTile() { return THISCALL_1(BOOL8, 0x4E5F50, this); }
	// * how much movement points it costs to move to given mixedPos
	INT32 GetMovementCost(INT32 orientation, UINT32 mixedPos) { return FASTCALL_4(INT32, 0x4B1620, this, orientation, mixedPos, movement); }
	// * the maximum number of level ups required to master remaining secondary skills
	INT32 SSkillsLeftToLearn();
	// * is the hero currently wearing artifact id ?
	BOOL WearsArtifact(INT id) { return THISCALL_2(BOOL, 0x4D9460, this, id); }
	// * get the value of primary 0 ~ 3 between 0/1 ~ 99 even if negative
	INT32 GetHeroPrimary(INT primary) { return THISCALL_2(INT32, 0x5BE240, this, primary); }
	// * used for diplomacy
	INT32 HasSimilarCreature(INT id) { return FASTCALL_2(INT32, 0x4A7230, this, id); }
	// * the class name of the current hero
	LPCSTR GetHeroClassName() { return THISCALL_1(LPCSTR, 0x4D91E0, this); }
};

// * how date is represented
struct H3Date
{
	UINT16 day;
	UINT16 week;
	UINT16 month;
	// * converts day, week, month into days from start, first day being 1
	UINT32 CurrentDay() const { return 28 * (month - 1) + 7 * (week - 1) + day - 1; }
};

// * how towns are represented in memory
struct H3Town
{
	// * +0
	// * 0~48
	UINT8	number;
	// * +1
	// * 0~7 who owns this town
	INT8	owner;
	// * +2
	// * was a structure built here this turn
	BOOL8	builtThisTurn; // +2
protected:
	h3unk	_f_03;
public:
	// * +4
	// * 0~8 Castle ~ Conflux
	UINT8	type;
	// * +5
	// * x coordinate
	UINT8	x;
	// * +6
	// * y coordinate
	UINT8	y;
	// * +7
	// * z coordinate
	UINT8	z;
	// * +8
	// * X destination of shipyard boat
	UINT8	pos2PlaceBoatX;
	// * +9
	// * Y destination of shipyard boat
	UINT8	pos2PlaceBoatY;
protected:
	h3unk	_f_0A[2];
public:
	// * +0C
	// * the ID of the hero inside the city's garrison
	INT32	garrisonHero;
	// * + 10
	// * the ID of the visiting hero in the bottom bar
	INT32	visitingHero;
protected:
	// * +14
	INT8	mageLevel;
	h3unk	_f_15;
public:
	// * +16
	// * number of recruitable non-upgraded then upgraded creatures
	INT16	recruits[2][7];
protected:
	h3unk	_f_32;
public:
	// * +33
	// * if mana vortex was not used this week
	BOOL8	manaVortextUnused;
protected:
	h3unk	_f_34;
	h3unk	_f_5a[3];
	h3unk	_f_38[8];
	h3unk	_f_40[2][2];
public:
	// * +44
	// * which spells are available in mage guild
	INT32	spells[5][6];
protected:
	// * +BC
	INT8	magicGuild[5];
	h3unk	_f_C1[3];
public:
	// * +C4
	// * the town's name, can be lenghtened
	H3String name;
protected:
	h3unk	_f_D4[12];
public:
	// * +E0
	// * the creatures in the town's garrison not belonging to a hero
	H3Army	Guards;
protected:
	// * +118
	// * for unused combat creatures?
	H3Army	Guards0;
public:
	// * +150
	H3Bitfield built[2];
	// * +158
	H3Bitfield bonus[2];
	// * +160
	H3Bitfield bMask[2];

	BOOL IsBuildingBuilt(INT32 id) { return THISCALL_3(BOOL, 0x4305A0, this, id, 1); }
	BOOL CanBuildStructure(INT32 id) { return THISCALL_3(BOOL, 0x4305A0, this, id, 0); }
	LPCSTR GetTownTypeName() { return THISCALL_1(LPCSTR, 0x5C1850, this); }

	enum eTown
	{
		CASTLE,
		RAMPART,
		TOWER,
		INFERNO,
		NECROPOLIS,
		DUNGEON,
		STRONGHOLD,
		FORTRESS,
		CONFLUX
	};

	enum eBuildings // from ERM help
	{
		B_MAGE_GUILD1,
		B_MAGE_GUILD2,
		B_MAGE_GUILD3,
		B_MAGE_GUILD4,
		B_MAGE_GUILD5,
		B_TAVERN,
		B_WHARF,
		B_FORT,
		B_CITADEL,
		B_CASTLE,
		B_VILAGE_HALL,
		B_TOWN_HALL,
		B_CITY_HALL,
		B_CAPITOL,
		B_MARKET,
		B_RESOURCE_SILO,
		B_BLACKSMITH,
		B_SPEC17,
		B_HORDE1,
		B_HORDE1U,
		B_WHARF2,
		B_SPEC21,
		B_SPEC22,
		B_SPEC23,
		B_HORDE2,
		B_HORDE2U,
		B_GRAIL,
		B_DECOR27,
		B_DECOR28,
		B_DECOR29,
		B_DWELL1,
		B_DWELL2,
		B_DWELL3,
		B_DWELL4,
		B_DWELL5,
		B_DWELL6,
		B_DWELL7,
		B_DWELL1U,
		B_DWELL2U,
		B_DWELL3U,
		B_DWELL4U,
		B_DWELL5U,
		B_DWELL6U,
		B_DWELL7U,

		/* CASTLE */
		B_LIGHTHOUSE = 17,
		B_STABLES = 21,
		B_BROTHERHOOD_OF_THE_SWORD = 22,

		/* RAMPART */
		B_MYSTIC_POND = 17,
		B_FOUNTAIN_OF_FORTUNE = 21,
		B_DWARVEN_TREASURY = 22,

		/* TOWER */
		B_ARTIFACT_MERCHANT = 17, // same for Dungeon and Conflux
		B_LOOKOUT_TOWER = 21,
		B_LIBRARY = 22,
		B_WALL_OF_KNOWLEDGE = 23,

		/* INFERNO */
		B_BRIMSTONECLOUDS = 21,
		B_CASTLE_GATE = 22,
		B_ORDER_OF_FIRE = 23,

		/* NECROPOLIS */
		B_VEIL_OF_DARKNESS = 17,
		B_NECROMANCY_AMPLIFIER = 21,
		B_SKELETON_TRANSFORMER = 22,

		/*  DUNGEON */
		B_MANA_VORTEX = 21,
		B_PORTAL_OF_SUMMONING = 22,
		B_BATTLE_ACADEMY = 23,

		/* STRONGHOLD */
		B_ESCAPE_TUNNEL = 17,
		B_FREELANCERS_GUILD = 21,
		B_BALLISTA_YARD = 22,
		B_HALL_OF_VALHALLA = 23,

		/* FORTRESS */
		B_CAGE_OF_WARLORDS = 17,
		B_GLYPHS_OF_FEAR = 21,
		B_BLOOD_OBELISK = 22,

		/* CONFLUX */
		B_MAGIC_UNIVERSITY = 21
	};
};

// * data about each of the 8 players on the map
struct H3Player // size 0x168
{
	// * +0
	// * 0~7 RED~PINK
	INT8 ownerID;
	// * +1
	// * if player has at least 1 hero
	BOOL8 hasHeroes;
protected:
	h3unk _f_02[2];
public:
	// * +4
	// * the id of the active hero
	// * -1 if none
	INT32  currentHero;
	// * +8
	// * IDs of the 8 possible heroes on adventure map
	INT32  heroIDs[8];
	// * +28
	// * ID of the hero in the left slot of tavern
	INT32  tavernHeroL;
	// * +2C
	// * ID of the hero in the right slot of tavern
	INT32  tavernHeroR;
protected:
	h3unk _f_30[4];
public:
	// * +34
	// * adventurer, explorer, builder
	INT32 AI_type;
	// * +38
	// * 0~47 visited obelisks
	INT8 visitedObelisks;
protected:
	h3unk _f_39[4];
public:
	// * +3D
	// * the number of days left to live without a town
	// * -1 if at least 1 town is owned
	INT8  daysLeft;
	// * +3E
	// * the number of towns owned
	INT8  townsCount;
	// * +3F
	// * ID of the selected town
	INT8  currentTown;
	// * +40
	// * IDs of the towns owned by player
	CHAR  towns[48];
protected:
	h3unk _f_70[4];
	// * +74
	INT32 topHeroIndex;
	h3unk _f_78[36];
public:
	// * +9C
	// * the current resources owned by player
	H3Resources playerResources;
protected:
	// * +B8
	INT32 magical_gardens; // ??? from WoG source https://github.com/GrayFace/wog/blob/master/T1/h3struct.txt#L100
	// * +BC
	INT32 magic_spring;
	// * +C0
	UINT8 unknown4[12];
	// * +CC
	// * name of player, uncertain length
	CHAR player_name[21];
public:
	// * +E1
	// * 1 human, 0 computer
	BOOL8 is_human;
	// * +E2
	// * 1 human, 0 computer
	BOOL8 is_human2;
protected:
	h3unk _f_E3[3];
	// * +E6
	BOOL8 human;
	h3unk _f_E7;
	// * +E8
	BOOL hasComboArtifacts;
	h3unk _f_EC[28];
public:
	// * +108
	// * the amount of resources gained daily
	H3Resources income;
protected:
	h3unk _f_124[4];
	// * +128
	// * doubles used by AI
	DOUBLE resourceImportance[7];
	h3unk _f_160[8];
public:
	// * returns structure of active hero if any
	H3Hero *GetActiveHero();
};

/*
 * Modeled after H3M_OA_ENTRY in h3m format
 * https://github.com/potmdehex/homm3tools/blob/master/h3m/h3mlib/h3m_structures/object_attributes/h3m_oa.h#L20
 * see also https://github.com/potmdehex/homm3tools/blob/master/h3m/h3mlib/h3m_structures/object_attributes/h3m_oa_body.h#L13
 * and https://github.com/ethernidee/era-editor/blob/master/Patch/Common.pas#L39 from mapeditor format
 */
struct H3ObjectAttributes
{
	// * +0
	// * the name of the DEF
	H3String defName;
	// * +10
	// * the width of object, read from LoD @ 0x503ED5
	UINT8 width;
	// * +11
	// * the height of object, read from LoD @ 0x503EE2
	UINT8 height;
protected:
	// * probably alignment, not reset @ 0x4D3CE1 and on
	h3unk _f_12[2];
public:
	// * +14
	// * a 8x6 bitfield of the object's shadow
	H3Bitfield maskShadow[2];

	// * +1C
	// * a 8x6 bitfield of the object's presence
	H3Bitfield maskObject[2];

	// * +24
	// * a 8x6 bitfield of the object's passability
	H3Bitfield maskEmpty[2];

	// * +2C
	// * a 8x6 bitfield of the object's yellow tiles
	H3Bitfield maskEnter[2];

	// * +34
	// * a bitfield of vaild terrains for this object
	H3Bitfield maskTerrain;
	// * +38
	// * the type of object, 0 ~ 232
	INT32 type;
	// * +3C
	// * the subtype of object, depends on type
	INT32 subtype;
	// * +40
	// * is the object flat on the adventure map? e.g. cursed ground
	BOOL8 flat;
protected:
	// * alignment
	h3unk _f_41;
	// * referenced a few places, e.g. 0x50663A
	h3unk _f_42[2];
};

// * from WoG source
struct H3MagicAnimation
{
	LPCSTR defName;
	LPCSTR name;
	INT32 type;
};

// * the counterpart to H3ObjectAttributes
struct H3ObjectDetails
{
	// * +0
	// * reference to H3ObjectAttributes
	UINT32 setup;
	// * +4
	// * x position on map
	UINT8 x;
	// * +5
	// * y position on map
	UINT8 y;
	// * +6
	// * z position on map
	UINT8 z;
protected:
	h3unk _f_7;
public:
	// * +8
	// * reference to object's DEF for drawing purposes
	UINT16 num;
protected:
	h3unk _f_A[2];
};

// * data for wandering monsters on adventure map
struct MapMonster
{
	unsigned  count : 12; // +00 max 4095
	unsigned  aggression : 5; // for diplomacy
	unsigned  noRun : 1; // +17
	unsigned  noGrowth : 1; // +18
	unsigned  setupIndex : 8; // +19 up to 255 individual messages/prizes
	unsigned  _u1 : 4; // +27 to my knowledge, not used anywere. Could expand the number of setups to 4095?
	unsigned  hasSetup : 1; // +31
};

// * data for artifact on the map
struct MapArtifact
{
	/*
	 * RoE-style artifact pickup requirements
	 * 0 - free selection
	 * 1 - for 2000 gold
	 * 2 - wisdom is required
	 * 3 - leadership is required
	 * 4 - 2500 gold and 3 wood
	 * 5 - 3000 gold and 5 wood
	 * 6 - fight is triggered
	 */
	unsigned type : 4;
	unsigned _u1 : 15;
	unsigned id : 12; // reference to its structure, max 4095
	unsigned hasSetup : 1;
};

// * data for scholar on adventure map
struct MapScholar
{
	unsigned  type : 3; // 0 Primary, 1 Secondary, 2 Spell
	unsigned  pSkill : 3;
	unsigned  sSkill : 7;
	unsigned  spell : 11;
	unsigned _u1 : 8;
};

// * data for event on adventure map
struct MapEvent
{
	unsigned  id : 10; // Up to 1024
	unsigned  enabled : 8; // which players can activate it?
	unsigned  aiEnabled : 1; // can AI activate it?
	unsigned  oneVisit : 1; // Cancel after 1 visit?
	unsigned _u1 : 12; // ?unsued?
};

// * data for treasure chest on adventure map
struct MapTreasureChest
{
	unsigned artifactID : 10;
	unsigned hasArtifact : 1;
	unsigned bonus : 4;
	unsigned _u1 : 17;
};

// * data for resource on adventure map
struct MapResource
{
	unsigned value : 19;  // up to 524,287
	unsigned setupIndex : 12;  // for guardians and message
	unsigned hasSetup : 1;  // TRUE/FALSE
};

// * data for sea chest on adventure map
struct MapSeaChest
{
	unsigned level : 2;
	unsigned _u1 : 1;
	unsigned artifactID : 10;
	unsigned _u2 : 19;
};

// * data for warrior's tomb on adventure map
struct MapWarriorsTomb
{
	unsigned  hasArt : 1;  // TRUE/FALSE
	unsigned _u1 : 4;
	unsigned  visited : 8; // which players have come by
	unsigned  artifactID : 10;
	unsigned _u2 : 9;
};

// * data for tree of knowledge on adventure map
struct MapTreeOfKnowledge
{
	unsigned  id : 5;  // up to 32
	unsigned  visited : 8;  // for players
	unsigned  type : 2;  // 0,1,2 ~ cost
	unsigned _u1 : 17;
};

// * data for campfire on adventure map
struct MapCampfire
{
	unsigned  resType : 4; // crystal, ...
	unsigned  resValue : 28; // resource = ResVal, gold = 100 * ResVal
};

// * data for lean to on adventure map
struct MapLeanTo
{
	unsigned  id : 5;
	unsigned _u1 : 1;
	unsigned  resValue : 4;
	unsigned  resType : 4;
	unsigned _u2 : 18;
};

// * data for witch's hut on adventure map
struct MapWitchHut
{
	unsigned _u1 : 5;
	signed    visited : 8;
	signed    sSkill : 7; // id
	unsigned _u2 : 12;
};

// * data for learning stone on adventure map
struct MapLearningStone
{
	int id;
};

// * data for wagon on adventure map
struct MapWagon
{
	unsigned  resValue : 5;
	signed    visited : 8;
	unsigned  hasBonus : 1;
	unsigned  hasArtifact : 1;
	unsigned  artifactID : 10;
	unsigned  resType : 4;
	unsigned _u3 : 3;
};

// * data for corpse on adventure map
struct MapCorpse
{
	unsigned  id : 5;
	unsigned _u1 : 1;
	unsigned  artifactID : 10;
	unsigned  hasArtifact : 1;
	unsigned _u2 : 15;
};

// * data for magic spring on adventure map
struct MapMagicSpring
{
	unsigned  id : 5;
	unsigned _u1 : 1;
	unsigned  used : 1;
	unsigned _u2 : 25;
};

// * data for water mill on adventure map
struct MapWaterMill
{
	unsigned  bonus : 5; // gold = 500 * Bonus
	unsigned  visited : 8;
	unsigned _u1 : 19;
};

// * data for creature banks on adventure map
struct MapCreatureBank
{
	unsigned _u1 : 5;
	unsigned  visited : 8;
	unsigned  id : 12;
	unsigned  taken : 1;
	unsigned _u2 : 6;
};

// * data for pyramid on adventure map
struct MapPyramid
{
	unsigned  taken : 1;
	unsigned  id : 4;
	unsigned  visited : 8;
	unsigned  spell : 8;
	unsigned _u1 : 11;
};

// * data for swan pond on adventure map
struct MapSwanPond
{
	unsigned  id : 5;
	unsigned  visited : 8; //
	unsigned  bonusLuck : 4; // 1...3
	unsigned _u3 : 15;
};

// * data for monoliths on adventure map
struct MapMonolith
{
	// * only really used for 2-way monoliths, such that entrance != exit
	int  index;
};

// * data for mystic garden on adventure map
struct MapMysticGarden
{
	unsigned  id : 5;
	unsigned _u1 : 1;
	unsigned  resType : 4;
	unsigned  hasRes : 1;
	unsigned _u2 : 21;
};

// * data for windmill on adventure map
struct MapWindmill
{
	unsigned  resType : 4;
	unsigned _u1 : 9;
	unsigned  resValue : 4;
	unsigned _u2 : 15;
};

// * data for mine/lighthouse on adventure map
struct MapMine
{
	int   index;
};

// * data for shipyard on adventure map
struct MapShipyard
{
	unsigned  owner : 8;
	unsigned  x : 8;
	unsigned  y : 8;
	unsigned _u3 : 8;
};

// * data for magic shrine on adventure map
struct MapMagicShrine
{
	unsigned _u1 : 13;
	unsigned  spell : 10;
	unsigned _u2 : 9;
};

// * data for university on adventure map
struct MapUniversity
{
	unsigned _u1 : 5;
	unsigned  visited : 8;
	unsigned  id : 12;
	unsigned _u2 : 7;
};

// * data of objects to be drawn at a given map tile
struct H3ObjectDraw
{
	// * +0
	// index of H3ObjectAttributes
	UINT16 sprite;
	// * +2
	// * reference to which square of the DEF (bottom right = 0, then left to right, down to top. Row 1: 0x10 and so on)
	UINT8 tileID;
	// * +3
	// * 0~6 drawing layer, 6 being top and 0 bottom
	UINT8 layer;


	H3ObjectDraw(UINT16 sprite, UINT8 tile_id, UINT8 layer)
		: sprite(sprite),
		  tileID(tile_id),
		  layer(layer)
	{
	}
};

// * data on a given tile on the adventure map
struct H3MapItem
{
	// * +0
	// * see Map... structures
	UINT32 setup;
	// * +4
	// *dirt, grass, snow ...
	INT8 land;
	// * +5
	// * the id of land DEF sprite
	INT8 landSprite;
	// * +6
	// * none, clear, icy, ...
	INT8 river;
	// * +7
	// * +the id of river DEF sprite
	INT8 riverSprite;
	// * +8
	// * none, dirt, gravel, ...
	INT8 road;
	// * +the id of road DEF sprite
	INT8 roadSprite;
protected:
	h3unk _f_0A[2];
public:
	// * +C
	// * mirror effect of DEF
	// * tileH      0x01 -	tileV	0x02
	// * riverH		0x04 -	riverH	0x08
	// * roadH		0x10 -	roadV	0x20
	// * can dig	0x40
	// * animated	0x80 (river, water or lava terrain)
	UINT8 mirror;
	// * +D
	// * 0x01 cannot access
	// * 0x02 water edge see 0x4FEA32
	// * 0x10 entrance (yellow) tile
	UINT8 access;
	// * +E
	// * a vector of DEFs to draw on this tile
	H3Vector<H3ObjectDraw> objectDrawing;
	// * +1E
	// * the object type on this tile
	INT16 objectType;
protected:
	h3unk _f_20[2];
public:
	// * +22
	// * the subtype of object on this tile
	INT16 objectSubtype;
	// * +24
	// * ???
	UINT16 drawNum;

	// * Get university on this tile
	H3University *GetUniversity()	{ return STDCALL_1(H3University*, 0x405DA0, this); }
	// * get real entrance (if any) of object on this tile
	H3MapItem* GetEntrance()		{ return THISCALL_1(H3MapItem*, 0x4FD0F0, this); }
	BOOL IsEntrance()				{ return access & 0x10; }
	BOOL IsBlocked()				{ return access & 1; }
	BOOL CanDig()					{ return mirror & 0x40; }

	// * casts setup to relevant map item data
	MapMonster*			CastMonster()		{ return (MapMonster*)this; }
	// * casts setup to relevant map item data
	MapScholar*			CastScholar()		{ return (MapScholar*)this; }
	// * casts setup to relevant map item data
	MapEvent*			CastEvent()			{ return (MapEvent*)this; }
	// * casts setup to relevant map item data
	MapTreasureChest*	CastTreasureChest() { return (MapTreasureChest*)this; }
	// * casts setup to relevant map item data
	MapWarriorsTomb*	CastWarriorsTomb()	{ return (MapWarriorsTomb*)this; }
	// * casts setup to relevant map item data
	MapTreeOfKnowledge*	CastTreeKnowledge() { return (MapTreeOfKnowledge*)this; }
	// * casts setup to relevant map item data
	MapCampfire*		CastCampfire()		{ return (MapCampfire*)this; }
	// * casts setup to relevant map item data
	MapLeanTo*			CastLeanTo()		{ return (MapLeanTo*)this; }
	// * casts setup to relevant map item data
	MapWitchHut*		CastWitchHut()		{ return (MapWitchHut*)this; }
	// * casts setup to relevant map item data
	MapLearningStone*	CastLearningStone() { return (MapLearningStone*)this; }
	// * casts setup to relevant map item data
	MapWagon*			CastWagon()			{ return (MapWagon*)this; }
	// * casts setup to relevant map item data
	MapCorpse*			CastCorpse()		{ return (MapCorpse*)this; }
	// * casts setup to relevant map item data
	MapMagicSpring*		CastMagicSpring()	{ return (MapMagicSpring*)this; }
	// * casts setup to relevant map item data
	MapWaterMill*		CastWatermill()		{ return (MapWaterMill*)this; }
	// * casts setup to relevant map item data
	MapCreatureBank*	CastCreatureBank()	{ return (MapCreatureBank*)this; }
	// * casts setup to relevant map item data
	MapPyramid*			CastPyramid()		{ return (MapPyramid*)this; }
	// * casts setup to relevant map item data
	MapSwanPond*		CastSwanPond()		{ return (MapSwanPond*)this; }
	// * casts setup to relevant map item data
	MapMonolith*		CastMonolith()		{ return (MapMonolith*)this; }
	// * casts setup to relevant map item data
	MapMysticGarden*	CastMysticGarden()	{ return (MapMysticGarden*)this; }
	// * casts setup to relevant map item data
	MapWindmill*		CastWindmill()		{ return (MapWindmill*)this; }
	// * casts setup to relevant map item data
	MapMine*			CastMine()			{ return (MapMine*)this; }
	// * casts setup to relevant map item data
	MapShipyard*		CastShipyard()		{ return (MapShipyard*)this; }
	// * casts setup to relevant map item data
	MapMagicShrine*		CastMagicShrine()	{ return (MapMagicShrine*)this; }
	// * casts setup to relevant map item data
	MapUniversity*		CastUniversity()	{ return (MapUniversity*)this; }
	// * casts setup to relevant map item data
	MapResource*		CastResource()		{ return (MapResource*)this; }
	// * casts setup to relevant map item data
	MapSeaChest*		CastSeaChest()		{ return (MapSeaChest*)this; }
	MapArtifact*		CastArtifact()		{ return (MapArtifact*)this; }
};

// * information about artifacts
// * enum for body artifact position
// * enum for artifact type ~ level
struct H3ArtifactSetup
{
	// * +0
	LPCSTR name;
	// * +4
	INT32 cost;
	// * +8
	INT32 position;
	// * +C
	INT32 type;
	// * +10
	LPCSTR description;
	// * +14
	INT32 comboID;
	// * +18
	BOOL partOfCombo;
	// * +1C
	BOOL8 disabled;
	// * +1D
	INT8 newSpell;
	h3unk _f_1E[2];

	enum ArtifactPosition
	{
		ArtPos_HEAD,
		ArtPos_SHOULDERS,
		ArtPos_NECK,
		ArtPos_RIGHT_HAND,
		ArtPos_LEFT_HAND,
		ArtPos_TORSO,
		ArtPos_RIGHT_RING,
		ArtPos_LEFT_RING,
		ArtPos_FEET,
		ArtPos_MISC_1,
		ArtPos_MISC_2,
		ArtPos_MISC_3,
		ArtPos_MISC_4,
		ArtPos_WAR_MACHINE_1,
		ArtPos_WAR_MACHINE_2,
		ArtPos_WAR_MACHINE_3, // First Aid Tent
		ArtPos_WAR_MACHINE_4,
		ArtPos_CATAPULT,
		ArtPos_SPELL_BOOK,
		ArtPos_MISC_5,
	};

	enum ArtifactType
	{
		ART_SPECIAL = 1,
		ART_TREASURE = 2,
		ART_MINOR = 4,
		ART_MAJOR = 8,
		ART_RELIC = 16,
		ART_ALL = 30 // never special!
	};
};

// * how combo artifacts are stored in memory
struct H3ComboArtifactSetup
{
	INT32 index;
	H3Bitfield artifacts[5];
};

// * data for creature banks
struct H3CreatureBank
{
	// * +0
	// * creatures guarding this bank
	H3Army guardians;
	// * +38
	// * resource rewards for defeating this bank
	H3Resources resources;
	// * +54
	// * the type of creature rewarded for defeating this bank
	INT32 creatureRewardType;
	// * +58
	// * the number of creatures rewarded for defeating this bank
	INT8 creatureRewardCount;
protected:
	h3unk _f_59[3];
public:
	// * +5C
	// *a list of artifact IDs gained for defeating this bank
	H3Vector<INT32> artifacts;

	BOOL HasUpgradedStack() { return guardians.type[0] != guardians.type[2]; }
	VOID SetupBank(int type, int level);
	VOID UpgradeStack(BOOL upg);
};

// * CRBanks.txt converted in memory, single bank state
struct H3CreatureBankState
{
	// * +0
	// * creatures guarding this bank
	H3Army guardians;
	// * +38
	// * resource rewards for defeating this bank
	H3Resources resources;
	// * +54
	// * the type of creature rewarded for defeating this bank
	INT32 creatureRewardType;
	// * +58
	// * the number of creatures rewarded for defeating this bank
	INT8 creatureRewardCount;
	// * +59
	// * the odds (out of 100) for this size to be spawned
	INT8 chance;
	// * +5A
	// * the odds (out of 100) to have an upgraded stack
	INT8 upgrade;
	// * +5B
	// * the amount of treasure, minor, major, relic artifacts
	INT8 artifactTypeCounts[4];
protected:
	h3unk _f_5F;
};

// * CRBanks.txt converted in memory, overall bank state
struct H3CreatureBankSetup
{
	H3String name;
	H3CreatureBankState states[4];

	enum eCrBank
	{
		CYCLOPS_STOCPILE,
		DWARVEN_TREASURY,
		GRIFFIN_CONSERVATORY,
		IMP_CACHE,
		MEDUA_STORES,
		NAGA_BANK,
		DRAGON_FLY_HIVE,
		SHIPWRECK,
		DERELICT_SHIP,
		CRYPT,
		DRAGON_UTOPIA
	};
};

// * town wall elements
struct H3ValidCatapultTargets
{
	INT32 fort_element_id;
	h3unk f_04[8];

	enum FORT_ELEMENTS {
		FE_DRAWBRIDGE,	// 0
		FE_DRAWBRIDGE_ROPE,
		FE_MOAT,
		FE_MOAT_LIP,
		FE_BACK_WALL,
		FE_UPPER_TOWER, // 5 ~ valid catapult target ~0
		FE_UPPER_WALL, // 6 ~ valid catapult target ~1
		FE_UPPER_BUTTRESS,
		FE_MID_UPPER_WALL, // 8 ~ valid catapult target ~2
		FE_GATE, // 9 ~ valid catapult target ~3
		FE_MID_LOWER_WALL, // 10 ~ valid catapult target ~4
		FE_LOWER_BUTTRESS,
		FE_LOWER_WALL, // 12 ~ valid catapult target ~5
		FE_LOWER_TOWER, // 13 ~ valid catapult target ~6
		FE_KEEP, // 14 ~ valid catapult target ~7
		FE_KEEP_CVR,
		FE_LOWER_TWR_CVR,
		FE_UPPER_TWR_CVR
	};
};

// * town wall data
struct H3WallSection
{
	// * +0
	INT16 x;
	// * +2
	INT16 y;
	// * +4
	INT32 hex_id;
	// * +8
	LPCSTR names[5];
	INT32 name; // from walls.txt
	INT16 hp;	// from walls.txt
	h3unk _f_22[2];
};

// * information about H3 spells
struct H3Spell
{
	// * +0
	// * -1 enemy
	// * 0 area
	// * 1 friendly
	INT32 type;
	// * +4
	// * the soundname to use
	LPCSTR soundName;
protected:
	// * +8
	UINT32 animationRelated;
public:
	// * +C
	// * bitfield of spell data
	struct SpellFlags
	{
		// * flag 1
		unsigned battlefield_spell : 1;
		// * flag 2
		unsigned map_spell : 1;
		// * flag 4
		unsigned time_scale : 1;
		// * flag 8
		unsigned creature_spell : 1;
		// * flag 10
		unsigned single_target : 1;
		// * flag 20
		unsigned single_shooting_stack : 1;
		// * flag 40
		unsigned expert_mass_version : 1;
		// * flag 80
		unsigned target_anywhere : 1;
		// * flag 100
		unsigned remove_obstacle : 1;
		// * flag 200
		// * All damage spells
		unsigned damage_spell : 1;
		// * flag 400
		unsigned mind_spell : 1;
		// * flag 800
		unsigned friendly_mass : 1;
		// * flag 1000
		unsigned cannot_target_siege : 1;
		// * flag 2000
		unsigned spell_from_artifact : 1;
		// * flag 4000
		// * Air/Fire Shield, Protections From, Anti-Magic, Magic Mirror, Stone Skin, Counterstrike
		unsigned defensive : 1;
		// * flag 8000
		// * All damage spells except INFERNO and CHAING LIGHTNING
		unsigned AI_damage_spells : 1;
		// * flag 10000
		// * Inferno and Chaing Lightning
		unsigned AI_area_effect : 1;
		// * flag 20000
		// * Death Ripple, Destroy Undead and Armageddon
		unsigned AI_mass_damage_spells : 1;
		// * flag 40000
		// * Shield, Air Shield, ... Berserk, Teleport, Clone
		// * NO SUMMON SPELLS
		unsigned AI_non_damage_spells : 1;
		// * flag 80000
		// * Resurrection, Animate Dead
		// * Hypnotize
		// * 4 Summon Spells
		unsigned AI_creatures : 1;
		// * flag 100000
		// * Summon Boat, Fly, WW, DD, TP
		// * Earthquake, Titan's Lightning Bolt (not sure why these are here???)
		unsigned AI_adventure_map : 1;
		// * flag 200000+
		// * there are no spells with these flags
		unsigned _unused : 11;
	}flags;
	// * +10
	// * full name
	LPCSTR name;
	// * +14
	// * short name
	LPCSTR shortName;
	// * +18
	// * 0~5
	INT32 level;
	enum eSchool : INT32
	{
		AIR = 1,
		FIRE = 2,
		WATER = 4,
		EARTH = 8
	};
	// * +1C
	eSchool school;
	// * +20
	// * mana cost at each spell expertise
	INT32 mana_cost[4];
	// * +30
	// * value multiplied by spell power
	INT32 sp_effect;
	// * +34
	// * base value of spell for calculations
	INT32 base_value[4];
	// * +44
	// * change for each class?
	INT32 chance_to_get[9];
	// * +68
	UINT32 ai_value[4];
	// * 78
	// * description of spell based on secondary skill level
	LPCSTR description[4];

	INT32 GetBaseEffect(INT32 level, INT32 spellPower) { return base_value[level] + spellPower * sp_effect; }

	enum eSpells
	{
		SUMMON_BOAT,
		SCUTTLE_BOAT,
		VISIONS,
		VIEW_EARTH,
		DISGUISE,
		VIEW_AIR,
		FLY,
		WATER_WALK,
		DIMENSION_DOOR,
		TOWN_PORTAL,
		QUICK_SAND,
		LAND_MINE,
		FORCE_FIELD,
		FIRE_WALL,
		EARTHQUAKE,
		MAGIC_ARROW,
		ICE_BOLT,
		LIGHTNING_BOLT,
		IMPLOSION,
		CHAIN_LIGHTNING,
		FROST_RING,
		FIREBALL,
		INFERNO,
		METEOR_SHOWER,
		DEATH_RIPPLE,
		DESTROY_UNDEAD,
		ARMAGEDDON,
		SHIELD,
		AIR_SHIELD,
		FIRE_SHIELD,
		PROTECTION_FROM_AIR,
		PROTECTION_FROM_FIRE,
		PROTECTION_FROM_WATER,
		PROTECTION_FROM_EARTH,
		ANTI_MAGIC,
		DISPEL,
		MAGIC_MIRROR,
		CURE,
		RESURRECTION,
		ANIMATE_DEAD,
		SACRIFICE,
		BLESS,
		CURSE,
		BLOODLUST,
		PRECISION,
		WEAKNESS,
		STONE_SKIN,
		DISRUPTING_RAY,
		PRAYER,
		MIRTH,
		SORROW,
		FORTUNE,
		MISFORTUNE,
		HASTE,
		SLOW,
		SLAYER,
		FRENZY,
		TITANS_LIGHTNING_BOLT,
		COUNTERSTRIKE,
		BERSERK,
		HYPNOTIZE,
		FORGETFULNESS,
		BLIND,
		TELEPORT,
		REMOVE_OBSTACLE,
		CLONE,
		FIRE_ELEMENTAL,
		EARTH_ELEMENTAL,
		WATER_ELEMENTAL,
		AIR_ELEMENTAL,
		/* These abilities are not available to heroes */
		STONE,
		POISON,
		BIND,
		DISEASE,
		PARALYZE,
		AGING,
		DEATH_CLOUD,
		THUNDERBOLT,
		DRAGONFLY_DISPEL,
		DEATH_STARE,
		ACID_BREATH
	};
};

// * information about combat obstacles
struct H3ObstacleInfo // size 20
{
	// * +0
	UINT16 LandTypes;
	// * +2
	UINT16 SpecialGroundTypes;
	// * +4
	INT8 HeightInCells;
	// * +5
	INT8 WidthInCells;
	// * +6
	INT8 BlockedCount;
	// * +7
	h3unk _f_7;
	// * +8
	INT8 RelativeCells[8];
	// * +10
	LPCSTR defName;
};

// * information about obstacle in combat manager
struct H3Obstacle // size 24
{
	// * +0
	H3LoadedDEF *def;
	// * +4
	H3ObstacleInfo *info;
	// * +8
	UINT8 AnchorHex;
protected:
	h3unk f_09;
	h3unk f_0A;
	h3unk f_0B[13];
};

// * bitfield flags for creatures
struct H3CreatureFlags
{
	unsigned DOUBLE_WIDE : 1;			// 1
	unsigned FLYER : 1;					// 2
	unsigned SHOOTER : 1;				// 4
	unsigned EXTENDED : 1;				// 8 ~ aka dragon breath
	unsigned ALIVE : 1;					// 10
	unsigned DESTROYWALLS : 1;			// 20
	unsigned SIEGEWEAPON : 1;			// 40
	unsigned KING1 : 1;					// 80 ~ all creatures of 7th level and neutral dragons that do not belong to the KING2 or KING3
	unsigned KING2 : 1;					// 100
	unsigned KING3 : 1;					// 200
	unsigned MINDIMMUNITY : 1;			// 400
	unsigned NOOBSTACLEPENALTY : 1;		// 800
	unsigned NOMELEEPENALTY : 1;		// 1000
	unsigned unk2000 : 1;				// 2000
	unsigned FIREIMMUNITY : 1;			// 4000
	unsigned DOUBLEATTACK : 1;			// 8000
	unsigned NORETALIATION : 1;			// 10000
	unsigned NOMORALE : 1;				// 20000
	unsigned UNDEAD : 1;				// 40000
	unsigned ATTACKALLAROUND : 1;		// 80000
	unsigned MAGOG : 1;					// 100000
	unsigned CANNOTMOVE : 1;			// 200000 ~21
	unsigned SUMMON : 1;				// 400000
	unsigned CLONE : 1;					// 800000
	unsigned MORALE : 1;				// 1000000
	unsigned WAITING : 1;				// 2000000 ~25
	unsigned DONE : 1;					// 4000000
	unsigned DEFENDING : 1;				// 8000000
	unsigned SACRIFICED : 1;			// 10000000
	unsigned NOCOLORING : 1;			// 20000000
	unsigned GRAY : 1;					// 40000000
	unsigned DRAGON : 1;				// 80000000
};

// * hardcoded creature information in heroes3.exe
struct H3CreatureInformation
{
	//  * +0
	// -1 means neutral
	INT32 town;
	//  * +4
	// 0 ~ 6
	INT32 level;
	//  * +8
	LPCSTR shortName;
	//  * +C
	LPCSTR defName;
	//  * +10
	H3CreatureFlags flags;
	//  * +14
	LPCSTR nameSingular;
	//  * +18
	LPCSTR namePlural;
	//  * +1C
	LPCSTR description;
	//  * +20
	H3Resources cost;
	//  * +3C
	INT32  fightValue;
	// * +40
	INT32  aiValue;
	//  * +44
	INT32  grow;
	// * +48
	INT32  hGrow;
	// * +4C
	INT32  hitPoints;
	// * +50
	INT32  speed;
	// * +54
	INT32  attack;
	// * +58
	INT32  defence;
	// * +5C
	INT32  damageLow;
	// * +60
	INT32  damageHigh;
	// * +64
	INT32  numberShots;
	// * +68
	INT32  spellCharges;
	// * +6C
	INT32  advMapLow;
	// * +70
	INT32  advMapHigh;

	LPCSTR GetCreatureName(INT32 count) { return count > 1 ? namePlural : nameSingular; }
	VOID UpgradeCost(H3Resources *res, H3CreatureInformation *upg, INT32 count);
};

// * a substructure of H3CombatMonster related to spells
struct H3CombatMonsterSpellsData
{
	INT32 bless_damage; // 0x458
	INT32 curse_damage; // 0x45C
	INT32 anti_magic; // 0x460
	INT32 bloodlust_effect; // 0x464
	INT32 precision_effect; // 0x468
	INT32 weakness_effect; // 0x46C
	INT32 stone_skin_effect; // 0x470
	INT32 unknown13; // 0x474
	INT32 prayer_effect; // 0x478
	INT32 mirth_effect; // 0x47C
	INT32 sorrow_effect; // 0x480
	INT32 fortune_effect; // 0x484
	INT32 misfortune_effect; // 0x488
	INT32 slayer_type; // 0x48C - called KING_1/2/3
	INT32 unknown14; // 0x490 - Max traversed cells before hitting?
	INT32 counterstrike_effect; // 0x494
	float frenzyMultiplier; // 0x498
	INT32 blind_effect; // 0x49C - for calculating damage retaliation damage?
	float fire_shield_effect; // 0x4A0
	INT32 unknown16; // 0x4A4
	float protection_air_effect; // 0x4A8 - in % as below
	float protection_fire_effect; // 0x4AC
	float protection_water_effect; // 0x4B0
	float protection_earth_effect; // 0x4B4
	INT32 shield_effect; // 0x4B8
	INT32 air_shield_effect; // 0x4BC
	INT8 blinded; // 0x4C0 - to reduce damage?
	INT8 paralyzed; // 0x4C1 - to reduce damage?
	INT8 unknown17[2]; // 0x4C2-0x4C3
	INT32 forgetfulness_level; // 0x4C4
	float slow_effect; // 0x4C8 - float
	INT32 haste_effect; // 0x4CC - value added/removed
	INT32 disease_attack_effect; // 0x4D0
	INT32 disease_defense_effect; // 0x4D4
	INT32 unknown18[3]; // 0x4D8-0x4E0
	INT32 magic_mirror_effect; // 0x4E4
	INT32 morale; // +4E8
	INT32 luck; // +4EC
	h3unk _f_4F0[56];
	INT32 Hypnotize_528;
	INT32 Hypnotize_52C;
	h3unk _f_530[24];
};

// * Cranim.txt
struct H3MonsterAnimation
{
	enum eMissiles
	{
		M_UPPER_RIGHT,
		M_RIGHT,
		M_LOWER_RIGHT
	};

	struct H3MissileOffets
	{
		INT16 offset_x;
		INT16 offset_y;
	}missiles[3];

	INT32 missile_frame_angles[12]; // from high to low (90 to -90)
	INT32 troop_count_location_offset;
	INT32 attack_climax_frame;
	INT32 time_between_fidgets;
	INT32 walk_animation_time;
	INT32 attack_animation_time;
	INT32 flight_animation_time;
};

// * monster information on battlefield
struct H3CombatMonster
{
protected:
	h3unk _f_000[52];
public:
	// * +34
	INT32 type;
	// * +38
	// * position on battlefield
	INT32 position;
	// * +3C
	INT32 animation;
	// * +40
	INT32 animationFrame;
	// * +44
	// * left or right
	INT32 secondHexOrientation;
protected:
	h3unk _f_048[4];
public:
	// * +4C
	// the number of creatures that are currently alive
	INT32 numberAlive;
	// * +50
	INT32 previousNumber;
protected:
	h3unk _f_054[4];
public:
	// * +58
	// * the number of lost hitpoints of top creature in stack
	INT32 healthLost;
	// * +5C
	// * ?reference to position on side?
	INT32 slotIndex;
	// * +60
	// * the number of creatures in this stack to compare against resurrection
	INT32 numberAtStart;
protected:
	h3unk _f_064[8];
public:
	// * +6C
	// * maximum hit points
	INT32 baseHP;
	// * +70
	INT32 isLucky;
public:
	// * +74
	// * a copy of H3CreatureInformation using combat values in some places
	H3CreatureInformation info;
protected:
	h3unk _f_0E8[12];
public:
	// * +F4
	// * left or right
	INT32 side;
	// * +F8
	//  * reference to position on side
	INT32 sideIndex;
protected:
	// * +FC
	UINT32 last_animation_time;
	// * +100
	INT32 yOffset;
	// * +104
	INT32 xOffset;
	h3unk _f_108[8];
	// * +110 from cranim
	H3MonsterAnimation cranim;
public:
	// * +164
	H3LoadedDEF *def;
protected:
	// * +168
	H3LoadedDEF *shootingDef;
	h3unk _f_16C[4];
	// * +170
	UINT32 moveSound;
	// * +174
	UINT32 attackSound;
	// * +178
	UINT32 getHitSound;
	// * +17C
	UINT32 shotSound;
	// * +180
	UINT32 deathSound;
	// * +184
	UINT32 defendSound;
	// * +188
	UINT32 extraSound1;
	// * +18C
	UINT32 extraSound2;
	h3unk _f_190[4];
public:
	// * +194
	// * the number of spells currently active
	INT32 activeSpellsNumber;
	// * +198
	// * the remaining number of turns of any spells
	INT32 activeSpellsDuration[81];
	// * +2DC
	// * the secondary skill level of applied spells
	INT32 activeSpellsLevel[81];
protected:
	h3unk _f_420[52];
public:
	// * +454
	// * number of retaliations left
	INT32 retaliations;
	// * +458
	// * information about some spell effects
	H3CombatMonsterSpellsData spellsData;

	// * returns appropriate name of stack
	LPCSTR GetCreatureName() { return info.GetCreatureName(numberAlive); }
	// * returns second square if creature occupies 2 squares
	INT32 GetSecondSquare() { return THISCALL_1(INT32, 0x4463C0, this); }
	// * returns actual speed of creature
	INT32 GetStackSpeed() { return THISCALL_1(INT32, 0x4489F0, this); }
	BOOL IsDone() { return info.flags.DONE; }
	BOOL IsClone() { return info.flags.CLONE; }
	BOOL IsSiege() { return info.flags.SIEGEWEAPON; }
	BOOL IsSummon() { return info.flags.SUMMON; }
	BOOL HadMorale() { return info.flags.MORALE; }
	BOOL IsWaiting() { return info.flags.WAITING; }
	BOOL HasMoved() { return info.flags.DONE; }
	// * index 0 ~ 41
	INT32 Index() { return sideIndex + 21 * side; }
	// * show creature information dialog
	VOID ShowStatsDialog(BOOL RightClick);
	// * Checks if hypnotized
	INT32 GetSide() { return THISCALL_1(INT, 0x43FE60, this); }
	// * Checks if hypnotized
	H3Hero * GetOwner() { return THISCALL_1(H3Hero*, 0x4423B0, this); }
	// * the bonus/decreased effect on a spell from targeting a creature
	INT32 GetProtectiveSpellEffect(INT32 damage, INT32 spellID) { return STDCALL_3(INT32, 0x5A7EC0, damage, spellID, this); }
};

constexpr int t = sizeof(H3CombatMonster);

struct H3PrimarySkills
{
	INT8 attack;
	INT8 defense;
	INT8 spellPower;
	INT8 knowledge;
};

struct H3PandorasBox
{
	// * +0
	H3String message;
	// * +10
	BOOL hasGuards;
	// * +14
	H3Army guardians;
	h3unk _f_4C[4];
	// * +50
	INT32 experience;
	// * +54
	INT32 spellPoints;
	// * +58
	INT8 morale;
	// * +59
	INT8 luck;
	h3unk _f_5A[2];
	// * +5C
	H3Resources resources;
	// * +78
	H3PrimarySkills pSkill;
	// * +7C
	H3Vector<INT32> skills;
	// * +8C
	H3Vector<INT32> artifacts;
	// * +9C
	H3Vector<INT32> spells;
	// * +10C
	H3Army creatureReward;
};

// * Pandora's box is same as event
struct H3Event : public H3PandorasBox
{
};

// * Unions don't like to have constructors
// * so this structure his made only for quests
// * based on H3Vector
struct H3QuestVector
{
protected:
	BOOL _init;
public:
	INT32 *first;
	INT32 *last;
	INT32 *capacity;

	INT32 Count() { return last - first; }
	INT32 operator[](INT32 index) { return first[index]; }
};

// * quest in memory, used for seer's hut and quest guards
struct H3Quest
{
	// * +0
	// * 0x641798 + questType * 0x3C
	h3func *vTable;
	// * +4
	// * 0 = quest guard, 1 = seer hut
	INT32 questorType;
	// * +8
	H3String messageProposal;
	// * +18
	H3String messageProgress;
	// * +28
	H3String messageCompletion;
	// * +38
	// * texts variant, of no apparent use
	INT32 stringId;
	// * +3C
	INT32 lastDay;
	// * +40
	// * size 20h, varies depending on quest type.
	union
	{
		INT32 achieveLevel;				// achieve level
		H3PrimarySkills achievePrimarySkill;	// have primary skills
		struct
		{
			INT32 __0;
			INT32 targetHero;
			INT32 successfulPlayers;
		} killHero;						// kill certain hero
		struct
		{
			INT32 __0;
			INT32 packedCoords;
			INT32 displayCreatureType;
			INT32 player;
		} killMonster;					// kill a monster in certain position on the map
		H3QuestVector getArtifacts;		// bring artifacts
		struct
		{
			H3QuestVector number;
			H3QuestVector type;
		} getCreatures;					// bring creatures
		H3Resources getResources;		// bring resources
		INT32 beHero;					// visit as a certain hero
		INT32 bePlayer;					// visit as a certain player
	} data;

	INT32 GetQuestType() { return (this ? (reinterpret_cast<DWORD>(vTable) - 0x641798) / 0x3C + 1 : 0); }
};

// * quest guard is a quest plus a byte to show who visited
struct H3QuestGuard
{
	H3Quest *quest;
	BYTE playersVisited;
};

// * seer hut is a quest guard plus some information about reward
struct H3SeerHut
{
	// * +0
	H3Quest *quest;
	// * +4
	BYTE playersVisited;
	// * +5
	INT32 rewardType;
	// * +9
	INT32 rewardValue;
	// * +C
	INT32 rewardValue2;
	// * +11
	BYTE seerNameId;
	// * +12
	h3unk _f_12;
};

// * if a mapartifact has a custom setup, this is the referenced data
struct H3MapArtifact
{
	// * +0
	H3String message;
	// * +10
	INT8 isGuarded;
	h3unk _f_11[3];
	// * +14
	H3Army guardians;
};

// * if a mapresource has a custom setup, this is the referenced data
struct H3MapResource : public H3MapArtifact
{
};

// * university is an array of 4 sskills
struct H3University
{
	int sSkill[4];
};

// * if a wandering monster has a custom setup, this is the referenced data
struct H3Monster
{
	// * +0
	H3String message;
	// * +10
	H3Resources resources;
	// * +2C
	INT32 artifact;
};

// * the format of global events set to occur
struct H3GlobalEvent
{
	// * +0
	H3String message;
	// * +10
	H3Resources resources;
	// * +2C
	UINT8 players;
	// * +2D
	BOOL8 humanEnabled;
	// * +2E
	BOOL8 computerEnabled;
	// * +2F
	UINT8 _u;
	// * +30
	UINT16 firstDay;
	// * +32
	UINT16 repeatEveryXDays;
};

// * the format of events in towns
struct H3CastleEvent : public H3GlobalEvent
{
	// * +34
	INT32 castleNumber;
	// * +38
	UINT8 building[6];
	// * +3E
	UINT8 _u1[2];
	// * +40
	INT16 creatures[7];
	// * +4E
	UINT8 _u2[2];
};

// * mostly vectors of information used on adventure map
struct H3MainSetup
{
	H3Vector<H3ObjectAttributes> objectAttributes;		// +00	// +01FB70
	H3Vector<H3ObjectDetails> objectDetails;	// +10
	H3Vector<H3LoadedDEF*> defs;			// +20 ???
	H3Vector<H3MapArtifact> artifactResource; // +30
	H3Vector<H3Monster> monsters;	// +40
	H3Vector<H3PandorasBox> pandoraEvents;// +50
	H3Vector<H3SeerHut> seerHuts;	// +60
	H3Vector<H3Quest> quests;		// +70
	H3Vector<H3GlobalEvent> globalEvents;	// +80
	H3Vector<H3CastleEvent> castleEvents;	// +90
protected:
	H3Vector<UINT32> unkA0;       // +A0
public:
	H3Vector<H3QuestGuard> questGuards;       // +B0
protected:
	H3Vector<UINT32> unkC0;       // +C0
public:
	H3MapItem *mapitems; // +D0	// +1FC40
	INT32 mapSize;			// +D4		// +1FC44
	INT8 SubterraneanLevel;	// + D8		// +1FC48
protected:
	h3unk _f_D9[3];			// +D9-B	// +1FC49~B
public:
	H3Vector<H3ObjectAttributes> objectLists[232];

	H3MapItem* GetMapItem(int x, int y, int z) { return THISCALL_4(H3MapItem*, 0x4086D0, this, x, y, z); }
	VOID DrawItem(H3MapItem *mitem, H3ObjectDraw *draw) { THISCALL_3(VOID, 0x505880, this, mitem, draw); }
	VOID AddObjectAttribute(H3ObjectAttributes * oa);
};

// from WoG sources
struct H3CampaignInfo
{
	h3unk _f_0;
	char AvgMapScoreAbove350;
	char CampaignMapIndex;
	h3unk _f_3;
	int BigCampaignIndex;
	h3unk _f_8[4];
	char CrossoverArrayIndex;
	h3unk _f_D[3];
	h3unk _f_10[4];
	h3unk _f_14;
	h3unk _f_15[3];
	h3unk _f_18[4];
	h3unk _f_1C;
	h3unk _f_1D[3];
	h3unk _f_20[4];
	char BigCampaignStarted[21];
	h3unk _f_39[3];
	H3Vector<UINT32> CrossoverHeroes;
	char SomeCrossoverArrays_ref;
	h3unk _f_4D[3];
	int SomeCrossoverArrays;
	h3unk _f_54[4];
	h3unk _f_58[4];
	H3Vector<UINT32> CampaignMapInfo;
	h3unk _f_6C;
	h3unk _f_6D[3];
	VOID *SomeCrossoverInfoStructs;
	h3unk _f_74[8];
};

// * artifact merchants is an array of 7 artifacts
struct H3ArtifactMerchant
{
	INT32 artifacts[7];
};

// * black market is an array of 7 artifacts
struct H3BlackMarket : public H3ArtifactMerchant
{
};

// * the grail is not always here, but when it is...
struct H3Grail
{
	UINT16 x;		// +0
	UINT16 y;		// +2
	UINT8 z;		// +4
	h3unk _f_5;
	INT8 isPresent;	// +6
	h3unk _f_7;
};

// * information about visibility and wandering monster zone control of map tiles
struct H3TileVision
{
	UINT8 vision; // bitfield of players
	UINT8 zoneControl; // does not exist in Demo
};

// from WoG source
struct H3PlayersInfo
{
	h3unk _f_000[8];
	INT8 handicap[8];
	INT32 townType[8];
	h3unk _f_030[8];
	INT8 difficulty;
	CHAR filename[251];
	CHAR saveDirectory[100];
	h3unk _f_198[12];
	INT32 heroMaybe[8];
	h3unk _f_1C4[8];
};

// from wog source
struct _PlayerUnk_
{
	h3unk _f_0[28];
	int heroCount;
	h3unk _f_20[36];
};

// from wog source
struct H3MapInfo
{
	int mapVersion;
	h3unk _f_4;
	char mapDifficulty;
	h3unk _f_6;
	h3unk _f_7;
	h3unk _f_8;
	h3unk _f_9;
	h3unk _f_A;
	char maxHeroLevel;
	h3unk _f_C;
	char playerTeam[8];
	h3unk _f_15[27];
	char specialVictoryCondition;
	char allowDefeatAllVictory;
	h3unk _f_32[6];
	int victoryConditionHero; // +38
	h3unk _f_3C[12];
	int VictoryConditionTownX;
	int VictoryConditionTownY;
	int VictoryConditionTownZ;
	h3unk _f_54[20];
	int VictoryConditionHeroX;
	int VictoryConditionHeroY;
	int VictoryConditionHeroZ;
	h3unk _f_74[44];
	_PlayerUnk_ PlayerUnk[8];
	h3unk _f_2C0[16];
};

// * the data for mines on the adventure map
struct H3Mine // size 0x40
{
	// * +0
	// -1 no owner
	INT8 owner;
	// * +1
	// * mine type. 0~6 resource, 7 abandonned
	INT8 type;
	h3unk _f_02[2];
	// * +4
	// * garrisoned army
	H3Army army;
	// * +3C
	UINT8 x;
	// * +3D
	UINT8 y;
	// * +3E
	UINT8 z;
	h3unk _f_3F;
};

// * custom text for signpost
struct H3Signpost
{
	INT8  HasMess;
	INT8 _u1[3];
	H3String message;
};

// * data of creature dwelling on adventure map
struct H3Dwelling
{
	// * +0
	INT8 type;
	// * +1
	INT8 subtype;
	INT8 _f2[2];
	// * +4
	INT32 creatureTypes[4];
	// * +14
	INT16 creatureCounts[4];
	// * +1C
	H3Army defenders;
	// * +54
	UINT8 x;
	// * +55
	UINT8 y;
	// * +56
	UINT8 z;
	// * +57
	INT8 ownerID;
	UINT8 _f58[4];
};

// * garrison data on adventure map
struct H3Garrison
{
	// * +0
	INT8 owner;
	UINT8 _f01[3];
	// * +4
	H3Army army;
	// * +40
	BOOL8 canRemoveCreatures;
	// * +41
	UINT8 x;
	// * +42
	UINT8 y;
	// * +43
	UINT8 z;
};

// * boat data on adventure map
// from WoG source
struct H3Boat // size 0x28 from 0x4CE5C0
{
	INT16 x;
	INT16 y;
	INT16 z;
	INT8 visible;
	H3MapItem *item; // 7
	h3unk _f_0B;
	INT32 object_type; // C
	INT8 object_flag;
	h3unk _f_11[3];
	INT32 object_setup; // 14h
	INT8 exists; // 18h
	INT8 index; // 19h
	INT8 par1;
	INT8 par2;
	INT8 owner; // 1Ch
	h3unk _f_1D[3];
	INT32 hero_id; // 20h
	INT8 has_hero; //24h
	h3unk _f_25[3];
};
#include <WTypes.h>
// * how h3combatmonster is represented during quick combat
struct H3QuickBattleCreatures
{
	INT32 count;
	INT32 type;
	INT32 num1;
	INT32 num2;
	INT32 speed;
	DOUBLE f_14;
	DOUBLE f_1C;
	DOUBLE f_24;
	h3unk f_2C[4];
	h3unk f_30[4];
	h3unk f_34[4];
	INT32 turretPriority;
	INT32 unitPower;
	INT32 stackPower;
	h3unk f_44[4];
};

// * represents one of the two sides during quick combat
struct H3AIQuickBattle
{
	H3Vector<H3QuickBattleCreatures> creatures;
	INT32 specialTerrain;
	INT32 spellPoints;
	BOOL8 canCastSpells;
	h3unk _f_19[3];
	INT32 armyStrength;
	INT8 tactics;
	h3unk _f_21[3];
	H3Hero *hero;
	H3Army *army;
	H3Hero *opponent;
	BOOL turrets;
	h3unk _f_31;
	INT16 turretsLevel;

	VOID DeleteCreatures() { THISCALL_2(VOID, 0x424880, this, 1); }
};

// * access data about objects on the adventure map
struct H3GlobalObjectSettings
{
	BOOL8 cannotEnter; // +0
	BOOL8 exitTop; // +1
	UINT8 canBeRemoved; // used at 0x548362
	h3unk _align; // probably alignment. All objects 0
	LPCSTR objectName;
	INT32 objectID;
	BOOL decor; // is it a decorative item?
};

// * the movement cost to reach a tile for a given hero
struct H3TileMovement // size 30
{
protected:
	H3Position mixedPosition;
public:
	struct accessability
	{
		unsigned accessible : 1;// 1
		unsigned unk1 : 3;		// 2, 4, 8
		unsigned entrance : 1;	// 0x10
		unsigned unk2 : 27;		// 0x20, 0x40, 0x80, ...
	}access;
protected:
	h3unk _f_08[16]; // +8
public:
	UINT16 movementCost; // +18
protected:
	UINT16 movementCost2; // +1A
	h3unk _f_1C[2];
public:
	UINT8 GetX() { return mixedPosition.GetX(); }
	UINT8 GetY() { return mixedPosition.GetY(); }
	UINT8 GetZ() { return mixedPosition.GetZ(); }

	BOOL ZoneControlled() { return (0x0100 & FASTCALL_3(UINT16, 0x4F8040, GetX(), GetY(), GetZ())); }
	H3MapItem *GetMapItem();
};

// from wog source
struct H3TurnTimer
{
	UINT lastShownTime;
	UINT startTimeMain;
	UINT turnLimit;
	UINT showNextPeriod;
	UINT battleStartTime;
};

struct H3CreatureExchange
{
	H3LoadedDEF *def;
protected:
	h3unk _f_04[104];
public:
	H3Army *army; // +6C
protected:
	h3unk _f_70[4];
public:
	H3Hero *hero; // +74
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////	MANAGERS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// * doesn't follow Manager format [size 0x70]
// * handles movement calculations on adventure map
// * is also used during combat
struct H3MovementManager
{
	// * +0
	h3unk _f_00[8];
	// * +8
	INT32 available_movement;
	// * +C
	INT32 maxLandMovement;
	// * +10
	// * see 0x56B768
	INT32 maxWaterMovement;
	h3unk _f_14;
	// * +15
	// * can hero cast Dimension Door?
	BOOL8 DD_access;
	// * +16
	// * can hero cast fly?
	BOOL8 fly_access;
	// * +17
	// * can cast waterwalk?
	BOOL8 waterwalk_access;
	// * +18
	// * level of waterwalk if cast
	INT32 waterwalk_level;
	// * level of fly if cast
	INT32 fly_level;
	h3unk _f_20[4];
	// * an array of tile movement
	H3TileMovement **movement_info;
	h3unk _f28[8];
	// * +30
	// * map width
	INT32 mapX;
	// * +34
	// * map height
	INT32 mapY;
	// * a vector of??
	H3Vector<UINT32> f38;
	// * a vector of??
	H3Vector<UINT32> f48;
	// * a vector of??
	H3Vector<UINT32> f58;
	// * +68
	// * ???
	INT32 battleHexes;
	h3unk _f6C[4];

	// * returns reference to H3TileMovement at position
	H3TileMovement *GetMovementInfo(UINT32 mixed_position) { return THISCALL_3(H3TileMovement*, 0x42ECC0, this, mixed_position, 0); }
};

// * doesn't follow Manager format
// * most of the game data is stored here
// * most entries are self-explanatory
struct H3Main
{
protected:
	h3unk _f_0000[4];
public:
	// * +4
	INT8 disabledShrines[70];
	// * +4A
	INT8 disabledSpells[70];
protected:
	// * +90
	UINT32 cs_bink;
	// * +94
	H3Vector<UINT32> townPreSetup;
	// * +A4
	H3SetupHero heroSetup[156];
	h3unk _f_1F454[4];
	// * +1F458
	H3CampaignInfo campaignInfo;
	h3unk _f_1F4D4[354];
public:
	// * +1F636
	BOOL8 isDead[8];
	// * +1F63E
	H3Date date;
protected:
	h3unk _f_1F644[32];
public:
	// * +1F664
	H3ArtifactMerchant artifactMerchant;
	// * +1F680
	H3Vector<H3BlackMarket> blackMarkets;
	// * +1F690
	H3Grail grail;
	// * +1F698
	// * 0 - RoE, 1 - AB, 2 - SoD
	INT32 mapKind;
	// * +1F69C
	BOOL8 isCheater;
	// * +1F69D
	// * fun fact : Griffin dwelling doesn't require Blacksmith in this mode
	BOOL8 inTutorial;
protected:
	h3unk _f_1F69E[2];
public:
	// * +1F86C
	H3PlayersInfo playersInfo;
	// * +1FA38
	H3MapInfo mapInfo;
	// * +1FB3C
	H3String mapName;
	// * +1FB4C
	H3String mapDescription;
protected:
	h3unk _f_1FB5C[20];
public:
	// * +1FB70
	H3MainSetup mainSetup;
protected:
	h3unk _f_20ACC[4];
public:
	// * +20AD0
	H3Player players[8];
	// * +21610
	H3Vector<H3Town> towns;
	// * +21620
	H3Hero heroes[156];
	// * +4DF18
	INT8 heroOwner[156];
	// * +4DFB4
	H3Bitfield heroMayBeHiredBy[156];
	// * +4E224
	INT8 randomArtifacts[144];
	// * +4E2B4
	INT8 artifactsAllowed[144];
protected:
	h3unk _f_4E344[32];
public:
	// * +4E364
	// * bitfield for players
	UINT8 keymasterVisited[8];
protected:
	h3unk _f_4E36C[12];
public:
	// * +4E378
	H3Vector<H3Signpost> signpostsBottles;
	// * +4E388
	H3Vector<H3Mine> minesLighthouses;
	// * +0x4E398
	H3Vector<H3Dwelling> dwellings;
	// * +0x4E3A8
	H3Vector<H3Garrison> garrisons;
	// * +0x4E3B8
	H3Vector<H3Boat> boats;
	// * +0x4E3C8
	H3Vector<H3University> universities;
	// * +0x4E3D8
	H3Vector<H3CreatureBank> creatureBanks;
	// * +4E3E8
	INT8 obeliskCount;
	// * +4E3E9
	UINT8 obeliskVisited[48];
protected:
	h3unk _f_4E419[575];
public:
	// * +4E658
	INT8 bannedSkills[28];
protected:
	h3unk _f_4E674[4];
public:
	// * +4E678
	// * H3Position
	H3Vector<UINT32> monolithTwoWay[8];
	// * +4E6F8
	// * H3Position
	H3Vector<UINT32> monolithOneWay[8];
protected:
	h3unk _f_4E778[4];
public:
	// * +4E77C
	// * H3Position
	H3Vector<UINT32> whirlPools;
	// * +4E78C
	// * H3Position
	H3Vector<UINT32> subterraneanGatesDestination;
	// * +4E79C
	// * H3Position
	H3Vector<UINT32> subterraneanGatesID;
protected:
	H3Vector<h3unk> _f_4E7AC;
	H3Vector<h3unk> _f_4E7BC;
	h3unk _f_4E7CC[4];
public: // functions

	H3MapItem *GetMapItem(UINT32 mixedPosition) { return THISCALL_2(H3MapItem*, 0x42ED80, this, mixedPosition); }
	H3Player *GetPlayer() { return THISCALL_1(H3Player*, 0x4CE670, this); }
	INT32 GetPlayerID() { return THISCALL_1(INT32, 0x4CE6E0, this); }
	H3Hero *GetHero(INT32 id) { return THISCALL_2(H3Hero*, 0x4317D0, this, id); }
	VOID ResetRandomArtifacts() { memset(randomArtifacts, 0, sizeof(randomArtifacts)); }
	INT32 GetRandomArtifactOfLevel(INT32 level) { return THISCALL_2(INT32, 0x4C9190, this, level); }
	VOID SaveGame(LPCSTR save_name) { THISCALL_6(VOID, 0x4BEB60, this, save_name, 1, 1, 1, 0); }
	VOID PlaceObjectOnMap(int x, int y, int z, int type, int subtype, int setup = -1) { THISCALL_7(VOID, 0x4C9550, this, x, y, z, type, subtype, setup); }
};

// * size 38h
// * base manager format
struct H3Manager
{
protected:
	struct {
		h3func managerConstructor; // 0x44D200
		h3func managerDestructor;
		h3func managerUpdate;
		// goes on
	} *h3ManagerVTable;

	H3Manager *parent;
	H3Manager *child;
	h3unk _f_0C[4];
	INT z_order;
	CHAR name[28]; // 0x14
	INT32 nameEnd; // 0x30
	h3unk _f_34[4];
public:
	VOID SetPreviousManager(H3Manager *prev) { parent = prev; }
	VOID SetNextManager(H3Manager *next) { child = next; }
};

// * the manager of managers
struct H3Executive
{
	H3Manager *first_mgr;
	H3Manager *last_mgr;
	H3Manager *active_mgr;
	h3unk _f_0C[4];

	VOID RemoveManager(H3Manager *mgr) { THISCALL_2(VOID, 0x4B0950, this, mgr); }
	INT AddManager(H3Manager *mgr, int order) { return THISCALL_3(INT, 0x4B0880, this, mgr, order); }
};

// * This removes the following warning when using enum
// * warning C4482: nonstandard extension used: enum '...' used in qualified name
#pragma warning(push)
#pragma warning(disable : 4482)
// * manager for mouse
struct H3MouseManager : public H3Manager
{
protected:
	h3unk _f_38[20];
	INT32 cursorType; // 0 crdeflt, 1 cradvntr, 2 crcombat, 3 crspell, 4 artifact @ 0x67FF88
	INT32 cursorFrame;
	H3LoadedDEF *cursorDef;
	h3unk _f_58[16];
	BOOL cursorHidden;
	h3unk _f_6C[12];
	RTL_CRITICAL_SECTION criticalSection; // 0x78
public:
	enum H3MouseCursorType : INT32
	{
		Cursor_Default,
		Cursor_Adventure,
		Cursor_Combat,
		Cursor_Spell,
		Cursor_Artifact
	};

	enum H3MouseAdventureMapCursorType
	{
		AMC_ArrowPointer,
		AMC_Busy_Wait,
		AMC_Hero,
		AMC_Town,
		AMC_Horse,
		AMC_Attack,
		AMC_Boat,
		AMC_Anchor,
		AMC_Hero_Meeting,
		AMC_Rearing_Horse,
		AMC_Horse2,
		AMC_Attack2,
		AMC_Boat2,
		AMC_Anchor2,
		AMC_Hero_Meeting2,
		AMC_Rearing_Horse2,
		AMC_Horse3,
		AMC_Attack3,
		AMC_Boat3,
		AMC_Anchor3,
		AMC_Hero_Meeting3,
		AMC_Rearing_Horse3,
		AMC_Horse4,
		AMC_Attack4,
		AMC_Boat4,
		AMC_Anchor4,
		AMC_Hero_Meeting4,
		AMC_Rearing_Horse4,
		AMC_Boat_1,
		AMC_Boat_2,
		AMC_Boat_3,
		AMC_Boat_4,
		AMC_Map_Scroll_North,
		AMC_Map_Scroll_Northeast,
		AMC_Map_Scroll_East,
		AMC_Map_Scroll_Southeast,
		AMC_Map_Scroll_South,
		AMC_Map_Scroll_Southwest,
		AMC_Map_Scroll_West,
		AMC_Map_Scroll_Northwest,
		AMC_Arrow_Pointer,
		AMC_Dimension_Door,
		AMC_Scuttle_Boat
	};

	enum H3MouseBattleFieldCursorType
	{
		BFC_Null,
		BFC_Move,
		BFC_Fly,
		BFC_Shooting,
		BFC_Hero,
		BFC_Question_Mark,
		BFC_Arrow_Pointer,
		BFC_Attack_Northeast,
		BFC_Attack_East,
		BFC_Attack_Southeast,
		BFC_Attack_Southwest,
		BFC_Attack_West,
		BFC_Attack_Northwest,
		BFC_Attack_North,
		BFC_Attack_South,
		BFC_Half_Damage,
		BFC_Attack_Wall,
		BFC_Heal,
		BFC_Sacrifice,
		BFC_Teleport
	};

	VOID TurnOn() { THISCALL_2(VOID, 0x50D7B0, this, 1); }
	VOID TurnOff() { THISCALL_2(VOID, 0x50D7B0, this, 0); }
	INT32 GetType() { return cursorType; }
	INT32 GetFrame() { return cursorFrame; }
	VOID SetCursor(INT32 type, INT32 frame) { THISCALL_3(VOID, 0x50CEA0, this, frame, type); }
	VOID DefaultCursor() { SetCursor(0, 0); }
	VOID SetArtifactCursor(INT32 art_id) { SetCursor(art_id, H3MouseCursorType::Cursor_Artifact); }
};

// * named heroWindowManager in H3, abbreviated
// * in charge of drawing and dialogs
struct H3WindowManager : public H3Manager
{
protected:
	UINT32 resultItemID; // 0x38
	h3unk _f_3C[4];
	UINT32 drawBuffer; // 0x40
	H3LoadedPCX16 *screenPcx16;
	struct H3Dlg *firstDlg;
	struct H3Dlg *lastDlg;
	h3unk _f_58[8];
public:

	enum H3ClickIDs
	{
		H3ID_OK = 30725,
		H3ID_CANCEL = 30726
	};

	VOID H3Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy) { THISCALL_5(VOID, 0x603190, this, x, y, dx, dy); }
	UINT32 ClickedItemID() { return resultItemID; }
	BOOL ClickedOK() { return resultItemID == H3ClickIDs::H3ID_OK; }
	BOOL ClickedCancel() { return resultItemID == H3ClickIDs::H3ID_CANCEL; }
	H3LoadedPCX16 *GetDrawBuffer() { return screenPcx16; }
};
#pragma warning(pop)

// * in charge of playing sounds
struct H3SoundManager : public H3Manager
{
	UINT32 MSSHandle;
	h3unk _f_40[68];
	INT32 clickSoundVar; // +84
	h3unk _f_88[8];
	_RTL_CRITICAL_SECTION rtlSection[3];
	VOID ClickSound(); // modeled after sub_00456540
};

// * in charge of the adventure map
struct H3AdventureManager : public H3Manager
{
protected:
	h3unk _f_038[12];
public:
	// * +44
	struct H3Dlg *dlg;
protected:
	h3unk _f_048[8];
public:
	// * +50
	// * for complete calculation of tile movements
	BOOL movementCalculated;
	// * +54
	// * for partial calculation of tile movements
	BOOL movementCalculated1;
protected:
	h3unk _f_058[4];
public:
	// * +5C
	// * a reference to H3_Main's mainSetup
	H3MainSetup *map;
protected:
	// * +60
	H3LoadedDEF *terrainDEF[10];
	h3unk _f_088[4];
	// * +8C
	H3LoadedDEF *riverDEF[4];
	h3unk _f_09C[4];
	// * +A0
	H3LoadedDEF *roadDEF[3];
	// * +AC
	H3LoadedDEF *edgDEF;
	// * +B0
	H3LoadedDEF *adagDEF;
	// * +B4
	H3LoadedDEF *agemulDEF;
	// * +B8
	H3LoadedDEF *agemurDEF;
	// * +BC
	H3LoadedDEF *agemllDEF;
	// * +C0
	H3LoadedDEF *agemlrDEF;
	// * +C4
	H3LoadedDEF *tshrcDEF;
	// * +C8
	H3LoadedDEF *radarDEF;
	// * +CC
	H3LoadedDEF *tshreDEF;
	// * +D0
	H3Vector<H3LoadedDEF*> defs;
	// * +E0
	H3LoadedDEF *attackDEF;
	// * +E4
	// * the position of top left of the screen
	H3Position screenPosition;
public:
	// * +E8
	// * the position of the mouse cursor in (x,y,z)
	H3Position mousePosition;
	// * +EC
	// * the previous map adventure coordinates of the mouse
	POINT previousMousePosition;
protected:
	h3unk _f_0F4[24];
	// * +10C
	H3LoadedDEF *heroDEF[18];
	// * +154
	H3LoadedDEF *boatDEF[3];
	// * +160
	H3LoadedDEF *boatMovementDEF[3];
	// * +16C
	H3LoadedDEF *heroFlags_00[8];
	// * +18C
	H3LoadedDEF *heroFlags_01[8];
	// * +1AC
	H3LoadedDEF *heroFlags_02[8];
	// * +1CC
	H3LoadedDEF *heroFlags_03[8];
	// * +1EC
	BOOL8 drawTransparentHero; // see 40F65F
	h3unk _f_1ED[3];
public:
	// * +1F0
	INT32 terrain;
protected:
	h3unk _f_1F4[8];
	// * +1FC
	INT32 heroDirection;
	h3unk _f_200[12];
	// * +20C
	INT8 centeredHero;
	h3unk _f_20D[11];
public:
	// * +218
	INT32 monsterTypeBattle;
	// * +21C
	INT32 monsterCountBattle;
	// * +220
	INT32 monsterSideBattle;
protected:
	h3unk _f_224[36];
	// * +248
	UINT32 loopSounds[70];
	// * +360
	UINT32 horseXYSounds[11];
	h3unk _f_38C[8];
public:
	// * +394
	// * see ePanel
	INT32 currentInfoPanel;
protected:
	h3unk _f_398[32];
public:

	enum ePanel
	{
		PHero = 3,
		PTown = 4
		// from 0 through 7
	};

	H3MapItem* GetMapItem()             { return THISCALL_2(H3MapItem*, 0x412B30, this, mousePosition.Mixed()); }
	H3MapItem* GetMapItem(int mixedPos) { return THISCALL_2(H3MapItem*, 0x412B30, this, mixedPos); }
	H3MapItem* GetMapItem(int x, int y, int z) { return THISCALL_4(H3MapItem*, 0x4086D0, map, x, y, z); }
	UINT8 GetX() { return mousePosition.GetX(); }
	UINT8 GetY() { return mousePosition.GetY(); }
	UINT8 GetZ() { return mousePosition.GetZ(); }
	VOID FullUpdate() { THISCALL_3(VOID, 0x417380, this, 1, 0); }
	VOID MobilizeHero() { THISCALL_4(VOID, 0x417540, this, 0, 0, 0); }
	VOID DemobilizeHero() { return THISCALL_3(VOID, 0x4175E0, this, 0, 0); }
	/*VOID MovementCalculationsMouse(VOID) { THISCALL_2(VOID, 0x419400, this, mousePosition.mixed); }*/
	VOID MovementCalculationsMouse() { THISCALL_2(VOID, 0x419400, this, mousePosition.Mixed()); }
	VOID MovementCalculations(UINT32 mixedPosition) { THISCALL_2(VOID, 0x419400, this, mixedPosition); }
	VOID MakeHeroPath() { THISCALL_4(VOID, 0x418D30, this, 1, 1, 1); }
	VOID ShowCoordinates(INT32 x, INT32 y, INT8 z);
	INT SimulateMouseOver(INT x, INT y) { return THISCALL_3(int, 0x40E2C0, this, x, y); }
	INT SimulateMouseOver(POINT & p) { return SimulateMouseOver(p.x, p.y); }
	CHAR UpdateHintMessage() { return THISCALL_5(CHAR, 0x40B0B0, this, GetMapItem(), GetX(), GetY(), GetZ()); }
};

// * trading between two armies
struct H3SwapManager : public H3Manager // size 0x68
{
protected:
	h3unk _f_38[8];
public:
	H3Hero *hero[2]; // similar to https://github.com/potmdehex/homm3tools/blob/master/hd_edition/hde_mod/hde/structures/swapmgr.h
	INT32 heroSelected;
	INT32 heroClicked;
protected:
	h3unk _f_50[4];
public:
	INT32 slotClicked;
protected:
	h3unk _f_58[5];
	BOOL8 samePlayer; // +5D
	h3unk _f_5E[10];
};

// * in charge of towns
struct H3TownManager : public H3Manager // size 472
{
	// * +38
	// * current town structure
	H3Town *town;
protected:
	h3unk _f_3C[224];
public:
	// * +11C
	// * ???
	H3CreatureExchange *top;
	// * +120
	// * this gets copied to recipientPage during mouse hover, however if you click fast enough the update isn't done
	H3CreatureExchange *bottom;
	// * +12C
	// * source page
	H3CreatureExchange *source;
	// * +130
	// * number of source stack
	INT32 sourcePageStack;
	// * +134
	// * recipient page
	H3CreatureExchange *recipientPage;
	// * +138
	// * number of recipient page
	INT32 recipientPageStack;
protected:
	h3unk _f_13C[100];
	// * +1A0
	// * bitfield of what can be built in the construction screen of the city
	H3Bitfield buildings[2];
	h3unk _f_1B0[20];
	h3unk _f_1C4[4];
	h3unk _f_1C8[16];
public:
	VOID Draw() { THISCALL_1(VOID, 0x5D5930, this); }
	VOID RefreshScreen() { THISCALL_1(VOID, 0x5D5810, this); }
};

// * keyboard and mouse input
struct H3InputManager : public H3Manager
{
	// * modifies equivalent WM_ messages into H3 messages
	enum MessageType
	{
		MT_KEYDOWN       = 1,  // 0x100
		MT_KEYUP         = 2,  // 0x101
		MT_MOUSEMOVE     = 4,  // 0x200
		MT_LBUTTONDOWN   = 8,  // 0x201
		MT_LBUTTONUP     = 16, // 0x202
		MT_LBUTTONDBLCLK = 8,  // 0x203
		MT_RBUTTONDOWN   = 32, // 0x204
		MT_RBUTTONUP     = 64, // 0x205
		MT_RBUTTONDBLCLK = 32, // 0x206
	};

	struct InputMessages
	{
		UINT message;
		h3unk f_4[28]; // contents vary
	}messages[64]; // see 0x4EC6B8, % 64
	INT current_message;
	INT next_message;
	// ... goes on a bit

	InputMessages& GetCurrentMessage() { return messages[current_message]; }
};

// * data for a single battlefield square
struct H3CombatSquare
{
	// * +0
	// * pixel position on screen
	INT16 x;
	// * +2
	// * pixel position on screen
	INT16 y;
	// * +4
	// * pixel position on screen
	INT16 left;
	// * +6
	// * pixel position on screen
	INT16 top;
	// * +8
	// * pixel position on screen
	INT16 right;
	// * +A
	// * pixel position on screen
	INT16 bottom;
	h3unk _f_0C[4];
	// * +10
	UINT8 obstacleBits;
	UINT8 _f_11[3];
	// * +14
	INT32 obstacleIndex;
	// * +18
	// * the side of stack on this square
	INT8 stackSide;
	// * +19
	// * the index of stack on this square
	INT8 stackIndex;
	// * +1A
	// * true if a wide creature is here
	BOOL8 twoHexMonsterSquare;
	h3unk _f_1B;
	// * +1C
	INT32 deadStacksNumber;
	// * +20
	INT8 DeadStackSide[14];
	// * +2E
	INT8 DeadStackIndex[14];
	// * +3C
	h3unk _f_3C[14];
	// * +4A
	INT8 AvailableForLeftSquare;
	// * +4B
	INT8 AvailableForRightSquare;
	h3unk _f_4C[32];
	h3unk _f_6C[4];

	H3CombatMonster *GetMonster() { return THISCALL_1(H3CombatMonster*, 0x4E7230, this); }
};

// * from wog source
// * size 24h
struct TownTowerLoaded
{
	INT32 crType2Shot;
	H3LoadedDEF *monDefLoaded;
	H3LoadedDEF *shotDefLoaded;
	INT32 creatureX;
	INT32 creatureY;
	INT32 orientation;
	INT32 defGroup;
	H3DefFrame *frame;
	INT32 StackNumber;
};

// * index of adjacent squares
// * -1 if outside of battlefield
struct H3AdjacentSquares
{
	INT16 topRight;
	INT16 right;
	INT16 bottomRight;
	INT16 bottomLeft;
	INT16 left;
	INT16 topLeft;
};

// * the manager of the battlefield
struct H3CombatManager : public H3Manager
{
protected:
	h3unk _f_0038[4];
public:
	enum BATTLE_ACTION : INT32
	{
		BA_CANCEL, //0 = Cancel Action(the stack can do a different action now but it may still be impossible to force it to do most actions through ERM).
		BA_CAST_SPELL, //1 = Hero casts a spell
		BA_WALK,
		BA_DEFEND,
		BA_RETREAT,
		BA_SURRENDER,
		BA_WALK_ATTACK,
		BA_SHOOT,
		BA_WAIT,
		BA_CATAPULT,
		BA_MONSTER_SPELL,
		BA_FIRST_AID_TENT,
		BA_NOTHING //12 = No action(can be to disable stack for this round)
	};

	// * +3C
	BATTLE_ACTION action;
	// * +40
	INT32 actionParameter;
	// * +44
	INT32 actionTarget;
	// * +48
	INT32 actionParameter2;
	// * +4C
	INT8 accessibleSquares[187];
	// * +107
	INT8 accessibleSquares2[187];
protected:
	h3unk _f_01C2[2];
public:
	// * +1C4
	H3CombatSquare squares[187];
	// * +5394
	INT32 landType;
protected:
	h3unk _f_5398[12];
public:
	// * +53A4
	INT32 siegeKind;
	// * +53A8
	INT32 hasMoat;
protected:
	h3unk _f_53AC[4];
public:
	// * +53B0
	H3LoadedPCX16 *drawBuffer;
protected:
	h3unk _f_53B4[4];
public:
	// * +53B8
	BOOL doNotDrawShade;
	// * +53BC
	// * H3MapItem where combat is taking place
	H3MapItem *mapitem;
	// * +53C0
	// * special terrain type used
	INT32 specialTerrain;
	// * +53C4
	BOOL8 antiMagicGarrison;
	// * +53C5
	BOOL8 creatureBank;
	// * +53C6
	BOOL8 boatCombat;
protected:
	h3unk _f_53C7;
public:
	// * +53C8
	// * town structure where combat is taking place
	H3Town *town;
	// * +53CC
	// * hero structures from each side
	H3Hero *hero[2];
	// * +53D4
	// * spell power from each side
	INT32 heroSpellPower[2];
protected:
	h3unk _f_53DC[8];
	// * +53E4
	UINT32 HeroAnimation[2];
	// * +53EC
	UINT32 HeroAnimationCadre[2];
	h3unk _f_53F4[16];
	// * +5404
	H3LoadedDEF *heroDefLoaded[2];
	// * +540C
	H3LoadedDEF *heroFlagLoaded[2];
	// * +5414
	INT32 heroFlagFrame[2];
	// * +541C
	RECT heroUpdateRect[2];
	// * +543C
	RECT heroFlagUpdateRect[2];
	// * +545C
	// * eagle eye 2x vector
	H3Vector<INT32> eagleEyeSpells[2];
	// * chain lightning?
	h3unk _f_547C[40];
public:
	// * +54A4
	UINT8 isNotAI[2];
	// * +54A6
	BOOL8 isHuman[2];
	// * +54A8
	INT32 heroOwner[2];
	// * +54B0
	BOOL8 artifactAutoCast[2];
protected:
	h3unk _f_54B2[2];
public:
	// * +54B4
	BOOL heroCasted[2];
	// * +54BC
	INT32 heroMonCount[2];
	// * +54C4
	H3Army *army[2];
	// * +54CC
	// * a two-sided array of 21 stacks for each side of combat
	H3CombatMonster stacks[2][21];
protected:
	h3unk _f_1329C[4];
public:
	// * +132A0
	INT32 turnsSinceLastEnchanterCast[2];
protected:
	h3unk _f_132A8[16];
public:
	// * +132B8
	INT32 currentMonSide;
	// * +132BC
	INT32 currentMonIndex;
	// * +132C0
	INT32 currentActiveSide;
	// * +132C4
	INT32 autoCombat;
	// * +132C8
	H3CombatMonster *activeStack;
	// * +132CC
	INT8 blueHighlight;
protected:
	h3unk _f_132CD[3];
public:
	// * +132D0
	INT32 creature_at_mouse_pos;
	// * +132D4
	INT32 mouse_coord;
	// * +132D8
	INT32 attacker_coord;
	// * +132DC
	// * the icons of CRCOMBAT.def, see H3MouseManager::H3MouseBattleFieldCursorType
	INT32 move_type;
protected:
	h3unk _f_132E0[20];
public:
	// * +132F4
	INT32 siegeKind2;
	// * +132F8
	BOOL finished;
	// * +132FC
	struct H3Dlg *dlg;
protected:
	h3unk _f_13300[356];
	// * +13464
	LPCSTR backgroundPcxName;
	// * +13468
	//INT16 AdjascentSquares[1122];
public:
	H3AdjacentSquares adjacentSquares[187];
protected:
	h3unk _f_13D2C[12];
	// * +132E8
	RECT updateRect;
	h3unk _f_13D48[12];
	// * +13D54
	INT cmNumWinPcxLoaded;
public:
	// * +13D58
	// * information about obstacles on battlefield
	H3Vector<H3Obstacle> obstacleInfo;
	// * +13D68
	BOOL tacticsPhase;
	// * +13D6C
	INT32 turn;
	// * +13D70
	INT32 tacticsDifference;
protected:
	h3unk _f_13D74[4]; // spell related?
	// * +13D78
	TownTowerLoaded Towers[3];
public:
	// * +13DE4
	INT32 waitPhase;
protected:
	// * +13DE8
	INT32 HeroDAttack;
	// * +13DEC
	INT32 HeroDDefence;
	// * +13DF0
	INT32 HeroDSpellPower2;
	// * +13DF4
	INT32 HeroDSpellPoints;
	// * +13DF8
	INT32 TownPicturesLoaded[90];
public:
	// * +13F60
	// * hit points of town walls
	INT32 fort_walls_hp[18];
	// * +13FA8
	INT32 fort_walls_alive[18];
protected:
	UINT8 f13FF0[4];
public:
	// * +13FF4
	// * pcx of grids
	H3LoadedPCX *CCellGrdPcx;
	// * +13FF8
	// * pcx to shade in blue using cheat menu
	H3LoadedPCX *CCellShdPcx;
protected:
	// * +13FFC
	INT32 GlobalCardeIndex;
public:
	// * +14000
	// * oddly there are only 20, not 21, slots for each side
	BOOL8 RedrawCreatureFrame[2][20];
protected:
	h3unk _f_14028[228];
public:
	// functions
	VOID SimulateMouseAtHex(int hex_id) { return THISCALL_2(VOID, 0x477550, this, hex_id); }
	BOOL8 CanCastSpellAtCoord(int spell_id, int spell_expertise, int coordinates)
	{
		return THISCALL_7(BOOL8, 0x5A3CD0, this, spell_id, spell_expertise, coordinates, currentActiveSide, 1, 0);
	}
	VOID WinBattle(VOID) { return THISCALL_2(VOID, 0x468F80, this, 1 - currentActiveSide); }
	VOID LoadSpell(INT32 spell_id) { return THISCALL_3(VOID, 0x59EF60, this, spell_id, 0); }
	VOID CastSpell(int spell_id, int hex_ix, int cast_type_012, int hex2_ix, int skill_level, int spell_power)
	{
		THISCALL_7(VOID, 0x5A0140, this, spell_id, hex_ix, cast_type_012, hex2_ix, skill_level, spell_power);
	}
	H3CombatMonster *GetResurrectionTarget(INT32 coordinate) { return THISCALL_4(H3CombatMonster*, 0x5A3FD0, this, currentActiveSide, coordinate, 0); }
	H3CombatMonster *GetAnimateDeadTarget(INT32 coordinate) { return THISCALL_3(H3CombatMonster*, 0x5A4260, this, currentActiveSide, coordinate); }
	int NextCreatureToMove(VOID) { return THISCALL_2(int, 0x464C60, this, 1); }
	BOOL8 IsHiddenBattle(VOID) { return THISCALL_1(BOOL8, 0x46A080, this); }
	BOOL8 IsBattleOver(VOID) { return THISCALL_1(BOOL8, 0x465410, this); }
	VOID Refresh() { Refresh(1, 0, 1); }
	VOID Refresh(BOOL redrawScreen, INT timeDelay, BOOL redrawBackground) { THISCALL_7(VOID, 0x493FC0, this, redrawScreen, 0, 0, timeDelay, redrawBackground, 0); }
	VOID RefreshCreatures() { THISCALL_1(VOID, 0x495770, this); }
	VOID ShadeSquare(int index);
	BOOL8 IsHumanTurn() { return isHuman[currentActiveSide]; }
	VOID AddStatusMessage(LPCSTR message, BOOL permanent = TRUE) { THISCALL_4(VOID, 0x4729D0, dlg, message, permanent, 0); }
};

#pragma pack(pop)

// * this is an internal structure to replace the use of defines
// * within the H3API to reduce the likelihood of conflicts.
// * You can always use it instead of the #define equivalents if you prefer
struct H3Pointers
{
	inline static H3MouseManager			* MouseManager()			{ return *reinterpret_cast<H3MouseManager**>(0x6992B0); }
	inline static H3WindowManager			* WindowManager()			{ return *reinterpret_cast<H3WindowManager**>(0x6992D0); }
	inline static H3Executive				* Executive()				{ return *reinterpret_cast<H3Executive**>(0x699550); }
	inline static H3Main					* Main()					{ return *reinterpret_cast<H3Main**>(0x699538); }
	inline static H3CombatManager			* CombatManager()			{ return *reinterpret_cast<H3CombatManager**>(0x699420); }
	inline static H3TownManager				* TownManager()				{ return *reinterpret_cast<H3TownManager**>(0x69954C); }
	inline static H3SoundManager			* SoundManager()			{ return *reinterpret_cast<H3SoundManager**>(0x699414); }
	inline static H3InputManager			* InputManager()			{ return *reinterpret_cast<H3InputManager**>(0x699530); }
	inline static H3AdventureManager		* AdventureManager()		{ return *reinterpret_cast<H3AdventureManager**>(0x6992B8); }
	inline static H3MovementManager			* MovementManager()			{ return *reinterpret_cast<H3MovementManager**>(0x6992D4); }
	inline static H3GlobalObjectSettings	* GlobalObjectSettings()	{ return *reinterpret_cast<H3GlobalObjectSettings**>(0x660428); }
	inline static H3Spell					* Spell()					{ return *reinterpret_cast<H3Spell**>(0x687FA8); }
	inline static H3CreatureBankSetup		* CreatureBankSetup()		{ return *reinterpret_cast<H3CreatureBankSetup**>(0x47A3C1 + 1); }
	inline static H3ValidCatapultTargets	* ValidCatapultTargets()	{ return *reinterpret_cast<H3ValidCatapultTargets**>(0x4929DD + 3); }
	inline static H3ArtifactSetup			* ArtifactSetup()			{ return *reinterpret_cast<H3ArtifactSetup**>(0x660B68); }
	inline static H3CreatureInformation		* CreatureInformation()		{ return *reinterpret_cast<H3CreatureInformation**>(0x6747B0); }
	inline static H3ObstacleInfo			* ObstacleInfo()			{ return *reinterpret_cast<H3ObstacleInfo**>(0x465C21); }
	inline static H3Hero					* DialogHero()				{ return *reinterpret_cast<H3Hero**>(0x698B70); }
	inline static H3TurnTimer				* TurnTimer()				{ return *reinterpret_cast<H3TurnTimer**>(0x4AD194 + 1); }
	inline static H3HeroSpecialty			* HeroSpecialty()			{ return *reinterpret_cast<H3HeroSpecialty**>(0x4B8AF1 + 1); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////	Member functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline BOOL H3Streambuf::Save(PVOID data, UINT data_size)
{
	if (data_size && THISCALL_3(UINT, vTable->saveRegion, this, data, data_size) >= data_size)
		return TRUE;
	return FALSE;
}

inline BOOL H3Streambuf::Load(PVOID data, UINT data_size)
{
	if (data_size && THISCALL_3(UINT, vTable->loadRegion, this, data, data_size) >= data_size)
		return TRUE;
	return FALSE;
}

inline INT32 H3Hero::GetRealSpellDamage(INT32 baseDamage, H3CombatMonster * mon, INT32 spellID, H3Hero * enemy)
{
	INT32 dmg = GetSorceryEffect(spellID, baseDamage, mon);
	dmg = FASTCALL_3(INT32, 0x44B180, dmg, spellID, mon->type); // golem-style resistance
	return mon->GetProtectiveSpellEffect(dmg, spellID);
}

inline BOOL H3Hero::UnlearnSkill(INT32 id)
{
	if (secSkill[id])
	{
		secSkill[id] = 0;
		int pos = secSkillPosition[id];
		secSkillPosition[id] = 0;
		for (int i = 0; i < 28; i++)
		{
			if (secSkillPosition[i] > pos)
				secSkillPosition[i] -= 1;
		}
		secSkillCount -= 1;
		return TRUE;
	}
	return FALSE;
}

inline VOID H3Hero::RecalculateMovement()
{
	H3AdventureManager *adv = H3Pointers::AdventureManager();
	adv->movementCalculated = 0;
	adv->movementCalculated1 = 0;
	if (dest_x != -1)
	{
		adv->MovementCalculations(H3Position::Pack(dest_x, dest_y, dest_z));
		adv->MakeHeroPath();
	}
}

inline INT32 H3Hero::SSkillsLeftToLearn()
{
	int known_skills = 0;
	for (int i = 0; i < 28; i++)
		known_skills += secSkill[i];

	int maxSkills = 3 * ByteAt(0x4E256A); // usually 3 * 8

	if (known_skills >= maxSkills)
		return 0;

	// hero has not learned all of his available skills
	int skills_can_be_learned = 0;

	int sslevel;
	H3Main *main = H3Pointers::Main();

	for (int i = 0; i < 28; i++)
	{
		sslevel = secSkill[i];
		if (!main->bannedSkills[i] || sslevel > 0)
			skills_can_be_learned += 3 - sslevel;
	}
	// only necropolis heroes can learn necromancy, unless hero already has it
	if (hero_class != NH3Heroes::NECROMANCER && hero_class != NH3Heroes::DEATH_KNIGHT && secSkill[NH3Skills::NECROMANCY] == 0 && !main->bannedSkills[NH3Skills::NECROMANCY])
		skills_can_be_learned -= 3;
	// necropolis heroes cannot learn leadership, unless hero already has it
	if ((hero_class == NH3Heroes::NECROMANCER || hero_class == NH3Heroes::DEATH_KNIGHT) && secSkill[NH3Skills::LEADERSHIP] == 0 && !main->bannedSkills[NH3Skills::LEADERSHIP])
		skills_can_be_learned -= 3;
	// dungeon heroes cannot learn water magic, unless hero already has it
	if ((hero_class == NH3Heroes::OVERLORD || hero_class == NH3Heroes::WARLOCK) && secSkill[NH3Skills::WATER_MAGIC] == 0 && !main->bannedSkills[NH3Skills::WATER_MAGIC])
		skills_can_be_learned -= 3;
	// rampart heroes cannot learn fire magic, unless hero already has it
	if ((hero_class == NH3Heroes::RANGER || hero_class == NH3Heroes::DRUID) && secSkill[NH3Skills::FIRE_MAGIC] == 0 && !main->bannedSkills[NH3Skills::FIRE_MAGIC])
		skills_can_be_learned -= 3;

	skills_can_be_learned = std::min(maxSkills - known_skills, skills_can_be_learned);
	skills_can_be_learned = std::max(skills_can_be_learned, 1);
	return skills_can_be_learned - 1; // -1 because it's already included in formula for level to go to
}

inline VOID H3Army::SplitFromStackToStack(INT32 fromStack, INT32 toStack, INT32 fraction)
{
	INT32 num = count[fromStack] / fraction;
	count[fromStack] -= num;
	AddStack(type[fromStack], num, toStack);
}

inline INT32 H3Army::FirstFreeSlot()
{
	INT32 r = 0;
	for (INT32 i = 0; i < 7; i++)
	{
		if (type[i] != -1)
			r++;
		else
			return r;
	}
	return -1;
}

inline INT32 H3Army::FindExistingByIndex(INT32 index)
{
	if (index >= 0 && index < 7)
	{
		int j = 0;
		for (int i = 0; i < 7; i++)
		{
			if (type[i] != -1)
				j++;
			if (j == index)
				return i;
		}
	}
	return -1;
}

inline VOID H3CreatureInformation::UpgradeCost(H3Resources * res, H3CreatureInformation * upg, INT32 count)
{
	res->wood    = (upg->cost.wood - cost.wood) * count;
	res->mercury = (upg->cost.mercury - cost.mercury) * count;
	res->ore     = (upg->cost.ore - cost.ore) * count;
	res->sulfur  = (upg->cost.sulfur - cost.sulfur) * count;
	res->crystal = (upg->cost.crystal - cost.crystal) * count;
	res->gems    = (upg->cost.gems - cost.gems) * count;
	res->gold    = (upg->cost.gold - cost.gold) * count;
}

inline BOOL H3Resources::EnoughResources(H3Resources * cost) const
{
	BOOL r = FALSE;
	while (!r)
	{
		if (cost->wood > wood)
			break;
		if (cost->mercury > mercury)
			break;
		if (cost->ore > ore)
			break;
		if (cost->sulfur > sulfur)
			break;
		if (cost->crystal > crystal)
			break;
		if (cost->gems > gems)
			break;
		if (cost->gold > gold)
			break;
		r = TRUE;
	}

	return r;
}

inline VOID H3Resources::RemoveResources(H3Resources * cost)
{
	wood    -= cost->wood;
	mercury -= cost->mercury;
	ore     -= cost->ore;
	sulfur  -= cost->sulfur;
	crystal -= cost->crystal;
	gems    -= cost->gems;
	gold    -= cost->gold;
}

inline VOID H3Resources::GainResourcesOF(H3Resources * gain)
{
	int *This = reinterpret_cast<int*>(this);
	int *Gain = reinterpret_cast<int*>(gain);
	INT resMax = INT_MAX;
	for (int i = 0; i < 7; i++, This++, Gain++)
	{
		if (*This > 0) // if current is positive
		{
			*This += *Gain;
			if (*Gain > 0)
			{
				if (*This < 0) // no overflow
					*This = resMax;
			}
			else
			{
				if (*This < 0) // can't go in negative resources
					*This = 0;
			}
		}
		else // gain normally
			*This = *This + *Gain;
	}
}

inline VOID H3AdventureManager::ShowCoordinates(INT32 x, INT32 y, INT8 z)
{
	if (x >= 0 && x < h3_MapSize && y >= 0 && y < h3_MapSize)
	{
		DemobilizeHero();
		screenPosition.SetXYZ(gameEdgeHorizontal + x, gameEdgeVertical + y, z);
		FullUpdate(); // force immediate redraw
	}
}

inline VOID H3CombatManager::ShadeSquare(int index)
{
	if (index < 0 || index > 187)
		return;
	H3CombatSquare *sq = &squares[index];
	CCellShdPcx->DrawToPcx16(0, 0, 0x2D, 0x34, drawBuffer, sq->left, sq->top, TRUE); // copied from 0x4935B9 and below
}

inline VOID H3CombatMonster::ShowStatsDialog(BOOL RightClick)
{
	THISCALL_3(VOID, 0x468440, H3Pointers::CombatManager(), this, RightClick);
}

inline VOID H3MainSetup::AddObjectAttribute(H3ObjectAttributes * oa)
{
	H3Vector<H3ObjectAttributes> *list = &objectLists[oa->type];
	THISCALL_4(VOID, 0x4D15F0, list, list->m_end, 1, oa);
}

inline VOID H3CreatureBank::SetupBank(int type, int level)
{
	H3CreatureBankState *cbs = &H3Pointers::CreatureBankSetup()[type].states[level];
	F_memcpy(&guardians, &cbs->guardians, sizeof(H3Army));
	F_memcpy(&resources, &cbs->resources, sizeof(H3Resources));
	creatureRewardType = cbs->creatureRewardType;
	creatureRewardCount = cbs->creatureRewardCount;

	const int stacks = guardians.GetStackCount();
	int stack_to_split;
	int first_free_slot;
	int fractions;
	switch (stacks)
	{
	case 1:
		fractions = 5;
		stack_to_split = 0;
		while (fractions > 1)
		{
			first_free_slot = guardians.FirstFreeSlot();
			if (first_free_slot != -1)
				guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);
			fractions--;
		}
		break;
	case 2:
		stack_to_split = 1;
		fractions = 2;
		first_free_slot = guardians.FirstFreeSlot();
		if (first_free_slot != -1)
			guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);

		fractions = 3;
		stack_to_split = 0;
		while (fractions > 1)
		{
			first_free_slot = guardians.FirstFreeSlot();
			if (first_free_slot != -1)
				guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);
			fractions--;
		}
		break;
	case 3:
		fractions = 2; // split in 2
		stack_to_split = 1; // stack 1 is first split
		first_free_slot = guardians.FirstFreeSlot();
		if (first_free_slot != -1)
			guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);

		stack_to_split = 0; // then stack 0 is split
		first_free_slot = guardians.FirstFreeSlot();
		if (first_free_slot != -1)
			guardians.SplitFromStackToStack(stack_to_split, first_free_slot, fractions);
		break;
	default:
		break;
	}

}

inline VOID H3CreatureBank::UpgradeStack(BOOL upg)
{
	if (upg) // in code there are additional checks for game type (RoE) and creature (4 Elementals)
	{
		if (THISCALL_1(char, 0x47AA50, guardians.type[0])) // creature has upgrade?
			guardians.type[2] = THISCALL_1(INT32, 0x47AAD0, guardians.type[0]);
	}
	else
		guardians.type[2] = guardians.type[0];

}

inline H3Hero * H3Player::GetActiveHero()
{
	return H3Pointers::Main()->GetHero(currentHero);
}

inline H3MapItem * H3TileMovement::GetMapItem()
{
	return H3Pointers::AdventureManager()->GetMapItem(*(int*)this);
}

#endif /* #define _H3STRUCTURES_H_ */