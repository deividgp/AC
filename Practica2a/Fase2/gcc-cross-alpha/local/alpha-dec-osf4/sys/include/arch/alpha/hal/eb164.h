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
 * @(#)$RCSfile: eb164.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1998/04/08 21:29:58 $
 */
#ifndef EB164_H
#define EB164_H

#include <sys/types.h>



#define NMI_ST_CTRL		0x61
#define TMR1_CTR2		0x42
#define TMR1_CMR		0x43

#define	IS_AN_EISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_EISA) 



/*************************************************************************
 **************** EB164 PCI and (E)ISA i/o map. ************************
 *************************************************************************
 */
#define CPU_EISA_SLOT0_CPUADDR	0x8580000000L	/* EISA system board 
						   (X-bus,IO ports,etc)
						   0-4KB		*/
#define CPU_EISA_SLOT1_CPUADDR	0x8580020000L	/* EISA slot1	4-8KB	*/
#define CPU_EISA_SLOT2_CPUADDR	0x8580040000L	/* EISA slot2	8-12KB	*/
#define CPU_EISA_SLOT3_CPUADDR	0x8580060000L	/* EISA slot3	12-16KB	*/
#define CPU_EISA_SLOT4_CPUADDR	0x8580080000L	/* EISA slot4	16-20KB	*/
#define CPU_EISA_SLOT5_CPUADDR	0x85800a0000L	/* EISA slot5	20-24KB	*/
#define CPU_EISA_SLOT6_CPUADDR	0x85800c0000L	/* EISA slot6	24-28KB */
#define CPU_PCI_IO_AREA		0x8580200000L

#define PCI_EISA_SLOT0_PCIADDR	0x00000000L	/* EISA system board 
						   (X-bus,IO ports,etc)
						   0-4KB		*/
#define PCI_EISA_SLOT1_PCIADDR	0x00001000L	/* EISA slot1	4-8KB	*/
#define PCI_EISA_SLOT2_PCIADDR	0x00002000L	/* EISA slot2	8-12KB	*/
#define PCI_EISA_SLOT3_PCIADDR	0x00003000L	/* EISA slot3	12-16KB	*/
#define PCI_EISA_SLOT4_PCIADDR	0x00004000L	/* EISA slot4	16-20KB	*/
#define PCI_EISA_SLOT5_PCIADDR	0x00005000L	/* EISA slot5	20-24KB	*/
#define PCI_EISA_SLOT6_PCIADDR	0x00006000L	/* EISA slot6	24-28KB */
#define PCI_PCI_IO_AREA		0x00010000L


#define MAX_SLOT 32

/*
#define DMA_DEBUG 1    
#define SG_DMA_DEBUG 1 
*/

/*
 *	This data structure is used to support central interrupt dispatch
 */
#define EISA_INTER_INFO_SIZE	16
#define PCI_INTER_INFO_SIZE	24

#endif /* EB164_H */


