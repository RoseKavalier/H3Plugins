//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-05-28                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3_CONFIG_HPP_
#define _H3_CONFIG_HPP_

// * Prevents some warnings
#define _CRT_SECURE_NO_WARNINGS

#ifndef _WINDOWS_
// * Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// * use std::min and std::max instead
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
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

#ifndef _LIMITS_
#include <limits>
#endif

#if (__cplusplus >= 199711L || (_MSC_VER && _MSC_VER >= 1500))
// * true if your compiler is C++98 compatible
#define _H3API_CPLUSPLUS98_
#endif

#if (__cplusplus >= 201103L || (_MSC_VER && _MSC_VER >= 1900))
// * true if your compiler is C++11 compatible
// * this checks for C++11 standard or Visual Studio 2015+ because VS2013 is not fully compliant
#define _H3API_CPLUSPLUS11_
#endif

#if (__cplusplus >= 201402L || (_MSC_VER && _MSC_VER >= 1900))
// * true if your compiler is C++14 compatible
#define _H3API_CPLUSPLUS14_
#endif

#if (__cplusplus >= 201703L || (_MSC_VER && _MSC_VER >= 1910))
// * true if your compiler is C++14 compatible
#define _H3API_CPLUSPLUS17_
#endif

#if (_MSC_VER && _MSC_VER <= 1500)
#pragma warning (disable:4482)
#endif

#ifndef _H3API_CPLUSPLUS11_
#ifndef nullptr
// * nullptr was added with C++11
#define nullptr NULL
#endif
#ifndef constexpr
// * constexpr was added with C++11
#define constexpr const
#endif
#ifndef _H3API_ENUM_
// * enum class was added with C++11
#define _H3API_ENUM_ enum
#endif
#ifndef noexcept
// * noexcept keyword added with C++11
#define noexcept throw()
#endif
#ifndef override
// * override keyword comes with C++11 and is used for a few virtual functions
#define override
#endif
#else
#ifndef _H3API_ENUM_
// * enum class
#define _H3API_ENUM_ enum class
#endif
#endif

#if _MSC_VER && _MSC_VER >= 1900
#ifndef _H3API_DEPRECATED_
// * indicates this content is deprecated
// * and replaced by equivalent expressions
#define _H3API_DEPRECATED_(msg) [[deprecated(msg)]]
#endif
#elif _MSC_VER
#ifndef _H3API_DEPRECATED_
// * indicates this content is deprecated
// * and replaced by equivalent expressions
#define _H3API_DEPRECATED_(msg) __declspec(deprecated(msg))
#endif
#elif defined(__GNUC__) || defined(__clang__)
#ifndef _H3API_DEPRECATED_
// * indicates this content is deprecated
// * and replaced by equivalent expressions
#define _H3API_DEPRECATED_(msg) __attribute__((deprecated(msg)))
#endif
#else
#pragma message("WARNING: _H3API_DEPRECATED_ is not implemented for this compiler.")
#ifndef _H3API_DEPRECATED_
// * indicates this content is deprecated
// * and replaced by equivalent expressions
#define _H3API_DEPRECATED_
#endif
#endif

#ifdef _MSC_VER
#ifndef __H3API_FORCEINLINE_
// * used to force function to be inline
#define __H3API_FORCEINLINE_ __forceinline
#endif
#elif defined(__GNUC__)
#ifndef __H3API_FORCEINLINE_
// * used to force function to be inline
#define __H3API_FORCEINLINE_ inline __attribute__((__always_inline__))
#endif
#elif defined(__CLANG__)
#if __has_attribute(__always_inline__)
#ifndef __H3API_FORCEINLINE_
// * used to force function to be inline
#define __H3API_FORCEINLINE_ inline __attribute__((__always_inline__))
#endif
#else
#ifndef __H3API_FORCEINLINE_
// * used to force function to be inline
#define __H3API_FORCEINLINE_ inline
#endif
#endif
#else
#ifndef __H3API_FORCEINLINE_
// * used to force function to be inline
#define __H3API_FORCEINLINE_ inline
#endif
#endif

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

#ifndef _H3API_DECLARE_
// * forward-defines a struct, pointer to struct and reference to struct
#define _H3API_DECLARE_(NAME) struct NAME; typedef struct NAME *P ## NAME; typedef struct NAME &R ## NAME;
#endif

#ifndef _H3API_EXPORT_
// * exports a function without name mangling
// * to use, type the following within a function's definition:
// * #pragma _H3API_EXPORT_
#define _H3API_EXPORT_ comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
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
#ifndef ValueAsDword
// * used to get the hexadecimal value of a type T instead of getting a casted value
#define ValueAsDword(value) (DwordAt(&(value)))
#endif
#pragma endregion Access Macros

#ifndef _H3API_STR_EXPAND_
// * inserts text representation of macro
#define _H3API_STR_EXPAND_(x) #x
#endif

#ifndef _H3API_STR_
// * expands a macro into its actual text
#define _H3API_STR_(x) _H3API_STR_EXPAND_(x)
#endif

namespace h3
{
	// * based on https://stackoverflow.com/a/1980156 by Gregory Pakosz
#ifndef _H3API_STATIC_ASSERT_
#ifdef _H3API_NO_VALIDATION_
	// * disabled compilation-time assertion
	// * undefine _H3API_NO_VALIDATION_ to enable these checks
#define _H3API_STATIC_ASSERT_(condition, message)
#else /* !_H3API_NO_VALIDATION_ */
#ifdef _H3API_CPLUSPLUS11_

	// * a compile-time assertion to ensure integrity of structure size and use of some templates
	// * define _H3API_NO_VALIDATION_ to remove these checks
#define _H3API_STATIC_ASSERT_(condition, message) static_assert(condition, message)
#else /* !_H3API_CPLUSPLUS11_ */
	namespace H3Internal
	{
		template<bool>  struct H3StaticAssert;
		template<>      struct H3StaticAssert<true> {};
		template<int i>	struct H3StaticAssertTest {};
	}

#define _H3API_CONCATENATE2_(arg1, arg2)  arg1 ## arg2
#define _H3API_CONCATENATE1_(arg1, arg2)  _H3API_CONCATENATE2_(arg1, arg2)
#define _H3API_CONCATENATE_(arg1, arg2)   _H3API_CONCATENATE1_(arg1, arg2)

	// * ugly but it should get the job done...

	// * a compile-time assertion to ensure integrity of structure size and use of some templates
	// * $message is not used and is simply a placeholder for static_assert
	// * define _H3API_NO_VALIDATION_ to remove these checks
#define _H3API_STATIC_ASSERT_(condition, message)\
	struct _H3API_CONCATENATE_(H3StaticAssertion_at_line_, __LINE__)\
	{\
	h3::H3Internal::H3StaticAssert<static_cast<bool>((condition))> _H3API_CONCATENATE_(H3_STATIC_ASSERTION_FAILED_AT_LINE_, __LINE__);\
	};\
	typedef h3::H3Internal::H3StaticAssertTest<sizeof(_H3API_CONCATENATE_(H3StaticAssertion_at_line_, __LINE__))> _H3API_CONCATENATE_(H3StaticAssertionTest_at_line_ , __LINE__)

#endif /* _H3API_CPLUSPLUS11_ */
#endif /* _H3API_NO_VALIDATION_ */
#endif /* _H3API_STATIC_ASSERT_ */

	namespace H3Internal
	{
		// * std::enable_if is only available as of C++11
		template<bool condition, class T = VOID>
		struct enable_if {};
		// * std::enable_if is only available as of C++11
		template<class T>
		struct enable_if<true, T> { typedef T type; };
	}

	// * this region declares a number of template functions to be used to call H3 functions;
// * template functions are superior to the old macro-style as there is no forced conversion
// * of arguments to a specific type; there is no longer complicated logic required to
// * pass a float or double to a function, it is done implicitly;
// * for ease of use, the old macros still exist and refer to these new templates;
// * these are generated via script, if you need more arguments for some reason request them;
// * in a perfect world without pre C++11, these would not be required...
#pragma region Function_Templates

	namespace H3Internal
	{
#pragma region Stdcall_Templates
		template<typename return_type>
		inline return_type H3Stdcall_0(UINT address)
		{
			return (reinterpret_cast<return_type(__stdcall*)()>(address)());
		}
		template<typename return_type, typename Arg1>
		inline return_type H3Stdcall_1(UINT address, Arg1 a1)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1)>(address)(a1));
		}
		template<typename return_type, typename Arg1, typename Arg2>
		inline return_type H3Stdcall_2(UINT address, Arg1 a1, Arg2 a2)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2)>(address)(a1, a2));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3>
		inline return_type H3Stdcall_3(UINT address, Arg1 a1, Arg2 a2, Arg3 a3)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3)>(address)(a1, a2, a3));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		inline return_type H3Stdcall_4(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4)>(address)(a1, a2, a3, a4));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		inline return_type H3Stdcall_5(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5)>(address)(a1, a2, a3, a4, a5));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
		inline return_type H3Stdcall_6(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)>(address)(a1, a2, a3, a4, a5, a6));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
		inline return_type H3Stdcall_7(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)>(address)(a1, a2, a3, a4, a5, a6, a7));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
		inline return_type H3Stdcall_8(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)>(address)(a1, a2, a3, a4, a5, a6, a7, a8));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
		inline return_type H3Stdcall_9(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
		inline return_type H3Stdcall_10(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11>
		inline return_type H3Stdcall_11(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12>
		inline return_type H3Stdcall_12(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13>
		inline return_type H3Stdcall_13(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14>
		inline return_type H3Stdcall_14(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15>
		inline return_type H3Stdcall_15(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16>
		inline return_type H3Stdcall_16(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17>
		inline return_type H3Stdcall_17(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18>
		inline return_type H3Stdcall_18(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19>
		inline return_type H3Stdcall_19(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19, typename Arg20>
		inline return_type H3Stdcall_20(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19, Arg20 a20)
		{
			return (reinterpret_cast<return_type(__stdcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19, Arg20)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20));
		}
#pragma endregion
#pragma region Thiscall_Templates
		template<typename return_type>
		inline return_type H3Thiscall_0(UINT address)
		{
			return (reinterpret_cast<return_type(__thiscall*)()>(address)());
		}
		template<typename return_type, typename Arg1>
		inline return_type H3Thiscall_1(UINT address, Arg1 a1)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1)>(address)(a1));
		}
		template<typename return_type, typename Arg1, typename Arg2>
		inline return_type H3Thiscall_2(UINT address, Arg1 a1, Arg2 a2)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2)>(address)(a1, a2));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3>
		inline return_type H3Thiscall_3(UINT address, Arg1 a1, Arg2 a2, Arg3 a3)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3)>(address)(a1, a2, a3));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		inline return_type H3Thiscall_4(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4)>(address)(a1, a2, a3, a4));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		inline return_type H3Thiscall_5(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5)>(address)(a1, a2, a3, a4, a5));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
		inline return_type H3Thiscall_6(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)>(address)(a1, a2, a3, a4, a5, a6));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
		inline return_type H3Thiscall_7(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)>(address)(a1, a2, a3, a4, a5, a6, a7));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
		inline return_type H3Thiscall_8(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)>(address)(a1, a2, a3, a4, a5, a6, a7, a8));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
		inline return_type H3Thiscall_9(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
		inline return_type H3Thiscall_10(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11>
		inline return_type H3Thiscall_11(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12>
		inline return_type H3Thiscall_12(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13>
		inline return_type H3Thiscall_13(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14>
		inline return_type H3Thiscall_14(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15>
		inline return_type H3Thiscall_15(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16>
		inline return_type H3Thiscall_16(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17>
		inline return_type H3Thiscall_17(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18>
		inline return_type H3Thiscall_18(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19>
		inline return_type H3Thiscall_19(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19, typename Arg20>
		inline return_type H3Thiscall_20(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19, Arg20 a20)
		{
			return (reinterpret_cast<return_type(__thiscall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19, Arg20)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20));
		}
#pragma endregion
#pragma region Fastcall_Templates
		template<typename return_type>
		inline return_type H3Fastcall_0(UINT address)
		{
			return (reinterpret_cast<return_type(__fastcall*)()>(address)());
		}
		template<typename return_type, typename Arg1>
		inline return_type H3Fastcall_1(UINT address, Arg1 a1)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1)>(address)(a1));
		}
		template<typename return_type, typename Arg1, typename Arg2>
		inline return_type H3Fastcall_2(UINT address, Arg1 a1, Arg2 a2)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2)>(address)(a1, a2));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3>
		inline return_type H3Fastcall_3(UINT address, Arg1 a1, Arg2 a2, Arg3 a3)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3)>(address)(a1, a2, a3));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		inline return_type H3Fastcall_4(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4)>(address)(a1, a2, a3, a4));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		inline return_type H3Fastcall_5(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5)>(address)(a1, a2, a3, a4, a5));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
		inline return_type H3Fastcall_6(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)>(address)(a1, a2, a3, a4, a5, a6));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
		inline return_type H3Fastcall_7(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)>(address)(a1, a2, a3, a4, a5, a6, a7));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
		inline return_type H3Fastcall_8(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)>(address)(a1, a2, a3, a4, a5, a6, a7, a8));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
		inline return_type H3Fastcall_9(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
		inline return_type H3Fastcall_10(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11>
		inline return_type H3Fastcall_11(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12>
		inline return_type H3Fastcall_12(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13>
		inline return_type H3Fastcall_13(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14>
		inline return_type H3Fastcall_14(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15>
		inline return_type H3Fastcall_15(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16>
		inline return_type H3Fastcall_16(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17>
		inline return_type H3Fastcall_17(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18>
		inline return_type H3Fastcall_18(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19>
		inline return_type H3Fastcall_19(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19, typename Arg20>
		inline return_type H3Fastcall_20(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19, Arg20 a20)
		{
			return (reinterpret_cast<return_type(__fastcall*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19, Arg20)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20));
		}
#pragma endregion
#pragma region Cdecl_Templates
		template<typename return_type>
		inline return_type H3Cdecl_0(UINT address)
		{
			return (reinterpret_cast<return_type(__cdecl*)()>(address)());
		}
		template<typename return_type, typename Arg1>
		inline return_type H3Cdecl_1(UINT address, Arg1 a1)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1)>(address)(a1));
		}
		template<typename return_type, typename Arg1, typename Arg2>
		inline return_type H3Cdecl_2(UINT address, Arg1 a1, Arg2 a2)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2)>(address)(a1, a2));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3>
		inline return_type H3Cdecl_3(UINT address, Arg1 a1, Arg2 a2, Arg3 a3)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3)>(address)(a1, a2, a3));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		inline return_type H3Cdecl_4(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4)>(address)(a1, a2, a3, a4));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		inline return_type H3Cdecl_5(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5)>(address)(a1, a2, a3, a4, a5));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
		inline return_type H3Cdecl_6(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)>(address)(a1, a2, a3, a4, a5, a6));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
		inline return_type H3Cdecl_7(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)>(address)(a1, a2, a3, a4, a5, a6, a7));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
		inline return_type H3Cdecl_8(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)>(address)(a1, a2, a3, a4, a5, a6, a7, a8));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
		inline return_type H3Cdecl_9(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
		inline return_type H3Cdecl_10(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11>
		inline return_type H3Cdecl_11(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12>
		inline return_type H3Cdecl_12(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13>
		inline return_type H3Cdecl_13(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14>
		inline return_type H3Cdecl_14(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15>
		inline return_type H3Cdecl_15(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16>
		inline return_type H3Cdecl_16(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17>
		inline return_type H3Cdecl_17(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18>
		inline return_type H3Cdecl_18(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19>
		inline return_type H3Cdecl_19(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19));
		}
		template<typename return_type, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19, typename Arg20>
		inline return_type H3Cdecl_20(UINT address, Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9, Arg10 a10, Arg11 a11, Arg12 a12, Arg13 a13, Arg14 a14, Arg15 a15, Arg16 a16, Arg17 a17, Arg18 a18, Arg19 a19, Arg20 a20)
		{
			return (reinterpret_cast<return_type(__cdecl*)(Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9, Arg10, Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, Arg17, Arg18, Arg19, Arg20)>(address)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20));
		}
#pragma endregion
	} /* namespace H3Internal */
#pragma endregion

#pragma region Model Functions macros
#pragma region STDCALL_DECLARATIONS
#ifndef STDCALL_0
#define STDCALL_0(return_type, address) h3::H3Internal::H3Stdcall_0<return_type>(UINT(address))
#endif
#ifndef STDCALL_1
#define STDCALL_1(return_type, address, arg1) h3::H3Internal::H3Stdcall_1<return_type>(UINT(address), arg1)
#endif
#ifndef STDCALL_2
#define STDCALL_2(return_type, address, arg1, arg2) h3::H3Internal::H3Stdcall_2<return_type>(UINT(address), arg1, arg2)
#endif
#ifndef STDCALL_3
#define STDCALL_3(return_type, address, arg1, arg2, arg3) h3::H3Internal::H3Stdcall_3<return_type>(UINT(address), arg1, arg2, arg3)
#endif
#ifndef STDCALL_4
#define STDCALL_4(return_type, address, arg1, arg2, arg3, arg4) h3::H3Internal::H3Stdcall_4<return_type>(UINT(address), arg1, arg2, arg3, arg4)
#endif
#ifndef STDCALL_5
#define STDCALL_5(return_type, address, arg1, arg2, arg3, arg4, arg5) h3::H3Internal::H3Stdcall_5<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5)
#endif
#ifndef STDCALL_6
#define STDCALL_6(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6) h3::H3Internal::H3Stdcall_6<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6)
#endif
#ifndef STDCALL_7
#define STDCALL_7(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7) h3::H3Internal::H3Stdcall_7<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#endif
#ifndef STDCALL_8
#define STDCALL_8(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) h3::H3Internal::H3Stdcall_8<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
#endif
#ifndef STDCALL_9
#define STDCALL_9(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) h3::H3Internal::H3Stdcall_9<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
#endif
#ifndef STDCALL_10
#define STDCALL_10(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) h3::H3Internal::H3Stdcall_10<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
#endif
#ifndef STDCALL_11
#define STDCALL_11(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) h3::H3Internal::H3Stdcall_11<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
#endif
#ifndef STDCALL_12
#define STDCALL_12(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) h3::H3Internal::H3Stdcall_12<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)
#endif
#ifndef STDCALL_13
#define STDCALL_13(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) h3::H3Internal::H3Stdcall_13<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)
#endif
#ifndef STDCALL_14
#define STDCALL_14(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) h3::H3Internal::H3Stdcall_14<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)
#endif
#ifndef STDCALL_15
#define STDCALL_15(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) h3::H3Internal::H3Stdcall_15<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)
#endif
#ifndef STDCALL_16
#define STDCALL_16(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) h3::H3Internal::H3Stdcall_16<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16)
#endif
#ifndef STDCALL_17
#define STDCALL_17(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17) h3::H3Internal::H3Stdcall_17<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17)
#endif
#ifndef STDCALL_18
#define STDCALL_18(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) h3::H3Internal::H3Stdcall_18<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18)
#endif
#ifndef STDCALL_19
#define STDCALL_19(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19) h3::H3Internal::H3Stdcall_19<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19)
#endif
#ifndef STDCALL_20
#define STDCALL_20(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20) h3::H3Internal::H3Stdcall_20<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20)
#endif
#pragma endregion
#pragma region THISCALL_DECLARATIONS
#ifndef THISCALL_0
#define THISCALL_0(return_type, address) h3::H3Internal::H3Thiscall_0<return_type>(UINT(address))
#endif
#ifndef THISCALL_1
#define THISCALL_1(return_type, address, arg1) h3::H3Internal::H3Thiscall_1<return_type>(UINT(address), arg1)
#endif
#ifndef THISCALL_2
#define THISCALL_2(return_type, address, arg1, arg2) h3::H3Internal::H3Thiscall_2<return_type>(UINT(address), arg1, arg2)
#endif
#ifndef THISCALL_3
#define THISCALL_3(return_type, address, arg1, arg2, arg3) h3::H3Internal::H3Thiscall_3<return_type>(UINT(address), arg1, arg2, arg3)
#endif
#ifndef THISCALL_4
#define THISCALL_4(return_type, address, arg1, arg2, arg3, arg4) h3::H3Internal::H3Thiscall_4<return_type>(UINT(address), arg1, arg2, arg3, arg4)
#endif
#ifndef THISCALL_5
#define THISCALL_5(return_type, address, arg1, arg2, arg3, arg4, arg5) h3::H3Internal::H3Thiscall_5<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5)
#endif
#ifndef THISCALL_6
#define THISCALL_6(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6) h3::H3Internal::H3Thiscall_6<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6)
#endif
#ifndef THISCALL_7
#define THISCALL_7(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7) h3::H3Internal::H3Thiscall_7<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#endif
#ifndef THISCALL_8
#define THISCALL_8(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) h3::H3Internal::H3Thiscall_8<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
#endif
#ifndef THISCALL_9
#define THISCALL_9(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) h3::H3Internal::H3Thiscall_9<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
#endif
#ifndef THISCALL_10
#define THISCALL_10(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) h3::H3Internal::H3Thiscall_10<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
#endif
#ifndef THISCALL_11
#define THISCALL_11(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) h3::H3Internal::H3Thiscall_11<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
#endif
#ifndef THISCALL_12
#define THISCALL_12(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) h3::H3Internal::H3Thiscall_12<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)
#endif
#ifndef THISCALL_13
#define THISCALL_13(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) h3::H3Internal::H3Thiscall_13<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)
#endif
#ifndef THISCALL_14
#define THISCALL_14(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) h3::H3Internal::H3Thiscall_14<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)
#endif
#ifndef THISCALL_15
#define THISCALL_15(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) h3::H3Internal::H3Thiscall_15<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)
#endif
#ifndef THISCALL_16
#define THISCALL_16(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) h3::H3Internal::H3Thiscall_16<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16)
#endif
#ifndef THISCALL_17
#define THISCALL_17(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17) h3::H3Internal::H3Thiscall_17<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17)
#endif
#ifndef THISCALL_18
#define THISCALL_18(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) h3::H3Internal::H3Thiscall_18<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18)
#endif
#ifndef THISCALL_19
#define THISCALL_19(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19) h3::H3Internal::H3Thiscall_19<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19)
#endif
#ifndef THISCALL_20
#define THISCALL_20(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20) h3::H3Internal::H3Thiscall_20<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20)
#endif
#pragma endregion
#pragma region FASTCALL_DECLARATIONS
#ifndef FASTCALL_0
#define FASTCALL_0(return_type, address) h3::H3Internal::H3Fastcall_0<return_type>(UINT(address))
#endif
#ifndef FASTCALL_1
#define FASTCALL_1(return_type, address, arg1) h3::H3Internal::H3Fastcall_1<return_type>(UINT(address), arg1)
#endif
#ifndef FASTCALL_2
#define FASTCALL_2(return_type, address, arg1, arg2) h3::H3Internal::H3Fastcall_2<return_type>(UINT(address), arg1, arg2)
#endif
#ifndef FASTCALL_3
#define FASTCALL_3(return_type, address, arg1, arg2, arg3) h3::H3Internal::H3Fastcall_3<return_type>(UINT(address), arg1, arg2, arg3)
#endif
#ifndef FASTCALL_4
#define FASTCALL_4(return_type, address, arg1, arg2, arg3, arg4) h3::H3Internal::H3Fastcall_4<return_type>(UINT(address), arg1, arg2, arg3, arg4)
#endif
#ifndef FASTCALL_5
#define FASTCALL_5(return_type, address, arg1, arg2, arg3, arg4, arg5) h3::H3Internal::H3Fastcall_5<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5)
#endif
#ifndef FASTCALL_6
#define FASTCALL_6(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6) h3::H3Internal::H3Fastcall_6<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6)
#endif
#ifndef FASTCALL_7
#define FASTCALL_7(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7) h3::H3Internal::H3Fastcall_7<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#endif
#ifndef FASTCALL_8
#define FASTCALL_8(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) h3::H3Internal::H3Fastcall_8<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
#endif
#ifndef FASTCALL_9
#define FASTCALL_9(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) h3::H3Internal::H3Fastcall_9<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
#endif
#ifndef FASTCALL_10
#define FASTCALL_10(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) h3::H3Internal::H3Fastcall_10<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
#endif
#ifndef FASTCALL_11
#define FASTCALL_11(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) h3::H3Internal::H3Fastcall_11<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
#endif
#ifndef FASTCALL_12
#define FASTCALL_12(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) h3::H3Internal::H3Fastcall_12<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)
#endif
#ifndef FASTCALL_13
#define FASTCALL_13(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) h3::H3Internal::H3Fastcall_13<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)
#endif
#ifndef FASTCALL_14
#define FASTCALL_14(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) h3::H3Internal::H3Fastcall_14<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)
#endif
#ifndef FASTCALL_15
#define FASTCALL_15(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) h3::H3Internal::H3Fastcall_15<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)
#endif
#ifndef FASTCALL_16
#define FASTCALL_16(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) h3::H3Internal::H3Fastcall_16<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16)
#endif
#ifndef FASTCALL_17
#define FASTCALL_17(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17) h3::H3Internal::H3Fastcall_17<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17)
#endif
#ifndef FASTCALL_18
#define FASTCALL_18(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) h3::H3Internal::H3Fastcall_18<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18)
#endif
#ifndef FASTCALL_19
#define FASTCALL_19(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19) h3::H3Internal::H3Fastcall_19<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19)
#endif
#ifndef FASTCALL_20
#define FASTCALL_20(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20) h3::H3Internal::H3Fastcall_20<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20)
#endif
#pragma endregion
#pragma region CDECL_DECLARATIONS
#ifndef CDECL_0
#define CDECL_0(return_type, address) h3::H3Internal::H3Cdecl_0<return_type>(UINT(address))
#endif
#ifndef CDECL_1
#define CDECL_1(return_type, address, arg1) h3::H3Internal::H3Cdecl_1<return_type>(UINT(address), arg1)
#endif
#ifndef CDECL_2
#define CDECL_2(return_type, address, arg1, arg2) h3::H3Internal::H3Cdecl_2<return_type>(UINT(address), arg1, arg2)
#endif
#ifndef CDECL_3
#define CDECL_3(return_type, address, arg1, arg2, arg3) h3::H3Internal::H3Cdecl_3<return_type>(UINT(address), arg1, arg2, arg3)
#endif
#ifndef CDECL_4
#define CDECL_4(return_type, address, arg1, arg2, arg3, arg4) h3::H3Internal::H3Cdecl_4<return_type>(UINT(address), arg1, arg2, arg3, arg4)
#endif
#ifndef CDECL_5
#define CDECL_5(return_type, address, arg1, arg2, arg3, arg4, arg5) h3::H3Internal::H3Cdecl_5<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5)
#endif
#ifndef CDECL_6
#define CDECL_6(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6) h3::H3Internal::H3Cdecl_6<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6)
#endif
#ifndef CDECL_7
#define CDECL_7(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7) h3::H3Internal::H3Cdecl_7<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7)
#endif
#ifndef CDECL_8
#define CDECL_8(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) h3::H3Internal::H3Cdecl_8<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
#endif
#ifndef CDECL_9
#define CDECL_9(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) h3::H3Internal::H3Cdecl_9<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
#endif
#ifndef CDECL_10
#define CDECL_10(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) h3::H3Internal::H3Cdecl_10<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
#endif
#ifndef CDECL_11
#define CDECL_11(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11) h3::H3Internal::H3Cdecl_11<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
#endif
#ifndef CDECL_12
#define CDECL_12(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) h3::H3Internal::H3Cdecl_12<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)
#endif
#ifndef CDECL_13
#define CDECL_13(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13) h3::H3Internal::H3Cdecl_13<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13)
#endif
#ifndef CDECL_14
#define CDECL_14(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14) h3::H3Internal::H3Cdecl_14<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14)
#endif
#ifndef CDECL_15
#define CDECL_15(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15) h3::H3Internal::H3Cdecl_15<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)
#endif
#ifndef CDECL_16
#define CDECL_16(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16) h3::H3Internal::H3Cdecl_16<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16)
#endif
#ifndef CDECL_17
#define CDECL_17(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17) h3::H3Internal::H3Cdecl_17<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17)
#endif
#ifndef CDECL_18
#define CDECL_18(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18) h3::H3Internal::H3Cdecl_18<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18)
#endif
#ifndef CDECL_19
#define CDECL_19(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19) h3::H3Internal::H3Cdecl_19<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19)
#endif
#ifndef CDECL_20
#define CDECL_20(return_type, address, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20) h3::H3Internal::H3Cdecl_20<return_type>(UINT(address), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20)
#endif
#pragma endregion
#pragma region VA_DECLARATIONS

// * you absolutely need c++11 to use STDCALL_VA, THISCALL_VA and FASTCALL_VA
// * in prior versions, variadic templates don't exist
// * va_list arguments would absolutely require __cdecl to clean the stack
#ifdef _H3API_CPLUSPLUS11_

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

#endif /* _H3API_CPLUSPLUS11_ */

#ifndef CDECL_VA
#define CDECL_VA(return_type, address, a1, ...) ((return_type(__cdecl *)(UINT, ...))(address))((UINT)(a1), __VA_ARGS__)
#endif

#ifndef CDECL_VA2
#define CDECL_VA2(return_type, address, a1, a2, ...) ((return_type(__cdecl *)(UINT, UINT, ...))(address))((UINT)(a1), (UINT)(a2), __VA_ARGS__)
#endif

#pragma endregion
#pragma endregion Model Functions macros

	// * objects marked with this should not be transferable
	class H3Uncopyable
	{
	public:
		H3Uncopyable() {}
	private:
		H3Uncopyable(const H3Uncopyable&);
		H3Uncopyable& operator=(const H3Uncopyable&);
	};

	// * template model to access data structures within h3 memory
	// * is_pointer indicates that the address is a pointer
	template<class type, UINT address, bool is_pointer>
	class H3DataPointer : public H3Uncopyable
	{
	public:
		typedef type* pointer;
		typedef type& reference;

		__H3API_FORCEINLINE_ H3DataPointer() :
			m_address(getAddress())
		{
		}
		reference operator*()
		{
			return *reinterpret_cast<pointer>(m_address);
		}
		pointer operator->()
		{
			return reinterpret_cast<pointer>(m_address);
		}
		pointer operator&()
		{
			return reinterpret_cast<pointer>(m_address);
		}
		// * returns itself as a way to switch between macro and typedef mode
		H3DataPointer<type, address, is_pointer>& operator()()
		{
			return *this;
		}
		operator pointer()
		{
			return reinterpret_cast<pointer>(m_address);
		}
	private:
		UINT m_address;

		__H3API_FORCEINLINE_ UINT getAddress()
		{
			return get<UINT>();
		}
		template<typename U>
		typename H3Internal::enable_if<is_pointer, U>::type get()
		{
			return *PUINT(address);
		}
		template<typename U>
		typename H3Internal::enable_if<!is_pointer, U>::type get()
		{
			return address;
		}
	};

	// * template model to access data structures that are arrays within h3 memory
	template<class type, UINT address, bool is_pointer>
	class H3DataArrayPointer : public H3Uncopyable
	{
	public:
		typedef type* pointer;
		typedef type& reference;

		__H3API_FORCEINLINE_ H3DataArrayPointer() :
			m_address(getAddress())
		{
		}
		reference operator*()
		{
			return *reinterpret_cast<pointer>(m_address);
		}
		pointer operator->()
		{
			return reinterpret_cast<pointer>(m_address);
		}
		pointer operator&()
		{
			return reinterpret_cast<pointer>(m_address);
		}
		// * returns itself as a way to switch between macro and typedef mode
		H3DataArrayPointer<type, address, is_pointer>& operator()()
		{
			return *this;
		}
		// * m_address is essentially data cast as UINT
		// * this is done so operator[] can be used in the case of pointer-type data like char*
		operator UINT()
		{
			return m_address;
		}
		reference operator[](UINT index)
		{
			return reinterpret_cast<pointer>(m_address)[index];
		}
		pointer operator()(UINT index)
		{
			return &reinterpret_cast<pointer>(m_address)[index];
		}

#ifdef _H3API_CPLUSPLUS11_
		// * access with static_cast<type*>()
		explicit operator pointer()
		{
			return *reinterpret_cast<pointer>(m_address);
		}
#endif

	private:
		UINT m_address;

		__H3API_FORCEINLINE_ UINT getAddress()
		{
			return get<UINT>();
		}
		template<typename U>
		typename H3Internal::enable_if<is_pointer, U>::type get()
		{
			return *PUINT(address);
		}
		template<typename U>
		typename H3Internal::enable_if<!is_pointer, U>::type get()
		{
			return address;
		}
	};

	// * template model to access primitive data within h3 memory
	template<class type, UINT address, bool is_pointer>
	class H3PrimitivePointer : public H3Uncopyable
	{
	public:
		typedef type* pointer;
		typedef type& reference;

		__H3API_FORCEINLINE_ H3PrimitivePointer() :
			m_address(getAddress())
		{
		}
		reference operator*()
		{
			return *reinterpret_cast<pointer>(m_address);
		}
		pointer operator&()
		{
			return reinterpret_cast<pointer>(m_address);
		}
		// * returns itself as a way to switch between macro and typedef mode
		H3PrimitivePointer<type, address, is_pointer>& operator()()
		{
			return *this;
		}
		operator type()
		{
			return *reinterpret_cast<pointer>(m_address);
		}
		void operator=(type new_data)
		{
			*reinterpret_cast<pointer>(m_address) = new_data;
		}
	private:
		UINT m_address;

		__H3API_FORCEINLINE_ UINT getAddress()
		{
			return get<UINT>();
		}
		template<typename U>
		typename H3Internal::enable_if<is_pointer, U>::type get()
		{
			return *PUINT(address);
		}
		template<typename U>
		typename H3Internal::enable_if<!is_pointer, U>::type get()
		{
			return address;
		}
	};

	// * template model to access primitive data arrays within h3 memory
	template<typename type, UINT address, bool is_pointer>
	class H3PrimitiveArrayPointer : public H3Uncopyable
	{
	public:
		typedef type* pointer;
		typedef type& reference;

		__H3API_FORCEINLINE_ H3PrimitiveArrayPointer() :
			m_address(getAddress())
		{
		}
		reference operator*()
		{
			return *reinterpret_cast<pointer>(m_address);
		}
		pointer operator&()
		{
			return reinterpret_cast<pointer>(m_address);
		}
		// * returns itself as a way to switch between macro and typedef mode
		H3PrimitiveArrayPointer<type, address, is_pointer>& operator()()
		{
			return *this;
		}
		// * m_address is essentially data cast as UINT
		// * this is done so operator[] can be used in the case of pointer-type data like char*
		operator UINT()
		{
			return m_address;
		}
		reference operator[](UINT index)
		{
			return reinterpret_cast<pointer>(m_address)[index];
		}
		type operator()(UINT index)
		{
			return reinterpret_cast<pointer>(m_address)[index];
		}
#ifdef _H3API_CPLUSPLUS11_
		// * access with static_cast<type*>()
		explicit operator pointer()
		{
			return *reinterpret_cast<pointer>(m_address);
		}
#endif
	private:
		UINT m_address;

		__H3API_FORCEINLINE_ UINT getAddress()
		{
			return get<UINT>();
		}
		template<typename U>
		typename H3Internal::enable_if<is_pointer, U>::type get()
		{
			return *PUINT(address);
		}
		template<typename U>
		typename H3Internal::enable_if<!is_pointer, U>::type get()
		{
			return address;
		}
	};
} /* namespace h3 */

#endif /* #define _H3_CONFIG_HPP_ */