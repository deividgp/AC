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
 *	@(#)$RCSfile: ip_var.h,v $ $Revision: 4.4.41.2 $ (DEC) $Date: 1998/03/31 21:15:00 $
 */ 
/*
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
 * Copyright (c) 1982, 1986 Regents of the University of California.
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
 *	Base:	ip_var.h	7.6 (Berkeley) 9/20/89
 *	Merged:	ip_var.h	7.7 (Berkeley) 6/28/90
 */
#ifndef	_NETINET_IP_VAR_H
#define	_NETINET_IP_VAR_H

#ifndef BYTE_ORDER
#include <machine/endian.h>
#endif

/*
 * Overlay for ip header used by other protocols (tcp, udp).
 * For 64-bit pointers, the next and previous fields are stored in the
 * mbuf header instead of in the ipovly.
 */
struct ipovly {
#ifdef __alpha
	u_int	fill[2];		/* filler */
#else /* __alpha */
	caddr_t	ih_next, ih_prev;	/* for protocol sequence q's */
#endif /* __alpha */
	u_char	ih_x1;			/* (unused) */
	u_char	ih_pr;			/* protocol */
	u_short	ih_len;			/* protocol length */
	struct	in_addr ih_src;		/* source internet address */
	struct	in_addr ih_dst;		/* destination internet address */
};

/*
 * Ip reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
#ifdef __alpha

struct ipq {
	struct	ipq *next,*prev;	/* to other reass headers */
	struct	ipasfrag *ipq_next;	/* to ip headers of fragments */
	struct	ipasfrag *ipq_prev;	/*       ""         ""	      */
	u_char	ipq_ttl;		/* time for reass q to live */
	u_char	ipq_p;			/* protocol of this fragment */
	u_short	ipq_id;			/* sequence id for reassembly */
	struct	in_addr ipq_src,ipq_dst;
};

#else

struct ipq {
	struct	ipq *next,*prev;	/* to other reass headers */
	u_char	ipq_ttl;		/* time for reass q to live */
	u_char	ipq_p;			/* protocol of this fragment */
	u_short	ipq_id;			/* sequence id for reassembly */
	struct	ipasfrag *ipq_next,*ipq_prev;
					/* to ip headers of fragments */
	struct	in_addr ipq_src,ipq_dst;
};

#endif /* __alpha */

/*
 * Ip header, when holding a fragment.
 *
 * Note: ipf_next must be at same offset as ipq_next above
 */
#ifdef __alpha

struct	ipasfrag {
	struct	ip	 *xxx;		/* place holder */
	struct	ip	 *ipf_ip;	/* pointer to the real ip */
	struct	ipasfrag *ipf_next;	/* next fragment */
	struct	ipasfrag *ipf_prev;	/* previous fragment */
};

#else

struct	ipasfrag {
#if	defined(_KERNEL) || defined(_NO_BITFIELDS) || (__STDC__ == 1)
	u_char	ip_vhl;
#else
#if BYTE_ORDER == LITTLE_ENDIAN 
	u_char	ip_hl:4,
		ip_v:4;
#endif
#if BYTE_ORDER == BIG_ENDIAN 
	u_char	ip_v:4,
		ip_hl:4;
#endif
#endif
	u_char	ip_tos;	
	u_short	ip_len;
	u_short	ip_id;
	short	ip_off;
	u_char	ip_ttl;
	u_char	ip_p;
	u_short	ip_sum;
	struct	ipasfrag *ipf_next;	/* next fragment */
	struct	ipasfrag *ipf_prev;	/* previous fragment */
};

#endif /* __alpha */

#define IPFRAG_MFF	0x10

/*
 * Structure stored in mbuf in inpcb.ip_options
 * and passed to ip_output when ip options are in use.
 * The actual length of the options (including ipopt_dst)
 * is in m_len.
 */
#define MAX_IPOPTLEN	40

struct ipoption {
	union {
		struct	in_addr ipopt_dest;	/* first-hop dst if source routed */
		int	ipopt_len;
	} ipopt ;  
#define ipopt_dst	ipopt.ipopt_dest
#define oplen 		ipopt.ipopt_len 
	char	ipopt_list[MAX_IPOPTLEN];	/* options proper */
};

#ifdef _KERNEL
/*
 * Structure attached to inpcb.ip_moptions and
 * passed to ip_output when IP multicast options are in use.
 */
struct ip_moptions {
	struct	ifnet *imo_multicast_ifp; /* ifp for outgoing multicasts */
	u_char	imo_multicast_ttl;	/* TTL for outgoing multicasts */
	u_char	imo_multicast_loop;	/* 1 => hear sends if a member */
	u_short	imo_num_memberships;	/* no. memberships this socket */
	struct	in_multi *imo_membership[IP_MAX_MEMBERSHIPS];
};
#endif

/* Source route holding structure (moved here from ip_input.c) */
struct ip_srcrt {
	struct	in_addr dst;			/* final destination */
	char	nop;				/* one NOP to align */
	char	srcopt[IPOPT_OFFSET + 1];	/* OPTVAL, OLEN and OFFSET */
	struct	in_addr route[MAX_IPOPTLEN/sizeof(struct in_addr)];
};

#include <netinet/ip_stat.h>

struct ipreass {
	int		ipr_percent;		/* % buffer space avail for reass */
	unsigned long	ipr_max;		/* max space available for reass */
	unsigned long	ipr_inuse;		/* space currently used for reass */
	int		ipr_drops;		/* # of drops due to buffer unavail */
};
#define IPR_DEFAULT	20		/* use 20% by default */

#ifdef _KERNEL
ndecl_lock_data(extern, ip_frag_lock)
#define IPFRAG_LOCKINIT()	ulock_setup(&ip_frag_lock, ip_frag_li, TRUE)
#define IPFRAG_LOCK()		ulock_write(&ip_frag_lock)
#define IPFRAG_UNLOCK()		ulock_done(&ip_frag_lock)

/* flags passed to ip_output as fourth parameter */
#define	IP_FORWARDING		0x1		/* most of ip header exists */
#define IP_NHMTU                0x2             /* provide next-hop mtu */
#define	IP_ROUTETOIF		SO_DONTROUTE	/* bypass routing tables */
#define	IP_ALLOWBROADCAST	SO_BROADCAST	/* can send broadcast packets */

extern	CONST u_char inetctlerrmap[];
extern	struct	ipstat	ipstat;
extern	struct	ipq	ipq;			/* ip reass. queue */
extern	u_int	ip_id;				/* ip packet ctr, for ids */
#if NETSYNC_LOCK
#define GET_NEXT_IP_ID() \
	(htons((u_short)((lockmode == 0) ? ip_id++ : atomic_incl(&ip_id))))
#else
#define GET_NEXT_IP_ID() (htons((u_short)ip_id++))
#endif /* NETSYNC_LOCK */

#endif /* _KERNEL */
#endif /* _NETINET_IP_VAR_H */
