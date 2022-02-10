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
 * @(#)$RCSfile: ip_converge.h,v $ $Revision: 1.1.24.2 $ (DEC) $Date: 1998/09/25 19:54:24 $
 */

#ifndef _ATM_IP_CONVERGE_H_
#define _ATM_IP_CONVERGE_H_

/* general includes */
#include "machine/endian.h"
#include "net/net_globals.h"
#include "sys/socket.h"
#include "sys/socketvar.h"
#include "net/netisr.h"
#include "net/route.h"
#include "netinet/in.h"
#include "netinet/ip.h"
#include "netinet/in_pcb.h"

#include "sys/ioctl.h"
#include "sys/param.h"
#include "sys/time.h"
#include "sys/errno.h"


#define ATM_HIDE_STEEL_DEPENDENCIES 1	/* Use modifications for V4.x stream */

/* ATM specific includes */
#include <atm/sys/atm_osf.h>
#include <atm/sys/atm.h>
#include <atm/sys/atm_adi.h>
#include <atm/sys/atm_cmi.h>

/* Some Constants */
#define ATMIP_LLC_HEADER_LENGTH		8
#define ATMIP_AAL5_TRAILER_LENGTH	8

typedef struct atmip_ppa atmip_ppa_t;
typedef struct atmip_ppa *atmip_ppa_p;

typedef struct atmip_driver atmip_driver_t;
typedef struct atmip_driver *atmip_driver_p;

typedef struct atmip_ifnet atmip_ifnet_t;
typedef struct atmip_ifnet *atmip_ifnet_p;

typedef struct atmip_vc atmip_vc_t;
typedef struct atmip_vc *atmip_vc_p;

typedef struct atmip_vcque atmip_vcque_t;
typedef struct atmip_vcque *atmip_vcque_p;

typedef struct atmip_map_entry atmip_map_entry_t;
typedef struct atmip_map_entry *atmip_map_entry_p;

typedef struct atmip_map_sect atmip_map_sect_t;
typedef struct atmip_map_sect *atmip_map_sect_p;

typedef struct atmip_esi atmip_esi_t;
typedef struct atmip_esi *atmip_esi_p;

#include "netinet/atm/atm_arp.h"

/* networking includes */
#include "sys/mbuf.h"
#include "sys/socket.h"

#include "net/if.h"
#include "net/if_llc.h"
#include "net/netisr.h"
#include "net/net_malloc.h"
#include "net/route.h"
#include "net/pfilt.h"

/* Domain stuff will go away with dynamic protocols */
#include "netinet/in.h"
#include "netinet/in_var.h"
#include "netinet/if_ether.h"
#include "netinet/if_fddi.h"
#include "netinet/if_trn.h"
#include "netns/ns.h"
#include "netns/ns_if.h"


/* structure for keeping track of interfaces.  Since LIS' are defined per
 * interface, interfaces must be identified and tracked.  This is done
 * by using the driver handle in the PPA structure when a new PPA
 * notification arrives.
 */


atmip_map_entry_p atmip_get_map_entry(int unit, int flag);

#define MAX_DRV_NAME 16
struct atmip_driver {
	queue_chain_t           q;
	queue_head_t		ppa_q;
	atm_lock_decl(drv_ppaq_lock)		/* protects num_ppas,	*/ 
						/* ppa_q, and drv_flag 	*/	
	int			num_ppas;	/* # ppas active for driver */
	int			drv_flag;	
#define ATMIP_DRV_UP		0x1
#define ATMIP_DRV_ESI_PENDING	0x2
	queue_head_t		esi_q;	
	atm_lock_decl(drv_esiq_lock)		/* protects esiq, next esi, */
						/* and num_esi_pend */
	int 			next_esi;	/* low order bytes of next esi */
	int			num_esi_pend;	/* Num esi's pending  */
	ulong			drv_base_esi;	/* starting esi	*/
	atm_drv_handle_t	drv_handle;	/* save a ref	*/
	char 			drv_nam[MAX_DRV_NAME];	/* drv name (const) */
	
	atmip_ifnet_p		drv_ifnet_q;
	atm_lock_decl(drv_ifq_lock)
};


/* structure used to keep track of ATM PPAs */

struct atmip_ppa {
	queue_chain_t		q;
	atm_ppa_p		ppa;
	atmip_driver_p		driver;
	atmip_esi_p		esi;
	uint			zomb_timer;
	atm_lock_decl(ppa_lock) 	/* protects next selector, zomb_timer */
					/* and ppa fields */
};

/* ether_driver extra after ifnet */
struct ether_driver_ext {
        /* struct arpcom minus ifnet */
        /* struct  ifnet ac_if; */
        u_char  ac_hwaddr[14];          /* hardware address (sizeof sa_data) */
        u_short ac_arphrd;              /* arp hardware type (net/if_arp.h) */
        u_char  *ac_bcastaddr;          /* pointer to link broadcast or 0 */
        u_int   ac_flag;                /* ip configured or not */
        struct dli_ifnet *ac_dlif;      /* pointer to the DLI data */
        /* struct ether_driver minus arpcom */
        struct  estat ess_ctrblk;       /* Counter block */
        int     ess_ztime;              /* Time counters last zeroed */
        short   ess_enetunit;           /* unit no. for packet filter */
        int     ess_missed;             /* count of missed rx packets */
        long extrabuf[4];       /* extra in case ifnet grows and we miss the upd
ate */
};

/* This structure is used to define each interface (LIS) into IP 	*/
/* This structure in on two linked lists: esi list of ifnets 	*/
/* associated with that esi and the driver list of ifnets	*/

struct atmip_ifnet {
	struct ifnet		ifnet;
	struct ether_driver_ext is_ed;
	atmip_ifnet_p		esi_ifp_next; 	/* next ptr in esi list */
	atmip_ifnet_p		drv_ifp_next; 	/* next ptr in drv list */
	atmip_ppa_p		ippa;		/* signaling ppa */
	atmip_driver_p		driver;
	atm_bind_handle_t	svc_bind;
	atm_bind_handle_t	pvc_bind;
	atmip_vc_p		draining;
        u_int  			flags;	    	/* arp server/client flags */
#define ATM_ARP_SERVER_CONFIG	0x01		/* Server addr. configured */
#define ATM_ARP_SERVER		0x02		/* This is a server */
#define ATM_ARP_SERVER_DOWN	0x04		/* server is a dead puppy */
	int			selector; 	/* selector for SVCs  */
	struct in_addr 		ip_addr;  	/* IP addr on the LIS */
	uchar 			lis_atm_addr[ATMADDR_LEN];
						/* addr of the LIS */
        struct arpclient_info 	arpc;		/* Info. on the client side */
	atm_lock_decl(atmip_ifnet_lock)
};

struct atmip_vc {
	queue_chain_t		q;
	int			state;
#define ATM_IP_VC_ACTIVE	0x01	/* VC is active */
#define ATM_IP_VC_CALL_FAILED	0x02	/* Failed to establish VC */
#define ATM_IP_VC_REQUESTED	0x04
#define ATM_IP_VC_TYPE_PVC	0x08
#define ATM_IP_VC_SERVER_DEAD	0x10
#define ATM_IP_VC_DELETE	0x40	/* delete when done */
#define ATM_IP_VC_ARP_ACTIVE	0x100	/* VC is active for ARP (not IP )   */
#define ATM_IP_VC_ROUTE_FMTU	0x200	/* override ipmtu with route mtu    */
#define ATM_IP_VC_ROUTE_BMTU	0x400	/* override ipmtu with route mtu    */
#define ATM_IP_VC_QUEUE		0x800	/* netisr is queued for route updt  */
#define ATM_IP_VC_CONV_OWNER	0x1000  /* ARP VC transitioning to IP VC    */ 
	atm_vc_p		vc;
	atmip_ifnet_p		ifp;
	atm_arp_data_p		arp;
	uint			zomb_timer;
	int			owner;
#define	ATM_IP_CVG		1
#define	ATM_ARP_CVG		2
	int			startvc_occurred; /* ATM_CME_START_VC occured
						   * while draining queue */
	int			drain_mutex;	/* Allow only one thread in
						 * atmip_drain_vc. */
        struct  ifqueue		atm_snd;	/* place to put packets
						 * when flow controlled */
	struct sockaddr_in  	inetaddr;	/* inet address only valid if
						 * route was added	*/
	atm_lock_decl(atmip_vc_lock)
};

atmip_vc_p atmip_alloc_vc(int owner,atmip_ifnet_p lisp);

/* struct for queueing to atmip_route_updt netisr */
struct atmip_vcque {
	queue_chain_t		q;
	atmip_vc_p		vc;
};
/* struct for mapping LIS Ids with a esi/ifnet/driver */
struct atmip_map_entry {
	atmip_ifnet_p 	map_ifnet;
	atmip_driver_p	map_drv;
	atmip_esi_p	esi;
	int		flag;
#define	ATMIP_MAP_PPA_WAIT    0x01	/* waiting for a PPA to come online */
#define ATMIP_MAP_NOT_DYNAM   0x02	/* LIS wasn't dynamicly mapped to   */
                                        /* ATM address */
#define ATMIP_MAP_BIND_DOWN   0x04      /* BIND point has been deleted */
};
#define NUM_MAP_ENT 16
struct atmip_map_sect {
	int	num_ent;	/* number of active map entries */
	int	start_ent;	/* start entry for this section */
	atmip_map_entry_t	entry[NUM_MAP_ENT];
	atmip_map_sect_p	next; /* pointer to next map section */
	atm_lock_decl(atmip_map_sec_lock)
};
struct atmip_esi {
	queue_chain_t		q;
	atm_esi_handle_t	esi_handle;
	atmip_driver_p		drv;
	atmip_ppa_p		ippa;
	atmip_ifnet_p		esi_ifnet_q;
	atm_lock_decl(esi_ifq_lock)
	ulong			esi;
	int 			num_ifnets;   /* # of LISs using this esi */
	int			flag;
#define ATMIP_ESI_NON_DYNAM	0x2
#define ATMIP_ESI_DOWN		0x4
};
	

/* VC encapsulation methods */
#define IP_VCE_NULL		0		/* NULL encapsulation */
#define IP_VCE_LLC		1		/* LLC encapsulation */
/* zombie deletion timeout value */
#define ATMIP_ZOMB_TO	30			/* 30 seconds */
#define MAX_SELECTOR 255
#define	MAX_IFNETS_PER_ESI (MAX_SELECTOR+1) /* XXX - this ignores that there   */
					    /* could be multiple PPAs per ESI  */
#define ATMIP_ESI_HIGH_BIT 0x80		    /* sets high order bit of ESI addr */
#define ATMIP_ESI_VAR_SHIFT 7		    /* shifts to the variable portion  */
					    /* of the private address	    */ 
#define	UNI_PREFIX_LENGTH 13		    /* prefix length for UNI	    */

/*
 * end of ip_converge.h 
 */

#endif
