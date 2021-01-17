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

#include "../H3_String.hpp"
#include "../H3_Tree.hpp"

namespace h3
{
	class H3Ini;
	class H3IniSection;

#pragma pack(push, 1)
	/**
	 * @brief HDmod's format for ini files entries/lines
	 *
	 */
	struct HDIniEntry
	{
		_H3API_ENUM_ eType : BYTE
		{
			INI_VALUE = 2,
			INI_TEXT  = 3,
			INI_KEY   = 4
		};

		union
		{
			LPCSTR text;
			UINT32 value;
		}data;              /**< @brief [00] integer if INI_VALUE, otherwise LPCSTR*/
		eType  entryType;   /**< @brief [04]*/
		DWORD  entryCount;  /**< @brief [05] how many values are associated to this key*/
		LPCSTR uselessText; /**< @brief [09] linking characters in between entries like " = "*/

		/**
		 * @brief Get the associated text
		 *
		 * @return LPCSTR text from data union
		 */
		_H3API_ LPCSTR GetText();
	};
#pragma pack(pop)

#pragma pack(push, 4)
	/**
	 * @brief HDmod's format for ini files
	 *
	 */
	struct HDIni
	{
		HDIniEntry** entries;     /**< @brief [00] pointer to array of entry pointers*/
		UINT         lineEntries; /**< @brief [04] how many entries are available*/
		h3unk        _f_08[4];    /**< @brief [08]*/
		CHAR         name[8];     /**< @brief [0C] unknown length, 8 as placeholder*/

		/**
		 * @brief parses key entries of the ini
		 *
		 */
		struct iterator
		{
		protected:
			HDIniEntry** m_entry;
		public:
			_H3API_ iterator(HDIniEntry** entries);
			_H3API_ HDIniEntry* operator->();
			_H3API_ iterator&   operator++();
			_H3API_ iterator    operator++(int);
			_H3API_ iterator&   operator*();
			_H3API_ BOOL8       operator==(const iterator& other) const;
			_H3API_ BOOL8       operator!=(const iterator& other) const;
			_H3API_ HDIniEntry* operator[](UINT index);
		};

		_H3API_ iterator begin();
		_H3API_ iterator end();
		/**
		 * @brief find the iterator (line) of the specified key
		 *
		 * @param key name of the option line for which settings exist
		 * @return iterator of the line with matching key, end() iterator if not found
		 */
		_H3API_ iterator FindEntry(LPCSTR key);
	};

	/**
	 * @brief H3IniLine represents a key + value, comment or empty line for the H3Ini class
	 *
	 */
	class H3IniLine
	{
	public:
		friend class H3Ini;
		friend class H3IniSection;

		enum LineType : UINT
		{
			EMPTY    = 0,
			COMMENT  = 1,
			SECTION  = 2,
			KEY      = 4,
			SEARCHED = 8,
			ALL      = EMPTY | COMMENT | SECTION | KEY,
		};
	private:
		UINT     m_type;
		H3String m_content;
		H3String m_value;

		_H3API_ INT matches(const H3String& key);
		_H3API_ INT matches(LPCSTR key);
		_H3API_ BOOL8 write(H3String& new_ini);

	public:
		_H3API_ H3IniLine();
#ifdef _H3API_CPLUSPLUS11_
		/**
		 * @brief insert a new line in the ini at the current position
		 *
		 * @param type type of line to insert
		 * @param content a copy of the line to be inserted
		 */
		_H3API_ H3IniLine(LineType type, H3String&& content);
		/**
		 * @brief Insert a KEY line in the ini at the current position
		 *
		 * @param content the name of the associated key
		 * @param value value associated to this key
		 */
		_H3API_ H3IniLine(H3String&& content, H3String&& value);
#else
		/**
		 * @brief insert a new line in the ini at the current position
		 *
		 * @param type type of line to insert
		 * @param content a copy of the line to be inserted
		 */
		_H3API_ H3IniLine(LineType type, const H3String& content);
		/**
		 * @brief Insert a KEY line in the ini at the current position
		 *
		 * @param content the name of the associated key
		 * @param value value associated to this key
		 */
		_H3API_ H3IniLine(const H3String& content, const H3String& value);
#endif
		/**
		 * @brief Get an integer value for the current line
		 *
		 * @param default_value value to use in case the key is not found
		 * @return atoi value of the current key, or default_value if the key does not exist
		 */
		_H3API_ INT      GetInteger(INT default_value);
		/**
		 * @brief Get a boolean value for the current line
		 *
		 * @param default_value value to use in case the key is not found
		 * @return bool true on: 1, t..., on, yes (case insensitive) false on: 0, f..., off, no (case insensitive)
		 */
		_H3API_ bool     GetBool(bool default_value);
		/**
		 * @brief Get a float value for the current line
		 *
		 * @param default_value value to use in case the key is not found
		 * @return atof value of the current key, or default_value if the key does not exist
		 */
		_H3API_ FLOAT    GetFloat(FLOAT default_value);
		/**
		 * @brief Get a double value for the current line
		 *
		 * @param default_value value to use in case the key is not found
		 * @return atof value of the current key, or default_value if the key does not exist
		 */
		_H3API_ DOUBLE   GetDouble(DOUBLE default_value);
		/**
		 * @brief Get a string value for the current line
		 *
		 * @param default_value value to use in case the key is not found
		 * @return returns the contents as is
		 */
		_H3API_ H3String GetString(const H3String& default_value);
		/**
		 * @brief Get an unsigned integer value for the current line which is written as an hexadecimal value
		 * 0x and 0X prefixes are supported, but not essential
		 * @param default_value value to use in case the key is not found
		 * @return strtoul value of the current key, or default_value if the key does not exist
		 */
		_H3API_ UINT     GetHex(UINT default_value);
		/**
		 * @brief Set the currentline's value as a boolean
		 *
		 * @param value true/false on/off etc.
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetBool(bool value);
		/**
		 * @brief Set the currentline's value as a signed integer
		 *
		 * @param value signed integer
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetInteger(INT value);
		/**
		 * @brief Set the currentline's value as a float
		 *
		 * @param value float
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetFloat(FLOAT value);
		/**
		 * @brief Set the currentline's value as a double
		 *
		 * @param value double
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetDouble(DOUBLE value);
		/**
		 * @brief Set the currentline's value as a string
		 *
		 * @param value string
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetString(const H3String& value);
		/**
		 * @brief Set the currentline's value as an unsigned integer in hexadecimal format
		 *
		 * @param value unsigned integer
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetHex(UINT value);
	};

	/**
	 * @brief contains all keys existing under this [section]
	 *
	 */
	class H3IniSection
	{
		friend class H3Ini;

	public:
		/**
		 * @brief parse all keys/lines existing in this section
		 *
		 */
		class iterator
		{
		public:
			_H3API_ iterator(H3IniLine** key);
			_H3API_ H3IniLine& operator*();
			_H3API_ H3IniLine* operator->();
			_H3API_ BOOL8      operator!=(const iterator& other);
			_H3API_ BOOL8      operator==(const iterator& other);
			_H3API_ iterator&  operator++();
			_H3API_ iterator   operator++(int);

		private:
			H3IniLine** data;
		};

		_H3API_ H3IniSection();
		_H3API_ H3IniSection(const H3IniLine* associated_line);

		_H3API_ iterator begin();
		_H3API_ iterator end();
		/**
		 * @brief find a line with the specified key.
		 *
		 * @param key line starting as key = value
		 * @return iterator/line of the matching key, end() if not found
		 */
		_H3API_ iterator Get(LPCSTR key);
		/**
		 * @brief find a line with the specified key
		 *
		 * @param key line starting as key = value
		 * @return iterator/line of the matching key, end() if not found
		 */
		_H3API_ iterator operator[](LPCSTR key);
		/**
		 * @brief modify an existing line's value as a boolean.
		 * Fails if the key is not found.
		 * @param key line's starting value
		 * @param value true/false on/off etc.
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetBool(LPCSTR key, bool value);
		/**
		 * @brief modify an existing line's value as a signed integer.
		 * Fails if the key is not found.
		 * @param key line's starting value
		 * @param value signed integer
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetInteger(LPCSTR key, INT value);
		/**
		 * @brief modify an existing line's value as a string.
		 * Fails if the key is not found.
		 * @param key line's starting value
		 * @param value string
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetString(LPCSTR key, const H3String& value);
		/**
		 * @brief modify an existing line's value as a float.
		 * Fails if the key is not found.
		 * @param key line's starting value
		 * @param value float
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetFloat(LPCSTR key, FLOAT value);
		/**
		 * @brief modify an existing line's value as a double.
		 * Fails if the key is not found.
		 * @param key line's starting value
		 * @param value double
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetDouble(LPCSTR key, DOUBLE value);
		/**
		 * @brief modify an existing line's value as an unsigned integerin hexadecimal format.
		 * Fails if the key is not found.
		 * @param key line's starting value
		 * @param value unsigned integer
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetHex(LPCSTR key, UINT value);
		/**
		 * @brief Get the specified key's associated value as a boolean
		 *
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return bool true on: 1, t..., on, yes (case insensitive) false on: 0, f..., off, no (case insensitive)
		 */
		_H3API_ bool     GetBool(LPCSTR key, bool default_value);
		/**
		 * @brief Get the specified key's associated value as a signed integer
		 *
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return INT atoi signed integer of the associated value
		 */
		_H3API_ INT      GetInteger(LPCSTR key, INT default_value);
		/**
		 * @brief Get the specified key's associated value as a float
		 *
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return FLOAT atof of the associated value
		 */
		_H3API_ FLOAT    GetFloat(LPCSTR key, FLOAT default_value);
		/**
		 * @brief Get the specified key's associated value as a double
		 *
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return DOUBLE atof of the associated value
		 */
		_H3API_ DOUBLE   GetDouble(LPCSTR key, DOUBLE default_value);
		/**
		 * @brief Get the specified key's associated value
		 *
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return H3String copy of the associated value
		 */
		_H3API_ H3String GetString(LPCSTR key, const H3String& default_value);
		/**
		 * @brief Get the specified key's associated value as an unsigned integer
		 * 0x and 0X prefixes are supported, but not essential
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return UINT strtoul of the associated value
		 */
		_H3API_ UINT     GetHex(LPCSTR key, UINT default_value);

	private:
		const H3String*      m_name;
		H3Vector<H3IniLine*> m_keys;
		BOOL                 m_searched;
	};

	/**
	 * @brief an ini read/write class where sections and keys are
	 * expected to be in a specific order. Access will be closer to constant time than O(log n)
	 */
	class H3Ini
	{
	public:
		/**
		 * @brief parses sections of the ini and their associated keys;
		 * Using iterators(sections) is generally more efficient.
		 *
		 */
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
		/**
		 * @brief opens and parses an ini file.
		 * Throws H3Exception only if the specified file is not accessible.
		 * @param file name of the ini file to parse
		 * @return BOOL8 whether the file could be parsed successfully
		 */
		_H3API_ BOOL8 Open(LPCSTR file);
		/**
		 * @brief save a modified ini to disk
		 *
		 * @param file path to the ini
		 * @param utf8 whether to use utf8 bom header
		 * @return BOOL8 whether the modified ini was successfully saved
		 */
		_H3API_ BOOL8 Save(LPCSTR file, BOOL utf8);
		/**
		 * @brief Get a [section] iterator
		 *
		 * @param section name of the ini section to look for
		 * @return iterator/section of the matching name, end() if not found
		 */
		_H3API_ iterator Get(LPCSTR section);
		/**
		 * @brief Get a [section] iterator
		 *
		 * @param section name of the ini section to look for
		 * @return iterator/section of the matching name, end() if not found
		 */
		_H3API_ iterator operator[](LPCSTR section);
		_H3API_ iterator begin();
		_H3API_ iterator end();
		/**
		 * @brief Get the specified [section][key] associated value as a boolean
		 *
		 * @param section name of the [section] in which the key resides
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return bool true on: 1, t..., on, yes (case insensitive) false on: 0, f..., off, no (case insensitive)
		 */
		_H3API_ bool     GetBool(LPCSTR section, LPCSTR key, bool default_value);
		/**
		 * @brief Get the specified [section][key] associated value as a signed integer
		 *
		 * @param section name of the [section] in which the key resides
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return INT atoi signed integer
		 */
		_H3API_ INT      GetInteger(LPCSTR section, LPCSTR key, INT default_value);
		/**
		 * @brief Get the specified [section][key] associated value as a float
		 *
		 * @param section name of the [section] in which the key resides
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return FLOAT atof
		 */
		_H3API_ FLOAT    GetFloat(LPCSTR section, LPCSTR key, FLOAT default_value);
		/**
		 * @brief Get the specified [section][key] associated value as a double
		 *
		 * @param section name of the [section] in which the key resides
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return DOUBLE atof
		 */
		_H3API_ DOUBLE   GetDouble(LPCSTR section, LPCSTR key, DOUBLE default_value);
		/**
		 * @brief Get the specified [section][key] associated value as a string
		 *
		 * @param section name of the [section] in which the key resides
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return H3String copy of the key's value
		 */
		_H3API_ H3String GetString(LPCSTR section, LPCSTR key, const H3String& default_value);
		/**
		 * @brief Get the specified [section][key] associated value as a hexadecimal unsigned integer
		 * 0x and 0X prefixes are supported, but not essential
		 * @param section name of the [section] in which the key resides
		 * @param key line's starting value
		 * @param default_value value to use in case the key is not found
		 * @return UINT strtoul unsigned integer
		 */
		_H3API_ UINT     GetHex(LPCSTR section, LPCSTR key, UINT default_value);
		/**
		 * @brief modify an existing [section][key] value as an boolean.
		 * Fails if the section or key is not found.
		 * @param section name of the section to seek
		 * @param key line's starting value
		 * @param value true/false on/off etc.
		 * @return BOOL8 whether the operation was successful
		 */
		_H3API_ BOOL8 SetBool(LPCSTR section, LPCSTR key, bool value);
		/**
		 * @brief modify an existing [section][key] value as a signed integer.
		 * Fails if the section or key is not found.
		 * @param section name of the section to seek
		 * @param key line's starting value
		 * @param value signed integer
		 * @return BOOL8 whether the operation was successful
		 */
		_H3API_ BOOL8 SetInteger(LPCSTR section, LPCSTR key, INT value);
		/**
		 * @brief modify an existing [section][key] value as a float.
		 * Fails if the section or key is not found.
		 * @param section name of the section to seek
		 * @param key line's starting value
		 * @param value float
		 * @return BOOL8 whether the operation was successful
		 */
		_H3API_ BOOL8 SetFloat(LPCSTR section, LPCSTR key, FLOAT value);
		/**
		 * @brief modify an existing [section][key] value as a double.
		 * Fails if the section or key is not found.
		 * @param section name of the section to seek
		 * @param key line's starting value
		 * @param value double
		 * @return BOOL8 whether the operation was successful
		 */
		_H3API_ BOOL8 SetDouble(LPCSTR section, LPCSTR key, DOUBLE value);
		/**
		 * @brief modify an existing [section][key] value as a string.
		 * Fails if the section or key is not found.
		 * @param section name of the section to seek
		 * @param key line's starting value
		 * @param value string
		 * @return BOOL8 whether the operation was successful
		 */
		_H3API_ BOOL8 SetString(LPCSTR section, LPCSTR key, const H3String& value);
		/**
		 * @brief modify an existing [section][key] value as an unsigned integer in hexadecimal format.
		 * Fails if the section or key is not found.
		 * @param section name of the section to seek
		 * @param key line's starting value
		 * @param value unsigned integer
		 * @return BOOL8 whether operation was successful
		 */
		_H3API_ BOOL8 SetHex(LPCSTR section, LPCSTR key, UINT value);

	private:
		H3Vector<H3IniLine>     m_lines;
		H3Vector<H3IniSection>  m_sections;
	};
#pragma pack(pop)
}

#endif /* #define _H3INI_HPP_ */