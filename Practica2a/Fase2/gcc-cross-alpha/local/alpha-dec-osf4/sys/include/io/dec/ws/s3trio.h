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
 * @(#)$RCSfile: s3trio.h,v $ $Revision: 1.1.21.2 $ (DEC) $Date: 1997/02/28 20:30:43 $
 */


#ifndef _S3TRIO_H_
#define _S3TRIO_H_

#ifdef KERNEL
/* screen functions */
extern caddr_t	s3trio_init_screen_handle();
extern int	s3trio_init_screen();
extern int	s3trio_clear_screen();
extern int	s3trio_scroll_screen();
extern int	s3trio_blitc();
extern int	s3trio_ioctl();
extern int	s3trio_map_unmap_screen();
extern void	s3trio_close();
extern int	s3trio_set_get_power_level();

/* cursor functions */
extern caddr_t	s3trio_init_cursor_handle();
extern int	s3trio_vga_load_cursor();
extern int	s3trio_load_cursor();
extern int	s3trio_recolor_cursor();
extern int	s3trio_vga_set_cursor_position();
extern int	s3trio_set_cursor_position();
extern int	s3trio_vga_cursor_on_off();
extern int	s3trio_cursor_on_off();

/* colormap functions */
extern caddr_t	s3trio_init_color_map_handle();
extern int	s3trio_init_color_map();
extern int	s3trio_load_color_map_entry();
extern void	s3trio_clean_color_map();
extern int	s3trio_video_on();
extern int	s3trio_video_off();

/* adaptor functions */
extern void s3trio_save();
extern void s3trio_restore();
extern void s3trio_init();
extern void s3trio_print();
extern void s3trio_interrupt();
extern void s3trio_bot();

/* configuration function */
extern int s3trio_configure();

/* VGA register access */
#define SEQ_INDEX                              0x03C4
#define SEQ_DATA                               0x03C5
#define CRTC_ADDRESS                           0x03D4
#define CRTC_DATA                              0x03D5

/* S3 register macros */
#define CHIP_REV_LVL                           0x002F
#define CHIP_ID_REG                   	       0x0030
#define MEM_CONFIG                             0x0031
#define CONF1_REG                              0x0036
#define VGA_LOCK_REG                   	       0x0038
#define SYS_LOCK_REG                   	       0x0039
#define SYS_CONF_REG                   	       0x0040
#define HG_CURSOR_MODE                         0x0045
#define HG_CURSOR_X_ORG1                       0x0046
#define HG_CURSOR_X_ORG2                       0x0047
#define HG_CURSOR_Y_ORG1                       0x0048
#define HG_CURSOR_Y_ORG2                       0x0049
#define HG_CURSOR_FG                   	       0x004A
#define HG_CURSOR_BG                   	       0x004B
#define HG_CURSOR_START                        0x004C
#define HG_CURSOR_START2                       0x004D
#define HG_DISP_X                              0x004E
#define HG_DISP_Y                              0x004F
#define EXT_MEM_CONT                           0x0053
#define HG_CURSOR_SW                           0x0055
#define LIN_ADD_WIN_CONT                       0x0058
#define EXT_MISC_CONT0                         0x0065
#define EXT_MISC_CONT1                         0x0066

/* Trio extended register set */
#define SUBSYS_CTL                             0x42E8 /* write only */
#define SUBSYS_STATUS                          0x42E8 /* read only */
#define VIDEO_SUBSYS                   	       0x46E8
#define ADV_FUNC_CNTL                          0x4AE8
#define GRAPH_STATUS                   	       0x9AE8 + 0xA0000


/* miscellaneous */
#define LINEAR_ADDRESSING_MODE                 0x0011
#define MMIO_ADDRESSING_MODE                   0x0021
#define GP_BUSY                                0x0200 /* bit 9 of 9AE8 */
#define CSR_BG_INDEX                   	       0x0002
#define CSR_FG_INDEX                   	       0x0003 

/* Plug N' Play version of S3 Trio graphics adapter has support */
/* for operation downstream of a PCI-PCI bridge. V+ is the new  */
/* trio64 chip on a PNP card */
#define ORIGINAL                                    1
#define PNP                                         2 
#define VPLUS                                       3

#define TRIO_PCI_PROBE_SUCCESS                      2
#define TRIO_PROBE_SUCCESS                          1 /* Req of intfc */
#define TRIO_PROBE_FAILURE                          0


/* S3 register locking macros */
#define sys_lock()\
	OUTB(CRTC_ADDRESS, SYS_LOCK_REG);\
	OUTB(CRTC_DATA, 0x0);
#define sys_unlock()\
	OUTB(CRTC_ADDRESS, SYS_LOCK_REG);\
	OUTB(CRTC_DATA, 0xA0);
#define vga_lock()\
	OUTB(CRTC_ADDRESS, VGA_LOCK_REG);\
	OUTB(CRTC_DATA, 0x0);
#define vga_unlock()\
	OUTB(CRTC_ADDRESS, VGA_LOCK_REG);\
	OUTB(CRTC_DATA, 0x48);

/* hardware graphics cursor color indices macros */
#define set_cfg_index()\
	{ OUTB(CRTC_ADDRESS, HG_CURSOR_MODE); INB(CRTC_DATA);\
	OUTB(CRTC_ADDRESS, HG_CURSOR_FG); OUTB(CRTC_DATA, CSR_FG_INDEX); }

#define set_cbg_index()\
	{ OUTB(CRTC_ADDRESS, HG_CURSOR_MODE); INB(CRTC_DATA);\
	OUTB(CRTC_ADDRESS, HG_CURSOR_BG); OUTB(CRTC_DATA, CSR_BG_INDEX); }

typedef struct {
	vgaHWRec std;          /* std IBM VGA registers - must be first! */
	
	/* S3 extended sequencer */
	unsigned char S3_SR08;
	unsigned char S3_SR0D;
	
	/* S3 VGA registers */
	unsigned char S3_CR30;
	unsigned char S3_CR31;	/* memory configuration register */
	unsigned char S3_CR32;
	unsigned char S3_CR33;
	unsigned char S3_CR34;
	unsigned char S3_CR35;
	unsigned char S3_CR36;
	unsigned char S3_CR37;
	unsigned char S3_CR38;
	unsigned char S3_CR39;
	unsigned char S3_CR3A;
	unsigned char S3_CR3B;
	unsigned char S3_CR3C;
	
	/* System Control Registers */
	unsigned char S3_CR40;	/* system configuration register */
	unsigned char S3_CR41;
	unsigned char S3_CR42;
	unsigned char S3_CR43;
	unsigned char S3_CR45; 	/* cursor support on V864 */
	unsigned char S3_CR46;
	unsigned char S3_CR47;
	unsigned char S3_CR48;
	unsigned char S3_CR49;
	unsigned char S3_CR4A; 	/* hardware cursor foreground color */
	unsigned char S3_CR4B; 	/* hardware cusror background color */
	unsigned char S3_CR4C;	/* hardware cusror start address */
	unsigned char S3_CR4D;        /* hardware cusror start address, pt 2 */
	unsigned char S3_CR4E;
	unsigned char S3_CR4F;
	
	/* System Extension Registers */
	unsigned char S3_CR50;
	unsigned char S3_CR51;
	unsigned char S3_CR52;
	unsigned char S3_CR53; 	/* Extended mode memory mapping switch, bit 4 */
	unsigned char S3_CR54;
	unsigned char S3_CR55;	/* MSC Windows and X11 hardware cursor switch */
	unsigned char S3_CR56;
	unsigned char S3_CR57;
	unsigned char S3_CR58;
	unsigned char S3_CR59;
	unsigned char S3_CR5A;
	unsigned char S3_CR5B;
	unsigned char S3_CR5C;
	unsigned char S3_CR5D;
	unsigned char S3_CR5E;
	unsigned char S3_CR5F;
	unsigned char S3_CR60;
	unsigned char S3_CR61;
	unsigned char S3_CR62;
	unsigned char S3_CR63;
	unsigned char S3_CR64;
	unsigned char S3_CR65;
	unsigned char S3_CR66;
	unsigned char S3_CR67;
	unsigned char S3_CR68;
	unsigned char S3_CR69;
	unsigned char S3_CR6A;
	unsigned char S3_CR6B;
	unsigned char S3_CR6C;
	unsigned char S3_CR6D;
	
	/* Enhanced Commands Registers */
	unsigned short S3_SUBSYS_CNTL;
	unsigned short S3_ADVFNC_CNTL;

} vgaS3trioRec, *vgaS3trioPtr;


#endif /* KERNEL */

#endif /* _S3TRIO_H_ */

