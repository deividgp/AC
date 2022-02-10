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
 * @(#)$RCSfile: pvl.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1994/06/17 16:56:51 $
 */

/*
*****************************************************************************
**									    *
**  Copyright ) Digital Equipment Corporation, 1994		    	    *
**  All Rights Reserved.  Unpublished rights reserved under  the  copyright *
**  laws of the United States.						    *
**									    *
**  The software contained on this media is proprietary to and embodies the *
**  confidential  technology of Digital Equipment Corporation.  Possession, *
**  use,  duplication  or  dissemination  of  the  software  and  media  is *
**  authorized  only  pursuant  to  a  valid  written  license from Digital *
**  Equipment Corporation.						    *
**									    *
**  RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure by the  U.S. *
**  Government  is  subject  to  restrictions  as set forth in Subparagraph *
**  (c)(1)(ii) of DFARS 252.227-7013, or in FAR 52.227-19, as applicable.   *
**									    *
*****************************************************************************/

#ifndef	_PVL_H_
#define _PVL_H_

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/devio.h>
#include <sys/param.h>
#include <io/common/devdriver.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>

/*
 * The PVL_SUPPORTS_PEER define indicates that this revision of the PV
 * driver does support peer interface functions.
 */
/*
#define	PVL_SUPPORTS_PEER
*/

#ifdef PVL_SUPPORTS_PEER
#include <io/dec/ws/peer.h>
#endif /* PVL_SUPPORTS_PEER */

/*
 * Historical mistake follows
 */
#ifndef NDEPTHS
#define	NDEPTHS			1
#define	NVISUALS		1
#endif

/*
 * Subpixel coordinate access macros.
 */
#define	PVL_SUBPIX_GET_FRAC( _sp )	((unsigned short) ((_sp) & 0x7))
#define	PVL_SUBPIX_GET_WHOLE( _sp )	((short) (((short) (_sp)) >> 3 ))
#define	PVL_SUBPIX_MAKE( _w, _f )	((unsigned short) ((((unsigned short) (_w))<<3)|(((unsigned short)(_f))&0x7)))

/*
 * Server/Driver interface magic numbers
 */
#define	PVL_PVQM_SIZE			(1<<17)
#define	PVL_INVALID_PIXELMAP_ID		2
#define	PVL_DOORBELL_0_PIXELMAP_ID	3
#define	PVL_DOORBELL_1_PIXELMAP_ID	4
#define	PVL_PIXELMAP_DCC_MASK		0x8000
#define	PVL_IOC_PAGEOUTIN_COUNT_MAX	16
#define	PVL_IOC_PID_PV_INDEX		0
#define	PVL_IOC_PID_GCP_INDEX		1
#define	PVL_IOC_PID_NUM			2

/*
 * Address access macros
 */
#define PVL_BASE(C)		(((pvl_info_t *)(C))->p_pvo)
#define	PVL_BASES(C)		(((pvl_info_t *)(C))->p_pvo_s)


#define PVL_BUS_ADDR_LOAD_L( _addr ) ((pvl_halfaddr_t) ((pvl_bus_addr2_t *) &(_addr))->low )
#define PVL_BUS_ADDR_LOAD_H( _addr ) ((pvl_halfaddr_t) ((pvl_bus_addr2_t *) &(_addr))->high )
#define PVL_BUS_ADDR_STORE_L( _addr, _val ) ((pvl_halfaddr_t) ((pvl_bus_addr2_t *) &(_addr))->low = (pvl_halfaddr_t) (_val))
#define PVL_BUS_ADDR_STORE_H( _addr, _val ) ((pvl_halfaddr_t) ((pvl_bus_addr2_t *) &(_addr))->high = (pvl_halfaddr_t) (_val))

/*
 * Module Definitions.  Significant structures on the module.
 */
#define	PVL_PROM_OFFSET			0x00000000L
#define	PVL_RENDER_OFFSET		0x00000000L
#define	PVL_SRAM_OFFSET			0x00180000L
#define	PVL_PVA_OFFSET			0x00210000L
#define	PVL_BT463_OFFSET		0x00218000L
#define	PVL_BT431_0_OFFSET		0x00220000L
#define	PVL_BT431_1_OFFSET		0x00228000L
#define	PVL_MODULE_SIZE			0x00230000L

#define	PVL_SPARSE_PROM_OFFSET		(PVL_PROM_OFFSET << 1)
#define	PVL_SPARSE_RENDER_OFFSET	(PVL_RENDER_OFFSET << 1)
#define	PVL_SPARSE_SRAM_OFFSET		(PVL_SRAM_OFFSET << 1)
#define	PVL_SPARSE_PVA_OFFSET		(PVL_PVA_OFFSET << 1)
#define	PVL_SPARSE_BT463_OFFSET		(PVL_BT463_OFFSET << 1)
#define	PVL_SPARSE_BT431_0_OFFSET	(PVL_BT431_0_OFFSET << 1)
#define	PVL_SPARSE_BT431_1_OFFSET	(PVL_BT431_1_OFFSET << 1)
#define	PVL_SPARSE_MODULE_SIZE		(PVL_MODULE_SIZE << 1)

/*
 * Module and System Addresses as seen from the PVbus
 */
#define	PVLB_RENDER_OFFSET_HIGH		0x00000000L
#define	PVLB_RENDER_OFFSET_LOW		0x00000000L
#define	PVLB_SRAM_OFFSET_HIGH		0x00000000L
#define	PVLB_SRAM_OFFSET_LOW		0x00800000L
#define	PVLB_PHOST_OFFSET_HIGH		0x00080000L
#define	PVLB_PHOST_OFFSET_LOW		0x00000000L
#define	PVLB_VHOST_OFFSET_HIGH		0x00180000L
#define	PVLB_VHOST_OFFSET_LOW		0x00000000L

/*
 * Locate major module structures
 */
#define	PVL_BT431_0_BASE(_pi)	((struct bt431 *) ((unsigned long) PVL_BASE(_pi) + PVL_BT431_0_OFFSET ) )
#define	PVL_BT431_1_BASE(_pi)	((struct bt431 *) ((unsigned long) PVL_BASE(_pi) + PVL_BT431_1_OFFSET ) )
#define	PVL_BT463_BASE(_pi)	((struct bt463 *) ((unsigned long) PVL_BASE(_pi) + PVL_BT463_OFFSET ) )

/*
 * PVA registers
 */

/*
 * Descriptions of page and shadow page table.
 */
#define	PVL_PVA_PAGE_SHIFT_0	9
#define	PVL_PVA_PAGE_SHIFT_1	12
#define	PVL_PVA_PAGE_SHIFT_2	13
#define	PVL_PVA_PAGE_SHIFT_3	16
#define	PVL_PVA_PAGE_SHIFT	PVL_PVA_PAGE_SHIFT_2

#define	PVL_PVA_PAGE_SIZE_0	(1<<PVL_PVA_PAGE_SHIFT_0)
#define	PVL_PVA_PAGE_SIZE_1	(1<<PVL_PVA_PAGE_SHIFT_1)
#define	PVL_PVA_PAGE_SIZE_2	(1<<PVL_PVA_PAGE_SHIFT_2)
#define	PVL_PVA_PAGE_SIZE_3	(1<<PVL_PVA_PAGE_SHIFT_3)
#define	PVL_PVA_PAGE_SIZE	PVL_PVA_PAGE_SIZE_2

#define	PVL_PVA_VPN_MASK_0	0x7fffffff
#define	PVL_PVA_VPN_MASK_1      0x7fffffff
#define	PVL_PVA_VPN_MASK_2	0x3fffffff
#define	PVL_PVA_VPN_MASK_3	0x07ffffff
#define	PVL_PVA_VPN_MASK	PVL_PVA_VPN_MASK_2

#define	PVL_PVA_PPN_MASK_0	0x003fffff
#define	PVL_PVA_PPN_MASK_1	0x003fffff
#define	PVL_PVA_PPN_MASK_2	0x001fffff
#define	PVL_PVA_PPN_MASK_3	0x0003ffff
#define	PVL_PVA_PPN_MASK	PVL_PVA_VPN_MASK_2

#define	PVL_PVA_TABLE_SIZE_0	(1<<12)
#define	PVL_PVA_TABLE_SIZE_1	(1<<13)
#define	PVL_PVA_TABLE_SIZE_2	(1<<14)
#define	PVL_PVA_TABLE_SIZE_3	(1<<17)
#define	PVL_PVA_TABLE0_SIZE	PVL_PVA_TABLE_SIZE_0
#define	PVL_PVA_TABLE1_SIZE	PVL_PVA_TABLE0_SIZE

#define	PVL_PVA_PREFETCH_SIZE	512

/*
 * TLB Description
 *
 * _ENTRIES gives the number of TLB entries implemented and _TOTAL
 * the number provided for in the module addressing.
 */

#define	PVL_PVA_TLB_ENTRIES	16
#define	PVL_PVA_TLB_TOTAL	64
#define	PVL_RENDER_TLB_ENTRIES	256
#define	PVL_RENDER_TLB_TOTAL	256

#define	PVL_VA_TO_VPN( _va )	((unsigned int) (((unsigned long) (_va))>>PVL_PVA_PAGE_SHIFT) & PVL_PVA_VPN_MASK)
#define	PVL_VPN_TO_VA( _vpn )	((vm_offset_t) (((unsigned long) (_vpn))<<PVL_PVA_PAGE_SHIFT))
#define	PVL_PA_TO_PPN( _pa )	((unsigned int) (((unsigned long) (_pa))>>PVL_PVA_PAGE_SHIFT) & PVL_PVA_PPN_MASK)
#define	PVL_PPN_TO_PA( _ppn )	((vm_offset_t) (((unsigned long) (_ppn))<<PVL_PVA_PAGE_SHIFT))

/*
 * Access to the register structures
 */
#define	PVL_PVA_BASE(_pi)	((pvl_pva_register_t *) ((pvl_info_t *)(_pi))->p_pva)

/*
 * Access to SRAM
 */
#define	PVL_SRAM_BASE(_pi)	((caddr_t) ((pvl_info_t *)(_pi))->p_sram)

/*
 * PV Renderer Registers
 */
#define	PVL_REND_IMP_OFFSET	((vm_offset_t) 0x00080000)
#define	PVL_REND_POLL_OFFSET	((vm_offset_t) 0x00100000)
#define	PVL_REND_DMA_OFFSET	((vm_offset_t) 0x00040000)
#define	PVL_REND_TLB_OFFSET	((vm_offset_t) 0x000c0000)
#define	PVL_REND_VIDEO_OFFSET	((vm_offset_t) 0x00140000)

#define	PVL_REND_SPARSE_POLL_OFFSET	((PVL_REND_POLL_OFFSET) << 1)

/*
 * Access to PV
 */
#define	PVL_REND_BASE(_pi)	((caddr_t) ((pvl_info_t *)(_pi))->p_pv)
#define	PVL_REND_SPARSE_BASE(_pi) ((caddr_t) ((pvl_info_t *)(_pi))->p_pv_s)

#define	PVL_REND_IMP_BASE(_pi)	((pvl_render_implement_t *) ((unsigned long) PVL_REND_BASE(_pi) + PVL_REND_IMP_OFFSET ) )
#define	PVL_REND_DMA_BASE(_pi)	((pvl_render_dma_t *) ((unsigned long) PVL_REND_BASE(_pi) + PVL_REND_DMA_OFFSET ) )
#define	PVL_REND_TLB_BASE(_pi)	((pvl_graphic_tlb_t *) ((unsigned long) PVL_REND_BASE(_pi) + PVL_REND_TLB_OFFSET ) )
#define	PVL_REND_VIDEO_BASE(_pi)	((pvl_render_video_t *) ((unsigned long) PVL_REND_BASE(_pi) + PVL_REND_VIDEO_OFFSET ) )

/*
 * PV Renderer Polling Register
 */
#define	PVL_REND_POLL_STATUS_FREE	0

#define	PVL_REND_HOST_TO_POLL( _pa )	((vm_offset_t) (PVL_REND_POLL_OFFSET | 0x00020000 | (((unsigned int) (_pa) & 0x03fff000)>>9)))
#define	PVL_REND_SRAM_TO_POLL( _sram )	((vm_offset_t) (PVL_REND_POLL_OFFSET | (((unsigned int) (_sram) & 0x03fff000)>>9)))

#define	PVL_REND_SPARSE_HOST_TO_POLL( _pa )	((vm_offset_t) (PVL_REND_SPARSE_POLL_OFFSET | 0x00040000 | (((unsigned int) (_pa) & 0x03fff000)>>8)))
#define	PVL_REND_SPARSE_SRAM_TO_POLL( _sram )	((vm_offset_t) (PVL_REND_SPARSE_POLL_OFFSET | (((unsigned int) (_sram) & 0x03fff000)>>8)))

/*
 * Debug printing defines
 */
#define PVL_SILENT		0
#define PVL_CONSOLE		1
#define PVL_PSST		2
#define PVL_TERSE		3
#define PVL_TALK		4
#define PVL_YAK			5
#define PVL_GAB			7
#define PVL_BLAB		10
#define PVL_YOW			13
#define PVL_NEVER		99
#define PVL_DEBUGGING		PVL_TALK
#define PVL_PANIC		PVL_SILENT

/*
#define PVL_NODEBUG
*/

#ifdef  PVL_NODEBUG
#	define PVL_DEBUG(L,S)
#else
#	define PVL_DEBUG(L,S)	if ((L) <= _pvl_debug) { S }
#endif /* PVL_NODEBUG */

/*
 * Brooktree BT431 Defines
 */

#define PVL_BT431_CUR_CMD           0x0000 /* cursor command reg */

#define PVL_BT431_CUR_XLO           0x0001 /* cursor x(lo) */
#define PVL_BT431_CUR_XHI           0x0002 /*  */
#define PVL_BT431_CUR_YLO           0x0003 /* cursor y(lo) */
#define PVL_BT431_CUR_YHI           0x0004 /*  */

#define PVL_BT431_WIN_XLO           0x0005 /* window x(lo) */
#define PVL_BT431_WIN_XHI           0x0006 /*  */
#define PVL_BT431_WIN_YLO           0x0007 /* window y(lo) */
#define PVL_BT431_WIN_YHI           0x0008 /*  */

#define PVL_BT431_WIN_WLO           0x0009 /* window width(lo) */
#define PVL_BT431_WIN_WHI           0x000a /*  */
#define PVL_BT431_WIN_HLO           0x000b /* window height(lo) */
#define PVL_BT431_WIN_HHI           0x000c /*  */

#define PVL_BT431_DUP_B0(X) \
(unsigned short) ((((unsigned short)(X) << 8) & 0xff00) \
			 | (((unsigned short)(X)) & 0xff))

/*
 * Brooktree BT463 Defines
 */
#define	PVL_BT463_WINDOW_TAG_COUNT		16
#define	PVL_BT463_CMAP_ENTRY_COUNT		528

#define	PVL_BT463_SETUP_HEAD_MASK		0x00000001
#define	PVL_BT463_SETUP_RW_MASK			0x00000002
#define	PVL_BT463_SETUP_C0_MASK			0x00000004
#define	PVL_BT463_SETUP_C1_MASK			0x00000008
#define	PVL_BT463_SETUP_C2_MASK			0x00000010

#define	PVL_BT463_DATA_WRITE_SHIFT		0
#define	PVL_BT463_DATA_READ0_SHIFT		8
#define	PVL_BT463_DATA_READ1_SHIFT		16

#define	PVL_BT463_ADDR_LOW			0
#define	PVL_BT463_ADDR_HIGH			(PVL_BT463_SETUP_C0_MASK)
#define	PVL_BT463_CMD_CURS			(PVL_BT463_SETUP_C1_MASK)
#define	PVL_BT463_CMD_CMAP			(PVL_BT463_SETUP_C0_MASK|PVL_BT463_SETUP_C1_MASK)

/*
 * Address registers
 */
#define PVL_BT463_CURSOR_COLOR0			0x0100
#define PVL_BT463_CURSOR_COLOR1			0x0101
#define PVL_BT463_ID_REG			0x0200
#define PVL_BT463_COMMAND_REG_0			0x0201
#define PVL_BT463_COMMAND_REG_1			0x0202
#define PVL_BT463_COMMAND_REG_2			0x0203

#define PVL_BT463_P0_P7_READ_MASK		0x0205
#define PVL_BT463_P8_P15_READ_MASK		0x0206
#define PVL_BT463_P16_P23_READ_MASK		0x0207
#define PVL_BT463_P24_P27_READ_MASK		0x0208

#define PVL_BT463_P0_P7_BLINK_MASK		0x0209
#define PVL_BT463_P8_P15_BLINK_MASK		0x020a
#define PVL_BT463_P16_P23_BLINK_MASK		0x020b
#define PVL_BT463_P24_P27_BLINK_MASK		0x020c

#define PVL_BT463_TEST_REG			0x020d

#define	PVL_BT463_WINDOW_TYPE_TABLE		0x0300

#define	PVL_BT463_LUT_BASE_8			0
#define	PVL_BT463_LUT_BASE_24			0x100

#define PVL_BT463_ADDR_LOW_MASK			0x00ff
#define PVL_BT463_ADDR_HIGH_MASK		0xff00

/*
 * Typedefs
 */

/*
 * Basic Data Type Definitions
 */
typedef unsigned int
  pvl_register_t;

typedef unsigned long
  pvl_bus_addr_t;

typedef unsigned int
  pvl_halfaddr_t;

typedef struct {
  pvl_halfaddr_t		low;
  pvl_halfaddr_t		high;
} pvl_bus_addr2_t;

typedef short
  pvl_subpixel_t;

typedef struct {
  pvl_subpixel_t		x;
  pvl_subpixel_t		y;
} pvl_subpixel_pair_t;

typedef struct {
  unsigned int
    pixelmap_id : 15,
    x : 6,
    y : 6,
    dirty : 1,
    : 4;
} pvl_graphic_tlb_t;

typedef struct {
  unsigned int
	vpn : 32,
	ppn : 22,
	pid : 8,
	we : 1,
	mru : 1;
} pvl_pva_tlb_entry_t;

/*
 * PVA PID Description
 */
typedef struct {
  unsigned int
    pid0 : 8,
    pid1 : 8,
    : 16;
} pvl_pid_t;

/*
 * PVA DMA Miss Register
 */
typedef struct {
  unsigned int
    vpn : 31,
    rd : 1;
} pvl_dma_miss_t;

/*
 * PVA CSR Description
 */
typedef struct {
  unsigned int
    vps : 2,
    spts0 : 2,
    spts1 : 2,
    dma_lockout : 1,
    pb_reset : 1,
    gpo : 1,
    gpi : 1,
    : 22;
} pvl_csr_t;

#define	PVL_PVA_CSR_VPS_512		0
#define	PVL_PVA_CSR_VPS_4K		1
#define	PVL_PVA_CSR_VPS_8K		2
#define	PVL_PVA_CSR_VPS_64K		3
#define	PVL_PVA_CSR_VPS			PVL_PVA_CSR_VPS_8K

#define	PVL_PVA_CSR_SPTS_4K		0
#define	PVL_PVA_CSR_SPTS_8K		1
#define	PVL_PVA_CSR_SPTS_16K		2
#define	PVL_PVA_CSR_SPTS_128K		3
#define	PVL_PVA_CSR_SPTS0		PVL_PVA_CSR_SPTS_4K
#define	PVL_PVA_CSR_SPTS1		PVL_PVA_CSR_SPTS0

/*
 * PVA ISR Description
 */
#define	PVL_PVA_INTR_PB0		0x00000001
#define	PVL_PVA_INTR_PB1		0x00000002
#define	PVL_PVA_INTR_TLB_MISS0		0x00000004
#define	PVL_PVA_INTR_TLB_MISS1		0x00000008
#define	PVL_PVA_INTR_DMA_RD_ERR0	0x00000010
#define	PVL_PVA_INTR_DMA_RD_ERR1	0x00000020
#define	PVL_PVA_INTR_DMA_WR_ERR0	0x00000040
#define	PVL_PVA_INTR_DMA_WR_ERR1	0x00000080
#define	PVL_PVA_INTR_ALL		0x000000ff

/*
 * PVA Process ID assignments
 */
#define	PVL_PVA_PID_SERVER		0x01
#define	PVL_PVA_PID_PAGER		0x00
#define	PVL_PVA_PID_INVALID		0xff

/*
 * PVA TC countdown counter max value
 */
#define	PVL_PVA_COUNTER_MAX		0x0003ffff

/*
 * PVA Register Space Description
 */
typedef struct {
  pvl_pva_tlb_entry_t	tlb[PVL_PVA_TLB_TOTAL];
  pvl_pid_t		pid;
  pvl_dma_miss_t	dma_miss;
  pvl_register_t	spt_base0;
  pvl_register_t	spt_base1;
  pvl_csr_t		csr;
  pvl_register_t	intr_status;
  pvl_register_t	intr_mask;
  pvl_register_t	intr_mask_set;
  pvl_register_t	intr_mask_clear;
  pvl_register_t	counter;
  pvl_register_t	revision;
  pvl_register_t	_pad1[4];
  pvl_register_t	tlb_burstwr;
} pvl_pva_register_t;

/*
 * PV Register Definitions
 */
#define	PVL_RENDER_IMP_USZ_4X2		0
#define	PVL_RENDER_IMP_USZ_4X4		1
#define	PVL_RENDER_IMP_USZ_8X2		2
#define	PVL_RENDER_IMP_USZ_8X4		4

#define	PVL_RENDER_IMP_VSZ_1024X1024	0
#define	PVL_RENDER_IMP_VSZ_1280X1024	1
#define	PVL_RENDER_IMP_VSZ_2048X1024	2
#define	PVL_RENDER_IMP_VSZ_2048X1536	3
#define	PVL_RENDER_IMP_VSZ_2048X2048	4
#define	PVL_RENDER_IMP_VSZ_UNSUPPORTED	5

typedef struct {
  unsigned int
    min : 4,
    major : 4,
    implement : 8,
    update_size : 4,
    vis_pmap_size : 4,
    mem_size : 5,
    reserved : 3;
} pvl_render_imp_rev_t;

typedef struct {
  unsigned int
    max_pkts : 8,
    : 1,
    stereo : 1,
    vsync : 1,
    page : 1,
    vm : 1,
    render : 1,
    packet : 1,
    block_en : 4,
    : 13;
} pvl_render_config_t;

typedef struct {
  unsigned int
    field : 1,
    vsync_int : 1,
    page_int : 1,
    vm_status : 1,
    vm_int : 1,
    render_status : 1,
    render_int : 1,
    packet_status : 1,
    packet_int : 1,
    stall : 1,
    : 22;
} pvl_render_status_t;

typedef struct {
  pvl_register_t	tlb_addr;
  pvl_render_imp_rev_t	imp_rev;
  pvl_render_config_t	config;
  pvl_render_status_t	status;
} pvl_render_implement_t;

#define	PVL_RENDER_DMA_FORMAT_RGB		0
#define	PVL_RENDER_DMA_FORMAT_DCC		1

#define	PVL_RENDER_DMA_RW_WRITE			0
#define	PVL_RENDER_DMA_RW_READ			1

typedef struct {
  pvl_register_t	pixelmap_id;
  pvl_register_t	pad0;
  pvl_subpixel_pair_t	xy_min;
  pvl_subpixel_pair_t	xy_max;
  pvl_register_t	addr_low;
  pvl_register_t	addr_high;
  pvl_register_t	pad1;
  pvl_register_t	offset;
  pvl_register_t	format;
  pvl_register_t	read_write;
  pvl_register_t	status;
} pvl_render_dma_t;

typedef struct {
  pvl_register_t	vblank_s;
  pvl_register_t	vblank_f;
  pvl_register_t	vsync_s;
  pvl_register_t	vsync_f;
  pvl_register_t	hblank_s;
  pvl_register_t	hblank_f;
  pvl_register_t	hsync2;
  pvl_register_t	pad0;
  pvl_register_t	hsync_s;
  pvl_register_t	hsync_f;
  pvl_register_t	crt_enable;
} pvl_render_video_t;

/*
 * Profiling data
 */
typedef struct {
  unsigned int		alloc_stall_requests;
  unsigned int		ping_requests;
  unsigned int		ping_queue_empty_count;
  unsigned int		ping_pv_ready_count;
  unsigned int		max_queue_depth;
  unsigned int		wait_for_queue;
  unsigned int		ping_from_intr_count;
  unsigned int		ping_from_intr_failure;
} pvl_profile_data_t;

/*
 * Interface window tag cell definition
 */
typedef struct {
    char		windex;
    unsigned char	low;
    unsigned char	mid;
    unsigned char	high;
} pvl_window_tag_cell_t;

/* 
 * pvl_attach_info_t
 *
 * This structure returns information about the device mapping back to 
 * a thread that has attached to the PV peer interface.
 */
#define	PVL_INFO_SIG_NUM			6
#define	PVL_INFO_SIG_PMAP_FAULT			0
#define	PVL_INFO_SIG_VA_PAGEIN			1
#define	PVL_INFO_SIG_MODULE_ERROR		2
#define	PVL_INFO_SIG_CLIPPING			3
#define	PVL_INFO_SIG_PVA_TLB1_FAULT		4
#define	PVL_INFO_SIG_PACKET_DONE		5

typedef struct {
  caddr_t			p_pvo;
  caddr_t			p_pvo_s;
  caddr_t			p_gcp;
  caddr_t			p_gcp_s;
  caddr_t			p_pva;
  caddr_t			p_pva_s;
  caddr_t			p_pv;
  caddr_t			p_pv_s;
  caddr_t			p_sram;
  caddr_t			p_sram_s;
  unsigned int			vram_size;		/* in pixels */
  unsigned int			sram_size;
  unsigned int			pixelmap_size;		/* in pixels */
  unsigned int			pixelmap_count;
  unsigned int			update_size;
  unsigned int			vis_pmap_size;
  unsigned int			monitor_rate;
  unsigned int			page_table_0_size;
  pvl_register_t		phys_page_table_0;
  pvl_pva_tlb_entry_t		*p_page_table_0;
  unsigned int			ppn_dead_area;
  caddr_t			phys_dead_area;
  caddr_t			phys_clip_area;
  caddr_t			phys_info_area;
  caddr_t			phys_cmd_area;
  unsigned int			cmd_area_size;
  caddr_t			p_cmd_area;
  caddr_t			p_clip_area;
  caddr_t			p_dead_area;
  caddr_t			pagein_vaddr;
  unsigned short		pagein_page_count;
  unsigned short		pagein_dirty;
  unsigned int			signal_reasons[PVL_INFO_SIG_NUM];
  caddr_t			pPingBase;
  caddr_t			pModuleBase;
  caddr_t			pSRAMBase;
  pvl_render_implement_t	*pRenderBase;
  caddr_t			packetArray;
  unsigned int			packetArraySize;
  unsigned int			pollBusy;
  caddr_t			packetGet;
  caddr_t			packetPolled;
  caddr_t			chainedPacket;
  unsigned int			chainedPacketSize;
  caddr_t			packet_poll_base;
  caddr_t			packet_pvl_base;
} pvl_attach_info_t;

/*
 * pvl_queue_t
 */
typedef struct {
  caddr_t		offset;
  unsigned int		size;
} pvl_queue_t;

#define	PVL_QUEUE_SIZE		32


/*
 * pvl_info_t
 */
typedef struct {
  ws_screen_descriptor	screen;
  ws_depth_descriptor	depth[NDEPTHS];
  ws_visual_descriptor	visual[NVISUALS];
  ws_cursor_functions	cf;
  ws_color_map_functions cmf;
  ws_screen_functions	sf;
  int			(*attach)();
  int			(*bootmsg)();
  int			(*map)();
  void			(*interrupt)();
  int			(*setup)();
  int			(*vm_hook)();
  struct controller	*ctlr;
  caddr_t		p_pva;
  caddr_t		p_pva_s;
  caddr_t		p_pv;
  caddr_t		p_pv_s;
  caddr_t		p_sram;
  caddr_t		p_sram_s;
  u_int 		text_foreground;
  u_int 		text_background;
  /*
   * stuff above this line gets initialized from px_types[]
   */
  caddr_t		p_pvo;
  caddr_t		p_pvo_s;
  unsigned int		vram_size;
  unsigned int		sram_size;
  unsigned int		pixelmap_size;
  unsigned int		pixelmap_count;
  unsigned int		update_size;
  unsigned int		vis_pmap_size;
  unsigned int		page_table_0_size;
  pvl_register_t	phys_page_table_0;
  pvl_pva_tlb_entry_t	*p_page_table_0;        /* PV shadow page table */
  unsigned int		ppn_dead_area;
  caddr_t		phys_dead_area;
  caddr_t		phys_clip_area;
  caddr_t		phys_info_area;
  caddr_t		phys_cmd_area;
  caddr_t		phys_packet_area;
  unsigned int		cmd_area_size;
  caddr_t		p_cmd_area;
  caddr_t		p_clip_area;
  caddr_t		p_info_area;
  caddr_t		p_packet_area;
  caddr_t		p_dead_area;
  caddr_t		dev_closure;
  pvl_register_t	last_intr_status;
  pvl_render_config_t	render_config;
  volatile int		image_stlb_lock;
  volatile int		pmap_stlb_lock;

#define	PVL_INFO_SLEEP_PV_DMA		0
#define	PVL_INFO_SLEEP_RENDER		1
#define	PVL_INFO_SLEEP_IMAGE		2
#define	PVL_INFO_SLEEP_PACKET		3
#define	PVL_INFO_SLEEP_NUM		4
  unsigned int		sleep_chan[PVL_INFO_SLEEP_NUM];
  unsigned long		state;
#define	PVL_INFO_STATE_VALID		0x00000001
#define	PVL_INFO_STATE_GCP_VALID		0x00000002
#define	PVL_INFO_STATE_SAVED_GTLB_VALID	0x00000004
  /*
   * Keep the PV config register around
   */
  pvl_render_imp_rev_t	render_imp_rev;
  /*
   * pid and sig_mask are used to direct delivery of signals to
   * the owning process.  They are controlled by device-private ioctl's.
   */
  struct proc		*p_proc[PVL_IOC_PID_NUM];
  pid_t			pid[PVL_IOC_PID_NUM];
  unsigned long		sig_mask[PVL_IOC_PID_NUM];
  /*
   * For 'soft' lockdowns during image operations, save the locked
   * down address range here.  Also bits for error status and to
   * enable VA range checking.  For hard lockdowns, we still use the
   * first and last vpn.
   */
  unsigned long		image_check_va_range;
  unsigned long		image_hardlock_in_progress;
  unsigned long		image_failure;
  unsigned int		image_va_first_vpn;
  unsigned int		image_va_last_vpn;
  /*
   * Interrupt parity.  We need to take two interrupts for vsync
   * operations
   */
  unsigned int		intr_parity;
  /*
   * During Put/GetImage, it may be necessary to service a pixelmap
   * fault.  Tuck the required PV TLB entries into this area.
   */
#define	PVL_INFO_SAVED_PV_TLB_MAX	512
  pvl_pva_tlb_entry_t	saved_tlb[PVL_INFO_SAVED_PV_TLB_MAX];
  pvl_graphic_tlb_t	saved_graphic_tlb;
  /*
   * DCC information.  We will have a default value which can be
   * overridden with an ioctl.  This value is placed in the high byte
   * to force treatment as a truecolor value
   */
  unsigned char		dcc_default;
  unsigned char		dcc_user;
  /*
   * Video on/off state.  Somewhat parallels that kept in the
   * Brooktree code.
   */
  char			video_on_off_dirty;
  char			video_on_off;
  /*
   * Window tag information
   */
  char			wt_dirty;
  char			wt_left_min_dirty;
  char			wt_left_max_dirty;
  char			wt_right_min_dirty;
  char			wt_right_max_dirty;
  pvl_window_tag_cell_t	wt_left_cell[PVL_BT463_WINDOW_TAG_COUNT];
  pvl_window_tag_cell_t	wt_right_cell[PVL_BT463_WINDOW_TAG_COUNT];
  /*
   * State for maintaining stereo modes
   */
  unsigned int		stereo_mode;
#define	PVL_INFO_STEREO_NONE		0
#define	PVL_INFO_STEREO_24		1
#define	PVL_INFO_STEREO_1212		2

  int			stereo_wtag_start;
  int			stereo_wtag_count;
  /*
   * Safe area for data used in pageoutin operations
   */
  pvl_register_t	poi_out_tlb_entries[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_register_t	poi_out_format[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_register_t	poi_out_offset[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_register_t	poi_out_pixelmapid[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_register_t	poi_in_tlb_entries[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_register_t	poi_in_format[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_register_t	poi_in_offset[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_register_t	poi_in_pixelmapid[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_subpixel_pair_t	poi_out_xy_min[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_subpixel_pair_t	poi_out_xy_max[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_subpixel_pair_t	poi_in_xy_min[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  pvl_subpixel_pair_t	poi_in_xy_max[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  int			poi_count;
  int			poi_clear_page_int;
  int			poi_tlb_index[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  vm_offset_t		poi_out_page[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  vm_offset_t		poi_in_page[PVL_IOC_PAGEOUTIN_COUNT_MAX];
  /*
   * Monitor information
   */
  unsigned int		monitor_rate;
  /*
   * Packet queue queue
   */
  pvl_queue_t		queue[PVL_QUEUE_SIZE];
  int			queue_get;
  int			queue_put;
  /*
   * Driver/Server communication area
   */
  pvl_attach_info_t	*pv;
  /*
   * Profiling data
   */
  pvl_profile_data_t	profile;
  /*
   * Info about process packet and image mapping
   */
  caddr_t		packet_poll_base;
  caddr_t		packet_pvl_base;
} pvl_info_t;

/*
 * pvl_type_t
 *
 * Parallels the pvl_info_t structure.
 */
typedef struct {
  ws_screen_descriptor	screen;
  ws_depth_descriptor	depth[NDEPTHS];
  ws_visual_descriptor	visual[NVISUALS];
  u_char		cursor_type;
  u_char		cmap_type;
  u_char		screen_type;
  u_char		max_fbn;
  ws_cursor_functions	cf;
  ws_color_map_functions cmf;
  ws_screen_functions	sf;
  int 			(*attach)();
  int			(*bootmsg)();
  int 			(*map)();
  void 			(*interrupt)();
  int 			(*setup)();
  int			(*vm_hook)();
  caddr_t		p_pva;
  caddr_t		p_pva_s;
  caddr_t		p_pv;
  caddr_t		p_pv_s;
  caddr_t		p_sram;
  caddr_t		p_sram_s;
  u_int 		text_foreground;
  u_int			text_background;
  u_int			ws_display_type;
  u_int			sram_size;
} pvl_type_t;

/*
 * Brooktree BT431 structures
 */
typedef struct {
  volatile unsigned int addr_low;
  volatile unsigned int addr_high;
  volatile unsigned int cursor_ram;
  volatile unsigned int control;
} pvl_bt431_t;


typedef struct {
  pvl_bt431_t	 	*btaddr;
  pvl_bt431_t		*btaddr2;
  char type;
  char screen_on;
  char on_off;
  char dirty_cursor;
  short fb_xoffset;
  short fb_yoffset;
  short x_hot;
  short y_hot;
  int unit;
  char inited;
  void (*enable_interrupt)();
  char cursor_was_on;
  caddr_t cmap_closure;
  u_short bits[512];        
} pvl_bt431_info_t;

/*
 * Brooktree BT463 Structures
 */
typedef struct {
  volatile unsigned int addr_low;
  volatile unsigned int addr_high;
  volatile unsigned int bt_reg;
  volatile unsigned int color_map;
} pvl_bt463_t;

typedef struct {
  unsigned char dirty_cell;
  unsigned char red;	/* only need 8 bits */
  unsigned char green;
  unsigned char blue;
} pvl_bt463_color_cell_t;

typedef struct {
  unsigned char low_byte;	/* Low order 8 bits of wid P0-P7. */
  unsigned char middle_byte;	/* Middle 8 bits of wid P8-P15. */
  unsigned char high_byte;	/* High order 8 bits of wid P0-P7. */
  unsigned char unused;
} pvl_bt463_tag_cell_t;

#define	PVL_BT463_SETUP_HEAD_MASK	0x00000001
#define	PVL_BT463_SETUP_RW_MASK	0x00000002
#define	PVL_BT463_SETUP_C0_MASK	0x00000004
#define	PVL_BT463_SETUP_C1_MASK	0x00000008
#define	PVL_BT463_SETUP_C2_MASK	0x00000010

#define	PVL_BT463_DATA_WRITE_SHIFT	0
#define	PVL_BT463_DATA_READ0_SHIFT	8
#define	PVL_BT463_DATA_READ1_SHIFT	16

typedef struct {
  volatile pvl_bt463_t  *btaddr;
  char			type;
  char 			screen_on;
  char 			dirty_colormap;
  char 			dirty_cursormap;
  short 		fb_xoffset;
  short 		fb_yoffset;
  int			unit;
  void    		(*enable_interrupt)();
  caddr_t		cursor_closure;
  ws_color_cell		saved_entry;
  ws_color_cell		cursor_fg;
  ws_color_cell		cursor_bg;
  short 		min_dirty;
  short	  		max_dirty;
  pvl_bt463_color_cell_t cells[PVL_BT463_CMAP_ENTRY_COUNT];
} pvl_bt463_info_t;


/*
 * PV rendering chip packet and instruction formats
 */

/*
 * the following is calculated as follows:
 *      Per packet data maximum         38 longwords
 *      Per Primitive data              16 longwords * 255
 *      Per Vertex data (2D only)        4 longwords * 255
 *                                      ------------ 
 *      Total                           5138
 */

#define PVL_MAX_BUFFER_SIZE		(5138 * 4)
#define PVL_MAX_PRIMITIVES		255
 
        
 
/*
 * PVL_INSTR_ instruction-field macros may be used instead of 
 * the pvInstruction structure, but the latter is usually preferable.
 */

#define PVL_INSTR_OPCODE 		0
#define PVL_INSTR_DST 			8
#define PVL_INSTR_SRC1 			12
#define PVL_INSTR_SRC0 			16
#define PVL_INSTR_CCOP 			20
#define PVL_INSTR_XYEN 			22
#define PVL_INSTR_XYSENSE 		24
#define PVL_INSTR_ZEN 			25
#define PVL_INSTR_CLEN 			26
#define PVL_INSTR_CCEN 			27

#define PVL_CAP_BUTT 			0
#define PVL_CAP_NOT_LAST		1

#define	PVL_XYMASK_DATA_LENGTH		8

#define	PVL_POINTS			0
#define	PVL_LINES			1
#define	PVL_WIDE_LINES			2
#define	PVL_QUADS			3
#define	PVL_READ_BLOCKS			4
#define	PVL_WRITE_BLOCKS		5

#define	PVL_NONE			0
#define	PVL_PER_PACKET			1
#define	PVL_PER_PRIMITIVE		2
#define	PVL_PER_VERTEX			3

#define	PVL_BAD_GEOM_FMT		0
#define	PVL_BAD_Z0_FMT			1
#define	PVL_BAD_Z1_FMT			2
#define	PVL_BAD_XYMASK_FMT		3

#define	PVL_BAD_XYMASK_PTR		4

#define	PVL_QUEUED			1
#define	PVL_SENT_TO_HW			2

/*
 * opcodes 
 */
#define PVL_AND				0
#define PVL_OR				1
#define PVL_XOR				2
#define PVL_NOT				3
#define PVL_COPY			4
#define PVL_ADD				5
#define PVL_SUB				6
#define PVL_CMPLT			7
#define PVL_CMPLE			8
#define PVL_CMPEQ			9
#define PVL_CMPGE			10
#define PVL_CMPGT			11
#define PVL_CMPOVF			12
#define PVL_MULHIGH			13
#define PVL_MULLOW			14
#define PVL_ADD24			15
#define PVL_SUB24			16
#define PVL_CMPLT24			17
#define PVL_CMPLE24			18
#define PVL_CMPEQ24			19
#define PVL_CMPGE24			20
#define PVL_CMPGT24             	21

/*
 * CC OPERATION 
 */

#define PVL_CC_REPLACE			0
#define PVL_CC_AND			1
#define PVL_CC_OR			2

/*
 * xymask enable flags 
 */

#define PVL_XYMASK_DISABLE		0
#define PVL_XYMASK_16X16 		1
#define PVL_XYMASK_256X1 		2
#define PVL_XYMASK_1X256 		3
	
/*
 * xymask sense 
 */

#define PVL_XYMASK_SET_ENABLED		0
#define PVL_XYMASK_SET_DISABLED		1

/*
 * Source and Destination operands
 */

#define PVL_OPERAND_PR0			0
#define PVL_OPERAND_PR1			1
#define PVL_OPERAND_PID0		4
#define PVL_OPERAND_PID1		5
#define PVL_OPERAND_PID2		6
#define PVL_OPERAND_PID3		7
#define PVL_OPERAND_PID4		8
#define PVL_OPERAND_PID5		9
#define PVL_OPERAND_0			10
#define PVL_OPERAND_1			11
#define PVL_OPERAND_RGB0		12
#define PVL_OPERAND_RGB1		13
#define PVL_OPERAND_Z0			14
#define PVL_OPERAND_Z1			15

/*
 * PixelVision values for the 0.0 and 1.0 contstants.
 */

#define PVL_0POINT0			0
#define PVL_1POINT0			0xff


/*
 *	Structure definitions
 */ 
typedef struct
{
  unsigned geomFmt 	: 3 ; /* what primitive? */
  unsigned capStyle 	: 1 ; /* Cap Butt or Cap not last */
  unsigned clipFmt	: 2 ; /* None, per-packet, or per-primitive */
  unsigned xyMaskFmt 	: 2 ; /* None, per-packet, or per-primitive */
  unsigned zMaskFmt 	: 2 ; /* None, per-packet, or per-primitive */
  unsigned rgb0Fmt 	: 2 ; /* none,per-packet,per-primitive,or per-vertex */
  unsigned rgb1Fmt 	: 2 ; /* none,per-packet,per-primitive,or per-vertex */
  unsigned z0Fmt 	: 2 ; /* none,per-packet,per-primitive,or per-vertex */
  unsigned z1Fmt 	: 2 ; /* none,per-packet,per-primitive,or per-vertex */
  unsigned instCount 	: 4 ; /* instructions in the packet */
  unsigned pidCount 	: 2 ; /* number of pixelmap IDs in packet */
  unsigned primCount 	: 8 ; /* number of primitives in packet */
} pvl_packet_header_t, *pvl_packet_header_ptr_t;

typedef struct {
  short x;
  short y;
} pvl_point_t, *pvl_point_ptr_t;

typedef	struct
{
  unsigned	blue	 : 8;
  unsigned	green	 : 8;
  unsigned	red   	 : 8;
  unsigned	reserved : 8;
} pvl_color_t, *pvl_color_ptr_t;


typedef unsigned int
  pvl_z_mask_t,
  *pvl_z_mask_ptr_t,
  pvl_z_t,
  *pvl_z_ptr_t;

typedef struct
{
  pvl_point_t clipRectMin;
  pvl_point_t clipRectMax;
} pvl_clip_rect_t,
  *pvl_clip_rect_ptr_t;

typedef	struct
{
  unsigned	opCode 		:8;
  unsigned	dst		:4;
  unsigned	src1		:4;
  unsigned	src0		:4;
  unsigned	ccop		:2;
  unsigned	xyMask		:2;
  unsigned	xyMaskSense	:1;
  unsigned	zMaskEn		:1;
  unsigned	clipEn		:1;
  unsigned	ccEn		:1;
  unsigned	reserved	:4;
} pvl_instruction_t,
  *pvl_instruction_ptr_t;

typedef struct
{
  unsigned int data[PVL_XYMASK_DATA_LENGTH];
} pvl_xy_mask_t,
  *pvl_xy_mask_ptr_t;

typedef struct
{
  pvl_point_t    v1;
  pvl_point_t    v2;
} pvl_line_t,
  *pvl_line_ptr_t;

typedef struct
{
  pvl_point_t    v1;
  pvl_point_t    v2;
  unsigned int width;
} pvl_wide_line_t,
  *pvl_wide_line_ptr_t;

typedef struct
{
  pvl_point_t    v1;
  pvl_point_t    v2;
  pvl_point_t    v3;
  pvl_point_t    v4;
} pvl_quad_t,
  *pvl_quad_ptr_t;



/*
 * Ioctl header.
 */
typedef struct {
  short			count;
  short			clear_page_int;
  int			*p_tlb_index;
  pvl_register_t	*p_out_tlb_entries;
  vm_offset_t		*p_out_page;
  pvl_register_t	*p_out_format;
  pvl_subpixel_pair_t	*p_out_xy_min;
  pvl_subpixel_pair_t	*p_out_xy_max;
  pvl_register_t	*p_out_offset;
  pvl_register_t	*p_out_pixelmapid;
  pvl_register_t	*p_in_tlb_entries;
  vm_offset_t		*p_in_page;
  pvl_register_t	*p_in_format;
  pvl_subpixel_pair_t	*p_in_xy_min;
  pvl_subpixel_pair_t	*p_in_xy_max;
  pvl_register_t	*p_in_offset;
  pvl_register_t	*p_in_pixelmapid;
} pvl_ioc_pageoutin_t;

#define	PVL_ERRNO_RETRY_IMAGE		0x666

typedef struct {
  short			left_start;
  short			left_ncells;
  short			right_start;
  short			right_ncells;
  pvl_window_tag_cell_t	*p_left_cells;
  pvl_window_tag_cell_t	*p_right_cells;
} pvl_ioc_window_tag_t;

typedef struct {
  int			mode;
#define PVL_IOC_STEREO_NONE		0
#define	PVL_IOC_STEREO_24		1
#define	PVL_IOC_STEREO_1212		2

  int			win_tag_start;
  int			win_tag_count;
} pvl_ioc_stereo_t;

typedef struct {
  caddr_t		packet;
  int			packetSize;
} pvl_ioc_ping_t;

/*
 * PVL_IOC_IMAGE_HOST_BASE is the host virtual address equivalent of the
 * PV bus address at which the PV will see image transfers.
 *
 * PVL_IOC_IMAGE_PVL_BASE is the PV bus address of the first page of all
 * put and get image operations.  The shadow page tables are used to
 * map actual host virtual addresses to this range.
 *
 * PVL_IOC_IMAGE_MAX_SIZE is the maximum image size that can be handled.
 */
#define	PVL_IOC_IMAGE_HOST_BASE		\
  ( ( PVL_PVA_TABLE0_SIZE << ( PVL_PVA_PAGE_SHIFT - 1 ) ) | 0x800000000L )
#define	PVL_IOC_IMAGE_PVL_BASE		\
  ( ( PVL_IOC_IMAGE_HOST_BASE | PVLB_VHOST_OFFSET_LOW | ( PVLB_VHOST_OFFSET_HIGH << 32 ) ) >> 2 )
#define	PVL_IOC_IMAGE_MAX_SIZE		\
  ( PVL_INFO_SAVED_PV_TLB_MAX * PVL_PVA_PAGE_SIZE )

typedef struct {
  vm_offset_t		addr;
  u_long		size;
  int			hard_lockdown;
  caddr_t		packet;
  int			packetSize;
} pvl_ioc_image_t;

typedef struct {
    short         screen;
    short         cmd;
    union {
      unsigned long data;
      pvl_ioc_pageoutin_t	pageoutin;
      pvl_ioc_stereo_t		stereo;
      unsigned char		console_dcc;
      pvl_ioc_window_tag_t	window_tag;
      pvl_ioc_ping_t		ping;
      pvl_ioc_image_t		image;
      pvl_profile_data_t	profile;
      unsigned int		sig_mask;
#define	PVL_IOC_SIG_PMAP_FAULT		(1<<PVL_INFO_SIG_PMAP_FAULT)
#define	PVL_IOC_SIG_VA_PAGEIN		(1<<PVL_INFO_SIG_VA_PAGEIN)
#define	PVL_IOC_SIG_MODULE_ERROR	(1<<PVL_INFO_SIG_MODULE_ERROR)
#define	PVL_IOC_SIG_CLIPPING		(1<<PVL_INFO_SIG_CLIPPING)
#define	PVL_IOC_SIG_PVA_TLB1_FAULT	(1<<PVL_INFO_SIG_PVA_TLB1_FAULT)
#define	PVL_IOC_SIG_PACKET_DONE		(1<<PVL_INFO_SIG_PACKET_DONE)

      unsigned int	pid_mask;
#define	PVL_IOC_PID_PV			(1<<PVL_IOC_PID_PV_INDEX)
#define	PVL_IOC_PID_GCP			(1<<PVL_IOC_PID_GCP_INDEX)

    } info;
} pvl_ioc_t;

#define PVL_IOC_PRIVATE	_IOWR('w', (0|IOC_S), pvl_ioc_t)

#define PVL_IOC_MAP_OPTION		1
#define	PVL_IOC_MAP_OPTION_SPARSE	2
#define	PVL_IOC_GET_PID			3
#define	PVL_IOC_SET_PID			4
#define	PVL_IOC_GET_SIGNALS		5
#define	PVL_IOC_SET_SIGNALS		6
#define	PVL_IOC_PMAP_PAGEOUTIN		7
#define	PVL_IOC_GET_STEREO		8
#define	PVL_IOC_SET_STEREO		9
#define	PVL_IOC_GET_CONSOLE_DCC		10
#define	PVL_IOC_SET_CONSOLE_DCC		11
#define	PVL_IOC_WRITE_WINDOW_TAG	12

#define	PVL_IOC_NEW_BASE		16

/*
 * Peer Functions
 *
 * This section details the device-specific peer interfact functions
 * provided by the PixelVision driver.
 */

/*
 * Device ioctl declarations
 *
 * In the following, some ioctl's will have both a peer definition and
 * a workstation definition.  This is to allow server upgradability from
 * the old style access method to the new peer access method.
 */

/*
 * PEER_PVL_IOCTL_PING_PACKETS
 *
 * Delivers a rendering packet to the PV device when the device is
 * already busy and has it's buffer filled.  The value passed is a
 * pvl_peer_ping_t.
 */
#ifdef PVL_SUPPORTS_PEER
#define	PEER_PVL_IOCTL_PING_PACKETS		\
	_IOW( 'p', ( 1 | PEER_IOCTL_SPECIFIC ), peer_pvl_ping_t )
#endif
#define	PVL_IOC_PING_PACKETS		( PVL_IOC_NEW_BASE )

/*
 * PEER_PVL_IOCTL_ALLOC_STALL
 *
 * Stalls the calling thread until sufficient packets are available for
 * it to proceed.
 */
#ifdef PVL_SUPPORTS_PEER
#define	PEER_PVL_IOCTL_ALLOC_STALL		\
	_IO( 'p', ( 2 | PEER_IOCTL_SPECIFIC ), NULL )
#endif
#define	PVL_IOC_ALLOC_STALL		( PVL_IOC_NEW_BASE + 1 )

/*
 * PEER_PVL_IOCTL_DEBUG_PING_PACKETS
 *
 * A debug version of PEER_PVL_IOCTL_PING_PACKETS used in combination with
 * PEER_PVL_IOCTL_DEBUG_ALLOC_PACKETS to insure that packets are cycled
 * in the correct order and that the caller doesn't violate allocation
 * restrictions.
 */
#ifdef PVL_SUPPORTS_PEER
#define	PEER_PVL_IOCTL_DEBUG_PING_PACKETS		\
	_IOW( 'p', ( 3 | PEER_IOCTL_SPECIFIC ), peer_pvl_ping_t )
#endif

/*
 * PEER_PVL_IOCTL_DEBUG_ALLOC_PACKETS
 *
 * Companion to above to return the next free packet.  Will stall until
 * one becomes available and will then return it's index as per ping
 * convention.
 */
#ifdef PVL_SUPPORTS_PEER
#define	PEER_PVL_IOCTL_DEBUG_ALLOC_PACKETS		\
	_IOR( 'p', ( 4 | PEER_IOCTL_SPECIFIC ), int )
#endif

/*
 * PEER_PVL_IOCTL_PUT_IMAGE
 *
 * Peer interface to put an image.  The image descriptor includes a
 * range of addresses to be locked down and a short list of packets 
 * which will perform the put image operation.
 */
#ifdef PVL_SUPPORTS_PEER
#define	PEER_PVL_IOCTL_PUT_IMAGE		\
	_IOW( 'p', ( 5 | PEER_IOCTL_SPECIFIC ), peer_pvl_image_t )
#endif
#define	PVL_IOC_PUT_IMAGE		( PVL_IOC_NEW_BASE + 2 )

/*
 * PEER_PVL_IOCTL_GET_IMAGE
 *
 * Companion to previous.
 */
#ifdef PVL_SUPPORTS_PEER
#define	PEER_PVL_IOCTL_GET_IMAGE		\
	_IOW( 'p', ( 6 | PEER_IOCTL_SPECIFIC ), peer_pvl_image_t )
#endif
#define	PVL_IOC_GET_IMAGE		( PVL_IOC_NEW_BASE + 3 )

/*
 * PVL_IOC_GET_PROFILE
 *
 * Debug/performance ioctl to retrieve various interesting info
 */
#define	PVL_IOC_GET_PROFILE		( PVL_IOC_NEW_BASE + 4 ) 

/*
 * PVL_IOC_CLEAR_PROFILE
 *
 * Sets the profiling values back to zero
 */
#define	PVL_IOC_CLEAR_PROFILE		( PVL_IOC_NEW_BASE + 5 )

/*
 * External Function Declarations
 */
#ifdef KERNEL

extern int
  pvl_bt431_load_cursor(),
  pvl_bt431_recolor_cursor(),
  pvl_bt431_set_cursor_position(),
  pvl_bt431_load_formatted_cursor(),
  pvl_bt431_cursor_on_off(),
  pvl_bt431_clean_cursormap(),
  pvl_bt463_init_color_map(),
  pvl_bt463_load_color_map_entry(),
  pvlprobe(),
  pvlattach(),
  pvl_recolor_cursor(),
  pvl_video_on(),
  pvl_video_off(),
  pvl_init_screen(),
  pvl_clear_screen(),
  pvl_scroll_screen(),
  pvl_blitc(),
  pvl_which_option(),
  pvl_attach(),
  pvl_dd_attach(),
  pvl_bootmsg(),
  pvl_ioctl(),
  pvl_map_screen(),
  pvl_setup(),
  pvl_invalidate_gcp_tlb(),
  pvl_bt463_init_color_map(),
  pvl_bt463_load_color_map_entry(),
  pvl_bt431_set_cursor_position();

extern void
  pvlintr(),
  pvl_close(),
  pvl_enable_interrupt(),
  pvl_interrupt();

extern caddr_t
  pvl_init_closure(),
  pvl_bt431_init_closure(),
  pvl_bt463_init_closure();

#endif /* KERNEL */

/*
 * External Data Declarations
 */

#ifdef KERNEL

extern struct controller
  *pvlinfo[];

extern int
  npvl_types,
  npvl_softc,
  _pvl_level,
  _pvl_debug;

extern pvl_info_t
  pvl_softc[];

extern pvl_type_t
  pvl_types[];

extern pvl_bt431_info_t
  pvl_bt431_softc[],
  pvl_bt431_type[];

extern pvl_bt463_info_t
  pvl_bt463_softc[],
  pvl_bt463_type[];

#endif /* KERNEL */

#endif /* _PVL_H_ */

