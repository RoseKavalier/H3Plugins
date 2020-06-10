//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-05-28                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3_VERSION_HPP_
#define _H3_VERSION_HPP_

#include "H3_Config.hpp"

#define _H3API_VERSION_MAJOR_ 1
#define _H3API_VERSION_MINOR_ 0
#define _H3API_VERSION_BUILD_ 0

#define _H3API_VERSION_ (_H3API_VERSION_MAJOR_ * 10000 | _H3API_VERSION_MINOR_ * 100 | _H3API_VERSION_BUILD_)
#define _H3API_VERSION_TEXT_ "H3API version " _H3API_STR_(_H3API_VERSION_MAJOR_) "." _H3API_STR_(_H3API_VERSION_MINOR_) "." _H3API_STR_(_H3API_VERSION_BUILD_)

#endif /* #define _H3_VERSION_HPP_ */