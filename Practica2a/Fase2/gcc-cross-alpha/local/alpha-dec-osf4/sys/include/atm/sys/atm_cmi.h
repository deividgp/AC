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
 * @(#)$RCSfile: atm_cmi.h,v $ $Revision: 1.1.10.3 $ (DEC) $Date: 1998/10/13 19:27:31 $
 */

#ifndef _ATM_ATM_CMI_H_
#define _ATM_ATM_CMI_H_

struct atm_cvg_params {
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
	void *reserved1;		/* Must be zero. */
	void *reserved2;
	void *reserved3;
};

typedef struct atm_cvg_params atm_cvg_params_t;

/* Types for linkage between convergence modules */

/*
 * A generic type for passing an an entry point from the target back to
 * the requester of the linkage.
 */
typedef long (*atm_linkage_entry_t)(int p1, void *p2, void *p3);

struct atm_cvg_linkage {
    atm_cvg_handle_t	requester;	/* Handle of module requesting link */
    void		*link_context;	/* Generic data passed to target */
    atm_linkage_entry_t entry_return;	/* Pointer to return pointer to
					 * entry function. */
};

typedef struct atm_cvg_linkage atm_cvg_linkage_t;
typedef struct atm_cvg_linkage *atm_cvg_linkage_p;

/* Connection types */
enum atm_ctype { ATM_CT_PTP, ATM_CT_PTM, ATM_CT_PVC };

union atm_cmi_addr {
	atm_addr_p	addr;
	struct	{
		unsigned int	vci;
		unsigned int	vpi;
	} vcn;
};

typedef	void	*atm_bind_handle_t;
typedef void	*atm_esi_handle_t;

/* Items for atm_cmm_bind_info */
typedef enum {	
	/* Values from 0-127 are for bind specific information */
	ATM_BIND_INFO_SELECTOR,		/* Return BIND selector value */
	ATM_BIND_INFO_ID,		/* Return BIND ID value */
	ATM_BIND_INFO_HANDLE,		/* user's bind handle */
	ATM_BIND_INFO_PPA,		/* return a pointer to the PPA */
	/* Values > 128 are for any information that applies to both
	 * binds and PPAs.  This include all driver data.
	 */
	ATM_PPA_INFO_ID=128,		/* Return PPA ID value */
	ATM_PPA_INFO_TYPE,		/* Return interface type */
	ATM_PPA_INFO_TOTAL_VC,		/* number of VCs driver supports */
	ATM_PPA_INFO_MAX_VCI,		/* Maximum number of VCIs supported */
	ATM_PPA_INFO_MAX_VPI,		/* Maximum number of VPIs supported */
	ATM_PPA_INFO_HI_VCI,		/* highest VCI value supported */
	ATM_PPA_INFO_HI_VPI,		/* highest VPI value supported */
	ATM_PPA_INFO_VC_LEFT,		/* Number of VCs unallocated */
	ATM_PPA_INFO_QUEUES,		/* Number of queues driver supports */
	ATM_PPA_INFO_CAPABILITIES,	/* Driver capabilities bitmask */
	ATM_PPA_INFO_FC,		/* Current type of flow control */
	ATM_PPA_INFO_HARD_MTU,		/* interface's hardware MTU */
	ATM_PPA_INFO_PEAK_MAX,		/* Maximum peak bandwidth suported */
	ATM_PPA_INFO_SUST_MAX,		/* Maximum sustainable supported */
	ATM_PPA_INFO_BURST_MAX,		/* Max burst bandwidth supported */
	ATM_PPA_INFO_PEAK_AVAIL,	/* Available peak bandwidth */
	ATM_PPA_INFO_SUST_AVAIL,	/* Available sustainable bandwidth */
	ATM_PPA_INFO_BURST_AVAIL,	/* Available burst bandwidth */
	ATM_PPA_INFO_DUNIT,		/* Driver unit number */
	ATM_PPA_INFO_DNAME,		/* name of driver */
	ATM_PPA_INFO_SNAME,		/* Name of signalling module */
	/* Add new calls for REV 2 of interface here */
	ATM_PPA_INFO_DID,		/* Driver ID value */
	ATM_PPA_INFO_MEDIA,		/* attached media type */
	ATM_PPA_INFO_UNI,		/* UNI type */
	ATM_PPA_NUM_VPI,		/* Number of VCIs in use */
	ATM_PPA_NUM_VCI,		/* Number of VPIs in use */
	ATM_PPA_PEAK_CELLRATE,		/* Peak PDU bitrate for interface */
	ATM_PPA_MAX_VC_FBW,		/* Largest fwd bandwidth perVC in GUs*/
	ATM_PPA_MAX_VC_BBW,		/* Largest back bandwidth perVC in GUs*/
	ATM_PPA_FRESVLIM,		/* fwd % bandwidth limit on CBR
					 * traffic*/
	ATM_PPA_BRESVLIM,		/* back % bandwidth limit on CBR
					 * traffic*/
	ATM_PPA_MAXRES,			/* max bandwidth avail for CBR, 
					 * in GUs */
	ATM_PPA_AVAILRES,		/* bandwidth currently avail for 
					 * CBR, in GUs */
	ATM_PPA_ALLOCGRANE,		/* allocation granularities */
	ATM_PPA_ALLOCLIMIT,		/* limits on allocation granularities */
	ATM_PPA_ESI,			/* returns a pointer to the ESI */
	ATM_PPA_ESILEN,			/* returns length of the ESI */
	ATM_PPA_ESIPID,			/* returns ESI id of parent ESI */
	ATM_PPA_ESIID,			/* returns ESI id of ESI */
	ATM_PPA_UNUSEDRES_FWD,		/* unused reserved resources, forward */
	ATM_PPA_UNUSEDRES_BACK		/* unused reserved resources, back */
} atm_bind_info_t;
		 

/* Exception notification sent by the CMM to convergence modules */
#define ATM_CME_CALL_FAILED	1
#define ATM_CME_EP_ACTIVE	2
#define ATM_CME_EP_DEAD		4
#define ATM_CME_VC_OLD		5
#define ATM_CME_ENQUERY_DONE	6
#define ATM_CME_PPA_ADD		7
#define ATM_CME_PPA_DEL		8
#define ATM_CME_START_VC	9
#define ATM_CME_DELPVC		10
#define ATM_CME_BIND_DEL	11
#define ATM_CME_DVR_DOWN	12
#define ATM_CME_RESV_EXPIRE	13
#define ATM_CME_RESV_AVAIL	14
#define ATM_CME_RESVREQ_REL	15
#define ATM_CME_ESI_DEL		16
#define ATM_CME_LINK_REQ	17
#define ATM_CME_UNLINK_REQ	18

/* Return values for ATM_CME_VC_OLD notifications */
#define ATM_AGER_OK		0
#define ATM_AGER_RESET		1

/* VC aging values for atm_cmm_connect */
#define ATM_AGE_DEFAULT		0
#define ATM_AGE_LOW		0x10000000
#define ATM_AGE_FOREVER		0x0fffffff
#define ATM_AGE_IDLE		0x20000000

/* Operations for atm_cmm_vc_control */
#define ATM_VCC_AGING		1
#define ATM_VCC_QPARAM		2
#define ATM_VCC_ENCAP_SIZE	3

/* Function prototypes for routines in the convergence module interface */

/* The classic version */
atm_cvg_handle_t atm_cmm_register_cvg(long version,
        char *const name,
	void *cvg_handle,
        void (*const receive)(atm_vc_p vc,
                        struct mbuf *mbp,
                        int length,
                        struct mbuf *trailer,
                        char      pti,
                        char gfc),
        atm_error_t (*const exception)(void *cvg_handle,
			int command,
                        void *arg),
	int (*const mmi_manage)(void *cvg_handle,
			int cmd,
			void *arg,
			int *retval,
			struct ucred *cred)
);

/* The new improved version for code backported from Steel */
void *atm_cmm_register_cvg_r3(long version,
			              char *const name,
				      void *cvg_handle,
				      atm_cvg_params_t *params,
				      atm_cvg_handle_t *return_handle,
				      void *reserved2); /* Must be NULL */

atm_error_t atm_cmm_unregister_cvg(atm_cvg_handle_t cm);

atm_cvg_handle_t atm_cmm_find_cvg(char *const name);

atm_error_t atm_cmm_linkto_cvg(atm_cvg_handle_t target,
			       atm_cvg_handle_t myhandle,
			       void *link_context,
			       atm_linkage_entry_t *entry_return);

atm_error_t atm_cmm_unlink_cvg(atm_cvg_handle_t target,
			       atm_cvg_handle_t myhandle,
			       void *link_context);

atm_drv_params_p atm_cmm_driver_query(atm_drv_handle_t driver);

void atm_cmm_drvp_free(atm_drv_params_t *pp);

atm_error_t atm_cmm_connect(atm_cvg_handle_t cm,
        enum atm_ctype 		type,
        atm_bind_handle_t 	calling,
        union atm_cmi_addr	called,
	atm_uni_call_ie_p	ei,
        int 			aging,
        atm_vc_services_p 	params
);


atm_error_t atm_cmm_add(atm_cvg_handle_t cm,
        atm_addr_t 		*addr,
	atm_uni_call_ie_p	ei,
        atm_vc_t 		*vc
);

atm_error_t atm_cmm_release(atm_cvg_handle_t cm,
        atm_vc_t *vc
);

atm_error_t atm_cmm_drop(atm_cvg_handle_t cm,
        atm_addr_t *addr
);

atm_error_t atm_cmm_send(atm_cvg_handle_t cm,
        atm_vc_t *vc,
        const struct mbuf *const data,
        const long length,
        unsigned char clp,
        unsigned char gfc
);

atm_error_t atm_cmm_vc_control(atm_cvg_handle_t cm,
        atm_vc_t *vc,
        int operation,
        void *arg
);

atm_error_t atm_cmm_enquery(atm_cvg_handle_t cm,
        atm_addr_t *ep
);

atm_bind_handle_t atm_cmm_ppa_bind(atm_ppa_p	ppa,
	atm_cvg_handle_t	cvg_handle,
	int			selector,
#define ATM_CMM_BIND_PICK	-1
	void *const		bind_handle,
	atm_error_t (*const connect)(void *bind_handle,
		atm_addr_p		addr,
		atm_bind_handle_t	myaddr,
		atm_vc_p		vc,
		atm_uni_call_ie_p	*reply,
		atm_vc_services_p	requested,
		atm_vc_services_p	*avail)
);

atm_error_t atm_cmm_ppa_unbind(atm_bind_handle_t handle);
atm_error_t atm_cmm_use_bind(atm_bind_handle_t handle);
atm_error_t atm_cmm_unuse_bind(atm_bind_handle_t handle);

atm_error_t atm_cmm_accept(atm_addr_p addr,
	atm_vc_services_t	give
);

void atm_cmm_reject(atm_addr_p addr);

atm_esi_handle_t atm_cmm_new_esi(atm_cvg_handle_t cvg_handle,
	unsigned char 		*esi,
	int			esilen,
	atm_drv_handle_t	driver,
	void			*arg
);

atm_error_t atm_cmm_del_esi(atm_cvg_handle_t,atm_esi_handle_t);

atm_error_t atm_cmm_vc_stats(atm_vc_p vc, atm_vc_stats_p stats);

unsigned long atm_cmm_bind_info(atm_bind_handle_t handle,atm_bind_info_t it);

unsigned long atm_cmm_ppa_info(atm_ppa_p ppa,atm_bind_info_t it);

atm_error_t atm_cmm_set_cause(atm_cvg_handle_t handle,
                atm_vc_p   vp,
                atm_addr_p addr,
                char *reason,
                atm_error_t cause,
                atm_location_t location,
                unsigned char diag_length,
		unsigned char *diag);
atm_error_t atm_cmm_set_log(atm_cvg_handle_t handle,
                atm_vc_p   vp,
                atm_addr_p addr,
                char *reason,
                atm_error_t cause,
                atm_location_t location,
                unsigned char diag_length,
                unsigned char *diag);
atm_cause_info_p atm_cmm_next_cause(atm_vc_p vp,atm_addr_p addr,
			atm_cause_info_p cip);
   
#endif
