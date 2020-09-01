//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
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
	inline BOOL H3ZStream::Read(T & data, UINT data_size)
	{
		return Load(PVOID(&data), data_size);
	}
	template<typename T>
	inline BOOL H3ZStream::Write(T & data, UINT data_size)
	{
		return Save(PVOID(&data), data_size);
	}

	template<typename ObjectType>
	inline ObjectType* H3MapItem::Cast()
	{
		return reinterpret_cast<ObjectType*>(this);
	}
	template<typename ObjectType>
	inline ObjectType& H3MapItem::Get()
	{
		return *reinterpret_cast<ObjectType*>(this);
	}
	template<typename T>
	inline H3NetworkDataExtra<T>::H3NetworkDataExtra(int recipient_id, int msg_id, int data, const T& extra_data) :
		recipient_id(recipient_id),
		msg_id(msg_id),
		bufferSize(sizeof(H3NetworkData) + sizeof(T)),
		shortData(data),
		extra_data(extra_data)
	{
	}
}

#endif /* #define _H3STRUCTURES_INL_ */