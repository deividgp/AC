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
 *	@(#)$RCSfile: capsar.h,v $ $Revision: 4.2.4.4 $ (DEC) $Date: 1994/05/12 18:03:38 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */
/************************************************************/
/*                                                          */
/*   Definitions file for capsar utilities and libraries    */
/*                                                          */
/************************************************************/

#ifndef _CAPSAR_H_
#define _CAPSAR_H_

#include <stdio.h>

#define NOTOK		(-1)		/* syscalls return this on error */
#define	OK		(0)		/* returned on success */
#define	DONE		(1)		/* job done */
#define	NULLCP		((char *)0)
#define NULLVP		((char **)0)
#define EOM		(-1)		/* emd of message */
#define EBFOUND		(0)		/* encapsaulation found */
#define EBSEP		(2)		/* separator found */
#define EBDASH		(3)		/* encapsulation boundery */
#define	ANYTEXT		(4)		/* any text */
#define DOT		(5)		/* dot character found */
#define HEADER		(6)		/* mail header line flag */
#define EOA		(7)		/* separator line */
#define CONT_POSS	(8)		/*header continuation line */
#define EBSMTP		(9)		/* separation line for SMTP */

#define NOTSMTP		(0)
#define SMTPLF		(1)
#define SMTPCRLF	(2)

#define TEXT		(0)
#define CDA		(1)

#define	TIDE_MARK_RATIO 0.0001		/* hide tide mark for memory 
					   allocation */
#define NO_LOGGING	(0)
#define STDERR_LOGGING  (1)
#define SYSLOG_LOGGING  (2)


/* mail message types */

#define	EMPTY		0		/* the message is empty */
#define	SIMPLE_MESSAGE	1		/* message has exactly 1 body part */
#define	COMPOUND_MESSAGE 2		/* two or more body parts */
#define MAIL_MESSAGE	3		/* content header + 1+ body part */
#define	MULTIPLE_FORMAT	4		/* 2+ representations of
					   same document eg ddif */

/* default settings */

#define ENABLE		1		/* if non zero conversion of
					   bodyparts is enabled */

#define	DEF_SEP 	"\n"
#define SMTP_SEP 	"\r\n"

/* internal representation of a mail message */

#define MM	struct mm
struct mm {
	char	*name;		/* name tag for message */
	char	*start;		/* string tag for message */
	char	*stop;		/* stop string tag */
	char	*body_type;	/* body type */
	int	complete;	/* completed string */
	int 	enable;		/* conversion enable */
	int	size;		/* size of message in bytes */
	int	message_type;	/* mail message type */
	char	*separator;	/* line separator for message */
	char	*dataptr;	/* pointer to message */
	char	*swapfile;	/* pointer to file on disk */
	int	fd;		/* file descriptor to file on disk */
	int	flat_fd;	/* file descriptor to flat mail file */
	int	offset;		/* offset in bytes from start of file */
	struct mm *mm_next;	/* link list of mail structures */
	struct mm *parent;	/* parent mail message */
};

#define COMPRESS_CMD 	"/usr/ucb/compress"
#define UUENCODE_CMD 	"/usr/bin/uuencode"
#define UNCOMPRESS_CMD 	"/usr/ucb/uncompress"
#define UUDECODE_CMD 	"/usr/bin/mhdecode"
#define CTOD 		"/usr/bin/ctod"
#define CAT 		"/bin/cat"

#define	BODY_TYPE_DEF 	"text"
#define DDIFTAG 	"DDIF"
#define DOTSTAG 	"DOTS"
#define DDIF_MAGICNO 	020037777777
#define DOTS_MAGICNO 	020037177777

/* useful functions used */
_BEGIN_CPLUSPLUS
void	error __((char *, char *));
char	*getcpy __((char *));

/* capsar routines */
MM	*capsar_new __((void));
MM	*capsar_create __((char *, char *));
MM	*capsar_parse_file __((int, int));
int	capsar_unparse_file __((MM *, int));
int	capsar_message_type __((MM *));
int	capsar_set_name __((MM *, char *));
char	*capsar_get_name __((MM *));
char	*capsar_get_body_type __((MM *));
MM	**capsar_get_messages __((MM *));
int	capsar_append_header __((MM *, char *));
int	capsar_delete_header __((MM *, char *));
char	**capsar_get_header_list __((MM *));
char	*capsar_get_header __((MM *, char *));
int	capsar_append_message __((MM *, MM *));
int	capsar_delete_message __((MM *, MM *));
MM	*capsar_new_parse __((FILE *, int));
int	capsar_quick __((FILE *));

_END_CPLUSPLUS
#endif /* _CAPSAR_H_ */
