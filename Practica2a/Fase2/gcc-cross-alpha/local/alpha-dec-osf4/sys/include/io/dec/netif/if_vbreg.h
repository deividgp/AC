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
 * @(#)$RCSfile: if_vbreg.h,v $ $Revision: 1.1.14.3 $ (DEC) $Date: 1999/02/04 18:47:38 $
 */

/* The first part of if_vbreg.h contains the backplane constants and data 
 * structures that are common between osf and elx backplane drivers.
 * Following that, are osf specific constants and typedefs.
 */

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/malloc.h>
#include <sys/buf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
#include <sys/lwc.h>
#include <vm/vm_kern.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/if_ether.h>
#include <net/ether_driver.h>
#include <hal/cpuconf.h>
#include <io/common/devdriver.h>
#include <io/dec/uba/ubavar.h>
#include <io/dec/vme/vbareg.h>
#include <io/dec/vme/vba_generic.h>
#include <io/dec/mbox/mbox.h>
#include <machine/rpb.h>
#include <machine/endian.h>
#include <kern/thread.h>


/*##################################################################
 *	Start of OSF/VxWorks common data structures and constants
 *	These must NOT change, or compatibility between o/s's will 
 *	be compromised.  The corresponding file in VxWorks is if_vb.h.
 *##################################################################*/

/* Driver i/o interface type */
#define VB_POLLED        0   /* Polling mode       */
#define VB_INTERRUPT     1   /* Mailbox interrupts */
#define VB_IRQ_INTERRUPT 2   /* IRQ interrupts (not supported on OSF) */

#define VB_MAXNODES_LIMIT 32     /* Architecturally defined max number of
			 	  *  nodes in a vb network, including
				  *  bridged nodes. */
#define U_INT32 unsigned int 	 /* 32 bit unsigned integer type */
#define S_INT32 int		 /* 32 bit signed integer type */
#define U_CHAR  unsigned char    /* 8 bit unsigned char */
#define U_SHORT16 unsigned short /* 16 bit unsigned type */
#define SEQNO_MAX 256		 /* Wrap value for freepkts_produced/consumed 
                                  * and recvpkts_produced/consumed increments*/
#define NMULTI  64		 /* Size of multicast address table */

/*
 * VME Backplane client node liveness state (current_state)
 */
#define VB_DOWN			0x0000	/* state down, initial state 	*/
#define VB_WAITING_FOR_CONFIRMATION 0x0001 /* in the process of	checking
					 * in, waiting to get confirmation
					 * from the box manager regarding
					 * configuration data */
#define VB_CONFIRMED		0x0002	/* Checked in and confirmed, but 
					 * not up (not accepting packets) */
#define VB_UP			0x0004	/* Up and participating	*/
#define VB_SHUTDOWN_PENDING	0x0008	/* Client controlled shutdown */
#define VB_CHECKIN_ERROR        0x0010  /* an error occurred during registration */
#define VB_LOST_LIVENESS	0x0020	/* Lost liveness with a remote node */
#define VB_UP_NO_WATCH          0x0040  /* Up, but don't check liveness of
					 *  the node.  Used for booting over
					 *  the backplane.
					 */
/* Time values for polling functions.
 * All values are in milliseconds.
 */
#define BM_MONITOR_CHECKIN_REQUESTS   300 /* bm monitors client checkin 
					   * requests */

#define CLIENT_UPDATE_HEARTBEAT       100 /* client updates it's heartbeat for
					   * other clients to look at. */

#define CLIENT_CHECK_LIVENESS  (CLIENT_UPDATE_HEARTBEAT * 100) 
					/* client checks for other clients'
					 *  liveness.  10 seconds.  This is 
					 *  the time inbetween checking for
					 *  liveness of other nodes in the
				   	 *  vb network.  If this is done
					 *  too frequently, we may lose 
					 *  liveness with other nodes too
					 *  easily (and they must reboot in
					 *  order to enter the network again).
					 *  If too slow, we may miss a reboot
					 *  altogether.  10 seconds seems
					 *  like a good time.
					 */

/* The timeout for checking liveness of remote nodes is configurable
 * in if_vb_data.c with a default of CLIENT_CHECK_LIVENESS.  
 * A value of 0 means that no liveness checking is to be done, which 
 * means that you expect that once the network nodes are up they will 
 * stay up.  If not, you will surely nxm.   
 */
#define VB_LIVENESS_TIMEOUT_DEFAULT CLIENT_CHECK_LIVENESS
				 	/* Default client liveness checking
					 * timeout.
					 */

#define CLIENT_CHECK_STATE_CHANGE    5000 /* 5 seconds */
					/* client checks for other clients'
				  	 *  state changes in l2 area, for
					 *  clients coming online and clients
					 *  going offline.  Also used 
					 *  to see if the VB_UP client's
					 *  census record revision number
					 *  has changed indicating that the 
				         *  client's multicast (or other) 
					 *  information has changed. 
					 */

/* State of multicast information in the l2 area */
#define MULTI_STATE_VALID 0	/* Multicast info is valid */
#define MULTI_STATE_INVALID 1	/* Update of multicast info is in progress, 
				 * table is invalid */

struct vb_multi
    {
    U_CHAR  vb_multi_char[6];
    };

/* Multicast information
 * Used to filter transmit msgs to participating backplane
 * network nodes.
 */
typedef struct vb_multi_info {
        U_INT32 multi_state;            /* state used to update this table */
	U_INT32 nmulti;			/* Current # of multicast slots */
	U_INT32 multi_flags;		/* Multicast flags IFF_PROMISC,
					 * IFF_ALLMULTI. 
					 */
	struct	vb_multi multi[NMULTI];	/* Multicast address list.  Includes
					 * the broadcast address, if turned
					 * on.
					 */
        /*
         * Note that we don't pad after 'multi' as
         * (64 * 6) mod 8 == 0
         */
 	U_CHAR	muse[NMULTI];		/* Multicast address usage count */
        U_CHAR  pad[3];                 /* pad muse to 4 bytes           */
}vb_multi_info_t;

struct vb_lan_reg_struct {
  union
    {
      U_CHAR  vb_addr[6];
                       /* vb LAN address -- for medulla, this
                        * is the 'shadow' enet address, as described in DECnet
                        * Digital Network Architecture LAN Node Product
                        * Functional Specification Version V2.0.0. This
                        * address is sent to the upper network layers as my
                        * hw address.
                        */
      U_INT32 vb_registration_addr[2];
    } vb_lan_reg;
};
#define vbLanAddr vb_lan_reg.vb_addr
#define vbLanReg  vb_lan_reg.vb_registration_addr

/* Flags for VME address modifiers
 * Set if area is mapped to a24 space, else mapped to a32 
 */
#define AM_A24 0x1
#define AM_A16 0x8

/* Set if area is supervisory, else user */
#define AM_SUPER 0x2

/* Set if area is data, else program */
#define AM_DATA 0x4

/******* The following are default values for configurable data.    *******
 ******* Driver are to use these values UNLESS OTHERWISE CONFIGURED *******
 ******* in if_vb_data.c: 					    *******/

/******Define the DEFAULT well known box mgr l2 address.
 ****** Note that the OSF default A24 window is the 4th 4 megabyte chunk,
 ****** so we don't bump into the default area.  This default was chosen so
 ****** as to come directly after the VxWorks SM driver default start address
 ****** of 0xA00000 and size of 0x400000.  Thus, if both VxWorks and the
 ****** VB driver are on the same system, then the defaults will cooporate nicely.
 ****** Any new user VME device drivers will have to make sure that addresses
 ****** don't overlap.
 */
/* Changed the VB_WELL_KNOWN_ADDRESS to 0xBC0000.
 * This allows maximum usage of the VME inbound window for use by other device
 * drivers. Previously the inbound window was fragmented with the old
 * default of 0xA40000. 
 */
#define VB_WELL_KNOWN_ADDRESS 0xBC0000

/* Define DEFAULT type of box mgr l2 space */
#define VB_WELL_KNOWN_ADDRESS_TYPE (AM_A24 | AM_SUPER | AM_DATA)

/* Define the default offset from the client system base address at which
 * to map our l3 queues inbound.
 */
#define VB_L3OFFSET_DEFAULT 0x00000  /* Default is 0 bytes from base.. ie AT
				      *  the base! 
				      */

/* Default max number of nodes in the network */
#define VB_MAXNODES_DEFAULT 10

/* Default message MTU size */
#define VB_MAXMTU_DEFAULT 1500

/* Default VME window size to be used exclusively by
 * the VB Backplane Driver on a given node.
 */
#define VB_DMA_WINDOW_SIZE 0x40000

/* Default Offset from A16 base to be used for Mailbox interrupts. This
 * MUST be the same as the VxWorks default. This is for the VIPVIC.
 */
#define VB_A16_OFFSET_DEFAULT 0x23

/* Default Offset from A16/A24 or A32 base to be used for Mailbox interrupts. This
 * MUST be the same as the VxWorks default. This is for UNIVERSE TUNDRA
 */
#define VB_MAILBOX_UNIV_OFFSET_DEFAULT 0x34c



/* Census list - used to maintain census of nodes that are or were active in
 * the vb network.  Table of structures allocated on a first-come-first-
 * served basis, one per node in the net.  The index into this table is
 * the index into the l2 and l3 communication areas.  Each node in
 * the network maintains this cache of bindings which is copied 
 * occasionally by the clients to get the updated census.
 * The box manager keeps the official census table in l2 memory
 * which is mapped onto the VME. 
 */
typedef struct censusinfo{
	U_INT32 vb_client_revision;
				/* Revision of backplane software that this
			     	 *  client is running.  Revision starts at 0. 
				 *  Currently not used. */
	U_INT32 client_heartbeat; 
				/* client liveness indication, updated by the 
				 *  client itself */
	U_INT32 censusRevision; /* Every time this structure is updated
                                 * by a client, this count is incremented
				 * by the client. */
	U_INT32 current_state;  /* current state of this node:
				 * Set by box manager only. */
        U_INT32 censusError;    /* set to an error code by the box manager
                                 * if there was an error during checkin, ie:
                                 * VB_CHECKIN_ERROR is true in current_state
				 * UNUSED for first release, but keep for
				 * possible future enhancement.
                                 */
        struct  vb_lan_reg_struct vb_lanaddr; /* The lan address */
	U_INT32 vmeaddr;	/* Base vme addr for node's l3 q */
	U_INT32 vmeaddr_am;	/* Address modifier for vme addr */
  	U_INT32 vmesize; 	/* Size of this node's level 3 memory, 
			* which must be mapped by any node that wishes to 
			* communicate with this node.  
			*/
	U_INT32 group_mask; 	/* Bit mask of groups the node is in.
			* Fixed at group 0 -- this will eventually correspond 
			* to the unit number of the driver.
			*/
	U_INT32 maxmtu;	/* Max transmission data unit.  Initially fixed at
			 *   1500 bytes -- ethernet mtu. 
			 */
        U_INT32 polled; /* TRUE if this node has a polled receive interface.
                         * FALSE if this node has an interrupt receive
                         * interface.  Sender needs to know whether it needs
                         * to ring this node's doorbell or not and if polled,
                         * then there's no doorbell.
                         */
        U_CHAR not_little_endian;
                        /* TRUE for big endian, FALSE for little endian.
                         * First release only supports little endian.
                         */
        U_CHAR mailbox_addr_type;  /* mailbox address modifier */
        U_SHORT16 mailbox_map_size; /* mailbox window size */
        U_INT32 mailboxA16Addr; /* This indicates which A16 address we are 
                                 * to use to send a mailbox interrupt to, 
                                 * otherwise 0.  
				 */
        U_SHORT16 intrPri; /* use this interrupt priority to send a VME IRQ */
        U_SHORT16 intrVec; /* and send at this vector, else {intrPri,intrVec}
                            *  == 0 */
	struct vb_multi_info vbmi; /* Multicast information */
}censusinfo_t;


typedef struct l2comm_hdr{
	U_INT32 vb_ident;	/* Backplane memory identification number,
				 *  used to make sure that the memory we
				 *  map to and THINK is the box mgr memory
				 *  really is used by the backplane and not
				 *  mapped by some other device.  The ident
				 *  number is fixed at 0xfeedface.
				 */
	U_INT32 vb_revision;	/* Backplane software revision.  
				 *  Note this is also stored in the
				 *  individual client's census record */
        U_INT32 vbMaxNodes; 	/* the maximum number of nodes that is supported */
        U_INT32 reserved;  	/* pad structure out to quadword */
        U_INT32 reserved2[8];   /* reserved for simple communication */
        U_INT32 reserved3[8];   /* reserved for simple communication */
}l2comm_hdr_t;

typedef struct l3header{
        U_INT32 next;    /* Offset from the start of l3 to the
                          * next l3header type */
        U_INT32 datapkt; /* Offset from the start of l3 to the
                          * datapkt associated with this l3header */
}l3header_t;

typedef struct l3_datapkthdr{
        U_INT32 vb_buf_len;  /* length of data in the following data buffer.
                              *  The data is 46-1500 bytes, PLUS 14 bytes
                              *  for the ethernet header.
                              */
}l3_datapkthdr_t;

typedef struct l3queue_struct{
        U_INT32 recvhead;        /* Contains the offset from l3 table header
                                  *  to the head l3header struct in the
                                  *  recv queue */
        U_INT32 recvtail;        /* Contains the offset from l3 table header
                                  *  to the tail l3header struct in the recv
                                  *  queue */
        U_INT32 freehead;        /* Contains the offset from l3 table header
                                  *  to the head l3header struct in the free
                                  *  queue */
        U_INT32 freetail;        /* Contains the offset from l3 table header
                                  *  to the tail l3header struct in the
                                  *  freequeue */
        U_INT32 freepkts_produced;  /* Each time a packet is enqueued on the
                                 * free queue, this count is incremented.*/
        U_INT32 freepkts_consumed;  /* Each time a msg is dequeued from
                                 * the free queue, this count is
                                 * incremented.  If freepkts_produced
                                 * == freepkts_consumed then the queue is
                                 * empty.  Used for determining when to
                                 * generate transmit interrupts and also
                                 * for packet lifetime tracking */
        U_INT32 recvpkts_produced;  /* Each time a msg is enqueued on
                                 * the receive queue, this count
                                 * is incremented.*/
        U_INT32 recvpkts_consumed;  /* Each time a msg is dequeued from
                                 * the receive queue, this count is
                                 * incremented.  If recvpkts_produced
                                 * == recvpkts_consumed then the receive
                                 * queue is empty (there are no msgs on it)
                                 * Used for determining whether we need to
                                 * start a receive packet lifetime timer
                                 * on the packet at the head of the receive
                                 * queue.  If there are no msg, then don't
                                 * start a timer. */
	U_INT32 transintr_pending; /* set if out of buffers */
        U_INT32 reserved;       /* reserved for future use, specifically
				 * for reporting status of individual queues.
				 */
}l3queue_struct_t;

typedef struct l3comm_hdr{
        U_INT32 rcvintr_pending; /* Set to 1 by senders to let the
                         * receiver know that there is data on at least one
                         * of the queues.  Not reset to 1 if it is already =1.
                         * When set to 1, an interrupt is triggered on the
                         * receiver node by the sender node.
                         */
        U_INT32 queue_status;  /* misc l3 area-wide status */
}l3comm_hdr_t;


/*#########################################################
 *   Start of OSF specific constants and data structures 
 *########################################################*/

/* The backplane driver BY DEFAULT is not configured to run.
 * The user must EXPLICITLY configure the driver to
 * run by setting the vb_startup_state field in vb_cfg configurable
 * structure (in if_vb_data.c) to VB_STARTUP_ON.  The default is 
 * VB_STARTUP_OFF.  If VB_STARTUP_OFF when the driver start function 
 * is activated, the driver will exit.  Otherwise, it is assumed that 
 * the rest of the configurable values are valid, and the driver will probe
 * the box mgr well known address indefinitely until it is found.
 */
#define VB_STARTUP_OFF 0
#define VB_STARTUP_ON  1

/* Structure definition for user configurable data (actual data
 * values are initialized in if_vb_data.c):
 */
typedef struct vb_cfg
    {
/* Configurable on a per-node basis (nodes can have different values): */
    U_INT32 vb_startup_state;          /* Startup state of this driver.
                                        * Default is VB_STARTUP_OFF.
                                        */
    U_INT32 vb_client_addr_type;       /* Address modifier for this clients
                                        * vme address (vme address is 
                                        * obtained dynamically).
                                        * Default is (AM_A24|AM_SUPER|AM_DATA)
                                        */
    U_INT32 vb_client_vme_window_size; /* Size of this clients vme window
                                        * Default is VB_DMA_WINDOW_SIZE.
                                        */
    U_INT32 vb_interface;              /* Interrupt or polled driver interface.
                                        * Default is VB_INTERRUPT.
                                        */
    U_INT32 vb_liveness_timeout;       /* Milliseconds in between checking
					*  liveness of remote nodes.  
					*  Default is VB_LIVENESS_TIMEOUT.
					*  Value of 0 means no liveness checking.
					*/
   U_INT32 vb_mailbox_addr_type;        /* Address modifier type for the
                                         * mailbox address */ 

   U_INT32 vb_mailbox_offset;	       /* Offset from A16 base to cause a 
					*  mailbox interrupt when written to.
					*  Must be one of 0x21, 0x23, 0x25, 
					*  or 0x27
					*/
    U_INT32 vb_maxnodes;               /* Max nodes in the network.  This is
				        * used by the box manager node to
				        * set the limit on the number of nodes
				        * that can participate in the VB
				        * network.  All clients read this
				        * value from the box mgr and adjust
				        * their array sizes as necessary.
                                        * Default is VB_MAXNODES_DEFAULT.
                                        */
    U_INT32 vb_l3offset;	       /* Offset from the system base
                                	* address to map our l3 queues 
					* inbound to.  The particular window 
					* depends on the client address 
					* modifier configured, A24 or A32.
					*/
    U_CHAR  vb_ether_802addr[6];     /* The ethernet address of the system */

/* Configurable on a per-network basis (all nodes must match): */
    U_INT32 vb_bm_wka;               /* Well known vme address of box mgr
                                      * data. Default is VB_WELL_KNOWN_ADDRESS.
                                      */
    U_INT32 vb_bm_addr_type;         /* Address modifier of box mgr data WKA.
                                      * Default is VB_WELL_KNOWN_ADDRESS_TYPE.
                                      */
    U_INT32 vb_maxmtu;               /* Max mtu size.
                                      * Default is VB_MAXMTU_DEFAULT.
                                      */
    }vb_cfg_t;


/************ Constants and defines ******************/
#define MINDATA 60              /* Minimum transmit buffer size: 46 min
                                 * ethernet data size plus 14 hdr = 60
                                 */

/* VME width values for reading/writing */
#define WRITE_BYTE      1       /* one byte */
#define WRITE_WORD      2       /* two bytes... */
#define WRITE_INTEGER   4
#define WRITE_QUAD      8

#define READ_BYTE       WRITE_BYTE
#define READ_WORD       WRITE_WORD
#define READ_INTEGER    WRITE_INTEGER
#define READ_QUAD       WRITE_QUAD

/* Values for the vb map structure's valid flag */
#define VB_INVALID              0   /* Need to map and probe */
#define VB_MAPPED_NOT_PROBED    1   /* Only need to probe */
#define VB_VALID                2   /* mapped and probed successfully,

/* Transmit status values */
#define VB_MSGSENT              0x0000  /* Msg was successfully transmitted*/
#define VB_NOFREE               0x0001  /* There was no free buffer on the
                                         * remote node that the current
                                         * mbuf was destined for. */
#define VB_NOTREADY             0x0002  /* The remote node that the current
                                         * mbuf was destined for is in a
                                         * not ready state.  Could be down,
                                         * or just not in the census.
                                         */
#define VB_UNK_DSTADDR          0x0004  /* The remote node's index is not
                                         * known (it's vb hw address is
                                         * not in our census) */
#define VB_DMA_ERROR            0x0008  /* DMA error */
#define VB_NOMSGSENT            0x0010  /* Msg was successfully transmitted*/

/* Read/write memory flags */
#define VB_LOCAL        0       /* reading/writing to local l3 memory */
#define VB_REMOTE       1       /* reading/writing to remote l3 memory */

/* Multicast flags */
#define VB_UNICAST   	0
#define VB_MULTICAST    1

/*
 * VME Backplane level 3 queue status bits
 * (set/cleared in the level 3 table header entry 'queue_status')
 */
#define VB_MISS         0x0001  /* Missed packet                */
#define VB_ERR          0x1000  /* Error summary                */

/* Delay 1000 milliseconds (1 second) inbetween each probe of the bm l2 wka */
#define VB_PROBE_DELAY 1000

/* This is the frequency that we call vbiopoll to poll for io activity,
 * IF the driver is in polling mode.
 */
#define VB_POLL_FREQUENCY  100          /* 100 milliseconds */

/* 2 second timeout to check for packets that have been
 * on the receive l3 queues too long.
 */
#define VB_RECV_PKTLIFE    2000   /* 2 second timeout (2000 milliseconds */

/*
 * For the OSF driver, VB_TRANSMIT_PKTLIFE is used to poll for old packets
 * on the if_snd queue, which have been on the send queue too long due to
 * transmission being blocked because there are no free buffers on the head
 * packet's destination node.
 * It is used to run the "watchdog" routine on a periodic basis. The watchdog
 * routine is normally used to detect timeouts on transmission,
 * Vxworks doesn't have a send queue, so it doesn't do transmission
 * packet lifetime checking.
 * NOTE: VB_TRANSMIT_PKTLIFE must be in seconds! not milliseconds..
 * because it is used for the watchdog timer (if_timer).
 */
#define VB_TRANSMIT_PKTLIFE (4)      /* 4 second timeout*/


/******** Macros for changing address to offset and vice versa ***********/
#define VB_ADDR_TO_OFF(saddr,eaddr) ((char *)(eaddr) - (char *)(saddr))
#define VB_OFF_TO_ADDR(saddr,off)   ((char *)(saddr) + (off))


/******* Structure typedefs ********************/
/*
 * 6-byte Ethernet address type
 */
typedef struct ether_addr{
        U_CHAR ether_hwaddr[6];
}ether_addr_t;
#define EADDR_SIZE sizeof(struct ether_addr)

#define MULTISIZE sizeof(struct vb_multi)  /* vb_multi is defined in if_vb_l2. */


/* OSF driver-specific capabilities record... contains configurable vb 
 * network capabilities for this node, to be stored locally on this node.
 * These values do not change after they are read.
 */
typedef struct vb_capabilities{
  U_INT32     vmeaddr;     /* Base vme addr for node's DMA window for l3 */
  U_INT32     vmeaddr_am;  /* Address modifier for vme addr */
  U_INT32     vmesize;     /* Size of vme window for l3 queues */
  U_INT32     group_mask;  /* Bit mask of groups node's in.  Fixed at 0
                            *  for first release */
  U_INT32     maxmtu;      /* Max transmission data unit supported..
                            * fixed at 1500 bytes. */ 
  U_INT32     polled;      /* TRUE if this node is configured to be polled */
  U_CHAR      not_little_endian;
                           /* TRUE for big endian, FALSE for little endian.
			    * First release only supports little endian.
                            */
  U_CHAR   mailbox_addr_type;  /* mailbox address modifier  */
  U_SHORT16 mailbox_map_size;  /* mailbox window size */
  U_INT32 mailboxA16Addr;  /* This is the A16 address we are to use
                            * to send a mailbox interrupt to. */
  U_INT32 a16_offset;	   /* Offset from mailboxA16Addr to write to in order
			    * to cause a mailbox interrupt to this node. 
			    * Reflects the module switch to be used for
			    * interrupting. */
  /* The following are unsupported for first release on osf: */
  U_SHORT16 intrPri;       /* use this interrupt priority to send a VME IRQ */
  U_SHORT16 intrVec;       /* and send at this vector, else {intrPri,intrVec}
                            *  == 0 */

}vb_capabilities_t;


struct vbmap_struct;

typedef struct vb_fct_struct {
  /* pointer write operations */
  void (*fct_vbWriteByte)( struct vbmap_struct *v , char   *adr , char dat   );
  void (*fct_vbWriteWord)( struct vbmap_struct *v , short  *adr , short dat  );
  void (*fct_vbWriteInt) ( struct vbmap_struct *v , int    *adr , int dat    );
  void (*fct_vbWriteQuad)( struct vbmap_struct *v , long   *adr , long dat   );
  void (*fct_vbBlockWriteByte)( struct vbmap_struct *v , char   *src , char *dst , int cnt   );

  /* offset write operations */
  void (*fct_vbWriteByteO)( struct vbmap_struct *v , U_INT32 off , char dat   );
  void (*fct_vbWriteWordO)( struct vbmap_struct *v , U_INT32 off , short dat  );
  void (*fct_vbWriteIntO) ( struct vbmap_struct *v , U_INT32 off , int dat    );
  void (*fct_vbWriteQuadO)( struct vbmap_struct *v , U_INT32 off , long dat   );
  void (*fct_vbBlockWriteByteO)( struct vbmap_struct *v , char   *src , U_INT32 off , int cnt   );

  /* bzero operation */
  void (*fct_vbBlockZeroByteO)( struct vbmap_struct *v , U_INT32 off , int cnt   );

  /* pointer read operations */
  char   (*fct_vbReadByte) ( struct vbmap_struct *v , char   *adr );
  short  (*fct_vbReadWord) ( struct vbmap_struct *v , short  *adr );
  int    (*fct_vbReadInt)  ( struct vbmap_struct *v , int    *adr );
  long   (*fct_vbReadQuad) ( struct vbmap_struct *v , long   *adr );
  void (*fct_vbBlockReadByte)( struct vbmap_struct *v , char   *src , char *dst , int cnt   );

  /* offset read operations */
  char   (*fct_vbReadByteO) ( struct vbmap_struct *v , U_INT32 off );
  short  (*fct_vbReadWordO) ( struct vbmap_struct *v , U_INT32 off );
  int    (*fct_vbReadIntO)  ( struct vbmap_struct *v , U_INT32 off );
  long   (*fct_vbReadQuadO) ( struct vbmap_struct *v , U_INT32 off );
  void (*fct_vbBlockReadByteO)( struct vbmap_struct *v , U_INT32 off , char *dst , int cnt   );

} vb_fct_struct;


/*
 * vbmap_struct contains all the information need to map locally allocated
 * data out onto the vme or to map a vme address to a local address.
 * This is driver specific, ie each driver has to map all the vme addresses,
 * at local virtual address, so don't put the vbmap_struct in the
 * census report.  Copy the census table fields vmeaddr, vmeaddr_am,
 * and vmesize to dst_address, address_space, and byte_count
 * respectively.
 */
typedef struct vbmap_struct{
    U_INT32 	status;	/* 0, or error from the dma mapping functions */
    U_INT32 	valid_flag;	
			/* 2 if ready to talk to, 0 or 1 if not. 
			 *  2 means the mapping and probing for 
			 *  this entry has been done (for final release,
			 *  we don't probe other clients, we assume they are 
			 *  up because their state is VB_UP in the census, 
			 *  however we do probe the bm).
			 *  0 means it hasn't been mapped or probed.
			 *  1 means it has been successfully mapped, but
			 *  it has to be probed still.
			 *  For final release, we set the valid_flag to 2
			 *  after successfully mapping a remote node, because
			 *  we don't bother doing a badaddr.
			 */
    U_INT32 	byte_count;     
			/* Size in bytes of area to map.
			 * Both inbound and outbound get this from the 
			 * census table's vmesize field.
			 */
    vme_atype_t address_space; 
			/* Address modifier for vme addr (copy from census 
			 * both inbound and outbound get this from the
			 * census table's vmeaddr_am field.
			 */
    vme_atype_t swap_info; 
			/* Either byte, word, longword, or no swap.
			 * For first release, this is noswap, since we
			 * are only supporting little endian machines.
			 */
    vme_addr_t 	vmeaddr;/* For an outbound mapping, this is the vme address 
			 * that the remote node's memory is mapped to.
			 * For an inbound mapping, this is the vme address
			 * that we obtained at checkin and which we will map
			 * our local l3 queues to (copy from census table's
			 *  vmeaddr field)
			 */
    /**** Used for outbound mappings only: ****/
    io_handle_t vb_io_handle; 
			/* io handle returned from vba_map_csr() and
			 * input to io_copyin/out functions for an OUTBOUND
			 * mapping (map a remote node's memory at a specified
		  	 * vme address to my local memory).
			 */
    /**** Used for inbound mappings only: ****/
    dma_handle_t vb_dma_handle; 
			/* dma handle returned from vba_set_dma_addr() and
			 * input to dma_map_load() on for an inbound mapping
			 * (my local memory mapped to a given vme address) 
			 * or if dynamically mapped, it is returned from
			 * dma_map_load().
			 */
    sg_entry_t  vb_dmaex_sg;
			/* Used for inbound mapping, stores bus address -
			 *  byte count pairs.
			 */
    vm_offset_t	local_va;  
			/* For an inbound mapping, this address is input
			 * to dma_map_load() and is the virtual address of 
		 	 * the local memory that was malloc'd.
			 * For an outbound mapping, this address is not
			 * used... instead, the vb_io_handle is used to
			 * read/write to the remote node's memory.
			 */
    vb_fct_struct fcts; /* read and write functions for this vb map struct*/
}vbmap_struct_t;


/* VB driver node information */
typedef struct vb_node_info_struct{
  U_INT32 vb_bm_revision;/* Version of driver software copied from l2 box mgr*/
  U_INT32 vb_node_index; /* Index into level 2 and 3 arrays for this node */
  U_CHAR  acting_bm;     /* True if this node is the current box manager */
  U_INT32 l2size;        /* Size of box manager l2 data */
  U_INT32 l2wka;         /* Well known VME address of box manager l2 queue */
  struct  vbmap_struct l2map;	    /* Mapping information for box mgr l2 area */
  struct  vbmap_struct A16_vbmap;   /* Outbound mapping information for A16 */
  struct  vb_capabilities vb_caps;  /* Configurable node capabilities */
  struct  vb_multi_info local_vbmi; /* Local Multicast filtering information */
  int     checkin_complete;   	    /* We have registered with the box mgr */
  U_INT32 next_dst_node;	    /* Next node to try to send to */
  struct  vb_lan_reg_struct vb_sta_addr; /* Local node's vb LAN address */
}vb_node_info_t;

/* Typedef for box manager level 2 communication data structures.
 * Actual size of array is variable according to vb_cfg.vb_maxnodes.
 */
typedef struct l2comm_struct{
        struct l2comm_hdr l2comm_header;
        struct censusinfo census_table[VB_MAXNODES_LIMIT];
}l2comm_struct_t;

/* Typedef for client-to-client communication data structures.
 * Actual size of array is variable according to vb_cfg.vb_maxnodes.
 */
typedef struct l3comm_struct{
        struct l3comm_hdr l3comm_header;
        struct l3queue_struct l3queue_table[VB_MAXNODES_LIMIT];
}l3comm_struct_t;

/*
 * Backplane software status per interface.
 * Each interface is referenced by a network interface structure,
 * is_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its
 * address, etc....
 */
#define is_if   is_ac.ac_if             /* network-visible interface    */
#define is_addr is_ac.ac_enaddr         /* The VB LAN address (fixed
                                         * prefix plus cpu index).
                                         */
struct  vb_softc {
        struct  ether_driver is_ed;     /* Ethernet driver common part    */
#define is_ac   is_ed.ess_ac            /* Ethernet common part */
#define ctrblk  is_ed.ess_ctrblk        /* Counter block                  */
#define ztime   is_ed.ess_ztime         /* Time counters last zeroed      */

        struct vbdebug {
	    int vb_nombuf;		/* packet was dropped due to no mbuf*/
            int vb_showmulti;       	/* debug: show multicast add/delete */
            int vb_misscnt;         	/* missed packet counter */
            int vb_interrupts;      	/* number of times vbiopoll was
                                         * entered if poll mode, otherwise
                                         * the number of times vbintr was
                                         * entered if interrupt mode */
            int vb_lwcs;        	/* number of times vbintr_lwc was
                                         * entered */
            int vb_iothreads;       	/* number of times the vbintr_thread
                                         * or vbintr_lwc was entered. */
            int vb_iopolls;        	/* number of times vbiopoll was
                                         * entered */
	    int vb_restarts;	        /* number of times we restarted */
            int vb_recvpktlifetime; 	/* number of times we entered
                                         * vb_recv_pktlife function */
            int vb_transpktlifetime; 	/* number of times we entered
                                         * vb_transmit_pktlife function */
        } vb_debug;

        int     unit;                   /* unit number from ctlr->ctlr_num */
        event_t vb_process_io_event;    /* For i/o processing synchronization*/
        simple_lock_data_t lk_vb_softc; 

        /* This is the vme backplane node specific structure */
        struct vb_node_info_struct vb_node_info;
};

#define vbnombuf sc->vb_debug.vb_nombuf
#define vbshowmulti sc->vb_debug.vb_showmulti
#define vbmisscnt sc->vb_debug.vb_misscnt
#define vblwcs sc->vb_debug.vb_lwcs
#define vbinterrupts sc->vb_debug.vb_interrupts
#define vbiothreads sc->vb_debug.vb_iothreads
#define vbiopolls sc->vb_debug.vb_iopolls
#define vbrestarts sc->vb_debug.vb_restarts
#define vbrecvpktlifetime sc->vb_debug.vb_recvpktlifetime
#define vbtranspktlifetime sc->vb_debug.vb_transpktlifetime


/* Short cuts to read and write functions */
#define vbReadB(v,adr)      ((v)->fcts.fct_vbReadByte(v,(char *)(adr)))
#define vbWriteB(v,adr,dat) ((v)->fcts.fct_vbWriteByte(v,(char *)(adr),dat))
#define vbReadBO(v,adr)      ((v)->fcts.fct_vbReadByteO(v,(adr)))
#define vbWriteBO(v,adr,dat) ((v)->fcts.fct_vbWriteByteO(v,(adr),dat))

#define vbReadW(v,adr)      ((v)->fcts.fct_vbReadWord(v,(short *)(adr)))
#define vbWriteW(v,adr,dat) ((v)->fcts.fct_vbWriteWord(v,(short *)(adr),dat))
#define vbReadWO(v,adr)      ((v)->fcts.fct_vbReadWordO(v,(adr)))
#define vbWriteWO(v,adr,dat) ((v)->fcts.fct_vbWriteWordO(v,(adr),dat))

#define vbReadI(v,adr)      ((v)->fcts.fct_vbReadInt(v,(int *)(adr)))
#define vbWriteI(v,adr,dat) ((v)->fcts.fct_vbWriteInt(v,(int *)(adr),dat))
#define vbReadIO(v,adr)      ((v)->fcts.fct_vbReadIntO(v,(adr)))
#define vbWriteIO(v,adr,dat) ((v)->fcts.fct_vbWriteIntO(v,(adr),dat))

#define vbReadQ(v,adr)      ((v)->fcts.fct_vbReadQuad(v,(long *)(adr)))
#define vbWriteQ(v,adr,dat) ((v)->fcts.fct_vbWriteQuad(v,(long *)(adr),dat))
#define vbReadQO(v,adr)      ((v)->fcts.fct_vbReadQuadO(v,(adr)))
#define vbWriteQO(v,adr,dat) ((v)->fcts.fct_vbWriteQuadO(v,(adr),dat))

#define vbReadBlockB(v,src,dst,cnt)  ((v)->fcts.fct_vbBlockReadByte (v,(char *)(src),(char *)(dst),cnt))
#define vbWriteBlockB(v,src,dst,cnt) ((v)->fcts.fct_vbBlockWriteByte(v,(char *)(src),(char *)(dst),cnt))
#define vbReadBlockBO(v,src,dst,cnt) ((v)->fcts.fct_vbBlockReadByteO (v,(src),(dst),cnt))
#define vbWriteBlockBO(v,src,dst,cnt) ((v)->fcts.fct_vbBlockWriteByteO(v,(src),(dst),cnt))

#define vbZeroBlockBO(v,dst,cnt) ((v)->fcts.fct_vbBlockZeroByteO(v,(dst),cnt))

