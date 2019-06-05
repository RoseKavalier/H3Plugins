//////////////////////////////////////////////////////////////////////
//																	//
//					Created by RoseKavalier:						//
//					rosekavalierhc@gmail.com						//
//																	//
//		    ***You may use or distribute these files freely			//
//			   so long as this notice remains present.***			//
//																	//
//			In preparing these files, several sources were			//
//			  consulted, they are listed in no particular			//
//							order below.							//
//																	//
//	Source: https://github.com/potmdehex/homm3tools					//
//	Author: potmdehex and contributors								//
//																	//
//	Source: https://github.com/redxu/HoMM3_FA						//
//	Author: redxu													//
//																	//
//	Source: https://github.com/openhomm/openhomm					//
//	Author: Ershov Stanislav, Fomin Roman, Akulich Alexander		//
//																	//
//	Source: https://github.com/GrayFace/wog							//
//	Author: GrayFace and WoG team									//
//																	//
//	Source: https://github.com/ethernidee/era						//
//	Author: Berserker												//
//																	//
//	Source: https://github.com/ethernidee/era-editor				//
//	Author: Grayface and Berserker									//
//																	//
//	Source:	http://wforum.heroes35.net/showthread.php?tid=3900		//
//	Author: Slava and GrayFace										//
//																	//
//	Source: http://wforum.heroes35.net/showthread.php?tid=4583		//
//	Author: gamecreator												//
//																	//
//	Thanks: patcher_x86 by baratorch and code therein				//
//																	//
//////////////////////////////////////////////////////////////////////

#ifndef _H3BASE_H_
#define _H3BASE_H_

#pragma once

#include <Windows.h>
// * Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// * Input / output functions
#include <stdio.h>
// * Prevents some warnings
#define _CRT_SECURE_NO_WARNINGS
// * disable sprintf warning
#pragma warning(disable:4996)

// * Slaps top of car
// * This bad boy can hold just about anything
typedef void(*naked_t)(void);
// * generic typedef to indicate this is a h3 function
typedef unsigned long h3func;
// * 1-byte sized boolean
typedef char BOOL8;
// * Used for unknown structure members
typedef char h3unk;

#ifndef ArraySize
#define ArraySize(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#ifndef PtrAt
// * returns unsigned int at address
#define PtrAt(address) (*(UINT*)(address))
#endif
#ifndef DwordAt
// * returns unsigned int at address
#define DwordAt(address) (*(UINT*)(address))
#endif
#ifndef IntAt
// * returns signed int at address
#define IntAt(address) (*(INT32*)(address))
#endif
#ifndef WordAt
// * returns unsigned short at address
#define WordAt(address) (*(UINT16*)(address))
#endif
#ifndef ShortAt
// * returns signed short at address
#define ShortAt(address) (*(INT16*)(address))
#endif
#ifndef ByteAt
// * returns unsigned char at address
#define ByteAt(address) (*(UINT8*)(address))
#endif
#ifndef CharAt
// * returns signed char at address
#define CharAt(address) (*(INT8*)(address))
#endif
#ifndef FloatAt
// * returns float at address
#define FloatAt(address) (*(FLOAT*)(address))
#endif

#ifndef FuncAt
// * returns address of function at call
// * can also be used to return destination of JMP
#define FuncAt(address) (DwordAt(address + 1) + address + 5)
#endif

#ifndef DEBUG_BREAKPOINT
// * inserts a breakpoint for quick stop using debugger
#define DEBUG_BREAKPOINT __asm int 3
#endif

// model function definitions
#ifndef THISCALL_0
#define THISCALL_0(return_type, address) ((return_type(__thiscall *)(void))address)()
#endif
#ifndef THISCALL_1
#define THISCALL_1(return_type, address, a1) ((return_type(__thiscall *)(UINT))(address))((UINT)(a1))
#endif
#ifndef THISCALL_2
#define THISCALL_2(return_type, address, a1, a2) ((return_type(__thiscall *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef THISCALL_3
#define THISCALL_3(return_type, address, a1, a2, a3) ((return_type(__thiscall *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef THISCALL_4
#define THISCALL_4(return_type, address, a1, a2, a3, a4) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef THISCALL_5
#define THISCALL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef THISCALL_6
#define THISCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef THISCALL_7
#define THISCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef THISCALL_8
#define THISCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef THISCALL_9
#define THISCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef THISCALL_10
#define THISCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef THISCALL_11
#define THISCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef THISCALL_12
#define THISCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef THISCALL_13
#define THISCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef THISCALL_14
#define THISCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef THISCALL_15
#define THISCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef THISCALL_16
#define THISCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef THISCALL_17
#define THISCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__thiscall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif

#ifndef STDCALL_0
#define STDCALL_0(return_type, address) ((return_type(__stdcall *)(void))address)()
#endif
#ifndef STDCALL_1
#define STDCALL_1(return_type, address, a1) ((return_type(__stdcall *)(UINT))(address))((UINT)(a1))
#endif
#ifndef STDCALL_2
#define STDCALL_2(return_type, address, a1, a2) ((return_type(__stdcall *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef STDCALL_3
#define STDCALL_3(return_type, address, a1, a2, a3) ((return_type(__stdcall *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef STDCALL_4
#define STDCALL_4(return_type, address, a1, a2, a3, a4) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef STDCALL_5
#define STDCALL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef STDCALL_6
#define STDCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef STDCALL_7
#define STDCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef STDCALL_8
#define STDCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef STDCALL_9
#define STDCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef STDCALL_10
#define STDCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef STDCALL_11
#define STDCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef STDCALL_12
#define STDCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef STDCALL_13
#define STDCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef STDCALL_14
#define STDCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef STDCALL_15
#define STDCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef STDCALL_16
#define STDCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef STDCALL_17
#define STDCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__stdcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif

#ifndef FASTCALL_0
#define FASTCALL_0(return_type, address) ((return_type(__fastcall *)(void))address)()
#endif
#ifndef FASTCALL_1
#define FASTCALL_1(return_type, address, a1) ((return_type(__fastcall *)(UINT))(address))((UINT)(a1))
#endif
#ifndef FASTCALL_2
#define FASTCALL_2(return_type, address, a1, a2) ((return_type(__fastcall *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef FASTCALL_3
#define FASTCALL_3(return_type, address, a1, a2, a3) ((return_type(__fastcall *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef FASTCALL_4
#define FASTCALL_4(return_type, address, a1, a2, a3, a4) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef FASTCALL_5
#define FASTCALL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef FASTCALL_6
#define FASTCALL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef FASTCALL_7
#define FASTCALL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef FASTCALL_8
#define FASTCALL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef FASTCALL_9
#define FASTCALL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef FASTCALL_10
#define FASTCALL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef FASTCALL_11
#define FASTCALL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef FASTCALL_12
#define FASTCALL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef FASTCALL_13
#define FASTCALL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef FASTCALL_14
#define FASTCALL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef FASTCALL_15
#define FASTCALL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef FASTCALL_16
#define FASTCALL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef FASTCALL_17
#define FASTCALL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__fastcall *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif

#ifndef CDECL_0
#define CDECL_0(return_type, address) ((return_type(__cdecl *)(void))address)()
#endif
#ifndef CDECL_1
#define CDECL_1(return_type, address, a1) ((return_type(__cdecl *)(UINT))(address))((UINT)(a1))
#endif
#ifndef CDECL_2
#define CDECL_2(return_type, address, a1, a2) ((return_type(__cdecl *)(UINT, UINT))(address))((UINT)(a1), (UINT)(a2))
#endif
#ifndef CDECL_3
#define CDECL_3(return_type, address, a1, a2, a3) ((return_type(__cdecl *)(UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3))
#endif
#ifndef CDECL_4
#define CDECL_4(return_type, address, a1, a2, a3, a4) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4))
#endif
#ifndef CDECL_5
#define CDECL_5(return_type, address, a1, a2, a3, a4, a5) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5))
#endif
#ifndef CDECL_6
#define CDECL_6(return_type, address, a1, a2, a3, a4, a5, a6) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6))
#endif
#ifndef CDECL_7
#define CDECL_7(return_type, address, a1, a2, a3, a4, a5, a6, a7) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7))
#endif
#ifndef CDECL_8
#define CDECL_8(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8))
#endif
#ifndef CDECL_9
#define CDECL_9(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9))
#endif
#ifndef CDECL_10
#define CDECL_10(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10))
#endif
#ifndef CDECL_11
#define CDECL_11(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11))
#endif
#ifndef CDECL_12
#define CDECL_12(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12))
#endif
#ifndef CDECL_13
#define CDECL_13(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13))
#endif
#ifndef CDECL_14
#define CDECL_14(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14))
#endif
#ifndef CDECL_15
#define CDECL_15(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15))
#endif
#ifndef CDECL_16
#define CDECL_16(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16))
#endif
#ifndef CDECL_17
#define CDECL_17(return_type, address, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17) ((return_type(__cdecl *)(UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT, UINT))(address))((UINT)(a1), (UINT)(a2), (UINT)(a3), (UINT)(a4), (UINT)(a5), (UINT)(a6), (UINT)(a7), (UINT)(a8), (UINT)(a9), (UINT)(a10), (UINT)(a11), (UINT)(a12), (UINT)(a13), (UINT)(a14), (UINT)(a15), (UINT)(a16), (UINT)(a17))
#endif

// * heapalloc using H3 assets
#define h3_malloc(size)						CDECL_1(UINT32, 0x617492, size)
// * same as h3_malloc but for objects
#define h3_new(obj, number)					CDECL_1(obj*, 0x617492, number * sizeof(obj))
// * heapfree using H3 assets
#define h3_delete(obj)						CDECL_1(UINT, 0x60B0F0, (UINT)obj)
// * memcpy using H3 assets
#define h3_memcpy(dest, src, len)			CDECL_3(void, 0x61AD70, (void*)dest, (void*)src, (size_t)len)
// * heap realloc using H3 assets
#define h3_realloc(obj, new_size)			CDECL_2(UINT, 0x619890, (void*)obj, new_size)
// * converts text to integer using H3 assets
#define h3_atoi(text)						CDECL_1(INT32, 0x6184D9, text)
// * compares two strings up to len characters
#define h3_strnicmp(string1, string2, len)	CDECL_3(INT, 0x626680, string1, string2, len)
// * copies len characters from source to dest
#define h3_strncpy(dest, src, len)			CDECL_3(PCHAR, 0x618FE0, dest, src, len)
// * compares two strings, not-case-sensitive
#define h3_strcmpi(string1, string2)		CDECL_2(BOOL, 0x6197C0, string1, string2)
// * reverses string in buffer, returned to buffer
#define h3_strRev(buffer)					CDECL_1(PCHAR, 0x627690, buffer)
// * FindFirstFileA using H3 assets
#define h3_FindFirstFileA(path, data)		STDCALL_2(HANDLE, PtrAt(0x63A11C), path, &data)
// * FindNextFileA using H3 assets
#define h3_FindNextFileA(handle, data)		STDCALL_2(HANDLE, PtrAt(0x63A120), handle, &data)
// * timeGetTime using H3 assets
#define h3_GetTime							STDCALL_0(DWORD, PtrAt(0x63A354))

// * movement bonuses
#define SPEED_BONUS_BOOTS					IntAt(0x698B50) // usually 600 mp
#define SPEED_BONUS_GLOVES					IntAt(0x698B4C) // usually 300 mp
#define WATER_BONUS_NECKLACE				IntAt(0x698B54) // usually 1000 mp
#define WATER_BONUS_SEA_CAPTAIN				IntAt(0x698B5C) // usually 500 mp
#define SPEED_BONUS_STABLES					IntAt(0x698AE4) // usually 400 mp
#define WATER_BONUS_LIGHTOUSE				WATER_BONUS_SEA_CAPTAIN // same as sea_captain's hat bonus ~500

// * various integer constants
#define h3_ArtifactCount					IntAt(0x44D1A8 + 2)
#define h3_CreatureCount					IntAt(0x5C8046 + 1)
#define h3_HeroCount						IntAt(0x4BD144 + 1)
#define h3_TownCount						(ByteAt(0x4BB0D7 + 2) + 1)
#define h3_SpellCount						ByteAt(0x4A2741 + 2)

// * the game dimensions
#define gameWidth							IntAt(0x403401)
#define gameHeight							IntAt(0x4033FC)

// * game limits for text dialog
#define gameMaxWidth						IntAt(0x415AAB + 2)
#define gameMaxHeight						IntAt(0x415AC1 + 2)

// * the offset in tiles from center of screen to edges
#define gameEdgeHorizontal					CharAt(0x4A8FC0)
#define gameEdgeVertical					CharAt(0x4A8FC5)

#define h3_GamePath							((PCHAR)0x698614)
#define h3_HeroRetreated					ByteAt(0x6985F3)
#define h3_HeroSurrendered					ByteAt(0x697794)
#define h3_AutoSolo							ByteAt(0x691259)
#define h3_HumanID							IntAt(0x6995A4)
#define h3_ActivePlayerBitset				(ByteAt(0x69CD10))

#define h3_MapSize							IntAt(0x6783C8)
#define h3_ColorMode						PtrAt(0x694DB0)
#define h3_BitMode							ByteAt(0x5FA22B) // typical 2, 4 means True graphic mode is used
#define h3_ObjectName(id)					(*(PCHAR*)(0x6A7A54 + 4 * id))
#define h3_MineNames(type)					(*(PCHAR*)(0x6A7538 + 4 * type))
#define h3_TentColors(type)					(*(PCHAR*)(0x6A7588 + 4 * type))
#define h3_TerrainName(type)				(*(PCHAR*)(0x6A5EEC + 4 * type))
#define h3_ExeVersion						PtrAt(0x588479)
#define h3_VersionSOD						0xFFFFE403
#define h3_TextBuffer						((PCHAR)0x697428) // 512 bytes of char buffer to be used
#define h3_NullString						((PCHAR)0x691260)
#define h3_SaveName							((PCHAR)0x69FC88)

#define h3_PrintScreenText(text)			CDECL_3(void, 0x553C40, 0x69D800, "%s", text)
#define h3_CanViewTile(x, y, z)				(FASTCALL_3(UINT8, 0x4F8040, x, y, z) & h3_ActivePlayerBitset)
#define h3_GetCreatureUpgrade(Type)			THISCALL_1(INT32, 0x47AAD0, Type)
#define multiplayer_game					STDCALL_0(BOOL8, 0x4CE950)
#define h3_MessageBox(text)					FASTCALL_12(void, 0x4F6C00, text, 1, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0)
#define h3_MessageBoxChoice(text)			FASTCALL_12(void, 0x4F6C00, text, 2, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0)
#define h3_MessageBoxRMB(text)				FASTCALL_12(void, 0x4F6C00, text, 4, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0)
#define h3_GetCursorPosition(x, y)			STDCALL_2(void, 0x50D700, &x, &y);
#define h3_GetCurrentDirectory(buf, len)	STDCALL_2(int, IntAt(0x63A1A4), len, buf)
#define h3_CreatureHasUpgrade(id)			THISCALL_1(BOOL8, 0x47AA50, id)
#define h3_GetCreatureUpgrade(id)			THISCALL_1(INT32, 0x47AAD0, id)
#define h3_GetDiplomacyPowerFactor(k)		STDCALL_1(INT32, 0x4A7330, k)

#pragma pack(push, 1) // 1 byte alignment

struct H3Numbers
{
	// * add thousands commas to numbers
	static int AddCommas(int num, char *out);
	// * show a number in short scale format with specified number of decimals
	static int MakeReadable(int num, char *out, int decimals = 1);
};

/*
 *
 * Based on code by ideasman42:
 * https://stackoverflow.com/a/24795133
 *
 * from idea by Greg Hewgill:
 * https://stackoverflow.com/a/1449849
 *
 * ever so slightly modifed by RoseKavalier
 *
 */
inline int H3Numbers::AddCommas(int num, char * out)
{
	char buf[32];
	char *src = buf;
	char *dst = out;

	int num_len, commas;

	num_len = sprintf(buf, "%d", num);

	if (*src == '-')
	{
		*dst++ = *src++;
		num_len--;
	}

	for (commas = 2 - num_len % 3; *src; commas = (commas + 1) % 3)
	{
		*dst++ = *src++;
		if (commas == 1)
			*dst++ = ',';
	}
	*--dst = 0;

	return (int)(dst - out);
}

/*
 *
 * Based on AddCommas above
 *
 * Also on idea by Christian Stigen Larsen:
 * https://gist.github.com/cslarsen/1870641
 * but does not require double or <math.h>
 *
 * This function returns an integer in readable format
 *
 * e.g.
 *
 * formatReadable(1998795, buf, 3)
 * reads as 199.879M
 *
 * formatReadable(1998795, buf, 2)
 * reads as 199.88M
 *
 * formatReadable(1998795, buf, 1)
 * reads as 199.9M
 *
 * formatReadable(1998795, buf, 0)
 * reads as 200M
 *
 */
inline int H3Numbers::MakeReadable(int num, char * out, int decimals)
{
#define RN_MIN_VALUE 10000
	int d, power, plus, div, dec;
	char buf[32];

	// * work with positives
	int m = num < 0 ? -num : num;

	// * if smaller than specified value, print regular number
	if (m < RN_MIN_VALUE)
		return sprintf(out, "%d", num);

	// * round the number to required precision
	dec = min(decimals, 3);
	plus = 500;
	div = 1000;
	for (int i = 0; i < dec; i++)
	{
		plus /= 10;
		div /= 10;
	}
	d = power = 0;
	while (m >= 1000)
	{
		d = m;
		m /= 1000;
		power++;
	}
	// * rounding, same idea as f = round(f + 0.5)
	d = (d + plus) / div * div;

	// * print template
	int len = sprintf(buf, "%d", d);
	int c = 2 - len % 3;

	char *dst = out;
	char *src = buf;

	// * leading negative
	if (num < 0)
		*dst++ = '-';

	// * copy source to destination
	while (*src)
	{
		*dst++ = *src++;
		if (c == 1)
		{
			// * if decimals are required
			if (dec)
			{
				*dst++ = '.';
				// * add required precision
				for (int i = 0; i < dec; i++)
					*dst++ = *src++;
			}
			break;
		}
		c = (c + 1) % 3;
	}
	// * add proper ending
	char scale[] = { 0, 'k', 'M', 'B' };
	*dst++ = scale[power];
	*dst = 0;

	return (int)(dst - out);
}

// * a vector following the H3 format
template<typename _Elem> struct H3Vector
{
protected:
	BOOL _init; // useless
public:
	// * the first item, also start of list
	_Elem *first;
	// * the end of last item
	_Elem *end;
	// * end of allocated memory
	_Elem *capacity;

	H3Vector() { Init(); }
	~H3Vector() { Deref(); }
	// * ~constructor
	void Init();
	// * ~destructor.
	void Deref();
	// * If list is empty
	BOOL IsEmpty();
	// * If vector is full
	BOOL IsFull();
	// * the number of items
	INT32 Count();
	// * the maximum number of items
	INT32 CountMax();
	// * calculates size
	UINT32 Size();
	// * calculates allocated size
	UINT32 SizeAllocated();
	// * removes the last item
	void RemoveLast();
	// * empties list
	void RemoveAll();
	// * Adds item
	_Elem* Add(_Elem & item);
	// * Adds only 1 item, expands by only 1
	_Elem* AddOne(_Elem & item);
	// * only for size 4 or references, H3 code
	void AddSize4(_Elem item);
	// * increases capacity
	BOOL Expand();
	// * returns First item
	_Elem *First();
	// * returns Last item
	_Elem *Last();
	// * Add one item to end
	_Elem* Append(_Elem & item) { return Add(item); }
	// * Add a single item, expanding by 1
	_Elem* Push(_Elem & item) { return AddOne(item); }
	// * Removes last item and returns reference to it
	_Elem* Pop();
	// * Returns item at position, can be negative to get from end
	_Elem* At(INT32 pos);
	// * remove one item, list shifts left
	BOOL Remove(INT32 pos);
	// * remove range, list shifts left
	BOOL Remove(INT32 fromPos, INT32 toPos);

	// * returns pointer to element at pos, positive only
	_Elem* operator[](INT32 pos);
	// * Adds item to end of list
	_Elem* operator+=(_Elem & item);
};

// * a string following the H3 format
struct H3String
{
protected:
	BOOL _init; // useless
	PCHAR str;
	INT32 length;
	INT32 capacity;

	void NullTerminate() { *End() = 0; }
	BOOL Realloc(int newSize);
public:
	// * constructor
	H3String();
	// * constructor and Assign(msg)
	H3String(PCHAR msg);
	// * constructor and Assign(msg, len)
	H3String(PCHAR msg, INT32 len);
	// * constructor and Assign(h3str)
	H3String(H3String *h3str);
	// * constructor and Assign(ch)
	H3String(CHAR ch);
	// * destructor
	~H3String();
	// * H3 constructor
	void Init();
	// * H3 destructor
	void Dereference();
	// * returns beginning of string
	PCHAR Begin() { return str; }
	// * returns end of string, on null char
	PCHAR End() { return str + length; }
	// * returns the last char of string
	CHAR Last() { return str[length - 1]; }
	// * sets string as mes
	H3String* Assign(PCHAR mes, INT32 len);
	// * Assign(mes, strlen(mes))
	H3String* Assign(PCHAR mes);
	// * sets *string as ch
	H3String* Assign(CHAR ch);
	// * sets &string as h3string
	H3String* Assign(H3String *h3string);
	// * sets string as h3string
	H3String* Assign(H3String &h3string);
	// * prints number to string
	H3String* Assign(int number);
	// * sets new capacity, 0x1F is default
	BOOL Reserve(INT32 newSize = 0x1E);
	// * returns constant char* string
	const PCHAR String() { return str; }
	// * current length of string
	INT32 Length() { return length; }
	// * capacity of string
	INT32 MaxLength() { return capacity; }
	// * Sets capacity if larger, otherwise shortens
	BOOL SetLength(INT32 len);
	// * Adds mes to end of string
	BOOL Append(PCHAR mes, INT32 len);
	// * Adds h3string to end of string
	BOOL Append(H3String & h3string);
	// * Adds h3string to end of string
	BOOL Append(H3String *h3string);
	// * Adds number to string
	H3String* Append(int number);
	// * Adds ch to end of string
	BOOL Append(CHAR ch);
	// * Finds position of first ch
	INT FindFirst(CHAR ch);
	// * returns string offset at pos
	PCHAR At(INT32 pos);
	// * Removes all instances of ch
	INT32 Remove(CHAR ch);
	// * Removes all instances of substring
	INT32 Remove(PCHAR substr);
	// * Removes all instances of substring
	INT32 Remove(PCHAR substr, INT32 sublen);
	// * Remove chars from start to end
	INT32 Remove(INT32 start, INT32 end);
	// * sets string to all 0s
	void Erase();
	// * memcmp ~ case sensitive
	BOOL Equals(PCHAR msg, INT32 len);
	// * Equals(msg, strlen(msg))
	BOOL Equals(PCHAR msg);
	// * strcmpi ~ not case-sensitive
	BOOL Equals_i(PCHAR msg);
	// * memcmp ~ case sensitive
	BOOL Equals(H3String *h3string);
	// * Ends string at position
	BOOL Truncate(INT32 position);
	// * Assign(h3str)
	H3String* operator=(H3String &h3str);
	// * Assign(h3str)
	H3String* operator=(H3String *h3str);
	// * Assign(msg)
	H3String* operator=(PCHAR msg);
	// * Assign(ch)
	H3String* operator=(CHAR ch);
	// * Append(h3str)
	H3String* operator+=(H3String &h3str);
	// * Append(h3str)
	H3String* operator+=(H3String *h3str);
	// * Append(msg)
	H3String* operator+=(PCHAR msg);
	// * Append(ch)
	H3String* operator+=(CHAR ch);
	// * Equals(h3str)
	BOOL operator==(H3String *h3str);
	// * Equals(str)
	BOOL operator==(PCHAR str);
	// * The number of times this string is referenced - avoids deletion from destructor in references
	INT8 References();
	// * Increase the number of references to this string
	void IncreaseReferences();

	BOOL FormattedNumber(int number);
	BOOL ScaledNumber(int number, int decimals = 1);

	/*
	*
	* Non-member functions
	*
	*/

	// * Adds two H3String into one H3String
	friend H3String operator+(H3String &lhs, H3String &rhs);
	// * Adds H3String and char into one H3String
	friend H3String operator+(H3String &lhs, CHAR rhs);
	// * Adds one char and H3String into one H3String
	friend H3String operator+(CHAR lhs, H3String &rhs);
	// * Adds one H3String and char* into one H3String
	friend H3String operator+(H3String &lhs, PCHAR rhs);
	// * Adds one char* and H3String into one H3String
	friend H3String operator+(PCHAR lhs, H3String &rhs);
};

// * dword used as bitfield
// * can be used as an array of bitfields
struct H3Bitfield
{
	UINT32 bf;

	// * returns whether bit at position is set or not
	// * position can exceed the scope of bitfield, meaning greater than 32 bits
	BOOL GetState(INT32 position)
	{
		INT32 index = position >> 5;
		INT32 pos = position & 0x1F;
		INT32 value = 1 << pos;
		return ((&bf)[index]) & value;
	}
	// * sets bit at position to one or off
	// * position can exceed the scope of bitfield, meaning greater than 32 bits
	void SetState(INT32 position, BOOL state)
	{
		INT32 index = position >> 5;
		INT32 pos = position & 0x1F;
		INT32 value = 1 << pos;
		if (state)
			((&bf)[index]) |= value;
		else
			((&bf)[index]) &= ~value;
	}
};

// * HDmod's format for ini files lines
struct HDIniEntry // size 0xD ~ 13
{
	union
	{
		PCHAR text;
		UINT32 value;
	}data;
	enum eType : BYTE
	{
		iniValue = 2,
		iniText = 3,
		iniKey = 4
	};
	eType entryType;
	DWORD entryCount;
	PCHAR uselessText; // like " = ", end of line, ...

	PCHAR GetText()
	{
		if (entryType == iniValue)
			return h3_NullString;
		return data.text;
	}
};

// * HDmod's format for ini files
struct HDIni
{
	HDIniEntry **entries;
	INT32 lineEntries;
	h3unk _f_08[4];
	CHAR name[8]; // unknown length

	HDIniEntry ** FindEntry(PCHAR key)
	{
		HDIniEntry **e = entries;
		int i = lineEntries;

		while (i > 0)
		{
			HDIniEntry *c = *e;
			if (c->entryType == c->iniKey)
			{
				if (h3_strcmpi(key, c->data.text) == 0)
					return e;

				i -= (c->entryCount + 1);
				e += (c->entryCount + 1);
			}
			else
			{
				i--;
				e++;
			}
		}
		return NULL;
	}
};

#pragma pack(pop)

// * H3String member function definitions


inline H3String * H3String::Assign(CHAR ch)
{
	if (String() || Realloc(1))
	{
		*Begin() = ch;
		SetLength(1);
	}
	return this;
}

inline H3String * H3String::Assign(H3String & h3string)
{
	if (h3string.Begin())
		Assign(h3string.String(), h3string.Length());
	return this;
}

inline H3String * H3String::Assign(H3String * h3string)
{
	if (h3string)
		Assign(h3string->Begin(), h3string->Length());
	return this;
}

inline H3String * H3String::Assign(int number)
{
	if (str || Reserve())
		length = sprintf(str, "%d", number);
	return this;
}

inline BOOL H3String::Reserve(INT32 newSize)
{
	return Realloc(newSize);
}

inline BOOL H3String::Realloc(int newSize)
{
	return THISCALL_2(BOOL, 0x404B80, this, newSize);
}

inline H3String::H3String()
{
	str = NULL;
	length = 0;
	capacity = 0;
}

inline H3String::H3String(PCHAR msg)
{
	H3String();
	Assign(msg);
}

inline H3String::H3String(PCHAR msg, INT32 len)
{
	H3String();
	Assign(msg, len);
}

inline H3String::H3String(H3String * h3str)
{
	H3String();
	Assign(h3str);
}

inline H3String::H3String(CHAR ch)
{
	H3String();
	Assign(ch);
}

inline H3String::~H3String()
{
	Dereference();
}

inline void H3String::Init()
{
	THISCALL_2(void, 0x404130, this, 0);
}

inline void H3String::Dereference()
{
	THISCALL_1(void, 0x4040F0, this);
}

inline H3String * H3String::Assign(PCHAR mes)
{
	return Assign(mes, strlen(mes));
}

inline H3String * H3String::Assign(PCHAR mes, INT32 len)
{
	return THISCALL_3(H3String*, 0x404180, this, mes, len);
}

inline BOOL H3String::SetLength(INT32 len)
{
	if (len > MaxLength())
		return Realloc(len);

	length = len;
	NullTerminate();
	return TRUE;
}

inline BOOL H3String::Append(PCHAR mes, INT32 len)
{
	if (!mes || len <= 0)
		return FALSE;

	if (Length() + len >= MaxLength() && !Realloc(Length() + len))
		return FALSE;

	PCHAR end = End();
	PCHAR m = mes;

	while (*m)
		*end++ = *m++;
	*end = 0;
	length += len;
	return TRUE;
}

inline BOOL H3String::Append(H3String & h3string)
{
	if (!h3string.Begin())
		return FALSE;
	return Append(h3string.Begin(), h3string.Length());
}

inline BOOL H3String::Append(H3String * h3string)
{
	if (!h3string)
		return FALSE;
	return Append(h3string->Begin(), h3string->Length());
}

inline H3String * H3String::Append(int number)
{
	if (Length() + 12 < MaxLength() || Realloc(Length() + 12))
		sprintf(End(), "%d", number);
	return this;
}

inline BOOL H3String::Append(CHAR ch)
{
	if (!ch) // null char already done
		return TRUE;

	if (Length() + 1 >= MaxLength() && !Realloc(Length() + 1))
		return FALSE;

	PCHAR end = End();
	*end = ch;
	*++end = 0;
	length++;
	return TRUE;
}

inline INT H3String::FindFirst(CHAR ch)
{
	PCHAR f = Begin();
	int pos = 0;
	while (*f)
	{
		if (*f == ch)
			return pos;
		f++;
		pos++;
	}
	return -1;
}

inline INT32 H3String::Remove(CHAR ch)
{
	if (!str || *str == 0) // no text or NULL string
		return 0;

	INT32 len = Length();

	char *src, *dst;
	for (src = dst = str; *src && length; src++)
	{
		if (*src == ch) // skip over this char
		{
			++src;
			length--;
		}
		*dst = *src;
		dst++;
	}
	*dst = 0; // place end character

	return len - Length();
}

inline INT32 H3String::Remove(PCHAR substr)
{
	return Remove(substr, strlen(substr));
}

inline INT32 H3String::Remove(PCHAR substr, INT32 sublen)
{
	PCHAR s, copyFrom, copyEnd;
	if (NULL == (s = strstr(str, substr)))
		// no match
		return 0;
	INT rem = length;
	copyFrom = s + sublen;
	while (NULL != (copyEnd = strstr(copyFrom, substr)))
	{
		memmove(s, copyFrom, copyEnd - copyFrom);
		s += copyEnd - copyFrom;
		copyFrom = copyEnd + sublen;
	}
	memmove(s, copyFrom, 1 + strlen(copyFrom));
	length = strlen(str);
	return rem - length;
}

inline PCHAR H3String::At(INT32 pos)
{
	if (Begin() && pos >= 0)
		return str + min(pos, Length());
	return NULL;
}

inline INT32 H3String::Remove(INT32 start, INT32 end)
{
	INT32 n = end - start;
	if (n <= 0)
		return 0;

	PCHAR dest, src;
	dest = At(start);
	src = At(end);
	if (!dest || !src)
		return 0;

	while (*src)
		*dest++ = *src++;

	SetLength(Length() - n);
	NullTerminate();
	return n;
}

inline void H3String::Erase()
{
	memset(Begin(), 0, Length());
	length = 0;
}

inline BOOL H3String::Equals(PCHAR msg, INT32 len)
{
	if (!msg || Length() != len)
		return FALSE;

	return memcmp(msg, Begin(), Length()) == 0;
}

inline BOOL H3String::Equals(PCHAR msg)
{
	if (!msg)
		return FALSE;
	return Equals(msg, strlen(msg));
}

inline BOOL H3String::Equals_i(PCHAR msg)
{
	if (!msg)
		return FALSE;
	return (h3_strcmpi(msg, String()) == 0);
}

inline BOOL H3String::Equals(H3String * h3string)
{
	if (!h3string)
		return FALSE;
	return Equals(h3string->Begin(), h3string->Length());
}

inline BOOL H3String::Truncate(INT32 position)
{
	if (position < Length() && String())
	{
		length = position;
		NullTerminate();
	}
	return FALSE;
}

inline H3String * H3String::operator=(H3String & h3str)
{
	return this->Assign(h3str);
}

inline H3String * H3String::operator=(H3String * h3str)
{
	return this->Assign(h3str);
}

inline H3String * H3String::operator+=(H3String & h3str)
{
	Append(h3str);
	return this;
}

inline H3String * H3String::operator+=(H3String * h3str)
{
	Append(h3str);
	return this;
}

inline H3String * H3String::operator+=(PCHAR msg)
{
	Append(msg, strlen(msg));
	return this;
}

inline H3String * H3String::operator+=(CHAR ch)
{
	Append(ch);
	return this;
}

inline BOOL H3String::operator==(H3String * h3str)
{
	return Equals(h3str);
}

inline BOOL H3String::operator==(PCHAR str)
{
	return Equals(str);
}

inline INT8 H3String::References()
{
	return str[-1];
}

inline void H3String::IncreaseReferences()
{
	str[-1]++;
}

inline H3String * H3String::operator=(PCHAR msg)
{
	Assign(msg);
	return this;
}

inline H3String * H3String::operator=(CHAR ch)
{
	Assign(ch);
	return this;
}

inline BOOL H3String::FormattedNumber(int number)
{
	if (!str && !Reserve())
		return FALSE;
	length = H3Numbers::AddCommas(number, str);

	return TRUE;
}

inline BOOL H3String::ScaledNumber(int number, int decimals)
{
	if (!str && !Reserve())
		return FALSE;
	length = H3Numbers::MakeReadable(number, str, decimals);
	return TRUE;
}

inline H3String operator+(H3String & lhs, H3String & rhs)
{
	H3String ans;
	if (!ans.Reserve(lhs.Length() + rhs.Length()))
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

inline H3String operator+(H3String & lhs, CHAR rhs)
{
	H3String ans;
	if (!ans.Reserve(lhs.Length()) + 1)
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

inline H3String operator+(CHAR lhs, H3String & rhs)
{
	H3String ans;
	if (!ans.Reserve(rhs.Length()) + 1)
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

inline H3String operator+(PCHAR lhs, H3String & rhs)
{
	H3String ans;
	int slen = strlen(lhs);
	if (!ans.Reserve(rhs.Length()) + slen)
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

inline H3String operator+(H3String & lhs, PCHAR rhs)
{
	H3String ans;
	int slen = strlen(rhs);
	if (!ans.Reserve(lhs.Length()) + slen)
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

// * H3Vector member function definitions

template<typename _Elem>
inline void H3Vector<_Elem>::Init()
{
	first = NULL;
	end = NULL;
	capacity = NULL;
}

template<typename _Elem>
inline void H3Vector<_Elem>::Deref()
{
	if (first)
		h3_delete(first);
	first = NULL;
	end = NULL;
	capacity = NULL;
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::IsEmpty()
{
	if (!first || first == end)
		return TRUE;
	return FALSE;
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::IsFull()
{
	if (end == capacity)
		return TRUE;
	return FALSE;
}

template<typename _Elem>
inline INT32 H3Vector<_Elem>::Count()
{
	return end - first;
}

template<typename _Elem>
inline INT32 H3Vector<_Elem>::CountMax()
{
	return capacity - first;
}

template<typename _Elem>
inline UINT32 H3Vector<_Elem>::Size()
{
	return (UINT32)end - (UINT32)first;
}

template<typename _Elem>
inline UINT32 H3Vector<_Elem>::SizeAllocated()
{
	return (UINT32)capacity - (UINT32)first;
}

template<typename _Elem>
inline void H3Vector<_Elem>::RemoveLast()
{
	if (end > first)
		end--;
}

template<typename _Elem>
inline void H3Vector<_Elem>::RemoveAll()
{
	end = first;
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::Add(_Elem & item)
{
	if (!first || IsFull())
	{
		if (!Expand())
			return NULL; // failed
	}
	h3_memcpy(end, &item, sizeof(_Elem));
	end++;
	return end - 1;  // returns position where it was added
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::AddOne(_Elem & item)
{
	if (!first)
	{
		//UINT32 size = sizeof(_Elem);
		//first = (_Elem*)h3_malloc(size);
		first = h3_new(_Elem, 1);
		end = first;
		if (first)
			capacity = first + 1;
		else
			return FALSE;
	}
	else if (IsFull())
	{
		UINT32 size = Size();
		UINT32 newSize = size + sizeof(_Elem);

		_Elem *temp = (_Elem*)h3_realloc(first, newSize);

		if (temp)
		{
			first = temp;
			end = (_Elem*)((UINT32)first + size);
			capacity = (_Elem*)((UINT32)first + newSize);
		}
		else
			return FALSE;
	}
	h3_memcpy(end, &item, sizeof(_Elem));
	end++;
	return end - 1;  // returns position where it was added
}

template<typename _Elem>
inline void H3Vector<_Elem>::AddSize4(_Elem item)
{
	THISCALL_4(void, 0x5FE2D0, this, end, 1, &item);
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::Expand()
{
#define MIN_ELEMENTS 10
#define SIZE_MULTIPLIER 2

	if (!first)
	{
		//UINT32 size = MIN_ELEMENTS * sizeof(_Elem);
		//first = (_Elem*)h3_malloc(size);
		first = h3_new(_Elem, MIN_ELEMENTS);
		end = first;
		if (first)
			capacity = first + MIN_ELEMENTS;
		return first != NULL;
	}
	else
	{
		UINT32 size = SizeAllocated();
		UINT32 cSize = Size();
		UINT32 newSize = size * SIZE_MULTIPLIER;
		_Elem *temp = (_Elem*)h3_realloc(first, newSize);
		if (temp)
		{
			first = temp;
			end = (_Elem*)((UINT32)first + cSize);
			capacity = (_Elem*)((UINT32)first + newSize);
			return TRUE;
		}
	}
	return FALSE;
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::First()
{
	return first;
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::Last()
{
	return end - 1;
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::Pop()
{
	end--;
	return end;
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::At(INT32 pos)
{
	INT32 n;
	if (pos >= 0)
		n = min(pos, Count() - 1);
	else
	{
		int c = Count();
		n = min(-(n), c);
		n = c - n;
	}
	return this[n];
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::Remove(INT32 pos)
{
	return Remove(pos, pos);
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::Remove(INT32 fromPos, INT32 toPos)
{
	if (fromPos < 0 || toPos < 0 || toPos < first)
		return FALSE;
	INT32 num = Count();
	if (fromPos >= num)
		return FALSE;

	INT32 to = min(num - 1, toPos); // don't go further than end!
	INT32 r = to - fromPos + 1; // number removed

	_Elem* rem = first + fromPos;
	_Elem* remEnd = rem + r;

	size_t copyLen = (size_t)end - (size_t)remEnd;
	memmove((void*)rem, (void*)remEnd, copyLen);
	end -= r;
	return TRUE;
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::operator[](INT32 pos)
{
	return first + pos;
}

template<typename _Elem>
inline _Elem* H3Vector<_Elem>::operator+=(_Elem & item)
{
	return Add(item);
}

#endif /* #define _H3BASE_H_ */