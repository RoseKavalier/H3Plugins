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

#ifndef _H3API_H_
#define _H3API_H_

#pragma once

// * this base file is all you need to include in your projects
// * in order to gain access to all the contents of these headers
// * e.g. #include "H3API.h"

// * Used to apply patches and hooks with the patcher_x86 library
#include "patcher_x86.hpp"
// * Base definitions and common structures
#include "H3Base.h"
// * Various constants stored in namespaces and enums
#include "H3Constants.h"
// * Structures for loaded game assets
#include "H3BinaryItems.h"
// * Structures to create dialogs
#include "H3Dialogs.h"
// * Structures used in the game
#include "H3Structures.h"
// * various non-member h3 functions
#include "H3Functions.h"
// * Strucutres from the random map generator
#include "H3RMG.h"
// * Some structures related to LODs
#include "H3Lod.h"
// * Definitions of some global variables, game functions in a separate header
#include "H3Defines.h"
// * Various functions and structures
#include "H3Varia.h"
// * Read from or write to file using game assets
#include "H3Stream.h"
// * AVL binary search tree for storing and finding data quickly
#include "H3Tree.h"

// * The H3Exception is hidden behind the _H3API_EXCEPTION_ guard.
// * Uncomment the line below to be able to use it.
//#define _H3API_EXCEPTION_

#ifdef _H3API_EXCEPTION_
// * SEH error handler, requires \EHa compiler flag
#include "H3Exception.h"
#endif /* #ifdef _H3API_EXCEPTION_ */

// * The H3Plugins headers are not necessary to be
// * included in your project to get access to the
// * rest of the H3API. They are here simply if you
// * wish to take advantage of shared use they provide.
//#define _H3API_PLUGINS_

#ifdef _H3API_PLUGINS_
#include "Plugins/H3Plugins.hpp"
#endif /* #ifdef _H3API_PLUGINS_ */

#endif /* #define _H3API_H_ */

// * Note to USERS
// *
// * If you are using MSVC 2017+ and are getting errors
// * with the H3API headers, go to your project's
// * Property Pages. Under the C/C++ options, look
// * for "Conformance mode" and set it as "No".
// * It's a bug that is still not resolved in VS.
// *
// * https://developercommunity.visualstudio.com/content/problem/174539/objbaseh-error-when-compiling-with-permissive-and.html