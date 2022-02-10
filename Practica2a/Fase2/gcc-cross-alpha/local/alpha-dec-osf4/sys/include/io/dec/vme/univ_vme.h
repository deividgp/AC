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
 * @(#)$RCSfile: univ_vme.h,v $ $Revision: 1.1.2.5 $ (DEC) $Date: 1999/02/11 21:30:34 $
 */

#ifndef _UNIV_VME_H 
#define _UNIV_VME_H 

#include <io/common/devdriver.h>
#include <io/dec/vme/vba_generic.h>
#include <io/dec/vme/vbareg.h>
#include <machine/scb.h>
#include <kern/event.h>
#include <machine/machlimits.h>

#define	Regptr	((struct univ_vme_io_handles *)(vhp->adapt_regs))
#define	Varptr	((struct univ_vme_vars *)(vhp->adapt_vars))
#define Busvars ((struct univ_vme_busvars *)(vhp->bus_vars))

#define DEV_SCB_OFFSET     0x800

#define VSCB_OFFSET        0x1000
#define VME_SCB_VEC_BASE   0x1180 /* Base of User Specified Vectors for VME */
#define VME_MAX_SCB_VEC    0x1FF0 /* Last valid User Specified Vector       */

#define MAX_UNIV_VME_INT_HNDLRS 4

#define VME_COMMON_INDEX   0
#define VME_RESET_INDEX    0
#define VME_SPL3_INDEX     1
#define VME_SPL4_INDEX     2
#define VME_SPL6_INDEX     3

#define VME_RESET_VEC      (DEV_SCB_OFFSET + 0x80)   /* 0x880 */
#define VME_SPL3_VEC       (DEV_SCB_OFFSET + 0x90)   /* 0x890 */
#define VME_SPL4_VEC       (DEV_SCB_OFFSET + 0xA0)   /* 0x8A0 */
#define VME_SPL6_VEC       (DEV_SCB_OFFSET + 0xB0)   /* 0x8B0 */

#define VP_INTR_VME_RESET (1UL << 24)
#define VP_INTR_VME_SPL3  (1UL << 25)
#define VP_INTR_VME_SPL4  (1UL << 26)
#define VP_INTR_VME_SPL6  (1UL << 27)
#define VP_INTR_ALL       (ULONG_MAX)

#define VME_MIN_VEC       24                      /* vec 0x18 SCB 0x1180 */
#define VME_MAX_VEC      255                      /* vec 0xFF SCB 0x1FF0 */
#define UNIV_VME_IPL_1     1
#define UNIV_VME_IPL_7     7

#define UNIV_PCI_SW_VEC    0x10E0
#define UNIV_USER_IACK_VEC 0x10F0
#define UNIV_LM0_VEC       0x1100
#define UNIV_LM1_VEC       0x1110
#define UNIV_LM2_VEC       0x1120
#define UNIV_LM3_VEC       0x1130
#define UNIV_MBOX0_VEC     0x1140 /* Module Switch 0 vector */
#define UNIV_MBOX1_VEC     0x1150 /* Module Switch 1 vector */
#define UNIV_MBOX2_VEC     0x1160 /* Module Switch 2 vector */
#define UNIV_MBOX3_VEC     0x1170 /* Module Switch 3 vector */

#define UNIV_PCI_SW_VECTOR     0xE
#define UNIV_USER_IACK_VECTOR  0xF
#define UNIV_LM0_VECTOR       0x10
#define UNIV_LM1_VECTOR       0x11
#define UNIV_LM2_VECTOR       0x12
#define UNIV_LM3_VECTOR       0x13
#define UNIV_MBOX0_VECTOR     0x14 /* Module Switch 0 SCB offset */
#define UNIV_MBOX1_VECTOR     0x15 /* Module Switch 1 SCB offset */
#define UNIV_MBOX2_VECTOR     0x16 /* Module Switch 2 SCB offset */
#define UNIV_MBOX3_VECTOR     0x17 /* Module Switch 3 SCB offset */

#define VEC_IRQ_ZERO_MASK  0xFE

#define VEC_VMEBUS_SELECT  0x20000000UL
#define VEC_CTLR_SELECT    0x40000000UL
#define VEC_ADAPT_SELECT   0x80000000UL
#define VEC_IRQ_MASK       0x00070000UL
#define VEC_BUS_NUM_MASK   0x00700000UL
#define VECTOR_MASK        0x00001FFFUL

#define VEC_IRQ_SHIFT      16
#define VEC_BUS_NUM_SHIFT  20

#define UNIV_4_GB   0x100000000UL
#define UNIV_3_GB   (3 * 1024 * 1024 *1024)
#define UNIV_2_GB   (2 * 1024 * 1024 *1024)
#define UNIV_1_GB   (1 * 1024 * 1024 *1024)
#define UNIV_640_MB (640 * 1024 * 1024)
#define UNIV_512_MB (512 * 1024 *1024)
#define UNIV_256_MB (256 * 1024 *1024)
#define UNIV_128_MB (128 * 1024 *1024)
#define UNIV_64_MB   (64 * 1024 * 1024)
#define UNIV_32_MB   (32 * 1024 * 1024)
#define UNIV_16_MB   (16 * 1024 * 1024)
#define UNIV_8_MB     (8 * 1024 * 1024)
#define UNIV_4_MB     (4 * 1024 * 1024)
#define UNIV_2_MB     (2 * 1024 * 1024)
#define UNIV_1_MB     (1 * 1024 * 1024)
#define UNIV_512_KB (512 * 1024)
#define UNIV_256_KB (256 * 1024)
#define UNIV_128_KB (128 * 1024)
#define UNIV_64_KB   (64 * 1024)
#define UNIV_32_KB   (32 * 1024)
#define UNIV_16_KB   (16 * 1024)
#define UNIV_8_KB     (8 * 1024)
#define UNIV_4_KB     (4 * 1024)

/*
 * Universe Register Declarations
 */

/*
 * All Universe registers are visible in PCI Memory Space as offsets
 * from the CSR base register (the only region of PCI space utilised by  
 * the Universe and described by a BAR is the 4KB CSR space). The PCI
 * configuration registers appear in both PCI config space and PCI 
 * memory space.
 * 
 * These declarations are for the address offsets.
 *
 */ 

/***************************************************************************/
/*                                                                         */
/*        PCI Configuration Registers                                      */
/*                                                                         */
/***************************************************************************/

/*
 * May want to declare control and status as 2 word offsets as opposed to 
 * one longword
 */

#define UNIV_PCI_ID    0x0000UL  /* PCI Config ID register                   */
#define UNIV_PCI_CSR   0x0004UL  /* PCI Config Space Control/Status Regs     */
#define UNIV_PCI_CLASS 0x0008UL  /* PCI Config Class register                */

/*
 * Next definition is for a  longword that contains the 
 * BIST/HEADER/Latency timer and cache line size registers.
 * These may not be needed at all. If they are it may be better
 * to declare byte offsets but for now this will do.
 */

#define UNIV_PCI_MISC0 0x000CUL  /* PCI Config MISC 0 register               */
#define UNIV_PCI_BS    0x0010UL  /* PCI Config Base Address Register         */
#define UNIV_PCI_BS1   0x0014UL  /* PCI Config Base Address Register 1       */

/*
 * PCI_MISC1 register contains bits for Max_latency, min gnt, interrupt pin
 * and interrupt line registers.
 */

#define UNIV_PCI_MISC1 0x003CUL  /* PCI Config MISC 1 register               */

/*****************************************************************************/
/*                                                                           */
/*  Tundra's Control and Status Register Offsets from the base of the PCI    */
/*  configuration header's UNIV_PCI_BS and UNIV_PCI_BS1 entry.               */
/*                                                                           */
/*****************************************************************************/

#define UNIV_LSI0_CTL 0x0100UL   /* PCI Slave Image 0 Control Register       */
#define UNIV_LSI0_BS  0x0104UL   /* PCI Slave Image 0 Base Address Register  */
#define UNIV_LSI0_BD  0x0108UL   /* PCI Slave Image 0 Bound Address Register */
#define UNIV_LSI0_TO  0x010CUL   /* PCI Slave Image 0 Translation Offset Reg */
                                 /* Univere reserved 0x0110UL                */
#define UNIV_LSI1_CTL 0x0114UL   /* PCI Slave Image 1 Control Register       */
#define UNIV_LSI1_BS  0x0118UL   /* PCI Slave Image 1 Base Address Register  */
#define UNIV_LSI1_BD  0x011CUL   /* PCI Slave Image 1 Bound Address Register */
#define UNIV_LSI1_TO  0x0120UL   /* PCI Slave Image 1 Translation Offset Reg */
                                 /* Universe Reserved 0x0124UL               */
#define UNIV_LSI2_CTL 0x0128UL   /* PCI Slave Image 2 Control Register       */
#define UNIV_LSI2_BS  0x012CUL   /* PCI Slave Image 2 Base Address Register  */
#define UNIV_LSI2_BD  0x0130UL   /* PCI Slave Image 2 Bound Address Register */
#define UNIV_LSI2_TO  0x0134UL   /* PCI Slave Image 2 Translation Offset Reg */
                                 /* Universe Reserved 0x0138UL               */
#define UNIV_LSI3_CTL 0x013CUL   /* PCI Slave Image 3 Control Register       */
#define UNIV_LSI3_BS  0x0140UL   /* PCI Slave Image 3 Base Address Register  */
#define UNIV_LSI3_BD  0x0144UL   /* PCI Slave Image 3 Bound Address Register */
#define UNIV_LSI3_TO  0x0148UL   /* PCI Slave Image 3 Translation Offset Reg */
                                 /* Universe Reserved 0x014CUL - 0x016CUL    */
#define UNIV_SCYC_CTL  0x0170UL  /* Special Cycle Control Register           */
#define UNIV_SCYC_ADDR 0x0174UL  /* Special Cycle PCI Address Register       */
#define UNIV_SCYC_EN   0x0178UL  /* Special Cycle Swap/Compare Enable Reg    */
#define UNIV_SCYC_CMP  0x017CUL  /* Special Cycle Compare Data Register      */
#define UNIV_SCYC_SWP  0x0180UL  /* Special Cycle Swap Data Register         */
#define UNIV_LMISC     0x0184UL  /* Universe PCI Misc register (timers)      */
#define UNIV_SLSI      0x0188UL  /* Special PCI Slave Image.                 */
#define UNIV_L_CMDERR  0x018CUL  /* PCI Command Error log                    */
#define UNIV_LAERR     0x0190UL  /* PCI Address Error log                    */
                                 /* Universe Reserved 0x0194UL - 0x019CUL    */
#define UNIV_LSI4_CTL  0x01A0UL  /* PCI Slave Image 4 Control Register       */
#define UNIV_LSI4_BS   0x01A4UL  /* PCI Slave Image 4 Base Address Reg       */
#define UNIV_LSI4_BD   0x01A8UL  /* PCI Slave Image 4 Bound Address Reg      */
#define UNIV_LSI4_TO   0x01ACUL  /* PCI Slave Image 4 Translation Offset Reg */
                                 /* Univere reserved 0x01B0UL                */
#define UNIV_LSI5_CTL  0x01B4UL  /* PCI Slave Image 5 Control Register       */
#define UNIV_LSI5_BS   0x01B8UL  /* PCI Slave Image 5 Base Address Register  */
#define UNIV_LSI5_BD   0x01BCUL  /* PCI Slave Image 5 Bound Address Register */
#define UNIV_LSI5_TO   0x01C0UL  /* PCI Slave Image 5 Translation Offset Reg */
                                 /* Universe Reserved 0x01C4UL               */
#define UNIV_LSI6_CTL  0x01C8UL  /* PCI Slave Image 6 Control Register       */
#define UNIV_LSI6_BS   0x01CCUL  /* PCI Slave Image 6 Base Address Register  */
#define UNIV_LSI6_BD   0x01D0UL  /* PCI Slave Image 6 Bound Address Register */
#define UNIV_LSI6_TO   0x01D4UL  /* PCI Slave Image 6 Translation Offset Reg */
                                 /* Universe Reserved 0x01D8UL               */
#define UNIV_LSI7_CTL  0x01DCUL  /* PCI Slave Image 7 Control Register       */
#define UNIV_LSI7_BS   0x01E0UL  /* PCI Slave Image 7 Base Address Register  */
#define UNIV_LSI7_BD   0x01E4UL  /* PCI Slave Image 7 Bound Address Register */
#define UNIV_LSI7_TO   0x01E8UL  /* PCI Slave Image 7 Translation Offset Reg */
                                 /* Universe Reserved 0x01ECUL - 0x01FCUL    */
#define UNIV_DCTL      0x0200UL  /* DMA Transfer Control Register.           */
#define UNIV_DTBC      0x0204UL  /* DMA Transfer Byte Register.              */
#define UNIV_DLA       0x0208UL  /* DMA PCI Bus Address Register.            */
                                 /* Universe Reserved 0x020CUL               */
#define UNIV_DVA       0x0210UL  /* DMA VMEbus Address Register.             */
                                 /*  Universe Reserved 0x0214UL              */
#define UNIV_DCPP      0x0218UL  /* DMA Command Packet Pointer.              */
                                 /* Universe Reserved 0x021CUL               */
#define UNIV_DGCS      0x0220UL  /* DMA General Control and status Register  */
#define UNIV_DLLUE     0x0224UL  /* DMA Linked List Update Enable Register   */
                                 /* Universe Reserved 0x0228UL - 0x02FCUL    */
#define UNIV_LINT_EN   0x0300UL  /* PCI Interrupt Enable Register            */
#define UNIV_LINT_STAT 0x0304UL  /* PCI Interrupt Status Register            */
#define UNIV_LINT_MAP0 0x0308UL  /* PCI Interrupt Map 0 Register             */
#define UNIV_LINT_MAP1 0x030CUL  /* PCI Interrupt Map 1 Register             */
#define UNIV_VINT_EN   0x0310UL  /* VMEbus Interrupt Enable Register         */
#define UNIV_VINT_STAT 0x0314UL  /* VMEbus Interrupt Status Register         */
#define UNIV_VINT_MAP0 0x0318UL  /* VMEbus Interrupt Map 0 Register          */
#define UNIV_VINT_MAP1 0x031CUL  /* VMEbus Interrupt Map 1 Register          */
#define UNIV_STATID    0x0320UL  /* Interrupt Status/ID out Register         */
#define UNIV_V1_STATID 0x0324UL  /* VMEbus IRQ1 Status/ID out Register       */
#define UNIV_V2_STATID 0x0328UL  /* VMEbus IRQ2 Status/ID out Register       */
#define UNIV_V3_STATID 0x032CUL  /* VMEbus IRQ3 Status/ID out Register       */
#define UNIV_V4_STATID 0x0330UL  /* VMEbus IRQ4 Status/ID out Register       */
#define UNIV_V5_STATID 0x0334UL  /* VMEbus IRQ5 Status/ID out Register       */
#define UNIV_V6_STATID 0x0338UL  /* VMEbus IRQ6 Status/ID out Register       */
#define UNIV_V7_STATID 0x033CUL  /* VMEbus IRQ7 Status/ID out Register       */
#define UNIV_LINT_MAP2 0x0340UL  /* Local Interrupt Map 2 Register           */
#define UNIV_VINT_MAP2 0x0344UL  /* VME interrupt Map 2 Register             */
#define UNIV_MBOX0     0x0348UL  /* Malibox 0                                */
#define UNIV_MBOX1     0x034CUL  /* Malibox 1                                */
#define UNIV_MBOX2     0x0350UL  /* Malibox 2                                */
#define UNIV_MBOX3     0x0354UL  /* Malibox 3                                */
#define UNIV_SEMA0     0x0358UL  /* Semaphore 0                              */
#define UNIV_SEMA1     0x035CUL  /* Semaphore 1                              */
                                 /* Universe Reserved 0x0360UL - 0x03FCUL    */
#define UNIV_MAST_CTL  0x0400UL  /* Master Control Register                  */
#define UNIV_MISC_CTL  0x0404UL  /* Miscellaneous Control Register           */
#define UNIV_MISC_STAT 0x0408UL  /* Miscellaneous Status Register            */
#define UNIV_USER_AM   0x040CUL  /* User Address modifier code Register      */
                                 /* Universe Reserved 0x0410UL - 0x0EFCUL    */
#define UNIV_VSI0_CTL  0x0F00UL  /* VMEbus Slave Image 0 Control Register    */
#define UNIV_VSI0_BS   0x0F04UL  /* VMEbus Slave Image 0 Base Address        */
#define UNIV_VSI0_BD   0x0F08UL  /* VMEbus Slave Image 0 Bound Address       */
#define UNIV_VSI0_TO   0x0F0CUL  /* VMEbus Slave Image 0 Translation Offset  */
                                 /* Universe Reserved 0x0F10UL               */
#define UNIV_VSI1_CTL  0x0F14UL  /* VMEbus Slave Image 1 Control Register    */
#define UNIV_VSI1_BS   0x0F18UL  /* VMEbus Slave Image 1 Base Address        */
#define UNIV_VSI1_BD   0x0F1CUL  /* VMEbus Slave Image 1 Bound Address       */
#define UNIV_VSI1_TO   0x0F20UL  /* VMEbus Slave Image 1 Translation Offset  */
                                 /* Universe Reserved 0x0F24UL               */
#define UNIV_VSI2_CTL  0x0F28UL  /* VMEbus Slave Image 2 Control Register    */
#define UNIV_VSI2_BS   0x0F2CUL  /* VMEbus Slave Image 2 Base Address        */
#define UNIV_VSI2_BD   0x0F30UL  /* VMEbus Slave Image 2 Bound Address       */
#define UNIV_VSI2_TO   0x0F34UL  /* VMEbus Slave Image 2 Translation Offset  */
                                 /* Universe Reserved 0x0F38UL               */
#define UNIV_VSI3_CTL  0x0F3CUL  /* VMEbus Slave Image 3 Control Register    */
#define UNIV_VSI3_BS   0x0F40UL  /* VMEbus Slave Image 3 Base Address        */
#define UNIV_VSI3_BD   0x0F44UL  /* VMEbus Slave Image 3 Bound Address       */
#define UNIV_VSI3_TO   0x0F48UL  /* VMEbus Slave Image 3 Translation Offset  */
                                 /* Universe Reserved 0x0F4CUL - 0x0F60UL    */
#define UNIV_LM_CTL    0x0F64UL  /* Location Monitor Control                 */
#define UNIV_LM_BS     0x0F68UL  /* Location Monitor Base Address Register   */
                                 /* Universe Reserved 0x0F6cUL               */
#define UNIV_VRAI_CTL  0x0F70UL  /* VMEbus Register Access Image Control     */
#define UNIV_VRAI_BS   0x0F74UL  /* VMEbus Register Access BAse Address      */
                                 /* Universe Reserved 0xF78UL - 0xF7CUL      */
#define UNIV_VCSR_CTL  0x0F80UL  /* VMEbus CSR Control Register              */
#define UNIV_VCSR_TO   0x0F84UL  /* VMEbus CSR Translation Offset            */
#define UNIV_V_AMERR   0x0F88UL  /* VMEbus Address Modifier Code Error log   */
#define UNIV_VAERR     0x0F8CUL  /* VMEbus Address Error log                 */

#define UNIV_VSI4_CTL  0x0F90UL  /* VMEbus Slave Image 4 Control             */
#define UNIV_VSI4_BS   0x0F94UL  /* VMEbus Slave Image 4 Base Address Reg    */
#define UNIV_VSI4_BD   0x0F98UL  /* VMEbus Slave Image 4 Bound Address Reg   */
#define UNIV_VSI4_TO   0x0F9CUL  /* VMEbus Slave Image 4 Translation Offset  */
                                 /* Universe Reserved 0x0FA0UL               */
#define UNIV_VSI5_CTL  0x0FA4UL  /* VMEbus Slave Image 5 Control             */
#define UNIV_VSI5_BS   0x0FA8UL  /* VMEbus Slave Image 5 Base Address Reg    */
#define UNIV_VSI5_BD   0x0FACUL  /* VMEbus Slave Image 5 Bound Address Reg   */
#define UNIV_VSI5_TO   0x0FB0UL  /* VMEbus Slave Image 5 Translation Offset  */
                                 /* Universe Reserved 0x0FB4UL               */
#define UNIV_VSI6_CTL  0x0FB8UL  /* VMEbus Slave Image 6 Control             */
#define UNIV_VSI6_BS   0x0FBCUL  /* VMEbus Slave Image 6 Base Address Reg    */
#define UNIV_VSI6_BD   0x0FC0UL  /* VMEbus Slave Image 6 Bound Address Reg   */
#define UNIV_VSI6_TO   0x0FC4UL  /* VMEbus Slave Image 6 Translation Offset  */
                                 /* Universe Reserved 0x0FC8UL               */
#define UNIV_VSI7_CTL  0x0FCCUL  /* VMEbus Slave Image 7 Control             */
#define UNIV_VSI7_BS   0x0FD0UL  /* VMEbus Slave Image 7 Base Address Reg    */
#define UNIV_VSI7_BD   0x0FD4UL  /* VMEbus Slave Image 7 Bound Address Reg   */
#define UNIV_VSI7_TO   0x0FD8UL  /* VMEbus Slave Image 7 Translation Offset  */
                                 /* Universe Reserved 0x0FDCUL - 0x0FECUL    */
                                 /* VME CR/CSR Reserved 0x0FF0UL             */
#define UNIV_VCSR_CLR  0x0FF4UL  /* VMEbus CSR Bit Clear Register            */
#define UNIV_VCSR_SET  0x0FF8UL  /* VMEbus CSR Bit SET Register              */
#define UNIV_VCSR_BS   0x0FFCUL  /* VMEbus CSR Base Address Register         */

/*****************************************************************************
 * PCI_ID (0x000) - PCI Configuration Space ID Register                      *
 *****************************************************************************/

#define PCI_ID_DID_MSK     0xFFFF0000   /* Mask for Device ID Value          */
#define PCI_ID_VUD_MSK     0x0000FFFF   /* Mask for Vendir ID Value          */

/*****************************************************************************
 * PCI_CSR (0x004) - PCI Configuration Space Control & Status Register       *
 *****************************************************************************/

#define PCI_CSR_D_PE       0x80000000   /* Parity Error Detected             */
#define PCI_CSR_S_ERR      0x40000000   /* SERR# asserted                    */
#define PCI_CSR_R_MA       0x20000000   /* Received Master Abort             */
#define PCI_CSR_R_TA       0x10000000   /* Received Target Abort             */
#define PCI_CSR_S_TA       0x08000000   /* Signaled Target Abort             */
#define PCI_CSR_DEVSEL_MSK 0x06000000   /* Mask for Device Select Timing     */
#define PCI_CSR_DP_D       0x01000000   /* Data Parity Detected              */
#define PCI_CSR_TFBBC      0x00800000   /* Target Fast Back to Back Capable  */
#define PCI_CSR_MFBBC      0x00000200   /* Master Fast BAck to BAck Enable   */
#define PCI_CSR_SERR_EN    0x00000100   /* SERR# Enable                      */
#define PCI_CSR_WAIT       0x00000080   /* Wait Cycle Control                */
#define PCI_CSR_PERESP     0x00000040   /* Parity Error Response Enable      */
#define PCI_CSR_VGAPS      0x00000020   /* VGA Palette Snoop                 */
#define PCI_CSR_MWI_EN     0x00000010   /* Memory Write and Invalidate Enable*/
#define PCI_CSR_SC         0x00000008   /* Special Cycles Enable             */
#define PCI_CSR_BM         0x00000004   /* Master Enable                     */
#define PCI_CSR_MS         0x00000002   /* Target Memory Enable              */
#define PCI_CSR_IOS        0x00000001   /* Target I/O Enable                 */

/*****************************************************************************
 * PCI_CLASS (0x008) - PCI Configuration Class Register                      *
 *****************************************************************************/

#define PCI_CLASS_BASE_MSK 0xFF000000   /* Mask for Base Class Code          */
#define PCI_CLASS_SUB_MSK  0x00FF0000   /* Mask for Sub Class Code           */
#define PCI_CLASS_PROG_MSK 0x0000FF00   /* Mask for Programming Interface    */
#define PCI_CLASS_RID_MSK  0x000000FF   /* Mask for Revision ID (Rev 1)      */

/*****************************************************************************
 * PCI_MISC0 (0x00C) - PCI Configuration Miscellaneous 0 Register            *
 *****************************************************************************/

#define PCI_MISC0_BISTC_MSK  0x80000000   /* Mask bit for BISTC              */
#define PCI_MISC0_SBIST_MSK  0x40000000   /* Mask bit for Start BIST         */
#define PCI_MISC0_CCODE_MSK  0x0F000000   /* Mask for Completion Codes       */
#define PCI_MISC0_MFUNC_MSK  0x00800000   /* Mask for Multifunction Device   */
#define PCI_MISC0_LAYOUT_MSK 0x007F0000   /* Mask for Configuration Space    */
#define PCI_MISC0_LTIMER_MSK 0x0000F800   /* Mask for Latency Timer          */

/*****************************************************************************
 * PCI_BS (0x010) - PCI Configuration Base Address Register                  *
 *****************************************************************************/

#define PCI_BS_MSK         0xFFFFF000   /* Mask for Base Address Bits 31:12  */
#define PCI_BS_SPACE_IO    0x00000001   /* Local Bus Address Space = I/O     */
#define PCI_BS_SPACE_MEM   0x00000000   /* Local Bus Address Space = Mem     */

/*****************************************************************************
 * PCI_BS1 (0x014) - PCI Configuration Base Address Register 1                *
 *****************************************************************************/

#define PCI_BS1_MSK        0xFFFFF000   /* Mask for Base Address Bits 31:12  */
#define PCI_BS1_SPACE_IO   0x00000001   /* Local Bus Address Space = I/O     */
#define PCI_BS1_SPACE_MEM  0x00000000   /* Local Bus Address Space = Mem     */

/*****************************************************************************
 * PCI_MISC1 (0x03C) - PCI Configuration Miscellaneous 1  Register           *
 *****************************************************************************/

#define PCI_MISC1_MAX_LAT  0xFF000000   /* Mask for Maximum Latency          */
#define PCI_MISC1_MIN_GNT  0x00FF0000   /* Mask for Minimum Grant            */
#define PCI_MISC1_INT_PIN  0x0000FF00   /* Mask for Interrupt Pin            */
#define PCI_MISC1_INT_LINE 0x000000FF   /* Mask for Interrupt Line           */
 
/*****************************************************************************/
/*   Tundra's PCI Slave Image Registers used to configure PCI to VMEbus      */
/*   windows. It is the intent that the PCI base and bound registers will    */
/*   be configured by firmware. The 64mb aligned window used for the         */
/*   Special PCI slave image window must also be configured by firmware.     */
/*                                                                           */
/*   The firmware should also setup the PCI Slave Image Control registers    */
/*   to indicate that the windows are in PCI I/O or PCI Memory space.        */
/*****************************************************************************/


/*****************************************************************************
 * LSI0_CTL (0x100) - PCI slave Image 0 Control Register                     *
 * LSI1_CTL (0x114) - PCI slave Image 1 Control Register                     *
 * LSI2_CTL (0x128) - PCI slave Image 2 Control Register                     *
 * LSI3_CTL (0x13C) - PCI slave Image 3 Control Register                     *
 * LSI4_CTL (0x1A0) - PCI slave Image 4 Control Register                     *
 * LSI5_CTL (0x1B4) - PCI slave Image 5 Control Register                     *
 * LSI6_CTL (0x1C8) - PCI slave Image 6 Control Register                     *
 * LSI7_CTL (0x1DC) - PCI slave Image 7 Control Register                     *
 *****************************************************************************/

#define LSIX_CTL_EN        0x80000000 /* Enable  PCI slave image             */
#define LSIX_CTL_DSBL      0x00000000 /* Disable PCI slave image             */
#define LSIX_EN_SHIFT      31

#define LSIX_CTL_P_WRT     0x40000000 /* Enable  posted write                */
#define LSIX_CTL_NO_P_WRT  0x00000000 /* Disable posted write                */
#define LSIX_P_WRT_SHIFT   30

#define LSIX_CTL_DW_08     0x00000000 /* VMEbus maximum data width =  8 bits */
#define LSIX_CTL_DW_16     0x00400000 /* VMEbus maximum data width = 16 bits */
#define LSIX_CTL_DW_32     0x00800000 /* VMEbus maximum data width = 32 bits */
#define LSIX_CTL_DW_64     0x00C00000 /* VMEbus maximum data width = 64 bits */
#define LSIX_DW_SHIFT  22

#define LSIX_CTL_A16       0x00000000 /* Map PCI to A16 VMEbus Address space */
#define LSIX_CTL_A24       0x00010000 /* Map PCI to A24 VMEbus Address space */
#define LSIX_CTL_A32       0x00020000 /* Map PCI to A32 VMEbus Address space */
#define LSIX_CTL_RSV1      0x00030000 /* Reserved                            */
#define LSIX_CTL_RSV2      0x00040000 /* Reserved                            */
#define LSIX_CTL_CR_CSR    0x00050000 /* Map PCI to VME CR/CSR Address space */
#define LSIX_CTL_USR1      0x00060000 /* Map PCI to User1 VME Address space  */
#define LSIX_CTL_USR2      0x00070000 /* MAP PCI to USer2 VME Address space  */
#define LSIX_AS_SHIFT      16

#define LSIX_CTL_DATA      0x00000000 /* Data Address Modifiers              */
#define LSIX_CTL_PROG      0x00004000 /* Program Address Modifiers           */
#define LSIX_PD_SHIFT      14

#define LSIX_CTL_USER      0x00000000 /* User Address Modifier               */
#define LSIX_CTL_SUPER     0x00001000 /* Supervisor Address Modifier         */
#define LSIX_US_SHIFT      12

#define LSIX_CTL_NO_BLT    0x00000000 /* Do not generate block transfers     */
                                      /* from multi-data beat PCI cycles     */
#define LSIX_CTL_EN_BLT    0x00000100 /* Generate block transfers            */
                                      /* from multi-data beat PCI cycles     */
#define LSIX_CS_SHIFT      8

#define LSIX_CTL_PCI_MEM   0x00000000 /* Image responds to PCI Memory cycles */
#define LSIX_CTL_PCI_IO    0x00000001 /* Image responds to PCI I/O cycles    */
#define LSIX_CTL_PCI_CFG   0x00000002 /* Image responds to PCI Config cycles */

/*****************************************************************************
 * LSI0_BS (0x104) - PCI Slave Image 0 Base Address Register                 *
 * LSI1_BS (0x118) - PCI Slave Image 1 Base Address Register                 *
 * LSI2_BS (0x12C) - PCI Slave Image 2 Base Address Register                 *
 * LSI3_BS (0x140) - PCI Slave Image 3 Base Address Register                 *
 * LSI4_BS (0x1A4) - PCI Slave Image 4 Base Address Register                 *
 * LSI5_BS (0x1B8) - PCI Slave Image 5 Base Address Register                 *
 * LSI6_BS (0x1CC) - PCI Slave Image 6 Base Address Register                 *
 * LSI7_BS (0x1E0) - PCI Slave Image 7 Base Address Register                 *
 *                                                                           *
 * The base adress specifies the lowest PCI address in the address range     *
 * that will be decoded.                                                     *
 *                                                                           *
 * PCI Slave images 0 and 4 have a 4KB granularity. Therfore, bits 11:00 are *
 * not compared. The remaining PCI slave images have a 64KB granularity.     *
 * Therefore, bits 15:00 are not compared.                                   *
 *****************************************************************************/

#define LSIX_BS_4K_MASK    0xfffff000 /* Image matches bits 31:12 of PCI Addr*/
#define LSIX_BS_64K_MASK   0xffff0000 /* Image matches bits 31:16 of PCI Addr*/


/*****************************************************************************
 * LSI0_BD (0x108) - PCI Slave Image 0 Bound Address Register                *
 * LSI1_BD (0x11C) - PCI Slave Image 1 Bound Address Register                *
 * LSI2_BD (0x130) - PCI Slave Image 2 Bound Address Register                *
 * LSI3_BD (0x144) - PCI Slave Image 3 Bound Address Register                *
 * LSI4_BD (0x1A8) - PCI Slave Image 4 Bound Address Register                *
 * LSI5_BD (0x1BC) - PCI Slave Image 5 Bound Address Register                *
 * LSI6_BD (0x1D0) - PCI Slave Image 6 Bound Address Register                *
 * LSI7_BD (0x1E4) - PCI Slave Image 7 Bound Address Register                *
 *                                                                           *
 * The address decoded in a slave image are those that are greater than      *
 * or equal to the base address and less than the PCI bound address.         *
 *                                                                           *
 * PCI Slave images 0 and 4 have a 4KB granularity. Therfore, bits 11:00 are *
 * not compared. The remaining PCI slave images have a 64KB granularity.     *
 * Therefore, bits 15:00 are not compared.                                   *
 *****************************************************************************/

#define LSIX_BD_4K_MASK    0xfffff000 /* Image 0 & 4 bound address mask      */
#define LSIX_BD_64K_MASK   0xffff0000 /* Images not 0 & 4 bound address mask */

/*****************************************************************************
 * LSI0_TO (0x10C) - PCI Slave Image 0 Translation Offset Register           *
 * LSI1_TO (0x120) - PCI Slave Image 1 Translation Offset Register           *
 * LSI2_TO (0x134) - PCI Slave Image 2 Translation Offset Register           *
 * LSI3_TO (0x148) - PCI Slave Image 3 Translation Offset Register           *
 * LSI4_TO (0x1AC) - PCI Slave Image 4 Translation Offset Register           *
 * LSI5_TO (0x1C0) - PCI Slave Image 5 Translation Offset Register           *
 * LSI6_TO (0x1D4) - PCI Slave Image 6 Translation Offset Register           *
 * LSI7_TO (0x1E8) - PCI Slave Image 7 Translation Offset Register           *
 *                                                                           *
 * VMEbus offset from the PCI slave image select address.                    *
 *                                                                           *
 * PCI Slave Images 0 and 4 have a 4KB granularity. The remaining PCI Slave  *
 * Images have a 64KB granularity.                                           *
 *                                                                           *
 * For PCI Slave Images 0 and 4:                                             *
 *   PCI bits 31:12 + LSIx_TO offset bits 31:12 are added to form VMEbus     *
 *   address 31:12. PCI bits 11:0 are then appended to the VMEbus address.   *
 * For PCI Slave Images other than 0 and 4:                                  *
 *   PCI bits 31:16 + LSIx_TO offset bits 31:16 are added to form VMEbus     *
 *   address 31:16. PCI bits 15:0 are then appended to the VMEbus address.   *
 *****************************************************************************/

#define LSIX_TO_4K_MASK    0xfffff000 /* Bits 31:12 of VMEbus offset         */
#define LSIX_TO_64K_MASK   0xffff0000 /* Bits 31:16 of VMEbus offset         */

/*****************************************************************************
 * SCYC_CTL (0x170) -  Special Cycle Control Register                        * 
 *                                                                           *
 * The special cycle generator will generate an ADOH or RMW cycle for the    *
 * 32 bit PCI bus address which matches the programmed address in SCYC_ADDR. *
 * A Read-Modify-Write command is initiated by a read to a specified address.*
 * Address-Only cycles are initiated be either read or write cycles.         *
 *****************************************************************************/

#define SCYC_CTL_DSBL      0x00000000  /* Disable                            */
#define SCYC_CTL_RMW       0x00000001  /* RMW (Read-Modify-Write)            */
#define SCYC_CTL_ADOH      0x00000002  /* Address-Only cycles                */

/*****************************************************************************
 * SCYC_ADDR (0x174) -  Special Cycle PCI Bus Address Register               * 
 *                                                                           *
 * This register designates the special cycle address. This address must be  *
 * contained in an enabled PCI image.                                        *
 *                                                                           *
 * All bits in this register are read/write. The address must be word        *
 * aligned ADDR(31:2).                                                       *
 *****************************************************************************/

/*****************************************************************************
 * SCYC_EN (0x178) -  Special Cycle Swap/Compare Enable Register             * 
 *                                                                           *
 * The bits enabled in this register defines the bits that will be involved  *
 * in the compare and swap operations for VME RMW cyccles.                   *
 *                                                                           *
 * All bits in this register are read/write. 1 = enable 0=disable            *
 *****************************************************************************/

/*****************************************************************************
 * SCYC_CMP (0x17C) -  Special Cycle Compare Data Register                   * 
 *                                                                           *
 * The data returned from the read portion of a VMEbus RMW is compared with  *
 * the contents of this register.  SYSC_EN is used to control which bits are *
 * compared.                                                                 *
 *                                                                           *
 * All bits in this register are read/write.                                 *
 *****************************************************************************/

/*****************************************************************************
 * SCYC_SWP (0x180) -  Special Cycle Swap Data Register                      * 
 *                                                                           *
 * If Enabled bits matched with the value in the compare register, then the  *
 * contetns of the swap data register is written back to VME. SCYC_EN is used*
 * to control which bits are written back to VME.                            *
 *                                                                           *
 * All bits in this register are read/write.                                 *
 *****************************************************************************/

/*****************************************************************************
 * LMISC (0x184) -  PCI Miscellaneous Register                               * 
 *                                                                           *
 * The Universe uses the coupled window timer to determine how long to hold  *
 * ownership of the VMEbus on behalf of the PCI Salve Channel after          *
 * processing a coupled transaction. The timer is restarted each time the    *
 * Universe processes a coupled transaction. If this timer expires, then the *
 * PCI Slave Channel releases the VME Master Interface.                      *
 *****************************************************************************/

#define LMISC_CWT_DIS      0x00000000  /* Disable Coupled Window Timer (CWT) */
#define LMISC_CWT_16       0x01000000  /* CWT =  16 PCI Clock cycles         */
#define LMISC_CWT_32       0x02000000  /* CWT =  32 PCI Clock cycles         */
#define LMISC_CWT_64       0x03000000  /* CWT =  64 PCI Clock cycles         */
#define LMISC_CWT_128      0x04000000  /* CWT = 128 PCI Clock cycles         */
#define LMISC_CWT_256      0x05000000  /* CWT = 256 PCI Clock cycles         */
#define LMISC_CWT_512      0x06000000  /* CWT = 512 PCI Clock cycles         */
#define LMISC_SW_SHIFT     24

/*****************************************************************************
 * SLSI (0x188) -  Special PCI Slave Image                                   * 
 *****************************************************************************/

#define SLSI_EN            0x80000000 /* Enable  Special PCI slave image     */
#define SLSI_DSBL          0x00000000 /* Disable Special PCI slave image     */
#define SLSI_EN_SHIFT      31

#define SLSI_P_WRT         0x40000000 /* Enable  PCI slave write posting     */
#define SLSI_NO_P_WRT      0x00000000 /* Disable PCI slave write posting     */
#define SLSI_P_WRT_SHIFT   30

#define SLSI_Q1_VME_DW_16  0x00000000 /* Quadrant 1 VME max data width=16    */
#define SLSI_Q1_VME_DW_32  0x00100000 /* Quadrant 1 VME max data width=32    */
#define SLSI_Q2_VME_DW_16  0x00000000 /* Quadrant 2 VME max data width=16    */
#define SLSI_Q2_VME_DW_32  0x00200000 /* Quadrant 2 VME max data width=32    */
#define SLSI_Q3_VME_DW_16  0x00000000 /* Quadrant 3 VME max data width=16    */
#define SLSI_Q3_VME_DW_32  0x00400000 /* Quadrant 3 VME max data width=32    */
#define SLSI_Q4_VME_DW_16  0x00000000 /* Quadrant 4 VME max data width=16    */
#define SLSI_Q4_VME_DW_32  0x00800000 /* Quadrant 4 VME max data width=32    */
#define SLSI_VME_DW_SHIFT  20


#define SLSI_Q1_VME_PROG  0x00001000  /* Quadrant 1 AM of Prog               */
#define SLSI_Q1_VME_DATA  0x00000000  /* Quadrant 1 AM of Data               */
#define SLSI_Q1_VME_USER  0x00000000  /* Quadrant 1 AM of User               */
#define SLSI_Q1_VME_SUPER 0x00000100  /* Quadrant 1 AM of Supervisor         */

#define SLSI_Q2_VME_PROG  0x00002000  /* Quadrant 2 AM of Prog               */
#define SLSI_Q2_VME_DATA  0x00000000  /* Quadrant 2 AM of Data               */
#define SLSI_Q2_VME_USER  0x00000000  /* Quadrant 2 Am of User               */
#define SLSI_Q2_VME_SUPER 0x00000200  /* Quadrant 2 AM of Supervisor         */

#define SLSI_Q3_VME_PROG  0x00004000  /* Quadrant 3 AM of Prog               */
#define SLSI_Q3_VME_DATA  0x00000000  /* Quadrant 3 AM of Data               */
#define SLSI_Q3_VME_USER  0x00000000  /* Quadrant 3 AM of User               */
#define SLSI_Q3_VME_SUPER 0x00000400  /* Quadrant 3 AM of Supervisor         */

#define SLSI_Q4_VME_PROG  0x00008000  /* Quadrant 4 AM of Prog               */
#define SLSI_Q4_VME_DATA  0x00000000  /* Quadrant 4 AM of Data               */
#define SLSI_Q4_VME_USER  0x00000000  /* Quadrant 4 AM of User               */
#define SLSI_Q4_VME_SUPER 0x00000800  /* Quadrant 4 AM of Supervisor         */

#define SLSI_PCI_MEM      0x00000000  /* Image responds to PCI Memory cycles */
#define SLSI_PCI_IO       0x00000001  /* Image responds to PCI I/O cycles    */
#define SLSI_PCI_RSV1     0x00000002  /* Reserved                            */
#define SLSI_PCI_RSV2     0x00000003  /* Reserved                            */

#define SLSI_BASE         0x000000FC  /* Mask for PCI base address field     */

#define SLSI_BASE_SHIFT   2           /* Value needed to shift 64mb value    */

/*****************************************************************************
 * L_CMDERR (0x18C) -  PCI Command Error Log Register                        * 
 *                                                                           *
 * The PCI Master Interface is responsible for logging errors under the      *
 * following conditions:                                                     *
 *   posted write transaction resulting in a target abort                    *
 *   posted write operation resulting in a master abort                      *
 *   maximum retry counter expires during retry or posted write transaction  *
 *****************************************************************************/

#define L_CMDERR_CMD_MSK  0xF0000000  /* PCI Command Error Log               */
#define L_CMDERR_M_ERR_ME 0x08000000  /* Multiple error occured since log    */
#define L_CMDERR_M_ERR_SE 0x00000000  /* Single error occured                */
#define L_CMDERR_L_STAT   0x00800000  /* Reads: 0=invalid 1=log valid/halted */
                                      /* Writes: 1=clears L_STAT/enables log */
/*****************************************************************************
 * LAERR (0x190) -  PCI Address Error Log Register                           * 
 *                                                                           *
 * The starting address of the errored PCI transaction is logged under the   *
 * following conditions:                                                     *
 *   posted write transaction resulting in a target abort                    *
 *   posted write operation resulting in a master abort or                   *
 *   maximum retry counter expires during retry or posted write transaction  *
 *                                                                           *
 * Contents are qualified by bit L_STAT of the L_CMDERR register             *
 *                                                                           *
 * All 32 bits of this register represent the starting address of the        *
 * failing PCI transaction.                                                  *
 *****************************************************************************/


/*****************************************************************************
 * DCTL register (0x200) - DMA Transfer Control Register                     *
 *****************************************************************************/

#define DCTL_READ         0x00000000  /* Transfer from VMEbus to PCI */
#define DCTL_WRITE        0x80000000  /* Transfer from PCI to VMEbus */

#define DCTL_D08          0x00000000  /* VMEbus maximum data width =  8 bits */
#define DCTL_D16          0x00400000  /* VMEbus maximum data width = 16 bits */
#define DCTL_D32          0x00800000  /* VMEbus maximum data width = 32 bits */
#define DCTL_D64          0x00C00000  /* VMEbus maximum data width = 64 bits */

#define DCTL_A16          0x00000000  /* Map PCI to A16 VMEbus Address space */
#define DCTL_A24          0x00010000  /* Map PCI to A24 VMEbus Address space */
#define DCTL_A32          0x00020000  /* Map PCI to A32 VMEbus Address space */
#define DCTL_RSV1         0x00030000  /* Reserved                            */
#define DCTL_RSV2         0x00040000  /* Reserved                            */
#define DCTL_RSV3         0x00050000  /* Reserved                            */
#define DCTL_User1        0x00060000  /* Map PCI to User1 VME Address space  */
#define DCTL_User2        0x00070000  /* MAP PCI to USer2 VME Address space  */

#define DCTL_DATA         0x00000000  /* Data Address Modifiers              */
#define DCTL_PROG         0x00004000  /* Program Address Modifiers           */

#define DCTL_USER         0x00000000  /* User Address Modifiers              */
#define DCTL_SUPER        0x00001000  /* Supervisor Address Modifiers        */

#define DCTL_NOBLT        0x00000000  /* Do not generate block transfers     */
#define DCTL_ENBLT        0x00000100  /* Generate block transfers            */

#define DCTL_DSBL_PCI64   0x00000000  /* Disable 64 bit PCI transactions     */
#define DCTL_ENBL_PCI64   0x00000080  /* Enable  64 bit PCI transactions     */

/*****************************************************************************
 * DTBC (0x204) - DMA Transfer Byte Count Register                           *
 *                                                                           *
 * The register specifies the number of bytes to be moved by the DMA before  *
 * the start of the DMA transfer, or the number of remaining bytes in the    *
 * transfer while the DMA is active. Thsi register is programmed from either *
 * bus or is programmed by the DMAC when it loads the command packet.        *
 *****************************************************************************/

#define BTBC_MASK         0x00FFFFFF  /* Mask for DMA transfer byte count    */

/*****************************************************************************
 * DLA (0x208) - DMA PCI Bus Address Register                                *
 *                                                                           *
 * This register is programmed from either bus or is programmed by the DMAC  *
 * when it loads the command packet. During linked-list operation, this reg- *
 * ister is only updated at the end of a transaction (i.e., processing of a  *
 * command packet) or when the DMA is stopped or halted.                     *
 *                                                                           *
 * All 32 bits of this register are used for the PCI address                 *
 *****************************************************************************/


/*****************************************************************************
 * DVA (0x210) - DMA VMEbus Address Register                                 *
 *                                                                           *
 * This register is programmed from either bus or is programmed by the DMAC  *
 * when it loads the command packet.  During linked-list operation, this     *
 * register is only updated at the end of a transaction (i.e., processing of *
 * a command packet) or when the DMA is stopped or halted.                   *
 *                                                                           *
 * All 32 bits of this register are used for the VMEbus address              *
 *****************************************************************************/


/*****************************************************************************
 * DCPP (0x218) - DMA Command Packet Pointer Register                        *
 *                                                                           *
 * This register contains the pointer to the current command packet.         *
 * Initially it is programmed to the starting packet of the linked-list, and *
 * is updated with the address to a new command packet at completion of a    *
 * packet. The packets must be an aligned 64-bit address.                    *
 *****************************************************************************/

#define DCPP_MASK         0xFFFFFFF8  /* Mask for DMA Command Packet Pointer */


/*****************************************************************************
 * DGCS (0x220) - DMA General Control and Status Register                    *
 *****************************************************************************/

#define DGCS_GO           0x80000000  /* Start DMA                           */
#define DGCS_STOP_REQ     0x40000000  /* Stop DMA when buffered data written */
#define DGCS_HALT_REQ     0x20000000  /* Halt DMA at end current cmd pckt    */
#define DGCS_CHAIN_DIRECT 0x00000000  /* DMA direct Mode                     */
#define DGCS_CHAIN_LINKED 0x08000000  /* DMA Linked List Mode                */
#define DGCS_VON_ALL      0x00000000  /* xxxx all bytes xferred until done   */
#define DGCS_VON_256      0x00100000  /*   256 byte boundry                  */
#define DGCS_VON_512      0x00200000  /*   512 byte boundry                  */
#define DGCS_VON_1024     0x00300000  /*  1024 byte boundry                  */
#define DGCS_VON_2048     0x00400000  /*  2048 byte boundry                  */
#define DGCS_VON_4096     0x00500000  /*  4096 byte boundry                  */
#define DGCS_VON_8192     0x00600000  /*  8192 byte boundry                  */
#define DGCS_VON_16384    0x00700000  /* 16384 byte boundry                  */
#define DGCS_VOFF_00US    0x00000000  /*    0 US between VME tenures         */
#define DGCS_VOFF_16US    0x00010000  /*   16 US between VME tenures         */
#define DGCS_VOFF_32US    0x00020000  /*   32 US between VME tenures         */
#define DGCS_VOFF_64US    0x00030000  /*   64 US between VME tenures         */
#define DGCS_VOFF_128US   0x00040000  /*  128 US between VME tenures         */
#define DGCS_VOFF_256US   0x00050000  /*  256 US between VME tenures         */
#define DGCS_VOFF_512US   0x00060000  /*  512 US between VME tenures         */
#define DGCS_VOFF_1024US  0x00070000  /* 1024 US between VME tenures         */
#define DGCS_VOFF_2US     0x00080000  /*    2 US between VME tenures         */
#define DGCS_VOFF_4US     0x00090000  /*    4 US between VME tenures         */
#define DGCS_VOFF_8US     0x000A0000  /*    8 US between VME tenures         */
#define DGCS_ACTIVE       0x00008000  /* DMA Active (R)                      */
#define DGCS_DMA_STOP     0x00004000  /* DMA Stopped (R/W1C)                 */
#define DGCS_DMA_HALT     0x00002000  /* DMA halted (R/W1C)                  */
#define DGCS_DMA_DONE     0x00000800  /* All DMA transfers Completed (R/W1C) */
#define DGCS_DMA_LERR     0x00000400  /* PCI error during DMA (R/W1C)        */
#define DGCS_DMA_VERR     0x00000200  /* VME error during DMA (R/W1C)        */
#define DGCS_DMA_P_ERR    0x00000100  /* Protocol Error (R/W1C)              */
#define DGCS_INT_STOP     0x00000040  /* Interrupt when DMA stopped          */
#define DGCS_INT_HALT     0x00000020  /* Interrupt when DMA halted           */
#define DGCS_INT_DONE     0x00000008  /* Interrupt when done                 */
#define DGCS_INT_L_ERR    0x00000004  /* Interrupt on PCI error              */
#define DGCS_INT_V_ERR    0x00000002  /* Interrupt on VME error              */
#define DGCS_INT_P_ERR    0x00000001  /* Interrupt on protocol error         */

#define DGCS_VON_SHIFT  20
#define DGCS_VOFF_SHIFT 16

/*****************************************************************************
 * D_LLUE Register (0x224) - DMA Linked List Update Enable Register          *
 *                                                                           *
 * The PCI Resource must read back a logic 1 in the update field before pro- *
 * ceeding to modify the linked list. After the last linked list has been    *
 * modified, the PCI resource must clear the Update field by writing a 0.    *
 *****************************************************************************/

#define D_LLUE_UPDATE     0x80000000  /* PCI Resource updating linked list   */
#define D_LLUE_NO_UPDATE  0x00000000  /* Resource not updating linked list   */



/*****************************************************************************
 * LINT_EN (0x300)   - Local Interrupt Enable Register and                   *
 * All bits in this register are Read/Write                                  *
 *****************************************************************************/

#define LINT_EN_LM3       0x00800000  /* Loc Mon 3 Interrupt enable          */
#define LINT_EN_LM2       0x00400000  /* Loc Mon 2 Interrupt enable          */
#define LINT_EN_LM1       0x00200000  /* Loc Mon 1 Interrupt enable          */
#define LINT_EN_LM0       0x00100000  /* Loc Mon 0 Interrupt enable          */
#define LINT_EN_MBOX3     0x00080000  /* Mailbox 3 Interrupt enable          */
#define LINT_EN_MBOX2     0x00040000  /* Mailbox 2 Interrupt enable          */
#define LINT_EN_MBOX1     0x00020000  /* Mailbox 1 Interrupt enable          */
#define LINT_EN_MBOX0     0x00010000  /* Mailbox 0 Interrupt enable          */
#define LINT_EN_ACFAIL    0x00008000  /* ACFAIL  Interrupt enable            */
#define LINT_EN_SYSFAIL   0x00004000  /* SYSFAIL Interrupt enable            */
#define LINT_EN_SW_LINT   0x00002000  /* Local Software Interrupt enable     */
#define LINT_EN_VMEIACK   0x00001000  /* VME Software IACK Interrupt enable  */
#define LINT_EN_VERR      0x00000400  /* VMEbus Error Interrupt enable       */
#define LINT_EN_LERR      0x00000200  /* PCI bus Error Interrupt enable      */
#define LINT_EN_DMA       0x00000100  /* Local DMA Interrupt enable          */
#define LINT_EN_VIRQ7     0x00000080  /* VMEbus IRQ7 Interrupt enable        */
#define LINT_EN_VIRQ6     0x00000040  /* VMEbus IRQ6 Interrupt enable        */
#define LINT_EN_VIRQ5     0x00000020  /* VMEbus IRQ5 Interrupt enable        */
#define LINT_EN_VIRQ4     0x00000010  /* VMEbus IRQ4 Interrupt enable        */
#define LINT_EN_VIRQ3     0x00000008  /* VMEbus IRQ3 Interrupt enable        */
#define LINT_EN_VIRQ2     0x00000004  /* VMEbus IRQ2 Interrupt enable        */
#define LINT_EN_VIRQ1     0x00000002  /* VMEbus IRQ1 Interrupt enable        */
#define LINT_EN_VOWN      0x00000001  /* VMEbus Ownership Interrupt enable   */

/*****************************************************************************
 * LINT_STAT (0x304) - Local Interrupt Status register                       *
 * All bits in this register are Read and write 1 to clear                   *
 *****************************************************************************/

#define LINT_STAT_LM3     0x00800000  /* Loc Mon 3 Interrupt asserted        */
#define LINT_STAT_LM2     0x00400000  /* Loc Mon 3 Interrupt asserted        */
#define LINT_STAT_LM1     0x00200000  /* Loc Mon 3 Interrupt asserted        */
#define LINT_STAT_LM0     0x00100000  /* Loc Mon 3 Interrupt asserted        */
#define LINT_STAT_MBOX3   0x00080000  /* Mailbox 3 Interrupt asserted        */
#define LINT_STAT_MBOX2   0x00040000  /* Mailbox 3 Interrupt asserted        */
#define LINT_STAT_MBOX1   0x00020000  /* Mailbox 3 Interrupt asserted        */
#define LINT_STAT_MBOX0   0x00010000  /* Mailbox 3 Interrupt asserted        */
#define LINT_STAT_ACFAIL  0x00008000  /* ACFAIL  Interrupt asserted          */
#define LINT_STAT_SYSFAIL 0x00004000  /* SYSFAIL Interrupt asserted          */
#define LINT_STAT_SW_LINT 0x00002000  /* Local Software Interrupt asserted   */
#define LINT_STAT_VMEIACK 0x00001000  /* VME Software IACK Interrupt asserted*/
#define LINT_STAT_VERR    0x00000400  /* VMEbus Error Interrupt asserted     */
#define LINT_STAT_LERR    0x00000200  /* PCI bus Error Interrupt asserted    */
#define LINT_STAT_DMA     0x00000100  /* Local DMA Interrupt asserted        */
#define LINT_STAT_VIRQ7   0x00000080  /* VMEbus IRQ7 Interrupt asserted      */
#define LINT_STAT_VIRQ6   0x00000040  /* VMEbus IRQ6 Interrupt asserted      */
#define LINT_STAT_VIRQ5   0x00000020  /* VMEbus IRQ5 Interrupt asserted      */
#define LINT_STAT_VIRQ4   0x00000010  /* VMEbus IRQ4 Interrupt asserted      */
#define LINT_STAT_VIRQ3   0x00000008  /* VMEbus IRQ3 Interrupt asserted      */
#define LINT_STAT_VIRQ2   0x00000004  /* VMEbus IRQ2 Interrupt asserted      */
#define LINT_STAT_VIRQ1   0x00000002  /* VMEbus IRQ1 Interrupt asserted      */
#define LINT_STAT_VOWN    0x00000001  /* VMEbus Ownership Interrupt asserted */

#define LINT_STAT_ALL_MASK 0x00FFF7FF
#define LINT_STAT_SPL6_MASK (LINT_STAT_LM3 | LINT_STAT_LM2 | LINT_STAT_LM1 | \
			     LINT_STAT_LM0 | LINT_STAT_MBOX3 | \
			     LINT_STAT_MBOX2 | LINT_STAT_MBOX1 | \
			     LINT_STAT_MBOX0 | LINT_STAT_ACFAIL | \
			     LINT_STAT_SYSFAIL | LINT_STAT_VERR | \
			     LINT_STAT_LERR | LINT_STAT_DMA | \
			     LINT_STAT_VIRQ7 | LINT_STAT_VOWN)
#define LINT_STAT_SPL4_MASK (LINT_STAT_VIRQ6 | LINT_STAT_VIRQ5 | \
			     LINT_STAT_VIRQ4)
#define LINT_STAT_SPL3_MASK (LINT_STAT_VIRQ3 | LINT_STAT_VIRQ2 | \
			     LINT_STAT_VIRQ1 | LINT_STAT_VMEIACK | \
			     LINT_STAT_SW_LINT)
#define LINT_STAT_ERR_MASK (LINT_STAT_ACFAIL | LINT_STAT_SYSFAIL | \
			    LINT_STAT_VERR | LINT_STAT_LERR)
#define LINT_STAT_LM_MASK (LINT_STAT_LM3 | LINT_STAT_LM2 | \
			   LINT_STAT_LM1 |  LINT_STAT_LM0)
#define LINT_STAT_MBX_MASK (LINT_STAT_MBOX3 | LINT_STAT_MBOX2 | \
			    LINT_STAT_MBOX1 | LINT_STAT_MBOX0)

/*****************************************************************************
 * The following bit definitions are used to direct interrupt sources to one
 * of the 8 PCI hardware interrupt pins
 *****************************************************************************/

#define LINT_PIN_0        0x0   /* Direct interrupt to LINT[0] pin           */
#define LINT_PIN_1        0x1   /* Direct interrupt to LINT[1] pin           */
#define LINT_PIN_2        0x2   /* Direct interrupt to LINT[2] pin           */
#define LINT_PIN_3        0x3   /* Direct interrupt to LINT[3] pin           */
#define LINT_PIN_4        0x4   /* Direct interrupt to LINT[4] pin           */
#define LINT_PIN_5        0x5   /* Direct interrupt to LINT[5] pin           */
#define LINT_PIN_6        0x6   /* Direct interrupt to LINT[6] pin           */
#define LINT_PIN_7        0x7   /* Direct interrupt to LINT[7] pin           */


/*****************************************************************************
 * LINT_MAP0 (0x308) - PCI Interrupt Map 0 register                          *
 * Maps various interrupt sources to 1 of 8 PCI interrupt pins               *
 *****************************************************************************/

#define LINT_MAP0_VIRQ7_SHIFT  28     /* Shift Lint Pin to VIRQ7 position    */
#define LINT_MAP0_VIRQ6_SHIFT  24     /* Shift Lint Pin to VIRQ6 position    */
#define LINT_MAP0_VIRQ5_SHIFT  20     /* Shift Lint Pin to VIRQ5 position    */
#define LINT_MAP0_VIRQ4_SHIFT  16     /* Shift Lint Pin to VIRQ4 position    */
#define LINT_MAP0_VIRQ3_SHIFT  12     /* Shift Lint Pin to VIRQ3 position    */
#define LINT_MAP0_VIRQ2_SHIFT   8     /* Shift Lint Pin to VIRQ2 position    */
#define LINT_MAP0_VIRQ1_SHIFT   4     /* Shift Lint Pin to VIRQ1 position    */
#define LINT_MAP0_VOWN_SHIFT    0     /* Shift Lint Pin to VOWN  position    */

/*****************************************************************************
 * LINT_MAP1 (0x30C) - PCI Interrupt Map 1 register                          *
 * Maps various interrupt sources to 1 of 8 PCI interrupt pins               *
 *****************************************************************************/

#define LINT_MAP0_ACFAIL_SHIFT  28    /* Shift Lint Pin to ACFAIL  position  */
#define LINT_MAP0_SYSFAIL_SHIFT 24    /* Shift Lint Pin to SYSFAIL position  */
#define LINT_MAP0_SW_INT_SHIFT  20    /* Shift Lint Pin to SW_INT  position  */
#define LINT_MAP0_SW_IACK_SHIFT 16    /* Shift Lint Pin to SW_IACK position  */
#define LINT_MAP0_RSVD_SHIFT    12    /* Shift Lint Pin to RSVD    position  */
#define LINT_MAP0_VERR_SHIFT     8    /* Shift Lint Pin to VERR    position  */
#define LINT_MAP0_LERR_SHIFT     4    /* Shift Lint Pin to LERR    position  */
#define LINT_MAP0_DMA_SHIFT      0    /* Shift Lint Pin to DMA     position  */

/*****************************************************************************
 * VINT_EN (0x310) - VME Interrupt Enable register                           *
 * All bits in this register are Read/Write                                  *
 *****************************************************************************/

#define VINT_EN_VME_SW7  0x80000000  /* VME Software 7 Interrupt enable      */
#define VINT_EN_VME_SW6  0x40000000  /* VME Software 6 Interrupt enable      */
#define VINT_EN_VME_SW5  0x20000000  /* VME Software 5 Interrupt enable      */
#define VINT_EN_VME_SW4  0x10000000  /* VME Software 4 Interrupt enable      */
#define VINT_EN_VME_SW3  0x08000000  /* VME Software 3 Interrupt enable      */
#define VINT_EN_VME_SW2  0x04000000  /* VME Software 2 Interrupt enable      */
#define VINT_EN_VME_SW1  0x02000000  /* VME Software 1 Interrupt enable      */
                                     /* A zero-to-one transition in the VME  */
                                     /* SW7 to SW1  bits above will cause    */
                                     /* the appropriate VME level interrupt  */
#define VINT_EN_VME_IRQ_SHIFT 24

#define VINT_EN_MBOX3    0x00080000  /* Mailbox 3 Interrupt enable           */
#define VINT_EN_MBOX2    0x00040000  /* Mailbox 2 Interrupt enable           */
#define VINT_EN_MBOX1    0x00020000  /* Mailbox 1 Interrupt enable           */
#define VINT_EN_MBOX0    0x00010000  /* Mailbox 0 Interrupt enable           */
#define VINT_EN_SW_INT   0x00001000  /* VME Software Interrupt enable        */
                                     /* A zero-to-one transition in above bit*/
                                     /* will cause the VME software interrupt*/
                                     /* to be asserted.                      */
#define VINT_EN_VERR     0x00000400  /* VMEbus Error Interrupt enable        */
#define VINT_EN_LERR     0x00000200  /* PCI bus Error Interrupt enable       */
#define VINT_EN_DMA      0x00000100  /* Local DMA Interrupt enable           */

#define VINT_EN_LINT7    0x00000080  /* Local Interrupt LINT[7] enable       */
#define VINT_EN_LINT6    0x00000040  /* Local Interrupt LINT[6] enable       */
#define VINT_EN_LINT5    0x00000020  /* Local Interrupt LINT[5] enable       */
#define VINT_EN_LINT4    0x00000010  /* Local Interrupt LINT[4] enable       */
#define VINT_EN_LINT3    0x00000008  /* Local Interrupt LINT[3] enable       */
#define VINT_EN_LINT2    0x00000004  /* Local Interrupt LINT[2] enable       */
#define VINT_EN_LINT1    0x00000002  /* Local Interrupt LINT[1] enable       */
#define VINT_EN_LINT0    0x00000001  /* Local Interrupt LINT[0] enable       */

/*****************************************************************************
 * VINT_EN (0x314) - VME Interrupt Status Register                           *
 * All bits in this register are Read with Write 1 to clear                  *
 *****************************************************************************/

#define VINT_STAT_VME_SW7 0x80000000  /* VME Software 7 Interrupt asserted   */
#define VINT_STAT_VME_SW6 0x40000000  /* VME Software 6 Interrupt asserted   */
#define VINT_STAT_VME_SW5 0x20000000  /* VME Software 5 Interrupt asserted   */
#define VINT_STAT_VME_SW4 0x10000000  /* VME Software 4 Interrupt asserted   */
#define VINT_STAT_VME_SW3 0x08000000  /* VME Software 3 Interrupt asserted   */
#define VINT_STAT_VME_SW2 0x04000000  /* VME Software 2 Interrupt asserted   */
#define VINT_STAT_VME_SW1 0x02000000  /* VME Software 1 Interrupt asserted   */
#define VINT_STAT_MBOX3   0x00080000  /* Mailbox 3 Interrupt asserted        */
#define VINT_STAT_MBOX2   0x00040000  /* Mailbox 2 Interrupt asserted        */
#define VINT_STAT_MBOX1   0x00020000  /* Mailbox 1 Interrupt asserted        */
#define VINT_STAT_MBOX0   0x00010000  /* Mailbox 0 Interrupt asserted        */
#define VINT_STAT_SW_INT  0x00001000  /* VME Software Interrupt asserted     */
#define VINT_STAT_VERR    0x00000400  /* VMEbus Error Interrupt asserted     */
#define VINT_STAT_LERR    0x00000200  /* PCI bus Error Interrupt asserted    */
#define VINT_STAT_DMA     0x00000100  /* Local DMA Interrupt asserted        */
#define VINT_STAT_LINT7   0x00000080  /* Local Interrupt LINT[7] asserted    */
#define VINT_STAT_LINT6   0x00000040  /* Local Interrupt LINT[6] asserted    */
#define VINT_STAT_LINT5   0x00000020  /* Local Interrupt LINT[5] asserted    */
#define VINT_STAT_LINT4   0x00000010  /* Local Interrupt LINT[4] asserted    */
#define VINT_STAT_LINT3   0x00000008  /* Local Interrupt LINT[3] asserted    */
#define VINT_STAT_LINT2   0x00000004  /* Local Interrupt LINT[2] asserted    */
#define VINT_STAT_LINT1   0x00000002  /* Local Interrupt LINT[1] asserted    */
#define VINT_STAT_LINT0   0x00000001  /* Local Interrupt LINT[0] asserted    */

#define VINT_STAT_VME_IRQ_SHIFT 24

/*****************************************************************************
 * The following bit definitions are used to direct interrupt sources to one *
 * of the 7 VME hardware interrupt pins (VIRQ* 7:1)                          *
 *****************************************************************************/

#define VIRQ_PIN_0        0x0   /* This value mask the interrupt no VIRQ*[0] */
#define VIRQ_PIN_1        0x1   /* Direct interrupt to VIRQ*[1] pin          */
#define VIRQ_PIN_2        0x2   /* Direct interrupt to VIRQ*[2] pin          */
#define VIRQ_PIN_3        0x3   /* Direct interrupt to VIRQ*[3] pin          */
#define VIRQ_PIN_4        0x4   /* Direct interrupt to VIRQ*[4] pin          */
#define VIRQ_PIN_5        0x5   /* Direct interrupt to VIRQ*[5] pin          */
#define VIRQ_PIN_6        0x6   /* Direct interrupt to VIRQ*[6] pin          */
#define VIRQ_PIN_7        0x7   /* Direct interrupt to VIRQ*[7] pin          */

/*****************************************************************************
 * VINT_MAP0 (0x318) - VME Interrupt Map 0 register                          *
 * Maps various interrupt sources to 1 of 7 VME interrupt pins               *
 *****************************************************************************/

#define VINT_MAP0_LINT7_SHIFT  28     /* Shift VIRQ* Pin to LINT7 position   */
#define VINT_MAP0_LINT6_SHIFT  24     /* Shift VIRQ* Pin to LINT6 position   */
#define VINT_MAP0_LINT5_SHIFT  20     /* Shift VIRQ* Pin to LINT5 position   */
#define VINT_MAP0_LINT4_SHIFT  16     /* Shift VIRQ* Pin to LINT4 position   */
#define VINT_MAP0_LINT3_SHIFT  12     /* Shift VIRQ* Pin to LINT3 position   */
#define VINT_MAP0_LINT2_SHIFT   8     /* Shift VIRQ* Pin to LINT2 position   */
#define VINT_MAP0_LINT1_SHIFT   4     /* Shift VIRQ* Pin to LINT1 position   */
#define VINT_MAP0_LINT0_SHIFT   0     /* Shift VIRQ* Pin to LINT0 position   */

/*****************************************************************************
 * VINT_MAP1 (0x31C) - VME Interrupt Map 1 register                          *
 * Maps various interrupt sources to 1 of 7 VME interrupt pins               *
 *****************************************************************************/

#define VINT_MAP1_SW_INT_SHIFT 16     /* Shift VIRQ* Pin to SW_INT  position */
#define VINT_MAP1_VERR_SHIFT    8     /* Shift VIRQ* Pin to VERR    position */
#define VINT_MAP1_LERR_SHIFT    4     /* Shift VIRQ* Pin to LERR    position */
#define VINT_MAP1_DMA_SHIFT     0     /* Shift VIRQ* Pin to DMA     position */

/*****************************************************************************
 * STATID (0x320) - Interrupt STATUS/ID Out                                  *
 *****************************************************************************/

#define STATID_STATID_MSK 0xFE000000  /* Status ID byte returned on IACK     */
#define STATID_STATID_SHIFT    24     /* Shift to top most significant bytes */

/*****************************************************************************
 * V1_STATID (0x324) - VIR1 Status/ID Register                               *
 * V2_STATID (0x328) - VIR2 Status/ID Register                               *
 * V3_STATID (0x32C) - VIR3 Status/ID Register                               *
 * V4_STATID (0x330) - VIR4 Status/ID Register                               *
 * V5_STATID (0x334) - VIR5 Status/ID Register                               *
 * V6_STATID (0x338) - VIR6 Status/ID Register                               *
 * V7_STATID (0x33C) - VIR7 Status/ID Register                               *
 *                                                                           *
 * The VxSTATID registers are read-only registers that hold the 8-bit VMEbus *
 * Status/ID that is acquired when the Universe performs a IACK cycle for a  *
 * given interrupt level.                                                    *
 *****************************************************************************/

#define VX_STATID_ERR     0x00000100  /* Bus Error during STATUS/ID cycle    */
#define VX_STATID_VEC_MSK 0x000000FF  /* Mask bits for acquired STATIS/ID    */
#define VX_STATID_MSK     (VX_STATID_ERR | VX_STATID_VEC_MSK)

/*****************************************************************************
 * LINT_MAP2 (0x340) - PCI Interrupt Map 2 register                          *
 * Maps various interrupt sources to 1 of 8 PCI interrupt pins               *
 *****************************************************************************/

#define LINT_MAP0_LM3_SHIFT    28     /* Shift Lint Pin to LM3   position    */
#define LINT_MAP0_LM2_SHIFT    24     /* Shift Lint Pin to LM2   position    */
#define LINT_MAP0_LM1_SHIFT    20     /* Shift Lint Pin to LM1   position    */
#define LINT_MAP0_LM0_SHIFT    16     /* Shift Lint Pin to LM0   position    */
#define LINT_MAP0_MBOX3_SHIFT  12     /* Shift Lint Pin to MBOX3 position    */
#define LINT_MAP0_MBOX2_SHIFT   8     /* Shift Lint Pin to MBOX2 position    */
#define LINT_MAP0_MBOX1_SHIFT   4     /* Shift Lint Pin to MBOX1 position    */
#define LINT_MAP0_MBOX0_SHIFT   0     /* Shift Lint Pin to MBOX0 position    */

/*****************************************************************************
 * VINT_MAP2 (0x344) - VME Interrupt Map 2 register                          *
 * Maps various interrupt sources to 1 of 7 VME interrupt pins               *
 *****************************************************************************/

#define VINT_MAP0_MBOX3_SHIFT  12     /* Shift VIRQ* Pin to MBOX3 position   */
#define VINT_MAP0_MBOX2_SHIFT   8     /* Shift VIRQ* Pin to MBOX2 position   */
#define VINT_MAP0_MBOX1_SHIFT   4     /* Shift VIRQ* Pin to MBOX1 position   */
#define VINT_MAP0_MBOX0_SHIFT   0     /* Shift VIRQ* Pin to MBOX0 position   */

/*****************************************************************************
 * MBOX0(0x348) - Mailbox Register 0                                         *
 * MBOX1(0x34C) - Mailbox Register 1                                         *
 * MBOX2(0x350) - Mailbox Register 2                                         *
 * MBOX3(0x354) - Mailbox Register 3                                         *
 * Writes to this register can cause interrupt generation on PCI or VMEbus   *
 * These registers are 32 bits in size and are read/write                    *
 *****************************************************************************/

/*****************************************************************************
 * SEMA0 (0x358) - Semaphore 0 Register                                      *
 * All bits in this register are read/write                                  *
 *****************************************************************************/

#define SEMA0_SEM3        0x80000000   /* Semaphore 3                        */
#define SEMA0_SEM3_MSK    0x7F000000   /* Semaphore 3 TAG3                   */
#define SEMA0_SEM2        0x00800000   /* Semaphore 2                        */
#define SEMA0_SEM2_MSK    0x007F0000   /* Semaphore 2 TAG2                   */
#define SEMA0_SEM1        0x00008000   /* Semaphore 1                        */
#define SEMA0_SEM1_MSK    0x00007F00   /* Semaphore 1 TAG1                   */
#define SEMA0_SEM0        0x00000080   /* Semaphore 0                        */
#define SEMA0_SEM0_MSK    0x0000007F   /* Semaphore 0 TAG0                   */

#define SEMA0_SEM3_SHIFT  24           /* Semaphore 3 TAG3 Bit Shift Value   */
#define SEMA0_SEM2_SHIFT  16           /* Semaphore 2 TAG2 Bit Shift Value   */
#define SEMA0_SEM1_SHIFT  08           /* Semaphore 1 TAG1 Bit Shift Value   */
#define SEMA0_SEM0_SHIFT  00           /* Semaphore 0 TAG0 Bit Shift Value   */

/*****************************************************************************
 * SEMA0 (0x35C) - Semaphore 1 Register                                      *
 * All bits in this register are read/write                                  *
 *****************************************************************************/

#define SEMA1_SEM7        0x80000000   /* Semaphore 7                        */
#define SEMA1_SEM7_MSK    0x7F000000   /* Semaphore 7 TAG7                   */
#define SEMA1_SEM6        0x00800000   /* Semaphore 6                        */
#define SEMA1_SEM6_MSK    0x007F0000   /* Semaphore 6 TAG6                   */
#define SEMA1_SEM5        0x00008000   /* Semaphore 5                        */
#define SEMA1_SEM5_MSK    0x00007F00   /* Semaphore 5 TAG5                   */
#define SEMA1_SEM4        0x00000080   /* Semaphore 4                        */
#define SEMA1_SEM4_MSK    0x0000007F   /* Semaphore 4 TAG4                   */

#define SEMA1_SEM7_SHIFT  24           /* Semaphore 7 TAG3 Bit Shift Value   */
#define SEMA1_SEM6_SHIFT  16           /* Semaphore 6 TAG2 Bit Shift Value   */
#define SEMA1_SEM5_SHIFT  08           /* Semaphore 5 TAG1 Bit Shift Value   */
#define SEMA1_SEM4_SHIFT  00           /* Semaphore 4 TAG0 Bit Shift Value   */

/*****************************************************************************
 * MAST_CTL (0x400) - Master Control  Register                               *
 *****************************************************************************/

#define MAST_CTL_RTRY_INF 0x00000000   /* Retry forever (on PCI)   */
#define MAST_CTL_RTRY_64  0x10000000   /* Retry 64  times (on PCI) */
#define MAST_CTL_RTRY_128 0x20000000   /* Retry 128 times (on PCI) */
#define MAST_CTL_RTRY_192 0x30000000   /* Retry 192 times (on PCI) */
#define MAST_CTL_RTRY_256 0x40000000   /* Retry 256 times (on PCI) */
#define MAST_CTL_RTRY_320 0x50000000   /* Retry 320 times (on PCI) */
#define MAST_CTL_RTRY_384 0x60000000   /* Retry 384 times (on PCI) */
#define MAST_CTL_RTRY_448 0x70000000   /* Retry 448 times (on PCI) */
#define MAST_CTL_RTRY_512 0x80000000   /* Retry 512 times (on PCI) */
#define MAST_CTL_RTRY_576 0x90000000   /* Retry 576 times (on PCI) */
#define MAST_CTL_RTRY_640 0xA0000000   /* Retry 640 times (on PCI) */
#define MAST_CTL_RTRY_704 0xB0000000   /* Retry 704 times (on PCI) */
#define MAST_CTL_RTRY_768 0xC0000000   /* Retry 768 times (on PCI) */
#define MAST_CTL_RTRY_832 0xD0000000   /* Retry 832 times (on PCI) */
#define MAST_CTL_RTRY_896 0xE0000000   /* Retry 896 times (on PCI) */
#define MAST_CTL_RTRY_960 0xF0000000   /* Retry 960 times (on PCI) */
#define MAST_CTL_RTRY_SHIFT 28

#define MAST_CTL_PW_128  0x00000000 /* Posted write xfer count = 128  bytes */
#define MAST_CTL_PW_256  0x01000000 /* Posted write xfer count = 256  bytes */
#define MAST_CTL_PW_512  0x02000000 /* Posted write xfer count = 512  bytes */
#define MAST_CTL_PW_1024 0x03000000 /* Posted write xfer count = 1024 bytes */
#define MAST_CTL_PW_2048 0x04000000 /* Posted write xfer count = 2048 bytes */
#define MAST_CTL_PW_4096 0x05000000 /* Posted write xfer count = 4096 bytes */
#define MAST_CTL_PW_BBSY 0x0F000000 /* Release after each transaction       */
#define MAST_CTL_PW_SHIFT 24

#define MAST_CTL_VME_BR0 0x00000000  /* VMEbus Request Level BR0             */
#define MAST_CTL_VME_BR1 0x00400000  /* VMEbus Request Level BR1             */
#define MAST_CTL_VME_BR2 0x00800000  /* VMEbus Request Level BR2             */
#define MAST_CTL_VME_BR3 0x00C00000  /* VMEbus Request Level BR3 (default)   */
#define MAST_CTL_VRL_SHIFT 22 

#define MAST_CTL_VME_DMD  0x00000000  /* VME request mode - Demand           */
#define MAST_CTL_VME_FAIR 0x00200000  /* VME request mode - Fair             */
#define MAST_CTL_VRM_SHIFT 21

#define MAST_CTL_VME_RWD  0x00000000  /* VME release mode Release-When-Done  */
#define MAST_CTL_VME_ROR  0x00100000  /* VME release mode Release-On-Request */
#define MAST_CTL_VREL_SHIFT 20

#define MAST_CTL_VOWN_REL 0x00000000  /* VOWN - release the VMEbus           */
#define MAST_CTL_VOWN_ACQ 0x00080000  /* VOWN - Acquire and hold VMEbus      */
#define MAST_CTL_VOWN_SHIFT 19

#define MAST_CTL_VOWN_ACK 0x00040000  /* VMEbus acquired and held from VON   */

#define MAST_CTL_PABS_32  0x00000000  /* PCI Aligned burst size = 32 bytes   */
#define MAST_CTL_PABS_64  0x00001000  /* PCI Aligned burst size = 64 bytes   */
#define MAST_CTL_PABS_128 0x00002000  /* PCI Aligned burst size = 128 bytes  */
#define MAST_CTL_PABS_SHIFT 12

#define MAST_CTL_BUS_NO   0x00000000  /* PCI bus number for config cyles     */
#define MAST_CTL_BUS_MASK 0x000000FF  /* Mask for PCI BUS Number             */

/*****************************************************************************
 * MISC_CTL (0x404) - Master Control  Register                               *
 *****************************************************************************/

#define MISC_CTL_VBTO_DISABL  0x00000000 /* VMEbus timeouts disabled         */
#define MISC_CTL_VBTO_16US    0x10000000 /* VMEbus timeout = 16usec          */
#define MISC_CTL_VBTO_32US    0x20000000 /* VMEbus timeout = 32usec          */
#define MISC_CTL_VBTO_64US    0x30000000 /* VMEbus timeout = 64usec (default)*/
#define MISC_CTL_VBTO_128US   0x40000000 /* VMEbus timeout = 128usec         */
#define MISC_CTL_VBTO_256US   0x50000000 /* VMEbus timeout = 256usec         */
#define MISC_CTL_VBTO_512US   0x60000000 /* VMEbus timeout = 512usec         */
#define MISC_CTL_VBTO_1024US  0x70000000 /* VMEbus timeout = 1024usec        */
#define MISC_CTL_VBTO_MASK    0xF0000000 /* VMEbus timeout mask value        */
#define MISC_CTL_VBTO_SHIFT   28
 
#define MISC_CTL_VARB_RR      0x00000000 /* Round-robin VMEbus arbitration   */
#define MISC_CTL_VARB_PRIO    0x04000000 /* Priority VMEbus arbitration      */
#define MISC_CTL_VARB_SHIFT   26
 
#define MISC_CTL_VARBTO_DISABL 0x00000000 /* VMEbus Arb timeouts disabled    */
#define MISC_CTL_VARBTO_16US   0x01000000 /* VMEbus Arb 16 microseconds      */
#define MISC_CTL_VARBTO_256US  0x02000000 /* VMEbus Arb 256 microseconds     */
#define MISC_CTL_VARBTO_MASK   0x03000000 /* VMEbus arb timeout mask bits    */
#define MISC_CTL_VARBTO_SHIFT  24

#define MISC_CTL_SW_LRST      0x00800000 /* Initiate a LRST# when set        */

#define MISC_CTL_SW_SYSRST    0x00400000 /* Initiate a SYSRST# when set      */
 
#define MISC_CTL_BI_OFF       0x00000000 /* Universe not in BImode           */
#define MISC_CTL_BI_ON        0x00100000 /* Universe in BImode               */
 
#define MISC_CTL_ENGBI_OFF    0x00000000 /* VIRQ1 assertion ignored          */
#define MISC_CTL_ENGBI_ON     0x00080000 /* VIRQ1 assertion sets BI mode     */
 
#define MISC_CTL_RESCIND_OFF  0x00000000 /* Disable Rescinding DTACK         */
#define MISC_CTL_RESCIND_ON   0x00040000 /* Enable Rescinding DTACK          */

#define MISC_CTL_SYSCON_OFF   0x00000000 /* Universe not System Controller   */
#define MISC_CTL_SYSCON_ON    0x00020000 /* Universe is System Controller    */

#define MISC_CTL_AUTOID_OFF   0x00000000 /* Universe auto id off             */
#define MISC_CTL_AUTOID_ON    0x00010000 /* Initiate Universe auto id seq    */
                                         /* Bits 15:0 are reserved           */

/*****************************************************************************
 * MISC_STAT (0x408) - Master Status  Register                               *
 * This is a read only register                                              *
 *****************************************************************************/

#define MISC_STAT_ENDIAN_MSK  0x80000000 /* Mask bit for endian bit          */
#define MISC_STAT_ENDIAN      0x00000000 /* Universe always PCI little endian*/

#define MISC_STAT_LCLSIZE_MSK 0x40000000 /* Mask bit for PCI bus size        */
#define MISC_STAT_LCLSIZE_32  0x00000000 /* PCI 32 bit bus                   */
#define MISC_STAT_LCLSIZE_64  0x40000000 /* PCI 64 bit bit                   */

#define MISC_STAT_DY4AUTO_MSK 0x08000000 /* Mask bit for DY4 Auto ID Enable  */
#define MISC_STAT_DY4AUTO_DBL 0x00000000 /* DY4 Auto ID disabled             */
#define MISC_STAT_DY4AUTO_ENA 0x08000000 /* DY4 Auto ID Enabled              */

#define MISC_STAT_BBSY_MSK    0x00200000 /* Mask bit for BBSY                */
#define MISC_STAT_BBST_ASRTD  0x00000000 /* BBSY asserted on bus             */
#define MISC_STAT_BBST_NEGTD  0x00000000 /* BBSY negated  on bus             */

#define MISC_STAT_DY4DONE_MSK 0x00080000 /* Mask bit for DY4 Auto ID done    */
#define MISC_STAT_DY4DONE_BSY 0x00000000 /* DY4 Auto ID NOT done             */
#define MISC_STAT_DY4DONE_DN  0x00080000 /* DY4 Auto ID done                 */

#define MISC_STAT_TXFE_MSK    0x00040000 /* Mask bit for Transmit FIFO Empty */
#define MISC_STAT_TXFE_BSY    0x00000000 /* Transmit FIFO not empty          */
#define MISC_STAT_TXFE_EMPTY  0x00040000 /* Transmit FIFO empty              */

#define MISC_STAT_RXFE_MSK    0x00020000 /* Mask bit for Receive FIFO Empty  */
#define MISC_STAT_RXFE_BSY    0x00000000 /* Receive FIFO not empty           */
#define MISC_STAT_RXFE_EMPTY  0x00020000 /* Receive FIFO empty               */

#define MISC_STAT_DY4AUTOID_MSK 0x0000FF00 /* Mask bits for DY4 Auto ID      */

/*****************************************************************************
 * USER_AM (0x40C) - User Am Codes Register                                  *
 * All bits in theis register are Read/Write                                 *
 *****************************************************************************/

#define USER_AM_USER1AM_MSK   0xFC000000 /* Mask bits for User 1 AM field    */
#define USER_AM_USER1AM_SHIFT         26 /* Shift value to move AM to field  */
#define USER_AM_USER2AM_MSK   0x00FC0000 /* Mask bits for User 2 AM field    */
#define USER_AM_USER2AM_SHIFT         18 /* Sift value to move Am to field   */

/*****************************************************************************/
/*   Tundra's VMEbus Slave Image Registers used to configure VMEbus to PCI   */
/*   windows.                                                                */
/*****************************************************************************/

/*****************************************************************************
 * VSI0_CTL (0xF00) - VMEbus Slave Image 0 Control Register                  *
 * VSI1_CTL (0xF14) - VMEbus Slave Image 1 Control Register                  *
 * VSI2_CTL (0xF28) - VMEbus Slave Image 2 Control Register                  *
 * VSI3_CTL (0xF3C) - VMEbus Slave Image 3 Control Register                  *
 * VSI4_CTL (0xF90) - VMEbus Slave Image 4 Control Register                  *
 * VSI5_CTL (0xFA4) - VMEbus Slave Image 5 Control Register                  *
 * VSI6_CTL (0xFB8) - VMEbus Slave Image 6 Control Register                  *
 * VSI7_CTL (0xFCC) - VMEbus Slave Image 7 Control Register                  *
 *****************************************************************************/

#define VSIX_CTL_EN       0x80000000 /* Enable  VME slave image              */
#define VSIX_CTL_DSBL     0x00000000 /* Disable VME slave image              */
#define VSIX_EN_SHIFT     31

#define VSIX_CTL_P_WRT    0x40000000 /* Enable VME slave write posting       */
#define VSIX_CTL_NO_P_WRT 0x00000000 /* Disable VME slave write posting      */
#define VSIX_P_WRT_SHIFT  30

#define VSIX_CTL_RD_PR    0x20000000 /* Enable VME slave read prefetch       */
#define VSIX_CTL_NO_RD_PR 0x00000000 /* Disable VME slave read prefetch      */
#define VSIX_PR_SHIFT     29

#define VSIX_CTL_DATA     0x00400000 /* Data Address Modifier                */
#define VSIX_CTL_PROG     0x00800000 /* Program Address Modifiers            */
#define VSIX_CTL_PRGDATA  0x00C00000 /* Program/Data Address Modifier        */
#define VSIX_PD_SHIFT     22

#define VSIX_CTL_USER     0x00100000  /* User Address Modifier               */
#define VSIX_CTL_SUPER    0x00200000  /* Supervisor Address Modifier         */
#define VSIX_CTL_SUPUSR   0x00300000  /* User/Supervisor Address Modifier    */
#define VSIX_US_SHIFT     20

#define VSIX_CTL_A16      0x00000000 /* VMEbus Address space = A16           */
#define VSIX_CTL_A24      0x00010000 /* VMEbus Address space = A24           */
#define VSIX_CTL_A32      0x00020000 /* VMEbus Address space = A32           */
#define VSIX_CTL_RSV1     0x00030000 /* Reserved                             */
#define VSIX_CTL_RSV2     0x00040000 /* Reserved                             */
#define VSIX_CTL_RSV3     0x00050000 /* Reserved                             */
#define VSIX_CTL_USR1     0x00060000 /* VMEbus Address space = User1 AM      */
#define VSIX_CTL_USR2     0x00070000 /* VMEbus Address space = User2 AM      */
#define VSIX_AS_SHIFT     16

#define VSIX_CTL_EN_PCI64 0x00000080 /* Enable PCI D64 transactions          */
#define VSIX_CTL_DS_PCI64 0x00000000 /* Disable PCI D64 transactions         */
#define VSIX_PCI64_SHIFT  7

#define VSIX_CTL_EN_PLCK  0x00000040 /* Enable use of PCI Lock during RMW    */
#define VSIX_CTL_DIS_PLCK 0x00000000 /* Disable use of PCI Lock during RMW   */
#define VSIX_PCLK_SHIFT   6

#define VSIX_CTL_PCI_MEM  0x00000000  /* Map VMEbus address to PCI Memory    */
#define VSIX_CTL_PCI_IO   0x00000001  /* Map VMEbus address to PCI I/O       */
#define VSIX_CTL_PCI_CFG  0x00000002  /* Map VMEbus address to PCI Config    */

/*****************************************************************************
 * VSI0_BS (0xF04) - VMEbus Slave Image 0 Base Address Register              *
 * VSI1_BS (0xF18) - VMEbus Slave Image 1 Base Address Register              *
 * VSI2_BS (0xF2C) - VMEbus Slave Image 2 Base Address Register              *
 * VSI3_BS (0xF40) - VMEbus Slave Image 3 Base Address Register              *
 * VSI4_BS (0xF94) - VMEbus Slave Image 4 Base Address Register              *
 * VSI5_BS (0xFA8) - VMEbus Slave Image 5 Base Address Register              *
 * VSI6_BS (0xFBC) - VMEbus Slave Image 6 Base Address Register              *
 * VSI7_BS (0xFD0) - VMEbus Slave Image 7 Base Address Register              *
 *                                                                           *
 * The base adress specifies the lowest VMEbus address in the address range  *
 * that will be decoded.                                                     *
 *                                                                           *
 * VMEbus Slave images 0 and 4 have a 4KB granularity. Therfore, bits 11:00  *
 * are not compared. The remaining VMEbus slave images have a 64KB           *
 * granularity. Therefore, bits 15:00 are not compared.                      *
 *****************************************************************************/

#define VSIX_BS_4K_MASK    0xfffff000 /* Image matches bits 31:12 of VME Addr*/
#define VSIX_BS_64K_MASK   0xffff0000 /* Image matches bits 31:16 of VME Addr*/

/*****************************************************************************
 * VSI0_BD (0xF08) - VMEbus Slave Image 0 Bound Address Register             *
 * VSI1_BD (0xF1C) - VMEbus Slave Image 1 Bound Address Register             *
 * VSI2_BD (0xF30) - VMEbus Slave Image 2 Bound Address Register             *
 * VSI3_BD (0xF44) - VMEbus Slave Image 3 Bound Address Register             *
 * VSI4_BD (0xF98) - VMEbus Slave Image 4 Bound Address Register             *
 * VSI5_BD (0xFAC) - VMEbus Slave Image 5 Bound Address Register             *
 * VSI6_BD (0xFC0) - VMEbus Slave Image 6 Bound Address Register             *
 * VSI7_BD (0xFD4) - VMEbus Slave Image 7 Bound Address Register             *
 *                                                                           *
 * The address decoded in a slave image are those that are greater than or   *
 * equal to the base address and less than the bound address.                *
 *                                                                           *
 * VMEbus Slave images 0 and 4 have a 4KB granularity. Therfore, bits 11:00  *
 * are not compared. The remaining VMEbus slave images have a 64KB           *
 * granularity. Therefore, bits 15:00 are not compared.                      *
 *****************************************************************************/

#define VSIX_BD_4K_MASK    0xfffff000 /* Image 0 & 4 bound address mask      */
#define VSIX_BD_64K_MASK   0xffff0000 /* Images not 0 & 4 bound address mask */

/*****************************************************************************
 * VSI0_TO (0xF0C) - VMEbus Slave Image 0 Translation Offset Register        *
 * VSI1_TO (0xF20) - VMEbus Slave Image 1 Translation Offset Register        *
 * VSI2_TO (0xF34) - VMEbus Slave Image 2 Translation Offset Register        *
 * VSI3_TO (0xF48) - VMEbus Slave Image 3 Translation Offset Register        *
 * VSI4_TO (0xF9C) - VMEbus Slave Image 4 Translation Offset Register        *
 * VSI5_TO (0xFB0) - VMEbus Slave Image 5 Translation Offset Register        *
 * VSI6_TO (0xFC4) - VMEbus Slave Image 6 Translation Offset Register        *
 * VSI7_TO (0xFD8) - VMEbus Slave Image 7 Translation Offset Register        *
 *                                                                           *
 * VMEbus Slave images 0 and 4 have a 4KB granularity. The remaining VMEbus  *
 * slave images have a 64KB granularity.                                     *
 *                                                                           *
 * For VMEbus Slave Images 0 and 4:                                          *
 *   VMEbus bits 31:12 + VSIx_TO offset bits 31:12 are added to form PCI     *
 *   address 31:12. VMEbus bits 11:0 are then appended to the PCI address.   *
 * For VMEbus Slave Images other than 0 and 4:                               *
 *   VMEbus bits 31:16 + VSIx_TO offset bits 31:16 are added to form PCI     *
 *   address 31:16. VMEbus bits 15:0 are then appended to the PCI address.   *
 *****************************************************************************/

#define VSIX_TO_4K_MASK    0xfffff000 /* Bits 31:12 of PCI offset            */
#define VSIX_TO_64K_MASK   0xffff0000 /* Bits 31:16 of PCI offset            */

/*****************************************************************************
 * LM_CTL (0xF64) - Location Monitor Control Register                        *
 *                                                                           *
 * This register specifies the VMEbus controls for the location monitor      *
 * image. The image has 1 4kb resolution and size. The image responds to a   *
 * VME read or write within the 4kb space and matching on of the address     *
 * modifier codes specified. Block transfers are not supported.              *
 *                                                                           *
 * VMEbus address bits [4:3] are used to set the status bit in the LINT_STAT *
 * for one of the four location monitor interrupts. If the onboard Universe  *
 * master is the owner of the VMEbus, the Universe will also generate DTACK  *
 * to determine the transaction.                                             *
 *****************************************************************************/

#define LM_CTL_EN         0x80000000  /* Location Monitor Image Enable       */
#define LM_CTL_DSBL       0x00000000  /* Location Monitor Image Disable      */
#define LM_CTL_DATA       0x00400000  /* Data Address Modifier               */
#define LM_CTL_PROG       0x00800000  /* Program Address Modifier            */
#define LM_CTL_PRGDATA    0x00C00000  /* Program & Data Address Modifier     */
#define LM_CTL_USER       0x00100000  /* User Address Modifier               */
#define LM_CTL_SUPER      0x00200000  /* Supervisor Address modifier         */
#define LM_CTL_SUP_USER   0x00300000  /* Supervisor & User Address Modifier  */
#define LM_CTL_A16        0x00000000  /* A16 Address Modifier                */
#define LM_CTL_A24        0x00010000  /* A24 Address Modifier                */
#define LM_CTL_A32        0x00020000  /* A32 Address Modifier                */

#define LM_IMG_EN_SHIFT   31
#define LM_PRGDATA_SHIFT  22
#define LM_SUP_USER_SHIFT 20
#define LM_AS_SHIFT       16

/*****************************************************************************
 * LM_BS (0xF68) - Location Base Address Register                            *
 *                                                                           *
 * The base address specifies the lowest 4kb range that will be decoded as a *
 * location monitor access.                                                  *
 *****************************************************************************/

#define LM_BS_4K_MASK     0xFFFFF000  /* Mask for Loc Base Address Register  */

/*****************************************************************************
 * VRAI_CTL (0xF70) - VMEbus Register Access Control Register                *
 *                                                                           *
 * The VME Access Image allows access to the Universe registers with standard*
 * VMEbus cycles. Only single cycle and lock AM codes are accepted. When a   *
 * register is accessed with RMW, it is locked for the duration of trans-    *
 * action.                                                                   *
 *****************************************************************************/

#define VRAI_CTL_EN       0x80000000  /* Image enable                        */
#define VRAI_CTL_DSBL     0x00000000  /* Image disable                       */
#define VRAI_CTL_DATA     0x00400000  /* Data Address Modifier               */
#define VRAI_CTL_PROG     0x00800000  /* Program Address Modifier            */
#define VRAI_CTL_PRGDATA  0x00C00000  /* Program & Data Address Modifier     */
#define VRAI_CTL_USER     0x00100000  /* User Address Modifier               */
#define VRAI_CTL_SUPER    0x00200000  /* Supervisor Address modifier         */
#define VRAI_CTL_SUP_USER 0x00300000  /* Supervisor & User Address Modifier  */
#define VRAI_CTL_A16      0x00000000  /* A16 Address Modifier                */
#define VRAI_CTL_A24      0x00010000  /* A24 Address Modifier                */
#define VRAI_CTL_A32      0x00020000  /* A32 Address Modifier                */

#define VRAI_IMG_EN_SHIFT   31
#define VRAI_PRGDATA_SHIFT  22
#define VRAI_SUP_USER_SHIFT 20
#define VRAI_AS_SHIFT       16

/*****************************************************************************
 * VRAI_BS (0xF74) - VMEbus Register Access Base Address Register            *
 *                                                                           *
 * The base address specifies the lowest address in the 4kb VMEbus register  *
 * access Image.                                                             *
 *****************************************************************************/

#define VRAI_BS_4K_MASK   0xFFFFF000  /* Mask for Reg Acc Base Address Reg   */

/*****************************************************************************
 * VCSR_CTL (0xF80) - VMEbus CSR Control Register                            *
 *                                                                           *
 * The EN bit allos software to enable or disable Universe CR/CSR image.     *
 * This image can also be enabled by the VME64 Auto ID process.              *
 * For CSR's not supported in the Universe and for CR accesses, The LAS field*
 * determines the PCI bus command that will be generated when the cycle is   *
 * mapped to the PCI bus.                                                    *
 *****************************************************************************/

#define VCSR_CTL_EN       0x80000000  /* Image Enable                        */
#define VCSR_CTL_DSBL     0x00000000  /* Image Disable                       */
#define VCSR_CTL_MEM      0x00000000  /* PCI bus memory Space                */
#define VCSR_CTL_IO       0x00000001  /* PCI bus I/O Space                   */
#define VCSR_CTL_CNFG     0x00000002  /* PCI bus Configuration Space         */

/*****************************************************************************
 * VCSR_TO (0xF84) - VMEbus CSR Translation Offset Register                  *
 *                                                                           *
 * For CSR's not supported in the Universe and for CR accesses, the trans-   *
 * lation offset is added to the 24 bit VMEbus address to produce a 32 bit   *
 * PCI bus address. Negative offsets are not supported.                      *
 *****************************************************************************/

#define VCSR_TO_MASK      0xFFF80000  /* Translation offset mask             */

/*****************************************************************************
 * V_AMERR (0xF88) - VMEbus AM Code Error Log Register                       *
 *                                                                           *
 * The Universe VMEbus Master Interface is responsible for logging the       *
 * paramters of a posted write transaction that results in a bus error. This *
 * register holds the address modifier code and the state of IACK* siginal.  *
 * The register contents are qualified by the V_STAT bit.                    *
 *****************************************************************************/

#define V_AMERR_AM_MASK   0xFC000000  /* VMEbus AM Code Error Log Mask       */
#define V_AMERR_IACK      0x02000000  /* VMEBUS IACK Signal                  */
#define V_AMERR_M_ERR     0x01000000  /* 0 = Single 1 = Multiple errors      */
#define V_AMERR_V_STAT    0x00800000  /* 0 = logs invalid 1 = logs valid     */
                                      /* Write 1 to V_STAT to clear and      */
                                      /* enable error logging.               */

/*****************************************************************************
 * VAERR (0xF8C) - VMEbus Address Error Log Register                         *
 *                                                                           *
 * The Universe PCI Master Interface is responsible for logging the param-   *
 * eters of a posted write transaction that results in a bus error. This     *
 * register holds the address. The register contents are qualified by the    *
 * V_STAT bit of the V_AMERR register.                                       *
 *                                                                           *
 * All 32 bits are valid for the VMEbus address error log.                   *
 *****************************************************************************/

/*****************************************************************************
 * VCSR_CLR (0xFF4) - VMEbus CSR Bit Clear Register                          *
 *                                                                           *
 * This register contains the Bit Clear Register as defined in the VME64     *
 * specification. Note that RESET bit can be written to only from the VMEbus *
 *****************************************************************************/

#define VCSR_CLR_RESET    0x80000000
#define VCSR_CLR_SYSFAIL  0x40000000
#define VCSR_CLR_FAIL     0x20000000


/*****************************************************************************
 * VCSR_SET (0xFF8) - VMEbus CSR Bit Set Register                            *
 *                                                                           *
 * This register implements the Bit Set Register as defined in the VME64     *
 * specification. Note that RESET bit can be written to only from the VMEbus.*
 * Writing a 1 to the RESET bit asserts LRST#. The PCI reset remains         *
 * asserted until a 1 is written to the RESET bit of the VCSR_CLR register.  *
 *****************************************************************************/

#define VCSR_SET_RESET    0x80000000
#define VCSR_SET_SYSFAIL  0x40000000
#define VCSR_SET_FAIL     0x20000000

/*****************************************************************************
 * VCSR_BS (0xFFC) - VMEbus CSR Base Address Register                        *
 *                                                                           *
 * The base address speciifes one of thirty-one available CR/CSR windows as  *
 * defined in the VME64 specification. Each window contains 512kb of CR/CSR  *
 * space.                                                                    *
 *****************************************************************************/

#define VCSR_BS_MSK      0xF8000000 /* Mask for Base Address 31:27           */

/*****************************************************************************
 *                   UNIVERSE DATA STRUCTURES                                *
 *****************************************************************************/

/*
 * Special PCI Target Image
 */
struct spcl_pci_slave_image  {
  u_int        slsi_cntrl;       /* Special PCI Target Image Register Value  */
  u_int        pci_slsi_base;    /* 64mb aligned PCI base address of window  */
  int          image_ena;        /* OS parameter for image enable            */
  int          wrt_post_ena;     /* OS parameter for window write posting    */
  int          max_data_wdth;    /* OS parameter for sub-window data width   */
  io_handle_t  a24_user_data;    /* 16mb A24 User Data I/O Handle            */
  io_handle_t  a24_user_prg;     /* 16mb A24 User Program I/O Handle         */
  io_handle_t  a24_super_data;   /* 16mb A24 Supervisory Data I/O Handle     */
  io_handle_t  a24_super_prg;    /* 16mb A24 Supervisory Program I/O Handle  */
  io_handle_t  a16_user_acc;     /* 64kb A16 User Access I/O Handle          */
  io_handle_t  a16_super_acc;    /* 64kb A16 Supervisory Access I/O Handle   */
};

/*
 * PCI Local Slave Image data structure
 */

#define PCI_SLAVE_WNDWS 8
#define VME_SLAVE_WNDWS 8

struct pci_slave_image  {
  u_int        lsi_cntrl;        /* control register value for image         */
  u_int        lsi_base;         /* base address of PCI image                */
  u_int        lsi_bnd;          /* bound address of PCI image               */
  u_int        lsi_to;           /* offset to base of VMEbus address         */
  u_int        lsi_alignment;    /* slave image alignment                    */
  int          image_ena;        /* OS parameter for image enable            */
  vme_addr_t   vme_base;         /* OS parameter VME window base address     */
  u_int        vme_wndw_size;    /* OS parameter for PCI/VME window in bytes */
  int          vme_addr_space;   /* OS parameter for VME address space       */
  int          vme_usr_sprvsr;   /* OS parameter for VME user/super selection*/
  int          vme_data_prg;     /* OS parameter for VME data/prog selection */
  int          max_data_wdth;    /* OS parameter for sub-window data width   */
  int          wrt_post_ena;     /* OS parameter for window write posting    */
  int          vme_cycle_select; /* OS parameter for cycle select            */
  vme_atype_t  vme_atype;        /* VMEbus address modifier for image        */
  vme_addr_t   vme_bnd;          /* VMEbus window end address -1             */
  io_handle_t  ioh;              /* I/O handle to base of PCI slave image    */
};

/*
 *      hw_sg_map_control - used to describe a scatter/gather map. It contains
 *      the bus base address of the window (phys_base), the pointer to the
 *      resource map (sg_rmap) and the address of the scatter/gather table.
 */
struct hw_sg_map_control {
	decl_simple_lock_data(, sg_rmap_lock) /* lock to protect rmap */
	struct map	*sg_rmap;	/* R-map that controls allocation */
	/* Pad lock data away from read-only data to allow code paths 
	 * referencing read-only data to exec. quicker -- less 
	 * cache-thrashing w/cache-blocks on multi-cpu systems 
	 * trying to get lock-data, causing read-only cached 
	 * data to be invalidated. 
	 * Pad of 8 64-byte elements puts read-mostly data in next
	 * block; and due to size of this structure, 13 bytes,
	 * when MALLOC'd, will get 128-byte bucket, which is integral
	 * number of 64-byte cache blocks; structure must not have a
	 * MALLOC bucket size that is a fraction of a cache block, or
	 * consecutive hw_sg_map_control's will cause cache thrash as well.
	 */
	ulong		pad[8];
	vm_offset_t	phys_base;	/* Bus base address of dma window */
	vm_offset_t	sg_table_base;	/* Address of scatter/gather table */
	u_long		prefetch_amount; /* Prefetch buffer needs	   */
};

struct vme_map_ctl {
  struct controller        d_ctlr;             /* needed for dma_map_alloc   */
  u_long                   req_bc;             /* size of window needed      */
  u_long                   bc;                 /* adjusted window's bc       */
  sglist_t                 dma_handle;         /* ptr to window's dma handle */
  struct ovrhd             *sgl_ovrhdp;        /* ptr to dma overhead info   */
  struct hw_sg_map_control *mapctl;            /* platform  map control info */
  u_long                   start_ba;           /* PCI base of mapped window  */
  u_long                   end_ba;             /* PCI end of mapped window   */
  int                      *sg_table_base;     /* KSEG address of base S/G   */
  u_long                   adj_start_ba;       /* PCI base aligned address   */
  u_long                   adj_end_ba;         /* PCI end aligned address    */
  int                      *adj_sg_table_base; /* KSEG alligned s/g entry    */
  struct hw_sg_map_control *vsi_mapctl;        /* VME window map control info*/
  int                      sg_pages_needed;    /* s/g entries needed         */
  u_int                    hw_sg_offset;
  u_int                    hw_sg_end_adj;
};

struct vme_slave_image {
  u_int        vsi_cntrl;        /* control register value for image         */
  u_int        vsi_base;         /* base address of VME image                */
  u_int        vsi_bnd;          /* bound address of VME image               */
  u_int        vsi_to;           /* offset to base of PCI bus address        */
  u_int        vsi_alignment;    /* Image 0 & 4 = 4kb, all others = 64kb     */
  u_int        pci_base;         /* PCI s/g base bus address of window       */
  u_int        pci_bnd;          /* PCI s/g end bus address -1 of window     */
  int          image_ena;        /* OS parameter for VME/PCI image enable    */
  vme_addr_t   vme_base;         /* OS parameter for VMEbus base address     */
  u_int        vme_wndw_size;    /* OS parameter for VME/PCI window size     */
  int          vme_addr_space;   /* OS parameter for VME address space       */
  int          vme_usr_sprvsr;   /* OS parameter for VME user/super selection*/
  int          vme_data_prg;     /* OS parameter for VME data/prog selection */
  int          wrt_post_ena;     /* OS parameter for VME window write posting*/
  int          rd_prefetch_ena;  /* OS parameter for VME read prefetch enable*/
  int          pci_64_bit_ena;   /* OS parameter for 64-bit PCI transaction  */
  int          pci_bus_lock_ena; /* OS parameter for PCI bus lock enable     */
  struct  vme_map_ctl *map_ctlp; /* pointer to mapping information for wndw  */
};

struct vme_csr_lm_image {
  u_int        cntrl_reg;        /* VMEbus Reg Access Image Control Register */
  vme_addr_t   vme_base;         /* OS parameter VME window base address     */
  int          csr_ena;          /* OS parameter for image enable/disable    */
  int          addr_space;       /* OS parameter for VME address space       */
  int          usr_sprvsr;       /* OS parameter for VME user/super selection*/
  int          data_prg;         /* OS parameter for VME data/prog selection */
};

struct univ_vme_vars {
  struct spcl_pci_slave_image   pci_slsi;
  struct pci_slave_image        pci_lsi[PCI_SLAVE_WNDWS];
  struct vme_slave_image        vme_vsi[VME_SLAVE_WNDWS];
  struct vme_map_ctl            vsi_map_ctl[VME_SLAVE_WNDWS];
  struct vme_csr_lm_image       csr;
  struct vme_csr_lm_image       lm;
  struct controller             dma_ctlr;
  sglist_t                      dma_handle;
  struct ovrhd                  *dma_ovrhdp;
  vm_offset_t                   dma_va;
  struct proc                   *dma_procp;
  u_long                        dma_pci_bus_addr;
  u_long                        dma_vme_bus_addr;
  u_long                        dma_req_bc;         /* total bc of request  */
  u_long                        dma_wndw_bc;        /* bc of pci s/g window */
  u_long                        dma_cur_bc;         /* bc of UnivII hw dma  */
  u_long                        dma_residual_bc;    /* bc of not xfered dma */
  u_long                        dma_total_xfer_bc;  /* total bc of xfer     */ 
  u_int                         dma_xfer_error;     /* 0=success 1=failure  */
  u_int                         dma_dctl_reg;
  u_int                         dma_dgcs_reg;
  dma_map_info_t                vme_dma_map_info_ptr;
  struct dma_map_info           vme_dma_map_info[VME_SLAVE_WNDWS + 2];
  int                           system_ctlr;
  int                           pci64_capable;
};

struct univ_vme_intr_info {
  u_long (*intr)();   /* interrupt service routine   */ 
  u_long param;       /* interrupt service parameter */
  u_long mask;        /* hardware interrupt mask     */
  u_short vector;     /* i/o vector offset into scb  */
};

#define UNIV_VME_COMMON_INDEX 0
#define UNIV_VME_RESET_INDEX 0
#define UNIV_VME_SPL3_INDEX  1
#define UNIV_VME_SPL4_INDEX  2
#define UNIV_VME_SPL6_INDEX  3

struct univ_vme_busvars {
  ihandler_id_t             *adapt_id_t[MAX_UNIV_VME_INT_HNDLRS];
  lock_data_t               adapt_c_lk;
  decl_simple_lock_data(,reg_s_lk)       /* simple lock for register access */
  struct univ_vme_intr_info *intr_info;
  struct vp_vme_sw          vme_sw;
  dma_map_info_t            pci_dma_info_ptr;
  dma_map_info_t            pci_sg_dma_info_ptr;
  dma_map_info_t            pci_direct_dma_info_ptr;
  dma_map_info_t            vme_dma_info_ptr;
  unsigned long             intr_mask;
  event_t                   dma_wakeup_event;
  unsigned int              dma_dgcs_intr_val;
  unsigned char             vec_irq_history[8];
  unsigned char             vec_history[VME_MAX_VEC+1];
  unsigned int              iack_post_vector;
  unsigned int              iack_post_pending;
  int                       lint_pin_policy;
};


/*
 * Linked list dma command packet
 */

struct univ_dma_cmd_packet {
  u_int        dctl_value;
  u_int        dtbc_value;
  u_int        dla_value;
  u_int        rsvd1_value;
  u_int        dva_value;
  u_int        rsvd2_value;
  union {
    struct {
      u_int value;
    } reg;
    struct {
      u_int null:1;
      u_int processed:1;
      u_int rsvd:1;
      u_int nxt_pckt:29;
    } regbit;
  } dcpp;
  u_int        rsvd3_value;
};

/*
 * I/O handles for Universe registers.
 */

struct univ_vme_io_handles {
  io_handle_t univ_pci_id;    /* PCI ID register (via PCI Mem Space)         */
  io_handle_t univ_pci_csr;   /* PCI Control/status reg (via PCI Mem Space)  */
  io_handle_t univ_pci_class; /* PCI Class code reg (via PCI Mem Space)      */
  io_handle_t univ_pci_misc0; /* PCI Config misc reg (via PCI Mem Space)     */
  io_handle_t univ_pci_bs;    /* PCI base address 0 reg (via PCI Mem Space)  */
  io_handle_t univ_pci_bs1;   /* PCI base address 1 reg (via PCI Mem Space)  */
  io_handle_t univ_rsrv_1[9];
  io_handle_t univ_pci_misc1; /* PCI Config misc 2 reg (via PCI Mem Space)   */
  io_handle_t univ_rsrv_2[48];
  /* 
   * Universe specific registers 
   */
  io_handle_t univ_lsi0_ctl;  /* PCI Slave Image 0 Control Register       */
  io_handle_t univ_lsi0_bs;   /* PCI Slave Image 0 Base Address Register  */
  io_handle_t univ_lsi0_bd;   /* PCI Slave Image 0 Bound Address Register */
  io_handle_t univ_lsi0_to;   /* PCI Slave Image 0 Translation Offset Reg */
  io_handle_t univ_rsrv_3;
  io_handle_t univ_lsi1_ctl;  /* PCI Slave Image 1 Control Register       */
  io_handle_t univ_lsi1_bs;   /* PCI Slave Image 1 Base Address Register  */
  io_handle_t univ_lsi1_bd;   /* PCI Slave Image 1 Bound Address Register */
  io_handle_t univ_lsi1_to;   /* PCI Slave Image 1 Translation Offset Reg */
  io_handle_t univ_rsvr_4;
  io_handle_t univ_lsi2_ctl;  /* PCI Slave Image 2 Control Register       */
  io_handle_t univ_lsi2_bs;   /* PCI Slave Image 2 Base Address Register  */
  io_handle_t univ_lsi2_bd;   /* PCI Slave Image 2 Bound Address Register */
  io_handle_t univ_lsi2_to;   /* PCI Slave Image 2 Translation Offset Reg */
  io_handle_t univ_rsvr_5;
  io_handle_t univ_lsi3_ctl;  /* PCI Slave Image 3 Control Register       */
  io_handle_t univ_lsi3_bs;   /* PCI Slave Image 3 Base Address Register  */
  io_handle_t univ_lsi3_bd;   /* PCI Slave Image 3 Bound Address Register */
  io_handle_t univ_lsi3_to;   /* PCI Slave Image 3 Translation Offset Reg */
  io_handle_t univ_rsvr_6[9];
  io_handle_t univ_scyc_ctl;  /* Special Cycle Control Register */
  io_handle_t univ_scyc_addr; /* Special Cycle PCI Address Register */
  io_handle_t univ_scyc_en;   /* Special Cycle Swap/Compare Enable Reg */
  io_handle_t univ_scyc_cmp;  /* Special Cycle Compare Data Register  */
  io_handle_t univ_scyc_swp;  /* Special Cycle Swap Data Register */
  io_handle_t univ_lmisc;     /* Universe PCI Misc register (timers) */
  io_handle_t univ_slsi;      /* Special PCI Slave Image. */
  io_handle_t univ_l_cmderr;  /* PCI Command Error log */
  io_handle_t univ_laerr;     /* PCI Address Error log */
  io_handle_t univ_rsvr_7[3];
  io_handle_t univ_lsi4_ctl;  /* PCI Slave Image 0 Control Register       */
  io_handle_t univ_lsi4_bs;   /* PCI Slave Image 0 Base Address Register  */
  io_handle_t univ_lsi4_bd;   /* PCI Slave Image 0 Bound Address Register */
  io_handle_t univ_lsi4_to;   /* PCI Slave Image 0 Translation Offset Reg */
  io_handle_t univ_rsvr_8;
  io_handle_t univ_lsi5_ctl;  /* PCI Slave Image 1 Control Register       */
  io_handle_t univ_lsi5_bs;   /* PCI Slave Image 1 Base Address Register  */
  io_handle_t univ_lsi5_bd;   /* PCI Slave Image 1 Bound Address Register */
  io_handle_t univ_lsi5_to;   /* PCI Slave Image 1 Translation Offset Reg */
  io_handle_t univ_rsvr_9;
  io_handle_t univ_lsi6_ctl;  /* PCI Slave Image 2 Control Register       */
  io_handle_t univ_lsi6_bs;   /* PCI Slave Image 2 Base Address Register  */
  io_handle_t univ_lsi6_bd;   /* PCI Slave Image 2 Bound Address Register */
  io_handle_t univ_lsi6_to;   /* PCI Slave Image 2 Translation Offset Reg */
  io_handle_t univ_rsvr_10;
  io_handle_t univ_lsi7_ctl;  /* PCI Slave Image 3 Control Register       */
  io_handle_t univ_lsi7_bs;   /* PCI Slave Image 3 Base Address Register  */
  io_handle_t univ_lsi7_bd;   /* PCI Slave Image 3 Bound Address Register */
  io_handle_t univ_lsi7_to;   /* PCI Slave Image 3 Translation Offset Reg */
  io_handle_t univ_rsvr_11[5];
  io_handle_t univ_dctl;      /* DMA Transfer Control Register. */
  io_handle_t univ_dtbc;      /* DMA Transfer Byte Register. */
  io_handle_t univ_dla;       /* DMA PCI Bus Address Register. */
  io_handle_t univ_rsvr_12;
  io_handle_t univ_dva;       /* DMA VMEbus Address Register. */
  io_handle_t univ_rsvr_13;
  io_handle_t univ_dcpp;      /* DMA Command Packet Pointer. */
  io_handle_t univ_rsvr_14;
  io_handle_t univ_dgcs;      /* DMA General Control and status Register */
  io_handle_t univ_dllue;     /* DMA Linked List Update Enable Register */
  io_handle_t univ_rsvr_15[54];
  io_handle_t univ_lint_en;   /* PCI Interrupt Enable Register */
  io_handle_t univ_lint_stat; /* PCI Interrupt Status Register */
  io_handle_t univ_lint_map0; /* PCI Interrupt Map 0 Register */
  io_handle_t univ_lint_map1; /* PCI Interrupt Map 1 Register */
  io_handle_t univ_vint_en;   /* VMEbus Interrupt Enable Register */
  io_handle_t univ_vint_stat; /* VMEbus Interrupt Status Register */
  io_handle_t univ_vint_map0; /* VMEbus Interrupt Map 0 Register */
  io_handle_t univ_vint_map1; /* VMEbus Interrupt Map 1 Register */
  io_handle_t univ_statid;    /* Interrupt Status/ID out Register */
  io_handle_t univ_v1_statid; /* VMEbus IRQ1 Status/ID out Register */
  io_handle_t univ_v2_statid; /* VMEbus IRQ2 Status/ID out Register */
  io_handle_t univ_v3_statid; /* VMEbus IRQ3 Status/ID out Register */
  io_handle_t univ_v4_statid; /* VMEbus IRQ4 Status/ID out Register */
  io_handle_t univ_v5_statid; /* VMEbus IRQ5 Status/ID out Register */
  io_handle_t univ_v6_statid; /* VMEbus IRQ6 Status/ID out Register */
  io_handle_t univ_v7_statid; /* VMEbus IRQ7 Status/ID out Register */
  io_handle_t univ_lint_map2; /* PCI Interrupt Map 2 Register */
  io_handle_t univ_vint_map2; /* VMEbus Interrupt Map 2 Register */
  io_handle_t univ_mbox0;     /* Mailbox 0 Register */
  io_handle_t univ_mbox1;     /* Mailbox 1 Register */
  io_handle_t univ_mbox2;     /* Mailbox 2 Register */
  io_handle_t univ_mbox3;     /* Mailbox 3 Register */
  io_handle_t univ_sema0;     /* Semaphore 0 Register */
  io_handle_t univ_sema1;     /* Semaphore 1 Register */
  io_handle_t univ_rsvr_16[40];
  io_handle_t univ_mast_ctl;  /* Master Control Register */
  io_handle_t univ_misc_ctl;  /* Miscellaneous Control Register */
  io_handle_t univ_misc_stat; /* Miscellaneous Status Register */
  io_handle_t univ_user_am;   /* User Address modifier code Register */
  io_handle_t univ_rsvr_17[700];
  io_handle_t univ_vsi0_ctl;  /* VMEbus Slave Image 0 Control Register */
  io_handle_t univ_vsi0_bs;   /* VMEbus Slave Image 0 Base Address */
  io_handle_t univ_vsi0_bd;   /* VMEbus Slave Image 0 Bound Address */
  io_handle_t univ_vsi0_to;   /* VMEbus Slave Image 0 Translation Offset */
  io_handle_t univ_rsvr_18;
  io_handle_t univ_vsi1_ctl;  /* VMEbus Slave Image 1 Control Register */
  io_handle_t univ_vsi1_bs;   /* VMEbus Slave Image 1 Base Address */
  io_handle_t univ_vsi1_bd;   /* VMEbus Slave Image 1 Bound Address */
  io_handle_t univ_vsi1_to;   /* VMEbus Slave Image 1 Translation Offset */
  io_handle_t univ_rsvr_19;
  io_handle_t univ_vsi2_ctl;  /* VMEbus Slave Image 2 Control Register */
  io_handle_t univ_vsi2_bs;   /* VMEbus Slave Image 2 Base Address */
  io_handle_t univ_vsi2_bd;   /* VMEbus Slave Image 2 Bound Address */
  io_handle_t univ_vsi2_to;   /* VMEbus Slave Image 2 Translation Offset */
  io_handle_t univ_rsvr_20;
  io_handle_t univ_vsi3_ctl;  /* VMEbus Slave Image 3 Control Register */
  io_handle_t univ_vsi3_bs;   /* VMEbus Slave Image 3 Base Address */
  io_handle_t univ_vsi3_bd;   /* VMEbus Slave Image 3 Bound Address */
  io_handle_t univ_vsi3_to;   /* VMEbus Slave Image 3 Translation Offset */
  io_handle_t univ_rsvr_21[6];
  io_handle_t univ_lm_ctl;    /* Location Monitor Control */
  io_handle_t univ_lm_bs;     /* Location Monitor Base Address Register */
  io_handle_t univ_rsvr_22;
  io_handle_t univ_vrai_ctl;  /* VMEbus Register Access Image Control */
  io_handle_t univ_vrai_bs;   /* VMEbus Register Access BAse Address */
  io_handle_t univ_rsvr_23[2];
  io_handle_t univ_vcsr_ctl;  /* VMEbus CSR Control Register */
  io_handle_t univ_vcsr_to;   /* VMEbus CSR Translation Offset */
  io_handle_t univ_v_amerr;   /* VMEbus Address Modifier Code Error log */
  io_handle_t univ_vaerr;     /* VMEbus Address Error log */
  io_handle_t univ_vsi4_ctl;  /* VMEbus Slave Image 4 Control Register */
  io_handle_t univ_vsi4_bs;   /* VMEbus Slave Image 4 Base Address */
  io_handle_t univ_vsi4_bd;   /* VMEbus Slave Image 4 Bound Address */
  io_handle_t univ_vsi4_to;   /* VMEbus Slave Image 4 Translation Offset */
  io_handle_t univ_rsvr_24;
  io_handle_t univ_vsi5_ctl;  /* VMEbus Slave Image 5 Control Register */
  io_handle_t univ_vsi5_bs;   /* VMEbus Slave Image 5 Base Address */
  io_handle_t univ_vsi5_bd;   /* VMEbus Slave Image 5 Bound Address */
  io_handle_t univ_vsi5_to;   /* VMEbus Slave Image 5 Translation Offset */
  io_handle_t univ_rsvr_25;
  io_handle_t univ_vsi6_ctl;  /* VMEbus Slave Image 6 Control Register */
  io_handle_t univ_vsi6_bs;   /* VMEbus Slave Image 6 Base Address */
  io_handle_t univ_vsi6_bd;   /* VMEbus Slave Image 6 Bound Address */
  io_handle_t univ_vsi6_to;   /* VMEbus Slave Image 6 Translation Offset */
  io_handle_t univ_rsvr_26;
  io_handle_t univ_vsi7_ctl;  /* VMEbus Slave Image 7 Control Register */
  io_handle_t univ_vsi7_bs;   /* VMEbus Slave Image 7 Base Address */
  io_handle_t univ_vsi7_bd;   /* VMEbus Slave Image 7 Bound Address */
  io_handle_t univ_vsi7_to;   /* VMEbus Slave Image 7 Translation Offset */
  io_handle_t univ_rsvr_27[5];
  io_handle_t univ_cr_csr_rsv;/* VME CR/CSR Reserved */
  io_handle_t univ_vcsr_clr;  /* VMEbus CSR Bit Clear Register */
  io_handle_t univ_vcsr_set;  /* VMEbus CSR Bit SET Register */
  io_handle_t univ_vcsr_bs;   /* VMEbus CSR Base Address Register */
};


/*
 * Constants for defining VMEbus slave image size. The values represent
 * multipliers of VME_IN_PAGE (256KB) to be used in calculating size
 */

#define VME_IN_PAGE       262144      /* "Page" size for setting inbound */
                                      /* slave images. Set to 256*1024   */
#define VME_IN_SIZE_256MB 1024        /* VMEbus slave image size = 256MB */
#define VME_IN_SIZE_128MB  512        /* VMEbus slave image size = 128MB */
#define VME_IN_SIZE_64MB   256        /* VMEbus slave image size =  64MB */
#define VME_IN_SIZE_32MB   128        /* VMEbus slave image size =  32MB */
#define VME_IN_SIZE_16MB    64        /* VMEbus slave image size =  16MB */
#define VME_IN_SIZE_8MB     32        /* VMEbus slave image size =   8MB */
#define VME_IN_SIZE_4MB     16        /* VMEbus slave image size =   4MB */
#define VME_IN_SIZE_1MB      4        /* VMEbus slave image size =   1MB */
#define VME_IN_SIZE_512KB    2        /* VMEbus slave image size = 512KB */
#define VME_IN_SIZE_256KB    1        /* VMEbus slave image size = 256KB */

#endif /* _UNIV_VME_H */




