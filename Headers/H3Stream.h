//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STREAM_H_
#define _H3STREAM_H_

#pragma once

#include "H3Base.h"
#include "H3Functions.h"

// * read / write files using H3 assets
class H3Stream
{
	enum StreamModeValues
	{
		MV_READ   = 1,
		MV_WRITE  = 2,
		MV_APPEND = 4,
		MV_UPDATE = 8,
		MV_BINARY = 16,
	};

public:
	enum StreamMode
	{
		SM_INVALID				= 0,
		/* r */
		SM_READ                 = MV_READ,
		/* rb */
		SM_READ_BINARY          = MV_READ          | MV_BINARY,
		/* w */
		SM_WRITE                = MV_WRITE,
		/* wb */
		SM_WRITE_BINARY         = MV_WRITE         | MV_BINARY,
		/* a */
		SM_APPEND               = MV_APPEND,
		/* ab */
		SM_APPEND_BINARY        = MV_APPEND        | MV_BINARY,
		/* r+ */
		SM_READ_UPDATE          = MV_READ          | MV_UPDATE,
		/* r+b */
		SM_READ_UPDATE_BINARY   = SM_READ_UPDATE   | MV_BINARY,
		/* w+ */
		SM_WRITE_UPDATE         = MV_WRITE         | MV_UPDATE,
		/* w+b */
		SM_WRITE_UPDATE_BINARY  = SM_WRITE_UPDATE  | MV_BINARY,
		/* a+ */
		SM_APPEND_UPDATE        = MV_APPEND        | MV_UPDATE,
		/* a+b */
		SM_APPEND_UPDATE_BINARY = SM_APPEND_UPDATE | MV_BINARY,
	};
	enum StreamStatus
	{
		SS_OK,
		SS_NOT_LOADED,
		SS_INVALID,
	};

	H3Stream(LPCSTR filename, StreamMode read_write_mode, BOOL read_to_buffer = FALSE);
	H3Stream(LPCSTR filename, LPCSTR read_write_mode, BOOL read_to_buffer = FALSE);
	H3Stream(const H3String& filename, StreamMode read_write_mode, BOOL read_to_buffer = FALSE) : H3Stream(filename.String(), read_write_mode, read_to_buffer) {}
	H3Stream(const H3String* filename, StreamMode read_write_mode, BOOL read_to_buffer = FALSE) : H3Stream(filename->String(), read_write_mode, read_to_buffer) {}
	~H3Stream();

	// * set integer write mode to hexadecimal display
	H3Stream& hex();
	// * set integer write mode to decimal display
	// * [default]
	H3Stream& decimal();
	// * the stream will write a new line after each output operation
	H3Stream& new_lines();
	// * the stream will not write a new line after each output operation
	// * [default]
	H3Stream& no_new_lines();
	// * writes a new line
	H3Stream& endl();

	BOOL IsReady() const { return m_status == SS_OK; }
	StreamStatus GetStatus() const { return m_status; }
	StreamMode GetMode() const { return m_mode; }

	// * makes a copy of the file to provided destination
	BOOL Copy(LPCSTR destination);
	// * makes a copy of the file to provided destination
	BOOL Copy(const H3String& destination);
	// * makes a copy of the file to provided destination
	BOOL Copy(const H3String* destination);

#if CPLUSPLUS11
	// * write varying arguments
	template<typename ... Args>
	H3Stream& Write(LPCSTR format, Args ... args)
	{
		if (IsReady() && CanWrite())
			CDECL_VA2(int, 0x61A031, m_file, format, args ...);
		return *this;
	}
#else
	// * write varying arguments
	H3Stream& Write(LPCSTR format, ...);
#endif

	// * writes integer
	H3Stream& operator<<(const int number);
	// * writes unsigned integer
	H3Stream& operator<<(const unsigned int number);
	// * writes float
	H3Stream& operator<<(const FLOAT number);
	// * writes double
	H3Stream& operator<<(const DOUBLE number);
	// * writes char
	H3Stream& operator<<(const CHAR character);
	// * writes text string
	H3Stream& operator<<(LPCSTR text);
	// * writes H3string
	H3Stream& operator<<(const H3String& str);
	// * writes H3string
	H3Stream& operator<<(const H3String* str);

	// * writes pre-defined string of known length
	// * WARNING!!! passing a char buffer[512]
	// * will print **all** of the buffer
	// * use Write() instead
	template<INT32 sz>
	H3Stream& operator<<(const CHAR(&expression)[sz]);
	// * reads a line
	// * and moves m_buffer_position along
	H3Stream& operator>>(H3String& line);
	// * reads all lines
	H3Stream& operator>>(H3Vector<H3String>& lines);

	BOOL ReadFile(DWORD size_to_read);

protected:
	FILE *       m_file;
	DWORD        m_size;
	StreamMode   m_mode;
	BOOL         m_write_hex;
	BOOL         m_write_new_lines;
	StreamStatus m_status;
	BYTE *       m_buffer;
	DWORD        m_buffer_size;
	DWORD        m_buffer_position;

	LPCSTR GetModeFormat();
	template<typename T>
	VOID Printf(LPCSTR format, T value);
	VOID WriteNewLine();
	BOOL CanWrite();
	BOOL CanRead();
};

inline H3Stream::H3Stream(LPCSTR filename, StreamMode read_write_mode, BOOL read_to_buffer) :
	m_file(nullptr),
	m_size(0),
	m_mode(read_write_mode),
	m_write_hex(FALSE),
	m_write_new_lines(FALSE),
	m_status(SS_NOT_LOADED),
	m_buffer(nullptr),
	m_buffer_size(0),
	m_buffer_position(0)
{
	LPCSTR mode = GetModeFormat();
	if (mode)
	{
		if (m_file = F_fopen(filename, mode))
		{
			m_status = SS_OK;
			m_size = F_GetFileSize(m_file);
		}
		if (read_to_buffer && m_size && CanRead())
			ReadFile(m_size);
	}
}

inline H3Stream::H3Stream(LPCSTR filename, LPCSTR read_write_mode, BOOL read_to_buffer) :
	m_file(nullptr),
	m_size(0),
	m_mode(SM_INVALID),
	m_write_hex(FALSE),
	m_write_new_lines(FALSE),
	m_status(SS_NOT_LOADED),
	m_buffer(nullptr),
	m_buffer_size(0),
	m_buffer_position(0)
{
	if (read_write_mode)
	{
		switch (read_write_mode[0])
		{
		case 'r':
			m_mode = (StreamMode)(m_mode | MV_READ);
			break;
		case 'w':
			m_mode = (StreamMode)(m_mode | MV_WRITE);
			break;
		case 'a':
			m_mode = (StreamMode)(m_mode | MV_APPEND);
			break;
		default:
			break;
		}

		if (read_write_mode[1])
		{
			switch (read_write_mode[1])
			{
			case 'r':
				m_mode = (StreamMode)(m_mode | MV_READ);
				break;
			case 'w':
				m_mode = (StreamMode)(m_mode | MV_WRITE);
				break;
			case 'a':
				m_mode = (StreamMode)(m_mode | MV_APPEND);
				break;
			case '+':
				m_mode = (StreamMode)(m_mode | MV_UPDATE);
				break;
			case 'b':
				m_mode = (StreamMode)(m_mode | MV_BINARY);
				break;
			default:
				break;
			}

			if (read_write_mode[2])
			{
				switch (read_write_mode[2])
				{
				case 'r':
					m_mode = (StreamMode)(m_mode | MV_READ);
					break;
				case 'w':
					m_mode = (StreamMode)(m_mode | MV_WRITE);
					break;
				case 'a':
					m_mode = (StreamMode)(m_mode | MV_APPEND);
					break;
				case '+':
					m_mode = (StreamMode)(m_mode | MV_UPDATE);
					break;
				case 'b':
					m_mode = (StreamMode)(m_mode | MV_BINARY);
					break;
				default:
					break;
				}
			}
		}
	}

	if (m_mode != SM_INVALID)
	{
		if (m_file = F_fopen(filename, read_write_mode))
		{
			m_status = SS_OK;
			m_size = F_GetFileSize(m_file);
		}
		if (read_to_buffer && m_size && CanRead())
			ReadFile(m_size);
	}
}

inline H3Stream::~H3Stream()
{
	if (m_file)
	{
		F_fclose(m_file);
		m_file = nullptr;
	}
	if (m_buffer)
	{
		F_delete(m_buffer);
		m_buffer = nullptr;
	}
}

inline H3Stream & H3Stream::hex()
{
	m_write_hex = TRUE;
	return *this;
}

inline H3Stream & H3Stream::decimal()
{
	m_write_hex = FALSE;
	return *this;
}

inline H3Stream & H3Stream::new_lines()
{
	m_write_new_lines = TRUE;
	return *this;
}

inline H3Stream & H3Stream::no_new_lines()
{
	m_write_new_lines = FALSE;
	return *this;
}

inline H3Stream & H3Stream::endl()
{
	if (IsReady() && CanWrite())
		Printf("%s", "\r\n");
	return *this;
}

inline BOOL H3Stream::Copy(LPCSTR destination)
{
	if (!(m_mode && (MV_READ | MV_UPDATE)))
		return FALSE;

	if ((!m_buffer_size || !m_buffer) && !ReadFile(m_size))
		return FALSE;

	F_fread(m_buffer, 1, m_size, m_file);

	H3Stream dest(destination, SM_WRITE_BINARY);
	if (dest.GetStatus() == SS_OK)
		F_fwrite(m_buffer, 1, m_size, dest.m_file);

	return TRUE;
}

inline BOOL H3Stream::Copy(const H3String & destination)
{
	if (destination.String() && destination.Length())
		return Copy(destination.String());
	return FALSE;
}

inline BOOL H3Stream::Copy(const H3String * destination)
{
	if (destination)
		return Copy(*destination);
	return FALSE;
}

#ifndef CPLUSPLUS11
inline H3Stream & H3Stream::Write(LPCSTR format, ...)
{
	if (IsReady() && CanWrite())
	{
		va_list args;
		va_start(args, format);
		int len = _snprintf(nullptr, 0, format, args);
		H3String buffer;
		if (len > 0 && buffer.Reserve(len + 1))
		{
			len = F_vsprintf(buffer.Begin(), format, args);
			buffer.Truncate(len);
			operator<<(buffer);
		}
		va_end(args);
		WriteNewLine();
	}
	return *this;
}
#endif

inline H3Stream & H3Stream::operator<<(const int number)
{
	if (IsReady() && CanWrite())
	{
		if (m_write_hex)
			Printf("0x%X", number);
		else
			Printf("%d", number);
		WriteNewLine();
	}
	return *this;
}

inline H3Stream & H3Stream::operator<<(const unsigned int number)
{
	if (IsReady())
	{
		if (m_write_hex)
			Printf("0x%X", number);
		else
			Printf("%u", number);
		WriteNewLine();
	}
	return *this;
}

inline H3Stream & H3Stream::operator<<(const FLOAT number)
{
	if (IsReady())
	{
		Printf("%f", number);
		WriteNewLine();
	}

	return *this;
}

inline H3Stream & H3Stream::operator<<(const DOUBLE number)
{
	if (IsReady())
	{
		Printf("%f", number);
		WriteNewLine();
	}

	return *this;
}

inline H3Stream & H3Stream::operator<<(const CHAR character)
{
	if (IsReady() && CanWrite())
	{
		F_fputc(character, m_file);
		WriteNewLine();
	}

	return *this;
}

inline H3Stream & H3Stream::operator<<(LPCSTR text)
{
	if (IsReady())
	{
		Printf("%s", text);
		WriteNewLine();
	}

	return *this;
}

inline H3Stream & H3Stream::operator<<(const H3String & str)
{
	if (IsReady() && str.String() && str.Length())
	{
		F_fwrite(str.String(), 1, str.Length(), m_file);
		WriteNewLine();
	}

	return *this;
}

inline H3Stream & H3Stream::operator<<(const H3String * str)
{
	if (str)
		return operator<<(*str);
	return *this;
}

inline LPCSTR H3Stream::GetModeFormat()
{
	switch (m_mode)
	{
	case SM_READ:
		return "r";
	case SM_READ_BINARY:
		return "rb";
	case SM_WRITE:
		return "w";
	case SM_WRITE_BINARY:
		return "wb";
	case SM_APPEND:
		return "a";
	case SM_APPEND_BINARY:
		return "ab";
	case SM_READ_UPDATE:
		return "r+";
	case SM_READ_UPDATE_BINARY:
		return "r+b";
	case SM_WRITE_UPDATE:
		return "w+";
	case SM_WRITE_UPDATE_BINARY:
		return "w+b";
	case SM_APPEND_UPDATE:
		return "a+";
	case SM_APPEND_UPDATE_BINARY:
		return "a+b";
	default:
		return nullptr;
	}
}

inline VOID H3Stream::WriteNewLine()
{
	if (m_write_new_lines)
		endl();
}

inline BOOL H3Stream::CanWrite()
{
	return m_mode && (MV_WRITE | MV_APPEND | MV_UPDATE);
}

inline BOOL H3Stream::CanRead()
{
	return m_mode && (MV_READ | MV_UPDATE);
}

inline BOOL H3Stream::ReadFile(DWORD size_to_read)
{
	if (!IsReady() || !CanRead())
		return FALSE;

	DWORD sz = min(m_size, size_to_read);

	if (m_buffer_size < size_to_read)
	{
		delete m_buffer;
		m_buffer_size = size_to_read;
		m_buffer = (PBYTE)F_calloc(m_buffer_size);
	}

	m_buffer_position = 0;

	return F_fread(m_buffer, 1, m_buffer_size, m_file) == m_buffer_size;
}

#endif /* #define _H3STREAM_H_ */

template<INT32 sz>
inline H3Stream & H3Stream::operator<<(const CHAR(&expression)[sz])
{
	if (IsReady() && CanWrite())
		F_fwrite((PVOID)&expression, 1, sz, m_file);
	return *this;
}

template<typename T>
inline VOID H3Stream::Printf(LPCSTR format, T value)
{
	if (CanWrite())
		CDECL_3(int, 0x61A031, m_file, format, value);
}

inline H3Stream & H3Stream::operator>>(H3String& str)
{
	str.Truncate(0);

	if (IsReady() && m_buffer && m_buffer_position < m_buffer_size)
	{
		int len = 0;
		BYTE* start = m_buffer + m_buffer_position;
		BYTE* current = start;
		while (m_buffer_position < m_buffer_size && *current)
		{
			if (*current == '\n')
			{
				// * if at least 1 character was parsed, check if previous is carriage return
				if (len && *(current - 1) == '\r')
					len--;
				// * skip this character for next time
				++m_buffer_position;
				break;
			}
			++len;
			++current;
			++m_buffer_position;
		}
		// * blank lines ("\n" or "\r\n") are not assigned
		if (len)
			str.Assign((PCHAR)start, len);
	}
	return *this;
}

inline H3Stream& H3Stream::operator>>(H3Vector<H3String>& lines)
{
	if (!IsReady() || !m_buffer || m_buffer_position >= m_buffer_size)
		return *this;
	lines.Deref();

	while (m_buffer_position < m_buffer_size)
	{
		H3String line;
		operator>>(line);
		lines += line;
	}

	return *this;
}