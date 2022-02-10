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
 * @(#)$RCSfile: sim_pza.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1995/08/21 12:24:57 $
 */

/* 
 * Define a half a second minimum wait time after setting the MIN bit.
 * This value might have to be changed if the testing proves that it is
 * not enough.
 */
#define PZA_MIN_WAIT_TIME	500000
#define PZA_MAX_WAIT_TIME	2000000
#define PZA_MIN_WAIT_CNT	5
#define PZA_MAX_WAIT_CNT	20      /* 2 seconds */
#define PZA_CDB_MAX_LEN		12

#define PZA_RESET_START_OFFSET	0x0000000CL
#define PZA_ASRCR_OFFSET	0x00000300L

#define AMCSR_LO_OFFSET		0x00000100L      
#define AMCSR_HI_OFFSET		0x00000104L      
#define ABBR_LO_OFFSET		0x00000108L           
#define ABBR_HI_OFFSET		0x0000010CL   
#define DAFQIR_LO_OFFSET	0x00000110L      
#define DAFQIR_HI_OFFSET	0x00000114L     
#define DACQIR_LO_OFFSET	0x00000118L      
#define DACQIR_HI_OFFSET	0x0000011cL      
#define ASR_LO_OFFSET		0x00000140L     
#define ASR_HI_OFFSET		0x00000144L      
#define AFAR_LO_OFFSET		0x00000148L     
#define AFAR_HI_OFFSET		0x0000014CL    
#define AFPR_LO_OFFSET		0x00000150L    
#define AFPR_HI_OFFSET		0x00000154L     
#define ERR_LOG_1_OFFSET	0x000001C0L
#define ERR_LOG_2_OFFSET	0x000001C4L
#define ERR_LOG_3_OFFSET	0x000001C8L
#define ERR_LOG_4_OFFSET	0x000001CCL
#define ERR_LOG_5_OFFSET	0x000001D0L
#define ERR_LOG_6_OFFSET	0x000001D4L
#define ERR_LOG_7_OFFSET	0x000001D8L
#define ERR_LOG_8_OFFSET	0x000001DCL
#define ERR_LOG_9_OFFSET	0x000001E0L
#define ERR_LOG_A_OFFSET	0x000001E4L

typedef struct pza_regs {
    vm_offset_t amcsr_lo;	/* Adapter Maintenance Control and Staus */
    vm_offset_t amcsr_hi;
    vm_offset_t abbr_lo;    	/* Adatper Block Base Register */
    vm_offset_t abbr_hi;
    vm_offset_t dafqir_lo; 	/* Driver-Adapter Free Queue IR */
    vm_offset_t dafqir_hi;
    vm_offset_t dacqir_lo; 	/* Driver-Adapter Command Queue IR */
    vm_offset_t dacqir_hi;
    vm_offset_t asr_lo;		/* Adapter Status Register */
    vm_offset_t asr_hi;
    vm_offset_t afar_lo;	/* Adapter Falling Address Register */
    vm_offset_t afar_hi;
    vm_offset_t afpr_lo;	/* Adapter Falling Parameter Register */
    vm_offset_t afpr_hi;
    vm_offset_t asrcr;		/* Adapter Status Release Control Register */
    vm_offset_t reset_start;
} PZA_REGS;

/*
 * Bits in the PCI Status register which we care about.
 */
#define PCI_STATUS_ERROR (STAT_DATA_PAR | STAT_SIG_TARG_ABRT | STAT_RCVD_TARG_ABRT | STAT_RCVD_MSTR_ABRT | STAT_SIG_SYS_ERR | STAT_DET_PAR_ERR)
