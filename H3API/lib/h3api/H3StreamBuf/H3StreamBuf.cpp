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

#include "H3StreamBuf.hpp"

namespace h3
{
	_H3API_ BOOL H3Streambuf::Save(PVOID data, UINT data_size)
	{
		if (data_size && THISCALL_3(UINT, vTable->saveRegion, this, data, data_size) >= data_size)
			return TRUE;
		return FALSE;
	}
	_H3API_ BOOL H3Streambuf::Load(PVOID data, UINT data_size)
	{
		if (data_size && THISCALL_3(UINT, vTable->loadRegion, this, data, data_size) >= data_size)
			return TRUE;
		return FALSE;
	}
}