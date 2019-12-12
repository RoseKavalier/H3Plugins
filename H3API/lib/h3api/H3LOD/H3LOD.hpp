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

#ifndef _H3LOD_HPP_
#define _H3LOD_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

namespace h3
{
#pragma pack(push, 1)
	struct H3LodItem
	{
		// * +0
		CHAR name[12];
		h3unk name_end[4];
		// * +10
		PUINT8 buffer;
		// * +14
		UINT32 size;
		// * +18
		INT32 type;
		UINT32 size_compressed;
	};

	// * size 190h
	struct H3Lod
	{
		// * +0
		LPCSTR name;
		// * +4
		FILE* filePosition;
		// * +8
		CHAR path[256]; // possibly less, not important
		h3unk _f_108[112];
		// * +178
		INT32 filesCount;
		h3unk _f_17C[4];
		// * +180
		PUINT8 fileHeaders;
		h3unk _f_184[12];

		H3Lod* Create(LPCSTR fileName);
		VOID Destroy();

		// * 1 means READ_ONLY
		BOOL Load(LPCSTR fileName);
		BOOL8 FindFileInLod(LPCSTR file);
		H3LodItem* LoadFileFromLod(LPCSTR file);
	};
#pragma pack(pop)
}

#endif /* #define _H3LOD_HPP_ */