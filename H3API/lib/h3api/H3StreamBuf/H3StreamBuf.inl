//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2020-05-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STREAMBUF_INL_
#define _H3STREAMBUF_INL_

#include "H3StreamBuf.hpp"

namespace h3
{
	template<typename T>
	inline BOOL h3::H3Streambuf::Read(T & data, UINT data_size)
	{
		return Load(PVOID(&data), data_size);
	}
	template<typename T>
	inline BOOL H3Streambuf::Write(T & data, UINT data_size)
	{
		return Save(PVOID(&data), data_size);
	}
}

#endif /* #define _H3STREAMBUF_INL_ */