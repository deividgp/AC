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
 * @(#)$RCSfile: apecs.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1995/06/23 12:13:07 $
 */
#ifndef	_ARCH_ALPHA_HAL_APECS_H
#define	_ARCH_ALPHA_HAL_APECS_H


/* Apecs addressing constants */
#define MAIN_MEM_SPACE_BASE		0x0
#define FRAME_BUFFER_MEM_SPACE		0x100000000	/* for frame buffer in main memory */
#define APECS_BUSIO_BASE		0x1c0000000
#define APECS_BUSMEM_BASE_SPARSE	0x200000000
#define APECS_BUSMEM_BASE_DENSE		0x300000000


/* Alpha IO Architecture stndard address swizzle */
#define	IO_SHIFT	(5)
#define	WIDTH_MASK	0x18
#define	WIDTH_SHIFT	(IO_SHIFT - 2)
#define Wrd		((long)1 << (WIDTH_SHIFT))
#define Tri		((long)2 << (WIDTH_SHIFT))
#define Lng		((long)3 << (WIDTH_SHIFT))
#define Quad	((long)0xf << (WIDTH_SHIFT))

/* specific segments */
#define	BUSMEM_BASE	APECS_BUSMEM_BASE_SPARSE
#define	BUSIO_BASE	APECS_BUSIO_BASE
#define BUSIO_MASK	0xffffff 	
#define BUSMEM_SPARSE_MASK	0x7ffffff
#define BUSMEM_DENSE_MASK	0xffffffffL
#define APECS_PCI_CNFG_MASK	0x7ffffff 	/* MUSTANG PCI config space mask - 31 bits */
#define	APECS_PCI_CONFIG_BASE	0x1e0000000

#define	BUSMEM_DENSE_BASE	APECS_BUSMEM_BASE_DENSE
#define	BUSMEM_SPARSE_BASE	APECS_BUSMEM_BASE_SPARSE
#define	IO_STRIDE	(0x80)
#define	ALIGN_MASK	(0xffffffffffffff9f)


#define PCI_CNFG_B(x) (APECS_PCI_CONFIG_BASE | (((long)(x) & APECS_PCI_CNFG_MASK) << IO_SHIFT))
#define PCI_CNFG_W(x) (APECS_PCI_CONFIG_BASE | Wrd | (((long)(x) & APECS_PCI_CNFG_MASK) << IO_SHIFT))
#define PCI_CNFG_L(x) (APECS_PCI_CONFIG_BASE | Lng | (((long)(x) & APECS_PCI_CNFG_MASK) << IO_SHIFT))

/* bus io space */
#define IO_B(x) (BUSIO_BASE | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define IO_W(x) (BUSIO_BASE | Wrd | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define IO_L(x)	(BUSIO_BASE | Lng | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define IO_T(x)	(BUSIO_BASE | Tri | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define IO_Q(x)	(BUSIO_BASE | Quad | (((long)(x) & BUSIO_MASK) << IO_SHIFT))

/* old io access */
#define MEM_B(x) (BUSMEM_BASE | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEM_W(x) (BUSMEM_BASE | Wrd | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEM_L(x) (BUSMEM_BASE | Lng | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEM_T(x) (BUSMEM_BASE | Tri | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))

/* sparse space */
#define MEMS_B(x) (APECS_BUSMEM_BASE_SPARSE | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_W(x) (APECS_BUSMEM_BASE_SPARSE | Wrd | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_L(x) (APECS_BUSMEM_BASE_SPARSE | Lng | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_T(x) (APECS_BUSMEM_BASE_SPARSE | Tri | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_Q(x) (APECS_BUSMEM_BASE_SPARSE | Quad | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))

/* burnsfix dense only longwords */
#define MEMD_L(x) (APECS_BUSMEM_BASE_DENSE | ((long)(x) & BUSMEM_DENSE_MASK))
#define MEMD_Q(x) (APECS_BUSMEM_BASE_DENSE | ((long)(x) & BUSMEM_DENSE_MASK))

/* io_handle sysmap */
#define	APECS_SPARSE_MEM_FLAG 	0x100000000L
#define	APECS_DENSE_MEM_FLAG 	0x200000000L
#define	APECS_IO_SPACE_FLAG 	0x400000000L
#define APECS_PCI_CONFIG_FLAG	0x800000000L
#define APECS_SPACE_BITS	0xf00000000L
#define	BUS_ADDR_BITS		 0xffffffffL
#define	GET_HANDLE_ADDR(x)	((x) & BUS_ADDR_BITS)




/* Macros for io accesses that are local to this file */
#define APECS_WRITE_BUS_D8(a,d)   WRITE_BUS_D8((APECS_IO_SPACE_FLAG|a),d)
#define APECS_WRITE_BUS_D16(a,d)  WRITE_BUS_D16((APECS_IO_SPACE_FLAG|a),d)
#define APECS_WRITE_BUS_D32(a,d)  WRITE_BUS_D32((APECS_IO_SPACE_FLAG|a),d)
#define APECS_READ_BUS_D8(a)      READ_BUS_D8((APECS_IO_SPACE_FLAG|a))
#define APECS_READ_BUS_D16(a)     READ_BUS_D16((APECS_IO_SPACE_FLAG|a))
#define APECS_READ_BUS_D32(a)     READ_BUS_D32((APECS_IO_SPACE_FLAG|a))

#define APECS_CNFG_READ_BUS_D8(a,s)      read_io_port((APECS_PCI_CONFIG_FLAG | a | (s << 11)), 1, 0)



/* Macros for io accesses that are local to this file */
#define APECS_WRITE_BUS_D8(a,d)   WRITE_BUS_D8((APECS_IO_SPACE_FLAG|a),d)
#define APECS_WRITE_BUS_D16(a,d)  WRITE_BUS_D16((APECS_IO_SPACE_FLAG|a),d)
#define APECS_WRITE_BUS_D32(a,d)  WRITE_BUS_D32((APECS_IO_SPACE_FLAG|a),d)
#define APECS_READ_BUS_D8(a)      READ_BUS_D8((APECS_IO_SPACE_FLAG|a))
#define APECS_READ_BUS_D16(a)     READ_BUS_D16((APECS_IO_SPACE_FLAG|a))
#define APECS_READ_BUS_D32(a)     READ_BUS_D32((APECS_IO_SPACE_FLAG|a))

#define APECS_CNFG_READ_BUS_D8(a,s)      read_io_port((APECS_PCI_CONFIG_FLAG | a | (s << 11)), 1, 0)

#define	HAXR0_ADDR	0x1a0000180L
#define	HAXR1_ADDR	0x1a00001a0L
#define	HAXR2_ADDR	0x1a00001c0L

#define EPIC_CSR	0x1a0000000L
#define EPIC_ERR_ADDR	0x1a0000020L
#define EPIC_DUMMY1	0x1a0000060L
#define EPIC_DUMMY2	0x1a0000080L
#define EPIC_DUMMY3	0x1a00000a0L
#define	EPIC_TBASE0	0x1a00000c0L
#define	EPIC_TBASE1	0x1a00000e0L
#define	EPIC_BASE0	0x1a0000100L
#define	EPIC_BASE1	0x1a0000120L
#define	EPIC_MASK0	0x1a0000140L
#define	EPIC_MASK1	0x1a0000160L
#define	EPIC_TBIA	0x1a0000400L

#define	EPIC_TBTR0	0x1a0000200L
#define	EPIC_TBDR0	0x1a0000300L
#define EPIC_TBREG_STEP	0x20
#define	EPIC_NUM_TB_REGS	8

#define	EPIC_BASE_SGEN	0x40000
#define	EPIC_BASE_WENB	0x80000

#define	EPIC_CSR_TENB	0x1
#define	EPIC_CSR_CLR_ERR	0xffe0L

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

#define	IO_PAGE_SIZE	8192

#define READ_EPIC_REG(r)	(*(u_int *)PHYS_TO_KSEG(r))
#define WRITE_EPIC_REG(r,d)	((*(u_int *)PHYS_TO_KSEG(r)) = d)
#define PRINT_REG(a)		printf("%lx = %lx\n", a, READ_EPIC_REG(a))

/*
 * Comanche CSR space
 */

#define	COMANCHE_CSR_BASE	0x180000000	/* Thru 0x19fffffff */
#define	EPIC_CSR_BASE		0x1A0000000	/* Thru 0x1afffffff */
#define PCI_SPECIAL_BASE	0x1b0000000	/* Thru 0x1bfffffff */
#define	PCI_CONFIG_BASE		0x1e0000000	/* Thru 0x1ffffffff */

#endif	/* _ARCH_ALPHA_HAL_APECS_H */
