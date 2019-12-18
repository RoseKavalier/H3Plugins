//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-15                        //
//                      Last edit: 2019-12-15                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Allocator.hpp"

namespace h3
{
	_H3API_ PVOID H3Allocator::operator new(const size_t sz)
	{
		return F_malloc(sz);
	}
	_H3API_ VOID H3Allocator::operator delete(const PVOID block)
	{
		F_delete(block);
	}
	_H3API_ PVOID H3Allocator::operator new[](const size_t sz)
	{
		return F_malloc(sz);
	}
	_H3API_ VOID H3Allocator::operator delete[](const PVOID block)
	{
		F_delete(block);
	}
}