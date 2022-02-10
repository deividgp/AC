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
 *	@(#)$RCSfile: user.h,v $ $Revision: 4.3.95.3 $ (DEC) $Date: 1998/03/27 18:27:45 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.
 * All Rights Reserved.
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
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
 * OSF/1 Release 1.2
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_USER_H_
#define _SYS_USER_H_

#include <sys/secdefines.h>
#include <mach/boolean.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/namei.h>
#include <sys/ucred.h>
#include <sys/sem.h>
#include <sys/audit.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <kern/queue.h>
#ifdef	_KERNEL
#include <sys/siginfo.h>
#include <kern/event.h>
#include <sys/security.h>
#include <machine/nxm.h>
#endif	/* _KERNEL */

#if defined (__cplusplus)
struct proc;
struct file;
struct exit_actn;
#endif

/*
 * Per process structure containing data that
 * isn't needed in core when the process is swapped out.
 */

#define MAXCOMLEN	16		/* <= MAXNAMLEN, >= sizeof(ac_comm) */
#define MAXLOGNAME      12              /* >= UT_NAMESIZE */

struct flag_field {
	int	fi_flag;
	udecl_simple_lock_data(,*fi_lock) /* unused */
};

#define NOFILE_IN_U    64

#ifdef __alpha
typedef enum {
	SPEC_ACTION_RAISE,
	SPEC_ACTION_IGNORE,
	SPEC_ACTION_CALL_HANDLER,
	SPEC_ACTION_INITIALIZE,
	SPEC_FAULT_IGNORE,
	SPEC_FAULT_RAISE,
	SPEC_ACTION_INITIALIZE_FB_FIXUP
} spec_action;

struct uuspeculative {	/* speculative execution data */
	int		sp_version;
	spec_action	sp_segv_action;
	spec_action	sp_fpe_action;
	vm_offset_t	sp_handler_addr;
};
#endif /* __alpha */

#if	(defined(_KERNEL) || defined(SHOW_UTT))

/*
 *	Per-thread U area.
 *
 *	It is likely that this structure contains no fields that must be
 *	saved between system calls.
 */
struct uthread {
/* namei & co. */
	struct unameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} uu_ncache;
	struct	nameidata uu_nd;
	long    uu_spare[1];
	int	uu_unix_lock;		/* bind to unix_master */
	/*
	 * Member uu_upcf is written at interrupt level.
	 * Give it its own longword, to avoid any locking
	 * overlap (if anything here needed locking, which
	 * nothing currently does).
	 */
	int     uu_upcf;

#ifdef __alpha

/* per thread ieee floating point state */
	ulong_t	uu_ieee_fp_trap_pc;
	ulong_t	uu_ieee_fp_trigger_sum;
	uint_t	uu_ieee_fp_trigger_inst;

	boolean_t uu_asmp;	/* AdvFS ASMP indicator */

        /* the following ieee variables are set via hal_sysinfo(2) */
	ulong_t	uu_ieee_fp_control;
	ulong_t	uu_ieee_set_state_at_signal;
	ulong_t	uu_ieee_fp_control_at_signal;
	ulong_t	uu_ieee_fpcr_at_signal;
#endif /* __alpha */

/* audit information */
	struct sysent *uu_callp;	/* system call table entry */
	int     uu_event;		/* audit event             */
	int     uu_vno_indx;		/* # of vno_{dev,num} used */
	dev_t   uu_vno_dev[AUD_VNOMAX];	/* vnode dev's referenced by cur proc */
	ino_t   uu_vno_num[AUD_VNOMAX];	/* vnode num's referenced by cur proc */
	uint_t  uu_vno_aud[AUD_VNOMAX];	/* vnode audit-mode bits   */
	mode_t  uu_vno_mode[AUD_VNOMAX];/* vnode mode flag         */
	u_int   uu_set_uids_snap;       /* snapshot of set_uids    */

#if SEC_MAC
	tag_t	uu_obj_slevel[AUD_VNOMAX]; /* vnode/object sensitivity level (SL) */
#endif
#if SEC_ILB
	tag_t	uu_obj_ilevel[AUD_VNOMAX];  /* vnode/object information level (IL) */
#endif
#if SEC_BASE
	ushort	  uu_sec_error;		    /* security related errno */
	ushort	  uu_last_fail_priv;	    /* last priv that failed and */
	privvec_t uu_privs_used;	    /* history of privs used */
#endif
#if SEC_PRIV || SEC_ARCH
	sec_eventvec_t	uu_sec_event_hist;  /* recent security event history
					     * mask.  flag bits accessed
					     * SE_ symbols as offsets (from
					     * security.h).  */
#endif

        sigset_t uu_oldmask;            /* saved mask from before sigpause */

	struct np_uthread *np_uthread;
	struct utask *utask;
	struct proc *proc;		/* pointer to proc structure */
	struct thread *thread;		/* quick lookup for current_thread() */
	struct task *task;		/* quick lookup for current_task() */
	struct uuprof uu_prof;
#ifdef _KERNEL
	struct nxm_pth_state *uu_proflast;/* last nxm thread to use uu_prof */
#endif
	stack_t  uu_sigstack;		/* sp & on stack state variable */
};

/*
 * Non-pageable per-thread U area.
 *
 * All the data here may be accessed on behalf of threads other
 * than the current thread, so must always be resident.
 */
struct np_uthread {
#ifdef __alpha
	long	*uu_ar0;		/* address of users saved R0 */
#else
	int	*uu_ar0;		/* address of users saved R0 */
#endif

/* thread exception handling */
        int     uu_code;                /* ``code'' to trap */
	int	uu_cursig;		/* singal to take */

/* per thread signal state */
	int	uu_tsig;		/* thread signal for upcalls */
	int	uu_sflags;		/* origin of signal */
	sigset_t uu_sigwaitmask;	/* signals waiting for */
#ifdef  _KERNEL
        struct event uu_select_event;	/* select waits on this */
	queue_head_t	uu_sigqueue;	/* queue of sigqueue structs */
	sigqueue_t	uu_curinfo;	/* curinfo for exc. */ 
	struct thread_rusage uu_tru;
	struct ushared_state *uu_sptr;
	struct ushared_state uu_share;
	long	uu_rq_enter;		/* time put on runqueue */
	long	uu_thread_rq_wait_sum;	/* sum of wait time */
#endif
};

struct utask_nd {
	struct vnode *utnd_cdir;	/* current directory */
	struct vnode *utnd_rdir;	/* root directory of current process */
};

/*
 * Structures associated with the per-process open file table.
 */
struct ufile_state {
	int	utask_need_to_lock;	     /* set if utask locks needed */
	int	uf_first_available;	     /* low water mark for available
						file descriptors */
	udecl_simple_lock_data(,uf_ofile_lock)
	struct	file *uf_ofile[NOFILE_IN_U];/* file structs of open files */
	char	uf_pofile[NOFILE_IN_U];	/* per-process flags of open files */
	int	uf_lastfile;		/* high-water mark of uf_ofile */
	/*
	 * If greater than NOFILE_IN_U file descriptors are allocated,
	 * uf_ofile_of and uf_pofile_of are used to reference the KALLOC'ed
	 * buffers which store the additional entries.
	 */
	u_int   uf_of_count;
	struct  file    **uf_ofile_of; /* Pointer to KALLOC'ed buffer */
	char            *uf_pofile_of; /* Pointer to KALLOC'ed buffer */
};


struct  socket_sel_queue {
        struct queue_entry      links; 
	int			msel;  /* set if multiple threads selecting */
        int			mbz;	/* maker to tell sel_queue form so_* */
        struct event            *event; /* event to wake-up */
        struct ufile_state	*ufile;	/* file state of task involved */
	struct task		*task;
};

/*
 *	Per-task U area - global process state.
 */
struct utask {
	udecl_simple_lock_data(,uu_handy_lock) /* handy lock for misc. data */
	char	uu_comm[MAXCOMLEN + 1];

/* 1.1 - processes and protection */
	char    uu_logname[MAXLOGNAME]; /* login name, if available */

/* 1.2 - memory management */
	lock_data_t uu_addr_lock;	/* user addr space lock */
	size_t	uu_tsize;		/* text size (clicks) */
	size_t	uu_dsize;		/* data size (clicks) */
	size_t	uu_ssize;		/* stack size (clicks) */
	caddr_t	uu_text_start;		/* text starting address */
	caddr_t	uu_data_start;		/* data starting address */
	caddr_t	uu_stack_start;		/* stack starting address */
	caddr_t	uu_stack_end;		/* stack ending address */
	boolean_t uu_stack_grows_up;	/* stack grows at high end? */
	time_t	uu_outime;		/* user time at last sample */

/* 1.3 - signal management */
	long	uu_extra;		/* used to be uu_sigtramp */
	sigset_t uu_sigrestart;		/* restart flags */

/* 1.4 - descriptor management */
	struct ufile_state uu_file_state;	/* open file information */
#define UF_EXCLOSE	0x1		/* auto-close on exec */
#define UF_MAPPED	0x2		/* mapped from device */
	struct utask_nd uu_utnd;
	mode_t	uu_cmask;		/* mask for file creation */

	int	uu_lflags;		/* process lock flags */
#define UL_TXTLOCK	1
#define UL_DATLOCK	2
#define UL_STKLOCK	4
#define UL_PROLOCK	8
#define UL_ALL_FUTURE	16

/* 1.5 - timing and statistics */
	struct	rusage uu_ru;		/* stats for this proc */
	struct	rusage uu_cru;		/* sum of stats for reaped children */
	long	uu_ioch;		/* # of chars read/written */
	struct	timeval uu_start;
	struct	flag_field uu_acflag;

/* 1.6 - resource controls */
	struct	rlimit uu_rlimit[RLIM_NLIMITS];
	int	uu_maxuprc;		/* max processes per UID (per tree) */

/* sysv ipc */
	int		 uu_shmsegs;	/* # attached shared-memory-segments */
	struct sem_undo *uu_semundo;	/* semaphore undo structure */

/* speculative execution */
#ifdef __alpha
	struct uuspeculative uu_spec;	/* speculative execution  */
#endif /* __alpha */

/* pointers and length to args and env */
        char		*uu_argp;
        char		*uu_envp;
        int		uu_arg_size;
        int		uu_env_size;
	struct execops  *uu_mgr;        /* File format manager */
	void            *uu_handle;     /* Handle for that manager */

/* pointer to compatability module control block */
	struct compat_mod *uu_compat_mod;

/* pointer to chain of LMF actions to do at process exit */
	struct exit_actn *uu_exitp;    /* _LMF_ */

/* audit masks and control flag */
	u_int  uu_auditmask[AUDIT_INTMASK_LEN];	/* auditmask          */
	u_int  uu_audit_cntl;			/* audit control flag */
	u_int  uu_set_uids;			/* incr on uid change */

/* reserved mesq notification queue count */
	u_int uu_sigresvcnt;
	struct 	socket_sel_queue **uu_so_sel; /* Pointer to KALLOC'ed buffer */
	char 	*uu_sel_cache;
	long	uu_sel_size;
	long	uu_task_rq_wait_sum;		/* runq wait sum exited threads */

/* toggle for extended descriptor support */
	u_int uu_fd_newmax;		    

#ifdef __alpha
	void (*uu_fbhandler)();
#endif
	udecl_lock_data(, proc_relation_lock)
	struct  proc *p_pgrpprv; /* pointer to prev process in process group */
};

#endif	/* (defined(_KERNEL) || defined(SHOW_UTT)) */

#include <machine/pcb.h>
struct user {
	struct	pcb u_pcb;
	struct	proc *u_procp;		/* pointer to proc structure */
#ifdef __alpha
	long	*u_ar0;			/* address of users saved R0 */
#else
	int	*u_ar0;			/* address of users saved R0 */
#endif
	char	u_comm[MAXCOMLEN + 1];

/* ssycall parameters, results and catches */
	int	u_arg[8];		/* arguments to current system call */
					/* now only used for signal */

/* 1.1 - processes and protection */
	char	u_logname[MAXLOGNAME];	/* login name, if available */

/* 1.2 - memory management */
	size_t	u_tsize;		/* text size (clicks) */
	size_t	u_dsize;		/* data size (clicks) */
	size_t	u_ssize;		/* stack size (clicks) */
	caddr_t	u_text_start;		/* text starting address */
	caddr_t	u_data_start;		/* data starting address */
	caddr_t	u_stack_start;		/* stack starting address */
	caddr_t	u_stack_end;		/* stack ending address */
	int	u_stack_grows_up;	/* stack grows at high end? */
	time_t	u_outime;		/* user time at last sample */

/* 1.3 - signal management */
	sig_t	u_signal[32+1];	/* disposition of signals */
	sigset_t u_sasigmask[32+1];	/* signals to be blocked */
	sigset_t u_sigonstack;		/* signals to take on sigstack */
	sigset_t u_sigintr;		/* signals that interrupt syscalls */
	sigset_t u_oldmask;		/* saved mask from before sigpause */
	int	u_code;			/* ``code'' to trap */
	stack_t u_sigstack;		/* sp & on stack state variable */
#define u_onstack	u_sigstack.ss_flags
#define u_sigsflags	u_sigstack.ss_flags
#define u_sigsp		u_sigstack.ss_sp
#define u_sigssz	u_sigstack.ss_size

/* 1.4 - descriptor management */
/* This information must exactly match ufile_state structure */
	struct	file *u_ofile[NOFILE_IN_U];/* file structs of open files */
	char	u_pofile[NOFILE_IN_U];	/* per-process flags of open files */
	int	u_lastfile;		/* high-water mark of u_ofile */
	/*
	 * If greater than NOFILE_IN_U file descriptors are allocated,
	 * uf_ofile_of and uf_pofile_of are used to reference the KALLOC'ed
	 * buffers which store the additional entries.
	 */
	u_int   u_of_count;
	struct  file    **u_ofile_of; /* Pointer to KALLOC'ed buffer */
	char            *u_pofile_of; /* Pointer to KALLOC'ed buffer */
#define UF_EXCLOSE	0x1		/* auto-close on exec */
#define UF_MAPPED	0x2		/* mapped from device */
				/* These definitions must match utask_nd */
	struct vnode *u_cdir;	/* current directory */
	struct vnode *u_rdir;	/* root directory of current process */
	short	u_cmask;		/* mask for file creation */

/* 1.5 - timing and statistics */
	struct	rusage u_ru;		/* stats for this proc */
	struct	rusage u_cru;		/* sum of stats for reaped children */
	struct	itimerval u_timer[3];
	int	u_XXX[3];
	struct	timeval u_start;
	struct	flag_field u_acflag;

	struct uuprof u_prof;
	u_short	u_maxuprc;		/* max processes per UID (per tree) */

/* 1.6 - resource controls */
	struct	rlimit u_rlimit[RLIM_NLIMITS];

/* namei & co. */
	struct nameicache {		/* last successful directory search */
		int nc_prevoffset;	/* offset at which last entry found */
		ino_t nc_inumber;	/* inum of cached directory */
		dev_t nc_dev;		/* dev of cached directory */
		time_t nc_time;		/* time stamp for cache entry */
	} u_ncache;
	struct	nameidata u_nd;
#define UL_TXTLOCK	1
#define UL_DATLOCK	2

/* compatability module pointer */
	struct compat_mod *u_compat_mod;

/* pointer to chain of LMF actions to do at process exit */
	struct exit_actn *u_exitp;     /* _LMF_ */

	int	u_stack[1];
};

/* u_error codes */
#include <sys/errno.h>

#ifdef	_KERNEL
#include <kern/thread.h>

#ifndef	u
#ifdef	multimax
extern struct u_address	active_uareas[NCPUS];
#define u       (active_uareas[cpu_number()])
#else	/* multimax */
#ifdef	balance
#define u	(*(struct u_address *) 0x40)
#else	/* balance */
#ifndef __alpha/* need to know size of uthread & pcb before def. u */
#ifndef mips
#define u	(current_thread()->u_address)
#endif	/* mips */
#endif	/* __alpha */
#endif	/* balance */
#endif	/* multimax */
#endif	/* u */
#ifdef __alpha
#define	u_ieee_fp_trigger_sum		uu_ieee_fp_trigger_sum
#define	u_ieee_fp_trigger_inst		uu_ieee_fp_trigger_inst
#define	u_ieee_fp_trap_pc		uu_ieee_fp_trap_pc
#define u_ieee_fp_control		uu_ieee_fp_control
#define u_ieee_set_state_at_signal	uu_ieee_set_state_at_signal
#define u_ieee_fp_control_at_signal	uu_ieee_fp_control_at_signal
#define u_ieee_fpcr_at_signal		uu_ieee_fpcr_at_signal
#define u_procp				proc
#define u_nd				uu_nd
#define u_spare				uu_spare
#define u_asmp				uu_asmp
#define u_unix_lock			uu_unix_lock
#define u_upcf				uu_upcf
#define u_ncache			uu_ncache
#define u_callp				uu_callp
#define u_event				uu_event
#define u_vno_indx			uu_vno_indx
#define u_vno_dev			uu_vno_dev
#define u_vno_num			uu_vno_num
#define u_vno_aud			uu_vno_aud
#define u_vno_mode			uu_vno_mode
#define u_set_uids_snap			uu_set_uids_snap
#define u_oldmask			uu_oldmask
#define u_prof				uu_prof
#define u_proflast			uu_proflast
#define u_sigstack			uu_sigstack
#define u_onstack			u_sigstack.ss_flags
#define u_sigsflags			u_sigstack.ss_flags
#define u_sigsp				u_sigstack.ss_sp
#define u_sigssz			u_sigstack.ss_size
#if SEC_MAC
#define u_obj_slevel			uu_obj_slevel
#endif
#if SEC_ILB
#define u_obj_ilevel			uu_obj_ilevel
#endif
#if SEC_BASE
#define u_sec_error			uu_sec_error
#define u_privs_used			uu_privs_used
#define u_last_fail_priv		uu_last_fail_priv
#endif
#if SEC_PRIV || SEC_ARCH
#define u_sec_event_hist		uu_sec_event_hist
#endif
#else
#define u_nd		uthread->uu_nd
#define u_spare		uthread->uu_spare
#define u_unix_lock     uthread->uu_unix_lock
#define u_upcf		uthread->uu_upcf
#define u_ncache	uthread->uu_ncache
#define u_event		uthread->uu_event
#define u_vno_indx	uthread->uu_vno_indx
#define u_vno_dev	uthread->uu_vno_dev
#define u_vno_num	uthread->uu_vno_num
#define u_vno_aud	uthread->uu_vno_aud
#define u_vno_mode	uthread->uu_vno_mode
#define u_set_uids_snap	uthread->uu_set_uids_snap
#define u_oldmask	uthread->uu_oldmask
#define u_prof		uthread->uu_prof
#define u_sigstack	uthread->uu_sigstack
#define u_onstack	u_sigstack.ss_flags
#define u_sigsflags	u_sigstack.ss_flags
#define u_sigsp		u_sigstack.ss_sp
#define u_sigssz	u_sigstack.ss_size
#endif

/*
 * These macros assume the FD table is locked!
 */
#define U_OFILE(fd, ufp) ((unsigned)(fd) < NOFILE_IN_U ? \
			(ufp)->uf_ofile[(fd)] : \
			(ufp)->uf_ofile_of[(fd) - NOFILE_IN_U])

#define U_OFILE_SET(fd, value, ufp) { \
                    if ((unsigned)(fd) < NOFILE_IN_U ) \
			(ufp)->uf_ofile[(fd)] = (value); \
                    else \
                        (ufp)->uf_ofile_of[(fd) - NOFILE_IN_U] = (value); \
		    if ((value) == NULL && (fd) < (ufp)->uf_first_available ) \
			(ufp)->uf_first_available = (fd); \
}

#define U_POFILE(fd, ufp) ((unsigned)(fd) < NOFILE_IN_U ? \
			(ufp)->uf_pofile[(fd)] : \
			(ufp)->uf_pofile_of[(fd) - NOFILE_IN_U])

#define U_POFILE_SET(fd, value, ufp) { \
                    if ((unsigned)(fd) < NOFILE_IN_U ) \
			(ufp)->uf_pofile[(fd)] = (value); \
                    else \
                        (ufp)->uf_pofile_of[(fd) - NOFILE_IN_U] = (value); \
}

#define u_thread_rq_wait_sum np_uthread->uu_thread_rq_wait_sum
#define u_rq_enter	     np_uthread->uu_rq_enter
#define u_ar0		np_uthread->uu_ar0
#define u_code		np_uthread->uu_code
#define u_sig		np_uthread->uu_sptr->sig
#define	u_cursig	np_uthread->uu_cursig
#define	u_sflags	np_uthread->uu_sflags
#define	u_tsig		np_uthread->uu_tsig
#define u_share		np_uthread->uu_share
#define u_sptr		np_uthread->uu_sptr
#define u_sigmask	np_uthread->uu_sptr->sigmask
#define uu_sigmask	uu_sptr->sigmask
#define uu_sig		uu_sptr->sig
#define u_nxm_active	np_uthread->uu_sptr->nxm_active
#define u_nxm_ssig	np_uthread->uu_sptr->nxm_ssig
#define u_sigwaitmask	np_uthread->uu_sigwaitmask
#define u_select_event	np_uthread->uu_select_event
#define	u_sigqueue	np_uthread->uu_sigqueue
#define	u_curinfo	np_uthread->uu_curinfo
#define u_tru		np_uthread->uu_tru
#define u_pthid		np_uthread->uu_sptr->pth_id
#define u_shflags	np_uthread->uu_sptr->flags
#define u_cancel_state	np_uthread->uu_sptr->cancel_state

#define u_comm		utask->uu_comm
#define u_calltype	utask->uu_calltype	/* ROMP_DUALCALL */
#define u_logname	utask->uu_logname
#define	u_utnd		utask->uu_utnd
#define	u_file_state	utask->uu_file_state
#define u_fd_newmax	utask->uu_fd_newmax
#define u_task_rq_wait_sum	utask->uu_task_rq_wait_sum
#define uu_cdir		uu_utnd.utnd_cdir
#define uu_rdir		uu_utnd.utnd_rdir

#define u_cdir		utask->uu_cdir
#define u_rdir		utask->uu_rdir
#define u_cred		u_nd.ni_cred
#define	u_ruid		u_procp->p_ruid
#define	u_rgid		u_procp->p_rgid
#define u_uid		u_cred->cr_uid
#define u_gid		u_cred->cr_gid
#define u_ngroups	u_cred->cr_ngroups
#define u_groups	u_cred->cr_groups

#define u_tsize		utask->uu_tsize
#define u_dsize		utask->uu_dsize
#define u_ssize		utask->uu_ssize
#define u_text_start	utask->uu_text_start
#define u_data_start	utask->uu_data_start
#define u_stack_start	utask->uu_stack_start
#define u_stack_end	utask->uu_stack_end
#define u_stack_grows_up utask->uu_stack_grows_up
#define u_outime	utask->uu_outime
#ifdef __alpha
#define u_spec		utask->uu_spec
#define u_fbhandler	utask->uu_fbhandler
#endif /* __alpha */

#define u_sigtramp	utask->uu_sigtramp

#define u_sigrestart	utask->uu_sigrestart

#define u_lastfile	u_file_state.uf_lastfile
#define	u_ofile_lock	u_file_state.uf_ofile_lock
#define u_handy_lock    utask->uu_handy_lock
#define u_addr_lock	utask->uu_addr_lock
#define u_cmask		utask->uu_cmask

#define u_ru		utask->uu_ru
#define u_cru		utask->uu_cru
#define u_ioch		utask->uu_ioch
#define u_timer		proc->p_timer
#define u_XXX		utask->uu_XXX
#define u_start		utask->uu_start
#define u_acflag	utask->uu_acflag

#define u_maxuprc	utask->uu_maxuprc

#define u_lflags	utask->uu_lflags

#define u_rlimit	utask->uu_rlimit


#define u_semundo	utask->uu_semundo
#define u_shmsegs	utask->uu_shmsegs

#define u_argp          utask->uu_argp
#define u_envp          utask->uu_envp
#define u_arg_size      utask->uu_arg_size
#define u_env_size      utask->uu_env_size
#define u_compat_mod    utask->uu_compat_mod
#define u_exitp         utask->uu_exitp           /* _LMF_ */
#define u_auditmask     utask->uu_auditmask
#define u_audit_cntl    utask->uu_audit_cntl
#define u_set_uids      utask->uu_set_uids
#define u_mgr           utask->uu_mgr
#define u_handle        utask->uu_handle
#define u_sigresvcnt	utask->uu_sigresvcnt
#define u_so_sel	utask->uu_so_sel
#define u_sel_cache	utask->uu_sel_cache
#define u_sel_size	utask->uu_sel_size


/*
 * Per-utask locks for MP synchronization.
 */

/*
 * This lock covers miscellaneous Unix-related per-task data:
 *   u.u_ru, u.u_cru, u.logname, u.u_acflag, u.u_rdir, u.u_cmask,
 *   and all members of u.u_rlimit except RLIMIT_CPU.
 */
#define U_HANDY_LOCK() 						\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		usimple_lock(&utask->uu_handy_lock);		\
}								\
MACRO_END
#define U_HANDY_UNLOCK() 					\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		usimple_unlock(&utask->uu_handy_lock);		\
}								\
MACRO_END
/*
 *
 * The file table for the process must always be lock if adding or
 * removing a file from the table.  This is to synchronize with the
 * fuser() system call which can peek into another processes 
 * open file table.  For read/writes through the file table on
 * a single threaded task, NO filetable lock is needed.
 *
 */
#define U_FDTABLE_LOCK_ALWAYS(ufp) 				\
MACRO_BEGIN							\
{								\
	usimple_lock(&(ufp)->uf_ofile_lock); 			\
}								\
MACRO_END

#define U_FDTABLE_UNLOCK_ALWAYS(ufp) 				\
MACRO_BEGIN							\
{								\
	usimple_unlock(&(ufp)->uf_ofile_lock); 			\
}								\
MACRO_END

#define U_FDTABLE_LOCK(ufp) 					\
MACRO_BEGIN							\
{								\
	if ((ufp)->utask_need_to_lock)				\
		usimple_lock(&(ufp)->uf_ofile_lock); 		\
}								\
MACRO_END

#define U_FDTABLE_UNLOCK(ufp) 					\
MACRO_BEGIN							\
{								\
	if ((ufp)->utask_need_to_lock)				\
		usimple_unlock(&(ufp)->uf_ofile_lock); 		\
}								\
MACRO_END

/*
 * multithreaded synchronization to Unix address space parameters:
 *   u.u_curbrk, u.u_minbrk, u.u_lflags, u.u_stack_start,
 *   u.u_stack_end, process sigactions, and POSIX timers
 */
#define U_ADDR_LOCK() 						\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		lock_write(&utask->uu_addr_lock);		\
}								\
MACRO_END

#define U_ADDR_UNLOCK() 					\
MACRO_BEGIN							\
{								\
	register struct utask *utask;				\
	utask = u.utask;					\
	if (utask->uu_file_state.utask_need_to_lock)		\
		lock_done(&utask->uu_addr_lock);		\
}								\
MACRO_END

#define U_ADDR_LOCK_TRY()					\
	(u.utask->uu_file_state.utask_need_to_lock ?		\
		lock_try_write(&u.utask->uu_addr_lock) : 1)

#endif	/* _KERNEL */
#endif	/* _SYS_USER_H_ */
