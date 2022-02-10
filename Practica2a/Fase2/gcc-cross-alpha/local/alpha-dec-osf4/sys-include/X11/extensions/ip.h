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
/***********************************************************
Copyright 1989 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/* $Header: /usr/sde/osf1/rcs/x11/src/xc/lib/DEC/ip.h,v 1.1.2.3 1995/05/16 19:35:28 Dave_Hill Exp $
 *  ip.h:
 *	Shared-Memory IPC package definitions
 */

#ifndef _IP_H_
#define _IP_H_

#define IP_VERSION	(1<<16 + 0)

/* definitions which ought to be part of the language */
#define TRUE 1
#define FALSE 0
#ifndef NULL
#define NULL 0L
#endif
#ifndef _Max
#define _Max(a, b) ( (b) > (a) ? (b) : (a) )
#endif

/* channel type definitions */
#define IP_FULLDUP 0
#define IP_HALFDUP 1

/* channel mode definitions */
#define IP_EITHER 0
#define IP_SENDER 1
#define IP_RECEIVER 2
#define IP_BOTH 3

#define IP_CREATOR 0
#define IP_ATTACHER 1

#define IP_ALIVE	1
#define IP_DEAD		0

/* status codes */
#define IP_SUCCESS	1
#define IP_BADCHAN	-1	/* invalid channel */
#define IP_BADTYPE	-2	/* wrong type of channel */
#define IP_BADMODE	-3	/* specified mode not permitted here */
#define IP_SHUTDOWN	-4	/* one or both ends of channel shut down */
#define IP_SHMERR	-5	/* shared-memory setup error */
#define IP_BADSIZE	-6	/* ridiculous buffer size */
#define IP_RETRY	-7	/* returned by callbacks */
#define IP_ABORT	-8	/* returned by callbacks */
#define IP_NOPRIVATE    -9	/* zero private area */

#define THEM(me) ((me) ^ 1)

#define WAIT(i, p) ipWait(i, p)

#define CHANNEL_OK(chan) ( ((chan)->base          != NULL) && \
			   ((chan)->base->cStatus == IP_ALIVE) && \
			   ((chan)->base->aStatus == IP_ALIVE) )

typedef unsigned int IPData, *IPDataPtr;
typedef unsigned int IPCard;
typedef unsigned char IPCard8;

typedef struct _PrivDesc {
    int size;
    int offset;
} PrivDesc, *PrivDescPtr;

typedef struct _BufDesc {
    int size;				/* how big is the buffer */
    int offset;				/* its offset from start of shmem */
    IPCard version;			/* version: major,minor */
    IPCard8 turn;			/* critical section variable */
    IPCard8 usingBuf[2];		/* critical section variables */
    IPCard8 unused;			/* dummy */
    int  nextRead;			/* 1st not read by receiver */
    int lastWritten;			/* 1st not written by sender */
    int lastRead;			/* last not written by sender */
    int lastReserved;			/* by sender */
    int highWater;			/* last+1 written before wraparound */
} BufDesc, *BufDescPtr;

typedef struct _MemHdr {
    int cStatus;			/* creator status */
    int aStatus;			/* attacher status */
    BufDesc bd0;
    BufDesc bd1;
    PrivDesc privd;
} MemHdr, *MemHdrPtr;


struct _Channel;
typedef int (*IPcallbackProc)(struct _Channel *, int, char *);

typedef struct _Channel {
    int whoami;
    int size;
    int type;
    int mode;				/* of creator */
    int smid;				/* shared memory segment id */
    MemHdrPtr base;			/* addr of shm segment */
    IPDataPtr pbuf0;			/* address of buffer 0 */
    IPDataPtr pbuf1;			/* address of buffer 1 */
    IPDataPtr privateData;		/* address of private area */
    BufDescPtr sendBd;			/* relative to owner of this struct */
    BufDescPtr receiveBd;		/* relative to owner of this struct */
    IPDataPtr sendBuf;			/* relative to owner of this struct */
    IPDataPtr receiveBuf;		/* relative to owner of this struct */
    IPcallbackProc allocFail;		/* allocation failure callback */
    char * allocFailParam;
    IPcallbackProc receiveFail;		/* receive data failure callback */
    char * receiveFailParam;
} Channel, *ChannelPtr;

/* ip.c */
extern int ipCreateChannel(ChannelPtr, int, int, IPCard, IPCard, IPCard);
extern int ipAttachChannel(ChannelPtr);
extern int ipAllocateData(ChannelPtr, IPCard, IPDataPtr *);
extern int ipUnallocateData(ChannelPtr, IPCard);
extern int ipSpaceAvailable(ChannelPtr);
extern int ipSendData(ChannelPtr);
extern int ipSendAndAllocateData(ChannelPtr, IPCard, IPDataPtr *);
extern int ipReceiveData(ChannelPtr, IPCard *, IPDataPtr *);
extern int ipReceiveAtLeastData(ChannelPtr, IPCard, IPCard *, IPDataPtr *);
extern int ipFreeData(ChannelPtr, IPCard);
extern int ipNoOp(int);
extern int ipUnallocateAndSendData(ChannelPtr, IPCard);
extern int ipReceiveDataAvail(ChannelPtr, IPCard *, IPDataPtr *, IPCard *);
extern int ipAdvanceRdPtr(ChannelPtr, IPCard);
extern int ipBulkFreeData(ChannelPtr, IPCard);
extern int ipSetAllocCallback(ChannelPtr, IPcallbackProc, char*);
extern int ipSetReceiveCallback(ChannelPtr, IPcallbackProc, char*);
extern int ipDestroyChannel(ChannelPtr);
extern int ipSendBufferSize(ChannelPtr);
extern int ipReceiveBufferSize(ChannelPtr);
extern int ipPrivateBuffer(ChannelPtr, int *, IPDataPtr *);

/* iputil.c */
extern int ipWait(IPCard, IPCard);

/* ipcs.c */
extern int ipEnterSection(ChannelPtr, BufDescPtr);
extern int ipLeaveSection(ChannelPtr, BufDescPtr);


#endif /* _IP_H_ */
