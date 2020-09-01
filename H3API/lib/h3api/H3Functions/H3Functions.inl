//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3FUNCTIONS_INL_
#define _H3FUNCTIONS_INL_

#include "H3Functions.hpp"

namespace h3
{
	template<typename T>
	H3Point F_ReverseCoordinates(T * current_point, T * base_point, UINT map_size)
	{
		H3Point coordinates;
		UINT delta = current_point - base_point;
		coordinates.x = delta % map_size;
		delta /= map_size;
		coordinates.y = delta % map_size;
		coordinates.z = delta / map_size;
		return coordinates;
	}
}

#endif /* #define _H3FUNCTIONS_INL_ */