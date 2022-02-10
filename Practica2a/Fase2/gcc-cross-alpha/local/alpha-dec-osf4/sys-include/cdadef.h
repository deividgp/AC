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
/* @(#)$RCSfile: cdadef.h,v $ $Revision: 4.2.7.2 $ (DEC) $Date: 1994/05/10 16:33:37 $     */
/********************************************************************************************************************************/
/* Created  6-APR-1994 12:05:36 by VAX SDL V3.2-12     Source:  6-APR-1994 11:42:16 CDA$LOCAL_ROOT:[CDABUILD.LIB.SRC]CDADEF.SDL;2 */
/********************************************************************************************************************************/

/*** MODULE CDA_DEFINITIONS IDENT V1-006 ***/
#ifndef _cdadef_
#define _cdadef_
/*++                                                                        */
/*                                                                          */
/*  COPYRIGHT (c) 1987, 1992 BY                                             */
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
/* General Toolkit processing option item codes for cda_create_root_aggregate */
/* and cda_open_file.                                                       */
#define CDA_LOG_INFORMATION_MESSAGES 2561 /* Automatically log information messages */
#define CDA_INPUT_FILE_SYSTEM 2562      /* value is ptr to char string input file system name. */
#define CDA_OUTPUT_FILE_SYSTEM 2563     /* value is ptr to char string output file system name. */
/*			Valid strings are same as those for the DDIF$_ERF_LABEL_TYPE. */
#define CDA_SKIP_MISSING_REFERENCES 2564 /* ignore missing ext refs and keep procesing. */
#define CDA_INPUT_FILE_SYSTEM_HANDLE 2565 /* value is handle representing file system context */
#define CDA_OUTPUT_FILE_SYSTEM_HANDLE 2566 /* value is handle representing file system context */
/* Function codes for cda_convert and domain_write_format.                  */
#define CDA_START 1                     /* Start conversion                 */
#define CDA_CONTINUE 2                  /* Continue conversion              */
#define CDA_STOP 3                      /* Stop conversion                  */
struct item_list {
    unsigned short int cda_w_item_length; /* Item buffer length             */
    unsigned short int cda_w_item_code; /* Item code                        */
    char *cda_a_item_address;           /* Item buffer address              */
    } ;
/* Item codes for cda_convert, cda_open_converter, cda_create_message_log,  */
/* domain_read_format, and domain_write_format.                             */
#define CDA_PROCESSING_OPTION 1         /* Processing option                */
#define CDA_INPUT_FORMAT 2              /* Input document format-name       */
#define CDA_INPUT_FRONT_END_PROCEDURE 3 /* Input document front-end procedure */
#define CDA_INPUT_FILE 4                /* Input file specification         */
#define CDA_INPUT_DEFAULT 5             /* Input default file specification */
#define CDA_INPUT_PROCEDURE 6           /* Input get data procedure         */
#define CDA_INPUT_POSITION_PROCEDURE 7  /* Input get position procedure     */
#define CDA_INPUT_PROCEDURE_PARM 8      /* Input procedure parameter        */
#define CDA_INPUT_ROOT_AGGREGATE 9      /* Input root aggregate             */
#define CDA_OUTPUT_FORMAT 10            /* Output document format-name      */
#define CDA_OUTPUT_BACK_END_PROCEDURE 11 /* Output document back-end procedure */
#define CDA_OUTPUT_FILE 12              /* Output file specification        */
#define CDA_OUTPUT_DEFAULT 13           /* Output default file specification */
#define CDA_OUTPUT_PROCEDURE 14         /* Output procedure                 */
#define CDA_OUTPUT_PROCEDURE_PARM 15    /* Output procedure parameter       */
#define CDA_OUTPUT_PROCEDURE_BUFFER 16  /* Output procedure initial buffer  */
#define CDA_OUTPUT_ROOT_AGGREGATE 17    /* Output root aggregate            */
#define CDA_OPTIONS_FILE 18             /* Options file specification       */
#define CDA_INPUT_FRONT_END_DOMAIN 19   /* Input document front-end domain  */
#define CDA_OUTPUT_BACK_END_DOMAIN 20   /* Output document back-end domain  */
#define CDA_OPTIONS_LINE 21             /* Options line                     */
#define CDA_INPUT_PRIVATE_ITEM 22       /* Front End private item           */
#define CDA_MESSAGE_LOG_FILE 23         /* Message log file spec            */
#define CDA_DEFAULT_MESSAGE_LOG_FILE 24 /* Default message log file spec    */
#define CDA_RESULT_MESSAGE_LOG_FILE 25  /* Result message spec              */
#define CDA_RESULT_MSG_FILE_RET_LEN 26  /* Result message spec length       */
#define CDA_MESSAGE_OUTPUT_PROCEDURE 27 /* Message-put rtn                  */
#define CDA_MESSAGE_OUTPUT_PROC_PARM 28 /* Message-put parameter            */
#define CDA_MESSAGE_OUTPUT_PROC_BUFFER 29 /* Message-put buffer             */
#define CDA_MESSAGE_FLUSH_PROCEDURE 30  /* Message-flush rtn                */
#define CDA_MESSAGE_HANDLE 31           /* Message-flush rtn                */
#define CDA_SEARCH_DOMAIN 32            /* Domain for GetFormatList         */
#define CDA_SEARCH_FEBE 33              /* FeBe parameter for GetFormatList */
#define CDA_YIELD_ROUTINE 34            /* cda_convert user callback routine */
#define CDA_YIELD_PARM 35               /* cda_convert user callback routine prm */
/* Item codes for dots_pack and dots_unpack.                                */
#define DOTS_INPUT_DEFAULT 1            /* Input default file name          */
#define DOTS_INPUT_FILE 2               /* Input file name                  */
#define DOTS_OUTPUT_DEFAULT 3           /* Output default file name         */
#define DOTS_OUTPUT_FILE 4              /* Output file name                 */
#define DOTS_OUTPUT_RESULT 5            /* Output resultant file name       */
#define DOTS_MISSING_REFERENCE 6        /* Name of missing reference        */
#define DOTS_CONTROLLED_COPY 7          /* Obey ERF_CONTROL item when packing */
#define DOTS_INPUT_PROCEDURE 8          /* user-supplied get-rtn            */
#define DOTS_INPUT_PROCEDURE_PARM 9     /* parameter for get-rtn            */
#define DOTS_OUTPUT_PROCEDURE 10        /* user-supplied put-rtn            */
#define DOTS_OUTPUT_PROCEDURE_PARM 11   /* parameter for put-rtn            */
#define DOTS_OUTPUT_PROCEDURE_BUFFER 12 /* addr & length of initial buffer  */
#define DOTS_INPUT_DEFAULT_TYPE 13      /* name of file system to which INPUT_DEFAULT applies */
#define DOTS_INPUT_FILE_TYPE 14         /* name of file system to which INPUT_FILE applies */
#define DOTS_OUTPUT_DEFAULT_TYPE 15     /* name of file system to which OUTPUT_DEFAULT applies */
#define DOTS_OUTPUT_FILE_TYPE 16        /* name of file system to which OUTPUT_FILE applies */
#define DOTS_SIMPLE_ENCODE 17           /* wrap simple DDIF or DTIF (no refs) into DOTS */
#define DOTS_ALWAYS_ENCODE 18           /* always create DOTS encoding even when doc has no refs */
/* Synonym definitions for ease-of-use                                      */
/* These are duplicates of the CDA_ definitions and MUST be equivalent.     */
#define DOTS_INPUT_FILE_SYSTEM 2562
#define DOTS_OUTPUT_FILE_SYSTEM 2563
#define DOTS_SKIP_MISSING_REFERENCES 2564
#define DOTS_INPUT_FILE_SYSTEM_HANDLE 2565
#define DOTS_OUTPUT_FILE_SYSTEM_HANDLE 2566
/* general UNKNOWN choice enumeration for backward compatibility use when skipping unknown choices */
#define CDA_K_UNKNOWN 32767             /* Unknown choice                   */
/* Domain constants for GetFormatList.                                      */
#define CDA_ALL_DOMAINS 1               /* All domains.                     */
#define CDA_DDIF_DOMAIN 2               /* Only DDIF domain.                */
#define CDA_DTIF_DOMAIN 3               /* Only DTIF domain.                */
/* FeBe constants for GetFormatList.                                        */
#define CDA_BOTH_FEBE 1                 /* Both front and back end converters. */
#define CDA_FRONT_END 2                 /* Front end converters only.       */
#define CDA_BACK_END 3                  /* Back end converters only.        */
/* CdaGetDataType Item Codes.                                               */
#define CDA_FILE_NAME 1                 /* File name string                 */
#define CDA_FILE_BUFFER 2               /* File content                     */
#define CDA_FILE_TYPE_STRING 3          /* String type return pointer       */
#define CDA_FILE_TYPE_LENGTH 4          /* Return string length             */
#define CDA_FILE_TYPE_VALUE 5           /* Core type return value           */
#define CDA_MAGIC_FILE_NAME 6           /* Alternate magic file name        */
/* CdaGetDataType Core File Type Return Values.                             */
#define CDA_K_FILE_CONTENT_DDIF 1       /* File contains DDIF               */
#define CDA_K_FILE_CONTENT_DOTS 2       /*  ""     ""    DOTS               */
#define CDA_K_FILE_CONTENT_DTIF 3       /*  ""     ""    DTIF               */
#define CDA_K_FILE_CONTENT_PS 4         /*  ""     ""    PostScript         */
#define CDA_K_FILE_CONTENT_TEXT 5       /*  ""     ""    Text               */
/* Character set identification codes (DEC STD 169).                        */
#define CDA_K_ISO_LATIN1 1              /* ISO Latin 1 (ISO 8859-1)         */
#define CDA_K_ISO_LATIN2 2              /* ISO Latin 2 (ISO 8859-2)         */
#define CDA_K_ISO_LATIN_ARABIC 3        /* ISO Latin-Arabic (ISO 8859-6)    */
#define CDA_K_ISO_LATIN_GREEK 4         /* ISO Latin-Greek (ISO 8859-7)     */
#define CDA_K_ISO_LATIN_HEBREW 6        /* ISO Latin-Hebrew (ISO 8859-8)    */
#define CDA_K_JIS_KATAKANA 32           /* JIS Roman, JIS Katakana (JIS X0201) */
#define CDA_K_DEC_TECH 33               /* DEC Special Graphics, DEC Technical */
#define CDA_K_DEC_MATH_ITALIC 34        /* DEC Mathematics Italic           */
#define CDA_K_DEC_MATH_SYMBOL 35        /* DEC Mathematics Symbol           */
#define CDA_K_DEC_MATH_EXTENSION 36     /* DEC Mathematics Extension        */
#define CDA_K_DEC_PUBLISHING 37         /* DEC Publishing                   */
#define CDA_K_DEC_KANJI 64              /* DEC Kanji (JIS X0208)            */
#define CDA_K_DEC_HANZI 65              /* DEC Hanzi (GB 2312)              */
#define CDA_K_DEC_HANGUL 66             /* DEC Hangul                       */
#define CDA_K_DEC_CNS11643 67           /* DEC Hanyu (CNS11643)             */
#define CDA_K_DEC_DTSCS 68              /* DEC Hanyu (DTSCS)                */
/* Synonym definitions for compatibility                                    */
#define CDA_K_ISO_LATIN6 3              /* Obsolete synonym                 */
#define CDA_K_ISO_LATIN7 4              /* Obsolete synonym                 */
#define CDA_K_ISO_LATIN8 6              /* Obsolete synonym                 */
/* Values of the add-info parameter for cda_locate_item and cda_store_item when */
/* the item data type is general floating point.                            */
#define CDA_K_F_FLOAT 0                 /* VAX F-floating                   */
#define CDA_K_D_FLOAT 1                 /* VAX D-floating                   */
#define CDA_K_G_FLOAT 2                 /* VAX G-floating                   */
#define CDA_K_H_FLOAT 3                 /* VAX H-floating                   */
#define CDA_K_IEEE_754_S_FLOAT 4        /* IEEE 754 single precision        */
#define CDA_K_IEEE_754_D_FLOAT 5        /* IEEE 754 double precision        */
#define CDA_K_NATIVE_S_FLOAT 6          /* Native single precision  VAX: F-float non-VAX: IEEE 754 single */
#define CDA_K_NATIVE_D_FLOAT 7          /* Native double precision  VAX: G-float non-VAX: IEEE 754 double */
/* Item codes for cda_status_to_message, cda_write_message.                 */
#define CDA_MESSAGE_SEVERITY 1          /* Message severity                 */
#define CDA_MESSAGE_PREFIX 2            /* Message prefix                   */
#define CDA_MESSAGE_PARAMETER 3         /* Messge parameter                 */
/* Values of the SEVERITY item code for cda_status_to_message and           */
/* cda_write_message routines.                                              */
#define CDA_K_WARNING 0                 /* Warning = 000                    */
#define CDA_K_NORMAL 1                  /* Normal = 001                     */
#define CDA_K_ERROR 2                   /* Error = 010                      */
#define CDA_K_INFORMATIONAL 3           /* Informational = 011              */
#define CDA_K_FATAL 4                   /* Fatal = 100                      */
#endif
