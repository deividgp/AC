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
/* $Header: /share/buffer/build/rcs.dsk1/os/src/usr/include/alpha/scnhdr.h,v 1.2.15.2 1998/04/28 15:13:53 Randy_Lowell Exp $ */
#ifndef _SCNHDR_H
#define _SCNHDR_H

/*  Copyright (c) 1984 AT&T */
/*    All Rights Reserved   */

/*  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T */
/*  The copyright notice above does not evidence any    */
/*  actual or intended publication of such source code. */

/*
 * The entries that refer to line numbers are not used for line numbers.
 * See sym.h for the entries to get to the line number 
 * table.  The entries that were for line numbers are reserved and must
 * be set to zero.
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct scnhdr {
    char        s_name[8];  	/* section name */
    long        s_paddr;    	/* physical address, aliased s_nlib */
    long        s_vaddr;    	/* virtual address */
    long        s_size;     	/* section size */
    long        s_scnptr;   	/* file ptr to raw data for section */
    long        s_relptr;   	/* file ptr to relocation */
    long        s_lnnoptr;  	/* special purpose */
    unsigned short  s_nreloc;   /* number of relocation entries */
    unsigned short  s_nlnno;    /* unused */
    int     	s_flags;    	/* flags */
    };

#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
type
  scnhdr = packed record
      s_name : packed array[1..8] of char; /* section name */
      s_paddr : integer64;      /* physical address */
      s_vaddr : integer64;      /* virtual address */
      s_size : integer64;       /* section size */
      s_scnptr : integer64;     /* file ptr to raw data for section */
      s_relptr : integer64;     /* file ptr to relocation */
      s_lnnoptr : integer64;    /* special purpose */
      s_nreloc : ushort;        /* number of relocation entries */
      s_nlnno : ushort;         /* unused */
      s_flags : long;           /* flags */
    end {record};
#endif /* __LANGUAGE_PASCAL__ */

/* SCNROUND is the size that sections are rounded off to */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define SCNROUND 16

/* SCN_ALIGN access the six bits of s_nlnno used to hold the
 * power-of-two section alignment for a specific section.
 */

#define SCN_ALIGN(_s_nlnno) ((_s_nlnno) & 0x3F)

#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define SCNROUND (16)
#endif /* __LANGUAGE_PASCAL__ */

#define s_nlib  s_paddr
#define SCNHDR  struct scnhdr
#define SCNHSZ  sizeof(SCNHDR)




/*
 * Define constants for names of "special" sections
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define _TEXT   ".text"
#define _DATA   ".data"
#define _BSS    ".bss"
#define _INIT   ".init"
#define _FINI   ".fini"

/* of exception handling sections */
#define _XDATA ".xdata"
#define _PDATA ".pdata"

/* of TLS sections */
#define _TLSDATA ".tlsdata"
#define _TLSBSS  ".tlsbss"
#define _TLSINIT ".tlsinit"

/* of dso related sections */
#define _GOT      ".got"
#define _DYNAMIC  ".dynamic"
#define _DYNSYM   ".dynsym"
#define _REL_DYN  ".rel.dyn"
#define _DYNSTR   ".dynstr"
#define _HASH     ".hash"
#define _MSYM     ".msym"
#define _CONFLICT ".conflict"
#define _LIBLIST  ".liblist"

/* of sections not supported in Digital UNIX objects. */
#define _TV       ".tv"
#define _LIB      ".lib"
#define _DSOLIST  ".dsolist"
#define _REGINFO  ".reginfo"

#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define _TEXT   ".text\0"
#define _DATA   ".data\0"
#define _BSS    ".bss\0"
#define _INIT   ".init\0"
#define _FINI   ".fini\0"

/* of exception handling sections */
#define _XDATA  ".xdata\0"
#define _PDATA  ".pdata\0"

/* of TLS sections */
#define _TLSDATA ".tlsdata\0"
#define _TLSBSS  ".tlsbss\0"
#define _TLSINIT ".tlsinit\0"

/* of dso related sections */
#define _GOT      ".got\0"
#define _DYNAMIC  ".dynamic\0"
#define _DYNSYM   ".dynsym\0"
#define _REL_DYN  ".rel.dyn\0"
#define _DYNSTR   ".dynstr\0"
#define _HASH     ".hash\0"
#define _MSYM     ".msym\0"
#define _CONFLICT ".conflict\0"
#define _LIBLIST  ".liblist\0"

/* of sections not supported in Digital UNIX objects. */
#define _TV       ".tv\0"
#define _LIB      ".lib\0"
#define _DSOLIST  ".dsolist\0"
#define _REGINFO  ".reginfo\0"

#endif /* __LANGUAGE_PASCAL__ */

/*
 * Names for read only data (.rdata), small data (.sdata) and small bss
 * (.bss).  Small sections are used for global pointer relative data items.
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define _RDATA  ".rdata"
#define _RCONST ".rconst"
#define _SDATA  ".sdata"
#define _SBSS   ".sbss"
#define _UCODE  ".ucode"
#define _LIT8   ".lit8"
#define _LIT4   ".lit4"
#define _LITA   ".lita"
#define _COMMENT ".comment"
#endif /* __LANGUAGE_C__ || __cplusplus */

#ifdef __LANGUAGE_PASCAL__
#define _RDATA  ".rdata\0"
#define _RCONST ".rconst\0"
#define _SDATA  ".sdata\0"
#define _SBSS   ".sbss\0"
#define _UCODE  ".ucode\0"
#define _LIT8   ".lit8\0"
#define _LIT4   ".lit4\0"
#define _LITA   ".lita\0"
#define _COMMENT ".comment\0"
#endif /* __LANGUAGE_PASCAL__ */


/*
 * The low 4 bits of s_flags is used as a section "type"
 */

#if defined(__LANGUAGE_C__) || defined(__cplusplus)
#define STYP_REG        0x00000000  /* "regular" section: allocated, relocated, loaded */
#define STYP_DSECT      0x00000001  /* "dummy" section: not allocated, relocated, not loaded */
#define STYP_NOLOAD     0x00000002  /* "noload" section: allocated, relocated, not loaded */
#define STYP_GROUP      0x00000004  /* "grouped" section: formed of input sections */
#define STYP_PAD        0x00000008  /* "padding" section: not allocated, not relocated, loaded */
#define STYP_COPY       0x00000010  /* "copy" section: for decision function used by field update;
                                       not allocated, not relocated, loaded;  reloc &
                                       lineno entries processed normally */
#define STYP_TEXT       0x00000020  /* section contains text only */
#define STYP_DATA       0x00000040  /* section contains data only */
#define STYP_BSS        0x00000080  /* section contains bss only */
#define STYP_RDATA      0x00000100  /* section contains read only data */
#define STYP_SDATA      0x00000200  /* section contains small data only */
#define STYP_SBSS       0x00000400  /* section contains small bss only */
#define STYP_UCODE      0x00000800  /* section only contains ucodes */

/* of dso related sections types */
#define STYP_GOT        0x00001000
#define STYP_DYNAMIC    0x00002000
#define STYP_DYNSYM     0x00004000
#define STYP_REL_DYN    0x00008000
#define STYP_DYNSTR     0x00010000
#define STYP_HASH       0x00020000
#define STYP_DSOLIST    0x00040000
#define STYP_RESERVED   0x00080000

#define STYP_CONFLICT   0x00100000          /* Overloaded: see STYP_MASK below */
#define STYP_REGINFO    0x00200000          /* Overloaded: see STYP_MASK below */
#define STYP_RESERVED2  0x00400000          /* Overloaded: see STYP_MASK below */
#define STYP_RESERVED3  0x00800000          /* Overloaded: see STYP_MASK below */

#define STYP_FINI       0x01000000      /* insts for .fini */

/* STYP_EXTENDESC says its an escape bit but no one was using it,
 * nor using a masking field to get the correct bits. I(jpm)
 * added the STYP_MASK and only overloaded 8 bits.(see below)
 */
#define STYP_EXTENDESC  0x02000000  /* Escape bit for adding additional */
                                    /* section type flags. The mask     */
                                    /* for valid values is 0x02FFF000.  */
                                    /* No other bits should be used.    */
#define STYP_LITA       0x04000000  /* address literals only        */
#define STYP_LIT8       0x08000000  /* literal pool for 8 byte literals */
#define STYP_LIT4       0x10000000  /* literal pool for 4 byte literals */
#define S_NRELOC_OVFL   0x20000000  /* s_nreloc overflowed, the value is in
                                       v_addr of the first entry */
#define STYP_LIB        0x40000000  /* section is a .lib section */
#define STYP_INIT       0x80000000  /* section only contains the text
                                       instructions for the .init sec. */

/* Since we are basically out of bits for STYPs, and have taken to
 * overloading bit fields, I've defined a mask to use to give
 * us more breathing room; Thus when checking any of the following
 * STYPs one must use the mask and compare for value;
 */   
#define STYP_EXTMASK    0x0FF00000
#define STYP_COMMENT    0x02100000  /* */
#define STYP_RCONST     0x02200000  /* Overloads with reginfo */
#define STYP_MSYM       0x02300000  /* .msym dso section */
#define STYP_XDATA      0x02400000  /* exception handling sections */
#define STYP_TLSDATA    0x02500000  /* Initialized thread local storage */
#define STYP_TLSBSS     0x02600000  /* Uninitialized thread local storage */
#define STYP_TLSINIT    0x02700000  /* TLS data initialization template */
#define STYP_PDATA      0x02800000  /* exception handling sections */

#define _MIPS_NSCNS_MAX 35

#endif /* __LANGUAGE_C__ || __cplusplus */
#ifdef __LANGUAGE_PASCAL__
#define STYP_REG        16#00000000 /* "regular" section: allocated, relocated, loaded */
#define STYP_DSECT      16#00000001 /* "dummy" section: not allocated, relocated,not loaded */
#define STYP_NOLOAD     16#00000002 /* "noload" section: allocated, relocated, not loaded */
#define STYP_GROUP      16#00000004 /* "grouped" section: formed of input sections */
#define STYP_PAD        16#00000008 /* "padding" section: not allocated, not relocated, loaded */
#define STYP_COPY       16#00000010 /* "copy" section:for decision function used by field update;
                                   not allocated, not relocated, loaded;  reloc &
                                   lineno entries processed normally */
#define STYP_TEXT       16#00000020 /* section contains text only */
#define STYP_DATA       16#00000040 /* section contains data only */
#define STYP_BSS        16#00000080 /* section contains bss only */
#define STYP_RDATA      16#00000100 /* section contains read only data */
#define STYP_SDATA      16#00000200 /* section contains small data only */
#define STYP_SBSS       16#00000400 /* section contains small bss only */
#define STYP_UCODE      16#00000800 /* section only contains ucodes */

/* of dso related sections types */
#define STYP_GOT        16#00001000
#define STYP_DYNAMIC    16#00002000
#define STYP_DYNSYM     16#00004000
#define STYP_REL_DYN    16#00008000
#define STYP_DYNSTR     16#00010000
#define STYP_HASH       16#00020000

/* Mips specific dso sections */
#define STYP_DSOLIST    16#00040000
#define STYP_RESERVED   16#00080000 /* Reserved */
#define STYP_CONFLICT   16#00100000
#define STYP_REGINFO    16#00200000
#define STYP_RESERVED2  16#00400000
#define STYP_RESERVED3  16#00800000
#define STYP_FINI       16#01000000     /* insts for .fini */
#define STYP_EXTENDESC  16#02000000 /* Escape bit for adding additional */
                                    /* section type flags. The mask     */
                                    /* for valid values is 0x02FFF000.  */
                                    /* No other bits should be used.    */
#define STYP_LITA       16#04000000 /* address literals only        */
#define STYP_LIT8       16#08000000 /* literal pool for 8 byte literals */
#define STYP_LIT4       16#10000000 /* literal pool for 4 byte literals */
#define S_NRELOC_OVFL   16#20000000 /* s_nreloc overflowed, the value is in
                                       v_addr of the first entry */
#define STYP_LIB        16#40000000 /* section is a .lib section */
#define STYP_INIT       16#80000000 /* section only contains the text
                                       instructions for the .init sec. */
#define STYP_MASK       16#0FF00000         /* See above */
#define STYP_COMMENT    16#02100000 
#define STYP_RCONST     16#02200000          /* Overloads with reginfo */
#define STYP_XDATA      16#02400000
#define STYP_TLSDATA    16#02500000 /* Initialized thread local storage */
#define STYP_TLSBSS     16#02600000 /* Uninitialized thread local storage */
#define STYP_TLSINIT    16#02700000 /* TLS data initialization template */
#define STYP_PDATA      16#02800000

#endif /* __LANGUAGE_PASCAL__ */

/*
 *  In a minimal file or an update file, a new function
 *  (as compared with a replaced function) is indicated by S_NEWFCN
 */

#define S_NEWFCN  0x100

/*
 * In 3b Update Files (output of ogen), sections which appear in SHARED
 * segments of the Pfile will have the S_SHRSEG flag set by ogen, to inform
 * dufr that updating 1 copy of the proc. will update all process invocations.
 */

#define S_SHRSEG    0x20

/* gp_table and libscn definitions provided for source compatibility.
 * These structures are not supported in Digital UNIX objects.
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
union gp_table {
  struct {
    int current_g_value; /* actual value */
    int unused;
  } header;
  struct {
    int g_value; /* hypothetical value */
    int bytes;  /* section size corresponding to hypothetical value */
  } entry;
}; 
#define GPTAB   union gp_table
#define GPTABSZ sizeof(GPTAB)

#endif /* __LANGUAGE_C__ || __cplusplus */

#ifdef __LANGUAGE_PASCAL__
type
  gp_table = record
    case boolean of
      false: (current_g_value: integer; unused: integer);
      true: (g_value: integer; bytes: integer);
    end;
  gpt_ptr = ^gp_table;
#endif /* __LANGUAGE_PASCAL__ */

/*
 * This is the definition of a mips .lib section entry.  Note the size and
 * offset are in sizeof(int)'s not bytes.
 */
#if defined(__LANGUAGE_C__) || defined(__cplusplus)
struct libscn {
    int size;       /* size of this entry (including target name) */
    int offset;     /* offset from start of entry to target name  */
    long    tsize;      /* text size in bytes, padded to DW boundary  */
    long    dsize;      /* initialized data "     "    "  "   "       */
    long    bsize;      /* uninitialized data "   "    "  "   "       */
    long    text_start; /* base of text used for this library         */
    long    data_start; /* base of data used for this library         */
    long    bss_start;  /* base of bss used for this library          */
};

#endif /* __LANGUAGE_C__ || __cplusplus */

/* Obsolete definitions */

#define LIBSCN  struct libscn
#define LSCNSZ  sizeof(LIBSCN)

#endif
