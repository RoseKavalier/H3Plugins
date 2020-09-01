#include "Hooks.hpp"
#include "H3API.hpp"
#include "ThirdParty/era.hpp"
#include "ThirdParty/json.hpp"

using namespace h3;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

struct RMGText
{
	std::string mapCreation;
	std::string separator;
	std::string expansions[3];
	std::string waterContent[3];
	std::string isHuman;
	std::string townChoice;
}LocalizedText;

_LHF_(EraLocalization);

bool GetLocalizedText(PatcherInstance* pi)
{
	H3SEHandler seh;
	try
	{
		h3::H3Version game;
		if (game.era())
		{
			pi->WriteLoHook(0x4F80CE, EraLocalization);
		}
		else
		{
			H3String dir = H3Path::CurrentDirectory();
			H3File lang;
			if (lang.Open(dir.AppendA("Lang/RMGDescription.json").String()) && lang.ReadToBuffer())
			{
				auto json = nlohmann::json::parse(lang.begin(), lang.end());
				auto j = json.at("RMGDescription");
				j.at("map_creation").get_to(LocalizedText.mapCreation);
				j.at("separator").get_to(LocalizedText.separator);
				j.at("original_map").get_to(LocalizedText.expansions[0]);
				j.at("first_expansion").get_to(LocalizedText.expansions[1]);
				j.at("second_expansion").get_to(LocalizedText.expansions[2]);
				j.at("water_none").get_to(LocalizedText.waterContent[0]);
				j.at("water_normal").get_to(LocalizedText.waterContent[1]);
				j.at("water_islands").get_to(LocalizedText.waterContent[2]);
				j.at("is_human").get_to(LocalizedText.isHuman);
				j.at("town_choice").get_to(LocalizedText.townChoice);
			}
		}
	}
	catch (const std::exception& e)
	{
		H3Error::ShowError(e.what());
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher *_P;
PatcherInstance *_PI;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

_LHF_(EraLocalization)
{
	era::ConnectEra(true);
	LocalizedText.mapCreation     = era::GetTranslation("RMGDescription.map_creation", {});
	LocalizedText.separator       = era::GetTranslation("RMGDescription.separator", {});
	LocalizedText.expansions[0]   = era::GetTranslation("RMGDescription.original_map", {});
	LocalizedText.expansions[1]   = era::GetTranslation("RMGDescription.first_expansion", {});
	LocalizedText.expansions[2]   = era::GetTranslation("RMGDescription.third_expansion", {});
	LocalizedText.waterContent[0] = era::GetTranslation("RMGDescription.water_none", {});
	LocalizedText.waterContent[1] = era::GetTranslation("RMGDescription.water_normal", {});
	LocalizedText.waterContent[2] = era::GetTranslation("RMGDescription.water_islands", {});
	LocalizedText.isHuman         = era::GetTranslation("RMGDescription.is_human", {});
	LocalizedText.townChoice      = era::GetTranslation("RMGDescription.town_choice", {});
	return EXEC_DEFAULT;
}

_LHF_(RMG_LocalizedDescription)
{
	auto rmg = reinterpret_cast<RMG_Main*>(c->esi);
	auto template_name = reinterpret_cast<LPCSTR>(c->eax);
	auto map_size = c->edx;
	auto num_levels = c->ecx;
	auto text_buffer = c->LocalStack<CHAR>(201);

	int number_human{ 0 };
	for (auto is_human : rmg->isHuman)
		if (is_human)
			++number_human;

	H3String new_desc;
	new_desc.Reserve(500);
	new_desc.Printf(LocalizedText.mapCreation.c_str(),
		template_name,
		rmg->randomSeed,
		map_size,
		num_levels,
		number_human,
		rmg->humanCount - number_human,
		LocalizedText.waterContent[rmg->waterAmount].c_str(),
		rmg->monsterStrength);

	new_desc += LocalizedText.separator;
	new_desc += LocalizedText.expansions[rmg->gameVersion];

	for (size_t i = 0; i < 8; ++i)
	{
		if (rmg->isHuman[i])
		{
			new_desc += LocalizedText.separator;
			new_desc += P_PlayerColor()[i];
			new_desc += LocalizedText.isHuman;
		}
		if (rmg->playerTown[i] != NH3Towns::eTownType::NEUTRAL)
		{
			new_desc += LocalizedText.separator;
			new_desc += P_PlayerColor()[i];
			new_desc += LocalizedText.townChoice;
			new_desc += P_CastleName()[rmg->playerTown[i]];
		}
	}
	F_memcpy(text_buffer, PVOID(new_desc.String()), std::min(new_desc.Length() + 1, 500u));
	c->return_address = 0x54A4FA;
	return NO_EXEC_DEFAULT;
}

void hooks_init(PatcherInstance* pi)
{
	if (GetLocalizedText(pi))
		pi->WriteLoHook(0x54A2B0, RMG_LocalizedDescription);
}