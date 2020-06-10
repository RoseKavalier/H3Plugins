#include "Hooks.h"

using namespace h3;

// HDMOD version as of latest update
constexpr DWORD HDMOD_VERSION = 5000281;
constexpr DWORD HDMOD_ERA = 4208204;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

using namespace H3Plugin::TextColor;

// * the maximum length of a color tag
constexpr UINT TAG_LEN = 31;
// * the value to indicate no custom color
constexpr INT NO_COLOR = -1;
// * the TextColor file name
constexpr CHAR ColorFileName[] = "\\H3.TextColor.ini";

#pragma pack(push, 4) // size 36, 35 otherwise which is ugly.
struct TextColorNode
{
	char name[TAG_LEN];
	char name_end;
	INT32 color;

	TextColorNode() :
		name(),
		name_end(),
		color()
	{
	}
	TextColorNode(H3String& col, INT32 val) :
		TextColorNode(col.String(), val)
	{
	}
	TextColorNode(LPCSTR col, INT32 val) :
		name(),
		name_end(),
		color(val)
	{
		F_strncpy(name, col, sizeof(name));
	}

	BOOL operator<(const TextColorNode& other) const
	{
		return F_strcmpi(name, other.name) < 0;
	}
};
#pragma pack(pop)

static class H3TextColor : public H3TextColorInformation
{
public:
	enum ColorMode : DWORD
	{
		CM_555,
		CM_565,
		CM_888
	};
	ColorMode mode;

	// * Returns the number of colors currently
			// * available to modify the text's appearance
	virtual UINT GetNumberColors() override;

	// * Fills a vector of H3Strings with the names
	// * of all current colors
	virtual const H3Vector<H3String>* GetColorNames() override;

	// * empties the vector of H3Strings with color names
	virtual VOID DeleteColorNames() override;

	// * Adds a color dynamically.
	// * Duplicate names are not allowed
	// * but duplicate colors are accepted.
	virtual VOID AddColor(LPCSTR name, UINT8 red, UINT8 green, UINT8 blue) override;
}InternalTextColor;

H3Plugin::TextColor::H3TextColorInformation * GetTextColor_()
{
#pragma _H3API_EXPORT_
	return &InternalTextColor;
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

// * global string for text file path
H3String ColorTextFile;
// * global string to store game text
H3String TextParser;
// * the current position from 0 to strlen in TextParser
UINT CurrentPosition;
// * the color to use at a given index
H3Vector<INT32> CharColors;
// * RB tree containing color names and rgb values
H3Tree<TextColorNode> ColorsTree;
// * a vector to pass the color names to other plugins
H3Vector<H3String> ColorNames;

UINT H3TextColor::GetNumberColors()
{
	return ColorsTree.Size();
}

const H3Vector<H3String>* H3TextColor::GetColorNames()
{
	ColorNames.RemoveAll();
	ColorNames.Reserve(ColorsTree.Size());
	for (auto& it : ColorsTree)
	{
		ColorNames.Push(it.name);
	}
	return &ColorNames;
}

VOID H3TextColor::DeleteColorNames()
{
	ColorNames.RemoveAll();
}

VOID H3TextColor::AddColor(LPCSTR name, UINT8 red, UINT8 green, UINT8 blue)
{
	INT32 color;
	switch (mode)
	{
	case H3TextColor::CM_555:
		color = H3RGB555::Pack(red, green, blue);
		break;
	case H3TextColor::CM_565:
		color = H3RGB565::Pack(red, green, blue);
		break;
	case H3TextColor::CM_888:
		color = H3RGB888::Pack(red, green, blue);
		break;
	default:
		return;
	}

	TextColorNode node(name, color);

	ColorsTree.Insert(node);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// * Gets the offset from start of text
// * works at the start of a new line
_LHF_(TextPositionNewLine)
{
	CurrentPosition = c->Local<UINT>(8 / 4);
	return EXEC_DEFAULT;
}

// * Increment the current position
// * works in the middle of a line
_LHF_(TextPositionLineMiddle)
{
	++CurrentPosition;
	return EXEC_DEFAULT;
}

// * Sets the correct color to use while using GDI mode ~16bit
_LHF_(DrawCharColor)
{
	const INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
	{
		c->eax = color;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

// * Sets the correct color to use while using True mode
_LHF_(TrueModeDrawCharColor)
{
	const INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
		c->eax = color;
	return EXEC_DEFAULT;
}

// * Sets the correct color to use while using Direct Draw
_LHF_(DirectDrawCharColor)
{
	const INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
		c->ebp = color;
	return EXEC_DEFAULT;
}

// * Sets the correct color to use while using Direct Draw
_LHF_(DirectDrawCharColor_5000281)
{
	const INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
		c->ebx = color;
	return EXEC_DEFAULT;
}


// * Sets the correct color to use while using True Stretchable mode
_LHF_(TrueStretchModeDrawCharColor)
{
	const INT32 color = CharColors[CurrentPosition];
	if (color != NO_COLOR)
	{
		c->edi = color;
		return NO_EXEC_DEFAULT;
	}
	return EXEC_DEFAULT;
}

// * Makes a copy of text to be printed
// * and removes color tags {~Color} from text
// * while storing custom colors to $CharColors
_LHF_(ParseText) // 0x4B5255
{
	PCHAR text = PCHAR(c->edx);
	UINT len = c->Local<UINT>(5);

	TextColorNode buffer;
	TextParser.Assign(text, len); // copy text to parser
	PCHAR current = TextParser.Begin();
	INT32 currentColor = NO_COLOR;

	CharColors.RemoveAll();

	for (UINT i = 0; i < len; i++, current++)
	{
		if (current[0] == '}')
			currentColor = NO_COLOR;
		else if (current[0] == '{' && current[1] == '~') // current[1] is always safe because strings are null-terminated
		{
			const UINT seekLen = std::min(TAG_LEN, len - i - 1); // why -1 ? because if the color tag is at the very end of the string, it will have no effect anyway
			F_strncpy(buffer.name, &current[2], seekLen); // make a temporary copy of text starting after '{~'
			for (UINT tagLen = 0; tagLen < seekLen; tagLen++)
			{
				if (buffer.name[tagLen] == '}') // seek end of color tag
				{
					buffer.name[tagLen] = 0; // null-terminate buffer, it now contains the color tag in between '{~'  '}'

					// * search in tree
					// * significantly faster than searching in vector
					// * as was previously done
					auto color_node = ColorsTree.Find(buffer);
					if (color_node == ColorsTree.end())
						break;

					// * set current color
					currentColor = color_node->color;
					const UINT removed = sizeof('{') + sizeof('~') + sizeof('}') + tagLen; // we are removing the {~Color} tag from parsed text;
					TextParser.Erase(i, i + removed); // remove this portion of text
					len -= removed; // the string length for loop is now shorter
					break;
				} // parse color tag contents
			} // seek '}' end tag
		} // seek '{~' start tag

		CharColors += currentColor;
	} // parse text

	// update registers
	c->edx = reinterpret_cast<int>(TextParser.String());
	c->Arg<LPCSTR>(1) = TextParser.String();
	c->Local<UINT>(5) = TextParser.Length();

	return EXEC_DEFAULT;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Place hooks for 32-bit modes
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// * handles all 32-bit color drawing as of HD 5.0 RC81
void DirectDrawHook_5000281(PatcherInstance *pi)
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
		pi->WriteLoHook(address + sizeof(needle_sought), DirectDrawCharColor_5000281);
}

// * Finds where to install @TrueModeDrawCharColor
// * hook within _hd3_.dll
void TrueColorHook_legacy(PatcherInstance *pi)
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
		pi->WriteLoHook(address, TrueModeDrawCharColor);
}

void DirectDrawHook_legacy(PatcherInstance *pi)
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
		pi->WriteLoHook(address + sizeof(needle_sought), DirectDrawCharColor);
}

// * Finds where to install @TrueStretchModeDrawCharColor
// * hook within HD_MCR.dll
void TrueStretchModeColorHook_legacy(PatcherInstance *pi)
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
		pi->WriteLoHook(address, TrueStretchModeDrawCharColor);
}

// * Finds where to install @TrueModeDrawCharColor for ERA version
// * hook within _hd3_.dll && HD_MCR.dll
void TrueColorHook_ERA(PatcherInstance *pi)
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
		pi->WriteLoHook(address, TrueModeDrawCharColor);

	address = HD_MCR_DLL.NeedleSearch(needle, 0);
	if (address)
		pi->WriteLoHook(address, TrueModeDrawCharColor);
}

_LHF_(MainHook)
{
	constexpr INT GREENMASK565 = 0x7E0;

	if (P_BitMode() == 4)
		InternalTextColor.mode = InternalTextColor.CM_888;
	else
	{
		if (c->edx == GREENMASK565)
			InternalTextColor.mode = InternalTextColor.CM_565;
		else
			InternalTextColor.mode = InternalTextColor.CM_555;
	}

	H3Stream colors(ColorTextFile.String(), H3Stream::StreamMode::SM_READ_BINARY, TRUE);
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

				// * pack if needed
				switch (InternalTextColor.mode)
				{
				case H3TextColor::CM_888:
					rgb += 0xFF000000;
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

				// * add the node to colors tree
				TextColorNode node(line, rgb);
				ColorsTree.Insert(node);
			}
		}
	}

	// * no longer needed
	ColorTextFile.Dereference();

	if (InternalTextColor.mode == InternalTextColor.CM_888)
	{
		DWORD hdmodVersion = _P->VarGetValue("HD.Version.Dword", 0u);
		if (hdmodVersion >= HDMOD_VERSION)
		{
			DirectDrawHook_5000281(_PI); // covers all 32-bit drawing modes
		}
		else if (hdmodVersion == HDMOD_ERA)
		{
			TrueColorHook_ERA(_PI);
		}
		else
		{
			TrueColorHook_legacy(_PI);
			TrueStretchModeColorHook_legacy(_PI);
			DirectDrawHook_legacy(_PI);
		}
	}
	else
		_PI->WriteLoHook(0x4B4F74, DrawCharColor);

	// remove hook as it is no longer needed
	// and would be triggered when switching
	// between windowed and fullscreen modes
	h->Undo();

	return EXEC_DEFAULT;
}

void Hooks_init(PatcherInstance *pi, h3::H3Version& version)
{
	F_GetCurrentDirectory(ColorTextFile, false);
	ColorTextFile.AppendA(ColorFileName);
	// * place here to check which color format to use
	pi->WriteLoHook(0x601BCF, MainHook);
	// * allows the use of '~' key in the save game text field
	pi->WriteByte(0x57D394, 4);
	// * allows the use of '{' and '}' in some text fields, such as chat
	pi->WriteWord(0x5BAFB7, 0x06EB);
	// * removes color tags from text and stores matching color
	pi->WriteLoHook(0x4B5255, ParseText);
	// * gets current text color index
	pi->WriteLoHook(0x4B54D4, TextPositionNewLine);
	// * gets current text color index
	pi->WriteLoHook(0x4B5196, TextPositionLineMiddle);
}