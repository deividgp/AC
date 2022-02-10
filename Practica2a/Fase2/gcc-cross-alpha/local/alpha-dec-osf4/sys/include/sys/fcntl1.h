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
 * @(#)$RCSfile: fcntl1.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1997/02/25 15:06:52 $
 */

#ifndef _SYS_FCNTL1_H_
#define _SYS_FCNTL1_H_


#include <standards.h>
#include <sys/types.h>
#include <sys/time.h>


/*
 * Command packet definitions for F_GETTIMES, F_SETTIMES and F_RWREFS.
 */

struct attr_timbuf {
        struct timeval  atime;  /* access time                  */
        struct timeval  mtime;  /* file data modification time  */
        struct timeval  ctime;  /* file attribute change time   */
};

struct frefs {
        u_short  readers;       /* number of read refs          */
        u_short  writers;       /* number of write refs         */
};

#endif  /* _SYS_FCNTL1_H_ */
