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
 * @(#)$RCSfile: pthread_debug.h,v $ $Revision: 1.1.12.5 $ (DEC) $Date: 1999/02/17 18:46:21 $
 */
/*
 * FACILITY:
 *
 *	DECthreads POSIX 1003.1c
 *
 * ABSTRACT:
 *
 *	External definitions for the DECthreads "debug assistant" library
 *	(libpthreaddebug.so on Digital UNIX, or PTHREAD$DBGSHR.EXE on
 *	OpenVMS)
 *
 *				IMPORTANT:
 *				----------
 *
 *	The interfaces defined in this header file are intended for use only
 *	by debuggers or libraries that need to support generalized debugger
 *	access with assistance from DECthreads, such as Ada or C++ tasking
 *	packages.
 *
 * AUTHORS:
 *
 *	Dave Butenhof
 *	Peter Portante
 *
 * CREATION DATE:
 *
 *	16 October 1995
 *
 * MODIFIED BY:
 *
 *	Dave Butenhof
 *	Richard Love
 *	Peter Portante
 *	Tim Rice
 *	Brian Silver
 *	Mark Simons
 *	Mary Sullivan
 *
 * LAST MODIFICATION DATE:
 *
 *	10 February 1999
 */

#ifndef _PTHREAD_DEBUG_H_
# define _PTHREAD_DEBUG_H_

#ifdef __cplusplus
    extern "C" {
#endif

#include <pthread.h>
#include <pthread_trace.h>
#include <signal.h>

#ifndef _DECTHREADS_
# error "<pthread_debug.h> depends upon DECthreads internals"
#endif

#if _DECTHREADS_VERSION < 314000L
# error "<pthread_debug.h> requires DECthreads V3.14 or higher"
#endif

#define PTHREAD_DEBUG_VERSION	2	/* Current interface version */

/*
 *			GENERAL NOTES ON USING THIS HEADER
 *
 * The header <pthread_debug.h> describes the functional interface and data
 * structures used to communicate with the DECthreads debug assistant (we'll
 * generally refer to it as "the assistant").
 *
 * To use the debug assistant, a debugger will compile (one or more modules)
 * with this header file, and link with the assistant library. The facilities
 * in this debugging system are designed to work with a mechanism such as the
 * Digital UNIX "proc" filesystem, or analysis of a saved core file, where the
 * multithreaded process being debugged (the "debuggee", or "target") lives in
 * a separate address space, not directly accessible by the assistant. Thus,
 * all memory references are made through "callbacks" supplied by the "client"
 * debugger (or any analysis tool utilizing this library).
 *
 * *** DECthreads "core" symbol table hook:
 *
 * In order to navigate within the address space of the multithreaded process,
 * the assistant relies on a special "symbol table" linked into the DECthreads
 * library (that is, libpthread.so on Digital UNIX, or PTHREAD$RTL.EXE on
 * OpenVMS). This symbol table, identified by the symbolic name
 * __pthread_dbg_symtable, tells the assistant how to find the various "root"
 * data structures necessary to identify threads, synchronization objects, and
 * other data. The assistant has no direct access to the symbol table of the
 * process being debugged, so it relies on the debugger to supply the address
 * of __pthread_dbg_symtable. The address is one of the arguments to the
 * pthreadDebugContextInit entry point, which must be called before using any
 * other debug assistant functions.
 *
 * It may also be noted that the debugger may look for __pthread_dbg_symtable
 * symbol to determine whether the target process may be multithreaded, before
 * attempting to initialize a debug assistant context for that process. At the
 * very least, be aware that the assistant currently cannot initialize
 * (pthreadDebugContextInit will fail) for any process that does not have a
 * visible __pthread_dbg_symtable symbol. In the future, we will try to work
 * with the kernel and debuggers to devise a better way to "hook" into the
 * target process, and we'd like to remove the need for
 * __pthread_dbg_symtable.
 *
 * *** Object caching and SUSPEND/RESUME callbacks:
 *
 * For efficiency, the assistant caches "objects" that it references in the
 * target process. However, because the target process is asynchronous, and
 * may be running simultaneously in many cases, the assistant cannot count on
 * the data remaining static. Therefore, it generally uses the cache to
 * efficiently LOCATE the remote object, and reads the actual target process
 * memory to "validate" the object. This validation can be avoided if and only
 * if the assistant can know that the process has been unable to run since the
 * object was last validated. It knows this, for example, while the debugger
 * traverses the list of threads, because pthreadDebugThdSeqInit suspends the
 * target process, which is resumed only when pthreadDebugThdSeqDestroy is
 * called. There is an important consequence to this assumption:
 *
 *    Operation in contexts where the assistant has not itself suspended the
 *    process do not assume that the debugger has suspended the target
 *    process. If the debugger wishes to take full advantage of caching in all
 *    contexts, the debugger should always use the pthreadDebugSuspend and
 *    pthreadDebugResume functions -- even though all they do is invoke the
 *    debugger callback. The functions allow the assistant to know when the
 *    debugger has suspended process execution.
 *
 * *** A few words about kernel threads and user threads
 *
 * In general, the debugger should endeavor to ignore kernel threads. It may,
 * however, sometimes be useful to have a mode that works with kernel threads
 * and ignores user threads. You should rarely attempt to deal with both user
 * and kernel threads simultaneously. For example, don't try to hold all other 
 * kernel threads while single stepping a user thread -- instead, hold all
 * other user threads.
 *
 * Beware that procfs may sometimes show a large number of kernel threads.
 * Generally, a DECthreads process will have one kernel thread for each
 * physical processor available to the process, plus one for the internal
 * "manager thread". Threads created in "system contention scope" (SCS) will
 * each have a private kernel thread. There may also be a number of kernel
 * threads that were previously used, and later destroyed. These are cached by
 * the kernel against future need. The kernel cache will be trimmed
 * approximately every 20 seconds by a routine that runs in the context of the
 * DECthreads "manager thread". (Note: the manager thread is used both by the
 * DECthreads library, in user mode context, and by the kernel, in kernel
 * context.)
 *
 * *** Identification of user thread ID from kernel thread:
 *
 * When a debugger takes a trap, it must usually determine the current thread
 * ID. When using the proc filesystem, the debugger can acquire a struct
 * prstatus structure for the current kernel thread, read the pr_teb member,
 * fetch from that address in the target process a block of memory of size
 * "sizeof(struct pthreadTeb_t)", and read the sequence member from the
 * resulting structure. However, there are special cases during process
 * initialization when this method will not work, because the TEB pointer is
 * only set when execution reaches the libc initialization (and is then
 * changed to a "true TEB" when DECthreads is initialized). (Note that in this
 * case, the correct thread ID is always "1".) Instead, you might want to
 * consider using pthreadDebugKidToId, which converts a kernel thread ID to a
 * user thread ID, and let the assistant do all the "grunt work" (even though
 * most of the work is done via the KTHDINFO and GETMEM callbacks). (You could
 * also supply the SPECKTHD callback and use pthreadDebugGetSpecialThread.)
 *
 * *** The SPECKTHD callback:
 *
 * For the most part, SPECKTHD is required only if the debugger plans to
 * utilize the pthreadDebugGetSpecialThread function. However, the assistant
 * will also use SPECKTHD (if available) to enhance the output of the "thread"
 * command (pthreadDebugCmd parser). Specifically, it will display ">" for the
 * current thread and "*" for the trap thread in the "thread -1" columnar
 * output format. It may be used in additional places (if available) for
 * various reasons, but we do not currently expect to require implementation
 * of the SPECKTHD callback.
 *
 * *** Interactions with proc filesystem:
 *
 * When you PRRUN, or PRSTEP, a process, after changing the HOLD state of user
 * mode threads, (especially after HOLDing them), you should always use the
 * additional flag PRRESCHED. This causes the kernel to generate a special
 * upcall for each kernel thread allowing the DECthreads scheduler to preempt
 * the HELD user thread before it can continue executing user instructions.
 * Without PRRESCHED, some HELD threads may continue to run. Also, beware that
 * HOLDing user threads does not work reliably prior to Digital UNIX 4.0D
 * patch kit 3 (released January, 1999).
 *
 * *** Something approximating release notes:
 *
 *    *** V0 interface
 *
 *	The V0 interface was the originally released Debug Assistant, shipped
 *	with Digital UNIX 4.0 and OpenVMS 7.0. There was no public header for
 *	this interface, though the private header was usually known (and
 *	distributed) as <pthdbg.h>.
 *
 *	The V0 PTHREAD_DEBUG_VERSION value was 0x0313c001, rather than 0. This
 *	scheme was scrapped for V1, setting PTHREAD_DEBUG_VERSION to 1.
 *
 *	Many V0 interfaces had substantially different names than the V1 and
 *	later.
 *
 *    *** V1 interface
 *
 *	Released with Digital UNIX 4.0D, OpenVMS 7.2. The <pthread_debug.h>
 *	header is shipped with the O/S kit. (But read the warnings carefully
 *	before using it!)
 *
 *	Many function names were changed for greater consistency, putting all
 *	the "object" designations towards the front. All of the old entry
 *	points remain for binary compatibility.
 *
 *	New callbacks were added: KTHDINFO and SPECKTHD. (Actually, V0 had
 *	defined the KTHDINFO, but hadn't defined the information structure
 *	associated with it.)
 *
 *	Most of the informational structures were changed substantially,
 *	and register info was changed from arrays to structures.
 *
 *	When V0 clients attach to the debug assistant, all input and output
 *	structures are translated to/from V1 internal form.
 *
 *	Porting from V0 to V1 may be a substantial amount of effort, but will
 *	gain significant new information.
 *
 *    *** Digital UNIX 4.0D, patch kit 3
 *
 *	Substantial changes to repair HOLD and UNHOLD, particularly of threads
 *	that may be concurrently executing on another processor. (Though some
 *	race conditions were observed even on a uniprocessor.) As a result,
 *	the behavior of, in particular, the pthreadDebugThdHold function was
 *	substantially changed in many cases. The ESRCH error was introduced to
 *	indicate a TERMINATED thread, which cannot be held. (The ESRCH error
 *	was arguably a bad idea, since it could retroactively change the
 *	behavior of existing V0 and V1 clients. A later release will remedy
 *	this by silently ignoring the TERMINATED thread and returning 0 for
 *	V0 and V1 clients.)
 *
 *   *** Digital UNIX 4.0D, patch kit 3, and OpenVMS 7.2
 *
 *	The SUSPEND and RESUME callbacks, and the WRITE callback, are now
 *	optional, regardless of client interface version. These may be
 *	omitted, for example, when the source of data is a core file, where
 *	those functions have no meaning. (OpenVMS SDA always omits them,
 *	because it supports only an asynchronous read-only connection.) But
 *	beware that some results are unreliable if SUSPEND and RESUME are not
 *	made available for a "live" process, since many operations cannot be
 *	completed "atomically". If you supply SUSPEND or RESUME, you must
 *	supply both.
 *
 *	You need not supply MALLOC or FREE callbacks; malloc and free will be
 *	used directly. If you supply either, you must supply both.
 *
 *    *** V2 interface
 *
 *	Released with Digital UNIX 4.0D, patch kit 4, Compaq Tru64 UNIX 4.0F,
 *	and Tru64 UNIX 5.0.
 *
 *	When you connect to a session with pthreadDebugContextInit, you may
 *	set some flags in the high end of the "version" member in the
 *	pthreadDebugCallbacks_t structure. These flags are defined in the
 *	pthreadDebugInitFlag_t enum, and are documented at the top of this
 *	header file.
 *
 *	New fields were added to the TSD (key address), RWL (writer ID, and
 *	reader count), and THREAD (creator interface) structures. Also, the
 *	THREAD info structure was substantially rearranged to give better
 *	and less ambiguous information about a thread's blocking state. All
 *	blocking state is now segregated into a "block" union containing
 *	appropriate information for each type of blocking state. Note that
 *	the blocking information is now filled in for READY and RUNNING
 *	threads as well as BLOCK threads. When a thread is readied, its prior
 *	blocking state remains until it begins to run, and that information
 *	can sometimes be useful in debugging. (E.g., the ready thread was
 *	previously blocked on condition variable 3.) In some cases when a
 *	thread is interrupted (e.g., by a ^C under ladebug), the blocking
 *	state also remains intact while the thread processes the signal; you
 *	can now see that the current thread was previously blocked, and why.
 *	Also, the kernel blocking state for UNIX, in addition to the habitat
 *	and syscall numbers (which are hard to translate without access to
 *	the OS source code), is now represented as strings. (Note that the
 *	habitat string will be empty if the habitat is 0, the "normal"
 *	habitat; others are named.) The syscall names don't always directly
 *	correspond to the user-visible libc stub names, but most are close
 *	enough to determine what's going on. Also note that the "process
 *	shared" synchronization object blocking functions are reported as
 *	kernel blocking states, but do not have habitat and syscall numbers.
 *
 *	Sequence traversal routines were added for TSD keys. (These routines
 *	can be used by version 0 and version 1 clients, but the entry points
 *	didn't exist on earlier versions of the Debug Assistant and aren't
 *	declared in earlier versions of the header file.)
 *
 *	There are some rudimentary and preliminary routines to process and
 *	format a DECthreads trace stream. Some are currently nonfunctional
 *	(and will fail with ENOSYS). The others are not intended to be
 *	self-evident, and are not well documented. (Even by the loose
 *	standards of this header file.)
 *
 *	There is a new event, TOOLREPORT, which will be used by the Visual
 *	Threads tool to invoke a debugger breakpoint if a debugger is attached
 *	that cares. The first argument is a string to be printed for the user.
 *	The second is a command string. The syntax of the command string is
 *	"undefined", but probably would be based on the ladebug command syntax
 *	and likely ignored by any other debugger. (Note that this event can be
 *	used by version 0 or version 1 clients, but the event will be accepted
 *	only when running with a version 2 Debug Assistant. Some unreleased
 *	version 1 Debug Assistants, such as the one in "Digital UNIX X5.0
 *	EFT1", also recognize this event.)
 *
 *	Correct 4.0D-3's regression in adding ESRCH errors for version 0
 *	clients that attempt to HOLD/UNHOLD terminated threads. Version 0 (and
 *	1) clients will receive the status 0. Version 2 clients will receive
 *	EINVAL.
 *
 *	Version 0 and version 1 interfaces silently ignore HOLD/UNHOLD
 *	requests for internal DECthreads threads. (Those with "negative"
 *	sequence numbers.) Version 2 clients will receive EPERM errors.
 */

/*
 * MACROS
 */

/*
 * The following error numbers (as defined by <errno.h>) may be returned as
 * the value of any debug assistant interface to indicate status. Client
 * callback routines are also expected to report the outcome by returning
 * error numbers. The following are the error numbers used by the assistant,
 * and their usual meaning. Callbacks should follow these guidelines if
 * possible.
 *
 *	ESUCCESS (0)	Successful completion
 *	ENOENT		End of traversal sequence (no more)
 *	ENOTSUP		Function not supported (usually callback error)
 *	EINVAL		Invalid parameter (sometimes, "thread in wrong state")
 *	ESRCH		ID does not represent a thread
 *	ENOMEM		Insufficient memory
 *	EPERM		Unable to perform operation (priv, ownership)
 *	EAGAIN		Operation cannot be performed right now (try again)
 *	ENOSYS		Not supported
 *	EBUSY		Operation cannot be performed: object is busy
 *	ECHILD		Broken association between parts of sync. object
 *	EFAULT		Internal addressing error
 *	EVERSION	Incompatible trace file version
 *	ESHUTDOWN	pthreadDebugCmd("exit")
 *
 * Note that, in most cases, errors returned by a callback routine cause the
 * debug assistant to immediately abort the current operation and return the
 * callback's error status to the client. There are some cases where the debug
 * assistant may be able to continue operation, or attempt an alternative. We
 * recognize that simply passing through the callback status is not
 * necessarily useful or informative to the client, and may cause confusion.
 * This situation, though, is unlikely to change at this late date.
 */

/*
 * These flags can be logically OR-ed into PTHREAD_DEBUG_VERSION (when
 * connecting with the v1 interface or higher) to affect how the connection is
 * made.
 *
 * PTHREAD_DEBUG_FLAG_PASSIVE:
 *
 *	Normally, when a debugger connects, pthreadDebugContextInit writes
 *	into the debuggee process to register the connection. (Tracing tools
 *	can ask about the connection.) Only one debugger (we think) can
 *	usefully attach to a given process: for example, they would need to
 *	coordinate interpretation of the event breakpoints, and any
 *	modifications to the process state.
 *
 *	PTHREAD_DEBUG_FLAG_PASSIVE allows a tool (e.g., VT) to attach without
 *	registering the connection. It's limited to "non-intrusive" changes.
 *	(For example, it cannot enable events.)
 *
 * PTHREAD_DEBUG_FLAG_NOUPDATE:
 *
 *	Normally, when certain queries are made, the debug assistant may
 *	update information in the target process. For example, one of the
 *	thread information fields is a stack highwater mark; this data, part
 *	of the thread control block, is updated by the assistant so that
 *	repeated queries will return more useful information. Setting the
 *	PTHREAD_DEBUG_FLAG_NOUPDATE on connection will prevent these updates.
 *	Note that setting both PASSIVE and NOUPDATE makes the connection
 *	read-only.
 *
 * PTHREAD_DEBUG_FLAG_UPCALLS:
 *
 *	Digital UNIX two-level scheduling involves a special communication
 *	path from the kernel out into the user-mode scheduler, called an
 *	upcall. Although similar in some ways to signal delivery, an upcall is
 *	something different. While the standard exc_remote_virtual_unwind
 *	routine in libc can be used to "walk" a stack containing upcalls, any
 *	debugger that doesn't use this routine, or have similar private logic,
 *	will be unable to find the user program state "underneath" an upcall
 *	frame. Because most existing debuggers do not use the standard
 *	routine, nor have similar logic, programmers may be unable to
 *	determine what a thread is actually doing (the stack traceback will
 *	appear to end at the upcall).
 *
 *	In order to avoid this confusion, the debug assistant, by default (and
 *	unconditionally for debuggers using the original "v0" interface) will
 *	"hide" upcall frames when returning (or setting) registers. Because
 *	the debugger won't see the upcall frames, the programmer won't be
 *	confused. There are complications involved, however, and a debugger
 *	that can support upcall frames may wish to avoid the extra
 *	indirection. (Also, thread library developers are extremely limited by
 *	upcall hiding, because the debugger cannot "see" a large chunk of
 *	thread library code.)
 *
 *	An "upcall-saavy" debugger that won't be confused by upcall frames may
 *	set PTHREAD_DEBUG_FLAG_UPCALLS to prevent the assistant from hiding
 *	upcalls.
 */
typedef enum pthreadDebugInitFlag_tag {
    PTHREAD_DEBUG_FLAG_PASSIVE	= 0x01000000,	/* Limited modification */
    PTHREAD_DEBUG_FLAG_NOUPDATE	= 0x02000000,	/* Read-only */
    PTHREAD_DEBUG_FLAG_UPCALLS	= 0x04000000	/* Debugger Knows Upcalls */
    } pthreadDebugInitFlag_t;

/*
 * TYPEDEFS
 */

/*
 * On OpenVMS Alpha, we specify long pointer sizes for all pointers.  To make
 * things simple, we just compile the entire header inside an explicit long
 * pointer region. Since this is a private (or at least semi-private) header,
 * it's reasonable to require that it be compiled using a recent version of
 * DEC C.
 */
#if defined (_PTHREAD_ENV_ALPHA) && defined (_PTHREAD_ENV_VMS)
# ifndef __INITIAL_POINTER_SIZE
#   ifdef __cplusplus
#     error "<pthread_debug.h> requires pointer size support and cannot be used under DEC C++"
#   else
#     error "<pthread_debug.h> requires DEC C version 5.0 or later, with pointer size support"
#   endif
# endif
# pragma __required_pointer_size __save
# pragma __required_pointer_size __long
#endif

/*
 * User thread IDs, mutex IDs and condition variable IDs are all sequence
 * numbers assigned by the DECthreads library. Each object can be accessed by
 * this number. The IDs for each object are maintained on a per-object basis.
 * So no two objects of the same type will share an ID, but objects of
 * different types may.
 */
typedef long	pthreadDebugId_t;

/*
 * We have this type here to distinguish between IDs which describe user
 * threads and IDs which describe kernel threads.
 */
typedef void	*pthreadDebugKId_t;

/*
 * This type designates an untyped pointer (void*) that will be interpreted as
 * an address in the multithreaded process ("target") that is being debugged,
 * not within the debugger (and debug assistant) address space.
 */
typedef void	*pthreadDebugTargetAddr_t;

/*
 * Type defining floating point and general registers.
 */
#if defined (_PTHREAD_ENV_ALPHA)
typedef struct  pthreadDebugRegs_tag {
    __pthreadLongUint_t	    r0;			/* return value (v0) */
    __pthreadLongUint_t	    r1;			/* callee saved 0 (t0) */
    __pthreadLongUint_t	    r2;			/* callee saved 1 (t1) */
    __pthreadLongUint_t	    r3;			/* callee saved 2 (t2) */
    __pthreadLongUint_t	    r4;			/* callee saved 3 (t3) */
    __pthreadLongUint_t	    r5;			/* callee saved 4 (t4) */
    __pthreadLongUint_t	    r6;			/* callee saved 5 (t5) */
    __pthreadLongUint_t	    r7;			/* callee saved 6 (t6) */
    __pthreadLongUint_t	    r8;			/* callee saved 7 (t7) */
    __pthreadLongUint_t	    r9;			/* caller saved 0 (s0) */
    __pthreadLongUint_t	    r10;		/* caller saved 1 (s1) */
    __pthreadLongUint_t	    r11;		/* caller saved 2 (s2) */
    __pthreadLongUint_t	    r12;		/* caller saved 3 (s3) */
    __pthreadLongUint_t	    r13;		/* caller saved 4 (s4) */
    __pthreadLongUint_t	    r14;		/* caller saved 5 (s5) */
    __pthreadLongUint_t	    r15;		/* caller saved 6 (fp) */
    __pthreadLongUint_t	    r16;		/* argument register 0 (a0) */
    __pthreadLongUint_t	    r17;		/* argument register 1 (a1) */
    __pthreadLongUint_t	    r18;		/* argument register 2 (a2) */
    __pthreadLongUint_t	    r19;		/* argument register 3 (a3) */
    __pthreadLongUint_t	    r20;		/* argument register 4 (a4) */
    __pthreadLongUint_t	    r21;		/* argument register 5 (a5) */
    __pthreadLongUint_t	    r22;		/* callee saved 8 (t8) */
    __pthreadLongUint_t	    r23;		/* callee saved 9 (t9) */
    __pthreadLongUint_t	    r24;		/* callee saved 10 (t10) */
    __pthreadLongUint_t	    r25;		/* callee saved 11 (t11) */
    __pthreadLongUint_t	    r26;		/* return address (ra) */
    __pthreadLongUint_t	    r27;		/* callee saved 12 (t12) */
    __pthreadLongUint_t	    r28;		/* assembler temp (at) */
    __pthreadLongUint_t	    r29;		/* global pointer (gp) */
    __pthreadLongUint_t	    r30;		/* stack pointer (sp) */
    __pthreadLongUint_t	    pc;			/* user-mode PC */
    __pthreadLongUint_t	    ps;			/* processor status */
    } pthreadDebugRegs_t, *pthreadDebugRegs_p;

typedef __pthreadLongUint_t	pthreadDebugRegsArray_t[33];	/* Array version */

typedef struct  pthreadDebugFregs_tag {
    __pthreadLongUint_t	    f0;			/* f0 return value */
    __pthreadLongUint_t	    f1;			/* f1 return value (complex) */
    __pthreadLongUint_t	    f2;			/* callee saved 1 */
    __pthreadLongUint_t	    f3;			/* callee saved 2 */
    __pthreadLongUint_t	    f4;			/* callee saved 3 */
    __pthreadLongUint_t	    f5;			/* callee saved 4 */
    __pthreadLongUint_t	    f6;			/* callee saved 5 */
    __pthreadLongUint_t	    f7;			/* callee saved 6 */
    __pthreadLongUint_t	    f8;			/* callee saved 7 */
    __pthreadLongUint_t	    f9;			/* caller saved 8 */
    __pthreadLongUint_t	    f10;		/* caller saved 0 */
    __pthreadLongUint_t	    f11;		/* caller saved 1 */
    __pthreadLongUint_t	    f12;		/* caller saved 2 */
    __pthreadLongUint_t	    f13;		/* caller saved 3 */
    __pthreadLongUint_t	    f14;		/* caller saved 4 */
    __pthreadLongUint_t	    f15;		/* caller saved 5 */
    __pthreadLongUint_t	    f16;		/* argument register 0 */
    __pthreadLongUint_t	    f17;		/* argument register 1 */
    __pthreadLongUint_t	    f18;		/* argument register 2 */
    __pthreadLongUint_t	    f19;		/* argument register 3 */
    __pthreadLongUint_t	    f20;		/* argument register 4 */
    __pthreadLongUint_t	    f21;		/* argument register 5 */
    __pthreadLongUint_t	    f22;		/* caller saved 6 */
    __pthreadLongUint_t	    f23;		/* caller saved 7 */
    __pthreadLongUint_t	    f24;		/* caller saved 8 */
    __pthreadLongUint_t	    f25;		/* caller saved 9 */
    __pthreadLongUint_t	    f26;		/* caller saved 10 */
    __pthreadLongUint_t	    f27;		/* caller saved 11 */
    __pthreadLongUint_t	    f28;		/* caller saved 12 */
    __pthreadLongUint_t	    f29;		/* caller saved 13 */
    __pthreadLongUint_t	    f30;		/* caller saved 14 */
    __pthreadLongUint_t	    fpcr;		/* FP status register */
    __pthreadLongUint_t	    fp_control;		/* IEEE fp control state */
    } pthreadDebugFregs_t, *pthreadDebugFregs_p;

typedef __pthreadLongUint_t	pthreadDebugFregsArray_t[33];	/* Array version */

#elif defined (_PTHREAD_ENV_VAX)
typedef struct pthreadDebugRegs_tag {
    int		r0;				/* R0 */
    int		r1;				/* R1 */
    int		r2;				/* R2 */
    int		r3;				/* R3 */
    int		r4;				/* R4 */
    int		r5;				/* R5 */
    int		r6;				/* R6 */
    int		r7;				/* R7 */
    int		r8;				/* R8 */
    int		r9;				/* R9 */
    int		r10;				/* R10 */
    int		r11;				/* R11 */
    int		r12;				/* R12 (AP) */
    int		r13;				/* R13 (FP) */
    int		r14;				/* R14 (SP) */
    int		pc;				/* R15 (PC) */
    int		psw;				/* processor status */
    } pthreadDebugRegs_t, *pthreadDebugRegs_p;
typedef pthreadDebugRegs_t	pthreadDebugFregs_t, *pthreadDebugFregs_p;

typedef int pthreadDebugRegsArray_t[17];	/* Array version */

#elif defined (_PTHREAD_ENV_X86)
typedef struct  pthreadDebugRegs_tag {
	DWORD	EAX;		/* DS(default) - 32bit - data register */
	DWORD	EBX;		/* DS(default) - 32bit - data register */
	DWORD	ECX;		/* DS(default) - 32bit - data register */
	DWORD	EDX;		/* DS(default) - 32bit - data register */
	DWORD	EBP;		/* SS(default) - 32bit - stack frame base */
	DWORD	ESI;		/* DS(default) - 32bit - data register */
	DWORD	EDI;		/* ES(default) - 32bit - data register */
	DWORD	ESP;		/* SS(default) - 32bit - stack frame pointer */
	DWORD	CS;		/* 16bit - code segment selector */
	DWORD	SS;		/* 16bit - stack segment selector */
	DWORD	DS;		/* 16bit - main data segment selector */
	DWORD	ES;		/* 16bit - string/data segment selector */
	DWORD	FS;		/* 16bit - optional data segment selector */
	DWORD	GS;		/* 16bit - optional data segment selector */
	DWORD	EFLAGS;		/* 32bit - condition/mode flags register */
	DWORD	EIP;		/* CS - 32bit - instruction pointer */
    } pthreadDebugRegs_t, *pthreadDebugRegs_p;
typedef pthreadDebugRegs_t	pthreadDebugFregs_t, *pthreadDebugFregs_p;

typedef DWORD	pthreadDebugRegsArray_t[16];	/* Array version */
typedef DWORD	pthreadDebugFregsArray_t[16];	/* Array version */

#else
# error "<pthread_debug.h> cannot be used in this environment"
#endif

/*
 * Debug assistant context type. This opaque value is returned by the
 * pthreadDebugContextInit() routine.
 */
typedef void*	pthreadDebugContext_t;
typedef void**	pthreadDebugContext_p;

/*
 * "Caller context" argument. A value of this type is specified when creating
 * a new debug context with pthreadDebugContextInit, and is passed by the
 * assistant to each client callback routine.
 */
typedef void*	pthreadDebugClient_t;

/*
 * Type defining "special thread" codes (SPECKTHD callback)
 *
 *	CURRENT		The thread being observed. (Debuggers usually have
 *			commands to switch between threads, for example, to
 *			see the stack and registers of various threads.)
 *	TRAP		The thread that caused the most recent debugging
 *			event -- breakpoint, hardware fault, etc.
 */
typedef enum pthreadDebugSpecialType_tag {
    PTHREAD_DEBUG_SPECIAL_TYPE_CURRENT	= 1,	/* Thread being observed */
    PTHREAD_DEBUG_SPECIAL_TYPE_TRAP	= 2	/* Thread that trapped */
    } pthreadDebugSpecialType_t;

/*
 * Type defining thread state.
 *
 *	UNKNOWN		The state can't be determined. (This should never
 *			happen.)
 *	RUNNING		Thread is currently executing on some processor.
 *	READY		Thread is not currently running, but is eligible to
 *			run when a processor becomes available.
 *	BLOCKED		Thread is waiting for some event (beyond its control)
 *			to occur before it can run. The SUBSTATE provides
 *			details about why it is waiting.
 *	NEW		A transitional state -- a newly created thread that
 *			hasn't yet been made READY.
 *	SORTING		Another transitional -- the thread has been removed
 *			from a ready queue briefly for some internal
 *			bookkeeping operation, and will shortly be made READY
 *			again.
 *	TERMINATED	The thread is no longer running, but has not yet
 *			been DETACHED.
 *	ZOMBIE		A transitional state -- the thread has terminated, and
 *			been detached, but all resources haven't yet been
 *			disposed.
 */
typedef enum pthreadDebugState_tag {
    PTHREAD_DEBUG_STATE_UNKNOWN		= 0,	/* Unknown (bad) state */
    PTHREAD_DEBUG_STATE_RUNNING		= 1,	/* Running on kernel thread */
    PTHREAD_DEBUG_STATE_READY		= 2,	/* Ready to run */
    PTHREAD_DEBUG_STATE_BLOCKED		= 3,	/* Blocked on some object */
    PTHREAD_DEBUG_STATE_NEW		= 4,	/* Just created not readied */
    PTHREAD_DEBUG_STATE_SORTING		= 5,	/* Sort scheduler database */
    PTHREAD_DEBUG_STATE_TERMINATED	= 6,	/* Not eligible to run */
    PTHREAD_DEBUG_STATE_ZOMBIE		= 7	/* Waiting to be reclaimed */
    } pthreadDebugState_t;

/*
 * Type defining thread substate.  For example, if the state is blocked,
 * substate gives additional information about current state or recent
 * transition.
 */
typedef enum pthreadDebugSubstate_tag {
    PTHREAD_DEBUG_SUBSTATE_UNKNOWN	= 0,	/* Unknown (bad) substate */
    PTHREAD_DEBUG_SUBSTATE_NORMAL	= 1,	/* No additional information */
    PTHREAD_DEBUG_SUBSTATE_UNBLOCK_PEND	= 2,	/* Kernel unblock pending */
    PTHREAD_DEBUG_SUBSTATE_KERNEL	= 3,	/* Blocked in the kernel */
    PTHREAD_DEBUG_SUBSTATE_MUTEX	= 4,	/* Blocked on a mutex */
    PTHREAD_DEBUG_SUBSTATE_CV		= 5,	/* Blocked on a cv */
    PTHREAD_DEBUG_SUBSTATE_TIMED_CV	= 6,	/* Blocked on a timed cv */
    PTHREAD_DEBUG_SUBSTATE_TERM_CANCEL	= 7,	/* Terminating from a cancel */
    PTHREAD_DEBUG_SUBSTATE_TERM_EXIT	= 8,	/* Terminating normally */
    PTHREAD_DEBUG_SUBSTATE_DELAY	= 9,	/* Blocked for a delay */
    PTHREAD_DEBUG_SUBSTATE_JOIN		= 10,	/* Blocked for a join */
    PTHREAD_DEBUG_SUBSTATE_START	= 11,	/* Thread just started */
    PTHREAD_DEBUG_SUBSTATE_SYNCSUSP	= 12,	/* Waiting for suspend */
    PTHREAD_DEBUG_SUBSTATE_READLOCK	= 13,	/* Thread is wating on rdlock */
    PTHREAD_DEBUG_SUBSTATE_WRITELOCK	= 14	/* Thread is wating on wrlock */
    } pthreadDebugSubstate_t;

/*
 * Type defining thread "kinds". All threads created by a program through
 * DECthreads interfaces are of kind NORMAL. A debugger should usually show
 * threads of other kinds only when a special switch or mode is used (e.g.,
 * pthread_debug's "thread -a".)
 */
typedef enum pthreadDebugThreadKind_tag {
    PTHREAD_DEBUG_THD_KIND_INITIAL	= 1,	/* Initial thread */
    PTHREAD_DEBUG_THD_KIND_NORMAL	= 2,	/* Normal thread */
    PTHREAD_DEBUG_THD_KIND_NULL		= 3,	/* DECthreads null thread */
    PTHREAD_DEBUG_THD_KIND_MGR		= 4,	/* DECthreads manager thread */
    PTHREAD_DEBUG_THD_KIND_FOREIGN	= 5,	/* A non-DECthreads NT thread */
    PTHREAD_DEBUG_THD_KIND_EXITHAND	= 6	/* The exit handler thread */
    } pthreadDebugThreadKind_t;

/*
 * Type defining the possible thread creators. You can use this information to 
 * determine whether the thread was created using the POSIX interface, one of
 * the (retired) DCE thread interfaces, or the (obsolete) CMA interface.
 */
typedef enum pthreadDebugThreadCreator_tag {
    PTHREAD_DEBUG_THD_CREATOR_POSIX	= 1,
    PTHREAD_DEBUG_THD_CREATOR_CMA	= 2,
    PTHREAD_DEBUG_THD_CREATOR_DCE	= 3,
    PTHREAD_DEBUG_THD_CREATOR_DCEEXC	= 4,
    PTHREAD_DEBUG_THD_CREATOR_TIS	= 5
    } pthreadDebugThreadCreator_t;

/*
 * Definitions for user mode and kernel mode blocking information.
 */
typedef enum pthreadDebugThdBlkType_tag {
    PTHREAD_DEBUG_THDBLK_BADVALUE	= 0,	/* Unknown, N/A */
    PTHREAD_DEBUG_THDBLK_NONE		= 1,	/* No blocking state */
    PTHREAD_DEBUG_THDBLK_MUTEX		= 2,	/* Mutex blocks */
    PTHREAD_DEBUG_THDBLK_COND		= 3,	/* Condition variable blocks */
    PTHREAD_DEBUG_THDBLK_DELAY		= 4,	/* pthread_delay_np */
    PTHREAD_DEBUG_THDBLK_RWL		= 5,	/* Readers/Writer lock blocks */
    PTHREAD_DEBUG_THDBLK_JOIN		= 6,	/* Join waits */
    PTHREAD_DEBUG_THDBLK_SUSPSYNC	= 7,	/* Suspend waits */
    PTHREAD_DEBUG_THDBLK_KERNEL		= 8	/* Kernel block */
    } pthreadDebugThdBlkType_t;

#ifdef _PTHREAD_ENV_UNIX
# define PTHREAD_DEBUG_KRNBFLG_FAULT	0x00000001	/* Pagefault */
# define PTHREAD_DEBUG_KRNBFLG_SYSCALL	0x00000002	/* Syscall */

typedef struct pthreadDebugThdKrnBlk_tag {
    pthreadDebugThdBlkType_t	type;		/* Union descriminator */
    long			flags;		/* Blocking flags */
    long			habitat;	/* Habitat (if SYSCALL) */
    long			syscall;	/* Syscall (if SYSCALL) */
    pthreadDebugTargetAddr_t	va;		/* Pagefault VA (if FAULT) */
    char			habitat_nm[8];	/* Habitat name (not hab 0) */
    char			syscall_nm[24];	/* Syscall name (if SYSCALL) */
    } pthreadDebugThdKrnBlk_t, *pthreadDebugThdKrnBlk_p;
#elif defined (_PTHREAD_ENV_VMS)
# define PTHREAD_DEBUG_KRNBFLG_WFLAND	0x00000001 /* SYS$WFLAND */
# define PTHREAD_DEBUG_KRNBFLG_COLLIDED	0x00000002 /* PFW collided */

typedef enum pthreadDebugKrnBlkType_tag {
    PTHREAD_DEBUG_KRNBLKTYPE_UNKNOWN = 0,	/* Undefined */
    PTHREAD_DEBUG_KRNBLKTYPE_NONE = 1,		/* No blocking state */
    PTHREAD_DEBUG_KRNBLKTYPE_SYNC = 2,		/* $SYNC */
    PTHREAD_DEBUG_KRNBLKTYPE_WFL = 3,		/* Event flag wait */
    PTHREAD_DEBUG_KRNBLKTYPE_HIBER = 4,		/* $HIBER */
    PTHREAD_DEBUG_KRNBLKTYPE_IMS = 5,		/* Inner-mode semaphore */
    PTHREAD_DEBUG_KRNBLKTYPE_PFW = 6		/* Pagefault wait */
    } pthreadDebugKrnBlkType_t;

typedef struct pthreadDebugThdKrnBlk_tag {
    pthreadDebugThdBlkType_t	type;		/* Union descriminator */
    long			flags;		/* Flags */
    pthreadDebugKrnBlkType_t	ktype;		/* Type of kernel block */
    union {
	struct {
	    unsigned short	*iosb;		/* IOSB (SYNC only) */
	    int			efn;		/* Event flag (SYNC only) */
	    } sync;
	unsigned int		mask[2];	/* Wait mask (WFL only) */
	unsigned long		seq;		/* Sequence # (IMS only) */
	__pthreadLongUint_t	va;		/* Address (PFW only) */
	} detail;
    } pthreadDebugThdKrnBlk_t, *pthreadDebugThdKrnBlk_p;
#else
typedef struct pthreadDebugThdKrnBlk_tag {
    pthreadDebugThdBlkType_t	type;		/* Union descriminator */
    long			flags;		/* Blocking flags */
    } pthreadDebugThdKrnBlk_t, *pthreadDebugThdKrnBlk_p;
#endif

/*
 * Information about the blocking state of a thread.
 */
typedef union pthreadDebugThdBlkInfo_tag {
    pthreadDebugThdBlkType_t	type;	/* Union descriminator */
    struct {
	pthreadDebugThdBlkType_t type;	/* Union descriminator */
	pthreadDebugId_t	mutex;	/* Mutex */
	} mutex;
    struct {
	pthreadDebugThdBlkType_t type;	/* Union descriminator */
	pthreadDebugId_t	cond;	/* Condition variable */
	pthreadDebugId_t	mutex;	/* Associated mutex */
	struct timespec		timeout;/* Timeout */
	} cond;
    struct {
	pthreadDebugThdBlkType_t type;	/* Union descriminator */
	struct timespec		timeout;/* Timeout */
	} delay;
    struct {
	pthreadDebugThdBlkType_t type;	/* Union descriminator */
	pthreadDebugId_t	rwlock;	/* read-write lock */
	} rwlock;
    struct {
	pthreadDebugThdBlkType_t type;	/* Union descriminator */
	pthreadDebugId_t	thread;	/* Join thread */
	} join;
    struct {
	pthreadDebugThdBlkType_t type;	/* Union descriminator */
	pthreadDebugId_t	thread;	/* suspending thread */
	} suspsync;
    pthreadDebugThdKrnBlk_t	kernel;	/* O/S-specific kernel blocking info */
    } pthreadDebugThdBlkInfo_t, *pthreadDebugThdBlkInfo_p;

/*
 * Type defining information returned about a thread.
 *
 * NOTES:
 *
 * 1) The "sequence" field is traditionally reported as a signed number when
 *    the PTHREAD_DEBUG_THD_INTERNAL flag is set, even though the sequence
 *    number is unsigned.
 * 2) Even when the state is "RUNNING", the thread may have a substate of
 *    "MUTEX", "CV", "TIMED_CV", etc. In such case, the "condition" and/or
 *    "mutex" fields (Id of the synchronization object on which the thread is
 *    waiting) MAY or MAY NOT be non-zero. This situation means that the
 *    thread is "about to wait" or "in the process of waking".
 * 3) The "locks" field can count only the non-default mutex types held by the
 *    thread -- recursive or errorcheck mutexes, pshared mutexes, and priority
 *    inheritance or priority ceiling mutexes. The thread may additionally
 *    hold any number of default (NORMAL) mutexes.
 * 4) If the stack was created with a user specified stack ("stackaddr"
 *    attribute), the PTHREAD_DEBUG_THD_STACKADDR flag will be set. In this
 *    case, all of the thread's stack information fields, except stack_base
 *    and stack_hiwater, are guesses, and probably inaccurate. You shouldn't,
 *    for example, compare stack_hiwater against stack_reserve to check for
 *    stack overflows. If the stacksize attribute has also been modified in
 *    the attributes object, DECthreads will guess that the creator intended
 *    that as the size of the user stack. Because the standard does not
 *    specify any such relationship, this is still an unreliable guess.
 *    (There's no specific indication that both stackaddr and stacksize were
 *    set. However, if DECthreads must guess, we guess PTHREAD_STACK_MIN. So
 *    it's reasonable for you to guess that, if the stacksize of a user stack
 *    isn't PTHREAD_STACK_MIN, the user also specified a stacksize.)
 *
 *    However, if the flag PTHREAD_DEBUG_THD_ESTACKADDR is also set, then the
 *    "extended stackaddr" interface, pthread_setstackaddr_np, was used, which
 *    allows the caller to specify the size and base address. In this case,
 *    all stack information may be considered valid.
 */

#define PTHREAD_DEBUG_THD_CANCEL	0x00000001 /* Cancel pending */
#define PTHREAD_DEBUG_THD_CAN_ENABLED	0x00000002 /* Cancel enabled */
#define PTHREAD_DEBUG_THD_CAN_ASYNC	0x00000004 /* Async cancel enabled */
#define PTHREAD_DEBUG_THD_CAN_SYSTEM	0x00000008 /* System cancel enabled */
#define PTHREAD_DEBUG_THD_NAME		0x00000010 /* Name != "<anonymous>" */
#define PTHREAD_DEBUG_THD_SYS_SCOPE	0x00000020 /* System contention scope */
#define PTHREAD_DEBUG_THD_INTERNAL	0x00000040 /* DECthreads internal */
#define PTHREAD_DEBUG_THD_HOLD		0x00000080 /* Thread is HELD */
#define PTHREAD_DEBUG_THD_SUSPEND	0x00000100 /* Thread is SUSPENDED */
#define PTHREAD_DEBUG_THD_JOINER	0x00000200 /* A thread is joining */
#define PTHREAD_DEBUG_THD_STACKADDR	0x00000400 /* User stack */
#define PTHREAD_DEBUG_THD_ESTACKADDR	0x00000800 /* User stack with size */

typedef struct pthreadDebugThreadInfo_tag {
    unsigned long	flags;		/* PTHREAD_DEBUG_THD_ flags */
    pthreadDebugState_t	state;		/* Current scheduler state */
    pthreadDebugSubstate_t substate;	/* Current scheduler substate */
    pthreadDebugThreadKind_t kind;	/* Kind of thread */
    pthreadDebugThreadCreator_t creator;/* The creating interface */
    int			sched_policy;	/* Thread's scheduling policy */
    int			base_priority;	/* Thread's (base) priority */
    int			cur_priority;	/* Thread's (current) priority */
    pthreadDebugId_t	sequence;	/* Sequence number */
    pthread_t		teb;		/* Pointer to thread's TEB */
    pthread_t		*handle;	/* "Handle" (where pthread_create
					   stored the TEB pointer) */
    void		*stack_base;	/* Base of thread's stack */
    void		*stack_reserve;	/* First byte of reserved zone */
    void		*stack_yellow;	/* First byte of yellow zone */
    void		*stack_guard;	/* First byte of guard zone */
    void		*stack_hiwater;	/* Stack's "highwater mark" */
    unsigned long	stack_size;	/* Total size of stack */
    pthreadDebugThdBlkInfo_t block;	/* Detailed blocking info */
    void	      *(*start)(void*); /* Thread start rtn */
    void		*start_arg;	/* Thread start arg */
    void		*result;	/* TERMINATED: Thread result */
    struct timespec	cpu_time;	/* Accumulated CPU time (nyi) */
    unsigned long	sig_block;	/* Blocked signal mask (UNIX only) */
    unsigned long	sig_pend;	/* Pending signal mask (UNIX only) */
    int			locks;		/* Number of owned locks (if known) */
    int			thd_errno;	/* Last known errno */
    char		name[32];	/* Thread's name */
    } pthreadDebugThreadInfo_t, *pthreadDebugThreadInfo_p;

/*
 * Type defining information returned about a kernel thread. The flags
 * are set by the callback to specify which fields are valid, in case some
 * information is unavailable (e.g., from a core file). Note that STATE and
 * TEB are always required.
 */

#define PTHREAD_DEBUG_KTD_POLICY	0x00000001 /* sched_policy valid */
#define PTHREAD_DEBUG_KTD_BPRIO		0x00000002 /* base_priority valid */
#define PTHREAD_DEBUG_KTD_CPRIO		0x00000004 /* cur_priority valid */
#define PTHREAD_DEBUG_KTD_SUSPCNT	0x00000008 /* suspend_count valid */
#define PTHREAD_DEBUG_KTD_SIGBLK	0x00000010 /* sig_block valid */
#define PTHREAD_DEBUG_KTD_SIGPND	0x00000020 /* sig_pend valid */
#define PTHREAD_DEBUG_KTD_SLEEP		0x00000040 /* sleep_time valid */
#define PTHREAD_DEBUG_KTD_WAIT		0x00000080 /* wait_event valid */
#define PTHREAD_DEBUG_KTD_USER		0x00000100 /* user_time valid */
#define PTHREAD_DEBUG_KTD_SYSTEM	0x00000200 /* system_time valid */
#define PTHREAD_DEBUG_KTD_SCHCLS	0x00000400 /* sched_class valid */

#ifdef _PTHREAD_ENV_UNIX
typedef enum pthreadDebugKState_tag {
    PTHREAD_DEBUG_KSTATE_UNKNOWN	= 0,	/* Unknown (bad) state */
    PTHREAD_DEBUG_KSTATE_RUNNING	= 1,	/* Running */
    PTHREAD_DEBUG_KSTATE_STOPPED	= 2,	/* Stopped */
    PTHREAD_DEBUG_KSTATE_WAITING	= 3,	/* Waiting normally */
    PTHREAD_DEBUG_KSTATE_UINT_WAITING	= 4,	/* Uninterruptible wait */
    PTHREAD_DEBUG_KSTATE_HALTED		= 5	/* Halted cleanly */
    } pthreadDebugKState_t;

typedef struct pthreadDebugKThreadInfo_tag {
    unsigned long	flags;		/* Miscellaneous flags */
    pthreadDebugKState_t state;		/* Current scheduler state */
    pthread_t		teb;		/* Current user thread TEB */
    int			sched_policy;	/* Thread scheduling policy */
    int			base_priority;	/* Thread base priority */
    int			cur_priority;	/* Thread current priority */
    int			suspend_count;	/* Mach suspend count */
    sigset_t		sig_block;	/* Current blocked signals */
    sigset_t		sig_pend;	/* Current pending signals */
    long		sleep_time;	/* Second thread has been sleeping */
    long		wait_event;	/* Event on which thread is waiting */
    struct timespec	user_time;	/* Accumulated user CPU time */
    struct timespec	system_time;	/* Accumulated system CPU time */
    char		sched_class[8];	/* Scheduling class name */
    long		reserved[10];	/* Expansion space */
    } pthreadDebugKThreadInfo_t, *pthreadDebugKThreadInfo_p;
#else
/*
 * FIX-ME: Don't take this too literally yet.
 */
typedef enum pthreadDebugKState_tag {
    PTHREAD_DEBUG_KSTATE_RUNNING	= 1,	/* Running */
    PTHREAD_DEBUG_KSTATE_STOPPED	= 2,	/* Stopped */
    PTHREAD_DEBUG_KSTATE_WAITING	= 3	/* Waiting normally */
    } pthreadDebugKState_t;

typedef struct pthreadDebugKThreadInfo_tag {
    unsigned long	flags;		/* Miscellaneous flags */
    pthreadDebugKState_t state;		/* Current scheduler state */
    int			sched_policy;	/* Thread scheduling policy */
    int			base_priority;	/* Thread base priority */
    int			cur_priority;	/* Thread current priority */
    long		wait_event;	/* Event on which thread is waiting */
    pthread_t		teb;		/* Current user thread TEB */
    struct timespec	user_time;	/* Accumulated user CPU time */
    struct timespec	system_time;	/* Accumulated system CPU time */
    char		sched_class[8];	/* Scheduling class name */
    long		reserved[10];	/* Expansion space */
    char		name[32];	/* Thread's name */
    } pthreadDebugKThreadInfo_t, *pthreadDebugKThreadInfo_p;
#endif

typedef enum pthreadDebugMutexType_tag {
    PTHREAD_DEBUG_MUT_TYPE_NORMAL	= 1,	/* Normal mutex */
    PTHREAD_DEBUG_MUT_TYPE_RECURSIVE	= 2,	/* Recursive mutex */
    PTHREAD_DEBUG_MUT_TYPE_ERRORCHECK	= 3	/* Error-check mutex */
    } pthreadDebugMutexType_t;

typedef enum pthreadDebugMutexProtocol_tag {
    PTHREAD_DEBUG_MUT_PROTO_NONE	= 1,	/* Normal */
    PTHREAD_DEBUG_MUT_PROTO_PROTECT	= 2,	/* Priority ceiling */
    PTHREAD_DEBUG_MUT_PROTO_INHERIT	= 3	/* Priority inheritance */
    } pthreadDebugMutexProtocol_t;

/*
 * Type defining information returned about a mutex.
 *
 * NOTES:
 *
 * 1) When a mutex is STATICALLY initialized using PTHREAD_MUTEX_INITIALIZER
 *    (or equivalent) and has not yet been used to BLOCK a thread, the mutex
 *    does not have a sequence number. It is not visible in a
 *    pthreadDebugMutSeq* traversal, or to pthreadDebugMutGetInfo, and its
 *    name cannot be set using pthreadDebugMutSetName. In this case, the
 *    "sequence" member of the pthreadDebugMutexInfo_t structure will have the
 *    value 0. The value 0 is never a valid sequence number, so there is no
 *    ambiguity. You can only examine the state of these mutexes using
 *    pthreadDebugMutGetInfoAddr.
 */

#define PTHREAD_DEBUG_MUT_NAME		0x00000001  /* Name != "<anonymous>" */
#define PTHREAD_DEBUG_MUT_LOCKED	0x00000002  /* Currently locked */
#define PTHREAD_DEBUG_MUT_WAITERS	0x00000004  /* There are waiters */
#define PTHREAD_DEBUG_MUT_METERED	0x00000008  /* Mutex has meter info */
#define PTHREAD_DEBUG_MUT_INTERNAL	0x00000010  /* DECthreads internal */
#define PTHREAD_DEBUG_MUT_PSHARED	0x00000020  /* "Process shared" */

typedef struct pthreadDebugMutexInfo_tag {
    unsigned long		flags;		/* Miscellaneous flags */
    pthreadDebugMutexType_t	type;		/* Mutex type */
    pthreadDebugId_t		owner;		/* Current owner (if known) */
    pthreadDebugId_t		sequence;	/* Sequence number */
    pthread_mutex_t		*address;	/* Mutex address */
    pthreadDebugMutexProtocol_t	protocol;	/* Mutex protocol (nyi) */
    int				prioceiling;	/* Priority ceiling (nyi) */
    int				priority;	/* Current priority (nyi) */
    long			reserved[10];	/* Expansion space */
    char			name[32];	/* Mutex name */
    } pthreadDebugMutexInfo_t, *pthreadDebugMutexInfo_p;

/*
 * Type defining information returned about a rwlock.
 *
 * NOTES:
 *
 * 1) When a rwlock is STATICALLY initialized using PTHREAD_RWLOCK_INITIALIZER
 *    (or equivalent) and has not yet been used to BLOCK a thread, the rwlock
 *    does not have a sequence number. It is not visible in a
 *    pthreadDebugRwSeq* traversal, or to pthreadDebugRwGetInfo, and its
 *    name cannot be set using pthreadDebugRwSetName. In this case, the
 *    "sequence" member of the pthreadDebugRwlockInfo_t structure will have the
 *    value 0. The value 0 is never a valid sequence number, so there is no
 *    ambiguity. You can only examine the state of these rwlockes using
 *    pthreadDebugRwGetInfoAddr.
 */

#define PTHREAD_DEBUG_RW_NAME		0x00000001  /* Name != "<anonymous>" */
#define PTHREAD_DEBUG_RW_RDLOCKED	0x00000002  /* Currently rdlocked */
#define PTHREAD_DEBUG_RW_WRLOCKED	0x00000004  /* Currently wrlocked */
#define PTHREAD_DEBUG_RW_RWAITERS	0x00000008  /* Waiting readers */
#define PTHREAD_DEBUG_RW_WWAITERS	0x00000010  /* Waiting writers */
#define PTHREAD_DEBUG_RW_INTERNAL	0x00000020  /* DECthreads internal */
#define PTHREAD_DEBUG_RW_PSHARED	0x00000040  /* "Process shared" */

typedef struct pthreadDebugRwlockInfo_tag {
    unsigned long		flags;		/* Miscellaneous flags */
    pthreadDebugId_t		sequence;	/* Sequence number */
    pthread_rwlock_t		*address;	/* Rwlock address */
    pthreadDebugId_t		wrid;		/* Write owner (if any) */
    unsigned long		rcount;		/* Reader count */
    char			name[32];	/* Rwlock name */
    } pthreadDebugRwlockInfo_t, *pthreadDebugRwlockInfo_p;

/*
 * Type defining information returned about a condition variable.
 *
 * NOTES:
 *
 * 1) When a condition variable is STATICALLY initialized using
 *    PTHREAD_COND_INITIALIZER (or equivalent) and has not yet been used to
 *    BLOCK a thread, the condition variable does not have a sequence
 *    number. It is not visible in a pthreadDebugCondSeq* traversal, or to
 *    pthreadDebugCondGetInfo, and its name cannot be set using
 *    pthreadDebugCondSetName. In this case, the "sequence" member of the
 *    pthreadDebugCondInfo_t structure will have the value 0. The value 0 is
 *    never a valid sequence number, so there is no ambiguity. You can only
 *    examine the state of these mutexes using pthreadDebugCondGetInfoAddr.
 */

#define PTHREAD_DEBUG_COND_NAME		0x00000001  /* Name != "<anonymous>" */
#define PTHREAD_DEBUG_COND_PEND		0x00000002  /* Pending wake (sig_int) */
#define PTHREAD_DEBUG_COND_WAITERS	0x00000004  /* There are waiters */
#define PTHREAD_DEBUG_COND_METERED	0x00000008  /* CV has meter info */
#define PTHREAD_DEBUG_COND_INTERNAL	0x00000010  /* DECthreads internal */
#define PTHREAD_DEBUG_COND_PSHARED	0x00000020  /* "Process shared" */

typedef struct pthreadDebugCondInfo_tag {
    unsigned long		flags;		/* Miscellaneous flags */
    pthreadDebugId_t		sequence;	/* Sequence number */
    pthread_cond_t		*address;	/* Condition address */
    pthreadDebugId_t		mutex;	     /* Associated mutex (if waiters) */
    long			reserved[10];	/* Expansion space */
    char			name[32];	/* Condition name */
    } pthreadDebugCondInfo_t, *pthreadDebugCondInfo_p;

/*
 * Type defining information returned about a thread specific data key.
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
 *
 * NOTE: Currently, EXTENDED tsd keys are reserved for use by the Digital UNIX
 * loader, in implementing THREAD LOCAL STORAGE. (cc's __declspec(thread).)
 */
#define PTHREAD_DEBUG_TSD_NAME		0x00000001 /* Name != "<anonymous>" */
#define PTHREAD_DEBUG_TSD_RESERVED	0x00000002 /* DECthreads reserved */
#define PTHREAD_DEBUG_TSD_ALLTHREAD	0x00000004 /* Const/Dest in all thds */
#define PTHREAD_DEBUG_TSD_EXTENDED	0x00000008 /* Extended (TLS) key */

typedef struct pthreadDebugTsdInfo_tag {
    unsigned long	flags;		/* Miscellaneous flags */
    pthread_key_t	key;		/* Key value */
    pthread_key_t	*address;	/* Where the key was stored */
    __pthreadConstructor_t constructor;	/* Constructor routine */
    union {				/* Destructor routine */
	__pthreadDestructor_t    standard;
	__pthreadExtDestructor_t extended;
	}		destructor;
    char		name[32];	/* key's name */
    } pthreadDebugTsdInfo_t, *pthreadDebugTsdInfo_p;

/*
 *				CALLBACK PROTOTYPES
 *
 * Typedefs for "callback routines" that the debug client must provide to the
 * debug assistant library. The set of callbacks is provided to
 * pthreadDebugContextInit via the pthreadDebugCallbacks_t structure.
 */

/*
 * GETMEM: Typedef for routine to read a block of memory from target process.
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	address		Address of target memory
 *	buffer		Local address to write memory
 *	size		Size of buffer
 *
 * Return value:
 *
 *	0		succeeded
 *	EINVAL		invalid address
 */
typedef int (*pthreadDebugGetMemRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugTargetAddr_t,
    void *,
    size_t);

/*
 * SETMEM: Typedef for routine to write a block of memory to target process
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	address		Address of target memory
 *	buffer		Local address to read memory
 *	size		Size of buffer
 *
 * Return value:
 *
 *	0		success
 *	EINVAL		invalid address
 *	ENOSYS		Not supported.
 */
typedef int (*pthreadDebugSetMemRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugTargetAddr_t,
    const void *,
    size_t);

/*
 * SUSPEND: Typedef for routine to suspend all threads in the target process.
 *
 * Suspension should be "counted" -- that is, when multiple calls to suspend
 * are made, the process should not be resumed until an equal number of calls
 * to resume have been made. If the underlying suspend/resume mechanism does
 * not have this property, the callback should implement a count and employ
 * the underlying mechanism only when the first suspend or last matching
 * resume request is made.
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *
 * Return value:
 *
 *	0		success
 *	ENOSYS		Not supported.
 */
typedef int (*pthreadDebugSuspendRtn_t) (pthreadDebugClient_t);

/*
 * RESUME: Typedef for routine to resume all threads in the target process.
 *
 * Suspension should be "counted" -- that is, when multiple calls to suspend
 * are made, the process should not be resumed until an equal number of calls
 * to resume have been made. If the underlying suspend/resume mechanism does
 * not have this property, the callback should implement a count and employ
 * the underlying mechanism only when the first suspend or last matching
 * resume request is made.
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *
 * Return value:
 *
 *	0		Success
 *	ENOSYS		Not supported.
 */
typedef int (*pthreadDebugResumeRtn_t) (pthreadDebugClient_t);

/*
 * KTHDINFO: Typedef for routine to get state information on a kernel thread.
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	thread_id	Kernel thread (port) ID
 *	thread_info	Kernel thread info struct
 *
 * Return value:
 *
 *	0		Success
 *	ESRCH		ID is invalid
 *	ENOSYS		Not supported.
 */
typedef int (*pthreadDebugKthdInfoRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugKId_t,
    pthreadDebugKThreadInfo_p);

/*
 * HOLD: Typedef for routine to prevent the kernel thread from running until
 *	 further notice.
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	thread_id	Kernel thread ID
 *
 * Return value:
 *
 *	0		Success
 *	ESRCH		ID is invalid
 *	ENOSYS		Not supported.
 */
typedef int (*pthreadDebugHoldRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugKId_t);

/*
 * UNHOLD: Typedef for routine to release a kernel thread that is held
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	thread_id	kernel thread ID
 *
 * Return value:
 *
 *	0	success
 *	ESRCH	invalid thread_id
 *	ENOSYS	Not supported.
 */
typedef int (*pthreadDebugUnholdRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugKId_t);

/*
 * GETFREG: Typedef for routine to get floating point register contents
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	fp_registers	register value structure
 *	thread_id	kernel thread ID
 *
 * Return value:
 *
 *	0	success
 *	ESRCH	invalid thread_id
 *	ENOSYS	Not supported.
 */
typedef int (*pthreadDebugGetFregRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugFregs_p,
    pthreadDebugKId_t);

/*
 * SETFREG: Typedef for routine to set floating point register contents
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	fp_registers	register value structure
 *	thread_id	kernel thread ID
 *
 * Return value:
 *
 *	0	success
 *	ESRCH	invalid thread_id
 *	ENOSYS	Not supported.
 */
typedef int (*pthreadDebugSetFregRtn_t) (
    pthreadDebugClient_t,
    const pthreadDebugFregs_t *,
    pthreadDebugKId_t);

/*
 * GETREG: Typedef for routine to get general register contents
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	registers	register value structure
 *	thread_id	kernel thread ID
 *
 * Return value:
 *
 *	0	success
 *	ESRCH	invalid thread_id
 */
typedef int (*pthreadDebugGetRegRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugRegs_p,
    pthreadDebugKId_t);

/*
 * SETREG: Typedef for routine to set general register contents
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	registers	register value structure
 *	thread_id	kernel thread ID
 *
 * Return value:
 *
 *	0	success
 *	ESRCH	invalid thread_id
 *	ENOSYS	Not supported.
 */
typedef int (*pthreadDebugSetRegRtn_t) (
    pthreadDebugClient_t,
    const pthreadDebugRegs_t *,
    pthreadDebugKId_t);

/*
 * OUTPUT: Typedef for routine to write a line of output
 *
 * Arguments:
 *
 *	caller_context		The caller's context argument
 *	line			A line of output (no newline)
 *
 * Return value:
 *
 *	0		Success
 *	ENOSYS		Not supported.
 */
typedef int (*pthreadDebugOutputRtn_t) (
    pthreadDebugClient_t,
    const char *);

/*
 * ERROR: Typedef for routine to write a line of error output
 *
 * Arguments:
 *
 *	caller_context		The caller's context argument
 *	line			A line of output (no newline)
 *
 * Return value:
 *
 *	0		Success
 *	ENOSYS		Not supported.
 */
typedef int (*pthreadDebugErrorRtn_t) (
    pthreadDebugClient_t,
    const char *);

/*
 * MALLOC: Typedef for routine to allocate memory
 *
 * Arguments:
 *
 *	caller_context		The caller's context argument
 *	size			size of allocation
 *
 * Return value:
 *
 *	pointer to memory
 *	NULL for error
 */
typedef void *(*pthreadDebugMallocRtn_t) (
    pthreadDebugClient_t,
    size_t);

/*
 * FREE: Typedef for routine to deallocate memory
 *
 * Arguments:
 *
 *	caller_context		The caller's context argument
 *	address			address of allocated space
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugFreeRtn_t) (
    pthreadDebugClient_t,
    void *);

/*
 * SPECIAL: Typedef for routine to determine the kernel thread ID of a
 * "special" thread in the debug target process. "Special" threads include the
 * current thread (which may be changed by a debugger command, for example,
 * ladebug's "thread" command), and the trap thread (the thread that generated
 * a trap (breakpoint, etc.) currently being processed.
 *
 * Arguments:
 *
 *	caller_context	The caller's context argument
 *	type		Which special thread to return.
 *	thread_id	Pointer to return current kernel thread ID
 *
 * Return value:
 *
 *	0	success
 *	ENOSYS	Not supported.
 *	ESRCH	no current thread
 */
typedef int (*pthreadDebugSpecKthdRtn_t) (
    pthreadDebugClient_t,
    pthreadDebugSpecialType_t,
    pthreadDebugKId_t *);

/*
 * The callback definition structure must be initialized by setting the
 * version field to the value PTHREAD_DEBUG_VERSION, and setting the address
 * of each callback routine, before calling pthreadDebugContextInit. Note that
 * DECthreads supports limited upwards compatibility for clients of this
 * interface specifying older versions (for example, clients compiled using
 * the original version will work with version 1).
 *
 * Callbacks that are not supported by the client must be set to NULL. The
 * client should clear the callback structure (e.g., with bzero or memset) and
 * then set the callbacks it understands and supports, to ensure that all
 * other callbacks are set to NULL.
 *
 * pthreadDebugContextInit will fail (with EINVAL) if the READ or GETREG
 * callbacks are not specified. It will also fail with EINVAL if you specify
 * either MALLOC or FREE (or SUSPEND and RESUME) without specifying both.
 * Other callbacks are optional, but may be required for some functions.
 * You'll get an error (ENOSYS or ENOTSUP) if you call a function that
 * requires an unimplemented callback. We may also want to call various
 * callbacks for other reasons (e.g., we use WRITE, if available, to update
 * some thread information when it's shown, for clients connected with V1 or
 * higher interface, but we'll ignore that feature if the callback isn't
 * present (or returns ENOSYS or ENOTSUP).
 *
 * Note in particular, however, that debug information is NOT RELIABLE if you
 * do not specify the SUSPEND and RESUME callbacks. Access to some information
 * is not atomic, and the consequences of accessing a running process may
 * range from bad data to (debugger) SEGV/ACCVIO errors. (This is OK if the
 * debugger knows that the target process is always suspended, but beware that
 * our access to remote process data will be substantially more efficient if
 * we know when the process is suspended, and we can know that only when we've
 * used SUSPEND/RESUME.)
 */
typedef struct pthreadDebugCallbacks_tag {
    unsigned long		version;
    pthreadDebugGetMemRtn_t	read_callback;	/* REQUIRED */
    pthreadDebugSetMemRtn_t	write_callback;
    pthreadDebugSuspendRtn_t	suspend_callback;
    pthreadDebugResumeRtn_t	resume_callback;
    pthreadDebugKthdInfoRtn_t	kthdinfo_callback;
    pthreadDebugHoldRtn_t	hold_callback;
    pthreadDebugUnholdRtn_t	unhold_callback;
    pthreadDebugGetFregRtn_t	getfreg_callback;
    pthreadDebugSetFregRtn_t	setfreg_callback;
    pthreadDebugGetRegRtn_t	getreg_callback; /* REQUIRED */
    pthreadDebugSetRegRtn_t	setreg_callback;
    pthreadDebugOutputRtn_t	output_callback;
    pthreadDebugOutputRtn_t	error_callback;
    pthreadDebugMallocRtn_t	malloc_callback;
    pthreadDebugFreeRtn_t	free_callback;
    pthreadDebugSpecKthdRtn_t	speckthd_callback;
    } pthreadDebugCallbacks_t, *pthreadDebugCallbacks_p;

/*
 * ROUTINES
 */

/*
 * pthreadDebugContextInit
 *
 *	Initialize the DECthreads debug interface and stores the context in
 *	the given debug context structure. This allows the caller to setup the
 *	process to be debugged and register all the callbacks once so that the
 *	other routines only need to take one parameter, this debug context
 *	structure. If the debugger wishes, it can register different callbacks
 *	based on procfs, ptrace core file, remote debugging, etc.
 *
 * Arguments:
 *
 *	caller_context		Uninterpreted value, passed to each callback.
 *	callbacks		Array of client callbacks, plus API version
 *	symbol_handle		Address of __pthread_dbg_symtable in target
 *	debug_context		Returns a handle to debug context.
 *
 * Callbacks:
 *
 *	GETMEM, SETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			Unsupported debug client (debug library cannot
 *				support debugger API version)
 *	ENOTSUP			Unsupported target (no DECthreads, or
 *				incompatible DECthreads version)
 *	ENOMEM			Unable to allocate internal context structure
 */
extern int
pthreadDebugContextInit (
    pthreadDebugClient_t,
    pthreadDebugCallbacks_p,
    void *,
    pthreadDebugContext_p);

/*
 * pthreadDebugContextDestroy
 *
 *	Destroy the given debug context and free any associated resources.
 *
 * Arguments:
 *
 *	debug_context		The debug context to destroy
 *
 * Callbacks:
 *
 *	FREE, GETMEM, SETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 */
extern int
pthreadDebugContextDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugCondGetInfo
 *
 *	Get the DECthreads state of a given condition variable.
 *
 *	The process must be suspended for proper operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	cond_id			condition variable id
 *	info			pointer to info structure
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			condition variable not found
 *	ECHILD			condition variable has lost "child" part
 */
extern int
pthreadDebugCondGetInfo (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugCondInfo_p);

/*
 * pthreadDebugCondGetInfoAddr
 *
 *	Get information about a condition variable from its address
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	cond_addr		Address of cond var in target process
 *	cond_info		Address of info buffer
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or not a cond var.
 *	ECHILD			condition variable has lost "child" part
 */
extern int
pthreadDebugCondGetInfoAddr (
	pthreadDebugContext_t,
	pthread_cond_t *,
	pthreadDebugCondInfo_t *);

/*
 * pthreadDebugCondSeqInit
 *
 *	Return the first condition variable in the current list of user
 *	condition variables. If the call succeeds, then
 *	pthreadDebugCvSeqNext() can be called to retrieve subsequent condition
 *	variables.
 *
 *	Note, this call will suspend the process. The corresponding destroy
 *	will resume the process.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	cond			Pointer to return first condition variable
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, SUSPEND, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no condition variables
 *	EBUSY			debug context's thread traversal is active
 *	ENOMEM			unable to allocate traversal context
 */
extern int
pthreadDebugCondSeqInit (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugCondSeqNext
 *
 *	Return the next condition variable in the current list of user
 *	condition variables.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	cond			Pointer to return next condition variable
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			the previously returned condition variable
 *				context no longer exists (process not
 *				suspended?)
 *	ENOENT			no more condition variables
 */
extern int
pthreadDebugCondSeqNext (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugCondSeqDestroy
 *
 *	Terminates the iterative condition variable queries started with
 *	pthreadDebugCvSeqInit().
 *
 *	Note, this call will resume the process suspended with the
 *	corresponding init operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *
 * Callbacks:
 *
 *	FREE, RESUME
 *
 * Return value:
 *
 *	0		Successful completion
 *	EINVAL		debug context isn't valid, or no traversal
 *	EBUSY		Active traversal of wrong type
 */
extern int
pthreadDebugCondSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugCondSetName
 *
 *	Set the name of a condition variable for the debug session. (Setting
 *	to "" removes any existing name.)
 *
 *	Note that this name applies only within the Debug Assistant session
 *	specified by debug_context. It cannot be seen within the target
 *	process (e.g., by tracing, or pthread_cond_getname_np), or by other
 *	Debug Assistant sessions. It will be forgotten when the debug context
 *	is destroyed.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	id			condition variable ID
 *	name			Pointer to name (up to 31 characters)
 *
 * Callbacks:
 *
 *	MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or not a cond var.
 *	ENOMEM			insufficient memory to create name
 */
extern int
pthreadDebugCondSetName (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	const char *);

/*
 * pthreadDebugCblkSeqInit
 *
 *	Return the first thread in the current list of threads blocked on a
 *	condition variable. If the call succeeds, then
 *	pthreadDebugCblkSeqNext() can be called to retrieve subsequent
 *	threads.
 *
 *	Note, this call will suspend the process. The corresponding destroy
 *	will resume the process.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	cond			The condition variable to examine
 *	thread			Pointer to return the first blocked thread
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, SUSPEND, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			Condition variable not found
 *	ENOENT			no threads blocked on a condition variable
 *	EBUSY			debug context's thread traversal is active
 *	ENOMEM			unable to allocate traversal context
 */
extern int
pthreadDebugCblkSeqInit (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugCblkSeqNext
 *
 *	Return the next thread in the current list of threads blocked on a
 *	condition variable.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	cond			The condition variable to examine
 *	thread			Pointer to return the next blocked thread
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no more threads
 */
extern int
pthreadDebugCblkSeqNext (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugCblkSeqDestroy
 *
 *	Terminates the iterative blocked thread queries started with
 *	pthreadDebugCblkSeqInit().
 *
 *	Note, this call will resume the process suspended with the
 *	corresponding init operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *
 * Callbacks:
 *
 *	FREE, RESUME
 *
 * Return value:
 *
 *	0		Successful completion
 *	EINVAL		debug context isn't valid, or no traversal
 *	EBUSY		Active traversal of wrong type
 */
extern int
pthreadDebugCblkSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugMutGetInfo
 *
 *	Get the DECthreads state of a given mutex.
 *
 *	Note, the process must be suspended for proper operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	mutex_id		mutex id
 *	info			pointer to info structure
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			mutex not found
 *	ECHILD			mutex has lost "child" part
 */
extern int
pthreadDebugMutGetInfo (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugMutexInfo_p);

/*
 * pthreadDebugMutGetInfoAddr
 *
 *	Get information about a mutex from its address
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	mutex_addr		Address of mutex in target process
 *	mutex_info		Address of info buffer
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or not a mutex
 *	ECHILD			mutex has lost "child" part
 */
extern int
pthreadDebugMutGetInfoAddr (
	pthreadDebugContext_t,
	pthread_mutex_t	*,
	pthreadDebugMutexInfo_t	*);

/*
 * pthreadDebugMutSeqInit
 *
 *	Return the first mutex in the current list of user mutexes. If the
 *	call succeeds, then pthreadDebugMutSeqNext() can be called to retrieve
 *	subsequent mutexes.
 *
 *	Note, this call will suspend the process. The corresponding destroy
 *	will resume the process.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	mutex			Pointer to return first mutex ID
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, SUSPEND, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no mutexes
 *	EBUSY			debug context's thread traversal is active
 *	ENOMEM			unable to allocate traversal context
 */
extern int
pthreadDebugMutSeqInit (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugMutSeqNext
 *
 *	Return the next mutex in the current list of user mutexes.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	mutex			Pointer to return next mutex ID
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no more mutexes
 */
extern int
pthreadDebugMutSeqNext (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugMutSeqDestroy
 *
 *	Terminates the iterative mutex queries started with
 *	pthreadDebugMutSeqInit().
 *
 *	Note, this call will resume the process suspended with the
 *	corresponding init operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *
 * Callbacks:
 *
 *	FREE, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or no traversal
 *	EBUSY			Active traversal of wrong type
 */
extern int
pthreadDebugMutSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugMutSetName
 *
 *  	Set the name of a mutex for the debug session.
 *
 *	Note that this name applies only within the Debug Assistant session
 *	specified by debug_context. It cannot be seen within the target
 *	process (e.g., by tracing, or pthread_mutex_getname_np), or by other
 *	Debug Assistant sessions. It will be forgotten when the debug context
 *	is destroyed.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	id			mutex ID
 *	name			Pointer to name (up to 31 characters)
 *
 * Callbacks:
 *
 *	MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or not a cond var.
 *	ENOMEM			insufficient memory to create name
 */
extern int
pthreadDebugMutSetName (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	const char *);

/*
 * pthreadDebugMblkSeqInit
 *
 *	Return the first thread in the current list of threads blocked on a
 *	mutex. If the call succeeds, then pthreadDebugMblkSeqNext() can be
 *	called to retrieve subsequent threads.
 *
 *	Note, this call will suspend the process. The corresponding destroy
 *	will resume the process.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	mutex			The mutex to examine
 *	thread			Pointer to return the first blocked thread
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, SUSPEND, FREE, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	ESRCH			Mutex not found
 *	EINVAL			debug context isn't valid
 *	ENOENT			no threads blocked on mutex
 *	EBUSY			debug context's thread traversal is active
 *	ENOMEM			unable to allocate traversal context
 */
extern int
pthreadDebugMblkSeqInit (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugMblkSeqNext
 *
 *	Return the next thread in the current list of threads blocked on a
 *	mutex.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	mutex			The mutex to examine
 *	thread			Pointer to return the next blocked thread
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no more threads
 */
extern int
pthreadDebugMblkSeqNext (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugMblkSeqDestroy
 *
 *	Terminates the iterative blocked thread queries started with
 *	pthreadDebugMblkSeqInit().
 *
 *	Note, this call will resume the process suspended with the
 *	corresponding init operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *
 * Callbacks:
 *
 *	FREE, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or no traversal
 *	EBUSY			Active traversal of wrong type
 */
extern int
pthreadDebugMblkSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugRwGetInfoAddr
 *
 *	Retrieve the state of a rwlock by address
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	rwlock_addr		Rwlock address (pthread_rwlock_t)
 *	info			Return rwlock info
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	EINVAL			Not a rwlock
 *	ECHILD			Rwlock has lost "child" part
 */
int
pthreadDebugRwGetInfoAddr (
	pthreadDebugContext_t,
	pthread_rwlock_t *,
	pthreadDebugRwlockInfo_p);

/*
 * pthreadDebugRwGetInfo
 *
 *	Retrieve the state of a rwlock
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	rwlock_id		Rwlock sequence number
 *	info			Return rwlock info
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			rwlock not found
 *	ECHILD			Rwlock has lost "child" part
 */
int
pthreadDebugRwGetInfo (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	pthreadDebugRwlockInfo_p);

/*
 * pthreadDebugRwblkRdSeqDestroy
 *
 *	Destroy the active blocked thread traversal context for the list of
 *	threads waiting on a rwlock for a read lock
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or no traversal
 *	EBUSY			Active traversal of wrong type
 */
int
pthreadDebugRwblkRdSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugRwblkRdSeqInit
 *
 *	Initialize a blocked thread traversal context.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	rwl_id			Read-write lock to search
 *	thread_id		Returns first thread
 *
 * Return value:
 *
 *	0			Successful completion
 *	ESRCH			Read-write lock not found
 *	EINVAL			debug context isn't valid
 *	EBUSY			debug context's blocked traversal is active
 *	ENOMEM			unable to allocate traversal context
 *	ENOENT			no threads
 */
int
pthreadDebugRwblkRdSeqInit (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugRwblkRdSeqNext
 *
 *	Return the next entry in a thread traversal context.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	thread_id		Returns first thread
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no more threads
 *	EBUSY			traversal in use by different object type
 */
int
pthreadDebugRwblkRdSeqNext (
	pthreadDebugContext_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugRwblkWrSeqDestroy
 *
 *	Destroy the active blocked thread traversal context for the list of
 *	threads waiting on a rwlock for a write lock
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or no traversal
 *	EBUSY			Active traversal of wrong type
 */
int
pthreadDebugRwblkWrSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugRwblkWrSeqInit
 *
 *	Initialize a blocked thread traversal context.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	rwl_id			Read-write lock to search
 *	thread_id		Returns first thread
 *
 * Return value:
 *
 *	0			Successful completion
 *	ESRCH			Read-write lock not found
 *	EINVAL			debug context isn't valid
 *	EBUSY			debug context's blocked traversal is active
 *	ENOMEM			unable to allocate traversal context
 *	ENOENT			no threads
 */
int
pthreadDebugRwblkWrSeqInit (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugRwblkWrSeqNext
 *
 *	Return the next entry in a thread traversal context.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	thread_id		Returns first thread
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no more threads
 *	EBUSY			traversal in use by different object type
 */
int
pthreadDebugRwblkWrSeqNext (
	pthreadDebugContext_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugRwSeqDestroy
 *
 *	Destroy the active rwlock traversal context.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or no traversal
 *	EBUSY			Active traversal of wrong type
 */
int
pthreadDebugRwSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugRwSeqInit
 *
 *	Initialize a rwlock traversal context.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	rwlock_id		Returns first rwlock
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	EBUSY			debug context's traversal is active
 *	ENOMEM			unable to allocate traversal context
 *	ENOENT			no rwlockes
 */
int
pthreadDebugRwSeqInit (
	pthreadDebugContext_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugRwSeqNext
 *
 *	Return the next entry in a rwlock traversal context.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	rwlock_id		Returns next rwlock
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no more rwlockes
 *	EBUSY			traversal in use by different object type
 */
int
pthreadDebugRwSeqNext (
	pthreadDebugContext_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugRwSetName
 *
 *	Set the name of a read-write lock for the debug session. (Setting to
 *	"" removes any existing name.)
 *
 *	Note that this name applies only within the Debug Assistant session
 *	specified by debug_context. It cannot be seen within the target
 *	process (e.g., by tracing, or pthread_cond_getname_np), or by other
 *	Debug Assistant sessions. It will be forgotten when the debug context
 *	is destroyed.
 *
 * Arguments:
 *
 *	debug_context		DECthreads debug context
 *	id			ID
 *	name			pointer to name string
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid or name is NULL
 *	ENOMEM			can't store new name
 */
int
pthreadDebugRwSetName (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	const char *);

/*
 * pthreadDebugThdGetInfo
 *
 *	Get the DECthreads state of a given thread.
 *
 *	Note, the process must be suspended for proper operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		thread id
 *	info			pointer to info structure
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, [SETMEM, FREE]
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			thread not found
 */
extern int
pthreadDebugThdGetInfo (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugThreadInfo_p);

/*
 * pthreadDebugThdGetInfoAddr
 *
 *	Get information about a thread from its address (pthread_t)
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	thd_addr		Address of thread in target process
 *	thd_info		Address of info buffer
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, [SETMEM, FREE]
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or not a thread
 */
extern int
pthreadDebugThdGetInfoAddr (
	pthreadDebugContext_t,
	pthread_t,
	pthreadDebugThreadInfo_t *);

/*
 * pthreadDebugThdSeqInit
 *
 *	Return the first thread in the current list of user threads. If the
 *	call succeeds, then pthreadDebugThdSeqNext() can be called to retrieve
 *	subsequent threads.
 *
 *	Note, this call will suspend the process. The corresponding destroy
 *	will resume the process.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread			Pointer to return first thread ID
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, SUSPEND, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOENT			no threads
 *	EBUSY			debug context's thread traversal is active
 *	ENOMEM			unable to allocate traversal context
 */
extern int
pthreadDebugThdSeqInit (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugThdSeqNext
 *
 *	Return the next thread in the current list of user threads.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread			Pointer to return next thread ID
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			the previously returned thread (context) no
 *				longer exists [process not suspended?]
 *	ENOENT			no more threads
 */
extern int
pthreadDebugThdSeqNext (
    pthreadDebugContext_t,
    pthreadDebugId_t *);

/*
 * pthreadDebugThdSeqDestroy
 *
 *	Terminates the iterative thread queries started with
 *	pthreadDebugThdSeqInit().
 *
 *	Note, this call will resume the process suspended with the
 *	corresponding init operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *
 * Callbacks:
 *
 *	FREE, RESUME, [ERROR, OUTPUT]
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or no traversal
 *	EBUSY			Active traversal of wrong type
 */
extern int
pthreadDebugThdSeqDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugThdSetName
 *
 *	Set the name of a thread for the debug session. (Setting to "" removes
 *	any existing name.)
 *
 *	Note that this name applies only within the Debug Assistant session
 *	specified by debug_context. It cannot be seen within the target
 *	process (e.g., by tracing, or pthread_getname_np), or by other Debug
 *	Assistant sessions. It will be forgotten when the debug context is
 *	destroyed.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	id			thread ID
 *	name			Pointer to name (up to 31 characters)
 *
 * Callbacks:
 *
 *	MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or not a cond var.
 *	ENOMEM			insufficient memory to create name
 */
extern int
pthreadDebugThdSetName (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	const char *);

/*
 * pthreadDebugTsdCreate
 *
 *	Create a new TSD key in the target process.
 *
 *	(Note that this is pointless unless the client is also adding code to
 *	the target process that will use the new key.)
 *
 *	This call has a potentially dangerous race condition if code in the
 *	target process may also be creating a TSD key. This race cannot be
 *	resolved from the Debug Assistant, so, if the condition is detected,
 *	this function will return EAGAIN. The client should allow the process
 *	to run and try again later. (This will never occur if the debugger
 *	creates a new TSD key before starting the process, and that's the
 *	best time to use it anyway.)
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	key			Pointer (return the TSD key)
 *	destructor		Address (in target process) of routine
 *
 * Callbacks:
 *
 *	MALLOC, SUSPEND, RESUME, GETMEM, SETMEM, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or key isn't valid
 *	ENOMEM			can't create key
 *	EAGAIN			Synchronization conflict: try again later
 */
extern int
pthreadDebugTsdCreate (
	pthreadDebugContext_t,
	pthread_key_t *,
	__pthreadDestructor_t);

/*
 * pthreadDebugTsdGetInfo
 *
 *	Get information on a Thread Specific Data (TSD) Key.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	key			The TSD key
 *	info			pointer to info structure
 *
 * Callbacks:
 *
 *	MALLOC, GETMEM, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or key isn't valid
 */
extern int
pthreadDebugTsdGetInfo (
	pthreadDebugContext_t,
	pthread_key_t,
	pthreadDebugTsdInfo_p);

/*
 * pthreadDebugTsdGetSpecific
 *
 *	Return the value of a thread-specific data (TSD) key for a specific
 *	thread.
 *
 *	NOTE: There is no interface to return a 32-bit value for a TSD key.
 *	The pointer "value" must point to a 64-bit "void*" on an Alpha
 *	(Digital UNIX or OpenVMS).
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		The thread's ID
 *	key			The TSD key
 *	value			Pointer where TSD value is returned
 *
 * Callbacks:
 *
 *	MALLOC, GETMEM, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or key isn't valid
 *	ESRCH			thread not found
 */
extern int
pthreadDebugTsdGetSpecific (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	pthread_key_t,
	__pthreadLongAddr_p);

/*
 * pthreadDebugTsdSetSpecific
 *
 *	Set the value of a thread-specific data (TSD) key for a specific
 *	thread.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		The thread's ID
 *	key			The TSD key
 *	value			Pointer where TSD value is returned
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, MALLOC, GETMEM, SETMEM, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or key isn't valid
 *	ESRCH			thread not found
 *	ENOTSUP			can't set key (thread has no TSD array)
 */
extern int
pthreadDebugTsdSetSpecific (
	pthreadDebugContext_t,
	pthreadDebugId_t,
	pthread_key_t,
	const void *);

/*
 * pthreadDebugTsdSetName
 *
 *	Set the name of a TSD key for the debug session. (Setting to ""
 *	removes any existing name.)
 *
 *	Note that this name applies only within the Debug Assistant session
 *	specified by debug_context. It cannot be seen within the target
 *	process (e.g., by tracing, or pthread_key_getname_np), or by other
 *	Debug Assistant sessions. It will be forgotten when the debug context
 *	is destroyed.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	key			TSD key
 *	name			Pointer to name (up to 31 characters)
 *
 * Callbacks:
 *
 *	MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or key isn't valid.
 *	ENOMEM			insufficient memory to create name
 */
extern int
pthreadDebugTsdSetName (
	pthreadDebugContext_t,
	pthread_key_t,
	const char *);

/*
 * pthreadDebugTsdSeqDestroy
 *
 *	Destroy a TSD traversal context
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *
 * Callbacks:
 *
 *	RESUME, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or no traversal
 *	EBUSY			Active traversal of wrong type
 */
extern int
pthreadDebugTsdSeqDestroy (
	pthreadDebugContext_t	debug_context);

/*
 * pthreadDebugTsdSeqInit
 *
 *	Initialize a TSD traversal context.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	key_id			pointer to return first key
 *
 * Callbacks:
 *
 *	SUSPEND, GETMEM, MALLOC, [FREE, RESUME]
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or key isn't valid.
 *	EBUSY			debug context's key traversal is active
 *	ENOMEM			unable to allocate traversal context
 *	ENOENT			no keys
 */
extern int
pthreadDebugTsdSeqInit (
	pthreadDebugContext_t	debug_context,
	pthreadDebugId_t	*key_id);

/*
 * pthreadDebugTsdSeqInit
 *
 *	Return the next TSD key.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	key_id			pointer to return next key
 *
 * Callbacks:
 *
 *	GETMEM, MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or key isn't valid.
 *	EBUSY			debug context's key traversal is active
 *	ENOMEM			unable to allocate traversal context
 *	ENOENT			no keys
 */
extern int
pthreadDebugTsdSeqNext (
	pthreadDebugContext_t	debug_context,
	pthreadDebugId_t	*key_id);

/*
 * pthreadDebugThdGetFreg
 *
 *	Get the thread's current floating point registers.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		thread id
 *	regs			register values
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, GETMEM, GETREG, MALLOC, GETFREG, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			thread not found
 *	any callback errors
 */
extern int
pthreadDebugThdGetFreg (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugFregs_p);

/*
 * pthreadDebugThdSetFreg
 *
 *	Set the thread's current floating point registers.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		thread id
 *	regs			register values
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, GETMEM, GETREG, MALLOC, SETFREG, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			thread not found
 *	any callback errors
 */
extern int
pthreadDebugThdSetFreg (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugFregs_p);

/*
 * pthreadDebugThdGetReg
 *
 *	Get the thread's current general registers.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		thread id
 *	regs			register values
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, GETMEM, MALLOC, GETREG, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			thread not found
 *	any callback errors
 */
extern int
pthreadDebugThdGetReg (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugRegs_p);

/*
 * pthreadDebugThdSetReg
 *
 *	Set the thread's current general registers.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		thread id
 *	regs			register values
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, GETMEM, MALLOC, SETREG, [GETREG, FREE]
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ESRCH			thread not found
 *	any callback errors
 */
extern int
pthreadDebugThdSetReg (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugRegs_p);

/*
 * pthreadDebugThdHold
 *
 *	Make the user thread ineligible for scheduling.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		thread to hold
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, GETMEM, MALLOC, SETMEM, HOLD, UNHOLD, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	EPERM (V2)		internal DECthreads thread (can't be held).
 *	EINVAL (V2)		thread is terminated
 *	any callback errors
 */
extern int
pthreadDebugThdHold (
    pthreadDebugContext_t,
    pthreadDebugId_t);

/*
 * pthreadDebugThdUnhold
 *
 *	Make the user thread eligible for scheduling.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		thread to release
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	EPERM (V2)		internal DECthreads thread (can't be held).
 *	EINVAL (V2)		thread is terminated
 */
extern int
pthreadDebugThdUnhold (
    pthreadDebugContext_t,
    pthreadDebugId_t);

/*
 * pthreadDebugThdKidToId
 *
 *	Convert a kernel thread ID into a user thread ID (sequence number).
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	kid			Kernel thread ID.
 *	thread_id		Thread ID.
 *
 * Callbacks:
 *
 *	KTHDINFO, GETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid, or not a thread
 */
extern int
pthreadDebugThdKidToId (
	pthreadDebugContext_t,
	pthreadDebugKId_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugSuspend
 *
 *	Invoke the SUSPEND callback to suspend the target process. The
 *	advantage of using this interface rather than "doing it directly" is
 *	that, when debug assistant knows that the target process is suspended,
 *	it can make more efficient use of its internal cache.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *
 * Callbacks:
 *
 *	SUSPEND
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOTSUP			SUSPEND callback not supported
 */
extern int
pthreadDebugSuspend (pthreadDebugContext_t);

/*
 * pthreadDebugResume
 *
 *	Invoke the RESUME callback to suspend the target process. The
 *	advantage of using this interface rather than "doing it directly" is
 *	that, when the assistant knows that the target process is suspended,
 *	it can make more efficient use of its internal cache.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *
 * Callbacks:
 *
 *	RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOTSUP			RESUME callback not supported
 */
extern int
pthreadDebugResume (pthreadDebugContext_t);

/*
 * pthreadDebugGetSpecialThread
 *
 *	Return the thread Id for a specific "special" kernel thread (if any).
 *	Depends upon the debug client's response to the SPECKTHD callback,
 *	essentially just converting that kernel thread ID into a user thread
 *	ID.
 *
 * Arguments:
 *
 *	debug_context		debug context to use
 *	type			Type of special thread
 *	thread_id		Thread ID (returned)
 *
 * Callbacks:
 *
 *	SPECKTHD, KTHDINFO, GETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOTSUP			SPECKTHD callback not supported
 */
extern int
pthreadDebugGetSpecialThread (
	pthreadDebugContext_t,
	pthreadDebugSpecialType_t,
	pthreadDebugId_t *);

/*
 * pthreadDebugCmd
 *
 *	This routine implements the commands previously provided by the
 *	pthread_debug_cmd() routine which was run in the context of the
 *	target. These commands operate from the context of the debugger now.
 *
 *	Note, the process must be suspended for reliable operation.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	command			Pointer to an ASCII character string
 *				representing a sequence of pthread_debug()
 *				commands, each separated by ";".
 *
 * Callbacks:
 *
 *	OUTPUT (Potentially all, depending upon the command.)
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOTSUP			invalid command
 *	ESHUTDOWN		command string terminated by "exit"
 */
extern int
pthreadDebugCmd(
    pthreadDebugContext_t,
    const char *);

/*
 * pthreadDebugSetErrorWidth
 *
 *	This routine modifies the output width of the error stream used by
 *	pthreadDebugCmd (and general error tracing output when enabled). The
 *	default if not set is 80 columns.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	width			New width for error stream width.
 *
 * Callbacks:
 *
 *	none
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 */
extern int
pthreadDebugSetErrorWidth (
    pthreadDebugContext_t,
    int);

/*
 * pthreadDebugSetOutputWidth
 *
 *	This routine modifies the output width of the output stream used by
 *	pthreadDebugCmd (and tracing output if enabled). The default if not
 *	set is 80 columns.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	width			New width for output stream width.
 *
 * Callbacks:
 *
 *	none
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 */
extern int
pthreadDebugSetOutputWidth (
    pthreadDebugContext_t,
    int);

/*
 *				 EVENTS
 *
 * The DECthreads event mechanism allows a debugger to determine when "things"
 * happen within the DECthreads scheduler. For example, when a thread is
 * created, when it first starts to run, and when it terminates.
 *
 * Ultimately the debugger learns of an event by receiving a breakpoint trap
 * that it has set within the "target" process. It can ask for the address of
 * a "hook" routine at which to set the breakpoint by calling the routine
 * pthreadDebugEventGetAddress. However, for performance reasons the
 * DECthreads scheduler does not normally call these hook routines. The hooks
 * must be enabled by setting events. (Note that the hook points consist of a
 * single no-op instruction so that they can be patched without needing to
 * save and restore the original instruction.)
 *
 * In principle, the debugger could begin by setting globally all events in
 * which it "may have" interest, and simply ignoring the resulting breakpoints
 * when an event isn't interesting at the moment. However, debugging of
 * asynchronous programs can be difficult enough without the timing impact of
 * dealing with extra breakpoints. It is strongly recommended that the
 * debugger enable only the events in which it is specifically interested, and
 * then disable them when it no longer needs to know.
 *
 * Additionally, when per-thread events are desired the debugger could simply
 * globally enable and disable any events, and check the current thread ID
 * during breakpoint processing. But to minimize the impact of events on
 * application behavior, it would be better to enable events only for specific
 * threads so that the breakpoint overhead occurs only where its likely to be
 * of use.
 */

/*
 *		Event definitions and "stub" prototypes
 *
 * Any of these events can be enabled either for specific threads or
 * "globally", for all threads in the target process. Note that disabling
 * (clearing) an event for a specific thread doesn't override a global enable
 * (or vice versa) -- events are reported if the event is enabled either
 * globally or for the current thread.
 *
 * Events are reported in either or both of two mechanisms, when the event
 * occurs while enabled.
 *
 * For the convenience of debuggers running in another process, DECthreads
 * calls a "breakpoint stub" in the target process -- a debugger may set
 * breakpoints at these calls to detect the event. Stub routine pointers are
 * returned by calling pthreadDebugEventGetAddress. Stubs are enabled by
 * getting a stub address, or by calling pthreadDebugEventSetGlobal or
 * pthreadDebugEventSetThread.
 *
 * For the convenience of code running within the threaded process, such as a
 * performance analyzer, DECthreads can be configured to call a hook routine
 * provided by the analyzer. You can set a hook address by calling
 * __pthread_debug_set_hook. (Note that although the "hook routine" event
 * interface is documented & prototyped in this header, the __pthread_debug_
 * routines are in libpthread.so [PTHREAD$RTL.EXE], not in the debug assistant
 * library.
 *
 * Each hook routine is called with arguments that identify the event, the
 * thread, and additional parameters giving specific information. Refer to the
 * pthreadDebugEventActivating_t routine prototype for the arguments passed to
 * the "Activating" event hook, for example.
 *
 *	ACTIVATING		Report the initial execution of a new thread
 *				(Setting this event for a specific thread is
 *				of minimal use, but is allowed: one example
 *				would be to enable it for the new thread
 *				reported in a Creating event, to determine
 *				when the new thread starts executing.)
 *	BLOCKING		Report when a thread blocks
 *	CREATING		Report when a thread is created
 *	RUNNING			Report when a thread runs (after blocking or
 *				preemption)
 *	TERMINATING		Report when a thread terminates (after a
 *				return from its start routine, a call to
 *				pthread_exit, or cancellation).  NOTE that
 *				the thread is not yet completely run down.
 *	INITIALIZED		Report when the DECthreads core has been
 *				initialized.
 *	FREEING			Report when a thread is going to be freed.
 *				This means a thread is completely run  down.
 *	UNBLOCK			Report when a thread is readied after
 *				having been blocked.
 *	BUGCHECK		Report when DECthreads bugchecks (panics)
 *	LASTCHANCE		Report when the last chance exception
 *				handler is invoked.
 *	TOOLTEXT		Report when a tool library detects some
 *				condition worth of debugger/user attention.
 */
typedef enum pthreadDebugEvent_tag {
    PTHREAD_DEBUG_EVENT_ACTIVATING	= 1,
    PTHREAD_DEBUG_EVENT_BLOCKING	= 2,
    PTHREAD_DEBUG_EVENT_CREATING	= 3,
    PTHREAD_DEBUG_EVENT_RUNNING		= 4,
    PTHREAD_DEBUG_EVENT_TERMINATING	= 5,
    PTHREAD_DEBUG_EVENT_INITIALIZED	= 6,
    PTHREAD_DEBUG_EVENT_FREEING		= 7,
    PTHREAD_DEBUG_EVENT_UNBLOCK		= 8,
    PTHREAD_DEBUG_EVENT_BUGCHECK	= 9,
    PTHREAD_DEBUG_EVENT_LASTCHANCE	= 10,
    PTHREAD_DEBUG_EVENT_TOOLREPORT	= 11
    } pthreadDebugEvent_t;

#define PTHREAD_DEBUG_EVENT_MIN	PTHREAD_DEBUG_EVENT_ACTIVATING
#define PTHREAD_DEBUG_EVENT_MAX PTHREAD_DEBUG_EVENT_TOOLREPORT
#define PTHREAD_DEBUG_EVENT_COUNT (PTHREAD_DEBUG_EVENT_MAX+1)

typedef unsigned int	pthreadDebugEventMask_t, *pthreadDebugEventMask_p;

/*
 * Flags passed to various event routines by DECthreads to indicate
 * certain states.
 */

/*
 * RUN event:
 *	PREEMPTED:	Outgoing thread was preempted
 *	KERNEL:		Outgoing thread blocking in kernel
 */
#define PTHREAD_DEBUG_EVTRUN_PREEMPTED	0x00000001 /* Outgoing preempted */
#define PTHREAD_DEBUG_EVTRUN_KERNEL	0x00000002 /* Outgoing kernel block */

/*
 * TERMINATE event:
 *	LOCKS:		Terminated with locks held
 */
#define PTHREAD_DEBUG_EVTTRM_LOCKS	0x00000001

/*
 * UNBLOCK event:
 *	PEND:		Unblocked before BLOCK event was seen.
 */
#define PTHREAD_DEBUG_EVTUBL_PEND	0x00000001

/*
 * Prototypes showing the arguments passed to the BPT stub routines
 * (returned by pthreadDebugEventGetAddress).
 *
 * A debugger receiving a breakpoint on one of these events can read the
 * arguments to determine what happened, and then use normal information
 * interfaces to format and report the data.
 */

/*
 * Thread is activating (running for the first time)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_ACTIVATING
 *	thread		The new thread's sequence number
 *	start_routine	Address of the start routine
 *	start_argument	The argument passed to the start routine
 *	spare		Unused
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventActivating_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	void *(*) (void *),
	void *,
	void *,
	unsigned long);

/*
 * Thread is blocking
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_BLOCKING
 *	thread		The thread's sequence number
 *	substate	One of KERNEL, MUTEX, CV, TIMED_CV
 *	object		Sequence number of mutex or condition variable (or 0
 *			if none)
 *	spare		Unused
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventBlocking_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	pthreadDebugSubstate_t,
	pthreadDebugId_t,
	void *,
	unsigned long);

/*
 * Thread is being created
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_CREATING
 *	thread		The creating thread's sequence number
 *	new_thread	The new thread's sequence number
 *	start_routine	Address of the start routine
 *	start_argument	Argument passed to start routine
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventCreating_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	pthreadDebugId_t,
	void *(*) (void *),
	void *,
	unsigned long);

/*
 * Thread is running (after having blocked or been preempted)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_RUNNING
 *	thread		The thread's sequence number
 *	substate	Thread's previous substate
 *	previous	Sequence number of previous thread
 *	spare		Unused
 *	flags		Flags (preempted, kernel)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventRunning_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	pthreadDebugSubstate_t,
	pthreadDebugId_t,
	void *,
	unsigned long);

/*
 * Thread is terminating
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_TERMINATING
 *	thread		The thread's sequence number
 *	substate	Reason for termination: normal, term_cancel
 *			(cancelled) or term_exit (pthread_exit)
 *	result		Thread's result value
 *	spare		Unused
 *	flags		Flags (locks)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventTerminating_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	pthreadDebugSubstate_t,
	void *,
	void *,
	unsigned long);

/*
 * The DECthreads code has been initialized.
 *
 * NOTE: This is OBSOLETE. It was a hack to allow clients to avoid asking
 * about state that wasn't available until after initialization. This bug
 * was long since fixed correctly; a process that hasn't yet completed
 * DECthreads initialization simply has one thread.
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_INITIALIZED
 *	thread		The thread's sequence number
 *	spare		Unused
 *	spare		Unused
 *	spare		Unused
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventInitialized_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	void *,
	void *,
	void *,
	unsigned long);

/*
 * Thread is freeing a zombie TCB
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_FREEING
 *	thread		Thread's sequence number
 *	freed		Freed thread's sequence number
 *	spare		Unused
 *	spare		Unused
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventFreeing_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	pthreadDebugId_t,
	void *,
	void *,
	unsigned long);

/*
 * Thread is unblocked from a wait (CV, Mutex, etc.)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_UNBLOCK
 *	thread		Unblocking thread's sequence number
 *	substate	Reason for block: mutex, cv, etc.
 *	unblock		Unblocked thread's sequence number
 *	spare		Unused
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventUnblock_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	pthreadDebugSubstate_t,
	pthreadDebugId_t,
	void *,
	unsigned long);

/*
 * DECthreads bugcheck (unrecoverable inconsistency)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_BUGCHECK
 *	thread		Bugchecking thread's sequence number
 *	reason		String describing reason
 *	spare		Unused argument
 *	spare		Unused argument
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventBugcheck_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	char *,
	void *,
	void *,
	unsigned long);

/*
 * DECthreads last-chance handler (exception not handled by thread)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_LASTCHANCE
 *	thread		Thread's sequence number
 *	spare1		Unused argument
 *	spare2		Unused argument
 *	spare3		Unused argument
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventLastchance_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	void *,
	void *,
	void *,
	unsigned long);
/*
 * TOOL reported condition
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_BUGCHECK
 *	thread		Reporting thread's sequence number
 *	reason		String describing condition
 *	command		ladebug commands (may be ignored by other debuggers)
 *	spare		Unused argument
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugEventToolReport_t) (
	pthreadDebugEvent_t,
	pthreadDebugId_t,
	char *,
	char *,
	void *,
	unsigned long);


/*
 * pthreadDebugEventGetAddress
 *
 *	Get the address of a function in which the debugger can place a break
 *	point in order to know that the specified event has occurred.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	event			Event number (pthreadDebugEvent_t)
 *	address			pointer to "void*" to receive bpt address
 *
 * Callbacks:
 *
 *	GETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 *	ENOTSUP			event code not supported
 */
extern int
pthreadDebugEventGetAddress (
    pthreadDebugContext_t,
    pthreadDebugEvent_t,
    void **);

/*
 * pthreadDebugEventGetGlobal
 *
 *	Get a bitmask representing the global events currently enabled
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	mask			Event mask (pthreadDebugEventMask_t)
 *
 * Callbacks:
 *
 *	GETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 */
extern int
pthreadDebugEventGetGlobal (
    pthreadDebugContext_t,
    pthreadDebugEventMask_p);

/*
 * pthreadDebugEventGetThread
 *
 *	Get a bitmask representing the thread events currently enabled
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		The thread for which to get event mask
 *	mask			Event mask (pthreadDebugEventMask_t)
 *
 * Callbacks:
 *
 *	GETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context isn't valid
 */
extern int
pthreadDebugEventGetThread (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugEventMask_p);

/*
 * pthreadDebugEventClearGlobal
 *
 *	This routine disables global event reporting for an event.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	event			Event number (pthreadDebugEvent_t)
 *
 * Callbacks:
 *
 *	GETMEM, SETMEM, SUSPEND, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or event isn't valid
 */
extern int
pthreadDebugEventClearGlobal (
    pthreadDebugContext_t,
    pthreadDebugEvent_t);

/*
 * pthreadDebugEventSetGlobal
 *
 *	This routine enables global event reporting for an event.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	event			Event number (pthreadDebugEvent_t)
 *
 * Callbacks:
 *
 *	GETMEM, SETMEM, SUSPEND, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context or event isn't valid
 */
extern int
pthreadDebugEventSetGlobal (
    pthreadDebugContext_t,
    pthreadDebugEvent_t);

/*
 * pthreadDebugEventClearThread
 *
 *	This routine disables event reporting for a specific thread
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		The thread for which to clear the event
 *	event			Event number (pthreadDebugEvent_t)
 *
 * Callbacks:
 *
 *	GETMEM, SETMEM, SUSPEND, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	ESRCH			thread not found
 *	EINVAL			debug context or event isn't valid
 */
extern int
pthreadDebugEventClearThread (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugEvent_t);

/*
 * pthreadDebugEventSetThread
 *
 *	This routine enables event reporting for a specific thread
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	thread_id		The thread for which to set the event
 *	event			Event number (pthreadDebugEvent_t)
 *
 * Callbacks:
 *
 *	GETMEM, SETMEM, SUSPEND, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	ESRCH			thread not found
 *	EINVAL			debug context or event isn't valid
 */
extern int
pthreadDebugEventSetThread (
    pthreadDebugContext_t,
    pthreadDebugId_t,
    pthreadDebugEvent_t);

/*
 *				TRACE STREAM SUPPORT
 *
 * Following is a set of interfaces to access a DECthreads log engine trace
 * stream. This trace stream may be specified as a file, or you may use a
 * pthreadDebugContext_t to access the in-memory trace buffers of a threaded
 * process.
 */

typedef enum _pthreadDebugTraceFmt_tag {
    PTHREAD_DEBUG_TRACE_FMT_TIME	= 0x01,	/* Show record's timestamp */
    PTHREAD_DEBUG_TRACE_FMT_CYCLE	= 0x02,	/* Show machine cycles */
    PTHREAD_DEBUG_TRACE_FMT_SIZE	= 0x04,	/* Show record position/size */
    PTHREAD_DEBUG_TRACE_FMT_STACK	= 0x08	/* Show call stack */
    } pthreadDebugTraceFmt_t;

typedef enum _pthreadDebugTraceDetail_tag {
    PTHREAD_DEBUG_TRACE_DETAIL_NONE,		/* event names */
    PTHREAD_DEBUG_TRACE_DETAIL_BRIEF,		/* scalar args, seq #s */
    PTHREAD_DEBUG_TRACE_DETAIL_MID,		/* Add names, some state */
    PTHREAD_DEBUG_TRACE_DETAIL_NORMAL,		/* Normal detail */
    PTHREAD_DEBUG_TRACE_DETAIL_FULL		/* All detail */
    } pthreadDebugTraceDetail_t;

typedef enum _pthreadDebugTraceSetHow_tag {
    PTHREAD_DEBUG_TRACE_SETHOW_REPLACE,		/* Replace current mask */
    PTHREAD_DEBUG_TRACE_SETHOW_SET,		/* Add bits to mask */
    PTHREAD_DEBUG_TRACE_SETHOW_CLEAR		/* Clear bits from mask */
    } pthreadDebugTraceSetHow_t;

typedef void *pthreadDebugTraceHandle_t;
typedef void **pthreadDebugTraceHandle_p;

/*
 * The common header of a log engine's trace record.
 *
 * NOTES:
 *	flags	OR-ed enum values from pthreadTraceLogHeadFlags_t type
 *	argp	Pointer to "raw" event args (usually use iterator)
 *	pc	Pointer to array of <frames> PC values (stack trace)
 *	name	The event name specified at event point (if any)
 *	evtname	Formatted "canonical" name for event ("mutex.lock.request")
 */
typedef struct pthreadDebugTraceHead_tag {
    pthreadTraceEvent_t		event;		/* Trace point identifier */
    pthreadTraceId_t		thread;		/* Thread that logged event */
    __pthreadLongUint_t		sequence;	/* Record sequence number */
    pthreadTraceTimestamp_t	timestamp;	/* Timestamp data */
    unsigned char		flags;		/* pthreadTraceLogHeadFlags_t */
    unsigned char		frames;		/* Number of frames in trace */
    unsigned char		argc;		/* Number of arguments */
    const unsigned char		*argt;		/* Address of arg type array */
    const void			*argp;		/* Address of first argument */
    const void			* const *pc;	/* Pointer to PC array */
    char			name[32];	/* Event name */
    char			evtname[32];	/* Event point name */
    } pthreadDebugTraceHead_t, *pthreadDebugTraceHead_p;

/*
 * pthreadDebugTraceClose
 *
 *	This routine closes a trace stream opened with pthreadDebugTraceOpen()
 *
 * Arguments:
 *
 *	trace_handle		Pointer to returned handle
 *
 * Callbacks:
 *
 *	FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			trace handle not valid
 */
extern int
pthreadDebugTraceClose (pthreadDebugTraceHandle_t);

/*
 * pthreadDebugTraceOpen
 *
 *	This routine opens a trace file for analysis. When you specify a trace
 *	file, you can access all data in the trace stream, from process
 *	creation. The callback structure must contain a valid version; it may
 *	also contain malloc, free, output, and error callbacks. Other
 *	callbacks are ignored.
 *
 * Arguments:
 *
 *	caller_context		Uninterpreted data returned to callbacks
 *	callbacks		Structure of version & callbacks
 *	trace_file		Name of trace file (may be NULL)
 *	trace_handle		Pointer to returned handle
 *
 * Callbacks:
 *
 *	MALLOC, FREE
 *
 * Return value:
 *
 *	0			Successful completion
 *	ENOMEM			Can't allocate context info
 *	ENOENT			File not found
 *	EVERSION		Unsupported version
 *	(others from callbacks, if any)
 */
extern int
pthreadDebugTraceOpen (
    void *,
    pthreadDebugCallbacks_p,
    char *,
    pthreadDebugTraceHandle_p);

/*
 * pthreadDebugTraceDestroy
 *
 *	This routine destroys a trace stream initialized with
 *	pthreadDebugTraceInit
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *
 * Callbacks:
 *
 *	SUSPEND, FREE, GETMEM, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context not valid
 */
extern int
pthreadDebugTraceDestroy (pthreadDebugContext_t);

/*
 * pthreadDebugTraceInit
 *
 *	Initializes a debug context for access to the active log engine trace
 *	buffers (if any) in the process connected to the debug_context.
 *
 * Arguments:
 *
 *	trace_context		New trace context
 *	debug_context		The debug context to use
 *
 * Callbacks:
 *
 *	MALLOC, GETMEM, SUSPEND, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	ENOMEM			Can't allocate context info
 *	EINVAL			debug context invalid
 *	ESRCH			target process isn't tracing
 *	(others from callbacks, if any)
 */
extern int
pthreadDebugTraceInit (
    pthreadDebugTraceHandle_p,
    pthreadDebugContext_t);

/*
 * pthreadDebugTraceSeqDestroy
 *
 *	This routine destroys a trace sequence iterator, after processing a
 *	set of trace records.
 *
 * Arguments:
 *
 *	trace_handle		Pointer to trace context handle
 *
 * Callbacks:
 *
 *	RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	EBUSY			Active traversal of wrong type
 *	EINVAL			trace context invalid, or no iterator
 */
extern int
pthreadDebugTraceSeqDestroy (pthreadDebugTraceHandle_t);

/*
 * pthreadDebugTraceSeqInit
 *
 *	This routine creates a trace sequence iterator, to allow the caller to
 *	process the trace records in the active stream. Note that, unless the
 *	active trace stream is a file, the iterator may be unable to return
 *	all records, as it can access only records currently in the target
 *	process' address space (active trace buffers).
 *
 *	This routine will search the available trace stream for the first
 *	record with a sequence number greater than or equal to the "sequence"
 *	argument. If none can be found, ENOENT is returned; otherwise the
 *	first record is copied to the output buffer ("first_trace").
 *
 *	The information returned (particularly the stack trace and arguments,
 *	to which the buffer contains only pointers) is valid only until the
 *	iterator is advanced (by calling pthreadDebugTraceSeqNext) or
 *	destroyed (by calling pthreadDebugTraceSeqDestroy). To save trace
 *	information for later use, the caller must copy the stack trace and
 *	argument data elsewhere.
 *
 *	The caller must not modify the stack trace or argument data to which
 *	the trace record buffer points.
 *
 * Arguments:
 *
 *	trace_handle		Pointer to trace context handle
 *	sequence		First sequence number (usually 0)
 *	first_trace		Pointer to trace record buffer
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, GETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			trace context invalid, or no iterator
 *	ENOMEM			Unable to allocate internal resources
 *	ENOENT			No trace records available
 */
extern int
pthreadDebugTraceSeqInit (
    pthreadDebugTraceHandle_t,
    unsigned long,
    pthreadDebugTraceHead_p);

/*
 * pthreadDebugTraceSeqNext
 *
 *	This routine returns the next record (if any) of the trace stream
 *	initialized by calling pthreadDebugTraceSeqInit.
 *
 *	The information returned (particularly the stack trace and arguments,
 *	to which the buffer contains only pointers) is valid only until the
 *	iterator is advanced (by calling pthreadDebugTraceSeqNext) or
 *	destroyed (by calling pthreadDebugTraceSeqDestroy). To save trace
 *	information for later use, the caller must copy the stack trace and
 *	argument data elsewhere.
 *
 *	The caller must not modify the stack trace or argument data to which
 *	the trace record buffer points.
 *
 * Arguments:
 *
 *	trace_handle		Pointer to trace context handle
 *	trace			Pointer to trace record buffer
 *
 * Callbacks:
 *
 *	none
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			trace context invalid, or no iterator
 *	ENOENT			No more trace records available
 */
extern int
pthreadDebugTraceSeqNext (
    pthreadDebugTraceHandle_t,
    pthreadDebugTraceHead_p);

/*
 * pthreadDebugTraceFormat
 *
 *	This routine creates an ASCII representation of the current trace
 *	record, and writes it using the output callback (specified on
 *	pthreadDebugTraceOpen either directly or through the use of a
 *	debug_context).
 *
 * Arguments:
 *
 *	trace_handle		Pointer to trace context handle
 *	detail			Level of detail desired
 *	flags			Formatting flags
 *
 * Callbacks:
 *
 *	none
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			Trace context invalid, or no current record
 *	ENOSYS			No output callback available
 */
extern int
pthreadDebugTraceFormat (
    pthreadDebugTraceHandle_t,
    pthreadDebugTraceDetail_t,
    pthreadDebugTraceFmt_t);

/*
 * pthreadDebugTraceArgSeqDestroy
 *
 *	This routine destroys a trace record argument iterator.
 *
 * Arguments:
 *
 *	trace_handle		Pointer to trace context handle
 *	trace			Pointer to trace record buffer
 *
 * Callbacks:
 *
 *	none
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			trace context invalid, or no iterator
 */
extern int
pthreadDebugTraceArgSeqDestroy (pthreadDebugTraceHandle_t);

/*
 * pthreadDebugTraceArgSeqInit
 *
 *	This routine creates a trace record argument iterator, by which the
 *	caller may iterate through the current trace record arguments.
 *	(Instead of parsing the argument array directly from the trace
 *	record.)
 *
 * Arguments:
 *
 *	trace_handle		Pointer to trace context handle
 *	type			Return PTHREAD_TRACE_TYPE_* value for argument
 *	size			Return the size of the argument
 *	data			Return pointer to the data
 *
 * Callbacks:
 *
 *	none
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			trace context invalid, or no iterator
 *	ENOENT			No current trace record
 */
extern int
pthreadDebugTraceArgSeqInit (
    pthreadDebugTraceHandle_t,
    pthreadTraceType_p,
    size_t *,
    void * const *);

/*
 * pthreadDebugTraceArgSeqNext
 *
 *	This routine returns the next argument in the current trace record.
 *
 * Arguments:
 *
 *	trace_handle		Pointer to trace context handle
 *	type			Return PTHREAD_TRACE_TYPE_* value for argument
 *	size			Return the size of the argument
 *	data			Return pointer to the data
 *
 * Callbacks:
 *
 *	none
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			trace context invalid, or no iterator
 *	ENOENT			No more arguments
 */
extern int
pthreadDebugTraceArgSeqNext (
    pthreadDebugTraceHandle_t,
    pthreadTraceType_p,
    size_t *,
    void * const *);

/*
 * pthreadDebugTraceClassGet
 *
 *	This routine returns the trace class mask enabled for the target
 *	process.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	classes			Pointer to mask
 *
 * Callbacks:
 *
 *	GETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	EINVAL			debug context invalid
 */
extern int
pthreadDebugTraceClassGet (
    pthreadDebugContext_t,
    unsigned long *);

/*
 * pthreadDebugTraceClassSet
 *
 *	This routine sets the trace class mask enabled for the target process
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	how			set, clear, replace
 *	classes			new class mask
 *
 * Callbacks:
 *
 *	SUSPEND, RESUME, GETMEM, SETMEM
 *
 * Return value:
 *
 *	0			Successful completion
 *	ENOSYS			Target process isn't tracing
 *	EINVAL			debug context invalid, or invalid class bits
 */
extern int
pthreadDebugTraceClassSet (
    pthreadDebugContext_t,
    pthreadDebugTraceSetHow_t,
    unsigned long);

/*
 * pthreadDebugTraceLoad
 *
 *	This routine requests that the target process load a (new) trace
 *	engine, and initialize it.
 *
 * Arguments:
 *
 *	debug_context		The debug context to use
 *	library			Name of trace engine
 *	argc			Count of arguments in argv
 *	argv			Pointer to array of argument pointers
 *
 * Callbacks:
 *
 *	SETMEM, GETMEM, SUSPEND, RESUME
 *
 * Return value:
 *
 *	0			Successful completion
 *	ENOSYS			Target process isn't tracing
 *	EINVAL			debug context invalid, or invalid class bits
 */
extern int
pthreadDebugTraceLoad (
    pthreadDebugContext_t,
    char *,
    int,
    char *[]);

/*
 * End of TRACE STREAM SUPPORT
 */

/*
 *				PROFILING HOOKS
 *
 * The following section deserves a separate header, but I'm crunching it in
 * here for now because the interfaces share some symbols and types with the
 * other debug interfaces.
 *
 * The earlier part of this header was dedicated to interfaces supported by
 * the debug assistant library, for use by debugger code that runs in another
 * process. The following interfaces are for profilers that run within the
 * DECthreads process. They are minimal and preliminary at this point.
 *
 * BEWARE: the in-process hook routines are called in places where the
 * DECthreads scheduling database may be LOCKED. You CANNOT make any calls to
 * the thread library, or to libc, within the hook routine. (This should be OK
 * for ATOM tools, but probably not for much of anything else.)
 */

/*
 * Prototypes showing the arguments passed to the hook routines (set by
 * __pthread_debug_set_hook).
 */

/*
 * Thread is activating (running for the first time)
 *
 *	event		PTHREAD_DEBUG_EVENT_ACTIVATING
 *	thread		The new thread's TEB pointer
 *	start_routine	Address of the start routine
 *	start_argument	The argument passed to start_routine
 *	spare		Unused
 *	flags		Flags (none currently defined)
 */
typedef void (*pthreadDebugHookActivating_t) (
	pthreadDebugEvent_t,
	pthread_t,
	void *(*) (void *),
	void *,
	void *,
	unsigned long);

/*
 * Thread is blocking
 *
 *	event		PTHREAD_DEBUG_EVENT_BLOCKING
 *	thread		The thread's TEB pointer
 *	substate	One of KERNEL, MUTEX, CV, TIMED_CV
 *	object		Address of blocking object, or NULL
 *	spare		Unused
 *	flags		Flags (none currently defined)
 */
typedef void (*pthreadDebugHookBlocking_t) (
	pthreadDebugEvent_t,
	pthread_t,
	pthreadDebugSubstate_t,
	void *,
	void *,
	unsigned long);

/*
 * Thread is being created
 *
 *	event		PTHREAD_DEBUG_EVENT_CREATING
 *	thread		The creating thread's TEB pointer
 *	new_thread	The new thread's TEB pointer
 *	start_routine	Address of the start routine
 *	start_argument	Argument passed to start routine
 *	flags		Flags (none currently defined)
 */
typedef void (*pthreadDebugHookCreating_t) (
	pthreadDebugEvent_t,
	pthread_t,
	pthread_t,
	void *(*) (void *),
	void *,
	unsigned long);

/*
 * Thread is running (after having blocked or been preempted)
 *
 *	event		PTHREAD_DEBUG_EVENT_RUNNING
 *	thread		The thread's TEB pointer
 *	substate	Thread's previous substate
 *	previous	TEB pointer for previous thread
 *	spare		Unused
 *	flags		Flags (preempted, kernel)
 */
typedef void (*pthreadDebugHookRunning_t) (
	pthreadDebugEvent_t,
	pthread_t,
	pthreadDebugSubstate_t,
	pthread_t,
	void *,
	unsigned long);

/*
 * Thread is terminating
 *
 *	event		PTHREAD_DEBUG_EVENT_TERMINATING
 *	thread		The thread's TEB pointer
 *	substate	Reason for termination: normal, term_cancel
 *			(cancelled) or term_exit (pthread_exit)
 *	result		Thread's result value
 *	spare		Unused
 *	flags		Flags (locks)
 */
typedef void (*pthreadDebugHookTerminating_t) (
	pthreadDebugEvent_t,
	pthread_t,
	pthreadDebugSubstate_t,
	void *,
	void *,
	unsigned long);

/*
 * The DECthreads code has been initialized
 *
 *	event		PTHREAD_DEBUG_EVENT_INITIALIZED
 *	thread		TEB pointer of initializing thread
 *	spare		Unused
 *	spare		Unused
 *	spare		Unused
 *	flags		Flags (none currently defined)
 */
typedef void (*pthreadDebugHookInitialized_t) (
	pthreadDebugEvent_t,
	pthread_t,
	void *,
	void *,
	void *,
	unsigned long);

/*
 * Thread is freeing a zombie TCB
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_FREEING
 *	thread		Thread's TEB pointer
 *	freed		TEB of thread being freed
 *	spare		Unused
 *	spare		Unused
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugHookFreeing_t) (
	pthreadDebugEvent_t,
	pthread_t,
	pthread_t,
	void *,
	void *,
	unsigned long);

/*
 * Thread is unblocked from a wait (CV, Mutex, etc.)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_UNBLOCK
 *	thread		Unblocking thread's TEB pointer
 *	substate	One of KERNEL, MUTEX, CV, TIMED_CV
 *	unblock		Unblocked thread's sequence number
 *	spare		Unused
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugHookUnblock_t) (
	pthreadDebugEvent_t,
	pthread_t,
	pthreadDebugSubstate_t,
	pthread_t,
	void *,
	unsigned long);

/*
 * DECthreads bugcheck (unrecoverable inconsistency)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_BUGCHECK
 *	thread		Bugchecking thread's TEB pointer
 *	reason		String describing reason
 *	spare		Unused argument
 *	spare		Unused argument
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugHookBugcheck_t) (
	pthreadDebugEvent_t,
	pthread_t,
	char *,
	void *,
	void *,
	unsigned long);

/*
 * DECthreads last-chance handler (exception not handled by thread)
 *
 * Arguments:
 *
 *	event		PTHREAD_DEBUG_EVENT_LASTCHANCE
 *	thread		Thread's TEB pointer
 *	spare1		Unused argument
 *	spare2		Unused argument
 *	spare3		Unused argument
 *	flags		Flags (none currently defined)
 *
 * Return value:
 *
 *	none
 */
typedef void (*pthreadDebugHookLastchance_t) (
	pthreadDebugEvent_t,
	pthread_t,
	void *,
	void *,
	void *,
	unsigned long);

extern int
__pthread_debug_clear_event (pthreadDebugEvent_t);

extern int
__pthread_debug_set_hook (
	pthreadDebugEvent_t,
	void *);

extern int
__pthread_debug_set_event (pthreadDebugEvent_t);

/*
 * Restore the pointer size environment for VMS
 */
#if defined (_PTHREAD_ENV_ALPHA) && defined (_PTHREAD_ENV_VMS)
# pragma __required_pointer_size __restore
#endif

#ifdef __cplusplus
    }
#endif

#endif /* _PTHREAD_DEBUG_H_ */
