#pragma once

#define _H3API_STD_CONVERSIONS_

#include <Plugin.hpp>
#include <H3API.hpp>
#include <ThirdParty/era.hpp>
#include <ThirdParty/json.hpp>

/**
 * Uncomment to show an error message when failing to link up with patcher_x86
 */
//#define SHOW_ERROR_MESSAGE_ON_FAIL

/**
 * @brief A derived Plugin that constructs itself
 */
class RMGDescriptionPlugin : public Plugin
{
public:
	RMGDescriptionPlugin() : Plugin()
	{
		Status status = Init("H3.RMGDescription");
		if (status == Status::Success)
			Start();
#ifdef SHOW_ERROR_MESSAGE_ON_FAIL
		else
			ShowError("H3.RMGDescription", status);
#endif
	}

private:
	void Start();

public:
	//======================================================================================
	//
	// Data or methods can be added here which can be accessed from anywhere using the plugin.
	//
	//======================================================================================

	int EraLocalization();
	int RMG_LocalizedDescription(HookContext& c);
	bool GetLocalizedText();

private:
	//======================================================================================
	//
	// Data or methods can be added here which can only be accessed from within the plugin.
	//
	//======================================================================================

	static constexpr LPCSTR keysEra[] =
	{
		"RMGDescription.map_creation",
		"RMGDescription.separator",
		"RMGDescription.original_map",
		"RMGDescription.first_expansion",
		"RMGDescription.third_expansion",
		"RMGDescription.water_none",
		"RMGDescription.water_normal",
		"RMGDescription.water_islands",
		"RMGDescription.is_human",
		"RMGDescription.town_choice",
	};

	static constexpr LPCSTR keys[] =
	{
		"map_creation",
		"separator",
		"original_map",
		"first_expansion",
		"second_expansion",
		"water_none",
		"water_normal",
		"water_islands",
		"is_human",
		"town_choice",
	};
	static constexpr size_t NumTextEntries = std::size(keys);

	struct RMGText
	{
		std::string mapCreation;
		std::string separator;
		std::string expansions[3];
		std::string waterContent[3];
		std::string isHuman;
		std::string townChoice;

		std::string& operator[](size_t index) { return reinterpret_cast<std::string*>(this)[index]; }

	}m_localizedText;
};