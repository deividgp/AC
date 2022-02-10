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

#pragma	ident	"@(#)$RCSfile: volklog.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/01/31 20:43:47 $"

/* @(#)src/common/uts/io/vxvm/volklog.h	5.3 16 Mar 1993 02:07:30 - Copyright (c) 1993 VERITAS Software Corp. */
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

/*
 * sys/volkern.h - volume manager kernel only header file
 */

#ifndef _SYS_VOLKLOG_H
#define _SYS_VOLKLOG_H

/*
 * The following structure defines the kernel image of the disk group log,
 * which is the list of log blocks for a disk group. The dgl_blk array
 * contains the sector-sized network independant form of the log block as it
 * appears on disk. The format of the block is as follows:
 *
 *		dgl_blk on intel contents:
 *		_________________________________________ __
 *		|	0x000 magic number		|  |
 *		|---------------------------------------|  |
 *		|	0x004 transaction ID		|   - VOL_KLOGENT_SIZE
 *		|---------------------------------------|  |
 *		|	0x00c sequence number		|  |
 *		|---------------------------------------|  |
 *		|	0x010 klog length		|  |
 *		|---------------------------------------|  |
 *		|	0x014 klog blk #		|  |
 *		|---------------------------------------| --
 *		|	0x018 log entry [0]		|
 *		|	0x030 log entry [1]		|
 *		|		.			|
 *		|		.			|
 *		|		.			|
 *		|	0x1e0 log entry [NLOGENT - 1]	|
 *		-----------------------------------------
 *
 */

#define VOL_KLOG_MAGIC	       (('K' << 24) | \
				('L' << 16) | \
				('O' << 8) | \
				('G'))

/* Following are the valid log entry types */
enum vol_klogent_type {
	MIN_KLOG_TYPE_ENT,
	VOL_KLOG_PLEXDET,	/* plex detach log entry */
	VOL_KLOG_VOLDIRTY,	/* volume open log entry */
	VOL_KLOG_COMMIT,	/* transaction commit log entry */
	VOL_KLOG_BCLERR,	/* volume BCL has failed - overrides VOLDIRTY */
	MAX_KLOG_TYPE_ENT
};

/*
 * The following defines the maximum entry size for the log entries based
 * on the largest (abort) record size. Generally this will be 21 bytes
 * padded to a 4-byte boundary for a total of 24 bytes.
*/
#define VOL_KLOGENT_SIZE	\
	(((1 + VOL_RID_BYTES + VOL_RID_BYTES +  VOL_ULONG_BYTES) + 4) & \
	~(4 - 1))

/*
 * NLOGENT is the number of entries for each log block based on the overhead
 * of the header rounded to the log entry size.
 */
#define NLOGENT	\
	((NBPSCTR - VOL_KLOGENT_SIZE) / VOL_KLOGENT_SIZE)

#endif	/* _SYS_VOLKLOG_H */
