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
 * @(#)$RCSfile: eb66.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1995/06/19 12:32:54 $
 */
#ifndef	_ARCH_ALPHA_HAL_EB66_H
#define	_ARCH_ALPHA_HAL_EB66_H

#define IOA_OKAY	0
#define	IOA_ERROR	-1

/*
 * EB66 SYSTEM ADDRESS MAP
 *
 * The 34-bit processor physical address space is mapped into memory 
 * and I/O space addresses as follows:
 *
 *   0 0000 0000 +--------------------------------+
 *               |     Cacheable Memory Space     |  0.5 GB
 *   0 2000 0000 +--------------------------------+
 *               |   Non-Cacheable Memory Space   |  0.5 GB
 *   0 4000 0000 +--------------------------------+
 *               |   Non-Existent Memory Space    |  3.0 GB 
 *   1 0000 0000 +--------------------------------+
 *               |      Graphics Memory Space     |  0.5 GB
 *   1 2000 0000 +--------------------------------+
 *               |  Memory Controller CSR Space   |  1.5 GB
 *   1 8000 0000 +--------------------------------+
 *               |    I/O Controller CSR Space    |  0.5 GB
 *   1 A000 0000 +--------------------------------+
 *               |   PCI Interrupt Acknowledge    |
 *               |          Special Cycle         |  0.5 GB
 *               |             Space              |
 *   1 C000 0000 +--------------------------------+
 *               |      PCI Sparse I/O Space      |  0.5 GB
 *   1 E000 0000 +--------------------------------+
 *               |    PCI Configuration Space     |  0.5 GB
 *   2 0000 0000 +--------------------------------+
 *               |    PCI Sparse Memory Space     |  4.0 GB
 *   3 0000 0000 +--------------------------------+
 *               |     PCI Dense Memory Space     |  4.0 GB
 *   3 FFFF FFFF +--------------------------------+
 *
 * The following constants are defined in lca.h and are included 
 * here for completeness:
 *
 * #define P2_BUSIO_BASE		0x1c0000000
 * #define LCA_PCI_CONFIG_BASE		0x1e0000000
 * #define BUSMEM_SPARSE_BASE		0x200000000
 * #define BUSMEM_DENSE_BASE		0x300000000
 *
 * Alpha I/O Architecture standard address swizzle:
 *
 * #define IO_SHIFT	(5)
 * #define IO_STRIDE	(0x80)
 * #define ALIGN_MASK	(0xffffffffffffff9f)
 * #define WIDTH_MASK	(0x18)
 * #define WIDTH_SHIFT	(IO_SHIFT - 2)
 * #define Wrd       	((long)1 << (WIDTH_SHIFT))
 * #define Tri		((long)2 << (WIDTH_SHIFT))
 * #define Lng       	((long)3 << (WIDTH_SHIFT))
 * #define Quad		((long)0 << (WIDTH_SHIFT))
 *
 */

#define	IS_AN_ISA_DEVICE(a)	(strcmp((a)->bus_name, "isa") == 0)

/*
 * EB66 BUS-RELATED DEFINITIONS
 *
 * The following constants define the mapping between PCI "slot"
 * number and the corresponding PCI address bit that drives the
 * device IDSEL pin.
 *
 */

#define	EB66_MIN_SLOT		0	/* PCI_AD<11> */
#define EB66_MAX_SLOT		12	/* PCI_AD<23> */

/*
 * EB66 IRQ & SCB DEFINITIONS
 *
 * The following constants define the SCB assignments for all ISA device 
 * interrupts.  Because EB66 uses a standard ISA IRQ to SCB mapping, the 
 * irq_to_scb_vector mapping provided in 82357_pic.h and 82357_pic.c is 
 * used.
 *
 * These definitions are included here for completeness.
 *
 * #define PIC_SCB_IRQ0		0x800	Intel 82C54 Interval Timer
 * #define PIC_SCB_IRQ1		0x810	Intel 8242 Keyboard controller
 * #define PIC_SCB_IRQ2		0x820	Chains interrupt from slave controller
 * #define PIC_SCB_IRQ3		0x830	National PC87312 serial port COM2
 * #define PIC_SCB_IRQ4		0x840	National PC87312 serial port COM1
 * #define PIC_SCB_IRQ5		0x850	National PC87312 parallel port (or IRQ7)
 * #define PIC_SCB_IRQ6		0x860	National PC87312 floppy disk controller
 * #define PIC_SCB_IRQ7		0x870	National PC87312 parallel port (or IRQ5)
 * #define PIC_SCB_IRQ8 	0x880   Unused 
 * #define PIC_SCB_IRQ9		0x890	ISA expansion connector
 * #define PIC_SCB_IRQ10	0x8A0   ISA expansion connector
 * #define PIC_SCB_IRQ11	0x8B0	ISA expansion connector
 * #define PIC_SCB_IRQ12	0x8C0	Intel 8242 Mouse controller
 * #define PIC_SCB_IRQ13	0x8D0	Unused 
 * #define PIC_SCB_IRQ14	0x8E0	ISA expansion connector
 * #define PIC_SCB_IRQ15	0x8F0   ISA expansion connector
 *
 *
 * The following constants define the SCB assignments for all PCI
 * device interrupts:
 *
 * On EB66
 *
 * #define PCI_SCB_J34_A	0x900	PCI expansion connector 0 INTA
 * #define PCI_SCB_J33_A	0x910	PCI expansion connector 1 INTA
 * #define PCI_SCB_J34_B	0x920	PCI expansion connector 0 INTB
 * #define PCI_SCB_J33_B	0x930	PCI expansion connector 1 INTB
 * #define PCI_SCB_J34_C	0x940	PCI expansion connector 0 INTC
 * #define PCI_SCB_ETHER	0x960	DECchip 21040 Ethernet LAN controller
 * #define PCI_SCB_SCSI		0x970	NCR 53C810 SCSI controller
 * #define PCI_SCB_J33_C	0x980	PCI expansion connector 1 INTC
 * #define PCI_SCB_J34_D	0x990	PCI expansion connector 0 INTD
 * #define PCI_SCB_J33_D	0x9A0	PCI expansion connector 1 INTD
 *
 */

#endif	/* _ARCH_ALPHA_HAL_EB66_H */
