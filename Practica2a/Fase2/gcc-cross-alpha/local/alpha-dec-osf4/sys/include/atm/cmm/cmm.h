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
 * @(#)$RCSfile: cmm.h,v $ $Revision: 1.1.38.3 $ (DEC) $Date: 1998/10/13 19:27:19 $
 */

#ifndef _ATM_CMM_H_
#define _ATM_CMM_H_

/* include the OS specific include file here (it should include all needed
 * OS specific includes as well as define internal OS specific stuff).
 */

#define ATM_HIDE_STEEL_DEPENDENCIES 1	/* Hide code with dependencies on
					 * Digital UNIX V5.x stream */

#include <kern/thread.h>
#include <atm/cmm/cmm_osf.h>

/* general ATM includes */
#include <atm/sys/atm_osf.h>
#include <atm/sys/atm.h>
#include <atm/sys/atm_adi.h>
#include <atm/sys/atm_cmi.h>
#include <atm/sys/atm_smi.h>
#include <sys/atm.h>
#include <atm/cmm/cmm_ioctl.h>

extern task_t first_task;
extern int resvtimeo;
extern int cmmdebug;

/*
 * For debugging and tracing, each module should define the following symbols
 * before including this header:
 *
 * DEBUG - debugging code is desired in this module.
 * DEBUG_FACILITY - name of the facility that this module belongs to
 */

#define DEBUG				/* GLG - turn it on *everywhere* */

#ifdef DEBUG
#define CMM_DEBUG1(flags,x) if((cmmdebug & (flags)) && \
				(cmmdebug & DEBUG_FACILITY)) printf##x
#else
#define CMM_DEBUG1(flags,x)
#endif
#define CMM_DEBUG(flags,x) CMM_DEBUG1(flags,x)

#ifdef DEBUG
#define CMM_SANITY_CHECK1(s) if((cmmdebug & ENDBG_SANITY) && \
			       (cmmdebug & DEBUG_FACILITY)) s
#else
#define CMM_SANITY_CHECK1(s)
#endif
#define CMM_SANITY_CHECK(s) CMM_SANITY_CHECK1(s)

/* Classes of events to debug */
#define ENDBG_TRACE	 0x1		/* Routine entries */
#define ENDBG_INFO	 0x2		/* Misc. informational messages */
#define ENDBG_USECNT	 0x4		/* Incr/decr of structure usecounts */
#define ENDBG_CALLSTATE  0x8		/* Changes of vc and endpoint state */
#define ENDBG_RESOURCE	0x10		/* Changes of vc resources */
#define ENDBG_SANITY	0x20		/* Enable major sanity checking */
#define ENDBG_ALL	0x3f

/* CMM components to debug */
#define DBGFAC_SMI	 0x10000	/* Interface with signaling module */
#define DBGFAC_CMI	 0x20000	/* Interface with convergence module */
#define DBGFAC_PPA	 0x40000	/* PPA related routines */
#define DBGFAC_DRIVER	 0x80000	/* Driver related routines */
#define DBGFAC_ESI	0x100000	/* ESI related routines */
#define DBGFAC_CMM	0x200000	/* CMM internal processing */
#define DBGFAC_MANAGE	0x400000	/* CMM management interface */
#define DBGFAC_ALL	0x7f0000

/*
 * Macro to replace a routine call with a simulated failure return.
 * Note don't add a trailing ';'
 */
#ifdef DEBUG
extern unsigned long cmmfail;

#define SIMULATE_FAILURE(NAME,MASK,VAR,CAUSE) \
	if(cmmfail & (MASK)) {\
	CMM_DEBUG(ENDBG_INFO,("%s: Simulated failure: mask=0x%lx\n",NAME,MASK)); \
		VAR = (CAUSE); \
	} else
#else
#define SIMULATE_FAILURE(NAME,MASK,VAR,CAUSE)
#endif

/*
 * Wrappers for ATM_MSG_xxxx macros with CMM's message level
 */
extern atm_msglevel_t atm_cmm_msglevel;

extern int cmm_autoload_modules;

#define CMM_MSG_NORMAL(x) ATM_MSG_NORMAL(atm_cmm_msglevel, x)
#define CMM_MSG_INFO(x) ATM_MSG_INFO(atm_cmm_msglevel, x)
#define CMM_MSG_VERBOSE(x) ATM_MSG_VERBOSE(atm_cmm_msglevel, x)

/**************************************************************************
 *		INTERNAL CMM STRUCTURES				          *
 **************************************************************************/

/* structure to reference structures from multiple linked lists */
typedef struct atm_cmm_list atm_cmm_list_t;
typedef struct atm_cmm_list *atm_cmm_list_p;
typedef struct atm_cmm_list_entry atm_cmm_list_entry_t;
typedef struct atm_cmm_list_entry *atm_cmm_list_entry_p;

struct atm_cmm_list {
	atm_cmm_list_entry_p	head;
	atm_cmm_list_entry_p	tail;
	int			ll;	/* list length */
	atm_cmm_lock_decl(list_lock)
};

struct atm_cmm_list_entry {
	atm_cmm_list_entry_p	next;
	atm_cmm_list_entry_p	prev;
	atm_cmm_list_p		lp;
};

#define atm_cmm_list_first(L)	((void *)((L)->head))
#define atm_cmm_list_last(L)	((void *)((L)->tail))
#define atm_cmm_list_length(L)	((L)->ll)
#define atm_cmm_list_next(L,W)	((void *)((((atm_cmm_list_entry_p)L) + W)->next))
#define atm_cmm_list_prev(L,W)	((void *)((((atm_cmm_list_entry_p)L) + W)->prev))
#define atm_cmm_list_islinked(L,W) (((((atm_cmm_list_entry_p)L) + W)->lp) ? 1 : 0)
#define atm_cmm_list_islinkedto(L,W,L1) ((((((atm_cmm_list_entry_p)L) + W)->lp) == (L1)) ? 1 : 0)
#define atm_cmm_list_lock(L)	atm_lock(&((L)->list_lock))
#define atm_cmm_list_unlock(L)	atm_unlock(&((L)->list_lock))
#define atm_cmm_list_terminate(L) atm_lock_terminate(&((L)->list_lock))
#define atm_cmm_list_make(N)	atm_cmm_list_entry_t	link[N]

void atm_cmm_list__add(atm_cmm_list_p,atm_cmm_list_entry_p,int, int);
void atm_cmm_list__insert(atm_cmm_list_p,atm_cmm_list_entry_p,
			  atm_cmm_list_entry_p, int, int);
void atm_cmm_list__remove(atm_cmm_list_entry_p,int, int);
void *atm_cmm_list__get(atm_cmm_list_p,int, int);

#define atm_cmm_list_add(L,E,W) \
		atm_cmm_list__add(L,(atm_cmm_list_entry_p)(E),W,0)
#define atm_cmm_list_insert(L,E,E1,W) \
		atm_cmm_list__insert(L,(atm_cmm_list_entry_p)(E),\
				     (atm_cmm_list_entry_p)(E1),W,0)
#define atm_cmm_list_remove(E,W) \
		atm_cmm_list__remove((atm_cmm_list_entry_p)(E),W,0)
#define atm_cmm_list_get(L,W) \
		atm_cmm_list__get((L),W,0)

#define atm_cmm_list_add_nolock(L,E,W) \
		atm_cmm_list__add(L,(atm_cmm_list_entry_p)(E),W,1)
#define atm_cmm_list_insert_nolock(L,E,E1,W) \
		atm_cmm_list__insert(L,(atm_cmm_list_entry_p)(E),\
				     (atm_cmm_list_entry_p)(E1),W,1)
#define atm_cmm_list_remove_nolock(E,W) \
		atm_cmm_list__remove((atm_cmm_list_entry_p)(E),W,1)
#define atm_cmm_list_get_nolock(L,W) \
		atm_cmm_list__get((L),W,1)

typedef struct atm_cmm_device atm_cmm_device_t;
typedef struct atm_cmm_device *atm_cmm_device_p;

typedef struct atm_cmm_signal atm_cmm_signal_t;
typedef struct atm_cmm_signal *atm_cmm_signal_p;

typedef struct atm_cmm_converge atm_cmm_converge_t;
typedef struct atm_cmm_converge *atm_cmm_converge_p;

typedef struct atm_cmm_vc atm_cmm_vc_t;
typedef struct atm_cmm_vc *atm_cmm_vc_p;

typedef struct atm_cmm_vcs atm_cmm_vcs_t;
typedef struct atm_cmm_vcs *atm_cmm_vcs_p;

typedef struct atm_cmm_addr atm_cmm_addr_t;
typedef struct atm_cmm_addr *atm_cmm_addr_p;

typedef struct atm_cmm_bind atm_cmm_bind_t;
typedef struct atm_cmm_bind *atm_cmm_bind_p;

typedef struct atm_cmm_ppa atm_cmm_ppa_t;
typedef struct atm_cmm_ppa *atm_cmm_ppa_p;

typedef struct atm_cmm_esi atm_cmm_esi_t;
typedef struct atm_cmm_esi *atm_cmm_esi_p;

typedef struct atm_cmm_log_info atm_cmm_log_info_t;
typedef struct atm_cmm_log_info *atm_cmm_log_info_p;

typedef struct atm_cmm_mib_var atm_cmm_mib_var_t;
typedef struct atm_cmm_mib_var *atm_cmm_mib_var_p;

/* Internal PPA structure.  Used to keep track of all PPA related activity. */

struct atm_cmm_ppa {
	atm_cmm_list_make(3);
#define ATM_CMM_PPAL_LIST	0
#define ATM_CMM_PPAL_SIG	1
#define ATM_CMM_PPAL_DRV	2
	atm_ppa_t	ppa;
	unsigned int	state;		/* the state of the PPA */
#define ATM_PPA_PVC	1		/* it's a PVC PPA */
#define ATM_PPA_ACTIVE	2		/* PPA is active */
#define ATM_PPA_ZOMBIE	4		/* On the zombie list */
#define ATM_PPA_DEAD	8		/* PPA no longer needed */

	unsigned int	ppa_id;		/* unique ID of PPA */
	unsigned int	zt;		/* zombie timer */
	int	usecount;		/* number of references */
	atm_cmm_list_t	binds;		/* convergence modules bound to PPA */
	atm_cmm_list_t	dbinds;		/* dead binds */
	atm_cmm_esi_p	esi;		/* ESI for this PPA */
	unsigned long	bindmask[4];	/* bit mask of used selectors */
	atm_cmm_lock_decl(atm_cmm_ppa_lock)
};

#define ATM_CMM_BIND_SET(P,V) (P)->bindmask[(V)/64] |= (1L<<((V)&0x3f))
#define ATM_CMM_BIND_CLEAR(P,V) (P)->bindmask[(V)/64] &= ~(1L<<((V)&0x3f))
#define ATM_CMM_BIND_USED(P,V) ((P)->bindmask[(V)/64] & (1L<<((V)&0x3f)))

#define PPA2CMMPPA(A)	(atm_cmm_ppa_p)( ((A) == NULL) ? NULL : \
	    ((char *)(A) - (char *)(&((atm_cmm_ppa_p)0)->ppa)) )

/*
 * PPA, bind, and ESI zombie timers must be longer than the VC zombie timer,
 * because VC's on the zombie list may still reference a PPA, bind, or ESI.
 * The alternative is to return less information when listing zombies
 * through the MMI interface.
 */
#define ATM_PPA_ZOMBIE_TIME		45

/* Macros to maintain PPA usecounts */
/* Increment PPA usecount */
#define PPA_USE(P,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((P)->atm_cmm_ppa_lock)); \
		     (P)->usecount++; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: use on PPA 0x%lx: now %d\n",\
				(T), (P), (P)->usecount));\
		     atm_cmm_unlock(tmppri,&((P)->atm_cmm_ppa_lock));\
	     }
/* Ditto when PPA is already locked or doesn't need locking */
#define PPA_USE_NOLOCK(P,T) { \
		     (P)->usecount++; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: use on PPA 0x%lx: now %d\n",\
				(T), (P), (P)->usecount));\
	     }

/* Decrement usecount and check if the PPA should be zombiefied */
#define PPA_UNUSE(P,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((P)->atm_cmm_ppa_lock)); \
		     (P)->usecount--; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: unuse on PPA 0x%lx: now %d\n",\
				(T), (P), (P)->usecount));\
		     atm_cmm_unlock(tmppri,&((P)->atm_cmm_ppa_lock));\
		     if((P)->usecount == 0)(void)atm_cmm_zombiefy_ppa((P));\
	     }


/* Structure used to keep track of device drivers */

#define ATM_CMM_REFERENCE_BUCKETS       128
#define ATM_CMM_REFERENCE_BUCKET(D,R) \
	&((D)->vchash[((R) & (ATM_CMM_REFERENCE_BUCKETS - 1))])

struct atm_cmm_device {
	atm_cmm_list_make(1);
#define ATM_CMM_DEVICE_L	0
	unsigned long		version;	/* driver's version */
	atm_drv_params_p	params;		/* driver's params */
	atm_services_granes_p	maxres;		/* max resources available */
	atm_services_granes_p	availres;	/* current resources available*/
	atm_error_t (*xmit_func)(int unit,
			struct mbuf *data,
			long length,
			atm_vc_p vc,
			unsigned char clp,
			unsigned char gfc);
	atm_error_t (*manage_func)(int unit,
			unsigned int command,
			void *arg);
	int (*mmi_func)(int unit,
			unsigned int command,
			void *arg,
			int *retval,
			struct ucred *cred);

	unsigned long		use_esi;	/* bitmask of ESIs to use */
	int			state;		/* driver state */
	int			num_vc;		/* number of VCs allocated */
	int			device_id;	/* driver ID */
	atm_cmm_list_t		vcs;		/* vcs attatched to driver */
	atm_cmm_list_t		ppas;		/* SVC PPAs attached to driver */
	atm_cmm_list_t		esis;		/* all esi's for this driver */
	atm_cmm_ppa_t		pvcppa;		/* driver's PVC ppa */
	atm_vc_stats_t		pdu_stats;	/* PDU statistics */

	/* hash buckets for hashing call reference to VC */
	atm_cmm_list_t		vchash[ATM_CMM_REFERENCE_BUCKETS];

	/* logging related stuff */
	int			max_log;	/* maximum # of causes/logs on
						 * a VC. Used by MMI vclist. */

	/* Reserved Resource information */
	int			fresvlimit;     /* %fwd bw avail to reserve*/
	int			bresvlimit;     /* %back bw avail to reserve*/
	atm_cmm_list_t		resvreqp;	/* reservation requests */
	atm_cmm_list_t		unusedp;	/* unused allocated resources */

	atm_bw_granularity_t	allocation;	/* driver allocation gran. */
	atm_bw_granularity_t	limit;		/* driver allocation limit */
        int                     fvcmaxbw;       /* config'd fwd alloc limit */
        int                     bvcmaxbw;       /* config'd back alloc limit */

	/* Callback to receive private data on the ILMI VC, as needed for
	 * supporting Flowmaster flow control.
	 */
	int (*escape_func)(unsigned long arg,
			      struct mbuf *m);
	unsigned long escape_arg;
	unsigned char escape_char;

	atm_cmm_lock_decl(atm_cmm_device_lock)
	/* the name array MUST be the last member in the structure */
	int			namelen;
	char			name[1];	/* drivers name */
};

/* state bits for above */
#define ATM_CMM_DRIVER_UP	1
#define ATM_CMM_DRIVER_OOS	2		/* taken out of service */
#define ATM_CMM_DRIVER_DOWN	4		/* driver going down */
#define ATM_CMM_FC_STANDARD	8		/* standard FC enabled */
#define ATM_CMM_FC_VENDOR	0x10		/* vendor FC enabled */
#define ATM_CMM_SDH		0x20		/* SDH mode */
#define ATM_CMM_DRIVER_NOESI	0x40		/* Don't register ESI's yet */

#define ATM_CMM_DRIVER_FCON	(ATM_CMM_FC_STANDARD|ATM_CMM_FC_VENDOR)


/* structure used for keeping track of signalling modules */

struct atm_cmm_signal {
	atm_cmm_list_make(1);
#define ATM_CMM_SIGNAL_L	0
	unsigned long           version;        /* driver's version */
	void			*sig_handle;	/* module's internal handle */
	atm_error_t (*sig_setup)(atm_addr_p addr,unsigned long *refptr);
	atm_error_t (*sig_release)(atm_addr_p addr);
	atm_error_t (*sig_add)(atm_addr_p addr);
	atm_error_t (*sig_drop)(atm_addr_p addr);
	atm_error_t (*sig_enquery)(atm_addr_p addr);
	atm_error_t (*sig_restart)(void *handle,
		unsigned int class,
		unsigned int vpi,
		unsigned int vci);
	atm_error_t (*sig_exception)(void *sig_handle,
		unsigned int exception,
		void *arg);
	int (*sig_mmi)(void *sig_handle,
		int command,
		void *arg,
		int *retval,
		struct ucred *cred);
	atm_error_t (*sig_mib)(void *sig_handle,
		atm_ppa_p       ppa,
		atm_mib_request_t command,
		atm_mib_var_p   request);

	atm_cmm_list_t		vcs;		/* vcs using this protocol */
	atm_cmm_list_t		ppas;		/* PPAs using this protocol */

	atm_call_stats_t	call_stats;	/* Call Statistics */

	int			usecount;	/* lock out deletions */

	atm_cmm_lock_decl(atm_cmm_sig_lock)
	/* the name array MUST be the last member in the structure */
	int			namelen;
	char			id[1];	/* drivers name */
};

/* structure used to keep track of convergence modules */

struct atm_cmm_converge {
	atm_cmm_list_make(1);
#define ATM_CMM_LIST_CL	0		/* list of convergence modules */

	unsigned long           version;        /* module's version */
	void			*handle;	/* module's internal handle */
	int			flags;
#define ATM_CMM_CVG_DEAD	0x1		/* Has been unregistered */

        void (*receive)(atm_vc_p vc,
                        struct mbuf *mbp,
                        int length,
                        struct mbuf *trailer,
                        char      pti,
                        char gfc);
        atm_error_t (*exception)(void *cvg_handle,
			int command,
                        void *arg);
	int (*mmi_manage)(void *cvg_handle,
			int cmd,
			void *arg,
			int *retval,
			struct ucred *cred);
        void (*endpt_receive)(atm_vc_p vc,
                        struct mbuf *mbp,
                        int length,
                        struct mbuf *trailer,
                        char      pti,
                        char gfc,
			atm_addr_p addr);

	atm_cmm_list_t	vcs;			/* VCs in use by module */
	atm_cmm_list_t	esis;			/* ESIs owned by module */
	atm_cmm_list_t	binds;			/* bindings for this module */

	atm_vc_stats_t	pdu_stats;		/* PDU statistics */
	atm_call_stats_t call_stats;		/* Call Statistics */

	int		usecount;		/* currently in use */
	int		linkage_count;		/* Count of other modules
						 * which have linked to us. */

	atm_cmm_lock_decl(atm_cmm_cvg_lock)
	/* the name array MUST be the last member in the structure */
	int			namelen;
	char			name[1];	/* module's name */
};

/* Macros to maintain convergence module usecounts */
/* Increment convergence module usecount */
#define CVG_USE(C,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((C)->atm_cmm_cvg_lock)); \
		     (C)->usecount++; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: use on CVG 0x%lx: now %d\n",\
				(T), (C), (C)->usecount));\
		     atm_cmm_unlock(tmppri,&((C)->atm_cmm_cvg_lock));\
	     }

/* Decrement usecount and check if the structure can be freed */
#define CVG_UNUSE(C,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((C)->atm_cmm_cvg_lock)); \
		     (C)->usecount--; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: unuse on CVG 0x%lx: now %d\n",\
				(T), (C), (C)->usecount));\
		     atm_cmm_unlock(tmppri,&((C)->atm_cmm_cvg_lock));\
		     if((C)->usecount == 0)atm_cmm_free_cvg((C));\
	     }


/* internal structure used by CMM to keep track of VCs */

struct atm_cmm_vc {
	atm_cmm_list_make(8);
#define ATM_CMM_LIST_VCC	0		/* convergence VCs */
#define ATM_CMM_LIST_VCB	1		/* BIND list */
#define ATM_CMM_LIST_VCD	2		/* driver list */
#define ATM_CMM_LIST_ZOM	3		/* zombie VC list */
#define ATM_CMM_LIST_VCR	4		/* call reference hash */
#define ATM_CMM_LIST_VSG	5		/* signalling list */
#define ATM_CMM_LIST_VSQ	6		/* VC start Q list */
#define ATM_CMM_LIST_AGE	7		/* VC aging list */

/* Some state info. Don't change ACTIVE and ZOMBIE since atmconfig uses them */
	unsigned long		flags;
#define ATM_CMM_VC_ACTIVE	1		/* VC is active */
#define ATM_CMM_VC_ZOMBIE	2		/* VC is on the zombie list */
#define ATM_CMM_VC_DEAD		4		/* All ep's are con_deleted */
#define ATM_CMM_VC_RELEASING	8		/* VC release in progress */
#define ATM_CMM_VC_RI_RCVD	0x10		/* VC Release Indication rcvd*/
#define ATM_CMM_VC_AGE_BUSY	0x20		/* Can't change aging param */
#define ATM_CMM_VC_NEW_AGE	0x40		/* New aging value pending */

#define ATM_CMM_VC_NOXMIT	0x100		/* don't send data */
#define ATM_CMM_VC_ON_DRIVER	0x200		/* VC was ADDVC'ed to driver */
#define ATM_CMM_VC_STOPPED	0x400		/* VC flow controlled */

#define ATM_CMM_VC_DBG_DEAD	0x1000		/* fake the VC as dead */
	atm_vc_t		vc;		/* the VC structure */
	atm_cmm_list_t		eps;		/* active endpoint list */
	atm_cmm_list_t		ieps;		/* incoming endpoint list */
	atm_cmm_list_t		ceps;		/* connecting endpoint list */
	atm_cmm_list_t		deps;		/* disconnected endpoint list */
	atm_cmm_list_t		neps;		/* null endpoint list */
	int			usecount;	/* Number of references */
	atm_queue_param_t	qp;
	atm_cmm_converge_p	cm;		/* convergence modules
						   that own VC */
	atm_cmm_bind_p		bind;		/* bind for VC */
	atm_vc_services_p	svcsignalled;   /* For incoming VC, original
						 * svcs requested by sig. */
	unsigned long		vcid;		/* system VC Identifier */
	unsigned int		aging;		/* aging parameter */
	unsigned int		new_aging;	/* Pending aging parameter */
	unsigned int		ageout_time;	/* VC aging timer */
	unsigned int		zt;		/* zombie timer */

	/* logging and cause information */
	atm_cmm_list_t		causes;		/* cause information */
	atm_cmm_list_t		log;		/* logging information */
	atm_cmm_log_info_p	dcause;		/* default cause */

	atm_cmm_lock_decl(atm_cmm_vc_lock)	/* lock the VC struct */
	atm_vc_stats_p		stats[1];	/* Pointers to VC statistics */
};

#define VC2CMMVC(V)	(atm_cmm_vc_p)( ((V) == NULL) ? NULL : \
			   ((char *)(V) - (char *)(&((atm_cmm_vc_p)0)->vc)) )

/* Macros to maintain VC usecounts */
/* Increment VC usecount */
#define VC_USE(V,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((V)->atm_cmm_vc_lock)); \
		     (V)->usecount++; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: use on VC 0x%lx: now %d\n",\
				(T), (V), (V)->usecount));\
		     atm_cmm_unlock(tmppri,&((V)->atm_cmm_vc_lock));\
	     }
			
/* Increment VC usecount when the VC is already locked or lock is not needed */
#define VC_USE_NOLOCK(V,T) { \
			    (V)->usecount++; \
			    CMM_DEBUG(ENDBG_USECNT,\
				      ("%s: use on VC 0x%lx: now %d\n",\
				       (T), (V), (V)->usecount));\
	     }

/* Decrement usecount and check if the VC should be zombiefied */
#define VC_UNUSE(V,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((V)->atm_cmm_vc_lock)); \
		     (V)->usecount--; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: unuse on VC 0x%lx: now %d\n",\
				(T), (V), (V)->usecount));\
		     atm_cmm_unlock(tmppri,&((V)->atm_cmm_vc_lock));\
		     if((V)->usecount == 0)(void)atm_cmm_zombiefy_vc((V));\
	     }

/* Ditto, when the VC doesn't need to be locked */
#define VC_UNUSE_NOLOCK(V,T) {\
		     (V)->usecount--; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: unuse on VC 0x%lx: now %d\n",\
				(T), (V), (V)->usecount));\
		     if((V)->usecount == 0)(void)atm_cmm_zombiefy_vc((V));\
	     }

/* Decrement usecount when the VC is already locked.  Unlocks the VC
 * before checking to zombiefy. */

#define VC_UNUSE_UNLOCK(V,T,S) {\
		     (V)->usecount--; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: unuse on VC 0x%lx: now %d\n",\
				(T), (V), (V)->usecount));\
		     atm_cmm_unlock((S),&((V)->atm_cmm_vc_lock));\
		     if((V)->usecount == 0)(void)atm_cmm_zombiefy_vc((V));\
	     }

#define ATM_VC_ZOMBIE_TIME	30	/* 30 second zombie timeout */

/* Internal structure used by CMM to keep track of VC Services */

struct atm_cmm_vcs {
	atm_cmm_list_make(2);
#define ATM_CMM_LIST_RESVREQ	0		/* resource resv requested */
#define ATM_CMM_LIST_RESVUNUSED	1		/* unused reserved resources */
	unsigned int		flags;		/* resource reservation state */
#define ATM_CMM_VCS_NOTRESV	1		/* no resources reserved */
#define ATM_CMM_VCS_RESVREQ	2		/* reservation requested  */
#define ATM_CMM_VCS_RESVUNUSED	4		/* resource allocated, unused */
#define ATM_CMM_VCS_RESVTIMEO	8   		/* unused resource timed out */
#define ATM_CMM_VCS_RESVALLOC	0x10		/* resource allocated, inuse */
#define ATM_CMM_VCS_RELEASE	0x20		/* VCServices release pending */
	long 			rtimer;		/* to timeout unused resources*/
	atm_vc_services_t	vcs;		/* the VC services structure */
	atm_services_granes_t   ratesalloc;	/* VC services rates alloc'd */
	atm_cmm_converge_p      cvg;             /* convergence module that gave
						 * the CMM this struct */
	atm_cmm_lock_decl(atm_cmm_vcs_lock)	/* lock VC services struct */
};

#define VCS2CMMVCS(V)	(atm_cmm_vcs_p)( ((V) == NULL) ? NULL : \
			((char *)(V) - (char *)(&((atm_cmm_vcs_p)0)->vcs)) )

#define ATM_VCS_ZOMBIE_TIME	ATM_VC_ZOMBIE_TIME

/* endpoint information structure */
struct atm_cmm_addr {
	atm_cmm_list_make(2);
#define ATM_CMM_LIST_ADDR	0
#define ATM_CMM_LIST_RELEASING	1
	atm_addr_t		addr;
	int			flags;
#define ATM_CMM_ADDR_CSYNC	1		/* cause info synced */
	int			usecount;	/* Number of references */

						/* Uses ATM_CMM_EPS_xxx  */
	unsigned int		start_st;	/* Starting state for current
						 * sequence of state changes */
	unsigned int		current_st;	/* Current endpoint state */
	unsigned int		target_st;	/* Target endpoint state */
	unsigned int		progressing;	/* State change in progress */
	atm_cmm_addr_p		saved_next_active;/* Help for atm_cmm_receive*/
	unsigned int		zt;		/* zombie timer */

	atm_cmm_lock_decl(atm_cmm_addr_lock)    /* lock for addr struct */
};

#define ADDR2CMMADDR(A)	(atm_cmm_addr_p)( ((A) == NULL) ? NULL : \
			 ((char *)(A) - (char *)(&((atm_cmm_addr_p)0)->addr)) )

#define ATM_ADDR_ZOMBIE_TIME	ATM_VC_ZOMBIE_TIME

/*
 * Endpoint states used in the start_st, current_st, and target_st fields.
 * These are a subset of the ATM Forum states (ATM_EPF_xxx values),
 * with a different encoding to simplify the state machine.
 * The ordering of these entries is signifcant, as transitions are always
 * to a higher numbered state.
 */
#define ATM_CMM_EPS_NULL	0		/* null state */
#define ATM_CMM_EPS_CI		1		/* call initiated (U1) */
#define ATM_CMM_EPS_ICP		2		/* call proceeding (U9) */
#define ATM_CMM_EPS_API		3		/* add initiated */
#define ATM_CMM_EPS_APR		4		/* add party received */
#define ATM_CMM_EPS_ACTIVE	5		/* active (U10) */
#define ATM_CMM_EPS_DPI		6		/* drop party initiated */
#define ATM_CMM_EPS_DPR		7		/* drop part received */
#define ATM_CMM_EPS_RR		8		/* release request (U11) */
#define ATM_CMM_EPS_RI		9		/* release indication (U12) */
#define ATM_CMM_EPS_RESTARTR	10		/* restart request (rest1) */
#define ATM_CMM_EPS_RESTART	11		/* restart (rest2) */
#define ATM_CMM_EPS_FINAL	12		/* done with the endpoint */


/* Internal cause and logging information tracking structure.*/

struct atm_cmm_log_info {
	atm_cmm_list_make(1);
#define ATM_CMM_LIST_CAUSE	0
	int			flags;
#define ATM_LOG_INFO_LOG	1
#define ATM_LOC_INFO_CAUSE	2
	atm_cmm_addr_p		addr;
	atm_cmm_vc_p		vc;
	struct timeval		when;
	atm_cause_info_t 	cause;
};

#define ATM_CAUSE_NEXT		0
#define ATM_CAUSE_FIRST		1
#define ATM_CAUSE_DEFAULT	2

#define LOG2CMMLOG(A)	(atm_cmm_log_info_p)( ((A) == NULL) ? NULL : \
		 ((char *)(A) - (char *)(&((atm_cmm_log_info_p)0)->cause)) )

/* Internal ESI structure used to keep track of all ESI's on the system on
 * a per-driver basis.
 *
 * Locking isn't needed here since the contents of the structure are
 * never changed after it's created.
 *
 * ESIs are cloned before they're passed to signalling modules for 
 * registration.  This is because multiple signalling modules can register
 * (and this reference) an ESI.  A list of clones is maintained and all
 * clones are removed before the parent is removed.
 */
struct atm_cmm_esi {
	atm_cmm_list_make(2);
#define ATM_CMM_ESIL_DRV        0
#define ATM_CMM_ESIL_CLN        0
#define ATM_CMM_ESIL_ZOM        0
#define ATM_CMM_ESIL_CVG	1
	atm_esi_t		esi;
	unsigned int		esi_id;		/* unique id for ESI */
	atm_cmm_converge_p	cm;
	atm_cmm_signal_p	sm;
	int			usecount;
	unsigned int		zt;		/* zombie timer */
	int			flags;
	atm_cmm_list_t		clones;		/* clone list */
	atm_cmm_esi_p		parent;		/* parent of clones */
	void *			arg;		/* owners arg for private */
	atm_cmm_lock_decl(atm_cmm_esi_lock)
};

/* ESI flags */
#define ATM_ESI_DEAD	1		/* ESI no longer needed */
#define ATM_ESI_PRIVATE	2		/* Owned by a convergence module */
#define ATM_ESI_NOCLONE	4		/* Clone not made yet */
#define ATM_ESI_ZOMBIE  8		/* ESI has been zombified */

#define ESI2CMMESI(A)	(atm_cmm_esi_p)( ((A) == NULL) ? NULL : \
			((char *)(A) - (char *)(&((atm_cmm_esi_p)0)->esi)) )

/* Macros to maintain ESI usecounts */
/* Increment ESI usecount. */
#define ESI_USE(E,T)	{int tmppri; \
			 atm_cmm_lock(tmppri,&((E)->atm_cmm_esi_lock)); \
			 (E)->usecount++; \
			 CMM_DEBUG(ENDBG_USECNT,\
				  ("%s: use on ESI 0x%lx: now %d\n",\
				   (T), (E), (E)->usecount)); \
			 atm_cmm_unlock(tmppri,&((E)->atm_cmm_esi_lock)); \
			 }

/* Ditto, when the ESI is already locked or doesn't need locking */
#define ESI_USE_NOLOCK(E,T) { \
			 (E)->usecount++; \
			 CMM_DEBUG(ENDBG_USECNT,\
				  ("%s: use on ESI 0x%lx: now %d\n",\
				   (T), (E), (E)->usecount)); \
			 }

/* Decrement usecount and check if the ESI should be zombiefied */
#define ESI_UNUSE(E,T) {int tmppri; \
			 atm_cmm_lock(tmppri,&((E)->atm_cmm_esi_lock)); \
			 ((E)->usecount)--; \
			 CMM_DEBUG(ENDBG_USECNT,\
				  ("%s: unuse on ESI 0x%lx: now %d\n",\
				   (T), (E), (E)->usecount)); \
			 atm_cmm_unlock(tmppri,&((E)->atm_cmm_esi_lock)); \
			 if((E)->usecount == 0)atm_cmm_zombiefy_esi((E)); \
			 }

#define ATM_ESI_ZOMBIE_TIME	45

/* Structre to record bindings of convergence modules to PPAs */

struct atm_cmm_bind {
	atm_cmm_list_make(3);
#define ATM_CMM_BINDL_PPA	0
#define ATM_CMM_BINDL_CVG	1
#define ATM_CMM_BINDL_ZOM	2
	atm_error_t (*connect)(void *bind_handle,
		atm_addr_p              addr,
		atm_bind_handle_t       bind,
		atm_vc_p                vc,
		atm_uni_call_ie_p	*reply,
		atm_vc_services_p       requested,
		atm_vc_services_p       *avail);	/* function to call */
	atm_cmm_converge_p		cm;		/* module owning bind */
	int				selector;	/* NSAP selector */
	unsigned int			flags;
#define ATM_CMM_BIND_DEAD	1		/* Bind no longer needed */
#define ATM_CMM_BIND_ZOMBIE	2		/* On zombie list */

	unsigned int			zt;		/* zombie timer */
	int				usecount;	/* references */
	unsigned int			bind_id;	/* global bind ID */
	void 				*bind_handle;	/* cookie for module */
	atm_cmm_ppa_p			ppa;		/* PPA of bind */
	atm_cmm_list_t			vcs;		/* VC's attached to bind */
	atm_cmm_lock_decl(atm_cmm_bind_lock)
};

#define ATM_BIND_ZOMBIE_TIME		45

/* Macros to maintain Bind usecounts */
/* Increment Bind usecount */
#define BIND_USE(B,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((B)->atm_cmm_bind_lock)); \
		     (B)->usecount++; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: use on bind 0x%lx: now %d\n",\
				(T), (B), (B)->usecount));\
		     atm_cmm_unlock(tmppri,&((B)->atm_cmm_bind_lock));\
	     }

/* Ditto, when the bind is already locked or a lock isn't needed */
#define BIND_USE_NOLOCK(B,T) { \
		     (B)->usecount++; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: use on bind 0x%lx: now %d\n",\
				(T), (B), (B)->usecount));\
	     }

/* Decrement usecount and check if the PPA should be zombiefied */
#define BIND_UNUSE(B,T) {int tmppri; \
		     atm_cmm_lock(tmppri,&((B)->atm_cmm_bind_lock)); \
		     (B)->usecount--; \
		     CMM_DEBUG(ENDBG_USECNT,\
			       ("%s: unuse on bind 0x%lx: now %d\n",\
				(T), (B), (B)->usecount));\
		     atm_cmm_unlock(tmppri,&((B)->atm_cmm_bind_lock));\
		     if((B)->usecount == 0)(void)atm_cmm_zombiefy_bind((B));\
	     }

/* Define a cap on the system reservation timeout (needed for sysconfig) */
#define ATM_CMM_RESV_TIMEO		30
#define ATM_CMM_RESV_MAXTIMEO		(100*ATM_CMM_RESV_TIMEO)

struct atm_cmm_mib_var {
	atm_cvg_handle_t	cvg_handle;	/* The callers module handle */
	void			*request_id;	/* The caller's request ID */
	void	(*callback)(atm_cvg_handle_t,	/* Pointer to callback rtn */
			    void *,
			    struct atm_mib_var *,
			    struct atm_mib_var *);
	atm_mib_var_t		mib_var;	/* The public structure */
};

#define MIBVAR2CMMMIBVAR(A)	(atm_cmm_mib_var_p)( ((A) == NULL) ? NULL : \
	    ((char *)(A) - (char *)(&((atm_cmm_mib_var_p)0)->mib_var)) )

/* function prototypes */
void atm_cmm_init(void);
atm_cmm_name_cmp(char *,char *);
void atm_cmm_list_init(atm_cmm_list_p,struct lockinfo *);
void atm_cmm_list_init_nolock(atm_cmm_list_p);
atm_cmm_vc_p atm_cmm_vc_alloc(void);
void atm_cmm_vc_free(atm_cmm_vc_p);
atm_vc_stats_p atm_cmm_alloc_vc_stats(atm_cmm_vc_p, int);

int atm_cmm_driver_config(int, int *, atm_ioctl_driver_name_p, int);
void atm_cmm_driver_report(atm_cmm_converge_p);
atm_cmm_bind_p atm_cmm_vc_bind(atm_cmm_ppa_p,
	atm_addr_p,
	atm_cmm_vc_p,
	atm_cmm_converge_p,
	atm_vc_services_p,
	atm_vc_services_p,
	atm_vc_services_p);
atm_cmm_bind_p atm_cmm_bind_find(atm_cmm_ppa_p, unsigned int);
atm_cmm_device_p atm_cmm_driver_find(char *);
atm_cmm_converge_p atm_cmm_converge_find(char *);
atm_error_t atm_cmm_zombiefy_vc(atm_cmm_vc_p);
void atm_cmm_reference_init(atm_cmm_device_p);
void atm_cmm_add_reference(atm_cmm_vc_p);
void atm_cmm_del_reference(atm_cmm_vc_p);
atm_cmm_vc_p atm_cmm_find_vc(unsigned long, atm_ppa_p);
void atm_cmm_driver_expire(atm_cmm_device_p);
void atm_cmm_driver_finish(atm_cmm_device_p);
atm_error_t atm_cmm_release_vc(atm_cmm_vc_p,int);
atm_error_t atm_cmm_drop_ep(atm_cmm_addr_p,int);
atm_error_t atm_cmm_add_vc_resources(atm_vc_services_p,atm_cmm_device_p);
void atm_cmm_remove_vc_resources(atm_vc_services_p, atm_cmm_device_p);
void atm_cmm_commit_vc_resources(atm_vc_services_p);
void atm_tcopy(char *, char *,int);
atm_cmm_signal_p atm_cmm_signal_find(char *);
atm_cmm_vc_p atm_cmm_vc_lookup(atm_cmm_device_p, int, int);
atm_drv_params_p atm_adi_params_convert(atm_drv_params_p, long);
atm_error_t atm_cmm_cause_set(atm_cmm_vc_p,
		  atm_cmm_addr_p,
		  char *,
		  char *,
		  atm_error_t,
		  atm_location_t,
		  unsigned char,
		  unsigned char *,
		  int);
atm_error_t atm_cmm_cause_sync(atm_cmm_vc_p, atm_cmm_log_info_p);
atm_error_t atm_cmm_log_set(atm_cmm_vc_p,
		  atm_cmm_addr_p,
		  char *,
		  char *,
		  atm_error_t,
		  atm_location_t,
		  unsigned char,
		  unsigned char *);
atm_cmm_log_info_p atm_cmm_cause_next(atm_cmm_vc_p, atm_cmm_addr_p,
		   atm_cmm_log_info_p);
atm_cmm_log_info_p atm_cmm_log_next(atm_cmm_vc_p, atm_cmm_addr_p,
		   atm_cmm_log_info_p);
atm_error_t atm_cmm_free_resvresource(atm_cmm_vcs_p, int);
void atm_cmm_free_resv_listchk(atm_cmm_vcs_p, int);
atm_error_t atm_cmm_driver_pacing_alloc(atm_cmm_vcs_p, atm_cmm_device_p);
atm_error_t atm_cmm_driver_res_alloc(atm_cmm_vcs_p, atm_cmm_device_p);
atm_error_t atm_cmm_driver_res_free(atm_cmm_vcs_p);
void atm_cmm_driver_resvlim_globalinit(int, int);
atm_error_t atm_cmm_sanity_services(atm_vc_services_p,
	atm_vc_services_p, atm_cmm_device_p);
atm_error_t atm_cmm_driver_rate_check(atm_vc_services_p, atm_cmm_device_p);
atm_error_t atm_cmm_alloc_bandwidth(atm_cmm_vcs_p, atm_cmm_device_p);
void atm_cmm_calc_granes(atm_services_granes_p, 
	atm_vc_services_p, atm_cmm_device_p);
void atm_cmm_release_bandwidth(atm_cmm_vcs_p, atm_cmm_device_p);
atm_cmm_esi_p atm_cmm_find_esi(unsigned char *, int, unsigned int,
			       atm_cmm_device_p);
unsigned long atm_cmm_grain2cr_internal(atm_bw_granularity_p, unsigned long, 
	atm_direction_t);
unsigned long atm_cmm_grain2mod_internal(atm_bw_granularity_p, unsigned long,
	atm_direction_t);
unsigned long atm_cmm_cr2grain_internal(atm_bw_granularity_p, unsigned long,
	atm_direction_t);
atm_esi_handle_t atm_cmm_new_global_esi(unsigned char *, 
	int, atm_cmm_device_p);
void atm_cmm_vc_restart();
void atm_cmm_vc_q2start(atm_cmm_vc_p);

void atm_cmm_esi_start(atm_cmm_device_p);
void atm_cmm_esi_collect(void);
void atm_cmm_esi_del_all(atm_cmm_device_p);
void atm_cmm_zombiefy_esi(atm_cmm_esi_p esi);
void atm_cmm_esi_sync(atm_cmm_signal_p);

int atm_cmm_defer_mmi_req(int, atm_cmm_device_p, void *);
void atm_cmm_do_mmi_list(atm_cmm_device_p, int);
#define atm_cmm_flush_mmi_list(d) atm_cmm_do_mmi_list((d), TRUE)
#define atm_cmm_process_mmi_list(d) atm_cmm_do_mmi_list((d), FALSE)

atm_error_t atm_cmm_progress_con(atm_cmm_addr_p,int);
void atm_cmm_resv_expire(void);
void atm_cmm_zombiefy_bind(register atm_cmm_bind_p);
atm_error_t atm_cmm_zombiefy_ppa(atm_cmm_ppa_p);

void atm_cmm_vc_collect(void);
void atm_cmm_bind_collect(void);
void atm_cmm_vcs_collect(void);
void atm_cmm_ppa_collect(void);
void atm_cmm_addr_collect(void);

atm_error_t atm_cmm_pvc_ppa_create(register atm_cmm_device_p);
atm_error_t atm_cmm_pvc_ppa_remove(register atm_cmm_device_p);
void atm_cmm_ppa_sync(register atm_cmm_converge_p);

atm_error_t atm_cmm_create_pvc(atm_cmm_converge_p,atm_vc_services_p,
			       atm_cmm_bind_p,unsigned int,unsigned int);
atm_cmm_addr_p atm_cmm_find_epref(atm_cmm_vc_p, long);
void *atm_cmm_adi_path(atm_mmi_path_p, void **, struct ucred *);
void *atm_cmm_cmi_path(atm_mmi_path_p, atm_cmm_converge_p *,
		       void **, struct ucred *);
void *atm_cmm_smi_path(atm_mmi_path_p, void **, struct ucred *);

void atm_cmm_do_vc_aging(void);
void atm_cmm_start_aging_vc(atm_cmm_vc_p, unsigned int);
void atm_cmm_stop_aging_vc(atm_cmm_vc_p);

void atm_cmm_free_cvg(atm_cmm_converge_p);
atm_error_t atm_cmm_driver_set_encapsz(atm_cmm_vc_p, int);

/* Eternal lock definitions */
/* Global list locks */
atm_lock_info(extern,atm_cmm_driver_list_info)
atm_lock_info(extern,atm_cmm_ppa_list_info)
atm_lock_info(extern,atm_cmm_converge_list_info)
atm_lock_info(extern,atm_cmm_signal_list_info)
atm_lock_info(extern,atm_cmm_vc_zombies_list_info)
atm_lock_info(extern,atm_cmm_bind_zombies_list_info)
atm_lock_info(extern,atm_cmm_esi_zombies_list_info)
atm_lock_info(extern,atm_cmm_ppa_zombies_list_info)
atm_lock_info(extern,atm_cmm_res_exp_list_info)
atm_lock_info(extern,atm_cmm_mmi_list_info)
atm_lock_info(extern,atm_cmm_vc_time_aging_info)
atm_lock_info(extern,atm_cmm_addr_zombies_list_info)

/* locks in the atm_cmm_device structure */
atm_lock_info(extern,atm_cmm_device_lock_info)
atm_lock_info(extern,atm_cmm_device_esi_list_lock_info)
atm_lock_info(extern,atm_cmm_device_ppas_list_lock_info)
atm_lock_info(extern,atm_cmm_device_vchash_list_lock_info)
atm_lock_info(extern,atm_cmm_device_vcs_list_lock_info)
atm_lock_info(extern,atm_cmm_device_unalloc_list_lock_info)
atm_lock_info(extern,atm_cmm_device_unused_list_lock_info)

/* locks in the atm_cmm_esi structure */
atm_cmm_lock_info(extern,atm_cmm_esi_lock_info)
atm_cmm_lock_info(extern,atm_cmm_esi_clone_list_info)

/* locks in the atm_cmm_ppa structure */
atm_lock_info(extern,atm_cmm_ppa_lock_info)
atm_lock_info(extern,atm_cmm_ppa_binds_list_lock_info)
atm_lock_info(extern,atm_cmm_ppa_dbinds_list_lock_info)

/* locks in the atm_cmm_converge structure */
atm_lock_info(extern,atm_cmm_cvg_lock_info)
atm_lock_info(extern,atm_cmm_cvg_esis_list_lock_info)
atm_lock_info(extern,atm_cmm_cvg_binds_list_lock_info)
atm_lock_info(extern,atm_cmm_cvg_vcs_list_lock_info)

/* locks in the atm_cmm_signal structure */
atm_lock_info(extern,atm_cmm_sig_lock_info)
atm_lock_info(extern,atm_cmm_sig_ppas_list_lock_info)
atm_lock_info(extern,atm_cmm_sig_vcs_list_lock_info)

/* locks in the atm_cmm_bind structure */
atm_lock_info(extern,atm_cmm_bind_lock_info)
atm_lock_info(extern,atm_cmm_bind_vcs_list_lock_info)

/* locks for the flow control queue start lists */
atm_cmm_lock_info(extern,atm_cmm_start_q_list_lock_info)

/* locks in the atm_cmm_vc structure */
atm_lock_info(extern,atm_cmm_vc_lock_info)
atm_lock_info(extern,atm_cmm_vc_eps_list_lock_info)
atm_lock_info(extern,atm_cmm_vc_ieps_list_lock_info)
atm_lock_info(extern,atm_cmm_vc_ceps_list_lock_info)
atm_lock_info(extern,atm_cmm_vc_deps_list_lock_info)
atm_lock_info(extern,atm_cmm_vc_neps_list_lock_info)
atm_lock_info(extern,atm_cmm_vc_causes_list_lock_info)
atm_lock_info(extern,atm_cmm_vc_log_list_lock_info)

/* locks in the atm_cmm_vcs structure */
atm_lock_info(extern,atm_cmm_vcs_lock_info)

/* locks in the atm_cmm_addr structure */
atm_lock_info(extern,atm_cmm_addr_lock_info)

#endif
    
