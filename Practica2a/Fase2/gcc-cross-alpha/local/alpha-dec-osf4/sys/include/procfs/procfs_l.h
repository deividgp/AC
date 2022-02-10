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
 * @(#)$RCSfile: procfs_l.h,v $ $Revision: 1.1.60.2 $ (DEC) $Date: 1998/10/30 19:32:45 $
 */

#ifndef _SYS_PROCFS_L_H_
#define _SYS_PROCFS_L_H_

#include <procfs/procfs.h>
#include <s5fs/s5dir.h>
#include <dirent.h>
#include <kern/ipc_pobj.h>

extern int npid;

#define procfs_task_invalid(pn)	((pn)->prc_flags & PRC_FDINVLD)
#define procfs_task_dead(pn)	((pn)->prc_flags & PRC_DEAD)
#define procfs_task_issys(pn)	((pn)->prc_flags & PRC_ISSYS)

/* Macro to test if a proc/task is traced by procfs */
#define procfs_flag_is_set(t, flag)	((t)->procfs.pr_flags & flag)
#define procfs_task_is_traced(t)	procfs_flag_is_set((t), PR_TRACING)
#define procfs_proc_is_traced(p)	\
	procfs_flag_is_set((proc_to_task(p)), PR_TRACING)
#define procfs_task_was_traced(t)	\
	procfs_flag_is_set((t), (PR_TRACING|PR_WASTRACED))
#define procfs_proc_was_traced(p)	\
	procfs_flag_is_set((proc_to_task(p)), (PR_TRACING|PR_WASTRACED))
#define procfs_task_is_open(t)		((t)->proc_vnptr != NULLVP)
#define procfs_proc_trace_exec(p)	\
	procfs_flag_is_set((proc_to_task(p)), PR_STOPEXEC)

/*
 * Local definitions and structure needed by the procfs filesystem.
 * Definitions that are interfaces to other parts of the kenel are in a
 * different file.
 */
#define	PR_MAX_NAME_SZ	23 /* Max size of a /proc filename */
#define PR_MIN_NAME_SZ	5  /* Report /proc filenames as 5 decimal digits MIN */
#define	PR_LAG_SEC	2 /* Number of seconds allowed between dirbuf updates */

#define PR_GRP_MASK 0x0000ff00
#define PR_GRP_DEF (0x00004600)	/* get 'F' group type */

struct pr_sys5_dir {
	struct s5direct s5_dir;
};

typedef	struct s5direct	pr_s5_dirent_t;

struct pr_generic_dir {
	ino_t	d_ino;
	ushort_t	d_reclen;
	ushort_t	d_namlen;
	char	d_name[PR_MAX_NAME_SZ+1];
};

typedef	struct pr_generic_dir	pr_g_dirent_t;

/* The following macros use a feature of the preprocessor, that comments use
 * no space, to get around the automatic insertion of whitespace around the
 * argument passed into a macro (another preprocessor feature).  This can be
 * replaced by the ## operator in ANSI C when ANSI C is available.
 */

#define PR_T_WRITE(t)	(void) procfs_trace_busy((t), FALSE)
#define PR_T_DONE(t)	procfs_trace_free((t))
#define PR_T_TRY(t)	procfs_trace_busy ((t), TRUE)

/* locks for io on procfs vnodes */
extern struct lockinfo  *procnode_ioctl_lockinfo;
#define PN_READ_LOCK(pp)        lock_read(&(pp)->prc_ioctl_lock)
#define PN_WRITE_LOCK(pp)       lock_write(&(pp)->prc_ioctl_lock)
#define PN_WRITE_LOCK_TRY(pp)   lock_try_write(&(pp)->prc_ioctl_lock)
#define PN_READ_UNLOCK(pp)      lock_read_done(&(pp)->prc_ioctl_lock)
#define PN_WRITE_UNLOCK(pp)     lock_write_done(&(pp)->prc_ioctl_lock)
#define PN_SET_RECURSIVE(pp)    lock_set_recursive(&(pp)->prc_ioctl_lock)
#define PN_CLEAR_RECURSIVE(pp)  lock_clear_recursive(&(pp)->prc_ioctl_lock)
#define PN_READ_RECURSIVE(pp)   lock_read_recursive(&(pp)->prc_ioctl_lock)
#define PN_READ_DONE_RECURSIVE(pp) lock_read_done_recursive(&(pp)->prc_ioctl_lock)
#define PN_LOCK_TERMINATE(pp)	lock_terminate(&(pp)->prc_ioctl_lock);
#define PN_IO_LOCK_INIT(pp)     lock_setup(&(pp)->prc_ioctl_lock,procnode_ioctl_lockinfo,TRUE)

#include <sys/ptrace.h>
#ifdef __alpha

#include <machine/trap.h>
#include <mach/alpha/thread_status.h>

#define PROCFS_THREAD_STATE_COUNT	ALPHA_THREAD_STATE_COUNT
#define PROCFS_THREAD_STATE		ALPHA_THREAD_STATE
#define PROCFS_FLOAT_STATE_COUNT	ALPHA_FLOAT_STATE_COUNT
#define PROCFS_FLOAT_STATE		ALPHA_FLOAT_STATE
#define PROCFS_thread_state		alpha_thread_state
#define PR_PC_OFF (sizeof(int))
#define	PROCFS_AST			T_AST

#define PROCFS_FLTPAGE_COOKIE		0xdeadbeef

#endif /* __alpha */

#ifdef mips

#include <mach/mips/thread_status.h>

#define PROCFS_THREAD_STATE_COUNT	MIPS_THREAD_STATE_COUNT
#define PROCFS_THREAD_STATE		MIPS_THREAD_STATE
#define PROCFS_FLOAT_STATE_COUNT	MIPS_FLOAT_STATE_COUNT
#define PROCFS_FLOAT_STATE		MIPS_FLOAT_STATE
#define PROCFS_thread_state		mips_thread_state
#define PR_PC_OFF 0
#define	PROCFS_AST			NULL


#endif
#ifdef i386

#include <mach/i386/thread_status.h>

#define PROCFS_THREAD_STATE_COUNT	i386_THREAD_STATE_COUNT
#define PROCFS_THREAD_STATE		i386_THREAD_STATE
#define PROCFS_FLOAT_STATE_COUNT	i386_FLOAT_STATE_COUNT
#define PROCFS_FLOAT_STATE		i386_FLOAT_STATE
#define PROCFS_thread_state		i386_thread_state
#define PR_PC_OFF 0
#define	PROCFS_AST			NULL


#endif
#ifdef multimax

#include <mach/mmax/thread_status.h>

#define PROCFS_THREAD_STATE_COUNT	NS32000_THREAD_STATE_COUNT
#define PROCFS_THREAD_STATE		NS32000_THREAD_STATE
#define PROCFS_FLOAT_STATE_COUNT	NS32000_THREAD_STATE_COUNT
#define PROCFS_FLOAT_STATE		NS32000_THREAD_STATE /* only 1 set
								of registers */
#define PROCFS_thread_state		ns32000_thread_state

#define PR_PC_OFF 0
#define	PROCFS_AST			NULL

#endif

#define PR_KERN_MAP	kernel_copy_map

/*
 * Functions defined in procfs_subrs.c
 */
extern void	procfs_child_inherit(task_t, task_t, thread_t, boolean_t);
extern void	procfs_exit(task_t, int);
extern void	procfs_release(task_t);
extern void	procfs_exec_trace(struct proc *, struct vnode *, int);
extern void	procfs_trace_signals(struct proc *, int *, int);
extern int	procfs_new_thread(thread_t, task_t, int *);
extern void	procfs_thread_terminate(task_t, thread_t);
extern void	procfs_stop_new_thread(task_t, thread_t);
extern int	procfs_syscall_start(thread_t, task_t, unsigned long,
				     int, long *, boolean_t);
extern int	procfs_syscall_finish(thread_t, task_t, unsigned long);
extern int	procfs_trap(task_t, thread_t, unsigned long,
			    unsigned long, k_siginfo_t*);
extern void	procfs_proc_free_trace(struct task *);
extern void	procfs_ast_stop(void);
extern void	procfs_vp_resched(struct task *);

/* procfs internal routines difinitions starts here */
extern int procfs_openm(task_t, vm_offset_t *);
extern void	procfs_sigdata(struct sigaction *, struct proc *, int, int);
extern boolean_t procfs_trace_busy(task_t, boolean_t);
extern void	procfs_trace_free(task_t);
extern task_t procfs_task_by_pid(pid_t pid);
extern int procfs_val_addrs(task_t, off_t *, vm_offset_t, int);
extern void procfs_proc_free_trace(task_t taskp);
extern int procfs_check_perms(struct vnode *, struct ucred *, task_t);
extern void procfs_set_sentry(task_t, sysset_t *);
extern void procfs_get_sentry(task_t, sysset_t *);
extern void procfs_set_sexit(task_t, sysset_t *);
extern void procfs_get_sexit(task_t, sysset_t *);
extern void procfs_set_trace(task_t, sigset_t *);
extern void procfs_get_trace(task_t, sigset_t *);
extern void procfs_set_fault(task_t, fltset_t *);
extern void procfs_get_fault(task_t, fltset_t *);
extern void procfs_trace_done(task_t);
extern void procfs_set_signal(task_t, thread_t, int, k_siginfo_t *);
extern int procfs_task_direct_stop(task_t, boolean_t);
extern int procfs_thread_direct_stop(task_t, thread_t);
extern int procfs_task_run(task_t, struct prrun *);
extern int procfs_thread_run(task_t, thread_t, struct prrun *);
extern int procfs_task_status(task_t, struct prstatus *);
extern int procfs_thread_status(task_t, thread_t, struct prstatus *);
extern int procfs_psinfo(task_t, struct prpsinfo *);
extern sigset_t procfs_get_sighold(task_t, thread_t);
extern int procfs_set_sighold(task_t, thread_t, sigset_t);
extern void procfs_get_g_dir(pr_g_dirent_t *);
extern void procfs_get_s5_dir(pr_s5_dirent_t *);

typedef enum {
	PROCFS_NO_EVENT,
	PROCFS_EVENT_RUN1,
	PROCFS_EVENT_RUN2,
	PROCFS_EVENT_TRUN,
	PROCFS_EVENT_TSTOP,
	PROCFS_EVENT_EXEC,
	PROCFS_EVENT_EXIT,
	PROCFS_EVENT_SIGNAL,
	PROCFS_EVENT_CREATE,
	PROCFS_EVENT_TERMINATE,
	PROCFS_EVENT_SYSSTART,
	PROCFS_EVENT_SYSFINISH,
	PROCFS_EVENT_TRAP,
	PROCFS_EVENT_AST,
	PROCFS_EVENT_FORK,
	PROCFS_EVENT_DONE1,
	PROCFS_EVENT_DONE2,
	PROCFS_EVENT_DSTOP,
	PROCFS_EVENT_READ,
	PROCFS_EVENT_WRITE,
	PROCFS_EVENT_SEEK,
	PROCFS_EVENT_BUSY,
	PROCFS_EVENT_FREE,
	PROCFS_EVENT_SIGKILL,
	PROCFS_EVENT_PANIC
} procfs_event_t;

extern void procfs_trace_event(procfs_event_t, task_t, thread_t, void *);

extern int procfs_rusage(task_t, prusage_t *);
extern int procfs_thread_rusage(task_t, prusage_t *);

#endif /* _SYS_PROCFS_L_H_ */
