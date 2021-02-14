#include "RMGDescription.hpp"

using namespace h3;

RMGDescriptionPlugin RMGDescription;

//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================

/**
 * @brief converts utf8 string to machine-locale ansi
 *
 * @param utf8 std::string of utf8 format to convert to ansi
 * @return std::string converted string
 */
std::string Utf8ToAnsi(const std::string& utf8, UINT code_page = CP_ACP)
{
	int nLength = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, NULL);
	std::wstring unicode;
	unicode.resize(nLength - 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &unicode[0], nLength);

	nLength = WideCharToMultiByte(code_page, 0, unicode.c_str(), -1, NULL, 0, NULL, NULL);
	std::string ansi;
	ansi.resize(nLength - 1);
	WideCharToMultiByte(code_page, 0, unicode.c_str(), -1, &ansi[0], nLength, NULL, NULL);
	return ansi;
}

//===================================================================================
//
//                             HOOKS
//
//===================================================================================

/**
 * @brief acquires text from ERA
 */
_LHF_(EraLocalization)
{
	return RMGDescription.EraLocalization();
}

/**
 * @brief replaces random map generator's scenario information by localized version
 */
_LHF_(RMG_LocalizedDescription)
{
	return RMGDescription.RMG_LocalizedDescription(*c);
}

bool RMGDescriptionPlugin::GetLocalizedText()
{
	H3SEHandler seh;
	try
	{
		H3Version game;
		if (game.era())
		{
			return nullptr != Hook(0x4F80CE, ::EraLocalization);
		}
		else
		{
			H3String dir = H3Path::CurrentDirectory().AppendA("Lang/RMGDescription.json");
			H3File lang;
			if (lang.Open(dir) && lang.ReadToBuffer())
			{
				auto json = nlohmann::json::parse(lang.begin(), lang.end());
				auto& j = json.at("RMGDescription");
				for (auto i = 0; i < NumTextEntries; ++i)
				{
					std::string utf8;
					j.at(keys[i]).get_to(utf8);
					m_localizedText[i] = Utf8ToAnsi(utf8, CP_ACP);
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

/**
 * @brief Instruct new game dialog to use complete map description instead of cut-off at 300 characters.
 *
 */
_LHF_(UseFullMapDescription)
{
	H3SEHandler seh;
	try
	{
		auto& desc = c->Ebx<H3SelectScenarioDialog*>()->CurrentMap().mapDescription;
		if (!desc.Empty()) // hdmod dir doesn't populate string
			c->Esi<LPCSTR>() = desc.String();
	}
	catch (...)
	{
		// just fail silently...
	}
	return EXEC_DEFAULT;
}

int RMGDescriptionPlugin::EraLocalization()
{
	era::ConnectEra(true);
	for (size_t i = 0; i < NumTextEntries; ++i)
		m_localizedText[i] = era::GetTranslation(keysEra[i]);
	return EXEC_DEFAULT;
}

int RMGDescriptionPlugin::RMG_LocalizedDescription(HookContext& c)
{
	auto rmg           = c.Esi<RMG_Main*>();
	auto template_name = c.Eax<LPCSTR>();
	auto map_size      = c.edx;
	auto num_levels    = c.ecx;
	auto text_buffer   = c.LocalStack<CHAR>(201);
	auto strm          = c.Ebx<H3ZStream*>();

	int number_human{ 0 };
	for (auto is_human : rmg->isHuman) // all players may be human, compute real number of humans
		if (is_human)
			++number_human;

	H3String new_desc;
	new_desc.Printf(m_localizedText.mapCreation.c_str(),
		template_name,
		rmg->randomSeed,
		map_size,
		num_levels,
		number_human,
		rmg->humanCount - number_human,
		m_localizedText.waterContent[rmg->waterAmount].c_str(),
		rmg->monsterStrength);
	new_desc.Reserve(500);

	new_desc += m_localizedText.separator;
	new_desc += m_localizedText.expansions[rmg->gameVersion];

	for (size_t i = 0; i < 8; ++i)
	{
		if (rmg->isHuman[i])
		{
			new_desc += m_localizedText.separator;
			new_desc += P_PlayerColor()[i];
			new_desc += m_localizedText.isHuman;
		}
		if (rmg->playerTown[i] != NH3Towns::eTownType::NEUTRAL)
		{
			new_desc += m_localizedText.separator;
			new_desc += P_PlayerColor()[i];
			new_desc += m_localizedText.townChoice;
			new_desc += P_CastleName()[rmg->playerTown[i]];
		}
	}

	strm->Write(new_desc);

	c.return_address = 0x54A539;
	return NO_EXEC_DEFAULT;
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void RMGDescriptionPlugin::Start()
{
	if (GetLocalizedText())
		Hook(0x54A2B0, ::RMG_LocalizedDescription);

	Hook(0x583AB8, ::UseFullMapDescription);
}
