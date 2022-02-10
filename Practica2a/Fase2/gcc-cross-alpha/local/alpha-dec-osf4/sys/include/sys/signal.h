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
 *	@(#)$RCSfile: signal.h,v $ $Revision: 4.3.59.4 $ (DEC) $Date: 1999/01/13 20:21:48 $
 */

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: SYSPROC - signal.h
 *                                                                    
 *
 * Copyright International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 */                                                                   

#ifndef _SYS_SIGNAL_H_
#define _SYS_SIGNAL_H_
#if defined(__cplusplus)
extern "C"
{
#endif

#include <standards.h>
#include <sys/siginfo.h>
#include <sys/sysmisc.h>

/*
 *
 *      The ANSI standard requires that certain values be in signal.h.
 *	The ANSI standard allows additional signals and pointers to 
 *	undeclarable functions with macro definitions beginning with
 * 	the letters SIG or SIG_ and an upper case letter.
 *      However, it also requires that if _ANSI_C_SOURCE is defined then 
 *      no other function definitions are present
 *
 *      This header includes all the ANSI required entries.  In addition
 *      other entries for the OSF system are included.
 *
 */

#ifdef _ANSI_C_SOURCE
#if !defined(_KERNEL) && (defined(__LANGUAGE_C__) || defined(__cplusplus))
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define signal(__a,__b) _Esignal(__a,__b)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern void (*__R(signal) __((int, void (*)(int)))) __((int));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int raise __((int));
# endif /* !_KERNEL && (__LANGUAGE_C__ || __cplusplus) */

/*
 * valid signal values: all undefined values are reserved for future use 
 * note: POSIX requires a value of 0 to be used as the null signal in kill()
 */
#define	SIGHUP	   1	/* hangup, generated when terminal disconnects */
#define	SIGINT	   2	/* interrupt, generated from terminal special char */
#define	SIGQUIT	   3	/* (*) quit, generated from terminal special char */
#define	SIGILL	   4	/* (*) illegal instruction (not reset when caught)*/
#define	SIGTRAP	   5	/* (*) trace trap (not reset when caught) */
#define	SIGABRT    6	/* (*) abort process */
#define SIGEMT	   7	/* (*) EMT instruction */
#define	SIGFPE	   8	/* (*) floating point exception */
#define	SIGKILL	   9	/* kill (cannot be caught or ignored) */
#define	SIGBUS	  10	/* (*) bus error (specification exception) */
#define	SIGSEGV	  11	/* (*) segmentation violation */
#define	SIGSYS	  12	/* (*) bad argument to system call */
#define	SIGPIPE	  13	/* write on a pipe with no one to read it */
#define	SIGALRM	  14	/* alarm clock timeout */
#define	SIGTERM	  15	/* software termination signal */
#define	SIGURG 	  16	/* (+) urgent contition on I/O channel */
#define	SIGSTOP	  17	/* (@) stop (cannot be caught or ignored) */
#define	SIGTSTP	  18	/* (@) interactive stop */
#define	SIGCONT	  19	/* (!) continue if stopped */
#define SIGCHLD   20	/* (+) sent to parent on child stop or exit */
#define SIGTTIN   21	/* (@) background read attempted from control terminal*/
#define SIGTTOU   22	/* (@) background write attempted to control terminal */
#define SIGPOLL	  23	/* I/O possible, or completed */
#define SIGXCPU	  24	/* cpu time limit exceeded (see setrlimit()) */
#define SIGXFSZ	  25	/* file size limit exceeded (see setrlimit()) */
#define SIGVTALRM 26	/* virtual time alarm (see setitimer) */
#define SIGPROF   27	/* profiling time alarm (see setitimer) */
#define SIGWINCH  28	/* (+) window size changed */
#define SIGINFO   29    /* (+) information request */
#define SIGUSR1   30	/* user defined signal 1 */
#define SIGUSR2   31	/* user defined signal 2 */
#define SIGRESV	  32	/* reserved by Digital for future use */

/*
 * additional signal names supplied for compatibility, only 
 */
#define SIGIOINT SIGURG	/* printer to backend error signal */
#define	SIGIO	SIGPOLL	/* STREAMS version of this signal */
#define SIGAIO	SIGIO	/* base lan i/o */
#define SIGPTY  SIGIO	/* pty i/o */
#define SIGIOT  SIGABRT /* abort (terminate) process */ 
#define	SIGLOST	SIGIOT	/* old BSD signal ?? */
#define SIGPWR  SIGINFO /* Power Fail/Restart -- SVID3/SVR4 */

/*
 * valid signal action values; other values => pointer to handler function 
 */
#ifndef	_NO_PROTO
typedef void (*__sigfp)(int);
#define	SIG_ERR		(__sigfp)-1
#define	SIG_DFL		(__sigfp)0
#define	SIG_IGN		(__sigfp)1
#define	SIG_HOLD        (__sigfp)2	        /* not valid as argument
                                                   to sigaction or sigvec */
#define	SIG_CATCH       (__sigfp)3      	/* not valid as argument
                                                   to sigaction or sigvec */
#else	/* _NO_PROTO */
#define SIG_ERR		(void (*)())-1
#define	SIG_DFL		(void (*)())0
#define	SIG_IGN		(void (*)())1
#define SIG_HOLD        (void (*)())2           /* not valid as argument
                                                   to sigaction or sigvec */
#define SIG_CATCH       (void (*)())3           /* not valid as argument
                                                   to sigaction or sigvec */
#endif	/* _NO_PROTO */

#endif /* _ANSI_C_SOURCE */

/*
 *   The following are values that have historically been in signal.h.
 *
 *   They are a part of the POSIX defined signal.h and therefore are
 *   included when _POSIX_C_SOURCE is defined >=1.
 *
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1) 

/*
 * values of "how" argument to sigprocmask() call
 */
#define SIG_BLOCK	1
#define SIG_UNBLOCK	2
#define SIG_SETMASK	3

/*
 * valid flag define for sa_flag field of sigaction structure - POSIX
 */
#define SA_NOCLDSTOP	0x00000004	/* do not set SIGCHLD for child stops*/

#ifndef ASSEMBLER
#ifndef _PID_T
#define _PID_T
typedef	 int		pid_t;		/* process ID */
#endif

#ifndef _SIGSET_T
#define _SIGSET_T
typedef unsigned long 	sigset_t;
#endif

/*
 * sigaction structure used in sigaction() system call 
 * The order of the fields in this structure must match those in
 * the sigvec structure (below).
 *
 * Realtime/EXT definition of sigaction includes the sa_sigaction
 * member to allow specification of the three-argument version
 * of a signal handler.
 */
struct sigaction {
#if (_POSIX_C_SOURCE >= 199309L) || defined(_XOPEN_SOURCE_EXTENDED) 
	union {
		 /* signal handler, or action value */
		void	(*_handler) __((int));
		void	(*_sigaction) __((int, siginfo_t *, void *));
	} _sa_un;
#define sa_handler _sa_un._handler
#define sa_sigaction _sa_un._sigaction
/*
 * Define SA_SIGINFO here for POSIX.1b and .1c use. Define it again
 * later on to be visible under _OSF_SOURCE, as it always has been.
 */
#define SA_SIGINFO	0x00000040	/* deliver siginfo to handler */
#else
/*
 * POSIX.1 specifies no argument for this function pointer, although
 * the intention is clearly that it be (*sa_handler)(int).
 */
	void	(*sa_handler) __(()); /* signal handler, or action value */

#endif /* (_POSIX_C_SOURCE >= 199309L) || defined(_XOPEN_SOURCE_EXTENDED) */
	sigset_t sa_mask;	/* signals to block while in handler */
	int	sa_flags;	/* signal action flags */
	int	sa_signo;	/* sigal number */
};

#ifndef _KERNEL

/*
 * function prototypes for signal functions 
 */
/* system calls */
extern int kill __((pid_t , int)); 
#ifdef _XOPEN_SOURCE_EXTENDED
extern void (*bsd_signal __((int, void (*func)(int)))) __((int));
extern int killpg __((pid_t, int));
#endif

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define sigaction(__a,__b,__c) _Esigaction(__a,__b,__c)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int __R(sigaction)
	__((int, const struct sigaction *, struct sigaction *)); 

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int sigprocmask __((int, const sigset_t *, sigset_t *));
extern int sigsuspend __((const sigset_t *));  
/* library routines */
extern int sigemptyset __((sigset_t *));
extern int sigfillset __((sigset_t *));
extern int sigaddset __((sigset_t *, int));
extern int sigdelset __((sigset_t *, int));
extern int sigismember __((const sigset_t *, int));
extern int sigpending __((sigset_t *));

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 
/* syscall prototypes */
extern int sigwaitinfo __((const sigset_t *, siginfo_t *));
extern int sigtimedwait __((const sigset_t *, siginfo_t *,
			    const struct timespec *)); 
extern int sigqueue __((pid_t, int, const union sigval));
/*
 * Realtime signal values are evalutated at runtime to enhance
 * binary compatibility with future changes to the number of
 * RT signals. These expressions should always be used rather
 * than hardcoded expressions based, for example, on NSIG.
 *
 * NOTE: these hardcoded values map to _SC_RTSIG_LOW and _SC_RTSIG_HI
 * in <unistd.h>. That file should be included here, but its prototypes
 * can wreak havoc with the namespace of existing applications that
 * never included <unistd.h> before.
 */
#define	SIGRTMIN  (sysconf(131))
#define	SIGRTMAX  (sysconf(132))
#endif /* _POSIX_C_SOURCE >= 199309L */

#if (_POSIX_C_SOURCE >= 199506L)
extern int pthread_sigmask __((int, const sigset_t *, sigset_t *));
extern int pthread_kill __((pthread_t, int));
#endif /* _POSIX_C_SOURCE >= 199506L */

#endif /* _KERNEL */
#endif 	/* ASSEMBLER */

#endif /* _POSIX_C_SOURCE >= 1 */


#include <machine/signal.h>

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#ifdef _OSF_SOURCE
#include <sys/types.h>
/*
 * Macro for converting signal number to an integer mask suitable for
 * older compat. routines such as sigblock().
 */
#define sigmask(m)	(1L << ((m)-1))

#ifndef ASSEMBLER
extern sigset_t cantmasksigset;
#endif

/*
 * sigvec structure used in sigvec compatibility interface.
 * The order of the fields in this structure must match those in
 * the sigaction structure (above).
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct	sigvec {
	void	(*sv_handler) __((int));	/* signal handler */
	int     sv_mask;        /* signal mask to apply */
	int     sv_flags;    
};                           

#define sv_onstack sv_flags     /* isn't compatibility wonderful! */

/*
 * function prototypes for signal functions 
 */

#ifndef _KERNEL
extern int sigvec __((int, struct sigvec *, struct sigvec *));
extern int killpg __((pid_t, int));
#endif	/* !_KERNEL */
#endif	/* __LANGUAGE_C__ || __cplusplus */

#endif /* _OSF_SOURCE */

/*
 * sigstack structure used in sigstack() system call 
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct  sigstack {
#ifdef _XOPEN_SOURCE_EXTENDED
        void    *ss_sp;                 /* signal stack pointer */
#else
        char    *ss_sp;                 /* signal stack pointer */
#endif
        int     ss_onstack;             /* current status */
};

/*
 * Pointer to a list of signal name strings and the number
 * of signals+1 supported by the system.
 */
extern char *__sys_siglist[];
extern int __sys_nsig;
#endif /* __LANGUAGE_C__ || __cplusplus */

/*
 * sigaltstack() control flags
 */
#define	SS_ONSTACK	0x00000001	/* use signal stack */
#define SS_DISABLE	0x00000002	/* disable (don't use) signal stack */
#define SS_NOMASK	0x00000004 	/* no mask restore on sigreturn */
#define SS_UCONTEXT	0x00000008	/* stack contains ucontext_t */
#define SS_STACKMAGIC	0xfafababe00000000
					/* stack data restore on sigreturn */
#define _SSTACKFLAGS	(SS_ONSTACK|SS_DISABLE|SS_UCONTEXT)

#define MINSIGSTKSZ	(4096)
#define SIGSTKSZ	(16384)

#ifndef _XOPEN_SOURCE_EXTENDED
/*
 * valid signal action values; other values => pointer to handler function 
 */
#define BADSIG		SIG_ERR
#endif

/*
 * valid flags define for sa_flag field of sigaction structure 
 */
#define	SA_ONSTACK	0x00000001	/* run on special signal stack */
#define SA_RESTART	0x00000002	/* restart system calls on sigs */
/* 
 * NOTE: The POSIX SA_NOCLDSTOP flag is defined above in this file 
 * as 0x00000004.
 */
#define SA_NODEFER	0x00000008	/* don't block while handling */
#define SA_RESETHAND	0x00000010	/* old sys5 style behavior */
#define SA_NOCLDWAIT	0x00000020	/* no zombies */
#ifndef SA_SIGINFO
#define SA_SIGINFO	0x00000040	/* deliver siginfo to handler */
#endif
#define SA_CLDNOTIFY	0x00000080	/* deliver siginfo when exiting */

#define SIGCLD		SIGCHLD

/* 
 * macros to manipulate signal sets
 */
#define	SIGINITSET(set)		(set) = (sigset_t)0;

#define	SIGMASK(s)		sigmask(s)

#define	SIGEMPTYSET(set)	(set) = (sigset_t)0;

#define	SIGFILLSET(set)		(set) = (sigset_t)~0;

#define SIGDELSET(set, s)	(set) &= ~SIGMASK(s);

#define SIGADDSET(set, s)	(set) |= SIGMASK(s);

#define SIGISMEMBER(set,s)	(((set) & SIGMASK(s)) != (sigset_t)0)

#define SIGMASKSET(dest, mask)	((dest) &= ~(mask))

#define SIGORSET(dest, mask)	((dest) |= (mask))

/*
 * values in sv_onstack are interpreted identically to values in
 * sa_onstack for sigaction();  however, the following additional
 * names are defined for values in sv_onstack to be compatible with
 * old usage of sigvec() 
 */

/* maximum number of actual signals: 1 - SIGMAX are valid */
#define SIGMAX	48
#ifndef _XOPEN_SOURCE_EXTENDED
/* amount of storage (1 to SIGMAX) for signals */
#define NSIG	(SIGMAX+1)	/* prefer __sys_nsig; see above */
#define ONSIG	(32)
#endif

#define SIG_STK		0x00000001 /* bit for using sigstack stack */
#define SIG_STD		0x00000002 /* bit for old style signals */
#define SV_ONSTACK	SA_ONSTACK /* take signal on signal stack */
#define SV_INTERRUPT	SA_RESTART /* do not restart system on signal return */

#ifndef _KERNEL

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define sigpause(__a) _Esigpause(__a)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int __R(sigpause) __((int));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

#ifndef _XOPEN_SOURCE_EXTENDED
extern int sigreturn __((struct sigcontext *));
extern int sigblock __((int));
extern int sigsetmask __((int));
#endif

extern int sigstack __((struct sigstack *, struct sigstack *));
extern int siginterrupt __((int, int));

#if defined(_POSIX_C_SOURCE) \
	&& (_POSIX_C_SOURCE >= 199506L) \
	&& !defined(_V40_OBJ_COMPAT)
# ifdef __DECC
#  pragma extern_prefix "_P"
# else
#  define sigwait(__a,__b) _Psigwait(__a,__b)
# endif
extern int __P_C(sigwait) __((const sigset_t *set, int *sig));
# ifdef __DECC
#  pragma extern_prefix ""
# endif
#else
# ifdef _OSF_SOURCE
extern int sigwait __((sigset_t *));
# endif /* _OSF_SOURCE */
#endif /* _POSIX_C_SOURCE >= 199506L */

/* SVR3, SVR4 */
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define sigset(__a,__b) _Esigset(__a,__b)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern void (*__R(sigset) __((int, void (*)(int)))) __((int));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int sighold __((int));
extern int sigrelse __((int));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define sigignore(__a) _Esigignore(__a)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int __R(sigignore) __((int));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

#ifdef _XOPEN_SOURCE_EXTENDED
extern int sigaltstack __((const stack_t *, stack_t *));
#else
extern int sigaltstack __((stack_t *, stack_t *));
#include <sys/procset.h>
extern int sigsendset __((const procset_t *, int));
extern int sigsend __((idtype_t, id_t, int));

int (*ssignal __((int, int (*)(int)))) __((int));
int gsignal __((int));
#endif

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
int (*ssignal_r __((int, int (*) (int), int (*sigs[])(int)))) __((int));
int gsignal_r __((int, int (*sigs[])(int)));
#endif /* _REENTRANT || _THREAD_SAFE */

#ifdef _XOPEN_SOURCE_EXTENDED
#include <sys/context_t.h>
#endif

#endif  /* !_KERNEL */

#ifdef _KERNEL


#define thread_signal_disposition(signo) (sigprop[signo] & SA_THREAD)
/*
 * signal_dispostion macro is now a routine.
 */

#ifndef ASSEMBLER
/*
 * Defintions for dynamic signals.
 */

struct sigacthdr {
	int	sh_count;
	int	sh_size;
	int	(*sh_sigtramp)();
	int	(*sh_sigtramp1170)();
	struct	sigaction sh_sigact[1];
};

/* Size of the header portion of the dynamic signal storage */
#define SA_HDRSIZE (sizeof(struct sigacthdr) - sizeof(struct sigaction))

/*
 * Signal properties.
 */
extern int sigprop[];

#define	SA_KILL		0x100		/* terminates process by default */
#define	SA_CORE		0x200		/* ditto and coredumps */
#define	SA_STOP		0x400		/* suspend process */
#define	SA_TTYSTOP	0x800		/* ditto, from tty */
#define	SA_IGNORE	0x1000		/* ignore by default */
#define	SA_CONT		0x2000 		/* continue if suspended */
#define	SA_CANTMASK	0x4000		/* non-maskable, catchable */
#define	SA_THREAD	0x8000		/* excpetion signal */
#define SA_PROCESS	0x10000		/* process signal */
					/* else is a per-thread signal	*/
#define SA_GROUP	0x20000		/* group signal */
#define SA_CATCH	0x40000		/* signal is being caught */
#define SA_OMASK	0x80000		/* sigsuspend in progress */
#define SA_NORESET	0x100000	/* don't honor noresethand */
#define SA_JOBC		0x200000	/* job control signal */
#define SA_UCONTEXT	0x400000	/* provide uconext_t */
#define SA_S1170	0x800000	/* 1170 SIGPOLL */
#define SA_SIGWAIT	0x1000000	/* did sigwait */
#define SA_UNWAIT	0x2000000	/* procfs undid a wait state */

#define CURSIG(p, npu)						\
	(npu->uu_cursig ? npu->uu_cursig : checksig(p, npu) ? issig() : 0)

#include <sys/unix_defs.h>

/*
 * Put the signal and possible a siginfo back into the pending
 * state.
 */
#define CURSIGBAK(p, npu, flags, sig)				\
        MACRO_BEGIN						\
        if (flags & SA_PROCESS) {				\
                sigaddset(&(p)->p_sig, sig);			\
                if (flags & SA_GROUP)				\
                        sigaddset(&(p)->p_gsig, sig);		\
		if ((npu)->uu_curinfo) {			\
			if ((npu)->uu_curinfo->siginfo.si_kflags\
			    & SQ_ABORT) 			\
				wakeup((npu)->uu_curinfo);	\
			sigq_requeue(&(p)->p_sigqueue,		\
				     &(npu)->uu_curinfo);	\
		}						\
        } else {						\
                sigaddset(&(npu)->uu_sig, sig);			\
		if ((npu)->uu_curinfo) {			\
			if ((npu)->uu_curinfo->siginfo.si_kflags\
			    & SQ_ABORT) 			\
				wakeup((npu)->uu_curinfo);	\
			sigq_requeue(&(npu)->uu_sigqueue,	\
				     &(npu)->uu_curinfo);	\
		}						\
        }							\
        MACRO_END

/*
 * We encapsulate here whether or not a p{g,}signal() operation may
 * block.  On a (non-master/slave) MP, or on a uniprocessor with
 * lock debugging (and hence simple locks) enabled, it may block,
 * and thus should not be called from interrupt level.  Otherwise,
 * psignal() is non-blocking, so may be called from interrupt
 * or thread context.
 *
 * Routines psignal_inthread() and pgsignal_internal() are the
 * old p{g,}signal(), which directly post a signal.  When
 * PSIGNAL_THREAD is true, psignal_inthread() may block,
 * and so is callable only from thread context.
 *
 * Routines p{g,}signal_indirect() enqueue a signal request for
 * deferred processing by a discrete kernel thread, so may be
 * called from interrupt level.  They are defined only when
 * PSIGNAL_THREAD is true.
 *
 * The definitions here hide which routine a call to "psignal"
 * or "pgsignal" will actually be translated into.  This is
 * done both on behalf of calls in the kernel that may be made
 * at interrupt level, and on behalf of externally-provided
 * device drivers.
 */
#include <unix_locks.h>
#include <cpus.h>
#include <mach_ldebug.h>
#include <rt_preempt.h>

#define PSIGNAL_THREAD	(UNIX_LOCKS || (NCPUS == 1 && MACH_LDEBUG))

#if	PSIGNAL_THREAD
#define psignal(P,SIG) psignal_indirect((P),(SIG),0)
#define psignal_info(P,SIG,SIP)	psignal_indirect((P),(SIG),(SIP))
#define pgsignal	pgsignal_indirect
#define pgsignal_self	pgsignal_inthread_self
typedef struct sig_event {
	queue_chain_t   se_chain;
	struct proc	*se_proc;
	struct pgrp	*se_pgrp;
	pid_t		se_pid;
	int		se_pid_generation;
	int		se_sig;
	int		se_flags;
	k_siginfo_t	se_sinfo;
} sig_event_t;

/*
 * Values for se_flags:
 */
#define SIGEV_GROUP     0x01    /* group signal */
#define SIGEV_CTTY      0x02    /* check controlling tty */
#define SIGEV_SINFO	0x08	/* event has siginformation */
#define SIGEV_DYN       0x80    /* event was dynamically allocated */
#define SIGEV_REALITIMER 0x100
#define SIGEV_POSIX_TIMER 0x200
#define SIGEV_NOOP	0x400	/* take no action on entry */

#else /* PSIGNAL_THREAD */

#define psignal		psignal_inthread	/* thread context only */
#define pgsignal	pgsignal_inthread
#define pgsignal_self	pgsignal_inthread_self

#endif	/* !PSIGNAL_THREAD */

/*
 * Treat the TTY subsystem as a special case:  on the only MP
 * reference platform (Multimax), TTY "interrupts" are guaranteed
 * to be delivered in thread context.  Hence pgsignal_inthread
 * may be used to post signals from the TTY code, even when
 * PSIGNAL_THREAD is true, except in uniprocessor lock debugging
 * configurations.
 *
 * This assumes that future MP platforms will follow the same
 * convention.
 *
 * A further complication here is our desire always to signal
 * the current process, if any, even if (in an MP environment)
 * it has changed pgrp's since we started deciding whether to
 * signal its (erstwhile) group (at which point we referenced
 * the pgrp, but did not lock it against changes).  We use
 * still another entry point, pgsignal_inthread_self(), to
 * deal with this case.  Note that forcing a signal to the
 * current process only makes sense in thread context (i.e.,
 * if there *is* a current process) -- hence if doself is
 * set in pgsignal_tty, we assume we're in thread context.
 */
#if PSIGNAL_THREAD && NCPUS == 1
#define	pgsignal_tty(pg, sig, checkctty, doself,smpsafe) \
MACRO_BEGIN \
	if (doself) \
		pgsignal_inthread_self(pg, sig, checkctty); \
	else \
		pgsignal_indirect(pg, sig, checkctty); \
MACRO_END
#define psignal_tty(p, sig, smpsafe)  psignal_indirect(p, sig, 0);

#else
#if NCPUS > 1 || RT_PREEMPT 
#define	pgsignal_tty(pg, sig, checkctty, doself, smpsafe) \
MACRO_BEGIN \
	if (doself) \
		pgsignal_inthread_self(pg, sig, checkctty); \
	else { \
		if (smpsafe) pgsignal_inthread(pg, sig, checkctty); \
		else \
			pgsignal_indirect(pg, sig, checkctty); \
	} \
MACRO_END


#define psignal_tty(p, sig, smpsafe) \
MACRO_BEGIN \
	if (smpsafe) psignal_inthread(p, sig); \
	else \
		psignal_indirect(p, sig, 0); \
MACRO_END
#else 
#define	pgsignal_tty(pg, sig, checkctty, doself, smpsafe) \
MACRO_BEGIN \
	if (doself) \
		pgsignal_inthread_self(pg, sig, checkctty); \
	else { \
		pgsignal_inthread(pg, sig, checkctty); \
	} \
MACRO_END


#define psignal_tty(p, sig, smpsafe) \
MACRO_BEGIN \
	psignal_inthread(p, sig); \
MACRO_END

#endif /* NCPUS > 1 || RT_PREEMPT */
#endif	/* PSIGNAL_THREAD && NCPUS == 1 */

#endif /* ASSEMBLER */
#endif /* _KERNEL */

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#if defined(__cplusplus)
}
#endif
#endif /* _SYS_SIGNAL_H_ */
