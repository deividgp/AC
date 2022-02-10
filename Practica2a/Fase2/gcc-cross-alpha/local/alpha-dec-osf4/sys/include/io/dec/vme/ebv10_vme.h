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
 *
 * History from when the file was arch/alpha/hal/ebv10_vme.h 
 *
 * Revision 1.1.2.3  1994/07/29  14:05:09  Bruce_Hansen
 * 	Removed software callback vectors for VMEbus Iack Interrupts.
 * 	Changed minimum PAS* deassertion value.
 * 	[1994/07/27  05:24:51  Bruce_Hansen]
 *
 * Revision 1.1.2.2  1994/06/28  22:16:09  Bruce_Hansen
 * 	Added definitions for mask and switched vic_btlr0 and vic_btlr1 register
 * 	offsets within structure ebv10_vme_io_handles.
 * 	[1994/06/27  23:42:18  Bruce_Hansen]
 * 
 * 	Definition file for VME on the AXPVME64 platform.
 * 	[1994/06/23  15:52:29  Bruce_Hansen]
 * 
 */
/*
 * @(#)$RCSfile: ebv10_vme.h,v $ $Revision: 1.1.16.2 $ (DEC) $Date: 1998/10/30 18:44:00 $
 */

#ifndef _EBV10_VME_H 
#define _EBV10_VME_H 

#include <hal/ebv10.h>
#include <io/dec/vme/vbareg.h>
#include <machine/scb.h>
#include <kern/event.h>

#define	Regptr	((struct ebv10_vme_io_handles *)(vhp->adapt_regs))
#define	Varptr	((struct ebv10_vme_vars *)(vhp->adapt_vars))
#define Busvars ((struct ebv10_vme_busvars *)(vhp->bus_vars))

/****************************************************************************
 *
 *  The following structure is used to customize various VMEbus
 *  configurable parameters. Care should be taken when changing
 *  the default values provided in file ebv10_vme_data.c. The values
 *  for each element follows the data structure.
 *
 ***************************************************************************/

struct	ebv10_vme_data {
  int            vme_brl;           /* VMEbus request level (ARCR)         */
  int            arb_mode;          /* VIC aribitration mode (ARCR)        */
  int            fairness_to;       /* VMEbus fair requester timer (ARCR)  */
  int            local_bus_to;      /* Local bus timeout period (TTR)      */
  int            vmebus_arb_to;     /* VMEbus timeout period (TTR)         */
  int            rel_mode;          /* VMEbus release mode VME_ROR/VME_RWD */
  int            syscon;            /* System controller specification     */
  int            vme_ovrlap;        /* Over map A24/A32 address space      */
  int            vme_wrtpost;       /* Enable/disable VIC write posting    */
  int            dma_intrlv;        /* MBLT DMA interleave gap (x*250ns)   */
  int            limit_dma_rd;      /* MBLT limit DMA reads to 8kb if = 1  */
  int            limit_dma_wrt;     /* MBLT limit DMA writes to 8kb if = 1 */
  int            force_hw_dma;      /* SMP force h/w DMA engine for MBLTs  */ 
  unsigned int   a32_ib_base;       /* A32 inbound DMA window base address */
  unsigned int   a32_ib_size;       /* 0=128mb, 1=64mb, 2=32mb & 3=16mb    */
  unsigned int   a24_ib_base;       /* A24 inbound DMA window base address */
  unsigned int   a24_ib_size;       /* 0=16mb, 1=8mb, 2=4mb, 3=2mb, 4=1mb  */
                                    /* 5=512kb 6=256kb, 7=128kb & 8=64kb   */
  unsigned int   icf_base;          /* Interprocessor Communication Facil- */
                                    /* ities base address. 256b boundries  */
  unsigned int   icf_mask;          /* ICF mask - typically set to 0       */
  int            irq_to_spl_tbl[8]; /* VME IRQ to system IPL mapping       */
  int            adapt_blk_spl;     /* Adapter resource blocking SPL       */
  int            adapt_mblt_access; /* Adapter MBLT access (sparse/dense)  */
};

/*
 *  User specified values for VMEbus requesy level (vme_brl) (ARCR register)
 */
#define VME_BR0        0x00     /* VMEbus Request Level BR0                  */
#define VME_BR1        0x01     /* VMEbus Request Level BR1                  */
#define VME_BR2        0x02     /* VMEbus Request Level BR2                  */
#define VME_BR3        0x03     /* VMEbus Request Level BR3 (default)        */
#define VME_BRLV_MASK  0x03

/*
 *  User specified values for arbitration mode. Only applicable for the
 *  system controller (ARCR register)
 */
#define VME_ARB_PRIO   0x01     /* VIC performs priority VMEbus arbitration  */
#define VME_ARB_RR     0x00     /* VIC performs round-robin arbitration      */

/*
 *  User specified values for Aribiter/Requester fairness (ARCR register)
 */
#define VME_FRTO_DSABL 0x00     /* Fairness disabled (default)       */
#define VME_FRTO_2US   0x01     /* Fair Request Timeout = 2us        */
#define VME_FRTO_4US   0x02     /* Fair Request Timeout = 4us        */
#define VME_FRTO_6US   0x03     /* Fair Request Timeout = 6us        */
#define VME_FRTO_8US   0x04     /* Fair Request Timeout = 8us        */
#define VME_FRTO_10US  0x05     /* Fair Request Timeout = 10us       */
#define VME_FRTO_12US  0x06     /* Fair Request Timeout = 12us       */
#define VME_FRTO_14US  0x07     /* Fair Request Timeout = 14us       */
#define VME_FRTO_16US  0x08     /* Fair Request Timeout = 16us       */
#define VME_FRTO_18US  0x09     /* Fair Request Timeout = 18us       */
#define VME_FRTO_20US  0x0A     /* Fair Request Timeout = 20us       */
#define VME_FRTO_22US  0x0B     /* Fair Request Timeout = 22us       */
#define VME_FRTO_24US  0x0C     /* Fair Request Timeout = 24us       */
#define VME_FRTO_26US  0x0D     /* Fair Request Timeout = 26us       */
#define VME_FRTO_28US  0x0E     /* Fair Request Timeout = 28us       */
#define VME_FRTO_NONE  0x0F     /* Fair Request Tiemout = none       */
#define VME_FRTO_MASK  0x0F

/*
 *  User specified Values for the Transfer Timeout Register
 *     local bus acquisition timeout
 *     VMEbus arbitration timeout
 */
#define VME_BUSTO_4US    0x00   /* 4 microseconds                        */
#define VME_BUSTO_16US   0x01   /* 16 microseconds                       */
#define VME_BUSTO_32US   0x02   /* 32 microseconds (default)             */
#define VME_BUSTO_64US   0x03   /* 64 microseconds                       */
#define VME_BUSTO_128US  0x04   /* 128 microseconds                      */
#define VME_BUSTO_256US  0x05   /* 256 microseconds                      */
#define VME_BUSTO_512US  0x06   /* 512 microseconds                      */
#define VME_BUSTO_DISABL 0x07   /* timeouts disabled                     */
#define VME_BUSTO_MASK   0x07

/*
 *  User specified Release modes for Release Control Register
 */
#define VME_ROR         0       /* ROR Release-On-Request                    */
#define VME_RWD         1       /* RWD Release-When-Done                     */
#define VME_RM_MSK      1

/*
 *  User specified value to enable/disable issuing of VMEbus RESETS from
 *  the sytem controller during autoconfiguration.
 */

#define VME_SYS_CONTROLLER   1  /* VMEbus adapter is the system controller   */
#define VME_NOSYS_CONTROLLER 0  /* VMEbus adpater is NOT system controller   */

#define VME_WRT_POST_ENABL   1  /* Enable  VME Master Write Post             */
#define VME_WRT_POST_DSABL   0  /* Disable VME Master Write Post             */

#define VME_DMA_RD_ALL       0   /* No DMA read Limit                        */
#define VME_DMA_RD_LMT       1   /* Limit DMA reads to 8kb or Less           */

#define VME_DMA_WRT_ALL      0   /* No DMA write Limit                       */
#define VME_DMA_WRT_LMT      1   /* Limit DMA writes to 8kb or Less          */

#define VME_SMP_DSBL_HW_DMA  0   /* SMP - use emulated DMA                   */
#define VME_SMP_ENBL_HW_DMA  1   /* Force HW MBLT ON SMP SYSTEM              */

/*
 * DMA interleave selection to control the Master Block Transfer DMA
 * interleave gap. The default value is 15 to provide the maximum
 * interleave gap. This value was selected to allow PIO operations
 * and VME IACK cycles to occur during the DMA interleave gap. As this
 * value is decreased, PIO and IACK cycles may be held off until the
 * Master Block Transfer DMA has completed.
 */

#define VME_DMA_INTRLV_15    15         /* 15 * 250ns = approximately 3.75us */
#define VME_DMA_INTRLV_14    14         /* 14 * 250ns = approximately 3.50us */
#define VME_DMA_INTRLV_13    13         /* 13 * 250ns = approximately 3.25us */
#define VME_DMA_INTRLV_12    12         /* 12 * 250ns = approximately 3.00us */
#define VME_DMA_INTRLV_11    11         /* 11 * 250ns = approximately 2.75us */
#define VME_DMA_INTRLV_10    10         /* 10 * 250ns = approximately 2.50us */
#define VME_DMA_INTRLV_9      9         /*  9 * 250ns = approximately 2.25us */
#define VME_DMA_INTRLV_8      8         /*  8 * 250ns = approximately 2.00us */
#define VME_DMA_INTRLV_7      7         /*  7 * 250ns = approximately 1.75us */
#define VME_DMA_INTRLV_6      6         /*  6 * 250ns = approximately 1.50us */
#define VME_DMA_INTRLV_5      5         /*  5 * 250ns = approximately 1.25us */
#define VME_DMA_INTRLV_4      4         /*  4 * 250ns = approximately 1.00us */
#define VME_DMA_INTRLV_3      3         /*  3 * 250ns = approximately 0.75us */
#define VME_DMA_INTRLV_2      2         /*  2 * 250ns = approximately 0.50us */
#define VME_DMA_INTRLV_1      1         /*  1 * 250ns = approximately 0.25us */
#define VME_DMA_INTRLV_0      0         /*  0 * 250ns = approximately 0.00us */
#define VME_DMA_INTRLV_MSK   15

/*
 *  User specified value to specify whether A24 and A32 addresses can reside
 *  within the same addressing range or they must be unique.
 */
#define VME_A24_A32_OVRLAP  1   /* A24 & A32 addresses can overlap each other*/
#define VME_A24_A32_UNIQUE  0   /* A24 & A32 addresses must be unique        */

/*
 *  User specified values for DMA inbound window sizes in kb
 */
#define VME_SZ_64_KB         0x10000 /*    64kb          */
#define VME_SZ_128_KB        0x20000 /*   128kb          */
#define VME_SZ_256_KB        0x40000 /*   256kb          */
#define VME_SZ_512_KB        0x80000 /*   512kb          */
#define VME_SZ_1024_KB      0x100000 /*   1024kb   - 1mb */
#define VME_SZ_2048_KB      0x200000 /*   2048kb   - 2mb */
#define VME_SZ_4096_KB      0x400000 /*   4096kb   - 4mb */
#define VME_SZ_8192_KB      0x800000 /*   8192kb   - 8mb */
#define VME_SZ_16384_KB    0x1000000 /*  16384kb  - 16mb */
#define VME_SZ_32768_KB    0x2000000 /*  32768kb  - 32mb */
#define VME_SZ_65536_KB    0x4000000 /*  65536kb  - 64mb */
#define VME_SZ_131072_KB   0x8000000 /* 131072kb - 128mb */

#define VME_SZ_SXTNTH_MB VME_SZ_64_KB
#define VME_SZ_EGHTH_MB  VME_SZ_128_KB
#define VME_SZ_QRTR_MB   VME_SZ_256_KB
#define VME_SZ_HALF_MB   VME_SZ_512_KB
#define VME_SZ_1_MB      VME_SZ_1024_KB
#define VME_SZ_2_MB      VME_SZ_2048_KB
#define VME_SZ_4_MB      VME_SZ_4096_KB
#define VME_SZ_8_MB      VME_SZ_8192_KB
#define VME_SZ_16_MB     VME_SZ_16384_KB
#define VME_SZ_32_MB     VME_SZ_32768_KB
#define VME_SZ_64_MB     VME_SZ_65536_KB
#define VME_SZ_128_MB    VME_SZ_131072_KB

/*
 * hardware interrupt enable/disable masks
 */

#define	VP_INTR_ALL       EBV10_INTR_ALL        /* all hardware interrupts */

#define	VP_INTR_VME_RESET EBV10_INTR_VME_RESET     /* reset */
#define	VP_INTR_AUTO_IRQ1 EBV10_INTR_AUTO_IRQ1     /* auto irq1 */
#define	VP_INTR_AUTO_IRQ2 EBV10_INTR_AUTO_IRQ2     /* auto irq2 */
#define	VP_INTR_AUTO_IRQ3 EBV10_INTR_AUTO_IRQ3     /* auto irq3 */
#define	VP_INTR_AUTO_IRQ4 EBV10_INTR_AUTO_IRQ4     /* auto irq4 */
#define	VP_INTR_AUTO_IRQ5 EBV10_INTR_AUTO_IRQ5     /* auto irq5 */
#define	VP_INTR_AUTO_IRQ6 EBV10_INTR_AUTO_IRQ6     /* auto irq6 */
#define	VP_INTR_AUTO_IRQ7 EBV10_INTR_AUTO_IRQ7     /* auto irq7 */

#define	VP_INTR_LOC_MONITOR EBV10_INTR_LOC_MONITOR /* loc mon */
#define	VP_INTR_VIP_ERR     EBV10_INTR_VIP_ERR     /* vip err */

#define	VP_INTR_VME_IRQ1    EBV10_INTR_VME_IRQ1    /* irq1 */
#define	VP_INTR_VME_IRQ2    EBV10_INTR_VME_IRQ2    /* irq2 */
#define	VP_INTR_VME_IRQ3    EBV10_INTR_VME_IRQ3    /* irq3 */
#define	VP_INTR_VME_IRQ4    EBV10_INTR_VME_IRQ4    /* irq4 */
#define	VP_INTR_VME_IRQ5    EBV10_INTR_VME_IRQ5    /* irq5 */
#define	VP_INTR_VME_IRQ6    EBV10_INTR_VME_IRQ6    /* irq6 */
#define	VP_INTR_VME_IRQ7    EBV10_INTR_VME_IRQ7    /* irq7 */

#define	VP_INTR_VME_DMA     EBV10_INTR_VME_DMA     /* dma  */
#define	VP_INTR_VME_IACK    EBV10_INTR_VME_IACK    /* iack */

#define	VP_INTR_VIC_SYSFAIL EBV10_INTR_VIC_SYSFAIL /* sysfail */
#define	VP_INTR_VIC_ARBTO   EBV10_INTR_VIC_ARBTO   /* arb to  */
#define	VP_INTR_VIC_WPFAIL  EBV10_INTR_VIC_WPFAIL  /* wrt post*/
#define	VP_INTR_VIC_ACFAIL  EBV10_INTR_VIC_ACFAIL  /* a/c fail*/

#define	VP_INTR_VME_ICMS0   EBV10_INTR_VME_ICMS0   /* local  0 */
#define	VP_INTR_VME_ICMS1   EBV10_INTR_VME_ICMS1   /* local  1 */
#define	VP_INTR_VME_ICMS2   EBV10_INTR_VME_ICMS2   /* local  2 */
#define	VP_INTR_VME_ICMS3   EBV10_INTR_VME_ICMS3   /* local  3 */

#define	VP_INTR_VME_ICGS0   EBV10_INTR_VME_ICGS0   /* global 0 */
#define	VP_INTR_VME_ICGS1   EBV10_INTR_VME_ICGS1   /* global 1 */
#define	VP_INTR_VME_ICGS2   EBV10_INTR_VME_ICGS2   /* global 2 */
#define	VP_INTR_VME_ICGS3   EBV10_INTR_VME_ICGS3   /* global 3 */

/******************************************************************************
 *
 *  This structure defines interrupt information for each i/o vector on VMEbus
 *
 *****************************************************************************/

struct ebv10_vme_intr_info {
  u_long (*intr)();   /* interrupt service routine   */ 
  u_long param;       /* interrupt service parameter */
  u_long mask;        /* hardware interrupt mask     */
  u_short vector;     /* i/o vector offset into scb  */
};

/*
 *  VME Adapter specific interrupt vector base register values
 */
#define LIRQ_BASE_VEC	    0x00  /* local IRQ1-IRQ 7 vector 0x1000  */
#define ERROR_BASE_VEC	    0x08  /* VIC,DMA,IACK     vector 0x1080  */
#define ICGS_BASE_VEC	    0x10  /* global switches  vector 0x1100  */
#define ICMS_BASE_VEC	    0x14  /* module switches  vector 0x1140  */

/*
 * VME adapter interrupt vector name and SCB vec location
 *
 *      VME_RESET_VEC      SCB VECTOR LOCATION 0x880
 *
 *      VME_IRQ1_AUTO_VEC  SCB VECTOR LOCATION 0x890
 *      VME_IRQ2_AUTO_VEC  SCB VECTOR LOCATION 0x8A0
 *      VME_IRQ3_AUTO_VEC  SCB VECTOR LOCATION 0x8B0
 *      VME_IRQ4_AUTO_VEC  SCB VECTOR LOCATION 0x8C0
 *      VME_IRQ5_AUTO_VEC  SCB VECTOR LOCATION 0x8D0
 *      VME_IRQ6_AUTO_VEC  SCB VECTOR LOCATION 0x8E0
 *      VME_IRQ7_AUTO_VEC  SCB VECTOR LOCATION 0x8F0
 *
 * 	VIP_LOC_MON_VEC	   SCB VECTOR LOCATION 0x1020
 * 	VIC_P_RT_TMR_VEC   SCB VECTOR LOCATION 0x1030
 * 	VIP_ERROR_VEC	   SCB VECTOR LOCATION 0x1070
 *
 *      VIC_ACFAIL_VEC	   SCB VECTOR LOCATION 0x1080
 *	VIC_WRITEPOST_VEC  SCB VECTOR LOCATION 0x1090
 *      VIC_ARBTIMEOUT_VEC SCB VECTOR LOCATION 0x10A0
 *      VIC_SYSFAIL_VEC	   SCB VECTOR LOCATION 0x10B0
 *      VME_IACK_VEC	   SCB VECTOR LOCATION 0x10C0
 *      DMA_STATUS_VEC	   SCB VECTOR LOCATION 0x10D0
 *
 *      ICF_GLBL_SW0_VEC   SCB VECTOR LOCATION 0x1100
 *      ICF_GLBL_SW1_VEC   SCB VECTOR LOCATION 0x1110
 *      ICF_GLBL_SW2_VEC   SCB VECTOR LOCATION 0x1120
 *      ICF_GLBL_SW3_VEC   SCB VECTOR LOCATION 0x1130
 *
 *      ICF_MOD_SW0_VEC	   SCB VECTOR LOCATION 0x1140
 *      ICF_MOD_SW1_VEC	   SCB VECTOR LOCATION 0x1150
 *      ICF_MOD_SW2_VEC	   SCB VECTOR LOCATION 0x1160
 *      ICF_MOD_SW3_VEC	   SCB VECTOR LOCATION 0X1170
 *
 *      VMEBUS VECTORS START - VECTOR LOCATION 0x1180
 *      VMEBUS VECTORS END   - VECTOR LOCATION 0x1FF0
 */

#define DEV_SCB_OFFSET     0x800

#define VME_RESET_VEC      (DEV_SCB_OFFSET + 0x80)   /* 0x880 */

#define VME_IRQ1_AUTO_VEC  (DEV_SCB_OFFSET + 0x90)   /* 0x890 */
#define VME_IRQ2_AUTO_VEC  (DEV_SCB_OFFSET + 0xA0)   /* 0x8A0 */
#define VME_IRQ3_AUTO_VEC  (DEV_SCB_OFFSET + 0xB0)   /* 0x8B0 */
#define VME_IRQ4_AUTO_VEC  (DEV_SCB_OFFSET + 0xC0)   /* 0x8C0 */
#define VME_IRQ5_AUTO_VEC  (DEV_SCB_OFFSET + 0xD0)   /* 0x8D0 */
#define VME_IRQ6_AUTO_VEC  (DEV_SCB_OFFSET + 0xE0)   /* 0x8E0 */
#define VME_IRQ7_AUTO_VEC  (DEV_SCB_OFFSET + 0xF0)   /* 0x8F0 */

#define VSCB_OFFSET        0x1000

#define	VIP_LOC_MON_VEC	  (VSCB_OFFSET + ((LIRQ_BASE_VEC | 2) * 16)) /*0x1020*/
#define	VIC_P_RT_TMR_VEC  (VSCB_OFFSET + ((LIRQ_BASE_VEC | 3) * 16)) /*0x1030*/
#define	VIP_ERROR_VEC	  (VSCB_OFFSET + ((LIRQ_BASE_VEC | 7) * 16)) /*0x1070*/

#define VIC_ACFAIL_VEC	  (VSCB_OFFSET + ((ERROR_BASE_VEC | 0) * 16))/*0x1080*/
#define	VIC_WRITEPOST_VEC (VSCB_OFFSET + ((ERROR_BASE_VEC | 1) * 16))/*0x1090*/
#define	VIC_ARBTIMEOUT_VEC (VSCB_OFFSET + ((ERROR_BASE_VEC | 2) * 16))/*0x10A0*/
#define	VIC_SYSFAIL_VEC	  (VSCB_OFFSET + ((ERROR_BASE_VEC | 3) * 16))/*0x10B0*/
#define	VME_IACK_VEC	  (VSCB_OFFSET + ((ERROR_BASE_VEC | 4) * 16))/*0x10C0*/
#define	DMA_STATUS_VEC	  (VSCB_OFFSET + ((ERROR_BASE_VEC | 5) * 16))/*0x10D0*/

#define	ICF_GLBL_SW0_VEC  (VSCB_OFFSET + ((ICGS_BASE_VEC | 0) * 16)) /*0x1100*/
#define	ICF_GLBL_SW1_VEC  (VSCB_OFFSET + ((ICGS_BASE_VEC | 1) * 16)) /*0x1110*/
#define	ICF_GLBL_SW2_VEC  (VSCB_OFFSET + ((ICGS_BASE_VEC | 2) * 16)) /*0x1120*/
#define	ICF_GLBL_SW3_VEC  (VSCB_OFFSET + ((ICGS_BASE_VEC | 3) * 16)) /*0x1130*/

#define	ICF_MOD_SW0_VEC	  (VSCB_OFFSET + ((ICMS_BASE_VEC | 0) * 16)) /*0x1140*/
#define	ICF_MOD_SW1_VEC	  (VSCB_OFFSET + ((ICMS_BASE_VEC | 1) * 16)) /*0x1150*/
#define	ICF_MOD_SW2_VEC	  (VSCB_OFFSET + ((ICMS_BASE_VEC | 2) * 16)) /*0x1160*/
#define	ICF_MOD_SW3_VEC	  (VSCB_OFFSET + ((ICMS_BASE_VEC | 3) * 16)) /*0x1170*/

#define VME_SCB_VEC_BASE (ICF_MOD_SW3_VEC + 16)    /* SCB OFFSET 0x1180 */

#define VME_MIN_VEC      ((VME_SCB_VEC_BASE - VSCB_OFFSET) / 16)
#define VME_MAX_VEC      255                      /* vec 0xFF SCB 0x1FF0 */

#define VME_MAX_SCB_VEC (((VME_MAX_VEC - VME_MIN_VEC) * 16) + VME_SCB_VEC_BASE)

/* VME scatter/gather (SG) mapping register totals                           */

#define VME_IB_A24_PMRCNT 	2048    /* 8kb  - 2048 maximum PMR's         */
#define VME_IB_A32_PMRCNT      16384    /* 64kb - 16384 maximum PMR's        */
#define VME_IB_PAGE_SIZE        8192    /* 8kb inbound PMR page size         */

#define VME_SP_OB_PMRCNT	256     /* 256 pmr's for 64mb sparse PCI mem */
#define VME_DN_OB_PMRCNT       1792     /* 1792 pmr's - 448mb dense PCI mem  */
#define VME_OB_PMRCNT_TOTAL    2048     /* 2k total outbound PMR's           */
#define VME_OB_PAGE_SIZE     262144     /* 256kb outbound page size          */

#define VIPVIC_PCI_SM_IB_A32_SG_OFFSET 0x00000000UL /* inbound 16K SG PMR's  */
#define VIPVIC_PCI_SM_IB_A24_SG_OFFSET 0x00010000UL /* inbound  2K SG PMR's  */

#define VIPVIC_PCI_SM_OB_SG_OFFSET_LOW 0x0001E000UL /* outbound 256 SG PMR's */
#define VIPVIC_PCI_SM_OB_SG_OFFSET_HGH 0x0001E400UL /* outbound 1792 SG PMR's*/

/* adapter specific structures */

/*
 *      hw_sg_table_control - one of these is kalloc'ed for each hw_sg_alloc.
 *      The address of this struct is placed in the private pointer in the
 *      overhead portion of the sglist. It holds the index of the allocated
 *      hardware scatter/gather entries, the number of entries allocated and
 *      the table base. The table base is used for comparision to make sure
 *      that system with multiple scatter/gather windows keep things sorted
 *      out.
 *
 *  struct hw_sg_table_control {
 *    u_int       index;           number of first s/g pmr allocated      
 *    u_int       num;             number of maps allocated               
 *    vm_offset_t table_base;      base of scatter/gather table           
 *    u_long      private_data;    used to store private data from sglist 
 *  };
 */

/*
 *      hw_sg_map_control - used to describe a scatter/gather map. It contains
 *      the bus base address of the window (phys_base), the pointer to the
 *      resource map (sg_rmap) and the address of the scatter/gather table.
 */
struct ebv10_vme_hw_sg_map_control {
  vm_offset_t  phys_base;      /* base address of DMA window or pio handle  */
  struct map   *sg_rmap;       /* Resource map that controls allocation     */
  io_handle_t  sg_table_base;  /* Address of in memory scatter/gather table */
};

struct ebv10_vme_pio_history {
  vme_atype_t    atype;        /* Requestor's atype flags                   */
  vme_addr_t     vme_addr;     /* Requestor's VMEbus address                */
  unsigned int   bcnt;         /* number of bytes requested to map          */
  io_handle_t    pio_ioh;      /* io_handle of the mapped PIO window        */
  io_handle_t    sg_ioh;       /* io_handle of 1st outbound sg map register */
  unsigned int   pmr_cnt;      /* number of outbound pmr's allocated        */
  unsigned int   reg_num;      /* number of first pmr allocated             */
  unsigned int   pmr_entry;    /* Contents of first PMR entry               */
};

struct ebv10_vme_vars {
  struct ebv10_vme_hw_sg_map_control dma_a24_map;   /*A24 DMA mngmnt struct  */
  struct ebv10_vme_hw_sg_map_control dma_a32_map;   /*A32 DMA mngmnt struct  */
  struct ebv10_vme_hw_sg_map_control pio_sparse_map;/*PIO Sparse mngmnt str  */
  struct ebv10_vme_hw_sg_map_control pio_dense_map; /*PIO Dense mngmnt struct*/
  struct ebv10_vme_data      cnfg_data;             /*Adapter config data    */

  unsigned int               system_ctlr;           /* sys ctlr 1=yes 0 = no */

  unsigned int               vme_pci_ib_wndw_base;  /*PCI inbound mem offset */
  unsigned int               vme_icf_base;          /*ICF base (256 boundry) */
  unsigned int               vme_icf_mask;          /*ICF mask               */

  unsigned int               vme_a32_real_base;
  unsigned int               vme_a32_real_num_maps;
  io_handle_t                vme_a32_real_sg_ioh;

  unsigned int               vme_a32_mask;
  unsigned int               vme_a32_size;
  unsigned int               vme_a32_base_addr;
  unsigned int               vme_a32_max_addr;
  unsigned int               vme_a32_num_maps;
  io_handle_t                vme_a32_sg_base;
  unsigned int               vme_a32_sg_offset;

  unsigned int               vme_a24_mask;
  unsigned int               vme_a24_size;
  unsigned int               vme_a24_base_addr;
  unsigned int               vme_a24_max_addr;
  unsigned int               vme_a24_num_maps;
  io_handle_t                vme_a24_sg_base;
  unsigned int               vme_a24_sg_offset;

  dma_map_info_t             vme_dma_map_info_ptr;
  struct dma_map_info        vme_a32_dma_map_info;
  struct dma_map_info        vme_a24_dma_map_info;
  struct dma_map_info        vme_icf_map_info;

  int                          sparse_window_pmrs;
  int                          dense_window_pmrs;
  struct ebv10_vme_pio_history *pio_sparse_history;
  struct ebv10_vme_pio_history *pio_dense_history;
};

/* bus specific structures */

#define VME_RESET_INDEX   0
#define VIP_LOC_MON_INDEX 1
#define VIP_ERROR_INDEX   2
#define VIC_ACFAIL_INDEX  3
#define VIC_WRTPOST_INDEX 4
#define VIC_ARBTO_INDEX   5
#define VIC_SYSFAIL_INDEX 6
#define VIC_IACK_INDEX    7
#define VIC_DMACMPL_INDEX 8
#define MAX_VME_ADAPT_INT_HNDLRS 9

#define VEC_SCB_INSTALLED  1
#define VEC_IRQ_ZERO_MASK  0xFE

#define VEC_AUTOVEC_SELECT 0x10000000UL
#define VEC_VMEBUS_SELECT  0x20000000UL
#define VEC_CTLR_SELECT    0x40000000UL
#define VEC_ADAPT_SELECT   0x80000000UL
#define VEC_IRQ_MASK       0x00070000UL
#define VEC_BUS_NUM_MASK   0x00700000UL
#define VECTOR_MASK        0x00001FFFUL

#define VEC_IRQ_SHIFT      16
#define VEC_BUS_NUM_SHIFT  20

#define MAX_IACK_INT_HNDLRS 7

#define VME_DMA_SEGMENT    0x00010000UL

struct ebv10_vme_busvars {
  ihandler_id_t    *adapt_id_t[MAX_VME_ADAPT_INT_HNDLRS];
  ihandler_id_t    *vp_intr_id;
  struct scbentry  iack_sw_scb[MAX_IACK_INT_HNDLRS];
  lock_data_t      adapt_c_lk;
  struct ebv10_vme_intr_info *intr_info;
  struct vp_vme_sw vme_sw;
  dma_map_info_t   dma_info_ptr;
  unsigned long    intr_mask;
  sg_entry_t       mblt_phys_tbl;
  event_t          dma_wakeup_event;
  struct ebv10_vme_pio_history *dma_pio_history_ptr;
  unsigned long    dma_base_vmeaddr;
  unsigned long    dma_max_map_vmeaddr;
  unsigned int     dma_direction;
  unsigned int     dma_xfer_error;
  unsigned long    dma_xfer_bc;
  unsigned long    dma_nxt_bc;
  unsigned long    dma_nxt_memaddr;
  unsigned long    dma_nxt_vmeaddr;
  io_handle_t      dma_nxt_pioh;
  unsigned long    dma_cur_va;
  io_handle_t      dma_cur_base_ioh;
  unsigned long    dma_cur_resid_bc;
  unsigned int     iack_post_pending;
  unsigned char    vec_irq_history[8];
  unsigned char    vec_history[((VME_MAX_SCB_VEC +16) - DEV_SCB_OFFSET)/16];
};

#define VME_MAX_A16_ADDR     0x10000
#define VME_MAX_A24_ADDR   0x1000000

/*
 *  Common VME/VIC bit definitions used in multiple registers
 */
#define VME_IPL_1       1         /* Local bus/VMEbus ipl 1                  */
#define VME_IPL_2       2         /* Local bus/VMEbus ipl 2                  */
#define VME_IPL_3       3         /* Local bus/VMEbus ipl 3                  */
#define VME_IPL_4       4         /* Local bus/VMEbus ipl 4                  */
#define VME_IPL_5       5         /* Local bus/VMEbus ipl 5                  */
#define VME_IPL_6       6         /* Local bus/VMEbus ipl 6                  */
#define VME_IPL_7       7         /* Local bus/VMEbus ipl 7                  */

/*                                                                           */
/* Outbound SG entry definitions 					     */
/*                                                                           */
#define VME_OB_IGNRD1 	        0x001F		/* ignored                   */
#define VME_OB_VALID	        0x0020		/* valid bit                 */
#define VME_OB_SWAP_MASK	0x01C0		/* swap mode                 */
#define VME_OB_RMW		0x0200		/* RMW enable                */
#define VME_OB_AS_MASK		0x0C00		/* address size (modifier)   */
#define VME_OB_FC_MASK		0x3000		/* function code             */
#define VME_OB_IGNRD2          0x3C000		/* ignored                   */
#define VME_OB_VMEADR_MASK  0xFFFC0000	        /* vme address               */

/*                                                                           */
/* byte swap mode constants                                                  */
/* (that may appear in both Inbound and Outbound SG `swap' fields)           */
/*                                                                           */
#define VME_SWAP_NONE          0	  /* no swap                         */
#define VME_SWAP_BYTE          0x0040     /* BYTE swap                       */
#define VME_SWAP_WORD          0x0080     /* WORD size swap                  */
#define VME_SWAP_LONG          0x00C0     /* LONGWORD swap                   */
#define VME_SWAP_QUAD          0x01C0     /* QUAD size swap                  */

/*                                                                           */
/* address space constants                                                   */
/* (that may appear in Outbound SG `am' field)                               */
/*                                                                           */
#define VME_OB_AS_A32          0x0400	  /* a32                             */
#define VME_OB_AS_A16          0x0800	  /* a16                             */
#define VME_OB_AS_A24          0x0C00	  /* a24                             */

/*                                                                           */
/* function code constants                                                   */
/* (that may appear in Outbound SG `fc' field)                               */
/*                                                                           */
#define VME_OB_FC_UDATA        0     	 /* user data                        */
#define VME_OB_FC_UPROG        0x1000    /* USER program                     */
#define VME_OB_FC_SDATA        0x2000    /* SUPERVISORY data                 */
#define VME_OB_FC_SPROG        0x3000    /* SUPERVISORY program              */

#define VME_OB_FC_SUPER        0x2000    /* SUPERVISORY MODE                 */
#define VME_OB_FC_USER         0x0000    /* USER MODE                        */
#define VME_OB_FC_PROG         0x1000    /* PROGRAM MODE                     */
#define VME_OB_FC_DATA         0x0000    /* PROGRAM MODE                     */

/*                                                                           */
/* Inbound SG entry definitions 					     */
/*                                                                           */
#define VME_IB_IGNRD	        0x001F		/* ignored 		     */
#define VME_IB_VALID		0x0020		/* valid bit 		     */
#define VME_IB_SWAP_MASK	0x01C0		/* swap mode 		     */
#define VME_IB_WL		0x0200		/* write lock		     */
#define VME_IB_USER             0x0000          /* User/supervisory access   */
#define VME_IB_SUPER		0x0400		/* supervisory access ONLY   */
#define VME_IB_IO		0x0800		/* I/O mapping	 	     */
#define VME_IB_LOCMON_MASK	0x3000		/* location monitor	     */
#define VME_IB_PFN_MASK	    0xFFFFC000	        /* page frame number	     */

/*                                                                           */
/* location monitor constants                                                */
/* (that may appear in Inbound SG `locmon' field)                            */
/*                                                                           */
#define VME_IB_LOCMON_NONE	0x0000  /* location monitor disable	     */
#define VME_IB_LOCMON_1	        0x1000	/* location monitor #1		     */
#define VME_IB_LOCMON_2	        0x2000	/* location monitor #2 		     */
#define VME_IB_LOCMON_3	        0x3000	/* location monitor #3		     */


#define VME_REG_STRIDE  4        /* Number of bytes between CSR addresses    */

/*                                                                           */
/* VME VIC and VIP  register I/O handles                                     */
/*                                                                           */
struct ebv10_vme_io_handles {
  io_handle_t vic_iicr;      /* VMEbus Interrupter Interrupt Control Register*/
  io_handle_t vic_icr1;      /* VMEbus Interrupt Control Register 1          */
  io_handle_t vic_icr2;      /* VMEbus Interrupt Control Register 2          */
  io_handle_t vic_icr3;      /* VMEbus Interrupt Control Register 3          */
  io_handle_t vic_icr4;      /* VMEbus Interrupt Control Register 4          */
  io_handle_t vic_icr5;      /* VMEbus Interrupt Control Register 5          */
  io_handle_t vic_icr6;      /* VMEbus Interrupt Control Register 6          */
  io_handle_t vic_icr7;      /* VMEbus Interrupt Control Register 7          */
  io_handle_t vic_dmasicr;   /* DMA Status Register                          */
  io_handle_t vic_licr1;     /* Local Interrupt Control Register 1           */
  io_handle_t vic_licr2;     /* Local Interrupt Control Register 2           */
  io_handle_t vic_licr3;     /* Local Interrupt Control Register 3           */
  io_handle_t vic_licr4;     /* Local Interrupt Control Register 4           */
  io_handle_t vic_licr5;     /* Local Interrupt Control Register 5           */
  io_handle_t vic_licr6;     /* Local Interrupt Control Register 6           */
  io_handle_t vic_licr7;     /* Local Interrupt Control Register 7           */
  io_handle_t vic_icgsicr;   /* ICGS Interrupt Control Register              */
  io_handle_t vic_icmsicr;   /* ICMS Interrupt Control Register              */
  io_handle_t vic_egicr;     /* Error Group Interrupt Control Register       */
  io_handle_t vic_icgsivbr;  /* ICGS Intrerupt Vector Base Register          */
  io_handle_t vic_icmsivbr;  /* ICMS Interrupt Vector Base Register          */
  io_handle_t vic_livbr;     /* Local Interrupt Vector Base Register         */
  io_handle_t vic_egivbr;    /* Error Group Interrupt Vector Base Register   */
  io_handle_t vic_icsr;      /* Interprocessor Communication Switch Register */
  io_handle_t vic_ipcr0;     /* Interprocessor Communication Register 0      */
  io_handle_t vic_ipcr1;     /* Interprocessor Communication Register 1      */
  io_handle_t vic_ipcr2;     /* Interprocessor Communication Register 2      */
  io_handle_t vic_ipcr3;     /* Interprocessor Communication Register 3      */
  io_handle_t vic_ipcr4;     /* Interprocessor Communication Register 4      */
  io_handle_t vic_ipcr5;     /* Interprocessor Communication Register 5      */
  io_handle_t vic_ipcr6;     /* Interprocessor Communication Register 6      */
  io_handle_t vic_ipcr7;     /* Interprocessor Communication Register 7      */
  io_handle_t vic_irsr;      /* VMEbus Interrupt Request Status Register     */
  io_handle_t vic_ivbr1;     /* VMEbus Interrupt Vector Base Register 1      */
  io_handle_t vic_ivbr2;     /* VMEbus Interrupt Vector Base Register 2      */
  io_handle_t vic_ivbr3;     /* VMEbus Interrupt Vector Base Register 3      */
  io_handle_t vic_ivbr4;     /* VMEbus Interrupt Vector Base Register 4      */
  io_handle_t vic_ivbr5;     /* VMEbus Interrupt Vector Base Register 5      */
  io_handle_t vic_ivbr6;     /* VMEbus Interrupt Vector Base Register 6      */
  io_handle_t vic_ivbr7;     /* VMEbus Interrupt Vector Base Register 7      */
  io_handle_t vic_ttr;       /* Transfer Timeout Register                    */
  io_handle_t vic_lbtr;      /* Local Bus Timimg Register                    */
  io_handle_t vic_btdr;      /* Block Transfer Definition Register           */
  io_handle_t vic_ifcr;      /* Interface Configuration Register             */
  io_handle_t vic_arcr;      /* Arbiter/Requester Configuration Register     */
  io_handle_t vic_amsr;      /* Adress Modifier Source Register              */
  io_handle_t vic_besr;      /* Bus Error Status Register                    */
  io_handle_t vic_dmasr;     /* DMA Status Register                          */
  io_handle_t vic_ss0cr0;    /* Slave Select 0 - Control Register 0          */
  io_handle_t vic_ss0cr1;    /* Slave Select 0 - Control Register 1          */
  io_handle_t vic_ss1cr0;    /* Slave Select 1 - Control Register 0          */
  io_handle_t vic_ss1cr1;    /* Slave Select 1 - Control Register 1          */
  io_handle_t vic_rcr;       /* Release Control Register                     */
  io_handle_t vic_btcr;      /* Block Transfer Control Register              */
  io_handle_t vic_btlr1;     /* Block Transfer Length Register 1 (15:8)      */
  io_handle_t vic_btlr0;     /* Block Transfer Length Register 0 (7:0)       */
  io_handle_t vic_srr;       /* System Reset Register                        */
  io_handle_t vic_btlr2;     /* Block Transfer Length Register 2 (24:16)     */

  io_handle_t vic_rsrvd[6];  /* Reserved Locations in VIC                    */

  io_handle_t vip_cr;        /* VIP COntrol Register                         */
  io_handle_t vip_besr;      /* VIP Bus Error/Status Register                */
  io_handle_t vip_icr;       /* VIP Interrupt Control Register               */
  io_handle_t vip_irr;       /* VIP Interrupt Reason Register                */
  io_handle_t vip_hwipl;     /* VIP Hardware IPL Mask Register               */
  io_handle_t vip_diagcsr;   /* VIP Diagnostic Control/Status Register       */
  io_handle_t vip_lmcsr;     /* VIP Location Monitor CSR                     */
  io_handle_t vip_obisgabr;  /* VIP Outbound Internal S/G Entry ABR          */
  io_handle_t vip_obisgmsk;  /* VIP Outbound Internal S/G Entry Mask         */
  io_handle_t vip_obisgword; /* VIP Outbound Internal S/G Entry Cntrl Word   */
  io_handle_t vip_ibisgmsk;  /* VIP Inbound Internal S/G Entry Mask          */
  io_handle_t vip_ibisgword; /* VIP Inbound Internal S/G Entry Cntrl Word    */
  io_handle_t vip_sgcchix;   /* VIP S/G Cached Index                         */
  io_handle_t vip_sgcwrd;    /* VIP S/G Cached Control Word                  */
  io_handle_t vip_pciertadr; /* VIP PCI Error Target Address Register        */
  io_handle_t vip_pciertcbe; /* VIP PCI Error Target Command/Byte Enable Reg */
  io_handle_t vip_pcieriadr; /* VIP PCI Error Initiator Address Register     */
  io_handle_t vip_leradr;    /* VIP Local Bus Error Address Register         */

  io_handle_t vip_rsrvd[14]; /* Reserved Locations                           */
  io_handle_t vifamsk;       /* VMEbus I/F Address Mask Register             */
  io_handle_t vifabr;        /* VMEbus I/F Address Base Register             */
  io_handle_t vip_ib_a32_sg; /* Base io_handle of A32 SG PMR's (16K entries) */
  io_handle_t vip_ib_a24_sg; /* Base io_handle of A24 SG PMR's (2k entries)  */
  io_handle_t vip_ob_sg_low; /* Base io_handle of outbound PMR's (8K entries)*/
  io_handle_t vip_ob_sg_hgh; /* Base io_handle of outbound PMR's (8K entries)*/
};

/* VIC64 Register Definitions		                                     */

/* vic_iicr - VIC Interrupter Interrupt Control Register                     */
        /* Provides enabling and IPL level encoding for the local interrupt  */
        /* issued when a VMEbus interrupt is acknowledged.                   */
#define VIC_IICR_IPL_MSK 0x07     /* Bits 2-0 IPL value. Value is inverted   */
                                  /* and driven onto the IPL lines when an   */
                                  /* interrupt is acknowledged.              */

                                  /* Bits 6-3. Reserved should read as 1's.  */

#define VIC_IICR_MASK    0x80     /* VMEbus Interrupt Mask - When clear the  */
#define VIC_IICR_IENABL  0x00     /* VIC signals a local interrupt at the    */
                                  /* acknowledgement of a previously issued  */
                                  /* VMEbus interrupt. When set, the VIC     */
                                  /* will not issue a local interrupt.       */

/* vic_icr1 to vic_icr7 -  VIC Interrupt Control Register                    */
        /* Provides enabling of the VIC as VMEbus interrupt handler for any  */
        /* or all of the VMEbus interrupts. Seven registers exist to provide */
        /* unique masking and IPL values for the seven VMEbus interrupts.    */
#define VIC_ICR_IPL_MSK 0x07      /* Bits 2-0 IPL value. Value is inverted   */
                                  /* and driven onto the IPL signals when a  */
                                  /* interrupt is acknowledged.              */

                                  /* Bits 6-3. Reserved should read as 1's.  */

#define	VIC_ICR_MASK    0x80      /* VMEbus Interrupt Mask. When clear, the  */
#define VIC_ICR_IENABL  0x00      /* VIC acts as a VMEbus interrupt handler  */
                                  /* by signaling a local interrupt at the   */
                                  /* specified IPL level. When set, the VIC  */
                                  /* does not handle the VMEbus interrupt    */
                                  /* and no local interrupt is issued.       */

/* vic_dmasicr -  VIC DMA Status and Interrupt Control Register              */
        /* Provides enabling and IPL level encoding of the DMA complete      */
        /* interrupt issued by the VIC when any VIC local DMA operation      */
        /* completes (successfully or unsuccessfully).                       */
#define VIC_DMASICSR_IPL_MSK 0x07 /* Bits 2-0 IPL value. Value is inverted   */
                                  /* and driven onto the IPL signals when a  */
                                  /* interrupt is acknowledged.              */

                                  /* Bits 6-3. Reserved should read as 1's.  */

#define	VIC_DMASICR_MASK   0x80   /* DMA status interrupt mask. When clear,  */
#define VIC_DMASICR_IENABL 0x00   /* the  VIC signals a local interrupt at   */
                                  /* the completion of any VIC local DMA     */
                                  /* operation. When set, the VIC will not   */
                                  /* issue a local interrupt.                */

/* vic_licr1 to vic_licr7 - VIC Local Interrupt Control Register             */
        /* Provides enabling, IPL level, and control of local interrupts     */
        /* 1-7 (LIRQ1-7)                                                     */
#define VIC_LICR_IPL_MSK 0x07     /* Bits 2-0 IPL value. Value is inverted   */
                                  /* and driven onto the IPL lines when a    */
                                  /* local interrupt is presented on the     */
                                  /* LIRQ1-7* signals and bit 7 of this      */
                                  /* register is clear (enabled)             */
#define VIC_LICR_VSTATE 0x08      /* Bit 3. LIRQ1-7* voltage state. A zero   */
                                  /* bit indicates LIRQ1-7* is asserted at   */
                                  /* VIC                                     */
#define VIC_LICR_VICVECTOR 0x10   /* Bit 4. Autovector enable. When set, the */
                                  /* VIC will supply the interrupt status ID */
                                  /* vector for the local interrupt acknow-  */
                                  /* ledge cycle. When clear, the VIC will   */
                                  /* assert the LIACK0* signal to indicate a */
                                  /* 68K "autovector" condition or that the  */
                                  /* interrupting source should provide the  */
                                  /* Status/ID vector to the processor.      */
                                  /* SBC's this bit MUST be SET.             */
#define VIC_LICR_EDGE   0x20      /* Bit 5. Edge/level enable. When a zero,  */
                                  /* the VIC responds to LIRQ1-7* as a level */
                                  /* sensitive interrupt. When set, it       */
                                  /* responds to LIRQ1-7* as an edge         */
                                  /* sensitive interrupt.                    */
                                  /* SBC's, LIRQ2-LICRQ7 bit MUST be CLEAR   */
#define VIC_LICR_POLARITY  0x40   /* Bit 6. Polarity set. When set, the VIC  */
                                  /* responds to interrupts as active High   */
                                  /* if bit 5 is zero (level sensitive) or   */
                                  /* on rising edge if bit 5 is set (edge    */
                                  /* sensitive). When cleared, the VIC       */
                                  /* responds to active Low or falling edge. */
                                  /* SBC's, LIRQ2-LICRQ7 bit MUST be CLEAR   */
#define VIC_LICR_MASK   0x80      /* Bit 7. Local Interrupt Mask. When clear */
#define VIC_LICR_IENABL 0x00      /* the VIC is enabled to handle the        */
                                  /* corresponding local interrupt asserted  */
                                  /* on the LIRQ1-7* signals.                */

/* vic_icgsicr - VIC ICGS Interrupt Control Register                         */
        /* Provides enabling and IPL encoding for the four global switch     */
        /* interrupts.                                                       */
#define VIC_ICGS0_IPL_MSK 0x07    /* Bits 2-0 IPL value. Value is inverted   */
                                  /* and driven onto the IPL signals when a  */
                                  /* global switch is acknowledged.          */
                                  /* Bit 3. Reserved. Should read as a 1.    */
#define VIC_ICGS0_MASK  0x10      /* Bit 4. ICGS0 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when global switch 0 is set.            */
#define VIC_ICGS1_MASK  0x20      /* Bit 5. ICGS1 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when global switch 1 is set.            */
#define VIC_ICGS2_MASK  0x40      /* Bit 6. ICGS2 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when global switch 2 is set.            */
#define VIC_ICGS3_MASK  0x80      /* Bit 7. ICGS3 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when global switch 3 is set.            */
#define	VIC_ICGSICR_MSK 0xF0      /* ICGS 3:0 mask or ICGS 3:0 Disable bits  */

/* vic_icmsicr - VIC ICMS Interrupt Control Register                         */
        /* Provides enabling and IPL encoding for the four module switch     */
        /* interrupts.                                                       */
#define VIC_ICMS0_IPL_MSK 0x07    /* Bits 2-0 IPL value. Value is inverted   */
                                  /* and driven onto the IPL signals when a  */
                                  /* module switch is acknowledged.          */
                                  /* Bit 3. Reserved. Should read as a 1.    */
#define VIC_ICMS0_MASK  0x10      /* Bit 4. ICMS0 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when module switch 0 is set.            */
#define VIC_ICMS1_MASK  0x20      /* Bit 5. ICMS1 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when module switch 1 is set.            */
#define VIC_ICMS2_MASK  0x40      /* Bit 6. ICMS2 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when module switch 2 is set.            */
#define VIC_ICMS3_MASK  0x80      /* Bit 7. ICMS3 mask. When clear, the VIC  */
                                  /* will issue and handle a local interrupt */
                                  /* when module switch 3 is set.            */
#define	VIC_ICMSICR_MSK 0xF0      /* ICMS 3:0 mask or ICMS 3:0 Disable bits  */

/* vic_egicr - VIC Error Group Interrupt Control Register                    */
        /* Provides enabling and IPL encoding for the error group interrupts */
#define VIC_EGICR_IPL_MSK 0x07    /* Bits 2-0 IPL value. Value is inverted   */
                                  /* and driven onto the IPL signals when a  */
                                  /* module switch is acknowledged.          */
#define VIC_EGICR_SYSFAIL 0x08    /* Bit 3. SYSFAIL* asserted. This bit is   */
                                  /* set whenever SYSFAIL* is detected       */
                                  /* asserted.                               */
#define VIC_EGICR_SYSFAIL_MASK 0x10 /* Bit 4. SYSFAIL* interrupt mask. When  */
                                  /* clear, the VIC generates a local        */
                                  /* interrupt when SYSFAIL* asserted.       */
#define VIC_EGICR_ARB_MASK 0x20   /* Bit 5. Arbitration timeout interrupt    */
                                  /* mask. When clear, the VIC generates a   */
                                  /* local interrupt when an arbitration     */
                                  /* timeout has occured.                    */
#define VIC_EGICR_WPF_MASK 0x40   /* Bit 6. Write post fail interrupt mask.  */
                                  /* When clear, the VIC generates a local   */
                                  /* interrupt when a write post operation   */
                                  /* has failed due to a bus error. For      */
                                  /* master write posts, an assertion of     */
                                  /* BERR* will triger an interrupt. For     */
                                  /* slave write posts, an assertion of      */
                                  /* LBERR* will triger an interrupt.        */
#define VIC_EGICR_ACF_MASK 0x80   /* Bit 7. AC fail interrupt mask. When     */
                                  /* clear, the VIC generates a local        */
                                  /* interrupt when ACFAIL* is detected as   */
                                  /* asserted.                               */
#define	VIC_EGICR_MSK      0xF0   /* Error Group Interrupt Mask Bits         */

/* vic_icgsivbr - VIC ICGS Interrupt Vector Base Register                    */
        /* Provides the status/ID vector for the global switch interrupts.   */
        /* This register must be written after any VIC reset to enable       */
        /* identification encoding for bits 1-0. This register is reset to   */
        /* 0x0F during any VIC reset.                                        */
#define VIC_ICGSIVBR_ICGS0 0x00   /* Bits 1-0. Global switch number (read    */
#define VIC_ICGSIVBR_ICGS1 0x01   /* only). This value indicates which global*/
#define VIC_ICGSIVBR_ICGS2 0x02   /* switch is pending during a global switch*/
#define VIC_ICGSIVBR_ICGS3 0x03   /* interrupt acknowledge cycle. These bits */
                                  /* are used with bits 7-2 to provide a     */
                                  /* unique status/ID vector for each global */
                                  /* switch. These bits are only valid during*/
                                  /* the interrupt acknowledge cycle.        */
#define VIC_ICGSIVBR_ICGS_MSK 0x03
#define VIC_ICGSIVBR_UVEC_MSK 0xFC/* Bits 7-2. Status/ID. These bits are user*/
                                  /* definable and are used with bits 1-0 to */
                                  /* provide a unique global switch interrupt*/
                                  /* status/ID vector.                       */


/* vic_icmsivbr - VIC ICMS Interrupt Vector Base Register                    */
        /* Provides the status/ID vector for the module switch interrupts.   */
        /* This register must be written after any VIC reset to enable       */
        /* identification encoding for bits 1-0. This register is reset to   */
        /* 0x0F during any VIC reset.                                        */
#define VIC_ICMSIVBR_ICMS0 0x00   /* Bits 1-0. Module switch number (read    */
#define VIC_ICMSIVBR_ICMS1 0x01   /* only). This value indicates which module*/
#define VIC_ICMSIVBR_ICMS2 0x02   /* switch is pending during a module switch*/
#define VIC_ICMSIVBR_ICMS3 0x03   /* interrupt acknowledge cycle. These bits */
                                  /* are used with bits 7-2 to provide a     */
                                  /* unique status/ID vector for each module */
                                  /* switch. These bits are only valid during*/
                                  /* the interrupt acknowledge cycle.        */
#define VIC_ICMSIVBR_ICMS_MSK 0x03
#define VIC_ICMSIVBR_UVEC_MSK 0xFC/* Bits 7-2. Status/ID. These bits are user*/
                                  /* definable and are used with bits 1-0 to */
                                  /* provide a unique module switch interrupt*/
                                  /* status/ID vector.                       */

/* vic_livbr - VIC Local Interrupt Vector Base Register                      */
        /* Provides the status/ID vector for the local interrupts.           */
        /* This register must be written after any VIC reset to enable       */
        /* identification encoding for bits 2-0. This register is reset to   */
        /* 0x0F during any VIC reset.                                        */
#define VIC_LIVBR_LIRQ1 0x01      /* Bits 2-0. Local interrupt number (read  */
#define VIC_LIVBR_LIRQ2 0x02      /* only). This value indicates which local */
#define VIC_LIVBR_LIRQ3 0x03      /* interrupt is pending during a local     */
#define VIC_LIVBR_LIRQ4 0x04      /* interrupt acknowledge cycle. These bits */
#define VIC_LIVBR_LIRQ5 0x05      /* are used with bits 7-3 to provide a     */
#define VIC_LIVBR_LIRQ6 0x06      /* unique status/ID vector for each local  */
#define VIC_LIVBR_LIRQ7 0x07      /* interrupt. These bits are only valid    */
                                  /* during the interrupt acknowledge cycle. */
#define VIC_LIVBR_LIRG_MSK 0x07
#define VIC_LIVBR_UVEC_MSK 0xF8   /* Bits 7-3. Status/ID. These bits are user*/
                                  /* definable and are used with bits 2-0 to */
                                  /* provide a unique local interrupt        */
                                  /* status/ID vector.                       */

/* vic_egivbr - VIC Error Group Interrupt Vector Base Register               */
        /* Provides the status/ID vector for the error group interrupts.     */
        /* This register must be written after any VIC reset to enable       */
        /* identification encoding for bits 2-0. This register is reset to   */
        /* 0x0F during any VIC reset.                                        */
#define VIC_EGIVBR_ACFAIL   0x00  /* Bits 2-0. Error/Status Group Interrupt  */
#define VIC_EGIVBR_WRT_PST  0x01  /* number (read only). This value indicates*/
#define VIC_EGIVBR_ARB_TMO  0x02  /* which group interrupt is pending during */
#define VIC_EGIVBR_SYSFAIL  0x03  /* interrupt acknowledge cycle. These bits */
#define VIC_EGIVBR_IINT_ACK 0x04  /* are used with bits 7-3 to provide a     */
#define VIC_EGIVBR_DMA_INT  0x05  /* unique status/ID vector for each error  */
                                  /* group interrupt. These bits are only    */
                                  /* valid during the interrupt acknowledge  */
                                  /* cycle.                                  */
#define VIC_EGIVBR_STAT_MSK 0x07
#define VIC_EGIVBR_UVEC_MSK 0xF8  /* Bits 7-3. Status/ID. These bits are user*/
                                  /* definable and are used with bits 2-0 to */
                                  /* provide a unique interrupt status/ID    */
                                  /* vector.                                 */

/* vic_icsr - VIC Interprocessor Communications Switch Register              */
        /* Provides setting, clearing and monitoring of the interprocessor   */
        /* switch interrupts via the local bus. If the switch interrupts are */
        /* enabled. setting these bits (more precisely, a clear-to-set trans-*/
        /* ition causes a local interrupt to occur in the same way as if the */
        /* switch was set over the VMEbus.                                   */
#define VIC_ICSR_ICMS0    0x01    /* Bits 3-0. Module switches. Bits 0,1,2   */
#define VIC_ICSR_ICMS1    0x02    /* 3 correspnd to ICMS0, ICMS1, ICMS2 and  */
#define VIC_ICSR_ICMS2    0x04    /* ICMS3 respectively in vic_icmsicr.      */
#define VIC_ICSR_ICMS3    0x08
#define VIC_ICSR_MOD_SW_MSK 0x0F
#define VIC_ICSR_ICGS0    0x10    /* Bits 7-4. Global switches. Bits 4,5,6   */
#define VIC_ICSR_ICGS1    0x20    /* 7 correspnd to ICGS0, ICGS1, ICGS2 and  */
#define VIC_ICSR_ICGS2    0x40    /* ICGS3 respectively in vic_icgsicr.      */
#define VIC_ICSR_ICGS3    0x80
#define VIC_ICSR_GLBL_SW_MSK 0xF0

/* vic_ipcr0 to vic_ipcr4 - VIC Interprocessor Communications Registers      */
        /* These are general purpose read/write registers that can be        */
        /* accessed from either the local bus of the VMEbus.                 */
                                  /* Bits 7-0. Data field.                   */

/* vic_ipcr5 VIC Interprocessor Communications Register 5                    */
        /* This register provides the VIC64 version/revision number. It can  */
        /* be accessed from either the local bus of the VMEbus.              */
                                  /* Bits 7-0. VIC64 version/revision        */

/* vic_ipcr6 VIC Interprocessor Communications Register 6                    */
        /* This register provides local or remote reset and HALT*.           */
                                  /* Bits 1-0. Reset/HALT* status (read only)*/
#define VIC_IPCR6_HALT      0x01  /* HALT* has been asserted longer then 6us */
                                  /* by a source other then the VIC.         */
#define VIC_IPCR6_LRESET    0x02  /* The VIC is performing a local reset     */
                                  /* function and the VIC is not the system  */
                                  /* controller.                             */
#define VIC_IPCR6_RELEASE   0x03  /* Indicates that the CPU has just been    */
                                  /* released from a system reset.           */
#define VIC_IPCR6_RUN       0x00  /* Local resources are running and opera-  */
                                  /* tional. This pattern must be written by */
                                  /* local CPU after a reset condition to    */
                                  /* indicate that local resources are run-  */
                                  /* ning and operational.                   */
                                  /* Bits 5-0. Reserved and read as 1's.     */
#define VIC_IPCR6_STATUS    0x40  /* This bit is read only from the VMEbus   */
                                  /* and can be read or written from the     */
                                  /* local bus. The VIC will set this bit    */
                                  /* upon assertion of HALT* or IRESET* as   */
                                  /* specified above or when a reset and hold*/
                                  /* state is entered by writing a 1 to bit 6*/
                                  /* of vic_ipcr7. If bit 7 of vic_ipcr7 is  */
                                  /* 0,the VIC will assert SYSFAIL* whenever */
                                  /* this bit is set.                        */
#define VIC_IPCR6_IRESET    0x80  /* This bit is read only from the VMEbus   */
                                  /* and local bus. On a VMEbus read, a 1    */
                                  /* indicates that IRESET is asserted. On a */
                                  /* local read, the value of ACFAIL is      */
                                  /* returned.                               */

/* vic_ipcr7 VIC Interprocessor Communications Register 7                    */
        /* This register provides semaphores to the five general purpose     */
        /* interprocessor communications registers (IPCR4-0). The remaining  */
        /* bits indicate VMEbus master status, generate HALT* and RESET*, and*/
        /* mask SYSRESET*.                                                   */
#define VIC_IPCR7_ICR0      0x01  /* Bit 0. Set when vic_ipcr0 is written    */
#define VIC_IPCR7_ICR1      0x02  /* Bit 1. Set when vic_ipcr1 is written    */
#define VIC_IPCR7_ICR2      0x04  /* Bit 2. Set when vic_ipcr2 is written    */
#define VIC_IPCR7_ICR3      0x08  /* Bit 3. Set when vic_ipcr3 is written    */
#define VIC_IPCR7_ICR4      0x10  /* Bit 4. Set when vic_ipcr4 is written    */
#define VIC_IPCR7_ICR_MSK   0x1F
#define VIC_IPCR7_MASTER    0x20  /* Bit 5. VMEbus master status (read only) */
                                  /* This bit is set whenever the VIC is the */
                                  /* VMEbus master and the VIC is asserting  */
                                  /* AS*. This bit is not set when the VIC is*/
                                  /* VMEbus master to an idle bus in ROR and */
                                  /* BCAP release modes. Bit 7 of the BESR   */
                                  /* may be used to indicate the the VIC is  */
                                  /* VMEbus master when AS* is not asserted. */
#define VIC_IPCR7_HRESET    0x40  /* Bit 6. HALT* and RESET* control. This   */
                                  /* bit may be used to assert the HALT* and */
                                  /* RESET* pins via software. Whenever this */
                                  /* bit is set, the VIC asserts HALT* and   */
                                  /* RESET* until this bit is cleared or any */
                                  /* reset occurs.                           */
#define VIC_IPCR7_SYSFAIL   0x80  /* Bit 7. SYSFAIL* mask. When set, the VIC */
                                  /* is prohibited from asserting SYSFAIL*   */
                                  /* in response to bit 6 of vic_ipcr6 being */
                                  /* set (which, by default, is set after any*/
                                  /* reset).                                 */

/* vic_irsr VIC VMEbus Interrupt Request/Status Register                     */
        /* This register provides status and control of VMEbus interrupts    */
#define VIC_IRSR_IENABL   0x01      /* Bit 0. Register enable/disable. This  */
#define VIC_IRSR_IDISABL  0x00      /* bit provides enabling/disabling for   */
                                    /* the remainder of this register.       */
#define VIC_IRSR_VMEIRQ1  0x02      /* Bits 7-1. VMEbus interrupt switches.  */
#define VIC_IRSR_VMEIRQ2  0x04      /* Setting any of these bits asserts the */
#define VIC_IRSR_VMEIRQ3  0x08      /* VMEbus IRQi signals corresponding to  */
#define VIC_IRSR_VMEIRQ4  0x10      /* the bit positions, if bit 0 is set    */
#define VIC_IRSR_VMEIRQ5  0x20      /* during the write. These bits are      */
#define VIC_IRSR_VMEIRQ6  0x40      /* cleared by setting the appropriate bit*/
#define VIC_IRSR_VMEIRQ7  0x80      /* and clearing bit 0 during the write.  */
#define VIC_IRSR_VMEIRQ_MSK 0xFE

/* vic_ivbr1 to vic_ivbr7 VIC VMEbus Interrupt Vector Base Registers         */
        /* These registers provide the status/ID byte to be supplied by the  */
        /* VIC upon acknowledgement of the corresponding VMEbus interrupts   */
        /* requested by the VIC interrupter module.                          */
#define VIC_IVBR_UINT_VEC_MSK 0xFF  /* Bits 7-0. Status/ID Vector. These bits*/
                                    /* provide the status/ID vector for      */
                                    /* VMEbus interrupt acknowledge cycles.  */
                                    /* vic_vivbr1 corresponds to IRQ1*.      */

/* vic_ttr  VIC Transfer Timeout Register                                    */
        /* Provides control of the local and VMEbus timeout timers           */
#define VIC_TTR_VMEACQ  0x01        /* Bit 0. Include VMEbus acquisition.    */
                                    /* When set, the local bus timer will    */
                                    /* include waiting for VMEbus acquisition*/
                                    /* When clear, the local bus will stop   */
                                    /* and reset when the VMEbus is requested*/
#define VIC_TTR_ARBTO   0x02        /* Bit 1. Arbitration timeout. When set  */
                                    /* the VIC as VMEbus arbiter has detected*/
                                    /* a VMEbus arbitration timeout. This is */
                                    /* used when configured as the VMEbus    */
                                    /* system controller (SCON* asserted).   */
                                    /* Bits 4-2. Local Bus Timeout period.   */
#define VIC_TTR_LBTO_4US   0x00     /* 4 microseconds                        */
#define VIC_TTR_LBTO_16US  0x04     /* 16 microseconds                       */
#define VIC_TTR_LBTO_32US  0x08     /* 32 microseconds (default)             */
#define VIC_TTR_LBTO_64US  0x0C     /* 64 microseconds                       */
#define VIC_TTR_LBTO_128US 0x10     /* 128 microseconds                      */
#define VIC_TTR_LBTO_256US 0x14     /* 256 microseconds                      */
#define VIC_TTR_LBTO_512US 0x18     /* 512 microseconds                      */
#define VIC_TTR_LBTO_DIS   0x1C     /* timeouts disabled                     */
                                    /* Bits 7-5. VMEbus Timeout period.      */
#define VIC_TTR_VMETO_4US   0x00    /* 4 microseconds                        */
#define VIC_TTR_VMETO_16US  0x20    /* 16 microseconds                       */
#define VIC_TTR_VMETO_32US  0x40    /* 32 microseconds (default)             */
#define VIC_TTR_VMETO_64US  0x60    /* 64 microseconds                       */
#define VIC_TTR_VMETO_128US 0x80    /* 128 microseconds                      */
#define VIC_TTR_VMETO_256US 0xA0    /* 256 microseconds                      */
#define VIC_TTR_VMETO_512US 0xC0    /* 512 microseconds                      */
#define VIC_TTR_VMETO_DIS   0xE0    /* timeouts disabled                     */

#define VIC_TTR_LBUSTO_SHIFT    2
#define VIC_TTR_VMETO_SHIFT     5


/* vic_lbtr  VIC Local Bus Timeout Register                                  */
        /* Provides timing control of PAS* and DS* signals when the VIC is   */
        /* local bus master. In the following descriptions, "n" is the       */
        /* binary value specified in the bit fields, and "T" is one CLK64M   */
        /* clock period. Clock latency may add one additional clock period   */
        /* these times.                                                      */
#define VIC_LBTR_MIN_A_PAS 0x00         /* Bit 3-0. Minimum PAS* asserted    */
                                        /* time. This field specifies the    */
                                        /* minimum asserted time for the     */
                                        /* PAS* signal whenever the VIC is   */
                                        /* the local bus master. The time    */
                                        /* is specified by (n+2)T.           */
                                        /* RECOMMENDED TO LEAVE AT ZERO      */
#define VIC_LBTR_MIN_D_DS  0x10         /* Bit 4. Minimum DS* deasserted     */
                                        /* time. This field specifies the    */
                                        /* minimum deasserted time for DS*   */
                                        /* signal whenever the VIC is the    */
                                        /* local bus master. A zero in this  */
                                        /* bit selects 1T, whereas a 1,      */
                                        /* selects 2T.                       */
                                        /* RECOMMENDED TO BE SET             */
#define VIC_LBTR_MIN_D_PAS 0xC0         /* Bits 7-5. Minimum PAS* deasserted */
                                        /* time. This field specifies the    */
                                        /* minimum deasserted time for PAS*  */
                                        /* signal whenever the VIC is the    */
                                        /* local bus master. The time is     */
                                        /* specified by (n+1)T.              */
                                        /* RECOMMENDED TO BE BINARY 110      */


/* vic_btdr  VIC Block Transfer Definition Register                          */
        /* Configures master block transfers (both MOVEM and block transfers */
        /* with local DMA) for boundry crossings, dual-path, and user-defined*/
        /* address modifiers.                                                */
#define VIC_BTDR_DPATH_ENA 0x01         /* Bit 0. Dual-path Enable. When set */
                                        /* the VIC is enabled with the dual- */
                                        /* path feature during master block  */
                                        /* transfers with local DMA. External*/
                                        /* logic is required when this option*/
                                        /* is enabled. DO NOT SET THIS BIT.  */
#define VIC_BTDR_AMSR_ENA  0x02         /* Bit 1. AMSR Enable. When set, the */
                                        /* VIC will issue the AM codes based */
                                        /* in the address modifier source    */
                                        /* register for block transfers. This*/
                                        /* bit effects AM codes for block    */
                                        /* transfers only.                   */
#define VIC_BTDR_LOC256_ENA 0x04        /* Bit 2. Enables Local address 256- */
                                        /* byte boundry crossing during DMA  */
                                        /* block transfer transfer operations*/
                                        /* RECOMMENDED THAT THIS BIT BE SET  */
#define VIC_BTDR_BUS256_ENA 0x08        /* Bit 3. Enables VMEbus address 256 */
                                        /* byte boundry crossing during DMA  */
                                        /* block transfer transfer operations*/
                                        /* RECOMMENDED THAT THIS BIT BE SET  */
#define VIC_BTDR_D64M_ENA   0x10        /* Bit 4. Enables D64 master opera-  */
                                        /* tions when BTCR bit 6 is set.     */
                                        /* RECOMMENDED THAT THIS BIT BE SET  */
#define VIC_BTDR_TURBO_ENA  0x20        /* Bit 5. Enables accelerated Block  */
                                        /* transfer operations.              */
                                        /* RECOMMENDED BIT MUST BE CLEAR     */
#define VIC_BTDR_D64S_ENA   0x40        /* Bit 6. Enables D64 slave operation*/
                                        /* RECOMMENDED THAT THIS BIT BE SET  */
#define VIC_BTDR_2K_ENA     0x80        /* Bit 7. Enables 2K byte boundry    */
                                        /* crossing for D64 master operations*/
                                        /* If this bit is set, VIC64 assumes */
                                        /* that the transfer is aligned to a */
                                        /* 2k boundry.                       */

/* vic_ifcr  VIC Interface Configuration Register                            */
        /* Controls various features of the VIC including RMCs, deadlock     */
        /* signaling, metastability delays, and the turbo feature.           */
#define VIC_IFCR_SCON      0x01         /* Bit 0. SCON* value (read only).   */
                                        /* When set, the VIC is not VMEbus   */
                                        /* system controller. When clear,    */
                                        /* VIC is system controller.         */
#define VIC_IFCR_TURBO     0x02         /* Bit 1. Turbo Enables. When set,   */
                                        /* the VIC accelerates VMEbus xfers  */
                                        /* by reducing selected timing by one*/
                                        /* CLK64M clock period.              */
                                        /* RECOMMEND THAT BIT MUST BE CLEAR  */
#define VIC_IFCR_META      0x04         /* Bit 2. Metastability interval.    */
                                        /* When set, the VIC adds one        */
                                        /* additional CLK64M clock period of */
                                        /* metastability delay on            */
                                        /* asynchronous inputs.              */
                                        /* RECOMMEND THAT BIT MUST BE CLEAR  */
                                        /* Bits 4-3. Deadlock signaling.     */
                                        /* These bits configure deadlock     */
                                        /* signaling. Bit 4 is used to enable*/
                                        /* the assertion of HALT* and LBERR* */
                                        /* in addition to the DEDLK* signal  */
                                        /* in deadlock situations. If Bit 4  */
                                        /* is enabled, bit 3 may be used to  */
                                        /* prevent the assertion of HALT* for*/
                                        /* RMC deadlocks.                    */
                                        /* RECOMMEND THAT BITS MUST BE CLEAR */
#define VIC_IFCR_DEDLK_SEL00  0x00      /* DEDLK* only (default)             */
#define VIC_IFCR_DEDLK_SEL10  0x10      /* HALT*, LBERR*, DEDLK*             */
#define VIC_IFCR_DEDLK_SEL11  0x18      /* HALT*, LBERR*, DEBLK*             */
                                        /* (HALT* not asserted for RMC cycles*/
#define VIC_IFCR_RMC_CB1      0x20      /* Bit 5. RMC Control Bit 1. When set*/
                                        /* the VIC will request the VMEbus   */
                                        /* whenever the RMC* is asserted     */
                                        /* independent of the MWB* signal.   */
                                        /* If the control bit, bit 7, is set */
                                        /* request is made only if the size  */
                                        /* of the first cycle of the indivis-*/
                                        /* able sequence is other than byte. */
                                        /* If bit 7 is clear, the request is */
                                        /* made independent of the size.     */
#define VIC_IFCR_RMC_CB2      0x40      /* Bit 6. RMC Control Bit 2. When set*/
                                        /* the the VMEbus AS* is stretched   */
                                        /* when the RMC* is asserted for     */
                                        /* VMEbus transfers. This is a don't */
                                        /* care condition if bit 7 is set.   */
#define VIC_IFCR_RMC_CB3      0x80      /* Bit 7. RMC Control Bit 3. When set*/
                                        /* the VIC qualifies the RMC control */
                                        /* bits 5 and 6 with the SIZ1/0      */
                                        /* signals. If RMC control bits 5 and*/
                                        /* 6 are set and the first cycle of  */
                                        /* the RMC transfer is of byte size, */
                                        /* the "set" behaviours are not      */
                                        /* implemented.                      */

/* vic_arcr  VIC Arbiter/Requester Configuration Register                    */
        /* This register provides configuration of the fairness timeout and  */
        /* DRAM refresh features. The VMEbus request level is also configured*/
        /* from this register.                                               */
                                        /* Bits 3-0. Fairness timer enable.  */
                                        /* The VMEbus fair requester is      */
                                        /* is enabled in this bit field. Two */
                                        /* values have specific meaning, all */
                                        /* other values indicate that the    */
                                        /* value is multiplied by 2us.       */
#define VIC_ARCR_FRTO_DSABL 0x00        /* Fairness disabled (default)       */
#define VIC_ARCR_FRTO_2     0x01        /* Fair Request Timeout = 2us        */
#define VIC_ARCR_FRTO_4     0x02        /* Fair Request Timeout = 4us        */
#define VIC_ARCR_FRTO_6     0x03        /* Fair Request Timeout = 6us        */
#define VIC_ARCR_FRTO_8     0x04        /* Fair Request Timeout = 8us        */
#define VIC_ARCR_FRTO_10    0x05        /* Fair Request Timeout = 10us       */
#define VIC_ARCR_FRTO_12    0x06        /* Fair Request Timeout = 12us       */
#define VIC_ARCR_FRTO_14    0x07        /* Fair Request Timeout = 14us       */
#define VIC_ARCR_FRTO_16    0x08        /* Fair Request Timeout = 16us       */
#define VIC_ARCR_FRTO_18    0x09        /* Fair Request Timeout = 18us       */
#define VIC_ARCR_FRTO_20    0x0A        /* Fair Request Timeout = 20us       */
#define VIC_ARCR_FRTO_22    0x0B        /* Fair Request Timeout = 22us       */
#define VIC_ARCR_FRTO_24    0x0C        /* Fair Request Timeout = 24us       */
#define VIC_ARCR_FRTO_26    0x0D        /* Fair Request Timeout = 26us       */
#define VIC_ARCR_FRTO_28    0x0E        /* Fair Request Timeout = 28us       */
#define VIC_ARCR_FRTO_NONE  0x0F        /* Fair Request Tiemout = none       */

#define VIC_ARCR_DRAM_ENA   0x10        /* Bit 4. DRAM refresh enable. When  */
                                        /* set, the VIC will perform CAS*    */
                                        /* before RAS* (DS* before PAS*)     */
                                        /* refresh function.                 */
                                        /* RECOMMEND THAT BIT MUST BE CLEAR  */
                                        /* Bits 6-5. VMEbus request level    */
#define VIC_ARCR_BRLVL0     0x00        /* VMEbus Request Level BR0          */
#define VIC_ARCR_BRLVL1     0x20        /* VMEbus Request Level BR1          */
#define VIC_ARCR_BRLVL2     0x40        /* VMEbus Request Level BR2          */
#define VIC_ARCR_BRLVL3     0x60        /* VMEbus Request Level BR3 (default)*/
#define VIC_ARCR_ARB_PRIO   0x80        /* Bit 7. Arbitration Mode Select.   */
#define VIC_ARCR_ARB_RR     0x00        /* When set, the VIC performs prior- */
                                        /* ity VMEbus arbitration. When clear*/
                                        /* the VIC performs round-robin arbi-*/
                                        /* tration. Only relevant when the   */
                                        /* VIC is configured as the VMEbus   */
                                        /* system controller.                */

#define VIC_ARCR_FRTO_MASK  0x0F
#define VIC_ARCR_BRLV_MASK  0x60
#define VIC_ARCR_ARB_MASK   0x80

#define VIC_ARCR_BRLV_SHIFT 5

/* vic_amsr  VIC Address Modifier Source Register                            */
        /* This register provides the user definable address modifiers (AM   */
        /* codes) that can be sourced by the VIC for VMEbus master cycles, or*/
        /* used in validating AM codes during VMEbus slave cycles.           */
#define VIC_AMSR_ADDR_MOD_MSK 0x3F      /* Bits 5-0. Address modifier code.  */
                                        /* The AM code that is issued during */
                                        /* master cycles or used for qualify-*/
                                        /* ing slave cycles. This register is*/
                                        /* used only when enabled for user-  */
                                        /* defined AM codes. Otherwise, stan-*/
                                        /* dard VMEbus codes are used.       */
#define VIC_AMSR_AM53_QUAL    0x40      /* Bit 6. AM5-3 qualification. When  */
                                        /* set, the VIC uses bits 5-3 in     */
                                        /* qualifying for slave accesses in  */
                                        /* addition to the address space size*/
                                        /* information defined in bits 3 and */
                                        /* 2 of the SSICR0s. This bit is     */
                                        /* over-ridden if bits 3 and 2 of the*/
                                        /* SSICR0s are both clear.           */
#define VIC_MASR_AM20_GEN     0x80      /* Bit 7. AM2-0 generation. When set */
                                        /* the VIC issues the AM2-0 codes    */
                                        /* based on the FC2/1 signals. AM5-3 */
                                        /* will be issued from bits 5-3 of   */
                                        /* this register. This bit is over-  */
                                        /* ridden if the VIC is configured   */
                                        /* is issue all AM bits from this    */
                                        /* register (i.e. ASIZ1=ASIZ0=Low).  */

/* vic_besr  VIC Bus Error Status Register                                   */
        /* This register provides BERR/LBERR*, self access, VMEbus master-   */
        /* ship, and timeout status. All bits except bit 7 are flags that    */
        /* must be cleared manually by the local processor after being set by*/
        /* status conditions. If these bits are to be used for a specific    */
        /* operation, it is important that they be cleared prior to starting */
        /* that operation.                                                   */
#define VIC_BESR_LTMO_ACQ  0x01         /* Bit 0. Local timeout during VMEbus*/
                                        /* acquisition. This bit, when set,  */
                                        /* indicates that a local bus timeout*/
                                        /* has occured during an attempted   */
                                        /* acquisition of the VMEbus.        */
#define VIC_BESR_SLSEL1    0x02         /* Bit 1. SLSEL1* self access. This  */
                                        /* bit is set when the VIC is select-*/
                                        /* ed by the assertion on the SLSEL1**/
                                        /* signal, while operating as VMEbus */
                                        /* master.                           */
#define VIC_BESR_SLSEL0    0x04         /* Bit 2. SLSEL0* self access. This  */
                                        /* bit is set when the VIC is select-*/
                                        /* ed by the assertion on the SLSEL0**/
                                        /* signal, while operating as VMEbus */
                                        /* master.                           */
#define VIC_BESR_LBTO      0x08         /* Bit 3. Local bus timeout. This bit*/
                                        /* when set, indicates a local bus   */
                                        /* timeout occured without qualifi-  */
                                        /* cation.                           */
#define VIC_BESR_VMETO     0x10         /* Bit 4. VMEbus timeout. This bit   */
                                        /* when set, indicates the VIC has   */
                                        /* signaled a VMEbus timeout. This   */
                                        /* bit is relevant only if the VIC is*/
                                        /* system controller and the VMEbus  */
                                        /* timeout is enabled.               */
#define VIC_BESR_BERR      0x20         /* Bit 5. VMEbus Error. This bit is  */
                                        /* set when a VMEbus bus error is    */
                                        /* signaled (BERR* asserted).        */
#define VIC_BESR_LBERR     0x40         /* Bit 6. Local bus error. This bit  */
                                        /* is set when a local bus error is  */
                                        /* signaled by a source other then   */
                                        /* VIC (LBERR* asserted to VIC).     */
#define VIC_BESR_VICMASTER 0x80         /* Bit 7. VMEbus mastership. This bit*/
                                        /* is set whenever the VIC is VMEbus */
                                        /* master.                           */
#define VIC_BESR_INT_MSK   0x7F         /* interruptable bits                */

/* vic_dmasr  VIC DMA Status Register                                        */
        /* This register provides status of a VIC DMA transfer. This includes*/
        /* the block transfer with local DMA function and the module based   */
        /* function. Status bits are included to show various BERR* and      */
        /* LBERR* statuses and DMA termination statuses                      */
#define VIC_DMASR_BLKTIP  0x01          /* Bit 0. Block transfer in progress.*/
                                        /* This bit, when set, indicates an  */
                                        /* interleaved block transfer is in  */
                                        /* progress. Once set, it is cleared */
                                        /* at completion of a local DMA oper-*/
                                        /* ation automatically by the VIC.   */
                                        /* It can also be manually cleared by*/
                                        /* writing a 0 to this bit position. */
#define VIC_DMASR_LBERR    0x02         /* Bit 1. LBERR* during DMA transfer.*/
                                        /* This bit, when set, indicates a   */
                                        /* LBERR* was signaled during a DMA  */
                                        /* transfer. Once set, this bit must */
                                        /* be cleared manually by writing a  */
                                        /* 0 to this bit position or by re-  */
                                        /* setting the VIC.                  */
#define VIC_DMASR_BERR     0x04         /* Bit 2. BERR* during DMA transfr.  */
                                        /* This bit, when set, indicates a   */
                                        /* BERR* was signaled during a DMA   */
                                        /* transfer. Once set, this bit must */
                                        /* be cleared manually by writing a  */
                                        /* 0 to this bit position or by re-  */
                                        /* setting the VIC.                  */
#define VIC_DMASR_LBUS_ERR 0x08         /* Bit 3. Local bus error (read only)*/
                                        /* This bit is set when a local bus  */
                                        /* error is signaled by a source     */
                                        /* other then the VIC (LBERR* assert-*/
                                        /* ed to the VIC). This bit is read- */
                                        /* only copy of bit 6 of the vic_besr*/
#define VIC_DMASR_VBUS_ERR 0x10         /* Bit 4. VMEbus bus error. This bit */
                                        /* is set when a VMEbus bus error is */
                                        /* signaled (BERR* asserted). This   */
                                        /* bit is a copy of bit 5 of the     */
                                        /* vic_besr register.                */
                                        /* Bits 6-5. Undefined. Read as 1's  */
#define VIC_DMASR_MWRT_POST 0x80        /* Bit 7. Master write post informa- */
                                        /* tion stored. This bit is set when-*/
                                        /* ever master write post information*/
                                        /* is stored.                        */
#define VIC_DMASR_ERR_MSK   0x1F        /* dmasr error mask bits             */
#define VIC_DMASR_MSK       0x9F        /* dmasr valid information bits      */

/* vic_ss0cr0  VIC Slave Select 0 - Control Register 0                       */
        /* This register provides control of the slave selection 0 facilities*/
        /* of the VIC. Enabling of the LIRQ2 timer interrupt is also confi-  */
        /* gured in this register.                                           */
                                        /* Bits 1-0. Local transfer mode.    */
                                        /* These bits set the local transfer */
                                        /* mode when the VIC is local bus    */
                                        /* master for both slave and master  */
                                        /* block transfers.                  */
#define VIC_SS0CR0_NONE   0x00          /* No support is given for slave     */
                                        /* block transfers on SLSEL0. The VIC*/
                                        /* will BERR* any attempt to receive */
                                        /* a VMEbus block transfer. Master   */
                                        /* block transfers with local DMA    */
                                        /* will not function in this mode.   */
#define VIC_SS0CR0_EMLT_SC 0x01         /* Emulate single-cycle transfers on */
                                        /* the local bus. In this mode, the  */
                                        /* VIC emulates single-cycle trans-  */
                                        /* fers when performing slave block  */
                                        /* transfers and master block trans- */
                                        /* fers with local DMA.              */
#define VIC_SS0CR0_ACC_XFERS 0x02       /* Accelerated transfers on the local*/
                                        /* bus. In this mode, the VIC asserts*/
                                        /* the PAS* signal for the entire    */
                                        /* slave block transfer and master   */
                                        /* block transfer with local DMA.    */
                                        /* RECOMMEND MUST USE THIS SELECTION */
                                        /* Bits 3-2. Address space configura-*/
                                        /* tion. The SLSEL0 address space is */
                                        /* configured according to these bits*/
#define VIC_SS0CR0_A32  0x00            /* A32 (extended)(default)           */
                                        /* RECOMENDED FOR A32 SLAVE SELECTION*/
#define VIC_SS0CR0_A24  0x04            /* A24 (standard)                    */
#define VIC_SS0CR0_A16  0x08            /* A16 (short)                       */
#define VIC_SS0CR0_UDEF 0x0C            /* User defined, uses AMSR register  */

#define VIC_SS0CR0_D32  0x10            /* Bit 4. D32 Enable. D32 slave oper-*/
                                        /* ations are enabled for SLSEL0 when*/
                                        /* this bit is set. This bit has no  */
                                        /* effect for enabling D32 master    */
                                        /* accesses. This bit also controls  */
                                        /* byte-lane switching for D16 Block */
                                        /* transfers. When set, ISOBE* and   */
                                        /* SWDEN* alternate states thus      */
                                        /* alternating which D16 bus data is */
                                        /* placed. When clear, only SWDEN*   */
                                        /* is asserted for D16 block xfers.  */
                                        /* RECOMMEND MUST BE SET             */
#define VIC_SS0CR0_SUP  0x20            /* Bit 5. Supervisory access. When   */
                                        /* set, SLSEL0* slave accesses are   */
                                        /* restricted to supervisory accesses*/
                                        /* Other accesses are BERRed. Super- */
                                        /* visory accesses are checked with  */
                                        /* AM(2) signal                      */
                                        /* Bits 7-6. Periodic interrupt timer*/
                                        /* enable. These bits enable and de- */
                                        /* termine the frequency of the      */
                                        /* periodic LIRQ2 interrupt. If the  */
                                        /* VIC is to handle this local inter-*/
                                        /* rupt, LICR2 must be enabled.      */
#define VIC_SS0CR0_TMR_DSABL    0x00    /* Timer disabled (default)          */
                                        /* RECOMMEND MUST BE THIS VALUE      */
#define VIC_SS0CR0_50HZ_LIRQ2   0x40    /* 50-Hz output on LIRQ2*            */
#define VIC_SS0CR0_1000HZ_LIRQ2 0x80    /* 1000Hz output on LIRQ2*           */
#define VIC_SS0CR0_100HZ_LIRQ2  0xC0    /* 100Hz output on LIRQ2*            */

/* vic_ss0cr1  VIC Slave Select 0 - Control Register 1                       */
        /* This register provides the various access and acquisition timing  */
        /* for the slave transfers and slave block transfers for SLSEL0* in  */
        /* addition to data acquisition timing for naster block transfers    */
        /* with local DMA.                                                   */
                                        /* Bits 3-0. Timing Field 0. These   */
                                        /* bits establish the following      */
                                        /* access/acquisition timing.        */
                                        /* Single-cycle slave access timing  */
                                        /* for SLSEL0* (SAT)                 */
                                        /* First cycle of a slave block      */
                                        /* transfer for SLSEL0* (SBAT0)      */
                                        /* First cycle of a master block     */
                                        /* transfer with local DMA (MBAT0)   */
                                        /* First cycle of a module-based     */
                                        /* DMA transfer (DMAAT0)             */
#define VIC_SS0CR1_TMF0  0x01           /* CLK64M Clock Period Delay 2.0     */
                                        /* Bits 7-4. Timing Field 1. These   */
                                        /* bits establish the following      */
                                        /* access/acquisition timing.        */
                                        /* Second and subsequent cycle of a  */
                                        /* slave block transfer for SLSEL0*  */
                                        /* (SBAT1)                           */
                                        /* Second and subsequent cycle of a  */
                                        /* master block transfer with local  */
                                        /* DMA (MBAT1)                       */
                                        /* Second and subsequent cycle of a  */
                                        /* module-based DMA transfer (DMAAT1)*/
#define VIC_SS0CR1_TMF1  0x00           /* CLK64M Clock Period Delay 0       */


/* vic_ss1cr0  VIC Slave Select 1 - Control Register 0                       */
        /* This register provides control of the slave selection 1 facilities*/
        /* of the VIC. Master and slave write posting is enabled in this     */
        /* register.                                                         */
                                        /* Bits 1-0. Local transfer mode.    */
                                        /* These bits set the local transfer */
                                        /* mode when the VIC is local bus    */
                                        /* master for both slave and master  */
                                        /* block transfers.                  */
#define VIC_SS1CR0_NONE      0x00       /* No support is given for slave     */
                                        /* block transfers on SLSEL1. The VIC*/
                                        /* will BERR* any attempt to receive */
                                        /* a VMEbus block transfer.          */
#define VIC_SS1CR0_EMLT_SC   0x01       /* Emulate single-cycle transfers on */
                                        /* the local bus. In this mode, the  */
                                        /* VIC emulates single-cycle trans-  */
                                        /* fers when performing slave block  */
                                        /* transfers.                        */
#define VIC_SS1CR0_ACC_XFERS 0x02       /* Accelerated transfers on the local*/
                                        /* bus. In this mode, the VIC asserts*/
                                        /* the PAS* signal for the entire    */
                                        /* slave block transfer.             */
                                        /* RECOMMEND MUST USE THIS SELECTION */
                                        /* Bits 3-2. Address space configura-*/
                                        /* tion. The SLSEL1 address space is */
                                        /* configured according to these bits*/
#define VIC_SS1CR0_A32     0x00         /* A32 (extended)(default)           */
#define VIC_SS1CR0_A24     0x04         /* A24 (standard)                    */
                                        /* RECOMENDED FOR A24 SLAVE SELECTION*/
#define VIC_SS1CR0_A16     0x08         /* A16 (short)                       */
#define VIC_SS1CR0_UDEF    0x0C         /* User defined, uses AMSR register  */
#define VIC_SS1CR0_D32     0x10         /* Bit 4. D32 Enable. D32 slave oper-*/
                                        /* ations are enabled for SLSEL1 when*/
                                        /* this bit is set. This bit has no  */
                                        /* effect for enabling D32 master    */
                                        /* accesses.                         */
                                        /* RECOMMEND MUST BE SET             */
#define VIC_SS1CR0_SUP     0x20         /* Bit 5. Supervisory access. When   */
                                        /* set, SLSEL1* slave accesses are   */
                                        /* restricted to supervisory accesses*/
                                        /* Other accesses are BERRed. Super- */
                                        /* visory accesses are checked with  */
                                        /* AM(2) signal                      */
#define VIC_SS1CR0_MWP_ENA 0x40         /* Bit 6, Master wrtie post enable.  */
                                        /* When set, master write posting is */
                                        /* enabled.                          */
                                        /* RECOMMEND THAT BIT MUST BE CLEAR  */
#define VIC_SS1CR0_SWP_ENA 0x80         /* Bit 7. Slave write post enable.   */
                                        /* When set slave write posting is   */
                                        /* Enabled.                          */
                                        /* RECOMMEND THAT BIT MUST BE CLEAR  */

/* vic_ss0cr1  VIC Slave Select 1 - Control Register 1                       */
        /* This register provides the various access and acquisition timing  */
        /* for the slave transfers and slave block transfers for SLSEL1*.    */
                                        /* Bits 3-0. Timing Field 0. These   */
                                        /* bits establish the following      */
                                        /* access/acquisition timing.        */
                                        /* Single-cycle slave access timing  */
                                        /* for SLSEL1* (SAT)                 */
                                        /* First cycle of a slave block      */
                                        /* transfer for SLSEL1* (SBAT0)      */
#define VIC_SS1CR1_TMF0  0x01           /* CLK64M Clock Period Delay 2.0     */
                                        /* Bits 7-4. Timing Field 1. These   */
                                        /* bits establish the following      */
                                        /* access/acquisition timing.        */
                                        /* Second and subsequent cycle of a  */
                                        /* slave block transfer for SLSEL1*  */
                                        /* (SBAT1)                           */
#define VIC_SS1CR1_TMF1  0x00           /* CLK64M Clock Period Delay 0       */

/* vic_rcr  VIC Release Control Register                                     */
        /* This register configures the VMEbus release mode and the burst    */
        /* length for block transfers with local DMA.                        */
                                        /* Bits 5-0. Block transfer burst    */
                                        /* length. The burst length for both */
                                        /* MOVEM and block transfers with    */
                                        /* local DMA are configured in this  */
                                        /* bit field. The value indicates the*/
                                        /* number of cycles per block        */
                                        /* For MBLT operations (D64 trans-   */
                                        /* fers), the burst length is 4 times*/
                                        /* the actual field contents. A value*/
                                        /* of 0 is interpreted to be 4*64.   */
                                        /* For non-MBLT operations, the burst*/
                                        /* length is simply the field con-   */
                                        /* contents. A value of 0 is inter-  */
                                        /* preted to mean 64.                */
                                        /* RECOMMEND THAT THIS FIELD BE CLEAR*/
                                        /* Bits 7-6. Release Mode. This bit  */
                                        /* field defines the release mode    */
                                        /* used by the VIC when releasing the*/
                                        /* VMEbus after the completion of a  */
                                        /* VMEbus transfer.                  */
#define VIC_RCR_MODE_ROR  0x00          /* ROR - Release on Request (default)*/
#define VIC_RCR_MODE_RWD  0x40          /* RWD - Release When Done           */
#define VIC_RCR_MODE_ROC  0x80          /* ROC - Release on BCLR* assertion  */
#define VIC_RCR_MODE_BCAP 0xC0          /* BCAP - VMEbus Capture and Hold    */

/* vic_btcr  VIC Block Transfer Control Register                             */
        /* This register provides control of the VIC block transfers. The    */
        /* local interleave periods and the data direction are defined in    */
        /* this register. The enabling bits got all of the VIC's block trnas-*/
        /* fer modes are located here as well. These enabling bits are       */
        /* mutuslly exclusive and more than one should not be set at the same*/
        /* time.                                                             */
#define VIC_BTCR_INTRLV_MSK 0x0F        /* Bits 3-0. Interleave period. The  */
                                        /* interleave period for block trans-*/
                                        /* fers are defined here. The inter- */
                                        /* leave period is 250ns times the   */
                                        /* value loaded into this bit field. */
#define VIC_BTCR_BLK_RD    0x10         /* Bit 4. Data Direction. This bit   */
#define VIC_BTCR_BLK_WRT   0x00         /* defines the direction of a block  */
                                        /* transfer with local DMA. When set,*/
                                        /* VMEbus block reads occur. When    */
                                        /* clear, VMEbus writes occur.       */
#define VIC_BTCR_MOVEM_ENA 0x20         /* Bit 5. MOVEM enable. When set,    */
                                        /* MOVEM transfers are enabled. After*/
                                        /* this bit is set, next VMEbus      */
                                        /* transfer is treated as the start  */
                                        /* of a VMEbus block transfer. Clear-*/
                                        /* ing this bit concludes a MOVEM    */
                                        /* block transfer in progress.       */
                                        /* RECOMMEND THIS BIT BE CLEAR       */
#define VIC_BTCR_BLT_ENA   0x40         /* Bit 6. Block transfer with local  */
                                        /* DMA enable. When set, block trans-*/
                                        /* fers with local DMA are enabled.  */
                                        /* After this bit is set, the next   */
                                        /* assertion of MWB* is considered   */
                                        /* the initiation cycle of a VMEbus  */
                                        /* block transfer with local DMA. It */
                                        /* is important to set this bit      */
                                        /* immediately before and clear this */
                                        /* bit immediately after the actual  */
                                        /* block transfer.                   */
                                        /* RECOMMEND THAT THIS BIT BE SET    */
#define VIC_BTCR_MODT_ENA   0x80        /* Bit 7. Module-based DMA transfer  */
                                        /* enable. When set, module-based DMA*/
                                        /* transfers are enabled. After this */
                                        /* bit is set, the next assertion of */
                                        /* BLT* by external logic is consid- */
                                        /* ered the initiation cycle of a    */
                                        /* module-based DMA transfer. Clear- */
                                        /* ing this bit concludes a module-  */
                                        /* based DMA transfer in progress.   */
                                        /* It is important to set this bit   */
                                        /* immediately before and clear this */
                                        /* bit immediately after the actual  */
                                        /* DMA transfer.                     */

/* vic_bltr0, vic_btlr1, vic_btlr2  VIC Block Transfer Length Registers 2-0  */
        /* These registers configure the byte count for block transfers with */
        /* local DMA. BTLR2 is considered the most significant byte, BTLR1 is*/
        /* the next significant byte abd BTLR0 is the least significant byte.*/
        /* Bit 0 of BTLR0 must never be set because it implies at least one  */
        /* 8-bit transfer is required to complete the block transfer. Only   */
        /* D16, D32 and D64 block transfers are supported.                   */
                                        /* Bits 7-0. Block transfer length.  */
                                        /* Defines the block transfer length */
                                        /* in bytes. BTLR2 is the most sig-  */
                                        /* nificant byte, BTLR1 the next and */
                                        /* BTLR0 is the least significant.   */

/* vic_srr  VIC  System Reset Register                                       */
        /* The system reset register provides the means to perform a VMEbus  */
        /* system reset (SYSRESET* asserted). Writing a value of 0xF0 causes */
        /* this function to occur. A system reset is also performed with the */
        /* VIC.                                                              */
#define VIC_SRR_SYS_RESET  0xF0         /* Bits 7-0. System reset field.     */
                                        /* Writing this field with 0xF0      */
                                        /* causes SYSRESET* to be asserted   */
                                        /* for a minimum of 200ms and a      */
                                        /* system reset to be performed with-*/
                                        /* in the VIC.                       */

/*                                                                           */
/* vip_cr  VIP  Control Register - R/W Cleared on powerup                    */
/*                                                                           */
#define VIP_CR_AKE              0x01    /* Bit 0. IACK Responder Enable. When*/
                                        /* set, the VIP becomes PCI IACK     */
                                        /* responder.                        */
#define VIP_CR_CXD              0x02    /* Bit 1. Cache Disable. When set S/G*/
                                        /* accesses are not cached.          */
#define VIP_CR_SGD              0x04    /* Bit 2. External S/G Disable. When */
                                        /* set, VIP ignores external S/G Ram.*/
#define VIP_CR_RST              0x08    /* Bit 3. Internal Reset. When set,  */
                                        /* the VIP performs a subset of the  */
                                        /* external reset.                   */
#define VIP_CR_DSE              0x10    /* Bit 4. DMA Register Snoop Enable. */
                                        /* When set, register VIP_DMACR bit  */
                                        /* 6 will snoop on write accesses to */
                                        /* to VIC_BTCR. IMPLEMENTED PASS 2,  */
                                        /* DISABLED in PASS1                 */
#define VIP_CR_PWE              0x20    /* Bit 5. PCI posted write enable.   */
                                        /* When set, PCI writes that are not */
                                        /* intended for the VIP internal reg-*/
                                        /* isters, will be posted, for later */
                                        /* execution on the Local bus.       */
#define VIP_CR_PWC              0x40    /* Bit 6. Psuedo Write Cycle. This   */
                                        /* bit mirrors register vic_btcr[6]. */
                                        /* Vic_btcr[6] is the block transfer */
                                        /* with local DMA enable, and setting*/
                                        /* this bit signals that the next VME*/
                                        /* write access is in fact a "Pseudo */
                                        /* write cycle". Vip_cr[6] is cleared*/
                                        /* at end of the "Pseudo write cycle"*/
                                        /* If the DMA snoop bit is set,      */
                                        /* vip_cr[6] will be updated on      */
                                        /* writes to vic_btcr[6]. IMPLEMENTED*/
                                        /* PASS 2, DISABLED PASS 1.          */
#define VIP_CR_PBD              0x80    /* Bit 7. PCI Burst DISABLE. When set*/
                                        /* DMA transfers across PCI will be  */
                                        /* made in single masked longwords.  */
                                        /* IMPLEMENTED PASS 2, CLEAR PASS 1  */
#define VIP_CR_DSZ              0x100   /* Bit 8. DMA Word Size. If set, VIP */
                                        /* will assert the local bus WORD*   */
                                        /* signal during DMA initiation      */
                                        /* cycles thereby setting up D16 MBLT*/
                                        /* cycles. If clear, the WORD* signal*/
                                        /* is never asserted.                */
#define VIP_CR_SG_DLY_0         0x000   /* Bits 10-9. SG Delay. The binary   */
#define VIP_CR_SG_DLY_1         0x200   /* value in these two bits is used as*/
#define VIP_CR_SG_DLY_2         0x400   /* number of PCI clock delays used to*/
#define VIP_CR_SG_DLY_3         0x600   /* access SG Ram. Default is 00.     */
#define VIP_CR_SG_DLY_MSK       0x600
#define VIP_CR_SWE              0x800   /* Bit 11. VME Sub Window Enable.    */
                                        /* This bit MUST be set to be PCI    */
                                        /* compliant. When set, the 64MB     */
                                        /* address space specified in        */
                                        /* VME_SUB_WINDOW_BASE configuration */
                                        /* register is enabled.              */

/*                                                                           */
/* vip_besr  VIP  Bus Error/Status Register- R/WOC Cleared on Reset          */
/*                                                                           */
#define VIP_BESR_RSV           0x0001   /* Reserved                          */
#define VIP_BESR_LBE           0x0002   /* Local Bus Error. Set on LBERR     */
                                        /* termination on local bus.         */
#define VIP_BESR_OBE           0x0004   /* Outbound error. Set when o/b or   */
                                        /* VMEbus master access error/con-   */
                                        /* flick is detected. Invalid S/G    */
                                        /* entry or byte enable/swap modes.  */
                                        /* Does not set on PIO writes that   */
                                        /* end in BERR on VME. FIXED PASS 2  */
#define VIP_BESR_ITA           0x0008   /* PCI Initiator Target Abort. Set   */
                                        /* when VIP initiated cycles has been*/
                                        /* aborted.                          */
#define VIP_BESR_PPE           0x0010   /* PCI Parity Error. Set when PCI    */
                                        /* BERR Parity Error is detected     */
                                        /* during VIP access.                */
#define VIP_BESR_CSO           0x0020   /* Configuration Space Overlap.      */
#define VIP_BESR_DWE           0x0040   /* Deferred Write Error. Set when a  */
                                        /* deferred write ends in error on   */
                                        /* the Local bus.                    */
#define VIP_BESR_MSE           0x0080   /* Missed Error. More then one error */
                                        /* has occured since last write to   */
                                        /* to this register. INPROPERLY      */
                                        /* ASSERTS AFTER PIO WRITES WITH BAD */
                                        /* PARITY. FIXED IN PASS 2.          */
#define VIP_BESR_VTA           0x0100   /* Vip Target Abort. Set when VIP    */
                                        /* target aborts a PCI cycle.        */
#define VIP_BESR_LBD           0x0200   /* Local Bus Deadlock. Set on VIC    */
                                        /* DEADLOCK termination on local bus */
#define VIP_BESR_IBE           0x0400   /* Inbound Error. Set when i/b S/G or*/
                                        /* VMEbus slave access error/conflick*/
                                        /* is detected. Inbound access to an */
                                        /* invalid S/G entry, write locked   */
                                        /* page, or User access to a Super-  */
                                        /* visory page will set this bit.    */
                                        /* SETS ONLY ON INBOUND ACCESS TO    */
                                        /* INVALID S/G ENTRY. FIXED PASS 2   */
#define VIP_BESR_WLE           0x0800   /* Write Lock Error. Set on inbound  */
                                        /* write access to a locked page.    */
#define VIP_BESR_SAE           0x1000   /* Supervisory Access Error. Set on  */
                                        /* inbound access to supervisory page*/
#define VIP_BESR_LM1           0x2000   /* Location Monitor 1 Overflow (LM1) */
#define VIP_BESR_LM2           0x4000   /* Location Monitor 2 Overflow (LM2) */
#define VIP_BESR_LM3           0x8000   /* Location Monitor 3 Overflow (LM3) */
#define VIP_BESR_PWT           0x10000  /* Posted Write Set. Set when there  */
                                        /* is outstanding data in write      */
                                        /* buffer. (no interrupt presented)  */
#define VIP_BESR_OCV           0x20000  /* S/G Outbound Cache is Valid. Set  */
                                        /* when there is a valid entry in the*/
                                        /* S/G outbound Cache (no interrupt) */
#define VIP_BESR_VHLT          0x40000  /* Sychronized version of the        */
                                        /* VIC_HALT* signal. This bit is read*/
                                        /* as "1" when the VIC comes out of  */
                                        /* reset.                            */
#define VIP_BESR_MSK        0x0007FFFE  /* BESR mask for valid bits          */
#define VIP_BESR_INT_MSK    0x0000FFFE  /* BESR interruptable bits           */

/*                                                                           */
/* vip_icr  VIP Interrupt Control Register- R/W Cleared on Reset             */
/*                                                                           */
#define VIP_ICR_ERR_INT_RSV    0x0001   /* Reserved                          */
#define VIP_ICR_ERR_INT_LBE    0x0002   /* Error Interrupt Enable for BERR   */
                                        /* Local Bus Error.                  */
#define VIP_ICR_ERR_INT_OBE    0x0004   /* Error Interrupt Enable for BERR   */
                                        /* Outbound Error.                   */
#define VIP_ICR_ERR_INT_ITA    0x0008   /* Error Interrupt Enable for BERR   */
                                        /* PCI Initiator Target Abort.       */
#define VIP_ICR_ERR_INT_PPE    0x0010   /* Error Interrupt Enable for BERR   */
                                        /* PCI Parity Error.                 */
#define VIP_ICR_ERR_INT_CSO    0x0020   /* Error Interrupt Enable for BERR   */
                                        /* Configuration Space Overlap.      */
#define VIP_ICR_ERR_INT_DWE    0x0040   /* Error Interrupt Enable for BERR   */
                                        /* Deferred Write Error.             */
#define VIP_ICR_STAT_INT_MSE   0x0080   /* Status Interrupt Enable for BERR  */
                                        /* Missed Error.                     */
#define VIP_ICR_STAT_INT_VTA   0x0100   /* Status Interrupt Enable for BERR  */
                                        /* VIP Target Abort.                 */
#define VIP_ICR_STAT_INT_LBD   0x0200   /* Status Interrupt Enable for BERR  */
                                        /* Local Bus Deadlock.               */
#define VIP_ICR_STAT_INT_IBE   0x0400   /* Status Interrupt Enable for BERR  */
                                        /* Inbound Error.                    */
#define VIP_ICR_STAT_INT_WLE   0x0800   /* Status Interrupt Enable for BERR  */
                                        /* Write Lock Error.                 */
#define VIP_ICR_STAT_INT_SAE   0x1000   /* Status Interrupt Enable for BERR  */
                                        /* Supervisor Access Error.          */
#define VIP_ICR_STAT_INT_LM1   0x2000   /* Status Interrupt Enable for BERR  */
                                        /* Location Monitor 1.               */
#define VIP_ICR_STAT_INT_LM2   0x4000   /* Status Interrupt Enable for BERR  */
                                        /* Location Monitor 2.               */
#define VIP_ICR_STAT_INT_LM3   0x8000   /* Status Interrupt Enable for BERR  */
                                        /* Location Monitor 3.               */
/*                                                                           */
/* vip_irr  VIP Interrupt Reason Register- Read Only - Cleared on Reset      */
/*     The vip_irr, when read, has exactly the same meaning as a PCI IACK    */
/*     cycle (except that it is independent of the status of the IACK        */
/*     responder enable bit in the the vip_cr).                              */
/*                                                                           */
/*     When read, a Local Bus IACK cycle is run. Once the Local Bus IACK     */
/*     cycle completes, the PCI cycle TRDY'd with the following data. Bits   */
/*     [31:11] are read as all zeroes, bits [10:8] will reflect the current  */
/*     value on the VIC IPL lines and bits [7:0] will reflect the 8 bit      */
/*     interrupt vector returned (in response to the Local Bus IACK cycle.   */
/*                                                                           */
/*     An exception to this is when the value represented by the IPL<2:0>    */
/*     lines is less then or equal to the value in vip_hwipl register, no    */
/*     local bus IACK cycle will take place and bytes 1 and 0 will bith be   */
/*     read as zero. The vip_hwipl value may be updated with the VIC64 IPL   */
/*     values after a local bus IACK cycle, if this is enabled.              */
/*                                                                           */
#define VIP_IRR_VEC_MSK        0x00FF   /* 8 bit interrupt vector returned   */
#define VIP_IRR_IPL_MSK        0x0700   /* 3 bit current VIC IPL lines       */
#define VIP_IRR_MSK            0x07FF   /* Valid mask for IRR register       */

/*                                                                           */
/* vip_hwipl  VIP Hardware IPL Register, R/W - Cleared on Reset              */
/*     The interrupt output SYSIRQ is asserted when the numeric value of the */
/*     VIC IPL lines exceeds the value in bits [2:0]. Vip_hwipl[2:0] are used*/
/*     as a hardware interrupt priority level and will cause the masking of  */
/*     all interrupts at the same or lower priority. These bits may also be  */
/*     written by the processor.                                             */
/*                                                                           */
/*     When bit 3 is clear, any successful local bus IACK cycle initiated by */
/*     the VIP will update bits [2:0] with the numeric value of the VIC IPL  */
/*     lines. When bit 3 is set, bits [2:0] are unaffected by VIP initiated  */
/*     IACK cycles on the local bus.                                         */
/*                                                                           */
/*                                                                           */
#define VIP_HWIPL_IPL_MSK      0x0007   /* IPL Mask [2:0]. Used to set the   */
                                        /* threshold for the generation of   */
                                        /* SYSIRQ to the VIP.                */
#define VIP_HWIPL_IUD          0x0008   /* Disable IPL Update. When set, the */
                                        /* IPL [2:0] will no longer be up-   */
                                        /* dated on local bus IACK cycles.   */
#define VIP_HWIPL_CIPL_MSK     0x0070   /* Current IPL [2:0]. These bits re- */
                                        /* flect the current state of the VIC*/
                                        /* IPL pins. Read Only.              */
#define VIP_HWIPL_MSK          0x007F   /* Register mask of valid bits       */

/*                                                                           */
/* vip_diagcsr VIP Diagnostic Control/Status Register, R/W - Cleared on Reset*/
/*                                                                           */
#define VIP_DIAGCSR_FWPE       0x0001   /* Force Write Parity Error on the   */
                                        /* next PCI Target write             */
#define VIP_DIAGCSR_FRPE       0x0002   /* Force Read  Parity Error on the   */
                                        /* next PCI Target Read              */
/*                                                                           */
/* vip_lmcsr VIP Location Monitor CSR, R/W - Cleared on Reset                */
/*    Each of the count values is incremented when referenced in an inbound  */
/*    scatter gather access as part of a VME slave access.  When a value of  */
/*    seven is reached in any count, it will next go to zero and the corre-  */
/*    sponding location monitor overflow bit will be set. An overflow can    */
/*    cause an interrupt if the appropriate bit is set in the vip_icr.       */
/*                                                                           */
/*                                                                           */
#define VIP_LMCSR_LM1_MSK      0x0007   /* 3 bit binary value - LM1          */
#define VIP_LMCSR_OV1          0x0008   /* Location Monitor 1 overflow       */
#define VIP_LMCSR_LM2_MSK      0x0070   /* 3 bit binary value - LM2          */
#define VIP_LMCSR_OV2          0x0080   /* Location Monitor 2 overflow       */
#define VIP_LMCSR_LM3_MSK      0x0700   /* 3 bit binary value - LM3          */
#define VIP_LMCSR_OV3          0x0800   /* Location Monitor 3 overflow       */

/*                                                                           */
/* vip_obisgabr VIP Outbound Internal S/G Address Base Register,             */
/*                                                     R/W - Cleared on Reset*/
/*    This register sets the base address for the internally mapped, outbound*/
/*    page into the VME address space.It is used, in conjunction with the    */
/*    vip_obisgword register, to define a variable size window for outbound  */
/*    cycles. This window will have a single mapping and does not require the*/
/*    use of external scatter gather memory.                                 */
/*                                                                           */
                                        /* Bits 31:29. Ignored               */
                                        /* Bits 28:18. Outbound Internal SG  */
                                        /*             Address Base.         */
                                        /* Bits 17:0.  Ignored.              */

/*                                                                           */
/* vip_obisgmsk VIP Outbound Internal S/G Mask, R/W - Cleared on Reset       */
/*                                                                           */
                                        /* Bits 17:0.  Ignored.              */
                                        /* Bits 28:18. Outbound Internal SG  */
                                        /* Address Mask. When clear, the     */
                                        /* corresponding bit of the PCI      */
                                        /* address is used in detection of an*/
                                        /* internal scatter gather hit.      */
                                        /* Bits 31:29. Ignored               */
#define VIP_OBISGMSK_SGE       0x8000   /* Internal Outbound Scatter Gather  */
                                        /* Enable.                           */

/*                                                                           */
/* vip_obisword VIP Outbound Internal S/G Word, R/W - Cleared on Reset       */
/*                                                                           */
#define VIP_OBISGWORD_IGNORED1   0x001F /* ignored                           */
#define VIP_OBISGWORD_VALID      0x0020 /* Valid Bit                         */
#define VIP_OBISGWORD_SWAP_NONE  0x0000 /* no swap                           */
#define VIP_OBISGWORD_SWAP_BYTE  0x0040 /* BYTE swap                         */
#define VIP_OBISGWORD_SWAP_WORD  0x0080 /* WORD size swap                    */
#define VIP_OBISGWORD_SWAP_LONG  0x00C0 /* LONGWORD swap                     */
#define VIP_OBISGWORD_SWAP_QUAD  0x01C0 /* QUAD size swap                    */
#define VIP_OBISGWORD_RMW        0x0200 /* RMW enable                        */
#define VIP_OBISGWORD_AS_A32     0x0400 /* a32                               */
#define VIP_OBISGWORD_AS_A16     0x0800 /* a16                               */
#define VIP_OBISGWORD_AS_A24     0x0C00 /* a24                               */
#define VIP_OBISGWORD_FUNC_UDATA 0      /* user data                         */
#define VIP_OBISGWORD_FUNC_UPROG 0x1000 /* USER program                      */
#define VIP_OBISGWORD_FUNC_SDATA 0x2000 /* SUPERVISORY data                  */
#define VIP_OBISGWORD_FUNC_SPROG 0x3000 /* SUPERVISORY program               */
#define VIP_OBISGWORD_IGNORED2  0x3C000 /* ignored                           */
#define VIP_OBISGWORD_VMEADR 0xFFFC0000 /* vme address                       */

#define VIP_OBISGWORD_SWAP_MSK   0x01C0 /* swap mode mask                    */
#define VIP_OBISGWORD_AS_MSK     0x0C00 /* address size (modifier) mask      */
#define VIP_OBISGWORD_FC_MSK     0x3000 /* function code mask                */
#define VIP_OBISGWORD_MSK    0xFFFC3FE0 /* Mask of valid obisgword bits      */

/*                                                                           */
/* vip_ibisgmsk VIP Inbound Internal S/G Mask, R/W - Cleared on Reset        */
/*                                                                           */
                                        /* Bits 12:0.  Ignored.              */
                                        /* Bits 30:13. Inbound Internal SG   */
                                        /* Address Mask. When clear, the     */
                                        /* corresponding bit of the Local Bus*/
                                        /* address is masked from the compas-*/
                                        /* son.                              */
                                        /* Bits31.  Ignored                  */

/*                                                                           */
/* vip_ibisword VIP Inbound Internal S/G Word, R/W - Cleared on Reset        */
/*                                                                           */
#define VIP_IBISGWORD_IGNORED1   0x001F /* ignored                           */
#define VIP_IBISGWORD_VALID      0x0020 /* Valid Bit                         */
#define VIP_IBISGWORD_SWAP_NONE  0x0000 /* no swap                           */
#define VIP_IBISGWORD_SWAP_BYTE  0x0040 /* BYTE swap                         */
#define VIP_IBISGWORD_SWAP_WORD  0x0080 /* WORD size swap                    */
#define VIP_IBISGWORD_SWAP_LONG  0x00C0 /* LONGWORD swap                     */
#define VIP_IBISGWORD_SWAP_QUAD  0x01C0 /* QUAD size swap                    */
#define VIP_IBISGWORD_WLK        0x0200 /* Write Lock                        */
#define VIP_IBISGWORD_SUP        0x0400 /* Supervisory Access                */
#define VIP_IBISGWORD_IO         0x0800 /* I/O Mapping                       */
#define VIP_IBISGWORD_LM_NONE    0x0000 /* No location monitor detection     */
#define VIP_IBISGWORD_LM1        0x1000 /* Location Monitor 1                */
#define VIP_IBISGWORD_LM2        0x2000 /* Location Monitor 2                */
#define VIP_IBISGWORD_LM3        0x3000 /* Location Monitor 3                */
#define VIP_IBISGWORD_ADD    0xFFFFC000 /* pci address                       */

#define VIP_IBISGWORD_SWAP_MSK   0x01C0 /* swap mode mask                    */
#define VIP_IBISGWORD_LM_MSK     0x3000 /* Location monitor mask             */
#define VIP_IBISGWORD_MSK    0xFFFFFFE0 /* Mask of valid ibisgword bits      */

/*                                                                           */
/* vip_sgcchix VIP Scatter Gather Index Cache (outbound), Read Only          */
/*                                                                           */
                                        /* Bits 17:0. Ignored.               */
                                        /* Bits 28:18. Scatter Gather Index  */
                                        /* Cache. Latched PCI address bits   */
                                        /* [28:18].                          */
					/* Ignored.                          */

/*                                                                           */
/* vip_sgcwrd VIP Scatter Gather Word Cache (outbound), Read Only            */
/*                                                                           */
#define VIP_SGCWRD_IGN1          0x001F /* Ignored.                          */
#define VIP_SGCWRD_VALID         0x0020 /* Valid                             */
#define VIP_SGCWRD_SWAP_NONE     0x0000 /* no swap                           */
#define VIP_SGCWRD_SWAP_BYTE     0x0040 /* BYTE swap                         */
#define VIP_SGCWRD_SWAP_WORD     0x0080 /* WORD size swap                    */
#define VIP_SGCWRD_SWAP_LONG     0x00C0 /* LONGWORD swap                     */
#define VIP_SGCWRD_SWAP_QUAD     0x01C0 /* QUAD size swap                    */
#define VIP_SGCWRD_RME           0x0200 /* Read Modify Write Enable          */
#define VIP_SGCWRD_AS_A32        0x0400 /* a32                               */
#define VIP_SGCWRD_AS_A16        0x0800 /* a16                               */
#define VIP_SGCWRD_AS_A24        0x0C00 /* a24                               */
#define VIP_SGCWRD_FUNC_UDATA    0x0000 /* user data                         */
#define VIP_SGCWRD_FUNC_UPROG    0x1000 /* USER program                      */
#define VIP_SGCWRD_FUNC_SDATA    0x2000 /* SUPERVISORY data                  */
#define VIP_SGCWRD_FUNC_SPROG    0x3000 /* SUPERVISORY program               */
#define VIP_SGCWRD_IGN2         0x3C000 /* Ignored.                          */
#define VIP_SGCWRD_VMEADR    0xFFFC0000 /* vme address                       */

#define VIP_SGCWRD_SWP_MSK       0x01C0 /* Swap mode                         */
#define VIP_SGCWRD_AM_MSK        0x0C00 /* Address modifier mask             */
#define VIP_SGCWRD_FC_MSK        0x3000 /* Function Code Mask                */

/*                                                                           */
/* vip_pciertadr VIP PCI Error Target Address Register, RO - Clear on reset  */
/*      In the event of an error during a PCI target access, PCI address     */
/*      bits [31:2] will be loaded into vip_pciertadr[31:2]. Subsequent error*/
/*      addresses will not be loaded until vip_besr register bits [7:0] have */
/*      been cleared.                                                        */
/*                                                                           */
#define VIP_PCIERTADR_MSK    0xFFFFFFFC /* Valid bits for vip_pciertadr Reg  */

/*                                                                           */
/* vip_pciertcbe VIP PCI Error Target Command/Byte Enable Register, RO       */
/*      In the event of an error during a target PCI access, the PCI command */
/*      is loaded into vip_pciertcbe[3:0], the PCI byte enable bits are      */
/*      loaded inti vip_pciertcbe[7:4]. This register will not be overwritten*/
/*      until the error bits in vip_besr are cleared.                        */
/*      VIP_PCIERTCBE REGISTER NOT IMPLEMENTED FOR PASS 1, WILL RETURN RANDOM*/
/*      DATA. IT WILL BE FIXED FOR PASS 2.                                   */
/*                                                                           */
#define VIP_PCIERTCBE_PCICMD_MSK 0x000F /* PCI command during error          */
#define VIP_PCIERTCBE_PCIBE_MSK  0x00F0 /* PCI byte enables during error     */
#define VIP_PCIERTCBE_MSK        0x00FF /* Mask of valid bits during read    */

/*                                                                           */
/* vip_pcieriadr VIP PCI Error Target Address Register, RO - Clear on Reset  */
/*      In the event of an error during a PCI initiator access, PCI address  */
/*      bits [31:2] will be loaded into vip_pcieriadr[31:2]. Subsequent error*/
/*      addresses will not be loaded until the error bits in vip_besr regis- */
/*      ter have been cleared.                                               */
/*      VIP_PCIERIADR REGISTER NOT IMPLEMENTED FOR PASS 1. WILL RETURN RANDOM*/
/*      DATA. WILL BE FIXED FOR PASS 2.                                      */
/*                                                                           */
#define VIP_PCIERIADR_MSK    0xFFFFFFFC /* Valid bits for vip_pcieriadr Reg  */

/*                                                                           */
/* vip_leradr VIP Local Bus Error Address Register, RO - Clear on Reset      */
/*      In the event of an error on the local bus, the starting local bus    */
/*      address will be loaded into vip_leradr[28:0]. This will represent the*/
/*      non-translated VMEbus address[28:1] and the local bus address bit 0  */
/*      as driven by the VIC64 and CY7C964 transceivers, during the local bus*/
/*      phase of the cycle.                                                  */
/*      Bits[31] and [30] contain the AM5 and AM2 respectively from the      */
/*      VMEbus during the SG lookup phase of the slave transfer. If the local*/
/*      bus error occured during a local DMA driven MBLT, AM bits don't apply*/
/*      If the error occured during the PCI phase of a SBLT cycle, the PCI   */
/*      Error Initiator Address register can be used with this register to   */
/*      deduce the failing VME address.                                      */
/*      In Medulla, the bits[30:31] and this rgister will indicate which of  */
/*      the SG entries was used for the error transfer.                      */
/*      This register will not be overwritten until all error bits in the    */
/*      vip_besr register have been cleared.                                 */
/*                                                                           */
#define VIP_LERADR_ADR_MSK 0x3FFFFFFF /* Local bus error address             */
#define VIP_LERADR_AM_MSK  0xC0000000 /* Address modifier mask               */
#define VIP_LERADR_AM5     0x80000000
#define VIP_LERADR_AM2     0x40000000

#endif /* _EBV10_VME_H */
