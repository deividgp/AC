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
 * @(#)$RCSfile: pci.h,v $ $Revision: 1.1.97.6 $ (DEC) $Date: 1998/12/04 21:49:44 $
 */
/****************************************************************/
/*								*/
/* MODULE NAME: pci.h						*/
/*								*/
/* LOCATION:	.../src/kernel/io/dec/pci			*/
/*								*/
/* DESCRIPTION:							*/
/*		Contains definitions for PCI bus support.       */
/*								*/
/* STRUCTURES:							*/
/*	pci_option	Defines PCI option table entry.		*/
/*	pci_intr_info	Contains per-intr. info on a PCI intr. 	*/
/*	pci_slot	Defines pci slot structure.		*/
/*	pci_sw		PCI switch table for platform indep.    */
/*			info.					*/
/*								*/
/* REVISION HISTORY:						*/
/*	8/6/93		Based on PCI Spec. V2.0			*/
/*								*/
/****************************************************************/

#ifndef	__PCI_H__
#define	__PCI_H__

#include <sys/types.h>
#include <io/common/handler.h>	/* for handler_* decl's */
#include <arch/alpha/hal/shared_intr.h>

/************************************************************************/
/* PCI Configuration Space Header Defintions				*/
/************************************************************************/

/************************************************/
/* Offsets within a Configuration Space Header	*/
/************************************************/
#define PCI_VID			0x00
#define PCI_DID			0x02
#define PCI_COMMAND		0x04
#define PCI_STATUS		0x06
#define PCI_REVID		0x08
#define PCI_PROG_IF_CODE	0x09
#define PCI_SUB_CLASS_CODE	0x0A
#define PCI_BASE_CLASS_CODE	0x0B
#define PCI_CACHE_LINE_SIZE	0x0C
#define PCI_LATENCY		0x0D
#define PCI_HEADER		0x0E
#define PCI_BIST		0x0F
/* Offsets for type 0 Config Header, bytes 17->64 */
#define PCI_BASE_REG0		0x10
#define PCI_BASE_REG1   	0x14
#define PCI_BASE_REG2   	0x18
#define PCI_BASE_REG3   	0x1C
#define PCI_BASE_REG4   	0x20
#define PCI_BASE_REG5   	0x24
#define PCI_CIS_PTR		0x28
#define PCI_SUBSYS_VID		0x2C
#define PCI_SUBSYS_DID		0x2E
#define PCI_EXP_ROM_BASE_REG	0x30
#define PCI_INTR_LINE		0x3C
#define PCI_INTR_PIN		0x3D
#define PCI_MIN_GNT		0x3E
#define PCI_MAX_LAT		0x3F
#define PCI_DEV_DEP_START	0x40
/* Offsets for type 1/PPB Config Header, bytes 17->64 */
/* bar0 & bar1 the same as type 0 config hdr */
#define PPB_PRI_BUS_NUM			0x18
#define PPB_SEC_BUS_NUM			0x19
#define PPB_SUB_BUS_NUM			0x1A
#define PPB_SEC_MAX_LAT			0x1B
#define PPB_IO_BASE			0x1C
#define PPB_IO_LIMIT			0x1D
#define PPB_SEC_STATUS			0x1E
#define PPB_MEM_BASE			0x20
#define PPB_MEM_LIMIT			0x22
#define PPB_PRE_MEM_BASE		0x24
#define PPB_PRE_MEM_LIMIT		0x26
#define PPB_PRE_BASE_UPPER		0x28
#define PPB_PRE_LIMIT_UPPER		0x2C
#define PPB_IO_BASE_UPPER		0x30
#define PPB_IO_LIMIT_UPPER		0x32
#define PPB_EXP_ROM_BASE_REG		0x38
/* PPB Intr Line & Intr Pin same as type 0 config header */
#define PPB_BRIDGE_CONTROL		0x3E

/****************************************************************/
/* PCI Configuration Space Header Register bit definitions	*/
/****************************************************************/

/************************/
/* Vendor ID Register 	*/
/************************/
#define OLD_NCR_ID      0x1000
#define ATI_ID          0x1002
#define DEC_ID          0x1011
#define CIRRUS_ID       0x1013
#define IBM_ID          0x1014
#define NCR_ID          0x101A
#define AMD_ID          0x1022
#define	SYMBIOS_ID	0x1026
#define TOSHIBA_ID    	0x102F
#define COMPAQ_ID       0x1032
#define NEC_ID          0x1033
#define HP_ID           0x103C
#define KPC_ID          0x1040 /* Kubota Pacific Corp. */
#define TI_ID           0x104C
#define SONY_ID         0x104D
#define MOT_ID          0x1057 /* Motorola */
#define MYLEX_ID        0x1069
#define APPLE_ID        0x106B
#define QLOGIC_ID       0x1077
#define CYPRESS_ID	0x1080
#define BIT3_ID         0x108A
#define	CMDTECH_ID	0x1095
#define	SYMPHONY_ID	0x10AD
#define CABLETRON_ID    0x10B1
#define THREE_COM_ID    0x10B7
#define ACER_ID         0x10B9
#define TCC_ID          0x10DA /* Thomas Conrad Corporation */
#define CERN_ID         0x10DC
#define ECP_ID          0x10DC
#define ECU_ID          0x10DC
#define ES_ID		0x10DD /* Evans & Sutherland */
#define TUNDRA_ID       0x10E3 /* Tundra Universe II */
#define PROTEON_ID      0x1108
#define	DATATECH_ID	0x1c1c
#define S3_ID		0x5333
#define INTEL_ID        0x8086
#define ADP_ID          0x9004
#define PCI_VID_INVALID 0xFFFF

/************************/
/* Device ID Register 	*/
/************************/
#define CA91C142        0X0000  /* Tundra Universe II VME Adapter */
#define DEC_PPB         0X0001  /* PCI-PCI bridge */
#define DEC_21040       0x0002  /* TULIP ethernet */
#define DEC_21041       0x0014  /* TULIP Pass 3 ethernet */
#define DEC_21140       0x0009  /* Original 10/100 Ethernet */
#define DEC_21142       0x0019  /* Newer 10/100 Ethernet (21143 id is same) */
#define DEC_DEFPA       0x000F  /* PCI FDDI */
#define DEC_DGLPB       0x0016  /* PCI-ATM/OTTO (oppo) */
#define DEC_DGLPA       0x0020  /* PCI-ATM/Meteor */
#define DEC_TGA         0x0004  /* TGA graphics */
#define DEC_TGA2        0x000d  /* TGA2 graphics */
#define DEC_NVRAM       0x0007  /* ZEPHYR presto-nvram */
#define DEC_PZA         0x0008  /* PZA SCSI */
#define DEC_7407        0x0010  /* VME interface processor */
#define DEC_PVP         0x0017  /* PVP graphics */
#define DEC_RM_SPUR     0x0018	/* DEC Reflective Memory */
#define DEC_SA285	0x1065	/* DEC StrongArm-PCI (Foot)bridge */
#define TI_COMET        0x3D07  /* COMET graphics */
#define INTEL_PCEB      0x0482
#define INTEL_SIO       0x0484
#define INTEL_I960_PPB	0x0960 /* PCI Bridge built into I960 */
#define INTEL_I960_ATU	0x1960 /* I2O-compliant ATU in I960 */
#define NCR_810         0x0001
#define NCR_825		0x0003
#define NCR_810A        0x0005
#define NCR_860		0x0006
#define NCR_896		0x000b
#define NCR_895		0x000c
#define NCR_875		0x000f
#define DATATECH_2130S	0x0001  /* Data Technology IDE card */
#define SYMPHONY_101P	0x0001  /* Symphony Lab IDE card */
#define SYMPHONY_105	0x0105  /* Symphony Lab IDE card */
#define SYMBIOS_89C621	0x0004  /* Symbios Logic 89C621 IDE chip */
#define CMD_PCI0646	0x0646  /* CMD Technology PCI0646 IDE chip */
#define CMD_PCI0640B	0x0640  /* CMD Technology PCI0640B IDE chip */
#define	CYPRESS_82C693	0xc693	/* Cypress CY82C693 multi-function chip */
#define ACER_M1543C     0x5229  /* Acer M1543C IDE */
#define NCR_825         0x0003
#define QLOGIC_ISP1020	0x1020	/* QLOGIC ISP1020 SCSI Adapter */
#define ADP_7870        0x7078
#define ATI_MACH32      0x4158
#define ATI_MACH64_CT   0x4354
#define ATI_MACH64_CX   0x4358
#define ATI_MACH64_GX   0x4758
#define MYLEX_960P	0x0001  /* PCI RAID */
#define S3_VISION864	0x88c0
#define S3_TRIO32       0x8810
#define S3_TRIO64       0x8811
#define TI_TMS380	0x0508	/* PCI Token Ring */
#define CIRRUS_PD6729	0x1100	/* CIRRUS LOGIC PD6729 PCMCIA Adapter */
#define	PCI_DID_INVALID 0xFFFF

/************************/
/* special defines for  */
/*  COMPAQ 1280/P VGA   */
/************************/
#define CPQ_1280P_VID	0x0E11
#define CPQ_1280P_DID	0x3032

/************************/
/* Command register 	*/
/************************/
/* Bit defs to provide coarse cntrl over device's PCI functionality */
#define	CMD_IO_SPACE	0x1	/* I/O space                   	*/
#define	CMD_MEM_SPACE	0x2	/* Memory space                	*/
#define	CMD_BUS_MASTER	0x4	/* Can be a PCI bus master     	*/
#define	CMD_SPEC_CYCLE	0x8	/* Enable special cycles       	*/
#define	CMD_MEM_WR_INV	0x10	/* Memory Write and Invalidate 	*/
#define	CMD_VGA_PALETTE	0x20	/* VGA palette snoop		*/
#define	CMD_PAR_ERR_RSP	0x40	/* Paritry error response      	*/
#define	CMD_WAIT_CYCLE	0x80	/* Wait cycle control          	*/
#define CMD_SERR_EN	0x100	/* SERR enable                 	*/
#define CMD_FAST_BBE	0x200	/* Fast Back-to-Back Enable	*/

/************************/
/* Status register 	*/
/************************/
#define STAT_66MHZ		0x20	/* 66 MHz Capable		*/
#define STAT_UDF		0x40	/* User Defined Features 	*/
#define STAT_FAST_BBE		0x80	/* Fast Back-to-Back capable	*/
#define	STAT_DATA_PAR		0x100	/* Data parity reported		*/
#define	STAT_DEVSEL_MASK 	0x600	/* Device select speed mask	*/
#define	STAT_DEVSEL_SLOW 	0x400	/* Device select slow       	*/
#define	STAT_DEVSEL_MED	 	0x200	/* Device select medium     	*/
#define	STAT_DEVSEL_FAST 	0x0	/* Device select fast       	*/
#define	STAT_SIG_TARG_ABRT 	0x800	/* Signaled a target abort  	*/
#define	STAT_RCVD_TARG_ABRT	0x1000	/* Received a target abort  	*/
#define	STAT_RCVD_MSTR_ABRT	0x2000	/* Received a master abort  	*/
#define	STAT_SIG_SYS_ERR	0x4000	/* Signaled a system error  	*/
#define	STAT_DET_PAR_ERR	0x8000	/* Detected a parity error  	*/

/************************/
/* Class codes		*/
/************************/
		/* Base class codes	*/
#define BASE_BC		0x00	/* Before Class defs. finalized */
#define BASE_MASS	0x01	/* Mass Storage controller	*/
#define BASE_NETWORK	0x02	/* Network controller		*/
#define BASE_DISPLAY	0x03	/* Display controller		*/
#define BASE_MULTMEDIA	0x04	/* Multimedia device		*/
#define	BASE_MEM	0x05	/* Memory controller		*/
#define BASE_BRIDGE	0x06	/* Bridge device		*/
#define BASE_COMM	0x07	/* Simple Communication ctrlrs. */
#define BASE_SYS_PERIPH	0x08	/* Generic System Peripherals	*/
#define BASE_INPUT	0x09	/* Input devices -- mouse,keybd */
#define BASE_DOCK	0x0A	/* Docking stations		*/
#define BASE_PROCESSOR	0x0B	/* Processor types		*/
#define BASE_SERIAL_BUS	0x0C	/* Serial bus cntrlrs		*/
#define BASE_WIRELESS	0x0D	/* Wireless cntrlrs		*/
#define BASE_INTELLIGENT 0x0E	/* Intelligent IO controllers	*/
#define BASE_SATELLITE	0x0F	/* Satellite Comm. controllers	*/
#define BASE_EN_DECRYPT	0x10	/* En/Decryption controllers	*/
#define BASE_DAC_DSP	0x11	/* Data Acq., Signal proc.	*/
#define BASE_UNKNOWN	0xFF	/* Doesn't fit any known class  */
		/* Subclass codes	*/
	/* Pre-class code subclass codes */
#define SUB_PREDEF	0x00	/* All pre-defined subclasses 	*/
#define	SUB_PRE_VGA	0x01	/* VGA compat. device		*/
	/* Mass Storage subclass codes */
#define SUB_SCSI	0x00	/* SCSI bus controller		*/
#define SUB_IDE		0x01	/* IDE controller		*/
#define	SUB_FDI		0x02	/* Floppy disk controller	*/
#define SUB_IPI		0x03	/* IPI bus controller		*/
#define	SUB_RAID	0x04	/* RAID controller		*/
#define SUB_MASS_OTHER	0x80	/* Other mass storage controllr */
	/* Network subclass codes */
#define SUB_ETHERNET	0x00	/* Ethernet controller		*/
#define SUB_TOKEN_RING  0x01	/* Token Ring controller	*/
#define SUB_FDDI	0x02	/* FDDI controller		*/
#define SUB_ATM		0x03	/* ATM controller		*/
#define SUB_NETWORK_OTHER 0x80	/* Other network controller	*/
	/* Display subclass codes */
#define SUB_VGA		0x00	/* VGA compatible controller	*/
#define SUB_XGA		0x01	/* XGA controller		*/
#define SUB_3D		0x02	/* 3D controller		*/
#define SUB_DISPLAY_OTHER 0x80	/* Other display controller	*/
	/* Multimedia subclass codes */
#define SUB_VIDEO	0x00	/* Video			*/
#define	SUB_AUDIO	0x01	/* Audio			*/
#define	SUB_MULTMEDIA_OTHER 0x80 /* other multimedia device */
	/* Memory controller subclasses */
#define	SUB_RAM		0x00	/* RAM				*/
#define SUB_FLASH	0x01	/* FLASH			*/
#define SUB_MEM_OTHER	0x80	/* Other memory controller	*/
	/* Bridge subclasses */
#define	SUB_HOST	0x00	/* Host bridge			*/
#define SUB_ISA		0x01	/* ISA bridge			*/
#define SUB_EISA	0x02	/* EISA bridge			*/
#define SUB_MC		0x03	/* MC bridge			*/
#define SUB_PCI		0x04	/* PCI-to-PCI bridge		*/
#define SUB_PCMCIA	0x05	/* PCMCIA bridge		*/
#define SUB_NUBUS	0x06	/* NuBus bridge			*/
#define SUB_CARDBUS	0x07	/* CardBus			*/
#define SUB_RACEWAY	0x08	/* RACEway			*/
#define SUB_BRIDGE_OTHER 0x80	/* Other bridge device		*/
	/* Communication controller subclasses */
#define SUB_PC_COMM	0x00	/* XT, 16450, 16550 Serial	*/
#define SUB_PARALLEL	0x01	/* Parallel Port Comm.		*/
#define SUB_MULTI_SERIAL 0x01	/* Multiport Serial controller	*/
#define SUB_COMM_OTHER	0x80	/* other comm. controller	*/
	/* System Component peripherals  */
#define SUB_8259_PIC	0x00	/* 8259 PIC's			*/
#define SUB_PC_PIC	0x00	/* PC-style PIC			*/
#define SUB_SLV_DMA	0x01	/* (E)ISA Slave DMA controllers */
#define SUB_TIMER	0x02	/* (Quantum) Timers		*/
#define SUB_RTC_TIMER	0x03	/* Real-time timers		*/
#define SUB_PCI_HOT_PLUG 0x04	/* PCI Hot-Plug controller	*/
#define SUB_SYS_OTHER	0x80	/* Other system peripheral	*/
	/* Input devices	*/
#define SUB_KEYBOARD	0x00	/* Keyboard controller		*/
#define SUB_PEN		0x01	/* Digitizer Pen		*/
#define SUB_MOUSE	0x02	/* Mouse controller		*/
#define SUB_SCANNER	0x03	/* Scanner controller		*/
#define SUB_GAMEPORT	0x04	/* Gameport controller		*/
#define SUB_INPUT_OTHER	0x80	/* Other input controller	*/
	/* Docking stations	*/
#define SUB_DOCKING	0x00	/* Generic Docking station	*/
#define SUB_DOCK_OTHER	0x80	/* other docking station	*/
	/* Processor type subclass	*/
#define	SUB_386		0x00	/* 386				*/
#define SUB_486		0x01	/* 486				*/
#define SUB_PENTIUM	0x02	/* Pentium			*/
#define SUB_ALPHA	0x10	/* ALPHA			*/
#define SUB_POWERPC	0x20	/* PowerPC			*/
#define SUB_COPROC	0x40	/* Co-processor			*/
	/* Serial bus controllers	*/
#define SUB_P1394	0x00	/* Firewire, IEEE 1394		*/
#define SUB_ACCESS	0x01	/* ACCESS.bus			*/
#define SUB_SSA		0x02	/* SSA				*/
#define SUB_USB		0x03	/* Universal Serial Bus		*/
#define SUB_FIBRE_CHNNL 0x04	/* Fibre Channel		*/
#define SUB_SMBUS	0x05	/* SMBus (System Mgmt Bus)	*/
	/* Wireless subclasses		*/
#define SUB_IRDA	0x00	/* iRDA compatible controller	*/
#define SUB_CONSUMER_IR 0x01	/* Consumber IR controller	*/
#define SUB_RF		0x10	/* RF controller		*/
#define SUB_WIRELESS_OTHER 0x80	/* Other wireless controller	*/
	/* Intelligent IO controllers	*/
#define SUB_I2O		0x00	/* I2O architecture		*/
	/* Satellite communication subclasses */
#define SUB_SAT_TV	0x01	/* TV				*/
#define SUB_SAT_AUDIO	0x02	/* Audio			*/
#define SUB_SAT_VOICE	0x03	/* Voice			*/
#define SUB_SAT_DATA	0x04	/* Data				*/
	/* Encryption/Decryption subclasses	*/
#define SUB_NET_COMP_ENC_DEC 0x00 /* Net.& Compute En/Decrypt.	*/
#define SUB_ENT_ENC_DEC	0x10	/* Entertainment En/Decryption	*/
#define SUB_ENC_DEC_OTHER 0x80	/* Other En/Decryption		*/
	/* Data acquistion & signal processing subclasses */
#define SUB_DPIO	0x00	/* DPIO modules			*/
#define SUB_DAC_DSP_OTHER 0x80	/* OTHER dac/dsp controllers	*/

/*******************************/
/* Programming Interface Codes */
/*******************************/
	/* IDE PIF values */
#define PIF_IDE_MASTER	 0x80	/* Master IDE Device		*/
#define PIF_IDE_PROG_SEC 0x08	/* Programmable Secondary flag	*/
#define PIF_IDE_PROG_PRI 0x02	/* Programmable Primary flag	*/
#define PIF_IDE_OPM_SEC  0x04	/* Operating Mode, Secondary	*/
#define PIF_IDE_OPM_PRI  0x01	/* Operating Mode, Primary	*/
	/* VGA PIF values */
#define PIF_VGA_COMPAT	 0x00	/* VGA Compatible		*/
#define PIF_8514_COMPAT	 0x01	/* 8514 Compatible		*/
	/* Bridge PIFs */
#define PIF_PCI_PPB	 0x00	/* PPB Arch. PCI bridge		*/
#define PIF_PCI_SUB_DEC	 0x01	/* Subtractive decode PPB	*/
	/* Communication PIFs */
#define PIF_XT_SERIAL	 0x00	/* XT Compatible Serial Ctlr	*/
#define PIF_16450_SERIAL 0x01	/* 16450 Compat. Serial Ctlr	*/
#define PIF_16550_SERIAL 0x02	/* 16550 Compat. Serial Ctlr	*/
#define PIF_PARALLEL	 0x00	/* Parallel Port (generic?)	*/
#define PIF_BI_PARALLEL	 0x01	/* Bidirectional Parallel port	*/
#define PIF_ECP_PARALLEL 0x02	/* ECP 1.x Compliant Parallel	*/
	/* System Component PIFs */
#define PIF_8259_PIC	 0x00	/* Generic 8259 PIC		*/
#define PIF_ISA_8259	 0x01	/* ISA PIC			*/
#define PIF_EISA_8259	 0x02	/* EISA PIC			*/
#define PIF_IO_APIC	 0x10	/* I/O APIC PIC			*/
#define PIF_8237_DMA	 0x00	/* 8237 DMA controller		*/
#define PIF_ISA_DMA	 0x01	/* ISA DMA controller		*/
#define PIF_EISA_DMA	 0x02	/* EISA DMA controller		*/
#define PIF_8254_TIMER	 0x00	/* Generic 8254 Sys. Timer	*/
#define PIF_ISA_TIMER	 0x01	/* ISA System Timer		*/
#define PIF_EISA_TIMER	 0x02	/* EISA System Timer		*/
#define PIF_RTC_TIMER	 0x00	/* Generic RTC controller	*/
#define PIF_ISA_RTC	 0x01	/* ISA RTC Controller		*/
	/* Gameport PIFs */
#define PIF_GAME_GENERIC 0x00	/* Gameport controller, generic */
#define PIF_GAME_LEGACY	 0x10	/* Gameport controller, legacy	*/
	/* IEEE 1394 PIFs */
#define PIF_1394_FW	 0x00	/* IEEE 1394 FireWire		*/
#define PIF_1394_OHCI	 0x10	/* IEEE 1394, 1394 OpenHCI	*/
	/* USB PIF's */
#define PIF_USB_UHCI	 0x00	/* USB Universal HCI		*/
#define PIF_USB_OHCI	 0x10	/* USB OpenHCI			*/
#define PIF_USB_OTHER    0x80	/* USB, other/no-specific pif	*/

/************************/
/* Cache Line Size Reg. */
/************************/
#define CACHE_LINE_SIZE(x)	((int)(x << 2))	/* Cache line size in bytes */

/************************/
/* Header Type Reg.	*/
/************************/
#define HDR_MULTI_FCN	0x80	/* If set, device is multi-function */
#define	HDR_LAYOUT_MASK 0x7F	/* Mask to extract 10h-3Fh config hdr type */
#define HDR_LAYOUT_V2	0x00	/* V2 config type for 10h-3Fh	    */

/************************/
/* BIST Register	*/
/************************/
#define BIST		0x80	/* BIST capable              */
#define BIST_START	0x40	/* Start BIST                */
#define BIST_STAT_MASK  0X0F	/* BIST completion code mask */
#define BIST_PASSED	0x0	/* BIST passed = 0	     */

/*************************/
/* Base Address Register */
/*************************/
#define BAR_MEM_MAP	0x0	/* Register maps into Memory space   */
#define BAR_MEM_MAP_32B 0x0	/* Map in 32-bit PCI addr. space     */
#define BAR_MEM_MAP_1M	0x2	/* Map in low 1 Meg. PCI addr. space */
#define BAR_MEM_MAP_64B 0x4	/* Map in 64-bit PCI addr. space     */
#define BAR_MEM_MAP_RSVD 0x6	/* Reserved mapping		     */ 
#define BAR_IO_MAP  	0x1	/* Register maps into I/O space      */
#define BAR_PREFETCH	0x8	/* No read side affects, etc.	     */
/* Masks for various bit fields */
#define BAR_SPACE_MASK	0x1	/* Mask Mem/IO bit space indicator   */
#define BAR_MEM_MASK	0x6	/* Mask MEM space bits		     */
#define BAR_PREFETCH_MASK 0x8	/* Mask Prefetchable bit	     */

/********************************/
/* CardBus CIS Pointer Register */
/********************************/
#define CISPTR_SPACE_MASK	0x700000000  /* Bits 30:28	     */
#define CISPTR_SPACE_SHIFT	28	     /* Shift for compare    */
#define CISPRT_SPACE_CONFIG	0x0	     /* CIS in Config. space */ 
#define CISPRT_SPACE_BAR0	0x1	     /* CIS in bar0 space    */ 
#define CISPRT_SPACE_BAR1	0x2	     /* CIS in bar1 space    */ 
#define CISPRT_SPACE_BAR2	0x3	     /* CIS in bar2 space    */ 
#define CISPRT_SPACE_BAR3	0x4	     /* CIS in bar3 space    */ 
#define CISPRT_SPACE_BAR4	0x5	     /* CIS in bar4 space    */ 
#define CISPRT_SPACE_BAR5	0x6	     /* CIS in bar5 space    */ 
#define CISPRT_SPACE_EXPROM	0x7	     /* CIS in Exp. ROM space */ 
#define CISPRT_CONFIG_MASK 	0x000000ff   /* Config space offset  */
#define CISPRT_BAR_MASK 	0x0fffffff   /* BAR space offset     */
#define CISPRT_EXPROM_MASK 	0x00ffffff   /* Exp.ROM space offset */
#define CISPRT_IMAGE_NUM_MASK	0x0f000000   /* Config space offset  */

/****************************************/
/* Expansion ROM Base Address Register	*/
/****************************************/
#define	EXP_ROM_BASE_MASK 0xFFFFF800  	/* Upper 21-bits of ROM addr. */
/* Note: next bit AND Mem. space bit in Command Reg. 
 *       must be set to enable access to expansion ROM.
 */
#define EXP_ROM_ENABLE	  0x1		/* ROM Addr. decode enable    */

/************************/
/* Interrupt Pin Reg.	*/
/************************/
#define	INTR_PIN_INTA	0x01	/* Device using PCI INTA intr pin */
#define	INTR_PIN_INTB	0x02	/* Device using PCI INTB intr pin */
#define	INTR_PIN_INTC	0x03	/* Device using PCI INTC intr pin */
#define	INTR_PIN_INTD	0x04	/* Device using PCI INTD intr pin */


/********************************/
/* PCI Expansion ROM Header	*/
/********************************/
/*
 * PCI Expansion ROM contents
 *
 * ROMs can contain multiple images (to support various architectures).
 * Each image has it's own header.
 */
struct pci_rom_exp_header {
	u_short	rom_sig;	/* Must contain PCI_ROM_SIG = AA55	*/
	union {
	   struct {      	/* PC-compatible Exp. ROM header	*/
		u_char	isize;  /* Init size in units of 512 bytes	*/
		u_char	ientry[3]; /* For intel: 3-byte offset/entry pt	*/ 
	   } init_vec;
	   struct {
		u_char rsvdb[4];/* Rsrvd (processor arch. unique data)	*/
	   } exp_hdr_rsvd;	/*  2H -> 5H				*/
	} rsvd0;
	u_char	rsvd1[18];	/*  6H -> 17H				*/
	u_short	pci_rom_data_off; /* Offset to PCI Data Structure	*/
};

/****************************************/
/* PCI Data Structure in Expansion ROM	*/
/****************************************/
struct pci_rom_data {
	u_int	signature;	/* Signature string "PCIR"	   */
	u_short	vendor_id;	/* Vendor id                       */
	u_short	device_id;	/* Device id                       */
	u_short	vital_data_off;	/* Offset to vital product data    */
	u_short	struct_len;	/* Size of this structure in bytes */
	u_char  struct_rev;	/* Revision of PCI Data Structure  */
	struct	class_code {	/* Class code                      */
		u_char	pio_int;
		u_char	sub_class;
		u_char	base;
	} class_code;
	u_short image_length;	/* Length of image, units of 512 bytes 	*/
	u_short	code_revision;	/* ROM code revision level            	*/
	u_char	code_type;	/* Type of code in this ROM segment   	*/
	u_char	indicator;	/* Last image in ROM if bit 7 = 0	*/
	u_short	rsvd;		/* Reserved				*/
};
/* Known defines for PCI data structure */
#define PCI_ROM_SIGNATURE	0xAA55	/* Value of PCI ROM sig. bytes	*/
#define INTEL_ROM_CODE_TYPE 	0x0	/* Intel x86, PC-AT compat.	*/
#define OPENFW_ROM_CODE_TYPE 	0x1	/* Open Firmware std for PCI	*/
#define OPENBOOT_ROM_CODE_TYPE 	0x1	/* For bckwd compat. to V2.0	*/
#define PCI_DATA_STRUCT_V2	0x0	/* Struct. rev. value for V2.0	*/
#define ROM_LAST_IMAGE		0x80	/* Last image in ROM		*/


/************************************************************************/
/*									*/
/* OSF Specific data structs, defines, etc. for PCI Bus Support		*/
/*                                                                      */
/************************************************************************/

#define PCI_NAMELEN	15	/* Length of driver, ctrl etc names. 	*/
#define MAX_PCI_SLOTS	32	/* Per the spec, although 21 looks ok	*/
#define MAX_FCN_PER_SLOT 8  	/* Per the spec 			*/
#define MAX_PCI_BUSSES 256	/* Max. PCI's per system, per spec.	*/
#define QUIET		 0	/* to print or not to print....		*/
#define VERBOSE		 1

/****************************************/
/* PCI Configuration Header structure	*/
/****************************************/
/* Design notes:
 *  (1) The following is *not* a direct duplicate/copy of a PCI device's
 *	Configuration header, especially the Base Address Register's 
 *	(bar's).  bar's are always io_handle's and are the io_handle-mapped
 *	value's of the device's bar value(s). 
 *	Use of any other ptr-offset arithmetic that is not
 *	based on the following data structure's and their elements/members
 *	(by driver's) risks binary portability/compatibility.
 *  (2) This data structure is 128 bytes (16 Quadwords = 16 *8 bytes).
 *	It is *important* to maintain the size of this structure below
 *	128 bytes due to dynamic memory allocation of these structures
 *	by the kernel allocator, which is a power-of-2 allocator.
 *  (3) Reserved elements/members exist to either match V2.0 of PCI
 *	Arch. Spec., V1.0 PPB Arch. Spec., or to pad elements to
 *	natural boundaries (ensuring binary compatibility overtime).
 *  (4) Define's following the pci_config_hdr structure are provided 
 *	to ease C code from having to explicitly specify union'd data
 *	structure's (config header bytes 48->64).
 */
struct pci_config_hdr {
/* 64 byte predefined header of 256 byte config space for every device 	*/
/* First 16 bytes defined the same for all types of devices. 		*/
	u_short	vendor_id;		/* Vendor id 			*/
	u_short	device_id;	        /* Device id 			*/
	u_short	command;	        /* Command 			*/
	u_short	status;			/* Status  			*/
	u_char	rev_id;		        /* Device revision ID 		*/
	struct	class_code class_code;  /* Class code 			*/
	u_char	cache_line_size;	/* System cache-size, 32b words */
	u_char	latency_timer;		/* Bus latency timer		*/
	u_char	hdr_type;		/* Defines type for 10h-3Fh 	*/
	u_char	bist;			/* Built in self test 		*/
/* Next 48 bytes have diff. layouts based on device's base function. 	*/
/* Note: For bar(Base Address Register) values --
 *	 Upper (32-)bits used to store per-platform mapping info;
 *	 Lower (32-)bits native PCI address (lower 4-bits 0'd).
 */
	union {
	    struct {
	/* 1 */	 io_handle_t	bar0;	     /* Base address reg 0 	*/
	/* 2 */	 io_handle_t	bar1;	     /* Base address reg 1 	*/
	/* 3 */	 io_handle_t	bar2;	     /* Base address reg 2 	*/
	/* 4 */	 io_handle_t	bar3;	     /* Base address reg 3 	*/
	/* 5 */	 io_handle_t	bar4;	     /* Base address reg 4 	*/
	/* 6 */	 io_handle_t	bar5;	     /* Base address reg 5	*/
	/* 7 */	 u_long		rsvd0;	     /* Reserved 		*/
	/* 8 */	 u_long		rsvd1;	     /* Reserved 		*/
	/* 9 */	 io_handle_t	exp_rom_bar; /* Expansion ROM address 	*/
	/* 10 */ u_long		cis_ptr;     /* Cardbus CIS Pointer	*/
	/* 11 */ u_short 	sub_vendor_id; /* Subsystem Vendor ID	*/
		 u_short	sub_device_id; /* Subsystem Device ID	*/
		 u_int		rsvd3;	     /* reserved; align qw	*/
	/* 12 */ u_char		intr_line;   /* Interrupt line 		*/
	 	 u_char		intr_pin;    /* Interrupt pin		*/
		 u_char		min_gnt;     /* Minimum grant 		*/
		 u_char		max_lat;     /* Maximum latency 	*/
		 u_int		rsvd4;	     /* Align to next qw bound	*/
	    } type0;
	    struct {
	/* 1 */	 io_handle_t bar0;           /* Base address reg 0      */
	/* 2 */	 io_handle_t bar1;           /* Base address reg 1      */
	/* 3 */	 u_char pri_bus_num; 	     /* Primary PCI bus number	*/
		 u_char	sec_bus_num; 	     /* Secondary PCI bus num.	*/
		 u_char	sub_bus_num; 	     /* Subordinate PCI bus num */
		 u_char	sec_max_lat;         /* Secondary max. latency	*/
		 u_char	io_base;             /* IO-space base		*/
		 u_char	io_limit;	     /* IO-space limit		*/
		 u_short sec_status;	     /* Secondary bus status	*/
	/* 4 */	 u_short mem_base;	     /* Mem-space space		*/
		 u_short mem_limit;	     /* Mem-space limit		*/
		 u_short premem_base; 	     /* Prefetch. mem base  	*/
		 u_short premem_limit;       /* Prefetch. mem limit 	*/
	/* 5 */	 u_int	premem_base_upper;   /* 64b Prefetch. mem. base	*/
		 u_int	premem_limit_upper;  /* 64b Prefetch. mem limit	*/
	/* 6 & 7*/
		 u_short io_base_upper;	     /* >64K IO-space base	*/
		 u_short io_limit_upper;     /* >64K IO-space limit	*/
		 u_int	rsvd5[3];	     /* Reserved; & align	*/
	/* 8 */	 io_handle_t ppb_exp_rom_bar; /* PPB Exp. Rom address 	*/
	/* 9,10, & 11 */
		 u_long	rsvd6[3];    	     /* Align to type0 struct  	*/
	/* 12 */ u_char  intr_line;  	     /* Interrupt line          */
		 u_char  intr_pin;   	     /* Interrupt pin 		*/
		 u_short bridge_ctl;         /* Bridge control		*/
		 u_int	rsvd7;	     	     /* Align to qw boundary 	*/
	    } type1;
	} hdrtype_u;
/* Device specific regs. start here, location 64, through 255 */
	u_long	private;      	/* device (driver) specific use */
	io_handle_t  config_base;  	/* slot's config space base	*/
};

/* Define's for simpler looking code for primary (type0) config hdr's */
#define bar0 hdrtype_u.type0.bar0	/* same offset for type1 also */
#define bar1 hdrtype_u.type0.bar1	/* same offset for type1 also */
#define bar2 hdrtype_u.type0.bar2
#define bar3 hdrtype_u.type0.bar3
#define bar4 hdrtype_u.type0.bar4
#define bar5 hdrtype_u.type0.bar5
#define cis_ptr hdrtype_u.type0.cis_ptr
#define sub_vendor_id hdrtype_u.type0.sub_vendor_id
#define sub_device_id hdrtype_u.type0.sub_device_id
#define exp_rom_bar hdrtype_u.type0.exp_rom_bar
#define intr_line hdrtype_u.type0.intr_line /* same offset for type1 also */
#define intr_pin hdrtype_u.type0.intr_pin   /* same offset for type1 also */
#define min_gnt hdrtype_u.type0.min_gnt
#define max_lat hdrtype_u.type0.max_lat
/* Define's for simpler looking code for PPB (type1) config hdr's */
#define ppb_pri_bus_num hdrtype_u.type1.pri_bus_num
#define ppb_sec_bus_num hdrtype_u.type1.sec_bus_num
#define ppb_sub_bus_num hdrtype_u.type1.sub_bus_num
#define ppb_sec_max_lat hdrtype_u.type1.sec_max_lat
#define ppb_io_base hdrtype_u.type1.io_base
#define ppb_io_limit hdrtype_u.type1.io_limit
#define ppb_sec_status hdrtype_u.type1.sec_status
#define ppb_mem_base hdrtype_u.type1.mem_base
#define ppb_mem_limit hdrtype_u.type1.mem_limit
#define ppb_pre_mem_base hdrtype_u.type1.premem_base
#define ppb_pre_mem_limit hdrtype_u.type1.premem_limit
#define ppb_pre_base_upper hdrtype_u.type1.premem_base_upper
#define ppb_pre_limit_upper hdrtype_u.type1.premem_limit_upper
#define ppb_io_base_upper hdrtype_u.type1.io_base_upper
#define ppb_io_limit_upper hdrtype_u.type1.io_limit_upper
#define ppb_exp_rom_bar hdrtype_u.type1.ppb_exp_rom_bar
#define ppb_bridge_ctl hdrtype_u.type1.bridge_ctl

/* Typedefs */
typedef struct pci_config_hdr pci_config_hdr_t;
typedef struct pci_rom_exp_header pci_rom_exp_header_t;
typedef struct pci_rom_data   pci_rom_data_t;


/****************************************/
/* PCI Config cycle formats/masks	*/
/****************************************/
/* 
 * TYPE 0:  
 * +-----------------------------------------+-----+-----------+-+-+
 * |                RESERVED                 |Fcn #|Reg. Number|0|0|
 * +-----------------------------------------+-----+-----------+-+-+
 *  31                                     11 10  8 7         2 1 0
 *
 * TYPE 1:
 * +---------------+---------------+---------+-----+-----------+-+-+
 * | Reserved      |   Bus Number  |Dev. No. |Fcn #|Reg. Number|0|1|
 * +---------------+---------------+---------+-----+-----------+-+-+
 *  31           24 23           16 15     11 10  8 7          2 1 0
 */
#define	PCI_CNFG_FCN_MASK 	0x00000700
#define	PCI_CNFG_REG_MASK	0x000000FC
#define	PCI_CNFG_DEV_MASK	0x0000F800
#define	PCI_CNFG_BUS_MASK	0x00FF0000
#define PCI_CNFG_FCN_SHIFT	8
#define PCI_CNFG_DEV_SHIFT	11
#define PCI_CNFG_BUS_SHIFT	16
/* flags for pci config cycle interface routine */
#define PCI_CNFG_TYPE0		0x00000001
#define PCI_CNFG_TYPE1		0x00000002
#define	PCI_CNFG_READ		0x00000010
#define	PCI_CNFG_WRITE		0x00000020
#define PCI_CNFG_BADADDR	0x00000040	/* do BADADDR on read */
/* size defs for pci config cycle interface routine */
#define	PCI_CNFG_BYTE		0x1
#define	PCI_CNFG_WORD		0x2
#define	PCI_CNFG_LONGWORD	0x4
#define	PCI_CNFG_DWORD		0x4 /* same as longword */
#define	PCI_CNFG_QWORD		0x8 /* quadword		*/


/****************************************************************/
/* PCI option data structure, used by 				*/
/* .../src/kernel/data/pci_option_data.c which contains info    */
/* on options that may be installed on a system.		*/
/****************************************************************/

#define PCI_CURRENT_SW_VERSION 0x210
/* 
 * HW-SW rev. V2.1.0
 *	-- supports V2.1 of PCI spec.
 *	-- first DEC-OSF/1 sw rev (for V3.3)
 */
struct	pci_option {
   u_short   pcisw_version;	/* Data struct, sw-config version i.d.  */
				/* bits 8-11 is major rev. of PCI spec.
				 * this structure & sw supports;
				 * bits 4-7 are minor rev. of PCI spec.
				 * bits 0-3 are sw-support of bits 11:4
				 */
				/* Note: SW checks this short to be 
				 *       < 0x0999 to ensure some numerical
				 *       distance from existing vendor_id's
				 *	starting at 0x1000, and some 
				 *	insurance from random, unapproved
				 *	vendor-id's < 0x1000. This format
				 *	and sw-check is done for binary-
				 *	compatibility to old(er) pci_option
				 *	data structure (no version, no
				 *	sub_vendor_id, no sub_device_id 
				 */
   u_short   vendor_id;	  	/* Vendor ID				*/
   u_short   device_id;	  	/* Device ID				*/
   u_char    rev;		/* HW rev.				*/
   u_char    base;		/* Base class code			*/
   u_char    sub;		/* Sub-class code			*/
   u_char    pif;		/* Prog. i/f code of class code		*/
   u_short   sub_vid;		/* Subsystem Vendor ID			*/
   u_short   sub_did;		/* Subsystem Device ID			*/
   u_short   vid_mo_flag;	/* Match-on flag for vendor-id field	*/
   u_short   did_mo_flag;	/* Match-on flag for device-id field	*/
   u_char    rev_mo_flag;	/* Match-on flag for HW rev. field	*/
   u_char    base_mo_flag;	/* Match-on flag for base class field	*/
   u_char    sub_mo_flag;	/* Match-on flag for sub-class field	*/
   u_char    pif_mo_flag;	/* Match-on flag for prog. i/f field	*/
   u_short   sub_vid_mo_flag;	/* Match-on flag for subsys. vid field	*/
   u_short   sub_did_mo_flag;	/* Match-on flag for subsys. did field	*/
   char	   driver_name[PCI_NAMELEN+1]; /* config file name of interface	*/
   char	   type;		/* C = ctlr, A = Adapt., D = Device	*/
   int	   (*adpt_config)();	/* adapter config routine to call	*/
};


/*
 * Previous/original definition of pci_option data structure.
 * Defined and used for generic PCI config. code to be able to
 *	translate V2.0.0 format to the latest (any) format.
 * This format supports V2.0 of PCI spec, PCI SW rev. 0, used
 * in DEC-OSF/1 V2.0b->V3.2b
 */

struct pci_option_V200 {
   u_short   vendor_id;	  	/* Vendor ID				*/
   u_short   device_id;	  	/* Device ID				*/
   u_char    rev;		/* HW rev.				*/
   u_char    base;		/* Base class code			*/
   u_char    sub;		/* Sub-class code			*/
   u_char    pif;		/* Prog. i/f code of class code		*/
   u_short   vid_mo_flag;	/* Match-on flag for vendor-id field	*/
   u_short   did_mo_flag;	/* Match-on flag for device-id field	*/
   u_char    rev_mo_flag;	/* Match-on flag for HW rev. field	*/
   u_char    base_mo_flag;	/* Match-on flag for base class field	*/
   u_char    sub_mo_flag;	/* Match-on flag for sub-class field	*/
   u_char    pif_mo_flag;	/* Match-on flag for prog. i/f field	*/
   char	   driver_name[PCI_NAMELEN+1]; /* config file name of interface	*/
   char	   type;		/* C = ctlr, A = Adapt., D = Device	*/
   int	   (*adpt_config)();	/* adapter config routine to call	*/
};



/*****************************************************************/
/* PCI Switch Table for bus-level, hardware dependent functions. */
/*****************************************************************/
struct	pci_sw {
    int	(*enable_option)();	/* Fnc for enabling option interrupts   */
    int (*disable_option)();	/* Fnc for disabling option interrupts  */
    int (*clear_errors)();	/* Fnc to clear errors caused by probe  */
    int	(*adpt_config)();	/* bus-adapter config routine     	*/
    int  (*eoi)();		/* Issue eoi to PIC interrupt level.	*/
    io_handle_t sparse_io_base; /* io_handle for sparse io base address */ 
    io_handle_t sparse_mem_base;/* io_handle for sparse memory base address */
    io_handle_t dense_mem_base; /* io_handle for dense memory base address  */
    io_handle_t config_base;	/* Base addr of config space		*/
    u_long (*config_fcn)();	/* Function to perform config space access */
    int	ppb_based_pci;	 	/* Primary PCI = 0; Bridged PCI = 1	*/
    vm_offset_t (*busphys_to_iohandle)(); /* Fnc to return io handle    */
    ihandler_id_t (*handler_add)(); /* Function for installing an ISR	*/
    int (*handler_enable)();	/* Function for enabling an interrupt	*/
    int (*handler_disable)();	/* Function for disabling an interrupt	*/
    int (*handler_del)();	/* Function for removing an ISR		*/
    dma_map_info_t (*dma_get_maps)(); /* Function to get dma windows info */
    ihandler_id_t  (*(*mb_ppb)())(); /* Motherboard PPB check & fcn rtn	*/
    u_long	rsvd1;		/* reserved for future use		*/
    u_long	rsvd2;		/* reserved for future use		*/
    int (*request_resource)();	/* Function for requesting I/O resource	*/
    int (*release_resource)();	/* Function for releaseing I/O resource */
};				/* note: 176 bytes, 22 QW in size	*/

#ifdef _KERNEL
/* Used for kernel device<->driver matching code */
#define MO_SHIFT	 0
#define SUB_DID_MO_SHIFT MO_SHIFT
#define SUB_VID_MO_SHIFT (SUB_DID_MO_SHIFT + 1)
#define PIF_MO_SHIFT	 (SUB_VID_MO_SHIFT + 1)
#define SUB_MO_SHIFT	 (PIF_MO_SHIFT + 1)
#define BASE_MO_SHIFT	 (SUB_MO_SHIFT + 1)
#define REV_MO_SHIFT	 (BASE_MO_SHIFT + 1)
#define DID_MO_SHIFT	 (REV_MO_SHIFT + 1)
#define VID_MO_SHIFT	 (DID_MO_SHIFT + 1)

#define VID_MO_INT_FLAG     (1 << VID_MO_SHIFT)
#define DID_MO_INT_FLAG     (1 << DID_MO_SHIFT)
#define REV_MO_INT_FLAG     (1 << REV_MO_SHIFT)
#define BASE_MO_INT_FLAG    (1 << BASE_MO_SHIFT)
#define SUB_MO_INT_FLAG     (1 << SUB_MO_SHIFT)
#define PIF_MO_INT_FLAG     (1 << PIF_MO_SHIFT)
#define SUB_VID_MO_INT_FLAG (1 << SUB_VID_MO_SHIFT)
#define SUB_DID_MO_INT_FLAG (1 << SUB_DID_MO_SHIFT)

#define MO_BASE_PRIO	1
#define MO_CASE28_PRIO	(MO_BASE_PRIO) 
#define MO_CASE27_PRIO	(MO_CASE28_PRIO + 1)
#define MO_CASE26_PRIO	(MO_CASE27_PRIO + 1)
#define MO_CASE25_PRIO	(MO_CASE26_PRIO + 1)
#define MO_CASE24_PRIO	(MO_CASE25_PRIO + 1)
#define MO_CASE23_PRIO	(MO_CASE24_PRIO + 1)
#define MO_CASE22_PRIO	(MO_CASE23_PRIO + 1)
#define MO_CASE21_PRIO	(MO_CASE22_PRIO + 1)
#define MO_CASE20_PRIO	(MO_CASE21_PRIO + 1)
#define MO_CASE19_PRIO	(MO_CASE20_PRIO + 1)
#define MO_CASE18_PRIO	(MO_CASE19_PRIO + 1)
#define MO_CASE17_PRIO	(MO_CASE18_PRIO + 1)
#define MO_CASE16_PRIO	(MO_CASE17_PRIO + 1)
#define MO_CASE15_PRIO	(MO_CASE16_PRIO + 1)
#define MO_CASE14_PRIO	(MO_CASE15_PRIO + 1)
#define MO_CASE13_PRIO	(MO_CASE14_PRIO + 1)
#define MO_CASE12_PRIO	(MO_CASE13_PRIO + 1)
#define MO_CASE11_PRIO	(MO_CASE12_PRIO + 1)
#define MO_CASE10_PRIO	(MO_CASE11_PRIO + 1)
#define MO_CASE9_PRIO	(MO_CASE10_PRIO + 1)
#define MO_CASE8_PRIO	(MO_CASE9_PRIO + 1)
#define MO_CASE7_PRIO	(MO_CASE8_PRIO + 1)
#define MO_CASE6_PRIO	(MO_CASE7_PRIO + 1)
#define MO_CASE5_PRIO	(MO_CASE6_PRIO + 1)
#define MO_CASE4_PRIO	(MO_CASE5_PRIO + 1)
#define MO_CASE3_PRIO	(MO_CASE4_PRIO + 1)
#define MO_CASE2_PRIO	(MO_CASE3_PRIO + 1)
#define MO_CASE1_PRIO	(MO_CASE2_PRIO + 1)

/* X is a pointer to a pci_option structure */
#define MOFLAG_2_INT(X, MO_INT)\
        if (X->vid_mo_flag)	MO_INT += VID_MO_INT_FLAG;\
	if (X->did_mo_flag)	MO_INT += DID_MO_INT_FLAG;\
	if (X->rev_mo_flag)	MO_INT += REV_MO_INT_FLAG;\
	if (X->base_mo_flag)	MO_INT += BASE_MO_INT_FLAG;\
	if (X->sub_mo_flag)	MO_INT += SUB_MO_INT_FLAG;\
	if (X->pif_mo_flag)	MO_INT += PIF_MO_INT_FLAG;\
	if (X->sub_vid_mo_flag)	MO_INT += SUB_VID_MO_INT_FLAG;\
	if (X->sub_did_mo_flag)	MO_INT += SUB_DID_MO_INT_FLAG

   /*
    * The match is based on match-on flags being set in the
    * pci_option passed in and the matching priority/order
    * listed below.
    * The basic premise of the order is that hw-identification
    * (vid, did, rev) has higher precedence over sw-identification
    * (base, sub, pif).  Additionally, some cases don't make sense
    * (like base-class-only, vid-only, did-only, pif-only,
    * driver: e.g., a "graphics" driver, or a "disk" driver --
    * too generic for a driver).
    * So, if you assign a rating system of 1 pt. to each
    * element, use hw over sw precedence, and apply some common-
    * sense to what are viable sets of match-on fields, you get
    * the following list:  (see pci.h for details
    *  *** Rev 2.1.0 (PCI spec rev 2.1; OSF-PCI SW rev 0) ***
    *    1. vid, did, rev, base, sub, pif, sub_vid, sub_did
    *    2. vid, did, rev, base, sub,    , sub_vid, sub_did
    *    3. vid, did, rev, base, sub, pif, sub_vid
    *    4. vid, did,    , base, sub, pif, sub_vid, sub_did
    *    5. vid, did, rev, base,    ,    , sub_vid, sub_did
    *    6. vid, did, rev, base, sub     , sub_vid
    *    7. vid, did,    , base, sub,    , sub_vid, sub_did
    *    8. vid, did, rev, base, sub, pif
    *    9. vid, did,    , base, sub, pif, sub_vid
    *   10. vid, did, rev,     ,    ,    , sub_vid, sub_did
    *   11. vid, did, rev, base,    ,    , sub_vid
    *   12. vid, did,    , base,    ,    , sub_vid, sub_did
    *   13. vid, did, rev, base, sub
    *   14. vid, did,    , base, sub,    , sub_vid
    *   15. vid, did,    , base, sub, pif
    *   16. vid, did, rev,     ,    ,    , sub_vid
    *   17. vid, did,    ,     ,    ,    , sub_vid, sub_did
    *   18. vid, did, rev, base,    ,
    *   19. vid, did,    , base,    ,    , sub_vid
    *   20. vid, did,    , base, sub,
    *   21. vid,    ,    , base, sub, pif
    *   22. vid, did, rev,     ,    ,
    *   23. vid, did,    ,     ,    ,    , sub_vid
    *   24.    ,    ,    , base, sub, pif
    *   25. vid, did,    , base,    ,
    *   26. vid,    ,    , base, sub,
    *   27. vid, did,    ,     ,    ,
    *   28.    ,    ,    , base, sub,
    */

/* multi function support */
#define PCI_FNC_NUM(pci_slot) (((pci_slot)->slot_cnfg_p->config_base & PCI_CNFG_FCN_MASK) >> PCI_CNFG_FCN_SHIFT)

#define PCI_FNC_NUM_MULT 100
#define PCI_SLOT_WITHOUT_FUNCTION(slotnum) ((slotnum)%PCI_FNC_NUM_MULT)
#endif /* _KERNEL */

/****************************************************************/
/* PCI intr. handler_add/del/enable/disable info structure	*/
/****************************************************************/
struct pci_intr_info {
        struct pci_slot *pci_slotp;     /* pci_slot for this intr       */
        ihandler_id_t   handler_key;    /* parent rtn'd hid             */
        caddr_t         intr_param;     /* passed-in intr param         */
        int             (*intr)();      /* Interrupt routine for device */
        int             flags;          /* various flags                */
        struct pci_intr_info *next;     /* link of intr's on this slot  */
};


/*
 * Structure connected to (per-PCI device) pci_slot struct
 * that contains the matching-driver info extracted from the
 * pci_option_data.c array or the sysconfigtab's PCI_Option
 * entries.
 *
 * Note: This structure is dynamically allocated, and thus,
 *	 is packed to fit a 32-byte space/size for power-of-2
 *	 malloc buckets.  
 *	 There is *no* "next"-linking ptr since it would grow
 *	 the structure past 32-bytes, which would fall into the
 *	 64-byte bucket, and waste alot of memory (esp. on larger 
 *	 servers).
 *	 So, when more than 1 driver matches a device, the
 *	 pci_dev_drvr_match() code must malloc a structure of
 *	 size (entry_num+1)*sizeof(struct pci_drvrs), copying
 *	 the previously allocated entry's into the new memory,
 *	 and freeing the old struct(s).
 *     : mo_case is a short since it contains a bit-flag
 *	 field that is 8-bits (a char) for a V210 pci_option match,
 *	 and room for growth in the field was desired.
 *     : entry_num is 8-bits since this allows 256 drivers to match
 *	 a single device -- that should be enough!
 *     : Driver_name and adpt_config must be kept the same size as
 *	 the old entries in struct pci_slot.
 *     : start structure with 64-bit ptr. to ensure 64-bit alignment.
 */
struct pci_drvr_info {
	int	(*adpt_config)();	/* adapter config fcn to call	*/
	char	entry_num;		/* effectively, max-cnt		*/
	char	class;			/* CTLR, ADPT, UNKNOWN		*/
	short	mo_case;		/* Int value of driver match-on */
	char    driver_name[PCI_NAMELEN+1]; /* config file driver name	*/ 
};

/*
 *      The following are used to describe the class attribute of the
 *      module.  These will be filled in during auto-configuration.
 *      These are also used to specify driver type in the config_type field
 *      of the pci_intr_info data structure.
 */
#define PCI_CTLR         1
#define PCI_DEV          2
#define PCI_ADPT         3
#define PCI_UNKNOWN      4	/* Module exists but we don't know what kind */
				/* it is.  Provided for loadable support.    */

/************************/
/* Per-slot/option data	*/
/************************/
struct	pci_slot {
   char         driver_name[PCI_NAMELEN +1];   /* Driver name                */
   int          slot;                   /* PCI IO slot number                */
   int          unit;                   /* Device unit number                */
   int          class;                  /* Indicates if device is a ctrlr    */
                                        /* or an adapter. Used to call       */
                                        /* correct config function.          */
   int		flags;			/* various flags                     */
   int          (*intr)();              /* Interrupt routine for device      */
   caddr_t      intr_param;		/* Param passed to isr		     */
   struct	pci_intr_info *handler_key; /* handler_add key               */
   int          (*adpt_config)();       /* Adapter config routine to call    */
   struct controller    *ctlr_p;        /* Pointer to controller structure   */
                                        /* if option in this slot is a ctlr. */
   struct bus   *bus_p;                 /* Pointer to bus structure if 	     */
                                        /* option in slot is a bus adapter.  */
   struct pci_config_hdr *slot_cnfg_p;  /* Pointer to slot's config info     */
   int		mo_case;		/* Int value of driver match-on case */
/* to round out struct to power of 2 -- 16 QW = 128 bytes		     */
   int		irsvd;
   struct pci_drvr_info *pci_drvr_info;	/* Driver info list ptr.	     */
   u_long	rsvd[2];		/* reserved -- for kernel use	     */
   struct pci_slot *next;		/* link to next struct in list       */
};

/* Attach pci_slot struct to this field of controller or bus struct */
#define pcislot	conn_priv[0]

/****************************************************************/
/* Flag definitions for flags field in pci_slot structure	*/
/****************************************************************/
#define PCI_ACTIVE	0x3	/* device id'd but not configd   */
#define PCI_INTA_ADD	0x10	/* INTA Handler add performed    */
#define PCI_INTB_ADD	0x20	/* INTB Handler add performed    */
#define PCI_INTC_ADD	0x40	/* INTC Handler add performed    */
#define PCI_INTD_ADD	0x80	/* INTD Handler add performed    */
#define PCI_INTA_ENAB	0x100	/* INTA Handler enable performed */
#define PCI_INTB_ENAB	0x200	/* INTB Handler enable performed */
#define PCI_INTC_ENAB	0x400	/* INTC Handler enable performed */
#define PCI_INTD_ENAB	0x800	/* INTD Handler enable performed */
/* Masks for above 4 bit fields   */
#define PCI_INTX_ADD_SLOT_MASK \
	(PCI_INTA_ADD | PCI_INTB_ADD | PCI_INTC_ADD | PCI_INTD_ADD)
#define PCI_INTX_ENAB_SLOT_MASK \
	(PCI_INTA_ENAB | PCI_INTB_ENAB | PCI_INTC_ENAB | PCI_INTD_ENAB)
/* Bit to be shifted into pci_slot->flags on add/enable/disable/delete */
#define PCI_INTX_ADD	(PCI_INTA_ADD >> 1)
#define PCI_INTX_ENAB	(PCI_INTA_ENAB >> 1)


/****************************************************************/
/* PCI-specific bus info structure passed to config routine     */
/* for a bus/bus-adapter connected to a PCI bus		        */
/****************************************************************/
struct	pci_bus_info {
   struct	common_bus_info	*common_bus_info; 
				 /* Ptr. to common bus base addrs	*/
   io_handle_t  config_base;	 /* Base addr of config space		*/
   u_long	(*config_fcn)(); /* Function to perform config space access 
				    on bus connected to 		*/
   int		ppb_based_pci;	 /* Primary PCI = 0, Bridged PCI = 1	*/
   struct bus	*bus_hd;	 /* Ptr. to bus head structure	      	*/
   struct pci_sw *pci_sw;	 /* Bus-level function switch table 	*/
};

/*
 * Extern statements for functions used by adapter config. fcns/modules
 * and/or per-platform PCI interfaces.
 */
extern	ihandler_id_t pci_handler_add();
extern	int pci_handler_del();
extern	int pci_handler_enable();
extern	int pci_handler_disable();

#ifdef _KERNEL
/*
 * PCI-related error logging data structures
 */

#define IS_EISA_BRIDGE(Pci_slotp) 					\
	(((Pci_slotp->slot_cnfg_p->vendor_id == INTEL_ID) &&		\
	  (Pci_slotp->slot_cnfg_p->device_id == INTEL_PCEB)) ||		\
	 ((Pci_slotp->slot_cnfg_p->class_code.base == BASE_BRIDGE) &&	\
	  (Pci_slotp->slot_cnfg_p->class_code.sub_class == SUB_EISA)) )
#define IS_ISA_BRIDGE(Pci_slotp) 					\
	(((Pci_slotp->slot_cnfg_p->vendor_id == INTEL_ID) &&		\
	  (Pci_slotp->slot_cnfg_p->device_id == INTEL_SIO)) ||		\
	 ((Pci_slotp->slot_cnfg_p->class_code.base == BASE_BRIDGE) &&	\
	  (Pci_slotp->slot_cnfg_p->class_code.sub_class == SUB_ISA)) )
#define PCI_CNFG_BUS_ADDR_MASK 				\
	(PCI_CNFG_REG_MASK | PCI_CNFG_FCN_MASK | 	\
	 PCI_CNFG_DEV_MASK | PCI_CNFG_BUS_MASK)

/* PCI bus subpacket header */
struct elr_pci_snap_hdr {
       u_int size;
       u_short phys_bus_id;
       u_short nodes;
};

/*
 * Compound data structure for configuration header of
 * standard & bridge PCI node for error logging.
 *
 * This could be made common for all PCI systems.
 */
struct elr_pci_cnfg_hdr_common {
    u_short e_vendor_id;      /* Vendor id                    */
    u_short e_device_id;      /* Device id                    */
    u_short e_command;        /* Command                      */
    u_short e_status;         /* Status                       */
    u_char  e_rev_id;         /* Data structure revision ID   */
    u_char  e_class_code[3];  /* Class code            */
    u_char  e_cache_line_size;
    u_char  e_latency_timer;
    u_char  e_hdr_type;       /* Defines type for 10h-3Fh     */
    u_char  e_bist;           /* Built in self test */
    union {
	struct {
	/* 1 */	 u_int	e_bar0;	/* Base address reg 0 	*/
	/* 2 */	 u_int	e_bar1;	/* Base address reg 1 	*/
	/* 3 */	 u_int	e_bar2;	/* Base address reg 2 	*/
	/* 4 */	 u_int	e_bar3;	/* Base address reg 3 	*/
	/* 5 */	 u_int	e_bar4;	/* Base address reg 4 	*/
	/* 6 */	 u_int	e_bar5;	/* Base address reg 5	*/
	/* 7 */  u_int	e_cis_ptr;        /* Cardbus CIS Pointer */
	/* 8 */  u_short e_sub_vendor_id; /* Subsystem Vendor ID */
		 u_short e_sub_device_id; /* Subsystem Device ID */
	/* 9 */	 u_int	e_exp_rom_bar; 	/* Expansion ROM address */
	/* 10 */ u_int	rsvd0;	     	/* reserved 		*/
	/* 11 */ u_int	rsvd1;	     	/* reserved 		*/
	/* 12 */ u_char	e_intr_line;   	/* Interrupt line 	*/
	 	 u_char	e_intr_pin;	/* Interrupt pin	*/
		 u_char	e_min_gnt;	/* Minimum grant 	*/
		 u_char	e_max_lat;	/* Maximum latency 	*/
	} type0;
	struct {
	/* 1 */	 u_int	e_bar0;	/* Base address reg 0 		*/
	/* 2 */	 u_int	e_bar1;	/* Base address reg 1 		*/
	/* 3 */	 u_char e_pri_bus_num;	/* Primary PCI bus number 	*/
		 u_char	e_sec_bus_num;	/* Secondary PCI bus num. 	*/
		 u_char	e_sub_bus_num;	/* Subordinate PCI bus num 	*/
		 u_char	e_sec_max_lat;	/* Secondary max. latency	*/
	/* 4 */	 u_char	e_io_base;	/* IO-space base		*/
		 u_char	e_io_limit;	/* IO-space limit		*/
		 u_short e_sec_status;	/* Secondary bus status		*/
	/* 5 */	 u_short e_mem_base;	/* Mem-space space		*/
		 u_short e_mem_limit;	/* Mem-space limit		*/
	/* 6 */  u_short e_premem_base;	/* Prefetch. mem base  		*/
		 u_short e_premem_limit;      /* Prefetch. mem limit 	*/
	/* 7 */	 u_int	e_premem_base_upper;  /* 64b Prefetch. mem. base */
	/* 8 */  u_int	e_premem_limit_upper; /* 64b Prefetch. mem limit */
	/* 9 */  u_short e_io_base_upper;     /* >64K IO-space base 	*/
		 u_short e_io_limit_upper;    /* >64K IO-space limit	*/
	/* 10 */ u_int	rsvd0;		 /* Reserved; 			*/
	/* 11 */ u_int	e_exp_rom_bar; /* PPB Exp. Rom address 	*/
	/* 12 */ u_char  e_intr_line;	 /* Interrupt line          */
		 u_char  e_intr_pin;	 /* Interrupt pin 		*/
		 u_short e_bridge_ctl;	 /* Bridge control		*/
	} type1;
    } elr_pci_hdrtype_u;
};


/* Define's for simpler looking code */
#define e_bar0 elr_pci_hdrtype_u.type0.e_bar0	/* type1 has same offset */
#define e_bar1 elr_pci_hdrtype_u.type0.e_bar1	/* type1 has same offset */
#define e_bar2 elr_pci_hdrtype_u.type0.e_bar2
#define e_bar3 elr_pci_hdrtype_u.type0.e_bar3
#define e_bar4 elr_pci_hdrtype_u.type0.e_bar4
#define e_bar5 elr_pci_hdrtype_u.type0.e_bar5
#define e_cis_ptr elr_pci_hdrtype_u.type0.e_cis_ptr
#define e_sub_vendor_id elr_pci_hdrtype_u.type0.e_sub_vendor_id
#define e_sub_device_id elr_pci_hdrtype_u.type0.e_sub_device_id
#define e_exp_rom_bar elr_pci_hdrtype_u.type0.e_exp_rom_bar /* type1 is same */
/* type0's intr_line & intr_pin has same offset as type1 */
#define e_intr_line elr_pci_hdrtype_u.type0.e_intr_line 
#define e_intr_pin elr_pci_hdrtype_u.type0.e_intr_pin
#define e_min_gnt elr_pci_hdrtype_u.type0.e_min_gnt
#define e_max_lat elr_pci_hdrtype_u.type0.e_max_lat
#define e_pri_bus_num elr_pci_hdrtype_u.type1.e_pri_bus_num
#define e_sec_bus_num elr_pci_hdrtype_u.type1.e_sec_bus_num
#define e_sub_bus_num elr_pci_hdrtype_u.type1.e_sub_bus_num
#define e_sec_max_lat elr_pci_hdrtype_u.type1.e_sec_max_lat
#define e_io_base elr_pci_hdrtype_u.type1.e_io_base
#define e_io_limit elr_pci_hdrtype_u.type1.e_io_limit
#define e_sec_status elr_pci_hdrtype_u.type1.e_sec_status
#define e_mem_base elr_pci_hdrtype_u.type1.e_mem_base
#define e_mem_limit elr_pci_hdrtype_u.type1.e_mem_limit
#define e_premem_base elr_pci_hdrtype_u.type1.e_premem_base
#define e_premem_limit elr_pci_hdrtype_u.type1.e_premem_limit
#define e_prebase_upper elr_pci_hdrtype_u.type1.e_premem_base_upper
#define e_prelimit_upper elr_pci_hdrtype_u.type1.e_premem_limit_upper
#define e_io_base_upper elr_pci_hdrtype_u.type1.e_io_base_upper
#define e_io_limit_upper elr_pci_hdrtype_u.type1.e_io_limit_upper
#define e_bridge_ctl elr_pci_hdrtype_u.type1.e_bridge_ctl

/*
 * pci snapshot header needed for DECanalyze support
 */
#define ELR_TYPE_DE		0 	/* DECevent */
#define ELR_TYPE_DA		1	/* DECanalyze */

#define ELR_DA_PCI_SNAP_SIZE	80
#define ELR_DA_PCI_CLASS	11
#define ELR_DA_PCI_DEV_TYPE	1
#define ELR_DA_PCI_BRIDGE_TYPE	2
#define ELR_DA_PCI_REV		1


/*
 * PCI device wrapper used by Platform's supported
 * by DECanalyze
 */
struct elr_da_pci_wrapper {
    u_short e_packet_length;  /* packet length */
    u_short e_packet_class;   /* packet class */
    u_short e_packet_type;    /* packet type */
    u_short e_packet_rev;     /* packet_rev  */
    u_int   e_pci_cnfg_space_addr_lo; /* pci node config space address */
    u_int   e_pci_cnfg_space_addr_hi; /* pci node config space address */
};

/*
 * PCI device wrapper used by Rawhide/Tlaser
 */
struct elr_pci_wrapper {
    u_int   e_pci_cnfg_space_addr_lo; /* pci node config space address */
    u_int   e_pci_cnfg_space_addr_hi; /* pci node config space address */
    u_int   e_pci_frame_size;
};

/*
 * use by Rawhide/TLaser platform code to describe the size of 
 * the header needed for each pci slot
 */
struct elr_pci_cnfg_hdr {
  struct elr_pci_wrapper wrapper;
  struct elr_pci_cnfg_hdr_common common;
};

/*
 * use by EV6/DECanalyze capable platform code to describe the 
 * size of the header needed for each pci slot
 */
struct elr_pci_cnfg_hdr_da {
  struct elr_da_pci_wrapper wrapper;
  struct elr_pci_cnfg_hdr_common common;
};

/*
 * Function prototypes for pci-related error logging 
 * by platform machine-check handlers.
 */
extern int elr_get_pcislot_count(int bus_num);
extern int elr_fill_pci_bus_snap(char **errlog_ptr, struct bus *busp);
extern int elr_set_snap_type(int snap_type);

/*
 * defines used by default pci handlers
 */
#define PCI_NO_IRQ			(-1)
#define PCI_ISA_INTR_LOW		0xE0
#define PCI_ISA_INTR_HIGH		0xEF
#define PCI_SET_INTMASK			1
#define	PCI_CLEAR_INTMASK		2
#define PCI_SCB_ISA_BASE		0x800
#define PCI_SCB_PCI_BASE		0x900
#define PCI_SCB_BUS_INDEX		0x200
#define PCI_SCB_PCI_SLOT_INDEX	0x40
#define PCI_SCB_PER_INTR_INDEX	0x10

/*
 * C/BE<3:0> field defines for PCI bus transaction command codes.
 */
#define PCI_CMD_IACK                    0x0
#define PCI_CMD_SPECIAL_CYCLE           0x1
#define PCI_CMD_IO_READ                 0x2
#define PCI_CMD_IO_WRITE                0x3
#define PCI_CMD_MEMORY_READ             0x6
#define PCI_CMD_MEMORY_WRITE            0x7
#define PCI_CMD_CONFIG_READ             0xA
#define PCI_CMD_CONFIG_WRITE            0xB
#define PCI_CMD_MEMORY_READ_MULT        0xC
#define PCI_CMD_DUAL_ADDRESS_CYCLE      0xD
#define PCI_CMD_MEMORY_READ_LINE        0xE
#define PCI_CMD_MEMORY_WRITE_AND_INVAL  0xF

#endif /* _KERNEL */

#endif	/* __PCI_H__ */






