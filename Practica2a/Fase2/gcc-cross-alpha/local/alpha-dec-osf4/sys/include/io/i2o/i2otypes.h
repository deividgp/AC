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
/*
 * @(#)$RCSfile: i2otypes.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1998/10/02 15:29:13 $
 */

/****************************************************************************

 I2O SIG All rights reserved.

**************************************************************************/

#ifndef __INCi2otypesh
#define __INCi2otypesh

#define I2OTYPES_REV 1_5_5

/* include architecture/compiler dependencies */

#include <io/i2o/i2odep.h>

/* 64 bit defines */

typedef struct _S64 {
   U32                         LowPart;
   S32                         HighPart;
} S64;

#ifndef U64
typedef struct _U64 {
   U32                         LowPart;
   U32                         HighPart;
} U64;
#endif

/* Pointer to Basics */

typedef    VOID                *PVOID;
typedef    S8                  *PS8;
typedef    S16                 *PS16;
typedef    S32                 *PS32;
typedef    S64                 *PS64;

/* Pointer to Unsigned Basics */

typedef    U8                  *PU8;
typedef    U16                 *PU16;
typedef    U32                 *PU32;
typedef    U64                 *PU64;

/* misc */

typedef S32             I2O_ARG;
typedef U32             I2O_COUNT;
typedef U32             I2O_USECS;
typedef U32             I2O_ADDR32;
typedef U32             I2O_SIZE;

#endif /* __INCi2otypesh */
