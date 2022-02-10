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
 * @(#)$RCSfile: cbus2_pci.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1997/11/12 18:03:42 $
 */

#ifndef CBUS2_PCI_H
#define CBUS2_PCI_H

#include <sys/types.h>
#include <hal/cpuconf.h>

/*
 * Cbus2_pci HWRPB Configuration Data Block
 *
 * This is defined and filled in by the system's console.
 *
 * KMBL TODO - get definition from hcb when available
 */
struct rpb_config {
	u_long size;
	u_long chk_sum;
 
	/******* Cbus2 Specific *******/
};

/*
 * CBUS2 CSR PHYSICAL ADDRESSES
 *
 * Each node's I/O registers on the CBus all fit within one 8k page.
 *
 * Memory on the CBus version 2  is laid out as follows:
 *
 *
 *  0 0000 0000 +---------------------------------+
 *              | Physical Memory     2GB         |
 *  0 8000 0000 +---------------------------------+
 *              | Reserved Memory     2GB         |
 *  1 0000 0000 +---------------------------------+
 *              | CPU[0,1,2,3]        2GB         |
 *		| Allocate Invalidate             |
 *  1 8000 0000 +---------------------------------+
 *              | PCI 1 Dense Memory Space  2GB   |
 *  1 c000 0000 +---------------------------------+
 *              | PCI 1 Sparse IO  Space 256MB    |
 *  2 0000 0000 +---------------------------------+
 *		| PCI 0 Sparse Memory Space 4GB   |
 *  3 0000 0000 +---------------------------------+
 *              | PCI 1  Sparse Memory Space 2GB  |
 *  3 8000 0000 +---------------------------------+
 *              | Primary I/O 2GB (expanded below)|
 *  3 9000 0000 +---------------------------------+
 *              | PCI 0 Config Space 128MB        |
 *  3 9800 0000 +---------------------------------+
 *              | PCI 1 Config Space 128MB        |
 *  3 a000 0000 +---------------------------------+
 *              | PCI 0 Sparse IO  Space 256MB    |
 *  3 c000 0000 +---------------------------------+
 *              | PCI 0 Dense Memory Space  1GB   |
 *  4 0000 0000 +---------------------------------+
 */
/*
 * The SABLE_GAMMA_SYSTEM_BASE is used because the address map
 * for GAMMA differs by a constant from SABLES's
 */


#define PCI1_DENSE_MEM_BASE	(0x180000000L + SABLE_GAMMA_SYSTEM_BASE)
#define PCI1_SPARSE_IO_BASE	(0x1c0000000L + SABLE_GAMMA_SYSTEM_BASE)

#define PCI0_SPARSE_MEM_BASE	(0x200000000L + SABLE_GAMMA_SYSTEM_BASE)
#define PCI1_SPARSE_MEM_BASE	(0x300000000L + SABLE_GAMMA_SYSTEM_BASE)

#define PCI0_CONFIG_BASE	(0x390000000L + SABLE_GAMMA_SYSTEM_BASE)

#define PCI1_CONFIG_BASE	(0x398000000L + SABLE_GAMMA_SYSTEM_BASE)

#define PCI0_SPARSE_IO_BASE	(0x3a0000000L + SABLE_GAMMA_SYSTEM_BASE)

#define PCI0_DENSE_MEM_BASE	(0x3c0000000L + SABLE_GAMMA_SYSTEM_BASE)

#define IO_BASE		        (0x180000000L + SABLE_GAMMA_SYSTEM_BASE)

#define PCI0_BASE	        (0x38e000000L)
#define PCI1_BASE	        (0x38f000000L)

/*  Cobra-bus2 CSRs are in the non-cachable primary IO space from 3.8000.0000 to 3.8fff.ffff
 *
 *  +--------------+ 3 8000 0000
 *  | CPU 0 CSRs   |            
 *  +--------------+ 3 8100 0000
 *  | CPU 1 CSRs   |            
 *  +--------------+ 3 8200 0000
 *  | CPU 2 CSRs   |            
 *  +--------------+ 3 8300 0000
 *  | CPU 3 CSRs   |            
 *  +--------------+ 3 8400 0000
 *  | CPU Reserved |            
 *  +--------------+ 3 8700 0000
 *  | Mem Reserved |            
 *  +--------------+ 3 8800 0000
 *  | Mem 0 CSRs   |            
 *  +--------------+ 3 8900 0000
 *  | Mem 1 CSRs   |            
 *  +--------------+ 3 8a00 0000
 *  | Mem 2 CSRs   |            
 *  +--------------+ 3 8b00 0000
 *  | Mem 3 CSRs   |            
 *  +--------------+ 3 8c00 0000           
 *  | Mem Reserved |            
 *  +--------------+ 3 8e00 0000           
 *  | PCI Bridge   |            
 *  +--------------+ 3 8f00 0000           
 *  | Expansion IO |            
 *  +--------------+ 3 9000 0000           
 *                                              
 *
 */
#define CPU0_BASE		0x380000000L
#define CPU1_BASE		0x381000000L
#define CPU2_BASE		0x382000000L
#define CPU3_BASE		0x383000000L
#define MEM0_BASE		0x388000000L
#define MEM1_BASE		0x389000000L
#define MEM2_BASE		0x38a000000L
#define MEM3_BASE		0x38b000000L

#define CBUS2_PCI_MEM_STRIDE	0x010000000L


/* Cbus2 memory is dievided into four quadrants: Q0, Q1, Q2, 
 * and Q3. Quadrant 0 is cached.  All the other quadrants 
 * are uncached
 */

/* Quadrant 0 - Cacheable memory */
#define	MEMORY_BASE		0x0
#define MEMORY_EXTENSION	0x010000000

/* Quadrant 1 - Mixed Bag: External I/O, Local address space (regs) */
#define	CBUS2_PCI_BUSIO_BASE	PCI0_SPARSE_IO_BASE
#define CBUS2_PCI_BUSIO_MASK	0x1ffffff 		/* 256M ? cbus2 24 bits
							 * or is is 23?
							 */

/* Quadrant 2 - PCI 0 Sparse Memory Space - External memory - Jensen swizzle */
#define	CBUS2_PCI_BUSMEM_BASE	PCI0_SPARSE_MEM_BASE
#define CBUS2_PCI_BUSMEM_MASK	0x7ffffff 		/* 128M ? 
							 * cbus2 23 bits
							 * or is it 28
							 */

/* Quadrant 3 - PCI 1 Sparse, CBUS CSRs, PCI0&1 Configuration Space
 * PCI0 Sparse (8MB) PCI1 Sparse (8MB) PCI0 Dense (1GB) */
#define	CBUS2_PCI_BUSMEM_LINEAR_BASE	PCI0_DENSE_MEM_BASE

/* Sysmap definitions/defines */
#define CBUS2_PCI_SYSMAP_MASK	0xFFFFFFFF00000000L	/* Upper 32-bits */
#define CBUS2_PCI_SYSMAP_SHIFT	8

/* Some other pci stuff */
#define CBUS2_PCI_PCI_MAX_SLOT 9
#define CBUS2_PCI_PCI_MIN_SLOT 0

/*
 * DMA Support
 */
#define	IS_A_SG_DEVICE(a,f)	(IS_A_FLOPPY_DEVICE(a) || IS_A_CONTIG_DEVICE(f) || cbus2_pci_always_sg)

#define BIT31			0x80000000
#define DMA_FORCE_CONTIG	DMA_RSVD_4000

#define	IS_A_FLOPPY_DEVICE(a)	(strcmp(a->ctlr_name, "fdi") == 0)
#define	IS_AN_EISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_EISA) 

#define	ADDRESS_LIMITED(f)	(f & DMA_ADDR_LIMIT)
#define FORCE_CONTIG(f)		(f & DMA_FORCE_CONTIG)
#define CONTIG_DESIRED(f)       (f & DMA_CONTIG)
#define SG_ALLOCED(f)		(f & DMA_HW_SG)

#define SG_NOTNEEDED	0
#define SG_REQUIRED	1
#define SG_DESIRED	2

#define SG_MAP_BASE_DEVICE(f, BUSP)   (ADDRESS_LIMITED(f) ? \
		(vm_offset_t)(BUSP->private[4]) : \
		(vm_offset_t)(BUSP->private[5]))

#define	CROSSES_PAGE_BOUNDARY(a,c)	((((a) & page_mask) + (c)) > page_size)
#define IS_PEER_TO_PEER(a)		((a) & BIT31)
#define PEER_TO_PEER_DMA_BASE		(0L)


/*
 * TO DO: Add direct mapped pci address translation
 */


/* IO Interrupts on CBUS2
 *
 * The four interrupt lines from each PCI slot have been ORed together.  
 * The interrupt logic sees one interrupt form each PCI slot.
 * The EISA interrupts, keyboard, mouse, serial and Parallel ports, 
 * floppy and IIC interrupts are all brought into the interrupt
 * logic.
 *
 * Cbus2 interrupts will be handled by an ICIC chip in a level triggered mode.  
 * The hardware will be located on the Standard IO Module.  Firmware 
 * support is required for acknowledge and end of interrupt (EOI) 
 * handling.  There is one master and three slave 8259s.
 *
 *
 *	SLAVE 0	(536, 537)
 *	800 pci slot0
 *	810 scsi port
 * 	820 ethernet port
 * 	830 mouse
 *	840 pci slot 1
 *	850 pci slot 2
 *	860 keyboard
 *	870 floppy (eisa irq 0)
 *
 *	SLAVE 1 (53a, 53b)				MASTER (534, 535)
 *	880 serial port 1 (eisa irq 1)			reserved
 *	890 parallel port 1 (eisa irq 2)		slave 0
 *	8a0 eisa irq 3					reserved
 *	8b0 eisa irq 4					slave 1
 *	8c0 eisa irq 5					slave 2
 *	8d0 eisa irq 6					reserved
 *	8e0 eisa irq 7					reserved
 *	8f0 serial port 0   (eisa irq 8)		nc (passive release)
 *
 *	SLAVE 2 (53c, 53d)
 *	900 eisa irq 9
 *	910 eisa irq 10
 *	920 eisa irq 11
 *	930 eisa irq 12
 *	940 eisa irq 13
 *	950 eisa irq 14
 * 	960 nc
 *	970 iic
 *
 * The routines are handled with two levels here.  
 *	First is the routine for all of Cbus2.  
 *	Next is the eisa routine. It maps the eisa irq level to the cbus2 irq level.
 *	Finally, the pic routine maps the pci irq (slot) to the cbus2 irq level.
 */    
#define T2_PCISLOT0_STDIO_IRQ	0
#define T2_PSIOP_STDIO_IRQ  	1	    
#define T2_ETHE_STDIO_IRQ	2
#define T2_PCISLOT1_STDIO_IRQ	4
#define T2_PCISLOT2_STDIO_IRQ	5

#define CBUS2_PCI_MOUS_STDIO_IRQ	3
#define CBUS2_PCI_KEYB_STDIO_IRQ	6
#define CBUS2_PCI_EISA0_STDIO_IRQ	7
 
#define CBUS2_PCI_EISA1_STDIO_IRQ	8
#define CBUS2_PCI_EISA2_STDIO_IRQ	9
#define CBUS2_PCI_EISA3_STDIO_IRQ	10
#define CBUS2_PCI_EISA4_STDIO_IRQ	11
#define CBUS2_PCI_EISA5_STDIO_IRQ	12
#define CBUS2_PCI_EISA6_STDIO_IRQ	13
#define CBUS2_PCI_EISA7_STDIO_IRQ	14
#define CBUS2_PCI_EISA8_STDIO_IRQ	15

#define CBUS2_PCI_EISA9_STDIO_IRQ	16
#define CBUS2_PCI_EISA10_STDIO_IRQ	17
#define CBUS2_PCI_EISA11_STDIO_IRQ	18
#define CBUS2_PCI_EISA12_STDIO_IRQ	19
#define CBUS2_PCI_EISA13_STDIO_IRQ	20	/* not connected */
#define CBUS2_PCI_EISA14_STDIO_IRQ	21
#define CBUS2_PCI_EISA15_STDIO_IRQ	22
#define CBUS2_PCI_IIC_STDIO_IRQ	23

#define CBUS2_PCI_FLOPPY_EISA_IRQ	0
#define CBUS2_PCI_COMMA_EISA_IRQ	8
#define CBUS2_PCI_PARLEL_EISA_IRQ	2
#define CBUS2_PCI_COMMB_EISA_IRQ	1

#define CBUS2_PCI_FLOPPY_STDIO_IRQ	7
#define CBUS2_PCI_COMMA_STDIO_IRQ	15
#define CBUS2_PCI_PARLEL_STDIO_IRQ	9
#define CBUS2_PCI_COMMB_STDIO_IRQ	8

#define	CBUS2_PCI_PCI0_ADDR_TO_HANDL(x)	((x) | (PCI0_SPARSE_IO_BASE << CBUS2_PCI_SYSMAP_SHIFT))
#define	CBUS2_PCI_PCI1_ADDR_TO_HANDL(x)	((x) | (PCI1_SPARSE_IO_BASE << CBUS2_PCI_SYSMAP_SHIFT))

#define	CTRL1_MASK	0x21
#define	CTRL2_MASK	0xa1

#define MASTER_INT_CTRL		0x534
#define MASTER_INT_MASK		0x535
#define SLAVE0_INT_CTRL		0x536
#define SLAVE0_INT_MASK		0x537
#define SLAVE1_INT_CTRL		0x53a
#define SLAVE1_INT_MASK		0x53b
#define SLAVE2_INT_CTRL		0x53c
#define SLAVE2_INT_MASK		0x53d
#define SLAVE3_INT_CTRL		0x53e
#define SLAVE3_INT_MASK		0x53f


#define READ_PCI0_SLAVE0_MASK	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE0_INT_MASK))
#define WRITE_PCI0_SLAVE0_MASK(x)	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE0_INT_MASK), (x) ) 
#define READ_PCI0_SLAVE0_CTRL	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE0_INT_CTRL))
#define WRITE_PCI0_SLAVE0_CTRL(x) 	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE0_INT_CTRL), (x) ) 

#define READ_PCI0_SLAVE1_MASK	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE1_INT_MASK)) 
#define WRITE_PCI0_SLAVE1_MASK(x)	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL( SLAVE1_INT_MASK), (x) )
#define READ_PCI0_SLAVE1_CTRL	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE1_INT_CTRL)) 
#define WRITE_PCI0_SLAVE1_CTRL(x) 	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE1_INT_CTRL), (x) )

#define READ_PCI0_SLAVE2_MASK	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE2_INT_MASK)) 
#define WRITE_PCI0_SLAVE2_MASK(x)	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE2_INT_MASK), (x) )
#define READ_PCI0_SLAVE2_CTRL	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE2_INT_CTRL)) 
#define WRITE_PCI0_SLAVE2_CTRL(x) 	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE2_INT_CTRL), (x) )

#define READ_PCI0_SLAVE3_MASK	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE3_INT_MASK)) 
#define WRITE_PCI0_SLAVE3_MASK(x)	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE3_INT_MASK), (x) )
#define READ_PCI0_SLAVE3_CTRL	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE3_INT_CTRL)) 
#define WRITE_PCI0_SLAVE3_CTRL(x) 	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(SLAVE3_INT_CTRL), (x) )

#define READ_PCI0_MASTER_MASK	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(MASTER_INT_MASK))
#define WRITE_PCI0_MASTER_MASK(x)	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(MASTER_INT_MASK), (x) )
#define READ_PCI0_MASTER_CTRL	READ_BUS_D8( CBUS2_PCI_PCI0_ADDR_TO_HANDL(MASTER_INT_CTRL))
#define WRITE_PCI0_MASTER_CTRL(x) 	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(MASTER_INT_CTRL), (x) )

/*
 * ELCR1 maps up to irq 11
 * ELCR2 maps eisa_irq 12 14 15
 *
 *  setting  bit makes it level sensitive
 *  clearing bit makes it edge sensitive
 */
#define CBUS2_PCI_ELCR1	0x26
#define CBUS2_PCI_ELCR2	0x27

#define WRITE_PCI0_CBUS2_PCI_ELCR1( x )	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(CBUS2_PCI_ELCR1), (x) )
#define WRITE_PCI0_CBUS2_PCI_ELCR2( x )	WRITE_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(CBUS2_PCI_ELCR2), (x) )

#define READ_PCI0_CBUS2_PCI_ELCR1	READ_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(CBUS2_PCI_ELCR1))
#define READ_PCI0_CBUS2_PCI_ELCR2	READ_BUS_D8(CBUS2_PCI_PCI0_ADDR_TO_HANDL(CBUS2_PCI_ELCR2))


#define CBUS2_PCI_EISA_IRQ_TO_STDIO_IRQ( x )	((x) + 7)
#define CBUS2_PCI_STDIO_IRQ_TO_EISA_IRQ( x )	((x) - 7)
#define STDIO_PCI0_IRQ_TO_SCB_VECTOR( x )	(( ( x ) * 0x10) + 0x800)

/*
 * XIO PCI1 Definitions
 */

#define READ_PCI1_SLAVE0_MASK      READ_BUS_D8( CBUS2_PCI_PCI1_ADDR_TO_HANDL(SLAVE0_INT_MASK))
#define WRITE_PCI1_SLAVE0_MASK(x)  WRITE_BUS_D8(CBUS2_PCI_PCI1_ADDR_TO_HANDL(SLAVE0_INT_MASK), (x) ) 
#define READ_PCI1_SLAVE0_CTRL      READ_BUS_D8( CBUS2_PCI_PCI1_ADDR_TO_HANDL(SLAVE0_INT_CTRL))
#define WRITE_PCI1_SLAVE0_CTRL(x)  WRITE_BUS_D8(CBUS2_PCI_PCI1_ADDR_TO_HANDL(SLAVE0_INT_CTRL), (x) ) 

#define READ_PCI1_MASTER_MASK      READ_BUS_D8( CBUS2_PCI_PCI1_ADDR_TO_HANDL(MASTER_INT_MASK))
#define WRITE_PCI1_MASTER_MASK(x)  WRITE_BUS_D8(CBUS2_PCI_PCI1_ADDR_TO_HANDL(MASTER_INT_MASK), (x) )
#define READ_PCI1_MASTER_CTRL      READ_BUS_D8( CBUS2_PCI_PCI1_ADDR_TO_HANDL(MASTER_INT_CTRL))
#define WRITE_PCI1_MASTER_CTRL(x)  WRITE_BUS_D8(CBUS2_PCI_PCI1_ADDR_TO_HANDL(MASTER_INT_CTRL), (x) )

#define STDIO_PCI1_IRQ_TO_SCB_VECTOR( x )		(( ( x ) * 0x10) + 0xC00)
/*
 * End XIO Definitions
 */

/*
 * Max PCI interrupts possible for each PCI channel
 */

#define PCI0_INTR_COUNT 64
#define PCI1_INTR_COUNT 64

#define TABLE_FULL	-1	/* kmbl todo - check for more generic constant */

#if 0				/* Not used any more */

struct cbus2_pci_interrupt_info {
    int	(*intr)();		/* Interrupt routine for device */
    caddr_t param;		/* Parameters for the routine */
    int	irq_level;		/* cbus2 irq level */
    int int_pci_num;		/* Need to know which PCI it came from */
};
#endif


/* 
 * IO address swizzle for CBUS2 
 */

#define Wrd       ((long)1 << (CBUS2_PCI_IO_SHIFT-2))
#define Lng       ((long)3 << (CBUS2_PCI_IO_SHIFT-2))

#define IO_B(x) (CBUS2_PCI_BUSIO_BASE |       (((long)(x) & CBUS2_PCI_BUSIO_MASK) << CBUS2_PCI_IO_SHIFT))
#define IO_W(x) (CBUS2_PCI_BUSIO_BASE | Wrd | (((long)(x) & CBUS2_PCI_BUSIO_MASK) << CBUS2_PCI_IO_SHIFT))
#define IO_L(x)	(CBUS2_PCI_BUSIO_BASE | Lng | (((long)(x) & CBUS2_PCI_BUSIO_MASK) << CBUS2_PCI_IO_SHIFT))

#define MEM_B(x) (CBUS2_PCI_BUSMEM_BASE |       (((long)(x) & CBUS2_PCI_BUSMEM_MASK) << CBUS2_PCI_IO_SHIFT))
#define MEM_W(x) (CBUS2_PCI_BUSMEM_BASE | Wrd | (((long)(x) & CBUS2_PCI_BUSMEM_MASK) << CBUS2_PCI_IO_SHIFT))
#define MEM_L(x) (CBUS2_PCI_BUSMEM_BASE | Lng | (((long)(x) & CBUS2_PCI_BUSMEM_MASK) << CBUS2_PCI_IO_SHIFT))




/*
 * Cbus2 Internal Bus (CBus2) Configuration Information
 */

/*
 * Hard configuration information (maximum number of slots).  Cbus2
 * supports a maximum of 4 processors.  For uniprocessor compilation,
 * provide for one CPU.
 */
#define CBUS2_IO_SLOTS  	1
#define CBUS2_MEM_SLOTS 	4
#define CBUS2_MAX_CPU_SLOTS 	4
#define CBUS2_SLOTS		7

#define CBUS2_CPU_SLOTS 	CBUS2_MAX_CPU_SLOTS
#define cbus2_pci_cpuid() 		mfpr_whami()



/*
 * The global Cbus2_nodes is set up during system configuration to 
 * indicate which CBus2 nodes are populated with working hardware.
 *
 * The allowable slot configurations are:
 *
 * Slot Number |  1 or 2 CPUs |	3 CPUs	      |	4 CPUs 
 * -----------------------------------------------------
 *	1      | 	ExIO  |	CPU2	ExIO  |	CPU3
 *	2      | CPU0	CPU0  |	CPU0	CPU0  |	CPU0
 *	3      | CPU1	CPU1  |	CPU1	CPU1  |	CPU1
 *	4      | MEM0	MEM0  |	MEM0	-     |	-
 *	5      | MEM1	MEM1  |	MEM1	CPU2  |	CPU2
 *	6      | MEM2	MEM2  |	MEM2	MEM0  |	MEM0
 *	7      | MEM3	MEM3  |	MEM3	MEM1  |	MEM1
 *
 * ==> for the three cpu system, if there are > 2 mem modules,
 *     cpu2 is in slot 1, otherwise its in slot 5. For all
 *     other numbers of cpus, the cpu# locations are fixed.
 *
 * slot 1 has external IO, CPU2, CPU3, or empty
 * slot 2 has cpu0
 * slot 3 has cpu1 or empty
 * slot 4 has mem0 or empty
 * slot 5 has mem1 or cpu2 or empty
 * slot 6 has mem2 or mem0 or empty
 * slot 7 has mem3 or mem1 or empty
 *	
 * Cbus2_modules_alive - for now, do it like this, just have two
 * counters, one for cpus, one for memories.  If slot occupancy is
 * needed, is a KMBL todo later.
 *
 * Also, the expansion io module is ignored for now.
 */
extern u_short Cbus2_cpu_modules_alive;		/* declared in cbus2_data.c */
extern u_short Cbus2_mem_modules_alive;		/* declared in cbus2_data.c */

#define CBUS2_MEM_SLOTS	4
#define IS_CBUS2_MEM_ALIVE(id)	((Cbus2_mem_modules_alive & (1 << id)) != 0)
#define IS_CBUS2_CPU_ALIVE(id)	((Cbus2_cpu_modules_alive & (1 << id)) != 0)
#define SET_CBUS2_MEM_ALIVE(id) (Cbus2_mem_modules_alive |= (1 << id))
#define SET_CBUS2_CPU_ALIVE(id) (Cbus2_cpu_modules_alive |= (1 << id))


/*
 * Masks for CBus2 bit fields.
 *
 * CBUS2_PA is 30 bits, corresponding to PA<33:4>.
 * CBUS2_LK is 29 bits, corresponding to PA<33:5> (MSB is always 0).
 * CBUS2_EA is 16 bits, corresponding to PA<33:18>.
 */
#define CBUS2_PA	0x3FFFFFFFUL /* CBus2 PA<33:4> */
#define CBUS2_LK	0x1FFFFFFFUL /* CBus2 Lock Address, PA<33:5> (MSB always 0) */
#define CBUS2_EA	    0xFFFFUL /* CBus2 Exchange Address, PA<33:18> */
#define CBUS2_TT	       0x7UL /* CBus2 Transaction 0=Read,2=Exch,4=Write,7=NUT */
#define CBUS2_CID 	       0x7UL /* CBus2 Commander ID  */

/*
 * SCB Stuff for the console lines
 *
 * Try MAY21::WRK:[MOPLOAD]NOV22_SBLOAD.SYS, and say ">>>update".  If you 
 * deposit 1 to physical 380, you will get the following:
 * 
 * 8f0 instead of 680/690
 * 880 instead of 6a0/6b0
 */
#define CBUS2_PCI_COMMA_SCB_RECV		0x680
#define CBUS2_PCI_COMMA_SCB_XMIT		0x690

#define CBUS2_PCI_COMMB_SCB_RECV		0x6a0
#define CBUS2_PCI_COMMB_SCB_XMIT		0x6b0

#define CBUS2_PCI_SCB_COMMA			0x8f0
#define CBUS2_PCI_SCB_COMMB			0x880


/*
 * some standard io addressing, more to follow
 */
#define CBUS2_PCI_NMI_ST_CTRL	0x61
#define CBUS2_PCI_TMR1_CTR2	0x42
#define CBUS2_PCI_TMR1_CMR	0x43

/* index'es into the base and mask arrays */
#define	WIN_NONE	-1
#define	WIN_1MEG	0
#define	WIN_2MEG	1
#define	WIN_4MEG	2
#define	WIN_8MEG	3
#define	WIN_16MEG	4
#define	WIN_32MEG	5
#define	WIN_64MEG	6
#define	WIN_128MEG	7
#define	WIN_256MEG	8
#define	WIN_512MEG	9
#define	WIN_1GIG	10
#define	WIN_1GIG_SG	11
#define	WIN_4GIG	12

/*
 * Possible T2 window sizes
 */
#define M_0_MEG			0x00000000
#define M_1_MEG			0x00100000
#define M_2_MEG			0x00200000
#define M_4_MEG			0x00400000
#define M_8_MEG			0x00800000
#define M_16_MEG		0x01000000
#define M_32_MEG		0x02000000
#define M_64_MEG		0x04000000
#define M_128_MEG		0x08000000
#define M_256_MEG		0x10000000
#define M_512_MEG		0x20000000
#define M_1_GIG			0x40000000
#define M_2_GIG			0x80000000


/* number of entries in the table of pfns for scatter gather */
#define	IO_PAGE_SIZE	8192
#define	NUM_ENTRIES	( WINDOW_SIZE(SG_WIN) / IO_PAGE_SIZE)

/* space required to store the table */
#define RAW_SPACE	((NUM_ENTRIES * sizeof(long)) + IO_PAGE_SIZE)

/* 
 * Flush the tlb.
 */

#define CBUS2_PCI_FLUSH_SG_TLB(x)  { \
      u_long temp; \
      temp = cbus2_pci_PCI_regs[x]->iocsr; \
      temp |= IOCSR_FLUSH_TLB; \
      cbus2_pci_PCI_regs[x]->iocsr = temp; \
      mb(); mb(); \
      temp = cbus2_pci_PCI_regs[x]->iocsr; \
      temp &= ~IOCSR_FLUSH_TLB; \
      cbus2_pci_PCI_regs[x]->iocsr = temp; \
      mb(); }

#define CBUS2_PCI_ENABLE_SG_TLB(x) {cbus2_pci_PCI_regs[x]->iocsr |= IOCSR_ENABLE_TLB; mb();};
#define CBUS2_PCI_DISABLE_SG_TLB(x) {cbus2_pci_PCI_regs[x]->iocsr &= ~IOCSR_ENABLE_TLB; mb();};



/*
 * T4  Control and Status Registers
 *
 * All CBUS CSRs in the Cbus2 IO subsystems are in the T4 gate array.  The
 * CBUS CSRs in the T4 are all aligned on hexaword boundaries and have 
 * quadword length.  Note, this structure also works for T2 as the T2
 * registers are a proper subset of the T3/T4's.  Just make sure
 * that T2 code does not reference T3/T4-only registers.
 *
 */

struct PCI_csr {
	u_long iocsr;	u_long fill_00[3]; /* I/O Control/Status */
	u_long cerr1;	u_long fill_01[3]; /* Cbus Error Register 1 */
	u_long cerr2;	u_long fill_02[3]; /* Cbus Error Register 2 */
	u_long cerr3;	u_long fill_03[3]; /* Cbus Error Register 3 */
	u_long pcierr1;	u_long fill_04[3]; /* PCI Error Register 1 */
	u_long pcierr2;	u_long fill_05[3]; /* PCI Error Register 2 */
	u_long pciscr;	u_long fill_06[3]; /* PCI Special Cycle  */
	u_long hae0_1;	u_long fill_07[3]; /* High Address Extension 1 */
	u_long hae0_2;	u_long fill_08[3]; /* High Address Extension 2 */
	u_long hbase;	u_long fill_09[3]; /* PCI Hole Base */
	u_long wbase1;	u_long fill_0a[3]; /* Window Base 1 */
	u_long wmask1;	u_long fill_0b[3]; /* Window Mask 1 */
	u_long tbase1;	u_long fill_0c[3]; /* Translated Base 1 */
	u_long wbase2;	u_long fill_0d[3]; /* Window Base 2 */
	u_long wmask2;	u_long fill_0e[3]; /* Window Mask 2 */
	u_long tbase2;	u_long fill_0f[3]; /* Translated Base 2 */
	u_long tlbbr;	u_long fill_10[3]; /* TLB by-pass */
	u_long ivr;	u_long fill_11[3]; /* IVR Passive Rels/Intr Addr  (reserved on T3/T4) */
	u_long hae0_3;	u_long fill_12[3]; /* High Address Extension 3 */
	u_long hae0_4;	u_long fill_13[3]; /* High Address Extension 4 */
	u_long wbase3;	u_long fill_14[3]; /* Window Base 3 */
	u_long wmask3;	u_long fill_15[3]; /* Window Mask 3 */
	u_long tbase3;	u_long fill_16[3]; /* Translated Base 3 */

	u_long rsvd1;	u_long fill_16a[3]; /* unused location */

	u_long tdr0;	u_long fill_17[3]; /* tlb data register 0 */
	u_long tdr1;	u_long fill_18[3]; /* tlb data register 1 */
	u_long tdr2;	u_long fill_19[3]; /* tlb data register 2 */
	u_long tdr3;	u_long fill_1a[3]; /* tlb data register 3 */
	u_long tdr4;	u_long fill_1b[3]; /* tlb data register 4 */
	u_long tdr5;	u_long fill_1c[3]; /* tlb data register 5 */
	u_long tdr6;	u_long fill_1d[3]; /* tlb data register 6 */
	u_long tdr7;	u_long fill_1e[3]; /* tlb data register 7 */
	u_long wbase4;	u_long fill_1f[3]; /* Window Base 4 */
	u_long wmask4;	u_long fill_20[3]; /* Window Mask 4 */
	u_long tbase4;	u_long fill_21[3]; /* Translated Base 4 */
/*
 * The following 4 registers are used to get to the ICIC chip
 */
	u_long air;	u_long fill_22[3]; /* Address Indirection register */
	u_long var;	u_long fill_23[3]; /* Vector access register */
	u_long dir;	u_long fill_24[3]; /* Data Indirection register */
	u_long ice;	u_long fill_25[3]; /* IC enable register Indirection register */

};
typedef struct PCI_csr * PCI_csrp_t;

/*
 * iocsr stuff we use
 */

#define IOCSR_FLUSH_TLB			0x10000000L
#define IOCSR_ENABLE_TLB		0x04000000L
#define IOCSR_ENABLE_TLB_ERROR_CHK	0x80L

#define FLUSH_T4_TLB(x)	(x->iocsr |= IOCSR_FLUSH_TLB)

/* 
 * HAE register Locking macros - handle IPL and SMP locks
 */
#define HAE_LOCK_INIT(lock, lockinfo)	\
	usimple_lock_setup ( &lock, lockinfo )

#define HAE_IPL_LOCK(lock, s) {		\
	s = spldevhigh();		\
	simple_lock ( &lock );		\
}

#define HAE_IPL_UNLOCK(lock, s) {	\
	simple_unlock ( &lock );	\
	splx(s);			\
}

/*
 * Cbus Error Register 1 - CERR1_ERRORS
 * This checks for 
 *	Error Name				Bits
 * 	Data Parity Errors 			45-42, 13-10
 * 	CA Parity Errors   			41, 40, 9, 8
 * 	Invalid PFN	   			18
 * 	Bus Sync Error				17
 *	Comander Write Parity Error		16
 *	Missed Read Data Parity Error		7
 *	Read Data Parity Error			6
 *	Missed Rsp Write Data Parity Error	5
 *	Responder Write Data Parity Error	4
 *	Missed Command Addr Parity Error	3
 *	Command Address Parity Error		2
 *	No Acknowledge Error			1
 *	Uncorr Read Error			0
 */



#define CERR1_BSE (1UL << 17)	/* Bus Synchronization Error */
#define CERR1_INVALID_PFN (1UL << 18)	/* Invalid pfn */

#define CERR1_UREL (1UL << 0)	/* Uncorr Read Error Low (even) */
#define CERR1_UREH (1UL << 32)	/* Uncorr Read Error High (odd) */
#define CERR1_URE  (CERR1_UREL|CERR1_UREH) /* Uncorr Read Error */
 
#define CERR1_CANAL (1UL << 1)	/* Cmd/Adr NoAck Low (even) */
#define CERR1_CANAH (1UL << 33)	/* Cmd/Adr NoAck High (odd) */
#define CERR1_CANA  (CERR1_CANAL|CERR1_CANAH)	/* Command/Address No-Ackn */
 
#define CERR1_CAPEL (1UL << 2)	/* Cmd/Adr Par Err Low (even) */
#define CERR1_CAPEH (1UL << 34)	/* Cmd/Adr Par Err High (odd) */
#define CERR1_CAPE  (CERR1_CAPEL|CERR1_CAPEH) /* Cmd/Adr Parity Error */
 
#define CERR1_MCAPEL (1UL << 3) /* Missed C/A Par Err Low (even) */
#define CERR1_MCAPEH (1UL << 35)/* Missed C/A Par Err High (odd) */
#define CERR1_MCAPE  (CERR1_MCAPEL|CERR1_MCAPEH)  /* Missed C/A Parity Err */
 
#define CERR1_WDPEL (1UL << 4)	/* Rsp Wr Data Par Err Low (even) */
#define CERR1_WDPEH (1UL << 36)	/* Rsp Wr Data Par Err High (odd) */
#define CERR1_WDPE  (CERR1_WDPEL|CERR1_WDPEH)  /* Rspdr Wrt Data Par Err */
 
#define CERR1_MWDPEL (1UL << 5) /* Missed Rsp Wr Data Par Err Low  */
#define CERR1_MWDPEH (1UL << 37)/* Missed Rsp Wr Data Par Err High */
#define CERR1_MWDPE (CERR1_MWDPEL|CERR1_MWDPEH) /*Missed Rsp Wr Data Parr Err*/
 
#define CERR1_RDPEL (1UL << 6)	/* Read Data Par Err Low (even) */
#define CERR1_RDPEH (1UL << 38)	/* Read Data Par Err High (odd) */
#define CERR1_RDPE  (CERR1_RDPEL|CERR1_RDPEH)/* Read Data Parity Error */
 
#define CERR1_MRDPEL (1UL << 7)	/* Missed Read Data Par Err Low */
#define CERR1_MRDPEH (1UL << 39)/* Missed Read Data Par Err High*/
#define CERR1_MRDPE  (CERR1_MRDPEL|CERR1_MRDPEH) /* Missed Rd Data par Err */

#define CERR1_CWDPEL (1UL << 16)
#define CERR1_CWDPEH (1UL << 48)
#define CERR1_CWDPE  (CERR1_CWDPEL|CERR1_CWDPEH)
 
#define CERR1_CSEL (1UL << 14)  /* CSTALL Sync Err Low */
#define CERR1_CSEH (1UL << 46)  /* CSTALL Sync Err High */
#define CERR1_CSE  (CERR1_CSEL|CERR1_CSEH) /* CSTALL Sync Error */

#define CERR1_ERRORS	(CERR1_CSE|CERR1_CWDPE|CERR1_MRDPE|\
 			 CERR1_RDPE|CERR1_MWDPE|CERR1_WDPE|CERR1_CANA|\
 			 CERR1_CAPE|CERR1_URE|CERR1_BSE|CERR1_INVALID_PFN)

#define CERR1_ERROR(x)	((x->cerr1) & CERR1_ERRORS)

/*
 * PCI Error Register 1 - PCIERR1_ERRORS
 * This checks for 
 *	Error Name				Bits
 *	Non-Maskable Interrupt			6
 *      PCI device Timeout Error		5
 *	PCI System Error			4
 *	PCI Parity Error			3
 *	PCI Read Data Parity Error		2
 *	PCI Address Parity Error		1
 *	PCI Write Data Parity Error		0
 */
#define	PCIERR1_NMI	(1UL << 6)
#define	PCIERR1_DTE	(1UL << 5)
#define	PCIERR1_SE	(1UL << 4)
#define	PCIERR1_PE	(1UL << 3)
#define	PCIERR1_RDPE	(1UL << 2)
#define	PCIERR1_APE	(1UL << 1)
#define	PCIERR1_WDPE	(1UL << 0)

#define PCIERR1_ERRORS	( PCIERR1_NMI | PCIERR1_DTE | PCIERR1_SE | PCIERR1_PE | \
 			 PCIERR1_RDPE | PCIERR1_APE | PCIERR1_WDPE )
 
#define PCIERR1_ERROR(x)	(x->pcierr1 & PCIERR1_ERRORS)

/*
 * T4 DMA is controlled by two sets of three registers: WBASE, WMASK, and 
 * TBASE
 * WBASE - enables the DMA function, enables DMA type (direct-mapped or 
 * scatter-gather), and to created a window of dma addresses that the T2 
 * should respond to.
 *
 * WMASK - redundantly indicates the size of the enabled window.  It must 
 * agree with WBASE
 * TBASE - for direct-mapped DMA, TBASE indicates offset to map DMAs into 
 * system memory. For scatter-gather TBASE provides a way to map the 
 * scatter/gather page table into system memory at different offsets.
 */

/*
 * Window Base Register		WBASE1 and WBASE2
 * 11:0	  PCI Window End Address - when WBASE[19] is set, these bits are 
 *	  compared to PCI_AD[31:20] of incoming PCI cycles to determine if the 
 *	  address falls at or below the upper bound of the first programmable 
 *	  PC window.
 * 17:12  reserved (must be zero)
 * 18	  Scatter-Gather enable - when this bit is set, scatter-gather mapping 
 *	  of PCI addresses with the first PCI target window is enabled.  When 
 *	  clear, the PCI addresses are direct mapped.
 * 19	  PCI window enable - when this bit is set, the T2 gate array will 
 *	  respond to PCI addresses which fall at or between the first 
 *	  programmable PCI window start and end addresses contained in 
 *	  WBASE[31:20] and WBASE[11:0], respectively.
 * 31:20  PCI window start address - when wbase1[19] is set, these bits are 
 *	  compared to PCI_AD[31:20] of incoming PCI cycles to determine if the 
 *	  address falls at or above the lower bound of the first programmable 
 *	  PCI window.
 * 63:32  reserved
 *
 *
 * Window Mask Register 	WMASK1 and WMASK2
 * 19:0	  reserved (must be zero)
 * 30:20  PCI Window Mask - specifies the size fo the PCI target window and is 
 *	  also used in the translation of the CPU address
 * 63:31  reserved (must be zero)
 *
 * Translated Base Register	TBASE1 and TBASE2
 * 8:0	  reserved (must be zero)
 * 30:9	  Translasted Base Address - if wbase[18] is set, this specified the 
 *	  base address for the scatter-gather map table for the first PCI 
 *	  target window. If WBASE[18] is clear, this specified the base CPU 
 *	  address of the translated PCI address for the first PCI target window
 * 63:31  reserved (must be zero)
 */

#define WINDOW_ENABLE		0x80000L	/* bit 19 */
#define WINDOW_DISABLE		0x00000L	/* bit 19 */
#define WINDOW_SCATTER_GATHER	0x40000L	/* bit 18 */	
#define WINDOW_DIRECT_MAPPED	0x00000L	/* bit 18 */	
#define WINDOW_PEER_PEER	0x20000L	/* bit 17 */	

#define WINDOW_START_MASK	0x7ff00000L
#define WINDOW_END_MASK		0x000007ffL

/* 
 * HBASE
 *
 * 8:0	  PC hole end address - when hbase,14> is set, these bits are compared 
 *	  to PCI_AD<23:15> of incoming PCI cycles to determine if the address
 *	  falls below the upper bound of the programmable PC hole.  The address
 *	  contained in this register signifies the last valid upper PCI address
 *	  in the hole. bits 8:5 must be non-zero when this hole is enabled.
 * 12:9	  reserved (must be zero)
 * 13	  PC hole enable 1 - when this bit is set, the T2 gate arry will not
 *	  respond to PCI addresses which fall within the fixed PC hole between 
 *	  512KB and 1MB
 * 14	  PC hole enable 2 - when this bit is set, the T2 gate arry will not
 *	  respond to PCI addresses which fall within the programmable PC hole 
 *	  start and end addresses contained in hbase<23:26> and hbase<7:0>
 *	  ====>	the Sable IO spec pg 50 is inconsistent here, this should 
 *	  	probably be hbase<23:15> and hbase<8:0>
 * 23:15  PC hole start address - when hbase<14> is set, these bits are 
 *	  compared to PCI_AD<23:15> of incoming PCI cycles to dtermine if the 
 *	  address falls above the lower bound of the programmable PC hole.  The
 *	  address contained in this register signifies the last valid lower PCI
 *	  address in the hole.Bits 23:20 must be non-zero when this hole is 
 *	  enabled.
 * 63:24  Reserved (must be zero)
 * 
 */
#define PC_HBASE_H1_ENAB	0x2000L		/* bit 13 */
#define PC_HBASE_H2_ENAB	0x4000L		/* bit 14 */
#define PC_HBASE_H2_END		0x03fL		/* ending   pci addr 1f8000 */
#define PC_HBASE_H2_START	0x100000L	/* starting pci addr 100000 */



/*****************************************************************************
 * MEMORY MODULE CSRS							     *
 *****************************************************************************
 *
 * Cbus2 accomodates up to four memory modules.  Each memory module has
 * two or four banks of DRAMs, and two ASIC slices to handle memory control and
 * CBus traffic.  There are no configuration rules for ordering memories in
 * their slots; the slot ID is picked up from the backplane when a module is
 * plugged in.
 *
 * Memory modules may be interleaved to improve performance.  Interleaving
 * increases performance on sequential memory accesses, and also increases
 * the chance that memory refresh cycles can be hidden behind accesses to
 * another board.  Cache lines are never split accross boards, even when they
 * are interleaved.
 *
 * Two or four identical boards may be interleaved, using two-way or four-way
 * interleaving.  Two-way interleaving may also be used to interleave boards
 * with different sizes, if multiple boards can be combined to have the same
 * capacity as the board which they are interleaved with.  For example, a
 * 256Mb board may be two-way interleaved with two 128Mb boards.
 *
 * The interleave mode, interleave unit, module size, and module base address
 * determine which addresses a module responds to.  The revision field
 * indicates the revision of the memory module ASICs.  The slot field is used
 * for error reporting, to correlate errors with the physical board location.
 * The only way that the slot number comes in to play in system setup is the
 * choice of a board to load the console.  When the system comes up, the
 * largest memory which is closest to the CPU (lowest slot number) is chosen
 * to load the console.
 */

struct mem_csr {
	u_long error;	u_long fill_00[3];  
/* CSR0: Error Register */
	u_long ctrap1;	u_long fill_02[3];  /* CSR1: CBus Command Trap 1 */
	u_long ctrap2;	u_long fill_04[3];  /* CSR2: CBus Command Trap 2 */
	u_long config;	u_long fill_06[3];  /* CSR3: Memory Configuration */
	u_long edcstat1; u_long fill_08[3]; /* CSR4: EDC Status 1 */
	u_long edcstat2; u_long fill_0A[3]; /* CSR5: EDC Status 2 */
	u_long edcctl;	u_long fill_0C[3];  /* CSR6: EDC Control */
	u_long stream;	u_long fill_0E[3];  /* CSR7: Stream Buffer Control */
	u_long refresh;	u_long fill_10[3];  /* CSR8: Refresh Control */
	u_long filter;	u_long fill_12[3];  /* CSR9: CRD Filter Control */
			u_long fill_14[4];
			u_long fill_16[4];
			u_long fill_18[4];
			u_long fill_1A[4];
			u_long fill_1C[4];
	u_long force;	u_long fill_1E[3];  /* CSRF: Tester Forced Refresh */
};
typedef struct mem_csr * mem_csrp_t;

/* This is looking at merr (memory csr0) */
/*
 * MEM_UNCORRECTABLE is everything EXCEPT memory correctables.  
 * All these are FATAL.  Note that the summary bits aren't checked
 * because they are set cor correctables.
 */
#define MEM_UNCORRECTABLE	0x0033f3e00033f3eUL
#define MEM_ERROR(x)		(x->error & MEM_UNCORRECTABLE)
/*
 * MEM_CORRECTABLE is just the two EDC correctable bits.  They'll be set if errors
 * were missed, so skip checking the missed correctables.  These macros are for
 * checking the memory error csr.
 * EDC Correctable Error -- Set on detection of an EDC Correctable Error on
 * data read from the DRAM array.  Write 1 to clear.  Cleared on powerup.
 */
#define MERR_EDCCEL (1UL << 18)		      /* Mem EDC Corr Err Low */
#define MERR_EDCCEH (1UL << 50)		      /* Mem EDC Corr Err High */
#define MERR_EDCCE  (MERR_EDCCEL|MERR_EDCCEH) /* Mem EDC Corr Err */

#define MERR_MISSED_EDCCEL (1UL << 19)        /* Mem missed EDC Corr Err Low */
#define MERR_MISSED_EDCCEH (1UL << 51)	      /* Mem missed EDC Corr Err High */
#define MERR_MISSED_EDCCE  (MERR_MISSED_EDCCEL|MERR_MISSED_EDCCEH)
                                              /* Mem EDC Corr Err */
#define MEM_CORRECTABLE		0x4000000040000UL
#define MEM_CORR(x)		(x->error & (MERR_EDCCE | MERR_MISSED_EDCCE ))
/*
 * If there's a correctable error, make sure that correction is enabled.
 */
#define EDCCTL_DISEDCCL (1UL << 30)		/* Dis EDC Correction Low */
#define EDCCTL_DISEDCCH (1UL << 62)		/* Dis EDC Correction High */
#define EDCCTL_DISEDCC (EDCCTL_DISEDCCL | EDCCTL_DISEDCCH) /* Dis EDC Corrn */
#define MEM_CORR_DIS(x) (x->edcctl & EDCCTL_DISEDCC)

/*
 * Machine Check SCB Vectors.
 *
 * These values are specified by the SRM.  CBUS2_PCI_VECTOR_FRU is a special
 * case.
 */
#define CBUS2_PCI_VECTOR_PROC_FATAL	0x670
#define CBUS2_PCI_VECTOR_SYS_FATAL	0x660
#define CBUS2_PCI_VECTOR_PROC_CORR	0x630
#define CBUS2_PCI_VECTOR_SYS_CORR	0x620  /* unused */
#define CBUS2_PCI_VECTOR_FRU		0x0


#endif /* CBUS2_PCI_H */
