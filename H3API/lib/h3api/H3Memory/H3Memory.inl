//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
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
	inline H3Patcher::WriteValue<T>::WriteValue(const UINT whereTo, const T value)
	{
		H3Protect protect(whereTo, sizeof(T));
		if (protect.CanWrite())
			*reinterpret_cast<T*>(whereTo) = value;
	}

	template<typename T, size_t size>
	inline H3Patcher::WriteValues<T, size>::WriteValues(const UINT whereTo, const T(&value)[size])
	{
		H3Protect protect(whereTo, sizeof(T) * size);
		if (protect.CanWrite())
			for (size_t i = 0; i < size; ++i)
				reinterpret_cast<T*>(whereTo)[i] = value[i];
	}

	template<typename T>
	VOID H3Patcher::AddressOfPatch(const UINT whereTo, const T & data)
	{
		DwordPatch(whereTo, reinterpret_cast<DWORD>(&data));
	}

	// * writes pointer of data type (its address)
	// * to the specified locations
	// * data can be of any type
	// * Address should be <int> or <long> derived
	template<typename Address, typename Type, size_t size>
	typename H3Internal::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4>::type
	H3Patcher::AddressOfPatch(const Address(&whereTo)[size], const Type & data)
	{
		for (size_t i = 0; i < size; ++i)
			DwordPatch(whereTo[i], reinterpret_cast<DWORD>(&data));
	}

	template<typename T>
	VOID H3Patcher::ObjectPatch(T & reference, T data)
	{
		WriteValue<T>(UINT(&reference), data);
	}

	template<size_t size>
	inline VOID H3Patcher::HexPatch(const UINT whereTo, const BYTE(&value)[size])
	{
		WriteValues<BYTE, size>(whereTo, value);
	}

	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearch(const UINT8(&needle)[sz], INT32 offset)
	{
		return NeedleSearch(PUINT8(needle), sz, offset);
	}
	template<INT32 sz, INT32 sz2>
	inline UINT32 H3DLL::NeedleSearchAround(const UINT8(&needle)[sz], INT32 radius, const UINT8(&needle2)[sz2])
	{
		return NeedleSearchAround(PUINT8(needle), sz, radius, PUINT8(needle2), sz2);
	}
	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearchAfter(UINT32 after, const UINT8(&needle)[sz], INT32 offset)
	{
		return NeedleSearchAfter(after, PUINT8(needle), sz, offset);
	}
	template<INT32 sz, INT32 sz2>
	inline UINT32 H3DLL::NeedleSearchConfirm(const UINT8(&needle)[sz], INT32 offset, const UINT8(&expectedCode)[sz2])
	{
		return NeedleSearchConfirm(PUINT8(needle), sz, offset, &expectedCode, sz2);
	}
	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearchRData(const UINT8(&needle)[sz])
	{
		return NeedleSearchRData(PUINT8(needle), sz);
	}
	template<INT32 sz>
	inline UINT32 H3DLL::NeedleSearchData(const UINT8(&needle)[sz])
	{
		return NeedleSearchData(PUINT8(needle), sz);
	}
}



#endif /* #define _H3MEMORY_INL_ */