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
 * @(#)$RCSfile: kn20aa.h,v $ $Revision: 1.1.18.2 $ (DEC) $Date: 1998/04/08 21:31:26 $
 */
#ifndef KN20AA_H
#define KN20AA_H

#include <sys/types.h>



#define NMI_ST_CTRL		0x61
#define TMR1_CTR2		0x42
#define TMR1_CMR		0x43

#define	IS_AN_EISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_EISA) 



/*************************************************************************
 **************** KN20AA PCI and (E)ISA i/o map. ************************
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
#define CPU_EISA_SLOT7_CPUADDR  0x85800e0000L   /* EISA slot7   28-32KB */
#define CPU_EISA_SLOT8_CPUADDR  0x8580100000L   /* EISA slot8   32-36KB */
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
#define PCI_EISA_SLOT7_PCIADDR  0x00007000L     /* EISA slot7   28-32KB */
#define PCI_EISA_SLOT8_PCIADDR  0x00008000L     /* EISA slot8   32-36KB */
#define PCI_PCI_IO_AREA		0x00010000L

/*************************************************************************
 *************************** Flash ROM Space *****************************
 *************************************************************************
 */
#define CIA_INT_REQ	(FLASH_ROM+0x0000L)	/* Interrupt Request Register 	*/
#define CIA_INT_MASK	(FLASH_ROM+0x0040L)	/* Interrupt Mask Register	*/
#define CIA_INT_EDGE	(FLASH_ROM+0x0080L)	/* Interrupt Level/edge select	*/
#define CIA_INT_HILO	(FLASH_ROM+0x00c0L)	/* Interrupt High/low irq select*/
#define CIA_INT_CLR	(FLASH_ROM+0x0100L)	/* Interrupt Clear Register	*/
#define CACHE_CNFG	(FLASH_ROM+0x0200L)	/* Cache & Memory Config. Reg	*/
#define SCR0		(FLASH_ROM+0x0300L)	/* SET Config Register		*/
#define SCR1		(FLASH_ROM+0x0340L)	/* SET Config Register		*/
#define SCR2		(FLASH_ROM+0x0380L)	/* SET Config Register		*/
#define SCR3		(FLASH_ROM+0x03c0L)	/* SET Config Register		*/
#define SCR4		(FLASH_ROM+0x0400L)	/* SET Config Register		*/
#define SCR5		(FLASH_ROM+0x0440L)	/* SET Config Register		*/
#define SCR6		(FLASH_ROM+0x0480L)	/* SET Config Register		*/
#define SCR7		(FLASH_ROM+0x04c0L)	/* SET Config Register		*/
#define CIA_RESET	(FLASH_ROM+0x0900L)	/* Force System Reset		*/


/*
 * ELCR1 maps up to irq 11
 * ELCR2 maps eisa_irq 12 14 15
 *
 *  setting  bit makes it level sensitive
 *  clearing bit makes it edge sensitive
 */
#define ELCR1	0x26
#define ELCR2	0x27

#define WRITE_ELCR1( x )	WRITE_BUS_D8(PCI_ADDR_TO_HANDL(ELCR1), (x) )
#define WRITE_ELCR2( x )	WRITE_BUS_D8(PCI_ADDR_TO_HANDL(ELCR2), (x) )

#define READ_ELCR1		READ_BUS_D8(PCI_ADDR_TO_HANDL(ELCR1))
#define READ_ELCR2		READ_BUS_D8(PCI_ADDR_TO_HANDL(ELCR2))

#define MAX_SLOT 32

/*
#define DMA_DEBUG 1    
#define SG_DMA_DEBUG 1 
*/

/*
 *      This data structure is used to support central interrupt dispatch
 *      PCI_INTER_INFO_SIZE is set to 32 to cover Noritake/Pinnacle, which
 *      has the greatest number of PCI slots/loads (7 expansion slots plus
 *      the on-board Qlogic ISP1020A SCSI chip).  Alcor and Mikasa/Pinnacle
 *      will not utilize all the entries because they have less PCI
 *      slots/loads.
 */
#define EISA_INTER_INFO_SIZE    16
#define PCI_INTER_INFO_SIZE     32
#define GRU_INTER_INFO_SIZE     20

#endif /* KN20AA_H */


