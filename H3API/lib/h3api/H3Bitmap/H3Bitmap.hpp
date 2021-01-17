//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2020-06-20                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3BITMAP_HPP_
#define _H3BITMAP_HPP_

#include "../H3_BinaryItems.hpp"
#include "../H3_Stream.hpp"

namespace h3
{
	/**
	 * @brief exports 24-bit bitmap to disk from H3LoadedPcx16 in memory
	 */
	class H3Bitmap
	{
	public:
		/**
		 * @brief transforms the specified pcx to bitmap
		 *
		 * @param pcx a loaded image in memory to convert as bitmap
		 * @return BOOL whether the conversion was successful
		 */
		_H3API_ BOOL Create(const H3LoadedPcx16& pcx);
		/**
		 * @brief saves a converted memory pcx to bitmap on disk
		 *
		 * @param file_name the destination name or path of the image
		 * @return BOOL whether the image was successfully saved
		 */
		_H3API_ BOOL Save(LPCSTR file_name);
		/**
		 * @brief saves a converted memory pcx to bitmap on disk
		 *
		 * @param file_name the destination name or path of the image
		 * @return BOOL whether the image was successfully saved
		 */
		_H3API_ BOOL Save(const H3String& file_name);

	private:
		_H3API_ INT  height();
		_H3API_ BOOL init(INT width, INT height);

		BITMAPFILEHEADER  m_header;
		BITMAPINFOHEADER  m_info;
		UINT              m_scanline;
		UINT              m_dynamicSize;
		H3UniquePtr<BYTE> m_pixels;
	};
}

#endif /* #define _H3BITMAP_HPP_ */