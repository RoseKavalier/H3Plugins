//////////////////////////////////////////////////////////////////////
//                                                                  //
//                  Created by RoseKavalier:                        //
//                  rosekavalierhc@gmail.com                        //
//                                                                  //
//          ***You may use or distribute these files freely         //
//             so long as this notice remains present.***           //
//                                                                  //
//          In preparing these files, several sources were          //
//            consulted, they are listed in no particular           //
//                          order below.                            //
//                                                                  //
//  Source: https://github.com/potmdehex/homm3tools                 //
//  Author: potmdehex and contributors                              //
//                                                                  //
//  Source: https://github.com/redxu/HoMM3_FA                       //
//  Author: redxu                                                   //
//                                                                  //
//  Source: https://github.com/openhomm/openhomm                    //
//  Author: Ershov Stanislav, Fomin Roman, Akulich Alexander        //
//                                                                  //
//  Source: https://github.com/GrayFace/wog                         //
//  Author: GrayFace and WoG team                                   //
//                                                                  //
//  Source: https://github.com/ethernidee/era                       //
//  Author: Berserker                                               //
//                                                                  //
//  Source: https://github.com/ethernidee/era-editor                //
//  Author: Grayface and Berserker                                  //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=3900      //
//  Author: Slava and GrayFace                                      //
//                                                                  //
//  Source: http://wforum.heroes35.net/showthread.php?tid=4583      //
//  Author: gamecreator                                             //
//                                                                  //
//  Thanks: patcher_x86 by baratorch and code therein               //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3LOD_H_
#define _H3LOD_H_

#pragma once

#include "H3Base.h"

struct H3LodItem
{
	// * +0
	CHAR name[12];
	h3unk _f_0C[4];
	// * +10
	PUINT8 buffer;
	// * +14
	UINT32 size;
	// * +18
	INT32 type;
	h3unk _f_1C[4];
};

// * size 190h
struct H3Lod
{
	// * +0
	LPCSTR name;
	// * +4
	FILE* filePosition;
	// * +8
	CHAR path[256]; // possibly less, not important
	h3unk _f_108[112];
	// * +178
	INT32 filesCount;
	h3unk _f_17C[4];
	// * +180
	PUINT8 fileHeaders;
	h3unk _f_184[12];

	H3Lod* Create(LPCSTR fileName) { return THISCALL_2(H3Lod*, 0x559420, this, fileName); }
	VOID Destroy() { THISCALL_1(VOID, 0x559460, this); }

	// * 1 means READ_ONLY
	BOOL Load(LPCSTR fileName) { return THISCALL_3(BOOL, 0x4FAF30, &filePosition, fileName, 1); }
	BOOL8 FindFileInLod(LPCSTR file) { return THISCALL_2(BOOL8, 0x4FB100, &filePosition, file); }
	H3LodItem* LoadFileFromLod(LPCSTR file) { return THISCALL_2(H3LodItem*, 0x4FACA0, &filePosition, file); }
};

#endif /* #define _H3LOD_H_ */