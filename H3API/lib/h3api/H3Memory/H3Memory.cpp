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

#include "H3Memory.hpp"
#include "../H3_String.hpp"

namespace h3
{
	_H3API_ H3Protect::H3Protect(UINT32 address, UINT32 size) :
		m_address(address), 
		m_size(size), 
		m_old_protect()
	{
		m_protect_edited = VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, PAGE_EXECUTE_WRITECOPY, &m_old_protect);
	}
	_H3API_ H3Protect::~H3Protect()
	{
		if (m_protect_edited)
			VirtualProtect(reinterpret_cast<LPVOID>(m_address), m_size, m_old_protect, &m_old_protect);
	}
	_H3API_ BOOL H3Protect::CanWrite()
	{
		return m_protect_edited;
	}
	_H3API_ PUCHAR H3Patcher::Memmem(PUCHAR haystack, size_t hlen, PUCHAR needle, size_t nlen)
	{
		PUCHAR p = haystack;
		size_t plen = hlen;

		if (!nlen)
			return nullptr;

		const UCHAR needle_first = *static_cast<unsigned char*>(needle);

		while (plen >= nlen && ((p = static_cast<unsigned char*>(memchr(p, needle_first, plen - nlen + 1)))))
		{
			if (!memcmp(p, needle, nlen))
				return p;
			p++;
			plen = hlen - (p - haystack);
		}

		return nullptr;
	}
	_H3API_ UINT32 H3Patcher::FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset)
	{
		if (!address)
			return NULL;

		UINT32 p = reinterpret_cast<UINT32>(H3Patcher::Memmem(address, max_search_length, needle, needle_length));
		if (p)
			p += offset;
		return p;
	}		

	_H3API_ VOID H3Patcher::NakedHook5(UINT32 start, VOID* function)
	{
		H3Protect protect(start, 5);
		if (protect.CanWrite())
		{
			ByteAt(start) = H3Patcher::jmp;
			DwordAt(start + 1) = reinterpret_cast<UINT32>(function) - start - 5;
		}
	}
	_H3API_ H3DLL::H3DLL() :
		code(), 
		size(), 
		dllName(), 
		rdata(), 
		rdataSize(), 
		data(), 
		dataSize()
	{
	}
	_H3API_ H3DLL::H3DLL(LPCSTR dll_name) :
		code(),
		size(),
		dllName(dll_name),
		rdata(),
		rdataSize(),
		data(),
		dataSize()
	{
		GetDLLInfo(dll_name);
	}
	_H3API_ VOID H3DLL::NeedleNotFound(PUINT8 needle, INT32 needleSize, BOOL inCode) const
	{
		H3String needleBuffer, message;
		for (int i = 0; i < needleSize; i++)
			needleBuffer.PrintfAppend("%02X ", needle[i]);

		if (inCode)
			message.Printf("Could not find needle:\n\n%s\n\nIn module: \"%s\".\n\nCode start: 0x%08X\n\nDLL size: 0x%08X",
				needleBuffer.String(), dllName, (UINT32)code, size);
		else
			message.Printf("Could not find needle:\n\n%s\n\nIn data of module: \"%s\".\n\nData start: 0x%08X\n\nDLL data size: 0x%08X",
				needleBuffer.String(), dllName, (UINT32)rdata, rdataSize);
		H3Error::ShowError(message, "Needle not found!");
	}
	_H3API_ VOID H3DLL::NeedleUnexpectedCode(UINT32 address, PUINT8 needle, INT32 needleSize, PUINT8 expectedCode, INT32 expectedSize) const
	{
		H3String message;
		H3String needle_buffer, expected_buffer, found_buffer;
		for (int i = 0; i < needleSize; i++)
			needle_buffer.PrintfAppend("%02X ", needle[i]);

		PCHAR adr = reinterpret_cast<PCHAR>(address);
		for (int i = 0; i < expectedSize; i++)
		{
			expected_buffer.PrintfAppend("%02X ", expectedCode[i]);
			found_buffer.PrintfAppend("%02X ", adr[i]);
		}
		message.Printf("Found needle:\n\n%s\n\nIn Module \"%s\".\n\nHowever, expected code...\n\n%s\n\n...does not match existing code:\n\n%s",
			needle_buffer.String(), dllName, expected_buffer.String(), found_buffer.String());
		H3Error::ShowError(message, "Needle not found!");
	}
	_H3API_ VOID H3DLL::DLLNotFound() const
	{
		H3String message;
		message.Printf("Module \"%s\" could not be found!", dllName);
		H3Error::ShowError(message, "DLL not found!");
	}
	_H3API_ VOID H3DLL::GetDLLInfo(LPCSTR name)
	{
		dllName = name;
		HMODULE hm = GetModuleHandleA(name);
		if (!hm)
		{
#ifdef _H3DLL_DEBUG_
			DLLNotFound();
#endif
			return;
		}
		IMAGE_DOS_HEADER* pDOSHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(hm);
		IMAGE_NT_HEADERS* pNTHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(reinterpret_cast<BYTE*>(pDOSHeader) + pDOSHeader->e_lfanew);
		code = PUINT8(reinterpret_cast<DWORD>(hm) + pNTHeaders->OptionalHeader.BaseOfCode);
		size = UINT32(pNTHeaders->OptionalHeader.SizeOfCode);

		// the following is based on https://stackoverflow.com/questions/4308996/finding-the-address-range-of-the-data-segment

		IMAGE_SECTION_HEADER* pSectionHdr = reinterpret_cast<IMAGE_SECTION_HEADER*>(pNTHeaders + 1);

		for (int i = 0; i < pNTHeaders->FileHeader.NumberOfSections; i++, pSectionHdr++)
		{
			const LPCSTR l_name = reinterpret_cast<LPCSTR>(pSectionHdr->Name);
			if (!memcmp(l_name, ".rdata", sizeof(".rdata"))) // no -1 to sizeof() to include \0 null terminator
			{
				rdata = reinterpret_cast<PUINT8>(reinterpret_cast<DWORD>(hm) + pSectionHdr->VirtualAddress);
				rdataSize = pSectionHdr->Misc.VirtualSize;
			}
			if (!memcmp(l_name, ".data", sizeof(".data"))) // no -1 to sizeof() to include \0 null terminator
			{
				data = reinterpret_cast<PUINT8>(reinterpret_cast<DWORD>(hm) + pSectionHdr->VirtualAddress);
				dataSize = pSectionHdr->Misc.VirtualSize;
			}
		}
	}
	_H3API_ UINT32 H3DLL::NeedleSearch(PUINT8 needle, INT32 needleSize, INT32 offset)
	{
		UINT32 p = H3Patcher::FindByNeedle(code, size, needle, needleSize, offset);
#ifdef _H3DLL_DEBUG_
		if (!p)
			NeedleNotFound(needle, needleSize);
#endif
		return p;
	}
	_H3API_ UINT32 H3DLL::NeedleSearchAround(PUINT8 needle, INT32 needleSize, INT32 radius, PUINT8 needle2, INT32 needleSize2)
	{
		UINT32 p = NeedleSearch(needle, needleSize, 0);
		if (p)
		{
			UINT32 low = std::max(reinterpret_cast<UINT32>(code), p - radius);
			UINT32 searchLength = std::min(static_cast<UINT32>(2 * radius), size - (p - (UINT32)code));
			p = H3Patcher::FindByNeedle(reinterpret_cast<PUINT8>(low), searchLength, needle2, needleSize2, 0);
#ifdef _H3DLL_DEBUG_
			if (!p)
				NeedleNotFound(needle2, needleSize2);
#endif
		}
		return p;
	}
	_H3API_ UINT32 H3DLL::NeedleSearchAfter(UINT32 after, PUINT8 needle, INT32 needleSize, INT32 offset) const
	{
		UINT32 p = H3Patcher::FindByNeedle(reinterpret_cast<PUINT8>(after), size - (after - reinterpret_cast<UINT32>(code)), needle, needleSize, offset);
#ifdef _H3DLL_DEBUG_
		if (!p)
			NeedleNotFound(needle, needleSize);
#endif
		return p;
	}
	_H3API_ UINT32 H3DLL::NeedleSearchConfirm(PUINT8 needle, INT32 needleSize, INT32 offset, PUINT8 expectedCode, INT32 expectedSize)
	{
		UINT32 p = NeedleSearch(needle, needleSize, offset);
		if (p)
		{
			if (memcmp(reinterpret_cast<PVOID>(p), expectedCode, expectedSize) != 0) // is the code at the found address different from what we expect?
			{
#ifdef _H3DLL_DEBUG_
				NeedleUnexpectedCode(p, needle, needleSize, expectedCode, expectedSize);
#endif
				p = 0;
			}
		}
		return p;
	}
	_H3API_ UINT32 H3DLL::NeedleSearchRData(PUINT8 needle, INT32 needleSize) const
	{
		UINT32 p = H3Patcher::FindByNeedle(rdata, rdataSize, needle, needleSize, 0);
#ifdef _H3DLL_DEBUG_
		if (!p)
			NeedleNotFound(needle, needleSize, FALSE);
#endif
		return p;
	}
	_H3API_ UINT32 H3DLL::NeedleSearchData(PUINT8 needle, INT32 needleSize) const
	{
		UINT32 p = H3Patcher::FindByNeedle(data, dataSize, needle, needleSize, 0);
#ifdef _H3DLL_DEBUG_
		if (!p)
			NeedleNotFound(needle, needleSize, FALSE);
#endif
		return p;
	}

}

