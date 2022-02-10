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
#pragma ident "@(#)$RCSfile: adap_hw.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:19 $"

#ifndef _ADAP_HW_H_
#define _ADAP_HW_H_

/*
* Module Name:
*   adap_hw.h
*
* Abstract:
*   This file describes the registers and data structures
*   for the ATMworks 351 hardware interface.
*
* Authors:
*   NCD
*
* Modification History:
*   Date       Name  Description
*   12-JUN-96  NCD   Created.
*   11-Apr-97  PAE   Modified the following constants.      New      Org.
*                    #define ADAP_LEDS_K_ADAP_OFF           0        1
*                    #define ADAP_LEDS_K_ADAP_DIAG          1        2
*                    #define ADAP_LEDS_K_ADAP_UP            2        1
*                
*                    #define ADAP_LEDS_K_LINK_WAIT          0        0
*                    #define ADAP_LEDS_K_LINK_ERROR         1        2
*                    #define ADAP_LEDS_K_LINK_UP            2        1
*              
*                    These sharp defines now align with the actual LED
*                    operation and the adap_led_set function in adap_sw.c
*
*
* Description:
*   This file contains the hardware definitions for the ATMworks 351.  Included are the
*   register offsets, bit fields, shift values, and some constants which
*   are used by software to access the chip.
*
*   Bit definitions are avoided since they presume a particular endianess which
*   may not be found on all host systems.
* 
* Conventions:
*   xxxx_M_yyyy - Bit Mask Field for a portion of a value
*   xxxx_V_yyyy - Shift Value necessary to right justify a field
*   xxxx_O_yyyy - Address Offset 
*   xxxx_K_yyyy - Constant      
*     
*   where:   xxxx = destination/source
*            yyyy = bit(s) identifier name
*  
* Issues:
*   Need to add defaults for each register.
*/

#define ADAP_O_EEROM          0x00000040     /* PH_CMD<7:6> = 01              */
 
#define ADAP_M_EEROM          0x0000000F     /* Only PH_DATA<3:0> used        */

#define ADAP_SUNI_ACCESS      0x00000080     /* Bit 7 set in PH CMD for SUNI  */

/* Peephole data bits for controling the EEROM. */

#define ADAP_EEROM_M_DO       0x00000008     /* Data Out.                     */
#define ADAP_EEROM_M_CS       0x00000004     /* Chip select.                  */
#define ADAP_EEROM_M_DI       0x00000002     /* Data In.                      */
#define ADAP_EEROM_M_SK       0x00000001     /* Serial Clock.                 */

/* Write these values to the peephole data register to affect the EEPROM. */

#define ADAP_EEROM_K_ONE      (ADAP_EEROM_M_CS | ADAP_EEROM_M_DI)
#define ADAP_EEROM_K_ONE_CLK  (ADAP_EEROM_M_CS | ADAP_EEROM_M_DI | ADAP_EEROM_M_SK)
#define ADAP_EEROM_K_ZERO     (ADAP_EEROM_M_CS)
#define ADAP_EEROM_K_ZERO_CLK (ADAP_EEROM_M_CS | ADAP_EEROM_M_SK)

#define ADAP_EEROM_K_CS_OFF   0
#define ADAP_EEROM_K_CS       ADAP_EEROM_M_CS /* Turn On chip select           */
#define ADAP_EEROM_K_CLK      ADAP_EEROM_M_SK /* DI = 0, CS = 0, Clock = 1     */

#define ADAP_EEROM_K_BYTE_LEN         66     /* 66 bytes of meaningful data   */
#define ADAP_EEROM_K_CRC_0            64     /* Byte index of CRC 0           */
#define ADAP_EEROM_K_CRC_1            65     /* Byte index of CRC 1           */
#define ADAP_EEROM_K_LAN_ADDR_LEN      6     /* Ethernet address is 6 bytes   */

#define ADAP_O_PCI_DEV_ID_LO  0x00000000     /* PH_CMD<7:5>=000, <4:0>=00000  */
#define ADAP_O_PCI_DEV_ID_HI  0x00000001     /* PH_CMD<7:5>=000, <4:0>=00001  */
#define ADAP_O_PCI_VEND_ID_LO 0x00000002     /* PH_CMD<7:5>=000, <4:0>=00010  */
#define ADAP_O_PCI_VEND_ID_HI 0x00000003     /* PH_CMD<7:5>=000, <4:0>=00011  */

#define ADAP_PCI_M_RATE       0x00000040     /* Rate                          */
#define ADAP_PCI_M_MEDIA      0x00000020     /* Media.                        */
#define ADAP_PCI_M_SMF_MMF    0x00000010     /* MMF or SMF                    */
#define ADAP_PCI_M_REVISION   0x00000007     /* Module Revison.               */

#define ADAP_O_LEDS           0x00000020     /* PH_CMD<7:5> = 001             */

#define ADAP_LEDS_M_RATE       0x000000C0    /* Rate                          */
#define ADAP_LEDS_M_TWIST_LOOP 0x00000020    /* Twister Loopback              */
#define ADAP_LEDS_M_XMT_EN     0x00000010    /* XMT Enable (MMF/UTP power)    */
#define ADAP_LEDS_M_ADAP       0x0000000C    /* Adapter LED Encoding          */
#define ADAP_LEDS_M_LINK       0x00000003    /* Link LED Encoding             */

#define ADAP_LEDS_K_ADAPTER            1
#define ADAP_LEDS_K_LINK               0


#define ADAP_LEDS_K_ADAP_OFF           0
#define ADAP_LEDS_K_ADAP_DIAG          1
#define ADAP_LEDS_K_ADAP_UP            2     
                
#define ADAP_LEDS_K_LINK_WAIT          0
#define ADAP_LEDS_K_LINK_ERROR         1
#define ADAP_LEDS_K_LINK_UP            2     

#define ADAP_LEDS_K_LOOP_DIS           0
#define ADAP_LEDS_K_XMT_DIS            0

/* Define the subsystem Vendor ID. */

#define ADAP_K_DEC_SUBSYS_VENDOR_ID 0x1011    /* Digital */

/* Physical media interface type, (bit 5 of subsystem ID word). */

#define ADAP_K_PHYS_IF_MMF      0x0020
#define ADAP_K_PHYS_IF_UTP      0x0000


#endif	/* _ADAP_HW_H_ */
