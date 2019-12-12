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

#include "H3Ini.hpp"

namespace h3
{
#pragma warning(push)
#pragma warning(disable:4482)
	_H3API_ LPCSTR HDIniEntry::GetText()
	{
		if (entryType == eType::iniValue)
			return h3_NullString;
		return data.text;
	}
	_H3API_ HDIniEntry* HDIni::FindEntry(LPCSTR key)
	{
		HDIniEntry** e = entries;
		int i = lineEntries;

		while (i > 0)
		{
			HDIniEntry* c = *e;
			if (c->entryType == HDIniEntry::eType::iniKey)
			{
				if (F_strcmpi(key, c->data.text) == 0)
					return *e;

				i -= (c->entryCount + 1);
				e += (c->entryCount + 1);
			}
			else
			{
				i--;
				e++;
			}
		}
		return nullptr;
	}
#pragma warning(pop)
}