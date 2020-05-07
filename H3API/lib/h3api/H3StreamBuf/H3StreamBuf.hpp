//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2020-05-06                       //
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
		_H3API_ BOOL Save(PVOID data, UINT data_size);
		_H3API_ BOOL Load(PVOID data, UINT data_size);

		template<typename T>
		inline BOOL Read(T& data, UINT data_size = sizeof(T));
		template<typename T>
		inline BOOL Write(T& data, UINT data_size = sizeof(T));
	};
}

#endif /* #define _H3STREAMBUF_HPP_ */