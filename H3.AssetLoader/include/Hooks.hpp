#ifndef _HOOKS_HPP_
#define _HOOKS_HPP_

#define _H3API_PLUGINS_
#include "H3API.hpp"

// * Global Patcher
extern Patcher *_P;
// * Global Patcher Instance
extern PatcherInstance *_PI;

extern h3::H3String AssetLoaderError;
extern LPCSTR defPath;
extern LoHook* DefHook;

void hooks_init(PatcherInstance* pi);

extern "C" __declspec(dllexport) h3::H3Plugin::AssetLoader::H3AssetLoader* GetAssetLoader_();

#endif