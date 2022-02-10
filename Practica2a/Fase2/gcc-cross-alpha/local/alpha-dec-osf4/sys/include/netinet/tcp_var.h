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
 *	@(#)$RCSfile: tcp_var.h,v $ $Revision: 4.2.54.3 $ (DEC) $Date: 1998/11/02 21:24:15 $
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
 *	Base:	tcp_var.h	7.8 (Berkeley) 6/29/88
 *	Merged:	tcp_var.h	7.10 (Berkeley) 6/28/90
 */

#ifndef _TCP_VAR_H_
#define _TCP_VAR_H_
/*
 * Kernel variables for tcp.
 */

/*
 * Tcp control block, one per tcp; fields:
 */

struct tcpcb {
#ifdef __alpha
	struct	ovtcpiphdr *seg_next;	/* sequencing queue */
	struct	ovtcpiphdr *seg_prev;
#else  /* not __alpha */
	struct	tcpiphdr *seg_next;	/* sequencing queue */
	struct	tcpiphdr *seg_prev;
#endif /* __alpha */
	short	t_state;		/* state of this connection */
	short	t_softerror;		/* possible error not yet reported */
	short   pad_t_timer[TCPT_NTIMERS];	/* old counter based tcp timers */
	short	t_rxtshift;		/* log(2) of rexmt exp. backoff */
	short	t_rxtcur;		/* current retransmit value */
	short	t_dupacks;		/* consecutive dup acks recd */
	u_short	t_maxseg;		/* maximum segment size */
	char	t_force;		/* 1 if forcing out a byte */
	u_char	t_flags;
#define	TF_ACKNOW	0x01		/* ack peer immediately */
#define	TF_DELACK	0x02		/* ack, but try to delay it */
#define	TF_NODELAY	0x04		/* don't delay packets to coalesce */
#define	TF_NOOPT	0x08		/* don't use tcp options */
#define	TF_SENTFIN	0x10		/* have sent FIN */
#define TF_REQ_SCALE    0x0020		/* have/will request window scaling */
#define TF_RCVD_SCALE   0x0040		/* other side has requested scaling */
#define TF_UIOMOVED     0x0080		/* UIOMOVE mbufs in use (DART) */

/* out-of-band data */
	char	t_oobflags;		/* have some */
	char	t_iobc;			/* input character */
#define	TCPOOB_HAVEDATA	0x01
#define	TCPOOB_HADDATA	0x02

	struct	tcpiphdr t_template;	/* skeletal packet for transmit
					 * (used to be mbuf)
					 */
	struct	inpcb *t_inpcb;		/* back pointer to internet pcb */
	tcp_seq	t_timestamp;		/* used by slowtimo */
/*
 * The following fields are used as in the protocol specification.
 * See RFC793, Sep. 1981, page 21.
 */
/* send sequence variables */
	tcp_seq	snd_una;		/* send unacknowledged */
	tcp_seq	snd_nxt;		/* send next */
	tcp_seq	snd_up;			/* send urgent pointer */
	tcp_seq	snd_wl1;		/* window update seg seq number */
	tcp_seq	snd_wl2;		/* window update seg ack number */
	tcp_seq	iss;			/* initial send sequence number */
	tcp_seq	snd_wnd;		/* send window */
/* receive sequence variables */
	tcp_seq	rcv_wnd;		/* receive window */
	tcp_seq	rcv_nxt;		/* receive next */
	tcp_seq	rcv_up;			/* receive urgent pointer */
	tcp_seq	irs;			/* initial receive sequence number */
/*
 * Additional variables for this implementation.
 */
/* receive variables */
	tcp_seq	rcv_adv;		/* advertised window */
/* retransmit variables */
	tcp_seq	snd_max;		/* highest sequence number sent;
					 * used to recognize retransmits
					 */
/* congestion control (for slow start, source quench, retransmit after loss) */
	tcp_seq	snd_cwnd;		/* congestion-controlled window */
	tcp_seq snd_ssthresh;		/* snd_cwnd size threshhold for
					 * slow start exponential to
					 * linear switch
					 */
/*
 * transmit timing stuff.  See below for scale of srtt and rttvar.
 * "Variance" is actually smoothed difference.
 */
	short	old_t_idle;		/* old counter based inactivity time */
	short	old_t_rtt;		/* old counter based round trip time */
	tcp_seq	t_rtseq;		/* sequence number being timed */
	short	t_srtt;			/* smoothed round-trip time */
	short	t_rttvar;		/* variance in round-trip time */
	u_short	t_rttmin;		/* minimum rtt allowed */
	u_short	t_msslimit;		/* user-specified max segment size */
	tcp_seq max_rcvd;		/* most peer has sent into window */
	tcp_seq	max_sndwnd;		/* largest window peer has offered */
	u_char  snd_scale;		/* window scaling for send window */
	u_char  rcv_scale;		/* window scaling for recv window */
	u_char  request_r_scale;	/* pending window scaling */
	u_char  requested_s_scale;
	int	t_rptr2rxt;		/* Repeat counter for R2 RXT timer */
	int	t_rptr2cur;		/* Current repeat counter for R2 timer */
	u_short	t_peermss;		/* max segment size offered by peer */
	short	t_persistcntr;		/* persist timeout for aborting */
	short	t_keepidle;		/* idle time before keepalive probe */
	short	t_keepintvl;		/* interval between keepalive probes */
	short	t_keepcnt;		/* number of keepalive probes */
	short	t_keepinit;		/* initial connect timeout */
	u_short t_flags2;		/* more flags */
#define TF2_PUSH	0x0001		/* set push for outbound data packets */
#define TF2_NODELACK	0x0002		/* set no delayed ack for incoming packets*/
#define TF2_TSOPTENA	0x0004		/* request of timestamp option(rfc1323) */
#define TF2_TSOPT	0x0008		/* timestamp option is enabled(rfc1323) */
#define TF2_PAWS	0x0010		/* enable PAWS option(rfc1323) */
#define TF2_SACKENA	0x0020		/* enable PAWS option(rfc1323) */
#define TF2_SACK	0x0040		/* enable SACK option(rfc2018) */
#define TF2_INHERIT	(TF2_PAWS|TF2_TSOPTENA|TF2_SACKENA)
	unsigned int t_lastaction;	/* start of inactivity period */
#define t_TSRecent_age t_lastaction	/* prevents discard of valid packets when tstamp wraps */
	unsigned int t_startrtt;	/* starting time for calcing round trip time */
	unsigned int t_timer[TCPT_NTIMERS];	/* tcp timers */
  	unsigned int t_TSRecent ;	/* The timestamp of the most recent received packet */
  	unsigned int t_TSEcr ;		/* peers timestamp sent as the TSEcr field of tsopt */
	tcp_seq	 Last_ACK_sent;		/* Last ack to determin if the window moves when updating t_TSEcr */
	struct tcp_sack_field *t_sack;	/* pointer to the last sack field received. */
};

#define MAX_SACK_ENTRIES 4
/*
 * the tcp_sack_field is used to save a sack update
 * recieved as an option in incoming packet once
 * tcp_outputs the missing packet then the number
 * of entries is set to 0
 */
struct tcp_sack_field {
	short number ;		/* the number of entries in this sack update */
	struct {
		int ledge ;	/* Left edge of the segment */
		int redge ;	/* right edge of the segment */
	} entries[MAX_SACK_ENTRIES] ;
} ;

#define	intotcpcb(ip)	((struct tcpcb *)(ip)->inp_ppcb)
#define	sototcpcb(so)	(intotcpcb(sotoinpcb(so)))

/*
 * The smoothed round-trip time and estimated variance
 * are stored as fixed point numbers scaled by the values below.
 * For convenience, these scales are also used in smoothing the average
 * (smoothed = (1/scale)sample + ((scale-1)/scale)smoothed).
 * With these scales, srtt has 3 bits to the right of the binary point,
 * and thus an "ALPHA" of 0.875.  rttvar has 2 bits to the right of the
 * binary point, and is smoothed with an ALPHA of 0.75.
 */
#define	TCP_RTT_SCALE		8	/* multiplier for srtt; 3 bits frac. */
#define	TCP_RTT_SHIFT		3	/* shift for srtt; 3 bits frac. */
#define	TCP_RTTVAR_SCALE	4	/* multiplier for rttvar; 2 bits */
#define	TCP_RTTVAR_SHIFT	2	/* multiplier for rttvar; 2 bits */

/*
 * The initial retransmission should happen at rtt + 4 * rttvar.
 * Because of the way we do the smoothing, srtt and rttvar
 * will each average +1/2 tick of bias.  When we compute
 * the retransmit timer, we want 1/2 tick of rounding and
 * 1 extra tick because of +-1/2 tick uncertainty in the
 * firing of the timer.  The bias will give us exactly the
 * 1.5 tick we need.  But, because the bias is
 * statistical, we have to test that we don't drop below
 * the minimum feasible timer (which is 2 ticks).
 * This macro assumes that the value of TCP_RTTVAR_SCALE
 * is the same as the multiplier for rttvar.
 */
#define	TCP_REXMTVAL(tp) \
	(((tp)->t_srtt >> TCP_RTT_SHIFT) + (tp)->t_rttvar)

#ifdef __alpha
#define REASS_MBUF(ov) (*(struct mbuf **)&((struct ovtcpiphdr *)(ov))->ti_rmb)
#else
#define REASS_MBUF(ti) (*(struct mbuf **)&((ti)->ti_t))
#endif /* __alpha */

#include <netinet/tcp_stat.h>

#define _TCBHASHSIZE	512		/* default value for tcbhashsize */
#define TCP_SENDSPACE	32*1024		/* default value for tcp_sendspace */
#define TCP_RECVSPACE	32*1024		/* default value for tcp_recvspace */
#define TCPREXMTTHRESH	3		/* default retransmit threshold */

#ifdef _KERNEL
#if	NETSYNC_LOCK
extern	simple_lock_data_t	misc_tcp_lock;
#define TCPMISC_LOCKINIT()	simple_lock_setup(&misc_tcp_lock, misc_tcp_li)
#define TCPMISC_LOCK()		simple_lock(&misc_tcp_lock)
#define TCPMISC_UNLOCK()	simple_unlock(&misc_tcp_lock)
#else	/* !NETSYNC_LOCK */
#define TCPMISC_LOCKINIT()
#define TCPMISC_LOCK()
#define TCPMISC_UNLOCK()
#endif

#define TCBMAXQUEUES 64
extern int ipqshiftbits ;
#define TCBQINDEX(addr) ((((addr)>>ipqshiftbits)&0xff) % tcbqNum)
extern	int tcp_skip_local_cwnd  ;
extern	int tcp_cwnd_segments ;
extern	int tcp_compat_42;
extern	int tcp_urgent_42;
extern	int tcbqNum ;
extern	struct	inpcb tcb[];		/* head of queue of active tcpcb's */
extern	struct	tcpstat tcpstat;	/* tcp statistics */
extern	struct	__inpcb_hashbucket tcbinit;	/* not-yet-connected pcbs */
extern	struct	__inpcb_hashbucket *tcbhashtab; /* connected pcbs */
extern	int	tcbhashmod;		/* buckets in tcbhashtab */
extern	int	tcbhashsize;		/* initial value for tcbhashmod */
extern	int tcbquickbindtab[] ;
extern	int tcbquickbind ;
extern struct tcb_hash_stats_struct {
	int     ChainHiwatCount ;
	int     ChainHiwatThreshold ;
	int     EmptyWarnCount ;
	int     EmptyWarnThreshold ;
	int     FastActive ;
	int     FastIdle ;
	int     SlowActive ;
	int 	AllTimeSlowActive ;
	int     SlowIdle ;
	int     ChainHiwat ;
	int 	AllTimeChainHiwat ;
	int     ChainLowat ;
	int     EmptyBuckets ;
	int     TotalBuckets ;
	int     TotalTcpConns ;
	int     AllTimeMaxTcpConns ;
} tcbhashstats ;

extern struct	__inpcb_hashbucket *HashHiwatBucket ;
extern struct	__inpcb_hashbucket *HashLowatBucket ;

#define FAILSAFEHASHTABLE	32
extern int total_tcp_inpcbs;
extern int tcp_keepalive_default; /* used to make keep alive the default mod */

#endif /* _KERNEL */
#endif /* _TCP_VAR_H_*/

