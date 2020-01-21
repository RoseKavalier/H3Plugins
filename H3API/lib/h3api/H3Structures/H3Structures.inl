//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STRUCTURES_INL_
#define _H3STRUCTURES_INL_

#include "H3Structures.hpp"

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

	template<typename T>
	inline H3NetworkDataExtra<T>::H3NetworkDataExtra(int recipient_id, int msg_id, int data, T& extra_data) :
		recipient_id(recipient_id),
		msg_id(msg_id),
		buffer_size(sizeof(H3NetworkData) + sizeof(T)),
		short_data(data),
		extra_data(extra_data)
	{
	}
}

#endif /* #define _H3STRUCTURES_INL_ */