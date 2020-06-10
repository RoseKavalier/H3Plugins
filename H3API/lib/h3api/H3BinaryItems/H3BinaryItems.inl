//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
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
	inline H3BinaryLoader<T>::H3BinaryLoader() :
		m_binary()
	{
	}
	template<typename T>
	inline H3BinaryLoader<T>::H3BinaryLoader(T* binary_item) :
		m_binary(binary_item)
	{
	}
	template<typename T>
	inline H3BinaryLoader<T>::~H3BinaryLoader()
	{
		if (m_binary)
			m_binary->Dereference();
	}
	template<typename T>
	inline void H3BinaryLoader<T>::Set(T* binary)
	{
		m_binary = binary;
	}
	template<typename T>
	inline T* H3BinaryLoader<T>::Get()
	{
		return m_binary;
	}
	template<typename T>
	inline T* H3BinaryLoader<T>::operator->()
	{
		return m_binary;
	}
	template<typename T>
	inline T* H3BinaryLoader<T>::operator*()
	{
		return m_binary;
	}
	template<typename T>
	inline BOOL H3BinaryLoader<T>::operator!()
	{
		return m_binary == nullptr;
	}

	inline H3DefLoader::H3DefLoader(LPCSTR name)
	{
		m_binary = H3LoadedDef::Load(name);
	}

	inline H3PcxLoader::H3PcxLoader(LPCSTR name)
	{
		m_binary = H3LoadedPcx::Load(name);
	}
	inline H3Pcx16Loader::H3Pcx16Loader(LPCSTR name)
	{
		m_binary = H3LoadedPcx16::Load(name);
	}
	inline H3FontLoader::H3FontLoader(LPCSTR name)
	{
		m_binary = H3Font::Load(name);
	}
	inline h3::H3TextFileLoader::H3TextFileLoader(LPCSTR name)
	{
		m_binary = H3TextFile::Load(name);
	}
	inline h3::H3TextTableLoader::H3TextTableLoader(LPCSTR name)
	{
		m_binary = H3TextTable::Load(name);
	}
}

#endif /* #define _H3BINARYITEMS_INL_ */