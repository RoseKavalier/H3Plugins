#include "Hooks.h"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

// * global string to store game text
H3String TextParser;
// * the current position from 0 to strlen in TextParser
INT32 CurrentPosition;
// * from mapeditor it seems 30,000 is max possible message length
// * however this will be used to track CharColors size and widen it if need arises
INT32 CharColorsSize = 30000 * sizeof(INT32);
// * an array of colors indexes for each character
PINT32 CharColors;
// * stores name to look out for, RGB color and RGB565 color
H3NamedColors H3CustomColors[] =
{
	{ "r", 0xF80000, Color32To16(0xF80000) }, // shortcut for H3Red palette
	{ "g", 0x00FC00, Color32To16(0x00FC00) }, // shortcut for H3Green palette
	{ "b", 0x0000F8, Color32To16(0x0000F8) }, // shortcut for H3Blue palette
	{ "y", 0xF8FC00, Color32To16(0xF8FC00) }, // shortcut for H3Yellow palette
	{ "o", 0xF88000, Color32To16(0xF88000) }, // shortcut for H3Orange palette
	{ "p", 0xF800F8, Color32To16(0xF800F8) }, // shortcut for H3Purple palette
	{ "c", 0x00FCF8, Color32To16(0x00FCF8) }, // shortcut for H3Cyan palette
	{ "k", 0x000000, Color32To16(0x000000) }, // shortcut for black
	{ "w", 0xFFFFFF, Color32To16(0xFFFFFF) }, // shortcut for white

	{ "Regular", 0xF8F0D8, Color32To16(0xF8F0D8) }, // from H3palette, regular text
	{ "Highlight", 0xE8D478, Color32To16(0xE8D478) }, // from H3palette, {} highlight text
	{ "H3Red", 0xF80000, Color32To16(0xF80000) }, // from H3palette, Red
	{ "H3Cyan", 0x00FCF8, Color32To16(0x00FCF8) }, // from H3Palette, Cyan
	{ "H3Green", 0x00FC00, Color32To16(0x00FC00) }, // from H3palette, Green
	{ "H3Blue", 0x0000F8, Color32To16(0x0000F8) }, // from H3palette, Blue
	{ "H3Yellow", 0xF8FC00, Color32To16(0xF8FC00) }, // from H3palette, Yellow
	{ "H3Orange", 0xF88000, Color32To16(0xF88000) }, // from H3palette, Orange
	{ "H3Purple", 0xF800F8, Color32To16(0xF800F8) }, // from H3palette, Purple
	{ "H3Pink", 0xC07888, Color32To16(0xC07888) }, // from H3palette, Pink

	{ "AliceBlue", 0xF0F8FF, Color32To16(0xF0F8FF) }, // named colors
	{ "AntiqueWhite", 0xFAEBD7, Color32To16(0xFAEBD7) },
	{ "Aqua", 0x00FFFF, Color32To16(0x00FFFF) },
	{ "Aquamarine", 0x7FFFD4, Color32To16(0x7FFFD4) },
	{ "Azure", 0xF0FFFF, Color32To16(0xF0FFFF) },
	{ "Beige", 0xF5F5DC, Color32To16(0xF5F5DC) },
	{ "Bisque", 0xFFE4C4, Color32To16(0xFFE4C4) },
	{ "Black", 0x000000, Color32To16(0x000000) },
	{ "BlanchedAlmond", 0xFFEBCD, Color32To16(0xFFEBCD) },
	{ "Blue", 0x0000FF, Color32To16(0x0000FF) },
	{ "BlueViolet", 0x8A2BE2, Color32To16(0x8A2BE2) },
	{ "Brown", 0xA52A2A, Color32To16(0xA52A2A) },
	{ "BurlyWood", 0xDEB887, Color32To16(0xDEB887) },
	{ "CadetBlue", 0x5F9EA0, Color32To16(0x5F9EA0) },
	{ "Chartreuse", 0x7FFF00, Color32To16(0x7FFF00) },
	{ "Chocolate", 0xD2691E, Color32To16(0xD2691E) },
	{ "Coral", 0xFF7F50, Color32To16(0xFF7F50) },
	{ "CornflowerBlue", 0x6495ED, Color32To16(0x6495ED) },
	{ "Cornsilk", 0xFFF8DC, Color32To16(0xFFF8DC) },
	{ "Crimson", 0xDC143C, Color32To16(0xDC143C) },
	{ "Cyan", 0x00FFFF, Color32To16(0x00FFFF) },
	{ "DarkBlue", 0x00008B, Color32To16(0x00008B) },
	{ "DarkCyan", 0x008B8B, Color32To16(0x008B8B) },
	{ "DarkGoldenRod", 0xB8860B, Color32To16(0xB8860B) },
	{ "DarkGray", 0xA9A9A9, Color32To16(0xA9A9A9) },
	{ "DarkGrey", 0xA9A9A9, Color32To16(0xA9A9A9) },
	{ "DarkGreen", 0xA9A9A9, Color32To16(0xA9A9A9) },
	{ "DarkKhaki", 0x006400, Color32To16(0x006400) },
	{ "DarkMagenta", 0x8B008B, Color32To16(0x8B008B) },
	{ "DarkOliveGreen", 0x556B2F, Color32To16(0x556B2F) },
	{ "Darkorange", 0xFF8C00, Color32To16(0xFF8C00) },
	{ "DarkOrchid", 0x9932CC, Color32To16(0x9932CC) },
	{ "DarkRed", 0x8B0000, Color32To16(0x8B0000) },
	{ "DarkSalmon", 0xE9967A, Color32To16(0xE9967A) },
	{ "DarkSeaGreen", 0x8FBC8F, Color32To16(0x8FBC8F) },
	{ "DarkSlateBlue", 0x483D8B, Color32To16(0x483D8B) },
	{ "DarkSlateGray", 0x2F4F4F, Color32To16(0x2F4F4F) },
	{ "DarkSlateGrey", 0x2F4F4F, Color32To16(0x2F4F4F) },
	{ "DarkTurquoise", 0x00CED1, Color32To16(0x00CED1) },
	{ "DarkViolet", 0x9400D3, Color32To16(0x9400D3) },
	{ "DeepPink", 0xFF1493, Color32To16(0xFF1493) },
	{ "DeepSkyBlue", 0x00BFFF, Color32To16(0x00BFFF) },
	{ "DimGray", 0x696969, Color32To16(0x696969) },
	{ "DimGrey", 0x696969, Color32To16(0x696969) },
	{ "DodgerBlue", 0x1E90FF, Color32To16(0x1E90FF) },
	{ "FireBrick", 0xB22222, Color32To16(0xB22222) },
	{ "FloralWhite", 0xFFFAF0, Color32To16(0xFFFAF0) },
	{ "ForestGreen", 0x228B22, Color32To16(0x228B22) },
	{ "Fuchsia", 0xFF00FF, Color32To16(0xFF00FF) },
	{ "Gainsboro", 0xDCDCDC, Color32To16(0xDCDCDC) },
	{ "GhostWhite", 0xF8F8FF, Color32To16(0xF8F8FF) },
	{ "Gold", 0xFFD700, Color32To16(0xFFD700) },
	{ "GoldenRod", 0xDAA520, Color32To16(0xDAA520) },
	{ "Gray", 0x808080, Color32To16(0x808080) },
	{ "Grey", 0x808080, Color32To16(0x808080) },
	{ "Green", 0x008000, Color32To16(0x008000) },
	{ "GreenYellow", 0xADFF2F, Color32To16(0xADFF2F) },
	{ "HoneyDew", 0xF0FFF0, Color32To16(0xF0FFF0) },
	{ "HotPink", 0xFF69B4, Color32To16(0xFF69B4) },
	{ "IndianRed", 0xCD5C5C, Color32To16(0xCD5C5C) },
	{ "Indigo", 0x4B0082, Color32To16(0x4B0082) },
	{ "Ivory", 0xFFFFF0, Color32To16(0xFFFFF0) },
	{ "Khaki", 0xF0E68C, Color32To16(0xF0E68C) },
	{ "Lavender", 0xE6E6FA, Color32To16(0xE6E6FA) },
	{ "LavenderBlush", 0xFFF0F5, Color32To16(0xFFF0F5) },
	{ "LawnGreen", 0x7CFC00, Color32To16(0x7CFC00) },
	{ "LemonChiffon", 0xFFFACD, Color32To16(0xFFFACD) },
	{ "LightBlue", 0xADD8E6, Color32To16(0xADD8E6) },
	{ "LightCoral", 0xF08080, Color32To16(0xF08080) },
	{ "LightCyan", 0xE0FFFF, Color32To16(0xE0FFFF) },
	{ "LightGoldenRodYellow", 0xFAFAD2, Color32To16(0xFAFAD2) },
	{ "LightGray", 0xD3D3D3, Color32To16(0xD3D3D3) },
	{ "LightGrey", 0xD3D3D3, Color32To16(0xD3D3D3) },
	{ "LightGreen", 0x90EE90, Color32To16(0x90EE90) },
	{ "LightPink", 0xFFB6C1, Color32To16(0xFFB6C1) },
	{ "LightSalmon", 0xFFA07A, Color32To16(0xFFA07A) },
	{ "LightSeaGreen", 0x20B2AA, Color32To16(0x20B2AA) },
	{ "LightSkyBlue", 0x87CEFA, Color32To16(0x87CEFA) },
	{ "LightSlateGray", 0x778899, Color32To16(0x778899) },
	{ "LightSlateGrey", 0x778899, Color32To16(0x778899) },
	{ "LightSteelBlue", 0xB0C4DE, Color32To16(0xB0C4DE) },
	{ "LightYellow", 0xFFFFE0, Color32To16(0xFFFFE0) },
	{ "Lime", 0x00FF00, Color32To16(0x00FF00) },
	{ "LimeGreen", 0x32CD32, Color32To16(0x32CD32) },
	{ "Linen", 0xFAF0E6, Color32To16(0xFAF0E6) },
	{ "Magenta", 0xFF00FF, Color32To16(0xFF00FF) },
	{ "Maroon", 0x800000, Color32To16(0x800000) },
	{ "MediumAquaMarine", 0x66CDAA, Color32To16(0x66CDAA) },
	{ "MediumBlue", 0x0000CD, Color32To16(0x0000CD) },
	{ "MediumOrchid", 0xBA55D3, Color32To16(0xBA55D3) },
	{ "MediumPurple", 0x9370D8, Color32To16(0x9370D8) },
	{ "MediumSeaGreen", 0x3CB371, Color32To16(0x3CB371) },
	{ "MediumSlateBlue", 0x7B68EE, Color32To16(0x7B68EE) },
	{ "MediumSpringGreen", 0x00FA9A, Color32To16(0x00FA9A) },
	{ "MediumTurquoise", 0x48D1CC, Color32To16(0x48D1CC) },
	{ "MediumVioletRed", 0xC71585, Color32To16(0xC71585) },
	{ "MidnightBlue", 0x191970, Color32To16(0x191970) },
	{ "MintCream", 0xF5FFFA, Color32To16(0xF5FFFA) },
	{ "MistyRose", 0xFFE4E1, Color32To16(0xFFE4E1) },
	{ "Moccasin", 0xFFE4B5, Color32To16(0xFFE4B5) },
	{ "NavajoWhite", 0xFFDEAD, Color32To16(0xFFDEAD) },
	{ "Navy", 0x000080, Color32To16(0x000080) },
	{ "OldLace", 0xFDF5E6, Color32To16(0xFDF5E6) },
	{ "Olive", 0x808000, Color32To16(0x808000) },
	{ "OliveDrab", 0x6B8E23, Color32To16(0x6B8E23) },
	{ "Orange", 0xFFA500, Color32To16(0xFFA500) },
	{ "OrangeRed", 0xFF4500, Color32To16(0xFF4500) },
	{ "Orchid", 0xDA70D6, Color32To16(0xDA70D6) },
	{ "PaleGoldenRod", 0xEEE8AA, Color32To16(0xEEE8AA) },
	{ "PaleGreen", 0x98FB98, Color32To16(0x98FB98) },
	{ "PaleTurquoise", 0xAFEEEE, Color32To16(0xAFEEEE) },
	{ "PaleVioletRed", 0xD87093, Color32To16(0xD87093) },
	{ "PapayaWhip", 0xFFEFD5, Color32To16(0xFFEFD5) },
	{ "PeachPuff", 0xFFDAB9, Color32To16(0xFFDAB9) },
	{ "Peru", 0xCD853F, Color32To16(0xCD853F) },
	{ "Pink", 0xFFC0CB, Color32To16(0xFFC0CB) },
	{ "Plum", 0xDDA0DD, Color32To16(0xDDA0DD) },
	{ "PowderBlue", 0xB0E0E6, Color32To16(0xB0E0E6) },
	{ "Purple", 0x800080, Color32To16(0x800080) },
	{ "Red", 0xFF0000, Color32To16(0xFF0000) },
	{ "RosyBrown", 0xBC8F8F, Color32To16(0xBC8F8F) },
	{ "RoyalBlue", 0x4169E1, Color32To16(0x4169E1) },
	{ "SaddleBrown", 0x8B4513, Color32To16(0x8B4513) },
	{ "Salmon", 0xFA8072, Color32To16(0xFA8072) },
	{ "SandyBrown", 0xF4A460, Color32To16(0xF4A460) },
	{ "SeaGreen", 0x2E8B57, Color32To16(0x2E8B57) },
	{ "SeaShell", 0xFFF5EE, Color32To16(0xFFF5EE) },
	{ "Sienna", 0xA0522D, Color32To16(0xA0522D) },
	{ "Silver", 0xC0C0C0, Color32To16(0xC0C0C0) },
	{ "SkyBlue", 0x87CEEB, Color32To16(0x87CEEB) },
	{ "SlateBlue", 0x6A5ACD, Color32To16(0x6A5ACD) },
	{ "SlateGray", 0x708090, Color32To16(0x708090) },
	{ "SlateGrey", 0x708090, Color32To16(0x708090) },
	{ "Snow", 0xFFFAFA, Color32To16(0xFFFAFA) },
	{ "SpringGreen", 0x00FF7F, Color32To16(0x00FF7F) },
	{ "SteelBlue", 0x4682B4, Color32To16(0x4682B4) },
	{ "Tan", 0xD2B48C, Color32To16(0xD2B48C) },
	{ "Teal", 0x008080, Color32To16(0x008080) },
	{ "Thistle", 0xD8BFD8, Color32To16(0xD8BFD8) },
	{ "Tomato", 0xFF6347, Color32To16(0xFF6347) },
	{ "Turquoise", 0x40E0D0, Color32To16(0x40E0D0) },
	{ "Violet", 0xEE82EE, Color32To16(0xEE82EE) },
	{ "Wheat", 0xF5DEB3, Color32To16(0xF5DEB3) },
	{ "White", 0xFFFFFF, Color32To16(0xFFFFFF) },
	{ "WhiteSmoke", 0xF5F5F5, Color32To16(0xF5F5F5) },
	{ "Yellow", 0xFFFF00, Color32To16(0xFFFF00) },
	{ "YellowGreen", 0x9ACD32, Color32To16(0x9ACD32) }
};

// * no custom color is -1
#define NO_COLOR -1
// * the number of custom colors
#define NUMBER_COLORS ArraySize(H3CustomColors)

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// * the largest size of a tag color... with some extra room
#define TAG_MAX_SIZE 31

// * Makes a copy of text to be printed
// * and removes color tags {~Color} from text
// * while storing custom colors to $CharColors
_LHF_(ParseText) // 0x4B5255
{
	PCHAR text = (PCHAR)c->edx;
	INT32 len = c->local_n(5);

	if (len >= CharColorsSize)
	{
		CharColorsSize *= 2; // double size
		h3_delete(CharColors);
		CharColors = (PINT32)h3_malloc(CharColorsSize);
	}

	CHAR buffer[TAG_MAX_SIZE + 1];
	TextParser.Assign(text, len); // copy text to parser
	PCHAR current = TextParser.String();
	INT32 currentColor = NO_COLOR;

	for (INT i = 0; i < len; i++, current++)
	{
		if (current[0] == '{' && current[1] == '~') // current[1] is always safe because strings are null-terminated
		{
			INT32 seekLen = min(TAG_MAX_SIZE, len - i - 1); // why -1 ? because if the color tag is at the very end of the string, it will have no effect anyway
			F_strncpy(buffer, &current[2], seekLen); // make a temporary copy of text starting after '{~'
			for (INT tagLen = 0; tagLen < seekLen; tagLen++)
			{
				if (buffer[tagLen] == '}') // seek end of color tag
				{
					buffer[tagLen] = 0; // null-terminate buffer, it now contains the color tag in between '{~'  '}'

					for (INT k = 0; k < NUMBER_COLORS; k++) // look up if this is an existing color in our table
					{
						if (!h3_strcmpi(buffer, H3CustomColors[k].name)) // not character-sensitive
						{
							currentColor = k; // set current color
							INT removed = sizeof('{') + sizeof('~') + sizeof('}') + tagLen; // we are removing the {~Color} tag from parsed text
							TextParser.Remove(i, i + removed); // remove this portion of text
							len -= removed; // the string length for loop is now shorter
							break;
						} // strcmpi
					} // cycle through custom colors
					// a match was (or was not) found!, skip the '}' check and proceed to the next character directly
					goto next_char;
				} // parse color tag contents
			} // seek '}' end tag
		} // seek '{~' start tag
		if (current[0] == '}')
			currentColor = NO_COLOR;
	next_char:
		CharColors[i] = currentColor;
	} // parse text

	// update registers
	c->edx = (int)TextParser.String();
	IntAt(c->ebp + 8) = (int)TextParser.String();
	IntAt(c->ebp - 0x14) = TextParser.Length();

	return EXEC_DEFAULT;
}

// * Calculates the current position in TextParser
// * works at the start of a new line
_LHF_(TextPositionNewLine)
{
	CurrentPosition = IntAt(c->esp) - (int)TextParser.String();
	return EXEC_DEFAULT;
}

// * Calculates the current position in TextParser
// * works in the middle of a line
_LHF_(TextPositionLineMiddle)
{
	// * c->edx points to an offset of string
	// * calculate the offset to know the matching color
	CurrentPosition = c->edx - (int)TextParser.String();
	return EXEC_DEFAULT;
}

// * Sets the correct color to use while using GDI mode ~16bit
_LHF_(DrawCharColor)
{
	INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
	{
		c->eax = H3CustomColors[color].rgb565;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

// * Sets the correct color to use while using True mode
_LHF_(TrueModeDrawCharColor)
{
	INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
		c->eax = H3CustomColors[color].rgb;
	return EXEC_DEFAULT;
}

// * Sets the correct color to use while using True Stretchable mode
_LHF_(TrueStretchModeDrawCharColor)
{
	INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
	{
		c->edi = H3CustomColors[color].rgb;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

#define COLORMODE_15BITS 0x3E0
#define COLORMODE_16BITS 0x7E0

//* It seems that while using HDmod only COLORMODE_16BITS is used.
// * This is still present for safety purposes.
_LHF_(CheckColorMode)
{
	if (c->eax == COLORMODE_15BITS)
	{
		for (INT i = 0; i < NUMBER_COLORS; i++)
			H3CustomColors[i].rgb565 = Color32To15(H3CustomColors[i].rgb);
	}
	return EXEC_DEFAULT;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Place hooks for 32-bit modes
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// * Finds where to install @TrueModeDrawCharColor
// * hook within _hd3_.dll
void TrueColorHook(PatcherInstance *pi)
{
	H3DLL _HD3_DLL;
	_HD3_DLL.GetDLLInfo("_hd3_.dll");

	///////////////////////////////////////////////////////////////////////////////
	// Needle: 68 00 04 00 00 B8 92 74 61 00
	///////////////////////////////////////////////////////////////////////////////
	UINT8 needle[] = {
		0x68, 0x00, 0x04, 0x00, 0x00,					// PUSH 400
		0xB8, 0x92, 0x74, 0x61, 0x00					// MOV EAX, 617492
	};
	///////////////////////////////////////////////////////////////////////////////
	// Expected code: 89 45 38
	///////////////////////////////////////////////////////////////////////////////
	UINT8 needle_sought[] = {
		0x89, 0x45, 0x38								// MOV DWORD PTR SS:[EBP+38], EAX
	};

	DWORD address = _HD3_DLL.NeedleSearchAround(needle, sizeof(needle), 0x50, needle_sought, sizeof(needle_sought));
	if (address)
		pi->WriteLoHook(address, TrueModeDrawCharColor);
}

// * Finds where to install @TrueStretchModeDrawCharColor
// * hook within HD_MCR.dll
void TrueStretchModeColorHook(PatcherInstance *pi)
{
	H3DLL HD_MCR_DLL;
	HD_MCR_DLL.GetDLLInfo("HD_MCR.dll");

	///////////////////////////////////////////////////////////////////////////////
	// Needle: 68 00 04 00 00 B8 92 74 61 00
	///////////////////////////////////////////////////////////////////////////////
	UINT8 needle[] = {
		0x68, 0x00, 0x04, 0x00, 0x00,					// PUSH 400
		0xB8, 0x92, 0x74, 0x61, 0x00					// MOV EAX, 617492
	};
	///////////////////////////////////////////////////////////////////////////////
	// Expected code: 8B 44 24 3C
	///////////////////////////////////////////////////////////////////////////////
	UINT8 needle_sought[] = {
		0x8B, 0x44, 0x24, 0x3C							// MOV EAX, DWORD PTR SS:[ESP+3C]
	};

	DWORD address = HD_MCR_DLL.NeedleSearchAround(needle, sizeof(needle), 0x50, needle_sought, sizeof(needle_sought));
	if (address)
		pi->WriteLoHook(address, TrueStretchModeDrawCharColor);
}

void Variables_init(Patcher *p)
{
	p->VarInit("TextColor.Count", NUMBER_COLORS);
	p->VarInit("TextColor.Table", (UINT)H3CustomColors);
}

void Hooks_init(PatcherInstance *pi)
{
	CharColors = (PINT32)h3_malloc(CharColorsSize);
	if (CharColors)
		memset(CharColors, NO_COLOR, CharColorsSize);
	else
	{
		H3Error::_ShowError(L"Memory could not be allocated for H3.TextColor!");
		return;
	}

	pi->WriteLoHook(0x4B5255, ParseText);
	pi->WriteLoHook(0x4B54D4, TextPositionNewLine);
	pi->WriteLoHook(0x4B5196, TextPositionLineMiddle);
	pi->WriteLoHook(0x55A914, CheckColorMode);

	if (h3_BitMode == 4)
	{
		TrueColorHook(pi);
		TrueStretchModeColorHook(pi);
	}
	else
		pi->WriteLoHook(0x4B4F74, DrawCharColor);

	pi->WriteByte(0x57D394, 4);			// allows the use of '~' key in the save game text field
	pi->WriteWord(0x5BAFB7, 0x06EB);	// allows the use of '{' and '}' in some text fields, such as chat
}