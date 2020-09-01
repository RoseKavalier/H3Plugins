//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-05-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3PATH_HPP_
#define _H3PATH_HPP_

#include "../H3_Base.hpp"
#include "../H3_String.hpp"

namespace h3
{
	class H3Path
	{
	public:
		_H3API_ static BOOL     IsDirectory(LPCSTR name);
		_H3API_ static BOOL     IsDirectory(DWORD attribute);
		_H3API_ static BOOL     IsFile(LPCSTR name);
		_H3API_ static BOOL     IsFile(DWORD attribute);
		_H3API_ static BOOL     IsValid(LPCSTR name);
		_H3API_ static BOOL     IsValid(DWORD attribute);
		_H3API_ static BOOL     FileExists(LPCSTR name);
		_H3API_ static BOOL     FileExists(DWORD attribute);
		_H3API_ static BOOL     CreateDir(const H3String& dir);
		_H3API_ static DWORD    GetAttributes(LPCSTR name);
		_H3API_ static H3String CurrentDirectory();
		_H3API_ static H3String ProcessPath();
		_H3API_ static H3String ModulePath(HMODULE hmodule);
		_H3API_ static H3String GetDir(const H3String& path);
		_H3API_ static H3String DirUp(const H3String& dir);

		class iterator
		{
		public:
			_H3API_ iterator(const H3String& filename);
			_H3API_ iterator(HANDLE handle);
			_H3API_ ~iterator();
			_H3API_ iterator& operator*();
			_H3API_ iterator& operator++();
			_H3API_ LPCSTR    Extension() const;
			_H3API_ H3String  FilePath() const;
			_H3API_ LPCSTR    FileName() const;
			_H3API_ DWORD     Attributes() const;
			_H3API_ DWORD     FilseSize() const;
			_H3API_ BOOL      IsDirectory() const;
			_H3API_ BOOL      IsFile() const;
			_H3API_ BOOL      IsValid() const;
			_H3API_ BOOL      FileExists() const;
			_H3API_ BOOL      operator==(const iterator& other) const;
			_H3API_ BOOL      operator!=(const iterator& other) const;
		private:
			HANDLE m_handle;
			WIN32_FIND_DATAA m_data;
		};

	public:
		_H3API_ H3Path(const H3Path& path);
		_H3API_ H3Path(const H3String& path);
		_H3API_ H3Path(LPCSTR path);

#ifdef _H3API_CPLUSPLUS11_
		_H3API_ H3Path(H3Path&& path);
		_H3API_ H3Path& operator=(H3Path&& path);
#endif
		_H3API_ iterator begin() const;
		_H3API_ iterator end() const;

		_H3API_ H3Path&  operator=(const H3Path& path);
		_H3API_ H3Path&  operator+=(const H3Path& path);
		_H3API_ H3Path   operator/(const H3Path& path);
		_H3API_ H3Path&  operator/=(const H3Path& path);
		_H3API_ BOOL     operator!=(const H3Path& path) const;
		_H3API_ BOOL     operator==(const H3Path& path) const;
		_H3API_ H3Path&  Append(const H3Path& path);
		_H3API_ BOOL     IsValid() const;
		_H3API_ BOOL     IsDirectory() const;
		_H3API_ BOOL     IsFile() const;
		_H3API_ BOOL     IsRoot() const;
		_H3API_ BOOL     CreateDir() const;
		_H3API_ BOOL     FileExists() const;
		_H3API_ BOOL     ReplaceExtension(const H3String& ext);
		_H3API_ H3String GetExtension() const;
		_H3API_ operator LPCSTR() const;
		_H3API_ const H3String& GetPath() const;
	private:
		H3String m_path;
		DWORD    m_attributes;
	};

	class H3DirectoryChanger
	{
	public:
		_H3API_ H3DirectoryChanger(LPCSTR dir);
		_H3API_ ~H3DirectoryChanger();
		_H3API_ BOOL Status() const;
	private:
		H3String m_oldDir;
		BOOL     m_status;
	};
}

#endif /* #define _H3PATH_HPP_ */