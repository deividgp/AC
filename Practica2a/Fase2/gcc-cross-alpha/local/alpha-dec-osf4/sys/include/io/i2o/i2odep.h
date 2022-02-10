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
 * @(#)$RCSfile: i2odep.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1998/10/02 15:28:59 $
 */

/****************************************************************************

 I2O SIG All rights reserved.

**************************************************************************/

/*
 * This template provides place holders for architecture and compiler
 * dependencies. 
 */

#ifndef __INCi2odeph
#define __INCi2odeph

#define I2ODEP_REV 1_5_5

#define USED_IN_D_UNIX_I2O 1

#ifndef USED_IN_D_UNIX_I2O
/*
 * Pragma macros. These are to assure appropriate alignment between
 * host/IOP as defined by the I2O Specification. Each one of the shared
 * header files includes these macros.
 */

#define PRAGMA_ALIGN_PUSH   <xxx>
#define PRAGMA_ALIGN_POP    <xxx>
#define PRAGMA_PACK_PUSH    <xxx>
#define PRAGMA_PACK_POP     <xxx>

#endif /* !USED_IN_D_UNIX_I2O */

/* Setup the basics */

typedef    char   	S8;
typedef    short  	S16;

#ifndef U8
typedef    unsigned char  U8;
#endif
#ifndef U16
typedef    unsigned short U16;
#endif

#ifndef U32
typedef    unsigned int	U32;
#endif
typedef    int		S32;


/* Bitfields */

typedef    U32  BF;


/* VOID */

#ifndef __VOID
typedef    void  VOID;
#define __VOID
#endif

#ifndef USED_IN_D_UNIX_I2O
/* Boolean */

#ifndef __BOOL
#define __BOOL

typedef <xxx>  BOOL;
#endif /* __BOOL */
#endif /* !USED_IN_D_UNIX_I2O */

/* NULL */

/* #define NULL  0 */

#endif /* __INCi2odeph */
