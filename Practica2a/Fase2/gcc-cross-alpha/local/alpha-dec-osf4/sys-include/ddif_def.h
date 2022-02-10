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
/* @(#)$RCSfile: ddif_def.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 04:28:37 $     */
/********************************************************************************************************************************/
/* Created  2-JUN-1991 09:34:50 by VAX SDL V3.2-12     Source:  2-APR-1991 17:19:05 DDIF$DEVELOP_ROOT:[DDIFBUILD.LIB.SRC]DDIF$DEF */
/********************************************************************************************************************************/
 
/*** MODULE DDIF$DEFINITIONS IDENT V1-023 ***/
/*++                                                                        */
/*                                                                          */
/*  COPYRIGHT (c) 1987, 1991 BY                                             */
/*  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.                  */
/*  ALL RIGHTS RESERVED.                                                    */
/*                                                                          */
/*  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED  */
/*  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE  */
/*  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER  */
/*  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY  */
/*  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY  */
/*  TRANSFERRED.                                                            */
/*                                                                          */
/*  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE  */
/*  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT  */
/*  CORPORATION.                                                            */
/*                                                                          */
/*  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS  */
/*  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.                 */
/*                                                                          */
/* Item codes for CDA$CREATE_ROOT_AGGREGATE processing-options parameter.   */
#define DDIF$_INHERIT_ATTRIBUTES 1      /* Inherit segment attributes       */
#define DDIF$_RETAIN_DEFINITIONS 2      /* Enable DDIF$FIND_DEFINITION      */
#define DDIF$_EVALUATE_CONTENT 3        /* Evaluate generic content references */
#define DDIF$_DISCARD_I_SEGMENTS 4      /* Discard image data segments      */
#define DDIF$_DISCARD_2D_SEGMENTS 5     /* Discard graphics data segments   */
#define DDIF$_DISCARD_T_SEGMENTS 6      /* Discard text data segments       */
#define DDIF$_DISCARD_TBL_SEGMENTS 7    /* Discard table data segments      */
#define DDIF$_DISCARD_PDL_SEGMENTS 8    /* Discard page description language segments */
#define DDIF$_ENABLE_INHERIT_STATUS 9   /* Enable CDA$_INHERIT status       */
/* Scope codes for CDA$ENTER_SCOPE and CDA$LEAVE_SCOPE.                     */
/* If an aggregate type is listed, it must be presented with CDA$ENTER_SCOPE. */
#define DDIF$K_DOCUMENT_SCOPE 0         /* Document scope                   */
#define DDIF$K_CONTENT_SCOPE 1          /* Content scope                    */
#define DDIF$K_SEGMENT_SCOPE 2          /* Segment scope		DDIF$_SEG */
#define DDIF$K_EXTERNAL_SCOPE 3         /* External scope		DDIF$_EXT */
/* Aggregate type codes.                                                    */
#define DDIF$_DDF 1                     /* DDIF document root               */
#define DDIF$_DSC 2                     /* Document descriptor              */
#define DDIF$_DHD 3                     /* Document header                  */
#define DDIF$_SEG 4                     /* Document segment                 */
#define DDIF$_TXT 5                     /* Latin-1 text content             */
#define DDIF$_GTX 6                     /* General text content             */
#define DDIF$_HRD 7                     /* Hard directive                   */
#define DDIF$_SFT 8                     /* Soft directive                   */
#define DDIF$_HRV 9                     /* Hard value directive             */
#define DDIF$_SFV 10                    /* Soft value directive             */
#define DDIF$_BEZ 11                    /* Bezier curve content             */
#define DDIF$_LIN 12                    /* Polyline content                 */
#define DDIF$_ARC 13                    /* Arc content                      */
#define DDIF$_FAS 14                    /* Fill area set content            */
#define DDIF$_IMG 15                    /* Image content                    */
#define DDIF$_CRF 16                    /* Content reference                */
#define DDIF$_EXT 17                    /* External content                 */
#define DDIF$_PVT 18                    /* Private content                  */
#define DDIF$_GLY 19                    /* Layout galley                    */
#define DDIF$_EOS 20                    /* End of segment                   */
#define DDIF$_ERF 21                    /* External reference               */
#define DDIF$_IDU 22                    /* Image data unit                  */
#define DDIF$_PTH 23                    /* Composite path element           */
#define DDIF$_SGA 24                    /* Segment attributes               */
#define DDIF$_CTD 25                    /* Content definition               */
#define DDIF$_FTD 26                    /* Font definition                  */
#define DDIF$_LSD 27                    /* Line style definition            */
#define DDIF$_PHD 28                    /* Path definition                  */
#define DDIF$_PTD 29                    /* Pattern definition               */
#define DDIF$_SGB 30                    /* Segment binding definition       */
#define DDIF$_TYD 31                    /* Type definition                  */
#define DDIF$_CTS 32                    /* Counter style                    */
#define DDIF$_OCC 33                    /* Occurrence definition            */
#define DDIF$_RCD 34                    /* Record definition                */
#define DDIF$_RGB 35                    /* RGB lookup table entry           */
#define DDIF$_TRN 36                    /* Transform                        */
#define DDIF$_LG1 37                    /* Generic layout I                 */
#define DDIF$_LS1 38                    /* Specific layout I                */
#define DDIF$_LW1 39                    /* Wrap attributes I                */
#define DDIF$_LL1 40                    /* Layout attributes I              */
#define DDIF$_GLA 41                    /* Galley attributes                */
#define DDIF$_PGD 42                    /* Page description                 */
#define DDIF$_PGL 43                    /* Page layout                      */
#define DDIF$_PGS 44                    /* Page select                      */
#define DDIF$_TBS 45                    /* Tab stop                         */
#define DDIF$_CPH 46                    /* Composite path                   */
#define DDIF$_AUD 47                    /* Audio content                    */
#define DDIF$_ADF 48                    /* Audio data frame                 */
#define DDIF$_PLJ 49                    /* Polyline join description        */
#define DDIF$_PJD 50                    /* Polyline join definition         */
#define DDIF$_MAX 51                    /* Maximum code plus 1              */
/* Item codes for all aggregates.  DDIF$_AGGREGATE_TYPE is read-only.       */
#define DDIF$_USER_CONTEXT 1            /* User context			Longword */
#define DDIF$_AGGREGATE_TYPE 2          /* Aggregate type code		Word */
#define DDIF$_ALL_MAX 3                 /* Maximum code plus 1              */
/* Values of data type enumeration for Measurement and Expression.          */
#define DDIF$K_VALUE_CONSTANT 0         /*				Integer */
#define DDIF$K_VALUE_VARIABLE 1         /*				String */
/* Values of data type enumeration for AngleRef.                            */
#define DDIF$K_ANGLE_CONSTANT 0         /*				Single precision floating */
#define DDIF$K_ANGLE_VARIABLE 1         /*				String */
/* Item codes for DDIF Document Root aggregate.                             */
#define DDIF$_DDF_DESCRIPTOR 257        /* Document descriptor		DDIF$_DSC */
#define DDIF$_DDF_HEADER 258            /* Document header		DDIF$_DHD */
#define DDIF$_DDF_CONTENT 259           /* Document content		DDIF$_SEG */
#define DDIF$_DDF_MAX 260               /* Maximum code plus 1              */
/* Item codes for Document Descriptor aggregate.  During CDA$PUT_AGGREGATE, the values of DDIF$_DSC_MAJOR_VERSION and */
/* DDIF$_DSC_MINOR_VERSION are not used.  The document always contains the current values for major and minor version. */
#define DDIF$_DSC_MAJOR_VERSION 513     /* Major version		Integer */
#define DDIF$_DSC_MINOR_VERSION 514     /* Minor version		Integer */
#define DDIF$_DSC_PRODUCT_IDENTIFIER 515 /* Product identifier		String */
#define DDIF$_DSC_PRODUCT_NAME 516      /* Product name			Array of character string */
#define DDIF$_DSC_MAX 517               /* Maximum code plus 1              */
/* Current values for major and minor standard version.                     */
#define DDIF$K_MAJOR_VERSION 1
#define DDIF$K_MINOR_VERSION 3
/* Item codes for Document Header aggregate.                                */
#define DDIF$_DHD_PRIVATE_DATA 769      /* Private header data		Sequence of DDIF$_PVT */
#define DDIF$_DHD_TITLE 770             /* Title			Array of character string */
#define DDIF$_DHD_AUTHOR 771            /* Author			Array of character string */
#define DDIF$_DHD_VERSION 772           /* Version			Array of character string */
#define DDIF$_DHD_DATE 773              /* Date				String */
#define DDIF$_DHD_CONFORMANCE_TAGS 774  /* Conformance tags		Array of string with add-info */
#define DDIF$_DHD_EXTERNAL_REFERENCES 775 /* External references		Sequence of DDIF$_ERF */
#define DDIF$_DHD_LANGUAGES_C 776       /* Languages			Array of enumeration */
#define DDIF$_DHD_LANGUAGES 777         /*				Array of variable */
#define DDIF$_DHD_STYLE_GUIDE 778       /* Style guide			Integer */
#define DDIF$_DHD_GENERAL_TEXT_CCS_C 779 /* General text coded char.set  Array of enumeration */
#define DDIF$_DHD_GENERAL_TEXT_CCS 780  /*				Array of variable */
#define DDIF$_DHD_MAX 781               /* Maximum code plus 1              */
/* Values of the add-info parameter for DDIF$_DHD_CONFORMANCE_TAGS.         */
#define DDIF$K_PRIVATE_CONFORMANCE 0    /* Nonstandard                      */
#define DDIF$K_SRQ_CONFORMANCE 1        /* "$SRQ" (structure required)      */
/* Values of DDIF$_DHD_LANGUAGES_C.                                         */
#define DDIF$K_ISO_639_LANGUAGE 0       /* ISO 639 language name	String */
#define DDIF$K_OTHER_LANGUAGE 1         /* Other language name		Character string */
/* Values of DDIF$_DHD_GENERAL_TEXT_CCS_C.                                  */
#define DDIF$K_CCS_VACANT 1             /* Vacant			None (null string) */
#define DDIF$K_CCS_UNKNOWN 2            /* Unknown			String */
#define DDIF$K_CCS_ASCII_GL 3           /* ASCII gl			String */
#define DDIF$K_CCS_1_OCTET 4            /* One octet			String */
#define DDIF$K_CCS_2_OCTET 5            /* Two octets			String */
#define DDIF$K_CCS_4_OCTET 6            /* Four octets			String */
/* Item codes for Document Segment aggregate.                               */
#define DDIF$_SEG_ID 1025               /* Segment ID			String */
#define DDIF$_SEG_USER_LABEL 1026       /* User label			Array of character string */
#define DDIF$_SEG_SEGMENT_TYPE 1027     /* Segment type			String */
#define DDIF$_SEG_SPECIFIC_ATTRIBUTES 1028 /* Specific attributes		DDIF$_SGA */
#define DDIF$_SEG_GENERIC_LAYOUT 1029   /* Generic layout		DDIF$_LG1 */
#define DDIF$_SEG_SPECIFIC_LAYOUT 1030  /* Specific layout		DDIF$_LS1 */
#define DDIF$_SEG_CONTENT 1031          /* Segment content		Sequence of content */
#define DDIF$_SEG_MAX 1032              /* Maximum code plus 1              */
/* Item codes for Latin-1 Text Content aggregate.                           */
#define DDIF$_TXT_CONTENT 1281          /* Text content			String */
#define DDIF$_TXT_MAX 1282              /* Maximum code plus 1              */
/* Item codes for General Text Content aggregate.                           */
#define DDIF$_GTX_CONTENT 1537          /* Text content			Character string */
#define DDIF$_GTX_MAX 1538              /* Maximum code plus 1              */
/* Item codes for Hard Directive aggregate.                                 */
#define DDIF$_HRD_DIRECTIVE 1793        /* Hard directive		Enumeration */
#define DDIF$_HRD_MAX 1794              /* Maximum code plus 1              */
/* Item codes for Soft Directive aggregate.                                 */
#define DDIF$_SFT_DIRECTIVE 2049        /* Soft directive		Enumeration */
#define DDIF$_SFT_MAX 2050              /* Maximum code plus 1              */
/* Values of DDIF$_HRD_DIRECTIVE, DDIF$_SFT_DIRECTIVE,			DDIF conforming */
/* DDIF$_LL1_INITIAL_DIRECTIVE.                                             */
#define DDIF$K_DIR_NEW_PAGE 1           /* New page                         */
#define DDIF$K_DIR_NEW_LINE 2           /* New line                         */
#define DDIF$K_DIR_NEW_GALLEY 3         /* New galley                       */
#define DDIF$K_DIR_TAB 4                /* Tab                              */
#define DDIF$K_DIR_SPACE 5              /* Space                            */
#define DDIF$K_DIR_HYPHEN_NEW_LINE 6    /* Hyphen and new line              */
#define DDIF$K_DIR_WORD_BREAK_POINT 7   /* Word break point                 */
#define DDIF$K_DIR_LEADERS 8            /* Leaders                          */
#define DDIF$K_DIR_BACKSPACE 9          /* Backspace                        */
#define DDIF$K_DIR_NULL 10              /* Null                             */
#define DDIF$K_DIR_NO_HYPHEN_WORD 11    /* No hyphenation in next word      */
#define DDIF$K_DIR_NEW_LEFTPAGE 16      /* New left page                    */
#define DDIF$K_DIR_NEW_RIGHTPAGE 17     /* New right page                   */
#define DDIF$K_DIR_LEFT_NEW_LINE 18     /* Left new line (obsolete)         */
#define DDIF$K_DIR_RIGHT_NEW_LINE 19    /* Right new line (obsolete)        */
#define DDIF$K_DIR_CENTERED_NEW_LINE 20 /* Centered new line (obsolete)     */
#define DDIF$K_DIR_JUSTIFIED_NEW_LINE 21 /* Fully justified new line (obsolete) */
/* Item codes for Hard Value Directive aggregate.                           */
#define DDIF$_HRV_C 2305                /* Directive choice		Enumeration */
#define DDIF$_HRV_ESC_RATIO_N 2306      /* Escapement ratio		Integer */
#define DDIF$_HRV_ESC_RATIO_D 2307      /*				Integer */
#define DDIF$_HRV_ESC_CONSTANT_C 2308   /* Escapement constant		Measurement enumeration */
#define DDIF$_HRV_ESC_CONSTANT 2309     /*				Variable */
#define DDIF$_HRV_RESET_VARIABLE 2310   /* Reset variable		String */
#define DDIF$_HRV_RESET_VALUE_C 2311    /* Reset value			Expression enumeration */
#define DDIF$_HRV_RESET_VALUE 2312      /*				Variable */
#define DDIF$_HRV_MAX 2313              /* Maximum code plus 1              */
/* Item codes for Soft Value Directive aggregate.                           */
#define DDIF$_SFV_C 2561                /* Directive choice		Enumeration */
#define DDIF$_SFV_ESC_RATIO_N 2562      /* Escapement ratio		Integer */
#define DDIF$_SFV_ESC_RATIO_D 2563      /*				Integer */
#define DDIF$_SFV_ESC_CONSTANT_C 2564   /* Escapement constant		Measurement enumeration */
#define DDIF$_SFV_ESC_CONSTANT 2565     /*				Variable */
#define DDIF$_SFV_RESET_VARIABLE 2566   /* Reset variable		String */
#define DDIF$_SFV_RESET_VALUE_C 2567    /* Reset value			Expression enumeration */
#define DDIF$_SFV_RESET_VALUE 2568      /*				Variable */
#define DDIF$_SFV_MAX 2569              /* Maximum code plus 1              */
/* Values of DDIF$_HRV_C, DDIF$_SFV_C.                                      */
#define DDIF$K_DIR_ESCAPEMENT 0         /* Escapement directive		HRV_ESC_RATIO_N to HRV_ESC_CONSTANT */
/*				SFV_ESC_RATIO_N to SFV_ESC_CONSTANT         */
#define DDIF$K_DIR_VARIABLE_RESET 1     /* Variable reset		HRV_RESET_VARIABLE to HRV_RESET_VALUE */
/*				SFV_RESET_VARIABLE to SFV_RESET_VALUE       */
/* Item codes for Bezier Curve Content aggregate.                           */
#define DDIF$_BEZ_FLAGS 2817            /* Flags			Longword */
#define DDIF$_BEZ_PATH_C 2818           /* Path				Array of Measurement enumeration */
#define DDIF$_BEZ_PATH 2819             /*				Array of variable */
#define DDIF$_BEZ_MAX 2820              /* Maximum code plus 1              */
/* Bit definitions for DDIF$_BEZ_FLAGS.					DDIF conforming */
#define ddif$m_bez_draw_curve 1
#define ddif$m_bez_fill_curve 2
#define ddif$m_bez_close_curve 4
struct bez_flags {
    unsigned ddif$v_bez_draw_curve : 1; /* Draw curve                       */
    unsigned ddif$v_bez_fill_curve : 1; /* Fill curve                       */
    unsigned ddif$v_bez_close_curve : 1; /* Close curve                     */
    unsigned ddif$v_bez_fill_0 : 13;
    unsigned ddif$v_bez_fill : 16;
    } ;
/* Item codes for Polyline Content aggregate.                               */
#define DDIF$_LIN_FLAGS 3073            /* Flags			Longword */
#define DDIF$_LIN_DRAW_PATTERN 3074     /* Draw pattern			Bit string */
#define DDIF$_LIN_PATH_C 3075           /* Path				Array of Measurement enumeration */
#define DDIF$_LIN_PATH 3076             /*				Array of variable */
#define DDIF$_LIN_JOINS_C 3077          /* Polyline joins		Array of enumeration */
#define DDIF$_LIN_JOINS 3078            /*				Array of variable */
#define DDIF$_LIN_MAX 3079              /* Maximum code plus 1              */
/* Bit definitions for DDIF$_LIN_FLAGS.					DDIF conforming */
#define ddif$m_lin_draw_polyline 1
#define ddif$m_lin_fill_polyline 2
#define ddif$m_lin_draw_markers 4
#define ddif$m_lin_regular_polygon 8
#define ddif$m_lin_close_polyline 16
#define ddif$m_lin_rounded_polyline 32
#define ddif$m_lin_rectangular_polygon 64
struct lin_flags {
    unsigned ddif$v_lin_draw_polyline : 1; /* Draw polyline                 */
    unsigned ddif$v_lin_fill_polyline : 1; /* Fill polyline                 */
    unsigned ddif$v_lin_draw_markers : 1; /* Draw markers                   */
    unsigned ddif$v_lin_regular_polygon : 1; /* Regular polygon             */
    unsigned ddif$v_lin_close_polyline : 1; /* Close polyline               */
    unsigned ddif$v_lin_rounded_polyline : 1; /* Rounded polyline           */
    unsigned ddif$v_lin_rectangular_polygon : 1; /* Rectangular polygon     */
    unsigned ddif$v_lin_fill_0 : 9;
    unsigned ddif$v_lin_fill : 16;
    } ;
/* Values of DDIF$_LIN_JOINS_C and DDIF$_PTH_JOINED_LINE_JOINS_C.           */
#define DDIF$K_DIRECT_JOIN 0            /* Join directly specified	DDIF$_PLJ */
#define DDIF$K_INDIRECT_JOIN 1          /* Join definition referenced	String */
/* Item codes for Arc Content aggregate.                                    */
#define DDIF$_ARC_FLAGS 3329            /* Flags			Longword */
#define DDIF$_ARC_CENTER_X_C 3330       /* Center X			Measurement enumeration */
#define DDIF$_ARC_CENTER_X 3331         /*				Variable */
#define DDIF$_ARC_CENTER_Y_C 3332       /* Center Y			Measurement enumeration */
#define DDIF$_ARC_CENTER_Y 3333         /*				Variable */
#define DDIF$_ARC_RADIUS_X_C 3334       /* Radius X			Measurement enumeration */
#define DDIF$_ARC_RADIUS_X 3335         /*				Variable */
#define DDIF$_ARC_RADIUS_DELTA_Y_C 3336 /* Radius delta Y		Measurement enumeration */
#define DDIF$_ARC_RADIUS_DELTA_Y 3337   /*				Variable */
#define DDIF$_ARC_START_C 3338          /* Start angle			AngleRef enumeration */
#define DDIF$_ARC_START 3339            /*				Variable */
#define DDIF$_ARC_EXTENT_C 3340         /* Extent			AngleRef enumeration */
#define DDIF$_ARC_EXTENT 3341           /*				Variable */
#define DDIF$_ARC_ROTATION_C 3342       /* Rotation			AngleRef enumeration */
#define DDIF$_ARC_ROTATION 3343         /*				Variable */
#define DDIF$_ARC_MAX 3344              /* Maximum code plus 1              */
/* Bit definitions for DDIF$_ARC_FLAGS.					DDIF conforming */
#define ddif$m_arc_draw_arc 1
#define ddif$m_arc_fill_arc 2
#define ddif$m_arc_pie_arc 4
#define ddif$m_arc_close_arc 8
struct arc_flags {
    unsigned ddif$v_arc_draw_arc : 1;   /* Draw arc                         */
    unsigned ddif$v_arc_fill_arc : 1;   /* Fill arc                         */
    unsigned ddif$v_arc_pie_arc : 1;    /* Pie arc                          */
    unsigned ddif$v_arc_close_arc : 1;  /* Close arc                        */
    unsigned ddif$v_arc_flags_fill_0 : 12;
    unsigned ddif$v_arc_flags_fill : 16;
    } ;
/* Item codes for Fill Area Set Content aggregate.                          */
#define DDIF$_FAS_FLAGS 3585            /* Flags			Longword */
#define DDIF$_FAS_PATH 3586             /* Path    			Sequence of DDIF$_PTH */
#define DDIF$_FAS_MORE_PATHS 3587       /* More paths			Sequence of DDIF$_CPH */
#define DDIF$_FAS_MAX 3588              /* Maximum code plus 1              */
/* Bit definitions for DDIF$_FAS_FLAGS.					DDIF conforming */
#define ddif$m_fas_co_draw_border 1
#define ddif$m_fas_co_fill_area 2
struct fas_flags {
    unsigned ddif$v_fas_co_draw_border : 1; /* Co-draw border               */
    unsigned ddif$v_fas_co_fill_area : 1; /* Co-fill area                   */
    unsigned ddif$v_fas_fill_0 : 14;
    unsigned ddif$v_fas_fill : 16;
    } ;
/* Item codes for Image Content aggregate.                                  */
#define DDIF$_IMG_CONTENT 3841          /* Image content		Sequence of DDIF$_IDU */
#define DDIF$_IMG_MAX 3842              /* Maximum code plus 1              */
/* Item codes for Content Reference aggregate.                              */
#define DDIF$_CRF_TRANSFORM 4097        /* Content transform		Sequence of DDIF$_TRN */
#define DDIF$_CRF_REFERENCE 4098        /* Content reference		String */
#define DDIF$_CRF_MAX 4099              /* Maximum code plus 1              */
/* Item codes for External Content aggregate.                               */
#define DDIF$_EXT_DIRECT_REFERENCE 4353 /* Direct reference		Object identifier */
#define DDIF$_EXT_INDIRECT_REFERENCE 4354 /* Indirect reference		Integer */
#define DDIF$_EXT_DATA_VALUE_DESCRIPTOR 4355 /* Data value descriptor	String */
#define DDIF$_EXT_ENCODING_C 4356       /* Encoding			Enumeration */
#define DDIF$_EXT_ENCODING 4357         /*				Variable */
#define DDIF$_EXT_ENCODING_L 4358       /*     Length (on input)	Integer */
#define DDIF$_EXT_MAX 4359              /* Maximum code plus 1              */
/* Values of DDIF$_EXT_ENCODING_C.                                          */
#define DDIF$K_DOCUMENT_ENCODING 0      /* Nested document		Document root aggregate */
#define DDIF$K_DDIS_ENCODING 1          /* Nested document		DDIS encoding */
#define DDIF$K_OCTET_ENCODING 2         /* Octet aligned		String */
#define DDIF$K_ARBITRARY_ENCODING 3     /* Arbitrary			Bit string */
/* Item codes for Private Content aggregate.                                */
#define DDIF$_PVT_NAME 4609             /* Value name			String */
#define DDIF$_PVT_DATA_C 4610           /* Value data			Enumeration */
#define DDIF$_PVT_DATA 4611             /*				Variable */
#define DDIF$_PVT_REFERENCE_ERF_INDEX 4612 /*     Reference index		Integer */
#define DDIF$_PVT_MAX 4613              /* Maximum code plus 1              */
/* Values of DDIF$_PVT_DATA_C.                                              */
#define DDIF$K_VALUE_BOOLEAN 0          /*				Boolean */
#define DDIF$K_VALUE_INTEGER 1          /*				Integer */
#define DDIF$K_VALUE_TEXT 2             /*				Array of character string */
#define DDIF$K_VALUE_GENERAL 3          /*				String */
#define DDIF$K_VALUE_REFERENCE 4        /*				String (DDIF$_PVT_REFERENCE_ERF_INDEX used) */
#define DDIF$K_VALUE_LIST 5             /*				Sequence of DDIF$_PVT */
#define DDIF$K_VALUE_EXTERNAL 6         /*				DDIF$_EXT */
/* Item codes for Layout Galley aggregate.                                  */
#define DDIF$_GLY_ID 4865               /* Galley ID			String */
#define DDIF$_GLY_BOUNDING_BOX_LL_X_C 4866 /* Galley bounding box		Measurement enumeration */
#define DDIF$_GLY_BOUNDING_BOX_LL_X 4867 /*     Lower left X coordinate	Variable */
#define DDIF$_GLY_BOUNDING_BOX_LL_Y_C 4868 /*				Measurement enumeration */
#define DDIF$_GLY_BOUNDING_BOX_LL_Y 4869 /*     Lower left Y coordinate	Variable */
#define DDIF$_GLY_BOUNDING_BOX_UR_X_C 4870 /*				Measurement enumeration */
#define DDIF$_GLY_BOUNDING_BOX_UR_X 4871 /*     Upper right X coordinate	Variable */
#define DDIF$_GLY_BOUNDING_BOX_UR_Y_C 4872 /*				Measurement enumeration */
#define DDIF$_GLY_BOUNDING_BOX_UR_Y 4873 /*     Upper right Y coordinate	Variable */
#define DDIF$_GLY_OUTLINE 4874          /* Galley outline		Sequence of DDIF$_PTH */
#define DDIF$_GLY_FLAGS 4875            /* Galley flags			Longword */
#define DDIF$_GLY_STREAMS 4876          /* Galley streams		Array of string */
#define DDIF$_GLY_SUCCESSOR_C 4877      /* Successor			Enumeration */
#define DDIF$_GLY_SUCCESSOR 4878        /*				Variable */
#define DDIF$_GLY_MAX 4879              /* Maximum code plus 1              */
/* Bit definitions for DDIF$_GLY_FLAGS.					DDIF conforming */
#define ddif$m_gly_vertical_align 1
#define ddif$m_gly_border 2
#define ddif$m_gly_autoconnect 4
#define ddif$m_gly_background_fill 8
#define ddif$m_gly_reserved 16
#define ddif$m_gly_nonimaged_proto 32
#define ddif$m_gly_current_value 64
struct gly_flags {
    unsigned ddif$v_gly_vertical_align : 1; /* Vertical align               */
    unsigned ddif$v_gly_border : 1;     /* Border                           */
    unsigned ddif$v_gly_autoconnect : 1; /* Autoconnect                     */
    unsigned ddif$v_gly_background_fill : 1; /* Background fill             */
    unsigned ddif$v_gly_reserved : 1;   /* Reserved for future use          */
    unsigned ddif$v_gly_nonimaged_proto : 1; /* Nonimaged proto             */
    unsigned ddif$v_gly_current_value : 1; /* Current value                 */
    unsigned ddif$v_gly_fill_0 : 9;
    unsigned ddif$v_gly_fill : 16;
    } ;
/* Values of DDIF$_GLY_SUCCESSOR_C.                                         */
#define DDIF$K_GENERIC_GALLEY 0         /* Generic galley		String */
#define DDIF$K_SPECIFIC_GALLEY 1        /* Specific galley		String */
#define DDIF$K_NO_SUCCESSOR_GALLEY 2    /* No successor galley		None */
/* Item codes for External Reference aggregate.                             */
#define DDIF$_ERF_DATA_TYPE 5377        /* Data type			Object identifier */
#define DDIF$_ERF_DESCRIPTOR 5378       /* Descriptor			Array of character string */
#define DDIF$_ERF_LABEL 5379            /* Label			Character string */
#define DDIF$_ERF_LABEL_TYPE 5380       /* Label type			String with add-info */
#define DDIF$_ERF_CONTROL 5381          /* Control			Enumeration */
#define DDIF$_ERF_MAX 5382              /* Maximum code plus 1              */
/* Values of the add-info parameter for DDIF$_ERF_LABEL_TYPE.  Must be identical */
/* to values for DTIF$_ERF_LABEL_TYPE and DOTS$_RTE_NAME_TYPE.              */
#define DDIF$K_PRIVATE_LABEL_TYPE 0     /* Private label type               */
#define DDIF$K_RMS_LABEL_TYPE 1         /* RMS file specification ("$RMS")  */
#define DDIF$K_UTX_LABEL_TYPE 2         /* ULTRIX file specification ("$UTX") */
#define DDIF$K_MDS_LABEL_TYPE 3         /* MS-DOS file specification ("$MDS") */
#define DDIF$K_STYLE_LABEL_TYPE 4       /* Style-guide file specification ("$STYLE") */
#define DDIF$K_OS2_LABEL_TYPE 5         /* OS/2 file specification ("$OS2") */
#define DDIF$K_OA_LABEL_TYPE 6          /* ALL-IN-1 file specification ("$OA") */
#define DDIF$K_PACKED_STYLE_LABEL_TYPE 7 /* Style-guide file specification ("$STYLE") (used when */
/* NO_COPY style guide packed by DOTS)                                      */
/* Values of DDIF$_ERF_CONTROL.						DDIF conforming */
#define DDIF$K_COPY_REFERENCE 1         /* Copy on reference                */
#define DDIF$K_NO_COPY_REFERENCE 2      /* No copy on reference             */
/* Item codes for Image Data Unit aggregate.                                */
#define DDIF$_IDU_PRIVATE_CODING_ATTR 5633 /* Private coding attributes	Sequence of DDIF$_PVT */
#define DDIF$_IDU_PIXELS_PER_LINE 5634  /* Pixels per line		Integer */
#define DDIF$_IDU_NUMBER_OF_LINES 5635  /* Number of lines		Integer */
#define DDIF$_IDU_COMPRESSION_TYPE 5636 /* Compression type		Enumeration */
#define DDIF$_IDU_COMPRESSION_PARAMS 5637 /* Compression parameters	Sequence of DDIF$_PVT */
#define DDIF$_IDU_DATA_OFFSET 5638      /* Data offset			Integer */
#define DDIF$_IDU_PIXEL_STRIDE 5639     /* Pixel stride			Integer */
#define DDIF$_IDU_SCANLINE_STRIDE 5640  /* Scanline stride		Integer */
#define DDIF$_IDU_BIT_ORDER 5641        /* Bit order			Enumeration */
#define DDIF$_IDU_BITS_PER_PIXEL 5642   /* Plane bits per pixel		Integer */
#define DDIF$_IDU_PLANE_DATA 5643       /* Plane data			String */
#define DDIF$_IDU_BYTE_UNIT 5644        /* Byte unit			Integer */
#define DDIF$_IDU_BYTE_ORDER 5645       /* Byte order			Enumeration */
#define DDIF$_IDU_DATA_TYPE 5646        /* Data type			Enumeration */
#define DDIF$_IDU_MAX 5647              /* Maximum code plus 1              */
/* AX04 item code retained for upward compatibility.                        */
#define DDIF$_IDU_PIXEL_ORDER 5641      /* Pixel order                      */
/* Values of DDIF$_IDU_COMPRESSION_TYPE.				DDIF conforming */
#define DDIF$K_PRIVATE_COMPRESSION 1    /* Private                          */
#define DDIF$K_PCM_COMPRESSION 2        /* Raw bitmap                       */
#define DDIF$K_G31D_COMPRESSION 3       /* CCITT Group 3 1 dimensional      */
#define DDIF$K_G32D_COMPRESSION 4       /* CCITT Group 3 2 dimensional      */
#define DDIF$K_G42D_COMPRESSION 5       /* CCITT Group 4 2 dimensional      */
#define DDIF$K_MONO_COMPRESSION 6       /* Mono compression                 */
#define DDIF$K_DCT_COMPRESSION 7        /* DCT compression                  */
/* Values of DDIF$_IDU_BIT_ORDER and DDIF$_AUD_BIT_ORDER.		DDIF conforming */
#define DDIF$K_LSBIT_FIRST 1            /* Least significant bit first      */
#define DDIF$K_MSBIT_FIRST 2            /* Most significant bit first       */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$K_STANDARD_PIXEL_ORDER 1   /* Standard pixel order             */
#define DDIF$K_REVERSE_PIXEL_ORDER 2    /* Reverse pixel order              */
/* Values of DDIF$_IDU_BYTE_ORDER and DDIF$_AUD_BYTE_ORDER		DDIF conforming */
#define DDIF$K_LSBYTE_FIRST 1           /* Least significant byte first     */
#define DDIF$K_MSBYTE_FIRST 2           /* Most significatn byte first      */
/* Values of DDIF$_IDU_DATA_TYPE.					DDIF conforming */
#define DDIF$K_PRIVATE 1                /* Private                          */
#define DDIF$K_BITSTREAM 2              /* Bitstream                        */
#define DDIF$K_INTEGER 3                /* Integer                          */
/* Item codes for Composite Path aggregate.                                 */
#define DDIF$_PTH_C 5889                /* Path choice			Enumeration */
#define DDIF$_PTH_LIN_PATH_C 5890       /* Line path			Array of Measurement enumeration */
#define DDIF$_PTH_LIN_PATH 5891         /*				Array of variable */
#define DDIF$_PTH_BEZ_PATH_C 5892       /* Cubic Bezier path		Array of Measurement enumeration */
#define DDIF$_PTH_BEZ_PATH 5893         /*				Array of variable */
#define DDIF$_PTH_ARC_CENTER_X_C 5894   /* Center X			Measurement enumeration */
#define DDIF$_PTH_ARC_CENTER_X 5895     /*				Variable */
#define DDIF$_PTH_ARC_CENTER_Y_C 5896   /* Center Y			Measurement enumeration */
#define DDIF$_PTH_ARC_CENTER_Y 5897     /*				Variable */
#define DDIF$_PTH_ARC_RADIUS_X_C 5898   /* Radius X			Measurement enumeration */
#define DDIF$_PTH_ARC_RADIUS_X 5899     /*				Variable */
#define DDIF$_PTH_ARC_RADIUS_DELTA_Y_C 5900 /* Radius delta Y		Measurement enumeration */
#define DDIF$_PTH_ARC_RADIUS_DELTA_Y 5901 /*				Variable */
#define DDIF$_PTH_ARC_START_C 5902      /* Start angle			AngleRef enumeration */
#define DDIF$_PTH_ARC_START 5903        /*				Variable */
#define DDIF$_PTH_ARC_EXTENT_C 5904     /* Extent			AngleRef enumeration */
#define DDIF$_PTH_ARC_EXTENT 5905       /*				Variable */
#define DDIF$_PTH_ARC_ROTATION_C 5906   /* Rotation			AngleRef enumeration */
#define DDIF$_PTH_ARC_ROTATION 5907     /*				Variable */
#define DDIF$_PTH_REFERENCE 5908        /* Path reference		Integer */
#define DDIF$_PTH_JOINED_LINE_PATH_C 5909 /* Joined line path		Array of Measurement enumeration */
#define DDIF$_PTH_JOINED_LINE_PATH 5910 /*				Array of Variable */
#define DDIF$_PTH_JOINED_LINE_JOINS_C 5911 /* Joined line joins		Array of enumeration */
#define DDIF$_PTH_JOINED_LINE_JOINS 5912 /*				Array of variable */
#define DDIF$_PTH_MAX 5913              /* Maximum code plus 1              */
/* Values of DDIF$_PTH_C.                                                   */
#define DDIF$K_PATH_LINE 0              /*				PTH_LIN_PATH_C to PTH_LIN_PATH */
#define DDIF$K_PATH_BEZIER 1            /*				PTH_BEZ_PATH_C to PTH_BEZ_PATH */
#define DDIF$K_PATH_ARC 2               /*				PTH_ARC_CENTER_X_C to PTH_ARC_ROTATION */
#define DDIF$K_PATH_REFERENCE 3         /*				PTH_REFERENCE */
#define DDIF$K_PATH_JOINED_LINE 4       /*				PTH_JOINED_LINE_PATH_C to PTH_JOINED_LINE_JOINS */
/* Item codes for Segment Attributes aggregate.  SGA_ITEM_CHANGE_LIST is read-only. */
#define DDIF$_SGA_PRIVATE_DATA 6145     /* Private attributes		Sequence of DDIF$_PVT */
#define DDIF$_SGA_CONTENT_STREAMS 6146  /* Content streams		Array of string */
#define DDIF$_SGA_CONTENT_CATEGORY 6147 /* Content category		String with add-info */
#define DDIF$_SGA_SEGMENT_TAGS 6148     /* Segment tags			Array of string with add-info */
#define DDIF$_SGA_BINDING_DEFNS 6149    /* Segment bindings		Sequence of DDIF$_SGB */
#define DDIF$_SGA_COMPUTE_C 6150        /* Computed content choice	Enumeration */
#define DDIF$_SGA_CPTCPY_TARGET 6151    /* Reference target		String */
#define DDIF$_SGA_CPTCPY_ERF_INDEX 6152 /* Reference external index	Integer */
#define DDIF$_SGA_CPTVAR_VARIABLE 6153  /* Variable name		String */
#define DDIF$_SGA_CPTXRF_TARGET 6154    /* Cross-reference target	String */
#define DDIF$_SGA_CPTXRF_ERF_INDEX 6155 /* Cross-reference index	Integer */
#define DDIF$_SGA_CPTXRF_VARIABLE 6156  /* Variable name		String */
#define DDIF$_SGA_CPTFNC_NAME 6157      /* Function name		String */
#define DDIF$_SGA_CPTFNC_PARAMETERS 6158 /* Function parameters		Sequence of DDIF$_PVT */
#define DDIF$_SGA_STRUCTURE_DESC_C 6159 /* Structure description	Enumeration */
#define DDIF$_SGA_STRUCTURE_DESC 6160   /* 				Sequence of DDIF$_OCC */
#define DDIF$_SGA_LANGUAGE 6161         /* Language			Integer */
#define DDIF$_SGA_LEGEND_UNIT_N 6162    /* Legend units			Integer */
#define DDIF$_SGA_LEGEND_UNIT_D 6163    /*				Integer */
#define DDIF$_SGA_LEGEND_UNIT_NAME 6164 /* Legend name			Array of character string */
#define DDIF$_SGA_UNITS_PER_MEASURE 6165 /* Units per measurement	Integer */
#define DDIF$_SGA_UNIT_NAME 6166        /* Units name			Array of character string */
#define DDIF$_SGA_ALT_PRESENTATION 6167 /* Alternate presentation	Array of character string */
#define DDIF$_SGA_LAYOUT_C 6168         /* Layout choice		Enumeration */
#define DDIF$_SGA_LAYGLY_WRAP 6169      /* Galley wrap attributes	DDIF$_LW1 */
#define DDIF$_SGA_LAYGLY_LAYOUT 6170    /* Galley layout attributes	DDIF$_LL1 */
#define DDIF$_SGA_LAYPTH_PATH 6171      /* String layout path		Sequence of DDIF$_PTH */
#define DDIF$_SGA_LAYPTH_FORMAT 6172    /* String layout format		Enumeration */
#define DDIF$_SGA_LAYPTH_ORIENTATION_C 6173 /* Character orientation	Enumeration */
#define DDIF$_SGA_LAYPTH_ORIENTATION 6174 /*				Variable */
#define DDIF$_SGA_LAYPTH_H_ALIGN 6175   /* Character horizontal align	Enumeration */
#define DDIF$_SGA_LAYPTH_V_ALIGN 6176   /* Character vertical align	Enumeration */
#define DDIF$_SGA_LAYREL_H_RATIO_N 6177 /* Horiz escapement ratio	Integer */
#define DDIF$_SGA_LAYREL_H_RATIO_D 6178 /*				Integer */
#define DDIF$_SGA_LAYREL_H_CONSTANT_C 6179 /* Horiz escapement constant	Measurement enumeration */
#define DDIF$_SGA_LAYREL_H_CONSTANT 6180 /*				Variable */
#define DDIF$_SGA_LAYREL_V_RATIO_N 6181 /* Vert escapement ratio	Integer */
#define DDIF$_SGA_LAYREL_V_RATIO_D 6182 /*				Integer */
#define DDIF$_SGA_LAYREL_V_CONSTANT_C 6183 /* Vert escapement constant	Measurement enumeration */
#define DDIF$_SGA_LAYREL_V_CONSTANT 6184 /*				Variable */
#define DDIF$_SGA_LAYPOS_TEXT_POSITION 6185 /* Text position		Enumeration */
#define DDIF$_SGA_FONT_DEFNS 6186       /* Font definitions		Sequence of DDIF$_FTD */
#define DDIF$_SGA_PATTERN_DEFNS 6187    /* Pattern definitions		Sequence of DDIF$_PTD */
#define DDIF$_SGA_PATH_DEFNS 6188       /* Path definitions		Sequence of DDIF$_PHD */
#define DDIF$_SGA_LINE_STYLE_DEFNS 6189 /* Line style definitions	Sequence of DDIF$_LSD */
#define DDIF$_SGA_CONTENT_DEFNS 6190    /* Content definitions		Sequence of DDIF$_CTD */
#define DDIF$_SGA_TYPE_DEFNS 6191       /* Type definitions		Sequence of DDIF$_TYD */
#define DDIF$_SGA_TXT_MASK_PATTERN 6192 /* Text mask pattern		Integer */
#define DDIF$_SGA_TXT_FONT 6193         /* Text font			Integer */
#define DDIF$_SGA_TXT_RENDITION 6194    /* Text rendition		Array of enumeration */
#define DDIF$_SGA_TXT_HEIGHT_C 6195     /* Text height			Measurement enumeration */
#define DDIF$_SGA_TXT_HEIGHT 6196       /* 				Variable */
#define DDIF$_SGA_TXT_SET_SIZE_N 6197   /* Text set size		Integer */
#define DDIF$_SGA_TXT_SET_SIZE_D 6198   /* Text set size		Integer */
#define DDIF$_SGA_TXT_DIRECTION 6199    /* Text direction		Enumeration */
#define DDIF$_SGA_TXT_DEC_ALIGNMENT 6200 /* Decimal align characters	Array of character string */
#define DDIF$_SGA_TXT_LEADER_SPACE_C 6201 /* Leader space			Measurement enumeration */
#define DDIF$_SGA_TXT_LEADER_SPACE 6202 /* 				Variable */
#define DDIF$_SGA_TXT_LEADER_BULLET 6203 /* Leader bullet		Character string */
#define DDIF$_SGA_TXT_LEADER_ALIGN 6204 /* Leader alignment		Enumeration */
#define DDIF$_SGA_TXT_LEADER_STYLE 6205 /* Leader style			Enumeration */
#define DDIF$_SGA_TXT_PAIR_KERNING 6206 /* Pair kerning			Boolean */
#define DDIF$_SGA_LIN_WIDTH_C 6207      /* Line width			Measurement enumeration */
#define DDIF$_SGA_LIN_WIDTH 6208        /* 				Variable */
#define DDIF$_SGA_LIN_STYLE 6209        /* Line style			Integer */
#define DDIF$_SGA_LIN_PATTERN_SIZE_C 6210 /* Line pattern size		Measurement enumeration */
#define DDIF$_SGA_LIN_PATTERN_SIZE 6211 /* 				Variable */
#define DDIF$_SGA_LIN_MASK_PATTERN 6212 /* Line mask pattern		Integer */
#define DDIF$_SGA_LIN_END_START 6213    /* Line end start		Enumeration */
#define DDIF$_SGA_LIN_END_FINISH 6214   /* Line end finish		Enumeration */
#define DDIF$_SGA_LIN_END_SIZE_C 6215   /* Line end size		Measurement enumeration */
#define DDIF$_SGA_LIN_END_SIZE 6216     /*				Variable */
#define DDIF$_SGA_LIN_JOIN 6217         /* Line join			Enumeration */
#define DDIF$_SGA_LIN_MITER_LIMIT_N 6218 /* Line miter limit		Integer */
#define DDIF$_SGA_LIN_MITER_LIMIT_D 6219 /*				Integer */
#define DDIF$_SGA_LIN_INTERIOR_PATTERN 6220 /* Line interior pattern	Integer */
#define DDIF$_SGA_MKR_STYLE 6221        /* Marker style			Enumeration */
#define DDIF$_SGA_MKR_MASK_PATTERN 6222 /* Marker mask pattern		Integer */
#define DDIF$_SGA_MKR_SIZE_C 6223       /* Marker size			Measurement enumeration */
#define DDIF$_SGA_MKR_SIZE 6224         /*	 			Variable */
#define DDIF$_SGA_GLY_ATTRIBUTES 6225   /* Galley attributes		DDIF$_GLA */
#define DDIF$_SGA_IMG_PRIVATE_DATA 6226 /* Image private data		Sequence of DDIF$_PVT */
#define DDIF$_SGA_IMG_PIXEL_PATH 6227   /* Pixel path			Integer */
#define DDIF$_SGA_IMG_LINE_PROGRESSION 6228 /* Line progression		Integer */
#define DDIF$_SGA_IMG_PP_PIXEL_DIST 6229 /* Asp ratio, pixel path	Integer */
#define DDIF$_SGA_IMG_LP_PIXEL_DIST 6230 /* Asp ratio, line progression	Integer */
#define DDIF$_SGA_IMG_BRT_POLARITY 6231 /* Brightness polarity		Enumeration */
#define DDIF$_SGA_IMG_GRID_TYPE 6232    /* Grid type			Enumeration */
#define DDIF$_SGA_IMG_TIMING_DESC 6233  /* Timing descriptor		Binary relative time */
#define DDIF$_SGA_IMG_SPECTRAL_MAPPING 6234 /* Spectral component mapping	Enumeration */
#define DDIF$_SGA_IMG_LOOKUP_TABLES_C 6235 /* Lookup tables		Enumeration */
#define DDIF$_SGA_IMG_LOOKUP_TABLES 6236 /*				Variable */
#define DDIF$_SGA_IMG_COMP_WAVELENGTH_C 6237 /* Component wavelength info	Enumeration */
#define DDIF$_SGA_IMG_COMP_WAVELENGTH 6238 /*				Variable */
#define DDIF$_SGA_IMG_COMP_SPACE_ORG 6239 /* Component space organization	Enumeration */
#define DDIF$_SGA_IMG_PLANES_PER_PIXEL 6240 /* Data planes per pixel	Integer */
#define DDIF$_SGA_IMG_PLANE_SIGNIF 6241 /* Data plane significance	Enumeration */
#define DDIF$_SGA_IMG_NUMBER_OF_COMP 6242 /* Number of components		Integer */
#define DDIF$_SGA_IMG_BITS_PER_COMP 6243 /* Bits per component		Array of integer */
#define DDIF$_SGA_FRM_FLAGS 6244        /* Frame flags			Longword */
#define DDIF$_SGA_FRM_BOX_LL_X_C 6245   /* Frame bounding box		Measurement enumeration */
#define DDIF$_SGA_FRM_BOX_LL_X 6246     /*     Lower left X coordinate	Variable */
#define DDIF$_SGA_FRM_BOX_LL_Y_C 6247   /*				Measurement enumeration */
#define DDIF$_SGA_FRM_BOX_LL_Y 6248     /*     Lower left Y coordinate	Variable */
#define DDIF$_SGA_FRM_BOX_UR_X_C 6249   /*				Measurement enumeration */
#define DDIF$_SGA_FRM_BOX_UR_X 6250     /*     Upper right X coordinate	Variable */
#define DDIF$_SGA_FRM_BOX_UR_Y_C 6251   /*				Measurement enumeration */
#define DDIF$_SGA_FRM_BOX_UR_Y 6252     /*     Upper right Y coordinate	Variable */
#define DDIF$_SGA_FRM_OUTLINE 6253      /* Frame outline		Sequence of DDIF$_PTH */
#define DDIF$_SGA_FRM_CLIPPING 6254     /* Frame clipping		Sequence of DDIF$_PTH */
#define DDIF$_SGA_FRM_POSITION_C 6255   /* Frame position choice	Enumeration */
#define DDIF$_SGA_FRMFXD_POSITION_X_C 6256 /* Frame fixed position		Measurement enumeration */
#define DDIF$_SGA_FRMFXD_POSITION_X 6257 /*     X coordinate		Variable */
#define DDIF$_SGA_FRMFXD_POSITION_Y_C 6258 /* Frame fixed position		Measurement enumeration */
#define DDIF$_SGA_FRMFXD_POSITION_Y 6259 /*     Y coordinate		Variable */
#define DDIF$_SGA_FRMINL_BASE_OFFSET_C 6260 /* Inline base offset		Measurement enumeration */
#define DDIF$_SGA_FRMINL_BASE_OFFSET 6261 /*				Variable */
#define DDIF$_SGA_FRMGLY_VERTICAL 6262  /* Galley vertical position	Enumeration */
#define DDIF$_SGA_FRMGLY_HORIZONTAL 6263 /* Galley horizontal position	Enumeration */
#define DDIF$_SGA_FRMMAR_BASE_OFFSET_C 6264 /* Margin base offset		Measurement enumeration */
#define DDIF$_SGA_FRMMAR_BASE_OFFSET 6265 /*				Variable */
#define DDIF$_SGA_FRMMAR_NEAR_OFFSET_C 6266 /* Margin near offset		Measurement enumeration */
#define DDIF$_SGA_FRMMAR_NEAR_OFFSET 6267 /*				Variable */
#define DDIF$_SGA_FRMMAR_HORIZONTAL 6268 /* Margin horizontal position	Enumeration */
#define DDIF$_SGA_FRM_TRANSFORM 6269    /* Frame content transform	Sequence of DDIF$_TRN */
#define DDIF$_SGA_ITEM_CHANGE_LIST 6270 /* Item change list		Item change list */
#define DDIF$_SGA_LAYPTH_REVERSE_PATH 6271 /* Reverse path			Boolean */
#define DDIF$_SGA_TXT_BACKGROUND 6272   /* Text background		Integer */
#define DDIF$_SGA_TXT_FORCE_HORIZONTAL 6273 /* Force text horizontal	Boolean */
#define DDIF$_SGA_IMG_PIXEL_GRP_SIZE 6274 /* Pixel group size		Integer */
#define DDIF$_SGA_IMG_PIXEL_GRP_ORDER 6275 /* Pixel group order		Enumeration */
#define DDIF$_SGA_IMG_COMP_QUANT_LEVELS 6276 /* Component quantize levels	Array of Integer */
#define DDIF$_SGA_FRMGLY_H_OFFSET_C 6277 /* Horizontal offset		Measurement enumeration */
#define DDIF$_SGA_FRMGLY_H_OFFSET 6278  /*				Variable */
#define DDIF$_SGA_FRMGLY_V_OFFSET_C 6279 /* Vertical offset		Measurement enumeration */
#define DDIF$_SGA_FRMGLY_V_OFFSET 6280  /* 				Variable */
#define DDIF$_SGA_TIME_RTU_FREQ 6281    /* RTU Frequency		Integer */
#define DDIF$_SGA_POLY_JOIN_DEFNS 6282  /* Polyline join definitions	Sequence of DDIF$_PJD */
#define DDIF$_SGA_MAX 6283              /* Maximum code plus 1              */
/* Values of the add-info parameter for DDIF$_SGA_CONTENT_CATEGORY.         */
#define DDIF$K_PRIVATE_CATEGORY 0       /* Nonstandard                      */
#define DDIF$K_I_CATEGORY 1             /* "$I" (image)                     */
#define DDIF$K_2D_CATEGORY 2            /* "$2D" (graphics)                 */
#define DDIF$K_T_CATEGORY 3             /* "$T" (text)                      */
#define DDIF$K_TBL_CATEGORY 4           /* "$TBL" (table)                   */
#define DDIF$K_PDL_CATEGORY 5           /* "$PDL" (page description language) */
#define DDIF$K_A_CATEGORY 6             /* "$A" (audio)                     */
/* Values of the add-info parameter for DDIF$_SGA_SEGMENT_TAGS.             */
#define DDIF$K_PRIVATE_TAG 0            /* Nonstandard                      */
#define DDIF$K_CRF_TAG 1                /* "$CRF" (cross-reference)         */
#define DDIF$K_F_TAG 2                  /* "$F" (figure)                    */
#define DDIF$K_P_TAG 3                  /* "$P" (paragraph)                 */
#define DDIF$K_S_TAG 4                  /* "$S" (section)                   */
#define DDIF$K_I_TAG 5                  /* "$I" (index)                     */
#define DDIF$K_E_TAG 6                  /* "$E" (emphasized)                */
#define DDIF$K_L_TAG 7                  /* "$L" (list)                      */
#define DDIF$K_LE_TAG 8                 /* "$LE" (list element)             */
#define DDIF$K_LIT_TAG 9                /* "$LIT" (literal)                 */
#define DDIF$K_FN_TAG 10                /* "$FN" (footnote)                 */
#define DDIF$K_AN_TAG 11                /* "$AN" (annotation)               */
#define DDIF$K_LBL_TAG 12               /* "$LBL" (label)                   */
#define DDIF$K_TTL_TAG 13               /* "$TTL" (title)                   */
#define DDIF$K_GRP_TAG 14               /* "$GRP" (group member)            */
#define DDIF$K_GO_TAG 15                /* "$GO" (graphics object)          */
#define DDIF$K_EN_TAG 16                /* "$EN" (end note)                 */
#define DDIF$K_APP_TAG 17               /* "$APP" (appendix)                */
#define DDIF$K_HDR_TAG 18               /* "$HDR" (header)                  */
#define DDIF$K_FTR_TAG 19               /* "$FTR" (footer)                  */
#define DDIF$K_TOC_TAG 20               /* "$TOC" (table of contents)       */
/* Values of DDIF$_SGA_COMPUTE_C.                                           */
#define DDIF$K_COPY_COMPUTE 0           /* Copy locally			SGA_CPTCPY_TARGET to SGA_CPTCPY_ERF_INDEX */
#define DDIF$K_REMOTE_COMPUTE 1         /* Copy remotely		SGA_CPTCPY_TARGET to SGA_CPTCPY_ERF_INDEX */
#define DDIF$K_VARIABLE_COMPUTE 2       /* Variable			SGA_CPTVAR_VARIABLE */
#define DDIF$K_XREF_COMPUTE 3           /* Cross-reference		SGA_CPTXRF_SEGMENT to SGA_CPTXRF_VARIABLE */
#define DDIF$K_FUNCTION_COMPUTE 4       /* Function link		SGA_CPTFNC_NAME to SGA_CPTFNC_PARAMETERS */
/* Values of DDIF$_SGA_STRUCTURE_DESC_C and DDIF$_OCC_STRUCTURE_ELEMENT_C.  */
#define DDIF$K_SEQUENCE_STRUCTURE 0     /* Sequence structure		Sequence of DDIF$_OCC */
#define DDIF$K_SET_STRUCTURE 1          /* Set structure		Sequence of DDIF$_OCC */
#define DDIF$K_CHOICE_STRUCTURE 2       /* Choice structure		Sequence of DDIF$_OCC */
#define DDIF$K_REFERENCED_TYPE 3        /* Referenced type		String (not for DDIF$_SGA_STRUCTURE_DESC_C) */
/* Values of DDIF$_SGA_LAYOUT_C.                                            */
#define DDIF$K_GALLEY_LAYOUT 0          /* Galley-based layout		SGA_LAYGLY_WRAP to SGA_LAYGLY_LAYOUT */
#define DDIF$K_PATH_LAYOUT 1            /* Path-based layout		SGA_LAYPTH_PATH to SGA_LAYPTH_V_ALIGN */
#define DDIF$K_RELATIVE_LAYOUT 2        /* Position-relative layout	SGA_LAYREL_H_RATIO_N to SGA_LAYREL_V_CONSTANT */
#define DDIF$K_POSITION_LAYOUT 3        /* Position-based layout	SGA_LAYPOS_TEXT_POSITION */
/* Values of DDIF$_SGA_LAYPTH_FORMAT, DDIF$_SGA_FRMGLY_HORIZONTAL,	DDIF conforming */
/* DDIF$_LW1_WRAP_FORMAT, DDIF$_LW1_QUAD_FORMAT.                            */
#define DDIF$K_FMT_FLUSH_PATH_BEGIN 1   /* Flush with beginning of path     */
#define DDIF$K_FMT_CENTER_OF_PATH 2     /* Centered on path                 */
#define DDIF$K_FMT_FLUSH_PATH_END 3     /* Flush with end of path           */
#define DDIF$K_FMT_FLUSH_PATH_BOTH 4    /* Flush with both ends of path     */
/* Values of DDIF$_SGA_LAYPTH_ORIENTATION_C.                                */
#define DDIF$K_PATH_FIXED 0             /* Fixed frame-relative		Single precision floating */
#define DDIF$K_PATH_RELATIVE 1          /* Path relative		Enumeration */
/* Values of DDIF$_SGA_LAYPTH_ORIENTATION for DDIF$K_PATH_RELATIVE.	DDIF conforming */
#define DDIF$K_RIGHT_ANGLE_RIGHT 1      /* Right                            */
#define DDIF$K_RIGHT_ANGLE_LEFT 2       /* Left                             */
#define DDIF$K_RIGHT_ANGLE_UP 3         /* Up                               */
#define DDIF$K_RIGHT_ANGLE_DOWN 4       /* Down                             */
/* Values of DDIF$_SGA_LAYPTH_H_ALIGN.					DDIF conforming */
#define DDIF$K_PATH_NORMAL_HORIZONTAL 1 /* Normal horizontal                */
#define DDIF$K_PATH_LEFTLINE 2          /* Left line                        */
#define DDIF$K_PATH_CENTERLINE 3        /* Center line                      */
#define DDIF$K_PATH_RIGHTLINE 4         /* Right line                       */
/* Values of DDIF$_SGA_LAYPTH_V_ALIGN.					DDIF conforming */
#define DDIF$K_PATH_NORMAL_VERTICAL 1   /* Normal vertical                  */
#define DDIF$K_PATH_BASELINE 2          /* Base line                        */
#define DDIF$K_PATH_CAPLINE 3           /* Cap line                         */
#define DDIF$K_PATH_BOTTOMLINE 4        /* Bottom line                      */
#define DDIF$K_PATH_HALFLINE 5          /* Half line                        */
#define DDIF$K_PATH_TOPLINE 6           /* Top line                         */
/* Values of DDIF$_SGA_LAYPOS_TEXT_POSITION.				DDIF conforming */
#define DDIF$K_TEXT_POS_BASE 1          /* Base                             */
#define DDIF$K_TEXT_POS_LD_SUBSCRIPT 2  /* Leading subscript                */
#define DDIF$K_TEXT_POS_LD_SUPERSCRIPT 3 /* Leading superscript             */
#define DDIF$K_TEXT_POS_TR_SUBSCRIPT 4  /* Trailing subscript               */
#define DDIF$K_TEXT_POS_TR_SUPERSCRIPT 5 /* Trailing superscript            */
#define DDIF$K_TEXT_POS_TOP_CENTER 6    /* Top center                       */
#define DDIF$K_TEXT_POS_BOTTOM_CENTER 7 /* Bottom center                    */
#define DDIF$K_TEXT_POS_RUBI 8          /* Rubi                             */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$K_TEXT_POS_L_SUBSCRIPT 2   /* Left subscript                   */
#define DDIF$K_TEXT_POS_L_SUPERSCRIPT 3 /* Left superscript                 */
#define DDIF$K_TEXT_POS_R_SUBSCRIPT 4   /* Right subscript                  */
#define DDIF$K_TEXT_POS_R_SUPERSCRIPT 5 /* Right superscript                */
/* Predefined values of DDIF$_SGA_TXT_MASK_PATTERN, DDIF$_SGA_LIN_MASK_PATTERN, DDIF$_SGA_LIN_INTERIOR_PATTERN, */
/* DDIF$_SGA_MKR_MASK_PATTERN, DDIF$_PTD_NUMBER, DDIF$_PTD_PAT_COLORS.      */
#define DDIF$K_PATT_TRANSPARENT 0
#define DDIF$K_PATT_BACKGROUND 1
#define DDIF$K_PATT_FOREGROUND 2
#define DDIF$K_PATT_VERT1_1 3
#define DDIF$K_PATT_VERT1_3 4
#define DDIF$K_PATT_VERT2_2 5
#define DDIF$K_PATT_VERT3_1 6
#define DDIF$K_PATT_VERT1_7 7
#define DDIF$K_PATT_VERT2_6 8
#define DDIF$K_PATT_VERT4_4 9
#define DDIF$K_PATT_VERT6_2 10
#define DDIF$K_PATT_HORIZ1_1 11
#define DDIF$K_PATT_HORIZ1_3 12
#define DDIF$K_PATT_HORIZ2_2 13
#define DDIF$K_PATT_HORIZ3_1 14
#define DDIF$K_PATT_HORIZ1_7 15
#define DDIF$K_PATT_HORIZ2_6 16
#define DDIF$K_PATT_HORIZ4_4 17
#define DDIF$K_PATT_HORIZ6_2 18
#define DDIF$K_PATT_GRID4 19
#define DDIF$K_PATT_GRID8 20
#define DDIF$K_PATT_UPDIAG1_3 21
#define DDIF$K_PATT_UPDIAG2_2 22
#define DDIF$K_PATT_UPDIAG3_1 23
#define DDIF$K_PATT_UPDIAG1_7 24
#define DDIF$K_PATT_UPDIAG2_6 25
#define DDIF$K_PATT_UPDIAG4_4 26
#define DDIF$K_PATT_UPDIAG6_2 27
#define DDIF$K_PATT_DOWNDIAG1_3 28
#define DDIF$K_PATT_DOWNDIAG2_2 29
#define DDIF$K_PATT_DOWNDIAG3_1 30
#define DDIF$K_PATT_DOWNDIAG1_7 31
#define DDIF$K_PATT_DOWNDIAG2_6 32
#define DDIF$K_PATT_DOWNDIAG4_4 33
#define DDIF$K_PATT_DOWNDIAG6_2 34
#define DDIF$K_PATT_BRICK_HORIZ 35
#define DDIF$K_PATT_BRICK_VERT 36
#define DDIF$K_PATT_BRICK_DOWNDIAG 37
#define DDIF$K_PATT_BRICK_UPDIAG 38
#define DDIF$K_PATT_GREY4_16D 39
#define DDIF$K_PATT_GREY12_16D 40
#define DDIF$K_PATT_BASKET_WEAVE 41
#define DDIF$K_PATT_SCALE_DOWN 42
#define DDIF$K_PATT_SCALE_UP 43
#define DDIF$K_PATT_SCALE_RIGHT 44
#define DDIF$K_PATT_SCALE_LEFT 45
#define DDIF$K_PATT_FILLER6 46
#define DDIF$K_PATT_FILLER7 47
#define DDIF$K_PATT_GREY1_16 48
#define DDIF$K_PATT_GREY2_16 49
#define DDIF$K_PATT_GREY3_16 50
#define DDIF$K_PATT_GREY4_16 51
#define DDIF$K_PATT_GREY5_16 52
#define DDIF$K_PATT_GREY6_16 53
#define DDIF$K_PATT_GREY7_16 54
#define DDIF$K_PATT_GREY8_16 55
#define DDIF$K_PATT_GREY9_16 56
#define DDIF$K_PATT_GREY10_16 57
#define DDIF$K_PATT_GREY11_16 58
#define DDIF$K_PATT_GREY12_16 59
#define DDIF$K_PATT_GREY13_16 60
#define DDIF$K_PATT_GREY14_16 61
#define DDIF$K_PATT_GREY15_16 62
/* Values of DDIF$_SGA_TXT_RENDITION. 					DDIF conforming */
#define DDIF$K_RND_DEFAULT 0            /* Default rendition                */
#define DDIF$K_RND_HIGHLIGHT 1          /* Highlighted intensity            */
#define DDIF$K_RND_FAINT 2              /* Faint intensity                  */
#define DDIF$K_RND_ITALIC 3             /* Italic rendition                 */
#define DDIF$K_RND_NORMAL 22            /* Normal intensity                 */
#define DDIF$K_RND_SLOW_BLINK 5         /* Slow blinking                    */
#define DDIF$K_RND_FAST_BLINK 6         /* Rapid blinking                   */
#define DDIF$K_RND_NO_BLINK 25          /* Steady (no blinking)             */
#define DDIF$K_RND_NEGATIVE 7           /* Negative image                   */
#define DDIF$K_RND_POSITIVE 27          /* Positive image                   */
#define DDIF$K_RND_CONCEAL 8            /* Concealed characters             */
#define DDIF$K_RND_NO_CONCEAL 28        /* Revealed characters              */
#define DDIF$K_RND_UNDERLINE 4          /* Underlined                       */
#define DDIF$K_RND_2_UNDERLINE 21       /* Double underlined                */
#define DDIF$K_RND_NO_UNDERLINE 24      /* Not underlined                   */
#define DDIF$K_RND_CROSS_OUT 9          /* Crossed out                      */
#define DDIF$K_RND_BOX 51               /* Boxed                            */
#define DDIF$K_RND_ENCIRCLE 52          /* Encircled                        */
#define DDIF$K_RND_OVERLINE 53          /* Overlined                        */
#define DDIF$K_RND_IDEO_UNDERLINE 60    /* Ideogram underlined              */
#define DDIF$K_RND_IDEO_2_UNDERLINE 61  /* Ideogram double underlined       */
#define DDIF$K_RND_IDEO_OVERLINE 62     /* Ideogram overlined               */
#define DDIF$K_RND_IDEO_2_OVERLINE 63   /* Ideogram double overlined        */
#define DDIF$K_RND_IDEO_STRESS 64       /* Ideogram stress marking          */
#define DDIF$K_RND_FC_UNDERLINE 65      /* Fancy underline                  */
#define DDIF$K_RND_FC_OVERLINE 66       /* Fancy overline                   */
#define DDIF$K_RND_FC_IDEO_UNDERLINE 67 /* Fancy ideogram underline         */
#define DDIF$K_RND_FC_IDEO_OVERLINE 68  /* Fancy ideogram overline          */
#define DDIF$K_RND_FC_IDEO_2_UNDERLINE 69 /* Fancy ideogram double underline */
#define DDIF$K_RND_FC_IDEO_2_OVERLINE 70 /* Fancy ideogram double overline  */
#define DDIF$K_RND_CHANGEBARS 257       /* Change bars                      */
/* Values of DDIF$_SGA_TXT_DIRECTION.					DDIF conforming */
#define DDIF$K_TXT_DIR_LTOR 1           /* Direction left to right          */
#define DDIF$K_TXT_DIR_RTOL 2           /* Direction right to left          */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$K_TXT_DIR_FORWARD 1        /* Forward direction                */
#define DDIF$K_TXT_DIR_BACKWARD 2       /* Backward direction               */
/* Values of DDIF$_SGA_TXT_LEADER_ALIGN.				DDIF conforming */
#define DDIF$K_ALIGNED_LEADER 1         /* Aligned leader                   */
#define DDIF$K_STAGGERED_LEADER 2       /* Staggered leader                 */
#define DDIF$K_NON_ALIGNED_LEADER 3     /* No specification                 */
/* Values of DDIF$_SGA_TXT_LEADER_STYLE.				DDIF conforming */
#define DDIF$K_X_RULE_LEADER 1          /* X rule                           */
#define DDIF$K_BULLET_LEADER 2          /* Bullet                           */
/* Predefined values of DDIF$_SGA_LIN_STYLE.				DDIF conforming */
#define DDIF$K_SOLID_LINE_STYLE 1       /* Solid                            */
#define DDIF$K_DASH_LINE_STYLE 2        /* Dash                             */
#define DDIF$K_DOT_LINE_STYLE 3         /* Dot                              */
#define DDIF$K_DASH_DOT_LINE_STYLE 4    /* Dash-dot                         */
/* Values of DDIF$_SGA_LIN_END_START, DDIF$_SGA_LIN_END_FINISH.		DDIF conforming */
#define DDIF$K_BUTT_LINE_END 1          /* Butt line end                    */
#define DDIF$K_ROUND_LINE_END 2         /* Round line end                   */
#define DDIF$K_SQUARE_LINE_END 3        /* Square line end                  */
#define DDIF$K_ARROW_LINE_END 4         /* Arrow line end                   */
#define DDIF$K_UNFILLED_ARROW_LINE_END 5 /* Unfilled arrow line end         */
/* Values of DDIF$_SGA_LIN_JOIN.					DDIF conforming */
#define DDIF$K_MITERED_LINE_JOIN 1      /* Mitered line join                */
#define DDIF$K_ROUNDED_LINE_JOIN 2      /* Rounded line join                */
#define DDIF$K_BEVELED_LINE_JOIN 3      /* Beveled line join                */
/* Values of DDIF$_SGA_MKR_STYLE.					DDIF conforming */
#define DDIF$K_DOT_MARKER 1             /* Dot                              */
#define DDIF$K_PLUS_MARKER 2            /* Plus sign                        */
#define DDIF$K_ASTERISK_MARKER 3        /* Asterisk                         */
#define DDIF$K_CIRCLE_MARKER 4          /* Circle                           */
#define DDIF$K_CROSS_MARKER 5           /* Diagonal cross                   */
/* Values of DDIF$_SGA_IMG_BRT_POLARITY.				DDIF conforming */
#define DDIF$K_ZERO_MAX_INTENSITY 1     /* Zero maximum intensity           */
#define DDIF$K_ZERO_MIN_INTENSITY 2     /* Zero minimum intensity           */
/* Values of DDIF$_SGA_IMG_GRID_TYPE.					DDIF conforming */
#define DDIF$K_RECTANGULAR_GRID 1       /* Rectangular grid                 */
#define DDIF$K_HEX_EVEN_INDENT 2        /* Hexagonal grid, indent even      */
#define DDIF$K_HEX_ODD_INDENT 3         /* Hexagonal grid, indent odd       */
/* Values of DDIF$_SGA_IMG_SPECTRAL_MAPPING.				DDIF conforming */
#define DDIF$K_PRIVATE_MAP 1            /* Privately mapped                 */
#define DDIF$K_MONOCHROME_MAP 2         /* Monochrome mapped                */
#define DDIF$K_GENERAL_MAP 3            /* General multispectral            */
#define DDIF$K_LUT_MAP 4                /* Lookup table mapped              */
#define DDIF$K_RGB_MAP 5                /* RGB mapped                       */
#define DDIF$K_CMY_MAP 6                /* CMY mapped                       */
#define DDIF$K_YUV_MAP 7                /* YUV mapped                       */
#define DDIF$K_HSV_MAP 8                /* HSV mapped                       */
#define DDIF$K_HLS_MAP 9                /* HLS mapped                       */
#define DDIF$K_YIQ_MAP 10               /* YIQ mapped                       */
/* Values of DDIF$_SGA_IMG_LOOKUP_TABLES_C.                                 */
#define DDIF$K_PRIVATE_LUT 0            /* Private LUT data		Sequence of DDIF$_PVT */
#define DDIF$K_RGB_LUT 1                /* RGB LUT data			Sequence of DDIF$_RGB */
/* Values of DDIF$_SGA_IMG_COMP_WAVELENGTH_C.                               */
#define DDIF$K_APPLICATION_WAVELENGTH 0 /* Application wavelength	Array of string */
#define DDIF$K_WAVELENGTH_MEASURE 1     /* Wavelength measure		Array of integer */
#define DDIF$K_WAVELENGTH_BAND_ID 2     /* Wavelength band ID		Array of string */
/* Values of DDIF$_SGA_IMG_COMP_SPACE_ORG.				DDIF conforming */
#define DDIF$K_BAND_INTERLEAVE_BY_PIXEL 1 /* Band interleaved by pixel      */
#define DDIF$K_BAND_SEQ_BY_PLANE 2      /* Band sequence by plane           */
#define DDIF$K_BIT_SEQ_BY_PLANE 3       /* Bit sequence by plane            */
#define DDIF$K_BAND_INTERLEAVE_BY_LINE 4 /* Band interleave by line         */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$K_FULL_COMPACTION 1        /* Full pixel compaction            */
#define DDIF$K_PARTIAL_EXPANSION 2      /* Partial pixel expansion          */
#define DDIF$K_FULL_EXPANSION 3         /* Full pixel expansion             */
/* Values of DDIF$_SGA_IMG_PLANE_SIGNIF.				DDIF conforming */
#define DDIF$K_LSB_FIRST 1              /* LSB first                        */
#define DDIF$K_MSB_FIRST 2              /* MSB first                        */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$K_LSB_MSB 1                /* LSB to MSB                       */
#define DDIF$K_MSB_LSB 2                /* MSB to LSB                       */
/* Bit definitions for DDIF$_FRM_FLAGS.					DDIF conforming */
#define ddif$m_flow_around 1
#define ddif$m_frame_border 2
#define ddif$m_frame_background_fill 4
struct frm_flags {
    unsigned ddif$v_flow_around : 1;    /* Flow around                      */
    unsigned ddif$v_frame_border : 1;   /* Frame border                     */
    unsigned ddif$v_frame_background_fill : 1; /* Frame background fill     */
    unsigned ddif$v_frm_fill_0 : 13;
    unsigned ddif$v_frm_fill : 16;
    } ;
/* Values of DDIF$_SGA_FRM_POSITION_C.                                      */
#define DDIF$K_FRAME_FIXED 0            /* Fixed position		FRMFXD_POSITION_X_C to FRMFXD_POSITION_Y */
#define DDIF$K_FRAME_INLINE 1           /* Inline position		FRMINL_BASE_OFFSET_C to FRMINL_BASE_OFFSET */
#define DDIF$K_FRAME_GALLEY 2           /* Galley position		FRMGLY_VERTICAL to FRMGLY_HORIZONTAL */
#define DDIF$K_FRAME_MARGIN 3           /* Margin position		FRMMAR_BASE_OFFSET_C to FRMMAR_HORIZONTAL */
/* Values of DDIF$_SGA_FRMGLY_VERTICAL.					DDIF conforming */
#define DDIF$K_FRMGLY_BELOW_CURRENT 1   /* Below current line               */
#define DDIF$K_FRMGLY_BOTTOM 2          /* Bottom of galley                 */
#define DDIF$K_FRMGLY_TOP 3             /* Top of galley                    */
#define DDIF$K_FRMGLY_ABOVE_CURRENT 4   /* Above current line               */
/* Values of DDIF$_SGA_FRMMAR_HORIZONTAL.				DDIF conforming */
#define DDIF$K_FRMMAR_CLOSEST_EDGE 1    /* Side closest edge                */
#define DDIF$K_FRMMAR_FURTHEST_EDGE 2   /* Side furthest edge               */
#define DDIF$K_FRMMAR_LEFT 3            /* Left of galleys                  */
#define DDIF$K_FRMMAR_RIGHT 4           /* Right of galleys                 */
/* Values of DDIF$_SGA_IMG_PIXEL_GRP_ORDER.				DDIF conforming */
#define DDIF$K_STD_PIXEL_ORDER 1        /* Standard pixel order             */
#define DDIF$K_REV_PIXEL_ORDER 2        /* Reverse pixel order              */
/* Item codes for Content Definition aggregate.                             */
#define DDIF$_CTD_LABEL 6401            /* Content label		String */
#define DDIF$_CTD_EXTERNAL_TARGET 6402  /* Content reference target	String */
#define DDIF$_CTD_EXTERNAL_ERF_INDEX 6403 /* Content reference index	Integer */
#define DDIF$_CTD_VALUE 6404            /* Content value		Sequence of content */
#define DDIF$_CTD_PRIVATE_DATA 6405     /* Content private data		Sequence of DDIF$_PVT */
#define DDIF$_CTD_MAX 6406              /* Maximum code plus 1              */
/* Item codes for Font Definition aggregate.                                */
#define DDIF$_FTD_NUMBER 6657           /* Font number			Integer */
#define DDIF$_FTD_IDENTIFIER 6658       /* Font identifier		String */
#define DDIF$_FTD_PRIVATE_DATA 6659     /* Font private data		Sequence of DDIF$_PVT */
#define DDIF$_FTD_MAX 6660              /* Maximum code plus 1              */
/* Item codes for Line Style Definition aggregate.                          */
#define DDIF$_LSD_NUMBER 6913           /* Line style number		Integer */
#define DDIF$_LSD_PATTERN 6914          /* Line style pattern		Array of integer */
#define DDIF$_LSD_PRIVATE_DATA 6915     /* Line style private data	Sequence of DDIF$_PVT */
#define DDIF$_LSD_MAX 6916              /* Maximum code plus 1              */
/* Item codes for Path Definition aggregate.                                */
#define DDIF$_PHD_NUMBER 7169           /* Path number			Integer */
#define DDIF$_PHD_DESCRIPTION 7170      /* Path description		Sequence of DDIF$_PTH */
#define DDIF$_PHD_PRIVATE_DATA 7171     /* Path private data		Sequence of DDIF$_PVT */
#define DDIF$_PHD_MAX 7172              /* Maximum code plus 1              */
/* Item codes for Pattern Definition aggregate.                             */
#define DDIF$_PTD_NUMBER 7425           /* Pattern number		Integer */
#define DDIF$_PTD_DEFN_C 7426           /* Pattern definition choice	Enumeration */
#define DDIF$_PTD_SOL_COLOR_C 7427      /* Color choice			Enumeration */
#define DDIF$_PTD_SOL_COLOR_R 7428      /* Color red intensity		Single precision floating */
#define DDIF$_PTD_SOL_COLOR_G 7429      /* Color green intensity	Single precision floating */
#define DDIF$_PTD_SOL_COLOR_B 7430      /* Color blue intensity		Single precision floating */
#define DDIF$_PTD_PAT_NUMBER 7431       /* Pattern number		Integer */
#define DDIF$_PTD_PAT_COLORS 7432       /* Pattern colors		Array of integer */
#define DDIF$_PTD_RAS_PATTERN 7433      /* Pattern image		DDIF$_IDU */
#define DDIF$_PTD_PRIVATE_DATA 7434     /* Pattern private data		Sequence of DDIF$_PVT */
#define DDIF$_PTD_MAX 7435              /* Maximum code plus 1              */
/* Values of DDIF$_PTD_DEFN_C.                                              */
#define DDIF$K_SOLID_COLOR 0            /* Solid color			PTD_SOL_COLOR_C to PTD_SOL_COLOR_B */
#define DDIF$K_STANDARD_PATTERN 1       /* Standard pattern		PTD_PAT_NUMBER to PTD_PAT_COLORS */
#define DDIF$K_RASTER_PATTERN 2         /* Raster pattern		PTD_RAS_PATTERN */
/* Values of DDIF$_PTD_SOL_COLOR_C.                                         */
#define DDIF$K_RGB_COLOR 0              /* RGB color			PTD_SOL_COLOR_R to PTD_SOL_COLOR_B */
#define DDIF$K_TRANSPARENCY 1           /* Transparency			None */
/* Item codes for Segment Binding aggregate.                                */
#define DDIF$_SGB_VARIABLE_NAME 7681    /* Variable name		String */
#define DDIF$_SGB_VARIABLE_VALUE_C 7682 /* Variable value choice	Enumeration */
#define DDIF$_SGB_CTR_TRIGGER_C 7683    /* Counter trigger		Enumeration */
#define DDIF$_SGB_CTR_TRIGGER 7684      /*				Variable */
#define DDIF$_SGB_CTR_INIT_C 7685       /* Counter initializer		Expression enumeration */
#define DDIF$_SGB_CTR_INIT 7686         /*				Variable */
#define DDIF$_SGB_CTR_STYLE 7687        /* Counter style		Sequence of DDIF$_CTS */
#define DDIF$_SGB_CTR_TYPE 7688         /* Counter type			Enumeration */
#define DDIF$_SGB_COM_STRING_EXPR_C 7689 /* Computed string expression	Array of enumeration */
#define DDIF$_SGB_COM_STRING_EXPR 7690  /*				Array of variable */
#define DDIF$_SGB_RCD_LIST 7691         /* Record definition list	Sequence of DDIF$_RCD */
#define DDIF$_SGB_MAX 7692              /* Maximum code plus 1              */
/* Values of DDIF$_SGB_VARIABLE_VALUE_C.                                    */
#define DDIF$K_COUNTER_VARIABLE 0       /* Counter variable		SGB_CTR_TRIGGER_C to SGB_CTR_TYPE */
#define DDIF$K_COMPUTED_VARIABLE 1      /* Computed variable		SGB_COM_STRING_EXPR_C to SGB_COM_STRING_EXPR */
#define DDIF$K_LIST_VARIABLE 2          /* List variable		SGB_RCD_LIST */
/* Values of DDIF$_SGB_CTR_TRIGGER_C.                                       */
#define DDIF$K_TAGGED_SEGMENT_TRIGGER 0 /* Counts tagged segments	String */
#define DDIF$K_LAYOUT_OBJECT_TRIGGER 1  /* Counts layout objects	Enumeration */
/* Values of DDIF$_SGB_CTR_TRIGGER for DDIF$K_OBJECT_TRIGGER.		DDIF conforming */
#define DDIF$K_DOCUMENT_LAYOUT_OBJECT 1 /* Document layout object           */
#define DDIF$K_PAGE_SET_LAYOUT_OBJECT 2 /* Page set layout object           */
#define DDIF$K_PAGE_LAYOUT_OBJECT 3     /* Page layout object               */
#define DDIF$K_FRAME_LAYOUT_OBJECT 4    /* Frame layout object              */
#define DDIF$K_BLOCK_LAYOUT_OBJECT 5    /* Block layout object              */
#define DDIF$K_LINE_LAYOUT_OBJECT 6     /* Line layout object               */
#define DDIF$K_POINT_PAGE_OBJECT 7      /* Point page object                */
/* Values of DDIF$_SGB_CTR_TYPE.					DDIF conforming */
#define DDIF$K_MILITARY_COUNTER 1       /* Military                         */
#define DDIF$K_OFFICE_COUNTER 2         /* Office                           */
#define DDIF$K_PAGE_RELATIVE_COUNTER 3  /* Page relative                    */
#define DDIF$K_CONDITIONAL_COUNTER 4    /* Conditional                      */
/* Values of DDIF$_SGB_COM_STRING_EXPR_C.                                   */
#define DDIF$K_TEXT_ELEMENT 0           /* Text element			Character string */
#define DDIF$K_VARIABLE_ELEMENT 1       /* Variable reference element	String */
/* Item codes for Type Definition aggregate.                                */
#define DDIF$_TYD_LABEL 7937            /* Type label			String */
#define DDIF$_TYD_PARENT 7938           /* Type parent			String */
#define DDIF$_TYD_ATTRIBUTES 7939       /* Type attributes		DDIF$_SGA */
#define DDIF$_TYD_PRIVATE_DATA 7940     /* Type private data		Sequence of DDIF$_PVT */
#define DDIF$_TYD_MAX 7941              /* Maximum code plus 1              */
/* Item codes for Counter Style aggregate.                                  */
#define DDIF$_CTS_STYLE_C 8193          /* Counter style		Enumeration */
#define DDIF$_CTS_STYLE 8194            /*				Variable */
#define DDIF$_CTS_MAX 8195              /* Maximum code plus 1              */
/* Values of DDIF$_CTS_STYLE_C.                                             */
#define DDIF$K_NUMBER_STYLE 0           /* Number style entry		Enumeration */
#define DDIF$K_BULLET_STYLE 1           /* Bullet style entry		Array of character string */
#define DDIF$K_STYLE_SEPARATOR 2        /* Style separator entry	Character string */
/* Values of DDIF$_CTS_STYLE for DDIF$K_NUMBER_STYLE.			DDIF conforming */
#define DDIF$K_ARABIC_COUNTER 1         /* Arabic                           */
#define DDIF$K_L_ROMAN_COUNTER 2        /* Lowercase roman                  */
#define DDIF$K_U_ROMAN_COUNTER 3        /* Uppercase roman                  */
#define DDIF$K_L_LATIN_COUNTER 4        /* Lowercase latin                  */
#define DDIF$K_U_LATIN_COUNTER 5        /* Uppercase latin                  */
#define DDIF$K_W_ARABIC_COUNTER 6       /* Wide arabic                      */
#define DDIF$K_WL_ROMAN_COUNTER 7       /* Wide lowercase roman             */
#define DDIF$K_WU_ROMAN_COUNTER 8       /* Wide uppercase roman             */
#define DDIF$K_WL_LATIN_COUNTER 9       /* Wide lowercase latin             */
#define DDIF$K_WU_LATIN_COUNTER 10      /* Wide uppercase latin             */
#define DDIF$K_WK_50_COUNTER 11         /* Wide katakana 50                 */
#define DDIF$K_WK_IROHA_COUNTER 12      /* Wide katakana iroha              */
#define DDIF$K_HEBREW_COUNTER 13        /* Hebrew                           */
#define DDIF$K_HANGUL_COUNTER 14        /* Hangul                           */
#define DDIF$K_HANZI_COMPLEX_COUNTER 15 /* Hanzi complex                    */
#define DDIF$K_HANZI_SIMPLE_COUNTER 16  /* Hanzi simple                     */
#define DDIF$K_HANZI_OLD_COUNTER 17     /* Hanzi old                        */
#define DDIF$K_HANYU_COMPLEX_COUNTER 18 /* Hanyu complex                    */
#define DDIF$K_HANYU_SIMPLE_COUNTER 19  /* Hanyu simple                     */
#define DDIF$K_HANYU_OLD_COUNTER 20     /* Hanyu old                        */
/* Item codes for Occurrence Definition aggregate.                          */
#define DDIF$_OCC_OCCURRENCE_C 8449     /* Occurrence choice		Enumeration */
#define DDIF$_OCC_STRUCTURE_ELEMENT_C 8450 /* Structure element choice	Enumeration */
#define DDIF$_OCC_STRUCTURE_ELEMENT 8451 /*				Variable */
#define DDIF$_OCC_MAX 8452              /* Maximum code plus 1              */
/* Values of DDIF$_OCC_OCCURRENCE_C.                                        */
#define DDIF$K_REQUIRED_OCCURRENCE 0    /* Required occurrence              */
#define DDIF$K_OPTIONAL_OCCURRENCE 1    /* Optional occurrence              */
#define DDIF$K_REPEAT_OCCURRENCE 2      /* Repeated occurrence              */
#define DDIF$K_OPT_RPT_OCCURRENCE 3     /* Optional repeated occurrence     */
/* Item codes for Record Definition aggregate.                              */
#define DDIF$_RCD_TYPE 8705             /* Record type			String */
#define DDIF$_RCD_TAG 8706              /* Record tag			String */
#define DDIF$_RCD_CONTENTS 8707         /* Record contents		Array of string */
#define DDIF$_RCD_MAX 8708              /* Maximum code plus 1              */
/* Item codes for RGB Lookup Table Entry aggregate.                         */
#define DDIF$_RGB_LUT_INDEX 8961        /* LUT index			Integer */
#define DDIF$_RGB_RED_VALUE 8962        /* Red value			Single precision floating */
#define DDIF$_RGB_GREEN_VALUE 8963      /* Green value			Single precision floating */
#define DDIF$_RGB_BLUE_VALUE 8964       /* Blue value			Single precision floating */
#define DDIF$_RGB_MAX 8965              /* Maximum code plus 1              */
/* Item codes for Transform aggregate.                                      */
#define DDIF$_TRN_PARAMETER_C 9217      /* Transform element		Enumeration */
#define DDIF$_TRN_PARAMETER 9218        /*				Variable */
#define DDIF$_TRN_MAX 9219              /* Maximum code plus 1              */
/* Values of DDIF$_TRN_PARAMETER_C.                                         */
#define DDIF$K_X_SCALE 0                /* X scale factor		Single precision floating */
#define DDIF$K_Y_SCALE 1                /* Y scale factor		Single precision floating */
#define DDIF$K_X_TRANSLATE 2            /* X translation		Single precision floating */
#define DDIF$K_Y_TRANSLATE 3            /* Y translation		Single precision floating */
#define DDIF$K_ROTATE 4                 /* Rotation			Single precision floating */
#define DDIF$K_SKEW 5                   /* Skew				Single precision floating */
#define DDIF$K_MATRIX_2_BY_3 6          /* 2 by 3 matrix		Array[6] of single precision floating */
#define DDIF$K_MATRIX_3_BY_3 7          /* 3 by 3 matrix		Array[9] of single precision floating */
/* Item codes for Generic Layout I aggregate.                               */
#define DDIF$_LG1_PRIVATE_DATA 9473     /* Private data			Sequence of DDIF$_PVT */
#define DDIF$_LG1_PAGE_DESCRIPTIONS 9474 /* Page descriptions		Sequence of DDIF$_PGD */
#define DDIF$_LG1_MAX 9475              /* Maximum code plus 1              */
/* Item codes for Specific Layout I aggregate.                              */
#define DDIF$_LS1_LAYOUT_C 9729         /* Layout choice		Array of enumeration */
#define DDIF$_LS1_LAYOUT 9730           /* Layout description		Array of variable */
#define DDIF$_LS1_MAX 9731              /* Maximum code plus 1              */
/* Values of DDIF$_LS1_LAYOUT_C.                                            */
#define DDIF$K_SPECIFIC_PAGE 0          /* Specific page		DDIF$_PGD */
#define DDIF$K_REFERENCED_PAGE 1        /* Referenced page		String */
/* Item codes for Wrap Attributes I aggregate.                              */
#define DDIF$_LW1_WRAP_FORMAT 9985      /* Wrap format			Enumeration */
#define DDIF$_LW1_QUAD_FORMAT 9986      /* Quad format			Enumeration */
#define DDIF$_LW1_HYPHENATION_FLAGS 9987 /* Hyphenation flags		Longword */
#define DDIF$_LW1_MAXIMUM_HYPH_LINES 9988 /* Maximum hyphen lines		Integer */
#define DDIF$_LW1_MINIMUM_ORPHAN_SIZE 9989 /* Minimum orphan size		Integer */
#define DDIF$_LW1_MINIMUM_WIDOW_SIZE 9990 /* Minimum widow size		Integer */
#define DDIF$_LW1_PRES_DIR 9991         /* Present direction		Enumeration */
#define DDIF$_LW1_ITEM_CHANGE_LIST 9992 /* Item change list             Item change list */
#define DDIF$_LW1_MAX 9993              /* Maximum code plus 1              */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$_LW1_MAXIMUM_ORPHAN_SIZE 9989 /* Maximum orphan size           */
#define DDIF$_LW1_MAXIMUM_WIDOW_SIZE 9990 /* Maximum widow size             */
/* Bit definitions for DDIF$_LW1_HYPHENATION_FLAGS.			DDIF conforming */
#define ddif$m_hyph_allowed 1
#define ddif$m_hyph_paragraph_end 2
#define ddif$m_hyph_galley_end 4
#define ddif$m_hyph_page_end 8
#define ddif$m_hyph_capitalized_word 16
struct lw1_hyphen_flags {
    unsigned ddif$v_hyph_allowed : 1;   /* Hyphenation allowed              */
    unsigned ddif$v_hyph_paragraph_end : 1; /* Paragraph end                */
    unsigned ddif$v_hyph_galley_end : 1; /* Galley end                      */
    unsigned ddif$v_hyph_page_end : 1;  /* Page end                         */
    unsigned ddif$v_hyph_capitalized_word : 1; /* Capitalized word          */
    unsigned ddif$v_lw1_fill_0 : 11;
    unsigned ddif$v_lw1_fill : 16;
    } ;
/* Values of DDIF$_LW1_PRES_DIR and DDIF$_GLA_PRES_DIR.                     */
#define DDIF$K_GALLEY_DEFAULT 0         /* Galley default (only in DDIF$_LW1_PRES_DIR item) */
#define DDIF$K_HORIZ_LEFT_TO_RIGHT 1    /* Horizontal left to right         */
#define DDIF$K_HORIZ_RIGHT_TO_LEFT 2    /* Horizontal right to left         */
#define DDIF$K_VERT_TOP_TO_BOTTOM 3     /* Vertical top to bottom           */
/* Item codes for Layout Attributes I aggregate.                            */
#define DDIF$_LL1_INITIAL_DIRECTIVE 10241 /* Initial directive		Enumeration */
#define DDIF$_LL1_GALLEY_SELECT 10242   /* Galley select		String */
#define DDIF$_LL1_BREAK_BEFORE 10243    /* Break before			Enumeration */
#define DDIF$_LL1_BREAK_WITHIN 10244    /* Break within			Enumeration */
#define DDIF$_LL1_BREAK_AFTER 10245     /* Break after			Enumeration */
#define DDIF$_LL1_INITIAL_INDENT_C 10246 /* Initial indent		Measurement enumeration */
#define DDIF$_LL1_INITIAL_INDENT 10247  /*				Variable */
#define DDIF$_LL1_BEGIN_INDENT_C 10248  /* Begin indent			Measurement enumeration */
#define DDIF$_LL1_BEGIN_INDENT 10249    /*				Variable */
#define DDIF$_LL1_END_INDENT_C 10250    /* End indent			Measurement enumeration */
#define DDIF$_LL1_END_INDENT 10251      /*				Variable */
#define DDIF$_LL1_SPACE_BEFORE_C 10252  /* Space before			Measurement enumeration */
#define DDIF$_LL1_SPACE_BEFORE 10253    /*				Variable */
#define DDIF$_LL1_SPACE_AFTER_C 10254   /* Space after			Measurement enumeration */
#define DDIF$_LL1_SPACE_AFTER 10255     /*				Variable */
#define DDIF$_LL1_LEADING_RATIO_N 10256 /* Leading ratio		Integer */
#define DDIF$_LL1_LEADING_RATIO_D 10257 /*				Integer */
#define DDIF$_LL1_LEADING_CONSTANT_C 10258 /* Leading constant		Measurement enumeration */
#define DDIF$_LL1_LEADING_CONSTANT 10259 /*				Variable */
#define DDIF$_LL1_TAB_STOPS 10260       /* Tab stops			Sequence of DDIF$_TBS */
#define DDIF$_LL1_ITEM_CHANGE_LIST 10261 /* Item change list             Item change list */
#define DDIF$_LL1_MAX 10262             /* Maximum code plus 1              */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$_LL1_LEFT_INDENT_C 10248   /* Left indent                      */
#define DDIF$_LL1_LEFT_INDENT 10249     /*                                  */
#define DDIF$_LL1_RIGHT_INDENT_C 10250  /* Right indent                     */
#define DDIF$_LL1_RIGHT_INDENT 10251    /*                                  */
/* Values of DDIF$_LL1_BREAK_BEFORE, DDIF$_LL1_BREAK_WITHIN,		DDIF conforming */
/* DDIF$_LL1_BREAK_AFTER.                                                   */
#define DDIF$K_BREAK_ALWAYS 1           /* Break always                     */
#define DDIF$K_BREAK_NEVER 2            /* Break never                      */
#define DDIF$K_BREAK_IF_NEEDED 3        /* Break if needed                  */
#define DDIF$K_BREAK_TO_PAGE 4          /* Break to page                    */
#define DDIF$K_BREAK_TO_LEFTPAGE 5      /* Break to left page               */
#define DDIF$K_BREAK_TO_RIGHTPAGE 6     /* Break to right page              */
/* Item codes for Galley Attributes aggregate.                              */
#define DDIF$_GLA_TOP_MARGIN_C 10497    /* Galley top margin		Measurement enumeration */
#define DDIF$_GLA_TOP_MARGIN 10498      /*				Variable */
#define DDIF$_GLA_LEFT_MARGIN_C 10499   /* Galley left margin		Measurement enumeration */
#define DDIF$_GLA_LEFT_MARGIN 10500     /*				Variable */
#define DDIF$_GLA_RIGHT_MARGIN_C 10501  /* Galley right margin		Measurement enumeration */
#define DDIF$_GLA_RIGHT_MARGIN 10502    /*				Variable */
#define DDIF$_GLA_BOTTOM_MARGIN_C 10503 /* Galley bottom margin		Measurement enumeration */
#define DDIF$_GLA_BOTTOM_MARGIN 10504   /*				Variable */
#define DDIF$_GLA_PRES_DIR 10505        /* Galley present direction	Enumeration */
#define DDIF$_GLA_ITEM_CHANGE_LIST 10506 /* Item change list             Item change list */
#define DDIF$_GLA_MAX 10507             /* Maximum code plus 1              */
/* Item codes for Page Description aggregate.                               */
#define DDIF$_PGD_LABEL 10753           /* Label			String */
#define DDIF$_PGD_PRIVATE_DATA 10754    /* Private data			Sequence of DDIF$_PVT */
#define DDIF$_PGD_DESC_C 10755          /* Page description		Enumeration */
#define DDIF$_PGD_DESC 10756            /*				Variable */
#define DDIF$_PGD_FLAGS 10757           /* Flags			Longword */
#define DDIF$_PGD_MAX 10758             /* Maximum code plus 1              */
/* Values of DDIF$_PGD_DESC_C.                                              */
#define DDIF$K_PAGE_SET_DESC 0          /* Page set description		Sequence of DDIF$_PGS */
#define DDIF$K_PAGE_LAYOUT 1            /* Page layout			DDIF$_PGL */
/* Bit definitions for DDIF$_PGD_FLAGS.					DDIF conforming */
#define ddif$m_pgd_point_page 1
struct pgd_flags {
    unsigned ddif$v_pgd_point_page : 1; /* Point page                       */
    unsigned ddif$v_pgd_fill_0 : 15;
    unsigned ddif$v_pgd_fill : 16;
    } ;
/* Item codes for Page Layout aggregate.                                    */
#define DDIF$_PGL_LAYOUT_ID 11009       /* Page layout ID		String */
#define DDIF$_PGL_SIZE_X_NOM_C 11010    /* Page size			Measurement enumeration */
#define DDIF$_PGL_SIZE_X_NOM 11011      /*	X nominal		Variable */
#define DDIF$_PGL_SIZE_X_STR_C 11012    /*				Measurement enumeration */
#define DDIF$_PGL_SIZE_X_STR 11013      /*	X stretch		Variable */
#define DDIF$_PGL_SIZE_X_SHR_C 11014    /*				Measurement enumeration */
#define DDIF$_PGL_SIZE_X_SHR 11015      /*	X shrink		Variable */
#define DDIF$_PGL_SIZE_Y_NOM_C 11016    /*				Measurement enumeration */
#define DDIF$_PGL_SIZE_Y_NOM 11017      /*	Y nominal		Variable */
#define DDIF$_PGL_SIZE_Y_STR_C 11018    /*				Measurement enumeration */
#define DDIF$_PGL_SIZE_Y_STR 11019      /*	Y stretch		Variable */
#define DDIF$_PGL_SIZE_Y_SHR_C 11020    /*				Measurement enumeration */
#define DDIF$_PGL_SIZE_Y_SHR 11021      /*	Y shrink		Variable */
#define DDIF$_PGL_ORIENTATION 11022     /* Page orientation		Enumeration */
#define DDIF$_PGL_PROTOTYPE 11023       /* Page prototype		String */
#define DDIF$_PGL_CONTENT 11024         /* Page content			Sequence of content */
#define DDIF$_PGL_MAX 11025             /* Maximum code plus 1              */
/* Values of DDIF$_PGL_ORIENTATION.					DDIF conforming */
#define DDIF$K_PORTRAIT_ORIENT 1        /* Portrait orientation             */
#define DDIF$K_LANDSCAPE_ORIENT 2       /* Landscape orientation            */
/* Item codes for Page Select aggregate.                                    */
#define DDIF$_PGS_PAGE_SIDE_CRITERIA 11265 /* Page side criteria		Enumeration */
#define DDIF$_PGS_SELECT_PAGE_LAYOUT_C 11266 /* Selected page layout		Enumeration */
#define DDIF$_PGS_SELECT_PAGE_LAYOUT 11267 /* 				Variable */
#define DDIF$_PGS_MAX 11268             /* Maximum code plus 1              */
/* Values of DDIF$_PGS_PAGE_SIDE_CRITERIA.				DDIF conforming */
#define DDIF$K_LEFT_PAGE 1              /* Left page                        */
#define DDIF$K_RIGHT_PAGE 2             /* Right page                       */
#define DDIF$K_EITHER_PAGE 3            /* Either page                      */
/* Values of DDIF$_PGS_SELECT_PAGE_LAYOUT_C.                                */
#define DDIF$K_SELECT_BY_LABEL 0        /* Select by label		String */
#define DDIF$K_SELECT_BY_DEFN 1         /* Select by definition		DDIF$_PGL */
/* Item codes for Tab Stop aggregate.                                       */
#define DDIF$_TBS_POSITION_C 11521      /* Position			Measurement enumeration */
#define DDIF$_TBS_POSITION 11522        /*				Variable */
#define DDIF$_TBS_TYPE 11523            /* Tab stop type		Enumeration */
#define DDIF$_TBS_LEADER 11524          /* Tab stop leader		Character string */
#define DDIF$_TBS_MAX 11525             /* Maximum code plus 1              */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$_TBS_HORIZONTAL_POSITION_C 11521 /* Horizontal position        */
#define DDIF$_TBS_HORIZONTAL_POSITION 11522 /*                              */
/* Values of DDIF$_TBS_TYPE.						DDIF conforming */
#define DDIF$K_BEGIN_TAB 1              /* Begin tab                        */
#define DDIF$K_CENTER_TAB 2             /* Center tab                       */
#define DDIF$K_END_TAB 3                /* End tab                          */
#define DDIF$K_DECIMAL_TAB 4            /* Decimal tab                      */
/* AX04 values retained for upward compatibility.                           */
#define DDIF$K_LEFT_TAB 1               /* Left tab                         */
#define DDIF$K_RIGHT_TAB 3              /* Right tab                        */
/* Item codes for Sequence of Composite Paths aggregate.                    */
#define DDIF$_CPH_PATH_ELEMENTS 11777   /* Path elements		Sequence of DDIF$_PTH */
#define DDIF$_CPH_MAX 11778             /* Maximum code plus 1              */
/* Item codes for Audio content aggregate.                                  */
#define DDIF$_AUD_DURATION_C 12033      /* Duration			Enumeration */
#define DDIF$_AUD_DURATION 12034        /*				Variable */
#define DDIF$_AUD_SAMPLE_RATE_C 12035   /* Sample rate			Enumeration */
#define DDIF$_AUD_SAMPLE_RATE 12036     /*				Variable */
#define DDIF$_AUD_CHANNELS 12037        /* Channels			Integer */
#define DDIF$_AUD_COMPRESSION_TYPE 12038 /* Compression type		Enumeration */
#define DDIF$_AUD_BIT_ORDER 12039       /* Bit order			Enumeration */
#define DDIF$_AUD_BYTE_ORDER 12040      /* Byte order			Enumeration */
#define DDIF$_AUD_PRIVATE_DATA 12041    /* Private data			Sequence of DDIF$_PVT */
#define DDIF$_AUD_DESCRIPTION 12042     /* Description			Array of character string */
#define DDIF$_AUD_DATA_C 12043          /* Audio data			Enumeration */
#define DDIF$_AUD_DATA 12044            /*				Variable */
#define DDIF$_AUD_MAX 12045             /* Maximum code plus 1              */
/* Values of DDIF$_AUD_DURATION_C.                                          */
#define DDIF$K_RTUS 0                   /* RTUs				Integer */
/* Values of DDIF$_AUD_SAMPLE_RATE_C.                                       */
#define DDIF$K_HERTZ 0                  /* Hertz			Single precision floating */
/* Values of DDIF$_AUD_COMPRESSION_TYPE					DDIF Conforming */
#define DDIF$K_AUD_PRIVATE 1            /* private encoding type            */
#define DDIF$K_AUD_LIN_PCM_8_BIT 2      /* 8 bit linear pcm                 */
#define DDIF$K_AUD_LIN_PCM_16_BIT 3     /* 16 bit linear pcm                */
#define DDIF$K_AUD_ULAW_PCM 4           /* ulaw pcm                         */
#define DDIF$K_AUD_ALAW_PCM 5           /* alaw pcm                         */
#define DDIF$K_AUD_CCITT_32K 6          /* 32K CCITT                        */
#define DDIF$K_AUD_CCITT_24K 7          /* 24K CCITT                        */
/* Values of DDIF$_AUD_DATA_C.                                              */
#define DDIF$K_DATA_FRAMES 0            /* Data frames			Sequence of DDIF$_ADF */
/* Item codes for Audio data frame aggregate.                               */
#define DDIF$_ADF_TIME_OFFSET 12289     /* Time offset			Integer */
#define DDIF$_ADF_SILENCE_LEVEL 12290   /* Silence level		Single precision floating */
#define DDIF$_ADF_FRAME_DATA 12291      /* Audio frame data		String */
#define DDIF$_ADF_MAX 12292             /* Maximum code plus 1              */
/* Item codes for Polyline join description aggregate.                      */
#define DDIF$_PLJ_PRIVATE_DATA 12545    /* Private data			Sequence of DDIF$_PVT */
#define DDIF$_PLJ_CURVE_RATIO 12546     /* Curve ratio			Single precision floating */
#define DDIF$_PLJ_1ST_ABSOLUTE_C 12547  /* 1st absolute offset		Measurement enumeration */
#define DDIF$_PLJ_1ST_ABSOLUTE 12548    /*				Variable */
#define DDIF$_PLJ_2ND_ABSOLUTE_C 12549  /* 2nd absolute			Measurement enumeration */
#define DDIF$_PLJ_2ND_ABSOLUTE 12550    /*				Variable */
#define DDIF$_PLJ_1ST_PERCENT 12551     /* 1st percent			Single precision floating */
#define DDIF$_PLJ_2ND_PERCENT 12552     /* 2nd percent			Single precision floating */
#define DDIF$_PLJ_MAX 12553             /* Maximum code plus 1              */
/* Item codes for Polyine join definition aggregate.                        */
#define DDIF$_PJD_LABEL 12801           /* Join definition label	String */
#define DDIF$_PJD_JOINS 12802           /* Join definition joins	Sequence of DDIF$_PLJ */
#define DDIF$_PJD_MAX 12803             /* Maximum code plus 1              */
