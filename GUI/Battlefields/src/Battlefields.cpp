#include "Battlefields.hpp"

using namespace h3;

BattlefieldsPlugin Battlefields;

BattlefieldsPlugin& BattlefieldsPlugin::GetPlugin()
{
    return Battlefields;
}

//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================

// * default background addresses
enum eCombatBackgrounds
{
    CmBkLava_pcx = 0x66D048, // Lava
    CmBkSub_pcx  = 0x66D058, // Subterranean
    CmBkRgh_pcx  = 0x66D064, // Rough
    CmBkSwmp_pcx = 0x66D070, // Swamp
    CmBkSnMt_pcx = 0x66D080, // Snow
    CmBkSnTr_pcx = 0x66D090, // Snow
    CmBkGrMt_pcx = 0x66D0A0, // Grass
    CmBkGrTr_pcx = 0x66D0B0, // Grass
    CmBkDes_pcx  = 0x66D0C0, // Sand
    CmBkDrTr_pcx = 0x66D0CC, // Dirt
    CmBkDrMt_pcx = 0x66D0DC, // Dirt
    CmBkDrDd_pcx = 0x66D0EC, // Dirt
    CmBkMC_pcx   = 0x66D0FC, // Magic Clouds
    CmBkRK_pcx   = 0x66D108, // Rocklands
    CmBkFF_pcx   = 0x66D114, // Fiery Field
    CmBkLP_pcx   = 0x66D120, // Lucid Pools
    CmBkCF_pcx   = 0x66D12C, // Clover field
    CmBkEF_pcx   = 0x66D138, // Evil Fog
    CmBkHG_pcx   = 0x66D144, // Holy Grounds
    CmBkCur_pcx  = 0x66D150, // Cursed ground
    CmBkMag_pcx  = 0x66D15C, // Magic Plains
    CmBkBch_pcx  = 0x66FF40, // Coast
    CmBkDeck_pcx = 0x66FF4C, // Land vs Boat
    CmBkBoat_pcx = 0x66FF5C, // Boat v Boat
};

// * index value of terrains used here
enum eTerrainIndex
{
    TI_LAVA,
    TI_SUBTERRA,
    TI_ROUGH,
    TI_SWAMP,
    TI_SNOW,
    TI_GRASS,
    TI_DESERT,
    TI_DIRT,
    TI_CLOUDS,
    TI_ROCKLANDS,
    TI_FIERY,
    TI_LUCID,
    TI_CLOVER,
    TI_EVILFOG,
    TI_HOLY,
    TI_CURSED,
    TI_MAGIC,
    TI_COAST,
    TI_DECK,
    TI_BOAT,
};

bool BattlefieldsPlugin::ReadIni()
{
    H3SEHandler seh;
    try
    {
        H3Ini ini;
        if (!ini.Open("Battlefields.ini"))
            return false;

        auto options = ini["options"];
        if (options == ini.end())
            return false;

        // * By default, we will use original backgrounds
        m_minScene = 1 - options["default"]->GetBool(true);

        // * load ini data to $CustomScenes
        for (UINT i = 0; i < SCENE_COUNT; i++)
            m_customScenes[i].count = options[m_customScenes[i].name]->GetInteger(0);

        return true;
    }
    catch (const H3Exception& e)
    {
        e.ShowMessagebox();
    }
    return false;
}


//===================================================================================
//
//                             HOOKS
//
//===================================================================================

int BattlefieldsPlugin::NewBattleGrounds(HookContext& c)
{
    INT scene_id;

    using cb = eCombatBackgrounds;
    using ti = eTerrainIndex;

    // * extract scene type
    switch (c.eax)
    {
    case cb::CmBkLava_pcx:
        scene_id = ti::TI_LAVA;
        break;
    case cb::CmBkSub_pcx:
        scene_id = ti::TI_SUBTERRA;
        break;
    case cb::CmBkRgh_pcx:
        scene_id = ti::TI_ROUGH;
        break;
    case cb::CmBkSwmp_pcx:
        scene_id = ti::TI_SWAMP;
        break;
    case cb::CmBkSnMt_pcx:
    case cb::CmBkSnTr_pcx:
        scene_id = ti::TI_SNOW;
        break;
    case cb::CmBkGrMt_pcx:
    case cb::CmBkGrTr_pcx:
        scene_id = ti::TI_GRASS;
        break;
    case cb::CmBkDes_pcx:
        scene_id = ti::TI_DESERT;
        break;
    case cb::CmBkDrTr_pcx:
    case cb::CmBkDrMt_pcx:
    case cb::CmBkDrDd_pcx:
        scene_id = ti::TI_DIRT;
        break;
    case cb::CmBkMC_pcx:
        scene_id = ti::TI_CLOUDS;
        break;
    case cb::CmBkRK_pcx:
        scene_id = ti::TI_ROCKLANDS;
        break;
    case cb::CmBkFF_pcx:
        scene_id = ti::TI_FIERY;
        break;
    case cb::CmBkLP_pcx:
        scene_id = ti::TI_LUCID;
        break;
    case cb::CmBkCF_pcx:
        scene_id = ti::TI_CLOVER;
        break;
    case cb::CmBkEF_pcx:
        scene_id = ti::TI_EVILFOG;
        break;
    case cb::CmBkHG_pcx:
        scene_id = ti::TI_HOLY;
        break;
    case cb::CmBkCur_pcx:
        scene_id = ti::TI_CURSED;
        break;
    case cb::CmBkMag_pcx:
        scene_id = ti::TI_MAGIC;
        break;
    case cb::CmBkBch_pcx:
        scene_id = ti::TI_COAST;
        break;
    case cb::CmBkDeck_pcx:
        scene_id = ti::TI_DECK;
        break;
    case cb::CmBkBoat_pcx:
        scene_id = ti::TI_BOAT;
        break;
    default:
        return EXEC_DEFAULT;
    }

    // * only trigger if there is a custom background
    if (INT max_scene = m_customScenes[scene_id].count)
    {
        // * pick a random scene (or not, depends on user choice)
        INT rand_scene = H3Random::RandBetween(m_minScene, max_scene);
        // * the scene is not default
        if (rand_scene)
        {
            F_sprintfbuffer(m_buffer, "%s%02d.pcx", m_customScenes[scene_id].name, rand_scene);
            c.Eax(m_buffer);
        }
    }

    return EXEC_DEFAULT;
}

_LHF_(NewBattleGrounds)
{
    return Battlefields.NewBattleGrounds(*c);
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void BattlefieldsPlugin::Start()
{
    if (!ReadIni())
        return;

    H3Random::SetRandomSeed();
    Hook(0x463833_h3,::NewBattleGrounds);
}