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
 *	@(#)$RCSfile: ip_stat.h,v $ $Revision: 1.1.7.3 $ (DEC) $Date: 1999/02/16 23:50:06 $
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
#ifndef	_NETINET_IP_STAT_H
#define	_NETINET_IP_STAT_H

/* ******** any changes to this struct should also be reflected
 * ******** in the routine to consolidate the per cpu stats.
 * ******** netaddstats of tcp_timer.c */
struct	ipstat {
	int	ips_total;		/* total packets received */
	int	ips_badsum;		/* checksum bad */
	int	ips_tooshort;		/* packet too short */
	int	ips_toosmall;		/* not enough data */
	int	ips_badhlen;		/* ip header length < data size */
	int	ips_badlen;		/* ip length < ip header length */
	int	ips_fragments;		/* fragments received */
	int	ips_fragdropped;	/* frags dropped (dups, out of space) */
	int	ips_fragtimeout;	/* fragments timed out */
	int	ips_forward;		/* packets forwarded */
	int	ips_cantforward;	/* packets rcvd for unreachable dest */
	int	ips_redirectsent;	/* packets forwarded on same net */
	int	ips_noproto;		/* unknown or unsupported protocol */
	int	ips_delivered;		/* packets consumed here */
	int	ips_localout;		/* total ip packets generated here */
	int	ips_odropped;		/* lost packets due to nobufs, etc. */
	int	ips_reassembled;	/* total packets reassembled ok */
	int	ips_fragmented;		/* output packets fragmented ok */
	int	ips_ofragments;		/* output fragments created */
	int	ips_cantfrag;		/* don't fragment flag was set, etc. */
        int     ips_accessdeny;	        /* total access filter denials */
	int	spares[10];
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t ips_lock;	/* statistics lock */
#endif
};
/*
 * TCP statistics.
 */
struct	tcpstat {
	u_int	tcps_connattempt;	/* connections initiated */
	u_int	tcps_accepts;		/* connections accepted */
	u_int	tcps_connects;		/* connections established */
	u_int	tcps_drops;		/* connections dropped */
	u_int	tcps_conndrops;		/* embryonic connections dropped */
	u_int	tcps_closed;		/* conn. closed (includes drops) */
	u_int	tcps_segstimed;		/* segs where we tried to get rtt */
	u_int	tcps_rttupdated;	/* times we succeeded */
	u_int	tcps_delack;		/* delayed acks sent */
	u_int	tcps_timeoutdrop;	/* conn. dropped in rxmt timeout */
	u_int	tcps_rexmttimeo;	/* retransmit timeouts */
	u_int	tcps_persisttimeo;	/* persist timeouts */
	u_int	tcps_keeptimeo;		/* keepalive timeouts */
	u_int	tcps_keepprobe;		/* keepalive probes sent */
	u_int	tcps_keepdrops;		/* connections dropped in keepalive */

	u_int	tcps_sndtotal;		/* total packets sent */
	u_int	tcps_sndpack;		/* data packets sent */
	u_int	tcps_sndbyte;		/* data bytes sent */
	u_int	tcps_sndrexmitpack;	/* data packets retransmitted */
	u_int	tcps_sndrexmitbyte;	/* data bytes retransmitted */
	u_int	tcps_sndacks;		/* ack-only packets sent */
	u_int	tcps_sndprobe;		/* window probes sent */
	u_int	tcps_sndurg;		/* packets sent with URG only */
	u_int	tcps_sndwinup;		/* window update-only packets sent */
	u_int	tcps_sndctrl;		/* control (SYN|FIN|RST) packets sent */

	u_int	tcps_rcvtotal;		/* total packets received */
	u_int	tcps_rcvpack;		/* packets received in sequence */
	u_int	tcps_rcvbyte;		/* bytes received in sequence */
	u_int	tcps_rcvbadsum;		/* packets received with ccksum errs */
	u_int	tcps_rcvbadoff;		/* packets received with bad offset */
	u_int	tcps_rcvshort;		/* packets received too short */
	u_int	tcps_rcvduppack;	/* duplicate-only packets received */
	u_int	tcps_rcvdupbyte;	/* duplicate-only bytes received */
	u_int	tcps_rcvpartduppack;	/* packets with some duplicate data */
	u_int	tcps_rcvpartdupbyte;	/* dup. bytes in part-dup. packets */
	u_int	tcps_rcvoopack;		/* out-of-order packets received */
	u_int	tcps_rcvoobyte;		/* out-of-order bytes received */
	u_int	tcps_rcvpackafterwin;	/* packets with data after window */
	u_int	tcps_rcvbyteafterwin;	/* bytes rcvd after window */
	u_int	tcps_rcvafterclose;	/* packets rcvd after "close" */
	u_int	tcps_rcvwinprobe;	/* rcvd window probe packets */
	u_int	tcps_rcvdupack;		/* rcvd duplicate acks */
	u_int	tcps_rcvacktoomuch;	/* rcvd acks for unsent data */
	u_int	tcps_rcvackpack;	/* rcvd ack packets */
	u_int	tcps_rcvackbyte;	/* bytes acked by rcvd acks */
	u_int	tcps_rcvwinupd;		/* rcvd window update packets */
	u_int	tcps_nooutputbuffs;	/* mget returned enobuffs and we sent a tcpQuench */
	u_int	tcps_skipchecksum ;	/* no checksum generated for packet */
	u_int	tcps_pendingconnectiondropped ;	/* temporary listen has gone away*/
	u_int	tcp_ignored_tsopt ;	/* number of timestamp options seen for connections with
					   timestamps disabled */
	u_int	tcp_processing_tsopt ;  /* number of incoming packets with timestamp option seen */
	int	spares[10];
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t tcps_lock;	/* statistics lock */
#endif
};

struct	udpstat {
				/* input statistics: */
	int	udps_ipackets;		/* total input packets */
	int	udps_hdrops;		/* packet shorter than header */
	int	udps_badsum;		/* checksum error */
	int	udps_badlen;		/* data length larger than packet */
	int	udps_noport;		/* no socket on port */
	int	udps_noportbcast;	/* of above, arrived as broadcast */
	int	udps_noportmcast;	/* of above, arrived as multicast */
	int	udps_fullsock;		/* not delivered, input socket full */
	int	udpps_pcbcachemiss;	/* input packets missing pcb cache */
				/* output statistics: */
	int	udps_opackets;		/* total output packets */
	int	spares[10];
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t udps_lock;		/* statistics lock */
#endif
};

/* ******** any changes to this struct should also be reflected
 * ******** in the routine to consolidate the per cpu stats.
 * ******** netaddstats of tcp_timer.c */
#endif



