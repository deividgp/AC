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
 * @(#)$RCSfile: secpolicy.h,v $ $Revision: 4.2.17.4 $ (DEC) $Date: 1995/06/30 22:39:45 $
 */
/*
 * (c) Copyright 1990, 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0.1
 */
/* @(#)secpolicy.h	6.2 15:10:06 2/17/91 SecureWare */

#ifndef __SECPOLICY__
#define __SECPOLICY__

/*
 * Copyright (c) 1988-1990 SecureWare, Inc.  All rights reserved.
 *
 * Based on:
 *	@(#)secpolicy.h	2.6.2.3 14:35:33 12/27/89 SecureWare
 *
 * This is unpublished proprietary source code of SecureWare, Inc. and
 * should be treated as confidential.
 */

#include <sys/secdefines.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/lock.h>
#include <sys/ucred.h>
#include <sys/time.h>
#ifdef _KERNEL
#include <kern/lock.h>
#endif

#if SEC_ARCH
/*
 * The last slot in each object tag pool is reserved to hold an object
 * number for use in indexing into the process bitmaps used to maintain
 * information labels.  We therefore define a new constant for those
 * places that are interested in the number of policy tags, and leave
 * the old one for those places that care about the size of the tag pool.
 */
#if SEC_ILB
#define	SEC_NUM_TAGS	(SEC_TAG_COUNT - 1)
#else
#define	SEC_NUM_TAGS	SEC_TAG_COUNT
#endif

/* Policy independent wildcard tag value */

#define SEC_WILDCARD_TAG_VALUE	0
#define	sec_wildcard(t)		(*(t) == SEC_WILDCARD_TAG_VALUE)

/* Maximum IR size that the kernel can handle */

#define SEC_MAX_IR_SIZE		8192

/*
 * Prototype structure for IRs imbedded in policy daemon messages.
 * The actual data associated with the IR immediately follows the
 * length field.
 */

typedef struct {
	uint_t	ir_length;	/* length of internal representation */
} ir_t;

/* Prototype structure for decisions imbedded in policy daemon messages.
 * The actual data associated with the decision immediately follows the
 * length field.
 */

typedef struct {
	ulong_t	dec_length;	/* decision length */
} dec_t;

/*
 * Indicator for whether the internal representation comes from kernel
 * or user space for SP_MAPTAG().
 */

#define SEC_IR_KERNEL	0
#define SEC_IR_USER	1

/*
 * Security policy module/daemon message types
 */

#define SPD_MAP_TAG		1	/* Map Tag to IR */
#define SPD_SET_TAG		2	/* Set Tag on Object */
#define SPD_MAKE_DECISION	3	/* Make an Access Decision */
#define	SPD_DECISION		4	/* Decision from Daemon */
#define SPD_GET_ATTRIBUTE	5	/* Read IR for Tag */
#define SPD_INTERNAL_REP	6	/* Response with IR for Tag */
#define SPD_CHANGE_DISCR	7	/* Change Discretionary */
#define SPD_NEW_DISCR		8	/* Change Discretionary Response */
#define SPD_SHUTDOWN		9	/* Terminate the Daemon */
#define SPD_SHUTDOWN_RESP	10	/* ACK the Shutdown Request */
#define SPD_PREPARE_SHUTDOWN	11	/* Shutdown Notification */
#define SPD_PREPARE_RESP	12	/* Shutdown Notification Response */
#define SPD_ERROR		13	/* Error Message type */
/*
 * POSIX ACLS
 */
#define SPD_GET_NEW_OBJTAG	14	/* Get Tag For New Object */
#define SPD_SET_NEW_OBJTAG	15	/* Set Tag For New Object */

#define SPD_GET_MAC_CONF	16      /* request macilb configuration */
#define SPD_MAC_CONF		17      /* Response with macilb configuration */

/* 
 * mh_flag for spd_send_message to indicate no wait 
 */
#if SEC_NET
#define TNET_NO_RESP	0x400
#endif

/*
 * Security policy module/daemon message formats
 */

/*********** Common Security Policy Message Header Format ************/

typedef struct spd_message_header {
	long	sync_id;	/* process sync id for driver */
	short	msg_type;	/* request-response type */
	short	mh_flags;	/* state field */
	short	error_code;	/* error return for audit */
} mhdr_t;

#define SPD_MHDR_SIZE	(sizeof(mhdr_t))

/*********** Message Pair for Mapping IRs to Tags ************/

struct spd_map_tag {
	mhdr_t		mhdr;		/* message header */
	udac_t		unixdac;	/* owner/creator uid/gid, mode */
	short		which_tag;	/* policy-specific tag number */
	attrtype_t	ir_type;	/* is tag for subject or object */
	ir_t		ir;		/* IR to be mapped to a tag */
};

#define SPD_MAP_TAG_SIZE	(sizeof(struct spd_map_tag))

struct spd_set_tag {
	mhdr_t		mhdr;		/* message header */
	tag_t		tag;		/* tag returned */
	ulong_t		obj_flags;	/* POSIX ACLS -- SEC_NEW_ID etc. */
	dac_t		obj_discr;	/* object discretionary */
};

#define SPD_SET_TAG_SIZE	(sizeof(struct spd_set_tag))

/*********** Message Pair for Requesting Policy Decisions ************/

struct spd_make_decision {
	mhdr_t	mhdr;			/* message header */
	tag_t	subject;		/* subject tag */
	tag_t	object;			/* object tag */
};

#define SPD_MAKE_DEC_SIZE	(sizeof(struct spd_make_decision))

struct spd_decision {
	mhdr_t	mhdr;			/* message header */
	tag_t	subject;		/* subject tag */
	tag_t	object;			/* object tag */
	dec_t	decision;		/* policy decision */
};

#define SPD_DECISION_SIZE	(sizeof(struct spd_decision))

/*********** Message Pair for Mapping Tags to IRs ************/

struct spd_get_attribute {
	mhdr_t		mhdr;		/* message header */
	tag_t		tag;		/* tag to map to ir */
	attrtype_t	tag_type;	/* subject or object */
};

#define SPD_GET_ATTR_SIZE	(sizeof(struct spd_get_attribute))

struct spd_internal_rep {
	mhdr_t	mhdr;			/* message header */
	tag_t	tag;			/* tag that was mapped */
	ir_t	ir;			/* internal representation */
};

#define SPD_INTERNAL_REP_SIZE	(sizeof(struct spd_internal_rep))

/*********** Message Pair for Discretionary Changes ************/

struct spd_change_discr {
	mhdr_t		mhdr;		/* message header */
	tag_t		object_tag;	/* object tag value */
	dac_t		object_dac;	/* new owner, group, and mode */
	attrtype_t	object_type;	/* subject or object */
	ushort_t	object_flags;	/* indicates which dac changed */
};

#define SPD_CHANGE_DISCR_SIZE	(sizeof(struct spd_change_discr))

struct spd_new_discr {
	mhdr_t		mhdr;		/* message header */
	tag_t		object_tag;	/* new object tag */
	dac_t		object_discr;	/* new owner, group, and mode */
	ushort_t	object_flags;	/* indicates which dac to change */
};

#define SPD_NEW_DISCR_SIZE	(sizeof(struct spd_new_discr))

/*********** POSIX ACLS begin ************/
/*********** Message Pair for Object Creation ************/

struct spd_object_create {
	mhdr_t	mhdr;			/* message header */
	tag_t	access_tag;		/* parents access tag value */
	tag_t	default_tag;		/* parents default tag value */
	edac_t	edac;			/* effective uid and gid */
	int	mode;			/* mode requested */
};

#define SPD_OBJECT_CREATE_SIZE	(sizeof(struct spd_object_create))

struct spd_new_objtag {
	mhdr_t	mhdr;			/* message header */
	tag_t	access_tag;		/* new access tag */
	tag_t	default_tag;		/* new default tag */
	int	mode;			/* mode returned */
};

#define SPD_NEW_OBJTAG_SIZE	(sizeof(struct spd_new_objtag))

/*********** POSIX ACLS end ************/

/*
 * get macilb configuration request/response
 */
struct spd_macilb_config {
    mhdr_t  mhdr;		/* message header			*/
    int     class_length;	/* number of bytes of classifications	*/
    int     cat_length;		/* number of bytes of categories	*/
    int     mark_length;	/* number of bytes of markings		*/
};



/*
 * Error Codes for Message Passing Functions
 */

#define SPD_OK		0		/* No error */
#define SPD_EFULLDB	1		/* Database is full */
#define SPD_ENOSUBJTAG	2		/* No subject tag found */
#define SPD_ENOOBJTAG	3		/* No object tag found */
#define SPD_EBADIREP	4		/* Bad internal representation */
#define SPD_EDEADLOCK	5		/* Re-send message after wait */
#define SPD_EBADMSG	6		/* Bad message type */

/*
 * Map a tag within a policy to a tag pool offset
 */

/*
 * Ioctl Structure Definitions 
 */

/* Structure for SPIOC_INIT and SPIOC_GETCONF commands */

struct sp_init {
	ulong_t		cache_size;		/* number of cache entries */
	ulong_t		cache_width;		/* decision size */
	ushort_t	magic;			/* policy magic number */
	ushort_t	spminor;		/* policy minor device */
	ushort_t	policy;			/* policy number */
	ushort_t	first_subj_tag;		/* first subject tag */
	ushort_t	subj_tag_count;		/* subject tag count */
	ushort_t	first_obj_tag;		/* first object tag */
	ushort_t	obj_tag_count;		/* object tag count */
};

#define SP_INITSIZE	(sizeof(struct sp_init))

/* Structure for SPIOC_INV_TAG command */

struct sp_inv_tag {
	tag_t	tag;			/* tag to invalidate */
};

/* Structure for SPIOC_SET_CACHE_SIZE command */

struct sp_set_cache_size {
	ulong_t	cache_size;		/* new cache size */
	ulong_t	cache_width;		/* new cache width */
};

/* Structure for SPIOC_GET_STATS command */

struct sp_mod_stats {
	ulong_t	decisions;		/* decisions made */
	ulong_t	queries;		/* daemon queries made */
	ulong_t	responses;		/* responses from daemon */
	ulong_t	collisions;		/* cache entry collisions */
	ulong_t	delay;			/* aggregate delay */
	ulong_t	max_delay;		/* maximum decision delay */
	ulong_t	cache_size;		/* number of cache entries */
	ulong_t	cache_width;		/* decision size */
};

#define SP_MOD_STAT_SIZE	(sizeof(struct sp_mod_stats))

#ifdef KERNEL
extern struct sp_mod_stats sp_mod_stats[];
#endif

/**************** Security Policy Configuration Definitions ****************/

/* Security Policy Configuration and Message Driver Files */

#define SP_CONFIG_FILE		"/tcb/files/sp_config"
#define SP_DAEMON_DEVICE	"/dev/spd"

/* Security Policy Configuration Devices */

#define	SPD_CONTROL_DEVICE	"/dev/spdcontrol"
#define SPD_CONTROL_MINOR	0xff		/* minor device number */

/* Security Policy Configuration File Format */

struct sec_policy_conf {
	char	daemon[64];	/* policy daemon executable */
	char	confdir[64];	/* policy daemon config directory */
};

#ifdef KERNEL

/*
 * Each policy daemon may have a decision cache.
 * Cache management routines in sec/spd_cache.c manipulate these cache
 * entries.
 */

#define DCACHE_BUCKETS	4		/* number of cache buckets per slot */

/* Definition of each element of the decision cache */

struct dcache_entry {
	caddr_t	decision;		/* decision pointer */
	tag_t	tag1;			/* first tag to hash */
	tag_t	tag2;			/* second tag to hash */
	time_t	time;			/* LRU time value */
	struct {
		uint_t	valid:1;	/* valid entry flag */
	} dc_flags;
};

/*
 * This is the definition of a decision cache hash slot.
 * 
 *			 MP locking notes
 * On multiprocessor systems, a spin lock exists for each hash
 * slot in a cache.  The lock protects all buckets in that slot.  No
 * thread will ever hold more than one cache slot lock at a time, nor
 * will it pend with a cache slot lock held.
 */
 
struct decision_cache {
	decl_simple_lock_data(, lock)
	struct dcache_entry bucket[DCACHE_BUCKETS];
};

typedef struct decision_cache dec_cache_t;

#define DEC_CACHE_ENTRY_SIZE	(sizeof(struct decision_cache))
#endif /* KERNEL */

#if SEC_ACL
/*
 * Definitions for Access Control Lists
 */

#if SEC_ACL_SWARE

typedef struct {
	udac_t		acl_head;	/* Creator/owner uid/gid, mode */
/*	acle_t		acl_entry[1];	COMMENT - Securieware ACL entries */
} acl_t;

/* SecureWare ACL Internal Representation Structure */

struct acl_ir {
	uint_t	ir_length;		/* length of ir */
	acl_t	ir;			/* ACL header and entries */
};

/* tag allocation */

#define ACL_SUBJ_TAG	0	/* subject identity */
#define ACL_OBJ_TAG	0	/* object access control list */

#define ACL_HEADERSIZE	(sizeof(udac_t))
#endif /* SEC_ACL_SWARE */

#if SEC_ACL_POSIX

typedef struct {
	cdac_t		acl_head;	/* Creator uid/gid */
/*	acl_data_t	acl_entry[1];	COMMENT - POSIX ACL en tries */
} pacl_t;

/* POSIX ACL Internal Representation Structure */
struct acl_ir {
	uint_t	ir_length;		/* length of ir */
	pacl_t	ir;			/* ACL header and entries */
};

#define PACL_SUBJ_TAG		0	/* subject identity */
#define PACL_OBJ_ACCESS_TAG	0	/* object access control list */
#define PACL_OBJ_DFLT_TAG	1	/* default access control list */

#define PACL_HEADERSIZE (sizeof(cdac_t))

#endif /* SEC_ACL_POSIX */

/* Access Control List Policy Special Tag Values */

#define SEC_ACL_NULL_TAG	1L	/* empty ACL-no access */

/* Access Control List Cache Decision Format */

struct acl_decision {
	ulong_t	dec_length;		/* decision length */
	struct {
		uint_t	read:1,		/* subject may read object */
			write:1,	/* subject may write object */
			exec:1,		/* subject may execute object */
			delete:1,	/* subject may delete object */
			rfu:28;
	} dec;
};

typedef struct acl_decision acl_dec_t;

#define ACL_DECISION_SIZE	(sizeof(struct acl_decision) - sizeof(long))

struct acl_cache_decision {
	struct {
		uint_t	read:1,		/* subject may read object */
			write:1,	/* subject may write object */
			exec:1,		/* subject may execute object */
			delete:1,	/* subject may delete object */
			rfu:28;
	} decision;
};

typedef struct acl_cache_decision acache_dec_t;

#define	ACL_CACHE_WIDTH	(sizeof(struct acl_cache_decision))

#endif /* SEC_ACL */

#if SEC_MAC

/*
 * Definitions for Mandatory Access Control
 */

/* MAC Special Tag Values */

#define SEC_MAC_WILDCARD_TAG    SEC_WILDCARD_TAG_VALUE
					/* grant access to all */
#define SEC_MAC_NULL_TAG	1L	/* no access */
#define SEC_MAC_SYSLO_TAG	2L	/* system lo tag */
#define SEC_MAC_SYSHI_TAG	3L	/* system hi tag */

/* MAC tag allocation */

#define MAND_SUBJ_SL_TAG	0	/* subject sensitivity label */
#define MAND_OBJ_SL_TAG		0	/* object sensitivity label */
#define MAND_SUBJ_CL_TAG	1	/* subject clearance */
#if SEC_ILB
#define MAND_SUBJ_IL_TAG	2	/* subject information label */
#define MAND_OBJ_IL_TAG		1	/* object information label */
#endif

/* MAC Internal Representation Structure */

/*
 * class_ir_t must be the same size as CLASSIFICATION in std_labels.h.
 */
typedef long class_ir_t;

struct mac_ir {
	uint_t		ir_length;	/* length of ir */
	class_ir_t	class;		/* classifications */
					/* compartments and markings follow */
};

#define MAC_IR_SIZE	(sizeof(struct mac_ir))

/* MAC Decision Format */

struct mac_decision {
	ulong_t	dec_length;		/* decision length */
	struct {
		uint_t	subj_dom:1,	/* subject dominates object */
			obj_dom:1,	/* object dominates subject */
			same:1,		/* levels are equal */
			incomp:1,	/* levels are incomparable */
#if SEC_ILB
			nocomb:1,	/* labels can't be combined */
			ilb_subj_dom:1,	/* subject IL dominates object IL */
			ilb_obj_dom:1,	/* object IL dominates subject IL */
			ilb_same:1,	/* subject and object are same IL */
			rfu:24;
#else
			rfu:28;
#endif
	} dec;
#if SEC_ILB
	tag_t	combination;
#endif
};

typedef struct mac_decision mac_dec_t;

#define MAC_DECISION_SIZE	(sizeof(struct mac_decision) - sizeof(long))

/* MAC Cache Decision Format */

struct mac_cache_decision {
	struct {
		uint_t	subj_dom:1,	/* subject dominates object */
			obj_dom:1,	/* object dominates subject */
			same:1,		/* levels are equal */
			incomp:1,	/* levels are incomparable */
#if SEC_ILB
			nocomb:1,	/* labels can't be combined */
			ilb_subj_dom:1,	/* subject IL dominates object IL */
			ilb_obj_dom:1,	/* object IL dominates subject IL */
			ilb_same:1,	/* subject and object are same IL */
			rfu:24;
#else
			rfu:28;
#endif
	} decision;
#if SEC_ILB
	tag_t	combination;
#endif
};

typedef struct mac_cache_decision mcache_dec_t;

#define	MAC_CACHE_WIDTH	(sizeof(struct mac_cache_decision))

/* Return values from mac_getdecision */

#define	MAC_SDOM	1
#define	MAC_ODOM	2
#define	MAC_INCOMP	4
#define	MAC_SAME	8
#if SEC_ILB && !defined(ILB_SDOM)
#define	ILB_SDOM	0x10
#define	ILB_ODOM	0x20
#define	ILB_SAME	0x40
#endif /* SEC_ILB && !defined(ILB_SDOM) */

#endif /* SEC_MAC */
#endif /* SEC_ARCH */

#define SPOLICY_CNT     1

/*
 * Security Policy Magic Numbers for Configuraton Recognition
 * Changes to these definitions must be reflected in the policy_name[]
 * table in seccmd/reduce.h.
 */

#if SEC_ARCH
#define SEC_ACL_MAGIC		0xf000	/* SecureWare Access Control Lists */
#define SEC_MAC_MAGIC		0xf001	/* Mandatory Access Control */
#define SEC_NCAV_MAGIC		0xf003	/* Nationality Caveats */
#define SEC_MACILB_MAGIC	0xf004	/* MAC and Information Labels */
#endif /* SEC_ARCH */

#define SEC_PACL_MAGIC		0xf010	/* POSIX Access Control Lists */

#define SEC_MAGIC_MAX		SEC_PACL_MAGIC

#if SEC_ARCH
#define	SEC_MAGIC_COUNT		(((unsigned short) SEC_MAGIC_MAX - \
					(unsigned short) SEC_ACL_MAGIC) + 1)
#endif /* SEC_ARCH */

#ifdef KERNEL
/*
 * This is the definition of the Security Policy Switch. This
 * switch serves as the connection between the various security
 * policy checks such as access or object create and the Security
 * Modules that are responsible for making the policy decisions.
 */

struct sec_module_desc {
	int	(*sw_init)	(/* policy */);
	int	(*sw_config)	(/* policy */);
	int	(*sw_access)	(/* subjtags, objtags, mode, dcheck, udac */);
	int	(*sw_obj_create)(/* subjtags, objtags, partags, attrtype */);
	int	(*sw_obj_delete) (/* subjtags, objtags, attrtype */);
	int	(*sw_getattr)	(/* attrtype, tag, attr */);
	int	(*sw_setattr)	(/* attrtype, tags, tagnum, new */);
	int	(*sw_setattr_check) (/* objtype, objp, parent, tags, tagnum, new */);
	int	(*sw_maptag) 	(/* attrtype, tagnum, attr, udac, new */);
	int 	(*sw_verify_ir) (/* attr, tagnum */);
	int	(*sw_policy_check) (/* Policy #, attr_num */);
	uint_t	sw_magic;
	uint_t	sw_priv_required;
	char	sw_subj_count;
	char	sw_obj_count;
	char	sw_first_subj_tag;
	char	sw_first_obj_tag;
};

extern struct sec_module_desc sp_switch[];
extern int spolicy_cnt;

/*
 * Macros to access elements of the policy switch
 */
#define	SP_INIT(policy)		(*sp_switch[policy].sw_init)(policy)
#define SP_CONFIG(policy)	(*sp_switch[policy].sw_config)(policy)
#define SP_VERIFY_IR(policy, kattr, dac, update, len)\
	(*sp_switch[policy].sw_verify_ir)(kattr, dac, update, len)

#define	SP_GETATTR(policy,attrtype,tag,attr)\
	(*sp_switch[policy].sw_getattr)(attrtype,tag,attr)
#define	SP_SETATTR(policy,attrtype,tags,tagnum,new)\
	(*sp_switch[policy].sw_setattr)(attrtype,tags,tagnum,new)
#define	SP_SETATTR_CHECK(policy,objtype,objp,par,tags,tagnum,new)\
	(*sp_switch[policy].sw_setattr_check)(objtype,objp,par,tags,tagnum,new)
#define	SP_MAPTAG(policy,attrtype,tagnum,attr,udac,new)\
	(*sp_switch[policy].sw_maptag)(attrtype,tagnum,attr,udac,new)

#define	OBJECT_TAG(policy,which)  (sp_switch[policy].sw_first_obj_tag + which)
#define	SUBJECT_TAG(policy,which) (sp_switch[policy].sw_first_subj_tag + which)
#define	SUBJECT_TAG_COUNT(policy) (sp_switch[policy].sw_subj_count)
#define	OBJECT_TAG_COUNT(policy)  (sp_switch[policy].sw_obj_count)

/*
 * Security Policy Miscellaneous Function Table
 */

struct sec_functions {
	int	(*sw_owner)		(/* owner, creator */);
	int	(*sw_change_subj)	();
	int	(*sw_change_obj)	(/* tags, newdac, flags */);
	int	sw_discr_index;
#if SEC_ILB
	int	(*sw_check_float)	(/* rw, tags, new */);
	void	(*sw_do_float)		(/* rw, tags, new */);
	void	(*sw_empty_object)	(/* tags */);
#endif
};

extern struct sec_functions sp_functions;

/*
 * Macros to call members of the sec_functions table
 */

#define	sec_owner(ouid,cuid)	(*sp_functions.sw_owner)(ouid, cuid)

#define	SP_CHANGE_SUBJECT()	\
	(security_is_on ? (*sp_functions.sw_change_subj)() : 0)
#define	SP_CHANGE_OBJECT(tags,newdac,flags)\
	(security_is_on ? (*sp_functions.sw_change_obj)(tags,newdac,flags) : 0)

#if SEC_ILB
#define	SP_CHECK_FLOAT(rw,tags,new)\
	(security_is_on ? (*sp_functions.sw_check_float)(rw,tags,new) : 0)
#define	SP_DO_FLOAT(rw,tags,new)\
	if (security_is_on) (*sp_functions.sw_do_float)(rw,tags,new)
#define	SP_EMPTY_OBJECT(tags)\
	if (security_is_on) (*sp_functions.sw_empty_object)(tags)
#endif /* SEC_ILB */


#if SEC_ARCH
/*
 * Macros and declarations for tag pools that are allocated separately
 * from their associated object data structures (IPC objects and ptys).
 */

extern tag_t semtag[], shmtag[], msgtag[];

#define SEMTAG(sp,t)	(&semtag[((((sp) - sema) * SEC_TAG_COUNT) + (t))])
#define SHMTAG(sp,t)	(&shmtag[((((sp) - shmem) * SEC_TAG_COUNT) + (t))])
#define MSGTAG(mp,t)	(&msgtag[((((mp) - msgque) * SEC_TAG_COUNT) + (t))])

#else

/*
 * Define the actions that are to be done, should end up in acl.h
 */

#ifdef SEC_IPC_ACL
extern struct secatttr_info *semtag[], *shmtag[], *msgtag[];

#define SEM_SECATTR(sp)	sp->sem_secattr
#define SHM_SECATTR(sp)	sp->s.shm_secattr
#define MSG_SECATTR(mp)	mp->msg_secattr
#else
#define SEM_SECATTR(sp)	NULL
#define SHM_SECATTR(sp)	NULL
#define MSG_SECATTR(mp)	NULL
#endif /* SEC_IPC_ACL */

#endif /* SEC_ARCH */

#if SEC_ILB
/*
 * External declarations for console/xcons tag pools
 */

extern tag_t contag[];

#define CONSOLETAG(tag)	(&contag[((0) * SEC_TAG_COUNT) + (tag)])
#define XCONSTAG(tag)	(&contag[((1) * SEC_TAG_COUNT) + (tag)])
#endif

#if SEC_PTY

extern tag_t ptctag[], ptstag[];

#define	PTCTAG(d,t)	(&ptctag[(minor(d) * SEC_TAG_COUNT) + (t)])
#define	PTSTAG(d,t)	(&ptstag[(minor(d) * SEC_TAG_COUNT) + (t)])

#endif /* SEC_PTY */

/*
 * External declarations for policy specific information (sec_conf.c)
 */

#if SEC_ACL_SWARE
extern int aclpolicy, aclobjtag, aclsubjtag;
#endif /* SEC_ACL_SWARE */

extern int paclpolicy;
#if SEC_ACL_POSIX
extern int paclobjtag, paclsubjtag;
#endif /* SEC_ACL_POSIX */

#if SEC_MAC
extern int macpolicy, macobjtag, macsubjtag, macclrnce;
#endif /* SEC_MAC */

#if SEC_ILB
extern int ilbobjtag, ilbsubjtag;
#endif

#if SEC_ILB

/*
 * Macros and declarations for Information Label Policy
 */

#define	SEC_OBJNUM(o)	((int) (o)[SEC_NUM_TAGS])
#define	SEC_SETOBJNUM(o,n)	((o)[SEC_NUM_TAGS] = (tag_t)(n))
#define	SEC_OBJ_BITS(o)	(&sec_obj_bits[SEC_OBJNUM(o) * sec_obj_mapwords])
#define	sp_free_bits(t)

extern mask_t	*sec_obj_bits;		/* pointer array for object bitmaps */
extern mask_t	*sec_objnummap;		/* object number allocation bitmap */
extern int	sec_curobjmap;		/* current index into sec_objnummap */
extern int	sec_lastobjmap;		/* indx of last word in sec_objnummap */
extern int	nsocket;		/* num of dynamic objects (sockets) */
extern int	sec_nobject;		/* number of objects in the system */
extern int	sec_firstdynobj;	/* first dynamic object number */
extern int	sec_obj_mapwords;	/* num of mask_t's in an obj bitmap */
extern int	sec_subj_mapwords;	/* num of mask_t's in a subj bitmap */

extern mask_t	*sp_bitmap_alloc();

#endif /* SEC_ILB */

struct sec_prop_attrs {
	char *attr_name;
	int (*access)();
	int (*validate)();
	int (*completion)();
	int (*data_free)();
	int (*build_sec_struct)();
	int decision_mask;
	struct sec_prop_attrs *next_entry;
};

typedef struct {
	struct sec_prop_attrs 	*sec_type;	
	void   			*sec_struct;
} proplist_sec_attrs_t;

extern struct sec_prop_attrs	*sec_init_prop(char *, int (*)(), int (*)(),
				   int (*)(), int (*)(), int (*)(), int);

/*******************************************************************************
 * Macros used for the property list code interfacing with the various security
 * policies.
 ******************************************************************************/
 

/******************************************************************************
 * SEC_PROP_BUILD_SEC
 *
 * The macro calls into the policy specific code that builds the argument list
 * for the operation if the property list name is designated to be a security
 * attribute and the operation pointer is not NULL.  The routine called into
 * allocates a data structure that the policy understandsd and assigns it to
 * sec_info.sec_struct casting it to a void pointer.  This space is freed by
 * calling the macro SEC_PROP_DATA_FREE.
 *
 * Expects:
 *	error:		integer where the error code is stored.
 *	sec_info:	Security information structure.
 *	name:		Name of the Property list.
 *	vp:		vnode pointer to the object.
 *	cred:		The credentials for this user.
 * 	data:		The attribute that is being set.
 *	len:		length of the attibute setting.
 *	op:		The type of operation performing.
 *
 * Sets error to:
 *	Success:	Returns 0, and the field  sec_info.sec_struct is 
 *			assigned a allocated data address that the policy
 *			understand.
 *	Failure:	Returns ENOMEM
 ******************************************************************************/

#define SEC_PROP_BUILD_SEC(error, sec_info, name, vp, cred, data, len, op) \
	do { \
        	if((sec_info).sec_type && \
		   (sec_info).sec_type->build_sec_struct)  { \
			error = 	\
			   (sec_info).sec_type->build_sec_struct(&(sec_info), \
	                   name, vp, cred, data, len, op); \
		} else	\
			error = 0; \
	} while(0)

/******************************************************************************
 * SEC_PROP_ACCESS
 *
 * Verifies that the subject has the required permissions to
 * perform the requested operation.  This routine depends on the success of
 * SEC_PROP_BUILD_SEC.
 *
 * Expects:
 *	decision:	The access decision.
 *	sec_info:	Security information structure built by 
 *			SEC_PROP_BUILD_SEC
 *	vp:		vnode pointer to the object.
 *	cred:		The credentials for this user.
 *	type:		The operation that is being performed, set,
 *			retrieve etc..
 *
 * Sets error to:
 *	Success:	Returns 0
 *	Failure:	EACCES if error not to be surpressed
 *			EPERM  if error is to be surpressed
 ******************************************************************************/

#define SEC_PROP_ACCESS(decision, sec_info, vp, cred, type) \
	do { \
        	if((sec_info).sec_type && (sec_info).sec_type->access && \
		   ((sec_info).sec_type->decision_mask & type))  { \
                	decision = (sec_info).sec_type->access(vp, \
							       cred, type); \
		} else \
			decision = 0; \
	} while(0)

/******************************************************************************
 * SEC_PROP_VALIDATE
 *
 * Validate the attribute is vallid by the policy standards.  This expects that
 * SEC_PROP_BUILD_SEC succeded.
 *
 * Expects:
 *	error:		integer where the error code is stored.
 *	sec_info:	Security information structure built by 
 *			SEC_PROP_BUILD_SEC
 *	op:		The type of operation being performed (set/retrieve/
 *			delete).
 *
 * Sets error to:
 *	Success:	Returns 0
 *	Failure:	Returns EINVAL or other error defined by the 
 *			policy validation routine.
 ******************************************************************************/

#define SEC_PROP_VALIDATE(error, sec_info, vp, op) \
	do { \
 	       if((sec_info).sec_type && (sec_info).sec_type->validate) { \
                	error =  \
			  (sec_info).sec_type->validate((sec_info).sec_struct, \
                          vp, op); \
		} else \
			error = 0; \
	} while(0)

/******************************************************************************
 * SEC_PROP_COMPLETION
 *
 * The setting of the proplerty list has succeded, know call the policy specific
 * code for handling caching of the attribute and other policy specific 
 * operations. This expects the following:
 *
 * Setting the ACL:
 * 	That SEC_PROP_BUILD_SEC, SEC_PROP_ACCESS,
 * 	SEC_PROP_VALIDATE and setproplist call succeded.
 *
 * Retrieving the ACL:
 * 	That SEC_PROP_BUILD_SEC, SEC_PROP_ACCESS,
 * 	SEC_PROP_VALIDATE and getproplist call succeded.
 *
 * Expects:
 *	sec_info:	Security information structure built by 
 *			SEC_PROP_BUILD_SEC
 *
 * Returns nothing as any return information is meaningless at this time.
 ******************************************************************************/

#define SEC_PROP_COMPLETION(error, sec_info, type, vp) \
	do { \
        	if((sec_info).sec_type && (sec_info).sec_type->completion)  {  \
			error = (sec_info).sec_type->completion(&(sec_info), \
				type, vp); \
		} else \
			error = 0; \
	} while(0)

/******************************************************************************
 * SEC_PROP_DATA_FREE
 *
 * Releases the data held by sec_info that was allocated by SEC_PROP_BUILD_SEC.
 * Expects that SEC_PROP_BUILD_SEC succeded.
 *
 * Expects:
 *	sec_info:	Security information structure built by 
 *			SEC_PROP_BUILD_SEC
 *
 * Returns nothing as any return information is meaningless at this time.
 ******************************************************************************/

#define SEC_PROP_DATA_FREE(sec_info) \
	do {	\
        	if((sec_info).sec_type && (sec_info).sec_type->data_free && \
		   (sec_info).sec_struct)  { \
	                (sec_info).sec_type->data_free(&(sec_info));  \
		} \
	} while(0)


#ifdef SEC_IPC_ACL
extern int setlabel(struct proc *, void *, long *);
extern int getlabel(struct proc *, void *, long *);
extern int sec_attrs_test(u_long, u_long, u_int);
#endif

#endif /* KERNEL */
#endif /* __SECPOLICY__ */
