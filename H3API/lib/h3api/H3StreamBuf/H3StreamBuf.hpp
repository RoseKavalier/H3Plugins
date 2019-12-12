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

#ifndef _H3STREAMBUF_HPP_
#define _H3STREAMBUF_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"

namespace h3
{
	// * the start of the save/load structure used by H3
	// * possibly ofstream or similar
		struct H3Streambuf
		{
		protected:
			struct {
				h3func freeSave;
				// * +4
				h3func loadRegion;
				// * +8
				h3func saveRegion;
			}*vTable;

			// goes on ...

		public:
			BOOL Save(PVOID data, UINT data_size);
			BOOL Load(PVOID data, UINT data_size);
		};
}

#endif /* #define _H3STREAMBUF_HPP_ */