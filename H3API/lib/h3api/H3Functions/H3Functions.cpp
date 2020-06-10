//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Functions.hpp"
#include "H3Functions.inl"
#include "../H3_Structures.hpp"

namespace h3
{
	_H3API_DEPRECATED_("Use F_utf8_to_unicode, or F_ansi_to_unicode") _H3API_ LPCWSTR F_MultiByteToWideChar(LPCSTR text, INT textLength, WCHAR * buffer)
	{
		return nullptr;
	}
	_H3API_ VOID F_Breakpoint()
	{
		if (IsDebuggerPresent())
			__asm int 3;
	}
	_H3API_ VOID F_GetCursorPosition(INT& x, INT& y)
	{
		STDCALL_2(VOID, 0x50D700, &x, &y);
	}
	_H3API_ VOID F_GetCursorPosition(POINT& p)
	{
		STDCALL_2(VOID, 0x50D700, &p.x, &p.y);
	}
	_H3API_ INT32 F_GetDiplomacyPowerFactor(FLOAT k)
	{
		return STDCALL_1(INT32, 0x4A7330, k);
	}
	_H3API_ INT32 F_GetCreatureUpgrade(INT id)
	{
		return THISCALL_1(INT32, 0x47AAD0, id);
	}
	_H3API_ BOOL8 F_CreatureHasUpgrade(INT id)
	{
		return THISCALL_1(BOOL8, 0x47AA50, id);
	}
	_H3API_ INT F_GetModuleFileNameA(HMODULE hmodule, PCHAR buf, INT bufLen)
	{
		return STDCALL_3(INT, IntAt(0x63A100), hmodule, buf, bufLen);
	}
	_H3API_ INT F_GetCurrentDirectory(PCHAR buf, INT bufLen)
	{
		return STDCALL_2(INT, IntAt(0x63A1A4), bufLen, buf);
	}
	_H3API_ BOOL F_SetCurrentDirectory(LPCSTR dir)
	{
		return STDCALL_1(BOOL, IntAt(0x63A204), dir);
	}
	_H3API_ BOOL F_GetCurrentDirectory(H3String& path, BOOL add_backslash)
	{
		if (STDCALL_2(INT, IntAt(0x63A1A4), MAX_PATH, h3_TextBuffer))
		{
			path.Assign(h3_TextBuffer);
			if (add_backslash)
				path += '\\';
			return TRUE;
		}
		return FALSE;
	}
	_H3API_ VOID F_MessageBoxRMB(LPCSTR text)
	{
		FASTCALL_12(VOID, 0x4F6C00, text, 4, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
	}
	_H3API_ VOID F_MessageBoxRMB(const H3String & text)
	{
		F_MessageBoxRMB(text.String());
	}
	_H3API_ VOID F_MessageBox(LPCSTR text)
	{
		FASTCALL_12(VOID, 0x4F6C00, text, 1, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
	}
	_H3API_ VOID F_MessageBox(const H3String & text)
	{
		F_MessageBox(text.String());
	}
	_H3API_ BOOL F_MessageBoxChoice(LPCSTR text)
	{
		FASTCALL_12(VOID, 0x4F6C00, text, 2, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
		return H3Internal::WindowManager()->ClickedOK();
	}
	_H3API_ VOID F_PrintScreenText(LPCSTR text)
	{
		CDECL_3(VOID, 0x553C40, 0x69D800, "%s", text);
	}
	_H3API_ BOOL F_CanViewTile(INT x, INT y, INT z)
	{
		return (FASTCALL_3(UINT8, 0x4F8040, x, y, z) & ByteAt(0x69CD10));
	}
	_H3API_ H3TileVision* F_GetTileVision(INT x, INT y, INT z)
	{
		return FASTCALL_3(H3TileVision*, 0x4F8070, x, y, z);
	}
	_H3API_ VOID F_ReveaTile(INT x, INT y, INT z)
	{
		F_GetTileVision(x, y, z)->vision |= ByteAt(0x69CD10);
	}
	_H3API_ DWORD F_GetTime()
	{
		return STDCALL_0(DWORD, PtrAt(0x63A354));
	}
	_H3API_ PCHAR F_strRev(PCHAR buffer)
	{
		return CDECL_1(PCHAR, 0x627690, buffer);
	}
	_H3API_ HANDLE F_FindFirstFileA(LPCSTR path, WIN32_FIND_DATAA& data)
	{
		return STDCALL_2(HANDLE, PtrAt(0x63A11C), path, &data);
	}
	_H3API_ HANDLE F_FindFirstFileA(H3String& path, WIN32_FIND_DATAA& data)
	{
		return STDCALL_2(HANDLE, PtrAt(0x63A11C), path.String(), &data);
	}
	_H3API_ HANDLE F_FindNextFileA(HANDLE handle, WIN32_FIND_DATAA& data)
	{
		return STDCALL_2(HANDLE, PtrAt(0x63A120), handle, &data);
	}
	_H3API_ BOOL F_FindClose(HANDLE handle)
	{
		return STDCALL_1(BOOL, PtrAt(0x63A118), handle);
	}
	_H3API_ DWORD F_GetFileAttributesA(LPCSTR name)
	{
		return STDCALL_1(DWORD, PtrAt(0x63A0C0), name);
	}
	_H3API_ DWORD F_GetFullPathNameA(LPCSTR fileName, DWORD bufferLength, PCHAR buffer)
	{
		return STDCALL_4(DWORD, PtrAt(0x63A1B8), fileName, bufferLength, buffer, NULL);
	}
	_H3API_ INT32 F_atoi(LPCSTR text)
	{
		return CDECL_1(INT32, 0x6184D9, text);
	}
	_H3API_ INT32 F_atoi(const H3String & text)
	{
		return F_atoi(text.String());
	}
	_H3API_ DOUBLE F_atof(LPCSTR text)
	{
		return CDECL_1(DOUBLE, 0x619366, text);
	}
	_H3API_ DOUBLE F_atof(const H3String & text)
	{
		return F_atof(text.String());
	}
	_H3API_ INT F_strnicmp(LPCSTR string1, LPCSTR string2, INT len)
	{
		return CDECL_3(INT, 0x626680, string1, string2, len);
	}
	_H3API_ PCHAR F_strncpy(LPCSTR dest, LPCSTR src, INT len)
	{
		return CDECL_3(PCHAR, 0x618FE0, dest, src, len);
	}
	_H3API_ BOOL8 F_Multiplayer()
	{
		return STDCALL_0(BOOL8, 0x4CE950);
	}
	_H3API_ BOOL8 F_SingleTargetSpell(INT32 spell, INT expertise)
	{
		return FASTCALL_2(BOOL8, 0x59E360, spell, expertise);
	}
	_H3API_ INT F_MultiplayerRNG(INT min_value, INT max_value)
	{
		return FASTCALL_2(INT, 0x50B3C0, min_value, max_value);
	}
	_H3API_ INT F_GetLocalTime()
	{
		SYSTEMTIME time;
		STDCALL_1(VOID, PtrAt(0x63A248), &time);
		return F_sprintf("%04d.%02d.%02d - %02dh%02dm%02ds", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	}
	_H3API_ FILE* F_fopen(LPCSTR filename, LPCSTR mode)
	{
		return CDECL_2(FILE*, 0x619691, filename, mode);
	}
	_H3API_ INT F_fclose(FILE* f)
	{
		return CDECL_1(int, 0x618F5E, f);
	}
	_H3API_ DWORD F_ftell(FILE* f)
	{
		return CDECL_1(DWORD, 0x6194DD, f);
	}
	_H3API_ INT F_fseek(FILE* f, INT offset, INT origin)
	{
		return CDECL_3(INT, 0x618C78, f, offset, origin);
	}
	_H3API_ DWORD F_GetFileSize(FILE* f)
	{
		F_fseek(f, 0, SEEK_END);
		DWORD size = F_ftell(f);
		F_fseek(f, 0, SEEK_SET);
		return size;
	}
	_H3API_ BOOL F_fread(PVOID buffer, size_t size, size_t count, FILE* f)
	{
		return CDECL_4(BOOL, 0x6196A4, buffer, size, count, f);
	}
	_H3API_ size_t F_fwrite(const VOID* buffer, size_t size, size_t count, FILE* f)
	{
		return CDECL_4(size_t, 0x618A1A, buffer, size, count, f);
	}
	_H3API_ INT F_fsetpos(FILE* f, const fpos_t& pos)
	{
		return CDECL_2(INT, 0x618D31, f, &pos);
	}
	_H3API_ INT F_fgetpos(FILE* f, fpos_t& pos)
	{
		return CDECL_2(INT, 0x618C56, f, &pos);
	}
	_H3API_ INT F_fputc(const CHAR c, FILE* f)
	{
		return CDECL_2(INT, 0x618B53, c, f);
	}
	_H3API_ INT F_strtol(LPCSTR str, INT base, PCHAR* end)
	{
		return CDECL_3(INT, 0x619BF8, str, &end, nullptr);
	}
	_H3API_ INT F_strtol(const H3String & str, INT base, PCHAR * end)
	{
		return F_strtol(str.String(), base, end);
	}
	_H3API_ UINT F_strtoul(LPCSTR str, INT base, PCHAR* end)
	{
		return CDECL_3(INT, 0x619E14, str, end, base);
	}
	_H3API_ UINT F_strtoul(const H3String & str, INT base, PCHAR * end)
	{
		return F_strtoul(str.String(), base, end);
	}
	_H3API_ PCHAR F_strtok(LPCSTR str, LPCSTR delimiters)
	{
		return CDECL_2(PCHAR, 0x617FBB, str, delimiters);
	}
	_H3API_ LPCSTR F_GetTownName(INT town_id)
	{
		return reinterpret_cast<LPCSTR*>(PtrAt(0x5C1857))[town_id];
	}
	_H3API_ BOOL F_CloseHandle(HANDLE handle)
	{
		return STDCALL_1(BOOL, PtrAt(0x63A0C8), handle);
	}
	_H3API_ HANDLE F_CreateFile(LPCSTR file, BOOL openExisting)
	{
		// * HDmod hijacks H3's CreateFile at import table and other similar functions
		// * this function serves as a pleasant shortcut
		return CreateFileA(file, openExisting ? GENERIC_READ : GENERIC_WRITE, 0, LPSECURITY_ATTRIBUTES(NULL),
			openExisting ? OPEN_EXISTING : CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, HANDLE(NULL));
	}
	_H3API_ DWORD F_GetFileSize(HANDLE handle)
	{
		// ::GetFileSize() isn't used in h3, might change to use it
		DWORD fileSize = 0;
		if (handle)
		{
			DWORD pos = SetFilePointer(handle, 0, NULL, FILE_CURRENT);
			fileSize  = SetFilePointer(handle, 0, NULL, FILE_END);
			SetFilePointer(handle, pos, NULL, FILE_BEGIN);
		}
		return fileSize;
	}
	_H3API_ BOOL F_ReadFile(HANDLE handle, PVOID data, DWORD bytesToRead)
	{
		DWORD szRead;

		if (!ReadFile(handle, data, bytesToRead, &szRead, NULL))
			return FALSE;
		return szRead == bytesToRead;
	}
	_H3API_ DWORD F_SetFilePointer(HANDLE handle, LONG position, DWORD source)
	{
		return SetFilePointer(handle, position, NULL, source);
	}
	_H3API_ BOOL F_WriteFile(HANDLE handle, PVOID buffer, DWORD bytesToWrite)
	{
		DWORD szWritten;
		if (!WriteFile(handle, buffer, bytesToWrite, &szWritten, NULL))
			return FALSE;
		return szWritten == bytesToWrite;
	}
	_H3API_ H3UniquePtr<WCHAR> F_utf8_to_unicode(LPCSTR utf8)
	{
		H3UniquePtr<WCHAR> ptr;
		if (!utf8)
			return ptr;
		UINT len = strlen(utf8);
		if (!len)
			return ptr;

		INT req_len = STDCALL_6(INT, PtrAt(0x63A1CC), CP_UTF8, 0, utf8, len, 0, 0);

		ptr.Set(reinterpret_cast<WCHAR*>(F_calloc(req_len + 1, sizeof(WCHAR))));
		if (ptr.Get())
			STDCALL_6(INT, PtrAt(0x63A1CC), CP_UTF8, 0, utf8, len, ptr.Get(), req_len);

		return ptr;
	}
	_H3API_ H3UniquePtr<WCHAR> F_ansi_to_unicode(LPCSTR ansi)
	{
		H3UniquePtr<WCHAR> ptr;
		if (!ansi)
			return ptr;
		UINT len = strlen(ansi);
		if (!len)
			return ptr;

		INT req_len = STDCALL_6(INT, PtrAt(0x63A1CC), CP_ACP, 0, ansi, len, 0, 0);

		ptr.Set(reinterpret_cast<WCHAR*>(F_calloc(req_len + 1, sizeof(WCHAR))));
		if (ptr.Get())
			STDCALL_6(INT, PtrAt(0x63A1CC), CP_ACP, 0, ansi, len, ptr.Get(), req_len);

		return ptr;
	}
}