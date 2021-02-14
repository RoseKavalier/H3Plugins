#include "LodTable.hpp"

using namespace h3;

LodTablePlugin LodTable;
UINT LodTablePlugin::m_lastLod = 8;
H3Lod LodTablePlugin::m_lodTable[LodTablePlugin::LOD_COUNT] = {};

// * existing H3LodType sequence, with room to add
INT LodTablePlugin::m_sequence[4][3][LodTablePlugin::LOD_COUNT] =
{
	{ { 5, 1 },		{ 4, 0 },		{ 1, 0 } },
	{ { 7, 3, 1 },	{ 6, 2, 0 },	{ 2, 1, 0 } },
	{ { 1 },		{ 0 },			{ 1, 0 } },
	{ { 1, 3 },		{ 0, 2 },		{ 1, 0 } }
};

// * the existing lod sequences
LodTablePlugin::LodTypesTable LodTablePlugin::m_table[4][3] =
{
	{ { 2, m_sequence[0][0] }, { 2, m_sequence[0][1] }, { 2, m_sequence[0][2] } },
	{ { 3, m_sequence[1][0] }, { 3, m_sequence[1][1] }, { 3, m_sequence[1][2] } },
	{ { 1, m_sequence[2][0] }, { 1, m_sequence[2][1] }, { 2, m_sequence[2][2] } },
	{ { 2, m_sequence[3][0] }, { 2, m_sequence[3][1] }, { 2, m_sequence[3][2] } }
};

LodTablePlugin::H3LodBase* LodTablePlugin::H3LodBase::Create(LPCSTR lod_name, LPCSTR path)
{
	if (!lod_name || !path || m_lastLod >= LOD_COUNT)
		return NULL;

	h3::F_strncpy(name, lod_name, 31);
	name[31] = 0;
	index = m_lastLod + 1;
	memset(&m_lodTable[index], 0, sizeof(h3::H3Lod));
	m_lodTable[index].Create(this->name);
	LoadItem(path);

	return this;
}

BOOL LodTablePlugin::H3LodBase::LoadItem(LPCSTR lod_path)
{
	int r = FALSE;
	if (index < 0)
		return r;

	if (m_lodTable[index].Load(lod_path))
		return r;
	r = TRUE;
	m_lastLod++;
	LodTable.AddToList(index);
	return r;
}

BOOL LodTablePlugin::AddToList(UINT ind)
{
	BOOL r = FALSE;
	if (ind >= 8 && ind < LOD_COUNT)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int n = m_table[i][j].number;
				int* t = m_table[i][j].index;

				if (n >= LOD_COUNT)
				{
					DeleleteFromList(ind);
					return r;
				}

				for (int k = LOD_COUNT - 1; k > 0; k--)
					t[k] = t[k - 1];
				t[0] = ind;
				m_table[i][j].number += 1;
			}
		}
		r = TRUE;
	}
	return r;
}

BOOL LodTablePlugin::DeleleteFromList(UINT ind)
{
	BOOL r = FALSE;
	if (ind >= 8 && ind < LOD_COUNT)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int n = m_table[i][j].number;
				int* t = m_table[i][j].index;
				for (int k = 0; k < n; k++)
				{
					if (t[k] == ind)
					{
						for (int l = k + 1; l < n; l++)
							t[l - 1] = t[l];
						t[n - 1] = 0;
						m_table[i][j].number -= 1;
						break;
					}
				}
			}
		}
		r = TRUE;
	}
	return r;
}


//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================

BOOL LoadCustomLod(LPCSTR lodName, LPCSTR lodPath)
{
	LodTablePlugin::H3LodBase new_lod;
	return NULL != new_lod.Create(lodName, lodPath);
}

DECLSPEC_NOINLINE int __stdcall LoadLodsFromFolder(LPCSTR path)
{
	if (!path)
		return 0;

	H3Path dir(path);
	if (!dir.IsDirectory())
		return 0;

	int lod_count = 0;

	for (auto& it : dir)
	{
		if (it.IsDirectory())
			continue;
		LPCSTR ext = it.Extension();
		if (!(F_strnicmp(ext, "lod", 3) == 0 || F_strnicmp(ext, "pac", 3) == 0))
			continue;

		H3String filePath(std::move(it.FilePath()));
		if (filePath.Empty())
			continue;

		lod_count += LoadCustomLod(it.FileName(), filePath.String());
	}

	return lod_count; // return number of successfully loaded LODs
}

//===================================================================================
//
//                             HOOKS
//
//===================================================================================


int LodTablePlugin::LoadLodsFromPacks()
{
	constexpr CHAR HD_PACKS_FOLDER[] = "_HD3_Data\\Packs\\";

	HDIni* hdini = VarGetValue<HDIni*>("HD.Ini.Main", NULL); // get HD.ini stored file data
	if (!hdini)
		return EXEC_DEFAULT;

	auto& packs = hdini->FindEntry("Packs"); // find <Packs> entry
	if (packs == hdini->end() || packs->entryCount == 0)
		return EXEC_DEFAULT;

	const UINT num = packs->entryCount;
	H3String packPath(h3_GamePath); // set game path
	packPath.AppendA(HD_PACKS_FOLDER); // add plugins general path
	UINT len = packPath.Length(); // backup current length, for quick reset of packs directory

	for (UINT i = 0; i < num; i++)
	{
		packPath += packs[i]->GetText(); // add pack name to ...\_HD3_Data\Packs\ path
		packPath += '\\';
		LoadLodsFromFolder(packPath.String()); // load all LODs and PACs from this folder
		packPath.Truncate(len); // remove current pack name
	}

	return EXEC_DEFAULT;
}


// * set to occur after game path is created
_LHF_(FindAndLoadLODs)
{
	return LodTable.LoadLodsFromPacks();
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void LodTablePlugin::Start()
{
	constexpr ADDRESS ORIG_LOD_TABLE  = 0x69D8A8;
	constexpr ADDRESS LOD_TABLE_CHECK = 0x55944C + 1;

	H3Version game;
	if (!game.sod() || ORIG_LOD_TABLE != DwordAt(LOD_TABLE_CHECK))
		return;

	VarInit("LodTable.Function", UINT(LoadLodsFromFolder));
	Hook(0x4EEA79, FindAndLoadLODs);

	AddressOfPatch(0x559395 + 1, m_lodTable[0].name);
	AddressOfPatch(0x5593A4 + 1, m_lodTable[1].name);
	AddressOfPatch(0x5593B3 + 1, m_lodTable[2].name);
	AddressOfPatch(0x5593C2 + 1, m_lodTable[3].name);
	AddressOfPatch(0x5593D1 + 1, m_lodTable[4].name);
	AddressOfPatch(0x5593E0 + 1, m_lodTable[5].name);
	AddressOfPatch(0x5593EF + 1, m_lodTable[6].name);
	AddressOfPatch(0x5593FE + 1, m_lodTable[7].name);

	AddressOfPatch(LOD_TABLE_PATCHES, m_lodTable[0].name);
	AddressOfPatch(FILEPOSITION_PATCHES, m_lodTable[0].filePosition);

	// * copy existing LOD to custom LodTable
	// * this step is required as HDmod loads plugins after regular LOD table is populated
	F_memcpy(PVOID(m_lodTable), PVOID(ORIG_LOD_TABLE), sizeof(H3Lod) * 8);

	AddressOfPatch(TYPES_TABLE_PATCHES, m_table[0][0].number);
	AddressOfPatch(TABLE0_INDEX_PATCHES, m_table[0][0].index);
	AddressOfPatch(TABLE01_PATCHES, m_table[0][1].number);
	AddressOfPatch(TABLE01_INDEX_PATCHES, m_table[0][1].index);
	AddressOfPatch(0x55C438 + 3, m_table[0][2].number);
}
