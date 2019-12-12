# H3Plugins

Welcome to the home of the Heroes of Might and Magic III **H3API** library and plugins made using them. This repository will also be used to distribute the **SoD_SP** plugin which is coded using the same library.

## Description

**H3.LodTable**
>Modifies the LOD tables to provide room for additional LOD or PAC archives. By default, all folders of active HDmod plugins are browsed to add **.pac** or **.lod** game archives. You may also add archives from your own folders by using the HDmod variables created by the plugin. Included with SoD_SP.

**H3.TextColor**
>Adds over 100 colors to game text using a simple tag **{~color}**_your text here_**}**. Included with SoD_SP.

**H3.Battlefields**
>Adds custom battlefield backgrounds when fighting on the adventure map. Requires **H3.LodTable** plugin.

**H3.ShiftToggle**
>When the Shift key is held on the adventure map, the active hero ignores any left mouse clicks.

**H3.CombatAnimation**
>Cycles through combat creatures' standing animation frames instead of being idle. Included with SoD_SP.

**H3.ImageLoader**
>Loads image from given directory as H3LoadedPcx16*.
*Supported formats*: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC thanks to [stb_image](https://github.com/nothings/stb)

**SoD_SP**
>Description is currently only available [here](https://docs.google.com/document/d/1JlQ6TC97d_Bb1g_sDRpxTvkKHtyXgZ3qORG5LJS8tp8/edit#).

## Download Releases

Releases are available [here](https://github.com/RoseKavalier/H3Plugins/releases).

## Obtaining and using the H3API library

A release for the library's contents might be updated from time to time, however your best bet is to clone the solution directly.
See [here](https://github.com/RoseKavalier/H3Plugins/tree/master/H3API/lib) for more information on using H3API.

The H3API headers were successfully tested using the 2008, 2013, 2015, 2017 and 2019 versions of MSVC.
You may freely use and distribute the headers, however it would be nice of you to leave the disclaimers intact.

## Build Instructions

All necessary files for building using _Visual Studio_ are available in the repository. Upon cloning the directory, you should be able to build the included projects yourself. The one exception being the very next topic... 

## SoD_SP Plugin

![](https://github.com/RoseKavalier/H3Plugins/blob/master/Images/SODSP.png)

In the spirit of transparency and contributing to the Heroes 3 modding community, I am releasing portions of the SoD_SP source code. You will not be able to build it with the released files and you will most likely see missing files, definitions and functions when inspecting them.

#### Quick SoD_SP F.A.Q.
**So why not all of the code?**
>SoD_SP is still an ongoing project and I would like to maintain control on some of its aspects. Over time, more should be made public and existing code will be updated periodically.

**Can I use the available code?**
>The released code may be freely used in your own plugins, although beware the potential conflicts with SoD_SP.

**What about using non-public code?**
>You can always try to make your case and convince me to make these public, or to release them in a separate plugin - similar to *H3.TextColor* or *H3.LodTable* which were originally meant to be a part of SoD_SP. Keep in mind that SoD_SP is specifically intended to be available as a single player plugin only and some elements may not be able to be similarly separated.

## Help

Got issues? Suggestions? Head over to the [Issues](https://github.com/RoseKavalier/H3Plugins/issues) tab and let them be known.

## Disclaimer

This software is not in any way official and is not endorsed by anyone.
Heroes, Might and Magic, Heroes of Might and Magic, Ubisoft and the Ubisoft logo are trademarks of Ubisoft Entertainment in the U.S. and/or other countries.
