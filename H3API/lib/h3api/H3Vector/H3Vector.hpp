//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3VECTOR_HPP_
#define _H3VECTOR_HPP_

#include "../H3_Base.hpp"

#if defined(_H3API_STD_CONVERSIONS_) || defined(_H3API_STD_VECTOR_)
#include <vector>
#endif

namespace h3
{
#pragma pack(push, 4)
	/**
	 * @brief a vector following the H3 format
	 *
	 * @tparam _Elem type of element to store
	*/
	template<typename _Elem>
	struct H3Vector : H3Allocator
	{
	protected:
		h3unk _allocator; // useless
		// * the first item, also start of list
		_Elem *m_first;
		// * the end of last item
		_Elem *m_end;
		// * end of allocated memory
		_Elem *m_capacity;

		_Elem* Allocate(UINT number);
		VOID Construct(_Elem* start, _Elem* finish);
		VOID Destruct(_Elem* start, _Elem* finish);
		VOID Deallocate();
		BOOL reserveExtra(INT32 number);

		UINT EXPAND_NUMBER(UINT minimumNeeded);
		UINT MIN_ELEMENTS() const;
		UINT GROWTH_MULTIPLIER() const;
	public:
		H3Vector(UINT number_elements);
		H3Vector();
		~H3Vector();

		H3Vector(const H3Vector<_Elem>& other);
		H3Vector<_Elem>& operator=(const H3Vector<_Elem>& other);

#ifdef _H3API_CPLUSPLUS11_
		H3Vector(H3Vector<_Elem>&& other);
		H3Vector<_Elem>& operator=(H3Vector<_Elem>&& other);
#endif

		void swap(H3Vector<_Elem>& other);

		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_Elem* begin();
		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_Elem* end();
		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_Elem* begin() const;
		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_Elem* end() const;

		// * ~constructor
		VOID Init();
		// * ~destructor.
		VOID Deref();
		// * If list is empty
		BOOL IsEmpty() const;
		// * If vector is full
		BOOL IsFull() const;
		// * the number of items
		UINT32 Size() const;
		// * the number of items
		UINT32 Count() const;
		// * the maximum number of items
		UINT32 CountMax() const;
		// * calculates size
		UINT32 RawSize() const;
		// * calculates allocated size
		UINT32 RawSizeAllocated() const;
		// * removes the last item
		VOID RemoveLast();
		// * empties list
		VOID RemoveAll();
		// * Adds item
		_Elem* Add(const _Elem & item);
		// * Adds only 1 item, expands by only 1
		_Elem* AddOne(const _Elem & item);
		// * only for size 4 or references, H3 code
		VOID AddSize4(_Elem item);
		// * increases capacity
		BOOL Expand();
		// * returns First item
		_Elem *First();
		const _Elem *CFirst() const;
		_Elem& RFirst();
		const _Elem& CRFirst() const;
		// * returns Last item
		_Elem *Last();
		const _Elem *CLast() const;
		_Elem& RLast();
		const _Elem& CRLast() const;
		// * Add one item to end
		_Elem* Append(const _Elem & item);
		// * Add a single item, expanding by 1
		_Elem* Push(const _Elem & item);
		// * Removes last item and returns reference to it
		_Elem* Pop();
		// * Returns item at position, can be negative to get from end
		_Elem* At(UINT32 pos);
		const _Elem* At(UINT32 pos) const;
		// * returns reference to item at position
		_Elem& RAt(UINT32 pos);
		const _Elem& RAt(UINT32 pos) const;
		// * remove one item, elements shift left
		BOOL Remove(UINT32 pos);
		// * remove range, elements shift left
		BOOL Remove(UINT32 fromPos, UINT32 toPos);
		// * removes elements [first, last) (that is, last is excluded)
		BOOL Remove(_Elem* first, _Elem* last);
		// * removes element and shifts remaining left
		BOOL Remove(_Elem* elem);
		// * reserves a number of elements, always greater than current
		BOOL Reserve(UINT number);
		// * Sets the current size to the specified number, smaller or greater
		BOOL Resize(UINT number);

		// * returns reference to element at pos, positive only
		_Elem& operator[](UINT32 pos);
		_Elem& operator[](UINT32 pos) const;
		// * Adds item to end of list
		_Elem* operator+=(const _Elem & item);

		BOOL Insert(_Elem* position, _Elem* first, _Elem* last);
		BOOL Insert(_Elem* position, const _Elem& elem);

#ifdef _H3API_CPLUSPLUS11_
		_Elem* Add(_Elem&& item);
		_Elem* Push(_Elem&& item);
		_Elem* AddOne(_Elem&& item);
		_Elem* Append(_Elem&& item);
		_Elem* operator+=(_Elem&& item);
#endif

	#ifdef _H3API_STD_CONVERSIONS_
		BOOL Insert(_Elem* position, typename std::vector<_Elem>::iterator first, typename std::vector<_Elem>::iterator last);
		H3Vector(const std::vector<_Elem>& vec);
		std::vector<_Elem> to_std_vector() const;
		H3Vector<_Elem>& operator=(const std::vector<_Elem>& vec);
	#endif /* _H3API_STD_CONVERSIONS_ */
	};
	_H3API_ASSERT_SIZE_(H3Vector<h3unk>, 16);
#pragma pack(pop)

#ifdef _H3API_STD_VECTOR_
#if defined(_MSC_VER) && (_MSC_VER >= 1800) // in VS2008, std::vector has size 20~24 which is not compatible.

#ifndef _DEBUG
#pragma pack(push, 4)
	/**
	 * @brief Required padding for H3StdVector<> to match H3Vector<> format
	*/
	class H3AllocatorReference
	{
		h3unk m_allocatorReference;
	};
#pragma pack(pop)
#endif

#ifdef _DEBUG // debug std::vector can be used directly as H3Vector
	/**
	 * @brief std::vector that is valid to be used as a H3Vector in debug format
	 *
	 * @tparam T type of element to store
	*/
	template<typename T>
	class H3StdVector : public std::vector<T, H3ObjectAllocator<T>>
#else // non-debug std::vector requires padding to use as H3Vector
	/**
	 * @brief std::vector that is valid to be used as a H3Vector in non-debug format
	 *
	 * @tparam T type of element to store
	*/
	template<typename T>
	struct H3StdVector : H3AllocatorReference, public std::vector<T, H3ObjectAllocator<T>>

#endif /* _DEBUG */
		// implementation
	{
	public:
		using std::vector<T, H3ObjectAllocator<T>>::vector; // inherit constructors
	};
	_H3API_ASSERT_SIZE_(H3StdVector<h3unk>, 16);
#endif /* defined(_MSC_VER) && (_MSC_VER >= 1800) */
#endif /* _H3API_STD_VECTOR_ */
}

#endif /* #define _H3VECTOR_HPP_ */