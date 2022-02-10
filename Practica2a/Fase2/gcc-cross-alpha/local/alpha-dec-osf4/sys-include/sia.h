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
/***** Until this works its commented out dupdef in Date variable
***#ifndef lint
***static char *rcsid = "@(#)$RCSfile: sia.h,v $ $Revision: 1.1.41.2 $ (DEC) $Date: 1998/06/19 17:33:37 $";
***#endif
***************/
/***********************************************************************
*	sia.h - SIA constants, structures, and macro definitions 
************************************************************************/
#ifndef _SIA_H_
#define _SIA_H_
#ifdef __cplusplus
extern "C" {
#endif

/***** sia common sys includes **/

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/sem.h>
#include <sys/uio.h>
#include <sys/audit.h>

/***** sia common usr includes **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sgtty.h>
#include <utmp.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <lastlog.h>
#include <errno.h>
#include <ttyent.h>
#include <syslog.h>
#include <limits.h>
#include <strings.h>
#include <loader.h>
#if defined(_LIBC_POLLUTION_H_) && defined(NLcatgets)
# undef NLcatgets
#endif
#include <nl_types.h>

#ifdef _THREAD_SAFE
#include <cma.h>
#include <pthread.h>
#endif

/**** sia logical definitions ****/

#ifndef	NULL
#define NULL 0L
#endif
#define YES 1
#define NO 0
#define TRUE 1
#define FALSE 0

/**** sia library and filenames ****/

#define SIALOGFILE      "/var/adm/sialog"          /* SIA logging file        */
#define SIAIGOODFILE    "/etc/sia/siainitgood"     /* sia init good file flag */
#define MATRIX_CONF     "/etc/sia/matrix.conf"     /* sia matrix config file  */
#define SIALIBCSO       "libc.so"                  /* local security in libc  */

/***** sia limits ***********/

#define SIABUFSIZ       1024    /* buffer size for loginname, password, and   */
                                /* one line of the SIA matrix config file     */
#define SIAPKGNAMAX     64      /* Libsia packagename maximum size            */
#define SIALIBNAMAX     64      /* Libsia packagename maximum size            */
#define SIADCAPMAX      32      /* max sec mech sia capabilities              */
#define SIASWMAX        4       /* max switches per capability                */
#define SIAMUTMAX       16      /* number mutexes utilized by SIA             */
#define SIAMXACCTNAME   64      /* maximum size of an account name            */
#define SIAMXPASSWORD   80      /* maximum size of a password                 */
#define SIANAMEMIN      16      /* minimum space allocated for entity->name   */

/**** Separate expansion sia entity structure ****/

typedef struct siaentitytoo {
			unsigned char *orig_amask;  /* audit mask pre-sia_ses_init */
			int orig_acntl;		    /* audit control flags pre-sia_ses_init */
			} SIAENTITYTOO;


/***** sia entity structure *******/ 

typedef struct siaentity {
                        char *name;             /* collected name             */
			char *password;         /* entered or collected password */
                        char *acctname;         /* account name               */
                        char **argv;            /* calling command argument   */
                                                /* strings                    */
                        int  argc;              /* number of arguments        */
			uid_t ouid;		/* original UID		      */
                        char *hostname;         /* requesting host NULL=>local*/
                        char *tty;              /* pathname of local tty      */
                        int colinput;           /* 1 => yes 0 => no input     */
                        int error;              /* error message value        */
                        int authcount;          /* Number of consecutive      */
                                                /* Failed authen attempts     */
                        int authtype;           /* Type of last authent       */
                        struct passwd *pwd;     /* pointer to pwent struct    */
			char *gssapi;
                        SIAENTITYTOO *siaetoo;	/* pointer to SIAENTITYTOO, formerly the previously unused and reserved field char *sia_pp */
                        int *mech[SIASWMAX];    /* pointers to mechanism      */
                                                /* specific data              */
                        } SIAENTITY;


/***** sia collect routine interface definition *****/

struct prompt_t
{
        unsigned char *prompt;
        unsigned char *result;
        int max_result_length;
        int min_result_length;
        int control_flags;
};
#ifndef __cplusplus
typedef struct prompt_t prompt_t;
#endif

typedef int sia_collect_func_t __((int /* timeout */, int /* rendition */,
					unsigned char * /* title */,
					int /* num_prompts */,
					prompt_t * /* prompts */));

/* top level returns from sia routines */

#define SIASUCCESS      1  		/* success return */
#define SIAFAIL         0 		/* failure return */
#define SIASTOP		2		/* stop processing */


/**************************************/
/***** sia top level interface    *****/
/***** special purpose routines   *****/
/**************************************/

extern int sia_init __((void));		/* only called from siainit command at*/
					/* boot time			      */

extern int sia_authorize __((SIAENTITY *entity)); /* only called internally */
					     /* for sia authorization */

extern int sia_chk_invoker __((void));	     /* called to check if process is */
					     /* sufficiently privialged	      */

extern int sia_get_groups __((const char *username, gid_t agroup, gid_t *buf, int *maxgroups)); /* initgroups processing, short of setgroups() */

extern int sia_collect_trm __((int timeout, int rendition, unsigned char *title, int num_prompts, prompt_t *prompts)); /* general collection routine for*/
					     /* terminals */
/**************************************/
/***** sia change secure info calls ***/
/**************************************/

extern int sia_chg_finger __((sia_collect_func_t *collect, char *username, int argc, char *argv[]));
extern int sia_chg_password __((sia_collect_func_t *collect, char *username, int argc, char *argv[]));
extern int sia_chg_shell __((sia_collect_func_t *collect, char *username, int argc, char *argv[]));

/*************************************/
/**** session processing calls	******/
/*************************************/


extern int sia_ses_init __((SIAENTITY **entityhdl, int argc, char *argv[], char *hostname, char *username, char *tty, int colinput, char *gssapi));
extern int sia_ses_authent __((sia_collect_func_t *collect, char *password, SIAENTITY *entity));
extern int sia_ses_reauthent __((sia_collect_func_t *collect,  SIAENTITY *entity));
extern int sia_ses_suauthent __((sia_collect_func_t *collect,  SIAENTITY *entity));
extern int sia_ses_estab __((sia_collect_func_t *collect, SIAENTITY *entity));
extern int sia_ses_launch __((sia_collect_func_t *collect, SIAENTITY *entity));
extern int sia_ses_release __((SIAENTITY **entityhdl));

/*********************************************/
/**** streamlined session processing calls ***/
/*********************************************/

#define	SIA_BEU_CLEARENV	0x001
#define	SIA_BEU_SETLUID		0x002
#define	SIA_BEU_DOCHDIR		0x004
#define	SIA_BEU_OKROOTDIR	0x008	/* ignored without *_DOCHDIR */
#define	SIA_BEU_REALLOGIN	0x010	/* do ses_estab & such, not su-style */
/* REALLOGIN implies DOCHDIR and SETLUID and sort-of implies OKROOTDIR */

extern int sia_become_user __((sia_collect_func_t *collect, int argc, char *argv[], char *hostname, char *username, char *tty, int colinput, char *gssapi, char **env, int flags));
extern int sia_validate_user __((sia_collect_func_t *collect, int argc, char *argv[], char *hostname, char *username, char *tty, int colinput, char *gssapi, char *passphrase));

#ifdef __cplusplus
}
#endif
#endif /* _SIA_H_ */
