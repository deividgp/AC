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
#pragma ident "@(#)$RCSfile: dyninst.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:42:43 $"


/*
	dyninst: fundamental dynamic counts (instructions, loads,
	stores, blocks, procedures).
 */

#include <stdio.h>
#include <assert.h>

long insts = 0;
long blocks = 0;
long procs = 0;
long loads = 0;
long stores = 0;

void AddProcedure()
{
   procs++;
}

void AddBlock(int instsBlock, int loadsBlock, int storesBlock)
{
  insts += instsBlock;
  loads += loadsBlock;
  stores += storesBlock;
  blocks++;
}

void PrintCounts()
{
  FILE *file;
  file = fopen("dyninst.out","w");
  assert(file != NULL);
  fprintf(file,"Instructions %ld\n",insts);
  fprintf(file,"Loads %ld\n",loads);
  fprintf(file,"Stores %ld\n",stores);
  fprintf(file,"Blocks %ld\n",blocks);
  fprintf(file,"Procedures: %ld\n",procs);
  fclose(file);
}


