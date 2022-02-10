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
 *	@(#)$RCSfile: mbuf.h,v $ $Revision: 4.3.49.3 $ (DEC) $Date: 1998/10/29 21:01:12 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
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
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
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
 *	Base:	mbuf.h	7.12 (Berkeley) 9/4/89
 *	Merged: mbuf.h	7.13 (Berkeley) 6/28/90
 */

#ifndef	_SYS_MBUF_H_
#define	_SYS_MBUF_H_

#include <sys/param.h>
#include <sys/malloc.h>

#ifdef	_KERNEL
#ifndef	_NET_GLOBALS_H_
#include "net/net_globals.h"
#endif
#ifndef	NET_MALLOC
#include "net/net_malloc.h"
#endif
#endif

#if	!defined(MCLBYTES)
/* Compat for now */
#ifdef __alpha
#define	MSIZE		256	/* size of an mbuf */
#else
#define	MSIZE		128	/* size of an mbuf */
#endif /* __alpha */
#define MCLBYTES	CLBYTES
#define MCL2KBYTES	2048
#define MAPPED_MBUFS	/* safe */
#endif
#if	defined(_KERNEL) && !defined(NMBCLUSTERS) && !defined(__alpha)
#include <mbclusters.h>
#endif

/*
 * Mbufs are of a single size, MSIZE, which includes overhead.  
 * An mbuf may add a single "mbuf cluster" of size MCLBYTES (from CLBYTES 
 * in sys/param.h), which has no additional overhead and is used instead 
 * of the internal data area; this is usually done when
 * at least MINCLSIZE of data must be stored.
 */

#define	MLEN		(MSIZE - sizeof(struct m_hdr))	/* normal data len */
#define	MHLEN		(MLEN - sizeof(struct pkthdr))	/* data len w/pkthdr */

#define	MINCLSIZE	(MHLEN + MLEN)	/* smallest amount to put in cluster */
#define	M_MAXCOMPRESS	(MHLEN / 2)	/* max amount to copy for compression */
#define MLENGTH(m)	((m)->m_flags & M_PKTHDR ? (m)->m_pkthdr.len : m_length(m))

/* forward declarations as required for C++ */
#ifdef __cplusplus
struct mbuf;
struct m_hdr;
#endif

#include <sys/secdefines.h>
#if SEC_NET
#       undef MMINOFF
#       define MMINOFF  24
/* For debugging we use a function call to allow us to trap MGET calls */
#	define TNSMM_CLEAR_ATTR(m) m->m_attr = (struct mbuf*)0
#       define TNSMM_FREE_ATTR(m) \
          if ((m)->m_attr != (struct mbuf *)0) {\
                (void)tnsmm_free_attr(m);\
                }
#else
#       define TNSMM_CLEAR_ATTR(m)
#       define TNSMM_FREE_ATTR(m)
#endif

/*
 * Macros for type conversion
 * mtod(m,t) -	convert mbuf pointer to data pointer of correct type
 * dtom(x) -	convert data pointer within mbuf to mbuf pointer (XXX)
 */
#define mtod(m,t)	((t)((m)->m_data))
#define	dtom(x)		((struct mbuf *)((u_long)(x) & ~(MSIZE-1)))

/* header at beginning of each mbuf: */
struct m_hdr {
	struct	mbuf *mh_next;		/* next buffer in chain */
	struct	mbuf *mh_nextpkt;	/* next chain in queue/record */
	caddr_t	mh_data;		/* location of data */
	int	mh_len;			/* amount of data in this mbuf */
	int	mh_type;		/* type of data in this mbuf */
	int	mh_flags;		/* flags; see below */
#ifdef __alpha
	union {
		caddr_t	*mun1_ipq[4];	/* ipasfrag chain pointers */
		caddr_t	*mun1_ihp[4];	/* protocol sequence chain */
#ifdef M_CTX_T
		m_ctx_t	*mun1_ctx[4];	/* generic context structure */
#endif
	} mh_un1;
#define	m_ipq		m_hdr.mh_un1.mun1_ipq
#define	m_ihp		m_hdr.mh_un1.mun1_ihp
#ifdef M_CTX_T
#define	m_ctx		m_hdr.mh_un1.mun1_ctx
#endif
#endif
#if SEC_NET
        struct mbuf *mh_attr;            /* mbuf chain security attributes */
#endif
};

/* record/packet header in first mbuf of chain; valid if M_PKTHDR set */
struct	pkthdr {
	int	len;		/* total packet length */
	int	protocolSum;	/* DART: rcv: TCP/UDP checksum from hardware */
	struct	ifnet *rcvif;	/* rcv interface */
};

/* description of external storage mapped into mbuf, valid if M_EXT set */
struct m_ext {
	caddr_t	ext_buf;		/* start of buffer */
#if	__STDC__
	void	(*ext_free)(caddr_t, u_long, caddr_t);
#else
	void	(*ext_free)();		/* free routine if not the usual */
#endif
	u_int	ext_size;		/* size of buffer, for ext_free */
	caddr_t	ext_arg;		/* additional ext_free argument */
	struct	ext_refq {		/* reference list */
		struct ext_refq *forw, *back;
	} ext_ref;
	int	(*uiomove_f)();	/* DART: copy routine if M_UIOMOVE */
	int	protocolSum;	/* DART: xmt: TCP/UDP checksum from hardware */
	int	bytesSummed;	/* DART: */
	unsigned short	(*checksum)();  /* external checksum routine */
};

struct mbuf {
	struct	m_hdr m_hdr;
	union {
		struct {
			struct	pkthdr MH_pkthdr;	/* M_PKTHDR set */
			union {
				struct	m_ext MH_ext;	/* M_EXT set */
				char	MH_databuf[MHLEN];
			} MH_dat;
		} MH;
		char	M_databuf[MLEN];		/* !M_PKTHDR, !M_EXT */
	} M_dat;
};

#if SEC_NET
#define m_ifp           M_dat.MH.MH_pkthdr.rcvif
#endif /*SEC_NET*/
                                                       
#define m_attr          m_hdr.mh_attr
#define	m_next		m_hdr.mh_next
#define	m_len		m_hdr.mh_len
#define	m_data		m_hdr.mh_data
#define	m_type		m_hdr.mh_type
#define	m_flags		m_hdr.mh_flags
#define	m_nextpkt	m_hdr.mh_nextpkt
#define	m_act		m_nextpkt
#define	m_pkthdr	M_dat.MH.MH_pkthdr
#define	m_ext		M_dat.MH.MH_dat.MH_ext
#define	m_pktdat	M_dat.MH.MH_dat.MH_databuf
#define	m_dat		M_dat.M_databuf

/* mbuf flags */
#define	M_EXT		0x0001	/* has associated external storage */
#define	M_PKTHDR	0x0002	/* start of record */
#define	M_EOR		0x0004	/* end of record */
#define	M_FASTFREE	0x0008	/* free external storage asap */
#define M_UIOMOVE	0x0010	/* DART: m_ext.uiomove_f is valid */
#define M_HDRRSVD	0x0020	/* DART: ATOMIC_FRAG_NETIO */

/* mbuf pkthdr flags, also in m_flags */
#define	M_BCAST		0x0100	/* send/received as link-level broadcast */
#define	M_MCAST		0x0200	/* send/received as link-level multicast */
#define	M_WCARD		0x0400	/* received as network-level broadcast */
#define M_PROTOCOL_SUM	0x0800	/* DART: protocolSum is valid */
#define M_ATM_CLP	0x1000	/* ATM: do Congestion Loss Priority on packet */
#define M_REQUE_OK	0x2000	/* OK for drivers to reque failed transmits */ 
#define M_REQUED_ONCE	0x4000	/* Driver re-queued a failed transmit (once) */ 
#define M_PROXY		0x8000	/* Firewall: proxy on localhost */
#define M_CHECKSUM	0x40000	/* External Checksum Routine valid */
#define M_IPPREPROCESS	0x80000	/* ip preprocess run on mbuf. mutually exclusive with M_PROTOCOL_SUM */

/* does mbuf hold a broadcast packet? */
#define m_broadcast(m)	((m)->m_flags & (M_BCAST|M_MCAST|M_WCARD))

/* flags copied when copying m_pkthdr */
#define	M_COPYFLAGS	(M_PKTHDR|M_EOR|M_BCAST|M_MCAST|M_WCARD|M_PROTOCOL_SUM|M_PROXY|M_CHECKSUM)

/* mbuf types */
#define	MT_FREE		M_FREE		/* should be on free list */
#define	MT_DATA		M_MBUF		/* dynamic (data) allocation */ 
#define	MT_HEADER	M_HEADER	/* packet header */
#define	MT_SOCKET	M_SOCKET	/* socket structure */
#define	MT_PCB		M_PCB		/* protocol control block */
#define	MT_RTABLE	M_RTABLE	/* routing tables */
#define	MT_HTABLE	M_HTABLE	/* IMP host tables */
#define	MT_ATABLE	M_ATABLE	/* address resolution tables */
#define	MT_SONAME	M_SONAME	/* socket name */
#define	MT_MRTABLE	M_MRTABLE	/* multicast route tables */
#define	MT_SOOPTS	M_SOOPTS	/* socket options */
#define	MT_FTABLE	M_FTABLE	/* fragment reassembly header */
#define	MT_RIGHTS	M_RIGHTS	/* access rights */
#define	MT_IFADDR	M_IFADDR	/* interface address */
#define MT_CONTROL	M_CONTROL	/* extra-data protocol message */
#define MT_OOBDATA	M_OOBDATA	/* expedited data */
#define MT_MAX		16		/* for backwards compatibility */

/* flags to m_get/MGET */
#define	M_DONTWAIT	M_NOWAIT
#define	M_WAIT		M_WAITOK
/*
 * flag to m_copym
 */
#define M_IGNOREEND	0x1000

/*
 * mbuf allocation/deallocation macros:
 *
 *	MGET(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain internal data.
 *
 *	MGETHDR(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain a packet header
 * and internal data.
 */

#define	MGET(m, how, type) { \
	MALLOC((m), struct mbuf *, MSIZE, (type), (how)); \
	if (m) { \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_dat; \
		(m)->m_flags = 0; \
		TNSMM_CLEAR_ATTR(m); \
	} else \
		(m) = m_retry((how), (type)); \
}

#define	MGETHDR(m, how, type) { \
	MALLOC((m), struct mbuf *, MSIZE, (type), (how)); \
	if (m) { \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_pktdat; \
		(m)->m_flags = M_PKTHDR; \
		TNSMM_CLEAR_ATTR(m); \
	} else \
		(m) = m_retryhdr((how), (type)); \
}

/*
 * Mbuf cluster macros.
 * MCLALLOC(caddr_t p, int how) allocates an mbuf cluster.
 * MCLGET adds such clusters to a normal mbuf;
 * the flag M_EXT is set upon success.
 * MCLFREE unconditionally frees a cluster allocated by MCLALLOC.
 */

#define	MCLALLOC(p, how) \
	  p = m_clalloc(1, (how));

#define	MCLFREE(p) { \
	FREE((p), M_CLUSTER); \
}

#define	MCLGET(m, how) { \
	(void) m_clalloc8((m), (how)); \
}

#define	MCLGET2(m, how) { \
	(void) m_clalloc2((m), (how)); \
}

#define MCLREFERENCED(m) \
	((m)->m_ext.ext_ref.forw != &((m)->m_ext.ext_ref))

/*
 * MFREE(struct mbuf *m, struct mbuf *n)
 * Free a single mbuf and associated external storage.
 * Place the successor, if any, in n.
 */
#define	MFREE(m, n) \
	((n) = m_free(m))

/*
 * Copy mbuf pkthdr from from to to.
 * from must have M_PKTHDR set, and to must be empty.
 */
#define	M_COPY_PKTHDR(to, from) { \
	(to)->m_pkthdr = (from)->m_pkthdr; \
	(to)->m_flags = (from)->m_flags & M_COPYFLAGS; \
	(to)->m_data = (to)->m_pktdat; \
}

/*
 * Set the m_data pointer of a newly-allocated mbuf (m_get/MGET) to place
 * an object of the specified size at the aligned end of the mbuf.
 */
#define	M_ALIGN(m, len) { \
	(m)->m_data += (MLEN - (len)) &~ (sizeof(long) - 1); \
}
/*
 * As above, for mbufs allocated with m_gethdr/MGETHDR
 * or initialized by M_COPY_PKTHDR.
 */
#define	MH_ALIGN(m, len) { \
	(m)->m_data += (MHLEN - (len)) &~ (sizeof(long) - 1); \
}

/*
 * Compute the amount of space available
 * before the current start of data in an mbuf.
 * Subroutine - data not available if certain references.
 */
#define	M_LEADINGSPACE(m)	m_leadingspace(m)

/*
 * Compute the amount of space available
 * after the end of data in an mbuf.
 * Subroutine - data not available if certain references.
 */
#define	M_TRAILINGSPACE(m)	m_trailingspace(m)

/*
 * Arrange to prepend space of size plen to mbuf m.
 * If a new mbuf must be allocated, how specifies whether to wait.
 * If how is M_DONTWAIT and allocation fails, the original mbuf chain
 * is freed and m is set to NULL.
 */
#define	M_PREPEND(m, plen, how) { \
	if (M_LEADINGSPACE(m) >= (plen)) { \
		(m)->m_data -= (plen); \
		(m)->m_len += (plen); \
	} else \
		(m) = m_prepend((m), (plen), (how)); \
	if ((m) && (m)->m_flags & M_PKTHDR) \
		(m)->m_pkthdr.len += (plen); \
}

/* change mbuf to new type */
/* Note: this may cause malloc() mbuf type stats to be inaccurate */
#define MCHTYPE(m, t) { \
	(m)->m_type = (t);\
}

/* length to m_copy to copy all */
#define	M_COPYALL	1000000000

/* compatiblity with 4.3 */
#define  m_copy(m, o, l)	m_copym((m), (o), (l), M_DONTWAIT)

/*
 * Mbuf statistics.
 */
struct mbstat {
	u_long	m_mbufs;	/* obsolete: tracked by malloc M_MBUF stats */
	u_long	m_clusters;	/* obsolete: tracked by malloc M_CLUSTER stats*/
	u_long	m_drops;	/* times failed to find space */
	u_long	m_drain;	/* times drained protocols for space */
	u_int	m_mtypes[MT_MAX];	/* obsolete: tracked by MALLOC(type) stats */
};

#ifdef	_KERNEL
#if	NETSYNC_LOCK
extern	simple_lock_data_t mbuf_slock;
#define MBUF_LOCKINIT()	simple_lock_setup(&mbuf_slock,mbuf_sli)
#define MBUF_LOCK()	simple_lock(&mbuf_slock)
#define MBUF_UNLOCK()	simple_unlock(&mbuf_slock)

#define MBUF_EXT_LOCK_SHIFT  24
extern simple_lock_data_t      *mbuf_ext_slock;
extern unsigned int 		mbuf_ext_lock_mask;
#define MBUF_EXT_LOCK_ADDR(m) \
        	(mbuf_ext_slock +    \
         	(((unsigned)(m) >> MBUF_EXT_LOCK_SHIFT) & mbuf_ext_lock_mask))

#define MBUF_EXT_LOCK(m) simple_lock(MBUF_EXT_LOCK_ADDR(m))
#define MBUF_EXT_UNLOCK(m) simple_unlock(MBUF_EXT_LOCK_ADDR(m))
#if	!VAGUE_STATS
#define MBSTAT(x)	do { spl_t _ns = splimp(); MBUF_LOCK(); \
			  x; MBUF_UNLOCK(); splx(_ns); } while (0)
#else	/* !VAGUE_STATS */
#define MBSTAT(x)	x
#endif  /* !VAGUE_STATS */
#else	/* NETSYNC_LOCK */
#define MBUF_LOCKINIT()
#define MBUF_LOCK()
#define MBUF_UNLOCK()
#define MBUF_EXT_LOCK(m) 
#define MBUF_EXT_UNLOCK(m)
#define MBSTAT(x)	x
#endif	/* NETSYNC_LOCK */
extern struct	mbstat mbstat;		/* statistics */
extern int	max_linkhdr;		/* largest link-level header */
extern int	max_protohdr;		/* largest protocol header */
extern int	max_hdr;		/* largest link+protocol header */
extern int	max_datalen;		/* MHLEN - max_hdr */
extern int	mclbytes;		/* variable version of MCLBYTES */
#endif
#endif
