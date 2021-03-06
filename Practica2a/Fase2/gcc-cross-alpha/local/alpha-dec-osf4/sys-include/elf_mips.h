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
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
/* $Header: /usr/sde/osf1/rcs/os/src/usr/include/alpha/elf_mips.h,v 1.1.18.2 1997/02/04 22:30:40 Randy_Lowell Exp $ */

#ifndef _ELF_MIPS_H_
#define _ELF_MIPS_H_

#include <elf_abi.h>

#if defined(__LANGUAGE_C__) || defined(__LANGUAGE_ASSEMBLY__) || defined(__cplusplus)
                /* no pascal support yet- */
/* 
 * Random constants
 */

#define _TEXT_ALIGN 0x1000
#define _DATA_ALIGN 0x10000

/*
 * e_flags
 */
#define EF_MIPS_NOREORDER   0x00000001
#define EF_MIPS_PIC     0x00000002
#define EF_MIPS_CPIC        0x00000004
#define EF_MIPS_UGEN_ALLOC  0x00000008
#define EF_MIPS_UGEN_RESERVED   0x00000010 /* reserved for future use */
#define EF_MIPS_ARCH        0xf0000000u
#define EF_MIPS_ARCH_2          0x10000000
#define EF_MIPS_ARCH_3          0x20000000

/* 
 * special Program header types
 */
#define PT_MIPS_REGINFO (PT_LOPROC + 0)

/* 
 * Special mips section indices
 */
#define SHN_MIPS_ACOMMON    (SHN_LOPROC + 0)
#define SHN_MIPS_TEXT       (SHN_LOPROC + 1)
#define SHN_MIPS_DATA       (SHN_LOPROC + 2)


/*
 * sh_type
 */
#define SHT_MIPS_LIBLIST    (SHT_LOPROC + 0)
#define SHT_MIPS_MSYM       (SHT_LOPROC + 1)
#define SHT_MIPS_CONFLICT   (SHT_LOPROC + 2)
#define SHT_MIPS_GPTAB      (SHT_LOPROC + 3)
#define SHT_MIPS_UCODE      (SHT_LOPROC + 4)
#define SHT_MIPS_DEBUG          (SHT_LOPROC + 5)
#define SHT_MIPS_REGINFO        (SHT_LOPROC + 6)



/*
 * sh_flags
 */
#define SHF_MIPS_GPREL  0x10000000

/*
 * special section names
 */
#define MIPS_SDATA  ".sdata"
#define MIPS_REL_SDATA  ".rel.sdata"
#define MIPS_SBSS   ".sbss"
#define MIPS_LIT4   ".lit4"
#define MIPS_LIT8   ".lit8"
#define MIPS_REGINFO    ".reginfo"
#define MIPS_LIBLIST    ".liblist"
#define MIPS_MSYM   ".msym"
#define MIPS_RHEADER    ".rheader"
#define MIPS_CONFLICT   ".conflict"
#define MIPS_GPTAB_SDATA    ".gptab.sdata"
#define MIPS_GPTAB_DATA ".gptab.data"
#define MIPS_GPTAB_BSS  ".gptab.bss"
#define MIPS_GPTAB_SBSS ".gptab.sbss"
#define MIPS_UCODE  ".ucode"
#define MIPS_MDEBUG ".mdebug"

/*
 * ".gptab" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef union
{
    struct
    {
        Elf32_Word  gt_current_g_value;
        Elf32_Word  gt_unused;
    } gt_header;
    struct
    {
        Elf32_Word  gt_g_value;
        Elf32_Word  gt_bytes;
    } gt_entry;
} Elf32_Gptab;

/*
 * ".reginfo" section
 */
typedef struct
{
    Elf32_Word  ri_gprmask;
    Elf32_Word  ri_fprmask;
    Elf32_Sword ri_gp_value;
} Elf32_RegInfo;
#endif
/*
 * r_info
 */
/*
 * relocation types
 */
#define R_MIPS_NONE 0
#define R_MIPS_32   1
#define R_MIPS_64   2
#define R_MIPS_GPREL32  3
#define R_MIPS_LITERAL  4
#define R_MIPS_LITUSE   5
#define R_MIPS_GPDISP   6
#define R_MIPS_BRADDR   7
#define R_MIPS_HINT 8

/*
 * ".liblist" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
    Elf32_Word  l_name;
    Elf32_Word  l_time_stamp;
    Elf32_Word  l_checksum;
    Elf32_Word  l_version;
    Elf32_Word  l_flags;
} Elf32_Lib;
#endif

/*
 * l_flags
 */
#define LL_NONE         0
#define LL_EXACT_MATCH      0x1
#define LL_IGNORE_INT_VER   0x2
#define LL_USE_SO_SUFFIX    0x4
#define LL_NO_LOAD	    0x8

/*
 * ".msym" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
    Elf32_Word  ms_hash_value;
    Elf32_Word  ms_info;
} Elf32_Msym;
#endif
/*
 * ms_info
 */
#define ELF32_MS_REL_INDEX(i)   ((i) >> 8)
#define ELF32_MS_FLAGS(i)   ((i) & 0xff)
#define ELF32_MS_INFO(r,f)  (((r) << 8) + ((f) & 0xff))

/*
 * ".conflict" section
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
typedef struct
{
    Elf32_Word  c_index;
} Elf32_Conflict;

extern Elf32_Conflict   _ConflictList [];

#define RLD_VERSION         3   /* Current shared object version 
                                 * produced by LD.  
                                 */
#define RLD_VERSION_2       2   /* LD shared object version prior to
                                 * GOT optimizations.
                                 */
#define RLD_VERSION_ONE_GOT 1   /* LD shared object version prior to
                                 * multi-GOT support.
                                 */

/*
 * ".got" section
 */
typedef struct
{
    Elf32_Addr  g_index;
} Elf32_Got;

extern Elf32_Got    _GlobalOffsetTable [];
#endif

#define MS_ALIAS        0x1

#define DT_MIPS_RLD_VERSION     0x70000001
#define DT_MIPS_TIME_STAMP      0x70000002
#define DT_MIPS_ICHECKSUM       0x70000003
#define DT_MIPS_IVERSION        0x70000004
#define DT_MIPS_FLAGS           0x70000005
#define DT_MIPS_BASE_ADDRESS    0x70000006
#define DT_MIPS_MSYM            0x70000007
#define DT_MIPS_CONFLICT        0x70000008
#define DT_MIPS_LIBLIST         0x70000009
#define DT_MIPS_LOCAL_GOTNO     0x7000000A
#define DT_MIPS_CONFLICTNO      0x7000000B
#define DT_MIPS_LIBLISTNO       0x70000010
#define DT_MIPS_SYMTABNO        0x70000011
#define DT_MIPS_UNREFEXTNO      0x70000012
#define DT_MIPS_GOTSYM          0x70000013
#define DT_MIPS_HIPAGENO        0x70000014
/* 0x70000015 is skipped */
#define DT_MIPS_RLD_MAP         0x70000016
#define DT_MIPS_SO_SUFFIX	0x70000017


#define RHF_NONE                    0x00000000
#define RHF_QUICKSTART              0x00000001
#define RHF_NOTPOT                  0x00000002
#define RHF_NO_LIBRARY_REPLACEMENT  0x00000004
#define RHF_NO_MOVE                 0x00000008
#define RHF_TLS			    0x04000000
#define RHF_BIND_NOW                0x08000000
#define RHF_RING_SEARCH             0x10000000
#define RHF_DEPTH_FIRST             0x20000000
#define RHF_USE_31BIT_ADDRESSES     0x40000000
#define RHF_RESERVED_SIGN_BIT       0x80000000

#endif              /* __LANGUAGE_C__ || __LANGUAGE_ASSEMBLY__ */
#endif              /* _ELF_MIPS_H_ */
