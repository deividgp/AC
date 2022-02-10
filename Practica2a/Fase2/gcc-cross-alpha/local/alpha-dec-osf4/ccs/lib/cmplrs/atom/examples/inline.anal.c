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
#pragma ident "@(#)$RCSfile: inline.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:46:32 $"


/*
	inline: identify potential candidates for inlining
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

long *counts;
FILE *file;

void OpenFile(int number)
{
  counts = (long *) calloc(sizeof(long),number);
  file = fopen("inline.out","w");
  assert(file != NULL);
  fprintf(file,"%12s %25s %25s %12s\n", "PC", "Parent", "Called", "Number");
}

void CallSiteCount(int index)
{
  counts[index]++;
}
  
void CallSitePrint(int index, long pc, char *nameCalled, char *nameParent)
{
  if (counts[index] > 0) {
    fprintf(file,"0x%010lx %25s %25s %14ld\n",
	    pc, nameParent, nameCalled, counts[index]);
  }
}

void CloseFile()
{
  fclose(file);
}


