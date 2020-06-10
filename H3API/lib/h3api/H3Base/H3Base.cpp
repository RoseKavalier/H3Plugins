//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Base.hpp"
#include "H3Base.inl"

namespace h3
{
	_H3API_ H3Version::H3Version()
	{
		IMAGE_DOS_HEADER* pDOSHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(0x400000);
		IMAGE_NT_HEADERS* pNTHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>((reinterpret_cast<BYTE*>(pDOSHeader) + pDOSHeader->e_lfanew));
		DWORD entry = pNTHeaders->OptionalHeader.AddressOfEntryPoint;

		// * checks entry point of exe
		switch (entry)
		{
		case 0x19A0AE: // 1.0
			m_version = GameVersion::ROE;
			break;
		case 0x21A884:
			m_version = GameVersion::SOD;
			break;
		case 0x21AB84:
			m_version = GameVersion::SOD_POLISH_GOLD;
			break;
		case 0x239C00:
			m_version = GameVersion::HOTA;
			break;
		case 0x301000:
			m_version = GameVersion::ERA;
			break;
		case 0x3017B0:
			m_version = GameVersion::WOG;
			break;
		default:
			m_version = GameVersion::UNKNOWN;
		}
	}
	_H3API_ H3Version::GameVersion H3Version::version() const
	{
		return m_version;
	}

	_H3API_ BOOL H3Version::roe()  const
	{
		return version() == GameVersion::ROE;
	}

	_H3API_ BOOL H3Version::sod()  const
	{
		return version() == GameVersion::SOD;
	}

	_H3API_ BOOL H3Version::hota() const
	{
		return version() == GameVersion::HOTA;
	}

	_H3API_ BOOL H3Version::era()  const
	{
		return version() == GameVersion::ERA;
	}

	_H3API_ BOOL H3Version::wog()  const
	{
		return version() == GameVersion::WOG;
	}

	_H3API_ VOID F_memcpy(PVOID dest, PVOID src, const UINT len)
	{
		CDECL_3(VOID, 0x61AD70, dest, src, len);
	}

	_H3API_ INT F_strcmpi(LPCSTR string1, LPCSTR string2)
	{
		return CDECL_2(INT, 0x6197C0, string1, string2);
	}

	_H3API_ PVOID F_memset(PVOID dest, const UINT value, const UINT len)
	{
		return CDECL_3(PVOID, 0x61B7E0, dest, value, len);
	}

	_H3API_ INT F_vsprintf(PCHAR buffer, LPCSTR format, va_list args)
	{
		return CDECL_3(INT, 0x6190DE, buffer, format, args);
	}

	_H3API_ INT F_sprintf(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		const INT r = F_vsprintf(H3Internal::_textBuffer(), format, args);
		va_end(args);
		return r;
	}

	_H3API_ INT F_sprintfbuffer(PCHAR buffer, LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		const INT r = F_vsprintf(buffer, format, args);
		va_end(args);
		return r;
	}

	/*
	 *
	 * Based on code by ideasman42:
	 * https://stackoverflow.com/a/24795133
	 *
	 * from idea by Greg Hewgill:
	 * https://stackoverflow.com/a/1449849
	 *
	 * ever so slightly modified by RoseKavalier
	 *
	 */
	_H3API_ INT H3Numbers::AddCommas(INT num, CHAR* out)
	{
		char buffer[64];
		char *src = buffer;
		char *dst = out;

		int num_len = F_sprintfbuffer(buffer, "%d", num);

		if (*src == '-')
		{
			*dst++ = *src++;
			num_len--;
		}

		for (int commas = 2 - num_len % 3; *src; commas = (commas + 1) % 3)
		{
			*dst++ = *src++;
			if (commas == 1)
				*dst++ = ',';
		}
		*--dst = 0;

		return dst - out;
	}

	/*
	 *
	 * Based on AddCommas above
	 *
	 * Also on idea by Christian Stigen Larsen:
	 * https://gist.github.com/cslarsen/1870641
	 * but does not require double or <math.h>
	 *
	 * This function returns an integer in readable format
	 *
	 * e.g.
	 *
	 * formatReadable(1998795, buf, 3)
	 * reads as 199.879M
	 *
	 * formatReadable(1998795, buf, 2)
	 * reads as 199.88M
	 *
	 * formatReadable(1998795, buf, 1)
	 * reads as 199.9M
	 *
	 * formatReadable(1998795, buf, 0)
	 * reads as 200M
	 *
	 */
	_H3API_ INT H3Numbers::MakeReadable(INT num, CHAR * out, INT decimals)
	{
		constexpr INT RN_MIN_VALUE = 10000;
		INT power;

		char buffer[64];

		// * work with positives
		INT64 m;
		if (num != INT_MIN)
			m = Abs(num);
		else
			m = INT64(INT_MAX) + 1;

		// * if smaller than specified value, print regular number
		if (m < RN_MIN_VALUE)
		{
			const INT r = F_sprintfbuffer(out, "%d", num);
			return r;
		}

		// * round the number to required precision
		INT dec = std::min(decimals, 3);
		INT plus = 500;
		INT div = 1000;
		for (INT i = 0; i < dec; i++)
		{
			plus /= 10;
			div /= 10;
		}
		INT d = power = 0;
		while (m >= 1000)
		{
			d = INT(m);
			m /= 1000;
			power++;
		}
		// * rounding, same idea as f = round(f + 0.5)
		d = (d + plus) / div * div;

		// * print template
		INT len = F_sprintfbuffer(buffer, "%d", d);
		INT c = 2 - len % 3;

		CHAR *dst = out;
		CHAR *src = buffer;

		// * leading negative
		if (num < 0)
			*dst++ = '-';

		// * copy source to destination
		while (*src)
		{
			*dst++ = *src++;
			if (c == 1)
			{
				// * if decimals are required
				if (dec)
				{
					*dst++ = '.';
					// * add required precision
					for (INT i = 0; i < dec; i++)
						*dst++ = *src++;
				}
				break;
			}
			c = (c + 1) % 3;
		}
		// * add proper ending
		constexpr CHAR scale[] = { 0, 'k', 'M', 'B' };
		*dst++ = scale[power];
		*dst = 0;

		return dst - out;
	}

	_H3API_ BOOL H3Bitfield::GetState(UINT32 position) const
	{
		UINT32 index = position >> 5;
		UINT32 pos   = position & 0x1F;
		UINT32 value = 1u << pos;
		return ((&m_bf)[index]) & value;
	}

	_H3API_ VOID H3Bitfield::SetState(UINT32 position, BOOL state)
	{
		UINT32 index = position >> 5;
		UINT32 pos   = position & 0x1F;
		UINT32 value = 1u << pos;
		if (state)
			((&m_bf)[index]) |= value;
		else
			((&m_bf)[index]) &= ~value;
	}

	_H3API_ VOID h3::H3Bitfield::Set(UINT32 value)
	{
		m_bf = value;
	}

	_H3API_ UINT h3::H3Bitfield::Get() const
	{
		return m_bf;
	}

	VOID H3Bitfield::Flip(UINT32 position)
	{
		UINT32 index = position >> 5;
		UINT32 pos = position & 0x1F;
		UINT32 value = 1u << pos;
		((&m_bf)[index]) ^= value;
	}

	_H3API_ H3Bitfield::reference H3Bitfield::operator[](UINT32 position)
	{
		return reference(this, position);
	}

	_H3API_ BOOL H3Bitfield::operator()(UINT position)
	{
		return GetState(position);
	}

	_H3API_ UINT H3Bitfield::Mask(UINT number_bits)
	{
		return UINT((1ull << (number_bits & 0x1F)) - 1);
	}

	_H3API_ VOID H3Random::SetRandomSeed(UINT seed)
	{
		srand(seed);
	}

	// * From https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range?answertab=active#tab-top
	_H3API_ INT H3Random::Random(INT high)
	{
		const INT num_bins = high + 1;
		const INT num_rand = RAND_MAX + 1;
		const INT bin_size = num_rand / num_bins;
		const INT defect = num_rand % num_bins;

		INT x;
		do { x = rand(); } while (num_rand - defect <= x);

		return x / bin_size;
	}
	_H3API_ INT H3Random::RandBetween(INT low, INT high)
	{
		return H3Random::Random(high - low) + low;
	}

	_H3API_ VOID H3Error::ShowError(LPCSTR message, LPCSTR title)
	{
		MessageBoxA(nullptr, message, title, MB_OK | MB_ICONERROR);
	}
	_H3API_ BOOL H3Error::ShowErrorChoice(LPCSTR message, LPCSTR title)
	{
		return MessageBoxA(nullptr, message, title, MB_OKCANCEL | MB_ICONERROR) == IDOK;
	}
	_H3API_ VOID H3Error::ShowErrorW(LPCWSTR message, LPCWSTR title)
	{
		MessageBoxW(nullptr, message, title, MB_OK | MB_ICONERROR);
	}
	_H3API_ BOOL H3Error::ShowErrorChoiceW(LPCWSTR message, LPCWSTR title)
	{
		return MessageBoxW(nullptr, message, title, MB_OKCANCEL | MB_ICONERROR);
	}
	_H3API_ VOID H3ObjectMask::operator=(const H3ObjectMask & other)
	{
		m_bits[0].Set(other[0].Get());
		m_bits[1].Set(other[1].Get());
	}
	_H3API_ H3Bitfield & H3ObjectMask::operator[](UINT index)
	{
		return m_bits[index];
	}
	_H3API_ const H3Bitfield & H3ObjectMask::operator[](UINT index) const
	{
		return m_bits[index];
	}
	_H3API_ H3Bitfield::reference::reference(H3Bitfield* bitfield) :
		m_bitfield(bitfield), m_position()
	{
	}
	_H3API_ H3Bitfield::reference::reference(H3Bitfield* bitfield, UINT position) :
		m_bitfield(bitfield), m_position(position)
	{
	}
	_H3API_ H3Bitfield::reference& H3Bitfield::reference::operator++()
	{
		++m_position;
		return *this;
	}
	_H3API_ H3Bitfield::reference H3Bitfield::reference::operator++(int)
	{
		reference ref(m_bitfield, m_position);
		++m_position;
		return ref;
	}
	_H3API_ H3Bitfield::reference& H3Bitfield::reference::operator~()
	{
		Flip();
		return *this;
	}
	_H3API_ H3Bitfield::reference::operator BOOL()
	{
		return m_bitfield->GetState(m_position);
	}
	_H3API_ BOOL H3Bitfield::reference::operator!()
	{
		return m_bitfield->GetState(m_position) == FALSE;
	}
	_H3API_ VOID H3Bitfield::reference::operator=(BOOL state)
	{
		m_bitfield->SetState(m_position, state);
	}
	_H3API_ VOID H3Bitfield::reference::Set()
	{
		m_bitfield->SetState(m_position, TRUE);
	}
	_H3API_ VOID H3Bitfield::reference::Reset()
	{
		m_bitfield->SetState(m_position, FALSE);
	}
	_H3API_ VOID H3Bitfield::reference::Flip()
	{
		m_bitfield->Flip(m_position);
	}
}

namespace h3
{
	namespace H3Internal
	{
		_H3API_  INT _gameWidth()
		{
			return IntAt(0x403401);
		}
		_H3API_ INT _gameHeight()
		{
			return IntAt(0x4033FC);
		}
		_H3API_ INT8 _gameEdgeHorizontal()
		{
			return CharAt(0x4A8FC0);
		}
		_H3API_ INT8 _gameEdgeVertical()
		{
			return CharAt(0x4A8FC5);
		}
		_H3API_ INT _mapSize()
		{
			return IntAt(0x6783C8);
		}
		_H3API_ UINT8 _bitMode()
		{
			return ByteAt(0x5FA228 + 3);
		}
		_H3API_ PCHAR _textBuffer()
		{
			return PCHAR(0x697428);
		}
	}
}

