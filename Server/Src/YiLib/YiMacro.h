#ifndef __YIMACRO_H__
#define __YIMACRO_H__

// Check windows
#if _WIN32 || _WIN64
    #if _WIN64
        #define _YI64
    #else
        #define _YI32
    #endif
#endif

// Check GCC
#if __GNUC__
    #if __x86_64__ || __ppc64__
        #define _YI64
    #else
        #define _YI32
    #endif
#endif

#endif //__YIMACRO_H__
