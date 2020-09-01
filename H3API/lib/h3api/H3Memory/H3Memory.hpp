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
	/**
	 * @brief raii virtual protection to enable writing
	 *
	 */
	class H3Protect
	{
		UINT32 m_address;
		UINT32 m_size;
		DWORD  m_oldProtect;
		BOOL   m_protectEdited;
	public:
		/**
		 * @brief enables writing at memory location
		 *
		 * @param address where you wish to write
		 * @param size how many bytes should be unprotected
		 */
		_H3API_ H3Protect(UINT32 address, UINT32 size);
		_H3API_ ~H3Protect();
		/**
		 * @brief checks if virtual protect was successful
		 *
		 * @return BOOL whether virtual protect operation enabled writing
		 */
		_H3API_ BOOL CanWrite();
	};

	/**
	 * @brief perform operations on loaded memory
	 *
	 */
	namespace H3Patcher
	{
		enum mnemonics
		{
			INC_EAX    = 0x40,
			INC_ECX    = 0x41,
			INC_EDX    = 0x42,
			INC_EBX    = 0x43,
			INC_ESP    = 0x44,
			INC_EBP    = 0x45,
			INC_ESI    = 0x46,
			INC_EDI    = 0x47,
			DEC_EAX    = 0x48,
			DEC_ECX    = 0x49,
			DEC_EDX    = 0x4A,
			DEC_EBX    = 0x4B,
			DEC_ESP    = 0x4C,
			DEC_EBP    = 0x4D,
			DEC_ESI    = 0x4E,
			DEC_EDI    = 0x4F,
			PUSH_EAX   = 0x50,
			PUSH_ECX   = 0x51,
			PUSH_EDX   = 0x52,
			PUSH_EBX   = 0x53,
			PUSH_ESP   = 0x54,
			PUSH_EBP   = 0x55,
			PUSH_ESI   = 0x56,
			PUSH_EDI   = 0x57,
			POP_EAX    = 0x58,
			POP_ECX    = 0x59,
			POP_EDX    = 0x5A,
			POP_EBX    = 0x5B,
			POP_ESP    = 0x5C,
			POP_EBP    = 0x5D,
			POP_ESI    = 0x5E,
			POP_EDI    = 0x5F,
			PUSHAD     = 0x60,
			POPAD      = 0x61,
			PUSH_DWORD = 0x68,
			PUSH_BYTE  = 0x6A,
			SHORT_JO   = 0x70,
			SHORT_JNO  = 0x71,
			SHORT_JB   = 0x72,
			SHORT_JNB  = 0x73,
			SHORT_JZ   = 0x74,
			SHORT_JNZ  = 0x75,
			SHORT_JNA  = 0x76,
			SHORT_JA   = 0x77,
			SHORT_JS   = 0x78,
			SHORT_JNS  = 0x79,
			SHORT_JP   = 0x7A,
			SHORT_JNP  = 0x7B,
			SHORT_JL   = 0x7C,
			SHORT_JGE  = 0x7D, // JNL
			SHORT_JNG  = 0x7E,
			SHORT_JG   = 0x7F,
			NOP        = 0x90,
			PUSHFD     = 0x9C,
			POPFD      = 0x9D,
			CALL       = 0xE8,
			JMP        = 0xE9,
			SHORT_JMP  = 0xEB,
			_RETN_     = 0xC3,
			_RETNX_    = 0xC2,

			FAR_JO     = 0x0F80,
			FAR_JNO    = 0x0F81,
			FAR_JB     = 0x0F82,
			FAR_JNB    = 0x0F83,
			FAR_JZ     = 0x0F84,
			FAR_JNZ    = 0x0F85,
			FAR_JNA    = 0x0F86,
			FAR_JA     = 0x0F87,
			FAR_JS     = 0x0F88,
			FAR_JNS    = 0x0F89,
			FAR_JP     = 0x0F8A,
			FAR_JNP    = 0x0F8B,
			FAR_JL     = 0x0F8C,
			FAR_JNL    = 0x0F8D,
			FAR_JNG    = 0x0F8E,
			FAR_JG     = 0x0F8F,
			CALL_DWORD = 0x15FF,
		};

		/**
		 * @brief finds the first byte sequence in a specified region
		 *
		 * @param haystack region in which to look for
		 * @param hlen the length of the memory region to search
		 * @param needle byte sequence to search for
		 * @param nlen how many bytes are in the needle
		 * @return PUCHAR address that matches needle, as a pointer. nullptr if not found
		 */
		_H3API_ PUCHAR Memmem(PUCHAR haystack, size_t hlen, PUCHAR needle, size_t nlen);
		/**
		 * @brief performs Memmem operation to find first byte sequence in a specified region
		 *
		 * @param address starting search point
		 * @param max_search_length maximum bytes to search through
		 * @param needle byte sequence to search for
		 * @param needle_length how many bytes are in the needle
		 * @param offset how many bytes to shift the found needle location by
		 * @return UINT32 location in the region, matching the needle and shifted by \p offset. nullptr if not found
		 */
		_H3API_ UINT32 FindByNeedle(PUINT8 address, UINT32 max_search_length, PUINT8 needle, INT32 needle_length, INT32 offset);

#ifndef _H3API_NAKED_FUNCTION_
#define _H3API_NAKED_FUNCTION_ VOID __declspec(naked)
#endif

		/**
		 * @brief only works for opcode length 5, most basic hook there is.
		 * you are also in charge of overwritten assembly
		 * @param address where to place hook
		 * @param function _H3API_NAKED_FUNCTION_ hook
		 */
		_H3API_ VOID NakedHook5(UINT32 address, VOID* function);
		/**
		 * @brief same as NakedHook5, but replaces bytes after the first 5 by NOP instructions
		 *
		 * @param address where to place hook
		 * @param function _H3API_NAKED_FUNCTION_ hook
		 * @param totalBytes how many bytes should be overwritten, minimum 5
		 */
		_H3API_ VOID NakedHook(UINT32 address, VOID* function, INT totalBytes);
		/**
		 * @brief write data at specific location
		 *
		 * @tparam T byte, word or dword, float, double...
		 * @param address where to write data
		 * @param value data to write
		 */
		template<typename T>
		struct WriteValue
		{
			WriteValue(const UINT address, const T value);
		};
		/**
		 * @brief write data at specific locations
		 *
		 * @tparam T byte, word or dword, float, double...
		 * @tparam size how many locations will be written to
		 * @param address where to write data
		 * @param value data to write
		 */
		template<typename T, size_t size>
		struct WriteValues
		{
			WriteValues(const UINT address, const T(&value)[size]);
		};
		/**
		 * @brief writes pointer of data type (its address)
		 *
		 * @tparam T any data type
		 * @param address address to write to
		 * @param data a global or constexpr array, double or other value to be written as a pointer
		 */
		template<typename T>
		VOID AddressOfPatch(const UINT address, const T& data);
		/**
		 * @brief writes pointer of data type (its address) to multiple locations
		 *
		 * @tparam Address primitive numerical type (int, unsigned int...)
		 * @tparam Type any data type
		 * @tparam size number of items in \p address array
		 * @param address addresses to write to
		 * @param data a global or constexpr array, double or other value to be written as a pointer
		 * @return H3Internal::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4>::type
		 */
		template<typename Address, typename Type, size_t size>
		typename H3Internal::enable_if<std::numeric_limits<Address>::is_integer && sizeof(Address) == 4>::type
		AddressOfPatch(const Address(&address)[size], const Type& data);
		/**
		 * @brief writes data type to an object reference without having to dereference to obtain their address
		 *
		 * @tparam T type of the object
		 * @param reference data member of the object
		 * @param data replacement value
		 */
		template<typename T>
		VOID ObjectPatch(T& reference, T data);
		/**
		 * @brief writes an array of bytes to the specified location
		 *
		 * @tparam size how many bytes are to be written
		 * @param address starting location to write patch
		 * @param value an array of bytes representing a patch
		 */
		template<size_t size>
		VOID HexPatch(const UINT address, const BYTE(&value)[size]);

		typedef WriteValue<BYTE>   BytePatch;
		typedef WriteValue<INT8>   CharPatch;
		typedef WriteValue<WORD>   WordPatch;
		typedef WriteValue<INT16>  ShortPatch;
		typedef WriteValue<DWORD>  DwordPatch;
		typedef WriteValue<INT32>  IntPatch;
		typedef WriteValue<FLOAT>  FloatPatch;
		typedef WriteValue<DOUBLE> DoublePatch;
	}

	/**
	 * @brief get information about loaded dll or process through its name
	 *
	 */
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
		/**
		 * @brief constructs the object and performs GetDllInfo()
		 *
		 * @param dll_name name of the process to inspect
		 */
		_H3API_ H3DLL(LPCSTR dll_name);

	protected:
		_H3API_ VOID needleNotFound(PUINT8 needle, INT32 needle_size, BOOL in_code = TRUE) const;
		_H3API_ VOID needleUnexpectedCode(UINT32 address, PUINT8 needle, INT32 needle_size, PUINT8 expected_code, INT32 expected_size) const;
		_H3API_ VOID processNotFound() const;
	public:
		/**
		 * @brief get process memory layout and size
		 *
		 * @param name name of the process
		 */
		_H3API_ VOID GetDLLInfo(LPCSTR name);
		/**
		 * @brief find the first instance of needle
		 *
		 * @param needle byte sequence to look for
		 * @param needle_size number of bytes in needle
		 * @param offset number of bytes by which to shift the result
		 * @return UINT32 address of the needle modified by \p offset, 0 if needle was not found
		 */
		_H3API_ UINT32 NeedleSearch(PUINT8 needle, INT32 needle_size, INT32 offset);
		/**
		 * @brief find the location of a secondary needle in the vicinity of primary needle
		 *
		 * @param needle primary byte sequence to look for
		 * @param needle_size size of primary needle
		 * @param radius search length around primary needle
		 * @param needle2 secondary byte sequence to look for
		 * @param needle_size2 size of secondary needle
		 * @return UINT32 address of the secondary needle, 0 if not found
		 */
		_H3API_ UINT32 NeedleSearchAround(PUINT8 needle, INT32 needle_size, INT32 radius, PUINT8 needle2, INT32 needle_size2);
		/**
		 * @brief used to perform subsequent searches of a needle based on previous results
		 *
		 * @param after starting search location
		 * @param needle byte sequence to look for
		 * @param needle_size number of bytes in needle
		 * @param offset number of bytes by which to shift the result
		 * @return UINT32 address of the needle modified by \p offset, 0 if needle was not found
		 */
		_H3API_ UINT32 NeedleSearchAfter(UINT32 after, const PUINT8 needle, INT32 needle_size, INT32 offset) const;
		/**
		 * @brief performs NeedleSearch and checks checks location for expectedCode
		 *
		 * @param needle byte sequence to look for
		 * @param needle_size number of bytes in needle
		 * @param offset number of bytes by which to shift the result
		 * @param expected_code byte sequence expected to be found at destination
		 * @param expected_size size of expected byte sequence
		 * @return UINT32 address of the needle modified by \p offset, 0 if needle was not found or expected sequence is not confirmed
		 */
		_H3API_ UINT32 NeedleSearchConfirm(PUINT8 needle, INT32 needle_size, INT32 offset, PUINT8 expected_code, INT32 expected_size);
		/**
		 * @brief performs NeedleSearch in RDATA section
		 *
		 * @param needle byte sequence to look for
		 * @param needle_size number of bytes in needle
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		_H3API_ UINT32 NeedleSearchRData(PUINT8 needle, INT32 needle_size) const;
		/**
		 * @brief performs NeedleSearch in DATA section
		 *
		 * @param needle byte sequence to look for
		 * @param needle_size number of bytes in needle
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		_H3API_ UINT32 NeedleSearchData(PUINT8 needle, INT32 needle_size) const;
		/**
		 * @brief find the first instance of needle
		 *
		 * @tparam sz number of bytes in needle
		 * @param needle byte sequence to look for
		 * @param offset number of bytes by which to shift the result
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		template <INT32 sz>
		UINT32 NeedleSearch(const UINT8(&needle)[sz], INT32 offset);
		/**
		 * @brief find the location of a secondary needle in the vicinity of primary needle
		 *
		 * @tparam sz number of bytes in primary needle
		 * @tparam sz2 number of bytes in secondary needle
		 * @param needle primary byte sequence to look for
		 * @param radius search length around primary needle
		 * @param needle2 secondary byte sequence to look for
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		template <INT32 sz, INT32 sz2>
		UINT32 NeedleSearchAround(const UINT8(&needle)[sz], INT32 radius, const UINT8(&needle2)[sz2]);
		/**
		 * @brief used to perform subsequent searches of a needle based on previous results
		 *
		 * @tparam sz number of bytes in needle
		 * @param after starting search location
		 * @param needle byte sequence to look for
		 * @param offset number of bytes by which to shift the result
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		template <INT32 sz>
		UINT32 NeedleSearchAfter(UINT32 after, const UINT8(&needle)[sz], INT32 offset);
		/**
		 * @brief performs NeedleSearch and checks checks location for expectedCode
		 *
		 * @tparam sz number of bytes in primary needle
		 * @tparam sz2 number of bytes in confirmation needle
		 * @param needle byte sequence to look for
		 * @param offset number of bytes by which to shift the result
		 * @param expected_code byte sequence expected to be found at destination
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		template <INT32 sz, INT32 sz2>
		UINT32 NeedleSearchConfirm(const UINT8(&needle)[sz], INT32 offset, const UINT8(&expected_code)[sz2]);
		/**
		 * @brief performs NeedleSearch in RDATA section
		 *
		 * @tparam sz number of bytes in needle
		 * @param needle byte sequence to look for
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		template <INT32 sz>
		UINT32 NeedleSearchRData(const UINT8(&needle)[sz]);
		/**
		 * @brief performs NeedleSearch in DATA section
		 *
		 * @tparam sz number of bytes in needle
		 * @param needle byte sequence to look for
		 * @return UINT32 address of the needle, 0 if needle was not found
		 */
		template <INT32 sz>
		UINT32 NeedleSearchData(const UINT8(&needle)[sz]);
	};
}

#endif /* #define _H3MEMORY_HPP_ */