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
 * @(#)$RCSfile: tga.h,v $ $Revision: 1.1.20.2 $ (DEC) $Date: 1997/09/29 20:44:32 $
 */

/************************************************************************
 *									*
 *			Copyright (c) 1993 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

/*
 * RAMDAC is a trademark of Brooktree Corporation
 */

#ifndef	TGA_DEFINED
#define	TGA_DEFINED

/*
 * Header files
 */
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devdriver.h>

/*
 * Special offsets within the PCI configuration header
 */
#define	TGA_CONFIG_PVRR_OFFSET		0x00000040
#define	TGA_CONFIG_PAER_OFFSET		0x00000044

/*
 * PAER values
 */
#define	TGA_CONFIG_PAER_32MB		0x00000000
#define	TGA_CONFIG_PAER_64MB		0x00010000
#define	TGA_CONFIG_PAER_128MB		0x00030000

/*
 * Offsets within Memory Space
 */
#define TGA2_ICS_OFFSET                 0x060000
#define TGA2_RAMDAC_OFFSET              0x080000
#define REVISION_FIELD                  0x0000ff
#define	TGA_ROM_OFFSET			0x000000
#define	TGA_ASIC_OFFSET			0x100000
#define	TGA_RAMDAC_SETUP_OFFSET		0x1000c0
#define	TGA_RAMDAC_DATA_OFFSET		0x1001f0
#define	TGA_XY_REG_OFFSET		0x100074
#define	TGA_VALID_REG_OFFSET		0x100070

#define	TGA_0_0_FB_OFFSET		0x00200000
#define	TGA_0_0_FB_SIZE			0x00200000
#define	TGA_0_1_FB_OFFSET		0x00400000
#define	TGA_0_1_FB_SIZE			0x00400000
#define	TGA_0_3_FB_OFFSET		0x00800000
#define	TGA_0_3_FB_SIZE			0x00800000
#define	TGA_1_3_FB_OFFSET		0x00800000
#define	TGA_1_3_FB_SIZE			0x00800000
#define	TGA_1_7_FB_OFFSET		0x01000000
#define	TGA_1_7_FB_SIZE			0x01000000
#define	TGA_INVALID_FB_OFFSET		0
#define	TGA_INVALID_FB_SIZE		0

/*
 * TGA card types
 */
#define	TGA_TYPE_T801			0
#define	TGA_TYPE_T802			1
#define	TGA_TYPE_T822			2
#define	TGA_TYPE_T844			3
#define	TGA_TYPE_T3204			4
#define	TGA_TYPE_T3208			5
#define	TGA_TYPE_T3288			6
#define	TGA_TYPE_INVALID		7
#define	TGA_TYPE_NUM			8
#define TGA2                            0x20

#ifndef NDEPTHS
#define NDEPTHS 1                       /* all current hardware just has one */
#define NVISUALS 1
#endif /* NDEPTHS */

typedef unsigned char tga_pix8_t;
typedef unsigned int tga_pix32_t;
typedef unsigned int tga_reg_t;

/*
 * Window tags definitions
 */
#define	TGA_TRUECOLOR_WID_INDEX		0xc
#define	TGA_TRUECOLOR_WID_MASK		0xc0000000

/*
 * Device-private ioctls
 */
#define	TGA_IOCTL_PRIVATE		_IOWR('w', (0|IOC_S), tga_ioc_t)
#define	TGA_IOC_LOAD_WINDOW_TAGS	0
#define	TGA_IOC_ENABLE_DMA_OPS		1
#define	TGA_IOC_SET_STEREO_MODE		2
#define	TGA_IOC_GET_STEREO_MODE		3
#define	TGA_IOC_GET_DIRECT_DMA_COUNT	4
#define	TGA_IOC_GET_DIRECT_DMA_INFO	5
#define TGA_QUERY_RAMDAC                6
#define TGA_SET_MONITOR_TIMING          7
#define TGA_SET_MONITOR_REGS            8
#define TGA_WRITE_RAMDAC                9
#define TGA_READ_RAMDAC                 0xa
#define TGA_WRITE_ASIC                  0xb
#define TGA_READ_ASIC                   0xc
#define TGA_IOC_DMA_OK                   0xd

typedef struct {
  char			windex;
  unsigned char		low;
  unsigned char		mid;
  unsigned char		high;
  int			resv[9]
} tga_window_tag_cell_t;

typedef struct {
  int         windex;
  int         clut_start;     /* color lookup table starting address  */
  int         cpix_format;    /* pixel format(depth)                  */
  int         cbuffer;        /* frame buffer selection (A, B or C)   */
  int         cmode;          /* index, grey scale, direct, true color*/
  int         ol_start;       /* color lookup table starting address  */
  int         opix_format;    /* pixel format(depth)                  */
  int         obuffer;        /* overlay buffer selection (A, B or C) */
  int         omode;          /* index, grey scale, direct, true color*/
  int         ov_mask;        /* mask overlay data?                   */
} tga_virtual_window_tag_cell_t;

typedef struct {
  char                  windex;
  unsigned char         low;
  unsigned char         mid;
  unsigned char         high;
} tga_463_tag_cell_t;

typedef struct {
  short                 ncells;
  short                 start;
  tga_window_tag_cell_t *p_cells;
} tga_ioc_window_tag_t;

typedef struct {
  vm_offset_t		phys_base;
  vm_offset_t		bus_base;
  vm_size_t		map_size;
} tga_dma_map_t;

typedef struct {
  int			alloc_map_num;		/* input */
  int			actual_map_num;		/* output */
  tga_dma_map_t		*maps;			/* input & output */
  unsigned int          dma_ok;                 /* DMA Safe to use */
} tga_ioc_dma_info_t;

typedef   struct {
 int width;
 int heigth;
 int depth;
}curs_ram_t;

typedef   struct {
    int wat_table;         /* is there a wat table           */
    int wat_table_len;     /* number of table entries        */
    int buffering;         /* buffering capabilities (1/2/3) */
    int color_table_size;  /* number of color table entries  */
    int min_color_depth;   /* minimum color table size       */
    int gamma_table;       /* is there a gamma pallete       */
    int gamma_table_size;  /* number of gamma table entries  */
    int gamma_table_depth; /* depth of an entry in bits      */
    int overlay_table;     /* is there an overlay table      */
    int overlay_table_size;/* number of overlay table entries*/
    int on_board_cursor;   /* is there a on-chip cursor ram  */
    curs_ram_t cursor;     /* cursor pallette size           */
   }tga_ramdac_t;

typedef struct {
  unsigned              deep : 1;
  unsigned              mbz0 : 1;
  unsigned              mask : 3;
  unsigned              block : 4;
  unsigned              col_size : 1;
  unsigned              sam_size : 1;
  unsigned              parity : 1;
  unsigned              write_en : 1;
  unsigned              ready : 1;
  unsigned              slow_dac : 1;
  unsigned              dma_size : 1;
  unsigned              sync_type : 1;
  unsigned              mbz1 : 15;
} tga_deep_reg_t;

typedef struct {
  unsigned              rev : 8;
  unsigned              mbz0 : 8;
  unsigned              monitor : 4;
  unsigned              vga : 1;
  unsigned              mem : 2;
  unsigned              alias : 1;
  unsigned              dac : 2;
  unsigned              prech : 1;
  unsigned              refresh : 1;
  unsigned              mbz1 : 4;
} tga_rev_reg_t;

typedef struct {
  unsigned              video : 1;
  unsigned              blank : 1;
  unsigned              cursor : 1;
  unsigned              interlace_d : 1;
  unsigned              power : 2;
  unsigned              mbz1 : 26;
} tga_videov_reg_t;

#define	TGA_DEEP_DEEP_8PLANE		0
#define	TGA_DEEP_DEEP_32PLANE		1

#define	TGA_DEEP_MASK_4MB		0x00
#define	TGA_DEEP_MASK_8MB		0x01
#define	TGA_DEEP_MASK_16MB		0x03
#define	TGA_DEEP_MASK_32MB		0x07

#define	TGA_DEEP_PARITY_ODD		0
#define	TGA_DEEP_PARITY_EVEN		1

#define	TGA_DEEP_READY_ON_8		0
#define	TGA_DEEP_READY_ON_2		1

#define	TGA_DEEP_DMA_64			0
#define	TGA_DEEP_DMA_128		1

typedef struct {
  unsigned		s_wr_mask : 8;
  unsigned		s_rd_mask : 8;
  unsigned		s_test : 3;
  unsigned		s_fail : 3;
  unsigned		d_fail : 3;
  unsigned		d_pass : 3;
  unsigned		z_test : 3;
  unsigned		z : 1;
} tga_stencil_mode_reg_t;

#define	TGA_SM_TEST_GEQ			0x00
#define	TGA_SM_TEST_TRUE		0x01
#define	TGA_SM_TEST_FALSE		0x02
#define	TGA_SM_TEST_LS			0x03
#define	TGA_SM_TEST_EQ			0x04
#define	TGA_SM_TEST_LEQ			0x05
#define	TGA_SM_TEST_GT			0x06
#define	TGA_SM_TEST_NEQ			0x07

#define	TGA_SM_RESULT_KEEP		0x00
#define	TGA_SM_RESULT_ZERO		0x01
#define	TGA_SM_RESULT_REPLACE		0x02
#define TGA_SM_RESULT_INCR		0x03
#define	TGA_SM_RESULT_DECR		0x04
#define	TGA_SM_RESULT_INV		0x05

#define	TGA_SM_Z_REPLACE		0
#define	TGA_SM_Z_KEEP			1

typedef struct {
  unsigned		mode : 8;
  unsigned		visual : 3;
  unsigned		rotate : 2;
  unsigned		line : 1;
  unsigned		z16 : 1;
  unsigned		cap_ends : 1;
  unsigned		mbz : 16;
} tga_mode_reg_t;

#define	TGA_MODE_MODE_SIMPLE			0x00
#define	TGA_MODE_MODE_Z_SIMPLE			0x10
#define	TGA_MODE_MODE_OPA_STIP			0x01
#define	TGA_MODE_MODE_OPA_FILL			0x21
#define	TGA_MODE_MODE_TRA_STIP			0x05
#define	TGA_MODE_MODE_TRA_FILL			0x25
#define	TGA_MODE_MODE_TRA_BLK_STIP		0x0d
#define	TGA_MODE_MODE_TRA_BLK_FILL		0x2d
#define	TGA_MODE_MODE_OPA_LINE			0x02
#define	TGA_MODE_MODE_TRA_LINE			0x06
#define	TGA_MODE_MODE_CINT_TRA_LINE		0x0e
#define	TGA_MODE_MODE_CINT_TRA_DITH_LINE	0x2e
#define	TGA_MODE_MODE_Z_OPA_LINE		0x12
#define	TGA_MODE_MODE_Z_TRA_LINE		0x16
#define	TGA_MODE_MODE_Z_CINT_OPA_LINE		0x1a
#define	TGA_MODE_MODE_Z_SINT_OPA		0x5a
#define	TGA_MODE_MODE_Z_CINT_OPA_DITH_LINE	0x3a
#define	TGA_MODE_MODE_Z_CINT_TRA_LINE		0x1e
#define	TGA_MODE_MODE_Z_SINT_TRA		0x5e
#define	TGA_MODE_MODE_Z_CINT_TRA_DITH_LINE	0x3e
#define	TGA_MODE_MODE_COPY			0x07
#define TGA_MODE_MODE_COPY24                    0x307
#define	TGA_MODE_MODE_DMA_READ			0x17
#define	TGA_MODE_MODE_DMA_READ_DITH		0x37
#define	TGA_MODE_MODE_DMA_WRITE			0x1f

#define	TGA_MODE_VISUAL_8_PACKED		0x00
#define	TGA_MODE_VISUAL_8_UNPACKED		0x01
#define	TGA_MODE_VISUAL_12_LOW			0x02
#define	TGA_MODE_VISUAL_12_HIGH			0x06
#define	TGA_MODE_VISUAL_24			0x03

#define	TGA_MODE_PM_IS_PERS			0x00800000
#define	TGA_MODE_ADDR_IS_NEW			0x00400000
#define	TGA_MODE_BRES3_IS_NEW			0x00200000
#define	TGA_MODE_COPY_WILL_DRAIN		0x00100000

typedef struct {
  unsigned		opcode : 4;
  unsigned		mbz : 4;
  unsigned 		visual : 2;
  unsigned		rotate : 2;
} tga_raster_op_t;

#define	TGA_ROP_OP_CLEAR			0
#define	TGA_ROP_OP_AND				1
#define	TGA_ROP_OP_AND_REVERSE			2
#define	TGA_ROP_OP_COPY				3
#define TGA_ROP_OP_COPY24                       0x303
#define	TGA_ROP_OP_AND_INVERTED			4
#define	TGA_ROP_OP_NOOP				5
#define	TGA_ROP_OP_XOR				6
#define	TGA_ROP_OP_OR				7
#define	TGA_ROP_OP_NOR				8
#define	TGA_ROP_OP_EQUIV			9
#define	TGA_ROP_OP_INVERT			10
#define	TGA_ROP_OP_OR_REVERSE			11
#define	TGA_ROP_OP_COPY_INVERTED		12
#define	TGA_ROP_OP_OR_INVERTED			13
#define	TGA_ROP_OP_NAND				14
#define	TGA_ROP_OP_SET				15

#define	TGA_ROP_VISUAL_8_PACKED			0x00
#define	TGA_ROP_VISUAL_8_UNPACKED		0x01
#define	TGA_ROP_VISUAL_12			0x02
#define	TGA_ROP_VISUAL_24			0x03

#define	TGA_INTR_VSYNC				0x00000001
#define	TGA_INTR_SHIFT_ADDR			0x00000002
#define TGA_INTR_DMA                            0x00000004
#define TGA_INTR_PARITY                         0x00000008
#define	TGA_INTR_TIMER				0x00000010
#define	TGA_INTR_ALL				0x0000000f
#define TGA2_INTR_ALL                           0x00000013
#define	TGA_INTR_ENABLE_SHIFT			16

#define	TGA_RAMDAC_INTERF_WRITE_SHIFT		0
#define	TGA_RAMDAC_INTERF_READ0_SHIFT		16
#define	TGA_RAMDAC_INTERF_READ1_SHIFT		24

#define	TGA_RAMDAC_485_READ			0x01
#define	TGA_RAMDAC_485_WRITE			0x00
#define	TGA_RAMDAC_485_ADDR_PAL_WRITE		0x00
#define	TGA_RAMDAC_485_DATA_PAL			0x02
#define	TGA_RAMDAC_485_PIXEL_MASK		0x04
#define	TGA_RAMDAC_485_ADDR_PAL_READ		0x06
#define	TGA_RAMDAC_485_ADDR_CUR_WRITE		0x08
#define	TGA_RAMDAC_485_DATA_CUR			0x0a
#define	TGA_RAMDAC_485_CMD_0			0x0c
#define	TGA_RAMDAC_485_ADDR_CUR_READ		0x0e
#define	TGA_RAMDAC_485_CMD_1			0x10
#define	TGA_RAMDAC_485_CMD_2			0x12
#define TGA_RAMDAC_485_CMD_3                    0x14
#define	TGA_RAMDAC_485_STATUS			0x14
#define	TGA_RAMDAC_485_CUR_RAM			0x16
#define	TGA_RAMDAC_485_CUR_LOW_X		0x18
#define	TGA_RAMDAC_485_CUR_HIGH_X		0x1a
#define	TGA_RAMDAC_485_CUR_LOW_Y		0x1c
#define	TGA_RAMDAC_485_CUR_HIGH_Y		0x1e

#define	TGA_RAMDAC_485_ADDR_EPSR_SHIFT		0
#define	TGA_RAMDAC_485_ADDR_EPDR_SHIFT		8

#define	TGA_RAMDAC_463_HEAD_MASK		0x01
#define	TGA_RAMDAC_463_READ			0x02
#define	TGA_RAMDAC_463_WRITE			0x00
#define	TGA_RAMDAC_463_ADDR_LOW			0x00
#define	TGA_RAMDAC_463_ADDR_HIGH		0x04
#define	TGA_RAMDAC_463_CMD_CURS			0x08
#define	TGA_RAMDAC_463_CMD_CMAP			0x0c

#define	TGA_RAMDAC_463_ADDR_EPSR_SHIFT		0
#define	TGA_RAMDAC_463_ADDR_EPDR_SHIFT		8

#define TGA_RAMDAC_463_CURSOR_COLOR0		0x0100
#define TGA_RAMDAC_463_CURSOR_COLOR1		0x0101
#define TGA_RAMDAC_463_COMMAND_REG_0		0x0201
#define TGA_RAMDAC_463_COMMAND_REG_1		0x0202
#define TGA_RAMDAC_463_COMMAND_REG_2		0x0203
#define	TGA_RAMDAC_463_READ_MASK		0x0205
#define	TGA_RAMDAC_463_BLINK_MASK		0x0209
#define	TGA_RAMDAC_463_WINDOW_TYPE_TABLE	0x0300

#define TGA_RAMDAC_561_HEAD_MASK                0x01
#define TGA_RAMDAC_561_READ                     0x02
#define TGA_RAMDAC_561_WRITE                    0x00
#define TGA2_RAMDAC_ONE_BYTE                    0x0E000
#define TGA2_RAMDAC_TWO_BYTES                   0x0c000
#define TGA2_RAMDAC_THREE_BYTES                 0x08000
#define TGA2_RAMDAC_FOUR_BYTES                  0x00000
#define TGA_RAMDAC_561_ADDR_LOW                 0x0000
#define TGA_RAMDAC_561_ADDR_HIGH                0x0100
#define TGA_RAMDAC_561_CMD_REGS                 0x0200
#define TGA_RAMDAC_561_CMD_CURS_PIX             0x0200
#define TGA_RAMDAC_561_CMD_CURS_LUT             0x0300
#define TGA_RAMDAC_561_CMD_FB_WAT               0x0300
#define TGA_RAMDAC_561_CMD_AUXFB_WAT            0x0200
#define TGA_RAMDAC_561_CMD_OL_WAT               0x0300
#define TGA_RAMDAC_561_CMD_AUXOL_WAT            0x0200
#define TGA_RAMDAC_561_CMD_GAMMA                0x0300
#define TGA_RAMDAC_561_CMD_CMAP                 0x0300

#define TGA_RAMDAC_561_ADDR_EPSR_SHIFT          0
#define TGA_RAMDAC_561_ADDR_EPDR_SHIFT          8

#define TGA_RAMDAC_561_CONFIG_REG_1             0x0001
#define TGA_RAMDAC_561_CONFIG_REG_2             0x0002
#define TGA_RAMDAC_561_CONFIG_REG_1             0x0001
#define TGA_RAMDAC_561_CONFIG_REG_2             0x0002
#define TGA_RAMDAC_561_CONFIG_REG_3             0x0003
#define TGA_RAMDAC_561_CONFIG_REG_4             0x0004
#define TGA_RAMDAC_561_WAT_SEG_REG              0x0006
#define TGA_RAMDAC_561_OL_SEG_REG               0x0007
#define TGA_RAMDAC_561_CHROMA_KEY_REG0          0x0010
#define TGA_RAMDAC_561_CHROMA_KEY_REG1          0x0011
#define TGA_RAMDAC_561_CHROMA_MASK_REG0         0x0012
#define TGA_RAMDAC_561_CHROMA_MASK_REG1         0x0013
#define TGA_RAMDAC_561_SYNC_CONTROL             0x0020
#define TGA_RAMDAC_561_PLL_VCO_DIV_REG          0x0021
#define TGA_RAMDAC_561_PLL_REF_REG              0x0022
#define TGA_RAMDAC_561_CURSOR_CTRL_REG          0x0030
#define TGA_RAMDAC_561_CURSOR_HS_REG            0x0034
#define TGA_RAMDAC_561_VRAM_MASK_REG            0x0050
#define TGA_RAMDAC_561_DAC_CTRL                 0x005f
#define TGA_RAMDAC_561_DIV_DOT_CLK_REG          0x0082

#define TGA_RAMDAC_561_READ_MASK                0x0205
#define TGA_RAMDAC_561_BLINK_MASK               0x0209
#define TGA_RAMDAC_561_FB_WINDOW_TYPE_TABLE     0x1000
#define TGA_RAMDAC_561_AUXFB_WINDOW_TYPE_TABLE  0x0E00
#define TGA_RAMDAC_561_OL_WINDOW_TYPE_TABLE     0x1400
#define TGA_RAMDAC_561_AUXOL_WINDOW_TYPE_TABLE  0x0F00
#define TGA_RAMDAC_561_RED_GAMMA_TABLE          0x3000
#define TGA_RAMDAC_561_GREEN_GAMMA_TABLE        0x3400
#define TGA_RAMDAC_561_BLUE_GAMMA_TABLE         0x3800
#define TGA_RAMDAC_561_COLOR_LOOKUP_TABLE       0x4000
#define TGA_RAMDAC_561_CURSOR_LOOKUP_TABLE      0x0a11
#define TGA_RAMDAC_561_CURSOR_BLINK_TABLE       0x0a15
#define TGA_RAMDAC_561_CROSS_LOOKUP_TABLE       0x0a19
#define TGA_RAMDAC_561_CROSS_BLINK_TABLE        0x0a1d
#define TGA_RAMDAC_561_CURSOR_PIXMAP            0x2000
#define TGA_RAMDAC_561_CURSOR_X_LOW             0x0036
#define TGA_RAMDAC_561_CURSOR_X_HIGH            0x0037
#define TGA_RAMDAC_561_CURSOR_Y_LOW             0x0038
#define TGA_RAMDAC_561_CURSOR_Y_HIGH            0x0039

typedef union {
  struct {
    unsigned int	pixels:9;
    unsigned int	front_porch:5;
    unsigned int	sync:7;
    unsigned int	back_porch:7;
    unsigned int	ignore:3;
    unsigned int	odd:1;
  } horizontal_setup;
  unsigned int h_setup;
} tga_horizontal_setup_t;

typedef union {
  struct {
    unsigned int	scan_lines:11;
    unsigned int 	front_porch:5;
    unsigned int	sync:6;
    unsigned int 	back_porch:6;
  } vertical_setup;
  unsigned int v_setup;
} tga_vertical_setup_t;

typedef volatile struct {
  tga_reg_t		buffer[8];

  tga_reg_t		foreground;
  tga_reg_t		background;
  tga_reg_t		planemask;
  tga_reg_t		pixelmask;
  tga_reg_t		mode;
  tga_reg_t		rop;
  tga_reg_t		shift;
  tga_reg_t		address;

  tga_reg_t		bres1;
  tga_reg_t		bres2;
  tga_reg_t		bres3;
  tga_reg_t		brescont;
  tga_reg_t		deep;
  tga_reg_t		start;
  tga_reg_t 		stencil_mode;
  tga_reg_t 		pers_pixelmask;

  tga_reg_t 		cursor_base_address;
  tga_reg_t 		horizontal_setup;
  tga_reg_t		vertical_setup;
#define	TGA_VERT_STEREO_EN		0x80000000
  tga_reg_t		base_address;
  tga_reg_t		video_valid;
#define	TGA_VIDEO_VALID_SCANNING	0x00000001
#define	TGA_VIDEO_VALID_BLANK		0x00000002
#define	TGA_VIDEO_VALID_CURSOR_ENABLE	0x00000004
#define TGA_VIDEO_VALID_DPMS_ON         0x00000000
#define TGA_VIDEO_VALID_DPMS_STANDBY    0x00000010
#define TGA_VIDEO_VALID_DPMS_SUSPEND    0x00000020
#define TGA_VIDEO_VALID_DPMS_OFF        0x00000030
  tga_reg_t		cursor_xy;
  tga_reg_t		video_shift_addr;
  tga_reg_t		intr_status;

  tga_reg_t		pixel_data;
  tga_reg_t		red_incr;
  tga_reg_t		green_incr;
  tga_reg_t		blue_incr;
  tga_reg_t		z_incr_low;
  tga_reg_t		z_incr_high;
  tga_reg_t		dma_address;
  tga_reg_t		bres_width;

  tga_reg_t		z_value_low;
  tga_reg_t		z_value_high;
  tga_reg_t		z_base_address;
  tga_reg_t		address2;
  tga_reg_t		red_value;
  tga_reg_t		green_value;
  tga_reg_t		blue_value;
  tga_reg_t		_jnk12;

  tga_reg_t		ramdac_setup;
  struct {
    tga_reg_t		junk;
  } _junk[8*2-1];

  struct {
    tga_reg_t		data;
  } slope_no_go[8];

  struct {
    tga_reg_t		data;
  } slope[8];

  tga_reg_t		bm_color_0;
  tga_reg_t		bm_color_1;
  tga_reg_t		bm_color_2;
  tga_reg_t		bm_color_3;
  tga_reg_t		bm_color_4;
  tga_reg_t		bm_color_5;
  tga_reg_t		bm_color_6;
  tga_reg_t		bm_color_7;

  tga_reg_t		c64_src;
  tga_reg_t		c64_dst;
  tga_reg_t		c64_src2;
  tga_reg_t		c64_dst2;
  tga_reg_t		_jnk45;
  tga_reg_t		_jnk46;
  tga_reg_t		_jnk47;
  tga_reg_t		_jnk48;

  struct {
    tga_reg_t		junk;
  } _junk2[8*3];
  
  tga_reg_t		eprom_write;
  tga_reg_t		_res0;
  tga_reg_t		clock;
  tga_reg_t		_res1;
  tga_reg_t		ramdac;
  tga_reg_t		intr_status2;
  tga_reg_t		command_status;
  tga_reg_t		command_status2;

} tga_rec_t, *tga_ptr_t;

typedef union {
  struct {
    unsigned char       low_byte;
    unsigned char       high_byte;
  }wat_in_bytes;
  struct {
    unsigned            tr:1;
    unsigned            mode:2;
    unsigned            bs:1;
    unsigned            pix:2;
    unsigned            addr:4;
    unsigned            resv:6;
  }wat_in_bits;
}fb_wid_cell_t;

typedef struct {
    int                 windex:16;
    fb_wid_cell_t       entry;
} tga_ibm561_fb_wid_cell_t;

typedef union {
  unsigned char         aux_fbwat;

  struct {
    unsigned            pt:1;
    unsigned            xh:1;
    unsigned            gma:1;
    unsigned            resv:5;
  }wat_in_bits;
} aux_fb_wid_cell_t;

typedef struct {
    int                 windex:8;
    aux_fb_wid_cell_t   entry;
} tga_ibm561_aux_fb_wid_cell_t;

typedef union {
  struct {
    unsigned char       low_byte;
    unsigned char       high_byte;
  }wat_in_bytes;
  struct {
    unsigned            tr:1;
    unsigned            mode:2;
    unsigned            bs:1;
    unsigned            pix:2;
    unsigned            addr:4;
    unsigned            resv:6;
  }wat_in_bits;
} ol_wid_cell_t;

typedef struct {
    int                 windex:16;
    ol_wid_cell_t       entry;
} tga_ibm561_ol_wid_cell_t;

typedef union {
  unsigned char         aux_olwat;
  struct {
    unsigned            ot:1;
    unsigned            xh:1;
    unsigned            gb:1;
    unsigned            ol:1;
    unsigned            ul:1;
    unsigned            ck:1;
    unsigned            resv:2;
  }wat_in_bits;
} aux_ol_wid_cell_t;

typedef struct {
    int                 windex:8;
    aux_ol_wid_cell_t   entry;
} tga_ibm561_aux_ol_wid_cell_t;


/*
 * There are actually 256 window tag entries in the FB and OL WAT tables.
 * We will use only 16 for compatability with the BT463 and more importantly
 * to implement the virtual ramdac interface.  This requires us to only
 * report the smallest WAT table size, in this case its the auxillary wat
 * tables which are 16 entries.
 */

#define TGA_RAMDAC_561_FB_WINDOW_TAG_COUNT      256
#define TGA_RAMDAC_561_FB_WINDOW_TAG_MAX_COUNT  16
#define TGA_RAMDAC_561_AUXFB_WINDOW_TAG_COUNT   16
#define TGA_RAMDAC_561_OL_WINDOW_TAG_COUNT      256
#define TGA_RAMDAC_561_OL_WINDOW_TAG_MAX_COUNT  16
#define TGA_RAMDAC_561_AUXOL_WINDOW_TAG_COUNT   16
#define TGA_RAMDAC_561_CMAP_ENTRY_COUNT         1024
#define TGA_RAMDAC_561_GAM_ENTRY_COUNT          256

typedef struct {
  ws_screen_descriptor	screen;        /* MUST be first!!! */
  ws_depth_descriptor	depth[NDEPTHS];
  ws_visual_descriptor	visual[NVISUALS];
  ws_cursor_functions	cf;
  ws_color_map_functions cmf;
  ws_screen_functions	sf;
  int         		(*attach)();
  int         		(*bootmsg)();
  int         		(*map)();
  int        		(*interrupt)();
  int         		(*setup)();
  vm_offset_t		base;
  tga_ptr_t		asic;
  vm_offset_t		fb;
  size_t		fb_size;
  unsigned int		bt485_present;
  unsigned int		bits_per_pixel;
  unsigned int		core_size;
  unsigned int		paer_value;
  tga_reg_t		deep;
  tga_reg_t		head_mask;
  tga_reg_t		refresh_count;
  tga_reg_t		horizontal_setup;
  tga_reg_t		vertical_setup;
  tga_reg_t		base_address;
  caddr_t		info_area;
  vm_offset_t		virtual_dma_buffer;
  vm_offset_t		physical_dma_buffer;
  int			wt_min_dirty;
  int			wt_max_dirty;
  int			wt_dirty;
  tga_window_tag_cell_t	wt_cell[16];	/* magic number */

  int                   tag_type;

  int                   fb_min_dirty;
  int                   fb_max_dirty;
  int                   fb_dirty;
  tga_ibm561_fb_wid_cell_t fb_cell[TGA_RAMDAC_561_FB_WINDOW_TAG_COUNT];

  int                   auxfb_min_dirty;
  int                   auxfb_max_dirty;
  int                   auxfb_dirty;
  tga_ibm561_aux_fb_wid_cell_t auxfb_cell[TGA_RAMDAC_561_AUXFB_WINDOW_TAG_COUNT];

  int                   ol_min_dirty;
  int                   ol_max_dirty;
  int                   ol_dirty;
  tga_ibm561_ol_wid_cell_t ol_cell[TGA_RAMDAC_561_OL_WINDOW_TAG_COUNT];

  int                   auxol_min_dirty;
  int                   auxol_max_dirty;
  int                   auxol_dirty;
  tga_ibm561_aux_ol_wid_cell_t auxol_cell[TGA_RAMDAC_561_AUXOL_WINDOW_TAG_COUNT];

  unsigned int		stereo_mode;
  io_handle_t		io_handle;
  dma_map_info_t	p_map_info;
  unsigned int          rev_id;
  unsigned int          bt463_present;
  unsigned int          ibm561_present;
  unsigned int          tga2_present;
  unsigned long         ramdac;
  vm_offset_t           ics;
  tga_rev_reg_t         revision;
  int                   cursor_on_off;
  unsigned int          dma_ok;
} tga_info_t;

#define TGA_FB_TAG      0x00
#define TGA_AUXFB_TAG   0x01
#define TGA_OL_TAG      0x02
#define TGA_AUXOL_TAG   0x03
#define	TGA_USER_MAPPING_COUNT		4

typedef struct {
  vm_offset_t		fb_alias_increment;
  vm_offset_t		option_base;
  unsigned int		planemask;
  vm_offset_t		virtual_dma_buffer;
  vm_offset_t		physical_dma_buffer;
} tga_server_info_t;

typedef struct {
  unsigned char 	dirty_cell;
  unsigned char 	red;	/* only need 8 bits */
  unsigned char 	green;
  unsigned char 	blue;
} tga_bt485_color_cell_t;

typedef struct {
  volatile unsigned int	*setup;
  volatile unsigned int	*data;
  unsigned int		head_mask;
  short			fb_xoffset;
  short			fb_yoffset;
  short			min_dirty;
  short			max_dirty;
  caddr_t		reset;
  u_int			mask;
} tga_bt485_type_t;

typedef struct {
  volatile unsigned int	*setup;
  volatile unsigned int	*data;
  unsigned int		head_mask;
  short			fb_xoffset;
  short			fb_yoffset;
  short			min_dirty;
  short			max_dirty;
  caddr_t		reset;
  u_int			mask;
  /***************************************************************
   * fields above this line MUST match struct bt485type exactly!
   ***************************************************************/
  u_int			unit;
  char			screen_on;
  char			on_off;
  char			dirty_cursor;
  char			dirty_colormap;
  short			x_hot;
  short			y_hot;
  ws_color_cell		cursor_fg;
  ws_color_cell		cursor_bg;
  void			(*enable_interrupt)();
  u_long		bits[256];
  tga_bt485_color_cell_t cells[256];
} tga_bt485_info_t;

#define	TGA_RAMDAC_463_WINDOW_TAG_COUNT	16
#define	TGA_RAMDAC_463_CMAP_ENTRY_COUNT	528

typedef struct {
  unsigned char		dirty_cell;
  unsigned char		red;
  unsigned char		green;
  unsigned char		blue;
} tga_bt463_color_cell_t;

typedef struct {
  unsigned char		low_byte;
  unsigned char		middle_byte;
  unsigned char		high_byte;
  unsigned char		unused;
} tga_bt463_wid_cell_t;

typedef struct {
  volatile unsigned int *setup;
  volatile unsigned int *data;
  unsigned int		head_mask;
  short 		fb_xoffset;
  short 		fb_yoffset;
} tga_bt463_type_t;

typedef struct {
  volatile unsigned int *setup;
  volatile unsigned int *data;
  unsigned int		head_mask;
  short 		fb_xoffset;
  short 		fb_yoffset;
  char			type;
  char 			screen_on;
  char 			dirty_colormap;
  char 			dirty_cursormap;
  int			unit;
  void			(*enable_interrupt)();
  caddr_t		cursor_closure;
  ws_color_cell		cursor_fg;
  ws_color_cell		cursor_bg;
  short			min_dirty;
  short			max_dirty;
  tga_bt463_color_cell_t cells[TGA_RAMDAC_463_CMAP_ENTRY_COUNT];
} tga_bt463_info_t;

typedef struct {
  volatile unsigned int *setup;
  volatile unsigned int *data;
  unsigned int          head_mask;
  short                 fb_xoffset;
  short                 fb_yoffset;
  short                 min_dirty;
  short                 max_dirty;
  caddr_t               reset;
  u_int                 mask;
} tga_ibm561_type_t;

typedef struct {
  unsigned char         dirty_cell;
  unsigned char         red;
  unsigned char         green;
  unsigned char         blue;
} tga_ibm561_color_cell_t;

typedef struct {
  unsigned char         dirty_cell;
  unsigned char         low;
  unsigned char         high;
} tga_ibm561_gamma_cell_t;

  /***************************************************************
   * fields above this line MUST match struct bt485type exactly!
   ***************************************************************/
typedef struct {
  volatile unsigned int *setup;
  volatile unsigned int *data;
  unsigned int          head_mask;
  short                 fb_xoffset;
  short                 fb_yoffset;
  caddr_t               reset;
  u_int                 mask;
  char                  type;
  char                  screen_on;
  char                  on_off;
  short                 x_hot;
  short                 y_hot;
  ws_color_cell         cursor_fg;
  ws_color_cell         cursor_bg;
  char                  dirty_colormap;
  char                  dirty_gammamap;
  char                  dirty_cursor;
  int                   unit;
  void                  (*enable_interrupt)();
  caddr_t               cursor_closure;
  short                 cmap_min_dirty;
  short                 cmap_max_dirty;
  short                 gam_min_dirty;
  short                 gam_max_dirty;
  tga_ibm561_color_cell_t cmap_cells[TGA_RAMDAC_561_CMAP_ENTRY_COUNT];
  tga_ibm561_gamma_cell_t gam_cells[TGA_RAMDAC_561_GAM_ENTRY_COUNT];
  unsigned int          bits[256];
} tga_ibm561_info_t;

typedef struct {
  volatile unsigned int	*xy_reg;
  volatile unsigned int	*valid;
  short			fb_xoffset;
  short			fb_yoffset;
} tga_curs_type_t;

typedef struct {
  volatile unsigned int	*xy_reg;
  volatile unsigned int	*valid;
  short			fb_xoffset;
  short			fb_yoffset;
  u_int			unit;
  char			on_off;
  char			dirty_cursor;
  char			dirty_cursormap;
  short			x_hot;
  short			y_hot;
  short			last_row;
  ws_color_cell		cursor_fg;
  ws_color_cell		cursor_bg;
  void			(*enable_interrupt)();
  unsigned int		bits[256];
} tga_curs_info_t;

typedef struct {
     short  width;
     short  height;
    }screen_attr_t;

typedef struct{
  unsigned int N:7;
  unsigned int M:7;
  unsigned int V:1;
  unsigned int X:2;
  unsigned int R:2;
  unsigned int misc:5;
}pll_setup_t;

struct monitor_data{
  unsigned int max_rows;   /* Monitor setup */
  unsigned int max_cols;
  unsigned int pixel_freq;
  unsigned int refresh_rate;
  unsigned int vert_slines;
  unsigned int vert_fp;
  unsigned int vert_sync;
  unsigned int vert_bp;
  unsigned int horz_pix;
  unsigned int horz_fp;
  unsigned int horz_sync;
  unsigned int horz_bp;
  unsigned int vco_div;      /* ICS setup */
  unsigned int ref_div;
  unsigned int vco_pre;
  unsigned int clk_div;
  unsigned int vco_out_div;
  unsigned int clk_out_en;
  unsigned int clk_out_enX;
  unsigned int res0;
  unsigned int clk_sel;
  unsigned int res1;
  unsigned int ibm561_vco_div; /* IBM561 PLL setup */
  unsigned int ibm561_ref;
};

struct ramdac_reg {
 int addr;
 int *data;
};

typedef struct {
  short                 screen;
  short                 cmd;
  union {
    tga_ioc_window_tag_t        window_tag;
    unsigned int                stereo_mode;
#define TGA_IOC_STEREO_NONE             0
#define TGA_IOC_STEREO_24               1

    int                         direct_dma_count;
    tga_ioc_dma_info_t          direct_dma_info;
    tga_ramdac_t                *tga_ramdac;
    struct monitor_data         monitor;
    struct ramdac_reg           reg;
  } data;
  int                   tag_type;
} tga_ioc_t;

/*
 * XXX visual closures must have pointer to device as first element, this
 * is a hack, but I can't think of a better one right now.
 */
typedef struct {
  ws_screen_descriptor  screen;
  ws_depth_descriptor   depth[NDEPTHS];
  ws_visual_descriptor  visual[NVISUALS];
  u_char                cursor_type;
  u_char                cmap_type;
  u_char                screen_type;
  ws_cursor_functions   cf;
  ws_color_map_functions cmf;
  ws_screen_functions   sf;
  int                   (*attach)();
  int                   (*bootmsg)();
  int                   (*map)();
  int                   (*interrupt)();
  int                   (*setup)();
  u_int                 ws_display_type;
} tga_type_t;

typedef struct {
  vm_offset_t           asic_offset;
  vm_offset_t           fb_offset;
  size_t                fb_size;
  unsigned int          bt485_present;
  unsigned int          bits_per_pixel;
  unsigned int          core_size;
  unsigned int          paer_value;
} tga_sub_type_t;

/*
 * Save-state structure
 */
typedef struct {
    tga_reg_t           pixelmask;
    tga_reg_t           mode;
    tga_reg_t           rop;
    tga_reg_t           bres3;
    tga_reg_t           address;
} tga_save_regs_t;

#endif	/* TGA_DEFINED */

