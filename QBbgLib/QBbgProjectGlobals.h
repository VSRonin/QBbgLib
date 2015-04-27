#ifndef ProjectGlobals_h__
#define ProjectGlobals_h__
//#define PRINT_RESPONSE_MESSAGE //Uncomment to debug response messages from bloomberg
#ifdef QBBG_LIB_BUILD
    #define QBBG_EXPORT __declspec(dllexport)
    #define QBBG_EXTERN 
#else
    #define QBBG_EXPORT __declspec(dllimport)
    #define QBBG_EXTERN extern
#endif // QBBG_LIB_BUILD
#endif