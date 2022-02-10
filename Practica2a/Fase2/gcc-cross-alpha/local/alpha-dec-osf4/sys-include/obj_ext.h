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
 * @(#)$RCSfile: obj_ext.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1998/04/28 15:13:48 $
 */
#ifndef __OBJ_EXT_H
#define __OBJ_EXT_H
#ifdef __cplusplus
extern "C" 
{
#endif

#include <obj.h>
struct obj;
struct obj_type;
struct obj_list;
#include <stdio.h>
#include <sys/types.h>
#include <scnhdr.h>
#include <filehdr.h>
#include <aouthdr.h>
#include <sym.h>
#include <elf_mips.h>
#include <elf_abi.h>  
extern unsigned long foreach_section(struct obj *,
 unsigned long (*routine) __(( struct obj *, struct scnhdr *, unsigned long)),
 unsigned long);
extern SCNHDR *address_to_section(struct obj *, unsigned long);
extern unsigned long section_type(struct obj *, const struct scnhdr *);
extern char *section_raw(struct obj *, const struct scnhdr *);
extern unsigned long section_nrel(struct obj *, const struct scnhdr *);
extern struct reloc *section_rel(struct obj *, const struct scnhdr *);
extern unsigned long find_section_byname( struct obj *, struct scnhdr *, 
					 unsigned long);
extern unsigned long find_section_bytype( struct obj *, struct scnhdr *, 
					 unsigned long);
extern unsigned long obj_section_type(struct obj_list *, unsigned long);
extern unsigned long aux_isym(struct obj *, unsigned long);
extern long get_aux(struct obj *, long );
extern void get_range(struct obj *, long , struct obj_type *);
extern unsigned long *objList_add(struct obj_list **, unsigned long, char *, 
				  unsigned long);
extern unsigned long *objList_change(struct obj_list **, unsigned long, 
				     unsigned long, char *, unsigned long);
extern unsigned long foreach_obj (struct obj_list *, 
 unsigned long (*routine)(unsigned long, unsigned long, unsigned long *), 
 unsigned long);
extern unsigned long forall_previous_objs (struct obj_list *, struct obj *, 
 unsigned long (*routine) __((struct obj *, struct obj *, unsigned long)), 
 unsigned long);
extern unsigned long list_last(struct obj_list *);
extern unsigned long foreach_sublist (struct obj_list *, 
 unsigned long (*routine) __((struct obj_list *, unsigned long)), 
 unsigned long);
extern unsigned long symbol_to_file(struct obj *, unsigned long);
extern unsigned long type_to_file(struct obj *, unsigned long);
extern unsigned long procedure_to_file(struct obj *, unsigned long);
extern struct fdr *file_pfd(struct obj *, unsigned long);
extern unsigned long file_symbol(struct obj *, unsigned long);
extern unsigned long file_lineindex(struct obj *, unsigned long);
extern unsigned long file_cline(struct obj *, unsigned long);
extern unsigned long file_cbLineOffset(struct obj *, unsigned long);
extern unsigned long file_lang(struct obj *, unsigned long);
extern unsigned long file_glevel(struct obj *, unsigned long);
extern unsigned long file_symbol_count(struct obj *, unsigned long);
extern unsigned long file_type_base(struct obj *, unsigned long);
extern char *file_string_base(struct obj *, unsigned long);
extern unsigned long foreach_rfd(struct obj *, unsigned long ,
 unsigned long (*routine) __((struct obj *, unsigned long, char *,long,long )),
 unsigned long, unsigned long, unsigned long);
extern char *file_name(struct obj *, unsigned long);
extern unsigned long address_to_file(struct obj *, unsigned long);
extern void change_fortran_names(struct obj *);
extern struct obj *obj_open(struct obj *, const char *, int );
extern struct obj *obj_fopen(struct obj *, const char *, int, unsigned int);
extern struct obj *dbx_obj_open(struct obj *, const char *);
extern struct obj *dbx_obj_open_fd(struct obj *, int);
extern struct obj *obj_init(struct obj *, int);
extern struct obj *fadd_obj(struct obj_list **, const char *, unsigned int);
extern struct obj *add_obj(struct obj_list **, const char *);
extern struct obj *fadd_obj(struct obj_list **, const char *, unsigned int);
extern struct obj *dbx_add_obj(struct obj_list **, const char *);
extern struct obj *dbx_add_obj_fd(struct obj_list **, int);
extern struct obj *insert_obj(struct obj_list **, struct obj *);
extern struct obj *dbx_insert_obj(struct obj_list **, struct obj *);
extern struct obj *symbol_to_obj(struct obj_list *, unsigned long);
extern struct obj *procedure_to_obj(struct obj_list *, unsigned long);
extern struct obj *file_to_obj(struct obj_list *, unsigned long);
extern struct obj *address_to_obj(struct obj_list *, unsigned long);
extern struct obj *address_to_obj_for_rld(struct obj_list *, unsigned long);
extern struct obj *obj_read_from_fd(struct obj *, int, unsigned long, 
				    unsigned long, unsigned long);
extern void obj_close(struct obj *);
extern void obj_fini(struct obj *);
extern void obj_close_arch(struct obj *);
extern void dbx_obj_close(struct obj *);
extern int obj_nsections(struct obj *);
extern Elf32_Dyn *obj_dynamic(struct obj *);
extern int obj_get_dynamic_info(Elf32_Dyn *, struct obj *, unsigned long, 
				unsigned long);
extern unsigned elfhash(const char *);
extern int obj_shared(struct obj *);
extern int obj_call_shared(struct obj *);
extern char *elf_get_pt_interp(struct obj *);
extern Elf32_Addr obj_find_symbol_value(unsigned long, const char *, int);
extern unsigned long obj_find_procedure_table(unsigned long, unsigned long, 
					      unsigned long*);
extern Elf32_Addr obj_dynsym_got_fcn(struct obj *, int);
extern Elf32_Addr obj_set_dynsym_got_fcn(struct obj *, int, Elf32_Addr);
extern long obj_get_got_entry(struct obj *, unsigned long, long , 
			      unsigned long *, int * );
extern int obj_resolve_symname(struct obj *, const char *);
extern int __ld_check_versions(struct obj *);
extern unsigned long procedure_symbol(struct obj *, long);
extern struct pdr *procedure_ppd(struct obj *, long );
extern unsigned long procedure_address(struct obj *, long);
extern long procedure_iline(struct obj *, long);
extern long procedure_lnLow(struct obj *, long);
extern long procedure_lnHigh(struct obj *, long);
extern long procedure_cbLineOffset(struct obj *, long);
extern long procedure_isaent(struct obj *, unsigned long);
extern unsigned long procedure_next(struct obj *, unsigned long);
extern unsigned long address_to_procedure(struct obj *, unsigned long);
extern unsigned long foreach_obj_procedure(struct obj *,
 unsigned long (*routine) __(( struct obj *, long, unsigned long)), 
 unsigned long);
extern unsigned long foreach_obj_procedure_sorted(struct obj *,
 unsigned long (*routine) __((struct obj *, long , unsigned long)),
 unsigned long);
extern unsigned long foreach_procedure(struct obj *, unsigned long file,
 unsigned long (*routine) __(( struct obj *, long, unsigned long)),
 unsigned long);
extern newprocedure(unsigned long, long, long, long, long);
extern unsigned long symbol_class(struct obj *, long);
extern unsigned long symbol_type(struct obj *, long);
extern unsigned symbol_weak(struct obj *, long);
extern unsigned long symbol_value(struct obj *, long);
extern unsigned long symbol_offset(struct obj *, long);
extern long symbol_iaux(struct obj *, long);
extern long symbol_isym(struct obj *, long);
extern long symbol_value_isym(struct obj *, long);
extern long symbol_value_iaux(struct obj *, long);
extern unsigned long end_symbol(struct obj *, long);
extern unsigned long procedure_end_symbol(struct obj *, long);
extern unsigned long address_to_symbol(struct obj_list *, unsigned long);
extern unsigned long symbol_to_outer_scope_symbol(struct obj *, unsigned long);
extern char *_mld_raw_symbol_name(struct obj *, long );
extern struct symr *user_symbol_alloc();
extern user_symbol_free();
extern union auxu *user_type_alloc();
extern long newsymbol(char *,int,int,struct obj_type *,long);
extern modify_user_symbol(long,int ,int ,struct obj_type *,long);
extern long find_user_symbol(const char *,int);
extern unsigned long symbol_size(struct obj *, long);
extern long scope_name_search(struct obj *, unsigned long, const char *, 
			      long, long );
extern long fortran_scope_search(struct obj *, unsigned long, const char *, 
				 int, int );
extern unsigned long file_scope_name_search(struct obj *, unsigned long, 
					    const char *, long, long);
extern long search_externals(struct obj *, const char *, int );
extern long search_externals_by_value(struct obj *, unsigned long);
extern long search_typedefs(struct obj *, const char *, int );
extern long search_cobol_main(struct obj *);
extern long search_procedures(struct obj *, const char *, int);
extern unsigned long search_files(struct obj *, const char *, int, int, int);
extern long find_symbol(struct obj *, long, const char *, int, int);
extern int case_strcmp(const char *, const char *);
extern int case_streq(const char *,const char *,int);
extern int case_streqn(const char *,const char *,size_t ,int);
extern unsigned long access_lines(struct obj *, unsigned long, unsigned long,
                                unsigned long, unsigned long *, unsigned long);
extern unsigned long outer_proc_lnhigh(struct obj *, unsigned long);
extern unsigned long file_line_to_address(struct obj *, unsigned long, 
					  unsigned long *, unsigned long);
extern unsigned long address_to_line(struct obj *, unsigned long);
extern iline_to_line(struct obj *, struct fdr *, struct pdr *, long);
extern void set_line(struct obj *, long, long, long);
extern long next_line(void);
extern unsigned long find_high_line (struct obj *, unsigned long);
extern char *has_extended_src (struct obj *, unsigned long, long, long *);
extern int interpret_command_mode(struct obj *, char *, unsigned long *, 
				  long *, unsigned long *);
extern int unsigned_leb128_decode(char *, unsigned long *);
extern int signed_leb128_decode(char *, long *);
extern int elf_spoof_coffhdrs(struct obj *, struct filehdr *, struct aouthdr *,
			      struct scnhdr *);
extern int elf_nreloc(struct obj *, int);
extern char *obj_raw_bits(struct obj *, char *);
extern int obj_section_reloc_type(struct obj *, int);
extern struct obj *obj_sym_open(struct obj *, char *);
extern void obj_sym_close(struct obj *);
extern void obj_update_dynamic(struct obj *, Elf32_Dyn *);
extern unsigned long obj_vtofo(struct obj *, unsigned long);
extern unsigned long obj_vtop(struct obj *, unsigned long);
extern struct obj *obj_rewrite(struct obj *, struct obj *, char *);
extern struct obj *obj_write(struct obj *);
extern void obj_extend_text_segment(struct obj *, int);
extern void *obj_extend_bss_segment(struct obj *, int);
extern void obj_set_section_size(struct obj *, char *, int);
extern void obj_set_section_address (struct obj *, char *, long);
extern void obj_map_dynamic(struct obj *, unsigned long, unsigned long, 
	    unsigned long *, unsigned long, unsigned, unsigned long *);
extern unsigned long obj_gpvalue(struct obj *);
extern void obj_add_global_abs_symbol(struct obj *, char *, unsigned long);
extern unsigned long obj_end(struct obj *);
extern unsigned long obj_otype(struct obj *);
extern FILHDR *obj_pfilehdr(struct obj *);
extern AOUTHDR *obj_paouthdr(struct obj *);
extern SCNHDR *obj_pscnhdr(struct obj *);
extern pHDRR obj_phdrr(struct obj *);
extern pSYMR obj_psymr(struct obj *);
extern pEXTR obj_pextr(struct obj *);
extern unsigned long obj_symbol_base(struct obj *);
extern unsigned long obj_external_base(struct obj *);
extern unsigned long obj_file_base(struct obj *);
extern unsigned long obj_procedure_base(struct obj *);
extern unsigned long obj_type_base(struct obj *);
extern unsigned long obj_base_address(struct obj *);
extern void obj_set_base_address(struct obj *, unsigned long);
extern unsigned long obj_data_base_address(struct obj *);
extern void obj_set_data_base_address(struct obj *, unsigned long);
extern char *obj_map_address(struct obj *);
extern void obj_set_map_address(struct obj *, char *);
extern unsigned long obj_map_diff(struct obj *);
extern unsigned long obj_map_diff_dbx(struct obj *);
extern Elf32_Word *obj_hash(struct obj *);
extern void obj_set_hash_address(struct obj *, Elf32_Word *);
extern char *obj_dynstr(struct obj *);
extern void obj_set_dynstr_address(struct obj *,char *);
extern Elf32_Sym *obj_dynsym(struct obj *);
extern void obj_set_dynsym_address(struct obj *, Elf32_Sym *);
extern Elf32_Msym *obj_msym(struct obj *);
extern void obj_set_msym_address(struct obj *, Elf32_Msym *);
extern Elf32_Rel *obj_dynrel(struct obj *);
extern void obj_set_dynrel_address(struct obj *, Elf32_Rel *);
extern Elf32_Lib *obj_liblist(struct obj *);
extern void obj_set_liblist_address(struct obj *, Elf32_Lib *);
extern Elf32_Conflict *obj_conflict(struct obj *);
extern void obj_set_conflict_address(struct obj *, Elf32_Conflict *);
extern Elf32_Word obj_unrefextno(struct obj *);
extern void obj_set_unrefextno(struct obj *, Elf32_Word);
extern Elf32_Word obj_gotsym(struct obj *);
extern void obj_set_gotsym(struct obj *, Elf32_Word);
extern Elf32_Word obj_timestamp(struct obj *);
extern void obj_set_timestamp(struct obj *, Elf32_Word);
extern Elf32_Word obj_ichecksum(struct obj *);
extern void obj_set_ichecksum(struct obj *, Elf32_Word);
extern Elf32_Word obj_iversion(struct obj *);
extern void obj_set_iversion(struct obj *, Elf32_Word);
extern Elf32_Word obj_dynflags(struct obj *);
extern void obj_set_dynflags(struct obj *, Elf32_Word);
extern Elf32_Word obj_dynrelsz(struct obj *);
extern void obj_set_dynrelsz(struct obj *, Elf32_Word);
extern Elf32_Word obj_dynrelent(struct obj *);
extern void obj_set_dynrelent(struct obj *, Elf32_Word);
extern Elf32_Word obj_dynsymcount(struct obj *);
extern void obj_set_dynsymcount(struct obj *, Elf32_Word);
extern Elf32_Word obj_dynsyment(struct obj *);
extern void obj_set_dynsyment(struct obj *, Elf32_Word);
extern Elf32_Word obj_dynstrsz(struct obj *);
extern void obj_set_dynstrsz(struct obj *, Elf32_Word);
extern Elf32_Word obj_liblistcount(struct obj *);
extern void obj_set_liblistcount(struct obj *, Elf32_Word);
extern Elf32_Word obj_conflictcount(struct obj *);
extern void obj_set_conflictcount(struct obj *, Elf32_Word);
extern char *obj_rpath(struct obj *);
extern void obj_set_rpath(struct obj *, char *);
extern char *obj_soname(struct obj *);
extern void obj_set_soname(struct obj *, char *);
extern Elf32_Word obj_rldversion(struct obj *);
extern char *obj_rldversion_string(struct obj *);
extern void obj_set_rldversion(struct obj *, Elf32_Word);
extern unsigned long obj_text_start(struct obj *);
extern void obj_set_text_start(struct obj *, Elf32_Addr);
extern unsigned long obj_text_size(struct obj *);
extern void obj_set_text_size(struct obj *, Elf32_Word);
extern unsigned long obj_data_start(struct obj *);
extern void obj_set_data_start(struct obj *, Elf32_Addr);
extern unsigned long obj_bss_start(struct obj *);
extern void obj_set_bss_start(struct obj *, Elf32_Addr);
extern unsigned long obj_data_size(struct obj *);
extern unsigned long obj_bss_size(struct obj *);
extern void obj_set_bss_size(struct obj *, Elf32_Word);
extern char *obj_name(struct obj *);
extern void obj_set_name(struct obj *, char *);
extern char *obj_path(struct obj *);
extern void obj_set_path(struct obj *, char *);
extern Elf32_Addr obj_init_address(struct obj *);
extern void obj_set_init_address(struct obj *, Elf32_Addr);
extern Elf32_Addr obj_fini_address(struct obj *);
extern void obj_set_fini_address(struct obj *, Elf32_Addr);
extern Elf32_Addr obj_entry_address(struct obj *);
extern void obj_set_entry_address(struct obj *, Elf32_Addr);
extern Elf32_Word obj_rldflags(struct obj *);
extern void obj_set_rldflag(struct obj *, Elf32_Word);
extern void obj_unset_rldflag(struct obj *, Elf32_Word);
extern int obj_is_mapped(struct obj *);
extern int obj_was_modified(struct obj *);
extern int obj_chksum_changed(struct obj *);
extern int obj_was_moved(struct obj *);
extern int obj_followed_csc(struct obj *);
extern char *obj_dynstrtab(struct obj *);
extern char *obj_dynstring(struct obj *, int);
extern int obj_conflict_foreign(struct obj *);
extern int obj_liblist_foreign(struct obj *);
extern Elf32_Addr obj_dynsym_value(struct obj *, int);
extern Elf32_Word obj_dynsym_size(struct obj *, int);
extern Elf32_Half obj_sym_shndx(struct obj *, int);
extern char *obj_dynsym_name(struct obj *, int);
extern unsigned char obj_sym_info(struct obj *, int);
extern int obj_msym_exists(struct obj *);
extern int obj_msym_not_exists(struct obj *);
extern Elf32_Word obj_dynsym_hash_value(struct obj *, int);
extern Elf32_Word obj_nbucket(struct obj *);
extern Elf32_Word obj_nchain(struct obj *);
extern Elf32_Word obj_hash_bucket(struct obj *, int);
extern Elf32_Word obj_hash_chain(struct obj *, int);
extern Elf32_Word obj_dynsym_rel_index(struct obj *, int);
extern Elf32_Word obj_msym_ms_info(struct obj *, int);
extern void obj_set_msym_ms_info(struct obj *, int, Elf32_Word);
extern Elf32_Word obj_msym_ms_hash_value(struct obj *, int);
extern void obj_set_msym_ms_hash_value(struct obj *, int, Elf32_Word);
extern Elf32_Addr obj_rel_off(struct obj *, int);
extern Elf32_Word obj_rel_info(struct obj *, int);
extern Elf32_Addr obj_conflict_symbol(struct obj *, int);
extern char *obj_liblist_name(struct obj *, int);
extern Elf32_Word obj_liblist_tstamp(struct obj *, int);
extern Elf32_Word obj_liblist_csum(struct obj *, int);
extern char *obj_liblist_version_str(struct obj *, int);
extern Elf32_Word obj_liblist_version(struct obj *, int);
extern Elf32_Word obj_liblist_flags(struct obj *, int);
extern char *obj_interface_version(struct obj *);
extern int obj_interface_not_match(struct obj *, struct obj *, int);
extern int obj_checksum_not_match(struct obj *, struct obj *, int);
extern int obj_name_not_match(struct obj *, struct obj *, int);
extern int obj_tstamp_not_match(struct obj *, struct obj *, int);
extern int obj_different_name(struct obj *, struct obj *);
extern Elf32_Ehdr *obj_pelfhdr(struct obj *);
extern Elf32_Phdr *obj_pproghdr(struct obj *);
extern Elf32_Shdr *obj_psecthdr(struct obj *);
extern Elf32_Shdr obj_section(struct obj *, int);
extern Elf32_Half obj_shstrndx(struct obj *);
extern char *obj_section_index_name(struct obj *, int);
extern char *obj_section_bits(struct obj *, Elf32_Shdr *);
extern char *obj_section_index_bits(struct obj *, int);
extern unsigned long obj_section_vaddr(struct obj *, const struct scnhdr *);
extern unsigned long obj_section_size(struct obj *, const struct scnhdr *);
extern unsigned long obj_section_offset(struct obj *, const struct scnhdr *);
extern char *obj_section_name(struct obj *, const struct scnhdr *);
extern unsigned long obj_rld_map(struct obj *);
extern void obj_set_rld_map(struct obj *, unsigned long);
extern int obj_fd(struct obj *);
extern void obj_set_fd(struct obj *, int);
extern long hdr_symptr(struct obj *);
extern long procedure_lnlow(struct obj *, long);
extern long procedure_lnhigh(struct obj *, long);
extern Elf32_Word obj_mgot_count(struct obj *);
extern void obj_set_mgot_count(struct obj *, Elf32_Word);
extern void obj_set_mgot_local_table(struct obj *, Elf32_Got **);
extern void obj_set_mgot_external_table(struct obj *, Elf32_Got **);
extern Elf32_Got *obj_mgot_local(struct obj *, Elf32_Word);
extern void obj_set_mgot_local(struct obj *, Elf32_Word, Elf32_Got *);
extern Elf32_Got *obj_mgot_external(struct obj *, Elf32_Word);
extern void obj_set_mgot_external(struct obj *, Elf32_Word, Elf32_Got *);
extern Elf32_Word obj_mgot_local_count(struct obj *, Elf32_Word);
extern Elf32_Word obj_mgot_external_count(struct obj *, Elf32_Word);
extern Elf32_Addr obj_mgot_local_entry(struct obj *, Elf32_Word, int);
extern void obj_set_mgot_local_entry(struct obj *, Elf32_Word, int, 
				     Elf32_Addr);
extern Elf32_Addr obj_mgot_external_entry(struct obj *, Elf32_Word, int);
extern void obj_set_mgot_external_entry(struct obj *, Elf32_Word, int, 
					Elf32_Addr);
extern Elf32_Word obj_mgot_first_multisym(struct obj *);
extern voidobj_set_mgot_first_multisym(struct obj *, Elf32_Word);
extern char *symbol_name(struct obj *, long);
extern unsigned obj_get_comment_data(struct obj *, unsigned, unsigned long *);
extern struct wobj *obj_create_new(const char *, struct obj *, unsigned long, 
				   unsigned long, unsigned long, unsigned long,
				   mode_t );
extern int obj_next_scnno(struct wobj *);
extern void *obj_create_addscn(struct wobj *, unsigned , unsigned long,	
			       unsigned long *);
extern void *obj_create_addsymscn(struct wobj *, wobj_symscn_t, unsigned long);
extern int obj_create_addinfo(struct wobj *, wobj_info_type_t, wobj_info_t);
extern void obj_create_complete(struct wobj *);
extern caddr_t obj_create_scnhdr_addr(void);

#ifdef __cplusplus
}
#endif



#endif /* __OBJ_EXT_H */
