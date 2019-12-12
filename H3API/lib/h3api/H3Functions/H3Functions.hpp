//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3FUNCTIONS_HPP_
#define _H3FUNCTIONS_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_String.hpp"

namespace h3
{
	// * forward declaration
	struct H3TileVision;

	// * inserts a breakpoint for quick stop using debugger
	VOID F_Breakpoint();
	// * Gets cursor coordinates within game window
	VOID F_GetCursorPosition(INT& x, INT& y);
	// * Gets cursor coordinates within game window
	VOID F_GetCursorPosition(POINT& p);
	// * given power ratio k, returns the diplomacy power factor
	INT32 F_GetDiplomacyPowerFactor(FLOAT k);
	// * returns a creature's upgraded version id
	INT32 F_GetCreatureUpgrade(INT id);
	// * checks whether the given creature has an upgraded version
	BOOL8 F_CreatureHasUpgrade(INT id);
	// * GetCurrentDirectoryA using h3 assets
	INT F_GetCurrentDirectory(PCHAR buf, INT bufLen = MAX_PATH);
	// * GetCurrentDirectoryA using h3 assets
	// * Assigned to path string and adds terminating '\' at request
	BOOL F_GetCurrentDirectory(H3String& path, BOOL add_backslash);
	// * message box with text shown (default h3_TextBuffer) on right mouse button click
	VOID F_MessageBoxRMB(LPCSTR text = h3_TextBuffer);
	// * message box with text shown (default h3_TextBuffer) with an 'OK' button
	VOID F_MessageBox(LPCSTR text = h3_TextBuffer);
	// * message box with 'OK' and 'Cancel' buttons
	// * returns true if clicked 'OK'
	BOOL F_MessageBoxChoice(LPCSTR text = h3_TextBuffer);
	// * prints text to the log screen (default h3_TextBuffer)
	VOID F_PrintScreenText(LPCSTR text = h3_TextBuffer);
	// * checks whether the active player can view given coordinates
	BOOL F_CanViewTile(INT x, INT y, INT z);
	// * Pointer to vision information of coordinates
	H3TileVision* F_GetTileVision(INT x, INT y, INT z);
	// * reveals tile for current player at coordinates
	VOID F_ReveaTile(INT x, INT y, INT z);
	// * timeGetTime using H3 assets
	DWORD F_GetTime();
	// * reverses string in buffer, returned to buffer
	PCHAR F_strRev(PCHAR buffer);
	// * FindFirstFileA using H3 assets
	HANDLE F_FindFirstFileA(LPCSTR path, WIN32_FIND_DATAA& data);
	// * FindFirstFileA using H3 assets
	HANDLE F_FindFirstFileA(H3String& path, WIN32_FIND_DATAA& data);
	// * FindNextFileA using H3 assets
	HANDLE F_FindNextFileA(HANDLE handle, WIN32_FIND_DATAA& data);
	// * converts text to integer using H3 assets
	INT32 F_atoi(LPCSTR text);
	// * compares two strings up to len characters
	INT F_strnicmp(LPCSTR string1, LPCSTR string2, INT len);
	// * copies len characters from source to dest
	PCHAR F_strncpy(LPCSTR dest, LPCSTR src, INT len);
	// * Checks if the current game features more than 1 human
	BOOL8 F_Multiplayer();
	// * converts text to wide char, destination is buffer that needs to be pre-allocated
	LPCWSTR F_MultiByteToWideChar(LPCSTR text, int textLength, WCHAR* buffer);
	INT F_MultiplayerRNG(INT min_value, INT max_value);
	INT F_GetLocalTime();
	FILE* F_fopen(LPCSTR filename, LPCSTR mode);
	int F_fclose(FILE* f);
	DWORD F_ftell(FILE* f);
	INT F_fseek(FILE* f, INT offset, INT origin);
	DWORD F_GetFileSize(FILE* f);
	size_t F_fread(PVOID buffer, size_t size, size_t count, FILE* f);
	size_t F_fwrite(const VOID* buffer, size_t size, size_t count, FILE* f);
	int F_fsetpos(FILE* f, const fpos_t& pos);
	int F_fgetpos(FILE* f, fpos_t& pos);
	int F_fputc(const CHAR c, FILE* f);
	INT F_strtol(LPCSTR str, INT base, PCHAR* end = nullptr);
	UINT F_strtoul(LPCSTR str, INT base, PCHAR* end = nullptr);
	PCHAR F_strtok(LPCSTR str, LPCSTR delimiters);
	LPCSTR F_GetTownName(int town_id);
}

#endif /* #define _H3FUNCTIONS_HPP_ */