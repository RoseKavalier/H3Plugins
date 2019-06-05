#include "Hooks.h"
#include "LodBase.h"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

// * new Lod table
H3Lod LodTable[LOD_COUNT];
// * the number of LODs existing, 8 by default
INT lastLod = 8;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

BOOL LoadCustomLod(PCHAR lodName, PCHAR lodPath)
{
	H3LodBase newLod;
	return NULL != newLod.Create(lodName, lodPath);
}

DECLSPEC_NOINLINE int __stdcall LoadLodsFromFolder(PCHAR path)
{
	int lodCount = 0;
	H3String folderPath, lodPath;
	folderPath = path;
	if (folderPath.Last() != '\\')
		folderPath += '\\';
	// * make a copy
	lodPath = folderPath;
	// * add '*'
	folderPath += '*';
	WIN32_FIND_DATAA data;
	HANDLE handle = h3_FindFirstFileA(folderPath.String(), data);

	CHAR lodName[32];
	int lpLen = lodPath.Length(); // backup of folderPath length, minus '*'

	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;

			INT len = strlen(data.cFileName);
			// * file name ends with .lod or .pac and requires at least 1 other char ==> minimum length 5
			// * LODs can only be 32 chars in name at most, including null char, hence 32 - 1 = 31
			if (len >= 5 && len <= 31)
			{
				h3_strncpy(lodName, data.cFileName, 31);
				lodName[len] = 0; // null terminate
				if (h3_strnicmp(lodName + len - 4, ".lod", 4) == 0 || h3_strnicmp(lodName + len - 4, ".pac", 4) == 0) // is a .lod or .pac file
				{
					lodPath.Append(lodName, len); // complete lod path with its name
					lodCount += LoadCustomLod(lodName, lodPath.String()); // load to our LOD table
					lodPath.Truncate(lpLen); // reset lodPath name without lod name
				}
			}
		} while (h3_FindNextFileA(handle, data));
	}

	return lodCount; // return number of successfully loaded LODs
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// * set to occur after game path is created
_LHF_(FindAndLoadLODs)
{
	HDIni *hdini = (HDIni*)_P->VarGetValue("HD.Ini.Main", NULL); // get HD.ini stored file data
	if (hdini)
	{
		HDIniEntry **entry = hdini->FindEntry("Packs"); // find <Packs> entry
		int num;
		if (entry && (num = (*entry)->entryCount)) // are there any Plugin folders loaded?
		{
			H3String packPath;
			packPath = h3_GamePath; // set game path
			packPath.Append("_HD3_Data\\Packs\\", sizeof("_HD3_Data\\Packs\\") - 1); // add plugins general path
			int len = packPath.Length(); // backup current length, for quick reset of packs directory

			for (int i = 0; i < num; i++)
			{
				entry++; // get next entry, which is next pack
				packPath += (*entry)->GetText(); // add pack name to ...\_HD3_Data\Packs\ path
				packPath += '\\';
				LoadLodsFromFolder(packPath.String()); // load all LODs and PACs from this folder
				packPath.Truncate(len); // remove current pack name
			}
		}
	}
	return EXEC_DEFAULT;
}

void Variables_init(Patcher *p)
{
	// * if you have a custom LOD folder, you can use this
	// * patcher_x86 variable to recuperate the folder loading function.
	// *
	// * Code example
	// *
	// * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// *
	// * Patcher *_P;
	// * UINT32 LoadingFunction = _P->VarGetValue("LodTable.Function", NULL);
	// * _P->WriteLoHook(0x4EEA81, LoadCustomLODPath);
	// *
	// * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// *
	// * LoHook LoadCustomLODPath @ 0x4EEA81
	// *
	// * PCHAR path = "C:\\MyFolderName\\"
	// * INT numLoaded = 0;
	// * if (LoadingFunction)
	// *	numLoaded = STDCALL_1(INT, LoadingFunction, path);
	// * return EXEC_DEFAULT;
	// *
	p->VarInit("LodTable.Function", (UINT)LoadLodsFromFolder);
}

void Hooks_init(PatcherInstance *pi)
{
	// * checks for all active HDmod packs and loads LOD, PAC from these folders
	pi->WriteLoHook(0x4EEA79, FindAndLoadLODs);

	// * replace all LOD references to custom table
	pi->WriteDword(0x559395 + 1, (UINT)(&LodTable[0]));
	pi->WriteDword(0x5593A4 + 1, (UINT)(&LodTable[1]));
	pi->WriteDword(0x5593B3 + 1, (UINT)(&LodTable[2]));
	pi->WriteDword(0x5593C2 + 1, (UINT)(&LodTable[3]));
	pi->WriteDword(0x5593D1 + 1, (UINT)(&LodTable[4]));
	pi->WriteDword(0x5593E0 + 1, (UINT)(&LodTable[5]));
	pi->WriteDword(0x5593EF + 1, (UINT)(&LodTable[6]));
	pi->WriteDword(0x5593FE + 1, (UINT)(&LodTable[7]));

	pi->WriteDword(0x55944C + 1, (UINT)(LodTable));
	pi->WriteDword(0x55A571 + 2, (UINT)(LodTable));
	pi->WriteDword(0x55A629 + 2, (UINT)(LodTable));

	pi->WriteDword(0x55A577 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55A62F + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55A726 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55A7D8 + 1, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55ABB8 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55ABE1 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55AC3D + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55AC6A + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55AFC6 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55AFEF + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B04A + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B077 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B40D + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B436 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B492 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B4BF + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B7D0 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B7F9 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B852 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55B879 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55BBE3 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55BC0C + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55BC68 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55BC95 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55BEF8 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55BF21 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55C1C8 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55C1F1 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55CA54 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55CA7D + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55CAD7 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55CB00 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55D197 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55D1C0 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55D227 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55D250 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55D2A8 + 2, (UINT)(&LodTable[0].filePosition));
	pi->WriteDword(0x55D2C7 + 2, (UINT)(&LodTable[0].filePosition));

	// * copy existing LOD to custom LodTable
	// * this step is required as HDmod loads plugins after regular LOD table is populated
	memcpy((void*)LodTable, (void*)h3_SoDLodTable, (size_t)(sizeof(H3Lod) * 8));

	// * replace static table references
	pi->WriteDword(0x55A548 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55ABA3 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55AC28 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55AFB1 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55B035 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55B3F8 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55B47D + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55B7BB + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55B840 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55BBCE + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55BC53 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55BEE3 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55C1B3 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55C43F + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55CA38 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55CA3F + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55CABB + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55CAC2 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55D17B + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55D212 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55D296 + 3, (UINT)(H3LodTypes::table));
	pi->WriteDword(0x55CA31 + 3, (UINT)(&H3LodTypes::table[0][0].index));
	pi->WriteDword(0x55CAB4 + 3, (UINT)(&H3LodTypes::table[0][0].index));
	pi->WriteDword(0x55D174 + 3, (UINT)(&H3LodTypes::table[0][0].index));
	pi->WriteDword(0x55AB9C + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55AC21 + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55AFAA + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55B02E + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55B3F1 + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55B476 + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55B7B4 + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55B839 + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55BBC7 + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55BC4C + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55BEDC + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55C1AC + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55D20B + 3, (UINT)(&H3LodTypes::table[0][1]));
	pi->WriteDword(0x55AB95 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55AC1A + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55AFA3 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55B027 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55B3EA + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55B46F + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55B7AD + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55B832 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55BBC0 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55BC45 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55BED5 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55C1A5 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55D204 + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55D28F + 3, (UINT)(&H3LodTypes::table[0][1].index));
	pi->WriteDword(0x55C438 + 3, (UINT)(&H3LodTypes::table[0][2]));
}