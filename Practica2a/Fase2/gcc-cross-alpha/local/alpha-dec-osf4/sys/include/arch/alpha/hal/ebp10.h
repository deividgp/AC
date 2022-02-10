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
 * @(#)$RCSfile: ebp10.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1994/07/15 17:09:00 $
 */

#ifndef	_ARCH_ALPHA_HAL_EBP10_H
#define	_ARCH_ALPHA_HAL_EBP10_H

/* burnsfix - from io_access.c */
#define IOA_OKAY	0
#define	IOA_ERROR	-1

#ifndef EBP10_NEW_ID_SEL	/* (NOT) / Defined in ebp10.c */
#define EBP10_MIN_PCI_SLOT 0	 /* PCI AD<15> */
#define EBP10_MAX_PCI_SLOT 10  /* PCI AD<21> */
#define EBP10_SCSI_PCI_SLOT 1	/* PCI AD<16> on 1st pass EBP10 */
#define EBP10_SIO_PCI_SLOT  2  /* PCI AD<17> on 1st pass EBP10 */
#define EBP10_PCI_OPTION_1 6  /* PCI AD<17> on 1st pass EBP10 */
#define EBP10_PCI_OPTION_2 7  /* PCI AD<18> on 1st pass EBP10 */
#define EBP10_PCI_OPTION_3 8

#else				/* NEW ID-SEL SCHEME */
/*    Now the slot number matches with Avanti & Mustang II*/
#define EBP10_MIN_PCI_SLOT 5	 /* PCI AD<??> */
#define EBP10_MAX_PCI_SLOT 15  /* PCI AD<??> */
#define EBP10_SCSI_PCI_SLOT 6	/* PCI AD<17> on  EBP10 */
#define EBP10_SIO_PCI_SLOT  7 /* PCI AD<18> on  EBP10 */
#define EBP10_PCI_OPTION_1 11  /* PCI AD<22> on  EBP10 */
#define EBP10_PCI_OPTION_2 12 /* PCI AD<23> on  EBP10 */
#define EBP10_PCI_OPTION_3 13  /* PCI AD<24> on  EBP10 */
#define EBP10_PCI_OPTION_3_HACK 8 /* PCI AD<19> on  EBP10 */
#endif

/* defines for new pci scheme (begins with new tulip riser) */
/* This scheme was used for EBP10 Pass 1 */
#define	PCI_VEC_SCSI	0x900
#define	PCI_VEC_TULIP	0x910
#define	PCI_VEC_SLOT0_A	0x920
#define	PCI_VEC_SLOT0_B	0x930
#define	PCI_VEC_SLOT0_C	0x940
#define	PCI_VEC_SLOT0_D	0x950
#define	PCI_VEC_SLOT1_A	0x960
#define	PCI_VEC_SLOT1_B	0x970
#define	PCI_VEC_SLOT1_C	0x980
#define	PCI_VEC_SLOT1_D	0x990

/* PCI interrupt control address */
#define	PCI_INTR_MASK_REG	0x26

#define MAX_CENTRAL_INTR	28
#define TABLE_FULL	-1


#define	IS_AN_ISA_DEVICE(a)	((a)->bus_hd->bus_type == BUS_ISA)

/*---------------------------------------------------------------------*/

/* This should go in sio.h file */

#define SIO_CNFG_REV    0x8
#define SIO_PIRQ0	0x60
#define SIO_PIRQ1	0x61
#define SIO_PIRQ2	0x62
#define SIO_PIRQ3	0x63
#define SIO_ROUTE_ENABLE 0x80
#define SIO_PIRQ_MASK   0xf

/* SCSI Offset 800L   SIO offset 1000L    */
/*     slot 1 800L	slot 2 1000L      */

#define EBP10_SIO_CNFG_OFFSET \
     (LCA_PCI_CONFIG_FLAG | ( EBP10_SIO_PCI_SLOT << PCI_CNFG_DEV_SHIFT)) 
#define EBP10_SIO_CNFG_READ_BUS_D8(a)  \
         read_io_port((EBP10_SIO_CNFG_OFFSET | a), 1, 0)
#define EBP10_SIO_CNFG_READ_BUS_D16(a)  \
         read_io_port((EBP10_SIO_CNFG_OFFSET | a), 2, 0)

#define EBP10_SCSI_CNFG_OFFSET \
     (LCA_PCI_CONFIG_FLAG | ( EBP10_SCSI_PCI_SLOT << PCI_CNFG_DEV_SHIFT))
#define EBP10_SCSI_CNFG_READ_BUS_D8(a)  \
         read_io_port((EBP10_SCSI_CNFG_OFFSET | a), 1, 0)
#define EBP10_SCSI_CNFG_READ_BUS_D16(a)  \
         read_io_port((EBP10_SCSI_CNFG_OFFSET | a), 2, 0)
/*---------------------------------------------------------------------*/

#endif	/* _ARCH_ALPHA_HAL_EBP10_H */
