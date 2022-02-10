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
 * @(#)$RCSfile: kn470.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1998/10/20 15:01:57 $
 */
#ifndef KN470_H
#define KN470_H

#include <sys/types.h>

struct kn470_mcheck_control {
	/* this is a per-cpu data structure for tracking machine check */
	/* error handing */

	/* The following set of structure elements are used for */
	/* intentional machine checks, such as those cause by BADADDR, */
	/* or probing. */
	u_int mcheck_expected;		/* flag: we're probing. */
	u_int mcheck_occurred;		/* Number of mchecks during probe. */
	memtest_t mcheck_tp_active;	/* testpage in progress? */
	long mcheck_page;		/* page being tested */
	long mcheck_return;		/* PC to return to if mcheck occurs */
					/* while testing memory */
};

#define GAMMA_SYSTEM_BASE	0x8000000000UL

/*
 * Sable CPU Module CSRS
 *
 * These are CSRs for hardware other than the CPU chip on the CPU module.
 * The CPU module has Backup Cache control logic, Cbus control logic, and
 * interrupt control logic on it.  There is a duplicate tag store to speed
 * up maintaining cache coherency.
 */

struct gamma_cpu_csr {
	u_long creg;	u_long fill_00[3]; /* Configuration Register */
	u_long esreg;	u_long fill_01[3]; /* Error Summary */

	u_long evbcr;	u_long fill_02[3]; /* EVBackup Cache Control */
	u_long evbear;	u_long fill_03[3]; /* EVBackup Cache Error Address */
	u_long evbcer;	u_long fill_04[3]; /* EVBackup Cache Correctable Error */
	u_long evbcear;	u_long fill_05[3]; /* EVB-Cache Corr Err Address Latch */
	u_long evbuer;	u_long fill_06[3]; /* EVB-Cache Uncorrectable Error */
	u_long evbuear;	u_long fill_07[3]; /* EVB-Cache Uncorr Err Addr Latch */
	u_long evresv;	u_long fill_08[3]; /* EVB Reserve Register */

	u_long dtctr;	u_long fill_09[3]; /* DupTag Control */
	u_long dter;	u_long fill_10[3]; /* DupTag Error */
	u_long dttcr;	u_long fill_11[3]; /* DupTag Test Control Register */
	u_long dttr;	u_long fill_12[3]; /* DupTag Test Register*/
	u_long dtresv;	u_long fill_13[3]; /* DupTag Reserve */

	u_long ibcsr;	u_long fill_14[3]; /* I-bus Control and Status */
	u_long ibear;	u_long fill_15[3]; /* I-bus Error Address  */

	u_long acr;	u_long fill_16[3]; /* Arbitration Control */

	u_long cbcr;	u_long fill_17[3]; /* CBus 2 Control */
	u_long cber;	u_long fill_18[3]; /* CBus 2 Error */
	u_long cbealr;	u_long fill_19[3]; /* CBus 2 Error Addr Latch low */
	u_long cbeahr;	u_long fill_20[3]; /* CBus 2 Error Addr Latch high */
	u_long cbresv;	u_long fill_21[3]; /* CBus 2 Reserve */

	u_long alr;	u_long fill_22[3]; /* Address Lock */
	u_long pmbr;	u_long fill_23[3]; /* Processor Mailbox */
	u_long iirr;	u_long fill_24[3]; /* Inter-Processor Int Request */
	u_long sicr;	u_long fill_25[3]; /* System Interrupt Clear */
	u_long mresv;	u_long fill_26[3]; /* Miscellaneous Reserve */

	u_long pmr1;	u_long fill_27[3]; /* Performace Register 1 */
	u_long pmr2;	u_long fill_28[3]; /* Performace Register 2 */
	u_long pmr3;	u_long fill_29[3]; /* Performace Register 3 */
	u_long pmr4;	u_long fill_30[3]; /* Performace Register 4 */
	u_long pmr5;	u_long fill_31[3]; /* Performace Register 5 */

};
typedef struct gamma_cpu_csr * gamma_cpu_csrp_t;

/* CSR00 - Configuration Register
 * The configuration register indecates the revision number of the
 * RATTLER ASICs.  It also has a field for configuring RATTLER when default mode of
 * operation needs to be modified.
 */
/*
 * 63:61 Cache Size 
 *	111 Undefined
 *	110 Undefined
 *	101 16MB
 *	100  8MB
 *	011  4MB
 *	010  2MB
 *	001  1MB
 *	000 Undefined
 */
#define CREG_CACHE_SIZE_SHIFT  	60
#define CREG_CACHE_SIZE_MASK  	(0x7UL << 60)	/* Cache Size (RW) */
#define CREG_DISABLE_EXCH_DLY1  (0x1UL << 59)	/* Disable Exchange Disable */
#define CREG_ACK_MB1  		(0x1UL << 58)	/* Acknowledge Memory Barrier */
#define CREG_ENABLE_4IDLEBC1	(0x1UL << 57)	
#define CREG_DISABLE_IDLEBC_CST	(0x1UL << 56)	
#define CREG_DISABLE_REVISION	(0xFUL << 32)	

/*
 * CSR01 - ESREG Error Summary Register
 * The error summary register provides read and write access to all error status 
 * bits in the RATTLER.  Ther error state can be determined for a read of this 
 * register and the errors may be cleared by writein 1 to clear through this 
 * register.  Supplimentary information is available in the other registers along 
 * with read only copies of the error bits also in this register.
 *
 * RATTLER has mainly four interface buses and there are error bits associated 
 * with each interface.  The error summary register provides a snapshot of error 
 * bits of those interface buses.
 *
 * Except for correctable ECC errors, all other missed error bits have been 
 * removed.  THis change supports the revised fault management strategy under 
 * which RATTLER disables error reporting from the EV5 Cbus2, duplicated, 
 * or I-bus interface after the first error from that interface section.
 */
/*
 * CB_ERR1 51:48
 *	or of bits 51-48 of CSR18 - CBER read data parity error
 *	or of bits 43-40 of CSR18 - CBER write data parity error 
 *	or of bits 37-36 of CSR18 - CBER CBER C/A high longword parity err1
 *	bit 32 of CSR18 - CBER uncorrectable read error
 */
#define ESREG_CB_SUMMARY1	(0x1UL << 56)
#define ESREG_CB_ERR1		(0xFUL << 48)

/*
 *	bit 38 of CSR14 - IBCSR commander cycle during ibus parity error1
 *	bit 37 of CSR14 - IBCSR snoop cycle during ibus parity err1
 */
#define ESREG_IB_SUMMARY1	(0x1UL << 47)
#define ESREG_IB_ERR1		(0x3UL << 45)
#define ESREG_IB_PAR_ERR1	(0x1UL << 44)
/*
 *	bit 63 of CSR10 - DTER tag parity error 1
 *	bit 60 of CSR10 - DTER Tag_con parity error1
 */
#define ESREG_DT_SUMMARY1	(0x1UL << 42)
#define ESREG_DT_ERR1		(0x3UL << 40)
/*
 *	bit 37 of CSR06 - EVBUER Parity error on victim address
 *	bit 36 of CSR06 - EVBUER Parity error on Add-Cmd bus
 *	bit 33:32 of CSR06 - EVBUER Uncorrectable Err 1
 */
#define ESREG_EVB_FATAL_ERR1		  (0xFUL << 36)
/*
 *	bit 29 of CSR18 - CBER cber data1 not acked
 *	bit 28 of CSR18 - CBER cber data0 not acked
 *	bit 24 of CSR18 - CBER cber c/a not acked
 * 	bit 20 of CSR18 - CBER Missed parity error write data01
 *	bit  0 of CSR18 - CBER uncorrectable read error
 *	OR bits 19-16 of  CSR18 - CBER read data parity error
 *	OR bits 11-8  of  CSR18 - CBER write data parity error
 *	OR bits 5-4 of CSR18 - CBER ca parity err0
 */
#define	ESREG_CB_SUMMARY0	(0x1UL << 24)
#define	ESREG_CB_ERR0		(0xFFUL << 16)

/*
 *	bit 06 of CSR14 - IBCSR commander cycle during ibus parity error0
 *	bit 05 of CSR14 - IBCSR snoop cycle during ibus parity err0
 */
#define ESREG_IB_SUMMARY0	   (0x1UL << 15)
#define ESREG_IB_ERR0		   (0x3UL << 13)
#define ESREG_IB_PAR_ERR0	   (0x1UL << 12)
/*
 *	bit 31 of CSR10 - DTER tag parity error 0
 *	bit 28 of CSR10 - DTER Tag_con parity error0
 */
#define ESREG_DT_SUMMARY0	   (0x1UL << 10)
#define ESREG_DT_ERR0		   (0x3UL << 8)
/*
 *	bit 5 of CSR06 - EVBUER Missed Parity 0 err on Add-Cmd bus
 *	bit 4 of CSR06 - EVBUER Parity 0 erro on Add-Cmd bus
 *	bit 1:0  CSR06 - EVBUER Uncorrectable Err 0
 */
#define ESREG_EVB_FATAL_ERR0		  (0xFUL << 4)
/*
 *	bit 3 of CSR04 - EVBCER Missed Uncorrectable Err 0
 *	bit 1:0  CSR04 - EVBCER Uncorrectable Err 0
 */
#define ESREG_EVB_CORR_ERR0	  (0x7UL << 4)

/*
 */
#define ESREG_EVB_FATAL_NORESPONSE	 ((0x1UL << 28) | (0x1UL << 60))

#define ESREG_CB_SUMMARY		(ESREG_CB_SUMMARY0 | ESREG_CB_SUMMARY1)
#define ESREG_IB_SUMMARY		(ESREG_IB_SUMMARY0 | ESREG_IB_SUMMARY1)
#define ESREG_DT_SUMMARY		(ESREG_DT_SUMMARY0 | ESREG_DT_SUMMARY1)

#define ESREG_EVB_CORR_ERR		(ESREG_EVB_CORR_ERR0 | ESREG_EVB_CORR_ERR1)
#define ESREG_EVB_FATAL_ERR		(ESREG_EVB_FATAL_ERR0 | ESREG_EVB_FATAL_ERR1 | \
					 ESREG_EVB_FATAL_NORESPONSE)


#define KN470_CB_ERROR(x)		(x->esreg & (ESREG_CB_SUMMARY))
#define KN470_IB_ERROR(x)		(x->esreg & (ESREG_IB_SUMMARY))
#define KN470_EVB_FATAL_ERROR(x)	(x->esreg & (ESREG_EVB_FATAL_ERR))
#define KN470_EVB_CORR_ERROR(x)		(x->esreg & (ESREG_EVB_CORR_ERR))
#define KN470_DT_ERROR(x)		(x->esreg & (ESREG_DT_SUMMARY))

/*
 * CSR02 - EVBCR CONTROL 
 * The EVB control register configures the Rattler for the EVbus operation.
 * The EVBC register contains control fields to enable and/or disable various
 * functions on the EV5/Mcache module bus.  Also this register has control bits 
 * for the use of diagnotsic code running as system initialization time.
 */


/*
 * CPU CSR25 - System Interrupt Clear register (SIC).
 *
 * The System Interrupt Clear register provides a path for the CPU to clear
 * the edge triggered interrupts from the CBus2 C_ERR_L signal, the SYS_EVENT_L
 * signal, and the interval timer interrupt, CINT_TIM signal.  
 *
 */

/*
 * CBus Error Interrupt Clear -- A read of this register returns the state
 * of the interrupt signal to the processor.  A STQ to this register with a
 * 1 in this bit position will clear the latched C_ERR_L interrupt signal
 * driven to the local CPU.  This interrupt can be masked in the 21064 chip.
 */
#define SICR_NHIC (1UL << 44)	/* CBus2 Node Halt Interrupt Clear */

/*
 * System Event Clear -- A read of this register returns the state of the
 * request signal to the processor.  A STQ to this register witha 1 in this bit
 * position will clear the latched CSYS_EVENT_L interrupt signal driven to the
 * local CPU.  This interrupt can be masked in the 21064 chip.
 */
#define SICR_SEIC (1UL << 40)	/* System Event Clear */

/*
 * Interval Timer Interrupt Clear -- A read of this register returns the state
 * of the interrupt signal to the processor. A STQ to this register with a 1
 * in this bit position will clear the latched CINT_TIM interrupt signal driven
 * to the local CPU.  This interrupt can be masked in the 21064 chip.
 */
#define SICR_ITIC (1UL << 36)	/* Interval Timer Interrupt Clear */


#endif /* KN470_H */
