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

	H3BinaryItem* GetBinaryItem() { return data.item; }
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
		THISCALL_3(H3BinaryItem*, 0x558970, this, name, type);
	}
	VOID Dereference() { THISCALL_1(VOID, vTable->dereference, this); }
	VOID AddToBinaryTree(H3BinTreeList* tree = (H3BinTreeList*)0x69E560);
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
	inline LPCSTR GetText(INT32 row) { return text.m_first[row - 1]; } // using the index from TxtEdit
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
	INT32 CountRows() { return text.Count(); }
	static H3TextFile* Load(LPCSTR name) { return THISCALL_1(H3TextFile*, 0x55C2B0, name); }
	VOID UnLoad() { THISCALL_1(VOID, vTable->dereference, this); }
};

struct H3RGB888
{
	UINT8 r;
	UINT8 g;
	UINT8 b;

	VOID Darken20()
	{
		r = ((r & 0xFE) >> 1) | (r & 0x80);
		g = ((r & 0xFE) >> 1) | (r & 0x80);
		b = ((r & 0xFE) >> 1) | (r & 0x80);
	}
	VOID Darken50()
	{
		r = ((r & 0xFE) >> 1);
		g = ((r & 0xFE) >> 1);
		b = ((r & 0xFE) >> 1);
	}

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
};

// * rgb pixel in HD mod
// * it is not argb or bgra but this order
struct H3ARGB888
{
	UINT8 a; // alpha - unused in H3
	UINT8 g;
	UINT8 r;
	UINT8 b;
	// darkens pixel's color by ~20%
	VOID Darken20()
	{
		r -= r / 5;
		g -= g / 5;
		b -= b / 5;
	}
	// darkens pixel's color by ~50%
	VOID Darken50()
	{
		r /= 2;
		g /= 2;
		b /= 2;
	}
	VOID Lighten20()
	{
		int _r = r;
		int _g = g;
		int _b = b;
		r = min(_r + _r / 5, 0xFF);
		g = min(_g + _g / 5, 0xFF);
		b = min(_b + _b / 5, 0xFF);
	}
	VOID Lighten50()
	{
		int _r = r;
		int _g = g;
		int _b = b;
		r = min(_r + _r / 2, 0xFF);
		g = min(_g + _g / 2, 0xFF);
		b = min(_b + _b / 2, 0xFF);
	}

	H3ARGB888(UINT8 red, UINT8 blue, UINT8 green) :
		a(0), g(green), r(red), b(blue)
	{}

};

struct H3RGB555 // https://docs.microsoft.com/en-us/windows/desktop/DirectShow/working-with-16-bit-rgb
{
protected:
	RGB555 bits;
public:
	const UINT8 GetRed()	const { return (bits & 0x7C00) >> 10; }
	const UINT8 GetGreen()	const { return (bits & 0x3E0) >> 5; }
	const UINT8 GetBlue()	const { return bits & 0x1F; }
	const DWORD UnPack()	const { return GetRed() << 16 | GetGreen() << 8 | GetBlue(); }

	static WORD Pack(UINT8 r, UINT8 g, UINT8 b) { return ((r / 8) & 0x1F) << 10 | ((g / 8) & 0x1F) << 5 | ((b / 8) & 0x1F);	}
	static DWORD Unpack(RGB555 rgb) { return (((((rgb & 0x7C00) >> 10) * 255 + 15) / 31) << 16) + (((((rgb & 0x3E0) >> 5) * 255 + 31) / 63) << 8) + (((rgb & 0x1F) * 255 + 15) / 31); }
	VOID PackRGB(UINT8 r, UINT8 g, UINT8 b) { bits = Pack(r, g, b); }
};

struct H3RGB565 // https://docs.microsoft.com/en-us/windows/desktop/DirectShow/working-with-16-bit-rgb
{
protected:
	RGB565 bits;
public:
	const UINT8 GetRed()	const { return (bits & 0xF800) >> 11; }
	const UINT8 GetRed8()	const { return (GetRed() * 255 + 15) / 31; }
	const UINT8 GetGreen()	const { return (bits & 0x7E0) >> 5; }
	const UINT8 GetGreen8() const { return (GetGreen() * 255 + 31) / 63; }
	const UINT8 GetBlue()	const { return bits & 0x1F; }
	const UINT8 GetBlue8()	const { return (GetBlue() * 255 + 15) / 31; }
	const DWORD GetRGB888() const { return (GetRed8() << 16 | GetGreen8() << 8 | GetBlue8()); }
	const RGB565 GetBits()	const { return bits; }

	H3RGB565() {}
	H3RGB565(UINT8 r, UINT8 g, UINT8 b) { PackRGB565(r, g, b); }
	H3RGB565(DWORD color) { PackRGB565((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF); }
	H3RGB565(H3RGB888 color) { PackRGB565(color.r, color.g, color.b); }

	VOID SetBits(WORD color) { bits = color; }
	static WORD Pack(UINT8 r, UINT8 g, UINT8 b) { return ((r / 8) & 0x1F) << 11 | ((g / 4) & 0x3F) << 5 | ((b / 8) & 0x1F);	}
	static DWORD Unpack(RGB565 rgb) { return (((((rgb & 0xF800) >> 11) * 255 + 15) / 31) << 16) + (((((rgb & 0x7E0) >> 5) * 255 + 31) / 63) << 8) + (((rgb & 0x1F) * 255 + 15) / 31); }
	WORD PackRGB565(UINT8 r, UINT8 g, UINT8 b) { return bits = Pack(r, g, b); }

	// darkens pixel's color by ~50%
	VOID Darken50()
	{
		UINT8 r = GetRed8();
		UINT8 g = GetGreen8();
		UINT8 b = GetBlue8();
		PackRGB565(r / 2, g / 2, b / 2);
	}
	// darkens pixel's color by ~20% if one color is prominent
	VOID Darken20()
	{
		UINT8 r = GetRed8();
		UINT8 g = GetGreen8();
		UINT8 b = GetBlue8();
		r -= r / 5;
		g -= g / 5;
		b -= b / 5;
		PackRGB565(r,g ,b);
	}
	VOID Lighten20()
	{
		INT r = GetRed8();
		INT g = GetGreen8();
		INT b = GetBlue8();
		r = min(r + r / 5, 0xFF);
		g = min(g + g / 5, 0xFF);
		b = min(b + b / 5, 0xFF);
		PackRGB565(r, g, b);
	}
	VOID Lighten50()
	{
		INT r = GetRed8();
		INT g = GetGreen8();
		INT b = GetBlue8();
		r = min(r + r / 2, 0xFF);
		g = min(g + g / 2, 0xFF);
		b = min(b + b / 2, 0xFF);
		PackRGB565(r, g, b);
	}
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

	static H3LoadedPCX* Load(LPCSTR name) { return THISCALL_1(H3LoadedPCX*, 0x55AA10, name); }
	static H3LoadedPCX* Create(LPCSTR name, INT width, INT height);

	// * returns row start in buffer
	PUINT8 GetRow(int row) { return buffer + row * scanlineSize; }
	// * returns the color index of pixel (x, y) starting from top left
	PUINT8 GetPixelIndex(int x, int y) { return GetRow(y) + x; }
	// * fills rectangle with color index from palette565
	VOID FillRectangle(INT x, INT y, INT dx, INT dy, BYTE color_index);
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

	VOID DarkenArea20(INT x, INT y, INT w, INT h);
	VOID DarkenArea50(INT x, INT y, INT w, INT h);
	VOID LightenArea20(INT x, INT y, INT w, INT h);
	VOID LightenArea50(INT x, INT y, INT w, INT h);

	// * based on HSV color model, not RGB
	// * hue is on the scale 0~1 and represents the color scheme
	// * saturation is also scaled between 0 ~ 1 and represents
	// * value is fixed
	VOID DrawHue(INT x, INT y, INT w, INT h, FLOAT hue, FLOAT saturation) { THISCALL_7(VOID, 0x44E610, this, x, y, w, h, hue, saturation); }

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

	// * returns row start in buffer
	PUINT8 GetRow(int row) { return buffer + row * sizeof(H3RGB888) * width; }
	// * returns rgb888 pixel at coordinates (x, y) in buffer
	H3RGB888* GetPixel(int x, int y) { return (H3RGB888*)GetRow(y) + x; }
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
	int dest_weight = 255 - alpha;

	int weighted_r = alpha * red + dest_weight * r;
	r = weighted_r / 255;

	int weighted_g = alpha * green + dest_weight * g;
	g = weighted_g / 255;

	int weighted_b = alpha * blue + dest_weight * b;
	b = weighted_b / 255;
}

inline FLOAT H3RGB888::GetHueAsNormalizedFloat(UINT8 red, UINT8 green, UINT8 blue)
{
	int c_min = min(min(red, green), blue);
	int c_max = max(max(red, green), blue);
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
	H3LoadedPCX16 *pcx16 = (H3LoadedPCX16*)F_malloc(sizeof(H3LoadedPCX16));
	if (!pcx16)
		return nullptr;
	return pcx16->Construct(name, width, height);
}

inline VOID H3LoadedPCX16::FillRectangle(INT x, INT y, INT w, INT h, BYTE r, BYTE g, BYTE b)
{
	INT _w, _h;
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	_w = min(w, width - x);
	_h = min(h, height - y);

	if (ByteAt(0x5FA228 + 3) == 4) // RGB888 mode
	{
		H3ARGB888 color(r, g, b);
		H3ARGB888 *rgb_row = (H3ARGB888 *)GetRow(y);
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
		H3RGB565 *rgb_row = (H3RGB565 *)GetRow(y);
		rgb_row += x;
		H3RGB565 color(r, g, b);
		for (int j = 0; j < _h; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->SetBits(color.GetBits());

			rgb_row = (H3RGB565*)((PUINT8)rgb_row + scanlineSize);
		}
	}
}

inline VOID H3LoadedPCX16::DarkenArea20(INT x, INT y, INT w, INT h)
{
	INT _w, _h;
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	_w = min(w, width - x);
	_h = min(h, height - y);

	if (ByteAt(0x5FA228 + 3) == 4) // RGB888 mode
	{
		H3ARGB888 *rgb_row = (H3ARGB888 *)GetRow(y);
		rgb_row += x;
		for (int j = 0; j < _h; ++j)
		{
			H3ARGB888 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->Darken20();

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = (H3RGB565 *)GetRow(y);
		rgb_row += x;

		for (int j = 0; j < _h; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->Darken20();

			rgb_row = (H3RGB565*)((PUINT8)rgb_row + scanlineSize);
		}
	}
}

inline VOID H3LoadedPCX16::DarkenArea50(INT x, INT y, INT w, INT h)
{
	INT _w, _h;
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	_w = min(w, width - x);
	_h = min(h, height - y);

	if (ByteAt(0x5FA228 + 3) == 4) // RGB888 mode
	{
		H3ARGB888 *rgb_row = (H3ARGB888 *)GetRow(y);
		rgb_row += x;
		for (int j = 0; j < _h; ++j)
		{
			H3ARGB888 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
			{
				rgb->Darken50();
			}

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = (H3RGB565 *)GetRow(y);
		rgb_row += x;

		for (int j = 0; j < _h; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->Darken50();

			rgb_row = (H3RGB565*)((PUINT8)rgb_row + scanlineSize);
		}
	}
}

inline VOID H3LoadedPCX16::LightenArea20(INT x, INT y, INT w, INT h)
{
	INT _w, _h;
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	_w = min(w, width - x);
	_h = min(h, height - y);

	if (ByteAt(0x5FA228 + 3) == 4) // RGB888 mode
	{
		H3ARGB888 *rgb_row = (H3ARGB888 *)GetRow(y);
		rgb_row += x;
		for (int j = 0; j < _h; ++j)
		{
			H3ARGB888 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
			{
				rgb->Lighten20();
			}

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = (H3RGB565 *)GetRow(y);
		rgb_row += x;

		for (int j = 0; j < _h; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->Lighten20();

			rgb_row = (H3RGB565*)((PUINT8)rgb_row + scanlineSize);
		}
	}
}

inline VOID H3LoadedPCX16::LightenArea50(INT x, INT y, INT w, INT h)
{
	INT _w, _h;
	if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
		return;
	_w = min(w, width - x);
	_h = min(h, height - y);

	if (ByteAt(0x5FA228 + 3) == 4) // RGB888 mode
	{
		H3ARGB888 *rgb_row = (H3ARGB888 *)GetRow(y);
		rgb_row += x;
		for (int j = 0; j < _h; ++j)
		{
			H3ARGB888 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
			{
				rgb->Lighten50();
			}

			rgb_row += width;
		}
	}
	else // RGB565 mode
	{
		H3RGB565 *rgb_row = (H3RGB565 *)GetRow(y);
		rgb_row += x;

		for (int j = 0; j < _h; ++j)
		{
			H3RGB565 *rgb = rgb_row;

			for (int i = 0; i < _w; ++i, ++rgb)
				rgb->Lighten50();

			rgb_row = (H3RGB565*)((PUINT8)rgb_row + scanlineSize);
		}
	}
}

inline VOID H3LoadedDEF::AddFrameFromDef(LPCSTR source, INT32 index)
{
	H3LoadedDEF *src = H3LoadedDEF::Load(source);
	if (!src)
		return;
	H3DefFrame *frm = src->groups[0]->frames[0];
	H3DefGroup *grp = groups[0];

	H3DefFrame *frame = (H3DefFrame *)F_malloc(sizeof(H3DefFrame));
	if (frame)
	{
		F_memcpy(frame, frm, sizeof(H3DefFrame)); // copy frame data
		frame->rawData = (PUINT8)F_malloc(frame->rawDataSize); // new data buffer
		F_memcpy(frame->rawData, frm->rawData, frame->rawDataSize); // copy data buffer

		int nFrames = grp->count;

		if (nFrames < index + 1) // add room for frame
		{
			H3DefFrame ** newList = (H3DefFrame**)F_realloc(grp->frames, (index + 1) * 4);
			if (newList)
			{
				newList[index] = frame;
				grp->count = index + 1;
				grp->spritesSize = index + 1;
				grp->frames = newList;
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

inline H3LoadedPCX * H3LoadedPCX::Create(LPCSTR name, INT width, INT height)
{
	H3LoadedPCX *pcx = (H3LoadedPCX*)F_malloc(sizeof(H3LoadedPCX));
	if (!pcx)
		return nullptr;

	pcx->InitiateBinary(name, 16); // see 0x44F5CC
	pcx->vTable = (BinaryVTable*)0x63BA14;
	pcx->width = width;
	pcx->height = height;
	// round up to nearest 4
	pcx->scanlineSize = ((width + 3) >> 2) << 2;
	pcx->bufSize = height * pcx->scanlineSize;
	pcx->bufSizeUnk = pcx->bufSize;
	pcx->buffer = (PUINT8)F_malloc(pcx->bufSize);
	if (!pcx->buffer)
	{
		F_delete(pcx);
		return nullptr;
	}
	pcx->palette565.Initiate();
	pcx->palette888.Initiate();

	return pcx;
}

inline VOID H3LoadedPCX::FillRectangle(INT x, INT y, INT dx, INT dy, BYTE color_index)
{
	INT _x, _y, _dx, _dy;
	_x = max(x, 0);
	_y = max(y, 0);
	_dx = max(dx, 0);
	_dy = max(dy, 0);
	_dx = min(width - _x, _dx);
	_dy = min(width - _y, _dy);

	PUINT8 start = GetPixelIndex(_x, _y);

	for (int j = 0; j < _dy; ++j)
	{
		PUINT8 pixel = start;
		for (int i = 0; i < _dx; ++i, ++pixel)
		{
			*pixel = color_index;
		}
		start += scanlineSize;
	}
}

#endif /* #define _H3BINARYITEMS_H_ */