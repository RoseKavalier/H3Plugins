//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-07-11                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3TYPES_HPP_
#define _H3TYPES_HPP_

/**
 * This file defines the various types used within H3API.
 * You can include only this file in your headers to speed up compilation
 * when you don't need to use any of the H3API-specific structures.
 */

/**
 * Slaps top of car
 * This bad boy can hold just about anything
 */
typedef void(*naked_t)();
/**
 * Naked function type used for basic hook types.
*/
typedef void(*H3NakedFunction)();
/**
 * generic typedef to indicate this is a h3 function
 */
typedef unsigned long h3func;
/**
 * 1-byte sized boolean.
 * bool is not used as its size is not guaranteed to be 1
 */
typedef char          BOOL8;
/**
 * Used for unknown structure members, general 8-bit case
 */
typedef char          h3unk, h3unk8;
/**
 * Used for unknown structure members, 16-bit case
 */
typedef short         h3unk16;
/**
 * Used for unknown structure members, 32-bit case
 */
typedef int           h3unk32;
/**
 * Used for alignment/padding of structure members
 */
typedef char          h3align;

/*
 * for uniformity's sake, use a typedef instead of define
 */
#ifdef VOID
#undef VOID
#endif

/**
 * typedef safety declarations
 * no checks are needed here based on C++03 Standard 7.1.3 typedef specifier
 * https://stackoverflow.com/questions/8594954/repeated-typedefs-invalid-in-c-but-valid-in-c?answertab=votes#tab-top
 */

typedef int              INT,    *PINT;
typedef unsigned int     UINT,   *PUINT;
typedef signed char      INT8,   *PINT8;
typedef signed short     INT16,  *PINT16;
typedef signed int       INT32,  *PINT32;
typedef signed __int64   INT64,  *PINT64;
typedef unsigned char    UINT8,  *PUINT8;
typedef unsigned short   UINT16, *PUINT16;
typedef unsigned int     UINT32, *PUINT32;
typedef unsigned __int64 UINT64, *PUINT64;
typedef int              BOOL,    BOOL32;
typedef float            FLOAT;
typedef                  FLOAT   *PFLOAT;
typedef double           DOUBLE;
typedef                  DOUBLE  *PDOUBLE;
typedef char             CHAR;
typedef                  CHAR    *PCHAR;
typedef unsigned char    UCHAR;
typedef                  UCHAR   *PUCHAR;
typedef unsigned char    BYTE;
typedef                  BYTE    *PBYTE;
typedef unsigned short   WORD;
typedef                  WORD    *PWORD;
typedef unsigned long    DWORD;
typedef                  DWORD   *PDWORD;
typedef const char*      LPCSTR;
typedef void             VOID,   *PVOID;

namespace h3
{
	typedef unsigned int ADDRESS;
}

/**
 * forward declaration for patcher_x86's Patcher class
 */
class Patcher;
/**
 * forward declaration for patcher_x86's PatcherInstance class
 */
class PatcherInstance;

#endif /* _H3TYPES_HPP_ */
