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
 *	Alpha FP definitions
 */

#ifndef __ALPHA_FP_H__
#define __ALPHA_FP_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#ifdef __alpha
#if defined(__LANGUAGE_C__) || defined(__LANGUAGE_ASSEMBLER__) || defined(__cplusplus)

#define IEEE_PLUS_SIGN		0
#define IEEE_MINUS_SIGN		1


/* ALPHA constants for exceptional values */
#define IEEE_CANONICAL_QUIET_NAN	0xfff8000000000000UL
#define IEEE_PLUS_QUIET_NAN		0x7fffffffffffffffUL
#define IEEE_MINUS_QUIET_NAN		0xffffffffffffffffUL
#define IEEE_PLUS_SIGNALING_NAN		0x7ff7ffffffffffffUL
#define IEEE_MINUS_SIGNALING_NAN	0xfff7ffffffffffffUL
#define IEEE_PLUS_INFINITY		0x7ff0000000000000UL
#define IEEE_MINUS_INFINITY		0xfff0000000000000UL
#define IEEE_PLUS_LARGEST_NUMBER	0x7fefffffffffffffUL
#define IEEE_MINUS_LARGEST_NUMBER	0xffefffffffffffffUL
#define IEEE_PLUS_ZERO			0x0000000000000000UL
#define IEEE_MINUS_ZERO			0x8000000000000000UL
#define IEEE_PLUS_TWO			0x4000000000000000UL

/* ALPHA constants for integer values in fp registers */
#define IEEE_PLUS_LARGEST_QUAD_INTEGER	0x7fffffffffffffffUL
#define IEEE_MINUS_LARGEST_QUAD_INTEGER	0x8000000000000000UL
#define IEEE_PLUS_LARGEST_LONG_INTEGER	0x47ffffffe0000000UL
#define IEEE_MINUS_LARGEST_LONG_INTEGER	0x8000000000000000UL

#define IEEE_ZERO_EXPONENT		0
#define IEEE_ZERO_FRACTION		0
#define IEEE_DENORM_EXPONENT		0
#define IEEE_NAN_EXPONENT		0x7ff
#define IEEE_QUIET_NAN_MASK		0x0008000000000000UL

#define IEEE_FP_TRUE			IEEE_PLUS_TWO
#define IEEE_FP_FALSE			IEEE_PLUS_ZERO
#define IEEE_SIGN_BIT_MASK		(1UL<<63)

/* S format constants */
#define IEEE_S_FRACTION_SIZE		23
#define IEEE_S_EXPONENT_BIAS		127
#define IEEE_S_EXPONENT_MAX		254
#define IEEE_S_EXPONENT_SHIFT		3	/* in reg to make like t */

/* T format constants */
#define IEEE_T_FRACTION_SIZE		52
#define IEEE_T_EXPONENT_BIAS		1023
#define IEEE_T_EXPONENT_MAX		2046
#define IEEE_T_FRACTION_HIGH_BIT	(1UL<<51)
#define IEEE_T_EXPONENT_SHIFT		0

/* F format constants */
#define VAX_F_FRACTION_SIZE		23
#define VAX_F_EXPONENT_BIAS		127

/* G format constants */
#define VAX_G_FRACTION_SIZE		52
#define VAX_G_EXPONENT_BIAS		1023

/* D format constants */
#define VAX_D_FRACTION_SIZE		55
#define VAX_D_EXPONENT_BIAS	 	127


/* Constants for fpcr bits in fc_struct.fc_word */
#define FPCR_DNOD	(1UL << 47)	/* denormal operand exception disable */
#define FPCR_DNZ	(1UL << 48)	/* denormal operands to zero (EV6) */
#define FPCR_INVD	(1UL << 49)	/* invalid operation disable (EV6) */
#define FPCR_DZED	(1UL << 50)	/* division by zero disable (EV6) */
#define FPCR_OVFD	(1UL << 51)	/* overflow disable (EV6) */
#define FPCR_INV	(1UL << 52)	/* invalid operation */
#define FPCR_DZE	(1UL << 53)	/* division by zero */
#define FPCR_OVF	(1UL << 54)	/* overflow */
#define FPCR_UNF	(1UL << 55)	/* undeflow */
#define FPCR_INE	(1UL << 56)	/* inexact result */
#define FPCR_IOV	(1UL << 57)	/* integer overflow */
/* Note that bits		58 and
				59 are for dynamic rounding; see below. */
#define FPCR_UNDZ	(1UL << 60)	/* underflow to zero (EV5) */
#define FPCR_UNFD	(1UL << 61)	/* underflow disable (EV5) */
#define FPCR_INED	(1UL << 62)	/* inexact disable (EV45) */
#define FPCR_SUM	(1UL << 63)	/* summary bit */

/* Constants for dyn_rm field of the fpcr */
#define FE_TOWARDZERO	0	/* chopped */
#define FE_DOWNWARD	1	/* minus infinity */
#define FE_TONEAREST	2	/* normal */
#define FE_UPWARD	3	/* plus infinity */

/* Dynamic rounding bit defns for bits 58-59 of fc_struct.fc_word */
#define FPCR_DYN_SHIFT    58				/* bit position of dyn_rm */
#define FPCR_DYN_MASK    (3UL << FPCR_DYN_SHIFT)	/* dynamic rounding mode mask */
#define FPCR_DYN_CHOPPED ((unsigned long)FE_TOWARDZERO << FPCR_DYN_SHIFT)
#define FPCR_DYN_MINUS   ((unsigned long)FE_DOWNWARD   << FPCR_DYN_SHIFT)
#define FPCR_DYN_NORMAL  ((unsigned long)FE_TONEAREST  << FPCR_DYN_SHIFT)
#define FPCR_DYN_PLUS    ((unsigned long)FE_UPWARD     << FPCR_DYN_SHIFT)

/* ieee dynamic rounding mode field value names */
#define IEEE_ROUND_CHOPPED		FE_TOWARDZERO
#define IEEE_ROUND_TO_ZERO		FE_TOWARDZERO	/* ieee name */
#define	IEEE_ROUND_TO_MINUS_INFINITY	FE_DOWNWARD
#define IEEE_ROUND_NORMAL		FE_TONEAREST
#define IEEE_ROUND_TO_NEAREST		FE_TONEAREST	/* ieee name */
#define IEEE_ROUND_TO_PLUS_INFINITY	FE_UPWARD


/* exception summary bits */
#define	EXCSUM_SWC	0x01
#define	EXCSUM_INV	0x02
#define	EXCSUM_DZE	0x04
#define	EXCSUM_OVF	0x08
#define	EXCSUM_UNF	0x10
#define	EXCSUM_INE	0x20
#define	EXCSUM_IOV	0x40
#define EXCSUM_MASK	0x7e


/*
 *	We implement the IEEE trap enables with a software register
 *	mask. The mask is 64 bits wide.
 */

/* Trap enables */
#define IEEE_TRAP_ENABLE_INV	0x000002	/* invalid operation */
#define IEEE_TRAP_ENABLE_DZE	0x000004	/* divide by 0 */
#define IEEE_TRAP_ENABLE_OVF	0x000008	/* overflow */
#define IEEE_TRAP_ENABLE_UNF	0x000010	/* underflow */
#define IEEE_TRAP_ENABLE_INE	0x000020	/* inexact */
#define IEEE_TRAP_ENABLE_DNO	0x000040	/* denormal operand exception enable */
#define IEEE_TRAP_ENABLE_MASK	0x00007e	/* if set, we handle */

/* Denorm and Underflow flushing */
#define IEEE_MAP_DMZ		0x001000	/* denormal inputs map to zero */
#define IEEE_MAP_UMZ		0x002000	/* underflow results map to zero */

/* Status flags */
#define IEEE_STATUS_INV		0x020000	/* invalid operation */
#define IEEE_STATUS_DZE		0x040000	/* divide by 0 */
#define IEEE_STATUS_OVF		0x080000	/* overflow */
#define IEEE_STATUS_UNF		0x100000	/* underflow */
#define IEEE_STATUS_INE		0x200000	/* inexact */
#define IEEE_STATUS_DNO		0x400000	/* denormal operand */
#define IEEE_STATUS_MASK	0x7e0000	/* mask of all sticky bits */

#define IEEE_STATUS_TO_EXCSUM_SHIFT	16	/* shift to line up with EXCSUM */
#define IEEE_STATUS_TO_FPCR_SHIFT	35	/* shift to line up with FPCR */

#define IEEE_INHERIT	0x8000000000000000	/* on fork or thread create */



#if defined(__LANGUAGE_C__) || defined(__cplusplus)

typedef unsigned long	_fp_ulong_64;	/* identify large fields */

/* Strict ANSI requires that bitfields be int or unsigned int.  Use of */
/* unsigned long is considered a common extension and useful in this case. */
/* Disable the warnings for libc compiles. */

#ifdef _LIBC_POLLUTION_H_
#pragma message disable bitnotint /* to avoid warning for libc */
#endif

/* in register formats for alpha floating point types */

typedef struct fp_s_register {
	_fp_ulong_64		mbz:29;		/* must be zero */
	unsigned long		fraction:23;
	unsigned long		exponent:11;
	unsigned long		sign:1;
} fp_s_register_t;				/* ieee single precision */

typedef struct fp_f_register {
	_fp_ulong_64		mbz:29;		/* must be zero */
	unsigned long		fraction:23;
	unsigned long		exponent:11;
	unsigned long		sign:1;
} fp_f_register_t;				/* vax single precision */

typedef struct fp_t_register {
	_fp_ulong_64		fraction:52;
	unsigned long		exponent:11;
	unsigned long		sign:1;
} fp_t_register_t;				/* ieee double precision */

typedef struct fp_g_register {
	_fp_ulong_64		fraction:52;
	unsigned long		exponent:11;
	unsigned long		sign:1;
} fp_g_register_t;				/* vax double precision */

typedef struct fp_d_register {
	_fp_ulong_64		fraction:55;
	unsigned long		exponent:8;
	unsigned long		sign:1;
} fp_d_register_t;				/* vax double precision */

typedef struct fp_l_register {
	_fp_ulong_64		mbz:29;
	unsigned long		low_bits:30;
	unsigned long		ignored:3;
	unsigned long		hi_bit:1;
	unsigned long		sign:1;
} fp_l_register_t;				/* longword format */

typedef struct fp_q_register {
	_fp_ulong_64		bits:63;
	unsigned long		sign:1;
} fp_q_register_t;				/* quadword format */

typedef union fp_register {
	_fp_ulong_64		qval;		/* quad to access */
	double			dval;		/* double to print */
	fp_s_register_t		s;		/* ieee single precision */
	fp_t_register_t		t;		/* ieee double precision */
	fp_f_register_t		f;		/* vax single precision */
	fp_g_register_t		g;		/* vax double precision */
	fp_d_register_t		d;		/* vax double precision */
	fp_l_register_t		l;		/* longword format */
	fp_l_register_t		q;		/* quadword format */
} fp_register_t;


/*
 * Structure definitions for the hardware floating-point 
 * control and status register (fpcr).
 */
typedef union fpcr {
	_fp_ulong_64	 qval;
	struct {
		_fp_ulong_64 res_0 : 47;	/* reserved */
		unsigned long dnod :  1;
		unsigned long dnz  :  1;
		unsigned long invd :  1;
		unsigned long dzed :  1;
		unsigned long ovfd :  1;
		unsigned long inv  :  1;
		unsigned long dze  :  1;
		unsigned long ovf  :  1;
		unsigned long unf  :  1;
		unsigned long ine  :  1;
		unsigned long iov  :  1;
		unsigned long dyn  :  2;	/* 2 bits for 4 modes */
		unsigned long undz :  1;
		unsigned long unfd :  1;
		unsigned long ined :  1;
		unsigned long sum  :  1;
	} fields;
} fpcr_t;


/* Exception Summary register */
typedef union excsum {
	_fp_ulong_64	qval;
	struct {
		/* cumulative exception bits representing exceptions in trap shadow */
		unsigned long swc  :  1;
		unsigned long inv  :  1;
		unsigned long dze  :  1;
		unsigned long ovf  :  1;
		unsigned long unf  :  1;
		unsigned long ine  :  1;
		unsigned long iov  :  1;
		_fp_ulong_64 res_7 : 57;		/* reserved; must be zero */
	} fields;
} excsum_t;


/* Software maintained fp_control quadword */
typedef union ieee_fp_control {
	_fp_ulong_64		qval;
	struct {

		unsigned long res_imp_0   :  1;		/* reserved */

		/* Enables: */
		unsigned long enable_inv  :  1;
		unsigned long enable_dze  :  1;
		unsigned long enable_ovf  :  1;
		unsigned long enable_unf  :  1;
		unsigned long enable_ine  :  1;
		unsigned long enable_dno  :  1;

		unsigned long res_arch_7  :  5;		/* reserved */

		/* Denorm and underflow controls: */
		unsigned long
		  map_denorms_to_zero     :  1;
		unsigned long
		  map_underflows_to_zero  :  1;

		unsigned long res_imp_14  :  3;		/* reserved */

		/* Status Bits: match fpcr and excsum except for dno versus iov */
		unsigned long inv         :  1;
		unsigned long dze         :  1;
		unsigned long ovf         :  1;
		unsigned long unf         :  1;
		unsigned long ine         :  1;
		unsigned long dno         :  1;		/* ... DNO placement precludes FPCR order */

		unsigned long res_arch_23 : 25;		/* reserved */
		unsigned long res_imp_48  : 15;		/* reserved */

		unsigned long inherit     :  1;		/* on fork or thread create */

	} fields;
} ieee_fp_control_t;




#ifdef _LIBC_POLLUTION_H_
#pragma message enable bitnotint  /* to reset warning */
#endif


extern int fegetround __((void));
extern int fesetround __((int));

/*
 * These functions are used to get and set the floating point control
 * register (fpcr)
 */
extern unsigned long _get_fpcr __((void));
extern unsigned long _set_fpcr __((unsigned long));

/* backward compatability macros */
#define fc_word		qval
#define fc_struct	fields
#define dyn_rm		dyn
#define FPCR_DYN_RM_MASK	FPCR_DYN_MASK
#define FPCR_DYN_RM_SHIFT	FPCR_DYN_SHIFT
#define FPCR_DYN_RM_CHOPPED	FPCR_DYN_CHOPPED
#define FPCR_DYN_RM_MINUS	FPCR_DYN_MINUS
#define FPCR_DYN_RM_NORMAL	FPCR_DYN_NORMAL
#define FPCR_DYN_RM_PLUS	FPCR_DYN_PLUS

/* prototypes for ieee user callable functions */
#ifndef _KERNEL
extern void	ieee_ignore_state_at_signal(void);
extern long	ieee_get_fp_control(void);
extern void	ieee_set_fp_control(long);
extern void	ieee_set_state_at_signal(unsigned long, unsigned long);
extern int	ieee_get_state_at_signal(unsigned long *, unsigned long *);
#endif /* _KERNEL */

#endif /* __LANGUAGE_C__ || __cplusplus */
#endif /* __LANGUAGE_C__ || __LANGUAGE_ASSEMBLER__ || __cplusplus */
#endif /* __alpha */

#ifdef __cplusplus
}
#endif
#endif /* __ALPHA_FP_H__ */

