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
 * @(#)$RCSfile: kn450.h,v $ $Revision: 1.1.12.5 $ (DEC) $Date: 1995/07/19 13:39:40 $
 */

#ifndef KN450_H
#define KN450_H

#include <sys/types.h>
#include <hal/cpuconf.h>


struct kn450_mcheck_control {
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


/*
 * Sable CPU Module CSRS
 *
 * These are CSRs for hardware other than the CPU chip on the CPU module.
 * The CPU module has Backup Cache control logic, Cbus control logic, and
 * interrupt control logic on it.  There is a duplicate tag store to speed
 * up maintaining cache coherency.
 */

struct sable_cpu_csr {
	u_long bcc;	u_long fill_00[3]; /* Backup Cache Control */
	u_long bcce;	u_long fill_01[3]; /* Backup Cache Correctable Error */
	u_long bccea;	u_long fill_02[3]; /* B-Cache Corr Err Address Latch */
	u_long bcue;	u_long fill_03[3]; /* B-Cache Uncorrectable Error */
	u_long bcuea;	u_long fill_04[3]; /* B-Cache Uncorr Err Addr Latch */
	u_long dter;	u_long fill_05[3]; /* Duplicate Tag Error */
	u_long cbctl;	u_long fill_06[3]; /* CBus Control */
	u_long cbe;	u_long fill_07[3]; /* CBus Error */
	u_long cbeal;	u_long fill_08[3]; /* CBus Error Addr Latch low */
	u_long cbeah;	u_long fill_09[3]; /* CBus Error Addr Latch high */
	u_long pmbx;	u_long fill_10[3]; /* Processor Mailbox */
	u_long ipir;	u_long fill_11[3]; /* Inter-Processor Int Request */
	u_long sic;	u_long fill_12[3]; /* System Interrupt Clear */
	u_long adlk;	u_long fill_13[3]; /* Address Lock (LDxL/STxC) */
	u_long madrl;	u_long fill_14[3]; /* CBus Miss Address */
	u_long rev;	u_long fill_15[3]; /* CMIC Revision */
};
typedef struct sable_cpu_csr * sable_cpu_csrp_t;

/*
 * Masks for B-Cache and Duplicate Tag Fields. (see section 4.1 of the
 * 						sable cpu spec)
 *
 * The Sable B-Cache is a direct-mapped physical write-back cache, with a
 * fixed 32 byte (hexaword) block size.  It supports the CBus snooping
 * protocol to allow for a multi processor implementation.
 *
 * Each cache block entry is made up of three storage element arrays.  The
 * control store, which is parity protected, contains the binary flags which
 * indicate whether a particular entry is valid, dirty, and/or shared.  The
 * tag store, which is also parity protected, contains the high order address
 * bits of the data currently stored in that particular cache block entry.
 * The data store, which is EDC protected, contains the cached data.
 * 
 * Control Flags:
 *   VALID	The entry is valid (tag and data are meaningful).
 *   DIRTY	The data store contains an updated copy of its main memory
 *		location.
 *   SHARED	The data store contains a copy of a main memory location which
 *		is also cached by another CBus node.  Writes to this location
 * 		must be write-through to maintain coherency.
 *   PARITY	Contains even parity over the contents of the control store.
 *
 * Tag Store:
 *   Contains the high order address bits <30:20> (<30:22> for 4Mb cache) of
 *   the memory location that currently resides in the cache entry.  Protected
 *   by a parity bit which maintains EVEN parity.  Parity is checked by the
 *   processor during every B-Cache probe cycle, and by the B-Cache controller
 *   during every Cbus2 initiated probe cycle.
 *
 * Data Store:
 *   Contains the actual data of the memory location that is cached.  A cache
 *   entry is made up of 8 longwords, each longword protected by 7 bits of
 *   EDC.  Physically the cache is only 4 longwords wide, so a cache block
 *   consists of 2 consecutive addresses aligned on a 32 byte block boundary.
 *   Error checking is performed whenever the processor hits the cache on a
 *   read and error checking and possibly correcting is performed whenever a
 *   Cbus2 read probe hits dirty, the victimization of a dirty location, or a
 *   masked processor write to a shared location.
 *
 * The B-Cache subsystem is manipulated by two different controllers.  The
 * first is the processor which will probe the taf field and, if hit, will
 * read or write data into the B-Cache.  The behavior of the processor
 * relative to the B-Cache is controlled/monitored by the processor registers
 * biu_stat, biu_addr, fill_addr, biu_ctl, and bc_tag.  The second is the
 * B-Cache controller.  It processes all miss traffic and CBus probe activity.
 * The behavior of the B-Cache controller is determined by the settings of the
 * B-Cache CSRs defined below.
 *
 * There is primary and secondary CSR space.  Primary CSR specs is used by
 * Sable systems, and secondary CSR space is used by Cobra systes.
 */

#define BC_MO	   0x1FFFFUL /* B-Cache Map Offset (PA<21:5>)) */
#define BC_TV	     0xFFFUL /* B-Cache Tag Value (PA<33:22>)*/
#define BC_EDC_WIDTH	   7 /* B-Cache EDC Syndrome Width */
#define BC_EDC	      0x7FUL /* B-Cache EDC Syndrome */
#define BC_CTL	       0x7UL /* B-Cache Control (Shared,Dirty,Valid) */
#define BC_SZ	       0x3UL /* B-Cache Size: 1x=4Mb, 01=1Mb, 00=undefined */

#define DT_O	      0xFFUL /* Dup Tag Store Offset */
#define DT_DV	   0xFFFFFUL /* Dup Tag Store Value */


/* 
 * CPU CSR0 - backup cache control register (BCC). (offset 0)
 *
 * Contains all of the control fields to enable/disable various functions 
 * of the B-Cache -- primarily for diagnostic self test code running at 
 * system initialization time.
 *
 * NOTE: The CPU shall ensure that the state of control flags in the low
 * longword are consistent with control flags in the upper longword by
 * performing quadword writes.
 *
 * Controls the mode of the Backup Cache, for instance whether new entries
 * may be allocated, whether the shared bit should be forced set on fills,
 * whether error checking and error reporting are enabled.  Also has some
 * bits for testing portions of the B-cache hardware.
 *
 * Each half of the CSR is associated with one of two "slices".  Bit masks
 * are defined for bits in the low slice (nameL), the high slice (nameH) 
 * and both slices (name).
 */

/* ********************* Configuration Information ************************* */

/*
 * Cache Size.  Cleared on powerup, set by the console before the cache is
 * enabled.
 *
 *	11 - 4MB Cache
 *	00 - 1MB Cache
 */
#define BCC_CSZL_SHIFT	30
#define BCC_CSZL (BC_SZ << BCC_CSZL_SHIFT) 	/* Cache Size Low */
#define BCC_CSZH_SHIFT	62
#define BCC_CSZH (BC_SZ << BCC_CSZH_SHIFT) 	/* Cache Size High */
#define BCC_CSZ	 (BCC_CSZL | BCC_CSZH)	   	/* Cache Size */

/* stuff to move to include *******/
#define BCUE_PEL    (1UL << 1)		  /* Parity Error Low */
#define BCUE_PEH    (1UL << 33)		  /* Parity Error High */
#define BCUE_MPEL   (1UL << 0)		  /* Missed Parity Error Low */
#define BCUE_MPEH   (1UL << 32L)	  /* Missed Parity Error High */
#define BCUE_UEL    (1UL << 3)		  /* B-Cache Uncorr EDC Error Low */
#define BCUE_UEH    (1UL << 35L)	  /* B-Cache Uncorr EDC Error High */
#define BCUE_MUEL   (1UL << 2)		  /* Missed BCache Uncorr EDC Err Low*/
#define BCUE_MUEH   (1UL << 34L)	  /* Missed BCache Uncorr EDC Error H*/
#define BCUE_ISBCL  (1UL << 17)		  /* B-Cache (1) or CPU (0) Low */
#define BCUE_ISBCH  (1UL << 49L)  	  /* B-Cache (1) or CPU (0) High */
#define BCUE_ERROR(x)	(x->bcue & (BCUE_PEL | BCUE_PEH | BCUE_MPEL | BCUE_MPEH | BCUE_UEL | \
			      BCUE_UEH | BCUE_MUEL | BCUE_MUEH | BCUE_ISBCL | BCUE_ISBCH))


#define BCCE_CEL   (1UL << 3)		 /* Correctable Error Low */
#define BCCE_CEH   (1UL << 35)		 /* Correctable Error High */
#define BCCE_CE	   (BCCE_CEL|BCCE_CEH)	 /* Correctable Error */
#define BCCE_ERROR(x)	(x->bcce & (BCCE_CE))

#define CBE_CANA 	(1UL << 14)		/* Cmd/Addr not acknowledged */
#define CBE_CAPEL 	(1UL << 2)		/* C/A Parity Error LW 2,0 */
#define CBE_CAPEH 	(1UL << 34)		/* C/A Parity Error LW 3,1 */
#define CBE_MCAPEL 	(1UL << 3)		/* Missed C/A Parity Err LW 2,0 */
#define CBE_MCAPEH	(1UL << 35)		/* Missed C/A Parity Err LW 3,1 */
#define CBE_RDPEL	(1UL << 6)		/* Par Err on Read Data, Even LW */
#define CBE_RDPEH 	(1UL << 38)		/* Par Err on Read Data, Odd LW */
#define CBE_MRDPEL 	(1UL << 7)		/* Missed Par Err on Rd D, Even LW */
#define CBE_MRDPEH 	(1UL << 39)		/* Missed Par Err on Rd D, Odd LW */
#define CBE_WDNA 	(1UL << 15)		/* Write Data not acknowledged */
#define CBE_WDPEL 	(1UL << 4)		/* Parity Error on Write Data LW 2,0 */
#define CBE_WDPEH 	(1UL << 36)		/* Parity Error on Write Data LW 3,1 */
#define CBE_MWDPEL 	(1UL << 5)		/* Missed Par Err on Wr D LW 2,0 */
#define CBE_MWDPEH 	(1UL << 37)		/* Missed Par Err on Wr D LW 2,0 */

#define CBE_ERROR(x)	(x->cbe & (CBE_CANA | CBE_CAPEL | CBE_CAPEH | CBE_MCAPEL |	\
 			      CBE_MCAPEH | CBE_RDPEL | CBE_RDPEH | CBE_MRDPEL |	\
 			      CBE_MRDPEH | CBE_WDNA | CBE_WDPEL | CBE_WDPEH |	\
 			      CBE_MWDPEL | CBE_MWDPEH))
/*
 * Duplicate Tag Parity Error
 */
#define DTER_PEL    (1UL << 1)		  /* Dup Tag Parity Error Low */
#define DTER_PEH    (1UL << 33)		  /* Dup Tag Parity Error High */
#define DTER_PE	    (DTER_PEL|DTER_PEH)   /* Dup Tag Parity Error */
 
#define DTER_MPEL   (1UL << 0)		  /* Missed Dup Tag Parity Err Low */
#define DTER_MPEH   (1UL << 32)		  /* Missed Dup Tag Parity Err High */
#define DTER_MPE    (DTER_MPEL|DTER_MPEH) /* Missed Dup Tag Parity Error */

#define DTER_ERRORS	(DTER_PE | DTER_MPE)
#define DTER_ERROR(x)	(x->dter & DTER_PE)

/*
 * CPU CSR12 - System Interrupt Clear register (SIC).
 *
 * The System Interrupt Clear register provides a path for the CPU to clear
 * the edge triggered interrupts from the CBus C_ERR_L signal, the SYS_EVENT_L
 * signal, and the interval timer interrupt, CINT_TIM signal.  The C_ERR_L and
 * SYS_EVENT_L signals are broadcast to both CPU modules.  The interval timer
 * clock is received from the CBus and used to generate an Interval Timer
 * Interrupt to each processor.  The Interval Timer Interrupt is local to each
 * CPU so that this interrupt will occur 180 degrees out of phase with the
 * other processor node.  The system generic SYSTEM EVENT INTERRUPT is
 * generated by an I/O halt request, an Operator Control Panel HALT request,
 * an enclosure event, or a power supply event.  The generic transaction error
 * signal C_ERR_L is generated by soft or hard errors related to data
 * transactions.
 */

/*
 * CBus Error Interrupt Clear -- A read of this register returns the state
 * of the interrupt signal to the processor.  A STQ to this register with a
 * 1 in this bit position will clear the latched C_ERR_L interrupt signal
 * driven to the local CPU.  This interrupt can be masked in the 21064 chip.
 */
#define SIC_EIC	 (1UL << 2)	/* CBus Error Interrupt Clear */

/*
 * Interval Timer Interrupt Clear -- A read of this register returns the state
 * of the interrupt signal to the processor. A STQ to this register with a 1
 * in this bit position will clear the latched CINT_TIM interrupt signal driven
 * to the local CPU.  This interrupt can be masked in the 21064 chip.
 */
#define SIC_ITIC (1UL << 32)	/* Interval Timer Interrupt Clear */

/*
 * System Event Clear -- A read of this register returns the state of the
 * request signal to the processor.  A STQ to this register witha 1 in this bit
 * position will clear the latched CSYS_EVENT_L interrupt signal driven to the
 * local CPU.  This interrupt can be masked in the 21064 chip.
 */
#define SIC_SEIC (1UL << 33)	/* System Event Clear */


#endif /* KN450_H */
