//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3String.hpp"
#include "H3String.inl"

namespace h3
{
	_H3API_ VOID H3String::Deref()
	{
		m_string = nullptr;
		m_length = 0;
		m_capacity = 0;
	}
	_H3API_ VOID H3String::NullTerminate()
	{
		*End() = 0;
	}
	_H3API_ BOOL H3String::Realloc(UINT new_size)
	{
		return THISCALL_2(BOOL, 0x404B80, this, new_size);
	}
	_H3API_ VOID H3String::ClearUnused()
	{
		const UINT to_clear = m_capacity - m_length;
		F_memset(PVOID(m_string + m_length), 0, to_clear);
	}
	_H3API_ BOOL H3String::CompareChars(LPCSTR chars, UINT num_chars, UINT pos, BOOL is_true) const
	{
		for (UINT i = 0; i < num_chars; ++i)
			if (m_string[pos] == chars[i])
				return is_true;

		return !is_true;
	}
	_H3API_ UINT H3String::CompareFirstOf(LPCSTR chars, UINT num_chars, BOOL is_true) const
	{
		if (Empty())
			return npos;

		for (UINT i = 0; i < m_length; ++i)
			if (CompareChars(chars, num_chars, i, is_true))
				return i;
		return npos;
	}

	_H3API_ UINT H3String::CompareLastOf(LPCSTR chars, UINT num_chars, BOOL is_true) const
	{
		if (!m_string || !m_length)
			return npos;

		for (UINT i = m_length; i > 0; --i)
			if (CompareChars(chars, num_chars, i - 1, is_true))
				return i - 1;
		return npos;
	}

	_H3API_ H3String::H3String() :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
	}

	_H3API_ H3String::H3String(LPCSTR msg) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
		Assign(msg);
	}

	_H3API_ H3String::H3String(LPCSTR msg, UINT len) :
		m_string(),
		m_length(0),
		m_capacity(0)
	{
		Assign(msg, len);
	}

	_H3API_ H3String::H3String(const H3String& other) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
		Assign(other);
	}
	_H3API_ H3String::H3String(CHAR ch) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
		Assign(ch);
	}

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3String::H3String(H3String&& other) noexcept :
		m_string(other.m_string),
		m_length(other.m_length),
		m_capacity(other.m_capacity)
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

	_H3API_ BOOL H3String::Empty() const
	{
		if (m_string == nullptr || m_length == 0)
			return TRUE;
		return FALSE;
	}

	_H3API_ UINT H3String::Length() const
	{
		return m_length;
	}

	_H3API_ UINT H3String::MaxLength() const
	{
		return m_capacity;
	}

	_H3API_ LPCSTR H3String::String() const
	{
		return m_string;
	}

	_H3API_ CHAR* H3String::begin()
	{
		return m_string;
	}

	_H3API_ CHAR* H3String::end()
	{
		return m_string + m_length;
	}

	_H3API_ VOID H3String::swap(H3String& other)
	{
		PCHAR s          = m_string;
		UINT l           = m_length;
		UINT c           = m_capacity;
		m_string         = other.m_string;
		m_length         = other.m_length;
		m_capacity       = other.m_capacity;
		other.m_string   = s;
		other.m_length   = l;
		other.m_capacity = c;
	}

	_H3API_ PCHAR H3String::Begin()
	{
		return m_string;
	}

	_H3API_ PCHAR H3String::End()
	{
		return m_string + m_length;
	}

	_H3API_ CHAR H3String::Last() const
	{
		return m_string[m_length - 1];
	}

	_H3API_ H3String& H3String::Assign(LPCSTR mes, UINT len)
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
		char buffer[16]; // more than enough considering number can only be 12 digits [-1234567890\0]
		int len = F_sprintfbuffer(buffer, "%d", number);
		Assign(buffer, UINT(len));
		return *this;
	}

	_H3API_ BOOL H3String::Reserve(UINT new_size)
	{
		return Realloc(new_size);
	}

	_H3API_ BOOL H3String::SetLength(UINT len)
	{
		if (len > m_capacity)
			return Realloc(len);

		m_length = len;
		NullTerminate();
		return TRUE;
	}

	_H3API_ VOID H3String::ShrinkToFit()
	{
		if (m_capacity == 0)
			return;
		UINT min_len = m_length + 2;
		if (min_len >= m_capacity)
			return;

		PCHAR tmp = (PCHAR)F_malloc(min_len);
		F_memcpy(tmp, m_string - 1, min_len);
		F_delete(m_string - 1);
		m_string = tmp - 1;
		m_capacity = min_len - 1;
	}

	_H3API_ H3String& H3String::Append(LPCSTR mes, UINT len)
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
		char buffer[16]; // more than enough considering number can only be 12 digits [-1234567890\0]
		const int len = F_sprintfbuffer(buffer, "%d", number);
		Assign(buffer, len);
		return Append(buffer, UINT(len));
	}

	_H3API_ H3String& H3String::Append(unsigned int number)
	{
		char buffer[16]; // more than enough considering number can only be 13 digits [0x1234567890\0]
		const int len = F_sprintfbuffer(buffer, "0x%X", number);
		return Append(buffer, UINT(len));
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
		UINT pos = 0;
		UINT len = Length();
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

	_H3API_ UINT H3String::FindFirstOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareFirstOf(chars, num_chars, TRUE);
	}

	_H3API_ UINT H3String::FindFirstOf(LPCSTR chars) const
	{
		return FindFirstOf(chars, strlen(chars));
	}

	_H3API_ UINT H3String::FindFirstOf(const H3String& chars) const
	{
		return FindFirstOf(chars.String(), chars.Length());
	}

	_H3API_ UINT H3String::FindFirstOf(const CHAR ch) const
	{
		return CompareFirstOf(&ch, 1, TRUE);
	}

	_H3API_ UINT H3String::FindFirstNotOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareFirstOf(chars, num_chars, FALSE);
	}

	_H3API_ UINT H3String::FindFirstNotOf(LPCSTR chars) const
	{
		return FindFirstNotOf(chars, strlen(chars));
	}

	_H3API_ UINT H3String::FindFirstNotOf(const H3String& chars) const
	{
		return FindFirstNotOf(chars.String(), chars.Length());
	}

	_H3API_ UINT H3String::FindFirstNotOf(const CHAR ch) const
	{
		return FindFirstNotOf(&ch, 1);
	}

	_H3API_ UINT H3String::FindLastOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareLastOf(chars, num_chars, TRUE);
	}

	_H3API_ UINT H3String::FindLastOf(LPCSTR chars) const
	{
		return CompareLastOf(chars, strlen(chars), TRUE);
	}

	_H3API_ UINT H3String::FindLastOf(const H3String& chars) const
	{
		return CompareLastOf(chars.String(), chars.Length(), TRUE);
	}

	_H3API_ UINT H3String::FindLastOf(const CHAR ch) const
	{
		return CompareLastOf(&ch, 1, TRUE);
	}

	_H3API_ UINT H3String::FindLastNotOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareLastOf(chars, num_chars, FALSE);
	}

	_H3API_ UINT H3String::FindLastNotOf(LPCSTR chars) const
	{
		return FindLastNotOf(chars, strlen(chars));
	}

	_H3API_ UINT H3String::FindLastNotOf(const H3String& chars) const
	{
		return FindLastNotOf(chars.String(), chars.Length());
	}

	_H3API_ UINT H3String::FindLastNotOf(const CHAR ch) const
	{
		return FindLastNotOf(&ch, 1);
	}

	_H3API_ H3String& H3String::Trim()
	{
		if (!m_string || !m_length)
			return *this;
		constexpr CHAR whitespace[] = { ' ', '\t' };
		UINT str_start = FindFirstNotOf(whitespace, 2);
		if (str_start != npos)
			Erase(0, str_start);
		UINT str_end = FindLastNotOf(whitespace, 2);
		if (str_end != npos)
			Erase(str_end + 1, npos);
		return *this;
	}

	_H3API_ PCHAR H3String::At(UINT pos)
	{
		if (m_string && pos >= 0)
			return m_string + std::min(pos, Length());
		return nullptr;
	}

	_H3API_ CHAR H3String::GetCharAt(UINT pos) const
	{
		if (m_string && pos >= 0 && Length())
			return m_string[std::min(pos, Length())];
		return 0;
	}

	_H3API_ H3String& H3String::Remove(CHAR ch)
	{
		return Remove(&ch, 1);
	}

	_H3API_ H3String& H3String::Remove(LPCSTR substr)
	{
		return Remove(substr, strlen(substr));
	}

	_H3API_ H3String& H3String::Remove(LPCSTR substr, UINT sublen)
	{
		PCHAR s, copy_end;
		if (!String())
			return *this;
		if (nullptr == (s = strstr(m_string, substr)))
			// no match
			return *this;

		PCHAR copyFrom = s + sublen;
		while (nullptr != (copy_end = strstr(copyFrom, substr)))
		{
			memmove(s, copyFrom, copy_end - copyFrom);
			s += copy_end - copyFrom;
			copyFrom = copy_end + sublen;
		}
		memmove(s, copyFrom, 1 + strlen(copyFrom));
		m_length = strlen(m_string);
		return *this;
	}

	_H3API_ H3String& H3String::Remove(UINT start, UINT end)
	{
		return Erase(start, end);
	}

	_H3API_ H3String & H3String::Erase(UINT pos)
	{
		return Erase(pos, pos + 1);
	}

	_H3API_ H3String & H3String::Erase(UINT first, UINT last)
	{
		if (first > m_length || first >= last)
			return *this;
		if (last > m_length)
		{
			Truncate(first);
			return *this;
		}

		PCHAR dst = begin() + first;
		PCHAR src = begin() + last;
		UINT  len = Length() - last; // copy length
		for (UINT i = 0; i < len; ++i)
			dst[i] = src[i];

		m_length -= last - first;
		m_string[m_length] = 0;

		return *this;
	}

	_H3API_ H3String & H3String::Erase(PCHAR first, PCHAR last)
	{
		return Erase(UINT(first - begin()), UINT(last - begin()));
	}

	_H3API_ BOOL H3String::Split(CHAR ch, H3String& out)
	{
		UINT pos = FindFirstOf(ch);
		if (pos == npos)
			return FALSE;
		if (pos == Length() - 1)
		{
			// split would not give anything in out
			Truncate(pos);
			return TRUE;
		}

		out.Assign(begin() + pos + 1, Length() - pos - 1);
		Truncate(pos);
		return TRUE;
	}

	_H3API_ VOID H3String::Erase()
	{
		F_memset(Begin(), 0, Length());
		m_length = 0;
	}

	_H3API_ BOOL H3String::Equals(LPCSTR msg, UINT len) const
	{
		if (!msg || Length() != len)
			return FALSE;

		return memcmp(msg, String(), Length()) == 0;
	}

	_H3API_ BOOL H3String::Equals(LPCSTR msg) const
	{
		if (!msg)
			return npos;
		return Equals(msg, strlen(msg));
	}

	_H3API_ BOOL H3String::Equals(const H3String& other) const
	{
		return Equals(other.String(), other.Length());
	}

	_H3API_ BOOL H3String::Equals_i(LPCSTR msg, UINT len) const
	{
		if (Length() != len)
			return FALSE;
		return (F_strcmpi(msg, String()) == 0);
	}

	_H3API_ BOOL H3String::Equals_i(LPCSTR msg) const
	{
		if (!msg)
			return npos;
		return Equals_i(msg, strlen(msg));
	}

	_H3API_ BOOL H3String::Equals_i(const H3String& other) const
	{
		return Equals_i(other.String(), other.Length());
	}

	_H3API_ H3String& H3String::Insert(UINT pos, LPCSTR msg, UINT len)
	{
		if (len == 0 || msg == nullptr)
			return *this;
		// * trying to insert at or after end
		if (pos >= Length())
			return Append(msg, len);

		if (!Reserve(Length() + len))
			return *this;

		UINT copylen = Length() - pos;
		// * simpler than malloc + free
		H3String temp;
		temp.Assign(m_string + pos, copylen);
		// * temporarily cut out
		Truncate(pos);
		// * insert msg
		Append(msg, len);
		// * insert original end
		Append(temp);

		return *this;
	}

	_H3API_ H3String& H3String::Insert(UINT pos, LPCSTR msg)
	{
		if (msg)
			return Insert(pos, msg, strlen(msg));
		return *this;
	}

	_H3API_ H3String& H3String::Insert(UINT pos, const H3String& to_insert)
	{
		return Insert(pos, to_insert.String(), to_insert.Length());
	}

	_H3API_ H3String& H3String::Insert(UINT pos, CHAR ch)
	{
		return Insert(pos, &ch, 1);
	}

	_H3API_ INT H3String::Compare(LPCSTR other) const
	{
		return strcmp(String(), other);
	}

	_H3API_ INT H3String::Compare(const H3String & other) const
	{
		return Compare(other.String());
	}

	_H3API_ INT H3String::Comparei(LPCSTR other) const
	{
		return F_strcmpi(String(), other);
	}

	_H3API_ INT H3String::Comparei(const H3String & other) const
	{
		return F_strcmpi(String(), other.String());
	}

	_H3API_ BOOL H3String::operator<(const H3String& other) const
	{
		return strcmp(String(), other.String()) < 0;
	}

	_H3API_ BOOL H3String::Truncate(UINT position)
	{
		if (position == npos)
			return FALSE;
		if (position < Length() && String())
		{
			m_length = position;
			m_string[m_length] = 0;
			return TRUE;
		}
		return FALSE;
	}
	_H3API_ UINT H3String::Occurrences(CHAR ch) const
	{
		if (Empty())
			return 0;
		UINT n = 0;
		for (UINT i = 0; i < m_length; ++i)
			if (m_string[i] == ch)
				++n;
		return n;
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

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3String& H3String::operator=(H3String&& other) noexcept
	{
		if (&other == this)
			return *this;

		m_string   = other.m_string;
		m_length   = other.m_length;
		m_capacity = other.m_capacity;
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

	_H3API_ BOOL H3String::operator==(const H3String& h3str) const
	{
		return Compare(h3str.String()) == 0;
	}

	_H3API_ BOOL H3String::operator==(LPCSTR str) const
	{
		return Compare(str) == 0;
	}
	_H3API_ BOOL H3String::operator!=(const H3String& h3str) const
	{
		return Compare(h3str.String()) != 0;
	}

	_H3API_ BOOL H3String::operator!=(LPCSTR str) const
	{
		return Compare(str) != 0;
	}

	_H3API_ CHAR& H3String::operator[](UINT32 pos) const
	{
		return m_string[pos];
	}
	_H3API_ CHAR& H3String::operator[](UINT32 pos)
	{
		return m_string[pos];
	}

	_H3API_ INT8 H3String::References() const
	{
	#ifdef _H3API_SAFE_
		if (!m_string)
			return HS_NOTFOUND;
	#endif
		return m_string[-1];
	}

	_H3API_ VOID H3String::IncreaseReferences()
	{
	#ifdef _H3API_SAFE_
		if (!m_string)
			return;
	#endif
		++m_string[-1];
	}

	_H3API_ BOOL H3String::FormattedNumber(int number)
	{
		if (!m_string && !Reserve())
			return FALSE;
		m_length = H3Numbers::AddCommas(number, m_string);

		return TRUE;
	}

	_H3API_ BOOL H3String::ScaledNumber(int number, int decimals)
	{
		if (!m_string && !Reserve())
			return FALSE;
		m_length = H3Numbers::MakeReadable(number, m_string, decimals);
		return TRUE;
	}

	_H3API_ H3String H3String::PrintfH3(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		CDECL_3(void, 0x6190DE, 0x69971C, format, args);
		va_end(args);
		return H3String(PCHAR(0x69971C));
	}

	_H3API_ H3String & H3String::PrintfAppendH3(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		CDECL_3(void, 0x6190DE, 0x69971C, format, args);
		va_end(args);
		return Append(PCHAR(0x69971C));
	}

#ifndef _H3API_CPLUSPLUS11_

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

#ifdef _H3API_STD_CONVERSIONS_
	_H3API_ H3String::H3String(const std::string& str) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
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
#endif /* _H3API_STD_CONVERSIONS_ */
}