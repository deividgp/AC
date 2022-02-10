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
 * @(#)$RCSfile: builtins.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1998/05/27 14:51:37 $
 */
/****************************************************************************
**
**  <builtins.h> - Prototypes for DEC C platform specific builtins
**
*****************************************************************************
**
**  Copyright Digital Equipment Corporation 1993, 1995. All rights reserved.
**
**  Restricted Rights: Use, duplication, or disclosure by the U.S.
**  Government is subject to restrictions as set forth in subparagraph
**  (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
**  52.227-14 Alt. III, as applicable.
**
**  This software is proprietary to and embodies the confidential
**  technology of Digital Equipment Corporation. Possession, use, or
**  copying of this software and media is authorized only pursuant to a
**  valid written license from Digital or an authorized sublicensor.
**
******************************************************************************
*/

#ifndef __BUILTINS_LOADED
#define __BUILTINS_LOADED 1

#if defined(__DECC) || defined(__DECCXX)

#ifdef __cplusplus
extern "C" {
#endif


#pragma __nostandard

/************************************************************
**  Part 1: DEC C builtins for atomic/interlocked operations.
*************************************************************
**
**  These functions are not easily/efficiently implemented using
**  inline assembly code, and so the compiler has builtin knowledge
**  of their names and signatures in order to generate fast and
**  reliable code (e.g. it may generate loops with tests arranged
**  for branch prediction using out-of-line branch targets for
**  failure paths).
**
**  The _RETRY variants store a non-zero status if the operation
**  completes successfully within the specified number of retries.
**  The variants without _RETRY do not return until they succeed.
**
**  Note that by convention the names _LONG and _QUAD designate
**  32-bit longword and 64-bit quadword operations (as defined by
**  the Alpha architecure), and should not be confused with the
**  C language type "long", which is 64-bits on Digital UNIX.
**
**  The following operations do not in themselves generate Memory
**  Barriers.  The user is expected to code explicitly any Memory
**  Barriers where needed using inline assembly code, e.g. asm("mb"),
**  or asm("wmb").  See /usr/include/c_asm.h for more information
**  on inline assembly code.
*/

/*
**  Atomic update of location with integer operation, returning
**  previous contents.
*/
int  __ATOMIC_ADD_LONG(volatile void *__address, int __expression);
int  __ATOMIC_ADD_LONG_RETRY(volatile void *__address,
			     int __expression,
			     int __retry,
			     int *__status);
long  __ATOMIC_ADD_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_ADD_QUAD_RETRY(volatile void *__address,
			      long __expression,
			      int __retry,
			      int *__status);

int  __ATOMIC_AND_LONG(volatile void *__address, int __expression);
int  __ATOMIC_AND_LONG_RETRY(volatile void *__address,
			     int __expression,
			     int __retry,
			     int *__status);
long  __ATOMIC_AND_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_AND_QUAD_RETRY(volatile void *__address,
			      long __expression,
			      int __retry,
			      int *__status);

int  __ATOMIC_OR_LONG(volatile void *__address, int __expression);
int  __ATOMIC_OR_LONG_RETRY(volatile void *__address,
			    int __expression,
			    int __retry,
			    int *__status);
long  __ATOMIC_OR_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_OR_QUAD_RETRY(volatile void *__address,
			     long __expression,
			     int __retry,
			     int *__status);

/*
**  Slightly faster than __ATOMIC_ADD using explicit +1 or -1.
*/
int  __ATOMIC_INCREMENT_LONG(volatile void *__address);
long  __ATOMIC_INCREMENT_QUAD(volatile void *__address);

int  __ATOMIC_DECREMENT_LONG(volatile void *__address);
long  __ATOMIC_DECREMENT_QUAD(volatile void *__address);

/*
**  Atomic replacement of location's contents, returning previous
**  contents.
*/
int  __ATOMIC_EXCH_LONG(volatile void *__address, int __expression);
int  __ATOMIC_EXCH_LONG_RETRY(volatile void *__address,
			      int __expression,
			      int __retry,
			      int *__status);
long  __ATOMIC_EXCH_QUAD(volatile void *__address, long __expression);
long  __ATOMIC_EXCH_QUAD_RETRY(volatile void *__address,
			       long __expression,
			       int __retry,
			       int *__status);

/*
**  Interlocked "test for bit clear and then clear".  Returns non-zero
**  if bit was already clear.
*/
int __INTERLOCKED_TESTBITCC_QUAD(volatile void *__address, int __bit_position);
int __INTERLOCKED_TESTBITCC_QUAD_RETRY(volatile void *__address,
				       int __bit_position,
				       int __retry,
				       int *__status);
/*
**  Interlocked "test for bit set and then set".  Returns non-zero
**  if bit was already set.
*/
int __INTERLOCKED_TESTBITSS_QUAD(volatile void *__address, int __bit_position);
int __INTERLOCKED_TESTBITSS_QUAD_RETRY(volatile void *__address,
				       int __bit_position,
				       int __retry,
				       int *__status);

/*
**  Acquire/release binary spinlock based on low-order bit of a longword.
**  NOTE: Memory barrier generated after lock, before unlock.
**  _RETRY variant returns non-zero on success within retry attempts.
*/
void __LOCK_LONG(volatile void *__address);
int  __LOCK_LONG_RETRY(volatile void *__address, int __retry);
void __UNLOCK_LONG(volatile void *__address);

/*
**  Acquire/release counted semaphore based on positive value of
**  longword indicating number of resources available.
**  NOTE: Memory barrier generated after acquisition, before release.
**  _RETRY variant returns non-zero on success within retry attempts.
*/
void __ACQUIRE_SEM_LONG(volatile void *__address);
int  __ACQUIRE_SEM_LONG_RETRY(volatile void *__address, int __retry);
void __RELEASE_SEM_LONG(volatile void *__address);

/*
**  Compare, Store Longword/Quadword
**      If *source matches old_value, store new_value in *dest, returning
**      0 if no match or if compare and store were not interlocked.
**      NOTE: Memory Barrier only within the LDx_L/STx_C sequence.
*/
int __CMP_STORE_LONG(volatile void *__source,
		     int __old_value,
		     int __new_value,
		     volatile void *__dest);
int __CMP_STORE_QUAD(volatile void *__source,
		     signed long __old_value,
		     signed long __new_value,
		     volatile void  *__dest);

/*
**  Add Aligned Word Interlocked (emulates the VAX instruction).
**      As on VAX, returns NZVC (0:3) of a VAX PSL.
**      Memory Barrier before and after update.
*/
int __ADAWI(short __src, volatile short *__dest);

#if !defined(__cplusplus) || \
    (defined(__DECCXX_VER) && __DECCXX_VER >= 60000000)
/************************************************************
**  Part 1a: DEC C/C++ builtins for bit counting
*************************************************************
**
**  These functions are not trivially implementable as asms
**  and need to be be highly optimized for certain kinds
**  of applications.  The names are compatible with some other
**  compiler implementations.
**
**  _popcnt, _poppar, _leadz, _trailz, _int_mult_upper
*/

long _popcnt(unsigned long);
long _poppar(unsigned long);
long _leadz(unsigned long);
long _trailz(unsigned long);
#pragma intrinsic(_popcnt, _poppar, _leadz, _trailz)
#define _int_mult_upper __UMULH
#endif  /* __cplusplus */



/******************************************************************
**  Part 2: "old" DEC C builtins for atomic/interlocked operations.
*******************************************************************
**
**  The following atomic/interlocked builtins have some usability issues,
**  but are retained as-is for compatibility with previous versions
**  of DEC C.  In particular, these _ATOMIC_ builtins always return
**  status (even when the retry count is omitted), but they have no
**  way to provide the old value, which is often useful.  The TESTBIT
**  routines return a value that indicates the previous state of
**  the bit, but they provide no way to determine success of the
**  operation if a retry count is specified.  They also generate
**  Memory Barrier instructions both before and after the atomic
**  update code, which tends to make them slower than necessary in
**  some cases.
*/
/*
**  op_ATOMIC_size Builtins
**
**  Note: There is one optional retry count parameter
*/
int __ADD_ATOMIC_LONG(volatile void *__address, int __expression, ...);
int __ADD_ATOMIC_QUAD(volatile void *__address, int __expression, ...);

int __AND_ATOMIC_LONG(volatile void *__address, int __expression, ...);
int __AND_ATOMIC_QUAD(volatile void *__address, int __expression, ...);

int __OR_ATOMIC_LONG(volatile void *__address, int __expression, ...);
int __OR_ATOMIC_QUAD(volatile void *__address, int __expression, ...);

/*
**  TESTBITxxI
**
**  Note: There is one optional retry count parameter
*/
int __TESTBITCCI(volatile void *__address, int __position, ...);
int __TESTBITSSI(volatile void *__address, int __position, ...);



/******************************************************************
**  Part 3: OpenVMS compatibility
*******************************************************************
**
**  These builtins are provided here largely to improve portability
**  of "older" source code from OpenVMS to Digital UNIX.  The more
**  usual UNIX convention for most of these builtins is to use inline
**  assembly code, which is now also available on OpenVMS Alpha (with
**  DEC C V5.0 or later).
*/

/*
**  Memory Barrier
*/
void	__MB(void);

/*
**  Instruction Memory Barrier
*/
void	__PAL_IMB(void);

/*
**  Trap Barrier Instruction
*/
void __TRAPB(void);

/*
**  Read Process Cycle Counter
*/
unsigned long __RPCC(void);

/*
**  Generate Trap
*/
void __PAL_GENTRAP(unsigned long __encoded_software_trap);

/*
**  Breakpoint
*/
void __PAL_BPT(void);

/*
**  Bugcheck
*/
void __PAL_BUGCHK(unsigned long __bugchk_code);

/*
**  Swap Privileged Context (Privileged)
*/
void __PAL_SWPCTX(void *__address);

/*
**  Halt the Processor. (Privileged)
*/
void __PAL_HALT(void);

/*
**  UMULH Builtin - Unsigned Quadword Multiply High
*/
unsigned long __UMULH(unsigned long __oper1,
			 unsigned long __oper2);


/*
**  The following floating point operations map to single
**  Alpha instructions (some with qualifiers), and can
**  also be specified by inline assembly code.
/*
**  Copy Sign
*/
float	    __CPYSF(float __operand1, float __operand2);
double	    __CPYS(double __operand1, double __operand2);

/*
**  Copy Sign Negate
*/
float	    __CPYSNF(float __operand1, float __operand2);
double	    __CPYSN(double __operand1, double __operand2);

/*
**  Copy Sign Exponent
*/
float	    __CPYSEF(float __operand1, float __operand2);
double	    __CPYSE(double __operand1, double __operand2);

/*
**  Convert from T-Floating to Quadword
*/
signed long __CVTTQ(double __operand1);

/*
**  Convert from T-Floating to S-Floating Chopped
*/
float __CVTTS_C(double __operand1);

/*
**  Add Floating Point Chopped
*/
float __ADDS_C(float __operand1, float __operand2);
double __ADDT_C(double __operand1, double __operand2);

/*
**  Subtract Floating Point Chopped
*/
float __SUBS_C(float __operand1, float __operand2);
double __SUBT_C(double __operand1, double __operand2);

/*
**  Multiply Floating Point Chopped
*/
float __MULS_C(float __operand1, float __operand2);
double __MULT_C(double __operand1, double __operand2);

/*
**  Divide Floating Point Chopped
*/
float __DIVS_C(float __operand1, float __operand2);
double __DIVT_C(double __operand1, double __operand2);

/*
**  __ALLOCA builtin - allocate n-bytes from the stack
**
**  This cannot be implemented using inline assembly code.  But
**  on Digital UNIX, code would typically #include <alloca.h>
**  and then use alloca() rather than including this header
**  file and using __ALLOCA().  The DEC C compiler treats both
**  styles equivalently, however.
*/
void *__ALLOCA(unsigned int __x);


#pragma __standard

#ifdef __cplusplus
}
#endif

#endif	/* __DECC || __DECCXX */
#endif  /* __BUILTINS_LOADED */
