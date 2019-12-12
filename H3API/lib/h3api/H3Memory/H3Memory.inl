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

#ifndef _H3MEMORY_INL_
#define _H3MEMORY_INL_

#include "H3Memory.hpp"

namespace h3
{
	template<typename T>
	inline H3Patcher::WriteValue<T>::WriteValue(const UINT address, const T value)
	{
		H3Protect protect(address, sizeof(T));
		if (protect.CanWrite())
			*reinterpret_cast<T*>(address) = value;
	}

	template<typename T, size_t size>
	inline h3::H3Patcher::WriteValues<T, size>::WriteValues(const UINT address, const T(&value)[size])
	{
		H3Protect protect(address, sizeof(T) * size);
		if (protect.CanWrite())
			for (size_t i = 0; i < size; ++i)
				reinterpret_cast<T*>(address)[i] = value[i];
	}

	template<size_t size>
	inline VOID h3::H3Patcher::HexPatch(const UINT address, const BYTE(&value)[size])
	{
		WriteValues<BYTE, size>(address, value);
	}

	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearch(UINT8(&needle)[sz], INT32 offset)
	{
		return NeedleSearch(PUINT8(needle), sz, offset);
	}
	template<INT32 sz, INT32 sz2>
	inline UINT32 H3DLL::NeedleSearchAround(UINT8(&needle)[sz], INT32 radius, UINT8(&needle2)[sz2])
	{
		return NeedleSearchAround(PUINT8(needle), sz, radius, PUINT8(needle2), sz2);
	}
	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearchAfter(UINT32 after, UINT8(&needle)[sz], INT32 offset)
	{
		return NeedleSearchAfter(after, PUINT8(needle), sz, offset);
	}
	template<INT32 sz, INT32 sz2>
	inline UINT32 H3DLL::NeedleSearchConfirm(UINT8(&needle)[sz], INT32 offset, UINT8(&expectedCode)[sz2])
	{
		return NeedleSearchConfirm(PUINT8(needle), sz, offset, &expectedCode, sz2);
	}
	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearchRData(UINT8(&needle)[sz])
	{
		return NeedleSearchRData(&needle, sz);
	}
	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearchData(UINT8(&needle)[sz])
	{
		return NeedleSearchData(PUINT8(needle), sz);
	}
}



#endif /* #define _H3MEMORY_INL_ */