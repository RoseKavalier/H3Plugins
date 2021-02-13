#include "TextColor.hpp"

using namespace h3;
using namespace H3Plugin::TextColor;

TextColorPlugin TextColor;
H3TextColor InternalTextColor;

//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================

H3TextColorInformation* GetTextColor_()
{
#pragma _H3API_EXPORT_
	return &InternalTextColor;
}

UINT H3TextColor::GetNumberColors()
{
	return TextColor.NumberColors();
}

const H3Vector<H3String>* H3TextColor::GetColorNames()
{
	return TextColor.GetColorNames();
}

VOID H3TextColor::DeleteColorNames()
{
	TextColor.DeleteColorNames();
}
VOID H3TextColor::AddColor(LPCSTR name, UINT8 red, UINT8 green, UINT8 blue)
{
	H3ARGB888 rgb(red, green, blue);
	TextColor.AddColor(name, ConvertColor(rgb.Value()));
}

INT32 H3TextColor::ConvertColor(INT32 rgb)
{
	switch (mode)
	{
	case H3TextColor::CM_888:
		rgb |= 0xFF000000;
		break;
	case H3TextColor::CM_555:
		rgb = H3RGB555::Pack((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
		break;
	case H3TextColor::CM_565:
		rgb = H3RGB565::Pack((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
		/* fall through */
	default:
		break;
	}
	return rgb;
}

INT32 TextColorNode::RGBColor() const
{
	INT32 rgb = INT32(F_strtoul(name + 1, 16));
	return InternalTextColor.ConvertColor(rgb);
}

//===================================================================================
//
//                             HOOKS
//
//===================================================================================

// * Gets the offset from start of text
// * works at the start of a new line
_LHF_(TextPositionNewLine)
{
	return TextColor.TextPositionNewLine(*c);
}

// * Increment the current position
// * works in the middle of a line
_LHF_(TextPositionLineMiddle)
{
	return TextColor.TextPositionLineMiddle();
}

// * Sets the correct color to use while using GDI mode ~16bit
_LHF_(DrawCharColor)
{
	return TextColor.DrawCharColor(*c);
}

// * Sets the correct color to use while using True mode
_LHF_(TrueModeDrawCharColor)
{
	return TextColor.TrueModeDrawCharColor(*c);
}

// * Sets the correct color to use while using Direct Draw
_LHF_(DirectDrawCharColor)
{
	return TextColor.DirectDrawCharColor(*c);
}

// * Sets the correct color to use while using Direct Draw
_LHF_(DirectDrawCharColor_5000281)
{
	return TextColor.DirectDrawCharColor_5000281(*c);
}

// * Sets the correct color to use while using True Stretchable mode
_LHF_(TrueStretchModeDrawCharColor)
{
	return TextColor.TrueStretchModeDrawCharColor(*c);
}

// * Makes a copy of text to be printed
// * and removes color tags {~Color} from text
// * while storing custom colors to $CharColors
_LHF_(ParseText) // 0x4B51FA
{
	return TextColor.ParseText(*c);
}

// * Set the current position in the text buffer
// * Uses Wogcn's own text parser to get accurate position
_LHF_(WogcnPosition)
{
	TextColor.SetPosition(c->Ebx<UINT>());
	return EXEC_DEFAULT;
}

// * Detects color-mode, populates ini colors and adds rgb setting hooks
_LHF_(MainHook)
{
	return TextColor.MainHook(*h, *c);
}

// * Checks if Wogcn plugin is active and installs optional hook to get current text position
void TextColorPlugin::CheckWogCnPlugin()
{
	H3DLL wogcn;
	if (!wogcn.GetDLLInfo("Wogcn.dll"))
		return;

	constexpr BYTE position[] = { 0x80, 0x3C, 0x1E, 0x00, 0x0F, 0x84 };
	ADDRESS addr = wogcn.NeedleSearch(position, 0);
	if (addr)
		Hook(addr, ::WogcnPosition);
}

// * handles all 32-bit color drawing as of HD 5.0 RC81
void TextColorPlugin::DirectDrawHook_5000281()
{
	///////////////////////////////////////////////////////////////////////////////
	// Needle: 54 12 00 00
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle[] = {
		0x54, 0x12, 0x00, 0x00					// MOV EDX,DWORD PTR DS:[EDI+1254]
	};
	///////////////////////////////////////////////////////////////////////////////
	// Expected code: 8B 2C 82
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle_sought[] = {
		0x8B, 0x1C, 0x82						// MOV EBX,DWORD PTR DS:[EAX*4+EDX]
	};

	H3DLL HD_TC2("HD_TC2.dll");

	DWORD address = HD_TC2.NeedleSearchAround(needle, 0x20, needle_sought);
	if (address)
		Hook(address + sizeof(needle_sought), ::DirectDrawCharColor_5000281);
}

// * Finds where to install @TrueModeDrawCharColor
// * hook within _hd3_.dll
void TextColorPlugin::TrueColorHook_legacy()
{
	H3DLL _HD3_DLL("_hd3_.dll");

	///////////////////////////////////////////////////////////////////////////////
	// Needle: 68 00 04 00 00 B8 92 74 61 00
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle[] = {
		0x68, 0x00, 0x04, 0x00, 0x00,					// PUSH 400
		0xB8, 0x92, 0x74, 0x61, 0x00					// MOV EAX, 617492
	};
	///////////////////////////////////////////////////////////////////////////////
	// Expected code: 89 45 38
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle_sought[] = {
		0x89, 0x45, 0x38								// MOV DWORD PTR SS:[EBP+38], EAX
	};

	DWORD address = _HD3_DLL.NeedleSearchAround(needle, 0x50, needle_sought);
	if (address)
		Hook(address, ::TrueModeDrawCharColor);
}

void TextColorPlugin::DirectDrawHook_legacy()
{
	///////////////////////////////////////////////////////////////////////////////
	// Needle: 54 12 00 00
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle[] = {
		0x54, 0x12, 0x00, 0x00							// MOV EDX,DWORD PTR DS:[EDI+1254]
	};
	///////////////////////////////////////////////////////////////////////////////
	// Expected code: 8B 2C 82
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle_sought[] = {
		0x8B, 0x2C, 0x82								// MOV EBP,DWORD PTR DS:[EAX*4+EDX]
	};

	H3DLL HD_TC2("HD_TC2.dll");

	DWORD address = HD_TC2.NeedleSearchAround(needle, 0x20, needle_sought);
	if (address)
		Hook(address + sizeof(needle_sought), ::DirectDrawCharColor);
}

// * Finds where to install @TrueStretchModeDrawCharColor
// * hook within HD_MCR.dll
void TextColorPlugin::TrueStretchModeColorHook_legacy()
{
	H3DLL HD_MCR_DLL("HD_MCR.dll");

	///////////////////////////////////////////////////////////////////////////////
	// Needle: 68 00 04 00 00 B8 92 74 61 00
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle[] = {
		0x68, 0x00, 0x04, 0x00, 0x00,					// PUSH 400
		0xB8, 0x92, 0x74, 0x61, 0x00					// MOV EAX, 617492
	};
	///////////////////////////////////////////////////////////////////////////////
	// Expected code: 8B 44 24 3C
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle_sought[] = {
		0x8B, 0x44, 0x24, 0x3C							// MOV EAX, DWORD PTR SS:[ESP+3C]
	};

	DWORD address = HD_MCR_DLL.NeedleSearchAround(needle, 0x50, needle_sought);
	if (address)
		Hook(address, ::TrueStretchModeDrawCharColor);
}

// * Finds where to install @TrueModeDrawCharColor for old ERA versions
// * hook within _hd3_.dll && HD_MCR.dll
void TextColorPlugin::TrueColorHook_ERA()
{
	H3DLL _HD3_DLL("_hd3_.dll");
	H3DLL HD_MCR_DLL("HD_MCR.dll");

	///////////////////////////////////////////////////////////////////////////////
	// Needle: 89 45 E0 83 3D
	///////////////////////////////////////////////////////////////////////////////
	constexpr UINT8 needle[] = {
		0x89, 0x45, 0xE0, 					// MOV DWORD PTR SS:[EBP-20],EAX
		0x83, 0x3D							// CMP DWORD PTR DS:[.....],0
	};

	DWORD address = _HD3_DLL.NeedleSearch(needle, 0);
	if (address)
		Hook(address, ::TrueModeDrawCharColor);

	address = HD_MCR_DLL.NeedleSearch(needle, 0);
	if (address)
		Hook(address, ::TrueModeDrawCharColor);
}

int TextColorPlugin::TextPositionNewLine(HookContext& c)
{
	TextColor.m_currentPosition = c.Local<UINT>(8 / 4);
	return EXEC_DEFAULT;
}

int TextColorPlugin::TextPositionLineMiddle()
{
	++m_currentPosition;
	return EXEC_DEFAULT;
}

int TextColorPlugin::DrawCharColor(HookContext& c)
{
	const INT32 color = CurrentColor();
	if (color != NO_COLOR)
	{
		c.eax = color;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

int TextColorPlugin::TrueModeDrawCharColor(HookContext& c)
{
	const INT32 color = CurrentColor();
	if (color != NO_COLOR)
		c.eax = color;
	return EXEC_DEFAULT;
}

int TextColorPlugin::DirectDrawCharColor(HookContext& c)
{
	const INT32 color = CurrentColor();
	if (color != NO_COLOR)
		c.ebp = color;
	return EXEC_DEFAULT;
}

int TextColorPlugin::DirectDrawCharColor_5000281(HookContext& c)
{
	const INT32 color = CurrentColor();
	if (color != NO_COLOR)
		c.ebx = color;
	return EXEC_DEFAULT;
}

int TextColorPlugin::TrueStretchModeDrawCharColor(HookContext& c)
{
	const INT32 color = CurrentColor();
	if (color != NO_COLOR)
	{
		c.edi = color;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

int TextColorPlugin::ParseText(HookContext& c)
{
	TextColorNode buffer;
	m_textParser = c.Arg<LPCSTR>(1);
	UINT len = m_textParser.Length();
	PCHAR current = m_textParser.begin();
	INT32 current_color = NO_COLOR;
	m_charColors.RemoveAll();

	for (UINT i = 0; i < len; i++, current++)
	{
		if (current[0] == '}')
			current_color = NO_COLOR;
		else if (current[0] == '{' && current[1] == '~') // current[1] is always safe because strings are null-terminated
		{
			const UINT seek_len = std::min(TAG_LEN, len - i - 1); // why -1 ? because if the color tag is at the very end of the string, it will have no effect anyway
			F_strncpy(buffer.name, &current[2], seek_len); // make a temporary copy of text starting after '{~'
			for (UINT tag_len = 0; tag_len < seek_len; tag_len++)
			{
				if (buffer[tag_len] == '}') // seek end of color tag
				{
					buffer[tag_len] = 0; // null-terminate buffer, it now contains the color tag in between '{~'  '}'

					if (buffer[0] == '#')
					{
						// * #RRGGBB color format
						current_color = buffer.RGBColor();
					}
					else
					{
						// * search in tree
						// * significantly faster than searching in vector
						// * as was previously done
						auto color_node = m_colorsTree.Find(buffer);
						if (color_node == m_colorsTree.end())
							break;
						// * set current color
						current_color = color_node->color;
					}

					const UINT removed = sizeof('{') + sizeof('~') + sizeof('}') + tag_len; // we are removing the {~Color} tag from parsed text;
					m_textParser.Erase(i, i + removed); // remove this portion of text
					len -= removed; // the string length for loop is now shorter
					break;
				} // parse color tag contents
			} // seek '}' end tag
		} // seek '{~' start tag

		m_charColors += current_color;
	} // parse text

	// update registers
	c.edx = reinterpret_cast<int>(m_textParser.String());
	c.Arg<LPCSTR>(1) = m_textParser.String();

	return EXEC_DEFAULT;
}

int TextColorPlugin::MainHook(LoHook& h, HookContext& c)
{
	constexpr INT GREENMASK565 = 0x7E0;

	auto& text_color = InternalTextColor;

	if (P_BitMode() == 4)
		text_color.mode = text_color.CM_888;
	else
	{
		if (c.edx == GREENMASK565)
			text_color.mode = text_color.CM_565;
		else
			text_color.mode = text_color.CM_555;
	}

	H3Stream colors(m_colorTextFile.String(), H3Stream::StreamMode::SM_READ_BINARY, TRUE);
	H3Vector<H3String> colors_list;

	if (colors.IsReady())
	{
		// * read all lines to string vector
		colors >> colors_list;

		H3String color_value;
		// * iterate on vector
		for (auto& line : colors_list)
		{
			// * skip new lines or comments
			if (!line.Length() || line[0] == '#')
				continue;

			// * split on equal sign
			if (line.Split('=', color_value))
			{
				// * remove spaces and tabs
				line.Trim();
				color_value.Trim();

				// * convert text to hexadecimal number
				INT32 rgb = INT32(F_strtoul(color_value, 16) & 0xFFFFFF);
				rgb = text_color.ConvertColor(rgb);

				// * add the node to colors tree
				TextColorNode node(line, rgb);
				m_colorsTree.Insert(node);
			}
		}
	}

	// * no longer needed
	m_colorTextFile.Dereference();

	if (text_color.mode == text_color.CM_888)
	{
		DWORD hdmodVersion = VarGetValue("HD.Version.Dword", 0u);
		if (hdmodVersion >= HDMOD_VERSION)
		{
			DirectDrawHook_5000281(); // covers all 32-bit drawing modes
		}
		else if (hdmodVersion == HDMOD_ERA)
		{
			TrueColorHook_ERA();
		}
		else
		{
			TrueColorHook_legacy();
			TrueStretchModeColorHook_legacy();
			DirectDrawHook_legacy();
		}
	}
	else
		Hook(0x4B4F74, ::DrawCharColor);

	CheckWogCnPlugin();

	// remove hook as it is no longer needed
	// and would be triggered when switching
	// between windowed and fullscreen modes
	h.Undo();

	return EXEC_DEFAULT;
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void TextColorPlugin::Start()
{
	m_colorTextFile = H3Path::CurrentDirectory().AppendA(ColorFileName);
	// * place here to check which color format to use
	Hook(0x601BCF, ::MainHook);
	// * allows the use of '~' key in the save game text field
	BytePatch(0x57D394, 4);
	// * allows the use of '{' and '}' in some text fields, such as chat
	WordPatch(0x5BAFB7, 0x06EB);
	// * removes color tags from text and stores matching color
	Hook(0x4B51FA, ::ParseText);
	// * gets current text color index
	Hook(0x4B54D4, ::TextPositionNewLine);
	// * gets current text color index
	Hook(0x4B5196, ::TextPositionLineMiddle);
}
