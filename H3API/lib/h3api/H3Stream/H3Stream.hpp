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

#ifndef _H3STREAM_HPP_
#define _H3STREAM_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_String.hpp"
#include "../H3_Vector.hpp"

namespace h3
{
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
		_H3ENUM_ StreamMode
		{
			SM_INVALID              = 0,
			/* r */
			SM_READ                 = MV_READ,
			/* rb */
			SM_READ_BINARY          = MV_READ | MV_BINARY,
			/* w */
			SM_WRITE                = MV_WRITE,
			/* wb */
			SM_WRITE_BINARY         = MV_WRITE | MV_BINARY,
			/* a */
			SM_APPEND               = MV_APPEND,
			/* ab */
			SM_APPEND_BINARY        = MV_APPEND | MV_BINARY,
			/* r+ */
			SM_READ_UPDATE          = MV_READ | MV_UPDATE,
			/* r+b */
			SM_READ_UPDATE_BINARY   = SM_READ_UPDATE | MV_BINARY,
			/* w+ */
			SM_WRITE_UPDATE         = MV_WRITE | MV_UPDATE,
			/* w+b */
			SM_WRITE_UPDATE_BINARY  = SM_WRITE_UPDATE | MV_BINARY,
			/* a+ */
			SM_APPEND_UPDATE        = MV_APPEND | MV_UPDATE,
			/* a+b */
			SM_APPEND_UPDATE_BINARY = SM_APPEND_UPDATE | MV_BINARY,
		};
		_H3ENUM_ StreamStatus
		{
			SS_OK,
			SS_NOT_LOADED,
			SS_INVALID,
		};

		_H3API_ H3Stream(LPCSTR filename, StreamMode read_write_mode, BOOL read_to_buffer = FALSE);
		_H3API_ H3Stream(LPCSTR filename, LPCSTR read_write_mode, BOOL read_to_buffer = FALSE);
		_H3API_ ~H3Stream();

		// * set integer write mode to hexadecimal display
		_H3API_ H3Stream& hex();
		// * set integer write mode to decimal display
		// * [default]
		_H3API_ H3Stream& decimal();
		// * the stream will write a new line after each output operation
		_H3API_ H3Stream& new_lines();
		// * the stream will not write a new line after each output operation
		// * [default]
		_H3API_ H3Stream& no_new_lines();
		// * writes a new line
		_H3API_ H3Stream& endl();

		_H3API_ BOOL IsReady() const;
		_H3API_ StreamStatus GetStatus() const;
		_H3API_ StreamMode GetMode() const;

		// * makes a copy of the file to provided destination

		_H3API_ BOOL Copy(LPCSTR destination);
		_H3API_ BOOL Copy(const H3String& destination);

#ifdef _CPLUSPLUS11_
		// * write varying arguments
		template<typename ... Args>
		H3Stream& Write(LPCSTR format, Args ... args);
#else
		// * write varying arguments
		_H3API_ H3Stream& Write(LPCSTR format, ...);
#endif

		// * writes integer
		_H3API_ H3Stream& operator<<(const int number);
		// * writes unsigned integer
		_H3API_ H3Stream& operator<<(const unsigned int number);
		// * writes float
		_H3API_ H3Stream& operator<<(const FLOAT number);
		// * writes double
		_H3API_ H3Stream& operator<<(const DOUBLE number);
		// * writes char
		_H3API_ H3Stream& operator<<(const CHAR character);
		// * writes text string
		_H3API_ H3Stream& operator<<(LPCSTR text);
		// * writes H3string
		_H3API_ H3Stream& operator<<(const H3String& str);
		// * writes pre-defined string of known length
		// * WARNING!!! passing a char buffer[512]
		// * will print **all** of the buffer
		// * use Write() instead
		template<INT32 sz>
		H3Stream& operator<<(const CHAR(&expression)[sz]);
		// * reads a line
		// * and moves m_buffer_position along
		_H3API_ H3Stream& operator>>(H3String& line);
		// * reads all lines
		_H3API_ H3Stream& operator>>(H3Vector<H3String>& lines);

		_H3API_ BOOL ReadFile(DWORD size_to_read);

	protected:
		FILE*        m_file;
		DWORD        m_size;
		StreamMode   m_mode;
		BOOL         m_write_hex;
		BOOL         m_write_new_lines;
		StreamStatus m_status;
		BYTE*        m_buffer;
		DWORD        m_buffer_size;
		DWORD        m_buffer_position;

		_H3API_ LPCSTR GetModeFormat();
		template<typename T>
		inline VOID Printf(LPCSTR format, T value);
		_H3API_ VOID WriteNewLine();
		_H3API_ BOOL CanWrite();
		_H3API_ BOOL CanRead();
	};

}

#endif /* #define _H3STREAM_HPP_ */