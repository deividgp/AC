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
 *	@(#)$RCSfile: netisr.h,v $ $Revision: 4.2.43.3 $ (DEC) $Date: 1998/11/02 21:24:13 $
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
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
 * Copyright (c) 1980, 1986, 1989 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	netisr.h	7.5 (Berkeley) 4/22/89
 *	Merged:	netisr.h	7.6 (Berkeley) 6/28/90
 */

#ifndef	_NET_NETISR_H
#define	_NET_NETISR_H

/*
 * The networking code is in separate kernel threads or in software
 * interrupts. When running in threads, all events are delivered in
 * thread context, at splnet() or spl0() depending on lock configuration.
 * When running in software interrupts, events are delivered at splnet()
 * or splsoftclock().
 *
 * Clients of the isr framework use a "netisr" structure to
 * enqueue events and maintain active status. Some default
 * structures are defined globally (especially those used in
 * non-local contexts e.g. packet receive), others may be
 * registered with netisr_add(). See net/netisr.c.
 */

struct netisr {
	struct	netisr *next, *prev;	/* Link in {in}active isr list */
	int	active;			/* Softnet active count */
	int	pending;		/* Interrupt pending on queue */
	void	(*isr)(void);		/* Isr to process input */
	struct	ifqueue *ifq;		/* Queue to receive packets, or NULL */
	struct	domain *dom;		/* Domain isr belongs to, or NULL */
	unsigned char flags;		/* Flags */
	unsigned char use;  
#define ISRF_INCHDR	1		/*   Include datalink */
	short	unit;			/* use count for this netisr */
	int	id;			/* Integer id */
	u_int	events;			/* Event count */
	u_int	wakeups;		/* Wakeup count */
	u_int	extras;			/* Wakeups with nothing to do */
	u_int	noserver;		/* No servers ready - NETISR_THREAD */
	u_int	block;			/* cnt threads blocked-NETISR_THREAD */
	u_int	maxactive;		/* max # concurrent threads active */
};

/*
 * Isr's may be used to deliver data to protocols, or simply events.
 */

#define NETISR_WILD	0	/* Copy of all packets */
#define NETISR_OTHER	1	/* Packets otherwise tossed (->dlpi)*/
#define	NETISR_ARP	2	/* ARP packets */
#define	NETISR_IP	3	/* IP packets */
#define	NETISR_RTMSG	4	/* Internal routing messages */
#define	NETISR_ISO	5	/* ISO packets */

#define	NETISR_MB	6	/* Mbuf/mblk event */
#define NETISR_STREAMS	7	/* Streams scheduler */
#define NETISR_ATMRTUPT	8	/* ATM IP route update */
#define NETISR_STRWELD	9	/* Streams "weld" */
#define NETISR_PFFAST	10	/* Sockets fasttimeout */
#define NETISR_PFSLOW	11	/* Sockets slowtimeout */
#define NETISR_IFSLOW	12	/* Sockets interface watchdog */
#define NETISR_ARPTMO	13	/* Sockets ARP timer */

#define NETISR_EVL	14	/* X.25 event logging */
#define NETISR_DLO	15	/* used for node 0 in DECnet */
#define	NETISR_DN	16	/* DECnet packets */
#define	NETISR_DLI	17	/* DLI packets */
#define	NETISR_LAT	18	/* LAT packets */
#define NETISR_WDD	19	/* WAN packets */
#define NETISR_NFSTMO	20	/* NFS timer */

#define NETISR_SRTMO	21	/* Token Ring S.R. timer */
#define NETISR_X25	22	/* X.25 packets */
#define NETISR_HDLC	23	/* HDLC packets */
#define NETISR_CTF	24	/* CTF messages */
#define NETISR_AAL	25	/* "Native" ATM API packets */
#define NETISR_IPV6	26	/* IPV6 packets */
#define NETISR_NETRAIN	27	/* Netrain failure detection code */
#define NETISR_NETDEV	28	/* network driver interrupt threads */

#define NETISR_MAX	40	/* maximum acticipated number of netisr id's */

/* The number of preallocated isr's is arbitrary, but
 * should be large enough for the above predefines. */
#define NNETISR		NETISR_MAX

#ifdef	_KERNEL

#if	NETISR_THREAD

#include "kern/queue.h"
#include "kern/thread.h"
#include "kern/sched_prim.h"

/*
 * Servers of the netisr framework export themselves via their
 * thread structure.
 */

extern thread_t netisr_servers;
extern int netisrwakeupthreshold;
#define NETISR_PERSIST 100

#define schednetisr_nospl(num) do {					\
	struct netisr *netisr;						\
	NETISR_LOCK();							\
	if (netisr = which_netisr(num)) {				\
	    ++netisr->pending;						\
	    if((netisr->active + netisr->pending) == 1)			\
		reminsque(netisr, netisr_active.prev);			\
	    if (netisr_active.block){					\
		netisr_active.block=0;					\
		if(thread_wakeup_one((vm_offset_t)&netisr_servers)==0){	\
			netisr_active.noserver++;			\
	    	}							\
	    }								\
	}								\
	NETISR_UNLOCK();						\
} while (0)

/*
 * This schedules a netisr thread to run.  The argument is a pointer
 * to a netisr struct, rather than an isr num.  The netisr pointer is
 * passed in to avoid the which_netisr() overhead.  Callers to this
 * routine are required to be at splimp().
 */
#define schednetisr_isr(netisr) do {					\
	++netisr->pending;			/*fuzzy*/		\
	if (netisr->active <= 1) { 					\
		NETISR_LOCK();						\
		netisr->active++;					\
		if (netisr->active == 1) {	\
			reminsque(netisr, netisr_active.prev);		\
		} else {						\
			netisr->active--;				\
		}							\
		NETISR_UNLOCK();					\
	} 								\
	/* safe to do this without a lock, the worst case is we do	\
	 * a useless wakeup if some other thread comes through here	\
	 * at the same moment. */					\
	if(netisr_active.block){					\
		netisr_active.block=0;					\
	   	if(thread_wakeup_one((vm_offset_t)&netisr_servers)==0) {\
			netisr_active.noserver++;			\
		}							\
	}								\
} while (0)

/*
 * This schedules a network driver thread to run a driver's
 * interrupt handler.  The argument is a pointer to a netisr struct,
 * rather than an isr num.  The netisr pointer is saved in each
 * driver softc. Callers to this routine are required to be at splimp().
 * This is the same as above but without netisrwakeupthreshold, thus,
 * only 1 of these threads (per driver) can run at a time.
 */
#define schednetisr_netdev(netisr) do {					\
	++netisr->pending;			/*fuzzy*/		\
	if (netisr->active <= 1) { 					\
		NETISR_LOCK();						\
		netisr->active++;					\
		if (netisr->active == 1) {	\
			reminsque(netisr, netisr_active.prev);		\
		} else {						\
			netisr->active--;				\
		}							\
		NETISR_UNLOCK();					\
	} 								\
	/* safe to do this without a lock, the worst case is we do	\
	 * a useless wakeup if some other thread comes through here	\
	 * at the same moment. */					\
	if (netisr_active.block != 0) {					\
	        netisr_active.block=0;					\
		if(thread_wakeup_one((vm_offset_t)&netisr_servers)==0) {\
			netisr_active.noserver++;			\
		}							\
	}								\
} while (0)

#else	/* NETISR_THREAD */

#if defined(vax) || defined(tahoe)
#include "machine/mtpr.h"
#define setsoftnet()    mtpr(SIRR, 12)
#else
extern void setsoftnet(void);
#endif

#define schednetisr_nospl(num) do {				\
	struct netisr *netisr;					\
	NETISR_LOCK();						\
	if ((netisr = which_netisr(num)) &&			\
	    (++netisr->pending + netisr->active) == 1) {	\
		reminsque(netisr, netisr_active.prev);		\
		setsoftnet();					\
	}							\
	NETISR_UNLOCK();					\
} while (0)

#endif	/* NETISR_THREAD */

#define schednetisr(num) do {	\
	int _s = splimp();	\
	schednetisr_nospl(num);	\
	splx(_s);		\
} while (0)

extern struct netisr netisr_active, netisr_table[];

#define which_netisr(num)	((unsigned)(num) < NNETISR ? \
					&netisr_table[num] : \
					netisr_lookup(num))

#if	NETSYNC_LOCK
extern simple_lock_data_t	netisr_slock;
#define NETISR_LOCKINIT()	simple_lock_setup(&netisr_slock, netisr_li)
#define NETISR_LOCK()		simple_lock(&netisr_slock)
#define NETISR_UNLOCK()		simple_unlock(&netisr_slock)
#else
#define NETISR_LOCKINIT()
#define NETISR_LOCK()
#define NETISR_UNLOCK()
#endif
#endif
#endif
