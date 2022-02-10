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
#pragma ident "@(#)$RCSfile: iscc_data.c,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1995/12/06 20:16:02 $"


/*
 * INCLUDE FILES:
 */

#include <sys/conf.h>				/* define block and character device	*/
						/* driver switch tables			*/
#include <sys/errno.h>				/* define device driver error codes	*/
#include <sys/workstation.h>			/* define structures for workstation	*/
						/* output drivers and ioctl requests	*/
#include <sys/inputdevice.h>			/* define structures for workstation	*/
						/* input drivers and ioctl requests	*/
#include <sys/kernel.h>				/* define kernel global variables used	*/
						/* by device drivers			*/
#include <sys/malloc.h>				/* define kernel memory allocator	*/
						/* related information			*/
#include <sys/types.h>				/* define system data types, major and	*/
						/* minor device interfaces		*/
#include <sys/tty.h>				/* define per-line tty structure	*/
#include <sys/uio.h>				/* define user i/o (uio) structure	*/
#include <sys/wsdevice.h>			/* define structures/interfaces for	*/
						/* workstation pseudo-device driver	*/

#include <hal/console.h>			/* define structures and constants used */
						/* by the system for console i/o	*/

#include <io/common/devdriver.h>		/* define structures, constants, and    */
						/* interfaces used by device drivers 	*/
						/* and autoconfiguration code		*/
#include <io/dec/eisa/isa.h>			/* define structures, constants, and	*/
						/* interfaces unique to the isa bus	*/
#include <io/dec/eisa/isccregs.h>		/* define iscc hardware registers	*/

#include <machine/cpu.h>			/* define constants and structures	*/
						/* related to the processor		*/
#include <machine/rpb.h>			/* define restart parameter block	*/


/*
 * LOCAL STORAGE:
 */

#ifdef	BINARY

extern ihandler_id_t *
		iscc_ih_id[];			/* per-device interrupt handler id	*/
extern struct controller *
		iscc_info[];			/* per-device controller structure	*/
extern io_handle_t
		iscc_iobase[];			/* per-line i/o handle		        */
extern int	iscc_ndev;			/* number of configured z8530 devices	*/
extern int	iscc_nline;			/* number of configured serial lines	*/
extern struct iscc_softc *
		iscc_sc;			/* per-driver soft controller structure	*/
extern caddr_t	iscc_std[];			/* list of optional hardware csr's	*/
extern struct tty
		iscc_tty[];			/* per-line tty structure	        */
extern int	iscc_tty_baudrate[];		/* per-line baud rate setting		*/
extern int	iscc_tty_break[];		/* per-line break control/status	*/
extern u_long	iscc_tty_charmask[];		/* per-line tty character mask		*/

#else

#include "iscc.h"				/* include iscc driver header file 	*/
						/* (no. of configured z8530 devices)	*/

ihandler_id_t *
		iscc_ih_id[NISCC_DEV];		/* per-device interrupt handler id	*/
struct controller *
		iscc_info[NISCC_DEV];		/* per-device controller structure	*/
io_handle_t	iscc_iobase[NISCC_LINE];	/* per-line i/o handle		        */
int		iscc_ndev  = NISCC_DEV;		/* number of configured z8530 devices	*/
int		iscc_nline = NISCC_LINE;	/* number of configured serial lines	*/
struct iscc_softc *
		iscc_sc;			/* per-driver soft controller structure */
caddr_t		iscc_std[] = { 0 };		/* list of optional hardware csr's	*/
struct tty	iscc_tty[NISCC_LINE];		/* per-line tty structure	        */
int		iscc_tty_baudrate[NISCC_LINE];	/* per-line baud rate setting		*/
int		iscc_tty_break[NISCC_LINE];	/* per-line break control/status	*/
u_long		iscc_tty_charmask[NISCC_LINE];	/* per-line tty character mask		*/

#endif
