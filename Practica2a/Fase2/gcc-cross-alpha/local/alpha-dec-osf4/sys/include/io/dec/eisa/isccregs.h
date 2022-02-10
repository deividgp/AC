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
 * @(#)$RCSfile: isccregs.h,v $ $Revision: 1.1.4.4 $ (DEC) $Date: 1995/12/06 20:16:43 $
 */

#ifndef	_EISA_ISCCREGS_H_
#define _EISA_ISCCREGS_H_


/*
 * z8530 miscellaneous channel constants
 */

#define	ISCC_CHAN_A		0	/* channel a's channel number			*/
#define	ISCC_CHAN_B		1	/* channel b's channel number			*/

#define	NISCC_CHAN    		2	/* number of channels for each z8530 device	*/


/*
 * z8530 per-device register offsets
 */

#define	ISCC_IOBASE_A		8	/* channel a's i/o base offset			*/
#define	ISCC_IOBASE_B		0	/* channel b's i/o base offset			*/


/*
 * z8530 per-channel register offsets
 */

#define	ISCC_CR		        0x00	/* command register (wo)			*/
#define	ISCC_DR		        0x00	/* data register (rw)				*/
#define	ISCC_RXDB	        0x04	/* receiver data buffer register (ro)		*/
#define	ISCC_STS	        0x00	/* status register (ro)				*/
#define	ISCC_TXDB	        0x04	/* transmitter data buffer register (wo)	*/


/*
 * z8530 read register selection codes
 */

#define	ISCC_RR0	      0x0000	/* tx/rx buffer status & external status	*/
#define	ISCC_RR1	      0x0001	/* special receive condition status		*/
#define	ISCC_RR2	      0x0002	/* interrupt vector				*/
#define	ISCC_RR3	      0x0003	/* interrupt pending (channel a only)		*/
#define	ISCC_RR8	      0x0008	/* rx data					*/
#define	ISCC_RR10	      0x000a	/* misc status (loop & clock)			*/
#define	ISCC_RR12	      0x000c	/* baud rate generator time constant (lo byte)  */
#define	ISCC_RR13	      0x000d	/* baud rate generator time constant (hi byte)	*/
#define	ISCC_RR15	      0x000f	/* external status interrupt enable		*/


/*
 * z8530 write register selection codes
 */

#define ISCC_WR0	      0x0000	/* command register 				*/
#define	ISCC_WR1	      0x0001	/* tx/rx interrupt data & transfer mode		*/
#define	ISCC_WR2	      0x0002	/* interrupt vector (shared by both channels)	*/
#define	ISCC_WR3	      0x0003	/* rx parameters & control			*/
#define	ISCC_WR4	      0x0004	/* tx/rx miscellaneous parameters & modes	*/
#define	ISCC_WR5	      0x0005	/* tx parameters & control			*/
#define	ISCC_WR6	      0x0006	/* sync characters or sdlc address field	*/
#define	ISCC_WR7	      0x0007	/* sync characters or sdlc flag			*/
#define	ISCC_WR8	      0x0008	/* tx buffer					*/
#define	ISCC_WR9	      0x0009	/* master interrupt control & reset (shared by  */
					/* both channels)				*/
#define	ISCC_WR10	      0x000a	/* miscellaneous tx/rx control			*/
#define	ISCC_WR11	      0x000b	/* clock mode control				*/
#define	ISCC_WR12	      0x000c	/* baud rate generator time constant (lo byte)  */
#define	ISCC_WR13	      0x000d	/* baud rate generator time constant (hi byte)	*/
#define	ISCC_WR14	      0x000e	/* miscellaneous control			*/
#define	ISCC_WR15	      0x000f	/* external/status interrupt control		*/


/*
 * z8530 tx/rx buffer status & external status register (ISCC_RR0)
 */

#define	ISCC_RR0_RXRDY		0x01	/* rx character available			*/
#define	ISCC_RR0_ZCOUNT		0x02	/* zero count (baud rate generator)		*/
#define	ISCC_RR0_TXEM		0x04	/* tx buffer empty				*/
#define	ISCC_RR0_DCD		0x08	/* data carrier detect				*/

#define	ISCC_RR0_HUNT		0x10	/* hunt						*/
#define	ISCC_RR0_SYNC		0x10	/* sync						*/

#define	ISCC_RR0_CTS		0x20	/* clear to send				*/
#define	ISCC_RR0_TXUR		0x40	/* tx underrun/eom				*/

#define	ISCC_RR0_BREAK		0x80	/* break detected				*/
#define	ISCC_RR0_ABORT		0x80	/* abort detected				*/


/*
 * z8530 special receive condition status register (ISCC_RR1)
 */

#define	ISCC_RR1_AS		0x01	/* all sent					*/
#define	ISCC_RR1_RCODES		0x0e	/* residue codes (sdlc)				*/
#define	ISCC_RR1_PE		0x10	/* parity error					*/
#define	ISCC_RR1_OE		0x20	/* rx overrun error				*/

#define	ISCC_RR1_CRC		0x40	/* crc error (sdlc)				*/
#define	ISCC_RR1_FE		0x40	/* framing error				*/

#define	ISCC_RR1_EOF		0x80	/* end of frame (sdlc)				*/


/*
 * z8530 interrupt pending register (ISCC_RR3)
 */

#define	ISCC_RR3_B_EXTIP	0x01	/* channel b ext/status interrupt pending	*/
#define	ISCC_RR3_B_TXIP		0x02	/* channel b tx interrupt pending		*/
#define	ISCC_RR3_B_RXIP		0x04	/* channel b rx interrupt pending		*/
#define	ISCC_RR3_A_EXTIP	0x08	/* channel a ext/status interrupt pending	*/
#define	ISCC_RR3_A_TXIP		0x10	/* channel a tx interrupt pending		*/
#define	ISCC_RR3_A_RXIP		0x20	/* channel a rx interrupt pending		*/


/*
 * z8530 miscellaneous status register (ISCC_RR10)
 */

#define	ISCC_RR10_ON_LOOP	0x02	/* on loop (sdlc)				*/
#define	ISCC_RR10_LOOP_TX	0x10	/* loop send (sdlc)				*/
#define	ISCC_RR10_1CLKMISS	0x40	/* 2 clocks missing				*/
#define	ISCC_RR10_2CLKMISS	0x80	/* 1 clock missing				*/


/*
 * z8530 external status interrupt enable register (ISCC_RR15)
 */

#define	ISCC_RR15_ZCOUNT_IE	0x02	/* zero count interrupt enable			*/
#define	ISCC_RR15_DCD_IE	0x08	/* data carrier detect interrupt enable		*/
#define	ISCC_RR15_HUNT_IE	0x10	/* hunt interrupt enable			*/
#define	ISCC_RR15_SYNC_IE	0x10	/* sync interrupt enable			*/
#define	ISCC_RR15_CTS_IE	0x20	/* clear to send interrupt enable		*/
#define	ISCC_RR15_TXUR_IE	0x40	/* tx underrun/eom interrupt enable		*/

#define	ISCC_RR15_BREAK_IE	0x80	/* break detected interrupt enable		*/
#define	ISCC_RR15_ABORT_IE	0x80	/* abort detected interrupt enable		*/


/*
 * z8530 command register (ISCC_WR0)
 */

#define	ISCC_WR0_REGSEL		0x07	/* register select				*/

#define	ISCC_WR0_CC		0x38	/* command code					*/
#define	ISCC_WR0_CC_RST_EXTIP	0x10	/*   2 = reset external/status interrupts	*/
#define	ISCC_WR0_CC_SEND_ABORT	0x18	/*   3 = send abort (sdlc)			*/
#define	ISCC_WR0_CC_E_NXT_RCHR	0x20	/*   4 = enable interrupt on next rx character	*/
#define	ISCC_WR0_CC_RST_TXIP	0x28	/*   5 = reset tx interrupt pending		*/
#define	ISCC_WR0_CC_ERR_RST	0x30	/*   6 = error reset				*/
#define	ISCC_WR0_CC_RST_HIUS	0x38	/*   7 = reset highest ius			*/

#define	ISCC_WR0_CRC_RST	0xc0	/* crc reset code				*/
#define	ISCC_WR0_CRC_RST_RX	0x40	/*   1 = reset rx crc checker			*/
#define	ISCC_WR0_CRC_RST_TX	0x80	/*   2 = reset tx crc generator			*/
#define	ISCC_WR0_CRC_RST_TXUR	0xc0	/*   3 = reset tx underrun/eom latch		*/


/*
 * z8530 tx/rx interrupt data & transfer mode (ISCC_WR1)
 */

#define	ISCC_WR1_EXT_IE		0x01	/* external/status master interrupt enable	*/
#define	ISCC_WR1_TXIE		0x02	/* tx interrupt enable				*/
#define	ISCC_WR1_PSPC		0x04	/* parity is special condition			*/

#define	ISCC_WR1_RXINT		0x18	/* rx interrupt mode				*/
#define	ISCC_WR1_RXINT_DS	0x00	/*   0 = rx interrupt disabled			*/
#define	ISCC_WR1_RXINT_1ST	0x08	/*   1 = rx interrupt on 1st character or 	*/
					/*	 special condition			*/
#define	ISCC_WR1_RXINT_ALL	0x10	/*   2 = rx interrupt on all rx characters or	*/
					/*	 special condition			*/
#define	ISCC_WR1_RXINT_SPC	0x18	/*   3 = rx interrupt on special condition	*/

#define	ISCC_WR1_WDMA		0x20	/* wait/dma request on tx or rx			*/
#define	ISCC_WR1_WDMA_SEL	0x40	/* wait/dma request select			*/
#define	ISCC_WR1_WDMA_EN	0x80	/* wait/dma request enable			*/


/*
 * z8530 rx parameters & control (ISCC_WR3)
 */

#define	ISCC_WR3_RXEN		0x01	/* rx enable					*/
#define	ISCC_WR3_SCLI		0x02	/* sync character load inhibit			*/
#define	ISCC_WR3_ASM		0x04	/* address search mode (sdlc)			*/
#define	ISCC_WR3_RCEN		0x08	/* rx crc enable				*/
#define	ISCC_WR3_EHM		0x10	/* enter hunt mode				*/
#define	ISCC_WR3_AEN		0x20	/* auto enable					*/

#define	ISCC_WR3_RXLEN		0xc0	/* rx character length				*/
#define	ISCC_WR3_RXLEN_5	0x00	/*   0 = 5 bits/rx character			*/
#define	ISCC_WR3_RXLEN_6	0x40	/*   1 = 6 bits/rx character			*/
#define	ISCC_WR3_RXLEN_7	0x80	/*   2 = 7 bits/rx character			*/
#define	ISCC_WR3_RXLEN_8	0xc0	/*   3 = 8 bits/rx character			*/


/*
 * z8530 tx/rx miscellaneous parameters & modes	(ISCC_WR4)
 */

#define	ISCC_WR4_PAREN		0x01	/* tx/rx parity enable				*/

#define	ISCC_WR4_PARSEL		0x02	/* parity even/odd select			*/
#define	ISCC_WR4_PARSEL_ODD	0x00	/*   0 = odd parity				*/
#define	ISCC_WR4_PARSEL_EVEN	0x02	/*   1 = even parity				*/

#define	ISCC_WR4_SYNC_EN	0x00	/* sync modes enable				*/

#define	ISCC_WR4_STOP		0x0c	/* stop bits/character				*/
#define	ISCC_WR4_STOP_1		0x04	/*   1 = 1 stop bit/character			*/
#define	ISCC_WR4_STOP_1_5	0x08	/*   2 = 1.5 stop bits/character		*/
#define	ISCC_WR4_STOP_2		0x0c	/*   3 = 2 stop bits/characters			*/

#define	ISCC_WR4_SYNC		0x30	/* sync character				*/
#define	ISCC_WR4_SYNC_8		0x00	/*   0 = 8-bit sync character			*/
#define	ISCC_WR4_SYNC_16	0x10	/*   1 = 16-bit sync character			*/
#define	ISCC_WR4_SYNC_SDLC	0x20	/*   2 = sdlc mode				*/
#define	ISCC_WR4_SYNC_EXTSYNC	0x30	/*   3 = external sync mode			*/

#define	ISCC_WR4_CLK		0xc0	/* clock rate					*/
#define	ISCC_WR4_CLK_X1		0x00	/*   0 = x1 clock				*/
#define	ISCC_WR4_CLK_X16	0x40	/*   1 = x16 clock				*/
#define	ISCC_WR4_CLK_X32	0x80	/*   2 = x32 clock				*/
#define	ISCC_WR4_CLK_X64	0xc0	/*   2 = x64 clock				*/


/*
 * z8530 tx parameters & control (ISCC_WR5)
 */

#define	ISCC_WR5_TCEN		0x01	/* tx crc enable				*/
#define	ISCC_WR5_RTS		0x02	/* request to send				*/

#define	ISCC_WR5_POLY		0x04	/* tx/rx crc polynomial				*/
#define	ISCC_WR5_POLY_SDLC	0x00	/*   0 = sdlc polynomial			*/
#define	ISCC_WR5_POLY_CRC16	0x04	/*   1 = crc-16 polynomial			*/

#define	ISCC_WR5_TXEN		0x08	/* tx enable					*/
#define	ISCC_WR5_SEND_BREAK	0x10	/* send break					*/

#define	ISCC_WR5_TXLEN		0x60	/* tx character length				*/
#define	ISCC_WR5_TXLEN_5	0x00	/*   0 = 5 bits/tx character			*/
#define	ISCC_WR5_TXLEN_6	0x20	/*   1 = 6 bits/tx character			*/
#define	ISCC_WR5_TXLEN_7	0x40	/*   2 = 7 bits/tx character			*/
#define	ISCC_WR5_TXLEN_8	0x60	/*   3 = 8 bits/tx character			*/

#define	ISCC_WR5_DTR		0x80	/* data terminal ready				*/


/*
 * z8530 master interrupt control & reset (ISCC_WR9)
 */

#define	ISCC_WR9_VIS		0x01	/* vector includes status			*/
#define	ISCC_WR9_NV		0x02	/* no vector					*/
#define	ISCC_WR9_DLC		0x04	/* disable lower chain				*/
#define	ISCC_WR9_MIE		0x08	/* master interrupt enable			*/

#define	ISCC_WR9_STATUS		0x10	/* interrupt vector modification for status	*/
#define	ISCC_WR9_STATUS_LO	0x00	/*   0 = modifies vector v3-v1			*/
#define	ISCC_WR9_STATUS_HI	0x10	/*   1 = modifies vector v6-v4			*/

#define	ISCC_WR9_INTACK		0x20	/* software interrupt acknowledge		*/

#define	ISCC_WR9_RSTCMD		0xc0	/* reset command				*/
#define	ISCC_WR9_RSTCMD_B	0x40	/*   1 = reset channel b			*/
#define	ISCC_WR9_RSTCMD_A	0x80	/*   2 = reset channel a			*/
#define	ISCC_WR9_RSTCMD_HWD	0xc0	/*   3 = force hardware reset			*/


/*
 * z8530 miscellaneous tx/rx control (ISCC_WR10)
 */

#define	ISCC_WR10_SYNC		0x01	/* 6-bit/8-bit sync				*/
#define	ISCC_WR10_SYNC_8BIT	0x00	/*   0 = 8-bit sync				*/
#define	ISCC_WR10_SYNC_6BIT	0x01	/*   1 = 6-bit sync				*/

#define	ISCC_WR10_LOOP		0x02	/* loop mode (sdlc)				*/
#define	ISCC_WR10_AFU		0x04	/* abort/flag on tx underrun			*/
#define	ISCC_WR10_MFI		0x08	/* mark/flag idle				*/
#define	ISCC_WR10_GAP		0x10	/* go active on poll				*/

#define	ISCC_WR10_DE		0x60	/* sync data encoding				*/
#define	ISCC_WR10_DE_NRZ	0x00	/*   0 = nrz					*/
#define	ISCC_WR10_DE_NRZI	0x20	/*   1 = nrzi					*/
#define	ISCC_WR10_DE_FM1	0x40	/*   2 = fm (transition = 1)			*/
#define	ISCC_WR10_DE_FM0	0x60	/*   3 = fm (transition = 0)			*/

#define	ISCC_WR10_CRC_PRESET	0x80	/* crc preset 					*/
#define	ISCC_WR10_CRC_PRESET_0	0x00	/*   0 = crc checker/generator preset to 0	*/
#define	ISCC_WR10_CRC_PRESET_1	0x80	/*   1 = crc checker/generator preset to 1	*/


/*
 * z8530 clock mode control (ISCC_WR11)
 */

#define	ISCC_WR11_TRxC		0x03	/* TRxC pin output source select		*/
#define	ISCC_WR11_TRxC_XTAL	0x00	/*   0 = xtal oscillator output			*/
#define	ISCC_WR11_TRxC_TXCLK	0x01	/*   1 = tx clock				*/
#define	ISCC_WR11_TRxC_BRGEN	0x02	/*   2 = baud rate generator			*/
#define	ISCC_WR11_TRxC_DPLL	0x03	/*   3 = digital phase-locked loop		*/

#define	ISCC_WR11_TRxC_IO	0x04	/* TRxC pin i/o control				*/
#define	ISCC_WR11_TRxC_IO_IN	0x00	/*   0 = set TRxC as input pin			*/
#define	ISCC_WR11_TRxC_IO_OUT	0x04	/*   1 = set TRxC as output pin			*/

#define	ISCC_WR11_TXCLK		0x18	/* tx clock source				*/
#define	ISCC_WR11_TXCLK_RTxC	0x00	/*   0 = RTxC pin				*/
#define	ISCC_WR11_TXCLK_TRxC	0x08	/*   1 = TRxC pin				*/
#define	ISCC_WR11_TXCLK_BRGEN	0x10	/*   2 = baud rate generator			*/
#define	ISCC_WR11_TXCLK_DPLL	0x18	/*   3 = digital phase-locked loop		*/

#define	ISCC_WR11_RXCLK		0x60	/* rx clock source				*/
#define	ISCC_WR11_RXCLK_RTxC	0x00	/*   0 = RTxC pin				*/
#define	ISCC_WR11_RXCLK_TRxC	0x20	/*   1 = TRxC pin				*/
#define	ISCC_WR11_RXCLK_BRGEN	0x40	/*   2 = baud rate generator			*/
#define	ISCC_WR11_RXCLK_DPLL	0x60	/*   3 = digital phase-locked loop		*/

#define	ISCC_WR11_RTxC		0x80	/* RTxC pin input signal select			*/
#define	ISCC_WR11_RTxC_NOXTAL	0x00	/*   0 = ttl-compatible clock			*/
#define	ISCC_WR11_RTxC_XTAL	0x80	/*   1 = xtal oscillator			*/


/*
 * z8530 miscellaneous control (ISCC_WR14)
 */

#define	ISCC_WR14_BRGEN_EN	0x01	/* baud rate generator enable			*/

#define	ISCC_WR14_BRGEN_SC	0x02	/* baud rate generator source			*/
#define	ISCC_WR14_BRGEN_SC_RTxC	0x00	/*   0 = scc's RTxC pin				*/
#define	ISCC_WR14_BRGEN_SC_PCLK	0x02	/*   1 = scc's PCLK pin				*/

#define	ISCC_WR14_DTR		0x00	/* dtr select					*/
#define	ISCC_WR14_REQ		0x04	/* request select				*/

#define	ISCC_WR14_AUTOECHO	0x08	/* auto echo					*/
#define	ISCC_WR14_LOCALLOOP	0x10	/* local loopback				*/

#define	ISCC_WR14_DPLL		0xe0	/* digital phase-locked loop command		*/
#define	ISCC_WR14_DPLL_ESM	0x20	/*   1 = enter search mode			*/
#define	ISCC_WR14_DPLL_RMC	0x40	/*   2 = reset missing clock			*/
#define	ISCC_WR14_DPLL_DS	0x60	/*   3 = disable dpll				*/
#define	ISCC_WR14_DPLL_BRGEN	0x80	/*   4 = set source to baud rate generator	*/
#define	ISCC_WR14_DPLL_RTxC	0xa0	/*   5 = set source to scc's RTxC pin input	*/
#define	ISCC_WR14_DPLL_FM	0xc0	/*   6 = operate dpll in fm mode		*/
#define	ISCC_WR14_DPLL_NRZI	0xe0	/*   7 = operate dpll in nrzi mode		*/

#define	ISCC_WR14_RXCLK		0x60	/* rx clock source				*/
#define	ISCC_WR14_RXCLK_RTxC	0x00	/*   0 = RTxC pin				*/
#define	ISCC_WR14_RXCLK_TRxC	0x20	/*   1 = TRxC pin				*/
#define	ISCC_WR14_RXCLK_BRGEN	0x40	/*   2 = baud rate generator			*/
#define	ISCC_WR14_RXCLK_DPLL	0x60	/*   3 = dpll					*/


/*
 * z8530 external/status interrupt control (ISCC_WR15)
 */

#define	ISCC_WR15_ZCOUNT_IE	0x02	/* zero count interrupt enable			*/
#define	ISCC_WR15_FIFO_EN	0x04	/* sdlc fifo enable 				*/
#define	ISCC_WR15_DCD_IE	0x08	/* data carrier detect interrupt enable		*/

#define	ISCC_WR15_HUNT_IE	0x10	/* hunt interrupt enable			*/
#define	ISCC_WR15_SYNC_IE	0x10	/* sync interrupt enable			*/

#define	ISCC_WR15_CTS_IE	0x20	/* clear to send interrupt enable		*/
#define	ISCC_WR15_TXUR_IE	0x40	/* tx underrun/eom interrupt enable		*/

#define	ISCC_WR15_BREAK_IE	0x80	/* break detected interrupt enable		*/
#define	ISCC_WR15_ABORT_IE	0x80	/* abort detected interrupt enable		*/


/*
 * z8530 driver configurable constants
 */

#ifndef NISCC
#define NISCC			1	/* if BINARY, hardwire this to 1		*/
#endif

#define	NISCC_DEV     		NISCC	/* number of configured z8530 devices		*/
#define	NISCC_LINE   NISCC_CHAN*NISCC	/* number of configured serial lines		*/
#define	NISCC_SPEED		17	/* number of supported baud rates - determined	*/
					/* by the 'iscc_speeds' driver table in iscc.c	*/


/*
 * z8530 driver serial line constants
 */

#define	ISCC_LINE_COMM1		0	/* comm1's serial line number			*/
#define	ISCC_LINE_COMM2		1	/* comm2's serial line number			*/
#define	ISCC_LINE_CONS		0	/* console's serial line number			*/
#define	ISCC_LINE_KDEBUG	1	/* kdebug kernel debugger's serial line number	*/


/*
 * z8530 driver structures 
 */

struct iscc_mem_regfile			/* iscc memory-resident hardware register file	*/
    {
    u_int rr0;				/* tx/rx buffer status & external status	*/
    u_int wr1;				/* tx/rx interrupt data & transfer mode		*/
    u_int wr2;				/* interrupt vector				*/
    u_int wr3;				/* rx parameters & control			*/
    u_int wr4;				/* tx/rx miscellaneous parameters & modes	*/
    u_int wr5;				/* tx parameters & control			*/
    u_int wr6;				/* sync characters or sdlc address field	*/
    u_int wr7;				/* sync characters or sdlc flag			*/
    u_int wr8;				/* tx buffer					*/
    u_int wr9;				/* master interrupt control & reset	 	*/
    u_int wr10;				/* miscellaneous tx/rx control			*/
    u_int wr11;				/* clock mode control				*/
    u_int wr12;				/* baud rate generator time constant	 	*/
    u_int wr13;				/* baud rate generator time constant	 	*/
    u_int wr14;				/* miscellaneous control			*/
    u_int wr15;				/* external/status interrupt control		*/
    };

struct iscc_softc			/* iscc driver soft controller structure	*/
    {
    long sc_category_flags[NISCC_LINE];		/* per-line category flags		*/
    long sc_flags[NISCC_LINE];			/* per-line state flags			*/
    u_int sc_harderrcnt[NISCC_LINE];		/* per-line hard error count		*/
    u_int sc_softerrcnt[NISCC_LINE];		/* per-line soft error count		*/
    struct iscc_mem_regfile
	sc_mem_regfile[NISCC_LINE];		/* per-line memory-resident hardware 	*/
						/* register file			*/
    struct speedtab
	sc_speeds_hi[NISCC_DEV][NISCC_SPEED];	/* per-device time constant table for	*/
						/* hi byte of each supported baud rate	*/
    struct speedtab
	sc_speeds_lo[NISCC_DEV][NISCC_SPEED];	/* per-device time constant table for	*/
						/* lo byte of each supported baud rate	*/
    };


/*
 * z8530 per-line state flags
 */

#define	LINE_INIT_DONE	      0x0001	/* line (channel) initialization done		*/
#define	LINE_INTR_ENA	      0x0002	/* line (controller) interrupts enabled		*/
#define	LINE_INUSE_KDEBUG     0x0004	/* line inuse by kdebug kernel debugger		*/

#endif	/* _EISA_ISCCREGS_H_ */
