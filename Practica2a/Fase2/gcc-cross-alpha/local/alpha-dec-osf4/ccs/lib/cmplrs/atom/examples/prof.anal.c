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
#pragma ident "@(#)$RCSfile: prof.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:48:08 $"


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

long instrTotal = 0;
long *instrPerProc = 0;

FILE *file;
void OpenFile(int number)
{
  instrPerProc = (long *) calloc(sizeof(long),number);
  assert(instrPerProc != NULL);
  file = fopen("prof.out","w");
  assert(file != NULL);
  fprintf(file,"%30s %15s %10s\n","Procedure","Instructions","Percentage");
}

void ProcedureCount(int number, int instructions)
{
  instrTotal += instructions;
  instrPerProc[number] += instructions;
}

void ProcedurePrint(int number, char *name)
{
  if (instrPerProc[number] > 0) {
    fprintf(file,"%30s %15ld %9.3f\n", name, instrPerProc[number], 
	    100.0 * instrPerProc[number] / instrTotal);
  }
}

void CloseFile()
{
  fprintf(file,"\n%30s %15ld\n", "Total", instrTotal);
  fclose(file);
}
