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
#pragma ident "@(#)$RCSfile: fm.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1997/09/29 21:04:09 $"

#ifndef _FW_H_
#define _FW_H_

/*
* Module Name:
*   fm.h
*
* Overview:
*  This header file describes the FLOWmaster flow control module.
*
* Authors:
*   JAD - John A. DeNisco
*
* Modification History:
*   Date       Name  Description
*   22-Jun-95  JAD   Created.
*
* Description:
*
*  This module enables an external entity to force a resynchronization of
*  a range of VCs. Additionally, this module periodically resynchronizes VCs
*  according to the specified rate.
*
* Calling Sequence:
*   - tm_an2_create
*      - tm_an2_destroy
*
*/

typedef enum
   {
   CONN_VC_READY,
   CONN_RELEASE
   } NOTIFY_EVENT;

/*++
 * =====================
 * = (AN2_DRV_VC_OPEN) =
 * =====================
 *
 * Overview:
 *   The FM module calls this driver routine to open the credit resynchronization VC.
 *   The driver decides the VC's QOS.  The driver must make note of the context 
 *   that the FM module passes, because this must be returned when the driver 
 *   receives packets and delivers them to the FM module.
 *
 *   The driver never closes the VC, it is up to the FM module to do so.
 *
 * Arguments:
 *   drv_handle                - (IN)  The handle passed when the FM module
 *                                     was created.
 *
 *   tm_an2_handle             - (IN)  The handle that the driver must save 
 *                                     and return when it indicates packets to
 *                                     the FLOWmaster module.
 *
 *   an2_resync_vc             - (IN)  The VCI of the VC to open.
 *
 *   p_credit_resync_vc_handle - (OUT) Handle for this AN2 instance.
 *
 * Returns:
 *   STATUS_K_SUCCESS  - Success: See Postconditions.
 *   STATUS_K_FAILURE  - Insufficient resources to complete creation.
 *
 * Preconditions:
 *   - none
 *
 * Postconditions:
 *   - The VC has been opened.  This operation may not pend.
 *
-*/

typedef STATUS (*AN2_DRV_VC_OPEN) (HANDLE drv_handle,
                                   HANDLE tm_an2_handle,
                                   UINT32 an2_resync_vc,
                                   HANDLE *p_credit_resync_vc_handle);

/*++
 * ======================
 * = (AN2_DRV_VC_CLOSE) =
 * ======================
 *
 * Overview:
 *   The FM module calls this driver routine to close the credit 
 *   resynchronization VC.  This operation may not pend.
 *
 * Arguments:
 *   drv_handle - (IN)  The handle that was passed when the FM module was created.
 *   vc_handle  - (IN)  The handle returned when the VC was opened.
 *
 * Returns:
 *   none
 *
 * Preconditions:
 *   - The VC was previously opened.
 *
 * Postconditions:
 *   - The VC is closed.
 *
-*/

typedef void (*AN2_DRV_VC_CLOSE) (HANDLE drv_handle,
                                  HANDLE vc_handle);

/*++
 * ============================
 * = (AN2_DRV_VC_CREDITS_SET) =
 * ============================
 *
 * Overview:
 *   The FM module calls this driver routine to set the number of credits on a 
 *   range of VCs.  This occurs when the VC is initially opened or when the VC
 *   is having its credits resynchronized.
 *
 *   The FM module guarentees that a VC is stalled when this call is made.
 *
 * Arguments:
 *   drv_handle - (IN)  The handle that was passed when the FM module was
 *                      created.
 *
 *   first_vc   - (IN)  The first VC in the range of VCs for which to set 
 *                      credits.
 *
 *   last_vc    - (IN)  The last VC in the range of VCs for which to set
 *                      credits.  This value may be equal to first VC.  It
 *                      is always guaranteed to be equal to or greater than
 *                      first_vc.  The driver must loop through all VCs in
 *                      the range.  If a VC is not open, the operation must
 *                      be ignored for that VC, but carried out for all 
 *                      others.
 *
 * Returns:
 *   none
 *
 * Preconditions:
 *   - All VCs are stalled.
 *   - last_vc is always greater than or equal to first VC.
 *
 * Postconditions:
 *   - All open VCs have their credits reinitialized.
 *
-*/

typedef void (*AN2_DRV_VC_CREDITS_SET) (HANDLE  drv_handle,
                                        UINT32  first_vc,
                                        UINT32  last_vc,
                                        UINT32  credits);

/*++
 * ======================
 * = (AN2_DRV_VC_STALL) =
 * ======================
 *
 * Overview:
 *   The FM module calls this driver routine to stall a range of VCs.  The
 *   term "stall" means to prevent further packets from being transmitted on
 *   the VC, and knowing that all of the credits for that VC have been
 *   returned.  While a VC is stalled, no more packets for that VC can be put
 *   on the wire.
 *
 *   For each VC in the range, the driver must set a flag indicated that the 
 *   VC is stalled.  When the driver has completed flushing the VC (all 
 *   previously queued packets are on the wire), then the driver calls back
 *   to the FM module to indicate that the flushing has been completed.  The
 *   driver must also indicate that the flushing has completed if the VC 
 *   closes during the stall operation.
 *
 * Arguments:
 *   drv_handle - (IN)  The handle that was passed when the FM module was
 *                      created.
 *
 *   first_vc   - (IN)  The first VC in the range of VCs for which to stall.                    
 *
 *   last_vc    - (IN)  The last VC in the range of VCs for which to stall.
 *                      This value may be equal to first VC.  It
 *                      is always guaranteed to be equal to or greater than
 *                      first_vc.  The driver must loop through all VCs in
 *                      the range.  If a VC is not open, then it cannot be
 *                      stalled.
 *
 * Returns:
 *   - none
 *
 * Preconditions:
 *   - All VCs are stalled.
 *   - last_vc is always greater than or equal to first VC.
 *
 * Postconditions:
 *   - All open VCs have their credits reinitialized.
 *
-*/

typedef UINT32 (*AN2_DRV_VC_STALL) (HANDLE drv_handle,
                                    UINT32 first_vc,
                                    UINT32 last_vc);

/*++
 * ========================
 * = (AN2_DRV_VC_RESTART) =
 * ========================
 *
 * Overview:
 *   The FM module calls this driver routine to restart a range of VCs.  The
 *   term "restart" means that the driver can again transmit packets on the 
 *   VCs.  To do this, the driver will probably just have to clear a flag in
 *   the per-VC state.
 *
 *   Typically a VC is restarted just after it is opened, or after it has had
 *   its credits reset after a credit resynchronization.
 *
 * Arguments:
 *   drv_handle - (IN)  The handle that was passed when the FM module was
 *                      created.
 *
 *   first_vc   - (IN)  The first VC in the range of VCs for which to stall.                    
 *
 *   last_vc    - (IN)  The last VC in the range of VCs for which to stall.
 *                      This value may be equal to first VC.  It is always 
 *                      guaranteed to be equal to or greater than first_vc.
 *                      The driver must loop through all VCs in the range.  
 *                      If a VC is not open, then it cannot be restarted.
 *                     
 *
 * Returns:
 *   none
 *
 * Preconditions:
 *   - All VCs are stalled.
 *   - last_vc is always greater than or equal to first VC.
 *
 * Postconditions:
 *   - All open VCs are unstalled.
-*/

typedef void (*AN2_DRV_VC_RESTART) (HANDLE drv_handle,
                                    UINT32 first_vc,
                                    UINT32 last_vc);

/*++
 * ====================
 * = (AN2_DRV_VC_XMT) =
 * ====================
 *
 * Overview:
 *   The FM module calls this driver routine to transmit a packet on the 
 *   credit resychronization VC or the ILMI VC (escape packet).
 *
 * Arguments:
 *   drv_handle - (IN)  The handle that was passed when the FM module was
 *                      created.
 *
 *   vc         - (IN)  The VC on which to transmit the packet.  Either the 
 *                      credit resynchronization VC or the ILMI VC.
 *
 *   p_pkt      - (IN)  Pointer to the packet to transmit.  The driver may not
 *                      hold onto this address after it returns.
 *
 *   pkt_len    - (IN)  The number of bytes in the packet.
 *
 * Returns:
 *   STATUS_K_SUCCESS -
 *   STATUS_K_FAILURE -
 *
 * Preconditions:
 *   - The VC was opened.
 *
 * Postconditions:
 *   - The packet has been transmitted.
 *
-*/

typedef STATUS (*AN2_DRV_VC_XMT) (HANDLE  drv_handle,
                                  UINT32  vc,
                                  UINT8  *p_pkt,
                                  UINT16  pkt_len);

/*++
 * =================
 * = tm_an2_create =
 * =================
 *
 * Overview:
 *   The device driver calls this to creates a new instance of the 
 *   tm_an2 control module.
 *
 * Arguments:
 *   os_handle          - (IN)  Handle for OS utilities.
 *   local_fm_support   - (IN)  TRUE if flowmaster is supported by this NIC.
 *   max_vccs           - (IN)  The maximum number of VCI values while in FM mode.
 *   adp_rcv_buffers    - (IN)  The credits for a VC (use 20 for most apps).
 *   adp_rcv_buffers    - (IN)  The max cnt of credits assigned to a VC (use 0).
 *   ad_uid             - (IN)  The MAC address of the device.
 *   drv_vc_open        - (IN)  The driver routine to handle opening the credit resync VC.
 *   drv_vc_close       - (IN)  The driver routine to handle closing the credit resync VC.
 *   drv_vc_restart     - (IN)  The driver routine to handle restarting a VC.
 *   drv_vc_stall       - (IN)  The driver routine to handle stalling a VC.
 *   drv_vc_xmt         - (IN)  The driver routine to handle transmitting a credit resync.
 *   drv_vc_credits_set - (IN)  The driver routine to handle the setting of credits.
 *   drv_handle         - (IN)  The handle to pass on any driver callback.
 *   p_tm_an2_handle    - (OUT) Handle for this AN2 instance.
 *
 * Returns:
 *   STATUS_K_SUCCESS    - Success: See Postconditions.
 *   STATUS_K_RESOURCES  - Insufficient resources to complete creation.
 *
 * Preconditions:
 *   - none
 *
 * Postconditions:
 *   - The module is ready to run the FLOWmaster protocol.
 *
-*/

STATUS tm_an2_create (HANDLE                  os_handle,
                      BOOLEAN                 local_fm_support,
                      UINT32                  max_vccs,
                      UINT32                  adp_rcv_buffers,
                      UINT32                  adp_max_rcv_buff_cnt,
                      UINT8                   ad_uid[6],
                      AN2_DRV_VC_OPEN         drv_vc_open,
                      AN2_DRV_VC_CLOSE        drv_vc_close,
                      AN2_DRV_VC_RESTART      drv_vc_restart,
                      AN2_DRV_VC_STALL        drv_vc_stall,
                      AN2_DRV_VC_XMT          drv_vc_xmt,
                      AN2_DRV_VC_CREDITS_SET  drv_vc_credits_set,
                      HANDLE                  drv_handle,
                      HANDLE                 *p_tm_an2_handle);

/*++
 * ==================
 * = tm_an2_destroy =
 * ==================
 *
 * Overview:
 *   The device driver calls this routine to destroy an instance of this module.
 *
 * Arguments:
 *   tm_an2_handle - (IN)  Handle returned by tm_an2_create.
 *
 * Returns:
 *   None
-*/

void tm_an2_destroy (HANDLE tm_an2_handle);

/*++
 * =========================
 * = tm_an2_fm_support_set =
 * =========================
 *
 * Overview:
 *   The device driver calls this routine enable or disable local FLOWmaster
 *   support.  This routine may be called at any time, but FLOWmaster does
 *   not change state until the next link transition.
 *
 * Arguments:
 *   tm_an2_handle - (IN)  Handle returned by tm_an2_create.
 *   fm_enabled    - (IN)  The new setting of local_fm_support
 *
 * Returns:
 *   None
-*/

void tm_an2_fm_support_set (HANDLE  tm_an2_handle,
                            BOOLEAN fm_enabled);

/*+
 * =============================
 * = tm_an2_link_status_change =
 * =============================
 *
 * Overview:
 *   The device driver calls this routine whenever the link becomes available 
 *   and it receives its first packet on VC 16, or when the link goes down.
 *
 * Arguments:
 *   tm_an2_handle - (IN)  Handle returned by tm_an2_create.
 *   link_up       - (IN)  Set to TRUE if the link is now up and available.        
 *
 * Returns:
 *   None
 *
 * Preconditions -
 *   none
 *
 * Postconditions -
 *   - The credit resync VC may be setup.
 *   - The credit resync VC may be torn down.
-*/

void tm_an2_link_status_change (HANDLE  tm_an2_handle,
                                BOOLEAN link_up);

/*++
 * ====================
 * = tm_an2_vc_opened =
 * ====================
 *
 * Overview:
 *   The device driver calls this routine whenever a new VC is setup.  The
 *   caller is responsible for setting the credits on the VC.
 *
 *   Note, only call for VCs that are UBR/ABR, do NOT call for CBR VCs.
 *
 * Arguments:
 *   tm_an2_handle    - (IN)  Handle returned by tm_an2_create.
 *   vpi              - (IN)  The VPI of the VC being setup.
 *   vci              - (IN)  The VCI of the VC being setup.
 *   p_use_flowmaster - (OUT) Set to true if the VC should be opened "FLOWmaster".
 *   p_credits        - (OUT) Set to the number of credits to assign the VC.
 *
 * Returns:
 *   None
 *
 * Preconditions -
 *   none
 *
 * Postconditions -
 *   - The routine calls to set the credits for the VC.
-*/

void tm_an2_vc_opened (HANDLE   tm_an2_context,
                       UINT32   vpi,
                       UINT32   vci,
                       BOOLEAN *p_use_flowmaster,
                       UINT32  *p_credits);

/*++
 * ========================
 * = tm_an2_vc_flush_done =
 * ========================
 *
 * Overview:
 *   The device driver calls this routine whenever a new VC is setup.  This
 *   module will then the drivers "set credits" routine to set the initial 
 *   number of credits on the VC.  This callback occurs before this routine
 *   returns.
 *
 * Arguments:
 *   tm_an2_handle - (IN)  Handle returned by tm_an2_create.
 *   vc_id         - (IN)  The VCI of the VC being setup.         
 *
 * Returns:
 *   None
 *
 * Preconditions -
 *   none
 *
 * Postconditions -
 *   - The routine calls to set the credits for the VC.
-*/

void tm_an2_vc_flush_done (HANDLE tm_an2_context);

/*++
 * ===================
 * = tm_an2_pkt_rcvd =
 * ===================
 *
 * Overview:
 *   The device driver calls this routine whenever a packet is received on the
 *   credit resync VC or an escape packet is received on the ILMI VC.
 *
 * Arguments:
 *   conn_context - (IN)  Context specified when the credit resync VCI was
 *                        opened.  Pass this value for packets received on 
 *                        the credit resync VCI or the ILMI VCI (for escape).
 *
 *   vc_id        - (IN)  The VCI on which the packet was received.
 *
 *   length       - (IN)  The byte length of the received packet.
 *
 *   p_pkt        - (IN)  Pointer to the virtually contiguous receive packet.
 *                        This must be valid for the duration of this call.
 *
 * Returns:
 *   None
 *
 * Preconditions -
 *   none
 *
 * Postconditions -
 *   - The routine calls to set the credits for the VC.
-*/

void tm_an2_pkt_rcvd (HANDLE  conn_context,
                      UINT32  vc_id,
                      UINT32  length,
                      void   *p_pkt);



#endif	/* _FW_H_ */
