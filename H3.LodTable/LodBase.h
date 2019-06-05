#ifndef _LODBASE_H_
#define _LODBASE_H_

#pragma once

#include "Hooks.h"

#pragma pack(push, 1)

// * the format of data used when creating a LOD
struct H3LodBase
{
	INT index;
	INT loadStatus;
	CHAR name[32];

	// * loads lod data to custom table
	H3LodBase *Create(PCHAR lodName, PCHAR lodPath);
	// * adds lod to memory
	BOOL LoadItem(PCHAR lodPath);
};


// * internal data relevant to LODs
struct H3LodTypes
{
	static struct LodTypesTable
	{
		INT number;
		INT *index;
	} table[4][3];

	static INT sequence[4][3][LOD_COUNT];
	static BOOL AddToList(INT ind);
	static BOOL DeleleteFromList(INT ind);
};

// * new Lod table
extern H3Lod LodTable[LOD_COUNT];
// * the number of LODs existing, 8 by default
extern INT lastLod;

#pragma pack(pop)

#endif /* #define _LODBASE_H_ */