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

#ifndef _H3DEFINES_HPP_
#define _H3DEFINES_HPP_

#include "../H3_Base.hpp"
#include "../H3_BinaryItems.hpp"
#include "../H3_Dialogs.hpp"
#include "../H3_String.hpp"
#include "../H3_Structures.hpp"

namespace h3
{
	namespace H3Internal
	{
		typedef H3DataPointer<H3AnimationSpeed,             0x63CF7C,     false>  H3AnimationSpeed_ptr;
		typedef H3DataPointer<H3String,                     0x69E528,     false>  H3DataPath_ptr;
		typedef H3DataPointer<H3ResourceManager,            0x69E560,     false>  H3ResourceManager_ptr;
		typedef H3DataPointer<H3Vector<INT>,                0x696A08,     false>  H3BattleShadowHexes_ptr;
		typedef H3DataPointer<H3QuestText,                  0x69E788,     false>  H3QuestsText_ptr;
		typedef H3DataPointer<H3QuestText,                  0x69F148,     false>  H3SeersText_ptr;
		typedef H3DataPointer<H3SpellbookText,              0x6A5338,     false>  H3SpellbookText_ptr;
		typedef H3DataPointer<H3Player,                     0x69CCFC,     true >  H3ActivePlayer_ptr;
		typedef H3DataPointer<H3TextFile,                   0x6A5DC4,     true >  H3GeneralText_ptr;
		typedef H3DataPointer<H3TextFile,                   0x696A68,     true >  H3AdveventText_ptr;
		typedef H3DataPointer<H3MouseManager,               0x6992B0,     true >  H3MouseMgr_ptr;
		typedef H3DataPointer<H3WindowManager,              0x6992D0,     true >  H3WindowMgr_ptr;
		typedef H3DataPointer<H3ExecutiveMgr,               0x699550,     true >  H3Executive_ptr;
		typedef H3DataPointer<H3Main,                       0x699538,     true >  H3Main_ptr;
		typedef H3DataPointer<H3CombatManager,              0x699420,     true >  H3CombatMgr_ptr;
		typedef H3DataPointer<H3TownManager,                0x69954C,     true >  H3TownMgr_ptr;
		typedef H3DataPointer<H3SoundManager,               0x699414,     true >  H3SoundMgr_ptr;
		typedef H3DataPointer<H3InputManager,               0x699530,     true >  H3InputMgr_ptr;
		typedef H3DataPointer<H3AdventureManager,           0x6992B8,     true >  H3AdventureMgr_ptr;
		typedef H3DataPointer<H3MovementManager,            0x6992D4,     true >  H3MovementMgr_ptr;
		typedef H3DataPointer<H3Hero,                       0x698B70,     true >  H3DialogHero_ptr;
		typedef H3DataPointer<H3BaseDlg,                    0x694FE0,     true >  H3BattleOptionsDlg_ptr;
		typedef H3DataPointer<H3BaseDlg,                    0x69FC44,     true >  H3NewGameDlg_ptr;
		typedef H3DataPointer<H3Palette565,                 0x6AAD18,     true >  H3GamePalette_ptr;
		typedef H3DataPointer<H3Palette565,                 0x6AAD10,     true >  H3PlayersPalette_ptr;
		typedef H3DataPointer<H3Font,                       0x698A54,     true >  H3TinyFont_ptr;
		typedef H3DataPointer<H3Font,                       0x698A58,     true >  H3SmallFont_ptr;
		typedef H3DataPointer<H3Font,                       0x698A5C,     true >  H3MediumFont_ptr;
		typedef H3DataPointer<H3Font,                       0x698A60,     true >  H3BigFont_ptr;
		typedef H3DataPointer<H3Font,                       0x698A64,     true >  H3CalliFont_ptr;
		typedef H3DataPointer<H3WavFile,                    0x694DF4,     true >  H3ButtonWav_ptr;
		typedef H3DataPointer<H3TurnTimer,                  0x4AD194 + 1, true >  H3TurnTimer_ptr;
		typedef H3DataPointer<H3TownDependencies,           0x5D6015 + 3, true >  H3TownDependencies_ptr;

		typedef H3DataArrayPointer<H3SpecialBuildingCosts,  0x5C1539 + 3, true > H3SpecialBuildingCosts_ptr;
		typedef H3DataArrayPointer<H3DwellingBuildingCosts, 0x5C1566 + 3, true > H3DwellingBuildingCosts_ptr;
		typedef H3DataArrayPointer<H3SecondarySkillInfo,    0x67DCF0,     true > H3SecondarySkillsInfo_ptr;
		typedef H3DataArrayPointer<H3GlobalObjectSettings,  0x660428,     true > H3ObjectSettings_ptr;
		typedef H3DataArrayPointer<H3Spell,                 0x687FA8,     true > H3Spell_ptr;
		typedef H3DataArrayPointer<H3CreatureBankSetup,     0x47A3C1 + 1, true > H3CreatureBankTable_ptr;
		typedef H3DataArrayPointer<H3ValidCatapultTargets,  0x4929DD + 3, true > H3ValidCatapultTargets_ptr;
		typedef H3DataArrayPointer<H3ArtifactSetup,         0x660B68,     true > H3Artifacts_ptr;
		typedef H3DataArrayPointer<H3CreatureInformation,   0x6747B0,     true > H3Creatures_ptr;
		typedef H3DataArrayPointer<H3ObstacleInfo,          0x465C21,     true > H3DefObstacleInfo_ptr;
		typedef H3DataArrayPointer<H3HeroInfo,              0x67DCE8,     true > H3HeroInfo_ptr;
		typedef H3DataArrayPointer<H3HeroSpecialty,         0x4B8AF1 + 1, true > H3HeroSpecialty_ptr;
		typedef H3DataArrayPointer<H3TownCreatureTypes,     0x47AB00 + 3, true > H3TownCreatureTypes_ptr;

		typedef H3PrimitivePointer<HWND,                    0x699650,     false> H3Hwnd_ptr;
		typedef H3PrimitivePointer<HMODULE,                 0x699604,     false> H3Module_ptr;
		typedef H3PrimitivePointer<HINSTANCE,               0x699604,     false> H3Instance_ptr;
		typedef H3PrimitivePointer<UINT,                    0x69CCF4,     false> H3CurrentPlayerID_ptr;
		typedef H3PrimitivePointer<UINT,                    0x69883C,     false> H3CurrentAnimationSpeed_ptr;
		typedef H3PrimitivePointer<UINT,                    0x69883C,     false> H3CurrentAnimationSpeed_ptr;
		typedef H3PrimitivePointer<UINT,                    0x698B50,     false> H3BootsOfSpeedBonus_ptr;
		typedef H3PrimitivePointer<UINT,                    0x698B4C,     false> H3EquestriansGlovesBonus_ptr;
		typedef H3PrimitivePointer<UINT,                    0x698B54,     false> H3NecklaceOceanGuidanceBonus_ptr;
		typedef H3PrimitivePointer<UINT,                    0x698B5C,     false> H3SeaCaptainsHatBonus_ptr;
		typedef H3PrimitivePointer<UINT,                    0x698AE4,     false> H3StablesBonus_ptr;
		typedef H3PrimitivePointer<UINT,                    0x6995A4,     false> H3HumanID_ptr;
		typedef H3PrimitivePointer<UINT,                    0x6783C8,     false> H3MapSize_ptr;
		typedef H3PrimitivePointer<UINT,                    0x694DB0,     false> H3GreenMask_ptr;
		typedef H3PrimitivePointer<UINT,                    0x694DB4,     false> H3BlueMask_ptr;
		typedef H3PrimitivePointer<UINT,                    0x694DB8,     false> H3RedMask_ptr;
		typedef H3PrimitivePointer<BOOL,                    0x69779C,     false> H3IsCampaignGame_ptr;
		typedef H3PrimitivePointer<BOOL8,                   0x6985F3,     false> H3HeroRetreated_ptr;
		typedef H3PrimitivePointer<BOOL8,                   0x697794,     false> H3HeroSurrendered_ptr;
		typedef H3PrimitivePointer<BOOL8,                   0x691259,     false> H3AutoSolo_ptr;
		typedef H3PrimitivePointer<BYTE,                    0x69CD10,     false> H3ActivePlayerBitset_ptr;
		typedef H3PrimitivePointer<BYTE,                    0x4A2741 + 2, false> H3SpellCount_ptr;
		typedef H3PrimitivePointer<BYTE,                    0x5FA228 + 3, false> H3BitMode_ptr;
		typedef H3PrimitivePointer<UINT,                    0x44D1A8 + 2, false> H3ArtifactCount_ptr;
		typedef H3PrimitivePointer<UINT,                    0x44D1A8 + 2, false> H3ArtifactCount_ptr;
		typedef H3PrimitivePointer<UINT,                    0x5C8046 + 1, false> H3CreatureCount_ptr;
		typedef H3PrimitivePointer<UINT,                    0x4BD144 + 1, false> H3HeroCount_ptr;
		typedef H3PrimitivePointer<UINT,                    0x5452D0 + 2, false> H3TownCount_ptr;
		typedef H3PrimitivePointer<UINT,                    0x415AAB + 2, false> H3TextDlgMaxWidth_ptr;
		typedef H3PrimitivePointer<UINT,                    0x415AC1 + 2, false> H3TextDlgMaxHeight_ptr;
		typedef H3PrimitivePointer<UINT,                    0x403400 + 1, false> H3GameWidth_ptr;
		typedef H3PrimitivePointer<UINT,                    0x4033FB + 1, false> H3GameHeight_ptr;

		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A75D4,     false> H3SecondarySkillLevel_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A53F8,     false> H3PrimarySkillName_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A7A54,     false> H3ObjectName_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A7538,     false> H3MineNames_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A7588,     false> H3TentColors_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A755C,     false> H3CastleName_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A5EEC,     false> H3TerrainName_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A5ECC,     false> H3ResourceName_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x696CC4,     false> H3RandomSignText_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6A7E60,     false> H3PlayerColor_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x69154C,     false> H3DwellingNames1_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x6913A4,     false> H3DwellingNames4_ptr;
		typedef H3PrimitiveArrayPointer<LPCSTR,             0x4D92B7 + 3, true > H3HeroDefaultBiography_ptr;
	}


#ifdef _H3API_DONT_USE_MACROS_

	typedef H3Internal::H3Hwnd_ptr                       P_HWND;
	typedef H3Internal::H3ArtifactCount_ptr              P_ArtifactCount;
	typedef H3Internal::H3CreatureCount_ptr              P_CreatureCount;
	typedef H3Internal::H3HeroCount_ptr                  P_HeroCount;
	typedef H3Internal::H3TownCount_ptr                  P_TownCount;
	typedef H3Internal::H3SpellCount_ptr                 P_SpellCount;
	typedef H3Internal::H3TextDlgMaxWidth_ptr            P_TextDlgMaxWidth;
	typedef H3Internal::H3TextDlgMaxHeight_ptr           P_TextDlgMaxHeight;
	typedef H3Internal::H3CurrentPlayerID_ptr            P_CurrentPlayerID;
	typedef H3Internal::H3CurrentAnimationSpeed_ptr      P_CurrentAnimationSpeed;
	typedef H3Internal::H3IsCampaignGame_ptr             P_IsCampaignGame;
	typedef H3Internal::H3Instance_ptr                   P_Instance;
	typedef H3Internal::H3Module_ptr                     P_Module;
	typedef H3Internal::H3BootsOfSpeedBonus_ptr          P_BootsOfSpeedBonus;
	typedef H3Internal::H3EquestriansGlovesBonus_ptr     P_EquestriansGlovesBonus;
	typedef H3Internal::H3NecklaceOceanGuidanceBonus_ptr P_NecklaceOceanGuidanceBonus;
	typedef H3Internal::H3SeaCaptainsHatBonus_ptr        P_SeaCaptainsHatBonus;
	typedef H3Internal::H3StablesBonus_ptr               P_StablesBonus;
	typedef H3Internal::H3SeaCaptainsHatBonus_ptr        P_LighthouseBonus;
	typedef H3Internal::H3HeroRetreated_ptr              P_HeroRetreated;
	typedef H3Internal::H3HeroSurrendered_ptr            P_HeroSurrendered;
	typedef H3Internal::H3AutoSolo_ptr                   P_AutoSolo;
	typedef H3Internal::H3HumanID_ptr                    P_HumanID;
	typedef H3Internal::H3MapSize_ptr                    P_MapSize;
	typedef H3Internal::H3GameWidth_ptr                  P_GameWidth;
	typedef H3Internal::H3GameHeight_ptr                 P_GameHeight;
	typedef H3Internal::H3ActivePlayerBitset_ptr         P_ActivePlayerBitset;
	typedef H3Internal::H3GreenMask_ptr                  P_GreenMask;
	typedef H3Internal::H3BlueMask_ptr                   P_BlueMask;
	typedef H3Internal::H3RedMask_ptr                    P_RedMask;
	typedef H3Internal::H3BitMode_ptr                    P_BitMode;

	typedef H3Internal::H3AnimationSpeed_ptr             P_AnimationSpeed;
	typedef H3Internal::H3DataPath_ptr                   P_DataPath;
	typedef H3Internal::H3ResourceManager_ptr            P_ResourceManager;
	typedef H3Internal::H3BattleShadowHexes_ptr          P_BattleShadowHexes;
	typedef H3Internal::H3QuestsText_ptr                 P_QuestsText;
	typedef H3Internal::H3SeersText_ptr                  P_SeersText;
	typedef H3Internal::H3ActivePlayer_ptr               P_ActivePlayer;
	typedef H3Internal::H3TownDependencies_ptr           P_TownDependencies;
	typedef H3Internal::H3GeneralText_ptr                P_GeneralText;
	typedef H3Internal::H3AdveventText_ptr               P_AdveventText;
	typedef H3Internal::H3MouseMgr_ptr                   P_MouseMgr;
	typedef H3Internal::H3WindowMgr_ptr                  P_WindowMgr;
	typedef H3Internal::H3Executive_ptr                  P_ExecutiveMgr;
	typedef H3Internal::H3Main_ptr                       P_Main;
	typedef H3Internal::H3CombatMgr_ptr                  P_CombatMgr;
	typedef H3Internal::H3TownMgr_ptr                    P_TownMgr;
	typedef H3Internal::H3SoundMgr_ptr                   P_SoundMgr;
	typedef H3Internal::H3InputMgr_ptr                   P_InputMgr;
	typedef H3Internal::H3AdventureMgr_ptr               P_AdventureMgr;
	typedef H3Internal::H3MovementMgr_ptr                P_MovementMgr;
	typedef H3Internal::H3DialogHero_ptr                 P_DialogHero;
	typedef H3Internal::H3BattleOptionsDlg_ptr           P_BattleOptionsDlg;
	typedef H3Internal::H3TurnTimer_ptr                  P_TurnTimer;
	typedef H3Internal::H3NewGameDlg_ptr                 P_NewGameDlg;
	typedef H3Internal::H3GamePalette_ptr                P_GamePalette;
	typedef H3Internal::H3PlayersPalette_ptr             P_PlayersPalette;
	typedef H3Internal::H3TinyFont_ptr                   P_TinyFont;
	typedef H3Internal::H3SmallFont_ptr                  P_SmallFont;
	typedef H3Internal::H3MediumFont_ptr                 P_MediumFont;
	typedef H3Internal::H3BigFont_ptr                    P_BigFont;
	typedef H3Internal::H3CalliFont_ptr                  P_CalliFont;
	typedef H3Internal::H3ButtonWav_ptr                  P_ButtonWav;
	typedef H3Internal::H3SpellbookText_ptr              P_SpellbookText;

	typedef H3Internal::H3SecondarySkillLevel_ptr        P_SecondarySkillLevel;
	typedef H3Internal::H3PrimarySkillName_ptr           P_PrimarySkillName;
	typedef H3Internal::H3ObjectName_ptr                 P_ObjectName;
	typedef H3Internal::H3MineNames_ptr                  P_MineNames;
	typedef H3Internal::H3TentColors_ptr                 P_TentColors;
	typedef H3Internal::H3CastleName_ptr                 P_CastleName;
	typedef H3Internal::H3TerrainName_ptr                P_TerrainName;
	typedef H3Internal::H3ResourceName_ptr               P_ResourceName;
	typedef H3Internal::H3RandomSignText_ptr             P_RandomSignText;
	typedef H3Internal::H3PlayerColor_ptr                P_PlayerColor;
	typedef H3Internal::H3DwellingNames1_ptr             P_DwellingNames1;
	typedef H3Internal::H3DwellingNames4_ptr             P_DwellingNames4;
	typedef H3Internal::H3HeroDefaultBiography_ptr       P_HeroDefaultBiography;

	typedef H3Internal::H3SpecialBuildingCosts_ptr       P_SpecialBuildingCosts;
	typedef H3Internal::H3DwellingBuildingCosts_ptr      P_DwellingBuildingCosts;
	typedef H3Internal::H3SecondarySkillsInfo_ptr        P_SecondarySkillsInfo;
	typedef H3Internal::H3ObjectSettings_ptr             P_ObjectSettings;
	typedef H3Internal::H3Spell_ptr                      P_Spell;
	typedef H3Internal::H3CreatureBankTable_ptr          P_CreatureBankTable;
	typedef H3Internal::H3ValidCatapultTargets_ptr       P_ValidCatapultTargets;
	typedef H3Internal::H3Artifacts_ptr                  P_Artifacts;
	typedef H3Internal::H3Creatures_ptr                  P_Creatures;
	typedef H3Internal::H3DefObstacleInfo_ptr            P_DefObstacleInfo;
	typedef H3Internal::H3HeroInfo_ptr                   P_HeroInfo;
	typedef H3Internal::H3HeroSpecialty_ptr              P_HeroSpecialty;
	typedef H3Internal::H3TownCreatureTypes_ptr          P_TownCreatureTypes;

#else

#define P_HWND                       h3::H3Internal::H3Hwnd_ptr()
#define P_ArtifactCount              h3::H3Internal::H3ArtifactCount_ptr()
#define P_CreatureCount              h3::H3Internal::H3CreatureCount_ptr()
#define P_HeroCount                  h3::H3Internal::H3HeroCount_ptr()
#define P_TownCount                  h3::H3Internal::H3TownCount_ptr()
#define P_SpellCount                 h3::H3Internal::H3SpellCount_ptr()
#define P_TextDlgMaxWidth            h3::H3Internal::H3TextDlgMaxWidth_ptr()
#define P_TextDlgMaxHeight           h3::H3Internal::H3TextDlgMaxHeight_ptr()
#define P_CurrentPlayerID            h3::H3Internal::H3CurrentPlayerID_ptr()
#define P_CurrentAnimationSpeed      h3::H3Internal::H3CurrentAnimationSpeed_ptr()
#define P_IsCampaignGame             h3::H3Internal::H3IsCampaignGame_ptr()
#define P_Instance                   h3::H3Internal::H3Instance_ptr()
#define P_Module                     h3::H3Internal::H3Module_ptr()
#define P_BootsOfSpeedBonus          h3::H3Internal::H3BootsOfSpeedBonus_ptr() // usually 600 mp
#define P_EquestriansGlovesBonus     h3::H3Internal::H3EquestriansGlovesBonus_ptr() // usually 300 mp
#define P_NecklaceOceanGuidanceBonus h3::H3Internal::H3NecklaceOceanGuidanceBonus_ptr() // usually 1000 mp
#define P_SeaCaptainsHatBonus        h3::H3Internal::H3SeaCaptainsHatBonus_ptr() // usually 500 mp
#define P_StablesBonus               h3::H3Internal::H3StablesBonus_ptr() // usually 400 mp
#define P_LighthouseBonus            h3::H3Internal::H3SeaCaptainsHatBonus_ptr() // same as sea_captain's hat bonus ~500
#define P_HeroRetreated              h3::H3Internal::H3HeroRetreated_ptr()
#define P_HeroSurrendered            h3::H3Internal::H3HeroSurrendered_ptr()
#define P_AutoSolo                   h3::H3Internal::H3AutoSolo_ptr()
#define P_HumanID                    h3::H3Internal::H3HumanID_ptr()
#define P_MapSize                    h3::H3Internal::H3MapSize_ptr()
#define P_GameWidth                  h3::H3Internal::H3GameWidth_ptr()
#define P_GameHeight                 h3::H3Internal::H3GameHeight_ptr()
#define P_ActivePlayerBitset         h3::H3Internal::H3ActivePlayerBitset_ptr()
#define P_GreenMask                  h3::H3Internal::H3GreenMask_ptr()
#define P_BlueMask                   h3::H3Internal::H3BlueMask_ptr()
#define P_RedMask                    h3::H3Internal::H3RedMask_ptr()
#define P_BitMode                    h3::H3Internal::H3BitMode_ptr()

#define P_AnimationSpeed             h3::H3Internal::H3AnimationSpeed_ptr()
#define P_DataPath                   h3::H3Internal::H3DataPath_ptr()
#define P_ResourceManager            h3::H3Internal::H3ResourceManager_ptr()
#define P_BattleShadowHexes          h3::H3Internal::H3BattleShadowHexes_ptr()
#define P_QuestsText                 h3::H3Internal::H3QuestsText_ptr()
#define P_SeersText                  h3::H3Internal::H3SeersText_ptr()
#define P_ActivePlayer               h3::H3Internal::H3ActivePlayer_ptr()
#define P_TownDependencies           h3::H3Internal::H3TownDependencies_ptr()
#define P_GeneralText                h3::H3Internal::H3GeneralText_ptr()
#define P_AdveventText               h3::H3Internal::H3AdveventText_ptr()
#define P_MouseMgr                   h3::H3Internal::H3MouseMgr_ptr()
#define P_WindowMgr                  h3::H3Internal::H3WindowMgr_ptr()
#define P_ExecutiveMgr               h3::H3Internal::H3Executive_ptr()
#define P_Main                       h3::H3Internal::H3Main_ptr()
#define P_CombatMgr                  h3::H3Internal::H3CombatMgr_ptr()
#define P_TownMgr                    h3::H3Internal::H3TownMgr_ptr()
#define P_SoundMgr                   h3::H3Internal::H3SoundMgr_ptr()
#define P_InputMgr                   h3::H3Internal::H3InputMgr_ptr()
#define P_AdventureMgr               h3::H3Internal::H3AdventureMgr_ptr()
#define P_MovementMgr                h3::H3Internal::H3MovementMgr_ptr()
#define P_DialogHero                 h3::H3Internal::H3DialogHero_ptr()
#define P_BattleOptionsDlg           h3::H3Internal::H3BattleOptionsDlg_ptr()
#define P_TurnTimer                  h3::H3Internal::H3TurnTimer_ptr()
#define P_NewGameDlg                 h3::H3Internal::H3NewGameDlg_ptr()
#define P_GamePalette                h3::H3Internal::H3GamePalette_ptr()
#define P_PlayersPalette             h3::H3Internal::H3PlayersPalette_ptr()
#define P_TinyFont                   h3::H3Internal::H3TinyFont_ptr()
#define P_SmallFont                  h3::H3Internal::H3SmallFont_ptr()
#define P_MediumFont                 h3::H3Internal::H3MediumFont_ptr()
#define P_BigFont                    h3::H3Internal::H3BigFont_ptr()
#define P_CalliFont                  h3::H3Internal::H3CalliFont_ptr()
#define P_ButtonWav                  h3::H3Internal::H3ButtonWav_ptr()
#define P_SpellbookText              h3::H3Internal::H3SpellbookText_ptr()

#define P_SecondarySkillLevel        h3::H3Internal::H3SecondarySkillLevel_ptr()
#define P_PrimarySkillName           h3::H3Internal::H3PrimarySkillName_ptr()
#define P_ObjectName                 h3::H3Internal::H3ObjectName_ptr()
#define P_MineNames                  h3::H3Internal::H3MineNames_ptr()
#define P_TentColors                 h3::H3Internal::H3TentColors_ptr()
#define P_CastleName                 h3::H3Internal::H3CastleName_ptr()
#define P_TerrainName                h3::H3Internal::H3TerrainName_ptr()
#define P_ResourceName               h3::H3Internal::H3ResourceName_ptr()
#define P_RandomSignText             h3::H3Internal::H3RandomSignText_ptr()
#define P_PlayerColor                h3::H3Internal::H3PlayerColor_ptr()
#define P_DwellingNames1             h3::H3Internal::H3DwellingNames1_ptr()
#define P_DwellingNames4             h3::H3Internal::H3DwellingNames4_ptr()
#define P_HeroDefaultBiography       h3::H3Internal::H3HeroDefaultBiography_ptr()

#define P_SpecialBuildingCosts       h3::H3Internal::H3SpecialBuildingCosts_ptr()
#define P_DwellingBuildingCosts      h3::H3Internal::H3DwellingBuildingCosts_ptr()
#define P_SecondarySkillsInfo        h3::H3Internal::H3SecondarySkillsInfo_ptr()
#define P_ObjectSettings             h3::H3Internal::H3ObjectSettings_ptr()
#define P_Spell                      h3::H3Internal::H3Spell_ptr()
#define P_CreatureBankTable          h3::H3Internal::H3CreatureBankTable_ptr()
#define P_ValidCatapultTargets       h3::H3Internal::H3ValidCatapultTargets_ptr()
#define P_Artifacts                  h3::H3Internal::H3Artifacts_ptr()
#define P_Creatures                  h3::H3Internal::H3Creatures_ptr()
#define P_DefObstacleInfo            h3::H3Internal::H3DefObstacleInfo_ptr()
#define P_HeroInfo                   h3::H3Internal::H3HeroInfo_ptr()
#define P_HeroSpecialty              h3::H3Internal::H3HeroSpecialty_ptr()
#define P_TownCreatureTypes          h3::H3Internal::H3TownCreatureTypes_ptr()

#endif
}

#endif /* #define _H3DEFINES_HPP_ */