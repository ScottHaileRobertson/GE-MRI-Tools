/**
 * Copyright 1991-2002 General Electric Company.
 * All rights reserved.
 *
 * File Name: GEtypes.h
 *
 * As per the Software C Coding Standards, July 2, 1991,
 * the Software Developer is required to use the typedef's
 * shown below in place of all basic data types.
 */

#ifndef GEtypes_INCL
#define GEtypes_INCL



/**************************************************
 *                                                *
 * OS       :   Windows                           *
 * Compiler :   MS VC++                           *
 * Version  :   tested on 6.0                     *
 *                                                *
 **************************************************/
#ifdef _MSC_VER
/* VC++ provides built in types for different sizes of integers */
#pragma warning(disable:4786)
#pragma warning(disable:4250)
typedef char               s8;
typedef unsigned char      n8;
typedef short              s16;
typedef unsigned short     n16;
typedef int                s32;
typedef unsigned int       n32;

typedef float              f32;
typedef double             f64;

#ifdef ENABLE_GETYPE_64BIT_DEFINE

#include <tchar.h>
#include <ostream>

typedef __int64            s64;
typedef unsigned __int64   n64;

/*
	This functions are necessary to overcome the fact that an 
	ostream operator<< is not supplied for the built in type 
	__int64.
*/
template <class _E, class _Tr>
inline  std::basic_ostream<_E, _Tr>& __cdecl operator<<(	std::basic_ostream<_E, _Tr>& _O, __int64 i64Val)
{
	_TCHAR chBuf[33];

	/* VC5BUG: _i64tot cannot handle negative numbers */
	if (i64Val < 0)
	{
		_O << _T("-");
		i64Val *= -1;
	}

	return (_O << _i64tot(i64Val, chBuf, 10)) ;	
}

template <class _E, class _Tr>
inline  std::basic_ostream<_E, _Tr>& __cdecl operator<<(	std::basic_ostream<_E, _Tr>& _O, unsigned __int64 i64Val)
{
	_TCHAR chBuf[33];

	return (_O << _i64tot(i64Val, chBuf, 10)) ;	
}

#endif /* ENABLE_GETYPE_64BIT_DEFINE */

/***************************************************
 *                                                 *
 * OS       :   Linux (RedHat)                     *
 * Compiler :   GNU                                *
 * Version  :   tested on 2.96                     *
 *                                                 *
 ***************************************************/
#elif defined(__linux__)

/* 
 * it is assumed that a GNU compiler is used
 * use these declarations for the GNU gcc compiler (as defined 
 * in sys/types.h) 
 */
#include <sys/types.h>

typedef char               s8;
typedef unsigned char      n8;
typedef int16_t            s16;
typedef u_int16_t          n16;
typedef long               s32;
typedef unsigned long      n32;

#ifdef ENABLE_GETYPE_64BIT_DEFINE

typedef int64_t            s64;
typedef u_int64_t          n64;

#endif /* ENABLE_GETYPE_64BIT_DEFINE */

typedef float              f32;
typedef double             f64;

/***************************************************
 *                                                 *
 * OS       :   Irix                               *
 * Compiler :   MIPSpro Compiler                   *
 * Version  :   tested on 7.2.1                    *
 *                                                 *
 ***************************************************/
#elif defined(IRIX)
/* the following types can be found in sys/types.h (or inttypes.h) */
#include <inttypes.h>

typedef char               s8;
typedef unsigned char      n8;
typedef int16_t            s16;
typedef uint16_t           n16;
typedef int32_t            s32;
typedef uint32_t           n32;

#ifdef ENABLE_GETYPE_64BIT_DEFINE

typedef int64_t            s64;
typedef uint64_t           n64;

#endif /* ENABLE_GETYPE_64BIT_DEFINE */

typedef float              f32;
typedef double             f64;


/***************************************************
 *                                                 *
 * OS       :   MCOS                               *
 * Compiler :   -                                  *
 * Version  :   -                                  *
 *                                                 *
 ***************************************************/
#elif defined(MCOS)

typedef char               s8;
typedef unsigned char      n8;
typedef short              s16;
typedef unsigned short     n16;
typedef int                s32;
typedef unsigned int       n32;

#ifdef ENABLE_GETYPE_64BIT_DEFINE

typedef long long          s64;
typedef unsigned long long n64;

#endif /* ENABLE_GETYPE_64BIT_DEFINE */

typedef float              f32;
typedef double             f64;

/***************************************************
 *                                                 *
 * OS       :   VxWorks                            *
 * Compiler :   Tornado 2.0 runnig gcc             *
 * Version  :   tested on cygnus-2.7.2-960126      *
 *                                                 *
 ***************************************************/
#else /* defined(VXWORKS) */

typedef char                   s8;
typedef unsigned char          n8;
typedef short                  s16;
typedef unsigned short         n16;
typedef long                   s32;
typedef unsigned long          n32;

#ifdef ENABLE_GETYPE_64BIT_DEFINE

typedef long long int          s64;
typedef unsigned long long int n64;

#endif /* ENABLE_GETYPE_64BIT_DEFINE */

typedef float                  f32;
typedef double                 f64;

#endif /* defined(_MSC_VER) */


#endif /* GEtypes_INCL */


