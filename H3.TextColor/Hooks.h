#ifndef _HOOKS_H_
#define _HOOKS_H_

#pragma once

#define _H3API_PLUGINS_
#include "../Headers/H3API.h"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

// * installs all TextColor hooks
void Hooks_init(PatcherInstance *pi);

extern "C" __declspec(dllexport) H3Plugin::TextColor::H3TextColorInformation *GetTextColor_();

#endif /* #define _HOOKS_H_ */