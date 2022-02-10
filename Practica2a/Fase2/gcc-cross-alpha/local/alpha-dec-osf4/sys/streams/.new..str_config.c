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
#pragma ident "@(#)$RCSfile: str_config.c,v $ $Revision: 4.2.18.12 $ (DEC) $Date: 1994/03/30 23:04:46 $"
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */

#include <streams/str_stream.h>
#include <streams/str_debug.h>
#include <sys/stropts.h>
#include <sys/sysconfig.h>

/*
 *	Configuration of statically bound modules.
 *	If sources for the module/driver are available, then the
 *	configuration call should probably go there. If not, then
 *	those few lines of code can be coded here.
 *
 *	In any case, insert the configure call in str_config().
 *
 *	Note: If the cfgmgr is not used and instead this static
 *	scheme is chosen as your default, the order of the optional
 *	device configuration calls is important. There are also device
 *	numbers in streamsm/standard.c.
 */


/*
 * misc modules and drivers
 */
#include <svvs.h>

extern int      svvs_configure();

void
strdev_conf(name, entrypt, buf, bufsize)
	char *			name;
	cfg_entrypt_t		entrypt;
	char *			buf;
	int			bufsize;
{
	int			retval;

	if (retval = (entrypt)(CFG_OP_CONFIGURE,
			buf, strlen(buf), NULL, 0)) {
#if STREAMS_DEBUG
		printf("STREAMS: %s CONFIGURE call failed (error=%d)\n",
			name, retval);
#endif
		return;
	}
}

void
strdev_print(sc, name, retval)
	str_config_t *sc;
	char *name;
	int retval;
{
	if (retval)
		printf("STREAMS: '%s' configure failed (%d)\n", name, retval);
#if	STREAMS_DEBUG
	else
		printf("STREAMS: '%s' configured (device %d/%d)\n",
		    sc->sc_sa_name, major(sc->sc_devnum), minor(sc->sc_devnum));
#endif
}

void
strmod_print(sc, name, retval)
	str_config_t *sc;
	char *name;
	int retval;
{
	if (retval)
		printf("STREAMS: module '%s' configure failed (%d)\n",
			name, retval);
}

void
str_config()
{
	str_config_t	sb, sc;
	
#define sc_size		sizeof(sc)
	int		maj, retval;
	char		str_parm_buf[256];

	bzero((caddr_t)&sb, sc_size);
	sb.sc_version = OSF_STREAMS_CONFIG_10;
        sb.sc_devnum = NODEV;   /* will find available slot */


#if     SVVS && !SVVS_DYNAMIC
        /*
         * See comments in streamsm/svvs.c
         */
        for (;;) {
                retval = svvs_configure(CFG_OP_CONFIGURE,
                                        &sb, sc_size, &sc, sc_size);
                if (retval == ENOENT)
                        break;
                if (retval) {
                        if (sc.sc_sa_flags & STR_IS_DEVICE)
                                strdev_print(&sc, "svvs???", retval);
                        else
                                strmod_print(&sc, "svvs???", retval);
                        break;
                }
#if STREAMS_DEBUG
                if (sc.sc_sa_flags & STR_IS_DEVICE) {
                        printf("STREAMS: SVVS '%s' configured (device %d/%d)\n",
                                sc.sc_sa_name,
                                major(sc.sc_devnum), minor(sc.sc_devnum));
                } else
                                                                                                        printf("STREAMS: SVVS '%s' configured\n",
                                sc.sc_sa_name);
#endif
        }
#endif

                                                                                

/*
 * add new configurations above this comment
 */

}
