#include "QwertzLayout.hpp"

using namespace h3;

QwertzLayoutPlugin QwertzLayout;

QwertzLayoutPlugin& QwertzLayoutPlugin::GetPlugin()
{
    return QwertzLayout;
}

//===================================================================================
//
//                 ADDITIONAL METHODS AND STRUCTURES
//
//===================================================================================


//===================================================================================
//
//                             HOOKS
//
//===================================================================================

_LHF_(RestoreMinusKey)
{
    constexpr int minus = '-';
    c->eax = minus;
    return EXEC_DEFAULT;
}

/**
 * @brief This member function is used to install all your hooks.
 * e.g. Hook(0x123456, MyHook);
 * writes a hook at 0x123456 to access MyHook (LoHook or H3NakedFunction, depending on MyHook)
 * e.g. Hook(0x123456, Call, Thiscall, MyHook);
 * writes a HiHook at 0x123456, on a CALL instruction with convention __thiscall, and default hook type EXTENDED_
 */
void QwertzLayoutPlugin::Start()
{
    WordPatch(0x4ECA0E + 1, 0xFFDF);
    WordPatch(0x4ECA23 + 7, 0x0040);
    WordPatch(0x4ECA6B + 7, 0x005A); // Z
    WordPatch(0x4ECA98 + 7, 0xFFFC);
    WordPatch(0x4ECAA1 + 7, 0x002B);
    WordPatch(0x4ECB0D + 7, 0xFFF6);
    WordPatch(0x4ECB16 + 7, 0xFFE4);
    WordPatch(0x4ECB31 + 7, 0x0023);
    WordPatch(0x4ECB3A + 7, 0x0079); // y
    WordPatch(0x4ECB8B + 7, 0x002D);
    Hook(0x4ECC48, RestoreMinusKey); // minus key was changed to 0xFFDF at 0x4ECA0E + 1
}
