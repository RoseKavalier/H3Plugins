#ifndef _HOOKS_H_
#define _HOOKS_H_

#pragma once

#define _H3API_PATCHER_X86_
#include "H3API.hpp"

// * 20 valid scenes
constexpr UINT SCENE_COUNT = 20;

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

// * should default scenes be considered
// * when randomly selecting?
extern INT minScene;

// * simple struc to contain number of scenes
// * and prefix of custom background
struct H3CombatScenes
{
	INT32 count;
	PCHAR name;
};

// * structure to hold all custom data
extern H3CombatScenes CustomScenes[SCENE_COUNT];

// * installs all TextColor hooks
void Hooks_init(PatcherInstance *pi);


#endif /* #define _HOOKS_H_ */