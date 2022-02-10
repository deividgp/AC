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
 *	@(#)$RCSfile: malloc.h,v $ $Revision: 4.2.8.2 $ (DEC) $Date: 1998/03/30 18:05:05 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: malloc.h
 *                                                                    
 * ORIGIN: IBM
 *
 * Copyright International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */                                                                   

#ifndef _MALLOC_H_
#define _MALLOC_H_
/*
	Constants defining mallopt operations
*/

#define M_MXFAST	1	/* set size of blocks to be fast */
#define M_NLBLKS	2	/* set number of block in a holding block */
#define M_GRAIN		3	/* set number of sizes mapped to one, for
				   small blocks */
#define M_KEEP		4	/* retain contents of block after a free until
				   another allocation */
/*
	structure filled by 
*/
struct mallinfo  {
	int arena;	/* total space in arena */
	int ordblks;	/* number of ordinary blocks */
	int smblks;	/* number of small blocks */
	int hblks;	/* number of holding blocks */
	int hblkhd;	/* space in holding block headers */
	int usmblks;	/* space in small blocks in use */
	int fsmblks;	/* space in free small blocks */
	int uordblks;	/* space in ordinary blocks in use */
	int fordblks;	/* space in free ordinary blocks */
	int keepcost;	/* cost of enabling keep option */
};	

/*
 * Definitions for acreate().
 */
#define MEM_NOAUTOGROW 0X1
#define MEM_SHARED     0X4

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long  size_t;
#endif

#ifdef   _NO_PROTO
extern int mallopt();
extern struct mallinfo mallinfo();
extern size_t mallocblksize();
extern void *acreate();
extern int   adelete();
extern void *amalloc();
extern void  afree();
extern void *arealloc();
extern void *acalloc();
extern int  amallopt();
extern size_t amallocblksize();
extern struct mallinfo amallinfo();

#else  /*_NO_PROTO */

#ifdef __cplusplus
extern "C" {
#endif
extern int mallopt(int, int);
extern struct mallinfo mallinfo(void);
extern size_t mallocblksize (void*);
extern void *acreate(void *, size_t, int, void *, void *(*)(size_t, void *));
extern int   adelete(void *);
extern void *amalloc(size_t, void *);
extern void  afree(void *, void *);
extern void *arealloc(void *, size_t, void *);
extern void *acalloc(size_t, size_t, void *);
extern int  amallopt(int, int, void *);
extern size_t amallocblksize (void *, void *);
extern struct mallinfo amallinfo(void *);
#ifdef __cplusplus
}
#endif
#endif /*_NO_PROTO */

#endif /* _MALLOC_H_ */
