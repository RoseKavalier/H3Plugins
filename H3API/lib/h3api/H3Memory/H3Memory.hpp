//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3MEMORY_HPP_
#define _H3MEMORY_HPP_

#include "../H3_Base.hpp"

namespace h3
{
	// * raii virtual protect
	class H3Protect
	{
		UINT32 m_address;
		UINT32 m_size;
		DWORD m_old_protect;
		BOOL m_protect_edited;
	public:
		_H3API_ H3Protect(UINT32 address, UINT32 size);
		_H3API_ ~H3Protect();
		_H3API_ BOOL CanWrite();
	};

	// * perform operations on loaded memory
	namespace H3Patcher
	{
		enum mnemonics
		{
			inc_eax    = 0x40,
			inc_ecx    = 0x41,
			inc_edx    = 0x42,
			inc_ebx    = 0x43,
			inc_esp    = 0x44,
			inc_ebp    = 0x45,
			inc_esi    = 0x46,
			inc_edi    = 0x47,
			dec_eax    = 0x48,
			dec_ecx    = 0x49,
			dec_edx    = 0x4A,
			dec_ebx    = 0x4B,
			dec_esp    = 0x4C,
			dec_ebp    = 0x4D,
			dec_esi    = 0x4E,
			dec_edi    = 0x4F,
			push_eax   = 0x50,
			push_ecx   = 0x51,
			push_edx   = 0x52,
			push_ebx   = 0x53,
			push_esp   = 0x54,
			push_ebp   = 0x55,
			push_esi   = 0x56,
			push_edi   = 0x57,
			pop_eax    = 0x58,
			pop_ecx    = 0x59,
			pop_edx    = 0x5A,
			pop_ebx    = 0x5B,
			pop_esp    = 0x5C,
			pop_ebp    = 0x5D,
			pop_esi    = 0x5E,
			pop_edi    = 0x5F,
			pushad     = 0x60,
			popad      = 0x61,
			push_dword = 0x68,
			push_byte  = 0x6A,
			short_jo   = 0x70,
			short_jno  = 0x71,
			short_jb   = 0x72,
			short_jnb  = 0x73,
			short_jz   = 0x74,
			short_jnz  = 0x75,
			short_jna  = 0x76,
			short_ja   = 0x77,
			short_js   = 0x78,
			short_jns  = 0x79,
			short_jp   = 0x7A,
			short_jnp  = 0x7B,
			short_jl   = 0x7C,
			short_jge  = 0x7D, // jnl
			short_jng  = 0x7E,
			short_jg   = 0x7F,
			nop        = 0x90,
			pushfd     = 0x9C,
			popfd      = 0x9D,
			call       = 0xE8,
			jmp        = 0xE9,
			short_jmp  = 0xEB,
			_retn_     = 0xC3,
			_retnX_    = 0xC2,

			far_jo     = 0x0F80,
			far_jno    = 0x0F81,
			far_jb     = 0x0F82,
			far_jnb    = 0x0F83,
			far_jz     = 0x0F84,
			far_jnz    = 0x0F85,
			far_jna    = 0x0F86,
			far_ja     = 0x0F87,
			far_js     = 0x0F88,
			far_jns    = 0x0F89,
			far_jp     = 0x0F8A,
			far_jnp    = 0x0F8B,
			far_jl     = 0x0F8C,
			far_jnl    = 0x0F8D,
			far_jng    = 0x0F8E,
			far_jg     = 0x0F8F,
			call_dword = 0x15FF
		};

		_H3API_ PUCHAR Memmem(PUCHAR haystack, size_t hlen, PUCHAR needle, size_t nlen);
		_H3API_ UINT32 FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset);

#ifndef _NAKED_FUNCTION_
#define _NAKED_FUNCTION_ VOID __declspec(naked)
#endif

		// * only works for opcode length 5, most basic hook there is
		// * function should be of type _NAKED_FUNCTION_
		// * you are also in charge of overwritten assembly
		_H3API_ VOID NakedHook5(UINT32 whereTo, VOID* function);
		// * requires at least 5 bytes
		// * function should be of type _NAKED_FUNCTION_
		// * you are also in charge of overwritten assembly
		// * replaces bytes after the first 5 by NOP instructions
		_H3API_ VOID NakedHook(UINT32 whereTo, VOID* function, INT totalBytes);

		// * writes byte, word or dword, float, double...
		template<typename T>
		struct WriteValue
		{
			WriteValue(const UINT whereTo, const T value);
		};
		// * writes array of values of type T
		template<typename T, size_t size>
		struct WriteValues
		{
			WriteValues(const UINT whereTo, const T(&value)[size]);
		};

		// * writes pointer of data type (its address)
		// * to the specified location
		// * data can be of any type
		template<typename T>
		VOID AddressOfPatch(const UINT whereTo, const T& data);

		// * writes pointer of data type (its address)
		// * to the specified locations
		// * data can be of any type
		template<typename Address, typename Type, size_t size>
		typename H3Internal::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4>::type
		AddressOfPatch(const Address(&whereTo)[size], const Type& data);

		// * writes an array of bytes to the specified location
		template<size_t size>
		VOID HexPatch(const UINT whereTo, const BYTE(&value)[size]);

		typedef WriteValue<BYTE>   BytePatch;
		typedef WriteValue<INT8>   CharPatch;
		typedef WriteValue<WORD>   WordPatch;
		typedef WriteValue<INT16>  ShortPatch;
		typedef WriteValue<DWORD>  DwordPatch;
		typedef WriteValue<INT32>  IntPatch;
		typedef WriteValue<FLOAT>  FloatPatch;
		typedef WriteValue<DOUBLE> DoublePatch;
	}

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

		_H3API_ H3DLL();
		_H3API_ H3DLL(LPCSTR dll_name);

		// for debug purposes
		_H3API_ VOID NeedleNotFound(PUINT8 needle, INT32 needleSize, BOOL inCode = TRUE) const;
		_H3API_ VOID NeedleUnexpectedCode(UINT32 address, PUINT8 needle, INT32 needleSize, PUINT8 expectedCode, INT32 expectedSize) const;
		_H3API_ VOID DLLNotFound() const;

		// get DLL code start and DLL size
		_H3API_ VOID GetDLLInfo(LPCSTR name);
		// find the first instance of needle
		_H3API_ UINT32 NeedleSearch(PUINT8 needle, INT32 needleSize, INT32 offset);
		// searches around the needle for a piece of code, needle2
		_H3API_ UINT32 NeedleSearchAround(PUINT8 needle, INT32 needleSize, INT32 radius, PUINT8 needle2, INT32 needleSize2);
		// to find subsequent instances of a needle, based on NeedleSearch result
		_H3API_ UINT32 NeedleSearchAfter(UINT32 after, const PUINT8 needle, INT32 needleSize, INT32 offset) const;
		// performs NeedleSearch and checks checks location for expectedCode
		_H3API_ UINT32 NeedleSearchConfirm(PUINT8 needle, INT32 needleSize, INT32 offset, PUINT8 expectedCode, INT32 expectedSize);
		// needleSearch in rdata
		_H3API_ UINT32 NeedleSearchRData(PUINT8 needle, INT32 needleSize) const;
		// needleSearch in data
		_H3API_ UINT32 NeedleSearchData(PUINT8 needle, INT32 needleSize) const;

		// find the first instance of needle
		template <INT32 sz> UINT32 NeedleSearch(const UINT8(&needle)[sz], INT32 offset);
		// searches around the needle for a piece of code, needle2
		template <INT32 sz, INT32 sz2> UINT32 NeedleSearchAround(const UINT8(&needle)[sz], INT32 radius, const UINT8(&needle2)[sz2]);
		// to find subsequent instances of a needle, based on NeedleSearch result
		template <INT32 sz> UINT32 NeedleSearchAfter(UINT32 after, const UINT8(&needle)[sz], INT32 offset);
		// performs NeedleSearch and checks checks location for expectedCode
		template <INT32 sz, INT32 sz2> UINT32 NeedleSearchConfirm(const UINT8(&needle)[sz], INT32 offset, const UINT8(&expectedCode)[sz2]);
		// needleSearch in rdata
		template <INT32 sz> UINT32 NeedleSearchRData(const UINT8(&needle)[sz]);
		// needleSearch in data
		template <INT32 sz> UINT32 NeedleSearchData(const UINT8(&needle)[sz]);
	};
}

#endif /* #define _H3MEMORY_HPP_ */