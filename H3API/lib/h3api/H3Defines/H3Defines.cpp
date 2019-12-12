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

#include "H3Defines.hpp"

namespace h3
{
	
	_H3API_ LPCSTR h3_SecondarySkillLevel(INT level)
	{
		return StrAt(0x6A75D4 + 4 * level);
	}
	_H3API_ LPCSTR h3_ObjectName(INT id)
	{
		return StrAt(0x6A7A54 + 4 * id);
	}
	_H3API_ LPCSTR h3_MineNames(INT type)
	{
		return StrAt(0x6A7538 + 4 * type);
	}
	_H3API_ LPCSTR h3_TentColors(INT type)
	{
		return StrAt(0x6A7588 + 4 * type);
	}
	_H3API_ LPCSTR h3_TerrainName(INT type)
	{
		return StrAt(0x6A5EEC + 4 * type);
	}
	_H3API_ LPCSTR h3_ResourceName(INT type)
	{
		return StrAt(0x6A5ECC + 4 * type);
	}
	_H3API_ LPCSTR h3_RandomSignText(INT type)
	{
		return StrAt(0x696CC4 + 4 * type);
	}
	_H3API_ LPCSTR h3_PlayerColor(INT type)
	{
		return StrAt(0x6A7E60 + 4 * type);
	}
	_H3API_ LPCSTR h3_DwellingNames1(INT type)
	{
		return StrAt(0x69154C + 4 * type);
	}
	_H3API_ LPCSTR h3_DwellingNames4(INT type)
	{
		return StrAt(0x6913A4 + 4 * type);
	}
	_H3API_ H3SpecialBuildingCosts& h3_SpecialBuildingCosts(int town)
	{
		return (*(H3SpecialBuildingCosts**)(0x5C1539 + 3))[town];
	}
	_H3API_ H3DwellingBuildingCosts& h3_DwellingBuildingCosts(int town)
	{
		return (*(H3DwellingBuildingCosts**)(0x5C1566 + 3))[town];
	}
	_H3API_ H3SecondarySkillInfo& h3_SecondarySkillsInfo(int skill)
	{
		return (*(H3SecondarySkillInfo**)(0x67DCF0))[skill];
	}
	_H3API_ H3GlobalObjectSettings& P_ObjectSettings(int id)
	{
		return (*(H3GlobalObjectSettings**)0x660428)[id];
	}
	_H3API_ H3Spell& P_Spell(int id)
	{
		return (*(H3Spell**)0x687FA8)[id];
	}
	_H3API_ H3CreatureBankSetup& P_CreatureBankTable(int id)
	{
		return (*(H3CreatureBankSetup**)(0x47A3C1 + 1))[id];
	}
	_H3API_ H3ValidCatapultTargets& P_ValidCatapultTargets(int id)
	{
		return (*(H3ValidCatapultTargets**)(0x4929DD + 3))[id];
	}
	_H3API_ H3ArtifactSetup& P_Artifacts(int id)
	{
		return (*(H3ArtifactSetup**)0x660B68)[id];
	}
	_H3API_ H3CreatureInformation& P_Creatures(int id)
	{
		return (*(H3CreatureInformation**)0x6747B0)[id];
	}
	_H3API_ H3ObstacleInfo& P_DefObstacleInfo(int id)
	{
		return (*(H3ObstacleInfo**)0x465C21)[id];
	}
	_H3API_ H3HeroInfo& P_HeroInfo(int id)
	{
		return (*(H3HeroInfo**)0x67DCE8)[id];
	}
	_H3API_ H3HeroSpecialty & P_HeroSpecialty(int id)
	{
		return (*(H3HeroSpecialty**)(0x4B8AF1 + 1))[id];
	}

#ifdef _H3API_DONT_USE_MACROS_
	_H3API_ H3String & h3_DataPath()
	{
		return *(H3String*)0x69E528;
	}

	_H3API_ HWND h3_HWND()
	{
		return *(HWND*)0x699650;
	}

	_H3API_ HMODULE h3_Instance()
	{
		return *(HMODULE*)0x699604;
	}

	_H3API_ UINT h3_ColorMode()
	{
		return PtrAt(0x694DB0);
	}

	_H3API_ PCHAR h3_SaveName()
	{
		return PCHAR(0x69FC88);
	}

	_H3API_ INT h3_ArtifactCount()
	{
		return IntAt(0x44D1A8 + 2);
	}

	_H3API_ INT h3_CreatureCount()
	{
		return IntAt(0x5C8046 + 1);
	}

	_H3API_ INT h3_HeroCount()
	{
		return IntAt(0x4BD144 + 1);
	}

	_H3API_ UINT8 h3_TownCount()
	{
		return ByteAt(0x5452D0 + 2);
	}

	_H3API_ UINT8 h3_SpellCount()
	{
		return ByteAt(0x4A2741 + 2);
	}

	_H3API_ INT gameMaxWidth()
	{
		return IntAt(0x415AAB + 2);
	}

	_H3API_ INT gameMaxHeight()
	{
		return IntAt(0x415AC1 + 2);
	}

	_H3API_ INT h3_CurrentPlayerID()
	{
		return IntAt(0x69CCF4);
	}

	_H3API_ INT h3_CurrentAnimationSpeed()
	{
		return IntAt(0x69883C);
	}

	_H3API_ BOOL h3_IsCampaignGame()
	{
		return IntAt(0x69779C) != 0;
	}

	_H3API_ BYTE h3_HeroRetreated()
	{
		return ByteAt(0x6985F3);
	}

	_H3API_ BYTE h3_HeroSurrendered()
	{
		return ByteAt(0x697794);
	}

	_H3API_ BYTE h3_AutoSolo()
	{
		return ByteAt(0x691259);
	}

	_H3API_ INT h3_HumanID()
	{
		return IntAt(0x6995A4);
	}

	_H3API_ BYTE h3_ActivePlayerBitset()
	{
		return ByteAt(0x69CD10);
	}

	_H3API_ H3Player & h3_ActivePlayer()
	{
		return **(H3Player**)0x69CCFC;
	}

	_H3API_ H3QuestText & h3_QuestsText()
	{
		return *(H3QuestText*)0x69E788;
	}

	_H3API_ H3QuestText & h3_SeersText()
	{
		return *(H3QuestText*)0x69F148;
	}

	_H3API_ H3AnimationSpeed & h3_AnimationSpeed()
	{
		return *(H3AnimationSpeed*)0x63CF7C;
	}

	_H3API_ H3Vector<INT>& h3_BattleShadowHexes()
	{
		return *(H3Vector<INT>*)0x696A08;
	}

	_H3API_ H3TownDependencies & h3_TownDependencies()
	{
		return (**(H3TownDependencies**)(0x5D6015 + 3));
	}

	_H3API_ H3NeutralBuildingCosts & h3_NeutralBuildingCosts()
	{
		return (**(H3NeutralBuildingCosts**)(0x5C1509 + 3));
	}

	_H3API_ INT SPEED_BONUS_BOOTS()
	{
		return IntAt(0x698B50);
	}

	_H3API_ INT SPEED_BONUS_GLOVES()
	{
		return IntAt(0x698B4C);
	}

	_H3API_ INT WATER_BONUS_NECKLACE()
	{
		return IntAt(0x698B54);
	}

	_H3API_ INT WATER_BONUS_SEA_CAPTAIN()
	{
		return IntAt(0x698B5C);
	}

	_H3API_ INT SPEED_BONUS_STABLES()
	{
		return IntAt(0x698AE4);
	}

	_H3API_ INT WATER_BONUS_LIGHTHOUSE()
	{
		return WATER_BONUS_SEA_CAPTAIN();
	}

	_H3API_ H3ColumnTextFile & P_GeneralText()
	{
		return (**(H3ColumnTextFile**)0x6A5DC4);
	}

	_H3API_ H3MouseManager & P_MouseMgr()
	{
		return (**(H3MouseManager**)0x6992B0);
	}

	_H3API_ H3WindowManager & P_WindowMgr()
	{
		return (**(H3WindowManager**)0x6992D0);
	}

	_H3API_ H3Executive & P_Executive()
	{
		return (**(H3Executive**)0x699550);
	}

	_H3API_ H3Main & P_Main()
	{
		return (**(H3Main**)0x699538);
	}

	_H3API_ H3CombatManager & P_CombatMgr()
	{
		return (**(H3CombatManager**)0x699420);
	}

	_H3API_ H3TownManager & P_TownMgr()
	{
		return (**(H3TownManager**)0x69954C);
	}

	_H3API_ H3SoundManager & P_SoundMgr()
	{
		return (**(H3SoundManager**)0x699414);
	}

	_H3API_ H3InputManager & P_InputMgr()
	{
		return (**(H3InputManager**)0x699530);
	}

	_H3API_ H3AdventureManager & P_AdventureMgr()
	{
		return (**(H3AdventureManager**)0x6992B8);
	}

	_H3API_ H3MovementManager & P_MovementMgr()
	{
		return (**(H3MovementManager**)0x6992D4);
	}

	_H3API_ H3Hero & P_DialogHero()
	{
		return (**(H3Hero**)0x698B70);
	}

	_H3API_ H3TurnTimer & P_TurnTimer()
	{
		return (**(H3TurnTimer**)(0x4AD194 + 1));
	}		

	_H3API_ H3Dlg* P_NewGameDlg()
	{
		return (*(H3Dlg**)0x69FC44);
	}

	_H3API_ H3Palette565 & P_GamePalette()
	{
		return (**(H3Palette565**)0x6AAD18);
	}

	_H3API_ H3Palette565 & P_PlayersPalette()
	{
		return (**(H3Palette565**)0x6AAD10);
	}

	_H3API_ H3Font & P_TinyFont()
	{
		return (**(H3Font**)0x698A54);
	}

	_H3API_ H3Font & P_SmallFont()
	{
		return (**(H3Font**)0x698A58);
	}

	_H3API_ H3Font & P_MediumFont()
	{
		return (**(H3Font**)0x698A5C);
	}

	_H3API_ H3Font & P_BigFont()
	{
		return (**(H3Font**)0x698A60);
	}

	_H3API_ H3Font & P_CalliFont()
	{
		return (**(H3Font**)0x698A64);
	}

	_H3API_ H3BinTreeList & P_BinaryTree()
	{
		return (*(H3BinTreeList*)0x69E560);
	}

	_H3API_ H3WavFile & C_ButtonWav()
	{
		return (**(H3WavFile**)0x694DF4);
	}
#endif	
}