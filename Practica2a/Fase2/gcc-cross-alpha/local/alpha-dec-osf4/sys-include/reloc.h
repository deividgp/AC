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
/* $Header: /usr/sde/osf1/rcs/os/src/usr/include/alpha/reloc.h,v 1.2.16.3 1997/02/14 19:50:31 Randy_Lowell Exp $ */
#ifndef _RELOC_H
#define _RELOC_H

/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct reloc {
    long	r_vaddr;	/* (virtual) address of reference */
    unsigned	r_symndx;	/* index into symbol table */
    unsigned	r_type 	: 8;	/* relocation type */
    unsigned	r_extern: 1;	/* if 1 symndx is an index into */
				/* the external symbol table, else */
				/* symndx is a section # */
    unsigned	r_offset:6;	/* for R_OP_STORE, quad based LE bit offset */
    unsigned	r_reserved:11;	/* Must be zero */
    unsigned	r_size:6;	/* R_OP_STORE, bit size */
    };
#endif /* __LANGUAGE_C__ || __cplusplus */

#ifdef __LANGUAGE_PASCAL__
type
  reloc = packed record
      r_vaddr : integer64;		/* (virtual) address of reference    */
      r_symndx : integer;		/* index into symbol table	     */
      r_type : 0..255;			/* relocation type		     */
      r_extern : 0..1;			/* if 1, symndx is an index into the */
					/* external symbol table, else	     */
					/* symndx is a section		   # */
      r_offset : 0..63;			/* for R_OP_STORE, quad based LE bit offset */
      r_reserved : 0..lshift(1, 11)-1;
      r_size : 0..63;			/* R_OP_STORE, bit size */
      end {record};
#endif /* __LANGUAGE_PASCAL__ */

/*
 * Section numbers for symndx for local relocation entries (r_extern == 0).
 * For these entries the starting address for the section referenced by the
 * section number is used in place of an external symbol table entry's value.
 */
#define	R_SN_NULL	0
#define	R_SN_TEXT	1
#define	R_SN_RDATA	2
#define	R_SN_DATA	3
#define	R_SN_SDATA	4
#define	R_SN_SBSS	5
#define	R_SN_BSS	6
#define	R_SN_INIT	7
#define	R_SN_LIT8	8
#define	R_SN_LIT4	9
#define	R_SN_XDATA	10
#define	R_SN_PDATA	11
#define R_SN_FINI	12
#define	R_SN_LITA	13
#define R_SN_ABS	14		/* constant relocation r_vaddr's */
#define R_SN_RCONST	15
#define R_SN_TLSDATA	16
#define R_SN_TLSBSS	17
#define R_SN_TLSINIT	18
#define MAX_R_SN	18

/*
 *   relocation types for all products and generics
 */

/*
 * All generics
 *	reloc. already performed to symbol in the same section
 */
#define  R_ABS		0

/*
 * ALPHA machines
 *
 *	32-bit reference
 *	64-bit reference
 *	32-bit displacement from gp
 *	reference to global pointer relative literal pool item
 *	identifies useage of a literal address previously loaded
 *	lda/ldah instruction pair to initialize gp.
 *	21-bit branch reference
 *	14-bit jsr hint reference
 */

#define R_REFLONG	1
#define R_REFQUAD	2
#define R_GPREL32	3
#define R_LITERAL	4
#define R_LITUSE	5
#define R_GPDISP	6
#define R_BRADDR	7
#define R_HINT		8

/*
 *	self relative relocations mean that the memory location at
 *	r_vaddr contains an offset to the destination. If the relocation
 *	is r_extern==1, then the value at the memory location is ignored
 *	(maybe we should allow offsets?). If r_extern==0, then the value
 *	at the memory location is the actual offset. 
 *
 *	The linker uses the relocated target and a relocated r_vaddr to
 *	determine the offset. Offsets are considered signed.
 */
#define R_SREL16	9		/* self relative 16 bit offset */
#define R_SREL32	10		/* self relative 32 bit offset */
#define R_SREL64	11		/* self relative 64 bit offset */
/* 
 *	stack relocations provide a primitive expression evaluator for
 *	relocatable and constant values at link time. It also provides
 *	a way to store a value into a bit field (the R_OP_STORE has a
 *	bit size and offset field (from a quadword aligned qaudword)).
 *
 *	The operations specify what they relocate and what happens to
 *	the linktime stack. It is an error to cause a stack underflow
 *	or have values left on the stack when the relocation for a section
 *	is complete.
 *
 *	terms:
 *		tos		top of stack
 *		stack		qaudword array representing the stack
 *		vaddr		address field in reloc record or 
 *					extern symbol address
 *		relocate(X)	relocate address X
 *		X(o:s)		address X, bitoffset o, bit size s
 *		r_offset	offset field in reloc record
 *		r_size		bitsize field in reloc record, 0 means 64 bits
 *
 *	Note: use R_SN_ABS as the section for constants (like in shifts).
 *		
 */
#define R_OP_PUSH	12	/* stack[++tos] = relocate(vaddr) */
#define R_OP_STORE	13	/* vaddr(r_offset:r_size) = stack[tos--] */
#define R_OP_PSUB	14	/* stack[tos] = stack[tos] - relocate(vaddr) */
#define R_OP_PRSHIFT	15	/* stack[tos] = stack[tos] >> relocate(vaddr) */

/*
 *	The GPVALUE relocation provides a mechanism to designate a range
 *	of section addresses to have a particular gp value.  This is not
 *	represented in the optional header when there are multiple gp
 *	ranges within an object file.
 *
 *	To compute the value of gp, add the r_symndx field to the value
 *	of gp in the optional header.  This gives the gp value used for
 *	the range from vaddr to the address pointed by the next GPVALUE
 *	field or object's last relocation record.
 *
 *	vaddr		points to the address where the gp range starts.
 *	symndx		the offset added to optional header's value.
 *	type		R_GPVALUE
 *	extern		0
 */

#define R_GPVALUE	16

#define R_GPRELHIGH	17	/* "ldah" displacement from gp */
#define R_GPRELLOW	18	/* "lda" displacement from gp */

/*
 *	The IMMED relocation identifies an address calculation embedded
 *	within a sequence of instructions.  This relocation can describe
 *	instruction sequences that calculate addresses by adding either
 *	a 16-bit or 32-bit immediate displacement to a base address.
 *	The r_size field holds a sub-opcode that identifies different
 *	types of address calculations.
 *
 *	R_IMMED_GP_16   	The identified instruction adds a 16-bit
 *	                 	displacement to the GP value, obtaining an
 *	                 	address.  The r_extern and r_symndx fields
 *	                 	specify the external symbol or section to
 *	                 	which the calculated address is relative.
 *
 *	R_IMMED_GP_HI32 	The instruction is part of a pair of
 *	                	instructions that add a 32-bit displacement 
 *	                 	to the GP value.  This instruction adds
 *	                 	the high portion of the 32-bit displacement.
 *	                 	The next R_IMMED_LO32 identifies the
 *	                	instruction with the low portion of the
 *	                	displacement.  More than one subsequent
 *	                 	R_IMMED_LO32 may share the same
 *	                 	R_IMMED_GP_HI32.  The r_extern and r_symndx
 *	                	fields of this relocation are not used.
 *
 *	R_IMMED_SCN_HI32	The instruction is part of a pair that
 *	                 	add a 32-bit displacement to the starting
 *	                  	address of the current section.  This
 *	                  	instruction adds the high portion of the
 *	                  	displacement.  The next R_IMMED_LO32
 *	                 	identifies the instruction with the low
 *	                 	portion.  The r_extern and r_symndx
 *	                  	fields of this relocation are not used.
 *
 *	R_IMMED_BR_HI32  	The instruction is part of a pair that
 *	                	add a 32-bit displacement to the address
 *	                 	of the instruction following a branch
 *	                 	(br, bsr, jsr, or jmp).  The branch must
 *	                	preceed this instruction.  The r_symndx
 *	                	specifies a byte offset from r_vaddr to the 
 *	                	branch instruction.  This instruction
 *	                  	adds the high portion of the displacement.
 *	                  	The next R_IMMED_LO32 identifies the
 *	                 	instruction with the low portion.  The
 *	                 	r_extern field is not used.
 *
 *	R_IMMED_LO32     	The instruction is part of a pair that add
 *	                 	a 32-bit displacement to a base address.
 *	                 	This instruction adds the low portion of
 *	                	the displacement.  This relocation pairs
 *	                	with the previous R_IMMED_GP_HI32,
 *	                	R_IMMED_SCN_HI32, or R_IMMED_BR_HI32.
 *	                 	The r_extern and r_symndx fields specify
 *	                 	the external symbol or section to which the
 *	                   	calculated address is relative.
 */

#define R_IMMED  	19

/*
 * Relocations for Thread Local Storage access instructions.
 */

#define R_TLS_LITERAL	20
#define R_TLS_HIGH	21
#define R_TLS_LOW	22

#define MAX_R_TYPE	23

/*
 * Literal usage types for R_LITUSE
 *
 *	literal address in register of a memory format instruction
 *	literal address in byte offset register of byte-manipulation instruction
 *	literal address is in target register of a jsr instruction.
 */

#define R_LU_BASE	1
#define R_LU_BYTOFF	2
#define R_LU_JSR	3

/*
 * Sub-opcodes for R_IMMED
 *
 *	16-bit displacement from GP value
 *	high part of 32-bit displacement from GP value
 *	high part of 32-bit displacement from section start
 *	high part of 32-bit displacement from instruction following branch
 *	low part of 32-bit displacement specified by last R_IMMED_*_HI32
 */

#define R_IMMED_GP_16   	1
#define R_IMMED_GP_HI32 	2
#define R_IMMED_SCN_HI32	3
#define R_IMMED_BR_HI32 	4
#define R_IMMED_LO32    	5


#define	RELOC	struct reloc
#define	RELSZ	sizeof(RELOC)

/*
 * Thread Local Storage definitions
 */

#define TLS_PTR_BIAS 0x00000000UL
#define TLS_MAX_SIZE 0x7fff7ff0UL

#endif /* _RELOC_H */
