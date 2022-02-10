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
 * @(#)$RCSfile: acl.h,v $ $Revision: 1.1.3.13 $ (DEC) $Date: 1996/01/03 06:18:56 $
 */

/*	Copyright (c) 1988 SecureWare, Inc.  All rights reserved.

	This Module contains Proprietary Information of SecureWare, Inc.
	and should be treated as Confidential.

	This is the include file for Access Control List Defines and
	Structure Definitions.

	acl.h	5.1 15:35:34 8/15/90
	Based on:
	  "acl.h	2.1 12:33:23 1/25/89"
*/




#ifndef __ACL__

#define __ACL__

#include <sys/sp_attr.h>
#include <sys/secpolicy.h>
#include <sys/security.h>
#include <sys/proplist.h>
#include <sys/types.h>
#include <sys/sec_objects.h>
#include <sys/vnode.h>
#include <sys/acl_def.h>


#define ACL_VERSION     1
#define ACL_MIN_ENTRIES         3

extern int paclpolicy;
#define ACLS_ENABLED    0
#define ACLS_NOT_LOADED 1
#define ACLS_NOT_ENABLED -1

/*  POSIX acl types
 */
typedef struct acl_entry *acl_entry_t;	/* library working storage acl entry descriptor */
typedef uint_t acl_perm_t;		/* permission(s) */
typedef acl_perm_t *acl_permset_t;	/* pointer to set of permissions */
typedef struct acl *acl_t;		/* library working storage acl descriptor */
typedef uint_t acl_tag_t;		/* type of acl entry */
typedef uint_t  acl_type_t;		/* type of acl (access, default, etc.) */

/*  obsolecent acl types
 */
typedef acl_tag_t acl_entry_type;
typedef acl_tag_t acl_tag_type;

/*  acl_perm_t values
 */
#define ACL_EXECUTE		0x001
#define ACL_WRITE		0x002
#define ACL_READ		0x004

/* obsolecent defines...
 */
#define ACL_NOPERM                0x0
#define ACL_PEXECUTE              0x1
#define ACL_PWRITE                0x2
#define ACL_PREAD                 0x4

#define ACL_PADD                 0x10
#define ACL_PREMOVE              0x20
#define PERM_CTRL               0x008
#define PERM_INSERT             0x010
#define PERM_DELETE             0x020
#define PERM_MODIFY             0x040
#define PERM_LOOKUP             0x080
#define PERM_EXTEND             0x100
#define MAX_ACL_PERM		0x1ff

#define ACL_PRDWR               (ACL_PREAD|ACL_PWRITE)
#define ACL_PRDEX               (ACL_PREAD|ACL_PEXECUTE)
#define ACL_PWREX               (ACL_PWRITE|ACL_PEXECUTE)
#define ACL_PRDWREX             (ACL_PREAD|ACL_PWRITE|ACL_PEXECUTE)

#define VALID_PERMS(perm) \
	(perm & ~MAX_ACL_PERM)


/*  acl_tag_t values - type of acl entry
 *  compatible with the dce values
 */
#define ACL_USER_OBJ 		0	/* user mode bits */
#define ACL_GROUP_OBJ		1	/* group mode bits */
#define ACL_OTHER		2	/* other mode bits - draft 15 name */
#define ACL_DCE_USER		3	/* user entry, DCE UUID */
#define ACL_DCE_GROUP		4	/* group entry, DCE UUID */
	/* hole			5-7 */
#define ACL_DCE_FOREIGN_USER	8	/* user entry, DCE UUIDs for cell and user */
#define ACL_DCE_FOREIGN_GROUP	9	/* group entry, DCE UUIDs for cell and group */
#define ACL_DCE_FOREIGN_OTHER	10	/* other entry in specific cell, DCE UUID for cell */
#define ACL_DCE_UNAUTH		11	/* DCE unauthenticated request */
	/* hole			12 */
#define ACL_DCE_OTHER		13	/* DCE none of the above */
	/* hole			14-22 */
#define ACL_USER		23	/* user entry, uid_t */
#define ACL_GROUP		24	/* group entry, gid_t */
#define ACL_MASK		25	/* POSIX permission mask - not implemented */
#define NUM_TAG_TYPES           ACL_MASK
#define ACL_UNDEFINED_TAG	NUM_TAG_TYPES+1

#undef USE_MASK_OBJ			/* not fully implemented */

/*  obsolecent acl_tag_t values - for backward compatibility only
 *  will be deleted in a future release
 */
#define USER_OBJ        ACL_USER_OBJ
#define GROUP_OBJ       ACL_GROUP_OBJ
#define OTHER_OBJ       ACL_OTHER
#define ACL_OTHER_OBJ	ACL_OTHER	/* draft 13 name */
#define DCE_USER        ACL_DCE_USER
#define DCE_GROUP       ACL_DCE_GROUP
#define FOREIGN_USER    ACL_DCE_FOREIGN_USER
#define FOREIGN_GROUP   ACL_DCE_FOREIGN_GROUP
#define FOREIGN_OTHER   ACL_DCE_FOREIGN_OTHER
#define UNAUTH          ACL_DCE_UNAUTH
#define ANY_OTHER       ACL_DCE_OTHER
#define USER_OTHER      ACL_USER
#define GROUP_OTHER     ACL_GROUP
#define ACL_MASK_OBJ	ACL_MASK
#define MASK_OBJ        ACL_MASK

/*  acl_type_t values
 *  originals defined in <sys/acl_def.h>
 *
 *	POSIX name:		other name:		proplist entry name:
 */
#define ACL_TYPE_ACCESS		ACL_TYPE_ACC		/* "DEC_ACL_ACC" */
#define ACL_TYPE_DEFAULT	ACL_TYPE_DEF		/* "DEC_ACL_DEF" */
#define ACL_TYPE_DEFAULT_DIR	ACL_TYPE_DEF_DIR	/* "DEC_ACL_DEF_DIR" */

/*  invalid user-id and group-id qualifiers
 */
#define ACL_UNDEFINED_UID	((uid_t)-2)
#define ACL_UNDEFINED_GID	((uid_t)-2)
#define BOGUS_UID               ACL_UNDEFINED_UID
#define BOGUS_GID               ACL_UNDEFINED_GID

/*  representation of an acl entry identifier (qualifier)
 */
typedef    union {
        	struct { 
			uid_t         id;       /* user or group */
                } uid;                   	/* for ACL_USER, ACL_GROUP */
#if 0	/* Turn on when DCE comes */
        	struct { 
                    	uuid_t        id;       /* DCE user or group */
                    } uuid;                  	/* for [delegated or not]
					           ACL_DCE_USER, ACL_DCE_GROUP */
        	struct {
                    	uuid_t        id;       /* DCE user or group */
                    	uuid_t        realm;    /* DCE cell */
                    } for_uuid;              	/* for [del or not]
						   ACL_DCE_FOREIGN_USER,
						   ACL_DCE_FOREIGN_GROUP */
        	struct {
                    uuid_t        realm;     /* DCE cell */
                    } for_cell;              /* for [del or not]ACL_DCE_OTHER */
        	struct {
                    uchar         data[1];   /* actual size given by "size" */
                    } other;                 /* for any unknown types */
#endif /* DCE */
        }acl_id;

#define ACL_UID_SIZE    sizeof(uid_t)

#define ACL_STAND_IS_ALIGN(addr) \
        ((long) addr & (ACL_UID_SIZE - 1))


/*  "Opaque" internal acl data structure
 *  subject to change
 */

/*  required entries
 */
typedef struct {
        acl_perm_t user_obj_perm;
        acl_perm_t group_obj_perm;
        acl_perm_t other_obj_perm;
	uint_t pad;	/* force a long word alignment of
			 * any following data.
			 */
} acl_unix_perm_t;

/*  common to all extended acl entries
 */
typedef struct {
        acl_tag_t  entry_type;
	acl_perm_t	entry_perm;
	uint_t		idsize;
	uint_t pad;	/* force a long word alignment of
			 * any following data.
			 */
} aclenthead_t;

/*  a (variable length) acl entry
 */
typedef struct {
	aclenthead_t	acl_common;
        acl_id          acl_id;
} acle_t;

#define acl_type	acl_common.entry_type
#define acl_perm	acl_common.entry_perm
#define acl_uid 	acl_id.uid.id
#define acl_gid 	acl_id.uid.id

/*  obsolecent -- only works with fixed size entries
 */
#define ACL_IR_SIZE     sizeof(acle_t)	

/*  The internal representation portion of an acl.
 *  This is the "ir" field in an attribute_t structure.
 *  The attribute_t structure contains the version and length info.
 */
typedef struct {
        acl_unix_perm_t unix_perms;
        acle_t          acl_entries;
} acl_ir_t;


/*      how to flatten an acl
 */
#define ACFL_DCEANON 0          /* anonymous access for DCE */
#define ACFL_NFSREST 1          /* restrictive access for NFS */
#define ACFL_NFSPERM 2          /* permissive access for NFS */
#define ACFL_NONE    0		/* no flattening for NFS */
#define ACFL_NFSMIN  ACFL_NONE
#define ACFL_NFSMAX  ACFL_NFSPERM

/*	how to format an acl into text
 */
#define ACFT_NUMIDS	0x01	/* use numeric ids instead of names */
#define ACFT_SHORT	0x02	/* use ',' to separate entries instead of '\n' */
#define ACFT_TERSE	0x04	/* use abbreviated entry types ("u" vs "user", etc.) */
#define ACFT_WHITE	0x08	/* add whitespace in short form (not posix formatting) */
#define ACFT_NPERM	0x10	/* use numeric permissions instead of symbolic */

#ifndef KERNEL

/*  acl_mod_perm() opcodes
 */
#define ACL_ADD_PERM	0
#define ACL_DELETE_PERM 1
#define ACL_SET_PERM	2
#define ACL_GET_PERM	3


/* "Opaque" working storage acl entry
 *  subject to change
 */
struct acl_entry{
	acle_t		*entry;
	void		*head;
	struct acl_entry	*next;
	struct acl_entry	*prev;
	int 		acl_magic;
	int 		size;
};


/* "Opaque" working storage acl
 *  subject to change
 */
struct acl {
        int             acl_magic;      /* validation member */
        int             acl_num;        /* number of actual acl entries */
	int		acl_alloc_size; /* size available in the acl */
	acl_entry_t     acl_current;    /* pointer to current entry in the linked list */
        acl_entry_t     acl_first;      /* pointer to ACL linked list */
	attribute_t	*attr_data;	/* Pointer to the attr data */
};

#ifndef POSIX_LIB

/*  acl storage management
 */
extern acl_t		acl_dup(const acl_t);
extern int		acl_free(acl_t);
extern acl_t		acl_init(size_t);

/*  acl entry manipulation - complete entries
 */
extern acl_entry_t	acl_create_entry(acl_t *acl_p);
#define			acl_create_entry(acl_p) \
				allocate_acl_entry(acl_p,sizeof(acle_t))
extern acl_entry_t	acl_get_entry(acl_t);
extern int              acl_delete_entry(acl_entry_t);
extern int              acl_copy_entry(acl_entry_t ,acl_entry_t );
extern int		acl_valid(acl_t,acl_entry_t *);
extern int              acl_first_entry(acl_t);

/*  acl entry manipulation - fields in an entry
 */
extern int		acl_add_perm(acl_permset_t permset_d, const acl_perm_t perm_d);
#define			acl_add_perm(permset,acl_perm) \
				acl_mod_perm(NULL,permset,NULL,acl_perm,ACL_ADD_PERM)
extern int		acl_clear_perm(acl_permset_t permset_d);
#define			acl_clear_perm(permset) \
				acl_mod_perm(NULL,permset,NULL,MAX_ACL_PERM,ACL_DELETE_PERM)
int			acl_delete_perm(acl_permset_t permset_d, acl_perm_t perm_d);
#define			acl_delete_perm(permset,acl_perm) \
				acl_mod_perm(NULL,permset,NULL,acl_perm,ACL_DELETE_PERM)
int			acl_get_permset(const acl_entry_t entry_d, acl_permset_t *permset_p);
#define			acl_get_permset(entry,permset) \
				acl_mod_perm(entry,NULL,permset,0,ACL_GET_PERM)
int			acl_set_permset(acl_entry_t entry_d, const acl_permset_t permset_d);
#define			acl_set_permset(entry,permset)	\
				acl_mod_perm(entry,permset,NULL,0,ACL_SET_PERM)
extern void *           acl_get_qualfier(acl_entry_t);
extern int		acl_get_tag_type(const acl_entry_t, acl_tag_t *);
extern int              acl_set_qualifier(acl_entry_t ,int *);
extern int              acl_set_tag_type(acl_entry_t , const acl_tag_t );
extern int              acl_free_qualifier(void * ,acl_tag_t);

/*  acl manipulation on an object
 */
extern acl_t		acl_get_fd(const int fd, const acl_type_t type_d);
#define			acl_get_fd(file_fd,acl_type) \
				acl_get(&file_fd,acl_type,OT_FILE_DESCR)
extern acl_t		acl_get_file(const char *path_p, const acl_type_t type_d);
#define			acl_get_file(path,acl_index) \
				acl_get(path,acl_index,OT_REGULAR)
extern int		acl_set_fd(const int fd, const acl_type_t type_d, const acl_t acl_d);
#define			acl_set_fd(file_fd,acl_type,acl_d) \
				acl_set(&file_fd,acl_type,acl_d,OT_FILE_DESCR)
extern int		acl_set_file(const char *path_p, const acl_type_t type_d, const acl_t acl_d);
#define			acl_set_file(path,acl_type,acl_d) \
				acl_set(path,acl_type,acl_d,OT_REGULAR)
extern int		acl_delete_def_fd(const int fd);
#define			acl_delete_def_fd(file_fd) \
				acl_set(file_fd,ACL_TYPE_DEF,NULL,OT_FILE_DESCR)
extern int		acl_delete_def_file(const char *path_p);
#define			acl_delete_def_file(path) \
				acl_set(path,ACL_TYPE_DEF,NULL,OT_REGULAR)

/*  acl format translation
 */
extern char *		acl_to_text(const acl_t ,ssize_t *);
extern acl_t		acl_from_text(const char *);
extern ssize_t		acl_copy_ext(void *prop_val, acl_t acl_d, ssize_t prop_len);
extern acl_t		acl_copy_int(const void *prop_val);
extern ssize_t		acl_size(const acl_t);
extern int		acl_free_text(const char *buf_p);
#define			acl_free_text(buff) \
				free(buff)

/*  Digital extensions
 */
acl_entry_t		acl_add_entry(acl_t *pacl_d, acl_tag_t type, acl_perm_t perm, ssize_t size, void *id);
extern acl_entry_t	allocate_acl_entry(acl_t *,int);
extern int		acl_mod_perm(acl_entry_t , acl_permset_t, acl_permset_t *, acl_perm_t,int);
extern int		acl_set(void *, int , acl_t ,int );
extern char *		acl_to_fmt_text(const acl_t acl_d, ssize_t *plen, int fmt);
extern acl_t		acl_get(void *, int ,int );
extern char *		acl_ext_to_text(const void *prop_val, ssize_t *len, int fmt);
extern char *		convert_to_er(char *acl, acle_t *entry, int fmt);
extern int		isaclprop(const char *name);
acl_entry_t		acl_find_entry(acl_t acl_d, acl_tag_t type, ssize_t idsize, void *pid);
#define			acl_delete_def_dir_file(path) \
				acl_set(path,ACL_TYPE_DEF_DIR,NULL,OT_REGULAR)
#define			acl_delete_def_dir_fd(file_fd) \
				acl_set(file_fd,ACL_TYPE_DEF_DIR,NULL,OT_FILE_DESCR)
#define			acl_delete_access_file(path) \
				acl_set(path,ACL_TYPE_ACC,NULL,OT_REGULAR)
#define			acl_delete_access_fd(file_fd) \
				acl_set(file_fd,ACL_TYPE_ACC,NULL,OT_REGULAR)
#if SEC_IPC_ACL
#define			acl_set_ipc(ipc_des,acl_type,acl_d,ipc_type) \
				acl_set(ipc_des,acl_type,acl_d,ipc_type)
#define			acl_get_ipc(ipc_des,acl_index,ipc_type) \
				acl_get(ipc_des,acl_index,ipc_type)
#endif /* SEC_IPC_ACL */
#endif /* POSIX_LIB */

#endif /* ndef KERNEL */

/*
 * MACRO to take the perms in the ACL header and convert it to
 * the standard mode bits, acl_ir is expected to be an acl_ir_t
 * data type.
 */

#define BUILD_PERMS(acl_ir,perm) \
	do { \
		perm = ((acl_ir)->unix_perms.user_obj_perm & 0007) << 6; \
		perm |= ((acl_ir)->unix_perms.group_obj_perm & 0007) << 3; \
		perm |= ((acl_ir)->unix_perms.other_obj_perm & 0007); \
	} while(0)


/*
 * MACRO to take the perms and place them in the ACL header.
 * acl_ir is expected to be an acl_ir_t data type.
 */

#define SET_PERMS(acl_ir,perm) \
	do { \
		(acl_ir)->unix_perms.user_obj_perm &=~ 07; \
		(acl_ir)->unix_perms.user_obj_perm |= ((perm)>>6) & 07; \
		(acl_ir)->unix_perms.group_obj_perm &=~ 07; \
		(acl_ir)->unix_perms.group_obj_perm |= ((perm)>>3) & 07; \
		(acl_ir)->unix_perms.other_obj_perm &=~ 07; \
		(acl_ir)->unix_perms.other_obj_perm |= (perm) & 07; \
	} while(0)

/*
 * MACRO for calling the acl_locate routine to find a given entry in
 * the ACL. ir_entry is expected to be an acl_ir_t data type, check
 * and acle_t *  to the information looking up, and end is an acle_t
 * pointer returned by the ACL_ENTRY_END_ADDRESS MACRO.
 */
/*	XXX this should be moved into pacllib.c, since acl_locate_id()
 *	is local to that file, and the version in the kernel has a
 *	different number of args.
 */
#define ENTRY_CHECK(ir_entry,check,end) \
	(acl_locate_id((acle_t *) &ir_entry->acl_entries,&check,end))

#ifndef roundup
#define roundup(x, y) \
	((((x) + (y) - 1) / y) * y)
#endif

/*
 * This macro is used to advance to the next entry in the ACL.
 * Note that we add in the size of the acl_id and then subtract
 * the ACL_STANDARD_ID_SIZE from it, this is because sizeof(acle_t)
 * always contains the  ACL_STANDARD_ID_SIZE.  The subtraction operation
 * only becomes of interest for variable length records.
 */

#define ACL_ENTRY_ADDRESS(acle) \
	((acle_t *) ((caddr_t) acle + (sizeof(aclenthead_t)+ \
 	   roundup(((acle_t *)acle)->acl_common.idsize, sizeof(ulong_t)))))

/*
 * Return the pointer to the last acle_t+1 record.
 */

#define ACL_ENTRY_END_ADDRESS(attr) \
	((acle_t *) (((caddr_t) attr) + ((attribute_t *)attr)->ir_length - \
	sizeof (aclenthead_t) + 1))

#define MIN_ACL_IR_LEN \
	(sizeof (attribute_t) - NUMB_IR_CHARS + sizeof(acl_unix_perm_t))

#ifdef KERNEL

/*  completion routine state
 */
typedef 	struct {
			char  *name;
        		struct vnode *vp;
			struct ucred *cred;
			attribute_t *attr;
			struct vattr vattr;
			int udac_update;
			int prop_len;
			int type;
		} acl_prop_params_t;

extern int	acl_ir_cache_delete(secinfo_t *, int);
extern int	attr_retrieve(attr_mask_t, struct vnode *);
extern int	attr_set(struct vnode *, attr_mask_t, attribute_t *);
extern int     	pacl_build_sec_struct(proplist_sec_attrs_t *, char *,
           	  struct vnode *, struct ucred *, attribute_t *, int, int) ;
extern int     	pacl_proplist_data_free(proplist_sec_attrs_t *);
extern int     	pacl_proplist_validate( acl_prop_params_t *, struct vnode *, int);
extern int 	pacl_fs_set(struct vnode *, attr_mask_t, attribute_t *);

extern attribute_t 	*pacl_fs_get(struct vnode *, attr_mask_t);
extern acl_perm_t pacl_flatten(attribute_t *attr, int how);

extern acle_t 	*buildacl(void *, int, acle_t *, acl_tag_t, acl_perm_t, void *, int);

#endif

#ifdef ACL_DEC_REGISTER /* { */
/*
 * Structure that contains the information for making an
 * evaluation decision based on the obj type.
 */

typedef		struct {
			char		*name;		  /* Name of entry */
			int		(*dec_match_p)(); /* Pointer to the
							   * supplied decision
							   * routine for the
							   * acl entry types
							   * that are not 
							   * defined by
							   * POSIX.
							   */
			acl_tag_t	type;		  /* Type of entry */
			int		mode_type;	  /*
							   * What field of the
							   * mode does the type
							   * apply to.
							   */
			int		eval_order;	  /*
							   * Order of 
							   * evaluation for
							   * this entry.								   */
		} acl_dec_reg_t;


extern int acl_dec_register(acl_type_t, int, int, int (*)(), char *, int);

/* this is the "return access for a user" routine for the registry
 * code, not to be confused with anonymous access/nfs flattened acls
 */
extern mode_t	xx_pacl_flatten(attribute_t *, udac_t *, struct ucred *);

#define 	ACL_EVAL_ENTRY(x,y) \
			((acl_dec_reg_t *) x + y)

/* class of access for tag registration
 */
#define		ACL_MODE_USER	0	/* Mode applies to the USER perms */
#define		ACL_MODE_GROUP	1	/* Mode applies to the GROUP perms */
#define		ACL_MODE_OTHER	2	/* Mode applies to the OTHER perms */

/* order for tag registration
 */
#define		ACL_REG_BEFORE	0	/* Insert the entry before the designated type. */
#define		ACL_REG_AFTER	1	/* Insert the entry after the designated type. */

#endif /* ACL_DEC_REGISTER } */

#endif /* __ACL__ */
