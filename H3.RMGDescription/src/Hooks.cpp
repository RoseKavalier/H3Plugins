#include "Hooks.hpp"
#include "H3API.hpp"
#include "ThirdParty/era.hpp"
#include "ThirdParty/json.hpp"

using namespace h3;


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Global variables
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

Patcher* _P;
PatcherInstance* _PI;

constexpr LPCSTR g_keysEra[] =
{
	"RMGDescription.map_creation",
	"RMGDescription.separator",
	"RMGDescription.original_map",
	"RMGDescription.first_expansion",
	"RMGDescription.second_expansion",
	"RMGDescription.water_none",
	"RMGDescription.water_normal",
	"RMGDescription.water_islands",
	"RMGDescription.is_human",
	"RMGDescription.town_choice",
};

constexpr LPCSTR g_keys[] =
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
constexpr size_t kNumTextEntries = std::size(g_keys);

struct RMGText
{
	union
	{
		struct
		{
			std::string mapCreation;
			std::string separator;
			std::string expansions[3];
			std::string waterContent[3];
			std::string isHuman;
			std::string townChoice;
		};
		struct
		{
			std::string entries[kNumTextEntries];
		};
	};

	std::string& operator[](size_t index) { return entries[index]; }

}g_localizedText;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Custom structures and functions
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

_LHF_(EraLocalization);

/**
 * @brief converts utf8 string to machine-locale ansi
 *
 * @param utf8 std::string of utf8 format to convert to ansi
 * @return std::string converted string
 */
std::string Utf8ToAnsi(const std::string& utf8)
{
	int nLength = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size() + 1, NULL, NULL);
	std::wstring unicode;
	unicode.resize(nLength);

	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size() + 1, &unicode[0], nLength);

	nLength = WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
	std::string ansi;
	ansi.resize(nLength);
	WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), -1, &ansi[0], nLength, NULL, NULL);
	return ansi;
}

/**
 * @brief Gets all localized text from json, or installs a later hook in the case of ERA
 *
 * @param pi patcher instance for ERA
 * @return bool whether all text was successfully acquired or hook installed
 */
bool GetLocalizedText(PatcherInstance* pi)
{
	H3SEHandler seh;
	try
	{
		H3Version game;
		if (game.era())
		{
			return nullptr != pi->WriteLoHook(0x4F80CE, EraLocalization);
		}
		else
		{
			H3String dir = H3Path::CurrentDirectory();
			H3File lang;
			if (lang.Open(dir.AppendA("Lang/RMGDescription.json").String()) && lang.ReadToBuffer())
			{
				auto json = nlohmann::json::parse(lang.begin(), lang.end());
				auto j = json.at("RMGDescription");
				for (auto i = 0; i < kNumTextEntries; ++i)
				{
					std::string utf8;
					j.at(g_keys[i]).get_to(utf8);
					g_localizedText[i] = Utf8ToAnsi(utf8);
				}
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
//	Hooks
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/**
 * @brief acquires text from ERA
 */
_LHF_(EraLocalization)
{
	era::ConnectEra(true);
	for (size_t i = 0; i < kNumTextEntries; ++i)
		g_localizedText[i] = era::GetTranslation(g_keysEra[i]);
	return EXEC_DEFAULT;
}

/**
 * @brief replaces random map generator's scenario information by localized version
 */
_LHF_(RMG_LocalizedDescription)
{
	auto rmg                 = reinterpret_cast<RMG_Main*>(c->esi);
	auto template_name       = reinterpret_cast<LPCSTR>(c->eax);
	auto map_size            = c->edx;
	auto num_levels          = c->ecx;
	auto text_buffer         = c->LocalStack<CHAR>(201);
	constexpr size_t max_len = 500 - 1;

	int number_human{ 0 };
	for (auto is_human : rmg->isHuman) // all players may be human, compute real number of humans
		if (is_human)
			++number_human;

	H3String new_desc;
	new_desc.Reserve(max_len);
	new_desc.Printf(g_localizedText.mapCreation.c_str(),
		template_name,
		rmg->randomSeed,
		map_size,
		num_levels,
		number_human,
		rmg->humanCount - number_human,
		g_localizedText.waterContent[rmg->waterAmount].c_str(),
		rmg->monsterStrength);

	new_desc += g_localizedText.separator;
	new_desc += g_localizedText.expansions[rmg->gameVersion];

	for (size_t i = 0; i < 8; ++i)
	{
		if (rmg->isHuman[i])
		{
			new_desc += g_localizedText.separator;
			new_desc += P_PlayerColor()[i];
			new_desc += g_localizedText.isHuman;
		}
		if (rmg->playerTown[i] != NH3Towns::eTownType::NEUTRAL)
		{
			new_desc += g_localizedText.separator;
			new_desc += P_PlayerColor()[i];
			new_desc += g_localizedText.townChoice;
			new_desc += P_CastleName()[rmg->playerTown[i]];
		}
	}
	F_memcpy(text_buffer, PVOID(new_desc.String()), std::min(new_desc.Length() + 1, max_len));
	text_buffer[max_len] = 0; // null terminate for safety
	c->return_address = 0x54A4FA;
	return NO_EXEC_DEFAULT;
}

void hooks_init(PatcherInstance* pi)
{
	if (GetLocalizedText(pi))
		pi->WriteLoHook(0x54A2B0, RMG_LocalizedDescription);
}