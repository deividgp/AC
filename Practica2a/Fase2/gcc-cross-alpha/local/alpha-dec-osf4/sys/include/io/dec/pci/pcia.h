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
 * @(#)$RCSfile: pcia.h,v $ $Revision: 1.1.23.2 $ (DEC) $Date: 1998/06/24 21:10:32 $
 */
#ifndef __PCIA_H__
#define __PCIA_H__

#include <sys/types.h>
/*
 * TLSB Address Map:
 * ----------------
 *
 *  TLSB ADDR <39:0>
 * 00 0000 0000 - 7F FFFF FFFF	- TLSB Memory Space
 * 80 0000 0000 - 8F FFFF FFFF	- Node 4 I/O Space
 * 90 0000 0000 - 9F FFFF FFFF	- Node 5 I/O Space
 * A0 0000 0000 - AF FFFF FFFF	- Node 6 I/O Space
 * B0 0000 0000 - BF FFFF FFFF	- Node 7 I/O Space
 * C0 0000 0000 - CF FFFF FFFF	- Node 8 I/O Space
 * D0 0000 0000 - DF FFFF FFFF	- Reserved
 * E0 0000 0000 - EF FFFF FFFF	- Reserved
 * F0 0000 0000 - FF FFFF FFFF	- TLSB CSR space/CPU private space
 *
 * Turbolaser I/O Space Per Node:
 * -----------------------------
 * x0 0000 0000 - x3 FFFF FFFF	- I/O Space for Hose 0
 * x4 0000 0000 - x7 FFFF FFFF	- I/O Space for Hose 1
 * x8 0000 0000 - xB FFFF FFFF	- I/O Space for Hose 2
 * xC 0000 0000 - xF FFFF FFFF	- I/O Space for Hose 3
 *
 * Cpu to PCI Address Mapping for a single PCIA:
 * ---------------------------------------------
 *
 * CPU Address Range		PCI Address Range	PCI Address Space
 * -----------------		-----------------	-----------------
 * x0 0000 0000	- x0 FFFF FFFF  0000 0000 - FFFF FFFF	PCI Memory Space -Dense
 * x1 0000 0000	- x1 1FFF FFFF  0000 0000 - 00FF FFFF	PCI Memory Space -Sparse
 *								(fixed)
 * x1 2000 0000	- x1 FFFF FFFF  0100 0000 - 07FF FFFF	PCI Memory Space -Sparse
 *								(variable)
 * x2 0000 0000	- x2 1FFF FFFF  0000 0000 - 00FF FFFF	PCI IO Space -Sparse
 *								(fixed)
 * x2 2000 0000	- x2 FFFF FFFF  0100 0000 - 07FF FFFF	PCI IO Space -Sparse
 *								(variable)
 * x3 0000 0000	- x3 7FFF FFFF  0000 0000 - 0000 00FF	PCI Configuration Space
 * x3 8000 0000	- x3 FFFF FFFF  	N/A		PCIA CSR's and Map RAM
 *
 * 
 * CPU to PCI Address Mapping:
 * ---------------------------
 * 
 * ------------------------------------------------------------------------
 * | 1 | TLSB Rcv | Hose # | Space Sel | Byte Aligned I/O | Byte Len | Zero|
 * |   | Node     |	   |  Field    |  Address	  |   Field  |     |
 * ------------------------------------------------------------------------
 *   39 38      36 35    34  33      32 31		5  4        3  2  0
 *   
 * <39> - I/O Select (Always 1 for direct I/O access)
 * <38-36>
 *	0 - Node 4 I/O Space
 *	1 - Node 5 I/O Space
 *	2 - Node 6 I/O Space
 *	3 - Node 7 I/O Space
 *	4 - Node 8 I/O Space
 *	5 - Reserved
 *	6 - Reserved
 *	7 - TLSB CSR Space, EV5 Private Space, TLEP Gbus space
 *
 * <35-34> - Hose select
 *	00 - Hose 0
 *	01 - Hose 1
 *	10 - Hose 2
 *	11 - Hose 3
 *	
 * <33-32> - PCI Address Space
 *	00 - Dense Memory Space
 *	01 - Sparse Memory Space
 *	10 - Sparse I/O Space
 *	11 - Sparse Configuration Space
 *	
 *
 * Dense Space address mapping:
 * ----------------------------
 * 		31			5 4	0
 *		---------------------------------
 * Cpu Address  |			 |	|
 *		---------------------------------
 *			     |
 *			     |
 *		31	     v 		5 4     0
 *		---------------------------------
 * PCI Address |			 | 00000|
 * 		---------------------------------
 */


struct pcia_regs
{

	/* hpc specific registers. These
	 * offsets are used to access all
	 * the hpcs even though only
	 * 1 hpc is defined 
	 */
	unsigned int	ctl0;
	char		pad0[0x7c];
	unsigned int	mretry0;
	char		pad1[0x7c];
	unsigned int	gpr0;
	char		pad2[0x7c];
	unsigned int	err0;
	char		pad3[0x7c];
	unsigned int	fadr0;
	char		pad4[0x7c];
	unsigned int	imask0;
	char		pad5[0x7c];
	unsigned int	diag0;
	char		pad6[0x7c];
	unsigned int	ipend0;
	char		pad7[0x7c];
	unsigned int	iprog0;
	char		pad8[0x7c];
	unsigned int	wmask_a0;
	char		pad9[0x7c];
	unsigned int	wbase_a0;
	char		pad10[0x7c];
	unsigned int	tbase_a0;
	char		pad11[0x7c];
	unsigned int	wmask_b0;
	char		pad12[0x7c];
	unsigned int	wbase_b0;
	char		pad13[0x7c];
	unsigned int	tbase_b0;
	char		pad14[0x7c];
	unsigned int	wmask_c0;
	char		pad15[0x7c];
	unsigned int	wbase_c0;
	char		pad16[0x7c];
	unsigned int	tbase_c0;
	char		pad17[0x7c];
	unsigned int	errvec0;
	char		pad18[0x6fc];
	unsigned int	devvec0;
	char		pad19[0x7fc];
	char		pad20[0x800];
	unsigned int	scycle;
	char		pad21[0x7c];
	unsigned int	iack;
	char		pad2end[0x1fdf7c];	/* pad to size of HPC */
};

	/* Non hpc specific */
struct pcia_ext_regs {
	char		pad22[0x800000];
	unsigned int	present;
	char		pad23[0x1ffffc];
	unsigned int	tbit;

};

/* csr defines */
#define HPC_DIAG_REV_SHIFT 3
#define HPC_DIAG_REV_MASK 	0x00000078L
/* hpc ctl register definitions */
#define HPC_CTL_SG_SIZE_MASK	0x06000000L
#define HPC_CTL_SG_SIZE_32K	0x00000000L
#define HPC_CTL_SG_SIZE_64K	0x02000000L
#define HPC_CTL_SG_SIZE_128K	0x06000000L
/* csr defines */
#define HPC_DIAG_REV_SHIFT 3
#define HPC_DIAG_REV_MASK 0x00000078L

/* 128k sg entries */
#define PCIA_TBIT_SET		0x00000001L /* above rev0 pcia only */
#define PCIA_PRESENT_REV_MASK	0x1E000000L


#define	IS_AN_EISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_EISA) 

/* private pci bus fields used by pcia code 
 * Commented defines are not used in the code
 * but instead are referenced directly.
 * This seemed like a good place to track them.
 */
/* #define BUS_NUM_HPC		private[2] */
/* #define BUS_DMA_INFO_LIST	private[3] */
/* #define BUS_HPC_REV          private[4] */
/* PCI SGMAP ctl structure	private[5] */
/* EISA SGMAP ctl structure 	private[6] */

/* private pci bus fields used by pcia code */
#define BUS_NUM_HPC 		private[2]
#define BUS_HPC_REV 		private[4]

/*
 * Alpha IO Architecture standard address swizzle
 */
#define	IO_SHIFT	(5)
#define	IO_STRIDE	(0x80)
#define	IO_BYTE_STRIDE	(0x20)
#define	ALIGN_MASK	(0xffffffffffffff9f)
#define	WIDTH_MASK	(0x18)
#define	WIDTH_SHIFT	(IO_SHIFT - 2)
#define Wrd		((long)1 << (WIDTH_SHIFT))
#define Lng		((long)3 << (WIDTH_SHIFT))
#define Tri		((long)2 << (WIDTH_SHIFT))

#define NUKE_BIT31 	0xffffffff7fffffffL 	/* matches eisa address with cpu address 	*/
#define IO_ALIGN_MASK	0xffffffffffffff9fL 	/* aligns swizzled address to longword boundary */

#define IOA_OKAY	0
#define	IOA_ERROR	-1

#define LOW_32		0x00000000FFFFFFFFL	/* Low 32 bits   */
#define HIGH_32		0xFFFFFFFF00000000L	/* Upper 32-bits */
#define SYSMAP_MASK	HIGH_32
#define SYSMAP_SHIFT	32

/* Used to get the PCI Bus
 * address bits from the EV5
 * address	
 */
#define PCI_ADDRESS_SPACE_MASK	0x300000000L

/*
 * mask used to retrieve the offset into
 * a pcia of an iohandle.
 */
#define PCIA_OFFSET_MASK 0x3ffffffff


/* These are used to set bits in the PCI_IO (PCI Sparce I/O Byte) Macro */
#define A_BYTE		00
#define A_WORD		01
#define A_TRI-BYTE	10
#define A_LONGWORD	11
#define A_QUADWORD	11

#define sLEFT  0	/* shift left first */
#define sRIGHT 1        /* shift right first */
#define BIT31		0x80000000


/* A general Macro to SWIZZLE an address. Its looking for:
 *	x		- the address to swizzle
 *	BASE		- The base address of the memory region
 *	Wrd/Lng		- The bits to guide size of data (Byte, word, 
 *			  tribyte, long)
 *	Mask		- Mask of the based on address size
 *	IO_SHIFT	- Distance to shift the address for the other data 
 *			  to fit into
 */
#define BUSMEM_MASK	0x7ffffff
#define BUSIO_MASK	0x1ffffff 


#define WINDOW_ENABLE		0x2
#define WINDOW_DISABLE		0x0
#define WINDOW_DIRECT_MAPPED 0x00000L
#define WINDOW_START_MASK 0x7ff00000L
#define WINDOW_SCATTER_GATHER 0x1


/*
 * The following are offsets from the adapter base address.
 * The adapter base address is a function of the slot on the TLSB
 * that the TIOP is in and the hose number of the TIOP to which the adapter
 * is attached.
 */
#define PCI_DENSE_MEM_BASE	0x000000000L	
#define PCI_SPARSE_MEM_BASE	0x100000000L
#define PCI_SPARSE_IO_BASE	0x200000000L
#define PCI_CONFIG_BASE		0x300000000L	/* PCI Config Sparse Space */
#define PCIA_CSR_RAM_BASE	0x380000000L	/* PCI  CSR's and Map RAM */
#define CONFIG_BASE_TO_CSR_RAM	0x080000000L	
#define PCIA_SG_MAP_RAM_BASE	0x001000000L
#define CONFIG_BASE_TO_SG_MAP	0x081000000L

/*
 * Determination of whether an iohandle is dense or not.  Dense space is the low
 * 32 bits of pcia address space.  Eliminate the bits used to select a pcia (lsb
 * node and hose select bits) and see if the result is below the next highest
 * address space, PCI_SPARSE_MEM_BASE.
 */
#define PCIA_DENSE_IOH(addr) ((addr & PCIA_OFFSET_MASK) < PCI_SPARSE_MEM_BASE)

/*
 * Bits <18:17> determine which HPC is being addressed in config space.
 */
#define	HPC0_CONFIG		0x00000L
#define	HPC1_CONFIG		0x20000L
#define	HPC2_CONFIG		0x40000L
#define	HPC3_CONFIG		0x60000L

/*
 * Offsets into CSR space for each HPC
 */
#define	TLASER_HPC0		0x000000L
#define	TLASER_HPC1		0x200000L
#define	TLASER_HPC2		0x400000L
#define	TLASER_HPC3		0x600000L

#define	TLASER_PCI_MAX_SLOT	12
#define TLASER_PCI_INTR_INFO_SIZE	12*4*5 /* 12 slots * 4 hoses * 5 IOPs */
#define TLASER_PCI_MAX_INTR	12*4	/* 12 slots * 4 interrupts per slot */
#define	TLASER_FLUSH_SG_TLB
#define EISA_INTR_INFO_SIZE	24
#define SET_INTMASK		0
#define CLEAR_INTMASK		1

/*
 * DMA Support
 */
#define IS_AN_EISA_DEVICE(a)    (a->bus_hd->bus_type == BUS_EISA)
#define DMA_FORCE_CONTIG        DMA_RSVD_4000

#define IS_A_CONTIG_DEVICE(f)   (f & DMA_CONTIG)
#define IS_A_FLOPPY_DEVICE(a)   (strcmp(a->ctlr_name, "fdi") == 0)
#define IS_A_SG_DEVICE(a,f)     (IS_A_CONTIG_DEVICE(f) || tlaser_always_sg)
#define ADDRESS_LIMITED(f)      ((f) & DMA_ADDR_LIMIT)
#define FORCE_CONTIG(f)         ((f) & DMA_FORCE_CONTIG)
#define CONTIG_DESIRED(f)       ((f) & DMA_CONTIG)
#define SG_ALLOCED(f)           ((f) & DMA_HW_SG)
#define HAS_SG_ALLOCED(f)       ((f) & DMA_HW_SG)

#define SG_NOTNEEDED    0
#define SG_REQUIRED     1
#define SG_DESIRED      2

#define M_8_MEG	0x000800000

#define SG_MAP_BASE_DEVICE(f,BUSP)   (ADDRESS_LIMITED(f) ? \
		(vm_offset_t)(BUSP->private[6]) : \
		(vm_offset_t)(BUSP->private[5]) )

#define CROSSES_PAGE_BOUNDARY(a,c)      ((((a) & page_mask) + (c)) > page_size)
#define PEER_TO_PEER_DMA_BASE           (0L)


/*
 * CTL register Locking macros - handle IPL and SMP locks
 */
#define CTL_LOCK_INIT(lock, lockinfo)   \
        usimple_lock_setup ( &lock, lockinfo )

#define CTL_IPL_LOCK(lock, s) {         \
        s = spldevhigh();               \
        simple_lock ( &lock );          \
}

#define CTL_IPL_UNLOCK(lock, s) {       \
        simple_unlock ( &lock );        \
        splx(s);                        \
}

/* EISA Interrupts on Turbolaser
 *
 * The EISA interrupts, keyboard, mouse, serial and Parallel ports, 
 * floppy and IIC interrupts are all brought into the interrupt
 * line for PCI slot 0.
 *
 * Eisa interrupts will be handled by three Intel 8259As arranged in 
 * an 8086 Fully Nested  Mode cascade and in a level triggered mode.  
 * The hardware will be located on the Standard IO Module.  Firmware 
 * support is required for acknowledge and end of interrupt (EOI) 
 * handling.  There is one master and three slave 8259s.
 *
 *
 *	SLAVE 0	(536, 537)
 *	800 pci slot0 - Not used on Tlaser
 *	810 scsi port - Not used on Tlaser
 * 	820 ethernet port
 * 	830 mouse
 *	840 pci slot 1 - Not used on Tlaser
 *	850 pci slot 2 - Not used on Tlaser
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
 *	940 eisa irq 13 - Not used on Tlaser
 *	950 eisa irq 14
 * 	960 nc
 *	970 iic
 *
 * The routines are handled with two levels here.  
 *	First is the routine for all of sable.  
 *	Next is the eisa routine. It maps the eisa irq level to the sable irq level.
 *	Finally, the pic routine maps the pci irq (slot) to the sable irq level.
 */    
#define T2_PCISLOT0_STDIO_IRQ	0
#define T2_PSIOP_STDIO_IRQ  	1	    
#define T2_ETHE_STDIO_IRQ	2
#define T2_PCISLOT1_STDIO_IRQ	4
#define T2_PCISLOT2_STDIO_IRQ	5

#define TLASER_MOUS_STDIO_IRQ	3
#define TLASER_KEYB_STDIO_IRQ	6
#define TLASER_EISA0_STDIO_IRQ	7
 
#define TLASER_EISA1_STDIO_IRQ	8
#define TLASER_EISA2_STDIO_IRQ	9
#define TLASER_EISA3_STDIO_IRQ	10
#define TLASER_EISA4_STDIO_IRQ	11
#define TLASER_EISA5_STDIO_IRQ	12
#define TLASER_EISA6_STDIO_IRQ	13
#define TLASER_EISA7_STDIO_IRQ	14
#define TLASER_EISA8_STDIO_IRQ	15

#define TLASER_EISA9_STDIO_IRQ	16
#define TLASER_EISA10_STDIO_IRQ	17
#define TLASER_EISA11_STDIO_IRQ	18
#define TLASER_EISA12_STDIO_IRQ	19
#define TLASER_EISA13_STDIO_IRQ	20	/* not connected */
#define TLASER_EISA14_STDIO_IRQ	21
#define TLASER_EISA15_STDIO_IRQ	22
#define TLASER_IIC_STDIO_IRQ	23

#define TLASER_FLOPPY_EISA_IRQ	0
#define TLASER_COMMA_EISA_IRQ	8
#define TLASER_PARLEL_EISA_IRQ	2
#define TLASER_COMMB_EISA_IRQ	1

#define TLASER_FLOPPY_STDIO_IRQ	7
#define TLASER_COMMA_STDIO_IRQ	15
#define TLASER_PARLEL_STDIO_IRQ	9
#define TLASER_COMMB_STDIO_IRQ	8

#define TLASER_PCI_ADDR_TO_HANDL(x)	((x) + eisa_base_addr + PCI_SPARSE_IO_BASE)

#define	CTRL1_MASK	0x21
#define	CTRL2_MASK	0xa1

#define IACK_REG		0x532
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


#define READ_SLAVE0_MASK	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE0_INT_MASK))
#define WRITE_SLAVE0_MASK(x)	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(SLAVE0_INT_MASK), (x) ) 
#define READ_SLAVE0_CTRL	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE0_INT_CTRL))
#define WRITE_SLAVE0_CTRL(x) 	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(SLAVE0_INT_CTRL), (x) ) 

#define READ_SLAVE1_MASK	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE1_INT_MASK)) 
#define WRITE_SLAVE1_MASK(x)	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL( SLAVE1_INT_MASK), (x) )
#define READ_SLAVE1_CTRL	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE1_INT_CTRL)) 
#define WRITE_SLAVE1_CTRL(x) 	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(SLAVE1_INT_CTRL), (x) )

#define READ_SLAVE2_MASK	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE2_INT_MASK)) 
#define WRITE_SLAVE2_MASK(x)	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(SLAVE2_INT_MASK), (x) )
#define READ_SLAVE2_CTRL	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE2_INT_CTRL)) 
#define WRITE_SLAVE2_CTRL(x) 	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(SLAVE2_INT_CTRL), (x) )

#define READ_SLAVE3_MASK	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE3_INT_MASK)) 
#define WRITE_SLAVE3_MASK(x)	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(SLAVE3_INT_MASK), (x) )
#define READ_SLAVE3_CTRL	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(SLAVE3_INT_CTRL)) 
#define WRITE_SLAVE3_CTRL(x) 	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(SLAVE3_INT_CTRL), (x) )

#define READ_MASTER_MASK	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(MASTER_INT_MASK))
#define WRITE_MASTER_MASK(x)	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(MASTER_INT_MASK), (x) )
#define READ_MASTER_CTRL	READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(MASTER_INT_CTRL))
#define WRITE_MASTER_CTRL(x) 	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(MASTER_INT_CTRL), (x) )
#define READ_IACK		READ_BUS_D8( TLASER_PCI_ADDR_TO_HANDL(IACK_REG))


/*
 * ELCR1 maps up to irq 11
 * ELCR2 maps eisa_irq 12 14 15
 *
 *  setting  bit makes it level sensitive
 *  clearing bit makes it edge sensitive
 */
#define TLASER_ELCR1	0x26
#define TLASER_ELCR2	0x27

#define WRITE_TLASER_ELCR1( x )	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(TLASER_ELCR1), (x) )
#define WRITE_TLASER_ELCR2( x )	WRITE_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(TLASER_ELCR2), (x) )

#define READ_TLASER_ELCR1	READ_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(TLASER_ELCR1))
#define READ_TLASER_ELCR2	READ_BUS_D8(TLASER_PCI_ADDR_TO_HANDL(TLASER_ELCR2))


#define TLASER_EISA_IRQ_TO_STDIO_IRQ( x )	((x) + 7)
#define TLASER_STDIO_IRQ_TO_EISA_IRQ( x )	((x) - 7)
#define STDIO_IRQ_TO_SCB_VECTOR( x )		(( ( x ) * 0x10) + 0x800)


#endif	__PCIA_H__
