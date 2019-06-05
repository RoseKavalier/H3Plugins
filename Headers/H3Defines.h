//////////////////////////////////////////////////////////////////////
//																	//
//					Created by RoseKavalier:						//
//					rosekavalierhc@gmail.com						//
//																	//
//		    ***You may use or distribute these files freely			//
//			   so long as this notice remains present.***			//
//																	//
//			In preparing these files, several sources were			//
//				consulted, they are listed in no particular			//
//							order below.							//
//																	//
//	Source: https://github.com/potmdehex/homm3tools					//
//	Author: potmdehex and contributors								//
//																	//
//	Source: https://github.com/redxu/HoMM3_FA						//
//	Author: redxu													//
//																	//
//	Source: https://github.com/openhomm/openhomm					//
//	Author: Ershov Stanislav, Fomin Roman, Akulich Alexander		//
//																	//
//	Source: https://github.com/GrayFace/wog							//
//	Author: GrayFace and WoG team									//
//																	//
//	Source: https://github.com/ethernidee/era						//
//	Author: Berserker												//
//																	//
//	Source: https://github.com/ethernidee/era-editor				//
//	Author: Grayface and Berserker									//
//																	//
//	Source:	http://wforum.heroes35.net/showthread.php?tid=3900		//
//	Author: Slava and GrayFace										//
//																	//
//	Source: http://wforum.heroes35.net/showthread.php?tid=4583		//
//	Author: gamecreator												//
//																	//
//	Thanks: patcher_x86 by baratorch and code therein				//
//																	//
//////////////////////////////////////////////////////////////////////

#ifndef _H3DEFINES_H_
#define _H3DEFINES_H_

#pragma once

#include "H3Base.h"
#include "H3Structures.h"

#define h3_DataPath							((H3String*)0x69E528)
#define h3_ActivePlayer						(*(H3Player**)0x69CCFC)

#define h3_GeneralText						(*(H3ColumnTextFile**)0x6A5DC4)
#define h3_CurrentPlayerID					IntAt(0x69CCF4)
#define h3_CurrentAnimationSpeed			IntAt(0x69883C)
#define h3_IsCampaignGame					(IntAt(0x69779C) != 0)
#define h3_AnimationSpeed					((H3AnimationSpeed*)0x63CF7C)
#define h3_BattleShadowHexes				((H3Vector<INT>*)0x696A08)

// various non-member functions
#define h3_GetTileVision(x, y, z)			FASTCALL_3(H3TileVision*, 0x4F8070, x, y, z)
#define h3_ReveaTile(x,y,z)					(h3_GetTileVision(x, y, z)->vision |= h3_ActivePlayerBitset)


// Constants C_ from Heroes3.exe

#define C_ButtonWav							(*(H3WavFile**)0x694DF4)

inline void H3SoundManager::ClickSound()
{
	H3WavFile *buttonWav = C_ButtonWav;
	INT32 backup = clickSoundVar;
	buttonWav->spinCount = 64;
	buttonWav->debugInfo = (PRTL_CRITICAL_SECTION_DEBUG)1;
	buttonWav->lockSemaphore = (HANDLE)(HANDLE_FLAG_PROTECT_FROM_CLOSE | HANDLE_FLAG_INHERIT);
	THISCALL_2(void, 0x59A510, this, buttonWav);
	clickSoundVar = backup;
}

// others
#define COMBATSQUARE_DIMENSION				44
#define MULTIPLAYER_ICON					0x66

#endif /* #define _H3DEFINES_H_ */