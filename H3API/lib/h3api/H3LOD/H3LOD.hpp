//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3LOD_HPP_
#define _H3LOD_HPP_

#include "../H3_Base.hpp"

namespace h3
{
#pragma pack(push, 1)
	struct H3Msk
	{
		struct Msk
		{
			DWORD dbits;
			WORD  wbits;

			_H3API_ void operator>>(H3ObjectMask& mask) const;
		};

		UINT8 width;	  /**< @brief [00] number or cells occupied horizontally*/
		UINT8 height;	  /**< @brief [01] number or cells occupied vertically*/
		Msk   colorMask;  /**< @brief [02] which cells have a display colour*/
		Msk   shadowMask; /**< @brief [08] which cells have a shadow colour*/
	};
	_H3API_ASSERT_SIZE_(H3Msk, 14);
#pragma pack(pop)

#pragma pack(push, 4)
	struct H3LodItem
	{
		CHAR    name[12];		 /**< @brief [00]*/
		h3unk32 nameEnd;		 /**< @brief [0C] always 0, indicates end of name*/
		PUINT8  buffer;			 /**< @brief [10]*/
		UINT32  size;			 /**< @brief [14]*/
		INT32   type;			 /**< @brief [18]*/
		UINT32 sizeCompressed;   /**< @brief [1C]*/
	};
	_H3API_ASSERT_SIZE_(H3LodItem, 0x20);

	struct H3LoadedMsk
	{
		UINT width;			 /**< @brief [00]*/
		UINT height;		 /**< @brief [04]*/
		H3ObjectMask colors; /**< @brief [08]*/
		H3ObjectMask shadow; /**< @brief [10]*/

		_H3API_ VOID operator=(const H3Msk& msk);
	};
	_H3API_ASSERT_SIZE_(H3LoadedMsk, 0x18);

	// * size 190h
	struct H3Lod
	{
		LPCSTR name;		 /**< @brief [00] lod's name*/
		FILE*  filePosition; /**< @brief [04]*/
		CHAR   path[256]; 	 /**< @brief [08] possibly fewer chars, not important*/
		h3unk  _f_108[112];	 /**< @brief [108]*/
		INT32  filesCount;	 /**< @brief [178]*/
		h3unk  _f_17C[4];	 /**< @brief [17C]*/
		PUINT8 fileHeaders;	 /**< @brief [180] buffer to lod item headers*/
		h3unk  _f_184[12];   /**< @brief [184]*/

		_H3API_ H3Lod*     Create(LPCSTR fileName);
		_H3API_ VOID       Destroy();
		_H3API_ BOOL       Load(LPCSTR fileName);
		_H3API_ BOOL8      FindFileInLod(LPCSTR file);
		_H3API_ H3LodItem* LoadFileFromLod(LPCSTR file);
	};
	_H3API_ASSERT_SIZE_(H3Lod, 0x190);

#pragma pack(pop)
}

#endif /* #define _H3LOD_HPP_ */