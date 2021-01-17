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
	inline BOOL H3Patcher::WriteValue(ADDRESS address, const T value)
	{
		H3Protect protect(address, sizeof(T));
		if (!protect.CanWrite())
			return FALSE;
		ValueAt<T>(address) = value;
		return TRUE;
	}

	template<typename T, size_t size>
	BOOL H3Patcher::WriteValues(const UINT address, const T(&value)[size])
	{
		H3Protect protect(address, sizeof(T) * size);
		if (!protect.CanWrite())
			return FALSE;
		for (size_t i = 0; i < size; ++i)
			ValueAt<T>(address + i) = value[i];
		return TRUE;
	}

	template<typename T>
	BOOL H3Patcher::AddressOfPatch(const UINT address, const T & data)
	{
		return DwordPatch(address, AddressOf(data));
	}

	template<typename Address, typename Type, size_t size>
	typename H3Internal::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4, BOOL>::type
	H3Patcher::AddressOfPatch(const Address(&address)[size], const Type& data)
	{
		for (size_t i = 0; i < size; ++i)
			if (!DwordPatch(address[i], AddressOf(data)))
				return FALSE;
		return TRUE;

		std::addressof(address);
	}

	template<typename T>
	BOOL H3Patcher::ObjectPatch(T & reference, T data)
	{
		return WriteValue<T>(AddressOf(reference), data);
	}

	template<size_t size>
	inline BOOL H3Patcher::HexPatch(const UINT address, const BYTE(&value)[size])
	{
		return WriteValues<BYTE, size>(address, value);
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