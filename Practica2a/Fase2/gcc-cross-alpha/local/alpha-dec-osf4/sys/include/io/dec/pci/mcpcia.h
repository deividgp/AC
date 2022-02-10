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
 * @(#)$RCSfile: mcpcia.h,v $ $Revision: 1.1.21.2 $ (DEC) $Date: 1998/05/01 17:04:46 $
 */

#ifndef __IO_DEC_PCI_MCPCIA_H__
#define __IO_DEC_PCI_MCPCIA_H__

#include <sys/types.h>
#include <hal/shared_intr.h>	/* for mcpcia_info struct */

/*
 * ----------------------
 * MCBUS-PCIA Address Map:
 * ----------------------
 *
 * I/O Space Per PCI Node (8GBytes per)
 * ------------------------------------
 * (8+x)8 0000 0000 - (8+x)9 FFFF FFFF	- I/O Space for PCI0
 * (8+x)A 0000 0000 - (8+x)B FFFF FFFF	- I/O Space for PCI1
 * (8+x)C 0000 0000 - (8+x)D FFFF FFFF	- I/O Space for PCI2
 * (8+x)E 0000 0000 - (8+x)F FFFF FFFF	- I/O Space for PCI3
 *
 * where x={0,1,2,3,4,5,6,7} for GID number
 *
 * for single MCBUS, RAWHIDE System, the address space becomes:
 * F8 0000 0000 - F9 FFFF FFFF  - I/O Space for PCI0
 * FA 0000 0000 - FB FFFF FFFF  - I/O Space for PCI1
 * FC 0000 0000 - FD FFFF FFFF  - I/O Space for PCI2
 * FE 0000 0000 - FF FFFF FFFF  - I/O Space for PCI3
 *
 *
 * CPU to PCI Address Mapping:
 * ---------------------------
 * 
 * +---+-------+-------+--+--+--+--+--+--+---------------+----------+-----+
 * | 1 |  GID  |  MID  |  |  |  |  |  |  | Byte Aligned  | Byte Len | Zero|
 * |   |       |       |  |  |  |  |  |  | I/O Address	 |   Field  |     |
 * +---+-------+-------+--+--+--+--+--+--+---------------+----------+-----+
 *  39  38   36 35   33 32 31 30 29 28 27 26            5 4        3  2  0
 *   
 * <39> - I/O Select (Always 1 for direct I/O access)
 *
 * <38-36> - Global Bus slot # (MCBUS #)
 *	GID slot #0->7 (MCBUS #0->7)
 *
 * <35-33> - MCBUS Slot #
 *	MCBUS slot 0->7 
 *	
 * <32-27> - PCI Address Space
 *	0.xxxxx = Sparse Memory Space   (  4GB on MCBUS; 128MB on PCI)
 *	1.0xxxx = Dense Memory Space    (  2GB on MCBUS;   2GB on PCI)
 *	1.10xxx = Sparse IO Space       (  1GB on MCBUS;  32MB on PCI)
 *	1.110xx = Sparse Config Space   (512MB on MCBUS;  16MB on PCI)
 *	1.1110x = PCI Bridge CSR Space  (256MB on MCBUS) -- Sparse-mapped!
 *	1.11110 = Interrupt Acknowledge (128MB on MCBUS)
 *	1.11111 = Unused		(128MB on MCBUS)
 */

/*
 * ----------------------
 * MCBUS-PCIA Address Map: (continued)
 * ----------------------
 *
 * ------------------------------------------------------------
 * Cpu to PCI Address Mapping for MCBUS-PCIy Bridge on MCBUS x:
 * ------------------------------------------------------------
 *
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * (8+x)(8+y*2).0000.0000	0000.0000 - 00FF.FFFF	PCIy Sparse Memory Space
 * - (8+x)(8+y*2).1FFF.FFFF				 (fixed, lower 16MB)
 *
 * (8+x)(8+y*2).2000.0000	0100.0000 - 07FF.FFFF	PCIy Sparse Memory Space
 * - (8+x)(8+y*2).FFFF.FFFF				 (variable, offset = 0)
 * 
 * (8+x)(9+y*2).0000.0000       0000.0000 - 7FFF.FFFF 	PCIy Dense Memory Space
 * - (8+x)(9+y*2).7FFF.FFFF  or	8000.0000 - FFFF.FFFF      if HAE_DENSE_MEM = 1
 *
 * (8+x)(9+y*2).8000.0000	0000.0000 - 0000.FFFF	PCIy Sparse IO Space
 * - (8+x)(9+y*2).801F.FFFF				 (fixed, lower 64K)
 *
 * (8+x)(9+y*2).8020.0000	0001.0000 - 01FF.FFFF	PCIy Sparse IO Space
 * - (8+x)(9+y*2).BFFF.FFFF				 (variable, offset = 0)
 *
 * (8+x)(9+y*2).C000.0000	0000.0000 - 0FFF.FFFF	PCIy Config Space (16MB)
 * - (8+x)(9+y*2).DFFF.FFFF
 *
 * (8+x)(9+y*2).E000.0000		N/A		PCIy-Bridge CSR Space (8MB)
 * - (8+x)(9+y*2).EFFF.FFFF
 *
 * (8+x)(9+y*2).F000.0000		N/A		Unused
 * - (8+x)(9+y*2).F000.3EFF
 * 
 * (8+x)(9+y*2).F000.3F00,		N/A		PCIy Interrupt ACK0
 * (8+x)(9+y*2).F000.3F40				PCIy INteruppt ACK1
 * 
 * (8+x)(9+y*2).F000.3F80		N/A		Unused
 * - (8+x)(9+y*2).FFFF.FFFF
 *
 */

/*
 * ----------------------
 * MCBUS-PCIA Address Map: (continued)
 * ----------------------
 *
 * for single MCBUS, RAWHIDE System, the address spaces become:
 * GID=7, PCI bus0 (MID=100)
 * -------------------------
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * F8.0000.0000 - F8.1FFF.FFFF	0000.0000 - 00FF.FFFF	PCI0 Sparse Memory Space
 * 							 (fixed, lower 16MB)
 * F8.2000.0000	- F8.FFFF.FFFF	0100.0000 - 07FF.FFFF	PCI0 Sparse Memory Space
 * 							 (variable, offset = 0)
 * F9.0000.0000 - F9.7FFF.FFFF	0000.0000 - 7FFF.FFFF 	PCI0 Dense Memory Space
 * 			     or	8000.0000 - FFFF.FFFF      if HAE_DENSE_MEM = 1
 * F9.8000.0000	- F9.801F.FFFF	0000.0000 - 0000.FFFF	PCI0 Sparse IO Space
 * 							 (fixed, lower 64K)
 * F9.8020.0000	- F9.BFFF.FFFF	0001.0000 - 01FF.FFFF	PCI0 Sparse IO Space
 * 							 (variable, offset = 0)
 * F9.C000.0000	- F9.DFFF.FFFF	0000.0000 - 0FFF.FFFF	PCI0 Config Space (16MB)
 * F9.E000.0000	- F9.EFFF.FFFF		N/A		PCI0-Bridge CSR Space (8MB)
 * F9.F000.0000	- F9.F000.3EFF		N/A		Unused
 * F9.F000.3F00, F9.F000.3F40		N/A		PCI0 Interrupt ACK0, ACK1
 * F9.F000.3F80	- F9.FFFF.FFFF		N/A		Unused
 *
 * 
 * for single MCBUS, RAWHIDE System, the address spaces become:
 * GID=7, PCI bus1 (MID=101)
 * -------------------------
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * FA.0000.0000 - FA.1FFF.FFFF	0000.0000 - 00FF.FFFF	PCI1 Sparse Memory Space
 * 							 (fixed, lower 16MB)
 * FA.2000.0000	- FA.FFFF.FFFF	0100.0000 - 07FF.FFFF	PCI1 Sparse Memory Space
 * 							 (variable, offset = 0)
 * FB.0000.0000 - FB.7FFF.FFFF	0000.0000 - 7FFF.FFFF 	PCI1 Dense Memory Space
 * 			     or	8000.0000 - FFFF.FFFF      if HAE_DENSE_MEM = 1
 * FB.8000.0000	- FB.801F.FFFF	0000.0000 - 0000.FFFF	PCI1 Sparse IO Space
 * 							 (fixed, lower 64K)
 * FB.8020.0000	- FB.BFFF.FFFF	0001.0000 - 01FF.FFFF	PCI1 Sparse IO Space
 * 							 (variable, offset = 0)
 * FB.C000.0000	- FB.DFFF.FFFF	0000.0000 - 0FFF.FFFF	PCI1 Config Space (16MB)
 * FB.E000.0000	- FB.EFFF.FFFF		N/A		PCI1-Bridge CSR Space (8MB)
 * FB.F000.0000	- FB.F000.3EFF		N/A		Unused
 * FB.F000.3F00, FB.F000.3F40		N/A		PCI1 Interrupt ACK0, ACK1
 * FB.F000.3F80	- FB.FFFF.FFFF		N/A		Unused
 *
 */

/*
 * ----------------------
 * MCBUS-PCIA Address Map: (continued)
 * ----------------------
 *
 * for single MCBUS, RAWHIDE System, the address spaces become:
 * GID=7, PCI bus2 (MID=110)
 * -------------------------
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * FC.0000.0000 - FC.1FFF.FFFF	0000.0000 - 00FF.FFFF	PCI2 Sparse Memory Space
 * 							 (fixed, lower 16MB)
 * FC.2000.0000	- FC.FFFF.FFFF	0100.0000 - 07FF.FFFF	PCI2 Sparse Memory Space
 * 							 (variable, offset = 0)
 * FD.0000.0000 - FD.7FFF.FFFF	0000.0000 - 7FFF.FFFF 	PCI3 Dense Memory Space
 * 			     or	8000.0000 - FFFF.FFFF      if HAE_DENSE_MEM = 1
 * FD.8000.0000	- FD.801F.FFFF	0000.0000 - 0000.FFFF	PCI2 Sparse IO Space
 * 							 (fixed, lower 64K)
 * FD.8020.0000	- FD.BFFF.FFFF	0001.0000 - 01FF.FFFF	PCI2 Sparse IO Space
 * 							 (variable, offset = 0)
 * FD.C000.0000	- FD.DFFF.FFFF	0000.0000 - 0FFF.FFFF	PCI2 Config Space (16MB)
 * FD.E000.0000	- FD.EFFF.FFFF		N/A		PCI2-Bridge CSR Space (8MB)
 * FD.F000.0000	- FD.F000.3EFF		N/A		Unused
 * FD.F000.3F00, FD.F000.3F40		N/A		PCI2 Interrupt ACK0, ACK1
 * FD.F000.3F80	- FD.FFFF.FFFF		N/A		Unused
 * 
 * 
 * for single MCBUS, RAWHIDE System, the address spaces become:
 * GID=7, PCI bus3 (MID=111)
 * -------------------------
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * FE.0000.0000 - FE.1FFF.FFFF	0000.0000 - 00FF.FFFF	PCI3 Sparse Memory Space
 * 							 (fixed, lower 16MB)
 * FE.2000.0000	- FE.FFFF.FFFF	0100.0000 - 07FF.FFFF	PCI3 Sparse Memory Space
 * 							 (variable, offset = 0)
 * FF.0000.0000 - FF.7FFF.FFFF	0000.0000 - 7FFF.FFFF 	PCI3 Dense Memory Space
 * 			     or	8000.0000 - FFFF.FFFF      if HAE_DENSE_MEM = 1
 * FF.8000.0000	- FF.801F.FFFF	0000.0000 - 0000.FFFF	PCI3 Sparse IO Space
 * 							 (fixed, lower 64K)
 * FF.8020.0000	- FF.BFFF.FFFF	0001.0000 - 01FF.FFFF	PCI3 Sparse IO Space
 * 							 (variable, offset = 0)
 * FF.C000.0000	- FF.DFFF.FFFF	0000.0000 - 0FFF.FFFF	PCI3 Config Space (16MB)
 * FF.E000.0000	- FF.EFFF.FFFF		N/A		PCI3-Bridge CSR Space (8MB)
 * FF.F000.0000	- FF.F000.3EFF		N/A		Unused
 * FF.F000.3F00, FF.F000.3F40		N/A		PCI3 Interrupt ACK0, ACK1
 * FF.F000.3F80	- FF.FFFF.FFFF		N/A		Unused (and some rsvd by EV5)
 *	
 */


/*
 * MC-PCI Bus Bridge CSRs
 *
 * Address Map Overview:
 *
 * Offset		Selected Space
 * ----------------	-------------------------------------------------
 * 0000.0000		General config, control, diag, error logging regs.
 * 0000.1000		PCI Error Status
 * 0000.1300		PCI Scatter/Gather Regs.
 * 0000.1800		Scatter/Gather TLB Regs.
 * 0000.4000		MDPA Error Status & Diagnostic Control
 * 0000.8000		MDPB Error Status & Diagnostic Control
 * 000E.0000 - 		Flash Rom Space -- 
 * 000F.FFFF			offset address into PCI Dense Mem Space
 * 1000.3F00		Interrupt Acknowledge
 *
 */

struct mcpcia_regs
{
	unsigned int	pci_rev;	/* offset 000 */
	char		pad2[0x3c];
	unsigned int	whoami;		/* offset 040 */
	char		pad4[0x3c];
	unsigned int	pci_lat;	/* offset 080 */
	char		pad6[0x7c];
	unsigned int	cap_ctrl;	/* offset  100 */
	char		pad8[0x1fc];
	unsigned int	perf_mon;	/* offset  300 */
	char		pad10[0x3c];
	unsigned int	perf_cont;	/* offset  340 */
	char		pad12[0xbc];
	unsigned int	hae_mem;	/* offset  400 */
	char		pad14[0x3c];
	unsigned int	hae_io;		/* offset  440 */
	char		pad16[0x3c];
	unsigned int	iack_sc;	/* offset  480 */
	char		pad18[0x3c];
	unsigned int	hae_dense;	/* offset  4C0 */
	char		pad20[0x3c];
	unsigned int	int_ctl;	/* offset  500 */
	char		pad22[0x3c];
	unsigned int	int_req;	/* offset  540 */
	char		pad24[0x3c];
	unsigned int	int_targ;	/* offset  580 */
	char		pad26[0x3c];
	unsigned int	int_adr;	/* offset  5C0 */
	char		pad28[0x3c];
	unsigned int	int_adr_ext;	/* offset  600 */
	char		pad30[0x3c];
	unsigned int	int_mask0;	/* offset  640 */
	char		pad32[0x3c];
	unsigned int	int_mask1;	/* offset  680 */
	char		pad34[0x7c];
	unsigned int	cap_diag;	/* offset  700 */
	char		pad36[0x3c];
	unsigned int	scratch;	/* offset  740 */
	char		pad38[0xbc];
	unsigned int	mc_err0;	/* offset  800 */
	char		pad40[0x3c];
	unsigned int	mc_err1;	/* offset  840 */
	char		pad42[0x3c];
	unsigned int	cap_err;	/* offset  880 */
	char		pad44[0x7bc];
	unsigned int	pci_err1;	/* offset 1040 */
	char		pad46[0x2bc];
	unsigned int	sg_tbia;	/* offset 1300 */
	char		pad48[0x3c];
	unsigned int	hbase;		/* offset 1340 */
	char		pad50[0xbc];
	struct	win_regs {		/* offset 1400 -> 17C0 */
			unsigned int	wbase;
			char		pad2[0x3c];
			unsigned int	wmask;
			char		pad4[0x3c];
			unsigned int	tbase;
			char		pad6[0x3c];
			unsigned int	wdac;	/* only for window 3 */
			char		pad8[0x3c];
	}	win_regs[4];
	struct	tb_tag_regs {		/* offset 1800 -> 19C0	*/
			unsigned int	tb_tag;
			char		pad2[0x3c];
	}	tb_tag_regs[8];
	struct	tb_page_regs {		/* offset 2000 -> 27C0	*/
			unsigned int	tb_page;
			char		pad2[0x3c];
	}	tb_page_regs[8][4];
	char		pad156[0x1800];
	unsigned int	mdpa_stat;	/* offset 4000 */
	char		pad158[0x3c];
	unsigned int	mdpa_syn;	/* offset 4040 */
	char		pad160[0x3c];
	unsigned int	mdpa_diag;	/* offset 4080 */
	char		pad162[0x3e7c];
	unsigned int	mdpb_stat;	/* offset 8000 */
	char		pad164[0x3c];
	unsigned int	mdpb_syn;	/* offset 8040 */
	char		pad166[0x3c];
	unsigned int	mdpb_diag;	/* offset 8080 */
/* -- for the record -- */
#ifdef for_completeness
	char		pad168[0xfffbe7c];
	unsigned int	int_ack0;	/* offset 1000.3F00 */
	char		padi170[0x3c];
	unsigned int	int_ack1;	/* offset 1000.3F40 */
#endif	/* for_completeness */
};

/*
 * Register bit fields in MCBUS-PCI Bridge 
 */
/*
 * PCI_REV register
 */
#define CAP_REV			0x0000000F
#define HORSE_REV		0x000000F0
#define SADDLE_REV		0x00000F00
#define SADDLE_TYPE		0x00007000
#define MCPCIA_EISA_PRESENT	0x00008000
/*
 * WHOAMI register
 */
#define BCACHE_SIZE		0x00000007
#define	CPU_INFO_VALID		0x00000080
#define	CPU_INFO_MASK		0x000000FF
#define	CPU_INFO_SHIFT		6
#define	UNCACHED_CPU		0x00000000
#define CACHED_CPU_1MB  	0x00000001
#define CACHED_CPU_2MB		0x00000002
#define CACHED_CPU_4MB		0x00000003
/*
 * INT_MASK register
 */
#define MCPCIA_EISA_INTR_ENABLE	(1<<16)			/* BIT 16 */
#define MCPCIA_HARD_ERR		0x800000		/* bit 23 */
#define MCPCIA_SOFT_ERR		0x400000		/* bit 22 */
#define MCPCIA_I2C_BUS_ERR	0x040000		/* bit 18 */

/*
 * MC-PCIA Address Space defines & declarations 
 */

/*
 * Alpha swizzle-address definitions
 */
/* These are used to set bits in the size field of swizzle-address format */
#define A_BYTE		00
#define A_WORD		01
#define A_TRI-BYTE	10
#define A_LONGWORD	11
#define A_QUADWORD	11

#define	MCPCIA_IO_SHIFT	(5)
#define	IO_STRIDE	(0x40)
#define	IO_BYTE_STRIDE	(0x10)
#define	WIDTH_MASK	(0x18)
#define	MCPCIA_WIDTH_SHIFT	(MCPCIA_IO_SHIFT - 2)
#define Byt		((long)0 << (WIDTH_SHIFT))
#define Wrd		((long)1 << (WIDTH_SHIFT))
#define Tri		((long)2 << (WIDTH_SHIFT))
#define Lng		((long)3 << (WIDTH_SHIFT))

#define IO_ALIGN_MASK	0xffffffffffffff9fL 	/* aligns swizzled address to longword boundary */

/*
 * DGD_TODO:
 *    A general Macro to SWIZZLE an address. Its looking for:
 *	x		- the address to swizzle
 *	BASE		- The base address of the memory region
 *	Wrd/Lng		- The bits to guide size of data (Byte, word, 
 *			  tribyte, long)
 *	Mask		- Mask of the based on address size
 *	IO_SHIFT	- Distance to shift the address for the other data 
 *			  to fit into
 */

#define IOA_OKAY	0
#define	IOA_ERROR	-1

/*
 * IOHANDLE-related definitions
 */
#define LOW_22			0x00000000003FFFFFL	/* Low 22 bits   */
#define LOW_24			0x0000000000FFFFFFL	/* Low 24 bits   */
#define LOW_25			0x0000000001FFFFFFL	/* Low 25 bits   */
#define LOW_27			0x0000000007FFFFFFL	/* Low 27 bits   */
#define LOW_31			0x000000007FFFFFFFL	/* Low 31 bits   */
#define LOW_32			0x00000000FFFFFFFFL	/* Low 32 bits   */
#define HIGH_32			0xFFFFFFFF00000000L	/* Upper 32-bits */
#define MCPCIA_BUSMEM_MASK	LOW_32
#define MCPCIA_BUSIO_MASK	(LOW_32 >> 2)
#define MCPCIA_SYSMAP_MASK	HIGH_32
#define MCPCIA_SYSMAP_SHIFT	8
#define MCBUS_GID_MASK		0x0000007000000000L
#define MCBUS_GID_SHIFT		36	
#define MCBUS_MID_MASK		0x0000000E00000000L
#define MCBUS_MID_SHIFT		33	
#define MCBUS_BUS_SPACE_MASK	

#define sLEFT  0	/* shift left first */
#define sRIGHT 1        /* shift right first */
#define NUKE_BIT31 	0xffffffff7fffffffL 
#define BIT31		0x80000000
#define BIT24		0x01000000


/*
 * The following are offsets from the adapter base address.
 * The adapter base address is a function of the slot (MID #) on the 
 * MCBUS that the MC-PCI bridge is in.
 */
#define MCPCIA_SPARSE_MEM_BASE	0x000000000L
#define MCPCIA_DENSE_MEM_BASE	0x100000000L	
#define MCPCIA_SPARSE_IO_BASE	0x180000000L
#define MCPCIA_CONFIG_BASE	0x1C0000000L	/* PCI Config Sparse Space */
#define MCPCIA_BRIDGE_CSR_BASE	0x1E0000000L
#define MCPCIA_INTR_ACK_BASE	0x1F0000000L

#define MCPCIA_SPARSE_MEM_SPACE_MASK	0x100000000L	/* A<32>	*/
#define MCPCIA_SPARSE_IO_SPACE_MASK	0x1C0000000L	/* A<32:30>	*/
#define MCPCIA_SPARSE_CNFG_SPACE_MASK	0x1E0000000L	/* A<32:29>	*/
#define MCPCIA_DENSE_MEM_SPACE_MASK	0x180000000L	/* A<32:31> 	*/
#define MCPCIA_DENSE_ADDR_MASK		LOW_31	
#define MCPCIA_IOBUS_MASK		(1L << 39)	/* A<39>	*/

/* 
 * PCI-centric defines for MCBUS-PCI Adapter
 */
#define	MCPCIA_PCI_MAX_SLOT		6
#define MCPCIA_PCI_INTR_INFO_SIZE	MCPCIA_PCI_MAX_SLOT*4 /* 4 INTx's per slot */
#define MCPCIA_8259_INTR_INFO_SIZE	16
#define EISA_IO_ADDR_BASE		0x000000F980000000L
#define MCPCIA_EISA_ADDR_TO_HANDL(x)	\
				((EISA_IO_ADDR_BASE << MCPCIA_SYSMAP_SHIFT) | x)
#define MCPCIA_EISA_BRIDGE_SLOT		1
#define MCPCIA_MAX_PER_MCBUS		4
#define MCPCIA_KEYB_IRQ			1
#define MCPCIA_MOUSE_IRQ		12
#define MCPCIA_GPC_CONFIG_HANDLE \
				(0x000000F9C0000000L << MCPCIA_SYSMAP_SHIFT)
#define MCPCIA_GPC_IO_HANDLE     \
				(0x000000F980000000L << MCPCIA_SYSMAP_SHIFT)
#define MCPCIA_GPC_MEM_HANDLE    \
				(0x000000F800000000L << MCPCIA_SYSMAP_SHIFT)
#define MCPCIA_GPC_DENSE_HANDLE  \
				(0x000000F900000000L << MCPCIA_SYSMAP_SHIFT)

/* MCPCIA INTERRUPT TO SCB INDEX-ing MACROS */
#define MCPCIA_SCB_EISA_BASE		0x800
#define MCPCIA_SCB_PCI_BASE		0x900
#define MCPCIA_SCB_BUS_INDEX		0x200
#define MCPCIA_SCB_PCI_SLOT_INDEX	0x40
#define MCPCIA_SCB_PER_INTR_INDEX	0x10

#define SET_INTMASK	1
#define CLEAR_INTMASK	2


/*
 * DMA Support
 */

/*
 * HW DMA Window defines for MC-PCI Bridge
 */
/* index'es into the base and mask arrays */
#define WIN_NONE        0
#define WIN_1MEG        1
#define WIN_2MEG        2
#define WIN_4MEG        3
#define WIN_8MEG        4
#define WIN_16MEG       5
#define WIN_32MEG       6
#define WIN_64MEG       7
#define WIN_128MEG      8
#define WIN_256MEG      9
#define WIN_512MEG      10
#define WIN_1GIG        11
#define WIN_2GIG        12
#define WIN_4GIG        13
#define WIN_8GIG        14

/* 
 * these defines don't work for window size of WIN_NONE 
 */
#define WINDOW_BASE(Size_index)	 ((1UL << (Size_index - 1)) << 20)
#define WINDOW_SIZE(Wndw_index)  ((1UL << (Wndw_index - 1)) << 20)
#define WINDOW_MASK(Wndw_index) (((1UL << (Wndw_index - 1)) - 1) << 20)
#define SG_TABLE_SIZE(Wndw_index) (1UL << (Wndw_index + 9))

#define M_1_MEG                 WINDOW_SIZE(WIN_1MEG)
#define M_2_MEG                 WINDOW_SIZE(WIN_2MEG)
#define M_4_MEG                 WINDOW_SIZE(WIN_4MEG)
#define M_8_MEG                 WINDOW_SIZE(WIN_8MEG)
#define M_16_MEG                WINDOW_SIZE(WIN_16MEG)
#define M_32_MEG                WINDOW_SIZE(WIN_32MEG)
#define M_64_MEG                WINDOW_SIZE(WIN_64MEG)
#define M_128_MEG               WINDOW_SIZE(WIN_128MEG)
#define M_256_MEG               WINDOW_SIZE(WIN_256MEG)
#define M_512_MEG               WINDOW_SIZE(WIN_512MEG)
#define M_1_GIG                 WINDOW_SIZE(WIN_1GIG)
#define M_2_GIG                 WINDOW_SIZE(WIN_2GIG)
#define M_4_GIG                 WINDOW_SIZE(WIN_4GIG)
#define M_8_GIG                 WINDOW_SIZE(WIN_8GIG)

struct win_sel {
	u_int	type;		/* Direct, SG; En/disable; DAC	*/
	u_int	size;		/* based on WIN_xxxx index 	*/
	u_long	pci_base;	/* PCI base addr. of window 	*/
	u_long	tbase;		/* TBASE for s/g or direct 	*/
};

/*
 *      Definition of bus info structures.
 */
/*----------------------------------------------------------------*/
/* The agreed upon format for bus info structures is              */
/*                                                                */
/*      +----------------------------------------+                */
/*      |  Pointer to common info block          |                */
/*      |  (this is a struct common_bus_info *)  |                */
/*      +----------------------------------------|                */
/*      |  Bus specific data block               |                */
/*      +----------------------------------------+                */
/*                                                                */
/*----------------------------------------------------------------*/
/*
 * note: the common_bus_info looks like:
 * struct  common_bus_info
 *      {
 *       int            (**intr)();
 *       io_handle_t    sparse_io_base;
 *       io_handle_t    sparse_mem_base;
 *       vm_offset_t    dense_mem_base;
 *      };
 */
struct mcpcia_bus_info {
        struct common_bus_info *common_bus_info;
        ulong           	gid_mid_base;
};


/*
 * MCPCIA DMA Window defines
 */

/*
 * Each MCBUS<->PCI adapter had 4 DMA windows.
 * The windows are used as defined below
 *      (console expectations as well).
 *  +--------+--------+--------+--------+-----------------------+
 *  |   PCI  | Window | Offset |  Size  |  Usage                |
 *  | Window |  Type  |        |        |                       |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    0   |  S/G   |   8 MB |   8 MB | ADDR-LIMITED devices  |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    1   | Direct |   2 GB |   1 GB | Map 0-1GB main mem    |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    2   |  S/G   |   3 GB |   1 GB | 32-bit Scatter-gather |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    3   |  S/G   |        |<=4 GB  | 64-bit Scatter-gather	|
 *  +--------+--------+--------+--------+-----------------------+
 */

/* win_sel indices */
#define MCPCIA_ADDRLIM_WIN      0       /* Index to Addr. Lim. DMA Window  */
#define MCPCIA_SG_WIN           1       /* Index to GP S/G DMA Window      */
#define MCPCIA_DIRECT_WIN       2       /* Index to Direct-map DMA Window  */
#define MCPCIA_SG64_WIN         3       /* 64-bit scatter-gather window */
#define MCPCIA_DIRECT64         4       /* 64-bit direct DMA is just a 
                                         * register, not a window as such,
                                         * but it needs a dma_map_info_t
                                         * structure allocated...
                                         */

/* Per-MCPCIA info struct used for dma, intrs, etc.	*/
/* Note: order of elements correlates to frequency of use/access in cache */
struct mcpcia_info {
	u_long			gp_sg_ctl;
	u_long			direct_base;
	u_long                  sg_64bit_ctl; /* for 64-bit SG PCI DMA */
	shared_intr_info_t	*intr;
	u_long			addrlim_sg_ctl;
	u_long			addrlim_sg_base;
	u_long			gp_sg_base;
	u_long                  sg_64bit_base; /* for 64-bit SG PCI DMA */
	dma_map_info_t		dma_maps;
};
/* 
 * Macro to extract primary PCI bus number from 
 * (potentially a compound) PCI bus number.
 * Used as index into array of mcpcia_info structs
 */
#define MCPCIA_BUS_NUM(Busp)	(((Busp)->bus_num) & 0x00000003)

#define IS_AN_EISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_EISA)
#define IS_AN_ISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_ISA)
#define IS_A_CONTIG_DEVICE(f)	(f & DMA_CONTIG)
#define IS_A_SG_DEVICE(a,f)	(IS_A_CONTIG_DEVICE(f) || mcpcia_always_sg)
#define ADDRESS_LIMITED(Flags)	((Flags) & DMA_ADDR_LIMIT)
#define CONTIG_DESIRED(Flags)	((Flags) & DMA_CONTIG)
#define SG_ALLOCED(f)		((f) & DMA_HW_SG)
#define HAS_SG_ALLOCED(f)	((f) & DMA_HW_SG)

#define SG_NOTNEEDED	0
#define SG_REQUIRED	1
#define SG_DESIRED	2

#define WINDOW_ENABLE		0x1
#define WINDOW_DISABLE		0x0
#define WINDOW_SCATTER_GATHER	0x2
#define WINDOW_DIRECT_MAPPED 	0x0
#define WINDOW_DAC_ENABLE	0x8
#define WINDOW_BASE_MASK	0xfff00000L
#define MCPCIA_WIN_MAX		0x5		/* 5 DMA mapping windows per PCI */
#define MCPCIA_DMA_PREFETCH	0xff 		/* 255 bytes */

/* Various translation macros 	*/
#define CONFIG_BASE_TO_BRIDGE_CSR_BASE	0x02000000L

#define CONFIG_HANDLE_TO_MID_NUM(Handle) \
    (((((Handle) >> MCPCIA_SYSMAP_SHIFT) & MCBUS_MID_MASK)) >> MCBUS_MID_SHIFT)
#define CONFIG_HANDLE_TO_GID_NUM(Handle) \
    (((((Handle) >> MCPCIA_SYSMAP_SHIFT) & MCBUS_GID_MASK)) >> MCBUS_GID_SHIFT)
#define HOSE_TO_BRIDGE_CSR_PHYS(Hose_num) 				\
	( 0xF9E0000000L + ( ( (u_long)Hose_num << 1) << 32) )
#define ADPT_BASE_TO_HOSE_NUM(Adpt_base) 				\
	( (8 - ((Adpt_base & MCBUS_GID_MASK) >> MCBUS_GID_SHIFT) ) * 	\
	  (((Adpt_base & MCBUS_MID_MASK) >> MCBUS_MID_SHIFT) - 4) )

#define _IS_64BIT_CAPABLE_(f) ((f) & DMA_64BIT)

/* 
 * Determination of SG DMA Window base address on PCI
 * Now includes 64-bit DMA selection...
 */

#define SG_MAP_SELECT(Flags,Busp) \
    ( !(_IS_64BIT_CAPABLE_(Flags)) && !(ADDRESS_LIMITED(Flags))) ? \
                mcpcia_info[MCPCIA_BUS_NUM(Busp)].gp_sg_ctl : \
                    (_IS_64BIT_CAPABLE_(Flags) ? \
                            mcpcia_info[MCPCIA_BUS_NUM(Busp)].sg_64bit_ctl : \
                            mcpcia_info[MCPCIA_BUS_NUM(Busp)].addrlim_sg_ctl )

#define SG_MAP_BASE_DEVICE(Flags,Busp) \
	(ADDRESS_LIMITED(Flags) ? \
		mcpcia_info[MCPCIA_BUS_NUM(Busp)].addrlim_sg_ctl : \
		mcpcia_info[MCPCIA_BUS_NUM(Busp)].gp_sg_ctl )

/* PCI base address values of direct-map DMA windows	*/
#define MCPCIA_32B_DIRECT_MAP_BASE	(u_long)(1UL << 31)	/* 2GB */
#define MCPCIA_64B_DIRECT_MAP_BASE	(u_long)(1UL << 40)  	/* 1TB */

#define MCPCIA_64B_SG_MAP_BASE          (u_long)(1UL << 36)     /* 64GB */

/* Determination of direct-map DMA Window base on PCI	*/
#define DIRECT_MAP_SELECT(Flags) \
	(((Flags) & DMA_64BIT) ? \
		MCPCIA_64B_DIRECT_MAP_BASE : MCPCIA_32B_DIRECT_MAP_BASE)


/* p2p region includes sparse & dense memory region	*/
#define LOCAL_PEER_TO_PEER_DMA_BASE	(0x0000000000000000L)	/* 0GB->2GB */

#define IS_IN_PCI_SPACE(Pa)		((Pa) & MCPCIA_IOBUS_MASK)
#define IS_IN_PCI_DENSE_MEM(Pa)		(((Pa) & MCPCIA_DENSE_MEM_SPACE_MASK) \
						== 0x100000000L )
#define IS_IN_PCI_SPARSE_MEM(Pa)	(((Pa) & MCPCIA_SPARSE_MEM_SPACE_MASK) \
						== 0L )
/* 
 * Note:
 *	The and-or check below is designed to:
 *	-- fail if the physical address is not in PCI space 
 *	-- then check for the next most freq. case: dense-mapped mem. region
 *	-- then check for sparse-space mapped mem. region.
 *
 *	The checking is done in this order to minimize the code sequence
 *	executed for the most frequent dma-mapping check (non-peer-to-peer)
 *	and to allow the p-2-p check to be longer if it is p-2-p, since
 *	the performance of p-2-p can afford the slightly greater overhead.
 */
#define IS_PEER_TO_PEER(Pa)		( IS_IN_PCI_SPACE(Pa) && \
					  (IS_IN_PCI_DENSE_MEM(Pa) || \
					   IS_IN_PCI_SPARSE_MEM(Pa)) )

#define IS_LOCAL_PEER_TO_PEER(Addr, Busp) \
    ( (((Addr) &  MCBUS_MID_MASK) >> MCBUS_MID_SHIFT) == \
      CONFIG_HANDLE_TO_MID_NUM(((struct pci_sw *)((Busp)->bus_sw))->config_base))



/*
 * Function prototypes for mcpcia.c;
 * Externs for mcbus.c & kn300.c
 */

/*
 * IO-Access routine externs
 */
extern	long mcpcia_read_io_port(io_handle_t iohandle, int width, int type);
extern	void mcpcia_write_io_port(io_handle_t iohandle, int width, int type, 
								long data);
extern	int mcpcia_io_copyin(io_handle_t src, vm_offset_t dest, u_long count); 
extern	int mcpcia_io_copyout(vm_offset_t src, io_handle_t dest, u_long count); 
extern	int mcpcia_io_zero(io_handle_t dest, u_long count); 
extern	int mcpcia_io_copyio(io_handle_t src, io_handle_t dest, u_long count); 
extern	io_handle_t mcpcia_busphys_to_iohandle(u_long bus_addr, 
					int flags, struct controller *ctlrp);
extern	u_long mcpcia_iohandle_to_phys(io_handle_t iohandle, long flags);

/*
 * DMA window sizing alg.
 */
extern	void mcpcia_choose_dma_windows();

/*
 * DMA mapping externs
 */
extern	int mcpcia_dma_map_dealloc(dma_handle_t dma_handle);
extern	u_long mcpcia_dma_map_alloc(u_long bc, struct  controller *cntrlrp, 
					dma_handle_t *dma_handlep, int flags);
extern	u_long mcpcia_dma_map_load(u_long bc, vm_offset_t va, 
		struct proc *procp, struct controller *cntrlrp, 
		dma_handle_t *dma_handlep, u_long max_bc, int flags);
extern	int mcpcia_dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int mcpcia_dma_min_boundary(struct controller *cntrlrp);

#endif	/* __IO_DEC_PCI_MCPCIA_H__ */
