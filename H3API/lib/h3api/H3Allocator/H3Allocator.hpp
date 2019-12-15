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

#ifndef _H3ALLOCATOR_HPP_
#define _H3ALLOCATOR_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

namespace h3
{
	// * a base structure to use the game new and delete allocators
	template <typename T>
	struct H3Allocator
	{
		H3Allocator();
		UINT Size();
		T* allocate(UINT number) throw();
		VOID deallocate(T* block) throw();
	};
}

#endif /* #define _H3ALLOCATOR_HPP_ */