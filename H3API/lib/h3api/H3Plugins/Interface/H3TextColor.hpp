#ifndef _H3TEXTCOLOR_HPP_
#define _H3TEXTCOLOR_HPP_

#include "../../H3_Base.hpp"
#include "../../H3_String.hpp"
#include "../../H3_Vector.hpp"

namespace h3
{
	namespace H3Plugin
	{
		namespace TextColor
		{
			LPCSTR const TextColorPluginName = "H3.TextColor.dll";

			// * This virtual class can be accessed
			// * by calling H3Plugin::TextColor::GetTextColor();
			class H3TextColorInformation
			{
			public:

				// * Returns the number of colors currently
				// * available to modify the text's appearance
				virtual UINT GetNumberColors() = 0;

				// * returns a vector of H3Strings with names of colors
				virtual const H3Vector<H3String>* GetColorNames() = 0;

				// * empties the vector of H3Strings with color names
				virtual VOID DeleteColorNames() = 0;

				// * Adds a color dynamically.
				// * Duplicate names are not allowed
				// * but duplicate colors are accepted.
				virtual VOID AddColor(LPCSTR name, UINT8 red, UINT8 green, UINT8 blue) = 0;

				// * Adds a color dynamically.
				// * Duplicate names are not allowed
				// * but duplicate colors are accepted.
				VOID AddColor(LPCSTR name, DWORD rgb_color) { AddColor(name, (rgb_color >> 16) & 0xFF, (rgb_color >> 8) & 0xFF, rgb_color & 0xFF); }
			};

			inline H3TextColorInformation * GetTextColor()
			{
				static BOOL called = FALSE;
				if (called)
					return nullptr;
				if (HMODULE h = LoadLibraryA(TextColorPluginName))
				{
					if (FARPROC f = GetProcAddress(h, "GetTextColor_"))
					{
						called = TRUE;
						return reinterpret_cast<H3TextColorInformation*(__stdcall *)()>(f)();
					}
				}
				return nullptr;
			}
		}
	}
}

#endif /* #define _H3TEXTCOLOR_HPP_ */