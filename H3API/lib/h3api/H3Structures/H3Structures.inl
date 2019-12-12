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
	inline H3NetorkDataExtra<T>::H3NetorkDataExtra(int recipient_id, int msg_id, int data, T& extra_data) :
		recipient_id(recipient_id),
		msg_id(msg_id),
		buffer_size(sizeof(H3NetworkData) + sizeof(T)),
		short_data(data),
		extra_data(extra_data)
	{
	}
}

#endif /* #define _H3STRUCTURES_INL_ */