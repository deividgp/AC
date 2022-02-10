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
 *	@(#)$RCSfile: net_globals.h,v $ $Revision: 4.2.13.4 $ (DEC) $Date: 1998/06/26 04:10:00 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0.1
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 *	File:	net/net_globals.h
 *
 *	Revision History:
 *
 * 5-June-91	Heather Gray
 *	OSF 1.0.1 patch.
 *
 * 5-May-91	Ron Widyono
 *	Don't enable NETSYNC_LOCK whenever RT_PREEMPT is selected.  This is
 *	temporary, until we find out exactly what is wrong with LOCK
 *	synchronization in the network.
 *
 */
/*
 * Global #defines for OSF/1 networking.
 *
 * Ugly as this file is, it makes the code a lot cleaner!
 *
 * The following major #defines are supported:
 *	NCPUS		number of processors
 *	NNETTHREADS	pseudo-device specifying threads
 *	UNIX_LOCKS	configure with locking
 *	VAGUE_STATS	no locking around stats
 *
 * These defines yield the following internal defines:
 *	NETNCPUS	number of processors doing network
 *	NETSYNC_SPL	do process synch with spl's (may co-exist w/locks)
 *	NETSYNC_LOCK	do process sync with locks (may co-exist w/spl)
 *	NETISR_THREAD	do isr's via thread (else via software interrupt)
 *	NETSYNC_LOCKTEST	turn on extra lock debugging (UNIX, too)
 *
 * Current prerequisites (not enforced!):
 *	One or both of NETSYNC_SPL && NETSYNC_LOCK
 *	NETSYNC_LOCK requires NETISR_THREAD
 *	UNIX requires NETSYNC_SPL
 */

#ifndef	_NET_GLOBALS_H_
#define _NET_GLOBALS_H_

#include <cpus.h>
#include <unix_locks.h>
#include <vague_stats.h>
#include <rt_preempt.h>

/*
 * These are default settings. Either or both of locking and spl are valid
 * for 1 or more cpus. However, recommend locks for multis, non-locks for unis.
 * The thread decision is dependent on several things. To configure both
 * sockets and streams to use softnets requires locore or hardware support.
 */
#define NETNCPUS	NCPUS
#define NETSYNC_LOCK	(UNIX_LOCKS)	/* locks needed in extended kernel */
#define NETSYNC_SPL	0		/* spls not needed because netisrs */
#define NETISR_THREAD	1		/*  are always executed by threads */

#if	NETSYNC_LOCK	/* Configure locking */

#if	MACH

#include "kern/lock.h"
#include "kern/spl.h"
#include "kern/assert.h"
#include "kern/queue.h"
#include "sys/lock_types.h"
#include <mach_ldebug.h>
#define LOCK_ASSERTL_DECL
#define LOCK_ASSERTL(string, cond)	ASSERT(cond)
#define LOCK_ASSERT(string, cond)	ASSERT(cond)

#define NETSYNC_LOCKTEST (DEBUG || MACH_LDEBUG)
#define LOCK_NETSTATS	 (VAGUE_STATS == 0)

#else	/* UNIX */

#include "net/net_unixlock.h"
typedef int	spl_t;
#define LOCK_ASSERTL_DECL		static char _file_[] = __FILE__; \
					extern char _net_lock_format_[];
#define LOCK_ASSERTL(string, cond)	{ if(!(cond)) printf(_net_lock_format_,\
						string, _file_, __LINE__); }
#define LOCK_ASSERT(string, cond)	{ if(!(cond)) printf("\t%s\n",string); }
#define NETSYNC_LOCKTEST DEBUG
#define LOCK_NETSTATS	 1

#endif

#else	/* !NETSYNC_LOCK */
#define LOCK_ASSERTL_DECL
#define LOCK_ASSERTL(string, cond)
#define LOCK_ASSERT(string, cond)
#define NETSYNC_LOCKTEST	0
#define LOCK_NETSTATS		0
#if	MACH
#include "kern/spl.h"
#else
typedef int	spl_t, lock_data_t, *lock_t;
#endif

#endif

#if	defined(_KERNEL) && NETSYNC_LOCK
#define ndecl_lock_data(class,name)	class lock_data_t name;
#define ndecl_lock_info(class,name)	class struct lockinfo *name;
#else
#define ndecl_lock_data(class,name)
#define ndecl_lock_info(class,name)
#endif

#if	NETSYNC_SPL	/* Do spl() synch */
#define NETSPL_DECL(s)		spl_t s;
#define NETSPL(s,level)		s = spl##level()
#define NETSPLX(s)		splx(s)
#else			/* Don't spl() synch */
#define NETSPL_DECL(s)
#define NETSPL(s,level)
#define NETSPLX(s)
#endif

#if	LOCK_NETSTATS
#define NETSTAT_LOCKINIT(lockp, lip) simple_lock_setup(lockp, lip)
#define NETSTAT_LOCK(lockp)	simple_lock(lockp)
#define NETSTAT_UNLOCK(lockp)	simple_unlock(lockp)
#else
#define NETSTAT_LOCKINIT(lockp, lip)
#define NETSTAT_LOCK(lockp)
#define NETSTAT_UNLOCK(lockp)
#endif

#define NETSTAT_INC(count) current_processor()->count++
#define NETSTAT_DEC(count) current_processor()->count--
#define NETSTAT_ADD(count, n) current_processor()->count += n 
ndecl_lock_info(extern, ifnet_li)

/* ANSI-C compatibility */
#ifdef	__STDC__
#ifndef CONST
#define CONST		const
#endif /* CONST */
#define VOLATILE	volatile
#else
#define CONST
#define VOLATILE
#endif

/* Global function prototypes */
#include "sys/types.h"
#include "net/proto_net.h"
#include "net/proto_uipc.h"

#endif	/* _NET_GLOBALS_H_ */
