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
 * @(#)$RCSfile: if_ottomaint.h,v $ $Revision: 1.1.3.2 $ (DEC) $Date: 1994/10/20 22:20:17 $
 */
/* Copyright 1993 Digital Equipment Corporation.               */
/* Distributed only by permission.                             */
/* Last modified on Mon Sep 27 17:40:15 1993 by burrows        */
/* Structure used to send and receive non-ethernet packets.
 * To use:
 *				   struct ottosndrcv sndrcv;
 *   create a socket:		   int s = socket (AF_INET, SOCK_DGRAM, 0);
 *
 *   fill in sndrcv.ifreq.name	   strcpy (sndrcv.ifreq.name, "otto0");
 *   fill in the fields		   sndrcv.length = length of buffer to send/rcv
 * 				   sndrcv.data = address of buffer
 *				   sndrcv.link = 0 or 1 (send only)
 * do the operation		   ioctl (s, SIOCOTTOSND, &sndrcv);
 *			       or  ioctl (s, SIOCOTTORCV, &sndrcv);
 *
 * Returns -1 on error, 0 otherwise.
 * 
 * After successful receive, sndrcv.length contains length of packet,
 * and sndrcv.link contains link that packet arrived on.
 *
 * SIOCOTTORCV is interruptible by signals.
 * SIOCOTTOSND will not send a packet that is an encapsulated Ethernet packet
 * unless the caller is root.  
 *
 * Names of all interfaces on the system can be found with
 * 		ioctl (s, SIOCGIFCONF, ifconf)
 * on the same type of socket.
 *
 * Restrictions
 * The receive side currently buffers only 4 packets.
 * The caller should call SIOCOTTORCV often enough to avoid losing packets.
 * Currently, the only way to poll for received packets is by setting
 * a timer to deliver a signal soon after making the SIOCOTTORCV call.
 *
 * Sent and received packets must be no longer than 1600 bytes,
 * including Autonet header.  Transmitted packets that are not a multiple
 * or 8 bytes in length are padded with arbitrary data to the next 8
 * byte boundary.
 */
struct ottosndrcv {
	struct ifreq ifreq;
	int link;		/* 0/1  link to send on, link received from */
	char *data;		/* point to packet/buffer */
	unsigned length;	/* length of packet/buffer */
};
#ifdef __osf__
#define SIOCOTTOSND _IOWR('i', 70, struct ottosndrcv)
#define SIOCOTTORCV _IOWR('i', 71, struct ottosndrcv)
#else
#define SIOCOTTOSND _IOWR('i', 59, struct ottosndrcv)
#define SIOCOTTORCV _IOWR('i', 60, struct ottosndrcv)
#endif

/* This structure is returned from the SIOCOTTOINFO ioctl.
 *
 *				struct ottoinfo info;
 * create a socket		int s = socket (AF_INET, SOCK_DGRAM, 0);
 * fill in info.ifreq.name      strcpy (info.ifreq.name, "otto0");
 * do the operation		ioctl (s, SIOCOTTOINFO, &info);
 *
 * Returns 0 on success, -1 on error.   On success, rest of data
 * structure becomes valid.
 */
/* DON'T MAKE THIS STRUCT ANY BIGGER.  It's nearly over the 127 byte limit
 * imposed by ioctl
 */
struct ottoinfo {
	struct ifreq ifreq;
	struct ottolinkinfo {
		char up;                 /* if driver thinks this link is up */
		char working;            /* if portinfo packets were xchged */
		u_short sa;              /* this link's short address */
		time_t updated;          /* time when sa updated */
		unsigned prods;          /* prods since last response */
		u_short partitionsize;   /* switches in autonet */
		u_short switchsa;        /* switch's short address */
		u_char epoch[8];         /* reconfiguration epoch number */
		u_char rootUID[8];       /* root UID of autonet tree */
		u_char switchuid[6];     /* uid of local switch */
	} link[2];
};
#ifdef __osf__
#define SIOCOTTOINFO _IOWR('i', 72, struct ottoinfo)
#else
#define SIOCOTTOINFO _IOWR('i', 61, struct ottoinfo)
#endif


/* Parts of this structure are returned by a OTTO on a SIOCRDCTRS call when the
 * ctr_type field of the ctrreq structure is not CTR_ETHER.  See
 * net/if.h for details of the SIOCRDCTRS call.
 * 	ctr_type value			structure returned
 *      --------------                  ------------------
 *	OTTO_CTR_BOTHLINKS		struct otto_stats_bothlinks
 *	OTTO_CTR_LINK0			struct otto_stats_perlink for link 0
 *	OTTO_CTR_LINK1			struct otto_stats_perlink for link 1
 */
#define OTTO_CTR_BOTHLINKS	(CTR_ETHER+1)
#define OTTO_CTR_LINK0		(CTR_ETHER+2)
#define OTTO_CTR_LINK1		(CTR_ETHER+3)
struct otto_stats {
	struct otto_stats_bothlinks {
		unsigned short reset;		/* device reset */
		unsigned short xmt_added_mbuf;	/* xmt added mbuf for hdr */
		unsigned short xmt_unicast_too_big;/* bcastsa unicast too big*/
		unsigned short xmt_multicast_too_big;/* multicast pkt to big */
		unsigned short xmt_too_many_xmt_frags;/* too many frags=>copy */
		unsigned short xmt_bad_aligned_frag;/* bad align=>copy on xmt */
		unsigned short xmt_bad_len_frag;/* bad len frag => copy */
		unsigned short xmt_short_frag;	/* short frag => copy */
		unsigned short simple_send;	/* did simplesendpkt */
		unsigned short status_change;	/* times LEDs were set */
		unsigned short no_free_desc;	/* no free buffer descriptor */
		unsigned short too_many_loops;	/* 1000 loops in isr */ 
		unsigned short tran_error;	/* OTTO transfer error */
		unsigned short dma_error;	/* DMA error in LHX register */
		unsigned short spare0;		/* spare */
		unsigned short spare1;		/* spare */
		unsigned short spare2;		/* spare */
		unsigned short spare3;		/* spare */
		unsigned short spare4;		/* spare */
		unsigned short spare5;		/* spare */
		unsigned short spare6;		/* spare */
		unsigned short spare7;		/* spare */
	} bothlinks;
	struct otto_stats_perlink {
		unsigned short xmt_error;	/* transmit error */
		unsigned short xmt_dma_error;	/* xmt DMA error */
		unsigned short xmt_frag_oflow;	/* xmt fragment overflow */
		unsigned short rcv_dma_error;	/* rcv DMA error */
		unsigned short rcv_overflow;	/* rcv frag overflow */
		unsigned short rcv_error;	/* receive error */
		unsigned short rcv_crc_error;	/* rcv CRC error */
		unsigned short rcv_violation;	/* rcv violation */
		unsigned short rcv_frmxcrc;	/* rcv frame err w/o CRC err */
		unsigned short rcv_frame_err;	/* rcv frame err */
		unsigned short rcv_len_err;	/* rcv length error */
		unsigned short rcv_discard;	/* rcv pkt not for us */
		unsigned short xmt_ring_full;	/* can't xmt because ring full*/
		unsigned short saw_syntax_error;	/* saw a syntax error */
		unsigned short saw_violation;		/* saw a violation */
		unsigned short missed_pkt;		/* misssed a pkt */
		unsigned short rcv_pkt_too_short;/* rcv pkt < header length */
		unsigned short rcv_pkt_too_large;/* pkt len > buffer size */
		unsigned short rcv_portinfo;	/* rcvd rcvportinfo */
		unsigned short rcv_non_ether;	/* rcvd non-ether pkt */
		unsigned short rcv_arp;		/* rcvd a SA arp pkt */
		unsigned short rcv_bad_align;	/* rcvd badly aligned ip hdr */
		unsigned short rcv_non_ether_long;/* rcvd long non-ether pkt */
		unsigned short rcv_non_ether_excess;/* discard non-ether pkt */
		unsigned short spare0;		/* spare */
		unsigned short spare1;		/* spare */
		unsigned short spare2;		/* spare */
		unsigned short spare3;		/* spare */
		unsigned short spare4;		/* spare */
		unsigned short spare5;		/* spare */
		unsigned short spare6;		/* spare */
		unsigned short spare7;		/* spare */
	} perlink[2];
};
