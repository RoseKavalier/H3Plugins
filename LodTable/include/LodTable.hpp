#pragma once

#include <Plugin.hpp>
#include <H3API.hpp>

/**
 * Uncomment to show an error message when failing to link up with patcher_x86
 */
//#define SHOW_ERROR_MESSAGE_ON_FAIL

/**
 * @brief A derived Plugin that constructs itself
 */
class LodTablePlugin : public Plugin
{
public:
	LodTablePlugin() : Plugin()
	{
		Status status = Init("H3.LodTable");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.LodTable", status);
#endif
	}

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================

	static constexpr UINT LOD_COUNT = 1000;

	BOOL AddToList(UINT ind);
	BOOL DeleleteFromList(UINT ind);

	struct H3LodBase
	{
		INT index;
		INT loadStatus;
		CHAR name[32];

		// * loads lod data to custom table
		H3LodBase* Create(LPCSTR lodName, LPCSTR lodPath);
		// * adds lod to memory
		BOOL LoadItem(LPCSTR lodPath);
	};

	int LoadLodsFromPacks();

	// * new Lod table
	static h3::H3Lod m_lodTable[LOD_COUNT];
	// * the number of LODs existing, 8 by default
	static UINT m_lastLod;

	static struct LodTypesTable
	{
		INT number;
		INT* index;
	} m_table[4][3];

	static INT m_sequence[4][3][LOD_COUNT];

	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================


	static constexpr h3::ADDRESS LOD_TABLE_PATCHES[] =
	{
		0x55944C + 1, 0x55A571 + 2, 0x55A629 + 2
	};

	static constexpr h3::ADDRESS FILEPOSITION_PATCHES[] =
	{
		0x55A577 + 2, 0x55A62F + 2, 0x55A726 + 2, 0x55A7D8 + 1, 0x55ABB8 + 2,
		0x55ABE1 + 2, 0x55AC3D + 2, 0x55AC6A + 2, 0x55AFC6 + 2, 0x55AFEF + 2,
		0x55B04A + 2, 0x55B077 + 2, 0x55B40D + 2, 0x55B436 + 2, 0x55B492 + 2,
		0x55B4BF + 2, 0x55B7D0 + 2, 0x55B7F9 + 2, 0x55B852 + 2, 0x55B879 + 2,
		0x55BBE3 + 2, 0x55BC0C + 2, 0x55BC68 + 2, 0x55BC95 + 2, 0x55BEF8 + 2,
		0x55BF21 + 2, 0x55C1C8 + 2, 0x55C1F1 + 2, 0x55CA54 + 2, 0x55CA7D + 2,
		0x55CAD7 + 2, 0x55CB00 + 2, 0x55D197 + 2, 0x55D1C0 + 2, 0x55D227 + 2,
		0x55D250 + 2, 0x55D2A8 + 2, 0x55D2C7 + 2
	};

	static constexpr h3::ADDRESS TYPES_TABLE_PATCHES[] =
	{
		0x55A548 + 3, 0x55ABA3 + 3, 0x55AC28 + 3, 0x55AFB1 + 3, 0x55B035 + 3,
		0x55B3F8 + 3, 0x55B47D + 3, 0x55B7BB + 3, 0x55B840 + 3, 0x55BBCE + 3,
		0x55BC53 + 3, 0x55BEE3 + 3, 0x55C1B3 + 3, 0x55C43F + 3, 0x55CA38 + 3,
		0x55CA3F + 3, 0x55CABB + 3, 0x55CAC2 + 3, 0x55D17B + 3, 0x55D212 + 3,
		0x55D296 + 3,
	};

	static constexpr h3::ADDRESS TABLE0_INDEX_PATCHES[] =
	{
		0x55CA31 + 3, 0x55CAB4 + 3, 0x55D174 + 3,
	};

	static constexpr h3::ADDRESS TABLE01_PATCHES[] =
	{
		0x55AB9C + 3, 0x55AC21 + 3, 0x55AFAA + 3, 0x55B02E + 3, 0x55B3F1 + 3,
		0x55B476 + 3, 0x55B7B4 + 3, 0x55B839 + 3, 0x55BBC7 + 3, 0x55BC4C + 3,
		0x55BEDC + 3, 0x55C1AC + 3, 0x55D20B + 3,
	};

	static constexpr h3::ADDRESS TABLE01_INDEX_PATCHES[] =
	{
		0x55AB95 + 3, 0x55AC1A + 3, 0x55AFA3 + 3, 0x55B027 + 3, 0x55B3EA + 3,
		0x55B46F + 3, 0x55B7AD + 3, 0x55B832 + 3, 0x55BBC0 + 3, 0x55BC45 + 3,
		0x55BED5 + 3, 0x55C1A5 + 3, 0x55D204 + 3, 0x55D28F + 3,
	};
};