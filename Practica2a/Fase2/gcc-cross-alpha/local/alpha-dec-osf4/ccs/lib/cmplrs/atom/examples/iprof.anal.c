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
#pragma ident "@(#)$RCSfile: iprof.anal.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:46:54 $"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

long instrTotal = 0;
long *instrPerProc;
long *callsPerProc;

FILE *OpenUnique(char *fileName, char *type)
{
  FILE *file;
  char Name[200];

  if (getenv("ATOMUNIQUE") != NULL)
    sprintf(Name,"%s.%d",fileName,getpid());
  else
    strcpy(Name,fileName);

  file = fopen(Name,type);
  if (file == NULL)
    {
      fprintf(stderr,"Atom: can't open %s for %s\n",Name, type);
      exit(1);
    }
  return(file);
}

static FILE *file;
void OpenFile(int number)
{
  file = OpenUnique("iprof.out","w");
  fprintf(file,"%30s %15s %15s %12s\n","Procedure","Calls",
	  "Instructions","Percentage");
  instrPerProc = (long *) calloc(sizeof(long), number);
  callsPerProc = (long *) calloc(sizeof(long), number);
  if (instrPerProc == NULL || callsPerProc == NULL) {
    fprintf(stderr,"Malloc failed\n");
    exit(1);
  }
}

void ProcedureCalls(int number)
{
  callsPerProc[number]++;
}
  
void ProcedureCount(int number, int instructions)
{
  instrTotal += instructions;
  instrPerProc[number] += instructions;
}
  

void ProcedurePrint(int number, char *name)
{
  if (instrPerProc[number] > 0) {
    fprintf(file,"%30s %15ld %15ld %12.3f\n",
	    name, callsPerProc[number], instrPerProc[number], 
	    100.0 * instrPerProc[number] / instrTotal);
  }
}

void CloseFile()
{
  fprintf(file,"\n%30s %15s %15ld\n", "Total", "", instrTotal);
  fclose(file);
}


