//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BASE_HPP_
#define _H3BASE_HPP_

#include "../H3_Core.hpp"
#include "../H3_Config.hpp"
#include "../H3_Allocator.hpp"

namespace h3
{
	// * Null string ""
	LPCSTR const h3_NullString = LPCSTR(0x63A608);
	// * 512 bytes of char buffer to be used for printing text
	PCHAR  const h3_TextBuffer = PCHAR(0x697428);
	// * path to the main directory of the game
	LPCSTR const h3_GamePath   = LPCSTR(0x698614);
	// * a text buffer used to save the game
	PCHAR  const h3_SaveName   = PCHAR(0x69FC88);

	// * checks for SoD, HotA and WoG/ERA
	class H3Version
	{
		_H3API_ENUM_ GameVersion : INT
		{
			UNKNOWN = -1,
			ROE,
			SOD,
			SOD_POLISH_GOLD,
			HOTA,
			ERA,
			WOG,
		};
		GameVersion m_version;
	public:
		_H3API_ H3Version();
		_H3API_ GameVersion version() const;
		_H3API_ BOOL roe()  const;
		_H3API_ BOOL sod()  const;
		_H3API_ BOOL hota() const;
		_H3API_ BOOL era()  const;
		_H3API_ BOOL wog()  const;
	};

	// * memcpy using H3 assets
	_H3API_ VOID F_memcpy(PVOID dest, PVOID src, const UINT len);
	// * compares two strings, not-case-sensitive
	_H3API_ INT F_strcmpi(LPCSTR string1, LPCSTR string2);
	// * sets dest to value
	_H3API_ PVOID F_memset(PVOID dest, const UINT value, const UINT len);
	// * vsprintf using h3 assets
	// * you need to handle va_list yourself to use this!
	// * otherwise use F_sprintf which will do both
	_H3API_ INT F_vsprintf(PCHAR buffer, LPCSTR format, va_list args);
	// * sprintf using h3 assets and buffer
	_H3API_ INT F_sprintf(LPCSTR format, ...);
	// * sprintf using h3 assets and custom buffer
	_H3API_ INT F_sprintfbuffer(PCHAR buffer, LPCSTR format, ...);

	namespace H3Numbers
	{
		// * add thousands commas to numbers
		_H3API_ INT AddCommas(INT num, CHAR *out);
		// * show a number in short scale format with specified number of decimals
		_H3API_ INT MakeReadable(INT num, CHAR *out, INT decimals = 1);
	}

	namespace H3Random
	{
		_H3API_ VOID SetRandomSeed(UINT seed = STDCALL_0(UINT, DwordAt(0x63A354)));
		_H3API_ INT  Random(INT high);
		_H3API_ INT  RandBetween(INT low, INT high);
	}

	namespace H3Error
	{
		// * external messagebox showing message
		_H3API_ VOID ShowError(LPCSTR message, LPCSTR title = "H3Error!");
		// * external messagebox showing message and offering OK / Cancel choice
		_H3API_ BOOL ShowErrorChoice(LPCSTR message, LPCSTR title = "H3Error!");
		// * external messagebox showing message
		// * wide char format
		_H3API_ VOID ShowErrorW(LPCWSTR message, LPCWSTR title = L"H3Error!");
		// * external messagebox showing message and offering OK / Cancel choice
		// * wide char format
		_H3API_ BOOL ShowErrorChoiceW(LPCWSTR message, LPCWSTR title = L"H3Error!");

		_H3API_DEPRECATED_("Use ShowErrorW") inline VOID _ShowError(LPCWSTR message, LPCWSTR title = L"H3Error!") {}
		_H3API_DEPRECATED_("Use ShowErrorChoiceW") inline BOOL _ShowErrorChoice(LPCWSTR message, LPCWSTR title = L"H3Error!") { return FALSE; }
	}

#pragma pack(push, 1)
	// * dword used as bitfield
	// * can be used as an array of bitfields
	// * for a safer and more developped version with iterators, use H3Bitset
	struct H3Bitfield
	{
		struct reference
		{
		protected:
			H3Bitfield* m_bitfield;
			UINT        m_position;
		public:
			_H3API_ reference(H3Bitfield* bitfield);
			_H3API_ reference(H3Bitfield* bitfield, UINT position);
			_H3API_ reference& operator++();
			_H3API_ reference operator++(int);
			_H3API_ reference& operator~();
			_H3API_ operator BOOL();
			_H3API_ BOOL operator!();
			_H3API_ VOID operator=(BOOL state);
			_H3API_ VOID Set();
			_H3API_ VOID Reset();
			_H3API_ VOID Flip();
		};

	protected:
		UINT m_bf;
	public:
		// * returns whether bit at position is set or not
		// * position can exceed the scope of bitfield, meaning greater than 32 bits
		_H3API_ BOOL GetState(UINT32 position) const;
		// * sets bit at position to on or off
		// * position can exceed the scope of bitfield, meaning greater than 32 bits
		_H3API_ VOID SetState(UINT32 position, BOOL state);
		// * Sets bitfield to specified value
		_H3API_ VOID Set(UINT32 value);
		// * Gets bitfield value as 32bits
		_H3API_ UINT Get() const;
		// * flips bit at position
		_H3API_ VOID Flip(UINT32 position);
		// * get reference at position
		_H3API_ reference operator[](UINT32 position);
		// * state of bit at position
		_H3API_ BOOL operator()(UINT position);
		// * the end mask of unusable bits for a bitfield with specified number of bits
		_H3API_ static UINT Mask(UINT number_bits);
	};

	// * a 8x6 mask for objects within h3
	struct H3ObjectMask
	{
		H3Bitfield m_bits[2];

		_H3API_ VOID operator=(const H3ObjectMask& other);
		_H3API_ H3Bitfield& operator[](UINT index);
		_H3API_ const H3Bitfield& operator[](UINT index) const;
	};

	// * represents a point on the map
	struct H3Point
	{
		INT x;
		INT y;
		INT z;
	};
#pragma pack(pop)

} /* namespace h3 */

namespace h3
{
	// * these are internal to H3API to avoid conflicts
	namespace H3Internal
	{
		_H3API_ INT   _gameWidth();
		_H3API_ INT   _gameHeight();
		_H3API_ INT8  _gameEdgeHorizontal();
		_H3API_ INT8  _gameEdgeVertical();
		_H3API_ INT   _mapSize();
		_H3API_ UINT8 _bitMode();
		_H3API_ PCHAR _textBuffer();
	} /* namespace H3Internal */
} /* namespace h3 */

#endif /* #define _H3BASE_HPP_ */