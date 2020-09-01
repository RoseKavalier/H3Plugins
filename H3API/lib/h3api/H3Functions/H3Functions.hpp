//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3FUNCTIONS_HPP_
#define _H3FUNCTIONS_HPP_

#include "../H3_Base.hpp"
#include "../H3_String.hpp"
#include "../H3_Structures.hpp"

namespace h3
{
	// * inserts a breakpoint for quick stop using debugger
	_H3API_ VOID          F_Breakpoint();
	// * Gets cursor coordinates within game window
	_H3API_ VOID          F_GetCursorPosition(INT& x, INT& y);
	// * Gets cursor coordinates within game window
	_H3API_ VOID          F_GetCursorPosition(POINT& p);
	// * given power ratio k, returns the diplomacy power factor
	_H3API_ INT32         F_GetDiplomacyPowerFactor(FLOAT k);
	// * returns a creature's upgraded version id
	_H3API_ INT32         F_GetCreatureUpgrade(INT id);
	// * checks whether the given creature has an upgraded version
	_H3API_ BOOL8         F_CreatureHasUpgrade(INT id);
	// * GetModuleFileNameA using h3 assets
	_H3API_ INT           F_GetModuleFileNameA(HMODULE hmodule, PCHAR buf, INT bufLen = MAX_PATH);
	// * GetCurrentDirectoryA using h3 assets
	_H3API_ INT           F_GetCurrentDirectory(PCHAR buf, INT bufLen = MAX_PATH);
	// * SetCurrentDirectoryA using h3 assets
	_H3API_ BOOL          F_SetCurrentDirectory(LPCSTR dir);
	// * GetCurrentDirectoryA using h3 assets
	// * Assigned to path string and adds terminating '\' at request
	_H3API_ BOOL          F_GetCurrentDirectory(H3String& path, BOOL add_backslash);
	// * message box with text shown (default h3_TextBuffer) on right mouse button click
	_H3API_ VOID          F_MessageBoxRMB(LPCSTR text = h3_TextBuffer);
	_H3API_ VOID          F_MessageBoxRMB(const H3String& text);
	// * message box with text shown (default h3_TextBuffer) with an 'OK' button
	_H3API_ VOID          F_MessageBox(LPCSTR text = h3_TextBuffer);
	_H3API_ VOID          F_MessageBox(const H3String& text);
	// * message box with 'OK' and 'Cancel' buttons
	// * returns true if clicked 'OK'
	_H3API_ BOOL          F_MessageBoxChoice(LPCSTR text = h3_TextBuffer);
	// * prints text to the log screen (default h3_TextBuffer)
	_H3API_ VOID          F_PrintScreenText(LPCSTR text = h3_TextBuffer);
	// * checks whether the active player can view given coordinates
	_H3API_ BOOL          F_CanViewTile(INT x, INT y, INT z);
	// * Pointer to vision information of coordinates
	_H3API_ H3TileVision* F_GetTileVision(INT x, INT y, INT z);

	_H3API_ H3Map_TileVision     F_GetTileVisionMap();
	_H3API_ H3FastMap_TileVision F_GetTileVisionFastMap();

	// * reveals tile for current player at coordinates
	_H3API_ VOID          F_ReveaTile(INT x, INT y, INT z);
	// * timeGetTime using H3 assets
	_H3API_ DWORD         F_GetTime();
	// * reverses string in buffer, returned to buffer
	_H3API_ PCHAR         F_strRev(PCHAR buffer);
	// * FindFirstFileA using H3 assets
	_H3API_ HANDLE        F_FindFirstFileA(LPCSTR path, WIN32_FIND_DATAA& data);
	// * FindFirstFileA using H3 assets
	_H3API_ HANDLE        F_FindFirstFileA(H3String& path, WIN32_FIND_DATAA& data);
	// * FindNextFileA using H3 assets
	_H3API_ HANDLE        F_FindNextFileA(HANDLE handle, WIN32_FIND_DATAA& data);
	// * FindClose using H3 assets
	_H3API_ BOOL          F_FindClose(HANDLE handle);
	// * GetFileAttributes using H3 assets
	_H3API_ DWORD         F_GetFileAttributesA(LPCSTR name);
	// * GetFullPathNameA using H3 assets
	_H3API_ DWORD         F_GetFullPathNameA(LPCSTR fileName, DWORD bufferLength, PCHAR buffer);
	// * converts text to integer using H3 assets
	_H3API_ INT32         F_atoi(LPCSTR text);
	_H3API_ INT32         F_atoi(const H3String& text);
	// * converts text to double using H3 assets
	_H3API_ DOUBLE        F_atof(LPCSTR text);
	_H3API_ DOUBLE        F_atof(const H3String& text);
	// * compares two strings up to len characters
	_H3API_ INT           F_strnicmp(LPCSTR string1, LPCSTR string2, INT len);
	// * copies len characters from source to dest
	_H3API_ PCHAR         F_strncpy(LPCSTR dest, LPCSTR src, INT len);
	// * Checks if the current game features more than 1 human
	_H3API_ BOOL8         F_Multiplayer();
	// * Checks if the current spell at given level is single-target or not
	_H3API_ BOOL8         F_SingleTargetSpell(INT32 spell, INT expertise);


	_H3API_ INT           F_MultiplayerRNG(INT min_value, INT max_value);
	_H3API_ H3String      F_GetLocalTime();
	_H3API_ FILE*         F_fopen(LPCSTR filename, LPCSTR mode);
	_H3API_ INT           F_fclose(FILE* f);
	_H3API_ DWORD         F_ftell(FILE* f);
	_H3API_ INT           F_fseek(FILE* f, INT offset, INT origin);
	_H3API_ DWORD         F_GetFileSize(FILE* f);
	_H3API_ BOOL          F_fread(PVOID buffer, size_t size, size_t count, FILE* f);
	_H3API_ size_t        F_fwrite(const VOID* buffer, size_t size, size_t count, FILE* f);
	_H3API_ INT           F_fsetpos(FILE* f, const fpos_t& pos);
	_H3API_ INT           F_fgetpos(FILE* f, fpos_t& pos);
	_H3API_ INT           F_fputc(const CHAR c, FILE* f);
	_H3API_ INT           F_strtol(LPCSTR str, INT base, PCHAR* end = nullptr);
	_H3API_ INT           F_strtol(const H3String& str, INT base, PCHAR* end = nullptr);
	_H3API_ UINT          F_strtoul(LPCSTR str, INT base, PCHAR* end = nullptr);
	_H3API_ UINT          F_strtoul(const H3String& str, INT base, PCHAR* end = nullptr);
	_H3API_ PCHAR         F_strtok(LPCSTR str, LPCSTR delimiters);
	_H3API_ LPCSTR        F_GetTownName(INT town_id);
	_H3API_ BOOL          F_CloseHandle(HANDLE handle);
	_H3API_ HANDLE        F_CreateFile(LPCSTR file, BOOL openExisting);
	_H3API_ DWORD         F_GetFileSize(HANDLE handle);
	_H3API_ BOOL          F_ReadFile(HANDLE handle, PVOID data, DWORD bytesToRead);
	_H3API_ DWORD         F_SetFilePointer(HANDLE handle, LONG position, DWORD source);
	_H3API_ BOOL          F_WriteFile(HANDLE handle, PVOID buffer, DWORD bytesToWrite);

	// * used to get coordinates of map data that is stored as an array
	// * e.g. H3MapItems, RMG_MapItems, H3TileVision
	template<typename T>
	H3Point F_ReverseCoordinates(T* current_point, T* base_point, UINT map_size);

	_H3API_ H3UniquePtr<WCHAR> F_utf8ToUnicode(LPCSTR utf8);
	_H3API_ H3UniquePtr<WCHAR> F_AnsiToUnicode(LPCSTR ansi);
}

#endif /* #define _H3FUNCTIONS_HPP_ */