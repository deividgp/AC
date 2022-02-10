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

#pragma	ident	"@(#)$RCSfile: volkinc.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1995/01/31 20:43:38 $"

/* @(#)src/common/uts/io/vxvm/volkinc.h	6.2 05 Jun 1993 23:43:19 - Copyright (c) 1993 VERITAS Software Corp. */
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
 * First define some lint needed things.
 */

#if defined(lint)

extern int	vol_global_zero;
#define ZERO	vol_global_zero
#if defined(STATIC)
#undef STATIC
#endif /* STATIC */
#define STATIC	static

#else

#define ZERO	0

#endif /* lint */

/*
 * Common includes for Volume Manager kernel source
 */

#if defined(SYSV_4_0) || defined(NATIVE)
/*
 * Use pre-Density includes
 */
#include        "sys/types.h"
#include	"sys/systm.h"
#include        "sys/time.h"
#include        "sys/uio.h"
#include        "sys/file.h"
#include        "sys/open.h"
#include        "sys/cred.h"
#include        "sys/ddi.h"
#include        "sys/conf.h"
#include        "sys/param.h"
#include        "sys/errno.h"
#include        "sys/cmn_err.h"
#include        "sys/kmem.h"
#include        "sys/debug.h"
#include        "sys/proc.h"
#include        "sys/user.h"
#include	"sys/vnode.h"
#include        "vol.h"
#include	"vollocal.h"
#include        "vollocks.h"
#if defined(TED_ACTIVE)
#include	"volted.h"
#endif /* TED_ACTIVE */
#include        "volkint.h"
#include        "volpack.h"
#include        "voltrace.h"
#include        "volkern.h"
#include        "volklog.h"
#include        "volblog.h"
#include        "vm/vm_hat.h"
#include        "vm/page.h"
#include        "volproto.h"

#ifdef VXVM_LOADABLE
#include	"sys/moddefs.h"
#endif /* VXVM_LOADABLE */

#include        "stddef.h"
#ifdef MP
#include        "sys/mp/mpmacros.h"
#endif /* MP */
#if defined(TED_ACTIVE)
#include        "sys/ted.h"
#endif /* TED_ACTIVE */

#else /* ! SYSV_4_0 */

#ifdef __alpha

#ifdef VXVM_DEBUG
#undef biodone
#define biodone(bp) vol_biodone(bp)
#endif /* VXVM_DEBUG */

#include        <sys/types.h>
#include        <sys/uio.h>
#include        <sys/file.h>
#include        <sys/param.h>
#include        <sys/systm.h>
#include        <sys/conf.h>
#include        <sys/errno.h>
#include        <sys/cmn_err.h>
#include        <sys/signal.h>
#include        <sys/proc.h>
#include        <sys/user.h>
#include        <sys/cred.h>
#include        <sys/vmmac.h>
#include        <sys/ioctl.h>
#include        <sys/disklabel.h>
#include        <sys/buf.h>
#include        <sys/vnode.h>
#include        <sys/lock_types.h>
#include        <sys/syslog.h>
#include        <sys/open.h>            /* for OTYP* definitions */

#include        <cpus.h>
#include        <machine/cpu.h>
#include        <vm/vm_map.h>
#include        <kern/kalloc.h>
#include        <kern/threadcall.h>
#include        <kern/sched_prim.h>

#if SEC_BASE
#include <sys/security.h>
#endif /* SEC_BASE */

#include        <sys/vol.h>
#include        <sys/vollocks.h>
#if defined(TED_ACTIVE)
#include        <sys/volted.h>
#include        <sys/ted.h>
#include        <sys/tedproto.h>
#endif /* TED_ACTIVE */
#include        <sys/volkint.h>
#include        <sys/volpack.h>
#include        <sys/voltrace.h>
#include        <sys/volkern.h>
#include        <sys/volklog.h>
#include        <sys/volblog.h>
#include        <sys/volproto.h>
#include        <sys/vollocal.h>

#else /* !__alpha */
#include	<stddef.h>
#include	<util/types.h>
#include	"svc/systm.h"
#include	<svc/time.h>
#include	<io/uio.h>
#include	<fs/file.h>		/* vol.c plex.c */
#include	<io/open.h>
#include	<proc/cred.h>
#include	<io/ddi.h>
#include	<io/conf.h>
#include	<util/param.h>
#include	<svc/errno.h>
#include	<util/cmn_err.h>
#include	<mem/kmem.h>
#include	<util/debug.h>
#include	<proc/proc.h>		/* vol.c */
#include	<proc/user.h>		/* vol.c */
#include	<fs/vnode.h>
#include	<vm/page.h>		/* vol.c */

#include	"vol.h"
#include	"vollocal.h"
#include	"vollocks.h"
#if defined(TED_ACTIVE)
#include	"volted.h"
#endif /* TED_ACTIVE */
#include	"volkint.h"
#include	"volpack.h"
#include	"voltrace.h"		/* vol.c only */
#include	"volkern.h"
#include	"volblog.h"
#include	"volklog.h"
#include	"volproto.h"

#ifdef VXVM_LOADABLE
#include	<util/mod/moddefs.h>
#endif /* VXVM_LOADABLE */

#if defined(TED_ACTIVE)
#include	<sys/ted.h>
#include	<sys/tedproto.h>
#include	<util/ipl.h>
#endif /* TED_ACTIVE */
#endif /* __alpha */

#endif /* SYSV_4_0 */
