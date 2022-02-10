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
/* Header file modified for bigendian by BigEndian_H. */
/*	Run on Sun Jun  7 18:08:49 1992
 */
/********************************************************************************************************************************/
/* Created  7-JUN-1992 18:08:39 by VAX SDL V3.2-12     Source: 24-MAR-1992 14:27:11 CDA$DEVELOP_ROOT:[CDABUILD.LIB.SRC]DTIFDEF.SD */
/********************************************************************************************************************************/
/*** MODULE DTIF_DEFINITIONS IDENT V1-001 ***/
#ifndef _dtifdef_
#define _dtifdef_
/*++                                                                        */
/*  COPYRIGHT (c) 1988, 1992 BY                                             */
/*  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.                  */
/*  ALL RIGHTS RESERVED.                                                    */
/*                                                                          */
/*  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND COPIED   */
/*  ONLY  IN  ACCORDANCE  OF  THE  TERMS  OF  SUCH  LICENSE  AND WITH THE   */
/*  INCLUSION OF THE ABOVE COPYRIGHT NOTICE. THIS SOFTWARE OR  ANY  OTHER   */
/*  COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY   */
/*  OTHER PERSON.  NO TITLE TO AND  OWNERSHIP OF THE  SOFTWARE IS  HEREBY   */
/*  TRANSFERRED.                                                            */
/*                                                                          */
/*  THE INFORMATION IN THIS SOFTWARE IS  SUBJECT TO CHANGE WITHOUT NOTICE   */
/*  AND  SHOULD  NOT  BE  CONSTRUED  AS A COMMITMENT BY DIGITAL EQUIPMENT   */
/*  CORPORATION.                                                            */
/*                                                                          */
/*  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE  OR  RELIABILITY OF ITS   */
/*  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.                 */
/*                                                                          */
/* Item codes for cda_create_root_aggregate processing-options parameter.   */
#define DTIF_INHERIT_ATTRIBUTES 513     /* Inherit attributes to cols, rows, cells, etc. */
#define DTIF_INHERIT_ATTR_TO_ROW_COL 514 /* Inherit only to row-col level   */
#define DTIF_INHERIT_ATTR_FROM_ROW_COL 515 /* Inherit only from row-col level to cells */
#define DTIF_RETAIN_DEFINITIONS 516     /* Enable cda_find_definition       */
/* Scope codes for the cda_enter_scope and cda_leave_scope scope-code parameter. */
/* If an aggregate type is listed, it must be presented with CDA$ENTER_SCOPE. */
#define DTIF_K_DOCUMENT_SCOPE 512       /* Document scope                   */
#define DTIF_K_TABLE_SCOPE 513          /* Table scope			DTIF_TBL */
#define DTIF_K_ROW_SCOPE 514            /* Row scope			DTIF_ROW */
#define DTIF_K_CELLS_SCOPE 515          /* Cells scope                      */
/* Aggregate type codes for DTIF (Digital Table Interchange Format).        */
#define DTIF_DTF 513                    /* DTIF document root               */
#define DTIF_DSC 514                    /* Document descriptor              */
#define DTIF_HDR 515                    /* Document header                  */
#define DTIF_DAT 516                    /* Date and time                    */
#define DTIF_ERF 517                    /* External reference               */
#define DTIF_LPT 518                    /* Language preference table        */
#define DTIF_NVL 519                    /* Named value                      */
#define DTIF_NES 520                    /* Named edit string                */
#define DTIF_CAT 521                    /* Column attributes                */
#define DTIF_TBL 522                    /* Table definition                 */
#define DTIF_TMD 523                    /* Table metadata                   */
#define DTIF_WND 524                    /* Window definition                */
#define DTIF_ROW 525                    /* Row definition                   */
#define DTIF_CLD 526                    /* Cell data                        */
#define DTIF_VTX 527                    /* Varying text                     */
#define DTIF_ARD 528                    /* Array definition                 */
#define DTIF_CFT 529                    /* Complex float                    */
#define DTIF_FMI 530                    /* Format information               */
#define DTIF_CCD 531                    /* Cell coordinates                 */
#define DTIF_RNG 532                    /* Range definition                 */
#define DTIF_CLR 533                    /* Cell range                       */
#define DTIF_RWR 534                    /* Row range                        */
#define DTIF_COR 535                    /* Column range                     */
#define DTIF_NMR 536                    /* Named range                      */
#define DTIF_EXT 537                    /* External                         */
#define DTIF_RSQ 538                    /* Repeat sequence                  */
#define DTIF_FMC 539                    /* Format condition                 */
#define DTIF_RLT 540                    /* Relative time                    */
#define DTIF_ECC 541                    /* External cell coordinates        */
#define DTIF_ECR 542                    /* External cell range              */
#define DTIF_ENR 543                    /* External named range             */
#define DTIF_REF 544                    /* Reference                        */
#define DTIF_MAX 545                    /* Maximum code plus 1              */
/* Item codes for all aggregates.  DTIF_AGGREGATE_TYPE is read-only.        */
#define DTIF_USER_CONTEXT 1             /* User context	    		Longword */
#define DTIF_AGGREGATE_TYPE 2           /* Aggregate type code		Word */
#define DTIF_ALL_MAX 3                  /* Maximum code plus 1              */
/* Values for items of type 'Measurement enumeration' .                     */
#define DTIF_K_VALUE_CONSTANT 0         /*				Integer */
/*	VALUE_VARIABLE							String [Reserved for future use.] */
/* Item codes for DTIF Document Root aggregate.                             */
#define DTIF_DTF_DESCRIPTOR 131329      /* Document descriptor		DTIF_DSC */
#define DTIF_DTF_HEADER 131330          /* Document header		DTIF_HDR */
#define DTIF_DTF_TABLES 131331          /* Tables			Sequence of DTIF_TBL */
#define DTIF_DTF_MAX 131332             /* Maximum code plus 1              */
/* Item codes for Document Descriptor aggregate.  During cda_put_aggregate, the values of DTIF_DSC_ENCODE_MAJOR_VERSION and */
/* DTIF_DSC_ENCODE_MINOR_VERSION are not used.  The document always contains the current values for major and minor version. */
#define DTIF_DSC_MAJOR_VERSION 131585   /* Creator major version	Integer */
#define DTIF_DSC_MINOR_VERSION 131586   /* Creator minor version	Integer */
#define DTIF_DSC_PRODUCT_IDENTIFIER 131587 /* Product identifier		String */
#define DTIF_DSC_PRODUCT_NAME 131588    /* Product name			Array of character string */
#define DTIF_DSC_ENCODE_MAJOR_VERSION 131589 /* Encoding major version	Integer */
#define DTIF_DSC_ENCODE_MINOR_VERSION 131590 /* Encoding minor version	Integer */
#define DTIF_DSC_MAX 131591             /* Maximum code plus 1              */
/* Current values for major and minor encoding version.                     */
#define DTIF_K_MAJOR_VERSION 1
#define DTIF_K_MINOR_VERSION 4
/* Item codes for Document Header aggregate.                                */
#define DTIF_HDR_PRIVATE_DATA 131841    /* Private header data		Sequence of DTIF_NVL */
#define DTIF_HDR_TITLE 131842           /* Title			Array of character string */
#define DTIF_HDR_DATE 131843            /* Date				DTIF_DAT */
#define DTIF_HDR_EXTERNAL_REFERENCES 131844 /* External references		Sequence of DTIF_ERF */
#define DTIF_HDR_LANGUAGES_C 131845     /* Languages			Array of enumeration */
#define DTIF_HDR_LANGUAGES 131846       /*				Array of variable */
#define DTIF_HDR_LANGUAGE_PREF_TABLES 131847 /* Language preference tables	Sequence of DTIF_LPT */
#define DTIF_HDR_GENERIC_COLUMNS 131848 /* Generic column attributes	Sequence of DTIF_CAT */
#define DTIF_HDR_GENERAL_TEXT_CCS_C 131849 /* General text coded char.set  Array of enumeration */
#define DTIF_HDR_GENERAL_TEXT_CCS 131850 /*				Array of variable */
#define DTIF_HDR_PATTERN_LIST 131851    /* Pattern definition list	Sequence of DDIF_PTD */
#define DTIF_HDR_FONT_LIST 131852       /* Font definition list		Sequence of DDIF_FTD */
#define DTIF_HDR_DOC_RANGES 131853      /* Range definition list	Sequence of DTIF_RNG */
#define DTIF_HDR_MAX 131854             /* Maximum code plus 1              */
/* Values of DTIF_HDR_LANGUAGES_C.                                          */
#define DTIF_K_ISO_639_LANGUAGE 0       /* ISO 639 language name	String */
#define DTIF_K_OTHER_LANGUAGE 1         /* Other language name		Character string */
/* Values of DTIF_HDR_GENERAL_TEXT_CCS_C.                                   */
#define DTIF_K_CCS_VACANT 1             /* Vacant			None (null string) */
#define DTIF_K_CCS_UNKNOWN 2            /* Unknown			String */
#define DTIF_K_CCS_ASCII_GL 3           /* ASCII gl			String */
#define DTIF_K_CCS_1_OCTET 4            /* One octet			String */
#define DTIF_K_CCS_2_OCTET 5            /* Two octets			String */
#define DTIF_K_CCS_4_OCTET 6            /* Four octets			String */
/* Item codes for Date and Time aggregate.                                  */
#define DTIF_DAT_DATETIME 132097        /* Date and time		String */
#define DTIF_DAT_TIME_DIFF_C 132098     /* Time difference		Enumeration */
#define DTIF_DAT_TIME_DIFF 132099       /*				Variable */
#define DTIF_DAT_MAX 132100             /* Maximum code plus 1              */
/* Values of DTIF_DAT_TIME_DIFF_C.                                          */
#define DTIF_K_UTC_TIME 0               /* UTC time			None */
#define DTIF_K_PLUS_DIFF 1              /* Positive difference		String */
#define DTIF_K_NEG_DIFF 2               /* Negative difference		String */
/* Item codes for External Reference aggregate.                             */
#define DTIF_ERF_DATA_TYPE 132353       /* Data type			Object identifier */
#define DTIF_ERF_DESCRIPTOR 132354      /* Descriptor			Array of character string */
#define DTIF_ERF_LABEL 132355           /* Label			Character string */
#define DTIF_ERF_LABEL_TYPE 132356      /* Label type			String with add-info */
#define DTIF_ERF_CONTROL 132357         /* Control			Enumeration */
#define DTIF_ERF_MAX 132358             /* Maximum code plus 1              */
/* Values of the add-info parameter for DTIF_ERF_LABEL_TYPE.  Must be identical */
/* to values for DDIF_ERF_LABEL_TYPE and DOTS_RTE_NAME_TYPE.                */
#define DTIF_K_PRIVATE_LABEL_TYPE 0     /* Private label type               */
#define DTIF_K_RMS_LABEL_TYPE 1         /* RMS file specification ("$RMS")  */
#define DTIF_K_UTX_LABEL_TYPE 2         /* ULTRIX file specification ("$UTX") */
#define DTIF_K_MDS_LABEL_TYPE 3         /* MS-DOS file specification ("$MDS") */
#define DTIF_K_STYLE_LABEL_TYPE 4       /* Style file specification ("$STYLE") */
#define DTIF_K_OS2_LABEL_TYPE 5         /* OS/2 file specification ("$OS2") */
#define DTIF_K_OA_LABEL_TYPE 6          /* ALL-IN-1 file specification ("$OA") */
#define DTIF_K_PACKED_STYLE_LABEL_TYPE 7 /* Style-guide file specification ("$STYLE") (used when */
/* NO_COPY style guide packed by DOTS)                                      */
/* Values of DTIF_ERF_CONTROL.						DTIF conforming */
#define DTIF_K_COPY_REFERENCE 1         /* Copy on reference                */
#define DTIF_K_NO_COPY_REFERENCE 2      /* No copy on reference             */
/* Item codes for Language Preference Table aggregate.                      */
#define DTIF_LPT_LANGUAGE_INDEX 132609  /* Language index		Integer */
#define DTIF_LPT_APPL_PRIVATE 132610    /* Application private		Sequence of DTIF_NVL */
#define DTIF_LPT_ITEMS 132611           /* Named items			Sequence of DTIF_NVL */
#define DTIF_LPT_EDITSTRS 132612        /* Named edit strings		Sequence of DTIF_NES */
#define DTIF_LPT_COLLATE_SEQ 132613     /* Collating sequence		String with add-info */
#define DTIF_LPT_COLLATE_TABLE 132614   /* Collating table		String */
#define DTIF_LPT_MAX 132615             /* Maximum code plus 1              */
/* Values of the add-info parameter for DTIF_LPT_COLLATE_SEQ.               */
#define DTIF_K_PRIVATE_COLLATE_SEQ 0    /* Private collating sequence       */
#define DTIF_K_ASCII_COLLATE_SEQ 1      /* ASCII collating sequence ("$ASCII") */
#define DTIF_K_MCS_COLLATE_SEQ 2        /* DEC Multinational collating sequence ("$MCS") */
#define DTIF_K_DANISH_COLLATE_SEQ 3     /* Danish collating sequence ("$DANISH") */
#define DTIF_K_FINSWD_COLLATE_SEQ 4     /* Finnish/Swedish collating sequence ("$FINSWD") */
#define DTIF_K_NORWEG_COLLATE_SEQ 5     /* Norwegian collating sequence ("$NORWEG") */
#define DTIF_K_SPANSH_COLLATE_SEQ 6     /* Spanish collating sequence ("$SPANSH") */
/* Item codes for Named Value aggregate.                                    */
#define DTIF_NVL_NAME 132865            /* Value name			String */
#define DTIF_NVL_VALUE_C 132866         /* Value data			Enumeration */
#define DTIF_NVL_VALUE 132867           /* 				Variable */
#define DTIF_NVL_REFERENCE_ERF_INDEX 132868 /*				Integer */
#define DTIF_NVL_MAX 132869             /* Maximum code plus 1              */
/* Values of DTIF_NVL_VALUE_C.                                              */
#define DTIF_K_VALUE_BOOLEAN 0          /*				Boolean */
#define DTIF_K_VALUE_INTEGER 1          /*				Integer */
#define DTIF_K_VALUE_TEXT 2             /*				Array of character string */
#define DTIF_K_VALUE_GENERAL 3          /*				String */
#define DTIF_K_VALUE_LIST 4             /*				Sequence of DTIF_NVL */
#define DTIF_K_VALUE_EXTERNAL 5         /*				DTIF_EXT */
#define DTIF_K_VALUE_FLOAT 6            /*				General floating point */
#define DTIF_K_VALUE_DATE 7             /*				DTIF_DAT */
#define DTIF_K_VALUE_EXPR 8             /*				CFE_EXP */
#define DTIF_K_VALUE_RELTIME 9          /*				DTIF_RLT */
#define DTIF_K_VALUE_DDIF_DOC 10        /*				DDIF_DDF */
#define DTIF_K_VALUE_DTIF_DOC 11        /*				DTIF_DTF */
#define DTIF_K_VALUE_REFERENCE 12       /*				String (& DTIF_NVL_REFERENCE_ERF_INDEX used) */
/* Item codes for Named Edit String aggregate.                              */
#define DTIF_NES_NAME 133121            /* Name				String */
#define DTIF_NES_DEFN 133122            /* Definition			ESF_EDS */
#define DTIF_NES_MAX 133123             /* Maximum code plus 1              */
/* Item codes for Column Attributes aggregate.                              */
#define DTIF_CAT_NAME 133377            /* Name				String */
#define DTIF_CAT_ID 133378              /* Identifier			Integer */
#define DTIF_CAT_APPL_PRIVATE 133379    /* Application private		Sequence of DTIF_NVL */
#define DTIF_CAT_GENERIC_REF 133380     /* Generic reference		Integer */
#define DTIF_CAT_DESCRIPTION 133381     /* Description			Array of character string */
#define DTIF_CAT_FORMATS 133382         /* Format information list	Sequence of DTIF_FMI */
#define DTIF_CAT_COMPUTED_BY 133383     /* Computed by expression	CFE_EXP */
#define DTIF_CAT_DEFAULT_VALUE_C 133384 /* Default value		Enumeration */
#define DTIF_CAT_DEFAULT_VALUE 133385   /*				Variable */
#define DTIF_CAT_MISSING_VALUE_C 133386 /* Missing value		Enumeration */
#define DTIF_CAT_MISSING_VALUE 133387   /*				Variable */
#define DTIF_CAT_QUERY_NAME 133388      /* Query name			Character string */
#define DTIF_CAT_COLUMN_HDR 133389      /* Column header		Character string */
#define DTIF_CAT_POSITION 133390        /* Position  			Integer		*** OBSOLETE *** */
#define DTIF_CAT_DATA_TYPE 133391       /* Data type			Enumeration */
#define DTIF_CAT_DATA_LENGTH 133392     /* Data length (bytes)		Integer */
#define DTIF_CAT_SCALE_FACTOR 133393    /* Scale factor			Integer */
#define DTIF_CAT_FLAGS 133394           /* Flags			Longword */
#define DTIF_CAT_HDR_FORMAT 133395      /* Header format		DTIF_FMI */
#define DTIF_CAT_COMPUTED_SEQ 133396    /* Computed by repeating seq.   DTIF_RSQ */
#define DTIF_CAT_MAX 133397             /* Maximum code plus 1              */
/* Values of DTIF_CAT_DEFAULT_VALUE_C, DTIF_CAT_MISSING_VALUE_C, DTIF_CLD_VALUE_C, DTIF_FMC_REL_VALUE_C. */
#define DTIF_K_CV_INTEGER 0             /* Integer			Variable integer */
#define DTIF_K_CV_LATIN1_TEXT 1         /* Latin-1 text			String */
#define DTIF_K_CV_SIMPLE_TEXT 2         /* Simple text			Character string */
#define DTIF_K_CV_DATE 3                /* Date				DTIF_DAT */
#define DTIF_K_CV_SCALED_INTEGER 4      /* Scaled integer		Scaled integer */
#define DTIF_K_CV_VTEXT 5               /* Varying text 		DTIF_VTX */
#define DTIF_K_CV_ARRAY 6               /* Array definition	     	DTIF_ARD */
#define DTIF_K_CV_COMPLEX 7             /* Complex float		DTIF_CFT */
#define DTIF_K_CV_FLOAT 8               /* Float			General floating point */
#define DTIF_K_CV_BOOLEAN 9             /* Boolean			Boolean */
#define DTIF_K_CV_COMPLEX_TEXT 10       /* Complex text			Array of character string */
#define DTIF_K_CV_DDIF_DOC 11           /* DDIF Compound document	DDIF_DDF */
#define DTIF_K_CV_DTIF_DOC 12           /* DTIF Nested table            DTIF_DTF */
#define DTIF_K_CV_RELTIME 13            /* Relative time                DTIF_RLT */
#define DTIF_K_CV_EXTERNAL_DEF 14       /* External definition		DTIF_EXT */
#define DTIF_K_CV_UNKNOWN 15            /* Unknown			Sequence of DTIF_NVL */
/* Values of DTIF_CAT_DATA_TYPE and DTIF_ROW_DATA_TYPE.		     	DTIF conforming */
#define DTIF_K_DT_UNKNOWN 0             /* Unknown                          */
#define DTIF_K_DT_WORD 1                /* Signed word integer              */
#define DTIF_K_DT_LONG 2                /* Signed longword integer          */
#define DTIF_K_DT_QUAD 3                /* Signed quadword integer          */
#define DTIF_K_DT_FFLOAT 4              /* VAX F-floating                   */
#define DTIF_K_DT_DFLOAT 5              /* VAX D-floating                   */
#define DTIF_K_DT_GFLOAT 6              /* VAX G-floating                   */
#define DTIF_K_DT_HFLOAT 7              /* VAX H-floating                   */
#define DTIF_K_DT_ABSDATE 8             /* Absolute date/time               */
#define DTIF_K_DT_TEXT 9                /* Text string                      */
#define DTIF_K_DT_VTEXT 10              /* Varying text string              */
#define DTIF_K_DT_SEGSTR 11             /* Segmented string                 */
#define DTIF_K_DT_RELTIME 12            /* Relative time                    */
#define DTIF_K_DT_DDIF_DOC 13           /* DDIF Compound document           */
#define DTIF_K_DT_DTIF_DOC 14           /* DTIF Compound document           */
#define DTIF_K_DT_IEEE_S_FLOAT 15       /* IEEE S-float                     */
#define DTIF_K_DT_IEEE_D_FLOAT 16       /* IEEE D-float                     */
#define DTIF_K_DT_IEEE_SE_FLOAT 17      /* IEEE SE-float                    */
#define DTIF_K_DT_IEEE_DE_FLOAT 18      /* IEEE DE-float                    */
/* Bit definitions for DTIF_CAT_FLAGS.					DTIF conforming */
#ifdef CDAbig_endian
#define dtif_m_cat_autorecalc 0x80000000
#else
#define dtif_m_cat_autorecalc 1
#endif
#ifdef CDAbig_endian
#define dtif_m_cat_readonly 0x40000000
#else
#define dtif_m_cat_readonly 2
#endif
#ifdef CDAbig_endian
#define dtif_m_cat_annotation 0x20000000
#else
#define dtif_m_cat_annotation 4
#endif
#ifdef CDAbig_endian
#define dtif_m_cat_hidden 0x10000000
#else
#define dtif_m_cat_hidden 8
#endif
#ifdef CDAbig_endian
#define dtif_m_cat_dimension 0x8000000
#else
#define dtif_m_cat_dimension 16
#endif
struct cat_flags {
    unsigned dtif_v_cat_autorecalc : 1; /* Auto recalculate                 */
    unsigned dtif_v_cat_readonly : 1;   /* Read only                        */
    unsigned dtif_v_cat_annotation : 1; /* Annotation                       */
    unsigned dtif_v_cat_hidden : 1;     /* Hidden                           */
    unsigned dtif_v_cat_dimension : 1;  /* Dimension                        */
    unsigned dtif_v_cat_fill_0 : 11;
    unsigned dtif_v_cat_fill_1 : 16;
    } ;
/* Item codes for Table Definition aggregate.                               */
#define DTIF_TBL_MAX_COLS 133633        /* Maximum columns		Integer */
#define DTIF_TBL_MAX_ROWS 133634        /* Maximum rows			Integer */
#define DTIF_TBL_APPL_PRIVATE 133635    /* Application private		Sequence of DTIF_NVL */
#define DTIF_TBL_METADATA 133636        /* Table metadata		DTIF_TMD */
#define DTIF_TBL_WINDOWS 133637         /* Window definitions		Sequence of DTIF_WND */
#define DTIF_TBL_ROWS 133638            /* Row data			Sequence of DTIF_ROW */
#define DTIF_TBL_MAX 133639             /* Maximum code plus 1              */
/* Item codes for Table Metadata aggregate.                                 */
#define DTIF_TMD_NAME 133889            /* Name				Array of character string */
#define DTIF_TMD_ID 133890              /* Identifier			Integer */
#define DTIF_TMD_APPL_PRIVATE 133891    /* Application private		Sequence of DTIF_NVL */
#define DTIF_TMD_DESCRIPTION 133892     /* Description			Array of character string */
#define DTIF_TMD_FLAGS 133893           /* Flags			Longword */
#define DTIF_TMD_DEFAULT_FMTS 133894    /* Default formats		Sequence of DTIF_FMI */
#define DTIF_TMD_COLUMNS 133895         /* Column definitions		Sequence of DTIF_CAT */
#define DTIF_TMD_RANGES 133896          /* Range definitions		Sequence of DTIF_RNG */
#define DTIF_TMD_SYMBOLS 133897         /* Symbol definitions		Sequence of DTIF_NVL */
#define DTIF_TMD_NUM_DIMENSIONS 133898  /* Number of dimensions		Integer */
#define DTIF_TMD_NUM_VARIABLES 133899   /* Number of variables		Integer */
#define DTIF_TMD_UNITS_PER_MEASUREMENT 133900 /* Units per measurement	Integer */
#define DTIF_TMD_UNITS_NAME 133901      /* Units name			Array of character string */
#define DTIF_TMD_MAX 133902             /* Maximum code plus 1              */
/* Bit definitions for DTIF_TMD_FLAGS.					DTIF conforming */
#ifdef CDAbig_endian
#define dtif_m_tmd_autorecalc 0x80000000
#else
#define dtif_m_tmd_autorecalc 1
#endif
#ifdef CDAbig_endian
#define dtif_m_tmd_autoresort 0x40000000
#else
#define dtif_m_tmd_autoresort 2
#endif
#ifdef CDAbig_endian
#define dtif_m_tmd_calcbycol 0x20000000
#else
#define dtif_m_tmd_calcbycol 4
#endif
#ifdef CDAbig_endian
#define dtif_m_tmd_calcbyrow 0x10000000
#else
#define dtif_m_tmd_calcbyrow 8
#endif
#ifdef CDAbig_endian
#define dtif_m_tmd_calcnatural 0x8000000
#else
#define dtif_m_tmd_calcnatural 16
#endif
#ifdef CDAbig_endian
#define dtif_m_tmd_fmtbycol 0x4000000
#else
#define dtif_m_tmd_fmtbycol 32
#endif
#ifdef CDAbig_endian
#define dtif_m_tmd_fmtbyrow 0x2000000
#else
#define dtif_m_tmd_fmtbyrow 64
#endif
struct tmd_flags {
    unsigned dtif_v_tmd_autorecalc : 1;
    unsigned dtif_v_tmd_autoresort : 1;
    unsigned dtif_v_tmd_calcbycol : 1;
    unsigned dtif_v_tmd_calcbyrow : 1;
    unsigned dtif_v_tmd_calcnatural : 1;
    unsigned dtif_v_tmd_fmtbycol : 1;
    unsigned dtif_v_tmd_fmtbyrow : 1;
    unsigned dtif_v_tmd_fill_0 : 9;
    unsigned dtif_v_tmd_fill_1 : 16;
    } ;
/* Renamed flag values introduced in BX00.                                  */
#ifdef CDAbig_endian
#define dtif_m_tmd_precbycol 0x4000000
#else
#define dtif_m_tmd_precbycol 32
#endif
#ifdef CDAbig_endian
#define dtif_m_tmd_precbyrow 0x2000000
#else
#define dtif_m_tmd_precbyrow 64
#endif
/* Item codes for Window Definition aggregate.                              */
#define DTIF_WND_NAME 134145            /* Name				Array of character string */
#define DTIF_WND_ID 134146              /* Identifier			Integer */
#define DTIF_WND_APPL_PRIVATE 134147    /* Application private		Sequence of DTIF_NVL */
#define DTIF_WND_CARDINAL_NUM 134148    /* Cardinal number		Integer */
#define DTIF_WND_DESCRIPTION 134149     /* Description			Array of character string */
#define DTIF_WND_FLAGS 134150           /* Flags			Longword */
#define DTIF_WND_FORMATS 134151         /* Format definitions		Sequence of DTIF_FMI */
#define DTIF_WND_RANGES 134152          /* Range definitions		Sequence of DTIF_RNG */
#define DTIF_WND_ACTIVE_LOC 134153      /* Active location		DTIF_CCD */
#define DTIF_WND_MAX 134154             /* Maximum code plus 1              */
/* Bit definitions for DTIF_WND_FLAGS.					DTIF conforming */
#ifdef CDAbig_endian
#define dtif_m_wnd_active 0x80000000
#else
#define dtif_m_wnd_active 1
#endif
#ifdef CDAbig_endian
#define dtif_m_wnd_hidden 0x40000000
#else
#define dtif_m_wnd_hidden 2
#endif
#ifdef CDAbig_endian
#define dtif_m_wnd_formula_hidden 0x20000000
#else
#define dtif_m_wnd_formula_hidden 4
#endif
#ifdef CDAbig_endian
#define dtif_m_wnd_value_hidden 0x10000000
#else
#define dtif_m_wnd_value_hidden 8
#endif
#ifdef CDAbig_endian
#define dtif_m_wnd_colhdr_hidden 0x8000000
#else
#define dtif_m_wnd_colhdr_hidden 16
#endif
#ifdef CDAbig_endian
#define dtif_m_wnd_rowhdr_hidden 0x4000000
#else
#define dtif_m_wnd_rowhdr_hidden 32
#endif
#ifdef CDAbig_endian
#define dtif_m_wnd_lines_hidden 0x2000000
#else
#define dtif_m_wnd_lines_hidden 64
#endif
struct wnd_flags {
    unsigned dtif_v_wnd_active : 1;
    unsigned dtif_v_wnd_hidden : 1;
    unsigned dtif_v_wnd_formula_hidden : 1;
    unsigned dtif_v_wnd_value_hidden : 1;
    unsigned dtif_v_wnd_colhdr_hidden : 1;
    unsigned dtif_v_wnd_rowhdr_hidden : 1;
    unsigned dtif_v_wnd_lines_hidden : 1;
    unsigned dtif_v_wnd_fill_0 : 9;
    unsigned dtif_v_wnd_fill_1 : 16;
    } ;
/* Item codes for Row Definition aggregate.                                 */
#define DTIF_ROW_NUM 134401             /* Row number			Integer */
#define DTIF_ROW_APPL_PRIVATE 134402    /* Application private		Sequence of DTIF_NVL */
#define DTIF_ROW_FORMATS 134403         /* Format definitions		Sequence of DTIF_FMI */
#define DTIF_ROW_FLAGS 134404           /* Flags			Longword */
#define DTIF_ROW_CELLS 134405           /* Cell data		     	Sequence of DTIF_CLD */
#define DTIF_ROW_ROW_HDR 134406         /* Row header			Array of character string */
#define DTIF_ROW_HDR_FORMAT 134407      /* Row header format		DTIF_FMI */
#define DTIF_ROW_DATA_TYPE 134408       /* Row data type		Enumeration */
#define DTIF_ROW_COMPUTED_BY 134409     /* Computed by expression	CFE_EXP */
#define DTIF_ROW_COMPUTED_SEQ 134410    /* Computed by repeating seq.	DTIF_RSQ */
#define DTIF_ROW_MAX 134411             /* Maximum code plus 1              */
/* Bit definitions for DTIF_ROW_FLAGS.					DTIF conforming */
#ifdef CDAbig_endian
#define dtif_m_row_annotation 0x80000000
#else
#define dtif_m_row_annotation 1
#endif
#ifdef CDAbig_endian
#define dtif_m_row_hidden 0x40000000
#else
#define dtif_m_row_hidden 2
#endif
struct row_flags {
    unsigned dtif_v_row_annotation : 1;
    unsigned dtif_v_row_hidden : 1;
    unsigned dtif_v_row_fill_0 : 14;
    unsigned dtif_v_row_fill_1 : 16;
    } ;
/* Item codes for Cell Data aggregate.                                      */
#define DTIF_CLD_COL_NUM 134657         /* Column number		Integer */
#define DTIF_CLD_STATE 134658           /* State			Enumeration */
#define DTIF_CLD_DESCRIPTION 134659     /* Description			Array of character string */
#define DTIF_CLD_APPL_PRIVATE 134660    /* Application private		Sequence of DTIF_NVL */
#define DTIF_CLD_FORMATS 134661         /* Format definitions		Sequence of DTIF_FMI */
#define DTIF_CLD_VALUE_C 134662         /* Cell value			Enumeration */
#define DTIF_CLD_VALUE 134663           /*				Variable */
#define DTIF_CLD_FORMULA_CFE 134664     /* Cell formula			CFE_EXP */
#define DTIF_CLD_MAX 134665             /* Maximum code plus 1              */
/* Values of DTIF_CLD_STATE, DTIF_FMC_STATE.		    		DTIF conforming */
#define DTIF_K_CS_ISVALUE 0
#define DTIF_K_CS_ISNULL 1
#define DTIF_K_CS_ISERROR 2
#define DTIF_K_CS_ISNOVALUE 3
#define DTIF_K_CS_ISUNDERFLOW 10
#define DTIF_K_CS_ISOVERFLOW 11
#define DTIF_K_CS_ISUNDEFREF 12
#define DTIF_K_CS_ISDIVZERO 13
#define DTIF_K_CS_ISRECURSIVE 14
#define DTIF_K_CS_ISMISEXTREF 15
#define DTIF_K_CS_ISNOTNUMBER 16
/* Item codes for Varying Text aggregate.                                   */
#define DTIF_VTX_VTEXT_LEN 134913       /* Varying text length		Integer */
#define DTIF_VTX_VTEXT_STR 134914       /* Varying text string		Character string */
#define DTIF_VTX_MAX 134915             /* Maximum code plus 1              */
/* Item codes for Array Definition aggregate.                               */
#define DTIF_ARD_DESCRIPTION 135169     /* Description			String */
#define DTIF_ARD_ELEM_TYPE_SIZE_C 135170 /* Array element type size	Enumeration */
#define DTIF_ARD_ELEM_TYPE_SIZE 135171  /*				Variable */
#define DTIF_ARD_X_DIMENSION 135172     /* X dimension			Integer */
#define DTIF_ARD_Y_DIMENSION 135173     /* Y dimension			Integer */
#define DTIF_ARD_Z_DIMENSION 135174     /* Z dimension			Integer */
#define DTIF_ARD_VALUES 135175          /* Values			String */
#define DTIF_ARD_MAX 135176             /* Maximum code plus 1              */
/* Values of DTIF_ARD_ELEM_TYPE_SIZE_C.                                     */
#define DTIF_K_STD_TYPE 0               /* Standard type size		Enumeration */
#define DTIF_K_VAR_TYPE 1               /* Variable type size		Integer */
/* Values of DTIF_ARD_ELEM_TYPE_SIZE for DTIFK_STD_TYPE.		DTIF conforming */
#define DTIF_K_ELEM_WORD 0              /* Word                             */
#define DTIF_K_ELEM_LONG 1              /* Longword                         */
#define DTIF_K_ELEM_FFLOAT 2            /* VAX F-floating                   */
#define DTIF_K_ELEM_DFLOAT 3            /* VAX D-floating                   */
#define DTIF_K_ELEM_GFLOAT 4            /* VAX G-floating                   */
#define DTIF_K_ELEM_HFLOAT 5            /* VAX H-floating                   */
/* Item codes for Complex Float aggregate.                                  */
#define DTIF_CFT_REAL_PART 135425       /* Real part			General floating point */
#define DTIF_CFT_IMAGINARY_PART 135426  /* Imaginary part 		General floating point */
#define DTIF_CFT_MAX 135427             /* Maximum code plus 1              */
/* Item codes for Format Information aggregate.                             */
#define DTIF_FMI_WINDOW_ID 135681       /* Window ID			Integer */
#define DTIF_FMI_C 135682               /* Format choice		Enumeration */
#define DTIF_FMI_NUM_DATATYPE 135683    /* Numeric data type		Longword */
#define DTIF_FMI_NUM_C 135684           /* Numeric format		Enumeration */
#define DTIF_FMI_NUMSTD_TYPE 135685     /* Numeric standard type	Enumeration */
#define DTIF_FMI_NUMSTD_DIGITS 135686   /* Numeric standard digits	Integer */
#define DTIF_FMI_NUMSTD_FRAC 135687     /* Numeric standard fraction	Integer */
#define DTIF_FMI_NUMEDS_EDITSTR 135688  /* Numeric edit string		ESF_EDS */
#define DTIF_FMI_NUMEID_EDITSTR_ID 135689 /* Numeric edit string index	Integer */
#define DTIF_FMI_NUM_RNDTRUNC 135690    /* Numeric rounding		Enumeration */
#define DTIF_FMI_TXT_C 135691           /* Text format			Enumeration */
#define DTIF_FMI_TXTSTD_TYPE 135692     /* Text standard type		Enumeration */
#define DTIF_FMI_TXTEDS_EDITSTR 135693  /* Text edit string		ESF_EDS */
#define DTIF_FMI_TXTEID_EDITSTR_ID 135694 /* Text edit string index	Integer */
#define DTIF_FMI_DAT_C 135695           /* Date format			Enumeration */
#define DTIF_FMI_DATSTD_TYPE 135696     /* Date standard type		Enumeration */
#define DTIF_FMI_DATSTD_ORDER 135697    /* Date standard order		Enumeration */
#define DTIF_FMI_DATEDS_EDITSTR 135698  /* Date edit string		ESF_EDS */
#define DTIF_FMI_DATEID_EDITSTR_ID 135699 /* Date edit string index	Integer */
#define DTIF_FMI_FLAGS 135700           /* Flags			Longword */
#define DTIF_FMI_WIDTH 135701           /* Width			Integer */
#define DTIF_FMI_LANG_ID 135702         /* Language index		Integer */
#define DTIF_FMI_DIRECTION 135703       /* Direction			Enumeration */
#define DTIF_FMI_UNIT_DESC 135704       /* Units description		Array of character string */
#define DTIF_FMI_ALIGNMENT 135705       /* Alignment			Enumeration */
#define DTIF_FMI_BORDER 135706          /* Border			Longword */
#define DTIF_FMI_NUM_SCALE 135707       /* Numeric scale		Integer */
#define DTIF_FMI_CONDITION 135708       /* Condition			DTIF_FMC */
#define DTIF_FMI_FONT 135709            /* Font				Integer */
#define DTIF_FMI_TEXT_HEIGHT_C 135710   /* Text height			Measurement enumeration  */
#define DTIF_FMI_TEXT_HEIGHT 135711     /*				Variable */
#define DTIF_FMI_FOREGROUND 135712      /* Foreground pattern		Integer */
#define DTIF_FMI_BACKGROUND 135713      /* Background pattern		Integer */
#define DTIF_FMI_WIDTH_SIZE_C 135714    /* Width size			Measurement enumeration  */
#define DTIF_FMI_WIDTH_SIZE 135715      /*				Variable */
#define DTIF_FMI_HEIGHT_SIZE_C 135716   /* Height size			Measurement enumeration  */
#define DTIF_FMI_HEIGHT_SIZE 135717     /*				Variable */
#define DTIF_FMI_HEIGHT_LINES 135718    /* Height lines			Integer */
#define DTIF_FMI_MAX 135719             /* Maximum code plus 1              */
/* Values of DTIF_FMI_C.                                                    */
#define DTIF_K_NUMERIC_FORMAT 0         /* Numeric format		DTIF_FMI_NUM_DATATYPE to DTIF_FMI_NUM_RNDTRUNC, */
/*				and DTIF_FMI_NUM_SCALE                      */
#define DTIF_K_TEXT_FORMAT 1            /* Text format			DTIF_FMI_TXT_C to DTIF_FMI_TXTEID_EDITSTR_ID */
#define DTIF_K_DATE_FORMAT 2            /* Date format			DTIF_FMI_DAT_C to DTIF_FMI_DATEID_EDITSTR_ID */
/* Bit definitions for DTIF_FMI_NUM_DATATYPE.				DTIF conforming */
#ifdef CDAbig_endian
#define dtif_m_fmi_num_all 0x80000000
#else
#define dtif_m_fmi_num_all 1
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_num_integer 0x40000000
#else
#define dtif_m_fmi_num_integer 2
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_num_float 0x20000000
#else
#define dtif_m_fmi_num_float 4
#endif
struct fmi_num_datatype {
    unsigned dtif_v_fmi_num_all : 1;
    unsigned dtif_v_fmi_num_integer : 1;
    unsigned dtif_v_fmi_num_float : 1;
    unsigned dtif_v_fmi_fill_0 : 13;
    unsigned dtif_v_fmi_fill_1 : 16;
    } ;
/* Values of DTIF_FMI_NUM_C.                                                */
#define DTIF_K_NUM_STANDARD 0           /* Numeric standard format	DTIF_FMI_NUMSTD_TYPE to DTIF_FMI_NUMSTD_FRAC */
#define DTIF_K_NUM_EDITSTR 1            /* Numeric edit string		DTIF_FMI_NUMEDS_EDITSTR */
#define DTIF_K_NUM_EDITSTR_ID 2         /* Numeric edit string index	DTIF_FMI_NUMEID_EDITSTR_ID */
/* Values of DTIF_FMI_NUMSTD_TYPE.					DTIF conforming */
#define DTIF_K_NUMSTD_GENERAL 0         /* General format                   */
#define DTIF_K_NUMSTD_INTEGER 1         /* Integer format                   */
#define DTIF_K_NUMSTD_FIXEDPT 2         /* Fixed point format               */
#define DTIF_K_NUMSTD_SCIENTIFIC 3      /* Scientific format                */
#define DTIF_K_NUMSTD_MONEY 4           /* Money format                     */
#define DTIF_K_NUMSTD_COMMA 5           /* Comma format                     */
#define DTIF_K_NUMSTD_PERCENT 6         /* Percent format                   */
#define DTIF_K_NUMSTD_PHONE 7           /* Phone format                     */
#define DTIF_K_NUMSTD_BAR 8             /* Bar format                       */
#define DTIF_K_NUMSTD_TEXT 9            /* Text format                      */
#define DTIF_K_NUMSTD_PERCENT_NOSCALE 10 /* Percent, no scale               */
/* Values of DTIF_FMI_NUM_RNDTRUNC.					DTIF conforming */
#define DTIF_K_NUM_ROUND 0              /* Round                            */
#define DTIF_K_NUM_TRUNCATE 1           /* Truncate                         */
/* Values of DTIF_FMI_TXT_C.                                                */
#define DTIF_K_TXT_STANDARD 0           /* Text standard format		DTIF_FMI_TXTSTD_TYPE */
#define DTIF_K_TXT_EDITSTR 1            /* Text edit string		DTIF_FMI_TXTEDS_EDITSTR */
#define DTIF_K_TXT_EDITSTR_ID 2         /* Text edit string index	DTIF_FMI_TXTEID_EDITSTR_ID */
/* Values of DTIF_FMI_TXTSTD_TYPE.					DTIF conforming */
#define DTIF_K_TXTSTD_PHONE 0           /* Telephone                        */
#define DTIF_K_TXTSTD_TEXT 1            /* Text                             */
#define DTIF_K_TXTSTD_REPEAT 2          /* Repeat                           */
/* Values of DTIF_FMI_DAT_C.                                                */
#define DTIF_K_DAT_STANDARD 0           /* Date standard format		DTIF_FMI_DATSTD_TYPE to DTIF_FMI_DATSTD_ORDER */
#define DTIF_K_DAT_EDITSTR 1            /* Date edit string		DTIF_FMI_DATEDS_EDITSTR */
#define DTIF_K_DAT_EDITSTR_ID 2         /* Date edit string index	DTIF_FMI_DATEID_EDITSTR_ID */
/* Values of DTIF_FMI_DATSTD_TYPE.					DTIF conforming */
#define DTIF_K_DATSTD_DATEONLY 0        /* Date only                        */
#define DTIF_K_DATSTD_TIMEONLY 1        /* Time only                        */
#define DTIF_K_DATSTD_DATEANDTIME 2     /* Date and time                    */
#define DTIF_K_DATSTD_RELYEARMONTH 3    /* Relative, year and month         */
#define DTIF_K_DATSTD_RELDAYTIME 4      /* Relative, day and time           */
#define DTIF_K_DATSTD_RELFULLDATE 5     /* Relative, full date              */
/* Values of DTIF_FMI_DATSTD_ORDER.					DTIF conforming */
#define DTIF_K_DATSTD_MDY 0             /* Month day year                   */
#define DTIF_K_DATSTD_DMY 1             /* Day month year                   */
/* Bit definitions for DTIF_FMI_FLAGS.					DTIF conforming */
#ifdef CDAbig_endian
#define dtif_m_fmi_readonly 0x80000000
#else
#define dtif_m_fmi_readonly 1
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_noreadonly 0x40000000
#else
#define dtif_m_fmi_noreadonly 2
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_bold 0x20000000
#else
#define dtif_m_fmi_bold 4
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_nobold 0x10000000
#else
#define dtif_m_fmi_nobold 8
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_italic 0x8000000
#else
#define dtif_m_fmi_italic 16
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_noitalic 0x4000000
#else
#define dtif_m_fmi_noitalic 32
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_underline 0x2000000
#else
#define dtif_m_fmi_underline 64
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_nounderline 0x1000000
#else
#define dtif_m_fmi_nounderline 128
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_valuehidden 0x800000
#else
#define dtif_m_fmi_valuehidden 256
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_novaluehidden 0x400000
#else
#define dtif_m_fmi_novaluehidden 512
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_formulahidden 0x200000
#else
#define dtif_m_fmi_formulahidden 1024
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_noformulahidden 0x100000
#else
#define dtif_m_fmi_noformulahidden 2048
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_running 0x80000
#else
#define dtif_m_fmi_running 4096
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_norunning 0x40000
#else
#define dtif_m_fmi_norunning 8192
#endif
struct fmi_flags {
    unsigned dtif_v_fmi_readonly : 1;
    unsigned dtif_v_fmi_noreadonly : 1;
    unsigned dtif_v_fmi_bold : 1;
    unsigned dtif_v_fmi_nobold : 1;
    unsigned dtif_v_fmi_italic : 1;
    unsigned dtif_v_fmi_noitalic : 1;
    unsigned dtif_v_fmi_underline : 1;
    unsigned dtif_v_fmi_nounderline : 1;
    unsigned dtif_v_fmi_valuehidden : 1;
    unsigned dtif_v_fmi_novaluehidden : 1;
    unsigned dtif_v_fmi_formulahidden : 1;
    unsigned dtif_v_fmi_noformulahidden : 1;
    unsigned dtif_v_fmi_running : 1;
    unsigned dtif_v_fmi_norunning : 1;
    unsigned dtif_v_fmi_fill_00 : 2;
    unsigned dtif_v_fmi_fill_2 : 16;
    } ;
/* Values of DTIF_FMI_DIRECTION.					DTIF conforming */
#define DTIF_K_DIR_OPPOSITE 0           /* Opposite direction               */
/* Values of DTIF_FMI_ALIGNMENT.					DTIF conforming */
#define DTIF_K_ALIGN_LEFT 0             /* Left alignment                   */
#define DTIF_K_ALIGN_CENTER 1           /* Center alignment                 */
#define DTIF_K_ALIGN_RIGHT 2            /* Right alignment                  */
/* Bit definitions for DTIF_FMI_BORDER.				DTIF conforming */
#ifdef CDAbig_endian
#define dtif_m_fmi_border_left 0x80000000
#else
#define dtif_m_fmi_border_left 1
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_border_noleft 0x40000000
#else
#define dtif_m_fmi_border_noleft 2
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_border_top 0x20000000
#else
#define dtif_m_fmi_border_top 4
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_border_notop 0x10000000
#else
#define dtif_m_fmi_border_notop 8
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_border_right 0x8000000
#else
#define dtif_m_fmi_border_right 16
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_border_noright 0x4000000
#else
#define dtif_m_fmi_border_noright 32
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_border_bottom 0x2000000
#else
#define dtif_m_fmi_border_bottom 64
#endif
#ifdef CDAbig_endian
#define dtif_m_fmi_border_nobottom 0x1000000
#else
#define dtif_m_fmi_border_nobottom 128
#endif
struct fmi_border {
    unsigned dtif_v_fmi_border_left : 1;
    unsigned dtif_v_fmi_border_noleft : 1;
    unsigned dtif_v_fmi_border_top : 1;
    unsigned dtif_v_fmi_border_notop : 1;
    unsigned dtif_v_fmi_border_right : 1;
    unsigned dtif_v_fmi_border_noright : 1;
    unsigned dtif_v_fmi_border_bottom : 1;
    unsigned dtif_v_fmi_border_nobottom : 1;
    unsigned dtif_v_fmi_fill_000 : 8;
    unsigned dtif_v_fmi_fill_3 : 16;
    } ;
/* Item codes for Cell Coordinates aggregate.                               */
#define DTIF_CCD_ROW 135937             /* Row number			Integer */
#define DTIF_CCD_COLUMN 135938          /* Column number		Integer */
#define DTIF_CCD_FLAGS 135939           /* Flags			Enumeration */
#define DTIF_CCD_MAX 135940             /* Maximum code plus 1              */
/* Values of DTIF_CCD_FLAGS.						DTIF conforming */
#define DTIF_K_RELROW_RELCOL 0          /* Relative row, relative column    */
#define DTIF_K_RELROW_ABSCOL 1          /* Relative row, absolute column    */
#define DTIF_K_ABSROW_RELCOL 2          /* Absolute row, relative column    */
#define DTIF_K_ABSROW_ABSCOL 3          /* Absolute row, absolute column    */
/* Item codes for Range Definition aggregate.                               */
#define DTIF_RNG_NAME 136193            /* Name				Array of character string */
#define DTIF_RNG_TYPE 136194            /* Type				Enumeration */
#define DTIF_RNG_REGION 136195          /* Region			Sequence of DTIF_CLR, DTIF_RWR, DTIF_COR, DTIF_NMR, */
/*				            DTIF_ECR, DTIF_ENR              */
#define DTIF_RNG_SORT_KEYNUM 136196     /* Sort key number		Integer */
#define DTIF_RNG_DESCRIPTION 136197     /* Description			Array of character string */
#define DTIF_RNG_SORT_DIRECTION 136198  /* Sort direction		Enumeration */
#define DTIF_RNG_SORT_ORDER 136199      /* Sort order			Enumeration */
#define DTIF_RNG_MAX 136200             /* Maximum code plus 1              */
/* Values of DTIF_RNG_TYPE.						DTIF conforming */
#define DTIF_K_RT_NAMED_RANGE 0         /* Named area                       */
#define DTIF_K_RT_VIEW_RANGE 1          /* View definition                  */
#define DTIF_K_RT_COL_TITLE 2           /* Column title section             */
#define DTIF_K_RT_ROW_TITLE 3           /* Row title section                */
#define DTIF_K_RT_DISPLAY_DATA 4        /* Displayed window range           */
#define DTIF_K_RT_DATA_RANGE 5          /* Maximum window range             */
#define DTIF_K_RT_SORT_RANGE 6          /* Sort range                       */
#define DTIF_K_RT_SORT_KEY 7            /* Sort key                         */
/* Values of DTIF_RNG_SORT_DIRECTION.					DTIF conforming */
#define DTIF_K_ASCENDING 0              /* Sort ascending                   */
#define DTIF_K_DESCENDING 1             /* Sort descending                  */
/* Values of DTIF_RNG_SORT_ORDER.					DTIF conforming */
#define DTIF_K_ROW_MAJOR 0              /* Row major                        */
#define DTIF_K_COL_MAJOR 1              /* Column major                     */
/* Item codes for Cell Range aggregate.                                     */
#define DTIF_CLR_RANGE_BEGIN 136449     /* Beginning cell coordinates	DTIF_CCD */
#define DTIF_CLR_RANGE_END 136450       /* Ending cell coordinates	DTIF_CCD */
#define DTIF_CLR_MAX 136451             /* Maximum code plus 1              */
/* Item codes for Row Range aggregate.                                      */
#define DTIF_RWR_ROW_BEGIN 136705       /* Beginning row number		Integer */
#define DTIF_RWR_ROW_END 136706         /* Ending row number		Integer */
#define DTIF_RWR_MAX 136707             /* Maximum code plus 1              */
/* Item codes for Column Range aggregate.                                   */
#define DTIF_COR_COL_BEGIN 136961       /* Beginning column number	Integer */
#define DTIF_COR_COL_END 136962         /* Ending column number		Integer */
#define DTIF_COR_MAX 136963             /* Maximum code plus 1              */
/* Item codes for Named Range aggregate.                                    */
#define DTIF_NMR_NAMEDRANGE 137217      /* Named range			Array of character string */
#define DTIF_NMR_MAX 137218             /* Maximum code plus 1              */
/* Item codes for External aggregate.                                       */
#define DTIF_EXT_DIRECT_REFERENCE 137473 /* Direct reference		Object identifier */
#define DTIF_EXT_INDIRECT_REFERENCE 137474 /* Indirect reference		Integer */
#define DTIF_EXT_DATA_VALUE_DESCRIPTOR 137475 /* Data value descriptor	String */
#define DTIF_EXT_ENCODING_C 137476      /* Encoding			Enumeration */
#define DTIF_EXT_ENCODING 137477        /* 				Variable */
#define DTIF_EXT_ENCODING_L 137478      /*     Length (on input)	Integer */
#define DTIF_EXT_MAX 137479             /* Maximum code plus 1              */
/* Values of DTIF_EXT_ENCODING_C.                                           */
#define DTIF_K_DOCUMENT_ENCODING 0      /* Nested document		Document root aggregate */
#define DTIF_K_DDIS_ENCODING 1          /* Nested document		DDIS encoding */
#define DTIF_K_OCTET_ENCODING 2         /* Octet aligned		String */
#define DTIF_K_ARBITRARY_ENCODING 3     /* Arbitrary		 	Bit string */
/* Item codes for Repeat Sequence aggregate.                                */
#define DTIF_RSQ_SEQUENCE 137729        /* Sequence repetitions	   	Integer */
#define DTIF_RSQ_EACH_ELEM 137730       /* Element repetitions		Integer */
#define DTIF_RSQ_ELEM_LIST_C 137731     /* Element list			Enumeration */
#define DTIF_RSQ_NESTED 137732          /* Nested sequence		DTIF_RSQ */
#define DTIF_RSQ_VALUES_COUNT 137733    /* Values count			Integer */
#define DTIF_RSQ_VALUES_LIST_C 137734   /* Values list			Array of enumeration */
#define DTIF_RSQ_VALUES_LIST 137735     /*				Array of variable */
#define DTIF_RSQ_SERIES_START_C 137736  /* Series start value		Enumeration */
#define DTIF_RSQ_SERIES_START 137737    /*				Variable */
#define DTIF_RSQ_SERIES_INCR_C 137738   /* Series increment value	Enumeration */
#define DTIF_RSQ_SERIES_INCR 137739     /* 			    	Variable */
#define DTIF_RSQ_SERIES_STOP_C 137740   /* Series stop			Enumeration */
#define DTIF_RSQ_SERIES_END_C 137741    /* Series end value		Enumeration */
#define DTIF_RSQ_SERIES_END 137742      /*				Variable */
#define DTIF_RSQ_SERIES_COUNT 137743    /* Series count			Integer */
#define DTIF_RSQ_MAX 137744
/* Value of DTIF_RSQ_ELEM_LIST_C.                                           */
#define DTIF_K_NESTED 0                 /* Nested sequence.		DTIF_RSQ_NESTED */
#define DTIF_K_VALUES 1                 /* Count			DTIF_RSQ_VALUES_COUNT to DTIF_RSQ_VALUES_LIST */
#define DTIF_K_SERIES 2                 /* Series			DTIF_RSQ_SERIES_START_C to DTIF_RSQ_SERIES_COUNT */
/* Value of DTIF_RSQ_VALUES_LIST_C.                                         */
#define DTIF_K_EXPRESSION 0             /* Expression			CFE_EXP */
#define DTIF_K_NULL_EXPRESSION 1        /* None				None */
/* Value of DTIF_RSQ_SERIES_START_C, DTIF_RSQ_SERIES_INCR_C, AND DTIF_RSQ_SERIES_END_C.	  DTIF conforming */
#define DTIF_K_SR_INTEGER 0
#define DTIF_K_SR_FLOATING_POINT 1
#define DTIF_K_SR_SCALED_INTEGER 2
/* Value of DTIF_RSQ_SERIES_STOP_C.                                         */
#define DTIF_K_END_VALUE 0              /* Series ending value              */
#define DTIF_K_COUNT 1                  /* Series ending count              */
/* Item codes for Format Condition aggregate.                               */
#define DTIF_FMC_CONDITION_C 137985     /* Condition choice		Enumeration */
#define DTIF_FMC_REL_OPR 137986         /* Relation operator		Enumeration */
#define DTIF_FMC_REL_VALUE_C 137987     /* Relation value		Enumeration */
#define DTIF_FMC_REL_VALUE 137988       /* 				Variable */
#define DTIF_FMC_CELL_STATE 137989      /* Cell state			Enumeration */
#define DTIF_FMC_OTHER_EXPRESSION 137990 /* Expression			CFE_EXP */
#define DTIF_FMC_MAX 137991
/* Values of DTIF_FMC_CONDITION_C.                                          */
#define DTIF_K_RELATION 0               /* Relation			DTIF_FMC_REL_OPR to DTIF_FMC_VALUE */
#define DTIF_K_STATE 1                  /* Cell state			DTIF_FMC_CELL_STATE */
#define DTIF_K_OTHER_EXPRESSION 2       /* Other expression		DTIF_FMC_OTHER_EXPRESSION */
/* Values of DTIF_FMC_REL_OPR.						DTIF conforming */
#define DTIF_K_IS_GREATER 0
#define DTIF_K_IS_GREATER_OR_EQUAL 1
#define DTIF_K_IS_LESS 2
#define DTIF_K_IS_LESS_OR_EQUAL 3
#define DTIF_K_IS_EQUAL 4
#define DTIF_K_IS_NOT_EQUAL 5
/* Item codes for Relative Time aggregate.                                  */
#define DTIF_RLT_YEAR_MONTH 138241      /* Year and month		Integer */
#define DTIF_RLT_DAY_TIME 138242        /* Day and time			Integer */
#define DTIF_RLT_MAX 138243
/* Item codes for External Cell Coordinates aggregate.                      */
#define DTIF_ECC_TABLE_REF 138497       /* Table reference		Integer */
#define DTIF_ECC_TABLE_ID 138498        /* Table ID			Integer */
#define DTIF_ECC_ROW_C 138499           /* Row				Enumeration */
#define DTIF_ECC_ROW 138500             /*				Variable */
#define DTIF_ECC_COL_C 138501           /* Column			Enumeration */
#define DTIF_ECC_COL 138502             /*				Variable */
#define DTIF_ECC_MAX 138503
/* Values of DTIF_ECC_ROW_C and DTIF_ECC_COL_C.				DTIF defined */
#define DTIF_K_ABSOLUTE 0               /* Absolute                         */
#define DTIF_K_RELATIVE 1               /* Relative                         */
#define DTIF_K_OFFSET 2                 /* Offset                           */
/* Item codes for External Cell Range aggregate.                            */
#define DTIF_ECR_RANGE_BEGIN 138753     /* Range begin			DTIF_ECC */
#define DTIF_ECR_RANGE_END 138754       /* Range end			DTIF_ECC */
#define DTIF_ECR_MAX 138755
/* Item codes for External Named Range aggregate.                           */
#define DTIF_ENR_TABLE_REF 139009       /* Table reference		Integer */
#define DTIF_ENR_TABLE_ID 139010        /* Table ID			Integer */
#define DTIF_ENR_RANGE_NAME 139011      /* Range name			Array of character string */
#define DTIF_ENR_MAX 139012
/* Item codes for Reference aggregate.                                      */
#define DTIF_REF_TARGET 139265          /* Reference target		String */
#define DTIF_REF_INDEX 139266           /* Reference index		Integer */
#define DTIF_REF_MAX 139267
/* Aggregate type codes for ESF (Edit String Format).                       */
#define ESF_EDS 769                     /* Edit string                      */
#define ESF_RPT 770                     /* Repeat                           */
#define ESF_TXS 771                     /* Text string                      */
#define ESF_NVL 772                     /* Named value                      */
#define ESF_DAT 773                     /* Date and time                    */
#define ESF_EXT 774                     /* External                         */
#define ESF_MAX 775                     /* Maximum code plus 1              */
/* Item codes for all aggregates.  ESF_AGGREGATE_TYPE is read-only.         */
#define ESF_USER_CONTEXT 1              /* User context			Longword */
#define ESF_AGGREGATE_TYPE 2            /* Aggregate type code		Word */
#define ESF_ALL_MAX 3                   /* Maximum code plus 1              */
/* Item codes for Edit String aggregate.                                    */
#define ESF_EDS_MAJOR_VERSION 196865    /* Major version		Integer */
#define ESF_EDS_MINOR_VERSION 196866    /* Minor version		Integer */
#define ESF_EDS_EDIT_STRING_C 196867    /* Edit string			Array of enumeration */
#define ESF_EDS_EDIT_STRING 196868      /*				Array of variable */
#define ESF_EDS_MAX 196869              /* Maximum code plus 1              */
/* Current values for major and minor encoding version.  Should be omitted when the edit string is embedded in a DTIF document. */
#define ESF_K_MAJOR_VERSION 1
#define ESF_K_MINOR_VERSION 4
/* Values of ESF_EDS_EDIT_STRING_C and ESF_RPT_SEQ_C.                       */
#define ESF_K_EDS_ALPHABETIC 0          /* Alphabetic			None */
#define ESF_K_EDS_AM_PM 1               /* AM PM			None */
#define ESF_K_EDS_ANY_CHAR 2            /* Any character		None */
#define ESF_K_EDS_ANY_CASE 3            /* Any case			None */
#define ESF_K_EDS_BINARY_DIGIT 4        /* Binary digit			None */
#define ESF_K_EDS_DIGIT_SEP 5           /* Digit separator		None */
#define ESF_K_EDS_DAY_NUMBER 6          /* Day number			None */
#define ESF_K_EDS_DECIMAL_DIGIT 7       /* Decimal digit		None */
#define ESF_K_EDS_RADIX_POINT 8         /* Radix point			None */
#define ESF_K_EDS_ENCODED_MINUS 9       /* Encoded minus		None */
#define ESF_K_EDS_ENCODED_PLUS 10       /* Encoded plus			None */
#define ESF_K_EDS_ENCODED_SIGN 11       /* Encoded sign			None */
#define ESF_K_EDS_EXPONENT 12           /* Exponent			None */
#define ESF_K_EDS_ZERO_REPLACE 13       /* Zero replace			ESF_TXS */
#define ESF_K_EDS_CURRENCY 14           /* Currency			None */
#define ESF_K_EDS_MINUS 15              /* Minus			None */
#define ESF_K_EDS_PLUS 16               /* Plus				None */
#define ESF_K_EDS_SIGN 17               /* Sign				None */
#define ESF_K_EDS_FLOAT_BLANK_SUPR 18   /* Float blank suppress		None */
#define ESF_K_EDS_FRACTION_SECOND 19    /* Fraction second		None */
#define ESF_K_EDS_HEX_DIGIT 20          /* Hex digit			None */
#define ESF_K_EDS_HOUR_12 21            /* Hour (12 hour system)	None */
#define ESF_K_EDS_HOUR_24 22            /* Hour (24 hour system)	None */
#define ESF_K_EDS_JULIAN_DIGIT 23       /* Julian digit			None */
#define ESF_K_EDS_LOGICAL_CHAR 24       /* Logical character		None */
#define ESF_K_EDS_LONG_TEXT 25          /* Long text			None */
#define ESF_K_EDS_LOWERCASE 26          /* Lowercase			None */
#define ESF_K_EDS_MINUS_LITERAL 27      /* Minus literal begin		ESF_TXS */
#define ESF_K_EDS_MINUS_LIT_END 28      /* Minus literal end		ESF_TXS */
#define ESF_K_EDS_MINUTE 29             /* Minute			None */
#define ESF_K_EDS_MONTH_NAME 30         /* Month name			None */
#define ESF_K_EDS_MONTH_NUMBER 31       /* Month number			None */
#define ESF_K_EDS_OCTAL_DIGIT 32        /* Octal digit			None */
#define ESF_K_EDS_PLUS_LITERAL 33       /* Plus literal			ESF_TXS */
#define ESF_K_EDS_REVERSE 34            /* Reverse			None */
#define ESF_K_EDS_SECOND 35             /* Second			None */
#define ESF_K_EDS_STR_LITERAL 36        /* String literal		ESF_TXS */
#define ESF_K_EDS_MISSING_SEP 37        /* Missing separator		None */
#define ESF_K_EDS_UPPERCASE 38          /* Uppercase			None */
#define ESF_K_EDS_WEEKDAYNAME 39        /* Weekday name			None */
#define ESF_K_EDS_YEAR 40               /* Year				None */
#define ESF_K_EDS_APPL_PRIVATE 41       /* Application private		Sequence of ESF_NVL */
#define ESF_K_EDS_DIGIT_SEP_LIT 42      /* Digit separator literal	ESF_TXS */
#define ESF_K_EDS_RADIX_POINT_LIT 43    /* Radix point literal		ESF_TXS */
#define ESF_K_EDS_CURRENCY_LIT 44       /* Currency sign literal	ESF_TXS */
#define ESF_K_EDS_REPEAT 45             /* Repeat			ESF_RPT (not for ESF_RPT_SEQ_C) */
#define ESF_K_EDS_DAY_ABBREV_NAME 46    /* Day abbreviated name		None */
#define ESF_K_EDS_MONTH_ABBREV_NAME 47  /* Month abbreviated name	None */
#define ESF_K_EDS_YEAR_SEP 48           /* Year separator		None */
#define ESF_K_EDS_MONTH_SEP 49          /* Month separator		None */
#define ESF_K_EDS_DAY_SEP 50            /* Day separator		None */
#define ESF_K_EDS_HOUR_SEP 51           /* Hour separator		None */
#define ESF_K_EDS_MINUTE_SEP 52         /* Minute separator		None */
#define ESF_K_EDS_SECOND_SEP 53         /* Second separator		None */
#define ESF_K_EDS_FRACTION_SECOND_SEP 54 /* Fractional sec. separator	None */
/* Item codes for Repeat aggregate.                                         */
#define ESF_RPT_COUNT 197121            /* Repeat count			Integer */
#define ESF_RPT_SEQ_C 197122            /* Repeat sequence		Enumeration */
#define ESF_RPT_SEQ 197123              /*				Variable */
#define ESF_RPT_MAX 197124              /* Maximum code plus 1              */
/* Item codes for Text String aggregate.                                    */
#define ESF_TXS_TEXT_STRING 197377      /* Text string			Array of character string */
#define ESF_TXS_MAX 197378              /* Maximum code plus 1              */
/* Item codes for Named Value aggregate.                                    */
#define ESF_NVL_NAME 197633             /* Value name			String */
#define ESF_NVL_VALUE_C 197634          /* Value data			Enumeration */
#define ESF_NVL_VALUE 197635            /* 				Variable */
#define ESF_NVL_REFERENCE_ERF_INDEX 197636 /*				Integer */
#define ESF_NVL_MAX 197637              /* Maximum code plus 1              */
/* Values of ESF_NVL_VALUE_C.                                               */
#define ESF_K_VALUE_BOOLEAN 0           /*				Boolean */
#define ESF_K_VALUE_INTEGER 1           /*				Integer */
#define ESF_K_VALUE_TEXT 2              /*				Array of character string */
#define ESF_K_VALUE_GENERAL 3           /*				String */
#define ESF_K_VALUE_LIST 4              /*				Sequence of ESF_NVL */
#define ESF_K_VALUE_EXTERNAL 5          /*				ESF_EXT */
#define ESF_K_VALUE_FLOAT 6             /*				General floating point */
#define ESF_K_VALUE_DATE 7              /*				ESF_DAT */
#define ESF_K_VALUE_EXPR 8              /*				CFE_EXP */
#define ESF_K_VALUE_RELTIME 9           /*				DTIF_RLT */
#define ESF_K_VALUE_DDIF_DOC 10         /*				DDIF_DDF */
#define ESF_K_VALUE_DTIF_DOC 11         /*				DTIF_DTF */
#define ESF_K_VALUE_REFERENCE 12        /*				String (& ESF_NVL_REFERENCE_ERF_INDEX used) */
/* Item codes for Date and Time aggregate.                                  */
#define ESF_DAT_DATETIME 197889         /* Date and time		String */
#define ESF_DAT_TIME_DIFF_C 197890      /* Time difference		Enumeration */
#define ESF_DAT_TIME_DIFF 197891        /*				Variable */
#define ESF_DAT_MAX 197892              /* Maximum code plus 1              */
/* Values of ESF_DAT_TIME_DIFF_C.                                           */
#define ESF_K_UTC_TIME 0                /* UTC time			None */
#define ESF_K_PLUS_DIFF 1               /* Positive difference		String */
#define ESF_K_NEG_DIFF 2                /* Negative difference		String */
/* Item codes for External aggregate.                                       */
#define ESF_EXT_DIRECT_REFERENCE 198145 /* Direct reference		Object identifier */
#define ESF_EXT_INDIRECT_REFERENCE 198146 /* Indirect reference		Integer */
#define ESF_EXT_DATA_VALUE_DESCRIPTOR 198147 /* Data value descriptor	String */
#define ESF_EXT_ENCODING_C 198148       /* Encoding			Enumeration */
#define ESF_EXT_ENCODING 198149         /* 				Variable */
#define ESF_EXT_ENCODING_L 198150       /*     Length (on input)	Integer */
#define ESF_EXT_MAX 198151              /* Maximum code plus 1              */
/* Values of ESF_EXT_ENCODING_C.                                            */
#define ESF_K_DOCUMENT_ENCODING 0       /* Nested document		Document root aggregate */
#define ESF_K_DDIS_ENCODING 1           /* Nested document		DDIS encoding */
#define ESF_K_OCTET_ENCODING 2          /* Octet aligned		String */
#define ESF_K_ARBITRARY_ENCODING 3      /* Arbitrary			Bit string */
/* Aggregate type codes for CFE (Canonical Format Expressions).             */
#define CFE_EXP 1025                    /* Expression                       */
#define CFE_EXL 1026                    /* Expression list                  */
#define CFE_SLL 1027                    /* Selector list                    */
#define CFE_CFT 1028                    /* Complex float                    */
#define CFE_DAT 1029                    /* Date and time                    */
#define CFE_TXC 1030                    /* Text choice                      */
#define CFE_VTX 1031                    /* Varying text                     */
#define CFE_FRF 1032                    /* Field reference                  */
#define CFE_PEX 1033                    /* Parenthesized expression         */
#define CFE_PFE 1034                    /* Private function expression      */
#define CFE_STF 1035                    /* String format                    */
#define CFE_STP 1036                    /* String pretty                    */
#define CFE_NPM 1037                    /* Named parameter                  */
#define CFE_CCD 1038                    /* Cell coordinates                 */
#define CFE_CLR 1039                    /* Cell range                       */
#define CFE_RWR 1040                    /* Row range                        */
#define CFE_COR 1041                    /* Column range                     */
#define CFE_MAX 1042                    /* Maximum code plus one            */
/* Item codes for all aggregates.  CFE_AGGREGATE_TYPE is read-only.         */
#define CFE_USER_CONTEXT 1              /* User context			Longword */
#define CFE_AGGREGATE_TYPE 2            /* Aggregate type code		Word */
#define CFE_ALL_MAX 3                   /* Maximum code plus 1              */
/* Item codes for Expression aggregate.                                     */
#define CFE_EXP_MAJOR_VERSION 262401    /* Major version		Integer */
#define CFE_EXP_MINOR_VERSION 262402    /* Minor version		Integer */
#define CFE_EXP_LIST 262403             /* Expression list		Sequence of CFE_EXL */
#define CFE_EXP_MAX 262404              /* Maximum code plus 1              */
/* Current values for major and minor encoding version.  Should be omitted when the expression is embedded in a DTIF document. */
#define CFE_K_MAJOR_VERSION 1
#define CFE_K_MINOR_VERSION 4
/* Item codes for Expression List aggregate.                                */
#define CFE_EXL_EXPR_C 262657           /* Expression choice		Enumeration */
#define CFE_EXL_EXPR 262658             /*				Variable */
#define CFE_EXL_MAX 262659              /* Maximum code plus 1              */
/* Values of CFE_EXL_EXPR_C.                                                */
#define CFE_K_LIT_INTEGER 0             /* Literal integer		Integer */
#define CFE_K_LIT_FLOAT 1               /* Literal float		General floating point */
#define CFE_K_LIT_TEXT 2                /* Literal text			CFE_TXC */
#define CFE_K_LIT_DATE 3                /* Literal date			CFE_DAT */
#define CFE_K_LIT_SCALED_INTEGER 4      /* Literal scaled integer	Scaled integer */
#define CFE_K_LIT_COMPLEX_FLOAT 5       /* Literal complex float	CFE_CFT */
#define CFE_K_LIT_VTEXT 6               /* Literal varying text		CFE_VTX */
#define CFE_K_PARENTHESIZED 7           /* Parenthesized expression	CFE_PEX */
#define CFE_K_CELL_COORD 8              /* Cell coordinates		CFE_CCD */
#define CFE_K_CELL_RANGE 9              /* Cell range			CFE_CLR */
#define CFE_K_ROW_RANGE 10              /* Row range			CFE_RWR */
#define CFE_K_COL_RANGE 11              /* Column range			CFE_COR */
#define CFE_K_NAMED_RANGE 12            /* Named range			Array of character string */
#define CFE_K_COL_NUM 13                /* Column number		Integer */
#define CFE_K_ROW_NUM 14                /* Row number			Integer */
#define CFE_K_COL_NAME 15               /* Column name			String */
#define CFE_K_NEGATE 16                 /* Negate			Sequence of CFE_EXL */
#define CFE_K_ADD 17                    /* Add				Sequence of CFE_EXL */
#define CFE_K_SUBTRACT 18               /* Subtract			Sequence of CFE_EXL */
#define CFE_K_DIVIDE 19                 /* Divide			Sequence of CFE_EXL */
#define CFE_K_MULTIPLY 20               /* Multiply			Sequence of CFE_EXL */
#define CFE_K_POWER 21                  /* Raise to a power		Sequence of CFE_EXL */
#define CFE_K_EXPONENT 22               /* Exponent			Sequence of CFE_EXL */
#define CFE_K_IF_THEN_ELSE 23           /* If-then-else			Sequence of CFE_EXL */
#define CFE_K_NOT 24                    /* Logical not			Sequence of CFE_EXL */
#define CFE_K_AND 25                    /* Logical and 			Sequence of CFE_EXL */
#define CFE_K_OR 26                     /* Logical or			Sequence of CFE_EXL */
#define CFE_K_EQL 27                    /* Equal			Sequence of CFE_EXL */
#define CFE_K_GTR 28                    /* Greater than			Sequence of CFE_EXL */
#define CFE_K_GEQ 29                    /* Greater than or equal	Sequence of CFE_EXL */
#define CFE_K_LSS 30                    /* Less than			Sequence of CFE_EXL */
#define CFE_K_LEQ 31                    /* Less than or equal		Sequence of CFE_EXL */
#define CFE_K_NEQ 32                    /* Not equal			Sequence of CFE_EXL */
#define CFE_K_BETWEEN 33                /* Between			Sequence of CFE_EXL */
#define CFE_K_ABS_VALUE 34              /* Absolute value		Sequence of CFE_EXL */
#define CFE_K_MODULO 35                 /* Modulus			Sequence of CFE_EXL */
#define CFE_K_SQRT 36                   /* Square root			Sequence of CFE_EXL */
#define CFE_K_SUM 37                    /* Summation			CFE_SLL */
#define CFE_K_AVG 38                    /* Average			CFE_SLL */
#define CFE_K_COUNT 39                  /* Count			CFE_SLL */
#define CFE_K_MIN 40                    /* Minimum			CFE_SLL */
#define CFE_K_MAX 41                    /* Maximum			CFE_SLL */
#define CFE_K_STDEV 42                  /* Standard deviation		CFE_SLL */
#define CFE_K_VAR 43                    /* Variance			CFE_SLL */
#define CFE_K_CVT_TO_VALUE 44           /* Convert to value		Sequence of CFE_EXL */
#define CFE_K_ROUND 45                  /* Round			Sequence of CFE_EXL */
#define CFE_K_TRUNCATE 46               /* Truncate			Sequence of CFE_EXL */
#define CFE_K_INT 47                    /* Integerize			Sequence of CFE_EXL */
#define CFE_K_ISERROR 48                /* Is error			Sequence of CFE_EXL */
#define CFE_K_ISBLANK 49                /* Is blank			Sequence of CFE_EXL */
#define CFE_K_ISNULL 50                 /* Is null			Sequence of CFE_EXL */
#define CFE_K_ISDATE 51                 /* Is date			Sequence of CFE_EXL */
#define CFE_K_ISNUMBER 52               /* Is number			Sequence of CFE_EXL */
#define CFE_K_ISSTRING 53               /* Is string			Sequence of CFE_EXL */
#define CFE_K_ISREF 54                  /* Is referenced		Sequence of CFE_EXL */
#define CFE_K_STR_CHAR 55               /* String character		Sequence of CFE_EXL */
#define CFE_K_STR_CODE 56               /* String character code	Sequence of CFE_EXL */
#define CFE_K_STR_CONCAT 57             /* String concatenate		Sequence of CFE_EXL */
#define CFE_K_STR_EXTRACT 58            /* String extract		Sequence of CFE_EXL */
#define CFE_K_STR_FIND 59               /* String find substring	Sequence of CFE_EXL */
#define CFE_K_STR_FIXED 60              /* String fixed			Sequence of CFE_EXL */
#define CFE_K_STR_FORMAT 61             /* String edit			CFE_STF */
#define CFE_K_STR_LEFT 62               /* Extract substring left	Sequence of CFE_EXL */
#define CFE_K_STR_LENGTH 63             /* String length		Sequence of CFE_EXL */
#define CFE_K_STR_LOWER 64              /* String lowercase		Sequence of CFE_EXL */
#define CFE_K_STR_PRETTY 65             /* String pretty		CFE_STP */
#define CFE_K_STR_PROPER 66             /* String proper		Sequence of CFE_EXL */
#define CFE_K_STR_REPEAT 67             /* String repeat		Sequence of CFE_EXL */
#define CFE_K_STR_REPLACE 68            /* String replace		Sequence of CFE_EXL */
#define CFE_K_STR_REVERSE 69            /* String reverse		Sequence of CFE_EXL */
#define CFE_K_STR_RIGHT 70              /* Extract substring right	Sequence of CFE_EXL */
#define CFE_K_STR_TRIM 71               /* String trim			Sequence of CFE_EXL */
#define CFE_K_STR_UPPER 72              /* String uppercase		Sequence of CFE_EXL */
#define CFE_K_CHOOSE 73                 /* Choose			Sequence of CFE_EXL */
#define CFE_K_INDEX 74                  /* Index			Sequence of CFE_EXL */
#define CFE_K_VLOOKUP 75                /* Vertical lookup		Sequence of CFE_EXL */
#define CFE_K_HLOOKUP 76                /* Horizontal lookup		Sequence of CFE_EXL */
#define CFE_K_TABLE 77                  /* Table			Sequence of CFE_EXL */
#define CFE_K_NAME_DAY 78               /* Date day of the week		Sequence of CFE_EXL */
#define CFE_K_NAME_MONTH 79             /* Date month name		Sequence of CFE_EXL */
#define CFE_K_NAME_DAYNUM 80            /* Day of the week		Sequence of CFE_EXL */
#define CFE_K_NAME_MONTHNUM 81          /* Month name			Sequence of CFE_EXL */
#define CFE_K_NOW 82                    /* Now				None */
#define CFE_K_TODAY 83                  /* Today			None */
#define CFE_K_TOMORROW 84               /* Tomorrow			None */
#define CFE_K_YESTERDAY 85              /* Yesterday			None */
#define CFE_K_EXT_DAY 86                /* Extract day			Sequence of CFE_EXL */
#define CFE_K_EXT_MONTH 87              /* Extract month		Sequence of CFE_EXL */
#define CFE_K_EXT_YEAR 88               /* Extract year			Sequence of CFE_EXL */
#define CFE_K_EXT_HOUR 89               /* Extract hour			Sequence of CFE_EXL */
#define CFE_K_EXT_MINUTE 90             /* Extract minute		Sequence of CFE_EXL */
#define CFE_K_EXT_SECOND 91             /* Extract second		Sequence of CFE_EXL */
#define CFE_K_DIFF_DAY 92               /* Difference day		Sequence of CFE_EXL */
#define CFE_K_DIFF_WEEK 93              /* Difference week		Sequence of CFE_EXL */
#define CFE_K_DIFF_MONTH 94             /* Difference month		Sequence of CFE_EXL */
#define CFE_K_DIFF_YEAR 95              /* Difference year		Sequence of CFE_EXL */
#define CFE_K_DIFF_HOUR 96              /* Difference hour		Sequence of CFE_EXL */
#define CFE_K_DIFF_MIN 97               /* Difference minute		Sequence of CFE_EXL */
#define CFE_K_DIFF_SEC 98               /* Difference second		Sequence of CFE_EXL */
#define CFE_K_CVT_TO_DATE 99            /* String to date		Sequence of CFE_EXL */
#define CFE_K_CVT_TO_TIME 100           /* String to time		Sequence of CFE_EXL */
#define CFE_K_PLUS_DAYS 101             /* Plus days			Sequence of CFE_EXL */
#define CFE_K_PLUS_WEEKS 102            /* Plus weeks			Sequence of CFE_EXL */
#define CFE_K_PLUS_MONTHS 103           /* Plus months			Sequence of CFE_EXL */
#define CFE_K_PLUS_YEARS 104            /* Plus years			Sequence of CFE_EXL */
#define CFE_K_PLUS_HOURS 105            /* Plus hours			Sequence of CFE_EXL */
#define CFE_K_PLUS_MINS 106             /* Plus minutes			Sequence of CFE_EXL */
#define CFE_K_PLUS_SECS 107             /* Plus seconds			Sequence of CFE_EXL */
#define CFE_K_ERROR 108                 /* Error			None */
#define CFE_K_NULL 109                  /* Null				None */
#define CFE_K_CUR_ROW 110               /* Current row			None */
#define CFE_K_CUR_COL 111               /* Current column		None */
#define CFE_K_CUR_CELL 112              /* Current cell			None */
#define CFE_K_CELL_ROW 113              /* Row portion of cell name	Sequence of CFE_EXL */
#define CFE_K_CELL_COL 114              /* Column portion of cell name	Sequence of CFE_EXL */
#define CFE_K_CELL_NAME 115             /* Constructed cell reference	Sequence of CFE_EXL */
#define CFE_K_COUNT_ROWS 116            /* Count rows			Sequence of CFE_EXL */
#define CFE_K_COUNT_COLS 117            /* Count columns		Sequence of CFE_EXL */
#define CFE_K_CELL_EXTRACT 118          /* Cell extract			Sequence of CFE_EXL */
#define CFE_K_APPREC 119                /* Appreciation			Sequence of CFE_EXL */
#define CFE_K_DEP_CROSS 120             /* Depreciation declining balance crossover	Sequence of CFE_EXL */
#define CFE_K_DEP_DB 121                /* Depreciation declining balance	Sequence of CFE_EXL */
#define CFE_K_DEP_DDB 122               /* Depreciation double declining balance	Sequence of CFE_EXL */
#define CFE_K_DEP_SLINE 123             /* Depreciation straight line	Sequence of CFE_EXL */
#define CFE_K_DEP_SOYD 124              /* Depreciation sum of years	Sequence of CFE_EXL */
#define CFE_K_DISCOUNT 125              /* Discount			Sequence of CFE_EXL */
#define CFE_K_FV 126                    /* Future value			Sequence of CFE_EXL */
#define CFE_K_FVA 127                   /* Future value of annuity	Sequence of CFE_EXL */
#define CFE_K_FVPV 128                  /* Future value of single payment	Sequence of CFE_EXL */
#define CFE_K_INTEREST 129              /* Interest payments		Sequence of CFE_EXL */
#define CFE_K_IRR 130                   /* Internal rate of return	Sequence of CFE_EXL */
#define CFE_K_MIRR 131                  /* Modified internal rate of return	Sequence of CFE_EXL */
#define CFE_K_NPV 132                   /* Net present value		Sequence of CFE_EXL */
#define CFE_K_PAYBACK 133               /* Payback			Sequence of CFE_EXL */
#define CFE_K_PERPMT 134                /* Number periods to achieve future value	Sequence of CFE_EXL */
#define CFE_K_PERPV 135                 /* Number periods given present value		Sequence of CFE_EXL */
#define CFE_K_PMTPV 136                 /* Payment per period given present value	Sequence of CFE_EXL */
#define CFE_K_PMTFV 137                 /* Payment per period to achieve future value	Sequence of CFE_EXL */
#define CFE_K_PRINCIPAL 138             /* Principal			Sequence of CFE_EXL */
#define CFE_K_PVA 139                   /* Present value of annuity	Sequence of CFE_EXL */
#define CFE_K_PVFV 140                  /* Present value to achieve future value	Sequence of CFE_EXL */
#define CFE_K_RATE 141                  /* Interest rate		Sequence of CFE_EXL */
#define CFE_K_LOGEST 142                /* LogEst			Sequence of CFE_EXL */
#define CFE_K_LSQR 143                  /* Least squares		Sequence of CFE_EXL */
#define CFE_K_INTEGRATE 144             /* Integrate			Sequence of CFE_EXL */
#define CFE_K_SIGMA 145                 /* Sigma			Sequence of CFE_EXL */
#define CFE_K_TREND 146                 /* Trend			Sequence of CFE_EXL */
#define CFE_K_LIT_TRUE 147              /* Literal true			None */
#define CFE_K_LIT_FALSE 148             /* Literal false		None */
#define CFE_K_LIT_PI 149                /* Literal pi			None */
#define CFE_K_RANDOM_U 150              /* Random number, uniformly distributed		None */
#define CFE_K_DECIMAL_STRING 151        /* Decimal string		String */
#define CFE_K_IN_TABLE 152              /* Field in table		Sequence of CFE_EXL */
#define CFE_K_SIN 153                   /* Sine				Sequence of CFE_EXL */
#define CFE_K_COS 154                   /* Cosine			Sequence of CFE_EXL */
#define CFE_K_TAN 155                   /* Tangent			Sequence of CFE_EXL */
#define CFE_K_ASIN 156                  /* Arc sine			Sequence of CFE_EXL */
#define CFE_K_ACOS 157                  /* Arc cosine			Sequence of CFE_EXL */
#define CFE_K_ATAN 158                  /* Arc tangent			Sequence of CFE_EXL */
#define CFE_K_ATAN2 159                 /* Arc tangent 2		Sequence of CFE_EXL */
#define CFE_K_LOG10 160                 /* Common logarithm		Sequence of CFE_EXL */
#define CFE_K_LOGN 161                  /* Natural logarithm		Sequence of CFE_EXL */
#define CFE_K_ALOG 162                  /* Antilogarithm		Sequence of CFE_EXL */
#define CFE_K_FACTORIAL 163             /* Factorial			Sequence of CFE_EXL */
#define CFE_K_ASL 164                   /* Arithmetic shift left	Sequence of CFE_EXL */
#define CFE_K_ASR 165                   /* Arithmetic shift right	Sequence of CFE_EXL */
#define CFE_K_ONES_CMP 166              /* Ones complement		Sequence of CFE_EXL */
#define CFE_K_SIGN 167                  /* Sign				Sequence of CFE_EXL */
#define CFE_K_CONTAINS 168              /* Contains substring		Sequence of CFE_EXL */
#define CFE_K_MATCHES 169               /* Matches			Sequence of CFE_EXL */
#define CFE_K_STARTS 170                /* String starts with		Sequence of CFE_EXL */
#define CFE_K_UNARY_PLUS 171            /* Unary plus			Sequence of CFE_EXL */
#define CFE_K_PERCENT 172               /* Percent			Sequence of CFE_EXL */
#define CFE_K_ISNOT_AVAIL 173           /* Is not available		Sequence of CFE_EXL */
#define CFE_K_ISNOT_CALC 174            /* Is not calculatable		Sequence of CFE_EXL */
#define CFE_K_NOT_AVAIL 175             /* Not available		None */
#define CFE_K_NOT_CALC 176              /* Not calculatable		None */
#define CFE_K_CELL_INDIRECT 177         /* Cell indirection		Sequence of CFE_EXL */
#define CFE_K_PERFV 178                 /* Periods to achieve future value	Sequence of CFE_EXL */
#define CFE_K_CURRENT_VALUE 179         /* Current value		None */
#define CFE_K_IDENTIFIER 180            /* Identifier			CFE_TXC */
#define CFE_K_PRIVATE_FUNCTION 181      /* Private function		CFE_PFE */
#define CFE_K_FIELD_REFERENCE 182       /* Field reference		CFE_FRF */
#define CFE_K_STDEVP 183                /* Standard deviation		CFE_SLL */
#define CFE_K_VARP 184                  /* Biased variance		CFE_SLL */
#define CFE_K_SQL_SELECT 185            /* SQL Select			Sequence of CFE_EXL */
#define CFE_K_EXT_CELL_COORD 186        /* External cell coordinates	DTIF_ECC */
#define CFE_K_EXT_CELL_RANGE 187        /* External cell range		DTIF_ECR */
#define CFE_K_EXT_NAMED_RANGE 188       /* External named range		DTIF_ENR */
#define CFE_K_EXT_REFERENCE 189         /* External reference		DTIF_REF */
#define CFE_K_LIT_RELTIME 190           /* Literal relative time	DTIF_RLT */
/* Item codes for Selector List aggregate.                                  */
#define CFE_SLL_CRITERIA 262913         /* Criteria			Sequence of CFE_EXL */
#define CFE_SLL_SELECTION 262914        /* Selection			Sequence of CFE_EXL */
#define CFE_SLL_MAX 262915              /* Maximum code plus 1              */
/* Item codes for Complex Float aggregate.                                  */
#define CFE_CFT_REAL_PART 263169        /* Real part			General floating point */
#define CFE_CFT_IMAGINARY_PART 263170   /* Imaginary part		General floating point */
#define CFE_CFT_MAX 263171              /* Maximum code plus 1              */
/* Item codes for Date and Time aggregate.                                  */
#define CFE_DAT_DATETIME 263425         /* Date and time		String */
#define CFE_DAT_TIME_DIFF_C 263426      /* Time difference		Enumeration */
#define CFE_DAT_TIME_DIFF 263427        /*				Variable */
#define CFE_DAT_MAX 263428              /* Maximum code plus 1              */
/* Values of CFE_DAT_TIME_DIFF_C.                                           */
#define CFE_K_UTC_TIME 0                /* UTC time			None */
#define CFE_K_PLUS_DIFF 1               /* Positive difference		String */
#define CFE_K_NEG_DIFF 2                /* Negative difference		String */
/* Item codes for Text Choice aggregate.                                    */
#define CFE_TXC_TEXT_C 263681           /* Text choice			Enumeration */
#define CFE_TXC_TEXT 263682             /*				Variable */
#define CFE_TXC_MAX 263683              /* Maximum code plus 1              */
/* Values of CFE_TXC_TEXT_C.                                                */
#define CFE_K_LATIN1_TEXT 0             /* Latin-1 text			String */
#define CFE_K_SIMPLE_TEXT 1             /* Simple text			Character string */
#define CFE_K_COMPLEX_TEXT 2            /* Complex text			Array of character string */
/* Item codes for Varying Text Aggregate.                                   */
#define CFE_VTX_VTEXT_LEN 263937        /* Varying Text Length		Integer */
#define CFE_VTX_VTEXT_STR 263938        /* Varying Text String		Character-String */
#define CFE_VTX_MAX 263939              /* Maximum code plus 1              */
/* Item codes for Field Reference aggregate.                                */
#define CFE_FRF_FIELD_CONTEXT 264193    /* Field context		String */
#define CFE_FRF_PATH 264194             /* Path				Array of string */
#define CFE_FRF_MAX 264195              /* Maximum code plus 1              */
/* Item codes for Parenthesized Expression aggregate.                       */
#define CFE_PEX_BEGIN_EXPR 264449       /* Begin expression 		Array of character string */
#define CFE_PEX_VALUE_EXPR 264450       /* Value expression		Sequence of CFE_EXL */
#define CFE_PEX_END_EXPR 264451         /* End expression		Array of character string */
#define CFE_PEX_MAX 264452              /* Maximum code plus 1              */
/* Item codes for Private Function Expression aggregate.                    */
#define CFE_PFE_FACILITY 264705         /* Facility			String */
#define CFE_PFE_NAME 264706             /* Function name		String */
#define CFE_PFE_REF_LABEL 264707        /* Reference label		String */
#define CFE_PFE_REF_LABEL_TYPE 264708   /* Reference label type		String with add-info */
#define CFE_PFE_RETURN_TYPE 264709      /* Return type			Longword */
#define CFE_PFE_PARAMS 264710           /* Parameters			Sequence of CFE_NPM */
#define CFE_PFE_MAX 264711              /* Maximum code plus 1              */
/* Values of the add-info parameter for CFE_PFE_REF_LABEL_TYPE.             */
#define CFE_K_PRIVATE_LABEL_TYPE 0      /* Private label type               */
#define CFE_K_RMS_LABEL_TYPE 1          /* RMS file specification ("$RMS")  */
#define CFE_K_UTX_LABEL_TYPE 2          /* ULTRIX file specification ("$UTX") */
#define CFE_K_MDS_LABEL_TYPE 3          /* MS-DOS or OS/2 file specification ("$MDS") */
/* Bit definitions for CFE_PFE_RET_TYPE.                                    */
#ifdef CDAbig_endian
#define cfe_m_pfe_fncret_numeric 0x80000000
#else
#define cfe_m_pfe_fncret_numeric 1
#endif
#ifdef CDAbig_endian
#define cfe_m_pfe_fncret_boolean 0x40000000
#else
#define cfe_m_pfe_fncret_boolean 2
#endif
#ifdef CDAbig_endian
#define cfe_m_pfe_fncret_date 0x20000000
#else
#define cfe_m_pfe_fncret_date 4
#endif
#ifdef CDAbig_endian
#define cfe_m_pfe_fncret_text 0x10000000
#else
#define cfe_m_pfe_fncret_text 8
#endif
struct pfe_type {
    unsigned cfe_v_pfe_fncret_numeric : 1;
    unsigned cfe_v_pfe_fncret_boolean : 1;
    unsigned cfe_v_pfe_fncret_date : 1;
    unsigned cfe_v_pfe_fncret_text : 1;
    unsigned cfe_v_pfe_fill_0 : 12;
    unsigned cfe_v_pfe_fill : 16;
    } ;
/* Item codes for String Format aggregate.                                  */
#define CFE_STF_SOURCE 264961           /* Source			Sequence of CFE_EXL */
#define CFE_STF_EDIT_STRING 264962      /* Edit string			ESF_EDS */
#define CFE_STF_MAX 264963              /* Maximum code plus 1              */
/* Item codes for String Pretty aggregate.                                  */
#define CFE_STP_STRING_EXPR 265217      /* String expression		Sequence of CFE_EXL */
#define CFE_STP_PRETTY_FLAGS 265218     /* Flags			Longword */
#define CFE_STP_MAX 265219              /* Maximum code plus 1              */
/* Bit definitions for CFE_STP_PRETTY_FLAGS.                                */
#ifdef CDAbig_endian
#define cfe_m_pretty_collapse 0x80000000
#else
#define cfe_m_pretty_collapse 1
#endif
#ifdef CDAbig_endian
#define cfe_m_pretty_compress 0x40000000
#else
#define cfe_m_pretty_compress 2
#endif
#ifdef CDAbig_endian
#define cfe_m_pretty_lowercase 0x20000000
#else
#define cfe_m_pretty_lowercase 4
#endif
#ifdef CDAbig_endian
#define cfe_m_pretty_trim 0x10000000
#else
#define cfe_m_pretty_trim 8
#endif
#ifdef CDAbig_endian
#define cfe_m_pretty_uncomment 0x8000000
#else
#define cfe_m_pretty_uncomment 16
#endif
#ifdef CDAbig_endian
#define cfe_m_pretty_upcase 0x4000000
#else
#define cfe_m_pretty_upcase 32
#endif
struct stp_pretty_flags {
    unsigned cfe_v_pretty_collapse : 1;
    unsigned cfe_v_pretty_compress : 1;
    unsigned cfe_v_pretty_lowercase : 1;
    unsigned cfe_v_pretty_trim : 1;
    unsigned cfe_v_pretty_uncomment : 1;
    unsigned cfe_v_pretty_upcase : 1;
    unsigned cfe_v_pretty_fill_0 : 10;
    unsigned cfe_v_pretty_fill_1 : 16;
    } ;
/* Item codes for Named Parameter aggregate.                                */
#define CFE_NPM_NAME 265473             /* Parameter name		String */
#define CFE_NPM_VALUE 265474            /* Parameter value		Sequence of CFE_EXL */
#define CFE_NPM_MAX 265475              /* Maximum code plus 1              */
/* Item codes for Cell Coordinates aggregate.                               */
#define CFE_CCD_ROW 265729              /* Row number			Integer */
#define CFE_CCD_COLUMN 265730           /* Column number		Integer */
#define CFE_CCD_FLAGS 265731            /* Flags			Enumeration */
#define CFE_CCD_MAX 265732              /* Maximum code plus 1              */
/* Values of CFE_CCD_FLAGS.						DTIF defined */
#define CFE_K_RELROW_RELCOL 0           /* Relative row, relative column    */
#define CFE_K_RELROW_ABSCOL 1           /* Relative row, absolute column    */
#define CFE_K_ABSROW_RELCOL 2           /* Absolute row, relative column    */
#define CFE_K_ABSROW_ABSCOL 3           /* Absolute row, absolute column    */
/* Item codes for Cell Range aggregate.                                     */
#define CFE_CLR_RANGE_BEGIN 265985      /* Beginning cell coordinates	CFE_CCD */
#define CFE_CLR_RANGE_END 265986        /* Ending cell coordinates	CFE_CCD */
#define CFE_CLR_MAX 265987              /* Maximum code plus 1              */
/* Item codes for Row Range aggregate.                                      */
#define CFE_RWR_ROW_BEGIN 266241        /* Beginning row number		Integer */
#define CFE_RWR_ROW_END 266242          /* Ending row number		Integer */
#define CFE_RWR_MAX 266243              /* Maximum code plus 1              */
/* Item codes for Column Range aggregate.                                   */
#define CFE_COR_COL_BEGIN 266497        /* Beginning column number	Integer */
#define CFE_COR_COL_END 266498          /* Ending column number		Integer */
#define CFE_COR_MAX 266499              /* Maximum code plus 1              */
#endif
