**Note**
>The library is now stored within `namespace h3` to help in preventing conflicts. If you do not wish to type `h3::` every time you use H3API, add the `using namespace h3;` line to your code.

H3API Preprocessor Definitions Overview
---
To use these options, either add these preprocessor definitions to your project's preprocessor definitions, or `#define` them prior to including H3API.

|      Preprocessor option     	| Description                                     	|
|:----------------------------:	|-------------------------------------------------	|
|      \_H3API\_LIBRARY\_      	| tells the library that it should only include header files within your project<br>and that you will rely on the static library to access the library's implementation<br>by default the library is header-only. |
|     \_H3API\_OPERATORS\_     	| tells the library to replace the new, new[], delete and delete[] operators<br>by the game's own operators.<br>be mindful of hooking too early in the launch process when using this. |
|   \_H3API\_STD\_CONVERSIONS\_   	| allows conversion between the following formats<br>`std::string <<==>> h3::H3String`<br>`std::vector <<==>> h3::H3Vector` |
|   \_H3API\_STD\_VECTOR\_   	| allows use of H3StdVector<>, inherited from std::vector<> with H3ObjectAllocator<><br>uses conditional padding to match H3Vector format |
|     \_H3API\_EXCEPTION\_     	| tells the library to include the H3Exception exception handler within your project<br>which is derived from std::exception and may catch SEH errors.<br>your project needs to use /EHa compiler flag to use it. |
| \_H3API\_DONT\_USE\_MACROS\_ 	| tells the library to exclude some macros that can pollute the global namespace when defined.<br>these macros are then replaced by typedefs so extra parentheses may be required.<br>if you would like the convenience of switching between both modes, always add parentheses at the end. |
|   \_H3API\_NO\_VALIDATION\_  	| there are compile-time asserts in H3API to verify<br>structures' sizes and validate some template parameters.<br>define this macro if you do not wish to perform these validations. |
|    \_H3API\_PATCHER\_X86\_   	| tells the library to include its own "patcher_x86.hpp" header within your project<br>don't use this if you prefer having your own patcher_x86 header. |
|      \_H3API\_PLUGINS\_      	| tells the library to include the necessary headers to interact with H3Plugins projects<br>in most cases you won't need this. |
|    \_H3API\_DEVELOPMENT\_    	| reserved for development of H3API, defining this macro will do absolutely nothing<br>as the included H3_Development.hpp file does not contain anything |
