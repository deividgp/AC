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
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * derived from cpuconf.c	4.14      (ULTRIX)  12/6/90;
 */


/***********************************************************************
 *
 * Modification History: cpuconf.c
 *
 * 30-oct-91	jac	Fixup Alpha switches from sync to BL6
 *
 * 28-oct-91	jac	Added nulladdrcpu routine. Used as null routine for
 *			functions which must return an address (and therefore
 *			may have a 64 bit return value)
 *
 * 03-Oct-91    ald     added flamingo support
 *
 * 12-sep-91    jac     added nexaddr routine reference
 *
 * 21-jun-91    jac     added laser/ruby  support
 *
 * 03-May-91    afd
 *      Alpha support.
 *
 * 10-May-91	Paul Grist
 *	Added support for 3max+/bigmax (DS_5000_300).
 *
 * 15-Oct-90	Randall Brown
 *	Added errlogging routines to cpusw for 3min.
 *
 * 09-Oct-90    jaw
 * 	merge in MM changes for rigel.
 *
 * 09-Oct-90    Paul Grist
 *      added startclock routine to cpuswitch for mipsmate, this
 *      fixes hangs after power-fails when the system needs to
 *      acess non-root disks, which are not spun up, the cases
 *      that were seen were swap on non-root and presto buffers.
 *
 * 01-Sep-90	sekhar
 *	added functions and stubs for print_consinfo interface.
 *      kn02_print_consinfo, kn02_log_errinfo 	- DS5000 (3MAX)
 *	kn220_print_consinfo, kn220_log_errinfo	- DS5500 (MIPSFAIR2)
 *	nullcpu stubs for other machines (both mips and vax).
 *
 * 31-Aug-90	Jim Paradis
 *	Added additional stubs for VAX9000 routines
 *
 * 03-Aug-90	rafiey (Ali Rafieymehr)
 *	Added support for VAX9000.
 *
 * 21-Jun-90	Fred L. Templin
 *	Added dummies for TURBOchannel data structures for case of
 *	DS5000 not defines. (Solution from afd).
 *
 * 20-Mar-90    Paul Grist
 *      Added MIPSMATE support (DS_5100).
 *
 * 30-Apr-90	Randall Brown
 *	Added new cpu entry for DS_5000_100.  Filled in the new values
 *	of the switch table for the MIPS systems. ( spls, intr, clock stuff)
 *
 * 06-Mar-90	afd
 *	Put mc146818startclocks() into cpu switch for pmax/3max.
 *
 * 18-Jan-90	robin
 *	Added kn220badaddr function to get badaddr to work with the
 *	way the KN220 memory intrrupts are cleared.
 *
 * 29-Dec-89	afd
 *	Added definitions for kn02erradr & kn02chksyn for when
 *	DS5000 not defined.
 *
 * 26-Dec-89	robin
 *	changed the kn220 write buffer routine used by 5500.
 *
 * 08-Dec-89	jaw
 *	fix 6200 entry from merge damage.
 *
 * 30-Nov-89    Paul Grist
 *      Added 8800 error logging routines as stubs for non-8800 
 *      VAXBI systems that will use biinit.c Did the same for
 *      ka6200 and ka6400.
 *
 * 14-Nov-89	gmm
 *	Remove kn5800_iscpu() and add kn5800_init_secondary().
 *
 * 30-Oct-89	afd
 *	Use kn01 cache flush routines for kn02 (DS5000 - 3max).
 *
 * 11-Aug-89	afd
 *	Set up 3MAX cpu struct in cpu switch table.
 *	
 * 10-Jul-89	burns
 *	For DS5800 moved several "vax" only fields into mips. Added
 *	the msize and cpuinit routines for afd. Added cache routines
 *	to the cpu switch for DS5800.
 *
 * 14-June-89	afd
 *	Fill in new HZ field in cpuswitch (used to be in param.c).
 *	hz, tick, tickadj are set in processor specific init routines.
 *
 * 23-May-89	darrell
 *	Merged VVAX support.
 *
 * 03-May-89	darrell
 *	Merged in VAX6400 support.
 *
 * 07-Apr-89	afd
 *	Created this file as a merged version of the old VAX cpuconf.c
 *	with new entries for MIPS based systems.  This file now supports
 *	both VAX and MIPS based systems.
 *
 **********************************************************************/

#pragma ident "@(#)$RCSfile: cpuconf.c,v $ $Revision: 1.2.138.3 $ (DEC) $Date: 1997/10/06 18:55:56 $"

#include <sys/param.h>
#include <hal/cpuconf.h>
#include <machine/cpu.h>

#ifndef DEC2100_A500
extern int      kn450_config_io()  { return (0); }
#endif /* DEC2100_A500 */

#ifndef DEC2100_C500
extern int      kn470_config_io()  { return (0); }
#endif /* DEC2100_C500 */

#ifndef DEC3000_500
kn15aa_is_sandpiper() { return (0); }
kn15aa_set_ioslot() {}
kn15aa_read_ioslot() { return (0); }
kn15aa_read_ir() { return (0); }
#endif /* DEC3000_500 */

#ifndef DEC2000_300
extern int      kn121_configure_io()  { return (0); }
#endif /*DEC2000_300*/
