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

#ifndef _H3STRING_HPP_
#define _H3STRING_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

#ifdef _H3_STD_CONVERSIONS_
#include <string>
#endif

namespace h3
{
#pragma pack(push, 1)
	// * a string following the H3 format
	struct H3String
	{
	protected:
		BOOL8 _init; // useless
		h3align _f_01[3];
		PCHAR str;
		INT32 length;
		INT32 capacity;
				
		_H3API_ VOID Deref();
		_H3API_ VOID NullTerminate();
		_H3API_ BOOL Realloc(int new_size);
		_H3API_ VOID ClearUnused();
		_H3API_ BOOL CompareChars(LPCSTR chars, INT32 num_chars, INT32 pos, BOOL is_true) const;
		_H3API_ INT32 CompareFirstOf(LPCSTR chars, INT32 num_chars, BOOL is_true) const;
		_H3API_ INT32 CompareLastOf(LPCSTR chars, INT32 num_chars, BOOL is_true) const;
	public:
		_H3API_ H3String();
		_H3API_ H3String(LPCSTR msg);
		_H3API_ H3String(LPCSTR msg, INT32 len);
		_H3API_ H3String(const H3String& other);
		_H3API_ H3String(CHAR ch);
	#ifdef _CPLUSPLUS11_
		_H3API_ H3String(H3String&& other) noexcept;
	#endif

		_H3API_ ~H3String();

		// * H3 constructor
		_H3API_ VOID Init();
		// * H3 destructor
		_H3API_ VOID Dereference();

		_H3API_ BOOL Empty() const;

		// * current length of string
		_H3API_ INT32 Length() const;
		// * capacity of string
		_H3API_ INT32 MaxLength() const;
		// * returns constant char* string
		_H3API_ LPCSTR String() const;

		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_H3API_ CHAR* begin();
		// * this is used in combination of C++11 'for :' range-based for loop iterator operations
		_H3API_ CHAR* end();

		// * returns beginning of string
		// * modifiable contrary to String()
		_H3API_ PCHAR Begin();
		// * returns end of string, on null char
		_H3API_ PCHAR End();

		// * returns the last char of string
		_H3API_ CHAR Last() const;

		// * sets string as mes

		_H3API_ H3String& Assign(LPCSTR mes, INT32 len);
		_H3API_ H3String& Assign(LPCSTR mes);
		_H3API_ H3String& Assign(CHAR ch);
		_H3API_ H3String& Assign(const H3String &other);
		_H3API_ H3String& Assign(INT32 number);

		// * sets new capacity, 0x1F is default
		_H3API_ BOOL Reserve(INT32 new_size = 0x1E);
		// * Sets capacity if larger, otherwise shortens
		_H3API_ BOOL SetLength(INT32 len);
		// * reduces buffer capacity to length + 1
		_H3API_ VOID ShrinkToFit();

		// * Adds mes to end of string

		_H3API_ H3String& Append(LPCSTR mes, INT32 len);
		template<INT32 Sz>
		H3String& Append(const CHAR (&buffer)[Sz]);
		_H3API_ H3String& Append(const H3String & other);
		_H3API_ H3String& Append(int number);
		_H3API_ H3String& Append(unsigned int number);
		_H3API_ H3String& Append(LPCSTR mes);
		_H3API_ H3String& Append(CHAR ch);

		// * Finds position of first ch
		_H3API_ LPCSTR FindFirst(CHAR ch);
		// * Finds position of first substring
		_H3API_ LPCSTR FindFirst(LPCSTR substr) const;

		_H3API_ INT32 FindFirstOf(LPCSTR chars, INT32 num_chars) const;
		_H3API_ INT32 FindFirstOf(LPCSTR chars) const;
		_H3API_ INT32 FindFirstOf(const H3String& chars) const;
		_H3API_ INT32 FindFirstOf(const CHAR ch) const;

		_H3API_ INT32 FindFirstNotOf(LPCSTR chars, INT32 num_chars) const;
		_H3API_ INT32 FindFirstNotOf(LPCSTR chars) const;
		_H3API_ INT32 FindFirstNotOf(const H3String& chars) const;
		_H3API_ INT32 FindFirstNotOf(const CHAR ch) const;

		_H3API_ INT32 FindLastOf(LPCSTR chars, INT32 num_chars) const;
		_H3API_ INT32 FindLastOf(LPCSTR chars) const;
		_H3API_ INT32 FindLastOf(const H3String& chars) const;
		_H3API_ INT32 FindLastOf(const CHAR ch) const;

		_H3API_ INT32 FindLastNotOf(LPCSTR chars, INT32 num_chars) const;
		_H3API_ INT32 FindLastNotOf(LPCSTR chars) const;
		_H3API_ INT32 FindLastNotOf(const H3String& chars) const;
		_H3API_ INT32 FindLastNotOf(const CHAR ch) const;

		// * removes leading and trailing whitespace ' ' and '\t'
		_H3API_ H3String& Trim();

		// * returns string offset at pos
		_H3API_ PCHAR At(INT32 pos);
		_H3API_ CHAR GetCharAt(INT32 pos) const;

		// * Removes all instances of string

		_H3API_ INT32 Remove(CHAR ch);
		_H3API_ INT32 Remove(LPCSTR substr);
		_H3API_ INT32 Remove(LPCSTR substr, INT32 sublen);
		// * Remove chars from start to end - inclusively!
		_H3API_ INT32 Remove(INT32 start, INT32 end);

		// * Splits a string on a given char
		// * The character is removed
		// * the original string is truncated
		// * The outgoing string gets the remainder
		// * of the original string
		_H3API_ BOOL Split(CHAR ch, H3String& out);

		// * sets string to all 0s
		_H3API_ VOID Erase();

		// * memcmp ~ case sensitive
		_H3API_ BOOL Equals(LPCSTR msg, INT32 len) const;
		_H3API_ BOOL Equals(LPCSTR msg) const;
		_H3API_ BOOL Equals(H3String& other) const;

		// * strcmpi ~ not case-sensitive
		_H3API_ BOOL Equals_i(LPCSTR msg, INT32 len) const;
		_H3API_ BOOL Equals_i(LPCSTR msg) const;
		_H3API_ BOOL Equals_i(const H3String& other) const;

		// * Inserts string within h3string at position
		_H3API_ H3String& Insert(INT32 pos, LPCSTR msg, INT32 len);
		_H3API_ H3String& Insert(INT32 pos, LPCSTR msg);
		_H3API_ H3String& Insert(INT32 pos, const H3String& to_insert);
		_H3API_ H3String& Insert(INT32 pos, CHAR ch);

		_H3API_ INT Compare(LPCSTR other) const;

		// * Ends string at position
		_H3API_ BOOL Truncate(INT32 position);

		// * counts number of times a character shows up
		_H3API_ INT Occurrences(CHAR ch) const;

		// * Assigns string to current

		_H3API_ H3String& operator=(const H3String& other);
		_H3API_ H3String& operator=(LPCSTR msg);
		_H3API_ H3String& operator=(CHAR ch);

	#ifdef _CPLUSPLUS11_
		_H3API_ H3String& operator=(H3String&& other) noexcept;
	#endif

		// * Appends to string

		_H3API_ H3String& operator+=(const H3String& other);
		template<INT32 Sz>
		H3String& operator+=(const CHAR(&buffer)[Sz]);
		_H3API_ H3String& operator+=(LPCSTR msg);
		_H3API_ H3String& operator+=(CHAR ch);
		_H3API_ H3String& operator+=(const int number);
		// * Adds hex number to string
		_H3API_ H3String& operator+=(const unsigned int number);

		// * Appends to string

		_H3API_ H3String& operator<<(CHAR ch);
		_H3API_ H3String& operator<<(LPCSTR msg);
		_H3API_ H3String& operator<<(H3String& other);
		_H3API_ H3String& operator<<(const int number);
		// * Adds hex number to string
		_H3API_ H3String& operator<<(const unsigned int number);

		// * cast operator
		_H3API_ operator LPCSTR () const;

		// * Compare using strcmp

		_H3API_ INT operator==(const H3String& h3str) const;
		_H3API_ INT operator==(LPCSTR str) const;

		// * Returns char at offset
		_H3API_ CHAR operator[](INT32 pos) const;

		// * The number of times this string is referenced - avoids deletion from destructor in references
		_H3API_ INT8 References() const;

		// * Increase the number of references to this string
		_H3API_ VOID IncreaseReferences();

		// * assigns a number with commas to a string
		_H3API_ BOOL FormattedNumber(int number);

		// * assigns a scaled number with k, M or B index and number of decimals
		_H3API_ BOOL ScaledNumber(int number, int decimals = 1);

	#ifdef _CPLUSPLUS11_
		// * use sprintf on a H3String directly
		template<typename ... Args>
		H3String& Printf(LPCSTR format, Args ... args);

		// * use sprintf on a H3String, appending the result to the end
		template<typename ... Args>
		H3String& PrintfAppend(LPCSTR format, Args ... args);
	#else // non c++11 versions
		// * use sprintf on a H3String directly
		_H3API_ H3String& Printf(LPCSTR format, ...);
		// * use sprintf on a H3String, appending the result to the end
		_H3API_ H3String& PrintfAppend(LPCSTR format, ...);
	#endif

	#ifdef _H3_STD_CONVERSIONS_
		// H3String to std::string conversions are handled through cast operator()
		_H3API_ H3String(const std::string& str);
		_H3API_ INT operator==(const std::string& str) const;
		_H3API_ H3String& operator+=(const std::string& str);
		_H3API_ H3String& operator=(const std::string& str);
		_H3API_ H3String& Assign(const std::string& str);
		_H3API_ H3String& Append(const std::string& str);
		_H3API_ std::string to_std_string() const;
	#endif /* _H3_STD_CONVERSIONS_ */

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

		enum eH3String
		{
			HS_NOTFOUND = -1,
			HS_FAILED = 0,
			HS_SUCCESS = 1
		};
	};
#pragma pack(pop)
}

#endif /* #define _H3STRING_HPP_ */