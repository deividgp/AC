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
#pragma ident "@(#)$RCSfile: malloc.inst.c,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/04/27 19:47:30 $"

/*
**  malloc.inst.c -	Instrumentation routines for malloc recording tool.
**
**	This tool records each call to the routine malloc() and prints a
**	summary of the application's allocated memory.
*/

#include <stdio.h>
#include <cmplrs/atom.inst.h>


/*
**  Perform once-per-application initializations.
*/
void InstrumentInit(int iargc, char **iargv)
{
    unsigned long	BrkStart;
    Obj *        	ObjMain;


    /*
     * Define prototypes for the analysis routines.
     */
    AddCallProto("Initialize(long)");
    AddCallProto("BeforeMalloc(REGV)");
    AddCallProto("AfterMalloc()");
    AddCallProto("BeforeBrk(REGV)");
    AddCallProto("BeforeSbrk(REGV)");
    AddCallProto("PrintResults()");

    /*
     * Calculate the start of this application's heap and pass it to the
     * initialization routine in the analysis code.  The application's
     * heap starts immediately after the main object's uninitialized
     * data area.
     */
    ObjMain = GetFirstObj();
    BrkStart = GetObjInfo(ObjMain, ObjUninitDataStartAddress) +
	GetObjInfo(ObjMain, ObjUninitDataSize);
    AddCallProgram(ProgramBefore, "Initialize", BrkStart);

    /*
     * Print out the results when the application finishes.
     */
    AddCallProgram(ProgramAfter, "PrintResults");
}


/*
 * Instrument each object in this application.
 */
Instrument(int iargc, char **iargv, Obj *obj)
{
    ProcRes	pres;


    /*
     * If this object defines malloc(), add an instrumentation point
     * to trace it.
     */
    ResolveNamedProc("malloc", &pres);
    if (pres.proc != NULL) {
	AddCallProc(pres.proc, ProcBefore, "BeforeMalloc", REG_ARG_1);
	AddCallProc(pres.proc, ProcAfter, "AfterMalloc");
    }

    /*
     * If this object defines brk(), add an instrumentation point.
     * This allows us to keep track of the end of the application's heap.
     */
    ResolveNamedProc("__brk", &pres);
    if (pres.proc != NULL) {
	AddCallProc(pres.proc, ProcBefore, "BeforeBrk", REG_ARG_1);
    }

    /*
     * If this object defines sbrk(), add an instrumentation point.
     * This allows us to keep track of the end of the application's heap.
     */
    ResolveNamedProc("__sbrk", &pres);
    if (pres.proc != NULL) {
	AddCallProc(pres.proc, ProcBefore, "BeforeSbrk", REG_ARG_1);
    }
}
