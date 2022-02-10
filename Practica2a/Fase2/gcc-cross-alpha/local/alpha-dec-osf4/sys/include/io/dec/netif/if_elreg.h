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
 * @(#)$RCSfile: if_elreg.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1996/09/05 19:14:59 $
 */

/*
 * Interrupt/Status bits.  These are read from the status register and
 * set/cleared in the CMD_ACKINT, CMD_SINTMASK, CMD_ZINTMASK commands.
 */
#define STS_PORT	0xe	/* IOPORT of status register */

#define S_IL		(1)		/* Interrupt Latch */
#define S_AF		(1<<1)		/* Adapter Failure */
#define S_TC		(1<<2)		/* Transmit Complete */
#define S_TA		(1<<3)		/* Transmit Available */
#define S_RC		(1<<4)		/* Receive Complete */
#define S_RE		(1<<5)		/* Receive Early */
#define S_IR		(1<<6)		/* Interrupt Request */
#define S_US		(1<<7)		/* Update Statistics */
#define S_IP		(1<<12)		/* Command In Progress */
#define CURWINDOW(x)	((x>>13)&0x7)	/* Current window num (sts only) */ 

/*
 * Commands (written to the command port)
 * 
 * 	bits [0:10] contain optional parameter
 * 	bits [11:15] contain the command
 */
#define CMD_PORT	0xe	/* IOPORT of command register */

#define CMD_RESET		(0x0)		/* Reset */
#define CMD_WINDOW0		((0x1<<11)+0x0)	/* Setup */
#define CMD_WINDOW1		((0x1<<11)+0x1)	/* Operating */
#define CMD_WINDOW2		((0x1<<11)+0x2)	/* Station Addr */
#define CMD_WINDOW3		((0x1<<11)+0x3)	/* FIFO manglement */
#define CMD_WINDOW4		((0x1<<11)+0x4)	/* Diagnostic */
#define CMD_WINDOW5		((0x1<<11)+0x5)	/* Diagnostic */
#define CMD_WINDOW6		((0x1<<11)+0x6)	/* Statistics */
#define CMD_START2		(0x2<<11)	/* Start 10Base2 */
#define CMD_RXDIS		(0x3<<11)	/* RX Disable */
#define CMD_RXENA		(0x4<<11)	/* RX Enable */
#define CMD_RXRESET		(0x5<<11)	/* RX Reset */
#define CMD_RXDTP		(0x8<<11)	/* RX Discard Top Packet */
#define CMD_TXENA		(0x9<<11)	/* TX Enable */
#define CMD_TXDIS		(0xa<<11)	/* TX Disable */
#define CMD_TXRESET		(0xb<<11)	/* TX Reset */
#define CMD_REQINT		(0xc<<11)	/* Request Interrupt */
#define CMD_ACKINT		(0xd<<11)	/* Acknowledge Interrupt */
#define CMD_SINTMASK		(0xe<<11)	/* Set Interrupt Mask */
#define CMD_ZINTMASK		(0xf<<11)	/* Read Zero Interrupt Mask */
#define CMD_FILTER		(0x10<<11)	/* Set RX Filter */
enum rx_filter {
      RF_IND	=0x1,	/* Individual Address */
      RF_GRP	=0x2,	/* Group Address */
      RF_BRD	=0x4,	/* Broadcast Address */
      RF_PRM	=0x8	/* Promiscuous */
};
#define CMD_RXEARLY		(0x11<<11)	/* Set RX Early Threshold */
#define CMD_TXAVAILTHRESH	(0x12<<11)      /* Set TX Available Thresh */
#define CMD_TXSTARTTHRESH	(0x13<<11)	/* Set TX Start Thresh */
#define CMD_STATSENA		(0x15<<11)	/* Statistics Enable */
#define CMD_STATSDIS		(0x16<<11)	/* Statistics Disable */
#define CMD_STOP2		(0x17<<11)	/* Stop 10Base2 */
#define CMD_RXRECTHRESH		(0x18<<11)	/* Set TX Reclaim Thresh */
#define CMD_POWERUP		(0x1b<<11)	/* Power up */
#define CMD_POWERDOWN		(0x1c<<11)	/* Power Down Full */
#define CMD_POWERAUTO		(0x1d<<11)	/* Power Auto */

/*
 * Window 0 Configuration Registers
 */

#define W0_MID			0x0		/* Manufacturer ID */
#define W0_AID			0x2		/* Adapter ID */
#define W0_CCR			0x4		/* Configuration Control Reg */
enum w0_ccr {
      CCR_POR=0x7f00,	/* Power on Reset bits */
      CCR_PCMCIA=0x4000,/* Set if PCMCIA -- otherwise ISA */
      CCR_AUI=0x2000,	/* Set if AUI is available */
      CCR_10B2=0x1000,	/* Set if 10Base2 xcvr is available */
      CCR_ENDEC=0x0100, /* Set if internal ENDEC (VCO) is used */
      CCR_RESET=0x4,	/* Reset to power-on reset */
      CCR_ENA=0x1	/* Enable adapter */
};
#define W0_ACR			0x6		/* Address Control Reg */
enum w0_acr {
      ACR_10BT=0x0000,	/* Select 10BaseT -- twisted pair */
      ACR_10B5=0x4000,	/* Select 10Base5 -- aui */
      ACR_10B2=0xc000,	/* Select 10Base2 -- thinwire */
      ACR_ROMS=0x3000,	/* Rom Size -- ISA only */
      ACR_ROMB=0x0f00,	/* Rom Base -- ISA only */
      ACR_ASE= 0x0080,	/* Auto Select -- should always be done anyway */
      ACR_BASE=0x001f	/* I/O Base Address */
};
#define W0_RCR			0x8		/* Resource Config Reg */
enum w0_rcr {
      RCR_IRQ=0xf000,	/* IRQ value */
      RCR_RSV=0x0f00 	/* Reserved field -- must be 0x0f00 */
};
#define W0_ECR			0xa		/* EEPROM Command Reg */
enum w0_ecr {
      ECR_EBY=0x8000, 	/* EEPROM is busy */
      ECR_TST=0x4000,	/* EEPROM Test Mode */
      ECR_CMD=0x00ff,	/* EEPROM command bits */
      ECR_READ= 0x0080,	/*  Read address */
      ECR_WRITE=0x0040,	/*  Write address */
      ECR_ERASE=0x00c0, /*  Erase address */
      ECR_EWENA=0x0030, /*  Enable erase/write */
      ECR_EWDIS=0x0000,	/*  Disable erase/write */
      ECR_EAR=  0x0020,	/*  Erase ALL registers */
      ECR_WAR=  0x0010	/*  Write ALL registers */
};
#define W0_EDR			0xc		/* EEPROM Data Reg */


/*
 * Window 3 Configuration Registers
 */
#define W3_ASI2			0x2		/* Additional Setup Info */
#define W3_ASI0			0x0		/* Additional Setup Info */
enum w3_asi {
      ASI_IAS_ISA=0x00040000,	/* ISA contention activation */
      ASI_IAS_PNP=0x00080000,	/* ISA PNP activation */
      ASI_IAS_BOT=0x000c0000,	/* Both ISA and PNP activation */
      ASI_IAS_NON=0x00000000,	/* Both ISA and PNP activation */
      ASI_PAR_35 =0x00000000,	/* RAM partition 3 TX to 5 RX (3:5) */
      ASI_PAR_13 =0x00010000,   /* RAM partition 1 TX to 3 RX (1:3) */
      ASI_PAR_11 =0x00020000,	/* RAM partition 1 TX to 1 RX (1:1) */
      ASI_RS     =0x00000030, 	/* RAM Speed (set these bits to zero) */
      ASI_RW     =0x00000008,   /* RAM Width (will alwasy be 0 -- 8 bits) */
      ASI_RSIZE8 =0x00000001,	/* RAM Size 8K (default) */
      ASI_RSIZE32=0x00000002 	/* RAM Size 32K */
};

/*
 * Window 1 Operational Registers
 */
#define W1_RXSTAT		0x8		/* Receive status */
enum w1_rxstat {
      RX_IC=0x8000,	/* Incomplete */
      RX_ER=0x4000,	/* Error inidication */
      RX_EM=0x3800,	/* Error mask */
      RX_EOR=0x0000,	/* Overrun Error */
      RX_ERT=0x1800,	/* Runt Error */
      RX_EAL=0x2000,	/* Alignment Error */
      RX_ECR=0x2800,	/* CRC Error */
      RX_EOS=0x0800,	/* Oversized Error */
      RX_BYTES=0x7ff	/* Number of bytes received */
};
#define W1_TXSTAT		0xb		/* Transmit status */
enum w1_txstat {
      TX_CM=0x80,	/* Complete */
      TX_IS=0x40,	/* Interrupt on sucessful completion requested */
      TX_JB=0x20,	/* Jabber Error */
      TX_UN=0x10,	/* Underrun -- serious error -- reset required */
      TX_MC=0x08,	/* Max collisions */
      TX_OF=0x04,	/* Status Overflow */
      TX_RE=0x02	/* Not used */
};
#define TX_INT		0x8000	    /* Request interrupt after completion */
#define W1_RXDATA		0x0		/* Receive data */
#define W1_TXDATA		0x0		/* Transmit data */
#define W1_FREETX		0xc		/* Free Transmit bytes */

/*
 * Window 4 Diagnostic Registers 
 */
#define W4_MEDIA 		0xa		/* Media Type and Status */
enum w4_media {
      MD_TPE	=0x8000,	/* 10BaseT Enabled */
      MD_COAXE	=0x4000,	/* 10Base2 Enabled */
      MD_RES1	=0x2000,       	/* reserved */
      MD_SQE	=0x1000,	/* SQE present */
      MD_VLB	=0x0800,	/* Valid Link Beat detected (TP) */
      MD_PRD	=0x0400,	/* Polarity Reversal Detected (TP) */
      MD_JAB	=0x0200,	/* Jabber detected (TP) */
      MD_UNSQ	=0x0100,       	/* Unsequelch (TP) */
      MD_LBE	=0x0080,	/* Link Beat Enabled */
      MD_JABE	=0x0040,	/* Jabber Enabled */
      MD_CS	=0x0020,	/* Carrier Sense */
      MD_COLL	=0x0010,	/* Collision */
      MD_SQEE	=0x0008,	/* SQE Stats Enable */
      MD_NCRC	=0x0004		/* CRC Strip Disable */
};
#define W4_NET			0x6		/* Net Diagnostic Port */
enum w4_net {
      ND_EXT	=0x8000,	/* External Loopback */
      ND_ENDEC	=0x4000,	/* ENDEC Loopback */
      ND_ECL	=0x2000,	/* Ethernet Controller Loopback */
      ND_LOOP	=0x1000,	/* FIFO Loopback (what we'll use) */
      ND_TXE	=0x0800,	/* TX Enabled */
      ND_RXE	=0x0400,	/* RX Enabled */
      ND_TXB	=0x0200,	/* TX Busy */
      ND_TXRR	=0x0100,	/* TX Reset Required */
      ND_STATE	=0x0080,	/* Statistics Enabled */
      ND_REV	=0x003e,	/* ASIC Rev */
      ND_LOW	=0x0001		/* Don't use */
};

/*
 * EEPROM structure
 */
struct w3_eeprom {
    unsigned short addr[3];			/* LAN Address */
    unsigned short pid;				/* Product ID */
    unsigned short mandata[3];			/* Manufacturing data */
    unsigned short mid;				/* Manufacturer ID */
    unsigned short addrconf;			/* Address configuration */
    unsigned short resconf;			/* Resource configuration */
    unsigned short oem[3];			/* OEM address fields */
    unsigned short swinfo;			/* Software info */
    unsigned short compat;			/* Compatibility word */
    unsigned short cs1;				/* 1st part checksum */
    unsigned short cw2;				/* Compatibility word 2 */
    unsigned short res1;			/* Reserved field */
    unsigned int   icw;				/* Internal config word */
    unsigned short swinfo2;			/* Secondary SW info */
    unsigned short res[2];			/* Reserved fields */
    unsigned short cs2;				/* 2nd part checksum */
    unsigned short pnp[40];			/* Plug And Play data */
};
