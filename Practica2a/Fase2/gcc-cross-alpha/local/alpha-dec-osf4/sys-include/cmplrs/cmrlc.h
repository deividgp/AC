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
 * @(#)$RCSfile: cmrlc.h,v $ $Revision: 1.1.11.2 $ (DEC) $Date: 1997/02/07 20:42:07 $
 */


/*
**  cmrlc.h	- External interface definition for compact relocation code.
**
**	This file defines the external interfaces for producers and
**	consumers of compact relocations.
*/

#ifndef _CMRLC_H_
#define _CMRLC_H_

#include <stdio.h>


struct 	obj;
struct 	reloc;


/*
****************************************************************************
**                                                                        **
**          Interfaces for producers of compact relocations               **
**                                                                        **
****************************************************************************
*/


/*
 * These constants indicate what information must be returned by the
 * 'pf_get_scn_info()' call-back function.  See 'cmrlc_create_init()' below.
 */
typedef enum {
    CMRLC_SCNINFO_START,   	/* final linked address of given section */
    CMRLC_SCNINFO_SIZE,    	/* final linked size of given section */
    CMRLC_SCNINFO_OBJSTART,	/* first address of section in 'obj' */
    CMRLC_SCNINFO_OBJSIZE, 	/* size of section in 'obj' */
    CMRLC_SCNINFO_OBJRAW   	/* pointer to 'obj's raw section data */
} cmrlc_scninfo_t;


/*
**  Prepare for creating compact relocation information.  Must be called
**  once before any other cmrlc_create_* routine.  The arguments to this
**  routine define several call-back functions that the other cmrlc_create_*
**  routines use to obtain some information.  Aside from the
**  'pf_get_scn_info()' function, the behavior of the call-backs need not be
**  defined until the producer calls 'cmrlc_create_gensection()'.
**
**  'pf_get_scn_info()' must place the data requested by 'info' at the
**  location pointed by 'pdata'.  This function should return 0 if it is
**  successful, and 1 on error.  The 'obj' parameter is not defined when
**  requesting CMRLC_SCNINFO_START or CMRLC_SCNINFO_SIZE since these
**  are not tied to a specific object.
*/
void cmrlc_create_init(
	unsigned long  	(*pf_get_gpvalue)(  	/* call-back to get GP value */
	    unsigned long     	obj,         	    /* opaque object ID */
	    unsigned          	section,     	    /* R_SN_* constant */
	    unsigned long     	vaddr),      	    /* addrs in section */
	const EXTR *   	(*pf_get_symr)(     	/* call-back to get ext SYMR */
	    unsigned long     	obj,         	    /* opaque object ID */
	    unsigned long     	indx),       	    /* external sym indx */
	unsigned long  	(*pf_get_exp_vaddr)(	/* call-back for expr r_vaddr */
	    unsigned long     	obj,         	    /* opaque object ID */
	    const struct reloc	*preloc),    	    /* expression reloc */
	int            	(*pf_get_scn_info)( 	/* call-back for section info */
	    unsigned long     	obj,         	    /* opaque object ID */
	    const char *      	scn_name,    	    /* section name */
	    cmrlc_scninfo_t   	info,        	    /* requested info */
	    unsigned long *   	pdata));     	    /* returned data */


/*
**  Prepare for creating compact relocation information.  Must be called
**  once for each COFF section before any call to cmrlc_create_gensection().
**  Producers may optionally avoid calling this function for sections that
**  are known not to contain any relocation records.
**
**  The 'start' parameter gives the first virtual address of the given
**  section in the final linked executable.
*/
void cmrlc_create_scn_init(
	const char *     	name, 	/* section name */
	unsigned long    	start,	/* first virtual address */
	unsigned long    	size);	/* size in bytes */


/*
**  Create compact relocation information for an object's section.  Must
**  be called once for each section with relocation entries in each
**  object.  Calls must be made such that the virtual address always
**  increases from one call to the next for any given section.
**
**  The 'raw_vaddr' parameter is the address of the first byte of this
**  object section data in the final linked executable.  The 'rvbias'
**  parameter is a constant to add to the 'r_vaddr' field of each relocation
**  entry so the fields match the final linked addresses for this section.
**  The 'rvbias' is not used to bias any expression relocation entries.
**  Instead, the 'pf_get_exp_vaddr' call-back is is used to bias these
**  addresses.
**
**  While this call is executing, the call-backs from 'cmrlc_create_init'
**  must be defined to do the following:
**
**  	'pf_get_gpvalue' : Must return the GP-value of any virtual
**  	    address within the object and section being processed.
**  	    The 'vaddr' parameter passed to this call-back is an address
**  	    within the final linked executable.
**
**  	'pf_get_symr' : Must return a pointer to the external symbol
**  	    corresponding to the given symbol index.  The index is from
**  	    a relocation record in 'relocs'.
**
**  	'pf_get_exp_vaddr' : Must return the virtual address corresponding
**  	    to the final linked executable for the given non-store expression
**  	    relocation entry (an entry with an R_OP_* type other than
**  	    R_OP_STORE).
*/
void cmrlc_create_gensection(
	unsigned long     	obj,      	/* opaque object ID */
	const char *      	scn_name, 	/* section name */
	void *            	raw,      	/* section data */
	unsigned long     	raw_size, 	/* num bytes of section data */
	unsigned long     	raw_vaddr,	/* first addrs of section */
	const struct reloc	relocs[], 	/* section relocation records */
	unsigned long     	nrelocs,  	/* number relocation records */
	long              	rvbias);  	/* bias for reloc's r_vaddr's */


/*
**  Create a compact relocation record for an R_GPVALUE relocation.
**  Producers call this routine to indicate a change in GP value when
**  there is no actual R_GPVALUE relocation to indicate the change.
*/
void cmrlc_create_gpval(
    unsigned long	obj,        	/* opaque object ID */
    const char * 	scn_name,   	/* section name */
    unsigned long	vaddr,      	/* final-link address of change */
    unsigned     	filegp_off);	/* offset of new GP from file's GP */


/*
**  Retrieve the compact relocation information for an entire executable.
**  Must be called exactly once after all relevant sections of all objects
**  have been processed by 'cmrlc_create_gensection()'.  '*praw' is set to
**  the beginning of the raw compact relocation data.  Returns the length
**  (in bytes) of the raw data.
*/
int cmrlc_create_getdata(
	void ** 	praw);


/*
**  Clean up after creating compact relocation information.  Must be
**  called after all compact relocation processing has been completed.
**  Data returned by 'cmrlc_create_getdata()' is no longer valid after
**  this call.
*/
void cmrlc_create_fini(void);



/*
****************************************************************************
**                                                                        **
**          Interfaces for consumers of compact relocations               **
**                                                                        **
****************************************************************************
*/


/*
 * Version identifiers returned by cmrlc_version().
 * Error conditions are less than zero.  Supported versions are
 * non-negative and increasing with increasing functionality.
 */
typedef enum {
    CMRLC_VER_UNSUPPORTED = -2,	/* unsupported version */
    CMRLC_VER_FAIL = -1,       	/* no compact relocation information */
    CMRLC_VER_FIRST = 0,       	/* initial version */
    CMRLC_VER_DYNSYM = 1,      	/* fixed .dynsym relocations */
    CMRLC_VER_STABLE = 2       	/* miscellaneous bug fixes */
} cmrlc_ver_t;


/*
 * Values for reloc_mask in cmrlc_read_init().
 */
#define CMRLC_RLC_REFLONG   	(1<<0)
#define CMRLC_RLC_REFQUAD   	(1<<1)
#define CMRLC_RLC_GPREL32   	(1<<2)
#define CMRLC_RLC_GPDISP    	(1<<3)
#define CMRLC_RLC_BRADDR_BSR	(1<<4)	/* BRADDR's for bsr's only */
#define CMRLC_RLC_BRADDR    	(1<<5)	/* BRADDR's for all branches */
#define CMRLC_RLC_HINT_JSR  	(1<<6)	/* HINT's for jsr's only */
#define CMRLC_RLC_HINT      	(1<<7)	/* HINT's for jsr's and jmp's */
#define CMRLC_RLC_SREL16    	(1<<8)
#define CMRLC_RLC_SREL32    	(1<<9)
#define CMRLC_RLC_SREL64    	(1<<10)
#define CMRLC_RLC_STACK     	(1<<11)	/* all OP_* relocations */
#define CMRLC_RLC_GPVALUE   	(1<<12)
#define CMRLC_RLC_IMMED  	(1<<13)
#define CMRLC_RLC_TLS_HIGH      (1<<14)
#define CMRLC_RLC_TLS_LOW       (1<<15)
#define CMRLC_RLC_ALL        \
    (CMRLC_RLC_REFLONG     | \
     CMRLC_RLC_REFQUAD     | \
     CMRLC_RLC_GPREL32     | \
     CMRLC_RLC_GPDISP      | \
     CMRLC_RLC_BRADDR      | \
     CMRLC_RLC_HINT        | \
     CMRLC_RLC_SREL16      | \
     CMRLC_RLC_SREL32      | \
     CMRLC_RLC_SREL64      | \
     CMRLC_RLC_STACK       | \
     CMRLC_RLC_GPVALUE     | \
     CMRLC_RLC_TLS_HIGH    | \
     CMRLC_RLC_TLS_LOW     | \
     CMRLC_RLC_IMMED)


/*
**  Return the version identifier of the object's compact relocation
**  information.  Tools should call this to ensure that compact
**  relocations exist for a file, that the revision of the compact
**  relocation information is still supported, and that the information
**  encoded in those relocations is sufficient for its needs.
**  Higher revision levels are guaranteed to support all functionality
**  from lower revision levels.
*/
cmrlc_ver_t cmrlc_version(
	struct obj *	pobj);


/*
**  Get the GP value in effect at the given virtual address.
**  Returns OBJ_FAIL if the given address is out of range or is not
**  associated with a section that has a GP value.  Also Returns OBJ_FAIL
**  if the compact relocation information has been stripped from the given
**  object.
*/
unsigned long cmrlc_get_gpvalue(
	struct obj *  	pobj,
	unsigned long 	vaddr);


/*
**  Prepare for reading compact relocation information from the given object.
**  Subsequent calls to cmrlc_read_next() will return relocation records
**  from the section specified in 'section_name'.  Only those relocations
**  specified in 'reloc_mask' will be reported.  cmrlc_read_init() must
**  be called before cmrlc_read_next().  cmrlc_read_init() may be re-called
**  at any time to restart the list of relocations returned.
**
**  Returns OBJ_FAIL if there is no compact relocation information for the
**  given object or if the specified section name or relocation mask is
**  invalid.  Otherwise, returns 0.
*/
int cmrlc_read_init(
	struct obj * 	pobj,
	const char * 	section_name,
	unsigned long	reloc_mask);


/*
**  Report the next relocation from the list requested in the last call
**  to cmrlc_read_init().  Set '*preloc' to the new relocation.
**  Relocations are always reported as local, never external.  Their
**  format is the same as is defined in <reloc.h>.
**  Returns OBJ_FAIL if there are no more relocations from the requested
**  list.  Otherwise, returns 0.
*/
int cmrlc_read_next(
	struct obj *  	pobj,
	struct reloc *	preloc);


/*
**  Read binary compact relocation data from the given object and write
**  a human-readable form to 'fout'.
**  Returns OBJ_FAIL if data is corrupt, 0 otherwise.
*/
int cmrlc_print(
	struct obj *  	obj,
	FILE *        	fout);


#endif /* _CMRLC_H_ */
