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
 * @(#)$RCSfile: ati64reg.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1994/08/01 17:27:01 $
 */
/*	Register definitions for ATI Mach64		*/


 /* to make offsets from DWORD indices */
#define MKOFF(i) ((i)*4)

/**** Direct Write registers (IO and MEM space) ****/
/* Clock Control */
#define IO_CLOCK_CNTL		0x4aec
#define CLOCK_CNTL		MKOFF(0x0024)
/* CRTC */
#define IO_CRTC_GEN_CNTL	0x1eec
#define IO_CRTC_PIX_WIDTH	IO_CRTC_GEN_CNTL+1
#define IO_CRTC_FIFO_LWM	IO_CRTC_GEN_CNTL+2
#define IO_CRTC_EXT_DISP	IO_CRTC_GEN_CNTL+3
#define CRTC_GEN_CNTL		MKOFF(0x0007)
#define CRTC_EXT_DISP		CRTC_GEN_CNTL+3
#define IO_CRTC_H_SYNC_STRT_WID	0x06ec
#define CRTC_H_SYNC_STRT_WID	MKOFF(0x0001)
#define IO_CRTC_H_TOTAL_DISP	0x02ec
#define CRTC_H_TOTAL_DISP	MKOFF(0x0000)
#define IO_CRTC_INT_CNTL	0x1aec
#define CRTC_INT_CNTL		MKOFF(0x0006)
#define IO_CRTC_OFF_PITCH	0x16ec
#define CRTC_OFF_PITCH		MKOFF(0x0005)
#define IO_CRTC_V_SYNC_STRT_WID	0x0eec
#define CRTC_V_SYNC_STRT_WID	MKOFF(0x0003)
#define IO_CRTC_V_TOTAL_DISP	0x0aec
#define CRTC_V_TOTAL_DISP	MKOFF(0x0002)
#define IO_CRTC_CRNT_VLINE	0x12ec
#define CRTC_CRNT_VLINE		MKOFF(0x0004)
/* DAC Control */
#define IO_DAC_CNTL		0x62ec
#define DAC_CNTL		MKOFF(0x0031)
#define IO_DAC_REGS		0x5eec
#define DAC_REGS		MKOFF(0x0030)
/* DAC registers (within DAC_REGS) */
#define DAC_W_INDEX		DAC_REGS+0
#define DAC_DATA		DAC_REGS+1
#define DAC_MASK		DAC_REGS+2
#define DAC_R_INDEX		DAC_REGS+3
/* IO DAC registers */
#define IO_DAC_W_INDEX		IO_DAC_REGS+0
#define IO_DAC_DATA		IO_DAC_REGS+1
#define IO_DAC_MASK		IO_DAC_REGS+2
#define IO_DAC_R_INDEX		IO_DAC_REGS+3
/* Hardware Cursor */
#define IO_CUR_CLR0		0x2eec
#define CUR_CLR0		MKOFF(0x0018)
#define IO_CUR_CLR1		0x32ec
#define CUR_CLR1		MKOFF(0x0019)
#define IO_CUR_HORZ_VERT_OFF	0x3eec
#define CUR_HORZ_VERT_OFF	MKOFF(0x001c)
#define IO_CUR_HORZ_VERT_POSN	0x3aec
#define CUR_HORZ_VERT_POSN	MKOFF(0x001b)
#define IO_CUR_OFFSET		0x36ec
#define CUR_OFFSET		MKOFF(0x001a)
/* Overscan */
#define IO_OVR_CLR		0x22ec
#define OVR_CLR			MKOFF(0x0010 )
#define IO_OVR_WID_LEFT_RIGHT	0x26ec
#define OVR_WID_LEFT_RIGHT	MKOFF(0x0011 )
#define IO_OVR_WID_TOP_BOTTOM	0x2aec
#define OVR_WID_TOP_BOTTOM	MKOFF(0x0012 )

/**** Setup and Control ****/
/* Bus Control */
#define IO_BUS_CNTL		0x4eec
#define BUS_CNTL		MKOFF(0x0028)
/* Configuration */
#define IO_CONFIG_CHIP_ID	0x6eec
#define CONFIG_CHIP_ID		MKOFF(0x0038)
#define IO_CONFIG_CNTL		0x6aec
#define IO_CONFIG_STAT0		0x72ec
#define CONFIG_STAT0		MKOFF(0x0039)
#define IO_CONFIG_STAT1		0x76ec
#define CONFIG_STAT1		MKOFF(0x003a)
/* Memory Control */
#define IO_MEM_CNTL		0x52ec
#define MEM_CNTL		MKOFF(0x002c)
#define IO_MEM_VGA_RP_SEL	0x5aec
#define MEM_VGA_RP_SEL		MKOFF(0x002e)
#define IO_MEM_VGA_WP_SEL	0x56ec
#define MEM_VGA_WP_SEL		MKOFF(0x002d)
/* Scratch Pad */
#define IO_SCRATCH_REG0		0x42ec
#define SCRATCH_REG0		MKOFF(0x0020)
#define IO_SCRATCH_REG1		0x46ec
#define SCRATCH_REG1		MKOFF(0x0021)
/* Test */
#define IO_GEN_TEST_CNTL	0x66ec
#define GEN_TEST_CNTL		MKOFF(0x0034)

/**** FIFOed Registers (MEM only) ****/
/** Draw Engine Control **/
/* Color Compare */
#define CLR_CMP_CLR		MKOFF(0x00c0)
#define CLR_CMP_CNTL		MKOFF(0x00c2)
#define CLR_CMP_MASK		MKOFF(0x00c1)
/* Context Control */
#define CONTEXT_LOAD_CNTL	MKOFF(0x00cb)
#define CONTEXT_MSK		MKOFF(0x00c8)
/* Data Path */
#define DP_BKGD_CLR		MKOFF(0x00b0)
#define DP_CHAIN_MSK		MKOFF(0x00b3)
#define DP_FRGD_CLR		MKOFF(0x00b1)
#define DP_MIX			MKOFF(0x00b5)
#define DP_PIX_WIDTH		MKOFF(0x00b4)
#define DP_SRC			MKOFF(0x00b6)
#define DP_WRITE_MSK		MKOFF(0x00b2)
/* Engine Status */
#define GUI_STAT		MKOFF(0x00ce)
#define GUI_TRAJ_CNTL		MKOFF(0x00cc)
/* FIFO Status */
#define FIFO_STAT		MKOFF(0x00c4)
/* Host Data */
#define HOST_CNTL		MKOFF(0x0090)
#define HOST_DATA		MKOFF(0x0080)
/* Pattern */
#define PAT_CNTL		MKOFF(0x00a2)
#define PAT_REG0		MKOFF(0x00a0)
#define PAT_REG1		MKOFF(0x00a1)
/* Scissor */
#define SC_BOTTOM		MKOFF(0x00ac)
#define SC_LEFT			MKOFF(0x00a8)
#define SC_LEFT_RIGHT		MKOFF(0x00aa)
#define SC_RIGHT		MKOFF(0x00a9)
#define SC_TOP			MKOFF(0x00ab)
#define SC_TOP_BOTTOM		MKOFF(0x00ad)
/** Draw Engine Trajectory **/
/* Destination Draw Engine */
#define DST_BRES_DEC		MKOFF(0x004b)
#define DST_BRES_ERR		MKOFF(0x0049)
#define DST_BRES_INC		MKOFF(0x004a)
#define DST_BRES_LNTH		MKOFF(0x0048)
#define DST_CNTL		MKOFF(0x004c)
#define DST_HEIGHT		MKOFF(0x0045)
#define DST_HEIGHT_WIDTH	MKOFF(0x0046)
#define DST_OFF_PITCH		MKOFF(0x0040)
#define DST_WIDTH		MKOFF(0x0044)
#define DST_X			MKOFF(0x0041)
#define DST_X_WIDTH		MKOFF(0x0047)
#define DST_Y			MKOFF(0x0042)
#define DST_Y_X			MKOFF(0x0043)
/* Source Draw Engine */
#define SRC_CNTL		MKOFF(0x006d)
#define SRC_HEIGHT1		MKOFF(0x0065)
#define SRC_HEIGHT_WIDTH1	MKOFF(0x0066)
#define SRC_HEIGHT2		MKOFF(0x006b)
#define SRC_HEIGHT_WIDTH2	MKOFF(0x006c)
#define SRC_OFF_PITCH		MKOFF(0x0060)
#define SRC_WIDTH1		MKOFF(0x0064)
#define SRC_WIDTH2		MKOFF(0x006a)
#define SRC_X			MKOFF(0x0061)
#define SRC_X_START		MKOFF(0x0067)
#define SRC_Y			MKOFF(0x0062)
#define SRC_Y_START		MKOFF(0x0068)
#define SRC_Y_X			MKOFF(0x0063)
#define SRC_Y_X_START		MKOFF(0x0069)

/* GUI_STAT bit 0 is set if the engine is busy. */
#define GUI_STAT_BUSY 0x0001

/* define the true VGA DAC register addresses */
#define VGA_DAC_MASK		0x03c6
#define VGA_DAC_R_INDEX		0x03c7
#define VGA_DAC_W_INDEX		0x03c8
#define VGA_DAC_DATA		0x03c9
