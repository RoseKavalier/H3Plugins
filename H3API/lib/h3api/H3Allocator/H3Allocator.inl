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

#ifndef _H3ALLOCATOR_INL_
#define _H3ALLOCATOR_INL_

#include "H3Allocator.hpp"

namespace h3
{
	template<typename T>
	inline H3Allocator<T>::H3Allocator()
	{
	}

	template<typename T>
	inline UINT H3Allocator<T>::Size()
	{
		return sizeof(T);
	}

	template<typename T>
	inline T * H3Allocator<T>::allocate(UINT number) throw()
	{
		return static_cast<T*>(F_malloc(number * Size()));
	}

	template<typename T>
	inline VOID H3Allocator<T>::deallocate(T * block) throw()
	{
		F_delete(block);
	}

}

#endif /* #define _H3ALLOCATOR_INL_ */