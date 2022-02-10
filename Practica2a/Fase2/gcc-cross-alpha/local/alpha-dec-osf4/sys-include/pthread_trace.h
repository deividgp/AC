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
 * @(#)$RCSfile: pthread_trace.h,v $ $Revision: 1.1.6.6 $ (DEC) $Date: 1999/02/17 18:46:23 $
 */
/*
 *  FACILITY:
 *
 *	DECthreads POSIX 1003.1c
 *
 *  ABSTRACT:
 *
 *	External definitions for DECthreads tracing functions.
 *
 *				IMPORTANT:
 *				----------
 *
 *	The interfaces defined in this header file are intended for use only
 *	by debuggers and analysis tools. The interfaces WILL change
 *	incompatibly when such changes are necessary to fix problems, or to
 *	improve the exchange of information between debuggers and thread
 *	library.
 *
 *	    ***************************************************
 *	    Do not use the interfaces described in this header
 *	    unless you are prepared to rebuild (and potentially
 *	    recode) on each release of the operating system.
 *	    ***************************************************
 *
 *  AUTHORS:
 *
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	 9 June 1997
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Richard Love
 *	Peter Portante
 *	Webb Scales
 *	Mark Simons
 *
 *  LAST MODIFICATION DATE:
 *
 *	28 January 1999
 */

#ifndef _PTHREAD_TRACE_H_
# define _PTHREAD_TRACE_H_

#ifdef __cplusplus
    extern "C" {
#endif

#include <pthread.h>
#include <signal.h>
#include <stdarg.h>

#ifndef _DECTHREADS_
# error "<pthread_trace.h> depends upon DECthreads internals"
#endif

#if _DECTHREADS_VERSION < 315000L
# error "<pthread_trace.h> requires DECthreads V3.15 or higher"
#endif

#define PTHREAD_TRACE_VERSION	0	/* Current interface version */

/*
 *			GENERAL NOTES ON USING THIS HEADER
 *
 * The header <pthread_trace.h> describes the functional interface and data
 * structures used to communicate with the DECthreads tracing facility. This
 * facility is designed to support the collection of realtime "event" data on
 * the operation of multithreaded programs. Note that, like any method of
 * observation applied to any phenomenon, use of this facility will perturb
 * the execution of the application being observed. This being the case, there
 * can be no guarantee that information abstracted from such analysis will
 * accurately reflect the behavior of the "real" application. Nevertheless, in
 * most cases the information will approximate the real application's behavior
 * closely enough to be of some use.
 */

/*
 * MACROS
 */

/*
 * TYPEDEFS
 */

/*
 * On OpenVMS Alpha, we specify long pointer sizes for all pointers. To make
 * things simple, we just compile the entire header inside an explicit long
 * pointer region. Since this header is used only to build certain types of
 * DEVELOPMENT TOOLS, and is never needed for any end user programs, it's
 * reasonable to require that it be compiled using a recent version of DEC C.
 * (Unfortunately, DEC C++ does not yet support long pointer access on OpenVMS
 * Alpha, and is therefore not supported. DEC C++, or other C++ compilers, may
 * be used on Digital UNIX or OpenVMS VAX.)
 */
#if defined (_PTHREAD_ENV_ALPHA) && defined (_PTHREAD_ENV_VMS)
# ifndef __INITIAL_POINTER_SIZE
#   ifdef __cplusplus
#     error "<pthread_trace.h> requires pointer size support and cannot be used under DEC C++"
#   else
#     error "<pthread_trace.h> requires DEC C version 5.0 or later, with pointer size support"
#   endif
# endif
# pragma __required_pointer_size __save
# pragma __required_pointer_size __long
#endif

/*
 * Define the maximum number of arguments allowed in a single trace record.
 * This is arbitrary, but having a limit makes processing easier.
 */
#define PTHREAD_TRACE_MAXARGS	64

/*
 * Trace event identifier. This can be viewed as either an integer ID, or as
 * a structure consisting of three fields:
 *
 * 1) "object": a byte (8 bits) describing the type of object to which the
 *    event applies. May be taken as an integer code, or as a single ASCII
 *    character.
 * 2) "operation": A word (16 bits) describing the operation applied to an
 *    object. May be taken as an integer code, or as two ASCII characters.
 * 3) "flags": a binary field of 8 flag bits
 *
 * The integer type pthreadTraceEvent_t is the usual representation, but you
 * can use pthreadTraceEventStruct_t to easily extract or view the individual
 * fields.
 */
typedef int pthreadTraceEvent_t;

typedef struct pthreadTraceEventStruct_tag {
    unsigned int	object : 8;		/* The object code */
    unsigned int	operation : 16;		/* The operation code */
    unsigned int	flags : 8;		/* The status flags */
    } pthreadTraceEventStruct_t;

typedef union pthreadTraceEventUnion_tag {
    pthreadTraceEvent_t		mask;
    pthreadTraceEventStruct_t	fields;
    } pthreadTraceEventUnion_t;

/* 
 * Standard event ID object values. Lowercase letters are reserved for user
 * events. A name for these events may be provided by writing an event.setname
 * event with arguments of type OBJECT and NAME. (For example, OBJECT='s',
 * NAME='server').
 */

typedef enum pthreadTraceObject_tag {
    PTHREAD_TRACE_OBJ_ANALYZE	= 'A',	/* Event analysis tool */
    PTHREAD_TRACE_OBJ_COND	= 'C',	/* Condition variable */
    PTHREAD_TRACE_OBJ_EVENT	= 'E',	/* The event stream */
    PTHREAD_TRACE_OBJ_KERNEL	= 'D',	/* DECthreads dispatcher */
    PTHREAD_TRACE_OBJ_KEY	= 'K',	/* Thread-specific data key */
    PTHREAD_TRACE_OBJ_LOCK	= 'L',	/* Read-write lock */
    PTHREAD_TRACE_OBJ_MUTEX	= 'M',	/* Mutex */
    PTHREAD_TRACE_OBJ_ONCE	= 'O',	/* One-time init routine */
    PTHREAD_TRACE_OBJ_PRIVATE	= 'P',	/* DECthreads library generic */
    PTHREAD_TRACE_OBJ_SYSTEM	= 'S',	/* Used to block in system */
    PTHREAD_TRACE_OBJ_THREAD	= 'T',	/* Thread */
    PTHREAD_TRACE_OBJ_USER	= 'U',	/* Generic user event */
    PTHREAD_TRACE_OBJ_VP	= 'V',	/* DECthreads virtual processor */
    PTHREAD_TRACE_OBJ_INTERRUPT	= 'B',	/* Software interrupts (ASTs/Signals) */
    PTHREAD_TRACE_OBJ_EF	= 'F',	/* Event flag upcalls */
    PTHREAD_TRACE_OBJ_EXIT	= 'X',	/* $EXIT/$FORCEX upcalls */
    PTHREAD_TRACE_OBJ_HIBER	= 'H',	/* $HIBER/$WAKE upcalls */
    PTHREAD_TRACE_OBJ_IMS	= 'I',	/* Inner mode semaphore upcalls */
    PTHREAD_TRACE_OBJ_PGFLT	= 'Y',	/* Pagefault upcalls */
    PTHREAD_TRACE_OBJ_notused	= '\0'	/* End of list placeholder */
    } pthreadTraceObject_t;

/*
 * Standard event ID operation values. Codes that begin with a lowercase
 * letter are reserved for user events. A name for these events may be
 * provided by writing an event.setname event with arguments of type OPERATION
 * and NAME. (For example, OPERATION='t', NAME='tune'). User events may also
 * use the standard operation types. (Note: in this list, the indented codes
 * represent convenience aliases to a "base code" -- for example, CREATE is an
 * alias to INIT.)
 */

typedef enum pthreadTraceOperation_tag {
    PTHREAD_TRACE_OP_APPLICATION= 'IA',		/* Application info */
    PTHREAD_TRACE_OP_ASSERT	= 'AS',		/* Assertion check */
    PTHREAD_TRACE_OP_BLOCK	= 'BL',		/* Thread blocking itself */
    PTHREAD_TRACE_OP_CANCEL	= 'CA',		/* pthread_cancel */
    PTHREAD_TRACE_OP_CATCH	= 'CE',		/* Catch DECthreads exception */
    PTHREAD_TRACE_OP_CREATE	= 'IN',		/* Create (alias for INIT) */
    PTHREAD_TRACE_OP_DESTROY	= 'DE',		/* Destroy/Delete */
    PTHREAD_TRACE_OP_DETACH	= 'DT',		/* Detach a thread */
    PTHREAD_TRACE_OP_ENTER	= 'NT',		/* vp.enter */
    PTHREAD_TRACE_OP_EXCEPT	= 'EX',		/* Raise thread exception */
    PTHREAD_TRACE_OP_EXIT	= 'XT',		/* vp.exit/pthread_exit */
    PTHREAD_TRACE_OP_GETPROP	= 'GP',		/* Get object property (TSD) */
    PTHREAD_TRACE_OP_HEADER	= 'HD',		/* event.header (special fmt) */
    PTHREAD_TRACE_OP_IMAGE	= 'II',		/* Binary image info */
    PTHREAD_TRACE_OP_INIT	= 'IN',		/* Initialize/Create */
    PTHREAD_TRACE_OP_JOIN	= 'JN',		/* Join with thread */
    PTHREAD_TRACE_OP_KILL	= 'KI',		/* pthread_kill */
    PTHREAD_TRACE_OP_LOCK	= 'LK',		/* Lock mutex, rwl */
    PTHREAD_TRACE_OP_NULL	= 'NL',		/* No (or generic) operation */
    PTHREAD_TRACE_OP_ONCE	= 'ON',		/* Call to pthread_once */
    PTHREAD_TRACE_OP_PREEMPT	= 'PR',		/* Thread preemption */
    PTHREAD_TRACE_OP_PROCESS	= 'IP',		/* Process info */
    PTHREAD_TRACE_OP_READY	= 'RD',		/* Thread is readied to run */
    PTHREAD_TRACE_OP_RESUME	= 'RE',		/* Resume a thread */
    PTHREAD_TRACE_OP_RUN	= 'RN',		/* Thread is running */
    PTHREAD_TRACE_OP_SETCAN	= 'SC',		/* Set thread cancelation */
    PTHREAD_TRACE_OP_SETNAME	= 'NA',		/* Change name of object */
    PTHREAD_TRACE_OP_SETPROP	= 'SP',		/* Set object property */
    PTHREAD_TRACE_OP_SETSCHED	= 'SD',		/* Set scheduling */
    PTHREAD_TRACE_OP_SIGINT	= 'SI',		/* Signal from interrupt */
    PTHREAD_TRACE_OP_SIGNAL	= 'SG',		/* Signal/broadcast a cond */
    PTHREAD_TRACE_OP_SIGWAIT	= 'SW',		/* sigwait */
    PTHREAD_TRACE_OP_SEARCH	= 'SE',		/* Snoop other VP's ready q's */
    PTHREAD_TRACE_OP_STACKHIGH	= 'SH',		/* Change in stack highwater */
    PTHREAD_TRACE_OP_START	= 'ST',		/* Thread start */
    PTHREAD_TRACE_OP_SUSPEND	= 'SU',		/* Suspend a thread */
    PTHREAD_TRACE_OP_SYSTEM	= 'IS',		/* System info */
    PTHREAD_TRACE_OP_TERM	= 'TR',		/* Thread terminate */
    PTHREAD_TRACE_OP_UNBLOCK	= 'UB',		/* Thread being unblocked */
    PTHREAD_TRACE_OP_UNLOCK	= 'UL',		/* Unlock a mutex or rwl */
    PTHREAD_TRACE_OP_WAIT	= 'WA',		/* Wait for a condition var */
    PTHREAD_TRACE_OP_YIELD	= 'YE'		/* Thread yield */
    } pthreadTraceOperation_t;

/*
 * Event ID status flags:
 */

typedef enum pthreadTraceStatus_tag {
    PTHREAD_TRACE_STAT_FAIL	= 0x01,		/* Operation failed */
    PTHREAD_TRACE_STAT_MULTIPLE	= 0x02,		/* Multiple targets */
    PTHREAD_TRACE_STAT_NONBLOCK	= 0x04,		/* Nonblocking (trylock) */
    PTHREAD_TRACE_STAT_TIMED	= 0x08,		/* Timed operation */
    PTHREAD_TRACE_STAT_USER	= 0x10,		/* pthread_trace_write_np */
    PTHREAD_TRACE_STAT_PRIVATE	= 0x20,		/* DECthreads debug event */
    PTHREAD_TRACE_STAT_CANCEL	= 0x40,		/* Operation cancelled */
    PTHREAD_TRACE_STAT_REQUEST	= 0x80		/* Requesting (part 1) op */
    } pthreadTraceStatus_t;

/*
 * Help in constructing (or deconstructing) event IDs:
 */

#define PTHREAD_TRACE_ID_OBJ_M		0x000000ff /* Mask for OBJECT */
#define PTHREAD_TRACE_ID_OP_M		0x00ffff00 /* Mask for OPERATION */
#define PTHREAD_TRACE_ID_STS_M		0xff000000 /* Mask for STATUS */

#define PTHREAD_TRACE_ID_OBJ_B		0	/* Initial bit for OBJECT */
#define PTHREAD_TRACE_ID_OP_B		8	/* Initial bit for OPERATION */
#define PTHREAD_TRACE_ID_STS_B		24	/* Initial bit for STATUS */

/*
 * This macro constructs an event ID from an object, operation, and status
 * set.
 */
#define pthreadTraceMakeId(_ob,_op,_st) ((((_st<<16)|(_op))<<8)|(_ob))

/*
 * These are the "trace classes" that can be selected for recording and/or
 * analysis.
 */

typedef enum pthreadTraceClass_tag {
    PTHREAD_TRACE_CLASS_COND	= 0x0001,	/* Condition var ops */
    PTHREAD_TRACE_CLASS_ERROR	= 0x0002,	/* Errors */
    PTHREAD_TRACE_CLASS_KEY	= 0x0004,	/* TSD ops */
    PTHREAD_TRACE_CLASS_LOCK	= 0x0008,	/* R/W lock ops */
    PTHREAD_TRACE_CLASS_MUTEX	= 0x0010,	/* Mutex ops */
    PTHREAD_TRACE_CLASS_ONCE	= 0x0020,	/* Once time init */
    PTHREAD_TRACE_CLASS_SCHED	= 0x0040,	/* Scheduling ops */
    PTHREAD_TRACE_CLASS_THREAD	= 0x0080,	/* Thread ops */
    PTHREAD_TRACE_CLASS_USER	= 0x0100,	/* User tracepoints */

    /*
     * Following are INTERNAL to DECthreads, and will result in data that
     * cannot be analyzed by external tools. (Some will not occur except
     * in internal debug builds, for performance reasons.)
     */
    PTHREAD_TRACE_CLASS_ICOND	= 0x00010000,	/* Internal condition */
    PTHREAD_TRACE_CLASS_ILOCK	= 0x00020000,	/* Internal rwlock */
    PTHREAD_TRACE_CLASS_IMUTEX	= 0x00040000,	/* Internal mutex */
    PTHREAD_TRACE_CLASS_ITHREAD	= 0x00080000,	/* Internal thread */
    PTHREAD_TRACE_CLASS_ISCHED	= 0x00100000,	/* Internal scheduling */
    PTHREAD_TRACE_CLASS_IUPCALL	= 0x00200000,	/* Internal upcalls */
    PTHREAD_TRACE_CLASS_IVP	= 0x00400000,	/* Internal vp ops */
    PTHREAD_TRACE_CLASS_IKERNEL	= 0x00800000,	/* Internal kernel ops */
    PTHREAD_TRACE_CLASS_IVPC	= 0x01000000,	/* Internal VP critical */
    PTHREAD_TRACE_CLASS_IMISC	= 0x40000000	/* Others */
    } pthreadTraceClass_t;

#define PTHREAD_TRACE_CLASS_EXTERNALS \
    (PTHREAD_TRACE_CLASS_COND|PTHREAD_TRACE_CLASS_ERROR| \
	    PTHREAD_TRACE_CLASS_KEY|PTHREAD_TRACE_CLASS_LOCK| \
	    PTHREAD_TRACE_CLASS_MUTEX|PTHREAD_TRACE_CLASS_ONCE| \
	    PTHREAD_TRACE_CLASS_THREAD|PTHREAD_TRACE_CLASS_SCHED| \
	    PTHREAD_TRACE_CLASS_USER)
#define PTHREAD_TRACE_CLASS_INTERNALS \
    (PTHREAD_TRACE_CLASS_ICOND|PTHREAD_TRACE_CLASS_ILOCK| \
	    PTHREAD_TRACE_CLASS_IMUTEX|PTHREAD_TRACE_CLASS_ITHREAD| \
	    PTHREAD_TRACE_CLASS_ISCHED|PTHREAD_TRACE_CLASS_IUPCALL| \
	    PTHREAD_TRACE_CLASS_IVP|PTHREAD_TRACE_CLASS_IKERNEL| \
	    PTHREAD_TRACE_CLASS_IVPC|PTHREAD_TRACE_CLASS_IMISC)
#define PTHREAD_TRACE_CLASS_ALL \
	(PTHREAD_TRACE_CLASS_EXTERNALS|PTHREAD_TRACE_CLASS_INTERNALS)

/*
 * These represent the TYPES of data that may appear in a trace record.
 */

typedef enum pthreadTraceType_tag {
				/* INPUT		OUTPUT	FORMAT	*/
    PTHREAD_TRACE_TYPE_UNUSED = 0,
    PTHREAD_TRACE_TYPE_CHAR,	/* char				%c	*/
    PTHREAD_TRACE_TYPE_BOOL,	/* char				TRUE, FALSE */
    PTHREAD_TRACE_TYPE_SHORT,	/* short			%hd	*/
    PTHREAD_TRACE_TYPE_INT,	/* int				%d	*/
    PTHREAD_TRACE_TYPE_LONG,	/* long				%ld	*/
#define PTHREAD_TRACE_TYPE_HEXINT	PTHREAD_TRACE_TYPE_INT
#define PTHREAD_TRACE_TYPE_HEXLONG	PTHREAD_TRACE_TYPE_POINTER
    PTHREAD_TRACE_TYPE_THREADID,/* long			*	thread %ld */
    PTHREAD_TRACE_TYPE_MUTEXID,	/* long			*	mutex %ld */
    PTHREAD_TRACE_TYPE_LOCKID,	/* long			*	rwlock %ld */
    PTHREAD_TRACE_TYPE_CONDID,	/* long			*	cond %ld */
    PTHREAD_TRACE_TYPE_POINTER,	/* void*			%p	*/
    PTHREAD_TRACE_TYPE_ERRNO,	/* int				strerror (%d) */
    PTHREAD_TRACE_TYPE_EXCADDR,	/* void*			%p	*/
    PTHREAD_TRACE_TYPE_EXCSTAT,	/* long				%#lx	*/
    PTHREAD_TRACE_TYPE_THDARG,	/* void*			%#lx	*/
    PTHREAD_TRACE_TYPE_STRING,	/* char*			%s	*/
    PTHREAD_TRACE_TYPE_NAME,	/* char*			%s	*/
    PTHREAD_TRACE_TYPE_BINARY,	/* (void*,long)			%#lx... */
    PTHREAD_TRACE_TYPE_MUTEX,	/* pthread_mutex_t*	long	mutex %ld */
    PTHREAD_TRACE_TYPE_COND,	/* pthread_cond_t*	long	cond %ld */
    PTHREAD_TRACE_TYPE_THREAD,	/* pthread_t		long	thread %ld */
    PTHREAD_TRACE_TYPE_KEY,	/* pthread_key_t	long	key %ld */
    PTHREAD_TRACE_TYPE_LOCK,	/* pthread_rwlock_t*	long	rwlock %ld */
    PTHREAD_TRACE_TYPE_TIME,	/* pthreadTraceTimespec_t*	<UNIX time> */
    PTHREAD_TRACE_TYPE_SCHED,	/* (int, int)			%s, prio %d */
    PTHREAD_TRACE_TYPE_MINIT,	/* pthreadTraceMutexInit_t*	<fields> */
    PTHREAD_TRACE_TYPE_CINIT,	/* pthreadTraceCondInit_t*	<fields> */
    PTHREAD_TRACE_TYPE_TINIT,	/* pthreadTraceThreadInit_t*	<fields> */
    PTHREAD_TRACE_TYPE_KINIT,	/* pthreadTraceKeyInit_t*	<fields> */
    PTHREAD_TRACE_TYPE_LINIT,	/* pthreadTraceRwlockInit_t*	<fields> */
    PTHREAD_TRACE_TYPE_CANCEL,	/* pthreadTraceCancel_t		<bits> */
    PTHREAD_TRACE_TYPE_OBJECT,	/* char				object %1s */
    PTHREAD_TRACE_TYPE_OPERATION, /* int			op %2s */
    PTHREAD_TRACE_TYPE_BLOCK_REASON, /* pthreadTraceBlockReason_t */
    PTHREAD_TRACE_TYPE_ENVIRONMENT, /* pthreadTraceEnvironment_t */
    PTHREAD_TRACE_TYPE_LABEL,	/* char*			%s: */
    PTHREAD_TRACE_TYPE_JAVA_STACK, /* char*			%s */
    PTHREAD_TRACE_TYPE_VP,	/* (vp*)		long	vp %ld */

    /*
     * (*) The MUTEXID, CONDID, LOCKID, and THREADID type codes exist only
     * within the thread library and trace engine. In the output stream (at
     * least for the log engine) they are identical to a MUTEX, COND, LOCK, or
     * THREAD type specified with the address of an object containing the same
     * sequence number. The <obj>ID variants are used when no actual object is
     * available.
     */

    /*
     * The following are types for VT-internal use.
     */
    PTHREAD_TRACE_TYPE_AID = 48,	/* Analysis ID */

    /*
     * Start any additional DECthreads-internal types, which cannot be
     * analyzed by external tracing tools, at value 64 or higher. It would be
     * best to define them to behave like "TYPE_BLOCK", with an explicit size, 
     * so that formatters can easily skip them.
     */

    PTHREAD_TRACE_TYPE_MAX		/* Maximum value (unused) */
    } pthreadTraceType_t, *pthreadTraceType_p;

/*
 * This code is passed to the reinit routine of the active tracing engine
 * (also known as an "event library") so it can deal with a fork.
 */
typedef enum pthreadTraceForkCode_tag {
    PTHREAD_TRACE_REINIT_PREPARE,		/* PREfork, in parent */
    PTHREAD_TRACE_REINIT_PARENT,		/* POSTfork, in parent */
    PTHREAD_TRACE_REINIT_CHILD			/* POSTfork, in child */
    } pthreadTraceForkCode_t;

/*
 * This code is passed to the fini routine of the active tracing engine (also
 * known as an "event library") so it can deal with a flush or shutdown
 * request.
 *
 * PTHREAD_TRACE_FINI_FLUSH is a request to flush volatile data (generally to
 * protect against a process crash).
 *
 * PTHREAD_TRACE_FINI_DESIST is a request to shut down the tracing engine,
 * possibly because another tracing engine has been selected. Usually, the
 * process will continue running, (and this engine may not be called again),
 * so all resources should be deallocated.
 *
 * PTHREAD_TRACE_FINI_TERMINATE is much like DESIST, except that the process
 * is about to terminate. It's not necessary, therefore, to deallocate all
 * resources, since the system will generally handle that anyway. (It's OK to
 * treat TERMINATE and DESIST as the same thing, though.)
 */
typedef enum pthreadTraceFiniCode_tag {
    PTHREAD_TRACE_FINI_FLUSH,			/* Flush buffers, continue */
    PTHREAD_TRACE_FINI_DESIST,			/* Flush and shut down */
    PTHREAD_TRACE_FINI_TERMINATE		/* Process termination */
    } pthreadTraceFiniCode_t;

typedef enum pthreadTraceLockState_tag {
    PTHREAD_TRACE_LOCK_ALL	= 0x1,		/* Full lock */
    PTHREAD_TRACE_LOCK_CANCEL	= 0x2,		/* Lock cancel only */
    PTHREAD_TRACE_LOCK_RESTORE	= 0x10,		/* (internal use only) */
    PTHREAD_TRACE_LOCK_NEST	= 0x20		/* (internal use only) */
    } pthreadTraceLockState_t;

/*
 * This describes the reason why a thread has blocked. (Used by scheduling
 * events.)
 */
typedef enum pthreadTraceBlockFlags_tag {
    PTHREAD_TRACE_BLKFLG_FAULT		= 0x00000001,	/* Pagefault */
    PTHREAD_TRACE_BLKFLG_SYSCALL	= 0x00000002	/* UNIX syscall */
    } pthreadTraceBlockFlags_t;

typedef enum pthreadTraceBlockVariant_tag {
    PTHREAD_TRACE_BLKVAR_OTHER,			/* Unknown */
    PTHREAD_TRACE_BLKVAR_UNIX,			/* Digital UNIX */
    PTHREAD_TRACE_BLKVAR_OPENVMS		/* OpenVMS */
    } pthreadTraceBlockVariant_t;

typedef enum pthreadTraceBlockVMSType_tag {
    PTHREAD_TRACE_BLKVMS_UNKNOWN = 0,		/* Undefined */
    PTHREAD_TRACE_BLKVMS_NONE = 1,		/* No blocking state */
    PTHREAD_TRACE_BLKVMS_SYNC = 2,		/* $SYNC */
    PTHREAD_TRACE_BLKVMS_WFL = 3,		/* Event flag wait */
    PTHREAD_TRACE_BLKVMS_HIBER = 4,		/* $HIBER */
    PTHREAD_TRACE_BLKVMS_IMS = 5,		/* Inner-mode semaphore */
    PTHREAD_TRACE_BLKVMS_PFW = 6,		/* Pagefault wait */
    PTHREAD_TRACE_BLKVMS_WAIT = 7,		/* Mgr/Exit-hndlr thread wait */
    PTHREAD_TRACE_BLKVMS_SETAST = 8		/* $SETAST wait */
    } pthreadTraceBlockVMSType_t;

typedef struct pthreadTraceBlockUNIX_tag {
    __pthreadLongInt_t		habitat;	/* Habitat (if SYSCALL) */
    __pthreadLongInt_t		syscall;	/* Syscall (if SYSCALL) */
    void			*va;		/* Pagefault VA (if FAULT) */
    __pthreadLongUint_t		reserved[3];
    pthreadTraceBlockFlags_t	flags;
    int				reserved1;
    } pthreadTraceBlockUNIX_t, *pthreadTraceBlockUNIX_p;

typedef union pthreadTraceBlockVMS_tag {
    pthreadTraceBlockVMSType_t		type;		/* Type of block */
    struct {
	pthreadTraceBlockVMSType_t	type;		/* Type of block */
	int				efn;		/* Event flag */
	unsigned short			*iosb;		/* IOSB (SYNC only) */
	unsigned short			status;		/* (Generally zero) */
	} sync;
    struct {
	pthreadTraceBlockVMSType_t	type;		/* Type of block */
	int				and;		/* "logical and" wait */
	unsigned int			efm[2];		/* Wait mask */
	} wfl;
    struct {
	pthreadTraceBlockVMSType_t	type;		/* Type of block */
	__pthreadLongUint_t		seq;		/* Sequence # */
	} ims;
    struct {
	pthreadTraceBlockVMSType_t	type;		/* Type of block */
	int				collided;	/* Collided fault */
	__pthreadLongUint_t		va;		/* Address */
	} pfw;
    __pthreadLongUint_t			reserved[7];
    } pthreadTraceBlockVMS_t, *pthreadTraceBlockVMS_p;

typedef struct pthreadTraceBlockOther_tag {
    __pthreadLongUint_t			reserved[7];
    } pthreadTraceBlockOther_t, *pthreadTraceBlockOther_p;

typedef struct pthreadTraceBlockReason_tag {
    pthreadTraceBlockVariant_t	variant;	/* Which OS? */
    union {
	pthreadTraceBlockUNIX_t		unix_info;
	pthreadTraceBlockVMS_t		vms_info;
	pthreadTraceBlockOther_t	other_info;
	} os;
    __pthreadLongUint_t			reserved2;
    } pthreadTraceBlockReason_t, *pthreadTraceBlockReason_p;

/*
 * Identifier of an object -- thread, condition variable, mutex, etc. This
 * is the debug "sequence number" of the object.
 */
typedef __pthreadLongInt_t	pthreadTraceId_t;

/*
 * This is essentially a POSIX "struct timespec", except that it's the same
 * size on both OpenVMS Alpha and Digital UNIX Alpha. Use of this type allows
 * trace log files to be moved between the two platforms.
 */
typedef struct pthreadTraceTimespec_tag {
    __pthreadLongInt_t	tv_sec;
    __pthreadLongUint_t	tv_nsec;
    } pthreadTraceTimespec_t, *pthreadTraceTimespec_p;

/*
 * The Timestamp structure contains 3 fields:
 *
 *	time		standard system time (seconds & nanoseconds since
 *			UNIX Epoch).
 *	toffset		user-mode analogy to the high 32-bits returned by RPCC
 *			on Digital UNIX and OpenVMS. (An adjustment factor for
 *			the time this thread has not been running on the VP.)
 *	cycles		adjusted cycles the VP had run, computed by combining
 *			the two halves of RPCC. (This may be inaccurate on an
 *			SMP, if the kernel thread has moved between
 *			processors.)
 */
typedef struct pthreadTraceTimestamp_tag {
    pthreadTraceTimespec_t time;		/* current clock time */
    int			toffset;		/* Thread cycle offset */
    unsigned int	cycles;			/* Adjusted CPU cycle counter */
    } pthreadTraceTimestamp_t, *pthreadTraceTimestamp_p;

/*
 * The Debugger info structure currently contains two fields
 *
 *	flags		Info flags (PTHREAD_TRACE_INFO_*)
 *	events		The events in which debugger has expressed interest.
 */
typedef enum pthreadTraceDebugInfoFlags_tag {
    PTHREAD_TRACE_INFO_DEBUGGER	= 0x00000001,	/* Debugger attached */
    PTHREAD_TRACE_INFO_MULTIPLE	= 0x00000002	/* Multiple debuggers */
    } pthreadTraceDebugInfoFlags_t;

typedef struct pthreadTraceDebugInfo_tag {
    unsigned long	flags;			/* PTHREAD_TRACE_INFO_* */
    unsigned long	events;			/* as pthreadDebugEventMask_t */
    } pthreadTraceDebugInfo_t, *pthreadTraceDebugInfo_p;

/*
 * Environment block passed to pthread_trace_<name>_init and event.system
 * event.
 */
typedef struct pthreadTraceEnvironment_tag {
    __pthreadLongUint_t	bin_version;		/* Binary DECthreads version */
    char		thread_version[32];	/* ASCII DECthreads version */
    char		os_name[32];		/* ASCII O/S name */
    char		os_release[32];		/* ASCII O/S release */
    char		os_version[32];		/* ASCII O/S version */
    char		hw_name[32];		/* ASCII hardware name */
    char		chip_name[32];		/* ASCII chip name */
    int			cpu_speed;		/* chip speed (cycles/sec) */
    int			cpus_online;		/* CPUs in box */
    int			cpus_active;		/* CPUs in running system */
    __pthreadLongUint_t	memory;			/* Memory (Mb) */
    } pthreadTraceEnvironment_t, *pthreadTraceEnvironment_p;

/*
 * Types describing the information reported about a thread.
 */

typedef enum pthreadTraceCancel_tag {
    PTHREAD_TRACE_CANCEL_PENDING = 0x0001,	/* Cancel is pending */
    PTHREAD_TRACE_CANCEL_STATE   = 0x0002,	/* Cancel enabled */
    PTHREAD_TRACE_CANCEL_SYSTEM  = 0x0004,	/* System cancel enabled */
    PTHREAD_TRACE_CANCEL_TYPE    = 0x0008	/* Cancel async */
    } pthreadTraceCancel_t;

/*
 * Type defining thread "kinds". All threads created by a program through
 * DECthreads interfaces are of kind NORMAL. A debugger should usually show
 * threads of other kinds only when a special switch or mode is used (e.g.,
 * pthread_trace's "thread -a".)
 */
typedef enum pthreadTraceThreadKind_tag {
    PTHREAD_TRACE_THD_KIND_INITIAL	= 1,	/* Initial thread */
    PTHREAD_TRACE_THD_KIND_NORMAL	= 2,	/* Normal thread */
    PTHREAD_TRACE_THD_KIND_NULL		= 3,	/* DECthreads null thread */
    PTHREAD_TRACE_THD_KIND_MGR		= 4,	/* DECthreads manager thread */
    PTHREAD_TRACE_THD_KIND_FOREIGN	= 5,	/* A non-DECthreads NT thread */
    PTHREAD_TRACE_THD_KIND_EXITHAND	= 6	/* The exit handler thread */
    } pthreadTraceThreadKind_t;

/*
 * Creator codes to show whether an thread was created by POSIX, CMA, etc.
 */
typedef enum pthreadTraceCreator_tag {
    PTHREAD_TRACE_CREATOR_NONE		= 0,	/* Unknown */
    PTHREAD_TRACE_CREATOR_POSIX		= 1,	/* POSIX interface */
    PTHREAD_TRACE_CREATOR_CMA		= 2,	/* CMA interface */
    PTHREAD_TRACE_CREATOR_DCE		= 3,	/* vanilla DCE thread */
    PTHREAD_TRACE_CREATOR_DCEEXC	= 4,	/* exception DCE thread */
    PTHREAD_TRACE_CREATOR_TIS		= 5	/* Prototype TIS TEB */
    } pthreadTraceCreator_t;

/*
 * Type defining information reported about a thread's creation.
 *
 * NOTES:
 *
 * 1) The "sequence" field is traditionally reported as a signed number when
 *    the PTHREAD_TRACE_THD_INTERNAL flag is set, even though the sequence
 *    is technically an unsigned number.
 * 2) If the stack was created with a user specified stack ("stackaddr"
 *    attribute), the PTHREAD_TRACE_THD_STACKADDR flag will be set. In this
 *    case, all of the thread's stack information fields, except stack_base,
 *    are guesses, and probably inaccurate. You shouldn't, for example,
 *    compare a later stack highwater mark against stack_reserve to check for
 *    stack overflows. If the stacksize attribute has also been modified in
 *    the attributes object, DECthreads will guess that the creator intended
 *    that as the size of the user stack. Because the standard does not
 *    specify any such relationship, this is still an unreliable guess.
 *    (There's no specific indication that both stackaddr and stacksize were
 *    set. However, if DECthreads must guess, we guess PTHREAD_STACK_MIN. So
 *    it's reasonable for you to guess that, if the stacksize of a user stack
 *    isn't PTHREAD_STACK_MIN, the user also specified a stacksize.)
 *
 *    However, if the flag PTHREAD_TRACE_THD_ESTACKADDR is also set, then the
 *    "extended stackaddr" interface, pthread_setstackaddr_np, was used, which
 *    allows the caller to specify the size and base address. In this case,
 *    all stack information may be considered valid.
 */

#define PTHREAD_TRACE_THD_NAME		0x00000001 /* Name != "<anonymous>" */
#define PTHREAD_TRACE_THD_SYS_SCOPE	0x00000002 /* System contention scope */
#define PTHREAD_TRACE_THD_INTERNAL	0x00000004 /* DECthreads internal */
#define PTHREAD_TRACE_THD_ERROR		0x00000008 /* Init failed */
#define PTHREAD_TRACE_THD_INVATTR	0x00000010 /* ERROR was bad attr. */
#define PTHREAD_TRACE_THD_DETACH	0x00000020 /* Created detached */
#define PTHREAD_TRACE_THD_STACKADDR	0x00000040 /* User stack */
#define PTHREAD_TRACE_THD_ESTACKADDR	0x00000080 /* .. Base and size known */

/*
 * (*) NOSIG and NOSYSCAN will be set for threads created using the LEGACY
 * interfaces (CMA, DCE threads), for binary compatibility with the original
 * implementation that delivered async signals to the initial thread, and
 * that did not support cancellation of syscalls. [Digital UNIX only].
 */

/*
 * NOTE: if the ERROR bit is set in flags, the following fields will be
 * initialized to 0 (NULL): teb, stack_base, stack_reserve, stack_yellow,
 * stack_guard.
 *
 * If the INVATTR flag is also set, the following additional fields will be
 * set to 0: kind, policy, priority, and stack_size.
 */
typedef struct pthreadTraceThreadInit_tag {
    unsigned int	flags;		/* PTHREAD_TRACE_THD_ flags */
    pthreadTraceThreadKind_t kind;	/* Kind of thread */
    pthread_t		teb;		/* Pointer to thread's TEB */
    pthread_t		*handle;	/* "Handle" (where pthread_create
					   stored the TEB pointer) */
    pthread_attr_t	*attributes;	/* Attributes object pointer */
    int			policy;		/* Thread's scheduling policy */
    int			priority;	/* Thread's (base) priority */
    void		*stack_base;	/* Base of thread's stack */
    void		*stack_reserve;	/* First byte of reserved zone */
    void		*stack_yellow;	/* First byte of yellow zone */
    void		*stack_guard;	/* First byte of guard zone */
    __pthreadLongUint_t	stack_size;	/* Total usable stack (bytes) */
    void	      *(*start)(void*); /* Thread start rtn */
    void		*start_arg;	/* Thread start arg */
    __pthreadLongUint_t	cpu_mask;	/* (TBD: some binding ID) */
    pthreadTraceCreator_t creator;	/* Creating interface */
    unsigned int	cancel;		/* Initial cancel state */
    } pthreadTraceThreadInit_t, *pthreadTraceThreadInit_p;

/*
 * Types describing the information reported about a mutex.
 */

typedef enum pthreadTraceMutexType_tag {
    PTHREAD_TRACE_MUT_TYPE_NORMAL	= 1,	/* Normal mutex */
    PTHREAD_TRACE_MUT_TYPE_RECURSIVE	= 2,	/* Recursive mutex */
    PTHREAD_TRACE_MUT_TYPE_ERRORCHECK	= 3	/* Error-check mutex */
    } pthreadTraceMutexType_t;

typedef enum pthreadTraceMutexProtocol_tag {
    PTHREAD_TRACE_MUT_PROTO_NONE	= 1,	/* Normal */
    PTHREAD_TRACE_MUT_PROTO_PROTECT	= 2,	/* Priority ceiling */
    PTHREAD_TRACE_MUT_PROTO_INHERIT	= 3	/* Priority inheritance */
    } pthreadTraceMutexProtocol_t;

#define PTHREAD_TRACE_MUT_NAME		0x00000001  /* Name != "<anonymous>" */
#define PTHREAD_TRACE_MUT_INTERNAL	0x00000002  /* DECthreads internal */
#define PTHREAD_TRACE_MUT_PSHARED	0x00000004  /* "Process shared" */
#define PTHREAD_TRACE_MUT_ERROR		0x00000008  /* Init failed */
#define PTHREAD_TRACE_MUT_INVATTR	0x00000010  /* ERROR was bad attr. */

/*
 * NOTE: if the ERROR bit is set in flags, the following fields will be
 * initialized to 0 (NULL): (n/a)
 *
 * If the INVATTR flag is also set, the following additional fields will be
 * set to 0: type, protocol, prioceiling, priority.
 */
typedef struct pthreadTraceMutexInit_tag {
    unsigned int		flags;		/* Miscellaneous flags */
    pthreadTraceMutexType_t	type;		/* Mutex type */
    pthread_mutex_t		*address;	/* Mutex address */
    pthread_mutexattr_t		*attributes;	/* Attributes object pointer */
    pthreadTraceMutexProtocol_t	protocol;	/* Mutex protocol (nyi) */
    int				prioceiling;	/* Priority ceiling (nyi) */
    int				priority;	/* Current priority (nyi) */
    } pthreadTraceMutexInit_t, *pthreadTraceMutexInit_p;

/*
 * Structure defining information reported about a rwlock initialization, or
 * the first use of a statically initialized rwlock.
 */

#define PTHREAD_TRACE_RW_NAME		0x00000001  /* Name != "<anonymous>" */
#define PTHREAD_TRACE_RW_INTERNAL	0x00000002  /* DECthreads internal */
#define PTHREAD_TRACE_RW_PSHARED	0x00000004  /* "Process shared" */
#define PTHREAD_TRACE_RW_ERROR		0x00000008  /* Init failed */
#define PTHREAD_TRACE_RW_INVATTR	0x00000010  /* ERROR was bad attr. */

typedef struct pthreadTraceRwlockInit_tag {
    unsigned int		flags;		/* Miscellaneous flags */
    pthread_rwlock_t		*address;	/* Rwlock address */
    pthread_rwlockattr_t	*attributes;	/* Attributes object pointer */
    } pthreadTraceRwlockInit_t, *pthreadTraceRwlockInit_p;

/*
 * Structure defining information recorded about a condition variable
 * initialization, or the first use of a statically initialized condition
 * variable.
 */

#define PTHREAD_TRACE_COND_NAME		0x00000001  /* Name != "<anonymous>" */
#define PTHREAD_TRACE_COND_INTERNAL	0x00000002  /* DECthreads internal */
#define PTHREAD_TRACE_COND_PSHARED	0x00000004  /* "Process shared" */
#define PTHREAD_TRACE_COND_ERROR	0x00000008  /* Init failed */
#define PTHREAD_TRACE_COND_INVATTR	0x00000010  /* ERROR was bad attr. */

typedef struct pthreadTraceCondInit_tag {
    unsigned int		flags;		/* Miscellaneous flags */
    pthread_cond_t		*address;	/* Condition address */
    pthread_condattr_t		*attributes;	/* Attributes object pointer */
    } pthreadTraceCondInit_t, *pthreadTraceCondInit_p;

/*
 * Structure defining information recorded about a thread specific data key
 * creation.
 *
 * NOTES:
 *
 * 1) EXTENDED tsd keys have additional semantics. In particular, they may
 *    have a constructor routine (called at thread startup) as well as a
 *    destructor routine (called at thread termination).
 * 2) EXTENDED tsd key destructor routines are called with additional
 *    arguments: as well as the current value of the tsd key in that thread,
 *    they receive the thread ID (pthread_t) and the tsd key itself.
 * 3) EXTENDED tsd keys can be created with the PTHREAD_KEY_ALLTHREAD_NP
 *    flag. The constructor (if any) will immediately be run for each thread
 *    that currently exists. Similarly, when the key is destroyed the
 *    destructor will immediately be run for each thread. Note that the
 *    constructor and destructor are, in these cases, run in the context of
 *    the thread creating or destroying the key, NOT in the context of the
 *    various threads -- thus the constructor and destructor must be carefully
 *    constructed (which is why the behavior is an option).
 * 4) While trace points are defined for changing the value of a thread
 *    specific data key, it is legal and supported for applications to get and
 *    set thread specific data values directly, without calls -- these
 *    operations cannot be traced by DECthreads, and therefore may not
 *    appear in the trace log.
 */
#define PTHREAD_TRACE_KEY_NAME		0x00000001 /* Name != "<anonymous>" */
#define PTHREAD_TRACE_KEY_RESERVED	0x00000002 /* DECthreads reserved */
#define PTHREAD_TRACE_KEY_ALLTHREAD	0x00000004 /* Const/Dest in all thds */
#define PTHREAD_TRACE_KEY_EXTENDED	0x00000008 /* Extended (TLS) key */
#define PTHREAD_TRACE_KEY_ERROR		0x00000010 /* Init failed */

/*
 * NOTE: if the ERROR bit is set in flags, the following fields will be
 * initialized to 0 (NULL): key.
 */
typedef struct pthreadTraceKeyInit_tag {
    unsigned int	flags;		/* Miscellaneous flags */
    pthread_key_t	*address;	/* Address where key was stored */
    __pthreadConstructor_t constructor;	/* Constructor routine */
    union {				/* Destructor routine */
	__pthreadDestructor_t    standard;
	__pthreadExtDestructor_t extended;
	}		destructor;
    } pthreadTraceKeyInit_t, *pthreadTraceKeyInit_p;

/*
 * The pthread_trace_write_np() function can be called by any application code
 * to generate a trace point. Use pthreadTraceMakeId() to create the ID, using
 * the PTHREAD_TRACE_OP_ and PTHREAD_TRACE_STAT_ codes above.
 * PTHREAD_TRACE_OBJ_ codes other than PTHREAD_TRACE_OBJ_USER cannot be used
 * by this interface. Also, you cannot specify the PTHREAD_TRACE_STAT_PRIVATE
 * flag, and PTHREAD_TRACE_STAT_USER will be added to all trace points.
 *
 *	event	event code (pthreadTraceMakeId)
 *	name	optional name string for trace point: uninterpreted, and may
 *		be NULL
 *	count	the number of argument pairs following.
 *	...	each argument consists of two or more values: a
 *		PTHREAD_TRACE_TYPE_ code followed by the arguments for that
 *		type; usually either a scalar value or a pointer.
 *
 * The return value will be ENOSYS if no event engine is loaded. Some engines
 * might report additional errors.
 *
 * NOTE: pthread_trace_write_np is the only function in this header intended
 * for use by application code, rather than by trace engines. The prototype
 * is here, rather than in <pthread.h>, due to the dependency on the event
 * definition and object/operation/status types.
 */
extern int
pthread_trace_write_np (
	pthreadTraceEvent_t,
	const char *,
	int,
	...);

/*
 * Define the programming interfaces.
 *
 * These functions are intended for use by tracing tools, and are not for
 * general use. (They will not be documented outside of this header, and will
 * have limited support.)
 */

/*
 * These typedefs describe the trace engine "hooks", which are called by the
 * DECthreads tracing code.
 *
 * A trace engine has a "name", which is used to construct the actual entry
 * points. The engine is packaged as a shared library with the name
 * libpthreadevent_%s.so, where %s is replaced by the engine name. E.g.,
 * libpthreadevent_vt.so for the Visual Threads engine. Each of the defined
 * entry points is resolved using dlsym() for names also constructed using the 
 * engine name, which will be called using the following typedef prototypes:
 *
 *	pthreadTraceEngineInit_t	pthread_trace_%s_init
 *	pthreadTraceEngineWrite_t	pthread_trace_%s_write
 *	pthreadTraceEngineSetClass_t	pthread_trace_%s_setclass
 *	pthreadTraceEngineFini_t	pthread_trace_%s_fini
 *	pthreadTraceEngineReinit_t	pthread_trace_%s_reinit
 *	pthreadTraceEngineVersion_t	pthread_trace_%s_version
 *
 * The environment in which most of these functions are called is "delicate".
 * They must avoid any thread library calls, in addition to any other calls
 * (such as libc stdio) that might involve synchronization. These are only
 * some of the restrictions. 
 */
typedef int (*pthreadTraceEngineInit_t) (
	pthreadTraceEnvironment_p, int, char**);
typedef int (*pthreadTraceEngineWrite_t) (
	pthreadTraceEvent_t, const char*, pthread_t, int, va_list);
typedef int (*pthreadTraceEngineSetClass_t) (int);
typedef int (*pthreadTraceEngineFini_t) (pthreadTraceFiniCode_t);
typedef int (*pthreadTraceEngineReinit_t) (pthreadTraceForkCode_t);
typedef int (*pthreadTraceEngineVersion_t) (void);

extern int __pthread_trace_getclass (unsigned long *);

extern int __pthread_trace_gettimestamp (
	pthread_t,
	pthreadTraceTimestamp_p);

extern int
__pthread_trace_getdebugger (
	int,
	pthreadTraceDebugInfo_p);

/*
 * Lock out scheduling for the duration of a function that might be a
 * cancellation point, or which might invoke 2-level scheduling. For example,
 * any I/O operation within a tracing engine or ATOM analysis routine should
 * use this function. To restore, call again with the return value:
 *
 *	int lockState;
 *	lockState = _pthread_trace_lock (PTHREAD_TRACE_LOCK_ALL);
 *	[...]
 *	_pthread_trace_lock (lockState);
 *
 * The value of "which" may be PTHREAD_TRACE_LOCK_ALL or
 * PTHREAD_TRACE_LOCK_CANCEL. ("ALL" includes "CANCEL", so there's no need to
 * specify both.)
 */
extern int __pthread_trace_lock (int);

extern int __pthread_trace_toolreport (
	const char *,
	const char *);

extern int __pthread_trace_setclass (unsigned long);

/*
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Information specific to the "log" trace engine that is built into
 * the POSIX thread library.
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

#define PTHREAD_TRACE_LOG_VERSION 5		/* Current version */

#ifdef _PTHREAD_ENV_VMS
# define PTHREAD_TRACE_LOG_BUFSIZE (1<<15)	/* (RMS limitation) */
#else
# define PTHREAD_TRACE_LOG_BUFSIZE (1024*1024)	/* 1Mb buffers */
#endif

/*
 * This is stored at the beginning of a log file: the "magic number". It
 * includes the version of the log engine.
 */

typedef struct pthreadTraceLogFilHdr_tag {
    char	traceMagic[4];		/* "ThTr" */
    char	engine[8];		/* "LOG     " */
    char	version[2];		/* version, "%0.2d" */
    } pthreadTraceLogFilHdr_t, *pthreadTraceLogFilHdr_p;

typedef enum pthreadTraceLogCompress_tag {
    PTHREAD_TRACE_LOG_COMPRESS_NONE = 0,
    PTHREAD_TRACE_LOG_COMPRESS_ZIP  = 1
    } pthreadTraceLogCompress_t;

typedef enum pthreadTraceLogHeadFlags_tag {
    PTHREAD_TRACE_HEAD_SYNC =		0x01,	/* Synch trace (vt only) */
    PTHREAD_TRACE_HEAD_NAME =		0x02,	/* Record has a name */
    PTHREAD_TRACE_HEAD_MOREFRAMES =	0x04	/* Exceeds MAX frame depth */
    } pthreadTraceLogHeadFlags_t;

/*
 * Special case of pthreadTraceLogHead_t. This will always be the first event
 * in a trace buffer. It is uncompressed in a compressed buffer. "Event" and
 * "size" are as in a standard event, but the rest is specialized. The "size"
 * field includes the event itself and the buffer data. That is, for
 * decompression (or processing), you must subtract the size of the event. The
 * "fullsize" field, however, is the size of the uncompressed data, which does
 * not include a header.
 *
 * This is stored at the beginning of each trace buffer written by the builtin
 * "log" trace engine, and is written to the output stream. Buffers may be
 * written out of order. The analyzer must sort them into the proper order (by
 * sequence number) to correctly follow the sequence of events.
 */
typedef struct pthreadTraceLogBufEvt_tag {
    pthreadTraceEvent_t		event;		/* EHD<0> (event.header) */
    unsigned int		size;		/* Size of buffer data. */
    __pthreadLongUint_t		sequence;	/* Buffer's sequence # */
    pthreadTraceLogCompress_t	compression;	/* Compression for buffer */
    unsigned int		fullsize;	/* Uncompressed size */
    } pthreadTraceLogBufEvt_t, *pthreadTraceLogBufEvt_p;

/*
 * The common header of a trace record.
 */
typedef struct pthreadTraceLogHead_tag {
    pthreadTraceEvent_t		event;		/* Trace point identifier */
    unsigned int		size;		/* Size of packet (bytes) */
    pthreadTraceId_t		thread;		/* Thread that logged event */
    __pthreadLongUint_t		sequence;	/* Event sequence number */
    pthreadTraceTimestamp_t	timestamp;      /* Timestamp data */
    unsigned char		flags;		/* Flag bits */
    unsigned char		frames;		/* Number of frames in trace */
    unsigned char		argc;		/* Number of arguments */
    unsigned char		argt[1];	/* Array of argument types */

#ifdef THESE_ARE_FOR_DOCUMENTATION_ONLY

    /*
     * Fields beyond this point cannot be referenced directly. The definitions
     * provide (minimal) documentation of the record's layout.
     *
     * 1) If the PTHREAD_TRACE_HEAD_NAME flag is set, the event's name string
     *    comes next, in the form of a PTHREAD_TRACE_TYPE_STRING argument.
     *
     * 2) Pad to 8 byte alignment.
     *
     * 3) The arguments begin here, one for each element in the argtypes
     *    array. The maximum number of arguments is PTHREAD_TRACE_MAXARGS.
     *    Each argument is naturally aligned for its type.
     *
     * 4) After the final argument, pad to 8-byte alignment for the list of
     *    stack trace PCs. The count of frames is in the "frames" field.
     */

    pthreadLongAddr_t		trace[frames];	/* Stack trace (end) */
#endif
    } pthreadTraceLogHead_t, *pthreadTraceLogHead_p;

/*
 *---------------------------------------------------------------------------
 * End of information specific to the "log" trace engine that is built into
 * the POSIX thread library.
 *---------------------------------------------------------------------------
 */

/*
 * Restore the pointer size environment for VMS
 */
#if defined (_PTHREAD_ENV_ALPHA) && defined (_PTHREAD_ENV_VMS)
# pragma __required_pointer_size __restore
#endif

#ifdef __cplusplus
    }
#endif

#endif /* _PTHREAD_TRACE_H_ */
