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
 * @(#)$RCSfile: procfs.h,v $ $Revision: 1.1.57.2 $ (DEC) $Date: 1998/01/12 20:08:31 $
 */

#ifndef _SYS_PROCFS_H_
#define _SYS_PROCFS_H_

#include <sys/signal.h>
#include <sys/siginfo.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/param.h>
#include <s5fs/s5param.h>

#ifdef	_KERNEL
#include <kern/macro_help.h>
#include <kern/lock.h>
#include <kern/queue.h>

#else
#include <sys/ioctl.h>

#define		MACRO_BEGIN	do {
#define		MACRO_END	} while (FALSE)

#endif /* _KERNEL */

/* sizes of fields in status and/or ps information structure */

#define CLNAME_SZ	8		/* scheduling class name size */
#define FNAME_SZ	16		/* exec'd file name size */
#define PSARGS_SZ	80		/* ps arguments size */

/* constants for task states */

#define PR_SSLEEP	'S'		/* sleeping: awaiting an event */
#define PR_SRUN		'R'		/* running */
#define PR_SIDL		'I'		/* intermediate state in task
					   creation */
#define PR_SZOMB	'Z'		/* intermediate state in task
					   termination */
#define PR_SSTOP	'T'		/* task is being traced */
#define PR_SDEFAULT	' '		/* default state */

#define PRNODEV 	NODEV
#define NFPREGS		32

struct timestruct {
        long    tv_sec;         /* seconds */
        long    tv_nsec;        /* nanoseconds */
};
typedef struct timestruct timestruc_t;

/*
 * Our proc(4) defines time structure to be timestruc_t, most other known
 * procfs supported by other vendors use timestruc_t as well. However, for
 * some reason, timestruct_t was actually used. To solve the problem, we
 * allow both names to be valid, and hope timestruct_t will be removed in
 * the future.
 */
#define timestruct_t timestruc_t

typedef unsigned long tid_t;	/* thread id type */

#define PRC_NREGS 46

struct gregset {
	long	regs[PRC_NREGS];	/* space for general registers */
};

typedef struct gregset gregset_t;


struct fpregset {
	long	regs[PRC_NREGS];	/* space for floating point registers */
};

typedef struct fpregset fpregset_t;

struct tgregset {
	gregset_t pr_regs;	/* space for general registers */
	tid_t	tid;
};

typedef struct tgregset tgregset_t;


struct tfpregset {
	fpregset_t pr_fpregs;	/* space for floating point registers */
	tid_t	tid;
};

typedef struct tfpregset tfpregset_t;

struct cmd_arguments {
	char	*buffer;	/* pointer to user space buffer */
	long	max_buf_size;   /* max allowable_size */
};

typedef struct cmd_arguments cmd_arguments_t;

typedef struct tsiginfo {
     siginfo_t pr_siginfo;     /* Signal information to set */
     tid_t    pr_tid;               /* Thread ID */
} tsiginfo_t;


typedef struct tsignal {
     int	pr_signal;     /* Signal to send/remove */
     tid_t	pr_tid;        /* Thread ID */
} tsignal_t;

/*
 * According to POSIX, sigaction is defined per task/process. All threads
 * in the same task share one sigaction table. so, PIOCTACTION ioctl
 * becomes obsolete, and will be removed in the future DEC UNIX kernel.
 * Currently, this interface will return sigactions for the first 32 signals
 * of a thread only.
 */
typedef struct tsigaction {
     struct sigaction	pr_sigaction[32];	/* array of sigaction structs */
     tid_t		pr_tid;        		/* Thread ID */
} tsigaction_t;

/*
 * These are the type definitions for the set of traced faults, traced system
 * calls, traced signals, general registers and floating point registers that
 * are used by the /proc code.
 */

/* type for set of traced faults first task then thread */

#define FLTSET_SZ	2

typedef struct {
	unsigned long word[FLTSET_SZ];
} fltset_t;

typedef struct tfltset {
     fltset_t pr_flttrace;   /* Fault trace mask */
     tid_t    pr_tid;        /* Thread ID */
} tfltset_t;

/* type for set of traced system calls first task then thread */

#define SYSSET_SZ	9

typedef struct {
	unsigned long word[SYSSET_SZ];
} sysset_t;

typedef struct tsysset {
     sysset_t pr_systrace;   /* Sytem call trace mask */
     tid_t    pr_tid;        /* Thread ID */
} tsysset_t;

/* type for set of traced signals for thread level */

typedef struct tsigset {
     sigset_t pr_sigtrace;   /* Signal trace mask */
     tid_t    pr_tid;        /* Thread ID */
} tsigset_t;

/*
 *  This contains the
 *  definitions for the ioctl commands as they are defined for the OSF generic
 *  ioctl routine in bsd/sys_generic.c.  The "com" or command parameter is
 *  passed into the generic ioctl routine as a 32 bit integer in the following
 *  format:
 *
 *	bits 0 - 7	ioctl command number
 *	bits 8 - 15	ioctl group id (use 'F' for /proc)
 *	bits 16 - 28	length for copyin/copyout
 *	bits 29 - 31	direction flag (copyin/copyout/void)
 *
 *  The length is the size of the data that is either copied in from the user
 *  to the kernel or copied out from the kernel to the user.
 *
 *  If the direction flag is set to copyin or copyout, user data is passed to
 *  or from the kernel respectively.  If no data is passed to or returned from
 *  the kernel, the direction is set to void.  The _IOR macro is for copyin, the
 *  _IOW macro is for copyout and the _IO macro is for void.  The arguments for
 *  the _IOR and _IOW macros are the group id, the ioctl command number and the
 *  data that is passed.  The arguments to the _IO macro are the group id and
 *  the ioctl number.  For more information see the ioctl.h header file where
 *  these macros are defined.
 *
 *  This header file also contains /proc data structures and definitions for all
 *  the flags used in the flag fields in the data structures.
 */

/* mask to get the /proc ioctl command number */

#define PR_CMD_MASK	0xff

/* codes for /proc ioctl system call */

/* ioctls for task level */

#define PIOCCRED     _IOR('F',1,struct prcred)    /* get credentials */
#define PIOCGETPR    _IOR('F',2,struct proc)      /* get proc structure */
#define PIOCGETU     _IOR('F',3,struct user)      /* get user structure */
#define PIOCGROUPS   _IOR('F',4,gid_t)            /* get group ids */
#define PIOCPSINFO   _IOR('F',5,struct prpsinfo)  /* get ps info */
#define PIOCNICE     _IOW('F',6,int)              /* set nice priority */
#define PIOCOPENMOBS _IOR('F',7,caddr_t)          /* get mapped object */
#define PIOCOPENM    _IOW('F',84,caddr_t)         /* get mapped object */
#define PIOCRUN      _IOW('F',8,struct prrun)     /* make task runable */
#define PIOCSTATUS   _IOR('F',9,struct prstatus)  /* get task status */
#define PIOCSTOP     _IOR('F',10,struct prstatus) /* stop a task */
#define PIOCWSTOP    _IOR('F',11,struct prstatus) /* stop a task w/wait*/
#define PIOCGTRACE   _IOR('F',12,sigset_t)        /* get traced signals */
#define PIOCSTRACE   _IOW('F',13,sigset_t)        /* set traced signals */
#define PIOCSSIG     _IOW('F',14,siginfo_t)  	  /* set sig to siginfo */
#define PIOCKILL     _IOW('F',15,int)             /* send sig to task */
#define PIOCUNKILL   _IOW('F',16,int)             /* delete pending sig */
#define PIOCGHOLD    _IOR('F',17,sigset_t)        /* get held signals */
#define PIOCSHOLD    _IOW('F',18,sigset_t)        /* set held signals */
#define PIOCCFAULT   _IO('F',19)                  /* clear current flt */
#define PIOCGFAULT   _IOR('F',20,fltset_t)        /* get traced faults */
#define PIOCSFAULT   _IOW('F',21,fltset_t)        /* set traced faults */
#define PIOCGENTRY   _IOR('F',22,sysset_t)        /* get traced syscall entry */
#define PIOCSENTRY   _IOW('F',23,sysset_t)        /* set traced syscall entry */
#define PIOCGEXIT    _IOR('F',24,sysset_t)        /* get traced syscall exit */
#define PIOCSEXIT    _IOW('F',25,sysset_t)        /* set traced syscall exit */
#define PIOCRFORK    _IO('F',26)                  /* reset (turn off)
                                                     inherit-on-fork */
#define PIOCSFORK    _IO('F',27)                  /* set inherit-on-fork */
#define PIOCRRLC     _IO('F',28)                  /* reset (turn off)
                                                     run-on-last-close */
#define PIOCSRLC     _IO('F',29)                  /* set run-on-last-close */
#define PIOCGFPREG   _IOR('F',30,fpregset_t)      /* get floating point regs */
#define PIOCSFPREG   _IOW('F',31,fpregset_t)      /* set floating point regs */
#define PIOCGREG     _IOR('F',32,gregset_t)       /* get general regs */
#define PIOCSREG     _IOW('F',33,gregset_t)       /* set general regs */
#define PIOCMAXSIG   _IOR('F',34,int)             /* get max signals */
#define PIOCACTION   _IOR('F',35,struct sigaction)   /* get sig actions */
#define PIOCNMAP     _IOR('F',36,int)             /* get # mem mappings */
#define PIOCMAP      _IOR('F',37,struct prmap)    /* get mem mappings */
#define PIOCGETTK    _IOR('F',38,struct task)     /* UNIMPLEMENTED */
#define PIOCGSPCACT  _IOR('F',39,int)             /* get special action value */
#define PIOCSSPCACT  _IOW('F',40,int)             /* set special action value */
#define PIOCNTHR     _IOR('F',41,int)             /* get thread count */
#define PIOCTLIST    _IOR('F',42,tid_t)           /* get thread ids */
#define PIOCGETUTK   _IOR('F',43,struct utask)    /* get the utask struct */
#define PIOCRTINH    _IO('F',71)                  /*reset inherit-on-th-create*/
#define PIOCSTINH    _IO('F',72)                  /* set inherit-on-th-create */
#define PIOCGFPCR    _IOR('F',77,u_long)          /* get FP control reg */
#define PIOCSFPCR    _IOW('F',78,u_long)          /* set FP control reg */
#define PIOCXPTH     _IOWR('F',79,u_long)  	  /* in port, out thread ptr */
#define PIOCARGUMENTS _IOW('F',80,cmd_arguments_t)  /* command line args */
#define PIOCSET      _IOW('F',81,u_long)          /* set process flags */
#define PIOCRESET    _IOW('F',82,u_long)          /* reset process flags */
#define PIOCMMAP     _IOWR('F',85,prmap_t)   	  /* create mem mapping */
#define PIOCSPPH     _IOW('F',86,void *)   	  /* set patch-point handler */
/* For LUCENT PIOC[T]USAGE from steel */
#define PIOCUSAGE    _IOR('F',90,prusage_t)	  /* SVR4-style task rusage data */
#define PIOCTUSAGE   _IOWR('F',91,prusage_t)	  /* SVR4-style thread rusage data */

/* ioctls for one or more threads */

#define PIOCTRUN     _IOWR('F',45,struct prrun)   /* make thread runable */
#define PIOCTGETTH   _IOWR('F',46,struct thread)  /* UNIMPLEMENTED */
#define PIOCTSTATUS  _IOWR('F',47,struct prstatus)   /* get thread status */
#define PIOCTSTOP    _IOWR('F',48,struct prstatus)   /* stop a thread */
#define PIOCTGTRACE  _IOWR('F',49,tsigset_t)      /* get traced signals */
#define PIOCTSTRACE  _IOWR('F',50,tsigset_t)      /* set traced signals */
#define PIOCTSSIG    _IOWR('F',51,tsiginfo_t)     /* set sig to siginfo */
#define PIOCTKILL    _IOWR('F',52,tsignal_t)      /* sent thread-specific sig */
#define PIOCTUNKILL  _IOWR('F',53,tsignal_t)      /* delete pending sig */
#define PIOCTCFAULT  _IOWR('F',54,tid_t)          /* clear faults */
#define PIOCTGFAULT  _IOWR('F',55,tfltset_t)      /* get traced faults */
#define PIOCTSFAULT  _IOWR('F',56,tfltset_t)      /* set traced faults */
#define PIOCTGFPREG  _IOWR('F',57,tfpregset_t)    /* get floating point regs */
#define PIOCTSFPREG  _IOWR('F',58,tfpregset_t)    /* set floating point regs */
#define PIOCTGREG    _IOWR('F',62,tgregset_t)     /* get general regs */
#define PIOCTSREG    _IOWR('F',63,tgregset_t)     /* set general regs */
#define PIOCTACTION  _IOWR('F',64,tsigaction_t)   /* get sig actions */
#define PIOCTTERM    _IOWR('F',66,tid_t)          /* terminate a thread */
#define PIOCTABRUN   _IOWR('F',69,prabrun_t)      /* run all but threads
                                                       in thread list */
#define PIOCTGETUTH  _IOWR('F',70,struct uthread) /* UNIMPLEMENTED */
#define PIOCTGENTRY  _IOWR('F',73,tsysset_t)      /* get traced syscall entry */
#define PIOCTSENTRY  _IOWR('F',74,tsysset_t)      /* set traced syscall entry */
#define PIOCTGEXIT   _IOWR('F',75,tsysset_t)      /* get traced syscall exit */
#define PIOCTSEXIT   _IOWR('F',76,tsysset_t)      /* set traced syscall exit */
#define PIOCTSHOLD   _IOWR('F',83,tsigset_t)      /* set held signals */

/*
 * The prstatus data structure contains status information that is passed to the
 * user from the kernel when the user invokes the PIOCSTATUS command.  This
 * structure contains status information for the task or thread that is being
 * traced.
 */

/* values for pr_flags in /proc status structure */

#define PR_STOPPED	0x00000001 /* task/thread is stopped */
#define PR_ISTOP	0x00000002 /* task/thread stopped on event of interest */
#define PR_DSTOP	0x00000004 /* task/thread has stop directive in effect */
#define PR_ASLEEP	0x00000008 /* task/thread is asleep within a system call */
#define PR_FORK		0x00000010 /* task/thread has inherit-on-fork flag set */
#define PR_RLC		0x00000020 /* task/thread has run-on-last-close flag set */
#define PR_PTRACE	0x00000040 /* task/thread is being traced by ptrace */
#define PR_PCINVAL	0x00000080 /* program counter contains invalid address */
#define PR_ISSYS	0x00000100 /* task/thread is a system task/thread */
#define PR_ABORT	0x00008000 /* abort the current stop condition */
#define PR_TRACING	0x00010000 /* task is traced */
#define PR_STOPFORK	0x00020000 /* stop child on fork */
#define PR_STOPEXEC	0x00040000 /* stop on exec */
#define PR_STOPTERM	0x00080000 /* stop on task exit */
#define PR_STOPTCR	0x00100000 /* stop on thread creation */
#define PR_STOPTTERM	0x00200000 /* stop on thread exit */
#define PR_ASYNC	0x00400000 /* asynchronous stop mode is in effect */
#define PR_USCHED	0x00800000 /* user level scheduling is in effect */
#define PR_KLC		0x01000000 /* kill-on-last-close, superceeds RLC */
#define PR_WASTRACED	0x02000000 /* was traced at point of exit */
#define PR_TOUCHING	0x04000000 /* touch in progress */

/* flag mask for PIOCSET and PIOCRESET */
#define PR_SETMASK	(PR_FORK | PR_RLC | PR_STOPFORK | PR_STOPEXEC | \
			PR_STOPTERM | PR_STOPTCR | PR_STOPTTERM | PR_KLC)

/* values for pr_why in /proc status structure */
#define PR_REQUESTED	1	/* task/thread stopped via PIOCSTOP */
#define PR_SIGNALLED	2	/* task/thread stopped on receipt of signal */
#define PR_FAULTED	3	/* task/thread stopped on receipt of fault */
#define PR_SYSENTRY	4	/* task/thread stopped on syscall entry */
#define PR_SYSEXIT	5	/* task/thread stopped on syscall exit */
#define PR_JOBCONTROL	6	/* task/thread stopped due to default action
				   of job control signal */
#define PR_FORKSTOP	7	/* child task stopped at end of fork() call */
#define PR_TCRSTOP	8	/* child task stopped on thread_create() */
#define PR_TTSTOP	9	/* child task stopped on thread_terminate() */
#define PR_DEAD	 ((short)0xDEAD) /* task/thread stopped in exit code */

/* /proc status structure */

struct prstatus {
	long	pr_flags;		/* status flags */
	short	pr_why;			/* why task/thread is stopped */
	long	pr_what;		/* what stopped the task/thread */
	siginfo_t pr_info;		/* signal information struct */
	short	pr_cursig;		/* current signal */
	sigset_t pr_sigpend;		/* set of pending signals */
	sigset_t pr_sighold;		/* set of held signals */
	struct sigaltstack pr_altstack;	/* alternate signal stack */
	struct  sigaction pr_action;	/* current signal action */
	pid_t	pr_pid;			/* process id */
	pid_t	pr_ppid;		/* parent process id */
	gid_t	pr_pgrp;		/* group id */
	pid_t	pr_sid;			/* session id */
	timestruc_t pr_utime;		/* user cpu time */
	timestruc_t pr_stime;		/* system cpu time */
	timestruc_t pr_cutime;		/* sum of childrens user times */
	timestruc_t pr_cstime;		/* sum of childrens system times */
	char	pr_clname[CLNAME_SZ];	/* scheduling class name */
	long	pr_teb;			/* thread environment block */
	long	pr_filler[19];		/* for future expansion */
	long	pr_instr;		/* current instruction */
	gregset_t pr_reg;		/* general registers */
	u_long	pr_subcode;		/* breakpoint (and other) subcode */
	long	pr_nthreads;		/* number of threads */
	struct vnode * pr_exvp;		/* vp for executable on disk */
	tid_t	pr_tid;			/* thread id */
					/* NOTE: pr_tid must be the last
					 * element in this structure. Add any
					 * new elements before it.
					 */
};

typedef struct prstatus prstatus_t;

/*
 * The prrun data structure contains information that is passed from the user to
 * the kernel when the user invokes the PIOCRUN command.  It allows the user to
 * specify certain actions to be taken before a stopped task or thread is run.
 * The actions are performed and the task or thread is resumed.
 */

/* values for pr_flags in run structure */

#define	PRCSIG		0x0001L		/* clear current signal */
#define PRCFAULT	0x0002L		/* clear current fault */
#define PRSTRACE	0x0004L		/* set traced signal set to pr_trace */
#define PRSHOLD		0x0008L		/* set held signal set to pr_hold */
#define PRSFAULT	0x0010L		/* set traced fault set to pr_fault */
#define PRSVADDR	0x0020L		/* set resume address to pr_vaddr */
#define PRSTEP		0x0040L		/* execute in single-step mode */
#define PRSTOP		0x0080L		/* set the demand stop bit */
#define PRSABORT	0x0100L		/* abort system call if PR_SYSENTRY
					   stop or PR_ASLEEP state */
#define	PRRESCHED	0x0200L		/* cause VPs to enter user scheduler */
#define PRNOSTEP	0x0400L		/* cancel in single-step mode */
#define PRTOUCH		0x0800L		/* set modify bit on page */
/* process run structure */

struct prrun {
	long	pr_flags;		/* flags */
	sigset_t pr_trace;		/* set of traced signals */
	sigset_t pr_sighold;		/* set of held signals */
	fltset_t pr_fault;		/* set of faults traced */
	caddr_t	 pr_vaddr;		/* resume virtual address */
	void 	 *pr_touch;		/* page to touch */
	long	 filler[7];		/* for future expansion */
	tid_t	 pr_tid;		/* id for PIOCTRUN, ignored */
					/* by PIOCRUN*/
					/* NOTE: pr_tid must be the last
					 * element in this structure. Add any
					 * new elements before it.
					 */
};

typedef struct prrun prrun_t;

/* NOTE: In order for the thread specific ioctl code to work, it is important
 * that the pr_count and pr_error_thread fields of the next 2 structures,
 * prthreads and prabrun, remain in the same relative positions. See the proc(4)
 * man page for a description of how these 2 structs are used as the "header" of
 * the buffer that is passed to the thread specific ioctls.
 */

/* The thread specific IOCTLs need a capacity to pass lists of threads and
 * structures of interest.  The prthreads structure is defined to aid this 
 */
typedef struct prthreads {
	long     pr_count;          /* number of threads in list */
	tid_t	 pr_error_thread;   /* point in thread list with error */
	char     pr_data[1];           /* thread ioctl data */
} prthreads_t;

/* /proc thread run-all-but structure
 *
 * This structure contains a count of the threads listed
 * as not to be started, a flag as to whether the data in the enclosed
 * prrun structure included is valid, and a list of thread IDs.
 * This gives all the information to modify and control the thread in the task
 * that are not listed by the caller.
 */


struct prabrun {
     long     pr_count;        /* Number of threads listed */
     tid_t    pr_error_thread; /* thread with error */
     prrun_t  pr_run;          /* Run data to apply to started threads */
     char     pr_data[1];      /* pointer to list of threads _NOT_ to run */
};

typedef struct prabrun prabrun_t;

/*
 * The prpsinfo data structure contains information that is passed to the user
 * from the kernel when the user invokes the PIOCPSINFO command.  It contains
 * the information reported by the ps user command.  The information stored in
 * this structure is compatible with the System V Release 4 ps command.
 */


/* ps information structure */

struct prpsinfo {
	char	pr_state;		/* task/thread state */
	char	pr_sname;		/* pr_state in printable char form */
 	char	pr_zomb;		/* task/thread terminated but not waited
					   for */
	char	pr_nice;		/* nice value */
	u_long	pr_flag;		/* process flags */
	uid_t	pr_uid;			/* user id */
	gid_t	pr_gid;			/* group id */
	pid_t	pr_pid;			/* process id */
	pid_t	pr_ppid;		/* parent process id */
	pid_t	pr_pgrp;		/* process group leader pid */
	pid_t	pr_sid;			/* session id */
	caddr_t	pr_addr;		/* physical address */
	long	pr_size;		/* image size in pages */
	long	pr_rssize;		/* resident set size in pages */
	caddr_t	pr_wchan;		/* sleeping task/thread wait address */
	timestruc_t pr_start;		/* start time */
	timestruc_t pr_time;		/* usr+sys cpu time */
	long	pr_pri;			/* task/thread priority */
	char	pr_oldpri;		/* old task/thread priority; pre-SVR4 */
	char	pr_cpu;			/* cpu usage; pre-SVR4 */
	dev_t	pr_ttydev;		/* controlling tty dev(PRNODEV if none*/
	char	pr_clname[CLNAME_SZ];	/* scheduling class name */
	char	pr_fname[FNAME_SZ];	/* last part of exec'd path name */
	char	pr_psargs[PSARGS_SZ];	/* arg list initial characters */
	int	pr_onpro;	/* processor on which it is running */
	int	pr_bindpro;	/* processor on which it is bound */
	int	pr_bindpset;	/* processor-set on which it is bound */
	int	pr_exbindpset;	/* processor-set on which it is exbound */
	long	pr_filler[18];          /* for future use */
};

typedef struct prpsinfo prpsinfo_t;

/*
 * The prmap data structure contains information that is passed to the user from
 * the kernel when the user invokes the PIOCMAP command. This structure contains
 * the memory map information for the traced task or thread.
 */

/* values for pr_mflags in memory mapping structure */

#define MA_READ		0x0001L		/* readable by traced task/thread */
#define MA_WRITE	0x0002L		/* writable by traced task/thread */
#define MA_EXEC		0x0004L		/* executable by traced task/thread */
#define MA_SHARED	0x0008L		/* changes shared by mapped object */
#define MA_BREAK	0x0010L		/* mapping grown by brk syscall */
#define MA_STACK	0x0020L		/* mapping grown by stack faults */

/* memory mapping structure */

struct prmap {
	caddr_t	pr_vaddr;		/* base virtual address */
	u_long	pr_size;		/* mapping size in bytes */
	off_t	pr_off;			/* offset into mapped object */
	long	pr_mflags;		/* protection and attribute flags */
	long	filler[4];		/* for future use */
};

typedef struct prmap prmap_t;

/*
 * The prcred data structure contains information that is passed to the user
 * from the kernel when the user invokes the PIOCCRED command.  This structure
 * contains the credentials of the traced task or thread.
 */

/* credentials structure */

struct prcred {
	uid_t	pr_euid;		/* effective user id */
	uid_t	pr_ruid;		/* real user id */
	uid_t	pr_suid;		/* user id saved from exec */
	gid_t	pr_egid;		/* effective group id */
	gid_t	pr_rgid;		/* real group id */
	gid_t	pr_sgid;		/* group id saved from exec */
	u_int	pr_ngroups;		/* number of supplementary groups */
};

typedef struct prcred prcred_t;

/*
 * Process resource usage struct for use by PIOCUSAGE. NOTE: fields
 * mark by XXX are currently unused and read as zero.
 */
typedef struct prusage {
      timestruc_t pr_tstamp;    /* current time stamp */
      timestruc_t pr_create;    /* process creation time stamp */
      timestruc_t pr_term;      /* XXX process termination time stamp */
      timestruc_t pr_rtime;     /* total real (elapsed) time */
      timestruc_t pr_utime;     /* user CPU time */
      timestruc_t pr_stime;     /* system CPU time */
      timestruc_t pr_ttime;     /* XXX other system trap CPU time */
      timestruc_t pr_tftime;    /* XXX text page fault sleep time */
      timestruc_t pr_dftime;    /* XXX data page fault sleep time */
      timestruc_t pr_kftime;    /* XXX kernel page fault sleep time */
      timestruc_t pr_ltime;     /* XXX user lock wait sleep time */
      timestruc_t pr_slptime;   /* XXX all other sleep time */
      timestruc_t pr_wtime;     /* wait-cpu (latency) time */
      timestruc_t pr_stoptime;  /* XXX stopped time */
      u_long      pr_minf;      /* minor page faults */
      u_long      pr_majf;      /* major page faults */
      u_long      pr_nswap;     /* swaps */
      u_long      pr_inblk;     /* input blocks */
      u_long      pr_oublk;     /* output blocks */
      u_long      pr_msnd;      /* messages sent */
      u_long      pr_mrcv;      /* messages received */
      u_long      pr_sigs;      /* XXX signals received */
      u_long      pr_vctx;      /* voluntary context switches */
      u_long      pr_ictx;      /* involuntary context switches */
      u_long      pr_sysc;      /* XXX system calls */
      u_long      pr_ioch;      /* chars read and written */
      tid_t       tid;          /* Thread ID to get info on (PIOCTUSAGE only) */
} prusage_t;

/*
 * macros for manipulating signal, fault and system call trace flags
 * it is assumed that the size of a word is 32 bits
 * sp is a pointer to sigset_t, fltset_t, or sysset_t
 * flag is a number corresponding to a trace flag in *sp.
 */

#ifdef __alpha
#define PR_SHFT 6
#define PR_MSK 0x3f
#else
#define PR_SHFT 5
#define PR_MSK 0x1f
#endif

/* turn on all trace flags in set */
#define	prfillset(sp) MACRO_BEGIN \
	register long _i_ = sizeof(*(sp))/sizeof(long); \
		while(_i_) \
			((long*)(sp))[--_i_] = -1; MACRO_END

/* turn off all trace flags in set */
#define	premptyset(sp) MACRO_BEGIN \
	register long _i_ = sizeof(*(sp))/sizeof(long); \
		while(_i_) \
			((long*)(sp))[--_i_] = 0L; MACRO_END

/* turn on specified trace flag in set */
#define	praddset(sp, flag) \
	(((u_long)((flag)) < (sizeof(long)*NBBY) * sizeof((*sp))/sizeof(long)) ? \
	(((long*)(sp))[((flag))>>PR_SHFT] |= (1L<<(((flag))&PR_MSK))) : 0)

/* turn off specified trace flag in set */
#define	prdelset(sp, flag) \
	(((u_long)((flag)) < (sizeof(long)*NBBY) * sizeof((*sp))/sizeof(long)) ? \
	(((long*)(sp))[((flag))>>PR_SHFT] &= ~(1L<<(((flag))&PR_MSK))) : 0)

/* query: 0 if trace flag is turned off in set
 *        1 iff trace flag is turned on in set
 */
#define	prismember(sp, flag) \
	(((u_long)((flag)) < (sizeof(long)*NBBY) * sizeof((*sp))/sizeof(long)) \
	&& (((long*)(sp))[((flag))>>PR_SHFT] & (1L<<(((flag))&PR_MSK))))

/* structure containing trace bitmaps for task and thread structures.  These
 * are allocated if the procress is being traced, i.e. opened for write.
 */

typedef struct proctrace {
	sigset_t pr_sigtrace;		/* signals traced by /proc */
	fltset_t pr_flttrace;		/* faults traced by /proc */
	sysset_t pr_sysenter;		/* syscalls traced on entry by /proc */
	sysset_t pr_sysexit;		/* syscalls traced on exit by /proc */
} trcbmap;

typedef struct proctrace *trcbmap_t;


#ifdef	_KERNEL
/* Structure containing /proc information for each task/thread and
 * included as part of the task/thread structure.
 */

struct procfs {
	long	pr_flags;		/* /proc status flags */
	trcbmap_t pr_t;			/* pointer to trace bit map */
	long	pr_what;		/* what stopped the task/thread */
	int	pr_why;			/* why task/thread is stopped */
	int	pr_nmap;		/* number of map entries (PIOCMAP) */
	int	pr_nthreads;		/* number of threads, for PIOCTLIST */
	uid_t	pr_uid;			/* user id of exec'd file */
	gid_t	pr_gid;			/* group id of exec'd file */
	int	pr_protect;		/* permissions of exec'd file */
	u_long	pr_subcode;		/* breakpoint (and other) subcode */
	struct vnode *pr_exvp;		/* vnode of executing image */
	void	*pr_patch;		/* user space patch pointer handler */
	int	pr_trace_busy;		/* task "tracing" fields busy */
	int 	pr_trace_waiters;	/* threads asleep while trace busy */ 
	tid_t	pr_tid;			/* thread id */
					/* NOTE: pr_tid must be the last
					 * element in this structure. Add any
					 * new elements before it.
					 */
};

typedef struct procfs procfs_t;


/* Structure containing /proc information for each thread and
 * included as part of the thread structure.
 */

struct t_procfs {
	long	pr_flags;		/* /proc status flags */
};

typedef struct t_procfs t_procfs_t;

#endif

#define VNTOPN(vn) ((struct procnode *)(vn)->v_data)

#ifdef _KERNEL
/* "procnode" struct which is included in the vnode at v_data, just like
 * inode for the ufs file system
 */

struct procnode
{
	int	prc_flags;	/* status flags */
	int	prc_pid;	/* pid == file name in /proc */
	pid_t	prc_excl;	/* pid if an exclusive open for write was done*/
	int	prc_exitval;	/* exit status of "traced" process if it exits*/
	unsigned int	prc_wrcnt;	/* # of write opened */
	unsigned int	prc_rdcnt;	/* # of read opened */
	struct queue_entry prc_selq; /* queue haed for select() system call */
	lock_data_t   prc_ioctl_lock;	/* lock for procfs ioctl */
};

/* flag defines for procnode.prc_flags */
#define	PRC_FDINVLD	0x00000001	/* all fd's that refer to this vnode
					 * are invalid */
#define	PRC_DEAD	0x00000002	/* vnode refer to a dead process */
#define	PRC_ISSYS	0x00000004	/* vnode refer to a system process */
#else /* ! _KERNEL */

/*
 * Here defines some obsolete flags that are not used/returned by kernel.
 * They are kept here in case any applications reference them. They are
 * all subject to remove in the future releases.
 */

/* values for old pr_qflags in the procfs structure */
#define PRFS_SCENTER	0x00000001	/* tracing system call on entry */
#define PRFS_SCEXIT	0x00000002	/* tracing system call on exit */
#define PRFS_FAULT	0x00000004	/* tracing fault */
#define PRFS_SIGNAL	0x00000008	/* tracing fault */
#define PRFS_ABORT	0x00000010	/* abort a system call */
#define PRFS_OPEN	0x00000020	/* task/thread is opened by /proc */
#define PRFS_FDINVLD	0x00000040	/* file descriptor invalid */
#define PRFS_EXECED	0x00000080	/* process was exec'd */
#define PRFS_TRACING	0x00000100	/* task open for write -can be traced */
#define PRFS_WASTRACED	0x00004000	/*was traced via /proc, used in psig()*/
#define PRFS_SWEXIT	0x00008000	/* victim in process of exiting */

/*
 * flags used by PIOCGSPCACT and PIOCSSPCACT. To fit these flags to pr_flags,
 * and keep PIOCGSPCACT and PIOCSSPCACT interface, they are difined as
 * following. The only reason is for backward binary compitabilities. The ioctl
 * command PIOCGSPCACT and PIOCSSPCACT will be retired in the future, PIOCSET
 * and PIOCRESET are supported interfaces for set/reset procfs flags.
 */
#define PRFS_STOPFORK	(PR_STOPFORK >> 8)
#define PRFS_STOPEXEC	(PR_STOPEXEC >> 8)
#define PRFS_STOPTERM	(PR_STOPTERM >> 8)
#define PRFS_STOPTCR	(PR_STOPTCR >> 8)
#define PRFS_STOPTTERM	(PR_STOPTTERM >> 8)
#define PRFS_KOLC	(PR_KLC >> 8)

#define PRFS_SPCACTMASK	(PR_SPCACTMASK >> 8)

/* The following obsolete flags were used in pr_flags */
#define PR_TINH		0x00000200 /* task has inherit-on-thread-create flag set */
#define PR_TSTOP	0x00000400 /* a thread has stopped on a thread trace */
#define PR_PNDSTOP	0x00000800 /* task has a stop pending for SIGCONT to see */
#define PR_KILLSIG	0x00001000 /* task was killed via a SIGKILL */
#define PR_STRACE	0x00002000 /* set while task/thread stopped on sig trace */
#define PR_CONTSIG	0x00004000 /* set in trace_sigcont, clr in psig */
#endif

#endif /* _SYS_PROCFS_H_ */
