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
#pragma ident "@(#)$RCSfile: branch.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:41:39 $"


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define TABLESIZE 256
int branchHistory[TABLESIZE];

struct BranchType {
  long pc;
  long predicts;
  long references;
} *branches;

int branchct;
FILE *file;

void OpenFile(int number)
{
  branchct = number;
  branches = (struct BranchType *) calloc(sizeof(struct BranchType),number);
  file = fopen("branch.out","w");
  assert(file != NULL);
}

int takenTable[] =    { 1, 2, 3, 3 };
int notTakenTable[] = { 0, 0, 1, 2 };

void CondBranch(int number, long pc, long taken)
{
  long index, history;

  index = (pc >> 2) & (TABLESIZE-1);
  history = branchHistory[index];
  if (taken) {
    if (history >= 2) branches[number].predicts++;
    branchHistory[index] = takenTable[history];
  } else {
    if (history <= 1) branches[number].predicts++;
    branchHistory[index] = notTakenTable[history];
  }
  branches[number].references++;
  branches[number].pc = pc;
}

void PrintResults(void)
{
  long references;
  long predicts;
  int i;

  fprintf(file,"%18s %20s %20s\n","PC","References","Predicted");
  references = 0;
  predicts = 0;
  for (i = 0; i < branchct; i++) {
    if (branches[i].references > 0) {
      references += branches[i].references;
      predicts += branches[i].predicts;
      fprintf(file,"0x%016lx %20ld %20f\n",
	      branches[i].pc, branches[i].references,
	      (float) branches[i].predicts / branches[i].references);
    }
  }
  fprintf(file,"%18s %20ld %20f\n","Totals", references,
                  (float) predicts / references);
  fclose(file);
}
