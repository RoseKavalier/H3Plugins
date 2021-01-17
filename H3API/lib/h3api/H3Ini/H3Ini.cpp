//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Ini.hpp"
#include "H3Ini.inl"
#include "../H3_Functions.hpp"
#include "../H3_Stream.hpp"
#ifdef _H3API_EXCEPTION_
#include "../H3_Exception.hpp"
#endif

namespace h3
{
	constexpr CHAR NEW_LINE[]     = "\r\n";
	constexpr CHAR INI_COMMENT    = '#';
	constexpr CHAR SECTION_START  = '[';
	constexpr CHAR SECTION_END    = ']';
	constexpr CHAR KEY_EQUALS[]   = " = ";
	constexpr CHAR BOM_HEADER[]   = "\xEF\xBB\xBF";

#pragma warning(push)
#pragma warning(disable:4482)
	_H3API_ LPCSTR HDIniEntry::GetText()
	{
		if (entryType == eType::INI_VALUE)
			return h3_NullString;
		return data.text;
	}
	_H3API_ HDIni::iterator HDIni::begin()
	{
		return iterator(entries);
	}
	_H3API_ HDIni::iterator HDIni::end()
	{
		return iterator(entries + lineEntries);
	}
	_H3API_ HDIni::iterator HDIni::FindEntry(LPCSTR key)
	{
		for (iterator it = begin(); it != end(); it++)
		{
			if (it->entryType == HDIniEntry::eType::INI_KEY)
			{
				if (F_strcmpi(key, it->data.text) == 0)
					return it;
			}
			else
				break;
		}

		return end();
	}
#pragma warning(pop)
	_H3API_ HDIni::iterator::iterator(HDIniEntry ** entries) :
		m_entry(entries)
	{
	}
	_H3API_ HDIniEntry * HDIni::iterator::operator->()
	{
		return *m_entry;
	}
	_H3API_ HDIni::iterator& HDIni::iterator::operator++()
	{
		m_entry += (*m_entry)->entryCount + 1;
		return *this;
	}
	_H3API_ HDIni::iterator HDIni::iterator::operator++(int)
	{
		iterator iter(this->m_entry);
		operator++();
		return iter;
	}
	_H3API_ HDIni::iterator & HDIni::iterator::operator*()
	{
		return *this;
	}
	_H3API_ BOOL8 HDIni::iterator::operator==(const iterator & other) const
	{
		return m_entry == other.m_entry;
	}
	_H3API_ BOOL8 HDIni::iterator::operator!=(const iterator & other) const
	{
		return m_entry != other.m_entry;
	}
	_H3API_ HDIniEntry * HDIni::iterator::operator[](UINT index)
	{
		return m_entry[index + 1];
	}

	_H3API_ INT H3IniLine::matches(const h3::H3String & key)
	{
		return m_content.Compare(key.String());
	}

	_H3API_ INT H3IniLine::matches(LPCSTR key)
	{
		return m_content.Compare(key);
	}

	_H3API_ BOOL8 H3IniLine::write(H3String & new_ini)
	{
		switch (m_type & LineType::ALL)
		{
		case LineType::EMPTY:
			break;
		case LineType::COMMENT:
			new_ini.Append(m_content);
			break;
		case LineType::SECTION:
			new_ini.Append(SECTION_START);
			new_ini.Append(m_content);
			new_ini.Append(SECTION_END);
			break;
		case LineType::KEY:
			new_ini.Append(m_content);
			new_ini.AppendA(KEY_EQUALS);
			new_ini.Append(m_value);
			break;
		default:
			return FALSE;
		}
		new_ini.AppendA(NEW_LINE);
		return TRUE;
	}

	_H3API_ H3IniLine::H3IniLine() :
		m_type(LineType::EMPTY)
	{
	}

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3IniLine::H3IniLine(h3::H3String && content, h3::H3String && value) :
		m_type(LineType::KEY), m_content(std::move(content)), m_value(std::move(value))
	{
	}
	_H3API_ H3IniLine::H3IniLine(LineType type, h3::H3String && content) :
		m_type(type), m_content(std::move(content))
	{
	}
#else
	H3IniLine::H3IniLine(LineType type, const H3String & content) :
		m_type(type), m_content(content)
	{
	}
	_H3API_ H3IniLine::H3IniLine(const H3String& content, const H3String& value) :
		m_content(content), m_value(value)
	{
	}
#endif
	_H3API_ FLOAT H3IniLine::GetFloat(FLOAT default_value)
	{
		if (m_value.Empty())
			return default_value;
		return FLOAT(F_atof(m_value));
	}
	_H3API_ DOUBLE H3IniLine::GetDouble(DOUBLE default_value)
	{
		if (m_value.Empty())
			return default_value;
		return F_atof(m_value);
	}
	_H3API_ H3String H3IniLine::GetString(const H3String & default_value)
	{
		if (m_value.Empty())
			return default_value;
		return m_value;
	}
	_H3API_ UINT H3IniLine::GetHex(UINT default_value)
	{
		if (m_value.Empty())
			return default_value;
		if (m_value.Length() > 2)
		{
			if (m_value[0] == '0' && (m_value[1] == 'x' || m_value[1] == 'X'))
				return F_strtoul(m_value.begin() + 2, 0x10);
		}
		return F_strtoul(m_value, 0x10);
	}
	_H3API_ bool H3IniLine::GetBool(bool default_value)
	{
		if (m_value.Empty())
			return default_value;
		switch (m_value[0])
		{
		case '1': // 1
		case 't': // true
		case 'T': // True
		case 'y': // yes
		case 'Y': // Yes
			return true;
		case '0': // 0
		case 'f': // false
		case 'F': // FALSE
		case 'n': // no
		case 'N': // No
			return false;
		case 'o': // on / off
		case 'O': // On / Off
		{
			char nf = m_value[1];
			if (nf == 'n' || nf == 'N')
				return true;
			if (nf == 'f' || nf == 'F')
				return false;
			return default_value;
		}
		default:
			return default_value;
		}
	}
	_H3API_ INT H3IniLine::GetInteger(INT default_value)
	{
		if (m_value.Empty())
			return default_value;
		return F_atoi(m_value.String());
	}
	_H3API_ BOOL8 H3IniLine::SetBool(bool value)
	{
		m_value.Assign(value ? '1' : '0');
		return TRUE;
	}
	_H3API_ BOOL8 H3IniLine::SetInteger(INT value)
	{
		m_value.Assign(value);
		return TRUE;
	}
	_H3API_ BOOL8 H3IniLine::SetFloat(FLOAT value)
	{
		m_value.Printf("%f", value);
		return TRUE;
	}
	_H3API_ BOOL8 H3IniLine::SetDouble(DOUBLE value)
	{
		m_value.Printf("%f", value);
		return TRUE;
	}
	_H3API_ BOOL8 H3IniLine::SetString(const H3String & value)
	{
		m_value.Assign(value);
		return TRUE;
	}
	_H3API_ BOOL8 H3IniLine::SetHex(UINT value)
	{
		m_value.Printf("0x%X", value);
		return TRUE;
	}

	_H3API_ H3IniSection::iterator::iterator(H3IniLine ** key) :
		data(key)
	{
	}

	_H3API_ H3IniLine & H3IniSection::iterator::operator*()
	{
		return **data;
	}

	_H3API_ H3IniLine * H3IniSection::iterator::operator->()
	{
		return *data;
	}

	_H3API_ BOOL8 H3IniSection::iterator::operator!=(const iterator & other)
	{
		return data != other.data;
	}

	_H3API_ BOOL8 H3IniSection::iterator::operator==(const iterator & other)
	{
		return data == other.data;
	}

	_H3API_ H3IniSection::iterator& H3IniSection::iterator::operator++()
	{
		++data;
		return *this;
	}

	_H3API_ H3IniSection::iterator H3IniSection::iterator::operator++(int)
	{
		iterator it(data);
		++data;
		return it;
	}

	_H3API_ H3IniSection::H3IniSection() :
		m_name(), m_searched()
	{
	}

	_H3API_ H3IniSection::H3IniSection(const H3IniLine * associated_line) :
		m_name(&associated_line->m_content), m_searched()
	{
	}

	_H3API_ H3IniSection::iterator H3IniSection::begin()
	{
		return iterator(m_keys.begin());
	}

	_H3API_ H3IniSection::iterator H3IniSection::end()
	{
		return iterator(m_keys.end() - 1);
	}

	_H3API_ H3IniSection::iterator H3IniSection::Get(LPCSTR key)
	{
		if (!m_searched)
		{
			UINT num = m_keys.Count();
			UINT left = 0;
			UINT right = num - 2; // last is empty line
			while (right >= left)
			{
				UINT mid = (left + right) / 2;
				H3IniLine** line = m_keys.begin() + mid;
				INT comp = (*line)->m_content.Compare(key);
				if (comp == 0)
					return iterator(line);
				if (comp < 0)
					right = mid - 1;
				else
					left = mid + 1;
			}
		}
		else
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (it->m_type & H3IniLine::LineType::SEARCHED)
					continue;
				if (it->m_content.Compare(key) == 0)
				{
					it->m_type |= H3IniLine::LineType::SEARCHED;
					return it;
				}
			}
		}
		return end();
	}

	_H3API_ H3IniSection::iterator H3IniSection::operator[](LPCSTR key)
	{
		return Get(key);
	}

	_H3API_ BOOL8 H3IniSection::SetBool(LPCSTR key, bool value)
	{
		iterator it = Get(key);
		if (it == end())
			return FALSE;
		return it->SetBool(value);
	}

	_H3API_ BOOL8 H3IniSection::SetInteger(LPCSTR key, INT value)
	{
		iterator it = Get(key);
		if (it == end())
			return FALSE;
		return it->SetInteger(value);
	}

	_H3API_ BOOL8 H3IniSection::SetString(LPCSTR key, const H3String & value)
	{
		iterator it = Get(key);
		if (it == end())
			return FALSE;
		return it->SetString(value);
	}

	_H3API_ BOOL8 H3IniSection::SetFloat(LPCSTR key, FLOAT value)
	{
		iterator it = Get(key);
		if (it == end())
			return FALSE;
		return it->SetFloat(value);
	}

	_H3API_ BOOL8 H3IniSection::SetDouble(LPCSTR key, DOUBLE value)
	{
		iterator it = Get(key);
		if (it == end())
			return FALSE;
		return it->SetDouble(value);
	}

	_H3API_ BOOL8 H3IniSection::SetHex(LPCSTR key, UINT value)
	{
		iterator it = Get(key);
		if (it == end())
			return FALSE;
		return it->SetHex(value);
	}

	_H3API_ bool H3IniSection::GetBool(LPCSTR key, bool default_value)
	{
		iterator it = Get(key);
		if (it == end())
			return default_value;
		return it->GetBool(default_value);
	}

	_H3API_ INT H3IniSection::GetInteger(LPCSTR key, INT default_value)
	{
		iterator it = Get(key);
		if (it == end())
			return default_value;
		return it->GetInteger(default_value);
	}

	_H3API_ FLOAT H3IniSection::GetFloat(LPCSTR key, FLOAT default_value)
	{
		iterator it = Get(key);
		if (it == end())
			return default_value;
		return it->GetFloat(default_value);
	}

	_H3API_ DOUBLE H3IniSection::GetDouble(LPCSTR key, DOUBLE default_value)
	{
		iterator it = Get(key);
		if (it == end())
			return default_value;
		return it->GetDouble(default_value);
	}

	_H3API_ H3String H3IniSection::GetString(LPCSTR key, const H3String & default_value)
	{
		iterator it = Get(key);
		if (it == end())
			return default_value;
		return it->GetString(default_value);
	}

	_H3API_ UINT H3IniSection::GetHex(LPCSTR key, UINT default_value)
	{
		iterator it = Get(key);
		if (it == end())
			return default_value;
		return it->GetHex(default_value);
	}

	_H3API_ H3Ini::iterator::iterator(H3IniSection * section) :
		data(section)
	{
	}

	_H3API_ H3IniSection& H3Ini::iterator::operator*()
	{
		return *data;
	}
	_H3API_ H3IniSection* H3Ini::iterator::operator->()
	{
		return data;
	}
	_H3API_ BOOL8 H3Ini::iterator::operator!=(const iterator& other)
	{
		return data != other.data;
	}
	_H3API_ BOOL8 H3Ini::iterator::operator==(const iterator & other)
	{
		return data == other.data;
	}
	_H3API_ H3Ini::iterator& H3Ini::iterator::operator++()
	{
		++data;
		return *this;
	}
	_H3API_ H3Ini::iterator H3Ini::iterator::operator++(int)
	{
		iterator it(data);
		++data;
		return it;
	}

	_H3API_ H3IniSection::iterator H3Ini::iterator::operator[](LPCSTR key)
	{
		return data->Get(key);
	}

	_H3API_ H3Ini::iterator H3Ini::begin()
	{
		return iterator(m_sections.begin());
	}
	_H3API_ H3Ini::iterator H3Ini::end()
	{
		return iterator(m_sections.end() - 1);
	}

	_H3API_ BOOL8 H3Ini::Open(LPCSTR file)
	{
		H3File f;
		if (!f.Open(file) || (!f.ReadToBuffer()))
#ifdef _H3API_EXCEPTION_
			throw H3Exception("Unable to open ini file.");
#else
			return FALSE;
#endif

		H3Vector<H3String> lines = f.GetLines(TRUE);
		// reserve parsed lines ahead of schedule
		// 1 extra line added for empty line
		m_lines.Reserve(lines.Count() + 1);

		H3IniSection* currentSection = nullptr;

		for (H3String* iter = lines.begin(); iter != lines.end(); ++iter)
		{
			H3String& it = *iter;
			it.Trim();
			if (it.Empty())
				m_lines.Add(H3IniLine());
			else
			{
				switch (it[0])
				{
				case INI_COMMENT:
#ifdef _H3API_CPLUSPLUS11_
					m_lines.Add(H3IniLine(H3IniLine::LineType::COMMENT, std::move(it)));
#else
					m_lines.Add(H3IniLine(H3IniLine::LineType::COMMENT, it));
#endif
					break;
				case SECTION_START:
				{
					if (it.Last() != SECTION_END)
					{
#ifdef _H3API_EXCEPTION_
						H3String error("Invalid section: ");
						error += it;
						throw H3Exception(error);
#else
						return FALSE;
#endif
					}
					it.Erase(it.Length() - 1);
					it.Erase(0);

					// * search for existing section, duplicate sections are not allowed
					for (H3IniSection* s = m_sections.begin(); s != m_sections.end(); ++s)
					{
						if (*s->m_name == it)
						{
							currentSection = s;
							break;
						}
					}
#ifdef _H3API_CPLUSPLUS11_
					H3IniLine* added = m_lines.Add(H3IniLine(H3IniLine::LineType::SECTION, std::move(it)));
#else
					H3IniLine* added = m_lines.Add(H3IniLine(H3IniLine::LineType::SECTION, it));
#endif
					currentSection = m_sections.Add(H3IniSection(added));
				}
					break;
				default: // key = value candidate
				{
					if (currentSection == nullptr)
					{
#ifdef _H3API_EXCEPTION_
						H3String error("Key line entry does not belong to a section: ");
						error += it;
						throw H3Exception(error);
#else
						return FALSE;
#endif
					}
					H3String value;
					if (!it.Split('=', value))
					{
#ifdef _H3API_EXCEPTION_
						H3String error("Key line does not have matching value: ");
						error += it;
						throw H3Exception(error);
#else
						return FALSE;
#endif
					}
					it.Trim();
					value.Trim();

					// * duplicate keys in a section are allowed but not supported
#ifdef _H3API_CPLUSPLUS11_
					H3IniLine* added = m_lines.Add(H3IniLine(std::move(it), std::move(value)));
#else
					H3IniLine* added = m_lines.Add(H3IniLine(it, value));
#endif
					currentSection->m_keys.Add(added);
				}
					break;
				}
			}
		}

		// * add empty sections and lines
		H3IniLine* emptyLine = m_lines.Add(H3IniLine());
		for (H3IniSection* section = m_sections.begin(); section != m_sections.end(); ++section)
			section->m_keys.Add(emptyLine);

		m_sections.Add(H3IniSection());

		return TRUE;
	}
	_H3API_ BOOL8 H3Ini::Save(LPCSTR file, BOOL utf8)
	{
		H3File f;
		if (!f.Save(file))
			return FALSE;

		H3String new_ini;
		if (utf8)
			new_ini.AssignA(BOM_HEADER);

		// end() - 1 because of empty line
		for (H3IniLine* iter = m_lines.begin(); iter != m_lines.end() - 1; ++iter)
		{
			if (!iter->write(new_ini))
				return FALSE;
		}
		return f.Write(new_ini);
	}
	_H3API_ H3Ini::iterator H3Ini::Get(LPCSTR section)
	{
		for (H3IniSection* it = m_sections.begin(); it != m_sections.end() - 1; ++it)
		{
			if (it->m_searched)
				continue;
			if (it->m_name->Compare(section) == 0)
			{
				it->m_searched = TRUE;
				return iterator(it);
			}
		}
		return end();
	}
	_H3API_ bool H3Ini::GetBool(LPCSTR section, LPCSTR key, bool default_value)
	{
		iterator it = Get(section);
		if (it == end())
			return default_value;
		return it->GetBool(key, default_value);
	}
	_H3API_ INT H3Ini::GetInteger(LPCSTR section, LPCSTR key, INT default_value)
	{
		iterator it = Get(section);
		if (it == end())
			return default_value;
		return it->GetInteger(key, default_value);
	}
	_H3API_ FLOAT H3Ini::GetFloat(LPCSTR section, LPCSTR key, FLOAT default_value)
	{
		iterator it = Get(section);
		if (it == end())
			return default_value;
		return it->GetFloat(key, default_value);
	}
	_H3API_ DOUBLE H3Ini::GetDouble(LPCSTR section, LPCSTR key, DOUBLE default_value)
	{
		iterator it = Get(section);
		if (it == end())
			return default_value;
		return it->GetDouble(key, default_value);
	}
	_H3API_ H3String H3Ini::GetString(LPCSTR section, LPCSTR key, const H3String & default_value)
	{
		iterator it = Get(section);
		if (it == end())
			return default_value;
		return it->GetString(key, default_value);
	}
	_H3API_ UINT H3Ini::GetHex(LPCSTR section, LPCSTR key, UINT default_value)
	{
		iterator it = Get(section);
		if (it == end())
			return default_value;
		return it->GetHex(key, default_value);
	}
	_H3API_ BOOL8 H3Ini::SetBool(LPCSTR section, LPCSTR key, bool value)
	{
		iterator it = Get(section);
		if (it == end())
			return FALSE;
		return it->SetBool(key, value);
	}
	_H3API_ BOOL8 H3Ini::SetInteger(LPCSTR section, LPCSTR key, INT value)
	{
		iterator it = Get(section);
		if (it == end())
			return FALSE;
		return it->SetInteger(key, value);
	}
	_H3API_ BOOL8 H3Ini::SetFloat(LPCSTR section, LPCSTR key, FLOAT value)
	{
		iterator it = Get(section);
		if (it == end())
			return FALSE;
		return it->SetFloat(key, value);
	}
	_H3API_ BOOL8 H3Ini::SetDouble(LPCSTR section, LPCSTR key, DOUBLE value)
	{
		iterator it = Get(section);
		if (it == end())
			return FALSE;
		return it->SetDouble(key, value);
	}
	_H3API_ BOOL8 H3Ini::SetString(LPCSTR section, LPCSTR key, const H3String & value)
	{
		iterator it = Get(section);
		if (it == end())
			return FALSE;
		return it->SetString(key, value);
	}
	_H3API_ BOOL8 H3Ini::SetHex(LPCSTR section, LPCSTR key, UINT value)
	{
		iterator it = Get(section);
		if (it == end())
			return FALSE;
		return it->SetHex(key, value);
	}
	_H3API_ H3Ini::iterator H3Ini::operator[](LPCSTR section)
	{
		return Get(section);
	}
}
