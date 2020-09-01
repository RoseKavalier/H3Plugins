//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3LOD.hpp"
#include "H3LOD.inl"

namespace h3
{
	_H3API_ H3Lod* H3Lod::Create(LPCSTR fileName)
	{
		return THISCALL_2(H3Lod*, 0x559420, this, fileName);
	}
	_H3API_ VOID H3Lod::Destroy()
	{
		THISCALL_1(VOID, 0x559460, this);
	}
	_H3API_ BOOL H3Lod::Load(LPCSTR fileName)
	{
		return THISCALL_3(BOOL, 0x4FAF30, &filePosition, fileName, 1); // 1 means read-only
	}
	_H3API_ BOOL8 H3Lod::FindFileInLod(LPCSTR file)
	{
		return THISCALL_2(BOOL8, 0x4FB100, &filePosition, file);
	}
	_H3API_ H3LodItem* H3Lod::LoadFileFromLod(LPCSTR file)
	{
		return THISCALL_2(H3LodItem*, 0x4FACA0, &filePosition, file);
	}
	_H3API_ VOID H3LoadedMsk::operator=(const H3Msk & msk)
	{
		width  = msk.width;
		height = msk.height;
		msk.colorMask  >> colors;
		msk.shadowMask >> shadow;
	}
	_H3API_ void H3Msk::Msk::operator>>(H3ObjectMask & mask) const
	{
		mask[0].Set(dbits);
		mask[1].Set(wbits);
	}
}