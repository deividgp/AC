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
/* @(#)$RCSfile: dvr_cc_def.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 04:42:21 $     */
#define _dvr$cdef_

/*
**++
**  COPYRIGHT (c) 1988, 1991 BY
**  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASSACHUSETTS.
**  ALL RIGHTS RESERVED.
**
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND COPIED
**  ONLY  IN  ACCORDANCE  OF  THE  TERMS  OF  SUCH  LICENSE  AND WITH THE
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE. THIS SOFTWARE OR  ANY  OTHER
**  COPIES THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY
**  OTHER PERSON.  NO TITLE TO AND  OWNERSHIP OF THE  SOFTWARE IS  HEREBY
**  TRANSFERRED.
**
**  THE INFORMATION IN THIS SOFTWARE IS  SUBJECT TO CHANGE WITHOUT NOTICE
**  AND  SHOULD  NOT  BE  CONSTRUED  AS A COMMITMENT BY DIGITAL EQUIPMENT
**  CORPORATION.
**
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE  OR  RELIABILITY OF ITS
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.
**
**  ABSTRACT:
**  	this file will include all the public
**  	entry points for appications calling the
**  	CDA character cell viewer.
**
**--
**/

/**
 ** Character cell viewer constants and structure defs
 **/
/*
 * Selectoptions flags, all are boolean
 */
#define DVR$M_SoftDirectives   (1L<<0)	/* obey soft directives		*/
#define DVR$M_Auto_Wrap	       (1L<<1)	/* do word-wrap formatting of text */
#define DVR$M_Outfile	       (1L<<2)	/* output to file		*/
#define DVR$M_Paging	       (1L<<3)	/* pause at end of page		*/
#define DVR$M_Text	       (1L<<4)	/* output text			*/
#define DVR$M_Images	       (1L<<5)	/* text placeholder for images	*/
#define DVR$M_Graphics	       (1L<<6)	/* text placeholder for graphics*/
#define DVR$M_ReportErrors     (1L<<7)	/* write errors to stderr   */
#define DVR$M_Layout	       (1L<<8)	/* Do layout		    */
#define DVR$M_SpecificLayout   (1L<<9)	/* Do specific layout	    */
#define DVR$M_Text_Backend     (1L<<10)	/* Act like a text backend*/
#define DVR$M_DefaultOptions					    \
      DVR$M_SoftDirectives | DVR$M_Auto_Wrap | DVR$M_Outfile \
    | DVR$M_Text | DVR$M_Images | DVR$M_Graphics	       \
    | DVR$M_Layout | DVR$M_SpecificLayout

/* Item codes for CDA$CONVERT, CDA$OPEN_CONVERTER, domain$READ_format, and  */
/* domain$WRITE_format.  The DVR$ prefix has been substituted for the CDA$  */
/* prefix.								    */
#define DVR$_PROCESSING_OPTION 1        /* Processing option                */
#define DVR$_INPUT_FORMAT 2             /* Input document format-name       */
#define DVR$_INPUT_FRONT_END_PROCEDURE 3 /* Input document front-end procedure */
#define DVR$_INPUT_FILE 4               /* Input file specification         */
#define DVR$_INPUT_DEFAULT 5            /* Input default file specification */
#define DVR$_INPUT_PROCEDURE 6          /* Input get data procedure         */
#define DVR$_INPUT_POSITION_PROCEDURE 7 /* Input get position procedure     */
#define DVR$_INPUT_PROCEDURE_PARM 8     /* Input procedure parameter        */
#define DVR$_INPUT_ROOT_AGGREGATE 9     /* Input root aggregate             */
#define DVR$_OUTPUT_FORMAT 10           /* Output document format-name      */
#define DVR$_OUTPUT_BACK_END_PROCEDURE 11 /* Output document back-end procedure */
#define DVR$_OUTPUT_FILE 12             /* Output file specification        */
#define DVR$_OUTPUT_DEFAULT 13          /* Output default file specification */
#define DVR$_OUTPUT_PROCEDURE 14        /* Output procedure                 */
#define DVR$_OUTPUT_PROCEDURE_PARM 15   /* Output procedure parameter       */
#define DVR$_OUTPUT_PROCEDURE_BUFFER 16 /* Output procedure initial buffer  */
#define DVR$_OUTPUT_ROOT_AGGREGATE 17   /* Output root aggregate            */
#define DVR$_OPTIONS_FILE 18            /* Options file specification       */

/*
**  This following item codes area unique to the CC viewer.  They are intended
**  for use in the private item list argument to the DvrCCInitialize routine.
*/
#define DVR$_FRONT_END_HANDLE 	256	/* front end input procedure handle */
#define DVR$_PAGE_HEIGHT	257	/* formatted page height in chars   */
#define DVR$_PAGE_WIDTH		258	/* formatted page width in chars    */
