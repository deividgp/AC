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
 * @(#)$RCSfile: sec_es_types.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/06/30 22:39:22 $
 */
#ifndef _SEC_ES_TYPES_H_
#define _SEC_ES_TYPES_H_

/* Define OSF/1 MLS system and program security events - values 0 - 31
 * reserved for kernel.
 */

#define	ES_KERNEL_STARTUP	32	/* boot record */
#define	ES_KERNEL_SHUTDOWN	33	/* shutdown record */
#define	ES_LOGIN_LOCAL		34	/* successful login */
#define	ES_LOGIN_REMOTE		35	/* successful login */
#define	ES_LOGIN_FAILED		36	/* failed login */
#define	ES_LOGOFF		37	/* logoff */
#define ES_AUTOLOG_TIMER	38	/* TPATH: auto-logoff by timer */
#define ES_SESSION		39	/* TPATH: new trusted path session */
#define ES_TPLOGIN		40	/* TPATH: successful tpath user login */
#define ES_TPLOGOFF		41	/* TPATH: trusted path logoff */
#define ES_AUTOLOG_MULTI	42	/* CHOTS: auto-logoff multi login */
#define ES_MULTI_FAILED		43	/* CHOTS: login failed multi login */
#define ES_2P_SUCCESS		44	/* CHOTS: two person check succeeded */
#define ES_2P_FAILED		45	/* CHOTS: two person check failed */
#define ES_LOGIN_MAX		46
#define	ES_PW_CHANGE		47	/* pw change */
#define	ES_PW_CHANGE_FAILED	48	/* pw change failed */
#define	ES_PW_CHANGE_NOPRIV	49	/* no priv for pw change */
#define ES_PW_MAX		50
#define	ES_USER_LOCK		51	/* login failure for locked user */
#define	ES_TERM_LOCK		52	/* login failure for locked terminal*/
#define ES_SET_USER_LOCK	53	/* lock user account */
#define ES_SET_USER_UNLOCK	54	/* unlock user account */
#define ES_SET_TERM_LOCK	55	/* lock terminal */
#define ES_SET_TERM_UNLOCK	56	/* unlock terminal */
#define	ES_TIME_LOCK		57	/* login failure for time lock */
#define ES_LOCK_MAX		58
#define ES_AUD_ENABLE		59	/* audit enabled */
#define	ES_AUD_DISABLE		60	/* disable auditing */
#define	ES_AUD_MODIFY		61	/* subsystem parameter modified */
#define	ES_AUD_REPORT		62	/* audit report generation */
#define	ES_AUD_ARCHIVE		63	/* compacted audit file archival */
#define	ES_AUD_DMN_INIT		64	/* compaction daemon start */
#define	ES_AUD_DMN_END		65	/* compaction daemon termination */
#define	ES_AUD_SHUTDOWN		66	/* audit shutdown notification */
#define	ES_AUD_ERROR		67	/* audit error condition */
#define ES_AUD_MAX		68
#define	ES_DB_INTEGRITY		69	/* Auth database integrity */
#define	ES_FS_INTEGRITY		70	/* File system discr integrity */
#define	ES_DB_RESOURCE		71	/* Auth database resource denial */
#define	ES_SEC_FAILURE		72	/* Security action failed in auth DB */
#define ES_DB_MAX		73
#define	ES_WS_DISPLAY_OPEN	74	/* display connection opened */
#define ES_WS_DISPLAY_CLOSED	75	/* display connection closed */
#define ES_WS_WINDOW_MANAGE	76	/* manage a client window */
#define ES_WS_WINDOW_UNMANAGE	77	/* unmanage a client window */
#define ES_WS_TP_MANAGE		78	/* manage trusted path client window */
#define ES_WS_IL_CHANGE		79	/* window information label change */
#define ES_WS_IL_FLOAT		80	/* window information label float */
#define ES_WS_IIL_CHANGE	81	/* window input information label chg */
#define ES_WS_SL_CHANGE		82	/* window input information label chg */
#define ES_WS_RUN_LEVEL_CHANGE	83	/* trusted path run level change */
#define ES_WS_CUT_PASTE		84	/* successful data paste */
#define ES_WS_CUT_PASTE_ERROR	85	/* setup error on cut paste */
#define ES_WS_FILE_IL_CHANGE	86	/* file information label change */
#define ES_WS_FILE_IL_FAILED	87	/* file information label error */
#define ES_WS_FILE_SL_CHANGE	88	/* file sensitivity label change */
#define ES_WS_FILE_SL_FAILED	89	/* file sensitivity label error */
#define ES_WS_FILE_BOTH_CHANGE	90	/* file il/sl label change */
#define ES_WS_FILE_BOTH_FAILED	91	/* file il/sl label error */
#define	ES_WS_ROLE_ASSUMED	92	/* enter an administrative role */
#define	ES_WS_ROLE_ENDED	93	/* leave an administrative role */
#define ES_WS_SL_DOWNGRADE	94	/* SL downgrade needed for paste */
#define ES_WS_IL_DOWNGRADE	95	/* window IL downgrade */
#define ES_WS_PW_CHANGE		96	/* sucessful password change */
#define ES_WS_PW_CHANGE_FAILED	97	/* unsuccessful password change */
#define ES_WS_PW_NO_AUTH	98	/* no authorization to change pw */
#define ES_WS_CHANGE_CLRNCE	99	/* downgrade session clearance */
#define	ES_WS_ACCESS_DENIED	100	/* server access denial */
#define	ES_WS_INSUFF_PRIV	101	/* server privilege denial */
#define	ES_WS_SERVER_RESET	102	/* server reset */
#define ES_WS_MAX		103
#define ES_MAX_CODE	ES_WS_MAX	/* based on WINDOW_SYSTEM group */

#endif
