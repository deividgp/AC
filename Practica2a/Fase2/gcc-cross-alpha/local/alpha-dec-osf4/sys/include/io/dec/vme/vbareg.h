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
 *	@(#)$RCSfile: vbareg.h,v $ $Revision: 1.2.19.3 $ (DEC) $Date: 1998/11/25 21:50:30 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */
/* 
 * derived from vbareg.h	4.2	(ULTRIX)	1/23/9
 */

/*
 * Abstract:
 *	This module contains the definitions for general VMEbus host
 *	modules.
 *
 */

#ifndef _VBAREG_H
#define _VBAREG_H

#define vme_flags conn_priv[4] /* this is in controller conn_priv */

/*
 * Definitions for VBA adapter and hardware capabilities
 */
#define VBA_TYPE_VIPVIC     0x00000000
#define VBA_TYPE_UNIV       0x10000000
#define VBA_TYPE_DWP64      0x20000000
#define VBA_TYPE_DWPVC      0x30000000
#define VBA_TYPE_TC         0x40000000
#define VBA_TYPE_MSK        0xF0000000
 
#define VBA_HW_BYTE_SWAP    0x00000000
#define VBA_NO_HW_BYTE_SWAP 0x08000000
#define VBA_BYTE_SWAP_MSK   0x08000000

#define VBA_BW_CAPABLE      0x04000000
#define VBA_NOT_BW_CAPABLE  0x00000000
#define VBA_BW_CAPABLE_MSK  0x04000000

/*
 * Definitions used internally by VBA adapters
 */
#define VBA_DOOR_BELL_INFO  0x04000000
#define VBA_DOOR_BELL_MSK   0x04000000

#define VBA_CSR_INFO        0x02000000
#define VBA_CSR_MSK         0x02000000

#define VBA_LOC_MON_INFO    0x01000000
#define VBA_LOC_MON_MSK     0x01000000

/*
 * Bit definitions for the flag field in the calls to dma_map_alloc() and
 * dma_map_load().
 *
 * The lower 16 bits of this flag are used for DMA_ bits as defined in
 * devdriver.h  The upper 16 bits are available for VME_ bits.
 */

#define VME_UDATA	0x00090000	/* User Data			*/
#define VME_UPROG	0x000A0000	/* User Program			*/
#define VME_SDATA	0x000D0000	/* Supervisory Data		*/
#define VME_SPROG	0x000E0000	/* Supervisory Program		*/

#define	VME_A64		0x00000000	/* A64 Request			*/
#define	VME_A32		0x00000000	/* A32 Request			*/
#define	VME_A24		0x00300000	/* A24 Request			*/
#define	VME_A16		0x00200000	/* A16 Request			*/
#define VME_USR_DEF	0x00100000	/* User Defined			*/

#define	VME_D08		0x00000000	/* D08 Data Size		*/
#define	VME_D16		0x00400000	/* D16 Data Size		*/
#define	VME_D32		0x00800000	/* D32 Data Size		*/
#define	VME_D64		0x00C00000	/* D64 Data Size		*/

/* some adapters may treat Byte Swap Words as a transaction Size Dependent 
 * swap instead
 */
#define	VME_BS_NOSWAP	0x00000000	/* No Byte Swap			*/
#define	VME_BS_BYTE	0x01000000	/* Byte Swap Bytes		*/
#define	VME_BS_WORD	0x02000000	/* Byte Swap Words		*/
#define	VME_BS_SIZE_DEPENDENT 0x02000000 /* Byte Swap Dependent upon 	*/
					/* transaction size		*/
#define	VME_BS_LWORD	0x03000000	/* Byte Swap Longwords		*/
#define	VME_BS_QUAD	0x04000000	/* Byte Swap Quadwords		*/

#define	VME_DMA		0x00000000	/* remains for backward		*/
					/* compatibility		*/
#define	VME_RESERV	0x08000000	/* Reserve VME Address space	*/
#define	VME_DENSE	0x10000000	/* DENSE Address Space Select   */
#define	VME_UDEF_AM53	0x20000000	/* User defined AM 5:3 Select   */
#define	VME_UNUSED	0x40000000
#define	VME_SHOEBOX	0x80000000	/* shoebox bit			*/

/*
 * masks and shift counts
 */
#define VME_AM_MASK          0x003F0000	/* VME Address Modifier (AM) Mask */
#define VME_AM_SHIFT         16		/* VME Address Modifier (AM) Shift*/

#define VME_AM_OPR_TYP_MASK  0x000F0000	/* VME AM Operation Type Mask     */
#define VME_AM_OPR_TYP_SHIFT 16		/* VME AM Operation type Shift	  */

#define VME_AM_ASPACE_MASK   0x00300000	/* VME AM Address Space Mask	  */
#define VME_AM_ASPACE_SHIFT  20		/* VME AM Address Space Shift	  */

#define	VME_DSIZE_MASK	     0x00C00000	/* VME Data Size Mask  		  */
#define	VME_DSIZE_SHIFT	     22		/* VME Data Size Shift		  */

#define	VME_BS_MASK	     0x07000000	/* Byte Swap mask		*/
#define	VME_BS_SHIFT	     24		/* Byte Swap shift count	*/

#define	VME_BITS_MASK	     0xFFFF0000	/* mask to get to VME_ bits */
#define	VME_BITS_SHIFT	     16		/* shift cnt to get to VME_ bits */

/*
 * The following values are convenient combinations of the VME_ flag bits 
 * used for the flags parameter
 */
#define VME_A32_UDATA	  (VME_A32 | VME_UDATA)
#define VME_A32_UPROG	  (VME_A32 | VME_UPROG)
#define VME_A32_SDATA	  (VME_A32 | VME_SDATA)
#define VME_A32_SPROG	  (VME_A32 | VME_SPROG)

#define VME_A24_UDATA	  (VME_A24 | VME_UDATA)
#define VME_A24_UPROG	  (VME_A24 | VME_UPROG)
#define VME_A24_SDATA	  (VME_A24 | VME_SDATA)
#define VME_A24_SPROG	  (VME_A24 | VME_SPROG)

#define VME_A16_UDATA     (VME_A16 | VME_UDATA)
#define VME_A16_UPROG     (VME_A16 | VME_UDATA)
#define VME_A16_SDATA     (VME_A16 | VME_SDATA)
#define VME_A16_SPROG     (VME_A16 | VME_SDATA)
#define VME_A16_USER_ACC  (VME_A16 | VME_UDATA)
#define VME_A16_SUPER_ACC (VME_A16 | VME_SDATA)

/*
 * For those adapters requiring data transfer size specifications for
 * outbound PIO transactions, the following values are convenient combinations
 * of the VME_ flag bits used for the flags parameter
 */
#define VME_A32_UDATA_D08	(VME_A32_UDATA | VME_D08)
#define VME_A32_UDATA_D16	(VME_A32_UDATA | VME_D16)
#define VME_A32_UDATA_D32	(VME_A32_UDATA | VME_D32)
#define VME_A32_UDATA_D64	(VME_A32_UDATA | VME_D64)

#define VME_A32_UPROG_D08	(VME_A32_UPROG | VME_D08)
#define VME_A32_UPROG_D16	(VME_A32_UPROG | VME_D16)
#define VME_A32_UPROG_D32	(VME_A32_UPROG | VME_D32)
#define VME_A32_UPROG_D64	(VME_A32_UPROG | VME_D64)

#define VME_A32_SDATA_D08	(VME_A32_SDATA | VME_D08)
#define VME_A32_SDATA_D16	(VME_A32_SDATA | VME_D16)
#define VME_A32_SDATA_D32	(VME_A32_SDATA | VME_D32)
#define VME_A32_SDATA_D64	(VME_A32_SDATA | VME_D64)

#define VME_A32_SPROG_D08	(VME_A32_SPROG | VME_D08)
#define VME_A32_SPROG_D16	(VME_A32_SPROG | VME_D16)
#define VME_A32_SPROG_D32	(VME_A32_SPROG | VME_D32)
#define VME_A32_SPROG_D64	(VME_A32_SPROG | VME_D64)

#define VME_A24_UDATA_D08	(VME_A24_UDATA | VME_D08)
#define VME_A24_UDATA_D16	(VME_A24_UDATA | VME_D16)
#define VME_A24_UDATA_D32	(VME_A24_UDATA | VME_D32)
#define VME_A24_UDATA_D64	(VME_A24_UDATA | VME_D64)

#define VME_A24_UPROG_D08	(VME_A24_UPROG | VME_D08)
#define VME_A24_UPROG_D16	(VME_A24_UPROG | VME_D16)
#define VME_A24_UPROG_D32	(VME_A24_UPROG | VME_D32)
#define VME_A24_UPROG_D64	(VME_A24_UPROG | VME_D64)

#define VME_A24_SDATA_D08	(VME_A24_SDATA | VME_D08)
#define VME_A24_SDATA_D16	(VME_A24_SDATA | VME_D16)
#define VME_A24_SDATA_D32	(VME_A24_SDATA | VME_D32)
#define VME_A24_SDATA_D64	(VME_A24_SDATA | VME_D64)

#define VME_A24_SPROG_D08	(VME_A24_SPROG | VME_D08)
#define VME_A24_SPROG_D16	(VME_A24_SPROG | VME_D16)
#define VME_A24_SPROG_D32	(VME_A24_SPROG | VME_D32)
#define VME_A24_SPROG_D64	(VME_A24_SPROG | VME_D64)

#define VME_A16_UDATA_D08	(VME_A16_UDATA | VME_D08)
#define VME_A16_UDATA_D16	(VME_A16_UDATA | VME_D16)
#define VME_A16_UDATA_D32	(VME_A16_UDATA | VME_D32)
#define VME_A16_UDATA_D64	(VME_A16_UDATA | VME_D64)

#define VME_A16_UPROG_D08	(VME_A16_UPROG | VME_D08)
#define VME_A16_UPROG_D16	(VME_A16_UPROG | VME_D16)
#define VME_A16_UPROG_D32	(VME_A16_UPROG | VME_D32)
#define VME_A16_UPROG_D64	(VME_A16_UPROG | VME_D64)

#define VME_A16_SDATA_D08	(VME_A16_SDATA | VME_D08)
#define VME_A16_SDATA_D16	(VME_A16_SDATA | VME_D16)
#define VME_A16_SDATA_D32	(VME_A16_SDATA | VME_D32)
#define VME_A16_SDATA_D64	(VME_A16_SDATA | VME_D64)

#define VME_A16_SPROG_D08	(VME_A16_SPROG | VME_D08)
#define VME_A16_SPROG_D16	(VME_A16_SPROG | VME_D16)
#define VME_A16_SPROG_D32	(VME_A16_SPROG | VME_D32)
#define VME_A16_SPROG_D64	(VME_A16_SPROG | VME_D64)

#define VME_A16_USER_ACC_D08	(VME_A16_UPROG_D08)
#define VME_A16_USER_ACC_D16	(VME_A16_UPROG_D16)
#define VME_A16_USER_ACC_D32	(VME_A16_UPROG_D32)
#define VME_A16_USER_ACC_D64 	(VME_A16_UPROG_D64)

#define VME_A16_SUPER_ACC_D08	(VME_A16_SDATA_D08)
#define VME_A16_SUPER_ACC_D16	(VME_A16_SDATA_D16)
#define VME_A16_SUPER_ACC_D32	(VME_A16_SDATA_D32)
#define VME_A16_SUPER_ACC_D64	(VME_A16_SDATA_D64)

#include <io/common/devdriver.h>

typedef		unsigned int	vme_addr_t;
typedef		unsigned int	vme_atype_t;

struct	vme_handler_info {
	struct handler_intr_info	gen_intr_info;
	unsigned int			vec;		/* vme intr vec */
	int				irq;		/* vme irq level */
};

extern	io_handle_t	vba_map_csr ();
extern	void		vba_unmap_csr();
extern	vme_addr_t	vba_get_vmeaddr ();
extern	vme_atype_t	vba_get_vmeaddr_am ();
extern	int		vbaconfl2 ();
extern	int		vbaconfl1 ();
extern	void		vba_display_addr_type ();
extern	void		vbaerrors ();
extern	int		vba_ba_config_bus ();
extern	unsigned int 	vba_post_irq ();
extern	boolean_t	vba_clear_irq ();
extern	unsigned int 	vba_set_dma_addr ();
extern	void		vba_get_dma_addr ();
extern  u_long          vba_dma ();
extern  int             vba_controller_configure();
extern  int             vba_controller_unconfigure();
extern  int             vba_add_bus_dispatch();
extern  unsigned int    vba_get_info();
extern  int             vba_badaddr();

#endif /* _VBAREG_H */
