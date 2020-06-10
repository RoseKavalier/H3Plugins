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

#include "../H3_Base.hpp"
#include "../H3_String.hpp"

namespace h3
{
#pragma pack(push, 1)
	template<UINT size>
	struct H3Bitset
	{
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
		struct iterator
		{
		protected:
			H3Bitset* m_bitset;
			UINT      m_position;
		public:
			iterator(H3Bitset* bitset);
			iterator(H3Bitset* bitset, UINT position);

			iterator& operator++();
			iterator  operator++(int);
			iterator& operator*();
			iterator* operator->();
			iterator& operator~(); // flips bit
			operator BOOL();         // if bit is set
			BOOL operator!();        // if bit is not set
			BOOL operator==(const iterator& other);
			BOOL operator!=(const iterator& other);
			VOID operator=(BOOL state);
			VOID Set();
			VOID Reset();
			VOID Flip();
		};

		H3Bitset();
		H3Bitset(UINT value);
		H3Bitset(UINT64 value);
		H3Bitset(const H3String& value);
		H3Bitset(const H3Bitset<size>& other);

		H3String ToString() const;
		H3String ToHexString() const;
		UINT     ToUINT() const;
		UINT64   ToUINT64() const;

		VOID Set();               // set all bits to true
		VOID Reset();             // set all bits to false
		BOOL All();               // if all bits are set
		BOOL Any();               // if any bit is set
		BOOL None();              // if no bits are set
		VOID Flip();              // flip all bits
		UINT Count();             // the number of bits set
		BOOL Test(UINT position); // the state of bool at position
		UINT Size();              // returns size of bitset
		UINT Length();            // the number of elements in the bitset array

		H3Bitset& operator=(const H3Bitset<size>& other);
		BOOL operator!=(const H3Bitset<size>& other);
		BOOL operator==(const H3Bitset<size>& other);
		BOOL operator!();  // checks if none are set
		BOOL operator()(); // if any is set
		BOOL operator()(UINT position); // checks state of position

		iterator begin();
		iterator end();
		iterator operator[](UINT position);
	};
#pragma pack(pop)
}

#endif /* #define _H3BITSET_HPP_ */