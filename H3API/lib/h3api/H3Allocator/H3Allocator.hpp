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
	/**
	 * @brief heap realloc using H3 assets
	 *
	 * @param obj memory block previously allocated by H3
	 * @param new_size the sought size of the new memory block
	 * @return reallocated memory block
	 */
	_H3API_ PVOID F_realloc(PVOID obj, UINT new_size);
	/**
	 * @brief calloc using H3 assets
	 *
	 * @param count the number of objects to allocate and null
	 * @param size sizeof() these objects
	 * @return allocated memory block initiated to 0s
	 */
	_H3API_ PVOID F_calloc(UINT count, UINT size = 1);
	/**
	 * @brief heapalloc using H3 assets
	 *
	 * @param size the sought size of the memory block
	 * @return VOID* allocated memory nlock
	 */
	_H3API_ PVOID F_malloc(UINT size);
	/**
	 * @brief heapfree using H3 assets
	 *
	 * @param obj a memory block previously allocated by H3
	 */
	_H3API_ VOID  F_delete(PVOID obj);
	/**
	 * @brief base structure to let structures use H3 operators new, delete, new[] and delete[]
	 *
	 */
	struct H3Allocator
	{
		_H3API_ PVOID operator new(const size_t sz);
		_H3API_ VOID  operator delete(PVOID block);
		_H3API_ PVOID operator new[](const size_t sz);
		_H3API_ VOID  operator delete[](PVOID block);
	};

	/**
	 * @brief An allocator to simulate H3's new & delete on objects
	 *
	 * @tparam T any type of data that will interact with H3 code
	 */
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
		/**
		 * @brief allocates an object
		 *
		 * @param number how many objects you wish to allocate, by default 1
		 * @return T* a memory block of \p number objects
		 */
		T* allocate(size_t number = 1) const noexcept;
		/**
		 * @brief deallocates a memory block previously allocated using H3 allocator
		 *
		 * @param block the object to deallocate
		 */
		VOID deallocate(T* block) const noexcept;
		/**
		 * @brief same as deallocate(T*), is a requirement for named allocators
		 * https://en.cppreference.com/w/cpp/named_req/Allocator
		 */
		VOID deallocate(T* block, size_t number) const noexcept;
		/**
		 * @brief calls default constructor on an allocated object
		 *
		 * @param block the object to construct
		 */
		VOID construct(T* block) const noexcept;
		/**
		 * @brief calls constructor with argument of matching type
		 *
		 * @param block the object to construct
		 * @param value the base argument to pass to the constructor
		 */
		VOID construct(T* block, const T& value) const noexcept;
		/**
		 * @brief calls constructor with argument of a different type
		 *
		 * @tparam U a type different than T
		 * @param block the object to construct
		 * @param arg an argument to pass to the constructor
		 */
		template<typename U>
		VOID construct(T* block, const U& arg) const noexcept;
		/**
		 * @brief calls default destructor
		 *
		 * @param block the object to destruct
		 */
		VOID destroy(T* block) const noexcept;

		/**
		 * @brief Requirement for named constructors
		 */
		template <typename U>
		H3ObjectAllocator(const H3ObjectAllocator<U>&) noexcept;
		/**
		 * @brief Requirement for named constructors
		 */
		template <typename U>
		bool operator==(const H3ObjectAllocator<U>&) const noexcept;
		/**
		 * @brief Requirement for named constructors
		 */
		template <typename U>
		bool operator!=(const H3ObjectAllocator<U>&) const noexcept;

#ifdef _H3API_CPLUSPLUS11_
		/**
		 * @brief calls constructor with arbitrary number of arguments
		 *
		 * @tparam Args any arguments list necessary
		 * @param block the object to construct
		 * @param args the arguments to pass to the constructor
		 */
		template<typename... Args>
		VOID construct(T* block, Args&&... args);
#endif
	};

	/**
	 * @brief An allocator to simulate H3's new[] & delete[] on object arrays
	 * The amount of objects is stored at array[-1]
	 * @tparam T any type of data that will interact with H3 code
	 */
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
		size_t* getArrayBase(T* block) const noexcept;
		size_t getArraySize(T* block) const noexcept;
	public:
		H3ArrayAllocator() noexcept;
		/**
		 * @brief allocates an object
		 *
		 * @param number how many objects you wish to allocate, by default 1
		 * @return T* a memory block of \p number objects
		 */
		T* allocate(size_t number = 1) const noexcept;
		/**
		 * @brief deallocates a memory block previously allocated using H3 allocator
		 *
		 * @param block the object to deallocate
		 */
		VOID deallocate(T* block) const noexcept;
		/**
		 * @brief calls default constructor on an allocated object
		 *
		 * @param block the object to construct
		 */
		VOID construct(T* block) const noexcept;
		/**
		 * @brief calls constructor with argument of matching type
		 *
		 * @param block the object to construct
		 * @param value the base argument to pass to the constructor
		 */
		VOID construct(T* block, const T& value) const noexcept;
		/**
		 * @brief calls constructor with argument of a different type
		 *
		 * @tparam U a type different than T
		 * @param block the object to construct
		 * @param arg an argument to pass to the constructor
		 */
		template<typename U>
		VOID construct(T* block, const U& arg) const noexcept;

		/**
		 * @brief calls default destructor on all objects
		 *
		 * @param block the object array to destruct
		 */
		VOID destroy(T* block) const noexcept;

		/**
		 * @brief Requirement for named constructors
		 */
		template <typename U>
		H3ArrayAllocator(const H3ArrayAllocator<U>&) noexcept;
		/**
		 * @brief Requirement for named constructors
		 */
		template <typename U>
		bool operator==(const H3ArrayAllocator<U>&) const noexcept;
		/**
		 * @brief Requirement for named constructors
		 */
		template <typename U>
		bool operator!=(const H3ArrayAllocator<U>&) const noexcept;

#ifdef _H3API_CPLUSPLUS11_
		// * calls constructor with arbitrary number of arguments
		template<typename... Args>
		VOID construct(T* block, Args&&... args);
#endif
	};

	/**
	 * @brief Common allocator type for Byte objects
	 */
	typedef H3ObjectAllocator<BYTE> ByteAllocator;
	/**
	 * @brief Common allocator type for char objects
	 */
	typedef H3ObjectAllocator<CHAR> CharAllocator;

#pragma pack(push, 4)
	/**
	 * @brief Stand-in for std::auto_ptr, mainly used for objects with virtual destructors
	 *
	 * @tparam T type for which a pointer is held
	 */
	template<typename T>
	struct H3AutoPtr
	{
	protected:
		BOOL8 m_used;
		T*    m_data;
	public:
		H3AutoPtr(T* _Ptr = 0);
		~H3AutoPtr();
		/**
		 * @brief get a pointer to managed object
		 *
		 * @return T* current pointer, may be NULL
		 */
		T* Get();
		/**
		 * @brief access the managed object and its methods directly
		 */
		T* operator->();
		/**
		 * @brief releases the managed object, replacing it with nullptr
		 * you become responsible of destroying and deallocating the returned object
		 * @return T* the managed object
		 */
		T* Release();
		/**
		 * @brief check the existence of an managed object
		 *
		 * @return BOOL8 whether there is a managed object
		 */
		BOOL8 Exists() const;
		/**
		 * @brief allows use of if (pointer)
		 *
		 * @return BOOL whether there is a managed object
		 */
		operator BOOL() const;
		/**
		 * @brief allows the use of if (!pointer)
		 *
		 * @return BOOL8 whether there is no managed object
		 */
		BOOL operator!() const;
		/**
		 * @brief dereference the managed object
		 *
		 * @return T& reference to managed object
		 */
		T& operator*() const;
	};
	_H3API_ASSERT_SIZE_(H3AutoPtr<h3unk>, 8);
#pragma pack(pop)

	/**
	 * @brief simili std::unique_ptr without C++11 requirements
	 *
	 * @tparam T type of object to manage
	 * @tparam H3ObjectAllocator<T> the allocator type to use, defaulted to H3ObjectAllocator
	 */
	template<typename T, typename Allocator = H3ObjectAllocator<T>>
	struct H3UniquePtr
	{
	protected:
		T* data;
		void destroy(T* block = nullptr);

	public:
		/**
		 * @brief Construct a new H3UniquePtr object
		 * data is initialized as nullptr
		 */
		H3UniquePtr();
		/**
		 * @brief Construct a new H3UniquePtr object
		 *
		 * @param source the data with which to initiate the data pointer
		 */
		H3UniquePtr(T* source);
		/**
		 * @brief Destruct and deallocates any managed object
		 *
		 */
		~H3UniquePtr();
		/**
		 * @brief sets a new managed object
		 * if an object is already managed, it is destructed and deallocated
		 * @param source new object to manage
		 */
		void Set(T* source);
		/**
		 * @brief get access to the managed object, if it exists
		 *
		 * @return T* the managed object
		 */
		T* Get();
		/**
		 * @brief access the managed object and its methods directly
		 */
		T* operator->();
		/**
		 * @brief releases the managed object, replacing it with nullptr
		 * you become responsible of destroying and deallocating the returned object
		 * @return T* the managed object
		 */
		T* Release();
		/**
		 * @brief Swaps the pointer's managed object with another pointer
		 *
		 * @param other the other pointer with which to swap contents
		 */
		void Swap(H3UniquePtr<T>& other);
		/**
		 * @brief allows the use of if (!pointer)
		 *
		 * @return BOOL whether there is no managed object
		 */
		BOOL operator!() const;
		/**
		 * @brief allows use of if (pointer)
		 *
		 * @return BOOL whether there is a managed object
		 */
		operator BOOL() const;

#ifdef _H3API_CPLUSPLUS11_
		/**
		 * @brief Construct a new H3UniquePtr object, taking ownership over its managed object
		 *
		 * @param other the pointer from which ownership should be taken
		 */
		H3UniquePtr(H3UniquePtr<T, Allocator>&& other);
		/**
		 * @brief Take control of another pointer's managed object
		 *
		 * @param other the pointer from which ownership should be taken
		 * @return H3UniquePtr<T, Allocator>& itself
		 */
		H3UniquePtr<T, Allocator>& operator=(H3UniquePtr<T, Allocator>&& other);
		H3UniquePtr<T, Allocator>& operator=(H3UniquePtr<T, Allocator>& other) = delete;
#else
	private:
		H3UniquePtr<T, Allocator>& operator=(H3UniquePtr<T, Allocator>& other);
#endif
	};
}

#endif /* #define _H3ObjectAllocator_HPP_ */