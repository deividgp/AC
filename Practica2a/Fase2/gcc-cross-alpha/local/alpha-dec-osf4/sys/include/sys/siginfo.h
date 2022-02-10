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
 * @(#)$RCSfile: siginfo.h,v $ $Revision: 1.1.24.3 $ (DEC) $Date: 1997/05/01 21:57:53 $"
 */

#ifndef _SYS_SIGINFO_H
#define _SYS_SIGINFO_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/sysmisc.h> /* for sigval; gets types.h */

#if defined(_OSF_SOURCE) || ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) ) || defined(_XOPEN_SOURCE_EXTENDED) 

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

/*
 * Max siginfo size -- 128 bytes altogether (used to pad siginfo _sifields)
 */
#define SI_MAX_SIZE	(128)
#define SI_PAD_SIZE ((SI_MAX_SIZE/sizeof(int)) - 4)

#ifndef _XOPEN_SOURCE_EXTENDED
typedef struct siginfo {
#else
typedef struct {
#endif
	int si_signo;	/* signal number */
	int si_errno;	/* error number */
	int si_code;	/* signal code */

	union {
		int _sipad[SI_PAD_SIZE]; /* reserve space for new fields */

		/* kill() or SIGCHLD */
		struct {
			pid_t	_pid;			/* sender's pid */
			union {
				/* kill() */
				struct {
					uid_t	_uid;	/* sender's uid */
				} _kill;

				/* SIGCHLD */
				struct {
					int	_status; /* exitcode/signal */
					clock_t _utime;
					clock_t _stime;
				} _sigchld;
			} _pinfo;
			/* POSIX.1b signals */
			struct {
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 
				/* application-defined value */
				sigval_t _sigval;
#else
				long	_sigval;
#endif /* _POSIX_C_SOURCE */
			} _sigrt;
		} _sigproc;

		/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
		struct {
#ifdef _XOPEN_SOURCE_EXTENDED
			void 	*_addr;
#else
			caddr_t	_addr;	/* faulting instruction/memory ref. */
#endif
		} _sigfault;


		/* SIGPOLL */
		struct {
			long	_band;	/* POLL_IN, POLL_OUT, POLL_MSG */
			/* fd not currently available for SIGPOLL */
			int	_fd;	/* file descriptor */
		} _sigpoll;

		/* ANON2 */
		struct {
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 
 			sigval_t _siganonval;
#else
			long _siganonval;
#endif /* _POSIX_C_SOURCE */
		} _siganon;
	} _sifields;
} siginfo_t;
#endif /* defined(__LANGUAGE_C__) || defined(__cplusplus) */

/*
 * This is how users expect to access these fields.
 */
#define si_pid	       _sifields._sigproc._pid
#define si_uid	       _sifields._sigproc._pinfo._kill._uid
#define si_status      _sifields._sigproc._pinfo._sigchld._status
#define si_utime       _sifields._sigproc._pinfo._sigchld._utime
#define si_stime       _sifields._sigproc._pinfo._sigchld._stime
#define si_value       _sifields._sigproc._sigrt._sigval
#define si_int	       _sifields._sigproc._sigrt._sigval.sival_int
#define si_ptr	       _sifields._sigproc._sigrt._sigval.sival_ptr
#define si_addr	       _sifields._sigfault._addr
#define si_band	       _sifields._sigpoll._band
#define si_fd	       _sifields._sigpoll._fd
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 
#define si_anonval     _sifields._siganon._siganonval
#define si_anonint     _sifields._siganon._siganonval.sival_int
#define si_anonptr     _sifields._siganon._siganonval.sival_ptr
#endif /* _POSIX_C_SOURCE */


/**************************************************************************
			si_code values
**************************************************************************/

/* negative si_codes are reserved for user-generated signals */
#define SI_QUEUE	-1	/* sent by sigqueue */
#define SI_USER		0	/* sent by kill, sigsend, raise, etc. */
#define SI_NOINFO	1	/* unknown source */
#define SI_TIMER	0x10	/* sent by timer expiration */
#define SI_ASYNCIO	0x20	/* sent by AIO completion */
#define SI_MESGQ	0x40	/* sent by realtime mesq state transition */

#define SI_FROMUSER(siptr)	((siptr)->si_code <= 0)
#define SI_FROMKERNEL(siptr)	((siptr)->si_code > 0)

/*
 * SIGILL si_codes 
 */
#define ILL_ILLOPC	1	/* illegal opcode */
#define ILL_ILLOPN	2	/* illegal operand */
#define ILL_ILLADR	3	/* illegal addressing mode */
#define ILL_ILLTRP	4	/* illegal trap */
#define ILL_PRVOPC	5	/* privileged opcode */
#define ILL_PRVREG	6	/* privileged register */
#define ILL_COPROC	7	/* coprocessor error */
#define ILL_BADSTK	8	/* internal stack error */
#ifndef _XOPEN_SOURCE_EXTENDED
#define NSIGILL		8
#endif

/*
 * SIGFPE si_codes
 */
#define FPE_INTDIV	1	/* integer divide by zero */
#define FPE_INTOVF	2	/* integer overflow */
#define FPE_FLTDIV	3	/* floating point divide by zero */
#define FPE_FLTOVF	4	/* floating point overflow */
#define FPE_FLTUND	5	/* floating point underflow */
#define FPE_FLTRES	6	/* floating point inexact result */
#define FPE_FLTINV	7	/* invalid floating point operation */
#define FPE_FLTSUB	8	/* subscript out of range */
#ifndef _XOPEN_SOURCE_EXTENDED
#define NSIGFPE		8
#endif

/*
 * SIGSEGV si_codes
 */
#define SEGV_MAPERR	1	/* address not mapped to object */
#define SEGV_ACCERR	2	/* invalid permissions for mapped object */
#ifndef _XOPEN_SOURCE_EXTENDED
#define NSIGSEGV	2
#endif

/* 
 * SIGBUS si_codes
 */
#define BUS_ADRALN	1	/* invalid address alignment */
#define BUS_ADRERR	2	/* non-existent physical address */
#define BUS_OBJERR	3	/* object specific hardware error */
#ifndef _XOPEN_SOURCE_EXTENDED
#define NSIGBUS		3
#endif

/*
 * SIGTRAP si_codes
 */
#define TRAP_BRKPT	1	/* process breakpoint */
#define TRAP_TRACE	2	/* process trace trap */
#ifndef _XOPEN_SOURCE_EXTENDED
#define NSIGTRAP	2
#endif

/*
 * SIGCHLD si_codes
 */
#define CLD_EXITED	1	/* child has exited */
#define CLD_KILLED	2	/* child was killed */
#define CLD_DUMPED	3	/* child terminated abnormally */
#define CLD_TRAPPED	4	/* traced child has trapped */
#define CLD_STOPPED	5	/* child has stopped */
#define CLD_CONTINUED	6	/* stopped child has continued */
#define CLD_SIGEXITING	7	/* child is exiting via a fatal signal */
#ifndef _XOPEN_SOURCE_EXTENDED
#define NSIGCLD		7
#endif

/*
 * SIGPOLL si_codes
 */
#define POLL_IN		1	/* data input available */
#define POLL_OUT	2	/* output buffers available */
#define POLL_MSG	3	/* input message available */
#define POLL_ERR	4	/* I/O error */
#define POLL_PRI	5	/* high priority input available */
#define POLL_HUP	6	/* device disconnected */
#ifndef _XOPEN_SOURCE_EXTENDED
#define NSIGPOLL	6
#endif

/**************************************************************************
			end si_code values
**************************************************************************/

#endif /* _OSF_SOURCE || _POSIX_C_SOURCE || _XOPEN_SOURCE_EXTENED */

#ifdef _KERNEL

#ifndef ASSEMBLER

#include <kern/queue.h>

/*
 * Define kernel version of siginfo with no padding for growth.
 * Copy into user siginfo structure when copying into user space.
 */
typedef struct k_siginfo {
	int si_signo;	/* signal number */
	int si_errno;	/* error number */
	int si_code;	/* signal code */
	int si_kflags;	/* reserved flags field */

	union {
		/* kill() or SIGCHLD */
		struct {
			pid_t	_pid;			/* child's pid */
			union {
				/* kill()/ sigqueue() */
				struct {
					uid_t	_uid;	/* sender's uid */
					pid_t 	_pidgen;
				} _kill;

				/* SIGCHLD */
				struct {
					int	_status; /* exitcode/signal */
					clock_t _utime;
					clock_t _stime;
				} _sigchld;

				/* POSIX.1b timers */
				struct {
					unsigned int _timer1;
					unsigned int _timer2;
				} _sigtimer;
			} _pinfo;

			/* POSIX.1b signals */
			struct {
				/* application-defined value */
				sigval_t _sigval;
			} _sigrt;
		} _sigproc;

		/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
		struct {
			caddr_t	_addr;	/* faulting instruction/memory ref. */
		} _sigfault;

		/* SIGPOLL */
		struct {
			long	_band;	/* POLL_IN, POLL_OUT, POLL_MSG */
			/* fd not currently available for SIGPOLL */
			int	_fd;	/* file descriptor */
		} _sigpoll;

		/* ANON */
		struct {
			sigval_t _siganon;
		} _siganon;

	} _sifields;
} k_siginfo_t;

#define si_uid	       _sifields._sigproc._pinfo._kill._uid
#define si_pidgen      _sifields._sigproc._pinfo._kill._pidgen
#define si_timer1      _sifields._sigproc._pinfo._sigtimer._timer1
#define si_timer2      _sifields._sigproc._pinfo._sigtimer._timer2

/*
 * Structure for queuing siginfo data.
 */
typedef struct sigqueue_struct {
	queue_chain_t	sigqueue_list;
	k_siginfo_t	siginfo;
} *sigqueue_t;


/*
 * Allocate a signal queue entry. The xsleep flags tells us
 * whether we can block or not. We should *never* have
 * to do this at interrupt level.
 */
#define SIGQ_ALLOC(sqp, xsleep)			      			\
	if (xsleep) 							\
		MALLOC((sqp),sigqueue_t,sizeof(struct sigqueue_struct),	\
		       M_SIGQ,M_WAITOK);				\
	else  								\
		MALLOC((sqp),sigqueue_t,sizeof(struct sigqueue_struct),	\
		       M_SIGQ,M_NOWAIT)

#define SIGQ_FREE(xqp)							\
MACRO_BEGIN								\
	if (xqp) {							\
		if ((xqp)->siginfo.si_kflags & SQ_ABORT)		\
			wakeup((xqp));					\
		if ((xqp)->siginfo.si_kflags & SQ_FREE)			\
			FREE((xqp), M_SIGQ);				\
		(xqp) = NULL;						\
	}								\
MACRO_END

/*
 * kernel macros and routines
 */

/* Like sigq_remove_all, but no quota checks, no locking assumed. */
#define sigq_clear_queue(xq) 						\
MACRO_BEGIN								\
	register sigqueue_t tmpq;					\
	while (tmpq = (sigqueue_t) dequeue_head((xq))) {		\
		tmpq->siginfo.si_kflags &= ~SQ_INQ;			\
		if (tmpq->siginfo.si_kflags & SQ_FREE)			\
			FREE(tmpq, M_SIGQ);				\
	}								\
MACRO_END

#define sigq_find_sig(q, sig) \
	sigq_find_next_sig((q), (sigqueue_t) queue_first((q)), (sig))
#define sigq_dequeue(q, qp) \
	queue_remove((q), (qp), sigqueue_t, sigqueue_list)

#define ALL_SIGQ_SIGS	(-1)

extern k_siginfo_t zero_ksiginfo;

#define SQ_RESV		0x1	/* entry is on reserved queue */
#define SQ_OWN		0x2	/* entry is owned by the caller */
#define SQ_FREE		0X4	/* free me when done */
#define SQ_POST		0x8	/* in process of posting */
#define SQ_INQ		0x10	/* entry is pending and queued */
#define	SQ_PEND		0x20	/* signal is still pending after this entry */
#define SQ_MUSTQ 	0x40	/* queue without checking p_siginfo */
#define SQ_ITIMER	0x80	/* entry is an interval timer */
#define SQ_QUOTA	0x100	/* credit quota on posting */
#define SQ_ABORT	0x200	/* signal abort request */
#define SQ_UAST		0x400	/* post user-mode ast */

#define SIP_TO_SQP(xsip) \
	((sigqueue_t)((char *)(xsip) - (int) &((sigqueue_t)0)->siginfo))

/*
 * Look for another siginfo for this type signal.
 * If the signal entry dequeued is not the last
 * of that type in the queue, the SQ_PEND flag
 * is set in the flags field of the entry returned.
 */
#define SIGQ_DEQUEUE( xq, xsig, xqp )					\
MACRO_BEGIN								\
	xqp = sigq_find_sig((xq), (xsig));				\
	if ((xqp)) {							\
		sigq_dequeue((xq), (xqp));				\
		(xqp)->siginfo.si_kflags &= ~SQ_INQ; 			\
		(xqp)->siginfo.si_kflags |= SQ_POST; 			\
	} 								\
MACRO_END

#endif /* _KERNEL */

#endif /* ASSEMBLER */

#if defined(__cplusplus)
}
#endif
#endif	/* _SYS_SIGINFO_H */
