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

#ifndef _H3BASE_H_
#define _H3BASE_H_

#pragma once

// * Change this value to 1 if you would like to use some additional safety checks in the H3API (in development)
#define H3API_SAFE 0

#include <Windows.h>
// * Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// * Input / output functions
#include <stdio.h>
// * defines some keywords: and [&&], or [||], not [!], xor [^] ...
#include <iso646.h>
// * Prevents some warnings
#define _CRT_SECURE_NO_WARNINGS
// * disable sprintf warning
#pragma warning(disable:4996)

// * true if your IDE version is C++11 compatible
#define CPLUSPLUS11 (__cplusplus > 199711L || (_MSC_VER && _MSC_VER >= 1900))

#ifndef CPLUSPLUS11
// * nullptr was added with C++11
#define nullptr NULL
// * constexpr was added with C++11
#define constexpr const
#endif

// * Slaps top of car
// * This bad boy can hold just about anything
typedef void			(*naked_t)();
// * generic typedef to indicate this is a h3 function
typedef unsigned long	h3func;
// * 1-byte sized boolean
typedef char			BOOL8;
// * Used for unknown structure members
typedef char			h3unk;

// * for uniformity's sake
#ifdef VOID
#undef VOID
// * void type
typedef void VOID;
#else
// * void type
typedef void VOID;
#endif

// * typedef safety declarations
// * no checks are needed here based on C++03 Standard 7.1.3 typedef specifier
// * https://stackoverflow.com/questions/8594954/repeated-typedefs-invalid-in-c-but-valid-in-c?answertab=votes#tab-top
typedef int					INT,	*PINT;
typedef unsigned int		UINT,	*PUINT;
typedef signed char         INT8,	*PINT8;
typedef signed short        INT16,	*PINT16;
typedef signed int          INT32,	*PINT32;
typedef signed __int64      INT64,	*PINT64;
typedef unsigned char       UINT8,	*PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned __int64    UINT64, *PUINT64;
typedef float				FLOAT;
typedef FLOAT				*PFLOAT;
typedef double				DOUBLE;
typedef DOUBLE				*PDOUBLE;
typedef char				CHAR;
typedef CHAR				*PCHAR;
typedef unsigned char		UCHAR;
typedef UCHAR				*PUCHAR;
typedef unsigned char		BYTE;
typedef BYTE				*PBYTE;
typedef unsigned short		WORD;
typedef WORD				*PWORD;
typedef unsigned long		DWORD;
typedef DWORD				*PDWORD;
typedef const char			*LPCSTR;
typedef void				*PVOID;

#ifndef ArraySize
// * returns number of elements in an array
#define ArraySize(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

#ifndef Abs
// * returns absolute value of number
#define Abs(num) (num >= 0 ? num : (-num))
#endif

#ifndef StrAt
// * returns c-string at address
#define StrAt(address) (*(LPCSTR*)(address))
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

// * model function definitions
#pragma region THISCALL_DECLARATIONS
#ifndef THISCALL_0
#define THISCALL_0(return_type, address) ((return_type(__thiscall *)(VOID))address)()
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
#pragma endregion

#pragma region STDCALL_DECLARATIONS
#ifndef STDCALL_0
#define STDCALL_0(return_type, address) ((return_type(__stdcall *)(VOID))address)()
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
#pragma endregion

#pragma region FASTCALL_DECLARATIONS
#ifndef FASTCALL_0
#define FASTCALL_0(return_type, address) ((return_type(__fastcall *)(VOID))address)()
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
#pragma endregion

#pragma region CDECL_DECLARATIONS
#ifndef CDECL_0
#define CDECL_0(return_type, address) ((return_type(__cdecl *)(VOID))address)()
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
#pragma endregion

#pragma region VA_DECLARATIONS
#ifndef STDCALL_VA
#define STDCALL_VA(return_type, address, a1, ...) ((return_type(__stdcall *)(UINT, ...))(address))((UINT)(a1), __VA_ARGS__)
#endif

#ifndef THISCALL_VA
#define THISCALL_VA(return_type, address, a1, ...) ((return_type(__thiscall *)(UINT, ...))(address))((UINT)(a1), __VA_ARGS__)
#endif

#ifndef FASTCALL_VA
#define FASTCALL_VA(return_type, address, a1, ...) ((return_type(__fastcall *)(UINT, ...))(address))((UINT)(a1), __VA_ARGS__)
#endif

#ifndef CDECL_VA
#define CDECL_VA(return_type, address, a1, ...) ((return_type(__cdecl *)(UINT, ...))(address))((UINT)(a1), __VA_ARGS__)
#endif

#ifndef CDECL_VA2
#define CDECL_VA2(return_type, address, a1, a2, ...) ((return_type(__cdecl *)(UINT, UINT, ...))(address))((UINT)(a1), (UINT)(a2), __VA_ARGS__)
#endif

#pragma endregion


// * movement bonuses
#define SPEED_BONUS_BOOTS					IntAt(0x698B50) // usually 600 mp
#define SPEED_BONUS_GLOVES					IntAt(0x698B4C) // usually 300 mp
#define WATER_BONUS_NECKLACE				IntAt(0x698B54) // usually 1000 mp
#define WATER_BONUS_SEA_CAPTAIN				IntAt(0x698B5C) // usually 500 mp
#define SPEED_BONUS_STABLES					IntAt(0x698AE4) // usually 400 mp
#define WATER_BONUS_LIGHTHOUSE				WATER_BONUS_SEA_CAPTAIN // same as sea_captain's hat bonus ~500

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

#define h3_GamePath							((LPCSTR)0x698614)
#define h3_HeroRetreated					ByteAt(0x6985F3)
#define h3_HeroSurrendered					ByteAt(0x697794)
#define h3_AutoSolo							ByteAt(0x691259)
#define h3_HumanID							IntAt(0x6995A4)
#define h3_ActivePlayerBitset				(ByteAt(0x69CD10))

#define h3_MapSize							IntAt(0x6783C8)
#define h3_ColorMode						PtrAt(0x694DB0)
#define h3_BitMode							ByteAt(0x5FA228 + 3) // typical 2, 4 means True graphic mode is used
#define h3_ObjectName(id)					StrAt(0x6A7A54 + 4 * id)
#define h3_MineNames(type)					StrAt(0x6A7538 + 4 * type)
#define h3_TentColors(type)					StrAt(0x6A7588 + 4 * type)
#define h3_TerrainName(type)				StrAt(0x6A5EEC + 4 * type)
#define h3_ExeVersion						PtrAt(0x588479)
#define h3_VersionSOD						0xFFFFE403
#define h3_TextBuffer						((PCHAR)0x697428) // 512 bytes of char buffer to be used
#define h3_NullString						((LPCSTR)0x691260)
#define h3_SaveName							((PCHAR)0x69FC88)

// * checks for SoD, HotA and WoG/ERA
class H3Version
{
	enum GameVersion : INT
	{
		UNKNOWN = -1,
		ROE,
		SOD,
		SOD_POLISH_GOLD,
		HOTA,
		ERA,
		WOG,
	};
	GameVersion m_version;
public:
	H3Version()
	{
		IMAGE_DOS_HEADER* pDOSHeader = (IMAGE_DOS_HEADER*)0x400000;
		IMAGE_NT_HEADERS* pNTHeaders = (IMAGE_NT_HEADERS*)((BYTE*)pDOSHeader + pDOSHeader->e_lfanew);
		DWORD entry = pNTHeaders->OptionalHeader.AddressOfEntryPoint;

		// * checks entry point of exe
		switch (entry)
		{
		case 0x19A0AE: // 1.0
			m_version = ROE;
			break;
		case 0x21A884:
			m_version = SOD;
			break;
		case 0x21AB84:
			m_version = SOD_POLISH_GOLD;
			break;
		case 0x239C00:
			m_version = HOTA;
			break;
		case 0x301000:
			m_version = ERA;
			break;
		case 0x3017B0:
			m_version = WOG;
			break;
		default:
			m_version = UNKNOWN;
		}
	}

	const GameVersion version() const { return m_version; }

	BOOL roe()  const { return version() == ROE;  }
	BOOL sod()  const { return version() == SOD;  }
	BOOL hota() const { return version() == HOTA; }
	BOOL era()  const { return version() == ERA;  }
	BOOL wog()  const { return version() == WOG;  }
};

// * heap realloc using H3 assets
inline PVOID F_realloc(PVOID obj, UINT new_size)
{
	return CDECL_2(PVOID, 0x619890, obj, new_size);
}

// * calloc using h3 assets
inline PVOID F_calloc(UINT count, UINT size = 1)
{
	return CDECL_2(PVOID, 0x61AA61, count, size);
}

// * heapalloc using H3 assets
inline PVOID F_malloc(UINT size)
{
	return CDECL_1(PVOID, 0x617492, size);
}

// * heapfree using H3 assets
inline VOID F_delete(PVOID obj)
{
	if (obj)
		CDECL_1(VOID, 0x60B0F0, (PVOID)obj);
}

// * memcpy using H3 assets
inline VOID F_memcpy(PVOID dest, PVOID src, UINT len)
{
	CDECL_3(VOID, 0x61AD70, dest, src, len);
}

// * compares two strings, not-case-sensitive
inline INT F_strcmpi(LPCSTR string1, LPCSTR string2)
{
	return CDECL_2(INT, 0x6197C0, string1, string2);
}

// * sets dest to value
inline PVOID F_memset(PVOID dest, UINT value, UINT len)
{
	return CDECL_3(PVOID, 0x61B7E0, dest, value, len);
}

// * vsprintf using h3 assets
// * you need to handle va_list yourself to use this!
// * otherwise use F_sprintf which will do both
inline INT F_vsprintf(PCHAR buffer, LPCSTR format, va_list args)
{
	return CDECL_3(INT, 0x6190DE, buffer, format, args);
}

// * sprintf using h3 assets and buffer
inline INT F_sprintf(LPCSTR format, ...)
{
	va_list args;
	va_start(args, format);
	INT r = F_vsprintf(h3_TextBuffer, format, args);
	va_end(args);
	return r;
}

// * The new, new[], delete and delete[] operators are
// * placed behind the _H3API_OPERATORS_ guards.
// * If you want to use them in your project, you
// * should first uncomment the last line of this paragraph
// * #define _H3API_OPERATORS_
// * * * * * * * * * NOTE * * * * * * * *
// * If defined, H3Vector will use the new[] and delete[] operators
// * gaining greater autonomy to use
// * appropriate constructors and destructors
#define _H3API_OPERATORS_

#ifdef _H3API_OPERATORS_

#pragma warning(push)
#pragma warning(disable:4595) /* disable 'operator new': non-member operator new or delete functions may not be declared inline warning */

//* new operator using h3 assets
inline PVOID operator new(size_t sz)
{
	return F_malloc(sz);
}

// * delete operator using h3 assets
inline VOID operator delete(PVOID ptr)
{
	if (ptr)
		F_delete(ptr);
}

// * new[] operator using h3 assets
inline PVOID operator new[](size_t sz)
{
	return F_malloc(sz);
}

// * delete[] operator using h3 assets
inline VOID operator delete[](PVOID ptr)
{
	if (ptr)
		F_delete(ptr);
}

#pragma warning(pop) /* #pragma warning(disable:4595) */

#endif /* _H3API_OPERATORS_ */

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
 * ever so slightly modified by RoseKavalier
 *
 */
inline int H3Numbers::AddCommas(const int num, char * out)
{
	char buf[32];
	char *src = buf;
	char *dst = out;

	int num_len = sprintf(buf, "%d", num);

	if (*src == '-')
	{
		*dst++ = *src++;
		num_len--;
	}

	for (int commas = 2 - num_len % 3; *src; commas = (commas + 1) % 3)
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
inline int H3Numbers::MakeReadable(const int num, char * out, const int decimals)
{
	constexpr INT RN_MIN_VALUE = 10000;
	int power;
	char buf[32];

	// * work with positives
	int m = num < 0 ? -num : num;

	// * if smaller than specified value, print regular number
	if (m < RN_MIN_VALUE)
		return sprintf(out, "%d", num);

	// * round the number to required precision
	int dec = min(decimals, 3);
	int plus = 500;
	int div = 1000;
	for (int i = 0; i < dec; i++)
	{
		plus /= 10;
		div /= 10;
	}
	int d = power = 0;
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
	_Elem *m_first;
	// * the end of last item
	_Elem *m_end;
	// * end of allocated memory
	_Elem *m_capacity;

	H3Vector(const int number_elements)
	{
		Init();
		Reserve(number_elements);
	}
	H3Vector() { Init(); }
	~H3Vector() { Deref(); }

	// * ~constructor
	VOID Init();
	// * ~destructor.
	VOID Deref();
	// * If list is empty
	BOOL IsEmpty() const;
	// * If vector is full
	BOOL IsFull() const;
	// * the number of items
	INT32 Count() const;
	// * the maximum number of items
	INT32 CountMax() const;
	// * calculates size
	UINT32 Size() const;
	// * calculates allocated size
	UINT32 SizeAllocated() const;
	// * removes the last item
	VOID RemoveLast();
	// * empties list
	VOID RemoveAll();
	// * Adds item
	_Elem* Add(_Elem & item);
	// * Adds only 1 item, expands by only 1
	_Elem* AddOne(_Elem & item);
	// * only for size 4 or references, H3 code
	VOID AddSize4(_Elem item);
	// * increases capacity
	BOOL Expand();
	// * returns First item
	_Elem *First();
	const _Elem *CFirst() const { return First(); }
	_Elem& RFirst() { return *First(); }
	const _Elem& CRFirst() const { return RFirst(); }
	// * returns Last item
	_Elem *Last();
	const _Elem *CLast() const { return Last(); }
	_Elem& RLast() { return *Last(); }
	const _Elem& CRLast() const { return RLast(); }
	// * Add one item to end
	_Elem* Append(_Elem & item) { return Add(item); }
	// * Add a single item, expanding by 1
	_Elem* Push(_Elem & item) { return AddOne(item); }
	// * Removes last item and returns reference to it
	_Elem* Pop();
	// * Returns item at position, can be negative to get from end
	_Elem* At(INT32 pos);
	const _Elem* CAt(INT32 pos) const;
	// * returns reference to item at position
	_Elem& RAt(INT32 pos) { return *At(pos); }
	const _Elem& CRAt(INT32 pos) const { return RAt(pos); }
	// * remove one item, elements shift left
	BOOL Remove(INT32 pos);
	// * remove range, list shifts left
	BOOL Remove(INT32 fromPos, INT32 toPos);
	// * reserves a number of elements, always greater than current
	BOOL Reserve(INT number);

	// * returns pointer to element at pos, positive only
	_Elem* operator[](INT32 pos);
	// * Adds item to end of list
	_Elem* operator+=(_Elem & item);
	// * Adds item to end of list
	_Elem* operator<<(_Elem & item) { return operator+=(item); }

	// * this is used in combination of C++11 'for :' range-based for loop iterator operations
	_Elem* begin() { return m_first; }
	// * this is used in combination of C++11 'for :' range-based for loop iterator operations
	_Elem* end() { return m_end; }
};

// * a string following the H3 format
struct H3String
{
protected:
	BOOL _init; // useless
	PCHAR str;
	INT32 length;
	INT32 capacity;

	VOID Deref() { str = nullptr; length = 0; capacity = 0; }
	VOID NullTerminate() { *End() = 0; }
	BOOL Realloc(int newSize);


public:
	// * constructor
	H3String();
	// * constructor and Assign(msg)
	H3String(LPCSTR msg);
	// * constructor and Assign(msg, len)
	H3String(LPCSTR msg, INT32 len);
	// * constructor and Assign(h3str)
	H3String(H3String *h3str);
	// * constructor and Assign(h3str)
	H3String(H3String & h3str);
	// * constructor and Assign(ch)
	H3String(CHAR ch);
	// * destructor
	~H3String();
	// * H3 constructor
	VOID Init();
	// * H3 destructor
	VOID Dereference();
	// * returns beginning of string
	// * modifiable contrary to String()
	PCHAR Begin();
	// * returns end of string, on null char
	PCHAR End();
	// * returns the last char of string
	CHAR Last();
	// * sets string as mes
	H3String& Assign(LPCSTR mes, INT32 len);
	// * Assign(mes, strlen(mes))
	H3String& Assign(LPCSTR mes);
	// * sets *string as ch
	H3String& Assign(CHAR ch);
	// * sets &string as h3string
	H3String& Assign(const H3String *h3string);
	// * sets string as h3string
	H3String& Assign(const H3String &h3string);
	// * prints number to string
	H3String& Assign(INT32 number);
	// * sets new capacity, 0x1F is default
	BOOL Reserve(INT32 newSize = 0x1E);
	// * returns constant char* string
	LPCSTR String() const;
	// * current length of string
	INT32 Length() const { return length; }
	// * capacity of string
	INT32 MaxLength() const { return capacity; }
	// * Sets capacity if larger, otherwise shortens
	BOOL SetLength(INT32 len);
	// * Adds mes to end of string
	BOOL Append(LPCSTR mes, INT32 len);

	// * reduces buffer capacity to length + 1
	VOID ShrinkToFit();

	template<INT32 sz>
	H3String& Append(const CHAR (&buffer)[sz]);
	// * Adds h3string to end of string
	BOOL Append(H3String & h3string);
	// * Adds h3string to end of string
	BOOL Append(H3String *h3string);
	// * Adds number to string
	H3String& Append(int number);
	// * Adds hex number to string
	H3String& Append(unsigned int number);
	// * Adds ch to end of string
	BOOL Append(CHAR ch);
	// * Finds position of first ch
	LPCSTR FindFirst(CHAR ch);
	// * Finds position of first substring
	LPCSTR FindFirst(LPCSTR substr) const;
	// * returns string offset at pos
	PCHAR At(INT32 pos);
	const CHAR GetCharAt(INT32 pos) const;
	// * Removes all instances of ch
	INT32 Remove(CHAR ch);
	// * Removes all instances of substring
	INT32 Remove(LPCSTR substr);
	// * Removes all instances of substring
	INT32 Remove(LPCSTR substr, INT32 sublen);
	// * Remove chars from start to end
	INT32 Remove(INT32 start, INT32 end);
	// * Splits a string on a given char
	// * The character is removed
	// * the original string is truncated
	// * The outgoing string gets the remainder
	// * of the original string
	BOOL Split(CHAR ch, H3String& out);
	// * sets string to all 0s
	VOID Erase();
	// * memcmp ~ case sensitive
	BOOL Equals(LPCSTR msg, INT32 len) const;
	// * Equals(msg, strlen(msg))
	BOOL Equals(LPCSTR msg) const;
	// * strcmpi ~ not case-sensitive
	BOOL Equals_i(LPCSTR msg) const;
	// * strcmpi ~ not case-sensitive
	BOOL Equals_i(const H3String& other) const;
	// * strcmpi ~ not case-sensitive
	BOOL Equals_i(const H3String* other) const;
	// * memcmp ~ case sensitive
	BOOL Equals(H3String *h3string) const;

	// * Inserts string within h3string at position
	BOOL Insert(INT32 pos, LPCSTR msg, INT32 len);
	// * Inserts string within h3string at position
	BOOL Insert(INT32 pos, LPCSTR msg) { return Insert(pos, msg, strlen(msg)); }
	// * Inserts string within h3string at position
	BOOL Insert(INT32 pos, H3String& to_insert) { return Insert(pos, to_insert.String(), to_insert.Length()); }
	// * Inserts string within h3string at position
	BOOL Insert(INT32 pos, H3String* to_insert) { return Insert(pos, *to_insert); }
	// * Inserts string within h3string at position
	BOOL Insert(INT32 pos, CHAR ch);

	INT Compare(const H3String* other) const;
	INT Compare(const H3String& other) const;
	INT Compare(LPCSTR other) const;

	// * Ends string at position
	BOOL Truncate(INT32 position);

	// * Assign(h3str)
	H3String& operator=(H3String &h3str);
	// * Assign(h3str)
	H3String& operator=(H3String *h3str);
	// * Assign(msg)
	H3String& operator=(LPCSTR msg);
	// * Assign(ch)
	H3String& operator=(CHAR ch);

#ifdef CPLUSPLUS11
	H3String& operator=(H3String&& other);
	H3String(H3String&& other);
#endif

	// * Append(h3str)
	H3String& operator+=(H3String &h3str);
	// * Append(h3str)
	H3String& operator+=(H3String *h3str);
	// * Append(msg)
	template<INT32 sz>
	H3String & operator+=(const CHAR(&buffer)[sz]);
	// * Append(msg)
	H3String& operator+=(LPCSTR msg);
	// * Append(ch)
	H3String& operator+=(CHAR ch);

	// * Append(signed int)
	// * Adds number to string
	H3String& operator+=(const int number) { return Append(number); }
	// * Adds hex number to string
	H3String& operator+=(const unsigned int number) { return Append(number); }

	// * Appends char
	H3String& operator<<(CHAR ch) { return operator+=(ch); }
	// * Appends string
	H3String& operator<<(LPCSTR msg) { return operator+=(msg); }
	// * Appends h3string
	H3String& operator<<(H3String & h3str) { return operator+=(h3str); }
	// * Appends
	H3String& operator<<(H3String * h3str) { return operator+=(h3str); }
	// * Adds number to string
	H3String& operator<<(const int number) { return Append(number); }
	// * Adds hex number to string
	H3String& operator<<(const unsigned int number) { return Append(number); }

	// * Compare(h3str)
	INT operator==(const H3String *h3str) const { return Compare(h3str); }
	// * Compare(h3str)
	INT operator==(const H3String & h3str) const { return Compare(h3str); }
	// * Compare(str)
	INT operator==(LPCSTR str) const;

	// * Returns char at offset
	const CHAR operator[](INT32 pos) const;

	// * The number of times this string is referenced - avoids deletion from destructor in references
	INT8 References();

	// * Increase the number of references to this string
	VOID IncreaseReferences();

	// * assigns a number with commas to a string
	BOOL FormattedNumber(int number);

	// * assigns a scaled number with k, M or B index and number of decimals
	BOOL ScaledNumber(int number, int decimals = 1);

#if CPLUSPLUS11
	// * use sprintf on a H3String directly
	template<typename ... Args>
	H3String& Printf(LPCSTR format, Args ... args)
	{
		// * snprintf with null buffer returns print length
		int len = _snprintf(nullptr, 0, format, args ...);
		if (len > 0 && Reserve(len + 1))
		{
			len = _snprintf(Begin(), len, format, args ...);
			if (len)
			{
				length = len - 1;
				str[len] = 0;
			}
		}
		return *this;
	}

	// * use sprintf on a H3String, appending the result to the end
	template<typename ... Args>
	H3String& PrintfAppend(LPCSTR format, Args ... args)
	{
		H3String appendme;
		appendme.Printf(format, args ...);
		Append(appendme);
		return *this;
	}
#else // non c++11 versions
	// * use sprintf on a H3String directly
	H3String& Printf(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		int len = _snprintf(nullptr, 0, format, args);
		if (len > 0 && Reserve(len + 1))
		{
			len = F_vsprintf(Begin(), format, args);
			Truncate(len);
		}
		va_end(args);
		return *this;
	}
	// * use sprintf on a H3String, appending the result to the end
	H3String& PrintfAppend(LPCSTR format, ...)
	{
		H3String appendme;
		va_list args;
		va_start(args, format);
		int len = _snprintf(nullptr, 0, format, args);
		if (len > 0 && appendme.Reserve(len + 1))
		{
			len = F_vsprintf(appendme.Begin(), format, args);
			appendme.Truncate(len);
		}
		va_end(args);
		Append(appendme);
		return *this;
	}
#endif


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
	friend H3String operator+(H3String &lhs, LPCSTR rhs);
	// * Adds one char* and H3String into one H3String
	friend H3String operator+(LPCSTR lhs, H3String &rhs);

	enum eH3String
	{
		HS_NOTFOUND = -1,
		HS_FAILED = 0,
		HS_SUCCESS = 1
	};
};

#ifdef CPLUSPLUS11
inline H3String& H3String::operator=(H3String&& other)
{
	if (&other == this)
		return *this;

	str = other.str;
	length = other.length;
	capacity = other.capacity;
	other.Deref();

	return *this;
}

inline H3String::H3String(H3String&& other) :
	str(other.str),
	length(other.length),
	capacity(other.capacity)
{
	other.Deref();
}
#endif

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
	// * sets bit at position to on or off
	// * position can exceed the scope of bitfield, meaning greater than 32 bits
	VOID SetState(INT32 position, BOOL state)
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
#pragma pack(pop)

// * H3String member function definitions

inline H3String & H3String::Assign(CHAR ch)
{
	if (str || Realloc(1))
	{
		*Begin() = ch;
		SetLength(1);
	}
	return *this;
}

inline H3String & H3String::Assign(const H3String & h3string)
{
	if (h3string.str)
		Assign(h3string.String(), h3string.Length());
	return *this;
}

inline H3String & H3String::Assign(const H3String * h3string)
{
	if (h3string)
		Assign(h3string->String(), h3string->Length());
	return *this;
}

inline H3String & H3String::Assign(const INT32 number)
{
	if (str || Reserve())
		length = sprintf(str, "%d", number);
	return *this;
}

inline BOOL H3String::Reserve(const INT32 newSize)
{
	return Realloc(newSize);
}

inline LPCSTR H3String::String() const
{
#if H3API_SAFE
	if (str)
		return str;
	return h3_NullString;
#endif
	return str;
}

inline BOOL H3String::Realloc(int newSize)
{
	return THISCALL_2(BOOL, 0x404B80, this, newSize);
}

inline H3String::H3String()
{
	Deref();
}

inline H3String::H3String(LPCSTR msg)
{
	Deref();
	Assign(msg);
}

inline H3String::H3String(LPCSTR msg, const INT32 len)
{
	Deref();
	Assign(msg, len);
}

inline H3String::H3String(H3String * h3str)
{
	Deref();
	Assign(h3str);
}

inline H3String::H3String(H3String & h3str)
{
	Deref();
	Assign(h3str);
}

inline H3String::H3String(const CHAR ch)
{
	Deref();
	Assign(ch);
}

inline H3String::~H3String()
{
	Dereference();
}

inline VOID H3String::Init()
{
	THISCALL_2(VOID, 0x404130, this, 0);
}

inline VOID H3String::Dereference()
{
	THISCALL_1(VOID, 0x4040F0, this);
}

inline PCHAR H3String::Begin()
{
#if H3API_SAFE
	if (str)
		return str;
	else
		return (PCHAR)h3_NullString;
#endif
	return str;
}

inline PCHAR H3String::End()
{
#if H3API_SAFE
	if (str)
		return str + length;
	else
		return (PCHAR)h3_NullString;
#endif
	return str + length;
}

inline CHAR H3String::Last()
{
#if H3API_SAFE
	if (str)
		return str[length - 1];
	else
		return '\0';
#endif
	return str[length - 1];
}

inline H3String & H3String::Assign(LPCSTR mes)
{
	return Assign(mes, strlen(mes));
}

inline H3String & H3String::Assign(LPCSTR mes, const INT32 len)
{
#if H3API_SAFE
	if (!mes)
		return this;
#endif
	return THISCALL_3(H3String&, 0x404180, this, mes, len);
}

inline BOOL H3String::SetLength(INT32 len)
{
	if (len > MaxLength())
		return Realloc(len);

	length = len;
	NullTerminate();
	return HS_SUCCESS;
}

inline BOOL H3String::Append(LPCSTR mes, INT32 len)
{
	if (!mes || len <= 0)
		return HS_FAILED;

	if (Length() + len >= MaxLength() && !Realloc(Length() + len))
		return HS_FAILED;

	PCHAR end = End();
	LPCSTR m = mes;

	while (*m)
		*end++ = *m++;
	*end = 0;
	length += len;
	return HS_SUCCESS;
}

inline VOID H3String::ShrinkToFit()
{
	if (capacity == 0)
		return;
	int min_len = length + 2;
	if (min_len >= capacity)
		return;

	PCHAR tmp = (PCHAR)F_malloc(min_len);
	F_memcpy(tmp, str - 1, min_len);
	F_delete(str - 1);
	str = tmp;
	capacity = min_len - 1;
}

template<INT32 sz>
inline H3String & H3String::Append(const CHAR (&buffer)[sz])
{
	Append(buffer, sz - 1);
	return *this;
}

template<INT32 sz>
inline H3String & H3String::operator+=(const CHAR(&buffer)[sz])
{
	Append(buffer, sz - 1);
	return *this;
}

inline BOOL H3String::Append(H3String & h3string)
{
	if (!h3string.Begin())
		return HS_FAILED;
	return Append(h3string.Begin(), h3string.Length());
}

inline BOOL H3String::Append(H3String * h3string)
{
	if (!h3string)
		return HS_FAILED;
	return Append(h3string->Begin(), h3string->Length());
}

inline H3String & H3String::Append(const int number)
{
	return PrintfAppend("%d", number);
}

inline H3String & H3String::Append(const unsigned int number)
{
	return PrintfAppend("0x%X", number);
}

inline BOOL H3String::Append(const CHAR ch)
{
	if (!ch) // null char already done
		return HS_SUCCESS;

	if (Length() + 1 >= MaxLength() && !Realloc(Length() + 1))
		return HS_FAILED;

	PCHAR end = End();
	*end = ch;
	*++end = 0;
	length++;
	return HS_SUCCESS;
}

inline LPCSTR H3String::FindFirst(const CHAR ch)
{
	PCHAR f = Begin();
	int pos = 0;
	int len = Length();
	while (*f && pos < len)
	{
		if (*f == ch)
			return f;
		++f;
		++pos;
	}
	return nullptr;
}

inline LPCSTR H3String::FindFirst(LPCSTR substr) const
{
	if (String())
		return strstr(String(), substr);
	return nullptr;
}

inline INT32 H3String::Remove(const CHAR ch)
{
	if (!str || *str == 0) // no text or NULL string
		return HS_FAILED;

	INT32 len = Length();
	register INT32 l = Length() + 1;

	char* dst;
	for (char* src = dst = str; *src && --l; src++)
	{
		if (*src == ch) // skip over this char
		{
			--length;
			continue;
		}
		*dst = *src;
		++dst;
	}
	*dst = 0; // place end character

	return len - Length();
}

inline INT32 H3String::Remove(LPCSTR substr)
{
	return Remove(substr, strlen(substr));
}

inline INT32 H3String::Remove(LPCSTR substr, INT32 sublen)
{
	PCHAR s, copy_end;
	if (!String())
		return HS_FAILED;
	if (nullptr == (s = strstr(str, substr)))
		// no match
		return 0;
	INT rem = length;
	PCHAR copyFrom = s + sublen;
	while (nullptr != (copy_end = strstr(copyFrom, substr)))
	{
		memmove(s, copyFrom, copy_end - copyFrom);
		s += copy_end - copyFrom;
		copyFrom = copy_end + sublen;
	}
	memmove(s, copyFrom, 1 + strlen(copyFrom));
	length = strlen(str);
	return rem - length;
}

inline PCHAR H3String::At(const INT32 pos)
{
	if (Begin() && pos >= 0)
		return str + min(pos, Length());
	return nullptr;
}

inline const CHAR H3String::GetCharAt(const INT32 pos) const
{
	if (str && pos >= 0 && Length())
		return str[min(pos, Length())];
	return 0;
}

inline INT32 H3String::Remove(INT32 start, INT32 end)
{
	INT32 n = end - start;
	if (n <= 0)
		return HS_FAILED;

	PCHAR dest = At(start);
	PCHAR src = At(end);
	if (!dest || !src)
		return HS_FAILED;

	while (*src)
		*dest++ = *src++;

	SetLength(Length() - n);
	NullTerminate();
	return n;
}

inline BOOL H3String::Split(const CHAR ch, H3String & out)
{
	LPCSTR limiter = FindFirst(ch);
	if (!limiter)
		return FALSE;

	INT pos = INT(limiter - String());
	INT rem_len = Length() - pos - 1;
	// * if it's the last char of string, no split can occur...
	// * still we remove the found char
	if (rem_len <= 0)
	{
		Truncate(pos == 0 ? 0 : pos - 1);
		return FALSE;
	}

	out.Assign(limiter + 1, rem_len);
	Truncate(pos == 0 ? 0 : pos - 1);
	return TRUE;
}

inline VOID H3String::Erase()
{
	F_memset(Begin(), 0, Length());
	length = 0;
}

inline BOOL H3String::Equals(LPCSTR msg, INT32 len) const
{
	if (!msg || Length() != len)
		return FALSE;

	return memcmp(msg, String(), Length()) == 0;
}

inline BOOL H3String::Equals(LPCSTR msg) const
{
	if (!msg)
		return HS_FAILED;
	return Equals(msg, strlen(msg));
}

inline BOOL H3String::Equals_i(LPCSTR msg) const
{
	if (!msg)
		return HS_FAILED;
	return (F_strcmpi(msg, String()) == 0);
}

inline BOOL H3String::Equals_i(const H3String & other) const
{
	if (Length() != other.Length())
		return FALSE;
	return Equals_i(other.String());
}

inline BOOL H3String::Equals_i(const H3String * other) const
{
	if (!other)
		return HS_FAILED;
	return Equals_i(*other);
}

inline BOOL H3String::Equals(H3String * h3string) const
{
	if (!h3string)
		return HS_FAILED;
	if (Length() != h3string->Length())
		return FALSE;
	return Equals(h3string->Begin(), h3string->Length());
}

inline BOOL H3String::Insert(INT32 pos, LPCSTR msg, INT32 len)
{
	if (len == 0 || msg == nullptr)
		return FALSE;
	// * trying to insert at or after end
	if (pos >= Length())
		return Append(msg, len);

	if (!Reserve(Length() + len))
		return FALSE;

	INT copylen = Length() - pos;
	// * simpler than malloc + free
	H3String temp;
	temp.Assign(str + pos, copylen);
	// * temporarily cut out
	Truncate(pos);
	// * insert msg
	Append(msg, len);
	// * insert original end
	Append(temp);

	return TRUE;
}

inline BOOL H3String::Insert(INT32 pos, const CHAR ch)
{
	CHAR temp[2];
	temp[0] = ch;
	temp[1] = 0;
	return Insert(pos, temp, 1);
}

inline INT H3String::Compare(const H3String * other) const
{
	return Compare(other->String());
}

inline INT H3String::Compare(const H3String & other) const
{
	return Compare(other.String());
}

inline INT H3String::Compare(const LPCSTR other) const
{
	return strcmp(String(), other);
}

inline BOOL H3String::Truncate(INT32 position)
{
	if (position < Length() && String())
	{
		length = position;
		str[length] = 0;
	}
	return FALSE;
}

inline H3String & H3String::operator=(H3String & h3str)
{
	return Assign(h3str);
}

inline H3String & H3String::operator=(H3String * h3str)
{
	return Assign(h3str);
}

inline H3String & H3String::operator+=(H3String & h3str)
{
	Append(h3str);
	return *this;
}

inline H3String & H3String::operator+=(H3String * h3str)
{
	Append(h3str);
	return *this;
}

inline H3String & H3String::operator+=(LPCSTR msg)
{
	Append(msg, strlen(msg));
	return *this;
}

inline H3String & H3String::operator+=(CHAR ch)
{
	Append(ch);
	return *this;
}

inline INT H3String::operator==(LPCSTR str) const
{
	return Compare(str);
}

inline const CHAR H3String::operator[](INT32 pos) const
{
#if H3API_SAFE
	if (!str)
		return 0;
	if (pos < 0)
		return str[0];
	if (pos > Length())
		return str[Length() - 1];
#endif
	return str[pos];
}

inline INT8 H3String::References()
{
#if H3API_SAFE
	if (!str)
		return HS_NOTFOUND;
#endif
	return str[-1];
}

inline VOID H3String::IncreaseReferences()
{
#if H3API_SAFE
	if (str)
#endif
		str[-1]++;
}

inline H3String & H3String::operator=(LPCSTR msg)
{
	Assign(msg);
	return *this;
}

inline H3String & H3String::operator=(CHAR ch)
{
	Assign(ch);
	return *this;
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
	if (!(ans.Reserve(lhs.Length() + 1)))
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

inline H3String operator+(CHAR lhs, H3String & rhs)
{
	H3String ans;
	if (!(ans.Reserve(rhs.Length()) + 1))
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

inline H3String operator+(LPCSTR lhs, H3String & rhs)
{
	H3String ans;
	int slen = strlen(lhs);
	if (!(ans.Reserve(rhs.Length()) + slen))
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

inline H3String operator+(H3String & lhs, LPCSTR rhs)
{
	H3String ans;
	int slen = strlen(rhs);
	if (!(ans.Reserve(lhs.Length()) + slen))
		return ans;
	ans += lhs;
	ans += rhs;
	return ans;
}

// * * * * * * * * * * * * * * * * * * * *
// *
// * H3Vector member function definitions
// *
// * * * * * * * * * * * * * * * * * * * *

template<typename _Elem>
inline VOID H3Vector<_Elem>::Init()
{
	m_first = nullptr;
	m_end = nullptr;
	m_capacity = nullptr;
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::IsEmpty() const
{
	if (!m_first || m_first == m_end)
		return TRUE;
	return FALSE;
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::IsFull() const
{
	if (m_end == m_capacity)
		return TRUE;
	return FALSE;
}

template<typename _Elem>
inline INT32 H3Vector<_Elem>::Count() const
{
	return m_end - m_first;
}

template<typename _Elem>
inline INT32 H3Vector<_Elem>::CountMax() const
{
	return m_capacity - m_first;
}

template<typename _Elem>
inline UINT32 H3Vector<_Elem>::Size() const
{
	return (UINT32)m_end - (UINT32)m_first;
}

template<typename _Elem>
inline UINT32 H3Vector<_Elem>::SizeAllocated() const
{
	return (UINT32)m_capacity - (UINT32)m_first;
}

template<typename _Elem>
inline VOID H3Vector<_Elem>::AddSize4(_Elem item)
{
	THISCALL_4(VOID, 0x5FE2D0, this, m_end, 1, &item);
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::First()
{
	return m_first;
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::Last()
{
	return m_end - 1;
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
		n = min(-(pos), c);
		n = c - n;
	}
	return m_first + n;
}

template<typename _Elem>
inline const _Elem * H3Vector<_Elem>::CAt(INT32 pos) const
{
	INT32 n;
	if (pos >= 0)
		n = min(pos, Count() - 1);
	else
	{
		int c = Count();
		n = min(-(pos), c);
		n = c - n;
	}
	return m_first + n;
}

template<typename _Elem>
inline BOOL H3Vector<_Elem>::Remove(INT32 pos)
{
	return Remove(pos, pos);
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::operator[](INT32 pos)
{
	return m_first + pos;
}

template<typename _Elem>
inline _Elem* H3Vector<_Elem>::operator+=(_Elem & item)
{
	return Add(item);
}

template<typename _Elem>
inline _Elem * H3Vector<_Elem>::Pop()
{
	if (m_end > m_first)
	{
		--m_end;
		m_end->~_Elem();
	}
	return m_end;
}

template<typename _Elem>
inline VOID H3Vector<_Elem>::RemoveAll()
{
	while (m_end > m_first)
	{
		--m_end;
		m_end->~_Elem();
	}
}

template<typename _Elem>
inline VOID H3Vector<_Elem>::RemoveLast()
{
	Pop();
}

#ifdef _H3API_OPERATORS_

	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Deref()
	{
		if (m_first)
			delete[] m_first;
		m_first = nullptr;
		m_end = nullptr;
		m_capacity = nullptr;
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Reserve(const INT number)
	{
		if (number <= 0)
			return FALSE;

		INT num = Count();
		if (number <= num)
			return FALSE;

		_Elem *t = new _Elem[number];
		if (!t)
			return FALSE;

#ifdef CPLUSPLUS11
		for (int i = 0; i < num; ++i)
			t[i] = std::move(m_first[i]);
#else
		for (int i = 0; i < num; ++i)
			t[i] = m_first[i];
#endif

		delete[] m_first;

		m_first = t;
		m_end = m_first + num;
		m_capacity = m_first + number;

		return TRUE;
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Expand()
	{
		constexpr INT MIN_ELEMENTS    = 10;
		constexpr INT SIZE_MULTIPLIER = 2;

		if (!m_first)
			return Reserve(MIN_ELEMENTS);
		else
			return Reserve(CountMax() * SIZE_MULTIPLIER);
	}

	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::Add(_Elem & item)
	{
		if (!m_first || IsFull())
		{
			if (!Expand())
				return nullptr; // failed
		}
		*m_end = item;
		++m_end;
		return m_end - 1;  // returns position where it was added
	}

	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::AddOne(_Elem & item)
	{
		if (!m_first)
		{
			if (!Reserve(1))
				return nullptr;
		}
		else if (IsFull())
		{
			if (!Reserve(CountMax() + 1))
				return nullptr;
		}
		*m_end = item;
		++m_end;
		return m_end - 1;  // returns position where it was added
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(INT32 fromPos, INT32 toPos)
	{
		if (fromPos < 0 || toPos < 0 || toPos < fromPos)
			return FALSE;
		INT num = Count();
		if (fromPos >= num)
			return FALSE;

		INT to = min(num - 1, toPos);
		INT r = to - fromPos + 1;

		for (int i = fromPos; i <= toPos; ++i)
			m_first[i]->~_Elem();

		_Elem* rem = m_first + fromPos;
		_Elem* remEnd = rem + r;
		size_t copyLen = (size_t)m_end - (size_t)remEnd;
		// * move any elements from the end
		memmove(PVOID(rem), PVOID(remEnd), copyLen);
		// * blank out the moved end elements
		F_memset(PVOID(remEnd), 0, copyLen);
		m_end -= r;
		return TRUE;
	}

#else /* _H3API_OPERATORS_ is not defined */

	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Deref()
	{
		if (m_first)
		{
			for (_Elem* i = m_first; i < m_end; ++i)
				i->~_Elem();

			F_delete((PVOID)m_first);
			m_first = nullptr;
		}
		m_end = nullptr;
		m_capacity = nullptr;
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Expand()
	{
		constexpr INT MIN_ELEMENTS = 10;
		constexpr INT SIZE_MULTIPLIER = 2;

		if (!m_first)
			return Reserve(MIN_ELEMENTS);
		else
			return Reserve(CountMax() * SIZE_MULTIPLIER);
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(INT32 fromPos, INT32 toPos)
	{
		if (fromPos < 0 || toPos < 0 || toPos < fromPos)
			return FALSE;
		INT32 num = Count();
		if (fromPos >= num)
			return FALSE;

		INT32 to = min(num - 1, toPos); // don't go further than end!
		INT32 r = to - fromPos + 1; // number removed

		_Elem* rem = m_first + fromPos;
		_Elem* remEnd = rem + r;

		for (_Elem* i = rem; i <= remEnd; ++i)
			i->~_Elem();

		size_t copyLen = (size_t)m_end - (size_t)remEnd;
		memmove((PVOID)rem, (PVOID)remEnd, copyLen);
		F_memset(PVOID(remEnd), 0, copyLen);

		m_end -= r;

		return TRUE;
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Reserve(const INT number)
	{
		INT num = Count();
		if (number <= num)
			return FALSE;

		UINT32 cSize = Size();
		UINT32 newSize = sizeof(_Elem) * number;

		_Elem *t = (_Elem*)F_calloc(newSize);
		if (!t)
			return FALSE;

		for (int i = 0; i < number; ++i)
			t[i] = _Elem();

		F_memcpy((PVOID)t, (PVOID)m_first, cSize);
		F_delete((PVOID)m_first);
		m_first = t;
		m_end = (_Elem*)((UINT32)m_first + cSize);
		m_capacity = (_Elem*)((UINT32)m_first + newSize);
		return TRUE;
	}

	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::AddOne(_Elem & item)
	{
		if (!m_first)
			if (!Reserve(1))
				return nullptr;
		else if (IsFull())
			if (!Reserve(CountMax() + 1))
				return nullptr;

		m_end = item;
		++m_end;
		return m_end - 1;  // returns position where it was added
	}

	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::Add(_Elem & item)
	{
		if (!m_first || IsFull())
			if (!Expand())
				return nullptr; // failed
		m_end = item;
		++m_end;
		return m_end - 1;  // returns position where it was added
	}

#endif /* #ifdef _H3API_OPERATORS_ */

#endif /* #define _H3BASE_H_ */