#include "Ini.h"
#include "Hooks.h"
#include <H3API.hpp>

// * returns 0 if failed
int Read_Ini()
{
	h3::H3SEHandler seh;
	try
	{
		h3::H3Ini ini;
		if (!ini.Open("Battlefields.ini"))
			return 0;

		auto options = ini["options"];
		if (options == ini.end())
			return 0;

		// * By default, we will use original backgrounds
		minScene = 1 - options["default"]->GetBool(true);

		// * load ini data to $CustomScenes
		for (UINT i = 0; i < SCENE_COUNT; i++)
			CustomScenes[i].count = options[CustomScenes[i].name]->GetInteger(0);

		return 1;
	}
	catch (h3::H3Exception& e)
	{
		e.ShowMessagebox();
	}
	return 0;
}