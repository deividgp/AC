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
 * @(#)$RCSfile: ruby_common.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1995/04/28 18:34:17 $
 */
#ifndef _RUBY_COMMON_H
#define _RUBY_COMMON_H

#include <hal/cpuconf.h>

/*
 * Ruby Machine check handler control structure.  The in_mcheck field is a
 * flag to catch software double machine checks.  The mcheck_ok and
 * badaddr_count fields are used to suppress logging of machine checks
 * during bad address probes.  The lgt field points to a VA which is mapped
 * to the physical address of the logout area.  The lgt_copy field points to
 * a page which is used to buffer copies of logout frames while they are
 * being logged.  The next_copy and copy_in_use[] fields are used to keep
 * track of logout frame copies in the lgt_copy area.  Note that the
 * lgt_copy stuff can go away when we get rid of dump_mcheck_frame.
 */
#define LGT_COPY_SIZE 8192
#define LGT_COPIES 8
 

/* 
 * this is a per-cpu data structure for tracking machine check 
 * error handing
 */

struct kn7aa_error_counters {	/* this is a copy of */
				/* elr_error_counters, so that */
				/* errlog.h doesn't need to be */
				/* included here. */
	char error_counters[96];
};

struct ruby_mcheck_control {
	/* this is a per-cpu data structure for tracking machine check */
	/* error handing */

	/* The following set of structure elements are used for */
	/* intentional machine checks, such as those cause by BADADDR, */
	/* or probing. */
	u_int mcheck_expected;		/* flag: we're probing. */
	memtest_t mcheck_tp_active;	/* flag: testpage in progress */
	u_int mcheck_occured;		/* Number of mchecks during probe. */
	u_int mcheck_action;		/* What action to take with this mcheck, recover, crash, retry */
	u_int mcheck_retry;		/* Logout frames retry bit */	
	long  mcheck_return;		/* return to this PC expected mchecks */
	long  mcheck_page;		/* page we're testing. */

	u_long mctl_probe_va;		/* VA being probed. */

	/* This next set of elements are used to describe the machine */
	/* check frame, built by PAL, and used in error parsing. */
        struct ruby_mchk_logout
		*mctl_lgt_va;		/* VA of PAL's mcheck logout area */
	u_long mctl_lgt_pa;		/* PA ... */
	u_long mctl_lgt_len;		/* size of logout area */
	u_long mctl_vector;		/* SCB Vector from PAL. */

	long *mctl_regs;		/* ptr to registers saved by */
					/* _XentInt before calling */
					/* machine check routine. */

	/* The next set of elements are used to maintain a running */
	/* count of error flags found set in the elr_soft_flags */
	/* structure returned from each error parse. These values */
	/* start at 0 at system boot time. */


	struct kn7aa_error_counters error_670_counters;
	struct kn7aa_error_counters error_660_counters;
	struct kn7aa_error_counters error_630_counters;
	struct kn7aa_error_counters error_620_counters;

#if MCHECK_BUFFER
	/* this set is used when there is machine check frame copied */
	/* from the PAL's. */
	struct ruby_mchk_logout
		*mctl_lgt_copy;		/* Buffer to hold copies of logout */
	long mctl_next_copy;		/* Number of next copy */
#endif /* MCHECK_BUFFER */

	/*
	 * Fields for maintaining error logger scratch buffer.
	 */
	struct ruby_mcheck_control_elbuf {
		char	    elctl_buf[NBPG];	/* Error logging scratch buffer. */
		u_long 	    elctl_len;		/* Length of scratch buffer. */
		caddr_t	    elctl_ptr;		/* Pointer to first free in */
						/* scratch buffer. */
		u_long      elctl_rmng;		/* Remaining room in scratch buffer. */
	} mctl_elctl;


	struct ruby_error_ctl_frames {
		struct elr_soft_flags *soft_flags; 
						/* ptr to software */
						/* flags portion of */
						/* error log packet */
		/* pointers to allocated space for... */
		struct elr_lep_common_header *lep_cmn_hdr;
		struct elr_lep_670_frame *lep_670_frame;
		struct elr_pal_rev *pal_rev;
		struct elr_dlist *dlist;
		struct elr_lsb *lsb;
		struct elr_lma *lma;
		struct elr_adp *adp;
	} mctl_efctl;

#if MCHECK_BUFFER
	int mctl_copy_in_use[LGT_COPIES];
#endif /* MCHECK_BUFFER */

};

#if NCPUS > 1
extern struct ruby_mcheck_control Ruby_mcheck_control[NCPUS];
#define MCHECK_CONTROL(cpu_id) &Ruby_mcheck_control[cpu_id]
#else /* NCPUS <= 1 */
extern struct ruby_mcheck_control Ruby_mcheck_control;
#define MCHECK_CONTROL(cpu_id) &Ruby_mcheck_control
#endif /* NCPUS <= 1 */


#define RETRY_BIT	0x1000000000000000	/* Retry bit in the top word */
						/* of Mcheck frame	*/
/* Watch chip csra structure def */

typedef union watch_csra {
  unsigned char reg;
  unsigned char rega;
  struct csra_bits {
    unsigned char rs: 4;
    unsigned char dv: 3;
    unsigned char uip: 1;
  } csra_bits;
} watch_csra;

/* Watch chip csra bit/field defs within the byte */

#define WATCH_CSRA_V_RS  0x000	/* Rate Select                 */
#define WATCH_CSRA_S_RS  0x004
#define WATCH_CSRA_M_RS  0x00F
#define WATCH_CSRA_K_RS  0x006  /* HW Group says set to 0b0110 */

#define WATCH_CSRA_V_DV  0x004	/* Divider select                 */
#define WATCH_CSRA_S_DV  0x003
#define WATCH_CSRA_M_DV  0x070
#define WATCH_CSRA_K_DV  0x020	/* expect Console to set to 0b010 */

#define WATCH_CSRA_V_UIP 0x007  /* Update in progress */
#define WATCH_CSRA_S_UIP 0x001	/* Read Only field    */
#define WATCH_CSRA_M_UIP 0x080

#define WATCH_CSRA_SET   0x026	/* This setting makes the clock run at */
				/* realtime. i.e. It agrees with the   */
				/* clock on the wall                   */

/* Watch chip csra defs within structure field definitions */

#define WATCH_CSRA_RS_SET 0b0110/* The meaning of this 4 bit field is */
				/* dependant upon the setting of the  */
				/* DV field. See LEP spec.            */

#define WATCH_CSRA_DV_SET 0b010	/* This sets the clock divider to */
				/* ~32kHz. As specified by the */
				/* hardware group */

/* Watch chip csrb structure def */

typedef union watch_csrb {
  unsigned char reg;
  unsigned char regb;
  struct csrb_bits {
    unsigned char dse: 1;
    unsigned char mlt: 1;  
    unsigned char dm: 1;
    unsigned char sqwe: 1;
    unsigned char uie: 1;
    unsigned char aie: 1;
    unsigned char pie: 1;
    unsigned char vset: 1;
  } csrb_bits;
} watch_csrb;

/* Watch chip csrb bit/field defs within the byte */

#define WATCH_CSRB_V_DSE 0x000  /* Daylight Savings time */
#define WATCH_CSRB_S_DSE 0x001
#define WATCH_CSRB_M_DSE 0x001
#define WATCH_CSRB_K_DSE 0x000  /* We want this off! - 00 */

#define WATCH_CSRB_V_HM 0x001	/* Hour Mode: 0 = am/pm, 1 = 24hr */ 
#define WATCH_CSRB_S_HM 0x001
#define WATCH_CSRB_M_HM 0x002
#define WATCH_CSRB_K_HM 0x002	/* Want 24 hour mode */

#define WATCH_CSRB_V_DM 0x002	/* Data Mode: 0 = BCD, 1 = binary */ 
#define WATCH_CSRB_S_DM 0x001
#define WATCH_CSRB_M_DM 0x004
#define WATCH_CSRB_K_DM 0x004	/* We want this set */

#define WATCH_CSRB_V_SQWE 0x003	/* Square Wave Interrupt enable */ 
#define WATCH_CSRB_S_SQWE 0x001
#define WATCH_CSRB_M_SQWE 0x008
#define WATCH_CSRB_K_SQWE 0x008	/* expect console to set this */

#define WATCH_CSRB_V_UIE 0x004	/* Update ended Interrupt enable   */ 
#define WATCH_CSRB_S_UIE 0x001
#define WATCH_CSRB_M_UIE 0x010
#define WATCH_CSRB_K_UIE 0x000	/* dont want this */

#define WATCH_CSRB_V_AIE 0x005	/* Alarm Interrupt enable   */ 
#define WATCH_CSRB_S_AIE 0x001
#define WATCH_CSRB_M_AIE 0x020
#define WATCH_CSRB_K_AIE 0x000	/* dont want this */

#define WATCH_CSRB_V_PIE 0x006	/* Periodic Interrupt enable   */ 
#define WATCH_CSRB_S_PIE 0x001
#define WATCH_CSRB_M_PIE 0x040
#define WATCH_CSRB_K_PIE 0x040	/* expect console to set this */

#define WATCH_CSRB_V_SET 0x007	/* Set mode */
#define WATCH_CSRB_S_SET 0x001
#define WATCH_CSRB_M_SET 0x080

#define WATCH_CSRB_SET 0x04E	/* what we would like to see in csrb */

/* Watch chip csrc structure def */

typedef union watch_csrc {
  unsigned char reg;
  unsigned char regc;
  struct csrc_bits {
    unsigned char rsvd: 3;  
    unsigned char uf: 1;  
    unsigned char af: 1;  
    unsigned char pf: 1;  
    unsigned char irqf: 1;  
  } csrc_bits;
} watch_csrc;

/* Watch chip csrc bit/field defs within the byte */

#define WATCH_CSRC_SET 0x000  /* expect to be... */

/* Watch chip csrd structure def */

typedef union watch_csrd {
  unsigned char reg;
  unsigned char regd;
  struct csrd_bits {
    unsigned char rsvd: 7;
    unsigned char vrt: 1;  
  } csrd_bits;
} watch_csrd;

#define csrd_vrt csrd.csrd_bits.vrt

/* Watch chip csrd bit/field defs within the byte */

#define WATCH_CSRD_V_VRT 0x008	/* Valid Ram Time Indicates the */
#define WATCH_CSRD_S_VRT 0x001	/* contents of the watch have been */
#define WATCH_CSRD_M_VRT 0x080	/* maintained since set. (Not */
				/* necessarily correct)       */
#define WATCH_CSRD_K_VRT 0x080  /* expect to be... */

#define WATCH_CSRD_SET 0x080  /* expect to be... */

/* Watch chip structure def */

struct gbus_watch {
  unsigned char seconds;
  char fill1[0x7F];
  unsigned char minutes;
  char fill2[0x7F];
  unsigned char hours;
  char fill3[0xBF];
  unsigned char day;
  char fill4[0x3F];
  unsigned char month;
  char fill5[0x3F];
  unsigned char year;
  char fill6[0x3F];
  watch_csra csra;
  char fill7[0x3F];
  watch_csrb csrb;
  char fill8[0x3F];
  watch_csrc csrc;
  char fill9[0x3F];
  watch_csrd csrd;
};

struct gbus_misc {
  unsigned char whami;
  char fill1[0x3F];
  unsigned char leds;
  char fill2[0x3F];
  unsigned char pmask;
  char fill3[0x3F];
  unsigned char intr;
  char fill4[0x3F];
  unsigned char halt;
  char fill5[0x3F];
  unsigned char lsbrst;
};

/*
 * define gbus structures and constants...
 */

struct gbus_map {
  struct gbus_uart *uart0; 
  struct gbus_uart *uart1;
  struct gbus_uart *uart2;
  struct gbus_watch *watch;
  struct gbus_misc *misc;
};

struct gbus_uart_foo {
  vm_offset_t reg;
};


/* GBUS offsets into mapped pages... */
#define GBUS_UART0A_PG_OFFSET 0x80

#define GBUS_UART_TxEM 0x02

/* Define all UART ports */
#define UART0A 0x1
#define UART0B 0x2
#define UART1A 0x3
#define UART1B 0x4
#define UART2A 0x5
#define UART2B 0x6

/* Define UART ports used */
#define UART_LOCAL UART0A
#define UART_PS UART1B
#define UART_P UART2A

/*
 * define gbus uart register secondary access indexes
 */
#define WR0 0

#define WR1 1
#define WR2 2 
#define WR3 3 
#define WR4 4 
#define WR5 5 
#define WR6 6
#define WR7 7

#define WR8_OFFSET 0x40
#define WR8 8

#define WR9  WR8 + 1
#define WR10 WR8 + 2
#define WR11 WR8 + 3
#define WR12 WR8 + 4
#define WR13 WR8 + 5
#define WR14 WR8 + 6
#define WR15 WR8 + 7

#define RR0  0
#define RR1  1
#define RR2  2 
#define RR3  3 

#define RR8_OFFSET 0x40

#define RR8  8
#define RR10 10
#define RR13 13
#define RR15 15

#define UART_TXINTENA 2
#define UART_RXINTENA 16

struct gbus_uart {
  union {
    unsigned char uart_wr0;
    unsigned char uart_wr1;
    unsigned char uart_wr2;
    unsigned char uart_wr3;
    unsigned char uart_wr4;
    unsigned char uart_wr5;
    unsigned char uart_wr6;
    unsigned char uart_wr7;

    unsigned char uart_rr0;
    unsigned char uart_rr1;
    unsigned char uart_rr2;
    unsigned char uart_rr3;
  } gu1;
  char uart_fill[0x3F]; /* unused IO space between DUART registers */
  union {
    unsigned char uart_wr8;
    unsigned char uart_wr9;
    unsigned char uart_wr10;
    unsigned char uart_wr11;
    unsigned char uart_wr12;
    unsigned char uart_wr13;
    unsigned char uart_wr14;
    unsigned char uart_wr15;

    unsigned char uart_rr8;
    unsigned char uart_rr10;
    unsigned char uart_rr13;
    unsigned char uart_rr15;
  } gu2;
};
    
/*
 * This will return physical address of the given lsb node number.
 * Each lsb node space is 4mb in length
*/
extern	u_long	lsb_start_phys;
#define RUBY_NEXADDR(lsbnode)  (lsb_start_phys + ((long)lsbnode * 0x400000))
                                                             
#endif _RUBY_COMMON_H

