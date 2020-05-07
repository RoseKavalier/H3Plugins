//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//                      Last edit: 2020-05-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BASE_HPP_
#define _H3BASE_HPP_

#include "../H3_Core.hpp"

// * Prevents some warnings
#define _CRT_SECURE_NO_WARNINGS

// * Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// * use std::min and std::max instead
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX

#ifndef _WINDOWS_

#endif

// * H3API uses std::min
#ifdef min
#undef min
#endif

// * H3API uses std::max
#ifdef max
#undef max
#endif

// * use STL functions instead of C-style
#include <algorithm>

// * Input / output functions
#include <cstdio>

// * disable sprintf warning
#pragma warning(disable:4996)

#if (__cplusplus > 199711L || (_MSC_VER && _MSC_VER >= 1900))
// * true if your IDE version is C++11 compatible
// * this checks for C++11 standard or Visual Studio 2015+
#define _CPLUSPLUS11_
#endif

#if (_MSC_VER && _MSC_VER <= 1500)
#pragma warning (disable:4482)
#endif

#ifndef _CPLUSPLUS11_
#ifndef nullptr
// * nullptr was added with C++11
#define nullptr NULL
#endif
#ifndef constexpr
// * constexpr was added with C++11
#define constexpr const
#endif
#ifndef _H3ENUM_
// * enum class was added with C++11
#define _H3ENUM_ enum
#endif
#ifndef noexcept
// * noexcept keyword added with C++11
#define noexcept throw()
#endif
#else
#ifndef _H3ENUM_
// * enum class
#define _H3ENUM_ enum class
#endif
#endif

// * indicates this content will be deprecated
// * and replaced by equivalent expressions
#define _H3API_DEPRECATED_

// * Slaps top of car
// * This bad boy can hold just about anything
typedef void(*naked_t)();
// * generic typedef to indicate this is a h3 function
typedef unsigned long h3func;
// * 1-byte sized boolean
typedef char          BOOL8;
// * Used for unknown structure members
typedef char          h3unk;
// * Used for alignment structure members
typedef char          h3align;

// * for uniformity's sake
#ifdef VOID
#undef VOID
// * void type
typedef void VOID;
#else
// * void type
typedef void VOID;
#endif

// * may be missing from some configurations, used for critical sections of H3WavFile
#ifndef RTL_RESOURCE_TYPE
#define RTL_RESOURCE_TYPE 1
#endif

// * typedef safety declarations
// * no checks are needed here based on C++03 Standard 7.1.3 typedef specifier
// * https://stackoverflow.com/questions/8594954/repeated-typedefs-invalid-in-c-but-valid-in-c?answertab=votes#tab-top
typedef int              INT, *PINT;
typedef unsigned int     UINT, *PUINT;
typedef signed char      INT8, *PINT8;
typedef signed short     INT16, *PINT16;
typedef signed int       INT32, *PINT32;
typedef signed __int64   INT64, *PINT64;
typedef unsigned char    UINT8, *PUINT8;
typedef unsigned short   UINT16, *PUINT16;
typedef unsigned int     UINT32, *PUINT32;
typedef unsigned __int64 UINT64, *PUINT64;
typedef float            FLOAT;
typedef FLOAT                    *PFLOAT;
typedef double           DOUBLE;
typedef DOUBLE                   *PDOUBLE;
typedef char             CHAR;
typedef CHAR                     *PCHAR;
typedef unsigned char    UCHAR;
typedef UCHAR                    *PUCHAR;
typedef unsigned char    BYTE;
typedef BYTE                     *PBYTE;
typedef unsigned short   WORD;
typedef WORD                     *PWORD;
typedef unsigned long    DWORD;
typedef DWORD                    *PDWORD;
typedef const char               *LPCSTR;
typedef void                     *PVOID;

#ifndef _H3_DECLARE_
// * forward-defines a struct, pointer to struct and reference to struct
#define _H3_DECLARE_(NAME) struct NAME; typedef struct NAME *P ## NAME; typedef struct NAME &R ## NAME;
#endif

#ifndef _H3_EXPORT_
// * exports a function without name mangling
// * to use, type the following within a function's definition:
// * #pragma _H3_EXPORT_
#define _H3_EXPORT_ comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
#endif

#ifndef ArraySize
// * returns number of elements in an array
#define ArraySize(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifndef Abs
// * returns absolute value of number
#define Abs(num) (((num) >= 0) ? (num) : (-(num)))
#endif

#pragma region Access Macros
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
#define FuncAt(address) (DwordAt((address) + 1) + (address) + 5)
#endif
#pragma endregion Access Macros

// * model function definitions
// * used to interact with game functions
#pragma region Model Functions
#pragma region THISCALL_DECLARATIONS
#ifndef THISCALL_0
#define THISCALL_0(return_type, address) ((return_type(__thiscall *)(VOID))(address))()
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
#define STDCALL_0(return_type, address) ((return_type(__stdcall *)(VOID))(address))()
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
#define FASTCALL_0(return_type, address) ((return_type(__fastcall *)(VOID))(address))()
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
#define CDECL_0(return_type, address) ((return_type(__cdecl *)(VOID))(address))()
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

// * you absolutely need c++11 to use STDCALL_VA, THISCALL_VA and FASTCALL_VA
// * in prior versions, variadic templates don't exist
// * va_list arguments would absolutely require __cdecl to clean the stack
#ifdef _CPLUSPLUS11_

namespace h3vargs
{
	template<typename return_type, typename ...Args>
	return_type Stdcall_Variadic(UINT address, Args... args)
	{
		return (reinterpret_cast<return_type(__stdcall*)(Args...)>(address))(args...);
	}

	template<typename return_type, typename ...Args>
	return_type Thiscall_Variadic(UINT address, Args... args)
	{
		return (reinterpret_cast<return_type(__thiscall*)(Args...)>(address))(args...);
	}

	template<typename return_type, typename ...Args>
	return_type Fastcall_Variadic(UINT address, Args... args)
	{
		return (reinterpret_cast<return_type(__fastcall*)(Args...)>(address))(args...);
	}
}

#ifndef STDCALL_VA
#define STDCALL_VA(return_type, address, ...) h3vargs::Stdcall_Variadic<return_type>(address, __VA_ARGS__)
#endif

#ifndef THISCALL_VA
#define THISCALL_VA(return_type, address, ...) h3vargs::Thiscall_Variadic<return_type>(address, __VA_ARGS__)
#endif

#ifndef FASTCALL_VA
#define FASTCALL_VA(return_type, address, ...) h3vargs::Fastcall_Variadic<return_type>(address, __VA_ARGS__)
#endif

#endif /* _CPLUSPLUS11_ */

#ifndef CDECL_VA
#define CDECL_VA(return_type, address, a1, ...) ((return_type(__cdecl *)(UINT, ...))(address))((UINT)(a1), __VA_ARGS__)
#endif

#ifndef CDECL_VA2
#define CDECL_VA2(return_type, address, a1, a2, ...) ((return_type(__cdecl *)(UINT, UINT, ...))(address))((UINT)(a1), (UINT)(a2), __VA_ARGS__)
#endif
#pragma endregion

#pragma endregion Model Functions

namespace h3
{
	// * Null string ""
	LPCSTR const h3_NullString = LPCSTR(0x63A608);

	PCHAR const h3_TextBuffer = PCHAR(0x697428);
#ifndef _H3API_DONT_USE_MACROS_
	// * 512 bytes of char buffer to be used for printing text
	//#define h3_TextBuffer      PCHAR(0x697428)
	// * the game dimensions
#define gameWidth          IntAt(0x403401)
// * the game dimensions
#define gameHeight         IntAt(0x4033FC)
// * the offset in tiles from center of screen to edges
#define gameEdgeHorizontal CharAt(0x4A8FC0)
// * the offset in tiles from center of screen to edges
#define gameEdgeVertical   CharAt(0x4A8FC5)
// * the map dimensions, in tiles
#define h3_MapSize         IntAt(0x6783C8)
// * the size of a pixel
// * 2 means 16-bit
// * 4 means 32-bit
#define h3_BitMode         ByteAt(0x5FA228 + 3)	
#else		
	_H3API_ INT gameWidth();
	_H3API_ INT gameHeight();
	_H3API_ INT8 gameEdgeHorizontal();
	_H3API_ INT8 gameEdgeVertical();
	_H3API_ INT h3_MapSize();
	_H3API_ UINT8 h3_BitMode();
#endif

	// * checks for SoD, HotA and WoG/ERA
	class H3Version
	{
		_H3ENUM_ GameVersion : INT
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
		_H3API_ H3Version();
		_H3API_ GameVersion version() const;
		_H3API_ BOOL roe()  const;
		_H3API_ BOOL sod()  const;
		_H3API_ BOOL hota() const;
		_H3API_ BOOL era()  const;
		_H3API_ BOOL wog()  const;
	};

	// * heap realloc using H3 assets
	_H3API_ PVOID F_realloc(PVOID obj, UINT new_size);
	// * calloc using h3 assets
	_H3API_ PVOID F_calloc(UINT count, UINT size = 1);
	// * heapalloc using H3 assets
	_H3API_ PVOID F_malloc(UINT size);
	// * heapfree using H3 assets
	_H3API_ VOID F_delete(PVOID obj);
	// * memcpy using H3 assets
	_H3API_ VOID F_memcpy(PVOID dest, PVOID src, const UINT len);
	// * compares two strings, not-case-sensitive
	_H3API_ INT F_strcmpi(LPCSTR string1, LPCSTR string2);
	// * sets dest to value
	_H3API_ PVOID F_memset(PVOID dest, const UINT value, const UINT len);
	// * vsprintf using h3 assets
	// * you need to handle va_list yourself to use this!
	// * otherwise use F_sprintf which will do both
	_H3API_ INT F_vsprintf(PCHAR buffer, LPCSTR format, va_list args);
	// * sprintf using h3 assets and buffer
	_H3API_ INT F_sprintf(LPCSTR format, ...);
	// * sprintf using h3 assets and custom buffer
	_H3API_ INT F_sprintfbuffer(PCHAR buffer, LPCSTR format, ...);

	namespace H3Numbers
	{
		// * add thousands commas to numbers
		_H3API_ int AddCommas(int num, char *out);
		// * show a number in short scale format with specified number of decimals
		_H3API_ int MakeReadable(int num, char *out, int decimals = 1);
	}

	namespace H3Random
	{
		_H3API_ void SetRandomSeed(UINT seed = STDCALL_0(UINT, DwordAt(0x63A354)));
		_H3API_ int Random(int high);
		_H3API_ int RandBetween(int low, int high);
	}

	namespace H3Error
	{
		// * external messagebox showing message
		_H3API_ VOID ShowError(LPCSTR message, LPCSTR title = "H3Error!");
		// * external messagebox showing message and offering OK / Cancel choice
		_H3API_ BOOL ShowErrorChoice(LPCSTR message, LPCSTR title = "H3Error!");
		// * external messagebox showing message
		// * wide char format
		_H3API_ VOID _ShowError(LPCWSTR message, LPCWSTR title = L"H3Error!");
		// * external messagebox showing message and offering OK / Cancel choice
		// * wide char format
		_H3API_ BOOL _ShowErrorChoice(LPCWSTR message, LPCWSTR title = L"H3Error!");
	}

#pragma pack(push, 1)
	// * dword used as bitfield
	// * can be used as an array of bitfields
	struct H3Bitfield
	{
	protected:
		UINT m_bf;
	public:
		// * returns whether bit at position is set or not
		// * position can exceed the scope of bitfield, meaning greater than 32 bits
		_H3API_ BOOL GetState(INT32 position) const;
		// * sets bit at position to on or off
		// * position can exceed the scope of bitfield, meaning greater than 32 bits
		_H3API_ VOID SetState(INT32 position, BOOL state);
		// * Sets bitfield to specified value
		_H3API_ VOID Set(UINT32 value);
		// * Gets bitfield value as 32bits
		_H3API_ UINT Get() const;
	};

	// * a 8x6 mask for objects within h3
	struct H3ObjectMask
	{
		H3Bitfield m_bits[2];

		_H3API_ VOID operator=(const H3ObjectMask& other);
	};

	// * represents a point on the map
	struct H3Point
	{
		INT x;
		INT y;
		INT z;
	};
#pragma pack(pop)
} // namespace h3

namespace h3
{
	// * these are internal to H3API to avoid conflicts
	namespace H3Internal
	{
		_H3API_ INT _gameWidth();
		_H3API_ INT _gameHeight();
		_H3API_ INT8 _gameEdgeHorizontal();
		_H3API_ INT8 _gameEdgeVertical();
		_H3API_ INT _h3_MapSize();
		_H3API_ UINT8 _h3_BitMode();
		_H3API_ PCHAR _h3_textBuffer();
	} // namespace H3Internal
} // namespace h3

#endif /* #define _H3BASE_HPP_ */