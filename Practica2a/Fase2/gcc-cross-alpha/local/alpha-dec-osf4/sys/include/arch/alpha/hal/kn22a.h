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
 * @(#)$RCSfile: kn22a.h,v $ $Revision: 1.1.22.2 $ (DEC) $Date: 1997/12/01 21:08:46 $
 */
#ifndef	_ARCH_ALPHA_HAL_MIKASA_H
#define	_ARCH_ALPHA_HAL_MIKASA_H

/************************/
/* Mikasa Platform CSRs */
/************************/
#define	KN22A_PCI_IR	        0x534	/* PCI Interrupt Register.	*/
#define	KN22A_PCI_IMR	        0x536	/* PCI Interrupt Mask Register. */

/**************************/
/* Noritake Platform CSRs */
/**************************/
#define KN22A_PCI_IR1          0x542 /*PCI Interrupt Register 1   */
#define KN22A_PCI_IR2          0x544 /*PCI Interrupt Register 2   */
#define KN22A_PCI_IR3          0x546 /*PCI Interrupt Register 3   */
#define KN22A_PCI_IMR1         0x54a /*PCI Interrupt Mask Register 1 */
#define KN22A_PCI_IMR2         0x54c /*PCI Interrupt Mask Register 2 */
#define KN22A_PCI_IMR3         0x54e /*PCI Interrupt Mask Register 3 */

/************************/
/* Common Platform CSRs */
/************************/
#define	KN22A_SRV_MGT_R	        0x532	/* Server Management Register.	*/

/**********************/
/* Noritake Mask Bits */
/**********************/
#define KN22A_PCI_SUM_IMR1     0x1
#define KN22A_PCI_SUM_IMR2     0x3

/************************/
/* Mikasa/Noritake IRQs */
/************************/
#define KN22A_KEYB_IRQ           1
#define KN22A_COM2_IRQ           3
#define KN22A_COM1_IRQ           4
#define KN22A_FLOPPY_IRQ         6
#define KN22A_LPT_IRQ            7
#define KN22A_MOUSE_IRQ         12

/***************************/
/* Mikasa/Noritake Vectors */
/***************************/
#define KN22A_VECTOR_PROC_CORR  0x630
#define KN22A_VECTOR_SYS_CORR   0x620

/*****************************/
/* Mikasa/Noritake Constants */
/*****************************/
#define	KN22A_MIN_PCI_SLOT	 0
#define	KN22A_MAX_PCI_SLOT	20
#define KN22A_HIGH_TEMP_THRESH  45

/**************************************************************************/
/* Interrupt Dispatch declarations. 					  */
/* Central dispatch table is a table of interrupt information structures. */
/* Each table entry contains the interrupt information for an IO device.  */
/* Registration consists of finding the first available slot in the table,*/
/* loading the device's data into the table, and returning the table      */
/* index as a handle.							  */
/*                                                                        */
/**************************************************************************/
#define	TABLE_FULL	-1
#define KN22A_MAX_CENTRAL_INTR	64	/* PCI 48, EISA 16. Increased for
					   Noritake */

/*********************/
/* Macro Definitions */
/*********************/
#define	KN22A_PCI_IRQ_TO_SCB(irq)	(0x900 | (irq)<<4)
#define KN22AB_PCI_IRQ_TO_SCB(irq)      ((0x900 | (irq)<<4) - 0x10)
#define	IS_AN_EISA_DEVICE(a)		(a->bus_hd->bus_type == BUS_EISA) 

/*
 * define a new header for correctable error frames.  This is just like
 * the old common error header (bytecount, flags, sys- and proc-offsets,
 * but this goes 64 bits further, to include the machine check error code,
 * too.  Current code tries to get this from paltemp[0], but there are no
 * paltemp registers included in the much smaller correctable error frame.
 */
  /*
   * Define the structure for the first three quadwords of info coming
   * in from the firmware.  That's all we really care about here. The
   * noritake/mikasa firmware uses same CRD error structure as the sable,
   * so the struct_el_kn450_data_corrected structure definition for works
   * for code that may wish to examine the details of the error.
   */
  typedef struct _kn22a_crd_err_hdr {
	u_int ByteCount;			/* bits [0..31], 1st quadword */
	u_int Flags;				/* bits [32..63], 1st quadword */
	u_int ProcOffset;			/* bits [0..31], 2nd quadword */
	u_int SysOffset;			/* bits [32.63], 2nd quadword */
	u_int MachineCheckCode;		/* bits [0..31], 3rd quadword */
	u_int MoreFlags;			/* bits [32..63], 3rd quadword */
  } KN22A_CRD_ERR_HDR, *pKN22A_CRD_ERR_HDR;

#endif	/* _ARCH_ALPHA_HAL_MIKASA_H */
