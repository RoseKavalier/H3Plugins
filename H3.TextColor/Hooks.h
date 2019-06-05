#ifndef _HOOKS_H_
#define _HOOKS_H_

#pragma once

#include "../Headers/H3API.h"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

// * initiates TextColor variables for use by other plugins
void Variables_init(Patcher *p);
// * installs all TextColor hooks
void Hooks_init(PatcherInstance *pi);

#endif /* #define _HOOKS_H_ */