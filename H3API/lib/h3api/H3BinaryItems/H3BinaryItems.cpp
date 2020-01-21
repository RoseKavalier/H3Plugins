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

#include "H3BinaryItems.hpp"
#include "H3BinaryItems.inl"

namespace h3
{
	_H3API_ VOID H3RGB888::Darken20()
	{
		r = ((r & 0xFE) >> 1) | (r & 0x80);
		g = ((r & 0xFE) >> 1) | (r & 0x80);
		b = ((r & 0xFE) >> 1) | (r & 0x80);
	}
	_H3API_ VOID H3RGB888::Darken50()
	{
		r = ((r & 0xFE) >> 1);
		g = ((r & 0xFE) >> 1);
		b = ((r & 0xFE) >> 1);
	}
	_H3API_ VOID H3RGB888::GrayScale()
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
	_H3API_ VOID H3RGB888::Darken(const UINT8 amount)
	{
		H3HSV hsv(*this);
		hsv.RemoveValue(amount);
		*this = hsv.ConvertToRgb888();
	}
	_H3API_ VOID H3RGB888::Lighten(const UINT8 amount)
	{
		H3HSV hsv(*this);
		hsv.AddValue(amount);
		*this = hsv.ConvertToRgb888();
	}
	_H3API_ VOID H3RGB888::AlphaDraw(UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha)
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
	_H3API_ FLOAT H3RGB888::GetHueAsNormalizedFloat(UINT8 red, UINT8 green, UINT8 blue)
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
	_H3API_ DWORD H3RGB888::Pack(UINT8 red, UINT8 green, UINT8 blue)
	{
		return 0xFF000000 + blue + (green << 8) + (red << 16);
	}
	_H3API_ H3RGB888::H3RGB888() :
		b(),
		g(),
		r()
	{
	}
	_H3API_ H3RGB888::H3RGB888(DWORD color) :
		b(color & 0xFF),
		g((color >> 8) & 0xFF),
		r((color >> 16) & 0xFF)
	{
	}
	_H3API_ H3RGB888::H3RGB888(UINT8 r, UINT8 g, UINT8 b) :
		b(b),
		g(g),
		r(r)
	{
	}
	_H3API_ H3RGB888::H3RGB888(H3RGB565& rgb) :
		r(rgb.GetRed8()), 
		g(rgb.GetGreen8()), 
		b(rgb.GetBlue8())
	{
	}
	_H3API_ H3RGB888::H3RGB888(H3ARGB888& rgb) :
		r(rgb.r), 
		g(rgb.g), 
		b(rgb.b)
	{
	}
	_H3API_ UINT H3ARGB888::Value() const
	{
		return DwordAt(this);
	}
	_H3API_ H3ARGB888::operator DWORD() const
	{
		return Value();
	}
	_H3API_ VOID H3ARGB888::Darken(const UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Darken(amount);
		r = rgb.r;
		g = rgb.g;
		b = rgb.b;
	}
	_H3API_ VOID H3ARGB888::Lighten(const UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Lighten(amount);
		r = rgb.r;
		g = rgb.g;
		b = rgb.b;
	}
	_H3API_ VOID H3ARGB888::GrayScale()
	{
		H3RGB888 rgb(*this);
		rgb.GrayScale();
		r = rgb.r;
		g = rgb.g;
		b = rgb.b;
	}
	_H3API_ VOID H3ARGB888::Legacy()
	{
		const UINT8 tmp = a;
		a = b;
		b = g;
		g = tmp;
	}
	_H3API_ H3ARGB888::H3ARGB888(UINT8 red, UINT8 blue, UINT8 green) :
		g(green), 
		b(blue), 
		r(red), 
		a(0xFF)
	{
	}
	_H3API_ UINT8 H3RGB555::GetRed()
	{
		return (bits & 0x7C00) >> 10;
	}
	_H3API_ UINT8 H3RGB555::GetGreen()
	{
		return (bits & 0x3E0) >> 5;
	}
	_H3API_ UINT8 H3RGB555::GetBlue()
	{
		return bits & 0x1F;
	}
	_H3API_ DWORD H3RGB555::UnPack()
	{
		return GetRed() << 16 | GetGreen() << 8 | GetBlue();
	}
	_H3API_ VOID H3RGB555::SetBits(WORD color)
	{
		bits = color;
	}
	_H3API_ WORD H3RGB555::Pack(UINT8 r, UINT8 g, UINT8 b)
	{
		return ((r / 8) & 0x1F) << 10 | ((g / 8) & 0x1F) << 5 | ((b / 8) & 0x1F);
	}
	_H3API_ DWORD H3RGB555::Unpack(RGB555 rgb)
	{
		return (((((rgb & 0x7C00) >> 10) * 255 + 15) / 31) << 16) + (((((rgb & 0x3E0) >> 5) * 255 + 31) / 63) << 8) + (((rgb & 0x1F) * 255 + 15) / 31);
	}
	_H3API_ VOID H3RGB555::PackRGB(UINT8 r, UINT8 g, UINT8 b)
	{
		bits = Pack(r, g, b);
	}
	_H3API_ UINT8 H3RGB565::GetRed()
	{
		return (bits & 0xF800) >> 11;
	}
	_H3API_ UINT8 H3RGB565::GetRed8()
	{
		return (GetRed() * 255 + 15) / 31;
	}
	_H3API_ UINT8 H3RGB565::GetGreen()
	{
		return (bits & 0x7E0) >> 5;
	}
	_H3API_ UINT8 H3RGB565::GetGreen8()
	{
		return (GetGreen() * 255 + 31) / 63;
	}
	_H3API_ UINT8 H3RGB565::GetBlue()
	{
		return bits & 0x1F;
	}
	_H3API_ UINT8 H3RGB565::GetBlue8()
	{
		return (GetBlue() * 255 + 15) / 31;
	}
	_H3API_ DWORD H3RGB565::GetRGB888()
	{
		return (GetRed8() << 16 | GetGreen8() << 8 | GetBlue8());
	}
	_H3API_ RGB565 H3RGB565::GetBits()
	{
		return bits;
	}
	_H3API_ H3RGB565::H3RGB565() :
		bits()
	{
	}
	_H3API_ H3RGB565::H3RGB565(UINT8 r, UINT8 g, UINT8 b) :
		bits(Pack(r,g,b))
	{
	}
	_H3API_ H3RGB565::H3RGB565(DWORD color)
	{
		PackRGB565((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	}
	_H3API_ H3RGB565::H3RGB565(H3RGB888 color)
	{
		PackRGB565(color.r, color.g, color.b);
	}
	_H3API_ H3RGB565::operator WORD() const
	{
		return Value();
	}
	_H3API_ WORD H3RGB565::Value() const
	{
		return bits;
	}
	_H3API_ VOID H3RGB565::SetBits(WORD color)
	{
		bits = color;
	}
	_H3API_ WORD H3RGB565::PackRGB565(UINT8 r, UINT8 g, UINT8 b)
	{
		return bits = Pack(r, g, b);
	}
	_H3API_ WORD H3RGB565::Pack(H3RGB888& rgb)
	{
		return bits = Pack(rgb.r, rgb.g, rgb.b);
	}
	_H3API_ WORD H3RGB565::Pack(UINT8 r, UINT8 g, UINT8 b)
	{
		return ((r / 8) & 0x1F) << 11 | ((g / 4) & 0x3F) << 5 | ((b / 8) & 0x1F);
	}
	_H3API_ DWORD H3RGB565::Unpack(RGB565 rgb)
	{
		return (((((rgb & 0xF800) >> 11) * 255 + 15) / 31) << 16) + (((((rgb & 0x7E0) >> 5) * 255 + 31) / 63) << 8) + (((rgb & 0x1F) * 255 + 15) / 31);
	}
	_H3API_ VOID H3RGB565::Darken(UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Darken(amount);
		Pack(rgb);
	}
	_H3API_ VOID H3RGB565::Lighten(UINT8 amount)
	{
		H3RGB888 rgb(*this);
		rgb.Lighten(amount);
		Pack(rgb);
	}
	_H3API_ VOID H3RGB565::GrayScale()
	{
		H3RGB888 rgb(*this);
		rgb.GrayScale();
		Pack(rgb);
	}
	_H3API_ H3HSV::H3HSV() : 
		h(), 
		s(), 
		v()
	{
	}
	_H3API_ H3HSV::H3HSV(H3HSV& other) : 
		h(other.h), 
		s(other.s), 
		v(other.v)
	{
	}
	_H3API_ H3HSV::H3HSV(const H3RGB888& rgb)
	{
		ConvertFromRgb888(rgb);
	}
	_H3API_ H3HSV& H3HSV::ConvertFromRgb888(const H3RGB888& rgb)
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
	_H3API_ H3RGB888 H3HSV::ConvertToRgb888() const
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
	_H3API_ VOID H3HSV::AddSaturation(UINT8 saturation)
	{
		s = std::min(255, s + saturation);
	}
	_H3API_ VOID H3HSV::RemoveSaturation(UINT8 saturation)
	{
		s = std::max(0, s - saturation);
	}
	_H3API_ VOID H3HSV::SetHue(UINT8 hue)
	{
		h = hue;
	}
	_H3API_ VOID H3HSV::AddValue(UINT8 value)
	{
		v = std::min(255, v + value);
	}
	_H3API_ VOID H3HSV::RemoveValue(UINT8 value)
	{
		v = std::max(0, v - value);
	}
	_H3API_ H3BinaryTreeNode* H3BinTreeList::FindItem(LPCSTR name)
	{
		H3BinaryTreeNode* node = THISCALL_2(H3BinaryTreeNode*, 0x55EE00, this, name);
		if (node == root)
			return nullptr;
		if (F_strcmpi(node->data.name, name))
			return nullptr;
		return node;
	}
	_H3API_ VOID H3BinTreeList::AddItem(H3BinaryItem* item)
	{
		return item->AddToBinaryTree(this);
	}
	_H3API_ VOID H3BinTreeList::RemoveItem(H3BinaryTreeNode* node)
	{
		H3BinaryTreeNode* temp;
		THISCALL_3(VOID, 0x55DF20, this, &temp, node);
	}
	_H3API_ VOID H3BinTreeList::RemoveItem(LPCSTR name)
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
	_H3API_ H3BinaryItem* H3BinaryTreeNode::GetBinaryItem() const
	{
		return data.item;
	}
	_H3API_ H3BinaryItem* H3BinaryTreeNode::operator->()
	{
		return data.item;
	}
	
	_H3API_ H3BinaryItem* H3BinaryItem::InitiateBinary(LPCSTR name, INT type)
	{
		return THISCALL_3(H3BinaryItem*, 0x558970, this, name, type);
	}
	_H3API_ VOID H3BinaryItem::Dereference()
	{
		THISCALL_1(VOID, vTable->dereference, this);
	}
	_H3API_ VOID H3BinaryItem::AddToBinaryTree(H3BinTreeList* tree)
	{
		H3BinaryTreeNode::BinaryItemData base;
		for (int i = 0; i < sizeof(base.name); ++i)
			base.name[i] = name[i];
		base.name_end = 0;
		base.item = this;
		struct returnValues
		{
			H3BinaryTreeNode* node;
			INT refCount;
		}retValues;

		THISCALL_3(returnValues*, 0x55DDF0, tree, &retValues, &base);
	}
	_H3API_ VOID H3BinaryItem::IncreaseReferences()
	{
		++ref;
	}
	_H3API_ LPCSTR H3BinaryItem::GetName() const
	{
		return name;
	}
	_H3API_ H3BinaryItem::~H3BinaryItem()
	{		
		Dereference();
	}
	_H3API_ LPCSTR H3ColumnTextFile::GetText(INT32 row) const
	{
		return text[row - 1];
	}
	_H3API_ H3ColumnTextFile* H3ColumnTextFile::Load(LPCSTR name)
	{
		return THISCALL_1(H3ColumnTextFile*, 0x55BDA0, name);
	}
	_H3API_ VOID H3ColumnTextFile::UnLoad()
	{
		THISCALL_1(VOID, vTable->dereference, this);
	}
	_H3API_ H3Vector<H3Vector<LPCSTR>*>& H3TextFile::GetText()
	{
		return text;
	}
	_H3API_ INT32 H3TextFile::CountRows() const
	{
		return text.Count();
	}
	_H3API_ H3WavFile* H3WavFile::Load(LPCSTR name)
	{
		return THISCALL_1(H3WavFile*, 0x55C930, name);
	}
	_H3API_ H3WavFile::H3WavFile(LPCSTR name) :
		_f_1C(0),
		buffer(),
		bufferSize(),
		lockSemaphore(HANDLE(0)),
		spinCount(127),
		debugInfo(PRTL_CRITICAL_SECTION_DEBUG(RTL_RESOURCE_TYPE))
	{
		InitiateBinary(name, 32);
		vTable = (BinaryVTable*)0x6416E0;		
	}
	_H3API_ H3WavFile::H3WavFile(LPCSTR name, PUINT8 buffer, DWORD bufferSize) :
		_f_1C(0),
		buffer(buffer),
		bufferSize(bufferSize),
		lockSemaphore(HANDLE(0)),
		spinCount(127),
		debugInfo(PRTL_CRITICAL_SECTION_DEBUG(RTL_RESOURCE_TYPE))		
	{
		InitiateBinary(name, 32);
		vTable = (BinaryVTable*)0x6416E0;
	}
	_H3API_ H3TextFile* H3TextFile::Load(LPCSTR name)
	{
		return THISCALL_1(H3TextFile*, 0x55C2B0, name);
	}
	_H3API_ VOID H3TextFile::UnLoad()
	{
		THISCALL_1(VOID, vTable->dereference, this);
	}
	_H3API_ VOID H3Palette565::ColorToPlayer(INT id)
	{
		FASTCALL_2(VOID, 0x6003E0, color, id);
	}
	_H3API_ VOID H3Palette565::RotateColors(INT min_index, INT max_index, INT count)
	{
		THISCALL_4(VOID, 0x522E40, this, min_index, max_index, count);
	}
	_H3API_ H3Palette565* H3Palette565::Initiate()
	{
		return THISCALL_1(H3Palette565*, 0x522B40, this);
	}
	_H3API_ H3ARGB888* H3Palette565::Get32bitColors()
	{
		if (type == 0x61)
			return reinterpret_cast<H3ARGB888*>(PtrAt(&color[254]));
		return nullptr;
	}
	_H3API_ VOID H3Palette565::CopyPalette(H3Palette565& source)
	{
		if (type == 0x61)
		{
			F_memcpy(color, source.color, sizeof(color) - 4);
			PDWORD dest = reinterpret_cast<PDWORD>(PtrAt(&color[254]));
			PDWORD src = reinterpret_cast<PDWORD>(PtrAt(&source.color[254]));
			F_memcpy(dest, src, 256 * sizeof(DWORD));
		}
		else
			F_memcpy(color, source.color, sizeof(color));
	}
	_H3API_ VOID H3Palette888::ColorToPlayer(INT id)
	{
		FASTCALL_2(VOID, 0x600400, this, id);
	}
	_H3API_ H3Palette888* H3Palette888::Initiate()
	{
		return THISCALL_1(H3Palette888*, 0x523320, this);
	}
	_H3API_ INT32 H3Font::GetLinesCountInText(LPCSTR str, INT32 width)
	{
		return THISCALL_3(INT32, 0x4B5580, this, str, width);
	}
	_H3API_ INT32 H3Font::GetMaxLineWidth(LPCSTR str)
	{
		return THISCALL_2(INT32, 0x4B56F0, this, str);
	}
	_H3API_ INT32 H3Font::GetMaxWordWidth(LPCSTR str)
	{
		return THISCALL_2(INT32, 0x4B5770, this, str);
	}
	_H3API_ VOID H3Font::TextDraw(H3LoadedPCX16* pcx, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, NH3Dlg::TextColor::eTextColor colorIndex, NH3Dlg::TextAlignment::eTextAlignment alignment)
	{
		pcx->TextDraw(this, text, x, y, width, height, colorIndex, alignment);
	}
	_H3API_ VOID H3LoadedPCX::DrawToPcx16(int srcX, int srcY, int dx, int dy, H3LoadedPCX16* dest, int destX, int destY, BOOL skip_transparent_colors)
	{
		THISCALL_9(VOID, 0x44FA80, this, srcX, srcY, dx, dy, dest, destX, destY, skip_transparent_colors);
	}
	_H3API_ VOID H3LoadedPCX::DrawToPcx(int src_x, int src_y, int dx, int dy, H3LoadedPCX* pcx_dest, int dest_x, int dest_y, BOOL copy_palette)
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
			pcx_dest->palette565.CopyPalette(palette565);
			F_memcpy(pcx_dest->palette888.color, palette888.color, sizeof(palette888.color));
		}
	}
	_H3API_ H3LoadedPCX* H3LoadedPCX::Load(LPCSTR name)
	{
		return THISCALL_1(H3LoadedPCX*, 0x55AA10, name);
	}
	_H3API_ H3LoadedPCX* H3LoadedPCX::Create(LPCSTR name, INT width, INT height)
	{
		H3LoadedPCX* pcx = reinterpret_cast<H3LoadedPCX*>(F_malloc(sizeof(H3LoadedPCX)));
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
	_H3API_ PUINT8 H3LoadedPCX::GetRow(int row)
	{
		return buffer + row * scanlineSize;
	}
	_H3API_ PUINT8 H3LoadedPCX::GetPixelIndex(int x, int y)
	{
		return GetRow(y) + x;
	}
	_H3API_ VOID H3LoadedPCX::FillRectangle(INT x, INT y, INT dx, INT dy, BYTE color_index)
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
	_H3API_ H3LoadedPCX::H3LoadedPCX(LPCSTR name) :
		bufSize(),
		bufSizeUnk(),
		width(),
		height(),
		scanlineSize(),
		buffer()
	{
		InitiateBinary(name, 16);
		palette565.Initiate();
		palette888.Initiate();
		vTable = (BinaryVTable*)0x63BA14;
	}
	_H3API_ H3LoadedPCX16* H3LoadedPCX16::Construct(LPCSTR name, INT width, INT height)
	{
		return THISCALL_4(H3LoadedPCX16*, 0x44DD20, this, name, width, height);
	}
	_H3API_ VOID H3LoadedPCX16::DrawToPcx16(INT x, INT y, BOOL transparent, H3LoadedPCX16* dest, INT srcX, INT srcY)
	{
		return THISCALL_12(VOID, 0x44DF80, this, srcX, srcY, width, height, dest->buffer, x, y, dest->width, dest->height, dest->scanlineSize, transparent);
	}
	_H3API_ H3LoadedPCX16* H3LoadedPCX16::Load(LPCSTR name)
	{
		return THISCALL_1(H3LoadedPCX16*, 0x55B1E0, name);
	}
	_H3API_ H3LoadedPCX16* H3LoadedPCX16::Create(LPCSTR name, INT width, INT height)
	{
		H3LoadedPCX16* pcx16 = reinterpret_cast<H3LoadedPCX16*>(F_malloc(sizeof(H3LoadedPCX16)));
		if (!pcx16)
			return nullptr;
		return pcx16->Construct(name, width, height);
	}
	_H3API_ VOID H3LoadedPCX16::Destroy(BOOL destroy_buffer)
	{
		THISCALL_2(VOID, 0x44DCF0, this, destroy_buffer);
	}
	_H3API_ VOID H3LoadedPCX16::DrawShadow(INT x, INT y, INT dw, INT dh)
	{
		THISCALL_5(VOID, 0x44E2C0, this, x, y, dw, dh);
	}
	_H3API_ VOID H3LoadedPCX16::FillRectangle(INT x, INT y, INT w, INT h, BYTE r, BYTE g, BYTE b)
	{
		if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
			return;
		INT _w = std::min(w, width - x);
		INT _h = std::min(h, height - y);

		if (H3Internal::_h3_BitMode() == 4) // RGB888 mode
		{
			H3ARGB888 color(r, g, b);
			H3ARGB888* rgb_row = reinterpret_cast<H3ARGB888*>(GetRow(y));
			rgb_row += x;
			for (int j = 0; j < _h; ++j)
			{
				H3ARGB888* rgb = rgb_row;

				for (int i = 0; i < _w; ++i, ++rgb)
					*rgb = color;

				rgb_row += width;
			}
		}
		else // RGB565 mode
		{
			H3RGB565* rgb_row = reinterpret_cast<H3RGB565*>(GetRow(y));
			rgb_row += x;
			H3RGB565 color(r, g, b);
			for (int j = 0; j < _h; ++j)
			{
				H3RGB565* rgb = rgb_row;

				for (int i = 0; i < _w; ++i, ++rgb)
					rgb->SetBits(color.GetBits());

				rgb_row = reinterpret_cast<H3RGB565*>(PUINT8(rgb_row) + scanlineSize);
			}
		}
	}
	_H3API_ VOID H3LoadedPCX16::FillRectangle(INT x, INT y, INT w, INT h, DWORD color)
	{
		FillRectangle(x, y, w, h, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	}
	_H3API_ VOID H3LoadedPCX16::DrawFrame(INT x, INT y, INT w, INT h, BYTE r, BYTE g, BYTE b)
	{
		FillRectangle(x, y, w, 1, r, g, b);
		FillRectangle(x, y + 1, 1, h - 2, r, g, b);
		FillRectangle(x + w - 1, y + 1, 1, h - 2, r, g, b);
		FillRectangle(x, y + h - 1, w, 1, r, g, b);
	}
	_H3API_ VOID H3LoadedPCX16::DarkenArea(INT x, INT y, INT w, INT h, UINT8 amount)
	{
		if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
			return;
		INT w_ = std::min(w, width - x);
		INT h_ = std::min(h, height - y);

		if (H3Internal::_h3_BitMode() == 4) // RGB888 mode
		{
			H3ARGB888* rgb_row = reinterpret_cast<H3ARGB888*>(GetRow(y));
			rgb_row += x;
			for (int j = 0; j < h_; ++j)
			{
				H3ARGB888* rgb = rgb_row;

				for (int i = 0; i < w_; ++i, ++rgb)
					rgb->Darken(amount);

				rgb_row += width;
			}
		}
		else // RGB565 mode
		{
			H3RGB565* rgb_row = reinterpret_cast<H3RGB565*>(GetRow(y));
			rgb_row += x;

			for (int j = 0; j < h_; ++j)
			{
				H3RGB565* rgb = rgb_row;

				for (int i = 0; i < w_; ++i, ++rgb)
					rgb->Darken(amount);

				rgb_row = reinterpret_cast<H3RGB565*>(PUINT8(rgb_row) + scanlineSize);
			}
		}
	}
	_H3API_ VOID H3LoadedPCX16::LightenArea(INT x, INT y, INT w, INT h, UINT8 amount)
	{
		if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
			return;
		INT w_ = std::min(w, width - x);
		INT h_ = std::min(h, height - y);

		if (H3Internal::_h3_BitMode() == 4) // RGB888 mode
		{
			H3ARGB888* rgb_row = reinterpret_cast<H3ARGB888*>(GetRow(y));
			rgb_row += x;
			for (int j = 0; j < h_; ++j)
			{
				H3ARGB888* rgb = rgb_row;

				for (int i = 0; i < w_; ++i, ++rgb)
					rgb->Lighten(amount);

				rgb_row += width;
			}
		}
		else // RGB565 mode
		{
			H3RGB565* rgb_row = reinterpret_cast<H3RGB565*>(GetRow(y));
			rgb_row += x;

			for (int j = 0; j < h_; ++j)
			{
				H3RGB565* rgb = rgb_row;

				for (int i = 0; i < w_; ++i, ++rgb)
					rgb->Lighten(amount);

				rgb_row = reinterpret_cast<H3RGB565*>(PUINT8(rgb_row) + scanlineSize);
			}
		}
	}
	_H3API_ VOID H3LoadedPCX16::GrayScaleArea(INT x, INT y, INT w, INT h)
	{
		if (x >= width || x < 0 || y >= height || y < 0 || !buffer)
			return;
		INT _w = std::min(w, width - x);
		INT _h = std::min(h, height - y);

		if (H3Internal::_h3_BitMode() == 4) // RGB888 mode
		{
			H3ARGB888* rgb_row = reinterpret_cast<H3ARGB888*>(GetRow(y));
			rgb_row += x;
			for (int j = 0; j < _h; ++j)
			{
				H3ARGB888* rgb = rgb_row;
				for (int i = 0; i < _w; ++i, ++rgb)
					rgb->GrayScale();

				rgb_row += width;
			}
		}
		else // RGB565 mode
		{
			H3RGB565* rgb_row = reinterpret_cast<H3RGB565*>(GetRow(y));
			rgb_row += x;

			for (int j = 0; j < _h; ++j)
			{
				H3RGB565* rgb = rgb_row;

				for (int i = 0; i < _w; ++i, ++rgb)
					rgb->GrayScale();

				rgb_row = reinterpret_cast<H3RGB565*>(reinterpret_cast<PUINT8>(rgb_row) + scanlineSize);
			}
		}
	}
	_H3API_ VOID H3LoadedPCX16::DrawHue(INT x, INT y, INT w, INT h, FLOAT hue, FLOAT saturation)
	{
		THISCALL_7(VOID, 0x44E610, this, x, y, w, h, DwordAt(&hue), DwordAt(&saturation));
	}
	_H3API_ BOOL H3LoadedPCX16::BackgroundRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL is_blue)
	{
		namespace dlg = NH3Dlg;
		PcxLoader back(is_blue ? dlg::HDassets::DLGBLUEBACK : dlg::Assets::DIBOXBACK);

		if (back.Get() == nullptr)
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
				back.Get()->DrawToPcx16(0, 0, _w, dh, this, _x, _y, FALSE);
				_x += 256;
				_w -= 256;
			}
			_y += 256;
			_h -= 256;
		}

		return TRUE;
	}
	_H3API_ BOOL H3LoadedPCX16::SimpleFrameRegion(INT32 x, INT32 y, INT32 _width, INT32 _height)
	{
		INT32 dX = _width;
		INT32 dY = _height;
		INT32 xEnd = x + _width;
		INT32 yEnd = y + _height;
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

			PcxLoader m_up;
			PcxLoader m_down;
			PcxLoader m_left;
			PcxLoader m_right;
			PcxLoader m_tl;
			PcxLoader m_tr;
			PcxLoader m_bl;
			PcxLoader m_br;
			H3LoadedPCX16* m_tgt;

			Frames(H3LoadedPCX16* bg) : 
				m_tgt(bg),
				m_up(NH3Dlg::HDassets::FRAME_U),
				m_down(NH3Dlg::HDassets::FRAME_D),
				m_left(NH3Dlg::HDassets::FRAME_L),
				m_right(NH3Dlg::HDassets::FRAME_R),
				m_tl(NH3Dlg::HDassets::FRAME_LU),
				m_tr(NH3Dlg::HDassets::FRAME_RU),
				m_bl(NH3Dlg::HDassets::FRAME_LD),
				m_br(NH3Dlg::HDassets::FRAME_RD)
			{				
			}

			PcxLoader* begin() { return &m_up; }
			PcxLoader* end() { return &begin()[8]; }

			BOOL AllLoaded()
			{
				for (int i = 0; i < 8; ++i)
					if (begin()[i].Get() == nullptr)
						return FALSE;
				return TRUE;
			}			

			VOID Draw(const INT x, const INT y, const INT frame)
			{
				begin()[frame].Get()->DrawToPcx16(0, 0, 4, 4, m_tgt, x, y, FALSE);
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
			frames.Draw(x + dX, y, frames.up);
			frames.Draw(x + dX, yEnd - 4, frames.down);
		}

		////////////////////////////////////////
		// do vertical sides - right to left
		////////////////////////////////////////
		while (dY >= 4)
		{
			dY -= 4;
			frames.Draw(x, y + dY, frames.left);
			frames.Draw(xEnd - 4, y + dY, frames.right);
		}

		////////////////////
		// Add corners
		////////////////////
		frames.Draw(x, y, frames.tl);
		frames.Draw(x, yEnd - 4, frames.bl);
		frames.Draw(xEnd - 4, y, frames.tr);
		frames.Draw(xEnd - 4, yEnd - 4, frames.br);

		return TRUE;
	}
	_H3API_ BOOL H3LoadedPCX16::FrameRegion(INT32 x, INT32 y, INT32 w, INT32 h, BOOL statusBar, INT32 colorIndex, BOOL is_blue)
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

		if (box.Get() == nullptr)
			return FALSE;

		// * copying to this local palette prevents recoloration of def for others
		H3Palette565 pal565, * pal;
		if (!is_blue)
		{
			F_memcpy(&pal565, box->palette565, sizeof(pal565));
			pal565.ColorToPlayer(colorIndex);
			pal = &pal565;
		}
		else
			pal = box->palette565;

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
		H3DefFrame* tm = box->GetGroupFrame(0, BoxFrames::BF_tm);
		H3DefFrame* bm = box->GetGroupFrame(0, f_bm);
		while (_w > 0)
		{
			tm->DrawToPcx16(0, 0, 64, 64, this, x + _w, y, pal);
			bm->DrawToPcx16(0, 0, 64, 64, this, x + _w, y + h - 64, pal);
			_w -= 64;
		}

		// * add vertical bars
		int _h = h - 64 - 64;
		H3DefFrame* ml = box->GetGroupFrame(0, BoxFrames::BF_ml);
		H3DefFrame* mr = box->GetGroupFrame(0, BoxFrames::BF_mr);
		while (_h > 0)
		{
			ml->DrawToPcx16(0, 0, 64, 64, this, x, y + _h, pal);
			mr->DrawToPcx16(0, 0, 64, 64, this, x + w - 64, y + _h, pal);
			_h -= 64;
		}

		// * add four corners
		box->GetGroupFrame(0, BoxFrames::BF_tl)->DrawToPcx16(0, 0, 64, 64, this, x, y, pal);
		box->GetGroupFrame(0, BoxFrames::BF_tr)->DrawToPcx16(0, 0, 64, 64, this, x + w - 64, y, pal);
		box->GetGroupFrame(0, f_bl)->DrawToPcx16(0, 0, 64, 64, this, x, y + h - 64, pal);
		box->GetGroupFrame(0, f_br)->DrawToPcx16(0, 0, 64, 64, this, x + w - 64, y + h - 64, pal);

		return 0;
	}
	_H3API_ VOID H3LoadedPCX16::SinkArea(INT32 x, INT32 y, INT32 w, INT32 h)
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
	_H3API_ VOID H3LoadedPCX16::BevelArea(INT32 x, INT32 y, INT32 w, INT32 h)
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
	_H3API_ VOID H3LoadedPCX16::TextDraw(H3Font* font, LPCSTR text, INT32 x, INT32 y, INT32 width, INT32 height, NH3Dlg::TextColor::eTextColor colorIndex, NH3Dlg::TextAlignment::eTextAlignment alignment)
	{
		THISCALL_10(VOID, 0x4B51F0, font, text, this, x, y, width, height, colorIndex, alignment, -1);
	}
	_H3API_ PUINT8 H3LoadedPCX16::GetRow(int row)
	{
		return buffer + row * scanlineSize;
	}
	_H3API_ H3RGB565* H3LoadedPCX16::GetPixel565(int x, int y)
	{
		return (H3RGB565*)GetRow(y) + x;
	}
	_H3API_ H3ARGB888* H3LoadedPCX16::GetPixel888(int x, int y)
	{
		return (H3ARGB888*)GetRow(y) + x;
	}
	_H3API_ H3LoadedPCX24* H3LoadedPCX24::Construct(LPCSTR name, INT width, INT height, PUINT8 data, UINT32 dataSize)
	{
		return THISCALL_6(H3LoadedPCX24*, 0x44EA20, this, name, width, height, data, dataSize);
	}
	_H3API_ VOID H3LoadedPCX24::DrawToPcx16(INT dst_x, INT dst_y, H3LoadedPCX16* dest, INT srcX, INT srcY)
	{
		return THISCALL_11(VOID, 0x44ECE0, this, srcX, srcY, width, height, dest->buffer, dst_x, dst_y, dest->width, dest->height, dest->scanlineSize);
	}
	_H3API_ H3LoadedPCX24* H3LoadedPCX24::Load(LPCSTR name, INT width, INT height)
	{
		H3LoadedPCX24* pcx = (H3LoadedPCX24*)F_malloc(sizeof(H3LoadedPCX24));
		UINT32 data_size = width * height * sizeof(H3RGB888);
		PUINT8 buffer = (PUINT8)F_malloc(data_size);
		pcx->Construct(name, width, height, buffer, data_size);
		return pcx;
	}
	_H3API_ PUINT8 H3LoadedPCX24::GetRow(int row)
	{
		return buffer + row * sizeof(H3RGB888) * width;
	}
	_H3API_ H3RGB888* H3LoadedPCX24::GetPixel(int x, int y)
	{
		return (H3RGB888*)GetRow(y) + x;
	}
	_H3API_ VOID H3DefFrame::DrawToPcx16(INT src_x, INT src_y, INT src_width, INT src_height, 
		H3LoadedPCX16* pcx16, INT dst_x, INT dst_y, H3Palette565* palette565, BOOL mirror, BOOL do_not_use_special_colors)
	{
		THISCALL_14(VOID, 0x47BE90, this, src_x, src_y, src_width, src_height, pcx16->buffer, 
			dst_x, dst_y, pcx16->width, pcx16->height, pcx16->scanlineSize, palette565, mirror, do_not_use_special_colors);
	}
	_H3API_ H3LoadedDEF* H3LoadedDEF::Load(LPCSTR name)
	{
		return THISCALL_1(H3LoadedDEF*, 0x55C9C0, name);
	}
	_H3API_ VOID H3LoadedDEF::AddFrameFromDef(LPCSTR source, INT32 index)
	{
		DefLoader src(source);
		if (!src.Get())
			return;
		H3DefFrame* frm = src->groups[0]->frames[0];
		H3DefGroup* grp = groups[0];

		H3DefFrame* frame = reinterpret_cast<H3DefFrame*>(F_malloc(sizeof(H3DefFrame)));
		if (frame)
		{
			F_memcpy(frame, frm, sizeof(H3DefFrame)); // copy frame data
			frame->rawData = reinterpret_cast<PUINT8>(F_malloc(frame->rawDataSize)); // new data buffer
			F_memcpy(frame->rawData, frm->rawData, frame->rawDataSize); // copy data buffer

			const int n_frames = grp->count;

			if (n_frames < index + 1) // add room for frame
			{
				H3DefFrame** new_list = reinterpret_cast<H3DefFrame**>(F_realloc(grp->frames, (index + 1) * 4));
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
	}
	_H3API_ VOID H3LoadedDEF::ColorToPlayer(INT32 id)
	{
		if (palette565)
			palette565->ColorToPlayer(id);
		palette888->ColorToPlayer(id);
	}
	_H3API_ H3DefFrame* H3LoadedDEF::GetGroupFrame(INT group, INT frame)
	{
		return groups[group]->frames[frame];
	}
	_H3API_ VOID H3LoadedDEF::DrawTransparent(INT32 frame, H3LoadedPCX16* pcx, INT32 x, INT32 y, 
		BOOL transparent, BOOL mirror, INT32 group, INT32 xFromRight, INT32 yFromBottom)
	{
		THISCALL_15(VOID, 0x47BA90, this, group, frame, xFromRight, yFromBottom, widthDEF, heightDEF, 
			pcx->buffer, x, y, pcx->width, pcx->height, pcx->scanlineSize, mirror, transparent);
	}
	_H3API_ VOID H3LoadedDEF::DrawToPcx16(INT group, INT frame, INT src_x, INT src_y, INT src_width, 
		INT src_height, H3LoadedPCX16* pcx16, INT dst_x, INT dst_y, BOOL mirror, BOOL do_not_use_special_colors)
	{
		GetGroupFrame(group, frame)->DrawToPcx16(src_x, src_y, src_width, src_height, 
			pcx16, dst_x, dst_y, palette565, mirror, do_not_use_special_colors);
	}
}