//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3RMG.hpp"
#include "H3RMG.inl"

namespace h3
{
	_H3API_ INT RMG_MapItem::GetLand() const
	{
		return tile.landType;
	}
	_H3API_ INT RMG_MapItem::GetLandSprite() const
	{
		return tile.landSprite;
	}
	_H3API_ INT RMG_MapItem::GetRiver() const
	{
		return tile.riverType;
	}
	_H3API_ INT RMG_MapItem::GetRiverSprite() const
	{
		return tile.riverSprite;
	}
	_H3API_ INT RMG_MapItem::GetRoad() const
	{
		return tile.roadType;
	}
	_H3API_ INT RMG_MapItem::GetRoadSprite() const
	{
		return tileData.roadSprite;
	}
	_H3API_ RMG_MapItem* RMG_Map::GetMapItem(INT x, INT y, INT z)
	{
		return THISCALL_4(RMG_MapItem*, 0x537DD0, this, x, y, z);
	}
	_H3API_ RMG_MapItem* RMG_Map::begin()
	{
		return mapItems;
	}
	_H3API_ RMG_MapItem* RMG_Map::end()
	{
		return &mapItems[mapHeight * mapWidth * numberLevels];
	}
	_H3API_ H3Point RMG_Map::GetCoordinates(RMG_MapItem* item)
	{
		H3Point coordinates;
		UINT delta = item - mapItems;
		coordinates.x = delta % mapWidth;
		delta /= mapWidth;
		coordinates.y = delta % mapWidth;
		coordinates.z = delta / mapWidth;
		return coordinates;
	}
	_H3API_ H3Map_RMG_MapItem RMG_Map::GetMap()
	{
		return H3Map_RMG_MapItem(mapItems, static_cast<UINT>(mapWidth), numberLevels - 1);
	}
	_H3API_ H3FastMap_RMG_MapItem RMG_Map::GetFastMap()
	{
		return H3FastMap_RMG_MapItem(mapItems, static_cast<UINT>(mapWidth), numberLevels - 1);
	}
	_H3API_ VOID RMG_Parameters::Validate()
	{
		monsterStrength += 3;
		if (monsterStrength < 1)
			monsterStrength = 1;
		else if (monsterStrength > 5)
			monsterStrength = 5;

		if (computerCount + humanCount < 2)
		{
			computerCount = 1;
			humanCount = 1;
		}
	}
	_H3API_ RMG_MapInfo::RMG_MapInfo(RMG_Main* main, BOOL underground) :
		vTable((h3func*)0x6409DC),
		hasMap(0),
		undergroundMap(nullptr),
		width(main->map.mapWidth),
		height(main->map.mapHeight),
		underground(underground)
	{
		undergroundMap = &main->map.mapItems[width * height];
	}
	_H3API_ RMG_MapInfo::~RMG_MapInfo()
	{
	}
	_H3API_ RMG_Main::RMG_Main(RMG_Parameters& p, PVOID progress)
	{
		p.Validate();
		THISCALL_12(RMG_Main*, 0x538000, this, p.width, p.height, p.hasUnderground, p.humanCount, p.humanTeams,
			p.computerCount, p.computerTeams, p.waterAmount, p.monsterStrength, progress, p.gameVersion);
		for (INT i = 0; i < 8; ++i)
		{
			if (p.isHuman[i])
				isHuman[i] = TRUE;
			playerTown[i] = p.townId[i];
		}
	}
	_H3API_ RMG_Main::~RMG_Main()
	{
		THISCALL_1(VOID, 0x5382E0, this);
	}
	_H3API_ BOOL8 RMG_Main::GenerateMap()
	{
		return THISCALL_1(BOOL8, 0x549E20, this);
	}
	_H3API_ BOOL8 RMG_Main::WriteMap(H3ZStream& stream)
	{
		return THISCALL_2(BOOL8, 0x54B0E0, this, &stream);
	}
	_H3API_ h3func RMG_Object::GetVTable() const
	{
		return h3func(vTable);
	}
}