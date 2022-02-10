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
 * @(#)$RCSfile: alloc_smt.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1996/12/16 17:24:32 $
 */

#ifndef _SMT_H_
#define _SMT_H_

/* Shared Magentic Tape (SMT) Allocation routine Return Statuses. */

#define SMT_SUCCESS     0      /* Device Allocated/Deallocated */
#define SMT_FAILED      1      /* Requeset unsuccessful, not Allocated */

/* Vector index definitions into jump table */

#define SMT_ALLOCATE 0         /* the allocate vector into the jump table */
#define SMT_DEALLOCATE 1       /* the deallocate vector into the jump table */

typedef struct smt_metadata {
  int flags;         /* global flags variable */
  int ref;           /* reference count variable */
  void (**table)()   /* handle to the jump table */
} SMT_DATA;

/* defines used in the smt_metadata flags member */

#define SMT_EXCLUSIVE 0x1      /* state flags */
#define SMT_LOADING   0x2 

/* Global declarations */

extern int alloc_smt(dev_t devunit);
extern void dealloc_smt(dev_t devunit);

#endif






