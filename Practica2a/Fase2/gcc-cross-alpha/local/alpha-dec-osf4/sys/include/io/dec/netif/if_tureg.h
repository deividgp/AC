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

#ifndef _IF_TUREG_H_
#define _IF_TUREG_H_

/*
 * TULIP Transmit & Receive descriptors
 */
struct tu_desc  {
   u_short	tu_status;	/* status flags */
   unsigned	tu_rflen:15;	/* rcv frame length */
   unsigned	tu_own:1;	/* ownership bit */
   unsigned	tu_bfsize1:11;	/* buffer size 1 */
   unsigned	tu_bfsize2:11;	/* buffer size 2 */
   unsigned	tu_control:10;	/* control flags */
   u_int	tu_bfaddr1;	/* buffer address 1 */
   u_int	tu_bfaddr2;	/* buffer address 2 */
};

#define TUDESC struct tu_desc

/*
 * TULIP receive status (RDES0<00:15>)
 */
#define TU_OF			0x0001	/* Overflow			*/
#define TU_CE			0x0002	/* CRC error			*/
#define TU_DB			0x0004	/* Dribbling Bits		*/
#define TU_RJ			0x0010	/* Receive Watchdog		*/
#define TU_FT			0x0020	/* Frame Type 			*/
#define TU_CS			0x0040	/* Collision Seen 		*/
#define TU_RTL			0x0080	/* Frame Too Long		*/
#define TU_RLS			0x0100	/* Last Segment			*/
#define TU_RFS			0x0200	/* First Segment		*/
#define TU_MF			0x0400	/* Multicast Frame		*/
#define TU_RF			0x0800	/* Runt Frame	 		*/
#define TU_DT			0x3000	/* Data Type	 		*/
#define TU_RLE			0x4000	/* Length Error 		*/

/* Receive Data types */
#define TU_DT_RSRF		0x0000   /* Serial Received Frame       */
#define TU_DT_RILF		0x1000   /* Internally Looped back Frame*/
#define TU_DT_RELF		0x2000   /* External looped back Frame  */
  
/*
 * TULIP transmit status (TDES0<00:15>)
 */
#define	TU_DE			0x0001	/* Deferred - network busy	*/
#define	TU_UF			0x0002	/* Underflow Error		*/
#define	TU_LF			0x0004	/* Link Fail			*/
#define	TU_CC			0x0078	/* Mask for Collision Count	*/
#define	TU_HF			0x0080	/* Heartbeat Fail		*/
#define	TU_EC			0x0100	/* Excessive Collisions		*/
#define	TU_LC			0x0200	/* Late Collision		*/
#define	TU_NC			0x0400	/* No Carrier			*/
#define	TU_LO			0x0800	/* Loss of Carrier 		*/
#define	TU_TO			0x4000	/* Transmit Watchdog Timeout    */

#define TU_ES			0x8000	/* Common Error Summary bit	*/

/*
 * A status of all 1s is returned if a Setup Frame completes successfully
 */
#define	TU_SETUP_OK		0xFFFF

/* 
 * TULIP receive control (RDES1<31:22>)
 */
#define TU_RCH			0x0004	/* Second Address Chained */
#define TU_RER			0x0008	/* Receive End of Ring */

/* 
 * TULIP transmit control (TDES1<31:22>)
 */
#define TU_HP			0x0001	/* Hash/Perfect Filtering */
#define TU_DPD			0x0002	/* Disable Padding */
#define TU_TCH			0x0004	/* Second Address Chained */
#define TU_TER			0x0008	/* Transmit End of Ring */
#define TU_AC			0x0010	/* Add CRC Disable */
#define TU_SET			0x0020	/* Setup packet */
#define TU_IV			0x0040	/* Inverse Filtering */
#define TU_TFS			0x0080	/* First Segment */
#define TU_TLS			0x0100	/* Last Segment */
#define TU_IC			0x0200	/* Interrupt on Completion */


/*
 * Ownership bit definition
 */
#define	TU_HOST			0	/* We own the descriptor	*/
#define	TU_TULIP		1	/* TULIP owns the descriptor	*/


/*
 * TULIP CSR definitions:
 */

/*
 * CSR0 - Bus Mode Register
 */
#define TU_CSR0_SWR	0x00000001	/* Software Reset		*/
#define TU_CSR0_BAR	0x00000002	/* Bus Arbitration		*/
#define TU_CSR0_DSL	0x0000007C	/* Descriptor Skip Length	*/
#define TU_CSR0_BLE	0x00000080	/* Big/Little Endian		*/
#define TU_CSR0_PBL	0x00003F00	/* Programmable Burst Length	*/
#define TU_CSR0_CAL	0x0000C000	/* Cache Alignment		*/
#define TU_CSR0_DAS	0x00010000	/* Diagnostic Address Space	*/
#define TU_CSR0_TAP	0x00060000	/* Transmit Automatic Polling	*/

/* Programmable Burst Lengths */
#define TU_PBL_0	(0 << 8)	/* */
#define TU_PBL_1	(1 << 8)	/* */
#define TU_PBL_2	(2 << 8)	/* */
#define TU_PBL_4	(4 << 8)	/* */
#define TU_PBL_8	(8 << 8)	/* */
#define TU_PBL_16	(16 << 8)	/* */
#define TU_PBL_32	(32 << 8)	/* */

/* Cache Alignment values */
#define TU_CAL_0	(0 << 14)	/* No address alignment	        */
#define TU_CAL_8	(1 << 14)	/* 8 lw address alignment       */
#define TU_CAL_16	(2 << 14)	/* 16 lw address alignment      */
#define TU_CAL_32	(3 << 14)	/* 32 lw address alignment      */

/* Transmit Auto Polling intervals */
#define	TU_TAP_0	(0 << 17)	/* No Auto polling		*/
#define	TU_TAP_200	(1 << 17)	/* Auto polling every 200 usec 	*/
#define	TU_TAP_800	(2 << 17)	/* Auto polling every 800 usec 	*/
#define	TU_TAP_1600	(3 << 17)	/* Auto polling every 1600 usec	*/

/*
 * WARNING: For DECchip 21040 and 21041, either CAL or Burst Length MUST
 *          be lower than 32 LWs to avoid undetected data corruption. See
 *          OSF_QAR 39571 for further details.
 */
#define	TU_CSR0_2104x	(TU_CSR0_BAR | TU_PBL_16 | TU_CAL_16)
#define	TU_CSR0_2114x	(TU_CSR0_BAR | TU_PBL_32 | TU_CAL_32)

/*
 * CSR1 - Transmit Poll Demand Register
 * CSR2 - Receive Poll Demand Register
 * CSR3 - Receive Ring Base Address Register
 * CSR4 - Transmit Ring Base Address Register
 */


/* 
 * CSR5 - Status Register
 */
#define TU_CSR5_TI	0x00000001	/* Transmit Interrupt		*/
#define TU_CSR5_TPS	0x00000002	/* Transmit Process Stopped	*/
#define TU_CSR5_TU	0x00000004	/* Transmit Buffer Unavailable	*/
#define TU_CSR5_TJT	0x00000008	/* Transmit Jabber Time-Out	*/
#define TU_CSR5_LNP	0x00000010	/* Link Pass - 21041 only	*/
#define TU_CSR5_UNF	0x00000020	/* Transmit Underflow		*/
#define TU_CSR5_RI	0x00000040	/* Receive Interrupt            */
#define TU_CSR5_RU	0x00000080	/* Receive Buffer Unavailable   */
#define TU_CSR5_RPS	0x00000100	/* Receive Process Stopped	*/
#define TU_CSR5_RWT	0x00000200	/* Receive Watchdog Timeout	*/ 
#define TU_CSR5_AT	0x00000400	/* AUI/TP Switch - 21040 only 	*/ 
#define TU_CSR5_FD	0x00000800	/* FDX Short Frame - 21040 only	*/ 
#define TU_CSR5_TM	0x00000800	/* Timer Expired - 21041 only	*/ 
#define TU_CSR5_LNF	0x00001000	/* Link Failure			*/ 
#define TU_CSR5_SE	0x00002000	/* System Error			*/ 
#define TU_CSR5_ER	0x00004000	/* Early Receive - 21041 only	*/ 
#define TU_CSR5_AIS	0x00008000	/* Abnormal Interrupt Summary	*/
#define TU_CSR5_NIS	0x00010000	/* Normal Interrupt Summary	*/
#define TU_CSR5_RS	0x000E0000	/* Receive Process State	*/
#define TU_CSR5_TS	0x00700000	/* Transmit Process State	*/ 
#define TU_CSR5_EB	0x03800000	/* Error Bits			*/ 
 
#define	TU_CSR5_INIT	0xFFFFFFFF	/* Clear out all errors		*/

/* Receive Process States */
#define TU_RS_STP	(0 << 17)	/* Stoppped		        */
#define TU_RS_RUN_FETCH	(1 << 17)	/* Running - fetch Rx Desc      */
#define TU_RS_RES	(2 << 17)	/* Reserved		        */
#define TU_RS_RUN_WAIT	(3 << 17)	/* Running - wait for Rx Pkt    */
#define TU_RS_SUS	(4 << 17)	/* Suspended			*/
#define TU_RS_RUN_CLOSE	(5 << 17)	/* Running - close Rx Desc	*/
#define TU_RS_RUN_FLUSH	(6 << 17)	/* Running - flush buf unavail	*/
#define TU_RS_RUN_DEQUE	(7 << 17)	/* Running - deque Rx from FIFO	*/

/* Transmit Process States */
#define TU_TS_STP	(0 << 20)	/* Stoppped		        */
#define TU_TS_RUN_FETCH	(1 << 20)	/* Running - fetch Tx Desc      */
#define TU_TS_RUN_WAIT	(2 << 20)	/* Running - wait for end of Tx	*/
#define TU_TS_RUN_ENQUE	(3 << 20)	/* Running - enque Tx to FIFO	*/
#define TU_TS_RES	(4 << 20)	/* Reserved		        */
#define TU_TS_RUN_SETUP	(5 << 20)	/* Running - setup Pkt		*/
#define TU_TS_SUS	(6 << 20)	/* Suspended			*/
#define TU_TS_RUN_CLOSE	(7 << 20)	/* Running - close Tx Desc	*/ 

/* Bus Error bits */
#define TU_EB_PARITY	(0 << 23)	/* Parity error			*/
#define TU_EB_MASTER	(1 << 23)	/* Master abort			*/
#define TU_EB_TARGET	(2 << 23)	/* Target abort			*/
#define TU_EB_RES1	(3 << 23)	/* Reserved		        */
#define TU_EB_RES2	(4 << 23)	/* Reserved		        */
#define TU_EB_RES3	(5 << 23)	/* Reserved		        */
#define TU_EB_RES4	(6 << 23)	/* Reserved		        */
#define TU_EB_RES5	(7 << 23)	/* Reserved		        */


/* 
 * CSR6 - Command Register
 */
#define TU_CSR6_HP	0x00000001	/* Hash/Perfect Rcv Filter Mode	*/
#define TU_CSR6_SR	0x00000002	/* Start/Stop Receive		*/
#define TU_CSR6_HO	0x00000004	/* Hash Only			*/
#define TU_CSR6_PB	0x00000008	/* Pass Bad Frames		*/
#define TU_CSR6_IF	0x00000010	/* Inverse Filtering		*/
#define TU_CSR6_SB	0x00000020	/* Start/Stop Backoff Counter	*/
#define TU_CSR6_PR	0x00000040	/* Promiscuous Mode		*/
#define TU_CSR6_PM	0x00000080	/* Pass All MultiCast		*/
#define TU_CSR6_FKD	0x00000100	/* Flaky Oscillator Disable	*/
#define TU_CSR6_FD	0x00000200	/* Full Duplex Operating Mode	*/
#define TU_CSR6_OM	0x00000C00	/* Operating Mode		*/
#define TU_CSR6_FC	0x00001000	/* Force Collision Mode		*/
#define TU_CSR6_ST	0x00002000	/* Start/Stop Transmission Cmd	*/
#define TU_CSR6_TR	0x0000C000	/* Threshold control bits	*/
#define TU_CSR6_BP	0x00010000	/* Back Pressure - 21040 only	*/
#define TU_CSR6_CA	0x00020000	/* Capture Effect		*/
/* DECchip 21140 - FasterNet definitions only */
#define TU_CSR6_PS	0x00040000	/* Port Select(10/100)		*/
#define TU_CSR6_HBD	0x00080000	/* HeartBeat Disable		*/
#define TU_CSR6_IMM	0x00100000	/* Immediate Transmission	*/
#define TU_CSR6_SF	0x00200000	/* Store & Forward		*/
#define TU_CSR6_TTM	0x00400000	/* Transmit Threshold Mode	*/
#define TU_CSR6_PCS	0x00800000	/* Port CS Mode			*/
#define TU_CSR6_SCR	0x01000000	/* Scrambler Mode		*/
#define TU_CSR6_MBO	0x02000000	/* 21140 and 21143		*/
/* DECchip 21041 only */
#define TU_CSR6_SC 	0x80000000	/* Special Capture Effect	*/

/* Operating Mode */
#define TU_OM_NOR	(0 << 10)	/* Normal 		        */
#define TU_OM_INL	(1 << 10)	/* Internal Loopback            */
#define TU_OM_EXL	(2 << 10)	/* External Loopback            */

/* Threshold control bits 		   21040-1		21140	*/
#define TU_TR_72	(0 << 14)	/* 72 bytes 	      128 bytes	*/
#define TU_TR_96	(1 << 14)	/* 96 bytes	      256 bytes */
#define TU_TR_128	(2 << 14)	/* 128 bytes	      512 bytes */
#define TU_TR_160	(3 << 14)	/* 160 bytes	     1024 bytes */

#define	TU_CSR6_2104x	TU_TR_160	/* MUST be MAX for 21040 to	*/
					/* avoid data corruption	*/

/*
 * CSR7 - Interrupt Mask Register
 */
#define TU_CSR7_TIM	0x00000001	/* Transmit Interrupt 		*/
#define TU_CSR7_TSM	0x00000002	/* Transmit Process Stopped 	*/
#define TU_CSR7_TUM	0x00000004	/* Transmit Buffer Unavailable	*/
#define TU_CSR7_TJM	0x00000008	/* Transmit Jabber Time-Out	*/
#define TU_CSR7_LPM	0x00000010	/* Link Pass Mask - 21041 only	*/
#define TU_CSR7_UNM	0x00000020	/* Transmit Underflow		*/
#define TU_CSR7_RIM	0x00000040	/* Receive Interrupt            */
#define TU_CSR7_RUM	0x00000080	/* Receive Buffer Unavailable   */
#define TU_CSR7_RSM	0x00000100	/* Receive Process Stopped	*/
#define TU_CSR7_RWM	0x00000200	/* Receive Watchdog Timeout	*/ 
#define TU_CSR7_ATM	0x00000400	/* AUI/TP Switch - 21040 only	*/ 
#define TU_CSR7_FDM	0x00000800	/* FDX Short Frame - 21040 only	*/ 
#define TU_CSR7_TMM	0x00000800	/* Timer Expired - 21041 only	*/ 
#define TU_CSR7_LFM	0x00001000	/* Link Failure			*/ 
#define TU_CSR7_SEM	0x00002000	/* System Error			*/ 
#define TU_CSR7_ERM	0x00004000	/* Early Receive - 21041 only	*/ 
#define TU_CSR7_AIM	0x00008000	/* Abnormal Interrupt Summary	*/
#define TU_CSR7_NIM	0x00010000	/* Normal Interrupt Summary	*/

#define	TU_CSR7_INIT	(TU_CSR7_TIM | TU_CSR7_RIM | TU_CSR7_NIM | TU_CSR7_AIM)

/*
 * CSR8 - Missed Frame Counter Register
 */
#define TU_CSR8_MFC	0x0000FFFF	/* Missed Frame Count		*/
#define TU_CSR8_MFCO	0x00010000	/* Missed Frame Count Overflow	*/


/*
 * CSR9 - Ethernet ROM Id Register
 * CSR10 - Data Diagnostic Register
 * CSR11 - Full Duplex Register
 * CSR12 - SIA Status Register		(DECchip 21040)
 * CSR12 - General Purpose Register	(DECchip 21140)
 */
#define	TU_CSR9_DN	0x80000000	/* Data Not valid bit  - 21040 */
#define	TU_CSR12_LNK	0x00000004	/* Linkfail status  - 21040/1 */

/* 21041 and 21140 definitions for CSR9 */

#define	TU_CSR9_CS	0x00000001	/* Chip Select */
#define	TU_CSR9_CLK	0x00000002	/* Clock */
#define	TU_CSR9_DT	0x00000004	/* Data In */
#define	TU_CSR9_DO	0x00000008	/* Data Out */
#define	TU_CSR9_SS	0x00000800	/* Serialrom Select */
#define	TU_CSR9_WR	0x00002000	/* Write select */
#define	TU_CSR9_RD	0x00004000	/* Read select */

#define	TU_CSR9_WRITE_SS	(TU_CSR9_WR | TU_CSR9_SS)
#define	TU_CSR9_WRITE_CS	(TU_CSR9_WRITE_SS | TU_CSR9_CS)
#define	TU_CSR9_WRITE_DT	(TU_CSR9_WRITE_CS | TU_CSR9_DT)
#define	TU_CSR9_WRITE_CLK	(TU_CSR9_WRITE_CS | TU_CSR9_CLK)
#define	TU_CSR9_WRITE_DT_CLK	(TU_CSR9_WRITE_DT | TU_CSR9_CLK)

/*
 * CSR12 - 
 */
#define	TU_CSR12_LS10		0x00000004	/* 21040, 21041, 21142, 21143 */
#define	TU_CSR12_LS100		0x00000002	/* 21143 only */

/*
 * CSR13 - SIA Connectivity Register	(DECchips 21040/1)
 */

/*
 * CSR14 - SIA Transmit/Receive Register(DECchip 21040/1)
 * CSR14 - MAC Parameters Register	(DECchip 21140)
 * CSR15 - SIA General Register
 */
#define	TU_CSR14_ANE		0x00000080	/* Auto-Negotiation Enabled */

/*
 * PCI Configuration register offsets for EISA-Tulip
 */
#define	TU_EISA_CFID	0x08		/* Configuration Id */
#define	TU_EISA_CFCS	0x0C		/* Configuration Command-Status */
#define	TU_EISA_CFRV	0x18		/* Configuration Revision */
#define	TU_EISA_CFLT	0x1C		/* Configuration Latency Timer */
#define	TU_EISA_CBIO	0x28		/* Configuration Base IO Address */
#define	TU_EISA_CFDA	0x2C		/* Configuration Driver Area */

/*
 * PCI Configuration register offsets for PCI-Tulip
 */
#define	TU_PCI_CFID	0x00 		/* Configuration Id */
#define	TU_PCI_CFCS	0x04		/* Configuration Command-Status */
#define	TU_PCI_CFRV	0x08		/* Configuration Revision */
#define	TU_PCI_CFLT	0x0C		/* Configuration Latency Timer */
#define	TU_PCI_CBIO	0x10		/* Configuration Base IO Address */
#define	TU_PCI_CBMA	0x14		/* Configuration Base Memory Address */
#define	TU_PCI_CFIT	0x3C		/* Configuration Interrupt */
#define	TU_PCI_CFDA	0x40		/* Configuration Driver Area */

/*
 *  MII definitions
 */
#define TU_MII_MDI	0x00080000	/* MII Management Data In */
#define TU_MII_MDO	0x00060000	/* MII Management Mode/Data Out */
#define TU_MII_MRD	0x00040000	/* MII Management Define Read Mode */
#define TU_MII_MWR	0x00000000	/* MII Management Define Write Mode */
#define TU_MII_MDT	0x00020000	/* MII Management Data Out */
#define TU_MII_MDC	0x00010000	/* MII Management Clock */
#define TU_MII_RD	0x00004000	/* Read from MII */
#define TU_MII_WR	0x00002000	/* Write to MII */
#define TU_MII_SEL	0x00000800	/* Select MII when RESET */

#define TU_MII_PREAMBLE (~0)		/* MII Management Preamble - 34 bits */
#define TU_MII_STARTRD  0x06		/* Start of Frame+Read Op Code: */
#define TU_MII_STARTWR  0x0A		/* Start of Frame+Write Op Code: */

/*
 * MII Registers
 */
#define TU_MII_CR	0x00		/* MII Management Control Register */
#define TU_MII_SR	0x01		/* MII Management Status Register */
#define TU_MII_ID	0x02		/* PHY Identifier Register (0) */
#define TU_MII_AR	0x04		/* Nway Advertisement Register */
#define TU_MII_PR	0x05		/* Nway Link Partner Ability Register */
#define TU_MII_ER	0x06		/* Nway Expansion Register */

/*
 * MII Control register
 */
#define TU_MII_CR_RST	0x8000		/* RESET the PHY chip */
#define TU_MII_CR_LPBK	0x4000		/* Loopback enable */
#define TU_MII_CR_10	0x0000		/* Set 10Mb/s */
#define TU_MII_CR_100	0x2000		/* Set 100Mb/s */
#define TU_MII_CR_ANE	0x1000		/* Auto Negotiation Enable */
#define TU_MII_CR_PD	0x0800		/* Power Down */
#define TU_MII_CR_ISOL	0x0400		/* Isolate Mode */
#define TU_MII_CR_RAN	0x0200		/* Restart Auto Negotiation */
#define TU_MII_CR_FDX	0x0100		/* Full Duplex Mode */
#define TU_MII_CR_CTE	0x0080		/* Collision Test Enable */

/*
 * MII Status register
 */
#define TU_MII_SR_T4C	0x8000		/* 100BASE-T4 capable */
#define TU_MII_SR_TXFD	0x4000		/* 100BASE-TX Full Duplex capable */
#define TU_MII_SR_TXHD	0x2000		/* 100BASE-TX Half Duplex capable */
#define TU_MII_SR_TFD	0x1000		/* 10BASE-T Full Duplex capable */
#define TU_MII_SR_THD	0x0800		/* 10BASE-T Half Duplex capable */
#define TU_MII_SR_TAF	0xf800		/* Technology Ability Field */
#define TU_MII_SR_ANC	0x0020		/* Auto Negotiation Complete*/
#define TU_MII_SR_RFD	0x0010		/* Remote Fault Detected */
#define TU_MII_SR_LKS	0x0004		/* Link Status */
#define TU_MII_SR_JABD	0x0002		/* Jabber Detect */

/*
 * Some EISA specific registers & bits
 */
#define	TU_EISA_ERA	0xC90		/* Ethernet ROM Address */

/*
 * Public file with MOP sysids is:  
 *	FILES::NET$ARCH:[REGISTRY]MOP-REGISTRY-PUBLIC.PS
 */
#define	EISA_TULIP_MOP_ID	202
#define	PCI_TULIP_MOP_ID	203

#endif	/* _IF_TUREG_H_ */

