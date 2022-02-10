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
 *	@(#)$RCSfile: msgbuf.h,v $ $Revision: 4.3.12.2 $ (DEC) $Date: 1997/06/20 16:11:04 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */


 /*
  * Change History
  *
  * 27-Jun-91   Scott Cranston
  *     Changed optional compilation of binary error support strategy.
  *        - changed instances of '#ifdef _UERF' to'#if UERF'
  *
  * 5-Jun-91	Scott Cranston
  *      Increased size of msgbuf to 24Kb for binary error logging
  */

#ifndef	_SYS_MSGBUF_H_
#define _SYS_MSGBUF_H_

#define MSG_MAGIC	0x063061
#define NEW_MSG_MAGIC	0x880524

#define DEFAULT_MSGBUF_SIZE  4096
#define MAX_MSGBUF_SIZE      (1024 * 1024)

struct	msgbuf_hdr {
	long	msg_magic;     /* magic number */
	long	msg_bufx;      /* write offset */
	long	msg_bufr;      /* read offset */
	long	msg_size;      /* buffer size or actual message size */
};

#define MSGBUF_HDRSIZ      (sizeof (struct  msgbuf_hdr))   

/*
 * Note that MSG_BSIZE is a constant equal to the deafult message buffer 
 * size less the MSGBUF_HDRSIZ. The actual message buffer size is
 * tuneable and can be changed by the user. So the constant
 * MSG_BSIZE should be used with extreme care. The correct actual
 * message buffer size to use is the msg_size in "struct msgbuf_hdr".
 */
#define MSG_BSIZE          (DEFAULT_MSGBUF_SIZE-MSGBUF_HDRSIZ)

struct	msgbuf {
	struct  msgbuf_hdr  hdr;
	char	msg_bufc[MSG_BSIZE];
};

#endif	/* _SYS_MSGBUF_H_ */
