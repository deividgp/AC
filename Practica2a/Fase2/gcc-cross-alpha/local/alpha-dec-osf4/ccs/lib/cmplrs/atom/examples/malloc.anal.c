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
#pragma ident "@(#)$RCSfile: malloc.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:47:19 $"

/*
**  malloc.anal.c -	Analysis routines for malloc recording tool.
**
**	This tool records each call to the routine malloc() and prints a
**	summary of the application's allocated memory.  See "malloc.inst.c"
**	for a description of how to use this tool.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>


/*
 * We record a histogram of allocation request.  Requests for less than
 * this amount are included in the histogram.  Requests for more than this
 * amount are reported outside of the histogram.
 */
#define MAXSIZE 	16384

/*
 * Allocate an array of structures to record information about various
 * sized allocations.  Allocate an additional structure to hold
 * information about large allocations.
 */
struct {
    long 	calls;
    long 	memoryAllocated;
} mallocHistory[MAXSIZE], mallocOther;


/*
 * Malloc() may call itself recursively.  This keeps track of recursive
 * calls, so we only record allocations made directly by the application.
 */
int 	depth = 0;


/*
 * These keep track of the initial, current, and maximum 'break' value
 * for the application.  The 'break' value is the last address of the
 * application's heap area.  We use these to determine the amount of
 * heap memory actually used by the application.
 */
long 	StartBrk;
long 	CurBrk;
long 	MaxBrk;


/*
 * The handle for the output file.
 */
FILE *	file;



/*
**  Record a call to malloc().
*/
void BeforeMalloc(long size)
{
   /*
    * Ignore recursive calls.
    */
   if (depth++ != 0)
	return;

   /*
    * Record the allocation request.
    */
   if (size < MAXSIZE) {
	mallocHistory[size].calls++;
	mallocHistory[size].memoryAllocated += size;
   } else {
	mallocOther.calls++;
	mallocOther.memoryAllocated += size;
   }
}


/*
**  Note that we have returned from a malloc() call, so we can keep track
**  of recursive calls.
*/
void AfterMalloc()
{
    depth--;
}


/*
**  Record a call to brk().  This call changes the application's
**  'break' value.
*/
void BeforeBrk(long newbrk)
{
    CurBrk = newbrk;
    if (CurBrk > MaxBrk)
	MaxBrk = CurBrk;
}


/*
**  Record a call to sbrk().  This call increases the application's
**  'break' value.
*/
void BeforeSbrk(long size)
{
    CurBrk += size;
    if (CurBrk > MaxBrk)
	MaxBrk = CurBrk;
}


/*
**  Create the output file and set the initial address for the
**  application's 'break' value.
*/
void Initialize(long startbrk)
{
    file = fopen("malloc.out", "w");
    if (file == NULL) {
	fprintf(stderr, "malloc: Unable to create file 'malloc.out'.\n");
	exit(1);
    }

    StartBrk = startbrk;
    MaxBrk = startbrk;
    CurBrk = startbrk;
}


/*
**  Print the summary information about this application's malloc() calls.
*/
void PrintResults()
{
    long 	calls;
    long	allocated;
    int 	i;


    fprintf(file, "%8s %15s %20s\n", "Size", "calls", "allocated");

    calls = 0;
    allocated = 0;
    for (i = 0; i < MAXSIZE; i++) {
	if (mallocHistory[i].calls > 0) {
	    fprintf(file, "%8ld %15ld %20ld\n", i,
		mallocHistory[i].calls, mallocHistory[i].memoryAllocated);
	    calls += mallocHistory[i].calls;
	    allocated += mallocHistory[i].memoryAllocated;
	}
    }

    if (mallocOther.calls > 0) {
	fprintf(file, ">=%7ld %15ld %20ld\n", MAXSIZE,
	    mallocOther.calls, mallocOther.memoryAllocated);
	calls += mallocOther.calls;
	allocated += mallocOther.memoryAllocated;
    }

    fprintf(file, "\n%8s %15ld %20ld\n", "Totals", calls, allocated);
    fprintf(file, "\nMaximum Memory Allocated: %ld bytes\n", MaxBrk - StartBrk);
    fclose(file);
}
