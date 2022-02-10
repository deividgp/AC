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
 * @(#)$RCSfile: fifo.h,v $ $Revision: 1.1.4.7 $ (DEC) $Date: 1995/12/19 20:37:13 $
 */
/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#ifndef _SYS_FIFO_H_
#define _SYS_FIFO_H_

#ifdef KERNEL
#ifdef __cplusplus
extern "C" {
#endif

struct fifo_bufhdr {
	struct fifo_bufhdr *fb_next;
	char fb_data[1];
};


/*
 *	Fifo information structure.
 */
struct fifoinfo {
	int	fifobuf,	/* max # bytes stored in a fifo */
		fifomax,	/* largest size of a single write to a fifo */
		fifobsz,	/* # of data bytes in each fifo data buffer */
		fifomnb;	/* max # bytes reserved for all fifos */
};

struct fifoinfo	fifoinfo;

#define DEFAULT_PIPE_SIZE           65536
#define DEFAULT_PIPE_MAX               ~0
#define DEFAULT_PIPE_BSZ             8192
#define DEFAULT_PIPE_MNB    (8192 * 10000)

#define PIPE_SIZE (fifoinfo.fifobuf)
#define PIPE_MAX  (fifoinfo.fifomax)
#define PIPE_BSZ  (fifoinfo.fifobsz)
#define PIPE_MNB  (fifoinfo.fifomnb)

#ifdef __cplusplus
}
#endif
#endif /* KERNEL */

#endif /* _SYS_FIFO_H_ */
