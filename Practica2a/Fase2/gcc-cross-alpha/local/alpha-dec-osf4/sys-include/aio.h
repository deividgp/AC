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
 *	@(#)$RCSfile: aio.h,v $ $Revision: 4.2.18.2 $ (DEC) $Date: 1996/08/07 20:34:00 $
 */

#ifndef __AIO_H
#define __AIO_H

#include <standards.h>

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)

#ifdef __cplusplus
extern "C" {
#endif

/* aio_close is for source-level compatibility */
#define aio_close close

#include <sys/sysaio.h>
#include <sys/timers.h> /* need timespec definition */

int aio_read __((struct aiocb *));
int aio_write __((struct aiocb *));
int lio_listio __((int, struct aiocb *[], int, struct sigevent *));
int aio_cancel __((int, struct aiocb *));
int aio_suspend __((const struct aiocb *[], int, const struct timespec *));
ssize_t aio_return __((struct aiocb *));
int aio_error __((const struct aiocb *));
int aio_fsync __((int, struct aiocb *));
int aio_group_completion_np __((void));
int aio_results_np __((aio_completion_t [], int,
		       const struct timespec *, int));
#ifdef __cplusplus
}
#endif
#endif /*_POSIX_C_SOURCE*/
#endif /*__AIO_H*/
