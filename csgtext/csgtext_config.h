#ifndef CSGTEXT_CONFIG_H_INCLUDED
#define CSGTEXT_CONFIG_H_INCLUDED

#ifdef _MSC_VER

   /// MSVC compiler
   // disabling warning 4251 is the only practical way to deal with dll-export issues according to M$
   #pragma warning (disable:4251) // class "XX" needs to have dll-interface to be used by clients of class "YY"

   #ifdef CSGTEXT_IMPLEMENTATION
      #define CSGTEXT_PUBLIC __declspec(dllexport)
      #define CSGTEXT_EXTERN
   #else
      #define CSGTEXT_PUBLIC __declspec(dllimport)
      #define CSGTEXT_EXTERN extern
   #endif
   #define CSGTEXT_PRIVATE

#elif __GNUC__

   /// gnu gcc

   #define CSGTEXT_PUBLIC  __attribute__ ((visibility("default")))
   #define CSGTEXT_PRIVATE __attribute__ ((visibility("hidden")))
   #define CSGTEXT_EXTERN

#else

  #error "Unknown compiler"

#endif


#endif // CSGTEXT_CONFIG_H_INCLUDED

