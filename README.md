### User documentation ###

Relevant user documentation and other useful resources are found [here](https://arnholm.github.io/angelcad-docs/). Pre-built binaries of AngelCAD are found [here](https://github.com/arnholm/angelcad/releases).


### Building AngelCAD ###

AngelCAD build system is based on [Code::Blocks](http://codeblocks.org/) and CPDE as described in [cpde_utils](https://github.com/arnholm/cpde_utils). To build AngelCAD it is required to install Code::Blocks and configure it as documented. On Linux, the g++ compiler is used. On Windows, MSVC2013 or newer is required (the free 'express' versions of MSVC are ok).

Furthermore, CPDE requires building and configuring the following 3rd party libraries 

| Library                             | Description/Comments |
| ----------------------------------- | -------------------- |
| [wxWidgets](http://wxwidgets.org/)  | Static library build, see instructions |
| [boost](https://www.boost.org/)  | boost_system, boost_filesystem, boost_thread |
| [msgpack](https://msgpack.org/) | C/C++ version. Not strictly required for AngelCAD build, but recommended |

Since AngelCAD 1.5-06, [FreeType](https://freetype.org/) is also required.

The best way to build the 3rd party libraries is to run the build scripts found in the [cpde_3rdparty](https://github.com/arnholm/cpde_3rdparty) repository.

## libraries required ##

Before building AngelCAD, you must build the following workspaces, containing libraries used

| Workspace                           | Libraries required by AngelCAD |
| ----------------------------------- | -------------------- |
| [cpde_syslibs](https://github.com/arnholm/cpde_syslibs/)  | cf_syslib, ce_angelscript, ce_angelscript_ex |
| [spacelibs](https://github.com/arnholm/spacelibs/)  | spacemath, spaceio, polyhealer, dxfdom |


## Applications included ##

The following applications are included in the build

| Application                         | Description |
| ----------------------------------- | -------------------- |
| as_csg    | AngelCAD script compiler |
| AngelCAD  | AngelCAD GUI editor/IDE |
| AngelView | AngelCAD 3d file viewer |
| polyfix   | command line 3d file repair utility |
| dxfread   | command line DXF file reader |
| csgfix    | command line preprocessor of OpenSCAD .csg files |


## xcsg ##

AngelCAD uses the [xcsg](https://github.com/arnholm/xcsg) application as the boolean engine. Build it or install a [prebuilt binary of xcsg](https://github.com/arnholm/xcsg/releases)


