//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3DIALOGS_INL_
#define _H3DIALOGS_INL_

#include "H3Dialogs.hpp"

namespace h3
{
	template<typename ItemType>
	inline typename ItemType * H3BaseDlg::Get(UINT16 id)
	{
		return reinterpret_cast<ItemType*>(GetH3DlgItem(id));
	}

	template<typename ItemType>
	inline typename ItemType* H3DlgItem::Cast()
	{
		return reinterpret_cast<ItemType*>(this);
	}
}

#endif /* #define _H3DIALOGS_INL_ */