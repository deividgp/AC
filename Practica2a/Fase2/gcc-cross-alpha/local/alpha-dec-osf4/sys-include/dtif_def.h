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
/* @(#)$RCSfile: dtif_def.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 04:28:42 $     */
/********************************************************************************************************************************/
/* Created  2-JUN-1991 09:35:05 by VAX SDL V3.2-12     Source:  2-APR-1991 17:21:46 DDIF$DEVELOP_ROOT:[DDIFBUILD.LIB.SRC]DTIF$DEF */
/********************************************************************************************************************************/
 
/*** MODULE DTIF$DEFINITIONS IDENT V1-011 ***/
/*++                                                                        */
/*  COPYRIGHT (c) 1988, 1990 BY                                             */
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
/* Item codes for CDA$CREATE_ROOT_AGGREGATE processing-options parameter.   */
#define DTIF$_INHERIT_ATTRIBUTES 513    /* Inherit attributes to cols, rows, cells, etc. */
#define DTIF$_INHERIT_ATTR_TO_ROW_COL 514 /* Inherit only to row-col level  */
#define DTIF$_INHERIT_ATTR_FROM_ROW_COL 515 /* Inherit only from row-col level to cells */
#define DTIF$_RETAIN_DEFINITIONS 516    /* Enable cda$find_definition       */
/* Scope codes for the CDA$ENTER_SCOPE and CDA$LEAVE_SCOPE scope-code parameter. */
/* If an aggregate type is listed, it must be presented with CDA$ENTER_SCOPE. */
#define DTIF$K_DOCUMENT_SCOPE 512       /* Document scope                   */
#define DTIF$K_TABLE_SCOPE 513          /* Table scope			DTIF$_TBL */
#define DTIF$K_ROW_SCOPE 514            /* Row scope			DTIF$_ROW */
#define DTIF$K_CELLS_SCOPE 515          /* Cells scope                      */
/* Aggregate type codes for DTIF (Digital Table Interchange Format).        */
#define DTIF$_DTF 513                   /* DTIF document root               */
#define DTIF$_DSC 514                   /* Document descriptor              */
#define DTIF$_HDR 515                   /* Document header                  */
#define DTIF$_DAT 516                   /* Date and time                    */
#define DTIF$_ERF 517                   /* External reference               */
#define DTIF$_LPT 518                   /* Language preference table        */
#define DTIF$_NVL 519                   /* Named value                      */
#define DTIF$_NES 520                   /* Named edit string                */
#define DTIF$_CAT 521                   /* Column attributes                */
#define DTIF$_TBL 522                   /* Table definition                 */
#define DTIF$_TMD 523                   /* Table metadata                   */
#define DTIF$_WND 524                   /* Window definition                */
#define DTIF$_ROW 525                   /* Row definition                   */
#define DTIF$_CLD 526                   /* Cell data                        */
#define DTIF$_VTX 527                   /* Varying text                     */
#define DTIF$_ARD 528                   /* Array definition                 */
#define DTIF$_CFT 529                   /* Complex float                    */
#define DTIF$_FMI 530                   /* Format information               */
#define DTIF$_CCD 531                   /* Cell coordinates                 */
#define DTIF$_RNG 532                   /* Range definition                 */
#define DTIF$_CLR 533                   /* Cell range                       */
#define DTIF$_RWR 534                   /* Row range                        */
#define DTIF$_COR 535                   /* Column range                     */
#define DTIF$_NMR 536                   /* Named range                      */
#define DTIF$_EXT 537                   /* External                         */
#define DTIF$_MAX 538                   /* Maximum code plus 1              */
/* Item codes for all aggregates.  DTIF$_AGGREGATE_TYPE is read-only.       */
#define DTIF$_USER_CONTEXT 1            /* User context			Longword */
#define DTIF$_AGGREGATE_TYPE 2          /* Aggregate type code		Word */
#define DTIF$_ALL_MAX 3                 /* Maximum code plus 1              */
/* Item codes for DTIF Document Root aggregate.                             */
#define DTIF$_DTF_DESCRIPTOR 131329     /* Document descriptor		DTIF$_DSC */
#define DTIF$_DTF_HEADER 131330         /* Document header		DTIF$_HDR */
#define DTIF$_DTF_TABLES 131331         /* Tables			Sequence of DTIF$_TBL */
#define DTIF$_DTF_MAX 131332            /* Maximum code plus 1              */
/* Item codes for Document Descriptor aggregate.  During CDA$PUT_AGGREGATE, the values of DTIF$_DSC_ENCODE_MAJOR_VERSION and */
/* DTIF$_DSC_ENCODE_MINOR_VERSION are not used.  The document always contains the current values for major and minor version. */
#define DTIF$_DSC_MAJOR_VERSION 131585  /* Creator major version	Integer */
#define DTIF$_DSC_MINOR_VERSION 131586  /* Creator minor version	Integer */
#define DTIF$_DSC_PRODUCT_IDENTIFIER 131587 /* Product identifier		String */
#define DTIF$_DSC_PRODUCT_NAME 131588   /* Product name			Array of character string */
#define DTIF$_DSC_ENCODE_MAJOR_VERSION 131589 /* Encoding major version	Integer */
#define DTIF$_DSC_ENCODE_MINOR_VERSION 131590 /* Encoding minor version	Integer */
#define DTIF$_DSC_MAX 131591            /* Maximum code plus 1              */
/* Current values for major and minor encoding version.                     */
#define DTIF$K_MAJOR_VERSION 1
#define DTIF$K_MINOR_VERSION 0
/* Item codes for Document Header aggregate.                                */
#define DTIF$_HDR_PRIVATE_DATA 131841   /* Private header data		Sequence of DTIF$_NVL */
#define DTIF$_HDR_TITLE 131842          /* Title			Array of character string */
#define DTIF$_HDR_DATE 131843           /* Date				DTIF$_DAT */
#define DTIF$_HDR_EXTERNAL_REFERENCES 131844 /* External references		Sequence of DTIF$_ERF */
#define DTIF$_HDR_LANGUAGES_C 131845    /* Languages			Array of enumeration */
#define DTIF$_HDR_LANGUAGES 131846      /*				Array of variable */
#define DTIF$_HDR_LANGUAGE_PREF_TABLES 131847 /* Language preference tables	Sequence of DTIF$_LPT */
#define DTIF$_HDR_GENERIC_COLUMNS 131848 /* Generic column attributes	Sequence of DTIF$_CAT */
#define DTIF$_HDR_MAX 131849            /* Maximum code plus 1              */
/* Values of DTIF$_HDR_LANGUAGES_C.                                         */
#define DTIF$K_ISO_639_LANGUAGE 0       /* ISO 639 language name	String */
#define DTIF$K_OTHER_LANGUAGE 1         /* Other language name		Character string */
/* Item codes for Date and Time aggregate.                                  */
#define DTIF$_DAT_DATETIME 132097       /* Date and time		String */
#define DTIF$_DAT_TIME_DIFF_C 132098    /* Time difference		Enumeration */
#define DTIF$_DAT_TIME_DIFF 132099      /*				Variable */
#define DTIF$_DAT_MAX 132100            /* Maximum code plus 1              */
/* Values of DTIF$_DAT_TIME_DIFF_C.                                         */
#define DTIF$K_UTC_TIME 0               /* UTC time			None */
#define DTIF$K_PLUS_DIFF 1              /* Positive difference		String */
#define DTIF$K_NEG_DIFF 2               /* Negative difference		String */
/* Item codes for External Reference aggregate.                             */
#define DTIF$_ERF_DATA_TYPE 132353      /* Data type			Object identifier */
#define DTIF$_ERF_DESCRIPTOR 132354     /* Descriptor			Array of character string */
#define DTIF$_ERF_LABEL 132355          /* Label			Character string */
#define DTIF$_ERF_LABEL_TYPE 132356     /* Label type			String with add-info */
#define DTIF$_ERF_CONTROL 132357        /* Control			Enumeration */
#define DTIF$_ERF_MAX 132358            /* Maximum code plus 1              */
/* Values of the add-info parameter for DTIF$_ERF_LABEL_TYPE.  Must be identical */
/* to values for DDIF$_ERF_LABEL_TYPE and DOTS$_RTE_NAME_TYPE.              */
#define DTIF$K_PRIVATE_LABEL_TYPE 0     /* Private label type               */
#define DTIF$K_RMS_LABEL_TYPE 1         /* RMS file specification ("$RMS")  */
#define DTIF$K_UTX_LABEL_TYPE 2         /* ULTRIX file specification ("$UTX") */
#define DTIF$K_MDS_LABEL_TYPE 3         /* MS-DOS file specification ("$MDS") */
#define DTIF$K_STYLE_LABEL_TYPE 4       /* Style file specification ("$STYLE") */
#define DTIF$K_OS2_LABEL_TYPE 5         /* OS/2 file specification ("$OS2") */
#define DTIF$K_OA_LABEL_TYPE 6          /* ALL-IN-1 file specification ("$OA") */
#define DTIF$K_PACKED_STYLE_LABEL_TYPE 7 /* Style-guide file specification ("$STYLE") (used when */
/* NO_COPY style guide packed by DOTS)                                      */
/* Values of DTIF$_ERF_CONTROL.						DTIF conforming */
#define DTIF$K_COPY_REFERENCE 1         /* Copy on reference                */
#define DTIF$K_NO_COPY_REFERENCE 2      /* No copy on reference             */
/* Item codes for Language Preference Table aggregate.                      */
#define DTIF$_LPT_LANGUAGE_INDEX 132609 /* Language index		Integer */
#define DTIF$_LPT_APPL_PRIVATE 132610   /* Application private		Sequence of DTIF$_NVL */
#define DTIF$_LPT_ITEMS 132611          /* Named items			Sequence of DTIF$_NVL */
#define DTIF$_LPT_EDITSTRS 132612       /* Named edit strings		Sequence of DTIF$_NES */
#define DTIF$_LPT_COLLATE_SEQ 132613    /* Collating sequence		String with add-info */
#define DTIF$_LPT_COLLATE_TABLE 132614  /* Collating table		String */
#define DTIF$_LPT_MAX 132615            /* Maximum code plus 1              */
/* Values of the add-info parameter for DTIF$_LPT_COLLATE_SEQ.              */
#define DTIF$K_PRIVATE_COLLATE_SEQ 0    /* Private collating sequence       */
#define DTIF$K_ASCII_COLLATE_SEQ 1      /* ASCII collating sequence ("$ASCII") */
#define DTIF$K_MCS_COLLATE_SEQ 2        /* DEC Multinational collating sequence ("$MCS") */
#define DTIF$K_DANISH_COLLATE_SEQ 3     /* Danish collating sequence ("$DANISH") */
#define DTIF$K_FINSWD_COLLATE_SEQ 4     /* Finnish/Swedish collating sequence ("$FINSWD") */
#define DTIF$K_NORWEG_COLLATE_SEQ 5     /* Norwegian collating sequence ("$NORWEG") */
#define DTIF$K_SPANSH_COLLATE_SEQ 6     /* Spanish collating sequence ("$SPANSH") */
/* Item codes for Named Value aggregate.                                    */
#define DTIF$_NVL_NAME 132865           /* Value name			String */
#define DTIF$_NVL_VALUE_C 132866        /* Value data			Enumeration */
#define DTIF$_NVL_VALUE 132867          /* 				Variable */
#define DTIF$_NVL_MAX 132868            /* Maximum code plus 1              */
/* Values of DTIF$_NVL_VALUE_C.                                             */
#define DTIF$K_VALUE_BOOLEAN 0          /*				Boolean */
#define DTIF$K_VALUE_INTEGER 1          /*				Integer */
#define DTIF$K_VALUE_TEXT 2             /*				Array of character string */
#define DTIF$K_VALUE_GENERAL 3          /*				String */
#define DTIF$K_VALUE_LIST 4             /*				Sequence of DTIF$_NVL */
#define DTIF$K_VALUE_EXTERNAL 5         /*				DTIF$_EXT */
#define DTIF$K_VALUE_FLOAT 6            /*				General floating point */
#define DTIF$K_VALUE_DATE 7             /*				DTIF$_DAT */
#define DTIF$K_VALUE_EXPR 8             /*				CFE$_EXP */
/* Item codes for Named Edit String aggregate.                              */
#define DTIF$_NES_NAME 133121           /* Name				String */
#define DTIF$_NES_DEFN 133122           /* Definition			ESF$_EDS */
#define DTIF$_NES_MAX 133123            /* Maximum code plus 1              */
/* Item codes for Column Attributes aggregate.                              */
#define DTIF$_CAT_NAME 133377           /* Name				String */
#define DTIF$_CAT_ID 133378             /* Identifier			Integer */
#define DTIF$_CAT_APPL_PRIVATE 133379   /* Application private		Sequence of DTIF$_NVL */
#define DTIF$_CAT_GENERIC_REF 133380    /* Generic reference		Integer */
#define DTIF$_CAT_DESCRIPTION 133381    /* Description			Array of character string */
#define DTIF$_CAT_FORMATS 133382        /* Format information list	Sequence of DTIF$_FMI */
#define DTIF$_CAT_COMPUTED_BY 133383    /* Computed by expression	CFE$_EXP */
#define DTIF$_CAT_DEFAULT_VALUE_C 133384 /* Default value		Enumeration */
#define DTIF$_CAT_DEFAULT_VALUE 133385  /*				Variable */
#define DTIF$_CAT_MISSING_VALUE_C 133386 /* Missing value		Enumeration */
#define DTIF$_CAT_MISSING_VALUE 133387  /*				Variable */
#define DTIF$_CAT_QUERY_NAME 133388     /* Query name			Character string */
#define DTIF$_CAT_COLUMN_HDR 133389     /* Column header		Character string */
#define DTIF$_CAT_POSITION 133390       /* Position			Integer */
#define DTIF$_CAT_DATA_TYPE 133391      /* Data type			Enumeration */
#define DTIF$_CAT_DATA_LENGTH 133392    /* Data length (bytes)		Integer */
#define DTIF$_CAT_SCALE_FACTOR 133393   /* Scale factor			Integer */
#define DTIF$_CAT_FLAGS 133394          /* Flags			Longword */
#define DTIF$_CAT_MAX 133395            /* Maximum code plus 1              */
/* Values of DTIF$_CAT_DEFAULT_VALUE_C, DTIF$_CAT_MISSING_VALUE_C, DTIF$_CLD_VALUE_C. */
#define DTIF$K_CV_INTEGER 0             /* Integer			Variable integer */
#define DTIF$K_CV_LATIN1_TEXT 1         /* Latin-1 text			String */
#define DTIF$K_CV_SIMPLE_TEXT 2         /* Simple text			Character string */
#define DTIF$K_CV_DATE 3                /* Date				DTIF$_DAT */
#define DTIF$K_CV_SCALED_INTEGER 4      /* Scaled integer		Scaled integer */
#define DTIF$K_CV_VTEXT 5               /* Varying text 		DTIF$_VTX */
#define DTIF$K_CV_ARRAY 6               /* Array definition		DTIF$_ARD */
#define DTIF$K_CV_COMPLEX 7             /* Complex float		DTIF$_CFT */
#define DTIF$K_CV_FLOAT 8               /* Float			General floating point */
#define DTIF$K_CV_BOOLEAN 9             /* Boolean			Boolean */
/* Values of DTIF$_CAT_DATA_TYPE.					DTIF conforming */
#define DTIF$K_DT_UNKNOWN 0             /* Unknown                          */
#define DTIF$K_DT_WORD 1                /* Signed word integer              */
#define DTIF$K_DT_LONG 2                /* Signed longword integer          */
#define DTIF$K_DT_QUAD 3                /* Signed quadword integer          */
#define DTIF$K_DT_FFLOAT 4              /* VAX F-floating                   */
#define DTIF$K_DT_DFLOAT 5              /* VAX D-floating                   */
#define DTIF$K_DT_GFLOAT 6              /* VAX G-floating                   */
#define DTIF$K_DT_HFLOAT 7              /* VAX H-floating                   */
#define DTIF$K_DT_ABSDATE 8             /* Absolute date/time               */
#define DTIF$K_DT_TEXT 9                /* Text string                      */
#define DTIF$K_DT_VTEXT 10              /* Varying text string              */
#define DTIF$K_DT_SEGSTR 11             /* Segmented string                 */
/* Bit definitions for DTIF$_CAT_FLAGS.					DTIF conforming */
#define dtif$m_cat_autorecalc 1
#define dtif$m_cat_readonly 2
#define dtif$m_cat_annotation 4
struct cat_flags {
    unsigned dtif$v_cat_autorecalc : 1; /* Auto recalculate                 */
    unsigned dtif$v_cat_readonly : 1;   /* Read only                        */
    unsigned dtif$v_cat_annotation : 1; /* Annotation                       */
    unsigned dtif$v_cat_fill_0 : 13;
    unsigned dtif$v_cat_fill_1 : 16;
    } ;
/* Item codes for Table Definition aggregate.                               */
#define DTIF$_TBL_MAX_COLS 133633       /* Maximum columns		Integer */
#define DTIF$_TBL_MAX_ROWS 133634       /* Maximum rows			Integer */
#define DTIF$_TBL_APPL_PRIVATE 133635   /* Application private		Sequence of DTIF$_NVL */
#define DTIF$_TBL_METADATA 133636       /* Table metadata		DTIF$_TMD */
#define DTIF$_TBL_WINDOWS 133637        /* Window definitions		Sequence of DTIF$_WND */
#define DTIF$_TBL_ROWS 133638           /* Row data			Sequence of DTIF$_ROW */
#define DTIF$_TBL_MAX 133639            /* Maximum code plus 1              */
/* Item codes for Table Metadata aggregate.                                 */
#define DTIF$_TMD_NAME 133889           /* Name				Array of character string */
#define DTIF$_TMD_ID 133890             /* Identifier			Integer */
#define DTIF$_TMD_APPL_PRIVATE 133891   /* Application private		Sequence of DTIF$_NVL */
#define DTIF$_TMD_DESCRIPTION 133892    /* Description			Array of character string */
#define DTIF$_TMD_FLAGS 133893          /* Flags			Longword */
#define DTIF$_TMD_DEFAULT_FMTS 133894   /* Default formats		Sequence of DTIF$_FMI */
#define DTIF$_TMD_COLUMNS 133895        /* Column definitions		Sequence of DTIF$_CAT */
#define DTIF$_TMD_RANGES 133896         /* Range definitions		Sequence of DTIF$_RNG */
#define DTIF$_TMD_SYMBOLS 133897        /* Symbol definitions		Sequence of DTIF$_NVL */
#define DTIF$_TMD_MAX 133898            /* Maximum code plus 1              */
/* Bit definitions for DTIF$_TMD_FLAGS.					DTIF conforming */
#define dtif$m_tmd_autorecalc 1
#define dtif$m_tmd_autoresort 2
#define dtif$m_tmd_calcbycol 4
#define dtif$m_tmd_calcbyrow 8
#define dtif$m_tmd_calcnatural 16
#define dtif$m_tmd_fmtbycol 32
#define dtif$m_tmd_fmtbyrow 64
struct tmd_flags {
    unsigned dtif$v_tmd_autorecalc : 1;
    unsigned dtif$v_tmd_autoresort : 1;
    unsigned dtif$v_tmd_calcbycol : 1;
    unsigned dtif$v_tmd_calcbyrow : 1;
    unsigned dtif$v_tmd_calcnatural : 1;
    unsigned dtif$v_tmd_fmtbycol : 1;
    unsigned dtif$v_tmd_fmtbyrow : 1;
    unsigned dtif$v_tmd_fill_0 : 9;
    unsigned dtif$v_tmd_fill_1 : 16;
    } ;
/* Item codes for Window Definition aggregate.                              */
#define DTIF$_WND_NAME 134145           /* Name				Array of character string */
#define DTIF$_WND_ID 134146             /* Identifier			Integer */
#define DTIF$_WND_APPL_PRIVATE 134147   /* Application private		Sequence of DTIF$_NVL */
#define DTIF$_WND_CARDINAL_NUM 134148   /* Cardinal number		Integer */
#define DTIF$_WND_DESCRIPTION 134149    /* Description			Array of character string */
#define DTIF$_WND_FLAGS 134150          /* Flags			Longword */
#define DTIF$_WND_FORMATS 134151        /* Format definitions		Sequence of DTIF$_FMI */
#define DTIF$_WND_RANGES 134152         /* Range definitions		Sequence of DTIF$_RNG */
#define DTIF$_WND_ACTIVE_LOC 134153     /* Active location		DTIF$_CCD */
#define DTIF$_WND_MAX 134154            /* Maximum code plus 1              */
/* Bit definitions for DTIF$_WND_FLAGS.					DTIF conforming */
#define dtif$m_wnd_active 1
#define dtif$m_wnd_hidden 2
#define dtif$m_wnd_formula_hidden 4
#define dtif$m_wnd_value_hidden 8
#define dtif$m_wnd_colhdr_hidden 16
#define dtif$m_wnd_rowhdr_hidden 32
#define dtif$m_wnd_lines_hidden 64
struct wnd_flags {
    unsigned dtif$v_wnd_active : 1;
    unsigned dtif$v_wnd_hidden : 1;
    unsigned dtif$v_wnd_formula_hidden : 1;
    unsigned dtif$v_wnd_value_hidden : 1;
    unsigned dtif$v_wnd_colhdr_hidden : 1;
    unsigned dtif$v_wnd_rowhdr_hidden : 1;
    unsigned dtif$v_wnd_lines_hidden : 1;
    unsigned dtif$v_wnd_fill_0 : 9;
    unsigned dtif$v_wnd_fill_1 : 16;
    } ;
/* Item codes for Row Definition aggregate.                                 */
#define DTIF$_ROW_NUM 134401            /* Row number			Integer */
#define DTIF$_ROW_APPL_PRIVATE 134402   /* Application private		Sequence of DTIF$_NVL */
#define DTIF$_ROW_FORMATS 134403        /* Format definitions		Sequence of DTIF$_FMI */
#define DTIF$_ROW_FLAGS 134404          /* Flags			Longword */
#define DTIF$_ROW_CELLS 134405          /* Cell data			Sequence of DTIF$_CLD */
#define DTIF$_ROW_MAX 134406            /* Maximum code plus 1              */
/* Bit definitions for DTIF$_ROW_FLAGS.					DTIF conforming */
#define dtif$m_row_annotation 1
struct row_flags {
    unsigned dtif$v_row_annotation : 1;
    unsigned dtif$v_row_fill_0 : 15;
    unsigned dtif$v_row_fill_1 : 16;
    } ;
/* Item codes for Cell Data aggregate.                                      */
#define DTIF$_CLD_COL_NUM 134657        /* Column number		Integer */
#define DTIF$_CLD_STATE 134658          /* State			Enumeration */
#define DTIF$_CLD_DESCRIPTION 134659    /* Description			Array of character string */
#define DTIF$_CLD_APPL_PRIVATE 134660   /* Application private		Sequence of DTIF$_NVL */
#define DTIF$_CLD_FORMATS 134661        /* Format definitions		Sequence of DTIF$_FMI */
#define DTIF$_CLD_VALUE_C 134662        /* Cell value			Enumeration */
#define DTIF$_CLD_VALUE 134663          /*				Variable */
#define DTIF$_CLD_FORMULA_CFE 134664    /* Cell formula			CFE$_EXP */
#define DTIF$_CLD_MAX 134665            /* Maximum code plus 1              */
/* Values of DTIF$_CLD_STATE.						DTIF conforming */
#define DTIF$K_CS_ISVALUE 0
#define DTIF$K_CS_ISNULL 1
#define DTIF$K_CS_ISERROR 2
#define DTIF$K_CS_ISNOVALUE 3
#define DTIF$K_CS_ISUNDERFLOW 10
#define DTIF$K_CS_ISOVERFLOW 11
#define DTIF$K_CS_ISUNDEFREF 12
#define DTIF$K_CS_ISDIVZERO 13
#define DTIF$K_CS_ISRECURSIVE 14
/* Item codes for Varying Text aggregate.                                   */
#define DTIF$_VTX_VTEXT_LEN 134913      /* Varying text length		Integer */
#define DTIF$_VTX_VTEXT_STR 134914      /* Varying text string		Character string */
#define DTIF$_VTX_MAX 134915            /* Maximum code plus 1              */
/* Item codes for Array Definition aggregate.                               */
#define DTIF$_ARD_DESCRIPTION 135169    /* Description			String */
#define DTIF$_ARD_ELEM_TYPE_SIZE_C 135170 /* Array element type size	Enumeration */
#define DTIF$_ARD_ELEM_TYPE_SIZE 135171 /*				Variable */
#define DTIF$_ARD_X_DIMENSION 135172    /* X dimension			Integer */
#define DTIF$_ARD_Y_DIMENSION 135173    /* Y dimension			Integer */
#define DTIF$_ARD_Z_DIMENSION 135174    /* Z dimension			Integer */
#define DTIF$_ARD_VALUES 135175         /* Values			String */
#define DTIF$_ARD_MAX 135176            /* Maximum code plus 1              */
/* Values of DTIF$_ARD_ELEM_TYPE_SIZE_C.                                    */
#define DTIF$K_STD_TYPE 0               /* Standard type size		Enumeration */
#define DTIF$K_VAR_TYPE 1               /* Variable type size		Integer */
/* Values of DTIF$_ARD_ELEM_TYPE_SIZE for DTIF$K_STD_TYPE.		DTIF conforming */
#define DTIF$K_ELEM_WORD 0              /* Word                             */
#define DTIF$K_ELEM_LONG 1              /* Longword                         */
#define DTIF$K_ELEM_FFLOAT 2            /* VAX F-floating                   */
#define DTIF$K_ELEM_DFLOAT 3            /* VAX D-floating                   */
#define DTIF$K_ELEM_GFLOAT 4            /* VAX G-floating                   */
#define DTIF$K_ELEM_HFLOAT 5            /* VAX H-floating                   */
/* Item codes for Complex Float aggregate.                                  */
#define DTIF$_CFT_REAL_PART 135425      /* Real part			General floating point */
#define DTIF$_CFT_IMAGINARY_PART 135426 /* Imaginary part 		General floating point */
#define DTIF$_CFT_MAX 135427            /* Maximum code plus 1              */
/* Item codes for Format Information aggregate.                             */
#define DTIF$_FMI_WINDOW_ID 135681      /* Window ID			Integer */
#define DTIF$_FMI_C 135682              /* Format choice		Enumeration */
#define DTIF$_FMI_NUM_DATATYPE 135683   /* Numeric data type		Longword */
#define DTIF$_FMI_NUM_C 135684          /* Numeric format		Enumeration */
#define DTIF$_FMI_NUMSTD_TYPE 135685    /* Numeric standard type	Enumeration */
#define DTIF$_FMI_NUMSTD_DIGITS 135686  /* Numeric standard digits	Integer */
#define DTIF$_FMI_NUMSTD_FRAC 135687    /* Numeric standard fraction	Integer */
#define DTIF$_FMI_NUMEDS_EDITSTR 135688 /* Numeric edit string		ESF$_EDS */
#define DTIF$_FMI_NUMEID_EDITSTR_ID 135689 /* Numeric edit string index	Integer */
#define DTIF$_FMI_NUM_RNDTRUNC 135690   /* Numeric rounding		Enumeration */
#define DTIF$_FMI_TXT_C 135691          /* Text format			Enumeration */
#define DTIF$_FMI_TXTSTD_TYPE 135692    /* Text standard type		Enumeration */
#define DTIF$_FMI_TXTEDS_EDITSTR 135693 /* Text edit string		ESF$_EDS */
#define DTIF$_FMI_TXTEID_EDITSTR_ID 135694 /* Text edit string index	Integer */
#define DTIF$_FMI_DAT_C 135695          /* Date format			Enumeration */
#define DTIF$_FMI_DATSTD_TYPE 135696    /* Date standard type		Enumeration */
#define DTIF$_FMI_DATSTD_ORDER 135697   /* Date standard order		Enumeration */
#define DTIF$_FMI_DATEDS_EDITSTR 135698 /* Date edit string		ESF$_EDS */
#define DTIF$_FMI_DATEID_EDITSTR_ID 135699 /* Date edit string index	Integer */
#define DTIF$_FMI_FLAGS 135700          /* Flags			Longword */
#define DTIF$_FMI_WIDTH 135701          /* Width			Integer */
#define DTIF$_FMI_LANG_ID 135702        /* Language index		Integer */
#define DTIF$_FMI_DIRECTION 135703      /* Direction			Enumeration */
#define DTIF$_FMI_UNIT_DESC 135704      /* Units description		Array of character string */
#define DTIF$_FMI_ALIGNMENT 135705      /* Alignment			Enumeration */
#define DTIF$_FMI_BORDER 135706         /* Border			Longword */
#define DTIF$_FMI_MAX 135707            /* Maximum code plus 1              */
/* Values of DTIF$_FMI_C.                                                   */
#define DTIF$K_NUMERIC_FORMAT 0         /* Numeric format		DTIF$_FMI_NUM_DATATYPE to DTIF$_FMI_NUM_RNDTRUNC */
#define DTIF$K_TEXT_FORMAT 1            /* Text format			DTIF$_FMI_TXT_C to DTIF$_FMI_TXTEID_EDITSTR_ID */
#define DTIF$K_DATE_FORMAT 2            /* Date format			DTIF$_FMI_DAT_C to DTIF$_FMI_DATEID_EDITSTR_ID */
/* Bit definitions for DTIF$_FMI_NUM_DATATYPE.				DTIF conforming */
#define dtif$m_fmi_num_all 1
#define dtif$m_fmi_num_integer 2
#define dtif$m_fmi_num_float 4
struct fmi_num_datatype {
    unsigned dtif$v_fmi_num_all : 1;
    unsigned dtif$v_fmi_num_integer : 1;
    unsigned dtif$v_fmi_num_float : 1;
    unsigned dtif$v_fmi_fill_0 : 13;
    unsigned dtif$v_fmi_fill_1 : 16;
    } ;
/* Values of DTIF$K_FMI_NUM_C.                                              */
#define DTIF$K_NUM_STANDARD 0           /* Numeric standard format	DTIF$_FMI_NUMSTD_TYPE to DTIF$_FMI_NUMSTD_FRAC */
#define DTIF$K_NUM_EDITSTR 1            /* Numeric edit string		DTIF$_FMI_NUMEDS_EDITSTR */
#define DTIF$K_NUM_EDITSTR_ID 2         /* Numeric edit string index	DTIF$_FMI_NUMEID_EDITSTR_ID */
/* Values of DTIF$K_FMI_NUMSTD_TYPE.					DTIF conforming */
#define DTIF$K_NUMSTD_GENERAL 0         /* General format                   */
#define DTIF$K_NUMSTD_INTEGER 1         /* Integer format                   */
#define DTIF$K_NUMSTD_FIXEDPT 2         /* Fixed point format               */
#define DTIF$K_NUMSTD_SCIENTIFIC 3      /* Scientific format                */
#define DTIF$K_NUMSTD_MONEY 4           /* Money format                     */
#define DTIF$K_NUMSTD_COMMA 5           /* Comma format                     */
#define DTIF$K_NUMSTD_PERCENT 6         /* Percent format                   */
#define DTIF$K_NUMSTD_PHONE 7           /* Phone format                     */
#define DTIF$K_NUMSTD_BAR 8             /* Bar format                       */
#define DTIF$K_NUMSTD_TEXT 9            /* Text format                      */
/* Values of DTIF$K_FMI_NUM_RNDTRUNC.					DTIF conforming */
#define DTIF$K_NUM_ROUND 0              /* Round                            */
#define DTIF$K_NUM_TRUNCATE 1           /* Truncate                         */
/* Values of DTIF$K_FMI_TXT_C.                                              */
#define DTIF$K_TXT_STANDARD 0           /* Text standard format		DTIF$_FMI_TXTSTD_TYPE */
#define DTIF$K_TXT_EDITSTR 1            /* Text edit string		DTIF$_FMI_TXTEDS_EDITSTR */
#define DTIF$K_TXT_EDITSTR_ID 2         /* Text edit string index	DTIF$_FMI_TXTEID_EDITSTR_ID */
/* Values of DTIF$_FMI_TXTSTD_TYPE.					DTIF conforming */
#define DTIF$K_TXTSTD_PHONE 0           /* Telephone                        */
#define DTIF$K_TXTSTD_TEXT 1            /* Text                             */
#define DTIF$K_TXTSTD_REPEAT 2          /* Repeat                           */
/* Values of DTIF$K_FMI_DAT_C.                                              */
#define DTIF$K_DAT_STANDARD 0           /* Date standard format		DTIF$_FMI_DATSTD_TYPE to DTIF$_FMI_DATSTD_ORDER */
#define DTIF$K_DAT_EDITSTR 1            /* Date edit string		DTIF$_FMI_DATEDS_EDITSTR */
#define DTIF$K_DAT_EDITSTR_ID 2         /* Date edit string index	DTIF$_FMI_DATEID_EDITSTR_ID */
/* Values of DTIF$_FMI_DATSTD_TYPE.					DTIF conforming */
#define DTIF$K_DATSTD_DATEONLY 0        /* Date only                        */
#define DTIF$K_DATSTD_TIMEONLY 1        /* Time only                        */
#define DTIF$K_DATSTD_DATEANDTIME 2     /* Date and time                    */
/* Values of DTIF$_FMI_DATSTD_ORDER.					DTIF conforming */
#define DTIF$K_DATSTD_MDY 0             /* Month day year                   */
#define DTIF$K_DATSTD_DMY 1             /* Day month year                   */
/* Bit definitions for DTIF$_FMI_FLAGS.					DTIF conforming */
#define dtif$m_fmi_readonly 1
#define dtif$m_fmi_noreadonly 2
#define dtif$m_fmi_bold 4
#define dtif$m_fmi_nobold 8
#define dtif$m_fmi_italic 16
#define dtif$m_fmi_noitalic 32
#define dtif$m_fmi_underline 64
#define dtif$m_fmi_nounderline 128
#define dtif$m_fmi_valuehidden 256
#define dtif$m_fmi_novaluehidden 512
#define dtif$m_fmi_formulahidden 1024
#define dtif$m_fmi_noformulahidden 2048
#define dtif$m_fmi_running 4096
#define dtif$m_fmi_norunning 8192
struct fmi_flags {
    unsigned dtif$v_fmi_readonly : 1;
    unsigned dtif$v_fmi_noreadonly : 1;
    unsigned dtif$v_fmi_bold : 1;
    unsigned dtif$v_fmi_nobold : 1;
    unsigned dtif$v_fmi_italic : 1;
    unsigned dtif$v_fmi_noitalic : 1;
    unsigned dtif$v_fmi_underline : 1;
    unsigned dtif$v_fmi_nounderline : 1;
    unsigned dtif$v_fmi_valuehidden : 1;
    unsigned dtif$v_fmi_novaluehidden : 1;
    unsigned dtif$v_fmi_formulahidden : 1;
    unsigned dtif$v_fmi_noformulahidden : 1;
    unsigned dtif$v_fmi_running : 1;
    unsigned dtif$v_fmi_norunning : 1;
    unsigned dtif$v_fmi_fill_00 : 2;
    unsigned dtif$v_fmi_fill_2 : 16;
    } ;
/* Values of DTIF$_FMI_DIRECTION.					DTIF conforming */
#define DTIF$K_DIR_OPPOSITE 0           /* Opposite direction               */
/* Values of DTIF$_FMI_ALIGNMENT.					DTIF conforming */
#define DTIF$K_ALIGN_LEFT 0             /* Left alignment                   */
#define DTIF$K_ALIGN_CENTER 1           /* Center alignment                 */
#define DTIF$K_ALIGN_RIGHT 2            /* Right alignment                  */
/* Bit definitions for DTIF$_FMI_BORDER.				DTIF conforming */
#define dtif$m_fmi_border_left 1
#define dtif$m_fmi_border_noleft 2
#define dtif$m_fmi_border_top 4
#define dtif$m_fmi_border_notop 8
#define dtif$m_fmi_border_right 16
#define dtif$m_fmi_border_noright 32
#define dtif$m_fmi_border_bottom 64
#define dtif$m_fmi_border_nobottom 128
struct fmi_border {
    unsigned dtif$v_fmi_border_left : 1;
    unsigned dtif$v_fmi_border_noleft : 1;
    unsigned dtif$v_fmi_border_top : 1;
    unsigned dtif$v_fmi_border_notop : 1;
    unsigned dtif$v_fmi_border_right : 1;
    unsigned dtif$v_fmi_border_noright : 1;
    unsigned dtif$v_fmi_border_bottom : 1;
    unsigned dtif$v_fmi_border_nobottom : 1;
    unsigned dtif$v_fmi_fill_000 : 8;
    unsigned dtif$v_fmi_fill_3 : 16;
    } ;
/* Item codes for Cell Coordinates aggregate.                               */
#define DTIF$_CCD_ROW 135937            /* Row number			Integer */
#define DTIF$_CCD_COLUMN 135938         /* Column number		Integer */
#define DTIF$_CCD_FLAGS 135939          /* Flags			Enumeration */
#define DTIF$_CCD_MAX 135940            /* Maximum code plus 1              */
/* Values of DTIF$_CCD_FLAGS.						DTIF conforming */
#define DTIF$K_RELROW_RELCOL 0          /* Relative row, relative column    */
#define DTIF$K_RELROW_ABSCOL 1          /* Relative row, absolute column    */
#define DTIF$K_ABSROW_RELCOL 2          /* Absolute row, relative column    */
#define DTIF$K_ABSROW_ABSCOL 3          /* Absolute row, absolute column    */
/* Item codes for Range Definition aggregate.                               */
#define DTIF$_RNG_NAME 136193           /* Name				Array of character string */
#define DTIF$_RNG_TYPE 136194           /* Type				Enumeration */
#define DTIF$_RNG_REGION 136195         /* Region			Sequence of DTIF$_CLR, DTIF$_RWR, DTIF$_COR, DTIF$_NMR */
#define DTIF$_RNG_SORT_KEYNUM 136196    /* Sort key number		Integer */
#define DTIF$_RNG_MAX 136197            /* Maximum code plus 1              */
/* Values of DTIF$_RNG_TYPE.						DTIF conforming */
#define DTIF$K_RT_NAMED_RANGE 0         /* Named area                       */
#define DTIF$K_RT_VIEW_RANGE 1          /* View definition                  */
#define DTIF$K_RT_COL_TITLE 2           /* Column title section             */
#define DTIF$K_RT_ROW_TITLE 3           /* Row title section                */
#define DTIF$K_RT_DISPLAY_DATA 4        /* Displayed window range           */
#define DTIF$K_RT_DATA_RANGE 5          /* Maximum window range             */
#define DTIF$K_RT_SORT_RANGE 6          /* Sort range                       */
/* Item codes for Cell Range aggregate.                                     */
#define DTIF$_CLR_RANGE_BEGIN 136449    /* Beginning cell coordinates	DTIF$_CCD */
#define DTIF$_CLR_RANGE_END 136450      /* Ending cell coordinates	DTIF$_CCD */
#define DTIF$_CLR_MAX 136451            /* Maximum code plus 1              */
/* Item codes for Row Range aggregate.                                      */
#define DTIF$_RWR_ROW_BEGIN 136705      /* Beginning row number		Integer */
#define DTIF$_RWR_ROW_END 136706        /* Ending row number		Integer */
#define DTIF$_RWR_MAX 136707            /* Maximum code plus 1              */
/* Item codes for Column Range aggregate.                                   */
#define DTIF$_COR_COL_BEGIN 136961      /* Beginning column number	Integer */
#define DTIF$_COR_COL_END 136962        /* Ending column number		Integer */
#define DTIF$_COR_MAX 136963            /* Maximum code plus 1              */
/* Item codes for Named Range aggregate.                                    */
#define DTIF$_NMR_NAMEDRANGE 137217     /* Named range			Array of character string */
#define DTIF$_NMR_MAX 137218            /* Maximum code plus 1              */
/* Item codes for External aggregate.                                       */
#define DTIF$_EXT_DIRECT_REFERENCE 137473 /* Direct reference		Object identifier */
#define DTIF$_EXT_INDIRECT_REFERENCE 137474 /* Indirect reference		Integer */
#define DTIF$_EXT_DATA_VALUE_DESCRIPTOR 137475 /* Data value descriptor	String */
#define DTIF$_EXT_ENCODING_C 137476     /* Encoding			Enumeration */
#define DTIF$_EXT_ENCODING 137477       /* 				Variable */
#define DTIF$_EXT_ENCODING_L 137478     /*     Length (on input)	Integer */
#define DTIF$_EXT_MAX 137479            /* Maximum code plus 1              */
/* Values of DTIF$_EXT_ENCODING_C.                                          */
#define DTIF$K_DOCUMENT_ENCODING 0      /* Nested document		Document root aggregate */
#define DTIF$K_DDIS_ENCODING 1          /* Nested document		DDIS encoding */
#define DTIF$K_OCTET_ENCODING 2         /* Octet aligned		String */
#define DTIF$K_ARBITRARY_ENCODING 3     /* Arbitrary			Bit string */
/* Aggregate type codes for ESF (Edit String Format).                       */
#define ESF$_EDS 769                    /* Edit string                      */
#define ESF$_RPT 770                    /* Repeat                           */
#define ESF$_TXS 771                    /* Text string                      */
#define ESF$_NVL 772                    /* Named value                      */
#define ESF$_DAT 773                    /* Date and time                    */
#define ESF$_EXT 774                    /* External                         */
#define ESF$_MAX 775                    /* Maximum code plus 1              */
/* Item codes for all aggregates.  ESF$_AGGREGATE_TYPE is read-only.        */
#define ESF$_USER_CONTEXT 1             /* User context			Longword */
#define ESF$_AGGREGATE_TYPE 2           /* Aggregate type code		Word */
#define ESF$_ALL_MAX 3                  /* Maximum code plus 1              */
/* Item codes for Edit String aggregate.                                    */
#define ESF$_EDS_MAJOR_VERSION 196865   /* Major version		Integer */
#define ESF$_EDS_MINOR_VERSION 196866   /* Minor version		Integer */
#define ESF$_EDS_EDIT_STRING_C 196867   /* Edit string			Array of enumeration */
#define ESF$_EDS_EDIT_STRING 196868     /*				Array of variable */
#define ESF$_EDS_MAX 196869             /* Maximum code plus 1              */
/* Current values for major and minor encoding version.  Should be omitted when the edit string is embedded in a DTIF document. */
#define ESF$K_MAJOR_VERSION 1
#define ESF$K_MINOR_VERSION 0
/* Values of ESF$_EDS_EDIT_STRING_C and ESF$_RPT_SEQ_C.                     */
#define ESF$K_EDS_ALPHABETIC 0          /* Alphabetic			None */
#define ESF$K_EDS_AM_PM 1               /* AM PM			None */
#define ESF$K_EDS_ANY_CHAR 2            /* Any character		None */
#define ESF$K_EDS_ANY_CASE 3            /* Any case			None */
#define ESF$K_EDS_BINARY_DIGIT 4        /* Binary digit			None */
#define ESF$K_EDS_DIGIT_SEP 5           /* Digit separator		None */
#define ESF$K_EDS_DAY_NUMBER 6          /* Day number			None */
#define ESF$K_EDS_DECIMAL_DIGIT 7       /* Decimal digit		None */
#define ESF$K_EDS_RADIX_POINT 8         /* Radix point			None */
#define ESF$K_EDS_ENCODED_MINUS 9       /* Encoded minus		None */
#define ESF$K_EDS_ENCODED_PLUS 10       /* Encoded plus			None */
#define ESF$K_EDS_ENCODED_SIGN 11       /* Encoded sign			None */
#define ESF$K_EDS_EXPONENT 12           /* Exponent			None */
#define ESF$K_EDS_ZERO_REPLACE 13       /* Zero replace			ESF$_TXS */
#define ESF$K_EDS_CURRENCY 14           /* Currency			None */
#define ESF$K_EDS_MINUS 15              /* Minus			None */
#define ESF$K_EDS_PLUS 16               /* Plus				None */
#define ESF$K_EDS_SIGN 17               /* Sign				None */
#define ESF$K_EDS_FLOAT_BLANK_SUPR 18   /* Float blank suppress		None */
#define ESF$K_EDS_FRACTION_SECOND 19    /* Fraction second		None */
#define ESF$K_EDS_HEX_DIGIT 20          /* Hex digit			None */
#define ESF$K_EDS_HOUR_12 21            /* Hour (12 hour system)	None */
#define ESF$K_EDS_HOUR_24 22            /* Hour (24 hour system)	None */
#define ESF$K_EDS_JULIAN_DIGIT 23       /* Julian digit			None */
#define ESF$K_EDS_LOGICAL_CHAR 24       /* Logical character		None */
#define ESF$K_EDS_LONG_TEXT 25          /* Long text			None */
#define ESF$K_EDS_LOWERCASE 26          /* Lowercase			None */
#define ESF$K_EDS_MINUS_LITERAL 27      /* Minus literal begin		ESF$_TXS */
#define ESF$K_EDS_MINUS_LIT_END 28      /* Minus literal end		ESF$_TXS */
#define ESF$K_EDS_MINUTE 29             /* Minute			None */
#define ESF$K_EDS_MONTH_NAME 30         /* Month name			None */
#define ESF$K_EDS_MONTH_NUMBER 31       /* Month number			None */
#define ESF$K_EDS_OCTAL_DIGIT 32        /* Octal digit			None */
#define ESF$K_EDS_PLUS_LITERAL 33       /* Plus literal			ESF$_TXS */
#define ESF$K_EDS_REVERSE 34            /* Reverse			None */
#define ESF$K_EDS_SECOND 35             /* Second			None */
#define ESF$K_EDS_STR_LITERAL 36        /* String literal		ESF$_TXS */
#define ESF$K_EDS_MISSING_SEP 37        /* Missing separator		None */
#define ESF$K_EDS_UPPERCASE 38          /* Uppercase			None */
#define ESF$K_EDS_WEEKDAYNAME 39        /* Weekday name			None */
#define ESF$K_EDS_YEAR 40               /* Year				None */
#define ESF$K_EDS_APPL_PRIVATE 41       /* Application private		Sequence of ESF$_NVL */
#define ESF$K_EDS_DIGIT_SEP_LIT 42      /* Digit separator literal	ESF$_TXS */
#define ESF$K_EDS_RADIX_POINT_LIT 43    /* Radix point literal		ESF$_TXS */
#define ESF$K_EDS_CURRENCY_LIT 44       /* Currency sign literal	ESF$_TXS */
#define ESF$K_EDS_REPEAT 45             /* Repeat			ESF$_RPT (not for ESF$_RPT_SEQ_C) */
/* Item codes for Repeat aggregate.                                         */
#define ESF$_RPT_COUNT 197121           /* Repeat count			Integer */
#define ESF$_RPT_SEQ_C 197122           /* Repeat sequence		Enumeration */
#define ESF$_RPT_SEQ 197123             /*				Variable */
#define ESF$_RPT_MAX 197124             /* Maximum code plus 1              */
/* Item codes for Text String aggregate.                                    */
#define ESF$_TXS_TEXT_STRING 197377     /* Text string			Array of character string */
#define ESF$_TXS_MAX 197378             /* Maximum code plus 1              */
/* Item codes for Named Value aggregate.                                    */
#define ESF$_NVL_NAME 197633            /* Value name			String */
#define ESF$_NVL_VALUE_C 197634         /* Value data			Enumeration */
#define ESF$_NVL_VALUE 197635           /* 				Variable */
#define ESF$_NVL_MAX 197636             /* Maximum code plus 1              */
/* Values of ESF$_NVL_VALUE_C.                                              */
#define ESF$K_VALUE_BOOLEAN 0           /*				Boolean */
#define ESF$K_VALUE_INTEGER 1           /*				Integer */
#define ESF$K_VALUE_TEXT 2              /*				Array of character string */
#define ESF$K_VALUE_GENERAL 3           /*				String */
#define ESF$K_VALUE_LIST 4              /*				Sequence of ESF$_NVL */
#define ESF$K_VALUE_EXTERNAL 5          /*				ESF$_EXT */
#define ESF$K_VALUE_FLOAT 6             /*				General floating point */
#define ESF$K_VALUE_DATE 7              /*				ESF$_DAT */
#define ESF$K_VALUE_EXPR 8              /*				CFE$_EXP */
/* Item codes for Date and Time aggregate.                                  */
#define ESF$_DAT_DATETIME 197889        /* Date and time		String */
#define ESF$_DAT_TIME_DIFF_C 197890     /* Time difference		Enumeration */
#define ESF$_DAT_TIME_DIFF 197891       /*				Variable */
#define ESF$_DAT_MAX 197892             /* Maximum code plus 1              */
/* Values of ESF$_DAT_TIME_DIFF_C.                                          */
#define ESF$K_UTC_TIME 0                /* UTC time			None */
#define ESF$K_PLUS_DIFF 1               /* Positive difference		String */
#define ESF$K_NEG_DIFF 2                /* Negative difference		String */
/* Item codes for External aggregate.                                       */
#define ESF$_EXT_DIRECT_REFERENCE 198145 /* Direct reference		Object identifier */
#define ESF$_EXT_INDIRECT_REFERENCE 198146 /* Indirect reference		Integer */
#define ESF$_EXT_DATA_VALUE_DESCRIPTOR 198147 /* Data value descriptor	String */
#define ESF$_EXT_ENCODING_C 198148      /* Encoding			Enumeration */
#define ESF$_EXT_ENCODING 198149        /* 				Variable */
#define ESF$_EXT_ENCODING_L 198150      /*     Length (on input)	Integer */
#define ESF$_EXT_MAX 198151             /* Maximum code plus 1              */
/* Values of ESF$_EXT_ENCODING_C.                                           */
#define ESF$K_DOCUMENT_ENCODING 0       /* Nested document		Document root aggregate */
#define ESF$K_DDIS_ENCODING 1           /* Nested document		DDIS encoding */
#define ESF$K_OCTET_ENCODING 2          /* Octet aligned		String */
#define ESF$K_ARBITRARY_ENCODING 3      /* Arbitrary			Bit string */
/* Aggregate type codes for CFE (Canonical Format Expressions).             */
#define CFE$_EXP 1025                   /* Expression                       */
#define CFE$_EXL 1026                   /* Expression list                  */
#define CFE$_SLL 1027                   /* Selector list                    */
#define CFE$_CFT 1028                   /* Complex float                    */
#define CFE$_DAT 1029                   /* Date and time                    */
#define CFE$_TXC 1030                   /* Text choice                      */
#define CFE$_VTX 1031                   /* Varying text                     */
#define CFE$_FRF 1032                   /* Field reference                  */
#define CFE$_PEX 1033                   /* Parenthesized expression         */
#define CFE$_PFE 1034                   /* Private function expression      */
#define CFE$_STF 1035                   /* String format                    */
#define CFE$_STP 1036                   /* String pretty                    */
#define CFE$_NPM 1037                   /* Named parameter                  */
#define CFE$_CCD 1038                   /* Cell coordinates                 */
#define CFE$_CLR 1039                   /* Cell range                       */
#define CFE$_RWR 1040                   /* Row range                        */
#define CFE$_COR 1041                   /* Column range                     */
#define CFE$_MAX 1042                   /* Maximum code plus one            */
/* Item codes for all aggregates.  CFE$_AGGREGATE_TYPE is read-only.        */
#define CFE$_USER_CONTEXT 1             /* User context			Longword */
#define CFE$_AGGREGATE_TYPE 2           /* Aggregate type code		Word */
#define CFE$_ALL_MAX 3                  /* Maximum code plus 1              */
/* Item codes for Expression aggregate.                                     */
#define CFE$_EXP_MAJOR_VERSION 262401   /* Major version		Integer */
#define CFE$_EXP_MINOR_VERSION 262402   /* Minor version		Integer */
#define CFE$_EXP_LIST 262403            /* Expression list		Sequence of CFE$_EXL */
#define CFE$_EXP_MAX 262404             /* Maximum code plus 1              */
/* Current values for major and minor encoding version.  Should be omitted when the expression is embedded in a DTIF document. */
#define CFE$K_MAJOR_VERSION 1
#define CFE$K_MINOR_VERSION 0
/* Item codes for Expression List aggregate.                                */
#define CFE$_EXL_EXPR_C 262657          /* Expression choice		Enumeration */
#define CFE$_EXL_EXPR 262658            /*				Variable */
#define CFE$_EXL_MAX 262659             /* Maximum code plus 1              */
/* Values of CFE$_EXL_EXPR_C.                                               */
#define CFE$K_LIT_INTEGER 0             /* Literal integer		Integer */
#define CFE$K_LIT_FLOAT 1               /* Literal float		General floating point */
#define CFE$K_LIT_TEXT 2                /* Literal text			CFE$_TXC */
#define CFE$K_LIT_DATE 3                /* Literal date			CFE$_DAT */
#define CFE$K_LIT_SCALED_INTEGER 4      /* Literal scaled integer	Scaled integer */
#define CFE$K_LIT_COMPLEX_FLOAT 5       /* Literal complex float	CFE$_CFT */
#define CFE$K_LIT_VTEXT 6               /* Literal varying text		CFE$_VTX */
#define CFE$K_PARENTHESIZED 7           /* Parenthesized expression	CFE$_PEX */
#define CFE$K_CELL_COORD 8              /* Cell coordinates		CFE$_CCD */
#define CFE$K_CELL_RANGE 9              /* Cell range			CFE$_CLR */
#define CFE$K_ROW_RANGE 10              /* Row range			CFE$_RWR */
#define CFE$K_COL_RANGE 11              /* Column range			CFE$_COR */
#define CFE$K_NAMED_RANGE 12            /* Named range			Array of character string */
#define CFE$K_COL_NUM 13                /* Column number		Integer */
#define CFE$K_ROW_NUM 14                /* Row number			Integer */
#define CFE$K_COL_NAME 15               /* Column name			String */
#define CFE$K_NEGATE 16                 /* Negate			Sequence of CFE$_EXL */
#define CFE$K_ADD 17                    /* Add				Sequence of CFE$_EXL */
#define CFE$K_SUBTRACT 18               /* Subtract			Sequence of CFE$_EXL */
#define CFE$K_DIVIDE 19                 /* Divide			Sequence of CFE$_EXL */
#define CFE$K_MULTIPLY 20               /* Multiply			Sequence of CFE$_EXL */
#define CFE$K_POWER 21                  /* Raise to a power		Sequence of CFE$_EXL */
#define CFE$K_EXPONENT 22               /* Exponent			Sequence of CFE$_EXL */
#define CFE$K_IF_THEN_ELSE 23           /* If-then-else			Sequence of CFE$_EXL */
#define CFE$K_NOT 24                    /* Logical not			Sequence of CFE$_EXL */
#define CFE$K_AND 25                    /* Logical and 			Sequence of CFE$_EXL */
#define CFE$K_OR 26                     /* Logical or			Sequence of CFE$_EXL */
#define CFE$K_EQL 27                    /* Equal			Sequence of CFE$_EXL */
#define CFE$K_GTR 28                    /* Greater than			Sequence of CFE$_EXL */
#define CFE$K_GEQ 29                    /* Greater than or equal	Sequence of CFE$_EXL */
#define CFE$K_LSS 30                    /* Less than			Sequence of CFE$_EXL */
#define CFE$K_LEQ 31                    /* Less than or equal		Sequence of CFE$_EXL */
#define CFE$K_NEQ 32                    /* Not equal			Sequence of CFE$_EXL */
#define CFE$K_BETWEEN 33                /* Between			Sequence of CFE$_EXL */
#define CFE$K_ABS_VALUE 34              /* Absolute value		Sequence of CFE$_EXL */
#define CFE$K_MODULO 35                 /* Modulus			Sequence of CFE$_EXL */
#define CFE$K_SQRT 36                   /* Square root			Sequence of CFE$_EXL */
#define CFE$K_SUM 37                    /* Summation			CFE$_SLL */
#define CFE$K_AVG 38                    /* Average			CFE$_SLL */
#define CFE$K_COUNT 39                  /* Count			CFE$_SLL */
#define CFE$K_MIN 40                    /* Minimum			CFE$_SLL */
#define CFE$K_MAX 41                    /* Maximum			CFE$_SLL */
#define CFE$K_STDEV 42                  /* Standard deviation		CFE$_SLL */
#define CFE$K_VAR 43                    /* Variance			CFE$_SLL */
#define CFE$K_CVT_TO_VALUE 44           /* Convert to value		Sequence of CFE$_EXL */
#define CFE$K_ROUND 45                  /* Round			Sequence of CFE$_EXL */
#define CFE$K_TRUNCATE 46               /* Truncate			Sequence of CFE$_EXL */
#define CFE$K_INT 47                    /* Integerize			Sequence of CFE$_EXL */
#define CFE$K_ISERROR 48                /* Is error			Sequence of CFE$_EXL */
#define CFE$K_ISBLANK 49                /* Is blank			Sequence of CFE$_EXL */
#define CFE$K_ISNULL 50                 /* Is null			Sequence of CFE$_EXL */
#define CFE$K_ISDATE 51                 /* Is date			Sequence of CFE$_EXL */
#define CFE$K_ISNUMBER 52               /* Is number			Sequence of CFE$_EXL */
#define CFE$K_ISSTRING 53               /* Is string			Sequence of CFE$_EXL */
#define CFE$K_ISREF 54                  /* Is referenced		Sequence of CFE$_EXL */
#define CFE$K_STR_CHAR 55               /* String character		Sequence of CFE$_EXL */
#define CFE$K_STR_CODE 56               /* String character code	Sequence of CFE$_EXL */
#define CFE$K_STR_CONCAT 57             /* String concatenate		Sequence of CFE$_EXL */
#define CFE$K_STR_EXTRACT 58            /* String extract		Sequence of CFE$_EXL */
#define CFE$K_STR_FIND 59               /* String find substring	Sequence of CFE$_EXL */
#define CFE$K_STR_FIXED 60              /* String fixed			Sequence of CFE$_EXL */
#define CFE$K_STR_FORMAT 61             /* String edit			CFE$_STF */
#define CFE$K_STR_LEFT 62               /* Extract substring left	Sequence of CFE$_EXL */
#define CFE$K_STR_LENGTH 63             /* String length		Sequence of CFE$_EXL */
#define CFE$K_STR_LOWER 64              /* String lowercase		Sequence of CFE$_EXL */
#define CFE$K_STR_PRETTY 65             /* String pretty		CFE$_STP */
#define CFE$K_STR_PROPER 66             /* String proper		Sequence of CFE$_EXL */
#define CFE$K_STR_REPEAT 67             /* String repeat		Sequence of CFE$_EXL */
#define CFE$K_STR_REPLACE 68            /* String replace		Sequence of CFE$_EXL */
#define CFE$K_STR_REVERSE 69            /* String reverse		Sequence of CFE$_EXL */
#define CFE$K_STR_RIGHT 70              /* Extract substring right	Sequence of CFE$_EXL */
#define CFE$K_STR_TRIM 71               /* String trim			Sequence of CFE$_EXL */
#define CFE$K_STR_UPPER 72              /* String uppercase		Sequence of CFE$_EXL */
#define CFE$K_CHOOSE 73                 /* Choose			Sequence of CFE$_EXL */
#define CFE$K_INDEX 74                  /* Index			Sequence of CFE$_EXL */
#define CFE$K_VLOOKUP 75                /* Vertical lookup		Sequence of CFE$_EXL */
#define CFE$K_HLOOKUP 76                /* Horizontal lookup		Sequence of CFE$_EXL */
#define CFE$K_TABLE 77                  /* Table			Sequence of CFE$_EXL */
#define CFE$K_NAME_DAY 78               /* Date day of the week		Sequence of CFE$_EXL */
#define CFE$K_NAME_MONTH 79             /* Date month name		Sequence of CFE$_EXL */
#define CFE$K_NAME_DAYNUM 80            /* Day of the week		Sequence of CFE$_EXL */
#define CFE$K_NAME_MONTHNUM 81          /* Month name			Sequence of CFE$_EXL */
#define CFE$K_NOW 82                    /* Now				None */
#define CFE$K_TODAY 83                  /* Today			None */
#define CFE$K_TOMORROW 84               /* Tomorrow			None */
#define CFE$K_YESTERDAY 85              /* Yesterday			None */
#define CFE$K_EXT_DAY 86                /* Extract day			Sequence of CFE$_EXL */
#define CFE$K_EXT_MONTH 87              /* Extract month		Sequence of CFE$_EXL */
#define CFE$K_EXT_YEAR 88               /* Extract year			Sequence of CFE$_EXL */
#define CFE$K_EXT_HOUR 89               /* Extract hour			Sequence of CFE$_EXL */
#define CFE$K_EXT_MINUTE 90             /* Extract minute		Sequence of CFE$_EXL */
#define CFE$K_EXT_SECOND 91             /* Extract second		Sequence of CFE$_EXL */
#define CFE$K_DIFF_DAY 92               /* Difference day		Sequence of CFE$_EXL */
#define CFE$K_DIFF_WEEK 93              /* Difference week		Sequence of CFE$_EXL */
#define CFE$K_DIFF_MONTH 94             /* Difference month		Sequence of CFE$_EXL */
#define CFE$K_DIFF_YEAR 95              /* Difference year		Sequence of CFE$_EXL */
#define CFE$K_DIFF_HOUR 96              /* Difference hour		Sequence of CFE$_EXL */
#define CFE$K_DIFF_MIN 97               /* Difference minute		Sequence of CFE$_EXL */
#define CFE$K_DIFF_SEC 98               /* Difference second		Sequence of CFE$_EXL */
#define CFE$K_CVT_TO_DATE 99            /* String to date		Sequence of CFE$_EXL */
#define CFE$K_CVT_TO_TIME 100           /* String to time		Sequence of CFE$_EXL */
#define CFE$K_PLUS_DAYS 101             /* Plus days			Sequence of CFE$_EXL */
#define CFE$K_PLUS_WEEKS 102            /* Plus weeks			Sequence of CFE$_EXL */
#define CFE$K_PLUS_MONTHS 103           /* Plus months			Sequence of CFE$_EXL */
#define CFE$K_PLUS_YEARS 104            /* Plus years			Sequence of CFE$_EXL */
#define CFE$K_PLUS_HOURS 105            /* Plus hours			Sequence of CFE$_EXL */
#define CFE$K_PLUS_MINS 106             /* Plus minutes			Sequence of CFE$_EXL */
#define CFE$K_PLUS_SECS 107             /* Plus seconds			Sequence of CFE$_EXL */
#define CFE$K_ERROR 108                 /* Error			None */
#define CFE$K_NULL 109                  /* Null				None */
#define CFE$K_CUR_ROW 110               /* Current row			None */
#define CFE$K_CUR_COL 111               /* Current column		None */
#define CFE$K_CUR_CELL 112              /* Current cell			None */
#define CFE$K_CELL_ROW 113              /* Row portion of cell name	Sequence of CFE$_EXL */
#define CFE$K_CELL_COL 114              /* Column portion of cell name	Sequence of CFE$_EXL */
#define CFE$K_CELL_NAME 115             /* Constructed cell reference	Sequence of CFE$_EXL */
#define CFE$K_COUNT_ROWS 116            /* Count rows			Sequence of CFE$_EXL */
#define CFE$K_COUNT_COLS 117            /* Count columns		Sequence of CFE$_EXL */
#define CFE$K_CELL_EXTRACT 118          /* Cell extract			Sequence of CFE$_EXL */
#define CFE$K_APPREC 119                /* Appreciation			Sequence of CFE$_EXL */
#define CFE$K_DEP_CROSS 120             /* Depreciation declining balance crossover	Sequence of CFE$_EXL */
#define CFE$K_DEP_DB 121                /* Depreciation declining balance	Sequence of CFE$_EXL */
#define CFE$K_DEP_DDB 122               /* Depreciation double declining balance	Sequence of CFE$_EXL */
#define CFE$K_DEP_SLINE 123             /* Depreciation straight line	Sequence of CFE$_EXL */
#define CFE$K_DEP_SOYD 124              /* Depreciation sum of years	Sequence of CFE$_EXL */
#define CFE$K_DISCOUNT 125              /* Discount			Sequence of CFE$_EXL */
#define CFE$K_FV 126                    /* Future value			Sequence of CFE$_EXL */
#define CFE$K_FVA 127                   /* Future value of annuity	Sequence of CFE$_EXL */
#define CFE$K_FVPV 128                  /* Future value of single payment	Sequence of CFE$_EXL */
#define CFE$K_INTEREST 129              /* Interest payments		Sequence of CFE$_EXL */
#define CFE$K_IRR 130                   /* Internal rate of return	Sequence of CFE$_EXL */
#define CFE$K_MIRR 131                  /* Modified internal rate of return	Sequence of CFE$_EXL */
#define CFE$K_NPV 132                   /* Net present value		Sequence of CFE$_EXL */
#define CFE$K_PAYBACK 133               /* Payback			Sequence of CFE$_EXL */
#define CFE$K_PERPMT 134                /* Number periods to achieve future value	Sequence of CFE$_EXL */
#define CFE$K_PERPV 135                 /* Number periods given present value		Sequence of CFE$_EXL */
#define CFE$K_PMTPV 136                 /* Payment per period given present value	Sequence of CFE$_EXL */
#define CFE$K_PMTFV 137                 /* Payment per period to achieve future value	Sequence of CFE$_EXL */
#define CFE$K_PRINCIPAL 138             /* Principal			Sequence of CFE$_EXL */
#define CFE$K_PVA 139                   /* Present value of annuity	Sequence of CFE$_EXL */
#define CFE$K_PVFV 140                  /* Present value to achieve future value	Sequence of CFE$_EXL */
#define CFE$K_RATE 141                  /* Interest rate		Sequence of CFE$_EXL */
#define CFE$K_LOGEST 142                /* LogEst			Sequence of CFE$_EXL */
#define CFE$K_LSQR 143                  /* Least squares		Sequence of CFE$_EXL */
#define CFE$K_INTEGRATE 144             /* Integrate			Sequence of CFE$_EXL */
#define CFE$K_SIGMA 145                 /* Sigma			Sequence of CFE$_EXL */
#define CFE$K_TREND 146                 /* Trend			Sequence of CFE$_EXL */
#define CFE$K_LIT_TRUE 147              /* Literal true			None */
#define CFE$K_LIT_FALSE 148             /* Literal false		None */
#define CFE$K_LIT_PI 149                /* Literal pi			None */
#define CFE$K_RANDOM_U 150              /* Random number, uniformly distributed		None */
#define CFE$K_DECIMAL_STRING 151        /* Decimal string		String */
#define CFE$K_IN_TABLE 152              /* Field in table			Sequence of CFE$_EXL */
#define CFE$K_SIN 153                   /* Sine				Sequence of CFE$_EXL */
#define CFE$K_COS 154                   /* Cosine			Sequence of CFE$_EXL */
#define CFE$K_TAN 155                   /* Tangent			Sequence of CFE$_EXL */
#define CFE$K_ASIN 156                  /* Arc sine			Sequence of CFE$_EXL */
#define CFE$K_ACOS 157                  /* Arc cosine			Sequence of CFE$_EXL */
#define CFE$K_ATAN 158                  /* Arc tangent			Sequence of CFE$_EXL */
#define CFE$K_ATAN2 159                 /* Arc tangent 2		Sequence of CFE$_EXL */
#define CFE$K_LOG10 160                 /* Common logarithm		Sequence of CFE$_EXL */
#define CFE$K_LOGN 161                  /* Natural logarithm		Sequence of CFE$_EXL */
#define CFE$K_ALOG 162                  /* Antilogarithm		Sequence of CFE$_EXL */
#define CFE$K_FACTORIAL 163             /* Factorial			Sequence of CFE$_EXL */
#define CFE$K_ASL 164                   /* Arithmetic shift left	Sequence of CFE$_EXL */
#define CFE$K_ASR 165                   /* Arithmetic shift right	Sequence of CFE$_EXL */
#define CFE$K_ONES_CMP 166              /* Ones complement		Sequence of CFE$_EXL */
#define CFE$K_SIGN 167                  /* Sign				Sequence of CFE$_EXL */
#define CFE$K_CONTAINS 168              /* Contains substring		Sequence of CFE$_EXL */
#define CFE$K_MATCHES 169               /* Matches			Sequence of CFE$_EXL */
#define CFE$K_STARTS 170                /* String starts with		Sequence of CFE$_EXL */
#define CFE$K_UNARY_PLUS 171            /* Unary plus			Sequence of CFE$_EXL */
#define CFE$K_PERCENT 172               /* Percent			Sequence of CFE$_EXL */
#define CFE$K_ISNOT_AVAIL 173           /* Is not available		Sequence of CFE$_EXL */
#define CFE$K_ISNOT_CALC 174            /* Is not calculatable		Sequence of CFE$_EXL */
#define CFE$K_NOT_AVAIL 175             /* Not available		None */
#define CFE$K_NOT_CALC 176              /* Not calculatable		None */
#define CFE$K_CELL_INDIRECT 177         /* Cell indirection		Sequence of CFE$_EXL */
#define CFE$K_PERFV 178                 /* Periods to achieve future value	Sequence of CFE$_EXL */
#define CFE$K_CURRENT_VALUE 179         /* Current value		None */
#define CFE$K_IDENTIFIER 180            /* Identifier			CFE$_TXC */
#define CFE$K_PRIVATE_FUNCTION 181      /* Private function		CFE$_PFE */
#define CFE$K_FIELD_REFERENCE 182       /* Field reference		CFE$_FRF */
/* Item codes for Selector List aggregate.                                  */
#define CFE$_SLL_CRITERIA 262913        /* Criteria			Sequence of CFE$_EXL */
#define CFE$_SLL_SELECTION 262914       /* Selection			Sequence of CFE$_EXL */
#define CFE$_SLL_MAX 262915             /* Maximum code plus 1              */
/* Item codes for Complex Float aggregate.                                  */
#define CFE$_CFT_REAL_PART 263169       /* Real part			General floating point */
#define CFE$_CFT_IMAGINARY_PART 263170  /* Imaginary part		General floating point */
#define CFE$_CFT_MAX 263171             /* Maximum code plus 1              */
/* Item codes for Date and Time aggregate.                                  */
#define CFE$_DAT_DATETIME 263425        /* Date and time		String */
#define CFE$_DAT_TIME_DIFF_C 263426     /* Time difference		Enumeration */
#define CFE$_DAT_TIME_DIFF 263427       /*				Variable */
#define CFE$_DAT_MAX 263428             /* Maximum code plus 1              */
/* Values of CFE$_DAT_TIME_DIFF_C.                                          */
#define CFE$K_UTC_TIME 0                /* UTC time			None */
#define CFE$K_PLUS_DIFF 1               /* Positive difference		String */
#define CFE$K_NEG_DIFF 2                /* Negative difference		String */
/* Item codes for Text Choice aggregate.                                    */
#define CFE$_TXC_TEXT_C 263681          /* Text choice			Enumeration */
#define CFE$_TXC_TEXT 263682            /*				Variable */
#define CFE$_TXC_MAX 263683             /* Maximum code plus 1              */
/* Values of CFE$_TXC_TEXT_C.                                               */
#define CFE$K_LATIN1_TEXT 0             /* Latin-1 text			String */
#define CFE$K_SIMPLE_TEXT 1             /* Simple text			Character string */
#define CFE$K_COMPLEX_TEXT 2            /* Complex text			Array of character string */
/* Item codes for Varying Text Aggregate.                                   */
#define CFE$_VTX_VTEXT_LEN 263937       /* Varying Text Length		Integer */
#define CFE$_VTX_VTEXT_STR 263938       /* Varying Text String		Character-String */
#define CFE$_VTX_MAX 263939             /* Maximum code plus 1              */
/* Item codes for Field Reference aggregate.                                */
#define CFE$_FRF_FIELD_CONTEXT 264193   /* Field context		String */
#define CFE$_FRF_PATH 264194            /* Path				Array of string */
#define CFE$_FRF_MAX 264195             /* Maximum code plus 1              */
/* Item codes for Parenthesized Expression aggregate.                       */
#define CFE$_PEX_BEGIN_EXPR 264449      /* Begin expression 		Array of character string */
#define CFE$_PEX_VALUE_EXPR 264450      /* Value expression		Sequence of CFE$_EXL */
#define CFE$_PEX_END_EXPR 264451        /* End expression		Array of character string */
#define CFE$_PEX_MAX 264452             /* Maximum code plus 1              */
/* Item codes for Private Function Expression aggregate.                    */
#define CFE$_PFE_FACILITY 264705        /* Facility			String */
#define CFE$_PFE_NAME 264706            /* Function name		String */
#define CFE$_PFE_REF_LABEL 264707       /* Reference label		String */
#define CFE$_PFE_REF_LABEL_TYPE 264708  /* Reference label type		String with add-info */
#define CFE$_PFE_RETURN_TYPE 264709     /* Return type			Longword */
#define CFE$_PFE_PARAMS 264710          /* Parameters			Sequence of CFE$_NPM */
#define CFE$_PFE_MAX 264711             /* Maximum code plus 1              */
/* Values of the add-info parameter for CFE$_PFE_REF_LABEL_TYPE.            */
#define CFE$K_PRIVATE_LABEL_TYPE 0      /* Private label type               */
#define CFE$K_RMS_LABEL_TYPE 1          /* RMS file specification ("$RMS")  */
#define CFE$K_UTX_LABEL_TYPE 2          /* ULTRIX file specification ("$UTX") */
#define CFE$K_MDS_LABEL_TYPE 3          /* MS-DOS or OS/2 file specification ("$MDS") */
/* Bit definitions for CFE$_PFE_RET_TYPE.                                   */
#define cfe$m_pfe_fncret_numeric 1
#define cfe$m_pfe_fncret_boolean 2
#define cfe$m_pfe_fncret_date 4
#define cfe$m_pfe_fncret_text 8
struct pfe_type {
    unsigned cfe$v_pfe_fncret_numeric : 1;
    unsigned cfe$v_pfe_fncret_boolean : 1;
    unsigned cfe$v_pfe_fncret_date : 1;
    unsigned cfe$v_pfe_fncret_text : 1;
    unsigned cfe$v_pfe_fill_0 : 12;
    unsigned cfe$v_pfe_fill : 16;
    } ;
/* Item codes for String Format aggregate.                                  */
#define CFE$_STF_SOURCE 264961          /* Source			Sequence of CFE$_EXL */
#define CFE$_STF_EDIT_STRING 264962     /* Edit string			ESF$_EDS */
#define CFE$_STF_MAX 264963             /* Maximum code plus 1              */
/* Item codes for String Pretty aggregate.                                  */
#define CFE$_STP_STRING_EXPR 265217     /* String expression		Sequence of CFE$_EXL */
#define CFE$_STP_PRETTY_FLAGS 265218    /* Flags			Longword */
#define CFE$_STP_MAX 265219             /* Maximum code plus 1              */
/* Bit definitions for CFE$_STP_PRETTY_FLAGS.                               */
#define cfe$m_pretty_collapse 1
#define cfe$m_pretty_compress 2
#define cfe$m_pretty_lowercase 4
#define cfe$m_pretty_trim 8
#define cfe$m_pretty_uncomment 16
#define cfe$m_pretty_upcase 32
struct stp_pretty_flags {
    unsigned cfe$v_pretty_collapse : 1;
    unsigned cfe$v_pretty_compress : 1;
    unsigned cfe$v_pretty_lowercase : 1;
    unsigned cfe$v_pretty_trim : 1;
    unsigned cfe$v_pretty_uncomment : 1;
    unsigned cfe$v_pretty_upcase : 1;
    unsigned cfe$v_pretty_fill_0 : 10;
    unsigned cfe$v_pretty_fill_1 : 16;
    } ;
/* Item codes for Named Parameter aggregate.                                */
#define CFE$_NPM_NAME 265473            /* Parameter name		String */
#define CFE$_NPM_VALUE 265474           /* Parameter value		Sequence of CFE$_EXL */
#define CFE$_NPM_MAX 265475             /* Maximum code plus 1              */
/* Item codes for Cell Coordinates aggregate.                               */
#define CFE$_CCD_ROW 265729             /* Row number			Integer */
#define CFE$_CCD_COLUMN 265730          /* Column number		Integer */
#define CFE$_CCD_FLAGS 265731           /* Flags			Enumeration */
#define CFE$_CCD_MAX 265732             /* Maximum code plus 1              */
/* Values of CFE$_CCD_FLAGS.						DTIF defined */
#define CFE$K_RELROW_RELCOL 0           /* Relative row, relative column    */
#define CFE$K_RELROW_ABSCOL 1           /* Relative row, absolute column    */
#define CFE$K_ABSROW_RELCOL 2           /* Absolute row, relative column    */
#define CFE$K_ABSROW_ABSCOL 3           /* Absolute row, absolute column    */
/* Item codes for Cell Range aggregate.                                     */
#define CFE$_CLR_RANGE_BEGIN 265985     /* Beginning cell coordinates	CFE$_CCD */
#define CFE$_CLR_RANGE_END 265986       /* Ending cell coordinates	CFE$_CCD */
#define CFE$_CLR_MAX 265987             /* Maximum code plus 1              */
/* Item codes for Row Range aggregate.                                      */
#define CFE$_RWR_ROW_BEGIN 266241       /* Beginning row number		Integer */
#define CFE$_RWR_ROW_END 266242         /* Ending row number		Integer */
#define CFE$_RWR_MAX 266243             /* Maximum code plus 1              */
/* Item codes for Column Range aggregate.                                   */
#define CFE$_COR_COL_BEGIN 266497       /* Beginning column number	Integer */
#define CFE$_COR_COL_END 266498         /* Ending column number		Integer */
#define CFE$_COR_MAX 266499             /* Maximum code plus 1              */
