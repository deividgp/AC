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
 * @(#)$RCSfile: ebv14.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1996/05/15 21:25:48 $
 */
#ifndef	_ARCH_ALPHA_HAL_EBV14_H
#define	_ARCH_ALPHA_HAL_EBV14_H

#include <sys/types.h>

/*
 * EBV14+ SYSTEM ADDRESS MAP - same as cabriolet (eb64p)
 *
 * The 34-bit processor physical address space is mapped into memory 
 * and I/O space addresses as follows:
 *
 *   0 0000 0000 +--------------------------------+
 *               |     Cacheable Memory Space     |   4 GB
 *   1 0000 0000 +--------------------------------+
 *               |   Non-Cacheable Memory Space   |   2 GB
 *   1 8000 0000 +--------------------------------+
 *               |   DECchip 21071-CA CSR Space   | 512 MB 
 *   1 A000 0000 +--------------------------------+
 *               |   DECchip 21071-DA CSR Space   | 256 MB
 *   1 B000 0000 +--------------------------------+
 *               |   PCI Interrupt Acknowledge    |
 *               |          Special Cycle         | 256 MB
 *               |             Space              |
 *   1 C000 0000 +--------------------------------+
 *               |      PCI Sparse I/O Space      | 512 MB
 *   1 E000 0000 +--------------------------------+
 *               |    PCI Configuration Space     | 512 MB
 *   2 0000 0000 +--------------------------------+
 *               |    PCI Sparse Memory Space     |   4 GB
 *   3 0000 0000 +--------------------------------+
 *               |     PCI Dense Memory Space     |   4 GB
 *   3 FFFF FFFF +--------------------------------+
 *
 * The following constants are defined in apecs.h and are included 
 * here for completeness:
 *
 * #define MAIN_MEM_SPACE_BASE		0x0
 * #define FRAME_BUFFER_MEM_SPACE	0x100000000
 * #define APECS_BUSIO_BASE		0x1c0000000
 * #define APECS_PCI_CONFIG_BASE	0x1e0000000
 * #define APECS_BUSMEM_BASE_SPARSE	0x200000000
 * #define APECS_BUSMEM_BASE_DENSE	0x300000000
 *
 * #define BUSIO_BASE		APECS_BUSIO_BASE
 * #define BUSMEM_BASE		APECS_BUSMEM_BASE_SPARSE
 * #define BUSMEM_SPARSE_BASE	APECS_BUSMEM_BASE_SPARSE
 * #define BUSMEM_DENSE_BASE	APECS_BUSMEM_BASE_DENSE
 *
 * Alpha I/O Architecture standard address swizzle:
 *
 * #define IO_SHIFT	(5)
 * #define WIDTH_MASK	0x18
 * #define WIDTH_SHIFT	(IO_SHIFT - 2)
 * #define Wrd       	((long)1 << (WIDTH_SHIFT))
 * #define Tri		((long)2 << (WIDTH_SHIFT))
 * #define Lng       	((long)3 << (WIDTH_SHIFT))
 * #define Quad		((long)0 << (WIDTH_SHIFT))
 *
 */

#define	IS_AN_ISA_DEVICE(a)	(strcmp((a)->bus_name, "isa") == 0)


/* 
 * i/o space addresses for miscellaneous hardware registers
 */
#define	EBV14_TIMERBASE	   	   0x4000	/* base of timer registers		*/
#define	EBV14_TODBASE		   0x8000	/* base of tod clock registers 		*/
#define EBV14_SIOBASE		   0x01F0	/* base of Super I/O registers		*/
#define EBV14_COM1BASE		   0x03F8	/* base of Super I/O COM1 registers  	*/
#define EBV14_COM2BASE		   0x02F8	/* base of Super I/O COM2 registers	*/
#define EBV14_MOUSEBASE		   0x0060	/* base of mouse registers 		*/
#define EBV14_KBDBASE		   0x0060	/* base of keyboard registers 		*/
#define EBV14_PP1BASE		   0x03BC	/* base of parallel port 1 registers 	*/
#define EBV14_PP2BASE		   0x0378	/* base of parallel port 2 registers 	*/

#define	EBV14_DSPL		   0x800	/* module display control register	*/
#define	EBV14_MCFG		   0x801	/* module configuration register	*/
#define EBV14_INT1		   0x802	/* interrupt register 1			*/
#define EBV14_INT2		   0x803	/* interrupt register 2 		*/
#define EBV14_INT3		   0x804	/* interrupt register 3 		*/
#define EBV14_INT4		   0x805	/* interrupt register 4 		*/
#define EBV14_MEMCFG1		   0x806	/* memory configuration register 1 	*/
#define EBV14_MEMCFG2  	   	   0x807	/* memory configuration register 2 	*/
#define EBV14_MEMCFG3		   0x808	/* memory configuration register 3 	*/
#define EBV14_MEMCFG4		   0x809	/* memory configuration register 4 	*/
#define	EBV14_MRST1		   0x80a	/* module reset reason register 1	*/
#define EBV14_MEMID		   0x80b	/* memory identification register       */
#define	EBV14_CCLK		   0x80c	/* dismiss interval timer interrupt	*/
#define	EBV14_MCTL		   0x80d	/* module control register		*/
#define	EBV14_MRST2		   0x80e	/* module reset reason register 2	*/
#define EBV14_BCACHE_CFG	   0x80f	/* bcache configuration		 	*/
#define	EBV14_MRST3		   0x82e	/* module reset reason register 3	*/

/*
 * module display control register (EBV14_DSPL)
 */

#define EBV14_DSPL_OUTPUT	   0x007f	/* display output character mask	*/

#define EBV14_DSPL_BRIGHT	   0x0080	/* display brightness			*/
#define EBV14_DSPL_BRIGHT_NORMAL   0x0000	/*   0 = normal display brightness	*/
#define EBV14_DSPL_BRIGHT_HI	   0x0080	/*   1 = high display brightness	*/


/*
 * module configuration register (EBV14_MCFG)
 */

#define EBV14_MCFG_BRKOUT	   0x0003	/* breakout mask			*/
#define EBV14_MCFG_BRKOUT_NONE	   0x0000	/* none defined 			*/
#define EBV14_MCFG_BRKOUT_TYPE1    0x0001	/* type 1 breakout			*/
#define EBV14_MCFG_BRKOUT_TYPE2    0x0002	/* type 2 breakout			*/

#define EBV14_MCFG_DEBUG	   0x0004	/* debug mode mask			*/
#define EBV14_MCFG_DEBUG0	   0x0000	/*   TBD				*/
#define EBV14_MCFG_DEBUG1	   0x0004	/*   TBD				*/

#define EBV14_MCFG_MODID	   0x0018	/* module id mask			*/
#define EBV14_MCFG_MODID_TYPE1	   0x0000	/* type 1 module 			*/
#define EBV14_MCFG_MODID_TYPE2	   0x0008	/* type 2 module 			*/

#define EBV14_MCFG_CPUID	   0x0060	/* cpu id mask				*/
#define EBV14_MCFG_CPUID_233	   0x0000	/* 233 mhz				*/
#define EBV14_MCFG_CPUID_288	   0x0020	/* 288 mhz				*/

/*
 * interrupt and interrupt mask register 1 (EBV14_INT1)
 */
#define EBV14_INT1_VME_RESET	   0x0001	/* VME reset				*/
#define EBV14_INT1_VME_IRQ7	   0x0002	/* VME IRQ7 				*/
#define EBV14_INT1_VIP_VIC_ERROR   0x0004	/* VIP/VIP error and status 		*/
#define EBV14_INT1_INTRVL_TMR 	   0x0008	/* interval timer 			*/
#define EBV14_INT1_VIP_STS	   0x0010	/* VIP status 				*/
#define EBV14_INT1_1MS_HEARTBEAT   0x0020	/* 1ms heartbeat timer 			*/


/*
 * interrupt and interrupt mask register 2 (EBV14_INT2)
 */
#define EBV14_INT2_VME_IRQ6	   0x0001	/* VME IRQ6				*/
#define EBV14_INT2_VME_IRQ5	   0x0002	/* VME IRQ5				*/
#define EBV14_INT2_VME_IRQ4	   0x0004	/* VME IRQ4				*/
#define EBV14_INT2_PCI0_INTA	   0x0008	/* pci slot 0 interrupt A 		*/
#define EBV14_INT2_PCI1_INTA	   0x0010	/* pci slot 1 interrupt A 		*/

/*
 * interrupt and interrupt mask register 3 (EBV14_INT3)
 */
#define EBV14_INT3_SCSI_IRQ	   0x0001	/* SCSI IRQ				*/
#define EBV14_INT3_NI_IRQ	   0x0002	/* NI IRQ5				*/
#define EBV14_INT3_PCI1_INTB	   0x0004	/* pci slot 1 interrupt B		*/
#define EBV14_INT3_SIO_IRQ	   0x0008	/* SIO IRQ				*/
#define EBV14_INT3_PCI0_INTB	   0x0010	/* pci slot 0 interrupt B		*/
#define EBV14_INT3_VME_IRQ3	   0x0020	/* VME IRQ3				*/
#define EBV14_INT3_VME_IRQ2	   0x0040	/* VME IRQ2				*/
#define EBV14_INT3_VME_IRQ1	   0x0080	/* VME IRQ3				*/

/*
 * interrupt and interrupt mask register 4 (EBV14_INT4)
 */
#define EBV14_INT4_VME_IACK	   0x0001	/* VME IACK				*/
#define EBV14_INT4_PCI0_INTC	   0x0002	/* pci slot 0 interrupt C		*/
#define EBV14_INT4_PCI1_INTC	   0x0004	/* pci slot 1 interrupt C		*/
#define EBV14_INT4_PCI0_INTD	   0x0008	/* pci slot 0 interrupt D		*/
#define EBV14_INT4_PCI1_INTD	   0x0010	/* pci slot 1 interrupt D		*/

/*
 * module control register (EBV14_MCTL)
 */

#define EBV14_MCTL_FLASH_ADDR_20   0x0001	/* flash address 20			*/
#define EBV14_MCTL_FLASH_SEL       0x0002	/* flash select 			*/
#define EBV14_MCTL_FLASH_SWITCH    0x0004	/* flash switch 			*/
#define EBV14_MCTL_FLASH_WRITE_ENA 0x0008	/* flash write enable			*/
#define EBV14_MCTL_WDT_RENABL	   0x0020	/* watchdog timer reset enable		*/
#define EBV14_MCTL_TMR0_MODE1_ENA  0x0080	/* timer 0 mode 1 enable		*/

/*
 * bcache configuration register (EBV14_BCACHE_CFG)
 */
#define EBV14_BCACHE_CFG_SS 	   0x0003	/* bcache size and speed mask		*/
#define EBV14_BCACHE_CFG_SS_DIS    0x0000	/* bcache disabled			*/
#define EBV14_BCACHE_CFG_SS_512KB_15NS 0x0001	/* 512 KB size, 15ns speed		*/
#define EBV14_BCACHE_CFG_SS_2MB_12NS   0x0002	/* 2 MB size, 12ns speed		*/

/*
 * module reset reason register (EBV14_MRST)
 */
#define EBV14_MRST_WATCHDOG	   0x0001	/* reset due to watchdog timer timeout	*/
#define EBV14_MRST_FPSWITCH	   0x0002	/* reset due to front panel switch 	*/
#define EBV14_MRST_VMERESET	   0x0004	/* reset due to vmebus sysreset		*/
#define EBV14_MRST_POWERUP	   0x0008	/* reset due to power-up		*/
#define EBV14_MRST_DIP		   0x0010	/* diagnostic in progress		*/


/*
 * isa0 interrupt request constants
 */
#define	EBV14_NUM_ISA_IRQ 	    16		/* max. irq for isa0			*/

/* ISA Interrupt Request levels (IRQ) for device interrupts supported via the 
 * 82378 SIO on Cortex:
 *    IR0     Unused (RTC internal to the SIO)
 *    IR1     Intel 8242 Keyboard controller
 *    IR2     Unused
 *    IR3     8-bit ISA - National PC87312 serial port COM2
 *    IR4     8-bit ISA - National PC87312 serial port COM1
 *    IR5     8-bit ISA - National PC87312 Parallel port 
 *    IR6     Unused
 *    IR7     8-bit ISA - National PC87312 Parallel port 
 *    IR8     Unused 
 *    IR9     Unused 
 *    IR10    Unused 
 *    IR11    Unused 
 *    IR12    16-bit ISA Intel 8242 Mouse controller
 *    IR13    Unused
 *    IR14    Unused 
 *    IR15    Unused 
 */

#define EBV14_ISA0_IRQ_KEYBOARD      1		/* irq for isa0 Intel 8242 keyboard controller	*/
#define EBV14_ISA0_IRQ_COM2	     3		/* irq for isa0 serial port COM2 (PC87312)	*/
#define EBV14_ISA0_IRQ_COM1          4		/* irq for isa0 serial port COM1 (PC87312)	*/
#define EBV14_ISA0_IRQ_PP2           5		/* irq for isa0 parallel port (PC87312) 	*/
#define EBV14_ISA0_IRQ_PP1           7		/* irq for isa0 parallel port (PC87312) 	*/
#define EBV14_ISA0_IRQ_MOUSE        12		/* irq for isa0 Intel 8242 mouse controller	*/

/* The following two are arbitrarily set to use two unused isa irq's, and are hardcoded into 	*/
/* the isa config table by ebv14 platform code (because there is no isa_cfg in the firmware). 	*/
#define EBV14_ISA0_IRQ_RT_TIMER     10		/* irq for isa0 Intel 82C54 interval timer      */
#define EBV14_ISA0_IRQ_RT_PERIODIC  11		/* irq for isa0 Intel 82C54 periodic timer      */

/*
 * pci slot number constants
 */

#define EBV14_MIN_PCI_SLOT           0		/* min. slot no. for pci (ad<11>)	*/
#define EBV14_MAX_PCI_SLOT           5 		/* max. slot no. for pci (ad<16>)	*/
#define EBV14_NUM_PCI_SLOT           6		/* no. of available pci slots		*/
						/* including 2 for pmc options */

#define EBV14_PCI_SLOT_VME	     0		/* vmebus slot no. for pci (ad<11>)	*/
#define EBV14_PCI_SLOT_NI	     1		/* ni slot no. for pci (ad<12>)	*/
#define EBV14_PCI_SLOT_SCSI	     2		/* scsi slot no. for pci (ad<13>)	*/
#define EBV14_PCI_SLOT_SIO           3		/* sio slot no. for pci (ad<14>)	*/
#define EBV14_PCI_SLOT_PMC	     4		/* PPB bridge slot (ad<15>) */

/*
 * interrupt vector offsets & constants
 */

#define EBV14_MIN_IOVEC            0x0800       /* min. interrupt vector offset         */
#define EBV14_MAX_IOVEC            0x1ff0       /* max. interrupt vector offset         */

#define EBV14_NUM_IOVEC            384          /* no. of available interrupt vectors   */

/* 
 * ISA device vectors
 */

/* ISA devices that interrupt on the PIC */
#define EBV14_IOVEC_KEYBOARD	   0x0810	/* keyboard				*/
#define EBV14_IOVEC_COM2	   0x0830	/* serial port COM2 (PC87312)		*/
#define EBV14_IOVEC_COM1           0x0840	/* serial port COM1 (PC87312)		*/
#define EBV14_IOVEC_PP2            0x0850	/* parallel port (PC87312) 		*/
#define EBV14_IOVEC_PP1            0x0870	/* parallel port (PC87312) 		*/
#define EBV14_IOVEC_MOUSE          0x08c0	/* Intel 8242 mouse controller		*/

/* ISA devices that interrupt on the XYLINX */
#define EBV14_IOVEC_RT_TIMER       0x09A0       /* isa realtime interval timer interrupt*/
#define EBV14_IOVEC_RT_PERIODIC    0x09B0       /* isa realtime periodic timer interrupt*/

/* 
 * PCI and VME device vectors
 */
#define EBV14_IOVEC_WATCHDOG       0x0820       /* watchdog timer timeout/halt interrupt*/
#define EBV14_IOVEC_VME_RESET      0x0880       /* vmebus reset interrupt               */
#define EBV14_IOVEC_NI             0x0900       /* network interface interrupt          */
#define EBV14_IOVEC_SCSI           0x0910       /* scsi interrupt                       */
#define EBV14_IOVEC_PCI_OPT1_B     0x0920       /* pci option slot #1 b interrupt       */
#define EBV14_IOVEC_PCI_OPT2_B     0x0930       /* pci option slot #2 b interrupt       */
#define EBV14_IOVEC_PCI_OPT1_C     0x0940       /* pci option slot #1 c interrupt       */
#define EBV14_IOVEC_PCI_OPT2_C     0x0950       /* pci option slot #2 c interrupt       */
#define EBV14_IOVEC_PCI_OPT1_D     0x0960       /* pci option slot #1 d interrupt       */
#define EBV14_IOVEC_PCI_OPT2_D     0x0970       /* pci option slot #2 d interrupt       */
#define EBV14_IOVEC_PCI_OPT1_A     0x0980       /* pci option slot #1 a interrupt       */
#define EBV14_IOVEC_PCI_OPT2_A     0x0990       /* pci option slot #2 a interrupt       */

#define EBV14_IOVEC_VME_BASE       0x1000       /* start of vmebus interrupts           */
#define EBV14_IOVEC_LOC_MONITOR    0x1020       /* vmebus location monitor interrupt    */
#define EBV14_IOVEC_VIP_ERR        0x1070       /* vip error interrupt                  */
#define EBV14_IOVEC_VIC_ACFAIL     0x1080       /* vic a/c failed interrupt             */
#define EBV14_IOVEC_VIC_WPFAIL     0x1090       /* vic writepost failed interrupt       */
#define EBV14_IOVEC_VIC_ARBTO      0x10a0       /* vic arbitration timeout interrupt    */
#define EBV14_IOVEC_VIC_SYSFAIL    0x10b0       /* vic sysfail interrupt                */
#define EBV14_IOVEC_VME_IACK       0x10c0       /* vmebus iack interrupt                */
#define EBV14_IOVEC_VME_DMA        0x10d0       /* vmebus dma status interrupt          */
#define EBV14_IOVEC_VME_ICGS0      0x1100       /* vmebus ip global switch 0 interrupt  */
#define EBV14_IOVEC_VME_ICGS1      0x1110       /* vmebus ip global switch 1 interrupt  */
#define EBV14_IOVEC_VME_ICGS2      0x1120       /* vmebus ip global switch 2 interrupt  */
#define EBV14_IOVEC_VME_ICGS3      0x1130       /* vmebus ip global switch 3 interrupt  */
#define EBV14_IOVEC_VME_ICMS0      0x1140       /* vmebus ip local switch 0 interrupt   */
#define EBV14_IOVEC_VME_ICMS1      0x1150       /* vmebus ip local switch 1 interrupt   */
#define EBV14_IOVEC_VME_ICMS2      0x1160       /* vmebus ip local switch 2 interrupt   */
#define EBV14_IOVEC_VME_ICMS3      0x1170       /* vmebus ip local switch 3 interrupt   */

#define EBV14_IOVEC_VME_END        0x1ff0       /* end of vmebus interrupts             */


/*
 * Hardware interrupt enable/disable interrupt mask bit positions for 
 * XYLINX interrupt controller for PCI devices.  These values
 * are found in the 'intr_line' field of the PCI bus slot configuration data.
 */
#define	EBV14_INTR_BIT_NI	   2	/* network interface interrupt	        */
#define	EBV14_INTR_BIT_SCSI	   3	/* scsi interrupt		        */
#define	EBV14_INTR_BIT_PCI_OPT1_B  4	/* pci option slot #1 b interrupt 	*/
#define	EBV14_INTR_BIT_PCI_OPT2_B  5	/* pci option slot #2 b interrupt	*/
#define	EBV14_INTR_BIT_PCI_OPT1_C  6	/* pci option slot #1 c interrupt	*/
#define	EBV14_INTR_BIT_PCI_OPT2_C  7	/* pci option slot #2 c interrupt 	*/
#define	EBV14_INTR_BIT_PCI_OPT1_D  8	/* pci option slot #1 d interrupt	*/
#define	EBV14_INTR_BIT_PCI_OPT2_D  9	/* pci option slot #2 d interrupt	*/
#define	EBV14_INTR_BIT_PCI_OPT1_A  10	/* pci option slot #1 a interrupt	*/
#define	EBV14_INTR_BIT_PCI_OPT2_A  11	/* pci option slot #2 a interrupt	*/

/*
 * Hardware interrupt enable/disable masks for XYLINX interrupt controller
 */
#define	EBV14_INTR_ALL		   (ULONG_MAX)	/* all hardware interrupts	        */

#define	EBV14_INTR_NI		   (1UL <<  2)	/* network interface interrupt	        */
#define	EBV14_INTR_SCSI	   	   (1UL <<  3)	/* scsi interrupt		        */
#define	EBV14_INTR_PCI_OPT1_B	   (1UL <<  4)	/* pci option slot #1 b interrupt 	*/
#define	EBV14_INTR_PCI_OPT2_B	   (1UL <<  5)	/* pci option slot #2 b interrupt	*/
#define	EBV14_INTR_PCI_OPT1_C	   (1UL <<  6)	/* pci option slot #1 c interrupt	*/
#define	EBV14_INTR_PCI_OPT2_C	   (1UL <<  7)	/* pci option slot #2 c interrupt 	*/
#define	EBV14_INTR_PCI_OPT1_D	   (1UL <<  8)	/* pci option slot #1 d interrupt	*/
#define	EBV14_INTR_PCI_OPT2_D	   (1UL <<  9)	/* pci option slot #2 d interrupt	*/
#define	EBV14_INTR_PCI_OPT1_A 	   (1UL << 10)	/* pci option slot #1 a interrupt	*/
#define	EBV14_INTR_PCI_OPT2_A	   (1UL << 11)	/* pci option slot #2 a interrupt	*/
#define	EBV14_INTR_VME_RESET	   (1UL << 12)	/* vmebus reset interrupt	        */
#define	EBV14_INTR_RT_TIMER	   (1UL << 13)	/* realtime interval timer interrupt    */
#define	EBV14_INTR_RT_PERIODIC	   (1UL << 14)	/* realtime periodic timer interrupt    */
#define	EBV14_INTR_HARDCLOCK	   (1UL << 15)	/* hardware interval timer interrupt    */

#define	EBV14_INTR_LOC_MONITOR	   (1UL << 18)	/* vmebus location monitor interrupt    */
#define	EBV14_INTR_LIRQ2	   (1UL << 18)	/* vic local irq2 interrupt	        */

#define	EBV14_INTR_VIP_ERR	   (1UL << 23)	/* vip error interrupt		        */
#define	EBV14_INTR_LIRQ7	   (1UL << 23)	/* vic local irq7 interrupt	        */

#define	EBV14_INTR_VME_IRQ1	   (1UL << 25)	/* vmebus irq1 interrupt	        */
#define	EBV14_INTR_VME_IRQ2	   (1UL << 26)	/* vmebus irq2 interrupt	        */
#define	EBV14_INTR_VME_IRQ3	   (1UL << 27)	/* vmebus irq3 interrupt	        */
#define	EBV14_INTR_VME_IRQ4	   (1UL << 28)	/* vmebus irq4 interrupt	        */
#define	EBV14_INTR_VME_IRQ5	   (1UL << 29)	/* vmebus irq5 interrupt	        */
#define	EBV14_INTR_VME_IRQ6	   (1UL << 30)	/* vmebus irq6 interrupt	        */
#define	EBV14_INTR_VME_IRQ7	   (1UL << 31)	/* vmebus irq7 interrupt	        */

#define	EBV14_INTR_VME_DMA	   (1UL << 36)	/* vmebus dma status interrupt	        */
#define	EBV14_INTR_VME_IACK	   (1UL << 37)	/* vmebus iack interrupt	        */
#define	EBV14_INTR_WATCHDOG	   (1UL << 38)	/* halt/watchdog timer timeout interrupt*/

#define	EBV14_INTR_VIC_SYSFAIL	   (1UL << 40)	/* vic sysfail interrupt	        */
#define	EBV14_INTR_VIC_ARBTO	   (1UL << 41)	/* vic arbitration timeout interrupt    */
#define	EBV14_INTR_VIC_WPFAIL	   (1UL << 42)	/* vic writepost failed interrupt       */
#define	EBV14_INTR_VIC_ACFAIL	   (1UL << 43)	/* vic a/c failed interrupt		*/
#define	EBV14_INTR_VME_ICMS0	   (1UL << 44)	/* vmebus ip local switch 0 interrupt   */
#define	EBV14_INTR_VME_ICMS1	   (1UL << 45)	/* vmebus ip local switch 1 interrupt   */
#define	EBV14_INTR_VME_ICMS2	   (1UL << 46)	/* vmebus ip local switch 2 interrupt   */
#define	EBV14_INTR_VME_ICMS3	   (1UL << 47)	/* vmebus ip local switch 3 interrupt   */
#define	EBV14_INTR_VME_ICGS0	   (1UL << 48)	/* vmebus ip global switch 0 interrupt  */
#define	EBV14_INTR_VME_ICGS1	   (1UL << 49)	/* vmebus ip global switch 1 interrupt  */
#define	EBV14_INTR_VME_ICGS2	   (1UL << 50)	/* vmebus ip global switch 2 interrupt  */
#define	EBV14_INTR_VME_ICGS3	   (1UL << 51)	/* vmebus ip global switch 3 interrupt  */

#endif	/* _ARCH_ALPHA_HAL_EBV14_H */
