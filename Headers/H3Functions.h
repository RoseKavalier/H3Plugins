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

#ifndef _H3FUNCTIONS_H_
#define _H3FUNCTIONS_H_

#pragma once

#include "H3Base.h"
#include "H3Structures.h"
#include "H3Defines.h"

// * inserts a breakpoint for quick stop using debugger
inline void F_Breakpoint()
{
	if (IsDebuggerPresent())
		__asm int 3;
}

// * Gets cursor coordinates within game window
inline void F_GetCursorPosition(INT &x, INT &y)
{
	STDCALL_2(void, 0x50D700, &x, &y);
}

// * Gets cursor coordinates within game window
inline void F_GetCursorPosition(POINT & p)
{
	STDCALL_2(void, 0x50D700, &p.x, &p.y);
}

// * given power ratio k, returns the diplomacy power factor
inline INT32 F_GetDiplomacyPowerFactor(float k)
{
	return STDCALL_1(INT32, 0x4A7330, k);
}

// * returns a creature's upgraded version id
inline INT32 F_GetCreatureUpgrade(INT id)
{
	return THISCALL_1(INT32, 0x47AAD0, id);
}

// * checks whether the given creature has an upgraded version
inline BOOL8 F_CreatureHasUpgrade(INT id)
{
	return THISCALL_1(BOOL8, 0x47AA50, id);
}

// * GetCurrentDirectoryA using h3 assets
inline INT F_GetCurrentDirectory(PCHAR buf, INT bufLen)
{
	return STDCALL_2(INT, IntAt(0x63A1A4), bufLen, buf);
}

// * message box with text shown (default h3_TextBuffer) on right mouse button click
inline void F_MessageBoxRMB(PCHAR text = h3_TextBuffer)
{
	FASTCALL_12(void, 0x4F6C00, text, 4, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
}

// * message box with text shown (default h3_TextBuffer) with an 'OK' button
inline void F_MessageBox(PCHAR text = h3_TextBuffer)
{
	FASTCALL_12(void, 0x4F6C00, text, 1, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
}

// * message box with 'OK' and 'Cancel' buttons
// * returns true if clicked 'OK'
inline BOOL F_MessageBoxChoice(PCHAR text = h3_TextBuffer)
{
	FASTCALL_12(void, 0x4F6C00, text, 2, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
	return H3Pointers::WindowManager()->ClickedOK();
}

// * prints text to the log screen (default h3_TextBuffer)
inline void F_PrintScreenText(PCHAR text = h3_TextBuffer)
{
	CDECL_3(void, 0x553C40, 0x69D800, "%s", text);
}

// * checks whether the active player can view given coordinates
inline BOOL F_CanViewTile(INT x, INT y, INT z)
{
	return (FASTCALL_3(UINT8, 0x4F8040, x, y, z) & h3_ActivePlayerBitset);
}

// * Pointer to vision information of coordinates
inline H3TileVision* F_GetTileVision(INT x, INT y, INT z)
{
	return FASTCALL_3(H3TileVision*, 0x4F8070, x, y, z);
}

// * reveals tile for current player at coordinates
inline void F_ReveaTile(INT x, INT y, INT z)
{
	F_GetTileVision(x, y, z)->vision |= h3_ActivePlayerBitset;
}

// * timeGetTime using H3 assets
inline DWORD F_GetTime()
{
	return STDCALL_0(DWORD, PtrAt(0x63A354));
}

// * reverses string in buffer, returned to buffer
inline PCHAR F_strRev(PCHAR buffer)
{
	return CDECL_1(PCHAR, 0x627690, buffer);
}

// * FindFirstFileA using H3 assets
inline HANDLE F_FindFirstFileA(PCHAR path, WIN32_FIND_DATAA & data)
{
	return STDCALL_2(HANDLE, PtrAt(0x63A11C), path, &data);
}

// * FindFirstFileA using H3 assets
inline HANDLE F_FindFirstFileA(H3String & path, WIN32_FIND_DATAA & data)
{
	return STDCALL_2(HANDLE, PtrAt(0x63A11C), path.String(), &data);
}

// * FindNextFileA using H3 assets
inline HANDLE F_FindNextFileA(HANDLE handle, WIN32_FIND_DATAA & data)
{
	return STDCALL_2(HANDLE, PtrAt(0x63A120), handle, &data);
}

// * converts text to integer using H3 assets
inline INT32 F_atoi(PCHAR text)
{
	return CDECL_1(INT32, 0x6184D9, text);
}

// * compares two strings up to len characters
inline INT F_strnicmp(PCHAR string1, PCHAR string2, INT len)
{
	return CDECL_3(INT, 0x626680, string1, string2, len);
}

// * compares two strings, not-case-sensitive
inline BOOL F_strcmpi(PCHAR string1, PCHAR string2)
{
	return CDECL_2(BOOL, 0x6197C0, string1, string2);
}

// * copies len characters from source to dest
inline PCHAR  F_strncpy(PCHAR dest, PCHAR src, INT len)
{
	return CDECL_3(PCHAR, 0x618FE0, dest, src, len);
}

// * heap realloc using H3 assets
inline PVOID F_realloc(PVOID obj, UINT new_size)
{
	return CDECL_2(PVOID, 0x619890, obj, new_size);
}

// * heapalloc using H3 assets
inline PVOID F_malloc(UINT size)
{
	return CDECL_1(PVOID, 0x617492, size);
}

// * heapfree using H3 assets
inline void F_delete(PVOID obj)
{
	if (obj)
		CDECL_1(void, 0x60B0F0, (PVOID)obj);
}

// * memcpy using H3 assets
inline void F_memcpy(PVOID dest, PVOID src, UINT len)
{
	CDECL_3(void, 0x61AD70, dest, src, len);
}

// * Checks if the current game features more than 1 human
inline BOOL8 F_Multiplayer()
{
	return STDCALL_0(BOOL8, 0x4CE950);
}

// * sets dest to value
inline PVOID F_memset(PVOID dest, UINT value, UINT len)
{
	return CDECL_3(PVOID, 0x61B7E0, dest, value, len);
}

// * converts text to wide char, destination is buffer that needs to be pre-allocated
inline LPCWSTR F_MultiByteToWideChar(PCHAR text, int textLength, WCHAR *buffer)
{
	return STDCALL_6(LPCWSTR, PtrAt(0x63A1CC), CP_ACP, 0, text, textLength, buffer, textLength);
}

#endif /* #define _H3FUNCTIONS_H_ */