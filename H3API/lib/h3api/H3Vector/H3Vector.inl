//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
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
	inline _Elem * H3Vector<_Elem>::Allocate(UINT number)
	{
		return H3ObjectAllocator< _Elem>().allocate(number);
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Construct(_Elem* start, _Elem* finish)
	{
		while (start < finish)
		{
			H3ObjectAllocator< _Elem>().construct(start);
			++start;
		}
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Destruct(_Elem * start, _Elem * finish)
	{
		while (start < finish)
		{
			H3ObjectAllocator< _Elem>().destroy(start);
			++start;
		}
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Deallocate()
	{
		H3ObjectAllocator<_Elem>().deallocate(m_first);
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::reserveExtra(INT32 number)
	{
		const INT32 count = Count();
		const INT32 capacity = CountMax();
		const INT32 avail = capacity - count;
		if (avail >= number)
			return TRUE;

		return Reserve(EXPAND_NUMBER(number));
	}
	template<typename _Elem>
	inline INT H3Vector<_Elem>::EXPAND_NUMBER(INT minimumNeeded)
	{
		INT32 cap = CountMax();
		int num = std::max(cap * GROWTH_MULTIPLIER(), MIN_ELEMENTS());
		return std::max(num, minimumNeeded);
	}
	template<typename _Elem>
	inline INT H3Vector<_Elem>::MIN_ELEMENTS() const
	{
		return 10;
	}
	template<typename _Elem>
	inline INT H3Vector<_Elem>::GROWTH_MULTIPLIER() const
	{
		return 2;
	}

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
#ifdef _H3API_CPLUSPLUS11_
	template<typename _Elem>
	inline H3Vector<_Elem>::H3Vector(H3Vector<_Elem>&& other) :
		m_first(other.m_first), m_end(other.m_end), m_capacity(other.m_capacity)
	{
		other.m_first    = nullptr;
		other.m_end      = nullptr;
		other.m_capacity = nullptr;
	}
	template<typename _Elem>
	inline H3Vector<_Elem>& H3Vector<_Elem>::operator=(H3Vector<_Elem>&& other)
	{
		if (&other == this)
			return *this;
		RemoveAll();
		m_first    = other.m_first;
		m_end      = other.m_end;
		m_capacity = other.m_capacity;
		other.m_first    = nullptr;
		other.m_end      = nullptr;
		other.m_capacity = nullptr;
		return *this;
	}
	template<typename _Elem>
	inline void H3Vector<_Elem>::swap(H3Vector<_Elem>& other)
	{
		if (&other == this)
			return;

		_Elem* first     = m_first;
		_Elem* last      = m_end;
		_Elem* cap       = m_capacity;
		m_first          = other.m_first;
		m_end            = other.m_end;
		m_capacity       = other.m_capacity;
		other.m_first    = first;
		other.m_end      = last;
		other.m_capacity = cap;
	}
#endif

	template<typename _Elem>
	inline H3Vector<_Elem>::~H3Vector()
	{
		Deref();
	}
	template<typename _Elem>
	inline H3Vector<_Elem>::H3Vector(const H3Vector<_Elem>& other)
	{
		UINT num = other.Size();
		Resize(num);
		for (UINT i = 0; i < num; ++i)
			(*this)[i] = other[i];
	}
	template<typename _Elem>
	inline H3Vector<_Elem>& H3Vector<_Elem>::operator=(const H3Vector<_Elem>& other)
	{
		if (&other == this)
			return *this;
		RemoveAll();
		UINT num = other.Size();
		Resize(num);
		for (UINT i = 0; i < num; ++i)
			(*this)[i] = other[i];
		return *this;
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
	inline _Elem* H3Vector<_Elem>::begin() const
	{
		return m_first;
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::end() const
	{
		return m_end;
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Init()
	{
		m_first    = nullptr;
		m_end      = nullptr;
		m_capacity = nullptr;
	}
	template<typename _Elem>
	inline VOID H3Vector<_Elem>::Deref()
	{
		if (m_first)
		{
			Destruct(begin(), end());
			Deallocate();
		}
		m_first    = nullptr;
		m_end      = nullptr;
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
	inline UINT32 H3Vector<_Elem>::Size() const
	{
		return m_end - m_first;
	}
	template<typename _Elem>
	inline UINT32 H3Vector<_Elem>::Count() const
	{
		return m_end - m_first;
	}
	template<typename _Elem>
	inline UINT32 H3Vector<_Elem>::CountMax() const
	{
		return m_capacity - m_first;
	}
	template<typename _Elem>
	inline UINT32 H3Vector<_Elem>::RawSize() const
	{
		return UINT32(m_end) - UINT32(m_first);
	}
	template<typename _Elem>
	inline UINT32 H3Vector<_Elem>::RawSizeAllocated() const
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
		for (_Elem* i = begin(); i < end(); ++i)
			i->~_Elem();

		m_end = m_first;
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
		if (!m_first)
			return Reserve(MIN_ELEMENTS());
		return Reserve(CountMax() * GROWTH_MULTIPLIER());
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
	inline _Elem* H3Vector<_Elem>::At(UINT32 pos)
	{
		return m_first + pos;
	}
	template<typename _Elem>
	inline const _Elem* H3Vector<_Elem>::At(UINT32 pos) const
	{
		return m_first + pos;
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::RAt(UINT32 pos)
	{
		return *At(pos);
	}
	template<typename _Elem>
	inline const _Elem& H3Vector<_Elem>::RAt(UINT32 pos) const
	{
		return *At(pos);
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(UINT32 pos)
	{
		return Remove(begin() + pos, begin() + pos + 1);
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(UINT32 fromPos, UINT32 toPos)
	{
		return Remove(begin() + fromPos, begin() + toPos);

		//UINT num = Count();
		//if (fromPos >= num)
		//	return FALSE;
		//toPos = std::min(toPos, num);
		//if (toPos <= fromPos)
		//	return FALSE;
		//
		//Destruct(begin() + fromPos, begin() + toPos);
		//
		//_Elem* rem     = m_first + fromPos;
		//_Elem* remEnd  = rem + toPos;
		//size_t copyLen = size_t(m_end) - size_t(remEnd);

		////* move any elements from the end
		//memmove(PVOID(rem), PVOID(remEnd), copyLen);
		//
		//m_end -= toPos - fromPos;
		//return TRUE;
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(_Elem * first, _Elem * last)
	{
		if (first >= last || IsEmpty())
			return FALSE;
		if (first < m_first)
			first = m_first;
		if (last > m_end)
			last = m_end;

		Destruct(first, last);
#ifdef _H3API_CPLUSPLUS11_
		_Elem* itFirst = first;
		_Elem* itLast  = last;
		while (itLast < m_end)
		{
			*itFirst = std::move(*itLast);
			++itFirst;
			++itLast;
		}
#else
		memmove(PVOID(first), PVOID(last), UINT(m_end) - UINT(last));
#endif
		m_end -= last - first;

		return TRUE;
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Remove(_Elem * elem)
	{
		return Remove(elem, elem + 1);
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Reserve(UINT number)
	{
		UINT num = Count();
		if (number <= num)
			return TRUE;

		_Elem *t = Allocate(number);
		if (!t)
			return FALSE;

		Construct(&t[0], &t[number]);

	#ifdef _H3API_CPLUSPLUS11_
		for (UINT i = 0; i < num; ++i)
			t[i] = std::move(m_first[i]);
	#else
		for (UINT i = 0; i < num; ++i)
			t[i] = m_first[i];
	#endif
		Destruct(begin(), end());
		Deallocate();

		m_first    = t;
		m_end      = m_first + num;
		m_capacity = m_first + number;

		return TRUE;
	}
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Resize(UINT number)
	{
		const UINT count = Count();

		if (number == count)
		{
			m_end = m_capacity;
			return TRUE;
		}
		if (number > count)
		{
			if (!Reserve(number))
				return FALSE;
			m_end = m_capacity;
			return TRUE;
		}

		// number < count

		Destruct(begin() + number, end());
		m_end    = m_first + number;
		_Elem *t = Allocate(number);
		if (!t)
			return FALSE;

		Construct(t, t + number);

#ifdef _H3API_CPLUSPLUS11_
		for (UINT i = 0; i < number; ++i)
			t[i] = std::move(m_first[i]);
#else
		for (UINT i = 0; i < number; ++i)
			t[i] = m_first[i];
#endif
		Destruct(begin(), end());
		Deallocate();

		m_first    = t;
		m_end      = m_first + number;
		m_capacity = m_end;

		return TRUE;
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::operator[](UINT32 pos)
	{
		return m_first[pos];
	}
	template<typename _Elem>
	inline _Elem& H3Vector<_Elem>::operator[](UINT32 pos) const
	{
		return m_first[pos];
	}
	template<typename _Elem>
	inline _Elem* H3Vector<_Elem>::operator+=(_Elem& item)
	{
		return Add(item);
	}
#ifdef _H3API_CPLUSPLUS11_
	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::Add(_Elem && item)
	{
		if (!m_first || IsFull())
		{
			if (!Expand())
				return nullptr; // failed
		}
		*m_end = std::move(item);
		++m_end;
		return m_end - 1;  // returns position where it was added
	}
	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::Push(_Elem && item)
	{
		return Add(std::move(item));
	}

	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::AddOne(_Elem && item)
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
		*m_end = std::move(item);
		++m_end;
		return m_end - 1;  // returns position where it was added
	}

	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::Append(_Elem && item)
	{
		return Add(std::move(item));
	}

	template<typename _Elem>
	inline _Elem * H3Vector<_Elem>::operator+=(_Elem && item)
	{
		return Add(std::move(item));
	}

	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Insert(_Elem * position, _Elem * first, _Elem * last)
	{
		if (UINT(first) >= UINT(last))
			return FALSE;

		const UINT32 num = last - first;
		const UINT32 currNum = Count();
		UINT32 pos = 0;
		if (!IsEmpty())
		{
			if (UINT(position) > UINT(begin()))
			{
				if (UINT(position) > UINT(end()))
					pos = currNum;
				else
					pos = position - begin();
			}
		}

		if (!reserveExtra(num))
			return FALSE;

		// move elements to end
		_Elem* origStart = begin() + pos;
		_Elem* newEnd = end() + num - 1;
		_Elem* oldEnd = end() - 1;
		if (pos < currNum)
		{
			while (oldEnd >= origStart)
			{
#ifdef _H3API_CPLUSPLUS11_
				*newEnd-- = std::move(*oldEnd--);
#else
				*newEnd-- = *oldEnd--;
#endif
			}
		}

		// Insert new elements
		_Elem* it = first;
		while (it < last)
		{
			*origStart++ = *it++;
		}

		m_end += num;

		return TRUE;
	}

#endif
#ifdef _H3_STD_CONVERSIONS_
	template<typename _Elem>
	inline BOOL H3Vector<_Elem>::Insert(_Elem * position, typename std::vector<_Elem>::iterator first, typename std::vector<_Elem>::iterator last)
	{
		if (first >= last)
			return FALSE;

		const INT32 num = std::distance(first, last);
		const INT32 currNum = Count();
		INT32 pos = 0;
		if (!IsEmpty())
		{
			if (UINT(position) > UINT(begin()))
			{
				if (UINT(position) > UINT(end()))
					pos = currNum;
				else
					pos = position - begin();
			}
		}

		if (!reserveExtra(num))
			return FALSE;

		// move elements to end
		_Elem* origStart = begin() + pos;
		_Elem* newEnd = end() + num - 1;
		_Elem* oldEnd = end() - 1;
		if (pos < currNum)
		{
			while (oldEnd >= origStart)
			{
#ifdef _H3API_CPLUSPLUS11_
				*newEnd-- = std::move(*oldEnd--);
#else
				*newEnd-- = *oldEnd--;
#endif
			}
		}

		// Insert new elements
		while (first < last)
		{
			*origStart++ = *first++;
		}

		m_end += num;

		return TRUE;
	}

	template<typename _Elem>
	inline H3Vector<_Elem>::H3Vector(const std::vector<_Elem>& vec)
	{
		Init();
		const INT n = vec.size();
		Reserve(n);
		for (int i = 0; i < n; ++i)
			Add(const_cast<_Elem&>(vec[i]));
		return *this;
	}
	template<typename _Elem>
	inline std::vector<_Elem> H3Vector<_Elem>::to_std_vector() const
	{
		std::vector<_Elem> vec;
		for (_Elem* i = begin(); i < end(); ++i)
			vec.push_back(*i);

		return vec;
	}
	template<typename _Elem>
	inline H3Vector<_Elem>& H3Vector<_Elem>::operator=(const std::vector<_Elem>& vec)
	{
		RemoveAll();
		const INT n = vec.size();
		Reserve(n);
		for (int i = 0; i < n; ++i)
			Add(const_cast<_Elem&>(vec[i]));
		return *this;
	}
#endif
}

#endif /* #define _H3VECTOR_INL_ */