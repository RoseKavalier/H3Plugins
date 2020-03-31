#ifndef _HOOKS_HPP_
#define _HOOKS_HPP_

#include "patcher_x86.hpp"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

void hooks_init(PatcherInstance* pi);

#endif