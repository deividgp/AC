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

#ifndef _PD6729_REG_H_
#define _PD6729_REG_H_

/****************************************************************/
/*								*/
/* MODULE NAME: pd6729_reg.h					*/
/*								*/
/* LOCATION:  /src/kernel/io/dec/pcmcia				*/
/*								*/
/* DESCRIPTION:							*/
/* 	Contains definitions for PD6729 PCI-PCMCIA bus adapter.	*/
/*								*/
/****************************************************************/

#include <sys/types.h>

/* 
 * Operation Registers offset definition 
 *
 * These are accessed as index off the index register pointed
 * to by the PCI Base Address 0 register for this chip.
 *
 * To access these registers for the socket 1, add 40h to them.
 */

/*
 * General Setup Registers 
 */ 
#define CHIP_REVISION    0x00		
#define INTERFACE_STATUS 0x01
#define POWER_CONTROL    0x02

#define CARD_STAT_CHANGE 0x04

#define MAPPING_ENABLE   0x06

#define CARD_DETECT_GENCTL 0x16

#define GLOBAL_CTL	 0x1e

/*
 * Interrupt Registers 
 */
#define INTR_AND_CONTROL 0x03
#define MGMT_INTR_CNFG	 0x05

/*
 * Misc configuration regsiters
 */

#define MISC_CTRL_1      0x16
#define MISC_CTRL_2      0x1E
#define FIFO_CONTROL     0x17
/*
 * Extention control register
 */

#define EXT_INDEX        0x2E
#define EXT_DATA         0x2F

#define EXT_SCRATCH      0x00
#define EXT_CONTROL_1    0x03
#define EXT_SYS_MM0_UA   0x05
#define EXT_SYS_MM1_UA   0x06
#define EXT_SYS_MM2_UA   0x07
#define EXT_SYS_MM3_UA   0x08
#define EXT_SYS_MM4_UA   0x09
#define EXTERN_DATA      0x0A
#define EXT_CONTROL_2    0x0B

/*
 * Timing registers
 */

#define SETUP_TIMING_0   0x3A
#define SETUP_TIMING_1   0x3D
#define COMMAND_TIMING_0 0x3B
#define COMMAND_TIMING_1 0x3E
#define RECOVER_TIMING_0 0x3C
#define RECOVER_TIMING_1 0x3F

/*
 * I/O Registers 
 */

#define IO_WINDOW_CTRL   0x07
#define IO_START_LOW_0   0x08
#define IO_START_HIGH_0  0x09
#define IO_END_LOW_0	 0x0a
#define IO_END_HIGH_0    0x0b

#define IO_START_LOW_1   0x0c
#define IO_START_HIGH_1  0x0d
#define IO_END_LOW_1	 0x0e
#define IO_END_HIGH_1    0x0f

/*
 * Card extention I/O registers
 */

#define CARD_IO_MAP_LOW_0 0x36
#define CARD_IO_MAP_HI_0  0x37
#define CARD_IO_MAP_LOW_1 0x38
#define CARD_IO_MAP_HI_1  0x39

/*
 * Memory Registers
 */

#define MEM_START_LOW_0  0x10
#define MEM_START_HIGH_0 0x11
#define MEM_END_LOW_0    0x12
#define MEM_END_HIGH_0   0x13
#define MEM_OFFSET_LOW_0 0x14
#define MEM_OFFSET_HIGH_0 0x15

#define MEM_START_LOW_1  0x18
#define MEM_START_HIGH_1 0x19
#define MEM_END_LOW_1    0x1a
#define MEM_END_HIGH_1   0x1b
#define MEM_OFFSET_LOW_1 0x1c
#define MEM_OFFSET_HIGH_1 0x1d

#define MEM_START_LOW_2  0x20
#define MEM_START_HIGH_2 0x21
#define MEM_END_LOW_2    0x22
#define MEM_END_HIGH_2   0x23
#define MEM_OFFSET_LOW_2 0x24
#define MEM_OFFSET_HIGH_2 0x25

#define MEM_START_LOW_3  0x28
#define MEM_START_HIGH_3 0x29
#define MEM_END_LOW_3    0x2a
#define MEM_END_HIGH_3   0x2b
#define MEM_OFFSET_LOW_3 0x2c
#define MEM_OFFSET_HIGH_3 0x2d

#define MEM_START_LOW_4  0x30
#define MEM_START_HIGH_4 0x31
#define MEM_END_LOW_4    0x32
#define MEM_END_HIGH_4   0x33
#define MEM_OFFSET_LOW_4 0x34
#define MEM_OFFSET_HIGH_4 0x35

/*
 * defines for setting up memory address register contents
 */

#define LOW_SHIFT	12
#define HIGH_SHIFT	20
#define UPPER_SHIFT     24
#define LOW_MASK	0xff
#define HIGH_MASK	0xf
#define UPPER_MASK	0xff
#define OFFSET_ORMASK	0x30		/* bit 4 and 5 must be 1's for offset reg. */ 

/* Shift value for getting to socket 1's Operations registers */
#define SOCKET_SHIFT 6			

#define INDEX	0x00L			/* offset from base I/O addr for index reg. */
#define DATA	0x01L			/* offset from base I/O addr for data reg. */

/*
 * Field/bit definitions for various commands to socket
 */

/* 
 * INTERFACE_STATUS register bit definitions
 */
#define CARD_DETECT_MASK	0xc
#define NO_CARD			0x0

#define BV_DETECT1	0x01
#define STSCHG		0x01
#define BV_DETECT2	0x02
#define SPKR		0x02
#define CARD_DETECT	0xc
#define WRITE_PROT	0x10
#define CARD_READY	0x20	/* Inverted */
#define POWERON		0x40
#define GPI		0x80

/*
 * POWER_CONTROL register bits
 */
#define CARD_ENABLE       0x80		/* Outputs to card socket are enabled */
#define PWR_NORESET	  0x40		/* Disable RESETDRV on resume */
#define AUTO_POWER	  0x20		/* Auto power on */

/* bit definitions for i82365SL chip */
#define CARD_POWER_ENABLE 0x10		/* PC Card Power Enable */
#define VPP2_CTR1	  0x08		/* PC Card Vpp2 power ctrl 1 */
#define VPP2_CTR0	  0x04		/* PC Card Vpp2 power ctrl 0 */
#define VPP1_CTR1	  0x02		/* PC Card Vpp1 power ctrl 1 */
#define VPP1_CTR0	  0x01		/* PC Card Vpp1 power ctrl 0 */

/* bit definitions for i82365SL DF chip */
#define VCC_MASK	  0x18		/* Mask for turning off Vcc */
#define VCC_5V		  0x10		/* Vcc = 5.0v  Power is applied to the card */
#define VCC_3V		  0x18		/* Vcc = 3.3v */
#define VPP_MASK	  0x03		/* Mask for turning off Vpp */
#define VPP_5V		  0x01		/* Vpp = 5.0v */
#define VPP_12V		  0x02		/* Vpp = 12.0v */

/*
 * I/O window control register bit definitions
 */

#define TIM_REG_SEL_1    0x80           /* Timing register select */
#define AUTO_SIZE_IO_1   0x20           /* Auto select of 8 bit or 16 bit */
#define IO_WIN_SIZE_1    0x10           /* Determine size of I/O window */
#define TIM_REG_SEL_0    0x08           /* Timing register select */
#define AUTO_SIZE_IO_0   0x02           /* Auto select of 8 bit or 16 bit */
#define IO_WIN_SIZE_0    0x01           /* Determine size of I/O window */


/*
 * Used with MEM_START_HIGH_x registers 
 */
#define DATA_PATH_16	  0x80		/* 16-bit data path size to the card */ 
/* 
 * Used with MEM_END_HIGH_x registers
 * for specifying wait states for 16-bit Memory Access
 */
#define WAIT_STATE_1	  0x40		/* 1 additional wait state	*/
#define WAIT_STATE_2	  0x80		/* 2 additional wait states	*/
#define WAIT_STATE_3	  0xc0		/* 3 additional wait states	*/


/*
 * Used with MEM_OFFSET_HIGH_x registers 
 */
#define REG_ACTIVE	  0x40		/* -REG is active for accesses -- must be
					 * set to access Card Information Structure 
					 */
#define MEM_OFFSET_WP	0x80	/* write protect this window */
/* 
 * Used with INTR_AND_CONTROL register 
 */
#define RING_ENABLE	  0x80		/* Ring Indicate Enable */
#define NOT_RESET	  0x40		/* RESET signal to the card socket is set
					 * inactive.  Used with ATA mode functions
					 */
#define IOCARD            0x20		/* I/O Card Interface mode -- I/O or mem card type */
#define INTR_ENABLE	  0x10
#define IRQ_MASK	  0x0F

/* 
 * Used with CARD_STAT_CHANGE and MGMT_INTR_CNFG registers
 */
#define BATTERY_STATUS		0x01	/* Battery Dead or Status Change Enable */
#define BATTERY_WARN		0x02	/* Battery Warning Enable */
#define READY_ENABLE		0x04	/* Ready Change mgmt interrupt Enable */
#define CARD_DETECT_ENABLE 	0x08	/* Card Detect Enable */
#define MGMT_INTR_SC_MASK 	0x0f
#define MGMT_INTR_CNFG_IRQ_SHIFT 4

/* 
 * Used with GLOBAL_CTL register 
 */
#define PWRDOWN			0x01
#define CSC_LEV_MODE		0x02	/* set to level mode interrupt for mgmt interrupt */
#define WRBACK_CSC		0x04	/* Explicit write back card status change interrupt acknowledge */
#define IRQ_SLOT0_LEV_MODE	0x08	/* set to level mode interrupt for socket 0 */
#define IRQ_SLOT1_LEV_MODE	0x10	/* set to level mode interrupt for socket 1 */

/* 
 * Used with MAPPING_ENABLE register
 */
#define MEM_MAP_ENABLE_0  0x01
#define MEM_MAP_ENABLE_1  0x02
#define MEM_MAP_ENABLE_2  0x04
#define MEM_MAP_ENABLE_3  0x08
#define MEM_MAP_ENABLE_4  0x10

#define IO_MAP_ENABLE_0   0x40
#define IO_MAP_ENABLE_1   0x80

/*
 * MISC_CTRL_1 bit definitions
 */

#define INPACK_ENA       0x80
#define SCRATCHPAD_1     0x40
#define SCRATCHPAD_0     0x20
#define SPEAKER_ENA      0x10
#define PULSE_SYS_IRQ    0x08
#define PULSE_MGMT_INT   0x04
#define VCC_33V          0x02

/*
 * MISC_CTRL_2 bit definitions
 */

#define IRQ15_RI_OUT     0x80
#define TIMER_CLK_DIVIDE 0x10
#define CORE_5V          0x08
#define SUSPEND_MODE     0x04
#define LOW_PWR_DYN_MODE 0x02
#define EX_CLK_ENA       0x01

/*
 * EXT_CONTROL_1 bit definitions
 */

#define PULL_UP_CTRL     0x20
#define INVERT_MGMT_IRQ  0x10
#define INVERT_CARD_IRQ  0x08
#define LED_ACTIVITY_ENA 0x04
#define AUTO_PRW_CLR     0x02
#define VCC_PWR_LOCK     0x01

/*
 * The PD6729 on the ALPHAbook 1 can only use interrupts: 3, 4, 5, 7, 10, and 15
 */

#define PD6729_INTERRUPT_MASK 0xDEB8;

/*
 * ISA Memory Space starting address to set up for memory window mapping
 *
 * (TBD) This address probably should be determined by the platform-specific
 *	 code, as each platform can have different set up/layout of the
 *	 memory space.
 */

#define ISA_MEM_START_ADDR 	0x80000		/* lowest address we can use */
#define ISA_MEM_END_ADDR	0xe0000		/* highest address we can use */

#endif  /* _PD6729_REG_H_ */
