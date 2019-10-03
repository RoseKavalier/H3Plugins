#ifndef _H3IMAGELOADER_HPP_
#define _H3IMAGELOADER_HPP_

#pragma once

#include "../H3Base.h"

namespace H3Plugin
{
	namespace ImageLoader
	{
		// * follows the format of H3 PCX files with indexed palette
		// * as they appear when read from LOD archives
		class H3PCX8
		{
			UINT32 m_size;
			UINT32 m_width;
			UINT32 m_height;
			// * UINT8 pixels[m_height][m_width];
			// * H3RGB888 palette[256];
		public:
			const PUINT8    Pixels()             const { return PUINT8(this) + sizeof(*this); }
			const UINT8     Pixels(INT x, INT y) const { return ByteAt(Pixels() + m_width * y + x); }
			const H3RGB888* Palette()            const { return (H3RGB888*)(Pixels() + m_size); }
			const H3RGB888* Color(INT x, INT y)  const { return &Palette()[Pixels(x, y)]; }
			const BOOL      IsIndexed()          const { return m_width * m_height == m_size; }
			const UINT32    Height()             const { return m_height; }
			const UINT32    Width()              const { return m_width; }
			const UINT32    Size()               const { return m_size; }
		};
		// * follows the format of H3 PCX files without index
		// * as they appear when read from LOD archives
		class H3PCX24
		{
			UINT32 m_size;
			UINT32 m_width;
			UINT32 m_height;
			// * H3RGB888 pixels[m_height][m_width];
		public:
			const H3RGB888* Pixels()             const { return (H3RGB888*)(PUINT8(this) + sizeof(*this)); }
			const H3RGB888* Pixels(INT x, INT y) const { return Pixels() + m_width * y + x; }
			const BOOL      RGBFormat()          const { return m_width * m_height * 3 == m_size; }
			const UINT32    Height()             const { return m_height; }
			const UINT32    Width()              const { return m_width; }
			const UINT32    Size()               const { return m_size; }
		};


		LPCSTR const ImageLoaderPluginName = "H3.ImageLoader.dll";

		// * This virtual class can be accessed
		// * by calling H3Plugin::ImageLoader::GetImageLoader();
		class H3ImageLoader
		{
		public:
			// * the number of images added by the plugin so far
			virtual INT NumberAdded() = 0;

			// * returns the last error
			virtual LPCSTR GetLastError() = 0;

			// * DOES NOT SUPPORT TRANSPARENCY
			// * @filepath - the complete path to the image you are looking to load
			// * @h3name - the name to use within the H3 assets (to recuperate the image later)
			// * @width and @height are optional, but can be used to resize the image
			virtual H3LoadedPCX16* LoadImageToPcx16(LPCSTR filepath, LPCSTR h3name, INT width = -1, INT height = -1) = 0;

			// * DOES NOT SUPPORT TRANSPARENCY
			// * @filepath - the complete path to the image you are looking to load
			// * @h3name - the name to use within the H3 assets (to recuperate the image later)
			// * @width and @height are optional, but can be used to resize the image
			H3LoadedPCX16* LoadImageToPcx16(const H3String filepath, LPCSTR h3name, INT width = -1, INT height = -1) { return LoadImageToPcx16(filepath.String(), h3name, width, height); }
			// * DOES NOT SUPPORT TRANSPARENCY
			// * @filepath - the complete path to the image you are looking to load
			// * @h3name - the name to use within the H3 assets (to recuperate the image later)
			// * @width and @height are optional, but can be used to resize the image
			H3LoadedPCX16* LoadImageToPcx16(const H3String filepath, const H3String h3name, INT width = -1, INT height = -1) { return LoadImageToPcx16(filepath.String(), h3name.String(), width, height); }
			// * DOES NOT SUPPORT TRANSPARENCY
			// * @filepath - the complete path to the image you are looking to load
			// * @h3name - the name to use within the H3 assets (to recuperate the image later)
			// * @width and @height are optional, but can be used to resize the image
			H3LoadedPCX16* LoadImageToPcx16(LPCSTR filepath, const H3String h3name, INT width = -1, INT height = -1) { return LoadImageToPcx16(filepath, h3name.String(), width, height); }

		};

		inline H3ImageLoader * GetImageLoader()
		{
			static BOOL called = FALSE;
			if (called)
				return NULL;
			if (HMODULE h = LoadLibraryA(ImageLoaderPluginName))
			{
				if (FARPROC f = GetProcAddress(h, "GetImageLoader_"))
				{
					called = TRUE;
					return ((H3ImageLoader*(__stdcall *)(void))f)();
				}
			}
			return NULL;
		}
	}
}




#endif /* #define _H3IMAGELOADER_HPP_ */