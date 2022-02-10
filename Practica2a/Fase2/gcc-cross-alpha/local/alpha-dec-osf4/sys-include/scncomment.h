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

#ifndef _SCNCOMMENT_H_
#define _SCNCOMMENT_H_
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Structure of an internal header in the .comment section.
 *
 *	cm_tag identifies the type of data in this subsection of the
 *	    .comment section.
 *
 *	cm_len gives the length in bytes of this subsection's data.
 *	    If cm_len is zero, the data is stored in the cm_val field.
 *
 *	cm_val is either a pointer to this subsection's data or is
 *	    itself the data.  If cm_len is non-zero, cm_val is a
 *	    relative file offset to the start of the data.  The offset
 *	    is relative to the beginning of the .comment section.
 */

typedef struct {
    unsigned int	cm_tag;
    unsigned int	cm_len;
    unsigned long	cm_val;
} CMHDR;

#define CMHDRSZ sizeof(CMHDR)

/* 
 * Version of .comment section format 
 */
#define CM_VERSION 0

/*
 * Values for cm_tag  
 */
#define CM_NULL              0       	/* marker for last internal header */
#define CM_END               0       	/* new name for last header */
#define CM_CMSTAMP           3       	/* version stamp header, must be first */
#define CM_COMPACT_RLC       4       	/* compact relocation data */
#define CM_STRSPACE          5       	/* generic string space */
#define CM_TAGDESC           6       	/* tag descriptor subsection */
#define CM_IDENT             7       	/* ident strings */
#define CM_TOOLVER	     8 	     	/* tool-specific version information */
#define CM_LOUSER            0x80000000 /* beginning of user range */
#define CM_HIUSER            0xffffffff /* end of user range */

/*
 *  Comment Section Flags
 */
typedef struct {
    unsigned int	cmf_strip:3;
    unsigned int	cmf_combine:5;
    unsigned int	cmf_modify:4;
    unsigned int	:20;
} cm_flags_t;

typedef enum {
    CMFS_KEEP   = 0,
    CMFS_STRIP  = 1,
    CMFS_LSTRIP = 2
} cmfs_t;

typedef enum {
    CMFC_APPEND  = 0,
    CMFC_CHOOSE  = 1,
    CMFC_DELETE  = 2,
    CMFC_ERRMULT = 3,
    CMFC_ERROR   = 4
} cmfc_t;

typedef enum {
    CMFM_COPY   = 0,
    CMFM_DELETE = 1,
    CMFM_ERROR  = 2
} cmfm_t;

#define CMFS_FLAG(flags) flags.cmf_strip
#define CMFC_FLAG(flags) flags.cmf_combine
#define CMFM_FLAG(flags) flags.cmf_modify

#define CMF_SET_FLAGS(flags, s, c, m) ((flags).cmf_strip = s, \
                                       (flags).cmf_combine = c, \
                                       (flags).cmf_modify = m)

#define CMF_SET_DEFAULT(flags) ((flags).cmf_strip = CMFS_KEEP, \
                                (flags).cmf_combine = CMFC_APPEND,\
                                (flags).cmf_modify = CMFM_COPY)

#define CMF_SAME_FLAGS(f1, f2) ((f1.cmf_strip == f2.cmf_strip) && \
                                (f1.cmf_combine == f2.cmf_combine) && \
                                (f1.cmf_modify == f2.cmf_modify))


/* 
 * Tag Descriptor Structure (CM_TAGDESC)
 */ 

struct cm_td {
    unsigned int	tag;	/* subsection tag value */
    cm_flags_t		flags;	/* flag values defined in scncomment.h */
};

typedef struct cm_td cm_td_t;


/*
******************************************************************************
**
**  The rest of the definitions in this file describe the old format of
**  the .comment section.  They are described here so tools can process
**  old objects.  New tools should not generate object files using these
**  definitions.
**
******************************************************************************
*/

typedef struct {
#if defined(__mips64) || defined(__alpha)
    unsigned long cm_tag;
#else
    unsigned cm_tag;
#endif
    union {
	unsigned long cm_val;
	unsigned long cm_ptr;
    } cm_un;
} CM;

#if defined(__mips64) || defined(__alpha)
/* #define CM_NULL            0L */
#define CM_RELOC_NO        1L
#define CM_RELOC_PTR       2L
#else
/* #define CM_NULL            0x00000000 */
#define CM_RELOC_NO        0x00000001
#define CM_RELOC_PTR       0x00000002  
#endif

struct full_rlc {
    int type;
    unsigned long konst;
    unsigned long vaddr;
    unsigned long dist2lo;
};

#if defined(__mips64) || defined(__alpha)
#define CM_R_TYPE_NULL      0
#define CM_R_TYPE_ABS       1
#define CM_R_TYPE_GPREL32   2
#define CM_R_TYPE_QUAD      3
#define CM_R_TYPE_GPHI_LO   4  
#define CM_R_TYPE_WORD      5  /* 32-bit */
/* Don't use type 6 until pixie is fixed */
#define CM_R_TYPE_INITHI_LO 7
#define CM_R_TYPE_SREL16    8
#define CM_R_TYPE_SREL32    9
#define CM_R_TYPE_SREL64   10
#define CM_R_TYPE_PUSHPSUB 11
#define CM_R_TYPE_SHIFTSTORE 12
#define CM_R_TYPE_GPVALUE  13
#define CM_R_TYPE_EXTENDED_TYPE 15
#else
#define CM_R_TYPE_NULL      0
#define CM_R_TYPE_ABS       1
#define CM_R_TYPE_REL32     2
#define CM_R_TYPE_WORD      3
#define CM_R_TYPE_GPHI_LO   4
#define CM_R_TYPE_JMPADDR   5
#define CM_R_TYPE_GPHI_LO2  6
#endif

typedef struct {
    char *scn_praw;
    char *rlc_ptr;
    char *cur_rlc_ptr;
    int  rlc_no;
    int  cur_rlc_no;
    unsigned long last_base;
    struct full_rlc rlc_entry;
} cm_struct ;


/* this struct must be the same as next, except for the last item, */
/* which is the constant for the addend */
#if defined(__mips64) || defined(__alpha)
#define        ADDEND_NOCONST  0
#define        ADDEND_CONST    1   /* if an addend included, e.g. sym + k */
#define        ADDEND_BASE     2   /* base of address to be relocated */
#define        DEL_VADDR_MASK   0xFFFFF00000000000

struct COMPACT_RELOC {
    unsigned long addend:  4;
    unsigned long type:    4;      /* relocation type */
    unsigned long del_lo:  8;      /* delta to ref_lo from ref_hi, shifted 2 */
    signed   long del_vaddr: 48;   /* delta addr, from previous entry */
};

#else /* defined(__mips64) || defined(__alpha) */

struct COMPACT_RELOC {
    unsigned addend:  2;
#define        ADDEND_NOCONST  0
#define        ADDEND_CONST    1   /* if an addend included, e.g. sym + k */
#define        ADDEND_BASE     2   /* base of address to be relocated */
    unsigned type:    3;           /* relocation type */
    unsigned del_lo:  8;           /* delta to ref_lo from ref_hi, shifted 2 */
    
    signed del_vaddr: 19;          /* delta addr, from previous entry */
                                   /* to be relocated */
#define        DEL_VADDR_MASK   0xFFFF8000
};

#endif /* defined(__mips64) || defined(__alpha) */

struct COMPACT_RELOC_C {
    struct COMPACT_RELOC _rlc;
    unsigned long addend_const;         /* k of addend */
};

struct COMPACT_RELOC_C_BASE {
    struct COMPACT_RELOC _rlc;
    unsigned long addend_const;         /* k of addend */
    unsigned long base;                 /* base for next delta */
};

struct COMPACT_RELOC_BASE {
    struct COMPACT_RELOC _rlc;
    unsigned long base;                 /* base for next delta */
};


union cm_rlc {
    struct COMPACT_RELOC            r;
    struct COMPACT_RELOC_C_BASE    cb;
    struct COMPACT_RELOC_C          c;
    struct COMPACT_RELOC_BASE       b;
};


#define VADDR_OVFL(delta)  (((delta & DEL_VADDR_MASK) != 0) && \
			    ((delta & DEL_VADDR_MASK) != DEL_VADDR_MASK))

#define VADDR_DELTA(delta) (delta & ~DEL_VADDR_MASK)

#ifdef __cplusplus
}
#endif
#endif /* _SCNCOMMENT_H_ */
