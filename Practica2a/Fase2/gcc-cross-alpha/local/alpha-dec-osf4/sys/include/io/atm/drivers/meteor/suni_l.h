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
#pragma ident "@(#)$RCSfile: suni_l.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:56 $"

#ifndef _SUNI_L_H_
#define _SUNI_L_H_

/*
* Module Name:
*   suni_l.h
*
* Abstract:
*   This module defines all of the registers, fields, and data structures that
*   are required to access the PM5345.  It is presumed that the reader has the 
*   data sheet from the SUNI manufacturer.
* 
* External Dependencies:
*   This module imports the definitions of ULONG and UBYTE.
*
* Authors:
*   DMW - Douglas M. Washabaugh
*
* Revision History:
*   Date       Author  Description
*   03-Aug-94    DMW     Created
*
* Issues:
*   None
*
* Disclaimer:
*   Copyright Digital Equipment Corporation 1994. All rights reserved.
*
*   Restricted Rights: Use, duplication, or disclosure by the U.S. Government
*   is subject to restrictions as set forth in subparagraph (c) (1) (ii) of
*   DFARS 252.227-7013, or in FAR 52.227-19, or in FAR 52.227-14 Alt. III, as
*   applicable.
*
*   This software is proprietary to and embodies the confidential technology of
*   Digital Equipment Corporation. Possession, use, or copying of this software
*   and media is authorized only pursuant to a valid written license from
*   Digital or an authorized sublicensor.
*                                      
--*/


/* Define the base addresses of the registers. */

#define SCM_O_MRI              0x00 
#define SCM_O_MASTER_CNF       0x01    
#define SCM_O_MIS              0x02
#define SCM_O_MCM              0x04
#define SCM_O_MC               0x05
#define SCM_O_CSCS             0x06
#define SCM_O_CRCS             0x07

#define SCM_O_RSOP_CIE         0x10
#define SCM_O_RSOP_SIS         0x11
#define SCM_O_RSOP_SB0         0x12
#define SCM_O_RSOP_SB1         0x13
#define SCM_O_TSOP_CS          0x14
#define SCM_O_TSOP_D           0x15

#define SCM_O_RLOP_CS          0x18
#define SCM_O_RLOP_IEIS        0x19
#define SCM_O_RLOP_LB0         0x1A
#define SCM_O_RLOP_LB1         0x1B
#define SCM_O_RLOP_LB2         0x1C
#define SCM_O_RLOP_FEBE0       0x1D
#define SCM_O_RLOP_FEBE1       0x1E
#define SCM_O_RLOP_FEBE2       0x1F
#define SCM_O_TLOP_CS          0x20
#define SCM_O_TLOP_DIAG        0x21

#define SCM_O_RPOP_CS          0x30
#define SCM_O_RPOP_IS          0x31

#define SCM_O_RPOP_IE          0x33

#define SCM_O_RPOP_PSL         0x37
#define SCM_O_RPOP_PB0         0x38
#define SCM_O_RPOP_PB1         0x39
#define SCM_O_RPOP_FEBE0       0x3A
#define SCM_O_RPOP_FEBE1       0x3B

#define SCM_O_RPOP_PBC         0x3D

#define SCM_O_TPOP_DIAG        0x40
#define SCM_O_TPOP_PC          0x41

#define SCM_O_TPOP_AP0         0x45
#define SCM_O_TPOP_AP1         0x46

#define SCM_O_TPOP_PSL         0x48
#define SCM_O_TPOP_PS          0x49

#define SCM_O_RACP_CS          0x50
#define SCM_O_RACP_IES         0x51
#define SCM_O_RACP_MHP         0x52
#define SCM_O_RACP_MMH         0x53
#define SCM_O_RACP_CHEC        0x54
#define SCM_O_RACP_UHEC        0x55
#define SCM_O_RACP_RCC0        0x56
#define SCM_O_RACP_RCC1        0x57
#define SCM_O_RACP_RCC2        0x58
#define SCM_O_RACP_CONF        0x59

#define SCM_O_TACP_CS          0x60
#define SCM_O_TACP_IUCHP       0x61
#define SCM_O_TACP_IUCPOP      0x62                       
#define SCM_O_TACP_FIFO_CR     0x63
#define SCM_O_TACP_TCC0        0x64
#define SCM_O_TACP_TCC1        0x65
#define SCM_O_TACP_TCC2        0x66
#define SCM_O_TACP_CONF        0x67

#define SCM_O_MASTER_TEST      0x80

/* SUNI_LITE Master Reset and Idenity REGISTER                        */
/*   For the SUNI_LITE PM5346, the TYPE bits have the value 110 (6).  */

#define SCM_MRI_M_RESET        0x80 /* R/W Reset NOT self clearing.   */
#define SCM_MRI_M_TYPE_2       0x40 /* RO  ID field used as chip ID   */ 
#define SCM_MRI_M_TYPE_1       0x20 /* RO  ID field used as chip ID   */
#define SCM_MRI_M_TYPE_0       0x10 /* RO  ID field used as chip ID   */
#define SCM_MRI_M_ID_3         0x08 /* RO  Chip revision              */
#define SCM_MRI_M_ID_2         0x04 /* RO  Chip revision              */
#define SCM_MRI_M_ID_1         0x02 /* RO  Chip revision              */
#define SCM_MRI_M_ID_0         0x01 /* RO  Chip revision              */

#define SCM_MRI_M_REV_FIELD    0x0F /* Mask to extrapulate chip rev.  */
#define SCM_MRI_M_ID_FIELD     0x70 /* Mask to extrapulate chip ID.   */
#define SCM_MRI_K_LOAD_COUNTERS   0

/* SUNI-LITE Master Configuration REGISTER */

#define SCM_MASTER_M_AUTOFEBE  0x40 /* R/W */
#define SCM_MASTER_M_AUTOLRDI  0x20 /* R/W */
#define SCM_MASTER_M_AUTOPRDI  0x10 /* R/W */
#define SCM_MASTER_M_TCAINV    0x08 /* R/W */
#define SCM_MASTER_M_RCAINV    0x04 /* R/W */
#define SCM_MASTER_M_RXDINV    0x02 /* R/W */
#define SCM_MASTER_M_UNUSED    0x01 /* --- */

/* SUNI-LITE MASTER INTERRUPT STATUS REGISTER */

#define SCM_MIS_M_TROOLI       0x80 /* RO A fatal error. */
#define SCM_MIS_M_LCDI         0x40 /* RO                */
#define SCM_MIS_M_RDOOLI       0x20 /* RO A fatal error. */
#define SCM_MIS_M_TACPI        0x10 /* RO                */
#define SCM_MIS_M_RACPI        0x08 /* RO                */ 
#define SCM_MIS_M_RPOPI        0x04 /* RO                */
#define SCM_MIS_M_RLOPI        0x02 /* RO                */
#define SCM_MIS_M_RSOPI        0x01 /* RO                */

#define MASTER_STS_M_FATAL_MASK 0xA0 /* TROOLI and RDOOLI are fatal errors.  */
#define MASTER_STS_M_ERR_MASK   0x4F /* Errors which cause state transitions.*/

/* SUNI_LITE Master Clock Monitor REGISTER */

#define SCM_MCM_M_UNUSED_0     0x80 /* NU */
#define SCM_MCM_M_UNUSED_1     0x40 /* NU */
#define SCM_MCM_M_UNUSED_2     0x20 /* NU */
#define SCM_MCM_M_UNUSED_3     0x10 /* NU */
#define SCM_MCM_M_RRCLKA       0x08 /* RO */
#define SCM_MCM_M_TRCLKA       0x04 /* RO */
#define SCM_MCM_M_RCLKA        0x02 /* RO */
#define SCM_MCM_M_TCLKA        0x01 /* RO */

#define SCM_MCM_M_CLKA         0x0F
#define SCM_MCM_K_CLKA         0x0F

/* SUNI-LITE Master Control REGISTER */

#define SCM_MC_M_LCDE          0x80 /* R/W default = 0                     */
#define SCM_MC_M_LCDV          0x40 /* R                                   */
#define SCM_MC_M_FIXPTR        0x20 /* R/W default = 1                     */
#define SCM_MC_M_UNUSED_0      0x01 /* NU                                  */
#define SCM_MC_M_UNUSED_1      0x08 /* NU                                  */
#define SCM_MC_M_LLE           0x04 /* R/W default = 0                     */
#define SCM_MC_M_DLE           0x02 /* R/W default = 0                     */
#define SCM_MC_M_LOOPT         0x01 /* R/W LOOP/LOCAL default = 0 (LOCAL)  */

#define SCM_MC_K_EN_LCD_INTR      1

/* SUNI-LITE Clock Synthesis Control and Status REGISTER */

#define SCM_CSCS_M_UNUSED_0    0x80 /* NU                                  */
#define SCM_CSCS_M_UNUSED_1    0x40 /* NU                                  */
#define SCM_CSCS_M_UNUSED_2    0x20 /* NU                                  */
#define SCM_CSCS_M_UNUSED_3    0x10 /* NU                                  */
#define SCM_CSCS_M_TROOLV      0x08 /* R                                   */
#define SCM_CSCS_M_UNUSED_4    0x04 /* NU                                  */
#define SCM_CSCS_M_TROOLE      0x02 /* R/W default = 0                     */
#define SCM_CSCS_M_TREFSEL     0x01 /* R/W default = 0                     */

#define SCM_CSCS_K_EN_TROOL_INTR  1                                   
/* SUNI-LITE Clock Recovery Control and Status REGISTER */

#define SCM_CRCS_M_UNUSED_0    0x80 /* NU                                  */
#define SCM_CRCS_M_UNUSED_1    0x40 /* NU                                  */
#define SCM_CRCS_M_UNUSED_2    0x20 /* NU                                  */
#define SCM_CRCS_M_UNUSED_3    0x10 /* NU                                  */
#define SCM_CRCS_M_RDOOLV      0x08 /* R                                   */
#define SCM_CRCS_M_UNUSED_4    0x04 /* NU                                  */
#define SCM_CRCS_M_RDOOLE      0x02 /* R/W  default = 0                    */
#define SCM_CRCS_M_RREFSEL     0x01 /* R/W  default = 0                    */

#define SCM_CRCS_K_EN_RDOOL_INTR  1
/* SUNI-LITE RSOP Control/Interrupt Enable REGISTER */

#define SCM_RSOP_M_UNUSED_0    0x80 /* NU                                   */
#define SCM_RSOP_M_DDS         0x40 /* R/W  default = 0                     */
#define SCM_RSOP_M_FOOF        0x20 /* W    default = x                     */
#define SCM_RSOP_M_UNUSED_1    0x01 /* NU                                   */
#define SCM_RSOP_M_BIPEE       0x08 /* R/W  default = 0                     */
#define SCM_RSOP_M_LOSE        0x04 /* R/W  default = 0                     */
#define SCM_RSOP_M_LOFE        0x02 /* R/W  default = 0                     */
#define SCM_RSOP_M_OOFE        0x01 /* R/W  default = 0                     */

#define SCM_RSOP_K_EN_BIPE_INTR   1
#define SCM_RSOP_K_EN_LOS_INTR    1
#define SCM_RSOP_K_EN_LOF_INTR    1
#define SCM_RSOP_K_EN_OOF_INTR    1
                                                                           
/* SUNI-LITE RSOP Status/Interrupt Status REGISTER */

#define SCM_RSOP_M_BIPEI       0x40 /* R                                    */
#define SCM_RSOP_M_LOSI        0x20 /* R                                    */
#define SCM_RSOP_M_LOFI        0x10 /* R                                    */
#define SCM_RSOP_M_OOFI        0x08 /* R                                    */
#define SCM_RSOP_M_LOSV        0x04 /* R                                    */
#define SCM_RSOP_M_LOFV        0x02 /* R                                    */
#define SCM_RSOP_M_OOFV        0x01 /* R                                    */

/* SUNI-LITE RSOP Section BIP-8 LSB REGISTER */
     
#define SCM_RSOP_M_SBE7        0x80 /* R                                    */
#define SCM_RSOP_M_SBE6        0x40 /* R                                    */
#define SCM_RSOP_M_SBE5        0x20 /* R                                    */
#define SCM_RSOP_M_SBE4        0x10 /* R                                    */
#define SCM_RSOP_M_SBE3        0x08 /* R                                    */
#define SCM_RSOP_M_SBE2        0x04 /* R                                    */
#define SCM_RSOP_M_SBE1        0x02 /* R                                    */
#define SCM_RSOP_M_SBE0        0x01 /* R                                    */

/* SUNI-LITE RSOP Section BIP-8 MSB REGISTER */

#define SCM_RSOP_M_SBE15       0x80 /* R                                    */
#define SCM_RSOP_M_SBE14       0x40 /* R                                    */
#define SCM_RSOP_M_SBE13       0x20 /* R                                    */
#define SCM_RSOP_M_SBE12       0x10 /* R                                    */
#define SCM_RSOP_M_SBE11       0x08 /* R                                    */
#define SCM_RSOP_M_SBE10       0x04 /* R                                    */
#define SCM_RSOP_M_SBE9        0x02 /* R                                    */
#define SCM_RSOP_M_SBE8        0x01 /* R                                    */

/* SUNI-LITE TSOP Control REGISTER */

#define SCM_TSOP_M_UNUSED_0    0x80 /* NU                                   */
#define SCM_TSOP_M_DS          0x40 /* R/W  default = 0                     */
#define SCM_TSOP_M_UNUSED_1    0x20 /* NU                                   */
#define SCM_TSOP_M_UNUSED_2    0x10 /* NU                                   */
#define SCM_TSOP_M_UNUSED_3    0x08 /* NU                                   */
#define SCM_TSOP_M_UNUSED_4    0x04 /* NU                                   */
#define SCM_TSOP_M_UNUSED_5    0x02 /* NU                                   */
#define SCM_TSOP_M_LAIS        0x01 /* R/W  default = 0                     */

/* SUNI-LITE TSOP Diagnostic REGISTER */

#define SCM_TSOP_M_UNUSED_6    0x80 /* NU                                   */
#define SCM_TSOP_M_UNUSED_7    0x40 /* NU                                   */
#define SCM_TSOP_M_UNUSED_8    0x20 /* NU                                   */
#define SCM_TSOP_M_UNUSED_9    0x10 /* NU                                   */
#define SCM_TSOP_M_UNUSED_10   0x08 /* NU                                   */
#define SCM_TSOP_M_DLOS        0x04 /* R/W  default = 0                     */
#define SCM_TSOP_M_DBIP8       0x02 /* R/W  default = 0                     */
#define SCM_TSOP_M_DFP         0x01 /* R/W  default = 0                     */
                                     
/* SUNI-LITE RLOP Control/Status REGISTER */

#define SCM_RLOP_M_BIPWORD     0x80 /* R/W  default = 0                     */
#define SCM_RLOP_M_UNUSED_0    0x40 /* NU                                   */
#define SCM_RLOP_M_UNUSED_1    0x20 /* NU                                   */
#define SCM_RLOP_M_UNUSED_2    0x10 /* NU                                   */
#define SCM_RLOP_M_UNUSED_3    0x08 /* NU                                   */
#define SCM_RLOP_M_UNUSED_4    0x04 /* NU                                   */
#define SCM_RLOP_M_LAISV       0x02 /* R                                    */
#define SCM_RLOP_M_RDIV        0x01 /* R                                    */

/*                 
 * SUNI-LITE RLOP Interrupt Enable/Interrupt Status  REGISTER
 */

#define SCM_RLOP_M_FEBEE       0x80 /* R/W default = 0                      */
#define SCM_RLOP_M_BIPEE       0x40 /* R/W default = 0                      */
#define SCM_RLOP_M_LAISE       0x20 /* R/W default = 0                      */
#define SCM_RLOP_M_RDIE        0x10 /* R/W default = 0                      */
#define SCM_RLOP_M_FEBEI       0x08 /* R                                    */
#define SCM_RLOP_M_BIPEI       0x04 /* R                                    */
#define SCM_RLOP_M_LAISI       0x02 /* R                                    */
#define SCM_RLOP_M_RDII        0x01 /* R                                    */

#define SCM_RLOP_K_EN_FEBE_INTR   1
#define SCM_RLOP_K_EN_BIPE_INTR   1
#define SCM_RLOP_K_EN_LAIS_INTR   1
#define SCM_RLOP_K_EN_RDI_INTR    1
/*
 * SUNI-LITE RLOP Line BIP-8/24 LSB REGISTER
 */

#define SCM_RLOP_M_LBE_7_0     0xFF /* R                                    */
                                     
/*
 * SUNI-LITE RLOP Line BIP-8/24 MSB REGISTER
 */

#define SCM_RLOP_M_LBE_15_8    0xFF /* R                                    */
                                                                          
/*
 * SUNI-LITE RLOP Line BIP-8/24 MSB REGISTER
 */

#define SCM_RLOP_M_UNUSED_5    0x80 /* NU                                   */
#define SCM_RLOP_M_UNUSED_6    0x40 /* NU                                   */
#define SCM_RLOP_M_UNUSED_7    0x20 /* NU                                   */
#define SCM_RLOP_M_UNUSED_8    0x10 /* NU                                   */
#define SCM_RLOP_M_LBE_19_16   0x0F /* R                                    */
                                     
/*                                   
 * SUNI-LITE RLOP Line FEBE LSB REGISTER
 */

#define SCM_RLOP_M_LFEBE_7_0   0xFF /* R                                    */

/*
 * SUNI-LITE RLOP Line FEBE MSB REGISTER
 */

#define SCM_RLOP_M_LFEBE_15_8  0xFF /* R                                    */
                                     
/*
 * SUNI-LITE RLOP Line FEBE MSB REGISTER
 */

#define SCM_RLOP_M_UNUSED_9    0x80 /* NU                                   */
#define SCM_RLOP_M_UNUSED_10   0x40 /* NU                                   */
#define SCM_RLOP_M_UNUSED_11   0x20 /* NU                                   */
#define SCM_RLOP_M_UNUSED_12   0x10 /* NU                                   */
#define SCM_RLOP_M_LFEBE19_16  0x0F /* R                                    */

/*
 * SUNI-LITE TLOP Control REGISTER
 */

#define SCM_TLOP_M_UNUSED_0    0x80 /* NU                                   */
#define SCM_TLOP_M_UNUSED_1    0x40 /* NU                                   */
#define SCM_TLOP_M_UNUSED_2    0x20 /* NU                                   */
#define SCM_TLOP_M_UNUSED_3    0x10 /* NU                                   */
#define SCM_TLOP_M_UNUSED_4    0x08 /* NU                                   */
#define SCM_TLOP_M_UNUSED_5    0x04 /* NU                                   */
#define SCM_TLOP_M_UNUSED_6    0x02 /* NU                                   */
#define SCM_TLOP_M_DRDI        0x01 /* R/W default = 0                      */

/*
 * SUNI-LITE TLOP Diagnostic REGISTER
 */

#define SCM_TLOP_M_UNUSED_7    0x80 /* NU                                   */
#define SCM_TLOP_M_UNUSED_8    0x40 /* NU                                   */
#define SCM_TLOP_M_UNUSED_9    0x20 /* NU                                   */
#define SCM_TLOP_M_UNUSED_10   0x10 /* NU                                   */
#define SCM_TLOP_M_UNUSED_11   0x08 /* NU                                   */
#define SCM_TLOP_M_UNUSED_12   0x04 /* NU                                   */
#define SCM_TLOP_M_UNUSED_13   0x02 /* NU                                   */
#define SCM_TLOP_M_DBIP        0x01 /* R/W default = 0                      */
                              
/*
 * SUNI-LITE RPOP Status/Control REGISTER
 */

#define SCM_RPOP_M_UNUSED_0    0x80 /* NU                                   */
#define SCM_RPOP_M_UNUSED_1    0x40 /* NU                                   */
#define SCM_RPOP_M_LOP         0x20 /* R                                    */
#define SCM_RPOP_M_UNUSED_2    0x10 /* NU                                   */
#define SCM_RPOP_M_PAIS        0x08 /* R                                    */
#define SCM_RPOP_M_PRDI        0x04 /* R                                    */
#define SCM_RPOP_M_UNUSED_3    0x02 /* NU                                   */
#define SCM_RPOP_M_UNUSED_4    0x01 /* NU                                   */

/*
 * SUNI-LITE RPOP Interrupt Status REGISTER
 */

#define SCM_RPOP_M_PSLI        0x80 /* R                                    */
#define SCM_RPOP_M_UNUSED_5    0x40 /* NU                                   */
#define SCM_RPOP_M_LOPI        0x20 /* R                                    */
#define SCM_RPOP_M_UNUSED_6    0x10 /* NU                                   */
#define SCM_RPOP_M_PAISI       0x08 /* R                                    */
#define SCM_RPOP_M_PRDII       0x04 /* R                                    */
#define SCM_RPOP_M_BIPEI       0x02 /* R                                    */
#define SCM_RPOP_M_FEBEI       0x01 /* R                                    */

/*
 * SUNI-LITE RPOP Interrupt Enable REGISTER
 */

#define SCM_RPOP_M_PSLE        0x80 /* R/W default = 0                      */
#define SCM_RPOP_M_UNUSED_7    0x40 /* NU                                   */
#define SCM_RPOP_M_LOPE        0x20 /* R/W default = 0                      */
#define SCM_RPOP_M_UNUSED_8    0x10 /* NU                                   */
#define SCM_RPOP_M_PAISE       0x08 /* R/W default = 0                      */
#define SCM_RPOP_M_PRDIE       0x04 /* R/W default = 0                      */
#define SCM_RPOP_M_BIPEE       0x02 /* R/W default = 0                      */
#define SCM_RPOP_M_FEBEE       0x01 /* R/W default = 0                      */

#define SCM_RPOP_K_EN_PSL_INTR    1
#define SCM_RPOP_K_EN_LOP_INTR    1
#define SCM_RPOP_K_EN_PAIS_INTR   1 
#define SCM_RPOP_K_EN_PRDI_INTR   1 
#define SCM_RPOP_K_EN_BIPE_INTR   1 
#define SCM_RPOP_K_EN_FEBE_INTR   1 

/*
 * SUNI-LITE RPOP Path Signal Label REGISTER
 */

#define SCM_RPOP_M_PSL7        0x80 /* R                                    */
#define SCM_RPOP_M_PSL6        0x40 /* R                                    */
#define SCM_RPOP_M_PSL5        0x20 /* R                                    */
#define SCM_RPOP_M_PSL4        0x10 /* R                                    */
#define SCM_RPOP_M_PSL3        0x08 /* R                                    */
#define SCM_RPOP_M_PSL2        0x04 /* R                                    */
#define SCM_RPOP_M_PSL1        0x02 /* R                                    */
#define SCM_RPOP_M_PSL0        0x01 /* R                                    */

/*
 * SUNI-LITE RPOP Path BIP-8 LSB REGISTER
 */

#define SCM_RPOP_M_PBE7        0x80 /* R                                    */
#define SCM_RPOP_M_PBE6        0x40 /* R                                    */
#define SCM_RPOP_M_PBE5        0x20 /* R                                    */
#define SCM_RPOP_M_PBE4        0x10 /* R                                    */
#define SCM_RPOP_M_PBE3        0x08 /* R                                    */
#define SCM_RPOP_M_PBE2        0x04 /* R                                    */
#define SCM_RPOP_M_PBE1        0x02 /* R                                    */
#define SCM_RPOP_M_PBE0        0x01 /* R                                    */

/*
 * SUNI-LITE RPOP Path BIP-8 MSB REGISTER
 */

#define SCM_RPOP_M_PBE15       0x80 /* R                                    */
#define SCM_RPOP_M_PBE14       0x40 /* R                                    */
#define SCM_RPOP_M_PBE13       0x20 /* R                                    */
#define SCM_RPOP_M_PBE12       0x10 /* R                                    */
#define SCM_RPOP_M_PBE11       0x08 /* R                                    */
#define SCM_RPOP_M_PBE10       0x04 /* R                                    */
#define SCM_RPOP_M_PBE9        0x02 /* R                                    */
#define SCM_RPOP_M_PBE8        0x01 /* R                                    */

/*
 * SUNI-LITE RPOP Path FEBE LSB REGISTER
 */

#define SCM_RPOP_M_PFE7        0x80 /* R                                    */
#define SCM_RPOP_M_PFE6        0x40 /* R                                    */
#define SCM_RPOP_M_PFE5        0x20 /* R                                    */
#define SCM_RPOP_M_PFE4        0x10 /* R                                    */
#define SCM_RPOP_M_PFE3        0x08 /* R                                    */
#define SCM_RPOP_M_PFE2        0x04 /* R                                    */
#define SCM_RPOP_M_PFE1        0x02 /* R                                    */
#define SCM_RPOP_M_PFE0        0x01 /* R                                    */

/*
 * SUNI-LITE RPOP Path FEBE MSB REGISTER
 */

#define SCM_RPOP_M_PFE15       0x80 /* R                                    */
#define SCM_RPOP_M_PFE14       0x40 /* R                                    */
#define SCM_RPOP_M_PFE13       0x20 /* R                                    */
#define SCM_RPOP_M_PFE12       0x10 /* R                                    */
#define SCM_RPOP_M_PFE11       0x08 /* R                                    */
#define SCM_RPOP_M_PFE10       0x04 /* R                                    */
#define SCM_RPOP_M_PFE9        0x02 /* R                                    */
#define SCM_RPOP_M_PFE8        0x01 /* R                                    */

/*
 * SUNI-LITE TPOP Control/Diagnostic REGISTER
 */

#define SCM_TPOP_M_UNUSED_0    0x80 /* NU                                   */
#define SCM_TPOP_M_UNUSED_1    0x40 /* NU                                   */
#define SCM_TPOP_M_UNUSED_2    0x20 /* NU                                   */
#define SCM_TPOP_M_UNUSED_3    0x10 /* NU                                   */
#define SCM_TPOP_M_UNUSED_4    0x08 /* NU                                   */
#define SCM_TPOP_M_UNUSED_5    0x04 /* NU                                   */
#define SCM_TPOP_M_DB3         0x02 /* R/W default = 0                      */
#define SCM_TPOP_M_PAIS        0x01 /* R/W default = 0                      */

/*
 * SUNI-LITE TPOP Pointer Control REGISTER
 */

#define SCM_TPOP_M_UNUSED_6    0x80 /* NU                                   */
#define SCM_TPOP_M_FTPTR       0x40 /* R/W default = 0                      */
#define SCM_TPOP_M_SOS         0x20 /* R/W default = 0                      */
#define SCM_TPOP_M_PLS         0x10 /* R/W default = 0                      */
#define SCM_TPOP_M_NDF         0x08 /* R/W default = 0                      */
#define SCM_TPOP_M_NSE         0x04 /* R/W default = 0                      */
#define SCM_TPOP_M_PSE         0x02 /* R/W default = 0                      */
#define SCM_TPOP_M_UNUSED_7    0x01 /* NU                                   */

/*
 * SUNI-LITE TPOP Arbitrary Pointer LSB REGISTER
 */

#define SCM_TPOP_M_APTR7       0x80 /* R/W default = 0                      */
#define SCM_TPOP_M_APTR6       0x40 /* R/W default = 0                      */
#define SCM_TPOP_M_APTR5       0x20 /* R/W default = 0                      */
#define SCM_TPOP_M_APTR4       0x10 /* R/W default = 0                      */
#define SCM_TPOP_M_APTR3       0x08 /* R/W default = 0                      */
#define SCM_TPOP_M_APTR2       0x04 /* R/W default = 0                      */
#define SCM_TPOP_M_APTR1       0x02 /* R/W default = 0                      */
#define SCM_TPOP_M_APTR0       0x01 /* R/W default = 0                      */

/*
 * SUNI-LITE TPOP Arbitrary Pointer MSB REGISTER
 */

#define SCM_TPOP_AP_M_NDF3     0x80 /* R/W default = 1                      */
#define SCM_TPOP_AP_M_NDF2     0x40 /* R/W default = 0                      */
#define SCM_TPOP_AP_M_NDF1     0x20 /* R/W default = 0                      */
#define SCM_TPOP_AP_M_NDF0     0x10 /* R/W default = 1                      */
#define SCM_TPOP_AP_M_S1       0x08 /* R/W default = 0                      */
#define SCM_TPOP_AP_M_S0       0x04 /* R/W default = 0                      */
#define SCM_TPOP_AP_M_APTR9    0x02 /* R/W default = 0                      */
#define SCM_TPOP_AP_M_APTR8    0x01 /* R/W default = 0                      */

#define SCM_TPOP_AP_K_SDH      0x98 /* Initialization Value if SDH          */
#define SCM_TPOP_AP_K_SONET    0x90 /* Initialization Value if SONET        */

/*
 * SUNI-LITE TPOP Path Status REGISTER
 */

#define SCM_TPOP_M_PFE3        0x80 /* R/W default = 0                      */
#define SCM_TPOP_M_PFE2        0x40 /* R/W default = 0                      */
#define SCM_TPOP_M_PFE1        0x20 /* R/W default = 0                      */
#define SCM_TPOP_M_PFE0        0x10 /* R/W default = 0                      */
#define SCM_TPOP_M_PRDI        0x08 /* R/W default = 0                      */
#define SCM_TPOP_M_G12         0x04 /* R/W default = 0                      */
#define SCM_TPOP_M_G11         0x02 /* R/W default = 0                      */
#define SCM_TPOP_M_G10         0x01 /* R/W default = 0                      */


/*
 * SUNI-LITE RACP Control/Status REGISTER
 */

#define SCM_RACP_M_OOCDV       0x80 /* R/W default = 0                      */
#define SCM_RACP_M_RXPTYPE     0x40 /* R/W default = 0                      */
#define SCM_RACP_M_PASS        0x20 /* R/W default = 0                      */
#define SCM_RACP_M_DISCOR      0x10 /* R/W default = 0                      */
#define SCM_RACP_M_HCSPASS     0x08 /* R/W default = 0                      */
#define SCM_RACP_M_HCSADD      0x04 /* R/W default = 1                      */
#define SCM_RACP_M_DDCSR       0x02 /* R/W default = 0                      */
#define SCM_RACP_M_FIFORST     0x01 /* R/W default = 0                      */

#define SCM_RACP_K_DROP_MATCH  0
#define SCM_RACP_K_COR_EN      0
#define SCM_RACP_K_DROP_UNCOR  0
#define SCM_RACP_K_FIFORST_SET 1
#define SCM_RACP_K_FIFORST_CLR 0

/*
 * SUNI-LITE RACP Interrupt Enable/Status REGISTER
 */

#define SCM_RACP_M_OOCDE       0x80 /* R/W default = 0                      */
#define SCM_RACP_M_HCSE        0x40 /* R/W default = 0                      */
#define SCM_RACP_M_FIFOE       0x20 /* R/W default = 0                      */
#define SCM_RACP_M_OOCDI       0x10 /* R                                    */
#define SCM_RACP_M_CHCSI       0x08 /* R                                    */
#define SCM_RACP_M_UHCSI       0x04 /* R                                    */
#define SCM_RACP_M_FOVRI       0x02 /* R                                    */
#define SCM_RACP_M_UNUSED_0    0x01 /* NU                                   */

#define SCM_RACP_K_EN_OOCD_INTR   1
#define SCM_RACP_K_EN_HCS_INTR    1  
#define SCM_RACP_K_EN_FIFO_INTR   1  
                                                                         
/*
 * SUNI-LITE RACP Match Header Pattern REGISTER
 */

#define SCM_RACP_M_GFC3        0x80 /* R/W default = 0                      */
#define SCM_RACP_M_GFC2        0x40 /* R/W default = 0                      */
#define SCM_RACP_M_GFC1        0x20 /* R/W default = 0                      */
#define SCM_RACP_M_GFC0        0x10 /* R/W default = 0                      */
#define SCM_RACP_M_PTI2        0x08 /* R/W default = 0                      */
#define SCM_RACP_M_PTI1        0x04 /* R/W default = 0                      */
#define SCM_RACP_M_PTI0        0x02 /* R/W default = 0                      */
#define SCM_RACP_M_CLP         0x01 /* R/W default = 0                      */

#define SCM_RACP_K_CLP_1          1

/*
 * SUNI-LITE RACP Match Header Mask REGISTER
 */

#define SCM_RACP_M_MGFC3       0x80 /* R/W default = 0                      */
#define SCM_RACP_M_MGFC2       0x40 /* R/W default = 0                      */
#define SCM_RACP_M_MGFC1       0x20 /* R/W default = 0                      */
#define SCM_RACP_M_MGFC0       0x10 /* R/W default = 0                      */
#define SCM_RACP_M_MPTI2       0x08 /* R/W default = 0                      */
#define SCM_RACP_M_MPTI1       0x04 /* R/W default = 0                      */
#define SCM_RACP_M_MPTI0       0x02 /* R/W Default = 0                      */
#define SCM_RACP_M_MCLP        0x01 /* R/W Default = 0                      */

#define SCM_RACP_K_MCLP_1         1

/*
 * SUNI-LITE RACP Correctable HCS Error Count REGISTER
 */

#define SCM_RACP_M_CHCS7       0x80 /* R                                    */
#define SCM_RACP_M_CHCS6       0x40 /* R                                    */
#define SCM_RACP_M_CHCS5       0x20 /* R                                    */
#define SCM_RACP_M_CHCS4       0x10 /* R                                    */
#define SCM_RACP_M_CHCS3       0x08 /* R                                    */
#define SCM_RACP_M_CHCS2       0x04 /* R                                    */
#define SCM_RACP_M_CHCS1       0x02 /* R                                    */
#define SCM_RACP_M_CHCS0       0x01 /* R                                    */

/*
 * SUNI-LITE RACP Uncorrectable HCS Error Count REGISTER
 */

#define SCM_RACP_M_UHCS7       0x80 /* R                                    */
#define SCM_RACP_M_UHCS6       0x40 /* R                                    */
#define SCM_RACP_M_UHCS5       0x20 /* R                                    */
#define SCM_RACP_M_UHCS4       0x10 /* R                                    */
#define SCM_RACP_M_UHCS3       0x08 /* R                                    */
#define SCM_RACP_M_UHCS2       0x04 /* R                                    */
#define SCM_RACP_M_UHCS1       0x02 /* R                                    */
#define SCM_RACP_M_UHCS0       0x01 /* R                                    */

/*
 * SUNI-LITE RACP Receive Cell Counter LSB REGISTER
 */

#define SCM_RACP_M_RCELL_7_0   0xFF /* R                                    */

/*
 * SUNI-LITE RACP Receive Cell Counter MSB REGISTER
 */

#define SCM_RACP_M_RCELL_15_8  0xFF /* R                                    */

/*
 * SUNI-LITE RACP Receive Cell Counter MSB REGISTER
 */

#define SCM_RACP_M_UNUSED_1    0x80 /* NU                                   */
#define SCM_RACP_M_UNUSED_2    0x40 /* NU                                   */
#define SCM_RACP_M_UNUSED_3    0x20 /* NU                                   */
#define SCM_RACP_M_UNUSED_4    0x10 /* NU                                   */
#define SCM_RACP_M_UNUSED_5    0x08 /* NU                                   */
#define SCM_RACP_M_RCELL_18_16 0x07 /* R                                    */

/*
 * SUNI-LITE RACP Configuration REGISTER
 */

#define SCM_RACP_M_RGFCE3      0x80 /* R/W default = 1                      */
#define SCM_RACP_M_RGFCE2      0x40 /* R/W default = 1                      */
#define SCM_RACP_M_RGFCE1      0x20 /* R/W default = 1                      */
#define SCM_RACP_M_RGFCE0      0x10 /* R/W default = 1                      */
#define SCM_RACP_M_FSEN        0x08 /* R/W default = 1                      */
#define SCM_RACP_M_RCALEVEL0   0x04 /* R/W default = 1                      */
#define SCM_RACP_M_HCSFTR1     0x02 /* R/W default = 0                      */
#define SCM_RACP_M_HCSFTR0     0x01 /* R/W default = 0                      */

/*
 * SUNI-LITE TACP Control/Status REGISTER
 */

#define SCM_TACP_M_FIFOE       0x80 /* R/W default = 0                      */
#define SCM_TACP_M_TSOCI       0x40 /* R                                    */
#define SCM_TACP_M_FOVRI       0x20 /* R                                    */
#define SCM_TACP_M_DHCS        0x10 /* R/W default = 0                      */
#define SCM_TACP_M_HCSB        0x08 /* R/W default = 0                      */
#define SCM_TACP_M_HCSADD      0x04 /* R/W default = 1                      */
#define SCM_TACP_M_DSCR        0x02 /* R/W default = 0                      */
#define SCM_TACP_M_FIFORST     0x01 /* R/W default = 0                      */

#define SCM_TACP_K_NO_HCSADD      0
#define SCM_TACP_K_EN_FIFO_INTR   1
#define SCM_TACP_K_FIFORST_CLR    0
#define SCM_TACP_K_FIFORST_SET    1

/*
 * SUNI-LITE TACP Idle/Unassigned Cell Header Pattern REGISTER
 */

#define SCM_TACP_M_IGFC3       0x80 /* R/W default = 0                      */
#define SCM_TACP_M_IGFC2       0x40 /* R/W default = 0                      */
#define SCM_TACP_M_IGFC1       0x20 /* R/W default = 0                      */
#define SCM_TACP_M_IGFC0       0x10 /* R/W default = 0                      */
#define SCM_TACP_M_IPTI2       0x08 /* R/W default = 0                      */
#define SCM_TACP_M_IPTI1       0x04 /* R/W default = 0                      */
#define SCM_TACP_M_IPTI0       0x02 /* R/W default = 0                      */
#define SCM_TACP_M_ICLP        0x01 /* R/W default = 0                      */

#define SCM_TACP_K_ICLP_1      0x01
                                                                               
/*                                                                      
 * SUNI-LITE TACP Idle/Unassigned Cell Payload Octet Pattern REGISTER   
 */                                                                    
                                                                       
#define SCM_TACP_M_ICP7        0x80 /* R/W default = 0                      */
#define SCM_TACP_M_ICP6        0x40 /* R/W default = 1                      */
#define SCM_TACP_M_ICP5        0x20 /* R/W default = 1                      */
#define SCM_TACP_M_ICP4        0x10 /* R/W default = 0                      */
#define SCM_TACP_M_ICP3        0x08 /* R/W default = 1                      */
#define SCM_TACP_M_ICP2        0x04 /* R/W default = 0                      */
#define SCM_TACP_M_ICP1        0x02 /* R/W default = 1                      */
#define SCM_TACP_M_ICP0        0x01 /* R/W default = 0                      */

/*
 * SUNI-LITE TACP FIFO Control REGISTER
 */

#define SCM_TACP_M_TXPTYP      0x80 /* R/W default = 0                      */
#define SCM_TACP_M_TXPRTYE     0x40 /* R/W default = 0                      */
#define SCM_TACP_M_UNUSED_0    0x20 /* NU                                   */
#define SCM_TACP_M_TXPRTYI     0x10 /* R                                    */
#define SCM_TACP_M_FIFODP      0x0C /* R/W default = 00                     */
#define SCM_TACP_M_TCALEVEL0   0x02 /* R/W default = 0                      */
#define SCM_TACP_M_UNUSED_1    0x01 /* NU                                   */

#define SCM_TACP_K_DIS_PAR        0
#define SCM_TACP_K_FIFO_DPTH_2    2 
/*
 * SUNI-LITE TACP Transmit Cell Counter LSB REGISTER
 */

#define SCM_TACP_M_TCELL_7_0   0xFF /* R                                    */

/*
 * SUNI-LITE TACP Transmit Cell Counter MSB REGISTER
 */

#define SCM_TACP_M_TCELL_15_8  0xFF /* R                                    */

/*
 * SUNI-LITE TACP Transmit Cell Counter MSB REGISTER
 */
#define SCM_TACP_M_UNUSED_2    0x80 /* NU                                   */
#define SCM_TACP_M_UNUSED_3    0x40 /* NU                                   */
#define SCM_TACP_M_UNUSED_4    0x20 /* NU                                   */
#define SCM_TACP_M_UNUSED_5    0x10 /* NU                                   */
#define SCM_TACP_M_UNUSED_6    0x08 /* NU                                   */
#define SCM_TACP_M_TCELL_18_16 0x07 /* R                                    */

/*
 * SUNI-LITE TACP Configuration REGISTER
 */

#define SCM_TACP_M_TGFCE3      0x80 /* R/W default = 0                      */
#define SCM_TACP_M_TGFCE2      0x40 /* R/W default = 0                      */
#define SCM_TACP_M_TGFCE1      0x20 /* R/W default = 0                      */
#define SCM_TACP_M_TGFCE0      0x10 /* R/W default = 0                      */
#define SCM_TACP_M_TFSEN       0x08 /* R/W default = 1                      */
#define SCM_TACP_M_H4INSB      0x04 /* R/W default = 0                      */
#define SCM_TACP_M_FIXBYTE1    0x02 /* R/W default = 0                      */
#define SCM_TACP_M_FIXBYTE0    0x01 /* R/W default = 0                      */


/*
 * SUNI-LITE Master Test REGISTER
 */

#define SCM_TEST_M_UNUSED_0     0x80 /* NU                                   */
#define SCM_TEST_M_UNUSED_1     0x40 /* NU                                   */
#define SCM_TEST_M_UNUSED_2     0x20 /* NU                                   */
#define SCM_TEST_M_PMCTST       0x10 /* W                                    */
#define SCM_TEST_M_DCBTRL       0x08 /* W                                    */
#define SCM_TEST_M_IOTST        0x04 /* R/W default = 0                      */
#define SCM_TEST_M_HIZDATA      0x02 /* W                                    */
#define SCM_TEST_M_HIZIO        0x01 /* R/W default = 0                      */



/*
 * SCM LINK STATUS CONSTANTS
 *
 * The following constants are used to manipulate the link status which is
 * maintained in the firmware. The link status is actually a member of the scm
 * control block and determines the phy entity state, based on current signal
 * conditions.
 *
 */

#define SCM_LINK_STAT_RLOC     0x0001 /* RCV Lost of Clock.                  */
#define SCM_LINK_STAT_RLOS     0x0002 /* RCV Section Lost of Signal.         */
#define SCM_LINK_STAT_RLOF     0x0004 /* RCV Section Out Of Frame.           */
#define SCM_LINK_STAT_ROOF     0x0008 /* RCV Section Lost Of Frame.          */
#define SCM_LINK_STAT_RLAIS    0x0010 /* RCV Line Alarm Indication Signal.   */
#define SCM_LINK_STAT_RPLOP    0x0020 /* RCV Path Lost Of Pointer.           */
#define SCM_LINK_STAT_RPAIS    0x0040 /* RCV Path Alarm Indication Signal.   */
#define SCM_LINK_STAT_RPRDI    0x0000 /* RCV Path Remote Detection Indication*/
#define SCM_LINK_STAT_LCD      0x0100 /* Lost Cell Delineation (RCV down).   */
#define SCM_LINK_STAT_OOCD     0x0200 /* Cell state change (RCV down).       */
#define SCM_LINK_STAT_RFIFO    0x0400 /* RCV Fifo Overrun (threshold ctrl).  */
#define SCM_LINK_STAT_TLOC     0x1000 /* XMT Lost of Clock.                  */
#define SCM_LINK_STAT_RLRDI    0x2000 /* XMT Line Remote Defect Indication.  */
#define SCM_LINK_STAT_TFIFO    0x4000 /* XMT Fifo Overrun (threshold ctrl).  */

#endif	/* _SUNI_L_H_ */
