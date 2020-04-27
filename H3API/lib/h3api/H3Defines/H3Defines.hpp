//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-06                        //
//                      Last edit: 2020-04-27                       //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#ifndef _H3DEFINES_HPP_
#define _H3DEFINES_HPP_

#include "../H3_Core.hpp"
#include "../H3_Base.hpp"
#include "../H3_BinaryItems.hpp"
#include "../H3_Dialogs.hpp"
//#include "../H3_String.hpp"
#include "../H3_Structures.hpp"

namespace h3
{	
	_H3API_ LPCSTR h3_SecondarySkillLevel(INT level);
	_H3API_ LPCSTR h3_PrimarySkillName(INT id);
	_H3API_ LPCSTR h3_MagicSchoolName(INT school);
	_H3API_ LPCSTR h3_ObjectName(INT id);
	_H3API_ LPCSTR h3_MineNames(INT type);
	_H3API_ LPCSTR h3_TentColors(INT type);
	_H3API_ LPCSTR h3_CastleName(INT type);
	_H3API_ LPCSTR h3_TerrainName(INT type);
	_H3API_ LPCSTR h3_ResourceName(INT type);
	_H3API_ LPCSTR h3_RandomSignText(INT type);
	_H3API_ LPCSTR h3_PlayerColor(INT type);
	_H3API_ LPCSTR h3_DwellingNames1(INT type);
	_H3API_ LPCSTR h3_DwellingNames4(INT type);
	_H3API_ H3SpecialBuildingCosts& h3_SpecialBuildingCosts(int town);
	_H3API_ H3DwellingBuildingCosts& h3_DwellingBuildingCosts(int town);
	_H3API_ H3SecondarySkillInfo& h3_SecondarySkillsInfo(int skill);
	_H3API_ H3GlobalObjectSettings& P_ObjectSettings(int id);
	_H3API_ H3Spell& P_Spell(int id);
	_H3API_ H3CreatureBankSetup& P_CreatureBankTable(int id);
	_H3API_ H3ValidCatapultTargets& P_ValidCatapultTargets(int id);
	_H3API_ H3ArtifactSetup& P_Artifacts(int id);
	_H3API_ H3CreatureInformation& P_Creatures(int id);
	_H3API_ H3ObstacleInfo& P_DefObstacleInfo(int id);
	_H3API_ H3HeroInfo& P_HeroInfo(int id);
	_H3API_ H3HeroSpecialty& P_HeroSpecialty(int id);
	_H3API_ LPCSTR P_HeroDefaultBiography(int id);
	_H3API_ H3TownCreatureTypes& P_TownCreatureTypes(int town);	

	LPCSTR const h3_GamePath = LPCSTR(0x698614);

#ifdef _H3API_DONT_USE_MACROS_
	// * game information
	_H3API_ H3String& h3_DataPath();
	_H3API_ HWND      h3_HWND();
	_H3API_ HMODULE   h3_Instance();
	_H3API_ UINT      h3_ColorMode();
	_H3API_ PCHAR     h3_SaveName();

	// * various integer constants
	_H3API_ INT   h3_ArtifactCount();
	_H3API_ INT   h3_CreatureCount();
	_H3API_ INT   h3_HeroCount();
	_H3API_ UINT8 h3_TownCount();
	_H3API_ UINT8 h3_SpellCount();

	// * game limits for text dialog
	_H3API_ INT gameMaxWidth();
	_H3API_ INT gameMaxHeight();

	// * gameplay values
	_H3API_ INT  h3_CurrentPlayerID();
	_H3API_ INT  h3_CurrentAnimationSpeed();
	_H3API_ BOOL h3_IsCampaignGame();
	_H3API_ BYTE h3_HeroRetreated();
	_H3API_ BYTE h3_HeroSurrendered();
	_H3API_ BYTE h3_AutoSolo();
	_H3API_ INT  h3_HumanID();
	_H3API_ BYTE h3_ActivePlayerBitset();

	// * gameplay structures
	_H3API_ H3Player&               h3_ActivePlayer();
	_H3API_ H3QuestText&            h3_QuestsText();
	_H3API_ H3QuestText&            h3_SeersText();
	_H3API_ H3AnimationSpeed&       h3_AnimationSpeed();
	_H3API_ H3Vector<INT>&          h3_BattleShadowHexes();
	_H3API_ H3TownDependencies&     h3_TownDependencies();
	_H3API_ H3NeutralBuildingCosts& h3_NeutralBuildingCosts();

	// * movement bonuses
	_H3API_ INT SPEED_BONUS_BOOTS();
	_H3API_ INT SPEED_BONUS_GLOVES();
	_H3API_ INT WATER_BONUS_NECKLACE();
	_H3API_ INT WATER_BONUS_SEA_CAPTAIN();
	_H3API_ INT SPEED_BONUS_STABLES();
	_H3API_ INT WATER_BONUS_LIGHTHOUSE();

	// Pointers P_ from Heroes3.exe

	_H3API_ H3ColumnTextFile&   P_GeneralText();
	_H3API_ H3MouseManager&     P_MouseMgr();
	_H3API_ H3WindowManager&    P_WindowMgr();
	_H3API_ H3Executive&        P_Executive();
	_H3API_ H3Main&             P_Main();
	_H3API_ H3CombatManager&    P_CombatMgr();
	_H3API_ H3TownManager&      P_TownMgr();
	_H3API_ H3SoundManager&     P_SoundMgr();
	_H3API_ H3InputManager&     P_InputMgr();
	_H3API_ H3AdventureManager& P_AdventureMgr();
	_H3API_ H3MovementManager&  P_MovementMgr();
	_H3API_ H3Hero&             P_DialogHero();
	_H3API_ H3TurnTimer&        P_TurnTimer();		
	_H3API_ H3Dlg*              P_NewGameDlg();
	_H3API_ H3Palette565&       P_GamePalette();
	_H3API_ H3Palette565&       P_PlayersPalette();
	_H3API_ H3Font&             P_TinyFont();
	_H3API_ H3Font&             P_SmallFont();
	_H3API_ H3Font&             P_MediumFont();
	_H3API_ H3Font&             P_BigFont();
	_H3API_ H3Font&             P_CalliFont();
	_H3API_ H3BinTreeList&      P_BinaryTree();

	// Constants C_ from Heroes3.exe

	_H3API_ H3WavFile& C_ButtonWav();
#else
#define h3_DataPath							((h3::H3String*)0x69E528)
#define h3_ActivePlayer						(*(h3::H3Player**)0x69CCFC)
#define h3_HWND								(*(HWND*)0x699650)

		// * various integer constants
#define h3_ArtifactCount					IntAt(0x44D1A8 + 2)
#define h3_CreatureCount					IntAt(0x5C8046 + 1)
#define h3_HeroCount						IntAt(0x4BD144 + 1)
#define h3_TownCount						ByteAt(0x5452D0 + 2)
#define h3_SpellCount						ByteAt(0x4A2741 + 2)

// * game limits for text dialog
#define gameMaxWidth						IntAt(0x415AAB + 2)
#define gameMaxHeight						IntAt(0x415AC1 + 2)

#define h3_CurrentPlayerID					IntAt(0x69CCF4)
#define h3_CurrentAnimationSpeed			IntAt(0x69883C)
#define h3_IsCampaignGame					(IntAt(0x69779C) != 0)
#define h3_AnimationSpeed					((h3::H3AnimationSpeed*)0x63CF7C)
#define h3_BattleShadowHexes				((h3::H3Vector<INT>*)0x696A08)
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
#define h3_SaveName							((PCHAR)0x69FC88)
#define h3_QuestsText						((h3::H3QuestText*)0x69E788)
#define h3_SeersText						((h3::H3QuestText*)0x69F148)
#define h3_TownDependencies					(*(h3::H3TownDependencies**)(0x5D6015 + 3))

// Pointers P_ from Heroes3.exe
#define P_GeneralText						(*(h3::H3ColumnTextFile**)0x6A5DC4)
#define P_MouseMgr							(*(h3::H3MouseManager**)0x6992B0)
#define P_WindowMgr							(*(h3::H3WindowManager**)0x6992D0)
#define P_Executive							(*(h3::H3Executive**)0x699550)
#define P_Main								(*(h3::H3Main**)0x699538)
#define P_CombatMgr							(*(h3::H3CombatManager**)0x699420)
#define P_TownMgr							(*(h3::H3TownManager**)0x69954C)
#define P_SoundMgr							(*(h3::H3SoundManager**)0x699414)
#define P_InputMgr							(*(h3::H3InputManager**)0x699530)
#define P_AdventureMgr						(*(h3::H3AdventureManager**)0x6992B8)
#define P_MovementMgr						(*(h3::H3MovementManager**)0x6992D4)
#define P_DialogHero						(*(h3::H3Hero**)0x698B70)
#define P_TurnTimer							(*(h3::H3TurnTimer**)(0x4AD194 + 1))
#define P_NewGameDlg						(*(h3::H3Dlg**)0x69FC44)
#define P_GamePalette						(*(h3::H3Palette565**)0x6AAD18)
#define P_PlayersPalette					(*(h3::H3Palette565**)0x6AAD10)
#define P_TinyFont							(*(h3::H3Font**)0x698A54)
#define P_SmallFont							(*(h3::H3Font**)0x698A58)
#define P_MediumFont						(*(h3::H3Font**)0x698A5C)
#define P_BigFont							(*(h3::H3Font**)0x698A60)
#define P_CalliFont							(*(h3::H3Font**)0x698A64)
#define P_BinaryTree						((h3::H3BinTreeList*)0x69E560)

// Constants C_ from Heroes3.exe

#define C_ButtonWav							(*(h3::H3WavFile**)0x694DF4)
#endif
	
}

#endif /* #define _H3DEFINES_HPP_ */