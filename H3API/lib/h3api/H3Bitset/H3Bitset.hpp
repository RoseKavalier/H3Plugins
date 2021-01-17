//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-06-01                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BITSET_HPP_
#define _H3BITSET_HPP_

#include "../H3_String.hpp"

namespace h3
{
#pragma pack(push, 4)
	/**
	 * @brief alternative for std::bitset matching C++98 alignment
	 *
	 * @tparam size the number of bits to be used
	 */
	template<UINT size>
	struct H3Bitset
	{
		/**
		 * @brief total bytes used by the bitset
		 *
		 * @return constexpr UINT occupied memory, including alignment
		 */
		static constexpr UINT RawSize();
	protected:
		static constexpr UINT m_length = (size - 1) / 32 + 1;
		UINT m_bits[m_length];

		VOID   set(UINT position, BOOL state);
		VOID   flip(UINT position);
		BOOL   get(UINT position) const;
		VOID   clear();
		UINT64 startMask();
		UINT   endMask();

	public:
		/**
		 * @brief incrementable iterator to inspect bitset's span
		 * modeled after Bitfield::reference but with known end
		 */
		struct iterator
		{
		protected:
			H3Bitset* m_bitset;
			UINT      m_position;
		public:
			/**
			 * @brief Construct a new iterator from start of bitset
			 *
			 * @param bitset bitset to use for iteration
			 */
			iterator(H3Bitset* bitset);
			/**
			 * @brief Construct a new iterator from specified position
			 *
			 * @param bitset bitset to use for iteration
			 * @param position 0..size-1
			 */
			iterator(H3Bitset* bitset, UINT position);
			/**
			 * @brief pre-increment
			 *
			 * @return itself
			 */
			iterator& operator++();
			/**
			 * @brief post-increment
			 *
			 * @return copy of itself before increment
			 */
			iterator  operator++(int);
			/**
			 * @brief required for range-based loop
			 *
			 * @return itself
			 */
			iterator& operator*();
			/**
			 * @brief
			 *
			 * @return iterator*
			 */
			iterator* operator->();
			/**
			 * @brief flips current bit
			 *
			 * @return itself
			 */
			iterator& operator~();
			/**
			 * @brief allows if (iterator) condition
			 *
			 * @return BOOL whether current bit is set
			 */
			operator BOOL();
			/**
			 * @brief allows if (!iterator) condition
			 *
			 * @return BOOL whether current bit is not set
			 */
			BOOL operator!();
			/**
			 * @brief iterator equality check
			 *
			 * @param other another iterator
			 * @return BOOL whether both iterators point to the same bit
			 */
			BOOL operator==(const iterator& other);
			/**
			 * @brief iterator inequality check
			 *
			 * @param other another iterator
			 * @return BOOL whether both iterators point to a different bit
			 */
			BOOL operator!=(const iterator& other);
			/**
			 * @brief Set the state of the current bit
			 *
			 * @param state true or false
			 */
			VOID operator=(BOOL state);
			/**
			 * @brief set the current bit as ON/true
			 */
			VOID Set();
			/**
			 * @brief set the current bit as OFF/false
			 */
			VOID Reset();
			/**
			 * @brief change the state of the current bit to on from off and vice-versa
			 */
			VOID Flip();
		};
		/**
		 * @brief Construct with all bits as off
		 */
		H3Bitset();
		/**
		 * @brief Construct with specified first 32 bits
		 *
		 * @param value the state of the first 32 bits
		 */
		H3Bitset(UINT value);
		/**
		 * @brief Construct with specified first 64 bits
		 *
		 * @param value the state of the first 64 bits
		 */
		H3Bitset(UINT64 value);
		/**
		 * @brief Construct from a string
		 * if the string contains other characters than 0 or 1, they are considered as 1 / true
		 * @param value a string of 0 (false) and 1s (false)
		 */
		H3Bitset(const H3String& value);
		H3Bitset(const H3Bitset<size>& other);
		/**
		 * @brief transform the current state to a readable string
		 *
		 * @return H3String string of 0s and 1s (off / on)
		 */
		H3String ToString() const;
		/**
		 * @brief transform the current hexadecimal state to a readable string
		 *
		 * @return H3String string of 0..9A..F as it appears in memory
		 */
		H3String ToHexString() const;
		/**
		 * @brief extract first 32 bits
		 *
		 * @return UINT state of the first 32 bits
		 */
		UINT     ToUINT() const;
		/**
		 * @brief extract first 64 bits
		 *
		 * @return UINT64 state of the first 64 bits
		 */
		UINT64   ToUINT64() const;
		/**
		 * @brief set all bits to true
		 */
		VOID Set();
		/**
		 * @brief set all bits to false
		 */
		VOID Reset();
		/**
		 * @brief checks if all bits are set
		 *
		 * @return BOOL true if all bits are on, false otherwise
		 */
		BOOL All();
		/**
		 * @brief checks if at least 1 bit is set
		 *
		 * @return BOOL true if at least one bit is on, false otherwise
		 */
		BOOL Any();
		/**
		 * @brief checks if there are no bits set
		 *
		 * @return BOOL true if all bits are off, false otherwie
		 */
		BOOL None();
		/**
		 * @brief flip all bits state
		 */
		VOID Flip();
		/**
		 * @brief counts how many bits are set
		 *
		 * @return UINT 0..size bits that are on
		 */
		UINT Count();
		/**
		 * @brief inspect state of any bit
		 *
		 * @param position 0..size-1
		 * @return BOOL the state of specified bit
		 */
		BOOL Test(UINT position);
		/**
		 * @brief number of bits in the bitset
		 *
		 * @return UINT size
		 */
		UINT Size() const;
		/**
		 * @brief number of DWORD used in memory
		 *
		 * @return UINT raw size of the bitset divided by 4
		 */
		UINT Length() const;
		/**
		 * @brief Checks if at least 1 bit matches in between the two bitsets.
		 *
		 * @param other The bitset to compare against.
		 * @return Whether at least 1 bit matched.
		 */
		BOOL Intersects(const H3Bitset<size>& other) const;
		/**
		 * @brief Checks if all set bits contained in \p other also set in the current bitset
		 *
		 * @param other The bitset to compare against.
		 * @return Whether the current bitset contains all set bits from \p other.
		 */
		BOOL Contains(const H3Bitset<size>& other) const;

		H3Bitset& operator=(const H3Bitset<size>& other);
		BOOL operator!=(const H3Bitset<size>& other);
		BOOL operator==(const H3Bitset<size>& other);
		/**
		 * @brief allows if (!bitset) condition, same as if (bitset.None())
		 *
		 * @return BOOL whether all bits are off
		 */
		BOOL operator!();
		/**
		 * @brief allows if (bitset()) condition, same as if (bitset.Any())
		 *
		 * @return BOOL whether any bool is set
		 */
		BOOL operator()();
		/**
		 * @brief checks state of bit at specified index
		 *
		 * @param position 0..size-1
		 * @return BOOL true if the bit is set, false otherwise
		 */
		BOOL operator()(UINT position);
		/**
		 * @brief iterator at first position of bitset
		 *
		 * @return iterator at position 0
		 */
		iterator begin();
		/**
		 * @brief iterator beyond last position of bitset
		 *
		 * @return iterator at position size
		 */
		iterator end();
		/**
		 * @brief access bit state at specified index through iterator
		 *
		 * @param position 0..size-1
		 * @return iterator for the specified position allowing additional access
		 */
		iterator operator[](UINT position);
	};
#pragma pack(pop)
}

#endif /* #define _H3BITSET_HPP_ */