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
 * @(#)$RCSfile: atm_adi.h,v $ $Revision: 1.1.14.2 $ (DEC) $Date: 1998/10/13 19:27:31 $
 */

#ifndef ATM_ATM_ADI_H_
#define ATM_ATM_ADI_H_

/* Structure used by device drivers to report their capabilities to the CMM.
* Also used by the CMM to report driver configurations to convergence modules
* on to retrieve driver statistics.
*/

struct atm_drv_params {
    char		*name;		/* driver's name */
    int			unit;		/* unit number */
    atm_interface_t	type;		/* Type of interface */
    atm_media_type_t	media;		/* Media Type */
    unsigned int    	num_vc;		/* total number of VCs supported */
    unsigned int	max_vcib;	/* maximum VCI value allowed */
    unsigned int	max_vpib;	/* maximum VPI value allowed */
    unsigned int	max_vci;	/* maximum VCI's supported */
    unsigned int	max_vpi;	/* maximum VPI's supported */
    unsigned int	sent;		/* number of cells sent */
    unsigned int	received;	/* number of cells received */
    unsigned int	dropped;	/* number of cells dropped locally */
    unsigned int	num_vci;	/* current number of VCI's configured */
    unsigned int	num_vpi;	/* current number of VPI's configured */
    unsigned int    	hard_mtu;	/* maximum packet size supported */
    unsigned int    	nqueue;		/* number of service queues */
    unsigned int	flowcontrol;	/* type of FC supported */
    atm_vc_services_t 	rates;		/* supported bit rates (total) */
    unsigned int    	capabilities;	/* capabilities - see below */
    unsigned char  	numid;		/* number of driver id's */
    unsigned char  	ids[1];		/* array of ID's */
};


typedef struct atm_drv_params atm_drv_params_t;
typedef struct atm_drv_params *atm_drv_params_p;

/* structre for passing queue parameters between convergence modules, CMM,
 * and drivers.  This is allocated and freed by the caller and should
 * only be referenced from within the management function call.  Thus,
 * the storage for this can be local storage in the callers routine.
 */
struct atm_queue_param {
	atm_vc_p        vc;		/* VC to which parameters apply */
	unsigned int    qlength;	/* number of cells to queue */
	unsigned int    qtime;		/* intercell timeout */
	unsigned int    flags;
};

/* flags for above */
#define ATM_QP_STAMP		0x01	/* timestamp cells */
#define ATM_QP_EFLAG		0x02	/* insert null error cells */

typedef struct atm_queue_param atm_queue_param_t;
typedef struct atm_queue_param *atm_queue_param_p;

struct atm_vc_encapsz {
	atm_vc_p vc;			/* Pointer to VC being modified */
	int size;			/* Number of bytes of encapsulation
					 * the convergence module will
					 * remove from the start of each PDU */
};

typedef struct atm_vc_encapsz atm_vc_encapsz_t;
typedef struct atm_vc_encapsz *atm_vc_encapsz_p;

/* function prototypes */
atm_drv_handle_t atm_cmm_register_dd(long version,
	atm_drv_params_p params,
	atm_error_t (*const xmit_func)(int unit,
			struct mbuf *data,
			long length,
			atm_vc_p vc,
			unsigned char clp,
			unsigned char gfc),
	atm_error_t (*const manage_func)(int unit,
			unsigned int command,
			void *arg),
	int (*const mmi_func)(int unit,
			unsigned int command,
			void *arg,
			int *retval,
			struct ucred *cred)
);

/* Management function commands */
#define ATM_DRVMGMT_UP		1	/* bring the driver up */
#define ATM_DRVMGMT_DOWN	2	/* shut the driver down */
#define ATM_DRVMGMT_ADDVC	3	/* add, but don't enable, a new VC */
#define ATM_DRVMGMT_DELVC	4	/* delete an existing VC */
#define ATM_DRVMGMT_ENBVC	5	/* enable a previously added VC */
#define ATM_DRVMGMT_QUERY	6	/* Query resources  */
#define ATM_DRVMGMT_MAXVCI	7	/* set MAX VCI value */
#define ATM_DRVMGMT_MAXVPI	8	/* set max VPI value */
#define ATM_DRVMGMT_SETQ	9	/* set driver queuing parameters */
#define ATM_DRVMGMT_CLEARQ	10	/* clear queuing parameters */
#define ATM_DRVMGMT_FC		12	/* set flow control state */
#define ATM_DRVMGMT_RAWPARAM	13	/* set VC raw processing parameters */
#define ATM_DRVMGMT_SDH		14	/* set SDH state */
#define ATM_DRVMGMT_SCRMIN	15	/* set minimum bandwidth allocation */
#define ATM_DRVMGMT_GCRMIN	16	/* get minimum bandwidth allocation */
#define ATM_DRVMGMT_GCRMAX	17	/* get maximum bandwidth allocation */
#define ATM_DRVMGMT_RRES	18	/* reserve resources for a VC */
#define ATM_DRVMGMT_RREL	19	/* release reserved resources */
#define ATM_DRVMGMT_ENCAPSZ	20	/* set encapsulation size for a VC */

void atm_cmm_receive(const atm_drv_handle_t driver,
	const struct mbuf *const mbp,
	const int               length,
	const struct mbuf *const trailer,
	atm_vc_t  		*vc,
	char              	pti,
	char              	gfc
);

void atm_cmm_oam_receive(atm_drv_handle_t driver,
                struct mbuf *mbp,
                atm_vc_t   *vc
);

void atm_cmm_error(atm_drv_handle_t driver,
                int        error,
                atm_vc_t  *vc
);
atm_error_t atm_cmm_adi_set_cause(atm_drv_handle_t handle,
                atm_vc_p   vp,
                atm_addr_p addr,
                char *reason,
                atm_error_t cause,
                atm_location_t location,
                unsigned char diag_length,
                unsigned char *diag);
atm_error_t atm_cmm_adi_set_log(atm_drv_handle_t handle,
                atm_vc_p   vp,
                atm_addr_p addr,
                char *reason,
                atm_error_t cause,
                atm_location_t location,
                unsigned char diag_length,
                unsigned char *diag);

/* These two routines reserved to Digital */
atm_error_t atm_cmm_register_ilmi_esc(atm_drv_handle_t handle,
				      int (*const esc_func)(unsigned long arg,
				                struct mbuf *m),
				      unsigned char escape,
				      unsigned long arg);
atm_error_t atm_cmm_unregister_ilmi_esc(atm_drv_handle_t handle,
					unsigned char escape);

/* error values for above */
#define ATM_DE_DOWN 		1	/* interface is now down */
#define ATM_DE_UP		2	/* interface is now up */
#define ATM_DE_VC_FATAL		3	/* fatal VC error */
#define ATM_DE_STARTQ		4	/* unflow control a queue */
#define ATM_DE_BRMIN		5	/* Minimum bitrate changed */
#define ATM_DE_BRMAX		6	/* Max bitrate changed */
#define ATM_DE_STARTVC		7	/* start a flow controlled VC */

#endif
