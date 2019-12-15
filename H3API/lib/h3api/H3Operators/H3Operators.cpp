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

#include "H3Operators.hpp"

#ifdef _H3API_OPERATORS_
#pragma warning(push)
#pragma warning(disable:4595) /* disable 'operator new': non-member operator new or delete functions may not be declared inline warning */

_H3API_ PVOID operator new(const size_t size)
{
	return h3::F_malloc(size);
}

_H3API_ VOID operator delete(PVOID block)
{
	if (block)
		h3::F_delete(block);
}

_H3API_ PVOID operator new[](const size_t size)
{
	return h3::F_malloc(size);
}

_H3API_ VOID operator delete[](PVOID block)
{
	if (block)
		h3::F_delete(block);
}
#pragma warning(pop) /* #pragma warning(disable:4595) */
#endif  /* _H3API_OPERATORS_ */