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
#define _dvr_cdef_

/*
**++
**  COPYRIGHT (c) 1988, 1992 BY
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
** Modified by:
**
**	V01-003		RJD000		Ronan Duke		28-Mar-1994
**		Merged in code from DEC Asia - to handle Asian characters
**
**	V01-002		SJM0000		Stephen Munyan		18-May-1992
**		Merged in code from DEC Japan as a result of their code
**		merge.
**
**	V01-001		ECR0000		Elizabeth C. Rust	30-Mar-1992
**		merge in audio code
**
**--
**/

/**
 ** Character cell viewer constants and structure defs
 **/
/*
 * Selectoptions flags, all are boolean
 */
#define DVR_M_SoftDirectives   (1L<<0)	/* obey soft directives		*/
#define DVR_M_Auto_Wrap	       (1L<<1)	/* do word-wrap formatting of text */
#define DVR_M_Outfile	       (1L<<2)	/* output to file		*/
#define DVR_M_Paging	       (1L<<3)	/* pause at end of page		*/
#define DVR_M_Text	       (1L<<4)	/* output text			*/
#define DVR_M_Images	       (1L<<5)	/* text placeholder for images	*/
#define DVR_M_Graphics	       (1L<<6)	/* text placeholder for graphics*/
#define DVR_M_ReportErrors     (1L<<7)	/* write errors to stderr   */
#define DVR_M_Layout	       (1L<<8)	/* Do layout		    */
#define DVR_M_SpecificLayout   (1L<<9)	/* Do specific layout	    */
#define DVR_M_Text_Backend     (1L<<10)	/* Act like a text backend*/
/* BEGIN AUDIO STUFF */
#ifdef CDA_AUDIO_SUPPORT
#define DVR_M_Audio	       (1L<<11)	/* text placeholder for audio	*/
#endif
/* END AUDIO STUFF */
#ifdef I18N_MULTIBYTE
#define DVR_M_Ascii_Fallback   (1L<<31)	/* Do Ascii Fallback            */
#endif

/* BEGIN AUDIO */
#ifdef CDA_AUDIO_SUPPORT
#define DVR_M_DefaultOptions					    \
      DVR_M_SoftDirectives | DVR_M_Auto_Wrap | DVR_M_Outfile \
    | DVR_M_Text | DVR_M_Images | DVR_M_Graphics | DVR_M_Audio \
    | DVR_M_Layout | DVR_M_SpecificLayout
#else
#define DVR_M_DefaultOptions					    \
      DVR_M_SoftDirectives | DVR_M_Auto_Wrap | DVR_M_Outfile \
    | DVR_M_Text | DVR_M_Images | DVR_M_Graphics	     \
    | DVR_M_Layout | DVR_M_SpecificLayout
#endif
/* Item codes for CDA_CONVERT, CDA_OPEN_CONVERTER, domain$READ_format, and  */
/* domain$WRITE_format.  The DVR_ prefix has been substituted for the CDA_  */
/* prefix.								    */
#define DVR_PROCESSING_OPTION 1        /* Processing option                */
#define DVR_INPUT_FORMAT 2             /* Input document format-name       */
#define DVR_INPUT_FRONT_END_PROCEDURE 3 /* Input document front-end procedure */
#define DVR_INPUT_FILE 4               /* Input file specification         */
#define DVR_INPUT_DEFAULT 5            /* Input default file specification */
#define DVR_INPUT_PROCEDURE 6          /* Input get data procedure         */
#define DVR_INPUT_POSITION_PROCEDURE 7 /* Input get position procedure     */
#define DVR_INPUT_PROCEDURE_PARM 8     /* Input procedure parameter        */
#define DVR_INPUT_ROOT_AGGREGATE 9     /* Input root aggregate             */
#define DVR_OUTPUT_FORMAT 10           /* Output document format-name      */
#define DVR_OUTPUT_BACK_END_PROCEDURE 11 /* Output document back-end procedure */
#define DVR_OUTPUT_FILE 12             /* Output file specification        */
#define DVR_OUTPUT_DEFAULT 13          /* Output default file specification */
#define DVR_OUTPUT_PROCEDURE 14        /* Output procedure                 */
#define DVR_OUTPUT_PROCEDURE_PARM 15   /* Output procedure parameter       */
#define DVR_OUTPUT_PROCEDURE_BUFFER 16 /* Output procedure initial buffer  */
#define DVR_OUTPUT_ROOT_AGGREGATE 17   /* Output root aggregate            */
#define DVR_OPTIONS_FILE 18            /* Options file specification       */

/*
**  This following item codes area unique to the CC viewer.  They are intended
**  for use in the private item list argument to the DvrCCInitialize routine.
*/
#define DVR_FRONT_END_HANDLE 	256	/* front end input procedure handle */
#define DVR_PAGE_HEIGHT	257	/* formatted page height in chars   */
#define DVR_PAGE_WIDTH		258	/* formatted page width in chars    */
#ifdef I18N_MULTIBYTE
#define DVR_TEXT_ENCODING 	259 /* text encoding name               */
#endif
