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

#pragma	ident	"@(#)$RCSfile: volblog.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/01/31 20:43:20 $"

/* @(#)src/common/uts/io/vxvm/volblog.h	5.2 16 Mar 1993 02:06:52 - Copyright (c) 1993 VERITAS Software Corp. */
/*
 * Copyright(C)1993 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 * 
 *               RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *               VERITAS SOFTWARE
 * 4800 GREAT AMERICA PARKWAY, SANTA CLARA, CA 95054
 */
/*
 * Alpha change log
 *
 * 09-28-93	Wai Yim
 * Merged alpha port with vxvm1.2.1 source.
 *
 */

#ifndef _SYS_VOLBLOG_H
#define _SYS_VOLBLOG_H

/*
 * structures for block change logging
 *
 * A block change log is written to each plex with an enabled logging
 * subdisk whenever writes are sent to a volume with a logging type of
 * LOGBLKNO.  This log consists of a header that includes a
 * monotonically increasing serial number, and a magic number for
 * validation purposes.  The remainder of the log (up to the end of
 * a disk sector) is composed of entries defining the beginning offset
 * and the extent of disk write requests that were received by the
 * disk driver, but not yet completed, at the time of the log write.
 */

/*
 * header for block change log
 */

struct bloghdr {
	ulong_t	vb_magic;		/* magic number */
	ulong_t	vb_serial_lo;		/* serial number, low part */
	ulong_t	vb_serial_hi;		/* serial number, high part */
};

/* magic number expected in vb_magic */
#define BLOG_MAGIC	('B' << 24 | 'L' << 16 | 'O' << 8 | 'G')

/*
 * structure of an entry in the block change log
 */

struct blogent {
	voff_t	vb_start;		/* byte offset to start of region */
	voff_t	vb_len;			/* byte length of region */
};

union blogent_align {
	struct bloghdr	a;
	struct blogent	b;
};

#define NBLOGENT \
	((NBPSCTR - sizeof(union blogent_align)) / sizeof(struct blogent))

/*
 * the block change log itself
 */

struct volblog {
	struct bloghdr vb_hdr;		/* log header */
	struct blogent vb_ent[NBLOGENT];/* log entries */
};

#endif	/* _SYS_VOLBLOG_H */
