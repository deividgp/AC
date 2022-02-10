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
 * @(#)$RCSfile: simport.h,v $ $Revision: 1.1.72.3 $ (DEC) $Date: 1998/05/11 15:25:11 $
 */
/* ----------------------------------------------------------
 * simport.h
 */
#ifndef _SIMPORT_INCL_
#define _SIMPORT_INCL_

#include <io/common/devdriver.h>

#define MAXCHAN	16
#define MAXTARG 16

#define STATISTIC_TIME  28800       /* time value (seconds) used to
                                       determine when spo_log_dma_errors 
				       should be called. Set to 8 hours */
#define SPO_KEEPALIVE_DEFAULT 8     /* time value (seconds) for the adapter
			               sanity keepalive algorithm. The actual
				       timeout value can double this default. */
#define SPO_ADAPTER_KEEPALIVE_DEFAULT 30
				    /* time value (seconds) that the adapter
				       uses as its default sanity time  */
/*
 * Forward structure declarations.
 */
struct simport_ws;
struct simport_softc;

/* 
 *  SIMport Data Structure Declaration
 */
typedef union {
        caddr_t ptr;
        U32 size[2];
} PTR;

/*
 *  SIMport Queue Carrier Declaration
 *  The Queue Carrier is the SIMport defined data structures used to
 *  form the interface queues between the host and the adapter.
 *  The Queue Carrier is used to pass queue buffers between the host and
 *  the adapter. It contains a link field which is used to form a
 *  one-way linked list. It contains a pointer to a queue buffer which
 *  must be formatted as a CAM or SIMport CCB command.  It also contains
 *  queue buffer and queue carrier token fields which are host virtual
 *  addresses. 
 */
typedef struct spqcar {        		/* SIMport carrier structure */
    volatile	PTR 	next;		/* Pointer to next queue carrier, physical */
    volatile	PTR 	bufp;		/* Queue buffer pointer, physical */
    volatile	PTR 	buftkn;		/* Queue buffer token, virtual */
    volatile	PTR 	cartkn;		/* Queue carrier token, virtual */ 
    U8	spo_func_code;		/* CAM or SIMport function code */
    U8	spo_status;		/* Stuatus of CAM or SIMport command */
    U16	spo_flags;		/* Flags for queue insert pri and status */
    U8	spo_rsvd;		/* CAM defined connect id, reserved */
    U8	spo_path_id;		/* CAM pathid, part of connection id */
    U8 	spo_target_id;		/* CAM target id, part of connection id */
    U8	spo_target_lun;		/* CAM lun id, part of connection id */
} SPQCAR;

/*
 * SIMport driver carrier meta structure definition.  The first 24 bytes
 * of the following structure are visible and used only by the driver.
 */

typedef struct simcar {
    struct simcar  *flink;	/* forward link				*/
    struct simcar  *blink;    	/* backward link			*/
    U32		   use_flag;	/* usage flag                   	*/
    U32		   spare;	/* spare longword for alignment 	*/
    sglist_t	   carr_sg;	/* DME struct for mapping the carrier	*/
    vm_offset_t	   carr_ba;	/* Phys address of the carrier		*/
    SPQCAR	   carrier;	/* SIMport defined carrier struct. 	*/
} SIMCAR;

/*
 * Define macro to get to carrier meta structure pointer from carrier
 * structure.
 */

#define SPO_SIMCAR_PTR(car_ptr) 	\
        (SIMCAR *)( ((U_WORD)(car_ptr)) - ((U_WORD)(sizeof(SIMCAR) - sizeof(SPQCAR))) )

#define SPO_FREECAR	0x0	/* usage flag, means the carrier is in 
				 * free pool
				 */
#define SPO_IN_USE	0x1	/* usage flag, the carrier is in use 	*/


#define spo_next_ptr	next.ptr
#define spo_buf_ptr 	bufp.ptr
#define spo_buf_token	buftkn.ptr
#define spo_car_token	cartkn.ptr

#define SPQ_STOPPER_ZERO	0x0
#define SPQ_STOPPER_ONE		0x1

#define SPQ_TAIL_INSERT		0x0	
#define SPQ_HEAD_INSERT		0x1	

typedef union spqptr {
    SPQCAR* ptr;	
    U32	size[2];
} SPQPTR;

/*
 *  SIMport Queue Header Declaration
 */
typedef struct spqhdr    {               /* N_PORT Queues */
    volatile SPQPTR hptr;                 /* Queue header pointer */
    volatile SPQPTR tptr;                 /* Queue tail pointer */
} SPQHDR;

#define spo_head_ptr	hptr.ptr
#define spo_tail_ptr	tptr.ptr


/* 
 *  SIMport Adapter Block 
 *
 *  The Adapter Block contains initialization parameters and the links for
 *  the SIMport interface queues between the adapter and the host.
 *  spo_qb_size is the number of bytes in a SIMport queue buffer.
 *  spo_ccb_ptr_sz is the number of bytes in a SIMport host pointer field.
 *  The SPQHDR structures contain the head and tail queue carrier
 *  addresses for the SIMport queues.
 */ 
typedef struct spab {
    U16	spo_qb_size;     /* Number of bytes in the queue buffer */
    U8	spo_ccb_ptr_sz;  /* Number of bytes allocated for a CCB pointer */ 
    U8	spo_pad[5];      /* Should be zero */
    U8	spo_pad2[8];     /* Should be zero */
    SPQHDR spo_dacqhd;	 /* Driver-Adapter command queue header */
    SPQHDR spo_adrqhd;	 /* Adapter-Driver response queue header */	
    SPQHDR spo_dafqhd;	 /* Driver-Adapter free queue header */
    SPQHDR spo_adfqhd;	 /* Adpater-Driver free queue header */
} SPAB;

/*
 * SIMport Buffer Segment Descriptor
 *
 * The BSD is a data structure used to contain the physical address
 * and size of a contiguous segment of host memory. The spo_type flag
 * indicates whether the format of the memory segment is that of a
 * host memory segment or of a SIMport Buffer Segment Map (BSM) . A
 * BSM is a list of BSDs and is used to address a host buffer that
 * consists of multiple host memory segments. The spo_bcount is the
 * number of bytes in the segment or in the BSM. The remaining fields
 * contain the host address bits of the memory segment or of the BSM.
 */
typedef struct spobsd
{
    U32	spo_type:2;		/* Buffer type */
    U32	spo_bufptr_lo:30;	/* Buffer pointer, lower 30 bits */
    U32	spo_bufptr_hi:16;	/* Buffer pointer, upper 16 bits */
    U32 spo_bcount:16;		/* Size in bytes of the buffer */
} SPOBSD;

#define SPO_BSD_TYPE	0	/* The BSD contains pointer to the host buf. */
#define SPO_BSM_TYPE	1	/* The BSD contains pointer to the BSMs */

/*
 *  SIMport Vendor Unique Commands and Messages
 */

/*
 * SIMport vendor unique function code definitions 
 */
#define	SPO_VU_SET_ADAP_STATE	0x80	/* Set Adapter State Command */
#define	SPO_VU_ADAP_STATE_SET	0x80	/* Adapter State Set Response Message */
#define	SPO_VU_SET_PARAM	0x81	/* Set Parameters Command */
#define	SPO_VU_PARAM_SET	0x81	/* Parameters Set Response Message */
#define	SPO_VU_SET_CHAN_STATE	0x82	/* Set Channel State Command */
#define	SPO_VU_CHAN_STATE_SET	0x82	/* Channel State Set Response Message */
#define SPO_VU_SET_DEV_STATE	0x83	/* Set Device State Command */
#define SPO_VU_DEV_STATE_SET	0x83	/* Device State Set Response Message */ 
#define SPO_VU_VERI_ADAP_SANITY	0x84	/* Verify Adapter Sanity Command */ 
#define SPO_VU_ADAP_SANITY_VERI	0x84	/* Adapter Sanity Verify Response */ 
#define SPO_VU_READ_CNTRS 	0x85	/* Read Counters Command */
#define SPO_VU_CNTRS_READ 	0x85	/* Counters Read Response Message */
#define SPO_VU_BSD_RSPN_CMD	0x86	/* BSD Response Command */
#define SPO_VU_BSD_REQUEST	0x86	/* BSD Requeset Message */
#define SPO_VU_BUS_RESET_CMD	0x87	/* Bus Reset Response Command */ 
#define SPO_VU_BUS_RESET_REQ	0x87	/* Bus Reset Request Message */ 
#define SPO_VU_UNSOL_RESEL	0x88	/* Unsolicited Reselection Message */
#define SPO_VU_CHAN_DISABLED	0x89	/* Channel Disabled Message */
#define SPO_VU_DEV_DISABLED	0x8a	/* Device Disabled Message */ 
#define SPO_VU_TARGET_EVENT	0x8b	/* Target Event Message */
#define SPO_VU_TARG_EVENT_ACK   0x8b    /* Enable accepts.  Sent after 
					 * "state set" msg is received
					 * or after a BR has been acked */
#define SPO_VU_SET_TARGET_STATE 0x8c	/* Set Target State Command */
#define SPO_VU_TARGET_STATE_SET 0x8c	/* Target State Set Message */
#define SPO_VU_CRASH_RECOV_CMPLT 0x8e   /* Used to inform the adapter that
					 * the driver has completed
					 * recovering from an adapter crash */
#define SPO_VU_CRASH_RECOV_CMPLT_RSPN 0x8e

/* 
 * Set Adapter State Command 
 */
typedef struct ccb_spvu_set_adpt
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8	spo_state;	/* The request state */
    U8  spo_pad1;
    U16 spo_flags;	/* Defined below */
    U8	spo_pad2[4];	/* Should be zero */
} CCB_SPVU_SET_ADPT;

/*
 * Adapter State Set Response Message 
 */
typedef struct ccb_spvu_state_set
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8	spo_state;	/* Adapter state */
    U8	spo_n_host_sg;  /* The number of host 4K segments memory */
    U16	spo_flags;	/* Supported features */
    U16	spo_n_adapt_qc;	/* Maximum number of queued comands */
    U8	spo_ka_time;	/* Minimum time in seconds for KEEPALIVE */
    U8	spo_n_freeq;	/* Minimum number of free queue entries */
    U8	spo_n_chan;	/* The number of SCSI channels */
    U8	spo_xfer_align;	/* Adapter alignment information */
    U8	spo_n_sac;	/* Recommended number of SAC buffers */
    U8	spo_pad[5];
    U8 	spo_nodes_on_chan[MAXCHAN]; /* Maximum number of nodes each channel */
} CCB_SPVU_STATE_SET;


/*
 *  SIMport state set value 
 */
#define SPO_STATE_ENABLED	1
#define SPO_STATE_DISABLED	2


/* word count */
#define	SPO_XFER_ALIGN_BYTE	0 
#define	SPO_XFER_ALIGN_WORD	1 
#define	SPO_XFER_ALIGN_LONGWORD	2 
#define	SPO_XFER_ALIGN_QUADWORD	3 
#define	SPO_XFER_ALIGN_OCTAWORD	4 

/*
 * Adapter State Set Command and Response Message flags field definition.
 */
#define SPO_INTR_HOLDOFF	0x01  /* Support the intr. holdoff timer */
#define SPO_SOFT_SETTING	0x02  /* Supp. the soft setting of SCSI node */
#define SPO_LINKED_BSM		0x04  /* Support the linked BSMs */
#define SPO_BSD_REQUEST		0x08  /* Support BSD Request unsolicited */
#define SPO_SET_CRASH_RECOV 	0x10  /* The adapter has been started in
					 crash recovery mode */

#define SPO_WORD_MASK		0x01
#define SPO_LWORD_MASK		0x03
#define SPO_QWORD_MASK		0x07
#define SPO_OWORD_MASK		0x0f

/* 
 * Set Parameters Command 
 */
typedef struct ccb_spvu_set_param
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8  spo_pad;         	/* Should be zero */
    U8	spo_n_host_sg;		/* Host 4K segments allocated for adapter */
    U16 spo_flags;          	/* Flags controlling adapter operation */ 
    U32	spo_system_time;	/* system time */
    U32	spo_int_holdoff;	/* Completion interrupt holdoff timer control */
    U32	spo_rp_timer;		/* The reset pending timer */
    SPOBSD  spo_host_sg_bsd;	/* Buffer segment descriptor allocated */
} CCB_SPVU_SET_PARAM;

/*
 * Set Parameters Command flags fields definition.
 */
#define SPO_ENABLE_CNTRS	0x0001	/* Enabled adapter counters */

/*
 * Paramters Set Response Message 
 */
typedef struct ccb_spvu_param_set
{
    CCB_HEADER  spo_cam_ch;         /* Header information fields */
} CCB_SPVU_PARAM_SET;

/* 
 * Set Channel State Command 
 */
typedef struct ccb_spvu_set_chnl
{
    CCB_HEADER  spo_cam_ch; /* Header information fields */
    U8      spo_state;      /* The request state */
    U8      spo_pad[3];     /* Should be zero */
    U8	    spo_chan_id;    /* Channel id */
    U8	    spo_node_id;    /* SCSI bus node id */
    U8      spo_pad2[2];    /* Should be zero */
} CCB_SPVU_SET_CHNL;

/*
 * Channel State Set Response Message
 */
typedef struct ccb_spvu_chnl_set
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8  spo_state;      /* The current state */
    U8  spo_pad[3];     /* Should be zero */
    U8	spo_chan_id;	/* Channel id */
    U8	spo_node_id;	/* Assigned SCSI bus node id */
    U8	spo_pad2[2];	/* Should be zero */
} CCB_SPVU_CHNL_SET;

/*
 * Set Device State Command 
 */
typedef struct ccb_spvu_set_device
{
    CCB_HEADER  spo_cam_ch;        /* Header information fields */
    U8      spo_state;         /* The request state */
    U8      spo_pad[7];        /* Should be zero */
} CCB_SPVU_SET_DEVICE;

/*
 * Device State Set Response Message 
 */
typedef struct ccb_spvu_device_set
{
    CCB_HEADER  spo_cam_ch;         /* Header information fields */
    U8	spo_state;          /* The current state */
    U8	spo_pad[7];	    /* Should be zero */
} CCB_SPVU_DEVICE_SET;

/*
 * Verify Adapter Sanity Command
 */
typedef struct ccb_spvu_ver_adap_sanity
{   CCB_HEADER  spo_cam_ch;     /* Header information fields */
} CCB_SPVU_VER_ADAP_SANITY;

/*
 * Verify Adapter Sanity Response
 */
typedef struct ccb_spvu_adap_sanity_rspn
{   CCB_HEADER  spo_cam_ch;     /* Header information fields */
} CCB_SPVU_ADAP_SANITY_RSPN;

/*
 * Read Conuters Command 
 */
typedef struct ccb_spvu_read_cntr
{   
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8      spo_pad[2];         /* Should be zero */
    U16      spo_flags;         /* Flags controlling adapter operation */
    U8      spo_pad2[4];        /* Should be zero */
} CCB_SPVU_READ_CNTR;

/*
 * Counters Read Response Message
 */
typedef struct ccb_spvu_cntr_read_rspn 
{
    CCB_HEADER  spo_cam_ch;         /* Header information fields */
    U8      	spo_pad[4];	    /* Should be zero */
    U32		spo_cntrs[41];	    /* SIMport counters */ 
} CCB_SPVU_CNTR_RSPN;

/* 
 * BSD Request Message
 */
typedef struct ccb_spvu_bsd_req
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8	spo_buf_id;	/* The buffer within the private data of ccb */
    U8	spo_pad[3];	/* Should be zero */
    U32	spo_offset;	/* The byte offset from the start of the buffer */
    PTR	CCB_VA;		/* Host virtual address of the CCB */ 
} CCB_SPVU_BSD_REQ;

#define spo_ccb_va	CCB_VA.ptr

#define SPO_BUFID_DATA		1
#define SPO_BUFID_CDB		2
#define SPO_BUFID_SENSE		3
#define SPO_BUFID_MESSAGE	4

/*
 * BSD Response Command 
 */

#define SPO_BSD_RSPN_ENTRY	12


typedef struct ccb_spvu_bsd_rspn
{   
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8      spo_buf_id;         /* The buffer field with the command */ 
    U8      spo_pad[3];        	/* Should be zero */
    U32	    spo_offset;		/* Offset from the start of the data buf */
    PTR	    CCB_VA;		/* Host virtual address of the I/O CCB */
    SPOBSD  spo_bsd[SPO_BSD_RSPN_ENTRY];  /* Buffer segment Descriptor */
} CCB_SPVU_BSD_RSPN;

/*
 * Bus Reset Request Message 
 */
typedef struct ccb_spvu_bus_reset_req
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U8	spo_reason;		/* Reason code for reset request */
    U8	spo_tgtid;		/* Target ID */
    U8  spo_pad[6];		/* Should be zero */
    PTR	CCB_VA;			/* The virtual address of the CCB active */
} CCB_SPVU_BUS_RESET_REQ;

/*
 * Bus Reset Response Command
 */
typedef struct ccb_spvu_bus_reset
{
    CCB_HEADER  spo_cam_ch;         /* Header information fields */
} CCB_SPVU_BUS_RESET;

/*
 * Device Disable Message
 */
typedef struct ccb_dev_disable
{
    CCB_HEADER  spo_cam_ch;         /* Header information fields */
} CCB_DEV_DISABLE;

/*
 * Adapter Crash Recovery Completed Command and Response
 */
typedef struct ccb_spvu_crash_recov_cmplt
{
    CCB_HEADER spo_cam_ch;     /* Header information fields */
    U16  spo_pad1;
    U16  spo_flags;		/* defined below */
    U8   spo_pad2[4];
} CCB_SPVU_CRASH_RECOV_CMPLT;
typedef CCB_SPVU_CRASH_RECOV_CMPLT CCB_SPVU_CRASH_RECOV_CMPLT_RSPN;

/*
 * Defines for Adapter Crash Recovery Completed Command and Response.
 */
#define SPO_RECOV_TARGET_MODE	0x1  /* The crash recovery operations
				      * for target mode functionality
				      * have been completed. */

/*
 * Target Event Message
 */
typedef struct ccb_spvu_target_event
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U16 spo_seq_id;	/* Sequence number for this event */
    U8  spo_init_id;	/* SCSI id of the initiator of the event */
    U8  spo_tag_id;	/* Queue Tag ID if there is one */
    U8	spo_flags;	/* Defined below */
    U8  spo_sense_len;	/* Number of bytes of sense data returned */
    U16 spo_rsvd1;
    U8  spo_msg_code;	/* SCSI message code */
    U8  spo_msg_args[7];/* Any data pertinent to the message code, in the
			 * format documented in the CAM specification. */
    U8  spo_sense_buf[32];/* Any sense data available from the event.
			   * This is the actual buffer that is used to pass
			   * the sense data. */
} CCB_SPVU_TARGET_EVENT;

/*
 * Set Target State Command
 */
typedef struct ccb_spvu_set_target_state
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U16 spo_seq_id;	/* Sequence number of the Target Event Message
			 * that this command is a response to. */
    U8  spo_init_id;	/* The initiator ID from the Target Event Message */
    U8  spo_tag_id;	/* The queue tag ID from the Target Event Message */
    U8	spo_flags;	/* Defined below */
    U8  spo_rsvd[3];
} CCB_SPVU_SET_TARGET_STATE;

/*
 * Target State Set Message
 */
typedef struct ccb_spvu_target_state_set
{
    CCB_HEADER  spo_cam_ch;     /* Header information fields */
    U16 spo_seq_id;	/* Sequence number of the Target Event Message
			 * that this command is a response to. */
    U8  spo_init_id;	/* The initiator ID from the Target Event Message */
    U8  spo_tag_id;	/* The queue tag ID from the Target Event Message */
    U8	spo_flags;	/* Defined below */
    U8  spo_rsvd[3];
} CCB_SPVU_TARGET_STATE_SET;

/*
 * Define for "spo_flags" for CCB_SPVU_TARGET_EVENT,
 * CCB_SPVU_SET_TARGET_STATE, and CCB_SPVU_TARGET_STATE_SET.
 */
#define SPO_TAG_ID_VALID     1
#define SPO_CLEAR_ALL_EVENTS 2

/* 
 * SIMport Returned Status Codes, see SIMport spec. Table A-3
 */
#define SPO_SUCCESS	     1
#define SPO_INV_COMMAND	     0
#define SPO_NOT_ENABLED	    -1	/* The adapter/channel/function is not enable */
#define SPO_NOT_DISABLED    -2  /* The adapter/channel/func is not disable */
#define SPO_HOST_MEM	    -3	/* Required n_host_sg number of 4K page */
#define SPO_HOST_FQE	    -4	/* No free queue element */
#define SPO_INV_INT_HOLDOFF -5  /* Interrupt Holdoff timer invalid/not supp. */
#define SPO_HOST_SG	    -6  /* Insuff. host memory allocated */
#define SPO_INV_CHANID	    -7	/* Invalid channel ID or non-exist channel */
#define SPO_INV_NODEID	    -8	/* Invalid node ID or soft setting not supp. */
#define SPO_CANT_DISABLE    -9	/* A device channel cannot be disabled */
#define SPO_INV_OFFSET	    -10	/* Invalid offset value/offset out of range */ 
#define SPO_INV_CCB	    -11	/* Invalid CCB address */
#define SPO_INV_BUF_ID	    -12	/* Invalid buf_id field value */
#define SPO_NO_RESET	    -13	/* Adapter should not reset the SCSI bus */

#define SPO_BUS_RESET	     2 /* Bus reset detected on the SCSI bus */
#define SPO_RESET_REJECT     3 /* Host denied the Adap's reset request */
#define SPO_BUS_DEV_RST	     4 /* bus Device Reset */
#define SPO_CHANN_HW_ERR     5 /* A hardware error has been detected */ 

#define SPOZONESIZE	4
#define NBSDSEGPBSM	17	/* Number of BSDs in the BSD segments */

/*
 * SIMport Buffer Segment Map
 *
 * The BSM is used to define a physically discontiguous host memory
 * buffer. The next_bsm_bsd field is a link to the next BSM, if
 * required. The num_entries field is a count of the number of valid
 * BSDs in the bsdseg. The Total_bytes field contains the total byte
 * count that this BSM maps. The buffer_offset field contains the
 * buffer offset from the start of the buffer that this BSM maps.  The
 * bsdseg field contains a BSD data structure for each physically
 * contiguous host memory segment.
 * The BSM is required to be quadword aligned.  
 */
typedef struct spobsm
{
   SPOBSD next_bsm_bsd;
   U16    num_entries;
   U8 	  pad[6];
   U32	  total_bytes;	    /* Total number of bytes mapped by this BSM */
   U32	  buffer_offset;    /* Byte offset from the start of the host buffer */
   SPOBSD bsdseg[NBSDSEGPBSM]; /* BSD entries */
} SPOBSM;

/*
 * SIMport driver BSM meta structure definition.  The first 56 bytes of
 * the following structure are visible and used only by the driver.
 */

typedef struct simbsm {
   struct simbsm  *flink;	/* forward link				*/
   struct simbsm  *blink;      	/* backward link			*/
   U32	  	  use_flag;	/* usage flag for zone A and B	     	*/
   U16		  zone_a_count;	/* number of bytes in zone A temp. buffer */
   U16		  zone_b_count;	/* number of bytes in zone B temp. buffer */
   void		  *src_dest_a;	/* virtual address of the beginning unaligned
				 * area of the user data buffer segment, the
				 * driver copies data to/from this location
				 * from/to the zone A temporary buffer area 
				 */
   void		  *src_dest_b;	/* virtual address of the ending unaligned
				 * area of the user data buffer segment
				 */
   U64		  zone_a;	/* temporary buffer space to transfer data
				 * for beginning unaligned data segment
				 */
   U64		  zone_b;	/* temporary buffer space to transfer data
				 * for ending unaligned data segment
				 */

   sglist_t	  bsm_sg;	/* DME struct for mapping the SPOBSM */
   vm_offset_t	  bsm_ba;	/* Phys address of the SPOBSM */

   SPOBSM	  bsm;		/* SIMport defined BSM struct.		*/

} SIMBSM;


#define SPO_ZONE_A	0x01	/* Zone A buffer is used 	*/
#define SPO_ZONE_B	0x02	/* Zone B buffer is used 	*/

/*
 * Define macro to get to BSM meta structure pointer from BSM
 * structure.
 */

#define SPO_SIMBSM_PTR(bsm_ptr)		\
        (SIMBSM *)( ((U_WORD)(bsm_ptr)) - ((U_WORD)(sizeof(SIMBSM) - sizeof(SPOBSM))) )


#define spo_bsm_bsd 	bsm.next_bsm_bsd 
#define spo_bsm_entry 	bsm.num_entries
#define spo_bsm_bytes	bsm.total_bytes
#define spo_bsm_offset	bsm.buffer_offset
#define spo_bsm_bsdseg	bsm.bsdseg

/*
 *  SIMport Private Data Area of Execute SCSI I/O CCB 
 */
typedef struct ccb_spvu_scsiio_priv 
{
    U8	spo_scsi_status;
    U8 	spo_sen_res;
    U8	pad[2];
    U32		spo_data_res;
    SPOBSD	spo_data_bsd[2];
    SPOBSD	spo_cdb_bsd;
    SPOBSD	spo_sen_bsd;
    SPOBSD	spo_msg_bsd;
    PTR		spo_ccb_next_ptr;  /* physical address of next CCB if link */
} CCB_SPVU_SCSIIO_PRIV;

/*
 *  SIMport Private Data Area of Accept Target I/O CCB 
 */
typedef struct ccb_spvu_accept_priv 
{
    U8	spo_scsi_status;
    U8 	spo_sen_res;
    U8  spo_cdb_len;
    U8	spo_sen_len;
    U32 rsvd2;
    U64 rsvd3;
    U64 rsvd4;
    SPOBSD spo_cdb_bsd;
    SPOBSD spo_sen_bsd;
    U32 spo_cmd_tmo;
    U8  spo_tag_q_action;
    U8  spo_tag_id;
    U8  spo_init_id;
    U8  rsvd5;
    U64 rsvd6;
} CCB_SPVU_ACCEPT_PRIV;

/*
 * SIMport Private Data Area of Enable LUN CCB
 */
typedef struct ccb_spvu_enable_lun_priv
{
    char rsvd1;
    char rsvd2;
    char rsvd3;
    char rsvd4;
    char *hptr; /* Queue header pointer */
    char *tptr; /* Queue tail pointer */
} CCB_SPVU_ENABLE_LUN_PRIV;

/*
 *  SIMport Buffer Segment Descriptor Manupilation Routine
 *  The design is to accomadate both 32 and 64 bits architecture.
 */
#define SPO_SETUP_BSD(bsdp, addr, len, align, t)		\
{								\
    (bsdp)->spo_type = (t);					\
    (bsdp)->spo_bufptr_lo = (((addr) & 0xffffffff) >> (align)) & 0x3fffffff;	\
    (bsdp)->spo_bufptr_hi = (((addr) & 0xffffffff) >> ((align)+30)) & 0xffff;	\
    (bsdp)->spo_bcount = (len);					\
}

/*
 * Alpha dense address definition
 */
#ifdef __alpha
#ifndef DENSE
#define DENSE(x)       ((x) - 0x10000000)
#endif
#endif


/*
 *  SIMport Adapter Registers
 */
/*
 *      SIMport Registers Definitions
 */
/*
 * This definition intends to make the compiler that does not support
 * long long happy.
 */

typedef struct regbits {
#ifdef __alpha
    volatile U64 paddr;
#else
    volatile U32 paddr;
    U32 pad;
#endif
} REGBITS;


/*  
 *  SIMport Adapter Status Register Bit Fields Definitions
 *  The ASR register is a 64 bit register.  Currently SIMport
 *  does not define bits 32-63.
 *  Bits 10-30 are Should be Zero fields.
 */
#define SPO_ASR_0	0x00000001	/* Should be Zero */
#define SPO_ASR_1	0x00000002	/* Should be Zero */
#define SPO_ASR_ADSE	0x00000004  	/* Adapter Data Struture Error */
#define SPO_ASR_AMSE	0x00000008	/* Adapter Memory System Error */
#define SPO_ASR_AAC	0x00000010  	/* Adapter Abnormal Condition */ 
#define SPO_ASR_5	0x00000020	/* Should be Zero */
#define SPO_ASR_6	0x00000040	/* Should be Zero */
#define SPO_ASR_7	0x00000080	/* Should be Zero */
#define SPO_ASR_ASIC	0x00000100	/* Adapter Completion Interrupt Request */
#define SPO_ASR_UNIN	0x00000200	/* Unitialized State */
#define SPO_ASR_AME	0x00008000  	/* Adapter Maintenance Error */

/*
 * Error log registers for the KZPSA and KZTSA.
 */
typedef struct spo_err_log_regs {
    U32 err_log_1;
    U32 err_log_2;
    U32 err_log_3;
    U32 err_log_4;
    U32 err_log_5;
    U32 err_log_6;
    U32 err_log_7;
    U32 err_log_8;
    U32 err_log_9;
    U32 err_log_a;
} SPO_ERR_LOG_REGS;

/*
 * Structure used to log the registers of the KZPSA and KZTSA.
 * This includes logging the error log registers.
 */
typedef struct spo_log_regs {
#define SPO_LOG_REGS_VERS 1
    U64 asr_reg;
    U64 afar_reg;
    U64 afpr_reg;
    SPO_ERR_LOG_REGS err_log_regs;
} SPO_LOG_REGS;



#define SPO_4KSEG	4096
#define SPO_BSD_MAXLEN	(65536 - DME_PAGE_SIZE)   /* The maximum length for a BSD */

/*
 *  The following macros will redefine the host specific routines
 *  in the fields of sim_softc structure.  The operation overload
 *  has to be examined closely to guarantee there is no one use
 *  there fields except simport modules.
 */


#define spo_hba_ioccb_setup 	hba_xfer_info
#define spo_hba_adap_reset      hba_msgout_pend

/* 
 * SIMport Registers
 */                                           
#define SPO_AMCSR	0
#define SPO_ABBR	1
#define SPO_DACQIR	2
#define SPO_DAFQIR	3
#define SPO_ASR		4
#define SPO_AFAR	5
#define SPO_AFPR	6
#define SPO_RESET_START 7
#define SPO_CLR_INTR	8
#define SPO_ASRCR	8	/* Adapter Status Release Control Register */

/* 
 *  Adapter Maintenance Control and Status Register - AMCSR
 */
#define	AMCSR_MIN	0x01	/* Maintenance Initialize */
#define	AMCSR_IE	0x08	/* Interrupt Enable */
#define AMCSR_ARC	0x10	/* Adapter Release Control Register Present.
				 * When set, the adapter implements the ASRCR.
				 * This bit is read-only to the host.
				 */
#define AMCSR_HRC	0x20	/* Host Release Control.  Read/write by the
				 * host.  When set, indicates that the host
				 * wishes to use the ASR as an indication
				 * of pending adapter interrupts.
				 */

/*
 *  SIMport PATHINQ Record Data Structure.  This declaration should be
 *  exactly identical to the CCB_PATHINQ except without the CCB_HEADER.
 */
typedef struct spo_pathinq_rec {
    U8 cam_version_num;             /* Version number for the SIM/HBA */
    U8 cam_hba_inquiry;             /* Mimic of INQ byte 7 for the HBA */
    U8 cam_target_sprt;             /* Flags for target mode support */
    U8 cam_hba_misc;                /* Misc HBA feature flags */
    U16 cam_hba_eng_cnt;            /* HBA engine count */
    U8 cam_vuhba_flags[ VUHBA ];    /* Vendor unique capabilities */
    U32 cam_sim_priv;               /* Size of SIM private data area */
    U32 cam_async_flags;            /* Event cap. for Async Callback */
    U8 cam_hpath_id;                /* Highest path ID in the subsystem */
    U8 cam_initiator_id;            /* ID of the HBA on the SCSI bus */
    U8 cam_prsvd0;                  /* Reserved field, for alignment */
    U8 cam_prsvd1;                  /* Reserved field, for alignment */
    char cam_sim_vid[ SIM_ID ];     /* Vendor ID of the SIM */
    char cam_hba_vid[ HBA_ID ];     /* Vendor ID of the HBA */
    U8 *cam_osd_usage;              /* Ptr for the OSD specific area */
} SPO_PATHINQ_REC;

/*
 * structure for the I/O completion wait queues
 */
typedef struct spo_waitq {
    struct simcar	*waitq_head;
    struct simcar	*waitq_tail;
    simple_lock_data_t	waitq_lock;	/* lock for the queue 		*/
} SPO_WAITQ;

/*
 * SIMport Resource Wait Queue data structure definition
 */
typedef struct spo_resource_queue {
    struct simport_ws	*qhead;		/* resource wait queue head	*/
    struct simport_ws	*qtail;		/* resource wait queue tail	*/
    simple_lock_data_t	qlock;		/* resource queue lock		*/

} SPO_RESOURCE_QUEUE;
   
typedef struct simport_htl_nexus {
#define SIMPORT_HTL_NEXUS_VERS 2

     /*
      * targ_event_head and tail keep track to the FIFO of TARGET EVENT
      * MESSAGES which have not been processed because no IMMEDIATE
      * NOTIFY CCBs were available.  These must be the first two fields
      * of the SIMPORT_HTL_NEXUS struct.
      */
     SIMCAR *targ_event_head;
     SIMCAR *targ_event_tail;
     SIMCAR *targ_event_waiting_carriers;

     /*
      * Accept_recovery_list is used to maintain the
      * list of accept CCBs which will be issued to the adapter
      * when an enable LUN is performed during adapter crash
      * recovery.
      */
     struct simport_ws *accept_recovery_list;

     /*
      * Copy of the Enable LUN CCB.  This information will be
      * used during error recovery.  Re_enable_lun is used to
      * store the CCB which is used to re-enable a LUN.
      */
     CCB_ENABLE_LUN ccb_enable_lun;
     CCB_ENABLE_LUN *re_enable_lun;

     /*
      * This are single-linked list
      */
     struct simport_ws *immed_notify_free; /* This is the list of available
					    * immediate notify CCBs. */
     struct simport_ws *immed_notify_used;

     struct simport_softc *spo_sc;         /* Pointer to SIMPORT_SOFTC */

     U32 lun;				   /* LUN Nexus is associated to */

     U32 flags;
#define SPO_HTM_ENABLED       	0x001
#define BDR_IN_PROGRESS		0x004
#define BUS_RESET_IN_PROGRESS	0x008
#define DISABLE_IN_PROGRESS	0x010
#define ENABLE_IN_PROGRESS	0x020
#define CRASH_RECOV_IN_PROGRESS	0x040	/* Crash recovery - need to send the
					 * enable LUN */
#define CRASH_RECOV_COMPLETED	0x080   /* Crash recovery - waiting for 
					 * enable LUN response */

    simple_lock_data_t	htl_lock;	/* resource list lock */

} SIMPORT_HTL_NEXUS;

/*
 * Structure to hold pending BDR info when the driver doesn't
 * get a response from the adapter.
 *
 * flag - indicates that there's a BDR in progress
 * spo_softc - indicates which adapter to issue BR should we need
 * to
 */
typedef struct spo_bdr_info {
    U8                          flag;
    U8                          spo_pad[7];
    struct simport_softc        *spo_softc;
} SPO_BDR_INFO;

/* 
 *  SIMport specific softc structure
 *
 *  NOTE:  When we implement multi-channel adapter drivers, we need to
 *	   revisit this structure for modification.
 */
typedef struct simport_softc {

#define SIMPORT_SOFTC_VERS	 4 

    SPAB*    		spo_abp;	/* Pointer to SPAB */
    U32			spo_state;	/* Adapter state */
    U32			spo_flags;	/* Supported features */
    U16			spo_n_adapt_qc;	/* Maximum number of queued comands */
    U8		spo_n_chan;		/* Number of SCSI channel */
    U8		spo_ka_time;		/* Minimum time in seconds for KEEPALIVE */
    U8		spo_n_freeq;		/* Minimum number of free queue entries */
    U8		spo_n_host_sg;		/* The number of host 4K segments memory */
    U8		spo_xfer_align;		/* Adapter minimum data alignment  */
    U8		spo_n_sac;		/* Recommended number of SAC buffers */
    
    U8  spo_nodes_on_chan[MAXCHAN];	/* Maximum number of nodes each channel */
    U32		spo_chan_id;		/* Channel ID of this channel */    
    U32		spo_int_holdoff;	/* Interrupt holdoff timer */
    char	*spo_adap_mem;		/* Pointer to memory space for adapter */
    sglist_t	spo_abp_sg;		/* DME struct for mapping spo_abp */
    vm_offset_t	spo_abp_ba;		/* Phys address of spo_abp */
    
    U32		(*spo_reg_intr)();	/* Will register interrupt handler */
    U32		(*spo_hba_pathinq)();	/* HW dependent pathinq routine */
    U64		(*spo_read_reg)();	/* Read a SIMport register */ 
    void	(*spo_write_reg)();	/* Write a SIMport register */
    void	(*spo_read_log_regs)(); /* Read the error log registers */    

    SPO_PATHINQ_REC	spo_pathinq_rec;/* Store the returned pathinq info */
    U32			spo_max_cdb_len;/* Max. CDB length supported */
    SIM_SOFTC		*spo_sim_softc;	/* Pointer to the SIM SOFTC structure */
    SPO_WAITQ		spo_adap_waitq;	/* Outstanding carriers/CCBs for the adapter */

    CCB_HEADER		*spo_adap_sanity_ccb; /* verify adapter sanity CCB */
    CCB_HEADER		*spo_adap_ccb;	/* CCB used for adapter reset */
    U32			spo_delay_cnt;	/* # of 100 milliseconds since MIN bit set */
    
    SIMPORT_HTL_NEXUS **spo_htl_nexus;  /* Pointer to LUN based array of
					 * of SIMPORT Host-Target-LUN pointers.
					 */
    U32			spo_crash_lun_cnt; /* Number of LUN's which are in
					 * crash recovery. */

    SIM_POOL_CTRL	*car_pool;	/* Pool structure for carriers */
    SIM_POOL_CTRL	*bsm_pool;	/* Pool structure for BSMs */
    SPO_RESOURCE_QUEUE	spo_resource_q;	/* Resource wait queue */
    SPO_BDR_INFO        pending_bdr[MAXTARG];
					/* Pending BDR structure per target */
    simple_lock_data_t	spo_dacqlk;	/* Driver-Adapter command queue lock*/
    simple_lock_data_t	spo_dafqlk;	/* Driver-Adapter free queue lock */
    simple_lock_data_t	spo_adrqlk;	/* Adapter-Driver response queue lock*/
    simple_lock_data_t	spo_adfqlk;	/* Adapter-Driver free queue lock */
    simple_lock_data_t	spo_genericlk;  /* Generic lock, for other fields */ 

    U32       dma_mapping_errors;       /* Number of mapping failures 
					   since last information msg */ 
    U16       log_dma_errors;           /* True if a dma error has occurred */
    U16       resource_q_timing;        /* True if process_resource_q timer
					   is running. */
} SIMPORT_SOFTC;

/*
 * SIMport Adater State 
 */
#define SPO_UNIN_STATE		0x00000001	/* UNIN state */
#define SPO_INIT_STATE		0x00000002	/* INIT state */
#define SPO_ENABLED_STATE	0x00000004	/* ENABLED state */
#define SPO_RESET_IN_PROGRESS	0x00000008	/* Adapter reset in progress
						 * state */
#define SPO_MISC_ERROR		0x00000010	/* Misc error state */
#define SPO_HARD_RESET_DONE	0x00000020	/* Hard reset has been
						 * performed */
#define SPO_THREADS		0x00000040	/* SIMport thread started */
#define SPO_POLL_MODE		0x00000080	/* Polling mode */
#define SPO_VERI_SANITY		0x00000100	/* Verify adap sanity state */
#define SPO_PATHINQ_VALID	0x00000200	/* Path inquiry information
						 * is valid */ 
#define SPO_ADAP_DEAD		0x00000400	/* Adapter is dead */
#define SPO_MIN_BIT_SET		0x00000800	/* MIN bit was set in ASR
						 * register */
#define SPO_BUS_RESET_NEEDED	0x00001000	/* SCSI bus reset is needed
						 * in progress */
#define SPO_SHARED_INTR		0x00002000	/* The adapter supports shared
						 * interrupts */
#define SPO_DEVICE_FOUND	0x00004000	/* Devices found on this 
						 * adapter */
#define SPO_BUS_RESET_IN_PROG   0x00008000      /* SCSI Bus reset in 
						 * progress */
/*
 * SIMport SIM_WS overlay data structure definition
 * The current assumption is that SIM_WS is 568-byte long and is a part
 * of the DEC_CAM_PKT.  This means that for each CCB allocated, there is
 * a corresponding SIM_WS space.  Since almost all the fields in the SIM_WS
 * are not needed by the SIMport drivers, we define an overlay structure
 * for the SIMport driver's usage.
 */

#define SPO_SIM_WS_MINSIZE	568	/* minumum assumed SIM_WS size	*/

typedef struct simport_ws {

#define SIMPORT_WS_VERS 1

    struct simport_ws	*flink;		/* forward link			*/
    struct simport_ws	*blink;		/* backward link		*/
    SIMBSM		sim_bsm;	/* SIMport driver's meta BSM	*/

    SIMBSM		*as_bsm;	/* Autosense BSM pointer	*/
    
    SIMPORT_SOFTC       *simport_softc; /* pointer to the adapter specific
					 * softc structure
				         */
    void		*dma_cdb_sglistp; /* DMA resource sglistp pointer for
					 * the CDB buffer in a CDB pointer was
					 * used.
					 */
    void 		*dma_sglistp;	/* First DMA resource sglistp pointer
					 * for this I/O request
					 */

    void		*dma_as_sglistp;/* DMA resourge sglistp pointer for
					 * the autosense buffer
					 */
    
    sglist_t	   	ccb_sg;		/* DME struct for mapping the CCB */
    vm_offset_t	   	ccb_ba;		/* Phys address of the CCB */

} SIMPORT_WS;


/*
 * SPO_SCHED_ISR
 * SIMport interrupt service kernel thread.
 */
#define SPO_SCHED_ISR(sc)  				\
{							\
    if((sc)->simh_init == CAM_TRUE) 			\
	thread_wakeup_one((sc));			\
}

/*
 * SPO_CCB_ALLOC
 * Allocates a CCB.  This is the SIMport interface to xpt_ccb_alloc
 * routine.  Once we allocate a CCB, we also clear the SIMPORT_WS
 * area since we overlay the SIM_WS area which has some fields (such
 * as CCB ptr) filled in by the CCB allocation routine which causes
 * corruption problem if we don't clear the area.
 */
#define	SPO_CCB_ALLOC(ccbp)						\
{									\
    (ccbp) = (CCB_HEADER *)xpt_ccb_alloc();				\
    if ((ccbp) != (CCB_HEADER *)NULL)                           	\
        bzero ((SIMPORT_WS *)SC_GET_WS(ccbp), sizeof(SIMPORT_WS));	\
}

/*
 * SPO_CCB_DEALLOC
 * Deallocates a CCB.  This is the SIMport interface to xpt_ccb_free
 * routine.
 *
 * Arguments:
 *	Pointer to the CCB_HEADER structure.	
 *
 */
#define SPO_CCB_DEALLOC(ccbp) (xpt_ccb_free(ccbp))

/*
 * Macro Name: SPO_GET_PATHID
 *     	Return the pathid based on the argument. 
 *
 * Arguments:
 *     	sc 	Pointer to the SIM_SOFTC structure. 
 */
#define SPO_GET_PATHID(sc)	(sc)->cntlr		
    

/* 
 * Macro Name: SPO_GET_CCB
 *	Calculate the CCB pointer from the associated
 *	SIMPORT_WS pointer.  This macro depends on the
 *	placement of the SIMPORT_WS within the DEC CAM
 *	packet.
 *	
 * Arguments:
 *	spo_ws	Pointer to the SIMPORT_WS structure.
 */
#define SPO_GET_CCB(spo_ws) \
   	(CCB_HEADER *)(((U_WORD)(spo_ws)) + ((U_WORD)sizeof(SIM_WS)))

 
/*
 * Macro Name: SPO_CCB_INIT 
 *	Set the CCB pathid, targetid and lun to the current adapter.
 * Arguments:
 *      sc:   Pointer to the SIM_SOFTC structre
 *	ccbp: Pointer to the CCB header that needs to be initialized  
 */
#define SPO_CCB_INIT(sc, ccbp) 			\
{						\
    ccbp->cam_path_id = SPO_GET_PATHID((sc));	\
    ccbp->cam_target_id = (sc)->scsiid;		\
    ccbp->cam_target_lun = 0;			\
}

/*
 * Macro Name: SPO_SET_ADAP_STATE_BLD
 * 	Initialize the field in the adapter state structure
 * Arguments:
 *	spop:	Pointer to the CCB_SPVU_SET_ADAP structure.
 *	state:	Enable or diable.
 */
#define	SPO_SET_ADAP_STATE_BLD(spop, state, flags)	\
{							\
    (spop)->spo_state = state;				\
    (spop)->spo_pad1 = 0;				\
    (spop)->spo_flags = flags;				\
    bzero(&((spop)->spo_pad2[0]), 4);			\
} 

/*
 * Macro Name: SPO_SET_PARAM_BLD
 *      Initialize the field in the adapter state structure
 * Arguments:
 *      spop:   A pointer to the CCB_SPVU_SET_PARAM structure.
 *      state:  Enable or diable.
 */
#define SPO_SET_PARAM_BLD(spop, flags, sys_time, 		\
		int_holdoff, rp_timer, n_host_sg, host_sg_bsd) 	\
{                                              		        \
    (spop)->spo_n_host_sg = n_host_sg;				\
    (spop)->spo_pad = 0;					\
    (spop)->spo_flags = flags;					\
    (spop)->spo_system_time = sys_time;				\
    (spop)->spo_int_holdoff = int_holdoff;			\
    (spop)->spo_rp_timer = rp_timer;				\
    (spop)->spo_host_sg_bsd = host_sg_bsd;			\
}

/*
 * Macro Name: SPO_SET_CHANNEL_STATE_BLD
 *      Initialize the field in the set channel state structure
 * Arguments:
 *      spop:   A pointer to the CCB_SPVU_SET_CHNL structure.
 *      state:  Enable or diable.
 *	chan_id: The internal identifier of the channel id
 *	node_id: The SCSI bus node id for the channel
 */
#define SPO_SET_CHANNEL_STATE_BLD(spop, state, chan_id, node_id) \
{                                                                \
    (spop)->spo_state = state;					 \
    bzero(&((spop)->spo_pad[0]), 3);                             \
    (spop)->spo_chan_id = chan_id;	                         \
    (spop)->spo_node_id = node_id; 				 \
    bzero(&((spop)->spo_pad2[0]), 2);                            \
}

/*
 * Macro Name: SPO_SET_DEV_STATE_BLD
 *      Initialize the fields in the set channel state structure
 * Arguments:
 *      spop:   A pointer to the CCB_SPVU_SET_DEV structure.
 *      state:  Enable or diable.
 */
#define SPO_SET_DEV_STATE_BLD(spop, state)         		\
{                                                               \
    (spop)->spo_state = state;                                  \
    bzero(&((spop)->spo_pad[0]), 7);                            \
}

/*
 * Macro Name: SPO_READ_COUNTER_BLD
 *      Initialize the fileds in the read counters structure 
 * Arguments:
 *      spop:   A pointer to the CCB_SPVU_READ_CNTR structure.
 *      flags:	ZERO_COUNTER, the counters are zeroed after being 
 *		read into the response message. 
 */
#define SPO_READ_COUNTER_BLD(spop, flags)                       \
{                                                               \
    bzero(&((spop)->spo_pad[0]), 2);                            \
    (spop)->spo_flags = flags;					\
    bzero(&((spop)->spo_pad2[0]), 5);                           \
}


/*
 * Macro Name: SPO_RESET_BUS_BLD
 *      Initialize the fileds in the reset bus ccb 
 * Arguments:
 *      ccb:   A pointer to the CCB_HEADER structure.
 *      flags:	ZERO_COUNTER, the counters are zeroed after being 
 *		read into the response message. 
 */
#define SPO_RESET_BUS_BLD(ccb, pathid)                	\
{                                                       \
    (ccb)->cam_ccb_len = sizeof (CCB_RESETBUS);		\
    (ccb)->cam_func_code = XPT_RESET_BUS;			\
    (ccb)->cam_path_id = pathid;				\
    (ccb)->cam_flags = CAM_DIR_NONE;			\
}

/*
 * Macro Name: SPO_IOCCB_VTOP
 * 	Translate user buffer's virtual address to
 *	physical address.
 *
 * Arguments:
 *	CCB_SCSIIO *ioccb: A pointer to the CCB_SCSIIO structure
 *	vm_offset_t vaddr: Virtual address to translate
 *	vm_offset_t phys: Translated physical address
 *
 */
#define SPO_IOCCB_VTOP(ioccb, vaddr, phys)		\
{							\
   if (IS_SYS_VA(vaddr))				\
   {			 				\
       if(svatophys(vaddr, &phys) != KERN_SUCCESS)	\
          phys = (vm_offset_t) NULL;			\
   }							\
   else							\
   {							\
       phys = pmap_resident_extract(proc_to_task(((struct buf *)(ioccb)->cam_req_map)->b_proc)->map->vm_pmap, \
			   vaddr);			\
   }							\
}    
/*
 * SPO_GET_DMA_BA will return the physical address of the
 * first element of the scatter-gather list.
 */
#define SPO_GET_DMA_BA(sg) (dma_get_next_sgentry(sg))->ba

/*
 * SPO_LIST_ADD() and SPO_LIST_DEL() assume NULL terminated lists.
 * They assume that "elem" contains flink and blink pointers.
 */
#define SPO_LIST_ADD(elem, list);					\
    (elem)->flink = (list);						\
    if ((list) != NULL) (list)->blink = (elem);				\
    (list) = (elem);
#define SPO_LIST_DEL(elem, list);					\
    if ((elem) == (list)) (list) = (elem)->flink;			\
    else (elem)->blink->flink = (elem)->flink;

#define SPO_GET_HTL_NEXUS(spo_sc, lun)					\
    (spo_sc)->spo_htl_nexus == NULL ? NULL : (spo_sc)->spo_htl_nexus[(lun)]

/*
 * Debug defines...
 */
/*
#define SPO_DEBUGQ_ON
*/
#ifdef SPO_DEBUGQ_ON
#define SPO_MAX_DEBUGQ 255
#define ADD_DEBUG(msg); {						\
    static int s;							\
    SIM_IPL_LOCK(spo_debugq_lock, s);					\
    CIRQ_SET_CURR(spo_debugq, spo_debugq_buf, (msg));			\
    SIM_IPL_UNLOCK(spo_debugq_lock, s);					\
}
#define SPO_MODULE_DEBUG ADD_DEBUG(module);
#else
#define ADD_DEBUG(msg);
#define SPO_MODULE_DEBUG;
#endif


#endif /* _SIMPORT_INCL_ */
