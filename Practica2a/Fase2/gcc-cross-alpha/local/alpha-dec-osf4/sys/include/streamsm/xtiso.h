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
 * @(#)$RCSfile: xtiso.h,v $ $Revision: 4.2.31.2 $ (DEC) $Date: 1997/08/29 19:56:10 $
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */

#ifndef _XTISO_H
#define _XTISO_H

#include <streamsm/xti.h>
#include <streamsm/xtiso_config.h>

extern int somaxconn;


/* 
 * Connection Indication Structure
 */
struct xtiseq { 
	long    seq_no;			/* sequence number		*/
	int     seq_used;		/* used or not?			*/
	struct  socket *seq_so;		/* associated socket		*/
};

/* Statically defined */
#define XTI_MAXOPENS	(minor(~0) + 1)


#if XTI_SPEC1170
/*
 * In the following structure certain values such as xti_rcvbuf are
 * unsigned int, although the XTI interface defines them as long.
 * Since at the socket level, these quantities are stored in int, this
 * will not be a problem.  Even if we need to change these in future,
 * it will not have any migration issues, as this is a purely internal
 * structure, not used anywhere else except xtiso.c
 *
 */
struct xti_opts {
	unsigned int		xopt_rcvbuf;
	unsigned int		xopt_rcvlowat;
	unsigned int		xopt_sndbuf;
	unsigned int		xopt_sndlowat;
	struct linger		xopt_linger;
	char *			xopt_opts_prot; /* protocol specific stuff */
	unsigned short		xopt_opts_maxlen; /* prot handler sets this */
	char			xopt_debug;
	char			xopt_flags;

};

/* udp options structure */
struct udpopts {
	char		udp_checksum;
};

/* tcp options structure */
struct tcpopts {
	char		tcp_nodelay;
	unsigned int	tcp_maxseg;
	struct t_kpalive tcp_keepalive;
};

/* Internet Protocol specific */
struct xti_opts_inet {
	/* ip level defaults */
	struct mbuf *		options;
	unsigned int		broadcast;
	unsigned int		dontroute;
	unsigned int		reuseaddr;
	unsigned char		tos;
	unsigned char		ttl;
	/* transport level defaults */
	union {
	  struct udpopts uopt;		/* udp options */
	  struct tcpopts topt;		/* tcp options */
	} transport;
};

#define xti_rcvbuf	xti_def_opts->xopt_rcvbuf
#define xti_rcvlowat	xti_def_opts->xopt_rcvlowat
#define xti_sndbuf	xti_def_opts->xopt_sndbuf
#define xti_sndlowat	xti_def_opts->xopt_sndlowat
#define xti_linger	xti_def_opts->xopt_linger
#define xti_debug	xti_def_opts->xopt_debug

#define ip_broadcast(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->broadcast
#define ip_dontroute(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->dontroute
#define ip_reuseaddr(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->reuseaddr
#define ip_options(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->options
#define ip_tos(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->tos
#define ip_ttl(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->ttl

#define tcp_nodelay(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->transport.topt.tcp_nodelay

#define tcp_maxseg(x)	((struct xti_opts_inet *)(x->xopt_opts_prot))->transport.topt.tcp_maxseg

#define tcp_keepalive(x) ((struct xti_opts_inet *)(x->xopt_opts_prot))->transport.topt.tcp_keepalive

#define udp_checksum(x) ((struct xti_opts_inet *)(x->xopt_opts_prot))->transport.uopt.udp_checksum
/*
 * Sizes of individual options value (including alignment) 
 *
 */
/* XTI Generic */
#define SZ_RCVBUF	T_ALIGN(sizeof(unsigned long))
#define SZ_RCVLOWAT	T_ALIGN(sizeof(unsigned long))
#define SZ_SNDBUF	T_ALIGN(sizeof(unsigned long))
#define SZ_SNDLOWAT	T_ALIGN(sizeof(unsigned long))
#define SZ_DEBUG	T_ALIGN(sizeof(unsigned long))	/* We have single value only */
#define SZ_LINGER	T_ALIGN(sizeof(struct t_linger))


/* INET Specific - IP */
#define SZ_BROADCAST	T_ALIGN(sizeof(unsigned int))
#define SZ_DONTROUTE	T_ALIGN(sizeof(unsigned int))
#define SZ_REUSEADDR	T_ALIGN(sizeof(unsigned int))
#define SZ_TOS		T_ALIGN(sizeof(unsigned char))
#define SZ_TTL		T_ALIGN(sizeof(unsigned char))
#define SZ_OPTIONS(x)	T_ALIGN((ip_options(x) ? ip_options(x)->m_len : 0))

/* INET Specific - TCP */
#define SZ_KEEPALIVE	T_ALIGN(sizeof(struct t_kpalive))
#define SZ_MAXSEG	T_ALIGN(sizeof(unsigned long))
#define SZ_NODELAY	T_ALIGN(sizeof(unsigned long))


/* INET Specific - UDP */
#define SZ_CHECKSUM	T_ALIGN(sizeof(unsigned long))

/* Total size required to return all Generic options - fixed */
#define OPT_XTIGENERICSIZE	SZ_RCVBUF+SZ_RCVLOWAT+SZ_SNDBUF+SZ_SNDLOWAT+\
				SZ_DEBUG+SZ_LINGER+\
				6*sizeof(struct t_opthdr) /* 6 options */

/* Total size required to return all IP options - variable on IP layer */
#define OPT_INETIPSIZE(x)	SZ_BROADCAST+SZ_DONTROUTE+SZ_REUSEADDR+\
				SZ_TOS+SZ_TTL+SZ_OPTIONS(x)+\
				6*sizeof(struct t_opthdr) /* 6 options */

/* Total size required to return all TCP options - fixed */
#define OPT_INETTCPSIZE		SZ_KEEPALIVE+SZ_MAXSEG+SZ_NODELAY+\
				3*sizeof(struct t_opthdr) /* 3 options */

/* Total size required to return all TCP options - fixed */
#define OPT_INETUDPSIZE		SZ_CHECKSUM+\
				1*sizeof(struct t_opthdr) /* 1 option */

/* Miscellaneous flags (auxiliary) various options management routines */
/* None, just return what's asked for */
#define XTI_OPTNULL		0x0000
/* 
 * Return all opts, subject to interpretation of other flags
 * (Other flags will possibly limit the scope of "all"
 */
#define XTI_OPTALLOPTS		0x0001	
/*
 * Return only association related options for any level
 * (if a level such as INET_TCP does not have association related options,
 * then just return.
 */
#define XTI_OPTASSOCOPTS	0x0002
/*
 * Return only the level that's in the opt->level of the first option in thr
 * buffer
 */
#define XTI_OPTLEVELOPTS	0x0004
/* Miscellaneous */
#define XTI_BADLEVEL		-1
#define XTI_BADNAME		-1
#endif
 
#define TPI_LEGACY              1

/*
 * XTI-Socket Control Block
 */
struct xticb {
	int	 xti_state;		/* state of transport provider	*/
	long	 xti_flags;		/* internal flags, see below	*/
	dev_t    xti_minor;             /* minor device # 		*/

	struct   socket   *xti_so;	/* corresponding socket		*/
	int	 xti_sostate;		/* safe state of socket		*/
	int	 xti_soerror;		/* safe socket error		*/
	long	 xti_sorcount;		/* safe read-count of socket	*/
	long	 xti_sowspace;		/* safe write-space of socket	*/
	int	 xti_sosnap;		/* async state of socket	*/

	struct   socket   *xti_lso;	/* "saved" listening socket	*/
	int	 xti_maxqlen;
	struct   xtiseq    *xti_seq;		
					/* outstanding conn ind seq #s	*/
	short	 xti_qlen;		/* # of conn ind. allowed	*/
        short	 xti_cindno;		/* # of outstanding conn ind	*/

	int 	 xti_seqcnt;		/* sequence counter 		*/
        int	 xti_pendind;		/* pending indication		*/
	long     xti_tsdu;
	long     xti_etsdu;

	queue_t  *xti_rq;		/* stream read queue ptr	*/
	queue_t  *xti_wq;		/* stream write queue ptr	*/

	mblk_t	 *xti_wndata;		/* pending normal data for write */
	mblk_t	 *xti_wexpdata;		/* pending expedited data for write */
	struct   mbuf *xti_wnam;	/* destination addr of unitdata	*/

	struct   mbuf *xti_rdata;	/* pending read-side data	*/
	struct   mbuf *xti_rnam;	/* source addr of unitdata      */
	int      xti_rflags;		/* pending read-side flags	*/
					/* xti error recovery		*/
	int	(*xti_pendcall)();
	int	xti_bufcallid;
	int	xti_tlierr;
	int	xti_unixerr;
	int	xti_errtype;

	struct   xtisocfg *xti_cfg;	/* link back to cfg head	*/
#define	xti_proto xti_cfg->xti_cfgproto	/* xtiproto for xticb		*/

#if	XTI_SPEC1170
	/*
	 * The following will be assigned only if some optmgmt related
	 * call is made.  It till trickle into a protocol dependent
	 * structure as well.
	 *
	 */
	struct xti_opts	*xti_def_opts; /* default options               */
#if 	TPI_LEGACY
	int	 xti_userstate;		/* state of transport provider	*/

#endif
#endif/*XTI_SPEC1170*/
};

/*
 * XTI configuration block.
 */
struct xtisocfg {
	struct	xtisocfg *	xti_cfgnext;	/* more config structs	*/
	dev_t 			xti_cfgmajor;	/* major device # 	*/
	int			xti_cfgnopen;	/* # of current opens	*/
	struct	xtiproto	xti_cfgproto;	/* protocol information	*/
	decl_simple_lock_data(, xti_cfglock)
};

/* 
 * If the transport supports options management then extract the following 
 * It serves as a part of the t_info structure which can be changed through
 * t_optmgmt().
 */
struct topt_xtiinfo
{
    int	etsdulen;			/* expedited data len */
    int	connectlen;			/* connect user data len */
    int disconlen;			/* disconnect user data len */
};

/*
 * xti_proto_info uses the following defines
 */
#define XTI_NO_OPTS	0		/* There are no setopts/getopts */
#define XTI_NS		-2L		/* Not supported */

/*
 * Socket types
 */
#define XTI_NEWSOCK     1		/* New Socket, open		*/
#define XTI_NOSOCK	2		/* Socket disabled, no close 	*/
#define XTI_CLOSESOCK	3		/* Close indicator 		*/

/* 
 * Internal XTI Flags
 */
#define XTI_ACTIVE	0x0001		/* if set, this xticb is in use */
#define XTI_FATAL	0x0002          /* fatal condition occurred     */
#define XTI_DISCONMAIN  0x0004          /* disconnect the main conn.    */
#define XTI_PRIV        0x0008          /* created by privileged user   */
#define XTI_MORENDATA	0x0010          /* more normal data expected from TU */
#define XTI_MOREEXPDATA	0x0020		/* more expedited normal data
					   expected from TU */
#define XTI_FLOW	0x0040		/* flow control for normal data  */
#define XTI_SETEOR      0x0080          /* EOR flag for record-oriented  TP */
#define XTI_TIMEOUT	0x0200		/* timeout active 		*/
#define XTI_ISCLOSING	0x0400		/* close in progress		*/
/* Removed the following
#define XTI_OPTINIT	0x1000		/* options initialized		*/

/*
 * Options Flags (uchar)
 */
#define XTI_OPTMODIFY	0x01		/* options modified		*/

/* 
 * State for connection indications
 */
#define	XTIS_AVAILABLE	0		/* Available			*/
#define XTIS_AWAITING	1		/* Awaiting acceptance		*/
#define XTIS_ACTIVE	2		/* Connected/accepted		*/
#define XTIS_LOST	3		/* Connection lost before accept*/

/*
 * Disconnect reason codes
 */
#define XTID_TPINIT		1  /* Initiated by transport provider    */
#define XTID_REMWITHDRAW	2  /* Connect req withdrawn by remote    */
#define XTID_REMREJECT  	3  /* Connect req rejected by remote     */
#define XTID_REMINIT		4  /* Disconnect req Initiated by remote */

/*
 * UDERR IND error types
 */
#define XTIU_BADOPTSZ		1  /* Initiated by transport provider    */
#define XTIU_BADMSGSZ		2  /* Connect req withdrawn by remote    */
#define XTIU_NOOPT		1  /* UDP Option not supported           */

#define XTI_INFO_ID	5010	/* module/driver ID */

/*
 * Flow control parameters - big enough for socket's default
 * TCP window, with lowater set to refill promptly.
 */
#define XTI_INIT_HI	6400
#define XTI_INIT_LO	(XTI_INIT_HI - 512)

/*
 * Debugging
 */
#if	XTIDEBUG

#define XTIF_ALL	(~0)
#define XTIF_CONFIGURE	0x00000001	/* configuration  		*/
#define XTIF_OPEN	0x00000002	/* open routine  		*/
#define XTIF_WPUT	0x00000004	/* write put routine 		*/
#define XTIF_MISC	0x00000008	/* miscellaneous trace 		*/
#define XTIF_WSRV	0x00000010	/* write service routine	*/
#define XTIF_OUTPUT	0x00000020	/* xti output routine		*/
#define XTIF_INPUT	0x00000040	/* xti input routine		*/
#define XTIF_EVENTS	0x00000080	/* socket event tracing		*/
#define XTIF_INFO	0x00000100	/* info request			*/
#define XTIF_BINDING	0x00000200	/* binding-related tracing	*/
#define XTIF_CONNECT	0x00000400	/* connect/disconnect trace	*/
#define XTIF_DATA	0x00000800	/* data xfer trace		*/
#define XTIF_SEND	0x00001000	/* xti send routine trace	*/
#define XTIF_RECV	0x00002000	/* xti receive routine trace 	*/
#define XTIF_CLOSE	0x00004000	/* close-related trace		*/
#define XTIF_ERRORS	0x00008000	/* stream error trace		*/
#define XTIF_SOCKET	0x00010000	/* socket misc			*/
#define XTIF_CHECKPOINT	0x00020000	/* routine entry trace		*/
#define XTIF_SEND_FLOW	0x00040000	/* send flow control trace	*/
#define XTIF_STRLOG	0x00080000	/* enable strlog trace		*/
#define XTIF_OPTMGMT	0x00100000	/* optmgmt stuff 		*/
#define XTIF_BREAK	0x40000000	/* enable debugger on "panic"	*/
#define XTIF_PANIC	0x80000000	/* enable "real" panic		*/

extern int xtiDEBUG;

#define PUTNEXT(q,mp)	xti_putnext((q),(mp))
#define XTITRACE(f,v)	do { if (xtiDEBUG & (f)) { v } } while (0)
#define CHECKPOINT(v)	XTITRACE(XTIF_CHECKPOINT, \
			 printf( "%s()\n",(v));)

#else	/* !XTIDEBUG */

#define PUTNEXT(q,mp)	putnext((q),(mp))
#define XTITRACE(f,v)
#define CHECKPOINT(v)

#endif	/* !XTIDEBUG */

#endif /* _XTISO_H */
