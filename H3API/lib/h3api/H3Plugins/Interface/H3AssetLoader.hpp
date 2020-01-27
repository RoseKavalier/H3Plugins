#ifndef _H3ASSETLOADER_HPP_
#define _H3ASSETLOADER_HPP_

#include "../../H3_Base.hpp"
#include "../../H3_BinaryItems.hpp"

namespace h3
{
	namespace H3Plugin
	{
		namespace AssetLoader
		{
			LPCSTR const ImageLoaderPluginName = "H3.AssetLoader.dll";

			class H3AssetLoader
			{
			public:
				// * the number of assets added by the plugin so far
				virtual INT NumberAdded() = 0;

				// * returns the last error
				virtual LPCSTR GetLastError() = 0;

				// * @filePath - the complete path to the PCX you are looking to load
				// * @h3name - the name of the PCX to load
				virtual H3LoadedPCX* LoadPcxFromFile(LPCSTR const filePath, LPCSTR const h3name) = 0;

				// * @filePath - the complete path to the WAV you are looking to load
				// * @h3name - the name of the WAV to load
				virtual H3WavFile* LoadWavFromFile(LPCSTR const filePath, LPCSTR const h3name) = 0;

				// * @filePath - the complete path to the DEF you are looking to load
				// * @h3name - the name of the DEF to load
				virtual H3LoadedDEF* LoadDefFromFile(LPCSTR const filePath, LPCSTR const h3name) = 0;
			};

			inline H3AssetLoader* GetAssetLoader()
			{
				static BOOL called = FALSE;
				if (called)
					return NULL;
				if (HMODULE h = LoadLibraryA(ImageLoaderPluginName))
				{
					if (FARPROC f = GetProcAddress(h, "GetAssetLoader_"))
					{
						called = TRUE;
						return ((H3AssetLoader*(__stdcall *)(void))f)();
					}
				}
				return NULL;
			}
		} //namespace AssetLoader
	} //namespace H3Plugin
} //namespace h3

#endif /* #define _H3ASSETLOADER_HPP_ */