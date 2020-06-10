//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3INI_HPP_
#define _H3INI_HPP_

#include "../H3_Base.hpp"
#include "../H3_String.hpp"
#include "../H3_Tree.hpp"
#include "../H3_Vector.hpp"

namespace h3
{
#pragma pack(push, 1)
	// * HDmod's format for ini files lines
	struct HDIniEntry // size 0xD ~ 13
	{
		union
		{
			LPCSTR text;
			UINT32 value;
		}data;
		_H3API_ENUM_ eType : BYTE
		{
			iniValue = 2,
			iniText  = 3,
			iniKey   = 4
		};
		eType entryType;
		DWORD entryCount;
		LPCSTR uselessText; // like " = ", end of line, ...

		_H3API_ LPCSTR GetText();
	};

	// * HDmod's format for ini files
	struct HDIni
	{
		HDIniEntry** entries;
		UINT lineEntries;
		h3unk _f_08[4];
		CHAR name[8]; // unknown length

		struct iterator
		{
		protected:
			HDIniEntry** m_entry;
		public:
			_H3API_ iterator(HDIniEntry** entries);
			_H3API_ HDIniEntry* operator->();
			_H3API_ iterator& operator++();
			_H3API_ iterator operator++(int);
			_H3API_ iterator& operator*();
			_H3API_ BOOL8 operator==(const iterator& other) const;
			_H3API_ BOOL8 operator!=(const iterator& other) const;
			_H3API_ HDIniEntry* operator[](UINT index);
		};

		_H3API_ iterator begin();
		_H3API_ iterator end();

		_H3API_ iterator FindEntry(LPCSTR key);
	};
#pragma pack(pop)

	class H3Ini;
	class H3IniSection;
#pragma pack(push, 4)
	class H3IniLine
	{
		friend class H3Ini;
		friend class H3IniSection;

		enum LineType : UINT
		{
			empty    = 0,
			comment  = 1,
			section  = 2,
			key      = 4,
			searched = 8,
			all      = empty | comment | section | key,
		};

		UINT     m_type;
		H3String m_content;
		H3String m_value;

		_H3API_ INT matches(const H3String& key);
		_H3API_ INT matches(LPCSTR key);
		_H3API_ BOOL8 write(H3String& new_ini);

	public:
		_H3API_ H3IniLine();
#ifdef _H3API_CPLUSPLUS11_
		_H3API_ H3IniLine(LineType type, H3String&& content);
		_H3API_ H3IniLine(H3String&& content, H3String&& value);
#else
		_H3API_ H3IniLine(LineType type, const H3String& content);
		_H3API_ H3IniLine(const H3String& content, const H3String& value);
#endif
		_H3API_ INT      GetInteger(INT default_value);
		_H3API_ bool     GetBool(bool default_value);
		_H3API_ FLOAT    GetFloat(FLOAT default_value);
		_H3API_ DOUBLE   GetDouble(DOUBLE default_value);
		_H3API_ H3String GetString(const H3String& default_value);
		_H3API_ UINT     GetHex(UINT default_value);

		_H3API_ BOOL8 SetBool(bool value);
		_H3API_ BOOL8 SetInteger(INT value);
		_H3API_ BOOL8 SetFloat(FLOAT value);
		_H3API_ BOOL8 SetDouble(DOUBLE value);
		_H3API_ BOOL8 SetString(const H3String& value);
		_H3API_ BOOL8 SetHex(UINT value);
	};

	class H3IniSection
	{
		friend class H3Ini;

	public:
		class iterator
		{
		public:
			_H3API_ iterator(H3IniLine** key);
			_H3API_ H3IniLine& operator*();
			_H3API_ H3IniLine* operator->();
			_H3API_ BOOL8 operator!=(const iterator& other);
			_H3API_ BOOL8 operator==(const iterator& other);
			_H3API_ iterator& operator++();
			_H3API_ iterator operator++(int);

		private:
			H3IniLine** data;
		};

		_H3API_ H3IniSection();
		_H3API_ H3IniSection(const H3IniLine* associated_line);

		_H3API_ iterator begin();
		_H3API_ iterator end();
		_H3API_ iterator Get(LPCSTR key);
		_H3API_ iterator operator[](LPCSTR key);

		_H3API_ BOOL8 SetBool(LPCSTR key, bool value);
		_H3API_ BOOL8 SetInteger(LPCSTR key, INT value);
		_H3API_ BOOL8 SetString(LPCSTR key, const H3String& value);
		_H3API_ BOOL8 SetFloat(LPCSTR key, FLOAT value);
		_H3API_ BOOL8 SetDouble(LPCSTR key, DOUBLE value);
		_H3API_ BOOL8 SetHex(LPCSTR key, UINT value);

		_H3API_ bool     GetBool(LPCSTR key, bool default_value);
		_H3API_ INT      GetInteger(LPCSTR key, INT default_value);
		_H3API_ FLOAT    GetFloat(LPCSTR key, FLOAT default_value);
		_H3API_ DOUBLE   GetDouble(LPCSTR key, DOUBLE default_value);
		_H3API_ H3String GetString(LPCSTR key, const H3String& default_value);
		_H3API_ UINT     GetHex(LPCSTR key, UINT default_value);

	private:
		const H3String* m_name;
		H3Vector<H3IniLine*> m_keys;
		BOOL m_searched;
	};

	// * an ini read/write class where sections and keys
	// * expected to be in a specific order. Access will be closer to constant time than O(log n)
	class H3Ini
	{
	public:
		class iterator
		{
		public:
			_H3API_ iterator(H3IniSection* section);
			_H3API_ H3IniSection& operator*();
			_H3API_ H3IniSection* operator->();
			_H3API_ BOOL8 operator!=(const iterator& other);
			_H3API_ BOOL8 operator==(const iterator& other);
			_H3API_ iterator& operator++();
			_H3API_ iterator operator++(int);
			_H3API_ H3IniSection::iterator operator[](LPCSTR key);
		private:
			H3IniSection* data;
		};

		// * sort will rearrange sections and keys alphabetically
		// * use this if you don't expect data to be in a specific order;
		// * if you know the pre-arranged order of sections and keys
		// * then unsorted will be much faster
		_H3API_ BOOL8 Open(LPCSTR file);
		_H3API_ BOOL8 Save(LPCSTR file, BOOL utf8);

		_H3API_ iterator Get(LPCSTR section);

		_H3API_ bool     GetBool(LPCSTR section, LPCSTR key, bool default_value);
		_H3API_ INT      GetInteger(LPCSTR section, LPCSTR key, INT default_value);
		_H3API_ FLOAT    GetFloat(LPCSTR section, LPCSTR key, FLOAT default_value);
		_H3API_ DOUBLE   GetDouble(LPCSTR section, LPCSTR key, DOUBLE default_value);
		_H3API_ H3String GetString(LPCSTR section, LPCSTR key, const H3String& default_value);
		_H3API_ UINT     GetHex(LPCSTR section, LPCSTR key, UINT default_value);

		_H3API_ BOOL8 SetBool(LPCSTR section, LPCSTR key, bool value);
		_H3API_ BOOL8 SetInteger(LPCSTR section, LPCSTR key, INT value);
		_H3API_ BOOL8 SetFloat(LPCSTR section, LPCSTR key, FLOAT value);
		_H3API_ BOOL8 SetDouble(LPCSTR section, LPCSTR key, DOUBLE value);
		_H3API_ BOOL8 SetString(LPCSTR section, LPCSTR key, const H3String& value);
		_H3API_ BOOL8 SetHex(LPCSTR section, LPCSTR key, UINT value);

		_H3API_ iterator operator[](LPCSTR section);
		_H3API_ iterator begin();
		_H3API_ iterator end();
	private:
		H3Vector<H3IniLine>     m_lines;
		H3Vector<H3IniSection>  m_sections;
	};
#pragma pack(pop)
}

#endif /* #define _H3INI_HPP_ */