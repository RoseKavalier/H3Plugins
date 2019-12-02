#ifndef _HOOKS_H_
#define _HOOKS_H_

#pragma once

#include "H3API.h"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

// * installs all hooks
void Hooks_init(PatcherInstance *pi);

#endif /* #define _HOOKS_H_ */