/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1999    *
 * *                                                               *
 * *   All Rights Reserved.  Unpublished rights  reserved  under   *
 * *   the copyright laws of the United States.                    *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Digital   *
 * *   Equipment Corporation.  Possession, use,  duplication  or   *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Digital Equipment  *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * HISTORY
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * math-hdr
 *
 *	Modification History:
 *
 * 01-Apr-91	Fred Canter
 *	MIPS C 2.20+, changes for -std
 *
 */
/* @(#)math.h   1.25  com/inc,3.1,9013 3/13/90 11:37:37 */
/*
 * COMPONENT_NAME: (math.h) math header file
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef  _MATH_H_
#define  _MATH_H_
#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */
#include <standards.h>

/*
 *      The ANSI standard requires that certain values be in math.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present.
 *
 *      This header includes all the ANSI required entries. In addition
 *      other entries for the XIX system are included.
 *
 */

/*
 *      ANSI required entries in math.h
 *
 */
#ifdef _ANSI_C_SOURCE

#ifdef _NO_PROTO

extern  double acos();
extern  double asin();
extern  double atan();
extern  double atan2();
extern  double ceil();
extern  double cos();
extern  double cosh();
extern  double exp();
extern  double fabs();
extern  double floor();
extern  double fmod();
extern  double frexp();
extern  double ldexp();
extern  double log();
extern  double log10();
extern  double modf();
extern  double pow();
extern  double sin();
extern  double sinh();
extern  double sqrt();
extern  double tan();
extern  double tanh();
/*
 * Single precision ANSI C functions. 
 */
extern float acosf ();
extern float asinf ();
extern float atanf ();
extern float atan2f ();
extern float ceilf ();
extern float cosf ();
extern float coshf ();
extern float expf ();
extern float fabsf ();
extern float floorf ();
extern float fmodf ();
extern float frexpf ();
extern float ldexpf ();
extern float logf ();
extern float log10f ();
extern float modff ();
extern float powf ();
extern float sinf ();
extern float sinhf ();
extern float sqrtf ();
extern float tanf ();
extern float tanhf ();

#else  /*_NO_PROTO */			/* Use ANSI C required prototyping */
#if defined(__STDC__) || defined(__cplusplus)

extern  double acos(double );
extern  double asin(double );
extern  double atan(double );
extern  double atan2(double ,double );
extern  double ceil(double );
extern  double cos(double );
extern  double cosh(double );
extern  double exp(double );
extern  double fabs(double );
extern  double floor(double );
extern  double fmod(double , double );
extern  double frexp(double , int *);
extern  double ldexp(double , int );
extern  double log(double );
extern  double log10(double );
extern  double modf(double , double *);
extern  double pow(double , double );
extern  double sin(double );
extern  double sinh(double );
extern  double sqrt(double );
extern  double tan(double );
extern  double tanh(double );
/*
 * Single precision ANSI C functions.
 */
extern float acosf ( float );
extern float asinf ( float );
extern float atanf ( float );
extern float atan2f ( float, float );
extern float ceilf ( float );
extern float cosf ( float );
extern float coshf ( float );
extern float expf ( float );
extern float fabsf ( float );
extern float floorf ( float );
extern float fmodf ( float, float );
extern float frexpf ( float, int * );
extern float ldexpf ( float, int );
extern float logf ( float );
extern float log10f ( float );
extern float modff ( float, float * );
extern float powf ( float, float );
extern float sinf ( float );
extern float sinhf ( float );
extern float sqrtf ( float );
extern float tanf ( float );
extern float tanhf ( float );

#endif
#endif /*_NO_PROTO */

#ifdef _INTRINSICS
extern  double cos( double );
extern  double sin( double );
#pragma intrinsic(cos, sin)
#ifndef fabs
extern double fabs( double );
#pragma intrinsic(fabs)
#endif
#endif

#ifdef __KAP
#pragma _KAP no side effects (acos)
#pragma _KAP no side effects (asin)
#pragma _KAP no side effects (atan)
#pragma _KAP no side effects (atan2)
#pragma _KAP no side effects (ceil)
#pragma _KAP no side effects (cos)
#pragma _KAP no side effects (cosh)
#pragma _KAP no side effects (exp)
#pragma _KAP no side effects (fabs)
#pragma _KAP no side effects (floor)
#pragma _KAP no side effects (fmod)
#pragma _KAP no side effects (frexp)
#pragma _KAP no side effects (ldexp)
#pragma _KAP no side effects (log)
#pragma _KAP no side effects (log10)
#pragma _KAP no side effects (modf)
#pragma _KAP no side effects (pow)
#pragma _KAP no side effects (sin)
#pragma _KAP no side effects (sinh)
#pragma _KAP no side effects (sqrt)
#pragma _KAP no side effects (tan)
#pragma _KAP no side effects (tanh)

#pragma _KAP no side effects (acosf)
#pragma _KAP no side effects (asinf)
#pragma _KAP no side effects (atanf)
#pragma _KAP no side effects (atan2f)
#pragma _KAP no side effects (ceilf)
#pragma _KAP no side effects (cosf)
#pragma _KAP no side effects (coshf)
#pragma _KAP no side effects (expf)
#pragma _KAP no side effects (fabsf)
#pragma _KAP no side effects (floorf)
#pragma _KAP no side effects (fmodf)
#pragma _KAP no side effects (frexpf)
#pragma _KAP no side effects (ldexpf)
#pragma _KAP no side effects (logf)
#pragma _KAP no side effects (log10f)
#pragma _KAP no side effects (modff)
#pragma _KAP no side effects (powf)
#pragma _KAP no side effects (sinf)
#pragma _KAP no side effects (sinhf)
#pragma _KAP no side effects (sqrtf)
#pragma _KAP no side effects (tanf)
#pragma _KAP no side effects (tanhf)
#endif /* __KAP */
#endif /*_ANSI_C_SOURCE */

/*
 *
 * The following function prototypes define functions available in the
 * XIX system but not required by the ANSI standard. They will not be
 * included in _ANSI_C_SOURCE is defined (strict ANSI conformance).
 *
 */

#ifdef _XOPEN_SOURCE

extern int signgam;

#ifdef _NO_PROTO
extern double   erf();
extern double   erfc();
extern double   gamma();
extern double   hypot();
extern int      isnan();
extern double   j0();
extern double   j1();
extern double   jn();
extern double   lgamma();
extern double   y0();
extern double   y1();
extern double   yn();

/*
 * Single precision XOPEN functions. These require full prototypes.
 */
#ifdef _OSF_SOURCE	/* Not defined in XPG4 */
extern float erfcf ();
extern float erff ();
extern float gammaf ();
extern float hypotf ();
extern int   isnanf ();
extern float j0f ();
extern float j1f ();
extern float jnf ();
extern float lgammaf ();
extern float y0f();
extern float y1f();
extern float ynf();
#endif /* _OSF_SOURCE */
#else
#if defined(__STDC__) || defined(__cplusplus)
extern double   erf(double );
extern double   erfc(double );
extern double   gamma(double );
extern double   hypot(double ,double );
extern int      isnan( double );
extern double   j0(double );
extern double   j1(double );
extern double   jn(int, double );
extern double   lgamma(double );
extern double   y0(double );
extern double   y1(double );
extern double   yn(int , double );

/*
 * Single precision XOPEN functions. 
 */
#ifdef _OSF_SOURCE	/* Not defined in XPG4 */
extern float erfcf ( float );
extern float erff ( float );
extern float gammaf ( float );
extern float hypotf ( float, float );
extern int   isnanf ( float );
extern float j0f ( float );
extern float j1f ( float );
extern float jnf ( int, float );
extern float lgammaf ( float );
extern float y0f( float );
extern float y1f( float );
extern float ynf( int, float );
#endif

#endif /* defined(__STDC__) || defined(__cplusplus) */
#endif /* _NO_PROTO */

#ifdef __KAP
#pragma _KAP no side effects (hypot)
#endif /* __KAP */

#endif /* _XOPEN_SOURCE */


#ifdef _OSF_SOURCE

#include <stdlib.h>

#if (defined(ultrix) || defined(__ULTRIX) || defined (__ultrix))
#    define   scalb ldexp
#endif

#endif /* _OSF_SOURCE */ 

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) 

#ifdef _NO_PROTO


/* same prototypes in _OSF_SOURCE and _XOPEN_SOURCE_EXTENDED */ 

extern double   acosh();
extern double   asinh();
extern double   atanh();
extern double   cbrt();
extern double   expm1();
extern double   log1p();
extern double   logb();
extern double   nextafter();
extern double   remainder();
extern double   rint();

#ifdef _XOPEN_SOURCE_EXTENDED

/* different in Spec1170 */
extern double   scalb();

/* additional in Spec1170 */  
extern int ilogb();

#else   /* not _XOPEN_SOURCE_EXTENDED but _OSF_SOURCE */

extern double   cabs();
extern double   copysign ();
extern double   drem();

#if !(defined(ultrix) || defined(__ULTRIX) || defined (__ultrix))
extern double   scalb();
#endif
extern int      finite();

/*
 * Single precision Digital functions. 
 */
extern float acoshf ();
extern float asinhf ();
extern float atanhf ();
extern float cabsf ();
extern float cbrtf ();
extern float copysignf ();
extern float dremf ();
extern float expm1f ();
extern float log1pf ();
extern float logbf ();
extern float nextafterf ();
extern float remainderf ();
extern float rintf ();
extern float scalbf ();
extern int finitef ();

/*
 * FAST Floating Point
 */
extern double F_acos ();
extern double F_asin ();
extern double F_atan ();
extern double F_atan2 ();
extern double F_cos ();
extern double F_exp ();
extern double F_hypot ();
extern double F_log ();
extern double F_log10 ();
extern double F_pow ();
extern double F_sin ();
extern double F_sqrt ();
extern double F_tan ();

/*
 * FAST Floating Point single precision
 */
extern float F_acosf ();
extern float F_asinf ();
extern float F_atan2f ();
extern float F_atanf ();
extern float F_cosf ();
extern float F_expf ();
extern float F_hypotf ();
extern float F_log10f ();
extern float F_logf ();
extern float F_powf ();
extern float F_sinf ();
extern float F_sqrtf ();
extern float F_tanf ();

/*
 * Additional Digital functions
 */
extern double acosd ();
extern double asind ();
extern double atand ();
extern double atand2 ();
extern double cosd ();
extern double cot ();
extern double cotd ();
extern double log2 ();
extern double nint ();
extern double powi ();
extern double sind ();
extern double tand ();
extern double trunc ();

extern float acosdf ();
extern float asindf ();
extern float atand2f ();
extern float atandf ();
extern float cosdf ();
extern float cotdf ();
extern float cotf ();
extern float log2f ();
extern float nintf ();
extern float powif ();
extern float sindf ();
extern float tandf ();
extern float truncf ();

extern int fp_class ();
extern int fp_classf ();
extern int powii ();
extern int unordered ();
extern int unorderedf ();

#endif  /* _XOPEN_SOURCE_EXTENDED */

#else /* _NO_PROTO */			/* Use ANSI C required prototyping */

#if defined(__STDC__) || defined(__cplusplus)

/* same prototypes in _OSF_SOURCE and _XOPEN_SOURCE_EXTENDED */

extern double   acosh(double );
extern double   asinh(double );
extern double   atanh(double );
extern double   cbrt(double );
extern double   expm1(double );
extern double   log1p(double );
extern double   logb( double );
extern double   nextafter(double, double );
extern double   remainder(double, double );
extern double   rint(double );

#ifdef _XOPEN_SOURCE_EXTENDED

/* different in Spec1170 */
extern double   scalb( double , double );

/* additional in Spec1170 */
extern int ilogb(double );

#else   /* not _XOPEN_SOURCE_EXTENDED but _OSF_SOURCE */

extern double   cabs( double, double );
extern double   copysign (double , double );
extern double   drem(double , double );

#if !(defined(ultrix) || defined(__ULTRIX) || defined (__ultrix))
extern double   scalb( double , double );
#endif
extern int      finite( double );

/*
 * Single precision Digital functions. 
 */
extern float acoshf ( float );
extern float asinhf ( float );
extern float atanhf ( float );
extern float cabsf ( float, float );
extern float cbrtf ( float );
extern float copysignf ( float, float );
extern float dremf ( float, float );
extern float expm1f ( float );
extern float log1pf ( float );
extern float logbf ( float );
extern float nextafterf ( float, float );
extern float remainderf ( float, float );
extern float rintf ( float );
extern float scalbf ( float, float );
extern int finitef ( float );

/*
 * FAST Floating Point
 */
extern double F_acos ( double );
extern double F_asin ( double );
extern double F_atan ( double );
extern double F_atan2 ( double, double );
extern double F_cos ( double );
extern double F_exp ( double );
extern double F_hypot ( double, double );
extern double F_log ( double );
extern double F_log10 ( double );
extern double F_pow ( double, double );
extern double F_sin ( double );
extern double F_sqrt ( double );
extern double F_tan ( double );
/*
 * FAST Floating Point single precision
 */
extern float F_acosf ( float );
extern float F_asinf ( float );
extern float F_atan2f ( float, float );
extern float F_atanf ( float );
extern float F_cosf ( float );
extern float F_expf ( float );
extern float F_hypotf ( float, float );
extern float F_log10f ( float );
extern float F_logf ( float );
extern float F_powf ( float, float );
extern float F_sinf ( float );
extern float F_sqrtf ( float );
extern float F_tanf ( float );

/*
 * Additional Digital functions
 */
extern double acosd ( double );
extern double asind ( double );
extern double atand ( double );
extern double atand2 ( double, double );
extern double cosd ( double );
extern double cot ( double );
extern double cotd ( double );
extern double log2 ( double );
extern double nint ( double );
extern double powi ( double, int );
extern double sind ( double );
extern double tand ( double );
extern double trunc ( double );

extern float acosdf ( float );
extern float asindf ( float );
extern float atand2f ( float, float );
extern float atandf ( float );
extern float cosdf ( float );
extern float cotdf ( float );
extern float cotf ( float );
extern float log2f ( float );
extern float nintf ( float );
extern float powif ( float, int );
extern float sindf ( float );
extern float tandf ( float );
extern float truncf ( float );

extern int fp_class ( double );
extern int fp_classf ( float );
extern int powii ( int, int );
extern int unordered ( double, double );
extern int unorderedf ( float, float );

#endif  /* _XOPEN_SOURCE_EXTENDED */

#endif  /* defined(__STDC__) || defined(__cplusplus) */ 

#endif /* _NO_PROTO */

#ifdef __KAP
#pragma _KAP no side effects (cabs)
#pragma _KAP no side effects (cabsf)
#endif /* __KAP */

#define _ABS(x) ((x) < 0 ? -(x) : (x))
#define _REDUCE(TYPE, X, XN, C1, C2)    { \
        double x1 = (double)(TYPE)X, x2 = X - x1; \
        X = x1 - (XN) * (C1); X += x2; X -= (XN) * (C2); }
#define _POLY1(x, c)    ((c)[0] * (x) + (c)[1])
#define _POLY2(x, c)    (_POLY1((x), (c)) * (x) + (c)[2])
#define _POLY3(x, c)    (_POLY2((x), (c)) * (x) + (c)[3])
#define _POLY4(x, c)    (_POLY3((x), (c)) * (x) + (c)[4])
#define _POLY5(x, c)    (_POLY4((x), (c)) * (x) + (c)[5])
#define _POLY6(x, c)    (_POLY5((x), (c)) * (x) + (c)[6])
#define _POLY7(x, c)    (_POLY6((x), (c)) * (x) + (c)[7])
#define _POLY8(x, c)    (_POLY7((x), (c)) * (x) + (c)[8])
#define _POLY9(x, c)    (_POLY8((x), (c)) * (x) + (c)[9])


#ifdef _OSF_SOURCE 

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

#define 	DOMAIN		01
#define		SING		02
#define		OVERFLOW	03
#define		UNDERFLOW	04
#define		TLOSS		05
#define		PLOSS		06

#endif /* _OSF_SOURCE */ 

#ifdef _FASTMATH
#define acos	F_acos
#define asin	F_asin
#define atan	F_atan
#define atan2	F_atan2
#define cos	F_cos
#define exp	F_exp
#define hypot	F_hypot
#define log	F_log
#define log10	F_log10
#define pow	F_pow
#define sin	F_sin
#define sqrt	F_sqrt
#define tan	F_tan
#define acosf	F_acosf
#define asinf	F_asinf
#define atan2f	F_atan2f
#define atanf	F_atanf
#define cosf	F_cosf
#define expf	F_expf
#define hypotf	F_hypotf
#define log10f	F_log10f
#define logf	F_logf
#define powf	F_powf
#define sinf	F_sinf
#define sqrtf	F_sqrtf
#define tanf	F_tanf
#endif /* _FASTMATH */
#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

/* N.B.  This FILE must be catenated with a machine-dependent file  ${MACHINE}/math.h
   with ends with #endif for _MATH_H_ feature-test
*/
/*
 */
/*
 * HISTORY
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: (math.h) math header file
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *      ANSI required entries in math.h
 *
 */
#ifdef _ANSI_C_SOURCE

#if defined(_IEEE_FP)
#	define HUGE_VAL 1.8e308
#else
#	define HUGE_VAL 1.797693134862315708e308
#endif

#endif /*_ANSI_C_SOURCE */

/*
 *
 * The following function prototypes define functions available in the
 * XIX system but not required by the ANSI standard. They will not be
 * included in _ANSI_C_SOURCE is defined (strict ANSI conformance).
 *
 */

#ifdef _XOPEN_SOURCE

/*
 *      Useful mathmatical constants:
 *
 * M_E          - e
 * M_LOG2E      - log2(e)
 * M_LOG10E     - log10(e)
 * M_LN2        - ln(2)
 * M_LN10       - ln(10)
 * M_PI         - pi
 * M_PI_2       - pi/2
 * M_PI_4       - pi/4
 * M_1_PI       - 1/pi
 * M_2_PI       - 2/pi
 * M_2_SQRTPI   - 2/sqrt(pi)
 * M_SQRT2      - sqrt(2)
 * M_SQRT1_2    - 1/sqrt(2)
*/

#define M_E        2.7182818284590452354E0  /*Hex  2^ 0 * 1.5bf0a8b145769 */
#define M_LOG2E    1.4426950408889634074E0  /*Hex  2^ 0 * 1.71547652B82FE */
#define M_LOG10E   4.3429448190325182765E-1 /*Hex  2^-2 * 1.BCB7B1526E50E */
#define M_LN2      6.9314718055994530942E-1 /*Hex  2^-1 * 1.62E42FEFA39EF */
#define M_LN10     2.3025850929940456840E0  /*Hex  2^ 1 * 1.26bb1bbb55516 */
#define M_PI       3.1415926535897932385E0  /*Hex  2^ 1 * 1.921FB54442D18 */
#define M_PI_2     1.5707963267948966192E0  /*Hex  2^ 0 * 1.921FB54442D18 */
#define M_PI_4     7.8539816339744830962E-1 /*Hex  2^-1 * 1.921FB54442D18 */
#define M_1_PI     3.1830988618379067154E-1 /*Hex  2^-2 * 1.45f306dc9c883 */
#define M_2_PI     6.3661977236758134308E-1 /*Hex  2^-1 * 1.45f306dc9c883 */
#define M_2_SQRTPI 1.1283791670955125739E0  /*Hex  2^ 0 * 1.20dd750429b6d */
#define M_SQRT2    1.4142135623730950488E0  /*Hex  2^ 0 * 1.6A09E667F3BCD */
#define M_SQRT1_2  7.0710678118654752440E-1 /*Hex  2^-1 * 1.6a09e667f3bcd */


#ifndef _MAXFLOAT
#define _MAXFLOAT
#define MAXFLOAT            ((float)3.40282346638528860e+38)
#endif

#endif /* _XOPEN_SOURCE */

#ifdef _OSF_SOURCE

/*
 *      Useful mathmatical constants:
 *
 * HUGE         - +infinity if ieee, else max_double
 * M_2PI        - 2*pi
 *
 */
#if defined(_IEEE_FP)
#	define HUGE 1.8e308
#else
#	define HUGE 1.797693134862315708e308
#endif
#define M_2PI      6.2831853071795864769E0  /*Hex  2^ 2 * 1.921FB54442D18 */

/* This is the nearest number to the cube root of MAXDOUBLE that   */
/*      doesn't cause the cube of it to overflow.                  */
/* In double precision hex this constant is: 554428a2 f98d728a     */
#define CUBRTHUGE      5.6438030941223618e102
#define INV_CUBRTHUGE  1.7718548704178434e-103

#endif /* _OSF_SOURCE */
#if defined(__cplusplus)
}
#endif
#endif /* _MATH_H_ */

