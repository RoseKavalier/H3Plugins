//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//                      Last edit: 2019-12-05                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STRING_INL_
#define _H3STRING_INL_

#include "H3String.hpp"

namespace h3
{
	template<INT32 Sz>
	inline H3String& H3String::Append(const CHAR(& buffer)[Sz])
	{
		return Append(buffer, Sz - 1);
	}
	template<INT32 Sz>
	inline H3String& H3String::operator+=(const CHAR(&buffer)[Sz])
	{
		return Append(buffer, Sz - 1);
	}
#ifdef _CPLUSPLUS11_
	template<typename ...Args>
	inline H3String&  H3String::Printf(LPCSTR format, Args ...args)
	{
		// * snprintf with null buffer returns print length
		int len = _snprintf(nullptr, 0, format, args ...);
		if (len > 0 && Reserve(len + 1))
		{
			len = _snprintf(Begin(), len, format, args ...);
			if (len)
			{
				length = len - 1;
				str[len] = 0;
			}
		}
		return *this;
	}
	template<typename ...Args>
	inline H3String&  H3String::PrintfAppend(LPCSTR format, Args ...args)
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
		const int slen = strlen(rhs);
		if (!(ans.Reserve(lhs.Length()) + slen))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(LPCSTR lhs, H3String&  rhs)
	{
		H3String ans;
		int slen = strlen(lhs);
		if (!(ans.Reserve(rhs.Length()) + slen))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}
}

#endif /* #define _H3STRING_INL_ */