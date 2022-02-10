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
 * @(#)$RCSfile: st.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1998/04/28 15:13:56 $
 */
/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
#ifndef _ST_H_
#define _ST_H_
/*
 * Routine and data definitions for utilizing the libst functions.
 * Libst provides capabilities for accessing object files,
 * including executables, .o files, and shared libraries.
 * These functions are of use in developing tools which analyze
 * object file data structures or need to access file, procedure,
 * symbol, or line number information.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <filehdr.h>
#include <scnhdr.h>
#include <aouthdr.h>
#include <reloc.h>
#include <symconst.h>
#include <scncomment.h>

typedef struct st_obj st_obj_t;
typedef struct st_objlist st_objlist_t;


/* Object file type enumeration.  Used by st_object_type() */
typedef enum {	ST_OTYPE_UNKNOWN,
		ST_ARCHIVE, 		/* Object is an archive */
		ST_OMAGIC, 		/* OMAGIC file */
		ST_NMAGIC, 		/* NMAGIC file */
		ST_ZMAGIC		/* ZMAGIC file */
} st_object_type_t;

/* Typedefs for routine arguments */
typedef unsigned long st_addr_t;	/* Address */
typedef unsigned long st_any_t;		/* For foreach routines */
typedef unsigned long st_file_t;	/* File handle */
typedef unsigned long st_proc_t;	/* Procedure handle */
typedef unsigned long st_sym_t;		/* Symbol handle */
typedef int 	      st_line_t;	/* Line number */
typedef char          st_char_t;        /* Usually for a pointer to char */
typedef unsigned long st_cmscn_t;	/* Comment section handle */
typedef unsigned int  st_cm_sscn_t;     /* Comment subsection handle */

/* Routine return value.  0 for success.  Positive return value is errno
 * from a system call.  A negative number is a library error.
 * Library errors are documented below.
 */
typedef int st_status_t;

typedef enum {
	False,
	True
} st_bool_t;

/*
 * Open flags for an object
 */
#define ST_RDONLY	0x01		/* Read only (the default)  */
#define ST_MANGLE_NAMES 0x10		/* Don't demangle C++ names
					   Names are demangled by default */
#define ST_FORCE	0x80		/* Override version checks and open obj */

/*
 * Libst routine definitions.
 * Routines provide support for creating and managing objects (.o, executable,
 * or shared library) and lists of objects.
 * Interface routines provide access to object file header information and the 
 * symbol table.  The symbol table contains information on the source files, 
 * procedures, symbols, symbol type/class/size information, and lines.
 * Access is provided where applicable to obtain information at the list, 
 * object and source file level.
 * For example, the number of procedures in the entire object can be
 * obtained, or the number of procedures in a particular file.
 *
 * Routines return opaque handles for objects, files, procedures, symbols, etc.
 */

#if !defined(_ST_INTERNAL)
/*** Object type/open/close routines ***/

/*
 * Determines if object is an archive, OMAGIC, NMAGIC or ZMAGIC file.
 * See object file type enumeration above for return values.
 */
st_status_t st_object_type(const char *filename, st_object_type_t *otype);

/*
 * Open object (executable, .o, .so, or .a) for access.  Object is 
 * memory mapped if possible, otherwise memory is dynamically allocated 
 * for it.
 * See #defines for open flags for a description of open options.
 */
st_status_t
st_obj_open(st_obj_t **obj, const char *name, unsigned int flags);

/*
 * Close object and free memory used by it, with the exception of dynamically
 * allocated symbol names.  Use st_free_name() to free symbol name memory.
 */
st_status_t
st_obj_close(st_obj_t *obj);

/*
 * Identity and access routines for archives.  Use st_obj_open() to open
 * an archive, st_ar_member_next to access each archive member.
 */

/* Sets "is_archive" to True if obj is an archive */
st_status_t st_is_obj_archive(st_obj_t *obj, st_bool_t *is_archive);

/* Read in next archive member.  Returns status of ST_E_ARCHIVE_END when
 * there are no more members.  Use st_* routines to access information
 * about the archive object.  For example, st_obj_name() returns the
 * archive member's file name.
 */
st_status_t st_ar_member_next(st_obj_t *obj);

/*** Object list routines ***/

/* If *obj_list is NULL, create a list and append the given obj to it.
 * Otherwise, append obj to existing list.
 */
st_status_t st_objlist_append(st_objlist_t **obj_list, st_obj_t *obj);

/* Obtain pointer to first object on the list. */
st_status_t st_objlist_first(st_objlist_t *obj_list, st_obj_t **obj);

/* Obtain pointer to last object on the list. */
st_status_t st_objlist_last(st_objlist_t *obj_list, st_obj_t **obj);

/* Call st_obj_close for each object on the list and free the list. */
st_status_t st_objlist_close(st_objlist_t *obj_list);

/*
 * Call routine once for each object on the list.
 * Returns 0 if called routine returns 0.  Returns ST_OBJ_END if end
 * of object list is reached.
 */
st_status_t st_foreach_obj(
		st_objlist_t *obj_list, 
		st_status_t  (*routine) __((st_obj_t *obj, 
					    st_any_t data, 
			   		    st_any_t *retval)),
    		st_any_t     data,
    		st_any_t     *retval);

/* Sets "result" to the obj containing the specified text, data, or bss address. */
st_status_t st_addr_to_obj(st_objlist_t *obj_list, 
			   st_addr_t    addr, 
			   st_obj_t     **result);

/* Sets "result" to the obj containing the specified file */
st_status_t st_file_to_obj(st_objlist_t *obj_list, 
			   st_file_t     file, 
			   st_obj_t     **result);

/* Sets "result" to the obj containing the specified procedure */
st_status_t st_proc_to_obj(st_objlist_t *obj_list, 
			   st_proc_t    proc, 
			   st_obj_t     **result);

/* Sets "result" to the obj containing the specified symbol */
st_status_t st_sym_to_obj(st_objlist_t *obj_list, 
			   st_sym_t    sym, 
			   st_obj_t     **result);

/* Sets "sym" to the handle of first symbol found matching the given name */
st_status_t st_objlist_external_name_sym(st_objlist_t *obj_list,
			     		 const char   *name,
			     		 st_sym_t     *sym);

/*** Object routines ***/

/* Check if object is sharable, e.g. a .so file */
st_status_t st_is_obj_shared(st_obj_t *obj, st_bool_t *shared);

/* Check if object is call-shared, e.g. uses shared libraries */
st_status_t st_is_obj_call_shared(st_obj_t *obj, st_bool_t *cs);

/* Check if object's symbol table is stripped */
st_status_t st_is_obj_stripped(st_obj_t *obj, st_bool_t *stripped);

/* Return handle of first source file in the object */
st_status_t st_obj_file_start(st_obj_t *obj, st_file_t *fstart);

/* Return count of files in the object */
st_status_t st_obj_file_count(st_obj_t *obj, unsigned int *nfiles);

/* Return next file handle for the object */
st_status_t st_obj_file_next(st_obj_t *obj, st_file_t fcur, st_file_t *fnext);

/* Return handle of first procedure in the object */
st_status_t st_obj_proc_start(st_obj_t *obj, st_proc_t *pstart);

/* Return count of procedures in the object */
st_status_t st_obj_proc_count(st_obj_t *obj, unsigned int *nprocs);

/* Return next procedure handle for the object */
st_status_t st_obj_proc_next(st_obj_t *obj, st_proc_t pcur, st_proc_t *pnext);

/* Return first symbol handle for the object */
st_status_t st_obj_sym_start(st_obj_t *obj, st_sym_t *sym_start);

/* Return next symbol handle for the object */
st_status_t st_obj_sym_next(st_obj_t *obj, st_sym_t sym, st_sym_t *sym_next);

/* Return number of symbols (local and external) in the object */
st_status_t st_obj_sym_count(st_obj_t *obj, unsigned int *nsyms);

/* Return handle of first local symbol in the object */
st_status_t st_obj_lsym_start(st_obj_t *obj, st_proc_t *lsym_start);

/* Return count of local symbols in the object */
st_status_t st_obj_lsym_count(st_obj_t *obj, unsigned int *nlsyms);

/* Return handle of next local symbol in the object */
st_status_t st_obj_lsym_next(st_obj_t *obj, st_sym_t sym, st_sym_t *lsym_next);

/* Return handle of first external symbol in the object */
st_status_t st_obj_esym_start(st_obj_t *obj, st_proc_t *esym_start);

/* Return count of external symbols in the object */
st_status_t st_obj_esym_count(st_obj_t *obj, unsigned int *nesyms);

/* Return handle of next external symbol in the object */
st_status_t st_obj_esym_next(st_obj_t *obj, st_sym_t sym, st_sym_t *esym_next);

/* Return the name of the object */
st_status_t st_obj_name(st_obj_t *obj, char **name);

/* Return text start address from the object file */
st_status_t st_obj_text_start(st_obj_t *obj, st_addr_t *text);

/* Return the size of the text segment */
st_status_t st_obj_text_size(st_obj_t *obj, unsigned long *tsize);

/* Return data start address from the object file */
st_status_t st_obj_data_start(st_obj_t *obj, st_addr_t *data);

/* Return the size of the data segment */
st_status_t st_obj_data_size(st_obj_t *obj, unsigned long *dsize);

/* Return bss start address from the object file */
st_status_t st_obj_bss_start(st_obj_t *obj, st_addr_t *bss);

/* Return the size of the bss segment.  */
st_status_t st_obj_bss_size(st_obj_t *obj, unsigned long *bsize);

/* Convert a file's text or data address to the equivalent address for the 
 * object file in mapped/allocated in memory.
 * Bss address translations aren't meaningful, since no bss segment data
 * data exists in the mapped/allocated region.
 */
st_status_t st_obj_mem_addr(st_obj_t	*obj, 
			    st_addr_t 	file_addr, 
			    st_addr_t 	*mem_addr);

/*** File routines ***/

/* Return source language type for file, as defined in symconst.h */
st_status_t st_file_lang(st_obj_t *obj, st_file_t file, unsigned int *lang);

/* Return the name of the file. */
st_status_t st_file_name(st_obj_t *obj, st_file_t file, char **fname);

/* Check if file is stripped of local symbols */
st_status_t st_is_file_locally_stripped(st_obj_t  *obj, 
					st_file_t file, 
					st_bool_t *stripped);

/* Return the handle of the first procedure for this file. */
st_status_t st_file_proc_start(st_obj_t  *obj, 
			       st_file_t file, 
			       st_proc_t *pstart);

/* Return the count of the procedures in this file */
st_status_t st_file_proc_count(st_obj_t		*obj, 
			       st_file_t 	file, 
			       unsigned int 	*pcount);

/* Return next procedure handle for the file */
st_status_t st_file_proc_next(st_obj_t *obj, 
			      st_file_t file, 
			      st_proc_t pcur,
			      st_proc_t *pnext);

/* Sets isym to the handle of the first symbol for the given file. */
st_status_t st_file_sym_start(st_obj_t *obj, st_file_t file, st_sym_t *isym);

/*** Procedure routines ***/

/* Determine if procedure is an alternate entry or nested procedure */
st_status_t st_is_alternate_entry(st_obj_t *obj, st_proc_t proc, st_bool_t *alt);

/* Get procedure address */
st_status_t st_proc_addr(st_obj_t *obj, st_proc_t proc, st_addr_t *proc_addr);

/* Get procedure symbol */
st_status_t st_proc_sym(st_obj_t *obj, st_proc_t proc, st_sym_t *symbol);

/* Get procedure name */
st_status_t st_proc_name(st_obj_t *obj, st_proc_t proc, char **name);

/* Get file handle for the given procedure. */
st_status_t st_proc_to_file(st_obj_t *obj, st_proc_t proc, st_file_t *file);

/* Get the starting line number for this procedure */
st_status_t st_proc_start_line(st_obj_t *obj, st_proc_t proc, st_line_t *sline);

/* Get the ending line number for this procedure */
st_status_t st_proc_end_line(st_obj_t *obj, st_proc_t proc, st_line_t *eline);

/* Get ending line of the enclosing procedure.  Useful when procedure 
 * is an alternate entry or is nested.
 */
st_status_t st_outer_proc_end_line(st_obj_t  *obj, 
				   st_proc_t proc,
				   st_line_t *eline);

/* Check if line number is in the range of a procedure.
 * Line number is treated as an unsigned long so this routine can
 * be called from st_foreach_proc.  If line number is in range, set
 * ipd to the procedure handle.  Sets ipd to -1 if line not in procedure.
 */
st_status_t st_check_proc_line_range(st_obj_t      *obj, 
		    	 	     st_proc_t     proc, 
		    	 	     unsigned long line, 
		    	 	     st_proc_t     *ipd);

/*
 * Create and sort a table of procedures by address.
 * Enables binary search operations on the procedure addresses by other 
 * routines.  The other routines that require a sorted procedure table will 
 * call this routine if the sorted procedure table doesn't exist.
 */
st_status_t st_proc_sort(st_obj_t *obj);

/* Get handle of first procedure in the sorted list */
st_status_t st_proc_sorted_start(st_obj_t *obj, st_proc_t *proc);

/* Get handle of procedure at the next highest address.  Calls st_proc_sort()
 * if sorted procedure list doesn't exist.
 */
st_status_t st_proc_sorted_next(st_obj_t *obj, st_proc_t proc, st_proc_t *result);

/* Call routine for each procedure in the given file.  Returns 0 when called
 * routine returns 0.  Returns ST_PROC_END if end of procedures was reached.
 */
st_status_t st_foreach_proc(st_obj_t	*obj,
			    st_file_t	file,
			    st_status_t (*routine) __((st_obj_t	 *obj,
			         		       st_proc_t procedure,
			    	 		       st_any_t  data,
						       st_any_t *result)),
			    st_any_t    data,
			    st_any_t    *result);

/* Call routine for each procedure in the object.  Returns 0 when called routine
 * returns 0.  Returns ST_PROC_END if end of procedures was reached.
 */
st_status_t st_foreach_obj_proc(st_obj_t *obj,
		    	        st_status_t (*routine) __((st_obj_t  *obj,
			 	       	       	           st_proc_t procedure,
			    	               	           st_any_t  data,
					       	           st_any_t  *result)),
		    	        st_any_t data,
		    	        st_any_t *result);

/* Call routine for each procedure in the sorted procedure list.  Calls
 * st_proc_sort() if sorted list doesn't exist.  Returns 0 when called routine
 * returns 0.  Returns ST_PROC_END if end of procedures was reached.
 */
st_status_t st_foreach_obj_proc_sorted(st_obj_t *obj,
			               st_status_t (*routine) __((st_obj_t *obj,
			    			                  st_proc_t proc,
			    			      		  st_any_t data,
			    			      		  st_any_t *result)),
			   	       st_any_t data,
			   	       st_any_t *result);

/*** Symbol routines ***/

/*
 * Get the symbol value.
 * For procedures, data or bss symbols, the value is the address.
 * For members of structures or unions, the value is the offset to
 * the field from the start of the structure.
 * For local symbols or arguments, the value is its relative offset from 
 * the procedure's frame pointer.
 */
st_status_t st_sym_value(st_obj_t *obj, st_sym_t symbol, unsigned long *value);

/* Get symbol type, as defined in symconst.h */
st_status_t st_sym_type(st_obj_t 	*obj, 
			st_sym_t 	symbol, 
			unsigned int 	*sym_type);

/* Get symbol class, as defined in symconst.h */
st_status_t st_sym_class(st_obj_t 	*obj, 
			 st_sym_t 	symbol, 
			 unsigned int 	*sym_class);

/* Check if symbol handle falls in the local portion of the symbol table.
 */
st_status_t st_is_sym_local(st_obj_t *obj, st_sym_t symbol, st_bool_t *local);

/* Check if symbol handle falls in the global section of the symbol table.
 */
st_status_t st_is_sym_global(st_obj_t *obj, st_sym_t symbol, st_bool_t *global);

/* Get file handle for the given symbol */
st_status_t st_sym_to_file(st_obj_t *obj, st_sym_t symbol, st_file_t *file);

/* Get symbol name.  Name buffer may be dynamically allocated if C++ name
 * demangling is enabled, or it may point into the object's string table
 * if demangling was not needed.  st_free_name() is provided for releasing
 * the memory.
 */
st_status_t st_sym_name(st_obj_t    *obj, 
	    	        st_sym_t    symbol, 
	    	        char        **name);

/* Get copy of symbol name.  The null-terminated name is copied to name_buf.
 * buflen is the length of the supplied name buffer.
 * If the name is longer than the supplied buffer, the truncated argument is
 * set to the number of characters truncated.  This interface avoids returning
 * dynamically allocated buffers for demangled C++ names, so no calls to
 * st_free_name are needed, but is more overhead for non-C++ names.
 */
st_status_t st_sym_name_copy(st_obj_t    *obj, 
	         	     st_sym_t    symbol, 
	         	     char        *name_buf,
	         	     int	 buflen,
	         	     int         *truncated);

/* Release memory for allocated name if it is outside the range of the
 * object file in memory.
 */
void st_free_name(st_obj_t *obj, char *name);

/* Set the name demangling flags for the object.  Flags are defined in
 * /usr/include/cmplrs/demangle_string.h.  Name demangling for C++ names
 * will occur for an object unless this call is made to disable it.
 */
st_status_t st_set_mangled_name_flag(st_obj_t *obj, unsigned int flag);

/* Get the current settings of the name demangling flags */
st_status_t st_get_mangled_name_flag(st_obj_t *obj, unsigned int *flag);

/* Return the symbol of the enclosing block or procedure for the 
 * given symbol
 */
st_status_t st_sym_to_outer_scope_sym(st_obj_t *obj,
				      st_sym_t symbol,
				      st_sym_t *osym);

/* Get handle of the symbol marking the end of this block */
st_status_t st_end_sym(st_obj_t *obj, st_sym_t symbol, st_sym_t *esym);

/* Get handle of symbol marking the end of the procedure containing symbol */
st_status_t st_proc_end_sym(st_obj_t *obj, st_sym_t symbol, st_sym_t *esym);

/* Get the symbol of the named global symbol */
st_status_t st_external_name_sym(st_obj_t   *obj, 
				 const char *name, 
				 st_sym_t  *osym);

/* Get the symbol corresponding to the specified frame offset in the proc.
 * The frame_offset must be a positive number and a relative offset from the 
 * virtual frame pointer for a procedure.  Frequently, but not always, this
 * is the stack pointer.  If an instruction references a local variable with
 * 20($sp), then the frame_offset would be 20.
 * The symbol returned may be a parameter to the procedure or a local symbol.
 * byte-offset returns the offset into the variable that the frame_offset
 * corresponds to, and is always >= 0.  The byte_offset from a variable may
 * span compiler temporaries on the stack.  To check this case, use st_sym_size
 * to obtain the size of the returned symbol.
 */
st_status_t st_frame_offset_to_sym(st_obj_t	*obj, 
		       		   st_proc_t    proc,
		       		   int 	 	frame_offset,
		       		   st_sym_t  	*osym,
				   int		*byte_offset);

/* Get the size of the named symbol */
st_status_t st_sym_size(st_obj_t *obj, st_sym_t s, unsigned long *size);

/*** Address routines ***/

/* Set file to handle of file containing supplied text address */
st_status_t st_addr_to_file(st_obj_t *obj, st_addr_t pc, st_file_t *file);

/* Get procedure containing given address. */
st_status_t st_addr_to_proc(st_obj_t *obj, st_addr_t pc, st_proc_t *proc);

/* Get the line number corresponding to the given address. */
st_status_t st_addr_to_line(st_obj_t *obj, st_addr_t address, st_line_t *line);

/* Get the symbol corresponding to the given data/bss address.  Data addresses
 * on the heap is not handled by this routine.
 */
st_status_t st_data_addr_to_sym(st_obj_t *obj, 
				st_addr_t addr, 
		    		st_sym_t *sym, 
		    		int *byte_offset);

/*** String routines - translate codes to printable strings. ***/

/* Return string for file's language, e.g. Fortran or C */
st_status_t st_lang_str(st_obj_t *obj, st_file_t file, char *buf, 
		        int buflen);

/* Return string for a symbol's type, e.g. Static or Global */
st_status_t st_type_str(st_obj_t *obj, unsigned int type, char *buf, 
		        int buflen);

/* Return string for a symbol's class, e.g. Text or Data */
st_status_t st_class_str(st_obj_t *obj, unsigned int sym_class, char *buf, 
			 int buflen);

/*** Error routines ***/

/* Places error message string in buf */
st_status_t st_strerror(st_status_t errcode, char *buf, int buflen);


/*** Versioning routines **/

/* Returns the vstamp values this libst was built with. */
st_status_t st_get_known_versions(unsigned short *, unsigned short *);


/* Opens the object file and reads only the portions necessary to
 * access the vstamps in the a.out and symbolic headers.  Calls
 * a decompression routine if necessary.  Does not handle archives.
 */
st_status_t st_get_format_versions(char *, unsigned short *, 
		       unsigned short *);


/* Does the same thing as st_get_format_versions(), but
 * reads from the "praw" memory pointer.  Assumes "praw"
 * points to the file header of an uncompressed object.
 */
st_status_t st_mem_get_format_versions(void *, unsigned short *, 
			   unsigned short *);

/* Opens the given file, decompressing if necessary, and 
 * searches for the .comment section header.  If found, its
 * raw data is read in and a pointer passed to the static
 * routine _st_get_toolver, which searches for a ST_CM_TOOLVER
 * entry identified by "toolname".
 * The caller should free the string pointed to by "msg".
 */
st_status_t st_get_version_byname(char *, char *, unsigned long *, char **);


/* Does the same thing as st_get_version_byname(), but reads
 * from the "praw" memory pointer.  "size" is the size of
 * the file in memory.
 */
st_status_t st_mem_get_version_byname(void *, unsigned long, char *, 
			  unsigned long *, char **);


/* Given an open file descriptor and the file offset of the object's
 * file header, search for a tool version entry.  Note that the 
 * file offset parameter may differ from the current position of
 * the file descriptor, and that the initial position should be 
 * restored before returning to the caller.  However, the file
 * descriptor should not be closed under any circumstances.
 */

st_status_t st_fd_get_version_byname(int, off_t, char *, unsigned long *, 
			 char **);

/* st_file_is_archive() checks whether the specified file
 * is an archive, using the routine st_fd_is_archive() 
 * defined in st_ar_open.c.  
 * This routine is included here because it is useful for
 * tools doing version-checking to know before an st_obj_open()
 * call whether a file is an archive.
 */
st_status_t st_file_is_archive(char *, st_bool_t *);

/* Comment section routines */

/* Get subsection tag descriptor flags */
st_status_t st_cm_flags(st_cmscn_t cmscn, st_cm_sscn_t sscn, 
			cm_flags_t *flags);

/* Get subsection tag */
st_status_t st_cm_tag(st_cmscn_t cmscn, st_cm_sscn_t sscn, 
		      unsigned int *tag);

/* Get subsection data */
st_status_t st_cm_data(st_cmscn_t cmscn, st_cm_sscn_t sscn,
		       unsigned int *dlen, void **dptr);

/* Set up for comment section processing */
st_status_t st_obj_cm_setup(st_obj_t *out_obj, st_cmscn_t *cmscn);

/* Set up for object-independent comment section processing */
st_status_t st_cm_setup(void *sdata, unsigned int ssize, st_cmscn_t *cmscn);

/* Free memory allocated for a comment section structure. */
st_status_t st_cm_cleanup(st_cmscn_t cmscn);

/* Find a .comment subsection. */
st_status_t st_cm_find_sscn(st_cmscn_t cmscn, unsigned int tag, 
			    st_cm_sscn_t *sscn);

/* Add a .comment subsection */
st_status_t st_cm_add(st_cmscn_t cmscn, unsigned int tag, 
		      unsigned int len, void *data);

/* Get first subsection in comment section */
st_status_t st_cm_start(st_cmscn_t cmscn, st_cm_sscn_t *sscn);

/* Get next subsection in comment section */
st_status_t st_cm_next(st_cmscn_t cmscn, st_cm_sscn_t cmcur, 
		       st_cm_sscn_t *cmnext);

/* Append subsection data */
st_status_t st_cm_append(st_cmscn_t cmscn, st_cm_sscn_t sscn,
			  unsigned int len, void *data);

/* Delete a .comment subsection */
st_status_t st_cm_delete(st_cmscn_t cmscn, st_cm_sscn_t sscn);

/* Delete a single entry in a .comment subsection. */
st_status_t st_cm_del_entry(st_cmscn_t cmscn, st_cm_sscn_t sscn, void *key);

/* Get tag descriptor flags for a .comment subsection.  "is_default" 
 * set if the flags returned are from the default settings. 
 */
st_status_t st_cm_get_flags(st_cmscn_t cmscn, unsigned int tag, 
			    cm_flags_t *flags, st_bool_t *is_default);

/* Set tag descriptor flags for a .comment subsection */
st_status_t st_cm_set_flags(st_cmscn_t cmscn, unsigned int tag, cm_flags_t flags);

/* Print the entire .comment section */
st_status_t st_cm_print(st_cmscn_t cmscn, st_bool_t verbose);

/* Print a .comment subsection */
st_status_t st_cm_print_one(st_cmscn_t cmscn, unsigned int tag, 
			    st_bool_t verbose);

/* Assemble output buffer for new .comment section */
st_status_t st_cm_layout(st_cmscn_t cmscn, void **cmdata, long *cmlen);

#endif /* !_ST_INTERNAL */


/* 
 * Library error return codes.
 * Some codes can be interpreted as warnings or errors, depending on the 
 * context.  An invalid query and a corrupt symbol table may generate
 * the same error code.
 * Status returns for st_foreach* routines follow error codes.
 */

#define ST_E_NULL_ARGUMENT	-1	/* Input argument is null */
#define ST_E_FILE		-2	/* File isn't a regular file or
					   isn't supported object type */
#define ST_E_SYMBOL_TABLE	-3	/* Object is stripped or symbol table is
				           unavailable */
#define ST_E_DECOMPRESS		-4	/* File decompression failed */
#define ST_E_ALIGNMENT		-5	/* Unaligned object - performance 
					   degraded */
#define ST_E_SYM_MAGIC		-6	/* Bad symbolic header magic number */
#define ST_E_DYN_INFO		-7	/* Error obtaining dynamic info */
#define ST_E_LIB_NAMES		-8	/* Unable to get shared lib names */
#define ST_E_NONSHARED		-9	/* Invalid call for nonshared program */
#define ST_E_OBJECT_TYPE	-10     /* Unknown object type */
#define ST_E_NULL_PTR		-11	/* Ref. through null pointer */
#define ST_E_OBJ_NAME		-12	/* Error duplicating obj name */
#define ST_E_FILE_STRIPPED	-13     /* File in object is stripped of 
					   local symbols */
#define ST_E_NO_STRINGS		-14	/* Strings don't exist for names */
#define ST_E_SYM_FILE_INDEX	-15	/* File invalid for symbol */
#define ST_E_SYM_FILE		-16	/* Can't get file containing symbol */
#define ST_E_FILE_RANGE		-17	/* File out of range for object */
#define ST_E_PROC_RANGE		-18	/* Proc out of range for obj. or file */
#define ST_E_SYM_RANGE		-19     /* Symbol out of range for object */
#define ST_E_TYPE_RANGE		-20	/* Type out of range for object */
#define ST_E_SECTION_RANGE	-21	/* Sect out of range for object */
#define ST_E_NO_PROCS		-22	/* No proc information for object */
#define ST_E_NO_PROC_SYM	-23	/* Proc symbol not available */
#define ST_E_NO_FILE_PROCS	-24	/* File contains no procedures */
#define ST_E_NO_COMMENT_SECTION	-25	/* Comment section doesn't exist */
#define ST_E_COMMENT_SECTION	-26	/* Comment section has invalid size 
					   for tag */
#define ST_E_SYM_VALUE		-27	/* Can't obtain symbol value */
#define ST_E_SYM_NAME		-28     /* Can't obtain symbol name */
#define ST_E_INVALID_SYM	-29	/* Invalid symbol, e.g. external
					   symbol when local symbol expected, 
					   or negative symbol */
#define ST_E_SYM_OUTER		-30	/* Can't locate enclosing procedure
					   for symbol.  Bad symbol table */
#define ST_E_SYM_ISYM		-31	/* Symbol's symbol index is invalid */
#define ST_E_SYM_TYPE		-32	/* Invalid symbol type */
#define ST_E_NO_END_SYM		-33	/* No stEnd symbol found */
#define ST_E_TYPE_SYM		-34	/* Can't get symbol for type */
#define ST_E_FILE_SYM		-35	/* Can't get file symbol for file */
#define ST_E_NAME_SYM		-36	/* Can't locate symbol matching name */
#define ST_E_ADDR_SECTION	-37	/* Can't find section containing addr */
#define ST_E_SECTION_TYPE	-38	/* Unknown section type */
#define ST_E_SECTION_SIZE	-39	/* Section size of 0 */
#define ST_E_NO_RELOCS		-40	/* No relocations for section */
#define ST_E_ADDR_OBJ		-41	/* Can't locate obj containing addr */
#define ST_E_OBJLIST_EMPTY	-42	/* Attempted operation on empty list */
#define ST_E_NO_OBJLIST_OBJ	-43	/* Input obj not on objlist */
#define ST_E_ADDR_PROC		-44	/* Can't locate proc containing addr */
#define ST_E_SECTIONS_DIFFER	-45	/* Text addr and the proc determined
					   to contain the text address
 					   are in different sections. */
#define ST_E_TYPE_FILE		-46	/* Can't get file containing type */
#define ST_E_PROC_FILE		-47	/* Can't get file containing proc */
#define ST_E_CMRLC_SIZE		-48	/* Invalid compact reloc data size */
#define ST_E_CMRLC_VERSION	-49	/* Invalid compact relocation version */
#define ST_E_SECTION_NAME	-50	/* Can't find section to match name */
#define ST_E_LINE_PROC		-51	/* Can't locate proc containing line */
#define ST_E_NO_LINES		-52	/* No line number info for file */
#define ST_E_ADDR_LINE		-53	/* Can't find line to match address */
#define ST_E_LINE_ADDR 		-54	/* Can't find address to match line */
#define ST_E_PROC_ILINE 	-55	/* Line # index out of range for proc */
#define ST_E_ORDER		-56	/* Routine called in wrong order */
#define ST_E_PROC_PLINE		-57	/* Packed line # index out of range for
					   proc */
#define ST_E_ALTERNATE		-58	/* Proc is alternate entry or nested */
#define ST_E_PROC_SORTED	-59	/* Can't locate proc in sorted
					   procedure table */
#define ST_E_INVALID_ADDR	-60	/* Address outside text or data range
					   of object */
#define ST_E_FILE_OBJ		-61	/* Can't locate obj containing file */
#define ST_E_PROC_OBJ		-62	/* Can't locate obj containing proc */
#define ST_E_SYM_OBJ		-63	/* Can't locate obj containing symbol */
#define ST_E_SECTION_OBJ	-64	/* Can't locate obj containing section */
#define ST_E_FRAME_OFFSET 	-65     /* Frame offset is valid for procedure, 					   but is not contained in any symbol */
#define ST_E_FRAME_OFFSET_RANGE -66	/* Frame offset is outside frame size 
					   for procedure. */
#define ST_E_INVALID_FRAME_OFFSET -67   /* Negative frame offset */
#define ST_E_DATA_ADDR		-68	/* Address is not in data or bss segment */
#define ST_E_DATA_INDEX_RANGE	-69	/* Invalid index */
#define ST_E_RFD_RANGE		-70     /* Invalid index */
#define ST_E_OBJ_LSTRIPPED	-71	/* Object stripped of local syms */
#define ST_E_ARCHIVE_NAME	-72	/* Error duplicating archive name */
#define ST_E_ARCHIVE_EMPTY	-73	/* Archive contains no members */
#define ST_E_OBJECT_INVALID	-74	/* Archive or object is 
                                           truncated or corrupt */
#define ST_E_NOT_ARCHIVE	-75	/* Object isn't archive */
#define ST_E_FILE_ACCESS	-76	/* Invalid file access permissions */
#define ST_E_FILE_NAME_LENGTH   -77	/* File name too long (>PATH_MAX) */
#define ST_E_ARCHIVE_OP		-78	/* Invalid operation for archive  */
#define ST_E_INVALID_WRITE	-79	/* Attempted write on an object opened
					   for reading */
#define ST_E_INVALID_OBJ	-80     /* Invalid st_obj_t,e.g. no file name */
#define ST_E_INVALID_REP	-81	/* Invalid section replacement */
#define ST_E_CHUNK_TYPE		-82     /* No chunk exists with given type */
#define ST_E_CHUNK_OFFSET	-83     /* No chunk exists with given offset */

#define ST_E_INVALID_TAG	-84     /* Tag value not found */
#define ST_E_CM_RANGE		-85  	/* Out of range for comment section */
#define ST_E_CM_OPERATION	-86	/* Invalid operation for tag value */
#define ST_E_CM_FLAGS		-87	/* Invalid tag descriptor flag settings */
#define ST_E_DATA_EXISTS 	-88	/* Scn data/relocations already exists */
#define ST_E_INVALID_DELETE 	-89	/* Invalid scn data/reloc deletion */
#define ST_E_INVALID_ADD 	-90	/* Invalid scn data/reloc addition */
#define ST_E_CHUNK_UNSORTED 	-91	/* Chunks not sorted by file offset */
#define ST_E_CHUNK_OVERLAP  	-92	/* File offsets for chunks overlap  */
#define ST_E_INVALID_CHUNK 	-93	/* Invalid chunk */
#define ST_E_CHUNK_INTERNAL	-94	/* Internal libst error */
#define ST_E_INVALID_OBJLIST_APPEND -95 /* Invalid object for object list  */
#define ST_E_OBJ_IN_USE         -96     /* Object in use and can't be closed */
#define ST_E_COMPRESSED_OP 	-97     /* Invalid operation on compressed file */

#define ST_E_MAJ_OBJ_VER        -98     /* Object file major version mismatch */
#define ST_E_MIN_OBJ_VER        -99     /* Object file minor version mismatch */
#define ST_E_MAJ_SYM_VER        -100    /* Symbol table major version mismatch */
#define ST_E_MIN_SYM_VER        -101    /* Symbol table minor version mismatch */
#define ST_E_CM_VER		-102    /* Comment section format version mismatch */
#define ST_E_CM_DATA		-103	/* Invalid comment section data */

/* Informational status returns - not errors */
#define ST_E_ARCHIVE_END	-995	/* End of members in archive reached */
#define ST_PROC_END		-996    /* End of procedures reached.  Returned
					   by foreach routines for procedures */
#define ST_OBJ_END		-997	/* End of objects on list reached.  
					   Returned by foreach routines for 
					   object lists */
#define ST_SECTION_END		-998	/* End of sections.  Returned by foreach
					   routines for sections */
#define ST_FOREACH_CONTINUE	-999	/* Not an error - routines called by
					   st_foreach routines return this. */

#ifdef __cplusplus
}
#endif

#endif /* _ST_H_ */
