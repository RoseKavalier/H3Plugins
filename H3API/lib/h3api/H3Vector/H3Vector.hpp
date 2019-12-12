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

#ifndef _H3VECTOR_HPP_
#define _H3VECTOR_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

#ifdef _H3_STD_CONVERSIONS_
#include <vector>
#endif

namespace h3
{
#pragma pack(push, 1)
	// * a vector following the H3 format
	template<typename _Elem>
	struct H3Vector : public H3Allocator
	{
	protected:
		BOOL _init; // useless
		// * the first item, also start of list
		_Elem *m_first;
		// * the end of last item
		_Elem *m_end;
		// * end of allocated memory
		_Elem *m_capacity;
	public:
		H3Vector(const int number_elements);
		H3Vector();
		~H3Vector();

		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_Elem* begin();
		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_Elem* end();

		// * ~constructor
		VOID Init();
		// * ~destructor.
		VOID Deref();
		// * If list is empty
		BOOL IsEmpty() const;
		// * If vector is full
		BOOL IsFull() const;
		// * the number of items
		INT32 Count() const;
		// * the maximum number of items
		INT32 CountMax() const;
		// * calculates size
		UINT32 Size() const;
		// * calculates allocated size
		UINT32 SizeAllocated() const;
		// * removes the last item
		VOID RemoveLast();
		// * empties list
		VOID RemoveAll();
		// * Adds item
		_Elem* Add(_Elem & item);
		// * Adds only 1 item, expands by only 1
		_Elem* AddOne(_Elem & item);
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
		_Elem* Append(_Elem & item);
		// * Add a single item, expanding by 1
		_Elem* Push(_Elem & item);
		// * Removes last item and returns reference to it
		_Elem* Pop();
		// * Returns item at position, can be negative to get from end
		_Elem* At(INT32 pos);
		const _Elem* CAt(INT32 pos) const;
		// * returns reference to item at position
		_Elem& RAt(INT32 pos);
		const _Elem& CRAt(INT32 pos) const;
		// * remove one item, elements shift left
		BOOL Remove(INT32 pos);
		// * remove range, list shifts left
		BOOL Remove(INT32 fromPos, INT32 toPos);
		// * reserves a number of elements, always greater than current
		BOOL Reserve(INT number);

		// * returns reference to element at pos, positive only
		_Elem& operator[](INT32 pos);
		_Elem& operator[](INT32 pos) const;
		// * Adds item to end of list
		_Elem* operator+=(_Elem & item);
		// * Adds item to end of list
		_Elem* operator<<(_Elem & item);

	#ifdef _H3_STD_CONVERSIONS_
		H3Vector(std::vector<_Elem>& vec);
		std::vector<_Elem> to_std_vector() const;
	#endif /* _H3_STD_CONVERSIONS_ */
	};
#pragma pack(pop)
}

#endif /* #define _H3VECTOR_HPP_ */