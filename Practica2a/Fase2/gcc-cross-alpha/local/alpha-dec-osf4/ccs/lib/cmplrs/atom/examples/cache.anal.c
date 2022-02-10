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
#pragma ident "@(#)$RCSfile: cache.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:41:58 $"


/*
	Cache: determine cache miss rate if application runs in 8K
	direct-mapped cache.
 */

#include <stdio.h>
#include <assert.h>

#define CACHE_SIZE 8192
#define BLOCK_SHIFT 5

long tags[CACHE_SIZE >> BLOCK_SHIFT];
long references, misses;

void Reference(long address)
{
  int index = (address & (CACHE_SIZE-1)) >> BLOCK_SHIFT;
  long tag = address >> BLOCK_SHIFT;

  if (tags[index] != tag) {
      misses++;
      tags[index] = tag;
    }
  references++;
}

void PrintResults()
{
  FILE *file;
  file = fopen("cache.out","w");
  assert(file != NULL);
  fprintf(file,"References: %ld\n",references);
  fprintf(file,"Misses:     %ld\n",misses);
  fprintf(file,"Miss Rate:  %lf\n",(double) misses / references);
  fclose(file);
}


