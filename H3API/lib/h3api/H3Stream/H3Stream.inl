//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2020-04-27                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STREAM_INL_
#define _H3STREAM_INL_

#include "H3Stream.hpp"

namespace h3
{
#ifdef _CPLUSPLUS11_
	template<typename ...Args>
	inline H3Stream& H3Stream::Write(LPCSTR format, Args ...args)
	{
		if (IsReady() && CanWrite())
			CDECL_VA2(int, 0x61A031, m_file, format, args ...);
		return *this;
	}
	template<INT32 sz>
	inline H3Stream& H3Stream::operator<<(const CHAR(&expression)[sz])
	{
		if (IsReady() && CanWrite())
			F_fwrite(reinterpret_cast<PVOID>(&expression), 1, sz, m_file);
		return *this;
	}
	template<typename T>
	inline VOID H3Stream::Printf(LPCSTR format, T value)
	{
		if (IsReady() && CanWrite())
			CDECL_3(int, 0x61A031, m_file, format, value);
	}
#endif

	template<typename T>
	inline BOOL h3::H3File::Read(const T & data, size_t sz)
	{
		return read(PVOID(&data), sz);
	}
	template<typename T>
	inline BOOL H3File::Write(const T & data, size_t sz)
	{
		return write(PVOID(&data), sz);
	}
}

#endif /* #define _H3STREAM_INL_ */