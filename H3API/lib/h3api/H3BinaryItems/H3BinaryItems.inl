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

#ifndef _H3BINARYITEMS_INL_
#define _H3BINARYITEMS_INL_

#include "H3BinaryItems.hpp"

namespace h3
{
	template<typename T>
	inline BinaryLoader<T>::BinaryLoader() :
		m_binary()
	{
	}
	template<typename T>
	inline h3::BinaryLoader<T>::BinaryLoader(T* binary_item) :
		m_binary(binary_item)
	{
	}
	template<typename T>
	inline BinaryLoader<T>::~BinaryLoader()
	{
		if (m_binary)
			m_binary->~T();
	}
	template<typename T>
	inline void BinaryLoader<T>::Set(T* binary)
	{
		m_binary = binary;
	}
	template<typename T>
	inline T* BinaryLoader<T>::Get()
	{
		return m_binary;
	}
	template<typename T>
	inline T* BinaryLoader<T>::operator->()
	{
		return m_binary;
	}

	inline DefLoader::DefLoader(LPCSTR name)
	{
		m_binary = h3::H3LoadedDEF::Load(name);
	}

	inline PcxLoader::PcxLoader(LPCSTR name)
	{
		m_binary = h3::H3LoadedPCX::Load(name);
	}
}

#endif /* #define _H3BINARYITEMS_INL_ */