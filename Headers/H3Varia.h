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

#ifndef _H3VARIA_H_
#define _H3VARIA_H_

#pragma once

#include "H3Base.h"

// * This macro can be enabled to show more information
// * using H3DLL functions, should they fail.
#define _H3DLL_DEBUG_ 0

// * display errors
class H3Error
{
public:
	// * external messagebox showing message
	static VOID ShowError(LPCSTR message, LPCSTR title = "H3Error!")
	{
		MessageBoxA(NULL, message, title, MB_OK | MB_ICONERROR);
	}
	// * external messagebox showing message and offering OK / Cancel choice
	static BOOL ShowErrorChoice(LPCSTR message, LPCSTR title = "H3Error!")
	{
		return MessageBoxA(NULL, message, title, MB_OKCANCEL | MB_ICONERROR);
	}
	// * external messagebox showing message
	// * wide char format
	static VOID _ShowError(LPCWSTR message, LPCWSTR title = L"H3Error!")
	{
		MessageBoxW(NULL, message, title, MB_OK | MB_ICONERROR);
	}
	// * external messagebox showing message and offering OK / Cancel choice
	// * wide char format
	static BOOL _ShowErrorChoice(LPCWSTR message, LPCWSTR title = L"H3Error!")
	{
		return MessageBoxW(NULL, message, title, MB_OKCANCEL | MB_ICONERROR);
	}
};

// * Get random values
class H3Random
{
public:
	static int Random(int high);
	static int RandBetween(int low, int high);
};

// * perform operations on loaded memory
class H3Patcher
{
public:
	static PUCHAR Memmem(PUCHAR haystack, size_t hlen, const PUCHAR needle, size_t nlen);
	static UINT32 FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset);
	static VOID WriteBytePatch(UINT32 start, UINT8 code);
	static VOID WriteWordPatch(UINT32 start, UINT16 code);
	static VOID WriteDwordPatch(UINT32 start, UINT32 code);
	static VOID WriteFloatPatch(UINT32 start, FLOAT code);
	static VOID WriteHexPatch(const UINT32 start, const PUINT8 code, const UINT codeLength);
	// * only works for opcode length 5, most basic hook there is
	static VOID NakedHook5(UINT32 start, VOID *function);

	// * writes byte, word or dword
	template<typename T> static VOID WriteValue(const UINT32 address, T value);
	// writes array of values of type T
	template<typename T, size_t size> static VOID WriteValue(const UINT32 address, T (&value)[size]);
	// writes array of UINT8
	template<size_t size> static VOID WriteHexPatch(const UINT32 address, const UINT8(&code)[size]);
};

// * get information about loaded dll
struct H3DLL
{
	PUINT8 code;
	UINT32 size;
	LPCSTR dllName;
	PUINT8 rdata;
	UINT32 rdataSize;
	PUINT8 data;
	UINT32 dataSize;

	H3DLL() { code = NULL; size = 0; dllName = NULL; }

	// for debug purposes
	VOID NeedleNotFound(PUINT8 needle, INT32 needleSize, BOOL inCode = TRUE);
	VOID NeedleUnexpectedCode(UINT32 address, PUINT8 needle, INT32 needleSize, PUINT8 expectedCode, INT32 expectedSize);
	VOID DLLNotFound();

	// get DLL code start and DLL size
	VOID GetDLLInfo(LPCSTR name);
	// find the first instance of needle
	UINT32 NeedleSearch(PUINT8 needle, INT32 needleSize, INT32 offset);
	// searches around the needle for a piece of code, needle2
	UINT32 NeedleSearchAround(PUINT8 needle, INT32 needleSize, INT32 radius, PUINT8 needle2, INT32 needleSize2);
	// to find subsequent instances of a needle, based on NeedleSearch result
	UINT32 NeedleSearchAfter(UINT32 after, PUINT8 needle, INT32 needleSize, INT32 offset);
	// performs NeedleSearch and checks checks location for expectedCode
	UINT32 NeedleSearchConfirm(PUINT8 needle, INT32 needleSize, INT32 offset, PUINT8 expectedCode, INT32 expectedSize);
	// needleSearch in rdata
	UINT32 NeedleSearchRData(PUINT8 needle, INT32 needleSize);
	// needleSearch in data
	UINT32 NeedleSearchData(PUINT8 needle, INT32 needleSize);

	// find the first instance of needle
	template <INT32 sz> UINT32 NeedleSearch(UINT8(&needle)[sz], INT32 offset);
	// searches around the needle for a piece of code, needle2
	template <INT32 sz, INT32 sz2> UINT32 NeedleSearchAround(UINT8(&needle)[sz], INT32 radius, UINT8(&needle2)[sz2]);
	// to find subsequent instances of a needle, based on NeedleSearch result
	template <INT32 sz> UINT32 NeedleSearchAfter(UINT32 after, UINT8(&needle)[sz], INT32 offset);
	// performs NeedleSearch and checks checks location for expectedCode
	template <INT32 sz, INT32 sz2> UINT32 NeedleSearchConfirm(UINT8(&needle)[sz], INT32 offset, UINT8(&expectedCode)[sz2]);
	// needleSearch in rdata
	template <INT32 sz> UINT32 NeedleSearchRData(UINT8(&needle)[sz]);
	// needleSearch in data
	template <INT32 sz> UINT32 NeedleSearchData(UINT8(&needle)[sz]);
};

#define Color32To16(Color) (((Color & 0x0000F8) >> 3) | ((Color & 0x00FC00) >> 5) | ((Color & 0xF80000) >> 8))
#define Color32To15(Color) (((Color & 0x0000F8) >> 3) | ((Color & 0x00F800) >> 6) | ((Color & 0xF80000) >> 9))

#pragma pack(push, 1)
// * used by H3.TextColor
struct H3NamedColors
{
	LPCSTR name;
	UINT32 rgb;
	UINT16 rgb565;
};

// * HDmod's format for ini files lines
struct HDIniEntry // size 0xD ~ 13
{
	union
	{
		LPCSTR text;
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
	LPCSTR uselessText; // like " = ", end of line, ...

	LPCSTR GetText()
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

	HDIniEntry ** FindEntry(LPCSTR key)
	{
		HDIniEntry **e = entries;
		int i = lineEntries;

		while (i > 0)
		{
			HDIniEntry *c = *e;
			if (c->entryType == c->iniKey)
			{
				if (F_strcmpi(key, c->data.text) == 0)
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

#define BytePatch(start, code) (H3Patcher::WriteBytePatch(start, code))
#define DwordPatch(start, value) (H3Patcher::WriteDwordPatch(start, value))
#define HexPatch(start, code) (H3Patcher::WriteHexPatch(start, code, sizeof(code)))
#define needle_search(start_address, search_end, needle, offset) (H3Patcher::FindByNeedle(start_address, search_end, needle, sizeof(needle), offset))
#define naked_function VOID __declspec(naked)
#define NAKED __declspec(naked)

enum mnemonics
{
	inc_eax = 0x40,
	inc_ecx = 0x41,
	inc_edx = 0x42,
	inc_ebx = 0x43,
	inc_esp = 0x44,
	inc_ebp = 0x45,
	inc_esi = 0x46,
	inc_edi = 0x47,
	dec_eax = 0x48,
	dec_ecx = 0x49,
	dec_edx = 0x4A,
	dec_ebx = 0x4B,
	dec_esp = 0x4C,
	dec_ebp = 0x4D,
	dec_esi = 0x4E,
	dec_edi = 0x4F,
	push_eax = 0x50,
	push_ecx = 0x51,
	push_edx = 0x52,
	push_ebx = 0x53,
	push_esp = 0x54,
	push_ebp = 0x55,
	push_esi = 0x56,
	push_edi = 0x57,
	pop_eax = 0x58,
	pop_ecx = 0x59,
	pop_edx = 0x5A,
	pop_ebx = 0x5B,
	pop_esp = 0x5C,
	pop_ebp = 0x5D,
	pop_esi = 0x5E,
	pop_edi = 0x5F,
	pushad = 0x60,
	popad = 0x61,
	push_dword = 0x68,
	push_byte = 0x6A,
	short_jo = 0x70,
	short_jno = 0x71,
	short_jb = 0x72,
	short_jnb = 0x73,
	short_jz = 0x74,
	short_jnz = 0x75,
	short_jna = 0x76,
	short_ja = 0x77,
	short_js = 0x78,
	short_jns = 0x79,
	short_jp = 0x7A,
	short_jnp = 0x7B,
	short_jl = 0x7C,
	short_jge = 0x7D, // jnl
	short_jng = 0x7E,
	short_jg = 0x7F,
	nop = 0x90,
	pushfd = 0x9C,
	popfd = 0x9D,
	call = 0xE8,
	jmp = 0xE9,
	short_jmp = 0xEB,
	_retn_ = 0xC3,
	_retnX_ = 0xC2,

	far_jo = 0x0F80,
	far_jno = 0x0F81,
	far_jb = 0x0F82,
	far_jnb = 0x0F83,
	far_jz = 0x0F84,
	far_jnz = 0x0F85,
	far_jna = 0x0F86,
	far_ja = 0x0F87,
	far_js = 0x0F88,
	far_jns = 0x0F89,
	far_jp = 0x0F8A,
	far_jnp = 0x0F8B,
	far_jl = 0x0F8C,
	far_jnl = 0x0F8D,
	far_jng = 0x0F8E,
	far_jg = 0x0F8F,
	call_dword = 0x15FF
};

inline PUCHAR H3Patcher::Memmem(PUCHAR haystack, size_t hlen, const PUCHAR needle, size_t nlen)
{
	UCHAR needle_first;
	PUCHAR p = haystack;
	size_t plen = hlen;

	if (!nlen)
		return NULL;

	needle_first = *(unsigned char *)needle;

	while (plen >= nlen && (p = (unsigned char *)memchr(p, needle_first, plen - nlen + 1)))
	{
		if (!memcmp(p, needle, nlen))
			return p;
		p++;
		plen = hlen - (p - haystack);
	}

	return NULL;
}

inline UINT32 H3Patcher::FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset)
{
	if (!address)
		return NULL;

	UINT32 p = (UINT32)H3Patcher::Memmem(address, max_search_length, needle, needle_length);
	if (p)
		p += offset;
	return p;
}

inline VOID H3Patcher::WriteBytePatch(UINT32 start, UINT8 code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 1, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		ByteAt(start) = code;
		VirtualProtect((LPVOID)start, 1, old_protect, &old_protect);
	}
}

inline VOID H3Patcher::WriteWordPatch(UINT32 start, UINT16 code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 2, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		WordAt(start) = code;
		VirtualProtect((LPVOID)start, 2, old_protect, &old_protect);
	}
}

inline VOID H3Patcher::WriteDwordPatch(UINT32 start, UINT32 code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 4, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		DwordAt(start) = code;
		VirtualProtect((LPVOID)start, 4, old_protect, &old_protect);
	}
}

inline VOID H3Patcher::WriteFloatPatch(UINT32 start, FLOAT code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 4, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		FloatAt(start) = code;
		VirtualProtect((LPVOID)start, 4, old_protect, &old_protect);
	}
}

inline VOID H3Patcher::WriteHexPatch(const UINT32 start, const PUINT8 code, const UINT codeLength)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, codeLength, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		for (UINT i = 0; i < codeLength; i++)
			ByteAt(start + i) = code[i];
		VirtualProtect((LPVOID)start, codeLength, old_protect, &old_protect);
	}
}

// * This removes the following warning when using enum
// * warning C4482: nonstandard extension used: enum '...' used in qualified name
#pragma warning(push)
#pragma warning(disable : 4482)
inline VOID H3Patcher::NakedHook5(UINT32 start, VOID * function)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 5, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		ByteAt(start) = mnemonics::jmp;
		DwordAt(start + 1) = (UINT32)(function)-(UINT32)(start)-5;
		VirtualProtect((LPVOID)start, 5, old_protect, &old_protect);
	}
}
#pragma warning(pop)

template<typename T>
inline VOID H3Patcher::WriteValue(const UINT32 address, T value)
{
	if (VirtualProtect((LPVOID)start, sizeof(T), PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		*(T*)address = value;
		VirtualProtect((LPVOID)start, sizeof(T), old_protect, &old_protect);
	}
}

template<typename T, size_t size>
inline VOID H3Patcher::WriteValue(const UINT32 address, T(&value)[size])
{
	if (VirtualProtect((LPVOID)start, size, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		memcpy((PVOID)address, (PVOID)value, size);
		VirtualProtect((LPVOID)start, size, old_protect, &old_protect);
	}
}

template<size_t size>
inline VOID H3Patcher::WriteHexPatch(const UINT32 address, const UINT8(&code)[size])
{
	return WriteHexPatch((UINT32)address, (PUINT8)&code, (UINT)size);
}

inline UINT32 H3DLL::NeedleSearch(PUINT8 needle, INT32 needleSize, INT32 offset)
{
	UINT32 p = H3Patcher::FindByNeedle(code, size, needle, needleSize, offset);
#if _H3DLL_DEBUG_
	if (!p)
		NeedleNotFound(needle, needleSize);
#endif
	return p;
}

inline UINT32 H3DLL::NeedleSearchAround(PUINT8 needle, INT32 needleSize, INT32 radius, PUINT8 needle2, INT32 needleSize2)
{
	UINT32 p = NeedleSearch(needle, needleSize, 0);
	if (p)
	{
		UINT32 low = max((UINT32)code, p - radius);
		UINT32 searchLength = min((UINT32)(2 * radius), size - (p - (UINT32)code));
		p = H3Patcher::FindByNeedle((PUINT8)low, searchLength, needle2, needleSize2, 0);
#if _H3DLL_DEBUG_
		if (!p)
			NeedleNotFound(needle2, needleSize2);
#endif
	}
	return p;
}

inline UINT32 H3DLL::NeedleSearchAfter(UINT32 after, PUINT8 needle, INT32 needleSize, INT32 offset)
{
	UINT32 p = H3Patcher::FindByNeedle((PUINT8)after, size - (after - (UINT32)code), needle, needleSize, offset);
#if _H3DLL_DEBUG_
	if (!p)
		NeedleNotFound(needle, needleSize);
#endif
	return p;
}

inline UINT32 H3DLL::NeedleSearchConfirm(PUINT8 needle, INT32 needleSize, INT32 offset, PUINT8 expectedCode, INT32 expectedSize)
{
	UINT32 p = NeedleSearch(needle, needleSize, offset);
	if (p)
	{
		if (memcmp((PVOID)p, expectedCode, expectedSize)) // is the code at the found address different from what we expect?
		{
#if _H3DLL_DEBUG_
			NeedleUnexpectedCode(p, needle, needleSize, expectedCode, expectedSize);
#endif
			p = 0;
		}
	}
	return p;
}

inline UINT32 H3DLL::NeedleSearchRData(PUINT8 needle, INT32 needleSize)
{
	UINT32 p = H3Patcher::FindByNeedle(rdata, rdataSize, needle, needleSize, 0);
#if _H3DLL_DEBUG_
	if (!p)
		NeedleNotFound(needle, needleSize, FALSE);
#endif
	return p;
}

inline UINT32 H3DLL::NeedleSearchData(PUINT8 needle, INT32 needleSize)
{
	UINT32 p = H3Patcher::FindByNeedle(data, dataSize, needle, needleSize, 0);
#if _H3DLL_DEBUG_
	if (!p)
		NeedleNotFound(needle, needleSize, FALSE);
#endif
	return p;
}

inline VOID H3DLL::GetDLLInfo(LPCSTR name)
{
	HMODULE hm = GetModuleHandleA(name);
	if (!hm)
	{
#if _H3DLL_DEBUG_
		DLLNotFound();
#endif
		return;
	}
	IMAGE_DOS_HEADER* pDOSHeader = (IMAGE_DOS_HEADER*)hm;
	IMAGE_NT_HEADERS* pNTHeaders = (IMAGE_NT_HEADERS*)((BYTE*)pDOSHeader + pDOSHeader->e_lfanew);
	code = PUINT8((DWORD)hm + pNTHeaders->OptionalHeader.BaseOfCode);
	size = UINT32(pNTHeaders->OptionalHeader.SizeOfCode);
	dllName = name;

	// the following is based on https://stackoverflow.com/questions/4308996/finding-the-address-range-of-the-data-segment

	IMAGE_SECTION_HEADER *pSectionHdr = (IMAGE_SECTION_HEADER *)(pNTHeaders + 1);

	for (int i = 0; i < pNTHeaders->FileHeader.NumberOfSections; i++, pSectionHdr++)
	{
		LPCSTR name = (LPCSTR)pSectionHdr->Name;
		if (!memcmp(name, ".rdata", sizeof(".rdata"))) // no -1 to sizeof() to include \0 null terminator
		{
			rdata = (PUINT8)((DWORD)hm + pSectionHdr->VirtualAddress);
			rdataSize = pSectionHdr->Misc.VirtualSize;
		}
		if (!memcmp(name, ".data", sizeof(".data"))) // no -1 to sizeof() to include \0 null terminator
		{
			data = (PUINT8)((DWORD)hm + pSectionHdr->VirtualAddress);
			dataSize = pSectionHdr->Misc.VirtualSize;
		}
	}
}

inline VOID H3DLL::NeedleNotFound(PUINT8 needle, INT32 needleSize, BOOL inCode)
{
	PCHAR buffer = (PCHAR)calloc(1, needleSize * 3 + strlen(dllName) + 512); // * 3 to show space in between hex codes
	PCHAR needleBuffer = (PCHAR)calloc(1, needleSize * 3);
	PCHAR nB = needleBuffer;
	if (nB && buffer)
	{
		for (int i = 0; i < needleSize; i++)
		{
			sprintf(nB, "%02X ", needle[i]); // note the whitespace at the end
			nB += 3;
		}
		if (inCode)
			sprintf(buffer, "Could not find needle:\n\n%s\n\nIn module: \"%s\".\n\nCode start: 0x%08X\n\nDLL size: 0x%08X", needleBuffer, dllName, (UINT32)code, size);
		else
			sprintf(buffer, "Could not find needle:\n\n%s\n\nIn data of module: \"%s\".\n\nData start: 0x%08X\n\nDLL data size: 0x%08X", needleBuffer, dllName, (UINT32)rdata, rdataSize);
		H3Error::ShowError(buffer, "Needle not found!");
	}
	free(buffer);
	free(needleBuffer);
}

inline VOID H3DLL::NeedleUnexpectedCode(UINT32 address, PUINT8 needle, INT32 needleSize, PUINT8 expectedCode, INT32 expectedSize)
{
	PCHAR buffer = (PCHAR)calloc(1, needleSize * 3 + expectedSize * 3 * 2 + strlen(dllName) + 512); // * 3 to show space in between hex codes
	PCHAR needleBuffer = (PCHAR)calloc(1, needleSize * 3);
	PCHAR expectedBuffer = (PCHAR)calloc(1, expectedSize * 3);
	PCHAR foundBuffer = (PCHAR)calloc(1, expectedSize * 3);
	if (buffer && needleBuffer && expectedBuffer && foundBuffer)
	{
		PCHAR nB = needleBuffer;
		PCHAR eB = expectedBuffer;
		PCHAR fB = foundBuffer;

		for (int i = 0; i < needleSize; i++)
		{
			sprintf(nB, "%02X ", needle[i]); // note the whitespace at the end
			nB += 3;
		}
		PCHAR adr = (PCHAR)address;
		for (int i = 0; i < expectedSize; i++)
		{
			sprintf(eB, "%02X ", expectedCode[i]); // note the whitespace at the end
			eB += 3;
			sprintf(fB, "%02X ", adr[i]); // note the whitespace at the end
			fB += 3;
		}

		sprintf(buffer, "Found needle:\n\n%s\n\nIn Module \"%s\".\n\nHowever, expected code...\n\n%s\n\n...does not match existing code:\n\n%s", needleBuffer, dllName, expectedBuffer, foundBuffer);
		H3Error::ShowError(buffer, "Needle not found!");
	}
	free(buffer);
	free(needleBuffer);
	free(expectedBuffer);
	free(foundBuffer);
}

inline VOID H3DLL::DLLNotFound()
{
	PCHAR buffer = (PCHAR)calloc(1, strlen(dllName) + 512);
	if (buffer)
	{
		sprintf(buffer, "Module \"%s\" could not be found!", dllName);
		H3Error::ShowError(buffer, "DLL not found!");
	}
	free(buffer);
}

template<INT32 sz>
inline UINT32 H3DLL::NeedleSearch(UINT8(&needle)[sz], INT32 offset)
{
	return NeedleSearch((PUINT8)&needle, sz, offset);
}

template<INT32 sz, INT32 sz2>
inline UINT32 H3DLL::NeedleSearchAround(UINT8(&needle)[sz], INT32 radius, UINT8(&needle2)[sz2])
{
	return NeedleSearchAround((PUINT8)&needle, sz, radius, (PUINT8)&needle2, sz2);
}

template<INT32 sz>
inline UINT32 H3DLL::NeedleSearchAfter(UINT32 after, UINT8(&needle)[sz], INT32 offset)
{
	return NeedleSearchAfter(after, (PUINT8)&needle, sz, offset);
}

template<INT32 sz, INT32 sz2>
inline UINT32 H3DLL::NeedleSearchConfirm(UINT8(&needle)[sz], INT32 offset, UINT8(&expectedCode)[sz2])
{
	return NeedleSearchConfirm((PUINT8)&needle, sz, offset, (PUINT8)&expectedCode, sz2);
}

template<INT32 sz>
inline UINT32 H3DLL::NeedleSearchRData(UINT8(&needle)[sz])
{
	return NeedleSearchRData((PUINT8)&needle, sz);
}

template<INT32 sz>
inline UINT32 H3DLL::NeedleSearchData(UINT8(&needle)[sz])
{
	return NeedleSearchData((PUINT8)&needle, sz);
}

// * From https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range?answertab=active#tab-top
inline int H3Random::Random(int high)
{
	DWORD
		num_bins = (DWORD)high + 1,
		num_rand = (DWORD)RAND_MAX + 1,
		bin_size = num_rand / num_bins,
		defect = num_rand % num_bins;

	int x;
	do
	{
		x = rand();
	}
	while (num_rand - defect <= (DWORD)x);

	return x / bin_size;
}

inline int H3Random::RandBetween(int low, int high)
{
	return H3Random::Random(high - low) + low;
}

#endif /* #define _H3VARIA_H_ */


