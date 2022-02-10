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
#pragma ident "@(#)$RCSfile: dtb.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:42:15 $"


/*
	dtb: Determine the number of dtb misses if the application uses
	8Kb pages and a fully associative translation buffer.
 */

#include <stdio.h>
#include <assert.h>

#define NEXTDTB(index)  (((index)+1) & (DTBSIZE-1))
#define PAGESIZE 8192
#define PAGESHIFT 13
/* must be power of 2 */
#define DTBSIZE 32

long dtb[DTBSIZE];

int nextMapping = 0;
long hits,misses;

#define MAPSIZE 8192
int pageMap[MAPSIZE];

void Reference(long address)
{
  long page = address >> PAGESHIFT;
  int i = pageMap[page & (MAPSIZE-1)];

  if (dtb[i] != page) {
    for (i = 0; i < DTBSIZE; i++) {
      if (dtb[i] == page) {
	pageMap[page & (MAPSIZE - 1)] = i;
	break;
      }
    }
  }
  if (i >= DTBSIZE) {
    misses++;
    dtb[nextMapping] = page;
    pageMap[page & (MAPSIZE-1)] = nextMapping;
    nextMapping = NEXTDTB(nextMapping);
  } else {
    hits++;
    if (nextMapping == i) {
      nextMapping = NEXTDTB(i);
    }
  }
}

void PrintResults()
{
  FILE *file;
  file = fopen("dtb.out","w");
  assert(file != NULL);
  fprintf(file,"DTB hits:       %12ld\n",hits);
  fprintf(file,"DTB Misses:     %12ld\n",misses);
  fprintf(file,"DTB references: %12ld\n",hits+misses);
  fprintf(file,"Miss Rate:      %12.4lf\n",(double) misses/(hits+misses));
  fclose(file);
}


