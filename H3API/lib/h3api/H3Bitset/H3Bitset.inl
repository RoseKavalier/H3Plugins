//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-06-01                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BITSET_INL_
#define _H3BITSET_INL_

#include "H3Bitset.hpp"

namespace h3
{


	template<UINT size>
	inline H3Bitset<size>::iterator::iterator(H3Bitset* bitset) :
		m_bitset(bitset), m_position()
	{
	}
	template<UINT size>
	inline H3Bitset<size>::iterator::iterator(H3Bitset* bitset, UINT position) :
		m_bitset(bitset), m_position(position)
	{
	}
	template<UINT size>
	inline typename H3Bitset<size>::iterator& H3Bitset<size>::iterator::operator++()
	{
		++m_position;
		return *this;
	}
	template<UINT size>
	inline typename  H3Bitset<size>::iterator H3Bitset<size>::iterator::operator++(int)
	{
		iterator it(m_bitset, m_position);
		++m_position;
		return it;
	}
	template<UINT size>
	inline typename H3Bitset<size>::iterator& H3Bitset<size>::iterator::operator*()
	{
		return *this;
	}
	template<UINT size>
	inline typename H3Bitset<size>::iterator* H3Bitset<size>::iterator::operator->()
	{
		return this;
	}
	template<UINT size>
	inline typename H3Bitset<size>::iterator& H3Bitset<size>::iterator::operator~()
	{
		Flip();
		return *this;
	}
	template<UINT size>
	inline H3Bitset<size>::iterator::operator BOOL()
	{
		return m_bitset->get(m_position);
	}
	template<UINT size>
	inline BOOL H3Bitset<size>::iterator::operator!()
	{
		return m_bitset->Test(m_position) == FALSE;
	}
	template<UINT size>
	inline BOOL H3Bitset<size>::iterator::operator==(const iterator& other)
	{
		return m_position == other.m_position;
	}
	template<UINT size>
	inline BOOL H3Bitset<size>::iterator::operator!=(const iterator& other)
	{
		return m_position != other.m_position;
	}
	template<UINT size>
	inline VOID H3Bitset<size>::iterator::operator=(BOOL state)
	{
		m_bitset->set(m_position, state);
	}
	template<UINT size>
	inline VOID H3Bitset<size>::iterator::Set()
	{
		m_bitset->set(m_position, TRUE);
	}
	template<UINT size>
	inline VOID H3Bitset<size>::iterator::Reset()
	{
		m_bitset->set(m_position, FALSE);
	}
	template<UINT size>
	inline VOID H3Bitset<size>::iterator::Flip()
	{
		m_bitset->flip(m_position);
	}

	template<UINT size>
	inline constexpr UINT H3Bitset<size>::RawSize()
	{
		return ((size - 1) / 32 + 1) * sizeof(UINT);
	}

	template<UINT size>
	inline VOID H3Bitset<size>::set(UINT position, BOOL state)
	{
		if (position >= size)
			return;
		UINT index = position >> 5;
		UINT bit   = position & 0x1F;
		UINT value = 1u << bit;
		if (state)
			m_bits[index] |= value;
		else
			m_bits[index] &= ~value;
	}
	template<UINT size>
	inline VOID H3Bitset<size>::flip(UINT position)
	{
		if (position >= size)
			return;
		UINT index = position >> 5;
		UINT bit = position & 0x1F;
		UINT value = 1u << bit;
		m_bits[index] ^= value;
	}
	template<UINT size>
	inline BOOL H3Bitset<size>::get(UINT position) const
	{
		if (position >= size)
			return -1;
		UINT index = position >> 5;
		UINT bit = position & 0x1F;
		UINT value = 1u << bit;
		return m_bits[index] & value;
	}
	template<UINT size>
	inline VOID H3Bitset<size>::clear()
	{
		for (UINT i = 0; i < m_length; ++i)
			m_bits[i] = 0;
	}
	template<UINT size>
	inline UINT64 H3Bitset<size>::startMask()
	{
		if (size <= 64)
			return (1ull << size) - 1;
		return UINT64_MAX;
	}
	template<UINT size>
	inline UINT H3Bitset<size>::endMask()
	{
		return UINT((1ull << (size & 0x1F)) - 1);
	}

	template<UINT size>
	inline H3Bitset<size>::H3Bitset() :
		m_bits()
	{
		_H3API_STATIC_ASSERT_(size > 0, "Size 0 not valid for H3Bitset");
	}
	template<UINT size>
	inline H3Bitset<size>::H3Bitset(UINT value) :
		m_bits()
	{
		_H3API_STATIC_ASSERT_(size > 0, "Size 0 not valid for H3Bitset");
		if (size < 32)
			value &= UINT(startMask());
		m_bits[0] = value;
	}
	template<UINT size>
	inline H3Bitset<size>::H3Bitset(UINT64 value) :
		m_bits()
	{
		_H3API_STATIC_ASSERT_(size > 0, "Size 0 not valid for H3Bitset");
		switch (m_length)
		{
		case 1:
			m_bits[0] = value & UINT(startMask());
			break;
		case 2:
			*PUINT64(m_bits) = value & startMask();
			break;
		default:
			*PUINT64(m_bits) = value;
		}
	}
	template<UINT size>
	inline H3Bitset<size>::H3Bitset(const H3String& value) :
		m_bits()
	{
		_H3API_STATIC_ASSERT_(size > 0, "Size 0 not valid for H3Bitset");
		UINT min_len = std::min(size, value.Length());
		for (UINT i = 0; i < min_len; ++i)
			if (value[i] != '0')
				set(i, TRUE);
	}
	template<UINT size>
	inline H3Bitset<size>::H3Bitset(const H3Bitset<size>& other)
	{
		_H3API_STATIC_ASSERT_(size > 0, "Size 0 not valid for H3Bitset");
		for (UINT i = 0; i < m_length; ++i)
			m_bits[i] = other.m_bits[i];
	}

	template<UINT size>
	inline H3String H3Bitset<size>::ToString() const
	{
		H3String str;
		str.Reserve(size);
		for (UINT i = 0; i < size; ++i)
			str.Append(get(i) ? '1' : '0');
		return str;
	}

	template<UINT size>
	inline H3String H3Bitset<size>::ToHexString() const
	{
		H3String str;
		str.Reserve(size);
		for (UINT i = 0; i < m_length; ++i)
			str.PrintfAppend("%x", m_bits[i]);
		return str;
	}

	template<UINT size>
	inline UINT H3Bitset<size>::ToUINT() const
	{
		return m_bits[0];
	}

	template<UINT size>
	inline UINT64 H3Bitset<size>::ToUINT64() const
	{
		switch (m_length)
		{
		case 1:
			return m_bits[0];
		default:
			return *PUINT64(m_bits);
		}
	}

	template<UINT size>
	inline VOID H3Bitset<size>::Set()
	{
		return VOID();
	}

	template<UINT size>
	inline VOID H3Bitset<size>::Reset()
	{
		clear();
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::All()
	{
		for (UINT i = 0; i < m_length - 1; ++i)
			if (m_bits[i] != UINT_MAX)
				return FALSE;
		return m_bits[m_length - 1] == UINT(endMask());
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::Any()
	{
		for (UINT i = 0; i < m_length - 1; ++i)
			if (m_bits[i] != 0)
				return TRUE;
		return FALSE;
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::None()
	{
		return !Any();
	}

	template<UINT size>
	inline VOID H3Bitset<size>::Flip()
	{
		for (UINT i = 0; i < m_length; ++i)
			m_bits[i] = m_bits[i] ^ UINT_MAX;
		m_bits[m_length - 1] &= UINT(endMask());
	}

	template<UINT size>
	inline UINT H3Bitset<size>::Count()
	{
		PUINT8 const bitset_lookup_table = PUINT8(0x67729C);
		UINT count = 0;

		PUINT current = m_bits + m_length - 1;
		UINT num_iterations = m_length;

		do
		{
			for (UINT i = *current; i; i >>= 4)
				count += bitset_lookup_table[i & 0xF];
			--current;
			--num_iterations;
		} while (num_iterations > 0);

		return count;
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::Test(UINT position)
	{
		return get(position);
	}

	template<UINT size>
	inline UINT H3Bitset<size>::Size()
	{
		return size;
	}

	template<UINT size>
	inline UINT H3Bitset<size>::Length()
	{
		return m_length;
	}

	template<UINT size>
	inline H3Bitset<size>& H3Bitset<size>::operator=(const H3Bitset<size>& other)
	{
		for (UINT i = 0; i < m_length; ++i)
			m_bits[i] = other.m_bits;
		return *this;
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::operator!=(const H3Bitset<size>& other)
	{
		return !operator==(other);
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::operator==(const H3Bitset<size>& other)
	{
		for (UINT i = 0; i < m_length; ++i)
			if (m_bits[i] != other.m_bits)
				return FALSE;
		return TRUE;
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::operator()(UINT position)
	{
		return get(position);
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::operator()()
	{
		return Any();
	}

	template<UINT size>
	inline BOOL H3Bitset<size>::operator!()
	{
		return None();
	}

	template<UINT size>
	inline typename H3Bitset<size>::iterator H3Bitset<size>::begin()
	{
		return iterator(this, 0);
	}

	template<UINT size>
	inline typename H3Bitset<size>::iterator H3Bitset<size>::end()
	{
		return iterator(this, size);
	}

	template<UINT size>
	inline typename H3Bitset<size>::iterator H3Bitset<size>::operator[](UINT position)
	{
		return iterator(this, position);
	}
}

#endif /* #define _H3BITSET_INL_ */