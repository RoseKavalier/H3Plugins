//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2019-12-06                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BINARYITEMS_HPP_
#define _H3BINARYITEMS_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_Vector.hpp"
#include "../H3_Constants.hpp"

namespace h3
{
	// * forward declarations

	struct H3ARGB888;
	typedef UINT16 RGB555;
	typedef UINT16 RGB565;
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

	struct H3RGB888
	{
		UINT8 r;
		UINT8 g;
		UINT8 b;

		// * approximate darkening, but faster than hsv
		VOID Darken20();
		// * approximate darkening, but faster than hsv
		VOID Darken50();
		VOID GrayScale();
		// * darkens pixel's color through HSV by amount
		VOID Darken(const UINT8 amount);
		// * lightens pixel's color through HSV by amount
		VOID Lighten(const UINT8 amount);
		// * this assumes the source pixel has full alpha visibility
		VOID AlphaDraw(UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha);
		static FLOAT GetHueAsNormalizedFloat(UINT8 red, UINT8 green, UINT8 blue);
		static DWORD Pack(UINT8 red, UINT8 green, UINT8 blue);
		_H3API_ H3RGB888();
		_H3API_ H3RGB888(DWORD color);
		_H3API_ H3RGB888(UINT8 r, UINT8 g, UINT8 b);
		_H3API_ H3RGB888(H3RGB565& rgb);
		_H3API_ H3RGB888(H3ARGB888& rgb);
	};

	// * argb pixel in HD mod
	struct H3ARGB888
	{
		// * legacy order pre - HDmod 5.0RC63
		//UINT8 a; // alpha - unused in H3
		//UINT8 g;
		//UINT8 r;
		//UINT8 b;

		UINT8 g;
		UINT8 b;
		UINT8 r;
		UINT8 a;

		UINT Value() const;
		_H3API_ operator DWORD () const;
		// * darkens pixel's color through HSV by amount
		VOID Darken(const UINT8 amount);
		// * lightens pixel's color through HSV by amount
		VOID Lighten(const UINT8 amount);
		VOID GrayScale();
		// * reorders pixels based on legacy drawing, pre - HDmod 5.0RC63
		VOID Legacy();
		_H3API_ H3ARGB888(UINT8 red, UINT8 blue, UINT8 green);
	};

	struct H3RGB555 // https://docs.microsoft.com/en-us/windows/desktop/DirectShow/working-with-16-bit-rgb
	{
	protected:
		RGB555 bits;
	public:
		UINT8 GetRed();
		UINT8 GetGreen();
		UINT8 GetBlue();
		DWORD UnPack();
		VOID SetBits(WORD color);
		static WORD Pack(UINT8 r, UINT8 g, UINT8 b);
		static DWORD Unpack(RGB555 rgb);
		VOID PackRGB(UINT8 r, UINT8 g, UINT8 b);
	};

	struct H3RGB565 // https://docs.microsoft.com/en-us/windows/desktop/DirectShow/working-with-16-bit-rgb
	{
	protected:
		RGB565 bits;
	public:
		UINT8 GetRed();
		UINT8 GetRed8();
		UINT8 GetGreen();
		UINT8 GetGreen8();
		UINT8 GetBlue();
		UINT8 GetBlue8();
		DWORD GetRGB888();
		RGB565 GetBits();
		_H3API_ H3RGB565();
		_H3API_ H3RGB565(UINT8 r, UINT8 g, UINT8 b);
		_H3API_ H3RGB565(DWORD color);
		_H3API_ H3RGB565(H3RGB888 color);
		_H3API_ operator WORD () const;
		WORD Value() const;
		VOID SetBits(WORD color);
		WORD PackRGB565(UINT8 r, UINT8 g, UINT8 b);
		WORD Pack(H3RGB888& rgb);
		static WORD Pack(UINT8 r, UINT8 g, UINT8 b);
		static DWORD Unpack(RGB565 rgb);
		// darkens pixel's color by amount
		VOID Darken(UINT8 amount);
		VOID Lighten(UINT8 amount);
		VOID GrayScale();
	};

	struct H3HSV
	{
	protected:
		UINT8 h;
		UINT8 s;
		UINT8 v;
	public:
		_H3API_ H3HSV();
		_H3API_ H3HSV(H3HSV& other);
		_H3API_ H3HSV(const H3RGB888& rgb);
		// * based on https://stackoverflow.com/a/14733008
		H3HSV& ConvertFromRgb888(const H3RGB888& rgb);
		H3RGB888 ConvertToRgb888() const;
		VOID AddSaturation(UINT8 saturation);
		VOID RemoveSaturation(UINT8 saturation);
		VOID SetHue(UINT8 hue);
		VOID AddValue(UINT8 value);
		VOID RemoveValue(UINT8 value);
	};

	// * a binary tree to hold game assets
	struct H3BinTreeList
	{
		h3unk _f0[4];
		// * +4
		H3BinaryTreeNode* root;
		h3unk _f8[4];
		INT32 number_nodes;

		H3BinaryTreeNode* FindItem(LPCSTR name);
		VOID AddItem(H3BinaryItem* item);
		VOID RemoveItem(H3BinaryTreeNode* node);
		VOID RemoveItem(LPCSTR name);
	};

	struct H3BinaryTreeNode // size 36
	{
		// * +0
		H3BinaryTreeNode* leftNode;
		// * +4
		H3BinaryTreeNode* parent;
		// * +8
		H3BinaryTreeNode* rightNode;
		// * +C
		struct BinaryItemData
		{
			// * +C
			CHAR name[12];
			// * +18
			UINT name_end; // always 0
			// * +1C
			H3BinaryItem* item;
		}data;
		// * +20
		BOOL isBlackNode; // https://en.wikipedia.org/wiki/Red–black_tree

		H3BinaryItem* GetBinaryItem() const;
		_H3API_ H3BinaryItem* operator->();
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
		H3BinaryItem* InitiateBinary(LPCSTR name, INT type);
		VOID Dereference();
		VOID AddToBinaryTree(H3BinTreeList* tree = reinterpret_cast<H3BinTreeList*>(0x69E560));
		VOID IncreaseReferences();
		LPCSTR GetName() const;
		_H3API_ ~H3BinaryItem();
	};
		
	// * from breakpoint at constructor, the following items are all H3BinaryTreeNode subclasses
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
		// * using the index from TxtEdit
		LPCSTR GetText(INT32 row) const;
		static H3ColumnTextFile* Load(LPCSTR name);
		VOID UnLoad();
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
		H3Vector<H3Vector<LPCSTR>*>& GetText();
		INT32 CountRows() const;
		static H3TextFile* Load(LPCSTR name);
		VOID UnLoad();
	};	

	struct H3Palette565 : public H3BinaryItem
	{
		// * +1C
		H3RGB565 color[256];

		VOID ColorToPlayer(INT id);
		VOID RotateColors(INT min_index, INT max_index, INT count = -1);
		H3Palette565* Initiate();
		// * as of HDmod 5.0 RC 63, Palette565 now contains a buffer o ARGB888 colors[256] located at &color[254]
		// * http://heroescommunity.com/viewthread.php3?TID=44581&PID=1503736#focus
		H3ARGB888* Get32bitColors();
		VOID CopyPalette(H3Palette565& source);
	};

	struct H3Palette888 : public H3BinaryItem
	{
		// * +1C
		H3RGB888 color[256];

		VOID ColorToPlayer(INT id);
		H3Palette888* Initiate();
	};

	struct H3Font : public H3BinaryItem
	{
		h3unk _f_1C[5];
		// * +21
		INT8 height;
		h3unk _f_22[26];
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

		INT32 GetLinesCountInText(LPCSTR str, INT32 width);
		INT32 GetMaxLineWidth(LPCSTR str);
		INT32 GetMaxWordWidth(LPCSTR str);
		
		VOID TextDraw(H3LoadedPCX16* pcx, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, 
			NH3Dlg::TextColor::eTextColor colorIndex = NH3Dlg::TextColor::REGULAR,
			NH3Dlg::TextAlignment::eTextAlignment alignment = NH3Dlg::TextAlignment::MiddleCenter);
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

		VOID DrawToPcx16(int srcX, int srcY, int dx, int dy, H3LoadedPCX16* dest, int destX, int destY, BOOL skip_transparent_colors);
		VOID DrawToPcx(int src_x, int src_y, int dx, int dy, H3LoadedPCX* pcx_dest, int dest_x = 0, int dest_y = 0, BOOL copy_palette = TRUE);
		static H3LoadedPCX* Load(LPCSTR name);
		static H3LoadedPCX* Create(LPCSTR name, INT width, INT height);
		// * returns row start in buffer
		PUINT8 GetRow(int row);
		// * returns the color index of pixel (x, y) starting from top left
		PUINT8 GetPixelIndex(int x, int y);
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
		h3align _f_35[3];

		H3LoadedPCX16* Construct(LPCSTR name, INT width, INT height);
		VOID DrawToPcx16(INT x, INT y, BOOL transparent, H3LoadedPCX16* dest, INT srcX = 0, INT srcY = 0);
		static H3LoadedPCX16* Load(LPCSTR name);
		static H3LoadedPCX16* Create(LPCSTR name, INT width, INT height);
		VOID Destroy(BOOL destroy_buffer = TRUE);
		// * darkens RGB by about 50%
		VOID DrawShadow(INT x, INT y, INT dw, INT dh);
		VOID FillRectangle(INT x, INT y, INT w, INT h, BYTE r, BYTE g, BYTE b);
		VOID FillRectangle(INT x, INT y, INT w, INT h, DWORD color);
		VOID DrawFrame(INT x, INT y, INT w, INT h, BYTE r = 232, BYTE g = 212, BYTE b = 120);
		VOID DarkenArea(INT x, INT y, INT w, INT h, UINT8 amount);
		VOID LightenArea(INT x, INT y, INT w, INT h, UINT8 amount);
		VOID GrayScaleArea(INT x, INT y, INT w, INT h);
		// * based on HSV color model, not RGB
		// * hue is on the scale 0~1 and represents the color scheme
		// * saturation is also scaled between 0 ~ 1 and represents
		// * value is fixed
		VOID DrawHue(INT x, INT y, INT w, INT h, FLOAT hue, FLOAT saturation);
		BOOL BackgroundRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL is_blue);
		BOOL SimpleFrameRegion(INT32 x, INT32 y, INT32 _width, INT32 _height);
		BOOL FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue);
		// * adds a 1 pixel border around the designated area to make it look
		// * as if the contents were lowered
		VOID SinkArea(INT32 x, INT32 y, INT32 w, INT32 h);
		// * adds a 1 pixel border around the designated area to make it look
		// * as if the contents were elevated
		VOID BevelArea(INT32 x, INT32 y, INT32 w, INT32 h);
		// * Draws text on the pcx
		VOID TextDraw(H3Font* font, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, 
			NH3Dlg::TextColor::eTextColor colorIndex = NH3Dlg::TextColor::REGULAR,
			NH3Dlg::TextAlignment::eTextAlignment alignment = NH3Dlg::TextAlignment::MiddleCenter);
	protected:
		// * returns row start in buffer
		PUINT8 GetRow(int row);
		// * returns rgb565 pixel at coordinates (x,y) in buffer
		// * !WARNING! This is only valid when h3_BitMode == 2 aka default
		H3RGB565* GetPixel565(int x, int y);
		// * returns rgb565 pixel at coordinates (x,y) in buffer
		// * !WARNING! This is only valid when h3_BitMode == 4 aka TRUE mode with HDmod
		H3ARGB888* GetPixel888(int x, int y);
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
		H3LoadedPCX24* Construct(LPCSTR name, INT width, INT height, PUINT8 data, UINT32 dataSize);
		// * converts RGB888 to RGB565
		// * if True mode, copies to ARGB888
		VOID DrawToPcx16(INT dst_x, INT dst_y, H3LoadedPCX16* dest, INT srcX = 0, INT srcY = 0);
		static H3LoadedPCX24* Load(LPCSTR name, INT width, INT height);
		// * returns row start in buffer
		PUINT8 GetRow(int row);
		// * returns rgb888 pixel at coordinates (x, y) in buffer
		H3RGB888* GetPixel(int x, int y);
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

		VOID DrawToPcx16(INT src_x, INT src_y, INT src_width, INT src_height, H3LoadedPCX16* pcx16, INT dst_x, INT dst_y,
			H3Palette565* palette565, BOOL mirror = FALSE, BOOL do_not_use_special_colors = TRUE);
	};

	// * Not a binary item but relevant to H3LoadedDEF and H3DefFrame
	struct H3DefGroup
	{
		// * +0
		int count;
		// * +4
		int spritesSize;
		// * +8
		H3DefFrame** frames;
	};

	struct H3LoadedDEF : public H3BinaryItem
	{
		// * +1C
		H3DefGroup** groups;
		// * +20
		H3Palette565* palette565;
		// * +24
		H3Palette888* palette888;
		// * +28
		INT32 groupsCount;
		// * +2C
		INT32* activeGroups;
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

		static H3LoadedDEF* Load(LPCSTR name);
		VOID AddFrameFromDef(LPCSTR source, INT32 index);
		VOID ColorToPlayer(INT32 id);
		H3DefFrame* GetGroupFrame(INT group, INT frame);
		VOID DrawTransparent(INT32 frame, H3LoadedPCX16* pcx, INT32 x, INT32 y, BOOL transparent = TRUE, 
			BOOL mirror = FALSE, INT32 group = 0, INT32 xFromRight = 0, INT32 yFromBottom = 0);
		VOID DrawToPcx16(INT group, INT frame, INT src_x, INT src_y, INT src_width, INT src_height, 
			H3LoadedPCX16* pcx16, INT dst_x, INT dst_y, BOOL mirror = FALSE, BOOL do_not_use_special_colors = TRUE);
	};	
#pragma pack(pop)

	// * a raii loader for binary items
	template <typename T>
	class BinaryLoader
	{
	protected:
		T* m_binary;
	public:
		inline BinaryLoader();
		inline BinaryLoader(T* binary_item);
		inline ~BinaryLoader();
		void Set(T* binary);
		T* Get();
		T* operator->();
	};

	class DefLoader : public BinaryLoader<H3LoadedDEF>
	{
	public:
		inline DefLoader(LPCSTR name);
	};

	class PcxLoader : public BinaryLoader<H3LoadedPCX>
	{
	public:
		inline PcxLoader(LPCSTR name);
	};
}

#endif /* #define _H3BINARYITEMS_HPP_ */