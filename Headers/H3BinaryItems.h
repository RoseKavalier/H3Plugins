//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//          In preparing these files, several sources were          //
//            consulted, they are listed in no particular           //
//                          order below.                            //
//                                                                  //
//  Source: https://github.com/potmdehex/homm3tools                 //
//  Author: potmdehex and contributors                              //
//                                                                  //
//  Source: https://github.com/redxu/HoMM3_FA                       //
//  Author: redxu                                                   //
//                                                                  //
//  Source: https://github.com/openhomm/openhomm                    //
//  Author: Ershov Stanislav, Fomin Roman, Akulich Alexander        //
//                                                                  //
//  Source: https://github.com/GrayFace/wog                         //
//  Author: GrayFace and WoG team                                   //
//                                                                  //
//  Source: https://github.com/ethernidee/era                       //
//  Author: Berserker                                               //
//                                                                  //
//  Source: https://github.com/ethernidee/era-editor                //
//  Author: Grayface and Berserker                                  //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=3900      //
//  Author: Slava and GrayFace                                      //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=4583      //
//  Author: gamecreator                                             //
//                                                                  //
//  Thanks: patcher_x86 by baratorch and code therein               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BINARYITEMS_H_
#define _H3BINARYITEMS_H_

#pragma once

#include "H3Base.h"

struct H3ARGB888;
typedef UINT16 RGB555;
typedef UINT16 RGB565;

// BINARY TREE ITEMS ~ named _BaseFileItem_ in database
struct H3BinaryItem;
struct H3BinaryTreeNode;
struct H3BinTreeList;
struct H3WavFile;
struct H3ColumnTextFile;
struct H3TextFile;
struct H3RGB888;
struct H3RGB555;
struct H3RGB565;
struct H3Palette565;
struct H3Font;
struct H3Palette888;
struct H3LoadedPCX;
struct H3LoadedPCX16;
struct H3LoadedPCX24;
struct H3DefFrame;
struct H3DefGroup;
struct H3LoadedDEF;
struct H3HSV;

#pragma pack(push, 1)

// * a binary tree to hold game assets
struct H3BinTreeList
{
	h3unk _f0[4];
	// * +4
	H3BinaryTreeNode* root;
	h3unk _f8[4];
	INT32 number_nodes;

	H3BinaryTreeNode* FindItem(LPCSTR name);
	VOID AddItem(H3BinaryItem *item);
	VOID RemoveItem(H3BinaryTreeNode* node);
	VOID RemoveItem(LPCSTR name);
};

struct H3BinaryTreeNode // size 36
{
	// * +0
	H3BinaryTreeNode *leftNode;
	// * +4
	H3BinaryTreeNode *parent;
	// * +8
	H3BinaryTreeNode *rightNode;
	// * +C
	struct BinaryItemData
	{
		// * +C
		CHAR name[12];
		// * +18
		UINT name_end; // always 0
		// * +1C
		H3BinaryItem *item;
	}data;
	// * +20
	BOOL isBlackNode; // https://en.wikipedia.org/wiki/Red–black_tree

	H3BinaryItem* GetBinaryItem() const { return data.item; }
};

struct H3BinaryItem // constructor 0x558970, size 1C
{
protected:
	// * +0
	struct BinaryVTable
	{
		h3func destroy;		// 0x5589C0, called by dereference
		h3func dereference; // 0x55D300
		h3func getSize;
	}*vTable;
	// * +4
	CHAR name[12];
	// * +10
	UINT name_end; // always 0
	// * +14
	INT32 type; // arg3 from constructor
	// * +18
	INT32 ref; // the number of times it is being used
public:
	H3BinaryItem* InitiateBinary(LPCSTR name, INT type) {
		return THISCALL_3(H3BinaryItem*, 0x558970, this, name, type);
	}
	VOID Dereference() { THISCALL_1(VOID, vTable->dereference, this); }
	VOID AddToBinaryTree(H3BinTreeList* tree = reinterpret_cast<H3BinTreeList*>(0x69E560));
	VOID IncreaseReferences() { ++ref; }
};

///////////////////////////////////////////////////
// from breakpoint at constructor, the following items are all H3BinaryTreeNode subclasses

struct H3WavFile : public H3BinaryItem // size 0x34 from 0x55C67E
{
	h3unk _f_1C[12];
	// * +28 fields of _RTL_CRITICAL_SECTION
	HANDLE lockSemaphore;
	// * +2C
	ULONG_PTR spinCount;
	// * +30
	PRTL_CRITICAL_SECTION_DEBUG debugInfo;
};

// * text file with a single column of text
struct H3ColumnTextFile : public H3BinaryItem
{
protected:
	// * +1C list of rows holding text, single column
	H3Vector<LPCSTR> text;
	// * +2C
	LPCSTR buffer;
	// the buffer size is not stored for this format
public:
	LPCSTR GetText(INT32 row) const { return text.m_first[row - 1]; } // using the index from TxtEdit
	static H3ColumnTextFile* Load(LPCSTR name) { return THISCALL_1(H3ColumnTextFile*, 0x55BDA0, name); }
	VOID UnLoad() { THISCALL_1(VOID, vTable->dereference, this); }
};

// * text file with a several columns of text
struct H3TextFile : public H3BinaryItem // size 0x34
{
protected:
	// * +1C list of rows holding lists of column text
	H3Vector<H3Vector<LPCSTR>*> text;
	// * +2C
	LPCSTR buffer;
	// * +30
	UINT buffer_size;
public:
	H3Vector<H3Vector<LPCSTR>*> & GetText() { return text; }
	INT32 CountRows() const { return text.Count(); }
	static H3TextFile* Load(LPCSTR name) { return THISCALL_1(H3TextFile*, 0x55C2B0, name); }
	VOID UnLoad() { THISCALL_1(VOID, vTable->dereference, this); }
};

struct H3RGB888
{
	UINT8 r;
	UINT8 g;
	UINT8 b;

	// * approximate darkening, but faster than hsv
	VOID Darken20()
	{
		r = ((r & 0xFE) >> 1) | (r & 0x80);
		g = ((r & 0xFE) >> 1) | (r & 0x80);
		b = ((r & 0xFE) >> 1) | (r & 0x80);
	}
	// * approximate darkening, but faster than hsv
	VOID Darken50()
	{
		r = ((r & 0xFE) >> 1);
		g = ((r & 0xFE) >> 1);
		b = ((r & 0xFE) >> 1);
	}
	VOID GrayScale()
	{
		const int c = std::max(r, std::max(g, b));
		int dr = c - r;
		int dg = c - g;
		int db = c - b;

		dr = (dr << 2) / 5;
		dg = (dg << 2) / 5;
		db = (db << 2) / 5;

		r += dr;
		g += dg;
		b += db;
	}

	// * darkens pixel's color through HSV by amount
	VOID Darken(const UINT8 amount);
	// * lightens pixel's color through HSV by amount
	VOID Lighten(const UINT8 amount);

	// * this assumes the source pixel has full alpha visibility
	VOID AlphaDraw(UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha);

	static FLOAT GetHueAsNormalizedFloat(UINT8 red, UINT8 green, UINT8 blue);
	static DWORD Pack(UINT8 red, UINT8 green, UINT8 blue) {	return blue + (green << 8) + (red << 16); }

	H3RGB888() {}
	H3RGB888(DWORD color)
	{
		b = color & 0xFF;
		g = (color >> 8) & 0xFF;
		r = (color >> 16) & 0xFF;
	}
	H3RGB888(UINT8 r, UINT8 g, UINT8 b)
	{
		this->b = b;
		this->g = g;
		this->r = r;
	}

	H3RGB888(H3RGB565& rgb);

	H3RGB888(H3ARGB888& rgb);

};

// * rgb pixel in HD mod
// * it is not argb or bgra but this order
struct H3ARGB888
{
	UINT8 a; // alpha - unused in H3
	UINT8 g;
	UINT8 r;
	UINT8 b;

	// * darkens pixel's color through HSV by amount
	VOID Darken(const UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Darken(amount);
		r =  rgb.r;
		g = rgb.g;
		b = rgb.b;
	}
	// * lightens pixel's color through HSV by amount
	VOID Lighten(const UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Lighten(amount);
		r =  rgb.r;
		g = rgb.g;
		b = rgb.b;
	}

	VOID GrayScale()
	{
		H3RGB888 rgb(*this);
		rgb.GrayScale();
		r = rgb.r;
		g = rgb.g;
		b = rgb.b;
	}

	H3ARGB888(UINT8 red, UINT8 blue, UINT8 green) :
		a(0), g(green), r(red), b(blue)	{}
};

struct H3RGB555 // https://docs.microsoft.com/en-us/windows/desktop/DirectShow/working-with-16-bit-rgb
{
protected:
	RGB555 bits;
public:
	UINT8 GetRed()	 const { return (bits & 0x7C00) >> 10; }
	UINT8 GetGreen() const { return (bits & 0x3E0) >> 5; }
	UINT8 GetBlue()	 const { return bits & 0x1F; }
	DWORD UnPack()	 const { return GetRed() << 16 | GetGreen() << 8 | GetBlue(); }

	static WORD Pack(UINT8 r, UINT8 g, UINT8 b) { return ((r / 8) & 0x1F) << 10 | ((g / 8) & 0x1F) << 5 | ((b / 8) & 0x1F);	}
	static DWORD Unpack(RGB555 rgb) { return (((((rgb & 0x7C00) >> 10) * 255 + 15) / 31) << 16) + (((((rgb & 0x3E0) >> 5) * 255 + 31) / 63) << 8) + (((rgb & 0x1F) * 255 + 15) / 31); }
	VOID PackRGB(UINT8 r, UINT8 g, UINT8 b) { bits = Pack(r, g, b); }
};

struct H3RGB565 // https://docs.microsoft.com/en-us/windows/desktop/DirectShow/working-with-16-bit-rgb
{
protected:
	RGB565 bits;
public:
	UINT8 GetRed()	  { return (bits & 0xF800) >> 11; }
	UINT8 GetRed8()	  { return (GetRed() * 255 + 15) / 31; }
	UINT8 GetGreen()  { return (bits & 0x7E0) >> 5; }
	UINT8 GetGreen8() { return (GetGreen() * 255 + 31) / 63; }
	UINT8 GetBlue()	  { return bits & 0x1F; }
	UINT8 GetBlue8()  { return (GetBlue() * 255 + 15) / 31; }
	DWORD GetRGB888() { return (GetRed8() << 16 | GetGreen8() << 8 | GetBlue8()); }
	RGB565 GetBits()  { return bits; }

	H3RGB565() {}
	H3RGB565(UINT8 r, UINT8 g, UINT8 b) { PackRGB565(r, g, b); }
	H3RGB565(DWORD color) { PackRGB565((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF); }
	H3RGB565(H3RGB888 color) { PackRGB565(color.r, color.g, color.b); }

	VOID SetBits(WORD color) { bits = color; }
	WORD PackRGB565(UINT8 r, UINT8 g, UINT8 b) { return bits = Pack(r, g, b); }
	WORD Pack(H3RGB888& rgb) { return bits = Pack(rgb.r, rgb.g, rgb.b); }

	static WORD Pack(UINT8 r, UINT8 g, UINT8 b) { return ((r / 8) & 0x1F) << 11 | ((g / 4) & 0x3F) << 5 | ((b / 8) & 0x1F);	}
	static DWORD Unpack(RGB565 rgb) { return (((((rgb & 0xF800) >> 11) * 255 + 15) / 31) << 16) + (((((rgb & 0x7E0) >> 5) * 255 + 31) / 63) << 8) + (((rgb & 0x1F) * 255 + 15) / 31); }

	// darkens pixel's color by amount
	VOID Darken(UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Darken(amount);
		Pack(rgb);
	}
	VOID Lighten(UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Lighten(amount);
		Pack(rgb);
	}
	VOID GrayScale()
	{
		H3RGB888 rgb(*this);
		rgb.GrayScale();
		Pack(rgb);
	}
};

struct H3HSV
{
protected:
	UINT8 h;
	UINT8 s;
	UINT8 v;
public:
	H3HSV() : h(), s(), v() { }
	H3HSV(H3HSV& other) : h(other.h), s(other.s), v(other.v) { }

	H3HSV(const H3RGB888& rgb)
	{
		ConvertFromRgb888(rgb);
	}
	// * based on https://stackoverflow.com/a/14733008
	H3HSV& ConvertFromRgb888(const H3RGB888& rgb)
	{
		const UINT8 rgb_min = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
		const UINT8 rgb_max = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

	    v = rgb_max;
	    if (v == 0)
	    {
	        h = 0;
	        s = 0;
	        return *this;
	    }

	    s = 255 * long(rgb_max - rgb_min) / v;
	    if (s == 0)
	    {
	        h = 0;
	        return *this;
	    }

	    if (rgb_max == rgb.r)
	        h = 0 + 43 * (rgb.g - rgb.b) / (rgb_max - rgb_min);
	    else if (rgb_max == rgb.g)
	        h = 85 + 43 * (rgb.b - rgb.r) / (rgb_max - rgb_min);
	    else
	        h = 171 + 43 * (rgb.r - rgb.g) / (rgb_max - rgb_min);

	    return *this;
	}
	H3RGB888 ConvertToRgb888() const
	{
		H3RGB888 rgb;

		if (s == 0)
	    {
	        rgb.r = v;
	        rgb.g = v;
	        rgb.b = v;
	        return rgb;
	    }

		const UINT8 region = h / 43;
		const UINT8 remainder = (h - (region * 43)) * 6;

		const UINT8 p = (v * (255 - s)) >> 8;
		const UINT8 q = (v * (255 - ((s * remainder) >> 8))) >> 8;
		const UINT8 t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	    switch (region)
	    {
	        case 0:
	            rgb.r = v; rgb.g = t; rgb.b = p;
	            break;
	        case 1:
	            rgb.r = q; rgb.g = v; rgb.b = p;
	            break;
	        case 2:
	            rgb.r = p; rgb.g = v; rgb.b = t;
	            break;
	        case 3:
	            rgb.r = p; rgb.g = q; rgb.b = v;
	            break;
	        case 4:
	            rgb.r = t; rgb.g = p; rgb.b = v;
	            break;
	        default:
	            rgb.r = v; rgb.g = p; rgb.b = q;
	            break;
	    }
	    return rgb;
	}
	VOID AddSaturation(UINT8 saturation) { s = std::min(255, s + saturation); }
	VOID RemoveSaturation(UINT8 saturation) { s = std::max(0, s - saturation); }
	VOID SetHue(UINT8 hue) { h = hue;}
	VOID AddValue(UINT8 value) { v = std::min(255, v + value); }
	VOID RemoveValue(UINT8 value) { v = std::max(0, v - value); }
};

struct H3Palette565 : public H3BinaryItem
{
	// * +1C
	H3RGB565 color[256];

	VOID ColorToPlayer(INT id) { FASTCALL_2(VOID, 0x6003E0, color, id); }
	VOID RotateColors(INT min_index, INT max_index, INT count = -1) { THISCALL_4(VOID, 0x522E40, this, min_index, max_index, count); }
	H3Palette565* Initiate() { return THISCALL_1(H3Palette565*, 0x522B40, this); }
};

struct H3Font : public H3BinaryItem
{
	h3unk _f_1C[32];
	// * +3C
	UINT8 width[3072]; // used to calculate line width
	// * +C3C
	UINT32 bufferOffsets[256]; // referenced at 0x4B4F1C
	// * +103C
	H3Palette565 palette;
	// * 1258
	PUINT8 bitmapBuffer; // how the characters look
	// * +125C
	INT32 bufferSize;

	INT32 GetLinesCountInText(LPCSTR str, INT32 width) { return THISCALL_3(INT32, 0x4B5580, this, str, width); }
	INT32 GetMaxLineWidth(LPCSTR str) { return THISCALL_2(INT32, 0x4B56F0, this, str); }
	INT32 GetMaxWordWidth(LPCSTR str) { return THISCALL_2(INT32, 0x4B5770, this, str); }
	VOID TextDraw(H3LoadedPCX16* pcx, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, NH3Dlg::TextColor::eTextColor colorIndex, NH3Dlg::TextAlignment::eTextAlignment alignment);
};

struct H3Palette888 : public H3BinaryItem
{
	// * +1C
	H3RGB888 color[256];

	VOID ColorToPlayer(INT id) { FASTCALL_2(VOID, 0x600400, this, id); }
	H3Palette888* Initiate() { return THISCALL_1(H3Palette888*, 0x523320, this); }
};

struct H3LoadedPCX : public H3BinaryItem // size 0x56C // vt 63BA14
{
	// * +1C
	INT32 bufSize;
	// * +20
	INT32 bufSizeUnk;
	// * +24
	INT32 width;
	// * +28
	INT32 height;
	// * +2C
	INT32 scanlineSize;
	// * +30
	// * 256-color indexed buffer
	PUINT8 buffer;
	// * +34
	H3Palette565 palette565;
	// * +250
	H3Palette888 palette888;

	VOID DrawToPcx16(int srcX, int srcY, int dx, int dy, H3LoadedPCX16 *dest, int destX, int destY, BOOL skip_transparent_colors)
	{
		THISCALL_9(VOID, 0x44FA80, this, srcX, srcY, dx, dy, dest, destX, destY, skip_transparent_colors);
	}
	VOID DrawToPcx(int src_x, int src_y, int dx, int dy, H3LoadedPCX* pcx_dest, int dest_x = 0, int dest_y = 0, BOOL copy_palette = TRUE);

	static H3LoadedPCX* Load(LPCSTR name) { return THISCALL_1(H3LoadedPCX*, 0x55AA10, name); }
	static H3LoadedPCX* Create(LPCSTR name, INT width, INT height);

	// * returns row start in buffer
	PUINT8 GetRow(int row) { return buffer + row * scanlineSize; }
	// * returns the color index of pixel (x, y) starting from top left
	PUINT8 GetPixelIndex(int x, int y) { return GetRow(y) + x; }
	// * fills rectangle with color index from palette565
	VOID FillRectangle(INT x, INT y, INT dx, INT dy, BYTE color_index);
};

class PcxLoader
{
	H3LoadedPCX* m_pcx;
public:
	PcxLoader() { m_pcx = nullptr; }
	PcxLoader(LPCSTR name)
	{
		m_pcx = H3LoadedPCX::Load(name);
	}
	VOID LoadPcx(LPCSTR name)
	{
		m_pcx = H3LoadedPCX::Load(name);
	}
	~PcxLoader()
	{
		if (m_pcx)
			m_pcx->Dereference();
	}
	H3LoadedPCX* GetPcx() const { return m_pcx; }
};

struct H3LoadedPCX16 : public H3BinaryItem // size 0x38 // vt 63B9C8
{
	// * +1C
	INT32 buffSize;
	// * +20
	INT32 buffSizeUnk;
	// * +24
	INT32 width;
	// * +28
	INT32 height;
	// * +2C
	INT32 scanlineSize;
	// * +30
	// * H3RGB565 buffer unless bitmode == 4
	// * in which case this is a H3ARGB888 buffer
	PUINT8 buffer;
	BOOL8 keep_buffer; // see 0x44DDE0
	h3unk _f_35[3];

	H3LoadedPCX16* Construct(LPCSTR name, INT width, INT height)
	{
		return THISCALL_4(H3LoadedPCX16*, 0x44DD20, this, name, width, height);
	}
	VOID DrawToPcx16(INT x, INT y, BOOL transparent, H3LoadedPCX16 *dest, INT srcX = 0, INT srcY = 0)
	{
		return THISCALL_12(VOID, 0x44DF80, this, srcX, srcY, width, height, dest->buffer, x,y, dest->width, dest->height, dest->scanlineSize, transparent);
	}
	static H3LoadedPCX16* Load(LPCSTR name) { return THISCALL_1(H3LoadedPCX16*, 0x55B1E0, name); }
	static H3LoadedPCX16* Create(LPCSTR name, INT width, INT height);

	VOID Destroy(BOOL destroy_buffer = TRUE) { THISCALL_2(VOID, 0x44DCF0, this, destroy_buffer); }
	// * darkens RGB by about 50%
	VOID DrawShadow(INT x, INT y, INT dw, INT dh) { THISCALL_5(VOID, 0x44E2C0, this, x, y, dw, dh); };

	VOID FillRectangle(INT x, INT y, INT w, INT h, BYTE r, BYTE g, BYTE b);
	VOID FillRectangle(INT x, INT y, INT w, INT h, DWORD color) { FillRectangle(x, y, w, h, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF); }

	VOID DrawFrame(INT x, INT y, INT w, INT h, BYTE r = 232, BYTE g = 212, BYTE b = 120);

	VOID DarkenArea(INT x, INT y, INT w, INT h, UINT8 amount);
	VOID LightenArea(INT x, INT y, INT w, INT h, UINT8 amount);
	VOID GrayScaleArea(INT x, INT y, INT w, INT h);

	// * based on HSV color model, not RGB
	// * hue is on the scale 0~1 and represents the color scheme
	// * saturation is also scaled between 0 ~ 1 and represents
	// * value is fixed
	VOID DrawHue(INT x, INT y, INT w, INT h, FLOAT hue, FLOAT saturation) { THISCALL_7(VOID, 0x44E610, this, x, y, w, h, hue, saturation); }

	BOOL BackgroundRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL is_blue);
	BOOL SimpleFrameRegion(INT32 x, INT32 y, INT32 w, INT32 h);
	BOOL FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue);

	// * adds a 1 pixel border around the designated area to make it look
	// * as if the contents were lowered
	VOID SinkArea(INT32 x, INT32 y, INT32 w, INT32 h);
	// * adds a 1 pixel border around the designated area to make it look
	// * as if the contents were elevated
	VOID BevelArea(INT32 x, INT32 y, INT32 w, INT32 h);
	// * Draws text on the pcx
	VOID TextDraw(H3Font* font, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, NH3Dlg::TextColor::eTextColor colorIndex, NH3Dlg::TextAlignment::eTextAlignment alignment);

protected:
	// * returns row start in buffer
	PUINT8 GetRow(int row) { return buffer + row * scanlineSize; }
	// * returns rgb565 pixel at coordinates (x,y) in buffer
	// * !WARNING! This is only valid when h3_BitMode == 2 aka default
	H3RGB565* GetPixel565(int x, int y) { return (H3RGB565*)GetRow(y) + x; };
	// * returns rgb565 pixel at coordinates (x,y) in buffer
	// * !WARNING! This is only valid when h3_BitMode == 4 aka TRUE mode with HDmod
	H3ARGB888* GetPixel888(int x, int y) { return (H3ARGB888*)GetRow(y) + x; };
};

class Pcx16Loader
{
	H3LoadedPCX16* pcx;
public:
	Pcx16Loader(LPCSTR name)
	{
		pcx = H3LoadedPCX16::Load(name);
	}
	~Pcx16Loader()
	{
		if (pcx)
			pcx->Dereference();
	}
	H3LoadedPCX16* GetPcx() { return pcx; }
};

struct H3LoadedPCX24 : public H3BinaryItem // size 0x30 // vt 63B9F4
{
	// * +1C
	INT32 buffSize;
	// * +20
	INT32 buffSizeUnk;
	// * +24
	INT32 width;
	// * +28
	INT32 height;
	// * +2C
	// * RGB888 buffer
	PUINT8 buffer;

	// * data argument can be NULL if needed, in this case no pixels will be copied
	// * you should still set dataSize as that is sent to buffSize
	// * dataSize = width * height * 3
	H3LoadedPCX24* Construct(LPCSTR name, INT width, INT height, PUINT8 data, UINT32 dataSize)
	{
		return THISCALL_6(H3LoadedPCX24*, 0x44EA20, this, name, width, height, data, dataSize);
	}
	// * converts RGB888 to RGB565
	// * if True mode, copies to ARGB888
	VOID DrawToPcx16(INT dst_x, INT dst_y, H3LoadedPCX16 *dest, INT srcX = 0, INT srcY = 0)
	{
		return THISCALL_11(VOID, 0x44ECE0, this, srcX, srcY, width, height, dest->buffer, dst_x, dst_y, dest->width, dest->height, dest->scanlineSize);
	}

	static H3LoadedPCX24* Load(LPCSTR name, INT width, INT height)
	{
		H3LoadedPCX24* pcx = (H3LoadedPCX24*)F_malloc(sizeof(H3LoadedPCX24));
		UINT32 data_size = width * height * sizeof(H3RGB888);
		PUINT8 buffer = (PUINT8)F_malloc(data_size);
		pcx->Construct(name, width, height, buffer, data_size);
		return pcx;
	}

	// * returns row start in buffer
	PUINT8 GetRow(int row) { return buffer + row * sizeof(H3RGB888) * width; }
	// * returns rgb888 pixel at coordinates (x, y) in buffer
	H3RGB888* GetPixel(int x, int y) { return (H3RGB888*)GetRow(y) + x; }
};

class Pcx24Loader
{
	H3LoadedPCX24* pcx;
public:
	Pcx24Loader(LPCSTR name, INT32 width, INT32 height)
	{
		pcx = H3LoadedPCX24::Load(name, width, height);
	}
	~Pcx24Loader()
	{
		if (pcx)
			pcx->Dereference();
	}
	H3LoadedPCX24* GetPcx() { return pcx; }
};

struct H3DefFrame : public H3BinaryItem
{
	// * +1C
	// * all row offsets and actual pixel data
	INT32 rawDataSize;
	// * +20
	// * frame width * frame height
	INT32 dataSize;
	// * +24
	INT32 compressionType;
	// * +28
	INT32 width;
	// * +2C
	INT32 height;
	// * +30
	INT32 frameWidth;
	// * +34
	INT32 frameHeight;
	// * +38
	// * marginLeft + frameWidth = width
	INT32 marginLeft;
	// * +3C
	INT32 marginTop;
	// * +40
	INT32 width2;
	// * +44
	// * pixel index and such.
	PUINT8 rawData;

	VOID DrawToPcx16(INT src_x, INT src_y, INT src_width, INT src_height, H3LoadedPCX16 *pcx16, INT dst_x, INT dst_y, H3Palette565 *palette565, BOOL mirror = FALSE, BOOL do_not_use_special_colors = TRUE)
	{
		THISCALL_14(VOID, 0x47BE90, this, src_x, src_y, src_width, src_height, pcx16->buffer, dst_x, dst_y, pcx16->width, pcx16->height, pcx16->scanlineSize, palette565,  mirror, do_not_use_special_colors);
	}
};

// * Not a binary item but relevant to H3LoadedDEF and H3DefFrame
struct H3DefGroup
{
	// * +0
	int count;
	// * +4
	int spritesSize;
	// * +8
	H3DefFrame **frames;
};

struct H3LoadedDEF : public H3BinaryItem
{
	// * +1C
	H3DefGroup **groups;
	// * +20
	H3Palette565 *palette565;
	// * +24
	H3Palette888 *palette888;
	// * +28
	INT32 groupsCount;
	// * +2C
	INT32 *activeGroups;
	// * +30
	INT32 widthDEF;
	// * +34
	INT32 heightDEF;

	// * for creature animation groups
	enum CreatureGroups
	{
		CG_MOVING = 0,
		CG_MOUSE_OVER = 1,
		CG_STANDING = 2,
		CG_GETTING_HIT = 3,
		CG_DEFEND = 4,
		CG_DEATH = 5,
		CG_UNUSED_DEATH = 6,
		CG_TURN_LEFT = 7,
		CG_TURN_RIGHT = 8,
		CG_TURN_LEFT2 = 9,
		CG_TURN_RIGHT2 = 10,
		CG_ATTACK_UP = 11,
		CG_ATTACK_STRAIGHT = 12,
		CG_ATTACK_DOWN = 13,
		CG_SHOOT_UP = 14,
		CG_SHOOT_STRAIGHT = 15,
		CG_SHOOT_DOWN = 16,
		CG_SPELL_ATTACK_UP = 17,
		CG_SPELL_ATTACK_STRAIGHT = 18,
		CG_SPELL_ATTACK_DOWN = 19,
		CG_START_MOVING = 20,
		CG_STOP_MOVING = 21
	};

	static H3LoadedDEF* Load(LPCSTR name) { return THISCALL_1(H3LoadedDEF*, 0x55C9C0, name); }
	VOID AddFrameFromDef(LPCSTR source, INT32 index);
	VOID ColorToPlayer(INT32 id);
	H3DefFrame *GetGroupFrame(INT group, INT frame)
	{
		return groups[group]->frames[frame];
	}
	VOID DrawTransparent(INT32 frame, H3LoadedPCX16 *pcx, INT32 x, INT32 y, BOOL transparent = TRUE, BOOL mirror = FALSE, INT32 group = 0, INT32 xFromRight = 0, INT32 yFromBottom = 0)
	{
		THISCALL_15(VOID, 0x47BA90, this, group, frame, xFromRight, yFromBottom, widthDEF, heightDEF, pcx->buffer, x, y, pcx->width, pcx->height, pcx->scanlineSize, mirror, transparent);
	}
	VOID DrawToPcx16(INT group, INT frame, INT src_x, INT src_y, INT src_width, INT src_height, H3LoadedPCX16 *pcx16, INT dst_x, INT dst_y, BOOL mirror = FALSE, BOOL do_not_use_special_colors = TRUE)
	{
		GetGroupFrame(group, frame)->DrawToPcx16(src_x, src_y, src_width, src_height, pcx16, dst_x, dst_y, palette565, mirror, do_not_use_special_colors);
	}
};

class DefLoader
{
	H3LoadedDEF* def;
public:
	DefLoader(LPCSTR name)
	{
		def = H3LoadedDEF::Load(name);
	}
	~DefLoader()
	{
		if (def)
			def->Dereference();
	}
	H3LoadedDEF* GetDef() { return def; }
};

#pragma pack(pop)

inline H3BinaryTreeNode * H3BinTreeList::FindItem(LPCSTR name)
{
	H3BinaryTreeNode* node = THISCALL_2(H3BinaryTreeNode*, 0x55EE00, this, name);
	if (node == root)
		return nullptr;
	if (F_strcmpi(node->data.name, name))
		return nullptr;
	return node;
}

inline VOID H3BinTreeList::AddItem(H3BinaryItem * item)
{
	return item->AddToBinaryTree(this);
}

inline VOID H3BinTreeList::RemoveItem(H3BinaryTreeNode * node)
{
	H3BinaryTreeNode* temp;
	THISCALL_3(VOID, 0x55DF20, this, &temp, node);
}

inline VOID H3BinTreeList::RemoveItem(LPCSTR name)
{
	if (!name)
		return;
	H3BinaryTreeNode* node = FindItem(name);
	if (node == root)
		return;
	if (F_strcmpi(node->data.name, name))
		return;
	RemoveItem(node);
}

inline VOID H3BinaryItem::AddToBinaryTree(H3BinTreeList* tree)
{
	H3BinaryTreeNode::BinaryItemData base;
	for (int i = 0; i < sizeof(base.name); ++i)
		base.name[i] = name[i];
	base.name_end = 0;
	base.item = this;
	struct returnValues
	{
		H3BinaryTreeNode *node;
		INT refCount;
	}retValues;

	THISCALL_3(returnValues*, 0x55DDF0, tree, &retValues, &base);
}

inline VOID H3RGB888::Darken(const UINT8 amount)
{
	H3HSV hsv(*this);
	hsv.RemoveValue(amount);
	*this = hsv.ConvertToRgb888();
}

inline VOID H3RGB888::Lighten(const UINT8 amount)
{
	H3HSV hsv(*this);
	hsv.AddValue(amount);
	*this = hsv.ConvertToRgb888();
}

inline VOID H3RGB888::AlphaDraw(UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha)
{
	// no weight
	if (alpha == 0)
		return;
	// full weight
	if (alpha == 255)
	{
		r = red;
		g = green;
		b = blue;
		return;
	}
	// how much weight does the existing color has
	const int dest_weight = 255 - alpha;

	const int weighted_r = alpha * red + dest_weight * r;
	r = weighted_r / 255;

	const int weighted_g = alpha * green + dest_weight * g;
	g = weighted_g / 255;

	const int weighted_b = alpha * blue + dest_weight * b;
	b = weighted_b / 255;
}

inline FLOAT H3RGB888::GetHueAsNormalizedFloat(UINT8 red, UINT8 green, UINT8 blue)
{
	int c_min = std::min(std::min(red, green), blue);
	int c_max = std::max(std::max(red, green), blue);
	if (c_min == c_max)
		return 0.0f;
	FLOAT hue;
	if (c_max == red)
		hue = FLOAT(green - blue) / FLOAT(c_max - c_min);
	else if (c_max == green)
		hue = 2.0f + FLOAT(blue - red) / FLOAT(c_max - c_min);
	else
		hue = 4.0f + FLOAT(red - green) / FLOAT(c_max - c_min);

	hue /= 6.0f;

	if (hue < 0.0f)
		hue += 1.0f;

	return hue;
}

inline H3LoadedPCX16 * H3LoadedPCX16::Create(LPCSTR name, INT width, INT height)
{
	H3LoadedPCX16 *pcx16 = reinterpret_cast<H3LoadedPCX16*>(F_malloc(sizeof(H3LoadedPCX16)));
	if (!pcx16)
		return nullptr;
	return pcx16->Construct(name, width, height);
}

inline VOID H3LoadedPCX16::FillRectangle(INT x, INT y, INT w, INT h, BYTE r, BYTE g, BYTE b)
{
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	INT _w = std::min(w, width - x);
	INT _h = std::min(h, height - y);

	if (h3_BitMode == 4) // RGB888 mode
	{
		H3ARGB888 color(r, g, b);
		H3ARGB888 *rgb_row = reinterpret_cast<H3ARGB888 *>(GetRow(y));
		rgb_row += x;
		for (int j = 0; j < _h; ++j)
		{
			H3ARGB888 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				*rgb = color;

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = reinterpret_cast<H3RGB565 *>(GetRow(y));
		rgb_row += x;
		H3RGB565 color(r, g, b);
		for (int j = 0; j < _h; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->SetBits(color.GetBits());

			rgb_row = reinterpret_cast<H3RGB565*>(PUINT8(rgb_row) + scanlineSize);
		}
	}
}

inline VOID H3LoadedPCX16::DrawFrame(INT x, INT y, INT w, INT h, BYTE r, BYTE g, BYTE b)
{
	FillRectangle(x, y, w, 1, r, g, b);
	FillRectangle(x, y + 1, 1, h - 2, r, g, b);
	FillRectangle(x + w - 1, y + 1, 1, h - 2, r, g, b);
	FillRectangle(x, y + h - 1, w, 1, r, g, b);
}

inline VOID H3LoadedPCX16::DarkenArea(INT x, INT y, INT w, INT h, UINT8 amount)
{
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	INT w_ = std::min(w, width - x);
	INT h_ = std::min(h, height - y);

	if (h3_BitMode == 4) // RGB888 mode
	{
		H3ARGB888 *rgb_row = reinterpret_cast<H3ARGB888 *>(GetRow(y));
		rgb_row += x;
		for (int j = 0; j < h_; ++j)
		{
			H3ARGB888 *rgb = rgb_row;

			for (int i = 0; i < w_; ++i, ++rgb)
				rgb->Darken(amount);

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = reinterpret_cast<H3RGB565 *>(GetRow(y));
		rgb_row += x;

		for (int j = 0; j < h_; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < w_; ++i, ++rgb)
				rgb->Darken(amount);

			rgb_row = reinterpret_cast<H3RGB565*>(PUINT8(rgb_row) + scanlineSize);
		}
	}
}

inline VOID H3LoadedPCX16::LightenArea(INT x, INT y, INT w, INT h, UINT8 amount)
{
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	INT w_ = std::min(w, width - x);
	INT h_ = std::min(h, height - y);

	if (h3_BitMode == 4) // RGB888 mode
	{
		H3ARGB888 *rgb_row = reinterpret_cast<H3ARGB888 *>(GetRow(y));
		rgb_row += x;
		for (int j = 0; j < h_; ++j)
		{
			H3ARGB888 *rgb = rgb_row;

			for (int i = 0; i < w_; ++i, ++rgb)
				rgb->Lighten(amount);

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = reinterpret_cast<H3RGB565 *>(GetRow(y));
		rgb_row += x;

		for (int j = 0; j < h_; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < w_; ++i, ++rgb)
				rgb->Lighten(amount);

			rgb_row = reinterpret_cast<H3RGB565*>(PUINT8(rgb_row) + scanlineSize);
		}
	}
}

inline VOID H3LoadedPCX16::GrayScaleArea(INT x, INT y, INT w, INT h)
{
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	INT _w = std::min(w, width - x);
	INT _h = std::min(h, height - y);

	if (h3_BitMode == 4) // RGB888 mode
	{
		H3ARGB888 *rgb_row = reinterpret_cast<H3ARGB888 *>(GetRow(y));
		rgb_row += x;
		for (int j = 0; j < _h; ++j)
		{
			H3ARGB888 *rgb = rgb_row;
			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->GrayScale();

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = reinterpret_cast<H3RGB565 *>(GetRow(y));
		rgb_row += x;

		for (int j = 0; j < _h; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->GrayScale();

			rgb_row = reinterpret_cast<H3RGB565*>(reinterpret_cast<PUINT8>(rgb_row) + scanlineSize);
		}
	}
}

inline BOOL H3LoadedPCX16::BackgroundRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL is_blue)
{
	PcxLoader back(is_blue ? NH3Dlg::HDassets::DLGBLUEBACK : NH3Dlg::Assets::DIBOXBACK);

	if (back.GetPcx() == nullptr)
		return FALSE;

	int _y = y;
	int _h = h;

	// * add background region
	while (_h > 0)
	{
		int _x = x;
		int dh = std::min(256, _h);
		int _w = w;
		while (_w > 0)
		{
			back.GetPcx()->DrawToPcx16(0, 0, _w, dh, this, _x, _y, FALSE);
			_x += 256;
			_w -= 256;
		}
		_y += 256;
		_h -= 256;
	}

	return TRUE;
}

inline BOOL H3LoadedPCX16::SimpleFrameRegion(INT32 xStart, INT32 yStart, INT32 _width, INT32 _height)
{
	INT32 dX = _width;
	INT32 dY = _height;
	INT32 xEnd = xStart + _width;
	INT32 yEnd = yStart + _height;
	if (dX < 4 || dY < 4)
		return FALSE;

	// * helper struct
	struct Frames
	{
		enum
		{
			up,
			down,
			left,
			right,
			tl,
			tr,
			bl,
			br
		};

		PcxLoader m_frames[8];
		H3LoadedPCX16 *m_tgt;
		Frames(H3LoadedPCX16* bg) : m_tgt(bg)
		{
			m_frames[up].LoadPcx(NH3Dlg::HDassets::FRAME_U);
			m_frames[down].LoadPcx(NH3Dlg::HDassets::FRAME_D);
			m_frames[left].LoadPcx(NH3Dlg::HDassets::FRAME_L);
			m_frames[right].LoadPcx(NH3Dlg::HDassets::FRAME_R);
			m_frames[tl].LoadPcx(NH3Dlg::HDassets::FRAME_LU);
			m_frames[tr].LoadPcx(NH3Dlg::HDassets::FRAME_RU);
			m_frames[bl].LoadPcx(NH3Dlg::HDassets::FRAME_LD);
			m_frames[br].LoadPcx(NH3Dlg::HDassets::FRAME_RD);
		}
		BOOL AllLoaded() const
		{
			for (int i = 0; i < 8; ++i)
				if (m_frames[i].GetPcx() == nullptr)
					return FALSE;
			return TRUE;
		}

		VOID Draw(const INT x, const INT y, const INT frame) const
		{
			m_frames[frame].GetPcx()->DrawToPcx16(0, 0, 4, 4, m_tgt, x, y, FALSE);
		}
	};

	Frames frames(this);
	if (!frames.AllLoaded())
		return FALSE;

	////////////////////////////////////////
	// do horizontal sides - bottom to top
	////////////////////////////////////////
	while (dX >= 4)
	{
		dX -= 4;
		frames.Draw(xStart + dX, yStart,   frames.up);
		frames.Draw(xStart + dX, yEnd - 4, frames.down);
	}

	////////////////////////////////////////
	// do vertical sides - right to left
	////////////////////////////////////////
	while (dY >= 4)
	{
		dY -= 4;
		frames.Draw(xStart,   yStart + dY, frames.left);
		frames.Draw(xEnd - 4, yStart + dY, frames.right);
	}

	////////////////////
	// Add corners
	////////////////////
	frames.Draw(xStart,   yStart,   frames.tl);
	frames.Draw(xStart,   yEnd - 4, frames.bl);
	frames.Draw(xEnd - 4, yStart,   frames.tr);
	frames.Draw(xEnd - 4, yEnd - 4, frames.br);

	return TRUE;
}

inline BOOL H3LoadedPCX16::FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue)
{
	enum BoxFrames
	{
		BF_tl,
		BF_tr,
		BF_bl,
		BF_br,
		BF_ml,
		BF_mr,
		BF_tm,
		BF_bm,
		BF_blstat,
		BF_brstat,
		BF_bmstat
	};

	DefLoader box(is_blue ? NH3Dlg::HDassets::DLGBLUEBOX : NH3Dlg::Assets::DLGBOX);
	if (box.GetDef() == nullptr)
		return FALSE;

	// * copying to this local palette prevents recoloration of def for others
	H3Palette565 pal565, *pal;
	if (!is_blue)
	{
		F_memcpy(&pal565, box.GetDef()->palette565, sizeof(pal565));
		pal565.ColorToPlayer(colorIndex);
		pal = &pal565;
	}
	else
		pal = box.GetDef()->palette565;

	INT f_bl, f_br, f_bm;
	if (statusBar)
	{
		f_bl = BoxFrames::BF_blstat;
		f_br = BoxFrames::BF_brstat;
		f_bm = BoxFrames::BF_bmstat;
	}
	else
	{
		f_bl = BoxFrames::BF_bl;
		f_br = BoxFrames::BF_br;
		f_bm = BoxFrames::BF_bm;
	}

	// * add horizontal bars
	int _w = w - 64 - 64;
	H3DefFrame *tm = box.GetDef()->GetGroupFrame(0, BoxFrames::BF_tm);
	H3DefFrame *bm = box.GetDef()->GetGroupFrame(0, f_bm);
	while (_w > 0)
	{
		tm->DrawToPcx16(0, 0, 64, 64, this, x + _w, y, pal);
		bm->DrawToPcx16(0, 0, 64, 64, this, x + _w, y + h - 64, pal);
		_w -= 64;
	}

	// * add vertical bars
	int _h = h - 64 - 64;
	H3DefFrame *ml = box.GetDef()->GetGroupFrame(0, BoxFrames::BF_ml);
	H3DefFrame *mr = box.GetDef()->GetGroupFrame(0, BoxFrames::BF_mr);
	while (_h > 0)
	{
		ml->DrawToPcx16(0, 0, 64, 64, this, x, y + _h, pal);
		mr->DrawToPcx16(0, 0, 64, 64, this, x + w - 64, y + _h, pal);
		_h -= 64;
	}

	// * add four corners
	box.GetDef()->GetGroupFrame(0, BoxFrames::BF_tl)->DrawToPcx16(0, 0, 64, 64, this, x, y, pal);
	box.GetDef()->GetGroupFrame(0, BoxFrames::BF_tr)->DrawToPcx16(0, 0, 64, 64, this, x + w - 64, y, pal);
	box.GetDef()->GetGroupFrame(0, f_bl)->DrawToPcx16(0, 0, 64, 64, this, x, y + h - 64, pal);
	box.GetDef()->GetGroupFrame(0, f_br)->DrawToPcx16(0, 0, 64, 64, this, x + w - 64, y + h - 64, pal);

	return TRUE;
}

inline VOID H3LoadedPCX16::SinkArea(INT32 x, INT32 y, INT32 w, INT32 h)
{
	// * at the very minimum, we're gonna want to shade a 3x3 rectangle
	// * border to have 1 pixel within
	if (x >= width - 2 || y >= height - 2 || w <= 2 || h <= 2)
		return;
	int _x = std::max(x, 0);
	int _y = std::max(y, 0);
	int _w = std::min(w, width - _x);
	int _h = std::min(h, height - _y);

	DarkenArea(_x, _y, _w - 1, 1, 50);
	DarkenArea(_x, _y + 1, 1, _h - 2, 50);
	LightenArea(_x + 1, _y + _h - 1, _w - 1, 1, 50);
	LightenArea(_x + _w - 1, _y + 1, 1, _h - 2, 50);
}

inline VOID H3LoadedPCX16::BevelArea(INT32 x, INT32 y, INT32 w, INT32 h)
{
	// * at the very minimum, we're gonna want to shade a 3x3 rectangle
	// * border to have 1 pixel within
	if (x >= width - 2 || y >= height - 2 || w <= 2 || h <= 2)
		return;
	int _x = std::max(x, 0);
	int _y = std::max(y, 0);
	int _w = std::min(w, width - _x);
	int _h = std::min(h, height - _y);

	LightenArea(_x, _y, _w, 1, 50);
	LightenArea(_x, _y + 1, 1, _y + _h - 2, 50);
	DarkenArea(_x + 1, _y + _h - 1, _w - 1, 1, 50);
	DarkenArea(_x + _w, _y + 1, 1, _h - 2, 50);
}

inline VOID H3LoadedPCX16::TextDraw(H3Font* font, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height,	NH3Dlg::TextColor::eTextColor colorIndex, NH3Dlg::TextAlignment::eTextAlignment alignment)
{
	THISCALL_10(VOID, 0x4B51F0, font, text, this, x, y, width, height, colorIndex, alignment, -1);
}

inline VOID H3LoadedDEF::AddFrameFromDef(LPCSTR source, INT32 index)
{
	H3LoadedDEF *src = H3LoadedDEF::Load(source);
	if (!src)
		return;
	H3DefFrame *frm = src->groups[0]->frames[0];
	H3DefGroup *grp = groups[0];

	H3DefFrame *frame = reinterpret_cast<H3DefFrame *>(F_malloc(sizeof(H3DefFrame)));
	if (frame)
	{
		F_memcpy(frame, frm, sizeof(H3DefFrame)); // copy frame data
		frame->rawData = reinterpret_cast<PUINT8>(F_malloc(frame->rawDataSize)); // new data buffer
		F_memcpy(frame->rawData, frm->rawData, frame->rawDataSize); // copy data buffer

		const int n_frames = grp->count;

		if (n_frames < index + 1) // add room for frame
		{
			H3DefFrame ** new_list = reinterpret_cast<H3DefFrame**>(F_realloc(grp->frames, (index + 1) * 4));
			if (new_list)
			{
				new_list[index] = frame;
				grp->count = index + 1;
				grp->spritesSize = index + 1;
				grp->frames = new_list;
			}
		}
		else
			grp->frames[index] = frame;
	}
	src->Dereference(); // get rid of source
}

inline VOID H3LoadedDEF::ColorToPlayer(INT32 id)
{
	if (palette565)
		palette565->ColorToPlayer(id);
	palette888->ColorToPlayer(id);
}

inline H3RGB888::H3RGB888(H3RGB565& rgb) :
	r(rgb.GetRed8()), g(rgb.GetGreen8()), b(rgb.GetBlue8()) { }

inline H3RGB888::H3RGB888(H3ARGB888& rgb) :
	r(rgb.r), g(rgb.g), b(rgb.b) { }

inline VOID H3Font::TextDraw(H3LoadedPCX16* pcx, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, NH3Dlg::TextColor::eTextColor colorIndex, NH3Dlg::TextAlignment::eTextAlignment alignment)
{
	pcx->TextDraw(this, text, x, y, width, height, colorIndex, alignment);
}

inline H3LoadedPCX * H3LoadedPCX::Create(LPCSTR name, INT width, INT height)
{
	H3LoadedPCX *pcx = reinterpret_cast<H3LoadedPCX*>(F_malloc(sizeof(H3LoadedPCX)));
	if (!pcx)
		return nullptr;

	pcx->InitiateBinary(name, 16); // see 0x44F5CC
	pcx->vTable = reinterpret_cast<BinaryVTable*>(0x63BA14);
	pcx->width = width;
	pcx->height = height;
	// round up to nearest 4
	pcx->scanlineSize = ((width + 3) >> 2) << 2;
	pcx->bufSize = height * pcx->scanlineSize;
	pcx->bufSizeUnk = pcx->bufSize;
	pcx->buffer = reinterpret_cast<PUINT8>(F_malloc(pcx->bufSize));
	if (!pcx->buffer)
	{
		F_delete(pcx);
		return nullptr;
	}
	pcx->palette565.Initiate();
	pcx->palette888.Initiate();

	return pcx;
}

inline VOID H3LoadedPCX::DrawToPcx(int src_x, int src_y, const int dx, const int dy, H3LoadedPCX* pcx_dest, int dest_x, int dest_y, const BOOL copy_palette)
{
	if (pcx_dest == nullptr || dx <= 0 || dy <= 0)
		return;

	if (src_x < 0)
		src_x = 0;
	if (src_y < 0)
		src_y = 0;
	if (dest_x < 0)
		dest_x = 0;
	if (dest_y < 0)
		dest_y = 0;

	const int w = std::min(dx, std::min(width - src_x, pcx_dest->width - dest_x));
	const int h = std::min(dy, std::min(height - src_y, pcx_dest->height - dest_y));

	if (w <= 0 || h <= 0)
		return;

	PUINT8 p_src = GetPixelIndex(src_x, src_y);
	PUINT8 p_dest = pcx_dest->GetPixelIndex(dest_x, dest_y);

	for (int j = 0; j < h; ++j)
	{
		PUINT8 dst = p_dest;
		PUINT8 src = p_src;
		for (int i = 0; i < w; ++i, ++dst, ++src)
			*dst = *src;
		p_dest += pcx_dest->scanlineSize;
		p_src += scanlineSize;
	}

	if (copy_palette)
	{
		F_memcpy(pcx_dest->palette565.color, palette565.color, sizeof(palette565.color));
		F_memcpy(pcx_dest->palette888.color, palette888.color, sizeof(palette888.color));
	}
}

inline VOID H3LoadedPCX::FillRectangle(INT x, INT y, INT dx, INT dy, BYTE color_index)
{
	const INT l_x = std::max(x, 0);
	const INT l_y = std::max(y, 0);
	if (dx < 0)
		dx = 0;
	if (dy < 0)
		dy = 0;
	dx = std::min(width - l_x, dx);
	dy = std::min(width - l_y, dy);

	PUINT8 start = GetPixelIndex(l_x, l_y);

	for (int j = 0; j < dy; ++j)
	{
		PUINT8 pixel = start;
		for (int i = 0; i < dx; ++i, ++pixel)
			*pixel = color_index;
		start += scanlineSize;
	}
}

#endif /* #define _H3BINARYITEMS_H_ */