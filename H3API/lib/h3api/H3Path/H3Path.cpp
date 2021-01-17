//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-05-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Path.hpp"
#include "H3Path.inl"
#include "../H3_Functions.hpp"

namespace h3
{
    _H3API_ H3Path::iterator::iterator(const H3String & filename) :
        m_handle(FindFirstFileA(filename.String(), &m_data))
    {
    }
    _H3API_ H3Path::iterator::iterator(HANDLE handle) :
        m_handle(handle), m_data()
    {
    }
    _H3API_ H3Path::iterator::~iterator()
    {
        if (m_handle && m_handle != INVALID_HANDLE_VALUE)
            FindClose(m_handle);
    }
    _H3API_ H3Path::iterator& H3Path::iterator::operator*()
    {
        return *this;
    }
    _H3API_ H3Path::iterator& H3Path::iterator::operator++()
    {
        if (m_handle && m_handle != INVALID_HANDLE_VALUE)
        {
            if (!FindNextFileA(m_handle, &m_data))
            {
                FindClose(m_handle);
                m_handle = INVALID_HANDLE_VALUE;
            }
        }
        return *this;
    }
    _H3API_ LPCSTR H3Path::iterator::Extension() const
    {
        return H3Path::Extension(m_data.cFileName);
    }
    _H3API_ H3String H3Path::iterator::FilePath() const
    {
        return GetPathName(FileName());
    }
    _H3API_ LPCSTR H3Path::iterator::FileName() const
    {
        return m_data.cFileName;
    }
    _H3API_ DWORD H3Path::iterator::Attributes() const
    {
        return m_data.dwFileAttributes;
    }
    _H3API_ DWORD H3Path::iterator::FilseSize() const
    {
        return m_data.nFileSizeLow;
    }
    _H3API_ BOOL H3Path::iterator::IsDirectory() const
    {
        return H3Path::IsDirectory(Attributes());
    }
    _H3API_ BOOL H3Path::iterator::IsFile() const
    {
        return H3Path::IsFile(Attributes());
    }

    _H3API_ BOOL H3Path::iterator::IsValid() const
    {
        return H3Path::IsValid(Attributes());
    }

    _H3API_ BOOL H3Path::iterator::FileExists() const
    {
        return H3Path::FileExists(Attributes());
    }

    _H3API_ BOOL H3Path::iterator::operator==(const iterator & other) const
    {
        if (this == &other)
            return TRUE;
        return m_handle == other.m_handle;
    }

    _H3API_ BOOL H3Path::iterator::operator!=(const iterator & other) const
    {
        return !(*this == other);
    }

    _H3API_ BOOL H3Path::IsDirectory(LPCSTR name)
    {
        return IsDirectory(GetAttributes(name));
    }
    _H3API_ BOOL H3Path::IsFile(LPCSTR name)
    {
        return IsFile(GetAttributes(name));
    }
    _H3API_ BOOL H3Path::IsValid(LPCSTR name)
    {
        return IsValid(GetAttributes(name));
    }
    _H3API_ BOOL H3Path::FileExists(LPCSTR name)
    {
        return FileExists(GetAttributes(name));
    }
    _H3API_ BOOL H3Path::IsDirectory(DWORD attribute)
    {
        return IsValid(attribute) && attribute & FILE_ATTRIBUTE_DIRECTORY;
    }
    _H3API_ BOOL H3Path::IsFile(DWORD attribute)
    {
        return IsValid(attribute) && !(attribute & FILE_ATTRIBUTE_DIRECTORY);
    }
    _H3API_ BOOL H3Path::IsValid(DWORD attribute)
    {
        return attribute != INVALID_FILE_ATTRIBUTES;
    }
    _H3API_ BOOL H3Path::FileExists(DWORD attribute)
    {
        return IsValid(attribute) && (attribute & FILE_ATTRIBUTE_ARCHIVE);
    }
    _H3API_ DWORD H3Path::GetAttributes(LPCSTR name)
    {
        return GetFileAttributesA(name);
    }
    _H3API_ H3String H3Path::CurrentDirectory()
    {
        char tmp[MAX_PATH];
        if (GetCurrentDirectoryA(MAX_PATH, tmp))
        {
            H3String dir(tmp);
            dir += '\\';
            return dir;
        }
        return H3String();
    }
    _H3API_ H3String H3Path::ProcessPath()
    {
        return ModulePath(NULL);
    }
    _H3API_ H3String H3Path::ModulePath(HMODULE hmodule)
    {
        char tmp[MAX_PATH];
        if (GetModuleFileNameA(hmodule, tmp, MAX_PATH))
        {
            H3String path(tmp);
            return GetDir(path);
        }
        return H3String();
    }
    _H3API_ H3String H3Path::GetDir(const H3String & path)
    {
        if (path.Empty() || path.Length() < 3)
            return H3String();

        INT32 len = path.Length() - 1;

        while (len >= 3)
        {
            if (path[len] == '/' || path[len] == '\\')
                return H3String(path.String(), len + 1);

            --len;
        }
        return H3String();
    }
    _H3API_ H3String H3Path::DirUp(const H3String & dir)
    {
        if (dir.Empty() || dir.Length() < 3)
            return H3String();

        INT32 len = dir.Length() - 1;
        BOOL first = TRUE;
        while (len >= 3)
        {
            if (dir[len] == '/' || dir[len] == '\\')
            {
                if (!first)
                    return H3String(dir.String(), len + 1);
                first = FALSE;
            }
            --len;
        }
        return H3String();
    }
    _H3API_ BOOL H3Path::CreateDir(const H3String & dir)
    {
        if (dir.Empty())
            return false;

        if (CreateDirectoryA(dir.String(), 0))
            return true;

        if (!CreateDir(DirUp(dir))) // recursively create upper directories
            return false;

        return CreateDirectoryA(dir.String(), 0);
    }

    _H3API_ H3DirectoryChanger::H3DirectoryChanger(LPCSTR dir) :
#ifdef _H3API_CPLUSPLUS11_
        m_oldDir(std::move(H3Path::CurrentDirectory())),
#else
        m_oldDir(H3Path::CurrentDirectory()),
#endif
        m_status()
    {
        if (!m_oldDir.Empty())
            m_status = SetCurrentDirectoryA(dir);
    }
    _H3API_ H3DirectoryChanger::~H3DirectoryChanger()
    {
        if (!m_oldDir.Empty())
            SetCurrentDirectoryA(m_oldDir.String());
    }
    _H3API_ BOOL H3DirectoryChanger::Status() const
    {
        return m_status;
    }

    _H3API_ H3String H3Path::GetPathName(const H3String& file)
    {
        return GetPathName(file.String());
    }

    _H3API_ H3String H3Path::GetPathName(LPCSTR file)
    {
        char tmp[MAX_PATH + 1];
        if (GetFullPathNameA(file, MAX_PATH, tmp, NULL))
            return H3String(tmp);
        return H3String();
    }

    _H3API_ LPCSTR H3Path::Extension(LPCSTR file_name)
    {
        UINT32 length, len;
        length = len = strlen(file_name);
        if (len == 0)
            return file_name;
        --len;
        while (len > 0)
        {
            if (file_name[len] == '.')
                return file_name + len + 1;
            --len;
        }
        return file_name + length;
    }

    _H3API_ LPCSTR H3Path::Extension(const H3String& file_name)
    {
        UINT32 len = file_name.Length();
        if (len == 0)
            return file_name.String();
        --len;
        while (len > 0)
        {
            if (file_name[len] == '.')
                return file_name.String() + len - 1;
            --len;
        }
        return file_name.String() + len;
    }

    _H3API_ H3Path::H3Path(const H3Path& path) :
        m_path(path.m_path), m_attributes(path.m_attributes)
    {
    }
    _H3API_ H3Path::H3Path(const H3String & path) :
        m_path(path), m_attributes(GetAttributes(path.String()))
    {
        if (IsDirectory())
        {
            CHAR last = m_path.Last();
            if (last != '/' && last != '\\')
                m_path += '/';
        }
    }
    _H3API_ H3Path::H3Path(LPCSTR path) :
        m_path(path), m_attributes(GetAttributes(path))
    {
    }
#ifdef _H3API_CPLUSPLUS11_
    _H3API_ H3Path::H3Path(H3Path&& path) :
        m_path(std::move(path.m_path)), m_attributes(path.m_attributes)
    {
    }
    _H3API_ H3Path & H3Path::operator=(H3Path && path)
    {
        m_path.Dereference();
        m_path = std::move(path.m_path);
        m_attributes = path.m_attributes;
        return *this;
    }
#endif
    _H3API_ H3Path::iterator H3Path::begin() const
    {
        if (IsDirectory())
        {
            H3String p(m_path);
            p += '*';
            return iterator(p);
        }
        return iterator(m_path);
    }
    _H3API_ H3Path::iterator H3Path::end() const
    {
        return iterator(INVALID_HANDLE_VALUE);
    }
    _H3API_ H3Path & H3Path::operator=(const H3Path & path)
    {
        m_path.Dereference();
        m_path = path.m_path;
        m_attributes = path.m_attributes;
        return *this;
    }
    _H3API_ H3Path & H3Path::operator+=(const H3Path & path)
    {
        m_path += path.m_path;
        m_attributes = GetAttributes(m_path.String());
        return *this;
    }
    _H3API_ H3Path H3Path::operator/(const H3Path & path)
    {
        H3String tmp(m_path);
        if (!(tmp.Last() == '/' || tmp.Last() == '\\'))
            tmp += '/';
        tmp += path.m_path;
        return H3Path(tmp);
    }
    _H3API_ H3Path & H3Path::operator/=(const H3Path & path)
    {
        if (!(m_path.Last() == '/' || m_path.Last() == '\\'))
            m_path += '/';
        m_path += path.m_path;
        m_attributes = GetAttributes(m_path.String());
        return *this;
    }
    _H3API_ BOOL H3Path::operator!=(const H3Path & path) const
    {
        return !(m_path == path.m_path);
    }
    _H3API_ BOOL H3Path::operator==(const H3Path & path) const
    {
        return m_path == path.m_path;
    }
    _H3API_ H3Path & H3Path::Append(const H3Path & path)
    {
        return operator/=(path);
    }
    _H3API_ BOOL H3Path::IsValid() const
    {
        return IsValid(m_attributes);
    }
    _H3API_ BOOL H3Path::IsDirectory() const
    {
        return IsDirectory(m_attributes);
    }
    _H3API_ BOOL H3Path::IsFile() const
    {
        return IsFile(m_attributes);
    }
    _H3API_ BOOL H3Path::IsRoot() const
    {
        if (m_path.Length() == 1 && m_path[0] == '/')
            return true;
        return m_path.Length() == 3 && m_path[1] == ':';
    }
    _H3API_ BOOL H3Path::CreateDir() const
    {
        return CreateDir(m_path);
    }
    _H3API_ BOOL H3Path::FileExists() const
    {
        return FileExists(m_attributes);
    }
    _H3API_ BOOL H3Path::ReplaceExtension(const H3String & ext)
    {
        if (ext.Empty())
            return FALSE;

        H3String currExt = GetExtension();
        if (currExt.Empty())
            return FALSE;
        INT dot = 0;
        if (ext[0] == '.')
            dot = 1;
        m_path.SetLength(m_path.Length() - currExt.Length() - dot);
        m_path += ext;
        return TRUE;
    }
    _H3API_ H3String H3Path::GetExtension() const
    {
        if (!IsFile())
            return H3String();

        INT32 pos = m_path.FindLastOf('.');
        if (pos == H3String::npos)
            return H3String();

        return H3String(m_path.String() + pos + 1);
    }
    _H3API_ const H3String& H3Path::GetPath() const
    {
        return m_path;
    }
    _H3API_ H3Path::operator LPCSTR() const
    {
        return m_path.String();
    }

    _H3API_ H3DirectoryChanger::H3DirectoryChanger(const H3String& dir) :
#ifdef _H3API_CPLUSPLUS11_
        m_oldDir(std::move(H3Path::CurrentDirectory())),
#else
        m_oldDir(H3Path::CurrentDirectory()),
#endif
        m_status()
    {
        if (!m_oldDir.Empty())
            m_status = SetCurrentDirectoryA(dir.String());
    }

    _H3API_ H3DirectoryChanger::H3DirectoryChanger(const H3Path& dir)  :
#ifdef _H3API_CPLUSPLUS11_
        m_oldDir(std::move(H3Path::CurrentDirectory())),
#else
        m_oldDir(H3Path::CurrentDirectory()),
#endif
        m_status()
    {
        if (!m_oldDir.Empty())
            m_status = SetCurrentDirectoryA(dir.GetPath().String());
    }

    _H3API_ H3DirectoryTraveler::iterator::iterator() :
        m_handle(INVALID_HANDLE_VALUE), m_data(), m_parent()
    {
    }

    _H3API_ H3DirectoryTraveler::iterator::iterator(LPCSTR filename, H3DirectoryTraveler* parent) :
        m_handle(FindFirstFileA(filename, &m_data)), m_parent(parent)
    {
    }

    _H3API_ H3DirectoryTraveler::iterator::~iterator()
    {
        if (m_handle && m_handle != INVALID_HANDLE_VALUE)
            FindClose(m_handle);
    }

    _H3API_ H3DirectoryTraveler::iterator& H3DirectoryTraveler::iterator::operator++()
    {
        while (!next())
        {
            if (!m_handle || m_handle == INVALID_HANDLE_VALUE)
                break;
        }
        return *this;
    }

    _H3API_ H3DirectoryTraveler::iterator& H3DirectoryTraveler::iterator::operator*()
    {
        return *this;
    }

    _H3API_ LPCSTR H3DirectoryTraveler::iterator::Extension() const
    {
        return H3Path::Extension(m_data.cFileName);
    }

    _H3API_ H3String H3DirectoryTraveler::iterator::FilePath() const
    {
        return H3Path::GetPathName(FileName());
    }

    _H3API_ LPCSTR H3DirectoryTraveler::iterator::FileName() const
    {
        return m_data.cFileName;
    }

    _H3API_ DWORD H3DirectoryTraveler::iterator::Attributes() const
    {
        return m_data.dwFileAttributes;
    }

    _H3API_ DWORD H3DirectoryTraveler::iterator::FilseSize() const
    {
        return m_data.nFileSizeLow;
    }

    _H3API_ BOOL H3DirectoryTraveler::iterator::IsDirectory() const
    {
        return H3Path::IsDirectory(Attributes());
    }

    _H3API_ BOOL H3DirectoryTraveler::iterator::IsFile() const
    {
        return H3Path::IsFile(Attributes());
    }

    _H3API_ BOOL H3DirectoryTraveler::iterator::IsValid() const
    {
        return H3Path::IsValid(Attributes());
    }

    _H3API_ BOOL H3DirectoryTraveler::iterator::FileExists() const
    {
        return H3Path::FileExists(Attributes());
    }

    _H3API_ BOOL8 H3DirectoryTraveler::iterator::operator==(const iterator& other) const
    {
        if (this == &other)
            return TRUE;
        return m_handle == other.m_handle;
    }

    _H3API_ BOOL8 H3DirectoryTraveler::iterator::operator!=(const iterator& other) const
    {
        return !(*this == other);
    }

    _H3API_ BOOL32 H3DirectoryTraveler::iterator::isNotRelativeDir() const
    {
        return strcmp(FileName(), ".") && strcmp(FileName(), "..");
    }

    _H3API_ BOOL32 H3DirectoryTraveler::iterator::next()
    {
        if (!m_handle || m_handle == INVALID_HANDLE_VALUE)
            return FALSE;

        if (!FindNextFileA(m_handle, &m_data))
        {
            if (m_parent->remainingDirectories())
            {
                FindClose(m_handle);
                m_handle = m_parent->nextDirectoryIteration(m_data);
            }
            else
            {
                FindClose(m_handle);
                m_handle = INVALID_HANDLE_VALUE;
                return false;
            }
        }
        if (IsDirectory() && isNotRelativeDir())
            m_parent->addDirectory(FileName());

        if (m_parent->m_type.Empty())
            return TRUE;
        return m_parent->m_type.Equals_i(Extension());
    }

    _H3API_ H3DirectoryTraveler::H3DirectoryTraveler(const H3String& file_type /*= ""*/, INT32 max_depth /*= -1*/) :
        m_startDirectory(H3Path::CurrentDirectory()), m_type(file_type), m_directories(), m_index(0u), m_nextDepthIndex(1u), m_maxDepth(max_depth)
    {
        m_directories.Add(m_startDirectory);
    }

    _H3API_ H3DirectoryTraveler::H3DirectoryTraveler(const H3Path& directory, const H3String& file_type, INT32 max_depth) :
        m_startDirectory(H3Path::CurrentDirectory()), m_type(file_type), m_directories(), m_index(0u), m_nextDepthIndex(1u), m_maxDepth(max_depth)
    {
        if (directory.IsDirectory())
        {
            m_directories.Add(directory.GetPath());
            setDirectory(directory.GetPath());
        }
    }

    _H3API_ H3DirectoryTraveler::~H3DirectoryTraveler()
    {
        if (!m_directories.IsEmpty())
            setDirectory(m_startDirectory);
    }

    _H3API_ H3DirectoryTraveler::iterator H3DirectoryTraveler::begin()
    {
        if (m_directories.IsEmpty())
            return iterator();
        return iterator("*", this);
    }

    _H3API_ H3DirectoryTraveler::iterator H3DirectoryTraveler::end()
    {
        return iterator();
    }

    _H3API_ H3String& H3DirectoryTraveler::currentDir() const
    {
        return m_directories[m_index];
    }

    _H3API_ BOOL32 H3DirectoryTraveler::remainingDirectories() const
    {
        return m_directories.Size() > m_index + 1;
    }

    _H3API_ BOOL32 H3DirectoryTraveler::setDirectory(const H3String& directory)
    {
        return SetCurrentDirectoryA(directory.String());
    }

    _H3API_ VOID H3DirectoryTraveler::addDirectory(LPCSTR filename)
    {
        if (m_maxDepth == 0)
            return;
        m_directories.Add(currentDir() + '\\' + filename);
    }

    _H3API_ VOID H3DirectoryTraveler::decreaseDepth()
    {
        if (m_maxDepth > 0)
            --m_maxDepth;
    }

    _H3API_ VOID H3DirectoryTraveler::newDepthCheck()
    {
        if (m_index >= m_nextDepthIndex)
        {
            m_nextDepthIndex = m_directories.Size();
            decreaseDepth();
        }
    }

    _H3API_ HANDLE H3DirectoryTraveler::nextDirectoryIteration(WIN32_FIND_DATAA& data)
    {
        ++m_index;
        newDepthCheck();
        if (!setDirectory(currentDir()))
            return INVALID_HANDLE_VALUE;
        return FindFirstFileA("*", &data);
    }

}