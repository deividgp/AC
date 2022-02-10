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
#pragma ident "@(#)$RCSfile: met_sw.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:51 $"

#ifndef _MET_SW_H_
#define _MET_SW_H_

/*
* Module Name:
*   met_sw.h
*
* Abstract:
*   This file describes the interface to the common software utilities
*   needed to initialize, configure, and reset Meteor.
*
* Authors:
*   DMW - Douglas M. Washabaugh
*   NCD - Nancy C. DiFonzo
*
* Modification History:
*   Date       Name  Description
*   07-Dec-95  DMW   Created.
*   12-Mar-96  NCD   Added some new routines and modified existing ones
*   27-Mar-96  NCD   -Split 'met_vc_open' into met_xmt_vc_open and met_rcv_vc_open
*                    -Updated comments based on first internal review.
*                    -Added typedefs for MET_CHANNEL_TYPE and MET_RATE_CTRL
*                    -Removed several routines that did not seem approriate
*                     for this module
*
* Description:
*   This module provides device drivers with a common interface for managing 
*   the Meteor SAR chip.  Other than C macros, this module does not provide 
*   any functions to assist in critical path operations (transmitting, 
*   receiving, or processing interrupts).
*
*   This module only allocates generic virtual memory.  Any "special" (memory
*   which can be accessed by the DMA engines) is allocated by the caller.
*
* Design Philosophies:
*   - Don't introduce unnecessary error checking.
*   - Enable the software module to control defaults for all unspecified
*     values.
*   - Minimize the number of values that the driver MUST set.
*   - Simplify the driver initialization code.
*   - Don't make the driver perform weird encodings for values.
*   - Be consistent with existing management strategies.
*
* Issues:
*
*/

#define     MET_CBR_RATE_TOLERANCE      1000   /* Target tolerance for CBR */

/*++
* MET_ITEM_CODE
* 
* Use these item codes when performing set/get operations.
* The description of each item code includes the access and the type.
* If the type is preceded by a "*", the get/set routine interprets the 
* "value" parameter as a pointer.
--*/

typedef enum
   {
   MET_ITEM_K_SW_ABR,                /* RW, Boolean                           */
   MET_ITEM_K_CBR_TBL,               /* RW, 0/1                               */ 
   MET_ITEM_K_USE_FM_FOR_RM,         /* RW, Boolean                           */
   MET_ITEM_K_FM_RESYNC,             /* WO, 1 = Start resync                  */
   MET_ITEM_K_USE_FM,                /* RW, Boolean                           */
   MET_ITEM_K_DISABLE_MRM_MRL,       /* RW, Boolean                           */
   MET_ITEM_K_MRM_OR_MRL,            /* RW, Boolean                           */
   MET_ITEM_K_64K_MODE,              /* RW, Boolean                           */
   MET_ITEM_K_VC_MODE,               /* RW, Refer to MET_VC_MODE              */
   MET_ITEM_K_VPI_VCI_MAPPING,       /* RW, Refer to MET_VC_MAP               */
   MET_ITEM_K_XMT_ENB,               /* RW, Boolean                           */
   MET_ITEM_K_PHY_GFC_SIGNAL,        /* RW, Boolean                           */
   MET_ITEM_K_PHY_CELL_MODE,         /* RW, Boolean                           */
   MET_ITEM_K_PHY_INT_HIGH,          /* RW, Boolean                           */
   MET_ITEM_K_PHY_LOOPBACK,          /* RW, Boolean                           */
   MET_ITEM_K_PHY_USE_GFC_FLOW_CTRL, /* RW, Boolean                           */
   MET_ITEM_K_PHY_GFC_A,             /* RW, Boolean                           */
   MET_ITEM_K_PHY_RCV_ENB,           /* RW, Boolean                           */   
   
   MET_ITEM_K_VC_CONG_CI,            /* RW, Boolean                           */  
   MET_ITEM_K_BIG_CI,                /* RW, Boolean                           */ 
   MET_ITEM_K_SMALL_CI,              /* RW, Boolean                           */ 
   MET_ITEM_K_RAW_CI,                /* RW, Boolean                           */ 
   MET_ITEM_K_BIG_SLOT_LOW_THOLD,    /* RW, MET_SLOT_LOW_THOLD                */  
   MET_ITEM_K_SMALL_SLOT_LOW_THOLD,  /* RW, MET_SLOT_LOW_THOLD                */ 
   MET_ITEM_K_RAW_SLOT_LOW_THOLD,    /* RW, MET_SLOT_LOW_THOLD                */ 
   MET_ITEM_K_BIG_SLOT_SIZE,         /* RW, MET_BIG_SLOT_SIZE                 */
   MET_ITEM_K_SMALL_SLOT_SIZE_LWRDS, /* RW, 16 <= value <= 511, or 0 for 512  */
   MET_ITEM_K_RCV_REASSEMBLY_TIMEOUT,/* RW, 0 = off, 2 <= value <= 15         */
   MET_ITEM_K_RCV_AAL5_16K_LIMIT,    /* RW, Boolean                           */
   MET_ITEM_K_EFCI_OR,               /* RW, Boolean                           */  
   MET_ITEM_K_RESET_STATE,           /* RW, Boolean                           */
   MET_ITEM_K_XMT_REPORT,            /* RW, *MET_REPORT_RING_PARAMS           */  
   MET_ITEM_K_RCV_REPORT,            /* RW, *MET_REPORT_RING_PARAMS           */
   MET_ITEM_K_RAW_CONGEST_THOLD,     /* RW, 0 disables                        */  
   MET_ITEM_K_BIG_CONGEST_THOLD,     /* RW, 0 disables                        */
   MET_ITEM_K_SMALL_CONGEST_THOLD,   /* RW, 0 disables                        */
   MET_ITEM_K_XMT_ABR,               /* RW, *MET_XMT_ABR                      */  
   MET_ITEM_K_CREDITS,               /* RW, *MET_CREDITS                      */
   MET_ITEM_K_CNTRS,                 /* RO, *MET_CNTRS                        */
   MET_ITEM_K_PCI_CONFIG,            /* RO, *MET_PCI_CONFIG                   */
   MET_ITEM_K_XMT_IOC_HLD_WR_ENB,    /* WO, 0 disables                        */
   MET_ITEM_K_XMT_IOC_HLD_CNT,       /* RW, 0 <= value <= 127                 */
   MET_ITEM_K_XMT_IOC_HLD_TM,        /* RW, 0 <= value <= 255                 */
   MET_ITEM_K_RCV_IOC_HLD_WR_ENB,    /* WO, 0 disables                        */
   MET_ITEM_K_RCV_IOC_HLD_CNT,       /* RW, 0 <= value <= 127                 */
   MET_ITEM_K_RCV_IOC_HLD_TM,        /* RW, 0 <= value <= 255                 */
   MET_ITEM_K_SLOTS_CONSUMED         /* RW, *MET_VC_INFO                      */
   } MET_ITEM_CODE; 

/* ***** Define Types for the met_item_get and met_item_set Routines. ****** */

/*++
* MET_RATE_CTRL
*
* An enumeration to specify the type of rate control for a Transmit VC.
*
--*/

typedef enum
   {
   MET_RATE_CTRL_K_CBR = 0,
   MET_RATE_CTRL_K_ABR = 1,
   MET_RATE_CTRL_K_UBR = 2,
   MET_RATE_CTRL_K_RSV = 3
   } MET_RATE_CTRL;

/*++
* MET_CHANNEL_TYPE
*
* An enumeration to specify the channel type for a Transmit VC.
*
--*/

typedef enum
   {
   MET_CHAN_TYPE_K_RAW  = 0,
   MET_CHAN_TYPE_K_RSV  = 1,
   MET_CHAN_TYPE_K_AAL5 = 2,
   MET_CHAN_TYPE_K_MPEG = 3
   } MET_CHANNEL_TYPE;

/*++
* MET_SLOT_LOW_THOLD
*
* An enumeration to specify the threshold at which a receive queue is 
* becoming close to empty.
*
--*/

typedef enum
   {
   MET_SLOTS_LOW_THOLD_K_8  = 0,
   MET_SLOTS_LOW_THOLD_K_16 = 1,
   MET_SLOTS_LOW_THOLD_K_32 = 2,
   MET_SLOTS_LOW_THOLD_K_64 = 3
   } MET_SLOTS_LOW_THOLD;

/*++
* MET_RCV_RAW_HOLD
*
* An enumeration to specify the number of raw cell slots which must be filled 
* receive data before a raw cell receive status report is generated.
*
--*/

typedef enum
   {
   MET_RCV_RAW_HOLD_0  = 0,
   MET_RCV_RAW_HOLD_4  = 1,
   MET_RCV_RAW_HOLD_16 = 2,
   MET_RCV_RAW_HOLD_32 = 3
   } MET_RCV_RAW_HOLD;


/*++
* MET_VC_MODE
*
* An enumeration to specify the VC mode for Meteor.
*
--*/

typedef enum
   {
   MET_VC_MODE_K_256B  = 0,
   MET_VC_MODE_K_1K    = 1
   } MET_VC_MODE;

/*++
* MET_VC_MAP
*
* An enumeration to specify the manner in which the VC provided by 
* the driver for transmitted AAL5 packets is mapped to cell VPI/VCIs.
*
--*/

typedef enum
   {
   MET_VC_MAP_K_MODE_0 = 0,
   MET_VC_MAP_K_MODE_1 = 1,
   MET_VC_MAP_K_MODE_2 = 2,
   MET_VC_MAP_K_MODE_3 = 3
   } MET_VC_MAP;

/*++
* MET_BIG_SLOT_SIZE
*
* An enumeration to specify the kilobyte size of slots in the "big" 
* receive queue.
*
--*/

typedef enum
   {
   MET_BIG_SLOT_SIZE_K_1  = 0,
   MET_BIG_SLOT_SIZE_K_2  = 1,
   MET_BIG_SLOT_SIZE_K_4  = 2,
   MET_BIG_SLOT_SIZE_K_8  = 3,
   MET_BIG_SLOT_SIZE_K_10 = 4,
   MET_BIG_SLOT_SIZE_K_16 = 5
   } MET_BIG_SLOT_SIZE;

/*++
* MET_XMT_ABR
*
* This structure contains information about transmit ABR settings.  Except
* for the line rate, 2 sets of parameters are specified.  When a VC is opened,
* it can be specified to use the first or second set.
*
*   line_rate -
*     The line rate in bits/sec.
*
*   adtf - 
*     ACR Decay Timer Factor for base parameter set 1.  This is specified in 
*     units of 251.52 us.
*           
*   nrm -
*     (Log(Base2)(desired NRM value)) -1.
*     Where:   0 <=  nrm  <= 7, allowing  2 <= NRM <= 256
*
*   trm -
*     The designed TRM value.  Specified in units of 251.52 us.
--*/

typedef struct
   {
   UINT32 line_rate;
   UINT32 adtf[2];
   UINT32 nrm[2];
   UINT32 trm[2];
   } MET_XMT_ABR;

/*++
* MET_CNTRS
* 
* Contains the counters maintained by the Meteor hardware.  All counters
* wrap.  Because counters cannot be sampled simultaneously, there will be a
* small skew between their values.  Refer to the programming spec for more
* details.
*
--*/

typedef struct
   {
   UINT32 rcv_cells;
   UINT32 rcv_aal5_pkts_dropped;
   UINT32 rcv_raw_cells_dropped;
   UINT32 xmt_cells;
   } MET_CNTRS;

/*++
* MET_SLOT_TYPE
*
* An enumeration to specify one of 3 types of slots.
*
--*/

typedef enum
   {
   MET_SLOT_TYPE_K_SMALL = 0,
   MET_SLOT_TYPE_K_BIG   = 1,
   MET_SLOT_TYPE_K_RAW   = 2
   } MET_SLOT_TYPE;

/*++
* MET_CREDITS
*
* Use this structure when setting the credits on a VC.
*
*   vpi -
*     The VPI of the VC to which the credits are assigned.
*   vci - 
*     The VCI of the VC to which the credits are assigned.
*
*   credits -
*     The number of credits to assign to the VC.
--*/

typedef struct
   {
   UINT32 vc_id;
   UINT32 credits;
   } MET_CREDITS;

/*++
* MET_VC_VALUE
*
* Use this structure when setting a generic on a VC.
*
* vc_id -
*   The VC_ID on which to set/get.
* 
* value -
*   The value that was set or read. 
--*/

typedef struct
   {
   UINT32 vc_id;
   UINT32 value;
   } MET_VC_VALUE;

/*++
*  MET_REPORT_RING_PARAMS
*
*  This structure contains the address and length of a report ring.  Only
*  32 bit addresses are supported.
*
*  base_phys_addr -
*    The physical address of the report ring.  The DMA engines use this
*    address.  If this memory is cached, the caller must ensure that the 
*    cache is flushed before accessing the report ring.
*
*  byte_len -
*    The byte length of the memory pointed to by "base_phys_addr".
--*/

typedef struct
   {
   UINT32  base_phys_addr;
   void   *p_report_ring;
   UINT32  byte_len;
   } MET_REPORT_RING_PARAMS;

/*++
*  MET_PCI_CONFIG
*
*  This structure contains the 16 longwords of the PCI Configuration area.
*  No attempt is made to specify individual fields since the MET_ITEM_GET
*  routine only allows the entire PCI configuration area to be read.
*
*  
--*/

typedef struct
   {
   UINT32 pci_cfg_data[16];
   } MET_PCI_CONFIG;


/*++
* ----------------------
* - MET_VC_CALLBACK -
* ----------------------
*
* Overview:
*   The meteor software module makes this callback when a VC operation
*   completes.
*
* Arguments:
*   context    - (IN)  The caller context (handle) that was specified when
*                      the VC operation was started.
*
*   vc         - (IN)  The VC associated with the operation.
*
* Returns:
*   none
*
* Preconditions:
*   A VC operation was started and completed. 
*
* Postconditions:
*   none
*
* Issues:
*   none
--*/                                              

typedef void (*MET_VC_CALLBACK) (HANDLE  context,
                                 UINT32  vc);   

   
/*++
* ==============================
* = XMT_DESCR_0_CREATE (macro) =
* ==============================
*
* Overview:
*   This macro creates the first longword of a transmit pending slot.  It 
*   does not perform the write to Meteor, it simply forms the longword 
*   specified by the input paramters and returns to the caller.
*
* _DESCR_0 -
*    The 32 bit quantity that this macro builds..
*
* _RAW -
*    If set to '1', the transmit slot contains a Raw cell.  Otherwise, the 
*    transmit slot contains an idle or AAL5 packet.
*
* _IDLE -
*    If set to '1', the data in the transmit slot is ignored (not DMA'd or 
*    transmitted), and an idle cell is sent.  Otherwise, the data in the 
*    transmit slot is DMA'd and transmitted.  This bit should be set to '1'
*    only for use in timing MPEG streams.
*
* _MGMT -
*    If set to '1', the data in the transmit stream is an F4 or F5 OAM cell.
*    
* _VC -
*    The VC on which the data is to be transmitted.
*
* _CRC_10_ENB -
*    If set to '1' (the RAW bit must also be set to '1' in this case), a CRC-10
*    is calculated and appended to the cell.  This bit must be set to '0' for 
*    all transmit slots containing AAL5 data.
*
* _EOP -
*    For AAL5 or idle packets (RAW = 0), a value of '1' indicates that this 
*    transmit slot contains the last byte of data.
*
*    For cells (RAW = 1), a value of '1' indicates that a status report and 
*    interrupt should be reported when the cell has been DMA'd.
*
* _SLOT_SIZE
*    The number of bytes contained in the transmit slot.  If RAW = 1, then this
*    field  must be set to 52.  This value must be in the range of 1-16383.
--*/
#define XMT_DESCR_0_CREATE(_DESCR_0, _RAW, _IDLE, _MGMT, _VC, _CRC_10_ENB, \
 				 _EOP, _SLOT_SIZE)                    \
   {                                              \
   _DESCR_0 = 0;                                  \
   _DESCR_0 |= _RAW        << MET_XMT_PEND_V_RAW; \
   _DESCR_0 |= _IDLE       << MET_XMT_PEND_V_IDL; \
   _DESCR_0 |= _MGMT       << MET_XMT_PEND_V_MGT; \
   _DESCR_0 |= _VC         << MET_XMT_PEND_V_VC;  \
   _DESCR_0 |= _CRC_10_ENB << MET_XMT_PEND_V_CRC; \
   _DESCR_0 |= _EOP        << MET_XMT_PEND_V_EOP; \
   _DESCR_0 |= _SLOT_SIZE  << MET_XMT_PEND_V_SZ;  \
   }

/*++
* ==============================
* = RCV_DESCR_0_CREATE (macro) =
* ==============================
*
* This macro creates longword 0 of a receive pending slot.
*
* _DESCR_0 -
*    The 32 bit quantity that this macro initializes.
*    
* _SLOT_TYPE -
*    0 = Small slot, 1 = Bit slot, 2 = Raw slot.
*
* _VC -
*    The VC with which this receive slot is associated.  For initial posting of
*    receive buffers, this should have the value 0.  For subsequent receive 
*    postings, this should contain the VC from the previous receive operation
*    in this buffer.
*
--*/
#define RCV_DESCR_0_CREATE(_DESCR_0, _SLOT_TAG, _SLOT_TYPE, _VC) \
   {                                                 \
   _DESCR_0  = 0;                                    \
   _DESCR_0  = _SLOT_TAG    << MET_RCV_PEND_V_TAG;   \
   _DESCR_0 |= _SLOT_TYPE   << MET_RCV_PEND_V_TYPE;  \
   _DESCR_0 |= _VC          << MET_RCV_PEND_V_VC;    \
   }

/*++
* ==============
* = met_create =
* ==============
*
* Overview:
*   This function creates an instance of this module.  This MUST be the first
*   call made to this module.  The returned handle is required by all calls to
*   this module.
*
* Arguments:
*   os_handle      - (IN)   Handle to use when calling the os_utl module.
*
*   os_reg_handle  - (IN)   Handle to use when calling the os_reg module.
*
*   vc_mode        - (IN)   Value indicating vc mode, which sets the
*                           number of VC's supported by Meteor.
*
*   p_met_rcv_rpt  - (IN)   Pointer to a structure containing the physical 
*                           address and length of the  host resident receive 
*                           report ring.
*
*   p_met_xmt_rpt  - (IN)   Pointer to a structure containing the physical 
*                           address and length of the host resident transmit 
*                           report ring.
*
*   p_text         - (IN)   Pointer to a text string that describes this
*                           instance.  This pointer must remain valid
*                           until the module is destroyed.
*
*   p_met_handle   - (OUT)  Handle that is required for subsequent calls
*                           to this module.
*
* Returns:
*   STATUS_K_SUCCESS -   Instance created.
*   STATUS_K_RESOURCES - Insufficient resources, instance not created.
*   STATUS_K_NOT_ALIGNED   - Improper alignment of a variable.
*
* Preconditions:
*   none
*
* Postconditions:
*   If success is returned, *p_met_handle is valid.
*
* Issues:
*   none
--*/                                              

STATUS met_create (HANDLE                   os_handle,
                   HANDLE                   os_reg_handle,
                   MET_VC_MODE              vc_mode,
                   MET_REPORT_RING_PARAMS  *p_met_rcv_rpt,
                   MET_REPORT_RING_PARAMS  *p_met_xmt_rpt,
                   char                    *p_text,
                   HANDLE                  *p_met_handle);

/*++
* ===============
* = met_destroy =
* ===============
*
* Overview:
*   Returns any allocated resources.  This MUST be the last call made to this
*   instance.
*
* Arguments:
*   met_handle - (IN) The handle returned by met_create.
*
* Returns:
*   none
*
* Preconditions:
*   met_handle is valid or NULL.
*
* Postconditions:
*   met_handle is invalid.
*
* Issues:
*   none
--*/
                                              
void met_destroy (HANDLE met_handle);

/*++
* ================
* = met_item_set =
* ================
*
* Overview:
*   The value of the specified item is set.
*
* Arguments:
*   met_handle    - (IN) The handle returned by met_create.
*
*   item_code     - (IN) The item code to set.
*
*   p_buff        - (IN) Depending upong the item code, this may be either the 
*                        actual value or a pointer to a buffer containing the 
*                        information about the value to set.
*
*   buff_size     - (IN) The byte length of p_buff.
*                   
*
* Returns:
*   STATUS_K_SUCCESS      - Refer to postconditions.
*   STATUS_K_OUT_OF_RANGE - Value was not valid for this item.  In the case
*                           of multiple items, no items will be set if any
*                           are in error.
*
*   STATUS_K_READ_ONLY - The item is read only.
*   STATUS_K_NOT_FOUND - The item code was not found.
*
* Preconditions:
*   Dependent upon item code.
*
* Postconditions:
*   Dependent upon item code.
*
* Issues:
*   none
--*/

STATUS met_item_set (HANDLE            met_handle,
                     MET_ITEM_CODE     item_code,
                     void             *p_buff,
                     UINT32            buff_size);

/*++
* ================
* = met_item_get =
* ================
*
* Overview:
*   The value of the specified item is copied into the 
*   caller's buffer.
*
* Arguments:
*   met_handle      - (IN)  The handle returned by met_create.
*
*   item_code       - (IN)  The item code to get.
*
*   p_value         - (OUT) Depending upong the item code, this may be either the 
*                           actual value or a pointer to a buffer containing the 
*                           information about the value to set.
*
*   buff_size       - (IN)  Size of the buffer allocated by the caller.
*
*   p_bytes_written - (OUT) Pointer to the number of bytes written
*                           to p_value.
*
* Returns:
*   STATUS_K_SUCCESS          - Refer to postconditions.
*   STATUS_K_WRITE_ONLY       - The item code was not known or read-only.
*   STATUS_K_BUFFER_TOO_SMALL - Buffer allocated by caller is too small.
*   STATUS_K_NOT_FOUND        - The item code was not found.
*
* Preconditions:
*   none
*
* Postconditions:
*   The value of the item is copied into caller's buffer.
*
* Issues:
*   none
--*/

STATUS met_item_get (HANDLE            met_handle,
                     MET_ITEM_CODE     item_code,
                     void             *p_value,
                     UINT32            buff_size,
                     UINT32           *p_bytes_written);

/*++
* ===================
* = met_rcv_vc_open =
* ===================
* Overview:
*   Opens the specified VC for receive.  
*
* Arguments:
*   met_handle      - (IN)  The handle returned by met_create.
*
*   vpi             - (IN)  The vpi value of the VC to be opened.
*  
*   vci             - (IN)  The vci value of the VC to be opened.
*
*   crc_10          - (IN)  If true, CRC10 checking is enabled.
*
*   aal5_streaming  - (IN)  If true, receive AAL5 streaming-mode is enabled.
*
*   slot_type       - (IN)  Specifies which type, small, big or raw, of slot
*                           to use for receive data.
*
*   flow_master     - (IN)  If true, FLOWmaster is enabled.
*
*   p_vc_id         - (OUT) Mapped vc identifier.
*
* Returns:
*
*   STATUS_K_SUCCESS          - Refer to postconditions.
*   STATUS_K_INVALID_VC       - Invalid VC.  No action taken.
*   STATUS_K_ALREAD_OPEN      - This VC was alread open.  No action taken.
*  
*
* Preconditions:
*
* Postconditions:
*   Opens the specified VC for receive.
*
* Issues:
--*/

STATUS met_rcv_vc_open (HANDLE              met_handle,
                        UINT8               vpi,
                        UINT16              vci,
                        BOOLEAN             crc_10,
                        BOOLEAN             aal5_streaming,
                        MET_SLOT_TYPE       slot_type,
                        BOOLEAN             flow_master,
                        UINT32             *p_vc_id);

/*++
* ===================
* = met_xmt_vc_open =
* ===================
* Overview:
*   Opens the specified VC with the specified characteristics for transmit.
*   Use this call to create any kind of VC (PVC, SVC) with any characteristic.
*  
*   The Transmit VC State Table entry for the specified VC is initialized with
*   input values.  The ABR Parameter and Value Tables are also initialized, as
*   appropriate, for the VC.
*
* Arguments:
*   met_handle      - (IN)  The handle returned by met_create.
*
*   vpi             - (IN)  The vpi value of the VC to be opened.
*  
*   vci             - (IN)  The vci value of the VC to be opened.
*
*   aal5_streaming  - (IN)  If true, receive AAL5 streaming-mode is enabled.
*  
*   abr_base_selection - (IN) Selects which of the 2 parameter base sets to use.
*
*   flow_master     - (IN)  If true, FLOWmaster is enabled.
*
*   credits         - (IN)  Initial value for FLOWmaster credit field.  Only
*                           valid when flow_master is true.
*
*   channel_type    - (IN)  Specifies which type, raw, AAL5, or MPEG, of channel
*                           to use for transmit data.
*
*   rate_ctrl       - (IN)  Specifies which type, CBR, ABR or UBR, of rate 
*                           control to use for transmit data.
*
*   cell_loss_priority
*                   - (IN)  Value for Cell Loss Priority to be transferred
*                           to ATM header of transmitted AAL5 cells.
*
*   ubr_cell_rate   - (IN)  UBR peak cell rate.
*
*   abr_cutoff_decrease_factor
*                   - (IN)  Value for ABR Cutoff Decrease Factor which controls
*                           the decrease in ACR associated with missing cell
*                           count.  The value written to the ABR parameter
*                           table is equal to:  
*
*                             For abr_cutoff_decrease_factor not equal to 0:
*                                Log(1/abr_cutoff_decrease_factor) 
*                                            or
*                             For abr_cutoff_decrease_factor equal to 0:
*                                           7.
*
*   abr_rate_decrease_factor
*                   - (IN)  Value for the ABR Rate Decrease Factor which controls
*                           the decrease in the cell transmission rate.  The 
*                           value written to the ABR parameter table is equal to:
*  
*                             For abr_rate_decrease_factor not equal to 0:
*                                Log(1/abr_rate_decrease_factor), 
*                                              or
*                             For abr_rate_decrease_factor equal to 0:
*                                              10
* 
*   abr_missing_rm_cell_cnt
*                   - (IN)  Value for the Missing Cell Count which specifies the 
*                           number of FRM cells.  The value written to the ABR
*                           parameter table is equal to:
*                                Log(abr_missing_rm_cell_cnt) - 1
*
*   abr_additive_increase_rate
*                   - (IN)  Value for the Additive Increase Rate.
*
*   abr_initial_cell_rate
*                   - (IN)  Value for the Initial Cell Rate.
* 
*   abr_min_cell_rate
*                   - (IN)  Value for Minimum Cell Rate.
*
*   abr_peak_cell_rate
*                   - (IN)  Value for Peak Cell Rate.
*
*
*   p_vc_id         - (OUT) Mapped vc identifier.

*
* Returns:
*   STATUS_K_SUCCESS      - Transmit VC opened.
*   STATUS_K_INVALID_VC   - Specified VC was invalid, no action taken.
*   STATUS_K_ALREADY_OPEN - Transmit VC alread open, no action taken.
*   STATUS_K_ARG_X_BAD    - Argument at position x of parameter list
*                           has an invalid value.
*
* Preconditions:
*
* Postconditions:
*   The NIC transmit over specified VC.
*
* Issues:
*   
--*/

STATUS met_xmt_vc_open (HANDLE              met_handle,
                        UINT8               vpi,
                        UINT16              vci,
                        BOOLEAN             aal5_streaming,
                        BOOLEAN             abr_base_selection,
                        BOOLEAN             flow_master,
                        UINT32              credits,
                        MET_CHANNEL_TYPE    channel_type,
                        MET_RATE_CTRL       rate_ctrl,     
                        BOOLEAN             cell_loss_priority,
                        UINT32              ubr_cell_rate,
                        UINT32              abr_cutoff_decrease_factor,
                        UINT32              abr_rate_decrease_factor,
                        UINT32              abr_missing_rm_cell_cnt,
                        UINT32              abr_additive_increase_rate,
                        UINT32              abr_initial_cell_rate,
                        UINT32              abr_min_cell_rate,
                        UINT32              abr_peak_cell_rate,
                        UINT32             *p_vc_id);

/*++
* ================
* = met_vc_flush =
* ================
*
* Overview:
*   Flushes any FLOWmaster credits that may have been queued.  When the flush 
*   operation completes, the caller is called back.
*
* Arguments:
*   met_handle    - (IN) The handle returned by met_create.
*
*   vc            - (IN) The VC to flush.
*
*   callback      - (IN) The routine to call when the flush completes.
*
*   context       - (IN) The context to pass to the callback routine.
*
* Returns:
*   STATUS_K_SUCCESS - The flush operation has completed.
*   STATUS_K_PENDING - The flush operation has started.
*   STATUS_K_FAILURE - The VC could not be flushed.
*
* Preconditions:
*   none
*
* Postconditions:
*   The specified VC is flushed of all FLOWmaster credits.
*
* Issues:
*   
--*/

STATUS met_vc_flush (HANDLE             met_handle,
                     UINT32             vc,
                     MET_VC_CALLBACK    callback,
                     HANDLE             context);
/*++
* ====================
* = met_rcv_vc_close =
* ====================
*
* Overview:
*   Disables the NIC from receiving over a currently
*   opened VC.
*
* Arguments:
*   met_handle - (IN) The handle returned by met_create.
*
*   vc_id      - (IN) The mapped vc identifier for the vc to be closed.
*  
*
* Returns:
*   STATUS_K_SUCCESS    -  Receive VC was closed.
*   STATUS_K_INVALID_VC -  Receive VC not valid.
*   STATUS_K_NOT_OPEN   -  Receive VC not opened.
*
* Preconditions:
*   VC must have been opened.
*
* Postconditions:
*   The VC is closed.  It will no longer  receive cells/packets.
*
* Issues:
*   none
--*/

STATUS met_rcv_vc_close (HANDLE             met_handle,
                         UINT32             vc_id);

/*++
* =======================
* = met_peep_hole_write =
* =======================
*
* Overview:
*   Performs a write to Meteor's peripheral and SRAM address space.  This is the
*   only mechanism that can be used to perform a write operation to this
*   address space.
*
*
* Arguments:
*   met_handle    - (IN) The handle returned by met_create.
*
*   sram_access   - (IN) If true, the SRAM memory space is accessed.  Otherwise,
*                        the peripheral memory space is accessed.
*
*   addr          - (IN) The destination peripheral or SRAM address.
*
*   value         - (IN) The value to write.
*
* Returns:
*   STATUS_K_SUCCESS - The write completed successfully.
*
*   STATUS_K_FAILURE - The write failed since the peephole access timed out.
*
* Preconditions:
*   - Peephole done bit is set.  This is guaranteed to be true if all peephole
*     transactions are via the met_peephole_write or met_peephole_read commands.
*
* Postconditions:
*   Peephole location has been written.
*
* Issues:
*   none
--*/

STATUS met_peephole_write (HANDLE          met_handle,
                           BOOLEAN         sram_access,
                           UINT32          addr,
                           UINT32          value);

/*++
* =====================
* = met_peephole_read =
* =====================
*
* Overview:
*   Performs a read to Meteor's peripheral or SRAM address space.  This is the
*   only mechanism that should be used to perform read operation to these 
*   address spaces. 
*
* Arguments:
*   met_handle    - (IN) The handle returned by met_create.
*
*   sram_access   - (IN) If true, the SRAM memory space is accessed.  Otherwise,
*                        the peripheral memory space is accessed.
*
*   addr          - (IN) The destination peripheral or SRAM address.
*
*   p_value       - (IN) Pointer to where result is copied.
*
*
* Returns:
*   STATUS_K_SUCCESS - The read completed successfully.
*
*   STATUS_K_FAILURE - The peephole access timed out. 
*
* Preconditions:
*   - Peephole done bit is set.  This is guaranteed to be true if all peephole
*     transactions are via the met_peephole_write or met_peephole_read commands.
*
* Postconditions:
*   A peep-hole operation may have been started.
*
* Issues:
*   none
--*/

STATUS met_peephole_read (HANDLE           met_handle,
                          BOOLEAN          sram_access,
                          UINT32           addr,
                          UINT32           *p_value);

/*++
* =========================
* = met_peephole_prf_read =
* =========================
*
* Overview:
*   Performs a read to Meteor's peripheral address space.  
*
* Arguments:
*   met_handle    - (IN) The handle returned by met_create.
*
*   offset        - (IN) The destination peripheral or SRAM address.
*
*   p_value       - (IN) Pointer to where result is copied.
*
*
* Returns:
*   STATUS_K_SUCCESS - The read completed successfully.
*
*   STATUS_K_FAILURE - The peephole read operation failed.
*
* Preconditions:
*   - Peephole done bit is set.  This is guaranteed to be true if all peephole
*     transactions are via the met_peephole_write, met_peephole_read, or
*     met_peephole_prf_read commands.
*
* Postconditions:
*   None.
*
* Issues:
*   None
--*/

STATUS met_peephole_prf_read (HANDLE           met_handle,
                              UINT32           offset,
                              UINT32          *p_value);

/*++
* ==================
* = met_credit_set =
* ==================
*
* Overview:
*   Sets the credit field of a transmit VC configured for FLOWmaster.
*
* Arguments:
*   met_handle - (IN) The handle returned by met_create.
*
*   vc_id      - (IN) The mapped vc identifier for the VC
*
*   credits    - (IN) Desired number of credits for the specified VC.
*  
*
* Returns:
*   STATUS_K_SUCCESS       -  Credit field was set.
*   STATUS_K_OUT_OF_RANGE  -  Credit value was too large.
*   STATUS_K_FAILURE       -  Credit field was not set.
*
* Preconditions:
*   none.
*
* Postconditions:
*   The credit field of the specified VC may be updated.
*
* Issues:
*   none
--*/

STATUS met_credit_set (HANDLE             met_handle,
                       UINT32             vc_id,
                       UINT32             credits);

/*++
* ============
* = met_init =
* ============
*
* Overview:
*   Initializes all components of Meteor that require software intervention.
*   This includes the Transmit Free and Active Slot Lists and associated
*   pointers, and all CSR values which are programmable.
*
* Arguments:
*   met_handle     - (IN) The handle returned by met_create.
*
* Returns:
*   STATUS_K_SUCCESS       - The initialization completed successfully.
*   STATUS_K_NOT_SUPPORTED - VC mode is not supported.
*
* Preconditions:
*   met_handle is valid or NULL.
*
* Postconditions:
*   Transmit Free Slot List and Active Slot Lists and all pointers have 
*   been initialized.  CSR's have been initialized with default data.
*
* Issues:
*   Need to define all, if any,  'non-default' data that should be loaded 
*   into the CSR's following the reset.
*   
--*/

STATUS met_init (HANDLE met_handle);
 


/*++
* ========================
* = met_cbr_sched_insert =
* ========================
*
* Overview:
*   This routine adds the specified vc_id to the CBR transmit schedule.  If the 
*   vc_id is already in the transmit schedule, it is first removed and then
*   re-added.  An error status is returned if the requested transmit bandwidth 
*   exceeds the remaining transmit bandwidth.  The remaining transmit bandwidth
*   depends on the link bandwidth and the previous CBR schedule requests.
*
*   The caller must have prevously opened the vc_id by calling met_xmt_vc_open. 
*
*   met_handle - (IN) The handle returned by met_create.
*
*   vpi        - (IN) The VPI for CBR circuit being added
*
*   vci        - (IN) The VCI for CBR circuit being added
* 
*   rate       - (IN) Rate, expressed in Megabits, for CBR circuit.
*
* Returns:
*   STATUS_K_SUCCESS       -  The CBR circuit was opened.
*
*   STATUS_K_FAILURE       -  Not enough bandwidth available for this rate or
*                             could not be fit into the schedule within an
*                             acceptable error allowance.  No action was taken.
*
*   STATUS_K_OUT_OF_RANGE  -  Transmit rate is either too fast or too slow
*
*
*
* Preconditions:
*
*   - met_xmt_vc_open was previously called to open the vc_id.  
*
* Postconditions:
*
*   - New CBR VC may have been added to the schedule table.
*
* Issues:
*
*   none
*
--*/

STATUS met_cbr_sched_insert (HANDLE met_handle, 
                             UINT8  vpi,
                             UINT16 vci, 
                             UINT32 rate);


/*++
* ==============================
* = met_cbr_tbl_size_calculate =
* ==============================
*
* Overview:
*   This routine calculates the CBR schedule table size required to
*   achieve the requested input transmit rate.  The largest table size which 
*   satisfies the guaranteed tolerance (1% currently) of the input rate is 
*   chosen.  
*
* Arguments:
*   met_handle  - (IN)  The handle returned by met_create.
*
*   rate        - (IN)  Transmit rate, in Megabytes, that the CBR schedule
*                       table size is based on.
*
*   p_tbl_size  - (OUT) Pointer to the location containing the size, in slots,
*                       of the CBR schedule table.
*
* Returns:
*   STATUS_K_SUCCESS      -  Refer to postconditions
*
*   STATUS_K_OUT_OF_RANGE -  Transmit rate is either too fast or too slow
*
*   STATUS_K_FAILURE      -  A CBR schedule table size could not be found to 
*                            support the input rate within the guaranteed 
*                            tolerance.
*
* Preconditions:
*   none
*
* Postconditions:
* 
*   A value for schedule size, in slots, is determined for the desired transmit
*   rate.
*
--*/

STATUS met_cbr_tbl_size_calculate (HANDLE met_handle, 
                                   UINT32 rate,
                                   UINT16 *p_tbl_size);


/*++
* ============================
* = met_cbr_tbl_vc_id_remove =
* ============================
*
* Overview:
*
*   This routine removes the vc_id from the transmit schedule.  The bandwidth 
*   that had been allocated to this vc_id is now available for future transmit 
*   schedule requests.
*
*   After this routine is called, no more transmits should be done on the vc_id.
*
*   No action is taken if a matching VC is not found.
*
* Arguments:
*   met_handle - (IN) The handle returned by met_create.
*
*   vpi        - (IN) The VPI of the CBR circuit being removed.
*
*   vci        - (IN) The VCI of the CBR circuit being removed.
*                        
* Returns:
*   STATUS_K_SUCCESS      -  Refer to postconditions.
*
*   STATUS_K_NOT_FOUND    -  CBR circuit for this VC was not found.
*
*
* Preconditions:
*   met_handle is valid or NULL.
*
* Postconditions:
*
*  - No more transmits can be done on the vc_id.
*  - The transmit schedule bandwidth allocated to the vc_id is freed.
*
* Issues:
*   none
*
*/

STATUS met_cbr_tbl_vc_id_remove (HANDLE met_handle, 
                                 UINT8  vpi,
                                 UINT16 vci);


/*++
* ==============
* = met_map_vc =
* ==============
*
* Overview:
*   Call this routine to determine how a VPI/VCI combination will be mapped 
*   into a VC_ID.  The VC_ID is a flat representation of the VPI and VCI 
*   space.  The returned value takes into account the current programming
*   of the VPI mapping in the Meteor chip.
*
* Arguments:
*   met_handle - (IN)  The handle returned by met_create.
*
*   vpi        - (IN)  The VPI to map. 
*
*   vci        - (IN)  The VCI to map.
*                        
*   p_vc_id    - (OUT) The mapped vc_id.
*                        
* Returns:
*   STATUS_K_SUCCESS -  The VPI, VCI values are valid for the Meteor mode.
*
*   STATUS_K_FAILURE -  The VPI, VCI values are invalid for the Meteor mode.
*
* Preconditions:
*   met_handle is valid.
*
* Postconditions:
*   none
*
* Issues:
*   none
*
--*/

STATUS met_map_vc (HANDLE met_handle,
                   UINT8  vpi,
                   UINT16 vci, 
                   UINT32 *p_vc_id);

#endif	/* _MET_SW_H_ */
