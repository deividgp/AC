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
/* @(#)$RCSfile: cda_def.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 04:27:54 $     */
/********************************************************************************************************************************/
/* Created  2-JUN-1991 09:34:33 by VAX SDL V3.2-12     Source: 21-NOV-1990 17:18:47 DDIF$DEVELOP_ROOT:[DDIFBUILD.LIB.SRC]CDA$DEF. */
/********************************************************************************************************************************/
 
/*** MODULE CDA$DEFINITIONS IDENT V1-014 ***/
/*++                                                                        */
/*                                                                          */
/*  COPYRIGHT (c) 1987, 1990 BY                                             */
/*  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.                           */
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
/* General Toolkit processing option item codes for CDA$CREATE_ROOT_AGGREGATE  */
/* and CDA$OPEN_FILE.                                                       */
#define CDA$_LOG_INFORMATION_MESSAGES 2561 /* Automatically log information messages */
#define CDA$_INPUT_FILE_SYSTEM 2562     /* value is ptr to char string input file system name. */
#define CDA$_OUTPUT_FILE_SYSTEM 2563    /* value is ptr to char string output file system name. */
/*			Valid strings are same as those for the DDIF$_ERF_LABEL_TYPE. */
#define CDA$_SKIP_MISSING_REFERENCES 2564 /* ignore missing ext refs and keep procesing. */
#define CDA$_INPUT_FILE_SYSTEM_HANDLE 2565 /* value is handle representing file system context */
#define CDA$_OUTPUT_FILE_SYSTEM_HANDLE 2566 /* value is handle representing file system context */
/* Function codes for CDA$CONVERT and domain$WRITE_format.                  */
#define CDA$_START 1                    /* Start conversion                 */
#define CDA$_CONTINUE 2                 /* Continue conversion              */
#define CDA$_STOP 3                     /* Stop conversion                  */
/* Item list structure definition.                                          */
struct item_list {
    unsigned short int cda$w_item_length; /* Item buffer length             */
    unsigned short int cda$w_item_code; /* Item code                        */
    char *cda$a_item_address;           /* Item buffer address              */
    } ;
/* Item codes for CDA$CONVERT, CDA$OPEN_CONVERTER, CDA$CREATE_MESSAGE_LOG,  */
/* domain$READ_format, and domain$WRITE_format.                             */
#define CDA$_PROCESSING_OPTION 1        /* Processing option                */
#define CDA$_INPUT_FORMAT 2             /* Input document format-name       */
#define CDA$_INPUT_FRONT_END_PROCEDURE 3 /* Input document front-end procedure */
#define CDA$_INPUT_FILE 4               /* Input file specification         */
#define CDA$_INPUT_DEFAULT 5            /* Input default file specification */
#define CDA$_INPUT_PROCEDURE 6          /* Input get data procedure         */
#define CDA$_INPUT_POSITION_PROCEDURE 7 /* Input get position procedure     */
#define CDA$_INPUT_PROCEDURE_PARM 8     /* Input procedure parameter        */
#define CDA$_INPUT_ROOT_AGGREGATE 9     /* Input root aggregate             */
#define CDA$_OUTPUT_FORMAT 10           /* Output document format-name      */
#define CDA$_OUTPUT_BACK_END_PROCEDURE 11 /* Output document back-end procedure */
#define CDA$_OUTPUT_FILE 12             /* Output file specification        */
#define CDA$_OUTPUT_DEFAULT 13          /* Output default file specification */
#define CDA$_OUTPUT_PROCEDURE 14        /* Output procedure                 */
#define CDA$_OUTPUT_PROCEDURE_PARM 15   /* Output procedure parameter       */
#define CDA$_OUTPUT_PROCEDURE_BUFFER 16 /* Output procedure initial buffer  */
#define CDA$_OUTPUT_ROOT_AGGREGATE 17   /* Output root aggregate            */
#define CDA$_OPTIONS_FILE 18            /* Options file specification       */
#define CDA$_INPUT_FRONT_END_DOMAIN 19  /* Input document front-end domain  */
#define CDA$_OUTPUT_BACK_END_DOMAIN 20  /* Output document back-end domain  */
#define CDA$_OPTIONS_LINE 21            /* Options line                     */
#define CDA$_INPUT_PRIVATE_ITEM 22      /* Front End private item           */
#define CDA$_MESSAGE_LOG_FILE 23        /* Message log file spec            */
#define CDA$_DEFAULT_MESSAGE_LOG_FILE 24 /* Default message log file spec   */
#define CDA$_RESULT_MESSAGE_LOG_FILE 25 /* Result message spec              */
#define CDA$_RESULT_MSG_FILE_RET_LEN 26 /* Result message spec length       */
#define CDA$_MESSAGE_OUTPUT_PROCEDURE 27 /* Message-put rtn                 */
#define CDA$_MESSAGE_OUTPUT_PROC_PARM 28 /* Message-put parameter           */
#define CDA$_MESSAGE_OUTPUT_PROC_BUFFER 29 /* Message-put buffer            */
#define CDA$_MESSAGE_FLUSH_PROCEDURE 30 /* Message-flush rtn                */
#define CDA$_MESSAGE_HANDLE 31          /* Message-flush rtn                */
/* Character set identification codes (DEC STD 169).                        */
#define CDA$K_ISO_LATIN1 1              /* ISO Latin 1 (ISO 8859-1)         */
#define CDA$K_ISO_LATIN2 2              /* ISO Latin 2 (ISO 8859-2)         */
#define CDA$K_ISO_LATIN_ARABIC 3        /* ISO Latin-Arabic (ISO 8859-6)    */
#define CDA$K_ISO_LATIN_GREEK 4         /* ISO Latin-Greek (ISO 8859-7)     */
#define CDA$K_ISO_LATIN_HEBREW 6        /* ISO Latin-Hebrew (ISO 8859-8)    */
#define CDA$K_JIS_KATAKANA 32           /* JIS Roman, JIS Katakana (JIS X0201) */
#define CDA$K_DEC_TECH 33               /* DEC Special Graphics, DEC Technical */
#define CDA$K_DEC_MATH_ITALIC 34        /* DEC Mathematics Italic           */
#define CDA$K_DEC_MATH_SYMBOL 35        /* DEC Mathematics Symbol           */
#define CDA$K_DEC_MATH_EXTENSION 36     /* DEC Mathematics Extension        */
#define CDA$K_DEC_PUBLISHING 37         /* DEC Publishing                   */
#define CDA$K_DEC_KANJI 64              /* DEC Kanji (JIS X0208)            */
#define CDA$K_DEC_HANZI 65              /* DEC Hanzi (GB 2312)              */
/* Synonym definitions for compatibility                                    */
#define CDA$K_ISO_LATIN6 3              /* Obsolete synonym                 */
#define CDA$K_ISO_LATIN7 4              /* Obsolete synonym                 */
#define CDA$K_ISO_LATIN8 6              /* Obsolete synonym                 */
/* Values of the add-info parameter for CDA$LOCATE_ITEM and CDA$STORE_ITEM when */
/* the item data type is general floating point.                            */
#define CDA$K_F_FLOAT 0                 /* VAX F-floating                   */
#define CDA$K_D_FLOAT 1                 /* VAX D-floating                   */
#define CDA$K_G_FLOAT 2                 /* VAX G-floating                   */
#define CDA$K_H_FLOAT 3                 /* VAX H-floating                   */
#define CDA$K_IEEE_754_S_FLOAT 4        /* IEEE 754 single precision        */
#define CDA$K_IEEE_754_D_FLOAT 5        /* IEEE 754 double precision        */
#define CDA$K_NATIVE_S_FLOAT 6          /* Native single precision  VAX: F-float non-VAX: IEEE 754 single */
#define CDA$K_NATIVE_D_FLOAT 7          /* Native double precision  VAX: G-float non-VAX: IEEE 754 double */
/* Item codes for CDA$STATUS_TO_MESSAGE, CDA$WRITE_MESSAGE.                 */
#define CDA$_MESSAGE_SEVERITY 1         /* Message severity                 */
#define CDA$_MESSAGE_PREFIX 2           /* Message prefix                   */
#define CDA$_MESSAGE_PARAMETER 3        /* Messge parameter                 */
/* Values of the SEVERITY item code for CDA$STATUS_TO_MESSAGE and           */
/* CDA$WRITE_MESSAGE routines.                                              */
#define CDA$K_WARNING 0                 /* Warning = 000                    */
#define CDA$K_NORMAL 1                  /* Normal = 001                     */
#define CDA$K_ERROR 2                   /* Error = 010                      */
#define CDA$K_INFORMATIONAL 3           /* Informational = 011              */
#define CDA$K_FATAL 4                   /* Fatal = 100                      */
