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
 *	@(#)$RCSfile: tty.h,v $ $Revision: 4.3.22.2 $ (DEC) $Date: 1995/06/03 23:16:56 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_TTY_H_
#define _SYS_TTY_H_

#include <sys/types.h>
#include <sys/ioctl.h>		/* for struct winsize */
#include <sys/termios.h>

#ifdef _KERNEL
#include <kern/queue.h>
#include <tty/tty_common.h>
#endif

#ifdef _KERNEL
/* Some useful instruments */
enum csize {                            /* bits per character */
    bits5, bits6, bits7, bits8};
enum parity {                           /* parity */
    nopar, oddpar, markpar, evenpar, spacepar};
enum stopbits {                         /* stop bits */
    stop1, stop2};
enum status {
    good_char, overrun, parity_error, framing_error, break_interrupt,
    cts_on, cts_off, dsr_on, dsr_off, ri_on, ri_off, cd_on, cd_off,
    cblock_buf, other_buf};

typedef unsigned int baud_t;
typedef int csize_t;
typedef int parity_t;
typedef int stop_t;


/*
 * A clist structure is the head of a linked list queue
 * of characters.  The characters are stored in blocks
 * containing a link and CBSIZE (param.h) characters.
 * The routines in tty_subr.c manipulate these structures.
 */
struct clist {
	int	c_cc;		/* character count */
	char	*c_cf;		/* pointer to first char */
	char	*c_cl;		/* pointer to last char */
};

/*
 * Per-tty structure.
 *
 * Should be split in two, into device and tty drivers.
 * Glue could be masks of what to echo and circular buffer
 * (low, high, timeout).
 */
struct tty {
	struct	clist t_rawq;
	struct	clist t_canq;
	struct	clist t_outq;		/* device */
	int	(*t_oproc)();		/* driver's start routine */
	int	(*t_param)();		/*  " param routine */
	int	(*t_hflow)();		/*  " hardware flow control routine */
	struct	queue_entry t_selq;	/* Queue of waiting threads	*/
	caddr_t	T_LINEP;		/* ### */
	caddr_t	t_addr;			/* ??? */
	caddr_t t_language;             /* local language hook */
	dev_t	t_dev;			/* device */
	int	t_flags;		/* (compat) some of both */
	int	t_state;		/* some of both */
	int	t_gen;			/* generation number */
 	struct	session *t_session;	/* tty */
 	struct	pgrp *t_pgrp;		/* foreground process group */
	char	t_line;			/* glue */
	char	t_col;			/* tty */
	char	t_rocount, t_rocol;	/* tty */
 	short	t_hiwat;		/* hi water mark */
 	short	t_lowat;		/* low water mark */
	short	t_hog;			/* hi water mark for input */
	struct	winsize t_winsize;	/* window size */
 	struct	termios t_termios;	/* termios state */
#define	t_iflag		t_termios.c_iflag
#define	t_oflag		t_termios.c_oflag
#define	t_cflag		t_termios.c_cflag
#define	t_lflag		t_termios.c_lflag
#define	t_min		t_termios.c_cc[VMIN]
#define	t_time		t_termios.c_cc[VTIME]
#define	t_cc		t_termios.c_cc
#define t_ispeed	t_termios.c_ispeed
#define t_ospeed	t_termios.c_ospeed
 	long	t_cancc;		/* stats */
 	long	t_rawcc;
 	long	t_outcc;
	long    t_shad_time;            /* Value of t_cc[VTIME] in ticks */
};
#endif /* _KERNEL */

#define TTIPRI	28
#define TTOPRI	29

/* limits */
#define	NSPEEDS	16
#define TTMASK	15
#define OBUFSIZ	100
#define TTYHOG	255

#ifdef	_KERNEL
/*
 * Since we allow both interrupt and thread based tty drivers in MP kernel, 
 * spl's must always be used.
 */
#define	TSPLVAR(s)	int s;
#define	TSPLTTY(s)	s = spltty()
#define	TSPLX(s)	splx(s)

#define TTMAXHIWAT	roundup(2048, CBSIZE)
#define TTMINHIWAT	roundup(100, CBSIZE)
#define TTMAXLOWAT	256
#define TTMINLOWAT	32

extern	struct ttychars ttydefaults;
#endif	/* _KERNEL */

/* internal state bits */
#define TS_TIMEOUT	0x000001	/* delay timeout in progress */
#define TS_WOPEN	0x000002	/* waiting for open to complete */
#define TS_ISOPEN	0x000004	/* device is open */
#define TS_FLUSH	0x000008	/* outq has been flushed during DMA */
#define TS_CARR_ON	0x000010	/* software copy of carrier-present */
#define TS_BUSY		0x000020	/* output in progress */
#define TS_ASLEEP	0x000040	/* wakeup when output done */
#define TS_XCLUDE	0x000080	/* exclusive-use flag against open */
#define TS_TTSTOP	0x000100	/* output stopped by ctl-s */
#define TS_HUPCLS	0x000200	/* hang up upon last close */
#define TS_TBLOCK	0x000400	/* tandem queue blocked */
#define TS_NBIO		0x002000	/* tty in non-blocking mode */
#define TS_ASYNC	0x004000	/* tty in async i/o mode */
#define TS_ONDELAY	0x008000	/* device is open; software copy of
 					 * carrier is not present */
#define TS_MODEM_ON     0x400000        /* CLOCAL changed from 1 to 0 (modem) */
#define	TS_CLOSING	0x800000	/* closing down line */
#define TS_INUSE	0x1000000	/* line is in use */
#define TS_NOFLOWCHARS  0x2000000       /* don't send START/STOP chars (lat) */
#define TS_DRAIN_CL     0x4000000       /* Line Disc. is in draining on close */
#define TS_NEED_PARAM  0x20000000	/* param routine needs to be called */
#ifdef	sun
#define TS_OUT          0x010000        /* tty in use for dialout only */
					/* NOTE: This was 0x008000 in
						 Sun Unix */
#endif
/* state for intra-line fancy editing work */
#define TS_BKSL		0x010000	/* state for lowercase \ work */
#define TS_ERASE	0x040000	/* within a \.../ for PRTRUB */
#define TS_LNCH		0x080000	/* next character is literal */
#define TS_TYPEN	0x100000	/* retyping suspended input (PENDIN) */
#define TS_CNTTB	0x200000	/* counting tab width, leave FLUSHO alone */

#define TS_INTIMEOUT    0x2000000       /* A input timeout is active. */

#define	TS_LOCAL	(TS_BKSL|TS_ERASE|TS_LNCH|TS_TYPEN|TS_CNTTB)


/* define partab character types */
#define ORDINARY	0
#define CONTROL		1
#define BACKSPACE	2
#define NEWLINE		3
#define TAB		4
#define VTAB		5
#define RETURN		6
#define FF              7

/*
 * Flags on character passed to ttyinput
 */
#define TTY_CHARMASK    0x000000ff      /* Character mask */
#define TTY_QUOTE       0x00000100      /* Character quoted */
#define TTY_ERRORMASK   0xff000000      /* Error mask */
#define TTY_FE          0x01000000      /* Framing error or BREAK condition */
#define TTY_PE          0x02000000      /* Parity error */

#define ISCTTY          isctty
#define ISBACKGROUND    isbackground

/*
 * Modem control commands (driver).
 */
#define	DMSET		0
#define	DMBIS		1
#define	DMBIC		2
#define	DMGET		3

#ifdef	_KERNEL
#define TCDEVSW_STOP(m,t,w,r)	(r) = (*cdevsw[(m)].d_stop)(t,w)	
#define	TTY_LOCK(tp)
#define	TTY_UNLOCK(tp)
#define	TTY_LOCK_TRY(tp)	1
#define TTY_LOCK_HOLDER(tp)	1
#define TTY_LOCK_ADDR(tp)	((lock_t)0)
#define TTY_SMP(tp)		0
#define TTY_LASSERT(tp, clause)
extern int ttysleep(), ttysleep_tmo();
#endif	/* _KERNEL */

#endif	/* _SYS_TTY_H_ */
