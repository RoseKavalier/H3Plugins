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

#ifndef _H3INI_HPP_
#define _H3INI_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

namespace h3
{
#pragma pack(push, 1)
	// * HDmod's format for ini files lines
	struct HDIniEntry // size 0xD ~ 13
	{
		union
		{
			LPCSTR text;
			UINT32 value;
		}data;
		_H3ENUM_ eType : BYTE
		{
			iniValue = 2,
			iniText = 3,
			iniKey = 4
		};
		eType entryType;
		DWORD entryCount;
		LPCSTR uselessText; // like " = ", end of line, ...

		LPCSTR GetText();
	};
	
	// * HDmod's format for ini files
	struct HDIni
	{
		HDIniEntry** entries;
		INT32 lineEntries;
		h3unk _f_08[4];
		CHAR name[8]; // unknown length

		HDIniEntry* FindEntry(LPCSTR key);
	};
#pragma pack(pop)
}

#endif /* #define _H3INI_HPP_ */