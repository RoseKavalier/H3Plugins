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

#include "H3String.hpp"

namespace h3
{
	_H3API_ VOID H3String::Deref()
	{
		str = nullptr;
		length = 0;
		capacity = 0;
	}
	_H3API_ VOID H3String::NullTerminate()
	{
		*End() = 0;
	}
	_H3API_ BOOL H3String::Realloc(int new_size)
	{
		return THISCALL_2(BOOL, 0x404B80, this, new_size);
	}
	_H3API_ VOID H3String::ClearUnused()
	{
		const int to_clear = capacity - length;
		F_memset(PVOID(str + length), 0, to_clear);
	}
	_H3API_ BOOL H3String::CompareChars(LPCSTR chars, INT32 num_chars, INT32 pos, BOOL is_true) const
	{
		for (INT32 i = 0; i < num_chars; ++i)
			if (str[pos] == chars[i])
				return is_true;

		return !is_true;
	}
	_H3API_ INT32 H3String::CompareFirstOf(LPCSTR chars, INT32 num_chars, BOOL is_true) const
	{
		if (!str || !length)
			return HS_NOTFOUND;

		for (int i = 0; i < length; ++i)
			if (CompareChars(chars, num_chars, i, is_true))
				return i;
		return HS_NOTFOUND;
	}

	_H3API_ INT32 H3String::CompareLastOf(LPCSTR chars, INT32 num_chars, BOOL is_true) const
	{
		if (!str || !length)
			return HS_NOTFOUND;

		for (int i = length - 1; i >= 0; --i)
			if (CompareChars(chars, num_chars, i, is_true))
				return i;
		return HS_NOTFOUND;
	}

	_H3API_ H3String::H3String() :
		str(nullptr),
		length(0),
		capacity(0)
	{
	}

	_H3API_ H3String::H3String(LPCSTR msg) :
		str(nullptr),
		length(0),
		capacity(0)
	{
		Assign(msg);
	}

	_H3API_ H3String::H3String(LPCSTR msg, INT32 len) :
		str(nullptr),
		length(0),
		capacity(0)
	{
		Assign(msg, len);
	}

	_H3API_ H3String::H3String(const H3String& other) :
		str(nullptr),
		length(0),
		capacity(0)
	{
		Assign(other);
	}
	_H3API_ H3String::H3String(CHAR ch) :
		str(nullptr),
		length(0),
		capacity(0)
	{
		Assign(ch);
	}

#ifdef _CPLUSPLUS11_
	_H3API_ H3String::H3String(H3String&& other) noexcept :
		str(other.str),
		length(other.length),
		capacity(other.capacity)
	{
		other.Deref();
	}
#endif

	_H3API_ H3String::~H3String()
	{
		Dereference();
	}

	_H3API_ VOID H3String::Init()
	{
		THISCALL_2(VOID, 0x404130, this, 0);
	}

	_H3API_ VOID H3String::Dereference()
	{
		THISCALL_1(VOID, 0x4040F0, this);
	}

	_H3API_ INT32 H3String::Length() const
	{
		return length;
	}

	_H3API_ INT32 H3String::MaxLength() const
	{
		return capacity;
	}

	_H3API_ LPCSTR H3String::String() const
	{
		return str;
	}

	_H3API_ CHAR* H3String::begin()
	{
		return str;
	}

	_H3API_ CHAR* H3String::end()
	{
		return str + length;
	}

	_H3API_ PCHAR H3String::Begin()
	{
		return str;
	}

	_H3API_ PCHAR H3String::End()
	{
		return str + length;
	}

	_H3API_ CHAR H3String::Last() const
	{
		return str[length - 1];
	}

	_H3API_ H3String& H3String::Assign(LPCSTR mes, INT32 len)
	{
		if (mes)
			return THISCALL_3(H3String&, 0x404180, this, mes, len);
		return *this;
	}

	_H3API_ H3String& H3String::Assign(LPCSTR mes)
	{
		return Assign(mes, strlen(mes));
	}

	_H3API_ H3String& H3String::Assign(CHAR ch)
	{
		if (ch == '\0')
			return *this;
		return Assign(&ch, 1);
	}

	_H3API_ H3String& H3String::Assign(const H3String& other)
	{
		if (other.String())
			return Assign(other.String(), other.Length());
		return *this;
	}

	_H3API_ H3String& H3String::Assign(INT32 number)
	{
		const int len = F_sprintf("%d", number);
		Assign(h3_TextBuffer, len);
		return *this;
	}

	_H3API_ BOOL H3String::Reserve(INT32 new_size)
	{
		return Realloc(new_size);
	}

	_H3API_ BOOL H3String::SetLength(INT32 len)
	{
		if (len > MaxLength())
			return Realloc(len);

		length = len;
		NullTerminate();
		return HS_SUCCESS;
	}

	_H3API_ VOID H3String::ShrinkToFit()
	{
		if (capacity == 0)
			return;
		int min_len = length + 2;
		if (min_len >= capacity)
			return;

		PCHAR tmp = (PCHAR)F_malloc(min_len);
		F_memcpy(tmp, str - 1, min_len);
		F_delete(str - 1);
		str = tmp - 1;
		capacity = min_len - 1;
	}

	_H3API_ H3String& H3String::Append(LPCSTR mes, INT32 len)
	{
		if (mes && len)
			return THISCALL_3(H3String&, 0x41B2A0, this, mes, len);
		return *this;
	}

	_H3API_ H3String& H3String::Append(const H3String&  other)
	{
		return Append(other.String(), other.Length());
	}

	_H3API_ H3String& H3String::Append(int number)
	{		
		int len = F_sprintf("%d", number);
		return Append(PCHAR(0x697428), len);
	}

	_H3API_ H3String& H3String::Append(unsigned int number)
	{		
		int len = F_sprintf("0x%X", number);
		return Append(PCHAR(0x697428), len);
	}

	_H3API_ H3String& H3String::Append(LPCSTR mes)
	{
		if (mes)
			return Append(mes, strlen(mes));
		return *this;
	}

	_H3API_ H3String& H3String::Append(CHAR ch)
	{
		if (ch == '\0')
			return *this;
		return Append(&ch, 1);
	}

	_H3API_ LPCSTR H3String::FindFirst(CHAR ch)
	{
		PCHAR f = Begin();
		int pos = 0;
		int len = Length();
		while (*f && pos < len)
		{
			if (*f == ch)
				return f;
			++f;
			++pos;
		}
		return nullptr;
	}

	_H3API_ LPCSTR H3String::FindFirst(LPCSTR substr) const
	{
		if (String())
			return strstr(String(), substr);
		return nullptr;
	}

	_H3API_ INT32 H3String::FindFirstOf(LPCSTR chars, INT32 num_chars) const
	{
		return CompareFirstOf(chars, num_chars, TRUE);
	}

	_H3API_ INT32 H3String::FindFirstOf(LPCSTR chars) const
	{
		return FindFirstOf(chars, strlen(chars));
	}

	_H3API_ INT32 H3String::FindFirstOf(const H3String& chars) const
	{
		return FindFirstOf(chars.String(), chars.Length());
	}

	_H3API_ INT32 H3String::FindFirstOf(const CHAR ch) const
	{
		return CompareFirstOf(&ch, 1, TRUE);
	}

	_H3API_ INT32 H3String::FindFirstNotOf(LPCSTR chars, INT32 num_chars) const
	{
		return CompareFirstOf(chars, num_chars, FALSE);
	}

	_H3API_ INT32 H3String::FindFirstNotOf(LPCSTR chars) const
	{
		return FindFirstNotOf(chars, strlen(chars));
	}

	_H3API_ INT32 H3String::FindFirstNotOf(const H3String& chars) const
	{
		return FindFirstNotOf(chars.String(), chars.Length());
	}

	_H3API_ INT32 H3String::FindFirstNotOf(const CHAR ch) const
	{
		return FindFirstNotOf(&ch, 1);
	}

	_H3API_ INT32 H3String::FindLastOf(LPCSTR chars, INT32 num_chars) const
	{
		return CompareLastOf(chars, num_chars, TRUE);
	}

	_H3API_ INT32 H3String::FindLastOf(LPCSTR chars) const
	{
		return CompareLastOf(chars, strlen(chars), TRUE);
	}

	_H3API_ INT32 H3String::FindLastOf(const H3String& chars) const
	{
		return CompareLastOf(chars.String(), chars.Length(), TRUE);
	}

	_H3API_ INT32 H3String::FindLastOf(const CHAR ch) const
	{
		return CompareLastOf(&ch, 1, TRUE);
	}

	_H3API_ INT32 H3String::FindLastNotOf(LPCSTR chars, INT32 num_chars) const
	{
		return CompareLastOf(chars, num_chars, FALSE);
	}

	_H3API_ INT32 H3String::FindLastNotOf(LPCSTR chars) const
	{
		return FindLastNotOf(chars, strlen(chars));
	}

	_H3API_ INT32 H3String::FindLastNotOf(const H3String& chars) const
	{
		return FindLastNotOf(chars.String(), chars.Length());
	}

	_H3API_ INT32 H3String::FindLastNotOf(const CHAR ch) const
	{
		return FindLastNotOf(&ch, 1);
	}

	_H3API_ H3String& H3String::Trim()
	{
		if (!str || !length)
			return *this;
		constexpr CHAR whitespace[] = { ' ', '\t' };
		int str_start = FindFirstNotOf(whitespace, 2);
		if (str_start > 0)
			Remove(0, str_start - 1);
		int str_end = FindLastNotOf(whitespace, 2);
		if (str_end >= 0)
			Remove(str_end + 1, Length());
		return *this;
	}

	_H3API_ PCHAR H3String::At(INT32 pos)
	{
		if (str && pos >= 0)
			return str + std::min(pos, Length());
		return nullptr;
	}

	_H3API_ CHAR H3String::GetCharAt(INT32 pos) const
	{
		if (str && pos >= 0 && Length())
			return str[std::min(pos, Length())];
		return 0;
	}

	_H3API_ INT32 H3String::Remove(CHAR ch)
	{
		if (!str || *str == 0) // no text or NULL string
			return HS_FAILED;

		const INT32 len = Length();
		INT32 l = Length() + 1;

		char* dst;
		for (char* src = dst = str; *src && --l; src++)
		{
			if (*src == ch) // skip over this char
			{
				--length;
				continue;
			}
			*dst = *src;
			++dst;
		}
		*dst = 0; // place end character

		return len - Length();
	}

	_H3API_ INT32 H3String::Remove(LPCSTR substr)
	{
		return Remove(substr, strlen(substr));
	}

	_H3API_ INT32 H3String::Remove(LPCSTR substr, INT32 sublen)
	{
		PCHAR s, copy_end;
		if (!String())
			return HS_FAILED;
		if (nullptr == (s = strstr(str, substr)))
			// no match
			return 0;
		INT rem = length;
		PCHAR copyFrom = s + sublen;
		while (nullptr != (copy_end = strstr(copyFrom, substr)))
		{
			memmove(s, copyFrom, copy_end - copyFrom);
			s += copy_end - copyFrom;
			copyFrom = copy_end + sublen;
		}
		memmove(s, copyFrom, 1 + strlen(copyFrom));
		length = strlen(str);
		return rem - length;
	}

	_H3API_ INT32 H3String::Remove(INT32 start, INT32 end)
	{
		if (!str)
			return HS_FAILED;
		end = std::min(end, length - 1);
		INT32 n = end - start + 1;
		if (n <= 0)
			return HS_FAILED;

		PCHAR dest = str + start;
		PCHAR src = dest + n;

		while (*src)
			*dest++ = *src++;

		length -= n;
		NullTerminate();
		return n;
	}

	_H3API_ BOOL H3String::Split(CHAR ch, H3String& out)
	{
		LPCSTR limiter = FindFirst(ch);
		if (!limiter)
			return FALSE;

		INT pos = INT(limiter - String());
		INT rem_len = Length() - pos - 1;
		// * if it's the last char of string, no split can occur...
		// * still we remove the found char
		if (rem_len <= 0)
		{
			Truncate(pos == 0 ? 0 : pos - 1);
			return FALSE;
		}

		out.Assign(limiter + 1, rem_len);
		Truncate(pos == 0 ? 0 : pos - 1);
		return TRUE;
	}

	_H3API_ VOID H3String::Erase()
	{
		F_memset(Begin(), 0, Length());
		length = 0;
	}

	_H3API_ BOOL H3String::Equals(LPCSTR msg, INT32 len) const
	{
		if (!msg || Length() != len)
			return FALSE;

		return memcmp(msg, String(), Length()) == 0;
	}

	_H3API_ BOOL H3String::Equals(LPCSTR msg) const
	{
		if (!msg)
			return HS_FAILED;
		return Equals(msg, strlen(msg));
	}

	_H3API_ BOOL H3String::Equals(H3String& other) const
	{
		return Equals(other.String(), other.Length());
	}

	_H3API_ BOOL H3String::Equals_i(LPCSTR msg, INT32 len) const
	{
		if (Length() != len)
			return FALSE;
		return (F_strcmpi(msg, String()) == 0);
	}

	_H3API_ BOOL H3String::Equals_i(LPCSTR msg) const
	{
		if (!msg)
			return HS_FAILED;
		return Equals_i(msg, strlen(msg));
	}

	_H3API_ BOOL H3String::Equals_i(const H3String& other) const
	{
		return Equals_i(other.String(), other.Length());
	}

	_H3API_ H3String& H3String::Insert(INT32 pos, LPCSTR msg, INT32 len)
	{
		if (len == 0 || msg == nullptr)
			return *this;
		// * trying to insert at or after end
		if (pos >= Length())
			return Append(msg, len);

		if (!Reserve(Length() + len))
			return *this;

		INT copylen = Length() - pos;
		// * simpler than malloc + free
		H3String temp;
		temp.Assign(str + pos, copylen);
		// * temporarily cut out
		Truncate(pos);
		// * insert msg
		Append(msg, len);
		// * insert original end
		Append(temp);

		return *this;
	}

	_H3API_ H3String& H3String::Insert(INT32 pos, LPCSTR msg)
	{
		if (msg)
			return Insert(pos, msg, strlen(msg));
		return *this;
	}

	_H3API_ H3String& H3String::Insert(INT32 pos, const H3String& to_insert)
	{
		return Insert(pos, to_insert.String(), to_insert.Length());
	}

	_H3API_ H3String& H3String::Insert(INT32 pos, CHAR ch)
	{
		return Insert(pos, &ch, 1);
	}

	_H3API_ INT H3String::Compare(LPCSTR other) const
	{
		return strcmp(String(), other);
	}

	_H3API_ BOOL H3String::Truncate(INT32 position)
	{
		if (position < Length() && String())
		{
			length = position;
			str[length] = 0;
		}
		return FALSE;
	}

	_H3API_ H3String& H3String::operator=(const H3String& other)
	{
		return Assign(other);
	}

	_H3API_ H3String& H3String::operator=(LPCSTR msg)
	{
		return Assign(msg);
	}

	_H3API_ H3String& H3String::operator=(CHAR ch)
	{
		return Assign(ch);
	}

#ifdef _CPLUSPLUS11_
	_H3API_ H3String& H3String::operator=(H3String&& other) noexcept
	{
		if (&other == this)
			return *this;

		str = other.str;
		length = other.length;
		capacity = other.capacity;
		other.Deref();

		return *this;
	}
#endif

	_H3API_ H3String& H3String::operator+=(const H3String& other)
	{
		return Append(other);
	}

	_H3API_ H3String& H3String::operator+=(LPCSTR msg)
	{
		return Append(msg);
	}

	_H3API_ H3String& H3String::operator+=(CHAR ch)
	{
		return Append(ch);
	}

	_H3API_ H3String& H3String::operator+=(const int number)
	{
		return Append(number);
	}

	_H3API_ H3String& H3String::operator+=(const unsigned int number)
	{
		return Append(number);
	}

	_H3API_ H3String& H3String::operator<<(CHAR ch)
	{
		return Append(ch);
	}

	_H3API_ H3String& H3String::operator<<(LPCSTR msg)
	{
		return Append(msg);
	}

	_H3API_ H3String& H3String::operator<<(H3String& other)
	{
		return Append(other);
	}

	_H3API_ H3String& H3String::operator<<(const int number)
	{
		return Append(number);
	}

	_H3API_ H3String& H3String::operator<<(const unsigned int number)
	{
		return Append(number);
	}

	_H3API_ H3String::operator LPCSTR() const
	{
		return String();
	}

	_H3API_ INT H3String::operator==(const H3String& h3str) const
	{
		return Compare(h3str);
	}

	_H3API_ INT H3String::operator==(LPCSTR str) const
	{
		return Compare(str);
	}

	_H3API_ CHAR H3String::operator[](INT32 pos) const
	{
	#ifdef _H3API_SAFE_
		if (!str)
			return 0;
		if (pos < 0)
			return str[0];
		if (pos > Length())
			return str[Length() - 1];
	#endif
		return str[pos];
	}

	_H3API_ INT8 H3String::References() const
	{
	#ifdef _H3API_SAFE_
		if (!str)
			return HS_NOTFOUND;
	#endif
		return str[-1];
	}

	_H3API_ VOID H3String::IncreaseReferences()
	{
	#ifdef _H3API_SAFE_
		if (!str)
			return;
	#endif
		++str[-1];
	}

	_H3API_ BOOL H3String::FormattedNumber(int number)
	{
		if (!str && !Reserve())
			return FALSE;
		length = H3Numbers::AddCommas(number, str);

		return TRUE;
	}

	_H3API_ BOOL H3String::ScaledNumber(int number, int decimals)
	{
		if (!str && !Reserve())
			return FALSE;
		length = H3Numbers::MakeReadable(number, str, decimals);
		return TRUE;
	}

#ifndef _CPLUSPLUS11_
	_H3API_ H3String& H3String::Printf(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		int len = _snprintf(nullptr, 0, format, args);
		if (len > 0 && Reserve(len + 1))
		{
			len = F_vsprintf(Begin(), format, args);
			Truncate(len);
		}
		va_end(args);
		return *this;
	}

	_H3API_ H3String& H3String::PrintfAppend(LPCSTR format, ...)
	{
		H3String appendme;
		va_list args;
		va_start(args, format);
		int len = _snprintf(nullptr, 0, format, args);
		if (len > 0 && appendme.Reserve(len + 1))
		{
			len = F_vsprintf(appendme.Begin(), format, args);
			appendme.Truncate(len);
		}
		va_end(args);
		Append(appendme);
		return *this;
	}
#endif

#ifdef _H3_STD_CONVERSIONS_
	_H3API_ H3String::H3String(const std::string& str) :
		str(nullptr),
		length(0),
		capacity(0)
	{
		Assign(str);
	}

	_H3API_ INT H3String::operator==(const std::string& str) const
	{
		return Compare(str.c_str());
	}
	_H3API_ H3String& H3String::operator+=(const std::string& str)
	{
		return Append(str);
	}
	_H3API_ H3String& H3String::operator=(const std::string& str)
	{
		return Assign(str);
	}
	_H3API_ H3String& H3String::Assign(const std::string& str)
	{
		return Assign(str.c_str(), str.length());
	}
	_H3API_ H3String& H3String::Append(const std::string& str)
	{
		Append(str.c_str(), str.length());
		return *this;
	}
	_H3API_ std::string H3String::to_std_string() const
	{
		return std::string(String(), Length());
	}
#endif
}