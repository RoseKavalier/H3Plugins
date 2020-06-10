//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3CORE_HPP_
#define _H3CORE_HPP_

#ifdef _H3API_LIBRARY_
// * allow function to be compiled
#define _H3API_
// * do not include *.cpp files
#undef _H3API_HEADER_ONLY_
#else
// * force function to be inline
#define _H3API_ inline
// * includes *.cpp as if it were a *.hpp
// * with forced inline functions
#define _H3API_HEADER_ONLY_
#endif

#endif /* #define _H3CORE_HPP_ */