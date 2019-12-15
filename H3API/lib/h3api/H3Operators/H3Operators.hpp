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

#ifndef _H3OPERATORS_HPP_
#define _H3OPERATORS_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

// * The new, new[], delete and delete[] operators are
// * placed behind the _H3API_OPERATORS_ guards.
// * If you want to use them in your project, you
// * should first define the preprocessor argument
// *           _H3API_OPERATORS_

#ifdef _H3API_OPERATORS_

#pragma warning(push)
#pragma warning(disable:4595) /* disable 'operator new': non-member operator new or delete functions may not be declared inline warning */

//* new operator using h3 assets
_H3API_ PVOID operator new(const size_t size);

// * delete operator using h3 assets
_H3API_ VOID operator delete(PVOID block);

// * new[] operator using h3 assets
_H3API_ PVOID operator new[](const size_t size);

// * delete[] operator using h3 assets
_H3API_ VOID operator delete[](PVOID block);

#pragma warning(pop) /* #pragma warning(disable:4595) */

#endif /* _H3API_OPERATORS_ */

#endif /* #define _H3OPERATORS_HPP_ */