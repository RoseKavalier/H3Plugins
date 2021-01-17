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

	inline H3String operator+(const H3String&  lhs, const H3String&  rhs)
	{
		H3String ans;
		if (!ans.Reserve(lhs.Length() + rhs.Length()))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}
#ifdef _H3API_CPLUSPLUS11_
	inline H3String operator+(const H3String& lhs, H3String&& rhs)
	{
		rhs.Insert(0, lhs);
		return std::move(rhs);
	}

	inline H3String operator+(H3String&& lhs, const H3String& rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}

	inline H3String h3::operator+(H3String&& lhs, H3String&& rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}

	inline H3String operator+(H3String&& lhs, LPCSTR rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}

	inline H3String operator+(LPCSTR lhs, H3String&& rhs)
	{
		rhs.Insert(0, lhs);
		return std::move(rhs);
	}

	inline H3String operator+(H3String&& lhs, CHAR rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}

	inline H3String operator+(CHAR lhs, H3String&& rhs)
	{
		rhs.Insert(0, lhs);
		return std::move(rhs);
	}

#endif

	inline H3String operator+(const H3String& lhs, CHAR rhs)
	{
		H3String ans;
		if (!(ans.Reserve(lhs.Length() + 1)))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(CHAR lhs, const H3String& rhs)
	{
		H3String ans;
		if (!(ans.Reserve(rhs.Length()) + 1))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(const H3String& lhs, LPCSTR rhs)
	{
		H3String ans;
		const UINT slen = strlen(rhs);
		if (!(ans.Reserve(lhs.Length()) + slen))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3String operator+(LPCSTR lhs, const H3String& rhs)
	{
		H3String ans;
		UINT slen = strlen(lhs);
		if (!(ans.Reserve(rhs.Length()) + slen))
			return ans;
		ans += lhs;
		ans += rhs;
		return ans;
	}

	inline H3WString operator+(const H3WString& lhs, const H3WString& rhs)
	{
		H3WString string(lhs);
		string += rhs;
		return string;
	}
#ifdef _H3API_CPLUSPLUS11_
	inline H3WString operator+(H3WString&& lhs, const H3WString& rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}
	inline H3WString h3::operator+(const H3WString& lhs, H3WString&& rhs)
	{
		rhs.Insert(0, lhs);
		return std::move(rhs);
	}
	inline H3WString h3::operator+(H3WString&& lhs, H3WString&& rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}
	inline H3WString h3::operator+(H3WString&& lhs, LPCWSTR rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}
	inline H3WString h3::operator+(LPCWSTR lhs, H3WString&& rhs)
	{
		rhs.Insert(0, lhs);
		return std::move(rhs);
	}
	inline H3WString h3::operator+(H3WString&& lhs, WCHAR rhs)
	{
		lhs += rhs;
		return std::move(lhs);
	}
	H3WString h3::operator+(WCHAR lhs, H3WString&& rhs)
	{
		rhs.Insert(0, lhs);
		return std::move(rhs);
	}
#endif

	inline H3WString operator+(const H3WString& lhs, WCHAR rhs)
	{
		H3WString string(lhs);
		string += rhs;
		return string;
	}

	inline H3WString operator+(WCHAR lhs, const H3WString& rhs)
	{
		H3WString string(lhs);
		string += rhs;
		return string;
	}

	inline H3WString operator+(const H3WString& lhs, LPCWSTR rhs)
	{
		H3WString string(lhs);
		string += rhs;
		return string;
	}

	inline H3WString operator+(LPCWSTR lhs, const H3WString& rhs)
	{
		H3WString string(lhs);
		string += rhs;
		return string;
	}
}

#endif /* #define _H3STRING_INL_ */