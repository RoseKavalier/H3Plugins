#ifndef _HOOKS_H_
#define _HOOKS_H_

#pragma once

#include "../Headers/H3API.h"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

// * the number of LODs that can be loaded
#define LOD_COUNT 1000

// * default LoD values
#define h3_SoDLodTable 0x69D8A8
#define LodTableCheck PtrAt(0x55944C + 1)

// * new Lod table
extern H3Lod LodTable[LOD_COUNT];
// * the number of LODs existing, 8 by default
extern INT lastLod;

// * initiates LodTable variables
void Variables_init(Patcher *p);
// * installs all LodTable hooks
void Hooks_init(PatcherInstance *pi);

#endif /* #define _HOOKS_H_ */