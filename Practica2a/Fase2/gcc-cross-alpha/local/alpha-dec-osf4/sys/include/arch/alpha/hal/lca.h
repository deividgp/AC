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
 * @(#)$RCSfile: lca.h,v $ $Revision: 1.1.10.4 $ (DEC) $Date: 1994/09/23 19:35:20 $
 */
/*
 * LCA4s - Low Cost Alpha
 *
 * Created: December 14, 1992
 *
 * Sections:
 * 	Memory Controller
 * 	I/O Controller
 */

#ifndef	_ARCH_ALPHA_HAL_LCA_H
#define	_ARCH_ALPHA_HAL_LCA_H
/*
 * Alpha IO Architecture standard address swizzle
 */
#define	IO_SHIFT	(5)
#define	IO_STRIDE	(0x80)
#define	ALIGN_MASK	(0xffffffffffffff9f)
#define	WIDTH_MASK	(0x18)
#define	WIDTH_SHIFT	(IO_SHIFT - 2)
#define Wrd		( (long)1 << (WIDTH_SHIFT) )
#define Tri		( (long)2 << (WIDTH_SHIFT) )
#define Lng		( (long)3 << (WIDTH_SHIFT) )
#define Quad		( (long)0xf << (WIDTH_SHIFT) )


/* Sysmap encodings of io_handle */
#define	LCA_SPARSE_MEM_FLAG	0x100000000L
#define	LCA_DENSE_MEM_FLAG	0x200000000L
#define	LCA_IO_SPACE_FLAG	0x400000000L
#define LCA_PCI_CONFIG_FLAG	0x800000000L
#define LCA_SPACE_BITS		0xf00000000L
#define	BUS_ADDR_BITS		0xffffffffL
#define	GET_HANDLE_ADDR(x)      ( (x) & BUS_ADDR_BITS )

/* LCA specific segments */

#define	BUSMEM_SPARSE_BASE	0x200000000L
#define	BUSMEM_DENSE_BASE	0x300000000L
#define	P1_BUSIO_BASE		BUSMEM_DENSE_BASE
#define	P2_BUSIO_BASE		0x1c0000000L

#define BUSMEM_SPARSE_MASK	0x7ffffffL
#define BUSMEM_DENSE_MASK	0xffffffffL
#define BUSIO_MASK		0x7ffffffL 		/* LCA BUS I/O space mask - 27 */

#define	BUSMEM_BASE		BUSMEM_SPARSE_BASE
#define	LCA_PCI_CONFIG_BASE	0x1e0000000L

#define LCA_PCI_CNFG_MASK	0x7ffffff 	/* LCA PCI config space mask - 27 bits */

#define PCI_CNFG_B(x)	(LCA_PCI_CONFIG_BASE | (((long)(x) & LCA_PCI_CNFG_MASK) << IO_SHIFT))
#define PCI_CNFG_W(x)	(LCA_PCI_CONFIG_BASE | Wrd | (((long)(x) & LCA_PCI_CNFG_MASK) << IO_SHIFT))
#define PCI_CNFG_L(x)	(LCA_PCI_CONFIG_BASE | Lng | (((long)(x) & LCA_PCI_CNFG_MASK) << IO_SHIFT))

#define P1_IO_B(x)	(P1_BUSIO_BASE | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P1_IO_W(x)	(P1_BUSIO_BASE | Wrd | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P1_IO_L(x)	(P1_BUSIO_BASE | Lng | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P1_IO_T(x)	(P1_BUSIO_BASE | Tri | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P1_IO_Q(x)	(P1_BUSIO_BASE | Quad | (((long)(x) & BUSIO_MASK) << IO_SHIFT))

#define P2_IO_B(x)	(P2_BUSIO_BASE | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P2_IO_W(x)	(P2_BUSIO_BASE | Wrd | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P2_IO_L(x)	(P2_BUSIO_BASE | Lng | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P2_IO_T(x)	(P2_BUSIO_BASE | Tri | (((long)(x) & BUSIO_MASK) << IO_SHIFT))
#define P2_IO_Q(x)	(P2_BUSIO_BASE | Quad | (((long)(x) & BUSIO_MASK) << IO_SHIFT))

#define MEM_B(x)	(BUSMEM_BASE | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEM_W(x)	(BUSMEM_BASE | Wrd | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEM_L(x)	(BUSMEM_BASE | Lng | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEM_T(x)	(BUSMEM_BASE | Tri | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))

#define MEMS_B(x)	(BUSMEM_SPARSE_BASE | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_W(x)	(BUSMEM_SPARSE_BASE | Wrd | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_L(x)	(BUSMEM_SPARSE_BASE | Lng | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_T(x)	(BUSMEM_SPARSE_BASE | Tri | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))
#define MEMS_Q(x)	(BUSMEM_SPARSE_BASE | Quad | (((long)(x) & BUSMEM_SPARSE_MASK) << IO_SHIFT))

/* burnsfix dense - quads */
#define MEMD_L(x) (BUSMEM_DENSE_BASE | ((long)(x) & BUSMEM_DENSE_MASK))
#define MEMD_Q(x) (BUSMEM_DENSE_BASE | ((long)(x) & BUSMEM_DENSE_MASK))


/* already masked addr */
#define	SWIZ_IT(a, w, s)	(addr << IO_SHIFT)


/* burnsfix - from io_access.c */
#define IOA_OKAY	0
#define	IOA_ERROR	-1

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

/* Macros for io accesses that are local to this file */
#define LCA_WRITE_BUS_D8(a,d)   WRITE_BUS_D8((LCA_IO_SPACE_FLAG|a),d)
#define LCA_WRITE_BUS_D16(a,d)  WRITE_BUS_D16((LCA_IO_SPACE_FLAG|a),d)
#define LCA_WRITE_BUS_D32(a,d)  WRITE_BUS_D32((LCA_IO_SPACE_FLAG|a),d)
#define LCA_READ_BUS_D8(a)      READ_BUS_D8((LCA_IO_SPACE_FLAG|a))
#define LCA_READ_BUS_D16(a)     READ_BUS_D16((LCA_IO_SPACE_FLAG|a))
#define LCA_READ_BUS_D32(a)     READ_BUS_D32((LCA_IO_SPACE_FLAG|a))

#define	IO_PAGE_SIZE	8192

/*
 * LCA Memory Controller
 */

#define	LCA_MEM_CTLR_BASE	0x120000000L

struct	lca_mem_ctlr {
	long	bcr0;			/* Bank 0 config register */
	long	bcr1;			/* Bank 1 config register */
	long	bcr2;			/* Bank 2 config register */
	long	bcr3;			/* Bank 3 config register */
	long	bmask0;			/* Bank 0 mask register */
	long	bmask1;			/* Bank 1 mask register */
	long	bmask2;			/* Bank 2 mask register */
	long	bmask3;			/* Bank 3 mask register */
	long	btr0;			/* Bank 0 timing register */
	long	btr1;			/* Bank 1 timing register */
	long	btr2;			/* Bank 2 timing register */
	long	btr3;			/* Bank 3 timing register */
	long	gtr;			/* Global timing register */
	long	esr;			/* Error status register */
	long	ear;			/* Error address register */
	long	car;			/* Cache register */
	long	vgr;			/* Video & Graphics control */
	long	plane_mask;		/* Plane mask */
	long	foreground;		/* Foreground */
};

/* Bank configuration registers */
#define	BCR_BAV		0x00000001	/* Base address valid */
#define	BCR_RAS		0x0000001e	/* Row address slecet */
#define	BCR_ERM 	0x00000020	/* Error mode */
#define BCR_WRM 	0x00000040	/* Write mode */
#define BCR_BWE 	0x00000080	/* Byte write enable */ 
#define BCR_SBE 	0x00000100	/* Split bank enable */
#define BCR_BBA 	0x1ff00000	/* Bank base address */

/* Bank address mask registers */
#define	BMASK_MASK	0x1ff00000

/* Bank timing registers */
#define	BTR_RAS		0x0000000f	/* Row address setup */
#define	BTR_RAH		0x000000f0	/* Row address hold */
#define	BTR_CAS 	0x00000f00	/* Column address setup */
#define	BTR_CASC	0x0001f000	/* Column address cycle */
#define	BTR_CASPC	0x001e0000	/* Column address pre-charge */
#define	BTR_TRISTATE	0x01e00000	/* Cycles to tristate */

/* Global timing register */
#define	GTR_PRECHARGE	0x0000001f	/* Cycles to precharge RAS and CAS */
#define	GTR_MINRAS	0x000003e0	/* Minimum cycles of RAS assertion */
#define	GTR_MAXRAS	0x0003fc00	/* Maximun cycles that RAS may be asserted */
#define	GTR_REF_ENAB	0x00040000	/* Refresh enable */
#define	GTR_REF_INT	0x07f80000	/* Refresh interval */
#define	GTR_RDS		0x08000000	/* Refresh divide select */
#define	GTR_SETUP	0xf0000000	/* CAS/RAS setup for refresh */

/* Error Status Register */
#define	ESR_EAV		0x00000001	/* Error address valid */
#define	ESR_CEE		0x00000002	/* Correctable error */
#define	ESR_UEE		0x00000004	/* Uncorrectible error */
#define	ESR_WRE		0x00000008	/* Write error */
#define	ESR_SOR		0x00000010	/* Error source */
#define	ESR_CTE		0x00000080	/* Backup cache tag parity error */
#define	ESR_MSE		0x00000200	/* Multiple soft errors */
#define	ESR_MHE		0x00000400	/* Multiple hard errors */
#define	ESR_ICE		0x00000800	/* Ignore correctable errors */
#define	ESR_NXM		0x00001000	/* Non-existant memory */
#define	ESR_WWECC	0x00ff0000	/* Write wrong ECC */
#define	ESR_ECC_VAL	0xff000000	/* ECC value */

/* Error Address Register */
#define	EAR_PERFCNT	0x00000007	/* Performance counter */
#define	EAR_ERRADDR	0x1ffffff8	/* Error address (quadword) */
#define	EAR_PERFCNTSEL	0xe0000000	/* Performance counter select */

/* Cache Register */
#define	CAR_BCE		0x00000001	/* Backup cache enable */
#define	CAR_FCM		0x00000002	/* Force backup cache miss */
#define	CAR_ETP		0x00000004	/* Enable tag parity check */
#define	CAR_WWP		0x00000008	/* Write wrong tag parity */
#define	CAR_ECE		0x00000010	/* Enable backup cache ECC */
#define	CAR_BCS		0x000000e0	/* Backup cache size */
#define	CAR_RCC		0x00000700	/* Read cycle count */
#define	CAR_WCC		0x00003800	/* Write cycle count */
#define	CAR_WHD		0x00004000	/* Write hold time */
#define	CAR_TAG		0x7fff0000	/* Tag */
#define	CAR_HIT		0x80000000	/* Hit */

/* Video & Graphics Control Register */
#define	VGR_MOD		0x00000001	/* Graphics mode */
#define	VGR_LDM		0x00000002	/* Load mode */
#define	VGR_BWE		0x00000004	/* Byte write enable */
#define	VGR_LDB		0x00000008	/* Load byte write enable */
#define	VGR_LDV		0x00000100	/* Load video control */
#define	VGR_INC		0x00000200	/* Address increment */
#define	VGR_FRAME	0x0ffffc00	/* Frame location */
#define	VGR_VRAM_SEL	0xf0000000	/* VRAM bank select */


/*
 * IOC - I/O Controller section of LCA
 */

/* IOC Registers */

/* Addresses of IOC registers */

#define IOCHAE_ADDR		0x180000000	/* Host Addr. Ext. Reg.	*/
#define	IOCC_ADDR		0x180000020	/* Control register address */
#define	IOCS0_ADDR		0x180000040	/* Status register 0 address */
#define	IOCS1_ADDR		0x180000060	/* Status register 1 address */
#define	IOC_TB_ENAB		0x1800000a0	/* Translation buffer enable */
#define	IOC_PAR_DIS		0x1800000e0	/* PCI Parity disable */
#define	WIN0_BASE_REG		0x180000100	/* Window base register 0 address */
#define	WIN1_BASE_REG		0x180000120	/* Window base register 1 address */
#define	WIN0_MASK_REG		0x180000140	/* Window mask register 0 address */
#define	WIN1_MASK_REG		0x180000160	/* Window mask register 1 address */
#define	WIN0_TBASE_REG		0x180000180	/* Translated base register 0 address */
#define	WIN1_TBASE_REG		0x1800001a0	/* Translated base register 1 address */

#define IOC_HAE			0x180000000	/* host address extension register   */
#define	IOC_CCTYPE		0x180000020	/* configuration cycle type register */
#define	IOC_STAT0		0x180000040	/* status 0 register		     */
#define	IOC_STAT1		0x180000060	/* status 1 register		     */
#define	IOC_TBIA		0x180000080	/* tb invalidate all register	     */
#define	IOC_TB_EN		0x1800000a0	/* tb enable register		     */
#define	IOC_PCI_PAR_DS		0x1800000e0	/* pci parity disable register	     */
#define	IOC_W_BASE_0		0x180000100	/* pci target window 0 base register */
#define	IOC_W_BASE_1		0x180000120	/* pci target window 1 base register */
#define	IOC_W_MASK_0		0x180000140	/* pci target window 0 mask register */
#define	IOC_W_MASK_1		0x180000160	/* pci target window 1 mask register */
#define	IOC_T_BASE_0		0x180000180	/* pci target window 0 translated    */
						/* base register		     */
#define	IOC_T_BASE_1		0x1800001a0	/* pci target window 1 translated    */
						/* base register		     */
#define	IOC_TB_TAG0		0x181000000	/* tb tag register 0		     */
#define	IOC_TB_TAG1		0x181000020	/* tb tag register 1		     */
#define	IOC_TB_TAG2		0x181000040	/* tb tag register 2		     */
#define	IOC_TB_TAG3		0x181000060	/* tb tag register 3		     */
#define	IOC_TB_TAG4		0x181000080	/* tb tag register 4		     */
#define	IOC_TB_TAG5		0x1810000a0	/* tb tag register 5		     */
#define	IOC_TB_TAG6		0x1810000c0	/* tb tag register 6		     */
#define	IOC_TB_TAG7		0x1810000e0	/* tb tag register 7		     */

/* IOC Control Register */

#define	IOCC_CFG_AD	0x00000003	/* PCI config cycle low order bits */
#define	IOCC_CLRERR	0x00000010	/* Clear status register error bit */
#define	IOCC_CLRLOST	0x00000020	/* Clear for status reg Lost error bit */
#define	IOCC_RESET	0x00000040	/* Assert PCI reset */
#define	IOCC_T_EN	0x00000080	/* Enable/disable scatter/gather translation buffer */
#define	IOCC_HAE	0xf8000000	/* Host address extension */

/* IOC Status Register 0 */
#define	IOCS0_CMD	0x0000000f	/* PCI command */
#define	IOCS0_ERR	0x00000010	/* PCI error */
#define	IOCS0_LOST	0x00000020	/* Lost PCI error */
#define	IOCS0_T_HIT	0x00000040	/* Scatter/gather translation hit */
#define	IOCS0_T_REF	0x00000080	/* Last PCI cycle referenced target window */
#define	IOCS0_CODE	0x00000700	/* Error code */
#define	IOCS0_P_NBR	0xffff7000	/* Page table error info */

/* IOC Status Register 1 */
#define	IOCS1_ADDR_MASK	0xffffffff	/* PCI Address, latched on error */

/* PCI Parity Disable register */
#define	IOCPAR_DIS	0x20		/* To disable PCI parity */


/* Target Window Registers */
	/* Window Base Registers */
#define	IOCWB_W_BASE	0x0fff00000L	/* PCI base address of target window */
#define	IOCWB_SG	0x100000000L	/* Scatter/gather enable */
#define	IOCWB_W_EN	0x200000000L	/* Target window enable */

	/* Window Mask Registers */
#define	IOCWM_W_MASK	0x0fff00000L	/* Target window mask - controls size of window */
#define	IOCWM_1MEG	0x000000000L	/*   1 Meg target window */
#define	IOCWM_2MEG	0x000100000L	/*   2 Meg target window */
#define	IOCWM_4MEG	0x000300000L	/*   4 Meg target window */
#define	IOCWM_8MEG	0x000700000L	/*   8 Meg target window */
#define	IOCWM_16MEG	0x000f00000L	/*  16 Meg target window */
#define	IOCWM_32MEG	0x001f00000L	/*  32 Meg target window */
#define	IOCWM_64MEG	0x003f00000L	/*  64 Meg target window */
#define	IOCWM_128MEG	0x007f00000L	/* 128 Meg target window */
#define	IOCWM_256MEG	0x00ff00000L	/* 256 Meg target window */
#define	IOCWM_512MEG	0x01ff00000L	/* 512 Meg target window */
#define	IOCWM_1GIG	0x03ff00000L	/*   1 Gig target window */
#define	IOCWM_2GIG	0x07ff00000L	/*   2 Gig target window */
#define	IOCWM_4GIG	0x0fff00000L	/*   4 Gig target window */


	/* Translated Base Registers */
#define	IOCTB_T_BASE	0x0fffffe00L	/* Base address */

/* Translation Buffer Tag Register */
#define	IOCTB_TAG	0x0fff0000L	/* Address tag */

#endif	/* _ARCH_ALPHA_HAL_LCA_H */
