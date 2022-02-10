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
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1994    *
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
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
#ifndef __C_EXCPT_H
#define __C_EXCPT_H
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__LANGUAGE_C) || defined(__LANGUAGE_C__) || defined(__cplusplus)

#include <excepthdr.h>

#ifdef _INCLUDE_ID
#pragma ident "$Header: /usr/sde/osf1/rcs/os/src/usr/include/alpha/c_excpt.h,v 1.1.8.3 1995/08/15 18:51:34 Thomas_Peterson Exp $"
#endif

/* 
** C Structured Exception Handling.
*/


/* definitions of keywords and intrinsic function names */
#ifndef __cplusplus
#define try                    __builtin_try
#endif
#define except                 __builtin_except
#define leave                  __builtin_leave
#define finally                __builtin_finally

/* Definitions of filter constants */
#define	EXCEPTION_CONTINUE_EXCEPTION	(-1)	/* act like nothing happened */
#define	EXCEPTION_CONTINUE_SEARCH	(0)	/* not me, look for another */
#define	EXCEPTION_EXECUTE_HANDLER	(1)	/* I'll take it */

/*
 * Scope table definition
*/

typedef struct {
    unsigned long count;   /* number of scope records follows */
    struct 
    {
	unsigned long  begin_address;	/* begin guarded block address */
	unsigned long  end_address;	/* end guarded block address */
	unsigned long  handle_address;	/* finally handler/filter for block */
	unsigned long  jmp_target;	/* jump target if exc is handled */
    } scope_record[1];
} SCOPE_TABLE;

extern void
__jump_unwind(void* Frame_ptr, void* target_ip)
;
extern EXCEPTION_DISPOSITION
__C_specific_handler(system_exrec_type *   exception_record,
		     void *                establisher_frame,
		     PCONTEXT              context_record,
		     DISPATCHER_CONTEXT *  dispatcher_context)
;

/* Typedef for pointer returned by exception_info() */ 

typedef struct _EXCEPTION_POINTERS
{
    system_exrec_type*		ExceptionRecord;
    PCONTEXT			ContextRecord;
    EXCEPTION_DISPOSITION	Disposition;
    DISPATCHER_CONTEXT		*DispatcherContext;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS, *Exception_info_ptr;

typedef
int
(* EXCEPTION_FILTER) ( EXCEPTION_POINTERS * ExceptionPtr );

typedef
void
(* TERMINATION_HANDLER) (unsigned long is_abnormal );

#ifdef __DECC
long  __exception_code();
#define exception_code() __exception_code()
Exception_info_ptr __exception_info();
#define exception_info() __exception_info()
int __abnormal_termination();
#define abnormal_termination() __abnormal_termination()

#else
#define exception_code()       __exception_code
#define exception_info()       __exception_info
#define abnormal_termination() __abnormal_termination
#endif

#endif /* __LANGUAGE_C__ */

#ifdef __cplusplus
}
#endif
#endif /* __C_EXCPT_H */
