//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Stream.hpp"
#include "../H3_Functions.hpp"

namespace h3
{
	_H3API_ H3Stream::H3Stream(LPCSTR filename, StreamMode read_write_mode, BOOL read_to_buffer) :
		m_file(nullptr),
		m_size(0),
		m_mode(read_write_mode),
		m_write_hex(FALSE),
		m_write_new_lines(FALSE),
		m_status(StreamStatus::SS_NOT_LOADED),
		m_buffer(nullptr),
		m_buffer_size(0),
		m_buffer_position(0)
	{
		LPCSTR mode = GetModeFormat();
		if (mode)
		{
			if ((m_file = F_fopen(filename, mode)))
			{
				m_status = StreamStatus::SS_OK;
				m_size = F_GetFileSize(m_file);
			}
			if (read_to_buffer && m_size && CanRead())
				ReadFile(m_size);
		}
	}
	_H3API_ H3Stream::H3Stream(LPCSTR filename, LPCSTR read_write_mode, BOOL read_to_buffer) :
		m_file(nullptr),
		m_size(0),
		m_mode(StreamMode::SM_INVALID),
		m_write_hex(FALSE),
		m_write_new_lines(FALSE),
		m_status(StreamStatus::SS_NOT_LOADED),
		m_buffer(nullptr),
		m_buffer_size(0),
		m_buffer_position(0)
	{
		if (read_write_mode)
		{
			switch (read_write_mode[0])
			{
			case 'r':
				m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_READ)));
				break;
			case 'w':
				m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_WRITE)));
				break;
			case 'a':
				m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_APPEND)));
				break;
			default:
				break;
			}

			if (read_write_mode[1])
			{
				switch (read_write_mode[1])
				{
				case 'r':
					m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_READ)));
					break;
				case 'w':
					m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_WRITE)));
					break;
				case 'a':
					m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_APPEND)));
					break;
				case '+':
					m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_UPDATE)));
					break;
				case 'b':
					m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_BINARY)));
					break;
				default:
					break;
				}

				if (read_write_mode[2])
				{
					switch (read_write_mode[2])
					{
					case 'r':
						m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_READ)));
						break;
					case 'w':
						m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_WRITE)));
						break;
					case 'a':
						m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_APPEND)));
						break;
					case '+':
						m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_UPDATE)));
						break;
					case 'b':
						m_mode = StreamMode(int(m_mode) | int(StreamMode(MV_BINARY)));
						break;
					default:
						break;
					}
				}
			}
		}

		if (m_mode != StreamMode::SM_INVALID)
		{
			if ((m_file = F_fopen(filename, read_write_mode)))
			{
				m_status = StreamStatus::SS_OK;
				m_size = F_GetFileSize(m_file);
			}
			if (read_to_buffer && m_size && CanRead())
				ReadFile(m_size);
		}
	}	
	_H3API_ H3Stream::~H3Stream()
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
	_H3API_ H3Stream& H3Stream::hex()
	{
		m_write_hex = TRUE;
		return *this;
	}
	_H3API_ H3Stream& H3Stream::decimal()
	{
		m_write_hex = FALSE;
		return *this;
	}
	_H3API_ H3Stream& H3Stream::new_lines()
	{
		m_write_new_lines = TRUE;
		return *this;
	}
	_H3API_ H3Stream& H3Stream::no_new_lines()
	{
		m_write_new_lines = FALSE;
		return *this;
	}
	_H3API_ H3Stream& H3Stream::endl()
	{
		if (IsReady() && CanWrite())
			CDECL_3(int, 0x61A031, m_file, "%s", "\r\n");			
		return *this;
	}
	_H3API_ BOOL H3Stream::IsReady() const
	{
		return m_status == StreamStatus::SS_OK;
	}
	_H3API_ H3Stream::StreamStatus H3Stream::GetStatus() const
	{
		return m_status;
	}
	_H3API_ H3Stream::StreamMode H3Stream::GetMode() const
	{
		return m_mode;
	}
	_H3API_ BOOL H3Stream::Copy(LPCSTR destination)
	{
		if (!(int(m_mode) & (MV_READ | MV_UPDATE)))
			return FALSE;

		if ((!m_buffer_size || !m_buffer) && !ReadFile(m_size))
			return FALSE;

		F_fread(m_buffer, 1, m_size, m_file);

		H3Stream dest(destination, StreamMode::SM_WRITE_BINARY);
		if (dest.GetStatus() == StreamStatus::SS_OK)
			F_fwrite(m_buffer, 1, m_size, dest.m_file);

		return TRUE;
	}
	_H3API_ BOOL H3Stream::Copy(const H3String& destination)
	{
		if (destination.String() && destination.Length())
			return Copy(destination.String());
		return FALSE;
	}
#ifndef _CPLUSPLUS11_
	_H3API_	H3Stream& H3Stream::Write(LPCSTR format, ...)
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

	_H3API_	H3Stream& H3Stream::operator<<(const int number)
	{
		if (IsReady() && CanWrite())
		{
			if (m_write_hex)
				CDECL_3(int, 0x61A031, m_file, "0x%X", number);				
			else
				CDECL_3(int, 0x61A031, m_file, "%d", number);				
			WriteNewLine();
		}
		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator<<(const unsigned int number)
	{
		if (IsReady())
		{
			if (m_write_hex)
				CDECL_3(int, 0x61A031, m_file, "0x%X", number);
			else
				CDECL_3(int, 0x61A031, m_file, "%u", number);
			WriteNewLine();
		}
		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator<<(const FLOAT number)
	{
		if (IsReady())
		{
			CDECL_3(int, 0x61A031, m_file, "%f", number);			
			WriteNewLine();
		}

		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator<<(const DOUBLE number)
	{
		if (IsReady())
		{
			CDECL_3(int, 0x61A031, m_file, "%f", number);
			WriteNewLine();
		}

		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator<<(const CHAR character)
	{
		if (IsReady() && CanWrite())
		{
			F_fputc(character, m_file);
			WriteNewLine();
		}

		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator<<(LPCSTR text)
	{
		if (IsReady())
		{
			CDECL_3(int, 0x61A031, m_file, "%s", text);			
			WriteNewLine();
		}

		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator<<(const H3String& str)
	{
		if (IsReady() && str.String() && str.Length())
		{
			F_fwrite(str.String(), 1, str.Length(), m_file);
			WriteNewLine();
		}

		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator>>(H3String& line)
	{
		line.Truncate(0);

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
				line.Assign((PCHAR)start, len);
		}
		return *this;
	}
	_H3API_	H3Stream& H3Stream::operator>>(H3Vector<H3String>& lines)
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
	_H3API_	BOOL H3Stream::ReadFile(DWORD size_to_read)
	{
		if (!IsReady() || !CanRead())
			return FALSE;

		const DWORD sz = std::min(m_size, size_to_read);

		if (m_buffer_size < sz)
		{
			delete m_buffer;
			m_buffer_size = sz;
			m_buffer = static_cast<PBYTE>(F_calloc(m_buffer_size));
		}

		m_buffer_position = 0;

		return F_fread(m_buffer, 1, m_buffer_size, m_file) == m_buffer_size;
	}
	_H3API_	LPCSTR H3Stream::GetModeFormat()
	{
		switch (m_mode)
		{
		case StreamMode::SM_READ:
			return "r";
		case StreamMode::SM_READ_BINARY:
			return "rb";
		case StreamMode::SM_WRITE:
			return "w";
		case StreamMode::SM_WRITE_BINARY:
			return "wb";
		case StreamMode::SM_APPEND:
			return "a";
		case StreamMode::SM_APPEND_BINARY:
			return "ab";
		case StreamMode::SM_READ_UPDATE:
			return "r+";
		case StreamMode::SM_READ_UPDATE_BINARY:
			return "r+b";
		case StreamMode::SM_WRITE_UPDATE:
			return "w+";
		case StreamMode::SM_WRITE_UPDATE_BINARY:
			return "w+b";
		case StreamMode::SM_APPEND_UPDATE:
			return "a+";
		case StreamMode::SM_APPEND_UPDATE_BINARY:
			return "a+b";
		default:
			return nullptr;
		}
	}
	_H3API_	VOID H3Stream::WriteNewLine()
	{
		if (m_write_new_lines)
			endl();
	}
	_H3API_	BOOL H3Stream::CanWrite()
	{
		return int(m_mode) & (MV_WRITE | MV_APPEND | MV_UPDATE);
	}
	_H3API_	BOOL H3Stream::CanRead()
	{
		return int(m_mode) & (MV_READ | MV_UPDATE);
	}
}