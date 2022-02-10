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
 * @(#)$RCSfile: psiopdefs.h,v $ $Revision: 1.1.18.2 $ (DEC) $Date: 1997/03/25 17:04:35 $
 */

/* number of bytes needed for script processor script ram */
#define PSIOP_SCRIPT_RAM_SIZE (32 * 1024)

/* number of bytes needed for script processor local memory */
#define PSIOP_LOCAL_RAM_SIZE  (1 * 1024)

/* DEFINITIONS OF ADDRESSES OF PSIOP REGISTERS IN PCI SPACE AS SEEN FROM
 * THE PSIOP'S.  THIS IS USED TO MOVE DATA FROM CHIP REGISTERS TO MEMORY
 * WITH THE MEMORY MOVE INSTRUCTION.
 */

/* The NCR53c810 register set as defined by the NCR data sheet. */

#define SIOP_REG_SCNTL0		0x00
#define SIOP_REG_SCNTL1		0x01
#define SIOP_REG_SCNTL2		0x02
#define SIOP_REG_SCNTL3		0x03
#define SIOP_REG_SCID		0x04
#define SIOP_REG_SXFER		0x05
#define SIOP_REG_SDID		0x06
#define SIOP_REG_GPREG		0x07
#define SIOP_REG_SFBR		0x08
#define SIOP_REG_SOCL		0x09
#define SIOP_REG_SSID		0x0A
#define SIOP_REG_SBCL		0x0B
#define SIOP_REG_DSTAT		0x0C
#define SIOP_REG_SSTAT0		0x0D
#define SIOP_REG_SSTAT1		0x0E
#define SIOP_REG_SSTAT2		0x0F
#define SIOP_REG_DSA0		0x10
#define SIOP_REG_DSA1		0x11
#define SIOP_REG_DSA2		0x12
#define SIOP_REG_DSA3		0x13
#define SIOP_REG_ISTAT		0x14
#define SIOP_REG_RVSD15		0x15
#define SIOP_REG_RVSD16		0x16
#define SIOP_REG_RVSD17		0x17
#define SIOP_REG_CTEST0		0x18
#define SIOP_REG_CTEST1		0x19
#define SIOP_REG_CTEST2		0x1A
#define SIOP_REG_CTEST3		0x1B
#define SIOP_REG_TEMP0		0x1C
#define SIOP_REG_TEMP1		0x1D
#define SIOP_REG_TEMP2		0x1E
#define SIOP_REG_TEMP3		0x1F
#define SIOP_REG_DFIFO		0x20
#define SIOP_REG_CTEST4		0x21
#define SIOP_REG_CTEST5		0x22
#define SIOP_REG_CTEST6		0x23
#define SIOP_REG_DBC0		0x24
#define SIOP_REG_DBC1		0x25
#define SIOP_REG_DBC2		0x26
#define SIOP_REG_DCMD		0x27
#define SIOP_REG_DNAD0		0x28
#define SIOP_REG_DNAD1		0x29
#define SIOP_REG_DNAD2		0x2A
#define SIOP_REG_DNAD3		0x2B
#define SIOP_REG_DSP0		0x2C
#define SIOP_REG_DSP1		0x2D
#define SIOP_REG_DSP2		0x2E
#define SIOP_REG_DSP3		0x2F
#define SIOP_REG_DSPS0		0x30
#define SIOP_REG_DSPS1		0x31
#define SIOP_REG_DSPS2		0x32
#define SIOP_REG_DSPS3		0x33
#define SIOP_REG_SCRATCHA0	0x34
#define SIOP_REG_SCRATCHA1	0x35
#define SIOP_REG_SCRATCHA2	0x36
#define SIOP_REG_SCRATCHA3	0x37
#define SIOP_REG_DMODE		0x38
#define SIOP_REG_DIEN		0x39
#define SIOP_REG_DWT		0x3A
#define SIOP_REG_DCNTL		0x3B
#define SIOP_REG_ADDER0		0x3C
#define SIOP_REG_ADDER1		0x3D
#define SIOP_REG_ADDER2		0x3E
#define SIOP_REG_ADDER3		0x3F
#define SIOP_REG_SIEN0		0x40
#define SIOP_REG_SIEN1		0x41
#define SIOP_REG_SIST0		0x42
#define SIOP_REG_SIST1		0x43
#define SIOP_REG_SLPAR		0x44
#define SIOP_REG_RVSD45		0x45
#define SIOP_REG_MACNTL		0x46
#define SIOP_REG_GPCNTL		0x47
#define SIOP_REG_STIME0		0x48
#define SIOP_REG_STIME1		0x49
#define SIOP_REG_RESPID0	0x4A
#define SIOP_REG_RESPID1	0x4B
#define SIOP_REG_STEST0		0x4C
#define SIOP_REG_STEST1		0x4D
#define SIOP_REG_STEST2		0x4E
#define SIOP_REG_STEST3		0x4F
#define SIOP_REG_SIDL		0x50
#define SIOP_REG_RVSD51		0x51
#define SIOP_REG_RVSD52		0x52
#define SIOP_REG_RVSD53		0x53
#define SIOP_REG_SODL		0x54
#define SIOP_REG_RVSD55		0x55
#define SIOP_REG_RVSD56		0x56
#define SIOP_REG_RVSD57		0x57
#define SIOP_REG_SBDL		0x58
#define SIOP_REG_RVSD59		0x59
#define SIOP_REG_RVSD5A		0x5A
#define SIOP_REG_RVSD5B		0x5B
#define SIOP_REG_SCRATCHB0	0x5C
#define SIOP_REG_SCRATCHB1	0x5D
#define SIOP_REG_SCRATCHB2	0x5E
#define SIOP_REG_SCRATCHB3	0x5F

/* NCR 53c810 Register bit definitions. */

/* SCSI Control Register Zero : SCNTL0 */
#define SCNTL0_ARB1	0x80
#define SCNTL0_ARB0	0x40
#define SCNTL0_START	0x20
#define SCNTL0_WATN	0x10
#define SCNTL0_EPC	0x08
#define SCNTL0_RES02	0x04
#define SCNTL0_AAP	0x02
#define SCNTL0_TRG	0x01

#define SCNTL0_EPG	0x04		/* '720, Enable Parity Generation */

/* SCSI Control Register One : SCNTL1 */
#define SCNTL1_EXC	0x80
#define SCNTL1_ADB	0x40
#define SCNTL1_DHP	0x20		/* Disable Halt on Parity Err or ATN */
#define SCNTL1_CON	0x10
#define SCNTL1_RST	0x08
#define SCNTL1_AESP	0x04
#define SCNTL1_IARB	0x02		/* Immediate Arbitration */
#define SCNTL1_SST	0x01		/* Start SCSI transfer */

/* SCSI Control Register Two : SCNTL2 */
#define SCNTL2_SDU	0x80		/* SCSI Disconnect Unexpected */
#define SCNTL2_RES06	0x40
#define SCNTL2_RES05	0x20
#define SCNTL2_RES04	0x10
#define SCNTL2_RES03	0x08
#define SCNTL2_RES02	0x04
#define SCNTL2_RES01	0x02
#define SCNTL2_RES00	0x01

/* SCSI Control Register Three : SCNTL3 */
#define SCNTL3_RES07	0x80
#define SCNTL3_SCF2	0x40		/* Sync Clock Conv Factor */
#define SCNTL3_SCF1	0x20
#define SCNTL3_SCF0	0x10
#define SCNTL3_RES03	0x08
#define SCNTL3_CCF2	0x04		/*  Clock Conv Factor */
#define SCNTL3_CCF1	0x02
#define SCNTL3_CCF0	0x01

#define SCNTL3_SCFMSK	0x70		/* Sync Clock Conv Factor Mask */
#define SCNTL3_CCFMSK	0x07		/* Clock Conv Factor Mask */

/* SCSI Chip ID: SCID */
#define SCID_RES07	0x80
#define SCID_RRE	0x40		/* Enable Response to Reselection */
#define SCID_SRE	0x20		/* Enable Response to Selection */
#define SCID_RES04	0x10
#define SCID_RES03	0x08
#define SCID_ENC2	0x04		/* Encoded '810 Chip SCSI ID */
#define SCID_ENC1	0x02
#define SCID_ENC0	0x01

#define SCID_ENCMSK	0x07		/* Encoded '810 Chip SCSI ID Mask */

/* SCSI Transfer : SXFER */
#define SXFER_TP2	0x80		/* SCSI Sync Transfer Period */
#define SXFER_TP1	0x40
#define SXFER_TP0	0x20
#define SXFER_RES04	0x10
#define SXFER_MO3	0x08		/* Max SCSI Sync Offset */
#define SXFER_MO2	0x04
#define SXFER_MO1	0x02
#define SXFER_MO0	0x01

#define SXFER_TPMSK	0xE0		/* SCSI Sync Transfer Period Mask */
#define SXFER_MOMSK	0x0F		/* Max SCSI Sync Offset Mask */

/* SCSI Destination ID: SDID */
#define SDID_RES07	0x80
#define SDID_RES06	0x40
#define SDID_RES05	0x20
#define SDID_RES04	0x10
#define SDID_RES03	0x08
#define SDID_ENC2	0x04		/* Encoded Destination SCSI ID */
#define SDID_ENC1	0x02
#define SDID_ENC0	0x01

#define SDID_ENCMSK	0x07		/* Encoded Destination SCSI ID Mask */

/* General Purpose : GPREG */
#define GPREG_RES07	0x80
#define GPREG_RES06	0x40
#define GPREG_RES05	0x20
#define GPREG_RES04	0x10
#define GPREG_RES03	0x08
#define GPREG_RES02	0x04
#define GPREG_GPIO1	0x02		/* General Purpose (See GPCNTL) */
#define GPREG_GPIO0	0x01

/* SCSI Output Control Latch : SOCL */
#define SOCL_REQ	0x80		/* Assert SCSI REQ signal */
#define SOCL_ACK	0x40		/* Assert SCSI ACK signal */
#define SOCL_BSY	0x20		/* Assert SCSI BSY signal */
#define SOCL_SEL	0x10		/* Assert SCSI SEL signal */
#define SOCL_ATN	0x08		/* Assert SCSI ATN signal */
#define SOCL_MSG	0x04		/* Assert SCSI MSG signal */
#define SOCL_CD		0x02		/* Assert SCSI C/D signal */
#define SOCL_IO		0x01		/* Assert SCSI I/O signal */

/* SCSI Selector ID: SSID */
#define SSID_VAL	0x80		/* SCSI Selector ID valid */
#define SSID_RES06	0x40
#define SSID_RES05	0x20
#define SSID_RES04	0x10
#define SSID_RES03	0x08
#define SSID_ENCID2	0x04		/* Encoded selecting SCSI ID */
#define SSID_ENCID1	0x02
#define SSID_ENCID0	0x01

#define SSID_ENCIDMSK	0x07		/* Encoded Selecting SCSI ID Mask */

/* SCSI Bus Control Lines : SBCL */
#define SBCL_REQ	0x80		/* State of SCSI REQ signal */
#define SBCL_ACK	0x40		/* State of SCSI ACK signal */
#define SBCL_BSY	0x20		/* State of SCSI BSY signal */
#define SBCL_SEL	0x10		/* State of SCSI SEL signal */
#define SBCL_ATN	0x08		/* State of SCSI ATN signal */
#define SBCL_MSG	0x04		/* State of SCSI MSG signal */
#define SBCL_CD		0x02		/* State of SCSI C/D signal */
#define SBCL_IO		0x01		/* State of SCSI I/O signal */

/* DMA Status : DSTAT */
#define DSTAT_DFE	0x80
#define DSTAT_MDPE	0x40		/* Master Data Parity Error */
#define DSTAT_BF	0x20
#define DSTAT_ABRT	0x10
#define DSTAT_SSI	0x08
#define DSTAT_SIR	0x04
#define DSTAT_RES01	0x02
#define DSTAT_IID	0x01

/* SCSI Status Zero : SSTAT0 */
#define SSTAT0_ILF	0x80		/* SCSI Input Data Latch Full */
#define SSTAT0_ORF	0x40		/* SCSI Output Data Register Full */
#define SSTAT0_OLF	0x20		/* SCSI Output Data Latch Full */
#define SSTAT0_AIP	0x10		/* Arbitration In Progress */
#define SSTAT0_LOA	0x08		/* Lost Arbitration */
#define SSTAT0_WOA	0x04		/* Won Arbitration */
#define SSTAT0_RST	0x02		/* SCSI Reset Signal */
#define SSTAT0_SDP	0x01		/* SCSI Parity Signal */

/* SCSI Status One : SSTAT1 */
#define SSTAT1_FF3	0x80		/* SCSI bytes in FIFO flags */
#define SSTAT1_FF2	0x40
#define SSTAT1_FF1	0x20
#define SSTAT1_FF0	0x10
#define SSTAT1_SDPL	0x08		/* Latched SCSI parity */
#define SSTAT1_MSG	0x04		/* SCSI MSG latched on REQ */
#define SSTAT1_CD	0x02		/* SCSI C/D latched on REQ */
#define SSTAT1_IO	0x01		/* SCSI I/O latched on REQ */

#define SSTAT1_FFMSK	0xF0		/* SCSI FIFO flags Mask */

/* SCSI Status Two : SSTAT2 */
#define SSTAT2_RES07	0x80
#define SSTAT2_RES06	0x40
#define SSTAT2_RES05	0x20
#define SSTAT2_RES04	0x10
#define SSTAT2_RES03	0x08
#define SSTAT2_RES02	0x04
#define SSTAT2_LDSC	0x02		/* Last Disconnect */
#define SSTAT2_RES00	0x01

/* Interrupt Status : ISTAT */
#define ISTAT_ABRT	0x80		/* Abort Operation */
#define ISTAT_SRST	0x40		/* Software Reset */
#define ISTAT_SIGP	0x20		/* Signal Process */
#define ISTAT_SEM	0x10		/* Semaphore */
#define ISTAT_CON	0x08		/* Connected */
#define ISTAT_INTF	0x04		/* Interrupt on the Fly */
#define ISTAT_SIP	0x02		/* SCSI Interrupt Pending */
#define ISTAT_DIP	0x01		/* DMA Interrupt Pending */

/* Chip Test Zero : CTEST0 */

/* Chip Test One : CTEST1 */

/* Chip Test Two : CTEST2 */
#define CTEST2_DDIR	0x80		/* Data Transfer Direction */
#define CTEST2_SIGP	0x40		/* Signal Process */
#define CTEST2_CIO	0x20		/* Configured as I/O Space */
#define CTEST2_CM	0x10		/* Configured as Memory Space */
#define CTEST2_RES03	0x08
#define CTEST2_TEOP	0x04		/* SCSI True End of Process */
#define CTEST2_DREQ	0x02		/* Data Request Status */
#define CTEST2_DACK	0x01		/* Data Acknowledge Signal */

/* Chip Test Three : CTEST3 */
#define CTEST3_V3	0x80		/* Chip Revision Level */
#define CTEST3_V2	0x40
#define CTEST3_V1	0x20
#define CTEST3_V0	0x10
#define CTEST3_FLF	0x08		/* Flush DMA FIFO */
#define CTEST3_CLF	0x04		/* Clear DMA and SCSI FIFOs */
#define CTEST3_FM	0x02		/* Fetch Pin Mode */
#define CTEST3_RES00	0x01

#define CTEST3_VMSK	0xF0		/* Chip Revision Level Mask */

/* DMA FIFO : DFIFO */
#define	DFIFO_RES07	0x80
#define	DFIFO_BO6	0x40		/* DMA FIFO Byte Offset Counter */
#define	DFIFO_BO5	0x20
#define	DFIFO_BO4	0x10
#define	DFIFO_BO3	0x08
#define	DFIFO_BO2	0x04
#define	DFIFO_BO1	0x02
#define	DFIFO_BO0	0x01

#define	DFIFO_BOMSK	0x7F		/* Byte Offset Counter Mask */

/* Chip Test Four : CTEST4 */

/* Chip Test Five : CTEST5 */

/* Chip Test Six : CTEST6 */

/* DMA Mode : DMODE */
#define DMODE_BL1	0x80		/* Burst Length */
#define DMODE_BL0	0x40
#define DMODE_SIOM	0x20		/* Source I/O-Memory Enable */
#define DMODE_DIOM	0x10		/* Destination I/O-Memory Enable */
#define DMODE_ER	0x08		/* Enable Read Line */
#define DMODE_RES02	0x04
#define DMODE_RES01	0x02
#define DMODE_MAN	0x01		/* Manual Start Mode */

#define DMODE_BLMSK	0xC0		/* Burst Length Mask */

/* DMA Interrupt Enable : DIEN */
#define DIEN_RES07	0x80
#define DIEN_MDPE	0x40		/* Master Data Parity Error */
#define DIEN_BF		0x20		/* Bus Fault */
#define DIEN_ABRT	0x10		/* Aborted */
#define DIEN_SSI	0x08		/* Single Step Interrupt */
#define DIEN_SIR	0x04		/* Scripts Interrupt Instr Received */
#define DIEN_RES01	0x02
#define DIEN_IID	0x01		/* Illegal Instr Detected */

/* DMA Control : DCNTL */
#define DCNTL_RES07	0x80
#define DCNTL_RES06	0x40
#define DCNTL_RES05	0x20
#define DCNTL_SSM	0x10		/* Single Step Mode */
#define DCNTL_IRQM	0x08		/* IRQ Mode */
#define DCNTL_STD	0x04		/* Start DMA Operation */
#define DCNTL_SA	0x02		/* Same Agent */
#define DCNTL_COM	0x01		/* 53c700 Compatability */

/* SCSI Interrupt Enable Zero : SIEN0 */
#define SIEN0_MA	0x80		/* SCSI Phase Mismatch */
#define SIEN0_CMP	0x40		/* Function complete */
#define SIEN0_SEL	0x20		/* Selected */
#define SIEN0_REL	0x10		/* Reselected */
#define SIEN0_SGE	0x08		/* SCSI Gross Error */
#define SIEN0_UDC	0x04		/* Unexpected Disconnect */
#define SIEN0_RST	0x02		/* SCSI Reset Condition */
#define SIEN0_PAR	0x01		/* SCSI Parity Error */

/* SCSI Interrupt Enable One : SIEN1 */
#define SIEN1_RES07	0x80
#define SIEN1_RES06	0x40
#define SIEN1_RES05	0x20
#define SIEN1_RES04	0x10
#define SIEN1_RES03	0x08
#define SIEN1_STO	0x04		/* Selection or Reselection Timeout */
#define SIEN1_GEN	0x02		/* General Purpose Timer Expired */
#define SIEN1_HTH	0x01		/* Handshake to Handshake Timer Expr */

/* SCSI Interrupt Status Zero : SIST0 */
#define SIST0_MA	0x80		/* SCSI Phase Mismatch */
#define SIST0_CMP	0x40		/* Function complete */
#define SIST0_SEL	0x20		/* Selected */
#define SIST0_REL	0x10		/* Reselected */
#define SIST0_SGE	0x08		/* SCSI Gross Error */
#define SIST0_UDC	0x04		/* Unexpected Disconnect */
#define SIST0_RST	0x02		/* SCSI Reset Condition */
#define SIST0_PAR	0x01		/* SCSI Parity Error */

/* SCSI Interrupt Status One : SIST1 */
#define SIST1_RES07	0x80
#define SIST1_RES06	0x40
#define SIST1_RES05	0x20
#define SIST1_RES04	0x10
#define SIST1_RES03	0x08
#define SIST1_STO	0x04		/* Selection or Reselection Timeout */
#define SIST1_GEN	0x02		/* General Purpose Timer Expired */
#define SIST1_HTH	0x01		/* Handshake to Handshake Timer Expr */

/* Memory Access Control : MACNTL */
#define MACNTL_RES07	0x80
#define MACNTL_RES06	0x40
#define MACNTL_RES05	0x20
#define MACNTL_RES04	0x10
#define MACNTL_DWR	0x08		/* Data Write : local memory */
#define MACNTL_DRD	0x04		/* Data Read : local memory */
#define MACNTL_PSCPT	0x02		/* Pointer Scripts : local memory */
#define MACNTL_SCPTS	0x01		/* Scripts : local memory */

/* SCSI Timer Register Zero : STIME0 */
#define STIME0_HTH3	0x80		/* Handshake to Handshake Timer cnts */
#define STIME0_HTH2	0x40
#define STIME0_HTH1	0x20
#define STIME0_HTH0	0x10
#define STIME0_SEL3	0x08		/* Selection Timeout Timer counts */
#define STIME0_SEL2	0x04
#define STIME0_SEL1	0x02
#define STIME0_SEL0	0x01

#define STIME0_HTHMSK	0xF0		/* Handshake to Handshake Timer Mask */
#define STIME0_SELMSK	0x0F		/* Selection Timeout Timer Mask */

/* SCSI Timer Register One : STIME1 */
#define STIME1_RES07	0x80
#define STIME1_RES06	0x40
#define STIME1_RES05	0x20
#define STIME1_RES04	0x10
#define STIME1_GEN3	0x08		/* General Purpose Timer counts */
#define STIME1_GEN2	0x04
#define STIME1_GEN1	0x02
#define STIME1_GEN0	0x01

#define STIME1_GENMSK	0x0F		/* General Purpose Timer Mask */

/* SCSI Test Register 1 */
#define STEST1_SCLK	0x80		/* Disable external SCLK */
#define STEST1_SISO	0x40		/* SCSI Isolation Mode */
#define STEST1_DBLEN	0x08		/* SCLK Doubler Enable */
#define STEST1_DBLSEL	0x04		/* SCLK Doubler Select */

/* SCSI Test Register 3 */
#define STEST3_EAN	0x80		/* Enable Active Negation */
#define STEST3_STR	0x40
#define STEST3_HSC	0x20
#define STEST3_DSI	0x10
#define STEST3_RSVD	0x08
#define STEST3_TTM	0x04
#define STEST3_CSF	0x02
#define STEST3_STW	0x01

/* Synchronous transfer parameter limits as part of the SDTR transfer factor. */

#define SIOP_MAX_OFFSET		8	/* max offset allowed */

#define SCPD			4	/* SCSI2 Sync MSG Period Divisor */

/* min/max number of clk periods chip can hold during synchronous */
#define SIOP_MIN_XFERP		4
#define SIOP_MAX_XFERP		11

/* little chip conversion - XFERP of 4 is really 0 on the chip */
/* should we really just make this SIOP_MIN_XFERP ? */
#define SIOP_SYNC_ADJUST	4	/* 810 minimally holds clk 4 periods */

/* SCLK divisor bits - actual bits for SCF and CCF. Also used as index
 * into divisor table for sync rate calculations.
 */
#define SIOP_SCLK_DIV_3_FAST	0x0
#define SIOP_SCLK_DIV_1		0x1	/* SCNTL3_CCF0               */
#define SIOP_SCLK_DIV_1_5	0x2	/* SCNTL3_CCF1               */
#define SIOP_SCLK_DIV_2		0x3	/* SCNTL3_CCF0 | SCNTL3_CCF1 */
#define SIOP_SCLK_DIV_3		0x4	/* SCNTL3_CCF2               */
#define SIOP_SCLK_DIV_4		0x5	/* SCNTL3_CCF2 | SCNTL3_CCF0 */

/* Macros for converting transfer period to values that can be loaded
 * into the SXFER register.  First the TP, (V) is calculatded and then
 * the transfer period factor, (P) is "re-calced" to match what (V)
 * was adjusted to.
 *
 * NOTE: maybe we should allow script to try and do this ??
 */
#define SIOP_CALC_PERIOD(shp,period,xferp) { \
    (xferp) = (((((period)*SCPD*100)/((shp)->sh_clk_period))-SIOP_SYNC_ADJUST) + \
               ((((period)*SCPD*100)%((shp)->sh_clk_period))?1:0)); \
    (period) = (((xferp)+SIOP_SYNC_ADJUST) * ((shp)->sh_clk_period))/(SCPD*100); \
    }

/* defines for job terminate state machine */
#define SIOP_KILL_RESET		0
#define SIOP_KILL_DRESET	1
#define SIOP_KILL_ABORT		2
#define SIOP_KILL_AT		3

/* Some general defines */
#define SIOP_SH_ALIGN		256

/* Macros for the Response ID registers.  They are bit field for the ID's
that the SIOP will respond to in a selecton or reselection phase.  If
the ID 15 - 8, RESPID1 has to have one of it's bits set.  If the ID is
7 - 0, RESPID0 has to have one of it's bits set. */

#define RESPID_HI( id )		(((id) >= 8)?(1 << ((id) - 8)):(0))
#define RESPID_LO( id )		(((id) <= 7)?(1 << (id)):(0))
