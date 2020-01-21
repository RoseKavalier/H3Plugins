//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-22                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3RMG_HPP_
#define _H3RMG_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_Vector.hpp"
#include "../H3_String.hpp"
#include "../H3_StreamBuf.hpp"
#include "../H3_Functions.hpp"

namespace h3
{
	// * forward declarations

	struct RMG_Object;
	struct RMG_Zone;
	struct RMG_Main;

#pragma pack(push, 1)
	struct RMG_Coordinates : H3Point
	{		
	};

	struct RMG_GroundTile
	{
		unsigned  landType    : 5; // bit 1~4
		unsigned _b6          : 1;
		unsigned  landSprite  : 7; // bit 7 ~ 13
		unsigned _b14         : 1;
		unsigned  riverType   : 3; // bit 15, 16, 17
		unsigned _b18         : 1;
		unsigned  riverSprite : 7;// bit 19, 20, 21, 22, 23, 24, 25
		unsigned _b26         : 1;
		unsigned  roadType    : 3; // bit 27 28 29
		unsigned _b30         : 3;
	};

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
		unsigned  isBlocked     : 1; // bit 28 [0x0800 0000] ~ if this is not set, roads are allowed to go everywhere!
		unsigned _b29           : 1;	// bit 29 [0x1000 0000] ~ water related ?
		unsigned _b30           : 1;	// bit 30 [0x2000 0000]
		unsigned _b31           : 1;	// bit 31 [0x4000 0000]
		unsigned _b32           : 1;	// bit 32 [0x8000 0000]
	};

	struct RMG_MovementCost
	{
		unsigned  cost : 16;
		unsigned _b17  : 16;
	};

	struct RMG_ZoneData
	{
		unsigned _b1    : 16;
		unsigned  zone1 : 8;
		unsigned  zone2 : 8;
	};

	struct RMG_MapItem
	{
		// * +0
		H3Vector<RMG_Object*> objects;
		// * +10
		RMG_Coordinates previousTile;
		// * +1C
		RMG_MovementCost movement;
		// * +20
		// * 1st byte ? neighbor zone ?  ? distance to yellow item?
		// * 2nd byte
		// * 3rd byte zone id
		// * 4th byte 2nd zone id
		RMG_ZoneData zone;
		// * +24
		RMG_GroundTile tile;
		// * +28
		RMG_GroundTileData tileData;
		h3unk _f_2C[4];

		int GetLand() const;
		int GetLandSprite() const;
		int GetRiver() const;
		int GetRiverSprite() const;
		int GetRoad() const;
		int GetRoadSprite() const;
	};

	// * similar to H3ObjectAttributes but not same order
	struct RMG_ObjectProps // size 4C
	{
		// * +0
		INT32 defNumber;
		// * +4
		H3Bitfield passable[2];
		// * +C
		H3Bitfield enterable[2];
		// * +14
		H3Bitfield land;
		// * +18
		H3Bitfield landpage;
		// * +1C
		INT32 type;
		// * +20
		INT32 subtype;
		// * +24
		INT32 page;
		// * +28
		BOOL8 flat;
		// * +29
		BOOL8 HasEntrance;
		h3align _f_2A[2];
		// * +2C
		INT32 EnterX;
		// * +30
		INT32 EnterY;
		// * +34
		INT32 width;
		// * +38
		INT32 height;
		// * +3C
		H3Bitfield maskobject[2];
		// * +44
		H3Bitfield maskshadow[2];
	};

	struct RMG_ObjectPropsRef // size E8
	{
		// * +0
		RMG_ObjectProps* prototype;
		h3unk _f_4[4];
		// * +8
		UINT32 refCount;
		// * +C
		INT32 prototypeIndex;
	};

	struct RMG_ObjectGenerator
	{
		h3func* vTable;
		INT32 type;
		INT32 subtype;
		// * varying size depending on type
		// * usually 20h, otherwise more
	};

	struct RMG_ZoneGenerator
	{
		// * +0
		PUINT8 zoneInfo;
		// * +4
		INT32 townType;
		// * +8
		INT32 townType2;
		// * +C
		INT32 ground;
		// * +10
		INT32 x;
		// * +14
		INT32 y;
		// * +18
		INT32 z;
		// * +1C
		INT32 size;
		h3unk _f_20[4];
		h3unk _f_24[4];
		// * +28
		INT32 width;
		// * +2C
		INT32 height;
		UINT8 _f_30[12];
		UINT8 _f_3C[8];
		// * +44
		INT32 objectCount[232];
		// * +3E4
		H3Vector<h3unk*> _f_3E4;
		H3Vector<h3unk*> _f_3F4;
		H3Vector<h3unk*> _f_404; // not found =P
	};

	// * values of RMG.TXT
	struct RMG_ZoneConnection // size 1C
	{
		// * +0
		RMG_Zone* zone;
		// * +4
		INT32 value;
		// * +8
		BOOL8 wide;
		// * +9
		BOOL8 borderGuard;
		// * +A
		BOOL8 created;
		h3unk _f_0B;
		// * +C
		INT32 minimumHumanPositions;
		// * +10
		INT32 maximumHumanPositions;
		// * +14
		INT32 minimumTotalPositions;
		// * +18
		INT32 maximumTotalPositions;
	};

	struct RMG_Zone
	{
		// * +0
		INT32 id;
		// * +4
		// * 0 human
		// * 1 computer
		// * 2 treasure
		// * 3 junction
		INT32 type;
		// * +8
		INT32 baseSize;
		// * +C
		INT32 minHumanPositions;
		// * +10
		INT32 maxHumanPositions;
		// * +14
		INT32 minTotalPositions;
		// * +18
		INT32 maxTotalPositions;
		// * +1C
		INT32 townsOwner;
		// * +20
		INT32 minPlayerTowns;
		// * +24
		INT32 minPlayerCastles;
		// * +28
		INT32 playerTownDensity;
		// * +2C
		INT32 playerCastleDensity;
		// * +30
		INT32 minNeutralTowns;
		// * +34
		INT32 minNeutralCastles;
		// * +38
		INT32 neutralTownsDensity;
		// * +3C
		INT32 neutralCastlesDensity;
		// * +40
		BOOL8 townsAreSameType;
		// * +41
		BOOL8 townTypes[9];
		h3unk _f_4A[2];
		// * +4C
		INT32 minMines[7];
		// * +68
		INT32 minesDensity[7];
		// * +84
		BOOL8 terrainMatchesTown;
		// * +85
		BOOL8 allowedTerrains[8];
		h3unk _f_8D[3];
		// * +90
		// * 0 none
		// * 2 weak
		// * 3 average
		// * 4 strong
		INT32 monsterStrength;
		// * +94
		BOOL8 monstersMatchTown;
		// * +95
		BOOL8 monstersAllowNeutrals;
		// * +96
		INT8 monstersAllowedTowns[9];
		h3unk _f_9F;
		// * +A0
		struct RMG_Treasure
		{
			INT32 lowValue;
			INT32 highValue;
			INT32 density;
		}treasures[3];
		// * +C4
		// * size 1C
		H3Vector<RMG_ZoneConnection> connections;
	};

	struct RMG_Template
	{
		// * +0
		H3String name;
		// * +10
		H3Vector<RMG_Zone*> zones;
		// * +20
		h3unk _f_20[4][4];
		// * +30
		INT32 minSize;
		// * +34
		INT32 maxSize;
	};

	struct RMG_Object
	{
		// * +0
		h3func* vTable;
		// * +4
		RMG_ObjectPropsRef* properties;
		// * +8
		INT32 x;
		// * +C
		INT32 y;
		// * +10
		INT32 z;
		h3unk _f_14[8];
	};

	struct RMG_ObjectMonster : public RMG_Object
	{
		// * +1C
		INT32 indexOnMap;
		// * +20
		INT32 count;
		h3unk _f_24[8];
	};

	struct RMG_ObjectTown : public RMG_Object
	{
		// * +1C
		INT32 indexOnMap;
		// * +20
		INT32 owner;
		// * +24
		BOOL8 hasFort;
		h3unk _f_25[3];
	};

	struct RMG_Map
	{
		// * +0
		h3func* mapitemsVTable;
		// * 4
		UINT8 mapItemsRef;
	protected:
		h3align _f_05[3];
	public:
		// * +8
		RMG_MapItem* mapItems;
		// * +C
		INT32 mapWidth;
		// * +10
		INT32 mapHeight;
		// * +14
		// * 1 + underground
		INT32 numberLevels;

		RMG_MapItem* GetMapItem(INT x, INT y, INT z);

		RMG_MapItem* begin();
		RMG_MapItem* end();
		H3Point GetCoordinates(RMG_MapItem* item);
	};

	struct RMG_Parameters
	{
		// * +0
		BOOL8 is_human[8];
		// * +8
		INT32 town_id[8];
		// * +28
		INT32 width;
		// * +2C
		INT32 height;
		// * +30
		BOOL has_underground;
		// * +34
		INT32 human_count;
		// * +38
		INT32 human_teams;
		// * +3C
		INT32 computer_count;
		// * +40
		INT32 computer_teams;
		// * +44
		INT32 water_amount;
		// * +48
		INT32 monster_strength;
		// * +4C
		INT32 game_version;

		VOID Validate();
	};

	struct RMG_MapInfo
	{
		h3func* vTable;
		BOOL8 has_map; // looks like a smart pointer, just not implemented code-wise yet
	protected:
		h3unk _f_05[3];
	public:
		RMG_MapItem* underground_map;
		int width;
		int height;
		BOOL underground;
	public:
		_H3API_ RMG_MapInfo(RMG_Main* main, BOOL underground = TRUE);
		_H3API_ ~RMG_MapInfo();
	};

	struct RMG_Main
	{
		// * +0
		h3func* vTable;
		// * +4
		UINT32 randomSeed;
		// * +8
		INT32 gameVersion;
		// * +C
		RMG_Map map;
		// * +24
		// * all of the the object properties
		H3Vector<RMG_ObjectProps> objectsTxt;
		// * +34
		// * object properties classified by type
		H3Vector<RMG_ObjectProps**> objectPrototypes[232];
		// * +EB4
		H3Vector<h3unk*> _f_0EB4;
		// * +EC4
		H3Vector<RMG_Object*> positions;
		// * +ED4
		UINT32 progress;
		// * +ED8
		BOOL8 isHuman[8];
		// * +EE0
		INT32 playerOwner[8];
		h3unk _f_f00[36];
		// * +F24
		INT32 playerTown[8];
		// * +F44
		INT32 monsterOrObjectCount;
		// * +F48
		INT32 humanCount;
		// * +F4C
		INT32 humanTeams;
		// *+F50
		INT32 computerCount;
		// * +F54
		INT32 computerTeams;
		h3unk _f_f58[8];
		INT32 townsCount;
		h3unk _f_f64[4];
		h3unk _f_f68[32];
		// * +F88
		BOOL8 bannedHeroes[156];
		// * +1024
		BOOL8 bannedArtifacts[144];
		h3unk _f_10B4[4];
		// * +10B8
		INT32 waterAmount;
		// * +10BC
		INT32 monsterStrength;
		// * +10C0
		H3String templateName;
		// * +10D0
		H3Vector<RMG_Template*> randomTemplates;
		// * +10E0
		H3Vector<RMG_ZoneGenerator*> zoneGenerators;
		// * +10F0
		H3Vector<RMG_ObjectGenerator*> objectGenerators;
		H3Vector<h3unk*> _f_1100;
		// * +1110
		INT32 objectCountByType[232];
		// * +14B0
		H3Vector<RMG_Coordinates> roadTargets;
		// * +14C0
		H3Vector<RMG_Object*> monolithsOneWay;
		// * +14D0
		H3Vector<RMG_Object*> monolithsTwoWay;

		_H3API_ RMG_Main(RMG_Parameters& p, PVOID progress);
		_H3API_ ~RMG_Main();
		BOOL8 GenerateMap();
		BOOL8 WriteMap(H3Streambuf& stream);
	};
#pragma pack(pop)
}

#endif /* #define _H3RMG_HPP_ */