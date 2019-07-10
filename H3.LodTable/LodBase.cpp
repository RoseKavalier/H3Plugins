#include "LodBase.h"
#include "../Headers/H3API.h"

// * existing H3LodType sequence, with room to add
INT H3LodTypes::sequence[4][3][LOD_COUNT] =
{
	{ { 5, 1 },		{ 4, 0 },		{ 1, 0 }	},
	{ { 7, 3, 1 },	{ 6, 2, 0 },	{ 2, 1, 0 } },
	{ { 1 },		{ 0 },			{ 1, 0 }	},
	{ { 1, 3 },		{ 0, 2 },		{ 1, 0 }	}
};

// * the existing lod sequences
H3LodTypes::LodTypesTable H3LodTypes::table[4][3] =
{
	{ { 2, sequence[0][0] }, { 2, sequence[0][1] }, { 2, sequence[0][2] } },
	{ { 3, sequence[1][0] }, { 3, sequence[1][1] }, { 3, sequence[1][2] } },
	{ { 1, sequence[2][0] }, { 1, sequence[2][1] }, { 2, sequence[2][2] } },
	{ { 2, sequence[3][0] }, { 2, sequence[3][1] }, { 2, sequence[3][2] } }
};

H3LodBase * H3LodBase::Create(LPCSTR lodName, LPCSTR lodPath)
{
	if (!lodName || !lodPath || lastLod >= LOD_COUNT)
		return NULL;

	F_strncpy(this->name, lodName, 31);
	this->name[31] = 0;
	this->index = lastLod + 1;
	memset(&LodTable[this->index], 0, sizeof(H3Lod));
	LodTable[this->index].Create(this->name);
	this->LoadItem(lodPath);

	return this;
}

BOOL H3LodBase::LoadItem(LPCSTR lodPath)
{
	int r = FALSE;
	if (this->index < 0)
		return r;

	if ((&LodTable[this->index])->Load(lodPath))
		return r;
	r = TRUE;
	lastLod++;
	H3LodTypes::AddToList(this->index);
	return r;
}

BOOL H3LodTypes::DeleleteFromList(INT ind)
{
	BOOL r = FALSE;
	if (ind >= 8 && ind < LOD_COUNT)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int n = table[i][j].number;
				int *t = table[i][j].index;
				for (int k = 0; k < n; k++)
				{
					if (t[k] == ind)
					{
						for (int l = k + 1; l < n; l++)
							t[l - 1] = t[l];
						t[n - 1] = 0;
						table[i][j].number -= 1;
						break;
					}
				}
			}
		}
		r = TRUE;
	}
	return r;
}

BOOL H3LodTypes::AddToList(INT ind)
{
	BOOL r = FALSE;
	if (ind >= 8 && ind < LOD_COUNT)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int n = table[i][j].number;
				int *t = table[i][j].index;

				if (n >= LOD_COUNT)
				{
					DeleleteFromList(ind);
					return r;
				}

				for (int k = LOD_COUNT - 1; k > 0; k--)
					t[k] = t[k - 1];
				t[0] = ind;
				table[i][j].number += 1;
			}
		}
		r = TRUE;
	}
	return r;
}