#ifndef CE_ANGELSCRIPT_CONFIG_H_INCLUDED
#define CE_ANGELSCRIPT_CONFIG_H_INCLUDED

#ifdef _MSC_VER

   /// MSVC compiler

   #ifdef CE_ANGELSCRIPT_IMPLEMENTATION
      #define CE_ANGELSCRIPT_PUBLIC  
      #define CE_ANGELSCRIPT_EXTERN
   #else
      #define CE_ANGELSCRIPT_PUBLIC 
      #define CE_ANGELSCRIPT_EXTERN 
   #endif
   #define CE_ANGELSCRIPT_PRIVATE

#elif __GNUC__

   /// gnu gcc
   
   #define CE_ANGELSCRIPT_PUBLIC   
   #define CE_ANGELSCRIPT_PRIVATE 
   #define CE_ANGELSCRIPT_EXTERN
	  
#else

  #error "Unknown compiler"

#endif


#endif // CE_ANGELSCRIPT_CONFIG_H_INCLUDED

