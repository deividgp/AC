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
 * @(#)$RCSfile: dc21171.h,v $ $Revision: 1.1.17.2 $ (DEC) $Date: 1998/09/18 17:45:06 $
 */
#ifndef DC21171_H
#define DC21771_H

#include <sys/types.h>
#include <hal/shared_intr.h>



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
#define LOW_26		0x0000000003FFFFFFL	/* Low 26 bits */
#define HIGH_38		0xFFFFFFFFFB000000L	/* high 38 bits */
#define LOW_27		0x0000000007FFFFFFL	/* Low 27 bits */
#define HIGH_37		0xFFFFFFFFF8000000L	/* high 37 bits */
#define LOW_29		0x000000001FFFFFFFL	/* Low 29 bits */
#define HIGH_35		0xFFFFFFFFE0000000L	/* high 35 bits */
#define LOW_48		0x0000FFFFFFFFFFFFL	/* Low 48 bits */
#define HIGH_16		0xFFFF000000000000L	/* Upper 16-bits */

#define SYSMAP_MASK	HIGH_16
#define SYSMAP_SHIFT	48

/* Used to get the PCI Bus
 * address bits from the EV5
 * address	
 */
#define PCI_DENSE_MEM_MASK 	~3L		 /* Zaps the low two bits too */
#define PCI_SPARSE_IO_MASK 	0x003ffffffL
#define PCI_SPARSE_MEM_MASK 	0x02bffffffL

/* These are used to set bits in the PCI_IO (PCI Sparce I/O Byte) Macro */
#define A_BYTE		00
#define A_WORD		01
#define A_TRI-BYTE	10
#define A_LONGWORD	11
#define A_QUADWORD	11

/* masks for byte fields */
#define BYTE0 		0x000000ff 
#define BYTE1 		0x0000ff00
#define BYTE2 		0x00ff0000
#define BYTE3 		0xff000000

#define sLEFT  0	/* shift left first */
#define sRIGHT 1        /* shift right first */


/* A general Macro to SWIZZLE an address. Its looking for:
 *	x		- the address to swizzle
 *	BASE		- The base address of the memory rehion
 *	Wrd/Lng		- The bits to guide size of data (Byte, word, tribyte, long)
 *	Mask		- Mask of the based on address size
 *	IO_SHIFT	- Distance to shift the address for the other data to fit into
 */
#define BUSMEM_MASK	0x7ffffff
#define BUSIO_MASK	0x1ffffff 



/*********************************************************************
 ***************** DC21171 CSR PHYSICAL ADDRESSES ********************
 *********************************************************************
 *
 *   0 0000 0000 +---------------------------------+	--------
 *               | 				   |        ^
 *               | 				   |	    |
 *               | 				   |	    | 0: Cached Memory
 *   		 |  GB Cached Memory		   |	    | Space
 *               | 				   |	    |
 *               | 				   |	    |
 *               | 				   |	    v
 *  80 0000 0000 +---------------------------------+    --------	-------
 *               | 512MB PCI - Memory		   |	    ^		   ^
 *		 | Sparce Space			   |	    |		   |
 *		 | 				   |	    |		   |
 *		 | 				   |	    |		   |
 *  84 0000 0000 +---------------------------------+	    | PCI - Memory |
 *		 | 				   |	    | Sparce Space |
 *               | 128MB PCI - Memory		   |	    | 740MB Max.   |
 *		 | Sparse Space			   |	    |		   |
 *		 | 				   |	    |		   |
 *  85 0000 0000 +---------------------------------+	    |		   |
 *               | 64MB PCI - Memory		   |	    |		   |
 *		 | Sparse Space			   |	    v		   |
 *  85 8000 0000 +---------------------------------+    --------	   |
 *               | PCI I/O Sparse Space - 64MB     |		   	   |
 *  86 0000 0000 +---------------------------------+    1: UnCached Memory |
 *               | PCI Memory Dense Space - 4GB	   |	   IO Space   	   |
 *		 :				   :		   	   |
 *		 | 				   |		   	   |
 *  87 0000 0000 +---------------------------------+		   	   |
 *               | PCI Config, CIA CSRs, Flash ROM |		   	   |
 *  88 0000 0000 +---------------------------------+			   |
 *		 | EV56 Byte/Word PCI MEM Space 4GB|			   |
 *  89 0000 0000 +---------------------------------+			   |
 *		 | EV56 Byte/Word PCI IO Space 4GB |			   |
 *  8a 0000 0000 +---------------------------------+			   |
 *		 | EV56 Byte/Word PCI CNFG0    4GB |			   |
 *  8b 0000 0000 +---------------------------------+			   |
 *		 | EV56 Byte/Word PCI CNFG1    4GB |			   v
 *		 +---------------------------------+			-------
 *
 *
 */

#define PCI0_DENSE_MEM_MASK	0x86ffffffffL	/* used to establish PCI type	  */
						/* addresses.		          */
#define MAIN_MEM_BASE		0x0000000000L
#define PCI0_SPARSE_MEM_BASE	0x8000000000L	/* 512MB */
#define PCI1_SPARSE_MEM_BASE	0x8400000000L	/* 128MB */
#define PCI2_SPARSE_MEM_BASE	0x8500000000L	/*  64MB */
#define PCIA_SPARSE_IO_BASE	0x8580000000L	/*  32MB */
#define PCIB_SPARSE_IO_BASE	0x85c0000000L	/*  32MB */
#define PCI0_DENSE_MEM_BASE	0x8600000000L	/*   4GB */
#define PCI0_CONFIG_BASE	0x8700000000L	/* PCI Configuration Sparse Space */
#define PCI_SPECIAL_INT_ACK	0x8720000000L	/* PCI -- Sparse Space */
#define CIA_MAIN_CSRS		0x8740000000L	/* CIA MAIN CSRs Pseudo Sparse */
#define CIA_MEMORY_CSRS		0x8750000000L	/* Mem Control CSRs Pseudo Sparse */
#define CIA_PCI_ADDRESS_TRANS	0x8760000000L	/* CIA PCI Address Pseudo Sparse */
#define	PCI_EV56_BW_MEM_BASE	0x8800000000L	/*   4GB byte/word PCI memory */
#define	PCI_EV56_BW_IO_BASE	0x8900000000L	/*   4GB byte/word PCI I/O    */
#define	PCI_EV56_BW_CNFG0_BASE	0x8a00000000L	/*   4GB byte/word PCI,       */
						/*	 config type 0	      */
#define	PCI_EV56_BW_CNFG1_BASE	0x8b00000000L	/*   4GB byte/word PCI,       */
						/*	 config type 1	      */

/* Hardware Specific Register Address Map
 *
 */
#define CIA_CONTROL_REG_BASE	0x8740000000L	/* CIA Control, Diag, error register */
#define CIA_MEM_CONTROL_REG	0x8750000000L	/* CIA Memory Control Register */
#define FLASH_ROM		0x8780000000L	/* Pseudo Sparse	*/

/**************************************************************************
 ************************** General CIA CSRs ******************************
 **************************************************************************
 */

/* Wrong name; not used; changed to CIA_REV				 */
/*#define PCI_REV (CIA_CONTROL_REG_BASE+0x80L)*/ /* PCI Revision	 */

#define CIA_REV  (CIA_CONTROL_REG_BASE+0x80L)	/* CIA ASIC Revision	 */
/*  31                                                8 7             0
   +---------------------------------------------------+---------------+
   |                                                   | cia_rev       |
   |                                                   |               |
   +---------------------------------------------------+---------------+ 	*/
#define Cia_rev 0x000000ffL   /* Specifies the revision of the CIA ASIC  */



#define PCI_LAT	 (CIA_CONTROL_REG_BASE+0xc0L)	/* PCI Latency			*/
/*  31                             16 15              8 7             0
   +---------------------------------+-----------------+---------------+
   |                                 |  latency        |               |
   |                                 |                 |               |
   +---------------------------------------------------+---------------+ 	*/
#define Latency		0x0000ff00L /* PCI master latency timmer in PCI
				      block cycles				*/

#define CIA_CTRL (CIA_CONTROL_REG_BASE+0x100L)	/* CIA Control Reg. 		*/
/* bits in the CIA_CTRL register 						*/
#define Rci_en		0x00000001L
#define Pci_lock_en	0x00000002L
#define Pci_loop_en	0x00000004L
#define Fst_bb_en	0x00000008L
#define Pci_mst_en	0x00000010L
#define Pci_mem_en	0x00000020L
#define Pci_req64_en	0x00000040L
#define Pci_ack64_en	0x00000080L
#define Addr_pe_en	0x00000100L
#define Perr_en		0x00000200L
#define Fill_err_en	0x00000400L
#define Ecc_chk_en	0x00001000L
#define Cack_en_pe	0x00002000L
#define Con_idle_bc	0x00004000L
#define Csr_ioa_bypass	0x00008000L
#define Io_flushreq_en 	0x00010000L
#define Cpu_flushreq_en	0x00020000L
#define Arb_ev5_en	0x00040000L
#define En_arb_link	0x00080000L
#define Rd_type		0x00300000L
#define Rl_type		0x03000000L
#define Rm_type		0x30000000L
				   
/* PCI READ Prefetch Algorithm (see pci_rd, pci_rl & pci_rm above)

   value	algorithm
   +-----+----------------------------------------------------------------------+
   | 00  | Fetch requested LW/QW and remainder of cache block			|
   | 01  | Prefetch next block and no more. Will not cross 8KB page boundry     |
   | 10  | Keep prefetching until PCI transaction completes. Will not cross *KB |
   | 00  | Reserved								|
   +-----+----------------------------------------------------------------------+
 */
   



#define CIA_CNFG (CIA_CONTROL_REG_BASE+0x140)	/* CIA Configuration Reg      */
/* CIA Configuration Register (NEW in Rev 2 of CIA ASIC, NOT in older Revs    */
#define IOA_BWEN	0x001	/* EV56 byte/word IO support enabled          */
#define PCI_MWEN	0x010	/* PCI target monster window enabled          */
#define PCI_DWEN	0x020	/* Second PCI target DMA write buffer enabled */
#define PCI_WLEN	0x100	/* CIA will link consecutive writes into      */
				/*  a single PCI transaction.		      */


#define HAE_MEM	 (CIA_CONTROL_REG_BASE+0x400)	/* Hardware Address Extension
						 * Sparse Space Memory
						 * Init to 0x00002028 will make
						 * all 3 regions contigus starting at
						 * PCI address 0.
						 *
   31      27 26                   15       11 10    8 7                2   0
  +----------+--------------------+-----------+-------+------------------+---+
  | region 1 |  RESERVED          | region 2  | RESERV| region 3         |RSV|
  |          |                    |           |       |                  |   |
  +----------+--------------------+-----------+-------+------------------+---+ */
#define Region3 	0x000000fcL
#define Region2 	0x0000f800L
#define Region1 	0xf8000000L



#define HAE_IO	 (CIA_CONTROL_REG_BASE+0x440L)	/* Hardware Address Extension
						 * Sparse Space I/O Space
						 *
   31          25 24                                                        0
  +--------------+-----------------------------------------------------------+
  |addr_ext      |                                                           |
  |              |                                                           |
  +--------------+-----------------------------------------------------------+ */
#define Addr_ext	0xfc000000L	/* Used to extend the PCI sparce space io
					 * address up to a full 32 bit PCI address.
					 * Set to zero on power up. Settinh HAE_IO
					 * to 0x00400000 will make region A & 
					 * region B consecutive in lower 64MB PCI
					 * IO space.			*/



#define CFG	 (CIA_CONTROL_REG_BASE+0x480L)	/* Configuration Register
  31							               2 1 0
 +----------------------------------------------------------------------+---+
 |                                                                      |Cfg|
 |                                                                      |   |
 +----------------------------------------------------------------------+---+ */
#define Cfg 0x00000003L	/* Used as low two address bits on an access
			 * to PCI Configuration space.			      */



/***************************************************************************
 ******************** Error and Diagnostic Regisres ************************
 ***************************************************************************
 */
#define CIA_DIAG 	 (CIA_CONTROL_REG_BASE+0x2000L)	/* CIA Diag Control Reg*/
#define DIAG_CHECK	 (CIA_CONTROL_REG_BASE+0x3000L)	/* Diag Check Reg      */
#define EIR0		 (CIA_CONTROL_REG_BASE+0x8000L)	/* Error Info Reg      */
#define EIR1		 (CIA_CONTROL_REG_BASE+0x8040L)	/* Error Info Reg      */
#define CIA_ERR		 (CIA_CONTROL_REG_BASE+0x8200L)	/* CIA Error Reg       */
#define ERR_MASK	 (CIA_CONTROL_REG_BASE+0x8280L)	/* CIA Error Mask Reg  */
#define CIA_SYN		 (CIA_CONTROL_REG_BASE+0x8300L)	/* CIA Syndrome reg.   */
#define CIA_MEM0 	 (CIA_CONTROL_REG_BASE+0x8400L)	/* CIA MEM Port Status */
#define CIA_MEM1	 (CIA_CONTROL_REG_BASE+0x8440L)	/* CIA MEM Port Status */
#define CIA_MEM2	 (CIA_CONTROL_REG_BASE+0x8480L)	/* CIA MEM Port Status */
#define CIA_IOP0	 (CIA_CONTROL_REG_BASE+0x8600L)	/* CIA IO Port Status  */
#define CIA_IOP1	 (CIA_CONTROL_REG_BASE+0x8640L)	/* CIA IO Port Status  */
#define PCI_ERR0	 (CIA_CONTROL_REG_BASE+0x8800l)	/* PCI Error Reg 0     */
#define PCI_ERR0_LOCK_STATE	0x00000010
#define PCI_ERR0_CMD		0x0000000f
#define PCI_ERR0_DAC_CYCLE	0x00000020

#define PCI_ERR1	 (CIA_CONTROL_REG_BASE+0x8840L)	/* PCI Error Reg 1     */

/* Bits used in the CIA_DIAG and DIAG_CHECK registers.					*/
#define FROM_WRT_EN 0x1       /* The FROM can only be programmed when this bit is set. 	*/
#define USE_CHECK   0x1 << 1  /* When set use the DIAG_CHECK for ECC. 			*/
#define FPE_PCI     0x1 << 29 /* When set a data parity error is forced on the PCI bus.	*/
#define FPE_CPU_EV5 0x1 << 30 /* When set a parity error is forced on the CPU		*/
	                      /* address/CMD bus when the EV5 is the bus master.	*/
#define FPE_CPU_CIA 0x1 << 31 /* When set a parity error is forced on the CPU		*/
 	                      /* address/CMD bus when the CIA is the bus master.	*/
 
/***************************************************************************
 ******************** System Configuration Registers ***********************
 ***************************************************************************
 */
#define MCR		(CIA_MEMORY_CSRS+0x000L)       	/* mem Config Reg.     */
#define MBA0		(CIA_MEMORY_CSRS+0x600L)       	/* Mem Base addr reg 0 */
#define MBA1		(CIA_MEMORY_CSRS+0x640L)       	/* Mem Base addr reg 1 */
#define MBA2		(CIA_MEMORY_CSRS+0x680L)       	/* Mem Base addr reg 2 */
#define MBA3		(CIA_MEMORY_CSRS+0x6c0L)       	/* Mem Base addr reg 3 */
#define MBA4		(CIA_MEMORY_CSRS+0x700L)       	/* Mem Base addr reg 4 */
#define MBA5		(CIA_MEMORY_CSRS+0x740L)       	/* Mem Base addr reg 5 */
#define MBA6		(CIA_MEMORY_CSRS+0x780L)       	/* Mem Base addr reg 6 */
#define MBA7		(CIA_MEMORY_CSRS+0x7c0L)	/* Mem Base addr reg 7 */
#define MBA8		(CIA_MEMORY_CSRS+0x800L)	/* Mem Base addr reg 8 */
#define MBA9		(CIA_MEMORY_CSRS+0x840L)       	/* Mem Base addr reg 9 */
#define MBA10		(CIA_MEMORY_CSRS+0x880L)       	/* Mem Base addr reg 10*/
#define MBA11		(CIA_MEMORY_CSRS+0x8c0L)       	/* Mem Base addr reg 11*/
#define MBA12		(CIA_MEMORY_CSRS+0x900L)       	/* Mem Base addr reg 12*/
#define MBA13		(CIA_MEMORY_CSRS+0x940L)       	/* Mem Base addr reg 13*/
#define MBA14		(CIA_MEMORY_CSRS+0x980L)       	/* Mem Base addr reg 14*/
#define MBA15		(CIA_MEMORY_CSRS+0x9c0L)       	/* Mem Base addr reg 15*/
#define TMG0		(CIA_MEMORY_CSRS+0xb00L)       	/* Mem Timing info     */
#define TMG1		(CIA_MEMORY_CSRS+0xb40L)       	/* Mem Timing info     */
#define TMG2		(CIA_MEMORY_CSRS+0xb80L)       	/* Mem Timing info     */

/***************************************************************************
 ********************* PCI ADDRESS and Scatter/Gather Registers ************
 ***************************************************************************
 */
#define SG_TBI		(CIA_PCI_ADDRESS_TRANS+0x100L)	/* Scatter/Gather Translation 

							 * Buffer Address
							 */
#define INVAL_ALL_TLB		0x3;
#define INVAL_UNLOCKED_TLB	0x2;
#define INVAL_LOCKED_TLB	0x1;

#define W_BASE0		(CIA_PCI_ADDRESS_TRANS+0x400L)	/* Window Base0		*/
#define W_MASK0		(CIA_PCI_ADDRESS_TRANS+0x440L)	/* Window Mask 0	*/
#define TBR0		(CIA_PCI_ADDRESS_TRANS+0x480L)	/* Translation Base0	*/
#define MEMCS_ENABLE	0x04				/* PCI-EISA PC compatability */
#define W_BASE1		(CIA_PCI_ADDRESS_TRANS+0x500L)	/* Window Base 1	*/
#define W_MASK1		(CIA_PCI_ADDRESS_TRANS+0x540L)	/* Window Mask 1	*/
#define TBR1		(CIA_PCI_ADDRESS_TRANS+0x580L)	/* Translation Base 1	*/
#define W_BASE2		(CIA_PCI_ADDRESS_TRANS+0x600L)	/* Window Base 2	*/
#define W_MASK2		(CIA_PCI_ADDRESS_TRANS+0x640L)	/* Window Mask 2	*/
#define TBR2		(CIA_PCI_ADDRESS_TRANS+0x680L)	/* Translation Base 2	*/
#define W_BASE3		(CIA_PCI_ADDRESS_TRANS+0x700L)	/* Window Base 3	*/
#define W_MASK3		(CIA_PCI_ADDRESS_TRANS+0x740L)	/* Window Mask 3	*/
#define TBR3		(CIA_PCI_ADDRESS_TRANS+0x780L)	/* Translation Base 3	*/
#define W_DAC		(CIA_PCI_ADDRESS_TRANS+0x7c0L)	/* Window DAC Base	*/
#define WINDOW_DIRECT_MAPPED	0x00000L
#define WINDOW_DAC_ENABLE	0x08			/* DAC enable bit	*/
#define WINDOW_ENABLE   	0x01			/* Enable window 	*/
#define WINDOW_SCATTER_GATHER 	0x2			/* SG window bit	*/

/*
 * Structure used to make coding easier for DMA window setup
 * Note: 1st element is an unsigned int, so ptr-based register
 *	 manipulations are stl/ldl's, not stq/ldq's.
 */
struct dc21171_pci_addr_trans_regs {
	unsigned int	int_element;	/* offset 000 */
	char            pad1[0x3fc];
        struct  win_regs {              /* offset 400 -> 7C0 */
                        unsigned int    wbase;		/* 00 */
                        char            pad2[0x3c];
                        unsigned int    wmask;		/* 40 */
                        char            pad4[0x3c];
                        unsigned int    tbase;		/* 80 */
                        char            pad6[0x3c];
                        unsigned int    wdac;   /* C0 -- only for window 3 */
                        char            pad8[0x3c];
        }       win_regs[4];
};


/*****************************************************************************
 ********************* Address Translation Registers *************************
 *****************************************************************************
 */
#define NUM_SG_TLB_TAGS 8
#define LTB_TAG0	 (CIA_PCI_ADDRESS_TRANS+0x800L)	/* Lockable Trans Buf Tag */
#define LTB_TAG1	 (CIA_PCI_ADDRESS_TRANS+0x840L)	/* Lockable Trans Buf Tag */
#define LTB_TAG2	 (CIA_PCI_ADDRESS_TRANS+0x880L)	/* Lockable Trans Buf Tag */
#define LTB_TAG3	 (CIA_PCI_ADDRESS_TRANS+0x8c0L)	/* Lockable Trans Buf Tag */
#define TB_TAG0		 (CIA_PCI_ADDRESS_TRANS+0x900L)	/* Translation Buf Tag  */
#define TB_TAG1		 (CIA_PCI_ADDRESS_TRANS+0x940L)	/* Translation Buf Tag  */
#define TB_TAG2		 (CIA_PCI_ADDRESS_TRANS+0x980L)	/* Translation Buf Tag  */
#define TB_TAG3		 (CIA_PCI_ADDRESS_TRANS+0x9c0L)	/* Translation Buf Tag  */
#define TB0_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1000L)/* Translation Buf Page */
#define TB0_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1040L)/* Translation Buf Page */
#define TB0_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1080L)/* Translation Buf Page */
#define TB0_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x10c0L)/* Translation Buf Page */
#define TB1_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1100L)/* Translation Buf Page */
#define TB1_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1140L)/* Translation Buf Page */
#define TB1_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1180L)/* Translation Buf Page */
#define TB1_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x11c0L)/* Translation Buf Page */
#define TB2_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1200L)/* Translation Buf Page */
#define TB2_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1240L)/* Translation Buf Page */
#define TB2_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1280L)/* Translation Buf Page */
#define TB2_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x12c0L)/* Translation Buf Page */
#define TB3_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1300L)/* Translation Buf Page */
#define TB3_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1340L)/* Translation Buf Page */
#define TB3_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1380L)/* Translation Buf Page */
#define TB3_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x13c0L)/* Translation Buf Page */
#define TB4_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1400L)/* Translation Buf Page */
#define TB4_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1440L)/* Translation Buf Page */
#define TB4_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1480L)/* Translation Buf Page */
#define TB4_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x14c0L)/* Translation Buf Page */
#define TB5_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1500L)/* Translation Buf Page */
#define TB5_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1540L)/* Translation Buf Page */
#define TB5_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1580L)/* Translation Buf Page */
#define TB5_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x15c0L)/* Translation Buf Page */
#define TB6_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1600L)/* Translation Buf Page */
#define TB6_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1640L)/* Translation Buf Page */
#define TB6_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1680L)/* Translation Buf Page */
#define TB6_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x16c0L)/* Translation Buf Page */
#define TB7_PAGE0	 (CIA_PCI_ADDRESS_TRANS+0x1700L)/* Translation Buf Page */
#define TB7_PAGE1	 (CIA_PCI_ADDRESS_TRANS+0x1740L)/* Translation Buf Page */
#define TB7_PAGE2	 (CIA_PCI_ADDRESS_TRANS+0x1780L)/* Translation Buf Page */
#define TB7_PAGE3	 (CIA_PCI_ADDRESS_TRANS+0x17c0L)/* Translation Buf Page */


#ifdef notdef /* Don't think I need these any more? */
#define IO_B(x)  (PCIA_SPARSE_IO_BASE  |       (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define IO_W(x)  (PCIA_SPARSE_IO_BASE  | Wrd | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define IO_L(x)	 (PCIA_SPARSE_IO_BASE  | Lng | (((long)(x) & BUSIO_MASK) << IO_SHIFT))

#define MEM_B(x) (PCI0_SPARSE_MEM_BASE |       (((long)(x) & BUSMEM_MASK) << IO_SHIFT))
#define MEM_W(x) (PCI0_SPARSE_MEM_BASE | Wrd | (((long)(x) & BUSMEM_MASK) << IO_SHIFT))
#define MEM_L(x) (PCI0_SPARSE_MEM_BASE | Lng | (((long)(x) & BUSMEM_MASK) << IO_SHIFT))
#endif /* notdef */


/*
 * This is a table index's that will be used to implement the sysmap
 * translations for dc21171.  The sysmap bits set in the address will
 * be an index into this table which contains the actual bits to OR
 * back into the address.
 *
 * EV56 adds 4 new maps to allow byte/word addressing. These maps are
 * in sysmap_tbl, but are never passed to/from any routine. SYSMAP_TBL_SIZE
 * stays at 9, so routines will fail if EV56 maps used directly. Refer to
 * sysmap_tbl index size check early in read_io_port() for an example.
 * One exception is iohandle_to_phys(). It accepts byte/word IO handles.
 */
#define SYSMAP_TBL_SIZE      9	/* CAUTION: yes, I mean 9 instead of 13! */
#define SYSMAP_EV56TBL_SIZE 13	/* (see above comments) 		 */
#define DC21171_MAIN_MEM 		1L
#define DC21171_PCI0_SPARSE_MEM 	2L
#define DC21171_PCI1_SPARSE_MEM 	3L
#define DC21171_PCI2_SPARSE_MEM 	4L
#define DC21171_PCIA_SPARSE_IO 		5L
#define DC21171_PCIB_SPARSE_IO 		6L
#define DC21171_PCI0_CONFIG 		7L
#define DC21171_PCI0_DENSE_MEM 		8L
#define DC21171_PCI_EV56_BW_MEM         9L
#define DC21171_PCI_EV56_BW_IO         10L
#define DC21171_PCI_EV56_BW_CNFG0      11L
#define DC21171_PCI_EV56_BW_CNFG1      12L


#define	DC21171_PCI_ADDR_TO_HANDL(x)	((x) | (DC21171_PCIA_SPARSE_IO << SYSMAP_SHIFT))
#define	DC21171_BW_PCI_ADDR_TO_HANDL(x)	((x) | (DC21171_PCI_EV56_BW_IO << SYSMAP_SHIFT))

/* Begin Pyxis specific */
#define PYXIS_INT_REQ_PA	0x87a0000000    /* interrupt request reg */
#define PYXIS_INT_MASK_PA	0x87a0000040
#define PYXIS_GPO		0x87a0000180	/* general purpose outputs */
u_long pyxis_intrdsabl(int i);
u_long pyxis_intrenabl(int i);
void pyxis_pci_eoi(shared_intr_info_t *sip);
/* End Pyxis specific */

/* DMA Window setup defines */

/* Set window base to be 3 GIG for all window sizes.  This
 * is done to the window that is sized on memory size. All
 * window sized less than or equal to 1 Gig will be based 
 * at a natural multiple boundry at 3 GIG.  If the memory 
 * is big we hold the window size down to 3 GIG.
 */

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
#define	WIN_2GIG	11
#define	WIN_4GIG	12
#define	WIN_4GIG_SG	13


/*
 * Possible window sizes
 */
#define M_0_MEG			0x000000000
#define M_1_MEG			0x000100000
#define M_2_MEG			0x000200000
#define M_4_MEG			0x000400000
#define M_8_MEG			0x000800000
#define M_16_MEG		0x001000000
#define M_32_MEG		0x002000000
#define M_64_MEG		0x004000000
#define M_128_MEG		0x008000000
#define M_256_MEG		0x010000000
#define M_512_MEG		0x020000000
#define M_1_GIG			0x040000000
#define M_2_GIG			0x080000000
#define M_3_GIG			0x0c0000000
#define M_4_GIG			0x100000000

#define WINDOW_START_MASK	0x7ff00000L

#define WINDOW_SIZE(x)	(dc21171_window_size[x])
#define WINDOW_BASE(Size_index)	 ((1UL << (Size_index)) << 20)
#define WINDOW_MASK(Wndw_index) (((1 << (Wndw_index)) - 1) << 20)

struct dc21171_win_sel {
	u_int	type;		/* Direct, SG; En/disable; DAC	*/
	u_int	size;		/* based on WIN_xxxx index 	*/
	u_long	pci_base;	/* PCI base addr. of window 	*/
	u_long	tbase;		/* TBASE for s/g or direct 	*/
};

#define DC21171_WIN_MAX 5
#define DC21171_DMA_PREFETCH 0x100

#define DC21171_ADDRLIM_WIN 0
/* note: dma window 1 or 2 used by dc21171/pyxis platforms;
 *	 the following define is only used for dma_map_info
 *	 setup.  Pyxis (miata/eb164) requires dma window 2
 *	 for sg-tlb flush fix.
 */
#define DC21171_PYXIS_SG_WIN    3
/*
 *  note: for 64-bit DMA addressing support, all dma windows
 *        need to be setup. The 32-bit SG window will now be
 *        window 2, 64-bit SG will be window 3, and the monster
 *        window (64-bit DIRECT map) will be "window 4".
 *        The above comment points to changes that are needed 
 *        in eb164.c concerning dma window 2 sg-tlb flush.
 */
#define DC21171_DIRECT_WIN      1
#define DC21171_SG_WIN          2
#define DC21171_SG64_WIN        3
#define DC21171_DIRECT64        4

/* PCI base address values of direct-map DMA windows    */
#define DC21171_32B_DIRECT_MAP_BASE     (u_long)(1UL << 30)     /* 1GB */
#define DC21171_64B_DIRECT_MAP_BASE     (u_long)(1UL << 40)     /* 1TB */

#define DC21171_64B_SG_MAP_BASE         (u_long)(1UL << 36)     /* 64GB */

/*
 * extern's for knxx/ebxx modules to use
 */
/* extern int		dc21171_no_32b_direct_map; */
extern int              dc21171_always_sg;
extern int		dc21171_no_64b_direct_map;
extern int		dc21171_32bit_direct_wsize;
extern int		dc21171_64bit_direct_wsize;
extern struct dc21171_win_sel dc21171_win_sel[];
extern u_long		dc21171_window_mask[];
extern struct dma_map_info dc21171_dma_map_info[];
extern vm_offset_t	dc21171_sg_ctl;
extern vm_offset_t	dc21171_isa_sg_ctl;
extern vm_offset_t	dc21171_sg64_ctl;

void dc21171_choose_dma_windows();
void dc21171_dma_map_init();
dma_map_info_t dc21171_dma_get_maps(struct bus *);

#endif /* DC21171_H */

