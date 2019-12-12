#ifndef _HOOKS_H_
#define _HOOKS_H_

#pragma once

#define _H3API_PATCHER_X86_
#include "H3API.hpp"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

// * installs all hooks
void Hooks_init(PatcherInstance *pi);

#endif /* #define _HOOKS_H_ */