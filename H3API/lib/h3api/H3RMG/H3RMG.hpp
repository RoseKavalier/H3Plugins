//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3RMG_HPP_
#define _H3RMG_HPP_

#include "../H3_Structures.hpp"

namespace h3
{
	_H3API_DECLARE_(RMG_Coordinates);
	_H3API_DECLARE_(RMG_GroundTile);
	_H3API_DECLARE_(RMG_GroundTileData);
	_H3API_DECLARE_(RMG_MovementCost);
	_H3API_DECLARE_(RMG_ZoneData);
	_H3API_DECLARE_(RMG_MapItem);
	_H3API_DECLARE_(RMG_ObjectProps);
	_H3API_DECLARE_(RMG_ObjectPropsRef);
	_H3API_DECLARE_(RMG_ObjectGenerator);
	_H3API_DECLARE_(RMG_ZoneGenerator);
	_H3API_DECLARE_(RMG_ZoneConnection);
	_H3API_DECLARE_(RMG_Zone);
	_H3API_DECLARE_(RMG_Template);
	_H3API_DECLARE_(RMG_Object);
	_H3API_DECLARE_(RMG_ObjectMonster);
	_H3API_DECLARE_(RMG_ObjectTown);
	_H3API_DECLARE_(RMG_Map);
	_H3API_DECLARE_(RMG_Parameters);
	_H3API_DECLARE_(RMG_MapInfo);
	_H3API_DECLARE_(RMG_Main);

#pragma pack(push, 4)
	struct RMG_Coordinates : H3Point
	{
	};

	struct RMG_GroundTile
	{
		unsigned  landType    : 5; /**< @brief [00]*/
		unsigned _b6          : 1; /**< @brief [05]*/
		unsigned  landSprite  : 7; /**< @brief [06]*/
		unsigned _b14         : 1; /**< @brief [13]*/
		unsigned  riverType   : 3; /**< @brief [14]*/
		unsigned _b18         : 1; /**< @brief [17]*/
		unsigned  riverSprite : 7; /**< @brief [18]*/
		unsigned _b26         : 1; /**< @brief [25]*/
		unsigned  roadType    : 3; /**< @brief [26]*/
		unsigned _b30         : 3; /**< @brief [29]*/
	};
	_H3API_ASSERT_SIZE_(RMG_GroundTile, 4);

	struct RMG_GroundTileData
	{
		unsigned  roadSprite    : 7;
		unsigned _b8            : 5;	//
		unsigned  orientation   : 3;	// bit 13 [0x0000 1000] ~ monster position 0~7, see 0x5437E2 & 0x54E117
		unsigned  mirrorLandV   : 1;	// bit 16 [0x0000 8000]
		unsigned  mirrorLandH   : 1;	// bit 17 [0x0001 0000]
		unsigned  mirrorRiverV  : 1;	// bit 18 [0x0002 0000]
		unsigned  mirrorRiverH  : 1;	// bit 19 [0x0004 0000]
		unsigned  mirrorRoadV   : 1;	// bit 20 [0x0008 0000]
		unsigned  mirrorRoadH   : 1;	// bit 21 [0x0010 0000]
		unsigned  shore         : 1;	// bit 22 [0x0020 0000]~ unsure, written to h3m at 0x532E42
		unsigned  hasObject     : 1;	// bit 23 [0x0040 0000] ~ see 0x547EB8
		unsigned _b24           : 1;	// bit 24 [0x0080 0000]
		unsigned _b25           : 1;	// bit 25 [0x0100 0000]
		unsigned  mustBeBlocked : 1;	// bit 26 [0x0200 0000] checks if not rock after 0x537F10
		unsigned  isEntrance    : 1;	// bit 27 [0x0400 0000] set when yellow entrance tile
		unsigned  isBlocked     : 1;    // bit 28 [0x0800 0000] ~ if this is not set, roads are allowed to go everywhere!
		unsigned _b29           : 1;	// bit 29 [0x1000 0000] ~ water related ?
		unsigned _b30           : 1;	// bit 30 [0x2000 0000]
		unsigned _b31           : 1;	// bit 31 [0x4000 0000]
		unsigned _b32           : 1;	// bit 32 [0x8000 0000]
	};
	_H3API_ASSERT_SIZE_(RMG_GroundTileData, 4);

	struct RMG_MovementCost
	{
		unsigned  cost : 16;
		unsigned _b17  : 16;
	};
	_H3API_ASSERT_SIZE_(RMG_MovementCost, 4);

	struct RMG_ZoneData
	{
		unsigned _b1    : 16;
		unsigned  zone1 : 8;
		unsigned  zone2 : 8;
	};
	_H3API_ASSERT_SIZE_(RMG_ZoneData, 4);

	struct RMG_MapItem
	{
		H3Vector<RMG_Object*> objects;      /**< @brief [00]*/
		RMG_Coordinates       previousTile;	/**< @brief [10]*/
		RMG_MovementCost      movement;     /**< @brief [1C]*/
		/**
		 * @brief [20] 1st byte ? neighbor zone ?  ? distance to yellow item?
		 * 2nd byte ?
		 * 3rd byte zone id?
		 * 4th byte 2nd zone id?
		 */
		RMG_ZoneData          zone;
		RMG_GroundTile        tile;         /**< @brief [24]*/
		RMG_GroundTileData    tileData;     /**< @brief [28]*/
		h3unk32               _f_2C;        /**< @brief [2C]*/

		_H3API_ INT GetLand() const;
		_H3API_ INT GetLandSprite() const;
		_H3API_ INT GetRiver() const;
		_H3API_ INT GetRiverSprite() const;
		_H3API_ INT GetRoad() const;
		_H3API_ INT GetRoadSprite() const;
	};
	_H3API_ASSERT_SIZE_(RMG_MapItem, 0x30);

	typedef H3Map<RMG_MapItem>     H3Map_RMG_MapItem;
	typedef H3FastMap<RMG_MapItem> H3FastMap_RMG_MapItem;

	/**
	 * @brief similar to H3ObjectAttributes but not same order
	 *
	*/
	struct RMG_ObjectProps
	{
		INT32        defNumber;   /**< @brief [00]*/
		H3ObjectMask passable;    /**< @brief [04]*/
		H3ObjectMask enterable;   /**< @brief [0C]*/
		H3Bitfield   land;        /**< @brief [14]*/
		H3Bitfield   landpage;    /**< @brief [18]*/
		INT32        type;        /**< @brief [1C]*/
		INT32        subtype;     /**< @brief [20]*/
		INT32        page;        /**< @brief [24]*/
		BOOL8        flat;        /**< @brief [28]*/
		BOOL8        hasEntrance; /**< @brief [29]*/
		INT32        enterX;      /**< @brief [2C]*/
		INT32        enterY;      /**< @brief [30]*/
		INT32        width;       /**< @brief [34]*/
		INT32        height;      /**< @brief [38]*/
		H3ObjectMask colors;      /**< @brief [3C]*/
		H3ObjectMask shadows;     /**< @brief [44]*/
	};
	_H3API_ASSERT_SIZE_(RMG_ObjectProps, 0x4C);

	struct RMG_ObjectPropsRef // size E8
	{
		RMG_ObjectProps* prototype;		 /**< @brief [00]*/
		h3unk32          _f_4;			 /**< @brief [04]*/
		UINT32           refCount;		 /**< @brief [08]*/
		INT32            prototypeIndex; /**< @brief [0C]*/
		// ...
	};

	struct RMG_ObjectGenerator
	{
		h3func* vTable;
		INT32   type;
		INT32   subtype;
		// * varying size depending on type
		// * usually 20h, otherwise more
	};

	struct RMG_ZoneGenerator
	{
		RMG_Zone*        zoneInfo;         /**< @brief [00]*/
		INT32            townType;         /**< @brief [04]*/
		INT32            townType2;        /**< @brief [08]*/
		INT32            ground;           /**< @brief [0C]*/
		INT32            x;                /**< @brief [10]*/
		INT32            y;                /**< @brief [14]*/
		INT32            z;                /**< @brief [18]*/
		INT32            size;             /**< @brief [1C]*/
		h3unk8           _f_20[4];         /**< @brief [20]*/
		h3unk8           _f_24[4];         /**< @brief [24]*/
		INT32            width;            /**< @brief [28]*/
		INT32            height;           /**< @brief [2C]*/
		h3unk8           _f_30[12];        /**< @brief [30]*/
		h3unk8           _f_3C[8];         /**< @brief [3C]*/
		INT32            objectCount[232]; /**< @brief [44]*/
		H3Vector<h3unk*> _f_3E4;           /**< @brief [3E4]*/
		H3Vector<h3unk*> _f_3F4;           /**< @brief [3F4]*/
		H3Vector<h3unk*> _f_404;           /**< @brief [404]*/
	};
	_H3API_ASSERT_SIZE_(RMG_ZoneGenerator, 0x414);

	// * values of RMG.TXT
	struct RMG_ZoneConnection
	{
		RMG_Zone* zone;                  /**< @brief [00]*/
		INT32     value;                 /**< @brief [04]*/
		BOOL8     wide;                  /**< @brief [08]*/
		BOOL8     borderGuard;           /**< @brief [09]*/
		BOOL8     created;               /**< @brief [0A]*/
		INT32     minimumHumanPositions; /**< @brief [0C]*/
		INT32     maximumHumanPositions; /**< @brief [10]*/
		INT32     minimumTotalPositions; /**< @brief [14]*/
		INT32     maximumTotalPositions; /**< @brief [18]*/
	};
	_H3API_ASSERT_SIZE_(RMG_ZoneConnection, 0x1C);

	struct RMG_Zone
	{
		struct RMG_Treasure
		{
			INT32 lowValue;
			INT32 highValue;
			INT32 density;
		};
		typedef H3Vector<RMG_ZoneConnection> ZoneConnectionVec;

		INT32             id;                      /**< @brief [00]*/
		INT32             type;                    /**< @brief [04] 0..3 human-computer-treasure-junction*/
		INT32             baseSize;                /**< @brief [08]*/
		INT32             minHumanPositions;       /**< @brief [0C]*/
		INT32             maxHumanPositions;       /**< @brief [10]*/
		INT32             minTotalPositions;       /**< @brief [14]*/
		INT32             maxTotalPositions;       /**< @brief [18]*/
		INT32             townsOwner;              /**< @brief [1C]*/
		INT32             minPlayerTowns;          /**< @brief [20]*/
		INT32             minPlayerCastles;        /**< @brief [24]*/
		INT32             playerTownDensity;       /**< @brief [28]*/
		INT32             playerCastleDensity;     /**< @brief [2C]*/
		INT32             minNeutralTowns;         /**< @brief [30]*/
		INT32             minNeutralCastles;       /**< @brief [34]*/
		INT32             neutralTownsDensity;     /**< @brief [38]*/
		INT32             neutralCastlesDensity;   /**< @brief [3C]*/
		BOOL8             townsAreSameType;        /**< @brief [40]*/
		BOOL8             townTypes[9];            /**< @brief [41]*/
		INT32             minMines[7];             /**< @brief [4C]*/
		INT32             minesDensity[7];         /**< @brief [68]*/
		BOOL8             terrainMatchesTown;      /**< @brief [84]*/
		BOOL8             allowedTerrains[8];      /**< @brief [85]*/
		INT32             monsterStrength;         /**< @brief [90] 0/2/3/4 non/weak/average/strong*/
		BOOL8             monstersMatchTown;       /**< @brief [94]*/
		BOOL8             monstersAllowNeutrals;   /**< @brief [95]*/
		INT8              monstersAllowedTowns[9]; /**< @brief [96]*/
		RMG_Treasure      treasures[3];            /**< @brief [A0]*/
		ZoneConnectionVec connections;             /**< @brief [C4]*/
	};
	_H3API_ASSERT_SIZE_(RMG_Zone, 0xD4);

	struct RMG_Template
	{
		H3String            name;      /**< @brief [00]*/
		H3Vector<RMG_Zone*> zones;     /**< @brief [10]*/
		h3unk8              _f_20[16]; /**< @brief [20]*/
		INT32               minSize;   /**< @brief [30]*/
		INT32               maxSize;   /**< @brief [34]*/
	};
	_H3API_ASSERT_SIZE_(RMG_Template, 0x38);

	struct RMG_Object
	{
		h3func*             vTable;     /**< @brief [00]*/
		RMG_ObjectPropsRef* properties; /**< @brief [04]*/
		INT32               x;          /**< @brief [08]*/
		INT32               y;          /**< @brief [0C]*/
		INT32               z;          /**< @brief [10]*/
		h3unk               _f_14[8];   /**< @brief [14]*/

		_H3API_ h3func GetVTable() const;
	};
	_H3API_ASSERT_SIZE_(RMG_Object, 0x1C);

	struct RMG_ObjectMonster : public RMG_Object
	{
		INT32 indexOnMap; /**< @brief [1C]*/
		INT32 count;      /**< @brief [20]*/
		h3unk _f_24[8];   /**< @brief [24]*/
	};
	_H3API_ASSERT_SIZE_(RMG_ObjectMonster, 0x2C);

	struct RMG_ObjectTown : public RMG_Object
	{
		INT32 indexOnMap; /**< @brief [1C]*/
		INT32 owner;      /**< @brief [20]*/
		BOOL8 hasFort;    /**< @brief [24]*/
	};
	_H3API_ASSERT_SIZE_(RMG_ObjectTown, 0x28);

	struct RMG_ObjectSeer : public RMG_Object
	{
		INT32 artifactId;           /**< @brief [1C]*/
		INT32 experienceAmount;     /**< @brief [20]*/
		INT32 resourceId;           /**< @brief [24]*/
		INT32 resourceAmount;       /**< @brief [28]*/
		INT32 creatureRewardType;   /**< @brief [2C]*/
		INT32 creatureRewardNumber; /**< @brief [30]*/
	};
	_H3API_ASSERT_SIZE_(RMG_ObjectSeer, 0x34);

	struct RMG_Map
	{
		h3func*      mapitemsVTable; /**< @brief [00]*/
		UINT8        mapItemsRef;    /**< @brief [04] probably auto_ptr<RMG_MapItem>*/
		RMG_MapItem* mapItems;       /**< @brief [08]*/
		INT32        mapWidth;       /**< @brief [0C]*/
		INT32        mapHeight;      /**< @brief [10]*/
		INT32        numberLevels;   /**< @brief [14] 1..2*/

		_H3API_ RMG_MapItem* GetMapItem(INT x, INT y, INT z);
		_H3API_ RMG_MapItem* begin();
		_H3API_ RMG_MapItem* end();
		_H3API_ H3Point GetCoordinates(RMG_MapItem* item);
		_H3API_ H3Map_RMG_MapItem GetMap();
		_H3API_ H3FastMap_RMG_MapItem GetFastMap();
	};
	_H3API_ASSERT_SIZE_(RMG_Map, 0x18);

	struct RMG_LocalMap : public RMG_Map
	{
		h3unk _f_18[16];
		H3Vector<RMG_Object*> localObjects; /**< @brief [28]*/
	};
	_H3API_ASSERT_SIZE_(RMG_LocalMap, 0x38);

	struct RMG_Parameters
	{
		BOOL8  isHuman[8];      /**< @brief [00]*/
		INT32  townId[8];       /**< @brief [08]*/
		INT32  width;           /**< @brief [28]*/
		INT32  height;          /**< @brief [2C]*/
		BOOL32 hasUnderground;  /**< @brief [30]*/
		INT32  humanCount;      /**< @brief [34]*/
		INT32  humanTeams;      /**< @brief [38]*/
		INT32  computerCount;   /**< @brief [3C]*/
		INT32  computerTeams;   /**< @brief [40]*/
		INT32  waterAmount;     /**< @brief [44]*/
		INT32  monsterStrength; /**< @brief [48]*/
		INT32  gameVersion;     /**< @brief [4C]*/

		_H3API_ VOID Validate();
	};
	_H3API_ASSERT_SIZE_(RMG_Parameters, 0x50);

	struct RMG_MapInfo
	{
		h3func*      vTable;         /**< @brief [00]*/
		BOOL8        hasMap;         /**< @brief [04] possibly auto_ptr*/
		RMG_MapItem* undergroundMap; /**< @brief [08]*/
		INT32        width;          /**< @brief [0C]*/
		INT32        height;         /**< @brief [10]*/
		BOOL32       underground;    /**< @brief [14]*/
	public:
		_H3API_ RMG_MapInfo(RMG_Main* main, BOOL underground = TRUE);
		_H3API_ ~RMG_MapInfo();
	};
	_H3API_ASSERT_SIZE_(RMG_MapInfo, 0x18);

	struct RMG_Main
	{
		h3func*                        vTable;                 /**< @brief [00]*/
		UINT32                         randomSeed;             /**< @brief [04]*/
		INT32                          gameVersion;            /**< @brief [08]*/
		RMG_Map                        map;                    /**< @brief [0C]*/
		H3Vector<RMG_ObjectProps>      objectsTxt;             /**< @brief [24] all of the the object properties*/
		H3Vector<RMG_ObjectProps**>    objectPrototypes[232];  /**< @brief [34] object properties classified by type*/
		H3Vector<h3unk*>               _f_0EB4;                /**< @brief [EB4]*/
		H3Vector<RMG_Object*>          positions;              /**< @brief [EC4]*/
		h3unk32                        progress;               /**< @brief [ED4]*/
		BOOL8                          isHuman[8];             /**< @brief [ED8]*/
		INT32                          playerOwner[8];         /**< @brief [EE0]*/
		h3unk                          _f_f00[36];             /**< @brief [F00]*/
		INT32                          playerTown[8];          /**< @brief [F24]*/
		INT32                          monsterOrObjectCount;   /**< @brief [F44]*/
		INT32                          humanCount;             /**< @brief [F48]*/
		INT32                          humanTeams;             /**< @brief [F4C]*/
		INT32                          computerCount;          /**< @brief [F50]*/
		INT32                          computerTeams;          /**< @brief [F54]*/
		h3unk                          _f_f58[8];              /**< @brief [F58]*/
		INT32                          townsCount;             /**< @brief [F60]*/
		h3unk                          _f_f64[4];              /**< @brief [F64]*/
		h3unk                          _f_f68[32];             /**< @brief [F68]*/
		BOOL8                          bannedHeroes[156];      /**< @brief [F88]*/
		BOOL8                          bannedArtifacts[144];   /**< @brief [1024]*/
		h3unk                          _f_10B4[4];             /**< @brief [10B4]*/
		INT32                          waterAmount;            /**< @brief [10B8]*/
		INT32                          monsterStrength;        /**< @brief [10BC]*/
		H3String                       templateName;           /**< @brief [10C0]*/
		H3Vector<RMG_Template*>        randomTemplates;        /**< @brief [10D0]*/
		H3Vector<RMG_ZoneGenerator*>   zoneGenerators;         /**< @brief [10E0]*/
		H3Vector<RMG_ObjectGenerator*> objectGenerators;       /**< @brief [10F0]*/
		H3Vector<h3unk*>               _f_1100;                /**< @brief [1100]*/
		INT32                          objectCountByType[232]; /**< @brief [1110]*/
		H3Vector<RMG_Coordinates>      roadTargets;            /**< @brief [14B0]*/
		H3Vector<RMG_Object*>          monolithsOneWay;        /**< @brief [14C0]*/
		H3Vector<RMG_Object*>          monolithsTwoWay;        /**< @brief [14D0]*/

		_H3API_ RMG_Main(RMG_Parameters& p, PVOID progress);
		_H3API_ ~RMG_Main();
		_H3API_ BOOL8 GenerateMap();
		_H3API_ BOOL8 WriteMap(H3ZStream& stream);
	};
	_H3API_ASSERT_SIZE_(RMG_Main, 0x14E0);
#pragma pack(pop)
}

#endif /* #define _H3RMG_HPP_ */