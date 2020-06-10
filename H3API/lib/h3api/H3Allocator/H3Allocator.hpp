//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-15                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3ObjectAllocator_HPP_
#define _H3ObjectAllocator_HPP_

#include "../H3_Core.hpp"
#include "../H3_Config.hpp"

namespace h3
{
	// * heap realloc using H3 assets
	_H3API_ PVOID F_realloc(PVOID obj, UINT new_size);
	// * calloc using h3 assets
	_H3API_ PVOID F_calloc(UINT count, UINT size = 1);
	// * heapalloc using H3 assets
	_H3API_ PVOID F_malloc(UINT size);
	// * heapfree using H3 assets
	_H3API_ VOID  F_delete(PVOID obj);

	// * a base structure to let H3 structures use
	// * h3 operators new, delete, new[], delete[]
	struct H3Allocator
	{
		_H3API_ PVOID operator new(const size_t sz);
		_H3API_ VOID  operator delete(PVOID block);
		_H3API_ PVOID operator new[](const size_t sz);
		_H3API_ VOID  operator delete[](PVOID block);
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

#ifdef _H3API_CPLUSPLUS11_
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

#ifdef _H3API_CPLUSPLUS11_
		// * calls constructor with arbitrary number of arguments
		template<typename... Args>
		VOID construct(T* block, Args&&... args);
#endif
	};

	typedef H3ObjectAllocator<BYTE> ByteAllocator;
	typedef H3ObjectAllocator<CHAR> CharAllocator;

	// * simili std::unique_ptr
	template<typename T, typename Allocator = H3ObjectAllocator<T>>
	struct H3UniquePtr
	{
	protected:
		T* data;
		void destroy(T* block = nullptr);

	public:
		H3UniquePtr();
		H3UniquePtr(T* source);
		~H3UniquePtr();
		void Set(T* source);
		T* Get();
		T* operator->();
		T* Release();
		void Swap(H3UniquePtr<T>& other);
		BOOL operator!() const;

#ifdef _H3API_CPLUSPLUS11_
		H3UniquePtr(H3UniquePtr<T, Allocator>&& other);
		H3UniquePtr<T, Allocator>& operator=(H3UniquePtr<T, Allocator>&& other);
		H3UniquePtr<T, Allocator>& operator=(H3UniquePtr<T, Allocator>& other) = delete;
#else
	private:
		H3UniquePtr<T, Allocator>& operator=(H3UniquePtr<T, Allocator>& other) {return *this}
#endif
	};
}

#endif /* #define _H3ObjectAllocator_HPP_ */