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
 * @(#)$RCSfile: if_lereg.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1994/04/11 14:12:52 $
 */

/* Digital Low End Media Access Controller (LeMAC)
 */

#ifndef __IF_LEREG__
#define __IF_LEREG__ 1

/* IO register map
 */
#define EISA_OFFSET	0xc00		/* if in EISA mode, all registers begin here */

#define LE_CSR		0x0		/* control and status register */
#define LE_CR		0x1		/* control register */
#define LE_ICR		0x2		/* interrupt control register */
#define LE_TSR		0x3		/* transmit status register */
#define LE_FMQ		0x6		/* free memory queue */
#define LE_FMQC		0x7		/* free memory queue count */
#define LE_RXQ		0x8		/* receive queue */
#define LE_RXQC		0x9		/* receive queue count */
#define LE_TXQ		0xa		/* transmit queue */
#define LE_TXQC		0xb		/* transmit queue count */
#define LE_TXDQ		0xc		/* transmit done queue */
#define LE_TXDQC	0xd		/* transmit done queue count */
#define LE_PIR1		0xe		/* page index register 1 */
#define LE_PIR2		0xf		/* page index register 2 */
#define LE_DATA		0x10		/* data register */
#define LE_IOPAGE	0x11		/* IO page register */
#define LE_IOBASE	0x12		/* IO base register */
#define LE_MEMPAGE	0x13		/* memory page register */
#define LE_MEMBASE	0x14		/* memory base register */
#define LE_MACADDR	0x15		/* station address prom */
#define LE_EEDATA1	0x16		/* EEPROM data register 1 */
#define LE_EEDATA2	0x17		/* EEPROM data register 2 */
#define LE_PADDR0	0x18		/* station address, byte 0 */
#define LE_PADDR1	0x19		/* station address, byte 1 */
#define LE_PADDR2	0x1a		/* station address, byte 2 */
#define LE_PADDR3	0x1b		/* station address, byte 3 */
#define LE_PADDR4	0x1c		/* station address, byte 4 */
#define LE_PADDR5	0x1d		/* station address, byte 5 */
#define LE_CNFG		0x1e		/* configuration management register */
#define EISA_ID		0xc80		/* EISA ID register */
#define EISA_CTL	0xc84		/* EISA control register */


/* definitions for LE_CSR
 */
#define CSR_RA		0x80		/* acccept runt packets if set */
#define CSR_PME		0x40		/* promiscuous mode enabled if set */
#define CSR_MCE		0x20		/* accept multicast pkts if set */
#define CSR_TNE		0x8		/* TX done queue NOT empty */
#define CSR_RNE		0x4		/* RX queue NOT empty */
#define CSR_TXD		0x2		/* transmitter disabled if set */
#define CSR_RXD		0x1		/* receiver disabled if set */

/* definitions for LE_CR
 */
#define CR_APD		0x80		/* auto port select disable */
#define CR_PORTSEL	0x40		/* port select, if APD == 0 then
					 * setting this selects thin/AUI
					 * regardless of the link bit,
					 * clearing it selects TP
					 */
#define CR_LOOP		0x20		/* enter loopback mode if set */
#define CR_DUPLEX	0x10		/* enter full-duplex mode if set */
#define CR_FASTBUS	0x8		/* set if bus speed is >8.33 MHz */
#define CR_D16		0x4		/* set this to enable D16 xfers */
#define CR_LED		0x2		/* turn on the LED */

/* definitions for LE_ICR
 */
#define ICR_IE		0x80		/* set this to enable interrupts */
#define ICR_IRQ15	0x60
#define ICR_IRQ11	0x40
#define ICR_IRQ10	0x20
#define ICR_IRQ5	0x0
#define ICR_TNEMASK	0x8		/* set to enable TNE interrupt */
#define ICR_RNEMASK	0x4		/* set to enable RNE interrupt */
#define ICR_TXDMASK	0x2		/* set to enable TXD interrupt */
#define ICR_RXDMASK	0x1		/* set to enable RXD interrupt */

/* definitions for LE_TSR
 * These bits pertain to the last packet sent
 */
#define TSR_NCL		0x80		/* set if carrier was lost */
#define TSR_ID		0x40		/* set if pkt was deferred */
#define TSR_LCL		0x20		/* set if pkt encountered late collision */
#define TSR_ECL		0x10		/* set if pkt encountered excessive collisions */
#define TSR_RETRY	0xf		/* contains the retry count */

/* definitions for LE_IOPAGE
 */
					/* 0PPPPPPP for DRAM page PPPPPPP */
#define IOPAGE_ROM	0x80		/* 10xxPPPP for ROM page PPPP */
#define IOPAGE_INIT	0xc0		/* 11000xxx for EEPROM init */
#define IOPAGE_WRENA	0xc8		/* 11001xxx for EEPROM write enable */
#define IOPAGE_WRITE	0xd0		/* 11010xxx for EEPROM write */
#define IOPAGE_WRDIS	0xd8		/* 11011xxx for EEPROM write disable */
#define IOPAGE_READ	0xe0		/* 11100xxx for EEPROM read */

/* definitions for LE_IOBASE
 */
#define IOBASE_EISA	0x20		/* EISA mode if set, turn on the ID and control
					 * registers, respond to slot-specific IO addresses
					 * beginning at offset 0xc00
					 */
#define IOBASE_MASK	0x1f		/* these are compared against SA bits 9-5, so
					 * if this has a value of 0x18 then IO space
					 * begins at port address 0x300, etc.  Set to
					 * zero if EISA is set
					 */

/* definitions for LE_MEMPAGE
 */
#define MEMPAGE_DRAM	0x0		/* DRAM accesses as 0PPPPPPP */
#define MEMPAGE_ROM	0x80		/* ROM accesses as 1xxxPPPP */

/* definitions for LE_MEMBASE
 */
#define MEMBASE_IO	0		/* no shared memory window */
#define MEMBASE_64K	0		/* actually, 0xa-0xf for 0xa0000-0xf0000 */
#define MEMBASE_32K	0x10		/* 0x14-0x1f */
#define MEMBASE_2K	0x40		/* 0x40-0xff */

/* definitions for LE_CNFG
 */
#define CNFG_LINK	0x20		/* LINK: when clear, TP port is up */
#define CNFG_PLRTY	0x10		/* status of the POLARITY pin on LeMAC */
#define CNFG_EEPROM	0xc		/* config info loaded from EEPROM */
#define CNFG_EISA	0x8		/* hardware init for EISA machines, 0xc00 offset */
#define CNFG_0x280	0x4		/* hardware init for ISA machines, IO addr 0x280 */
#define CNFG_0x200	0x0		/* hardware init for ISA machines, IO addr 0x200 */

#define ID_DEC2030      0x3020a310
#define ID_DEC2040      0x4020a310
#define ID_DEC2050      0x5020a310
#define DE300_MASK      0xf0ffffff
#define DE300_HW_REV    0x0f000000

/* definition for EISA_CTL
 */
#define CTL_ENABLE	0x1		/* enable shared memory */



/* definitions for receive buffer, the first four bytes of which is the
 * packet length and receiver status for that packet
 */
typedef union le_rxstat {
	unsigned int _le_statlen;	/* length is little-endian in bytes 1..2 */
	unsigned char _le_rx_stat[4];
} le_rxstat;

#define le_rx_stat _le_rx_stat[0]
#define LE_RXLEN(x)	(((x)->_le_statlen >> 8) & 0x7ff)	/* pkt length */
#define LE_RXOK		0x80		/* pkt arrived without errors */
#define LE_RXIAM	0x10		/* individual address match */
#define LE_RXMCM	0x8		/* multicast match */
#define LE_RXDBE	0x4		/* dribble bit error, pkt length % 8 != 0 */
#define LE_RXCRC	0x2		/* CRC error */
#define LE_RXPLL	0x1		/* phase-locked loop lost lock */

/* definitions for a transmit buffer
 */
typedef union le_txstat {
	unsigned int _le_statlen;
	struct {
		unsigned char _le_tx_stat;
		unsigned char _le_tlen_0;
		unsigned char _le_tlen_1;
		unsigned char _le_tx_index;	/* offset for pkt data in tx buf */
	} _le_tx_buf;
} le_txstat;

#define le_tx_stat	_le_tx_buf._le_tx_stat
#define le_tx_index	_le_tx_buf._le_tx_index

/* transmitter control bits
 */
#define LE_TXSQEON	0x40		/* turn on heartbeat for this pkt */
#define LE_TXSTOPERR	0x20		/* turn transmitter off upon any TX error */
#define LE_TXQMODE	0x10		/* turn on to automatically recycle TX buffer */
#define LE_TXLAB	0x8		/* less aggressive backoff */
#define LE_TXPAD	0x4		/* automatically pad runt pkts */
#define LE_TXIFC	0x2		/* calculate frame check sequence and append CRC */
#define LE_TXISA	0x1		/* insert source address before pkt data */

/* transmitted status bits
 */
#define LE_TXDONE	0x80		/* this bit is set when the pkt has been sent */
#define LE_TXSQE	0x20		/* heartbeat failure when this pkt was sent */
#define LE_TXNCL	0x10		/* carrier lost */
#define LE_TXLCL	0x8		/* late collision */
#define LE_TXID		0x4		/* initially deferred */
#define LE_TXEXCOLL	0x3		/* excessive collisions */
#define LE_TXMUCOLL	0x2		/* multiple collisions */
#define LE_TXONECOLL	0x1		/* one collision */



#endif /* __IF_LEREG__ */
