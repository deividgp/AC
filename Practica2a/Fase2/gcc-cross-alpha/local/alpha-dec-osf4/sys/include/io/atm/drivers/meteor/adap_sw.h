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
#pragma ident "@(#)$RCSfile: adap_sw.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:24 $"

#ifndef _ADAP_SW_H_
#define _ADAP_SW_H_

/*
* Module Name:
*   adap_sw.h
*
* Abstract:
*   This file describes the interface to the ATMworks351 adapter.
*
* Authors:
*   NCD - Nancy C. DiFonzo
*
* Modification History:
*   Date       Name  Description
*   17-May-96  NCD   Created.
*
* Description:
*   This module provides a common interface for managing the ATMworks351
*   peripheral devices.  The call sequence should be as follows, with
*   dependencies indicated by indention.
*
*             adap_create  - mandatory
*                adap_init - mandatory
*                adap_led_set - as needed
*                   adap_info_get - as needed
*                   adap_suni_init - mandatory for operation
*                      adap_suni_counter_get - recommended every 1 second
*                      adap_suni_link_check  - recommended every 1 second
*                      adap_suni_intr_enable - optional
*                adap_destroy - mandatory
*/               

/*++
* ADAP_SUNI_COUNTERS
*
* Structure that holds the latest values read from the Suni-Lite error counters
* located in the RSOP, RLOP, RPOP, RACP, and TACP blocks.
*
*    rsop_bip8    -  Number of section BIP-8 errors detected since the previous
*                    poll of the counters.
*                    
*    rlop_bip24   -  Number of line BIP-8/24 errors detected since the previous
*                    poll of the counters.
*
*    rlop_febe    -  Number of line FEBE errors detected since the previous poll
*                    of the counters.
*
*    rpop_bip8    -  Number of path BIP-8 errors detected since the previous 
*                    poll of the counters.
* 
*    rpop_febe    -  Number of path FEBE errors detected since the previous poll
*                    of the counters.
*
*    racp_chcs    -  Number of correctable HCS error events detected since the
*                    previous poll of the counters.
*
*    racp_uhcs    -  Number of uncorrectable HCS error events detected since the
*                    previous poll of the counters.
*
*    racp_rcc     -  Number of cells written into the receive FIFO since the 
*                    previous poll of the counters.
*
*    tacp_tcc     -  Number of cells read from the transmit FIFO since the
*                    previous poll of the counters.
*
--*/
 
typedef struct
   {
   UINT32          rsop_bip8;
   UINT32          rlop_bip24;
   UINT32          rlop_febe;
   UINT32          rpop_bip8;
   UINT32          rpop_febe;
   UINT32          racp_chcs;
   UINT32          racp_uhcs;
   UINT32          racp_rcc;
   UINT32          tacp_tcc;
   } ADAP_SUNI_COUNTERS;

/*++
* ADAP_RATE
*
* An enumeration to specify the desired rate for the ATMworks351.
*
--*/

typedef enum
   {
   ADAP_RATE_K_12  = 0,
   ADAP_RATE_K_25  = 1,
   ADAP_RATE_K_51  = 2,
   ADAP_RATE_K_155 = 3
   } ADAP_RATE;

/*++
* ADAP_RATE_AVAIL
*
* An enumeration to specify the rate available by this implementation
* of the ATMworks351.
*
--*/

typedef enum
   {
   ADAP_RATE_AVAIL_K_51  = 0,
   ADAP_RATE_AVAIL_K_155 = 1
   } ADAP_RATE_AVAIL;

/*++
* ADAP_LED_ID
*
* An enumeration to specify an LED.
*
--*/

typedef enum
   {
   ADAP_LED_K_LINK = 0,
   ADAP_LED_K_ADAP = 1
   } ADAP_LED_ID;

/*++
* ADAP_LED_STATE
*
* An enumeration to specify the states of the ATMworks351 LED's.
*
--*/

typedef enum
   {
   ADAP_LED_OFF   = 0,
   ADAP_LED_AMBER = 1,
   ADAP_LED_GREEN = 2
   } ADAP_LED_STATE;


/*++
* ===============
* = adap_create =
* ===============
*
* Overview:
*   This function creates an instance of this module.  This MUST be the first
*   call made to this module.  The returned handle is required by all calls to
*   this module.
*
* Arguments:
*   met_handle     - (IN)   Handle to use when calling the met_sw module.
*
*   os_handle      - (IN)   Handle to use when calling the os_utl module.
*
*   os_reg_handle  - (IN)   Handle to use when calling the os_reg module.
*
*   rate           - (IN)   Desired rate for the ATMworks351.
*
*   sdh            - (IN)   Value indicating the type of transmission service 
*                           either SDH (Synchronous Digital Hierarchy) or 
*                           SONET (Synchronous Optical Network).  True 
*                           selects SDH.
*
*   loop_timing    - (IN)   Value indicating the source of timing for the
*                           transmit section of the Suni-Lite.  0 (typical)
*                           chooses timing derived from inputs TRCLK+ and
*                           TRCLK-.  1 selects timing derived from the receiver
*                           inputs.
*
*   p_adap_handle  - (OUT)  Handle that is required for subsequent calls
*                           to this module.
*
* Returns:
*   STATUS_K_SUCCESS -   Instance created.
*   STATUS_K_RESOURCES - Insufficient resources, instance not created.
*
* Preconditions:
*   - met_create, os_create, and os_reg_create have been called.
*
* Postconditions:
*   - If success is returned, *p_adap_handle is valid.
*
* Issues:
*   none
--*/                                              

STATUS adap_create (HANDLE         met_handle,
                    HANDLE         os_handle,
                    HANDLE         os_reg_handle,
                    ADAP_RATE      rate,
                    BOOLEAN        sdh,
                    BOOLEAN        loop_timing,
                    HANDLE        *p_adap_handle);

/*++
* ================
* = adap_destroy =
* ================
*
* Overview:
*   Returns any allocated resources.  This MUST be the last call made to this
*   instance.
*
* Arguments:
*   adap_handle    - (IN)  Handle returned by adap_create.
*
* Returns:
*   none
*
* Preconditions:
*   adap_handle is valid or NULL.
*
* Postconditions:
*   adap_handle is invalid.
*
* Issues:
*   none
--*/
                                              
void adap_destroy (HANDLE adap_handle);

/*++
* ===================
* = adap_soft_reset =
* ===================
*
* Overview:
*   This routine issues a soft reset to the Meteor chip of the ATMworks351 
*   and performs initialization to all Meteor and peripheral devices corrupted
*   during the reset.  .  
*
* Arguments:
*   adap_handle    - (IN)  Handle returned by adap_create.
*
* Returns:
*   STATUS_K_SUCCESS - The METEOR chip, portions of the SRAM necessary for
*                      operation, and the Suni-Lite chip, have been initialized.
*
*   STATUS_K_FAILURE - Some part the initialization did not work.
*
* Preconditions:
*   adap_handle is valid.
*
* Postconditions:
*   none
*
* Issues:
*   none
--*/
                                              
STATUS adap_soft_reset (HANDLE adap_handle);

/*++
* =========================
* = adap_loopback_mode_en =
* =========================
*
* Overview:
*  This routine provides the caller with a standard mechanism for enabling
*  loopback.
*
* Arguments:
*   adap_handle    - (IN)  Handle returned by adap_create.
*
* Returns:
*  none
*
* Preconditions:
*  none
*
* Postconditions:
*  - The ATMworks351 Meteor is put into loopback mode.
*
* Issues:
--*/

void adap_loopback_mode_en (HANDLE adap_handle);

/*++
* ==========================
* = adap_loopback_mode_dis =
* ==========================
*
* Overview:
*  This routine provides the caller with a standard mechanism for disabling
*  loopback.
*
* Arguments:
*   adap_handle    - (IN)  Handle returned by adap_create.
*
* Returns:
*  none
*
* Preconditions:
*  none
*
* Postconditions:
*  - The ATMworks351 Meteor is taken out of loopback mode.
*
* Issues:
--*/

void adap_loopback_mode_dis (HANDLE adap_handle);

/*++
* =================
* = adap_prf_init =
* =================
*
* Overview:
*   This routine initializes the module components of the ATMworks351 
*   excluding the Meteor chip and SRAM.  Included are:  the Suni-Lite chip, 
*   and the LED peripheral register.  
*
*   This module also verifies the EEROM for data integrity, determines
*   the number of Ethernet addresses supported by the board, and initializes
*   the Base Ethernet Address.
*
* Arguments:
*   adap_handle    - (IN)  Handle returned by adap_create.
*
* Returns:             
*   STATUS_K_SUCCESS     - Peripheral, Suni-Lite, LED Register are initialized 
*                          and the EEROM is verified.
*
*   STATUS_K_EEROM_ERROR - The EEROM verification failed.
*
*   STATUS_K_FAILURE     - Either the Suni-Lite or LED Register initialization 
*                          failed.
* Preconditions:
*   adap_handle is valid or NULL.
*
* Postconditions:
*   Adapter peripheral devices are ready for operation.
*
* Issues
*   none
--*/
                                              
STATUS adap_prf_init (HANDLE adap_handle);

/*++
* =================
* = adap_info_get =
* =================
*
* Overview:
*   This function returns the Ethernet Base Address, total number
*   of addresses supported, and the Module Revision ID.  
*
*   The remaining Ethernet addresses are located immediately following
*   the base address, and can easily be derived by incrementing the lowest
*   byte of the base address by 1 for each address supported.  Note, it is
*   only necessary to increment the lowest byte since the DECnet LAN Node 
*   Product Functional Specification states that the last byte of the 
*   ending address is guranteed to be larger than the last byte of the base 
*   address.
*
* Arguments:
*   adap_handle      - (IN)  Handle returned by adap_create.
*
*   base_lan_addr    - (OUT) 6 byte Base Ethernet address.
*
*   p_lan_addr_total - (OUT) Number of Ethernet addresses supported.
*
*   p_revision       - (OUT) Module revision ID.
*
* Returns:
*   None.
*
* Preconditions:
*   - adap_init was called.
*
* Postconditions:
*   - Caller has the starting Ethernet Address, total number of addresses and
*     Module Identification value.
*
* Issues:
*   None
--*/                                              

void adap_info_get (HANDLE   adap_handle, 
                    UINT8    base_lan_addr[6],
                    UINT16  *p_lan_addr_total, 
                    UINT8   *p_revision);

/*++
* ==================
* = adap_suni_init =
* ==================
*
* Overview:
*   This routine resets and initializes the Suni-Lite.  All registers requiring
*   non-default values are initialized for ATMworks351 operation.  Two values, 
*   SDH and LOOPT, are user input during the adap_create call.   
*
* Arguments:
*   adap_handle    - (IN)   Handle returned by adap_create.
*
* Returns:
*   STATUS_K_SUCCESS  -  The Suni-Lite chip has been initialized for the
*                        ATMworks351 implementation.
*
*   STATUS_K_FAILURE  -  An error occurred during the Suni-Lite initialization.  
*
* Preconditions:
*   - adap_create has been called specifying the values for SDH and LOOPT 
*
* Postconditions:
*   - If success is returned, the Suni-Lite is initialized and ready to
*     receive for operation.
*
* Issues:
*   None.
--*/

STATUS adap_suni_init (HANDLE adap_handle);

/*++
* =====================
* = adap_sun_cntr_get =
* =====================
*
* Overview:
*   This routine causes the values of the internal Suni-Lite error/event 
*   counters in the RSOP, RLOP, RPOP, RACP, and TACP blocks to be loaded 
*   into their associated registers.  The values are read, which resets
*   the values to 0, and placed into the user provided suni counter data
*   structure 
*
* Arguments:
*   adap_handle     - (IN) The handle returned by adap_create.
*
*   p_suni_counters - (IN) Pointer to a structure to hold values from
*                          the Suni-Lite counters.
*
* Returns:
*   STATUS_K_SUCCESS - The Suni-Lite Counter structure contains the current 
*                      values for the Suni-Lite internal errors.
*
*   STATUS_K_FAILURE - The Suni-Lite error counters were not read.
*
* Preconditions:
*   - adap_suni_init has been called.
*
* Postconditions:
*   - Suni Counters structure is updated with the latest error counts.
*
* Issues:
*   None.
--*/

STATUS adap_suni_cntr_get (HANDLE              adap_handle,
                           ADAP_SUNI_COUNTERS *p_suni_counters);

/*++
* ========================
* = adap_suni_link_check =
* ========================
*
* Overview:
*   This routine reads all registers on the Suni-Lite which may indicate that
*   the link is down.  This routine should be called once per second.
*
* Arguments:
*   adap_handle     - (IN) The handle returned by adap_create.
*
* Returns:
*   STATUS_K_SUCCESS - No errors have been found.
*
*   STATUS_K_FAILURE - An error has been found indicating the link is down.
*
* Preconditions:
*   None.
*
* Postconditions:
*   None
*
* Issues:
*   None.
--*/

STATUS adap_suni_link_check (HANDLE adap_handle);

/*++
* ================
* = adap_led_set =
* ================
*
* Overview:
*   This routine provides control to both the Adapter and Link LED's of
*   the ATMworks351.  Each LED can be set to one of three states:  OFF,
*   GREEN, or AMBER.
*
*   The following table describes the Led states:
*
*            \        Adapter Status        |             Link Status
*              \ ---------------------------------------------------------------
*               |                           |
*     OFF  (00) |                           |    Port waiting for connection 
*               |                           |
*    GREEN (01) |   Diagnostics passed,     |    Port Active (connected,
*               |   Module operational      |      link established)
*               |                           |
*    AMBER (10) |   Running Diagnostics     |    Port Inactive due to errors
*               |                           |
*   
* Arguments:
*   adap_handle  - (IN) Handle returned by adap_create.
*
*   led_id       - (IN) Identifier for which LED to write.
*
*   led_value    - (IN) New LED state. 
*                        
* Returns:          
*   STATUS_K_SUCCESS - Led was set to new value.
*
*   STATUS_K_FAILURE - Peephole write failed, LED state was not changed.
*
* Preconditions:
*   None.
*
* Postconditions:
*   None
*
* Issues:
*   None.
--*/

STATUS adap_led_set (HANDLE          adap_handle,
                     ADAP_LED_ID     led_id,
                     ADAP_LED_STATE  led_value);


/*++
* =========================
* = adap_suni_intr_enable =
* =========================
*
* Overview:
*   This routine enables all interrupts that signal events which may require
*   attention by Meteor.  This routine is provided to aid an interrupt driven
*   method for determining that the Suni-Lite has experienced an error which 
*   may indicate the link state has changed.  This should only be used as an 
*   alternative to periodically polling the registers with the 
*   adap_suni_link_check routine. 
*
* Arguments:
*   adap_handle  - (IN) Handle returned by adap_create.
*                        
* Returns:          
*   STATUS_K_SUCCESS - Suni-Lite interrupts are enabled.
*
*   STATUS_K_FAILURE - At least one peephole write failed.  Some interrupts 
*                      are not enabled.
* Preconditions:
*   None.
*
* Postconditions:
*   None
*
* Issues:
*   Not sure if this should be provided or not.  Do we want to encourage/force
*   polling?
--*/

STATUS adap_suni_intr_enable (HANDLE adap_handle);

#endif	/* _ADAP_SW_H_ */
