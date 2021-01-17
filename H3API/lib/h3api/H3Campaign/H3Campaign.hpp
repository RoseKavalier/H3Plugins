//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2021-01-14                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3CAMPAIGN_HPP_
#define _H3CAMPAIGN_HPP_

#include "../H3_Base.hpp"
#include "../H3_Constants.hpp"

namespace h3
{
#pragma pack(push, 4)

	struct H3CmpBonusBuildings
	{
		typedef NH3Towns::eBuildings eBuildings;

		LPCSTR names[44];
	};

#pragma pack(pop)
}

#endif /* #define _H3CAMPAIGN_HPP_ */