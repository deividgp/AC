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
 *	@(#)$RCSfile: in_var.h,v $ $Revision: 4.2.34.2 $ (DEC) $Date: 1996/11/22 22:10:43 $
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
 * Copyright (c) 1985, 1986 Regents of the University of California.
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
 *	Base:	in_var.h	7.4 (Berkeley) 4/22/89
 *	Merged:	in_var.h	7.6 (Berkeley) 6/28/90
 */

#ifndef _IN_VAR_H_
#define _IN_VAR_H_
/*
 * Interface address, Internet version.  One of these structures
 * is allocated for each interface with an Internet address.
 * The ifaddr structure contains the protocol-independent part
 * of the structure and is assumed to be first.
 */
struct in_ifaddr {
	struct	ifaddr ia_ifa;		/* protocol-independent info */
#define	ia_ifp		ia_ifa.ifa_ifp
#define ia_flags	ia_ifa.ifa_flags
					/* ia_{,sub}net{,mask} in host order */
	u_int	ia_net;			/* network number of interface */
	u_int	ia_netmask;		/* mask of net part */
	u_int	ia_subnet;		/* subnet number, including net */
	u_int	ia_subnetmask;		/* mask of subnet part */
	struct	in_addr ia_netbroadcast; /* to recognize net broadcasts */
	struct	in_ifaddr *ia_next;	/* next in list of internet addresses */
	struct	sockaddr_in ia_addr;	/* reserve space for interface name */
	struct	sockaddr_in ia_dstaddr; /* reserve space for broadcast addr */
#define	ia_broadaddr	ia_dstaddr
	struct	sockaddr_in ia_sockmask; /* reserve space for general netmask */
	struct	in_multi *ia_multiaddrs; /* list of multicast addresses */
};

struct	in_aliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_in ifra_addr;
	struct	sockaddr_in ifra_broadaddr;
#define ifra_dstaddr ifra_broadaddr
	struct	sockaddr_in ifra_mask;
};

/*
 * Internet version of access filter struct's
 */
struct in_afiltreq {
	char    ifafr_name[IFNAMSIZ];	/* if name, e.g. "en0" */
	u_int   ifafr_cnt;		/* number of entries */
	struct  in_afilt *ifafr_filt;	/* user-defined filter */
};

struct in_afilt {
	struct  sockaddr_in ifaf_addr;	/* addr */
	struct  sockaddr_in ifaf_mask;	/* mask */
	u_int   ifaf_action;		/* action */
	u_int	ifaf_cnt;		/* counter */
};

/*
 *  in_ifaddr hash table struct
 *
 *  Note: we can save 8 bytes by getting-rid of *ifp and use
 *      available u_short for if_index to ifp mapping-array
 *      However, w/o *ifp, we already need 24-bytes -- so mallocing
 *      24 bytes -- we get 32-bytes -- so mapping-array effort/complexity 
 *      isn't worthwhile.
 */
struct in_ifaddrh {
	struct  in_addr ipa;	   /* ip addr */
	u_int	ref;		       /* ref count for broadcast addrs */	
	u_short flags;		 /* flags */
	struct ifnet *ifp;	       /* ptr to ifnet */
	struct in_ifaddrh *inh_next;   /* ptr to next entry */
};

struct inifaddr_hstat {
	int iacompared;
	int iamatched;
	int iaentry;
	int iarefentry;
};

/*
 * Given a pointer to an in_ifaddr (ifaddr),
 * return a pointer to the addr, or dstaddr, as a sockaddr_in.
 */
#define	IA_SIN(ia) (&(((struct in_ifaddr *)(ia))->ia_addr))
#define	IA_DSIN(ia) (&(((struct in_ifaddr *)(ia))->ia_dstaddr))

/*
 * Inifaddr hash macro given 32-bit ipaddr as a key returns bucket index
 * for table size (1 << inifaddr_hexp) -- Courtesy of Jeff Mogul
 */
#define _INIFADDR_HASH(_dst_, _hb_)				  \
    {								\
       int _i_;						      \
       (_hb_) = (_dst_);					     \
       for (_i_ = inifaddr_hexp; _i_ < 32; _i_ += inifaddr_hexp)     \
	    (_hb_) += ((_dst_) >> _i_);			      \
       (_hb_) &= inifaddr_hmask;				     \
     }
#define _INIFADDR_HASH_ENABLED()	(inifaddr_hexp > 0) 

#define	_INIFADDR_MAX_HEXP  9   /* max (2**max_hexp) size of inifaddr_htab */
#define	_INIFADDR_MIN_HEXP  4   /* min (2**max_hexp) size of inifaddr_htab */
#define	_INIFADDRHEXP	    5   /* default (2**hexp) size of inifaddr_htab */
#define IFAH_BROADCAST    0x1   /* hash entry w/ broadcast address */

#ifdef	_KERNEL
ndecl_lock_data(extern, inifaddr_lock)
#define INIFADDR_LOCKINIT()	ulock_setup(&inifaddr_lock, inifaddr_li, TRUE)
#define INIFADDR_WRITE_LOCK()	ulock_write(&inifaddr_lock)
#define INIFADDR_READ_LOCK()	ulock_read(&inifaddr_lock)
#define INIFADDR_UNLOCK()	ulock_done(&inifaddr_lock)
#define INIFADDR_ISLOCKED()	(lockmode==0||lock_holder(&inifaddr_lock))

extern 	simple_lock_data_t      inifaddr_spin_lock;
#define INIFADDR_SPIN_LOCKINIT() simple_lock_setup(&inifaddr_spin_lock, inifaddr_spin_li)
#define INIFADDR_SPIN_LOCK()	 simple_lock(&inifaddr_spin_lock)
#define INIFADDR_SPIN_UNLOCK()	 simple_unlock(&inifaddr_spin_lock)
#define INIFADDR_SPIN_ISLOCKED() (lockmode==0||simple_lock_holder(&inifaddr_spin_lock))

extern	struct	in_ifaddr *in_ifaddr;
extern	struct	in_ifaddrh **inifaddr_htab; /* in_ifaddr hash table */
extern	int	inifaddr_hexp;		/* exponentiation of inifaddr_htab */
extern	int	inifaddr_hsize;		/* hash table size of inifaddr_htab */
extern	int	inifaddr_hmask;		/* mask to be used in HASH macro */
extern	struct  inifaddr_hstat inifaddr_hstat; /* inifaddr_htab  stat */
extern	struct	ifqueue	ipintrq;	/* ip packet input queue */

/*
 * Macro for finding the interface (ifnet structure) corresponding to one
 * of our IP addresses.
 */
#define INADDR_TO_IFP(addr, ifp) \
	/* struct in_addr addr; */ \
	/* struct ifnet *ifp; */ \
{ \
	register struct in_ifaddr *ia; \
\
	INIFADDR_SPIN_LOCK(); \
	for (ia = in_ifaddr; \
	    ia != NULL && IA_SIN(ia)->sin_addr.s_addr != (addr).s_addr; \
	    ia = ia->ia_next) \
		 continue; \
	(ifp) = (ia == NULL) ? NULL : ia->ia_ifp; \
	INIFADDR_SPIN_UNLOCK(); \
}

/*
 * Macro for finding the interface (ifnet structure) corresponding to one
 * of our IP addresses.  Looks at the remote address of POINTOPOINT
 * interfaces. Courtesy Jeff Honig.
 */
#define IFADDR_TO_IFP(addr, ifp) \
	/* struct in_addr addr; */ \
	/* struct ifnet *ifp; */ \
{ \
	register struct in_ifaddr *ia; \
\
	INIFADDR_SPIN_LOCK(); \
	for (ia = in_ifaddr; \
	    ia != NULL; \
	    ia = ia->ia_next) \
	    if (((ia->ia_ifp->if_flags & IFF_POINTOPOINT) ? \
		IA_DSIN(ia) : IA_SIN(ia))->sin_addr.s_addr == \
			(addr).s_addr) \
		 break; \
	(ifp) = (ia == NULL) ? NULL : ia->ia_ifp; \
	INIFADDR_SPIN_UNLOCK(); \
}

/*
 * Macro for finding the internet address structure (in_ifaddr) corresponding
 * to a given interface (ifnet structure).
 */
#define IFP_TO_IA(ifp, ia) \
	/* struct ifnet *ifp; */ \
	/* struct in_ifaddr *ia; */ \
{ \
	LOCK_ASSERT("IFP_TO_IA", \
		    (INIFADDR_ISLOCKED() || INIFADDR_SPIN_ISLOCKED())); \
	for ((ia) = in_ifaddr; \
	    (ia) != NULL && (ia)->ia_ifp != (ifp); \
	    (ia) = (ia)->ia_next) \
		continue; \
}
#endif

/*
 * Per-interface router version information is kept in this list.
 * This information should be part of the ifnet structure but we don't wish
 * to change that - as it might break a number of things
 */

struct router_info {
       struct ifnet *ifp;
       int    type; /* type of router which is querier on this interface */
       int    time; /* # of slow timeouts since last old query */
       struct router_info *next;
};

/*
 * Internet multicast address structure.  There is one of these for each IP
 * multicast group to which this host belongs on a given network interface.
 * They are kept in a linked list, rooted in the interface's in_ifaddr
 * structure.
 */
struct in_multi {
	struct	in_addr inm_addr;	/* IP multicast address */
	struct	ifnet *inm_ifp;		/* back pointer to ifnet */
	struct	in_ifaddr *inm_ia;	/* back pointer to in_ifaddr */
	u_int	inm_refcount;		/* no. membership claims by sockets */
	u_int	inm_timer;		/* IGMP membership report timer */
	struct	in_multi *inm_next;	/* ptr to next multicast address */
	u_int   inm_state;	      /*  state of the membership */
	struct  router_info *inm_rti;   /* router info */
};

#ifdef _KERNEL
/*
 * Structure used by macros below to remember position when stepping through
 * all of the in_multi records.
 */
struct in_multistep {
	struct in_ifaddr *i_ia;
	struct in_multi *i_inm;
};

/*
 * Macro for looking up the in_multi record for a given IP multicast address
 * on a given interface.  If no matching record is found, "inm" returns NULL.
 */
#define IN_LOOKUP_MULTI(addr, ifp, inm) \
	/* struct in_addr addr; */ \
	/* struct ifnet *ifp; */ \
	/* struct in_multi *inm; */ \
{ \
	register struct in_ifaddr *ia; \
\
	INIFADDR_SPIN_LOCK(); \
	IFP_TO_IA((ifp), ia); \
	if (ia == NULL) \
		(inm) = NULL; \
	else \
		for ((inm) = ia->ia_multiaddrs; \
		    (inm) != NULL && (inm)->inm_addr.s_addr != (addr).s_addr; \
		     (inm) = inm->inm_next) \
			 continue; \
	INIFADDR_SPIN_UNLOCK(); \
}

/*
 * Macro to step through all of the in_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  IN_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "inm" when there
 * are no remaining records.
 */
#define IN_NEXT_MULTI(step, inm) \
	/* struct in_multistep  step; */ \
	/* struct in_multi *inm; */ \
{ \
	LOCK_ASSERT("IFP_TO_IA", \
		    (INIFADDR_ISLOCKED() || INIFADDR_SPIN_ISLOCKED())); \
	if (((inm) = (step).i_inm) != NULL) \
		(step).i_inm = (inm)->inm_next; \
	else \
		while ((step).i_ia != NULL) { \
			(inm) = (step).i_ia->ia_multiaddrs; \
			(step).i_ia = (step).i_ia->ia_next; \
			if ((inm) != NULL) { \
				(step).i_inm = (inm)->inm_next; \
				break; \
			} \
		} \
}

#define IN_FIRST_MULTI(step, inm) \
	/* struct in_multistep step; */ \
	/* struct in_multi *inm; */ \
{ \
	LOCK_ASSERT("IFP_TO_IA", \
		    (INIFADDR_ISLOCKED() || INIFADDR_SPIN_ISLOCKED())); \
	(step).i_ia = in_ifaddr; \
	(step).i_inm = NULL; \
	IN_NEXT_MULTI((step), (inm)); \
}

#endif

#endif
