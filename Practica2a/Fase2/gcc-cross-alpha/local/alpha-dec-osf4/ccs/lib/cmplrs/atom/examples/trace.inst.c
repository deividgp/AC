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
#pragma ident "@(#)$RCSfile: trace.inst.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:50:10 $"


#include <stdio.h>
#include <cmplrs/atom.inst.h>

void InstrumentInit(int p1, char **p2) {
   AddCallProto("OpenFile()");
   AddCallProto("InstReference(REGV)");
   AddCallProto("DataReference(VALUE)");
   AddCallProto("CloseFile()");

   AddCallProgram(ProgramBefore,"OpenFile");
   AddCallProgram(ProgramAfter,"CloseFile");
}

Instrument(int argc, char **argv, Obj *obj)
{
   Proc *p; Block *b; Inst *i;

   for (p = GetFirstObjProc(obj); p != NULL; p = GetNextProc(p)) {
     for (b = GetFirstBlock(p); b != NULL; b = GetNextBlock(b)) {
       AddCallBlock(b,BlockBefore,"InstReference",REG_PC);
       for (i = GetFirstInst(b); i != NULL; i = GetNextInst(i)) {
	 if (IsInstType(i,InstTypeLoad) || IsInstType(i,InstTypeStore)) {
	   AddCallInst(i,InstBefore,"DataReference",EffAddrValue);
	 }
       }
     }
   }
}
