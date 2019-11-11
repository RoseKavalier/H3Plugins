#ifndef _H3TEXTCOLOR_HPP_
#define _H3TEXTCOLOR_HPP_

#pragma once

#include "../H3Base.h"

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
			virtual INT GetNumberColors() = 0;

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

			// * Adds a color dynamically.
			// * Duplicate names are not allowed
			// * but duplicate colors are accepted.
			VOID AddColor(H3String& name, UINT8 red, UINT8 green, UINT8 blue) { AddColor(name.String(), red, green, blue); }

			// * Adds a color dynamically.
			// * Duplicate names are not allowed
			// * but duplicate colors are accepted.
			VOID AddColor(H3String& name, DWORD rgb_color) { AddColor(name.String(), rgb_color); }
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

#endif /* #define _H3TEXTCOLOR_HPP_ */