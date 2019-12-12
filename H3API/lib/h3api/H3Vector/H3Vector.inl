//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//                      Last edit: 2019-12-05                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3VECTOR_INL_
#define _H3VECTOR_INL_

#include "H3Vector.hpp"

namespace h3
{
	template<typename _Elem>
	inline H3Vector<_Elem>::H3Vector(const int number_elements) :
		m_first(nullptr),
		m_end(nullptr),
		m_capacity(nullptr)
	{
		Reserve(number_elements);
	}
	template<typename _Elem>
	inline H3Vector<_Elem>::H3Vector() :
		m_first(nullptr),
		m_end(nullptr),
		m_capacity(nullptr)
	{
	}
	template<typename _Elem>
	inline H3Vector<_Elem>::~H3Vector()
	{
		if (m_first)
			delete[] m_first;
		m_first = nullptr;
		m_end = nullptr;
		m_capacity = nullptr;
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::begin()
	{
		return m_first;
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::end()
	{
		return m_end;
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Init()
	{
		m_first = nullptr;
		m_end = nullptr;
		m_capacity = nullptr;
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Deref()
	{
		if (m_first)
			delete[] m_first;
		m_first = nullptr;
		m_end = nullptr;
		m_capacity = nullptr;
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::IsEmpty() const
	{
		if (!m_first || m_first == m_end)
			return TRUE;
		return FALSE;
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::IsFull() const
	{
		if (m_end == m_capacity)
			return TRUE;
		return FALSE;
	}
	template<typename _Elem>
	inline INT32 H3Vector<_Elem>::Count() const
	{
		return m_end - m_first;
	}
	template<typename _Elem>
	inline INT32 H3Vector<_Elem>::CountMax() const
	{
		return m_capacity - m_first;
	}
	template<typename _Elem>
	inline UINT32 H3Vector<_Elem>::Size() const
	{
		return UINT32(m_end) - UINT32(m_first);
	}
	template<typename _Elem>
	inline UINT32 H3Vector<_Elem>::SizeAllocated() const
	{
		return UINT32(m_capacity) - UINT32(m_first);
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::RemoveLast()
	{
		Pop();
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::RemoveAll()
	{
		while (m_end > m_first)
		{
			--m_end;
			m_end->~_Elem();
		}
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::Add(_Elem& item)
	{
		if (!m_first || IsFull())
		{
			if (!Expand())
				return nullptr; // failed
		}
		*m_end = item;
		++m_end;
		return m_end - 1;  // returns position where it was added
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::AddOne(_Elem& item)
	{
		if (!m_first)
		{
			if (!Reserve(1))
				return nullptr;
		}
		else if (IsFull())
		{
			if (!Reserve(CountMax() + 1))
				return nullptr;
		}
		*m_end = item;
		++m_end;
		return m_end - 1;  // returns position where it was added
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::AddSize4(_Elem item)
	{
		THISCALL_4(VOID, 0x5FE2D0, this, m_end, 1, &item);
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Expand()
	{
		constexpr INT MIN_ELEMENTS    = 10;
		constexpr INT SIZE_MULTIPLIER = 2;

		if (!m_first)
			return Reserve(MIN_ELEMENTS);
		return Reserve(CountMax()* SIZE_MULTIPLIER);
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::First()
	{
		return m_first;
	}
	template<typename _Elem>
	inline const _Elem* H3Vector<_Elem>::CFirst() const
	{
		return m_first;
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::RFirst()
	{
		return *m_first;
	}
	template<typename _Elem>
	inline const _Elem& H3Vector<_Elem>::CRFirst() const
	{
		return *m_first;
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::Last()
	{
		return m_end - 1;
	}
	template<typename _Elem>
	inline const _Elem* H3Vector<_Elem>::CLast() const
	{
		return m_end - 1;
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::RLast()
	{
		return *Last();
	}
	template<typename _Elem>
	inline const _Elem& H3Vector<_Elem>::CRLast() const
	{
		return *CLast();
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::Append(_Elem& item)
	{
		return Add(item);
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::Push(_Elem& item)
	{
		return Add(item);
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::Pop()
	{
		if (m_end > m_first)
		{
			--m_end;
			m_end->~_Elem();
		}
		return m_end;
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::At(INT32 pos)
	{
		INT32 n;
		if (pos >= 0)
			n = std::min(pos, Count() - 1);
		else
		{
			int c = Count();
			n = std::min(-(pos), c);
			n = c - n;
		}
		return m_first + n;
	}
	template<typename _Elem>
	inline const _Elem* H3Vector<_Elem>::CAt(INT32 pos) const
	{
		INT32 n;
		if (pos >= 0)
			n = std::min(pos, Count() - 1);
		else
		{
			int c = Count();
			n = std::min(-(pos), c);
			n = c - n;
		}
		return m_first + n;
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::RAt(INT32 pos)
	{
		return *At(pos);
	}
	template<typename _Elem>
	inline const _Elem& H3Vector<_Elem>::CRAt(INT32 pos) const
	{
		return RAt(pos);
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(INT32 pos)
	{
		return Remove(pos, pos);
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(INT32 fromPos, INT32 toPos)
	{
		if (fromPos < 0 || toPos < 0 || toPos < fromPos)
			return FALSE;
		INT num = Count();
		if (fromPos >= num)
			return FALSE;

		INT to = std::min(num - 1, toPos);
		INT r = to - fromPos + 1;

		for (int i = fromPos; i <= toPos; ++i)
			m_first[i]->~_Elem();

		_Elem* rem = m_first + fromPos;
		_Elem* remEnd = rem + r;
		size_t copyLen = size_t(m_end) - size_t(remEnd);
		//* move any elements from the end
		memmove(PVOID(rem), PVOID(remEnd), copyLen);
		//* blank out the moved end elements
		F_memset(PVOID(remEnd), 0, copyLen);
		m_end -= r;
		return TRUE;
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Reserve(INT number)
	{
		if (number <= 0)
			return FALSE;

		INT num = Count();
		if (number <= num)
			return FALSE;

		_Elem *t = new _Elem[number];
		if (!t)
			return FALSE;

	#ifdef _CPLUSPLUS11_
		for (int i = 0; i < num; ++i)
			t[i] = std::move(m_first[i]);
	#else
		for (int i = 0; i < num; ++i)
			t[i] = m_first[i];
	#endif

		delete[] m_first;

		m_first = t;
		m_end = m_first + num;
		m_capacity = m_first + number;

		return TRUE;
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::operator[](INT32 pos)
	{
		return m_first[pos];
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::operator[](INT32 pos) const
	{
		return m_first[pos];
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::operator+=(_Elem& item)
	{
		return Add(item);
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::operator<<(_Elem& item)
	{
		return Add(item);
	}
#ifdef _H3_STD_CONVERSIONS_
	template<typename _Elem>
	inline H3Vector<_Elem>::H3Vector(std::vector<_Elem>& vec)
	{
		Init();
		for (_Elem* i = vec.begin(); i < vec.end(); ++i)
			Add(i);
	}
	template<typename _Elem>
	inline std::vector<_Elem> H3Vector<_Elem>::to_std_vector() const
	{
		std::vector<_Elem> vec;
		for (_Elem* i = begin(); i < end(); ++i)
			vec.push_back(*i);
		
		return vec;
	}
#endif
}

#endif /* #define _H3VECTOR_INL_ */