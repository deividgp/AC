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
 * @(#)$RCSfile: localedef.h,v $ $Revision: 1.1.12.7 $ (DEC) $Date: 1995/04/27 20:15:46 $
 */
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 * COMPONENT_NAME: (CMDLOC) Locale Database Commands
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * 1.13  com/inc/sys/localedef.h, libcnls, bos320, 9132320 7/31/91 09:53:36
 */
#ifndef _SYS_LOCALEDEF_H_
#define _SYS_LOCALEDEF_H_
#ifdef __cplusplus
extern "C" {
#endif

/*
  Call the method named 'n' from the handle 'hdl' which returns type 't'.
*/
#define _METHOD(hdl,n)	    (*(hdl->core.n))
#define _METHOD_EXT(hdl,n)  (*(hdl->methods->n))

/*
  Used to default without handle if none active
*/
#define _IF_METHOD(h,n)	        if (h->core.n)
#define _IF_METHOD_EXT(hdl,n)   if (hdl->methods->n)

/*
 * Forward define the major locale class objects before any
 * possible references
 */
typedef struct _LC_charmap_t 	_LC_charmap_t;
typedef struct _LC_monetary_t 	_LC_monetary_t;
typedef struct _LC_numeric_t	_LC_numeric_t;
typedef struct _LC_resp_t	_LC_resp_t;
typedef struct _LC_time_t	_LC_time_t;
typedef struct _LC_collate_t	_LC_collate_t;
typedef struct _LC_ctype_t	_LC_ctype_t;
typedef struct _LC_locale_t	_LC_locale_t;

#include <sys/lc_core.h>

#if defined(__STDC__) || defined(__cplusplus)
#	define	_signed	signed
#ifdef _LOCALEDEF
#	define	_const		/* So localedef can assign into locale objects */
#else /* _LOCALEDEF */
#	define _const	const	/* Warn about any assignments */
#endif /* _LOCALEDEF */
#else /* __STDC__  || __cplusplus */
#	define	_signed
#	define  _const
#endif /* __STDC__  || __cplusplus */


/* _LC_charmap_t
**
** Structure representing CHARMAP class which maps characters to process code
** and vice-verse.
*/
struct _LC_charmap_t {

    _LC_core_charmap_t core;
    
    char     *cm_csname;	/* codeset name  */
    
    unsigned long   cm_mb_cur_max; /* max encoding length for this codeset  */
    unsigned long   cm_mb_cur_min; /* min encoding length for this codeset  */

    unsigned char
	     cm_max_disp_width; /* max display width of any char */
				/* in the codeset */
#ifdef _AIX
    unsigned int	cs_hbound; /* Upper bound on unique width code points */
    unsigned 
	char *cm_cstab;		/* character set id table. */
#endif    
};


/* _LC_monetary_t
**
** Structure representing MONETARY class which defines the formatting
** of monetary quantities for a locale.
*/
struct _LC_monetary_t {

    _LC_core_monetary_t   core;
    
    char *int_curr_symbol;	   /* international currency symbol*/
    char *currency_symbol;	   /* national currency symbol	*/
    char *mon_decimal_point;	   /* currency decimal point	*/
    char *mon_thousands_sep;	   /* currency thousands separator*/
    char *mon_grouping;		   /* currency digits grouping	*/
    char *positive_sign;	   /* currency plus sign		*/
    char *negative_sign;	   /* currency minus sign		*/
    _signed char int_frac_digits;   /* internat currency fract digits*/
    _signed char frac_digits;	   /* currency fractional digits	*/
    _signed char p_cs_precedes;	   /* currency plus location	*/
    _signed char p_sep_by_space;	   /* currency plus space ind.	*/
    _signed char n_cs_precedes;	   /* currency minus location	*/
    _signed char n_sep_by_space;	   /* currency minus space ind.	*/
    _signed char p_sign_posn;	   /* currency plus position	*/
    _signed char n_sign_posn;	   /* currency minus position	*/
    char *debit_sign;		   /* currency debit symbol	*/
    char *credit_sign;		   /* currency credit symbol	*/
    char *left_parenthesis;	   /* currency left parenthesis	*/
    char *right_parenthesis;	   /* currency right parenthesis	*/
    
};


/* _LC_numeric_t  	
**
** Structure representing NUMERIC class which defines the formatting 
** of numeric quantities in a locale.
*/
struct _LC_numeric_t {

    _LC_core_numeric_t core;
    
    char     *decimal_point;
    char     *thousands_sep;
    unsigned
	char *grouping;
    
};


/* _LC_resp_t
** 
** Structure representing RESPONSE class which defines the content
** of affirmative versus negative responses in a locale.
*/
struct _LC_resp_t  {

    _LC_core_resp_t core;

    char    *yesexpr;	     /* POSIX: Expression for affirmative. */
    char    *noexpr;	     /* POSIX: Expression for negative. */
    char    *yesstr;	     /* X/OPEN: colon sep str for affirmative. */
    char    *nostr;	     /* X/OPEN: colon sep str for negative. */

};


/* _LC_time_t  
** 
** Structure representing the TIME class which defines the formatting
** of time and date quantities in this locale.
*/
struct _LC_time_t {

    _LC_core_time_t core;
    
    char *d_fmt;  
    char *t_fmt;  
    char *d_t_fmt;
    char *t_fmt_ampm;
    char *abday[7];  
    char *day[7];    
    char *abmon[12];  
    char *mon[12];    
    char *am_pm[2];
    char **era;			/* NULL terminated array of strings */
    char *era_year;
    char *era_d_fmt;
    char *alt_digits;
    char *m_d_recent;		/* recent month-day format: OSF extension */
    char *m_d_old;		/* old month-day format:  OSF extension */
    char *era_d_t_fmt;
    char *era_t_fmt;
};


/* _LC_weight_t
** 
** Array of collation weights for a character or collating symbol.
** Version 1 Structure (retained for upward compatibility)
*/
#define _COLL_WEIGHTS_INLINE (sizeof(unsigned int *)/sizeof(unsigned int))

typedef union {
    unsigned int n[_COLL_WEIGHTS_INLINE];
    		       /* This type is used if the number of  */
    		       /* orders can fit into this space      */
             
    _const unsigned int      /* This type is used if the number of  */
	  *p;	       /* collation orders won't fit          */
} _LC_weight_t;    
  
/* _LC_collel_t
**
** Collation data for a collation symbol
** Version 1 Structure (retained for upward compatibility)
*/
typedef struct {

    _const char         *ce_sym; /* value of collation symbol           */
    _LC_weight_t ce_wgt;	/* The weights associated with a       */
				/* collating symbol matching ce_sym    */
} _LC_collel_t;


/* _LC_coltbl_v1_t
** 
** Array of per-character collation data for locale.
** Version 1 Structure (retained for upward compatibility)
*/
typedef struct {
    _LC_weight_t   ct_wgt;    /* The collation weights for this      */
			      /* character.                          */

    _const _LC_collel_t   *ct_collel;/* Pointer to collation symbol array   */
} _LC_coltbl_v1_t;

/*
 *********
 * Version 2 structures
 *********
 */

/* Define a datatype for the string pool */
typedef char _LC_strpool_t, *_LC_strpool_ptr_t;

/* _LC_collel_tbl_v2_t
** 
** Array of per-character collation data for locale.
**
**     strpool_idx - idx into string pool array (eliminate ptr usage)
**     ce_wgts     - variable length array of n-weights (where n=co_nord)
**
** Version 2 structures: Implement basic space compression techniques
*/
typedef struct {
	int          strpool_idx;
	unsigned int ce_wgt[1];
} _LC_collel_tbl_v2_t;

/*
** Declare the collate element table for the version currently supported
** Version 2 structures: Implement basic space compression techniques
**/
typedef _LC_collel_tbl_v2_t  _LC_collel_tbl_t;

/* _LC_collel_qidx_v2_t
** 
** Single Dimensional Array containing a (Quick) idx value into the collel_tbl_v2
** structure. If no collation element defined, the idx is -1. The min/max values
** for the wc entries containing a collating element is saved.  This allows for
** compression of the array
**
** Version 2 structures: Implement basic space compression techniques
*/
typedef struct {
	unsigned int min;
	unsigned int max;
	unsigned int *tbl;
} _LC_collel_qidx_v2_t;

/*
** Declare the collate element qidx type for the version currently supported
** This supports future expansion.
** Version 2 structures: Implement basic space compression techniques
**/
typedef _LC_collel_qidx_v2_t _LC_collel_qidx_t;

/* _LC_coltbl_v2_t
** 
** Control structure for collecting pointers to the various structures
** This structure is a per process structure because of the runtime resolution
*/
typedef struct {
        unsigned int         ce_tbl_bsize;    /* size of ce_tbl entry (in bytes)  (varying size) */
	unsigned int         ce_tbl_cnt;      /* no of entries in the ce_tbl                     */
	unsigned int         ce_strpool_cnt;  /* Length of string pool array                     */
	unsigned int         version_mask;    /* mask value for the type of structures used      */
	_LC_strpool_t        *ce_strpool;     /* ptr to array of chars (or strings)              */
	_LC_collel_tbl_t     *ce_tbl;         /* ptr to the coll element entries in the locale   */
	_LC_collel_qidx_t    *ce_qidx;        /* ptr to qidx structure                           */
	unsigned int         *ct_wgt[1];      /* variable array of pointers to wgt tables        */
} _LC_coltbl_v2_t;

/* _LC_coll_methods_t
 *
 * Place New Collation Methods Here
 */
typedef struct {
  int (*getcolval) __((_LC_collate_t *hdl, unsigned int *colval, unsigned int realwc, const char *str, int order));
} _LC_coll_methods_t;

/* _LC_coltbl_t
 * 
 * Union of the v1 and v2 coltbl structures - for upward compatibility support
 */

#ifdef _LOCALEDEF
/* Localedef internals uses v1 structures */
typedef _LC_coltbl_v1_t _LC_coltbl_t;
#else
typedef union {
  _LC_coltbl_v1_t  ct_v1;
  _LC_coltbl_v2_t  ct_v2;
} _LC_coltbl_t;
#endif

/* _LC_subs_t
**
** Substring source and target pair
*/
typedef struct {

    _LC_weight_t ss_act;	/* indicates for which orders this */
				/* susbstitution string is active. */
    _const char *ss_src;	/* source string to match */
    _const char *ss_tgt;	/* target string to replace */

} _LC_subs_t;


/* _LC_collate_t
**
** Structure representing COLLATE class defining the collation rules
** for a locale.
*/
#define _COLL_COLELM_1ARRAY_MASK    0x1
#define _COLL_COLELM_TRIE_MASK      0x2
#define _COLL_VERSION               0x1

struct _LC_collate_t {

    _LC_core_collate_t core;
    
    unsigned			            /* number of collation orders */
	char    co_nord;	            /* supported in this locale */
    
    unsigned			            /* Version number for collation support    */
	char    version;	            /* Introduced in _LC_VERSION = 2           */
                                            /* Value is defined by _COLL_VERSION       */
    
    unsigned			            /* Flag to indicate there is a collating element table */
	char    ce_defined;	            /* in this locale */
    
    _LC_weight_t co_sort;	            /* sort order     */
					    /* processing flags    */
    
    unsigned int     co_wc_min;		    /* min process code    */
    unsigned int     co_wc_max;		    /* max process code    */
    unsigned int     co_hbound;		    /* max process code with "unique" info */

    unsigned int     co_col_min;	    /* min coll weight     */
    unsigned int     co_col_max;	    /* max coll weight     */

    _const _LC_coltbl_t *co_coltbl; 	    /* array of collation  */
				            /* weights, symbols    */
    unsigned
	char    co_nsubs;		    /* number of sub strs  */
    _const _LC_subs_t         *co_subs;     /* substitution strs   */
    _const _LC_coll_methods_t *methods;     /* ptr to new methods  */
};

/*
** MASKS for the co_colmod[] sort modifier array
*/
#define _COLL_FORWARD_MASK   0x1
#define _COLL_BACKWARD_MASK  0x2
#define _COLL_NOSUBS_MASK    0x4
#define _COLL_POSITION_MASK  0x8
#define _COLL_CHAR_ORDER_MASK 0x10
  
/*
** MASKS for the ss_act[] flags
*/
#define _SUBS_ACTIVE         1
#define _SUBS_REGEXP         2
  
/* _LC_classnm_t
**
** Element mapping class name to a bit-unique mask.
*/
typedef struct {

    char    *name;
    unsigned
	int mask;

} _LC_classnm_t;


/* _LC_ctype_t
**
** Structure representing CTYPE class which defines character
** membership in a character class.
*/
struct _LC_ctype_t {

  _LC_core_ctype_t core;

  /* min and max process code */
  unsigned int      min_wc;
  unsigned int      max_wc;

  unsigned int      max_upper;	/* Last character with upper-case equiv */
  unsigned int      max_lower;	/* Last character with lower-case equiv */

  /* upper, lower translation */
  _const unsigned int      *_upper;	/* [0..max_upper] */
  _const unsigned int      *_lower;	/* [0..max_lower] */
  
  /* character class membership */
  _const unsigned
      int      *_mask;       /* Array of masks for CPs 0..255 */
  _const unsigned
      int      *qmask;	     /* Array of masks for CPs 255..+ */
  _const unsigned
      char     *qidx;	     /* index into qmask for CPs 255..+ */

  unsigned int	qidx_hbound;	/* Last code-point with unique qidx value */
  /* class name mapping */
  unsigned
      char     nclasses;
 _const _LC_classnm_t *classnms;
  
  unsigned int	num_rows;   /* number of rows    in qmask table */
  unsigned int	num_qmasks; /* number of columns in qmask table */
};

/*
** The masks for characters are stored in _LC_ctype_t's qmask table.
** That table is a two-dimensional array, with columns representing
** masks, and rows representing slices of those masks.
**
** Only the low _CTYPE_NUM_MASK_BITS bits of each array element are
** used as mask bits.  The remaining high bits are kept clear.
**
** The masks for character classes are stored in _LC_ctype_t's
** classnms table.  Since a character class mask has only one mask
** bit set, the table stores only the slice containing that bit.
** The high bits are used to indicate which slice it is.
**
** This format lets wctype("alpha") return the mask for "alpha" in a
** wctype_t.  And it lets iswctype(wctype_t, 'a') check just one
** slice of the mask for 'a', instead of the entire mask.
*/
#define _CTYPE_NUM_MASK_BITS   28
#define _CTYPE_ROW_MASK        (~0 << _CTYPE_NUM_MASK_BITS)

/*
** The number of character classes is limited by the type of two
** _LC_ctype_t fields:  nclasses and qidx.  Both are 'unsigned char'.
*/
#define _CTYPE_MAX_CHARCLASSES 255

/* _LC_locale_t
** 
** Entry point to locale database.  setlocale() receives a pointer to 
** this structure from __lc_load().
*/

/**********
** IF THIS NUMBER CHANGES, IT MUST ALSO BE CHANGED IN
** langinfo.h
**********/
#ifndef _NL_NUM_ITEMS
#define _NL_NUM_ITEMS	61
#endif

#define	_NL_OLD_SIZE	55

/* forward declaration as required by C++ */
#ifdef __cplusplus
struct lconv;
#endif

struct _LC_locale_t {

    _LC_core_locale_t core;
    char           *nl_info[_NL_OLD_SIZE];    /* Should be at end for growth */
					      /* instead must overflow to nl_info2 */
    struct lconv   *nl_lconv;
    
    _LC_charmap_t  *lc_charmap;
    _LC_collate_t  *lc_collate;
    _LC_ctype_t    *lc_ctype;
    _LC_monetary_t *lc_monetary;
    _LC_numeric_t  *lc_numeric;
    _LC_resp_t     *lc_resp;
    _LC_time_t     *lc_time;
    char	   *nl_info2[_NL_NUM_ITEMS - _NL_OLD_SIZE];
};

#define _LC_MAX_OBJECTS   256
#define _DFLT_LOC_PATH    "/usr/lib/nls/loc/"

extern _LC_charmap_t  *__lc_charmap;
extern _LC_collate_t  *__lc_collate;
extern _LC_ctype_t    *__lc_ctype;
extern _LC_monetary_t *__lc_monetary;
extern _LC_numeric_t  *__lc_numeric;
extern _LC_resp_t     *__lc_resp;
extern _LC_time_t     *__lc_time;
extern _LC_locale_t   *__lc_locale;

#ifdef _LIBC_POLLUTION_H_
#if defined(__STDC__) || defined(__cplusplus)
#define	_MNAME(n)	__ ## n
#else
#define _MNAME(n)	__/**/n
#endif
#else
#define _MNAME(n)	n
#endif

#define _ISMACRO(c,cmsk) ((_METHOD(__lc_ctype,_MNAME(iswctype)) == 0L) \
		? (int) (__lc_ctype->_mask[c] & (cmsk)) \
		: _METHOD(__lc_ctype,_MNAME(iswctype)) (c,cmsk,__lc_ctype))
#define _TOUPPER(c) ((int) ((_METHOD(__lc_ctype,_MNAME(towupper)) == 0L) \
		? __lc_ctype->_upper[c] \
		: _METHOD(__lc_ctype,_MNAME(towupper)) (c,__lc_ctype)))
#define _TOLOWER(c) ((int) ((_METHOD(__lc_ctype,_MNAME(towlower)) == 0L) \
		? __lc_ctype->_lower[c] \
		: _METHOD(__lc_ctype,_MNAME(towlower)) (c,__lc_ctype)))

#define _ISWMACRO(c,cmsk) ((_METHOD(__lc_ctype,_MNAME(iswctype)) == 0L) \
		? (int) (__lc_ctype->_mask[(int)(c)] & (cmsk)) \
		: _METHOD(__lc_ctype,_MNAME(iswctype)) (c,cmsk,__lc_ctype))
#define _TOWUPPER(c)	 ((_METHOD(__lc_ctype,_MNAME(towupper)) == 0L) \
		? __lc_ctype->_upper[(int)(c)] \
		: _METHOD(__lc_ctype,_MNAME(towupper)) (c,__lc_ctype))
#define _TOWLOWER(c)	 ((_METHOD(__lc_ctype,_MNAME(towlower)) == 0L) \
		? __lc_ctype->_lower[(int)(c)] \
		: _METHOD(__lc_ctype,_MNAME(towlower)) (c,__lc_ctype))

#ifdef __cplusplus
}
#endif
#endif  /* _SYS_LOCALEDEF_H_ */
