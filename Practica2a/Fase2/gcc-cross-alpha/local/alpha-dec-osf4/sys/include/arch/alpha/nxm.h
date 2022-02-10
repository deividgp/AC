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
 * @(#)$RCSfile: nxm.h,v $ $Revision: 1.1.25.5 $ (DEC) $Date: 1995/06/15 16:26:16
 $
 */
#ifndef _ALPHA_NXM_H
#define _ALPHA_NXM_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/types.h>

#if !defined(__LANGUAGE_ASSEMBLY__) && !defined(ASSEMBLER)
#include <kern/queue.h>
#include <mach/thread_status.h>
#include <sys/signal.h>
#include <sys/resource.h>
#include <sys/habitat.h>

/*
 * Out-of-line user thread state. The kernel can access this
 * when needed, but only the pointer to it (ushared_state.nws)
 * lives in the shared state.
 */
struct nxm_pth_state {
	u_long 		fpregs[32];
	u_long 		fpcr;	/* WARNING... must follow the fpregs!!! */
	stack_t		altstack;
	struct uuprof 	prof;
	struct 	nxm_ieee_state {
		long	ieee_fp_control;	/* floating point state */
		long	ieee_set_state_at_signal;
		long	ieee_fp_control_at_signal;
		long	ieee_fpcr_at_signal;
	} nxm_ieee_state;
	int		sigforce;
	int		pad1;
	long		pad2[9];
};

#ifdef _KERNEL

/*
 * Returns TRUE if the specified thread is an unbound nxm thread.
 */
#define NXM_UNBOUND(__th__) 						\
	((__th__)->nxm_flags && !((__th__)->nxm_flags & NXM_BOUND))

#define NXM_IEEE_STATE_COPYIN()						\
MACRO_BEGIN								\
	if (NXM_UNBOUND(current_thread())) {				\
		int nofault_save;					\
		struct pcb *pcb = current_pcb();			\
		nofault_save = pcb->pcb_nofault;			\
		if (copyin(&u.u_pthid->nxm_ieee_state, 			\
			   &u.u_ieee_fp_control, 			\
			    sizeof(struct nxm_ieee_state))) {		\
			pcb->pcb_nofault = nofault_save;		\
			sigexit(u.u_procp, SIGSEGV);			\
		}							\
		pcb->pcb_nofault = nofault_save;			\
	}								\
MACRO_END

#define NXM_IEEE_STATE_COPYOUT()					\
MACRO_BEGIN								\
	if (NXM_UNBOUND(current_thread())) {				\
		int nofault_save;					\
		struct pcb *pcb = current_pcb();			\
		nofault_save = pcb->pcb_nofault;			\
		if (copyout(&u.u_ieee_fp_control, 			\
			    &u.u_pthid->nxm_ieee_state, 		\
			    sizeof(struct nxm_ieee_state))) {		\
			pcb->pcb_nofault = nofault_save;		\
			sigexit(u.u_procp, SIGSEGV);			\
		}							\
		pcb->pcb_nofault = nofault_save;			\
	}								\
MACRO_END
#endif /* _KERNEL */

/*
 * Context-switched shared-state structure. This data is shared
 * directly between the running user thread and the kernel.
 * This state is context-switched by the user thread library.
 *
 * Each kernel thread has storage for this same data.
 */
struct ushared_state {
	sigset_t 	sigmask;	/* thread signal mask */
	sigset_t 	sig;		/* thread pending mask */
	struct 		nxm_pth_state *pth_id; /* out-of-line state */
	int		flags;		/* shared flags */
#define US_SIGSTACK	0x1		/* thread called sigaltstack */
#define US_ONSTACK	0x2		/* thread is running on altstack */
#define US_PROFILE	0x4		/* thread called profil */
#define US_SYSCALL	0x8		/* thread in syscall */
#define US_TRAP		0x10		/* thread has trapped */

	int		cancel_state;	/* thread's cancelation state */
#define US_CANCEL	  0x1		/* cancel pending */
#define US_NOCANCEL	  0X2		/* synch cancel disabled */
#define US_SYS_NOCANCEL	  0x4		/* syscall cancel disabled */
#define US_ASYNC_NOCANCEL 0x8		/* asynch cancel disabled */
#define US_CANCEL_BITS	(US_NOCANCEL|US_SYS_NOCANCEL|US_ASYNC_NOCANCEL)
#define US_CANCEL_MASK	(US_CANCEL|US_NOCANCEL|US_SYS_NOCANCEL| \
			 US_ASYNC_NOCANCEL)

	/*
	 * These are semi-shared. They are always visible to
	 * the kernel but are never context-switched by the library.
	 */
	int		nxm_ssig;	/* scheduler's synchronous signals */
	int		reserved1;
	long		nxm_active;	/* scheduler active */
	long		reserved2;
};

/*
 * Upcall frame structure. The kernel builds this frame on the
 * stack and its address on an upcall. This same structure can be
 * used for saving/restoring user thread state on library context
 * switches.
 */
struct  nxm_upcall {
	int	usaved;				/* u_state is valid */
	int	pad;
	struct	ushared_state u_state;		/* shared state */
	struct 	alpha_saved_state reg_state;	/* register state */
};

#define UPCALL_HDR_SIZE \
	(sizeof(struct nxm_upcall) - sizeof(struct alpha_saved_state))

/*
 * Shared state structure. The ushared_state portion is context-switch
 * when new user threads are scheduled. The remainder of the structure
 * is shared state bewteen the kernel and the library scheduler. It is
 * never owned by the user thread.
 */
typedef enum nxm_wake_vals {
	NXM_SCHED_IDLE,
	NXM_SCHED_ACTIVE,
	NXM_SCHED_PENDING
} nxm_wake_val_t;

#define NXM_SCHED_ANY	-1

#ifdef __DECC
#ifndef _KERNEL
#pragma message disable bitnotint
#endif
#endif /* __DECC */

/*
 * NOTE: the enum field _nxm_wake_state is signed. If any
 * enums are added to nxm_wake_val_t, the size of nxm_wake_state
 * needs to be increased to avoid sign-bit problems.
 */
typedef struct nxm_sched_bits {
	nxm_wake_val_t	_nxm_wake_state:3;	/* scheduler state */
	unsigned int 	_nxm_unused:13;
 	unsigned short 	_nxm_slotnum;		/* scheduler's slot */
} nxm_sched_bits_t;

#ifdef __DECC
#ifndef _KERNEL
#pragma message enable bitnotint
#endif
#endif /* __DECC */

#define nxm_wake_state	nxm_bits._nxm_wake_state
#define nxm_slotnum	nxm_bits._nxm_slotnum

struct nxm_sched_state {
	struct	ushared_state nxm_u;	/* state own by user thread */
	nxm_sched_bits_t nxm_bits;
	int	nxm_fp_owned;		/* thread did floating point? */
	int	nxm_quantum;		/* quantum count-down value */
	int	nxm_set_quantum;	/* quantum reset value */
	int	nxm_sysevent;		/* syscall state */
	struct	nxm_upcall *nxm_uc_ret;	/* stack ptr of scheduler thread */
	void	*nxm_tid;		/* scheduler's thread id */
	long	nxm_va;			/* page fault address */
	struct 	nxm_pth_state *nxm_pthid; /* id of null thread */
	long	pad[2];
};

/*
 * Shared struct allocated by nxm_task_init(). Visible to both kernel
 * and threads library.
 */
struct nxm_shared {
	long nxm_callback;		/* address of upcall routine */
	unsigned int nxm_version;	/* version number */
	unsigned short nxm_uniq_offset;	/* correction factor for TEB */
	short pad1;
	long space[2];			/* future growth */
	struct nxm_sched_state nxm_ss[1]; /* array of shared areas */
};

/*
 * nxm_action: desriptor for pseudo-upcall.
 */
typedef struct nxm_action {
#define NXM_ACTION_NONE		0
#define NXM_ACTION_SIGNAL	1
#define NXM_ACTION_SIGEV	2
#define NXM_ACTION_SIGFORCE	3
	long	nxm_action_type;
	void	*nxm_action_data;
	long	space[6];
} *nxm_action_t;

/*
 * Structure to report blocking events.
 * (Stop complaints about ulong bit fields.)
 */
#ifdef __DECC
#ifndef _KERNEL
#pragma message disable bitnotint
#endif
#endif /* __DECC */

typedef struct nxm_block_event {
	union {
		struct {
			unsigned long 	_nxm_event_flags:3;
#define NXM_BLOCK_FAULT		0x1	/* blocked on fault/trap event */
#define NXM_BLOCK_SYSCALL	0x2	/* blocked in a syscalls */
#define NXM_BLOCKED_PENDING	0x4	/* blocked with pending signal */
			unsigned long	_nxm_event_habitat:4;
			unsigned long	_nxm_event_syscall:9;
			unsigned long	_nxm_event_kid:48;
		} _nxm_event_s;
		unsigned long _nxm_event_total;
	} _nxm_event_un;
} nxm_event_t;

#ifdef __DECC
#ifndef _KERNEL
#pragma message enable bitnotint
#endif
#endif /* __DECC */

#define nxm_event _nxm_event_un._nxm_event_total
#define nxm_event_flags _nxm_event_un._nxm_event_s._nxm_event_flags
#define nxm_event_habitat _nxm_event_un._nxm_event_s._nxm_event_habitat
#define nxm_event_syscall _nxm_event_un._nxm_event_s._nxm_event_syscall
#define nxm_event_kid _nxm_event_un._nxm_event_s._nxm_event_kid

/*
 * Thread type flags.
 */
#define NXM_TYPE_SCS		0x0
#define NXM_TYPE_VP		0x1
#define NXM_TYPE_MANAGER	0x2

/*
 * Thread signal flags.
 */
#define NXM_SIGNAL_EXPLICIT	0x0
#define NXM_SIGNAL_INHERIT	0x1

typedef struct nxm_task_attr {
	int priority;
	int policy;
	long cpumask[2];
	long pad[2];
} nxm_task_attr_t, *nxm_task_attr_p;

/*
 * Shared thread attributes.
 */
typedef struct nxm_thread_attr {
	int version;
	int type;
	int cancel_flags;
	int priority;
	int policy;
	int signal_type;
        void *pthid;
	sigset_t sigmask;
	long cpumask[2];
	struct {
		long pc;
		long sp;
		long a0;
	} registers;
	long pad2[2];
} nxm_thread_attr_t, *nxm_thread_attr_p;

#if _POSIX_C_SOURCE >= 199506L
typedef struct nxm_sigev_action {
	void         	(*nxm_sigev_func) __((sigval_t));
	sigval_t	nxm_sigev_argument;
} *nxm_sigev_action_t;
#endif

/* 
 * Used only for speculative execution to pass exception data from trap()
 * to nxm_upcall().
 */
struct spec_trap_args {
	u_long trap_a0;
	u_long trap_a1;
	u_long trap_a2;
};

#ifdef _KERNEL
/*
 * Deal with per-thread pending signal masks atomically.
 */
extern sigaddset_atomic(sigset_t *, int);
extern sigadelset_atomic(sigset_t *, int);

#define nxm_sigaddset(__th__,__maskaddr__, __sig__) \
	if (NXM_UNBOUND(__th__))  \
		sigaddset_atomic((__maskaddr__), (__sig__)); \
	else \
		sigaddset((__maskaddr__), (__sig__));
	
#define nxm_sigdelset(__th__, __maskaddr__, __sig__) \
	if (NXM_UNBOUND(__th__))  \
		sigdelset_atomic((__maskaddr__), (__sig__)); \
	else \
		sigdelset((__maskaddr__), (__sig__));

/*
 * Deal with per-thread bit fields atomically.
 */
extern atomic_bitset_l(int *, int);
extern atomic_bitclr_l(int *, int);

typedef struct interrupt_state {
	sigset_t is_sigmask;
	int	 is_cancel;
} interrupt_state_t;

#define sigint_off(_mask_, _saved_state_)				\
{									\
	sigset_t tset;							\
	tset = (_mask_);						\
	sigsetsum(&tset, u.u_sigmask);					\
	(_saved_state_).is_sigmask = u.u_sigmask;			\
	u.u_sigmask = tset;						\
	(_saved_state_).is_cancel = u.u_cancel_state & US_NOCANCEL;	\
	atomic_bitset_l(&u.u_cancel_state, US_NOCANCEL);		\
}

#define sigint_on(_saved_state_)					\
	u.u_sigmask = (_saved_state_).is_sigmask;			\
	if (!((_saved_state_).is_cancel))				\
		atomic_bitclr_l(&u.u_cancel_state, US_NOCANCEL);

#define NXM_TEB(__pthid__, __task__)					\
		((unsigned long) (__pthid__) - 				\
		 (unsigned long) (__task__)->nxm_share->nxm_uniq_offset)


/* max number of scheduler threads */
#define NXM_THREAD_MAX							\
	((page_size - ((sizeof(struct nxm_shared) 			\
		       - sizeof(struct nxm_sched_state)))) / 		\
		sizeof(struct nxm_sched_state))

#define NXM_EXTRA_TIMEOUT 20

#endif /* _KERNEL */
#endif  /* __ASSEMBLER__ */

#define NXM_VERSION		200001

/*
 * Non-signal signals.
 */
#define NXM_THREAD_CANCEL	0x7afababa	/* cancel thread */

/*
 * Suspend types.
 */
#define NXM_SUSPEND_NOCOUNT	0x1
#define NXM_SUSPEND_COUNT	0x2
#define NXM_SUSPEND_FORCE	0x4

/*
 * Thread kill target types.
 */
#define NXM_KILL_UNBOUND	0x1
#define NXM_KILL_BOUND		0x2

/*
 * Flags to guide saving restoring state.
 */
#define NXM_SHARED_SAVED	0x1	/* must restore shared state */
#define NXM_FAST_RESTORE	0x2	/* full restore not required */
#define NXM_FP_ACTIVE		0x4	/* fp registers are live */
#define NXM_UPCALL_FRAME	0x10   	/* signature for stack peekers */

/*
 * Upcall operation codes. Passed as 1st arg to the upcall routine
 * to define the scheduler event.
 *
 * Events detected by the kernel: 1-100 reserved.
 */
#define NXM_QUANTUM_EXPIRE		1 /* quantum expired */
#define	NXM_SCHED_THREAD_UT_BLOCKED	2 /* thread blocked in kernel */
#define	NXM_THREAD_UNBLOCK_NO_SID 	3 /* thread unblocked no sched id */
#define NXM_SIGNAL_BLOCKED		4 /* current thread have blocked sig */
#define NXM_SPECULATIVE_EXECUTION	5 /* call user spec-exec handler */
#define	NXM_THREAD_INTERRUPTED 		6 /* sched/bound thread interrupted */
#define	NXM_VP_RESCHED 			7 /* vp should reenter scheduler */
#define NXM_GENTRAP_HANDLER		8 /* call user gentrap handler */
#define NXM_FB_FIXUP		       10 /* fixup FBs */

#ifndef _KERNEL
#define	_thread_self	13
#define _thread_create	32
#define _task_init 	33
#define _get_psetinfo	34
#define _idle 		35
#define _wakeup_idle 	36
#define _set_pthid 	37
#define _thread_kill 	38
#define _thread_block 	39
#define _thread_wakeup 	40
#define _get_binding	42
#define _resched 	44
#define _set_cancel 	45
#define _set_binding	46
#define _get_state	48
#define _thread_suspend	49
#define _thread_resume	50
#define _signal_check	51
#define _switch_pri	59
#endif

#if defined(__cplusplus)
}
#endif
#endif /* _ALPHA_NXM_H */
