//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3STREAM_HPP_
#define _H3STREAM_HPP_

#include "../H3_Base.hpp"
#include "../H3_String.hpp"
#include "../H3_Vector.hpp"

namespace h3
{
	// * read / write files using H3 fwrite() assets
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
		_H3API_ENUM_ StreamMode
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
		_H3API_ENUM_ StreamStatus
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

#ifdef _H3API_CPLUSPLUS11_
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

		_H3API_ LPCSTR getModeFormat();
		template<typename T>
		inline VOID printf(LPCSTR format, T value);
		_H3API_ VOID writeNewLine();
		_H3API_ BOOL canWrite();
		_H3API_ BOOL canRead();
	};

	// * read/write using CreateFile (not h3 CreateFile due to HDmod hooks)
	class H3File
	{
	protected:
		HANDLE m_handle;
		DWORD  m_fileSize;
		PBYTE  m_buffer;
		DWORD  m_pointer;
		HANDLE m_save;

		_H3API_ void getSize();
		_H3API_ void clear();
		_H3API_ void close();
		_H3API_ BOOL read(const PVOID buffer, DWORD sizeToRead);
		_H3API_ BOOL write(const PVOID buffer, DWORD sizeToWrite);
		_H3API_ BOOL exists(LPCSTR filepath);
	public:
		_H3API_ H3File();
		_H3API_ ~H3File();
		_H3API_ VOID Close();

		// * to read
		_H3API_ BOOL Open(LPCSTR const file);
		_H3API_ BOOL Read(const PVOID buffer, DWORD sizeToRead);
		_H3API_ BOOL ReadToBuffer(); // read whole file to memory
		_H3API_ H3String GetLine();
		_H3API_ H3Vector<H3String> GetLines(BOOL includeEmptyLines = FALSE);
		_H3API_ BOOL Read(PVOID data, size_t data_len);
		template<typename T>
		inline  BOOL Read(const T& data);
		_H3API_ BOOL SetPointer(UINT pos);
		_H3API_ UINT Pointer() const;
		_H3API_ BOOL Skip(UINT numBytes);
		_H3API_ const PBYTE Buffer() const;
		_H3API_ PBYTE ReleaseBuffer();
		_H3API_ PBYTE begin();
		_H3API_ PBYTE end();
		_H3API_ UINT Size() const;

		// * to write
		_H3API_ BOOL Save(LPCSTR const file);
		_H3API_ BOOL Write(PVOID data, size_t data_len);
		_H3API_ BOOL Write(const H3String& string);
		template<typename T>
		inline BOOL Write(const T& data);
	};

	/**
	 * @brief writes a text file following h3 format (viewable with TxtEdit).
	 * The '\r' and '\t' characters are reserved for cell / line delimitations, avoid their use whenever possible
	 */
	class H3SpreadSheet
	{
	public:
		/**
		 * @brief clears the contents of the spreadsheet
		 */
		_H3API_ VOID Clear();
		/**
		 * @brief inserts the current text and adds a new line
		 */
		_H3API_ VOID NewLine();
		/**
		 * @brief insert an empty column at current location
		 */
		_H3API_ VOID NewColumn();
		/**
		 * @brief unsigned integers will be printed in hexadecimal format
		 */
		_H3API_ H3SpreadSheet& Hex();
		/**
		 * @brief unsigned integers will be printed in decimal format
		 */
		_H3API_ H3SpreadSheet& Dec();
		/**
		 * @brief save the spreadsheet's contents to specifield file name. The contents are then cleared
		 */
		_H3API_ BOOL Save(LPCSTR const file);
		/**
		 * @brief insert a line at specified row
		 */
		_H3API_ BOOL InsertLine(const H3String& line, UINT row = static_cast<UINT>(-1));
		/**
		 * @brief passing a H3SpreadSheet does nothing, only useful to modify Hex/Dec modes in a << chain
		 */
		_H3API_ H3SpreadSheet& operator<<(const H3SpreadSheet&);
		/**
		 * @brief insert text and start a new column
		 */
		_H3API_ H3SpreadSheet& operator<<(LPCSTR text);
		/**
		 * @brief insert an integer and start a new column
		 */
		_H3API_ H3SpreadSheet& operator<<(INT32 value);
		/**
		 * @brief insert an unsigned integer and start a new column. May be hexadecimal with Hex() method
		 */
		_H3API_ H3SpreadSheet& operator<<(UINT32 value);
		/**
		 * @brief insert a floating integer and start a new column
		 */
		_H3API_ H3SpreadSheet& operator<<(FLOAT value);
		/**
		 * @brief insert a double value and start a new column
		 */
		_H3API_ H3SpreadSheet& operator<<(DOUBLE value);
		/**
		 * @brief insert a single character and start a new column
		 */
		_H3API_ H3SpreadSheet& operator<<(CHAR ch);
		/**
		 * @brief insert a string and start a new column
		 */
		_H3API_ H3SpreadSheet& operator<<(const H3String& line);
	private:
		_H3API_ VOID addTab();

		H3String           m_currentLine;
		H3Vector<H3String> m_lines;
		BOOL               m_hexMode;
	};
}

#endif /* #define _H3STREAM_HPP_ */