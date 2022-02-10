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
#pragma ident "@(#)$RCSfile: ptrace.inst.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:48:40 $"


#include <stdio.h>
#include <cmplrs/atom.inst.h>

static const char *	SafeProcName(Proc *);


Instrument(int argc, char **argv, Obj *obj)
{
   Proc *p;

   AddCallProto("ProcTrace(char *)");
   for (p = GetFirstObjProc(obj); p != NULL; p = GetNextProc(p)) {
     AddCallProc(p,ProcBefore,"ProcTrace",SafeProcName(p));
   }
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
