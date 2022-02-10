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
#pragma ident "@(#)$RCSfile: if_lpa_defs.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1997/09/29 21:04:14 $"

#ifndef _IF_LPA_DEFS_H_
#define _IF_LPA_DEFS_H_

#include <net/if_lane/g_types.h>
#include <io/atm/drivers/meteor/os_reg.h>
#include <io/atm/drivers/meteor/codes.h>

#ifndef ALIGN_64
#define ALIGN_64(value,size) (((long) value + (size - 1)) & ~(size - 1))
#endif

#define LPA_BPUL                (sizeof (unsigned long) * 8)

#define LPA_CRCLEN                 4      // size of AAL5 CRC
#define LPA_MAX_SCHED_LEN       4096
#define LPA_MAX_CELL_RATE     353207
#define LPA_MAXTRAILERLEN         56      // max size of AAL5 trailer (rounded up mod 8)
#define LPA_MAXVC               1024      // max vc_id, not maximum VCI.
#define LPA_MAX_VC_BITS           10      // 
#define LPA_MAXVP                  8
#define LPA_MINTRAILERLEN          8      // min size of AAL5 trailer
#define LPA_NTXPKTS             1024
#define LPA_NRXPKTS             1024
#define LPA_RSVD_XMT_PKTS          4      // reserved for ILMI/Signalling

#define LPA_STATS_INC(x,y)   (((x)->y)++)
#define LPA_STATS_INC_L(x,y,l)   (((x)->y)++)

#define LPA_TAG_FLIP(x)           (x==1 ? 0:1)

#define MAX_DMA_HANDLE ((1024 * 4) + 10)

#define MET_RCV_SLOT_MAX        1024
#define MET_RCV_REPORT        (1024 * 3)
#define MET_SLOT_SIZE_K_16K    16384
#define MET_XMIT_REPORT         1024
#define MET_XMIT_SLOT_MAX       1024

#define MAX_TIMERS                20

#define RCV_BUFFS_SMALL   32              // Only for critical packets
#define RCV_BUFFS_BIG     64


typedef unsigned          lpa_uword32;    // a 32 bit word 
unsigned int lpa_vpi_bits;
unsigned int lpa_rcv_holdoff_time;
unsigned int lpa_rcv_holdoff_pkt_cnt;

/*++
* Define the structure to hold the information for an allocated timer.
*
*   p_next -
*     Link to the next timer in the list.
*
*   os_handle -
*     The handle for the instantiation with which this timer is associated.
*     This is provided as a convenience so that the caller only has to deal
*     with timers instead of timers and instantiations.
*
*   mini_port_timer -
*     The NDIS timer information.
--*/

typedef struct _timer
   {
   struct _timer       *p_next;
   HANDLE               os_handle;
   LPA_TIMER_CALLBACK   user_callback;
   HANDLE               user_context;
   BOOLEAN              in_use;
   } TIMER_BLK;

// structure to hold DMA mapping resources

typedef struct _lpa_dma_handle 
   {
   struct _lpa_dma_handle *next;
   dma_handle_t           handle;
   } LPA_DMA_HANDLE;

// transmit packet buffers

typedef struct
   {
   unsigned short         next;           // free list
   unsigned               len;            // pkt len, track cell usage in adap
   unsigned               nSlots;         // track # of slot used 
   atm_vc_t              *xmtqp;          // queue that this packet came from
   struct mbuf           *m;              // mbuf mapped
   LPA_DMA_HANDLE        *dma_handle;     // dma_handles for mbuf
   unsigned char         *trailerv;       // virtual address of trailer buffer
   unsigned long          trailerp;       // physical addr of trailer buffer
   } LPA_XMT_PKT;

typedef struct
   {
   unsigned short         q_head;
   unsigned short         q_tail;
   } LPA_XMT_PKT_QUEUE;

typedef struct
   {
   UINT32 xmt_descr;
   UINT32 phys_addr;
   } XMT_SLOT_COPY;

/*+
 * Define flag values for the "flags" member of VC_INFO.
 *
 *  LPA_VC_FC -
 *    FLOWmaster is active on this VC.  Set when the VC is opened with 
 *    FLOWmaster enabled.  FLOWmaster routines can use this flag to detect
 *    if a FLOWmaster action is appropriate for the VC.
 *
 *  LPA_VC_STOPPED -
 *    The VC is currently stopped, no transmits may be started.  This flag is
 *    set when credit resynchronization on the VC starts, and is reset when the
 *    credit resynchronization completes.
 *
 *  LPA_VC_QHIGH -
 *    This flag is set when the number of queued transmit packets reaches
 *    a high number.  The driver can use this to notify the OS, and then 
 *    to notify the OS when the VC queue is no longer at a high level.
-*/

#define LPA_VC_FC             0x00000002
#define LPA_VC_STOPPED        0x00000100       // stopped for credit resync
#define LPA_VC_QHIGH          0x00020000

/*+
 * VC_RCV_INFO
 *
 * This is a sub-structure of the per-VC structure.  It is a convenient grouping
 * of VC information related to receives.
 *
 * m -
 *   The first mbuf in the chain of mbufs being received.
 *
 * last_m -
 *   The last mbuf in the chain of mbufs being received.  This is needed so that
 *   mbufs are in an ordered list, with the newest ones quickly added at the tail.
 *
 * has_sop -
 *   The driver uses this to detect SOP EOP violations across chained receive
 *   packets.  When set to TRUE, the driver has seen an SOP and is expecting 
 *   an EOP.
 *
 * dropping -
 *   An error has occured and the packet is being dropped.
 *
 * pkt_size -
 *   The running total of the packet being received on this VC.  This is needed 
 *   because the receive path supports chaining, and some state must be
 *   maintained across receive segments.
 *
 *   When a packet is not being received, this value is 0.  The final total is
 *   reported to the OS.
 *
 * slot_type -
 *   The Meteor receive slot type (small, big) for this VC.
 *
 * buffs_needed -
 *   The number of receive buffers that this VC needs to have posted.  This is 
 *   incremented everytime a receive buffer for the VC is given to the OS, but
 *   a receive buffer was not available to replace it.  It is decremented when
 *   the receive buffer is replaced.
-*/

typedef struct 
   {
   struct mbuf           *m;
   struct mbuf           *last_m;
   unsigned short         has_sop;
   unsigned short         dropping;
   unsigned               pkt_size;
   MET_SLOT_TYPE          slot_type;
   unsigned               buffs_needed;
   } VC_RCV_INFO;

/*+
 * VC_INFO
 *
 * One of these structures is instantiated for each VC that is opened.
 * It is an auxillary to the OS VC context which is stored in this VC
 * structure.  Whenever the OS passes a VC to the driver, it passes 
 * an OS VC context which the driver initializes to contain a pointer to
 * this structure.  The purpose of this structure is to contain driver specific
 * VC information.
 *
 * An array of these structures is instantiated when the NICs context is 
 * instantiated.  These structures may be inserted and removed from the 
 * transmit ready list, but they are never deallocated.
 *
 * p_next - 
 *   Links the structure onto lists, particulary the transmit ready list.
 *
 * enabled -
 *   If set to "true", the VC has been added and enabled.  The driver can
 *   use this to ensure that a packet can be transmitted, and that the 
 *   pointer to the OS VC context is valid.
 *
 * flags - 
 *   A mask of flags for this VC.  Flags are defined in this file by the 
 *   name LPA_VC_*.
 *
 * queued - 
 *   Set to true if there are any packets queued on the if queue for this VC.
 *
 * vc_id -
 *   The vc_id returned from met_vc_open.
 *
 * p_os_vc_info -
 *   Pointer to the OS VC structure for this VC.
 *
 * ifq -
 *   The IF queue (transmit pending queue) for this VC.
 *
 * slots_posted -
 *   The current number of transmit slots posted to this VC.  This is used to 
 *   prevent slow rate VCs from hogging all of the available transmit slots on
 *   Meteor.
-*/

typedef struct _VC_INFO
   {
   struct _VC_INFO       *p_next;
   int                    enabled;
   int                    flags;
   int                    queued;
   unsigned int           vpi;
   unsigned int           vci;
   unsigned int           vc_id;
   atm_vc_t              *p_os_vc_info;
   struct ifqueue         ifq;
   LPA_XMT_PKT_QUEUE      xmt_pkt_queue;
   VC_RCV_INFO            rcv;
   unsigned int           slots_posted;
   } VC_INFO;

typedef struct _AAL5_TRAILER
   {
   UINT8                  cpcs_uu;
   UINT8                  cpi;
   UINT8                  length[2];
   } AAL5_TRAILER;

struct lpa_rcv_slot 
   {
   unsigned short   nextFree;     // next free slot
   LPA_DMA_HANDLE *dma_handle;     // dma handles for mbuf
   struct mbuf    *m;              // mbuf used by this slot
   MET_SLOT_TYPE   slot_type;    // The type of Meteor slot allocated for this slot.
   int             missing_in_action;
   };

/*+
 * LPA_DATA
 *
 * xmt_slots_avail -
 *   The number of slots available on Meteor.  This number starts at a hardware
 *   defined limit.  It is decremented each time that the driver posts a 
 *   transmit slot to the hardware (which could be many for a single packet) and 
 *   is incremented whenever the driver processes the transmit report for the
 *   packet.
 *
-*/
typedef struct _lpa_data
   {
   unsigned int           xmt_slots_avail;
   unsigned int           rcv_buff_allocs_deferred;
 
   unsigned int           xmt_slot_index;
   unsigned int           rcv_slot_index;

   volatile io_handle_t   devicebase;
   UINT32                 int_holdoff;
  
   UINT32                *rxReportbase;
   UINT32                *txReportbase;
   int                    nextRXReport;    // index of next report
   int                    nextTXReport;    // index of next report
   UINT32                 rxReporttag;     // tag expected in report
   UINT32                 txReporttag;     // tag expected in report
  
   VC_INFO               *p_xmt_vc_ready_head;       // head of ready xmit queues
   VC_INFO               *p_xmt_vc_ready_tail;       // tail of ready xmit queues 

   int                    fc_credits;
   int                    fc_resync_vc;
  
   unsigned               xmt_pkts_next_free;   // head of free list of txpkt desc 
   unsigned               rcvFreeSlot;     // head of Free rcv slot 
   unsigned               rcvPostedSlot;   // head of posted rcv slot 

   LPA_DMA_HANDLE        *trailer_dma_handle;       // dma handles for trailer
   LPA_DMA_HANDLE        *rxReport_dma_handle;      // dma handles 
   LPA_DMA_HANDLE        *txReport_dma_handle;      // dma handles &&& not used?
   HANDLE                 met_handle;               // common code meteor handle
   HANDLE                 adap_handle;              // common code meteor handle
   unsigned               vc_mode;
   UINT32                 small_slot_size;          // cntrl2 csr setting 
   UINT32                 big_slot_size;            // cntrl2 csr setting

   // information about how the hardware has been programmed 

   int                    unit;                     // device unit number
  
   // Buffers for AAL5 trailers of tx packets.  This points into the area after 
   //   the report ring.  It has size: 
   //   (LPA_NTXPKTS + 1 + LPA_NTXPKTS / 8) * LPA_MAXTRAILERLEN bytes 

   unsigned char         *trailerspace;
   unsigned long          trailerspacedma;          // dma addr of trailer space

   // heads of lists of packets queued on transmit VCs

   struct controller     *ctlr;                     // controller struct passed
   ihandler_id_t         *hid;                      // return from handler_add
  
   LPA_DMA_HANDLE        *dma_free;

   atm_drv_handle_t       lpa_handle;
   HANDLE                 tm_an2_handle;
   atm_drv_params_t      *p_driver_params;

   atm_vc_t               *p_enabled_vcs_head;
   atm_vc_t               *vcnext;                   // next vc whose pkts xmit

   int                    active_vcs;          // number of active vc's
   UINT16                 tbl_len;

   // called on SUNI GPIN transitions to see if link has gone [down, up]

   int                    device_state;
   int                    link_state;
   int                    ilmi_up;
   UINT32                 ticks;
   int                    rev_id;
   BOOLEAN                run_lost_rcv_buffer_workaround;
   atm_media_type_t       phy_type;

   int                    max_vpi;
   int                    max_vci;
   int                    vpi_bits;
          
   unsigned short         rcv_error;                // receive error
   unsigned short         no_free_desc;             // no free buffer descriptor

   int                    possible_slots_lost;
   int                    ok_to_repost_small_slots;
   int                    ok_to_repost_big_slots;

   // counters for various errors

   unsigned int           peephole_done;
   unsigned int           peephole_error;
   unsigned int           hostAccess_error;
   unsigned int           xmtUnderflow;
   unsigned int           rcvFIFOOverflow;
   unsigned int           rcvDataOverflow;
   unsigned int           rcvNBS;
   unsigned int           rcvNSS;
   unsigned int           rcvNRS;
   unsigned int           rcvBSL;
   unsigned int           rcvSSL;
   unsigned int           rcvRSL;
   unsigned int           rcvNOP;
   unsigned int           rcvUVC;
   unsigned int           rcvUACK;

   unsigned int           hostAccess_error_saved;
   unsigned int           xmtUnderflow_saved;
   unsigned int           rcvFIFOOverflow_saved;
   unsigned int           rcvDataOverflow_saved;
   unsigned int           rcvNBS_saved;
   unsigned int           rcvNSS_saved;
   unsigned int           rcvNRS_saved;
   unsigned int           rcvBSL_saved;
   unsigned int           rcvSSL_saved;
   unsigned int           rcvRSL_saved;
   unsigned int           rcvNOP_saved;
   unsigned int           rcvUVC_saved;
   unsigned int           rcvUACK_saved;

   unsigned int           rcv_crc_32_err;
   unsigned int           rcv_len_err;
   unsigned int           rcv_aborted_pkt;
   unsigned int           rcv_cell_lost_congst;
   unsigned int           rcv_cell_lost_other;
   unsigned int           rcv_reassembly_timeout;
   unsigned int           rcv_pkt_too_long;

   unsigned int           rcv_crc_32_err_saved;
   unsigned int           rcv_len_err_saved;
   unsigned int           rcv_aborted_pkt_saved;
   unsigned int           rcv_cell_lost_congst_saved;
   unsigned int           rcv_cell_lost_other_saved;
   unsigned int           rcv_reassembly_timeout_saved;
   unsigned int           rcv_pkt_too_long_saved;

   BOOLEAN                flowmaster_capable;
   int                    lpa_sdh;
   int                    has_fm;                   // endpoint supp FLOWmaster
   UINT16                 esi_cnt;                // # of MAC addrs on board
   ETHER_ADDR             base_esi;              // hardware addr of device

   atm_vc_t               resync_vc;
   TIMER_BLK              timers[MAX_TIMERS];
  
   int                    dump;                     // sync for debug thread

   // These are at the bottom of the structure for easier viewing by the 
   //   debugger.

   VC_INFO                vc_info[LPA_MAXVC]; 
   LPA_DMA_HANDLE         dma_handle[MAX_DMA_HANDLE];
   LPA_XMT_PKT            xmt_pkts[LPA_NTXPKTS];     // array of xmit packets
   struct lpa_rcv_slot    rcvSlot[MET_RCV_SLOT_MAX]; // rcv slot

   unsigned long          rxvcfree[LPA_MAXVC / LPA_BPUL];
   unsigned long          txvcfree[LPA_MAXVC / LPA_BPUL];     

   } LPA_DATA;


/*+
 * ===============
 * = LPA_REG_SET =
 * ===============
 *
 * This macro writes the value to the specified register.
 *
 * P_SC       - (IN) Pointer to the NIC's software context.
 *
 * REG_OFFSET - (IN) The offset of the register to update.
 *
 * VALUE      - (IN) The 32 bit value to write to the register.
-*/

#define LPA_REG_SET(P_SC,REG_OFFSET,VALUE)                               \
   {                                                                     \
   io_handle_t  _csr;                                                    \
                                                                         \
   _csr = (io_handle_t) ((P_SC->devicebase) + (io_handle_t) REG_OFFSET); \
                                                                         \
   wbflush ();                                                           \
   WRITE_BUS_D32 (_csr, VALUE);                                          \
   wbflush ();                                                           \
   }                                                                     \

/*+
 * ===============
 * = LPA_REG_GET =
 * ===============
 *
 * This macro reads the value from the specified register.
 *
 * P_SC       - (IN) Pointer to the NIC's software context.
 *
 * REG_OFFSET - (IN) The offset of the register to update.
 *
 * P_VALUE    - (IN) Pointer to where to write the 32 bit value.
-*/

#define LPA_REG_GET(P_SC,REG_OFFSET,P_VALUE)                             \
   {                                                                     \
   io_handle_t  _csr;                                                    \
                                                                         \
   _csr = (io_handle_t) ((P_SC->devicebase) + (io_handle_t) REG_OFFSET); \
                                                                         \
   MB ();                                                                \
   *(P_VALUE) = READ_BUS_D32 (_csr);                                     \
   MB ();                                                                \
   }                                                                     \

// Function Prototypes ---------------------------------------------------------

/* Return a DMA address from a virtual address.   Must be called
   with softc lock held.  A struct lpa_dma_handle is prepended to the linked
   list whose head is "*phandle".   This struct should be freed by
   a subsequent call to lpa_dma_free.  */

unsigned long lpa_dma_alloc (caddr_t                  address, 
                             unsigned                 len,
                             struct _lpa_data        *od, 
                             struct _lpa_dma_handle **phandle);

/* Free DMA resources allocated by lpa_dma_alloc. Must be called
   with softc lock held.   The first "num" lpa_dma_handle structs
   on the linked list whose head is "*phandle" are freed and removed
   from the list.  If "num" is -1, or if "num" exceeds the number of
   entries in the list, all the entries in the list are freed and removed
   from the list. */

void lpa_dma_free (struct _lpa_data        *od,
	                struct _lpa_dma_handle **phandle, 
                   int                      num);

// (min vc) >= vc is allocated, or 0 on alloc. failure.
//   allocate and never free VC 0 at initialization time

unsigned lpa_allocvc (unsigned long      *bitmap, 
                      unsigned            vc);


// alloc. a xmit pkt descriptor, return its index, or 0 on alloc. failure

unsigned lpa_xmt_pkt_alloc (LPA_DATA *od);


// allocate a rcv slot and the associated mbuf 

short lpa_slot_alloc (LPA_DATA *p_sc, MET_SLOT_TYPE slot_type, int wait_flag);


// free a rcv slot 

void lpa_slot_free (LPA_DATA       *od, 
                    unsigned short  index);

void lpa_slot_flush (LPA_DATA *p_sc, MET_SLOT_TYPE slot_type);

void lpa_free_lists_destroy (LPA_DATA *p_sc);

// free an xmit pkt descriptor allocated by lpa_xmt_pkt_alloc.  It is illegal
//   to free descriptor 0 

void lpa_xmt_pkt_free (LPA_DATA *od, 
                       unsigned  index);

// free a VC

void lpa_freevc (unsigned long           *bitmap, 
                 unsigned                 vc);

// Initialize the lpa_data structure.  0 on success and -1 on failure.

int lpa_initialize (LPA_DATA *od);


// initialize the VC and descriptor free lists 

void lpa_free_lists_init (LPA_DATA *od);


// initialize the SUNI chip 

void lpa_initsuni (LPA_DATA *od);


// Sets schedule slot index to indicate the given vc

void lpa_setsched (LPA_DATA *od, 
                   unsigned  index, 
                   unsigned  vc);


// reset the device and reinitialize the VC and descriptor free lists.
//   The device is left in a state where it can send and receive packets.
//   txcells and noackcells are values passed to lpa_buildcelllists

int lpa_softreset (LPA_DATA *od);

STATUS lpa_fm_vc_open (HANDLE  drv_handle,
                       HANDLE  tm_an2_handle,
                       UINT32  fm_resync_vci,
                       HANDLE *p_tm_vc_handle);

void lpa_fm_vc_close (HANDLE drv_handle,
                      HANDLE tm_vc_handle);

void lpa_fm_vc_credits_set (HANDLE drv_handle,
                            UINT32 first_vc,
                            UINT32 last_vc,
                            UINT32 credits);

UINT32 lpa_fm_vc_stall (HANDLE drv_handle,
                        UINT32 first_vc,
                        UINT32 last_vc);

void lpa_fm_vc_restart (HANDLE drv_handle,
                        UINT32 first_vc,
                        UINT32 last_vc);

STATUS lpa_fm_vc_xmt (HANDLE  drv_handle,
                      UINT32  vc,
                      UINT8  *p_pkt,
                      UINT16  pkt_len);

STATUS lpa_rcv_buff_init (LPA_DATA *p_sc, int n, unsigned slot_type);


#endif	/* _IF_LPA_DEFS_H_ */
