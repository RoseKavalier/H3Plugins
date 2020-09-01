//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STRING_HPP_
#define _H3STRING_HPP_

#include "../H3_Base.hpp"

#ifdef _H3API_STD_CONVERSIONS_
#include <string>
#endif

namespace h3
{
#pragma pack(push, 4)
	// * a string following the H3 format
	struct H3String
	{
	protected:
		h3unk8 _allocator; // useless
		PCHAR  m_string;
		UINT32 m_length;
		UINT32 m_capacity;

		_H3API_ VOID Deref();
		_H3API_ VOID NullTerminate();
		_H3API_ BOOL Realloc(UINT new_size);
		_H3API_ VOID ClearUnused();
		_H3API_ BOOL CompareChars(LPCSTR chars, UINT num_chars, UINT pos, BOOL is_true) const;
		_H3API_ UINT CompareFirstOf(LPCSTR chars, UINT num_chars, BOOL is_true) const;
		_H3API_ UINT CompareLastOf(LPCSTR chars, UINT num_chars, BOOL is_true) const;
	public:
		_H3API_ H3String();
		_H3API_ H3String(LPCSTR msg);
		_H3API_ H3String(LPCSTR msg, UINT len);
		_H3API_ H3String(const H3String& other);
		_H3API_ H3String(CHAR ch);
	#ifdef _H3API_CPLUSPLUS11_
		_H3API_ H3String(H3String&& other) noexcept;
	#endif

		_H3API_ ~H3String();

		// * H3 constructor
		_H3API_ VOID Init();
		// * H3 destructor
		_H3API_ VOID Dereference();

		_H3API_ BOOL Empty() const;

		// * current length of string
		_H3API_ UINT Length() const;
		// * capacity of string
		_H3API_ UINT MaxLength() const;
		// * returns constant char* string
		_H3API_ LPCSTR String() const;

		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_H3API_ CHAR* begin();
		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_H3API_ CHAR* end();

		_H3API_ VOID swap(H3String& other);

		// * returns beginning of string
		// * modifiable contrary to String()
		_H3API_ PCHAR Begin();
		// * returns end of string, on null char
		_H3API_ PCHAR End();

		// * returns the last char of string
		_H3API_ CHAR Last() const;

		// * sets string as mes

		_H3API_ H3String& Assign(LPCSTR mes, UINT len);
		_H3API_ H3String& Assign(LPCSTR mes);
		template<UINT Sz>
		inline H3String& AssignA(const CHAR(&buffer)[Sz]);
		_H3API_ H3String& Assign(CHAR ch);
		_H3API_ H3String& Assign(const H3String &other);
		_H3API_ H3String& Assign(INT32 number);

		// * sets new capacity, 0x1F is default
		_H3API_ BOOL Reserve(UINT new_size = 0x1E);
		// * Sets capacity if larger, otherwise shortens
		_H3API_ BOOL SetLength(UINT len);
		// * reduces buffer capacity to length + 1
		_H3API_ VOID ShrinkToFit();

		// * Adds mes to end of string

		_H3API_ H3String& Append(LPCSTR mes, UINT len);
		template<UINT Sz>
		inline H3String& AppendA(const CHAR (&buffer)[Sz]);
		_H3API_ H3String& Append(const H3String & other);
		_H3API_ H3String& Append(int number);
		_H3API_ H3String& Append(unsigned int number);
		_H3API_ H3String& Append(LPCSTR mes);
		_H3API_ H3String& Append(CHAR ch);

		// * Finds position of first ch
		_H3API_ LPCSTR FindFirst(CHAR ch);
		// * Finds position of first substring
		_H3API_ LPCSTR FindFirst(LPCSTR substr) const;

		_H3API_ UINT FindFirstOf(LPCSTR chars, UINT num_chars) const;
		_H3API_ UINT FindFirstOf(LPCSTR chars) const;
		_H3API_ UINT FindFirstOf(const H3String& chars) const;
		_H3API_ UINT FindFirstOf(const CHAR ch) const;

		_H3API_ UINT FindFirstNotOf(LPCSTR chars, UINT num_chars) const;
		_H3API_ UINT FindFirstNotOf(LPCSTR chars) const;
		_H3API_ UINT FindFirstNotOf(const H3String& chars) const;
		_H3API_ UINT FindFirstNotOf(const CHAR ch) const;

		_H3API_ UINT FindLastOf(LPCSTR chars, UINT num_chars) const;
		_H3API_ UINT FindLastOf(LPCSTR chars) const;
		_H3API_ UINT FindLastOf(const H3String& chars) const;
		_H3API_ UINT FindLastOf(const CHAR ch) const;

		_H3API_ UINT FindLastNotOf(LPCSTR chars, UINT num_chars) const;
		_H3API_ UINT FindLastNotOf(LPCSTR chars) const;
		_H3API_ UINT FindLastNotOf(const H3String& chars) const;
		_H3API_ UINT FindLastNotOf(const CHAR ch) const;

		// * removes leading and trailing whitespace ' ' and '\t'
		_H3API_ H3String& Trim();

		// * returns string offset at pos
		_H3API_ PCHAR At(UINT pos);
		_H3API_ CHAR GetCharAt(UINT pos) const;

		// * Removes all instances of string

		_H3API_ H3String& Remove(CHAR ch);
		_H3API_ H3String& Remove(LPCSTR substr);
		_H3API_ H3String& Remove(LPCSTR substr, UINT sublen);
		// * Remove chars from start to end - inclusively!
		_H3API_ H3String& Remove(UINT start, UINT end);
		// * removes character at position
		_H3API_ H3String& Erase(UINT pos);
		// * removes characters from [first, last)
		_H3API_ H3String& Erase(UINT first, UINT last);
		// * removes characters from [first, last)
		_H3API_ H3String& Erase(PCHAR first, PCHAR last);

		// * Splits a string on a given char
		// * The character is removed
		// * the original string is truncated
		// * The outgoing string gets the remainder
		// * of the original string
		_H3API_ BOOL Split(CHAR ch, H3String& out);

		// * sets string to all 0s
		_H3API_ VOID Erase();

		// * memcmp ~ case sensitive
		_H3API_ BOOL Equals(LPCSTR msg, UINT len) const;
		_H3API_ BOOL Equals(LPCSTR msg) const;
		_H3API_ BOOL Equals(const H3String& other) const;

		// * strcmpi ~ not case-sensitive
		_H3API_ BOOL Equals_i(LPCSTR msg, UINT len) const;
		_H3API_ BOOL Equals_i(LPCSTR msg) const;
		_H3API_ BOOL Equals_i(const H3String& other) const;

		// * Inserts string within h3string at position
		_H3API_ H3String& Insert(UINT pos, LPCSTR msg, UINT len);
		_H3API_ H3String& Insert(UINT pos, LPCSTR msg);
		_H3API_ H3String& Insert(UINT pos, const H3String& to_insert);
		_H3API_ H3String& Insert(UINT pos, CHAR ch);

		_H3API_ INT Compare(LPCSTR other) const;
		_H3API_ INT Compare(const H3String& other) const;
		// * compare case insensitive
		_H3API_ INT Comparei(LPCSTR other) const;
		_H3API_ INT Comparei(const H3String& other) const;

		_H3API_ BOOL operator<(const H3String& other) const;

		// * Ends string at position
		_H3API_ BOOL Truncate(UINT position);

		// * counts number of times a character shows up
		_H3API_ UINT Occurrences(CHAR ch) const;

		// * Assigns string to current

		_H3API_ H3String& operator=(const H3String& other);
		_H3API_ H3String& operator=(LPCSTR msg);
		_H3API_ H3String& operator=(CHAR ch);

	#ifdef _H3API_CPLUSPLUS11_
		_H3API_ H3String& operator=(H3String&& other) noexcept;
	#endif

		// * Appends to string

		_H3API_ H3String& operator+=(const H3String& other);
		_H3API_ H3String& operator+=(LPCSTR msg);
		_H3API_ H3String& operator+=(CHAR ch);
		_H3API_ H3String& operator+=(const int number);
		// * Adds hex number to string
		_H3API_ H3String& operator+=(const unsigned int number);

		// * Compare using strcmp

		_H3API_ BOOL operator==(const H3String& h3str) const;
		_H3API_ BOOL operator==(LPCSTR str) const;
		_H3API_ BOOL operator!=(const H3String& h3str) const;
		_H3API_ BOOL operator!=(LPCSTR str) const;

		// * Returns char at offset
		_H3API_ CHAR& operator[](UINT32 pos) const;
		_H3API_ CHAR& operator[](UINT32 pos);

		// * The number of times this string is referenced - avoids deletion from destructor in references
		_H3API_ INT8 References() const;

		// * Increase the number of references to this string
		_H3API_ VOID IncreaseReferences();

		// * assigns a number with commas to a string
		_H3API_ BOOL FormattedNumber(int number);

		// * assigns a scaled number with k, M or B index and number of decimals
		_H3API_ BOOL ScaledNumber(int number, int decimals = 1);

		// * use sprintf with H3 assets, buffer limit 512 chars
		static _H3API_ H3String PrintfH3(LPCSTR format, ...);

		// * use sprintf on a H3String, appending the result to the end
		// * uses H3 assets, buffer limit 512 chars
		_H3API_ H3String& PrintfAppendH3(LPCSTR format, ...);

	#ifdef _H3API_CPLUSPLUS11_
		// * use sprintf on a H3String directly
		template<typename ... Args>
		inline H3String& Printf(LPCSTR format, Args ... args);
		// * use sprintf on a H3String, appending the result to the end
		template<typename ... Args>
		inline H3String& PrintfAppend(LPCSTR format, Args ... args);
	#else // non c++11 versions
		// * use sprintf on a H3String directly
		_H3API_ H3String& Printf(LPCSTR format, ...);
		// * use sprintf on a H3String, appending the result to the end
		_H3API_ H3String& PrintfAppend(LPCSTR format, ...);
	#endif

	#ifdef _H3API_STD_CONVERSIONS_
		_H3API_ H3String(const std::string& str);
		_H3API_ INT operator==(const std::string& str) const;
		_H3API_ H3String& operator+=(const std::string& str);
		_H3API_ H3String& operator=(const std::string& str);
		_H3API_ H3String& Assign(const std::string& str);
		_H3API_ H3String& Append(const std::string& str);
		_H3API_ std::string to_std_string() const;
	#endif /* _H3API_STD_CONVERSIONS_ */

		/*
		*
		* Non-member functions
		*
		*/

		// * Adds two H3String into one H3String
		friend inline H3String operator+(H3String& lhs, H3String& rhs);
		// * Adds H3String and char into one H3String
		friend inline H3String operator+(H3String& lhs, CHAR rhs);
		// * Adds one char and H3String into one H3String
		friend inline H3String operator+(CHAR lhs, H3String& rhs);
		// * Adds one H3String and char* into one H3String
		friend inline H3String operator+(H3String& lhs, LPCSTR rhs);
		// * Adds one char* and H3String into one H3String
		friend inline H3String operator+(LPCSTR lhs, H3String& rhs);

		// * these enum values follow std::string naming convention
		enum eH3String : UINT
		{
			max_len     = static_cast<UINT>(-3),
			npos        = static_cast<UINT>(-1),
		};
	};
	_H3API_ASSERT_SIZE_(H3String, 16);
#pragma pack(pop)
}

#endif /* #define _H3STRING_HPP_ */