//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-15                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Allocator.hpp"
#include "H3Allocator.inl"

namespace h3
{
	_H3API_ PVOID F_realloc(PVOID obj, UINT new_size)
	{
		return CDECL_2(PVOID, 0x619890, obj, new_size);
	}

	_H3API_ PVOID F_calloc(UINT count, UINT size)
	{
		return CDECL_2(PVOID, 0x61AA61, count, size);
	}

	_H3API_ PVOID F_malloc(UINT size)
	{
		return CDECL_1(PVOID, 0x617492, size);
	}

	_H3API_ VOID F_delete(PVOID obj)
	{
		if (obj)
			CDECL_1(VOID, 0x60B0F0, obj);
	}

	_H3API_ PVOID H3Allocator::operator new(const size_t sz)
	{
		return F_malloc(sz);
	}
	_H3API_ VOID H3Allocator::operator delete(PVOID block)
	{
		F_delete(block);
	}
	_H3API_ PVOID H3Allocator::operator new[](const size_t sz)
	{
		return F_malloc(sz);
	}
	_H3API_ VOID H3Allocator::operator delete[](PVOID block)
	{
		F_delete(block);
	}
}