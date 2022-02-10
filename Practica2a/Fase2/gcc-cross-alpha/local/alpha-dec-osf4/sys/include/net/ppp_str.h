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
 * @(#)$RCSfile: ppp_str.h,v $ $Revision: 1.1.2.5 $ (DEC) $Date: 1995/09/26 21:41:50 $
 */
/*
  ppp_str.h - streams version include file

  Copyright (C) 1990 Brad K. Clements, All Rights Reserved,
  See copyright statement in NOTES

  The original copyright by Brad Clements (see above) has
  been modified by his written permission dated 5/12/95 to
  specifically include commercial use by Digital Equipment Corp.
*/


#ifdef	VJC
#include <net/vjcompress.h>
#endif /* VJC */

/*
 * Packet sizes
 */
#define	PPP_MTU		1500	/* Default MTU (size of Info field) */
#define PPP_MAXMRU	65000	/* Largest MRU we allow */

/*
 * module ID's for each STREAMS module
 */

#define	PPP_MID_ASYNC		6000	/* for ppp_async module */
#define	PPP_MID_COMPRESS	6001	/* for ppp_comp module */
#define	PPP_MID_IF		6002	/* for ppp_if module */

/*
 * Definitions for ioctls.
 */
struct npioctl {
    int		protocol;	/* PPP procotol, e.g. PPP_IP */
    enum NPmode	mode;
};

/* Structure describing a CCP configuration option, for SIOCSCOMPRESS */
#define MAX_PPP_OPTION	32
struct ppp_option_data {
	u_int	length;
	int	transmit;
	u_char	opt_data[MAX_PPP_OPTION];
};

struct ifpppstatsreq {
    char ifr_name[IFNAMSIZ];
    struct ppp_stats stats;
};

struct ifpppcstatsreq {
    char ifr_name[IFNAMSIZ];
    struct ppp_comp_stats stats;
};

/*
 * Ioctl definitions.
 */

#if defined(__STDC__) || defined(__osf__)
#define	SIOCSIFCOMPAC	_IOW('p', 130, char)
#define	SIOCSIFCOMPPROT	_IOW('p', 131, char)
#define	SIOCSIFMRU	_IOW('p', 132, int)	/* set max receive unit */
#define	SIOCGIFMRU	_IOR('p', 133, int)	/* get max receive unit */
#define	SIOCGIFASYNCMAP	_IOR('p', 134, u_int32_t) /* get transmit async map */
#define	SIOCSIFASYNCMAP	_IOW('p', 135, u_int32_t) /* set transmit async map */
#define	SIOCGETU	_IOR('p', 136, int)	/* get unit number */
#define	SIOCSIFVJCOMP	_IOW('p', 137, char)	/* enable/disable VJ comp */
#define	SIOCGIFDEBUG	_IOR('p', 138, int)	/* get debug flags */
#define	SIOCSIFDEBUG	_IOW('p', 139, int)	/* set debug flags */
#define	SIOCGIFRASYNCMAP _IOR('p', 140, u_int32_t) /* get receive async map */
#define	SIOCSIFRASYNCMAP _IOW('p', 141, u_int32_t) /* set receive async map */
#define	SIOCGIFXASYNCMAP _IOR('p', 142, ext_accm)  /* get extended xmit map */
#define	SIOCSIFXASYNCMAP _IOW('p', 143, ext_accm)  /* set extended xmit map */
#define	SIOCSETU	_IOW('p', 144, int)	/* set unit number */
#define SIOCSETNPMODE	_IOW('p', 145, struct npioctl)	/* set NP mode */
#define SIOCGETNPMODE	_IOWR('p', 146, struct npioctl)	/* get NP mode */
#define SIOCGIFCOMP	_IOR('p', 148, int)	/* get CCP kernel flags */
#define SIOCSIFCOMP	_IOW('p', 149, int)	/* set CCP closed/open/up */
#define SIOCSCOMPRESS	_IOW('p', 150, struct ppp_option_data)

#define SIOCGPPPSTATS	_IOWR('i', 123, struct ifpppstatsreq)
#define SIOCGPPPCSTATS	_IOWR('i', 124, struct ifpppcstatsreq)

#else
/* traditional C compiler */
#define	SIOCSIFCOMPAC	_IOW(p, 130, char)
#define	SIOCSIFCOMPPROT	_IOW(p, 131, char)
#define	SIOCSIFMRU	_IOW(p, 132, int)	/* set max receive unit */
#define	SIOCGIFMRU	_IOR(p, 133, int)	/* get max receive unit */
#define	SIOCGIFASYNCMAP	_IOR(p, 134, u_int32_t)	/* get transmit async map */
#define	SIOCSIFASYNCMAP	_IOW(p, 135, u_int32_t)	/* set transmit async map */
#define	SIOCGETU	_IOR(p, 136, int)	/* get unit number */
#define	SIOCSIFVJCOMP	_IOW(p, 137, char)	/* enable/disable VJ comp */
#define	SIOCGIFDEBUG	_IOR(p, 138, int)	/* get debug flags */
#define	SIOCSIFDEBUG	_IOW(p, 139, int)	/* set debug flags */
#define	SIOCGIFRASYNCMAP _IOR(p, 140, u_int32_t) /* get receive async map */
#define	SIOCSIFRASYNCMAP _IOW(p, 141, u_int32_t) /* set receive async map */
#define	SIOCGIFXASYNCMAP _IOR(p, 142, ext_accm) /* get extended xmit map */
#define	SIOCSIFXASYNCMAP _IOW(p, 143, ext_accm) /* set extended xmit map */
#define	SIOCSETU	_IOW(p, 144, int)	/* set unit number */
#define SIOCSETNPMODE	_IOW(p, 145, struct npioctl)	/* set NP mode */
#define SIOCGETNPMODE	_IOWR(p, 146, struct npioctl)	/* get NP mode */
#define SIOCGIFCOMP	_IOR(p, 148, int)	/* get CCP kernel flags */
#define SIOCSIFCOMP	_IOW(p, 149, int)	/* set CCP closed/open/up */
#define SIOCSCOMPRESS	_IOW(p, 150, struct ppp_option_data)

#define SIOCGPPPSTATS	_IOWR(i, 123, struct ifpppstatsreq)
#define SIOCGPPPCSTATS	_IOWR(i, 124, struct ifpppcstatsreq)
#endif

/*
 * Note on SIOCSIFVJCOMP: the parameter is now encoded as follows.
 * Bit 0 = overall VJ enable, bit 1 = don't compress connection ID,
 * bit 2 = receiver rejects VJ compression,
 * bits 4--7 = maximum slot ID (0 => use default (15)).
 */

/* Bits for SIOCGIFDEBUG */
#define PAI_FLAGS_B7_0		0x100
#define PAI_FLAGS_B7_1		0x200
#define PAI_FLAGS_PAR_EVEN	0x400
#define PAI_FLAGS_PAR_ODD	0x800
#define PAI_FLAGS_HIBITS	0xF00

/* Bit definitions for SIOC[GS]IFCOMP. */
#define CCP_ISOPEN	            1
#define CCP_ISUP	            2
#define CCP_COMP_RUN	            4
#define CCP_DECOMP_RUN	            8
#define CCP_ERROR	         0x10
#define CCP_FATALERROR	         0x20

/* defines for streams modules */
#define IF_INPUT_ERROR	        0xe1
#define IF_OUTPUT_ERROR	        0xe2
#define IF_GET_CSTATS	        0xe3
#define IF_CSTATS	        0xe4

/*
 * Values for FCS calculations.
 */
#define PPP_INITFCS	0xffff	/* Initial FCS value */
#define PPP_GOODFCS	0xf0b8	/* Good final FCS value */
#define PPP_FCS(fcs, c)	(((fcs) >> 8) ^ fcstab[((fcs) ^ (c)) & 0xff])

/*
 * Values for pii_flags.
 */
#define	PII_FLAGS_INUSE		0x1	/* in use by  a stream	*/
#define	PII_FLAGS_ATTACHED	0x8	/* already if_attached	*/
#define	PII_FLAGS_VJC_ON	0x10	/* VJ TCP header compression enabled */
#define PII_FLAGS_VJC_NOCCID	0x20	/* VJ: don't compress conn. id */
#define PII_FLAGS_VJC_REJ	0x40	/* receive: reject VJ comp */
#define PII_FLAGS_DEBUG		0x80	/* enable debug printout */

/*
 * Values for pai_flags.
 */
#define	PAI_FLAGS_INUSE		0x1
#define	PAI_FLAGS_FLUSH		0x2
#define	PAI_FLAGS_ESCAPED 	0x4
#define	PAI_FLAGS_COMPPROT	0x8
#define	PAI_FLAGS_COMPAC	0x10
#define	PAI_FLAGS_RCV_COMPPROT	0x20
#define	PAI_FLAGS_RCV_COMPAC	0x40

#define PAI_FLAGS_DEBUG		0x1000
#define PAI_FLAGS_LOG_INPKT	0x2000
#define PAI_FLAGS_LOG_OUTPKT	0x4000
#define PAI_FLAGS_ALL_DEBUG	0x7000

#ifdef	_KERNEL
#define	PPP_SMP		/* enable SMP macros and code,
				only in kernel, and
				only if this symbol defined */
#endif	/* _KERNEL */

#ifdef	PPP_SMP		/* PPP's SMP macros */

#include <kern/lock.h>

#define	PPP_LOCK_LOG(m,s,a) \
			if (ppp_lock_debug) log(LOG_DEBUG, \
				m "(%d) LOCK_LOG " s "\n", __LINE__, a)

/* SMP macros for ppp_if.c */

#define	PPP_SETUP_IF_TABLE(m)	\
	{ \
	PPP_LOCK_LOG(m,"setup table",0); \
	simple_lock_setup (&ppp_if_table_lock,	\
		ppp_if_table_lock_info); \
	}
#define	PPP_LOCK_IF_TABLE(m)	\
	{ \
	PPP_LOCK_LOG(m,"lock table",0); \
	simple_lock (&ppp_if_table_lock); \
	}
#define	PPP_UNLOCK_IF_TABLE(m)	\
	{ \
	simple_unlock (&ppp_if_table_lock); \
	PPP_LOCK_LOG(m,"unlock table",0); \
	}

#define	PPP_SETUP_IF_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"setup element %d", p-pii ); \
	simple_lock_setup (&p->ppp_if_element_lock,	\
		ppp_if_element_lock_info); \
	}
#define	PPP_LOCK_IF_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"lock element %d", p-pii ); \
	simple_lock (&p->ppp_if_element_lock); \
	}
#define	PPP_UNLOCK_IF_ELEMENT(m)	\
	{ \
	simple_unlock (&p->ppp_if_element_lock); \
	PPP_LOCK_LOG(m,"unlock element %d", p-pii ); \
	}
#define	PPP_TERMINATE_IF_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"terminate element %d", p-pii ); \
	simple_lock_terminate (&p->ppp_if_element_lock); \
	}

/* SMP macros for ppp_comp.c */

#define	PPP_SETUP_COMP_TABLE(m)	\
	{ \
	PPP_LOCK_LOG(m,"setup table",0); \
	simple_lock_setup (&ppp_comp_table_lock,	\
		ppp_comp_table_lock_info); \
	}
#define	PPP_LOCK_COMP_TABLE(m)	\
	{ \
	PPP_LOCK_LOG(m,"lock table",0); \
	simple_lock (&ppp_comp_table_lock); \
	}
#define	PPP_UNLOCK_COMP_TABLE(m)	\
	{ \
	simple_unlock (&ppp_comp_table_lock); \
	PPP_LOCK_LOG(m,"unlock table",0); \
	}

#define	PPP_SETUP_COMP_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"setup element %d", cp->unit); \
	simple_lock_setup (&cp->ppp_comp_element_lock,	\
		ppp_comp_element_lock_info); \
	}
#define	PPP_LOCK_COMP_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"lock element %d", cp->unit); \
	simple_lock (&cp->ppp_comp_element_lock); \
	}
#define	PPP_UNLOCK_COMP_ELEMENT(m)	\
	{ \
	simple_unlock (&cp->ppp_comp_element_lock); \
	PPP_LOCK_LOG(m,"unlock element %d", cp->unit); \
	}
#define	PPP_TERMINATE_COMP_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"terminate element %d", cp->unit); \
	simple_lock_terminate (&cp->ppp_comp_element_lock); \
	}

/* SMP macros for ppp_async.c */

#define	PPP_SETUP_ASYNC_TABLE(m)	\
	{ \
	PPP_LOCK_LOG(m,"setup table",0); \
	simple_lock_setup (&ppp_async_table_lock,	\
		ppp_async_table_lock_info); \
	}
#define	PPP_LOCK_ASYNC_TABLE(m)	\
	{ \
	PPP_LOCK_LOG(m,"lock table",0); \
	simple_lock (&ppp_async_table_lock); \
	}
#define	PPP_UNLOCK_ASYNC_TABLE(m)	\
	{ \
	simple_unlock (&ppp_async_table_lock); \
	PPP_LOCK_LOG(m,"unlock table",0); \
	}

#define	PPP_SETUP_ASYNC_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"setup element %d", p-pai ); \
	simple_lock_setup (&p->ppp_async_element_lock,	\
		ppp_async_element_lock_info); \
	}
#define	PPP_LOCK_ASYNC_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"lock element %d", p-pai ); \
	simple_lock (&p->ppp_async_element_lock); \
	}
#define	PPP_UNLOCK_ASYNC_ELEMENT(m)	\
	{ \
	simple_unlock (&p->ppp_async_element_lock); \
	PPP_LOCK_LOG(m,"unlock element %d", p-pai ); \
	}
#define	PPP_TERMINATE_ASYNC_ELEMENT(m)	\
	{ \
	PPP_LOCK_LOG(m,"terminate element %d", p-pai ); \
	simple_lock_terminate (&p->ppp_async_element_lock); \
	}

#else

#define	PPP_SETUP_IF_TABLE(m)		{}
#define	PPP_LOCK_IF_TABLE(m)		{}
#define	PPP_UNLOCK_IF_TABLE(m)		{}

#define	PPP_SETUP_IF_ELEMENT(m)		{}
#define	PPP_LOCK_IF_ELEMENT(m)		{}
#define	PPP_UNLOCK_IF_ELEMENT(m)	{}
#define	PPP_TERMINATE_IF_ELEMENT(m)	{}

#define	PPP_SETUP_COMP_TABLE(m)		{}
#define	PPP_LOCK_COMP_TABLE(m)		{}
#define	PPP_UNLOCK_COMP_TABLE(m)	{}

#define	PPP_SETUP_COMP_ELEMENT(m)	{}
#define	PPP_LOCK_COMP_ELEMENT(m)	{}
#define	PPP_UNLOCK_COMP_ELEMENT(m)	{}
#define	PPP_TERMINATE_COMP_ELEMENT(m)	{}

#define	PPP_SETUP_ASYNC_TABLE(m)	{}
#define	PPP_LOCK_ASYNC_TABLE(m)		{}
#define	PPP_UNLOCK_ASYNC_TABLE(m)	{}

#define	PPP_SETUP_ASYNC_ELEMENT(m)	{}
#define	PPP_LOCK_ASYNC_ELEMENT(m)	{}
#define	PPP_UNLOCK_ASYNC_ELEMENT(m)	{}
#define	PPP_TERMINATE_ASYNC_ELEMENT(m)	{}

#endif	/* PPP_SMP */

/*
 * Structure used within the ppp_if streams module.
 */

struct ppp_if_info {

#ifdef	PPP_SMP		/* PPP kernel SMP */
    decl_simple_lock_data (, ppp_if_element_lock)
#endif	/* PPP_SMP */

    int			pii_flags;
    struct ifnet	pii_ifnet;
    queue_t		*pii_writeq;	/* used by ppp_output */
    enum NPmode		pii_npmode[NUM_NP];
    mblk_t		*pii_npq;	/* list of packets queued up */
    mblk_t		**pii_npq_tail;
#ifdef	VJC
    struct vjcompress	pii_sc_comp;	/* vjc control buffer */
#endif
#ifdef	PPP_STATS
    struct pppstat	pii_stats;
#endif
    struct ppp_comp_stats pii_cstats;
};

typedef	struct ppp_if_info	PII;

/*
 * Structure used within the ppp_async streams module.
 */

struct  ppp_async_info {

#ifdef	PPP_SMP		/* PPP kernel SMP */
    decl_simple_lock_data (, ppp_async_element_lock)
#endif	/* PPP_SMP */

    u_int	pai_flags;
    int		pai_buffsize;	/* how big of an input buffer to alloc */
    int		pai_buffcount;	/* how many chars currently in input buffer */
    u_short	pai_fcs;	/* the current fcs */
    mblk_t	*pai_buffer;	/* pointer to the current buffer list */
    mblk_t	*pai_bufftail;	/* pointer to the current input block */
    ext_accm	pai_asyncmap;	/* current outgoing asyncmap */
    u_int32_t	pai_rasyncmap;	/* current receive asyncmap */
};

typedef	struct ppp_async_info	PAI;

/*
 * FCS lookup table as calculated by genfcstab.
 */
static u_short fcstab[256] = {
	0x0000,	0x1189,	0x2312,	0x329b,	0x4624,	0x57ad,	0x6536,	0x74bf,
	0x8c48,	0x9dc1,	0xaf5a,	0xbed3,	0xca6c,	0xdbe5,	0xe97e,	0xf8f7,
	0x1081,	0x0108,	0x3393,	0x221a,	0x56a5,	0x472c,	0x75b7,	0x643e,
	0x9cc9,	0x8d40,	0xbfdb,	0xae52,	0xdaed,	0xcb64,	0xf9ff,	0xe876,
	0x2102,	0x308b,	0x0210,	0x1399,	0x6726,	0x76af,	0x4434,	0x55bd,
	0xad4a,	0xbcc3,	0x8e58,	0x9fd1,	0xeb6e,	0xfae7,	0xc87c,	0xd9f5,
	0x3183,	0x200a,	0x1291,	0x0318,	0x77a7,	0x662e,	0x54b5,	0x453c,
	0xbdcb,	0xac42,	0x9ed9,	0x8f50,	0xfbef,	0xea66,	0xd8fd,	0xc974,
	0x4204,	0x538d,	0x6116,	0x709f,	0x0420,	0x15a9,	0x2732,	0x36bb,
	0xce4c,	0xdfc5,	0xed5e,	0xfcd7,	0x8868,	0x99e1,	0xab7a,	0xbaf3,
	0x5285,	0x430c,	0x7197,	0x601e,	0x14a1,	0x0528,	0x37b3,	0x263a,
	0xdecd,	0xcf44,	0xfddf,	0xec56,	0x98e9,	0x8960,	0xbbfb,	0xaa72,
	0x6306,	0x728f,	0x4014,	0x519d,	0x2522,	0x34ab,	0x0630,	0x17b9,
	0xef4e,	0xfec7,	0xcc5c,	0xddd5,	0xa96a,	0xb8e3,	0x8a78,	0x9bf1,
	0x7387,	0x620e,	0x5095,	0x411c,	0x35a3,	0x242a,	0x16b1,	0x0738,
	0xffcf,	0xee46,	0xdcdd,	0xcd54,	0xb9eb,	0xa862,	0x9af9,	0x8b70,
	0x8408,	0x9581,	0xa71a,	0xb693,	0xc22c,	0xd3a5,	0xe13e,	0xf0b7,
	0x0840,	0x19c9,	0x2b52,	0x3adb,	0x4e64,	0x5fed,	0x6d76,	0x7cff,
	0x9489,	0x8500,	0xb79b,	0xa612,	0xd2ad,	0xc324,	0xf1bf,	0xe036,
	0x18c1,	0x0948,	0x3bd3,	0x2a5a,	0x5ee5,	0x4f6c,	0x7df7,	0x6c7e,
	0xa50a,	0xb483,	0x8618,	0x9791,	0xe32e,	0xf2a7,	0xc03c,	0xd1b5,
	0x2942,	0x38cb,	0x0a50,	0x1bd9,	0x6f66,	0x7eef,	0x4c74,	0x5dfd,
	0xb58b,	0xa402,	0x9699,	0x8710,	0xf3af,	0xe226,	0xd0bd,	0xc134,
	0x39c3,	0x284a,	0x1ad1,	0x0b58,	0x7fe7,	0x6e6e,	0x5cf5,	0x4d7c,
	0xc60c,	0xd785,	0xe51e,	0xf497,	0x8028,	0x91a1,	0xa33a,	0xb2b3,
	0x4a44,	0x5bcd,	0x6956,	0x78df,	0x0c60,	0x1de9,	0x2f72,	0x3efb,
	0xd68d,	0xc704,	0xf59f,	0xe416,	0x90a9,	0x8120,	0xb3bb,	0xa232,
	0x5ac5,	0x4b4c,	0x79d7,	0x685e,	0x1ce1,	0x0d68,	0x3ff3,	0x2e7a,
	0xe70e,	0xf687,	0xc41c,	0xd595,	0xa12a,	0xb0a3,	0x8238,	0x93b1,
	0x6b46,	0x7acf,	0x4854,	0x59dd,	0x2d62,	0x3ceb,	0x0e70,	0x1ff9,
	0xf78f,	0xe606,	0xd49d,	0xc514,	0xb1ab,	0xa022,	0x92b9,	0x8330,
	0x7bc7,	0x6a4e,	0x58d5,	0x495c,	0x3de3,	0x2c6a,	0x1ef1,	0x0f78
};
