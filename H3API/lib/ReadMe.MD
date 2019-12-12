H3API may now be used as a header-only style library
in which case all you are required to do is:

`#include "[relative_path]/H3API.hpp"`
              
It it now possible as well to complie H3API into a 
static library, in this case you need to write:

`#define _H3API_LIBRARY_`

`#include "[relative_path]/H3API.hpp"`

and link the library to your project.

**Note**
>The library is now stored within `namespace h3` to help in preventing conflicts. If you do not wish to type `h3::` every time you use H3API, add the `using namespace h3;` line to your code.

H3API Preprocessor Definitions Overview
---

**\_H3API\_LIBRARY\_**

tells the library that it should only include header files within your project
and that you will rely on the static library to access the library's implementation
by default the library is header-only.

**\_H3API\_OPERATORS\_**

tells the library to replace the new, new[], delete and delete[] operators
by the game's own operators.
be mindful of hooking too early in the launch process when using this.

**\_H3\_STD\_CONVERSIONS_**

allows conversion between the following formats

`std::string <<==>> h3::H3String`

`std::vector <<==>> h3::H3Vector`

**\_H3API\_EXCEPTION_**

tells the library to include the H3Exception exception handler within your project
which is derived from std::exception and may catch SEH errors.
your project needs to use /EHa compiler flag to use it.

**\_H3API\_DONT\_USE\_MACROS\_**

tells the library to exclude some macros that can pollute the global namespace
when defined, these macros are replaced by function calls so you need to add parentheses

`e.g. gameWidth <<==>> gameWidth()`

**\_H3API\_PATCHER\_X86\_**

tells the library to include its own "patcher_x86.hpp" header within your project
don't use this if you prefer having your own patcher_x86 header. 

**\_H3API\_PLUGINS\_**

tells the library to include the necessary headers to interact with H3Plugins projects
in most cases you won't need this.
