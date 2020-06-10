//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STRING_INL_
#define _H3STRING_INL_

#include "H3String.hpp"

namespace h3
{
	template<UINT Sz>
	inline H3String& H3String::AppendA(const CHAR(& buffer)[Sz])
	{
		return Append(buffer, Sz - 1);
	}
	template<UINT Sz>
	inline H3String & H3String::AssignA(const CHAR(&buffer)[Sz])
	{
		return Assign(buffer, Sz - 1);
	}
#ifdef _H3API_CPLUSPLUS11_
	template<typename ...Args>
	inline H3String&  H3String::Printf(LPCSTR format, Args ...args)
	{
		// * snprintf with null buffer returns print length
		// * does not count null-pointer in return value
#pragma warning(push)
#pragma warning(disable : 4996)
		UINT len = _snprintf(nullptr, 0, format, args ...);
		if (len > 0 && Reserve(len + 2))
		{
			len = _snprintf(Begin(), len + 1, format, args ...);
#pragma warning(pop)
			if (len)
			{
				m_length = len;
				m_string[len] = 0;
			}
		}
		return *this;
	}
	template<typename ...Args>
	inline H3String& H3String::PrintfAppend(LPCSTR format, Args ...args)
	{
		H3String append_to_me;
		append_to_me.Printf(format, args ...);
		Append(append_to_me);
		return *this;
	}
#endif

	inline H3String operator+(H3String&  lhs, H3String&  rhs)
	{
		H3String ans;
		if (!ans.Reserve(lhs.Length() + rhs.Length()))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(H3String&  lhs, CHAR rhs)
	{
		H3String ans;
		if (!(ans.Reserve(lhs.Length() + 1)))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(CHAR lhs, H3String&  rhs)
	{
		H3String ans;
		if (!(ans.Reserve(rhs.Length()) + 1))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(H3String&  lhs, LPCSTR rhs)
	{
		H3String ans;
		const UINT slen = strlen(rhs);
		if (!(ans.Reserve(lhs.Length()) + slen))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(LPCSTR lhs, H3String&  rhs)
	{
		H3String ans;
		UINT slen = strlen(lhs);
		if (!(ans.Reserve(rhs.Length()) + slen))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}
}

#endif /* #define _H3STRING_INL_ */