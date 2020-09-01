//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//          In preparing these files, several sources were          //
//            consulted, they are listed in no particular           //
//                          order below.                            //
//                                                                  //
//  Source: https://github.com/potmdehex/homm3tools                 //
//  Author: potmdehex and contributors                              //
//                                                                  //
//  Source: https://github.com/redxu/HoMM3_FA                       //
//  Author: redxu                                                   //
//                                                                  //
//  Source: https://github.com/openhomm/openhomm                    //
//  Author: Ershov Stanislav, Fomin Roman, Akulich Alexander        //
//                                                                  //
//  Source: https://github.com/GrayFace/wog                         //
//  Author: GrayFace and WoG team                                   //
//                                                                  //
//  Source: https://github.com/ethernidee/era                       //
//  Author: Berserker                                               //
//                                                                  //
//  Source: https://github.com/ethernidee/era-editor                //
//  Author: Grayface and Berserker                                  //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=3900      //
//  Author: Slava and GrayFace                                      //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=4583      //
//  Author: gamecreator                                             //
//                                                                  //
//  Thanks: patcher_x86 by baratorch and code therein               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

//
//  ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄
// ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌
// ▐░▌       ▐░▌ ▀▀▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀
// ▐░▌       ▐░▌          ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌
// ▐░█▄▄▄▄▄▄▄█░▌ ▄▄▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌     ▐░▌
// ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌     ▐░▌
// ▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀█░▌▐░█▀▀▀▀▀▀▀▀▀      ▐░▌
// ▐░▌       ▐░▌          ▐░▌▐░▌       ▐░▌▐░▌               ▐░▌
// ▐░▌       ▐░▌ ▄▄▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌▐░▌           ▄▄▄▄█░█▄▄▄▄
// ▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░▌          ▐░░░░░░░░░░░▌
//  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀            ▀▀▀▀▀▀▀▀▀▀▀
//

// * Note to USERS
// *
// * If you are using MSVC 2017+ and are getting errors
// * with the H3API headers, go to your project's
// * Property Pages. Under the C/C++ options, look
// * for "Conformance mode" and set it as "No".
// * It's a bug that is still not resolved in VS.
// *
// * https://developercommunity.visualstudio.com/content/problem/174539/objbaseh-error-when-compiling-with-permissive-and.html

// * H3API may now be used as a header-only style library
// * in which case all you are required to do is:
// * #include "[relative_path]/H3API.hpp"
// *
// * It it now possible as well to compile H3API into a
// * static library, in this case you need to write:
// * #define _H3API_LIBRARY_
// * #include "[relative_path]/H3API.hpp"
// * and link the library to your project.

// *
// * H3API Preprocessor Definitions Overview
// *

// * _H3API_LIBRARY_
// * tells the library that it should only include header files within your project
// * and that you will rely on the static library to access the library's implementation
// * by default the library is header-only.

// * _H3API_OPERATORS_
// * tells the library to replace the new, new[], delete and delete[] operators
// * by the game's own operators.
// * be mindful of hooking too early in the launch process when using this.

// * _H3API_STD_CONVERSIONS_
// * allows conversion between the following formats
// * std::string <<==>> h3::H3String
// * std::vector <<==>> h3::H3Vector

// * _H3API_STD_VECTOR_
// * If you are using Visual Studio 2013 or more recent you can
// * define this preprocessor to use H3StdVector<> which acts as std::vector<>
// * with correct padding and uses H3ObjectAllocator<>

// * _H3API_EXCEPTION_
// * tells the library to include the H3Exception exception handler within your project
// * which is derived from std::exception and may catch SEH errors.
// * your project needs to use /EHa compiler flag to use it.

// * _H3API_DONT_USE_MACROS_
// * tells the library to exclude macros that can pollute the global namespace when defined.
// * these macros are then replaced by typedefs so extra parentheses may be required.
// * if you would like the convenience of switching between both modes, always add parentheses at the end.

// * _H3API_NO_VALIDATION_
// * there are compile-time asserts in H3API to verify
// * structures' sizes and validate some template parameters.
// * define this macro if you do not wish to perform these validations.

// * _H3API_PATCHER_X86_
// * tells the library to include its own "patcher_x86.hpp" header within your project
// * don't use this if you prefer having your own patcher_x86 header.

// * _H3API_PLUGINS_
// * tells the library to include the necessary headers to interact with H3Plugins projects
// * in most cases you won't need this.

#ifndef _H3API_HPP_
#define _H3API_HPP_

#include "h3api/H3_Allocator.hpp"
#include "h3api/H3_Base.hpp"
#include "h3api/H3_BinaryItems.hpp"
#include "h3api/H3_Bitset.hpp"
#include "h3api/H3_Constants.hpp"
#include "h3api/H3_Defines.hpp"
#include "h3api/H3_Dialogs.hpp"
#include "h3api/H3_Functions.hpp"
#include "h3api/H3_Ini.hpp"
#include "h3api/H3_LOD.hpp"
#include "h3api/H3_MapItems.hpp"
#include "h3api/H3_Memory.hpp"
#include "h3api/H3_Path.hpp"
#include "h3api/H3_RMG.hpp"
#include "h3api/H3_Stream.hpp"
#include "h3api/H3_String.hpp"
#include "h3api/H3_Structures.hpp"
#include "h3api/H3_Tree.hpp"
#include "h3api/H3_Vector.hpp"
#include "h3api/H3_Version.hpp"

#ifdef _H3API_EXCEPTION_
// * SEH error handler, requires \EHa compiler flag
#include "h3api/H3_Exception.hpp"
#endif /* #ifdef _H3API_EXCEPTION_ */

#ifdef _H3API_PLUGINS_
// * header files for the H3Plugins project
#include "h3api/H3_Plugins.hpp"
#endif

#ifdef _H3API_PATCHER_X86_
// * include H3API's version of patcher_x86 header
#include "patcher_x86.hpp"
#endif

#ifdef _H3API_OPERATORS_
// * include H3API operators
#include "h3api/H3_Operators.hpp"
#endif

#ifdef _H3API_DEVELOPMENT_
// * includes development files which are not yet available
#include "h3api/H3_Development.hpp"
#endif

#endif /* #define _H3API_HPP_ */