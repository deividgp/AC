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
#ifndef	_SYS_CDROM_INCLUDE
#define	_SYS_CDROM_INCLUDE	1
#ifdef __cplusplus
extern "C" {
#endif

/*	
 *	@(#)$RCSfile: cdrom.h,v $ $Revision: 4.3.12.4 $ (DEC) $Date: 1995/01/25 18:50:52 $
 */ 
/*
 * <sys/cdrom.h> is specified by the Rock Ridge Interchange Protocol (rev 1.09)
 *
 * <cdfs/rrip.h> has the Rock Ridge stuff.
 * <cdfs/xcdr.h> has the XCDR stuff.
 */
#include <cdfs/rrip.h>
#include <cdfs/xcdr.h>

#ifndef _KERNEL
/*
 * Other stuff:
 */
#include <sys/time.h>

/* these are not specified by either XCDR or RRIP: */
void cdfs_tounixdate(time_t *,int,int,int,int,int,int,int);
time_t rrip_convert_tf_ts(int, signed char *);
time_t cdfs_longdate(signed char *);
void xcdr_pvd(const char *, struct iso9660_pvd *);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _SYS_CDROM_INCLUDE */
