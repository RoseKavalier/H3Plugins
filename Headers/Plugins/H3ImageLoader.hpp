#ifndef _H3IMAGELOADER_HPP_
#define _H3IMAGELOADER_HPP_

#pragma once

#include "../H3Base.h"
#include "../H3Functions.h"

namespace H3Plugin
{
	namespace ImageLoader
	{
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