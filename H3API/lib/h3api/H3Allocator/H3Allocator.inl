//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-15                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3ObjectAllocator_INL_
#define _H3ObjectAllocator_INL_

#include "H3Allocator.hpp"

namespace h3
{
	template<typename T>
	inline H3ObjectAllocator<T>::H3ObjectAllocator() noexcept
	{
	}
	template<typename T>
	inline T * H3ObjectAllocator<T>::allocate(size_t number) const noexcept
	{
		return reinterpret_cast<T*>(F_malloc(number * sizeof(T)));
	}
	template<typename T>
	inline VOID H3ObjectAllocator<T>::deallocate(T * block) const noexcept
	{
		F_delete(reinterpret_cast<PVOID>(block));
	}
	template<typename T>
	inline VOID H3ObjectAllocator<T>::deallocate(T* block, size_t number) const noexcept
	{
		F_delete(reinterpret_cast<PVOID>(block));
	}
	template<typename T>
	inline VOID H3ObjectAllocator<T>::construct(T * block) const noexcept
	{
		new(reinterpret_cast<PVOID>(block)) T();
	}
	template<typename T>
	inline VOID H3ObjectAllocator<T>::construct(T * block, const T & value) const noexcept
	{
		new(reinterpret_cast<PVOID>(block)) T(value);
	}
	template<typename T>
	template<typename U>
	inline VOID H3ObjectAllocator<T>::construct(T * block, const U & arg) const noexcept
	{
		new(reinterpret_cast<PVOID>(block)) T(arg);
	}
	template<typename T>
	inline VOID H3ObjectAllocator<T>::destroy(T * block) const noexcept
	{
		block->~T();
	}
#ifdef _H3API_CPLUSPLUS11_
	template<typename T>
	template<typename ...Args>
	inline VOID H3ObjectAllocator<T>::construct(T * block, Args && ...args)
	{
		new(reinterpret_cast<PVOID>(block)) T(std::forward<Args>(args)...);
	}
#endif

	template<typename T>
	inline size_t * H3ArrayAllocator<T>::getArrayBase(T * block) const noexcept
	{
		return reinterpret_cast<size_t*>(block) - 1;
	}
	template<typename T>
	inline size_t H3ArrayAllocator<T>::getArraySize(T * block) const noexcept
	{
		return *getArrayBase(block);
	}
	template<typename T>
	inline H3ArrayAllocator<T>::H3ArrayAllocator() noexcept
	{
	}
	template<typename T>
	inline T * H3ArrayAllocator<T>::allocate(size_t number) const noexcept
	{
		size_t* block = reinterpret_cast<size_t*>(F_malloc(number * sizeof(T) + sizeof(size_t)));
		*block = number;
		return reinterpret_cast<T*>(block + 1);
	}
	template<typename T>
	inline VOID H3ArrayAllocator<T>::deallocate(T * block) const noexcept
	{
		F_delete(reinterpret_cast<PVOID>(getArrayBase(block)));
	}
	template<typename T>
	inline VOID H3ArrayAllocator<T>::construct(T * block) const noexcept
	{
		size_t number = getArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			new(reinterpret_cast<PVOID>(block)) T();
			++block;
		}
	}
	template<typename T>
	inline VOID H3ArrayAllocator<T>::construct(T * block, const T & value) const noexcept
	{
		size_t number = getArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			new(reinterpret_cast<PVOID>(block)) T(value);
			++block;
		}
	}
	template<typename T>
	template<typename U>
	inline VOID H3ArrayAllocator<T>::construct(T * block, const U & arg) const noexcept
	{
		size_t number = getArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			new(reinterpret_cast<PVOID>(block)) T(arg);
			++block;
		}
	}
	template<typename T>
	inline VOID H3ArrayAllocator<T>::destroy(T * block) const noexcept
	{
		size_t number = getArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			block->~T();
			++block;
		}
	}
	template<typename T>
	template<typename U>
	inline H3ObjectAllocator<T>::H3ObjectAllocator(const H3ObjectAllocator<U>&) noexcept
	{
	}
	template<typename T>
	template<typename U>
	inline bool H3ObjectAllocator<T>::operator==(const H3ObjectAllocator<U>&) const noexcept
	{
		return TRUE;
	}
	template<typename T>
	template<typename U>
	inline bool H3ObjectAllocator<T>::operator!=(const H3ObjectAllocator<U>&) const noexcept
	{
		return FALSE;
	}
	template<typename T>
	template<typename U>
	inline H3ArrayAllocator<T>::H3ArrayAllocator(const H3ArrayAllocator<U>&) noexcept
	{
	}

	template<typename T>
	template<typename U>
	inline bool H3ArrayAllocator<T>::operator==(const H3ArrayAllocator<U>&) const noexcept
	{
		return true;
	}

	template<typename T>
	template<typename U>
	inline bool H3ArrayAllocator<T>::operator!=(const H3ArrayAllocator<U>&) const noexcept
	{
		return false;
	}
#ifdef _H3API_CPLUSPLUS11_
	template<typename T>
	template<typename ...Args>
	inline VOID H3ArrayAllocator<T>::construct(T * block, Args && ...args)
	{
		size_t number = getArraySize(block);
		for (size_t i = 0; i < number; ++i)
		{
			new(reinterpret_cast<PVOID>(block)) T(std::forward<Args>(args)...);
			++block;
		}
	}
#endif
	template<typename T, typename Allocator>
	inline void H3UniquePtr<T, Allocator>::destroy(T* replacement)
	{
		if (replacement && replacement == data)
			return;
		if (data)
		{
			Allocator().destroy(data);
			Allocator().deallocate(data);
			data = nullptr;
		}
	}
	template<typename T, typename Allocator>
	inline H3UniquePtr<T, Allocator>::H3UniquePtr() :
		data()
	{
	}

	template<typename T, typename Allocator>
	inline H3UniquePtr<T, Allocator>::H3UniquePtr(T* source) :
		data(source)
	{
		source = nullptr;
	}
	template<typename T, typename Allocator>
	inline H3UniquePtr<T, Allocator>::~H3UniquePtr()
	{
		destroy();
	}
	template<typename T, typename Allocator>
	inline void H3UniquePtr<T, Allocator>::Set(T * source)
	{
		destroy(source); // check we aren't releasing ourselves
		data = source;
	}
	template<typename T, typename Allocator>
	inline T * H3UniquePtr<T, Allocator>::Get()
	{
		return data;
	}
	template<typename T, typename Allocator>
	inline T * H3UniquePtr<T, Allocator>::operator->()
	{
		return data;
	}
	template<typename T, typename Allocator>
	inline T * H3UniquePtr<T, Allocator>::Release()
	{
		T* r = data;
		data = nullptr;
		return r;
	}
	template<typename T, typename Allocator>
	inline void H3UniquePtr<T, Allocator>::Swap(H3UniquePtr<T>& other)
	{
		T* tmp     = data;
		data       = other.data;
		other.data = tmp;
	}
	template<typename T, typename Allocator>
	inline BOOL H3UniquePtr<T, Allocator>::operator!() const
	{
		return data == nullptr;
	}
	template<typename T, typename Allocator>
	inline H3UniquePtr<T, Allocator>::operator BOOL() const
	{
		return data != nullptr;
	}
#ifdef _H3API_CPLUSPLUS11_
	template<typename T, typename Allocator>
	inline H3UniquePtr<T, Allocator>::H3UniquePtr(H3UniquePtr<T, Allocator>&& other) :
		data(other.Release())
	{
	}
	template<typename T, typename Allocator>
	inline H3UniquePtr<T, Allocator>& H3UniquePtr<T, Allocator>::operator=(H3UniquePtr<T, Allocator>&& other)
	{
		if (&other == this)
			return *this;

		destroy();
		data = other.Release();

		return *this;
	}
#endif

	template<typename T>
	inline H3AutoPtr<T>::H3AutoPtr(T* _Ptr) :
		m_used(_Ptr != 0),
		m_data(_Ptr)
	{
	}

	template<typename T>
	inline H3AutoPtr<T>::~H3AutoPtr()
	{
		if (m_used)
		{
			delete m_data;
			m_used = FALSE;
		}
	}

	template<typename T>
	inline T* H3AutoPtr<T>::Get()
	{
		return m_data;
	}

	template<typename T>
	inline T* H3AutoPtr<T>::operator->()
	{
		return m_data;
	}

	template<typename T>
	inline T* H3AutoPtr<T>::Release()
	{
		T* ptr = m_data;
		m_used = FALSE;
		m_data = nullptr;
		return ptr;
	}

	template<typename T>
	inline BOOL8 H3AutoPtr<T>::Exists() const
	{
		return m_used;
	}

	template<typename T>
	inline H3AutoPtr<T>::operator BOOL() const
	{
		return m_used != FALSE;
	}

	template<typename T>
	inline BOOL H3AutoPtr<T>::operator!() const
	{
		return m_used == FALSE;
	}

	template<typename T>
	inline T& H3AutoPtr<T>::operator*() const
	{
		return *m_data;
	}

}

#endif /* #define _H3ObjectAllocator_INL_ */