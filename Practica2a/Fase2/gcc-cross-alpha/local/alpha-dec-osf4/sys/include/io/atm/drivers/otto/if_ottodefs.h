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
 * @(#)$RCSfile: if_ottodefs.h,v $ $Revision: 1.1.36.2 $ (DEC) $Date: 1999/02/05 13:24:09 $
 */
/* Here's how this driver manages the descriptors in the OTTO.
   You should first read the OTTO hardware spec to understand what the
   descriptors do.

   This code treats descriptors as 64-bit quantities.    That is
   descriptor n starts at  byte position 8*n into the descriptor
   table (which is at address OTTO_DESCPOS within the static RAM--
   see if_ottoreg.h)

   OTTO_FINALFRAG is a fragment descriptor for a few hundred
   bytes of otherwise unused memory.  The purpose is to
   absorb unwanted DMA writes.

   OTTO_EMPTYPKT is pkt descriptor pointing to one fragment,
   OTTO_FINALFRAG, and looped back to itelf so it has infinite
   length.

   OTTO_EMPTYRING is a receive rignt that looks perpetually
   empty.  It can never receive a packet.  There is one packet
   descriptor, OTTO_EMPTYPKT, always disabled.

   OTTO_FULLRING is a receive ring that looks perpetually full.
   It receive an infinite number of packets of infinte length.
   There is one packet descriptor, OTTO_EMPTYPKT, always enabled.

   There are OTTO_NTXPKTS transmit packet descriptor, starting
   at descriptor OTTO_TXPKTSTART.   Each transmit descriptor
   is immediately follwed by OTTO_MAXFRAGSPERTXBUF
   fragment descriptors.  The packet descriptor always points
   to the fragment descriptor following it.  If a transmit packet has
   more fragments than  OTTO_MAXFRAGSPERTXBUF, it must be copied to avoid
   fragments.

   There are OTTO_NRINGS receive ring descriptors, starting at
   descriptor OTTO_RINGSSTART.  Each ring descritpor is immediately
   followed by OTTO_MAXPKTSPERRING receive packet descriptors.
   The ring descriptor invariably points into the packets immediately
   following it, which are arranged in a ring.

   There are OTTO_NRXPKTS collections of fragment descriptors,
   starting at descriptor OTTO_RXPKTSTART.  Each collection
   contains OTTO_MAXFRAGSPERRXBUF fragment descriptors.  The fragments
   in such a collection are invariably used to hold the fragemnts
   of a single receive packet.
 */
#define OTTO_MAXFRAGSPERTXBUF	7	/* no of frags per txpkt */
#define OTTO_MAXFRAGSPERRXBUF	8	/* no of frags per rxpkt */
#define OTTO_MAXPKTSPERRING	15	/* no of rxpkt's per ring */
					/* more efficient if this is (2**n)-1 */

/* these macrosallocate descriptors to various functions */
#define OTTO_FINALFRAG		0
#define OTTO_EMPTYPKT		1
#define OTTO_EMPTYRING		2
#define OTTO_FULLRING		3

#define OTTO_NTXPKTS		128
#define OTTO_TXPKTSTART		4
#define OTTO_TXPKTEND	(OTTO_TXPKTSTART+(OTTO_MAXFRAGSPERTXBUF+1)*OTTO_NTXPKTS)

#define OTTO_NRINGS		32
#define OTTO_RINGSSTART		OTTO_TXPKTEND
#define OTTO_RINGEND	(OTTO_RINGSSTART+(OTTO_MAXPKTSPERRING+1)*OTTO_NRINGS)

#define OTTO_NRXPKTS ((OTTO_MAXDOUBLEDESC-OTTO_RXPKTSTART) / OTTO_MAXFRAGSPERRXBUF)
#define OTTO_RXPKTSTART		OTTO_RINGEND
#define OTTO_RXPKTEND	(OTTO_RXPKTSTART+OTTO_MAXFRAGSPERRXBUF*OTTO_NRXPKTS)

/* XXX this is to reduce the number of cells available to the
 * receiver for the purpose of testing fragmented receives
 * Note: do NOT turn on flow control if running this test.
 */
#if 0
#define OTTO_TXCELLS  (OTTO_MAXCELLS / 4)
#define OTTO_NOACKCELLS       (OTTO_MAXCELLS-OTTO_TXCELLS-OTTO_CELLS_PER_ROW)
#else
#define OTTO_TXCELLS  (OTTO_MAXCELLS/4)
#define OTTO_NOACKCELLS       (OTTO_MAXCELLS/4)
#endif

#define OTTO_PRI_PKT 2          /* number of outstanding priority packets */

#define OTTO_MAXXMTQUEUED (OTTO_NTXPKTS-1-OTTO_PRI_PKT)
        /* max number of packets to queue for xmt on otto */

/* FTW FIXME: shouldn't know about MTU here
 */
#define OTTO_MAXXMTBYTESQUEUED (48*OTTO_TXCELLS-32768-200-512*OTTO_PRI_PKT)
        /* max number of bytes in transmit packets queued on device
           The 200 allows space for header and trailer bytes.
           The 32768 is a maximum length MTU.
           The 512*OTTO_PRI_PKT allows for OTTO_PRI_PKT priority packets.  */

#define OTTO_NON_ETHER_BUFFERS 4	/* number of non-ether pkt buffers */
#define OTTO_NON_ETHER_BUFFERLEN 1600	/* size of non-ether packet buffers */

#define OTTO_CRCLEN 4           /* size of AAL5 CRC */
#define OTTO_MINTRAILERLEN 8    /* min size of AAL5 trailer */
#define OTTO_MAXTRAILERLEN 56   /* max size of AAL5 trailer (rounded up mod 8)*/
/* Dummy buffer used for the final DMA fragment.   This fragment is
   used to terminate all DMA chains.   It will swallow all received
   packets that are too long and source all transmit packets that are too
   long. */
#define OTTO_DUMMYLEN (1 << 8)   /* must be power of two > 2 and <= page size */

/* structure in the softc per ring in the controller RAM */
struct otto_ring {
	otto_uword32 tag;		/* tag to use */
	unsigned short desc;		/* index of ring descriptor */
	unsigned short next;		/* free list */
	unsigned short nextfree;	/* next free entry in ring */
	unsigned short lastused;	/* last used entry in ring */
		    /* The ring is empty when nextfree == lastused.
		       The ring can never be totally filled --- it is
		       illegal to use an entry if doing so would set
		       nextfree == lastused.  */
       unsigned short missed;		/* packets we couldn't allocate
       					   last time */
       unsigned short pktindex[OTTO_MAXPKTSPERRING];
       					/* indexes of rxpkt structures
       					   that have been queued on this 
       					   ring */
};

struct otto_xmtq {
	struct otto_xmtq *next;
	unsigned short pktswaiting;	/* # of this queue's xmt pkts in ctlr */
	unsigned short maxpktswaiting;	/* max allowed pktswaiting */
        unsigned short qhigh;		/* true if high water mark reached */
	unsigned short congestion; 	/* congestion counter */
	struct ifqueue *pifq;   	/* ptr to xifq, or to if_snd */
	struct mbuf *rxpartial;		/* for multi-frag packets, mbuf chain
				   	   of frags received thus far */
	unsigned crc;			/* accumulated crc for multi-frag packets */
	int len;			/* total len so far for multi-frag packets */
	atm_vc_p vcp;
};

struct otto_txfrag {
	unsigned next;
	int nparts;
	int np;
	struct mbuf *m0;
	unsigned tcrc;
	int tlen;
	int index;
};

/* structure to hold DMA mapping resources */
struct otto_dma_handle {
	struct otto_dma_handle *next;
	dma_handle_t handle;
};

/* receive packet buffers */
struct otto_rxpkt {
	 unsigned short next;		/* free list */
	 unsigned short desc;		/* index of pkt descriptor */
	 struct mbuf *m;		/* mbuf mapped */
	 struct otto_dma_handle *dma_handle;	/* dma handles for mbuf */
};

/* transmit packet buffers */
struct otto_txpkt {
	 unsigned short next;		/* free list */
	 unsigned short desc;		/* index of pkt descriptor */
	 unsigned len;			/* packet length, to keep
	 				   track of cell usage in adapter */
	 int vci;			/* VCI used for transmission */
	 struct mbuf *m;		/* mbuf mapped */
	 struct otto_dma_handle *dma_handle;	/* dma_handles for mbuf */
	 unsigned char *trailerv;	/* virtual address of trailer buffer */
	 unsigned long trailerp;	/* physical address of trailer buffer */
};

#define OTTO_BPUL	(sizeof (unsigned long) * 8)

#define	OTTO_MAX_SCHED_LEN	4096
#define	OTTO_MAX_CELL_RATE	353207

#define HASHSIZE		128		/* must be power of two */
#define OTTO_HASH(vci)		((vci) & (HASHSIZE-1))

struct otto_data {
	char    *slotaddress;			/* address of TC slot */
	volatile otto_uword32 *rom;		/* address of the ROM */
	unsigned romsize;			/* address space taken by ROM
						   in bytes */

        volatile otto_uword32 *uid;		/* UID in ROM */
        volatile otto_uword32 *hostname;	/* hostname in ROM */

	volatile otto_uword32 *ram;		/* address of the RAM */
	unsigned ramsize;			/* addres space taken by RAM
						   in bytes */
        unsigned ncellbuffers;			/* # of cell buffers in RAM */

        volatile struct otto_descriptor *descriptors;	/* descriptors in RAM */
        unsigned ndescriptors;			/* number of 8 byte descriptors
        					   in RAM (used for pkt descriptors,
        					   ring descriptors,
        					   fragment descriptors)*/

	unsigned reportringsize;		/* report ring size in bytes */

	volatile otto_uword32 *ram_writelo;	/* atomic lo-half writes */
	volatile otto_uword32 *ram_writehi;	/* atomic hi-half writes */

	volatile struct otto_csr *csr;		/* main CSR */
	volatile struct otto_dma *dma;		/* DMA chip */
	volatile otto_uword32 *fifo;		/* FIFO */
	volatile otto_uword32 *cell;		/* cell chip */
	volatile otto_uword32 *suni;		/* SUNI chip */
	volatile otto_uword32 *exec;		/* execute microcode request */
	volatile otto_uword32 *txrequest;	/* transmit request */
	volatile otto_uword32 *activate;        /* activate txvc */
	volatile otto_uword32 *ackfifoptrs;     /* read ACK FIFO ptrs */

	/* these addresses do the same as those above except accesses also
	   acknowledge a pending interrupt */
	volatile otto_uword32 *rom_intack;
	volatile otto_uword32 *ram_intack;
        volatile struct otto_descriptor *descriptors_intack;
	volatile otto_uword32 *ram_writelo_intack;
	volatile otto_uword32 *ram_writehi_intack;
	volatile struct otto_csr *csr_intack;
	volatile struct otto_dma *dma_intack;
	volatile otto_uword32 *fifo_intack;
	volatile otto_uword32 *cell_intack;
	volatile otto_uword32 *suni_intack;
	volatile otto_uword32 *exec_intack;
	volatile otto_uword32 *txrequest_intack;

	struct otto_dma_handle dma_handle[2048];
	struct otto_dma_handle *dma_free;

	otto_uword32 ucodeversion;	/* microcode version
					   Initialized by otto_unsetreset */
        otto_uword32 ucodecreated;	/* microcode creation date
					   Initialized by otto_unsetreset */


        /* information about how the hardware has been programmed */
        int unit;			/* device unit number */
	int isoppo;			/* true is this is an OPPO (i.e. PCI) */

        volatile struct otto_rep *reportbase;
        				/* system virtual address
       					   of report ring */
	unsigned long reportdma;	      /* DMA address of report ring */
	struct otto_dma_handle *reporthandle;	/* report ring dma handle */ 
	char *dummybuffer;			/* dummy buffer points into area
						   after report ring */
	unsigned long dummydma;			/* dummy buffer DMA addr */


        unsigned txcells;		/* number of transmit cells allocated */ 
        unsigned rxcells;		/* number of receive cells allocated */
        unsigned noackcells;		/* number of noack receive cells
       					   allocated */ 

        unsigned ringfreelist;	/* head of free list of ring descriptors */
        struct otto_ring rings[OTTO_NRINGS];	/* array of rings */

        unsigned rxpktfreelist;	/* head of free list of rxpkt descriptors */
        struct otto_rxpkt rxpkts[OTTO_NRXPKTS];	/* array of receive pkts */

        unsigned txpktfreelist;	/* head of free list of txpkt descriptors */
        struct otto_txpkt txpkts[OTTO_NTXPKTS];	/* array of transmit packets */
        unsigned txfragfreelist;	/* head of free list of txpkt descriptors */
        struct otto_txfrag txfrags[OTTO_NTXPKTS];	/* array of transmit packets */

			/* bit maps of receive and transmit VCs */
	unsigned long rxvcfree[OTTO_MAXVC / OTTO_BPUL];
	unsigned long txvcfree[OTTO_MAXVC / OTTO_BPUL];

	/* heads of lists of packets queued on transmit VCs */
	unsigned txvcpkts[OTTO_MAXVC]; 

	/* rings associated with VCs */
	unsigned rxvcrings[OTTO_MAXVC];

	/* Buffers for AAL5 trailers of tx packets.
	   This points into the area after the report ring 
	   It has size (OTTO_NTXPKTS+1+OTTO_NTXPKTS/8)*OTTO_MAXTRAILERLEN
	   bytes */
	unsigned char *trailerspace;
	unsigned long trailerspacedma;		/* dma address of start
						   of trailer space */

	int nextreport;				/* index of next report */
	otto_uword32 reporttag;			/* tag expected in report */

	int xmtwaiting;				/* # pkts queued for xmt */

	/* addressing */
	struct ether_addr physaddress[8];		/* hardware address of device */

	struct CONTROLLER_STRUCT *ctlr;		/* controller struct passed
						   to probe routine */

	int lbolt;	/* woken once per second when waiting in ottoinit.
			   global lbolt can't be using for discless init */

	struct otto_stats otto_stats;

	/* OSF memory allocator can't handle requests for contiguous memory.
	   We allocate what's needed here. */

	char reportBuf[OTTO_REP_RING_LEN_BYTES*2+OTTO_DUMMYLEN+
			OTTO_NTXPKTS*OTTO_MAXTRAILERLEN+NBPG];

	atm_drv_handle_t otto_handle;
	atm_drv_params_p driver_params;

	atm_vc_p vc_buckets[HASHSIZE];
				/* all active VCs stored in hash bucks */
	int active_vcs;		/* number of active vc's */

	int otto_numid;		/* number of MAC addresses on this board */
	int kicker;		/* woken up when the transmitter hits its
				 * low-water mark on pending xmits
				 */
	int updown;		/* called on SUNI GPIN transitions to see
				 * if the link has gone down or come back
				 * up
				 */
	atm_vc_p next_vc;	/* the next VC eligible for transmit
				 */
#define OTTO_VC_IGNORE  0x01            /* ignore received packets */
#define OTTO_VC_FC      0x02            /* flow controlled */
#define OTTO_VC_SCHED   0x04            /* scheduled */
#define OTTO_VC_PVC     0x08            /* a permanent virtual circuit */
#define OTTO_VC_ARPXMT  0x10            /* inARP has been sent */
#define OTTO_VC_ARPRCV  0x20            /* inARP has been received */
#define OTTO_VC_ARPRCV_RECENT 0x40      /* inARP has been received recently */
#define OTTO_VC_DONT_ARP 0x80           /* don't arp on this circuit */
#define OTTO_VC_STOPPED 0x100           /* stopped for credit resync */
#define OTTO_VC_RVC     0x200           /* a resilient virtual circuit */
#define OTTO_VC_SVC     0x400           /* a switched virtual circuit */
#define OTTO_VC_FIXED   0x800           /* allocated for internal use */
#define OTTO_VC_USED    0x1000          /* used to send a packet recently */
#define OTTO_VC_UPDATED 0x2000          /* updated by incoming packet recently*/
#define OTTO_VC_STALE 0x4000            /* address needs to be updated soon */
	/* 0x8000 is reserved for OTTOPVM */
#define OTTO_VC_NOFC 	0x10000         /* must not use flow control */
#define OTTO_VC_ALLOCATED (OTTO_VC_PVC|OTTO_VC_RVC|OTTO_VC_SVC|OTTO_VC_FIXED)

	int vcflags[OTTO_MAXVC];	/* per-VC state */
        struct snmpstate {
                unsigned up;                    /* 1 => link is up, 0 =>down*/
                time_t lastpktrcvd;             /* time last packet received */
                time_t lastpktsent;             /* time last request sent */
                unsigned backoff;               /* backoff interval */
                struct otto_fakesnmp pkt;       /* data */
        } snmp;
	struct mbuf *fakesnmp_mbuf;

	struct mbuf *otto_listsimplesend;	/* list of transmits generated
						   by otto driver itself */

        /* information about transmits queues: how much data is in
           each mbuf queue and in the controller */
        struct {
                int pktswaiting;                /* # xmt pkts in controller */
                int byteswaiting;               /* # xmt bytes in controller */
                int totallen;                   /* # xmt pkts in mbuf queues */
                int maxtotallen;                /* max allowed totallen */
                                                /* eligible for sending */
        } xmtqueues;
	int xmt_processing;			/* processing transmit requests? */

	struct otto_xmtq *ready;        	/* list of queues */
	simple_lock_data_t rdy_q_lock;		/* lock for ready queue only */ 
	struct fc_state *fcs;			/* flow control resync state */
	atm_vc_p resync_vc;			/* VC used for FlowMaster    */
 
 	int flow_on;	       /* = 1 if ATM_FLOW_VENDOR is sent AND the board 
 				  is up AND has_fm is true */
 
 	int flow_requested;    /* = 1 if ATM_FLOW_VENDOR was requested but the
 				  has_fm is false because no SNMP packet has
 				  yet been received. Once an SNMP packet is
 				  received, the code will enable flow control.
				*/
	/* watchdog values */
	struct otto_watchdog {
		unsigned resetsuni;             /* suni should be held reset
						   for this many seconds */
		unsigned reset;                 /* reset called */
		unsigned notgettingcells;       /* SUNI upset on last look */
	} otto_watchdog;
	int has_fm;				/* endpoint supports FLOWmaster */
	unsigned int defaultring;
	int otto_sdh;
	unsigned long ottostamp;

	int suspended;			/* if non-zero, we have hit our receive 
					   threshold so no further interrupts 
					   are permitted until lta_pause ticks 
					   have elapsed. */
	int livelock_count;		/* # of times rcv threshold was hit */

	ihandler_id_t   *hid;           /* ihander_id_t rtn from handler_add */

	u_long schedlen;              		/* current schedule length */
	u_long schedfree;             		/* free slots in schedule */
	u_long schedbase;             		/* base/start of schedule */
	u_int sched[OTTO_MAX_SCHED_LEN]; 	/* our copy of the schedule */

	int after_attach;		/* attach done flag -- our crude way
					   of implementing "aft-attach" since
					   the TC bus code cannot support this
					   for certain early Bird machines */
};

struct  otto_lock {
	simple_lock_data_t lock;	/* SMP lock for driver/softc */
    	int owner_cpu;			/* cpu where lock was obtained */
	int count;			/* nested lock obtained count */
};

/*
 *  Special locking macros.
 *
 *  OTTO_OBTAIN_LOCK	
 *	Attempt to get the lock without spinning.  If this is not possible, 
 *	see if we already own the lock.  If both of these fail, wait for
 *	the lock.  When the lock is finally obtained, mark us as the owner
 *	and bump the nesting count.
 *
 *  OTTO_RELEASE_LOCK
 *	Decrement the nesting count.  If it is now zero, release the lock.
 */

#define OTTO_OBTAIN_LOCK(lp)	{		\
	if ((!simple_lock_try(&(lp)->lock)) &&	\
	    ((lp)->owner_cpu != cpu_number())) 	\
	    simple_lock(&(lp)->lock);		\
	(lp)->owner_cpu = cpu_number();		\
	(lp)->count ++;				\
}		

#define OTTO_RELEASE_LOCK(lp)	{		\
    	(lp)->count --;				\
    	if ((lp)->count == 0) {			\
	    (lp)->owner_cpu = -1;		\
            simple_unlock(&(lp)->lock);		\
	}					\
}

#define OTTO_STATS_INC(x,y)	(((x)->otto_stats.bothlinks.y)++)
#define OTTO_STATS_INC_L(x,y,l)	(((x)->otto_stats.perlink[l].y)++)

/* A xilinx code descriptor */
struct otto_xilinxdesc {
	unsigned char *data;	/* the data */
	int stride;		/* stride between bytes of data */
	int checksum;		/* sum of bytes */
	int len;		/* bytes in data */
};

int otto_initialize (int unit, char *devicebase, struct otto_data *od,
	struct otto_xilinxdesc *xilinxcode,
	unsigned txcells, unsigned noackcells, char *membase);
/* Initialize the otto_data structure.  Return 0 on success and -1 on failure.
   This routine calls the routines below to accomplish this. 
   This routine may print error messages on the console when it fails.

   unit is a device unit numbers used solely for error reporting

   devicebase is a system virtual address for the base
   of the device in IO space.  It will be passed to otto_sethwaddresses.

   If xilinxcode is not 0, it should point to a xilinx code descriptor.
   If it is 0, the default xilinxcode for the device is loaded.
   xilinxcode will be passed to otto_loadxilinx.

   txcells and noackcells are values passed to otto_buildcelllists.

   membase should point to a physically contiguous region of size
   OTTO_REP_RING_LEN_BYTES*2+OTTO_DUMMYLEN+ OTTO_NTXPKTS*OTTO_MAXTRAILERLEN+NBPG
   bytes. */

int otto_softreset (struct otto_data *od, unsigned txcells, unsigned noackcells);
/* reset the device, and reinitialize the VC and descriptor free lists.
   The device is left in a state where it can send and receive packets.
   txcells and noackcells are values passed to otto_buildcelllists. */

void otto_sethwaddresses (char *devicebase, int unit, struct otto_data *od,
	char *reportbase, unsigned long reportphys,
	char *dummybase, unsigned long dummyphys,
	char *trailerbase, unsigned long trailerphys);
/* Initialize the addresses in the otto_data structure.
   This routine must be called before of the routines below are celled.

   unit is a device unit number used solely for error reporting

   devicebase is a system virtual address for the base
   of the device in IO space.

   reportbase should point to a natually aligned, physically
   contiguous, 64Kbyte region for the report ring.   reportphys should
   be its physical (bus) address.

   dummybase should point to a contiguous region of size OTTO_DUMMYLEN bytes.
   dummyphys should be its physical (bus) address.

   trailerbase should point to a contiguous region of size
   OTTO_NTXPKTS*OTTO_MAXTRAILERLEN bytes.  trailerphys should be its
   physical (bus) address.  */

void otto_initfreelists (struct otto_data *od);
/* initialize the VC and descriptor free lists */

void otto_setreset (struct otto_data *od);
/* Put device in reset state. */

void otto_unsetreset (struct otto_data *od);
/* Take device out of reset state.
   As a side effect, this routinie initializes od->ucodeversion and 
   od->ucodecreated */

void otto_lockpioonly (struct otto_data *od);
/* Lock microsequencer to service PIO requests only. */

void otto_unlockpioonly (struct otto_data *od);
/* Allow microsequencer to service non-PIO requests. */

int otto_loadxilinx (struct otto_data *od,
	struct otto_xilinxdesc *xilinxcode);
/* Load otto's xilinx chips.  Return 0 on success, -1 on failure.
   If xilinxcode is not 0, it should point to a xilixn code descriptor.
   If it is 0, the default xilinxcode for the device is loaded.

   This routine may print an error message on the console if it fails.
   When it reports failure, it is a hard failure --- several attempts
   have been made.
 */

int otto_sramtest (struct otto_data *od);
/* Test the static RAM. Returns 0 on success, and -1 on failure.
   The static RAM is zeroed when this routine returns.

   This routine may print error messages on the console when it fails.  */

void otto_setreportbase (struct otto_data *od);
/* Set the base of the report ring using the reportbase field in od.
   This field should contain the system virtual address of the report
   ring area---a physically contiguous region of size od->reportringsize.  
   The ring is initialized to have all tag bits set. */

void otto_buildcelllists (struct otto_data *od,
	unsigned txcells, unsigned noackcells);
/* Construct initial cell lists for the device.
   txcells cells are set aside for transmit.  (The driver must ensure that
   no more than txcells transmit cells could ever be in use.)

   noackcells cells are set aside for the cells that are guaranteed
   to be available for flow controlled traffic.   All other cell
   buffers will be used for receive cells.    It is good for there
   to be many receive cell buffers in addition to those strictly
   needed, because this allows the sender to transmit a burst of cells
   and to receive acknowledgements quickly, without waiting for cells
   to be given to the host processor.  */

void otto_initsuni (struct otto_data *od);
/* initialize the SUNI chip */

void otto_resetsuni (struct otto_data *od);
/* put the SUNI chip into a RESET state */

unsigned otto_allocring (struct otto_data *od);
/* allocate a ring descriptor, and return its index, or 0 if no descriptor
   exists.  */

void otto_freering (struct otto_data *od, unsigned index);
/* free a ring descriptor allocated by otto_allocdesc.  It is illegal
   to free descriptor 0 */

unsigned otto_allocrxpkt (struct otto_data *od);
/* allocate a receive packet descriptor, and return its index, or 0
   if no descriptor exists.  */

void otto_freerxpkt (struct otto_data *od, unsigned index);
/* free a receive packet descriptor allocated by otto_allocrxpkt.  It is illegal
   to free descriptor 0 */

unsigned otto_alloctxpkt (struct otto_data *od);
/* allocate a transmit packet descriptor, and return its index, or 0
   if no descriptor exists.  */

void otto_freetxpkt (struct otto_data *od, unsigned index);
/* free a transmit packet descriptor allocated by otto_alloctxpkt.  It is illegal
   to free descriptor 0 */

unsigned otto_allocvc (unsigned long *bitmap, unsigned vc);
/* allocate a VC.  The lowest available VC no smaller than vc is allocated.
   Retrusn 0 if there is no available VC.  VC 0 should be allocated 
   at initialization time, and never freed.   */

void otto_freevc (unsigned long *bitmap, unsigned vc);
/* free a VC */

void otto_setrxvc (struct otto_data *od, unsigned vc,
	int ign, int pkt, int ack, int ring);
/* Set the ign, pkt, ack and ring values in an receive VC's structure.
   For each of ign, pkt, ack and ring, the value -1 indicates no change.
   For booleans, 0 reset the bit, and non-zero sets the bit */

void otto_settxvc (struct otto_data *od, unsigned vc,
        int usesched, int enflowcntl, int overflow, int credits);
/* Set the usesched, enflowcntl, overflow and credits values in a transmit
   VC's structure.
   For each of usesched, enflowcntl, overflow and credits, the value -1
   indicates no change.
   For booleans, 0 reset the bit, and non-zero sets the bit */

void otto_setsched (struct otto_data *od, unsigned index, unsigned vc);
/* Sets schedule slot index to indicate the given vc. */

void otto_wait_for_phaselock (struct otto_data *od);
/* waits a while for the SUNI and PLL to acquire lock */
/* It's unclear what happens if we continue operating the device
  when lock isn't acquired.   However, since we may need to call this
  from an interrupt routine, it waits only a limited time. */
