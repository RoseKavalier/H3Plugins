//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STRUCTURES_HPP_
#define _H3STRUCTURES_HPP_

#include "../H3_Base.hpp"
#include "../H3_Constants.hpp"
#include "../H3_Vector.hpp"
#include "../H3_String.hpp"
#include "../H3_MapItems.hpp"

namespace h3
{
	// * forward declarations
	_H3API_DECLARE_(H3NetworkData);
	_H3API_DECLARE_(H3ZStream);
	_H3API_DECLARE_(H3Position);
	_H3API_DECLARE_(H3IndexVector);
	_H3API_DECLARE_(H3Artifact);
	_H3API_DECLARE_(H3AnimationSpeed);
	_H3API_DECLARE_(H3Resources);
	_H3API_DECLARE_(H3Army);
	_H3API_DECLARE_(H3SetupHero);
	_H3API_DECLARE_(H3HeroInfo);
	_H3API_DECLARE_(H3HeroSpecialty);
	_H3API_DECLARE_(H3HeroFlags);
	_H3API_DECLARE_(H3Hero);
	_H3API_DECLARE_(H3Date);
	_H3API_DECLARE_(H3Player);
	_H3API_DECLARE_(H3TownCreatureTypes);
	_H3API_DECLARE_(H3Town);
	_H3API_DECLARE_(H3SpecialBuildingCosts);
	_H3API_DECLARE_(H3NeutralBuildingCosts);
	_H3API_DECLARE_(H3DwellingBuildingCosts);
	_H3API_DECLARE_(H3TownDependencies);
	_H3API_DECLARE_(H3ComboArtifactSetup);
	_H3API_DECLARE_(H3CreatureBank);
	_H3API_DECLARE_(H3CreatureBankState);
	_H3API_DECLARE_(H3CreatureBankSetup);
	_H3API_DECLARE_(H3ValidCatapultTargets);
	_H3API_DECLARE_(H3WallSection);
	_H3API_DECLARE_(H3Spell);
	_H3API_DECLARE_(H3ObstacleInfo);
	_H3API_DECLARE_(H3Obstacle);
	_H3API_DECLARE_(H3CreatureFlags);
	_H3API_DECLARE_(H3CreatureInformation);
	_H3API_DECLARE_(H3CombatMonsterSpellsData);
	_H3API_DECLARE_(H3MonsterAnimation);
	_H3API_DECLARE_(H3CombatMonster);
	_H3API_DECLARE_(H3PrimarySkills);
	_H3API_DECLARE_(H3SecondarySkill);
	_H3API_DECLARE_(H3SecondarySkillInfo);
	_H3API_DECLARE_(H3PandorasBox);
	_H3API_DECLARE_(H3Event);
	_H3API_DECLARE_(H3QuestVector);
	_H3API_DECLARE_(H3Quest);
	_H3API_DECLARE_(H3QuestGuard);
	_H3API_DECLARE_(H3SeerHut);
	_H3API_DECLARE_(H3QuestText);
	_H3API_DECLARE_(H3SpellbookText);
	_H3API_DECLARE_(H3MapArtifact);
	_H3API_DECLARE_(H3MapResource);
	_H3API_DECLARE_(H3Monster);
	_H3API_DECLARE_(H3GlobalEvent);
	_H3API_DECLARE_(H3CastleEvent);
	_H3API_DECLARE_(H3MainSetup);
	_H3API_DECLARE_(H3CampaignInfo);
	_H3API_DECLARE_(H3ArtifactMerchant);
	_H3API_DECLARE_(H3BlackMarket);
	_H3API_DECLARE_(H3Grail);
	_H3API_DECLARE_(H3TileVision);
	_H3API_DECLARE_(H3PlayersInfo);
	_H3API_DECLARE_(H3PlayerUnk);
	_H3API_DECLARE_(H3MapInfo);
	_H3API_DECLARE_(H3Mine);
	_H3API_DECLARE_(H3Signpost);
	_H3API_DECLARE_(H3Dwelling);
	_H3API_DECLARE_(H3Garrison);
	_H3API_DECLARE_(H3Boat);
	_H3API_DECLARE_(H3FastBattleCreature);
	_H3API_DECLARE_(H3AiFastBattle);
	_H3API_DECLARE_(H3AICombatInfo);
	_H3API_DECLARE_(H3GlobalObjectSettings);
	_H3API_DECLARE_(H3TileMovement);
	_H3API_DECLARE_(H3TurnTimer);
	_H3API_DECLARE_(H3CreatureExchange);
	_H3API_DECLARE_(H3MovementManager);
	_H3API_DECLARE_(H3Main);
	_H3API_DECLARE_(H3Manager);
	_H3API_DECLARE_(H3ExecutiveMgr);
	_H3API_DECLARE_(H3MouseManager);
	_H3API_DECLARE_(H3WindowManager);
	_H3API_DECLARE_(H3SoundManager);
	_H3API_DECLARE_(H3AdventureManager);
	_H3API_DECLARE_(H3SwapManager);
	_H3API_DECLARE_(H3TownManager);
	_H3API_DECLARE_(H3InputManager);
	_H3API_DECLARE_(H3CombatSquare);
	_H3API_DECLARE_(TownTowerLoaded);
	_H3API_DECLARE_(H3AdjacentSquares);
	_H3API_DECLARE_(H3CombatManager);

	// * forward declarations from other submodules
	struct H3LoadedDef;
	struct H3WavFile;
	struct H3LoadedPcx;

#pragma pack(push, 4)

	struct H3NetworkData
	{
		// * +0
		INT32 recipientId; // -1 means everyone
		h3unk32 _f_04;
		// * +8
		INT msgId;
		// * +C
		INT bufferSize; // sizeof(*this) + extra size of H3NetworkData
		INT     _f_10;
		// * +14
		INT shortData;
		// * more fields can be added here if more information is needed to be sent

		_H3API_ H3NetworkData(int recipient_id, int msg_id, int data);
		_H3API_ INT32 SendData();
	};
	_H3API_ASSERT_SIZE_(H3NetworkData, 0x18);

	template <typename T>
	struct H3NetworkDataExtra : H3NetworkData
	{
		H3NetworkDataExtra(int recipient_id, int msg_id, int data, const T& extra_data);
		T extraData;
	};

	// * the save/load structure used by H3
	// * that also handles gzip inflat/deflate
	// * gz_state or similar from zlib
	struct H3ZStream
	{
	protected:
		struct
		{
			h3func destroy; // [00]
			h3func read;    // [04]
			h3func write;   // [08]
		}*vTable;

		h3unk _f_04[156]; // guess based on gz_state
	public:
		_H3API_ BOOL Save(PVOID data, UINT data_size);
		_H3API_ BOOL Load(PVOID data, UINT data_size);

		template<typename T>
		inline BOOL Read(T& data, UINT data_size = sizeof(T));
		template<typename T>
		inline BOOL Write(T& data, UINT data_size = sizeof(T));

		_H3API_ H3ZStream(LPCSTR file_name, LPCSTR mode);
		_H3API_ ~H3ZStream();
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
		_H3API_ UINT GetX();
		// * returns y from coordinates
		_H3API_ UINT GetY();
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
		_H3API_ static VOID UnpackXYZ(UINT coord, INT& x, INT& y, INT& z);
		// * Can be used on the stack safely to unpack X
		_H3API_ static UINT UnpackX(UINT coord);
		// * Can be used on the stack safely to unpack Y
		_H3API_ static UINT UnpackY(UINT coord);
		// * Can be used on the stack safely to unpack Z
		_H3API_ static UINT8 UnpackZ(UINT coord);
	};

	// * to choose a random index within a range, without repeating results
	struct H3IndexVector
	{
	protected:
		INT    m_minimum;
		INT    m_availableCount;
		BOOL8  m_init; // essentially H3Vector<BOOL8>
		BOOL8* m_begin;
		BOOL8* m_end;
		BOOL8* m_capacity;
	public:
		_H3API_ H3IndexVector(INT min_num, INT max_num);
		_H3API_ ~H3IndexVector();
		// * never returns the same value
		// * returns InvalidIndex() if there are no non-selected indexes
		_H3API_ INT ChooseRandom();
		// * returns m_minimum - 1
		_H3API_ INT InvalidIndex();
	};
	_H3API_ASSERT_SIZE_(H3IndexVector, 0x18);

	// * artifacts as they appear on H3Hero structure
	// * also used for artifact enum
	struct H3Artifact
	{
		typedef NH3Artifacts::eArtifacts     eArtifacts;
		typedef NH3Artifacts::eArtifactSlots eArtifactSlots;

		INT32 id; /**< @brief [00] 0..140 eArtifacts*/
		INT32 subtype; /**< @brief [04] spell id for spell scrolls, otherwise -1*/
	};

	// * a reference to the 3 animation speeds of H3
	struct H3AnimationSpeed
	{
		FLOAT delay[3];
	};

	// * An "array" representing the 7 resources
	struct H3Resources
	{
		typedef NH3Resources::eResourceType eType;

		union
		{
			struct
			{
				INT32 wood;
				INT32 mercury;
				INT32 ore;
				INT32 sulfur;
				INT32 crystal;
				INT32 gems;
				INT32 gold;
			};
			INT32 asArray[7];
		};


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
		// * Number of non-zero resources
		_H3API_ INT Count() const;
		_H3API_ PINT begin();
		_H3API_ PINT end();
		_H3API_ PINT cbegin() const;
		_H3API_ PINT cend() const;
		// * checks for overflow
		_H3API_ H3Resources& operator+=(const H3Resources& other);
		// * checks for overflow
		_H3API_ H3Resources& operator-=(const H3Resources& other);
		// * does not check for overflow
		_H3API_ H3Resources& operator=(const H3Resources& other);
		_H3API_ BOOL operator>=(const H3Resources& other) const;
		_H3API_ BOOL operator>(const H3Resources& other) const;
		_H3API_ BOOL operator<(const H3Resources& other) const;
		_H3API_ BOOL operator<=(const H3Resources& other) const;
		_H3API_ INT& operator[](int index);
	};

	// * The arrangement of 7 creatures on various H3 structures
	struct H3Army
	{
		struct iterator
		{
		protected:
			INT32* m_type;
		public:
			_H3API_ iterator(INT32* type);
			_H3API_ iterator& operator*();
			_H3API_ iterator& operator++();
			_H3API_ iterator operator++(int);
			_H3API_ BOOL operator==(const iterator& other);
			_H3API_ BOOL operator!=(const iterator& other);
			_H3API_ BOOL operator!() const;

			_H3API_ INT32& Type();
			_H3API_ INT32& Count();
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
		_H3API_ INT32 NumberAlignments(INT8(&towns)[9]);
		// * AI value total for army
		_H3API_ INT32 GetArmyValue();
		_H3API_ iterator begin();
		_H3API_ iterator end();
		_H3API_ H3Army& operator=(const H3Army& other);
		_H3API_ iterator operator[](UINT index);
	};
#pragma pack(pop)

#pragma pack(push, 1)
	// * not the hero on the map
	struct H3SetupHero
	{
		INT8	   owner;                    // +0
	protected:
		h3align    _f_01[3];
	public:
		UINT32     number;                   // +4
		UINT32     id;                       // +8
		BOOL8      hasCustomName;            // +C
		CHAR       name[13];                 // +D
		BOOL8      hasCustomExperience;      // +1A
	protected:
		h3align    _f_1B;
	public:
		INT32      experience;               // +1C
		UINT8      hasCustomPicture;         // +20
		UINT8      pictureId;                // +21
		BOOL8      hasCustomSecondarySkills; // +22
	protected:
		h3align    _f_23;
	public:
		UINT32     numberSecondarySkills;    // +24
		UINT8      secondarySkills[8];       // +28
		UINT8      secondarySkillsLevels[8]; // +30
		BOOL8      hasCustomCreatures;       // +38
	protected:
		h3align    _f_39[3];
	public:
		INT32      creatureType[7];          // +3C
		INT16      creatureNumber[7];        // +58
		BOOL8      groupedFormation;         // +66 spread/grouped
		BOOL8      hasCustomArtifacts;       // +67
		H3Artifact bodyArt[19];              // +68
		H3Artifact backpackArt[64];          // +100
		UINT8      backpackCount;            // +300
		UINT16     x;                        // +301
		UINT16     y;                        // +303
		UINT8      radius;                   // +305
		BOOL8      hasCustomBiography;       // +306
	protected:
		UINT8      _f_307;
	public:
		H3String   biography;
		BOOL8      isFemale;                 // +318
	protected:
		h3align    _f_319[3];
	public:
		BOOL8      hasCustomSpells;          // +31C
	protected:
		h3align    _f_31D[3];
	public:
		H3Bitfield spells[3];                // +320
		BOOL8      hasCustomPrimarySkills;   // +32C
		INT8       pSkill[4];                // +32D
	protected:
		h3unk      _f_331[3];
	public:
	};
	_H3API_ASSERT_SIZE_(H3SetupHero, 0x334);
#pragma pack(pop)

#pragma pack(push, 4)

	// * secondary skills of a hero
	struct H3SecondarySkill
	{
		typedef NH3Skills::eSecondarySkills eSecSkills;
		typedef NH3Skills::eSecSkillLevel   eSecSkillLevel;

		INT32 type;  /**< @brief [00] 0..27 eSecSkills*/
		INT32 level; /**< @brief [04] 0..3 eSecSkillLevel*/
	};

	struct H3SecondarySkillInfo
	{
		LPCSTR name;
		LPCSTR description[3];
	};

	struct H3HeroCreatures
	{
		INT32 lowAmount; /**< @brief [00] minimum number of creatures to start with*/
		INT32 higAmount; /**< @brief [04] maximum number of creatures to start with*/
	};

	// * Starting Hero default data
	struct H3HeroInfo
	{
		typedef NH3Heroes::eHeroRace      eHeroRace;
		typedef NH3Heroes::eHeroClasses eHeroClass;

		BOOL32           isFemale;          /**< @brief [00]*/
		eHeroRace        race;              /**< @brief [04] 0..13 never used*/
		INT32            heroClass;         /**< @brief [08] 0..17 eHeroClass*/
		H3SecondarySkill sskills[2];        /**< @brief [0C] starting secondary skills*/
		BOOL8            hasSpellbook;      /**< @brief [1C]*/
	protected:
		h3align         _f_1D[3];
	public:
		INT32           startingSpell;     /**< @brief [20] -1 if no spell*/
		INT32           armyType[3];       /**< @brief [24] NH3Creatures::eH3Creatures*/
		LPCSTR          smallPortrait;     /**< @brief [30] 48x36 small portrait name*/
		LPCSTR          largePortrait;     /**< @brief [34] 58x64 large portrait name*/
		BOOL8           roeHero;           /**< @brief [38] hero is available in RoE*/
		BOOL8           expansionHero;     /**< @brief [39] hero is available in AB and SoD*/
		BOOL8           campaignHero;      /**< @brief [3A] hero is available in specific campaigns, not in regular maps*/
	protected:
		UINT            _f_3C; // always 0
	public:
		LPCSTR          name;              /**< @brief [40] default name of the hero*/
		H3HeroCreatures creatureAmount[3]; /**< @brief [44] up to 3 starting stacks, type is determined by .armyType*/
	};
	_H3API_ASSERT_SIZE_(H3HeroInfo, 0x5C);

	// * The specialty structure of heroes
	struct H3HeroSpecialty
	{
		typedef NH3Heroes::eHeroSpecialty eType;

		// * +0
		eType  type;
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
		unsigned well              : 1; /**< @brief [0x00000001] Visited Well*/
		unsigned stables           : 1; /**< @brief [0x00000002] Visited Stables*/
		unsigned buoy              : 1; /**< @brief [0x00000004] Visited Buoy*/
		unsigned swanPond          : 1; /**< @brief [0x00000008] Visited Swan Pond*/
		unsigned idolFortuneMorale : 1; /**< @brief [0x00000010] Visited idol of fortune on days 1~6, morale bonys*/
		unsigned fountainFortune1  : 1; /**< @brief [0x00000020] -1 luck from fountain of fortune*/
		unsigned wateringHole      : 1; /**< @brief [0x00000040] visited watering hole*/
		unsigned oasis             : 1; /**< @brief [0x00000080] visited oasis*/
		unsigned temple            : 1; /**< @brief [0x00000100] visited temple on days 1~6*/
		unsigned shipwreck         : 1; /**< @brief [0x00000200] shipwreck morale penalty*/
		unsigned crypt             : 1; /**< @brief [0x00000400] crypt morale penalty*/
		unsigned derelectShip      : 1; /**< @brief [0x00000800] derelict ship morale penalty*/
		unsigned pyramid           : 1; /**< @brief [0x00001000] pyramid morale penalty*/
		unsigned faerieRing        : 1; /**< @brief [0x00002000] visited faerie ring*/
		unsigned fountainOfYouth   : 1; /**< @brief [0x00004000] visited fountain of youth*/
		unsigned mermaids          : 1; /**< @brief [0x00008000] visited mermaids*/
		unsigned rallyFlag         : 1; /**< @brief [0x00010000] visited rally flag*/
		unsigned inTavern          : 1; /**< @brief [0x00020000] hero is in tavern, see 0x4DA4D1*/
		unsigned inBoat            : 1; /**< @brief [0x00040000] hero is in a boat*/
		unsigned unk80000          : 1; /**< @brief [0x00080000] */
		unsigned sirens            : 1; /**< @brief [0x00100000] visited sirens*/
		unsigned warriorTomb       : 1; /**< @brief [0x00200000] warrior's tomb morale penalty*/
		unsigned luckCheat         : 1; /**< @brief [0x00400000] typed luck cheat*/
		unsigned moraleCheat       : 1; /**< @brief [0x00800000] typed morale cheat*/
		unsigned speedCheat        : 1; /**< @brief [0x01000000] typed speed cheat*/
		unsigned idolFortuneLuck   : 1; /**< @brief [0x02000000] luck bonus from idol of fortune*/
		unsigned temple2           : 1; /**< @brief [0x04000000] visited temple on day 7, +2 morale*/
		unsigned fountainFortune2  : 1; /**< @brief [0x08000000] +1 luck from fountain of fortune*/
		unsigned fountainFortune3  : 1; /**< @brief [0x10000000] +2 luck from fountain of fortune*/
		unsigned fountainFortune4  : 1; /**< @brief [0x20000000] +3 luck from fountain of fortune*/
		unsigned unk40000000       : 2; /**< @brief [0x40000000-0x80000000] */


	};

#pragma pack(pop)

#pragma pack(push, 1)
	// * Hero structure on the adventure map
	struct H3Hero
	{
		typedef NH3Heroes::eHeroIdentity eHeroId;
		typedef NH3Heroes::eHeroClasses  eHeroClass;

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
		// * the number of spell points
		INT16   spellPoints;
	public:
		// * +1A
		// * 0~156, has to match class, cannot be used to change specialty
		INT32	id;
	protected:
		UINT	number; // +1E set at 4D8DB1, unknown
	public:
		// * +22
		// * 0 ~ 7 Red ~ Pink
		INT8	owner;
		// * +23
		// * the hero's name, null-terminated
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
		h3unk	_f_47;
		h3unk   _f_48;
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
		UINT8	_f_7F[16];
	public:
		// * +8F
		// * the seed for skill tree, 1~255
		UINT8	levelSeed;
	protected:
		UINT8	_f_90;
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
		// * +109
		FLOAT  AI_experienceEffectiveness;
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
		// * +11A
		INT8	moraleBonus;
		// * +11B
		INT8	luckBonus;
	protected:
		BOOL8	isSleeping;	// +11C
		UINT8  _f_11D[12];
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
		INT8	backpackCount;
		// * +3D5
		// * male or female
		BOOL    isFemale;
		// * +3D9
		// * has custom biography?
		BOOL8	customBio;
		// * +3DA
		// * custom biography
		H3String biography;
		// * +3EA
		// * Spells the hero has learned
		BOOL8   learnedSpells[70];
		// * +430
		// * Spells the hero has access to through artifacts
		BOOL8   availableSpells[70];
		// * +476
		// * the four primary skills, attack, defense, spell power, knowledge
		INT8   primarySkill[4];
		// * +47A
		UINT   aiAggressiveness;
		// * +47E
		UINT   aiSpellPowerEffectiveness;
		// * +482
		UINT   aiSpellLengthEffectiveness;
		// * +486
		UINT   aiKnowledgeEffectiveness;
		// * +48A
		UINT   aiDoubleSpellPointsEffectiveness;
		// * +48E
		UINT   aiExtraSpellPointsEffectiveness;

	public:
		// * calculates maximum daily movement on land
		_H3API_ INT32 MaxLandMovement();
		// * calculates maximum daily movement on water
		_H3API_ INT32 MaxWaterMovement();
		// * calculates maximum daily movement automatically
		_H3API_ INT32 CalcMaxMovement();
		// * give an artifact by reference
		_H3API_ VOID GiveArtifact(H3Artifact& art, INT32 slot);
		// * give an artifact to hero
		_H3API_ VOID GiveArtifact(H3Artifact& art);
		// * give an artifact to hero's backpack
		// * index = -1 means first free slot
		_H3API_ VOID GiveBackpackArtifact(H3Artifact& art, INT32 index = -1);
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
		// * checks under the hero for terrain modifying spells
		_H3API_ INT32 GetSpecialSpellTerrain();
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
		// * whether a specified artifact can replace or be placed in specified slot
		_H3API_ BOOL8 CanReplaceArtifact(int id, int slot) const;
		// * whether a specified artifact can be placed in specified slot
		_H3API_ BOOL8 CanPlaceArtifact(int id, int slot) const;
		// * removes an artifact from player
		_H3API_ VOID RemoveArtifact(int slot);
		// * removes an artifact from player's backpack
		_H3API_ VOID RemoveBackpackArtifact(int slot);
		// * shows animated creature dialog
		_H3API_ VOID ShowCreatureDialog(int slot, BOOL rightClick);
		// * Show info about hero's proficiency at spell
		_H3API_ VOID ShowSpellInfo(int spell, BOOL RMB);
		// * Show info about hero's seconday skill
		_H3API_ VOID ShowSSkillInfo(int skill, BOOL RMB);
		// * Show info about hero's primary skill
		_H3API_ VOID ShowPSkillInfo(int skill, BOOL RMB);
		// * Checks if the hero is wearing all pieces of a combination artifact
		_H3API_ BOOL HasAllCombinationParts(INT slot);
		// * disassembles a combination artifact and
		// * gives a hero all pieces of a combination artifact
		_H3API_ VOID DisassembleCombinationArtifact(INT slot);
		// * opponentArmy may be nullptr to calculate the cost on adventure map
		_H3API_ INT32 CalculateSpellCost(INT spell, H3Army* opponentArmy, INT specialTerrain);
		// * opponentArmy may be nullptr to calculate the cost on adventure map
		_H3API_ INT32 CalculateAdventureMapSpellCost(INT spell);
		// * remove spell points and redraw hero preview on adventure map
		_H3API_ VOID RemoveSpellPointsAndRefresh(UINT16 spellPoints);
		/**
		 * @brief Updates all temporary spells granted by artifacts or learned
		 */
		_H3API_ VOID UpdateAvailableSpells();
		_H3API_ VOID Hide();
		_H3API_ VOID Show();
	};
	_H3API_ASSERT_SIZE_(H3Hero, 0x492);

	// * how date is represented
	struct H3Date
	{
		UINT16 day;
		UINT16 week;
		UINT16 month;
		// * converts day, week, month into days from start, first day being 1
		_H3API_ UINT32 CurrentDay() const;
	};
#pragma pack(pop)

#pragma pack(push, 4)
	struct H3TownCreatureTypes
	{
		struct iterator
		{
		protected:
			INT32* m_base;
		public:
			_H3API_ iterator(INT32* base);

			_H3API_ iterator& operator*();
			_H3API_ iterator& operator++();
			_H3API_ iterator operator++(int);
			_H3API_ BOOL operator==(const iterator& other) const;
			_H3API_ BOOL operator!=(const iterator& other) const;

			_H3API_ INT32& Base();
			_H3API_ INT32& Upgraded();
		};

		INT32 base[7];
		INT32 upgrade[7];

		_H3API_ iterator begin();
		_H3API_ iterator end();
	};

	// * how towns are represented in memory
	struct H3Town
	{
		typedef NH3Towns::eTownType      eTown;
		typedef NH3Towns::eBuildings eBuildings;

		// * +0
		// * 0..48
		UINT8	number;
		// * +1
		// * -1..7 who owns this town
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
		//h3unk	_f_0A[2];
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
		h3unk	_f_35[3];
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
		//h3unk	_f_C1[3];
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
	_H3API_ASSERT_SIZE_(H3Town, 0x168);

	struct H3SpecialBuildingCosts
	{
		typedef NH3Towns::eSpecialBuildings eSpecialBuildings;

		// * each town has its own
		H3Resources cost[9];
	};

	struct H3NeutralBuildingCosts
	{
		typedef NH3Towns::eNeutralBuildings eNeutralBuildings;
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
		typedef NH3Towns::eBuildings eBuildings;
		typedef NH3Towns::eTownType  eTownType;

		struct Buildings
		{
			union
			{
				struct
				{
					unsigned mageGuild1   : 1;  /**< @brief [00]*/
					unsigned mageGuild2   : 1;  /**< @brief [01]*/
					unsigned mageGuild3   : 1;  /**< @brief [02]*/
					unsigned mageGuild4   : 1;  /**< @brief [03]*/
					unsigned mageGuild5   : 1;  /**< @brief [04]*/
					unsigned tavern       : 1;  /**< @brief [05]*/
					unsigned wharf        : 1;  /**< @brief [06]*/
					unsigned fort         : 1;  /**< @brief [07]*/
					unsigned citadel      : 1;  /**< @brief [08]*/
					unsigned castle       : 1;  /**< @brief [09]*/
					unsigned villageHall  : 1;  /**< @brief [10]*/
					unsigned townHall     : 1;  /**< @brief [11]*/
					unsigned cityHall     : 1;  /**< @brief [12]*/
					unsigned capitol      : 1;  /**< @brief [13]*/
					unsigned market       : 1;  /**< @brief [14]*/
					unsigned resourceSilo : 1;  /**< @brief [15]*/
					unsigned blacksmith   : 1;  /**< @brief [16]*/
					unsigned special17    : 1;  /**< @brief [17]*/
					unsigned horde1       : 1;  /**< @brief [18]*/
					unsigned horde1u      : 1;  /**< @brief [19]*/
					unsigned wharf2       : 1;  /**< @brief [20]*/
					unsigned special21    : 1;  /**< @brief [21]*/
					unsigned special22    : 1;  /**< @brief [22]*/
					unsigned special23    : 1;  /**< @brief [23]*/
					unsigned horde2       : 1;  /**< @brief [24]*/
					unsigned horde2u      : 1;  /**< @brief [25]*/
					unsigned grail        : 1;  /**< @brief [26]*/
					unsigned decor27      : 1;  /**< @brief [27]*/
					unsigned decor28      : 1;  /**< @brief [28]*/
					unsigned decor29      : 1;  /**< @brief [29]*/
					unsigned dwelling1    : 1;  /**< @brief [30]*/
					unsigned dwelling2    : 1;  /**< @brief [31]*/
					unsigned dwelling3    : 1;  /**< @brief [32]*/
					unsigned dwelling4    : 1;  /**< @brief [33]*/
					unsigned dwelling5    : 1;  /**< @brief [34]*/
					unsigned dwelling6    : 1;  /**< @brief [35]*/
					unsigned dwelling7    : 1;  /**< @brief [36]*/
					unsigned dwelling1u   : 1;  /**< @brief [37]*/
					unsigned dwelling2u   : 1;  /**< @brief [38]*/
					unsigned dwelling3u   : 1;  /**< @brief [39]*/
					unsigned dwelling4u   : 1;  /**< @brief [40]*/
					unsigned dwelling5u   : 1;  /**< @brief [41]*/
					unsigned dwelling6u   : 1;  /**< @brief [42]*/
					unsigned dwelling7u   : 1;  /**< @brief [43]*/
					unsigned unused       : 20; /**< @brief [44]*/
				};
				UINT64 value;
			};
		};

		Buildings m_dependency[9][44];
	};
	_H3API_ASSERT_SIZE_(H3TownDependencies::Buildings, 8);

	// * data about each of the 8 players on the map
	struct H3Player // size 0x168
	{
		typedef NH3PlayerColors::ePlayerColors ePlayerColor;

		// * +0
		// * 0..7 RED~PINK
		INT8 ownerID;
		// * +1
		// * number of heroes on map
		INT8 numberHeroes;
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
		INT8  towns[48];
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
		UINT8 _f_C0[12];
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
	_H3API_ASSERT_SIZE_(H3Player, 0x168);

/*
 * Modeled after H3M_OA_ENTRY in h3m format
 * https://github.com/potmdehex/homm3tools/blob/master/h3m/h3mlib/h3m_structures/object_attributes/h3m_oa.h#L20
 * see also https://github.com/potmdehex/homm3tools/blob/master/h3m/h3mlib/h3m_structures/object_attributes/h3m_oa_body.h#L13
 * and https://github.com/ethernidee/era-editor/blob/master/Patch/Common.pas#L39 from mapeditor format
 */
	struct H3ObjectAttributes
	{
		typedef NH3Objects::eObjectTypes eH3Objects;

		// * +0
		// * the name of the DEF
		H3String defName;
		// * +10
		// * the width of object, read from LoD @ 0x503ED5
		UINT8 width;
		// * +11
		// * the height of object, read from LoD @ 0x503EE2
		UINT8 height;
		// * +14
		// * a 8x6 bitfield of the object's presence
		H3ObjectMask colors;
		// * +1C
		// * a 8x6 bitfield of the object's passability
		H3ObjectMask passability;
		// * +24
		// * a 8x6 bitfield of the object's shadow
		H3ObjectMask shadows;
		// * +2C
		// * a 8x6 bitfield of the object's yellow tiles
		H3ObjectMask entrances;
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
		//h3align _f_41;
		// * referenced a few places, e.g. 0x50663A
		h3unk16 _f_42;
	};
	_H3API_ASSERT_SIZE_(H3ObjectAttributes, 0x44);

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
		// * +8
		// * reference to object's DEF for drawing purposes
		UINT16 num;
		// * +A
		// * Random(0, 255) on map start
		UINT8 frameRandomness;
	};
	_H3API_ASSERT_SIZE_(H3ObjectDetails, 0x0C);

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
	_H3API_ASSERT_SIZE_(H3ObjectDraw, 0x04);

	// * university is an array of 4 sskills
	struct H3University
	{
		typedef NH3Skills::eSecondarySkills eSecSkills;

		INT32 sSkill[4];

		_H3API_ PINT begin();
		_H3API_ PINT end();
	};
#pragma pack(pop)

#pragma pack(push, 1)
	// * data on a given tile on the adventure map
	struct H3MapItem
	{
		typedef NH3Objects::eObjectTypes  eObjectType;
		typedef NH3Terrains::eTerrainType eTerrainType;

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
		h3unk16 _f_0A;
	public:
		union {
			struct {
				bool tileMirrorH  : 1; /**< @brief [01]*/
				bool tileMirrorV  : 1; /**< @brief [02]*/
				bool riverMirrorH : 1; /**< @brief [04]*/
				bool riverMirrorV : 1; /**< @brief [08]*/
				bool roadMirrorH  : 1; /**< @brief [10]*/
				bool roadMirrorV  : 1; /**< @brief [20]*/
				bool canDig       : 1; /**< @brief [40]*/
				bool animated     : 1; /**< @brief [80] (river, water or lava terrain)*/
			};
			UINT8 mirror; /**< @brief [0C] mirror effect of terrain defs*/
		};
		union {
			struct {
				bool cannotAccess   : 1; /**< @brief [01]*/
				bool waterEdge      : 1; /**< @brief [02] see 0x4FEA32*/
				bool unknownAccess1 : 2;
				bool entranceTile   : 1; /**< @brief [10] yellow tile in mapeditor*/
				bool unknownAccess2 : 3;
			};
			UINT8 access; /**< @brief [0D] accessibility of tiles*/
		};
		// * +E
		// * a vector of DEFs to draw on this tile
		H3Vector<H3ObjectDraw> objectDrawing;
		// * +1E
		// * the object type on this tile
		INT16 objectType;
	protected:
		h3unk16 _f_20;
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
		_H3API_ INT  GetRealType() const; // if there's a hero on a tile, returns object underneath the hero
		_H3API_ UINT GetRealSetup() const; // if there's a hero on a tile, returns the setup of the object underneath the hero

		// * casts setup to relevant map item data
		template<typename ObjectType>
		ObjectType* Cast();
		// * get setup as reference of relevant type
		template<typename ObjectType>
		ObjectType& Get();

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
	_H3API_ASSERT_SIZE_(H3MapItem, 0x26);
	typedef H3Map<H3MapItem> H3Map_MapItem;
	typedef H3FastMap<H3MapItem> H3FastMap_MapItem;
#pragma pack(pop)

#pragma pack(push, 4)

	// * information about artifacts
	// * enum for body artifact position
	// * enum for artifact type ~ level
	struct H3ArtifactSetup
	{
		typedef NH3Artifacts::eArtifactSlots eArtifactSlots;
		typedef NH3Artifacts::eArtifactType  eArtifactType;

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
		INT32 partOfCombo; // -1 indicates it's not part of a combination
		// * +1C
		BOOL8 disabled;
		// * +1D
		INT8 newSpell;
	};
	_H3API_ASSERT_SIZE_(H3ArtifactSetup, 0x20);

	// * how combo artifacts are stored in memory
	struct H3ComboArtifactSetup
	{
		INT32 index;
		// this might be larger if you have more than default artifacts
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
		// * +5C
		// *a list of artifact IDs gained for defeating this bank
		H3Vector<INT32> artifacts;

		_H3API_ BOOL HasUpgradedStack();
		_H3API_ VOID SetupBank(int type, int level);
		_H3API_ VOID UpgradeStack(BOOL upg);
	};
	_H3API_ASSERT_SIZE_(H3CreatureBank, 0x6C);

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
	};
	_H3API_ASSERT_SIZE_(H3CreatureBankState, 0x60);

	// * CRBanks.txt converted in memory, overall bank state
	struct H3CreatureBankSetup
	{
		typedef NH3Objects::eCrBank eCrBank;

		H3String name;
		H3CreatureBankState states[4];
	};

	// * town wall elements
	struct H3ValidCatapultTargets
	{
		typedef NH3Combat::eFortElements eFortElements;

		INT32 fortElementId;
	protected:
		h3unk f_04[8];
	public:
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
	};
	_H3API_ASSERT_SIZE_(H3WallSection, 0x24);

	// * information about H3 spells
	struct H3Spell
	{
		typedef NH3Spells::eSchool     eSchool;
		typedef NH3Spells::eSpells     eSpells;
		typedef NH3Spells::eTargetType eTargetType;

		// * +0
		eTargetType type;
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
			unsigned battlefieldSpell : 1;
			// * flag 2
			unsigned mapSpell : 1;
			// * flag 4
			unsigned timeScale : 1;
			// * flag 8
			unsigned creatureSpell : 1;
			// * flag 10
			unsigned singleTarget : 1;
			// * flag 20
			unsigned singleShootingStack : 1;
			// * flag 40
			unsigned expertMassVersion : 1;
			// * flag 80
			unsigned targetAnywhere : 1;
			// * flag 100
			unsigned removeObstacle : 1;
			// * flag 200
			// * All damage spells
			unsigned damageSpell : 1;
			// * flag 400
			unsigned mindSpell : 1;
			// * flag 800
			unsigned friendlyMass : 1;
			// * flag 1000
			unsigned cannotTargetSiege : 1;
			// * flag 2000
			unsigned spellFromArtifact : 1;
			// * flag 4000
			// * Air/Fire Shield, Protections From, Anti-Magic, Magic Mirror, Stone Skin, Counterstrike
			unsigned defensive : 1;
			// * flag 8000
			// * All damage spells except INFERNO and CHAING LIGHTNING
			unsigned aiDamageSpells : 1;
			// * flag 10000
			// * Inferno and Chaing Lightning
			unsigned aiAreaEffect : 1;
			// * flag 20000
			// * Death Ripple, Destroy Undead and Armageddon
			unsigned aiMassDamageSpells : 1;
			// * flag 40000
			// * Shield, Air Shield, ... Berserk, Teleport, Clone
			// * NO SUMMON SPELLS
			unsigned aiNonDamageSpells : 1;
			// * flag 80000
			// * Resurrection, Animate Dead
			// * Hypnotize
			// * 4 Summon Spells
			unsigned aiCreatures : 1;
			// * flag 100000
			// * Summon Boat, Fly, WW, DD, TP
			// * Earthquake, Titan's Lightning Bolt (not sure why these are here???)
			unsigned aiAdventureMap : 1;
			// * there are no spells with these flags
			unsigned unk200000 : 11;
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

		_H3API_ INT32 GetBaseEffect(INT32 level, INT32 spellPower);
	};
	_H3API_ASSERT_SIZE_(H3Spell, 0x88);

	// * information about combat obstacles
	struct H3ObstacleInfo
	{
		// * +0 (bitfield)
		UINT16 landTypes;
		// * +2 (bitfield)
		UINT16 specialGroundTypes;
		// * +4
		INT8 heightInCells;
		// * +5
		INT8 widthInCells;
		// * +6
		INT8 blockedCount;
		// * +7
		h3unk8 _f_7;
		// * +8
		INT8 relativeCells[8];
		// * +10
		LPCSTR defName;
	};
	_H3API_ASSERT_SIZE_(H3ObstacleInfo, 0x14);

	// * information about obstacle in combat manager
	struct H3Obstacle
	{
		// * +0
		H3LoadedDef* def;
		// * +4
		H3ObstacleInfo* info;
		// * +8
		UINT8 anchorHex;
	protected:
		h3unk8 f_09;    // {-1}
		h3unk8 f_0A;    // {1}
		h3align _f_0B;
		UINT _f_0C;    // {0}
		UINT _f_10;    // {0}
		UINT f_14;     // {-1}
	};
	_H3API_STATIC_ASSERT_(sizeof(H3Obstacle) == 24, "H3Obstacle is incorrect");

	// * bitfield flags for creatures
	struct H3CreatureFlags
	{
		unsigned doubleWide        : 1; // 1
		unsigned flyer             : 1; // 2
		unsigned shooter           : 1; // 4
		unsigned extendedAttack    : 1; // 8 ~ aka dragon breath
		unsigned alive             : 1; // 10
		unsigned destroyWalls      : 1; // 20
		unsigned siegeWeapon       : 1; // 40
		unsigned king1             : 1; // 80 ~ all creatures of 7th level and neutral dragons that do not belong to the KING2 or KING3
		unsigned king2             : 1; // 100
		unsigned king3             : 1; // 200
		unsigned mindImmunity      : 1; // 400
		unsigned noObstaclePenalty : 1; // 800
		unsigned noMeleePenalty    : 1; // 1000
		unsigned unk2000           : 1; // 2000
		unsigned fireImmunity      : 1; // 4000
		unsigned doubleAttack      : 1; // 8000
		unsigned noRetaliation     : 1; // 10000
		unsigned noMorale          : 1; // 20000
		unsigned undead            : 1; // 40000
		unsigned attackAllAround   : 1; // 80000
		unsigned fireballAttack    : 1; // 100000
		unsigned cannotMove        : 1; // 200000 ~21
		unsigned summon            : 1; // 400000
		unsigned clone             : 1; // 800000
		unsigned morale            : 1; // 1000000
		unsigned waiting           : 1; // 2000000 ~25
		unsigned done              : 1; // 4000000
		unsigned defending         : 1; // 8000000
		unsigned sacrificed        : 1; // 10000000
		unsigned noColoring        : 1; // 20000000
		unsigned gray              : 1; // 40000000
		unsigned dragon            : 1; // 80000000
	};
	_H3API_STATIC_ASSERT_(sizeof(H3CreatureFlags) == 4, "H3CreatureFlags size is invalid");

	// * hardcoded creature information in heroes3.exe
	struct H3CreatureInformation
	{
		typedef NH3Creatures::eH3Creatures eCreatureType;

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
	_H3API_ASSERT_SIZE_(H3CreatureInformation, 0x74);

	// * a substructure of H3CombatMonster related to spells
	struct H3CombatMonsterSpellsData
	{
		INT32 blessDamage;            // 0x458
		INT32 curseDamage;            // 0x45C
		INT32 antiMagic;              // 0x460
		INT32 bloodlustEffect;        // 0x464
		INT32 precisionEffect;        // 0x468
		INT32 weaknessEffect;         // 0x46C
		INT32 stoneSkinEffect;        // 0x470
	protected: INT32 _f_474; public:
		INT32 prayerEffect;           // 0x478
		INT32 mirthEffect;            // 0x47C
		INT32 sorrowEffect;           // 0x480
		INT32 fortuneEffect;          // 0x484
		INT32 misfortuneEffect;       // 0x488
		INT32 slayerType;             // 0x48C - called KING_1/2/3
		INT32 hexesTraveled; /**< @brief [490] for jousting bonus*/
		INT32 counterstrikeEffect;   // 0x494 - number of strikes added through spell
		FLOAT frenzyMultiplier;      // 0x498
		FLOAT blindEffect;           // 0x49C - for calculating damage retaliation damage
		FLOAT fireShieldEffect;      // 0x4A0
	protected: h3unk32 _f_4A4; public:
		FLOAT protectionAirEffect;   // 0x4A8 - in % as below
		FLOAT protectionFireEffect;  // 0x4AC
		FLOAT protectionWaterEffect; // 0x4B0
		FLOAT protectionEarthEffect; // 0x4B4
		FLOAT shieldEffect;          // 0x4B8
		FLOAT airShieldEffect;       // 0x4BC
		BOOL8 blinded;               // 0x4C0 - to reduce damage?
		BOOL8 paralyzed;             // 0x4C1 - to reduce damage?
		INT32 forgetfulnessLevel;    // 0x4C4
		FLOAT slowEffect;            // 0x4C8
		INT32 hasteEffect;           // 0x4CC - value added/removed
		INT32 diseaseAttackEffect;   // 0x4D0
		INT32 diseaseDefenseEffect;  // 0x4D4
	protected: h3unk32 _f_4D8[2]; public:
		INT32 faerieDragonSpell;     // 4E0
		INT32 magicMirrorEffect;     // 4E4 (not a float)
		INT32 morale;                // +4E8
		INT32 luck;                  // +4EC
		BOOL8 isDone;                // +4F0
		BOOL8 highlightContour;      // +4F1
		H3Vector<H3CombatMonster*> dendroidBinder;  // +4F4 which dendroids have binded the current target (used for animation requirement)
		H3Vector<H3CombatMonster*> dendroidBinds;   // +504 a list of H3CombatMonsters binded by this dendroid
	protected:
		H3Vector<H3CombatMonster*> _f_514; // possibly tied to hypnotize as well?
		H3Vector<H3CombatMonster*> hypnotized; // 524
		h3unk _f_534[20];
	};

	// * Cranim.txt
	struct H3MonsterAnimation
	{
		typedef NH3Combat::eMissiles eMissiles;

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
		typedef NH3Creatures::eH3Creatures eCreatureType;
	protected: // these need confirmations
		BOOL8   attackedAlready;              /**< @brief [00]*/
		INT32   totalPlayerStacks;            /**< @brief [04] ??*/
		UINT32  visibility;                   /**< @brief [08] 4-visible, 8-not visible*/
		h3unk32 _f_0C;
		h3unk32 _f_10;
		h3unk32 _f_14;
		h3unk32 _f_18;
		INT32   battlefieldDestination;       /**< @brief [1C] where to shoot/move to*/
		BOOL8   fireShieldAnimation;          /**< @brief [20] fire shield animation is being shown*/
		BOOL8   movementRelated;              /**< @brief [21] fire shield animation is being shown*/
		h3unk32 _f_24;
		INT32   cloneId;                      /**< @brief [28] the index of the cloned creature*/
		h3unk32 _f_2C;
		BOOL8   skipCountDraw;                /**< @brief [30] when true, the rectangular pcx with stack count is not drawn*/
	public:
		INT32 type;                           /**< @brief [34] tied to the creature's id*/
		INT32 position;                       /**< @brief [38] position on battlefield 0..186 */
		INT32 animation;                      /**< @brief [3C]*/
		INT32 animationFrame;                 /**< @brief [40]*/
		INT32 secondHexOrientation;           /**< @brief [44] 0 left, 1 right, -1 not applicable*/
	protected: h3unk32 _f_048;
	public:
		INT32 numberAlive;		              /**< @brief [4C] number of creatures that are currently alive*/
		INT32 previousNumber;                 /**< @brief [50]*/
		INT32 numberForeverDead;              /**< @brief [54] number of creatures that can never be recovered (e.g. basic Resurrection) */
		INT32 healthLost;                     /**< @brief [50] number of lost hit points of top creature in stack*/
		INT32 slotIndex;                      /**< @brief [5C] 0..6, -1 is removed after battle */
		INT32 numberAtStart;                  /**< @brief [60] number of creatures in this stack to compare against resurrection*/
	protected: h3unk32 _f_064[2]; // maybe align?
	public:
		INT32 baseHP;                         /**< @brief [6C] maximum hit points*/
		INT32 isLucky;                        /**< @brief [70]*/
		H3CreatureInformation info;           /**< @brief [74] copy of H3CreatureInformation using combat values in some places*/
	protected: // these need confirmations
		BOOL8 applyFireShield;                /**< @brief [E8] stack needs to be hit by fire shield*/
		BOOL8 hasLosses;                      /**< @brief [E9] ?at least one creature has died?*/
		BOOL8 hasLosses2;                     /**< @brief [EA] ?at least one creature has died?*/
		BOOL8 isDead;                         /**< @brief [EB] all creatures have died*/
	public:
		INT32 spellToApply;                   /**< @brief [EC] set in After-Hit spell subroutine 0x440220*/
	protected:
		h3unk _f_0F0[4];                      /**< @brief [F0] ?before getting attacked? */
	public:
		INT32 side;                           /**< @brief [F4] the real owner of the creature, 0.attacker 1.defender */
		INT32 sideIndex;                      /**< @brief [F8] reference to position on side*/
	protected:
		UINT32 lastAnimationTime;             /**< @brief [FC]*/
		INT32 yOffset;                        /**< @brief [100]*/
		INT32 xOffset;                        /**< @brief [104]*/
		h3unk _f_108[8];                      /**< @brief [108]*/
		H3MonsterAnimation cranim;            /**< @brief [110] data from cranim.txt*/
	public:
		H3LoadedDef* def;                     /**< @brief [164]*/
	protected:
		H3LoadedDef* shootingDef;             /**< @brief [168]*/
		h3unk _f_16C[4];
		LPCSTR moveSound;                     /**< @brief [170]*/
		LPCSTR attackSound;                   /**< @brief [174]*/
		LPCSTR getHitSound;                   /**< @brief [178]*/
		LPCSTR shotSound;                     /**< @brief [17C]*/
		LPCSTR deathSound;                    /**< @brief [180]*/
		LPCSTR defendSound;                   /**< @brief [184]*/
		LPCSTR extraSound1;                   /**< @brief [188]*/
		LPCSTR extraSound2;                   /**< @brief [18C]*/
		h3unk _f_190[4];
	public:
		INT32 activeSpellsNumber;             /**< @brief [194] number of spells currently active*/
		INT32 activeSpellsDuration[81];       /**< @brief [198] remaining number of turns of any spells*/
		INT32 activeSpellsLevel[81];          /**< @brief [2DC] secondary skill level of applied spells*/
	protected: h3unk _f_420[52];
	public:
		INT32 retaliations;                   /**< @brief [454] number of retaliations left*/
		H3CombatMonsterSpellsData spellsData; /**< @brief [458] information about some spell effects, grouped here for clarity*/

		// * returns appropriate name of stack
		_H3API_ LPCSTR GetCreatureName();
		// * returns second square if creature occupies 2 squares
		_H3API_ INT32 GetSecondSquare();
		// * returns actual speed of creature
		_H3API_ INT32 GetStackSpeed();
		/**
		 * @brief Seeks hex id location considering relative orientation for a given position. Battle side is taken into consideration.
		 * @param considered_hex hex location to inspect
		 * @param relative_orientation The neighbor hex orientation, 0~7 see H3AdjacentSquares::eRelativeOrientation
		 * @return hex at relative position, -1 if invalid
		 */
		_H3API_ INT32 HexRelativePosition(INT32 considered_hex, INT32 relative_orientation);

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
		_H3API_ INT32 ApplyPhysicalDamage(INT32 amount);
		_H3API_ VOID  ApplySpell(INT32 spellId, INT32 spellPower, INT32 schoolLevel, H3Hero* hero);
		_H3API_ BOOL8 CanReceiveSpell(INT32 spellId);
		_H3API_ BOOL  CanCastSpellAtEmptyHex(INT32 hexId);
		_H3API_ BOOL8 MoveToHex(INT32 hexId);
		_H3API_ BOOL8 UseEnchanters();
		_H3API_ INT32 GetX() const;
		_H3API_ INT32 GetY() const;
	};
	_H3API_ASSERT_SIZE_(H3CombatMonster, 0x548);

	struct H3PrimarySkills
	{
		typedef NH3Skills::ePrimarySkills ePriSkills;

		union
		{
			struct
			{
				INT8 attack;
				INT8 defense;
				INT8 spellPower;
				INT8 knowledge;
			};
			INT8 priSkills[4];
		};

		_H3API_ PINT8 begin();
		_H3API_ PINT8 end();
	};

	struct H3PandorasBox
	{
		// * +0
		H3String message;
		// * +10
		BOOL8 customizedGuards;
		// * +14
		H3Army guardians;
		// * +4C
		BOOL8 hasMessageOrGuardians;
		// * +50
		INT32 experience;
		// * +54
		INT32 spellPoints;
		// * +58
		INT8 morale;
		// * +59
		INT8 luck;
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
		// * +AC
		H3Army creatureReward;
	};
	_H3API_ASSERT_SIZE_(H3PandorasBox, 0xE4);

	// * Pandora's box is same as event
	struct H3Event : public H3PandorasBox
	{
	};

	// * quest in memory, used for seer's hut and quest guards
	struct H3Quest
	{
		typedef NH3Quest::eQuestType eQuestType;
		// * Unions don't like to have constructors
		// * so this structure his made only for quests
		// * based on H3Vector
		struct QuestVector
		{
		protected:
			h3unk8 _allocator;
			INT32* first;
			INT32* last;
			INT32* capacity;
		public:
			_H3API_ INT32  Count();
			_H3API_ INT32& operator[](INT32 index);
			_H3API_ INT32* begin();
			_H3API_ INT32* end();
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
				INT32 _f_00;
				INT32 targetHero;
				INT32 successfulPlayers;
			} killHero;						// kill certain hero
			struct
			{
				INT32 _f_00;
				H3Position packedCoords;
				INT32 displayCreatureType;
				INT32 player;
			} killMonster;					// kill a monster in certain position on the map
			QuestVector getArtifacts;		// bring artifacts
			struct
			{
				QuestVector number;
				QuestVector type;
			} getCreatures;					// bring creatures
			INT getResources[7];			// bring resources
			INT32 beHero;					// visit as a certain hero
			INT32 bePlayer;					// visit as a certain player
		} data;

		_H3API_ eQuestType GetQuestType() const;
		_H3API_ H3Resources& GetResources();
	};
	_H3API_ASSERT_SIZE_(H3Quest, 0x60);
#pragma pack(pop)

#pragma pack(push, 1)
	// * quest guard is a quest plus a byte to show who visited
	struct H3QuestGuard
	{
		H3Quest* quest;
		struct
		{
			bool red    : 1;
			bool blue   : 1;
			bool tan    : 1;
			bool green  : 1;
			bool orange : 1;
			bool purple : 1;
			bool teal   : 1;
			bool pink   : 1;
		}playersVisited;

		_H3API_ H3Quest::eQuestType QuestType() const;
	};
	_H3API_ASSERT_SIZE_(H3QuestGuard, 5);

	// * seer hut is a quest guard plus some information about reward
	struct H3SeerHut : H3QuestGuard
	{
		typedef NH3Quest::eSeerReward eSeerReward;

		// * +5
		INT32 rewardType;
		// * +9
		INT32 rewardValue;
		// * +D
		INT32 rewardValue2;
		// * +11
		BYTE seerNameId;
		// * +12
		h3unk8 _f_12;

		_H3API_ WORD CreatureCount() const;
		_H3API_ INT8 Luck() const;
		_H3API_ INT8 Morale() const;
		_H3API_ INT32 Primary() const;
		_H3API_ INT8 PrimaryCount() const;

		//_H3API_ H3Quest::eQuestType QuestType() const;
	};
	_H3API_ASSERT_SIZE_(H3SeerHut, 0x13);
#pragma pack(pop)

#pragma pack(push, 4)
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

	struct H3SpellbookText
	{
		struct TextPair
		{
			LPCSTR text;
			LPCSTR description;
		};

		TextPair previousPage;
		TextPair nextPage;
		TextPair adventureMapSpells;
		TextPair combatSpells;
		TextPair schoolSpells[5]; // air, fire, water, earth, all
		TextPair spellPoints;
		TextPair closeSpellbook;
	};

	// * if a mapartifact has a custom setup, this is the referenced data
	struct H3MapArtifact
	{
		// * +0
		H3String message;
		// * +10
		BOOL8 isGuarded;
		// * +14
		H3Army guardians;
	};
	_H3API_ASSERT_SIZE_(H3MapArtifact, 0x4C);

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
		// * +30
		UINT16 firstDay;
		// * +32
		UINT16 repeatEveryXDays;
	};
	_H3API_ASSERT_SIZE_(H3GlobalEvent, 0x34);

	// * the format of events in towns
	struct H3CastleEvent : public H3GlobalEvent
	{
		// * +34
		INT32 castleNumber;
		// * +38
		H3Bitfield buildings[2];
		// * +40
		INT16 creatures[7];
	};
	_H3API_ASSERT_SIZE_(H3CastleEvent, 0x50);

	// * mostly vectors of information used on adventure map
	struct H3MainSetup
	{
		H3Vector<H3ObjectAttributes> objectAttributes; // +00	// +01FB70
		H3Vector<H3ObjectDetails> objectDetails;	   // +10
		H3Vector<H3LoadedDef*>  defs;			       // +20
		H3Vector<H3MapArtifact> artifactResource;      // +30
		H3Vector<H3Monster>     monsters;	           // +40
		H3Vector<H3PandorasBox> pandoraEvents;         // +50 // +01FBC0
		H3Vector<H3SeerHut>     seerHuts;	           // +60 // +01FBD0
		H3Vector<H3QuestGuard>  questGuards;	       // +70 // +01FBE0
		H3Vector<H3GlobalEvent> globalEvents;	       // +80
		H3Vector<H3CastleEvent> castleEvents;	       // +90
	protected:
		H3Vector<h3unk*> _f_A0;                        // +A0
	public:
		H3Vector<H3Quest*> quests;                     // +B0
	protected:
		H3Vector<UINT32> _f_C0;                        // +C0
	public:
		H3MapItem* mapitems;                           // +D0	// +1FC40
		INT32 mapSize;			                       // +D4	// +1FC44
		BOOL8 hasUnderground;                          // +D8	// +1FC48
		H3Vector<H3ObjectAttributes> objectLists[232];

		_H3API_ H3MapItem* GetMapItem(int x, int y, int z);
		_H3API_ VOID DrawItem(H3MapItem* mitem, H3ObjectDraw* draw);
		_H3API_ VOID AddObjectAttribute(H3ObjectAttributes* oa);
		_H3API_ H3Point GetCoordinates(H3MapItem* item);

		_H3API_ H3Map_MapItem GetMap();
		_H3API_ H3FastMap_MapItem GetFastMap();
	};
	_H3API_ASSERT_SIZE_(H3MainSetup, 0xF5C);

	// from WoG sources
	struct H3CampaignInfo
	{
	protected:
		h3unk _f_0;
	public:
		BOOL8 avgMapScoreAbove350;
		INT8 campaignMapIndex;
	protected:
		h3unk _f_3;
	public:
		INT bigCampaignIndex;
	protected:
		h3unk _f_8[4];
	public:
		INT8 crossoverArrayIndex;
	protected:
		h3unk _f_D[3];
		h3unk _f_10[4];
		h3unk _f_14;
		h3unk _f_15[3];
		h3unk _f_18[4];
		h3unk _f_1C;
		h3unk _f_1D[3];
		h3unk _f_20[4];
	public:
		h3unk BigCampaignStarted[21];
	protected:
		h3unk _f_39[3];
		H3Vector<h3unk*> crossoverHeroes;
		h3unk someCrossoverArraysRef;
		h3unk _f_4D[3];
		INT someCrossoverArrays;
		h3unk _f_54[4];
		h3unk _f_58[4];
		H3Vector<h3unk*> campaignMapInfo;
		h3unk _f_6C;
		h3unk _f_6D[3];
		VOID* someCrossoverInfoStructs;
		h3unk _f_74[8];
	};
	_H3API_ASSERT_SIZE_(H3CampaignInfo, 0x7C);

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
		UINT8  z;		// +4
	protected:
		h3unk8 _f_5;
	public:
		INT8 isPresent;	// +6
	};
	_H3API_ASSERT_SIZE_(H3Grail, 0x08);

	// * information about visibility and wandering monster zone control of map tiles
	struct H3TileVision
	{
		UINT8 vision; // bitfield of players
		BOOL8 zoneControl; // does not exist in Demo
	};
	_H3API_ASSERT_SIZE_(H3TileVision, 0x02);
	typedef H3Map<H3TileVision> H3Map_TileVision;
	typedef H3FastMap<H3TileVision> H3FastMap_TileVision;

	// from WoG source
	struct H3PlayersInfo
	{
	protected:
		h3unk _f_000[8];
	public:
		INT8  handicap[8];
		INT32 townType[8];
	protected:
		h3unk _f_030[8];
	public:
		INT8  difficulty;
		CHAR  filename[251];
		CHAR  saveDirectory[100];
	protected:
		h3unk _f_198[12];
	public:
		INT32 heroMaybe[8];
	protected:
		h3unk _f_1C4[8];
	};
	_H3API_ASSERT_SIZE_(H3PlayersInfo, 0x1CC);

	// from wog source
	struct H3PlayerUnk
	{
	protected:
		h3unk _f_0[28];
	public:
		int heroCount;
	protected:
		h3unk _f_20[36];
	};
	_H3API_ASSERT_SIZE_(H3PlayerUnk, 0x44);

	// from wog source
	struct H3MapInfo
	{
		INT mapVersion;
	protected:
		h3unk8 _f_4;
	public:
		INT8 mapDifficulty;
	protected:
		h3unk _f_6;
		h3unk _f_7;
		h3unk _f_8;
		h3unk _f_9;
		h3unk _f_A;
	public:
		INT8 maxHeroLevel;
	protected:
		h3unk8 _f_C;
	public:
		INT8 playerTeam[8];
	protected:
		h3unk _f_15[27];
	public:
		INT8 specialVictoryCondition;
		BOOL8 allowDefeatAllVictory;
	protected:
		h3unk _f_32[6];
	public:
		INT victoryConditionHero; // +38
	protected:
		h3unk _f_3C[12];
	public:
		INT victoryConditionTownX;
		INT victoryConditionTownY;
		INT victoryConditionTownZ;
	protected:
		h3unk _f_54[20];
	public:
		INT victoryConditionHeroX;
		INT victoryConditionHeroY;
		INT victoryConditionHeroZ;
	protected:
		h3unk _f_74[44];
	public:
		H3PlayerUnk PlayerUnk[8];
	protected:
		h3unk _f_2C0[16];
	};
	_H3API_ASSERT_SIZE_(H3MapInfo, 0x2D0);

	// * the data for mines on the adventure map
	struct H3Mine
	{
		// * +0
		// -1 no owner
		INT8 owner;
		// * +1
		// * mine type. 0..6 resource, 7 abandonned
		INT8 type;
		// * +4
		// * garrisoned army
		H3Army army;
		// * +3C
		UINT8 x;
		// * +3D
		UINT8 y;
		// * +3E
		UINT8 z;
	};
	_H3API_ASSERT_SIZE_(H3Mine, 0x40);

	// * custom text for signpost
	struct H3Signpost
	{
		BOOL8 hasMessage;
		H3String message;
	};
	_H3API_ASSERT_SIZE_(H3Signpost, 0x14);

	// * data of creature dwelling on adventure map
	struct H3Dwelling
	{
		// * +0
		INT8 type;
		// * +1
		// * used to retrieve name
		INT8 subtype;
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
	protected:
		h3unk8 _f58[4];
	};
	_H3API_ASSERT_SIZE_(H3Dwelling, 0x5C);

	// * garrison data on adventure map
	struct H3Garrison
	{
		// * +0
		INT8 owner;
		// * +4
		H3Army army;
		// * +3C
		BOOL8 canRemoveCreatures;
		// * +3D
		UINT8 x;
		// * +3E
		UINT8 y;
		// * +3F
		UINT8 z;
	};
	_H3API_ASSERT_SIZE_(H3Garrison, 0x40);
#pragma pack(pop)

#pragma pack(push, 1)
	// * boat data on adventure map
	// from WoG source
	struct H3Boat // size 0x28 from 0x4CE5C0
	{
		INT16 x;
		INT16 y;
		INT16 z;
		INT8 visible;
		H3MapItem* item; // 7
	protected: h3unk _f_0B; public:
		INT32 objectType; // +C
		INT8 objectFlag; // +10
	protected: h3unk _f_11[3]; public:
		INT32 objectSetup; // +14
		INT8 exists; // 18h
		INT8 index; // 19h
		INT8 par1;
		INT8 par2;
		INT8 owner; // 1Ch
	protected:
		h3unk _f_1D[3];
	public:
		INT32 heroId;  // 20h
		BOOL8 hasHero; //24h
	protected:
		h3unk _f_25[3];
	};
	_H3API_ASSERT_SIZE_(H3Boat, 0x28);
#pragma pack(pop)

#pragma pack(push, 4)
	// * how h3combatmonster is represented during ai-ai fast battle
	struct H3FastBattleCreature
	{
		INT32 count;
		INT32 type;
		INT32 num1;
		INT32 num2;
		INT32 speed;
	protected:
		DOUBLE f_14;
		DOUBLE f_1C;
		DOUBLE f_24;
		h3unk f_2C[4];
		h3unk f_30[4];
		h3unk f_34[4];
	public:
		INT32 turretPriority;
		INT32 unitPower;
		INT32 stackPower;
	protected:
		h3unk8 f_44[4];
	};
	_H3API_ASSERT_SIZE_(H3FastBattleCreature, 0x48);

	// * represents one of the two sides during ai-ai fast battle
	struct H3AiFastBattle
	{
		H3Vector<H3FastBattleCreature> creatures; /**< @brief [00]*/
		INT32 specialTerrain;                     /**< @brief [10]*/
		INT32 spellPoints;                        /**< @brief [14]*/
		BOOL8 canCastSpells;                      /**< @brief [18]*/
		INT32 armyStrength;                       /**< @brief [1C]*/
		INT8 tactics;                             /**< @brief [20]*/
		H3Hero* hero;                             /**< @brief [24]*/
		H3Army* army;                             /**< @brief [28]*/
		H3Hero* opponent;                         /**< @brief [2C]*/
		BOOL8 turrets;                            /**< @brief [30]*/
		INT16 turretsLevel;                       /**< @brief [32]*/

		_H3API_ VOID DeleteCreatures();
	};
	_H3API_ASSERT_SIZE_(H3AiFastBattle, 0x34);

	struct H3AIBattleSpell // ctor 4365D0
	{
		// * +0
		INT32 spellId;
		// * +4
		INT32 skillLevel; // the associated secondary skill level to the spell
		// * +8
		INT32 spellPower;
		// * +C
		INT32 spellDuration;
	protected:
		h3unk _f_10;
		INT32 _f_14; // {-1}
		INT32 _f_18; // {-1}
		INT32 _f_1C; // {0}
		UINT8 _f_20; // {0}
	};
	_H3API_ASSERT_SIZE_(H3AIBattleSpell, 0x24);

	struct H3AICombatInfo
	{
		// * +0
		INT heroAttack;
		// * +4
		INT heroDefence;
	protected:
		h3unk _f_08[4];
	public:
		// * +C
		INT damage[4];
		// * +1C
		INT moveType;
		// * +20
		INT thisSide;
		// * +24
		INT enemySide;
	};
	_H3API_ASSERT_SIZE_(H3AICombatInfo, 0x28);

	// * access data about objects on the adventure map
	struct H3GlobalObjectSettings
	{
		BOOL8  cannotEnter; // +0
		BOOL8  exitTop; // +1
		BOOL8  canBeRemoved; // used at 0x548362
		LPCSTR objectName;
		INT32  objectID;
		BOOL32 decor; // is it a decorative item?
	};
	_H3API_ASSERT_SIZE_(H3GlobalObjectSettings, 0x10);
#pragma pack(pop)

#pragma pack(push, 1)
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
	_H3API_ASSERT_SIZE_(H3TileMovement, 0x1E);
#pragma pack(pop)
	typedef H3Map<H3TileMovement> H3Map_TileMovement;
	typedef H3FastMap<H3TileMovement> H3FastMap_TileMovement;
#pragma pack(push, 4)
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
		H3LoadedDef* def;
	protected:
		h3unk _f_04[104];
	public:
		H3Army* army; // +6C
	protected:
		h3unk _f_70[4];
	public:
		H3Hero* hero; // +74
	};
	_H3API_ASSERT_SIZE_(H3CreatureExchange, 0x78);

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
	protected:
		// * +0
		h3unk _f_00[8];
	public:
		// * +8
		INT32 availableMovement;
		// * +C
		INT32 maxLandMovement;
		// * +10
		// * see 0x56B768
		INT32 maxWaterMovement;
		h3unk8 _f_14;
		// * +15
		// * can hero cast Dimension Door?
		BOOL8 ddAccess;
		// * +16
		// * can hero cast fly?
		BOOL8 flyAccess;
		// * +17
		// * can cast waterwalk?
		BOOL8 waterwalkAccess;
		// * +18
		// * level of waterwalk if cast
		INT32 waterwalkLevel;
		// * level of fly if cast
		INT32 flyLevel;
	protected: h3unk _f_20[4]; public:
		// * +24
		// * an array of tile movement
		H3TileMovement* movementInfo;
	protected: h3unk _f_28[8]; public:
		// * +30
		// * map width
		INT32 mapX;
		// * +34
		// * map height
		INT32 mapY;
	protected:
		// * a vector of size 30 items, H3TileMovement ?
		H3Vector<UINT32> _f_38;
	public:
		// * +48
		// * H3Position of path to take
		H3Vector<UINT32> arrowPath;
	protected:
		// * a vector of size 4 items
		H3Vector<UINT32> _f_58;
	public:
		// * +68
		struct BattleHexes
		{
			INT32 hexes[187];
		}*battleHexes;
		// * +6C
		// * [x][y][z] array
		UINT* aiData;

		// * returns reference to H3TileMovement at position
		_H3API_ H3TileMovement* GetMovementInfo(UINT32 mixed_position);
		_H3API_ H3Map_TileMovement GetMap();
		_H3API_ H3FastMap_TileMovement GetFastMap();
	};
	_H3API_STATIC_ASSERT_(sizeof(H3MovementManager) == 0x70, "H3MovementManager size is wrong");

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
		UINT32 csBink;
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
		// * +1F6A0
		H3PlayersInfo playersInfo;
		// * +1F86C
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
		h3unk _f_4E36C[12]; // visited objects, e.g. library, fountain youth, fountain fortune
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
		_H3API_ BOOL8 IsHuman(UINT8 player_id);

		_H3API_ H3Map_MapItem GetMap();
		_H3API_ H3FastMap_MapItem GetFastMap();
	};
	_H3API_STATIC_ASSERT_(sizeof(h3::H3Main) == 0x4E7D0, "H3Main size is invalid");

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
		h3unk      _f_0C[4];
		INT32      zOrder;
		CHAR       name[28]; // 0x14
		INT32      nameEnd; // 0x30
		h3unk      _f_34[4];
	public:
		_H3API_ VOID SetPreviousManager(H3Manager* prev);
		_H3API_ VOID SetNextManager(H3Manager* next);
	};
	_H3API_ASSERT_SIZE_(H3Manager, 0x38);

	// * the manager of managers
	struct H3ExecutiveMgr
	{
		H3Manager* first_mgr;
		H3Manager* last_mgr;
		H3Manager* active_mgr;
	protected:
		h3unk      _f_0C[4];
	public:
		_H3API_ VOID RemoveManager(H3Manager* mgr);
		_H3API_ INT  AddManager(H3Manager* mgr, int order);
	};
	_H3API_ASSERT_SIZE_(H3ExecutiveMgr, 0x10);

	// * This removes the following warning when using enum
// * warning C4482: nonstandard extension used: enum '...' used in qualified name
#pragma warning(push)
#pragma warning(disable : 4482)
// * manager for mouse
	struct H3MouseManager : public H3Manager
	{
		typedef NH3Mouse::H3MouseCursorType       MouseCursorType;
		typedef NH3Mouse::eAdventureMapCursorType AdventureCursorType;
		typedef NH3Mouse::eBattleFieldCursorType  BattlefieldCursorType;
	protected:
		h3unk _f_38[20];
		INT32 cursorType; // 0 crdeflt, 1 cradvntr, 2 crcombat, 3 crspell, 4 artifact @ 0x67FF88
		INT32 cursorFrame;
		H3LoadedDef* cursorDef;
		h3unk _f_58[16];
		BOOL cursorHidden;
		h3unk _f_6C[12];
		RTL_CRITICAL_SECTION criticalSection; // 0x78
	public:
		_H3API_ VOID TurnOn();
		_H3API_ VOID TurnOff();
		_H3API_ INT32 GetType() const;
		_H3API_ INT32 GetFrame() const;
		_H3API_ VOID SetCursor(INT32 type, INT32 frame);
		_H3API_ VOID DefaultCursor();
		_H3API_ VOID SetArtifactCursor(INT32 art_id);
	};
	_H3API_STATIC_ASSERT_(sizeof(H3MouseManager) == 0x90, "H3MouseManager size is invalid");

	// * named heroWindowManager in H3, abbreviated
	// * in charge of drawing and dialogs
	struct H3WindowManager : public H3Manager
	{
		typedef NH3Dlg::eClickId eClickId;
	protected:
		UINT32 resultItemID; // 0x38
		h3unk _f_3C[4];
		struct H3LoadedPcx16* screenPcx16; // +40
		h3unk _f_44[8];
		struct H3LoadedPcx16* backupScreen; // +4C
		struct H3BaseDlg* firstDlg; // +50
		struct H3BaseDlg* lastDlg; // +54
		h3unk _f_58[8];
	public:
		VOID H3Redraw(INT32 x, INT32 y, INT32 dx, INT32 dy);
		UINT32 ClickedItemID() const;
		BOOL ClickedOK() const;
		BOOL ClickedCancel() const;
		struct H3LoadedPcx16* GetDrawBuffer();
	};
	_H3API_STATIC_ASSERT_(sizeof(H3WindowManager) == 0x60, "H3WindowManager size is invalid");
#pragma warning(pop)

	// * in charge of playing sounds
	struct H3SoundManager : public H3Manager
	{
	protected:
		UINT32 mssHandle;
		HANDLE hSamples[17]; // unsure about the amount
		INT32 clickSoundVar; // +84
		h3unk _f_88[8];
		_RTL_CRITICAL_SECTION rtlSection[3];
	public:
		_H3API_ VOID ClickSound(); // modeled after sub_00456540

		// PlaySound is a winapi macro if you don't have WIN32_LEAN_AND_MEAN
#pragma push_macro("PlaySound")
#ifdef PlaySound
#undef PlaySound
#endif
		_H3API_ VOID PlaySound(struct H3WavFile* wav);
		_H3API_ VOID PlaySound(LPCSTR wavName);
#pragma pop_macro("PlaySound")
		/**
		 * @brief Plays a sound file and then waits the specified amount of milliseconds before resuming. Has no effect with HDmod
		 *
		 * @param wav_name name of the wav file to play
		 * @param milliseconds time delay. If negative, 4000 milliseconds are used.
		 */
		_H3API_ VOID PlaySoundAndWait(LPCSTR wav_name, INT milliseconds);
	};
	_H3API_STATIC_ASSERT_(sizeof(H3SoundManager) == 0xD4, "H3SoundManager size is invalid");

	// * in charge of the adventure map
	struct H3AdventureManager : public H3Manager
	{
	protected:
		h3unk _f_038[12];
	public:
		// * +44
		struct H3Dlg* dlg;
		// * +48
		UINT16* arrowPathFrames; // [z][y][z] array storing id of frame to be drawn
	protected:
		h3unk _f_04C[4];
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
		H3LoadedDef* terrainDef[10];
		h3unk _f_088[4];
		// * +8C
		H3LoadedDef* riverDef[4];
		h3unk _f_09C[4];
		// * +A0
		H3LoadedDef* roadDef[3];
		// * +AC
		H3LoadedDef* edgDef;
		// * +B0
		H3LoadedDef* adagDef;
		// * +B4
		H3LoadedDef* agemulDef;
		// * +B8
		H3LoadedDef* agemurDef;
		// * +BC
		H3LoadedDef* agemllDef;
		// * +C0
		H3LoadedDef* agemlrDef;
		// * +C4
		H3LoadedDef* tshrcDef;
		// * +C8
		H3LoadedDef* radarDef;
		// * +CC
		H3LoadedDef* tshreDef;
		// * +D0
		H3Vector<H3LoadedDef*> defs;
		// * +E0
		H3LoadedDef* attackDEF;
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
		H3LoadedDef* heroDef[18];
		// * +154
		H3LoadedDef* boatDef[3];
		// * +160
		H3LoadedDef* boatMovementDef[3];
		// * +16C
		H3LoadedDef* heroFlags00[8];
		// * +18C
		H3LoadedDef* heroFlags01[8];
		// * +1AC
		H3LoadedDef* heroFlags02[8];
		// * +1CC
		H3LoadedDef* heroFlags03[8];
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
		H3WavFile* loopSounds[70];
		// * +360
		H3WavFile* horseXYSounds[11];
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
			// from 0 through 7
			PHERO = 3,
			PTOWN = 4,
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
		_H3API_ VOID ShowCoordinates(UINT32 x, UINT32 y, UINT8 z);
		_H3API_ INT SimulateMouseOver(INT x, INT y);
		_H3API_ INT SimulateMouseOver(POINT& p);
		_H3API_ CHAR UpdateHintMessage();
		_H3API_ H3Point GetCoordinates(H3MapItem* item);

		_H3API_ H3Map_MapItem GetMap();
		_H3API_ H3FastMap_MapItem GetFastMap();

		_H3API_ H3Map_UINT16 GetPathMap();
		_H3API_ H3FastMap_UINT16 GetPathFastMap();
	};
	_H3API_ASSERT_SIZE_(H3AdventureManager, 0x3B8);

	// * trading between two armies
	struct H3SwapManager : public H3Manager
	{
	public:
		// * +38
		struct H3BaseDlg* dlg;
	protected:
		h3unk _f_3C[4];
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
	_H3API_ASSERT_SIZE_(H3SwapManager, 0x68);

	// * in charge of towns
	struct H3TownManager : public H3Manager // size 472
	{
		// * +38
		// * current town structure
		H3Town* town;
		// * +3C
		struct H3LoadedPcx16* background;
		// * +40
		H3LoadedDef* creatures[7];
		struct BuildingDrawInfo
		{
			UINT numberFrames; // +0
			UINT currentFrame; // +4
			UINT xPos; // +8
			UINT yPos; // +C
			UINT width; // +10
			UINT height; // +14
			h3unk _f_18[4];
			UINT id; // +1C
			H3LoadedDef* def; // +20
			H3LoadedPcx* outline; // + 24
			H3LoadedPcx* background; // * +28
			h3unk _f_2C[4];
		}*buildingDrawing[44];
		// * +10C
		UINT numberBuildings;
		// * +110
		INT townType;
	protected:
		h3unk _f_114[4];
	public:
		// * +118
		struct H3BaseDlg* dlg;
		// * +11C
		// * ???
		H3CreatureExchange* top;
		// * +120
		// * this gets copied to recipientPage during mouse hover, however if you click fast enough the update isn't done
		H3CreatureExchange* bottom;
	protected:
		h3unk _f_124[8];
	public:
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
	public:
		// * +1A0
		// * bitfield of what can be built in the construction screen of the city
		H3Bitfield buildings[2];
		h3unk _f_1A8[48];
	public:
		_H3API_ VOID Draw();
		_H3API_ VOID RefreshScreen();
		_H3API_ VOID ViewTavern();
	};
	_H3API_ASSERT_SIZE_(H3TownManager, 0x1D8);

	// * keyboard and mouse input
	struct H3InputManager : public H3Manager
	{
		typedef NH3VKey::eMessageType eMessageType;

		struct InputMessages
		{
			UINT message;
			h3unk f_4[28]; // contents vary
		}messages[64]; // * +38, see 0x4EC6B8, % 64

		INT currentMessage; // * +838
		INT nextMessage; // * +83C

	protected:
		h3unk _f_840[288];
	public:
		_H3API_ InputMessages& GetCurrentMessage();
	};
	_H3API_ASSERT_SIZE_(H3InputManager, 0x960);

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
	protected: h3unk _f_0C[4]; public:
		// * +10
		UINT8 obstacleBits;
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
		// * +1C
		INT32 deadStacksNumber;
		// * +20
		INT8 deadStackSide[14];
		// * +2E
		INT8 deadStackIndex[14];
	protected: h3unk _f_3C[14]; public:
		// * +4A
		BOOL8 availableForLeftSquare;
		// * +4B
		BOOL8 availableForRightSquare;
	protected:
		h3unk8 _f_4C[32];
		h3unk8 _f_6C[4];
	public:

		_H3API_ H3CombatMonster* GetMonster();
	};
	_H3API_ASSERT_SIZE_(H3CombatSquare, 0x70);

	// * from wog source
	struct TownTowerLoaded
	{
		INT32 crType2Shot;
		H3LoadedDef* monDefLoaded;
		H3LoadedDef* shotDefLoaded;
		INT32 creatureX;
		INT32 creatureY;
		INT32 orientation;
		INT32 defGroup;
		struct H3DefFrame* frame;
		INT32 stackNumber;
	};
	_H3API_ASSERT_SIZE_(TownTowerLoaded, 0x24);

	// * index of adjacent squares
	// * -1 if outside of battlefield
	struct H3AdjacentSquares
	{
		typedef NH3Combat::eRelativeOrientation eRelativeOrientation;

		INT16 topRight;
		INT16 right;
		INT16 bottomRight;
		INT16 bottomLeft;
		INT16 left;
		INT16 topLeft;
	};
	_H3API_ASSERT_SIZE_(H3AdjacentSquares, 0x0C);

	// * the manager of the battlefield
	struct H3CombatManager : public H3Manager
	{
		typedef NH3Combat::eBattleAction eBattleAction;
		typedef NH3Combat::eSquareAccess eSquareAccess;
	protected:
		h3unk _f_0038[4];
	public:
		// * +3C
		eBattleAction action;
		// * +40
		INT32 actionParameter;
		// * +44
		INT32 actionTarget;
		// * +48
		INT32 actionParameter2;
		// * +4C
		INT8 accessibleSquares[187];
		// * +107
		// * 1 -> can attack
		// * 2 -> can reach
		eSquareAccess accessibleSquares2[187];
		// * +1C4
		H3CombatSquare squares[187];
		// * +5394
		INT32 landType;
	protected:
		h3unk _f_5398[8];
	public:
		// * +53A0
		INT32 absoluteObstacleId;
		// * +53A4
		INT32 siegeKind;
		// * +53A8
		INT32 hasMoat;
	protected:
		h3unk _f_53AC[4];
	public:
		// * +53B0
		H3LoadedPcx16* drawBuffer;
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
		// * current group
		UINT32 HeroAnimation[2];
		// * +53EC
		UINT32 HeroAnimationFrame[2];
		h3unk _f_53F4[16];
		// * +5404
		H3LoadedDef* heroDefLoaded[2];
		// * +540C
		H3LoadedDef* heroFlagLoaded[2];
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
		// * +132D0
		INT32 creatureAtMousePos;
		// * +132D4
		INT32 mouseCoord;
		// * +132D8
		INT32 attackerCoord;
		// * +132DC
		// * the icons of CRCOMBAT.def, see H3MouseManager::eBattleFieldCursorType
		INT32 moveType;
	protected: h3unk _f_132E0[20]; public:
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
	public:
		// * +13468
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
		BOOL8 tacticsPhase;
		// * +13D6C
		INT32 turn;
		// * +13D70
		INT32 tacticsDifference;
	protected:
		h3unk _f_13D74[4]; // spell related?
		// * +13D78
		TownTowerLoaded towers[3];
	public:
		// * +13DE4
		INT32 waitPhase;
	protected:
		// * +13DE8
		INT32 heroDAttack;
		// * +13DEC
		INT32 heroDDefence;
		// * +13DF0
		INT32 heroDSpellPower2;
		// * +13DF4
		INT32 heroDSpellPoints;
		// * +13DF8
		INT32 townPicturesLoaded[90];
	public:
		// * +13F60
		// * hit points of town walls
		INT32 fortWallsHp[18];
		// * +13FA8
		INT32 fortWallsAlive[18];
	protected: h3unk _f_13FF0[4]; public:
		// * +13FF4
		// * pcx of grids
		H3LoadedPcx* CCellGrdPcx; // this is the name of the resource in the lod
		// * +13FF8
		// * pcx to shade in blue using cheat menu
		H3LoadedPcx* CCellShdPcx;  // this is the name of the resource in the lod
	protected:
		// * +13FFC
		INT32 globalCardeIndex;
	public:
		// * +14000
		// * oddly there are only 20, not 21, slots for each side
		BOOL8 redrawCreatureFrame[2][20];
		// * +14028
		BOOL8 heroAnimation[2];
		// * +1402A
		BOOL8 heroFlagAnimation[2];
		// * +1402C
		BOOL8 turretAnimation[3];
	protected:
		h3unk _f_14030[188];
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

		_H3API_ VOID PlayMagicAnimation(INT32 id, H3CombatMonster* target, INT32 timeStep, BOOL8 showTargetBeingHit);
		_H3API_ VOID ReportDamageDone(H3Spell* spell, LPCSTR attackerName, INT32 damageDone, H3CombatMonster* target, INT32 killedCount);
		_H3API_ BOOL8 ShouldCastSpellAfterHit(INT32 spellId, INT32 side, H3CombatMonster* target);

		_H3API_ VOID ResurrectTarget(H3CombatMonster* target, INT32 hitPoints, INT32 isTemporary);
		_H3API_ H3CombatMonster* SummonCreature(INT32 side, INT32 creatureId, INT32 amount, INT32 position, INT32 redrawAnimation, BOOL redraw);
		_H3API_ H3CombatMonster* GetSummonDemonTarget(INT32 side, INT32 coordinate);
		_H3API_ VOID RaiseDemon(H3CombatMonster* caster, H3CombatMonster* target);
		/**
		 * @brief Checks whether after-hit creature spells can be applied to the target stack using rand(1, 100).
		 *
		 * @param spell_id id of the spell being considered
		 * @param creature_side controlling side of the creature performing the attack [hypnotized ? 1 - side : side]
		 * @param target creature that will receive the spell
		 * @return BOOL8 whether the spell can be applied to the target
		 */
		_H3API_ BOOL8 CanApplyCreatureSpell(INT32 spell_id, INT32 creature_side, H3CombatMonster* target);

		_H3API_ VOID DrawRay(BOOL redraw, INT startX, INT startY, INT dstX, INT dstY, INT allowBranches, INT randomnessRange, INT startThickness, INT endThickness, WORD color565, INT amplitude, INT arching, INT rayStraightness, INT smoothness, BOOL pathRandomness, INT timeDelay);
		_H3API_ VOID DrawRay(BOOL redraw, H3CombatMonster* start, H3CombatMonster* end, INT allowBranches, INT randomnessRange, INT startThickness, INT endThickness, WORD color565, INT amplitude, INT arching, INT rayStraightness, INT smoothness, BOOL pathRandomness, INT timeDelay);
	};
	_H3API_ASSERT_SIZE_(H3CombatManager, 0x140EC);

	// * these are internal to H3API to avoid conflicts
	namespace H3Internal
	{
		_H3API_ H3MouseManager*         _mouseManager();
		_H3API_ H3WindowManager*        _windowManager();
		_H3API_ H3ExecutiveMgr*         _executiveMgr();
		_H3API_ H3Main*                 _main();
		_H3API_ H3CombatManager*        _combatManager();
		_H3API_ H3TownManager*          _townManager();
		_H3API_ H3SoundManager*         _soundManager();
		_H3API_ H3InputManager*         _inputManager();
		_H3API_ H3AdventureManager*     _adventureManager();
		_H3API_ H3MovementManager*      _movementManager();
		_H3API_ H3GlobalObjectSettings* _globalObjectSettings();
		_H3API_ H3Spell*                _spell();
		_H3API_ H3CreatureBankSetup*    _creatureBankSetup();
		_H3API_ H3ValidCatapultTargets* _validCatapultTargets();
		_H3API_ H3ArtifactSetup*        _artifactSetup();
		_H3API_ INT                     _artifactCount();
		_H3API_ H3CreatureInformation*  _creatureInformation();
		_H3API_ H3ObstacleInfo*         _obstacleInfo();
		_H3API_ H3Hero*                 _dialogHero();
		_H3API_ H3TurnTimer*            _turnTimer();
		_H3API_ H3HeroSpecialty*        _heroSpecialty();
		_H3API_ H3TownCreatureTypes*    _townCreatureTypes();
		_H3API_ H3SecondarySkillInfo&   _secondarySkillsInfo(int skill);
		_H3API_ H3ComboArtifactSetup*   _combinationArtifacts();
	}

#pragma pack(pop)
}

#endif /* #define _H3STRUCTURES_HPP_ */