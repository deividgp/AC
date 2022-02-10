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
 * @(#)$RCSfile: ebv10.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1995/04/14 18:04:00 $
 */

#ifndef	_ARCH_ALPHA_HAL_EBV10_H
#define	_ARCH_ALPHA_HAL_EBV10_H

#include <machine/machlimits.h>			/* include Alpha AXP machine limits	*/


/* 
 * i/o space addresses for miscellaneous hardware registers
 */

#define	EBV10_CCLK		   0x2000	/* dismiss interval timer interrupt	*/
#define	EBV10_DSPL		   0x2400	/* module display control register	*/
#define	EBV10_MCFG		   0x2800	/* module configuration register	*/
#define	EBV10_MCFG2		   0x2900	/* module configuration register 2	*/
#define	EBV10_MCTL		   0x2c00	/* module control register		*/
#define	EBV10_MRST		   0x3000	/* module reset reason register		*/
#define	EBV10_TIMERBASE		   0x4000	/* base of timer registers		*/
#define	EBV10_UARTBASE		   0x6000	/* base of uart registers		*/
#define	EBV10_TODBASE		   0x8000	/* base of tod clock registers 		*/
											

/*
 * module display control register (EBV10_DSPL)
 */

#define EBV10_DSPL_OUTPUT	   0x007f	/* display output character		*/

#define EBV10_DSPL_BRIGHT	   0x0080	/* display brightness			*/
#define EBV10_DSPL_BRIGHT_NORMAL   0x0000	/*   0 = normal display brightness	*/
#define EBV10_DSPL_BRIGHT_HI	   0x0080	/*   1 = high display brightness	*/


/*
 * module configuration register (EBV10_MCFG)
 */

#define EBV10_MCFG_MEMID	   0x0007	/* memory card id			*/
#define EBV10_MCFG_MEMID_NONE	   0x0000	/*   0 = no memory card			*/
#define EBV10_MCFG_MEMID_8MB	   0x0002	/*   2 = 8mb memory card		*/
#define EBV10_MCFG_MEMID_16MB	   0x0006	/*   6 = 16mb memory card		*/
#define EBV10_MCFG_MEMID_32MB	   0x0007	/*   7 = 32mb memory card		*/
#define EBV10_MCFG_MEMID_64MB	   0x0004	/*   4 = 64mb memory card		*/
#define EBV10_MCFG_MEMID_128MB	   0x0005	/*   5 = 128mb memory card		*/

#define EBV10_MCFG_MODID	   0x0018	/* module id				*/
#define EBV10_MCFG_MODID_64	   0x0008	/*   1 = AXPvme 64 			*/
#define EBV10_MCFG_MODID_160	   0x0010	/*   2 = AXPvme 160 			*/
#define EBV10_MCFG_MODID_224	   0x0018	/*   3 = AXPvme 66/100/165/231/264 	*/

#define EBV10_MCFG_TERMPWR	   0x0020	/* scsi termpwr present (via P2 pin)	*/
#define EBV10_MCFG_BC_SCSI	   0x0040	/* backup cache/SCSI present		*/
#define EBV10_MCFG_PCI0OPT	   0x0080	/* pci0 option (in slot #4) present	*/


/*
 * module configuration register 2 (EBV10_MCFG2)
 */

#define EBV10_MCFG2_FROM_WINSEL	   0x0003	/* flash rom window select		*/
#define EBV10_MCFG2_FROM_WENABL	   0x0004	/* flash rom write enable		*/


/*
 * module control register (EBV10_MCTL)
 */

#define EBV10_MCTL_INTRSEL	   0x0002	/* interrupt select			*/
#define EBV10_MCTL_INTRSEL_VME	   0x0000	/*   0 = select vmebus irq 1,2,3	*/
#define EBV10_MCTL_INTRSEL_PCI0	   0x0002	/*   1 = select pci0 b,c,d		*/

#define EBV10_MCTL_PCI0_ARBSEL	   0x000c	/* pci0 arbitration selection		*/
#define EBV10_MCTL_PCI0_ARBSEL_0   0x0000	/*   0 = lca, ni, scsi, pci0-opt*, vme	*/
#define EBV10_MCTL_PCI0_ARBSEL_1   0x0004	/*   1 = pci0-opt*, lca, vme, ni, scsi	*/
#define EBV10_MCTL_PCI0_ARBSEL_2   0x0008	/*   2 = vme, lca, pci0-opt*, ni, scsi	*/
#define EBV10_MCTL_PCI0_ARBSEL_3   0x000c	/*   3 = vme, lca, pci0-opt*, ni, scsi	*/
						/* (* refers to pci0 option in slot #4)	*/

#define EBV10_MCTL_CPU_IENABL	   0x0010	/* processor interrupt enable		*/
#define EBV10_MCTL_WDT_RENABL	   0x0020	/* watchdog timer reset enable		*/

#define EBV10_MCTL_PARKSEL	   0x00c0	/* pci0 park device select		*/
#define EBV10_MCTL_PARKSEL_LCA	   0x0000	/*   0 = park with lca (default)	*/
#define EBV10_MCTL_PARKSEL_NI	   0x0040	/*   1 = park with ni			*/
#define EBV10_MCTL_PARKSEL_OPT	   0x0080	/*   2 = park with pci0 option, slot #4	*/
#define EBV10_MCTL_PARKSEL_VME	   0x00c0	/*   3 = park with vme			*/
						

/*
 * module reset reason register (EBV10_MRST)
 */

#define EBV10_MRST_WATCHDOG	   0x0001	/* reset due to watchdog timer timeout	*/
#define EBV10_MRST_FPSWITCH	   0x0002	/* reset due to front panel switch 	*/
#define EBV10_MRST_VMERESET	   0x0004	/* reset due to vmebus sysreset		*/
#define EBV10_MRST_POWERUP	   0x0008	/* reset due to power-up		*/
#define EBV10_MRST_DIP		   0x0010	/* diagnostic in progress		*/


/*
 * isa0 interrupt request constants
 */

#define EBV10_ISA0_IRQ_UART	   4		/* uart irq for isa0			*/
#define EBV10_ISA0_IRQ_RT_TIMER	   5		/* realtime interval timer irq for isa0	*/
#define EBV10_ISA0_IRQ_RT_PERIODIC 6		/* realtime periodic timer irq for isa0 */


/*
 * pci0 slot number constants
 */

#define EBV10_MIN_PCI0_SLOT        0		/* min. slot no. for pci0 (ad<11>)	*/
#define EBV10_MAX_PCI0_SLOT        5		/* max. slot no. for pci0 (ad<16>)	*/
#define EBV10_NUM_PCI0_SLOT        6		/* no. of available pci0 slots		*/

#define EBV10_PCI0_SLOT_VME	   0		/* vmebus slot no. for pci0 (ad<11>)	*/
#define EBV10_PCI0_SLOT_NI	   1		/* ni slot no. for pci0 (ad<12>)	*/
#define EBV10_PCI0_SLOT_SCSI	   2		/* scsi slot no. for pci0 (ad<13>)	*/
#define EBV10_PCI0_SLOT_SIO        3		/* sio slot no. for pci0 (ad<14>)	*/
#define EBV10_PCI0_SLOT_OPT1	   4		/* option #1 slot no. for pci0 (ad<15>) */
#define EBV10_PCI0_SLOT_OPT2	   5		/* option #2 slot no. for pci0 (ad<16>) */
						/* (available only on Raytheon SBC's)	*/


/*
 * interrupt vector offsets & constants
 */

#define	EBV10_MIN_IOVEC		   0x0800	/* min. interrupt vector offset		*/
#define	EBV10_MAX_IOVEC		   0x1ff0	/* max. interrupt vector offset		*/
#define	EBV10_NUM_IOVEC		   384		/* no. of available interrupt vectors	*/

#define	EBV10_IOVEC_WATCHDOG	   0x0820	/* watchdog timer timeout interrupt	*/
#define	EBV10_IOVEC_PCI0_OPT1_A	   0x0830	/* pci0 option slot #1 a interrupt	*/
#define	EBV10_IOVEC_UART	   0x0840	/* uart interrupt (channel a/b)		*/
#define	EBV10_IOVEC_RT_TIMER	   0x0850	/* realtime interval timer interrupt    */
#define	EBV10_IOVEC_NI		   0x0860	/* network interface interrupt 		*/
#define	EBV10_IOVEC_SCSI	   0x0870	/* scsi interrupt 			*/
#define	EBV10_IOVEC_VME_RESET	   0x0880	/* vmebus reset interrupt		*/
#define	EBV10_IOVEC_AUTO_IRQ1	   0x0890	/* vmebus irq1 interrupt (autovector)	*/
#define	EBV10_IOVEC_PCI0_OPT1_B	   0x0890	/* pci0 option slot #1 b interrupt 	*/
#define	EBV10_IOVEC_AUTO_IRQ2	   0x08a0	/* vmebus irq2 interrupt (autovector)	*/
#define	EBV10_IOVEC_PCI0_OPT1_C	   0x08a0	/* pci0 option slot #1 c interrupt	*/
#define	EBV10_IOVEC_AUTO_IRQ3	   0x08b0	/* vmebus irq3 interrupt (autovector)	*/
#define	EBV10_IOVEC_PCI0_OPT1_D	   0x08b0	/* pci0 option slot #1 d interrupt	*/
#define	EBV10_IOVEC_AUTO_IRQ4	   0x08c0	/* vmebus irq4 interrupt (autovector)	*/
#define	EBV10_IOVEC_AUTO_IRQ5	   0x08d0	/* vmebus irq5 interrupt (autovector)	*/
#define	EBV10_IOVEC_AUTO_IRQ6	   0x08e0	/* vmebus irq6 interrupt (autovector)	*/
#define	EBV10_IOVEC_AUTO_IRQ7	   0x08f0	/* vmebus irq7 interrupt (autovector)	*/
#define	EBV10_IOVEC_PCI0_OPT2_A	   0x0900	/* pci0 option slot #2 a interrupt 	*/
#define	EBV10_IOVEC_PCI0_OPT2_B	   0x0910	/* pci0 option slot #2 b interrupt 	*/
#define	EBV10_IOVEC_PCI0_OPT2_C	   0x0920	/* pci0 option slot #2 c interrupt 	*/
#define	EBV10_IOVEC_PCI0_OPT2_D	   0x0930	/* pci0 option slot #2 d interrupt	*/

#define	EBV10_IOVEC_VME_BASE	   0x1000	/* start of vmebus interrupts 		*/
#define	EBV10_IOVEC_LOC_MONITOR	   0x1020	/* vmebus location monitor interrupt    */
#define	EBV10_IOVEC_RT_PERIODIC	   0x1030	/* realtime periodic timer interrupt    */
#define	EBV10_IOVEC_VIP_ERR	   0x1070	/* vip error interrupt		        */
#define	EBV10_IOVEC_VIC_ACFAIL	   0x1080	/* vic a/c failed interrupt		*/
#define	EBV10_IOVEC_VIC_WPFAIL	   0x1090	/* vic writepost failed interrupt	*/
#define	EBV10_IOVEC_VIC_ARBTO	   0x10a0	/* vic arbitration timeout interrupt    */
#define	EBV10_IOVEC_VIC_SYSFAIL	   0x10b0	/* vic sysfail interrupt	        */
#define	EBV10_IOVEC_VME_IACK	   0x10c0	/* vmebus iack interrupt	        */
#define	EBV10_IOVEC_VME_DMA	   0x10d0	/* vmebus dma status interrupt	        */

#define	EBV10_IOVEC_VME_ICGS0	   0x1100	/* vmebus ip global switch 0 interrupt  */
#define	EBV10_IOVEC_VME_ICGS1	   0x1110	/* vmebus ip global switch 1 interrupt  */
#define	EBV10_IOVEC_VME_ICGS2	   0x1120	/* vmebus ip global switch 2 interrupt  */
#define	EBV10_IOVEC_VME_ICGS3	   0x1130	/* vmebus ip global switch 3 interrupt  */
#define	EBV10_IOVEC_VME_ICMS0	   0x1140	/* vmebus ip local switch 0 interrupt   */
#define	EBV10_IOVEC_VME_ICMS1	   0x1150	/* vmebus ip local switch 1 interrupt   */
#define	EBV10_IOVEC_VME_ICMS2	   0x1160	/* vmebus ip local switch 2 interrupt   */
#define	EBV10_IOVEC_VME_ICMS3	   0x1170	/* vmebus ip local switch 3 interrupt   */

#define	EBV10_IOVEC_VME_END	   0x1ff0	/* end of vmebus interrupts 		*/


/*
 * hardware interrupt enable/disable masks
 */

#define	EBV10_INTR_ALL		   (ULONG_MAX)	/* all hardware interrupts	        */
#define	EBV10_INTR_HARDCLOCK	   (1UL <<  1)	/* hardware interval timer interrupt    */
#define	EBV10_INTR_PCI0_OPT1_A 	   (1UL <<  3)	/* pci0 option slot #1 a interrupt	*/
#define	EBV10_INTR_UART		   (1UL <<  4)	/* uart interrupt (channel a/b)	        */
#define	EBV10_INTR_RT_TIMER	   (1UL <<  5)	/* realtime interval timer interrupt    */
#define	EBV10_INTR_NI		   (1UL <<  6)	/* network interface interrupt	        */
#define	EBV10_INTR_SCSI		   (1UL <<  7)	/* scsi interrupt		        */

#define	EBV10_INTR_VME_RESET	   (1UL <<  8)	/* vmebus reset interrupt	        */
#define	EBV10_INTR_AUTO_IRQ1	   (1UL <<  9)	/* vmebus irq1 interrupt (autovector)   */
#define	EBV10_INTR_PCI0_OPT1_B	   (1UL <<  9)	/* pci0 option slot #1 b interrupt 	*/
#define	EBV10_INTR_AUTO_IRQ2	   (1UL << 10)	/* vmebus irq2 interrupt (autovector)   */
#define	EBV10_INTR_PCI0_OPT1_C	   (1UL << 10)	/* pci0 option slot #1 c interrupt	*/
#define	EBV10_INTR_AUTO_IRQ3	   (1UL << 11)	/* vmebus irq3 interrupt (autovector)   */
#define	EBV10_INTR_PCI0_OPT1_D	   (1UL << 11)	/* pci0 option slot #1 d interrupt	*/
#define	EBV10_INTR_AUTO_IRQ4	   (1UL << 12)	/* vmebus irq4 interrupt (autovector)   */
#define	EBV10_INTR_AUTO_IRQ5	   (1UL << 13)	/* vmebus irq5 interrupt (autovector)   */
#define	EBV10_INTR_AUTO_IRQ6	   (1UL << 14)	/* vmebus irq6 interrupt (autovector)   */
#define	EBV10_INTR_AUTO_IRQ7	   (1UL << 15)	/* vmebus irq7 interrupt (autovector)   */

#define	EBV10_INTR_LIRQ2	   (1UL << 18)	/* vic local irq2 interrupt	        */
#define	EBV10_INTR_LOC_MONITOR	   (1UL << 18)	/* vmebus location monitor interrupt    */
#define	EBV10_INTR_LIRQ3	   (1UL << 19)	/* vic local irq3 interrupt	        */
#define	EBV10_INTR_RT_PERIODIC	   (1UL << 19)	/* realtime periodic timer interrupt    */
#define	EBV10_INTR_LIRQ7	   (1UL << 23)	/* vic local irq7 interrupt	        */
#define	EBV10_INTR_VIP_ERR	   (1UL << 23)	/* vip error interrupt		        */

#define	EBV10_INTR_VME_IRQ1	   (1UL << 25)	/* vmebus irq1 interrupt	        */
#define	EBV10_INTR_VME_IRQ2	   (1UL << 26)	/* vmebus irq2 interrupt	        */
#define	EBV10_INTR_VME_IRQ3	   (1UL << 27)	/* vmebus irq3 interrupt	        */
#define	EBV10_INTR_VME_IRQ4	   (1UL << 28)	/* vmebus irq4 interrupt	        */
#define	EBV10_INTR_VME_IRQ5	   (1UL << 29)	/* vmebus irq5 interrupt	        */
#define	EBV10_INTR_VME_IRQ6	   (1UL << 30)	/* vmebus irq6 interrupt	        */
#define	EBV10_INTR_VME_IRQ7	   (1UL << 31)	/* vmebus irq7 interrupt	        */

#define	EBV10_INTR_VME_DMA	   (1UL << 36)	/* vmebus dma status interrupt	        */
#define	EBV10_INTR_VME_IACK	   (1UL << 37)	/* vmebus iack interrupt	        */
#define	EBV10_INTR_WATCHDOG	   (1UL << 38)	/* watchdog timer timeout interrupt	*/

#define	EBV10_INTR_VIC_SYSFAIL	   (1UL << 40)	/* vic sysfail interrupt	        */
#define	EBV10_INTR_VIC_ARBTO	   (1UL << 41)	/* vic arbitration timeout interrupt    */
#define	EBV10_INTR_VIC_WPFAIL	   (1UL << 42)	/* vic writepost failed interrupt       */
#define	EBV10_INTR_VIC_ACFAIL	   (1UL << 43)	/* vic a/c failed interrupt		*/
#define	EBV10_INTR_VME_ICMS0	   (1UL << 44)	/* vmebus ip local switch 0 interrupt   */
#define	EBV10_INTR_VME_ICMS1	   (1UL << 45)	/* vmebus ip local switch 1 interrupt   */
#define	EBV10_INTR_VME_ICMS2	   (1UL << 46)	/* vmebus ip local switch 2 interrupt   */
#define	EBV10_INTR_VME_ICMS3	   (1UL << 47)	/* vmebus ip local switch 3 interrupt   */

#define	EBV10_INTR_VME_ICGS0	   (1UL << 48)	/* vmebus ip global switch 0 interrupt  */
#define	EBV10_INTR_VME_ICGS1	   (1UL << 49)	/* vmebus ip global switch 1 interrupt  */
#define	EBV10_INTR_VME_ICGS2	   (1UL << 50)	/* vmebus ip global switch 2 interrupt  */
#define	EBV10_INTR_VME_ICGS3	   (1UL << 51)	/* vmebus ip global switch 3 interrupt  */
#define	EBV10_INTR_PCI0_OPT2_A	   (1UL << 52)	/* pci0 option slot #2 a interrupt	*/
#define	EBV10_INTR_PCI0_OPT2_B	   (1UL << 53)	/* pci0 option slot #2 b interrupt	*/
#define	EBV10_INTR_PCI0_OPT2_C	   (1UL << 54)	/* pci0 option slot #2 c interrupt 	*/
#define	EBV10_INTR_PCI0_OPT2_D	   (1UL << 55)	/* pci0 option slot #2 d interrupt	*/

#endif	/* _ARCH_ALPHA_HAL_EBV10 */
