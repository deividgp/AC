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
 */
/*
 * HISTORY
 */
#ifndef lint
static char	*sccsid = "@(#)$RCSfile: llib-lm.c,v $ $Revision: 4.2.7.2 $ (DEC) $Date: 1994/02/22 21:23:12 $",
#endif 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: (CMDPROG) Programming Utilities
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27, 10
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*NOTUSED*/
/*NOTDEFINED*/

#include <math.h>

int signgam;

/* BESSEL(3M) */
double	j0(double x) { return (x); }
double	j1(double x) { return (x); }
double	jn(int n, double x) { return (x); }
double	y0(double x) { return (x); }
double	y1(double x) { return (x); }
double	yn(int n, double x) { return (x); }
/* single precision */
float	j0f(float x) { return (x); }
float	j1f(float x) { return (x); }
float	jnf(int n, float x) { return (x); }
float	y0f(float x) { return (x); }
float	y1f(float x) { return (x); }
float	ynf(int n, float x) { return (x); }
/* ERF(3M) */
double	erf(double x) { return (x); }
double	erfc(double x) { return (x); }
/* single precision */
float	erff(float x) { return (x); }
float	erfcf(float x) { return (x); }
/* EXP(3M) */
double	exp(double x) { return (x); }
double	expm1(double x) { return (x); }
double	log(double x) { return (x); }
double	log10(double x) { return (x); }
double	pow(double x, double y)  { return (x); }
double	sqrt(double x) { return (x); }

/* Single precision */
float	expf(float x) { return (x); }
float	expm1f(float x) { return (x); }
float	logf(float x) { return (x); }
float	log10f(float x) { return (x); }
float	powf(float x, float y)  { return (x); }
float	sqrtf(float x) { return (x); }
/* FLOOR(3M) */
double	floor(double x) { return (x); }
double	ceil(double x) { return (x); }
double	drem(double x, double y) { return (x); }
double	fmod(double x, double y) { return (x); }
double	fabs(double x) { return (x); }
double  cabs(double x, double y) { return (x); }
double	modf(double x, double *n) { return (x); }
double	remainder(double x, double y) { return (x); }
double  rint(double x) { return (x); }

/* Single precision */
float	floorf(float x) { return (x); }
float	ceilf(float x) { return (x); }
float	dremf(float x, float y) { return (x); }
float	fmodf(float x, float y) { return (x); }
float	fabsf(float x) { return (x); }
float   cabsf(float x, float y) { return (x); }
float	modff(float x, float *n) { return (x); }
float	remainderf(float x, float y) { return (x); }
float	rintf(float x) { return (x); }

/* FREXP(3M) */
double  frexp(double x, int *i) { return (x); }
float   frexpf(float x, int *i) { return (x); }
double  ldexp(double x, int i) { return (x); }
float   ldexpf(float x, int i) { return (x); }
double  logb(double x) { return (x); }
float   logbf(float x) { return (x); }
double  scalb(double x, double i) { return (x); }
float   scalbf(float x, float i) { return (x); }

/* GAMMA(3M) */
double	gamma(double x) { return (x); }
float	gammaf(float x) { return (x); }
double	lgamma(double x) { return (x); }
float	lgammaf(float x) { return (x); }

/* HYPOT(3M) */
double	hypot(double x, double y) { return (x); }
float	hypotf(float x, float y) { return (x); }

/* MATHERR(3M) */
int	matherr(struct exception *p) { return (0); }

/* SINH(3M) */
double	sinh(double x) { return (x); }
double	cosh(double x) { return (x); }
double	tanh(double x) { return (x); }

/* single precision */
float	sinhf(float x) { return (x); }
float	coshf(float x) { return (x); }
float	tanhf(float x) { return (x); }

/* TRIG(3M) */
double	sin(double x) { return (x); }
double	cos(double x) { return (x); }
double	tan(double x) { return (x); }
double	asin(double x) { return (x); }
float	acosf(float x) { return (x); }
double	acos(double x) { return (x); }
double	atan(double x) { return (x); }
double	atan2(double x, double y) { return (x); }

double	asinh(double x) { return (x); }
double	acosh(double x) { return (x); }
double	atanh(double x) { return (x); }
double	cbrt(double x) { return (x); }
double	nearest(double x) { return (x); }
double	trunc(double x) { return (x); }
int	    ilogb(double x) { return (0); }
int	    isnan(double x) { return (0); }
double	log1p(double x) { return (x); }
double	copysign(double x, double y) { return (x); }
int     finite (double x) { return (0); }
int     fp_class (double x) { return (x); }
double	nextafter(double x, double y) { return (x); }
int	    unordered(double x, double y) { return (0); }
/* single precision */
float	sinf(float x) { return (x); }
float	cosf(float x) { return (x); }
float	tanf(float x) { return (x); }
float	asinf(float x) { return (x); }
float	atanf(float x) { return (x); }
float	atan2f(float x, float y) { return (x); }
float	asinhf(float x) { return (x); }
float	acoshf(float x) { return (x); }
float	atanhf(float x) { return (x); }
float	cbrtf(float x) { return (x); }
float	truncf(float x) { return (x); }
int	    isnanf(float x) { return (0); }
float	log1pf(float x) { return (x); }
float	copysignf(float x, float y) { return (x); }
int     finitef(float x) { return (0); }
int     fp_classf(float x) { return (x); }
float	nextafterf(float x, float y) { return (x); }
int	    unorderedf( float x, float y) { return (0); }

/*
 * FAST Floating Point
 */
double F_acos (double x) { return (x); }
double F_asin (double x) { return (x); }
double F_atan (double x) { return (x); }
double F_atan2 (double x, double y) { return (x); }
double F_cos (double x) { return (x); }
double F_exp (double x) { return (x); }
double F_hypot (double x, double y) { return (x); }
double F_log (double x) { return (x); }
double F_log10 (double x) { return (x); }
double F_pow (double x, double y) { return (x); }
double F_sin (double x) { return (x); }
double F_sqrt (double x) { return (x); }
double F_tan (double x) { return (x); }
/*
 * FAST Floating Point single precision
 */
float F_acosf (float x) { return (x); }
float F_asinf (float x) { return (x); }
float F_atan2f (float x, float y) { return (x); }
float F_atanf (float x) { return (x); }
float F_cosf (float x) { return (x); }
float F_expf (float x) { return (x); }
float F_hypotf (float x, float y) { return (x); }
float F_log10f (float x) { return (x); }
float F_logf (float x) { return (x); }
float F_powf (float x, float y) { return (x); }
float F_sinf (float x) { return (x); }
float F_sqrtf (float x) { return (x); }
float F_tanf (float x) { return (x); }

/*
 * Additional Digital functions
 */
double acosd (double x) { return (x); }
double asind (double x) { return (x); }
double atand (double x) { return (x); }
double atand2 (double x, double y) { return (x); }
double cosd (double x) { return (x); }
double cot (double x) { return (x); }
double cotd (double x) { return (x); }
double log2 (double x) { return (x); }
double nint (double x) { return (x); }
double powi (double x, int i) { return (x); }
double sind (double x) { return (x); }
double tand (double x) { return (x); }

float acosdf (float x) { return (x); }
float asindf (float x) { return (x); }
float atand2f (float x, float y) { return (x); }
float atandf (float x) { return (x); }
float cosdf (float x) { return (x); }
float cotdf (float x) { return (x); }
float cotf (float x) { return (x); }
float log2f (float x) { return (x); }
float nintf (float x) { return (x); }
float powif (float x, int y) { return x; }
float sindf (float x) { return (x); }
float tandf (float x) { return (x); }

int powii (int x, int y) { return x; }







