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
 * @(#)$RCSfile: atireg.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1994/02/25 21:28:05 $
 */

/*	Register definitions for ATI 68800		*/



/*************************************************************************
 **                                                                     **
 **                             AMACH.H                                 **
 **                                                                     **
 **     Copyright (c) 1993, ATI Technologies Inc.                       **
 *************************************************************************/
/*   
 *  Created from the 68800.H and 68801.H in the Windows NT Group
 *      as a simple merging of the files so ALL Mach8 and Mach32 defines
 *      are located in one H file.
 *
 *  Created the 68800.inc file which includes equates, macros, etc 
 *       from the following include files:    
 *       8514vesa.inc, vga1regs.inc,  m32regs.inc,  8514.inc
 *
 * supplement Defines, structures and values to the 68800 Family.
 *
 * This is a "C" only file and is NOT derived from any Assembler INC files.
 */

#if 0  
        
/*-------------------------------------------------------------------------*/
/*                 REGISTER PORT ADDRESSES				   */
/*									   */
#define SETUP_ID1            0x0100 /* Setup Mode Identification (Byte 1) */
#define SETUP_ID2            0x0101 /* Setup Mode Identification (Byte 2) */
#define SETUP_OPT            0x0102 /* Setup Mode Option Select */
#define ROM_SETUP            0x0103 /* */
#define SETUP_1              0x0104 /* */
#define SETUP_2              0x0105 /* */


/*   Lowest and highest I/O ports used by the VGAWonder.  */
#define VGA_BASE_IO_PORT	0x03B0
#define VGA_START_BREAK_PORT	0x03BB
#define VGA_END_BREAK_PORT	0x03C0
#define VGA_MAX_IO_PORT 	0x03DF

/* Registers used in reading/writing EEPROM */
#define IO_SEQ_IND     0x03C4           /* Sequencer index register  */
#define IO_HI_SEQ_ADDR IO_SEQ_IND       /* word register */
#define IO_SEQ_DATA    0x03C5           /* Sequencer data register  */

#endif /* 0 */

/* define registers in IO space */
#define IO_DAC_MASK             0x02EA /* DAC Mask */
#define IO_DAC_R_INDEX          0x02EB /* DAC Read Index */
#define IO_DAC_W_INDEX          0x02EC /* DAC Write Index */
#define IO_DAC_DATA             0x02ED /* DAC Data */

#define IO_DISP_STATUS          0x02E8 /* Display Status */
#define IO_H_TOTAL              0x02E8 /* Horizontal Total */
#define IO_OVERSCAN_COLOR_8     0x02EE 
#define IO_OVERSCAN_BLUE_24     0x02EF 
#define IO_H_DISP               0x06E8 /* Horizontal Displayed */
#define IO_OVERSCAN_GREEN_24    0x06EE 
#define IO_OVERSCAN_RED_24      0x06EF 
#define IO_H_SYNC_STRT          0x0AE8 /* Horizontal Sync Start */
#define IO_CURSOR_OFFSET_LO     0x0AEE 
#define IO_H_SYNC_WID           0x0EE8 /* Horizontal Sync Width */
#define IO_CURSOR_OFFSET_HI     0x0EEE 
#define IO_V_TOTAL              0x12E8 /* Vertical Total */
#define IO_CONFIG_STATUS_1      0x12EE /* Read only equivalent to HORZ_CURSOR_POSN  */
#define IO_HORZ_CURSOR_POSN     0x12EE 
#define IO_V_DISP               0x16E8 /* Vertical Displayed */
#define IO_CONFIG_STATUS_2      0x16EE /* Read only equivalent to VERT_CURSOR_POSN */
#define IO_VERT_CURSOR_POSN     0x16EE 
#define IO_V_SYNC_STRT          0x1AE8 /* Vertical Sync Start */
#define IO_CURSOR_COLOR_0       0x1AEE 
#define IO_FIFO_TEST_DATA       0x1AEE 
#define IO_CURSOR_COLOR_1       0x1AEF 
#define IO_V_SYNC_WID           0x1EE8 /* Vertical Sync Width */
#define IO_HORZ_CURSOR_OFFSET   0x1EEE 
#define IO_VERT_CURSOR_OFFSET   0x1EEF 
#define IO_DISP_CNTL            0x22E8 /* Display Control  */
#define IO_CRT_PITCH            0x26EE 
#define IO_CRT_OFFSET_LO        0x2AEE 
#define IO_CRT_OFFSET_HI        0x2EEE 
#define IO_LOCAL_CONTROL        0x32EE 
#define IO_FIFO_OPT             0x36EE 
#define IO_MISC_OPTIONS         0x36EE 
#define IO_EXT_CURSOR_COLOR_0   0x3AEE 
#define IO_FIFO_TEST_TAG        0x3AEE 
#define IO_EXT_CURSOR_COLOR_1   0x3EEE 
#define IO_SUBSYS_CNTL          0x42E8 /* Subsystem Control */
#define IO_SUBSYS_STAT          0x42E8 /* Subsystem Status */
#define IO_MEM_BNDRY            0x42EE 
#define IO_SHADOW_CTL           0x46EE 
#define IO_ROM_PAGE_SEL         0x46E8 /* ROM Page Select (not in manual) */
#define IO_ADVFUNC_CNTL         0x4AE8 /* Advanced Function Control */
#define IO_CLOCK_SEL            0x4AEE 
        
#define IO_ROM_ADDR_1           0x52EE 
#define IO_ROM_ADDR_2           0x56EE 
#define IO_SCRATCH_PAD_0        0x52EE 
#define IO_SCRATCH_PAD_1        0x56EE 
        
#define IO_SHADOW_SET           0x5AEE 
#define IO_MEM_CFG              0x5EEE 
#define IO_EXT_GE_STATUS        0x62EE 
        
#define IO_HORZ_OVERSCAN        0x62EE 
#define IO_VERT_OVERSCAN        0x66EE 
        
#define IO_MAX_WAITSTATES       0x6AEE 
#define IO_GE_OFFSET_LO         0x6EEE 
#define IO_BOUNDS_LEFT          0x72EE 
#define IO_GE_OFFSET_HI         0x72EE 
#define IO_BOUNDS_TOP           0x76EE 
#define IO_GE_PITCH             0x76EE 
#define IO_BOUNDS_RIGHT         0x7AEE 
#define IO_EXT_GE_CONFIG        0x7AEE 
#define IO_BOUNDS_BOTTOM        0x7EEE 
#define IO_MISC_CNTL            0x7EEE 
#define IO_CUR_Y                0x82E8 /* Current Y Position */
#define IO_PATT_DATA_INDEX      0x82EE 
#define IO_CUR_X                0x86E8 /* Current X Position */
#define IO_SRC_Y                0x8AE8 /* */
#define IO_DEST_Y               0x8AE8 /* */
#define IO_AXSTP                0x8AE8 /* Destination Y Position */
#define IO_SRC_X                0x8EE8 /* Axial     Step Constant */
#define IO_DEST_X               0x8EE8 /* */
#define IO_DIASTP               0x8EE8 /* Destination X Position */
#define IO_PATT_DATA            0x8EEE 
#define IO_R_EXT_GE_CONFIG      0x8EEE 
#define IO_ERR_TERM             0x92E8 /* Error Term */
#define IO_R_MISC_CNTL          0x92EE 
#define IO_MAJ_AXIS_PCNT        0x96E8 /* Major Axis Pixel Count */
#define IO_BRES_COUNT           0x96EE 
#define IO_CMD                  0x9AE8 /* Command */
#define IO_GE_STAT              0x9AE8 /* Graphics Processor Status */
#define IO_EXT_FIFO_STATUS      0x9AEE 
#define IO_LINEDRAW_INDEX       0x9AEE 
#define IO_SHORT_STROKE         0x9EE8 /* Short Stroke Vector Transfer */
#define IO_BKGD_COLOR           0xA2E8 /* Background Color */
#define IO_LINEDRAW_OPT         0xA2EE 
#define IO_FRGD_COLOR           0xA6E8 /* Foreground Color */
#define IO_DEST_X_START         0xA6EE 
#define IO_WRT_MASK             0xAAE8 /* Write Mask */
#define IO_DEST_X_END           0xAAEE 
#define IO_RD_MASK              0xAEE8 /* Read Mask */
#define IO_DEST_Y_END           0xAEEE 
#define IO_CMP_COLOR            0xB2E8 /* Compare Color */
#define IO_R_H_TOTAL            0xB2EE 
#define IO_R_H_DISP             0xB2EE 
#define IO_SRC_X_START          0xB2EE 
#define IO_BKGD_MIX             0xB6E8 /* Background Mix */
#define IO_ALU_BG_FN            0xB6EE 
#define IO_R_H_SYNC_STRT        0xB6EE 
#define IO_FRGD_MIX             0xBAE8 /* Foreground Mix */
#define IO_ALU_FG_FN            0xBAEE 
#define IO_R_H_SYNC_WID         0xBAEE 
#define IO_MULTIFUNC_CNTL       0xBEE8 /* Multi-Function Control (mach 8) */
#define IO_MIN_AXIS_PCNT        0xBEE8 
#define IO_SCISSOR_T            0xBEE8 
#define IO_SCISSOR_L            0xBEE8 
#define IO_SCISSOR_B            0xBEE8 
#define IO_SCISSOR_R            0xBEE8 
#define IO_MEM_CNTL             0xBEE8 
#define IO_PATTERN_L            0xBEE8 
#define IO_PATTERN_H            0xBEE8 
#define IO_PIXEL_CNTL           0xBEE8 
#define IO_SRC_X_END            0xBEEE 
#define IO_SRC_Y_DIR            0xC2EE 
#define IO_R_V_TOTAL            0xC2EE 
#define IO_EXT_SSV              0xC6EE /* (used for MACH 8) */
#define IO_EXT_SHORT_STROKE     0xC6EE 
#define IO_R_V_DISP             0xC6EE 
#define IO_SCAN_X               0xCAEE 
#define IO_R_V_SYNC_STRT        0xCAEE 
#define IO_DP_CONFIG            0xCEEE 
#define IO_VERT_LINE_CNTR       0xCEEE 
#define IO_PATT_LENGTH          0xD2EE 
#define IO_R_V_SYNC_WID         0xD2EE 
#define IO_PATT_INDEX           0xD6EE 
#define IO_EXT_SCISSOR_L        0xDAEE /* "extended" left scissor (12 bits precision) */
#define IO_R_SRC_X              0xDAEE 
#define IO_EXT_SCISSOR_T        0xDEEE /* "extended" top scissor (12 bits precision) */
#define IO_R_SRC_Y              0xDEEE 
#define IO_PIX_TRANS            0xE2E8 /* Pixel Data Transfer */
#define IO_PIX_TRANS_HI         0xE2E9 /* Pixel Data Transfer */
#define IO_EXT_SCISSOR_R        0xE2EE /* "extended" right scissor (12 bits precision) */
#define IO_EXT_SCISSOR_B        0xE6EE /* "extended" bottom scissor (12 bits precision) */
#define IO_SRC_CMP_COLOR        0xEAEE /* (used for MACH 8) */
#define IO_DEST_CMP_FN          0xEEEE 
#define IO_EXT_CUR_Y            0xF6EE /* Mach8 only */
#define IO_ASIC_ID              0xFAEE /* Mach32 rev 6 */
#define IO_LINEDRAW             0xFEEE 



/* Internal registers (read only, for test purposes only) */
#define IO__PAR_FIFO_DATA       0x1AEE 
#define IO__PAR_FIFO_ADDR       0x3AEE 
#define IO__MAJOR_DEST_CNT      0x42EE 
#define IO__MAJOR_SRC_CNT       0x5EEE 
#define IO__MINOR_DEST_CNT      0x66EE 
#define IO__MINOR_SRC_CNT       0x8AEE 
#define IO__HW_TEST             0x32EE 
        
/*--------------------------------------------------------- */
/* define the registers locations in Memory Mapped space */
/* take the IO address and and with 0xFC00 works for offset */

/*---     IF	(port AND 0FFh) EQ 0E8h */
/*---           mov word ptr seg:[edx+(3FFE00h+((port AND 0FC00h)shr 8))],ax */
/*---     ELSE */
/*---       IF	(port AND 0FFh) EQ 0EEh */
/*---           mov word ptr seg:[edx+(3FFF00h+((port AND 0FC00h)shr 8))],ax */

#define MM_DISP_STATUS          0x3ffe00+((IO_DISP_STATUS      & 0xFC00) >> 8)
#define MM_H_TOTAL              0x3ffe00+((IO_H_TOTAL          & 0xFC00) >> 8)
#define MM_H_DISP               0x3ffe00+((IO_H_DISP           & 0xFC00) >> 8)
#define MM_H_SYNC_STRT          0x3ffe00+((IO_H_SYNC_STRT      & 0xFC00) >> 8)
#define MM_H_SYNC_WID           0x3ffe00+((IO_H_SYNC_WID       & 0xFC00) >> 8)
#define MM_V_TOTAL              0x3ffe00+((IO_V_TOTAL          & 0xFC00) >> 8)
#define MM_V_DISP               0x3ffe00+((IO_V_DISP           & 0xFC00) >> 8)
#define MM_V_SYNC_STRT          0x3ffe00+((IO_V_SYNC_STRT      & 0xFC00) >> 8)
#define MM_V_SYNC_WID           0x3ffe00+((IO_V_SYNC_WID       & 0xFC00) >> 8)
#define MM_DISP_CNTL            0x3ffe00+((IO_DISP_CNTL        & 0xFC00) >> 8)
#define MM_SUBSYS_CNTL          0x3ffe00+((IO_SUBSYS_CNTL      & 0xFC00) >> 8)
#define MM_SUBSYS_STAT          0x3ffe00+((IO_SUBSYS_STAT      & 0xFC00) >> 8)
#define MM_ROM_PAGE_SEL         0x3ffe00+((IO_ROM_PAGE_SEL     & 0xFC00) >> 8)
#define MM_ADVFUNC_CNTL         0x3ffe00+((IO_ADVFUNC_CNTL     & 0xFC00) >> 8)
#define MM_CUR_Y                0x3ffe00+((IO_CUR_Y            & 0xFC00) >> 8)
#define MM_CUR_X                0x3ffe00+((IO_CUR_X            & 0xFC00) >> 8)
#define MM_SRC_Y                0x3ffe00+((IO_SRC_Y            & 0xFC00) >> 8)
#define MM_DEST_Y               0x3ffe00+((IO_DEST_Y           & 0xFC00) >> 8)
#define MM_AXSTP                0x3ffe00+((IO_AXSTP            & 0xFC00) >> 8)
#define MM_SRC_X                0x3ffe00+((IO_SRC_X            & 0xFC00) >> 8)
#define MM_DEST_X               0x3ffe00+((IO_DEST_X           & 0xFC00) >> 8)
#define MM_DIASTP               0x3ffe00+((IO_DIASTP           & 0xFC00) >> 8)
#define MM_ERR_TERM             0x3ffe00+((IO_ERR_TERM         & 0xFC00) >> 8)
#define MM_MAJ_AXIS_PCNT        0x3ffe00+((IO_MAJ_AXIS_PCNT    & 0xFC00) >> 8)
#define MM_CMD                  0x3ffe00+((IO_CMD              & 0xFC00) >> 8)
#define MM_GE_STAT              0x3ffe00+((IO_GE_STAT          & 0xFC00) >> 8)
#define MM_SHORT_STROKE         0x3ffe00+((IO_SHORT_STROKE     & 0xFC00) >> 8)
#define MM_BKGD_COLOR           0x3ffe00+((IO_BKGD_COLOR       & 0xFC00) >> 8)
#define MM_FRGD_COLOR           0x3ffe00+((IO_FRGD_COLOR       & 0xFC00) >> 8)
#define MM_WRT_MASK             0x3ffe00+((IO_WRT_MASK         & 0xFC00) >> 8)
#define MM_RD_MASK              0x3ffe00+((IO_RD_MASK          & 0xFC00) >> 8)
#define MM_CMP_COLOR            0x3ffe00+((IO_CMP_COLOR        & 0xFC00) >> 8)
#define MM_BKGD_MIX             0x3ffe00+((IO_BKGD_MIX         & 0xFC00) >> 8)
#define MM_FRGD_MIX             0x3ffe00+((IO_FRGD_MIX         & 0xFC00) >> 8)
#define MM_MULTIFUNC_CNTL       0x3ffe00+((IO_MULTIFUNC_CNTL   & 0xFC00) >> 8)
#define MM_MIN_AXIS_PCNT        0x3ffe00+((IO_MIN_AXIS_PCNT    & 0xFC00) >> 8)
#define MM_SCISSOR_T            0x3ffe00+((IO_SCISSOR_T        & 0xFC00) >> 8)
#define MM_SCISSOR_L            0x3ffe00+((IO_SCISSOR_L        & 0xFC00) >> 8)
#define MM_SCISSOR_B            0x3ffe00+((IO_SCISSOR_B        & 0xFC00) >> 8)
#define MM_SCISSOR_R            0x3ffe00+((IO_SCISSOR_R        & 0xFC00) >> 8)
#define MM_MEM_CNTL             0x3ffe00+((IO_MEM_CNTL         & 0xFC00) >> 8)
#define MM_PATTERN_L            0x3ffe00+((IO_PATTERN_L        & 0xFC00) >> 8)
#define MM_PATTERN_H            0x3ffe00+((IO_PATTERN_H        & 0xFC00) >> 8)
#define MM_PIXEL_CNTL           0x3ffe00+((IO_PIXEL_CNTL       & 0xFC00) >> 8)
#define MM_PIX_TRANS            0x3ffe00+((IO_PIX_TRANS        & 0xFC00) >> 8)
#define MM_PIX_TRANS_HI         0x3ffe00+((IO_PIX_TRANS_HI     & 0xFC00) >> 8)


#define MM_OVERSCAN_COLOR_8     0x3fff00+((IO_OVERSCAN_COLOR_8     & 0xFC00) >> 8) + (IO_OVERSCAN_COLOR_8     & 1)    
#define MM_OVERSCAN_BLUE_24     0x3fff00+((IO_OVERSCAN_BLUE_24     & 0xFC00) >> 8) + (IO_OVERSCAN_BLUE_24     & 1) 
#define MM_OVERSCAN_GREEN_24    0x3fff00+((IO_OVERSCAN_GREEN_24    & 0xFC00) >> 8) + (IO_OVERSCAN_GREEN_24    & 1) 
#define MM_OVERSCAN_RED_24      0x3fff00+((IO_OVERSCAN_RED_24      & 0xFC00) >> 8) + (IO_OVERSCAN_RED_24      & 1) 
#define MM_CURSOR_OFFSET_LO     0x3fff00+((IO_CURSOR_OFFSET_LO     & 0xFC00) >> 8) + (IO_CURSOR_OFFSET_LO     & 1) 
#define MM_CURSOR_OFFSET_HI     0x3fff00+((IO_CURSOR_OFFSET_HI     & 0xFC00) >> 8) + (IO_CURSOR_OFFSET_HI     & 1) 
#define MM_CONFIG_STATUS_1      0x3fff00+((IO_CONFIG_STATUS_1      & 0xFC00) >> 8) + (IO_CONFIG_STATUS_1      & 1) 
#define MM_HORZ_CURSOR_POSN     0x3fff00+((IO_HORZ_CURSOR_POSN     & 0xFC00) >> 8) + (IO_HORZ_CURSOR_POSN     & 1) 
#define MM_CONFIG_STATUS_2      0x3fff00+((IO_CONFIG_STATUS_2      & 0xFC00) >> 8) + (IO_CONFIG_STATUS_2      & 1)
#define MM_VERT_CURSOR_POSN     0x3fff00+((IO_VERT_CURSOR_POSN     & 0xFC00) >> 8) + (IO_VERT_CURSOR_POSN     & 1)
#define MM_CURSOR_COLOR_0       0x3fff00+((IO_CURSOR_COLOR_0       & 0xFC00) >> 8) + (IO_CURSOR_COLOR_0       & 1)
#define MM_FIFO_TEST_DATA       0x3fff00+((IO_FIFO_TEST_DATA       & 0xFC00) >> 8) + (IO_FIFO_TEST_DATA       & 1)
#define MM_CURSOR_COLOR_1       0x3fff00+((IO_CURSOR_COLOR_1       & 0xFC00) >> 8) + (IO_CURSOR_COLOR_1       & 1)
#define MM_HORZ_CURSOR_OFFSET   0x3fff00+((IO_HORZ_CURSOR_OFFSET   & 0xFC00) >> 8) + (IO_HORZ_CURSOR_OFFSET   & 1)
#define MM_VERT_CURSOR_OFFSET   0x3fff00+((IO_VERT_CURSOR_OFFSET   & 0xFC00) >> 8) + (IO_VERT_CURSOR_OFFSET   & 1)
#define MM_CRT_PITCH            0x3fff00+((IO_CRT_PITCH            & 0xFC00) >> 8) + (IO_CRT_PITCH            & 1)
#define MM_CRT_OFFSET_LO        0x3fff00+((IO_CRT_OFFSET_LO        & 0xFC00) >> 8) + (IO_CRT_OFFSET_LO        & 1)
#define MM_CRT_OFFSET_HI        0x3fff00+((IO_CRT_OFFSET_HI        & 0xFC00) >> 8) + (IO_CRT_OFFSET_HI        & 1)
#define MM_LOCAL_CONTROL        0x3fff00+((IO_LOCAL_CONTROL        & 0xFC00) >> 8) + (IO_LOCAL_CONTROL        & 1)
#define MM_FIFO_OPT             0x3fff00+((IO_FIFO_OPT             & 0xFC00) >> 8) + (IO_FIFO_OPT             & 1)
#define MM_MISC_OPTIONS         0x3fff00+((IO_MISC_OPTIONS         & 0xFC00) >> 8) + (IO_MISC_OPTIONS         & 1)
#define MM_EXT_CURSOR_COLOR_0   0x3fff00+((IO_EXT_CURSOR_COLOR_0   & 0xFC00) >> 8) + (IO_EXT_CURSOR_COLOR_0   & 1)
#define MM_FIFO_TEST_TAG        0x3fff00+((IO_FIFO_TEST_TAG        & 0xFC00) >> 8) + (IO_FIFO_TEST_TAG        & 1)
#define MM_EXT_CURSOR_COLOR_1   0x3fff00+((IO_EXT_CURSOR_COLOR_1   & 0xFC00) >> 8) + (IO_EXT_CURSOR_COLOR_1   & 1)
#define MM_MEM_BNDRY            0x3fff00+((IO_MEM_BNDRY            & 0xFC00) >> 8) + (IO_MEM_BNDRY            & 1)
#define MM_SHADOW_CTL           0x3fff00+((IO_SHADOW_CTL           & 0xFC00) >> 8) + (IO_SHADOW_CTL           & 1)
#define MM_CLOCK_SEL            0x3fff00+((IO_CLOCK_SEL            & 0xFC00) >> 8) + (IO_CLOCK_SEL            & 1)
#define MM_ROM_ADDR_1           0x3fff00+((IO_ROM_ADDR_1           & 0xFC00) >> 8) + (IO_ROM_ADDR_1           & 1)
#define MM_ROM_ADDR_2           0x3fff00+((IO_ROM_ADDR_2           & 0xFC00) >> 8) + (IO_ROM_ADDR_2           & 1)
#define MM_SCRATCH_PAD_0        0x3fff00+((IO_SCRATCH_PAD_0        & 0xFC00) >> 8) + (IO_SCRATCH_PAD_0        & 1)
#define MM_SCRATCH_PAD_1        0x3fff00+((IO_SCRATCH_PAD_1        & 0xFC00) >> 8) + (IO_SCRATCH_PAD_1        & 1)
#define MM_SHADOW_SET           0x3fff00+((IO_SHADOW_SET           & 0xFC00) >> 8) + (IO_SHADOW_SET           & 1)
#define MM_MEM_CFG              0x3fff00+((IO_MEM_CFG              & 0xFC00) >> 8) + (IO_MEM_CFG              & 1)
#define MM_EXT_GE_STATUS        0x3fff00+((IO_EXT_GE_STATUS        & 0xFC00) >> 8) + (IO_EXT_GE_STATUS        & 1)
#define MM_HORZ_OVERSCAN        0x3fff00+((IO_HORZ_OVERSCAN        & 0xFC00) >> 8) + (IO_HORZ_OVERSCAN        & 1)
#define MM_VERT_OVERSCAN        0x3fff00+((IO_VERT_OVERSCAN        & 0xFC00) >> 8) + (IO_VERT_OVERSCAN        & 1)
#define MM_MAX_WAITSTATES       0x3fff00+((IO_MAX_WAITSTATES       & 0xFC00) >> 8) + (IO_MAX_WAITSTATES       & 1)
#define MM_GE_OFFSET_LO         0x3fff00+((IO_GE_OFFSET_LO         & 0xFC00) >> 8) + (IO_GE_OFFSET_LO         & 1)
#define MM_BOUNDS_LEFT          0x3fff00+((IO_BOUNDS_LEFT          & 0xFC00) >> 8) + (IO_BOUNDS_LEFT          & 1)
#define MM_GE_OFFSET_HI         0x3fff00+((IO_GE_OFFSET_HI         & 0xFC00) >> 8) + (IO_GE_OFFSET_HI         & 1)
#define MM_BOUNDS_TOP           0x3fff00+((IO_BOUNDS_TOP           & 0xFC00) >> 8) + (IO_BOUNDS_TOP           & 1)
#define MM_GE_PITCH             0x3fff00+((IO_GE_PITCH             & 0xFC00) >> 8) + (IO_GE_PITCH             & 1)
#define MM_BOUNDS_RIGHT         0x3fff00+((IO_BOUNDS_RIGHT         & 0xFC00) >> 8) + (IO_BOUNDS_RIGHT         & 1)
#define MM_EXT_GE_CONFIG        0x3fff00+((IO_EXT_GE_CONFIG        & 0xFC00) >> 8) + (IO_EXT_GE_CONFIG        & 1)
#define MM_BOUNDS_BOTTOM        0x3fff00+((IO_BOUNDS_BOTTOM        & 0xFC00) >> 8) + (IO_BOUNDS_BOTTOM        & 1)
#define MM_MISC_CNTL            0x3fff00+((IO_MISC_CNTL            & 0xFC00) >> 8) + (IO_MISC_CNTL            & 1)
#define MM_PATT_DATA_INDEX      0x3fff00+((IO_PATT_DATA_INDEX      & 0xFC00) >> 8) + (IO_PATT_DATA_INDEX      & 1)
#define MM_PATT_DATA            0x3fff00+((IO_PATT_DATA            & 0xFC00) >> 8) + (IO_PATT_DATA            & 1)
#define MM_R_EXT_GE_CONFIG      0x3fff00+((IO_R_EXT_GE_CONFIG      & 0xFC00) >> 8) + (IO_R_EXT_GE_CONFIG      & 1)
#define MM_R_MISC_CNTL          0x3fff00+((IO_R_MISC_CNTL          & 0xFC00) >> 8) + (IO_R_MISC_CNTL          & 1)
#define MM_BRES_COUNT           0x3fff00+((IO_BRES_COUNT           & 0xFC00) >> 8) + (IO_BRES_COUNT           & 1)
#define MM_EXT_FIFO_STATUS      0x3fff00+((IO_EXT_FIFO_STATUS      & 0xFC00) >> 8) + (IO_EXT_FIFO_STATUS      & 1)
#define MM_LINEDRAW_INDEX       0x3fff00+((IO_LINEDRAW_INDEX       & 0xFC00) >> 8) + (IO_LINEDRAW_INDEX       & 1)
#define MM_LINEDRAW_OPT         0x3fff00+((IO_LINEDRAW_OPT         & 0xFC00) >> 8) + (IO_LINEDRAW_OPT         & 1)
#define MM_DEST_X_START         0x3fff00+((IO_DEST_X_START         & 0xFC00) >> 8) + (IO_DEST_X_START         & 1)
#define MM_DEST_X_END           0x3fff00+((IO_DEST_X_END           & 0xFC00) >> 8) + (IO_DEST_X_END           & 1)
#define MM_DEST_Y_END           0x3fff00+((IO_DEST_Y_END           & 0xFC00) >> 8) + (IO_DEST_Y_END           & 1)
#define MM_R_H_TOTAL            0x3fff00+((IO_R_H_TOTAL            & 0xFC00) >> 8) + (IO_R_H_TOTAL            & 1)
#define MM_R_H_DISP             0x3fff00+((IO_R_H_DISP             & 0xFC00) >> 8) + (IO_R_H_DISP             & 1)
#define MM_SRC_X_START          0x3fff00+((IO_SRC_X_START          & 0xFC00) >> 8) + (IO_SRC_X_START          & 1)
#define MM_ALU_BG_FN            0x3fff00+((IO_ALU_BG_FN            & 0xFC00) >> 8) + (IO_ALU_BG_FN            & 1)
#define MM_R_H_SYNC_STRT        0x3fff00+((IO_R_H_SYNC_STRT        & 0xFC00) >> 8) + (IO_R_H_SYNC_STRT        & 1)
#define MM_ALU_FG_FN            0x3fff00+((IO_ALU_FG_FN            & 0xFC00) >> 8) + (IO_ALU_FG_FN            & 1)
#define MM_R_H_SYNC_WID         0x3fff00+((IO_R_H_SYNC_WID         & 0xFC00) >> 8) + (IO_R_H_SYNC_WID         & 1)
#define MM_SRC_X_END            0x3fff00+((IO_SRC_X_END            & 0xFC00) >> 8) + (IO_SRC_X_END            & 1)
#define MM_SRC_Y_DIR            0x3fff00+((IO_SRC_Y_DIR            & 0xFC00) >> 8) + (IO_SRC_Y_DIR            & 1)
#define MM_R_V_TOTAL            0x3fff00+((IO_R_V_TOTAL            & 0xFC00) >> 8) + (IO_R_V_TOTAL            & 1)
#define MM_EXT_SSV              0x3fff00+((IO_EXT_SSV              & 0xFC00) >> 8) + (IO_EXT_SSV              & 1)
#define MM_EXT_SHORT_STROKE     0x3fff00+((IO_EXT_SHORT_STROKE     & 0xFC00) >> 8) + (IO_EXT_SHORT_STROKE     & 1)
#define MM_R_V_DISP             0x3fff00+((IO_R_V_DISP             & 0xFC00) >> 8) + (IO_R_V_DISP             & 1)
#define MM_SCAN_X               0x3fff00+((IO_SCAN_X               & 0xFC00) >> 8) + (IO_SCAN_X               & 1)
#define MM_R_V_SYNC_STRT        0x3fff00+((IO_R_V_SYNC_STRT        & 0xFC00) >> 8) + (IO_R_V_SYNC_STRT        & 1)
#define MM_DP_CONFIG            0x3fff00+((IO_DP_CONFIG            & 0xFC00) >> 8) + (IO_DP_CONFIG            & 1)
#define MM_VERT_LINE_CNTR       0x3fff00+((IO_VERT_LINE_CNTR       & 0xFC00) >> 8) + (IO_VERT_LINE_CNTR       & 1)
#define MM_PATT_LENGTH          0x3fff00+((IO_PATT_LENGTH          & 0xFC00) >> 8) + (IO_PATT_LENGTH          & 1)
#define MM_R_V_SYNC_WID         0x3fff00+((IO_R_V_SYNC_WID         & 0xFC00) >> 8) + (IO_R_V_SYNC_WID         & 1)
#define MM_PATT_INDEX           0x3fff00+((IO_PATT_INDEX           & 0xFC00) >> 8) + (IO_PATT_INDEX           & 1)
#define MM_EXT_SCISSOR_L        0x3fff00+((IO_EXT_SCISSOR_L        & 0xFC00) >> 8) + (IO_EXT_SCISSOR_L        & 1)
#define MM_R_SRC_X              0x3fff00+((IO_R_SRC_X              & 0xFC00) >> 8) + (IO_R_SRC_X              & 1)
#define MM_EXT_SCISSOR_T        0x3fff00+((IO_EXT_SCISSOR_T        & 0xFC00) >> 8) + (IO_EXT_SCISSOR_T        & 1)
#define MM_R_SRC_Y              0x3fff00+((IO_R_SRC_Y              & 0xFC00) >> 8) + (IO_R_SRC_Y              & 1)
#define MM_EXT_SCISSOR_R        0x3fff00+((IO_EXT_SCISSOR_R        & 0xFC00) >> 8) + (IO_EXT_SCISSOR_R        & 1)
#define MM_EXT_SCISSOR_B        0x3fff00+((IO_EXT_SCISSOR_B        & 0xFC00) >> 8) + (IO_EXT_SCISSOR_B        & 1)
#define MM_SRC_CMP_COLOR        0x3fff00+((IO_SRC_CMP_COLOR        & 0xFC00) >> 8) + (IO_SRC_CMP_COLOR        & 1)
#define MM_DEST_CMP_FN          0x3fff00+((IO_DEST_CMP_FN          & 0xFC00) >> 8) + (IO_DEST_CMP_FN          & 1)
#define MM_EXT_CUR_Y            0x3fff00+((IO_EXT_CUR_Y            & 0xFC00) >> 8) + (IO_ASIC_ID              & 1)
#define MM_ASIC_ID              0x3fff00+((IO_ASIC_ID              & 0xFC00) >> 8) + (IO_ASIC_ID              & 1)
#define MM_LINEDRAW             0x3fff00+((IO_LINEDRAW             & 0xFC00) >> 8) + (IO_LINEDRAW             & 1)
#define MM__PAR_FIFO_DATA       0x3fff00+((IO__PAR_FIFO_DATA       & 0xFC00) >> 8) + (IO__PAR_FIFO_DATA       & 1)
#define MM__PAR_FIFO_ADDR       0x3fff00+((IO__PAR_FIFO_ADDR       & 0xFC00) >> 8) + (IO__PAR_FIFO_ADDR       & 1)
#define MM__MAJOR_DEST_CNT      0x3fff00+((IO__MAJOR_DEST_CNT      & 0xFC00) >> 8) + (IO__MAJOR_DEST_CNT      & 1)
#define MM__MAJOR_SRC_CNT       0x3fff00+((IO__MAJOR_SRC_CNT       & 0xFC00) >> 8) + (IO__MAJOR_SRC_CNT       & 1)
#define MM__MINOR_DEST_CNT      0x3fff00+((IO__MINOR_DEST_CNT      & 0xFC00) >> 8) + (IO__MINOR_DEST_CNT      & 1)
#define MM__MINOR_SRC_CNT       0x3fff00+((IO__MINOR_SRC_CNT       & 0xFC00) >> 8) + (IO__MINOR_SRC_CNT       & 1)
#define MM__HW_TEST             0x3fff00+((IO__HW_TEST             & 0xFC00) >> 8) + (IO__HW_TEST             & 1)
                                                                                                            
/* */
/* */
/*--------------------------------------------------------- */
/* */
/*Following are the FIFO checking macros: */
/* */
#define ONE_WORD             0x8000 
#define TWO_WORDS            0xC000 
#define THREE_WORDS          0xE000 
#define FOUR_WORDS           0xF000 
#define FIVE_WORDS           0xF800 
#define SIX_WORDS            0xFC00 
#define SEVEN_WORDS          0xFE00 
#define EIGHT_WORDS          0xFF00 
#define NINE_WORDS           0xFF80 
#define TEN_WORDS            0xFFC0 
#define ELEVEN_WORDS         0xFFE0 
#define TWELVE_WORDS         0xFFF0 
#define THIRTEEN_WORDS       0xFFF8 
#define FOURTEEN_WORDS       0xFFFC 
#define FIFTEEN_WORDS        0xFFFE 
#define SIXTEEN_WORDS        0xFFFF 
/* */
/* */
/* */
/*--------------------------------------- */

/* */
/* */
/* Draw Command (IBM 8514 compatible CMD register) */
/* */
/* opcode field */
#define OP_CODE              0xE000 
#define SHIFT_op_code        0x000D 
#define DRAW_SETUP           0x0000 
#define DRAW_LINE            0x2000 
#define FILL_RECT_H1H4       0x4000 
#define FILL_RECT_V1V2       0x6000 
#define FILL_RECT_V1H4       0x8000 
#define DRAW_POLY_LINE       0xA000 
#define BITBLT_OP            0xC000 
#define DRAW_FOREVER         0xE000 
/* swap field */
#define LSB_FIRST            0x1000 
/* data width field */
#define DATA_WIDTH           0x0200 
#define BIT16                0x0200 
#define BIT8                 0x0000 
/* CPU wait field */
#define CPU_WAIT             0x0100 
/* octant field */
#define OCTANT               0x00E0 
#define SHIFT_octant         0x0005 
#define YPOSITIVE            0x0080 
#define YMAJOR               0x0040 
#define XPOSITIVE            0x0020 
/* draw field */
#define DRAW                 0x0010 
/* direction field */
#define DIR_TYPE             0x0008 
#define DEGREE               0x0008 
#define XY                   0x0000 
#define RECT_RIGHT_AND_DOWN  0x00E0 /* quadrant 3 */
#define RECT_LEFT_AND_UP     0x0000 /* quadrant 1 */
/* last pel off field */
#define SHIFT_last_pel_off   0x0002 
#define LAST_PEL_OFF         0x0004 
#define LAST_PEL_ON          0x0000 
#define LAST_PIXEL_OFF       0x0004
#define LAST_PIXEL_ON        0x0000
#define MULTIPLE_PIXELS      0x0002
#define SINGLE_PIXEL         0x0000

/* pixel mode */
#define PIXEL_MODE           0x0002 
#define MULTI                0x0002 
#define SINGLE               0x0000 
/* read/write */
#define RW                   0x0001 
#define WRITE                0x0001 
#define READ                 0x0000 
/* */
/* --------------------------------------------------------- */
/* */


/* */
/* GE_STAT (9AE8) is set if the engine is busy. */
/* */
#define HARDWARE_BUSY 0x200

/* */
/* Extended Graphics Engine Status (EXT_GE_STATUS) */
/* */
#define POINTS_INSIDE        0x8000 
#define EE_DATA_IN           0x4000 
#define GE_ACTIVE            0x2000 
#define CLIP_ABOVE           0x1000 
#define CLIP_BELOW           0x0800 
#define CLIP_LEFT            0x0400 
#define CLIP_RIGHT           0x0200 
#define CLIP_FLAGS           0x1E00 
#define CLIP_INSIDE          0x0100 
#define EE_CRC_VALID         0x0080 
#define CLIP_OVERRUN         0x000F 
/* */
/* Datapath Configuration Register (DP_CONFIG)  */
#define FG_COLOR_SRC         0xE000 
#define SHIFT_fg_color_src   0x000D 
#define DATA_ORDER           0x1000 
#define DATA_WIDTH           0x0200 
#define BG_COLOR_SRC         0x0180 
#define SHIFT_bg_color_src   0x0007 
#define EXT_MONO_SRC         0x0060 
#define SHIFT_ext_mono_src   0x0005 
#define DRAW                 0x0010 
#define READ_MODE            0x0004 
#define POLY_FILL_MODE       0x0002 
#define SRC_SWAP             0x0800 
/* */
#define FG_COLOR_SRC_BG      0x0000 /* Background Color Register */
#define FG_COLOR_SRC_FG      0x2000 /* Foreground Color Register */
#define FG_COLOR_SRC_HOST    0x4000 /* CPU Data Transfer Reg */
#define FG_COLOR_SRC_BLIT    0x6000 /* VRAM blit source */
#define FG_COLOR_SRC_GS      0x8000 /* Grey-scale mono blit */
#define FG_COLOR_SRC_PATT    0xA000 /* Color Pattern Shift Reg */
#define FG_COLOR_SRC_CLUH    0xC000 /* Color lookup of Host Data */
#define FG_COLOR_SRC_CLUB    0xE000 /* Color lookup of blit src */
/* */
#define BG_COLOR_SRC_BG      0x0000 /* Background Color Reg */
#define BG_COLOR_SRC_FG      0x0080 /* Foreground Color Reg */
#define BG_COLOR_SRC_HOST    0x0100 /* CPU Data Transfer Reg */
#define BG_COLOR_SRC_BLIT    0x0180 /* VRAM blit source */

/* */
/* Note that "EXT_MONO_SRC" and "MONO_SRC" are mutually destructive, but that */
/* "EXT_MONO_SRC" selects the ATI pattern registers. */
/* */
#define EXT_MONO_SRC_ONE     0x0000 /* Always '1' */
#define EXT_MONO_SRC_PATT    0x0020 /* ATI Mono Pattern Regs */
#define EXT_MONO_SRC_HOST    0x0040 /* CPU Data Transfer Reg */
#define EXT_MONO_SRC_BLIT    0x0060 /* VRAM Blit source plane */

/* */
/* Linedraw Options Register (LINEDRAW_OPT)  */
/* */
#define CLIP_MODE            0x0600 
#define SHIFT_clip_mode      0x0009 
#define CLIP_MODE_DIS        0x0000 
#define CLIP_MODE_LINE       0x0200 
#define CLIP_MODE_PLINE      0x0400 
#define CLIP_MODE_PATT       0x0600 
#define BOUNDS_RESET         0x0100 
#define OCTANT               0x00E0 
#define SHIFT_ldo_octant     0x0005 
#define YDIR                 0x0080 
#define XMAJOR               0x0040 
#define XDIR                 0x0020 
#define DIR_TYPE             0x0008 
#define DIR_TYPE_DEGREE      0x0008 
#define DIR_TYPE_OCTANT      0x0000 
#define LAST_PEL_OFF         0x0004 
#define POLY_MODE            0x0002 
/* */
/* */

