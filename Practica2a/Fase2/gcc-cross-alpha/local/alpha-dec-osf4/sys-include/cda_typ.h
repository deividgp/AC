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
/* @(#)$RCSfile: cda_typ.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 04:28:15 $     */
#ifndef _cdatyp_
#define _cdatyp_
/*
**++
**
**  COPYRIGHT (c) 1991 BY
**  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.
**  ALL RIGHTS RESERVED.
**
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED
**  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER
**  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY
**  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY
**  TRANSFERRED.
**
**  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE
**  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT
**  CORPORATION.
**
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.
**
**  ABSTRACT:
**	This file contains the type definitions for the CDA & DDIS routines.
**
**--
**/

/*
 * The CDA_EXPAND_PROTO flag along with the PROTO macro allow for tailoring
 * routine declarations to expand to function prototypes or not depending
 * on the particular platform (compiler) capabilities.
 * If CDA_EXPAND_PROTO is defined, the PROTO macro will expand to function
 * prototypes.  If OS2 or msdos turn on flag as prototypes must be used
 * on these platforms.  For other platforms it is left to the application
 * to #define CDA_EXPAND_PROTO before #include of this file if function
 * prototyping is desired.
 */
#if defined(OS2) || defined(msdos) || defined(vaxc)
#ifndef CDA_EXPAND_PROTO
#define CDA_EXPAND_PROTO 1
#endif
#endif

/*
 * CDA keyword macros.
 */
#ifndef CDA_MACROS_DEFINED
#define CDA_MACROS_DEFINED
#if defined (OS2) || defined (RATIONAL) || defined (MSWINDOWS)
#define CDA_HUGE huge
#define CDA_FAR  far
#define CDA_APIENTRY far pascal
#define CDA_CALLBACK far pascal _loadds _export
#elif defined(msdos)
#define CDA_HUGE huge
#define CDA_FAR  far
#define CDA_APIENTRY far cdecl
#define CDA_CALLBACK far cdecl
#else
#define CDA_FAR
#define CDA_HUGE
#define CDA_APIENTRY
#define CDA_CALLBACK
#endif
#endif

/*
 * CDA defined types.
 */
#ifndef CDA_TYPES
#define CDA_TYPES
#if defined (vms) || defined(__unix__) || defined(unix)
typedef unsigned long	CDAstatus;	/* Return status code		 */
typedef long		CDAsize;	/* Size, length, or position arg */
typedef unsigned short	CDAitemcode;	/* Itemlist item code		 */
typedef unsigned short	CDAitemlength;	/* Itemlist item length		 */
typedef unsigned char CDA_HUGE * CDAbufaddr; /* Addr. array of unsigned bytes */
typedef void CDA_FAR *	CDAaddress;	/* Generic address argument	 */
typedef int		CDAcardinal;	/* Integer arguments		 */
typedef int		CDAboolean;	/* Boolean value		 */
typedef char 		CDAenvirontext;	/* Environment specific text	 */
					/* character			 */
typedef unsigned char	CDAoctet;	/* Unsigned 8-bit entity	 */
typedef int		CDAaggtype;	/* CDA aggregate type code	 */
typedef long 		CDAconstant;	/* CDA enumerated constant	 */
typedef	int		CDAindex;	/* Array index			 */
typedef void CDA_FAR *	CDAuserparam;   /* User supplied parameter       */
typedef unsigned long	CDAflags;	/* Flags/mask longword		 */
#endif

#if defined(OS2) || defined(msdos)
typedef unsigned long	CDAstatus;	/* Return status code		 */
typedef long		CDAsize;	/* Size, length, or position arg */
typedef unsigned short	CDAitemcode;	/* Itemlist item code		 */
typedef unsigned short	CDAitemlength;	/* Itemlist item length    	 */
typedef unsigned char CDA_HUGE * CDAbufaddr; /* Addr. array of unsigned bytes */
typedef void CDA_FAR *	CDAaddress;	/* Generic address argument	 */
typedef int		CDAcardinal;	/* Integer arguments		 */
typedef char		CDAboolean;	/* Boolean value		 */
typedef char 		CDAenvirontext;	/* Environment specific text	 */
					/* character			 */
typedef unsigned char	CDAoctet;	/* Unsigned 8-bit entity	 */
typedef int		CDAaggtype;	/* CDA aggregate type code	 */
typedef long		CDAconstant;	/* CDA enumerated constant	 */
typedef int		CDAindex;	/* Array index			 */
typedef void CDA_FAR *	CDAuserparam;   /* User supplied parameter       */
typedef unsigned long	CDAflags;	/* Flags/mask longword		 */
#endif

typedef struct cda_itemlist {		/* Itemlist structure		 */
    CDAitemlength item_length;
    CDAitemcode   item_code;		/* Parameter can be value or adrr*/
    union {				/* It is recommended that this   */
	CDAsize	    item_value;		/* itemlist struct be used over  */
	CDAaddress  item_address;	/* the struct cda_itemlist def'd */
	} CDAitemparam;			/* in cda$def.h (cda_def.h).	 */
    } CDAitemlist;

typedef struct cda_aggregate CDA_FAR *CDAagghandle; /* Aggregate handle	     */

typedef struct cda_document CDA_FAR *CDArootagghandle;/* Root aggregate handle */

typedef struct cda_converter CDA_FAR *CDAconverterhandle;   /* Converter handle	     */

typedef struct cda_frontend CDA_FAR *CDAfrontendhandle;	    /* Cvtr front end handle */

typedef struct cda_filehandle CDA_FAR *CDAfilehandle;	    /* CDA file handle	     */

typedef struct cda_text_filehandle CDA_FAR *CDAtextfilehandle; /* Text file handle   */

typedef struct cda_message CDA_FAR *CDAmessagehandle;	    /* CDA message handle    */

/*
 * DDIS defined types.
 */
typedef	struct ddis_context CDA_FAR *DDISstreamhandle;	    /* DDIS stream handle    */

typedef unsigned long	DDIStype;	/* DDIS tag (type) argument	 */
typedef unsigned long	DDISlength;	/* DDIS length argument          */
typedef unsigned long	DDISentry;	/* DDIS parse table entry	 */

#endif				/* for the CDA_TYPES definition */

/*
 * usage: PROTO (return_type function, (arg1, arg2, arg3))
 */
#ifndef PROTO
#if CDA_EXPAND_PROTO == 1
#define PROTO(name, arg_list) name arg_list
#else
#define PROTO(name, arg_list) name ()
#endif
#endif

/* 
 * The symbol CDAbig_endian is defined here for big endian platforms.
 * When compiling applications on big endian platforms not listed below,
 * the symbol CDAbig_endian must be defined on the compile command line.
 */
#if defined(sun)
#define CDAbig_endian
#endif

#endif
