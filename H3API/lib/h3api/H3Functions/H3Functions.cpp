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

#include "H3Functions.hpp"
#include "../H3_Structures.hpp"

namespace h3
{
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
		return STDCALL_1(INT32, 0x4A7330, DwordAt(&k));
	}
	_H3API_ INT32 F_GetCreatureUpgrade(INT id)
	{
		return THISCALL_1(INT32, 0x47AAD0, id);
	}
	_H3API_ BOOL8 F_CreatureHasUpgrade(INT id)
	{
		return THISCALL_1(BOOL8, 0x47AA50, id);
	}
	_H3API_ INT F_GetCurrentDirectory(PCHAR buf, INT bufLen)
	{
		return STDCALL_2(INT, IntAt(0x63A1A4), bufLen, buf);
	}
	_H3API_ BOOL F_GetCurrentDirectory(H3String& path, BOOL add_backslash)
	{
		if (int len = STDCALL_2(INT, IntAt(0x63A1A4), MAX_PATH, h3_TextBuffer))
		{
#ifdef _H3API_ERA_
			// * ERA hooks GetCurrentDirectory and adds +1 length
			--len;
#endif
			path.Assign(h3_TextBuffer, len);
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
	_H3API_ VOID F_MessageBox(LPCSTR text)
	{
		FASTCALL_12(VOID, 0x4F6C00, text, 1, -1, -1, -1, 0, -1, 0, -1, 0, -1, 0);
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
	_H3API_ INT32 F_atoi(LPCSTR text)
	{
		return CDECL_1(INT32, 0x6184D9, text);
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
	_H3API_ LPCWSTR F_MultiByteToWideChar(LPCSTR text, int textLength, WCHAR* buffer)
	{
		return STDCALL_6(LPCWSTR, PtrAt(0x63A1CC), CP_ACP, 0, text, textLength, buffer, textLength);
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
	_H3API_ int F_fclose(FILE* f)
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
	_H3API_ size_t F_fread(PVOID buffer, size_t size, size_t count, FILE* f)
	{
		return CDECL_4(size_t, 0x6196A4, buffer, size, count, f);
	}
	_H3API_ size_t F_fwrite(const VOID* buffer, size_t size, size_t count, FILE* f)
	{
		return CDECL_4(size_t, 0x618A1A, buffer, size, count, f);
	}
	_H3API_ int F_fsetpos(FILE* f, const fpos_t& pos)
	{
		return CDECL_2(int, 0x618D31, f, &pos);
	}
	_H3API_ int F_fgetpos(FILE* f, fpos_t& pos)
	{
		return CDECL_2(int, 0x618C56, f, &pos);
	}
	_H3API_ int F_fputc(const CHAR c, FILE* f)
	{
		return CDECL_2(int, 0x618B53, c, f);
	}
	_H3API_ INT F_strtol(LPCSTR str, INT base, PCHAR* end)
	{
		return CDECL_3(INT, 0x619BF8, str, &end, nullptr);
	}
	_H3API_ UINT F_strtoul(LPCSTR str, INT base, PCHAR* end)
	{
		return CDECL_3(INT, 0x619E14, str, end, base);
	}
	_H3API_ PCHAR F_strtok(LPCSTR str, LPCSTR delimiters)
	{
		return CDECL_2(PCHAR, 0x617FBB, str, delimiters);
	}
	_H3API_ LPCSTR F_GetTownName(int town_id)
	{
		return reinterpret_cast<LPCSTR*>(PtrAt(0x5C1857))[town_id];
	}
}