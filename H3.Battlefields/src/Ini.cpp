#include "Ini.h"
#include "Hooks.h"

// * returns 0 if failed
int Read_Ini()
{
	// * initiate reader
	INIReader reader("Battlefields.ini");

	// * if reader could not be opened, return failure
	if (reader.ParseError() < 0)
		return 0;

	// * By default, we will use original backgrounds
	minScene = 1 - reader.GetBoolean("options", "Default", TRUE);

	// * load ini data to $CustomScenes
	for (int i = 0; i < SCENE_COUNT; i++)
		CustomScenes[i].count = reader.GetInteger("options", CustomScenes[i].name, 0);

	return 1;
}