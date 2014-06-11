/*
 * Copyright (C) 2013-2014 TMDJoJo. All rights reserved.
 *
 * Language: UTF-8
 * Maximum line width: 80 chars
 * Tab width: 4 spaces
 *
 *  File name: yi_type.h
 *  Created on: 2014-1-1
 *  Author: tmdjojo
 *  Description:
 */

#ifndef YI_TYPE_H_
#define YI_TYPE_H_


////g++  version: 4.6.3


////////////////////////////////////////
////fundamental types define
////////////////////////////////////////

////below length 8 bits
#define VOID                    void
typedef bool                    BOOL;
typedef unsigned char           UCHAR;
typedef char                    CHAR;

////below length 16 bits
typedef unsigned short          USHORT;
typedef short                   SHORT;

////below length 32 bits
typedef unsigned int            UINT;
typedef int                     INT;
typedef float                   FLOAT;

////below length 64 bits
typedef unsigned long           ULONG;
typedef long                    LONG;
////long long


////////////////////////////////////////
////fundamental macros define
////////////////////////////////////////

////true
#ifndef TRUE
    #define TRUE 1
#endif
////false
#ifndef FALSE
    #define FALSE 0
#endif


////max file path length
#ifndef _MAX_PATH
    #define _MAX_PATH 260
#endif

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif

////////////////////////////////////////
////free memory macro
////////////////////////////////////////

////delete memory
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)  if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif

////delete array memory
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)    if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif

////////////////////////////////////////
////trace macro
////////////////////////////////////////
//#define DEBUG(formate,...)  printf("[DEBUG]"formate,__VA_ARGS__)
#define _DEBUG

#ifndef _DEBUG
    #define DEBUG(formate...)
#else
    #define DEBUG(formate...)  printf("[DEBUG] "formate)
#endif

#define PRINT(formate...)  printf("[DEBUG] "formate)

////
//#ifndef SAFE_FREE
//#define SAFE_FREE(x)  if( (x)!=NULL ) { free(x); (x)=NULL; }
//#endif

////
//#ifndef SAFE_RELEASE
//#define SAFE_RELEASE(x)   if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
//#endif

#endif /* YI_TYPE_H_ */
