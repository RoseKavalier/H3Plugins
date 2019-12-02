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
#include "H3BinaryItems.h"

#define h3_DataPath							((H3String*)0x69E528)
#define h3_ActivePlayer						(*(H3Player**)0x69CCFC)
#define h3_HWND								(*(HWND*)0x699650)

// * various integer constants
#define h3_ArtifactCount					IntAt(0x44D1A8 + 2)
#define h3_CreatureCount					IntAt(0x5C8046 + 1)
#define h3_HeroCount						IntAt(0x4BD144 + 1)
#define h3_TownCount						(ByteAt(0x4BB0D7 + 2) + 1)
#define h3_SpellCount						ByteAt(0x4A2741 + 2)

// * game limits for text dialog
#define gameMaxWidth						IntAt(0x415AAB + 2)
#define gameMaxHeight						IntAt(0x415AC1 + 2)

#define h3_CurrentPlayerID					IntAt(0x69CCF4)
#define h3_CurrentAnimationSpeed			IntAt(0x69883C)
#define h3_IsCampaignGame					(IntAt(0x69779C) != 0)
#define h3_AnimationSpeed					((H3AnimationSpeed*)0x63CF7C)
#define h3_BattleShadowHexes				((H3Vector<INT>*)0x696A08)
#define h3_Instance							(*(HMODULE*)0x699604)

// * movement bonuses
#define SPEED_BONUS_BOOTS					IntAt(0x698B50) // usually 600 mp
#define SPEED_BONUS_GLOVES					IntAt(0x698B4C) // usually 300 mp
#define WATER_BONUS_NECKLACE				IntAt(0x698B54) // usually 1000 mp
#define WATER_BONUS_SEA_CAPTAIN				IntAt(0x698B5C) // usually 500 mp
#define SPEED_BONUS_STABLES					IntAt(0x698AE4) // usually 400 mp
#define WATER_BONUS_LIGHTHOUSE				WATER_BONUS_SEA_CAPTAIN // same as sea_captain's hat bonus ~500

#define h3_GamePath							((LPCSTR)0x698614)
#define h3_HeroRetreated					ByteAt(0x6985F3)
#define h3_HeroSurrendered					ByteAt(0x697794)
#define h3_AutoSolo							ByteAt(0x691259)
#define h3_HumanID							IntAt(0x6995A4)
#define h3_ActivePlayerBitset				(ByteAt(0x69CD10))
#define h3_ColorMode						PtrAt(0x694DB0)
#define h3_ObjectName(id)					StrAt(0x6A7A54 + 4 * (id))
#define h3_MineNames(type)					StrAt(0x6A7538 + 4 * (type))
#define h3_TentColors(type)					StrAt(0x6A7588 + 4 * (type))
#define h3_TerrainName(type)				StrAt(0x6A5EEC + 4 * (type))
#define h3_ResourceName(type)				StrAt(0x6A5ECC + 4 * (type))
#define h3_RandomSignText(type)				StrAt(0x696CC4 + 4 * (type))
#define h3_PlayerColor(type)				StrAt(0x6A7E60 + 4 * (type))
#define h3_DwellingNames1(type)				StrAt(0x69154C + 4 * (type))
#define h3_DwellingNames4(type)				StrAt(0x6913A4 + 4 * (type))
#define h3_ExeVersion						PtrAt(0x588479)
#define h3_VersionSOD						0xFFFFE403
#define h3_SaveName							((PCHAR)0x69FC88)
#define h3_QuestsText						((H3QuestText*)0x69E788)
#define h3_SeersText						((H3QuestText*)0x69F148)
#define h3_NeutralBuildingCosts				(*(H3NeutralBuildingCosts*)(0x5C1509 + 3))
#define h3_SpecialBuildingCosts				(*(H3SpecialBuildingCosts**)(0x5C1539 + 3))
#define h3_DwellingBuildingCosts			(*(H3DwellingBuildingCosts**)(0x5C1566 + 3))
#define h3_TownDependencies					(*(H3TownDependencies**)(0x5D6015 + 3))
#define h3_SecondarySkillsInfo				(*(H3SecondarySkillInfo**)(0x67DCF0))
#define h3_SecondarySkillLevel(level)		StrAt(0x6A75D4 + 4 * (level))

// Pointers P_ from Heroes3.exe
#define P_GeneralText						(*(H3ColumnTextFile**)0x6A5DC4)
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
#define P_GamePalette						(*(H3Palette565**)0x6AAD18)
#define P_PlayersPalette					(*(H3Palette565**)0x6AAD10)
#define P_TinyFont							(*(H3Font**)0x698A54)
#define P_SmallFont							(*(H3Font**)0x698A58)
#define P_MediumFont						(*(H3Font**)0x698A5C)
#define P_BigFont							(*(H3Font**)0x698A60)
#define P_CalliFont							(*(H3Font**)0x698A64)
#define P_BinaryTree						((H3BinTreeList*)0x69E560)
#define P_HeroInfo							(*(H3HeroInfo**)0x67DCE8)

// Constants C_ from Heroes3.exe

#define C_ButtonWav							(*(H3WavFile**)0x694DF4)

namespace h3
{
	// * pointers to data
	namespace ptr
	{
		inline H3Font* TinyFont() { return *reinterpret_cast<H3Font**>(0x698A54); }
		inline H3Font* SmallFont() { return *reinterpret_cast<H3Font**>(0x698A58); }
		inline H3Font* MediumFont() { return *reinterpret_cast<H3Font**>(0x698A5C); }
		inline H3Font* BigFont() { return *reinterpret_cast<H3Font**>(0x698A60); }
		inline H3Font* CalliFont() { return *reinterpret_cast<H3Font**>(0x698A64); }
		inline H3Palette565* GamePalette() { return *reinterpret_cast<H3Palette565**>(0x6AAD18); }
		inline H3Palette565* PlayersPalette() { return *reinterpret_cast<H3Palette565**>(0x6AAD10); }
		inline H3BinTreeList* BinaryTree() { return reinterpret_cast<H3BinTreeList*>(0x69E560); }
		inline H3HeroInfo* HeroInformation() { return *reinterpret_cast<H3HeroInfo**>(0x67DCE8); }
		inline H3WavFile* ButtonWav() { return *reinterpret_cast<H3WavFile**>(0x694DF4); }
		inline H3ColumnTextFile* GeneralText() { return *reinterpret_cast<H3ColumnTextFile**>(0x6A5DC4); }
		inline H3GlobalObjectSettings* ObjectSettings() { return *reinterpret_cast<H3GlobalObjectSettings**>(0x660428); }
		inline H3Spell* Spells() { return *reinterpret_cast<H3Spell**>(0x687FA8); }
		inline H3CreatureBankSetup* CreatureBanks() { return *reinterpret_cast<H3CreatureBankSetup**>(0x47A3C1 + 1); }
		inline H3ValidCatapultTargets* CatapultTargets() { return *reinterpret_cast<H3ValidCatapultTargets**>(0x4929DD + 3); }
		inline H3ArtifactSetup* Artifacts() { return *reinterpret_cast<H3ArtifactSetup**>(0x660B68); }
		inline H3CreatureInformation* Creatures() { return *reinterpret_cast<H3CreatureInformation**>(0x6747B0); }
		inline H3ObstacleInfo* Obstacles() { return *reinterpret_cast<H3ObstacleInfo**>(0x465C21); }
		inline H3Hero* DialogHero() { return *reinterpret_cast<H3Hero**>(0x698B70); }
		inline H3TurnTimer* TurnTimer() { return *reinterpret_cast<H3TurnTimer**>(0x4AD194 + 1); }
		inline H3HeroSpecialty* HeroSpecialties() { return *reinterpret_cast<H3HeroSpecialty**>(0x4B8AF1 + 1); }
		inline H3Dlg* NewGameDialog() { return *reinterpret_cast<H3Dlg**>(0x69FC44); }
	}
	// * constants
	namespace cst
	{
		inline INT ArtifactCount() { return *reinterpret_cast<INT*>(0x44D1A8 + 2); }
		inline INT CreatureCount() { return *reinterpret_cast<INT*>(0x5C8046 + 1); }
		inline INT HeroCount()     { return *reinterpret_cast<INT*>(0x4BD144 + 1); }
		inline UINT8 TownCount()   { return *reinterpret_cast<UINT8*>(0x4BB0D7 + 2) + 1; }
		inline UINT8 SpellCount()  { return *reinterpret_cast<UINT8*>(0x4A2741 + 2); }
	}
	// * variables
	namespace var
	{

	}
	// * managers
	namespace mgr
	{
		inline H3MouseManager*     Mouse()     { return *reinterpret_cast<H3MouseManager**>(0x6992B0); }
		inline H3WindowManager*    Window()    { return *reinterpret_cast<H3WindowManager**>(0x6992D0); }
		inline H3Executive*        Executive() { return *reinterpret_cast<H3Executive**>(0x699550); }
		inline H3Main*             Main()      { return *reinterpret_cast<H3Main**>(0x699538); }
		inline H3CombatManager*    Combat()    { return *reinterpret_cast<H3CombatManager**>(0x699420); }
		inline H3TownManager*      Town()      { return *reinterpret_cast<H3TownManager**>(0x69954C); }
		inline H3SoundManager*     Sound()     { return *reinterpret_cast<H3SoundManager**>(0x699414); }
		inline H3InputManager*     Input()     { return *reinterpret_cast<H3InputManager**>(0x699530); }
		inline H3AdventureManager* Adventure() { return *reinterpret_cast<H3AdventureManager**>(0x6992B8); }
		inline H3MovementManager*  Movement()  { return *reinterpret_cast<H3MovementManager**>(0x6992D4); }
	}
}


// others
constexpr INT COMBATSQUARE_DIMENSION	= 44;
constexpr INT MULTIPLAYER_ICON			= 0x66;

#endif /* #define _H3DEFINES_H_ */