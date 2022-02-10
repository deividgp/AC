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
 * @(#)$RCSfile: atm_smi.h,v $ $Revision: 1.1.28.2 $ (DEC) $Date: 1998/09/25 19:39:11 $
 */

#ifndef _ATM_ATM_SMI_H_
#define _ATM_ATM_SMI_H_

struct atm_sig_params {
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
			       atm_ppa_p ppa,
			       atm_mib_request_t command,
			       atm_mib_var_p request);
	void *reserved1;		/* Must be zero */
	void *reserved2;
	void *reserved3;
    };

typedef struct atm_sig_params atm_sig_params_t;

/* The classic version */
atm_sig_handle_t atm_cmm_register_sig(long version,
	char *const id,
	void *sig_handle,
	atm_error_t (*const sig_setup)(atm_addr_p addr,unsigned long *refptr),
	atm_error_t (*const sig_release)(atm_addr_p addr),
	atm_error_t (*const sig_add)(atm_addr_p addr),
	atm_error_t (*const sig_drop)(atm_addr_p addr),
	atm_error_t (*const sig_enquery)(atm_addr_p addr),
	atm_error_t (*const sig_restart)(void *handle,
		unsigned int class,
		unsigned int vpi,
		unsigned int vci),
	atm_error_t (*const sig_exception)(void *sig_handle,
		unsigned int exception,
		void *arg),
	int (*const sig_mmi)(void *sig_handle,
		int command,
		void *arg,
		int *retval,
		struct ucred *cred),
	atm_error_t (*const sig_mib)(void *sig_handle,
		atm_ppa_p ppa,
		atm_mib_request_t command,
		atm_mib_var_p request)
);

/* The new improved version for code backported from Steel */
void *atm_cmm_register_sig_r3(long version,
			   char *const id,
			   void *sig_handle,
			   atm_sig_params_t *params,
			   atm_sig_handle_t *return_handle,
			   void *reserved1,
			   void *reserved2,
			   void *reserved3,
			   void *reserved4,
			   void *reserved5,
			   void *reserved6,
			   void *reserved7
);

/* Signal module exceptions */
#define ATM_SIGE_NEW_ESI	1
#define ATM_SIGE_DEL_ESI	2
#define ATM_SIGE_DEL_PPA	3
#define ATM_SIGE_ACCEPT		4
#define ATM_SIGE_REJECT		5


atm_error_t atm_cmm_new_call(atm_sig_handle_t sm,
	atm_addr_t 		*addr,
	atm_uni_call_ie_p	ei,
	atm_vc_services_p 	services,
	atm_ppa_p		ppap,
	unsigned int		selector,
	unsigned int		vpi,
	unsigned int		vci,
	unsigned long 		call_reference
);

atm_error_t atm_cmm_reply(atm_sig_handle_t sm,
	atm_addr_t 		*addr,
	atm_uni_call_ie_p	ies,
	unsigned int		vpi,
	unsigned int		vci,
	unsigned long		call_reference
);

atm_error_t atm_cmm_activate_con(atm_sig_handle_t sm,atm_addr_t *addr);

/* For backward compatibility with pre-PTMIN releases */
#define atm_cmm_activate atm_cmm_activate_con

atm_error_t atm_cmm_con_failed(atm_sig_handle_t sm,
	atm_addr_t *addr
);

atm_error_t atm_cmm_con_release(atm_sig_handle_t sm,
        unsigned long reference,
	atm_ppa_p ppa

);

atm_error_t atm_cmm_ep_add(atm_sig_handle_t sm,
			   atm_addr_t *addr,
			   atm_uni_call_ie_p ie,
			   atm_ppa_p ppap,
			   unsigned long call_reference,
			   unsigned long epreference
);

atm_error_t atm_cmm_ep_dropped(atm_sig_handle_t sm,
        unsigned long reference,
        long epreference,
	atm_ppa_p ppa
);

atm_error_t atm_cmm_con_deleted(atm_sig_handle_t sm,
	atm_addr_p addr
);

atm_error_t atm_cmm_restart(atm_sig_handle_t sm,
        unsigned int class,
        unsigned int vpi,
        unsigned int vci
);

void atm_cmm_restart_ack(void *handle,
        unsigned int class,
        unsigned int vpi,
        unsigned int vci
);

void atm_cmm_status_done(atm_addr_p addr);

atm_addr_p atm_cmm_findaddr(unsigned long call_reference,
	long 		endpoint,
	atm_ppa_p	ppa
);

/*
 * The sig_info parameter allows signaling module specific information
 * to be passed to convergence modules.  For example, the standard UNI
 * signaling module passes the UNI version that is in use on the PPA.
 * The signaling module can provide a NULL value if there is no information.
 */
atm_ppa_p atm_cmm_new_ppa(atm_sig_handle_t sm,
	unsigned char 		*addr,
	unsigned int 		addrlen,
	unsigned char		ton,
	unsigned char		anpi,
	atm_drv_handle_t	driver,
	atm_esi_p		esi,
	void			*ppas_id,
	atm_uni_type_t		uni,
	void			*sig_info	
);

atm_error_t atm_cmm_del_ppa(atm_sig_handle_t sm,
	atm_ppa_p	ppa
);

atm_error_t atm_cmm_mib_response(atm_mib_var_p	request,
	atm_mib_var_p	response
);

atm_vc_p atm_cmm_vc_get(atm_drv_handle_t driver,
	unsigned int vpi,
	unsigned int vci
);

/* PVC notification traps are not a supported interface */
atm_error_t
atm_cmm_pvc_trap(atm_sig_handle_t sm, atm_ppa_p ppap, int type,
		atm_error_t (*const pvc_notify)(int cmd, atm_ppa_p ppap,
				void *arg1, void *arg2));

/* Command codes for PVC notify function */
#define ATM_PVC_NOTIFY_ADD      1               /* a PVC has been added */
#define ATM_PVC_NOTIFY_DELETE   2               /* A PVC has been deleted */
#define ATM_PVC_VCC_ADD         3               /* New VCC has been created */
#define ATM_PVC_VCC_DEL         4               /* VCC has been deleted */
#define ATM_PVC_VPC_ADD         5               /* VPC has bee created */
#define ATM_PVC_VPC_DEL         6               /* VPC has been deleted */


atm_error_t atm_cmm_sig_set_cause(atm_sig_handle_t sm,
        unsigned long reference,
        long epreference,
        atm_ppa_p ppa,
        char *reason,
        atm_error_t cause,
        atm_location_t location,
        int diag_length,
        unsigned char *diag);

atm_error_t atm_cmm_smi_set_cause(atm_sig_handle_t handle,
                atm_vc_p   vp,
                atm_addr_p addr,
                char *reason,
                atm_error_t cause,
                atm_location_t location,
                unsigned char diag_length,
                unsigned char *diag);
atm_error_t atm_cmm_smi_set_log(atm_sig_handle_t handle,
                atm_vc_p   vp,
                atm_addr_p addr,
                char *reason,
                atm_error_t cause,
                atm_location_t location,
                unsigned char diag_length,
                unsigned char *diag);

/* Reserved to Digital */
atm_error_t atm_cmm_smi_check_escape(atm_drv_handle_t handle,
				     struct mbuf *m);
#endif
