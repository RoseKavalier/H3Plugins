#ifndef _H3BASE_INL_
#define _H3BASE_INL_

#include "H3Base.hpp"

namespace h3
{
	template<typename T>
	inline H3SmartPointer<T>::H3SmartPointer(T* _Ptr) :
		m_used(_Ptr != 0),
		m_data(_Ptr)
	{
	}
#ifdef _CPLUSPLUS11_
	template<typename T>
	inline H3SmartPointer<T>::H3SmartPointer(H3SmartPointer<T>&& other) :
		m_used(other.m_used),
		m_data(other.release())
	{
	}
#else
	template<typename T>
	inline H3SmartPointer<T>::H3SmartPointer(H3SmartPointer<T>& other) :
		m_used(other.m_used),
		m_data(other.release())
	{
	}
#endif

	template<typename T>
	inline H3SmartPointer<T>::~H3SmartPointer()
	{
		if (m_used)
			m_data->~T();
	}

	template<typename T>
	inline T* H3SmartPointer<T>::get()
	{
		return m_data;
	}

	template<typename T>
	inline T* H3SmartPointer<T>::operator->()
	{
		return get();
	}

	template<typename T>
	inline T* H3SmartPointer<T>::release()
	{
		T* _Ptr = m_data;
		m_used = FALSE;
		m_data = nullptr;
		return _Ptr;
	}
}

#endif /* #define _H3BASE_INL_ */