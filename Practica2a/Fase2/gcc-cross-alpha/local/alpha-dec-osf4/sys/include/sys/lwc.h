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
 * @(#)$RCSfile: lwc.h,v $ $Revision: 1.1.28.2 $ (DEC) $Date: 1999/01/11 18:45:23 $
 */
#ifndef	__LWC__
#define	__LWC__

#ifndef	ASSEMBLER

#ifndef	spllwc
#define	spllwc splextreme
#endif	/* !spllwc */

typedef vm_offset_t	lwc_id_t;
typedef int		lwc_pri_t;

struct lwc {
	void 		(*lwc_ctxt)();		/* Context */
};

typedef	struct lwc	*lwc_t;

#endif /* !ASSEMBLER */

#ifdef	KERNEL
#ifndef	ASSMEBLER

#define lwc_cpu_post(pri) 						\
MACRO_BEGIN								\
{									\
	int s;								\
	s = spllwc();							\
	current_pcb()->pcb_ast.flags.lwc_pending |= (1L << (pri));	\
	(void) splx(s);							\
}									\
MACRO_END

#define lwc_rt_set(ipl) 						\
MACRO_BEGIN								\
{									\
	current_pcb()->pcb_ast.flags.lwc_pending 			\
	    = (current_pcb()->pcb_ast.flags.lwc_pending & 0x00ffffff) 	\
			| (ipl << 24);					\
}									\
MACRO_END

#define	lwc_rt_pending() 						\
	(current_pcb()->pcb_ast.flags.lwc_pending  >> 24)

extern void 	lwc_create(/* int pri, void (*)() */);

#define LWC_PRI_MACH_FACTOR	0	
#define LWC_PRI_SOFTCLOCK	1
#define LWC_PRI_VFS_UBC		2
#define LWC_PRI_MSFS_UBC 	3
#define LWC_PRI_VM_SWAP		4 
#define LWC_PRI_RT		5	
#define LWC_PRI_PSIGNAL		6	
#define LWC_PRI_CALLOUT 	7	
#define LWC_PRI_SYSLOG 		8	
#define LWC_PRI_BINLOG 		9	
#define LWC_PRI_RDG 		10	

#endif	/* !ASSEMBLER */
#endif	/* KERNEL */

#ifdef _OSF_SOURCE
#define	LWC_PRI_MAX		16 	/* max lwc routines allowed */
#endif 

#endif /* !__LWC__ */
