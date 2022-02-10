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
 * @(#)$RCSfile: atm.h,v $ $Revision: 1.1.27.3 $ (DEC) $Date: 1998/10/13 19:27:27 $
 */

#ifndef _ATM_ATM_H_
#define _ATM_ATM_H_

/* Global definitions */
#define ATM_MAX_VPI		0xff
#define ATM_MAX_VCI		0xffff
#define ATM_REVISION_1		0x0000000100000001
#define ATM_REVISION_2		0x0000000200000002
#define ATM_REVISION		0x0000000200000002 /* Default API version */
#define ATM_REVISION_3		0x0000000300000003 /* For access to Steel
						    * API features */

/* global typedefs */
typedef void *atm_drv_handle_t;
typedef void *atm_sig_handle_t;
typedef void *atm_cvg_handle_t;
typedef struct atm_vc atm_vc_t;
typedef struct atm_vc *atm_vc_p;
typedef struct atm_addr atm_addr_t;
typedef struct atm_addr *atm_addr_p;
typedef struct atm_vc_services atm_vc_services_t;
typedef struct atm_vc_services *atm_vc_services_p;


/* cause information values and meaning.  From the UNI 3.0 spec
* but the CMM will use these values when indicating an error.
* If you change this typedef, change the text translations in atm_cmm_cause2str
*/

typedef enum {
	ATM_CAUSE_GOOD=0,	/* no error - good status */
	ATM_CAUSE_UN,		/* unallocated number */
	ATM_CAUSE_NR,		/* no route to network */
	ATM_CAUSE_ND,		/* no route to destination */
	ATM_CAUSE_VCBAD=10,	/* VCI/VPI unacceptable */
	ATM_CAUSE_NORMALCC=16,	/* normal call clearing */
	ATM_CAUSE_UB,		/* user busy */
	ATM_CAUSE_NOR,		/* no user responding */
	ATM_CAUSE_CR=21,	/* call rejected */
	ATM_CAUSE_NC,		/* number changed */
	ATM_CAUSE_CLIR,		/* user rejects all calls with
				       calling line identification
				       restriction */
	ATM_CAUSE_DOO=27,	/* destination out of order */
	ATM_CAUSE_INF,		/* invalid number format */
	ATM_CAUSE_RESP=30,	/* response to ENQUERY */
	ATM_CAUSE_NORMAL,	/* normal, unspecified */
	ATM_CAUSE_NU=31,	/* normal, unspecified - old name */
	ATM_CAUSE_RVU=35,	/* requested VC unavailable */
	ATM_CAUSE_VPCI_AF,	/* VPCI/VCI assignment failure */
	ATM_CAUSE_UCRU,		/* user cell rate unavail */
	ATM_CAUSE_NOO,		/* network out of order */
	ATM_CAUSE_TF=41,	/* temporary failure */
	ATM_CAUSE_AID=43,	/* access info discarded */
	ATM_CAUSE_NVA=45,	/* no VC available */
	ATM_CAUSE_RUU=47,	/* resource unavailable */
	ATM_CAUSE_QU=49,	/* QOS unavailable */
	ATM_CAUSE_BCNA=57,	/* bearer capability not
				       authorized */
	ATM_CAUSE_BCNPA,	/* bearer capability not
				       presently available */
	ATM_CAUSE_ONA=63,	/* option not available */
	ATM_CAUSE_BCNI=65,	/* bearer capability not
				       implemented */
	ATM_CAUSE_UCTP=73,	/* unsupported combination of
				       traffic parameters */
	ATM_CAUSE_APNS=78,	/* AAL parameters can not
				       be supported */
	ATM_CAUSE_ICRV=81,	/* invalid call reference
				       value */
	ATM_CAUSE_CNE,		/* identified channel does not
				       exist */
	ATM_CAUSE_ID=88,	/* incompatable destination */
	ATM_CAUSE_IER,		/* invalid endpoint ref */
	ATM_CAUSE_ITN=91,	/* invalid transit network
				       selection */
	ATM_CAUSE_TAP,		/* too many pending add party
				       requests */
	ATM_CAUSE_MIEM=96,	/* mandatory information
				       element missing */
	ATM_CAUSE_MTNI,		/* message type non-existent
				 * or not implemented */
	ATM_CAUSE_IENI=99,	/* IE non-existent or not implemented */
	ATM_CAUSE_IIEC,		/* invalid IE contents */
	ATM_CAUSE_MNCST,	/* message not compatable with
				       call state */
	ATM_CAUSE_RTE,		/* recovery timer expired */
	ATM_CAUSE_IML=104,	/* incorrect message length */
	ATM_CAUSE_PEU=111,	/* protocol error unspecified */
    /* additional, non-UNI error types are listed below.
     * Values above 255 (one byte) are used to indicate local errors.
     * These error values are encoded so that the lower 8 bits always
     * correspond to the correct UNI cause value.  The upper bits are
     * simply used to provide extra information.
     */
	ATM_CAUSE_NIY=0x12f,		/* Not implemented yet */
	ATM_CAUSE_NOMEM=0x22f,		/* no memory available */
	ATM_CAUSE_BADCVG=0x312,		/* invalid convergence module
				       		specified */
	ATM_CAUSE_BADDRV=0x42f,		/* invalid driver specified */
	ATM_CAUSE_BADSIGV=0x52f,	/* invalid signalling protocol
				       		specified */
	ATM_CAUSE_QWARN=0x600,		/* queue is almost full */
	ATM_CAUSE_QFULL=0x700,		/* queue is full */
	ATM_CAUSE_BUSY=0x811,		/* resource is in use */
	ATM_CAUSE_BARG=0x915,		/* bad function call argument */
	ATM_CAUSE_DEFER=0xa17,		/* operation will finish later */
	ATM_CAUSE_UENT=0xb12,         	/* unknown entity */
	ATM_CAUSE_NOSPC=0xc2f,        	/* No space left */
	ATM_CAUSE_UNKNOWN=0xd1f,      	/* Unknown cause value */
	ATM_CAUSE_SNA=0xe2f,		/* Service Not Available */
	ATM_CAUSE_BADCVGRESP=0xf2f	/* convergence module responded with
					   null/invalid services struct */
} atm_error_t;

/* Local/generic errors detected by the CMM when sanity checking a services
 * structure.
 * If you change this typedef, change the text translations in
 * atm_cmm_lerr2str.
 */
typedef enum atmlerr {
	ATM_LERR_GOOD,		/* No generic or locally detected errors found
				 * in the services struct */
	ATM_LERR_PEAKMISSING,	/* peak CLP0+1 rate mandatory, yet missing */
	ATM_LERR_PEAKTOOBIG,	/* peak CLP0+1 rate exceeds per-VC limit*/
	ATM_LERR_NOBWAVAIL,	/* peak CLP0+1 rate exceeds avail bandwidth */
	ATM_LERR_BADPEAKCR0,	/* peak CLP0 rate exceeds peak CLP0+1*/
	ATM_LERR_BADBURSTCR0,	/* burst CLP0 rate exceeds burst CLP0+1*/
	ATM_LERR_BURSTTOOBIG,   /* burst CLP0 or CLP0+1 rate exceeds 
				 * peak CLP0+1 */
	ATM_LERR_BADSUSTCR0,	/* sustained CLP0 rate exceeds sust CLP0+1*/
	ATM_LERR_SUSTTOOBIG,    /* sustained CLP0 or CLP0+1 rate exceeds
				 * peak CLP0+1 */
	ATM_LERR_RATETOOSMALL,  /* cps rate is < 1 granularity unit */
	ATM_LERR_BADTRAFFTYPE, 	/* bad traffic flag (CBR or pacing not set) */
	ATM_LERR_BADDRVHANDLE, 	/* ppa driver != service's driver handle */
	ATM_LERR_RESNOTALLOC, 	/* services not backed by resources */
	ATM_LERR_RESALREADY, 	/* services struct already backed by resources*/
	ATM_LERR_RATESCHANGED, 	/* service rate info modified after being 
				 * backed by resources */
	ATM_LERR_RATESINCOMPAT, /* the rates in the reserved-resource service 
				 * struct can't be applied to incoming call */
	ATM_LERR_VCALREADY, 	/* services struct already attached to a VC */
	ATM_LERR_LAST		/* end marker */

} atm_lerr_t;

/* ATM Location codes.
 * This indicates where the error occurred.
 */

typedef enum {
	ATM_LOCATION_USER=0,		/* error at ATM user */
	ATM_LOCATION_LOCAL_PRIVATE,	/* private network serving local user */
	ATM_LOCATION_LOCAL_PUBLIC,	/* public network serving local user */
	ATM_LOCATION_TRANSIT,		/* transit network */
	ATM_LOCATION_REMOTE_PRIVATE,	/* private serving remote user */
	ATM_LOCATION_REMOTE_PUBLIC,	/* public serving remote */
	ATM_LOCATION_INTERNATIONAL=7,	/* international network */
	ATM_LOCATION_BEYOND=0xa		/* beyond internetworking pint */
} atm_location_t;

/* Global QoS type definitions */
typedef enum atmqos { ATM_QOS_NONE=0, ATM_QOS_CLASSA, ATM_QOS_CLASSB, ATM_QOS_CLASSC, 
		ATM_QOS_CLASSD, ATM_QOS_CLASSX, ATM_QOS_CLASSY } atmqos_t;

/* Global ATM AAL types */
typedef enum atmaal { ATM_AAL1=1, ATM_AAL2, ATM_AAL34, ATM_AAL5=5 } atmaal_t;


/* Structure for retrieving extended cause information for endpoints.  This
 * extended information includes all normal ATM information, plus some
 * local information (such as the module in which the error was reported).
 * The total number of causes per endpoint is a system tunable parameter.
 */

#define ATM_DIAGNOSTIC_LENGTH	27

struct atm_cause_info {
	atm_error_t	cause;		/* the type of error that occurred */
	atm_location_t	location;	/* location on the network */
	char 		*module_name;	/* The local module where it happened */
	char 		*reason;	/* module internal reason */
	unsigned char	diag_length;	/* length of diagnostics info */
	unsigned char	diag[ATM_DIAGNOSTIC_LENGTH];	/* diagnostic info */
};


typedef struct atm_cause_info atm_cause_info_t;
typedef struct atm_cause_info *atm_cause_info_p;

/* This tells us if we are the called or calling party.  This is needed
 * when doing CBR related work so we can tell if our transmission side
 * is the forward or backward direction.
 */

typedef enum {
	ATM_DIRECTION_PVC,
	ATM_DIRECTION_CALLING,
	ATM_DIRECTION_CALLED
} atm_direction_t;

/* ATM Physical Point of Attachement (PPA) structure.  This defines
* and ATM address endpoint on the local system.
*
* Make the structure a power of 2 bytes in length.
*/

typedef enum {
	ATM_UNI_PRIVATE,		/* Private UNI */
	ATM_UNI_PUBLIC			/* Public UNI */
} atm_uni_type_t;

typedef enum {
	ATM_PPA_PRIVATE,		/* owned by a single convergence mod */
	ATM_PPA_PUBLIC			/* shared by all */
} atm_ppa_type_t;


#define ATM_PPA_MAX_ADDR	31

struct atm_ppa {
    atm_drv_handle_t	driver;
    atm_sig_handle_t	sig;
    void		*ppas_id;
    unsigned char	ton;			/* type of number */
    unsigned char	anpi;			/* address number plan id */
    unsigned char	addrlen;
    unsigned char	address[ATM_PPA_MAX_ADDR];
    atm_uni_type_t	uni;			/* Type of Interface */
    atm_ppa_type_t	type;			/* type of PPA */
    void		*esi_arg;		/* ESI owner's arg */
    void  		*sig_info;		/* signalling info */
};

typedef struct atm_ppa atm_ppa_t;
typedef struct atm_ppa *atm_ppa_p;

/* ATM ESI structure used in defining ESI portions of UNI 3.X addresses.
* This may also be used by other signalling protocols to define local
* parts of addresses (or full addresses if the protocol supports that).
*/

#define ATM_MAX_ESI		ATM_PPA_MAX_ADDR

struct atm_esi {
    unsigned char		esi[ATM_MAX_ESI];
    unsigned char		esilen;
    atm_drv_handle_t		driver;

    /* the following members are for use only by
     * signalling protocol modules.
     */
    void			*sigp1;
    void			*sigp2;
};

typedef struct atm_esi atm_esi_t;
typedef struct atm_esi *atm_esi_p;

/* This structure defines the service parameters of the connection.  There
* is exactly on of these per VC.
* Storage for this structure is allocated by the first module to reference
* the VC (signalling or convergence) and released by the CMM when deleting
* a VC.
*/
struct atm_vc_services {
    atm_vc_p        vc;			/* VC for these parameters */
    atmqos_t        fqos;		/* forward QOS */
    atmqos_t        bqos;		/* backward QOS */
    unsigned int    fmtu;		/* forward MTU */
    unsigned int    bmtu;		/* backward MTU */
    unsigned int    valid_rates;	/* valid cell rates provided */
    unsigned int    fpeakcr[2];		/* forward peak cell rate */
    unsigned int    bpeakcr[2];		/* backward peak cell rate */
    unsigned int    fsustcr[2];		/* forward sustainable cell rate */
    unsigned int    bsustcr[2];		/* backward sustainable cell rate */
    unsigned int    fburstcr[2];	/* forward burst cell rate */
    unsigned int    bburstcr[2];	/* backward burst cell rate */
    unsigned int    flags;		/* flags - see below */
    atmaal_t	    aal;		/* AAL type */
    unsigned char   queue;		/* driver queue to use */
    unsigned int    bearer_class;	/* Bearer class information */
    atm_lerr_t 	    lerrstat;		/* local/generic services sanity-check
					 * status */
    unsigned int    nerrstat;		/* network/signalling services 
					 * sanity-check status */
    atm_drv_handle_t cmm_drv_handle;	/* driver handle for rsvd resources */

    /* Field accessible only by driver modules */
    void	   *drv_resource;	

    /* Field accessible only by convergence modules */
    void           *converge_handle;
};

/* Flags for the valid rates */
#define ATM_VCRV_FPEAK0		0x0001
#define ATM_VCRV_FPEAK1		0x0002
#define ATM_VCRV_BPEAK0		0x0004
#define ATM_VCRV_BPEAK1		0x0008
#define ATM_VCRV_FSUST0		0x0010
#define ATM_VCRV_FSUST1		0x0020
#define ATM_VCRV_BSUST0		0x0040
#define ATM_VCRV_BSUST1		0x0080
#define ATM_VCRV_FBURST0	0x0100
#define ATM_VCRV_FBURST1	0x0200
#define ATM_VCRV_BBURST0	0x0400
#define ATM_VCRV_BBURST1	0x0800

/* flags for above */
#define ATM_SERVICES_BEI	0x00000001	/* best effort indicator */
#define ATM_SERVICES_FTAG	0x00000002	/* forward tagging */
#define ATM_SERVICES_BTAG	0x00000004	/* backward tagging */
#define ATM_SERVICES_PACING	0x00000008	/* pace the VC */
#define ATM_SERVICES_CBR	0x00000010	/* this is a CBR circuit */
#define ATM_SERVICES_VBR	0x00000020	/* This is a VBR circuit */
#define ATM_SERVICES_TIMING	0x00000100	/* end-end timing required */
#define ATM_SERVICES_NOTIMING	0x00000200	/* no timing requirements */
#define ATM_SERVICES_CLIPPING	0x00001000	/* Susceptible to Clipping */
#define ATM_SERVICES_PTM	0x00002000	/* Point-to-multipoint call */

/* Except for PACING, all traffic contract parameter flags are not negotiable */
#define ATM_SERVICES_CANTCHANGE \
	(ATM_SERVICES_BEI | ATM_SERVICES_FTAG | ATM_SERVICES_BTAG |\
	ATM_SERVICES_CBR | ATM_SERVICES_VBR | ATM_SERVICES_TIMING |\
	ATM_SERVICES_NOTIMING | ATM_SERVICES_CLIPPING | ATM_SERVICES_PTM)


/* Bearer class */
#define ATM_BBEARER_BCOB_A	0x00000001	/* Bearer class A */
#define ATM_BBEARER_BCOB_C	0x00000003	/* Bearer class C */
#define ATM_BBEARER_BCOB_X	0x00000010	/* Bearer class X */

/* Cell Loss Priority for cell rate arrays.  The first element of a
* cell rate array is for CLP=0 and the second element is for CLP=1.
* These can be accessed with the two following defines to make it
* more apparent what is going on.  For example:
*		atm_vc_services.bpeakcr[ATM_CLP_0]
*		atm_vc_services.bburstcr[ATM_CLP_1]
*/
#define ATM_CLP_0	0
#define ATM_CLP_1	1


/* Definitions of values fetched via BIND/PPA info calls */

typedef enum {	ATM_IT_TI,		/* T1 - 1.5 Mbs */ 
		ATM_IT_E1,		/* E1 - 2 Mbs */
		ATM_IT_E3,		/* E3 - 34 Mbs */
		ATM_IT_DS3, 		/* DS3 - 45 Mbs */
		ATM_IT_STS1,		/* STS1 - 51 Mbs */
		ATM_IT_100, 		/* generic 100 Mbs */
		ATM_IT_TAXI,		/* TAXI - 100 Mbs */
		ATM_IT_FC,		/* Fiber Channel - 155 Mbs */
		ATM_IT_STS3, 		/* STS3 - 155 Mbs */
		ATM_IT_155,		/* generic 155 Mbs */
		ATM_IT_STS12		/* STS12 - 622 Mbs */
} atm_interface_t;

/* driver capabilities bits */
#define ATM_DC_DOESPTI		0x00000001
#define ATM_DC_DOESGFC		0x00000002
#define ATM_DC_DOES_AAL5	0x00000004
#define ATM_DC_DOES_AAL3	0x00000008
#define ATM_DC_DOES_RAW		0x00000010
#define ATM_DC_DOES_STAMP0	0x00000020
#define ATM_DC_DOES_CBR		0x00000100
#define ATM_DC_DOES_VBR		0x00000200
#define ATM_DC_DOES_PACING	0x00001000
#define ATM_DC_DOES_HWCHKSUM	0x00002000 /* Hardware IP checksums */

/* media type */
typedef enum {
	ATM_MT_COAX,			/* Coaxial cable */
	ATM_MT_SMF,			/* Single Mode Fiber */
	ATM_MT_MMF,			/* Multimode Fiber */
	ATM_MT_STP,			/* Shielded twisted pair */
	ATM_MT_UTP			/* Unshielded twisted pair */
} atm_media_type_t;


/* Structure used to report per-VC statistics back to convergence modules
 * or any module which uses the VC stats call.
 */

#include <sys/time.h>

typedef struct {
    unsigned long	bytes_in;
    unsigned long	bytes_out;
    unsigned int	packets_in;
    unsigned int	packets_out;
    struct timeval	opened;
    struct timeval	last_out;
    struct timeval	last_in;
} atm_vc_stats_t, *atm_vc_stats_p;

/* Structure for setting and getting allocation granularities.
 * Granularities are specified as a ratio of some multiplier.
 * Typically, the multiplier will be the maximum line rate.
 * The numerator and denominator represent the ratio to be applied
 * to the multiplier.
 * For example, for an OC-3 line, the peak cell rate is 353207 cps.
 * To specify an allocation unit of 2% of the maximum multiplier is
 * set to 353207, numerator to 2, and denominator to 100.
 * Figuring the actual cell rate is simply:
 *		(multiplier * numerator)/denominator
 * To give the integer cell rate.
 * When the ratio doesn't yield an integer, it is up to the driver and/or
 * convergence modules to do the math to extract the non-integer components
 * of the quotient.
 */

struct atm_granularity {
	unsigned long	numerator;
	unsigned long	denominator;
	unsigned long	multiplier;
		 int	flags;
};

/* Granularity flags used for setting only */
#define ATM_GRANE_VALID		1		/* contents are valid */
#define ATM_GRANE_EXACT		2		/* must set exactly */

typedef struct atm_granularity atm_granularity_t;
typedef struct atm_granularity *atm_granularity_p;

struct atm_bw_granularity {
	atm_granularity_t	fwd;
	atm_granularity_t	back;
};

typedef struct atm_bw_granularity atm_bw_granularity_t;
typedef struct atm_bw_granularity *atm_bw_granularity_p;

/* Structure for getting services rates actually allocated to a VC,
 * in allocation granularity units.
 */
struct atm_services_granes {
        unsigned int            fpeakgr[2];     /* fpeakcr granes allocated */
        unsigned int            bpeakgr[2];     /* bpeakcr granes allocated */
        unsigned int            fsustgr[2];     /* fsustcr granes allocated */
        unsigned int            bsustgr[2];     /* bsustcr granes allocated */
        unsigned int            fburstgr[2];    /* fburstcr granes allocated */
        unsigned int            bburstgr[2];    /* bburstcr granes allocated */
};

typedef struct atm_services_granes atm_services_granes_t;
typedef struct atm_services_granes *atm_services_granes_p;



atm_error_t atm_cmm_vc_stats(atm_vc_p vc, atm_vc_stats_p stats);

/* This structure is the focus for all endpoint activity.  There is exactly
* one of these for each connection to an endpoint.  Since VCs can be
* connected to multiple endpoints more than one of these structures could
* be associated with a VC.  This structure contains the endpoint address
* and subaddress, as well as all endpoint status.
* No module should make any assumption about the size of this structure
* outside the members listed here.
* Convergence or signalling modules allocate and delete storage for this
* Structure.
*/

struct atm_addr {
    atm_vc_p        vc;			/* VC for this endpoint */
    unsigned char   address[20];		/* ATM hardware address */
    unsigned char   ton;			/* type of number */
    unsigned char   anpi;			/* address/numbering plan */
    unsigned char   subaddress[20];		/* ATM hardware subaddress */
    unsigned char   subaddress_type;
    unsigned char   eprtype;		/* endpoint reference type */
    unsigned short  endpoint;		/* endpoint reference number */
    unsigned char   state;			/* internal state value */
    atm_error_t     atm_error;		/* last errno on the endpoint */
    void            *setup;			/* setup signalling params */
    void            *connect;	

    /* cause information */
    unsigned char   location;
    unsigned char   cause;
    unsigned char   diag_length;
    unsigned char   diagnostic[ATM_DIAGNOSTIC_LENGTH];

    /* Endpoint State IE */
    unsigned char   endstate;		/* endpoint state values */

    /* private convergence module structure members */
    void                    *conv_p1;
    void                    *conv_p2;

    /* private signalling module structure members */
    void                    *sig_p1;
    void                    *sig_p2;
};

/*
 * Endpoint states which might be reflected in the atm_addr_t state field.
 * Based on the UNI 3.x specification.
 */
#define ATM_EPF_NULL		0		/* null state */
#define ATM_EPF_CI		1		/* call initiated (U1) */
#define ATM_EPF_OCP		3		/* call proceeding (U3) */
#define ATM_EPF_CD		4		/* call delivered (U4) */
#define ATM_EPF_CP		6		/* call present (U6) */
#define ATM_EPF_CR		7		/* call received (U7) */
#define ATM_EPF_CREQ		8		/* connection request (U8) */
#define ATM_EPF_ICP		9		/* call proceeding (U9) */
#define ATM_EPF_ACTIVE		10		/* active (U10) */
#define ATM_EPF_RR		11		/* release request (U11) */
#define ATM_EPF_RI		12		/* release indication (U12) */
#define ATM_EPF_RESTARTR	17		/* restart request (rest1) */
#define ATM_EPF_RESTART		18		/* restart (rest2) */
#define ATM_EPF_API		33		/* add initiated */
#define ATM_EPF_APR		34		/* add party received */
#define ATM_EPF_DPI		35		/* drop party initiated */
#define ATM_EPF_DPR		36		/* drop part received */

/* This structure is the focus for all VC activity.  There is exactly one
* of these for each VC on the system.  Module may only modify those
* structure members which are assigned to them.  Other structure
* members should be considered read-only under lock protection on MP
* systems.
* Only the CMM may allocate and free storage for this structure.
* No module should make any assumption about the size of this structure
* outside the members listed here.
*/
struct atm_vc {
	/* Fields accessible only by convergence modules */
	void                    *conv_pp1;
	void                    *conv_pp2;

	/* Fields accessible only by drivers */
	void                    *drv_pp1;
	void                    *drv_pp2;

	/* Fields accessible only by signalling modules */
	void                    *sig_pp1;
	void                    *sig_pp2;

	/* VC physical parameters */
	atm_vc_services_p       vcs;

	/* VC information */
	unsigned long           call_reference;
	atm_error_t             errno;
	int                     vci;
	int                     vpi;
	atm_ppa_p	        ppa;
	int			selector;
	atm_direction_t		direction;	/* direction of the call */
};


/* The following structure is used to pass UNI 3.0 signalling parameters
* between convergence modules and the UNI 3.0 signalling module.
* This is allocated by the first module to reference the endpoint
* (signalling or convergence) and is deleted by the convergence module
* when the endpoint is deleted.
*/

typedef enum {	ATM_IET_EMPTY=0,
		ATM_IET_AAL1,
		ATM_IET_AAL2,
		ATM_IET_AAL3,
		ATM_IET_AAL5,
		ATM_IET_AALU,
		ATM_IET_CI,
		ATM_IET_BBHI,
		ATM_IET_BBLOW,
		ATM_IET_BBBC,		/* No longer used */
		ATM_IET_REPEAT
} atm_ie_types_t;

struct atm_uni_call_ie {
    atm_ie_types_t	ie_type;
    unsigned char	last;
    union {
	    union {
		    struct {
			    unsigned short   subtype;
			    unsigned short   cbr_rate;
			    unsigned short   multiplier;
			    unsigned short   crt;
			    unsigned short   err_corr;
			    unsigned short   sdt;
			    unsigned short   pfc;
		    } aal1;
		    struct {
			    unsigned int  fsdu;
			    unsigned int  bsdu;
			    unsigned int  mid;
			    unsigned short   mode;
			    unsigned short   sscs;
		    } aal34;
		    struct {
			    unsigned int  fsdu;
			    unsigned int  bsdu;
			    unsigned short   mode;
			    unsigned short   sscs;
		    } aal5;
		    unsigned short 	aalu[4];
	    } aal_params;
	    struct {
		    unsigned short   class;
		    unsigned short   type;

		    unsigned short   timing;
		    unsigned short   clipping;
		    unsigned short   upcc;
	    } bbbc;			/* No longer used. BBBC info is now 
					 * in the atm_vc_services struct. */
	    struct {
		    unsigned short   hlit;
		    unsigned short   hlisz;
		    unsigned short   hli[8];
	    } bb_high_layer;
	    struct {
		    unsigned short   layer2proto;
		    unsigned short   mode2;
		    unsigned short   q933;
		    unsigned short   window_size;
		    unsigned short   user2proto;
		    unsigned short   layer3proto;
		    unsigned short   mode3;
		    unsigned short   dpsize;
		    unsigned short   pktwindow;
		    unsigned short   user3proto;
		    unsigned int     ipi;
		    unsigned short   snapid;
		    unsigned short   oui[3];
		    unsigned short   pid[2];
	    } bb_low_layer;
	    struct {
		    unsigned short  bbri;
	    } bbrepeat;
	    unsigned short bytes[28];
    } ie;
};

typedef struct atm_uni_call_ie atm_uni_call_ie_t;
typedef struct atm_uni_call_ie *atm_uni_call_ie_p;

/* Macros for accessing information in the above structure */
#define ATM_IE_SETVAL(F,V) (F) = (V); (F) |= (0xFFFFFFFFL << (sizeof((F)) * 4))
#define ATM_IE_ISVALID(F) ((F) & (8L << (sizeof((F)) * 4)))
#define ATM_IE_GETVAL(F) ((F) & ((F) >> (sizeof((F)) * 4)))
#define ATM_IE_CLRVAL(F) (F) = 0

/* following types are used to determine what version of UNI signaling is 
 * being used
 */

typedef enum {
	ATM_UNI30,			/* UNI 3.0   */
	ATM_UNI31,			/* UNI 3.1   */
	ATM_UNIUNKN			/* unknown   */
} atm_uni_vers_t;


/*
 * The following are used for communicating MIB information among components
 * of the ATM subsystem.  For example, a convergence module uses these
 * types and structures when requesting information from the switch via ILMI.
 */

/* Definitions of the possible operations on atm_mib_var structures. */
/* These must match the SNMP definitions. */
typedef enum {
	ATM_MIB_GET,			/* SNMP Get */
	ATM_MIB_GETNEXT,		/* SNMP Get Next */
	ATM_MIB_SET			/* SNMP Set */
} atm_mib_request_t;

/* Definitions of possible results for MIB requests */
/* These must match the SNMP definitions. */
typedef enum {
	ATM_MIB_ERR_NOERROR,
	ATM_MIB_ERR_TOOBIG,
	ATM_MIB_ERR_NOSUCHNAME,
	ATM_MIB_ERR_BADVALUE,
	ATM_MIB_ERR_READONLY,
	ATM_MIB_ERR_GENERR
} atm_mib_error_t;

/* Definitions of the possible types for values in atm_mib_var_t. */
/* These must match the SNMP definitions. */
typedef enum {
	ATM_MIB_TYPE_BOOLEAN=1,		/* Boolean */
	ATM_MIB_TYPE_INTEGER,		/* Integer */
	ATM_MIB_TYPE_BITSTRING,		/* Bit String */
	ATM_MIB_TYPE_OCTETSTRING,	/* Octet String */
	ATM_MIB_TYPE_NULL,		/* Null value */
	ATM_MIB_TYPE_OBJECT_ID		/* Object ID */
} atm_mib_type_t;


/*
 * The type for each element in a MIB object id (variable name).
 * The complete object ID is an array of atm_oid_t.
 * The data in an atm_oid_t is not BER encoded.
 */
typedef unsigned int atm_oid_t;
typedef unsigned int *atm_oid_p;

/*
 * This structure is used to pass MIB data to and from the CMM.
 */
struct atm_mib_var {
	unsigned int	oid_length;	/* Number of elements in the name */
	atm_oid_p	oid;		/* Pointer to full name of variable */

					/* GLG - the value should be a union
					 * with the common types broken out. */

	unsigned int	value_length;	/* Size of the variable value. */
	atm_mib_type_t	value_type;	/* Type of the returned value */
	void		*value;		/* Pointer to the variable value */
	atm_mib_error_t	status;		/* Status returned on a response */

	/* Fields reserved for use by signaling module */
	void		*sig_pp1;
	void		*sig_pp2;

	/* Fields reserved for use by convergence module */
	void		*cvg_pp1;
	void		*cvg_pp2;
};

typedef struct atm_mib_var atm_mib_var_t;
typedef struct atm_mib_var *atm_mib_var_p;

/*
 * These are obsolete definitions which will be removed at some point in the
 * future.
 */
struct atm_odi {
	void		*buffer;	/* where to put data */
	int		buffer_length;	/* size of data buffer */
	int		object_size;	/* Size of each object returned */
	int		object_count;	/* number of objects returned */
	unsigned int	length;		/* length of ID */
	unsigned int	id[1];		/* The OID of the object to fetch */
};
typedef struct atm_odi atm_odi_t;
typedef struct atm_odi *atm_odi_p;


/* random definitions which may be needed by all ATM modules */
#define ATM_FLOW_NONE		0
#define ATM_FLOW_STD		1
#define ATM_FLOW_VENDOR		2


/* Values defined for use in different elements in the signalling messages */

/* AAL5 Parameters IDs */
#define ATM_AAL5_MAX_FSDU_ID	0x8C
#define ATM_AAL5_MAX_BSDU_ID	0x81
#define ATM_AAL5_MODE_ID	0x83
#define ATM_AAL5_MODE_ID	0x83
#define ATM_AAL5_SSCS_TYPE_ID	0x84
#define ATM_AAL5_MAX_SDU	65535	/* Forward and backward max. CPCS SDU */

/* Mode for AAL3/4 and AAL5 */
#define ATM_AAL_MESG_MODE	0x01	/* Message mode */
#define ATM_AAL_STREAM_MODE	0x02	/* Streaming mode */

/* SSCS type for AAL3/4 and AAL 5 */
#define ATM_AAL_SSCS_NULL	0x00	/* Null */ 
#define ATM_AAL_SSCS_ASSURED	0x01	/* Assured operation */
#define ATM_AAL_SSCS_NONASSURED	0x02	/* Non-assured operation */
#define ATM_AAL_SSCS_FR		0x04	/* Frame relay SSCS */

/* Traffic type */
#define ATM_TRAFFIC_CBR		0x01	/* CBR traffic */
#define ATM_TRAFFIC_VBR		0x02	/* VBR traffic */

/* Timing requirements */
#define ATM_TIMING_NOIND	0x00	/* No indication of timing */
#define ATM_TIMING_ETOE_REQ	0x01	/* End to end timing required */
#define ATM_TIMING_ETOE_NOTREQ	0x02	/* End to end timing not required */

/* Susceptibility to clipping */
#define ATM_SUSC_CLIPPING_NO	0x00	/* Not susceptible to clipping */
#define ATM_SUSC_CLIPPING_YES	0x01	/* Susceptible to clipping */

/* User plane connection configuration */
#define ATM_USER_PLANE_PTP	0x00	/* Point to point */
#define ATM_USER_PLANE_PTM	0x01	/* Point to multipoint */

/* Broadband high layer information */
#define ATM_BHLI_TYPE_ISO	0x00	/* ISO */
#define ATM_BHLI_TYPE_USR	0x01	/* User specific */
#define ATM_BHLI_TYPE_HLPROF	0x02	/* High layer profile */
#define ATM_BHLI_TYPE_VENDOR	0x03	/* Vendor specific */

/* Broadband low layer information */
#define ATM_BLLI_UIL2_ISO1745		0x01
#define ATM_BLLI_UIL2_CCITT_Q921	0x02
#define ATM_BLLI_UIL2_CCITT_LL_X25	0x06
#define ATM_BLLI_UIL2_CCITT_ML_X25	0x07
#define ATM_BLLI_UIL2_EXTENDED_LAPB	0x08
#define ATM_BLLI_UIL2_HDLC_ARM1		0x09
#define ATM_BLLI_UIL2_HDLC_ARM2		0x0A
#define ATM_BLLI_UIL2_HDLC_ARM3		0x0B
#define ATM_BLLI_UIL2_LAN_LLC_8022	0x0C
#define ATM_BLLI_UIL2_CCITT_SLP		0x0D
#define ATM_BLLI_UIL2_CCITT_Q922	0x0E
#define ATM_BLLI_UIL2_USER_SPEC		0x10
#define ATM_BLLI_UIL2_ISO_7776_DTE	0x11

/* Layer/SNAP ID for BLLI information */
#define ATM_BLLI_LAYER_MASK		0x60
#define ATM_BLLI_LAYER1_ID		0x20
#define ATM_BLLI_LAYER2_ID		0x40
#define ATM_BLLI_LAYER3_ID		0x60

/* Mode of operation for octet 6a */
#define	ATM_BLLI_MODE_NORMAL		0x01
#define	ATM_BLLI_MODE_EXTENDED		0x10

/* Q.933 use */
#define ATM_BLLI_Q933			0x00

/* User information layer 3 protocol */
#define ATM_BLLI_UIL3_CCITT_PL_X25	0x06
#define ATM_BLLI_UIL3_ISO_8208		0x07
#define ATM_BLLI_UIL3_ISO_8878		0x08
#define ATM_BLLI_UIL3_ISO_8473		0x09
#define ATM_BLLI_UIL3_CCITT_T70_MNL	0x0A
#define ATM_BLLI_UIL3_ISO_TR9577	0x0B
#define ATM_BLLI_UIL3_USER_SPEC		0x10


/* Mode of operation for octet 7a */
#define	ATM_BLLI_MODE_NPSN	0x01	/* Normal pkt. sequence numbering. */
#define	ATM_BLLI_MODE_EPSN	0x10	/* Extended pkt. sequence numbering. */

/* Default packet size */
#define	ATM_BLLI_DPKT_SIZE_16	0x04
#define	ATM_BLLI_DPKT_SIZE_32	0x05
#define	ATM_BLLI_DPKT_SIZE_64	0x06
#define	ATM_BLLI_DPKT_SIZE_128	0x07
#define	ATM_BLLI_DPKT_SIZE_256	0x08
#define	ATM_BLLI_DPKT_SIZE_512	0x09
#define	ATM_BLLI_DPKT_SIZE_1024	0x0A
#define	ATM_BLLI_DPKT_SIZE_2048	0x0B
#define	ATM_BLLI_DPKT_SIZE_4096	0x0C

/* ISO/IEC TR 9577 initial protocol indentification (IPI) */
#define ATM_BLLI_ISO_9577_IP	0x66
#define ATM_BLLI_ISO_9577_SNAP	0x80

/* Type of Number */
#define ATM_CPN_TON_UNKNOWN	0x00	/* Unknown */
#define ATM_CPN_INTERNATIONAL	0x01	/* International */

/* Addressing/numbering plan identification */
#define ATM_CPN_NMB_PLAN_ISDN	0x01	/* ISDN numbering plan (E.164) */
#define ATM_CPN_NMB_PLAN_NSAP	0x02	/* ISO NSAP */

/* Presentation indicator */
#define ATM_CPN_PRES_ALLOWED		0x00
#define ATM_CPN_PRES_RESTRICT		0x01
#define ATM_CPN_PRES_NUMB_UNAVAIL	0x02

/* Screening indicator */
#define ATM_CPN_SCREEN_NOSCREEN		0x00
#define ATM_CPN_SCREEN_VERIFIED_PASS	0x01
#define ATM_CPN_SCREEN_VERIFIED_FAIL	0x02

/* QoS parameters */
#define ATM_QOS_UNSPECIFIED	0x00
#define ATM_QOS_CLASS1		0x01
#define ATM_QOS_CLASS2		0x02
#define ATM_QOS_CLASS3		0x03
#define ATM_QOS_CLASS4		0x04

/* Subsystem-wide error message levels */

typedef enum {
	ATM_MSGLEVEL_UNSPEC=-1,		/* Level is unspecified. Use global. */
	ATM_MSGLEVEL_NORMAL,		/* Output normal level of messages */
	ATM_MSGLEVEL_INFO,		/* Output additional info messages */
	ATM_MSGLEVEL_VERBOSE		/* Output most verbose level */
} atm_msglevel_t;

extern atm_msglevel_t atm_global_msglevel; /* Default level for all ATM
					    * components */

/*
 * Macros for displaying user messages under the control of a ATM subsystem-
 * wide error message level.  An individual component can override the 
 * global message level by specifying its own message level variable e.g.
 *
 *	ATM_MSG_NORMAL(xyz_level, ("ATMXYZ - invalid MTU value %d", mtu));
 */ 

/*
 * Use ATM_MSG_NORMAL for messages which should be displayed at the normal
 * message level:
 *	- Initial "component is configured" messages.
 *	- Abnormal VC releases.
 *	- Internal error conditions in the subsystem.
 *	- Problems that always require user action
 *	- Messages that accompany a panic
 */
#define ATM_MSG_NORMAL(l,msg) printf##msg

/*
 * Use ATM_MSG_INFO for messages which should be displayed at the informational
 * message level:
 *	- Normal VC releases
 *	- Important state changes or loss of connectivity
 *	- Error conditions that are known to be transient
 *	- Unexpected conditions that may not represent actual errors
 */
#define ATM_MSG_INFO(l,msg) \
	{ if( ( (l) == ATM_MSGLEVEL_UNSPEC && \
	    atm_global_msglevel >= ATM_MSGLEVEL_INFO ) || \
	      ( (l) >= ATM_MSGLEVEL_INFO)) printf##msg; }

/*
 * Use ATM_MSG_VERBOSE for messages which should be displayed at the verbose
 * message level:
 *	- Information needed only for troubleshooting
 *	- Detailed progress or state change messages
 */
#define ATM_MSG_VERBOSE(l,msg) \
	{ if( ( (l) == ATM_MSGLEVEL_UNSPEC && \
	    atm_global_msglevel >= ATM_MSGLEVEL_VERBOSE ) || \
	      ( (l) >= ATM_MSGLEVEL_VERBOSE)) printf##msg; }


/* global function prototypes */
atm_addr_p atm_cmm_alloc_addr(void);
void atm_cmm_free_addr(atm_addr_p addr);
atm_error_t atm_cmm_use_addr(atm_addr_p addr);
atm_error_t atm_cmm_unuse_addr(atm_addr_p addr);

atm_vc_services_p atm_cmm_alloc_services(void);
atm_error_t atm_cmm_reserve_resources(atm_ppa_p ppa, atm_cvg_handle_t cm,
		atm_vc_services_p s);
atm_error_t atm_cmm_free_services(atm_vc_services_p s);
atm_error_t atm_cmm_use_services(atm_vc_services_p s);
atm_error_t atm_cmm_unuse_services(atm_vc_services_p s);

atm_error_t atm_cmm_use_esi(atm_esi_p esi);
atm_error_t atm_cmm_unuse_esi(atm_esi_p esi);

atm_error_t atm_cmm_use_ppa(atm_ppa_p ppa);
atm_error_t atm_cmm_unuse_ppa(atm_ppa_p ppa);

atm_error_t atm_cmm_use_vc(atm_vc_p vc);
atm_error_t atm_cmm_unuse_vc(atm_vc_p vc);

atm_uni_call_ie_p atm_cmm_alloc_ie(int num_ie);
void atm_cmm_free_ie(atm_uni_call_ie_p uni);

int atm_cmm_causes(atm_vc_p vp, atm_addr_p addr);
char *atm_cmm_cause2str(atm_error_t);
char *atm_cmm_lerr2str(atm_lerr_t);

unsigned long atm_cmm_grain2cr(atm_ppa_p, unsigned long,atm_direction_t direction);
unsigned long atm_cmm_grain2mod(atm_ppa_p, unsigned long,atm_direction_t direction);
unsigned long atm_cmm_cr2grain(atm_ppa_p, unsigned long,atm_direction_t direction);
unsigned long atm_cmm_maxvccr(atm_ppa_p,atm_direction_t direction);

#ifdef ATM_CMM_TIMING_DEBUG
unsigned long atm_cmm_get_time(void);
#endif
atm_drv_handle_t atm_cmm_find_driver(char *);
#ifdef  _KERNEL
thread_t atm_cmm_new_thread(task_t, void (*)(void *),void *, int, int);
#endif /* _KERNEL */

atm_mib_var_p atm_cmm_create_mib_var(atm_oid_p, int);
atm_error_t atm_cmm_submit_mib_request(atm_cvg_handle_t,
				       atm_ppa_p,
				       atm_mib_request_t,
				       void *,
				       atm_mib_var_p,
				       void (*)(atm_cvg_handle_t,
						void *,
						atm_mib_var_p,
						atm_mib_var_p));
void atm_cmm_free_mib_var(atm_mib_var_p);
#endif
