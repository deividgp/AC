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

#ifndef __AUDIT__
#define __AUDIT__ 1

#include <sys/types.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sys/syscall.h>
#include <sys/systm.h>
#include <sys/habitat.h>
#if MLS_AUDIT
#include <sys/security.h>
#include <sys/secpolicy.h>
#endif /* MLS_AUDIT */

/* audcntl options */
#define GET_SYS_AMASK           0
#define SET_SYS_AMASK           1
#define GET_TRUSTED_AMASK       2
#define SET_TRUSTED_AMASK       3
#define GET_PROC_AMASK          4
#define SET_PROC_AMASK          5
#define GET_PROC_ACNTL          6
#define SET_PROC_ACNTL          7
#define GET_AUDSWITCH           8
#define SET_AUDSWITCH           9
#define GETPAID                10
#define SETPAID                11
#define GET_AUDSTYLE           12
#define SET_AUDSTYLE           13
#define GET_SITEMASK           14
#define SET_SITEMASK           15
#define GET_OBJAUDBIT          16
#define SET_OBJAUDBIT          17
#define UPDEVENTS              18
#define FLUSH_AUD_BUF          19
#define GET_HABITAT_EVENT      20
#define SET_HABITAT_EVENT      21
#define GET_NSITEVENTS         22
#define GET_AUDSIZE            23
#define GET_SUBJ_AMASK         24
#define GET_SUBJ_ACNTL         25
#define GET_DATALEN            30

#if MLS_AUDIT
/* MLS note: these audcntl options are for the support of the MLS product,
   and are not guaranteed to be present after MLS support merges into the
   base product.
*/
#define GET_SLRANGE            39
#define SET_SLRANGE            40
#endif /* MLS_AUDIT */


/* audcntl flags - exclusive states */
#define AUDIT_OR             0x000
#define AUDIT_AND            0x001
#define AUDIT_OFF            0x002
#define AUDIT_USR            0x004
#define AUDIT_CNTLMASK       0x007

/* audcntl flags - non-exclusive states */
#define AUDIT_SYSCALL_OFF    0x008
#define AUDIT_HABITAT_USR    0x010

/* audcntl UPDEVENTS flags */
#define UPD_CNTL             0x001
#define UPD_MASK             0x002

/* audstyle flags */
#define AUD_EXEC_ARGP        0x001
#define AUD_EXEC_ENVP        0x002
#define AUD_LOGIN_UNAME      0x004
#define AUD_OBJ_DESEL        0x008
#define AUD_OBJ_SEL          0x010
#define AUD_OBJ_MASK         (AUD_OBJ_DESEL|AUD_OBJ_SEL)
#define AUD_STYLFLAGS        0x01f  /* user visible flags */
#define AUD_PROPL_UNAVAIL    0x80000000   /* kernel only  */

/* audioctl commands and structure */
#define AUDIOCGETN           _IOR('C', 0, struct audiocp)
#define AUDIOCSETN           _IOW('C', 1, int)
struct audiocp {
    u_int size;              /* size of audit buffer      */
    u_int offset;            /* offset into buffer        */
    u_int nbytes;            /* # bytes of data available */
};

/* objaudbit/property-list values */
#define AUD_PROPL_FLAG       "DEC_AUDIT_PROPLISTFLAG"
#define AUD_SELECT           0x1
#define AUD_DESELECT         0x2

/* misc values */
#define AUID_INVAL          -1
#define AUDITD_RECSZ         (MAXPATHLEN*2)
#define AUD_BUF_SIZ          4096
#define AUD_MAXEVENT_LEN     64
#define N_SYSCALLS           ((LAST&~0x3)+(NBBY>>1))
#define MAXHABSYSCALL_LEN    128
#define AUD_VNOMAX           2      /* must be at least 2 */
#define N_AUDTUPLES          128


/* audit version number
    also distinguish between 64-bit and 32-bit longword
    low-order 16 bits used for version #
    high-order 16 bits used for flags

    - updated to version 2 for new msfs_syscall audit format
*/
#define AUD_VERSION          0x0002
#define AUD_VERS_MASK        0x00ff
#define AUD_VERS_LONG        0x8000     /* 64-bit longword */
#define AUD_MLS              0x4000     /* mls data        */


/* token encodings:
    bit 0x80 (TP_* tokens) indicates private token; cannot be given to audgen(2)
    0x01-0x1f, 0x81-0x8f are reserved for ptr token types
*/
#define A_TOKEN_PRIV(x)      ((x)&0x80)
#define A_TOKEN_PTR(x)       (((x)&0x7f) >= 0x01 && ((x)&0x7f) <= AUD_TOKEN_PTR_MAX)
#define A_TOKEN_IOVEC(x)     ((x) >= AUD_TOKEN_IOVEC_MIN && (x) <= AUD_TOKEN_PTR_MAX)


#if MLS_AUDIT
#define AUD_COMPAT           1
/* -- MLS tokens --
    MLS note: tags will not be used in platinum.  These tokens will either
    not be present, or will not be used in this fashion once MLS merges
    int the base pool.
*/
#define T_PRIVMASK           0x0f   /* 0017 */ /* privvec_t */
#define TP_PRIVMASK          0x8f   /* 0217 */ /* support to be dropped */

#define T_MLSACL             0x7c   /* 0174 */ /* tag_t/uint_t for now */
#define T_SLABEL             0x7d   /* 0175 */ /* tag_t/uint_t for now */
#define T_ILABEL             0x7e   /* 0176 */ /* tag_t/uint_t for now */
#define T_SECEVENT           0x7f   /* 0177 */
#define TP_SLABEL            0xfb   /* 0373 */ /* support to be dropped */
#define TP_ILABEL            0xfc   /* 0374 */ /* support to be dropped */
#define TP_SECEVENT          0xfd   /* 0375 */ /* support to be dropped */
#define TP_PRIV              0xfe   /* 0376 */
#endif /* MLS_AUDIT */


/* -- public tokens -- */
    /* start of ptr token types */
#define AUD_T_CHARP          0x01   /* 0001 */
#define AUD_T_SOCK           0x03   /* 0003 */
#define AUD_T_LOGIN          0x04   /* 0004 */
#define AUD_T_HOMEDIR        0x05   /* 0005 */
#define AUD_T_SHELL          0x06   /* 0006 */
#define AUD_T_DEVNAME        0x07   /* 0007 */
#define AUD_T_SERVICE        0x08   /* 0010 */
#define AUD_T_HOSTNAME       0x09   /* 0011 */
#define AUD_T_INTP           0x0a   /* 0012 */
    /* 1st element of int array is # of data elements in array */

    /* start of iovec style data */
#define AUD_TOKEN_IOVEC_MIN  0x18
#define AUD_T_OPAQUE         0x18   /* 0030 */
#define AUD_T_INTARRAY       0x19   /* 0031 */
#define AUD_T_GIDSET         0x1a   /* 0032 */
#define AUD_T_XDATA          0x1b   /* 0033 */
#define AUD_TOKEN_PTR_MAX    0x1f   /* 0037 */
    /* end of iovec style data */
    /* end of ptr token types */

#define AUD_T_AUID           0x20   /* 0040 */
#define AUD_T_RUID           0x21   /* 0041 */
#define AUD_T_UID            0x22   /* 0042 */
#define AUD_T_PID            0x23   /* 0043 */
#define AUD_T_PPID           0x24   /* 0044 */
#define AUD_T_GID            0x25   /* 0045 */
#define AUD_T_EVENT          0x26   /* 0046 */
#define AUD_T_SUBEVENT       0x27   /* 0047 */

#define AUD_T_DEV            0x28   /* 0050 */
#define AUD_T_ERRNO          0x29   /* 0051 */
#define AUD_T_RESULT         0x2a   /* 0052 */
#define AUD_T_MODE           0x2b   /* 0053 */
#define AUD_T_HOSTADDR       0x2c   /* 0054 */
#define AUD_T_INT            0x2d   /* 0055 */
#define AUD_T_DESCRIP        0x2e   /* 0056 */
#define AUD_T_HOSTID         0x2f   /* 0057 */

#define AUD_T_X_ATOM         0x30   /* 0060 */
#define AUD_T_X_CLIENT       0x31   /* 0061 */
#define AUD_T_X_PROPERTY     0x32   /* 0062 */
#define AUD_T_X_RES_CLASS    0x33   /* 0063 */
#define AUD_T_X_RES_TYPE     0x34   /* 0064 */
#define AUD_T_X_RES_ID       0x35   /* 0065 */


/* -- private tokens -- */
#define AUD_TP_ACCRGHT       0x81   /* 0201 */
#define AUD_TP_MSGHDR        0x82   /* 0202 */
#define AUD_TP_EVENTP        0x83   /* 0203 */
#define AUD_TP_HABITAT       0x84   /* 0204 */
#define AUD_TP_ADDRVEC       0x85   /* 0205 */
#define AUD_TP_INTP          0x86   /* 0206 */

#define AUD_TP_AUID          0xa1   /* 0241 */
#define AUD_TP_RUID          0xa2   /* 0242 */
#define AUD_TP_UID           0xa3   /* 0243 */
#define AUD_TP_PID           0xa4   /* 0244 */
#define AUD_TP_PPID          0xa5   /* 0245 */
#define AUD_TP_HOSTADDR      0xa6   /* 0246 */
#define AUD_TP_EVENT         0xa7   /* 0247 */

#define AUD_TP_SUBEVENT      0xa8   /* 0250 */
#define AUD_TP_NCPU          0xa9   /* 0251 */
#define AUD_TP_DEV           0xaa   /* 0252 */
#define AUD_TP_LENGTH        0xab   /* 0253 */
#define AUD_TP_IPC_GID       0xac   /* 0254 */
#define AUD_TP_IPC_MODE      0xad   /* 0255 */
#define AUD_TP_IPC_UID       0xae   /* 0256 */
#define AUD_TP_TV_SEC        0xaf   /* 0257 */

#define AUD_TP_TV_USEC       0xb0   /* 0260 */
#define AUD_TP_SHORT         0xb1   /* 0261 */
#define AUD_TP_LONG          0xb2   /* 0262 */
#define AUD_TP_VNODE_DEV     0xb3   /* 0263 */
#define AUD_TP_VNODE_ID      0xb4   /* 0264 */
#define AUD_TP_VNODE_MODE    0xb5   /* 0265 */
#define AUD_TP_VERSION       0xb6   /* 0266 */
#define AUD_TP_SET_UIDS      0xb7   /* 0267 */

#define AUD_TP_CONT          0xb8   /* 0270 */
#define AUD_TP_TID           0xb9   /* 0271 */

#if defined(AUD_COMPAT) || defined(KERNEL)
/* -- public tokens -- */
    /* start of ptr token types */
#define T_CHARP              AUD_T_CHARP
#define T_SOCK               AUD_T_SOCK
#define T_LOGIN              AUD_T_LOGIN
#define T_HOMEDIR            AUD_T_HOMEDIR
#define T_SHELL              AUD_T_SHELL
#define T_DEVNAME            AUD_T_DEVNAME
#define T_SERVICE            AUD_T_SERVICE
#define T_HOSTNAME           AUD_T_HOSTNAME
#define T_INTP               AUD_T_INTP
    /* 1st element of int array is # of data elements in array */

    /* start of iovec style data */
#define T_OPAQUE             AUD_T_OPAQUE
#define T_INTARRAY           AUD_T_INTARRAY
#define T_GIDSET             AUD_T_GIDSET
#define T_XDATA              AUD_T_XDATA
    /* end of iovec style data */
    /* end of ptr token types */

#define T_AUID               AUD_T_AUID
#define T_RUID               AUD_T_RUID
#define T_UID                AUD_T_UID
#define T_PID                AUD_T_PID
#define T_PPID               AUD_T_PPID
#define T_GID                AUD_T_GID
#define T_EVENT              AUD_T_EVENT
#define T_SUBEVENT           AUD_T_SUBEVENT

#define T_DEV                AUD_T_DEV
#define T_ERRNO              AUD_T_ERRNO
#define T_RESULT             AUD_T_RESULT
#define T_MODE               AUD_T_MODE
#define T_HOSTADDR           AUD_T_HOSTADDR
#define T_INT                AUD_T_INT
#define T_DESCRIP            AUD_T_DESCRIP
#define T_HOSTID             AUD_T_HOSTID

#define T_X_ATOM             AUD_T_X_ATOM
#define T_X_CLIENT           AUD_T_X_CLIENT
#define T_X_PROPERTY         AUD_T_X_PROPERTY
#define T_X_RES_CLASS        AUD_T_X_RES_CLASS
#define T_X_RES_TYPE         AUD_T_X_RES_TYPE
#define T_X_RES_ID           AUD_T_X_RES_ID


/* -- private tokens -- */
#define TP_ACCRGHT           AUD_TP_ACCRGHT
#define TP_MSGHDR            AUD_TP_MSGHDR
#define TP_EVENTP            AUD_TP_EVENTP
#define TP_HABITAT           AUD_TP_HABITAT
#define TP_ADDRVEC           AUD_TP_ADDRVEC
#define TP_INTP              AUD_TP_INTP

#define TP_AUID              AUD_TP_AUID
#define TP_RUID              AUD_TP_RUID
#define TP_UID               AUD_TP_UID
#define TP_PID               AUD_TP_PID
#define TP_PPID              AUD_TP_PPID
#define TP_HOSTADDR          AUD_TP_HOSTADDR
#define TP_EVENT             AUD_TP_EVENT

#define TP_SUBEVENT          AUD_TP_SUBEVENT
#define TP_NCPU              AUD_TP_NCPU
#define TP_DEV               AUD_TP_DEV
#define TP_LENGTH            AUD_TP_LENGTH
#define TP_IPC_GID           AUD_TP_IPC_GID
#define TP_IPC_MODE          AUD_TP_IPC_MODE
#define TP_IPC_UID           AUD_TP_IPC_UID
#define TP_TV_SEC            AUD_TP_TV_SEC

#define TP_TV_USEC           AUD_TP_TV_USEC
#define TP_SHORT             AUD_TP_SHORT
#define TP_LONG              AUD_TP_LONG
#define TP_VNODE_DEV         AUD_TP_VNODE_DEV
#define TP_VNODE_ID          AUD_TP_VNODE_ID
#define TP_VNODE_MODE        AUD_TP_VNODE_MODE
#define TP_VERSION           AUD_TP_VERSION
#define TP_SET_UIDS          AUD_TP_SET_UIDS

#define TP_CONT              AUD_TP_CONT
#define TP_TID               AUD_TP_TID
#endif /* defined(AUD_COMPAT) || defined(KERNEL) */


/* trusted audit events */
#define MIN_TRUSTED_EVENT    512
#define AUDIT_START          512
#define AUDIT_STOP           513
#define AUDIT_SETUP          514
#define AUDIT_SUSPEND        515
#define AUDIT_LOG_CHANGE     516
#define AUDIT_LOG_CREAT      517
#define AUDIT_XMIT_FAIL      518
#define AUDIT_REBOOT         519
#define AUDIT_LOG_OVERWRITE  520
#define AUDIT_DAEMON_EXIT    521
#define LOGIN                522
#define LOGOUT               523
#define AUTH_EVENT           524
#define AUDGEN8              525
#define SW_COMPATIBILITY     526    /* MLS compatibility */
#define DNSIX_AUDIT_EVENT    527    /* MLS */
#define AUTHORIZATION_USE    528    /* MLS */

#define X_SERVER_STARTUP     540
#define X_SERVER_SHUTDOWN    541
#define X_CLIENT_STARTUP     542
#define X_CLIENT_SHUTDOWN    543
#define X_CLIENT_ATTR        544
#define X_OBJECT_ATTR        545    /* MLS */
#define X_OBJECT_CREATE      546
#define X_OBJECT_RENAME      547
#define X_OBJECT_DESTROY     548
#define X_DATA_MOVE          549    /* MLS */
#define X_OBJECT_READ        550
#define X_OBJECT_WRITE       551
#define X_SEC_CLEARANCE      552    /* MLS */
#define X_TPATH_HNDLR        553    /* MLS */
#define X_SELECTION_HNDLR    554    /* MLS */
#define X_WIN_MNGR           555    /* MLS */

#define LPR_EVENT            573    /* MLS */

/* retired/recycled values */
#define X_SERVER_DAC         544
#define X_CLIENT_IPC         545
#define X_OBJECT_DAC         549


#define MAX_TRUSTED_EVENT    (MIN_TRUSTED_EVENT+N_TRUSTED_EVENTS-1)

/* trusted, site event info */
#define N_TRUSTED_EVENTS     64
#define MIN_SITE_EVENT       2048


/* X auditing; data format associated with AUD_T_XDATA (iov_base) */
struct aud_xdata {
    u_short version;
#if MLS_AUDIT
#define AUD_XOBJ_VERSION    (0|AUD_MLS)
#else
#define AUD_XOBJ_VERSION    0
#endif /* MLS_AUDIT */
    u_short flags;
#define AUD_XOBJ_CLIENT     0x001
#define AUD_XOBJ_OBJECT     0x002
    uid_t   auid;                   /* -1 if no auid, euid, egid included */
    uid_t   euid;
    gid_t   egid;
    int     gidsetsize;             /* # of groups in gidset        */
    gid_t   gidset[NGROUPS_MAX];
    pid_t   pid;                    /* 0 if no pid included         */
    mode_t  mode;                   /* -1 if no mode included       */
    int     client_id;              /* -1 if no client_id included  */
    int     objtyp;                 /* -1 if no client_id included  */
    u_int   atom;                   /* 0 if no atom included        */
    u_int   res_id;                 /* 0 if no res_id included      */
    char    info_string[80];
    char    hdr_string[80];
#if MLS_AUDIT
    priv_t  privmask[SEC_SPRIVVEC_SIZE]; /* 0'ed, if not included   */
    tag_t   acl;                    /* SEC_MAC_NULL_TAG if no label */
    tag_t   slabel;                 /* SEC_MAC_NULL_TAG if no label */
    tag_t   ilabel;                 /* SEC_MAC_NULL_TAG if no label */
    tag_t   kbd_il;                 /* SEC_MAC_NULL_TAG if no label */
    tag_t   ptr_il;                 /* SEC_MAC_NULL_TAG if no label */
#endif /* MLS_AUDIT */
};



/* macros used for auditmask lengths
    kernel space: used as int-mask
    user space: used as char-mask
*/
#define AUDMASK_LEN(x)       ((x) > 0 ? ((x)-1)/(NBBY>>1)+1 : 0)
#define SYSCALL_MASK_LEN     AUDMASK_LEN(N_SYSCALLS)
#define TRUSTED_MASK_LEN     AUDMASK_LEN(N_TRUSTED_EVENTS)
#define AUDIT_MASK_LEN       (SYSCALL_MASK_LEN+TRUSTED_MASK_LEN)
#define AUDINTMASK_LEN(x)    ((x) > 0 ? ((x)-1)/(WORD_BIT>>1)+1 : 0)
#define SYSCALL_INTMASK_LEN  AUDINTMASK_LEN(N_SYSCALLS)
#define TRUSTED_INTMASK_LEN  AUDINTMASK_LEN(N_TRUSTED_EVENTS)
#define AUDIT_INTMASK_LEN    (SYSCALL_INTMASK_LEN+TRUSTED_INTMASK_LEN)


/* macros used to adjust various auditmasks */
#define BYTE_IN_MASK(event)         ((event)>>2)
#define BITS_IN_BYTE(status,event)  ( (status) << ( (~(event) & ((NBBY>>1)-1)) << 1) )
#define WORD_IN_MASK(event)         ((event)>>4)
#define BITS_IN_WORD(status,event)  ( (status) << EVENT_SHIFT(event) )
#define EVENT_SHIFT(event)          \
    ((((event)&((WORD_BIT>>1)-1) | 0x3) - ((event)&0x3)) << 1)

/* adjust buf for system audit_mask by setting event succeed/fail bits */
#define A_SYSMASK_SET(buf,event,succeed,fail) \
    { if ( (event) >= MIN_TRUSTED_EVENT ) { \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT)] &= ~BITS_IN_BYTE(0x3,(event)-MIN_TRUSTED_EVENT); \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT)] |= \
            BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)-MIN_TRUSTED_EVENT); \
      } \
      else { \
        (buf)[BYTE_IN_MASK(event)] &= ~BITS_IN_BYTE(0x3,(event)); \
        (buf)[BYTE_IN_MASK(event)] |= BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)); \
      } \
    }

/* adjust buf for user audit_mask by setting event succeed/fail bits */
#define A_PROCMASK_SET(buf,event,succeed,fail) \
    { if ( (event) >= MIN_TRUSTED_EVENT ) { \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT+N_SYSCALLS)] &= \
            ~BITS_IN_BYTE(0x3,(event)-MIN_TRUSTED_EVENT+N_SYSCALLS); \
        (buf)[BYTE_IN_MASK((event)-MIN_TRUSTED_EVENT+N_SYSCALLS)] |= \
            BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)-MIN_TRUSTED_EVENT+N_SYSCALLS); \
      } \
      else { \
        (buf)[BYTE_IN_MASK(event)] &= ~BITS_IN_BYTE(0x3,(event)); \
        (buf)[BYTE_IN_MASK(event)] |= BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)); \
      } \
    }

/* adjust buf for siteauditmask by setting event succeed/fail bits */
#define A_SITEMASK_SET(buf,event,succeed,fail) \
    { if ( (event) >= MIN_SITE_EVENT ) { \
        (buf)[BYTE_IN_MASK((event)-MIN_SITE_EVENT)] &= \
            ~BITS_IN_BYTE(0x3,(event)-MIN_SITE_EVENT); \
        (buf)[BYTE_IN_MASK((event)-MIN_SITE_EVENT)] |= \
            BITS_IN_BYTE(( ((succeed)<<1)|(fail) ),(event)-MIN_SITE_EVENT); \
      } \
    }


#ifdef KERNEL
#include "bin_compat.h"

/* macros to check auditability of event according to auditmask; 2 bits/event */
#define EVENT_BITS(mask,event)  (((mask)[WORD_IN_MASK(event)] >> \
					EVENT_SHIFT(event)) & 0x3)
#define AUDIT_EVENT_K(event)    (syscallauditmask[(event)])
#define AUDIT_EVENT_U(event)    (EVENT_BITS(u.u_auditmask,(event)))
#define AUDIT_EVENT_T(event)    (EVENT_BITS(trustedauditmask,(event)))
#define AUDIT_EVENT_S(event)    (EVENT_BITS(siteauditmask,(event)))

#define DO_AUD(event) \
    ((u.u_audit_cntl & (AUDIT_OFF|AUDIT_SYSCALL_OFF)) ? 0 : \
    ((u.u_audit_cntl & AUDIT_AND) ? \
        AUDIT_EVENT_K(event) & AUDIT_EVENT_U(event) : \
    ((u.u_audit_cntl & AUDIT_USR) ? \
        AUDIT_EVENT_U(event) : \
        AUDIT_EVENT_K(event) | AUDIT_EVENT_U(event) )))

#define DO_TRUSTED_AUD(event) \
    ((u.u_audit_cntl & AUDIT_OFF) ? 0 : \
    ((u.u_audit_cntl & AUDIT_AND) ? \
        AUDIT_EVENT_T((event)-MIN_TRUSTED_EVENT) & AUDIT_EVENT_U((event)-MIN_TRUSTED_EVENT+N_SYSCALLS) : \
    ((u.u_audit_cntl & AUDIT_USR) ? \
        AUDIT_EVENT_U((event)-MIN_TRUSTED_EVENT+N_SYSCALLS) : \
        AUDIT_EVENT_T((event)-MIN_TRUSTED_EVENT) | AUDIT_EVENT_U((event)-MIN_TRUSTED_EVENT+N_SYSCALLS) )))


#if BIN_COMPAT
#define DO_HABITAT_AUD(habitat,event,error) \
    ( u.u_audit_cntl & AUDIT_HABITAT_USR \
    || \
    (!(u.u_audit_cntl & (AUDIT_OFF|AUDIT_SYSCALL_OFF|AUDIT_USR)) && \
    habitats[(habitat)] && habitats[(habitat)]->cm_auditmask && \
    (EVENT_BITS(habitats[(habitat)]->cm_auditmask, (event)) & \
        (((error) == 0) ? 0x02 : 0x01))) )

#define DO_AUDIT(event,error) \
	(audswitch && \
		(!hbval(event) ? \
			(DO_AUD(event) & (((error) == 0) ? 0x02 : 0x01)) \
		: \
			(DO_HABITAT_AUD(hbval(event),syscval(event),(error)))))

#else /* BIN_COMPAT */
#define DO_AUDIT(event,error) \
	(audswitch && (DO_AUD(event) & (((error) == 0) ? 0x02 : 0x01)))
#endif /* BIN_COMPAT */


/* perform audit_rec_build if auditing on for specified event/proc */
#if BIN_COMPAT
#define AUDIT_CALL(event,error,args,retval,flags,param) \
do { \
	u_int c, h, m, *mp; \
	if (audswitch && !((c = u.u_audit_cntl) & (AUDIT_OFF|AUDIT_SYSCALL_OFF))) { \
		if (!(h = hbval(event))) { \
			m = AUDIT_EVENT_U(event); \
			if (c & AUDIT_AND) \
				m &= AUDIT_EVENT_K(event); \
			else if (!(c & AUDIT_USR)) \
				m |= AUDIT_EVENT_K(event); \
		} else { \
			if (c & AUDIT_HABITAT_USR) \
				m = 0x03; \
			else if (!(c & AUDIT_USR) && \
			    habitats[h] && (mp = habitats[h]->cm_auditmask)) \
				m = EVENT_BITS(mp, syscval(event)); \
			else \
				m = 0; \
		} \
		if (m & (((error) == 0) ? 0x02 : 0x01)) \
			audit_rec_build((event), (args), (error), (retval), \
				(flags), (param)); \
	} \
} while (0)

#else /* BIN_COMPAT */

#define AUDIT_CALL(event,error,args,retval,flags,param) \
do { \
	u_int c, m; \
	if (audswitch && !((c = u.u_audit_cntl) & (AUDIT_OFF|AUDIT_SYSCALL_OFF))) { \
		m = AUDIT_EVENT_U(event); \
		if (c & AUDIT_AND) \
			m &= AUDIT_EVENT_K(event); \
		else if (!(c & AUDIT_USR)) \
			m |= AUDIT_EVENT_K(event); \
		if (m & (((error) == 0) ? 0x02 : 0x01)) \
			audit_rec_build((event), (args), (error), (retval), \
				(flags), (param)); \
	} \
} while (0)
#endif /* BIN_COMPAT */


/* version of AUDIT_CALL which calls a function instead of inline expansion;
   specifically to decrease text space growth
*/
#define AUDIT_CALL2(event,error,args,retval,flags,param) \
do { \
	if (audswitch) \
        	audit_call((event), (error), (args), (retval), (flags), \
			(param)); \
} while (0)


/* audit_rec_build operations */
#define AUD_VNO              0x001
#define AUD_HDR              0x002
#define AUD_PRM              0x004
#define AUD_RES              0x008
#define AUD_HPR              (AUD_HDR|AUD_PRM|AUD_RES)
#define AUD_VHPR             (AUD_VNO|AUD_HDR|AUD_PRM|AUD_RES)
#define AUD_FLU              0x010
#define AUD_PTR              0x020
#define AUD_LCL              0x040
#define AUD_LCK              0x080
#define AUD_GEN              0x100


/* misc values used in building audit records */
#define SIZ_TOKEN            1
#define AUD_RECTAIL          (3*SIZ_TOKEN + 2*sizeof(int) + sizeof(long))
/* base size for audit data buffer */
#define AUD_MINBUF_SIZ (AUD_BUF_SIZ<<2)
#define AUDSIZE(x) \
    ( ((x)*1024) < AUD_MINBUF_SIZ ? AUD_MINBUF_SIZ : ((x)*1024) )

/* global data */
extern u_int syscallauditmask[];
extern u_int trustedauditmask[];
extern u_int *siteauditmask;
extern int   n_sitevents;
extern u_int audswitch;
extern u_int audsize;
extern u_int audstyle;
extern struct aud_log aud_log;

extern u_long audit_rec_build();


/* audit statistics */
#define AUD_STAT_COLLECT 1
#if AUD_STAT_COLLECT
struct aud_stats {              /* vague audit subsystem stats          */
    u_long aud_records;         /* # audit records built                */
    u_long aud_sleep;           /* # sleeps against resource set        */
    u_long aud_flush1;          /* # writes into audit driver buffer    */
    u_long aud_flush2;          /* # AUD_FLU writes into driver buffer  */
    u_long aud_overflow1;       /* # overflow hndlr calls for syscalls  */
    u_long aud_overflow2;       /* # overflow hndlr calls for audgen()  */
    u_long aud_deselect;        /* # events deselected                  */
    u_long aud_suspendpriv;     /* # events bypassed due to privilege   */
#if SEC_MAC
    u_long aud_maclevel;        /* # events bypassed due to mac level   */
#endif /* SEC_MAC */
    u_long n_read;              /* # device reads                       */
    u_long n_getn;              /* # AUDIOCGETN operations              */
    u_long n_setn;              /* # AUDIOCSETN operations              */
    u_long n_sel;               /* # selects operations returning data  */
    u_long n_sleep;             /* # sleeps against audit driver        */
    u_long n_getpropl_call;     /* # VOP_GETPROPLIST calls for audit    */
    u_long n_getpropl_err;      /* # VOP_GETPROPLIST errors             */
    u_long n_setpropl_call;     /* # VOP_{SET,DEL}PROPLIST calls        */
};
#define AUD_STAT(field) aud_stats.field++

#else
#define AUD_STAT(field)

#endif /* AUD_STAT_COLLECT */

/*
  encodings for sysent[].aud_param
  (cap designation indicates security level must be recorded)
    0:   nothing
    2:   mode_t
    3:   long
    4:   *int (user-space)
    5:   int[], length in prev param (user-space)
    6:   privvec_t
    7:   label (ir)
    8:   record continuation marker
    a/A: int
    b/B: *char (user-space)
    c/C: fd
    d/D: data, length in next param (user-space)
    g/G: string, length in next param (user-space)
    h/H: struct sockaddr *addr, length in next param (user-space)
    i/I: struct msghdr *msg (4.3) (user-space)
    k/K: msgctl operations (user-space)
    l/L: uid_t
    m/M: gid_t
    n/N: semctl operations (similar to msgctl operations)
    o/O: shmctl operations (similar to msgctl operations)
    p/P: dev_t
    q/Q: pid_t
    r/R: *char (kernel-space)
    s/S: fd[2] (for socketpair) (user-space)
    t/T: struct msghdr *msg (4.4) (user-space)
    v/V: exportfs operation (user-space)
    w/W: *char (user-space)
            with inode info taken from retval (use only for object creat)
    x/X: *char (user-space)
            with add'l namei to get vnode info (use only for object creat)

  last field in sysent[].aud_param entry (entries may be combined):
    1:   apply audit object selection/deselection model
            (must be same value as FREAD)
    2:   audit despite selection model
    4:   perform audit from system call's code
*/

#define AUD_OVERRIDE_OBJ_SEL     2
#define SELF_AUDIT              '4'


#if MLS_AUDIT
#define AUDIT_ENABLED (audswitch == 1)
#endif /* MLS_AUDIT */

#endif /* KERNEL */


#if !(defined(KERNEL) || defined(_KERNEL))

extern char *syscallnames[];
extern char *trustedevent[];

#ifdef _NO_PROTO

extern int audit_change_mask();
extern int audit_build_mask();
extern void audit_change_mask_done();
extern int aud_aliasent();
extern int aud_alias_event();
extern int aud_sitevent();
extern int aud_sitevent_num();

#else /* !_NO_PROTO */

#if defined(__STDC__) || defined(__cplusplus)
#ifdef __cplusplus
extern "C"
{
#endif

extern int audit_change_mask(char const * , char * , char * , char * , int , char * , int );
extern int audit_build_mask(char const * , char * , char * , int );
extern void audit_change_mask_done(void);
extern int aud_aliasent(int , char * , int );
extern int aud_alias_event(char const * , int , char * , int );
extern int aud_sitevent(int , int , char * , char * );
extern int aud_sitevent_num( char const * , char const * , int * , int * );

#ifdef __cplusplus
}
#endif
#endif /* __STDC__ || __cplusplus */

#endif /* !_NO_PROTO */

#endif /* !(defined(KERNEL) || defined(_KERNEL)) */
#endif /* __AUDIT__ */
