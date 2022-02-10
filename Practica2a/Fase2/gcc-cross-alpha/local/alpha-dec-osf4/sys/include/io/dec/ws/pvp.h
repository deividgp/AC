/*
 * @(#)$RCSfile: pvp.h,v $ $Revision: 1.1.13.2 $ (DEC) $Date: 1996/10/11 20:19:05 $
 */
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
#ifndef	_PVP_H_
#define _PVP_H_

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/devio.h>
#include <sys/param.h>
#include <sys/malloc.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devdriver.h>

/*
 * The PVP_SUPPORTS_PEER define indicates that this revision of the PV
 * driver does support peer interface functions.  NOT!
 */
/*
#define	PVP_SUPPORTS_PEER
*/

#ifdef PVP_SUPPORTS_PEER
#include <io/dec/ws/peer.h>
#endif /* PVP_SUPPORTS_PEER */

/*
 * Historical mistake follows
 */
#ifndef NDEPTHS
#define	NDEPTHS			1
#define	NVISUALS		1
#endif

/*
 * SPL
 */
#define	PVP_RAISE_SPL()			splhigh();
#define	PVP_LOWER_SPL(_v)		splx(_v);

/*
 * PCI I/O - same order as normal assignment expression
 */
#define PVP_WR8(_adr,_dat)						      \
{									      \
    WRITE_BUS_D8((io_handle_t)_adr,(unsigned long)_dat);		      \
    wbflush();								      \
}
#define PVP_WR8I(_adr,_dat)	PVP_WR8(_adr,_dat)

#define PVP_WR16(_adr,_dat)						      \
{									      \
    u_long _t = *(u_short *)&_dat;					      \
    WRITE_BUS_D16((io_handle_t)_adr,_t);				      \
    wbflush();								      \
}
#define PVP_WR16I(_adr,_dat)						      \
{									      \
    WRITE_BUS_D16((io_handle_t)_adr,(unsigned long)_dat);		      \
    wbflush();								      \
}

#if 1
#ifndef WRITE_BUS_D24
#define WRITE_BUS_D24(A,D)	write_io_port(A,3,BUS_MEMORY,D)
#endif
#define PVP_WR24(_adr,_dat)						      \
{									      \
    u_long _t = *(u_int *)&_dat;					      \
    WRITE_BUS_D24((io_handle_t)_adr, _t);				      \
    wbflush();								      \
}
#define PVP_WR24I(_adr,_dat)						      \
{									      \
    WRITE_BUS_D24((io_handle_t)_adr, (unsigned long)_dat);		      \
    wbflush();								      \
}
#else
#define PVP_WR24(_adr,_dat)						      \
{									      \
    u_long _t = *(u_int *)&_dat;					      \
    WRITE_BUS_D16((io_handle_t)_adr, _t);				      \
    _t >>= 16;								      \
    WRITE_BUS_D8((io_handle_t)_adr+2,_t);				      \
    wbflush();								      \
}
#define PVP_WR24I(_adr,_dat)						      \
{									      \
    WRITE_BUS_D16((io_handle_t)_adr, (unsigned long)_dat);		      \
    WRITE_BUS_D8((io_handle_t)_adr+2,(unsigned long)(_dat >> 16));	      \
    wbflush();								      \
}
#endif

#define PVP_WR32(_adr,_dat)						      \
{									      \
    u_long _t = *(u_int *)&_dat;					      \
    WRITE_BUS_D32((io_handle_t)_adr,_t);				      \
    wbflush();								      \
}
#define PVP_WR32I(_adr,_dat)						      \
{									      \
    WRITE_BUS_D32((io_handle_t)_adr,(unsigned long)_dat);		      \
    wbflush();								      \
}

#define PVP_RD8(_dst,_typ,_adr)						      \
{									      \
    u_long _v;								      \
    _v = READ_BUS_D8((io_handle_t)_adr);				      \
    (_dst) = *(_typ *) &_v;						      \
}

#ifndef READ_BUS_D24
#define READ_BUS_D24(A)	(unsigned int)read_io_port(A,3,BUS_MEMORY)
#endif
#define PVP_RD24(_dst,_typ,_adr)					      \
{									      \
    u_long _v;								      \
    _v = READ_BUS_D24((io_handle_t)_adr);				      \
    (_dst) = *(_typ *) &_v;						      \
}

#define PVP_RD32(_dst,_typ,_adr)					      \
{									      \
    u_long _v;								      \
    _v = READ_BUS_D32((io_handle_t)_adr);				      \
    (_dst) = *(_typ *) &_v;						      \
}

#define pvp_polled(a,b,c,d)
#define PVP_POLL(_i,_s,_t,_p,_o,_l)					      \
{									      \
    pvp_polled(_i,_o,_l,0);						      \
    PVP_RD32(_s,_t,_p);							      \
}

/*
 * Subpixel coordinate access macros.
 */
#define	PVP_SUBPIX_GET_FRAC( _sp )	((unsigned short) ((_sp) & 0x7))
#define	PVP_SUBPIX_GET_WHOLE( _sp )	((short) (((short) (_sp)) >> 3 ))
#define	PVP_SUBPIX_MAKE( _w, _f )	((unsigned short) ((((unsigned short) (_w))<<3)|(((unsigned short)(_f))&0x7)))

/*
 * Server/Driver interface magic numbers
 */
#define	PVP_PVQM_SIZE			(1<<17)
#define	PVP_INVALID_PIXELMAP_ID		2
#define	PVP_DOORBELL_0_PIXELMAP_ID	3
#define	PVP_DOORBELL_1_PIXELMAP_ID	4
#define	PVP_PIXELMAP_DCC_MASK		0x8000
#define	PVP_IOC_PAGEOUTIN_COUNT_MAX	16
#define	PVP_IOC_PID_PV_INDEX		0 /* RM process */
#define	PVP_IOC_PID_GCP_INDEX		1 /* server process */
#define	PVP_IOC_PID_NUM			2

/*
 * Address access macros
 */
#define PVP_BASE(C)		(((pvp_info_t *)(C))->io_pvo)

/*
 * Module Definitions.  Significant structures on the module.
 */
#define PVP_RENDER_OFFSET	    	0x00000000L
#define	PVP_SRAM_OFFSET			0x00600000L
#define PVP_PIC_CSR_OFFSET		0x00700000L
#define	PVP_VDAC_OFFSET			0x00701000L
#define PVP_RENDER_ALIAS_OFFSET		0x00800000L

#define	PVP_MODULE_SIZE			0x00200000L
#define PVP_FULL_MODULE_SIZE	    	0x00800000L

#define	PVP_SPARSE_SRAM_OFFSET		(PVP_SRAM_OFFSET << 5)
#define	PVP_SPARSE_RENDER_OFFSET	(PVP_RENDER_OFFSET << 5)
#define PVP_SPARSE_MODULE_SIZE		(PVP_MODULE_SIZE << 5)
#define PVP_SPARSE_FULL_MODULE_SIZE	(PVP_FULL_MODULE_SIZE << 5)

#if 0
/*
 * XXX Module and System Addresses as seen from the PVbus
 */
#define	PVPB_RENDER_OFFSET_HIGH		0x00000000L
#define	PVPB_RENDER_OFFSET_LOW		0x00000000L
#define	PVPB_SRAM_OFFSET_HIGH		0x00000000L
#define	PVPB_SRAM_OFFSET_LOW		0x00800000L
/* physical host address */
#define	PVPB_PHOST_OFFSET_HIGH		0x00080000L
#define	PVPB_PHOST_OFFSET_LOW		0x00000000L
/* virtual host address */
#define	PVPB_VHOST_OFFSET_HIGH		0x00180000L
#define	PVPB_VHOST_OFFSET_LOW		0x00000000L
#endif

/*
 * Locate major module structures
 */
#define PVP_PIC_CSR_BASE(_pi)	((pvp_pic_csr_t *) (PVP_BASE(_pi) + PVP_PIC_CSR_OFFSET))

#define	PVP_VDAC_BASE(_pi)	(PVP_BASE(_pi) + PVP_VDAC_OFFSET)

/*
 * TLB Description
 *
 * _ENTRIES gives the number of TLB entries implemented and _TOTAL
 * the number provided for in the module addressing.
 */
#define	PVP_RENDER_TLB_ENTRIES	256
#define	PVP_RENDER_TLB_TOTAL	256


/*
 * Access to SRAM
 */
#define	PVP_SRAM_BASE(_pi)	((unsigned int *)(PVP_BASE(_pi) + PVP_SRAM_OFFSET))

/*
 * PV Renderer Registers
 */
#define	PVP_REND_DMA_OFFSET	((vm_offset_t) 0x00040000)
#define	PVP_REND_IMP_OFFSET	((vm_offset_t) 0x00080000)
#define	PVP_REND_TLB_OFFSET	((vm_offset_t) 0x000c0000)
#define	PVP_REND_POLL_OFFSET	((vm_offset_t) 0x00100000)
#define	PVP_REND_VIDEO_OFFSET	((vm_offset_t) 0x00140000)

/*
 * Access to PV - kernel always uses secure ping address space
 */
#define	PVP_REND_BASE(_pi)	(PVP_BASE(_pi) + PVP_RENDER_OFFSET)
#define PVP_REND_ALIAS_BASE(_pi) (PVP_BASE(_pi) + PVP_RENDER_ALIAS_OFFSET)

#define	PVP_REND_IMP_BASE(_pi)	((pvp_render_implement_t *)		      \
				 (PVP_REND_BASE(_pi) + PVP_REND_IMP_OFFSET ))
#define	PVP_REND_DMA_BASE(_pi)	((pvp_render_dma_t *)			      \
				 (PVP_REND_BASE(_pi) + PVP_REND_DMA_OFFSET ))
#define	PVP_REND_TLB_BASE(_pi)	((pvp_graphic_tlb_t *)			      \
				 (PVP_REND_BASE(_pi) + PVP_REND_TLB_OFFSET ))
#define	PVP_REND_VIDEO_BASE(_pi) ((pvp_render_video_t *)		      \
				  (PVP_REND_BASE(_pi) + PVP_REND_VIDEO_OFFSET ))

/*
 * PV Renderer Polling Register
 */
#define	PVP_REND_POLL_STATUS_FREE	0

/* 0x20000 means host, not sram */
#define	PVP_REND_HOST_TO_POLL(_pa) ((vm_offset_t)			      \
				    (PVP_REND_POLL_OFFSET |		      \
				     0x00020000 |			      \
				     (((unsigned int) (_pa) & 0x03fff000) >> 9)))

#define PVP_SPARSE_REND_HOST_TO_POLL(_pa) (PVP_REND_HOST_TO_POLL(_pa) << 5)

/*
 * Interrupt status manipulations
 */
#define	PVP_INT_STEREO		0x01
#define	PVP_INT_VSYNC		0x02
#define	PVP_INT_PAGE		0x04
#define	PVP_INT_VM		0x08
#define	PVP_INT_RENDER		0x10
#define	PVP_INT_PACKET		0x20
#define	PVP_INT_STALL		0x20

/* test _a superset _b */
#define PVP_INT_SUPERSET(_a,_b) (((_a)&(_b))==(_b))

#define	PVP_INT_ENABLE(_pvp,_mask)					      \
{									      \
    pvp_render_implement_t *_p_rend_imp = PVP_REND_IMP_BASE( _pvp );	      \
    pvp_render_config_t _rc;						      \
    PVP_RD32( _rc, pvp_render_config_t, &_p_rend_imp->config );		      \
    if ( (_mask) & PVP_INT_STEREO ) _rc.stereo = 1;			      \
    if ( (_mask) & PVP_INT_VSYNC ) _rc.vsync = 1;			      \
    if ( (_mask) & PVP_INT_PAGE ) _rc.page = 1;				      \
    if ( (_mask) & PVP_INT_VM ) _rc.vm = 1;				      \
    if ( (_mask) & PVP_INT_RENDER ) _rc.render = 1;			      \
    if ( (_mask) & PVP_INT_PACKET ) _rc.packet = 1;			      \
    _rc.block_en = 0xff;						      \
    (_pvp)->render_config = _rc;					      \
    PVP_WR32( &_p_rend_imp->config, _rc);				      \
}

#define	PVP_INT_DISABLE(_pvp,_mask)					      \
{									      \
    pvp_render_implement_t *_p_rend_imp = PVP_REND_IMP_BASE( _pvp );	      \
    pvp_render_config_t _rc;						      \
    PVP_RD32( _rc, pvp_render_config_t, &_p_rend_imp->config);		      \
    if ( (_mask) & PVP_INT_STEREO ) _rc.stereo = 0;			      \
    if ( (_mask) & PVP_INT_VSYNC ) _rc.vsync = 0;			      \
    if ( (_mask) & PVP_INT_PAGE ) _rc.page = 0;				      \
    if ( (_mask) & PVP_INT_VM ) _rc.vm = 0;				      \
    if ( (_mask) & PVP_INT_RENDER ) _rc.render = 0;			      \
    if ( (_mask) & PVP_INT_PACKET ) _rc.packet = 0;			      \
    _rc.block_en = 0xff;						      \
    (_pvp)->render_config = _rc;					      \
    PVP_WR32( &_p_rend_imp->config, _rc);				      \
}

#define	PVP_INT_CLEAR(_pvp,_mask)					      \
{									      \
    pvp_render_implement_t *_p_rend_imp = PVP_REND_IMP_BASE( _pvp );	      \
    pvp_render_status_t _rs;						      \
    PVP_RD32( _rs, pvp_render_status_t, &_p_rend_imp->status);		      \
    _rs.vsync_int = !( (_mask) & PVP_INT_VSYNC );			      \
    _rs.page_int = !( (_mask) & PVP_INT_PAGE );				      \
    _rs.vm_int = !( (_mask) & PVP_INT_VM );				      \
    _rs.render_int = !( (_mask) & PVP_INT_RENDER );			      \
    _rs.packet_int = !( (_mask) & PVP_INT_PACKET );			      \
    if ( (_mask) & PVP_INT_STALL ) _rs.stall = 0;			      \
    _pvp->render_status = _rs;						      \
    PVP_WR32( &_p_rend_imp->status, _rs);				      \
}

/*
 * Debug printing defines
 */
#define PVP_SILENT		0
#define PVP_CONSOLE		1
#define PVP_PSST		2
#define PVP_TERSE		3
#define PVP_TALK		4
#define PVP_YAK			5
#define PVP_GAB			7
#define PVP_BLAB		10
#define PVP_YOW			13
#define PVP_NEVER		99
#define PVP_DEBUGGING		PVP_TALK
#define PVP_PANIC		PVP_SILENT

/*
#define PVP_NODEBUG
*/

#ifdef  PVP_NODEBUG
#	define PVP_DEBUG(L,S)
#else
#	define PVP_DEBUG(L,S)	if ((L) <= _pvp_debug) { S }
#endif /* PVP_NODEBUG */

/*
 * IBM561 Defines
 */

typedef struct {
    int width;
    int heigth;
    int depth;
} curs_ram_t;

typedef struct {
    vm_offset_t		phys_base;
    vm_offset_t		bus_base;
    vm_size_t		map_size;
} pvp_dma_map_t;

typedef struct {
    int			alloc_map_num; /* input */
    int			actual_map_num;	/* output */
    pvp_dma_map_t	*maps; /* input & output */
} pvp_ioc_dma_info_t;


#define PVP_MSPEC(H,V,R)	(((((H)<<16)+(V))<<16)+R)

/*
 * Resolution flags
 */
#define PVP_VIDEO_HOE	0x20
#define	PVP_VIDEO_SOG	(0x02|PVP_VIDEO_HOE)
#define PVP_VIDEO_SYNC	(PVP_VIDEO_SOG|PVP_VIDEO_HOE)
#define	PVP_VIDEO_STEREO	1

typedef struct {
    long	mspec;
    int		flags;
    int		hz;
    int		PllM;
    int		PllN;
    int		PllPFR;
    int		vgaMisc;
    int		vgaN;
    int		vgaD;
    int		vgaP;
    int		Vactive;
    int		Vblank;
    int		VSFporch;
    int		VSWidth;
    int		vgaVblankFP;
    int		vgaVblankBP;
    int		Hactive;
    int		Hblank;
    int		HSFporch;
    int		HSWidth;
    int		vgaHblankFP;
    int		vgaHblankBP;
} pvp_monitor_data_t;
    
typedef struct {
    int		hres;
    int		vres;
    int		vref;
} pvp_ioc_monitor_t;

/*
 * for backward compat, 463 window tags are mapped to 561 format.
 */
typedef struct {
    unsigned char	windex;
    unsigned char	low;
    unsigned char	mid;
    unsigned char	high;
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_window_tag_cell_t;

typedef struct {
    char	windex;
    int         clut_start;     /* color lookup table starting address  */
    int         cpix_format;    /* pixel format(depth)                  */
    int         cbuffer;        /* frame buffer selection (A, B or C)   */
    int         cmode;          /* index, grey scale, direct, true color*/
    int         ol_start;       /* color lookup table starting address  */
    int         opix_format;    /* pixel format(depth)                  */
    int         obuffer;        /* overlay buffer selection (A, B or C) */
    int         omode;          /* index, grey scale, direct, true color*/
    int         ov_mask;        /* mask overlay data?                   */
} pvp_561_window_tag_cell_t;

typedef struct {
    short			left_start;
    short			left_ncells;
    short			right_start;
    short			right_ncells;
    pvp_window_tag_cell_t	*p_left_cells;
    pvp_window_tag_cell_t	*p_right_cells;
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_ioc_window_tag_t;

#define	PVP_RAMDAC_561_ADDR_LOW			0x00
#define	PVP_RAMDAC_561_ADDR_HIGH		0x04

#define	PVP_RAMDAC_561_ADDR_REG			0x8
#define	PVP_RAMDAC_561_ADDR_LUT			0xC

#define PVP_RAMDAC_561_CONFIG_REG_1		0x0001
#define PVP_RAMDAC_561_CONFIG_REG_2		0x0002
#define PVP_RAMDAC_561_CONFIG_REG_3		0x0003
#define PVP_RAMDAC_561_CONFIG_REG_4		0x0004
#define PVP_RAMDAC_561_INTERLEAVE_REG		0x0005
#define PVP_RAMDAC_561_WAT_SEG_REG		0x0006
#define PVP_RAMDAC_561_OL_SEG_REG		0x0007
#define PVP_RAMDAC_561_CHROMA_KEY_REG0		0x0010
#define PVP_RAMDAC_561_CHROMA_KEY_REG1		0x0011
#define PVP_RAMDAC_561_CHROMA_MASK_REG0		0x0012
#define PVP_RAMDAC_561_CHROMA_MASK_REG1		0x0013
#define PVP_RAMDAC_561_SYNC_CTRL_REG		0x0020
#define PVP_RAMDAC_561_PLL_DIV_REG		0x0021
#define PVP_RAMDAC_561_PLL_REF_REG		0x0022
#define PVP_RAMDAC_561_CURSOR_CTRL_REG		0x0030
#define PVP_RAMDAC_561_CURSOR_HS_REG		0x0034
#define PVP_RAMDAC_561_SCISSOR_REG		0x0040
#define PVP_RAMDAC_561_VRAM_MASK_REG		0x0050
#define PVP_RAMDAC_561_DAC_CTRL_REG		0x005f

#define	PVP_RAMDAC_561_READ_MASK		0x0205
#define	PVP_RAMDAC_561_BLINK_MASK		0x0209
#define	PVP_RAMDAC_561_FB_WINDOW_TYPE_TABLE	0x1000
#define	PVP_RAMDAC_561_AUXFB_WINDOW_TYPE_TABLE	0x0E00
#define	PVP_RAMDAC_561_OL_WINDOW_TYPE_TABLE	0x1400
#define	PVP_RAMDAC_561_AUXOL_WINDOW_TYPE_TABLE	0x0F00
#define	PVP_RAMDAC_561_RED_GAMMA_TABLE		0x3000
#define	PVP_RAMDAC_561_GREEN_GAMMA_TABLE	0x3400
#define	PVP_RAMDAC_561_BLUE_GAMMA_TABLE		0x3800
#define	PVP_RAMDAC_561_COLOR_LOOKUP_TABLE	0x4000
#define	PVP_RAMDAC_561_CURSOR_LOOKUP_TABLE	0x0a11
#define	PVP_RAMDAC_561_CURSOR_BLINK_TABLE	0x0a15
#define	PVP_RAMDAC_561_CROSS_LOOKUP_TABLE	0x0a19
#define	PVP_RAMDAC_561_CROSS_BLINK_TABLE	0x0a1d
#define	PVP_RAMDAC_561_CURSOR_PIXMAP		0x2000
#define	PVP_RAMDAC_561_CURSOR_X_LOW		0x0036
#define	PVP_RAMDAC_561_CURSOR_X_HIGH		0x0037
#define	PVP_RAMDAC_561_CURSOR_Y_LOW		0x0038
#define	PVP_RAMDAC_561_CURSOR_Y_HIGH		0x0039

#define PVP_561_ADDR(_pvp,_addr)					      \
{									      \
    io_handle_t _vdac = (io_handle_t) PVP_VDAC_BASE(_pvp);		      \
    PVP_WR8(_vdac | PVP_RAMDAC_561_ADDR_LOW, _addr & 0xff);		      \
    PVP_WR8(_vdac | PVP_RAMDAC_561_ADDR_HIGH, _addr >> 8);		      \
}

/*
 * read/write 1-4 bytes of data to either vdac registers or lut/wat
 */
#define PVP_561_RDREG8(_pvp,_dst,_typ)	PVP_RD8(_dst,_typ,PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG)

#define PVP_561_WRREG8(_pvp,_dat)	PVP_WR8(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)
#define PVP_561_WRREG8I(_pvp,_dat)	PVP_WR8I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)
#define PVP_561_WRREG16(_pvp,_dat)	PVP_WR16(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)
#define PVP_561_WRREG16I(_pvp,_dat)	PVP_WR16I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)
#define PVP_561_WRREG24(_pvp,_dat)	PVP_WR24(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)
#define PVP_561_WRREG24I(_pvp,_dat)	PVP_WR24I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)
#define PVP_561_WRREG32(_pvp,_dat)	PVP_WR32(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)
#define PVP_561_WRREG32I(_pvp,_dat)	PVP_WR32I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_REG, _dat)

#define PVP_561_WRLUT8(_pvp,_dat)	PVP_WR8(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)
#define PVP_561_WRLUT8I(_pvp,_dat)	PVP_WR8I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)
#define PVP_561_WRLUT16(_pvp,_dat)	PVP_WR16(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)
#define PVP_561_WRLUT16I(_pvp,_dat)	PVP_WR16I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)
#define PVP_561_WRLUT24(_pvp,_dat)	PVP_WR24(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)
#define PVP_561_WRLUT24I(_pvp,_dat)	PVP_WR24I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)
#define PVP_561_WRLUT32(_pvp,_dat)	PVP_WR32(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)
#define PVP_561_WRLUT32I(_pvp,_dat)	PVP_WR32I(PVP_VDAC_BASE(_pvp)+PVP_RAMDAC_561_ADDR_LUT, _dat)

#define PVP_561_WAT10(_h,_l) (((_l & 0xfc) >> 2) |			      \
			      ((_h & 3) << 6) |				      \
			      ((_l & 3) << 14));

typedef union {
    struct {
	unsigned char	low_byte;
	unsigned char	high_byte;
    } wat_in_bytes;
    struct {
	unsigned 		tr:1;
	unsigned		mode:2;
	unsigned		bs:1;
	unsigned 		pix:2;
	unsigned		addr:4;
	unsigned		resv:6;
    } wat_in_bits;
} fb_wid_cell_t; 

typedef struct {
    int			windex:16;
    fb_wid_cell_t  	entry;
} pvp_561_fb_wid_cell_t;

typedef union {
    unsigned char		aux_fbwat;
    struct {
	unsigned 		pt:1;
	unsigned		xh:1;
	unsigned		gma:1;
	unsigned		resv:5;
    } wat_in_bits;
} aux_fb_wid_cell_t;

typedef struct {
    int			windex:8;
    aux_fb_wid_cell_t  	entry;
} pvp_561_aux_fb_wid_cell_t;

typedef union {
    struct {
	unsigned char	low_byte;
	unsigned char	high_byte;
    } wat_in_bytes;
    struct {
	unsigned 		tr:1;
	unsigned		mode:2;
	unsigned		bs:1;
	unsigned 		pix:2;
	unsigned		addr:4;
	unsigned		resv:6;
    } wat_in_bits;
} ol_wid_cell_t;

typedef struct {
    int			windex:16;
    ol_wid_cell_t   	entry;
} pvp_561_ol_wid_cell_t;

typedef union {
    unsigned char		aux_olwat;
    struct {
	unsigned 		ot:1;
	unsigned		xh:1;
	unsigned		gb:1;
	unsigned		ol:1;
	unsigned		ul:1;
	unsigned		ck:1;
	unsigned		resv:2;
    } wat_in_bits;
} aux_ol_wid_cell_t;

typedef struct {
    int			windex:8;
    aux_ol_wid_cell_t  	entry;
} pvp_561_aux_ol_wid_cell_t;


/*  
 * There are actually 256 window tag entries in the FB and OL WAT tables.
 * We will use only 16 for compatability with the BT463 and more importantly
 * to implement the virtual ramdac interface.  This requires us to only
 * report the smallest WAT table size, in this case its the auxillary wat
 * tables which are 16 entries.
 */
#define	PVP_RAMDAC_561_FB_WINDOW_TAG_COUNT		256
#define	PVP_RAMDAC_561_FB_WINDOW_TAG_MAX_COUNT		8
#define	PVP_RAMDAC_561_AUXFB_WINDOW_TAG_COUNT		16
#define	PVP_RAMDAC_561_AUXFB_WINDOW_TAG_MAX_COUNT	16
#define	PVP_RAMDAC_561_OL_WINDOW_TAG_COUNT		256
#define	PVP_RAMDAC_561_OL_WINDOW_TAG_MAX_COUNT		16
#define	PVP_RAMDAC_561_AUXOL_WINDOW_TAG_COUNT		16
#define	PVP_RAMDAC_561_AUXOL_WINDOW_TAG_MAX_COUNT	16
#define	PVP_RAMDAC_561_CMAP_ENTRY_COUNT			1024
#define	PVP_RAMDAC_561_GAM_ENTRY_COUNT			256

typedef struct {
    io_handle_t			addr;
    short			fb_xoffset;
    short			fb_yoffset;
    short			min_dirty;
    short			max_dirty;
    u_int			mask;
} pvp_561_type_t;

typedef struct {
    unsigned char		dirty_cell;
    unsigned char		red;
    unsigned char		green;
    unsigned char		blue;
} pvp_561_color_cell_t;

typedef struct {
    unsigned char		dirty_cell;
    unsigned char		low;
    unsigned char		high;
    unsigned char		reserved;
} pvp_561_gamma_cell_t;

typedef struct {
    io_handle_t		addr;
    short 		fb_xoffset;
    short 		fb_yoffset;
    short		min_dirty;
    short		max_dirty;
    u_int		mask;
    /* everything above this line must match pvp_561_types_t */
    char		type;
    char 		screen_on;
    char		on_off;
    short		x_hot;
    short		y_hot;
    ws_color_cell	cursor_fg;
    ws_color_cell	cursor_bg;
    int                 cursor_position;
    char 		dirty_colormap;
    char 		dirty_gammamap;
    char 		dirty_cursor;
    char 		dirty_cursor_pos;
    int			unit;
    void		(*enable_interrupt)();
    caddr_t		cursor_closure;
    short		cmap_min_dirty;
    short		cmap_max_dirty;
    short		gam_min_dirty;
    short		gam_max_dirty;
    pvp_561_color_cell_t cmap_cells[PVP_RAMDAC_561_CMAP_ENTRY_COUNT];
    pvp_561_gamma_cell_t gam_cells[PVP_RAMDAC_561_GAM_ENTRY_COUNT];
    unsigned int	bits[256];
} pvp_561_info_t;

/*
 * Typedefs
 */

/*
 * Basic Data Type Definitions - DO NOT CHANGE
 */
typedef unsigned int
  pvp_register_t;

typedef unsigned long
  pvp_bus_addr_t;

typedef unsigned int
  pvp_halfaddr_t;

typedef struct {
    pvp_halfaddr_t		low;
    pvp_halfaddr_t		high;
} pvp_bus_addr2_t;

typedef short
  pvp_subpixel_t;

typedef struct {
    pvp_subpixel_t		x;
    pvp_subpixel_t		y;
} pvp_subpixel_pair_t;

typedef struct {
    unsigned int
	pixelmap_id : 15,
	x : 6,
	y : 6,
	dirty : 1,
	: 4;
} pvp_graphic_tlb_t;

/*
 * PV Register Definitions
 */
#define	PVP_RENDER_IMP_USZ_4X2		0
#define	PVP_RENDER_IMP_USZ_4X4		1
#define	PVP_RENDER_IMP_USZ_8X2		2
#define	PVP_RENDER_IMP_USZ_8X4		4

#define	PVP_RENDER_IMP_VSZ_1024X1024	0
#define	PVP_RENDER_IMP_VSZ_1280X1024	1
#define	PVP_RENDER_IMP_VSZ_2048X1024	2
#define	PVP_RENDER_IMP_VSZ_2048X1536	3
#define	PVP_RENDER_IMP_VSZ_2048X2048	4
#define	PVP_RENDER_IMP_VSZ_UNSUPPORTED	5

typedef struct {
    unsigned int
	min : 4,
	major : 4,
	implement : 8,
	update_size : 4,
	vis_pmap_size : 4,
	mem_size : 5,
	reserved : 3;
} pvp_render_imp_rev_t;

typedef struct {
    unsigned int
	max_pkts : 8,			/* 0x000ff */
	: 1,				/* 0x00100 */
	stereo : 1,			/* 0x00200 */
	vsync : 1,			/* 0x00400 */
	page : 1,			/* 0x00800 */
	vm : 1,				/* 0x01000 */
	render : 1,			/* 0x02000 */
	packet : 1,			/* 0x04000 */
	block_en : 4,			/* 0x78000 */
	: 13;
} pvp_render_config_t;

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
} pvp_render_status_t;

typedef struct {
    pvp_register_t		tlb_addr;
    pvp_render_imp_rev_t	imp_rev;
    pvp_render_config_t		config;
    pvp_render_status_t		status;
} pvp_render_implement_t;

#define	PVP_RENDER_DMA_FORMAT_RGB		0
#define	PVP_RENDER_DMA_FORMAT_DCC		1

#define	PVP_RENDER_DMA_RW_WRITE			0
#define	PVP_RENDER_DMA_RW_READ			1

typedef struct {
    pvp_register_t	pixelmap_id;
    pvp_register_t	pad0;
    pvp_subpixel_pair_t	xy_min;
    pvp_subpixel_pair_t	xy_max;
    pvp_register_t	addr_low;
    pvp_register_t	addr_high;
    pvp_register_t	pad1;
    pvp_register_t	offset;
    pvp_register_t	format;
    pvp_register_t	read_write;
    pvp_register_t	status;
} pvp_render_dma_t;

typedef struct {
    pvp_register_t	vblank_s;
    pvp_register_t	vblank_f;
    pvp_register_t	vsync_s;
    pvp_register_t	vsync_f;
    pvp_register_t	hblank_s;
    pvp_register_t	hblank_f;
    pvp_register_t	hsync2;
    pvp_register_t	pad0;
    pvp_register_t	hsync_s;
    pvp_register_t	hsync_f;
    pvp_register_t	crt_enable;
} pvp_render_video_t;

typedef struct {
    unsigned int
	: 1,				/* 0 */
	dma_aborted_int : 1,		/* 1 */
	: 1,				/* 2 */
	clk_sync_status : 1,		/* 3 */
	clk_reset : 1,			/* 4 */
	pb_soft_reset : 1,		/* 5 */
	s1280x1024 : 1,			/* 6 */
	base_addr : 6,			/* 12:7 */
	expmod_prsnt : 1,		/* 13 */
	usize_4x4 : 1,			/* 14 */
	host_dma_wren : 1,		/* 15 */
	vga_portsel : 1,		/* 16 */
	mda_decode_en : 1,		/* 17 */
	rom_prsnt : 1,			/* 18 */
	vclk_prsnt : 1,			/* 19 */
	vclktype_ad : 1,		/* 20 */
	dac_prsnt : 1,			/* 21 */
	dactype_vga : 1,		/* 22 */
	vga_prsnt : 1,			/* 23 */
	vgafc_en : 1,			/* 24 */
	vga_reset : 1,			/* 25 */
	ub_go_fast : 1,			/* 26 */
	fastmode_en : 1,		/* 27 */
	prefetch_en : 1,		/* 28 */
	revision : 3;			/* 29:31 */
} pvp_pic_csr_t;

#define PVP_VGA_ON(_pvp) (console_io_handle == _pvp->io_pvo &&		      \
			  _pvp->pic_csr.vga_prsnt &&			      \
			  (_pvp->state & PVP_INFO_STATE_VALID) == 0)

#define PVP_WR_ENABLE(_pvp)						      \
{									      \
    pvp_pic_csr_t *_pic;						      \
    _pic = PVP_PIC_CSR_BASE( _pvp );					      \
    PVP_RD32( _pvp->pic_csr, pvp_pic_csr_t, _pic );			      \
    _pvp->pic_csr.host_dma_wren = 1;					      \
    PVP_WR32( _pic, _pvp->pic_csr );					      \
}

#define PVP_WR_DISABLE(_pvp)						      \
{									      \
    pvp_pic_csr_t *_pic;						      \
    _pic = PVP_PIC_CSR_BASE( _pvp );					      \
    PVP_RD32( _pvp->pic_csr, pvp_pic_csr_t, _pic );			      \
    _pvp->pic_csr.host_dma_wren = 0;					      \
    PVP_WR32( _pic, _pvp->pic_csr );					      \
}

#define PVP_PIC_PUSH(_pvp,_op)						      \
{									      \
    pvp_pic_csr_t _csr, *_pic;						      \
    _pic = PVP_PIC_CSR_BASE( _pvp );					      \
    PVP_RD32( _pvp->pic_csr, pvp_pic_csr_t, _pic );			      \
    if (_pvp->pic_csr.base_addr == 0 && _pvp->image_in_progress == 0) {	      \
	printf("pvp: bad pic push %08x %08x\n",				      \
	       *(unsigned int *)&_pvp->pic_csr_/**/_op,			      \
	       *(unsigned int *)&_pvp->pic_csr);			      \
    }									      \
    _pvp->pic_csr_/**/_op = _pvp->pic_csr;				      \
    _pvp->pic_csr.base_addr = 0;					      \
    PVP_WR32( _pic, _pvp->pic_csr );					      \
}

#define PVP_PIC_POP(_pvp,_op)						      \
{									      \
    pvp_pic_csr_t *_pic;						      \
    _pic = PVP_PIC_CSR_BASE( _pvp );					      \
    if (_pvp->pic_csr_/**/_op.base_addr == 0 &&				      \
	_pvp->image_in_progress == 0)					      \
    {									      \
	printf("pvp: bad pic pop %08x %08x\n",				      \
	       *(unsigned int *)&_pvp->pic_csr_/**/_op,			      \
	       *(unsigned int *)&_pvp->pic_csr);			      \
    }									      \
    _pvp->pic_csr = _pvp->pic_csr_/**/_op;				      \
    PVP_WR32( _pic, _pvp->pic_csr );					      \
}
    
#define PVP_PIC_ADDR_USE_BASE	47
#define PVP_PIC_ADDR_HOST_SPACE	48


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
    unsigned int		ping_queued_count;
    unsigned int		total_intr_count;
    unsigned int		packet_intr_count;
    unsigned int		vm_intr_count;
    unsigned int		render_intr_count;
    unsigned int		doorbell_intr_count;
    unsigned int		vsync_intr_count;
    unsigned int		dma_mapfail_total;
    unsigned int		dma_mapfail_pmap;
    unsigned int		dma_wait_doorbell;
    unsigned int		dma_eof;
    unsigned int		pmap_intr_count;
    unsigned int		pmap_unfielded_faults;
    unsigned int		pmap_zero_count;
    unsigned int		pmap_invalid_saved_tlb;
    unsigned int		pmap_bad_pid_count;
    unsigned int		pmap_pageoutin_count;
} pvp_profile_data_t;

/* 
 * pvp_attach_info_t
 *
 * This structure returns information about the device mapping back to 
 * a thread that has attached to the PV peer interface.
 */
#define	PVP_INFO_SIG_PMAP_FAULT			0
#define	PVP_INFO_SIG_VA_PAGEIN			1
#define	PVP_INFO_SIG_MODULE_ERROR		2
#define	PVP_INFO_SIG_CLIPPING			3
#define	PVP_INFO_SIG_PACKET_DONE		5
#define	PVP_INFO_SIG_NUM			6

#define PVP_SCRATCH_SIZE	((1<<12) * sizeof(int *))

typedef struct { /*.same as PVL, except some fields aren't filled */
    caddr_t			p_pvo;
    caddr_t			p_pvo_s;
    caddr_t			p_gcp;
    caddr_t			p_gcp_s;	/* XXX */
    caddr_t			p_pva;
    caddr_t			p_pva_s;	/* XXX */
    caddr_t			p_pv;
    caddr_t			p_pv_s;
    caddr_t			p_sram;
    caddr_t			p_sram_s;	/* XXX */
    unsigned int		vram_size;	/* in pixels */
    unsigned int		sram_size;
    unsigned int		pixelmap_size;	/* in pixels */
    unsigned int		pixelmap_count;
    unsigned int		update_size;
    unsigned int		vis_pmap_size;
    unsigned int		monitor_rate;
    unsigned int		page_table_0_size; /* XXX */
    pvp_register_t		phys_page_table_0; /* XXX */
    caddr_t 			*p_page_table_0; /* XXX */
    unsigned int		ppn_dead_area;
    caddr_t			phys_dead_area;
    caddr_t			phys_clip_area;
    caddr_t			phys_info_area;
    caddr_t			phys_cmd_area;
    unsigned int		cmd_area_size;
    caddr_t			p_cmd_area;
    caddr_t			p_clip_area;
    caddr_t			p_dead_area;
    caddr_t			pagein_vaddr;
    unsigned short		pagein_page_count;
    unsigned short		pagein_dirty;
    unsigned int		signal_reasons[PVP_INFO_SIG_NUM];
    caddr_t			pPingBase;	/* XXX */
    caddr_t			pModuleBase;	/* XXX */
    caddr_t			pSRAMBase;	/* XXX */
    pvp_render_implement_t	*pRenderBase;	/* XXX */
    caddr_t			packetArray;
    unsigned int		packetArraySize;
    unsigned int		pollBusy;
    caddr_t			packetGet;
    caddr_t			packetPolled;
    caddr_t			chainedPacket;
    unsigned int		chainedPacketSize;
    caddr_t			packet_poll_base;
    caddr_t			fault_tlb; /* XXX */
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_attach_info_t;

/*
 * pvp_dma_handle
 */
#define PVP_DMA_DEFFLAGS (DMA_ALL | DMA_CONTIG )

typedef struct {
    u_int		valid;
    u_int		locked;
    u_int		loaded;
    u_int		size;
    u_int		max;
    u_int		flags;
    vm_offset_t		start;
    dma_handle_t	dma_handle;
} pvp_dma_handle;


/*
 * pvp_type_t
 *
 * Parallels the pvp_info_t structure.
 */
typedef struct {
  ws_screen_descriptor	screen;
  ws_depth_descriptor	depth[NDEPTHS];
  ws_visual_descriptor	visual[NVISUALS];
  u_char		cursor_type;
  u_char		cmap_type;
  u_char		screen_type;
  ws_cursor_functions	cf;
  ws_color_map_functions cmf;
  ws_screen_functions	sf;
  int 			(*attach)();
  int			(*bootmsg)();
  int 			(*map)();
  void 			(*interrupt)();
  int 			(*setup)();
  int			(*vm_hook)();
  u_int 		text_foreground;
  u_int			text_background;
  u_int			ws_display_type;
} pvp_type_t;


/*
 * IBM561 Structures
 */
typedef struct {
    int wat_table;			/* is there a wat table           */ 
    int wat_table_len;			/* number of table entries        */
    int buffering;			/* buffering capabilities (1/2/3) */
    int color_table_size;		/* number of color table entries  */
    int min_color_depth;		/* minimum color table size       */
    int gamma_table;			/* is there a gamma pallete       */
    int gamma_table_size;		/* number of gamma table entries  */
    int gamma_table_depth;		/* depth of an entry in bits      */
    int overlay_table;			/* is there an overlay table      */
    int overlay_table_size;		/* number of overlay table entries*/
    int on_board_cursor;		/* is there a on-chip cursor ram  */
    curs_ram_t cursor;			/* cursor pallette size           */
} pvp_ramdac_t;


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
#define PVP_MAX_BUFFER_SIZE		(5138 * 4)
#define PVP_MAX_PRIMITIVES		255
 
 
/*
 * PVP_INSTR_ instruction-field macros may be used instead of 
 * the pvInstruction structure, but the latter is usually preferable.
 */
#define PVP_INSTR_OPCODE 		0
#define PVP_INSTR_DST 			8
#define PVP_INSTR_SRC1 			12
#define PVP_INSTR_SRC0 			16
#define PVP_INSTR_CCOP 			20
#define PVP_INSTR_XYEN 			22
#define PVP_INSTR_XYSENSE 		24
#define PVP_INSTR_ZEN 			25
#define PVP_INSTR_CLEN 			26
#define PVP_INSTR_CCEN 			27

#define PVP_CAP_BUTT 			0
#define PVP_CAP_NOT_LAST		1

#define	PVP_XYMASK_DATA_LENGTH		8

#define	PVP_POINTS			0
#define	PVP_LINES			1
#define	PVP_WIDE_LINES			2
#define	PVP_QUADS			3
#define	PVP_READ_BLOCKS			4
#define	PVP_WRITE_BLOCKS		5

#define	PVP_NONE			0
#define	PVP_PER_PACKET			1
#define	PVP_PER_PRIMITIVE		2
#define	PVP_PER_VERTEX			3

#define	PVP_BAD_GEOM_FMT		0
#define	PVP_BAD_Z0_FMT			1
#define	PVP_BAD_Z1_FMT			2
#define	PVP_BAD_XYMASK_FMT		3

#define	PVP_BAD_XYMASK_PTR		4

#define	PVP_QUEUED			1
#define	PVP_SENT_TO_HW			2

/*
 * opcodes 
 */
#define PVP_AND				0
#define PVP_OR				1
#define PVP_XOR				2
#define PVP_NOT				3
#define PVP_COPY			4
#define PVP_ADD				5
#define PVP_SUB				6
#define PVP_CMPLT			7
#define PVP_CMPLE			8
#define PVP_CMPEQ			9
#define PVP_CMPGE			10
#define PVP_CMPGT			11
#define PVP_CMPOVF			12
#define PVP_MULHIGH			13
#define PVP_MULLOW			14
#define PVP_ADD24			15
#define PVP_SUB24			16
#define PVP_CMPLT24			17
#define PVP_CMPLE24			18
#define PVP_CMPEQ24			19
#define PVP_CMPGE24			20
#define PVP_CMPGT24             	21

/*
 * CC OPERATION 
 */
#define PVP_CC_REPLACE			0
#define PVP_CC_AND			1
#define PVP_CC_OR			2

/*
 * xymask enable flags 
 */
#define PVP_XYMASK_DISABLE		0
#define PVP_XYMASK_16X16 		1
#define PVP_XYMASK_256X1 		2
#define PVP_XYMASK_1X256 		3
	
/*
 * xymask sense 
 */
#define PVP_XYMASK_SET_ENABLED		0
#define PVP_XYMASK_SET_DISABLED		1

/*
 * Source and Destination operands
 */
#define PVP_OPERAND_PR0			0
#define PVP_OPERAND_PR1			1
#define PVP_OPERAND_PID0		4
#define PVP_OPERAND_PID1		5
#define PVP_OPERAND_PID2		6
#define PVP_OPERAND_PID3		7
#define PVP_OPERAND_PID4		8
#define PVP_OPERAND_PID5		9
#define PVP_OPERAND_0			10
#define PVP_OPERAND_1			11
#define PVP_OPERAND_RGB0		12
#define PVP_OPERAND_RGB1		13
#define PVP_OPERAND_Z0			14
#define PVP_OPERAND_Z1			15

/*
 * PixelVision values for the 0.0 and 1.0 contstants.
 */
#define PVP_0POINT0			0
#define PVP_1POINT0			0xff


/*
 *	Structure definitions
 */ 
typedef struct
{
    unsigned geomFmt 	: 3 ;		/* what primitive? */
    unsigned capStyle 	: 1 ;		/* Cap Butt or Cap not last */
    unsigned clipFmt	: 2 ;		/* None, per-packet, or per-primitive */
    unsigned xyMaskFmt 	: 2 ;		/* None, per-packet, or per-primitive */
    unsigned zMaskFmt 	: 2 ;		/* None, per-packet, or per-primitive */
    unsigned rgb0Fmt 	: 2 ;		/* none,per-packet,per-primitive,or per-vertex */
    unsigned rgb1Fmt 	: 2 ;		/* none,per-packet,per-primitive,or per-vertex */
    unsigned z0Fmt 	: 2 ;		/* none,per-packet,per-primitive,or per-vertex */
    unsigned z1Fmt 	: 2 ;		/* none,per-packet,per-primitive,or per-vertex */
    unsigned instCount 	: 4 ;		/* instructions in the packet */
    unsigned pidCount 	: 2 ;		/* number of pixelmap IDs in packet */
    unsigned primCount 	: 8 ;		/* number of primitives in packet */
} pvp_packet_header_t, *pvp_packet_header_ptr_t;
#define PVP_HDR_BLOCKS		((1<<22) | (1<<24))
#define PVP_HDR_READ_BLOCKS	(PVP_HDR_BLOCKS | PVP_READ_BLOCKS)
#define PVP_HDR_WRITE_BLOCKS	(PVP_HDR_BLOCKS | PVP_WRITE_BLOCKS)

/*
 * note that this is a quadword[sic] value, and needs << 1,
 * hence "- 31" instead of "- 32".
 */
#define PVP_DMA_SRAM_HI_ADDR (1 << (PVP_PIC_ADDR_USE_BASE -31))
#define PVP_DMA_HOST_HI_ADDR ((1 << (PVP_PIC_ADDR_USE_BASE -31)) |\
			      (1 << (PVP_PIC_ADDR_HOST_SPACE -31)))

/* _xy is assumed to be "int" */
#define PVP_GET_XY(_x,_y,_xy)						      \
{									      \
    _x = (short)(_xy & 0xffff) >> 3;					      \
    _y = (short)(_xy >> 16) >> 3;					      \
}
#define PVP_MAKE_XY(_x,_y) ((((_y)&0x1fff) << 19) | (((_x)&0x1fff) << 3))

typedef struct {
    unsigned int hdr;
    unsigned int pid;
    int 	 xymin;
    int 	 xymax;
    unsigned int lo_addr;
    unsigned int hi_addr;
    unsigned int offset;
    unsigned int format;
} pvp_image_packet_t;

typedef struct {
    short x;
    short y;
} pvp_point_t, *pvp_point_ptr_t;

typedef unsigned int
    pvp_z_mask_t,
    *pvp_z_mask_ptr_t,
    pvp_z_t,
    *pvp_z_ptr_t;

typedef	struct
{
    unsigned	blue	 : 8;
    unsigned	green	 : 8;
    unsigned	red   	 : 8;
    unsigned	reserved : 8;
} pvp_color_t, *pvp_color_ptr_t;

typedef struct
{
    pvp_point_t clipRectMin;
    pvp_point_t clipRectMax;
} pvp_clip_rect_t,
  *pvp_clip_rect_ptr_t;

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
} pvp_instruction_t,
  *pvp_instruction_ptr_t;

typedef struct
{
    unsigned int data[PVP_XYMASK_DATA_LENGTH];
} pvp_xy_mask_t,
  *pvp_xy_mask_ptr_t;

typedef struct
{
    pvp_point_t    v1;
    pvp_point_t    v2;
} pvp_line_t,
  *pvp_line_ptr_t;

typedef struct
{
    pvp_point_t    v1;
    pvp_point_t    v2;
    unsigned int width;
} pvp_wide_line_t,
  *pvp_wide_line_ptr_t;

typedef struct
{
    pvp_point_t    v1;
    pvp_point_t    v2;
    pvp_point_t    v3;
    pvp_point_t    v4;
} pvp_quad_t,
  *pvp_quad_ptr_t;


/*
 * pvp_queue_t
 */
typedef struct {
    vm_offset_t		offset;
    pvp_image_packet_t	*dma_pkt;
    unsigned int	size;
} pvp_queue_t;
   
#define	PVP_QUEUE_SIZE		32 

/*
 * pvp_info_t
 */
typedef struct {
    ws_screen_descriptor	screen;
    ws_depth_descriptor		depth[NDEPTHS];
    ws_visual_descriptor	visual[NVISUALS];
    ws_cursor_functions		cf;
    ws_color_map_functions 	cmf;
    ws_screen_functions		sf;
    int				(*attach)();
    int				(*bootmsg)();
    int				(*map)();
    void			(*interrupt)();
    int				(*setup)();
    int				(*vm_hook)();
    struct controller	*ctlr;
    u_int 		text_foreground;
    u_int 		text_background;
    /*
     * stuff above this line gets initialized from pvp_types[]
     */
    vm_offset_t		pvo_8;
    vm_offset_t		pvo_16;
    vm_offset_t		pvo_24;
    vm_offset_t		pvo_32;
    io_handle_t		io_pvo;		/* memory space */
    io_handle_t		io_cf;		/* config space */
    dma_map_info_t	p_map_info;

    caddr_t		p_cmd_area; 	/* server packet area */
    caddr_t		phys_cmd_area;
    caddr_t		busphys_cmd_area;
    caddr_t		p_clip_area;
    caddr_t		phys_clip_area;
    caddr_t		busphys_clip_area;
					/* driver/server communication */
    pvp_attach_info_t	*p_info_area;
    caddr_t		phys_info_area;
    caddr_t		p_packet_area;
    caddr_t		phys_packet_area;
    caddr_t		busphys_packet_area;
    caddr_t		p_pmap_area;
    caddr_t		phys_pmap_area;
    caddr_t		p_scratch_area;
    caddr_t		busphys_pmap_area;
    caddr_t		phys_scratch_area;
    caddr_t		busphys_scratch_area;

    unsigned int	vram_size;
    unsigned int	sram_size;
    unsigned int	pixelmap_size;
    unsigned int	pixelmap_count;
    unsigned int	update_size;
    unsigned int	vis_pmap_size;
    unsigned int	cmd_area_size;
    unsigned int	scratch_area_size;

    pvp_render_config_t	render_config;
    pvp_render_status_t	render_status;

#define	PVP_INFO_SLEEP_PV_DMA		0
#define	PVP_INFO_SLEEP_RENDER		1
#define	PVP_INFO_SLEEP_IMAGE		2
#define	PVP_INFO_SLEEP_PACKET		3
#define	PVP_INFO_SLEEP_NUM		4
    unsigned int		sleep_chan[PVP_INFO_SLEEP_NUM];

#define	PVP_INFO_STATE_VALID		0x00000001
#define	PVP_INFO_STATE_GCP_VALID	0x00000002
#define	PVP_INFO_STATE_SAVED_GTLB_VALID	0x00000004
    unsigned long		state;

#define PVP_X				0
#define PVP_RM				1
#define PVP_DBG				2
#define PVP_N_INFO			3
    unsigned long		n_info;
    pid_t			n_info_pid[PVP_N_INFO];
    struct proc			*n_info_procp[PVP_N_INFO];
    caddr_t			n_info_mapped[PVP_N_INFO];

    /*
     * Keep the PV config register around
     */
    pvp_render_imp_rev_t	render_imp_rev;

    /*
     * pid and sig_mask are used to direct delivery of signals to
     * the owning process.  They are controlled by device-private ioctl's.
     */
    struct proc		*p_proc[PVP_IOC_PID_NUM];
    pid_t		pid[PVP_IOC_PID_NUM];
    unsigned long	sig_mask[PVP_IOC_PID_NUM];

    unsigned int	paging_in_progress;
    unsigned int	image_in_progress;
    unsigned int	packet_in_progress;
    unsigned int	image_failure;
    unsigned int	image_va_first;
    unsigned int	image_va_last;
    unsigned int	doorbell;

    /*
     * Some times we need the card to go quiet before we poke it, done
     * during vsync interrupt handleing.
     */
    unsigned int	waiting_for_idle;

    /*
     * During Put/GetImage, it may be necessary to service a pixelmap
     * fault.  Tuck the required PV TLB entries into this area.
     */
    pvp_graphic_tlb_t	saved_graphic_tlb;

    unsigned int	monitor_mode;
    unsigned int   	dac_dac;
    unsigned int   	dac_sync;
    unsigned int	dac_config_2;
    pvp_pic_csr_t	pic_csr;
    pvp_pic_csr_t	pic_csr_image;
    pvp_pic_csr_t	pic_csr_page;

    /*
     * Window tag information
     */
    int			fb_min_dirty;
    int			fb_max_dirty;
    int			fb_dirty;
    pvp_561_fb_wid_cell_t fb_cell[PVP_RAMDAC_561_FB_WINDOW_TAG_MAX_COUNT];
    int			auxfb_min_dirty;
    int			auxfb_max_dirty;
    int			auxfb_dirty;
    pvp_561_aux_fb_wid_cell_t auxfb_cell[PVP_RAMDAC_561_AUXFB_WINDOW_TAG_MAX_COUNT];
    int			ol_min_dirty;
    int			ol_max_dirty;
    int			ol_dirty;
    pvp_561_ol_wid_cell_t ol_cell[PVP_RAMDAC_561_OL_WINDOW_TAG_MAX_COUNT];
    int			auxol_min_dirty;
    int			auxol_max_dirty;
    int			auxol_dirty;
    pvp_561_aux_ol_wid_cell_t auxol_cell[PVP_RAMDAC_561_AUXOL_WINDOW_TAG_MAX_COUNT];

    /*
     * State for maintaining stereo modes
     */
    unsigned int	stereo_mode;
#define	PVP_INFO_STEREO_NONE		0
#define	PVP_INFO_STEREO_24		1
#define	PVP_INFO_STEREO_1212		2
#if 0
    int			stereo_wtag_start;
    int			stereo_wtag_count;
#endif
    /*
     * Safe area for data used in pageoutin operations
     */
    pvp_register_t	poi_out_tlb_entries[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_register_t	poi_out_format[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_register_t	poi_out_offset[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_register_t	poi_out_pixelmapid[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_register_t	poi_in_tlb_entries[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_register_t	poi_in_format[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_register_t	poi_in_offset[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_register_t	poi_in_pixelmapid[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_subpixel_pair_t	poi_out_xy_min[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_subpixel_pair_t	poi_out_xy_max[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_subpixel_pair_t	poi_in_xy_min[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    pvp_subpixel_pair_t	poi_in_xy_max[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    int			poi_count;
    int			poi_clear_page_int;
    int			poi_tlb_index[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    vm_offset_t		poi_out_page[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    vm_offset_t		poi_in_page[PVP_IOC_PAGEOUTIN_COUNT_MAX];
    /*
     * Monitor information
     */
    unsigned int		monitor_rate;
    /*
     * Packet queue queue
     */
    pvp_queue_t		queue[PVP_QUEUE_SIZE];
    int			queue_get;
    int			queue_put;
    /*
     * Profiling data
     */
    pvp_profile_data_t	profile;
    /*
     * Info about process packet and image mapping
     */
    io_handle_t		packet_poll_base;
    io_handle_t		image_poll_base;
    unsigned long	pad;
    int			toggle_stereo_mode;
} pvp_info_t;

#define PVP_INFO(_pvp,_f,_v)						      \
{									      \
    (_pvp)->p_info_area[0]._f = (_v);					      \
    (_pvp)->p_info_area[1]._f = (_v);					      \
    (_pvp)->p_info_area[2]._f = (_v);					      \
}

/*
 * Ioctl header.
 */
typedef struct {
    short		count;
    short		clear_page_int;
    int			*p_tlb_index;
    pvp_register_t	*p_out_tlb_entries;
    vm_offset_t		*p_out_page;
    pvp_register_t	*p_out_format;
    pvp_subpixel_pair_t	*p_out_xy_min;
    pvp_subpixel_pair_t	*p_out_xy_max;
    pvp_register_t	*p_out_offset;
    pvp_register_t	*p_out_pixelmapid;
    pvp_register_t	*p_in_tlb_entries;
    vm_offset_t		*p_in_page;
    pvp_register_t	*p_in_format;
    pvp_subpixel_pair_t	*p_in_xy_min;
    pvp_subpixel_pair_t	*p_in_xy_max;
    pvp_register_t	*p_in_offset;
    pvp_register_t	*p_in_pixelmapid;
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_ioc_pageoutin_t;

#define	PVP_ERRNO_RETRY_IMAGE		0x666

typedef struct {
    int			mode;
#define PVP_IOC_STEREO_NONE		0
#define	PVP_IOC_STEREO_24		1
#define	PVP_IOC_STEREO_1212		2
    int			win_tag_start;
    int			win_tag_count;
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_ioc_stereo_t;

typedef struct {
    caddr_t		packet;	/* offset from base of packet buffer */
    int			packetSize;
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_ioc_ping_t;


/*
 * PVL_IOC_IMAGE_MAX_SIZE is the maximum image size that can be handled.
 */
#define	PVP_IOC_IMAGE_MAX_SIZE		(2*1024*1024 - 2*NBPG)

/*
 * clients tell the driver to verify a put/get-image packet
 */
typedef struct {
    vm_offset_t		addr;
    u_long		size;
    int			hard_lockdown;
    caddr_t		packet;		/* offset */
    int			packetSize;
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_ioc_image_t;

typedef struct {
    short         screen;
    short         cmd;
    union {
	unsigned long 		data;
	pvp_attach_info_t   	*attach_info;
	pvp_ioc_pageoutin_t	pageoutin;
	pvp_ioc_stereo_t	stereo;
	pvp_ioc_window_tag_t	window_tag;
	pvp_ioc_ping_t		ping;
	pvp_ioc_image_t		image;
	pvp_profile_data_t	profile;
	unsigned int		sig_mask;
#define	PVP_IOC_SIG_PMAP_FAULT		(1<<PVP_INFO_SIG_PMAP_FAULT)
#define	PVP_IOC_SIG_VA_PAGEIN		(1<<PVP_INFO_SIG_VA_PAGEIN)
#define	PVP_IOC_SIG_MODULE_ERROR	(1<<PVP_INFO_SIG_MODULE_ERROR)
#define	PVP_IOC_SIG_CLIPPING		(1<<PVP_INFO_SIG_CLIPPING)
#define	PVP_IOC_SIG_PACKET_DONE		(1<<PVP_INFO_SIG_PACKET_DONE)

	unsigned int		pid_mask;
#define	PVP_IOC_PID_PV			(1<<PVP_IOC_PID_PV_INDEX)
#define	PVP_IOC_PID_GCP			(1<<PVP_IOC_PID_GCP_INDEX)
#if 0
	pvp_ramdac_t		*p_ramdac;
	int			direct_dma_count;
	pvp_ioc_dma_info_t	direct_dma_info;
#endif
	pvp_ioc_monitor_t	monitor;
    } info;
    /*XXX DO NOT CHANGE THIS STRUCT ABOVE THIS LINE XXX*/
} pvp_ioc_t;

#define PVP_IOC_PRIVATE	_IOWR('w', (0|IOC_S), pvp_ioc_t)

/*XXX DO NOT CHANGE BASIC IOCTL ASSIGNMENTS XXX*/
#define PVP_IOC_MAP_OPTION		1
#define	PVP_IOC_MAP_OPTION_SPARSE	2
#define	PVP_IOC_GET_PID			3
#define	PVP_IOC_SET_PID			4
#define	PVP_IOC_GET_SIGNALS		5
#define	PVP_IOC_SET_SIGNALS		6
#define	PVP_IOC_PMAP_PAGEOUTIN		7
#define	PVP_IOC_GET_STEREO		8
#define	PVP_IOC_SET_STEREO		9
#define	PVP_IOC_UNUSED1			10 /* old dcc ioctl's */
#define	PVP_IOC_UNUSED2			11
#define	PVP_IOC_WRITE_WINDOW_TAG	12
#define	PVP_IOC_READ_PV_REG		13
#define	PVP_IOC_WRITE_PV_REG		14
#define	PVP_IOC_SET_MONITOR		15

#define	PVP_IOC_NEW_BASE		16

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
 * PEER_PVP_IOCTL_PING_PACKETS
 *
 * Delivers a rendering packet to the PV device when the device is
 * already busy and has it's buffer filled.  The value passed is a
 * pvp_peer_ping_t.
 */
#ifdef PVP_SUPPORTS_PEER
#define	PEER_PVP_IOCTL_PING_PACKETS		\
	_IOW( 'p', ( 1 | PEER_IOCTL_SPECIFIC ), peer_pvp_ping_t )
#endif
#define	PVP_IOC_PING_PACKETS		( PVP_IOC_NEW_BASE )

/*
 * PEER_PVP_IOCTL_ALLOC_STALL
 *
 * Stalls the calling thread until sufficient packets are available for
 * it to proceed.
 */
#ifdef PVP_SUPPORTS_PEER
#define	PEER_PVP_IOCTL_ALLOC_STALL		\
	_IO( 'p', ( 2 | PEER_IOCTL_SPECIFIC ), NULL )
#endif
#define	PVP_IOC_ALLOC_STALL		( PVP_IOC_NEW_BASE + 1 )

/*
 * PEER_PVP_IOCTL_DEBUG_PING_PACKETS
 *
 * A debug version of PEER_PVP_IOCTL_PING_PACKETS used in combination with
 * PEER_PVP_IOCTL_DEBUG_ALLOC_PACKETS to insure that packets are cycled
 * in the correct order and that the caller doesn't violate allocation
 * restrictions.
 */
#ifdef PVP_SUPPORTS_PEER
#define	PEER_PVP_IOCTL_DEBUG_PING_PACKETS		\
	_IOW( 'p', ( 3 | PEER_IOCTL_SPECIFIC ), peer_pvp_ping_t )
#endif

/*
 * PEER_PVP_IOCTL_DEBUG_ALLOC_PACKETS
 *
 * Companion to above to return the next free packet.  Will stall until
 * one becomes available and will then return it's index as per ping
 * convention.
 */
#ifdef PVP_SUPPORTS_PEER
#define	PEER_PVP_IOCTL_DEBUG_ALLOC_PACKETS		\
	_IOR( 'p', ( 4 | PEER_IOCTL_SPECIFIC ), int )
#endif

/*
 * PEER_PVP_IOCTL_PUT_IMAGE
 *
 * Peer interface to put an image.  The image descriptor includes a
 * range of addresses to be locked down and a short list of packets 
 * which will perform the put image operation.
 */
#ifdef PVP_SUPPORTS_PEER
#define	PEER_PVP_IOCTL_PUT_IMAGE		\
	_IOW( 'p', ( 5 | PEER_IOCTL_SPECIFIC ), peer_pvp_image_t )
#endif
#define	PVP_IOC_PUT_IMAGE		( PVP_IOC_NEW_BASE + 2 )

/*
 * PEER_PVP_IOCTL_GET_IMAGE
 *
 * Companion to previous.
 */
#ifdef PVP_SUPPORTS_PEER
#define	PEER_PVP_IOCTL_GET_IMAGE		\
	_IOW( 'p', ( 6 | PEER_IOCTL_SPECIFIC ), peer_pvp_image_t )
#endif
#define	PVP_IOC_GET_IMAGE		( PVP_IOC_NEW_BASE + 3 )

/*
 * PVP_IOC_GET_PROFILE
 *
 * Debug/performance ioctl to retrieve various interesting info
 */
#define	PVP_IOC_GET_PROFILE		( PVP_IOC_NEW_BASE + 4 ) 

/*
 * PVP_IOC_CLEAR_PROFILE
 *
 * Sets the profiling values back to zero
 */
#define	PVP_IOC_CLEAR_PROFILE		( PVP_IOC_NEW_BASE + 5 )

#define PVP_IOC_INVALID	    	    	( PVP_IOC_NEW_BASE + 6 )

/*
 * External Function Declarations
 */
#ifdef KERNEL

extern int
    pvpprobe(),
    pvpattach(),
    pvp_init_screen(),
    pvp_which_option(),
    pvp_attach(),
    pvp_dd_attach(),
    pvp_bootmsg(),
    pvp_ioctl(),
    pvp_map_screen(),
    pvp_clear_screen(),
    pvp_scroll_screen(),
    pvp_blitc(),
    pvp_setup(),
    pvp_invalidate_page(),
    pvp_561_video_on(),
    pvp_561_video_off(),
    pvp_561_cursor_on_off(),
    pvp_561_load_cursor(),
    pvp_561_recolor_cursor(),
    pvp_561_set_cursor_position(),
    pvp_561_init_color_map(),
    pvp_561_load_color_map_entry();

extern void
  pvpintr(),
  pvp_close(),
  pvp_561_enable_interrupt(),
  pvp_interrupt();

extern caddr_t
  pvp_init_closure(),
  pvp_561_init_closure();

/*
 * External Data Declarations
 */

extern struct controller
  *pvpinfo[];

extern int
    npvp_types,
    npvp_561_types,
    npvp_561_softc,
    npvp_softc,
    _pvp_level,
    _pvp_debug,
    npvp_monitor_data,
    pvp_doorbell[];

extern pvp_info_t
  pvp_softc[];

extern pvp_type_t
  pvp_types[];

extern pvp_561_info_t
  pvp_561_softc[];

extern pvp_561_type_t
  pvp_561_types[];

extern pvp_dma_handle	dma_page;

extern pvp_dma_handle	dma_image;

extern pvp_monitor_data_t pvp_monitor_data[];

extern vm_offset_t pvp_misc;
extern vm_offset_t pvp_pmap;
extern vm_offset_t pvp_image;
extern vm_offset_t pvp_ring_buffers;
extern unsigned int pvp_image_size;
extern unsigned int pvp_cmd_size;


#endif /* KERNEL */

#endif /* _PVP_H_ */
