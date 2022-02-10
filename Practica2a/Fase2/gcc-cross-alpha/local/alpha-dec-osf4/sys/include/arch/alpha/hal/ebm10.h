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
#pragma ident "@(#)$RCSfile: ebm10.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1996/05/06 16:30:29 $"

#ifndef	_ARCH_ALPHA_HAL_EBM10_H
#define	_ARCH_ALPHA_HAL_EBM10_H

#include <sys/types.h>

/*
 * LEGO K2  SYSTEM ADDRESS MAP
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
 * LEGO K2 BUS-RELATED DEFINITIONS
 *
 * The following constants define the mapping between PCI "slot"
 * number and the corresponding PCI address bit that drives the
 * device IDSEL pin.
 *
 */

//#define	EBM10_MIN_SLOT		5	/* PCI_AD<16> */
/*#define	EBM10_MIN_SLOT		7 */	/* PCI_AD<18> */
//#define EBM10_MAX_SLOT		20	/* PCI_AD<31> */
#define	EBM10_MIN_SLOT		0 /* Primary AD<11>   Secondary AD<16>*/
#define	EBM10_MAX_SLOT	       20 /* Primary AD<31>   Secondary AD<36 */

/*
 * LEGO K2 IRQ & SCB DEFINITIONS
 *
 * The following constants define the SCB assignments for all ISA device 
 * interrupts.  Because EB64+ uses a standard ISA IRQ to SCB mapping, the 
 * irq_to_scb_vector mapping provided in 82357_pic.h and 82357_pic.c is 
 * used.
 *
 * These definitions are included here for completeness.
 *
 * #define PIC_SCB_IRQ0		0x800	Intel 82C54 Interval Timer
 * #define PIC_SCB_IRQ1		0x810	Intel 8242 Keyboard controller
 * #define PIC_SCB_IRQ2		0x820	Chains interrupt from slave controller
 * #define PIC_SCB_IRQ3		0x830	National PC87312 serial port COM2
 * #define PIC_SCB_IRQ4		0x840	National PC87312 serial port COM1
 * #define PIC_SCB_IRQ5		0x850	National PC87312 parallel port (or IRQ7)
 * #define PIC_SCB_IRQ6		0x860	National PC87312 floppy disk controller
 * #define PIC_SCB_IRQ7		0x870	National PC87312 parallel port (or IRQ5)
 * #define PIC_SCB_IRQ8 	0x880   Unused 
 * #define PIC_SCB_IRQ9		0x890	ISA expansion connector
 * #define PIC_SCB_IRQ10	0x8A0   ISA expansion connector
 * #define PIC_SCB_IRQ11	0x8B0	ISA expansion connector
 * #define PIC_SCB_IRQ12	0x8C0	Intel 8242 Mouse controller
 * #define PIC_SCB_IRQ13	0x8D0	Unused 
 * #define PIC_SCB_IRQ14	0x8E0	ISA expansion connector
 * #define PIC_SCB_IRQ15	0x8F0   ISA expansion connector
 *
 *
 *
 * The following constants define the SCB assignments for all PCI
 * device interrupts:
 *
 * On LEGO K2 
 * 	ATACAMA, GOBI and SAHARA backplanes:
 *	[ Slot numbering Slot_0  === AD<11> i.e. first slot ]
 * 
 * Primary_SLOT1 (ID31/Slot_19)	0x900 - 0x9F0
 * Primary_SLOT2 (ID30/Slot_18)	0xA00 - 0xAF0
 * Primary_SLOT3 (ID29/Slot_17)	0xB00 - 0xBF0
 * Primary_SLOT4 (ID28/Slot_16)	0xC00 - 0xCF0
 *
 * SIO on PCI_SLOT  (ID18/Slot_07)  DOES NOT GENERATE PCI INTERRUPTS
 *
 * ATACAMA:-
 *	AD<31> SLOT 1	PCI Device 1	Physical Connector 1
 *	AD<30> SLOT 2	PCI Device 2	Physical Connector 2
 *	AD<29> SLOT 3	PCI Device 3	Physical Connector 3
 *	AD<28> SLOT 4	PCI Device 4	Physical Connector 4
 *
 * GOBI:-
 *	AD<31> SLOT 1	PCI Device 1	Physical Connector 1
 *	AD<30> SLOT 2	PCI Device 2	Physical Connector 2
 *	AD<29> SLOT 3	PCI Device 3	Physical Connector 3
 *	AD<28> SLOT 4	PCI Device 4	PCI-PCI Bridge
 *					       		Physical Connector 4
 *					       		Physical Connector 5
 *					       		Physical Connector 6
 *					       		Physical Connector 7
 *
 * SAHARA:-
 *	AD<31> SLOT 1	PCI Device 1	Physical Connector 1
 *	AD<30> SLOT 2	PCI Device 2	Physical Connector 2
 *	AD<29> SLOT 3	PCI Device 3	PCI-PCI Bridge
 *					       		Physical Connector 3
 *					       		Physical Connector 4
 *					       		Physical Connector 5
 *					       		Physical Connector 6
 *	AD<28> SLOT 4	PCI Device 4	PCI-PCI Bridge
 *					       		Physical Connector 7
 *					       		Physical Connector 8
 *					       		Physical Connector 9
 *					       		Physical Connector 10
 */

/*
 * Server Management Feature Interrupt Vectors
 */
 
#define K2_SCB_WDO_TMR_1	0xD00 /* Watchdog timer 1  */
/* Timer 2 pulls the plug via hard reset! */
#define K2_SCB_CPU_TEMP_WARN	0xD10 /* CPU temperature fail interrupt */
#define K2_SCB_CPU_TEMP_NORMAL	0xD20 /* CPU temperature normal interrupt */
#define K2_SCB_SYS_FAN_WARN	0xD30 /* System fan fail interrupt */
#define K2_SCB_PSU_1_FAIL	0xD40 /* Power Supply 1 failed */
#define K2_SCB_PSU_2_FAIL	0xD50 /* Power Supply 2 failed */


/*
 * PCI SCB Vector Range
 */

#define K2_SCB_DEV_PCI_MIN	0x900	/* 1st SCB vector for PCI devices */
#define K2_SCB_DEV_PCI_MAX	0xCF0	/* Last SCB vector for PCI devices */
#define K2_PRIM_SLOT_1_ILR	0x90	/* 1st PCI dev Interrupt Line Reg */

/*
 * Interrupt Controller Register Definitions
 *   These registers reside in the ISA space
 *     Configuration register	(16 bits)
 *     Master interrupt controller register (16 bits)
 *     4 slot interrupt controller registers (32 bits)
 */

#define K2_CFG_MSTR_INTR	0x500	/* Combined Config & Master Intr 32b */
#define K2_MSTR_INTR_REG	0x500	/* Master Interrupt Register (16bit) */
#define K2_CONFIG_REG		0x502   /* Configuration Reg (16bit)  */
#define K2_INTR_REG_1		0x510	/* Intr Accel Reg - Slot 1 <AD31> */
#define K2_INTR_REG_2		0x514	/* Intr Accel Reg - Slot 2 <AD30> */
#define K2_INTR_REG_3		0x518	/* Intr Accel Reg - Slot 3 <AD29> */
#define K2_INTR_REG_4		0x51C	/* Intr Accel Reg - Slot 4 <AD28> */

/* Configuration Register Layout 16 bit */

#define K2_CONFIG_M_ADR		0xFFF0	/* Interript Register Address Mask */
#define K2_CONFIG_M_CFG		0x000F	/* Back plane configuration Bits */
#define K2_CONFIG_CFG_1		0x0001	/* Config format for Slot Reg 1	*/
#define K2_CONFIG_CFG_2		0x0002	/* Config format for Slot Reg 2	*/
#define K2_CONFIG_CFG_3		0x0004	/* Config format for Slot Reg 3	*/
#define K2_CONFIG_CFG_4		0x0008	/* Config format for Slot Reg 4	*/
#define K2_CONFIG_CFG_PPBRIDGE	1	/*   1 = PCI-PCI Bridge */
#define	K2_CONFIG_CFG_CONNECTOR	0	/*   0 = Physical Connector */
#define K2_CONFIG_CFG_ATACAMA	0x0000	/* 0000(b)	Atacama	0 PPB	*/
#define K2_CONFIG_CFG_GOBI	0x0001	/* 0001(b)	Gobi	1 PPB	*/
#define	K2_CONFIG_CFG_SAHARA	0x0003	/* 0011(b)	Sahara	2 PPB	*/
#define K2_CONFIG_CFG_NAMIB     0x0007  /* 0111(b)      Namib   3 PPB   */

/* Master Interrupt Controller Register Bits Definitions 16 bit */

#define K2_MSTR_INTR_M_MODE	0x8000	/* Interrupt Controller Mode */
#define K2_MSTR_INTR_MODE_PICMG	0	/* PICMG Mode		*/
#define K2_MSTR_INTR_MODE_ACCEL	1	/* Accelerator Mode	*/
#define	K2_MSTR_INTR_M_PCIE	0x4000	/* PCI to CPU Interrupt Enable */
#define	K2_MSTR_INTR_M_MSKEN	0x2000	/* Interr Register Mask Enable */
#define	K2_MSTR_INTR_M_MINTFE	0x0C00	/* RESERVED 	*/
#define	K2_MSTR_INTR_M_MINT_F	0x0800	/* RESERVED	*/
#define	K2_MSTR_INTR_M_MINT_E	0x0400	/* RESERVED	*/
#define	K2_MSTR_INTR_M_MINT	0x03C0	/* Mask bits for 4 backplane intr */
#define	K2_MSTR_INTR_M_MINT_D	0x0200	/* Mask INTD if 1	*/
#define	K2_MSTR_INTR_M_MINT_C	0x0100	/* Mask INTC if 1	*/	
#define	K2_MSTR_INTR_M_MINT_B	0x0080	/* Mask INTB if 1	*/
#define	K2_MSTR_INTR_M_MINT_A	0x0040	/* Mask INTA if 1	*/
#define	K2_MSTR_INTR_M_INTFE	0x0030	/* RESERVED	*/
#define	K2_MSTR_INTR_M_INT_F	0x0020	/* RESERVED	*/
#define	K2_MSTR_INTR_M_INT_E	0x0010	/* RESERVED	*/
#define	K2_MSTR_INTR_M_INT	0x000F	/* Backplane Intr Status Bits */
#define	K2_MSTR_INTR_M_INT_D	0x0008	/* INTD <- Intr from Slot Reg 4 */
#define	K2_MSTR_INTR_M_INT_C	0x0004	/* INTC <- Intr from Slot Reg 3 */
#define	K2_MSTR_INTR_M_INT_B	0x0002	/* INTB <- Intr from Slot Reg 2 */
#define	K2_MSTR_INTR_M_INT_A	0x0001	/* INTA <- Intr from Slot Reg 1 */


/* PCI-PCI Bridge Register Layout 32 bits*/

#define	K2_INTR_PPB_M_MS4I	0xF0000000 /* Mask Bits for Bridged slot 4 */
#define	K2_INTR_PPB_M_MS4I_D	0x80000000 /* Mask INTD on Slot 4 bhnd bridg */
#define	K2_INTR_PPB_M_MS4I_C	0x40000000 /*  */
#define	K2_INTR_PPB_M_MS4I_B	0x20000000 /*  */
#define	K2_INTR_PPB_M_MS4I_A	0x10000000 /*  */
#define	K2_INTR_PPB_M_MS3I	0x0F000000 /* Mask Bits for Bridged slot 3 */
#define	K2_INTR_PPB_M_MS3I_D	0x08000000 /*  */
#define	K2_INTR_PPB_M_MS3I_C	0x04000000 /*  */
#define	K2_INTR_PPB_M_MS3I_B	0x02000000 /*  */
#define	K2_INTR_PPB_M_MS3I_A	0x01000000 /*  */
#define	K2_INTR_PPB_M_MS2I	0x00F00000 /* Mask Bits for Bridged slot 2 */
#define	K2_INTR_PPB_M_MS2I_D	0x00800000 /*  */
#define	K2_INTR_PPB_M_MS2I_C	0x00400000 /*  */
#define	K2_INTR_PPB_M_MS2I_B	0x00200000 /*  */
#define	K2_INTR_PPB_M_MS2I_A	0x00100000 /*  */
#define	K2_INTR_PPB_M_MS1I	0x000F0000 /* Mask Bits for Bridged slot 1 */
#define	K2_INTR_PPB_M_MS1I_D	0x00080000 /*  */
#define	K2_INTR_PPB_M_MS1I_C	0x00040000 /*  */
#define	K2_INTR_PPB_M_MS1I_B	0x00020000 /*  */
#define	K2_INTR_PPB_M_MS1I_A	0x00010000 /*  */

#define	K2_INTR_PPB_M_S4I	0x0000F000 /* Intr Status Bits for Slot 4 */
#define	K2_INTR_PPB_M_S4I_D	0x00008000 /* INT D for Slot 4 bhnd bridge */
#define	K2_INTR_PPB_M_S4I_C	0x00004000
#define	K2_INTR_PPB_M_S4I_B	0x00002000
#define	K2_INTR_PPB_M_S4I_A	0x00001000
#define	K2_INTR_PPB_M_S3I	0x00000F00 /* Intr Status Bits for Slot 3 */
#define	K2_INTR_PPB_M_S3I_D	0x00000800
#define	K2_INTR_PPB_M_S3I_C	0x00000400
#define	K2_INTR_PPB_M_S3I_B	0x00000200
#define	K2_INTR_PPB_M_S3I_A	0x00000100
#define	K2_INTR_PPB_M_S2I	0x000000F0 /* Intr Status Bits for Slot 2 */
#define	K2_INTR_PPB_M_S2I_D	0x00000080
#define	K2_INTR_PPB_M_S2I_C	0x00000040
#define	K2_INTR_PPB_M_S2I_B	0x00000020
#define	K2_INTR_PPB_M_S2I_A	0x00000010
#define	K2_INTR_PPB_M_S1I	0x0000000F /* Intr Status Bits for Slot 1 */
#define	K2_INTR_PPB_M_S1I_D	0x00000008
#define	K2_INTR_PPB_M_S1I_C	0x00000004
#define	K2_INTR_PPB_M_S1I_B	0x00000002
#define	K2_INTR_PPB_M_S1I_A	0x00000001

/*
 * Server Management and Watchdog Timer Register Definitions
 *   These registers reside in the ISA space
 *     Watchdog Register (16 bits)
 *     Server Management Register (16 bits)
 *
 */

#define K2_WATCHDOG_REG		0x504 /* Watchdog Register */
#define K2_SERVER_MAN_REG	0x506 /* Server Management Register */

/* Layout of the Watchdog Register */

#define	K2_WDO_M_WINT		0x0200 /* Indicates watchdog INT occurred*/
#define	K2_WDO_M_WPHAS		0x0100 /* Phase: 1 = T1 expired & T2 running */
#define K2_WDO_M_WMODE		0x0080 /* Mode: 0 = dual timer; 1 = 1 timer */
#define K2_WDO_M_WEN		0x0040 /* Enable: 0 = disable; 1 = enable */

#define K2_WDO_TIMEOUT_BITS	 3
#define K2_WDO_MAX_TIMEOUT_INDEX 8

#define K2_WDO_M_T2CF		0x0038 /* Timer T2 timeout period */
#define K2_WDO_M_T1CF		0x0007 /* Timer T1 timeout period */


/* Timer T2 timeout values */

#define K2_WDO_M_T2CF_10mS	0x0000 /* 10 mS */
#define K2_WDO_M_T2CF_100mS	0x0008 /* 100 mS */
#define K2_WDO_M_T2CF_500mS	0x0010 /* 500 ms */
#define K2_WDO_M_T2CF_1S	0x0018 /* 1 Sec */
#define K2_WDO_M_T2CF_8S	0x0020 /* 8 Sec */
#define K2_WDO_M_T2CF_1M	0x0028 /* 1 Min */
#define K2_WDO_M_T2CF_5M	0x0030 /* 5 Min */
#define K2_WDO_M_T2CF_20M	0x0038 /* 20 Min */


/* Timer T1 timeout values */

#define K2_WDO_M_T1CF_10mS	0x0000 /* 10 mS */
#define K2_WDO_M_T1CF_100mS	0x0001 /* 100 mS */
#define K2_WDO_M_T1CF_500mS	0x0002 /* 500 mS */
#define K2_WDO_M_T1CF_1S	0x0003 /* 1 Sec */
#define K2_WDO_M_T1CF_8S	0x0004 /* 8 Sec */
#define K2_WDO_M_T1CF_1M	0x0005 /* 1 Min */
#define K2_WDO_M_T1CF_5M	0x0006 /* 5 Min */
#define K2_WDO_M_T1CF_20M	0x0007 /* 20 Min */


/* Server Management Register Layout 16 bits access only */
/* Follows REV 0.6 of Server Management Specification */

#define K2_SERVMAN_M_PINT	0x0600 /* Redundant PSU Interrupt Status */
				       /* 1 = Interrupt   0 = No Interrupt */
#define K2_SERVMAN_M_PINT_2	0x0400 /* Redundant PSU 2(uses Vector D50) */
#define K2_SERVMAN_M_PINT_1	0x0200 /* Redundant PSU 1(uses Vector D40) */
#define K2_SERVMAN_M_MPINT	0x0100 /* Redundant PSU Interrupt Mask */
				       /* 1 = Mask   0 = No Mask */
#define K2_SERVMAN_M_POFF	0x0080 /* Power Off, turn off PSU */
#define K2_SERVMAN_M_MSNMI	0x0040 /* NMI Mask bit; 1 = mask NMI1, NMI2 */
#define K2_SERVMAN_M_MSINT	0x0020 /* Interrupt Mask bit; 1 = mask intr */
#define K2_SERVMAN_M_SNMI_2	0x0010 /* Server NMI #2 */
#define K2_SERVMAN_M_SNMI_1	0x0008 /* Server NMI #1 */
#define K2_SERVMAN_M_SINT_3	0x0004 /* Server Interrupt #3 */
#define K2_SERVMAN_M_SINT_2	0x0002 /* Server Interrupt #2 */
#define K2_SERVMAN_M_SINT_1	0x0001 /* Server Interrupt #1 */

#define	K2_M_CPU_FAN_FAIL	K2_SERVMAN_M_SNMI_2
#define K2_M_SYSTEM_TEMP_FAIL	K2_SERVMAN_M_SNMI_1

#define K2_M_SYSTEM_FAN_WARN	K2_SERVMAN_M_SINT_3
#define K2_M_CPU_TEMP_NORMAL	K2_SERVMAN_M_SINT_2
#define K2_M_CPU_TEMP_WARN	K2_SERVMAN_M_SINT_1


#endif	/* _ARCH_ALPHA_HAL_EBM10_H */
