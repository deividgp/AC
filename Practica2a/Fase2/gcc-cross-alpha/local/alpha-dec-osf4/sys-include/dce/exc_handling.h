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
 * @(#)$RCSfile: exc_handling.h,v $ $Revision: 4.2.24.2 $ (DEC) $Date: 1998/10/02 21:41:53 $
 */
/*
 *  FACILITY:
 *
 *	DECthreads core
 *
 *  FILENAME:
 *
 *	EXC_HANDLING.H
 *
 *  ABSTRACT:
 *
 *	Header file for exception handling in C
 *
 *  AUTHORS:
 *
 *	Eric Roberts
 *	Bob Conti
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	15 March 1989
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Bob Conti
 *	Paul Curtin
 *	Webb Scales
 *	Peter Portante
 *	Brian Silver
 *
 *  LAST MODIFICATION DATE:
 *
 *	16 September 1998
 */


#ifndef EXC_HANDLING
#define EXC_HANDLING	1

#ifdef __cplusplus
    extern "C" {
#endif

/*
 *  INCLUDE FILES
 */

#include <pthread_exception.h>

#ifndef CMA_CONFIG
# if defined(vms) || defined(__vms) || defined (VMS) || defined(__VMS) || defined(__vms__)
#  include <cma_config.h>
# else
#  include <dce/cma_config.h>
# endif
#endif

#if ((_CMA_COMPILER_ == _CMA__DECC) || (_CMA_COMPILER_ == _CMA__DECCPLUS)) && _CMA_OS_ == _CMA__VMS
# pragma __extern_model __save
# pragma __extern_model __strict_refdef
#elif _CMA_COMPILER_ == _CMA__VAXC
# pragma nostandard
#endif

/*
 * Many of the type names in this source are derived from type names
 * in PTHREAD_EXCEPTION.H, so let's do the derivation here.  Or, if
 * the nearly equivalent type in PTHREAD_EXCEPTION.H is not exactly
 * what "it" used to be in EXC_HANDLING.H (old CORE version), just
 * define it here.
 */

typedef __pthreadExcAddr_t		exc_address_t;
typedef __pthreadExcKind_t		exc_kind_t;
typedef __pthreadExcExt_t		exc_ext_t;
typedef __pthreadExcKindV1Addr_t	exc_kind_v1addr_t;
typedef __pthreadExcKindV1Status_t	exc_kind_v1status_t;

typedef __pthreadExcKindAddr_t		exc_kind_address_t;
typedef __pthreadExcKindStatus_t	exc_kind_status_t;
typedef __pthreadExcState_t		exc_state_t;

#define exc_kind_none_c			_PTHREAD_EXC_KIND_NONE
#define exc_kind_address_c		_PTHREAD_EXC_KIND_ADDR
#define exc_kind_status_c		_PTHREAD_EXC_KIND_STATUS

typedef __pthreadExcCtx_t		exc_context_t;

#define exc_newexc_c			_PTHREAD_EXC_NEWMAGIC
#define exc_v2exc_c			_PTHREAD_EXC_VER_V2
#define exc_v3exc_c			_PTHREAD_EXC_VER_V3
#define exc_curr_c			_PTHREAD_EXC_VER_CUR

/*
 * Use the most efficient code available to determine the address of the
 * current procedure frame on VAX VMS systems (which we need to integrate
 * well with native VAX VMS condition handling).
 *
 * - VAX C under VAX VMS supports instruction "builtins" to access general
 *   registers.
 *
 * - GCC supports an "asm" statement that generates inline assembly code.
 *
 * - Otherwise, declare an extern function (part of DECthreads' assembly
 *   code) that will return the value.
 */
#if _CMA_OS_ == _CMA__VMS
# define exc_fetch_fp   pthread_exc_fetch_fp_np
#endif

/*
 * Define all of the status codes used by DECthreads.
 *
 * These values cannot be altered, since they have shipped to customers!
 */

/*
 * EXC facility messages
 */
#define exc_s_exception		_PTHREAD_STATUS_(1, 4)
#define exc_s_exccop		_PTHREAD_STATUS_(2, 4)
#define exc_s_uninitexc		_PTHREAD_STATUS_(3, 4)
#define exc_s_unkstatus		_PTHREAD_STATUS_(128, 4)
#define exc_s_exccoplos		_PTHREAD_STATUS_(129, 4)

/*
 * These should be set to match with underlying system exception codes on
 * platforms where that is appropriate (e.g., ss$_ codes on VMS).
 */

#if defined (_PTHREAD_EXC_VMS)
/*
 * A few of these codes are somewhat imaginary, since VMS doesn't support
 * condition codes that very closely approximate the sense of some UNIX
 * signals.  SIGTRAP, SIGABRT (SIGIOT), and SIGEMT have no clear parallels,
 * and the values chosen are fairly arbitrary.  For two others, we chose what
 * seemed close equivalents: SIGPIPE becomes "no mailbox", and SIGXFSZ becomes
 * "disk quota exceeded".
 */
# define exc_s_illaddr		12	/* ss$_accvio */
# define exc_s_exquota		28	/* ss$_exquota */
# define exc_s_insfmem		292	/* ss$_insfmem */
# define exc_s_nopriv		36	/* ss$_nopriv */
# define exc_s_normal		1	/* ss$_normal */
# define exc_s_illinstr		1084	/* ss$_opcdec */
# define exc_s_resaddr		1100	/* ss$_radrmod */
# define exc_s_privinst		1084	/* ss$_opcdec */
# define exc_s_resoper		1108	/* ss$_roprand */
# define exc_s_SIGTRAP		1044	/* ss$_break */
# define exc_s_SIGABRT		44	/* ss$_abort */
# define exc_s_SIGEMT		1068	/* ss$_compat */
# define exc_s_aritherr		1164	/* ss$_fltovf */
# define exc_s_SIGSYS		20	/* ss$_badparam */
# define exc_s_SIGPIPE		628	/* ss$_nombx */
# define exc_s_excpu		8364	/* ss$_excputim */
# define exc_s_exfilsiz		1004	/* ss$_exdiskquota */
# define exc_s_intovf		1148	/* ss$_intovf */
# define exc_s_intdiv		1156	/* ss$_intdiv */
# define exc_s_fltovf		1164	/* ss$_fltovf */
# define exc_s_fltdiv		1172	/* ss$_fltdiv */
# define exc_s_fltund		1180	/* ss$_fltund */
# define exc_s_decovf		1188	/* ss$_decovf */
# define exc_s_subrng		1196	/* ss$_subrng */
#else
# define exc_s_illaddr		_PTHREAD_STATUS_(5, 4)
# define exc_s_exquota		_PTHREAD_STATUS_(6, 4)
# define exc_s_insfmem		_PTHREAD_STATUS_(7, 4)
# define exc_s_nopriv		_PTHREAD_STATUS_(8, 4)
# define exc_s_normal		_PTHREAD_STATUS_(9, 1)
# define exc_s_illinstr		_PTHREAD_STATUS_(10, 4)
# define exc_s_resaddr		_PTHREAD_STATUS_(11, 4)
# define exc_s_privinst		_PTHREAD_STATUS_(12, 4)
# define exc_s_resoper		_PTHREAD_STATUS_(13, 4)
# define exc_s_SIGTRAP		_PTHREAD_STATUS_(14, 4)
# define exc_s_SIGABRT		_PTHREAD_STATUS_(15, 4)
# define exc_s_SIGEMT		_PTHREAD_STATUS_(16, 4)
# define exc_s_aritherr		_PTHREAD_STATUS_(17, 4)
# define exc_s_SIGSYS		_PTHREAD_STATUS_(18, 4)
# define exc_s_SIGPIPE		_PTHREAD_STATUS_(19, 4)
# define exc_s_excpu		_PTHREAD_STATUS_(20, 4)
# define exc_s_exfilsiz		_PTHREAD_STATUS_(21, 4)
# define exc_s_intovf		_PTHREAD_STATUS_(22, 4)
# define exc_s_intdiv		_PTHREAD_STATUS_(23, 4)
# define exc_s_fltovf		_PTHREAD_STATUS_(24, 4)
# define exc_s_fltdiv		_PTHREAD_STATUS_(25, 4)
# define exc_s_fltund		_PTHREAD_STATUS_(26, 4)
# define exc_s_decovf		_PTHREAD_STATUS_(27, 4)
# define exc_s_subrng		_PTHREAD_STATUS_(28, 4)
#endif

/*
 * Define alias names
 */
#define exc_s_accvio		exc_s_illaddr
#define exc_s_SIGILL		exc_s_illinstr
#define exc_s_SIGFPE		exc_s_aritherr
#define exc_s_SIGBUS		exc_s_illaddr
#define exc_s_SIGSEGV		exc_s_illaddr
#define exc_s_SIGXCPU		exc_s_excpu
#define exc_s_SIGXFSZ		exc_s_exfilsiz
#define exc_s_SIGIOT		exc_s_SIGABRT


/*
 * Synonyms for convenience
 */
#define cma_s_normal		exc_s_normal
#define cma_s_alerted		pthread_cancel_s
#define cma_s_exit_thread	pthread_exit_s
#define cma_s_stackovf		pthread_stackovf_s
#define cma_s_unimp		_PTHREAD_UNIMP_S

/*
 * CMA-specific status codes
 */
#define cma_s_assertion		_PTHREAD_STATUS_(49, 4)
#define cma_s_badparam		_PTHREAD_STATUS_(50, 4)
#define cma_s_bugcheck		_PTHREAD_STATUS_(51, 4)
#define cma_s_existence		_PTHREAD_STATUS_(53, 4)
#define cma_s_in_use		_PTHREAD_STATUS_(54, 4)
#define cma_s_use_error		_PTHREAD_STATUS_(55, 4)
#define cma_s_wrongmutex	_PTHREAD_STATUS_(56, 4)
#define cma_s_nostackmem	_PTHREAD_STATUS_(58, 4)
#define cma_s_notcmastack	_PTHREAD_STATUS_(59, 4)
#define cma_s_timed_out		_PTHREAD_STATUS_(60, 4)
#define cma_s_inialrpro		_PTHREAD_STATUS_(62, 4)
#define cma_s_defer_q_full	_PTHREAD_STATUS_(63, 4)
#define cma_s_signal_q_full	_PTHREAD_STATUS_(64, 4)
#define cma_s_alert_nesting	_PTHREAD_STATUS_(65, 4)

/*
 * TYPEDEFS
 */

/*
 * Most of the interface typedefs are in PTHREAD_EXCEPTION.H, but a
 * few stragglers must appear here.
 */

/*
 * Internal contents of an exception object.
 */
typedef long int exc_int_t;


/*
 *  GLOBAL DATA
 */

#if !defined(_CMA_SUPPRESS_EXTERNALS_) && !defined(_CMA_CORE_BUILD_)
# define exc_push_ctx		pthread_exc_push_ctx_np
# define exc_pop_ctx            pthread_exc_pop_ctx_np
# define exc_raise              pthread_exc_raise_np
# define exc_raise_status       pthread_exc_raise_status_np
# define exc_report             pthread_exc_report_np
# define exc_get_message        pthread_exc_get_message_np
#endif


#if _CMA_OS_ == _CMA__VMS
/*
 * On OpenVMS, we use the native condition handling mechanism to implement
 * DECthreads exceptions; thus we need a condition handler.
 */
# define exc_handler	pthread_exc_handler_np
#endif

/*
 * Define the exception variables
 *
 * NOTE: it does not make sense to turn all DECthreads status codes into
 * exceptions as some are never raised.	 Those are:
 *
 *	cma_s_normal	-- never signalled
 *	cma_s_exception	-- internal to the implementation of exceptions
 *	cma_s_exccop	-- internal to the implementation of exceptions
 *	cma_s_timed_out	-- returned as status value from timed condition wait
 */

#if (_CMA_OS_ == _CMA__VMS) && !defined (_CMA_CORE_BUILD_)
# if defined (__STDC__) || _CMA_COMPILER_ == _CMA__DECCPLUS
#  define _CMA_EXCNAME(name)	cma$e_##name
#  define _CMA_CMANAME(name)	cma$e_##name
# else
#  define _CMA_EXCNAME(name)	cma$e_/**/name
#  define _CMA_CMANAME(name)	cma$e_/**/name
# endif
#else
# if defined (__STDC__) || (_CMA_COMPILER_ == _CMA__DECCPLUS) || (_CMA_COMPILER_ == _CMA__MSC)
#  define _CMA_EXCNAME(name)	exc_e_##name
#  define _CMA_CMANAME(name)	cma_e_##name
# else
#  define _CMA_EXCNAME(name)	exc_e_/**/name
#  define _CMA_CMANAME(name)	cma_e_/**/name
# endif
#endif

#if _CMA_OS_ == _CMA__VMS && !defined(_CMA_CORE_BUILD_)
/*
 * Define exc_e_ or cma_e_ aliases for the cma$e_ names.  The purpose of
 * all this is to use the "VMS calling standard" names (cma$rtl)
 * regardless of whether the client code uses the VMS or portable
 * DECthreads interfaces, so that use of exceptions never requires the
 * cma$open_rtl image.
 */
# define exc_e_uninitexc	cma$e_uninitexc
# define exc_e_illaddr		cma$e_illaddr
# define exc_e_exquota		cma$e_exquota
# define exc_e_insfmem		cma$e_insfmem
# define exc_e_nopriv		cma$e_nopriv
# define exc_e_illinstr		cma$e_illinstr
# define exc_e_resaddr		cma$e_resaddr
# define exc_e_privinst		cma$e_privinst
# define exc_e_resoper		cma$e_resoper
# define exc_e_SIGTRAP		cma$e_SIGTRAP
# define exc_e_SIGIOT		cma$e_SIGIOT
# define exc_e_SIGEMT		cma$e_SIGEMT
# define exc_e_aritherr		cma$e_aritherr
# define exc_e_SIGSYS		cma$e_SIGSYS
# define exc_e_SIGPIPE		cma$e_SIGPIPE
# define exc_e_excpu		cma$e_excpu
# define exc_e_exfilsiz		cma$e_exfilsiz
# define exc_e_intovf		cma$e_intovf
# define exc_e_intdiv		cma$e_intdiv
# define exc_e_fltovf		cma$e_fltovf
# define exc_e_fltdiv		cma$e_fltdiv
# define exc_e_fltund		cma$e_fltund
# define exc_e_decovf		cma$e_decovf
# define exc_e_subrng		cma$e_subrng
 
# define cma_e_alerted		cma$e_alerted
# define cma_e_assertion	cma$e_assertion
# define cma_e_badparam		cma$e_badparam
# define cma_e_bugcheck		cma$e_bugcheck
# define cma_e_exit_thread	cma$e_exit_thread
# define cma_e_existence	cma$e_existence
# define cma_e_in_use		cma$e_in_use
# define cma_e_use_error	cma$e_use_error
# define cma_e_wrongmutex	cma$e_wrongmutex
# define cma_e_stackovf		cma$e_stackovf
# define cma_e_nostackmem	cma$e_nostackmem
# define cma_e_notcmastack	cma$e_notcmastack
# define cma_e_unimp		cma$e_unimp
# define cma_e_inialrpro	cma$e_inialrpro
# define cma_e_defer_q_full	cma$e_defer_q_full
# define cma_e_signal_q_full	cma$e_signal_q_full
# define cma_e_alert_nesting	cma$e_alert_nesting
#endif

#if !defined (_EXC_NO_EXCEPTIONS_) && !defined (_CMA_SUPPRESS_EXTERNALS_)
_CMA_IMPORT_ EXCEPTION
    _CMA_EXCNAME (uninitexc),
    _CMA_EXCNAME (illaddr),
    _CMA_EXCNAME (exquota),
    _CMA_EXCNAME (insfmem),
    _CMA_EXCNAME (nopriv),
    _CMA_EXCNAME (illinstr),
    _CMA_EXCNAME (resaddr),
    _CMA_EXCNAME (privinst),
    _CMA_EXCNAME (resoper),
    _CMA_EXCNAME (SIGTRAP),
    _CMA_EXCNAME (SIGIOT),
    _CMA_EXCNAME (SIGEMT),
    _CMA_EXCNAME (aritherr),
    _CMA_EXCNAME (SIGSYS),
    _CMA_EXCNAME (SIGPIPE),
    _CMA_EXCNAME (excpu),
    _CMA_EXCNAME (exfilsiz),
    _CMA_EXCNAME (intovf),
    _CMA_EXCNAME (intdiv),
    _CMA_EXCNAME (fltovf),
    _CMA_EXCNAME (fltdiv),
    _CMA_EXCNAME (fltund),
    _CMA_EXCNAME (decovf),
    _CMA_EXCNAME (subrng),

    _CMA_CMANAME (alerted),
    _CMA_CMANAME (assertion),
    _CMA_CMANAME (badparam),
    _CMA_CMANAME (bugcheck),
    _CMA_CMANAME (exit_thread),
    _CMA_CMANAME (existence),
    _CMA_CMANAME (in_use),
    _CMA_CMANAME (use_error),
    _CMA_CMANAME (wrongmutex),
    _CMA_CMANAME (stackovf),
    _CMA_CMANAME (nostackmem),
    _CMA_CMANAME (notcmastack),
    _CMA_CMANAME (unimp),
    _CMA_CMANAME (inialrpro),
    _CMA_CMANAME (defer_q_full),
    _CMA_CMANAME (signal_q_full),
    _CMA_CMANAME (alert_nesting);
#endif

/*
 * Define aliased exceptions
 */

#define exc_e_accvio		_CMA_EXCNAME (illaddr)
#define exc_accvio_e		_CMA_EXCNAME (illaddr)
#define exc_e_SIGILL		_CMA_EXCNAME (illinstr)
#define exc_SIGILL_e		_CMA_EXCNAME (illinstr)
#define exc_e_SIGFPE		_CMA_EXCNAME (aritherr)
#define exc_SIGFPE_e		_CMA_EXCNAME (aritherr)
#define exc_e_SIGBUS		_CMA_EXCNAME (illaddr)
#define exc_SIGBUS_e		_CMA_EXCNAME (illaddr)
#define exc_e_SIGSEGV		_CMA_EXCNAME (illaddr)
#define exc_SIGSEGV_e		_CMA_EXCNAME (illaddr)
#define exc_e_SIGXCPU		_CMA_EXCNAME (excpu)
#define exc_SIGXCPU_e		_CMA_EXCNAME (excpu)
#define exc_e_SIGXFSZ		_CMA_EXCNAME (exfilsiz)
#define exc_SIGXFSZ_e		_CMA_EXCNAME (exfilsiz)
#define exc_e_SIGABRT		_CMA_EXCNAME (SIGIOT)

/*
 * The following are pthread exception names.
 */

#define exc_uninitexc_e		_CMA_EXCNAME (uninitexc)
#define exc_illaddr_e		_CMA_EXCNAME (illaddr)
#define exc_exquota_e		_CMA_EXCNAME (exquota)
#define exc_insfmem_e		_CMA_EXCNAME (insfmem)
#define exc_nopriv_e		_CMA_EXCNAME (nopriv)
#define exc_illinstr_e		_CMA_EXCNAME (illinstr)
#define exc_resaddr_e		_CMA_EXCNAME (resaddr)
#define exc_privinst_e		_CMA_EXCNAME (privinst)
#define exc_resoper_e		_CMA_EXCNAME (resoper)
#define exc_SIGTRAP_e		_CMA_EXCNAME (SIGTRAP)
#define exc_SIGABRT_e		_CMA_EXCNAME (SIGIOT)
#define exc_SIGIOT_e		_CMA_EXCNAME (SIGIOT)
#define exc_SIGEMT_e		_CMA_EXCNAME (SIGEMT)
#define exc_aritherr_e		_CMA_EXCNAME (aritherr)
#define exc_SIGSYS_e		_CMA_EXCNAME (SIGSYS)
#define exc_SIGPIPE_e		_CMA_EXCNAME (SIGPIPE)
#define exc_excpu_e		_CMA_EXCNAME (excpu)
#define exc_exfilsiz_e		_CMA_EXCNAME (exfilsiz)
#define exc_intovf_e		_CMA_EXCNAME (intovf)
#define exc_intdiv_e		_CMA_EXCNAME (intdiv)
#define exc_fltovf_e		_CMA_EXCNAME (fltovf)
#define exc_fltdiv_e		_CMA_EXCNAME (fltdiv)
#define exc_fltund_e		_CMA_EXCNAME (fltund)
#define exc_decovf_e		_CMA_EXCNAME (decovf)
#define exc_subrng_e		_CMA_EXCNAME (subrng)

#define pthread_assertion_e	_CMA_CMANAME (assertion)
#define pthread_badparam_e	_CMA_CMANAME (badparam)
#define pthread_bugcheck_e	_CMA_CMANAME (bugcheck)
#define pthread_exit_thread_e	_CMA_CMANAME (exit_thread)
#define pthread_existence_e	_CMA_CMANAME (existence)
#define pthread_in_use_e	_CMA_CMANAME (in_use)
#define pthread_use_error_e	_CMA_CMANAME (use_error)
#define pthread_wrongmutex_e	_CMA_CMANAME (wrongmutex)
#define pthread_nostackmem_e	_CMA_CMANAME (nostackmem)
#define pthread_notstack_e	_CMA_CMANAME (notcmastack)
#define pthread_unimp_e		_CMA_CMANAME (unimp)
#define pthread_inialrpro_e	_CMA_CMANAME (inialrpro)
#define pthread_defer_q_full_e	_CMA_CMANAME (defer_q_full)
#define pthread_signal_q_full_e _CMA_CMANAME (signal_q_full)

/*
 * CONSTANTS AND MACROS
 */

/*
 * Define "routine" to equivalence an exception to an integer
 * (typically a system-defined status value).
 */
#define exc_set_status(_e_,_s_) pthread_exc_set_status_np((_e_),(_s_))

/*
 * Define "routine" to return the status of an exception. Returns 0 if status
 * kind (and value of status in *s), or -1 if not status kind.
 */
#define exc_get_status(_e_,_s_) pthread_exc_get_status_np((_e_),(_s_))

/*
 * Define "routine" to determine if two exceptions match.
 */
#define exc_matches(_e1_,_e2_)  pthread_exc_matches_np((_e1_),(_e2_))


#if _CMA_OS_ == _CMA__VMS
/*
 * For VMS, try to integrate peacefully with native VMS condition
 * handling.
 */
# define exc_establish(_exc_ctx_)       pthread_exc_establish_np((_exc_ctx_))
# define exc_unestablish(_exc_ctx_)     pthread_exc_unestablish_np((_exc_ctx_))
#else
# define exc_establish(_exc_ctx_)
# define exc_unestablish(_exc_ctx_)
#endif


#if ((_CMA_COMPILER_ == _CMA__DECC) || (_CMA_COMPILER_ == _CMA__DECCPLUS)) && _CMA_OS_ == _CMA__VMS
# pragma __extern_model __restore
#elif _CMA_COMPILER_ == _CMA__VAXC
# pragma standard
#endif

#ifdef __cplusplus
    }
#endif

#endif
