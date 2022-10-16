#pragma once

#define _H3API_PLUGINS_
#include <Plugin.hpp>
#include <H3API.hpp>

// * the maximum length of a color tag
constexpr UINT TAG_LEN = 31;

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
	TextColorNode(h3::H3String& col, INT32 val) :
		TextColorNode(col.String(), val)
	{
	}
	TextColorNode(LPCSTR col, INT32 val) :
		name(),
		name_end(),
		color(val)
	{
		h3::F_strncpy(name, col, sizeof(name));
	}

	BOOL operator<(const TextColorNode& other) const
	{
		return h3::F_strcmpi(name, other.name) < 0;
	}
	CHAR& operator[](UINT pos)
	{
		return name[pos];
	}
	INT32 RGBColor() const;
};
#pragma pack(pop)

class H3TextColor : public h3::H3Plugin::TextColor::H3TextColorInformation
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
	virtual const h3::H3Vector<h3::H3String>* GetColorNames() override;

	// * empties the vector of H3Strings with color names
	virtual VOID DeleteColorNames() override;

	// * Adds a color dynamically.
	// * Duplicate names are not allowed
	// * but duplicate colors are accepted.
	virtual VOID AddColor(LPCSTR name, UINT8 red, UINT8 green, UINT8 blue) override;

	INT32 ConvertColor(INT32 rgb);
};

/**
 * Uncomment to show an error message when failing to link up with patcher_x86
 */
//#define SHOW_ERROR_MESSAGE_ON_FAIL

/**
 * @brief A derived Plugin that constructs itself
 */
class TextColorPlugin : public Plugin
{
public:
	TextColorPlugin() : Plugin()
	{
		Status status = Init("H3.TextColor");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.TextColor", status);
#endif
	}

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================

	UINT NumberColors() const { return m_colorsTree.Size(); }
	const h3::H3Vector<h3::H3String> *GetColorNames()
	{
		DeleteColorNames();
		m_colorNames.Reserve(NumberColors());
		for (auto& it : m_colorsTree)
		{
			m_colorNames.Push(it.name);
		}
		return &m_colorNames;
	}
	VOID DeleteColorNames() { m_colorNames.RemoveAll(); }
	VOID AddColor(LPCSTR name, INT32 rgb)
	{
		TextColorNode node(name, rgb);
		m_colorsTree.Insert(node);
	}

	INT32 CurrentColor() const
	{
		return m_charColors[m_currentPosition];
	}

	void SetPosition(UINT position) { m_currentPosition = position; }

	int TextPositionNewLine(HookContext&);
	int TextPositionLineMiddle();
	int DrawCharColor(HookContext&);
	int TrueModeDrawCharColor(HookContext&);
	int DirectDrawCharColor(HookContext&);
	int DirectDrawCharColor_5000281(HookContext&);
	int TrueStretchModeDrawCharColor(HookContext&);
	int ParseText(HookContext&);
	int MainHook(LoHook&, HookContext&);
	void DrawCharacter(h3::H3Font* this_, int character, h3::H3LoadedPcx16* pcx16, int x, int y, int color);

private:
	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================


	h3::H3String m_colorTextFile;
	h3::H3String m_textParser;
	UINT m_currentPosition;
	h3::H3Vector<INT32> m_charColors;
	h3::H3Tree<TextColorNode> m_colorsTree;
	h3::H3Vector<h3::H3String> m_colorNames;

	using draw_char_t = void(__fastcall*)(h3::H3Font*, int, h3::H3LoadedPcx16*, int, int, int);
	draw_char_t m_drawFunction;

	void CheckWogCnPlugin();
	void DirectDrawHook_5000281();
	void TrueColorHook_ERA();
	void TrueColorHook_legacy();
	void TrueStretchModeColorHook_legacy();
	void DirectDrawHook_legacy();

	// * the value to indicate no custom color
	static constexpr INT NO_COLOR = -1;
	// * the TextColor file name
	static constexpr CHAR ColorFileName[] = "\\H3.TextColor.ini";

	// HDMOD version as of latest update
	static constexpr DWORD HDMOD_VERSION = 5000281;
	static constexpr DWORD HDMOD_DRAW_CHARACTER_VERSION = 5004307;
	static constexpr DWORD HDMOD_ERA = 4208204;
};