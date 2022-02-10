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
#pragma ident "@(#)$RCSfile: lockinfo.c,v $ $Revision: 1.1.883.13 $ (DEC) $Date: 1999/03/30 18:05:32 $"


#include <kern/lock.h>
#include <machine/cpu.h>
#include <unix_locks.h>
#include <net/net_globals.h>
#include <sys/lock_probe.h>

#if 0
#include "rt_sem.h"
#endif


#include "rt_ipc.h"
#include "rt_csem.h"
#include "te.h"
#include "tu.h"
#include "xna.h" 
#include "mfa.h"
#include "faa.h"
#include "packetfilter.h"
#include "gwscreen.h"
#include "pty.h"
#include "rpty.h"
#include "dli.h"
#include "dlb.h"
#include  "dlpi.h"
#include "dec_audit.h"
#include "siop.h"
#include "xza.h"
#include "aha.h"
#include "pza.h"
#include "tza.h"
#include "isp.h"
#include "psiop.h"
#include "xcr.h"
#include "tra.h"
#include "fta.h"
#include "lta.h"
#include "trsrcf.h"
#include "mlog.h"
#include "cdfs.h"
#include "ffm_fs.h"
#include "tcds.h"
#include "streams.h"
#include "strifnet.h"
#include "ci.h"
#include "uq.h"
#include "ldtty.h"
#include "pci.h"
#include "msfs.h"
#include "drd.h"
#include "dlm.h"
#include "dlmsl.h"
#include "ccomsub.h"
#include "mcnet.h"
#include "rm.h"
#include "rmvm.h"
#include "procfs.h"
#include "lsm.h"
#include "scsi.h"
#include "xtiso.h"
#include "ppp.h"
#include "atm.h"
#include "atmip.h"
#include "uni3x.h"
#include "atmilmi3x.h"
#include "atmuni.h"
#include "pwrmgr_enabled.h"
#include "usb.h"
#include "envram.h"
#include "pnvram.h"

/*
 * Define lockmode here so that we can have a different initial value
 * for the SAS kernel.  When we make osf_boot smart enough to read MFS,
 * then this definition could go back to lock.c.
 */
#include "sas.h"
#if SAS > 0
long lockmode =  0; /* 0: uni, 1: rt, 2: smp, 3: rt/smp, 4: rt/smp/dbg/stats */
#else
long lockmode = -1; /* to be determined at bootstrap time */
#endif /* SAS > 0 */

#if MACH_SLOCKS
#define SCC(xxx) xxx
#else
#define SCC(xxx)
#endif

#if UNIX_LOCKS
#define UCC(xxx) xxx
#else
#define UCC(xxx)
#endif

#if NETSYNC_LOCK
#define NCC(xxx) xxx
#else
#define NCC(xxx)
#endif

#define LI(name, extlip, minspl, flags) { \
	extern struct lockinfo *extlip; \
	lip->li_name = name; \
	lip->li_count = 0; \
	lip->li_flgspl = (minspl) | (flags); \
	extlip = lip++; \
}
#define SLI(a,b,c,d) SCC(LI(a,b,c,d))
#define ULI(a,b,c,d) UCC(LI(a,b,c,d))
#define NLI(a,b,c,d) NCC(LI(a,b,c,d))

#define LI_DISABLE_HIERARCHY_CHECKING(p) (p)->li_flgspl &= ~LI_DOHIER
#define SLI_DISABLE_HIERARCHY_CHECKING(p) SCC(LI_DISABLE_HIERARCHY_CHECKING(p))
#define ULI_DISABLE_HIERARCHY_CHECKING(p) UCC(LI_DISABLE_HIERARCHY_CHECKING(p))
#define NLI_DISABLE_HIERARCHY_CHECKING(p) NCC(LI_DISABLE_HIERARCHY_CHECKING(p))

#define DEFAULT (LI_VALID | LI_DOHIER) /* default lockinfo flags */
#define RWS	(LI_RWS | LI_VALID | LI_DOHIER) /* default lockinfo flags */
#define PROBE   (LI_VALID | LI_PROBE)  /* Flags set probing */
#define ORDERED (DEFAULT | LI_ORDERED)
#define ORDNEXT (DEFAULT | LI_ORDNEXT)

#define ULI_NOCHECK(name, extlip) { \
	ULI(name, extlip, SPLNONE, DEFAULT); \
	ULI_DISABLE_HIERARCHY_CHECKING(extlip); \
}

#ifdef LOCK_PROBE
int probe_smp = 1;	/* 0 == disabled at PROBE_START/END macro */
#define ULI_PROBE(name, extlip) { \
	ULI(name, extlip, SPLNONE, PROBE); \
}
#else
#define ULI_PROBE(name, extlip)
#endif /* LOCK_PROBE */

extern int lockinfo_count;
extern struct lockinfo *lockinfo_table;
extern struct lockstats *lockstats_table[];


/*
 * The following function contains lockinfo specs for initializing the
 * complex and simple lock data structures associated with lock debugging
 * and statistics.  The order of the LI() macro invocations determines the
 * relative locking hierarchy positions between classes of locks, with specs
 * nearer the beginning of the function referring to higher (or outermost)
 * locks and specs nearer the end of the function referring to lower (or
 * innermost) locks.  To add a new lockinfo spec, follow these steps:
 *
 *	1) Determine where the class of locks fits in below, and add a new
 *		LI() line in the function below specifying the class name,
 *		the name of an external lockinfo structure pointer, the
 *		minimum required spl level for lock acquisition, and the
 *		default trace flag constant.  The suggested class naming
 *		convention is to use the name of the global lock instance
 *		for single-lock classes or <structure_name>.<field_name>
 *		for classes of locks which are fields in other structures.
 *		If the associated lock instances are conditionally compiled,
 *		use the SLI(), ULI(), or NLI() macro in place of LI() as
 *		appropriate.
 *
 *	2) Add the global (struct lockinfo *) variable to the source file
 *		related to the locking class.  Use conditionally compiled
 *		declarations (decl_simple_lock_info/udecl_simple_lock_info)
 *		if the associated lock instances are conditionally compiled.
 *
 *	3) Replace the associated lock_init() or simple_lock_init() calls
 *		with lock_setup() or simple_lock_setup() calls naming the
 *		global (struct lockinfo *) variable as the 2nd argument.
 *
 *	4) If the lock class is a field of a data structure which is
 *		dynamically allocated and freed, add a complementary call
 *		to lock_terminate() or simple_lock_terminate() just before
 *		the data structure is freed.
 */

lockinfo_bootstrap(lip_start)
struct lockinfo *lip_start;
{
	register struct lockinfo *lip;
	register struct lockstats *lsp;
	register int i;

	lip = lip_start;
	lip->li_name = "unknown_simple_lock";
	lip->li_count = 0;
	lip->li_flgspl = 0;
	lip++;
	lip->li_name = "unknown_complex_lock";
	lip->li_count = 0;
	lip->li_flgspl = 0;
	lip++;

	/*********************************************/
	/* start of lockinfo specs for complex locks */
	/*********************************************/

	LI("lockdev_lock", lockdev_lockinfo, SPLNONE, DEFAULT);
	LI("sys_exitp_lock", sys_exitp_lockinfo, SPLNONE, DEFAULT);
	LI("fdfs_lock", fdfs_lockinfo, SPLNONE, DEFAULT);
	LI("cfg_subsys_lock", cfg_subsys_lockinfo, SPLNONE, ORDERED);
	LI("callbk_list_lock", callbk_list_lockinfo, SPLNONE, DEFAULT);
	LI("subsys_tbl_lock", subsys_tbl_lockinfo, SPLNONE, DEFAULT);
#if DLM > 0
	LI("dlm_smp_lock", dlm_smp_lockinfo, SPLNONE, DEFAULT);
#endif /* DLM */
#if DLMSL > 0
	LI("sl_smp_lock", sl_smp_lockinfo, SPLNONE, DEFAULT);
#endif /* DLMSL */
#if DRD > 0
	LI("bsc_rm_node.bn_node_lock", bsc_node_lockinfo, SPLNONE, DEFAULT);
#endif
	LI("lock_for_exported", lockinfo_for_exported, SPLNONE, DEFAULT);
#if ATM
#if UNI3X /* New ATM Signaling */
	ULI("atmsig_softc.timer_lock", atmsig_timer_lock_i, SPLNONE, DEFAULT);
#endif /* UNI3X */
#endif /* ATM */	
	LI("inode.i_io_lock", i_io_lockinfo, SPLNONE, ORDERED);
	LI_DISABLE_HIERARCHY_CHECKING(i_io_lockinfo);
	LI("nfs_daemon_lock", nfs_daemon_lockinfo, SPLNONE, DEFAULT);

#if PROCFS > 0
	LI("procnode.prc_ioctl_lock", procnode_ioctl_lockinfo,SPLNONE,ORDERED);
	LI("procfs_mount_lock", procfs_mount_lockinfo, SPLNONE, DEFAULT);
#endif
	LI("semidq_lock", semidq_lockinfo, SPLNONE, DEFAULT);
	LI("msgidq_lock", msgidq_lockinfo, SPLNONE, DEFAULT);
	LI("utask.uu_addr_lock", u_addr_lockinfo, SPLNONE, DEFAULT);
#if ATM
#if ATMIP
        NLI("request_q_complex_lock", request_q_complex_lock_info, SPLNONE, DEFAULT);
#endif
#endif
#if MSFS > 0
	/***********************************************
	 * AdvFS Complex (sleep) locks in hierarchy
	 ***********************************************/
	LI("RawBufFreeWait", ADVRawBufFreeWait_lockinfo, SPLNONE, DEFAULT );

	LI("BfsDeleteLock",Bfs_delete_lockinfo, SPLNONE, DEFAULT);
	LI("DmnTblLock", ADVDmnTblLock_info, SPLNONE, DEFAULT );
	LI("InitLock", ADVInitLock_info, SPLNONE, DEFAULT );
        LI("fsContext.file_lock", ADVfsContext_file_lock_info, SPLNONE,
	   ORDERED | ORDNEXT );
    /* DO NOT PUT ANY LOCK BETWEEN fsContext.file_lock AND vm_umap.vm_lock
     * BECAUSE OF THE ORDNEXT FLAG ON THE FILE_LOCK!!  THESE MUST BE AT THE
     * SAME HIERARCHY LEVEL.  OR ELSE.
     */
#endif
	LI("vm_umap.vm_lock", u_map_lockinfo, SPLNONE, DEFAULT);
	LI("rnode.r_rwlock", rnode_rw_lockinfo, SPLNONE, ORDERED);
	NLI("unp_mutex_lock", unp_mutex_li, SPLNONE, DEFAULT);
#if MSFS > 0
	/***********************************************
	 * AdvFS Complex (sleep) locks in hierarchy - cont
	 ***********************************************/
        LI("domainT.rmvolTruncLk", ADVdomainT_rmvolTruncLk_info, SPLNONE, DEFAULT);
        LI("bfAccessT.trunc_xfer_lk", ADVbfAccessT_trunc_xfer_lk_info, SPLNONE, DEFAULT );
	LI("bsInMemXtntT.migTruncLk", ADVbsInMemXtntT_migTruncLk_info, SPLNONE, ORDERED );
	LI("ddlActiveLk", ADVvdT_ddlActiveLk_info, SPLNONE, DEFAULT );
        LI("BfSetTblLock", ADVBfSetTblLock_info, SPLNONE, DEFAULT );
	LI("quotaInfoT_qiLock", ADVquotaInfoT_qiLock, SPLNONE, DEFAULT );
	LI("bfSetT.fragLock", ADVbfSetT_fragLock_info, SPLNONE, DEFAULT );
	LI("bfSetT.dirLock", ADVbfSetT_dirLock_info, SPLNONE, DEFAULT );
/*	LI("bfAccessT.cow_lk", ADVbfAccessT_cow_lk_info, SPLNONE, DEFAULT );*/
	LI("bfAccessT.mcellList_lk", ADVbfAccessT_mcellList_lk_info, SPLNONE, ORDERED );
	LI("bfAccessT.putpage_lk",ADVbfAccessT_putpage_lk_info, SPLNONE, DEFAULT );
	LI("bfAccessT.xtntMap_lk", ADVbfAccessT_xtntMap_lk_info, SPLNONE, DEFAULT );
	LI("FilesetLock", ADVFilesetLock_lockinfo, SPLNONE, DEFAULT );
/*	LI("dQuot.dqLock", ADVdQuot_dqLock_info, SPLNONE, DEFAULT ); */
	LI("vdT.mcell_lk", ADVvdT_mcell_lk_info, SPLNONE, DEFAULT );
	LI("vdT.del_list_lk", ADVvdT_del_list_lk_info, SPLNONE, DEFAULT );
	LI("BMT.bfAccessT.mcellList_lk", ADV_BMT_bfAccessT_mcellList_lk_info, SPLNONE, DEFAULT );
	LI("BMT.bfAccessT.xtntMap_lk", ADV_BMT_bfAccessT_xtntMap_lk_info, SPLNONE, DEFAULT );
	LI("domainT.scLock", ADVdomainT_scLock_info, SPLNONE, DEFAULT );
	LI("vdT.page0_mcell_lk", ADVvdT_page0_mcell_lk_info, SPLNONE, DEFAULT );
	LI("vdT.stgMap_lk", ADVvdT_stgMap_lk_info, SPLNONE, DEFAULT );
#endif
	ULI("chtabhead_lock", chtabhead_lockinfo, SPLNONE, DEFAULT);
	NLI("global_raw_lock", global_raw_li, SPLNONE, DEFAULT);
	NLI("domain_lock", domain_li, SPLNONE, DEFAULT);
	NLI("pmtu_lock", pmtu_li, SPLNONE, DEFAULT);
#if DLI > 0 || DLB > 0
	NLI("dli_input_lock", dli_input_li, SPLNONE, DEFAULT);
#endif
	NLI("socklocks.sock_lock", sock_li, SPLNONE, ORDERED);
	NLI("socklocks.snd_lock", snd_li, SPLNONE, DEFAULT);
	NLI("socklocks.rcv_lock", rcv_li, SPLNONE, DEFAULT);
	ULI("rnode_table_lock", rnode_table_lockinfo, SPLNONE, DEFAULT);
	LI("pgrphash_lock", pgrphash_lockinfo, SPLNONE, DEFAULT);
	ULI("p.proc_relation_lock", proc_relation_lockinfo, SPLNONE, ORDERED);
	ULI("pgrp.pg_lock", pgrp_lockinfo, SPLNONE, ORDERED);
	ULI("sysdev_write_lock", sysdev_write_lockinfo, SPLNONE, DEFAULT);
	LI("cm_lock", cm_lockinfo, SPLNONE, DEFAULT);
	LI("shmidq_lock", shmidq_lockinfo, SPLNONE, DEFAULT);
	LI("lk_lmf", lk_lmf_lockinfo, SPLNONE, DEFAULT);
	NLI("pr_dom_lock", pr_dom_li, SPLNONE, DEFAULT);
	/* inp_lock must follow socket lock */
	NLI("tcb.inp_lock", inp_tcphead_li, SPLNONE, ORDERED);
	NLI("udb.inp_lock", inp_udphead_li, SPLNONE, DEFAULT);
	NLI("inifaddr_lock", inifaddr_li, SPLNONE, DEFAULT);
	NLI("igmp_lock", igmp_li, SPLNONE, DEFAULT);
	NLI("mfc_lock", mfc_li, SPLNONE, DEFAULT);
	NLI("route_lock", route_li, SPLNONE, DEFAULT);
	NLI("ip_frag_lock", ip_frag_li, SPLNONE, DEFAULT);
#if DLI > 0 || DLB > 0
	NLI("dli_dlif_lock", dli_dlif_li, SPLNONE, DEFAULT);
#endif
#if NTRA > 0 || TRSRCF > 0
	/* srt_thread_lock needs to be after dli_dlif_lock */
	NLI("srt_thread_lock", srtab_li, SPLNONE, DEFAULT);
#endif

#if NFAA > 0
	LI("fxx_softc.lk_thread_level",
		faa_thread_level_lockinfo, SPLNONE, DEFAULT);
#endif
#if DEC_AUDIT > 0
	ULI("audinit.lock", audinit_lockinfo, SPLNONE, DEFAULT);
#endif

#if NSCSI > 0
	ULI("cam_pd_unit",cam_pd_unit_li,   SPLBIO, DEFAULT);
	ULI("scsi_did",   scsi_did_li,      SPLBIO, DEFAULT);
#if NSIOP > 0
	/* CAM siop */
	ULI("cam_siop_jalloc",  cam_siop_jalloc_li,     SPLBIO, DEFAULT);
	ULI("cam_siop_balloc",  cam_siop_balloc_li,     SPLBIO, DEFAULT);
#endif
#endif
	LI("vm_kmap.vm_lock", k_map_lockinfo, SPLNONE, ORDERED);
#if RPTY > 0
	LI("pty_allocation_lock", pty_opcl_lockinfo, SPLNONE, DEFAULT);
#endif

#ifdef ALPHA
	LI("ev_lock", ev_lock_info, SPLNONE, DEFAULT);
#endif ALPHA

	/*******************************************/
	/* end of lockinfo specs for complex locks */
	/*******************************************/
	/******************************************/
        /* start of lockinfo specs for NOCHECK    */
	/* complex locks.			  */
	/******************************************/
#if	(CDFS > 0)
	ULI_NOCHECK("cdnode.cd_io_lock", cdfs_inio_lockinfo);
#endif	/* CDFS > 0 */
	ULI_NOCHECK("bdevlock.dsw_lock", bdev_lockinfo);
	ULI_NOCHECK("cdevlock.dsw_lock", cdev_lockinfo);
	ULI_NOCHECK("handler_id_lock", handler_id_lockinfo);
	ULI_NOCHECK("handler_key.lock", handler_key_lockinfo);
	ULI_NOCHECK("ldbl_module_list_lock", ldbl_module_list_lockinfo);
	ULI_NOCHECK("topology_tree_lock", topology_tree_lockinfo);

	/* I/O resource mgmt locks */
	ULI_NOCHECK("res_handle_list_lock", res_handle_list_lockinfo);
	ULI_NOCHECK("resource_key.lock", resource_key_lockinfo);
	ULI_NOCHECK("intr_db_lock", intr_db_lockinfo);
	ULI_NOCHECK("mem_db_lock", mem_db_lockinfo);
	ULI_NOCHECK("io_db_lock", io_db_lockinfo);
	ULI_NOCHECK("io_rsrc_list.lock", resource_entry_lockinfo);
	ULI_NOCHECK("io_res_map_lock", io_res_map_lockinfo);
	ULI_NOCHECK("mem_res_map_lock", mem_res_map_lockinfo);


#if	(NVBA > 0) || (CVBA > 0)
	ULI_NOCHECK("vhp_bus_adapt.shoebox_lk", vhp_shobox_lockinfo);
	ULI_NOCHECK("vhp_bus_adapt.adapt_c_lk", vhp_adapt_c_lockinfo);
#endif	/* (NVBA > 0) || (CVBA > 0) */
#if	(NLV > 0)
	ULI_NOCHECK("volgrp.vg_lock", vg_lockinfo);
	ULI_NOCHECK("lvol.lv_lock", lvtmp_lockinfo);
#endif	/* NLV > 0 */
#if	(NLSM_TED > 0)
	ULI_NOCHECK("ted_cmd_slepp_lock", ted_cmd_slepp_lockinfo);
#endif	/* (NLSM_TED > 0) */
	ULI_NOCHECK("ufsmount.um_lock", umpq_lockinfo);
	ULI_NOCHECK("dqhead.dq_lock", dq_lockinfo);
	ULI_NOCHECK("fifonode.fn_rdio_lock", fifo_rdio_lockinfo);
	ULI_NOCHECK("fifonode.fn_wrio_lock", fifo_wrio_lockinfo);
	ULI_NOCHECK("bp.b_lock", buf_lockinfo);
	ULI_NOCHECK("sleeplck.fichain_lock", sleeplcks_fichain_lockinfo);
	ULI_NOCHECK("grantlcks.fichain_lock", grantlcks_fichain_lockinfo);
	ULI_NOCHECK("klmlcks.fichain_lock", klmlcks_fichain_lock);
	ULI_NOCHECK("mount.m_unmount_lock", unmount_lockinfo);
	ULI_NOCHECK("vfssw_lock", vfssw_lockinfo);
#if	(NLSM > 0)
	ULI_NOCHECK("volcpybuf_sleep.sl_sleep", vol_alloc_sleep_lockinfo);
#endif	/* NLSM	> 0) */

#if MSFS > 0
	/***************************************************/
	/* start of lockinfo specs for NOCHECK AdvFS locks */
	/***************************************************/

	/* HSM locks */
        ULI_NOCHECK("bfAccessT.mss_lk", ADVbfAccessT_mss_lk_info );
        ULI_NOCHECK("bfSetT.shlvLock", ADVbfSetT_shlvLock_info );
	ULI_NOCHECK("pqd_main_lock", ADVpqd_main_lock_info );
        ULI_NOCHECK("pqd_lowpri_lock", ADVpqd_lowpri_lock_info );

	/* Locks with hierarchy violations */
	ULI_NOCHECK("dQuot.dqLock", ADVdQuot_dqLock_info );
	ULI_NOCHECK("bfAccessT.cow_lk", ADVbfAccessT_cow_lk_info );
	LI("logDescT.descLock", ADVlogDescT_descLock_info, SPLNONE, ORDERED ); 
	LI_DISABLE_HIERARCHY_CHECKING(ADVlogDescT_descLock_info);
#endif /* MSFS */

#if	(DEC4100 == 1)
	/*********************************************/
        /* start of lockinfo spec for I2C Bus lock   */
        /*********************************************/

        ULI_NOCHECK("i2c_lock", i2c_lockinfo);
#endif /* DEC4100 */
	/******************************************/
        /* end of lockinfo specs for NOCHECK      */
	/* complex locks.			  */
	/******************************************/

	LI("lock.l_lock", interlock_lockinfo, SPLNONE, DEFAULT);
	LI_DISABLE_HIERARCHY_CHECKING(interlock_lockinfo);

#if MSFS > 0
	/******************************************/
	/* start of lockinfo specs for PROBE      */
	/* complex locks.			  */
	/******************************************/

	/* fs/fs_create.c PROBES */
	ULI_PROBE("Pfs_create_file", Pfs_create_file_lockinfo);
	ULI_PROBE("Pfs_update_stats", Pfs_update_stats_lockinfo);
    ULI_PROBE("Pfs_flush_saved_stats", Pfs_flush_saved_stats_lockinfo);
	ULI_PROBE("Pfs_trunc_test", Pfs_trunc_test_lockinfo);

	/* fs/fs_dir_init.c PROBES */
	ULI_PROBE("Pfs_init_directory", Pfs_init_directory_lockinfo);
	ULI_PROBE("Pfs_assemble_dir", Pfs_assemble_dir_lockinfo);
	ULI_PROBE("Pdir_empty", Pdir_empty_lockinfo);
	ULI_PROBE("Pfs_create_file_set", Pfs_create_file_set_lockinfo);
	ULI_PROBE("Pcreate_root_file", Pcreate_root_file_lockinfo);
	ULI_PROBE("Pfs_init_ftx", Pfs_init_ftx_lockinfo);
	ULI_PROBE("Pfs_insert_undo", Pfs_insert_undo_lockinfo);
	
	/* kernel/msfs/fs/fs_file_sets.c */
	ULI_PROBE("Pfs_fset_create", Pfs_fset_create_lockinfo);
	ULI_PROBE("Pfs_fset_get_id", Pfs_fset_get_id_lockinfo);
	ULI_PROBE("Pfs_fset_get_stats", Pfs_fset_get_stats_lockinfo);
	ULI_PROBE("Pfs_fset_delete", Pfs_fset_delete_lockinfo);
	ULI_PROBE("Pfs_fset_clone", Pfs_fset_clone_lockinfo);
	ULI_PROBE("Pfs_fset_get_info", Pfs_fset_get_info_lockinfo);
	ULI_PROBE("Pfs_fset_name_change", Pfs_fset_name_change_lockinfo);
	ULI_PROBE("Pfs_create_frag", Pfs_create_frag_lockinfo);
	ULI_PROBE("Pfs_quick_frag_test", Pfs_quick_frag_test_lockinfo);
	ULI_PROBE("Pfs_delete_frag", Pfs_delete_frag_lockinfo);

        /* kernel/msfs/fs/fs_read_write.c */
        ULI_PROBE("Pfs_zero_fill_pages", Pfs_zero_fill_pages_lockinfo);
        ULI_PROBE("Pfs_read", Pfs_read_lockinfo);
        ULI_PROBE("Pfs_read_cntxt_access", Pfs_read_cntxt_access_lockinfo);
        ULI_PROBE("Pfs_read_cntxt_vp", Pfs_read_cntxt_vp_lockinfo);
        ULI_PROBE("Pfs_read_cntxt", Pfs_read_cntxt_lockinfo);
        ULI_PROBE("Pfs_read_vp", Pfs_read_vp_lockinfo);
        ULI_PROBE("Pfs_write", Pfs_write_lockinfo);
        ULI_PROBE("Pfs_write_cntxt_vp", Pfs_write_cntxt_vp_lockinfo);
        ULI_PROBE("Pfs_write_add_stg", Pfs_write_add_stg_lockinfo);
        ULI_PROBE("Pcopy_and_del_frag", Pcopy_and_del_frag_lockinfo);
        ULI_PROBE("Pbcopy_frag", Pbcopy_frag_lockinfo);
        ULI_PROBE("Puiomove_frag", Puiomove_frag_lockinfo);

        /* kernel/msfs/fs/fs_quota.c */
        ULI_PROBE("PquotaUndoObsolete",PquotaUndoObsolete_lockinfo);
        ULI_PROBE("PquotaUndo", PquotaUndo_lockinfo);
        ULI_PROBE("Pchk_quota_write", Pchk_quota_write_lockinfo);
        ULI_PROBE("Pquota_init", Pquota_init_lockinfo);
        ULI_PROBE("Pquota_files_init", Pquota_files_init_lockinfo);
        ULI_PROBE("Pattach_quota", Pattach_quota_lockinfo);
        ULI_PROBE("Pdetach_quota", Pdetach_quota_lockinfo);
        ULI_PROBE("Pchk_blk_quota", Pchk_blk_quota_lockinfo);
        ULI_PROBE("Pchk_bf_quota", Pchk_bf_quota_lockinfo);
        ULI_PROBE("Pchk_bf_quota_chg", Pchk_bf_quota_chg_lockinfo);
        ULI_PROBE("Pvalidate_quota_status", Pvalidate_quota_status_lockinfo);
        ULI_PROBE("Pflush_time_limits", Pflush_time_limits_lockinfo);
        ULI_PROBE("Pget_quota_config", Pget_quota_config_lockinfo);
        ULI_PROBE("Pfs_quota_blks", Pfs_quota_blks_lockinfo);
        ULI_PROBE("Pchkdquot", Pchkdquot_lockinfo);
        ULI_PROBE("Pget_quota_blks_used", Pget_quota_blks_used_lockinfo);
        ULI_PROBE("Popmntque", Popmntque_lockinfo);
        ULI_PROBE("Pqi_init", Pqi_init_lockinfo);
        ULI_PROBE("Pqf_get", Pqf_get_lockinfo);
        ULI_PROBE("Pquota_activate", Pquota_activate_lockinfo);
        ULI_PROBE("Pquota_deactivate", Pquota_deactivate_lockinfo);
        ULI_PROBE("Padvfs_enforce_on", Padvfs_enforce_on_lockinfo);
        ULI_PROBE("Padvfs_enforce_off", Padvfs_enforce_off_lockinfo);
        ULI_PROBE("Padvfs_maint_on", Padvfs_maint_on_lockinfo);
        ULI_PROBE("Padvfs_maint_off", Padvfs_maint_off_lockinfo);
        ULI_PROBE("Padvfs_quota_chown", Padvfs_quota_chown_lockinfo);
        ULI_PROBE("Padvfs_get_quota", Padvfs_get_quota_lockinfo);
        ULI_PROBE("Padvfs_set_quota", Padvfs_set_quota_lockinfo);
        ULI_PROBE("Padvfs_set_use", Padvfs_set_use_lockinfo);
        ULI_PROBE("Padvfs_quota_sync", Padvfs_quota_sync_lockinfo);
        ULI_PROBE("Pmutex_lock_try", Pmutex_lock_try_lockinfo);
        ULI_PROBE("Pdqinit", Pdqinit_lockinfo);
        ULI_PROBE("Pdqget", Pdqget_lockinfo);
        ULI_PROBE("Pdqput", Pdqput_lockinfo);
        ULI_PROBE("Pdqsync",Pdqsync_lockinfo);
        ULI_PROBE("Pdqflush", Pdqflush_lockinfo);

	/* kernel/msfs/osf/msfs_misc.c */
	ULI_PROBE("Posf_fd_to_bfh", Posf_fd_to_bfh_lockinfo);
	ULI_PROBE("Pfscontext_lock_init", Pfscontext_lock_init_lockinfo);
	ULI_PROBE("Pvnode_fscontext_allocate", Pvnode_fscontext_allocate_lockinfo);
	ULI_PROBE("Pvnode_fscontext_deallocate", Pvnode_fscontext_deallocate_lockinfo);
	ULI_PROBE("Pbf_get_l", Pbf_get_l_lockinfo);
	ULI_PROBE("Pmsfs_inactive", Pmsfs_inactive_lockinfo);
	ULI_PROBE("Pmsfs_reclaim", Pmsfs_reclaim_lockinfo);
	ULI_PROBE("Pcopy_frag_into_vm_page", Pcopy_frag_into_vm_page_lockinfo);
	ULI_PROBE("Pmsfs_putpage", Pmsfs_putpage_lockinfo);
	ULI_PROBE("Pmsfs_getpage", Pmsfs_getpage_lockinfo);
	ULI_PROBE("Pcopy_frag_into_page", Pcopy_frag_into_page_lockinfo);
	ULI_PROBE("Pmsfs_mmap", Pmsfs_mmap_lockinfo);
	ULI_PROBE("Pmsfs_bread", Pmsfs_bread_lockinfo);
	ULI_PROBE("Pmsfs_brelse", Pmsfs_brelse_lockinfo);

	/* kernel/msfs/osf/msfs_vnops.c */
        ULI_PROBE("Pmsfs_create", Pmsfs_create_lockinfo);
        ULI_PROBE("Pmsfs_mknod", Pmsfs_mknod_lockinfo);
        ULI_PROBE("Pmsfs_close", Pmsfs_close_lockinfo);
        ULI_PROBE("Pmsfs_access", Pmsfs_access_lockinfo);
        ULI_PROBE("Pmsfs_getattr", Pmsfs_getattr_lockinfo);
        ULI_PROBE("Pmsfs_setattr", Pmsfs_setattr_lockinfo);
        ULI_PROBE("Pmsfs_read", Pmsfs_read_lockinfo);
        ULI_PROBE("Pmsfs_write", Pmsfs_write_lockinfo);
        ULI_PROBE("Pmsfs_fsync", Pmsfs_fsync_lockinfo);
        ULI_PROBE("Pmsfs_seek", Pmsfs_seek_lockinfo);
        ULI_PROBE("Pmsfs_remove", Pmsfs_remove_lockinfo);
        ULI_PROBE("Pmsfs_link", Pmsfs_link_lockinfo);
        ULI_PROBE("Pmsfs_rename", Pmsfs_rename_lockinfo);
        ULI_PROBE("Pdecr_link_count", Pdecr_link_count_lockinfo);
        ULI_PROBE("Pmsfs_mkdir", Pmsfs_mkdir_lockinfo);
        ULI_PROBE("Pmsfs_rmdir", Pmsfs_rmdir_lockinfo);
        ULI_PROBE("Pmsfs_symlink", Pmsfs_symlink_lockinfo);
        ULI_PROBE("Pmsfs_readdir", Pmsfs_readdir_lockinfo);
        ULI_PROBE("Pmsfs_readlink", Pmsfs_readlink_lockinfo);
        ULI_PROBE("Pmsfs_page_read", Pmsfs_page_read_lockinfo);
        ULI_PROBE("Pmsfs_page_write", Pmsfs_page_write_lockinfo);
        ULI_PROBE("Pmsfsspec_read", Pmsfsspec_read_lockinfo);
        ULI_PROBE("Pmsfsspec_write", Pmsfsspec_write_lockinfo);
        ULI_PROBE("Pmsfsspec_close", Pmsfsspec_close_lockinfo);
        ULI_PROBE("Pmsfsspec_reclaim", Pmsfsspec_reclaim_lockinfo);
        ULI_PROBE("Pmsfsfifo_read", Pmsfsfifo_read_lockinfo);
        ULI_PROBE("Pmsfsfifo_write", Pmsfsfifo_write_lockinfo);
        ULI_PROBE("Pmsfsfifo_close", Pmsfsfifo_close_lockinfo);
        ULI_PROBE("Pmsfsfifo_getattr", Pmsfsfifo_getattr_lockinfo);
        ULI_PROBE("Pmsfs_chown", Pmsfs_chown_lockinfo);
        ULI_PROBE("Pmsfs_chmod", Pmsfs_chmod_lockinfo);
        ULI_PROBE("Pattach_undel_dir", Pattach_undel_dir_lockinfo);
        ULI_PROBE("Pdetach_undel_dir", Pdetach_undel_dir_lockinfo);
        ULI_PROBE("Pget_undel_dir", Pget_undel_dir_lockinfo);
        ULI_PROBE("Pget_name", Pget_name_lockinfo);
        ULI_PROBE("Pget_name2", Pget_name2_lockinfo);
        ULI_PROBE("Pmsfs_lockctl", Pmsfs_lockctl_lockinfo);
        ULI_PROBE("Pmsfs_setvlocks", Pmsfs_setvlocks_lockinfo);
        ULI_PROBE("Pmsfs_syncdata", Pmsfs_syncdata_lockinfo);

	/* kernel/msfs/bs/bs_access.c */

	ULI_PROBE("Pbs_bf_htop", Pbs_bf_htop_lockinfo);
	ULI_PROBE("Pinit_access", Pinit_access_lockinfo);
	ULI_PROBE("Palloc_sublist", Palloc_sublist_lockinfo);
	ULI_PROBE("Pget_free_acc", Pget_free_acc_lockinfo);
	ULI_PROBE("Pfind_bfap", Pfind_bfap_lockinfo);
	ULI_PROBE("Paccess_invalidate", Paccess_invalidate_lockinfo);
	ULI_PROBE("Pbs_inval_rsvd_acc_st", Pbs_inval_rsvd_acc_st_lockinfo);
	ULI_PROBE("Pbs_init_area", Pbs_init_area_lockinfo);
	ULI_PROBE("Pbs_map_bf", Pbs_map_bf_lockinfo);
	ULI_PROBE("Pbs_insmntque", Pbs_insmntque_lockinfo);
	ULI_PROBE("Pbs_access", Pbs_access_lockinfo);
	ULI_PROBE("Prbf_access", Prbf_access_lockinfo);
	ULI_PROBE("Prbf_vfs_access", Prbf_vfs_access_lockinfo);
	ULI_PROBE("Pbfm_open_ms", Pbfm_open_ms_lockinfo);
	ULI_PROBE("Pbs_del_access", Pbs_del_access_lockinfo);
	ULI_PROBE("Prbf_access_int", Prbf_access_int_lockinfo);
	ULI_PROBE("Prbf_access_one_int", Prbf_access_one_int_lockinfo);
	ULI_PROBE("Pget_n_setup_new_vnode", Pget_n_setup_new_vnode_lockinfo);
	ULI_PROBE("Pgrab_bsacc", Pgrab_bsacc_lockinfo);
	ULI_PROBE("Pbs_close", Pbs_close_lockinfo);
	ULI_PROBE("Pbs_vfs_close", Pbs_vfs_close_lockinfo);
	ULI_PROBE("Pbs_close_one", Pbs_close_one_lockinfo);
	ULI_PROBE("Pbs_close_options", Pbs_close_options_lockinfo);
	ULI_PROBE("Pclose_int", Pclose_int_lockinfo);
	ULI_PROBE("Pclose_one_int", Pclose_one_int_lockinfo);
	ULI_PROBE("Pbs_unhook_vnode", Pbs_unhook_vnode_lockinfo);
	ULI_PROBE("Pbf_setup_truncation", Pbf_setup_truncation_lockinfo);
	/* ULI_PROBE("Preturn_bsacc_refcnt", Preturn_bsacc_refcnt_lockinfo);*/
	ULI_PROBE("Pbs_get_current_tag", Pbs_get_current_tag_lockinfo);
	/* ULI_PROBE("Paccess_test", Paccess_test_lockinfo); */
	ULI_PROBE("Pcheck_busy", Pcheck_busy_lockinfo);
	ULI_PROBE("Pcheck_mv_bfap_to_free", Pcheck_mv_bfap_to_free_lockinfo);
	ULI_PROBE("Pcleanup_closed_list", Pcleanup_closed_list_lockinfo);

	/* kernel/msfs/bs/bs_bmt_util.c		*/

	ULI_PROBE("Palloc_link_mcell_undo", Palloc_link_mcell_undo_lockinfo);
	ULI_PROBE("Palloc_mcell", Palloc_mcell_lockinfo);
	ULI_PROBE("Palloc_mcell_undo", Palloc_mcell_undo_lockinfo);
	ULI_PROBE("Palloc_page0_mcell", Palloc_page0_mcell_lockinfo);
	ULI_PROBE("Pbmt_alloc_link_mcell", Pbmt_alloc_link_mcell_lockinfo);
	ULI_PROBE("Pbmt_alloc_mcell", Pbmt_alloc_mcell_lockinfo);
	ULI_PROBE("Pbmt_alloc_prim_mcell", Pbmt_alloc_prim_mcell_lockinfo);
	ULI_PROBE("Pbmt_alloc_prim_mcell", Pbmt_alloc_prim_mcell_lockinfo);
	ULI_PROBE("Pbmt_close", Pbmt_close_lockinfo);
	ULI_PROBE("Pbmt_extend", Pbmt_extend_lockinfo);
	ULI_PROBE("Pbmt_find_mcell", Pbmt_find_mcell_lockinfo);
	ULI_PROBE("Pbmt_free_bf_mcells", Pbmt_free_bf_mcells_lockinfo);
	ULI_PROBE("Pbmt_free_bf_mcells_2", Pbmt_free_bf_mcells_2_lockinfo);
	ULI_PROBE("Pbmt_free_bf_mcells_i", Pbmt_free_bf_mcells_i_lockinfo);
	ULI_PROBE("Pbmt_free_mcell", Pbmt_free_mcell_lockinfo);
	ULI_PROBE("Pbmt_get_vd_bf_descs", Pbmt_get_vd_bf_descs_lockinfo);
	ULI_PROBE("Pbmt_init_page", Pbmt_init_page_lockinfo);
	ULI_PROBE("Pbmt_link_mcells", Pbmt_link_mcells_lockinfo);
	ULI_PROBE("Pbmt_open", Pbmt_open_lockinfo);
	ULI_PROBE("Pbmt_read", Pbmt_read_lockinfo);
	ULI_PROBE("Pbmt_set_mcell_free_list", Pbmt_set_mcell_free_list_lockinfo);
	ULI_PROBE("Pbmt_unlink_mcells", Pbmt_unlink_mcells_lockinfo);
	ULI_PROBE("Pbmt_upd_mcell_free_list", Pbmt_upd_mcell_free_list_lockinfo);
	ULI_PROBE("Pbmtr_assign", Pbmtr_assign_lockinfo);
	ULI_PROBE("Pbmtr_assign_rec", Pbmtr_assign_rec_lockinfo);
	ULI_PROBE("Pbmtr_clone_mcell", Pbmtr_clone_mcell_lockinfo);
	ULI_PROBE("Pbmtr_clone_recs", Pbmtr_clone_recs_lockinfo);
	ULI_PROBE("Pbmtr_create_rec", Pbmtr_create_rec_lockinfo);
	ULI_PROBE("Pbmtr_find", Pbmtr_find_lockinfo);
	ULI_PROBE("Pbmtr_get_rec_n_lk", Pbmtr_get_rec_n_lk_lockinfo);
	ULI_PROBE("Pbmtr_get_rec_ptr", Pbmtr_get_rec_ptr_lockinfo);
	ULI_PROBE("Pbmtr_put_rec_n_unlk", Pbmtr_put_rec_n_unlk_lockinfo);
	ULI_PROBE("Pbmtr_put_rec_n_unlk_int", Pbmtr_put_rec_n_unlk_int_lockinfo);
	ULI_PROBE("Pbmtr_put_rec_undo_opx", Pbmtr_put_rec_undo_opx_lockinfo);
	ULI_PROBE("Pbmtr_scan", Pbmtr_scan_lockinfo);
	ULI_PROBE("Pbmtr_scan_mcells", Pbmtr_scan_mcells_lockinfo);
	ULI_PROBE("Pbmtr_update_rec", Pbmtr_update_rec_lockinfo);
	ULI_PROBE("Pbmtr_update_rec_int", Pbmtr_update_rec_int_lockinfo);
	ULI_PROBE("Pbmtr_update_rec_n_unlk", Pbmtr_update_rec_n_unlk_lockinfo);
	ULI_PROBE("Pextend_bmt_redo_opx", Pextend_bmt_redo_opx_lockinfo);
	ULI_PROBE("Pfree_mcell_chains_opx", Pfree_mcell_chains_opx_lockinfo);
	ULI_PROBE("Pinit_bs_bmt_util_opx", Pinit_bs_bmt_util_opx_lockinfo);
	ULI_PROBE("Pinit_mcell", Pinit_mcell_lockinfo);
	ULI_PROBE("Plink_mcells", Plink_mcells_lockinfo);
	ULI_PROBE("Plink_unlink_mcells_undo", Plink_unlink_mcells_undo_lockinfo);
	ULI_PROBE("Pallocate_link_new_mcell", Pallocate_link_new_mcell_lockinfo);
	ULI_PROBE("Pbmtr_find_check", Pbmtr_find_check_lockinfo);

	/* kernel/msfs/bs/bs_domain.c		*/

	ULI_PROBE("Pbs_bfdmn_activate", Pbs_bfdmn_activate_lockinfo);
	ULI_PROBE("Pbs_bfdmn_deactivate", Pbs_bfdmn_deactivate_lockinfo);
	ULI_PROBE("Pbs_bfdmn_flush", Pbs_bfdmn_flush_lockinfo);
	ULI_PROBE("Pbs_bfdmn_flush_all", Pbs_bfdmn_flush_all_lockinfo);
	ULI_PROBE("Pbs_bfdmn_flush_bfrs", Pbs_bfdmn_flush_bfrs_lockinfo);
	ULI_PROBE("Pbs_bfdmn_flush_sync", Pbs_bfdmn_flush_sync_lockinfo);
	ULI_PROBE("Pbs_bfdmn_id_activate", Pbs_bfdmn_id_activate_lockinfo);
	ULI_PROBE("Pbs_bfdmn_tbl_activate", Pbs_bfdmn_tbl_activate_lockinfo);
	ULI_PROBE("Pbs_bfset_get_dev", Pbs_bfset_get_dev_lockinfo);
	ULI_PROBE("Pbs_dmn_change", Pbs_dmn_change_lockinfo);
	ULI_PROBE("Pbs_domain_access", Pbs_domain_access_lockinfo);
	ULI_PROBE("Pbs_domain_close", Pbs_domain_close_lockinfo);
	ULI_PROBE("Pbs_get_dmntbl_params", Pbs_get_dmntbl_params_lockinfo);
	ULI_PROBE("Pbs_sync", Pbs_sync_lockinfo);
	ULI_PROBE("Pbs_vd_add_active", Pbs_vd_add_active_lockinfo);
	ULI_PROBE("Pbs_vd_remove_active", Pbs_vd_remove_active_lockinfo);
	ULI_PROBE("Pclear_bmt", Pclear_bmt_lockinfo);
	ULI_PROBE("Pdmn_alloc", Pdmn_alloc_lockinfo);
	ULI_PROBE("Pdmn_dealloc", Pdmn_dealloc_lockinfo);
	ULI_PROBE("Pdomain_lookup", Pdomain_lookup_lockinfo);
	ULI_PROBE("Pdomain_name_lookup", Pdomain_name_lookup_lockinfo);
	ULI_PROBE("Pfind_del_entry", Pfind_del_entry_lockinfo);
	ULI_PROBE("Pfree_vdds", Pfree_vdds_lockinfo);
	ULI_PROBE("Pget_domain_disks", Pget_domain_disks_lockinfo);
	ULI_PROBE("Pget_domain_major", Pget_domain_major_lockinfo);
	ULI_PROBE("Pget_raw_vd_attrs", Pget_raw_vd_attrs_lockinfo);
	ULI_PROBE("Pget_vdd", Pget_vdd_lockinfo);
	ULI_PROBE("Pmega_presto_start", Pmega_presto_start_lockinfo);
	ULI_PROBE("Pmega_touch_presto", Pmega_touch_presto_lockinfo);
	ULI_PROBE("Pscan_rsvd_file_xtnt_map", Pscan_rsvd_file_xtnt_map_lockinfo);
	ULI_PROBE("Pset_disk_count", Pset_disk_count_lockinfo);
	ULI_PROBE("Pset_vd_mounted", Pset_vd_mounted_lockinfo);
	ULI_PROBE("Psetup_vd", Psetup_vd_lockinfo);
	ULI_PROBE("Pstrcat", Pstrcat_lockinfo);
	ULI_PROBE("Pvd_alloc", Pvd_alloc_lockinfo);
	ULI_PROBE("Pvd_alloc_index", Pvd_alloc_index_lockinfo);
	ULI_PROBE("Pvd_dup", Pvd_dup_lockinfo);
	ULI_PROBE("Pvd_free", Pvd_free_lockinfo);
	ULI_PROBE("Pvd_remove", Pvd_remove_lockinfo);
	ULI_PROBE("Pwait_for_ddl_active_entry", Pwait_for_ddl_active_entry_lockinfo);
	ULI_PROBE("Pset_recovery_failed", Pset_recovery_failed_lockinfo);

	/* kernel/msfs/bs/bs_extents.c		*/

	ULI_PROBE("Pcreate_xtnt_map_hdr", Pcreate_xtnt_map_hdr_lockinfo);
	ULI_PROBE("Pinit_bs_xtnts_opx", Pinit_bs_xtnts_opx_lockinfo);
	ULI_PROBE("Pinsert_xtnt_chain", Pinsert_xtnt_chain_lockinfo);
	ULI_PROBE("Pload_from_bmt_xtra_xtnt_rec", Pload_from_bmt_xtra_xtnt_rec_lockinfo);
	ULI_PROBE("Pload_from_shadow_rec", Pload_from_shadow_rec_lockinfo);
	ULI_PROBE("Pload_from_xtnt_array", Pload_from_xtnt_array_lockinfo);
	ULI_PROBE("Pload_from_xtnt_rec", Pload_from_xtnt_rec_lockinfo);
	ULI_PROBE("Pload_from_xtra_xtnt_rec", Pload_from_xtra_xtnt_rec_lockinfo);
	ULI_PROBE("Pload_inmem_xtnt_map", Pload_inmem_xtnt_map_lockinfo);
	ULI_PROBE("Podm_check_xtnt_map", Podm_check_xtnt_map_lockinfo);
	ULI_PROBE("Podm_create_xtnt_map", Podm_create_xtnt_map_lockinfo);
	ULI_PROBE("Podm_create_xtnt_rec", Podm_create_xtnt_rec_lockinfo);
	ULI_PROBE("Podm_fix_rsvd_file_xtnt_map", Podm_fix_rsvd_file_xtnt_map_lockinfo);
	ULI_PROBE("Podm_print_xtnt_map", Podm_print_xtnt_map_lockinfo);
	ULI_PROBE("Podm_remove_mcells_from_xtnt_map", Podm_remove_mcells_from_xtnt_map_lockinfo);
	ULI_PROBE("Podm_rewrite_xtnt_map", Podm_rewrite_xtnt_map_lockinfo);
	ULI_PROBE("Premove_xtnt_chain", Premove_xtnt_chain_lockinfo);
	ULI_PROBE("Pundo_insert_remove_xtnt_chain", Pundo_insert_remove_xtnt_chain_lockinfo);
	ULI_PROBE("Pundo_mcell_cnt", Pundo_mcell_cnt_lockinfo);
	ULI_PROBE("Pundo_upd_xtnt_rec", Pundo_upd_xtnt_rec_lockinfo);
	ULI_PROBE("Pundo_zero", Pundo_zero_lockinfo);
	ULI_PROBE("Pupdate_mcell_cnt", Pupdate_mcell_cnt_lockinfo);
	ULI_PROBE("Pupdate_xtnt_array", Pupdate_xtnt_array_lockinfo);
	ULI_PROBE("Pupdate_xtnt_rec", Pupdate_xtnt_rec_lockinfo);
	ULI_PROBE("Px_create_inmem_xtnt_map", Px_create_inmem_xtnt_map_lockinfo);
	ULI_PROBE("Px_create_shadow_rec", Px_create_shadow_rec_lockinfo);
	ULI_PROBE("Px_delete_shadow_rec", Px_delete_shadow_rec_lockinfo);
	ULI_PROBE("Px_load_inmem_xtnt_map", Px_load_inmem_xtnt_map_lockinfo);
	ULI_PROBE("Px_update_ondisk_xtnt_map", Px_update_ondisk_xtnt_map_lockinfo);

	/* kernel/msfs/bs/bs_init.c		*/

	ULI_PROBE("Pbs_dmn_init", Pbs_dmn_init_lockinfo);
	ULI_PROBE("Pbs_disk_init", Pbs_disk_init_lockinfo);
	ULI_PROBE("Pbmt_init_mcell_free_list", Pbmt_init_mcell_free_list_lockinfo);
	ULI_PROBE("Pdel_init_mcell_list", Pdel_init_mcell_list_lockinfo);
	ULI_PROBE("Ptagdir_init_pg0", Ptagdir_init_pg0_lockinfo);
	ULI_PROBE("Pinit_sbm", Pinit_sbm_lockinfo);

	/* kernel/msfs/bs/bs_inmem_map.c	*/

	ULI_PROBE("Pimm_create_xtnt_map", Pimm_create_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_init_xtnt_map", Pimm_init_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_extend_xtnt_map", Pimm_extend_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_get_first_xtnt_desc", Pimm_get_first_xtnt_desc_lockinfo);
	ULI_PROBE("Pimm_get_xtnt_desc", Pimm_get_xtnt_desc_lockinfo);
	ULI_PROBE("Pimm_get_next_xtnt_desc", Pimm_get_next_xtnt_desc_lockinfo);
	ULI_PROBE("Pimm_delete_xtnt_map", Pimm_delete_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_delete_sub_xtnt_maps", Pimm_delete_sub_xtnt_maps_lockinfo);
	ULI_PROBE("Pimm_init_sub_xtnt_map", Pimm_init_sub_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_copy_sub_xtnt_map", Pimm_copy_sub_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_extend_sub_xtnt_map", Pimm_extend_sub_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_load_sub_xtnt_map", Pimm_load_sub_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_unload_sub_xtnt_map", Pimm_unload_sub_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_copy_xtnt_descs", Pimm_copy_xtnt_descs_lockinfo);
	ULI_PROBE("Pimm_split_desc", Pimm_split_desc_lockinfo);
	ULI_PROBE("Pmm_get_alloc_page_cnt", Pmm_get_alloc_page_cnt_lockinfo);
	ULI_PROBE("Pget_sub_xtnt_map_alloc_page_cnt", Pget_sub_xtnt_map_alloc_page_cnt_lockinfo);
	ULI_PROBE("Pimm_get_next_page", Pimm_get_next_page_lockinfo);
	ULI_PROBE("Pimm_get_first_hole", Pimm_get_first_hole_lockinfo);
	ULI_PROBE("Pimm_get_hole_size", Pimm_get_hole_size_lockinfo);
	ULI_PROBE("Pimm_get_page_type", Pimm_get_page_type_lockinfo);
	ULI_PROBE("Pimm_set_next_valid_copy_page", Pimm_set_next_valid_copy_page_lockinfo);
	ULI_PROBE("Pimm_page_to_sub_xtnt_map", Pimm_page_to_sub_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_page_to_xtnt", Pimm_page_to_xtnt_lockinfo);
	ULI_PROBE("Pimm_overlay_xtnt_map", Pimm_overlay_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_merge_xtnt_map", Pimm_merge_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_remove_page_map", Pimm_remove_page_map_lockinfo);
	ULI_PROBE("Pimm_check_xtnt_map", Pimm_check_xtnt_map_lockinfo);
	ULI_PROBE("Pimm_print_xtnt_map", Pimm_print_xtnt_map_lockinfo);

	/* kernel/msfs/bs/bs_migrate.c		*/

	ULI_PROBE("Pmig_register_migrate_agent", Pmig_register_migrate_agent_lockinfo);
	ULI_PROBE("Pbs_migrate", Pbs_migrate_lockinfo);
	ULI_PROBE("Pmig_migrate", Pmig_migrate_lockinfo);
	ULI_PROBE("Pmigrate_normal_one_disk", Pmigrate_normal_one_disk_lockinfo);
	ULI_PROBE("Pmigrate_normal", Pmigrate_normal_lockinfo);
	ULI_PROBE("Pmigrate_stripe", Pmigrate_stripe_lockinfo);
	ULI_PROBE("Pget_xm_page_range_info", Pget_xm_page_range_info_lockinfo);
	ULI_PROBE("Pextend_page_range_list", Pextend_page_range_list_lockinfo);
	ULI_PROBE("Pswitch_stg", Pswitch_stg_lockinfo);
	ULI_PROBE("Pbs_move_metadata", Pbs_move_metadata_lockinfo);
	ULI_PROBE("Pmove_metadata", Pmove_metadata_lockinfo);
	ULI_PROBE("Pset_block_map", Pset_block_map_lockinfo);
	ULI_PROBE("Palloc_copy_stg", Palloc_copy_stg_lockinfo);
	ULI_PROBE("Palloc_hole_stg", Palloc_hole_stg_lockinfo);

	/* kernel/msfs/bs/bs_misc.c		*/

	ULI_PROBE("Powner_or_suser", Powner_or_suser_lockinfo);
	ULI_PROBE("Pcopyin_domain_and_set_names", Pcopyin_domain_and_set_names_lockinfo);
	ULI_PROBE("Pfree_domain_and_set_names", Pfree_domain_and_set_names_lockinfo);
	ULI_PROBE("Popen_domain", Popen_domain_lockinfo);
	ULI_PROBE("Popen_set", Popen_set_lockinfo);
	ULI_PROBE("Pmsfs_real_syscall", Pmsfs_real_syscall_lockinfo);
	ULI_PROBE("Pbs_inherit", Pbs_inherit_lockinfo);
	ULI_PROBE("Pbs_inherit_init", Pbs_inherit_init_lockinfo);

	/* kernel/msfs/bs/bs_msg_queue.c */
	ULI_PROBE("Pmsgq_create", Pmsgq_create_lockinfo);
	ULI_PROBE("Pmsgq_alloc_msg", Pmsgq_alloc_msg_lockinfo);
	ULI_PROBE("Pmsgq_send_msg", Pmsgq_send_msg_lockinfo);
	ULI_PROBE("Pmsgq_recv_msg", Pmsgq_recv_msg_lockinfo);
	ULI_PROBE("Pmsgq_free_msg", Pmsgq_free_msg_lockinfo);
	ULI_PROBE("Pulmq_alloc_msg", Pulmq_alloc_msg_lockinfo);
	ULI_PROBE("Pulmq_send_msg", Pulmq_send_msg_lockinfo);
	ULI_PROBE("Pulmq_recv_msg", Pulmq_recv_msg_lockinfo);
	ULI_PROBE("Pulmq_free_msg", Pulmq_free_msg_lockinfo);

    /* bs/bs_buffer2.c PROBE stuff */
    ULI_PROBE("Pbs_cache_init", Pbs_cache_init_lockinfo);
    ULI_PROBE("Ppage_lookup", Ppage_lookup_lockinfo);
    ULI_PROBE("Pmap_pages", Pmap_pages_lockinfo);
    ULI_PROBE("Pblkmap", Pblkmap_lockinfo);
    ULI_PROBE("Pbs_refpg_unshelve", Pbs_refpg_unshelve_lockinfo);
    ULI_PROBE("Pbs_refpg_get", Pbs_refpg_get_lockinfo);
    ULI_PROBE("Pbs_refpg", Pbs_refpg_lockinfo);
    ULI_PROBE("Pbs_refpg_fetch", Pbs_refpg_fetch_lockinfo);
    ULI_PROBE("Pbs_refpg_int", Pbs_refpg_int_lockinfo);
    ULI_PROBE("Pbs_derefpg", Pbs_derefpg_lockinfo);
    ULI_PROBE("Pbs_pinpg", Pbs_pinpg_lockinfo);
    ULI_PROBE("Pbs_pinpg_ftx", Pbs_pinpg_ftx_lockinfo);
    ULI_PROBE("Pbs_pinpg_put", Pbs_pinpg_put_lockinfo);
    ULI_PROBE("Pbs_pinpg_unshelve", Pbs_pinpg_unshelve_lockinfo);
    ULI_PROBE("Pbs_pinpg_clone", Pbs_pinpg_clone_lockinfo);
    ULI_PROBE("Pbs_pinpg_int", Pbs_pinpg_int_lockinfo);
    ULI_PROBE("Pbs_pinpg_one_int", Pbs_pinpg_one_int_lockinfo);
    ULI_PROBE("Pbs_unpinpg", Pbs_unpinpg_lockinfo);
    ULI_PROBE("Pbs_find_page", Pbs_find_page_lockinfo);
    ULI_PROBE("Pfind_page", Pfind_page_lockinfo);
    ULI_PROBE("P_state_block", P_state_block_lockinfo);
    ULI_PROBE("Pbs_set_bufstate", Pbs_set_bufstate_lockinfo);
    ULI_PROBE("Pbs_clear_bufstate", Pbs_clear_bufstate_lockinfo);
    ULI_PROBE("Pbs_get_bufstate", Pbs_get_bufstate_lockinfo);
    ULI_PROBE("Pset_state", Pset_state_lockinfo);
    ULI_PROBE("Pwait_state", Pwait_state_lockinfo);
    ULI_PROBE("Pclear_state", Pclear_state_lockinfo);
    ULI_PROBE("Pbuf_remap", Pbuf_remap_lockinfo);
    ULI_PROBE("Pget_freebuf", Pget_freebuf_lockinfo);
    ULI_PROBE("Pclear_buf", Pclear_buf_lockinfo);
    ULI_PROBE("Pseq_ahead_cont", Pseq_ahead_cont_lockinfo);
    ULI_PROBE("Pprefetch", Pprefetch_lockinfo);
    ULI_PROBE("Pseq_ahead_start", Pseq_ahead_start_lockinfo);
    ULI_PROBE("Pseq_ahead", Pseq_ahead_lockinfo);
    ULI_PROBE("Pbs_real_invalidate_pg", Pbs_real_invalidate_pg_lockinfo);
    ULI_PROBE("Pbs_purge_dirty", Pbs_purge_dirty_lockinfo);
    ULI_PROBE("Pbs_cache_rundown", Pbs_cache_rundown_lockinfo);
    ULI_PROBE("Pbfr_trace", Pbfr_trace_lockinfo);
    ULI_PROBE("Pbs_get_rawbuf", Pbs_get_rawbuf_lockinfo);
    ULI_PROBE("Pbs_put_rawbuf", Pbs_put_rawbuf_lockinfo);
    ULI_PROBE("Pbs_clear_rawbuf", Pbs_clear_rawbuf_lockinfo);
    ULI_PROBE("Punpin_sync", Punpin_sync_lockinfo);
    ULI_PROBE("Pbs_put_freebuf", Pbs_put_freebuf_lockinfo);
    ULI_PROBE("Pbs_notify_fsync_waiter", Pbs_notify_fsync_waiter_lockinfo);
    ULI_PROBE("Pcall_clear_buf", Pcall_clear_buf_lockinfo);

    /* bs/bs_copy.c probe stuff */
    ULI_PROBE("Pcp_copy_page_range", Pcp_copy_page_range_lockinfo);
    ULI_PROBE("Pset_block_map", Pset_block_map_lockinfo);
    ULI_PROBE("Pverify_page_write", Pverify_page_write_lockinfo);
    ULI_PROBE("Pforce_write", Pforce_write_lockinfo);
    ULI_PROBE("Pcompare_copies", Pcompare_copies_lockinfo);
    ULI_PROBE("Pcp_insert_onto_xtnt_ma", Pcp_insert_onto_xtnt_ma_lockinfo);
    ULI_PROBE("Pcp_remove_from_xtnt_ma", Pcp_remove_from_xtnt_ma_lockinfo);
    ULI_PROBE("Pcp_alloc_stg", Pcp_alloc_stg_lockinfo);

    /* bs/bs_create.c probe stuff */
    ULI_PROBE("Prbf_create", Prbf_create_lockinfo);
    ULI_PROBE("Prbf_int_create", Prbf_int_create_lockinfo);
    ULI_PROBE("Pcreate_rtdn_opx", Pcreate_rtdn_opx_lockinfo);
    ULI_PROBE("Pmake_mcell_valid", Pmake_mcell_valid_lockinfo);
    ULI_PROBE("Pcreate_undo_opx", Pcreate_undo_opx_lockinfo);
    ULI_PROBE("Pbs_create", Pbs_create_lockinfo);
    ULI_PROBE("Pinit_bscreate_opx", Pinit_bscreate_opx_lockinfo);
    ULI_PROBE("Pnew_mcell", Pnew_mcell_lockinfo);
    ULI_PROBE("Pkill_mcell", Pkill_mcell_lockinfo);
    ULI_PROBE("Pdealloc_mcells", Pdealloc_mcells_lockinfo);

    /* bs/bs_delete.c probe stuff */
    ULI_PROBE("Pbs_deferred_delete_und", Pbs_deferred_delete_und_lockinfo);
    ULI_PROBE("Prbf_delete", Prbf_delete_lockinfo);
    ULI_PROBE("Prbf_delete_int", Prbf_delete_int_lockinfo);
    ULI_PROBE("Pbs_delete_undo_opx", Pbs_delete_undo_opx_lockinfo);
    ULI_PROBE("Preset_ondisk_bf_state", Preset_ondisk_bf_state_lockinfo);
    ULI_PROBE("Pbs_delete_rtdn_opx", Pbs_delete_rtdn_opx_lockinfo);
    ULI_PROBE("Pbs_delete", Pbs_delete_lockinfo);
    ULI_PROBE("Pinit_bs_delete_opx", Pinit_bs_delete_opx_lockinfo);
    ULI_PROBE("Pdel_add_to_del_list", Pdel_add_to_del_list_lockinfo);
    ULI_PROBE("Pdel_remove_from_del_li", Pdel_remove_from_del_li_lockinfo);
    ULI_PROBE("Pdel_bitfile_list_undo", Pdel_bitfile_list_undo_lockinfo);
    ULI_PROBE("Ppin_link", Ppin_link_lockinfo);
    ULI_PROBE("Ppin_hdr", Ppin_hdr_lockinfo);
    ULI_PROBE("Pdel_clean_mcell_list", Pdel_clean_mcell_list_lockinfo);
    ULI_PROBE("Pdel_dealloc_stg", Pdel_dealloc_stg_lockinfo);
    ULI_PROBE("Pdel_xtnt_array", Pdel_xtnt_array_lockinfo);
    ULI_PROBE("Pxfer_xtnts_to_clone", Pxfer_xtnts_to_clone_lockinfo);
    ULI_PROBE("Pdel_part_xtnt", Pdel_part_xtnt_lockinfo);
    ULI_PROBE("Pdel_range", Pdel_range_lockinfo);
    ULI_PROBE("Pdel_ftx_start", Pdel_ftx_start_lockinfo);
    ULI_PROBE("Pdel_ftx_done", Pdel_ftx_done_lockinfo);
    ULI_PROBE("Psbm_howmany_blks", Psbm_howmany_blks_lockinfo);
    ULI_PROBE("Pdel_find_del_entry", Pdel_find_del_entry_lockinfo);

	/* bs/bs_qio.c probe stuff */
	ULI_PROBE("Pcheck_queue", Pcheck_queue_lockinfo);
	ULI_PROBE("Pbs_q_blocking", Pbs_q_blocking_lockinfo);
	ULI_PROBE("Pbs_q_list", Pbs_q_list_lockinfo);
	ULI_PROBE("Pbs_io_complete", Pbs_io_complete_lockinfo);
	ULI_PROBE("Pcheck_cont_bits", Pcheck_cont_bits_lockinfo);
	ULI_PROBE("Pbs_pinblock", Pbs_pinblock_lockinfo);
	ULI_PROBE("Pbs_pinblock_sync", Pbs_pinblock_sync_lockinfo);
	ULI_PROBE("Plsn_io_list", Plsn_io_list_lockinfo);
	ULI_PROBE("Pbs_q_lazy", Pbs_q_lazy_lockinfo);
	ULI_PROBE("Pwait_to_readyq", Pwait_to_readyq_lockinfo);
	ULI_PROBE("Pready_to_consolq", Pready_to_consolq_lockinfo);
	ULI_PROBE("Psort_to_dev", Psort_to_dev_lockinfo);
	ULI_PROBE("Pcache_logflush", Pcache_logflush_lockinfo);
	ULI_PROBE("Pcall_logflush", Pcall_logflush_lockinfo);
	ULI_PROBE("Pbs_logpage_dirty", Pbs_logpage_dirty_lockinfo);
	ULI_PROBE("Pbs_logflush_start", Pbs_logflush_start_lockinfo);
	ULI_PROBE("Plogflush_cont", Plogflush_cont_lockinfo);
	ULI_PROBE("Pbs_logflush_sync", Pbs_logflush_sync_lockinfo);
	ULI_PROBE("Pbfflush_start", Pbfflush_start_lockinfo);
	ULI_PROBE("Pbfflush_sync", Pbfflush_sync_lockinfo);
	ULI_PROBE("Pbs_sync_bf_flush", Pbs_sync_bf_flush_lockinfo);
	ULI_PROBE("Pbfflush", Pbfflush_lockinfo);
	ULI_PROBE("Pbfflush_sync_nowait", Pbfflush_sync_nowait_lockinfo);
	ULI_PROBE("Pbs_bf_flush_nowait", Pbs_bf_flush_nowait_lockinfo);
	ULI_PROBE("Pbs_bflush", Pbs_bflush_lockinfo);
	ULI_PROBE("Pbs_bflush_sync", Pbs_bflush_sync_lockinfo);
	ULI_PROBE("Pflush_vols", Pflush_vols_lockinfo);
	ULI_PROBE("Prm_or_moveq", Prm_or_moveq_lockinfo);
	ULI_PROBE("Plink_write_req", Plink_write_req_lockinfo);
	ULI_PROBE("Prm_ioq", Prm_ioq_lockinfo);
	ULI_PROBE("Pbs_raw_page", Pbs_raw_page_lockinfo);
	ULI_PROBE("Psendtoiothread", Psendtoiothread_lockinfo);
	ULI_PROBE("Pbfflush_range", Pbfflush_range_lockinfo);

    /* bs/bs_tagdir.c probe stuff */
    ULI_PROBE("Ptagdir_get_info", Ptagdir_get_info_lockinfo);
    ULI_PROBE("Pinit_tagdir_opx", Pinit_tagdir_opx_lockinfo);
    ULI_PROBE("Ptagdir_remove_tag", Ptagdir_remove_tag_lockinfo);
    ULI_PROBE("Ptagdir_tag_to_freelist", Ptagdir_tag_to_freelist_lockinfo);
    ULI_PROBE("Ptagdir_freetag_dellist", Ptagdir_freetag_dellist_lockinfo);
    ULI_PROBE("Pinit_next_tag_page", Pinit_next_tag_page_lockinfo);
    ULI_PROBE("Ptagdir_alloc_tag", Ptagdir_alloc_tag_lockinfo);
    ULI_PROBE("Pextend_tagdir_redo_opx", Pextend_tagdir_redo_opx_lockinfo);
    ULI_PROBE("Ptagdir_insert_tag", Ptagdir_insert_tag_lockinfo);
    ULI_PROBE("Ptagdir_set_next_tag", Ptagdir_set_next_tag_lockinfo);
    ULI_PROBE("Ptagdir_reset_tagmap", Ptagdir_reset_tagmap_lockinfo);
    ULI_PROBE("Ptagdir_stuff_tagmap", Ptagdir_stuff_tagmap_lockinfo);
    ULI_PROBE("Ptagdir_set_tagmap_comm", Ptagdir_set_tagmap_comm_lockinfo);
    ULI_PROBE("Ptagdir_write_undo_opx", Ptagdir_write_undo_opx_lockinfo);
    ULI_PROBE("Ptagdir_lookup", Ptagdir_lookup_lockinfo);
    ULI_PROBE("Ptagdir_lookup2", Ptagdir_lookup2_lockinfo);
    ULI_PROBE("Ptagdir_lookup_next", Ptagdir_lookup_next_lockinfo);
    ULI_PROBE("Pbs_switch_root_tagdir", Pbs_switch_root_tagdir_lockinfo);
    ULI_PROBE("Pswitch_root_tagdir_red", Pswitch_root_tagdir_red_lockinfo);

    /* bs/bs_params probe stuff */
    ULI_PROBE("Pbs_get_bf_xtnt_map", Pbs_get_bf_xtnt_map_lockinfo);
    ULI_PROBE("Pbs_get_bkup_xtnt_map", Pbs_get_bkup_xtnt_map_lockinfo);
    ULI_PROBE("Pbs_delete_with_clone", Pbs_delete_with_clone_lockinfo);
    ULI_PROBE("Pbs_get_bf_page_cnt", Pbs_get_bf_page_cnt_lockinfo);
    ULI_PROBE("Pbs_get_bf_next_page", Pbs_get_bf_next_page_lockinfo);
    ULI_PROBE("Pbs_get_bf_page_sz", Pbs_get_bf_page_sz_lockinfo);
    ULI_PROBE("Pbs_get_bf_params", Pbs_get_bf_params_lockinfo);
    ULI_PROBE("Pbs_set_bf_params", Pbs_set_bf_params_lockinfo);
    ULI_PROBE("Pbs_get_bf_iparams", Pbs_get_bf_iparams_lockinfo);
    ULI_PROBE("Pbs_set_bf_iparams", Pbs_set_bf_iparams_lockinfo);
    ULI_PROBE("Pbs_get_dmn_vd_list", Pbs_get_dmn_vd_list_lockinfo);
    ULI_PROBE("Pbs_get_dmn_params", Pbs_get_dmn_params_lockinfo);
    ULI_PROBE("Pbs_set_dmn_params", Pbs_set_dmn_params_lockinfo);
    ULI_PROBE("Pbs_get_vd_params", Pbs_get_vd_params_lockinfo);
    ULI_PROBE("Pbs_set_vd_params", Pbs_set_vd_params_lockinfo);
    ULI_PROBE("Pbs_get_avail_mcells", Pbs_get_avail_mcells_lockinfo);

    /* bs/bs_service_class.c probe stuff */
    ULI_PROBE("Psc_init_sc_tbl", Psc_init_sc_tbl_lockinfo);
    ULI_PROBE("Psc_find_super_class", Psc_find_super_class_lockinfo);
    ULI_PROBE("Psc_find_alt_class", Psc_find_alt_class_lockinfo);
    ULI_PROBE("Psc_binSearchForClass", Psc_binSearchForClass_lockinfo);
    ULI_PROBE("Psc_add_class", Psc_add_class_lockinfo);
    ULI_PROBE("Psc_add_vd_to_class", Psc_add_vd_to_class_lockinfo);
    ULI_PROBE("Psc_add_vd", Psc_add_vd_lockinfo);
    ULI_PROBE("Psc_remove_class", Psc_remove_class_lockinfo);
    ULI_PROBE("Psc_remove_vd", Psc_remove_vd_lockinfo);
    ULI_PROBE("Psc_select_class", Psc_select_class_lockinfo);
    ULI_PROBE("Psc_valid_vd", Psc_valid_vd_lockinfo);
    ULI_PROBE("Psc_select_vd_for_mcell", Psc_select_vd_for_mcell_lockinfo);
    ULI_PROBE("Psc_select_vd_for_stg", Psc_select_vd_for_stg_lockinfo);

    /* bs/bs_shadow.c probe stuff */
    ULI_PROBE("Psha_register_shadow_ag", Psha_register_shadow_ag_lockinfo);
    ULI_PROBE("Pundo_bitfile_type", Pundo_bitfile_type_lockinfo);
    ULI_PROBE("Pget_old_members", Pget_old_members_lockinfo);
    ULI_PROBE("Pextend_shadow_desc", Pextend_shadow_desc_lockinfo);
    ULI_PROBE("Pcreate_new_members", Pcreate_new_members_lockinfo);

    /* bs/bs_stripe.c probe_stuff */
    ULI_PROBE("Pstr_register_stripe_ag", Pstr_register_stripe_ag_lockinfo);
    ULI_PROBE("Pbs_stripe", Pbs_stripe_lockinfo);
    ULI_PROBE("Pstr_stripe", Pstr_stripe_lockinfo);
    ULI_PROBE("Pstripe_zero_size", Pstripe_zero_size_lockinfo);
    ULI_PROBE("Pstripe_nonzero_size", Pstripe_nonzero_size_lockinfo);
    ULI_PROBE("Pundo_xtnt_rec", Pundo_xtnt_rec_lockinfo);
    ULI_PROBE("Pupdate_xtnt_rec_fields", Pupdate_xtnt_rec_fields_lockinfo);
    ULI_PROBE("Pstr_create_stripe_hdr", Pstr_create_stripe_hdr_lockinfo);
    ULI_PROBE("Pstr_delete_stripe_hdr", Pstr_delete_stripe_hdr_lockinfo);
    ULI_PROBE("Pstr_calc_page_alloc", Pstr_calc_page_alloc_lockinfo);
    ULI_PROBE("Pstr_create_bf_rel_xtnt", Pstr_create_bf_rel_xtnt_lockinfo);
    ULI_PROBE("Pcreate_bf_rel_xtnt_des", Pcreate_bf_rel_xtnt_des_lockinfo);

    /* bs/ftx_recovery.c probe stuff */
    ULI_PROBE("Pftx_bfmeta_rec_redo", Pftx_bfmeta_rec_redo_lockinfo);
    ULI_PROBE("Pftx_bfdata_rec_redo", Pftx_bfdata_rec_redo_lockinfo);
    ULI_PROBE("Pftx_bfdmn_recovery", Pftx_bfdmn_recovery_lockinfo);
    ULI_PROBE("Pftx_recovery_pass", Pftx_recovery_pass_lockinfo);
    ULI_PROBE("Pnum_of_log_recs", Pnum_of_log_recs_lockinfo);

    /* msfs/bs/ftx_routines.c probe stuff */
    ULI_PROBE("Pftx_register_agent", Pftx_register_agent_lockinfo);
    ULI_PROBE("Pftx_register_agent_n", Pftx_register_agent_n_lockinfo);
    ULI_PROBE("Pftx_register_agent_n2", Pftx_register_agent_n2_lockinfo);
    ULI_PROBE("P_ftx_start_meta", P_ftx_start_meta_lockinfo);
    ULI_PROBE("P_ftx_start", P_ftx_start_lockinfo);
    ULI_PROBE("P_ftx_start_n", P_ftx_start_n_lockinfo);
    ULI_PROBE("P_ftx_start_exc", P_ftx_start_exc_lockinfo);
    ULI_PROBE("P_ftx_start_i", P_ftx_start_i_lockinfo);
    ULI_PROBE("Pnewftx", Pnewftx_lockinfo);
    ULI_PROBE("Pftx_done", Pftx_done_lockinfo);
    ULI_PROBE("Pftx_done_fs", Pftx_done_fs_lockinfo);
    ULI_PROBE("Pftx_done_n", Pftx_done_n_lockinfo);
    ULI_PROBE("Pftx_done_u", Pftx_done_u_lockinfo);
    ULI_PROBE("Pftx_done_urd", Pftx_done_urd_lockinfo);
    ULI_PROBE("Pftx_done_urdr", Pftx_done_urdr_lockinfo);
    ULI_PROBE("Pftx_quit", Pftx_quit_lockinfo);
    ULI_PROBE("Pftx_fail", Pftx_fail_lockinfo);
    ULI_PROBE("Pftx_fail_2", Pftx_fail_2_lockinfo);
    ULI_PROBE("Pftx_set_continuation", Pftx_set_continuation_lockinfo);
    ULI_PROBE("Pftx_special_done_mode", Pftx_special_done_mode_lockinfo);
    ULI_PROBE("Prbf_pinpg", Prbf_pinpg_lockinfo);
    ULI_PROBE("Prbf_deref_page", Prbf_deref_page_lockinfo);
    ULI_PROBE("Prbf_pin_record", Prbf_pin_record_lockinfo);
    ULI_PROBE("Paddone_undo", Paddone_undo_lockinfo);
    ULI_PROBE("Paddone_redo", Paddone_redo_lockinfo);
    ULI_PROBE("Paddone_rtdn", Paddone_rtdn_lockinfo);
    ULI_PROBE("Paddone_cont", Paddone_cont_lockinfo);
    ULI_PROBE("Paddone_recredo", Paddone_recredo_lockinfo);
    ULI_PROBE("Plog_donerec_nunpin", Plog_donerec_nunpin_lockinfo);
    ULI_PROBE("Pdo_ftx_continuations", Pdo_ftx_continuations_lockinfo);
    ULI_PROBE("Pget_perlvl_p", Pget_perlvl_p_lockinfo);
    ULI_PROBE("P_ftx_lock", P_ftx_lock_lockinfo);
    ULI_PROBE("P_ftx_add_lock", P_ftx_add_lock_lockinfo);
    ULI_PROBE("P_ftx_shared_lock", P_ftx_shared_lock_lockinfo);
    ULI_PROBE("P_ftx_exclusive_lock", P_ftx_exclusive_lock_lockinfo);
    ULI_PROBE("P_ftx_set_state", P_ftx_set_state_lockinfo);
    ULI_PROBE("Pftx_unlock", Pftx_unlock_lockinfo);
    ULI_PROBE("Prelease_ftx_locks", Prelease_ftx_locks_lockinfo);
    ULI_PROBE("Pget_ftx_id", Pget_ftx_id_lockinfo);
    ULI_PROBE("Pget_ftx_dmnh", Pget_ftx_dmnh_lockinfo);
    ULI_PROBE("Pftx_init", Pftx_init_lockinfo);
    ULI_PROBE("Pftx_free", Pftx_free_lockinfo);
    ULI_PROBE("Pftx_init_recovery_loga", Pftx_init_recovery_loga_lockinfo);
    ULI_PROBE("Pftx_get_dirtybufla", Pftx_get_dirtybufla_lockinfo);
    ULI_PROBE("Pftx_set_oldestftxla", Pftx_set_oldestftxla_lockinfo);
    ULI_PROBE("Pftx_get_oldestftxla", Pftx_get_oldestftxla_lockinfo);
    ULI_PROBE("Pftx_set_firstla", Pftx_set_firstla_lockinfo);
    ULI_PROBE("Preset_oldest_lsn", Preset_oldest_lsn_lockinfo);

    /* msfs/osf/msfs_proplist.c probe stuff */
    ULI_PROBE("Pmsfs_pl_register_agnts", Pmsfs_pl_register_agnts_lockinfo);
    ULI_PROBE("Pmsfs_pl_init_cur", Pmsfs_pl_init_cur_lockinfo);
    ULI_PROBE("Pmsfs_pl_cur_to_pnt", Pmsfs_pl_cur_to_pnt_lockinfo);
    ULI_PROBE("Pmsfs_pl_deref_cur", Pmsfs_pl_deref_cur_lockinfo);
    ULI_PROBE("Pmsfs_pl_pin_cur", Pmsfs_pl_pin_cur_lockinfo);
    ULI_PROBE("Pmsfs_pl_seek_cur", Pmsfs_pl_seek_cur_lockinfo);
    ULI_PROBE("Pmsfs_pl_next_mc_cur", Pmsfs_pl_next_mc_cur_lockinfo);
    ULI_PROBE("Pmsfs_setproplist", Pmsfs_setproplist_lockinfo);
    ULI_PROBE("Pmsfs_pl_set_entry", Pmsfs_pl_set_entry_lockinfo);
    ULI_PROBE("Pmsfs_pl_fill_hdr_image", Pmsfs_pl_fill_hdr_image_lockinfo);
    ULI_PROBE("Pmsfs_getproplist", Pmsfs_getproplist_lockinfo);
    ULI_PROBE("Pmsfs_pl_create_rec", Pmsfs_pl_create_rec_lockinfo);
    ULI_PROBE("Pmsfs_pl_get_entry", Pmsfs_pl_get_entry_lockinfo);
    ULI_PROBE("Pmsfs_pl_get_name", Pmsfs_pl_get_name_lockinfo);
    ULI_PROBE("Pmsfs_pl_get_data", Pmsfs_pl_get_data_lockinfo);
    ULI_PROBE("Pmsfs_delproplist", Pmsfs_delproplist_lockinfo);
    ULI_PROBE("Pmsfs_pl_del_root_done", Pmsfs_pl_del_root_done_lockinfo);
    ULI_PROBE("Pmsfs_pl_del_data_chain", Pmsfs_pl_del_data_chain_lockinfo);
    ULI_PROBE("Pmsfs_pl_unlink_mcells", Pmsfs_pl_unlink_mcells_lockinfo);

	/* kernel/msfs/fs/fs_dir_lookup.c	*/

	ULI_PROBE("Pinsert_seq", Pinsert_seq_lockinfo);
	ULI_PROBE("Premove_dir_ent", Premove_dir_ent_lockinfo);
	ULI_PROBE("Premove_dots", Premove_dots_lockinfo);
	ULI_PROBE("Pseq_search", Pseq_search_lockinfo);
	ULI_PROBE("Premove_bf", Premove_bf_lockinfo);
	ULI_PROBE("Ptag_search", Ptag_search_lockinfo);
	ULI_PROBE("Premove_entry", Premove_entry_lockinfo);
	ULI_PROBE("Pglom_dir_entries", Pglom_dir_entries_lockinfo);
	ULI_PROBE("Pdir_trunc_start", Pdir_trunc_start_lockinfo);
	ULI_PROBE("Pdir_trunc_finish", Pdir_trunc_finish_lockinfo);

        /* kernel/msfs/osf/msfs_vfsops.c */
        ULI_PROBE("Pmsfs_vptofh", Pmsfs_vptofh_lockinfo);
        ULI_PROBE("Padvfs_quotactl", Padvfs_quotactl_lockinfo);
        ULI_PROBE("Padvfs_quotactl_mp", Padvfs_quotactl_mp_lockinfo);
        ULI_PROBE("Padvfs_mountfs", Padvfs_mountfs_lockinfo);
        ULI_PROBE("Pmsfs_unmount", Pmsfs_unmount_lockinfo);
        ULI_PROBE("Pcheck_vd_sizes", Pcheck_vd_sizes_lockinfo);

        /* kernel/msfs/bs/bs_bitfile_sets.c */
        ULI_PROBE("Pbs_fragbf_thread", Pbs_fragbf_thread_lockinfo);
        ULI_PROBE("Pfrag_group_dealloc",Pfrag_group_dealloc_lockinfo);
        ULI_PROBE("Pfrag_group_init",Pfrag_group_init_lockinfo);
        ULI_PROBE("Pfrag_list_extend",Pfrag_list_extend_lockinfo);
        ULI_PROBE("Pbs_frag_alloc",Pbs_frag_alloc_lockinfo);
        ULI_PROBE("Pbs_frag_dealloc",Pbs_frag_dealloc_lockinfo);
        ULI_PROBE("Pbs_frag_has_stg",Pbs_frag_has_stg_lockinfo);
        ULI_PROBE("Pbs_fragbf_open",Pbs_fragbf_open_lockinfo);
        ULI_PROBE("Pbs_fragbf_close",Pbs_fragbf_close_lockinfo);
        ULI_PROBE("Pbs_bfs_init",Pbs_bfs_init_lockinfo);
        ULI_PROBE("Pbfs_lookup",Pbfs_lookup_lockinfo);
        ULI_PROBE("Pbfs_invalidate",Pbfs_invalidate_lockinfo);
        ULI_PROBE("Pbfs_alloc",Pbfs_alloc_lockinfo);
        ULI_PROBE("Pbfs_dealloc",Pbfs_dealloc_lockinfo);
        ULI_PROBE("Pbs_bfs_remove_all",Pbs_bfs_remove_all_lockinfo);
        ULI_PROBE("Pbs_bfs_get_handle",Pbs_bfs_get_handle_lockinfo);
        ULI_PROBE("Pbfs_create",Pbfs_create_lockinfo);
        ULI_PROBE("Prbf_bfs_create",Prbf_bfs_create_lockinfo);
        ULI_PROBE("Pbfs_close",Pbfs_close_lockinfo);
        ULI_PROBE("Pbs_bfs_close",Pbs_bfs_close_lockinfo);
        ULI_PROBE("Pbfs_access",Pbfs_access_lockinfo);
        ULI_PROBE("Pbfs_open",Pbfs_open_lockinfo);
        ULI_PROBE("Pdelete_orig_set_tags",Pdelete_orig_set_tags_lockinfo);
        ULI_PROBE("Pdelete_clone_set_tags",Pdelete_clone_set_tags_lockinfo);
        ULI_PROBE("Pbfs_delete_pending_list_add",Pbfs_delete_pending_list_add_lockinfo);
        ULI_PROBE("Pdel_list_remove_undo",Pdel_list_remove_undo_lockinfo);
        ULI_PROBE("Pbfs_delete_pending_list_remove",Pbfs_delete_pending_list_remove_lockinfo);
        ULI_PROBE("Pbfs_delete_pending_list_finish_all",Pbfs_delete_pending_list_finish_all_lockinfo);
        ULI_PROBE("Punlink_clone_undo",Punlink_clone_undo_lockinfo);
        ULI_PROBE("Punlink_clone",Punlink_clone_lockinfo);
        ULI_PROBE("Pbs_bfs_delete",Pbs_bfs_delete_lockinfo);
        ULI_PROBE("Pclone_tagdir",Pclone_tagdir_lockinfo);
        ULI_PROBE("Pbs_bfs_clone",Pbs_bfs_clone_lockinfo);
        ULI_PROBE("Pbs_bfs_out_of_sync",Pbs_bfs_out_of_sync_lockinfo);
        ULI_PROBE("Pbs_bfs_get_set_id",Pbs_bfs_get_set_id_lockinfo);
        ULI_PROBE("Pbs_bfs_get_clone_info",Pbs_bfs_get_clone_info_lockinfo);
        ULI_PROBE("Pbs_bfs_get_desc",Pbs_bfs_get_desc_lockinfo);
        ULI_PROBE("Pbs_bfs_add_root",Pbs_bfs_add_root_lockinfo);
        ULI_PROBE("Pbs_bfs_remove_root",Pbs_bfs_remove_root_lockinfo);
        ULI_PROBE("Pbs_bfs_switch_root_tagdir",Pbs_bfs_switch_root_tagdir_lockinfo);
        ULI_PROBE("Pbs_bfset_activate",Pbs_bfset_activate_lockinfo);
        ULI_PROBE("Pbs_bfset_deactivate",Pbs_bfset_deactivate_lockinfo);
        ULI_PROBE("Pbs_bfs_get_info",Pbs_bfs_get_info_lockinfo);
        ULI_PROBE("Pbs_bfs_find_set",Pbs_bfs_find_set_lockinfo);
        ULI_PROBE("Pnew_clone_mcell",Pnew_clone_mcell_lockinfo);
        ULI_PROBE("Pnew_clone_mcell_undo_opx",Pnew_clone_mcell_undo_opx_lockinfo);
        ULI_PROBE("Pinit_crmcell_opx",Pinit_crmcell_opx_lockinfo);
        ULI_PROBE("Pclone",Pclone_lockinfo);
        ULI_PROBE("Pbs_have_clone",Pbs_have_clone_lockinfo);
        ULI_PROBE("Pprint_out_of_sync_msg",Pprint_out_of_sync_msg_lockinfo);
        ULI_PROBE("Pbs_cow_pg",Pbs_cow_pg_lockinfo);
        ULI_PROBE("Pbs_cow",Pbs_cow_lockinfo);
        ULI_PROBE("Pbfs_upd_shelving_thresholds",Pbfs_upd_shelving_thresholds_lockinfo);
        ULI_PROBE("Pbs_get_bfset_params",Pbs_get_bfset_params_lockinfo);
        ULI_PROBE("Pbs_set_bfset_params",Pbs_set_bfset_params_lockinfo);
        ULI_PROBE("Prbf_set_bfset_params",Prbf_set_bfset_params_lockinfo);

        /* kernel/msfs/bs/ms_logger.c */
	ULI_PROBE("Plgr_lsn_gt", Plgr_lsn_gt_lockinfo);
	ULI_PROBE("Plgr_lsn_lt", Plgr_lsn_lt_lockinfo);
	ULI_PROBE("Plsn_add", Plsn_add_lockinfo);
	ULI_PROBE("Plsn_gt", Plsn_gt_lockinfo);
	ULI_PROBE("Plsn_lt", Plsn_lt_lockinfo);
	ULI_PROBE("Plgr_make_pg_safe", Plgr_make_pg_safe_lockinfo);
	ULI_PROBE("Plgr_valid_blk", Plgr_valid_blk_lockinfo);
	ULI_PROBE("Plgr_repair_pg", Plgr_repair_pg_lockinfo);
	ULI_PROBE("Plgr_complete_pg", Plgr_complete_pg_lockinfo);
	ULI_PROBE("Plgr_restore_pg", Plgr_restore_pg_lockinfo);
	ULI_PROBE("Plgr_restore_rec", Plgr_restore_rec_lockinfo);
	ULI_PROBE("Plgr_valid_pg", Plgr_valid_pg_lockinfo);
	ULI_PROBE("Plgr_refpg", Plgr_refpg_lockinfo);
	ULI_PROBE("Plgr_unpinpg", Plgr_unpinpg_lockinfo);
	ULI_PROBE("Plgr_init", Plgr_init_lockinfo);
	ULI_PROBE("Padd_lsn_list", Padd_lsn_list_lockinfo);
	ULI_PROBE("Plgr_writev_ftx", Plgr_writev_ftx_lockinfo);
	ULI_PROBE("Pget_clean_pg", Pget_clean_pg_lockinfo);
	ULI_PROBE("Plgr_retest_firstrec", Plgr_retest_firstrec_lockinfo);
	ULI_PROBE("Prelease_dirty_pg", Prelease_dirty_pg_lockinfo);
	ULI_PROBE("Plgr_write", Plgr_write_lockinfo);
	ULI_PROBE("Plgr_read_open", Plgr_read_open_lockinfo);
	ULI_PROBE("Plgr_dmn_read_open", Plgr_dmn_read_open_lockinfo);
	ULI_PROBE("Plgr_read_close", Plgr_read_close_lockinfo);
	ULI_PROBE("Plgr_read", Plgr_read_lockinfo);
	ULI_PROBE("Pget_pg_lsn", Pget_pg_lsn_lockinfo);
	ULI_PROBE("Pfind_log_end_pg", Pfind_log_end_pg_lockinfo);
	ULI_PROBE("Psetup_log_desc", Psetup_log_desc_lockinfo);
	ULI_PROBE("Plog_init", Plog_init_lockinfo);
	ULI_PROBE("Plgr_open", Plgr_open_lockinfo);
	ULI_PROBE("Plgr_close", Plgr_close_lockinfo);
	ULI_PROBE("Plgr_flush", Plgr_flush_lockinfo);
	ULI_PROBE("Plgr_flush_start", Plgr_flush_start_lockinfo);
	ULI_PROBE("Plgr_flush_sync", Plgr_flush_sync_lockinfo);
	ULI_PROBE("Plog_flush", Plog_flush_lockinfo);
	ULI_PROBE("Plog_flush_sync", Plog_flush_sync_lockinfo);
	ULI_PROBE("Plgr_get_last_rec", Plgr_get_last_rec_lockinfo);
	ULI_PROBE("Plgr_dmn_get_last_rec", Plgr_dmn_get_last_rec_lockinfo);
	ULI_PROBE("Plgr_get_first_rec", Plgr_get_first_rec_lockinfo);
	ULI_PROBE("Plgr_dmn_get_first_rec", Plgr_dmn_get_first_rec_lockinfo);
	ULI_PROBE("Plgr_dmn_get_pseudo_first_rec", Plgr_dmn_get_pseudo_first_rec_lockinfo);
	ULI_PROBE("Plgr_checkpoint_log", Plgr_checkpoint_log_lockinfo);
	ULI_PROBE("Plgr_switch_vol", Plgr_switch_vol_lockinfo);
	ULI_PROBE("Plgr_calc_num_pgs", Plgr_calc_num_pgs_lockinfo);
    
	/* kernel/msfs/bs/bs_sbm.c */
	ULI_PROBE("Pbitmap_undo_opx", Pbitmap_undo_opx_lockinfo);
        ULI_PROBE("Pinit_bs_bitmap_opx", Pinit_bs_bitmap_opx_lockinfo);
	ULI_PROBE("Psbm_set_pg_bits", Psbm_set_pg_bits_lockinfo);
        ULI_PROBE("Palloc_bits", Palloc_bits_lockinfo);
	ULI_PROBE("Palloc_bits_page", Palloc_bits_page_lockinfo);
        ULI_PROBE("Pdealloc_bits_no_sub_ftx", Pdealloc_bits_no_sub_ftx_lockinfo);
	ULI_PROBE("Pdealloc_bits_page", Pdealloc_bits_page_lockinfo);
        ULI_PROBE("Psbm_find_space", Psbm_find_space_lockinfo);
	ULI_PROBE("Psbm_remove_space", Psbm_remove_space_lockinfo);
	ULI_PROBE("Psbm_return_space_no_sub_ftx", Psbm_return_space_no_sub_ftx_lockinfo);
	ULI_PROBE("Premove_desc", Premove_desc_lockinfo);
	ULI_PROBE("Padd_cache", Padd_cache_lockinfo);
	ULI_PROBE("Premove_cache", Premove_cache_lockinfo);
	ULI_PROBE("Pload_x_cache", Pload_x_cache_lockinfo);
	ULI_PROBE("Psbm_init", Psbm_init_lockinfo);
	ULI_PROBE("Psbm_clear_cache", Psbm_clear_cache_lockinfo);
	ULI_PROBE("Psbm_total_free_space", Psbm_total_free_space_lockinfo);
	ULI_PROBE("Psbm_dump", Psbm_dump_lockinfo);

	/* kernel/msfs/bs/bs_stg.c */
	
	ULI_PROBE("Padd_stg_undo", Padd_stg_undo_lockinfo);
	ULI_PROBE("Pinit_bs_stg_opx", Pinit_bs_stg_opx_lockinfo);
	ULI_PROBE("Prbf_add_overlapping_stg", Prbf_add_overlapping_stg_lockinfo);
	ULI_PROBE("Prbf_add_overlapping_clone_stg", Prbf_add_overlapping_clone_stg_lockinfo);
	ULI_PROBE("Prbf_add_stg", Prbf_add_stg_lockinfo);
	ULI_PROBE("Pstg_add_stg", Pstg_add_stg_lockinfo);
	ULI_PROBE("Pstg_add_stg_no_cow", Pstg_add_stg_no_cow_lockinfo);
	ULI_PROBE("Pstg_set_alloc_disk", Pstg_set_alloc_disk_lockinfo);
	ULI_PROBE("Padd_stg", Padd_stg_lockinfo);
	ULI_PROBE("Padd_rsvd_stg", Padd_rsvd_stg_lockinfo);
	ULI_PROBE("Palloc_stg", Palloc_stg_lockinfo);
	ULI_PROBE("Palloc_append_stg", Palloc_append_stg_lockinfo);
	ULI_PROBE("Pget_first_mcell", Pget_first_mcell_lockinfo);
	ULI_PROBE("Palloc_hole_stg", Palloc_hole_stg_lockinfo);
	ULI_PROBE("Pstg_alloc_from_svc_class", Pstg_alloc_from_svc_class_lockinfo);
	ULI_PROBE("Pcp_stg_alloc_from_svc_class", Pcp_stg_alloc_from_svc_class_lockinfo);
	ULI_PROBE("Pextend_skip", Pextend_skip_lockinfo);
	ULI_PROBE("Pstg_alloc_from_one_disk", Pstg_alloc_from_one_disk_lockinfo);
	ULI_PROBE("Pcp_stg_alloc_from_one_disk", Pcp_stg_alloc_from_one_disk_lockinfo);
	ULI_PROBE("Palloc_from_one_disk", Palloc_from_one_disk_lockinfo);
	ULI_PROBE("Pcp_stg_alloc_in_one_mcell", Pcp_stg_alloc_in_one_mcell_lockinfo);
	ULI_PROBE("Pstg_alloc_one_xtnt", Pstg_alloc_one_xtnt_lockinfo);
	ULI_PROBE("Pxfer_stg", Pxfer_stg_lockinfo);
	ULI_PROBE("Pxfer_stg_to_bf", Pxfer_stg_to_bf_lockinfo);
	ULI_PROBE("Pxfer_stg_to_xtnts", Pxfer_stg_to_xtnts_lockinfo);
	ULI_PROBE("Pxfer_append_stg", Pxfer_append_stg_lockinfo);
	ULI_PROBE("Pxfer_hole_stg", Pxfer_hole_stg_lockinfo);
	ULI_PROBE("Pxfer_stg_on_one_disk", Pxfer_stg_on_one_disk_lockinfo);
	ULI_PROBE("Pxfer_stg_in_one_subxtnt", Pxfer_stg_in_one_subxtnt_lockinfo);
	ULI_PROBE("Pstg_alloc_new_mcell", Pstg_alloc_new_mcell_lockinfo);
	ULI_PROBE("Px_page_to_iolist", Px_page_to_iolist_lockinfo);
	ULI_PROBE("Px_page_to_blkmap", Px_page_to_blkmap_lockinfo);
	ULI_PROBE("Px_copypage_to_blkmap", Px_copypage_to_blkmap_lockinfo);
	ULI_PROBE("Pscan_xtnt_map_list", Pscan_xtnt_map_list_lockinfo);
	ULI_PROBE("Px_page_to_blk", Px_page_to_blk_lockinfo);
	ULI_PROBE("Px_page_mapped", Px_page_mapped_lockinfo);
	ULI_PROBE("Ppage_is_mapped", Ppage_is_mapped_lockinfo);
	ULI_PROBE("Pstg_remove_stg_start", Pstg_remove_stg_start_lockinfo);
	ULI_PROBE("Pstg_remove_stg_finish", Pstg_remove_stg_finish_lockinfo);
	ULI_PROBE("Premove_stg", Premove_stg_lockinfo);
	ULI_PROBE("Pdealloc_stg", Pdealloc_stg_lockinfo);
	ULI_PROBE("Pclip_del_xtnt_map", Pclip_del_xtnt_map_lockinfo);
	ULI_PROBE("Pmerge_xtnt_maps", Pmerge_xtnt_maps_lockinfo);
	ULI_PROBE("Pmerge_sub_xtnt_maps", Pmerge_sub_xtnt_maps_lockinfo);
	ULI_PROBE("Punload_sub_xtnt_maps", Punload_sub_xtnt_maps_lockinfo);

	/* kernel/msfs/osf/msfs_io.c */
	ULI_PROBE("Pdomain_panic", Pdomain_panic_lockinfo);
	ULI_PROBE("Pbs_osf_complete", Pbs_osf_complete_lockinfo);
	ULI_PROBE("Pmsfs_iodone", Pmsfs_iodone_lockinfo);
	ULI_PROBE("Pmsfs_async_iodone_lwc", Pmsfs_async_iodone_lwc_lockinfo);
	ULI_PROBE("Pcheck_consol_list", Pcheck_consol_list_lockinfo);
	ULI_PROBE("Plist_map", Plist_map_lockinfo);
	ULI_PROBE("Pconsecutive_list_io", Pconsecutive_list_io_lockinfo);
	ULI_PROBE("Pcall_disk", Pcall_disk_lockinfo);
	ULI_PROBE("Pbs_startio", Pbs_startio_lockinfo);
	ULI_PROBE("Pread_raw_page", Pread_raw_page_lockinfo);
	ULI_PROBE("Pwrite_raw_page", Pwrite_raw_page_lockinfo);

	/* kernel/msfs/osf/msfs_lookup.c */
	ULI_PROBE("Pstrtoul", Pstrtoul_lockinfo);
	ULI_PROBE("Pmsfs_lookup", Pmsfs_lookup_lockinfo);
	ULI_PROBE("Pcheck_path_back", Pcheck_path_back_lockinfo);
	ULI_PROBE("Pnew_parent", Pnew_parent_lockinfo);

	/* kernel/msfs/osf/msfs_syscalls.c */
	ULI_PROBE("Pmsfs_syscall", Pmsfs_syscall_lockinfo);

#endif /* MSFS */

	/********************************************/
	/* start of lockinfo specs for simple locks */
	/********************************************/

#if DLM > 0
        ULI("dlm_pdb_lock",         dlm_pdb_lockinfo,         SPLNONE,DEFAULT);
        ULI("dlm_lkid_lock",        dlm_lkid_lockinfo,        SPLNONE,DEFAULT);
        ULI("dlm_lkb_lock",         dlm_lkb_lockinfo,         SPLNONE,DEFAULT);
        ULI("dlm_rsb_lock",         dlm_rsb_lockinfo,         SPLNONE,DEFAULT);
        ULI("dlm_rsb_incarn_lock",  dlm_rsb_incarn_lockinfo,  SPLNONE,DEFAULT);
        ULI("dlm_rhash_chain_lock", dlm_rhash_chain_lockinfo, SPLNONE,DEFAULT);
        ULI("dlm_rsbinfo_respq_lock",dlm_rsbinfo_respq_lockinfo,SPLNONE,DEFAULT);
        ULI("dlm_msg_respq_lock",   dlm_msg_respq_lockinfo,   SPLNONE,DEFAULT);
        ULI("dlm_deadlockq_lock",   dlm_deadlockq_lockinfo,   SPLNONE,DEFAULT);
        ULI("dlm_timeoutq_lock",    dlm_timeoutq_lockinfo,    SPLNONE,DEFAULT);
#endif /* DLM */
#if DLMSL > 0
	ULI("malloc_smp_lock", malloc_smp_lockinfo,    SPLNONE, DEFAULT);
#endif /* DLMSL */
#if DRD > 0
	ULI("drd_maphd_lock",  drd_maphd_lockinfo,     SPLNONE, DEFAULT);
        ULI("drd_map_lock",  drd_map_lockinfo,     SPLNONE, DEFAULT);
	ULI("drd_bsc_chtabhead_lock", bsc_chtabhead_lockinfo, SPLNONE, DEFAULT);
	ULI("drd_bssdupreq_lock", bssdupreq_lock_info, SPLNONE, DEFAULT);
	ULI("drd_bss_sv_active_lock", bss_sv_active_lockinfo, SPLNONE, DEFAULT);
	ULI("drd_bp_lock", drd_bp_lockinfo, SPLNONE, DEFAULT);
	ULI("bsc_rm_serial_lock", bsc_rm_serial_lockinfo, SPLNONE, DEFAULT);
	ULI("bsc_biod_lock", bsc_biod_lock_info, SPLNONE, DEFAULT);
#endif

	SLI("hostname_lock", hostname_lockinfo, SPLNONE, DEFAULT);
	SLI("arptab_lock", arptab_li, SPLNONE, DEFAULT);
	NLI("ifnet_spin_lock", ifnet_spin_li, SPLNONE, DEFAULT);
	NLI("inifaddr_spin_lock", inifaddr_spin_li, SPLNONE, DEFAULT);
	NLI("ifqueue.ifq_slock_splnone", ifqueue_splnone_li, SPLNONE, DEFAULT);
	NLI("domain.dom_rc_lock", dom_rc_li, SPLNONE, DEFAULT);
	NLI("global_unpconn_lock", global_unpconn_li, SPLNONE, DEFAULT);

	ULI("rpc_cl_xid_lock", rpc_cl_xid_lock_info, SPLNONE, DEFAULT);
	ULI("lk_rpcrqcred", lk_rpcrqcred_info, SPLNONE, DEFAULT);
	ULI("lk_rpccallout", lk_rpccallout_info, SPLNONE, DEFAULT);
	ULI("lk_rpcdupreq", lk_rpcdupreq_info, SPLNONE, DEFAULT);

	ULI("nfs_activewrites_lock",nfs_activewrites_lockinfo,SPLNONE,DEFAULT);
	ULI("nfs3_activewrites_lock",nfs3_activewrites_lockinfo,SPLNONE,DEFAULT);
	ULI("nfs_writefree_lock", nfs_writefree_lockinfo, SPLNONE, DEFAULT);
	ULI("nfs3_writefree_lock", nfs3_writefree_lockinfo, SPLNONE, DEFAULT);
	ULI("nfs_sys_lock", nfs_sys_lockinfo, SPLNONE, DEFAULT);
	ULI("tslist_lock", nfs_tslist_lockinfo, SPLNONE, DEFAULT);
	ULI("chlist_lock", chlist_lockinfo, SPLNONE, DEFAULT);
	ULI("asyncdaemon_lock", asyncdaemon_lockinfo, SPLNONE, DEFAULT);
	ULI("unixauthtab_lock", unixauthtab_lockinfo, SPLNONE, DEFAULT);
	ULI("nfs_minor_lock", nfs_minor_lockinfo, SPLNONE, DEFAULT);
	ULI("nfs_newnum_lock", nfs_newnum_lockinfo, SPLNONE, DEFAULT);
	ULI("rnode.r_statelock", rnode_state_lockinfo, SPLNONE, DEFAULT);
	ULI("mntinfo.mi_lock", mntinfo_lockinfo, SPLNONE, DEFAULT);
	ULI("presto_lock", presto_lockinfo, SPLNONE, DEFAULT);

	SLI("shm_stats_lock", shm_stats_lockinfo, SPLNONE, DEFAULT);
	SLI("shmid_lock", shmid_lockinfo, SPLNONE, DEFAULT);
	SLI("msgid_lock", msgid_lockinfo, SPLNONE, DEFAULT);
	SLI("semid_lock", semid_lockinfo, SPLNONE, DEFAULT);
	SLI("undo_lock", undo_lockinfo, SPLNONE, DEFAULT);
	SLI("cur_msghdrs", cur_msghdrs_lockinfo, SPLNONE, DEFAULT);
	SLI("all_zones_lock", all_zones_lockinfo, SPLNONE, DEFAULT);
	SLI("stack_queue_lock", stack_queue_lockinfo, SPLNONE, DEFAULT);
	SLI("all_psets_lock", all_psets_lockinfo, SPLNONE, DEFAULT);

	ULI("pgrp.pg_sig_lock", pgrp_sig_lockinfo, SPLNONE, DEFAULT);
	ULI("accounting_lock", accounting_lockinfo, SPLNONE, DEFAULT);
	ULI("aiosb_lock", aiosb_lockinfo, SPLNONE, DEFAULT);
	ULI("gidhash_lock", gidhash_lockinfo, SPLNONE, DEFAULT);
	ULI("uidhash_lock", uidhash_lockinfo, SPLNONE, DEFAULT);
	ULI("ruidhash_lock", ruidhash_lockinfo, SPLNONE, DEFAULT);
	ULI("pid_lock", pid_lockinfo, SPLNONE, DEFAULT);
	ULI("proc.p_lock", proc_lockinfo, SPLNONE, ORDERED);
	ULI("aio_lock", aio_lockinfo, SPLNONE, DEFAULT);
	ULI("session.s_lock", sess_lockinfo, SPLNONE, DEFAULT);

	SLI("task_swap_queues_lock",task_swap_queues_lockinfo,SPLNONE,DEFAULT);
	SLI("task.lock", task_lockinfo, SPLNONE, ORDERED);
	SLI("processor_set.lock", pset_lockinfo, SPLNONE, ORDERED);
	SLI("task.ipc_translation_lock", ipc_task_lockinfo, SPLNONE, DEFAULT);
	SLI("thread.ipc_state_lock", ipc_thread_lockinfo, SPLNONE, DEFAULT);
	SLI("kern_port.port_data_lock", kern_port_lockinfo, SPLNONE, DEFAULT);
	SLI("kern_set.set_data_lock", kern_set_lockinfo, SPLNONE, ORDERED);
	SLI("msg_queue.lock", msg_queue_lockinfo, SPLNONE, ORDERED);
	SLI("port_hash_bucket.lock", port_hash_lockinfo, SPLNONE, DEFAULT);
	SLI("reply_port_cache_lock", reply_pcache_lockinfo, SPLNONE, DEFAULT);
	SLI("task_ref_count_lock", task_ref_count_lockinfo, SPLNONE, DEFAULT);

	ULI("kiorequest.req_lk", kio_reqs_lk_info, SPLNONE, DEFAULT);
	ULI("kio_sys_lk", kio_sys_lockinfo, SPLNONE, DEFAULT);
	ULI("kiohandle.kio_handle_lk", kio_handles_lk_info, SPLNONE, DEFAULT);
#if MSFS > 0
	/********************************************************
	 * AdvFS simple locks in the hierarchy
	 ********************************************************/
	ULI("DmnTblMutex", ADVDmnTblMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("BfSetTblMutex", ADVBfSetTblMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("BfAccessTblMutex", ADVBfAccessTblMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("DomainMutex", ADVdomainT_mutex_lockinfo, SPLNONE, DEFAULT );
	ULI("LookupMutex", ADVLookupMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("IoQueueMutex", ADVIoQueueMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("LogDescTbl", ADVLogDescTbl_lockinfo, SPLNONE, DEFAULT );
	ULI("LockMgrMutex.mutex",  msfs_lockmgrmutex_lockinfo, SPLNONE, DEFAULT );
	ULI("mutexT.mutex",  msfs_mp_mutex_lockinfo, SPLNONE, DEFAULT );
	ULI("filesetMutex", ADVfilesetMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("dquotMutex", ADVdquotMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("fsContext_mutex", ADVfsContext_mutex_lockinfo, SPLNONE, DEFAULT );
	ULI("dirMutex", ADVbfSetT_dirMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("bfSetT.dirMutex", ADVbfSetT_dirMutex_lockinfo, SPLNONE, DEFAULT );
        ULI("bfSetT.cloneDelStateMutex", ADVbfSetT_cloneDelStateMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("FtxMutex", ADVFtxMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("BfAccessTraceMutex", ADVBfAccessTraceMutex_lockinfo, SPLNONE, DEFAULT );
	ULI("msgQT.mutex", ADVmsgQT_mutex_lockinfo, SPLNONE, DEFAULT );
	ULI("dqhead_dqh_mutex", ADVdqhead_dqh_mutex_lockinfo, SPLNONE, DEFAULT );
	ULI("Ms_malloc_mutex", ADVMs_malloc_mutex_lockinfo, SPLNONE, DEFAULT );
#endif
	ULI("ufile_state.uf_ofile_lock", ufd_lockinfo, SPLNONE, DEFAULT);
	ULI("utask_nd.utnd_lock", utnd_lockinfo, SPLNONE, DEFAULT);
	ULI("ihash_lock", ihash_lockinfo, SPLNONE, DEFAULT);
	ULI("inode.i_incore_lock", i_incore_lockinfo, SPLNONE, ORDERED);
	ULI("utask.uu_handy_lock", u_handy_lockinfo, SPLNONE, DEFAULT);
	ULI("real_ucred.lock", ucred_lockinfo, SPLNONE, DEFAULT);
	ULI("file.f_incore_lock", file_lockinfo, SPLNONE, DEFAULT);
	ULI("vnode.v_lock", vnode_lockinfo, SPLNONE, DEFAULT);
	ULI("namei.nch_lockinfo", nch_lockinfo, SPLNONE, DEFAULT);
	ULI("vn_free_lock", vn_free_lockinfo, SPLNONE, DEFAULT);
	ULI("nc_freelist_lockinfo", nc_freelist_lockinfo, SPLNONE, DEFAULT);
	ULI("nc_purge_lockinfo", nc_purge_lockinfo, SPLNONE, DEFAULT);

	NLI("unp_misc_lock", unp_misc_li, SPLNONE, DEFAULT);
	NLI("tcb.inp_rc_lock", inp_tcp_rc_li, SPLNONE, DEFAULT);
	NLI("udb.inp_rc_lock", inp_udp_rc_li, SPLNONE, DEFAULT);
	NLI("mfclencap_lock", mfclencap_li, SPLNONE, DEFAULT);
#if LOCK_NETSTATS
	NLI("rtstat.rts_lock", rtstat_li, SPLNONE, DEFAULT);
	NLI("icmpstat.icps_lock", icmpstat_li, SPLNONE, DEFAULT);
	NLI("igmpstat.igps_lock", igmpstat_li, SPLNONE, DEFAULT);
	NLI("mrtstat.mrts_lock", mrtstat_li, SPLNONE, DEFAULT);
	NLI("ipstat.ips_lock", ipstat_li, SPLNONE, DEFAULT);
#endif
	NLI("misc_tcp_lock", misc_tcp_li, SPLNONE, DEFAULT);
#if LOCK_NETSTATS
	NLI("tcpstat.tcps_lock", tcpstat_li, SPLNONE, DEFAULT);
	NLI("udpstat.udps_lock", udpstat_li, SPLNONE, DEFAULT);
#endif
#if NPTY > 0
	ULI("pty_lock", pty_lockinfo, SPLNONE, DEFAULT);
#endif
#if RPTY > 0
	SLI("pty_lock", pty_lockinfo, SPLNONE, DEFAULT);
#endif
#if DEC_AUDIT > 0
	ULI("audlog.lock", audlog_lockinfo, SPLNONE, DEFAULT);
	ULI("audselq.lock", audselq_lockinfo, SPLNONE, DEFAULT);
	ULI("audbuf.lock", audbuf_lockinfo, SPLNONE, DEFAULT);
	ULI("audmask.lock", audmask_lockinfo, SPLNONE, DEFAULT);
#endif

	SLI("consvp_lock", consvp_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_map.ref_lock", vm_map_ref_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_map_entry.vme_faultlock", vme_fault_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_vp_object.vu_seglock", vop_seglockinfo, SPLNONE, DEFAULT);
	SLI("vm_object.ob_lock", vm_object_lockinfo, SPLNONE, ORDERED);
	SLI("vm_map.hint_lock", vm_map_hint_lockinfo, SPLNONE, DEFAULT);
	SLI("gr_mapping_lock", mapping_lock_lockinfo, SPLNONE, DEFAULT);
	SLI("gh_stats_lock", mapping_lock_lockinfo, SPLNONE, DEFAULT);
	SLI("gr_pagezeroer_lock", gr_pagezeroer_lockinfo, SPLNONE, DEFAULT);
	SLI("gr_collect_lock", gr_collect_lockinfo, SPLNONE, DEFAULT);
	SLI("granhint_lock", granhint_lockinfo, SPLNONE, DEFAULT);
#if RMVM > 0
	SLI("vm_rm_object.links_lock", vm_rm_object_links_lockinfo, SPLNONE, ORDERED);
	SLI("rm_object_map_recv_lock",rm_object_map_recv_lockinfo, SPLNONE, DEFAULT); 
	SLI("rm_object_map_trans_base_lock",rm_object_map_trans_base_lockinfo, SPLNONE, DEFAULT);
 	SLI("rm_object_map_dual_base_lock",rm_object_map_dual_base_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_rm_object.ob_lock", vm_rm_object_lockinfo, SPLNONE, DEFAULT);
#endif
	SLI("shared_segment.ss_lock", shared_segment_lockinfo, SPLNONE,DEFAULT);
	SLI("a_lock", a_lock_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_swap_circular_lock", vm_swap_circular_lockinfo,SPLNONE,DEFAULT);
	SLI("vm_swap.vs_lock", vm_swap_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_swap_io_lock", vm_swap_io_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_swap_space_lock", vm_swap_space_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_page_queue_lock", vm_page_queue_lockinfo, SPLNONE, DEFAULT);
	SLI("vm_page_lock_data", vm_page_lockinfo, SPLNONE, DEFAULT);
	SLI("ppg_umc.umc_lock", ppg_umc_lockinfo, SPLNONE, DEFAULT);
	SLI("umc_lru_lock", umc_lru_lockinfo, SPLNONE, DEFAULT);
	SLI("ubc_lru_lock", ubc_lru_lockinfo, SPLNONE, DEFAULT);
	SLI("ubc_pages_lock", ubc_pages_lockinfo, SPLNONE, DEFAULT);
	SLI("ubc_dirty_lock", ubc_dirty_lockinfo, SPLNONE, DEFAULT);
	SLI("ubc_iocount_lock", ubc_iocount_lockinfo, SPLNONE, DEFAULT);
	SLI("u_seg_cache_lock", u_seg_cache_lockinfo, SPLNONE, DEFAULT);
	SLI("ptepages_lock", ptepages_lockinfo, SPLNONE, DEFAULT);
	SLI("anon_klock.akl_slock", akl_slock_lockinfo, SPLNONE, DEFAULT);
	SLI("pmap_memdsc_lock", pmap_memdsc_lockinfo, SPLNONE, DEFAULT);
	SLI("binlog_selq_lock", binlog_selq_lockinfo, SPLNONE, DEFAULT);

#if STREAMS != 0 || TIMOD || SVVS || STRKINFO || STRIFNET || XTISO || DLB || DLPI || LDTTY || RPTTY || PCKT || LAT 
	SLI("modsw_lock", modsw_lockinfo, SPLNONE, DEFAULT);
	SLI("sth_pipestat.lock", stb_lockinfo, SPLNONE, DEFAULT);
	SLI("sad_lock", sad_lockinfo, SPLNONE, DEFAULT);
	SLI("muxid_lock", streams_muxid_lockinfo, SPLNONE, DEFAULT);
	SLI("iocblk_id_lock", iocblk_id_lockinfo, SPLNONE, DEFAULT);
	SLI("weldq_lock", weldq_lockinfo, SPLNONE, DEFAULT);
	SLI("bufc_lock",streams_bufc_lockinfo, SPLNONE, DEFAULT);
	SLI("active_qlock_lock", active_qlock_lockinfo, SPLNONE, DEFAULT);
	SLI("streams_open_lock", streams_open_lockinfo, SPLNONE, DEFAULT);
	SLI("sth_s.sth_ext_flags_lock", sth_ext_flags_lockinfo, SPLNONE, DEFAULT);
#endif	/* STREAMS || TIMOD || SVVS || STRKINFO || STRIFNET || XTISO || DLB || DLPI || LDTTY || RPTTY || PCKT || LAT */

#if PPP
	SLI("ppp_if_table_lock", ppp_if_table_lock_info, SPLNONE, DEFAULT);
	SLI("ppp_if_info.ppp_if_element_lock", ppp_if_element_lock_info, SPLNONE, DEFAULT);
	SLI("ppp_comp_table_lock", ppp_comp_table_lock_info, SPLNONE, DEFAULT);
	SLI("ppp_comp_info.ppp_comp_element_lock", ppp_comp_element_lock_info, SPLNONE, DEFAULT);
	SLI("ppp_async_table_lock", ppp_async_table_lock_info, SPLNONE, DEFAULT);
	SLI("ppp_async_info.ppp_async_element_lock", ppp_async_element_lock_info, SPLNONE, DEFAULT);
#endif	/* PPP */

#if XTISO
	SLI("xtiso_lock", xtiso_lockinfo, SPLNONE, DEFAULT);
	SLI("xtisoc_lock", xtisoc_lockinfo, SPLNONE, DEFAULT);
#endif	/* XTISO */

#if LDTTY
	SLI("ldtty.t_intimeout_lock", tp_intimeout_lockinfo, SPLNONE, DEFAULT);
#endif

#if 0
#if RT_SEM
	SLI("real_time.p4bsem_lock", p4bsem_lockinfo, SPLNONE, DEFAULT);
#endif
#endif
#if	(DLB > 0)
	NLI("dlbq_list_head_slock", dlbq_list_sli, SPLNONE, DEFAULT);
#endif
#if RT_CSEM || RT_IPC
	SLI("real_time.p4csem_lock", p4csem_lockinfo, SPLNONE, DEFAULT);
#endif
#if MCNET > 0
        LI("mcnet_psend_lock", mcnet_psend_lockinfo, SPLNONE, DEFAULT);
#endif
#if RM > 0
	LI("rm_mgmt_locks", rm_mgmt_lockinfo, SPLNONE, DEFAULT);
	LI("rm_mgmt_tag_lock", rm_mgmt_tag_lockinfo, SPLNONE, DEFAULT);
	LI("rm_mgmt_bitmap_lock", rm_mgmt_bitmap_lockinfo, SPLNONE, DEFAULT);
	LI("rm_map_data_lock", rm_map_data_lockinfo, SPLNONE, DEFAULT);
	LI("rm_callback_lock", rm_callback_lockinfo, SPLNONE, DEFAULT);
#endif
	ULI("cxalloc_lock ", cxalloc_lockinfo, SPLSOFTC, DEFAULT);
	ULI("rci_registry_lock", rci_registry_lockinfo, SPLSOFTC, DEFAULT);
	ULI("rci_event_lock", rci_event_lockinfo, SPLSOFTC, DEFAULT);
	ULI("error_event_lock", event_cntrl_li, SPLSOFTC, DEFAULT);

#if DLPI
	NLI("dltimer_lock", dltimer_lockinfo, SPLSOFTC, DEFAULT);
#endif

#ifdef	ASE
	ULI("amlog",            amlog_lock_li,          SPLSOFTC, DEFAULT);
	ULI("amcntrl",          am_cntrl_lock_li,       SPLSOFTC, DEFAULT);
	ULI("amcntrl.hflink",   am_host_lk_li,          SPLSOFTC, DEFAULT);
	ULI("amcntrl.dflink",   am_device_lk_li,        SPLSOFTC, DEFAULT);
	ULI("ase_table",        ase_table_lock_li,      SPLSOFTC, DEFAULT);
#endif

#ifdef	DTM
	ULI("dtm_stack_lock",	dtm_stack_lockinfo,  SPLSOFTC, DEFAULT);
	ULI("dtm_control",	dtm_control_lockinfo, SPLNONE, DEFAULT);
#endif

#if ATM
        ULI("atm_cmm_mmi_list",atm_cmm_mmi_list_info, SPLIMP,DEFAULT);
#if ATMIP
        ULI("atm_arp_delevt_lock", atm_arp_delevt_lock_li, SPLSOFTC, DEFAULT);
#endif
#endif

	SLI("log_lock", log_lockinfo, SPL1, DEFAULT);
	NLI("ifqueue.ifq_slock_splnet", ifqueue_splnet_li, SPLNET, DEFAULT);

#if RM > 0
        /*
         * MC interrupts (like all PCI interrupts on Alpha) can come in at 
         * SPLDEVLOW or SPLDEVHIGH.  We use SPLDEVLOW in this declaration 
         * to cover the case when they come in at SPLDEVLOW.
         */
	SLI("rm_error_lock", rm_error_lockinfo, SPLDEVLOW, DEFAULT);
	SLI("rm_init_state_lock", rm_init_state_lockinfo, SPLDEVLOW, DEFAULT);
	SLI("rm_thread_lock", rm_thread_lockinfo, SPLDEVLOW, DEFAULT);
	SLI("rm_error_shutting_down_state_lock", rm_error_shutting_down_state_lockinfo, SPLDEVLOW, DEFAULT);
	SLI("rm_object_map_trans_intr_lock",rm_object_map_trans_intr_lockinfo, SPLDEVLOW, DEFAULT);
 	SLI("rm_object_map_dual_intr_lock",rm_object_map_dual_intr_lockinfo, SPLDEVLOW, DEFAULT);
	SLI("vm_rm_object_mappers_lock", vm_rm_object_mappers_lockinfo, SPLDEVLOW, DEFAULT);
	SLI("vm_rm_base_address_lock", vm_rm_base_address_lockinfo, SPLDEVLOW, DEFAULT);
#endif
#if MCNET > 0
        LI("mcnet_reflock", mcnet_reflockinfo, SPLDEVLOW, DEFAULT);
#endif
#if CCOMSUB > 0
        SLI("CComGlbSlock", CComGlbSlockInfo, SPLDEVLOW, DEFAULT);
        SLI("CComQueSlock", CComQueSlockInfo, SPLDEVLOW, DEFAULT);
#endif
#if DRD > 0
	LI("bsc_rm_segment.bs_seg_lock", bsc_seg_lockinfo, SPLDEVLOW, DEFAULT);
	ULI("bsc_rm_lock", bsc_rm_lock_info, SPLDEVLOW, DEFAULT);
	ULI("bss_rm_pend_lock", bss_rm_pend_lock_info, SPLDEVLOW, DEFAULT);
	ULI("drd_retry_que_lock",  drd_retry_que_lockinfo,     SPLSOFTC, DEFAULT);
#endif
#if RM > 0
	SLI("rm_event_buff_lock", rm_event_buff_lockinfo, SPLDEVLOW, DEFAULT);
#endif
#if DLMSL > 0
	ULI("slrecv_smp_lock", slrecv_smp_lockinfo,  SPLMEMCHN, DEFAULT);
#endif /* DLMSL */

#if NSCSI > 0
	ULI("cam_pd_unit_table",cam_pd_unit_table_li,   SPLBIO, DEFAULT);
	ULI("cam_pd_device",    cam_pd_device_li,       SPLBIO, DEFAULT);
	ULI("cam_resp_que",     cam_resp_que_li,        SPLBIO, DEFAULT);
	ULI("cam_pd_device3",   cam_pd_device3_li,      SPLBIO, DEFAULT);
	ULI("cam_disk",    	cam_dsk_lock_li,        SPLBIO, DEFAULT);
	ULI("cam_disk_recq",   	cam_recq_lock_li,       SPLBIO, DEFAULT);
	ULI("cam_c_ctrl",       cam_c_ctrl_li,          SPLBIO, DEFAULT);
	ULI("cam_c_qhead",      cam_c_qhead_li,         SPLBIO, DEFAULT);
	ULI("cam_c_edt",        cam_c_edt_li,           SPLBIO, DEFAULT);
	ULI("cam_ccmn_bp_pool", cam_ccmn_bp_pool_li,    SPLBIO, DEFAULT);
	ULI("cam_ccmn_data_pool",cam_ccmn_data_pool_li, SPLBIO, DEFAULT);
	ULI("cam_d3_ctrl",      cam_d3_ctrl_li,         SPLBIO, DEFAULT);
	ULI("cam_x_qhead",      cam_x_qhead_li,         SPLBIO, DEFAULT);
	ULI("cam_x_ctrl",       cam_x_ctrl_li,          SPLBIO, DEFAULT);
	ULI("cam_softc",        cam_softc_li,           SPLBIO, DEFAULT);
	ULI("cam_reg",          cam_reg_li,             SPLBIO, DEFAULT);
	ULI("cam_cplt",         cam_cplt_li,            SPLBIO, DEFAULT);
	ULI("cam_sm",           cam_sm_li,              SPLBIO, DEFAULT);
#endif
#if NASC > 0 || NTCDS > 0 || NPSIOP > 0 || NSIOP > 0 || NAHA > 0 ||  NXZA > 0 || NISP > 0
	ULI("cam_htm",          cam_htm_nexuslk_li,     SPLBIO, DEFAULT);
#endif

	ULI("ddr_dbase", ddr_dbase_open_lkinfo, SPLNONE, DEFAULT);
	ULI("ddr_scsidevs", ddr_scsidevs_lockinfo, SPLNONE, DEFAULT);
	ULI("dev_desc.lk", cam_ddr_dev_desc_lkinfo, SPLNONE, DEFAULT);

#if NXZA > 0
	ULI("cam_xza_target",   cam_xza_target_li,      SPLBIO, DEFAULT);
#endif
#if NSIOP > 0
	ULI("cam_siop_doneq",   cam_siop_doneq_li,      SPLBIO, DEFAULT);
	ULI("cam_free_job",     cam_free_job_li,        SPLBIO, DEFAULT);
	ULI("cam_free_buf",     cam_free_buf_li,        SPLBIO, DEFAULT);
	ULI("cam_sh",           cam_sh_li,              SPLBIO, DEFAULT);
	ULI("cam_siopq",        cam_siopq_li,           SPLBIO, DEFAULT);
#endif
#if NPSIOP > 0
        ULI("cam_psiop_doneq",   cam_psiop_doneq_li,    SPLBIO, DEFAULT);
        ULI("cam_pfree_job",     cam_pfree_job_li,      SPLBIO, DEFAULT);
        ULI("cam_psh",           cam_psh_li,            SPLBIO, DEFAULT);
        ULI("cam_psiopq",        cam_psiopq_li,         SPLBIO, DEFAULT);
#endif
#if NAHA > 0
	ULI("cam_aha_softc",	 cam_aha_softc_li,	SPLBIO, DEFAULT);
	ULI("cam_aha_freeq",	 cam_aha_freeq_li,	SPLBIO, DEFAULT);
	ULI("cam_aha_activeq",	 cam_aha_activeq_li,	SPLBIO, DEFAULT);
#endif
#if NATA > 0
	ULI("cam_ata_softc",     cam_ata_li,            SPLBIO, DEFAULT);
#endif
#if NTZA > 0 || NPZA > 0
	ULI("cam_spo_generic",	 cam_spo_genericlk_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_resource",	 cam_spo_resourcelk_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_nexus",	 cam_spo_nexuslk_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_iowaitq",	 cam_spo_iowaitq_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_dacq",	 cam_spo_dacqlk_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_dafq",	 cam_spo_dafqlk_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_adrq",	 cam_spo_adrqlk_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_adfq",	 cam_spo_adfqlk_li,	SPLBIO, DEFAULT);
	ULI("cam_spo_debug",	 cam_spo_debugqlk_li,	SPLBIO, DEFAULT);
#endif /* NTZA > 0 || NPZA > 0 */
#if NISP > 0 
	ULI("isp_abort",         cam_isp_abort_li,      SPLBIO, DEFAULT);
	ULI_DISABLE_HIERARCHY_CHECKING(cam_isp_abort_li);
	ULI("cam_isp",		 cam_isp_li,		SPLBIO, DEFAULT);
#endif /* NISP > 0 */

#if NUSB > 0
	ULI("usb_bus.lock", usb_bus_li, SPLBIO, DEFAULT);
	ULI("usb_device.lock", usb_device_li, SPLBIO, DEFAULT);
	ULI("usb_hub.lock", usb_hub_li, SPLBIO, DEFAULT);
	ULI("usb_interface.lock", usb_interface_li, SPLBIO, DEFAULT);
	ULI("usb_pipe.lock", usb_pipe_li, SPLBIO, DEFAULT);
	ULI("usb_request.lock", usb_request_li, SPLBIO, DEFAULT);
	ULI("usb_array.lock", usb_array_li, SPLBIO, DEFAULT);
#endif

#if NXCR > 0
	ULI("astro_re_table",	re_table_li,		SPLBIO, DEFAULT);
	ULI("astro_re_device",	re_device_li,		SPLBIO, DEFAULT);
	ULI("astro_xcr_softc",	xcr_softc_li,		SPLBIO, DEFAULT);
	ULI("astro_xcr_reg",	xcr_reg_li,		SPLBIO, DEFAULT);
	ULI("astro_xcr_cb",	xcr_cb_li,		SPLBIO, DEFAULT);
#endif
#if NSCSI > 0
	ULI("cam_pool_ctrl",    cam_pool_ctrl_li,       SPLNONE, DEFAULT);
	ULI("cam_pool_queue",   cam_pool_queue_li,      SPLNONE, DEFAULT);
#endif

#if NPNVRAM > 0
	ULI("pnvram_softc_lock", pnvram_li,             SPLBIO, DEFAULT);
#endif

#if NENVRAM > 0
	ULI("envram_softc_lock", envram_li,             SPLBIO, DEFAULT);
#endif

#if STREAMS != 0 || TIMOD || SVVS || STRKINFO || STRIFNET || XTISO || DLB || DLPI || LDTTY || RPTTY || PCKT || LAT 
	SLI("osrq_lock", osrq_lockinfo, SPLDEVHIGH,DEFAULT);
	SLI("streams_log_lock", streamsm_log_lockinfo, SPLDEVHIGH,DEFAULT);
	SLI("mblk_lock",streams_mblk_lockinfo, SPLDEVHIGH, DEFAULT);
	SLI("queue(streams).q_lock", streams_q_lockinfo, SPLDEVHIGH, DEFAULT);
	SLI("sqh_s.sqh_lock", sqh_lockinfo, SPLDEVHIGH, DEFAULT);
	SLI("str_to_lock", str_to_lockinfo, SPLDEVHIGH, DEFAULT);
	SLI("sq_flags_lock", sq_flags_lockinfo, SPLDEVHIGH, DEFAULT);
#endif /* STREAMS != 0 || TIMOD || SVVS || STRKINFO || STRIFNET || XTISO || DLB || DLPI || LDTTY || RPTTY || PCKT || LAT */
#if	(DLB > 0)
	NLI("dlb_slock", dlb_sli, SPLIMP, DEFAULT);
	NLI("dlbq_lock", dlbq_sli, SPLIMP, DEFAULT);
#endif
#if MCNET > 0
        NLI("mcnet_sclock", mcnet_sclockinfo, SPLIMP, DEFAULT);
#endif
#if NGWSCREEN > 0
	NLI("gwscreen_lock", gwscreen_li, SPLIMP, DEFAULT);
#endif
#if NTE > 0	/* TEGEC */
	SLI("te_softc.lk_te_softc", te_softc_lockinfo, SPLIMP, DEFAULT);
#endif
#if NTU > 0	/* TULIP */
	SLI("tu_softc.lk_tu_softc", tu_softc_lockinfo, SPLIMP, DEFAULT);
#endif
#if NXNA > 0	/* DEMNA */
	SLI("xna_softc.lk_xna_softc", xna_softc_lockinfo, SPLIMP, DEFAULT);
#endif
#if NMFA > 0	/* DEMFA */
	SLI("mfa_softc.lk_mfa_softc", mfa_softc_lockinfo, SPLIMP, DEFAULT);
#endif
#if NFTA > 0	/* DEFTA, DEFEA, DEFPA */
	SLI("fta_softc.lk_fta_softc", fta_softc_lockinfo, SPLIMP, DEFAULT);
        SLI("fta_softc.lk_fta_xmit", fta_xmit_lockinfo, SPLIMP, DEFAULT);
        SLI("fta_softc.lk_fta_regs", fta_regs_lockinfo, SPLIMP, DEFAULT);
#endif
#if NFAA > 0	/* DEFAA */
	SLI("fxx_softc.lk_interrupt_level",
		faa_interrupt_level_lockinfo, SPLIMP, DEFAULT);
#endif
#if NLTA > 0    /* DGLTA, DGLPB */
        SLI("otto_softc.lk_otto_softc", otto_softc_lockinfo, SPLIMP, DEFAULT);
        SLI("otto_softc.lk_ready_q", otto_rdy_q_lockinfo, SPLIMP, DEFAULT);
#endif
#if PACKETFILTER > 0
	NLI("pfilt_lock", pfilt_lockinfo, SPLIMP, DEFAULT);
#endif
#if	defined(DEC2100_A500) || defined(DEC2100_C500)
	ULI("PCI0_hae0_3_lock",        PCI0_hae0_3_li, SPLDEVHIGH, DEFAULT);
	ULI("PCI1_hae0_3_lock",        PCI1_hae0_3_li, SPLDEVHIGH, DEFAULT);
	ULI("cbus2_pci_int_lock",      cbus2_pci_int_li, SPLDEVHIGH, DEFAULT);
#endif	/* defined(DEC2100_A500) || defined(DEC2100_C500) */
#ifdef	DEC21000
	ULI("pcia_ctl_lock",        pcia_ctl_li, SPLDEVHIGH, DEFAULT);
#endif	/* DEC21000	*/
#if NPCI > 0
	ULI("dma_hw_sg_rmap_lock", sg_rmap_lockinfo, SPLDEVHIGH, DEFAULT);
	ULI("shared_intr_lock", intr_add, SPLDEVHIGH, DEFAULT);
	ULI("shared_intr_act_lock", intr_act, SPLDEVHIGH, DEFAULT);
#endif	/* NPCI	*/
#if PWRMGR_ENABLED
	ULI("pwrmgr_data_lock", pwrmgr_lock_info, SPLDEVHIGH, DEFAULT);
#endif
	NLI("ifqueue.ifq_slock", ifqueue_li, SPLIMP, ORDERED);
	NLI("ifnet.if_slock", ifnet_li, SPLIMP, DEFAULT);
	NLI("mbuf_ext_slock", mbuf_ext_sli, SPLIMP, DEFAULT);
	NLI("mbuf_slock", mbuf_sli, SPLIMP, DEFAULT);
	ULI("cku_private.lk_outbuf", cku_lk_outbuf_info, SPLIMP, DEFAULT);
	ULI("udp_data.lk_udpdata", lk_udpdata_info, SPLIMP, DEFAULT);
	ULI("nfs_rrok_lock", nfs_rrok_lockinfo, SPLIMP, DEFAULT);
	ULI("nfs_xprtfree_lock", nfs_xprtfree_lockinfo, SPLIMP, DEFAULT);
	NLI("netisr_slock", netisr_li, SPLIMP, DEFAULT);
	NLI("aio_socket_lock", aio_socket_lockinfo, SPLIMP, DEFAULT);

        /* ATM LOCKS */
#if ATM
#if ATMIP
        ULI("atmip_driver_q_lock",atmip_driver_q_li,SPLIMP, DEFAULT);
        ULI("atmip_zombie_vc_lock",atmip_vc_zombie_li,SPLIMP, DEFAULT);
        ULI("atmip_zombie_ppa_lock",atmip_ppa_zombie_li,SPLIMP, DEFAULT);
        ULI("atmip_rtupdt_lock",atmip_rtupdt_li,SPLIMP, DEFAULT);
        ULI("atmip_drv_ppaq_lock",atmip_drv_ppaq_li,SPLIMP, DEFAULT);
        ULI("atmip_drv_esiq_lock",atmip_drv_esiq_li,SPLIMP, DEFAULT);
        ULI("atmip_drv_ifq_lock",atmip_drv_ifq_li,SPLIMP, DEFAULT);
        ULI("atmip_esi_ifq_lock",atmip_esi_ifq_li,SPLIMP, DEFAULT);
        ULI("atmip_map_lock",atmip_map_li,SPLIMP, DEFAULT);
        ULI("atmip_map_sec_lock",atmip_map_sec_li,SPLIMP, DEFAULT);
        ULI("atmip_ppa_lock", atmip_ppa_li, SPLIMP, DEFAULT);
        ULI("atm_arp_rcv_q_lock", atm_arp_rcv_q_lock_li, SPLIMP, DEFAULT);
        ULI("atm_arp_table_lock", atm_arp_table_lock_li, SPLIMP, DEFAULT);
        ULI("atm_arp_bucket_lock", atm_arp_bucket_lock_li, SPLIMP, DEFAULT);
        ULI("atm_arp_data_lock", atm_arp_data_lock_li, SPLIMP, DEFAULT);
        ULI("atmip_vc_lock", atmip_vc_li, SPLIMP, DEFAULT);
        ULI("atmip_ifnet_lock", atmip_ifnet_li, SPLIMP, DEFAULT);
        ULI("inarp_pending_q_lock", inarp_pending_q_lock_li, SPLIMP, DEFAULT);
#endif
#if ATMUNI
	ULI("atmuni_softc.drv_lock", atmuni_drv_lock_i, SPLIMP, DEFAULT);
	ULI("atmuni_softc.vuni_lock", atmuni_vuni_lock_i,
	                                    SPLIMP, DEFAULT);
	ULI("atmuni_softc.vuni_prv_lock(uni)",
	                 atmuni_vuni_prv_lock_i,
	                 SPLIMP, DEFAULT);
	ULI("atmuni_softc.ilmi_lock", atmuni_ilmi_lock_i,
	                 SPLIMP, DEFAULT);
	ULI("atmuni_softc.sig_lock", atmuni_sig_lock_i,
	                 SPLIMP, DEFAULT);
	ULI("atmuni_softc.unigen_lock", atmuni_unigen_lock_i,
	                 SPLIMP, DEFAULT);
#endif
        ULI("atm_cmm_driver_list",atm_cmm_driver_list_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_ppa_list",atm_cmm_ppa_list_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_converge_list",atm_cmm_converge_list_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_signal_list",atm_cmm_signal_list_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_vc_zombies_list",atm_cmm_vc_zombies_list_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_vcs_zombies_list",atm_cmm_vcs_zombies_list_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_bind_zombies_list",atm_cmm_bind_zombies_list_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_ppa_zombies_list",atm_cmm_ppa_zombies_list_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_addr_zombies_list",atm_cmm_addr_zombies_list_info,
                                        SPLIMP,DEFAULT);

        ULI("atm_cmm_device_lock",atm_cmm_device_lock_info,SPLIMP,DEFAULT);
	ULI("atm_time_aging_vcs_list",atm_cmm_vc_time_aging_info,
					SPLIMP,DEFAULT);
        ULI("atm_cmm_device.esi_list",atm_cmm_device_esi_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_device.ppas_list",atm_cmm_device_ppas_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_device.vchash_list",atm_cmm_device_vchash_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_device.vcs_list",atm_cmm_device_vcs_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_device.unalloc_list",atm_cmm_device_unalloc_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_device.unused_list",atm_cmm_device_unused_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_res_exp_list",atm_cmm_res_exp_list_info, SPLIMP,DEFAULT);

        ULI("atm_cmm_esi_lock",atm_cmm_esi_lock_info,SPLIMP,DEFAULT);

        ULI("atm_cmm_ppa_lock",atm_cmm_ppa_lock_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_ppa_lock.binds_list",atm_cmm_ppa_binds_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_ppa_lock.dbinds_list",atm_cmm_ppa_dbinds_list_lock_info,
                                        SPLIMP,DEFAULT);


        ULI("atm_cmm_cvg_lock",atm_cmm_cvg_lock_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_cvg.esis_list",atm_cmm_cvg_esis_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_cvg.binds_list",atm_cmm_cvg_binds_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_cvg.vcs_list",atm_cmm_cvg_vcs_list_lock_info,
                                        SPLIMP,DEFAULT);

        ULI("atm_cmm_sig_lock",atm_cmm_sig_lock_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_sig.ppas_list",atm_cmm_sig_ppas_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_sig_lock.vcs_list",atm_cmm_sig_vcs_list_lock_info,
                                        SPLIMP,DEFAULT);

        ULI("atm_cmm_bind_lock",atm_cmm_bind_lock_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_bind.vcs_list",atm_cmm_bind_vcs_list_lock_info,
                                        SPLIMP,DEFAULT);
	ULI("atm_cmm_start_queue",atm_cmm_start_q_list_lock_info,
					SPLIMP,DEFAULT);
        ULI("atm_cmm_vc_lock",atm_cmm_vc_lock_info,SPLIMP,DEFAULT);
        ULI("atm_cmm_vc.eps_list",atm_cmm_vc_eps_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_vc.ieps_list",atm_cmm_vc_ieps_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_vc.ceps_list",atm_cmm_vc_ceps_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_vc.deps_list",atm_cmm_vc_deps_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_vc.neps_list",atm_cmm_vc_neps_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_vc.causes_list",atm_cmm_vc_causes_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_vc.log_list",atm_cmm_vc_log_list_lock_info,
                                        SPLIMP,DEFAULT);
        ULI("atm_cmm_addr_lock",atm_cmm_addr_lock_info,SPLIMP,DEFAULT);

        ULI("atm_cmm_vcs_lock",atm_cmm_vcs_lock_info,SPLIMP,DEFAULT);
#if ATMILMI3X /* ATM ILMI */
	ULI("atm:ilmi_softc.lock", ilmi_lock_i, SPLIMP, DEFAULT);
	ULI("atm:ilmi_softc.rq_lock(ctx)", ilmi_rq_lock_i, SPLIMP, DEFAULT);
	ULI("atm:ilmi_softc.rx_lock(ctx)", ilmi_rx_lock_i, SPLIMP, DEFAULT);
#endif
#if UNI3X /* New ATM Signaling */
	ULI("atmsig_softc.rq_lock", atmsig_rq_lock_i, SPLIMP, DEFAULT);
	ULI("atmsig_softc.rx_lock", atmsig_rx_lock_i, SPLIMP, DEFAULT);
	NLI("atmsig_softc.trace_lock(ctx)", atmsig_trace_lock_i, SPLNONE, DEFAULT);
	ULI("atmsig_softc.callref_lock(ctx)", atmsig_callref_lock_i, SPLIMP, DEFAULT);
	ULI("atmsig_softc.lock", atmsig_lock_i, SPLIMP, DEFAULT);
#endif
#if ATMTM  /* Another ATM Test Module (atmtm) */
	ULI("atmtm_ppa_qlock", atmtm_ppa_qlkinfo, SPLIMP, DEFAULT);
	ULI("atmtm_vc_lock", atmtm_vc_lkinfo, SPLIMP, DEFAULT);
	ULI("atmtm_concon_qlock", atmtm_concon_qlkinfo, SPLIMP, DEFAULT);
	ULI("atmtm_report_qlock", atmtm_report_qlkinfo, SPLIMP, DEFAULT);
	ULI("atmtm_con_handle_lock", atmtm_con_handle_lkinfo, SPLIMP, DEFAULT);
	ULI("atmtm_srv_handle_lock", atmtm_srv_handle_lkinfo, SPLIMP, DEFAULT);
	ULI("atmtm_repfree_qlock", atmtm_repfree_qlkinfo, SPLIMP, DEFAULT);
	ULI("atmtm_misc_lock", atmtm_misc_lkinfo, SPLIMP, DEFAULT);
#endif
#endif					/* ATM */
        /* End of ATM locks */

	SLI("pmap_seg.ps_seg_lock", pmap_seg_ps_seglockinfo,
							SPLIMP, DEFAULT);
	SLI("pmap_ssm.pss_lock", pmap_ssm_lockinfo, SPLIMP, DEFAULT);
	SLI("pmap.lock", user_pmap_lockinfo, SPLIMP, DEFAULT);
	SLI("pvh.lock", pvh_lockinfo, SPLIMP, DEFAULT);
	SLI_DISABLE_HIERARCHY_CHECKING(pvh_lockinfo);
	SLI("pmap.other_lock", user_pmap_other_lockinfo, SPLIMP, DEFAULT);
	SLI("kernel_pmap.lock", kernel_pmap_lockinfo, SPLIMP, DEFAULT);
	SLI("kernel_pmap.other_lock", kernel_pmap_other_lockinfo,
							SPLIMP, DEFAULT);
	SLI("reaper_lock", reaper_lockinfo, SPLSCHED, DEFAULT);
	SLI("event.ev_slock", event_lockinfo, SPLSCHED, DEFAULT);
	SLI("thread_callq.tcq_lock", tcq_lockinfo, SPLHIGH, DEFAULT);
	ULI("proc.p_timer_lock", proc_timer_lockinfo, SPLHIGH, DEFAULT);
	SLI("mpqueue_head.lock", mpqueue_lockinfo, SPLHIGH, DEFAULT);
	SLI("kmemdata.waitlock", kmemdata_waitlock_info, SPLHIGH, DEFAULT);
	SLI("kmembuckets.kb_lock", kdp_kb_lockinfo, SPLHIGH, DEFAULT);
	SLI("kmem_debug_lock", kmem_debug_lockinfo, SPLHIGH, DEFAULT);
	SLI("vm_page_wire_lock", vm_page_wire_lockinfo, SPLHIGH, DEFAULT);
	SLI("vm_page_free_lock", vm_page_free_lockinfo, SPLHIGH, DEFAULT);
	SLI("vm_page_bucket.bk_lock", vm_page_bucket_lockinfo, SPLHIGH,DEFAULT);
	SLI("contig_malloc_lock", contig_malloc_lockinfo, SPLHIGH, DEFAULT);

	/* lock classes below here cannot use assert_wait, wakeup, etc. */

	SLI("class.lock", class_lockinfo, SPLSCHED, ORDERED);
	SLI("thread.lock", thread_lockinfo, SPLSCHED, ORDERED);
	SLI("wait_queue.lock", wait_queue_lockinfo, SPLSCHED, DEFAULT);
	SLI("swapper_lock_data", swapper_lockinfo, SPLSCHED, DEFAULT);
	SLI("callout_lock", callout_lockinfo, SPLHIGH, DEFAULT);
	SLI("processor_set.idle_lock", pset_idle_lockinfo, SPLSCHED, DEFAULT);
	SLI("processor.lock", processor_lockinfo, SPLSCHED, DEFAULT);
	SLI("processor.runq.lock", proc_runq_lockinfo, SPLSCHED, DEFAULT);
	SLI("processor_set.runq.lock", pset_runq_lockinfo, SPLSCHED, DEFAULT);
	SLI("action_lock", action_lockinfo, SPLSCHED, DEFAULT);

	ULI("session.s_fpgrp_lock", sess_fpgrp_lockinfo, SPLHIGH, DEFAULT);
	ULI("pgrp.pg_ref_lock", pgrp_refcnt_lockinfo, SPLHIGH, DEFAULT);
	SLI("xprlock", xprlockinfo, SPLHIGH, DEFAULT);
	SLI("processor.callout_lock", processor_callout_lockinfo, SPLDEVRT, ORDERED);
	SLI("callout_free_lock", callout_free_lockinfo, SPLDEVRT, DEFAULT);

	SLI("binlog_lock", binlog_lockinfo, SPLEXTREME, DEFAULT);
	SLI("msgbuf_lock", msgbuf_lockinfo, SPLEXTREME, DEFAULT);
	SLI("tsd_table_lock", tsd_table_lockinfo, SPLNONE, DEFAULT);

	/******************************************/
	/* end of lockinfo specs for simple locks */
	/******************************************/

	/******************************************/
        /* start of lockinfo specs for NOCHECK    */
	/* simple locks.			  */
	/******************************************/

#if	(DEC4000 == 1)
	ULI_NOCHECK("kn430_fprint_lock", kn430_fprint_lockinfo);
	ULI_NOCHECK("kn430_watch_lock", kn430_watch_lockinfo);
#endif	/* DEC4000 */
#if	(NTRA > 0)
	ULI_NOCHECK("tra_softc.scb_clear_lock",  tra_lockinfo);
#endif 	/* (NTRA > 0 */
	ULI_NOCHECK("bp_map.map_lock", bp_map_lockinfo);
	ULI_NOCHECK("cluster_bl_lock", cluster_bl_lockinfo);
	ULI_NOCHECK("exec_switch_lock", exec_switch_lockinfo);
#if	(NMLOG > 0)
	ULI_NOCHECK("mem_lock", mem_lockinfo);
#endif	/* NMLOG > 0 */
#if	(CDFS > 0)
	ULI_NOCHECK("cdfs.lock", cdfs_lockinfo);
	ULI_NOCHECK("cdhead.hash_lock", cdfs_hash_lockinfo);
	ULI_NOCHECK("cdfs.mount_lock", cdfsmount_lockinfo);
	ULI_NOCHECK("cnode.cd_incore_lock", cdfs_incore_lockinfo);
#endif	/* CDFS > 0 */
#if	(FFM_FS > 0)
	ULI_NOCHECK("ffm_mounttab_lock", ffm_mounttab_lockinfo);
#endif	/* FFM_FS > 0 */
#if	(NTCDS > 0)
	ULI_NOCHECK("DMA_CTRL.d3_lk_ctrl", d3cntrl_lockinfo);
#endif	/* NTCDS > 0 */
#if	(NPSIOP > 0)
	ULI_NOCHECK("siop_lock", siop_lockinfo);
#endif	/* NPSIOP > 0 */
	ULI_NOCHECK("nfs_export_lock", nfs_export_lockinfo);
#if	(VAGUE_STATS == 0)
	ULI_NOCHECK("rpc_cl_stat_lock", rpc_cl_stat_lockinfo);
	ULI_NOCHECK("rpc_sv_stat_lock", rpc_sv_stat_lockinfo);
#endif
#if	(NVBA > 0) || (CVBA > 0)
	ULI_NOCHECK("vba_bus_adapt.adapt_s_lock", vhp_adapt_s_lockinfo);
#endif	/* NVBA > 0 || CVBA > 0 */
#if	(STRIFNET > 0)
	ULI_NOCHECK("contextPtr.context_lock", streamsm_context_lockinfo);
	ULI_NOCHECK("list(streams)_lock", streamsm_list_lockinfo);
#endif	/* STRIFNET > 0 */
#if	(NLSM_TED > 0)
	ULI_NOCHECK("ted_lockp", ted_lockp_lockinfo);
	ULI_NOCHECK("ted_event.e_condp", ted_act_lockinfo);
#endif	/* NLSM_TED > 0 */
	ULI_NOCHECK("mfs_minor_lock", mfs_minor_lockinfo);
	ULI_NOCHECK("gen_lock", gen_lockinfo);
	ULI_NOCHECK("dhp.dqh_lock", dqh_lockinfo);
	ULI_NOCHECK("dqfree_lock", dqfree_lockinfo);
	ULI_NOCHECK("ump_qsync_lock", ump_qsync_lockinfo);
        ULI_NOCHECK("mounttab_lock", mounttab_lockinfo);
	ULI_NOCHECK("fs.fs_lock", fs_lockinfo);
	ULI_NOCHECK("fifo_fileid_lock", fifo_fileid_lockinfo);
	ULI_NOCHECK("fifonode.fn_fifo_lock", fifo_lockinfo);
	ULI_NOCHECK("speclisth.sh_lock", spechash_lockinfo);
	ULI_NOCHECK("devlist.lock",devlist_lockinfo);
	ULI_NOCHECK("bfreelist_lock", bfreelist_lockinfo);
	ULI_NOCHECK("bufhd.bhd_lock", bhash_lockinfo);
	ULI_NOCHECK("flckinfo.flckinfo_lock", flckinfo_lockinfo);
	ULI_NOCHECK("flino.flino_lock", flino_lockinfo);
	ULI_NOCHECK("fids_lock", fids_lockinfo);
	ULI_NOCHECK("vn_dealloc_cache_lockup_ref",
		    vn_dealloc_cache_lookup_ref_lockinfo);
	ULI_NOCHECK("mount.m_lock", mount_lockinfo);
	ULI_NOCHECK("mount.m_vlist_lock", mount_vlist_lockinfo);
	ULI_NOCHECK("vnode.v_output_lock", vnode_output_lockinfo);
	ULI_NOCHECK("vnode.v_aux_lock", vnode_aux_lockinfo);
	ULI_NOCHECK("vnode.v_buflists_lock", buflists_lockinfo);
	ULI_NOCHECK("mountlist_lock", mountlist_lockinfo);
#if	MACH_LDEBUG
	ULI_NOCHECK("vnode_trace_lock", vnode_trace_lockinfo);
#endif	/* MACH_LDEBUG */
#if	(MACH_XP_FPD > 0)
	ULI_NOCHECK("memory_manager_default_lock", 
	  	    memory_manager_default_lockinfo);
#endif	/* (MACH_XP_FPD > 0) */
	ULI_NOCHECK("vm_perf_lock", vm_perf_lockinfo);
	ULI_NOCHECK("vm_swap_list.vsl_lock", vm_swap_list_vsl_lockinfo);
#if	(NLSM > 0)
	ULI_NOCHECK("volspin.vol_alloc_spin_lock", vol_alloc_spin_lockinfo);
	ULI_NOCHECK("volsync.sy_lock", vol_allocsync_lockinfo);
#endif	/* NLSM	> 0) */
#ifdef	DTM
	ULI_NOCHECK("dtm_list_lock", dtm_list_lockinfo);
#endif
	

	/******************************************/
        /* end of lockinfo specs for NOCHECK      */
	/* simple locks.			  */
	/******************************************/

	i = (1 << LOCKSTATS_SHIFT) - 1;
	lsp = (struct lockstats *)(((unsigned long)lip + i) & ~i);
	lockinfo_count = lip - lip_start;
	lockinfo_table = lip_start;

	if (lockmode==4) {
		for (i = 0; i < ncpus; i++, lsp += lockinfo_count)
			lockstats_table[i] = lsp;
		bzero((char *)lip, (char *)lsp - (char *)lip);
	}
	return((char *)lsp - (char *)lip_start);
}


