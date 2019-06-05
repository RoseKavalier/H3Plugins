//////////////////////////////////////////////////////////////////////
//																	//
//					Created by RoseKavalier:						//
//					rosekavalierhc@gmail.com						//
//																	//
//		    ***You may use or distribute these files freely			//
//			   so long as this notice remains present.***			//
//																	//
//			In preparing these files, several sources were			//
//				consulted, they are listed in no particular			//
//							order below.							//
//																	//
//	Source: https://github.com/potmdehex/homm3tools					//
//	Author: potmdehex and contributors								//
//																	//
//	Source: https://github.com/redxu/HoMM3_FA						//
//	Author: redxu													//
//																	//
//	Source: https://github.com/openhomm/openhomm					//
//	Author: Ershov Stanislav, Fomin Roman, Akulich Alexander		//
//																	//
//	Source: https://github.com/GrayFace/wog							//
//	Author: GrayFace and WoG team									//
//																	//
//	Source: https://github.com/ethernidee/era						//
//	Author: Berserker												//
//																	//
//	Source: https://github.com/ethernidee/era-editor				//
//	Author: Grayface and Berserker									//
//																	//
//	Source:	http://wforum.heroes35.net/showthread.php?tid=3900		//
//	Author: Slava and GrayFace										//
//																	//
//	Source: http://wforum.heroes35.net/showthread.php?tid=4583		//
//	Author: gamecreator												//
//																	//
//	Thanks: patcher_x86 by baratorch and code therein				//
//																	//
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
	static void ShowError(LPCSTR message, LPCSTR title = "H3Error!")
	{
		MessageBoxA(NULL, message, title, MB_OK | MB_ICONERROR);
	}

	// * wide char format
	static void _ShowError(LPCWSTR message, LPCWSTR title = L"H3Error!")
	{
		MessageBoxW(NULL, message, title, MB_OK | MB_ICONERROR);
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
class H3Manipulator
{
public:
	static PUCHAR Memmem(PUCHAR haystack, size_t hlen, const PUCHAR needle, size_t nlen);
	static UINT32 FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset);
	static void WriteBytePatch(UINT32 start, UINT8 code);
	static void WriteWordPatch(UINT32 start, UINT16 code);
	static void WriteDwordPatch(UINT32 start, UINT32 code);
	static void WriteFloatPatch(UINT32 start, FLOAT code);
	static void WriteHexPatch(UINT32 start, PUINT8 code, UINT codeLength);
	// * only works for opcode length 5, most basic hook there is
	static void NakedHook5(UINT32 start, void *function);
};

// * get information about loaded dll
struct H3DLL
{
	PUINT8 code;
	UINT32 size;
	PCHAR dllName;
	PUINT8 data;
	UINT32 dataSize;

	H3DLL() { code = NULL; size = 0; dllName = NULL; }

	// for debug purposes
	void NeedleNotFound(PUINT8 needle, INT32 needleSize, BOOL inCode = TRUE);
	void NeedleUnexpectedCode(UINT32 address, PUINT8 needle, INT32 needleSize, PUINT8 expectedCode, INT32 expectedSize);
	void DLLNotFound();

	// get DLL code start and DLL size
	void GetDLLInfo(const PCHAR name);
	// find the first instance of needle
	UINT32 NeedleSearch(PUINT8 needle, INT32 needleSize, INT32 offset);
	// searches around the needle for a piece of code, needl2
	UINT32 NeedleSearchAround(PUINT8 needle, INT32 needleSize, INT32 radius, PUINT8 needle2, INT32 needleSize2);
	// to find subsequent instances of a needle, based on NeedleSearch result
	UINT32 NeedleSearchAfter(UINT32 after, PUINT8 needle, INT32 needleSize, INT32 offset);
	// performs NeedleSearch and checks checks location for expectedCode
	UINT32 NeedleSearchConfirm(PUINT8 needle, INT32 needleSize, INT32 offset, PUINT8 expectedCode, INT32 expectedSize);
	// needleSearch in data
	UINT32 NeedleSearchData(PUINT8 needle, INT32 needleSize);
};

#define Color32To16(Color) (((Color & 0x0000F8) >> 3) | ((Color & 0x00FC00) >> 5) | ((Color & 0xF80000) >> 8))
#define Color32To15(Color) (((Color & 0x0000F8) >> 3) | ((Color & 0x00F800) >> 6) | ((Color & 0xF80000) >> 9))

#pragma pack(push, 1)
// * used by H3.TextColor
struct H3NamedColors
{
	PCHAR name;
	UINT32 rgb;
	UINT16 rgb565;
};
#pragma pack(pop)

#define BytePatch(start, code) (H3Manipulator::WriteBytePatch(start, code))
#define DwordPatch(start, value) (H3Manipulator::WriteDwordPatch(start, value))
#define HexPatch(start, code) (H3Manipulator::WriteHexPatch(start, code, sizeof(code)))
#define needle_search(start_address, search_end, needle, offset) (H3Manipulator::FindByNeedle(start_address, search_end, needle, sizeof(needle), offset))
#define naked_function void __declspec(naked)
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
	call_dword = 0xFF15
};

inline PUCHAR H3Manipulator::Memmem(PUCHAR haystack, size_t hlen, const PUCHAR needle, size_t nlen)
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

inline UINT32 H3Manipulator::FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset)
{
	if (!address)
		return NULL;

	UINT32 p = (UINT32)H3Manipulator::Memmem(address, max_search_length, needle, needle_length);
	if (p)
		p += offset;
	return p;
}

inline void H3Manipulator::WriteBytePatch(UINT32 start, UINT8 code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 1, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		ByteAt(start) = code;
		VirtualProtect((LPVOID)start, 1, old_protect, &old_protect);
	}
}

inline void H3Manipulator::WriteWordPatch(UINT32 start, UINT16 code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 2, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		WordAt(start) = code;
		VirtualProtect((LPVOID)start, 2, old_protect, &old_protect);
	}
}

inline void H3Manipulator::WriteDwordPatch(UINT32 start, UINT32 code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 4, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		DwordAt(start) = code;
		VirtualProtect((LPVOID)start, 4, old_protect, &old_protect);
	}
}

inline void H3Manipulator::WriteFloatPatch(UINT32 start, FLOAT code)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 4, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		FloatAt(start) = code;
		VirtualProtect((LPVOID)start, 4, old_protect, &old_protect);
	}
}

inline void H3Manipulator::WriteHexPatch(UINT32 start, PUINT8 code, UINT codeLength)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, codeLength, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		for (UINT i = 0; i < codeLength; i++)
			ByteAt(start + i) = code[i];
		VirtualProtect((LPVOID)start, codeLength, old_protect, &old_protect);
	}
}

inline void H3Manipulator::NakedHook5(UINT32 start, void * function)
{
	DWORD old_protect = 0;
	if (VirtualProtect((LPVOID)start, 5, PAGE_EXECUTE_WRITECOPY, &old_protect))
	{
		ByteAt(start) = mnemonics::jmp;
		DwordAt(start + 1) = (UINT32)(function)-(UINT32)(start)-5;
		VirtualProtect((LPVOID)start, 5, old_protect, &old_protect);
	}
}

inline UINT32 H3DLL::NeedleSearch(PUINT8 needle, INT32 needleSize, INT32 offset)
{
	UINT32 p = H3Manipulator::FindByNeedle(code, size, needle, needleSize, offset);
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
		p = H3Manipulator::FindByNeedle((PUINT8)low, searchLength, needle2, needleSize2, 0);
#if _H3DLL_DEBUG_
		if (!p)
			NeedleNotFound(needle2, needleSize2);
#endif
	}
	return p;
}

inline UINT32 H3DLL::NeedleSearchAfter(UINT32 after, PUINT8 needle, INT32 needleSize, INT32 offset)
{
	UINT32 p = H3Manipulator::FindByNeedle((PUINT8)after, size - (after - (UINT32)code), needle, needleSize, offset);
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
		if (memcmp((void*)p, expectedCode, expectedSize)) // is the code at the found address different from what we expect?
		{
#if _H3DLL_DEBUG_
			NeedleUnexpectedCode(p, needle, needleSize, expectedCode, expectedSize);
#endif
			p = 0;
		}
	}
	return p;
}

inline UINT32 H3DLL::NeedleSearchData(PUINT8 needle, INT32 needleSize)
{
	UINT32 p = H3Manipulator::FindByNeedle(data, dataSize, needle, needleSize, 0);
#if _H3DLL_DEBUG_
	if (!p)
		NeedleNotFound(needle, needleSize, FALSE);
#endif
	return p;
}

inline void H3DLL::GetDLLInfo(const PCHAR name)
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
		PCHAR name = (PCHAR)pSectionHdr->Name;
		if (!memcmp(name, ".rdata", sizeof(".rdata"))) // no -1 to sizeof() to include \0 null terminator
		{
			data = (PUINT8)((DWORD)hm + pSectionHdr->VirtualAddress);
			dataSize = pSectionHdr->Misc.VirtualSize;
			break;
		}
	}
}

inline void H3DLL::NeedleNotFound(PUINT8 needle, INT32 needleSize, BOOL inCode)
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
			sprintf(buffer, "Could not find needle:\n\n%s\n\nIn data of module: \"%s\".\n\nData start: 0x%08X\n\nDLL data size: 0x%08X", needleBuffer, dllName, (UINT32)data, dataSize);
		H3Error::ShowError(buffer, "Needle not found!");
	}
	free(buffer);
	free(needleBuffer);
}

inline void H3DLL::NeedleUnexpectedCode(UINT32 address, PUINT8 needle, INT32 needleSize, PUINT8 expectedCode, INT32 expectedSize)
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

inline void H3DLL::DLLNotFound()
{
	PCHAR buffer = (PCHAR)calloc(1, strlen(dllName) + 512);
	if (buffer)
	{
		sprintf(buffer, "Module \"%s\" could not be found!", dllName);
		H3Error::ShowError(buffer, "DLL not found!");
	}
	free(buffer);
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