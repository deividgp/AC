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
#pragma ident "@(#)$RCSfile: met_hw.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:45 $"

#ifndef _MET_HW_H_
#define _MET_HW_H_

/*
* Module Name:
*   met_hw.h
*
* Abstract:
*   This file describes the registers and data structures
*   for the Meteor hardware interface.
*
* Authors:
*   NCD
*
* Modification History:
*   Date       Name  Description
*   22-Feb-96  NCD   Created.
*
* Description:
*   This file contains the hardware definitions for Meteor.  Included are the
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
*   where:   xxxx = Meteor destination/source
*            yyyy = bit(s) identifier name
*  
* Issues:
*   Need to add defaults for each register.
*/
 
#define MET_K_VENDOR_ID       0x102F         /* Toshiba's vendor code.      */

#define MET_K_1_DEVICE_ID     0x0020         /* Meteor, 1K or 4K.           */
#define MET_K_2_DEVICE_ID     0x0021         /* Meteor, 4K, has PHY framer. */

/* The 4K ASIC has a PCI revision byte with the value 1. */

#define MET_K_REV_ID_1K 0
#define MET_K_REV_ID_4K 1

/* CSR definitions.  These locations are directly accessed in PCI space        */
                                                                                          
/* Tx_pending_Slot Registers (Even Addresses)                                  */

#define MET_XMT_PEND_M_RSVD_0  0x80000000     /* Reserved 0                    */
#define MET_XMT_PEND_M_RAW     0x40000000     /* Raw                           */
#define MET_XMT_PEND_M_IDL     0x20000000     /* Idle                          */
#define MET_XMT_PEND_M_MGT     0x10000000     /* Management                    */
#define MET_XMT_PEND_M_RSVD_1  0x0C000000     /* Reserved                      */
#define MET_XMT_PEND_M_VC      0x03FF0000     /* VC                            */
#define MET_XMT_PEND_M_CRC     0x00008000     /* CRC10 Enable                  */
#define MET_XMT_PEND_M_EOP     0x00004000     /* EOP                           */
#define MET_XMT_PEND_M_SZ      0x00003FFF     /* Slot Size                     */

#define MET_XMT_PEND_V_RSVD_0          31     /* Reserved 0 Shift              */
#define MET_XMT_PEND_V_RAW             30     /* Raw Shift                     */
#define MET_XMT_PEND_V_IDL             29     /* Idle Shift                    */
#define MET_XMT_PEND_V_MGT             28     /* Management Shift              */
#define MET_XMT_PEND_V_RSVD_1          26     /* Reserved 1 Shift              */
#define MET_XMT_PEND_V_VC              16     /* VC Shift                      */
#define MET_XMT_PEND_V_CRC             15     /* CRC10 Enable Shift            */
#define MET_XMT_PEND_V_EOP             14     /* EOP Shift                     */
#define MET_XMT_PEND_V_SZ               0     /* Slot Size Shift               */

#define MET_XMT_PEND_K_RAW              1     /* Raw Cell indication           */
#define MET_XMT_PEND_K_IDL              1     /* Idle Cell indication          */
#define MET_XMT_PEND_K_MGT              1     /* OAM F4 or F5 Cell indication  */
#define MET_XMT_PEND_K_CRC              1     /* CRC10 Enable                  */
#define MET_XMT_PEND_K_EOP              1     /* EOP indication                */

#define MET_XMT_PEND_K_NOT_RAW          0     /* Raw Cell indication           */
#define MET_XMT_PEND_K_NOT_IDL          0     /* Idle Cell indication          */
#define MET_XMT_PEND_K_NOT_MGT          0     /* OAM F4 or F5 Cell indication  */
#define MET_XMT_PEND_K_NOT_CRC          0     /* CRC10 Enable                  */
#define MET_XMT_PEND_K_NOT_EOP          0     /* EOP indication                */


/* Tx_pending_Slot Registers (Odd Addresses)                                   */

#define MET_XMT_PEND_M_ADDR    0xFFFFFFFF     /* Base Address                  */

#define MET_XMT_PEND_V_ADDR             0     /* Base Address Shift            */

/* Rx_Pending_Slot Registers                                                   */

#define MET_RCV_PEND_M_TAG     0xFFFC0000     /* Slot Tag                      */
#define MET_RCV_PEND_M_TYPE    0x00030000     /* Slot Type                     */
#define MET_RCV_PEND_M_RSVD_0  0x0000F000     /* Reserved 0                    */
#define MET_RCV_PEND_M_VC      0x00000FFF     /* VC                            */

#define MET_RCV_PEND_V_TAG             18     /* Slot Tag                      */
#define MET_RCV_PEND_V_TYPE            16     /* Slot Type                     */
#define MET_RCV_PEND_V_RSVD_0          12     /* Reserved 0                    */
#define MET_RCV_PEND_V_VC               0     /* VC                            */

#define MET_RCV_PEND_K_SMALL            0     /* Slot Type - Small             */
#define MET_RCV_PEND_K_BIG              1     /* Slot Type - Big               */
#define MET_RCV_PEND_K_RAW              2     /* Slot Type - Raw               */

#define MET_RCV_PEND_M_ADDR    0xFFFFFFFC     /* Base Address                  */

#define MET_RCV_PEND_V_ADDR             2     /* Base Address                  */ 


/* Meteor Control Register 1                                                   */

#define MET_CTRL_1_M_RSVD      0xFE000000     /* Reserved                      */
#define MET_CTRL_1_M_MRM_SEL   0x01000000     /* MRL or MRM select             */
#define MET_CTRL_1_M_MRM_MRL_DIS 0x00800000   /* PCI MRL or MRM disable        */
#define MET_CTRL_1_M_SW_ABR    0x00400000     /* Software ABR Flow Control Enb */
#define MET_CTRL_1_M_CBR_SEL   0x00200000     /* CBR Schedule Table Select     */
#define MET_CTRL_1_M_FM_RM     0x00100000     /* Flowmaster ABR RM cell enable */
#define MET_CTRL_1_M_FM_RSNC   0x00080000     /* Flowmaster Credit Resync. Req.*/
#define MET_CTRL_1_M_FM_EN     0x00040000     /* Flowmaster Control Enable     */
#define MET_CTRL_1_M_SWAP_DATA 0x00020000     /* Xmt and Rcv Data Byte Swap    */
#define MET_CTRL_1_M_SWAP_LTRL 0x00010000     /* Literal Byte Swap             */
#define MET_CTRL_1_M_64K       0x00008000     /* 64K Mode                      */
#define MET_CTRL_1_M_VC_MODE   0x00006000     /* VC's supported                */
#define MET_CTRL_1_M_VC_MAP    0x00001C00     /* VPI/VCI Mapping               */
#define MET_CTRL_1_M_XMT_EN    0x00000200     /* XMT Enable                    */
#define MET_CTRL_1_M_PHY_IF_RESET 0x00000100  /* Phy Interface Reset           */
#define MET_CTRL_1_M_CELL      0x00000080     /* Phy Cell Mode Enable          */
#define MET_CTRL_1_M_PHY_CHIP_RESET 0x00000040 /* Phy Chip Reset               */
#define MET_CTRL_1_M_GFC_SGNL  0x00000020     /* GFC Signal Detect             */
#define MET_CTRL_1_M_PHY_INT   0x00000010     /* Phy Int High                  */
#define MET_CTRL_1_M_PHY_LOOP  0x00000008     /* Phy Loopback Enable           */
#define MET_CTRL_1_M_GFC       0x00000004     /* GFC Flow Control Enable       */
#define MET_CTRL_1_M_GFC_A     0x00000002     /* GFC A Flow Control Select     */
#define MET_CTRL_1_M_RCV_EN    0x00000001     /* Receive Enable                */

#define MET_CTRL_1_V_RSVD              25     /* Reserved                      */
#define MET_CTRL_1_V_MRM_SEL           24     /* MRL or MRM select             */
#define MET_CTRL_1_V_MRM_MRL_DIS       23     /* PCI MRL or MRM disable        */
#define MET_CTRL_1_V_SW_ABR            22     /* Software ABR Flow Control     */
#define MET_CTRL_1_V_CBR_SEL           21     /* CBR Schedule Table Select     */
#define MET_CTRL_1_V_FM_RM             20     /* Flowmaster ABR RM cell enable */
#define MET_CTRL_1_V_FM_RSNC           19     /* Flowmaster Credit Resync.     */
#define MET_CTRL_1_V_FM_EN             18     /* Flowmaster Control Enable     */
#define MET_CTRL_1_V_SWAP_DATA         17     /* Xmt and Rcv Data Byte Swap    */
#define MET_CTRL_1_V_SWAP_LTRL         16     /* Literal Byte Swap             */
#define MET_CTRL_1_V_64K               15     /* 64K Mode                      */
#define MET_CTRL_1_V_VC_MODE           14     /* VC's supported Shift          */
#define MET_CTRL_1_V_VC_MAP            10     /* VPI/VCI Mapping Shift         */
#define MET_CTRL_1_V_XMT_EN             9     /* XMT Enable Shift              */
#define MET_CTRL_1_V_PHY_IF_RESET       8     /* Phy Interface Reset           */
#define MET_CTRL_1_V_CELL               7     /* Phy Cell Mode Enable Shift    */
#define MET_CTRL_1_V_PHY_CHIP_RESET     6     /* Phy Chip Reset Shift          */
#define MET_CTRL_1_V_GFC_SGNL           5     /* GFC Signal Detect             */
#define MET_CTRL_1_V_PHY_INT            4     /* Phy Int High Shift            */
#define MET_CTRL_1_V_PHY_LOOP           3     /* Phy Loopback Enable Shift     */
#define MET_CTRL_1_V_GFC                2     /* GFC Flow Control Enable Shift */
#define MET_CTRL_1_V_GFC_A              1     /* GFC A Flow Control Select     */
#define MET_CTRL_1_V_RCV_EN             0     /* Receive Enable Shift          */

#define MET_CTRL_1_K_VC_MODE_256        0
#define MET_CTRL_1_K_VC_MODE_1K         1
#define MET_CTRL_1_K_CBR_TBL_1          0
#define MET_CTRL_1_K_CBR_TBL_2          1
#define MET_CTRL_1_K_RCV_EN             1 
#define MET_CTRL_1_K_XMT_EN             1
#define MET_CTRL_1_K_XMT_DIS            0
#define MET_CTRL_1_K_XMT_ENB            1
#define MET_CTRL_1_K_PHY_RCV_DIS        0
#define MET_CTRL_1_K_PHY_RCV_ENB        1
#define MET_CTRL_1_K_PHY_IF_RESET_SET   1
#define MET_CTRL_1_K_PHY_IF_RESET_CLR   0
#define MET_CTRL_1_K_PHY_CHIP_RESET_SET 1
#define MET_CTRL_1_K_PHY_CHIP_RESET_CLR 0
#define MET_CTRL_1_K_PHY_LOOP_EN        1
#define MET_CTRL_1_K_PHY_LOOP_DIS       0

/* Meteor Control 2.                                                           */

#define MET_CTRL_2_M_RAW_HOLD  0xC0000000     /* Receive Raw Report Holdoff    */
#define MET_CTRL_2_M_CONGST    0x20000000     /* Congestion CI Enable          */
#define MET_CTRL_2_M_BIG_CI    0x10000000     /* Big Slot CI Enable            */
#define MET_CTRL_2_M_SML_CI    0x08000000     /* Small Slot CI Enable          */
#define MET_CTRL_2_M_RAW_CI    0x04000000     /* Raw Slot CI Enable            */
#define MET_CTRL_2_M_BSL_TH    0x03000000     /* FIFO Int. Lev. Big Slot Low   */
#define MET_CTRL_2_M_SSL_TH    0x00C00000     /* FIFO Int. Lev. Small Slot Low */
#define MET_CTRL_2_M_RSL_TH    0x00300000     /* FIFO Int. Lev. Raw Slot Low   */
#define MET_CTRL_2_M_BIG_SZ    0x000E0000     /* Big Slot Size                 */
#define MET_CTRL_2_M_SML_SZ    0x0001FF00     /* Small Slot Size               */
#define MET_CTRL_2_M_RATO      0x000000F0     /* Reassembly Time Out           */
#define MET_CTRL_2_M_BAD_RM_DMA_EN 0x00000008 /* Receive Bad RM DMA Enable     */                    */
#define MET_CTRL_2_M_AAL5_16   0x00000004     /* AAL5 16k Limit                */
#define MET_CTRL_2_M_EFCI      0x00000002     /* EFCI Logical Or               */
#define MET_CTRL_2_M_RESET     0x00000001     /* Soft Reset                    */

#define MET_CTRL_2_V_RAW_HOLD          30     /* Receive Raw Report Holdoff    */
#define MET_CTRL_2_V_CONGST            29     /* Congestion CI Enable Shift    */
#define MET_CTRL_2_V_BIG_CI            28     /* Big Slot CI Enable Shift      */
#define MET_CTRL_2_V_SML_CI            27     /* Small Slot CI Enable Shift    */
#define MET_CTRL_2_V_RAW_CI                   /* Raw Slot CI Enable Shift      */
#define MET_CTRL_2_V_BSL_TH            24     /* FIFO Level for Big Slot Low   */
                                              /*  Int. Shift                   */
#define MET_CTRL_2_V_SSL_TH            22     /* FIFO Level for Small Slot Low */
                                              /*  Int. Shift                   */
#define MET_CTRL_2_V_RSL_TH            20     /* FIFO Level for Raw Slot Low   */
                                              /*  Int. Shift                   */
#define MET_CTRL_2_V_BIG_SZ            17     /* Big Slot Size Shift           */
#define MET_CTRL_2_V_SML_SZ             8     /* Small Slot Size Shift         */
#define MET_CTRL_2_V_RATO               4     /* Reassembly Time Out Shift     */
#define MET_CTRL_2_V_BAD_RM_DMA_EN      3     /* Receive Bad RM DMA Enable     */
#define MET_CTRL_2_V_AAL5_16            2     /* AAL5 16k Limit Shift          */
#define MET_CTRL_2_V_EFCI               1     /* EFCI Logical Or Shift         */
#define MET_CTRL_2_V_RESET              0     /* Soft Reset Shift              */

#define MET_CTRL_2_K_SML_SZ_MIN        16     /* Small Slot Size Minimum       */
#define MET_CTRL_2_K_SML_SZ_MAX       512     /* Small Slot Size Maximum       */

#define MET_CTRL_2_K_RATO_MIN           2     /* Reassembly Time Out Minumum   */
#define MET_CTRL_2_K_RATO_MAX          15     /* Reassembly Time Out Maximum   */
#define MET_CTRL_2_K_RATO_DISABLE       0     /* Reassembly Time Out Disable   */

#define MET_CTRL_2_K_NOT_RESET          0     /* Not Reset                     */

/* Interrupt Status.                                                           */

#define MET_INT_ST_M_RSVD      0xFFE00000     /* Reserved                      */
#define MET_INT_ST_M_XMT_FTL   0x00100000     /* XmtFatal Error                */
#define MET_INT_ST_M_PCI       0x00080000     /* PCI Fatal Error               */
#define MET_INT_ST_M_PHY       0x00040000     /* Phy Fatal Error               */
#define MET_INT_ST_M_PH_DONE   0x00020000     /* Peep Hole Cycle Done          */
#define MET_INT_ST_M_PH_ERR    0x00010000     /* Peep Hole Cycle Error         */
#define MET_INT_ST_M_HOST      0x00008000     /* Host Access Error             */
#define MET_INT_ST_M_XMT_UN    0x00004000     /* XmtFree Slot Underflow        */
#define MET_INT_ST_M_XMT_IOC   0x00002000     /* XmtInterrupt on Completion    */
#define MET_INT_ST_M_FM_RSYNC  0x00001000     /* Flowmaster Rsync. Done        */
#define MET_INT_ST_M_RCV_FR_OV 0x00000800     /* Rcv Free Slot FIFO Overflow   */
#define MET_INT_ST_M_RCV_DT_OV 0x00000400     /* Rcv Data   Overflow        */
#define MET_INT_ST_M_RCV_NBS   0x00000200     /* Rcv No Big Slots              */
#define MET_INT_ST_M_RCV_NSS   0x00000100     /* Rcv No Small Slots            */
#define MET_INT_ST_M_RCV_NRS   0x00000080     /* Rcv No Raw Slots              */
#define MET_INT_ST_M_RCV_BSL   0x00000040     /* Rcv Big Slots Low             */
#define MET_INT_ST_M_RCV_SSL   0x00000020     /* Rcv Small Slots Low           */
#define MET_INT_ST_M_RCV_RSL   0x00000010     /* Rcv Raw Slots Low             */
#define MET_INT_ST_M_RCV_NOP   0x00000008     /* Rcv Unopened VC               */
#define MET_INT_ST_M_RCV_U_VC  0x00000004     /* Rcv Unknown VC                */
#define MET_INT_ST_M_RCV_U_ACK 0x00000002     /* Rcv Unknown Ack               */
#define MET_INT_ST_M_RCV_IOC   0x00000001     /* Rcv IOC                       */

#define MET_INT_ST_V_RSVD              21     /* Reserved                      */
#define MET_INT_ST_V_XMT_FTL           20     /* XmtFatal Error Shift          */
#define MET_INT_ST_V_PCI               19     /* PCI Fatal Error  Shift        */
#define MET_INT_ST_V_PHY               18     /* Phy Fatal Error Shift         */
#define MET_INT_ST_V_PH_DONE           17     /* Peep Hole Cycle Done Shift    */
#define MET_INT_ST_V_PH_ERR            16     /* Peep Hole Cycle Error  Shift  */
#define MET_INT_ST_V_HOST              15     /* Host Access Error Shift       */
#define MET_INT_ST_V_XMT_UN            14     /* XmtFree Slot Underflow Shift  */
#define MET_INT_ST_V_XMT_IOC           13     /* XmtInterrupt on Completion    */ 
#define MET_INT_ST_V_FM_RSYNC          12     /* Flowmaster Rsync. Done Shift  */
#define MET_INT_ST_V_RCV_FR_OV         11     /* Rcv Free Slot FIFO Overflow   */
#define MET_INT_ST_V_RCV_DT_OV         10     /* Rcv Data FIFO Overflow Shift  */
#define MET_INT_ST_V_RCV_NBS            9     /* Rcv No Big Slots Shift        */
#define MET_INT_ST_V_RCV_NSS            8     /* Rcv No Small Slots Shift      */
#define MET_INT_ST_V_RCV_NRS            7     /* Rcv No Raw Slots Shift        */
#define MET_INT_ST_V_RCV_BSL            6     /* Rcv Big Slots Low Shift       */
#define MET_INT_ST_V_RCV_SSL            5     /* Rcv Small Slots Low Shift     */
#define MET_INT_ST_V_RCV_RSL            4     /* Rcv Raw Slots Low Shift       */
#define MET_INT_ST_V_XMT_NOP            3     /* Rcv Unopened VC Shift         */
#define MET_INT_ST_V_RCV_U_VC           2     /* Rcv Unknown VC Shift          */
#define MET_INT_ST_V_RCV_U_ACK          1     /* Rcv Unknown Ack Shift         */
#define MET_INT_ST_V_RCV_IOC            0     /* Rcv IOC Shift                 */

/* Interrupt Enable.                                                           */

#define MET_INT_EN_M_RSVD      0xFFE00000     /* Reserved                      */
#define MET_INT_EN_M_XMT_FTL   0x00100000     /* XmtFatal Error Enable         */
#define MET_INT_EN_M_PCI       0x00080000     /* PCI Fatal Error Enable        */
#define MET_INT_EN_M_PHY       0x00040000     /* Phy Fatal Error Enable        */
#define MET_INT_EN_M_PH_DONE   0x00020000     /* Peep Hole Cycle Enable Done   */
#define MET_INT_EN_M_PH_ERR    0x00010000     /* Peep Hole Cycle Error Enable  */
#define MET_INT_EN_M_HOST      0x00008000     /* Host Access Error Enable      */
#define MET_INT_EN_M_XMT_UN    0x00004000     /* XmtFree Slot Underflow Enable */
#define MET_INT_EN_M_XMT_IOC   0x00002000     /* XmtInterrupt on Completion    */
#define MET_INT_EN_M_FM_RSYNC  0x00001000     /* Flowmaster Rsync. Done Enable */
#define MET_INT_EN_M_RCV_FR_OV 0x00000800     /* Rcv Free Slot FIFO Overflow   */
#define MET_INT_EN_M_RCV_DT_OV 0x00000400     /* Rcv Data FIFO Overflow Enable */
#define MET_INT_EN_M_RCV_NBS   0x00000200     /* Rcv No Big Slots Enable       */
#define MET_INT_EN_M_RCV_NSS   0x00000100     /* Rcv No Small Slots Enable     */
#define MET_INT_EN_M_RCV_NRS   0x00000080     /* Rcv No Raw Slots Enable       */
#define MET_INT_EN_M_RCV_BSL   0x00000040     /* Rcv Big Slots Low Enable      */
#define MET_INT_EN_M_RCV_SSL   0x00000020     /* Rcv Small Slots Low Enable    */
#define MET_INT_EN_M_RCV_RSL   0x00000010     /* Rcv Raw Slots Low Enable      */
#define MET_INT_EN_M_RCV_NOP   0x00000008     /* Rcv Unopened VC Enable        */
#define MET_INT_EN_M_RCV_U_VC  0x00000004     /* Rcv Unknown VC Enable         */
#define MET_INT_EN_M_RCV_U_ACK 0x00000002     /* Rcv Unknown Ack Enable        */
#define MET_INT_EN_M_RCV_IOC   0x00000001     /* Rcv IOC Enable                */

#define MET_INT_EN_V_RSVD              21     /* Reserved                      */
#define MET_INT_EN_V_XMT_FTL           20     /* XmtFatal Error Enable Shift   */
#define MET_INT_EN_V_PCI               19     /* PCI Fatal Error  Enable Shift */
#define MET_INT_EN_V_PHY               18     /* Phy Fatal Error Enable Shift  */
#define MET_INT_EN_V_PH_DONE           17     /* Peep Hole Cycle Enable Done   */
#define MET_INT_EN_V_PH_ERR            16     /* Peep Hole Cycle Error Enable  */
#define MET_INT_EN_V_HOST              15     /* Host Access Error Enable Shift*/
#define MET_INT_EN_V_XMT_UN            14     /* XmtFree Slot Underflow Enable */
#define MET_INT_EN_V_XMT_IOC           13     /* XmtInterrupt on Completion    */
#define MET_INT_EN_V_FM_RSYNC          12     /* Flowmaster Rsync. Done Enable */
#define MET_INT_EN_V_RCV_FR_OV         11     /* Rcv Free Slot FIFO Overflow   */
#define MET_INT_EN_V_RCV_DT_OV         10     /* Rcv Data FIFO Overflow Enable */
#define MET_INT_EN_V_RCV_NBS            9     /* Rcv No Big Slots Enable Shift */ 
#define MET_INT_EN_V_RCV_NSS            8     /* Rcv No Small Slots Enable     */
#define MET_INT_EN_V_RCV_NRS            7     /* Rcv No Raw Slots Enable Shift */
#define MET_INT_EN_V_RCV_BSL            6     /* Rcv Big Slots Low Enable Shift*/
#define MET_INT_EN_V_RCV_SSL            5     /* Rcv Small Slots Low Enable    */
#define MET_INT_EN_V_RCV_RSL            4     /* Rcv Raw Slots Low Enable Shift*/
#define MET_INT_EN_V_XMT_NOP            3     /* Rcv Unopened VC Enable Shift  */
#define MET_INT_EN_V_RCV_U_VC           2     /* Rcv Unknown VC Enable Shift   */
#define MET_INT_EN_V_RCV_U_ACK          1     /* Rcv Unknown Ack Enable Shift  */
#define MET_INT_EN_V_RCV_IOC            0     /* Rcv IOC Enable Shift          */

/* Interrupt Holdoff.                                                          */

#define MET_INT_HLD_M_XMT_WR   0x80000000     /* XmtIOC Holdoff Write          */
#define MET_INT_HLD_M_XMT_CNT  0x7F000000     /* XmtIOC Holdoff Count          */
#define MET_INT_HLD_M_XMT_TM   0x00FF0000     /* XmtIOC Holdoff Time           */
#define MET_INT_HLD_M_RCV_WR   0x00008000     /* Rcv IOC Holdoff Write         */
#define MET_INT_HLD_M_RCV_CNT  0x00007F00     /* Rcv IOC Holdoff Count         */
#define MET_INT_HLD_M_RCV_TM   0x000000FF     /* Rcv IOC Holdoff Time          */

#define MET_INT_HLD_V_XMT_WR           31     /* XmtIOC Holdoff Write Shift    */
#define MET_INT_HLD_V_XMT_CNT          24     /* XmtIOC Holdoff Count Shift    */
#define MET_INT_HLD_V_XMT_TM           16     /* XmtIOC Holdoff Time Shift     */
#define MET_INT_HLD_V_RCV_WR           15     /* Rcv IOC Holdoff Write Shift   */
#define MET_INT_HLD_V_RCV_CNT           8     /* Rcv IOC Holdoff Count Shift   */
#define MET_INT_HLD_V_RCV_TM            0     /* Rcv IOC Holdoff Time Shift    */

#define MET_INT_HLD_K_TM_MIN            0     /* Min Value allowed for Time    */
#define MET_INT_HLD_K_TM_MAX          127     /* Max Value allowed for Time    */
#define MET_INT_HLD_K_CNT_MIN           0     /* Min Value allowed for Count   */
#define MET_INT_HLD_K_CNT_MAX         255     /* Max Value allowed for Count   */

/* Transmit Free Slot List Pointers.                                                 */

#define MET_XMT_FS_M_VALID     0x80000000     /* XmtFree Slot List Valid       */
#define MET_XMT_FS_M_RSVD_0    0x7C000000     /* Reserved 0                    */
#define MET_XMT_FS_M_HEAD      0x03FF0000     /* XmtFree Slot Head             */
#define MET_XMT_FS_M_RSVD_1    0x0000FC00     /* Reserved 1                    */
#define MET_XMT_FS_M_TAIL      0x000003FF     /* XmtFree Slot Tail             */

#define MET_XMT_FS_V_VALID             31     /* XmtFree Slot List Valid Shift */
#define MET_XMT_FS_V_RSVD_0            26     /* Reserved 0                    */
#define MET_XMT_FS_V_HEAD              16     /* XmtFree Slot Head Shift       */
#define MET_XMT_FS_V_RSVD_1            10     /* Reserved 1                    */
#define MET_XMT_FS_V_TAIL               0     /* XmtFree Slot Tail Shift       */

/* Transmit Report Base.                                                       */

#define MET_XMT_RPT_BS_M_ADDR  0xFFFFFFC0     /* Xmt Report Queue              */
#define MET_XMT_RPT_BS_M_RSVD  0x0000003F     /* Reserved                      */

#define MET_XMT_RPT_BS_V_ADDR           6     /* Xmt Report Queue Shift        */
#define MET_XMT_RPT_BS_V_RSVD           0     /* Reserved                      */

/* Receive Report Base.                                                        */

#define MET_RCV_RPT_BS_M_ADDR  0xFFFFFFC0     /* Rcv Report Queue              */
#define MET_RCV_RPT_BS_M_RSVD  0x0000003F     /* Reserved                      */

#define MET_RCV_RPT_BS_V_ADDR           6     /* Rcv Report Queue Shift        */
#define MET_RCV_RPT_BS_V_RSVD           0     /* Reserved                      */

/* Transmit Report Pointers.                                                   */

#define MET_XMT_RPT_PTR_M_PTR  0xFFFFFFFC     /* XmtReport Pointer             */
#define MET_XMT_RPT_PTR_M_RSVD 0x00000002     /* Reserved                      */
#define MET_XMT_RPT_PTR_M_OWN  0x00000001     /* XmtOwn                        */

#define MET_XMT_RPT_PTR_V_PTR           2     /* XmtReport Pointer Shift       */
#define MET_XMT_RPT_PTR_V_RSVD          1     /* Reserved                      */
#define MET_XMT_RPT_PTR_V_OWN           0     /* XmtOwn Shift                  */


/* Receive Report Pointers.                                                    */

#define MET_RCV_RPT_PTR_M_PTR  0xFFFFFFFC     /* Rcv Report Pointer            */
#define MET_RCV_RPT_PTR_M_RSVD 0x00000002     /* Reserved                      */
#define MET_RCV_RPT_PTR_M_OWN  0x00000001     /* Rcv Own                       */

#define MET_RCV_RPT_PTR_V_PTR           2     /* Rcv Report Pointer Shift      */
#define MET_RCV_RPT_PTR_V_RSVD          1     /* Reserved                      */
#define MET_RCV_RPT_PTR_V_OWN           0     /* Rcv Own Shift                 */



/* Receive Slot Congestion Threshold Register.                                 */

#define MET_RCV_CNG_TH_M_RSVD  0xFF000000     /* Reserved                      */
#define MET_RCV_CNG_TH_M_RAW   0x00FF0000     /* Raw Slot Congestion Threshold */
#define MET_RCV_CNG_TH_M_BIG   0x0000FF00     /* Big Slot Congestion Threshold */
#define MET_RCV_CNG_TH_M_SML   0x000000FF     /* Small Slot Cong. Threshold    */

#define MET_RCV_CNG_TH_V_RSVD          24     /* Reserved                      */
#define MET_RCV_CNG_TH_V_RAW           16     /* Raw Slot Congestion Threshold */
#define MET_RCV_CNG_TH_V_BIG            8     /* Big Slot Congestion Threshold */
#define MET_RCV_CNG_TH_V_SML            0     /* Small Slot Congestion         */

#define MET_RCV_CNG_TH_K_MIN            0     /* Min value for Slot Congestion */
#define MET_RCV_CNG_TH_K_MAX          255     /* Max value for Slot Congestion */

/* Transmit ABR ADTF Register.                                                 */

#define MET_XMT_ABR_ADTF_M_2   0xFFFF0000     /* ADTF for ABR set 2            */
#define MET_XMT_ABR_ADTF_M_1   0x0000FFFF     /* ADTF for ABR set 1            */

#define MET_XMT_ABR_ADTF_V_2           16     /* ADTF for ABR set 2 Shift      */
#define MET_XMT_ABR_ADTF_V_1            0     /* ADTF for ABR set 1 Shift      */

#define MET_XMT_ABR_ADTF_K_MIN          0     /* ADTF for ABR Minumum          */
#define MET_XMT_ABR_ADTF_K_MAX 0x0000FFFF     /* ADTF for ABR Minumum          */

/* Transmit ABR Nrm and Trm Register.                                          */

#define MET_XMT_ABR_RM_M_RSVD  0xE0000000     /* Reserved                      */
#define MET_XMT_ABR_RM_M_LINE  0x1F000000     /* Line Rate Exponent            */
#define MET_XMT_ABR_RM_M_NRM_2 0x00E00000     /* Nrm for ABR set 2             */
#define MET_XMT_ABR_RM_M_TRM_2 0x001FF000     /* Trm for ABR set 2             */
#define MET_XMT_ABR_RM_M_NRM_1 0x00000E00     /* Nrm for ABR set 1             */
#define MET_XMT_ABR_RM_M_TRM_1 0x000001FF     /* Trm for ABR set 1             */

#define MET_XMT_ABR_RM_V_RSVD          29     /* Reserved                      */
#define MET_XMT_ABR_RM_V_LINE          24     /* Line Rate Exponent Shift      */
#define MET_XMT_ABR_RM_V_NRM_2         21     /* Nrm for ABR set 2 Shift       */
#define MET_XMT_ABR_RM_V_TRM_2         12     /* Trm for ABR set 2 Shift       */
#define MET_XMT_ABR_RM_V_NRM_1          9     /* Nrm for ABR set 1 Shift       */
#define MET_XMT_ABR_RM_V_TRM_1          0     /* Trm for ABR set 1 Shift       */

#define MET_XMT_ABR_RM_K_NRM_MIN        0     /* Min Value allowed for Nrm     */
#define MET_XMT_ABR_RM_K_NRM_MAX        7     /* Max Value allowed for Nrm     */

#define MET_XMT_ABR_RM_K_TRM_MIN        0     /* Min Value allowed for Trm     */
#define MET_XMT_ABR_RM_K_TRM_MAX      511     /* Max Value allowed for Trm     */

#define MET_XMT_ABR_RM_K_LINE_MIN       0     /* Min Value allowed for Line    */
#define MET_XMT_ABR_RM_K_LINE_MAX      31     /* Max Value allowed for Line    */


/* Peephole Command Register.                                                  */

#define MET_PH_CMD_M_READ      0x80000000     /* Peephole Read Command         */
#define MET_PH_CMD_M_PRF       0x40000000     /* Peephole Peripheral Access    */
#define MET_PH_CMD_M_RSVD      0x3FFF0000     /* Reserved                      */
#define MET_PH_CMD_M_ADDR      0x0000FFFF     /* Peephole Address              */

#define MET_PH_CMD_V_READ              31     /* Peephole Read Command Shift   */
#define MET_PH_CMD_V_PRF               30     /* Peephole Peripheral Access    */
#define MET_PH_CMD_V_RSVD              16     /* Reserved                      */
#define MET_PH_CMD_V_ADDR               0     /* Peephole Address Shift        */

/* Peephole Data Register.                                                     */

#define MET_PH_DATA_M_DONE     0x80000000     /* Peephole Done                 */
#define MET_PH_DATA_M_RSVD     0x7FFF0000     /* Reserved                      */
#define MET_PH_DATA_M_DATA     0x0000FFFF     /* Peephole Data                 */

#define MET_PH_DATA_V_DONE             31     /* Peephole Done Shift           */
#define MET_PH_DATA_V_RSVD             16     /* Reserved                      */
#define MET_PH_DATA_V_DATA              0     /* Peephole Data Shift           */

#define MET_PH_DATA_K_DONE              1
#define MET_PH_CMD_K_PRF_READ  (MET_PH_CMD_M_READ | MET_PH_CMD_M_PRF)

/* Rcv Raw Slot Tag                                                            */

#define MET_RCV_RAW_SLOT_M_RSVD_0 0xFFFF0000  /* Reserved 0                    */
#define MET_RCV_RAW_SLOT_M_TAG    0x0000FFFC  /* Rcv Raw Slot Tag              */
#define MET_RCV_RAW_SLOT_M_RSVD_1 0x00000002  /* Reserved 1                    */
#define MET_RCV_RAW_SLOT_M_VALID  0x00000001  /* Rcv Raw Slot Tag valid        */

#define MET_RCV_RAW_SLOT_V_RSVD_0         16  /* Reserved 0                    */
#define MET_RCV_RAW_SLOT_V_TAG             2  /* Rcv Raw Slot Tag              */
#define MET_RCV_RAW_SLOT_V_RSVD_1          1  /* Reserved 1                    */
#define MET_RCV_RAW_SLOT_V_VALID           0  /* Rcv Raw Slot Tag valid        */

/* Rcv Cell Count Register,                                                    */

#define MET_RCV_CELL_M_RSVD    0xFFF00000     /* Reserved                      */
#define MET_RCV_CELL_M_CNT     0x000FFFFF     /* Rcv Cell Count                */

#define MET_RCV_CELL_V_RSVD             20    /* Reserved                      */
#define MET_RCV_CELL_V_CNT               0    /* Rcv Cell Count Shift          */

/* Rcv AAL5 Drop Packet Count Register.                                        */

#define MET_RCV_AAL5_DROP_M_RSVD 0xFFF00000    /* Reserved                      */
#define MET_RCV_AAL5_DROP_M_CNT 0x000FFFFF     /* Rcv AAL5 Drop Packet Count    */

#define MET_RCV_AAL5_DROP_V_RSVD        20    /* Reserved                      */
#define MET_RCV_AAL5_DROP_V_CNT          0    /* Rcv AAL5 Drop Packet Count    */

/* Rcv Raw Drop Cell Count.                                                    */

#define MET_RCV_RAW_DROP_M_RSVD 0xFFF00000     /* Reserved                      */
#define MET_RCV_RAW_DROP_M_CNT  0x000FFFFF     /* Rcv Raw Drop Cell Count       */

#define MET_RCV_RAW_DROP_V_RSVD        20     /* Reserved                      */
#define MET_RCV_RAW_DROP_V_CNT          0     /* Rcv Raw Drop Cell Count Shift */

/* Xmt Cell Count Register.                                                    */

#define MET_XMT_CELL_M_RSVD    0xFFF00000     /* Reserved                      */
#define MET_XMT_CELL_M_CNT     0x000FFFFF     /* Xmt Cell Count                */

#define MET_XMT_CELL_V_RSVD            20     /* Reserved                      */
#define MET_XMT_CELL_V_CNT              0     /* Xmt Cell Count Shift          */

/* Real Time Register.                                                         */

#define MET_REAL_M_RSVD        0xC0000000     /* Reserved                      */
#define MET_REAL_M_3P93US      0x3FFFFF00     /* Real-time in 3.93 us          */
#define MET_REAL_M_30NS        0x000000FF     /* Real-time in 30 ns            */

#define MET_REAL_V_RSVD                30     /* Reserved                      */
#define MET_REAL_V_3P93US               8     /* Real-time in 3.93 us Shift    */
#define MET_REAL_V_30NS                 0     /* Real-time in 30 ns Shift      */

/* Current Time Register.                                                      */

#define MET_CUR_M_RSVD         0xFFFF0000     /* Reserved                      */
#define MET_CUR_M_ABR_TIME     0x0000FF00     /* ABR Time                      */
#define MET_CUR_M_UBR_TIME     0x000000FF     /* UBR Time                      */

#define MET_CUR_V_RSVD                 16     /* Reserved                      */
#define MET_CUR_V_ABR_TIME              8     /* ABR Shift                     */
#define MET_CUR_V_UBR_TIME              0     /* UBR Shift                     */

/* Test Control Register.                                                      */

#define MET_TEST_M_RSVD        0xFFFF2000     /* Reserved                      */
#define MET_TEST_M_RPT_PTR_SEG 0x00001000     /* Seg Xmt and Rcv rpt queue ptrs*/
#define MET_TEST_M_TDS_WAIT    0x00000800     /* TDS wait                      */
#define MET_TEST_M_TAC_TIME    0x00000400     /* Tac Timer Speedup             */
#define MET_TEST_M_LRM_POLL    0x00000200     /* Last RM Poll Time             */
#define MET_TEST_M_RATO_POLL   0x00000100     /* Reassembly Time Out Poll Time */
#define MET_TEST_M_GFC_HALT    0x00000080     /* Force GFC Halt                */
#define MET_TEST_M_GFC_SET_A   0x00000040     /* Force GFC SET_A               */
#define MET_TEST_M_PH_TEST     0x00000020     /* Peephole Test Mode            */
#define MET_TEST_M_SET_INTR    0x00000010     /* Force Interrupt               */
#define MET_TEST_M_CNT_FRC     0x00000008     /* Force Counting                */
#define MET_TEST_M_CNT_SEG     0x00000004     /* Set Counter Segments          */
#define MET_TEST_M_XMT_DIS     0x00000002     /* XmtDMA Disable                */
#define MET_TEST_M_RCV_DIS     0x00000001     /* Rcv DMA Disable               */

#define MET_TEST_V_RSVD                13     /* Reserved                      */
#define MET_TEST_V_RPT_PTR_SEG         12     /* Seg Xmt and Rcv rpt queue ptrs*/
#define MET_TEST_V_TDS_WAIT            11     /* TDS wait Shift                */
#define MET_TEST_V_TAC_TIME            10     /* Tac Timer Speedup Shift       */
#define MET_TEST_V_LRM_POLL             9     /* Last RM Poll Time Shift       */
#define MET_TEST_V_RATO_POLL            8     /* Reassembly Time Out Poll Time */
#define MET_TEST_V_GFC_HALT             7     /* Force GFC Halt Shift          */
#define MET_TEST_V_GFC_SET_A            6     /* Force GFC SET_A Shift         */
#define MET_TEST_V_PH_TEST              5     /* Peephole Test Mode Shift      */
#define MET_TEST_V_SET_INTR             4     /* Force Interrupt Shift         */
#define MET_TEST_V_CNT_FRC              3     /* Force Counting Shift          */
#define MET_TEST_V_CNT_SEG              2     /* Set Counter Segments Shift    */
#define MET_TEST_V_XMT_DIS              1     /* XmtDMA Disable Shift          */
#define MET_TEST_V_RCV_DIS              0     /* Rcv DMA Disable Shift         */

/*  CSR offsets in PCI space.                                                  */

#define MET_O_XMT_PEND_CTRL_0        0x00     /* 0x00 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_0        0x04     /* 0x01 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_CTRL_1        0x08     /* 0x02 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_1        0x0C     /* 0x03 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_CTRL_2        0x10     /* 0x04 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_2        0x14     /* 0x05 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_CTRL_3        0x18     /* 0x06 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_3        0x1C     /* 0x07 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_CTRL_4        0x20     /* 0x08 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_4        0x24     /* 0x09 << 2. PCI Space offset   */
#define MET_O_XMT_PEND_CTRL_5        0x28     /* 0x0A << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_5        0x2C     /* 0x0B << 2. PCI Space offset   */
#define MET_O_XMT_PEND_CTRL_6        0x30     /* 0x0C << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_6        0x34     /* 0x0D << 2. PCI Space offset   */
#define MET_O_XMT_PEND_CTRL_7        0x38     /* 0x0E << 2. PCI Space offset   */
#define MET_O_XMT_PEND_ADDR_7        0x3C     /* 0x0F << 2. PCI Space offset   */

#define MET_O_RCV_PEND_CTRL_0        0x40     /* 0x10 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_0        0x44     /* 0x11 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_CTRL_1        0x48     /* 0x12 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_1        0x4C     /* 0x13 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_CTRL_2        0x50     /* 0x14 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_2        0x54     /* 0x15 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_CTRL_3        0x58     /* 0x16 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_3        0x5C     /* 0x17 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_CTRL_4        0x60     /* 0x18 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_4        0x64     /* 0x19 << 2. PCI Space offset   */
#define MET_O_RCV_PEND_CTRL_5        0x68     /* 0x1A << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_5        0x6C     /* 0x1B << 2. PCI Space offset   */
#define MET_O_RCV_PEND_CTRL_6        0x70     /* 0x1C << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_6        0x74     /* 0x1D << 2. PCI Space offset   */
#define MET_O_RCV_PEND_CTRL_7        0x78     /* 0x1E << 2. PCI Space offset   */
#define MET_O_RCV_PEND_ADDR_7        0x7C     /* 0x1F << 2. PCI Space offset   */

#define MET_K_XMT_PEND_CTRL_BASE     0x00     /* Base Address of XMT pend ctrl */
#define MET_K_XMT_PEND_ADDR_BASE     0x04     /* Base Address of XMT pend addr */
#define MET_K_XMT_PEND_SLOT_MAX      0x07     /* Max Slot value                */

#define MET_O_CTRL_1                 0x80     /* 0x20 << 2. PCI Space offset   */
#define MET_O_CTRL_2                 0x84     /* 0x21 << 2. PCI Space offset   */
#define MET_O_INT_ST                 0x88     /* 0x22 << 2. PCI Space offset   */
#define MET_O_INT_EN                 0x8C     /* 0x23 << 2. PCI Space offset   */
#define MET_O_INT_HLD                0x90     /* 0x24 << 2. PCI Space offset   */
#define MET_O_XMT_FS                 0x94     /* 0x25 << 2. PCI Space offset   */
#define MET_O_XMT_RPT_BS             0x98     /* 0x26 << 2. PCI Space offset   */
#define MET_O_RCV_RPT_BS             0x9C     /* 0x27 << 2. PCI Space offset   */
#define MET_O_XMT_RPT_PTR            0xA0     /* 0x28 << 2. PCI Space offset   */
#define MET_O_RCV_RPT_PTR            0xA4     /* 0x29 << 2. PCI Space offset   */
#define MET_O_RCV_CNG_TH             0xA8     /* 0x2A << 2. PCI Space offset   */
#define MET_O_XMT_ABR_ADTF           0xAC     /* 0x2B << 2. PCI Space offset   */
#define MET_O_XMT_ABR_RM             0xB0     /* 0x2C << 2. PCI Space offset   */
#define MET_O_PH_CMD                 0xB4     /* 0x2D << 2. PCI Space offset   */
#define MET_O_PH_DATA                0xB8     /* 0x2E << 2. PCI Space offset   */
#define MET_O_RCV_RAW_SLOT           0xBC     /* 0x2F << 2. PCI Space offset   */
#define MET_O_RCV_CELL               0xC0     /* 0x30 << 2. PCI Space offset   */
#define MET_O_RCV_AAL5_DROP          0xC4     /* 0x31 << 2. PCI Space offset   */
#define MET_O_RCV_RAW_DROP           0xC8     /* 0x32 << 2. PCI Space offset   */
#define MET_O_XMT_CELL               0xCC     /* 0x33 << 2. PCI Space offset   */
#define MET_O_REAL                   0xD0     /* 0x34 << 2. PCI Space offset   */
#define MET_O_CUR                    0xD4     /* 0x35 << 2. PCI Space offset   */
#define MET_O_TEST                   0xD8     /* 0x36 << 2. PCI Space offset   */

#define MET_CTRL_2_K_RESET     0x00000001     /* Soft Reset                    */

/*  These constants describe the CSR values following a soft reset.  The soft  */
/*  reset bit (Meteor Control 2, bit 0) must be cleared by the Meteor chip,    */
/*  prior to any CSR writes.                                                   */

#define MET_CTRL_1_K_DEF       0x00000040     /* Phy Chip Reset, GFC signal set*/
#define MET_CTRL_2_K_DEF       0x00001001     /* Soft reset  */
#define MET_INT_ST_K_DEF       0x00000000
#define MET_INT_EN_K_DEF       0x00000000
#define MET_INT_HLD_K_DEF      0x00000000
#define MET_XMT_FS_K_DEF       0x00000000
#define MET_XMT_RPT_BS_K_DEF   0x00000000
#define MET_RCV_RPT_BS_K_DEF   0x00000000
#define MET_XMT_RPT_PTR_K_DEF  0x00000000
#define MET_RCV_RPT_PTR_K_DEF  0x00000000
#define MET_RCV_CNG_TH_K_DEF   0x00000000
#define MET_XMT_ABR_ADTF_K_DEF 0x00000000
#define MET_XMT_ABR_RM_K_DEF   0x00000000
#define MET_PH_CMD_K_DEF       0x40000000
#define MET_PH_DATA_K_DEF      0x80000000      /* PH Done bit set              */
#define MET_RCV_RAW_ADDR_K_DEF 0x00000000
#define MET_RCV_CELL_K_DEF     0x00000000
#define MET_RCV_AAL5_DROP_K_DEF 0x00000000
#define MET_RCV_RAW_DROP_K_DEF  0x00000000
#define MET_XMT_CELL_K_DEF     0x00000000
#define MET_REAL_K_DEF         0x00000000
#define MET_CUR_K_DEF          0x00000000
#define MET_TEST_K_DEF         0x00000000

/* Peep Hole Accessed SRAM Structures                                          */

/* Receive Slot Tag VC State Table. */

#define MET_RCV_SLOT_TAG_M_RSVD    0xC000     /* Reserved                      */
#define MET_RCV_SLOT_TAG_M_PTR     0x3FFF     /* Slot Tag Pointer              */

#define MET_RCV_SLOT_TAG_V_RSVD        14     /* Reserved                      */
#define MET_RCV_SLOT_TAG_V_PTR          0     /* Slot Tag Pointer              */

/* Receive VC State Table                                                      */

/* Receive VC State Table, Word 0                                              */

#define MET_RCV_VC_M_CRC10_EN      0x8000     /* Rcv VC CRC10 Enable           */
#define MET_RCV_VC_M_DROP          0x4000     /* Rcv VC Drop                   */
#define MET_RCV_VC_M_OPEN          0x2000     /* Rcv VC Open                   */
#define MET_RCV_VC_M_CONGST        0x1000     /* Rcv VC Congestion             */
#define MET_RCV_VC_M_CELL_LOSS     0x0800     /* Rcv VC Cell Loss              */
#define MET_RCV_VC_M_RCV_SM        0x0400     /* Rcv VC AAL5 Stream Mode       */
#define MET_RCV_VC_M_SLOT_TYPE     0x0300     /* Rcv VC Slot Type              */
#define MET_RCV_VC_M_SLOT_CONS     0x00FF     /* Rcv VC Slots Consumed         */

#define MET_RCV_VC_V_CRC10_EN          15     /* Rcv VC CRC10 Enable Shift     */
#define MET_RCV_VC_V_DROP              14     /* Rcv VC Drop Shift             */
#define MET_RCV_VC_V_OPEN              13     /* Rcv VC Open Shift             */
#define MET_RCV_VC_V_CONGST            12     /* Rcv VC Congestion Shift       */
#define MET_RCV_VC_V_CELL_LOSS         11     /* Rcv VC Cell Loss Shift        */
#define MET_RCV_VC_V_RCV_SM            10     /* Rcv VC AAL5 Stream Mode Shift */
#define MET_RCV_VC_V_SLOT_TYPE          8     /* Rcv VC Slot Type Shift        */
#define MET_RCV_VC_V_SLOT_CONS          0     /* Rcv VC Slots Consumed Shift   */

#define MET_RCV_VC_K_OPEN               1     /* Open                          */
#define MET_RCV_VC_K_CLOSE              0     /* Close                         */

#define MET_RCV_VC_M_RSVD          0xE000     /* Reserved                      */
#define MET_RCV_VC_M_SLOT_PTR      0x1FFF     /* Rcv VC Slot Pointer           */

#define MET_RCV_VC_V_RSVD              13
#define MET_RCV_VC_V_SLOT_PTR           0     /* Rcv VC Slot Pointer Shift     */

/* Receive VC State Table, Word 7                                              */

#define MET_RCV_VC_M_IN_AAL5       0x8000     /* Rcv VC In AAL5 Pkt            */
#define MET_RCV_VC_M_OR_CI         0x4000     /* Rcv VC Or CI                  */
#define MET_RCV_VC_M_OR_CLP        0x2000     /* Rcv VC Or CLP                 */
#define MET_RCV_VC_M_FM            0x1000     /* Rcv VC FM                     */
#define MET_RCV_VC_M_EX_RATO       0x0F00     /* Rcv VC Ex RATO                */
#define MET_RCV_VC_M_ACK_CNT       0x00FF     /* Rcv VC Ack Count              */

#define MET_RCV_VC_V_IN_AAL5           15     /* Rcv VC In AAL5 Pkt Shift      */
#define MET_RCV_VC_V_OR_CI             14     /* Rcv VC Or CI Shift            */
#define MET_RCV_VC_V_OR_CLP            13     /* Rcv VC Or CLP Shift           */
#define MET_RCV_VC_V_FM                12     /* Rcv VC FM Shift               */
#define MET_RCV_VC_V_EX_RATO            8     /* Rcv VC Ex RATO Shift          */
#define MET_RCV_VC_V_ACK_CNT            0     /* Rcv VC Ack Count Shift        */

/* Receive VC State Table offsets                                              */

#define MET_O_RCV_VC_WORD_0          0x00     /* Word offset for word 0        */
#define MET_O_RCV_VC_LEN             0x01     /* Word offset for AAL5 length   */
#define MET_O_RCV_VC_SLOT_LOW        0x02     /* Word offset for low slot addr */
#define MET_O_RCV_VC_SLOT_HIGH       0x03     /* Word offset for high slot addr*/
#define MET_O_RCV_VC_CRC_LOW         0x04     /* Word offset for low CRC word  */
#define MET_O_RCV_VC_CRC_HIGH        0x05     /* Word offset for high CRC word */
#define MET_O_RCV_VC_SLOT_PTR        0x06     /* Word offset for Slot Pointer  */
#define MET_O_RCV_VC_WORD_7          0x07     /* Word offset for word 7        */

#define MET_K_RCV_VC_ENTRY_SIZE         8     /* 8 Words (16 bits) per entry   */
#define MET_K_RCV_VC_WORD_0_INIT        0     /* Open = 0                      */
   
/* Transmit VC State Table.  Word 0                                            */

#define MET_XMT_VC_M_CHTYP         0xC000     /* Xmt VC chtyp                  */
#define MET_XMT_VC_M_SM            0x2000     /* Xmt VC SM                     */
#define MET_XMT_VC_M_FM            0x1000     /* Xmt VC FM                     */
#define MET_XMT_VC_M_ABS           0x0800     /* Xmt VC ABS                    */
#define MET_XMT_VC_M_RC            0x0600     /* Xmt VC RC                     */
#define MET_XMT_VC_M_CLP           0x0100     /* Xmt VC CLP                    */
#define MET_XMT_VC_M_RSVD_0        0x00F0     /* Reserved 0                    */
#define MET_XMT_VC_M_PRES_VAL      0x000F     /* Xmt VC Prescale Value         */

#define MET_XMT_VC_V_CHTYP             13     /* Xmt VC chtyp Shift            */
#define MET_XMT_VC_V_SM                12     /* Xmt VC SM Shift               */
#define MET_XMT_VC_V_FM                11     /* Xmt VC FM Shift               */
#define MET_XMT_VC_V_ABS               10     /* Xmt VC ABS Shift              */
#define MET_XMT_VC_V_RC                 9     /* Xmt VC RC Shift               */
#define MET_XMT_VC_V_CLP                8     /* Xmt VC CLP Shift              */
#define MET_XMT_VC_V_RSVD_0             4     /* Reserved 0                    */
#define MET_XMT_VC_V_PRES_VAL           0     /* Xmt VC Prescale Value Shift   */

/* Transmit VC State Table.  Word 1                                            */

#define MET_XMT_VC_M_RSVD_1        0x8000     /* Reserved 1                    */
#define MET_XMT_VC_M_MPEG_CNT      0x7000     /* Xmt VC MPEG Count             */
#define MET_XMT_VC_M_PRES_CNT      0x0F00     /* Xmt VC Prescale Count         */
#define MET_XMT_VC_M_CREDIT        0x00FF     /* Xmt VC Credit                 */

#define MET_XMT_VC_V_RSVD_1            15     /* Reserved 1                    */
#define MET_XMT_VC_V_MPEG_CNT          12     /* Xmt VC MPEG Count Shift       */
#define MET_XMT_VC_V_PRES_CNT           8     /* Xmt VC Prescale Count Shift   */
#define MET_XMT_VC_V_CREDIT             0     /* Xmt VC Credit Shift           */

/* Transmit VC State Table.  Word 4                                            */

#define MET_XMT_VC_M_ACTIVE        0x8000     /* Xmt VC Active                 */
#define MET_XMT_VC_M_SCH           0x4000     /* Xmt VC Schedule               */
#define MET_XMT_VC_M_OR_BRM        0x2000     /* Xmt VC OR BRM                 */
#define MET_XMT_VC_M_TURN          0x1000     /* Xmt VC Turn                   */
#define MET_XMT_VC_M_A_SLOT_H      0x0FFF     /* Xmt VC A Slot H               */

#define MET_XMT_VC_V_ACTIVE            15     /* Xmt VC Active Shift           */
#define MET_XMT_VC_V_SCH               14     /* Xmt VC Schedule Shift         */
#define MET_XMT_VC_V_OR_BRM            13     /* Xmt VC OR BRM Shift           */
#define MET_XMT_VC_V_TURN              12     /* Xmt VC Turn Shift             */
#define MET_XMT_VC_V_A_SLOT_H           0     /* Xmt VC A Slot H Shift         */

#define MET_XMT_VC_K_ACTIVE             1     /* Xmt VC Active                 */
#define MET_XMT_VC_K_NOT_ACTIVE         0     /* Xmt VC Not Active             */
#define MET_XMT_VC_K_OR_BRM_INIT        0

/* Transmit VC State Table.  Word 5                                            */

#define MET_XMT_VC_M_RSVD_2        0xF000     /* Reserved 2                    */
#define MET_XMT_VC_M_A_SLOT_T      0x0FFF     /* Xmt VC Slot T                 */

#define MET_XMT_VC_V_RSVD_2            12     /* Reserved 2                    */
#define MET_XMT_VC_V_A_SLOT_T           0     /* Xmt VC Slot T Shift           */

/* Transmit VC State Table.  Word 6                                            */

#define MET_XMT_VC_M_RSVD_3        0x8000     /* Reserved 3                    */
#define MET_XMT_VC_M_IDLE          0x4000     /* Xmt VC Idle                   */
#define MET_XMT_VC_M_SLOT_PTR      0x3FFF     /* Xmt VC Slot Pointer           */

#define MET_XMT_VC_V_RSVD_3            15     /* Reserved 3                    */
#define MET_XMT_VC_V_IDLE              14     /* Xmt VC Idle Shift             */
#define MET_XMT_VC_V_SLOT_PTR           0     /* Xmt VC Slot Pointer Shift     */

/* Transmit VC State Table.  Word 7                                            */

#define MET_XMT_VC_M_RSVD_4        0xF000     /* Reserved 4                    */
#define MET_XMT_VC_M_VC_LINK       0x0FFF     /* Xmt VC Link                   */

#define MET_XMT_VC_V_RSVD_4            12     /* Reserved 4                    */
#define MET_XMT_VC_V_VC_LINK            0     /* Xmt VC Link Shift             */

#define MET_XMT_VC_K_CREDIT_MIN         0     /* Minumum value for credits     */
#define MET_XMT_VC_K_CREDIT_MAX       255     /* Maximum value for credits     */

/* Transmit VC State Table word offsets.  Accessable via Peephole Interface    */

#define MET_O_XMT_VC_WORD_0          0x00     /* Word offset for word 0        */
#define MET_O_XMT_VC_WORD_1          0x01     /* Word offset for word 1        */
#define MET_O_XMT_VC_CRC_L           0x02     /* Word offset for CRC low word  */
#define MET_O_XMT_VC_CRC_H           0x03     /* Word offset for CRC high word */
#define MET_O_XMT_VC_WORD_4          0x04     /* Word offset for word 4        */
#define MET_O_XMT_VC_A_SLOT_T        0x05     /* Word offset for A slot T      */
#define MET_O_XMT_VC_WORD_6          0x06     /* Word offset for word 6        */
#define MET_O_XMT_VC_LINK            0x07     /* Word offset for VC link       */

#define MET_K_XMT_VC_ENTRY_SIZE         8     /* 8 Words (16 bits) per entry   */

/* ABR Parameter Table.  8 words/entry, 1 entry/VC                             */

/* ABR Parameter Table.  Word 0                                                */

#define MET_ABR_PAR_M_RSVD_0       0x8000     /* Reserved 0                    */
#define MET_ABR_PAR_M_CDFX         0x7000     /* CDFx                          */
#define MET_ABR_PAR_M_RDFX         0x0F00     /* Rdfx                          */
#define MET_ABR_PAR_M_CRMX         0x00E0     /* Crmx                          */
#define MET_ABR_PAR_M_RSVD_1       0x001F     /* Reserved 1                    */

#define MET_ABR_PAR_V_RSVD_0           15     /* Reserved 0                    */
#define MET_ABR_PAR_V_CDFX             12     /* CDFx Shift                    */
#define MET_ABR_PAR_V_RDFX              8     /* Rdfx Shift                    */
#define MET_ABR_PAR_V_CRMX              5     /* Crmx Shift                    */
#define MET_ABR_PAR_V_RSVD_1            0     /* Reserved 1                    */

#define MET_ABR_PAR_K_CDFX_DEF          0     /* CDFX Default Value ???        */
#define MET_ABR_PAR_K_RDFX_DEF          0     /* RDFX Default Value ???        */
#define MET_ABR_PAR_K_CRMX_DEF          0     /* CRMX Default Value ???        */

#define MET_ABR_PAR_K_CDFX_MIN          0     /* CDFX Minimum Value            */
#define MET_ABR_PAR_K_CDFX_MAX          7     /* CDFX Maximum Value            */

#define MET_ABR_PAR_K_RDFX_MIN          0     /* RDFX Minimum Value            */
#define MET_ABR_PAR_K_RDFX_MAX         11     /* RDFX Maximum Value            */

#define MET_ABR_PAR_K_CRMX_MIN          0     /* CRMX Minimum Value            */
#define MET_ABR_PAR_K_CRMX_MAX          7     /* CRMX Maximum Value            */

/* ABR Parameter Table.  Word 1                                                */

#define MET_ABR_PAR_M_RSVD_2       0x8000     /* Reserved 2                    */
#define MET_ABR_PAR_M_AIR          0x7FFF     /* AIR                           */

#define MET_ABR_PAR_V_RSVD_2           15     /* Reserved 2                    */
#define MET_ABR_PAR_V_AIR               0     /* AIR Shift                     */

#define MET_ABR_PAR_K_AIR_DEF           0     /* AIR Default Value ???         */
#define MET_ABR_PAR_K_AIR_MIN           0     /* AIR Minimum Value             */
#define MET_ABR_PAR_K_AIR_MAX       32767     /* AIR Maximum Value             */

/* ABR Parameter Table.  Word 2                                                */

#define MET_ABR_PAR_M_RSVD_3       0x8000     /* Reserved 3                    */
#define MET_ABR_PAR_M_ICR          0x7FFF     /* ICR                           */

#define MET_ABR_PAR_V_RSVD_3           15     /* Reserved 3                    */
#define MET_ABR_PAR_V_ICR               0     /* ICR Shift                     */

#define MET_ABR_PAR_K_ICR_DEF           0     /* ICR Default Value ???         */
#define MET_ABR_PAR_K_ICR_MIN           0     /* ICR Minimum Value             */
#define MET_ABR_PAR_K_ICR_MAX       32767     /* ICR Maximum Value             */

/* ABR Parameter Table.  Word 3                                                */

#define MET_ABR_PAR_M_RSVD_4       0x8000     /* Reserved 4                    */
#define MET_ABR_PAR_M_MCR          0x7FFF     /* MCR                           */

#define MET_ABR_PAR_V_RSVD_4           15     /* Reserved 4                    */
#define MET_ABR_PAR_V_MCR               0     /* MCR Shift                     */

#define MET_ABR_PAR_K_MCR_DEF           0     /* MCR Default Value ???         */
#define MET_ABR_PAR_K_MCR_MIN           0     /* MCR Minimum Value             */
#define MET_ABR_PAR_K_MCR_MAX       32767     /* MCR Maximum Value             */

/* ABR Parameter Table.  Word 4                                                */

#define MET_ABR_PAR_M_RSVD_5       0x8000     /* Reserved 5                    */
#define MET_ABR_PAR_M_PCR          0x7FFF     /* PCR                           */

#define MET_ABR_PAR_V_RSVD_5           15     /* Reserved 5                    */
#define MET_ABR_PAR_V_PCR               0     /* PCR Shift                     */

#define MET_ABR_PAR_K_PCR_DEF           0     /* PCR Default Value ???         */
#define MET_ABR_PAR_K_PCR_MIN           0     /* PCR Minimum Value             */
#define MET_ABR_PAR_K_PCR_MAX       32767     /* PCR Maximum Value             */

/* ABR Parameter Table.  Word 5                                                */

#define MET_ABR_PAR_M_RSVD_6       0xFFFE     /* Reserved 6                    */
#define MET_ABR_PAR_M_CI_VC        0x0001     /* CI-VC                         */

#define MET_ABR_PAR_V_RSVD_6           15     /* Reserved 6                    */
#define MET_ABR_PAR_V_CI_VC             0     /* CI-VC Shift                   */

/* ABR Parameter Table.  Word 6                                                */

#define MET_ABR_PAR_M_RSVD_7       0xFFFF     /* Reserved 7                    */

#define MET_ABR_PAR_V_RSVD_7            0     /* Reserved 7                    */

/* ABR Parameter Table.  Word 7                                                */

#define MET_ABR_PAR_M_RSVD_8       0xFFFF     /* Reserved 8                    */

#define MET_ABR_PAR_V_RSVD_8            0     /* Reserved 8                    */

/* ABR Parameter Table Word offsets.  Accessable via Peephole Interface        */

#define MET_O_ABR_PAR_WORD_0         0x00     /* Word offset for word 0        */
#define MET_O_ABR_PAR_AIR            0x01     /* Word offset for AIR           */
#define MET_O_ABR_PAR_ICR            0x02     /* Word offset for ICR           */
#define MET_O_ABR_PAR_MCR            0x03     /* Word offset for MCR           */
#define MET_O_ABR_PAR_PCR            0x04     /* Word offset for PCR           */
#define MET_O_ABR_PAR_CI_VC          0x05     /* Word offset for CI-VC         */
#define MET_O_ABR_PAR_WORD_6         0x06     /* Word offset for word 6        */
#define MET_O_ABR_PAR_WORD_7         0x07     /* Word offset for word 7        */

#define MET_K_ABR_PAR_ENTRY_SIZE        8     /* 8 Words (16) per entry        */

/* ABR Value Table.  4 words/entry, 1 entry/VC                                 */

/* ABR Value Table.  Word 0                                                    */
                                        
#define MET_ABR_VAL_M_RSVD_0       0x8000     /* Reserved 0                    */
#define MET_ABR_VAL_M_ACR          0x7FFF     /* ACR                           */

#define MET_ABR_VAL_V_RSVD_0           15     /* Reserved 0                    */
#define MET_ABR_VAL_V_ACR               0     /* ACR Shift                     */

/* ABR Value Table.  Word 1                                                    */

#define MET_ABR_VAL_M_F_TRN        0x8000     /* First Trn                     */
#define MET_ABR_VAL_M_ABR_ACT      0x4000     /* ABR active                    */
#define MET_ABR_VAL_M_F_FRM        0x2000     /* Force FRM                     */
#define MET_ABR_VAL_M_LRM_V        0x1000     /* Last RM Valid                 */
#define MET_ABR_VAL_M_RSVD_1       0x0E00     /* Reserved 1                    */
#define MET_ABR_VAL_M_FRACT        0x01FF     /* Fraction                      */

#define MET_ABR_VAL_V_F_TRN            15     /* First Trn Shift               */
#define MET_ABR_VAL_V_ABR_ACT          14     /* ABR active Shift              */
#define MET_ABR_VAL_V_F_FRM            13     /* Force FRM Shift               */
#define MET_ABR_VAL_V_LRM_V            12     /* Last RM Valid Shift           */
#define MET_ABR_VAL_V_RSVD_1            9     /* Reserved 1                    */
#define MET_ABR_VAL_V_FRACT             0     /* Fraction Shift                */

#define MET_ABR_VAL_K_FRACT_DEF         0
#define MET_ABR_VAL_K_ACTIVE            1

/* ABR Value Table.  Word 2                                                    */

#define MET_ABR_VAL_M_LRM          0xFFFF     /* Last RM                       */

#define MET_ABR_VAL_V_LRM               0     /* Last RM Shift                 */

/* ABR Value Table.  Word 3                                                    */

#define MET_ABR_VAL_M_CRM_CNT      0xFF00     /* Crm Cnt                       */
#define MET_ABR_VAL_M_NRM_CNT      0x00FF     /* Nrm Cnt                       */

#define MET_ABR_VAL_V_CRM_CNT           8     /* Crm Cnt Shift                 */
#define MET_ABR_VAL_V_NRM_CNT           0     /* Nrm Cnt Shift                 */

/* ABR Value Table word offsets.  Accessable via Peephole Interface            */

#define MET_O_ABR_VAL_ACR            0x00     /* Word offset for ACR           */
#define MET_O_ABR_VAL_WORD_1         0x01     /* Word offset for word 1        */
#define MET_O_ABR_VAL_LRM            0x02     /* Word offset for Last RM       */
#define MET_O_ABR_VAL_WORD_3         0x03     /* Word offset for word 3        */

#define MET_K_ABR_VAL_ENTRY_SIZE        4     /* 4 Words (8) per entry        */


/* RM Cell Data Table.  4 words/entry, 1 entry/VC.                             */

/* RM Cell Data Table.  Word 0                                                 */

#define MET_RM_DATA_M_PI           0xFF00     /* PI                            */
#define MET_RM_DATA_M_MT           0x00FF     /* MT                            */

#define MET_RM_DATA_V_PI                8     /* PI Shift                      */
#define MET_RM_DATA_V_MT                0     /* MT Shift                      */

/* RM Cell Data Table.  Word 1                                                 */

#define MET_RM_DATA_M_RSVD_0       0x8000     /* Reserved 0                    */
#define MET_RM_DATA_M_ER_NZ        0x4000     /* ER nz                         */
#define MET_RM_DATA_M_ER_E         0x3E00     /* ER e                          */
#define MET_RM_DATA_M_ER_M         0x01FF     /* ER m                          */

#define MET_RM_DATA_V_RSVD_0           15     /* Reserved 0                    */
#define MET_RM_DATA_V_ER_NZ            14     /* ER nz Shift                   */
#define MET_RM_DATA_V_ER_E              9     /* ER e Shift                    */
#define MET_RM_DATA_V_ER_M              0     /* ER m Shift                    */

/* RM Cell Data Table.  Word 2                                                 */

#define MET_RM_DATA_M_RSVD_1       0x8000     /* Reserved 1                    */
#define MET_RM_DATA_M_CCR_NZ       0x4000     /* CCR m                         */
#define MET_RM_DATA_M_CCR_E        0x3E00     /* CCR m                         */
#define MET_RM_DATA_M_CCR_M        0x01FF     /* CCR m                         */

#define MET_RM_DATA_V_RSVD_1           15     /* Reserved 1                    */
#define MET_RM_DATA_V_CCR_NZ           14     /* CCR m Shift                   */
#define MET_RM_DATA_V_CCR_E             9     /* CCR m Shift                   */
#define MET_RM_DATA_V_CCR_M             0     /* CCR m Shift                   */

/* RM Cell Data Table.  Word 3                                                 */

#define MET_RM_DATA_M_RSVD_2       0x8000     /* Reserved 2                    */
#define MET_RM_DATA_M_MCR_NZ       0x4000     /* MCR m                         */
#define MET_RM_DATA_M_MCR_E        0x3E00     /* MCR m                         */
#define MET_RM_DATA_M_MCR_M        0x01FF     /* MCR m                         */

#define MET_RM_DATA_V_RSVD_2           15     /* Reserved 2                     */
#define MET_RM_DATA_V_MCR_NZ           14     /* MCR m Shift                   */
#define MET_RM_DATA_V_MCR_E             9     /* MCR m Shift                   */
#define MET_RM_DATA_V_MCR_M             0     /* MCR m Shift                   */

/* RM Cell Data Table word offsets.  Accessable via Peephole Interface         */

#define MET_O_RM_DATA_WORD_0         0x00     /* Word offset for word 0        */
#define MET_O_RM_DATA_ER             0x01     /* Word offset for ER            */
#define MET_O_RM_DATA_CCR            0x02     /* Word offset for CCR           */
#define MET_O_RM_DATA_MCR            0x03     /* Word offset for MCR           */

/* Xmt Slot Descriptors.  4 words/entry, 1 entry/VC                            */

/* Xmt Slot Descriptors.  Word 0                                               */

#define MET_XMT_DESC_M_RSVD        0x8000     /* Reserved                      */
#define MET_XMT_DESC_M_RAW         0x4000     /* Raw                           */
#define MET_XMT_DESC_M_IDLE        0x2000     /* Idle                          */
#define MET_XMT_DESC_M_MGMT        0x1000     /* Management                    */
#define MET_XMT_DESC_M_LINK        0x0FFF     /* Link                          */

#define MET_XMT_DESC_V_RSVD            15     /* Reserved                      */
#define MET_XMT_DESC_V_RAW             14     /* Raw Shift                     */
#define MET_XMT_DESC_V_IDLE            13     /* Idle Shift                    */
#define MET_XMT_DESC_V_MGMT            12     /* Management Shift              */
#define MET_XMT_DESC_V_LINK             0     /* Link Shift                    */

/* Xmt Slot Descriptors.  Word 1                                               */

#define MET_XMT_DESC_M_CRC_EN      0x8000     /* CRC10 Enable                  */
#define MET_XMT_DESC_M_EOP         0x4000     /* EOP                           */
#define MET_XMT_DESC_M_SIZE        0x3FFF     /* Slot Size                     */

#define MET_XMT_DESC_V_CRC_EN          15     /* CRC10 Enable Shift            */
#define MET_XMT_DESC_V_EOP             14     /* EOP Shift                     */
#define MET_XMT_DESC_V_SIZE             0     /* Slot Size Shift               */

/* Xmt Slot Descriptors.  Word 2                                               */

#define MET_XMT_DESC_M_ADDR_L      0xFFFF     /* Base Address Low              */

#define MET_XMT_DESC_V_ADDR_L           0     /* Base Address Low Shift        */

/* Xmt Slot Descriptors.  Word 3                                               */

#define MET_XMT_DESC_M_ADDR_H      0xFFFF     /* Base Address High             */

#define MET_XMT_DESC_V_ADDR_H           0     /* Base Address High Shift       */

/* Xmt Slot Descriptors word offsets.  Accessable via Peephole Interface       */

#define MET_O_XMT_DESC_WORD_0        0x00     /* Word offset for word 0        */
#define MET_O_XMT_DESC_WORD_1        0x01     /* Word offset for word 1        */
#define MET_O_XMT_DESC_ADDR_L        0x02     /* Word offset for Low Address   */
#define MET_O_XMT_DESC_ADDR_H        0x03     /* Word offset for High Address  */

#define MET_K_XMT_DESC_ENTRY_SIZE       4     /* 8 Words (16 bits) per entry   */

/* ABR/UBR Schedule Table.  2 words/entry, 4k entries                          */

/* ABR/UBR Schedule Table.  Word 0                                             */

#define MET_ABR_UBR_M_ACT          0x8000     /* Active                        */
#define MET_ABR_UBR_M_RSVD_0       0x7000     /* Reserved 0                    */
#define MET_ABR_UBR_M_LOW          0x0FFF     /* Low                           */

#define MET_ABR_UBR_V_ACT              15     /* Active Shift                  */
#define MET_ABR_UBR_V_RSVD_0           12     /* Reserved 0                    */
#define MET_ABR_UBR_V_LOW               0     /* Low                           */

/* ABR/UBR Schedule Table.  Word 1                                             */

#define MET_ABR_UBR_M_RSVD_1       0xF000     /* Reserved 1                    */
#define MET_ABR_UBR_M_HIGH         0x0FFF     /* High                          */

#define MET_ABR_UBR_V_RSVD_1           12     /* Reserved 1                    */
#define MET_ABR_UBR_V_HIGH              0     /* High Shift                    */

#define MET_K_ABR_UBR_ENTRY_SIZE        2     /* ABR/UBR Schedule entry size   */
#define MET_K_ABR_UBR_TABLE_SIZE     4096     /* ABR/UBR Schedule table size   */

/* ABR/UBR Schedule Table word offsets.  Accessable via Peephole Interface     */

#define MET_O_ABR_UBR_WORD_0         0x00     /* Word offset for low           */
#define MET_O_ABR_UBR_WORD_1         0x01     /* Word offset for high          */

/* CBR Schedule Table.  1 word/entry, 2-4k entries/table, 2 tables             */

#define MET_CBR_M_ACT              0x8000     /* Active                        */
#define MET_CBR_M_EOT              0x4000     /* EOT                           */
#define MET_CBR_M_RSVD             0x3000     /* Reserved                      */
#define MET_CBR_M_VC               0x0FFF     /* VC                            */

#define MET_CBR_V_ACT                  15     /* Active Shift                  */
#define MET_CBR_V_EOT                  14     /* EOT Shift                     */
#define MET_CBR_V_RSVD                 12     /* Reserved                      */
#define MET_CBR_V_VC                    0     /* VC Shift                      */

#define MET_CBR_K_ACTIVE              0x1     /* CBR Active                    */
#define MET_CBR_K_NOT_ACTIVE          0x0     /* CBR inactive                  */
#define MET_CBR_K_EOT                 0x1     /* EOT                           */
#define MET_CBR_K_NOT_EOT             0x0     /* Not EOT                       */

#define MET_K_CBR_ENTRY_SIZE          0x1     /* 1 Word per entry              */
#define MET_K_CBR_ENTRY_MAX          4096     /* Maximum of 4k entries         */

#define MET_K_CBR_INIT             0x4000     /* EOT bit set in all entries    */

/* ACR Lookup Table.  1 word/entry, 512 entries.                               */

#define MET_ACR_M_RSVD             0xFC00     /* Reserved                      */
#define MET_ACR_M_CELL_INT         0x03FF     /* Cell Interval                 */

#define MET_ACR_V_RSVD                 10     /* Reserved                      */
#define MET_ACR_V_CELL_INT              0     /* Cell Interval Shift           */

#define MET_K_ACR_ENTRY_MAX           512
#define MET_K_ACR_ENTRY_SIZE            1
#define MET_K_ACR_FIRST_ENTRY       0x2B1

#define MET_K_VC_MODE_00              0x0       
#define MET_K_VC_MODE_01              0x1
#define MET_K_PH_WRITE                0x0
#define MET_K_PH_READ                 0x1
#define MET_K_PH_SRAM_ACCESS          0x0
#define MET_K_PH_PRF_ACCESS           0x1
#define MET_K_XMT_FS_TAIL_256        0xff
#define MET_K_XMT_FS_TAIL_1K        0x3ff

#define MET_K_VC_MODE_256B_VC_TOT     256
#define MET_K_VC_MODE_1K_VC_TOT      1024   

/* SRAM Mapping

   VC Mode Select (Control 1) identifies the number of VC's supported.         
                                  00 - 256 Vc's                                
                                  01 -  1k Vc's                                
   The SRAM mapping is different depending upon the VC mode selected           
                                                                               */

#define MET_O_RCV_BFS_FIFO_256    0x0000      /* Rcv. Big Free FIFO  (256 VC)  */
#define MET_O_RCV_BFS_FIFO_1K     0x0000      /* Rcv. Big Free FIFO  (1K  VC)  */
#define MET_O_RCV_SFS_FIFO_256    0x0400      /* Rcv. Small Free FIFO(256 VC)  */
#define MET_O_RCV_SFS_FIFO_1K     0x0800      /* Rcv. Small Free FIFO(1K  VC)  */
#define MET_O_RCV_RFS_FIFO_256    0x0800      /* Rcv. Raw Cell Free  (256 VC)  */
#define MET_O_RCV_RFS_FIFO_1K     0x1000      /* Rcv. Raw Cell Free  (1K  VC)  */
#define MET_O_RCV_BIG_TAGS_256    0x1000      /* Rcv. AAL5 Big Tags  (256 VC)  */
#define MET_O_RCV_BIG_TAGS_1K     0xB400      /* Rcv. AAL5 Big Tags  (1K  VC)  */
#define MET_O_RCV_SML_TAGS_256    0x1200      /* Rcv. AAL5 Sml Tags  (256 VC)  */
#define MET_O_RCV_SML_TAGS_1K     0xB800      /* Rcv. AAL5 Sml Tags  (1K  VC)  */
#define MET_O_RCV_RAW_TAGS_256    0x1400      /* Rcv. Raw Tags       (256 VC)  */
#define MET_O_RCV_RAW_TAGS_1K     0xBC00      /* Rcv. Raw Tags       (1K  VC)  */
#define MET_O_RCV_TAG_TAB_256     0x1600      /* Rcv. Tag VC State   (256 VC)  */
#define MET_O_RCV_TAG_TAB_1K      0x1C00      /* Rcv. Tab VC State   (1K  VC)  */
#define MET_O_RCV_VC_TAB_256      0x1800      /* Rcv. VC State Table (256 VC)  */
#define MET_O_RCV_VC_TAB_1K       0x2000      /* Rcv. VC State Table (1K  VC)  */
#define MET_O_XMT_VC_TAB_256      0x2000      /* Xmt. VC State Table (256 VC)  */
#define MET_O_XMT_VC_TAB_1K       0x4000      /* Xmt. VC State Table (1K  VC)  */
#define MET_O_ABR_PARAM_256       0x2800      /* ABR Parameter Table (256 VC)  */
#define MET_O_ABR_PARAM_1K        0x6000      /* ABR Parameter Table (1K  VC)  */
#define MET_O_ABR_VALUE_256       0x3000      /* ABR Value Table     (256 VC)  */
#define MET_O_ABR_VALUE_1K        0x8000      /* ABR Value Table     (1K  VC)  */
#define MET_O_RM_DATA_256         0x3400      /* RM Cell Data Table  (256 VC)  */
#define MET_O_RM_DATA_1K          0x9000      /* RM Cell Data Table  (1K  VC)  */
#define MET_O_XMT_DESC_256        0x3800      /* Xmt. Slot Desc.     (256 VC)  */
#define MET_O_XMT_DESC_1K         0xA000      /* Xmt. Slot Desc.     (1K  VC)  */
#define MET_O_ACR_LOOK_256        0x3C00      /* ACR Lookup Table    (256 VC)  */
#define MET_O_ACR_LOOK_1K         0xB000      /* ACR Lookup Table    (1k  VC)  */
#define MET_O_ABR_SCHED_256       0x4000      /* ABR Schedule Table  (256 VC)  */
#define MET_O_ABR_SCHED_1K        0xC000      /* ABR Schedule Table  (1K  VC)  */
#define MET_O_CBR_SCHED_1_256     0x6000      /* CBR Schedule Table 1(256 VC)  */
#define MET_O_CBR_SCHED_1_1K      0xE000      /* CBR Schedule Table 1(1K  VC)  */
#define MET_O_CBR_SCHED_2_256     0x7000      /* CBR Schedule Table 2(256 VC)  */
#define MET_O_CBR_SCHED_2_1K      0xF000      /* CBR Schedule Table 2(1K  VC)  */


/* PCI Configuration Offsets                                                   */
 
#define MET_PCI_CFG_M_DEV_ID   0xFFFF0000      /* Device ID                    */
#define MET_PCI_CFG_M_VEND_ID  0x0000FFFF      /* Vendor ID                    */
#define MET_PCI_CFG_M_STATUS   0xFFFF0000      /* Status                       */
#define MET_PCI_CFG_M_CMD      0x0000FFFF      /* Command                      */
#define MET_PCI_CFG_M_CLASS    0xFFFFFF00      /* Class Code                   */
#define MET_PCI_CFG_M_REV_ID   0x000000FF      /* Revision ID                  */
#define MET_PCI_CFG_M_CACHE    0x000000FF      /* Cache Size                   */
#define MET_PCI_CFG_M_LAT      0x0000FF00      /* Latency Timer                */
#define MET_PCI_CFG_M_HEADER   0x00FF0000      /* Header Type                  */
#define MET_PCI_CFG_M_BIST     0xFF000000      /* BIST                         */
#define MET_PCI_CFG_M_BASE_0   0xFFFFFFFF      /* Base Address Register 0      */
#define MET_PCI_CFG_M_BASE_1   0xFFFFFFFF      /* Base Address Register 1      */
#define MET_PCI_CFG_M_BASE_2   0xFFFFFFFF      /* Base Address Register 2      */
#define MET_PCI_CFG_M_BASE_3   0xFFFFFFFF      /* Base Address Register 3      */
#define MET_PCI_CFG_M_BASE_4   0xFFFFFFFF      /* Base Address Register 4      */
#define MET_PCI_CFG_M_BASE_5   0xFFFFFFFF      /* Base Address Register 5      */
#define MET_PCI_CFG_M_CIS      0xFFFFFFFF      /* Cardbus CIS Pointer          */
#define MET_PCI_CFG_M_SUB_ID   0xFFFF0000      /* Subsystem ID                 */
#define MET_PCI_CFG_M_SUB_VEND 0x0000FFFF      /* Subsystem Vendor Id          */
#define MET_PCI_CFG_M_EXP_ROM  0xFFFFFFFF      /* Expansion ROM Base Address   */
#define MET_PCI_CFG_M_RSVD_0   0xFFFFFFFF      /* Reserved 0                   */
#define MET_PCI_CFG_M_RSVD_1   0xFFFFFFFF      /* Reserved 1                   */
#define MET_PCI_CFG_M_MAX_LAT  0xFF000000      /* Maximum Latency              */
#define MET_PCI_CFG_M_MIN_GNT  0x00FF0000      /* Minimum Grant                */
#define MET_PCI_CFG_M_INT_PIN  0x0000FF00      /* Interrupt Pin                */
#define MET_PCI_CFG_M_INT_LINE 0x000000FF      /* Interrupt Line               */

#define MET_PCI_CFG_V_DEV_ID           16      /* Device ID                    */
#define MET_PCI_CFG_V_VEND_ID           0      /* Vendor ID                    */
#define MET_PCI_CFG_V_STATUS           16      /* Status                       */
#define MET_PCI_CFG_V_CMD               0      /* Command                      */
#define MET_PCI_CFG_V_CLASS             8      /* Class Code                   */
#define MET_PCI_CFG_V REV_ID            0      /* Revision ID                  */
#define MET_PCI_CFG_V_CACHE             0      /* Cache Size                   */
#define MET_PCI_CFG_V_LAT               8      /* Latency Timer                */
#define MET_PCI_CFG_V_HEADER           16      /* Header Type                  */
#define MET_PCI_CFG_V_BIST             24      /* BIST                         */
#define MET_PCI_CFG_V_BASE_0            0      /* Base Address Register 0      */
#define MET_PCI_CFG_V_BASE_1            0      /* Base Address Register 1      */
#define MET_PCI_CFG_V_BASE_2            0      /* Base Address Register 2      */
#define MET_PCI_CFG_V_BASE_3            0      /* Base Address Register 3      */
#define MET_PCI_CFG_V_BASE_4            0      /* Base Address Register 4      */
#define MET_PCI_CFG_V_BASE_5            0      /* Base Address Register 5      */
#define MET_PCI_CFG_V_CIS               0      /* Cardbus CIS Pointer          */
#define MET_PCI_CFG_V_SUB_ID           16      /* Subsystem ID                 */
#define MET_PCI_CFG_V_SUB_VEND          0      /* Subsystem Vendor Id          */
#define MET_PCI_CFG_V_EXP_ROM           0      /* Expansion ROM Base Address   */
#define MET_PCI_CFG_V_RSVD_0            0      /* Reserved 0                   */
#define MET_PCI_CFG_V_RSVD_1            0      /* Reserved 1                   */
#define MET_PCI_CFG_V_MAX_LAT          24      /* Maximum Latency              */
#define MET_PCI_CFG_V_MIN_GNT          16      /* Minimum Grant                */
#define MET_PCI_CFG_V_INT_PIN           8      /* Interrupt Pin                */
#define MET_PCI_CFG_V_INT_LINE          0      /* Interrupt Line               */

#define MET_O_PCI_CFG_DEV_ID         0x02      /* Device ID                    */
#define MET_O_PCI_CFG_VEND_ID        0x00      /* Vendor ID                    */
#define MET_O_PCI_CFG_STATUS         0x06      /* Status                       */
#define MET_O_PCI_CFG_CMD            0x04      /* Command                      */
#define MET_O_PCI_CFG_CLASS          0x09      /* Class Code                   */
#define MET_O_PCI_CFG_REV_ID         0x08      /* Revision ID                  */
#define MET_O_PCI_CFG_BIST           0x0F      /* BIST                         */
#define MET_O_PCI_CFG_HEADER         0x0E      /* Header Type                  */
#define MET_O_PCI_CFG_LAT            0x0D      /* Latency Timer                */
#define MET_O_PCI_CFG_CACHE          0x0C      /* Cache Size                   */
#define MET_O_PCI_CFG_BASE_0         0x10      /* Base Address Register 0      */
#define MET_O_PCI_CFG_BASE_1         0x14      /* Base Address Register 1      */
#define MET_O_PCI_CFG_BASE_2         0x18      /* Base Address Register 2      */
#define MET_O_PCI_CFG_BASE_3         0x1C      /* Base Address Register 3      */
#define MET_O_PCI_CFG_BASE_4         0x20      /* Base Address Register 4      */
#define MET_O_PCI_CFG_BASE_5         0x24      /* Base Address Register 5      */
#define MET_O_PCI_CFG_CIS            0x28      /* Cardbus CIS Pointer          */
#define MET_O_PCI_CFG_SUB_ID         0x2E      /* Subsystem ID                 */
#define MET_O_PCI_CFG_SUB_VEND       0x2C      /* Subsystem Vendor Id          */
#define MET_O_PCI_CFG_EXP_ROM        0x30      /* Expansion ROM Base Address   */
#define MET_O_PCI_CFG_RSVD_0         0x34      /* Reserved 0                   */
#define MET_O_PCI_CFG_RSVD_1         0x38      /* Reserved 1                   */
#define MET_O_PCI_CFG_MAX_LAT        0x3F      /* Maximum Latency              */
#define MET_O_PCI_CFG_MIN_GNT        0x3E      /* Minimum Grant                */
#define MET_O_PCI_CFG_INT_PIN        0x3D      /* Interrupt Pin                */
#define MET_O_PCI_CFG_INT_LINE       0x3C      /* Interrupt Line               */


#define MET_O_PCI_CFG_ADDR_00        0x00      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_04        0x04      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_08        0x08      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_0C        0x0C      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_10        0x10      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_14        0x14      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_18        0x18      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_1C        0x1C      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_20        0x20      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_24        0x24      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_28        0x28      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_2C        0x2C      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_30        0x30      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_34        0x34      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_38        0x38      /* PCI Space Offset             */
#define MET_O_PCI_CFG_ADDR_3C        0x3C      /* PCI Space Offset             */

/* Transmit Report Queue Entry                                                 */

#define MET_XMT_RPT_M_RSVD_1   0xFFFF0000      /* Transmit Report Queue Rsvd 1 */
#define MET_XMT_RPT_M_VC       0x0000FFF0      /* Transmit Report Queue VC     */
#define MET_XMT_RPT_M_RSVD_0   0x0000000E      /* Tranmsit Report Queue Rsvd 0 */
#define MET_XMT_RPT_M_OWN      0x00000001      /* Transmit Report Queue Own    */

#define MET_XMT_RPT_V_RSVD_1           16      /* Tranmsit Report Queue Rsvd 1 */
#define MET_XMT_RPT_V_VC                4      /* Transmit Report Queue VC     */
#define MET_XMT_RPT_V_RSVD_0            1      /* Transmit Report Queue Rsvd 0 */
#define MET_XMT_RPT_V_OWN               0      /* Tranmsit Report Queue Own    */           

#define MET_XMT_RPT_K_MET_OWN           1     /* Meteor own bit                */
#define MET_XMT_RPT_K_ENTRY_SIZE        4     /* 4 Bytes per entry             */
#define MET_XMT_RPT_K_SIZE           1024     /* Xmt Status Report Queue Size  */

/* Receive Report Queue Entry                                                  */

#define MET_RCV_RPT_M_RSVD_0   0xFFFF0000      /* Reserved 0                   */
#define MET_RCV_RPT_M_TAG      0x0000FFFC      /* Receive Report Tag           */
#define MET_RCV_RPT_M_RAW      0x00000002      /* Receive Report Raw           */
#define MET_RCV_RPT_M_OWN      0x00000001      /* Receive Report Own           */

#define MET_RCV_RPT_M_EOP      0x80000000      /* Receive Report EOP           */
#define MET_RCV_RPT_M_SOP      0x40000000      /* Receive Report SOP           */
#define MET_RCV_RPT_M_BAD      0x20000000      /* Receive Report BAD           */
#define MET_RCV_RPT_M_STATUS   0x1C000000      /* Receive Report STATUS        */
#define MET_RCV_RPT_M_CLP      0x02000000      /* Receive Report CLP           */
#define MET_RCV_RPT_M_EFCI     0x01000000      /* Receive Report EFCI          */
#define MET_RCV_RPT_M_SIZE     0x00FFF000      /* Receive Report SIZE          */
#define MET_RCV_RPT_M_VC       0x00000FFF      /* Receive Report VC            */

#define MET_RCV_RPT_V_RSVD_0           16      /* Reserved 0                   */
#define MET_RCV_RPT_V_TAG               2      /* Receive Report Tag           */
#define MET_RCV_RPT_V_RAW               1      /* Receive Report Raw           */
#define MET_RCV_RPT_V_OWN               0      /* Receive Report Own           */

#define MET_RCV_RPT_V_EOP              31      /* Receive Report EOP           */
#define MET_RCV_RPT_V_SOP              30      /* Receive Report SOP           */
#define MET_RCV_RPT_V_BAD              29      /* Receive Report BAD           */
#define MET_RCV_RPT_V_STATUS           26      /* Receive Report STATUS        */
#define MET_RCV_RPT_V_CLP              25      /* Receive Report CLP           */
#define MET_RCV_RPT_V_EFCI             24      /* Receive Report EFCI          */
#define MET_RCV_RPT_V_SIZE             12      /* Receive Report SIZE          */
#define MET_RCV_RPT_V_VC                0      /* Receive Report VC            */

#define MET_RCV_RPT_K_MET_OWN           1      /* Meteor own bit               */
#define MET_RCV_RPT_K_ENTRY_SIZE        8      /* 8 Bytes per entry            */
#define MET_RCV_RPT_K_SIZE           3072      /* Rcv Status Report Queue Size */

#define MET_RCV_RPT_K_EOP               1      /* EOP                          */
#define MET_RCV_RPT_K_SOP               1      /* SOP                          */
#define MET_RCV_RPT_K_BAD               1      /* Bad                          */
#define MET_RCV_RPT_K_CLP               1      /* CLP                          */
#define MET_RCV_RPT_K_EFCI              1      /* EFCI                         */
 
/* Receive AAL5 Status Report Bad and Status encodings for Bad = 1             */

#define MET_RCV_RPT_STAT_K_CRC          0      /* CRC-32 Error                 */
#define MET_RCV_RPT_STAT_K_LEN          1      /* Length Error                 */
#define MET_RCV_RPT_STAT_K_ABORT        2      /* Aborted Packet               */
#define MET_RCV_RPT_STAT_K_CONGST_LOSS  3      /* Slot Congestion, Cell Loss   */
#define MET_RCV_RPT_STAT_K_LOSS         4      /* Other Cell Loss              */
#define MET_RCV_RPT_STAT_K_RATO         5      /* Reassembly Timer Timeout     */
#define MET_RCV_RPT_STAT_K_TOO_LONG     6      /* Packet too Long              */
#define MET_RCV_RPT_STAT_K_RSVD         7      /* Reserved                     */

/* Receive Raw Cell Status Longword                                            */

#define MET_RCV_RAW_STAT_M_RSVD_0      0xFFFF8000 /* Reserved_0                */
#define MET_RCV_RAW_STAT_M_CELL_LOSS   0x00004000 /* Cell Loss                 */
#define MET_RCV_RAW_STAT_M_SLOT_CONGST 0x00002000 /* Congestion                */
#define MET_RCV_RAW_STAT_M_CRC10_ERR   0x00001000 /* CRC10 Error               */
#define MET_RCV_RAW_STAT_M_VC          0x00000FFF /* VC                        */

#define MET_RCV_RAW_STAT_V_RSVD_0              15 /* Reserved_0                */
#define MET_RCV_RAW_STAT_V_CELL_LOSS           14 /* Cell Loss                 */
#define MET_RCV_RAW_STAT_V_SLOT_CONGST         13 /* Congestion                */
#define MET_RCV_RAW_STAT_V_CRC10_ERR           12 /* CRC10 Error               */
#define MET_RCV_RAW_STAT_V_VC                   0 /* VC                        */

/* Constants                                                                   */

#define MET_K_LINK_RATE         149760000      /* Rate in bits/sec             */
#define MET_K_CELLS_SEC            353207      /* Rate in Cells/sec            */
//#define MET_K_CELLS_SEC            390000      /* Rate in Cells/sec            */
#define MET_K_MAX_CBR_ENTRY          4096      /* Maximum number of CBR entries*/
#define MET_K_PRESCALE_VAL_MAX         15      /* Maximum prescale value       */
                                                                                     
#define MET_VC_MAP_K_DEFAULT            0      /* VCI/VPI mapping default value*/

#define MET_ABR_VAL_K_ACR_DEF      0x64B2      /* For 155 Mbits/sec cell rate. */

/* Report Queue Structures                                                     */

typedef struct
   {
   UINT32 lword_0;    /* Refer to MET_RCV_RPT_* definitions. */    
   UINT32 lword_1;    /* Refer to MET_RCV_RPT_* definitions. */ 
   } MET_RCV_RPT;

typedef struct
   {
   UINT32 lword_0;    /* Refer to MET_XMT_RPT_* definitions. */    
   } MET_XMT_RPT;

/* Pending Slot Structures. */

typedef struct
   {
   UINT32 lword_0;    /* Refer to MET_RCV_PEND_* definitions. */    
   UINT32 base_addr;  /* Refer to MET_RCV_PEND_* definitions. */ 
   } MET_RCV_PENDING_SLOT;

typedef struct
   {
   UINT32 lword_0;    /* Refer to MET_XMT_PEND_* definitions. */    
   UINT32 base_addr;  /* Refer to MET_XMT_PEND_* definitions. */ 
   } MET_XMT_PENDING_SLOT;

#define MET_RCV_K_PENDING_SLOT_CNT 8
#define MET_XMT_K_PENDING_SLOT_CNT 8

#endif	/* _MET_HW_H_ */
