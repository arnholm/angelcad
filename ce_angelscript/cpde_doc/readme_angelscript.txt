Angelscript as static library on Windows
========================================

Download from   :  http://angelcode.com/angelscript/

Instead of using the included make or project files, which do not appear to compile the 
included "add_on" folder (containing very useful things), the current project is built
from scratch in CPDE and included as a standard CPDE static library on engine level.

Steps to create the project file:

1. Used the cpde Project Wizard to create a cpde_ISO_LIB project called ce_angelscript

2. Expanded angelscript_<version>.zip into the project so that the folder structure becomes
   ce_angelscript/angelscript_<version>/sdk/...
 
3. Set project include path internally (all targets)
   search directories -> Compiler:   angelscript_<version>\sdk\angelscript\include
   
4. Copied 2 files  
     ce_angelscript\cpde_doc\ce_angelscript.h         ==> ce_angelscript\angelscript_<version>\sdk
     ce_angelscript\cpde_doc\ce_angelscript_config.h  ==> ce_angelscript\angelscript_<version>\sdk
	 
   This simplifies #includes in applications, see step 6 below
   
5. Added aatc container library to std/add_on
   - cd "somewhere" 
   - git clone https://github.com/Sami-Vuorela/aatc
   - create subfolder ce_angelscript\angelscript_<version>\sdk\add_on\aatc
   - copy contents of "somewhere"\aatc\source to ce_angelscript\angelscript_<version>\sdk\add_on\aatc
   - edit aatc_config.hpp with ANGELSCRIPT_H protection around #include <angelscript.h>

6. Customised the post build steps using the -iroot option:
   $(CPDE_USR)/bin/cpde_usr -project=$(PROJECT_NAME)  -root=$(PROJECT_DIR)  -build=$(TARGET_NAME)  -iroot=angelscript_2.31.0\sdk -target=$(TARGET_OUTPUT_FILE)  -usr=$(CPDE_USR)

   Applications can then simply do 
	   #include "ce_angelscript/ce_angelscript.h"
   and
       #include "ce_angelscript/add_on/scriptbuilder/scriptbuilder.h"
       #include "ce_angelscript/add_on/scriptstdstring/scriptstdstring.h"
   
7. Special handling of as_callfunc_x64_* files
	  - as_callfunc_x64_arm.asm      : exclude from MSVC/GCC targets
      - as_callfunc_x64_gcc.cpp      : exclude from MSVC targets
	  - as_callfunc_x64_mingw.cpp    : exclude from MSVC/GCC targets
	  - as_callfunc_x64_msvc.cpp     : exclude from GCC targets
	  - as_callfunc_x64_msvc_asm.asm : define custom build: $(#MSVC_TOOLCHAIN.ASM)  /c /nologo /W3 /Zi  /Fo$object $file
	  - as_callfunc_arm_gcc.S        : exclude from MSVC targets
	  - as_callfunc_arm_vita.S       : exclude from MSVC/GCC targets
	  - as_callfunc_arm_xcode.S      : exclude from MSVC/GCC targets
	  - as_callfunc_ppc.cpp          : exclude from MSVC/GCC targets
	  - as_callfunc_ppc_64.cpp       : exclude from MSVC/GCC targets
	  - as_callfunc_xenon.cpp        : exclude from MSVC/GCC targets
	  - as_callfunc_mips.cpp         : exclude from MSVC/GCC targets
	  - as_callfunc_arm.cpp          : exclude from MSVC/GCC targets
	  
	  MSVC_TOOLCHAIN.ASM is set to "ml64.exe"                for x64 (64bit)
	  MSVC_TOOLCHAIN.ASM is set to "cpde_dummy_compiler.exe" for x86 (32bit)
	  
8. Build CPDE as usual
   See User Manual in ce_angelscript\angelscript_2.30.2\sdk\docs
   
9. How to upgrade core version of angelscript
   9.1 remove all source files from project file
   9.2 remove everything under angelscript_2.31.0 (including that folder) from source control and delete files.
   9.3 copy in new files files from new version. Add to source control.
   9.4 add source files to project from folders sdk/angelscript and sdk/add_on.
   9.5 add aatc source files to stk/add_on as described in point 5
   9.6 Repeat steps [3-7] to configure the new version
         
   