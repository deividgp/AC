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
 * @(#)$RCSfile: pnvram_reg.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1995/04/24 18:35:54 $
 */

#ifndef _PNVRAM_REG_H_
#define _PNVRAM_REG_H_

/************************************************************************/
/*									*/
/* pnvram.h								*/
/*									*/
/* Digital PCI NVRAM presto driver					*/
/*									*/
/************************************************************************/

#include <io/common/devdriver.h>

/* 
 * PCI NVRAM register definitions
 */

/* 
 * Define offsets to nvram device registers
 * note: Mem-space mapped CSR's in same
 *	 location/offset in PCI config space,
 *	 and PCI Config. regs. in same location/offset
 *	 in PCI Mem.-mapped space.
 */ 
#define PNV_ID		0x00L		/* PCI VID/DID regs.		*/
#define PNV_CMD		0x04L		/* PCI Cmd reg.			*/
#define PNV_STAT	0x08L		/* PCI Status reg.		*/
#define PNV_BASE_ADDR1	0x10L
#define PNV_BASE_ADDR2  0x14L
#define PNV_ERROR	0x40L		/* Error Register 		*/
#define PNV_FADDR	0x44L		/* Failing Address Register	*/
#define PNV_MEM_CFG	0x48L		/* Memory Config Register	*/
#define PNV_EDC_CTRL	0x4CL		/* EDC Control Register		*/
#define PNV_EDC_SYND	0x50L		/* EDC Syndrome Register	*/
#define PNV_BAT_CTRL    0x54L		/* Battery Control/Status Reg.	*/
#define PNV_BAT_DIAG_RST 0x58L		/* Battery Diagnostic Reset Reg.*/
#define PNV_EEPROM_IF	0x5CL		/* EEPROM Interface Register	*/
#define PNV_SLAVE_ADDR  0x60L		/* DMA Slave Address Register	*/
#define PNV_MASTER_ADDR 0x64L		/* DMA Master Address Register 	*/
#define PNV_BYTE_COUNT  0x68L		/* DMA Byte Count Register	*/
#define PNV_DMA_CMD	0x6cL		/* DMA Command Register		*/
#define PNV_INTR_CTRL	0x70L		/* Interrupt Control Register	*/

/*
 * Bit definitions for Error Register
 */
#define PNVR_ERR_SUM	0x01	/* Error Summary bit 			*/
				/* Failing Addr & EDC Syndrome regs.
				 * frozen until this bit is cleared 	*/
#define PNVR_CMD_PAR	0x0010	/* Command/Address parity error 	*/
#define PNVR_WR_PAR	0x0020	/* Write data parity error		*/
#define PNVR_CRD_ERR	0x0040	/* Correctable EDC error		*/
#define PNVR_UCRD_ERR	0x0080	/* UnCorrectable EDC error		*/
#define PNVR_M_CMD_ERR	0x1000	/* Missed Command/Addr. parity error	*/
#define PNVR_M_WR_PAR	0x2000	/* Missed Write data parity error	*/
#define PNVR_M_CRD_ERR	0x4000	/* Missed Correctable EDC error 	*/
#define PNVR_M_UCRD_ERR	0x8000	/* Missed UnCorrectable EDC error 	*/

/*
 * Bit definitions for (NVRAM) Memory Configuration Register
 */
#define PNV_BANK_MASK		0x0003	/* Number of banks (1,2,4,rsvd)	*/
#define PNV_SIZE_MASK		0x000c	/* SRAM size: 256K,1M,4M, rsvd	*/
#define PNV_MOD_REV_MASK 	0x0070	/* Module Rev.			*/
#define PNV_CHIP_REV_MASK 	0x0F00	/* PCI chip rev.		*/
/* useful defines wrt Mem. Cnfg. Reg. to determine NVRAM size */
#define PNV_SIZE_SHIFT  1
#define PNV_512K	0x80000

/*
 * Bit definitions for EDC Control Register
 */
#define PNVR_DIS_CRD_LOG	0x1000	/* Disable EDC Status reg. 
					   logging for CRD's		*/
#define PNVR_DIS_EDC_SERR	0x8000	/* Disable assertion of PCI SERR
					   on Uncorrectable EDC error	*/

/* 
 * Bit definitions for Battery Control and Status Register
 */
#define PNV_BCHRG	0x001	/* Battery charge status 	*/
#define PNV_BDISC	0x002	/* Battery disconnet bit 	*/
#define PNV_BFAIL	0x004	/* Battery Failed to charge	*/
#define PNV_BAT_OK	0x008	/* State of battery 		*/
#define PNV_SPEED_MASK	0x300	/* PCI bus speed mask		*/

/*
 * Bit definitions for EEPROM Interface Register
 */
#define PNV_SCL		0x01	/* Serial Clock			*/
#define PNV_XMT_SDA	0x20	/* Serial Write Data		*/
#define PNV_RCV_SDA	0x40	/* Serial Read Data		*/

/*
 * define's for Byte Count register
 */
#define PNV_MAX_XFER_SIZE   65532	/* 64K less 4 bytes	*/

/* 
 * Bit definitions for DMA Command Register
 */
#define PNV_NV_READ     0x01	/* Move data from nvram to mem 	*/
#define PNV_NV_WRITE	0x02	/* Move data from mem to nvram 	*/

/*
 * Bit definitions for Interrupt Control Register
 */
#define PNV_ENAB_DMA	0x01
#define PNV_ENAB_CRD	0x02
#define	PNV_DISAB_ABRT	0x04	/* Set to 1 to not intr. on DMA abort */
#define PNV_DMA_INTR	0x100
#define PNV_CRD_INTR	0x200
#define PNV_ABRT_INTR	0x400	/* DMA Abort Intr */
#define PNV_INTR_OCCURRED (PNV_DMA_INTR | PNV_CRD_INTR | PNV_ABRT_INTR)

#define PNV_CACHE_OFFSET  0x400 /* reserved space			*/
#define PNV_DIAG_RESERVED 0x400 /* reserved space to store diag results	*/
#define PNV_DIAG_RESULT   0x08L	/* neg. offset from cache start where
				   diag. results are placed 		*/
#define PNV_DIAG_SIZE	  0x04  /* size of diag. results		*/
#define BOARD_FAILED	 0x0008 /* bit is set if board failed diags	*/

/*
 * Define constants used for upper layer presto commuication
 */
#define PNVRAM_MAPPED 	 1	/* buffer is mapped */
#define PNVRAM_NOTMAPPED 0	/* buffer is not mapped */
#define PNVRAM_CACHED	 1	/* Use kseg space */
#define PNVRAM_NOTCACHED 0	/* Use a cached space */

#define GET_SYSID	0x0008	/* Temp. define until devdriver.h updated */

#endif	/* _PNVRAM_REG_H_ */

