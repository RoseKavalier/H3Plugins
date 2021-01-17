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

#include "../H3_String.hpp"
#include "../H3_Vector.hpp"

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
		_H3API_ static H3String GetPathName(const H3String& file);
		_H3API_ static H3String GetPathName(LPCSTR file);
		_H3API_ static LPCSTR   Extension(LPCSTR file_name);
		_H3API_ static LPCSTR   Extension(const H3String& file_name);

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
		_H3API_ H3DirectoryChanger(const H3String& dir);
		_H3API_ H3DirectoryChanger(const H3Path& dir);
		_H3API_ ~H3DirectoryChanger();
		_H3API_ BOOL Status() const;
	private:
		H3String m_oldDir;
		BOOL     m_status;
	};

	/**
	 * @brief An iterative, non-recursive class to search for files at a specified depth within directories
	 */
	class H3DirectoryTraveler
	{
	public:
		class iterator
		{
		public:
			_H3API_ iterator();
			_H3API_ iterator(LPCSTR filename, H3DirectoryTraveler* parent);
			_H3API_ ~iterator();

			_H3API_ iterator& operator++();
			_H3API_ iterator& operator*();
			_H3API_ LPCSTR    Extension() const;
			_H3API_ H3String  FilePath() const;
			_H3API_ LPCSTR    FileName() const;
			_H3API_ DWORD     Attributes() const;
			_H3API_ DWORD     FilseSize() const;
			_H3API_ BOOL      IsDirectory() const;
			_H3API_ BOOL      IsFile() const;
			_H3API_ BOOL      IsValid() const;
			_H3API_ BOOL      FileExists() const;
			_H3API_ BOOL8     operator==(const iterator& other) const;
			_H3API_ BOOL8     operator!=(const iterator& other) const;
		protected:
			_H3API_ BOOL32 isNotRelativeDir() const;
			_H3API_ BOOL32 next();

		private:
			HANDLE               m_handle;
			WIN32_FIND_DATAA     m_data;
			H3DirectoryTraveler* m_parent;
		};

		/**
		 * @brief Prepares iteration starting from the current directory.
		 * @param file_type Only iterate over files of this type, e.g. "exe", "dll", "" for any file.
		 * @param max_depth How many directories deep to search, <0 means any depth, 0 only current directory.
		 */
		_H3API_ H3DirectoryTraveler(const H3String& file_type = "", INT32 max_depth = -1);
		/**
		 * @brief Prepares iteration starting from the specified directory.
		 * @param directory The starting directory to search from.
		 * @param file_type Only iterate over files of this type, e.g. "exe", "dll", "" for any file.
		 * @param max_depth How many directories deep to search, <0 means any depth, 0 only current directory.
		 */
		_H3API_ H3DirectoryTraveler(const H3Path& directory, const H3String& file_type, INT32 max_depth);
		_H3API_ ~H3DirectoryTraveler();

		_H3API_ iterator begin();
		_H3API_ iterator end();

	protected:
		_H3API_ H3String& currentDir() const;
		_H3API_ BOOL32    remainingDirectories() const;
		_H3API_ BOOL32    setDirectory(const H3String& directory);
		_H3API_ VOID      addDirectory(LPCSTR filename);
		_H3API_ VOID      decreaseDepth();
		_H3API_ VOID      newDepthCheck();
		_H3API_ HANDLE    nextDirectoryIteration(WIN32_FIND_DATAA& data);
	private:
		H3String           m_startDirectory;
		H3String           m_type;
		H3Vector<H3String> m_directories;
		UINT32             m_index;
		UINT32             m_nextDepthIndex;
		INT32              m_maxDepth;
	};
}

#endif /* #define _H3PATH_HPP_ */