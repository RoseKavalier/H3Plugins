//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-06-20                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "H3Bitmap.hpp"
#include "H3Bitmap.inl"

namespace h3
{
    _H3API_ BOOL H3Bitmap::Create(const H3LoadedPcx16& pcx)
    {
        if (!init(pcx.width, pcx.height))
            return FALSE;

        if (H3Internal::_bitMode() == 2)
        {
            // todo check green mask for RGB555 case
            PH3RGB565 src  = reinterpret_cast<PH3RGB565>(pcx.buffer);
            RGBTRIPLE* dst = reinterpret_cast<RGBTRIPLE*>(m_pixels.Get());

            for (INT y = 0; y < pcx.height; ++y)
            {
                for (INT x = 0; x < pcx.width; ++x)
                {
                    H3RGB888 rgb     = src[x]; // rgb565 to rgb888
                    dst[x].rgbtRed   = rgb.r;
                    dst[x].rgbtGreen = rgb.g;
                    dst[x].rgbtBlue  = rgb.b;
                }
                src = reinterpret_cast<PH3RGB565>(reinterpret_cast<PUINT8>(src) + pcx.scanlineSize);
                dst = reinterpret_cast<PRGBTRIPLE>(reinterpret_cast<PUINT8>(dst) + m_scanline);
            }
        }
        else
        {
            PH3ARGB888 src = reinterpret_cast<PH3ARGB888>(pcx.buffer);
            PRGBTRIPLE dst = reinterpret_cast<PRGBTRIPLE>(m_pixels.Get());

            for (INT y = 0; y < pcx.height; ++y)
            {
                for (INT x = 0; x < pcx.width; ++x)
                {
                    dst[x].rgbtRed   = src[x].r;
                    dst[x].rgbtGreen = src[x].g;
                    dst[x].rgbtBlue  = src[x].b;
                }
                src = reinterpret_cast<PH3ARGB888>(reinterpret_cast<PUINT8>(src) + pcx.scanlineSize);
                dst = reinterpret_cast<PRGBTRIPLE>(reinterpret_cast<PUINT8>(dst) + m_scanline);
            }
        }

        // flip horizontally, pcx is top down, bmp is bottom up
        m_info.biHeight = -m_info.biHeight;

        return TRUE;
    }
    _H3API_ BOOL H3Bitmap::Save(LPCSTR file_name)
    {
        if (!m_pixels)
            return FALSE;
        H3File f;
        if (!f.Save(file_name))
            return FALSE;
        if (!f.Write(m_header))
            return FALSE;
        if (!f.Write(m_info))
            return FALSE;
        return f.Write(m_pixels.Get(), m_scanline * height());
    }
    _H3API_ BOOL H3Bitmap::Save(const H3String& file_name)
    {
        return Save(file_name.String());
    }
    _H3API_ INT H3Bitmap::height()
    {
        return m_info.biHeight < 0 ? -m_info.biHeight : m_info.biHeight;
    }
    _H3API_ BOOL H3Bitmap::init(INT width, INT height)
    {
        m_scanline             = ((width * 3 + 3) >> 2) << 2; // padding to multiple of 4
        m_dynamicSize          = m_scanline * height;
        m_pixels.Set(ByteAllocator().allocate(m_dynamicSize));
        if (!m_pixels)
            return FALSE;

        m_header.bfType        = 0x4D42;
        m_header.bfOffBits     = sizeof(m_header) + sizeof(m_info);
        m_header.bfSize        = sizeof(m_header) + sizeof(m_info) + m_dynamicSize;

        m_info.biSize          = sizeof(m_info);
        m_info.biWidth         = width;
        m_info.biHeight        = height;
        m_info.biPlanes        = 1;
        m_info.biBitCount      = 8 * 3;
        m_info.biCompression   = BI_RGB;
        m_info.biSizeImage     = 0;
        m_info.biXPelsPerMeter = 3780;
        m_info.biYPelsPerMeter = 3780;
        m_info.biClrUsed       = 0;
        m_info.biClrImportant  = 0;

        return TRUE;
    }
}