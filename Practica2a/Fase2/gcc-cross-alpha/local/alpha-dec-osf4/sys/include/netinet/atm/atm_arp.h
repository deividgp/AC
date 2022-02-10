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
 * @(#)$RCSfile: atm_arp.h,v $ $Revision: 1.1.23.2 $ (DEC) $Date: 1998/09/25 19:54:13 $
 */

#ifndef _ATM_ATM_ARP_H_
#define _ATM_ATM_ARP_H_

#include <machine/endian.h>
#include <net/net_globals.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <vm/vm_kern.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>

#include <sys/mbuf.h>
#include <sys/socket.h>

#include <net/if.h>
#include <net/route.h>
#include <net/netisr.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_var.h>
#include <netinet/if_ether.h>
#include <kern/thread.h>

#include <atm/sys/atm_osf.h>
#include <atm/sys/atm.h>
#include <atm/sys/atm_adi.h>
#include <atm/sys/atm_cmi.h>
#include <atm/sys/atm_smi.h>


/* Size of the ATM ARP table */
#define ATM_ARP_TABLE_SZ	256

/* defines for atm_arp_alloc_entry */
#define ATM_ARP_NOWAIT 0
#define ATM_ARP_WAITOK 1

/* Typical return values from atm_arp_* routines */
#define ATM_ARP_FAILURE		1  /* A generic failure */
#define ATM_ARP_RESOLVED	2  /* ARP address was resolved */
#define ATM_ARP_UNRESOLVED	3  /* ARP address is not resolved yet */
#define ATM_ARP_UNAVAILABLE	4  /* ARP address is unavailable */
#define ATM_ARP_LOOPBACK	5  /* The destination address is of our own */

/* Hashing macro to look up an entry in the table. */
#define ATM_ARP_HASH(index, ip_addr) {\
	u_short tmp_val;\
	tmp_val = (u_short)((ip_addr.s_addr & 0x0000ffff) ^\
			    ((ip_addr.s_addr & 0xffff0000) >> 16));\
	index = (tmp_val & 0x00ff) ^ ((tmp_val & 0xff00) >> 8);\
};

/* 
 * As an end system, we have to only deal with 20 byte
 * ATM NSAP addresses. All the three NSAP formats - DCC, ICD and E.164 -
 * are 20 bytes long. The native E.164 address is eight bytes long.
 * Classical IP addresses are 4 bytes long.
 */
#define IPADDR_LEN		        sizeof(struct in_addr)
#define ATMADDR_LEN			0x14	/* ATM address len */
#define E164_LEN 			0x08

/* 
 * Masks for accessing the length fields for address and subaddress
 * fields.
 */
#define	ATM_ARP_OCTET_LEN_M	0x3F		/* len of the address */
#define ATM_ARP_ADDR_SEL_M	0x40		/* Type of address    */
#define ATM_ARP_E164_ADDR	0x40		/* bit6 == 1 */
#define ATM_ARP_FORUM_ADDR	0x00		/* bit 6 == 0 */


/* Protocol defined values */

#define	ATM_ARP_HARDWARE_TYPE		0x0013
#define	ATM_ARP_PROTOCOL_TYPE_IP	0x0800	/* IP */
#define	ATM_ARP_REQUEST			1
#define	ATM_ARP_REPLY			2
#define	ATM_INARP_REQUEST		8
#define	ATM_INARP_REPLY			9
#define	ATM_ARP_NAK			10

/*
 * The following is the PDU information for an ATM ARP packet.
 * Parts of the structure are used to construct a PDU for
 * sending ATM ARP packets. The PDU show contains the LLC 
 * information.
 */
struct atm_arp_hdr {
#define ATM_ARP_LLC		8
    u_char	llc_info[ATM_ARP_LLC];	/* 8 bytes of LLC info */
    u_short	ar_hrd;		/* The hardware type = 0x0013 */
    u_short	ar_pro;		/* The protocol type = 0x0800 */
    u_char	ar_shtl;	/* The type & len. of source ATM address */
    u_char	ar_sstl;	/* The type & len. of source ATM subaddress */
    u_short	ar_op;		/* The operation code - REQUEST, REPLY, NAK */
    u_char	ar_spln;	/* The len. of source protocol address */
    u_char	ar_thtl;	/* The type & len of target ATM address */
    u_char	ar_tstl;	/* The type & len of target ATM subaddress */
    u_char	ar_tpln;	/* The len of the target protocol address */
/*
 *  Other fields are variable. If ar_sstl = 0 then ar_ssa is not
 *  present. Similarly if ar_tstl = 0 then ar_tsa is not present.
 */
/*    u_char  *ar_sha;		   The source ATM address */
/*    u_char  *ar_ssa;		   The source ATM subaddressaddress */
/*    u_char  *ar_spa;	           The source protocol address */
/*    u_char  *ar_tha;             The target ATM address */
/*    u_char  *ar_tsa;             The target ATM subaddress */
/*    u_char  *ar_tpa;		   The target protocol address */
};


#define ATM_ARP_APPEND_LLC(pkt)\
{\
     bcopy(llc_head, pkt, ATM_ARP_LLC);\
}
#define	ATM_AR_SHA(ah)	   ((u_char *)((ah) + 1))
#define	ATM_AR_SSA(ah)	   (ATM_AR_SHA(ah)+((ah)->ar_shtl&ATM_ARP_OCTET_LEN_M))
#define ATM_AR_SPA(ah)     (ATM_AR_SSA(ah)+((ah)->ar_sstl&ATM_ARP_OCTET_LEN_M))
#define ATM_AR_THA(ah)     (ATM_AR_SPA(ah)+(ah)->ar_spln)
#define ATM_AR_TSA(ah)     (ATM_AR_THA(ah)+((ah)->ar_thtl&ATM_ARP_OCTET_LEN_M))
#define ATM_AR_TPA(ah)     (ATM_AR_TSA(ah)+((ah)->ar_tstl&ATM_ARP_OCTET_LEN_M))

typedef struct atm_arp_data  atm_arp_data_t;
typedef struct atm_arp_data  *atm_arp_data_p;

typedef struct atm_arp_addr  atm_arp_addr_t;
typedef struct atm_arp_addr  *atm_arp_addr_p;

typedef struct atm_arp_entry  atm_arp_entry_t;
typedef struct atm_arp_entry  *atm_arp_entry_p;

typedef struct atm_arp_hdr  atm_arp_hdr_t;
typedef struct atm_arp_hdr  *atm_arp_hdr_p;

typedef struct rcv_q_buf  rcv_q_buf_t;
typedef struct rcv_q_buf  *rcv_q_buf_p; 

typedef struct atmip_vc atmarp_vc_t;
typedef struct atmip_vc *atmarp_vc_p;

#define ATM_ARP_ISLOCKED(l)	(lockmode == 0 || lock_holder(l))

struct inarp_pending {
    queue_chain_t  list;    
    atm_vc_p	vc_p;
    atmip_ifnet_p lis_p;
    u_short	flag;
#define ATM_ARP_INFORM_IPCVG	0x01
#define ATM_ARP_QUEUE_VC	0x02
#define ATM_ARP_ATMADDR		0x04
/* reasons */
#define ATM_ARP_NORMAL		0x03
#define ATM_ARP_VC_DEAD		0x04	/* VC is dead */
#define ATM_ARP_PERM_ENTRY	0x08	/* A VC for a permanent entry */
    u_short	time;
#define ATM_ARP_INARP_TIME_RETRY	10
    u_char	atm_addr[ATMADDR_LEN];
    u_char	e164_addr[E164_LEN];
};
udecl_simple_lock_info(extern, inarp_pending_q_lock_li)

/*  
 * This information is relevant if the end system is a client. 
 * NOTE: As a client we don't bind to any address as we never
 *       receive any calls on an SVC. All calls that we initiate
 *	 to a server use IP's bind point.
 */
struct arpclient_info {
    struct in_addr server_ipaddr;	   /* Server's IP address */
    u_char atm_server_addr[ATMADDR_LEN];   /* The configured address */
    int	connect_req_tm;	   	   	   /* connect request timer */
    int	connect_retry_tm;      	           /* assigned retry value */
#define ATM_ARP_CONNECT_RETRY_MIN	10 /* minimum value        */
    int  server_connect_tm;		   /* timer to re-register with server*/
};

/* 
 * NOTE on 'vcs' in 'struct atm_arp_data' below:
 *	These are list of VCs that IP has with the remote system. This
 *	list is maintained by the IP convergence layer.
 * NOTE on 'arpvcs' in 'struct atm_arp_data' below: 
 * 	If we are the server this has no meaning.
 *	On a client this contains the VC(s) to the server.  Only
 *	the server entry (or entries for multiple LIS) should have
 *	non-empty arpvcs queue.
 */

struct atm_arp_data {
    struct in_addr	ip_addr;
    u_char		atm_addr[ATMADDR_LEN];
    u_char		e164_addr[E164_LEN];
    queue_head_t	vcs;		/* Linked list of VCs used by IP */
    queue_head_t	arpvcs;		/* Linked list of VCs used by ARP */
    atmip_ifnet_p	lis_p;		/* LIS for this address */
    struct mbuf		*arp_hold;	/* mbuf being help pending ARP
				   	 * resolution. */
    int			active_vc_cnt;	/* # of live VCs for this arp entry */
    u_int		state;
#define ATM_ARP_STATE_CALLING	1	/* a call is being made */
#define ATM_ARP_CALL_FAILED	2	/* to server failed */
#define ATM_ARP_SERVER_DEAD	4	/* to server arptab deleted */

    u_int		arp_flags;	/* flags for this entry */
/* The arp_flags for every entry */
#define	ATM_ARP_COMPLETE	0x0001	/* An useable entry */
#define ATM_ARP_PERMANENT	0x0002	/* A permanent entry */
#define ATM_ARP_STALE		0x0004	/* Needs to be revalidated */
#define ATM_ARP_NO_RESPONSE	0x0008	/* No response from server */
#define ATM_ARP_UNKNOWN		0x0010	/* ARP server has no entry for this */
#define ATM_ARP_REQUEST_SENT	0x0020	/* Request sent to the server */
#define ATM_INARP_REQUEST_SENT	0x0040	/* InARP Request sent to the server */
#define ATM_ARP_SERVER_ENTRY	0x0080	/* Entry for the ARP server */
#define ATM_ARP_ENTRY_DELETE	0x0100	/* Entry is deleted */
#define ATM_ARP_IP_INCOMPLETE   0x0200  /* Entry for incomplete lis_p field */

    udecl_simple_lock_data(, atm_arp_data_lock) /* lock for entry data
						   except prev_p,next_p */
};
udecl_simple_lock_info(extern, atm_arp_data_li)

/* 
 * 'server_connect_tm': If on a client there has been no activity
 *  with the server in the past 20 minutes AND we don't have a VC open
 *  with the server, the client must open a new VC, so that the server
 *  can validate the entry by InARP message exchange.
 */

struct atm_arp_entry{
    atm_arp_data_t		data;		/* mapping info */
    u_short			index;		/* The index in the table */
    short			arp_reqsent_tm;	/* timer */
    short			arp_valid_tm;	/* timer */
    short			arp_req_tries;	/* # times a resolution was tried */
    unsigned int		fc_tstamp;	/*time stamp for failed call */
    int				fc_cnt;		/* count of failed calls */
    struct timeval 		tstamp;		/* time stamp */
    atm_arp_entry_p		prev_p; 
    atm_arp_entry_p		next_p;
};

/*
 * Timers defined above:
 * --------------------
 * arp_reqsent_tm: Timer which indicates that the time elapsed since the
 *		  arp request for an entry was sent.
 * arp_valid_tm	  Timer which indicates the time when the entry needs to
 *		  be revalidated. 20 minutes for a server entry and 15 minutes
 *		  for a client entry.
 */
#define ATM_ARP_AGING		1	/* 1 sec. aging timer */
#define ATM_ARP_MAX_REARP	5	/* timeout before rearping */
#define ATM_ARP_MAX_REQ		4	/* max request allowed */

struct atm_arp_bucket {
	atm_arp_entry_p bucket;
	udecl_simple_lock_data(, bucket_lock)	/* bucket link list lock */
};
udecl_simple_lock_info(extern, atm_arp_bucket_lock_li)

/* The ATM ARP table */
struct atm_arp_table {
u_short	atm_arp_retry;		/* ? Max time before sending next ARP req */
u_short server_time_valid;	/* seconds the entry can be valid */
u_short client_time_valid;	/* seconds the entry can be valid */
u_int	total;			/* Total number of entries in the table */
struct atm_arp_bucket atm_arp_table[ATM_ARP_TABLE_SZ]; /* The arp table */
udecl_simple_lock_data(, table_lock)	/* lock for retry, timers, total */
};
udecl_simple_lock_info(extern, atm_arp_table_lock_li)

/* 
 * Define default values for retry time, client and server
 * timeouts for entries in the ARP table.
 * All values are in seconds.
 */
#define ATM_ARP_RETRY			20	/* ? */
#define ATM_ARP_SERVER_TIME_VALID	1200
#define ATM_ARP_CLIENT_TIME_VALID	900


struct _evt_q_head {
	queue_head_t	evt_q;
	udecl_simple_lock_data(, evt_lock)
};

struct _timer_evt {
	queue_chain_t  q;
	int	evt_flag;
#define TIMER_CONONE	0x01
#define TIMER_INREQ	0x02
#define TIMER_REQ	0x04
#define TIMER_REVAL	0x08
#define TIMER_DEL	0x10
#define TIMER_INREQ_NOQ 0x20
	void		*evt_handle;
};

struct _delete_evt {
	queue_chain_t	q;
	int	evt_timer;
	atm_arp_entry_p	evt_ae;
};
udecl_simple_lock_info(extern, atm_arp_delevt_lock_li)
#define delete_q_head	delete_evt_q.evt_q
#define delete_q_lock	delete_evt_q.evt_lock



/*
 * The following structures are used to queue incoming packets.
 * Which are later processed by the ATM ARP module at a lower
 * priority.
 */
struct rcv_q_buf {
    queue_chain_t  list;
    atm_vc_p vc_p;
    struct mbuf *m;
    int length;
    struct mbuf *m_last;
    char pti;
    char gfc;
};
struct _rcv_q_head {
    queue_head_t 	rcv_q;
    udecl_simple_lock_data (,rcv_q_lock)
};
udecl_simple_lock_info(extern, atm_arp_rcv_q_lock_li)

#define rcv_q_head         &(atm_arp_rcv_q.rcv_q)
#define rcv_q_lock	   atm_arp_rcv_q.rcv_q_lock


/* Function prototypes called from other modules */

int atm_arp_resolve(const atmip_ifnet_p lis_p,
		    struct in_addr destip,
		    atm_arp_data_p *arp_data_p);
void atm_arp_inresolve(const atm_vc_p vc_p,
		       const atm_addr_p addr_p,
		       const atmip_ifnet_p lis_p);
void atm_arp_init();
void atm_arp_register();
void atm_arp_receive(atm_vc_p vc_p,
		     struct mbuf *m,
		     int length,
		     struct mbuf *trailer,
		     char pti,
		     char gfc);
atm_error_t atm_arp_exception(void *handle,
			      int exception,
			      void *arg);
int atm_arp_dequeue_inarp_pending(const atm_vc_p vc_p,
				  const atm_arp_data_p data,
				  const short reason);
int atm_arp_manage(void *handle,
		   int cmd,
		   void *arg,
		   int *retval,
		   struct ucred *cred);

/*
 * end of atm_arp.h 
 */

#endif
