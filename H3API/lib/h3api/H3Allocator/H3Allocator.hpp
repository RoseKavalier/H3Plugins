//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-15                        //
//                      Last edit: 2019-12-15                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3ObjectAllocator_HPP_
#define _H3ObjectAllocator_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

namespace h3
{
	// * a base structure to let H3 structures use 
	// * h3 operators new, delete, new[], delete[]	
	struct H3Allocator
	{
		_H3API_ PVOID operator new(const size_t sz);
		_H3API_ VOID  operator delete(const PVOID block);
		_H3API_ PVOID operator new[](const size_t sz);
		_H3API_ VOID  operator delete[](const PVOID block);
	};
	   	 
	// * an allocator to simulate h3's new & delete on objects
	template <typename T>
	struct H3ObjectAllocator
	{	
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;

		H3ObjectAllocator() noexcept;		
		// * allocates memory
		T* allocate(size_t number = 1) const noexcept;
		// * deallocates memory
		VOID deallocate(T* block) const noexcept;
		// * calls default constructor
		VOID construct(T* block) const noexcept;
		// * calls constructor with argument
		VOID construct(T* block, const T& value) const noexcept;
		// * calls constructor with 1 different argument
		template<typename U>
		VOID construct(T* block, const U& arg) const noexcept;
		// * calls default destructor
		VOID destroy(T* block) const noexcept;		

		template <typename U>
		H3ObjectAllocator(const H3ObjectAllocator<U>&) noexcept;
		template <typename U>
		bool operator==(const H3ObjectAllocator<U>&) const noexcept;
		template <typename U>
		bool operator!=(const H3ObjectAllocator<U>&) const noexcept;

#ifdef _CPLUSPLUS11_
		// * calls constructor with arbitrary number of arguments
		template<typename... Args>
		VOID construct(T* block, Args&&... args);
#endif
	};

	// * an allocator to similate use of h3's new[] & delete[] on arrays
	template <typename T>
	struct H3ArrayAllocator
	{
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
	private:		
		size_t* GetArrayBase(T* block) const noexcept;
		size_t GetArraySize(T* block) const noexcept;
	public:
		H3ArrayAllocator() noexcept;
		// * allocates memory
		T* allocate(size_t number = 1) const noexcept;
		// * deallocates memory
		VOID deallocate(T* block) const noexcept;
		// * calls default constructor
		VOID construct(T* block) const noexcept;
		// * calls constructor with argument
		VOID construct(T* block, const T& value) const noexcept;
		// * calls constructor with 1 different argument
		template<typename U>
		VOID construct(T* block, const U& arg) const noexcept;

		// * calls default destructor
		VOID destroy(T* block) const noexcept;

		template <typename U>
		H3ArrayAllocator(const H3ArrayAllocator<U>&) noexcept;
		template <typename U>
		bool operator==(const H3ArrayAllocator<U>&) const noexcept;
		template <typename U>
		bool operator!=(const H3ArrayAllocator<U>&) const noexcept;

#ifdef _CPLUSPLUS11_
		// * calls constructor with arbitrary number of arguments
		template<typename... Args>
		VOID construct(T* block, Args&&... args);
#endif
	};
}

#endif /* #define _H3ObjectAllocator_HPP_ */