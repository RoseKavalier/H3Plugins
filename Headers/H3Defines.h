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

#ifndef _H3DEFINES_H_
#define _H3DEFINES_H_

#pragma once

#include "H3Base.h"
#include "H3Structures.h"

#define h3_DataPath							((H3String*)0x69E528)
#define h3_ActivePlayer						(*(H3Player**)0x69CCFC)
#define h3_HWND								(*(HWND*)0x699650)

#define h3_GeneralText						(*(H3ColumnTextFile**)0x6A5DC4)
#define h3_CurrentPlayerID					IntAt(0x69CCF4)
#define h3_CurrentAnimationSpeed			IntAt(0x69883C)
#define h3_IsCampaignGame					(IntAt(0x69779C) != 0)
#define h3_AnimationSpeed					((H3AnimationSpeed*)0x63CF7C)
#define h3_BattleShadowHexes				((H3Vector<INT>*)0x696A08)

// Pointers P_ from Heroes3.exe

#define P_MouseMgr							(*(H3MouseManager**)0x6992B0)
#define P_WindowMgr							(*(H3WindowManager**)0x6992D0)
#define P_Executive							(*(H3Executive**)0x699550)
#define P_Main								(*(H3Main**)0x699538)
#define P_CombatMgr							(*(H3CombatManager**)0x699420)
#define P_TownMgr							(*(H3TownManager**)0x69954C)
#define P_SoundMgr							(*(H3SoundManager**)0x699414)
#define P_InputMgr							(*(H3InputManager**)0x699530)
#define P_AdventureMgr						(*(H3AdventureManager**)0x6992B8)
#define P_MovementMgr						(*(H3MovementManager**)0x6992D4)
#define P_ObjectSettings					(*(H3GlobalObjectSettings**)0x660428)
#define P_Spell								(*(H3Spell**)0x687FA8)
#define P_CreatureBankTable					(*(H3CreatureBankSetup**)(0x47A3C1 + 1))
#define P_ValidCatapultTargets				(*(H3ValidCatapultTargets**)(0x4929DD + 3)) // up to 0x63BEC8, exclusively ~ so 8 total
#define P_Artifacts							(*(H3ArtifactSetup**)0x660B68)
#define P_Creatures							(*(H3CreatureInformation**)0x6747B0)
#define P_DefObstacleInfo					(*(H3ObstacleInfo**)0x465C21) // 0x63C7C8 in SoD
#define P_DialogHero						(*(H3Hero**)0x698B70)
#define P_TurnTimer							(*(H3TurnTimer**)(0x4AD194 + 1))
#define P_HeroSpecialty						(*(H3HeroSpecialty**)(0x4B8AF1 + 1))
#define P_NewGameDlg						(*(H3Dlg**)0x69FC44)

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