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
#pragma ident "@(#)$RCSfile: inline.inst.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:46:43 $"


#include <stdio.h>
#include <cmplrs/atom.inst.h>

static int numberCallSites=0;

static const char *	SafeProcName(Proc *);


void InstrumentInit(int argc, char **argv)
{
   AddCallProto("OpenFile(int)");
   AddCallProto("CallSiteCount(int)");
   AddCallProto("CallSitePrint(int,long,char *,char *)");
   AddCallProto("CloseFile()");
   AddCallProgram(ProgramAfter,"CloseFile");
}

Instrument(int argc, char **argv, Obj *obj)
{
   Proc *p; Block *b; Inst *i;
   ProcRes target;
   int opcode,function;

   for (p = GetFirstObjProc(obj); p != NULL; p = GetNextProc(p)) {
     for (b = GetFirstBlock(p); b != NULL; b = GetNextBlock(b)) {
       for (i = GetFirstInst(b); i != NULL; i = GetNextInst(i)) {
	 /* JSR and BSR */
	 opcode = GetInstInfo(i,InstOpcode);
	 function = (GetInstInfo(i,InstMemDisp) >> 14) & 0x3;
	 if ((opcode == 0x1A && function == 1 ) || opcode == 0x34) {
	   ResolveTargetProc(i, &target);
	   if (target.name != NULL) {
	     AddCallInst(i,InstBefore,"CallSiteCount", numberCallSites);
	     AddCallObj(obj, ObjAfter,"CallSitePrint",
			numberCallSites, InstPC(i), target.name,
			SafeProcName(p));
	     numberCallSites++;
	   }
	 }
       }
     }
   }
}

void InstrumentFini(void)
{
   AddCallProgram(ProgramBefore,"OpenFile",numberCallSites);
}


static const char *SafeProcName(Proc *p)
{
    const char *	name;
    static char 	buf[128];

    name = ProcName(p);
    if (name)
	return(name);
    sprintf(buf, "proc_at_0x%lx", ProcPC(p));
    return(buf);
}
