//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STRUCTURES_HPP_
#define _H3STRUCTURES_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_Vector.hpp"
#include "../H3_String.hpp"
#include "../H3_MapItems.hpp"
#include "../H3_Functions.hpp"

namespace h3
{
	// * forward declarations

	struct H3CombatMonster;

#pragma pack(push, 1)

	// * a smart pointer sometimes seen in H3
	// * used for items with virtual destructors
	// * use std::unique_ptr || std::shared_ptr ... otherwise
	template <typename T>
	struct H3SmartPointer : H3Allocator
	{
	protected:
		// * +0
		BOOL8   m_used;
		h3align m_01[3];
		// * +4
		T*      m_data;
	public:
		H3SmartPointer(T* _Ptr = 0);
#ifdef _CPLUSPLUS11_
		H3SmartPointer(H3SmartPointer<T>&& other);
#else
		H3SmartPointer(H3SmartPointer<T>& other);
#endif
		~H3SmartPointer();
		T* get();
		T* operator->();
		T* release();
	};

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

		_H3API_ H3NetworkData(int recipient_id, int msg_id, int data);
		_H3API_ INT32 SendData();
	};

	template <typename T>
	struct H3NetworkDataExtra : H3NetworkData
	{
		H3NetworkDataExtra(int recipient_id, int msg_id, int data, T& extra_data);
		T extra_data;
	};

	// * stored (x,y,z) coordinates H3format
	struct H3Position
	{
	protected:
		UINT pos;
	public:
		// * Cast operator
		_H3API_ operator UINT () const;
		// * returns the packed coordinates
		_H3API_ UINT Mixed();
		// * returns x from coordinates
		_H3API_ UINT8 GetX();
		// * returns y from coordinates
		_H3API_ UINT8 GetY();
		// * returns z from coordinates
		_H3API_ UINT8 GetZ();
		// * provided variables x, y, z, unpacks the coordinates to those variables
		_H3API_ VOID GetXYZ(INT& x, INT& y, INT& z);
		// * modifies x
		_H3API_ VOID SetX(INT16 x);
		// * modifies y
		_H3API_ VOID SetY(INT16 y);
		// * modifies z
		_H3API_ VOID SetZ(INT16 z);
		// * modifies x, y and z
		_H3API_ VOID SetXYZ(INT x, INT y, INT z);
		// * Can be used on the stack safely to pack coordinates
		_H3API_ static UINT Pack(INT x, INT y, INT z);
		// * Can be used on the stack safely to unpack coordinates
		_H3API_ static VOID UnpackXYZ(UINT& coord, INT& x, INT& y, INT& z);
		// * Can be used on the stack safely to unpack X
		_H3API_ static UINT8 UnpackX(UINT& coord);
		// * Can be used on the stack safely to unpack Y
		_H3API_ static UINT8 UnpackY(UINT& coord);
		// * Can be used on the stack safely to unpack Z
		_H3API_ static UINT8 UnpackZ(UINT& coord);
	};

	// * to choose a random index within a range, without repeating results
	struct H3IndexVector
	{
	protected:
		INT    m_minimum;
		INT    m_availableCount;
		BOOL8  m_init; // H3Vector<BOOL8>
		h3align _f_09[3];
		BOOL8* m_begin;
		BOOL8* m_end;
		BOOL8* m_capacity;
	public:
		_H3API_ H3IndexVector(int minNum, int maxNum);
		_H3API_ ~H3IndexVector();
		// * never returns the same value
		// * returns InvalidIndex() if there are no non-selected indexes
		_H3API_ INT ChooseRandom();
		// * returns m_minimum - 1
		_H3API_ INT InvalidIndex();
	};

	// * artifacts as they appear on H3Hero structure
	// * also used for artifact enum
	struct H3Artifact
	{
		INT32 id;
		INT32 subtype; // used for spell scrolls, otherwise -1

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
	};
	
	// * a reference to the 3 animation speeds of H3
	struct H3AnimationSpeed
	{
		FLOAT delay[3];
	};

	// * An "array" representing the 7 resources
	struct H3Resources
	{
		enum H3ResType
		{
			RT_Wood    = 0,
			RT_Mercury = 1,
			RT_Ore     = 2,
			RT_Sulfur  = 3,
			RT_Crystal = 4,
			RT_Gems    = 5,
			RT_Gold    = 6,
		};

		INT32 wood;
		INT32 mercury;
		INT32 ore;
		INT32 sulfur;
		INT32 crystal;
		INT32 gems;
		INT32 gold;

		_H3API_ H3Resources();
		_H3API_ H3Resources(H3Resources const& other);
		// * compares current values against cost
		// * returns true if every current value is greater or equal
		_H3API_ BOOL EnoughResources(const H3Resources& cost) const;
		// * removes cost resources from current
		// * checks for negative overflow!
		_H3API_ VOID RemoveResources(const H3Resources& cost);
		// * adds resources to current
		// * checks for overflow!
		_H3API_ VOID GainResourcesOF(const H3Resources& gain);
		// * Get resources as array
		_H3API_ INT& AsRef(int index);
		// * Number of non-zero resources
		_H3API_ INT Count() const;
		_H3API_ PINT begin();
		_H3API_ PINT end();
		_H3API_ PINT cbegin() const;
		_H3API_ PINT cend() const;
		// * does not check for overflow
		_H3API_ H3Resources& operator+=(const H3Resources& other);
		// * does not check for overflow
		_H3API_ H3Resources& operator-=(const H3Resources& other);
		// * does not check for overflow
		_H3API_ H3Resources& operator=(const H3Resources& other);
	};
	
	// * The arrangment of 7 creatures on various H3 structures
	struct H3Army
	{
		class H3Iterator
		{
			INT32 m_type;
			_H3API_ PINT32 AsArray() const;

		public:
			_H3API_ INT32 Type() const;
			_H3API_ INT32 Count() const;

			_H3API_ INT32& RType();
			_H3API_ INT32& RCount();
		};

		INT32 type[7];
		INT32 count[7];

		// * add amount creature of type to slot
		_H3API_ VOID AddStack(INT32 type, INT32 amount, INT32 slot);
		// * Split fromStack based on fraction denominator to toStack
		// * fraction = 2 cuts in half
		_H3API_ VOID SplitFromStackToStack(INT32 fromStack, INT32 toStack, INT32 fraction);
		// * the first type[] index to hold no creature
		_H3API_ INT32 FirstFreeSlot();
		// * the slot position of the n-th existing stack
		_H3API_ INT32 FindExistingByIndex(INT32 index);
		// * the number of existing stacks
		_H3API_ INT32 GetStackCount();
		// * Total number of creatures
		_H3API_ INT32 GetCreaturesCount();
		// * has at least one creature cre
		_H3API_ BOOL8 HasCreatureType(INT32 cre);
		// * not empty
		_H3API_ BOOL HasCreatures();
		// * remove all contents
		_H3API_ VOID Clear();
		// * clear contents of stack #0-6
		_H3API_ VOID Clear(INT stack);
		// * removes contents and gives creatures
		_H3API_ VOID ClearAndGive(INT type, INT count);
		// * checks if all stacks are flagged as undead
		_H3API_ BOOL8 IsUndeadArmy();
		// * the number of different creature alignments in an army
		// * the creature array can be empty
		_H3API_ INT32 NumberAlignments(INT8 (&towns)[9]);
		// * AI value total for army
		_H3API_ INT32 GetArmyValue();
		_H3API_ H3Iterator* begin();
		_H3API_ H3Iterator* end();
		_H3API_ H3Army& operator=(const H3Army& other);
	};

	// * not the hero on the map
	struct H3SetupHero
	{
		INT8	owner;
		UINT8   _u1[3];
		UINT32  number;             // ???
		UINT32  id;                 // = Id
		UINT8   fl_N;               // = has custom name
		CHAR    name[13];
		UINT8   fl_E;               // = has experience
		UINT8   _u2;
		INT32   experience;
		UINT8   fl_P;               //   +20  db   = custom picture
		UINT8   pic;                //   +21  db   = picture id
		UINT8   fl_SS;              //   +22  db   = custom sskills
		UINT8   _u3;
		UINT32  sSNum;              //!   +24  dd   = number of sskills
		UINT8   sSkill[8];          //  +28  dd*8
		UINT8   sSLev[8];           //   +30  db*8
		UINT8   fl_C;               //   +38  db   = custom creatures
		UINT8   _u4[3];
		UINT32  cType[7];           //   +3C  dd*7 = creature types
		UINT16  cNum[7];            //   +58  dw*7 = creature numbers
		UINT8   group;              //   +66  db   = spread/grouped?
		UINT8   fl_A;               //   +67  db   = custom arts?
		H3Artifact  bodyArt[19];    //+68  dd*2*13 = equipped artifacts, first UINT32 = id, second is setup (for spellscroll, otherwise -1)
		H3Artifact  backpackArt[64];//+100 dd*2*40
		UINT8   backpackCount;      //   +300 db
		UINT16  x0, y0;             //   +301 2*dw
		UINT8   radius;             //!   +305 db
		UINT8   fl_B;               //   +306 db   = custom biblio?
		UINT8   _u6;
		H3String biography;
		UINT8   gender;             //   +318 dd
		UINT8   _u9[3];
		UINT8   fl_SP;              //   +31C db   = custom spells?
		UINT8   _u10[3];
		UINT8   spell[10];          //  +320 db*A ?? length is correct ??
		UINT16  _u11;
		UINT8   fl_PS;              //   +32C db   = custom primary skills?
		INT8    pSkill[4];          //  +32D db*4 = ADPK
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
		// * +0
		UINT32  type;
		enum SpecialtyType
		{
			ST_skill = 0,
			ST_creatureLevel = 1,
			ST_resource = 2,
			ST_spell = 3,
			ST_staticCreature = 4,
			ST_speed = 5,
			ST_conversion = 6,
			ST_dragon = 7,
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
		_H3API_ INT32 MaxLandMovement();
		// * calculates maximum daily movement on water
		_H3API_ INT32 MaxWaterMovement();
		// * calculates maximum daily movement automatically
		_H3API_ INT32 CalcMaxMovement();
		// * give an artifact by reference
		_H3API_ VOID GiveArtifact(H3Artifact& art, INT32 slot);
		// * learn secondary skill by given increase
		_H3API_ VOID LearnSecondarySkill(INT32 id, INT32 increase);
		// * returns effect (none, basic, ... expert) of a spell on a given terrain
		_H3API_ INT32 GetSpellExpertise(INT32 spell_id, INT32 special_terrain);
		// * does this hero own creature of type...?
		_H3API_ BOOL8 HasCreatureType(INT32 type);
		// * the bonus effect on a spell from specialty
		_H3API_ INT32 GetSpellSpecialtyEffect(INT32 spellID, INT32 creatureLevel, INT32 baseDamage);
		// * the bonus effect on a spell from sorcery
		_H3API_ INT32 GetSorceryEffect(INT32 spellID, INT32 baseDamage, H3CombatMonster* mon);
		// * combined effects of a spell on a creature
		_H3API_ INT32 GetRealSpellDamage(INT32 baseDamage, H3CombatMonster* mon, INT32 spellID, H3Hero* enemy);
		// * checks under the hero for special terrain
		_H3API_ INT32 GetSpecialTerrain();
		// * checks if hero has access to a spell
		_H3API_ BOOL HasSpell(INT32 spell);
		// * attempts to combine body artifacts into combo
		_H3API_ VOID BuildCombinationArtifact(INT32 combo_id);
		// * hero loses skill of id
		_H3API_ BOOL UnlearnSkill(INT32 id);
		// * forces recalculation of movement costs on the adventure map
		_H3API_ VOID RecalculateMovement();
		// * is it possible to move to where hero is standing?
		_H3API_ BOOL8 CanFlyOnTile();
		// * how much movement points it costs to move to given mixedPos
		_H3API_ INT32 GetMovementCost(INT32 orientation, UINT32 mixedPos);
		// * the maximum number of level ups required to master remaining secondary skills
		_H3API_ INT32 SSkillsLeftToLearn();
		// * is the hero currently wearing artifact id ?
		_H3API_ BOOL WearsArtifact(INT id);
		// * get the value of primary 0 ~ 3 between 0/1 ~ 99 even if negative
		_H3API_ INT32 GetHeroPrimary(INT primary);
		// * used for diplomacy
		_H3API_ INT32 HasSimilarCreature(INT id);
		// * the class name of the current hero
		_H3API_ LPCSTR GetHeroClassName();
		// * shows hero dialog in right-click mode
		_H3API_ VOID ShowDialog() const;
		// * army value * (attack & defense power coefficient)
		_H3API_ INT GetPower() const;
	};

	// * how date is represented
	struct H3Date
	{
		UINT16 day;
		UINT16 week;
		UINT16 month;
		// * converts day, week, month into days from start, first day being 1
		_H3API_ UINT32 CurrentDay() const;
	};

	struct H3TownCreatureTypes
	{
		class H3Iterator
		{
			INT m_base;

			_H3API_ PINT AsArray() const;

		public:
			_H3API_ INT32 Base() const;
			_H3API_ INT32 Upgraded() const;
			_H3API_ INT32& RBase();
			_H3API_ INT32& RUpgraded();
		};

		INT base[7];
		INT upgrade[7];

		_H3API_ H3Iterator* begin();
		_H3API_ H3Iterator* end();
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
		// * is it built?
		BOOL8	magicGuild[5];
		h3unk	_f_C1[3];
	public:
		// * +C4
		// * the town's name, can be lengthened
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
		// * for the first 32 buildings
		// * the game checks mask against global INT64 which
		// * explains why 2 bitfields can only fit in 32 buildings
		H3Bitfield built[2];
		// * +158
		// * for the remaining buildings
		H3Bitfield built2[2];
		// * +160
		// * will this structure be buildable in this town?
		H3Bitfield buildableMask[2];

		#pragma region townEnums
		enum eTown
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
			B_MAGE_GUILD1   = 0,
			B_MAGE_GUILD2   = 1,
			B_MAGE_GUILD3   = 2,
			B_MAGE_GUILD4   = 3,
			B_MAGE_GUILD5   = 4,
			B_TAVERN        = 5,
			B_WHARF         = 6,
			B_FORT          = 7,
			B_CITADEL       = 8,
			B_CASTLE        = 9,
			B_VILAGE_HALL   = 10,
			B_TOWN_HALL     = 11,
			B_CITY_HALL     = 12,
			B_CAPITOL       = 13,
			B_MARKET        = 14,
			B_RESOURCE_SILO = 15,
			B_BLACKSMITH    = 16,
			B_SPEC17        = 17,
			B_HORDE1        = 18,
			B_HORDE1U       = 19,
			B_WHARF2        = 20,
			B_SPEC21        = 21,
			B_SPEC22        = 22,
			B_SPEC23        = 23,
			B_HORDE2        = 24,
			B_HORDE2U       = 25,
			B_GRAIL         = 26,
			B_DECOR27       = 27,
			B_DECOR28       = 28,
			B_DECOR29       = 29,
			B_DWELL1        = 30,
			B_DWELL2        = 31,
			B_DWELL3        = 32,
			B_DWELL4        = 33,
			B_DWELL5        = 34,
			B_DWELL6        = 35,
			B_DWELL7        = 36,
			B_DWELL1U       = 37,
			B_DWELL2U       = 38,
			B_DWELL3U       = 39,
			B_DWELL4U       = 40,
			B_DWELL5U       = 41,
			B_DWELL6U       = 42,
			B_DWELL7U       = 43,

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
	#pragma endregion

		_H3API_ BOOL IsBuildingBuilt(INT32 id) const;
		_H3API_ LPCSTR GetTownTypeName() const;
		_H3API_ H3Hero* GetGarrisonHero() const;
		_H3API_ H3Hero* GetVisitingHero() const;
		_H3API_ BOOL8 IsMageGuildBuilt(INT level) const;
		_H3API_ H3String GetNameAndType() const;
		_H3API_ INT32 GoldIncome(BOOL count_silo = FALSE) const;
		_H3API_ H3Resources& GetResourceSiloIncome() const;
		_H3API_ H3TownCreatureTypes& GetCreatureTypes() const;
		_H3API_ BOOL CanBeBuilt(eBuildings id) const;
		_H3API_ H3Resources TotalIncome() const;
	};
	
	struct H3SpecialBuildingCosts
	{
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

		// * each town has its own
		H3Resources cost[9];
	};

	struct H3NeutralBuildingCosts
	{
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
		// * same for all towns
		H3Resources cost[17];
	};

	struct H3DwellingBuildingCosts
	{
		// * each town has its own 2 * 7 levels
		// * unupgraded first, then upgraded
		H3Resources cost[2][7];
	};

	struct H3TownDependencies
	{
		enum eBuildingDependency : UINT64
		{
			NO_REQ                = 0,
			BLD_REQ_MAGE1         = 0x01,
			BLD_REQ_MAGE2         = 0x02,
			BLD_REQ_MAGE3         = 0x04,
			BLD_REQ_MAGE4         = 0x08,
			BLD_REQ_MAGE5         = 0x10,
			BLD_REQ_TAVERN        = 0x20,
			BLD_REQ_WHARF         = 0x40,
			BLD_REQ_FORT          = 0x80,
			BLD_REQ_CITADEL       = 0x100,
			BLD_REQ_CASTLE        = 0x200,
			BLD_REQ_VILLAGE_HALL  = 0x400,
			BLD_REQ_TOWN_HALL     = 0x800,
			BLD_REQ_CITY_HALL     = 0x1000,
			BLD_REQ_CAPITOL       = 0x2000,
			BLD_REQ_MARKET        = 0x4000,
			BLD_REQ_RESOURCE_SILO = 0x8000,
			BLD_REQ_BLACKSMITH    = 0x10000,
			BLD_REQ_SPEC17        = 0x20000,
			BLD_REQ_HORDE1        = 0x40000,
			BLD_REQ_HORDE1U       = 0x80000,
			BLD_REQ_WHARF2        = 0x100000,
			BLD_REQ_SPEC21        = 0x200000,
			BLD_REQ_SPEC22        = 0x400000,
			BLD_REQ_SPEC23        = 0x800000,
			BLD_REQ_HORDE2        = 0x1000000,
			BLD_REQ_HORDE2U       = 0x2000000,
			BLD_REQ_GRAIL         = 0x4000000,
			BLD_REQ_DECOR27       = 0x8000000,
			BLD_REQ_DECOR28       = 0x10000000,
			BLD_REQ_DECOR29       = 0x20000000,
			BLD_REQ_DWELL1        = 0x40000000,
			BLD_REQ_DWELL2        = 0x80000000,
			BLD_REQ_DWELL3        = 0x100000000,
			BLD_REQ_DWELL4        = 0x200000000,
			BLD_REQ_DWELL5        = 0x400000000,
			BLD_REQ_DWELL6        = 0x800000000,
			BLD_REQ_DWELL7        = 0x1000000000,
			BLD_REQ_DWELL1U       = 0x2000000000,
			BLD_REQ_DWELL2U       = 0x4000000000,
			BLD_REQ_DWELL3U       = 0x8000000000,
			BLD_REQ_DWELL4U       = 0x10000000000,
			BLD_REQ_DWELL5U       = 0x20000000000,
			BLD_REQ_DWELL6U       = 0x40000000000,
			BLD_REQ_DWELL7U       = 0x80000000000,
		};

	protected:
		UINT64 m_dependency[9][44];
	public:
		_H3API_ VOID Set(H3Town::eTown town, H3Town::eBuildings building, eBuildingDependency depend);
		_H3API_ VOID Add(H3Town::eTown town, H3Town::eBuildings building, eBuildingDependency depend);
		_H3API_ VOID Remove(H3Town::eTown town, H3Town::eBuildings building, eBuildingDependency depend);
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
		_H3API_ H3Hero* GetActiveHero();
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
		h3align _f_12[2];
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
		h3align _f_41;
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
		h3align _f_7;
	public:
		// * +8
		// * reference to object's DEF for drawing purposes
		UINT16 num;
	protected:
		h3align _f_A[2];
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

		_H3API_ H3ObjectDraw(UINT16 sprite, UINT8 tile_id, UINT8 layer);
	};

	// * university is an array of 4 sskills
	struct H3University
	{
		int sSkill[4];

		_H3API_ PINT begin();
		_H3API_ PINT end();
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
		_H3API_ H3University* GetUniversity();
		// * get real entrance (if any) of object on this tile
		_H3API_ H3MapItem* GetEntrance();
		_H3API_ BOOL IsEntrance() const;
		_H3API_ BOOL IsBlocked() const;
		_H3API_ BOOL CanDig() const;

		// * casts setup to relevant map item data

		_H3API_ MapMonster*         CastMonster();
		_H3API_ MapScholar*         CastScholar();
		_H3API_ MapScroll*          CastScroll();
		_H3API_ MapEvent*           CastEvent();
		_H3API_ MapTreasureChest*   CastTreasureChest();
		_H3API_ MapWarriorsTomb*    CastWarriorsTomb();
		_H3API_ MapTreeOfKnowledge* CastTreeKnowledge();
		_H3API_ MapCampfire*        CastCampfire();
		_H3API_ MapLeanTo*          CastLeanTo();
		_H3API_ MapWitchHut*        CastWitchHut();
		_H3API_ MapLearningStone*   CastLearningStone();
		_H3API_ MapWagon*           CastWagon();
		_H3API_ MapCorpse*          CastCorpse();
		_H3API_ MapMagicSpring*     CastMagicSpring();
		_H3API_ MapWaterMill*       CastWatermill();
		_H3API_ MapCreatureBank*    CastCreatureBank();
		_H3API_ MapPyramid*         CastPyramid();
		_H3API_ MapSwanPond*        CastSwanPond();
		_H3API_ MapMonolith*        CastMonolith();
		_H3API_ MapMysticGarden*    CastMysticGarden();
		_H3API_ MapWindmill*        CastWindmill();
		_H3API_ MapMine*            CastMine();
		_H3API_ MapShipyard*        CastShipyard();
		_H3API_ MapMagicShrine*     CastMagicShrine();
		_H3API_ MapUniversity*      CastUniversity();
		_H3API_ MapResource*        CastResource();
		_H3API_ MapSeaChest*        CastSeaChest();
		_H3API_ MapArtifact*        CastArtifact();
		_H3API_ MapGenerator*       CastGenerator();
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
			ArtPos_HEAD          = 0,
			ArtPos_SHOULDERS     = 1,
			ArtPos_NECK          = 2,
			ArtPos_RIGHT_HAND    = 3,
			ArtPos_LEFT_HAND     = 4,
			ArtPos_TORSO         = 5,
			ArtPos_RIGHT_RING    = 6,
			ArtPos_LEFT_RING     = 7,
			ArtPos_FEET          = 8,
			ArtPos_MISC_1        = 9,
			ArtPos_MISC_2        = 10,
			ArtPos_MISC_3        = 11,
			ArtPos_MISC_4        = 12,
			ArtPos_WAR_MACHINE_1 = 13,
			ArtPos_WAR_MACHINE_2 = 14,
			ArtPos_WAR_MACHINE_3 = 15, // first aid tent
			ArtPos_WAR_MACHINE_4 = 16,
			ArtPos_CATAPULT      = 17,
			ArtPos_SPELL_BOOK    = 18,
			ArtPos_MISC_5        = 19,
		};

		enum ArtifactType
		{
			ART_SPECIAL          = 1,
			ART_TREASURE         = 2,
			ART_MINOR            = 4,
			ART_MAJOR            = 8,
			ART_RELIC            = 16,
			ART_ALL              = 30 // never special!
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

		_H3API_ BOOL HasUpgradedStack();
		_H3API_ VOID SetupBank(int type, int level);
		_H3API_ VOID UpgradeStack(BOOL upg);
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
		h3align _f_5F;
	};

	// * CRBanks.txt converted in memory, overall bank state
	struct H3CreatureBankSetup
	{
		H3String name;
		H3CreatureBankState states[4];

		enum eCrBank
		{
			CYCLOPS_STOCPILE     = 0,
			DWARVEN_TREASURY     = 1,
			GRIFFIN_CONSERVATORY = 2,
			IMP_CACHE            = 3,
			MEDUA_STORES         = 4,
			NAGA_BANK            = 5,
			DRAGON_FLY_HIVE      = 6,
			SHIPWRECK            = 7,
			DERELICT_SHIP        = 8,
			CRYPT                = 9,
			DRAGON_UTOPIA        = 10,
		};
	};

	// * town wall elements
	struct H3ValidCatapultTargets
	{
		INT32 fort_element_id;
		h3unk f_04[8];

		enum FORT_ELEMENTS {
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
			AIR   = 1,
			FIRE  = 2,
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
		
		_H3API_ INT32 GetBaseEffect(INT32 level, INT32 spellPower);
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
		struct H3LoadedDEF* def;
		// * +4
		H3ObstacleInfo* info;
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
		LPCSTR soundName;
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

		_H3API_ LPCSTR GetCreatureName(INT32 count);
		_H3API_ H3Resources UpgradeCost(H3CreatureInformation* upg, INT32 count);
	};

	// * a substructure of H3CombatMonster related to spells
	struct H3CombatMonsterSpellsData
	{
		INT32 bless_damage;            // 0x458
		INT32 curse_damage;            // 0x45C
		INT32 anti_magic;              // 0x460
		INT32 bloodlust_effect;        // 0x464
		INT32 precision_effect;        // 0x468
		INT32 weakness_effect;         // 0x46C
		INT32 stone_skin_effect;       // 0x470
		INT32 unknown13;               // 0x474
		INT32 prayer_effect;           // 0x478
		INT32 mirth_effect;            // 0x47C
		INT32 sorrow_effect;           // 0x480
		INT32 fortune_effect;          // 0x484
		INT32 misfortune_effect;       // 0x488
		INT32 slayer_type;             // 0x48C - called KING_1/2/3
		INT32 unknown14;               // 0x490 - Max traversed cells before hitting?
		INT32 counterstrike_effect;    // 0x494
		float frenzyMultiplier;        // 0x498
		INT32 blind_effect;            // 0x49C - for calculating damage retaliation damage?
		float fire_shield_effect;      // 0x4A0
		INT32 unknown16;               // 0x4A4
		float protection_air_effect;   // 0x4A8 - in % as below
		float protection_fire_effect;  // 0x4AC
		float protection_water_effect; // 0x4B0
		float protection_earth_effect; // 0x4B4
		INT32 shield_effect;           // 0x4B8
		INT32 air_shield_effect;       // 0x4BC
		INT8 blinded;                  // 0x4C0 - to reduce damage?
		INT8 paralyzed;                // 0x4C1 - to reduce damage?
		INT8 unknown17[2];             // 0x4C2-0x4C3
		INT32 forgetfulness_level;     // 0x4C4
		float slow_effect;             // 0x4C8 - float
		INT32 haste_effect;            // 0x4CC - value added/removed
		INT32 disease_attack_effect;   // 0x4D0
		INT32 disease_defense_effect;  // 0x4D4
		INT32 unknown18[3];            // 0x4D8-0x4E0
		INT32 magic_mirror_effect;     // 0x4E4
		INT32 morale;                  // +4E8
		INT32 luck;                    // +4EC
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

		INT32 missileFrameAngles[12]; // from high to low (90 to -90)
		INT32 troopCountLocationOffset;
		INT32 attackClimaxFrame;
		INT32 timeBetweenFidgets;
		INT32 walkAnimationTime;
		INT32 attackAnimationTime;
		INT32 flightAnimationTime;
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
		H3LoadedDEF* def;
	protected:
		// * +168
		H3LoadedDEF* shootingDef;
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
		_H3API_ LPCSTR GetCreatureName();
		// * returns second square if creature occupies 2 squares
		_H3API_ INT32 GetSecondSquare();
		// * returns actual speed of creature
		_H3API_ INT32 GetStackSpeed();
		_H3API_ BOOL IsDone();
		_H3API_ BOOL IsClone();
		_H3API_ BOOL IsSiege();
		_H3API_ BOOL IsSummon();
		_H3API_ BOOL HadMorale();
		_H3API_ BOOL IsWaiting();
		_H3API_ BOOL HasMoved();
		// * index 0 ~ 41
		_H3API_ INT32 Index();
		// * show creature information dialog
		_H3API_ VOID ShowStatsDialog(BOOL RightClick);
		// * Checks if hypnotized
		_H3API_ INT32 GetSide();
		// * Checks if hypnotized
		_H3API_ H3Hero* GetOwner();
		// * the bonus/decreased effect on a spell from targeting a creature
		_H3API_ INT32 GetProtectiveSpellEffect(INT32 damage, INT32 spellID);
		// * odds of magic resisting
		_H3API_ INT32 MagicMirrorEffect();
	};

	struct H3PrimarySkills
	{
		INT8 attack;
		INT8 defense;
		INT8 spellPower;
		INT8 knowledge;

		_H3API_ PINT8 begin();
		_H3API_ PINT8 end();
	};

	struct H3SecondarySkill
	{
		INT type;
		INT level; // 0 ~ 3
	};

	struct H3SecondarySkillInfo
	{
		LPCSTR name;
		LPCSTR description[3];
	};

	struct H3PandorasBox
	{
		// * +0
		H3String message;
		// * +10
		BOOL8 customizedGuards;
		h3unk _f_11[3];
		// * +14
		H3Army guardians;
		// * +4C
		BOOL8 hasMessageOrGuardians;
		h3align _f_4d[3];
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
		H3Vector<H3SecondarySkill> sSkills;
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
		INT32* first;
		INT32* last;
		INT32* capacity;
	public:
		_H3API_ INT32 Count();
		_H3API_ INT32 operator[](INT32 index);
		_H3API_ INT32* begin();
		_H3API_ INT32* end();
	};

	// * quest in memory, used for seer's hut and quest guards
	struct H3Quest
	{
		enum eQuestType
		{
			QT_None            = 0,
			QT_ExperienceLevel = 1,
			QT_PrimarySkill    = 2,
			QT_DefeatHero      = 3,
			QT_DefeatMonster   = 4,
			QT_BringArtifacts  = 5,
			QT_BringCreatures  = 6,
			QT_BringResources  = 7,
			QT_BeHero          = 8,
			QT_BePlayer        = 9,
		};

		// * +0
		// * 0x641798 + questType * 0x3C
		//
		// vt0	Constructor
		// vt1	AI value
		// vt2	Condition is met
		// vt3	Remove from hero
		// vt4	Show Message1
		// vt5	Show Message2
		// vt6	Print objective number
		// vt7	Get custom text
		// vt8
		// vt9
		// vt10
		// vt11
		// vt12
		// vt13
		// vt14
		h3func* vTable;
		// * +4
		// * 0 = quest guard, 1 = seer hut
		BOOL hasReward;
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
		union QuestData
		{
			INT32 achieveLevel;						// achieve level
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
				UINT packedCoords;
				INT32 displayCreatureType;
				INT32 player;
			} killMonster;					// kill a monster in certain position on the map
			H3QuestVector getArtifacts;		// bring artifacts
			struct
			{
				H3QuestVector number;
				H3QuestVector type;
			} getCreatures;					// bring creatures
			INT getResources[7];			// bring resources
			INT32 beHero;					// visit as a certain hero
			INT32 bePlayer;					// visit as a certain player			
		} data;

		_H3API_ eQuestType GetQuestType() const;
		_H3API_ H3Resources& GetResources();
	};

	// * quest guard is a quest plus a byte to show who visited
	struct H3QuestGuard
	{
		H3Quest* quest;
		BYTE playersVisited;

		_H3API_ H3Quest::eQuestType QuestType() const;
	};

	// * seer hut is a quest guard plus some information about reward
	struct H3SeerHut
	{
		enum eSeerReward
		{
			SR_None           = 0,
			SR_Experience     = 1,
			SR_SpellPoints    = 2,
			SR_Morale         = 3,
			SR_Luck           = 4,
			SR_Resource       = 5,
			SR_PrimarySkill   = 6,
			SR_SecondarySkill = 7,
			SR_Artifact       = 8,
			SR_Spell          = 9,
			SR_Creature       = 10,
		};
		// * +0
		H3Quest* quest;
		// * +4
		BYTE playersVisited;
		// * +5
		INT32 rewardType;
		// * +9
		INT32 rewardValue;
		// * +D
		INT32 rewardValue2;
		// * +11
		BYTE seerNameId;
		// * +12
		h3unk _f_12;

		_H3API_ WORD CreatureCount() const;
		_H3API_ INT8 Luck() const;
		_H3API_ INT8 Morale() const;
		_H3API_ INT32 Primary() const;
		_H3API_ INT8 PrimaryCount() const;

		_H3API_ H3Quest::eQuestType QuestType() const;
	};

	struct H3QuestText
	{
		struct
		{
		private:
			H3String m_unused[5];
		public:
			H3String text[44];
		private:
			H3String m_unused2;
		public:
			H3String deserted;
			H3String deadline;
		}variants[3];
	};

	// * if a mapartifact has a custom setup, this is the referenced data
	struct H3MapArtifact
	{
		// * +0
		H3String message;
		// * +10
		BOOL8 isGuarded;
		h3unk _f_11[3];
		// * +14
		H3Army guardians;
	};

	// * if a mapresource has a custom setup, this is the referenced data
	struct H3MapResource : public H3MapArtifact
	{
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
		h3align _f_2F;
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
		H3Vector<H3ObjectAttributes> objectAttributes; // +00	// +01FB70
		H3Vector<H3ObjectDetails> objectDetails;	   // +10
		H3Vector<H3LoadedDEF*> defs;			       // +20 ???
		H3Vector<H3MapArtifact> artifactResource;      // +30
		H3Vector<H3Monster> monsters;	               // +40
		H3Vector<H3PandorasBox> pandoraEvents;         // +50	// +01FBC0
		H3Vector<H3SeerHut> seerHuts;	               // +60	// +01FBD0
		H3Vector<H3QuestGuard> questGuards;	           // +70	// +01FBE0
		H3Vector<H3GlobalEvent> globalEvents;	       // +80
		H3Vector<H3CastleEvent> castleEvents;	       // +90
	protected:
		H3Vector<h3unk*> unkA0;                        // +A0
	public:
		H3Vector<H3Quest*> quests;                     // +B0
	protected:
		H3Vector<UINT32> unkC0;                        // +C0
	public:
		H3MapItem* mapitems;                           // +D0	// +1FC40
		INT32 mapSize;			                       // +D4	// +1FC44
		INT8 SubterraneanLevel;	                       // +D8	// +1FC48
	protected:
		h3unk _f_D9[3];			                       // +D9	// +1FC49~B
	public:
		H3Vector<H3ObjectAttributes> objectLists[232];

		_H3API_ H3MapItem* GetMapItem(int x, int y, int z);
		_H3API_ VOID DrawItem(H3MapItem* mitem, H3ObjectDraw* draw);
		_H3API_ VOID AddObjectAttribute(H3ObjectAttributes* oa);
		_H3API_ H3Point GetCoordinates(H3MapItem* item);
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
		H3Vector<h3unk*> CrossoverHeroes;
		char SomeCrossoverArrays_ref;
		h3unk _f_4D[3];
		int SomeCrossoverArrays;
		h3unk _f_54[4];
		h3unk _f_58[4];
		H3Vector<h3unk*> CampaignMapInfo;
		h3unk _f_6C;
		h3unk _f_6D[3];
		VOID* SomeCrossoverInfoStructs;
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
		BOOL8 zoneControl; // does not exist in Demo
	};

	// from WoG source
	struct H3PlayersInfo
	{
		h3unk _f_000[8];
		INT8  handicap[8];
		INT32 townType[8];
		h3unk _f_030[8];
		INT8  difficulty;
		CHAR  filename[251];
		CHAR  saveDirectory[100];
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
		// * used to retrieve name
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
		H3MapItem* item; // 7
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
		H3Hero* hero;
		H3Army* army;
		H3Hero* opponent;
		BOOL turrets;
		h3unk _f_31;
		INT16 turretsLevel;

		_H3API_ VOID DeleteCreatures();
	};

	struct H3AICombatInfo
	{
		// * +0
		INT heroAttack;
		// * +4
		INT heroDefence;		
		h3unk _f_08[4];
		// * +C
		INT damage[4];
		// * +1C
		INT moveType;
		// * +20
		INT thisSide;
		// * +24
		INT enemySide;		
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
		_H3API_ UINT8 GetX();
		_H3API_ UINT8 GetY();
		_H3API_ UINT8 GetZ();
		_H3API_ BOOL ZoneControlled();
		_H3API_ H3MapItem* GetMapItem();
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
		struct H3LoadedDEF* def;
	protected:
		h3unk _f_04[104];
	public:
		H3Army* army; // +6C
	protected:
		h3unk _f_70[4];
	public:
		H3Hero* hero; // +74
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
		H3TileMovement** movement_info;
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
		_H3API_ H3TileMovement* GetMovementInfo(UINT32 mixed_position);
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
		H3Vector<h3unk*> _f_4E7AC;
		H3Vector<h3unk*> _f_4E7BC;
		h3unk _f_4E7CC[4];
	public: // functions

		_H3API_ H3MapItem* GetMapItem(UINT32 mixedPosition);
		_H3API_ H3Player* GetPlayer();
		_H3API_ INT32 GetPlayerID();
		_H3API_ H3Hero* GetHero(INT32 id);
		_H3API_ VOID ResetRandomArtifacts();
		_H3API_ INT32 GetRandomArtifactOfLevel(INT32 level);
		_H3API_ VOID SaveGame(LPCSTR save_name);
		_H3API_ VOID PlaceObjectOnMap(int x, int y, int z, int type, int subtype, int setup = -1);
		_H3API_ VOID RefreshMapItemAppearrance(H3MapItem* mi);
		_H3API_ H3Point GetCoordinates(H3MapItem* item);
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

		H3Manager* parent;
		H3Manager* child;
		h3unk _f_0C[4];
		INT z_order;
		CHAR name[28]; // 0x14
		INT32 nameEnd; // 0x30
		h3unk _f_34[4];
	public:
		_H3API_ VOID SetPreviousManager(H3Manager* prev);
		_H3API_ VOID SetNextManager(H3Manager* next);
	};

	// * the manager of managers
	struct H3Executive
	{
		H3Manager* first_mgr;
		H3Manager* last_mgr;
		H3Manager* active_mgr;
		h3unk _f_0C[4];

		_H3API_ VOID RemoveManager(H3Manager* mgr);
		_H3API_ INT AddManager(H3Manager* mgr, int order);
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
		H3LoadedDEF* cursorDef;
		h3unk _f_58[16];
		BOOL cursorHidden;
		h3unk _f_6C[12];
		RTL_CRITICAL_SECTION criticalSection; // 0x78
	public:
		enum H3MouseCursorType : INT32
		{
			Cursor_Default   = 0,
			Cursor_Adventure = 1,
			Cursor_Combat    = 2,
			Cursor_Spell     = 3,
			Cursor_Artifact  = 4,
		};

		enum H3MouseAdventureMapCursorType
		{
			AMC_ArrowPointer         = 0,
			AMC_Busy_Wait            = 1,
			AMC_Hero                 = 2,
			AMC_Town                 = 3,
			AMC_Horse                = 4,
			AMC_Attack               = 5,
			AMC_Boat                 = 6,
			AMC_Anchor               = 7,
			AMC_Hero_Meeting         = 8,
			AMC_Rearing_Horse        = 9,
			AMC_Horse2               = 10,
			AMC_Attack2              = 11,
			AMC_Boat2                = 12,
			AMC_Anchor2              = 13,
			AMC_Hero_Meeting2        = 14,
			AMC_Rearing_Horse2       = 15,
			AMC_Horse3               = 16,
			AMC_Attack3              = 17,
			AMC_Boat3                = 18,
			AMC_Anchor3              = 19,
			AMC_Hero_Meeting3        = 20,
			AMC_Rearing_Horse3       = 21,
			AMC_Horse4               = 22,
			AMC_Attack4              = 23,
			AMC_Boat4                = 24,
			AMC_Anchor4              = 25,
			AMC_Hero_Meeting4        = 26,
			AMC_Rearing_Horse4       = 27,
			AMC_Boat_1               = 28,
			AMC_Boat_2               = 29,
			AMC_Boat_3               = 30,
			AMC_Boat_4               = 31,
			AMC_Map_Scroll_North     = 32,
			AMC_Map_Scroll_Northeast = 33,
			AMC_Map_Scroll_East      = 34,
			AMC_Map_Scroll_Southeast = 35,
			AMC_Map_Scroll_South     = 36,
			AMC_Map_Scroll_Southwest = 37,
			AMC_Map_Scroll_West      = 38,
			AMC_Map_Scroll_Northwest = 39,
			AMC_Arrow_Pointer        = 40,
			AMC_Dimension_Door       = 41,
			AMC_Scuttle_Boat         = 42,

		};

		enum H3MouseBattleFieldCursorType
		{
			BFC_Null             = 0,
			BFC_Move             = 1,
			BFC_Fly              = 2,
			BFC_Shooting         = 3,
			BFC_Hero             = 4,
			BFC_Question_Mark    = 5,
			BFC_Arrow_Pointer    = 6,
			BFC_Attack_Northeast = 7,
			BFC_Attack_East      = 8,
			BFC_Attack_Southeast = 9,
			BFC_Attack_Southwest = 10,
			BFC_Attack_West      = 11,
			BFC_Attack_Northwest = 12,
			BFC_Attack_North     = 13,
			BFC_Attack_South     = 14,
			BFC_Half_Damage      = 15,
			BFC_Attack_Wall      = 16,
			BFC_Heal             = 17,
			BFC_Sacrifice        = 18,
			BFC_Teleport         = 19,

		};

		_H3API_ VOID TurnOn();
		_H3API_ VOID TurnOff();
		_H3API_ INT32 GetType() const;
		_H3API_ INT32 GetFrame() const;
		_H3API_ VOID SetCursor(INT32 type, INT32 frame);
		_H3API_ VOID DefaultCursor();
		_H3API_ VOID SetArtifactCursor(INT32 art_id);
	};

	// * named heroWindowManager in H3, abbreviated
	// * in charge of drawing and dialogs
	struct H3WindowManager : public H3Manager
	{
	protected:
		UINT32 resultItemID; // 0x38
		h3unk _f_3C[4];
		UINT32 drawBuffer; // 0x40
		struct H3LoadedPCX16* screenPcx16;
		struct H3Dlg* firstDlg;
		struct H3Dlg* lastDlg;
		h3unk _f_58[8];
	public:

		enum H3ClickIDs
		{
			H3ID_OK     = 30725,
			H3ID_CANCEL = 30726
		};

		VOID H3Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy);
		UINT32 ClickedItemID() const;
		BOOL ClickedOK() const;
		BOOL ClickedCancel() const;
		struct H3LoadedPCX16* GetDrawBuffer();
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
		_H3API_ VOID ClickSound(); // modeled after sub_00456540
		_H3API_ VOID PlaySound(struct H3WavFile* wav);
		_H3API_ VOID PlaySound(LPCSTR wavName);
	};

	// * in charge of the adventure map
	struct H3AdventureManager : public H3Manager
	{
	protected:
		h3unk _f_038[12];
	public:
		// * +44
		struct H3Dlg* dlg;
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
		H3MainSetup* map;
	protected:
		// * +60
		H3LoadedDEF* terrainDEF[10];
		h3unk _f_088[4];
		// * +8C
		H3LoadedDEF* riverDEF[4];
		h3unk _f_09C[4];
		// * +A0
		H3LoadedDEF* roadDEF[3];
		// * +AC
		H3LoadedDEF* edgDEF;
		// * +B0
		H3LoadedDEF* adagDEF;
		// * +B4
		H3LoadedDEF* agemulDEF;
		// * +B8
		H3LoadedDEF* agemurDEF;
		// * +BC
		H3LoadedDEF* agemllDEF;
		// * +C0
		H3LoadedDEF* agemlrDEF;
		// * +C4
		H3LoadedDEF* tshrcDEF;
		// * +C8
		H3LoadedDEF* radarDEF;
		// * +CC
		H3LoadedDEF* tshreDEF;
		// * +D0
		H3Vector<H3LoadedDEF*> defs;
		// * +E0
		H3LoadedDEF* attackDEF;
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
		H3LoadedDEF* heroDEF[18];
		// * +154
		H3LoadedDEF* boatDEF[3];
		// * +160
		H3LoadedDEF* boatMovementDEF[3];
		// * +16C
		H3LoadedDEF* heroFlags_00[8];
		// * +18C
		H3LoadedDEF* heroFlags_01[8];
		// * +1AC
		H3LoadedDEF* heroFlags_02[8];
		// * +1CC
		H3LoadedDEF* heroFlags_03[8];
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

		_H3API_ H3MapItem* GetMapItem();
		_H3API_ H3MapItem* GetMapItem(int mixedPos);
		_H3API_ H3MapItem* GetMapItem(int x, int y, int z);
		_H3API_ UINT8 GetX();
		_H3API_ UINT8 GetY();
		_H3API_ UINT8 GetZ();
		_H3API_ VOID FullUpdate();
		_H3API_ VOID MobilizeHero();
		_H3API_ VOID DemobilizeHero();
		_H3API_ VOID MovementCalculationsMouse();
		_H3API_ VOID MovementCalculations(UINT32 mixedPosition);
		_H3API_ VOID MakeHeroPath();
		_H3API_ VOID ShowCoordinates(INT32 x, INT32 y, INT8 z);
		_H3API_ INT SimulateMouseOver(INT x, INT y);
		_H3API_ INT SimulateMouseOver(POINT& p);
		_H3API_ CHAR UpdateHintMessage();
		_H3API_ H3Point GetCoordinates(H3MapItem* item);
	};

	// * trading between two armies
	struct H3SwapManager : public H3Manager // size 0x68
	{
	protected:
		h3unk _f_38[8];
	public:
		H3Hero* hero[2]; // similar to https://github.com/potmdehex/homm3tools/blob/master/hd_edition/hde_mod/hde/structures/swapmgr.h
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
		H3Town* town;
	protected:
		h3unk _f_3C[224];
	public:
		// * +11C
		// * ???
		H3CreatureExchange* top;
		// * +120
		// * this gets copied to recipientPage during mouse hover, however if you click fast enough the update isn't done
		H3CreatureExchange* bottom;
		// * +12C
		// * source page
		H3CreatureExchange* source;
		// * +130
		// * number of source stack
		INT32 sourcePageStack;
		// * +134
		// * recipient page
		H3CreatureExchange* recipientPage;
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
		_H3API_ VOID Draw();
		_H3API_ VOID RefreshScreen();
	};

	// * keyboard and mouse input
	struct H3InputManager : public H3Manager
	{
		// * modifies equivalent WM_ messages into H3 messages
		enum MessageType
		{
			MT_KEYDOWN = 1,        // 0x100
			MT_KEYUP = 2,          // 0x101
			MT_MOUSEMOVE = 4,      // 0x200
			MT_LBUTTONDOWN = 8,    // 0x201
			MT_LBUTTONUP = 16,     // 0x202
			MT_LBUTTONDBLCLK = 8,  // 0x203
			MT_RBUTTONDOWN = 32,   // 0x204
			MT_RBUTTONUP = 64,     // 0x205
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

		_H3API_ InputMessages& GetCurrentMessage();
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

		_H3API_ H3CombatMonster* GetMonster();
	};

	// * from wog source
	// * size 24h
	struct TownTowerLoaded
	{
		INT32 crType2Shot;
		struct H3LoadedDEF* monDefLoaded;
		struct H3LoadedDEF* shotDefLoaded;
		INT32 creatureX;
		INT32 creatureY;
		INT32 orientation;
		INT32 defGroup;
		struct H3DefFrame* frame;
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
		H3LoadedPCX16* drawBuffer;
	protected:
		h3unk _f_53B4[4];
	public:
		// * +53B8
		BOOL doNotDrawShade;
		// * +53BC
		// * H3MapItem where combat is taking place
		H3MapItem* mapitem;
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
		H3Town* town;
		// * +53CC
		// * hero structures from each side
		H3Hero* hero[2];
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
		H3LoadedDEF* heroDefLoaded[2];
		// * +540C
		H3LoadedDEF* heroFlagLoaded[2];
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
		H3Army* army[2];
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
		H3CombatMonster* activeStack;
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
		struct H3CombatDlg* dlg;
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
		struct H3LoadedPCX* CCellGrdPcx;
		// * +13FF8
		// * pcx to shade in blue using cheat menu
		struct H3LoadedPCX* CCellShdPcx;
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
		_H3API_ VOID SimulateMouseAtHex(int hex_id);
		_H3API_ BOOL8 CanCastSpellAtCoord(int spell_id, int spell_expertise, int coordinates);
		_H3API_ VOID WinBattle();
		_H3API_ VOID LoadSpell(INT32 spell_id);
		_H3API_ VOID CastSpell(int spell_id, int hex_ix, int cast_type_012, int hex2_ix, int skill_level, int spell_power);
		_H3API_ H3CombatMonster* GetResurrectionTarget(INT32 coordinate);
		_H3API_ H3CombatMonster* GetAnimateDeadTarget(INT32 coordinate);
		_H3API_ int NextCreatureToMove();
		_H3API_ BOOL8 IsHiddenBattle();
		_H3API_ BOOL8 IsBattleOver();
		_H3API_ VOID Refresh();
		_H3API_ VOID Refresh(BOOL redrawScreen, INT timeDelay, BOOL redrawBackground);
		_H3API_ VOID RefreshCreatures();
		_H3API_ VOID ShadeSquare(int index);
		_H3API_ BOOL8 IsHumanTurn();
		_H3API_ VOID AddStatusMessage(LPCSTR message, BOOL permanent = TRUE);
	};

	// * these are internal to H3API to avoid conflicts
	namespace H3Internal
	{
		_H3API_ H3MouseManager*         MouseManager();
		_H3API_ H3WindowManager*        WindowManager();
		_H3API_ H3Executive*            Executive();
		_H3API_ H3Main*                 Main();
		_H3API_ H3CombatManager*        CombatManager();
		_H3API_ H3TownManager*          TownManager();
		_H3API_ H3SoundManager*         SoundManager();
		_H3API_ H3InputManager*         InputManager();
		_H3API_ H3AdventureManager*     AdventureManager();
		_H3API_ H3MovementManager*      MovementManager();
		_H3API_ H3GlobalObjectSettings* GlobalObjectSettings();
		_H3API_ H3Spell*                Spell();
		_H3API_ H3CreatureBankSetup*    CreatureBankSetup();
		_H3API_ H3ValidCatapultTargets* ValidCatapultTargets();
		_H3API_ H3ArtifactSetup*        ArtifactSetup();
		_H3API_ H3CreatureInformation*  CreatureInformation();
		_H3API_ H3ObstacleInfo*         ObstacleInfo();
		_H3API_ H3Hero*                 DialogHero();
		_H3API_ H3TurnTimer*            TurnTimer();
		_H3API_ H3HeroSpecialty*        HeroSpecialty();
		_H3API_ H3TownCreatureTypes*    TownCreatureTypes();
	}

#pragma pack(pop)
}

#endif /* #define _H3STRUCTURES_HPP_ */