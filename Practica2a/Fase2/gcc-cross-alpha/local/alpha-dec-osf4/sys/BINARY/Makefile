IDENT=-DIDENT=BINARY -DMACH -DOSF -DCOMPAT_43 -DUFS -DTRN
#
# *****************************************************************
# *                                                               *
# *    Copyright (c) Digital Equipment Corporation, 1991, 1999    *
# *                                                               *
# *   All Rights Reserved.  Unpublished rights  reserved  under   *
# *   the copyright laws of the United States.                    *
# *                                                               *
# *   The software contained on this media  is  proprietary  to   *
# *   and  embodies  the  confidential  technology  of  Digital   *
# *   Equipment Corporation.  Possession, use,  duplication  or   *
# *   dissemination of the software and media is authorized only  *
# *   pursuant to a valid written license from Digital Equipment  *
# *   Corporation.                                                *
# *                                                               *
# *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
# *   by the U.S. Government is subject to restrictions  as  set  *
# *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
# *   or  in  FAR 52.227-19, as applicable.                       *
# *                                                               *
# *****************************************************************
#
# HISTORY
#
#
#	@(#)$RCSfile: template.mk,v $ $Revision: 4.6.105.2 $ (DEC) $Date: 1998/10/15 17:57:57 $
#
# (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
# ALL RIGHTS RESERVED
#
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# Copyright (c) 1988 Carnegie-Mellon University
# Copyright (c) 1987 Carnegie-Mellon University
# Copyright (c) 1986 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement specifies
# the terms and conditions for use and redistribution.
#  
#
# OSF/1 Release 1.0

#
# Copyright (c) 1980, 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#

#
#  This must be here before any rules are possibly defined by the
#  machine dependent makefile fragment so that a plain "make" command
#  always works.  The config program will emit an appropriate rule to
#  cause "all" to depend on every kernel configuration it generates.
#

VPATH=..

#
# Set up values that need to work in ODE as well as outside 
# of ODE.
#

alpha_CC_SUITE	= ACC
alpha_cc_suite  = acc
mips_CC_SUITE	= MCC
mips_cc_suite  	= mcc
alpha_TARGET_MACHINE	= ALPHA
mips_TARGET_MACHINE	= MIPS
alpha_CURRENT_MACHINE	= ALPHA
mips_CURRENT_MACHINE	= MIPS

target_machine = ${target_machine?${target_machine}:${MACHINE}}
current_machine = ${current_machine?${current_machine}:${MACHINE}}
#
# Set upper case values.
TARGET_MACHINE = ${${target_machine}_TARGET_MACHINE}
CURRENT_MACHINE = ${${current_machine}_CURRENT_MACHINE}

CC_SUITE = ${CC_SUITE?${CC_SUITE}:${${target_machine}_CC_SUITE}}
cc_suite = ${cc_suite?${cc_suite}:${${target_machine}_cc_suite}}

#  Shortened for macro definitions.
_C_M_ = ${CURRENT_MACHINE}
_T_M_ = ${TARGET_MACHINE}


# 
# Determine development environment, based on current machine and
# target machine.  The default is a native development environment.
#
# ${CURRENT_MACHINE}_${TARGET_MACHINE}_DEVENV

MIPS_ALPHA_DEVENV = CROSS
DEVENV = ${${_C_M_}_${_T_M_}_DEVENV?${_C_M_}_${_T_M_}_DEVENV:NATIVE}

build_all: all

_build_prefix_%: %

cpu=arch/${target_machine}

#
#  In order to move the link commands out of config and back into the
#  template makefile, config has been changed to emit a dendency rule
#  of the form *vmunix.sys: *vmunix.swap for each configuration so that
#  the common commands for building each configuration can be placed
#  directly in the template in the default rule for the .sys.swap
#  dependency.
#
.SUFFIXES: .swap .sys

#
#  Make sure we don't remove this by accident if interrupted at the wrong
#  time.
#
.PRECIOUS: Makefile

#
#  Tools needed
#
AWK=		awk
BASENAME=	basename
CAT=		cat
CD=		cd
CP=		cp
CSPLIT=		csplit
DIRNAME=	dirname
ECHO=		echo
ED=		ed
EGREP=		egrep
EX=		ex
GREP=		grep
KSH=		ksh
LINT=		lint
LN=		ln
LS=		ls
MAKE=		make
MKDIR=		mkdir
MV=		mv
RM=		rm -f
SED=		sed
SHELL=		sh
SORT=		sort
TOUCH=		touch
UNIQ=		uniq

#
#  Compilation components
#

# Contrain the search path of CC, CPP and C2 instead of absolute paths.

OBJECT_FORMAT = ${OBJECT_FORMAT?${OBJECT_FORMAT}:COFF}
_CC_EXEC_PREFIX = ${${OBJECT_FORMAT}_${CC_SUITE}_EXEC_PREFIX}
CC=	${_CC_EXEC_PREFIX}cc
CPP=	${CC} -E
LD=	${_CC_EXEC_PREFIX}ld
NM=	${_CC_EXEC_PREFIX}nm

ENCODE=	uuencode
DECODE=	uudecode

GCC_VOLATILE = 
MCC_VOLATILE ="-Dvolatile= "
ACC_VOLATILE ="-Dvolatile= "
VOLATILE=${${CC_SUITE}_VOLATILE}
FORCE_VOLATILE=

VMUNIX_LIB=

#
#  Pre-processor environment
#
INCLUDES= -I -I. -I.. -I../include
ALLDEFINES= -DKERNEL -D_KERNEL -D_BSD -DBINARY
ALLOPTS= ${INCLUDES} ${IDENT} ${ALLDEFINES}
LINTOPTS=${ALLOPTS} ${VOLATILE}

#
#  Common C-compilation flags
#
#  To build a DEBUGable kernel define CDEBUGOPTS=-g in config file
# 

COPTS_P=${CDEBUGOPTS} ${DEPENDS} ${ALLOPTS} ${${CC_SUITE}_OPTS} ${CCOMPRESS} -MD

ACC_CFLAGS = -no_excpt -Wg,-unroll,1 -Wb,-static -Wco,-nofloat -Olimit 3000 -msg_inform cvtdiftypes -msg_inform uninit1
ACC_CFOPTS = -no_excpt -Wg,-unroll,1 -Wb,-static -Olimit 3000 -msg_inform cvtdiftypes -msg_inform uninit1
ACC_DCFLAGS = -no_excpt -Wco,-nofloat -Olimit 3000
ACC_DCFOPTS = -no_excpt -Olimit 3000
MCC_CFLAGS =
MCC_CFOPTS =

# Make internal symbols in the kernel servers visible for profiling
# and debugging. Enable type checking in the MIG stubs.
# Turn on ANSI-style prototypes.
 
MIG_CFLAGS=-Dmig_internal= -DTypeCheck=1

CFLAGS  = ${COPTS_P} ${${@}_MIG?${MIG_CFLAGS}:} ${${CC_SUITE}_CFLAGS}
COPTS   = ${COPTS_P} ${${@}_MIG?${MIG_CFLAGS}:} ${${CC_SUITE}_CFLAGS}
CFOPTS  = ${COPTS_P} ${${CC_SUITE}_CFOPTS}
DCFLAGS = ${COPTS_P} ${${CC_SUITE}_DCFLAGS}
DCOPTS  = ${COPTS_P} ${${CC_SUITE}_DCFLAGS}
DCFOPTS = ${COPTS_P} ${${CC_SUITE}_DCFOPTS}

#
#  Common assembly flags

SFLAGS=	${DEPENDS} ${ALLOPTS} ${${CC_SUITE}_OPTS} -DASSEMBLER

#
#  Path name of the version identification file.

FEATURES=${cpu}/FEATURES.h
VERSION_FILES= \
	conf/version.type \
	conf/version.major \
	conf/version.minor \
	conf/version.variant \
	conf/version.build \
	conf/version.patch

#
#  LDOBJS is the set of object files which comprise the kernel.
#  It is used both in the dependency list for each *vmunix.swap
#  rule emitted by config and also in the .sys.swap rule
#  below which links the kernel from these objects.
#  
#  LDOBJS_PREFIX and LDOBJS_SUFFIX are defined in the machine
#  dependent Makefile (if necessary).

LDOBJS=${LDOBJS_PREFIX} ${OBJS} ${LDOBJS_SUFFIX}

#
#  LDDEPS is the set of extra dependencies associated with each
#  *vmunix.swap rule (in addition to $LDOBJS and the swap*.o file).
#
#  LDDEPS_PREFIX is defined in the machine dependent Makefile
#  (if necessary).

LDDEPS=${LDDEPS_PREFIX} ${VERSION_FILES} \
	conf/version.banner conf/newvers.sh conf/copyright

#
#  PRELDDEPS is another set of extra dependencies associated with each
#  *vmunix.swap rule (in addition to $LDOBJS and the swap*.o file).
#  It is defined in the machine dependent Makefile (if necessary).
#
#  The generated rule looks like
#	vmunix.sys: ${PRELDDEPS} ${ORDERED} ${OBJS} ${LDDEPS}
#

#
#  SWAPDEPS is the set of extra dependencies associated with each
#  swap*.o rule emitted by config (in addition to the
#  ../${cpu}/swap*.c file).
#
#  SWAPDEPS_PREFIX is defined in the machine dependent Makefile
#  (if necessary).
#
SWAPDEPS=${SWAPDEPS_PREFIX} 

#
#  SYSDEPS is the set of extra dependencies associated with each
#  *vmunix rule (in addition to *vmunix.sys).
#
#  SYSDEPS_PREFIX is defined in the machine dependent Makefile
#  (if necessary).
#
SYSDEPS=${SYSDEPS_PREFIX}



#
#  Compilation rules to generate *vmunix from *vmunix.sys
#
SYS_RULE_1=@eval `${AWK} 'NR==1{S=$$1;next;};\
END {\
  print "rm -f $@";\
  C = "ln $@.sys $@";\
  if (S != "") {\
    C = C "; ln $@ $@" S; \
    printf "rm -f $@%s; ", S; \
  }\
  printf "echo \"%s\"; %s\n", C, C; \
}' vers.suffix`
SYS_RULE_2=
SYS_RULE_3=
SYS_RULE_4=

#
# Compilation rules to generate .o from .b
#
B_RULE_1A=${RM} $*.o; ${DECODE} 
B_RULE_1B=$*.b

#
# Compilation rules to generate .o from .o
#
O_RULE_1A=${RM} $*.o; cp 
O_RULE_1B=$*.o .

#
# Compilation rules to generate .o from .s
#
S_RULE_1A=${KCPP} ${SFLAGS} 
S_RULE_1B=$*.s >$*.i 
S_RULE_2=${AS} -o $*.o $*.i
S_RULE_3=${RM} $*.i

#
# Compilation rules to generate .o from .c for normal files
#
C_RULE_1A=${KCC} -c ${CFLAGS}
C_RULE_1B=$*.c
C_RULE_2=
C_RULE_3=
C_RULE_4=

#
# Compilation rules to generate .o from .c for driver files
#
C_RULE_1A_D=${C_RULE_1A}
C_RULE_1B_D=${C_RULE_1B}
C_RULE_2_D=${C_RULE_2}
C_RULE_3_D=${C_RULE_3}
C_RULE_4_D=${C_RULE_4}

#
# Compilation rules to generate .o from .c for profiling routine files
#
C_RULE_1A_P=${KCC} -c -S ${COPTS_P} 
C_RULE_1B_P=${C_RULE_1B}
C_RULE_2_P=ex - $*.s < ${GPROF.EX}
C_RULE_3_P=${AS} -o $*.o $*.s
C_RULE_4_P=${RM} $*.s


gprof: kgmon_on all kgmon_off

kgmon_on:
	kgmon -r -b

kgmon_off:
	kgmon -h -p
	gprof /mach >GPROF

MIPS_TEXTBASE=${LOADADDR?${LOADADDR}:80030000}
ALPHA_TEXTBASE=${LOADADDR?${LOADADDR}:ffffffff00000000}
TEXTBASE=${${_T_M_}_TEXTBASE}

#
#  Theses macros are filled in by the config program depending on the
#  current configuration.  The MACHDEP macro is replaced by the
#  contents of the machine dependent makefile template and the others
#  are replaced by the corresponding symbol definitions for the
#  configuration.
#


OBJS=ufs_quota.o kern_memcntl.o kern_swapctl.o rt_init_sysent.o \
	rt_syscalls.o soe_two_init_sysent.o soe_two_syscalls.o \
	svid_three_init_sysent.o svid_three_syscalls.o \
	svr_four_init_sysent.o svr_four_syscalls.o sysv_init_sysent.o \
	sysv_syscalls.o rt_hab_cfg.o soe_two_cfg.o svid_three_cfg.o \
	svr_four_cfg.o sysv_hab_cfg.o vfs_svid2calls.o micro_time.o \
	alpha_scrub.o platform_switch.o dec7000_cons.o dma_direct_map.o \
	devz.o lsb_common.o mbox_data.o trn_sr.o ted.o tedSpace.o cm.mod \
	generic.mod io.mod ipc.mod proc.mod sec.mod socket.mod \
	sec_min.mod rt.mod std_kern.mod bsd_tty.mod xpr.mod mach_xp.mod \
	cdfs.mod dvdfs.mod ess.mod ess_stub.mod kdebug.mod dli.mod \
	ffm_fs.mod atm.mod atmip.mod lane.mod atmifmp.mod atmtm.mod \
	atmuni.mod atmilmi3x.mod uni3x.mod bparm.mod lat.mod lv.mod \
	advfs.mod packetfilter.mod net.mod netrain.mod ether.mod \
	loop.mod sl.mod ppp.mod inet.mod nfs.mod nfs_server.mod \
	procfs.mod notprocfs.mod snmpinfo.mod bufcall.mod streams.mod \
	streams_debug.mod dlb.mod dlpi.mod ifnet.mod kinfo.mod \
	strstd.mod svvs.mod timod.mod tirdwr.mod ldtty.mod xtiso.mod \
	pts.mod ufs.mod uipc.mod vfs.mod vm.mod _lmf_.mod pckt.mod \
	ntp_time.mod mlog.mod profiling.mod pty.mod prf.mod \
	mach_co_stats.mod mach_ipc_stats.mod gwscreen.mod pwrmgr.mod \
	dec_audit.mod sec_base.mod sec_driver.mod sec_mld.mod \
	dec_acl.mod dce_acl_stubs.mod spd_cache.mod acl_stubs.mod \
	spd_mac.mod spd_misc.mod arch_alpha.mod in_cksum.mod pfm.mod \
	arch_alphapmap.mod fp.mod mcount.mod kn15aa_mult.mod kn15aa.mod \
	kn16aa_mult.mod kn16aa.mod kn430_mult.mod kn430.mod \
	kn430_common.mod kn7aa_mult.mod kn7aa.mod kn7aa_common.mod \
	kn8ae_mult.mod kn8ae.mod kn8ae_common.mod dc21171_mult.mod \
	dc21171.mod kn121_mult.mod kn121.mod kn25_mult.mod kn25.mod \
	kn450_mult.mod kn450.mod cbus2_pci_mult.mod cbus2_pci.mod \
	kn470_mult.mod kn470.mod kn20aa_mult.mod kn20aa.mod \
	kn22a_mult.mod kn22a.mod ebp10_mult.mod ebp10.mod eb64p_mult.mod \
	eb64p.mod eb64p_pallib.mod eb66_mult.mod eb66.mod \
	eb66_pallib.mod eb164_mult.mod eb164.mod eb164_pallib.mod \
	ebv10_mult.mod ebv10.mod ebv10_common.mod ds1386clock_mult.mod \
	ds1386.mod ebv14_mult.mod ebv14.mod ebv14_pallib.mod \
	ebv16_mult.mod ebv16.mod ebv16_pallib.mod ebm10_mult.mod \
	ebm10.mod ebm20_mult.mod ebm20.mod ruby_common_mult.mod \
	ruby_common.mod kn300_mult.mod kn300.mod kn600_mult.mod \
	kn600.mod ebm30_mult.mod ebm30.mod alphabook_mult.mod \
	alphabook.mod mcbus.mod mcpcia_mult.mod mcpcia.mod dc104x.mod \
	dc104x_mult.mod linear_io_access.mod linear_io_access_mult.mod \
	pc_bell_mult.mod pc_bell.mod sio.mod pic.mod mc146818_mult.mod \
	mc146818.mod lca_mult.mod lca.mod apecs_mult.mod apecs.mod \
	vba_vipvic.mod vba_univ.mod lsbmem_mult.mod lsbmem.mod \
	cma_dd.mod cam_disk.mod cam_tape.mod cam.mod cam_sim.mod \
	cam_tcds.mod cam_94.mod cam_aha1740.mod cam_ata.mod isp.mod \
	itpsa.mod cam_pza.mod cam_tza.mod cam_simport.mod cam_psiop.mod \
	cam_siop.mod cam_xza.mod fbus.mod mbox.mod ibus.mod xmi.mod \
	xna.mod mfa.mod tc.mod scc.mod nvtc.mod bba.mod eisa.mod i2c.mod \
	iscc.mod isa.mod gpc.mod ace.mod lp.mod envram.mod re_xcr.mod \
	pci.mod pnvram.mod mchan.mod pcia_mult.mod pcia.mod pd6729.mod \
	pcic.mod pcmcia.mod i2o.mod i2o_bs.mod ln.mod le.mod te.mod \
	tu.mod fza.mod fta.mod tra.mod faa.mod vb.mod lta.mod lpa.mod \
	dsa_cippd.mod dsa_np.mod dsa_scs.mod dsa_sysap.mod dsa_uba.mod \
	dsa_uqserv.mod dsa_kdm.mod fdi.mod ws.mod scc_input.mod \
	gpc_input.mod qfont.mod bt431.mod bt459.mod bt463.mod fb.mod \
	vga.mod ati32.mod ati64.mod cirrus.mod qvision.mod s3v864.mod \
	s3trio.mod wd.mod comet.mod tga.mod sfbp.mod pv.mod pvl.mod \
	pvp.mod presto.mod lsm.mod vme_vba.mod ddr.mod kio.mod kds.mod \
	envmon.mod distint.mod el.mod lan_common.mod hmc.mod \
	pci_isa_intr.mod ev6_common.mod usb.mod usb_ohci.mod usb_hub.mod \
	usb_hid.mod usb_keyboard.mod usb_mouse.mod usb_printer.mod \
	emx.mod alt.mod lfa.mod 

GOBJS=cm_cfg.o generic_cfg.o io_cfg.o kern_devsw.o ipc_cfg.o proc_cfg.o \
	sec_cfg.o socket_cfg.o spd_proplist.o spd_udac.o sec_conf.o \
	sec_subrs.o sec_acl.o rt_cfg.o init_sysent.o exc_server.o \
	exc_user.o mach_host_server.o mach_server.o syscalls.o \
	cmu_syscalls.o coff_exec.o interp_exec.o kern_acct.o kern_aio.o \
	kern_clock.o kern_class.o kern_compat.o kern_descrip.o \
	kern_exec.o kern_execargs.o kern_execconfig.o kern_exit.o \
	kern_fork.o kern_kmodcall.o kern_malloc.o contig_malloc.o \
	kern_mman.o kern_proc.o kern_prot.o kern_resource.o kern_sig.o \
	kern_sigqueue.o kern_subr.o kern_subsys.o kern_synch.o \
	kern_time.o kern_utctime.o kern_xxx.o ldr_kload.o lwc.o \
	mach_process.o mach_signal.o subr_binlog.o subr_log.o subr_prf.o \
	subr_rmap.o subr_select.o subr_xxx.o subsys_conf.o svipc_ipc.o \
	svipc_msg.o svipc_sem.o svipc_shm.o sys_generic.o sys_socket.o \
	sys_sysinfo.o tty_tty.o uipc_domain.o uipc_mbuf.o uipc_socket.o \
	uipc_socket2.o uipc_syscalls.o ux_exception.o ddi_subr.o \
	kdebug_kern.o event.o exception.o host.o ipc_basics.o \
	ipc_copyin.o ipc_copyout.o ipc_host.o ipc_kport.o ipc_kreply.o \
	ipc_kset.o ipc_mports.o ipc_pobj.o ipc_port.o ipc_prims.o \
	ipc_ptraps.o ipc_tt.o kalloc.o lock.o lockdev.o mach_factor.o \
	mach_sysdev.o mach_user_internal.o machine.o mig_support.o \
	parallel.o processor.o queue.o sched_prim.o syscall_emulation.o \
	syscall_subr.o syscall_sw.o task.o task_swap.o thread.o \
	thread_swap.o threadcall.o timer.o zalloc.o msfs_syscalls.o if.o \
	netisr.o nfs_hooks.o fdfs_vfsops.o fdfs_vnops.o kern_fuser.o \
	kern_sigsend.o kern_sysfs.o kern_sysinfo.o kern_uadmin.o \
	kern_wait.o priocntl.o procset.o tty_common.o tty_cfg.o tty.o \
	tty_compat.o tty_subr.o xpr.o memory_object_default_user.o \
	cdfs_bmap.o cdfs_config.o cdfs_lookup.o cdfs_node.o cdfs_subr.o \
	cdfs_vfsops.o cdfs_vnops.o dvdfs_vfsops.o dvdfs_node.o \
	dvdfs_vnops.o ess.o eventTypes.o groupEventFuncs.o macroFuncs.o \
	eventTypes_extensions.o macroFuncs_extensions.o \
	event_simulation.o kdebug_brkpt.o kdebug_conf.o kdebug_cfg.o \
	kdebug_io.o kdebug_main.o kdebug_proto.o db_access.o db_aout.o \
	db_break.o db_command.o db_cond.o db_doprnt.o db_examine.o \
	db_expr.o db_ext_symtab.o db_input.o db_lex.o db_macro.o \
	db_output.o db_print.o db_run.o db_sym.o db_task_thread.o \
	db_tr.o db_trap.o db_variables.o db_watch.o db_write_cmd.o \
	dli_bind.o dli_filter.o dli_init.o dli_input.o dli_mopctrs.o \
	dli_netsync.o dli_output.o dli_proto.o dli_sockopt.o dli_subr.o \
	dli_timer.o dli_usrreq.o ffm_cfg.o ffm_vfsops.o ffm_vnops.o \
	cmm.o cmm_subr.o cmm_adi.o cmm_smi.o cmm_cmi.o cmm_ppa.o \
	cmm_esi.o cmm_manage.o cmm_state.o atm_arp.o ip_converge.o \
	cm_sap_shim.o le_disp.o lec_arp.o lec_ctrl.o lec_data.o \
	lec_upper.o map.o svc_info.o utl.o utl_os.o g_event.o \
	ipsh_dunix.o ipshost.o atmtm.o atmuni_addrmgr.o atmuni_connect.o \
	atmuni_data.o atmuni_devmanip.o atmuni_except.o atmuni_ilmi.o \
	atmuni_loader.o atmuni_mmi.o atmuni_receive.o atmuni_sig.o \
	atmuni_sigstubs.o atmuni_unimanip.o ilmi_manage.o ilmi_loader.o \
	ilmi_data.o ilmi_receive.o agent.o codec.o dec_atm.o fsm.o \
	netpref.o system.o atmsig_manage.o atmsig_loader.o \
	atmsig_cmm_callbacks.o atmsig_qsaalrx.o atmsig_mainloop.o \
	atmsig_receive.o atmsig_data.o atmsig_ies.o atmsig_status.o \
	atmsig_add.o atmsig_drop.o atmsig_release.o atmsig_restart.o \
	atmsig_callrefs.o atmsig_misc.o atmsig_setup.o atmsig_addrman.o \
	atmsig_trill_as.o aal.o asd.o asi.o cm_lib.o las.o cm_atm.o \
	cm_bdy5.o cm_gen.o cm_hash.o ss_ptsp.o am_bdy1.o am_bdy2.o \
	am_bdy3.o am_bdy4.o am_bdy5.o am_db1.o am_db2.o am_id.o \
	am_ex_pt.o am_ptli.o am_mf.o am_ptmi.o as_bdy1.o as_bdy2.o \
	as_bdy3.o as_bdy4.o as_bdy5.o as_bdy6.o as_ex_pt.o as_id.o \
	as_ptui.o as_ptmi.o lm.o smambdy1.o smasbdy1.o bparm_cfg.o \
	aclchk.o aclclr.o aclcmp.o aclrep.o aclset.o adpcre.o adpdel.o \
	adplist.o adpsh.o asclro.o asclrp.o ascre.o asdel.o aslist.o \
	asmsg.o asrset.o assetf.o asseti.o asseto.o assetp.o asshow.o \
	cbabo.o cbcre.o cbdel.o cbhalt.o cbhrun.o cbhstr.o cborun.o \
	cbostr.o cbrout.o cbrxmt.o cbsrun.o cbsstr.o dbchgc.o dbrepb.o \
	dbrepc.o dbreps.o dbsetc.o dbsetm.o exerr.o hicre.o hidel.o \
	hiecan.o hierpt.o hifind.o hihra.o hihri.o hihsts.o hiinit.o \
	hiocmd.o hiopen.o hiora.o hioreq.o hiori.o hiosi.o hiosts.o \
	hiqrpt.o hiqsts.o hirej.o hiscmd.o hises.o hissi.o histr.o \
	hsrset.o hszero.o hxsts.o idlchk.o idlclr.o idlcmp.o idlset.o \
	ifchk.o ifmsg.o latcom.o lscre.o lsdel.o lsdups.o lslist.o \
	lslook.o lslsth.o lsmsg.o lsperm.o lsrem.o lsrset.o lsscan.o \
	lsshow.o lstmo.o ndcre.o nddel.o ndfail.o ndlist.o ndpur.o \
	ndshow.o ndzero.o obclon.o obcre.o obdel.o obfind.o oblist.o \
	obrel.o obren.o obrset.o obsetf.o obshow.o oxses.o qrcre.o \
	qrdel.o qrfind.o qrlist.o qrscan.o sb1inp.o sb1out.o sbacc.o \
	sbcre.o sbdel.o sbdups.o sbfind.o sbopen.o sbrej.o sbria.o \
	sbsig.o sbstop.o sbstr.o ticelp.o tocelp.o vcshow.o axrate.o \
	grpret.o hxses.o ixerr.o latadpsubs.o latclose.o latdefsvc.o \
	lathashsubs.o latlioc.o latlog.o latlrput.o latlrsrv.o latmain.o \
	latopen.o latsub.o lattimer.o lattioc.o lattli.o latursrv.o \
	latuwput.o ofmsg.o strchk.o strcvt.o strdif.o strequ.o strinp.o \
	strmov.o strret.o sxgetc.o sxputc.o sxses.o sxsig.o lv_block.o \
	lv_config.o lv_defect.o lv_ioctls.o lv_kdb.o lv_lvsubr.o \
	lv_mircons.o lv_pbuf.o lv_phys.o lv_schedule.o lv_strategy.o \
	lv_subr.o lv_syscalls.o lv_vgda.o lv_vgsa.o bs_access.o \
	bs_bitfile_sets.o bs_bmt_util.o bs_buffer2.o bs_copy.o \
	bs_create.o bs_delete.o bs_domain.o bs_errlst.o bs_extents.o \
	bs_init.o bs_inmem_map.o bs_migrate.o bs_misc.o bs_msg_queue.o \
	bs_params.o bs_qio.o bs_sbm.o bs_service_class.o bs_shadow.o \
	bs_stg.o bs_stripe.o bs_tagdir.o ftx_recovery.o ftx_routines.o \
	ms_generic_locks.o ms_logger.o ms_mode.o ms_privates.o \
	ms_public.o fs_create.o fs_dir_init.o fs_dir_lookup.o \
	fs_file_sets.o fs_quota.o fs_read_write.o mss_common.o \
	mss_entry.o mss_fs.o mss_lock.o mss_log.o mss_misc.o mss_pqd.o \
	mss_send.o mss_space.o mss_syscall.o ter_inmem_map.o \
	ter_ondisk_map.o ter_stg.o msfs_cfg.o msfs_config.o msfs_io.o \
	msfs_lookup.o msfs_misc.o msfs_proplist.o msfs_vfsops.o \
	msfs_vnops.o bpf_filter.o pfilt.o pfilt_bpf.o net_cfg.o raw_cb.o \
	raw_usrreq.o route.o netrain_cfg.o netrain.o if_nr.o \
	if_ethersubr.o if_ether.o if_loop.o if_sl.o ppp_init.o ppp_if.o \
	ppp_async.o ppp_comp.o vjcompress.o bsd_comp.o inet_cfg.o igmp.o \
	in.o in_pcb.o in_proto.o ip_icmp.o ip_input.o ip_mroute.o \
	ip_output.o ip_screen.o pmtu.o raw_ip.o tcp_debug.o tcp_input.o \
	tcp_output.o tcp_subr.o tcp_timer.o tcp_usrreq.o udp_usrreq.o \
	nfs3_vfsops.o nfs3_vnodeops.o nfs3_xdr.o nfs_client.o \
	nfs_common.o nfs_config.o nfs_dump.o nfs_subr.o nfs_vfsops.o \
	nfs_vnodeops.o nfs_xdr.o prop_xdr.o auth_kern.o authunix_prot.o \
	clnt_kudp.o clnt_ktcp.o clnt_perror.o kudp_fastsend.o \
	pmap_kgetport.o pmap_prot.o pmap_rmt.o rpc_callmsg.o rpc_prot.o \
	subr_kudp.o svc.o svc_auth.o svc_auth_unix.o svc_kudp.o \
	svc_ktcp.o xdr.o xdr_array.o xdr_mbuf.o xdr_mem.o \
	xdr_reference.o bootparam_xdr.o mountxdr.o klm_kprot.o \
	klm_lockmgr.o nfs_server.o nfs3_server.o procfs_subrs.o \
	procfs_vfsops.o procfs_vnops.o procfs_ioctl.o \
	procfs_vfsops_stubs.o procfs_subrs_stubs.o procfs_vnops_stubs.o \
	snmpinfo.o str_memory.o nd.o str_cfg.o str_env.o str_filesys.o \
	str_init.o str_modsw.o str_osr.o str_runq.o str_scalls.o \
	str_shead.o str_subr.o str_support.o str_synch.o str_tty.o \
	str_util.o str_weld.o str_debug.o dlb.o dlpi_data.o dl.o \
	dlhash.o dlioctl.o dlprim.o dlproc.o dltimer.o dlutil.o ifnet.o \
	kinfo.o log.o sad.o standard.o svvs.o timod.o tirdwr.o ldtty.o \
	ldtty_compat.o ldtty_euc.o xtiso.o pty.o mfs_vfsops.o \
	mfs_vnops.o ufs_alloc.o ufs_bmap.o ufs_cfg.o ufs_disksubr.o \
	ufs_inode.o ufs_lookup.o ufs_physio.o ufs_proplist.o ufs_subr.o \
	ufs_tables.o ufs_vfsops.o ufs_vnops.o uipc_proto.o uipc_usrreq.o \
	dead_vfsops.o dead_vnops.o fifo_vnops.o spec_vnops.o vfs_bio.o \
	vfs_cache.o vfs_cfg.o vfs_flock.o vfs_lookup.o vfs_subr.o \
	vfs_syscalls.o vfs_ubc.o vfs_vnops.o k_mape_inv.o k_mape_io.o \
	k_mape_mem.o u_mape_anon.o u_mape_dev.o u_mape_seg.o \
	u_mape_shm.o u_mape_ssm.o u_mape_vp.o vm_anon.o vm_anonpage.o \
	vm_cfg.o vm_cmap.o vm_fault.o vm_kern.o vm_kmap.o vm_map.o \
	vm_object.o vm_pagelru.o vm_resident.o vm_subr.o vm_swap.o \
	vm_umap.o vm_unix.o vm_user.o vm_vlock.o vpage.o kern_lmf.o \
	pckt.o kern_ntptime.o memlog.o subr_mcount.o tty_pty.o prf.o \
	callout_statistics.o ipc_statistics.o gw_screen.o pwrmgr.o \
	kern_audit.o kern_auditcalls.o kern_auditdev.o sec_calls.o \
	sec_socket.o sec_stream.o sec_driver.o sec_mld.o spd_pacl.o \
	dce_acl_stubs.o spd_cache.o acl_stubs.o spd_mac.o spd_misc.o \
	alpha_exception.o alpha_ptrace.o alpha_signal.o atomic_ops.o \
	byte_swap.o clock.o coff_subr.o context.o copy.o cpu.o crc.o \
	__divl.o __divq.o __divlu.o __divqu.o __reml.o __remq.o \
	__remlu.o __remqu.o ots_div_alpha.o ots_div_data_alpha.o \
	ots_extv_alpha.o ots_extv_vol_alpha.o ots_extzv_alpha.o \
	ots_extzv_vol_alpha.o ots_insv_alpha.o ots_insv_vol_alpha.o \
	ots_location_alpha.o ots_move_alpha.o ots_movem_alpha.o \
	ots_fill_alpha.o ots_zero_alpha.o ots_translate_alpha.o \
	ots_strcmp_eql_alpha.o ots_strcmp_eqlp_alpha.o \
	ots_strcmp_leq_alpha.o ots_strcmp_leqp_alpha.o \
	ots_strcmp_lss_alpha.o ots_strcmp_lssp_alpha.o dumpsys.o entry.o \
	exec_config.o exec_subr.o fastcopy.o in_checksum.o in_cksum.o \
	intr.o kernargs.o locore.o lockprim.o addupc.o machdep.o mem.o \
	pfm.o ovbcopy.o pal_lib.o pcb.o pmap.o pmap_debug.o \
	pmap_update.o prom.o spl.o super.o syscall_trap.o trap.o \
	softfp.o ieee_float_math.o 64bit_math.o bootio.o fp_ieee.o \
	fp_ieee_handler.o fp_ascii.o fp_result.o fp_scale.o fp_trigger.o \
	fp_tables.o fp_emulator.o fp_emulate.o ul.o usercopy.o nofault.o \
	vm_machdep.o mcount.o lww.o lwu.o autoconf.o cons_sw.o console.o \
	cpusw.o io_access.o kn15aa_mult.o kn15aa.o kn16aa_mult.o \
	kn16aa.o kn430_mult.o kn430.o dec4000_cons.o kn7aa_mult.o \
	kn7aa.o lsbinit.o lsb_iop.o kn8ae_mult.o kn8ae.o tlsbinit.o \
	tlsb_iop.o dc21171_mult.o dc21171.o kn121_mult.o kn121.o \
	kn25_mult.o kn25.o kn450_mult.o kn450.o cbus2_pci_mult.o \
	cbus2_pci.o kn470_mult.o kn470.o kn20aa_mult.o kn20aa.o \
	kn22a_mult.o kn22a.o ebp10_mult.o ebp10.o eb64p_mult.o eb64p.o \
	eb64p_pallib.o eb66_mult.o eb66.o eb66_pallib.o eb164_mult.o \
	eb164.o eb164_pallib.o ebv10_mult.o ebv10.o ebv10_pallib.o \
	ds1386clock_mult.o ds1386clock.o ebv14_mult.o ebv14.o \
	ebv14_pallib.o ebv16_mult.o ebv16.o ebv16_pallib.o ebm10_mult.o \
	ebm10.o ebm20_mult.o ebm20.o ruby_common_mult.o ruby_common.o \
	kn300_mult.o kn300.o kn600_mult.o kn600.o ebm30_mult.o ebm30.o \
	alphabook_mult.o alphabook.o mcbus.o mcpcia_mult.o mcpcia.o \
	dc104x.o dc104x_mult.o linear_io_access.o \
	linear_io_access_mult.o hal_lmf.o hal_sysinfo.o pc_bell_mult.o \
	pc_bell.o sio.o 82357_pic.o mc146818clock_mult.o mc146818clock.o \
	lca_mult.o lca.o apecs_mult.o apecs.o ebv10_vme.o univ_vme.o \
	kdebug_ace_cons.o kdebug_misc.o kdebug_cobra_cons.o \
	kdebug_gbus_cons.o kdebug_scc_cons.o kdebug_iscc_cons.o \
	db_alpha_aout.o db_alpha_inst.o db_alpha_sym.o db_commands.o \
	db_disasm.o db_interface.o db_trace.o driver_support.o \
	ldbl_driver_support.o ldbl_controller_support.o \
	stanza_resolver.o topology.o handler.o tty_def.o io_resource.o \
	lsbmem_mult.o lsbmem.o cma_dd.o cam_disk.o cam_tape.o \
	cam_logger.o cam_special.o ccfg.o camdb.o pdrv_common.o \
	special_audio.o special_direct.o special_generic.o \
	special_sequential.o uagt.o xpt.o dme_null.o sim_common.o \
	cam_eei.o cam_rci.o sim_xpt.o sim_htm.o sim_as.o sim_error.o \
	sim_sched.o sim_sm.o sim_target.o dme_tcds_94_dma.o tcds_adapt.o \
	dme_turbo_94_ram.o dme_common.o sim_94_fast.o sim_94.o \
	sim_kn02.o aha1740.o sim_ata.o sim_ata_acer.o sim_ata_cmd.o \
	sim_ata_cypress.o sim_ata_datatech.o sim_ata_dma.o \
	sim_ata_symphony.o sim_ata_unknown.o isp1020.o itpsa.o \
	itpsacfg.o itpsahtm.o sim_pza.o sim_kztsa.o simport.o \
	simport_htm.o simport_dme.o simport_subr.o psiop.o psiop_pci.o \
	siop.o siop_kn430.o skz_config.o skz_main.o skz_dme.o \
	skz_error.o skz_sched.o skz_debug.o skz_nport.o skz_diag.o \
	skz_target.o mips_dummy.o fbus.o fbus_loadable.o flag.o mbox.o \
	ibus.o xmiinit.o xlamb.o if_xna.o if_mfa.o tc.o tc_loadable.o \
	scc.o nvtc.o amd79c30.o amd79c30_dummy.o amd79c30_hdlc.o eisa.o \
	eisa_cnfg.o isp.o i2c.o iscc.o isa.o gpc.o ace.o lp.o envram.o \
	re_driver.o xcr_logger.o xcr_port.o pci.o dma_sg_map.o \
	shared_intr.o pci_common_intr_handler.o pnvram.o mchan.o \
	pcia_mult.o pcia.o pd6729.o pcic.o pcmcia_fnc.o pcmcia.o \
	card_services.o card_config.o pcmcia_event.o i2oexec.o i2omsg.o \
	i2opcixport.o i2o.o i2o_bs.o i2o_logger.o if_ln.o if_le.o \
	if_te.o if_tu.o if_fza.o if_fta.o if_tra.o if_faa.o if_vb.o \
	if_otto.o if_otto_xilinx.o if_ottodefs.o otto_platform.o \
	otto_flow.o otto_fakesnmp.o aal5crc.o acr_tbl.o adap_sw.o fm.o \
	if_lpa.o if_lpa_defs.o if_lpa_platform.o met_sw.o ciconfig.o \
	cippd_error.o cippd_event.o cippd_pmaint.o cippd_protocol.o \
	cippdvar.o gvp_block.o gvp_dg.o gvp_msg.o gvp_subr.o gvpvar.o \
	np_block.o np_dg.o np_error.o np_init.o np_isr.o np_lpmaint.o \
	np_msg.o np_subr.o npvar.o xminp.o scs_block.o scs_configdb.o \
	scs_conn.o scs_dg.o scs_error.o scs_event.o scs_info.o \
	scs_maint.o scs_msg.o scs_protocol.o scs_subr.o scsvar.o \
	scs_directory.o mscp_tape.o mscp_disk.o mscp_bbr.o \
	mscp_bbrstates.o mscp_config.o mscp_conpol.o mscp_diskvar.o \
	mscp_subr.o mscp_var.o sysap_start.o uba.o uqserv.o kdm.o fd.o \
	fdcam.o ws_driver.o lk201.o vsxxx.o pcxal.o pcxas.o qfont.o \
	bt431.o bt459.o bt463.o fb.o vga_support.o vga.o ati.o ati64.o \
	cirrus.o qvision.o s3v864.o s3trio.o wd.o comet.o tga.o pmagro.o \
	sfb.o pv.o pvl.o pvp.o pr.o presto_cfg.o error_event.o \
	alloc_smt.o dki_osf.o plex.o volspec.o vol.o volblog.o \
	volioctl.o volklog.o volted.o volSpace.o volroot.o vol_cfg.o \
	vba_generic.o vba_tc.o vba_pci.o vba_dispatch.o ddr.o kio.o \
	kds.o envmon.o distint_cfg.o if_el.o lan_common.o hmc.o \
	hmc_support.o pci_isa_intr.o ev6_common.o usbd.o usb_ohci.o \
	usb_hub.o usb_hid.o usb_keyboard.o usb_mouse.o usb_printer.o 

CFILES1=\
	bsd/cm_cfg.c \
	bsd/generic_cfg.c \
	bsd/io_cfg.c \
	bsd/kern_devsw.c \
	bsd/ipc_cfg.c \
	bsd/proc_cfg.c \
	dec/sec/sec_cfg.c \
	bsd/socket_cfg.c \
	sec/spd_proplist.c \
	sec/spd_udac.c \
	sec/sec_conf.c \
	sec/sec_subrs.c \
	sec/sec_acl.c \
	kern/rt_cfg.c \
	./init_sysent.c \
	./mach/exc_server.c \
	./mach/exc_user.c \
	./mach/mach_host_server.c \
	./mach/mach_server.c \
	./syscalls.c \
	bsd/cmu_syscalls.c \
	bsd/coff_exec.c \
	bsd/interp_exec.c \
	bsd/kern_acct.c \
	bsd/kern_aio.c \
	bsd/kern_clock.c \
	bsd/kern_class.c \
	bsd/kern_compat.c \
	bsd/kern_descrip.c \
	bsd/kern_exec.c \
	bsd/kern_execargs.c \
	bsd/kern_execconfig.c \
	bsd/kern_exit.c \
	bsd/kern_fork.c \
	bsd/kern_kmodcall.c \
	bsd/kern_malloc.c \
	bsd/contig_malloc.c \
	bsd/kern_mman.c \
	bsd/kern_proc.c \
	bsd/kern_prot.c \
	bsd/kern_resource.c \
	bsd/kern_sig.c \
	bsd/kern_sigqueue.c \
	bsd/kern_subr.c \
	bsd/kern_subsys.c \
	bsd/kern_synch.c \
	bsd/kern_time.c \
	bsd/kern_utctime.c \
	bsd/kern_xxx.c \
	bsd/ldr_kload.c \
	bsd/lwc.c \
	bsd/mach_process.c \
	bsd/mach_signal.c \
	bsd/subr_binlog.c \
	bsd/subr_log.c \
	bsd/subr_prf.c \
	bsd/subr_rmap.c \
	bsd/subr_select.c \
	bsd/subr_xxx.c \
	bsd/subsys_conf.c \
	bsd/svipc_ipc.c \
	bsd/svipc_msg.c \
	bsd/svipc_sem.c \
	bsd/svipc_shm.c \
	bsd/sys_generic.c \
	bsd/sys_socket.c \
	bsd/sys_sysinfo.c \
	bsd/tty_tty.c \
	bsd/uipc_domain.c \
	bsd/uipc_mbuf.c \
	bsd/uipc_socket.c \
	bsd/uipc_socket2.c \
	bsd/uipc_syscalls.c \
	builtin/ux_exception.c \
	ddidki/ddi_subr.c \
	dec/debug/kdebug/kdebug_kern.c \
	kern/event.c \
	kern/exception.c \
	kern/host.c \
	kern/ipc_basics.c \
	kern/ipc_copyin.c \
	kern/ipc_copyout.c \
	kern/ipc_host.c \
	kern/ipc_kport.c \
	kern/ipc_kreply.c \
	kern/ipc_kset.c \
	kern/ipc_mports.c \
	kern/ipc_pobj.c \
	kern/ipc_port.c \
	kern/ipc_prims.c \
	kern/ipc_ptraps.c \
	kern/ipc_tt.c \
	kern/kalloc.c \
	kern/lock.c \
	kern/lockdev.c \
	kern/mach_factor.c \
	kern/mach_sysdev.c \
	kern/mach_user_internal.c \
	kern/machine.c \
	kern/mig_support.c \
	kern/parallel.c \
	kern/processor.c \
	kern/queue.c \
	kern/sched_prim.c \
	kern/syscall_emulation.c \
	kern/syscall_subr.c \
	kern/syscall_sw.c \
	kern/task.c \
	kern/task_swap.c \
	kern/thread.c \
	kern/thread_swap.c \
	kern/threadcall.c \
	kern/timer.c \
	kern/zalloc.c \
	msfs/osf/msfs_syscalls.c \
	net/if.c \
	net/netisr.c \
	nfs/nfs_hooks.c \
	svr4/fdfs_vfsops.c \
	svr4/fdfs_vnops.c \
	svr4/kern_fuser.c \
	svr4/kern_sigsend.c \
	svr4/kern_sysfs.c \
	svr4/kern_sysinfo.c \
	svr4/kern_uadmin.c \
	svr4/kern_wait.c \
	svr4/priocntl.c \
	svr4/procset.c \
	tty/tty_common.c \
	tty/tty_cfg.c \
	bsd/tty.c \
	bsd/tty_compat.c \
	bsd/tty_subr.c \
	kern/xpr.c \
	./mach/memory_object_default_user.c \
	cdfs/cdfs_bmap.c \
	cdfs/cdfs_config.c \
	cdfs/cdfs_lookup.c \
	cdfs/cdfs_node.c \
	cdfs/cdfs_subr.c \
	cdfs/cdfs_vfsops.c \
	cdfs/cdfs_vnops.c \
	dvdfs/dvdfs_vfsops.c \
	dvdfs/dvdfs_node.c \
	dvdfs/dvdfs_vnops.c \
	dec/debug/ess/ess.c \
	dec/debug/ess/eventTypes.c \
	dec/debug/ess/groupEventFuncs.c \
	dec/debug/ess/macroFuncs.c \
	dec/debug/ess/eventTypes_extensions.c \
	dec/debug/ess/macroFuncs_extensions.c \
	dec/debug/ess/event_simulation.c \
	dec/debug/kdebug/kdebug_brkpt.c \
	dec/debug/kdebug/kdebug_conf.c \
	dec/debug/kdebug/kdebug_cfg.c \
	dec/debug/kdebug/kdebug_io.c \
	dec/debug/kdebug/kdebug_main.c \
	dec/debug/kdebug/kdebug_proto.c \
	dec/debug/ddb/db_access.c \
	dec/debug/ddb/db_aout.c \
	dec/debug/ddb/db_break.c \
	dec/debug/ddb/db_command.c \
	dec/debug/ddb/db_cond.c \
	dec/debug/ddb/db_doprnt.c \
	dec/debug/ddb/db_examine.c \
	dec/debug/ddb/db_expr.c \
	dec/debug/ddb/db_ext_symtab.c \
	dec/debug/ddb/db_input.c \
	dec/debug/ddb/db_lex.c \
	dec/debug/ddb/db_macro.c \
	dec/debug/ddb/db_output.c \
	dec/debug/ddb/db_print.c \
	dec/debug/ddb/db_run.c \
	dec/debug/ddb/db_sym.c \
	dec/debug/ddb/db_task_thread.c \
	dec/debug/ddb/db_tr.c \
	dec/debug/ddb/db_trap.c \
	dec/debug/ddb/db_variables.c \
	dec/debug/ddb/db_watch.c \
	dec/debug/ddb/db_write_cmd.c \
	dli/dli_bind.c \
	dli/dli_filter.c \
	dli/dli_init.c \
	dli/dli_input.c \
	dli/dli_mopctrs.c \
	dli/dli_netsync.c \
	dli/dli_output.c \
	dli/dli_proto.c \
	dli/dli_sockopt.c \
	dli/dli_subr.c \
	dli/dli_timer.c \
	dli/dli_usrreq.c \
	ffm/ffm_cfg.c \
	ffm/ffm_vfsops.c \
	ffm/ffm_vnops.c \
	atm/cmm/cmm.c \
	atm/cmm/cmm_subr.c \
	atm/cmm/cmm_adi.c \
	atm/cmm/cmm_smi.c \
	atm/cmm/cmm_cmi.c \
	atm/cmm/cmm_ppa.c \
	atm/cmm/cmm_esi.c \
	atm/cmm/cmm_manage.c \
	atm/cmm/cmm_state.c \
	netinet/atm/atm_arp.c \
	netinet/atm/ip_converge.c \
	net/if_lane/cm_sap_shim.c \
	net/if_lane/le_disp.c \
	net/if_lane/lec_arp.c \
	net/if_lane/lec_ctrl.c \
	net/if_lane/lec_data.c \
	net/if_lane/lec_upper.c \
	net/if_lane/map.c \
	net/if_lane/svc_info.c \
	net/if_lane/utl.c \
	net/if_lane/utl_os.c \
	net/if_lane/g_event.c \
	atm/ifmp/dunix/ipsh_dunix.c \
	atm/ifmp/host/ipshost.c \
	atm/cmm/atmtm/atmtm.c \
	atm/uni3.x/atmuni/atmuni_addrmgr.c \
	atm/uni3.x/atmuni/atmuni_connect.c \
	atm/uni3.x/atmuni/atmuni_data.c \
	atm/uni3.x/atmuni/atmuni_devmanip.c \
	atm/uni3.x/atmuni/atmuni_except.c \
	atm/uni3.x/atmuni/atmuni_ilmi.c \
	atm/uni3.x/atmuni/atmuni_loader.c \
	atm/uni3.x/atmuni/atmuni_mmi.c \
	atm/uni3.x/atmuni/atmuni_receive.c \
	atm/uni3.x/atmuni/atmuni_sig.c \
	atm/uni3.x/atmuni/atmuni_sigstubs.c \
	atm/uni3.x/atmuni/atmuni_unimanip.c \
	atm/uni3.x/ilmi/ilmi_manage.c \
	atm/uni3.x/ilmi/ilmi_loader.c \
	atm/uni3.x/ilmi/ilmi_data.c \
	atm/uni3.x/ilmi/ilmi_receive.c \
	atm/uni3.x/ilmi/agent.c \
	atm/uni3.x/ilmi/codec.c \
	atm/uni3.x/ilmi/dec_atm.c \
	atm/uni3.x/ilmi/fsm.c \
	atm/uni3.x/ilmi/netpref.c \
	atm/uni3.x/ilmi/system.c \
	atm/uni3.x/cmmintf/atmsig_manage.c \
	atm/uni3.x/cmmintf/atmsig_loader.c \
	atm/uni3.x/cmmintf/atmsig_cmm_callbacks.c \
	atm/uni3.x/cmmintf/atmsig_qsaalrx.c \
	atm/uni3.x/cmmintf/atmsig_mainloop.c \
	atm/uni3.x/cmmintf/atmsig_receive.c \
	atm/uni3.x/cmmintf/atmsig_data.c \
	atm/uni3.x/cmmintf/atmsig_ies.c \
	atm/uni3.x/cmmintf/atmsig_status.c \
	atm/uni3.x/cmmintf/atmsig_add.c \
	atm/uni3.x/cmmintf/atmsig_drop.c \
	atm/uni3.x/cmmintf/atmsig_release.c \
	atm/uni3.x/cmmintf/atmsig_restart.c \
	atm/uni3.x/cmmintf/atmsig_callrefs.c \
	atm/uni3.x/cmmintf/atmsig_misc.c \
	atm/uni3.x/cmmintf/atmsig_setup.c \
	atm/uni3.x/cmmintf/atmsig_addrman.c \
	atm/uni3.x/cmmintf/atmsig_trill_as.c \
	atm/uni3.x/common/aal.c \
	atm/uni3.x/common/asd.c \
	atm/uni3.x/common/asi.c \
	atm/uni3.x/common/cm_lib.c \
	atm/uni3.x/common/las.c \
	atm/uni3.x/common/cm_atm.c \
	atm/uni3.x/common/cm_bdy5.c \
	atm/uni3.x/common/cm_gen.c \
	atm/uni3.x/common/cm_hash.c \
	atm/uni3.x/common/ss_ptsp.c \
	atm/uni3.x/q93b/am_bdy1.c \
	atm/uni3.x/q93b/am_bdy2.c \
	atm/uni3.x/q93b/am_bdy3.c \
	atm/uni3.x/q93b/am_bdy4.c \
	atm/uni3.x/q93b/am_bdy5.c \
	atm/uni3.x/q93b/am_db1.c \
	atm/uni3.x/q93b/am_db2.c \
	atm/uni3.x/q93b/am_id.c \
	atm/uni3.x/q93b/am_ex_pt.c \
	atm/uni3.x/q93b/am_ptli.c \
	atm/uni3.x/q93b/am_mf.c \
	atm/uni3.x/q93b/am_ptmi.c \
	atm/uni3.x/qsaal/as_bdy1.c \
	atm/uni3.x/qsaal/as_bdy2.c \
	atm/uni3.x/qsaal/as_bdy3.c \
	atm/uni3.x/qsaal/as_bdy4.c \
	atm/uni3.x/qsaal/as_bdy5.c \
	atm/uni3.x/qsaal/as_bdy6.c \
	atm/uni3.x/qsaal/as_ex_pt.c \
	atm/uni3.x/qsaal/as_id.c \
	atm/uni3.x/qsaal/as_ptui.c \
	atm/uni3.x/qsaal/as_ptmi.c \
	atm/uni3.x/lm/lm.c 

CFILES2=\
	atm/uni3.x/lm/smambdy1.c \
	atm/uni3.x/lm/smasbdy1.c \
	arch/alpha/hal/bparm_cfg.c \
	lat/engine/aclchk.c \
	lat/engine/aclclr.c \
	lat/engine/aclcmp.c \
	lat/engine/aclrep.c \
	lat/engine/aclset.c \
	lat/engine/adpcre.c \
	lat/engine/adpdel.c \
	lat/engine/adplist.c \
	lat/engine/adpsh.c \
	lat/engine/asclro.c \
	lat/engine/asclrp.c \
	lat/engine/ascre.c \
	lat/engine/asdel.c \
	lat/engine/aslist.c \
	lat/engine/asmsg.c \
	lat/engine/asrset.c \
	lat/engine/assetf.c \
	lat/engine/asseti.c \
	lat/engine/asseto.c \
	lat/engine/assetp.c \
	lat/engine/asshow.c \
	lat/engine/cbabo.c \
	lat/engine/cbcre.c \
	lat/engine/cbdel.c \
	lat/engine/cbhalt.c \
	lat/engine/cbhrun.c \
	lat/engine/cbhstr.c \
	lat/engine/cborun.c \
	lat/engine/cbostr.c \
	lat/engine/cbrout.c \
	lat/engine/cbrxmt.c \
	lat/engine/cbsrun.c \
	lat/engine/cbsstr.c \
	lat/engine/dbchgc.c \
	lat/engine/dbrepb.c \
	lat/engine/dbrepc.c \
	lat/engine/dbreps.c \
	lat/engine/dbsetc.c \
	lat/engine/dbsetm.c \
	lat/engine/exerr.c \
	lat/engine/hicre.c \
	lat/engine/hidel.c \
	lat/engine/hiecan.c \
	lat/engine/hierpt.c \
	lat/engine/hifind.c \
	lat/engine/hihra.c \
	lat/engine/hihri.c \
	lat/engine/hihsts.c \
	lat/engine/hiinit.c \
	lat/engine/hiocmd.c \
	lat/engine/hiopen.c \
	lat/engine/hiora.c \
	lat/engine/hioreq.c \
	lat/engine/hiori.c \
	lat/engine/hiosi.c \
	lat/engine/hiosts.c \
	lat/engine/hiqrpt.c \
	lat/engine/hiqsts.c \
	lat/engine/hirej.c \
	lat/engine/hiscmd.c \
	lat/engine/hises.c \
	lat/engine/hissi.c \
	lat/engine/histr.c \
	lat/engine/hsrset.c \
	lat/engine/hszero.c \
	lat/engine/hxsts.c \
	lat/engine/idlchk.c \
	lat/engine/idlclr.c \
	lat/engine/idlcmp.c \
	lat/engine/idlset.c \
	lat/engine/ifchk.c \
	lat/engine/ifmsg.c \
	lat/engine/latcom.c \
	lat/engine/lscre.c \
	lat/engine/lsdel.c \
	lat/engine/lsdups.c \
	lat/engine/lslist.c \
	lat/engine/lslook.c \
	lat/engine/lslsth.c \
	lat/engine/lsmsg.c \
	lat/engine/lsperm.c \
	lat/engine/lsrem.c \
	lat/engine/lsrset.c \
	lat/engine/lsscan.c \
	lat/engine/lsshow.c \
	lat/engine/lstmo.c \
	lat/engine/ndcre.c \
	lat/engine/nddel.c \
	lat/engine/ndfail.c \
	lat/engine/ndlist.c \
	lat/engine/ndpur.c \
	lat/engine/ndshow.c \
	lat/engine/ndzero.c \
	lat/engine/obclon.c \
	lat/engine/obcre.c \
	lat/engine/obdel.c \
	lat/engine/obfind.c \
	lat/engine/oblist.c \
	lat/engine/obrel.c \
	lat/engine/obren.c \
	lat/engine/obrset.c \
	lat/engine/obsetf.c \
	lat/engine/obshow.c \
	lat/engine/oxses.c \
	lat/engine/qrcre.c \
	lat/engine/qrdel.c \
	lat/engine/qrfind.c \
	lat/engine/qrlist.c \
	lat/engine/qrscan.c \
	lat/engine/sb1inp.c \
	lat/engine/sb1out.c \
	lat/engine/sbacc.c \
	lat/engine/sbcre.c \
	lat/engine/sbdel.c \
	lat/engine/sbdups.c \
	lat/engine/sbfind.c \
	lat/engine/sbopen.c \
	lat/engine/sbrej.c \
	lat/engine/sbria.c \
	lat/engine/sbsig.c \
	lat/engine/sbstop.c \
	lat/engine/sbstr.c \
	lat/engine/ticelp.c \
	lat/engine/tocelp.c \
	lat/engine/vcshow.c \
	lat/streams/axrate.c \
	lat/streams/grpret.c \
	lat/streams/hxses.c \
	lat/streams/ixerr.c \
	lat/streams/latadpsubs.c \
	lat/streams/latclose.c \
	lat/streams/latdefsvc.c \
	lat/streams/lathashsubs.c \
	lat/streams/latlioc.c \
	lat/streams/latlog.c \
	lat/streams/latlrput.c \
	lat/streams/latlrsrv.c \
	lat/streams/latmain.c \
	lat/streams/latopen.c \
	lat/streams/latsub.c \
	lat/streams/lattimer.c \
	lat/streams/lattioc.c \
	lat/streams/lattli.c \
	lat/streams/latursrv.c \
	lat/streams/latuwput.c \
	lat/streams/ofmsg.c \
	lat/streams/strchk.c \
	lat/streams/strcvt.c \
	lat/streams/strdif.c \
	lat/streams/strequ.c \
	lat/streams/strinp.c \
	lat/streams/strmov.c \
	lat/streams/strret.c \
	lat/streams/sxgetc.c \
	lat/streams/sxputc.c \
	lat/streams/sxses.c \
	lat/streams/sxsig.c \
	lvm/lv_block.c \
	lvm/lv_config.c \
	lvm/lv_defect.c \
	lvm/lv_ioctls.c \
	lvm/lv_kdb.c \
	lvm/lv_lvsubr.c \
	lvm/lv_mircons.c \
	lvm/lv_pbuf.c \
	lvm/lv_phys.c \
	lvm/lv_schedule.c \
	lvm/lv_strategy.c \
	lvm/lv_subr.c \
	lvm/lv_syscalls.c \
	lvm/lv_vgda.c \
	lvm/lv_vgsa.c \
	msfs/bs/bs_access.c \
	msfs/bs/bs_bitfile_sets.c \
	msfs/bs/bs_bmt_util.c \
	msfs/bs/bs_buffer2.c \
	msfs/bs/bs_copy.c \
	msfs/bs/bs_create.c \
	msfs/bs/bs_delete.c \
	msfs/bs/bs_domain.c \
	msfs/bs/bs_errlst.c \
	msfs/bs/bs_extents.c \
	msfs/bs/bs_init.c \
	msfs/bs/bs_inmem_map.c \
	msfs/bs/bs_migrate.c \
	msfs/bs/bs_misc.c \
	msfs/bs/bs_msg_queue.c \
	msfs/bs/bs_params.c \
	msfs/bs/bs_qio.c \
	msfs/bs/bs_sbm.c \
	msfs/bs/bs_service_class.c \
	msfs/bs/bs_shadow.c \
	msfs/bs/bs_stg.c \
	msfs/bs/bs_stripe.c \
	msfs/bs/bs_tagdir.c \
	msfs/bs/ftx_recovery.c \
	msfs/bs/ftx_routines.c \
	msfs/bs/ms_generic_locks.c \
	msfs/bs/ms_logger.c \
	msfs/bs/ms_mode.c \
	msfs/bs/ms_privates.c \
	msfs/bs/ms_public.c \
	msfs/fs/fs_create.c \
	msfs/fs/fs_dir_init.c \
	msfs/fs/fs_dir_lookup.c \
	msfs/fs/fs_file_sets.c \
	msfs/fs/fs_quota.c \
	msfs/fs/fs_read_write.c \
	msfs/mss/mss_common.c \
	msfs/mss/mss_entry.c \
	msfs/mss/mss_fs.c \
	msfs/mss/mss_lock.c \
	msfs/mss/mss_log.c \
	msfs/mss/mss_misc.c \
	msfs/mss/mss_pqd.c \
	msfs/mss/mss_send.c \
	msfs/mss/mss_space.c \
	msfs/mss/mss_syscall.c \
	msfs/mss/ter_inmem_map.c \
	msfs/mss/ter_ondisk_map.c \
	msfs/mss/ter_stg.c \
	msfs/osf/msfs_cfg.c \
	msfs/osf/msfs_config.c \
	msfs/osf/msfs_io.c \
	msfs/osf/msfs_lookup.c \
	msfs/osf/msfs_misc.c \
	msfs/osf/msfs_proplist.c \
	msfs/osf/msfs_vfsops.c \
	msfs/osf/msfs_vnops.c \
	net/bpf_filter.c \
	net/pfilt.c \
	net/pfilt_bpf.c \
	net/net_cfg.c \
	net/raw_cb.c \
	net/raw_usrreq.c \
	net/route.c \
	net/netrain_cfg.c \
	net/netrain.c \
	net/if_nr.c \
	net/if_ethersubr.c \
	netinet/if_ether.c \
	net/if_loop.c \
	net/if_sl.c \
	streamsm/ppp_init.c \
	streamsm/ppp_if.c \
	streamsm/ppp_async.c \
	streamsm/ppp_comp.c \
	streamsm/vjcompress.c \
	streamsm/bsd_comp.c \
	netinet/inet_cfg.c \
	netinet/igmp.c \
	netinet/in.c \
	netinet/in_pcb.c \
	netinet/in_proto.c \
	netinet/ip_icmp.c \
	netinet/ip_input.c \
	netinet/ip_mroute.c \
	netinet/ip_output.c \
	netinet/ip_screen.c \
	netinet/pmtu.c \
	netinet/raw_ip.c \
	netinet/tcp_debug.c \
	netinet/tcp_input.c \
	netinet/tcp_output.c \
	netinet/tcp_subr.c \
	netinet/tcp_timer.c \
	netinet/tcp_usrreq.c \
	netinet/udp_usrreq.c \
	nfs/nfs3_vfsops.c \
	nfs/nfs3_vnodeops.c \
	nfs/nfs3_xdr.c \
	nfs/nfs_client.c \
	nfs/nfs_common.c \
	nfs/nfs_config.c \
	nfs/nfs_dump.c \
	nfs/nfs_subr.c \
	nfs/nfs_vfsops.c \
	nfs/nfs_vnodeops.c \
	nfs/nfs_xdr.c \
	nfs/prop_xdr.c \
	rpc/auth_kern.c \
	rpc/authunix_prot.c \
	rpc/clnt_kudp.c \
	rpc/clnt_ktcp.c \
	rpc/clnt_perror.c \
	rpc/kudp_fastsend.c \
	rpc/pmap_kgetport.c \
	rpc/pmap_prot.c \
	rpc/pmap_rmt.c \
	rpc/rpc_callmsg.c 

CFILES3=\
	rpc/rpc_prot.c \
	rpc/subr_kudp.c \
	rpc/svc.c \
	rpc/svc_auth.c \
	rpc/svc_auth_unix.c \
	rpc/svc_kudp.c \
	rpc/svc_ktcp.c \
	rpc/xdr.c \
	rpc/xdr_array.c \
	rpc/xdr_mbuf.c \
	rpc/xdr_mem.c \
	rpc/xdr_reference.c \
	rpcsvc/bootparam_xdr.c \
	rpcsvc/mountxdr.c \
	klm/klm_kprot.c \
	klm/klm_lockmgr.c \
	nfs/nfs_server.c \
	nfs/nfs3_server.c \
	procfs/procfs_subrs.c \
	procfs/procfs_vfsops.c \
	procfs/procfs_vnops.c \
	procfs/procfs_ioctl.c \
	procfs/procfs_vfsops_stubs.c \
	procfs/procfs_subrs_stubs.c \
	procfs/procfs_vnops_stubs.c \
	bsd/snmpinfo.c \
	streams/str_memory.c \
	streams/nd.c \
	streams/str_cfg.c \
	streams/str_env.c \
	streams/str_filesys.c \
	streams/str_init.c \
	streams/str_modsw.c \
	streams/str_osr.c \
	streams/str_runq.c \
	streams/str_scalls.c \
	streams/str_shead.c \
	streams/str_subr.c \
	streams/str_support.c \
	streams/str_synch.c \
	streams/str_tty.c \
	streams/str_util.c \
	streams/str_weld.c \
	streams/str_debug.c \
	streamsm/dlb.c \
	data/dlpi_data.c \
	streamsm/dlpi/dl.c \
	streamsm/dlpi/dlhash.c \
	streamsm/dlpi/dlioctl.c \
	streamsm/dlpi/dlprim.c \
	streamsm/dlpi/dlproc.c \
	streamsm/dlpi/dltimer.c \
	streamsm/dlpi/dlutil.c \
	streamsm/ifnet.c \
	streamsm/kinfo.c \
	streamsm/log.c \
	streamsm/sad.c \
	streamsm/standard.c \
	streamsm/svvs.c \
	streamsm/timod.c \
	streamsm/tirdwr.c \
	tty/ldtty.c \
	tty/ldtty_compat.c \
	tty/ldtty_euc.c \
	streamsm/xtiso.c \
	tty/pty.c \
	ufs/mfs_vfsops.c \
	ufs/mfs_vnops.c \
	ufs/ufs_alloc.c \
	ufs/ufs_bmap.c \
	ufs/ufs_cfg.c \
	ufs/ufs_disksubr.c \
	ufs/ufs_inode.c \
	ufs/ufs_lookup.c \
	ufs/ufs_physio.c \
	ufs/ufs_proplist.c \
	ufs/ufs_subr.c \
	ufs/ufs_tables.c \
	ufs/ufs_vfsops.c \
	ufs/ufs_vnops.c \
	ufs/ufs_quota.c \
	bsd/uipc_proto.c \
	bsd/uipc_usrreq.c \
	vfs/dead_vfsops.c \
	vfs/dead_vnops.c \
	vfs/fifo_vnops.c \
	vfs/spec_vnops.c \
	vfs/vfs_bio.c \
	vfs/vfs_cache.c \
	vfs/vfs_cfg.c \
	vfs/vfs_flock.c \
	vfs/vfs_lookup.c \
	vfs/vfs_subr.c \
	vfs/vfs_syscalls.c \
	vfs/vfs_ubc.c \
	vfs/vfs_vnops.c \
	vm/k_mape_inv.c \
	vm/k_mape_io.c \
	vm/k_mape_mem.c \
	vm/u_mape_anon.c \
	vm/u_mape_dev.c \
	vm/u_mape_seg.c \
	vm/u_mape_shm.c \
	vm/u_mape_ssm.c \
	vm/u_mape_vp.c \
	vm/vm_anon.c \
	vm/vm_anonpage.c \
	vm/vm_cfg.c \
	vm/vm_cmap.c \
	vm/vm_fault.c \
	vm/vm_kern.c \
	vm/vm_kmap.c \
	vm/vm_map.c \
	vm/vm_object.c \
	vm/vm_pagelru.c \
	vm/vm_resident.c \
	vm/vm_subr.c \
	vm/vm_swap.c \
	vm/vm_umap.c \
	vm/vm_unix.c \
	vm/vm_user.c \
	vm/vm_vlock.c \
	vm/vpage.c \
	bsd/kern_lmf.c \
	tty/pckt.c \
	bsd/kern_ntptime.c \
	bsd/memlog.c \
	bsd/subr_mcount.c \
	bsd/tty_pty.c \
	dec/prf/prf.c \
	kern/callout_statistics.c \
	kern/ipc_statistics.c \
	net/gw_screen.c \
	dec/pwrmgr/pwrmgr.c \
	dec/sec/kern_audit.c \
	dec/sec/kern_auditcalls.c \
	dec/sec/kern_auditdev.c \
	sec/sec_calls.c \
	sec/sec_socket.c \
	sec/sec_stream.c \
	sec/sec_driver.c \
	sec/sec_mld.c \
	sec/spd_pacl.c \
	sec/dce_acl_stubs.c \
	sec/spd_cache.c \
	sec/acl_stubs.c \
	sec/spd_mac.c \
	sec/spd_misc.c \
	svr4/kern_memcntl.c \
	svr4/kern_swapctl.c \
	./rt_init_sysent.c \
	./rt_syscalls.c \
	./soe_two_init_sysent.c \
	./soe_two_syscalls.c \
	./svid_three_init_sysent.c \
	./svid_three_syscalls.c \
	./svr_four_init_sysent.c \
	./svr_four_syscalls.c \
	./sysv_init_sysent.c \
	./sysv_syscalls.c \
	kmod/rt_hab/rt_hab_cfg.c \
	kmod/soe2_hab/soe_two_cfg.c \
	kmod/svid3_hab/svid_three_cfg.c \
	kmod/svr4_hab/svr_four_cfg.c \
	kmod/sysv_hab/sysv_hab_cfg.c \
	kmod/sysv_hab/vfs_svid2calls.c \
	bsd/init_main.c \
	kern/ipc_globals.c \
	vm/vm_init.c \
	arch/alpha/alpha_exception.c \
	arch/alpha/alpha_init.c \
	arch/alpha/alpha_ptrace.c \
	arch/alpha/alpha_signal.c \
	arch/alpha/clock.c \
	arch/alpha/coff_subr.c \
	arch/alpha/copy.c \
	arch/alpha/cpu.c \
	arch/alpha/crc.c \
	arch/alpha/dumpsys.c \
	arch/alpha/exec_config.c \
	arch/alpha/exec_subr.c \
	arch/alpha/in_cksum.c \
	arch/alpha/intr.c \
	arch/alpha/kernargs.c \
	arch/alpha/machdep.c \
	arch/alpha/mem.c \
	arch/alpha/micro_time.c \
	arch/alpha/pfm.c \
	arch/alpha/ovbcopy.c \
	arch/alpha/pcb.c \
	arch/alpha/pmap.c \
	arch/alpha/pmap_debug.c \
	arch/alpha/pmap_update.c \
	arch/alpha/pmap_init.c \
	arch/alpha/prom.c \
	arch/alpha/startup.c \
	arch/alpha/super.c \
	arch/alpha/syscall_trap.c \
	arch/alpha/trap.c \
	arch/alpha/softfp.c \
	arch/alpha/ieee_float_math.c \
	arch/alpha/64bit_math.c \
	arch/alpha/bootio.c \
	arch/alpha/bootio_subrs.c \
	dec/sas/bootio_net.c \
	dec/sas/io.c \
	dec/sas/sys.c \
	dec/sas/sys_advfs.c \
	dec/sas/sys_cdfs.c \
	arch/alpha/fp/fp_ieee.c \
	arch/alpha/fp/fp_ieee_handler.c \
	arch/alpha/fp/fp_ascii.c \
	arch/alpha/fp/fp_result.c \
	arch/alpha/fp/fp_scale.c \
	arch/alpha/fp/fp_trigger.c \
	arch/alpha/fp/fp_tables.c \
	arch/alpha/fp/fp_emulator.c \
	arch/alpha/ul.c \
	arch/alpha/vm_machdep.c \
	arch/alpha/hal/autoconf.c \
	arch/alpha/hal/cons_sw.c \
	arch/alpha/hal/console.c \
	arch/alpha/hal/cpusw.c \
	arch/alpha/hal/platform_switch.c \
	arch/alpha/hal/io_access.c \
	arch/alpha/hal/kn15aa_mult.c \
	arch/alpha/hal/kn15aa.c \
	arch/alpha/hal/kn16aa_mult.c \
	arch/alpha/hal/kn16aa.c \
	arch/alpha/hal/kn430_mult.c \
	arch/alpha/hal/kn430.c \
	arch/alpha/hal/dec4000_cons.c \
	arch/alpha/hal/kn7aa_mult.c \
	arch/alpha/hal/kn7aa.c \
	io/dec/lsb/lsbinit.c \
	io/dec/lsb/lsb_iop.c \
	arch/alpha/hal/kn8ae_mult.c \
	arch/alpha/hal/kn8ae.c \
	io/dec/lsb/tlsbinit.c \
	io/dec/lsb/tlsb_iop.c \
	arch/alpha/hal/dc21171_mult.c \
	arch/alpha/hal/dc21171.c \
	arch/alpha/hal/kn121_mult.c \
	arch/alpha/hal/kn121.c \
	arch/alpha/hal/kn25_mult.c \
	arch/alpha/hal/kn25.c \
	arch/alpha/hal/kn450_mult.c \
	arch/alpha/hal/kn450.c \
	arch/alpha/hal/cbus2_pci_mult.c \
	arch/alpha/hal/cbus2_pci.c \
	arch/alpha/hal/kn470_mult.c \
	arch/alpha/hal/kn470.c \
	arch/alpha/hal/kn20aa_mult.c \
	arch/alpha/hal/kn20aa.c \
	arch/alpha/hal/kn22a_mult.c \
	arch/alpha/hal/kn22a.c \
	arch/alpha/hal/ebp10_mult.c \
	arch/alpha/hal/ebp10.c \
	arch/alpha/hal/eb64p_mult.c \
	arch/alpha/hal/eb64p.c \
	arch/alpha/hal/eb66_mult.c \
	arch/alpha/hal/eb66.c \
	arch/alpha/hal/eb164_mult.c \
	arch/alpha/hal/eb164.c \
	arch/alpha/hal/ebv10_mult.c \
	arch/alpha/hal/ebv10.c \
	arch/alpha/hal/ds1386clock_mult.c \
	arch/alpha/hal/ds1386clock.c \
	arch/alpha/hal/ebv14_mult.c \
	arch/alpha/hal/ebv14.c \
	arch/alpha/hal/ebv16_mult.c \
	arch/alpha/hal/ebv16.c \
	arch/alpha/hal/ebm10_mult.c \
	arch/alpha/hal/ebm10.c \
	arch/alpha/hal/ebm20_mult.c \
	arch/alpha/hal/ebm20.c \
	arch/alpha/hal/dec7000_cons.c \
	arch/alpha/hal/ruby_common_mult.c \
	arch/alpha/hal/ruby_common.c \
	arch/alpha/hal/kn300_mult.c \
	arch/alpha/hal/kn300.c \
	arch/alpha/hal/kn600_mult.c \
	arch/alpha/hal/kn600.c \
	arch/alpha/hal/ebm30_mult.c \
	arch/alpha/hal/ebm30.c \
	arch/alpha/hal/alphabook_mult.c \
	arch/alpha/hal/alphabook.c \
	arch/alpha/hal/mcbus.c \
	io/dec/pci/mcpcia_mult.c \
	io/dec/pci/mcpcia.c \
	arch/alpha/hal/dc104x.c \
	arch/alpha/hal/dc104x_mult.c \
	arch/alpha/hal/linear_io_access.c 

CFILES4=\
	arch/alpha/hal/linear_io_access_mult.c \
	arch/alpha/hal/hal_lmf.c \
	arch/alpha/hal/hal_sysinfo.c \
	arch/alpha/hal/pc_bell_mult.c \
	arch/alpha/hal/pc_bell.c \
	arch/alpha/hal/sio.c \
	arch/alpha/hal/dma_direct_map.c \
	arch/alpha/hal/82357_pic.c \
	arch/alpha/hal/mc146818clock_mult.c \
	arch/alpha/hal/mc146818clock.c \
	arch/alpha/hal/lca_mult.c \
	arch/alpha/hal/lca.c \
	arch/alpha/hal/apecs_mult.c \
	arch/alpha/hal/apecs.c \
	io/dec/vme/ebv10_vme.c \
	io/dec/vme/univ_vme.c \
	arch/alpha/kdebug_ace_cons.c \
	arch/alpha/kdebug_misc.c \
	arch/alpha/kdebug_cobra_cons.c \
	arch/alpha/kdebug_gbus_cons.c \
	arch/alpha/kdebug_scc_cons.c \
	arch/alpha/kdebug_iscc_cons.c \
	arch/alpha/db_alpha_aout.c \
	arch/alpha/db_alpha_inst.c \
	arch/alpha/db_alpha_sym.c \
	arch/alpha/db_commands.c \
	arch/alpha/db_disasm.c \
	arch/alpha/db_interface.c \
	arch/alpha/db_trace.c \
	arch/alpha/devz.c \
	io/common/driver_support.c \
	io/common/ldbl_driver_support.c \
	io/common/ldbl_controller_support.c \
	io/common/stanza_resolver.c \
	io/common/topology.c \
	io/common/handler.c \
	io/common/tty_def.c \
	io/common/io_resource.c \
	io/dec/lsb/lsbmem_mult.c \
	io/dec/lsb/lsbmem.c \
	io/common/cma_dd.c \
	io/cam/cam_disk.c \
	io/cam/cam_tape.c \
	io/cam/cam_logger.c \
	io/cam/cam_special.c \
	io/cam/ccfg.c \
	io/cam/camdb.c \
	io/cam/pdrv_common.c \
	io/cam/special_audio.c \
	io/cam/special_direct.c \
	io/cam/special_generic.c \
	io/cam/special_sequential.c \
	io/cam/uagt.c \
	io/cam/xpt.c \
	io/cam/dme_null.c \
	io/cam/sim_common.c \
	io/cam/cam_eei.c \
	io/cam/cam_rci.c \
	io/cam/sim_xpt.c \
	io/cam/sim_htm.c \
	io/cam/sim_as.c \
	io/cam/sim_error.c \
	io/cam/sim_sched.c \
	io/cam/sim_sm.c \
	io/cam/sim_target.c \
	io/cam/dme_tcds_94_dma.c \
	io/cam/tcds_adapt.c \
	io/cam/dme_turbo_94_ram.c \
	io/cam/dme_common.c \
	io/cam/sim_94_fast.c \
	io/cam/sim_94.c \
	io/cam/sim_kn02.c \
	io/cam/aha1740.c \
	io/cam/ata/sim_ata.c \
	io/cam/ata/sim_ata_acer.c \
	io/cam/ata/sim_ata_cmd.c \
	io/cam/ata/sim_ata_cypress.c \
	io/cam/ata/sim_ata_datatech.c \
	io/cam/ata/sim_ata_dma.c \
	io/cam/ata/sim_ata_symphony.c \
	io/cam/ata/sim_ata_unknown.c \
	io/cam/qlogic/isp1020.c \
	io/cam/iti/itpsa.c \
	io/cam/iti/itpsacfg.c \
	io/cam/iti/itpsahtm.c \
	io/cam/spo/sim_pza.c \
	io/cam/spo/sim_kztsa.c \
	io/cam/spo/simport.c \
	io/cam/spo/simport_htm.c \
	io/cam/spo/simport_dme.c \
	io/cam/spo/simport_subr.c \
	io/cam/siop/psiop.c \
	io/cam/siop/pci/psiop_pci.c \
	io/cam/siop/siop.c \
	io/cam/siop/kn430/siop_kn430.c \
	io/cam/xza/skz_config.c \
	io/cam/xza/skz_main.c \
	io/cam/xza/skz_dme.c \
	io/cam/xza/skz_error.c \
	io/cam/xza/skz_sched.c \
	io/cam/xza/skz_debug.c \
	io/cam/xza/skz_nport.c \
	io/cam/xza/skz_diag.c \
	io/cam/xza/skz_target.c \
	io/cam/mips_dummy.c \
	io/dec/lsb/lsb_common.c \
	io/dec/fbus/fbus.c \
	io/dec/fbus/fbus_loadable.c \
	io/dec/fbus/flag.c \
	io/dec/mbox/mbox.c \
	io/dec/ibus/ibus.c \
	io/dec/xmi/xmiinit.c \
	io/dec/xmi/xlamb.c \
	io/dec/netif/if_xna.c \
	io/dec/netif/if_mfa.c \
	io/dec/tc/tc.c \
	io/dec/tc/tc_loadable.c \
	io/dec/tc/scc.c \
	io/dec/tc/nvtc.c \
	io/dec/tc/amd79c30.c \
	io/dec/tc/amd79c30_dummy.c \
	io/dec/tc/amd79c30_hdlc.c \
	io/dec/eisa/eisa.c \
	io/dec/eisa/eisa_cnfg.c \
	arch/alpha/hal/isp.c \
	io/dec/i2c/i2c.c \
	io/dec/eisa/iscc.c \
	io/dec/eisa/isa.c \
	io/dec/eisa/gpc.c \
	io/dec/eisa/ace.c \
	io/dec/eisa/lp.c \
	io/dec/eisa/envram.c \
	io/dec/eisa/re_driver.c \
	io/dec/eisa/xcr_logger.c \
	io/dec/eisa/xcr_port.c \
	io/dec/pci/pci.c \
	arch/alpha/hal/dma_sg_map.c \
	arch/alpha/hal/shared_intr.c \
	io/dec/pci/pci_common_intr_handler.c \
	io/dec/pci/pnvram.c \
	io/dec/pci/mchan.c \
	io/dec/pci/pcia_mult.c \
	io/dec/pci/pcia.c \
	io/dec/pcmcia/pd6729.c \
	io/dec/pcmcia/pcic.c \
	io/dec/pcmcia/pcmcia_fnc.c \
	io/dec/pcmcia/pcmcia.c \
	io/dec/pcmcia/card_services.c \
	io/dec/pcmcia/card_config.c \
	io/dec/pcmcia/pcmcia_event.c \
	io/i2o/i2oexec.c \
	io/i2o/i2omsg.c \
	io/i2o/i2opcixport.c \
	io/i2o/i2o.c \
	io/i2o/i2o_bs.c \
	io/i2o/i2o_logger.c \
	io/dec/netif/if_ln.c \
	io/dec/netif/if_le.c \
	io/dec/netif/if_te.c \
	io/dec/netif/if_tu.c \
	io/dec/netif/if_fza.c \
	io/dec/netif/if_fta.c \
	io/dec/netif/if_tra.c \
	io/dec/netif/if_faa.c \
	io/dec/netif/if_vb.c \
	io/atm/drivers/otto/if_otto.c \
	io/atm/drivers/otto/if_otto_xilinx.c \
	io/atm/drivers/otto/if_ottodefs.c \
	io/atm/drivers/otto/otto_platform.c \
	io/atm/drivers/otto/otto_flow.c \
	io/atm/drivers/otto/otto_fakesnmp.c \
	io/atm/drivers/otto/aal5crc.c \
	io/atm/drivers/meteor/acr_tbl.c \
	io/atm/drivers/meteor/adap_sw.c \
	io/atm/drivers/meteor/fm.c \
	io/atm/drivers/meteor/if_lpa.c \
	io/atm/drivers/meteor/if_lpa_defs.c \
	io/atm/drivers/meteor/if_lpa_platform.c \
	io/atm/drivers/meteor/met_sw.c \
	io/dec/ci/ciconfig.c \
	io/dec/ci/cippd_error.c \
	io/dec/ci/cippd_event.c \
	io/dec/ci/cippd_pmaint.c \
	io/dec/ci/cippd_protocol.c \
	io/dec/ci/cippdvar.c \
	io/dec/gvp/gvp_block.c \
	io/dec/gvp/gvp_dg.c \
	io/dec/gvp/gvp_msg.c \
	io/dec/gvp/gvp_subr.c \
	io/dec/gvp/gvpvar.c \
	io/dec/np/np_block.c \
	io/dec/np/np_dg.c \
	io/dec/np/np_error.c \
	io/dec/np/np_init.c \
	io/dec/np/np_isr.c \
	io/dec/np/np_lpmaint.c \
	io/dec/np/np_msg.c \
	io/dec/np/np_subr.c \
	io/dec/np/npvar.c \
	io/dec/xmi/xminp.c \
	io/dec/scs/scs_block.c \
	io/dec/scs/scs_configdb.c \
	io/dec/scs/scs_conn.c \
	io/dec/scs/scs_dg.c \
	io/dec/scs/scs_error.c \
	io/dec/scs/scs_event.c \
	io/dec/scs/scs_info.c \
	io/dec/scs/scs_maint.c \
	io/dec/scs/scs_msg.c \
	io/dec/scs/scs_protocol.c \
	io/dec/scs/scs_subr.c \
	io/dec/scs/scsvar.c \
	io/dec/sysap/scs_directory.c \
	io/dec/sysap/mscp_tape.c \
	io/dec/sysap/mscp_disk.c \
	io/dec/sysap/mscp_bbr.c \
	io/dec/sysap/mscp_bbrstates.c \
	io/dec/sysap/mscp_config.c \
	io/dec/sysap/mscp_conpol.c \
	io/dec/sysap/mscp_diskvar.c \
	io/dec/sysap/mscp_subr.c \
	io/dec/sysap/mscp_var.c \
	io/dec/sysap/sysap_start.c \
	io/dec/uba/uba.c \
	io/dec/uba/uqserv.c \
	io/dec/uba/kdm.c \
	io/dec/fdi/fd.c \
	io/dec/fdi/fdcam.c \
	io/dec/ws/ws_driver.c \
	io/dec/ws/lk201.c \
	io/dec/ws/vsxxx.c \
	io/dec/ws/pcxal.c \
	io/dec/ws/pcxas.c \
	io/dec/ws/qfont.c \
	io/dec/ws/bt431.c \
	io/dec/ws/bt459.c \
	io/dec/ws/bt463.c \
	io/dec/ws/fb.c \
	io/dec/ws/vga_support.c \
	io/dec/ws/vga.c \
	io/dec/ws/ati.c \
	io/dec/ws/ati64.c \
	io/dec/ws/cirrus.c \
	io/dec/ws/qvision.c \
	io/dec/ws/s3v864.c \
	io/dec/ws/s3trio.c \
	io/dec/ws/wd.c \
	io/dec/ws/comet.c \
	io/dec/ws/tga.c \
	io/dec/ws/pmagro.c \
	io/dec/ws/sfb.c \
	io/dec/ws/pv.c \
	io/dec/ws/pvl.c \
	io/dec/ws/pvp.c \
	io/dec/presto/pr.c \
	io/dec/presto/presto_cfg.c \
	data/mbox_data.c \
	io/common/error_event.c \
	io/common/alloc_smt.c \
	net/trn_sr.c \
	vxvm/dki_osf.c \
	vxvm/plex/plex.c \
	vxvm/volspec/volspec.c \
	vxvm/vol/vol.c \
	vxvm/vol/volblog.c \
	vxvm/vol/volioctl.c \
	vxvm/vol/volklog.c \
	vxvm/vol/volted.c \
	vxvm/vol/volSpace.c \
	vxvm/vol/volroot.c \
	vxvm/vol/vol_cfg.c \
	ted/ted.c \
	ted/tedSpace.c \
	io/dec/vme/vba_generic.c \
	io/dec/vme/vba_tc.c \
	io/dec/vme/vba_pci.c \
	io/dec/vme/vba_dispatch.c \
	io/common/ddr.c \
	io/common/kio.c \
	io/common/kds.c \
	arch/alpha/hal/envmon.c \
	arch/alpha/hal/distint_cfg.c \
	io/dec/netif/if_el.c \
	io/dec/netif/lan_common.c \
	io/dec/eisa/hmc.c \
	io/dec/eisa/hmc_support.c \
	io/dec/pci/pci_isa_intr.c \
	arch/alpha/hal/ev6_common.c \
	io/dec/usb/usbd.c \
	io/dec/usb/usb_ohci.c \
	io/dec/usb/usb_hub.c \
	io/dec/usb/usb_hid.c \
	io/dec/usb/usb_keyboard.c \
	io/dec/usb/usb_mouse.c \
	io/dec/usb/usb_printer.c 

COBJS=ufs_quota.o kern_memcntl.o kern_swapctl.o rt_init_sysent.o \
	rt_syscalls.o soe_two_init_sysent.o soe_two_syscalls.o \
	svid_three_init_sysent.o svid_three_syscalls.o \
	svr_four_init_sysent.o svr_four_syscalls.o sysv_init_sysent.o \
	sysv_syscalls.o rt_hab_cfg.o soe_two_cfg.o svid_three_cfg.o \
	svr_four_cfg.o sysv_hab_cfg.o vfs_svid2calls.o init_main.o \
	ipc_globals.o vm_init.o alpha_init.o micro_time.o pmap_init.o \
	startup.o bootio_subrs.o bootio_net.o io.o sys.o sys_advfs.o \
	sys_cdfs.o platform_switch.o dec7000_cons.o dma_direct_map.o \
	devz.o lsb_common.o mbox_data.o trn_sr.o ted.o tedSpace.o 

SFILES=\
	arch/alpha/atomic_ops.s \
	arch/alpha/byte_swap.s \
	arch/alpha/context.s \
	arch/alpha/__divl.s \
	arch/alpha/__divq.s \
	arch/alpha/__divlu.s \
	arch/alpha/__divqu.s \
	arch/alpha/__reml.s \
	arch/alpha/__remq.s \
	arch/alpha/__remlu.s \
	arch/alpha/__remqu.s \
	arch/alpha/ots_div_alpha.s \
	arch/alpha/ots_div_data_alpha.s \
	arch/alpha/ots_extv_alpha.s \
	arch/alpha/ots_extv_vol_alpha.s \
	arch/alpha/ots_extzv_alpha.s \
	arch/alpha/ots_extzv_vol_alpha.s \
	arch/alpha/ots_insv_alpha.s \
	arch/alpha/ots_insv_vol_alpha.s \
	arch/alpha/ots_location_alpha.s \
	arch/alpha/ots_move_alpha.s \
	arch/alpha/ots_movem_alpha.s \
	arch/alpha/ots_fill_alpha.s \
	arch/alpha/ots_zero_alpha.s \
	arch/alpha/ots_translate_alpha.s \
	arch/alpha/ots_strcmp_eql_alpha.s \
	arch/alpha/ots_strcmp_eqlp_alpha.s \
	arch/alpha/ots_strcmp_leq_alpha.s \
	arch/alpha/ots_strcmp_leqp_alpha.s \
	arch/alpha/ots_strcmp_lss_alpha.s \
	arch/alpha/ots_strcmp_lssp_alpha.s \
	arch/alpha/entry.s \
	arch/alpha/fastcopy.s \
	arch/alpha/in_checksum.s \
	arch/alpha/locore.s \
	arch/alpha/lockprim.s \
	arch/alpha/addupc.s \
	arch/alpha/pal_lib.s \
	arch/alpha/scb.s \
	arch/alpha/spl.s \
	arch/alpha/fp/fp_emulate.s \
	arch/alpha/usercopy.s \
	arch/alpha/nofault.s \
	arch/alpha/mcount.s \
	arch/alpha/alpha_scrub.s \
	arch/alpha/lww.s \
	arch/alpha/lwu.s \
	arch/alpha/hal/eb64p_pallib.s \
	arch/alpha/hal/eb66_pallib.s \
	arch/alpha/hal/eb164_pallib.s \
	arch/alpha/hal/ebv10_pallib.s \
	arch/alpha/hal/ebv14_pallib.s \
	arch/alpha/hal/ebv16_pallib.s 

SOBJS=scb.o alpha_scrub.o 

ORDERED=init_main.o ipc_globals.o vm_init.o alpha_init.o pmap_init.o \
	startup.o scb.o bootio_subrs.o bootio_net.o io.o sys.o \
	sys_advfs.o sys_cdfs.o 

# 
#
# HISTORY
# 
#
# *****************************************************************
# *                                                               *
# *    Copyright (c) Digital Equipment Corporation, 1991, 1999    *
# *                                                               *
# *   All Rights Reserved.  Unpublished rights  reserved  under   *
# *   the copyright laws of the United States.                    *
# *                                                               *
# *   The software contained on this media  is  proprietary  to   *
# *   and  embodies  the  confidential  technology  of  Digital   *
# *   Equipment Corporation.  Possession, use,  duplication  or   *
# *   dissemination of the software and media is authorized only  *
# *   pursuant to a valid written license from Digital Equipment  *
# *   Corporation.                                                *
# *                                                               *
# *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
# *   by the U.S. Government is subject to restrictions  as  set  *
# *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
# *   or  in  FAR 52.227-19, as applicable.                       *
# *                                                               *
# *****************************************************************
# (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
# ALL RIGHTS RESERVED
#
#
# Mach Operating System
# Copyright (c) 1989 Carnegie-Mellon University
# All rights reserved.  The CMU software License Agreement
# specifies the terms and conditions for use and redistribution.
#
# OSF/1 Release 1.0
######################################################################
#BEGIN	Machine dependent Makefile fragment for ALPHA
######################################################################
#

#
# To build a Mach-O kernel define MACHO in the config file
#
KCC=${_CC_EXEC_PREFIX}cc

RM=		rm -f
GPSIZE=		${MACHO?0:4}

ACC_ENDIAN	= 
MCC_ENDIAN	= -EL
GCC_ENDIAN	=

ENDIAN=${${CC_SUITE}_ENDIAN}

#
# COPTS is recognized by config and massaged for profiling kernels
#
# cc options for most kernel sources
# CCNFLAGS - normal files
# CCFFLAGS - normal files allowed to do floating point
# CCDFLAGS - device drivers
# CCSFLAGS - swap*.c files
# CCASFLAGS - *.s files
# CCASFFLAGS - *.s files allowed to do floating point
# CCPFLAGS - profiling *.c files
# CCPASFLAGS - profiling *.s files
#
# CCOPTS may be set from the config file
# CDEBUGOPTS may be set from the config file
# ASOPTS may be set from the config file
# ENDIAN may be set from the config file
#
CCPROFOPT=-Wb,-p2
CCOPTS= -DLANGUAGE_C -std0

# need this for alpha
# afd add -v for debug
DEFINES= -D__alpha -Umips -UMIPS

CCNFLAGS= ${CPP_ONLY} -c -O2  ${ENDIAN} ${CCOPTS} ${COPTS} ${DEFINES}
CCFFLAGS= ${CPP_ONLY} -c -O2  ${ENDIAN} ${CCOPTS} ${CFOPTS} ${DEFINES}
CCDFLAGS= ${CPP_ONLY} -c -O0  ${ENDIAN} ${CCOPTS} ${COPTS} ${DEFINES}
CCSFLAGS= ${CPP_ONLY} -c -O2  ${ENDIAN} ${CCOPTS} ${COPTS} ${DEFINES}
CCASFLAGS= ${CPP_ONLY} -c -O0  ${ENDIAN} ${ASOPTS} ${COPTS} ${DEFINES} -DASSEMBLER
CCASFFLAGS= ${CPP_ONLY} -c -O0  -std ${ENDIAN} ${ASOPTS} ${CFOPTS} ${DEFINES} -DASSEMBLER
CCPFLAGS= -c  ${ENDIAN} ${CCOPTS} ${PCOPTS} ${PROFOPTS} ${DEFINES}
CCPASFLAGS= -c -O0  ${ENDIAN} ${ASOPTS} ${PCOPTS} ${PROFOPTS} ${DEFINES} -DASSEMBLER

DCC_NFLAGS= ${CPP_ONLY} -c -O2  ${ENDIAN} ${CCOPTS} ${DCOPTS} ${DEFINES}
DCC_FFLAGS= ${CPP_ONLY} -c -O2  ${ENDIAN} ${CCOPTS} ${DCFOPTS} ${DEFINES}
DCC_DFLAGS= ${CPP_ONLY} -c -O0  ${ENDIAN} ${CCOPTS} ${DCOPTS} ${DEFINES}
DCC_PFLAGS= -c  ${ENDIAN} ${CCOPTS} ${PCOPTS} ${PROFOPTS} ${DEFINES}

# Periodic checks should be made to make sure that the ".lita" section size
# remains in the comfort zone of under 48k.  Note that 64K is the maximum
# space available.

# text linked before scb.o disappears at the end of system initialization.
# files are listed as "ordered" to make them scavengable.

LDFLAGS= ${MACHO?:${ENDIAN} -G ${GPSIZE} -N} -w2 -O2 -T ${TEXTBASE} -e start ${LDOPTS}

# define volatile to be __volatile__ for gcc with -traditional
#
ACC_OPTS=-signed -Wg,-w2 ${WORKON?-D_USE_KERNEL_INTRINSICS:}
MCC_OPTS=
GCC_EXTRAS=-signed
GCC_OPTS=${NO_GCC?:${GCC_EXTRAS}}

${SOBJS}: assym.s

#DEPENDS=${NO_GCC?-G ${GPSIZE}:-MD -G ${GPSIZE}}
DEPENDS=-G ${GPSIZE}

SYSDEPS_PREFIX=libvmunix


libvmunix: vmunix.sys


######################################################################
#END	Machine dependent Makefile fragment for Alpha
######################################################################
CDEBUGOPTS=-g1
CCOMPRESS=-compress

CFILES=${CFILES1} ${CFILES2} ${CFILES3} ${CFILES4}

#
#
# echo the list of CFILES used to build the system
#
#
cfiles:
	@${ECHO} ${CFILES}

objfiles:
	@${ECHO} ${OBJS}
#
#
# export flags for use by kernel lib makefiles
#
#
asflags:
	@${ECHO} ${CCASFLAGS}

ccnflags:
	@${ECHO} ${CCNFLAGS}
#
#  Default rule used to build a *vmunix.sys configuration from the
#  object list and a particular *vmunix.swap module.  The *vmunix.swap
#  module is a normal object file compiled from the appropriate swap*.c
#  file and then copied to the *vmunix.swap name to trigger the full
#  kernel link using this default rule.
#

#
#  OBJSDEPS is the set of files (defined in the machine dependent
#  template if necessary) which all objects depend on (such as an
#  in-line assembler expansion filter
#

${OBJS}: ${OBJSDEPS}



#
#  This macro is replaced by three rules per configuration, plus a
#  final definition for the LOAD symbol consisting of all configuration
#  names and a dependency of "all" on this symbol (so that the
#  "default" rule above will build everything).  The three rules in
#  each configuration are:
#
#  - a *vmunix from *vmunix.sys dependency using the SYS_RULE_* rules,
#  - a *vmunix.swap from LDDEPS, swap*.o, and LDDEPS dependency that
#    simply copies the swap file to the target name, and
#  - a swap*.o from swap*.c and SWAPDEPS dependency using the C_RULE_* rules.
#

vmunix .ORDER: migfiles migdebugfiles vmunix.sys ${SYSDEPS}
vmunix.sys: ${PRELDDEPS} ${ORDERED} ${LOBJS} ${OBJS} ${LDDEPS}

LOAD= vmunix

SYSENT=rt_init_sysent.c soe_two_init_sysent.c \
	svid_three_init_sysent.c sysv_init_sysent.c init_sysent.c \
	svr_four_init_sysent.c 

all: ${LOAD}


scalls: ${SYSENT}

HOST_CC		= env - COMP_HOST_ROOT=/ COMP_TARGET_ROOT=/ /bin/cc -std0

ACC_GENASSYM_CFLAGS = -no_excpt
MCC_GENASSYM_CFLAGS =

GENASSYM_CFLAGS = -std0 -EL ${ALLOPTS} ${VOLATILE} ${${CC_SUITE}_GENASSYM_CFLAGS} -MD

CROSS_genassym.o: ${cpu}/genassym.c
	${CC} ${GENASSYM_CFLAGS} -c ${cpu}/genassym.c

NATIVE_genassym.o: ${cpu}/genassym.c
	${HOST_CC} ${GENASSYM_CFLAGS} -c ${cpu}/genassym.c

#
# Use macros to get the correct command to build and run genassym
# for multiarchitecutures and cross development environments.
# 

NATIVE_RUN_GENASSYM	= ./genassym > assym.s
CROSS_RUN_GENASSYM	= /bin/sh ${TARGET_EXEC_PREFIX}/run-genassym
RUN_GENASSYM		= ${${DEVENV}_RUN_GENASSYM}

CROSSENVPATH		= ${COMP_HOST_ROOT}/usr/lib/cmplrs/${cc_suite}

MIPS_NATIVE_GENASSYM	= ${HOST_CC} -std0 -EL -o genassym genassym.o
ALPHA_NATIVE_GENASSYM	= ${HOST_CC} -std0 -EL -non_shared -o genassym genassym.o
ALPHA_CROSS_GENASSYM	= ${LD} -o genassym -L -L${CROSSENVPATH} \
				${CROSSENVPATH}/crt0_sa.o genassym.o \
				${CROSSENVPATH}/libc_sa.a -N -T 20000000

GENASSYM 		= ${${TARGET_MACHINE}_${DEVENV}_GENASSYM}

assym.s: ${DEVENV}_genassym.o
	${GENASSYM}
	${RUN_GENASSYM}
	@${RM} genassym
	@${LN} -fs genassym.o ${DEVENV}_genassym.o

locore.o: assym.s ${LOCORE_HEADS}

#
#  Mach IPC-based interfaces
#

MACH_DEFSFILES=\
	mach/std_types.defs \
	mach/mach_types.defs \
	mach/mach.defs \
	mach/mach_host.defs \
	mach/exc.defs \
	mach/memory_object.defs \
	mach/memory_object_default.defs \
	mach/device_types.defs \
	mach/device.defs \
	mach/monitor.defs

MACH_GENFILES=\
	./mach/mach_server.c \
	./mach/mach_user_internal.h \
	./mach/mach_interface.h \
	./mach/mach_host_server.c \
	./mach/mach_host.h \
	./mach/memory_object_server.c \
	./mach/memory_object_user.c \
	./mach/memory_object_user.h \
	./mach/memory_object_default_server.c \
	./mach/memory_object_default_user.c \
	./mach/memory_object_default.h \
	./mach/exc_server.c \
	./mach/exc_user.c \
	./mach/exc.h \
	./mach/monitor_server.c \
	./mach/monitor.h

# These are defined to allow specific flags to be passed to mig generated
# C files.  ${@}_MIG check above adds in MIG_CFLAGS the compilation of
# these files.
#
exc_server.o_MIG =
exc_user.o_MIG = 
mach_host_server.o_MIG =
mach_server.o_MIG =
memory_object_default_user.o_MIG =
memory_object_user.o_MIG =
monitor_server.o_MIG =
mach_debug_server.o_MIG =
mach_user_internal.o_MIG =

MACH_MKFILE=	mach/Makefile

$(MACH_GENFILES) : migfiles

migfiles :: $(MACH_DEFSFILES) $(MACH_MKFILE)
	${RM} -rf ./mach
	${MKDIR} ./mach
	${CD} ./mach && \
	 ${MAKE} ${MFLAGS} VPATH=../../mach && ${TOUCH} ../migfiles

MACH_DEBUG_DEFSFILES=\
	mach_debug/mach_debug_types.defs \
	mach_debug/mach_debug.defs

MACH_DEBUG_GENFILES=\
	./mach_debug/mach_debug_server.c

MACH_DEBUG_MKFILE=	mach_debug/Makefile

$(MACH_DEBUG_GENFILES) : migdebugfiles

migdebugfiles :: $(MACH_DEBUG_DEFSFILES) $(MACH_DEBUG_MKFILE)
	${RM} -rf ./mach_debug
	${MKDIR} ./mach_debug
	${CD} ./mach_debug && \
	 ${MAKE} ${MFLAGS} VPATH=../../mach_debug && ${TOUCH} ../migdebugfiles

MIG_ALL_FILES = migfiles migdebugfiles

#
#  The default exit rule now brings the Makefile up to date, so it
#  shouldn't be necessary to execute this rule manually.
#

.EXIT:

DEPFILES= ${cpu}/Locore.c ${cpu}/genassym.c ${cpu}/swapgeneric.c \
		${LCFILES} assym.s ${CFILES} ${SFILES} 

LINTFILES=
LINTFLAGS= -n -whpCDPR -XE -Nn6000 -Nd8000 ${LINTOPTS}
LINTFILTER= ${GREP} -v 'struct/union .* never defined' | \
	    ${GREP} -v 'possible pointer alignment problem'

depend: makedep

makedep: makedepfiles
	${CAT} /dev/null >makedeptmp
	-(${CSPLIT} -ks -fmakedeptmp makedepfiles 100 {25} 1>/dev/null 2>&1; exit 0)
	-for i in makedeptmp?? ; do \
		(for f in `${CAT} $$i` ; do \
			${CAT} $$f >> makedeptmp ; \
		done) ; \
	done
	-${SED} -e 's+\.\./.*/src/kernel/++' \
		-e 's+/.*/src/kernel/++' \
		-e 's/	 */ /' \
		-e '/\.\.\/.*\.h/ b'  \
		-e 's+\.\./++' makedeptmp | \
		${SED} -e 's+^\(.*\)\.o:+\1.o \1.ln:+' | \
			${SORT} -u > makedep1
	${RM} makedeptmp*
	${AWK} ' { if ($$1 != prev) { \
			print rec; rec = $$0; prev = $$1; \
			if ( NR > 1 ) print "" \
		} else { \
			if (length(rec $$3) > 78) { \
				print rec; rec = $$0; \
			} else \
				rec = rec " " $$3 \
			} } \
		END { print rec } ' makedep1 > makedep
	${RM} makedep1 makedepfiles

makedepfiles:
	echo genassym > makedepfilestmp
	${CAT} /dev/null > makelinttmp
	-for i in ${cpu}/Locore.c \
			${LCFILES} ; do \
		echo "$$i `${BASENAME} $$i .c`">> makelinttmp; \
	done
	-for i in ${SFILES} ; do \
		${BASENAME} "$$i" .s >> makedepfilestmp; \
	done
	-for i in ${CFILES1} ; do \
		${BASENAME} "$$i" .c >> makedepfilestmp; \
		echo "$$i `${BASENAME} $$i .c`">> makelinttmp; \
	done
	-for i in ${CFILES2} ; do \
		${BASENAME} "$$i" .c >> makedepfilestmp; \
		echo "$$i `${BASENAME} $$i .c`">> makelinttmp; \
	done
	-for i in ${CFILES3} ; do \
		${BASENAME} "$$i" .c >> makedepfilestmp; \
		echo "$$i `${BASENAME} $$i .c`">> makelinttmp; \
	done
	-for i in ${CFILES4} ; do \
		${BASENAME} "$$i" .c >> makedepfilestmp; \
		echo "$$i `${BASENAME} $$i .c`">> makelinttmp; \
	done
	< makedepfilestmp sed "s/$$/.o.d/" > makedepfiles
	-${SED} -e 's+^.*/src/kernel/++' \
		-e 's+\.\./++' makelinttmp | ${SORT} +1 -u > makelintfiles
	${CAT} /dev/null > makelint
	${AWK} 'BEGIN { printf("\nLINTOBJS=") } \
		{ printf(" \\\n\t%s.ln", $$2) } \
		END { printf("\n\n") }' makelintfiles >> makelint
	${AWK} 'BEGIN { DOL=36; \
		printf("lint:\t%c{LINTOBJS}\n", DOL); \
		printf("\t%c{TOUCH} lint\n\n", DOL) }' /dev/null >> makelint
	${AWK} '{ DOL=36; \
		printf("%s.ln: %s\n", $$2, $$1); \
		printf("\t-%c{LINT} -c %c{LINTFLAGS} %s | \\\n", DOL, DOL, $$1); \
		printf("\t\t(%c{LINTFILTER} ; exit 0) > %s.lint 2>&1\n\n", DOL, $$2) }' \
		makelintfiles >> makelint
	${RM} makedepfilestmp makelinttmp makelintfiles

#
#  Permit manually forced checkout of modules when the dependency
#  information is not current.
#

checkout:	${USE}



#
#  Clean up the current build directory.
#

clean:
	@for f in ${LOAD}; do ${ECHO} ${RM} $$f $$f.* && ${RM} $$f $$f.*; done
	${RM} eddep *.o *.mod Makefile.* *.s locore.i \
		$(MIG_ALL_FILES) \
		errs linterrs makelinks *.log *LOG* ${CLEAN_EXTRA}
	${RM} makedepfiles makedepfilestmp *.o.d
	${RM} makelintfiles lint *.ln *.lint
	${RM} sysconfigtab*
	${CAT} /dev/null >makedep
	${CAT} /dev/null >makelint


MACHINEDIR=.

#
#  This macro is replaced by the set of rules which build everything in
#  OBJS.
#

cm_cfg.o: bsd/cm_cfg.c
	@${RM} cm_cfg.o cm_cfg.o.d
	${KCC} ${CCNFLAGS}  bsd/cm_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cm ; fi

generic_cfg.o: bsd/generic_cfg.c
	@${RM} generic_cfg.o generic_cfg.o.d
	${KCC} ${CCNFLAGS}  bsd/generic_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_generic ; fi

io_cfg.o: bsd/io_cfg.c
	@${RM} io_cfg.o io_cfg.o.d
	${KCC} ${CCNFLAGS}  bsd/io_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_io ; fi

kern_devsw.o: bsd/kern_devsw.c
	@${RM} kern_devsw.o kern_devsw.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_devsw.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_io ; fi

ipc_cfg.o: bsd/ipc_cfg.c
	@${RM} ipc_cfg.o ipc_cfg.o.d
	${KCC} ${CCNFLAGS}  bsd/ipc_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ipc ; fi

proc_cfg.o: bsd/proc_cfg.c
	@${RM} proc_cfg.o proc_cfg.o.d
	${KCC} ${CCNFLAGS}  bsd/proc_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_proc ; fi

sec_cfg.o: dec/sec/sec_cfg.c
	@${RM} sec_cfg.o sec_cfg.o.d
	${KCC} ${CCNFLAGS}  dec/sec/sec_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec ; fi

socket_cfg.o: bsd/socket_cfg.c
	@${RM} socket_cfg.o socket_cfg.o.d
	${KCC} ${CCNFLAGS}  bsd/socket_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_socket ; fi

spd_proplist.o: sec/spd_proplist.c
	@${RM} spd_proplist.o spd_proplist.o.d
	${KCC} ${CCNFLAGS}  sec/spd_proplist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_min ; fi

spd_udac.o: sec/spd_udac.c
	@${RM} spd_udac.o spd_udac.o.d
	${KCC} ${CCNFLAGS}  sec/spd_udac.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_min ; fi

sec_conf.o: sec/sec_conf.c
	@${RM} sec_conf.o sec_conf.o.d
	${KCC} ${CCNFLAGS}  sec/sec_conf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_min ; fi

sec_subrs.o: sec/sec_subrs.c
	@${RM} sec_subrs.o sec_subrs.o.d
	${KCC} ${CCNFLAGS}  sec/sec_subrs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_min ; fi

sec_acl.o: sec/sec_acl.c
	@${RM} sec_acl.o sec_acl.o.d
	${KCC} ${CCNFLAGS}  sec/sec_acl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_min ; fi

rt_cfg.o: kern/rt_cfg.c
	@${RM} rt_cfg.o rt_cfg.o.d
	${KCC} ${CCNFLAGS}  kern/rt_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_rt ; fi

init_sysent.o: init_sysent.c
	@${RM} init_sysent.o init_sysent.o.d
	${KCC} ${CCNFLAGS}  init_sysent.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

exc_server.o: mach/exc_server.c
	@${RM} exc_server.o exc_server.o.d
	${KCC} ${CCNFLAGS}  mach/exc_server.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

exc_user.o: mach/exc_user.c
	@${RM} exc_user.o exc_user.o.d
	${KCC} ${CCNFLAGS}  mach/exc_user.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mach_host_server.o: mach/mach_host_server.c
	@${RM} mach_host_server.o mach_host_server.o.d
	${KCC} ${CCNFLAGS}  mach/mach_host_server.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mach_server.o: mach/mach_server.c
	@${RM} mach_server.o mach_server.o.d
	${KCC} ${CCNFLAGS}  mach/mach_server.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

syscalls.o: syscalls.c
	@${RM} syscalls.o syscalls.o.d
	${KCC} ${CCNFLAGS}  syscalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

cmu_syscalls.o: bsd/cmu_syscalls.c
	@${RM} cmu_syscalls.o cmu_syscalls.o.d
	${KCC} ${CCNFLAGS}  bsd/cmu_syscalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

coff_exec.o: bsd/coff_exec.c
	@${RM} coff_exec.o coff_exec.o.d
	${KCC} ${CCNFLAGS}  bsd/coff_exec.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

interp_exec.o: bsd/interp_exec.c
	@${RM} interp_exec.o interp_exec.o.d
	${KCC} ${CCNFLAGS}  bsd/interp_exec.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_acct.o: bsd/kern_acct.c
	@${RM} kern_acct.o kern_acct.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_acct.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_aio.o: bsd/kern_aio.c
	@${RM} kern_aio.o kern_aio.o.d
	${KCC} ${CCNFLAGS} -g3 bsd/kern_aio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_clock.o: bsd/kern_clock.c
	@${RM} kern_clock.o kern_clock.o.d
	${KCC} ${CCNFLAGS} -g3 bsd/kern_clock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_class.o: bsd/kern_class.c
	@${RM} kern_class.o kern_class.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_class.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_compat.o: bsd/kern_compat.c
	@${RM} kern_compat.o kern_compat.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_compat.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_descrip.o: bsd/kern_descrip.c
	@${RM} kern_descrip.o kern_descrip.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_descrip.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_exec.o: bsd/kern_exec.c
	@${RM} kern_exec.o kern_exec.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_exec.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_execargs.o: bsd/kern_execargs.c
	@${RM} kern_execargs.o kern_execargs.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_execargs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_execconfig.o: bsd/kern_execconfig.c
	@${RM} kern_execconfig.o kern_execconfig.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_execconfig.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_exit.o: bsd/kern_exit.c
	@${RM} kern_exit.o kern_exit.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_exit.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_fork.o: bsd/kern_fork.c
	@${RM} kern_fork.o kern_fork.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_fork.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_kmodcall.o: bsd/kern_kmodcall.c
	@${RM} kern_kmodcall.o kern_kmodcall.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_kmodcall.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_malloc.o: bsd/kern_malloc.c
	@${RM} kern_malloc.o kern_malloc.o.d
	${KCC} ${CCNFLAGS} -g3 bsd/kern_malloc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

contig_malloc.o: bsd/contig_malloc.c
	@${RM} contig_malloc.o contig_malloc.o.d
	${KCC} ${CCNFLAGS}  bsd/contig_malloc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_mman.o: bsd/kern_mman.c
	@${RM} kern_mman.o kern_mman.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_mman.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_proc.o: bsd/kern_proc.c
	@${RM} kern_proc.o kern_proc.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_proc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_prot.o: bsd/kern_prot.c
	@${RM} kern_prot.o kern_prot.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_prot.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_resource.o: bsd/kern_resource.c
	@${RM} kern_resource.o kern_resource.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_resource.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_sig.o: bsd/kern_sig.c
	@${RM} kern_sig.o kern_sig.o.d
	${KCC} ${CCNFLAGS} -g3 bsd/kern_sig.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_sigqueue.o: bsd/kern_sigqueue.c
	@${RM} kern_sigqueue.o kern_sigqueue.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_sigqueue.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_subr.o: bsd/kern_subr.c
	@${RM} kern_subr.o kern_subr.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_subsys.o: bsd/kern_subsys.c
	@${RM} kern_subsys.o kern_subsys.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_subsys.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_synch.o: bsd/kern_synch.c
	@${RM} kern_synch.o kern_synch.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_synch.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_time.o: bsd/kern_time.c
	@${RM} kern_time.o kern_time.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_time.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_utctime.o: bsd/kern_utctime.c
	@${RM} kern_utctime.o kern_utctime.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_utctime.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_xxx.o: bsd/kern_xxx.c
	@${RM} kern_xxx.o kern_xxx.o.d
	${KCC} ${CCNFLAGS} -g3 bsd/kern_xxx.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ldr_kload.o: bsd/ldr_kload.c
	@${RM} ldr_kload.o ldr_kload.o.d
	${KCC} ${CCNFLAGS}  bsd/ldr_kload.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

lwc.o: bsd/lwc.c
	@${RM} lwc.o lwc.o.d
	${KCC} ${CCNFLAGS}  bsd/lwc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mach_process.o: bsd/mach_process.c
	@${RM} mach_process.o mach_process.o.d
	${KCC} ${CCNFLAGS}  bsd/mach_process.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mach_signal.o: bsd/mach_signal.c
	@${RM} mach_signal.o mach_signal.o.d
	${KCC} ${CCNFLAGS}  bsd/mach_signal.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

subr_binlog.o: bsd/subr_binlog.c
	@${RM} subr_binlog.o subr_binlog.o.d
	${KCC} ${CCNFLAGS}  bsd/subr_binlog.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

subr_log.o: bsd/subr_log.c
	@${RM} subr_log.o subr_log.o.d
	${KCC} ${CCNFLAGS} -g3 bsd/subr_log.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

subr_prf.o: bsd/subr_prf.c
	@${RM} subr_prf.o subr_prf.o.d
	${KCC} ${CCNFLAGS} -D_USE_KERNEL_INTRINSICS bsd/subr_prf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

subr_rmap.o: bsd/subr_rmap.c
	@${RM} subr_rmap.o subr_rmap.o.d
	${KCC} ${CCNFLAGS}  bsd/subr_rmap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

subr_select.o: bsd/subr_select.c
	@${RM} subr_select.o subr_select.o.d
	${KCC} ${CCNFLAGS}  bsd/subr_select.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

subr_xxx.o: bsd/subr_xxx.c
	@${RM} subr_xxx.o subr_xxx.o.d
	${KCC} ${CCNFLAGS}  bsd/subr_xxx.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

subsys_conf.o: bsd/subsys_conf.c
	@${RM} subsys_conf.o subsys_conf.o.d
	${KCC} ${CCNFLAGS}  bsd/subsys_conf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

svipc_ipc.o: bsd/svipc_ipc.c
	@${RM} svipc_ipc.o svipc_ipc.o.d
	${KCC} ${CCNFLAGS}  bsd/svipc_ipc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

svipc_msg.o: bsd/svipc_msg.c
	@${RM} svipc_msg.o svipc_msg.o.d
	${KCC} ${CCNFLAGS}  bsd/svipc_msg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

svipc_sem.o: bsd/svipc_sem.c
	@${RM} svipc_sem.o svipc_sem.o.d
	${KCC} ${CCNFLAGS}  bsd/svipc_sem.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

svipc_shm.o: bsd/svipc_shm.c
	@${RM} svipc_shm.o svipc_shm.o.d
	${KCC} ${CCNFLAGS}  bsd/svipc_shm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

sys_generic.o: bsd/sys_generic.c
	@${RM} sys_generic.o sys_generic.o.d
	${KCC} ${CCNFLAGS}  bsd/sys_generic.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

sys_socket.o: bsd/sys_socket.c
	@${RM} sys_socket.o sys_socket.o.d
	${KCC} ${CCNFLAGS}  bsd/sys_socket.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

sys_sysinfo.o: bsd/sys_sysinfo.c
	@${RM} sys_sysinfo.o sys_sysinfo.o.d
	${KCC} ${CCNFLAGS}  bsd/sys_sysinfo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

tty_tty.o: bsd/tty_tty.c
	@${RM} tty_tty.o tty_tty.o.d
	${KCC} ${CCNFLAGS}  bsd/tty_tty.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

uipc_domain.o: bsd/uipc_domain.c
	@${RM} uipc_domain.o uipc_domain.o.d
	${KCC} ${CCNFLAGS}  bsd/uipc_domain.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

uipc_mbuf.o: bsd/uipc_mbuf.c
	@${RM} uipc_mbuf.o uipc_mbuf.o.d
	${KCC} ${CCNFLAGS}  bsd/uipc_mbuf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

uipc_socket.o: bsd/uipc_socket.c
	@${RM} uipc_socket.o uipc_socket.o.d
	${KCC} ${CCNFLAGS}  bsd/uipc_socket.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

uipc_socket2.o: bsd/uipc_socket2.c
	@${RM} uipc_socket2.o uipc_socket2.o.d
	${KCC} ${CCNFLAGS}  bsd/uipc_socket2.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

uipc_syscalls.o: bsd/uipc_syscalls.c
	@${RM} uipc_syscalls.o uipc_syscalls.o.d
	${KCC} ${CCNFLAGS}  bsd/uipc_syscalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ux_exception.o: builtin/ux_exception.c
	@${RM} ux_exception.o ux_exception.o.d
	${KCC} ${CCNFLAGS}  builtin/ux_exception.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ddi_subr.o: ddidki/ddi_subr.c
	@${RM} ddi_subr.o ddi_subr.o.d
	${KCC} ${CCNFLAGS}  ddidki/ddi_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kdebug_kern.o: dec/debug/kdebug/kdebug_kern.c
	@${RM} kdebug_kern.o kdebug_kern.o.d
	${KCC} ${CCNFLAGS}  dec/debug/kdebug/kdebug_kern.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

event.o: kern/event.c
	@${RM} event.o event.o.d
	${KCC} ${CCNFLAGS}  kern/event.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

exception.o: kern/exception.c
	@${RM} exception.o exception.o.d
	${KCC} ${CCNFLAGS}  kern/exception.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

host.o: kern/host.c
	@${RM} host.o host.o.d
	${KCC} ${CCNFLAGS}  kern/host.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_basics.o: kern/ipc_basics.c
	@${RM} ipc_basics.o ipc_basics.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_basics.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_copyin.o: kern/ipc_copyin.c
	@${RM} ipc_copyin.o ipc_copyin.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_copyin.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_copyout.o: kern/ipc_copyout.c
	@${RM} ipc_copyout.o ipc_copyout.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_copyout.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_host.o: kern/ipc_host.c
	@${RM} ipc_host.o ipc_host.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_host.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_kport.o: kern/ipc_kport.c
	@${RM} ipc_kport.o ipc_kport.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_kport.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_kreply.o: kern/ipc_kreply.c
	@${RM} ipc_kreply.o ipc_kreply.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_kreply.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_kset.o: kern/ipc_kset.c
	@${RM} ipc_kset.o ipc_kset.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_kset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_mports.o: kern/ipc_mports.c
	@${RM} ipc_mports.o ipc_mports.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_mports.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_pobj.o: kern/ipc_pobj.c
	@${RM} ipc_pobj.o ipc_pobj.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_pobj.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_port.o: kern/ipc_port.c
	@${RM} ipc_port.o ipc_port.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_port.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_prims.o: kern/ipc_prims.c
	@${RM} ipc_prims.o ipc_prims.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_prims.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_ptraps.o: kern/ipc_ptraps.c
	@${RM} ipc_ptraps.o ipc_ptraps.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_ptraps.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

ipc_tt.o: kern/ipc_tt.c
	@${RM} ipc_tt.o ipc_tt.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_tt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kalloc.o: kern/kalloc.c
	@${RM} kalloc.o kalloc.o.d
	${KCC} ${CCNFLAGS}  kern/kalloc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

lock.o: kern/lock.c
	@${RM} lock.o lock.o.d
	${KCC} ${CCNFLAGS} -g3 kern/lock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

lockdev.o: kern/lockdev.c
	@${RM} lockdev.o lockdev.o.d
	${KCC} ${CCNFLAGS}  kern/lockdev.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mach_factor.o: kern/mach_factor.c
	@${RM} mach_factor.o mach_factor.o.d
	${KCC} ${CCNFLAGS}  kern/mach_factor.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mach_sysdev.o: kern/mach_sysdev.c
	@${RM} mach_sysdev.o mach_sysdev.o.d
	${KCC} ${CCNFLAGS}  kern/mach_sysdev.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mach_user_internal.o: kern/mach_user_internal.c
	@${RM} mach_user_internal.o mach_user_internal.o.d
	${KCC} ${CCNFLAGS}  kern/mach_user_internal.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

machine.o: kern/machine.c
	@${RM} machine.o machine.o.d
	${KCC} ${CCNFLAGS}  kern/machine.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

mig_support.o: kern/mig_support.c
	@${RM} mig_support.o mig_support.o.d
	${KCC} ${CCNFLAGS}  kern/mig_support.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

parallel.o: kern/parallel.c
	@${RM} parallel.o parallel.o.d
	${KCC} ${CCNFLAGS}  kern/parallel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

processor.o: kern/processor.c
	@${RM} processor.o processor.o.d
	${KCC} ${CCNFLAGS}  kern/processor.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

queue.o: kern/queue.c
	@${RM} queue.o queue.o.d
	${KCC} ${CCNFLAGS}  kern/queue.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

sched_prim.o: kern/sched_prim.c
	@${RM} sched_prim.o sched_prim.o.d
	${KCC} ${CCNFLAGS} -g3 kern/sched_prim.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

syscall_emulation.o: kern/syscall_emulation.c
	@${RM} syscall_emulation.o syscall_emulation.o.d
	${KCC} ${CCNFLAGS}  kern/syscall_emulation.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

syscall_subr.o: kern/syscall_subr.c
	@${RM} syscall_subr.o syscall_subr.o.d
	${KCC} ${CCNFLAGS}  kern/syscall_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

syscall_sw.o: kern/syscall_sw.c
	@${RM} syscall_sw.o syscall_sw.o.d
	${KCC} ${CCNFLAGS}  kern/syscall_sw.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

task.o: kern/task.c
	@${RM} task.o task.o.d
	${KCC} ${CCNFLAGS} -g3 kern/task.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

task_swap.o: kern/task_swap.c
	@${RM} task_swap.o task_swap.o.d
	${KCC} ${CCNFLAGS}  kern/task_swap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

thread.o: kern/thread.c
	@${RM} thread.o thread.o.d
	${KCC} ${CCNFLAGS} -g3 kern/thread.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

thread_swap.o: kern/thread_swap.c
	@${RM} thread_swap.o thread_swap.o.d
	${KCC} ${CCNFLAGS}  kern/thread_swap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

threadcall.o: kern/threadcall.c
	@${RM} threadcall.o threadcall.o.d
	${KCC} ${CCNFLAGS}  kern/threadcall.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

timer.o: kern/timer.c
	@${RM} timer.o timer.o.d
	${KCC} ${CCNFLAGS}  kern/timer.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

zalloc.o: kern/zalloc.c
	@${RM} zalloc.o zalloc.o.d
	${KCC} ${CCNFLAGS} -g3 kern/zalloc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

msfs_syscalls.o: msfs/osf/msfs_syscalls.c
	@${RM} msfs_syscalls.o msfs_syscalls.o.d
	${KCC} ${CCNFLAGS}  msfs/osf/msfs_syscalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

if.o: net/if.c
	@${RM} if.o if.o.d
	${KCC} ${CCNFLAGS}  net/if.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

netisr.o: net/netisr.c
	@${RM} netisr.o netisr.o.d
	${KCC} ${CCNFLAGS} -g3 net/netisr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

nfs_hooks.o: nfs/nfs_hooks.c
	@${RM} nfs_hooks.o nfs_hooks.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_hooks.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

fdfs_vfsops.o: svr4/fdfs_vfsops.c
	@${RM} fdfs_vfsops.o fdfs_vfsops.o.d
	${KCC} ${CCNFLAGS}  svr4/fdfs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

fdfs_vnops.o: svr4/fdfs_vnops.c
	@${RM} fdfs_vnops.o fdfs_vnops.o.d
	${KCC} ${CCNFLAGS}  svr4/fdfs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_fuser.o: svr4/kern_fuser.c
	@${RM} kern_fuser.o kern_fuser.o.d
	${KCC} ${CCNFLAGS}  svr4/kern_fuser.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_sigsend.o: svr4/kern_sigsend.c
	@${RM} kern_sigsend.o kern_sigsend.o.d
	${KCC} ${CCNFLAGS}  svr4/kern_sigsend.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_sysfs.o: svr4/kern_sysfs.c
	@${RM} kern_sysfs.o kern_sysfs.o.d
	${KCC} ${CCNFLAGS}  svr4/kern_sysfs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_sysinfo.o: svr4/kern_sysinfo.c
	@${RM} kern_sysinfo.o kern_sysinfo.o.d
	${KCC} ${CCNFLAGS}  svr4/kern_sysinfo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_uadmin.o: svr4/kern_uadmin.c
	@${RM} kern_uadmin.o kern_uadmin.o.d
	${KCC} ${CCNFLAGS}  svr4/kern_uadmin.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

kern_wait.o: svr4/kern_wait.c
	@${RM} kern_wait.o kern_wait.o.d
	${KCC} ${CCNFLAGS}  svr4/kern_wait.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

priocntl.o: svr4/priocntl.c
	@${RM} priocntl.o priocntl.o.d
	${KCC} ${CCNFLAGS}  svr4/priocntl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

procset.o: svr4/procset.c
	@${RM} procset.o procset.o.d
	${KCC} ${CCNFLAGS}  svr4/procset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

tty_common.o: tty/tty_common.c
	@${RM} tty_common.o tty_common.o.d
	${KCC} ${CCNFLAGS}  tty/tty_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_std_kern ; fi

tty_cfg.o: tty/tty_cfg.c
	@${RM} tty_cfg.o tty_cfg.o.d
	${KCC} ${CCNFLAGS}  tty/tty_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bsd_tty ; fi

tty.o: bsd/tty.c
	@${RM} tty.o tty.o.d
	${KCC} ${CCNFLAGS}  bsd/tty.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bsd_tty ; fi

tty_compat.o: bsd/tty_compat.c
	@${RM} tty_compat.o tty_compat.o.d
	${KCC} ${CCNFLAGS}  bsd/tty_compat.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bsd_tty ; fi

tty_subr.o: bsd/tty_subr.c
	@${RM} tty_subr.o tty_subr.o.d
	${KCC} ${CCNFLAGS}  bsd/tty_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bsd_tty ; fi

xpr.o: kern/xpr.c
	@${RM} xpr.o xpr.o.d
	${KCC} ${CCNFLAGS}  kern/xpr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_xpr ; fi

memory_object_default_user.o: mach/memory_object_default_user.c
	@${RM} memory_object_default_user.o memory_object_default_user.o.d
	${KCC} ${CCNFLAGS}  mach/memory_object_default_user.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mach_xp ; fi

cdfs_bmap.o: cdfs/cdfs_bmap.c
	@${RM} cdfs_bmap.o cdfs_bmap.o.d
	${KCC} ${CCNFLAGS}  cdfs/cdfs_bmap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cdfs ; fi

cdfs_config.o: cdfs/cdfs_config.c
	@${RM} cdfs_config.o cdfs_config.o.d
	${KCC} ${CCNFLAGS}  cdfs/cdfs_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cdfs ; fi

cdfs_lookup.o: cdfs/cdfs_lookup.c
	@${RM} cdfs_lookup.o cdfs_lookup.o.d
	${KCC} ${CCNFLAGS}  cdfs/cdfs_lookup.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cdfs ; fi

cdfs_node.o: cdfs/cdfs_node.c
	@${RM} cdfs_node.o cdfs_node.o.d
	${KCC} ${CCNFLAGS}  cdfs/cdfs_node.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cdfs ; fi

cdfs_subr.o: cdfs/cdfs_subr.c
	@${RM} cdfs_subr.o cdfs_subr.o.d
	${KCC} ${CCNFLAGS}  cdfs/cdfs_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cdfs ; fi

cdfs_vfsops.o: cdfs/cdfs_vfsops.c
	@${RM} cdfs_vfsops.o cdfs_vfsops.o.d
	${KCC} ${CCNFLAGS}  cdfs/cdfs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cdfs ; fi

cdfs_vnops.o: cdfs/cdfs_vnops.c
	@${RM} cdfs_vnops.o cdfs_vnops.o.d
	${KCC} ${CCNFLAGS}  cdfs/cdfs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cdfs ; fi

dvdfs_vfsops.o: dvdfs/dvdfs_vfsops.c
	@${RM} dvdfs_vfsops.o dvdfs_vfsops.o.d
	${KCC} ${CCNFLAGS}  dvdfs/dvdfs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dvdfs ; fi

dvdfs_node.o: dvdfs/dvdfs_node.c
	@${RM} dvdfs_node.o dvdfs_node.o.d
	${KCC} ${CCNFLAGS}  dvdfs/dvdfs_node.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dvdfs ; fi

dvdfs_vnops.o: dvdfs/dvdfs_vnops.c
	@${RM} dvdfs_vnops.o dvdfs_vnops.o.d
	${KCC} ${CCNFLAGS}  dvdfs/dvdfs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dvdfs ; fi

ess.o: dec/debug/ess/ess.c
	@${RM} ess.o ess.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ess/ess.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ess ; fi

eventTypes.o: dec/debug/ess/eventTypes.c
	@${RM} eventTypes.o eventTypes.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ess/eventTypes.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ess ; fi

groupEventFuncs.o: dec/debug/ess/groupEventFuncs.c
	@${RM} groupEventFuncs.o groupEventFuncs.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ess/groupEventFuncs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ess ; fi

macroFuncs.o: dec/debug/ess/macroFuncs.c
	@${RM} macroFuncs.o macroFuncs.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ess/macroFuncs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ess ; fi

eventTypes_extensions.o: dec/debug/ess/eventTypes_extensions.c
	@${RM} eventTypes_extensions.o eventTypes_extensions.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ess/eventTypes_extensions.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ess ; fi

macroFuncs_extensions.o: dec/debug/ess/macroFuncs_extensions.c
	@${RM} macroFuncs_extensions.o macroFuncs_extensions.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ess/macroFuncs_extensions.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ess ; fi

event_simulation.o: dec/debug/ess/event_simulation.c
	@${RM} event_simulation.o event_simulation.o.d
	${KCC} ${CCNFLAGS} -g3 dec/debug/ess/event_simulation.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ess_stub ; fi

kdebug_brkpt.o: dec/debug/kdebug/kdebug_brkpt.c
	@${RM} kdebug_brkpt.o kdebug_brkpt.o.d
	${KCC} ${CCNFLAGS}  dec/debug/kdebug/kdebug_brkpt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_conf.o: dec/debug/kdebug/kdebug_conf.c
	@${RM} kdebug_conf.o kdebug_conf.o.d
	${KCC} ${CCNFLAGS}  dec/debug/kdebug/kdebug_conf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_cfg.o: dec/debug/kdebug/kdebug_cfg.c
	@${RM} kdebug_cfg.o kdebug_cfg.o.d
	${KCC} ${CCNFLAGS}  dec/debug/kdebug/kdebug_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_io.o: dec/debug/kdebug/kdebug_io.c
	@${RM} kdebug_io.o kdebug_io.o.d
	${KCC} ${CCNFLAGS}  dec/debug/kdebug/kdebug_io.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_main.o: dec/debug/kdebug/kdebug_main.c
	@${RM} kdebug_main.o kdebug_main.o.d
	${KCC} ${CCNFLAGS}  dec/debug/kdebug/kdebug_main.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_proto.o: dec/debug/kdebug/kdebug_proto.c
	@${RM} kdebug_proto.o kdebug_proto.o.d
	${KCC} ${CCNFLAGS}  dec/debug/kdebug/kdebug_proto.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_access.o: dec/debug/ddb/db_access.c
	@${RM} db_access.o db_access.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_access.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_aout.o: dec/debug/ddb/db_aout.c
	@${RM} db_aout.o db_aout.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_aout.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_break.o: dec/debug/ddb/db_break.c
	@${RM} db_break.o db_break.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_break.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_command.o: dec/debug/ddb/db_command.c
	@${RM} db_command.o db_command.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_command.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_cond.o: dec/debug/ddb/db_cond.c
	@${RM} db_cond.o db_cond.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_cond.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_doprnt.o: dec/debug/ddb/db_doprnt.c
	@${RM} db_doprnt.o db_doprnt.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_doprnt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_examine.o: dec/debug/ddb/db_examine.c
	@${RM} db_examine.o db_examine.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_examine.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_expr.o: dec/debug/ddb/db_expr.c
	@${RM} db_expr.o db_expr.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_expr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_ext_symtab.o: dec/debug/ddb/db_ext_symtab.c
	@${RM} db_ext_symtab.o db_ext_symtab.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_ext_symtab.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_input.o: dec/debug/ddb/db_input.c
	@${RM} db_input.o db_input.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_input.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_lex.o: dec/debug/ddb/db_lex.c
	@${RM} db_lex.o db_lex.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_lex.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_macro.o: dec/debug/ddb/db_macro.c
	@${RM} db_macro.o db_macro.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_macro.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_output.o: dec/debug/ddb/db_output.c
	@${RM} db_output.o db_output.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_output.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_print.o: dec/debug/ddb/db_print.c
	@${RM} db_print.o db_print.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_print.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_run.o: dec/debug/ddb/db_run.c
	@${RM} db_run.o db_run.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_run.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_sym.o: dec/debug/ddb/db_sym.c
	@${RM} db_sym.o db_sym.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_sym.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_task_thread.o: dec/debug/ddb/db_task_thread.c
	@${RM} db_task_thread.o db_task_thread.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_task_thread.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_tr.o: dec/debug/ddb/db_tr.c
	@${RM} db_tr.o db_tr.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_tr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_trap.o: dec/debug/ddb/db_trap.c
	@${RM} db_trap.o db_trap.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_trap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_variables.o: dec/debug/ddb/db_variables.c
	@${RM} db_variables.o db_variables.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_variables.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_watch.o: dec/debug/ddb/db_watch.c
	@${RM} db_watch.o db_watch.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_watch.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_write_cmd.o: dec/debug/ddb/db_write_cmd.c
	@${RM} db_write_cmd.o db_write_cmd.o.d
	${KCC} ${CCNFLAGS}  dec/debug/ddb/db_write_cmd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

dli_bind.o: dli/dli_bind.c
	@${RM} dli_bind.o dli_bind.o.d
	${KCC} ${CCNFLAGS}  dli/dli_bind.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_filter.o: dli/dli_filter.c
	@${RM} dli_filter.o dli_filter.o.d
	${KCC} ${CCNFLAGS}  dli/dli_filter.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_init.o: dli/dli_init.c
	@${RM} dli_init.o dli_init.o.d
	${KCC} ${CCNFLAGS}  dli/dli_init.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_input.o: dli/dli_input.c
	@${RM} dli_input.o dli_input.o.d
	${KCC} ${CCNFLAGS}  dli/dli_input.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_mopctrs.o: dli/dli_mopctrs.c
	@${RM} dli_mopctrs.o dli_mopctrs.o.d
	${KCC} ${CCNFLAGS}  dli/dli_mopctrs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_netsync.o: dli/dli_netsync.c
	@${RM} dli_netsync.o dli_netsync.o.d
	${KCC} ${CCNFLAGS}  dli/dli_netsync.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_output.o: dli/dli_output.c
	@${RM} dli_output.o dli_output.o.d
	${KCC} ${CCNFLAGS}  dli/dli_output.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_proto.o: dli/dli_proto.c
	@${RM} dli_proto.o dli_proto.o.d
	${KCC} ${CCNFLAGS}  dli/dli_proto.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_sockopt.o: dli/dli_sockopt.c
	@${RM} dli_sockopt.o dli_sockopt.o.d
	${KCC} ${CCNFLAGS}  dli/dli_sockopt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_subr.o: dli/dli_subr.c
	@${RM} dli_subr.o dli_subr.o.d
	${KCC} ${CCNFLAGS}  dli/dli_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_timer.o: dli/dli_timer.c
	@${RM} dli_timer.o dli_timer.o.d
	${KCC} ${CCNFLAGS}  dli/dli_timer.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

dli_usrreq.o: dli/dli_usrreq.c
	@${RM} dli_usrreq.o dli_usrreq.o.d
	${KCC} ${CCNFLAGS}  dli/dli_usrreq.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dli ; fi

ffm_cfg.o: ffm/ffm_cfg.c
	@${RM} ffm_cfg.o ffm_cfg.o.d
	${KCC} ${CCNFLAGS}  ffm/ffm_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ffm_fs ; fi

ffm_vfsops.o: ffm/ffm_vfsops.c
	@${RM} ffm_vfsops.o ffm_vfsops.o.d
	${KCC} ${CCNFLAGS}  ffm/ffm_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ffm_fs ; fi

ffm_vnops.o: ffm/ffm_vnops.c
	@${RM} ffm_vnops.o ffm_vnops.o.d
	${KCC} ${CCNFLAGS}  ffm/ffm_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ffm_fs ; fi

cmm.o: atm/cmm/cmm.c
	@${RM} cmm.o cmm.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_subr.o: atm/cmm/cmm_subr.c
	@${RM} cmm_subr.o cmm_subr.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_adi.o: atm/cmm/cmm_adi.c
	@${RM} cmm_adi.o cmm_adi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_adi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_smi.o: atm/cmm/cmm_smi.c
	@${RM} cmm_smi.o cmm_smi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_smi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_cmi.o: atm/cmm/cmm_cmi.c
	@${RM} cmm_cmi.o cmm_cmi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_cmi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_ppa.o: atm/cmm/cmm_ppa.c
	@${RM} cmm_ppa.o cmm_ppa.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_ppa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_esi.o: atm/cmm/cmm_esi.c
	@${RM} cmm_esi.o cmm_esi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_esi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_manage.o: atm/cmm/cmm_manage.c
	@${RM} cmm_manage.o cmm_manage.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_manage.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

cmm_state.o: atm/cmm/cmm_state.c
	@${RM} cmm_state.o cmm_state.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/cmm_state.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atm ; fi

atm_arp.o: netinet/atm/atm_arp.c
	@${RM} atm_arp.o atm_arp.o.d
	${KCC} ${CCNFLAGS} -g3 netinet/atm/atm_arp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmip ; fi

ip_converge.o: netinet/atm/ip_converge.c
	@${RM} ip_converge.o ip_converge.o.d
	${KCC} ${CCNFLAGS} -g3 netinet/atm/ip_converge.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmip ; fi

cm_sap_shim.o: net/if_lane/cm_sap_shim.c
	@${RM} cm_sap_shim.o cm_sap_shim.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/cm_sap_shim.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

le_disp.o: net/if_lane/le_disp.c
	@${RM} le_disp.o le_disp.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/le_disp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

lec_arp.o: net/if_lane/lec_arp.c
	@${RM} lec_arp.o lec_arp.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/lec_arp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

lec_ctrl.o: net/if_lane/lec_ctrl.c
	@${RM} lec_ctrl.o lec_ctrl.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/lec_ctrl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

lec_data.o: net/if_lane/lec_data.c
	@${RM} lec_data.o lec_data.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/lec_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

lec_upper.o: net/if_lane/lec_upper.c
	@${RM} lec_upper.o lec_upper.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/lec_upper.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

map.o: net/if_lane/map.c
	@${RM} map.o map.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/map.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

svc_info.o: net/if_lane/svc_info.c
	@${RM} svc_info.o svc_info.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/svc_info.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

utl.o: net/if_lane/utl.c
	@${RM} utl.o utl.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/utl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

utl_os.o: net/if_lane/utl_os.c
	@${RM} utl_os.o utl_os.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/utl_os.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

g_event.o: net/if_lane/g_event.c
	@${RM} g_event.o g_event.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_lane/g_event.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lane ; fi

ipsh_dunix.o: atm/ifmp/dunix/ipsh_dunix.c
	@${RM} ipsh_dunix.o ipsh_dunix.o.d
	${KCC} ${CCNFLAGS} -g3 atm/ifmp/dunix/ipsh_dunix.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmifmp ; fi

ipshost.o: atm/ifmp/host/ipshost.c
	@${RM} ipshost.o ipshost.o.d
	${KCC} ${CCNFLAGS} -g3 atm/ifmp/host/ipshost.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmifmp ; fi

atmtm.o: atm/cmm/atmtm/atmtm.c
	@${RM} atmtm.o atmtm.o.d
	${KCC} ${CCNFLAGS} -g3 atm/cmm/atmtm/atmtm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmtm ; fi

atmuni_addrmgr.o: atm/uni3.x/atmuni/atmuni_addrmgr.c
	@${RM} atmuni_addrmgr.o atmuni_addrmgr.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_addrmgr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_connect.o: atm/uni3.x/atmuni/atmuni_connect.c
	@${RM} atmuni_connect.o atmuni_connect.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_connect.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_data.o: atm/uni3.x/atmuni/atmuni_data.c
	@${RM} atmuni_data.o atmuni_data.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_devmanip.o: atm/uni3.x/atmuni/atmuni_devmanip.c
	@${RM} atmuni_devmanip.o atmuni_devmanip.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_devmanip.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_except.o: atm/uni3.x/atmuni/atmuni_except.c
	@${RM} atmuni_except.o atmuni_except.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_except.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_ilmi.o: atm/uni3.x/atmuni/atmuni_ilmi.c
	@${RM} atmuni_ilmi.o atmuni_ilmi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_ilmi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_loader.o: atm/uni3.x/atmuni/atmuni_loader.c
	@${RM} atmuni_loader.o atmuni_loader.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_loader.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_mmi.o: atm/uni3.x/atmuni/atmuni_mmi.c
	@${RM} atmuni_mmi.o atmuni_mmi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_mmi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_receive.o: atm/uni3.x/atmuni/atmuni_receive.c
	@${RM} atmuni_receive.o atmuni_receive.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_receive.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_sig.o: atm/uni3.x/atmuni/atmuni_sig.c
	@${RM} atmuni_sig.o atmuni_sig.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_sig.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_sigstubs.o: atm/uni3.x/atmuni/atmuni_sigstubs.c
	@${RM} atmuni_sigstubs.o atmuni_sigstubs.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_sigstubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

atmuni_unimanip.o: atm/uni3.x/atmuni/atmuni_unimanip.c
	@${RM} atmuni_unimanip.o atmuni_unimanip.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/atmuni/atmuni_unimanip.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmuni ; fi

ilmi_manage.o: atm/uni3.x/ilmi/ilmi_manage.c
	@${RM} ilmi_manage.o ilmi_manage.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/ilmi_manage.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

ilmi_loader.o: atm/uni3.x/ilmi/ilmi_loader.c
	@${RM} ilmi_loader.o ilmi_loader.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/ilmi_loader.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

ilmi_data.o: atm/uni3.x/ilmi/ilmi_data.c
	@${RM} ilmi_data.o ilmi_data.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/ilmi_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

ilmi_receive.o: atm/uni3.x/ilmi/ilmi_receive.c
	@${RM} ilmi_receive.o ilmi_receive.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/ilmi_receive.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

agent.o: atm/uni3.x/ilmi/agent.c
	@${RM} agent.o agent.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/agent.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

codec.o: atm/uni3.x/ilmi/codec.c
	@${RM} codec.o codec.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/codec.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

dec_atm.o: atm/uni3.x/ilmi/dec_atm.c
	@${RM} dec_atm.o dec_atm.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/dec_atm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

fsm.o: atm/uni3.x/ilmi/fsm.c
	@${RM} fsm.o fsm.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/fsm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

netpref.o: atm/uni3.x/ilmi/netpref.c
	@${RM} netpref.o netpref.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/netpref.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

system.o: atm/uni3.x/ilmi/system.c
	@${RM} system.o system.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/ilmi/system.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x ; fi

atmsig_manage.o: atm/uni3.x/cmmintf/atmsig_manage.c
	@${RM} atmsig_manage.o atmsig_manage.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_manage.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_loader.o: atm/uni3.x/cmmintf/atmsig_loader.c
	@${RM} atmsig_loader.o atmsig_loader.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_loader.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_cmm_callbacks.o: atm/uni3.x/cmmintf/atmsig_cmm_callbacks.c
	@${RM} atmsig_cmm_callbacks.o atmsig_cmm_callbacks.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_cmm_callbacks.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_qsaalrx.o: atm/uni3.x/cmmintf/atmsig_qsaalrx.c
	@${RM} atmsig_qsaalrx.o atmsig_qsaalrx.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_qsaalrx.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_mainloop.o: atm/uni3.x/cmmintf/atmsig_mainloop.c
	@${RM} atmsig_mainloop.o atmsig_mainloop.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_mainloop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_receive.o: atm/uni3.x/cmmintf/atmsig_receive.c
	@${RM} atmsig_receive.o atmsig_receive.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_receive.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_data.o: atm/uni3.x/cmmintf/atmsig_data.c
	@${RM} atmsig_data.o atmsig_data.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_ies.o: atm/uni3.x/cmmintf/atmsig_ies.c
	@${RM} atmsig_ies.o atmsig_ies.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_ies.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_status.o: atm/uni3.x/cmmintf/atmsig_status.c
	@${RM} atmsig_status.o atmsig_status.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_status.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_add.o: atm/uni3.x/cmmintf/atmsig_add.c
	@${RM} atmsig_add.o atmsig_add.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_add.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_drop.o: atm/uni3.x/cmmintf/atmsig_drop.c
	@${RM} atmsig_drop.o atmsig_drop.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_drop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_release.o: atm/uni3.x/cmmintf/atmsig_release.c
	@${RM} atmsig_release.o atmsig_release.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_release.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_restart.o: atm/uni3.x/cmmintf/atmsig_restart.c
	@${RM} atmsig_restart.o atmsig_restart.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_restart.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_callrefs.o: atm/uni3.x/cmmintf/atmsig_callrefs.c
	@${RM} atmsig_callrefs.o atmsig_callrefs.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_callrefs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_misc.o: atm/uni3.x/cmmintf/atmsig_misc.c
	@${RM} atmsig_misc.o atmsig_misc.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_misc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_setup.o: atm/uni3.x/cmmintf/atmsig_setup.c
	@${RM} atmsig_setup.o atmsig_setup.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_setup.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_addrman.o: atm/uni3.x/cmmintf/atmsig_addrman.c
	@${RM} atmsig_addrman.o atmsig_addrman.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_addrman.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

atmsig_trill_as.o: atm/uni3.x/cmmintf/atmsig_trill_as.c
	@${RM} atmsig_trill_as.o atmsig_trill_as.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/cmmintf/atmsig_trill_as.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

aal.o: atm/uni3.x/common/aal.c
	@${RM} aal.o aal.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/aal.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

asd.o: atm/uni3.x/common/asd.c
	@${RM} asd.o asd.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/asd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

asi.o: atm/uni3.x/common/asi.c
	@${RM} asi.o asi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/asi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

cm_lib.o: atm/uni3.x/common/cm_lib.c
	@${RM} cm_lib.o cm_lib.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/cm_lib.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

las.o: atm/uni3.x/common/las.c
	@${RM} las.o las.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/las.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

cm_atm.o: atm/uni3.x/common/cm_atm.c
	@${RM} cm_atm.o cm_atm.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/cm_atm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

cm_bdy5.o: atm/uni3.x/common/cm_bdy5.c
	@${RM} cm_bdy5.o cm_bdy5.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/cm_bdy5.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

cm_gen.o: atm/uni3.x/common/cm_gen.c
	@${RM} cm_gen.o cm_gen.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/cm_gen.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

cm_hash.o: atm/uni3.x/common/cm_hash.c
	@${RM} cm_hash.o cm_hash.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/cm_hash.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

ss_ptsp.o: atm/uni3.x/common/ss_ptsp.c
	@${RM} ss_ptsp.o ss_ptsp.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/common/ss_ptsp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_bdy1.o: atm/uni3.x/q93b/am_bdy1.c
	@${RM} am_bdy1.o am_bdy1.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_bdy1.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_bdy2.o: atm/uni3.x/q93b/am_bdy2.c
	@${RM} am_bdy2.o am_bdy2.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_bdy2.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_bdy3.o: atm/uni3.x/q93b/am_bdy3.c
	@${RM} am_bdy3.o am_bdy3.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_bdy3.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_bdy4.o: atm/uni3.x/q93b/am_bdy4.c
	@${RM} am_bdy4.o am_bdy4.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_bdy4.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_bdy5.o: atm/uni3.x/q93b/am_bdy5.c
	@${RM} am_bdy5.o am_bdy5.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_bdy5.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_db1.o: atm/uni3.x/q93b/am_db1.c
	@${RM} am_db1.o am_db1.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_db1.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_db2.o: atm/uni3.x/q93b/am_db2.c
	@${RM} am_db2.o am_db2.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_db2.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_id.o: atm/uni3.x/q93b/am_id.c
	@${RM} am_id.o am_id.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_id.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_ex_pt.o: atm/uni3.x/q93b/am_ex_pt.c
	@${RM} am_ex_pt.o am_ex_pt.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_ex_pt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_ptli.o: atm/uni3.x/q93b/am_ptli.c
	@${RM} am_ptli.o am_ptli.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_ptli.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_mf.o: atm/uni3.x/q93b/am_mf.c
	@${RM} am_mf.o am_mf.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_mf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

am_ptmi.o: atm/uni3.x/q93b/am_ptmi.c
	@${RM} am_ptmi.o am_ptmi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/q93b/am_ptmi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_bdy1.o: atm/uni3.x/qsaal/as_bdy1.c
	@${RM} as_bdy1.o as_bdy1.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_bdy1.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_bdy2.o: atm/uni3.x/qsaal/as_bdy2.c
	@${RM} as_bdy2.o as_bdy2.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_bdy2.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_bdy3.o: atm/uni3.x/qsaal/as_bdy3.c
	@${RM} as_bdy3.o as_bdy3.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_bdy3.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_bdy4.o: atm/uni3.x/qsaal/as_bdy4.c
	@${RM} as_bdy4.o as_bdy4.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_bdy4.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_bdy5.o: atm/uni3.x/qsaal/as_bdy5.c
	@${RM} as_bdy5.o as_bdy5.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_bdy5.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_bdy6.o: atm/uni3.x/qsaal/as_bdy6.c
	@${RM} as_bdy6.o as_bdy6.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_bdy6.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_ex_pt.o: atm/uni3.x/qsaal/as_ex_pt.c
	@${RM} as_ex_pt.o as_ex_pt.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_ex_pt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_id.o: atm/uni3.x/qsaal/as_id.c
	@${RM} as_id.o as_id.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_id.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_ptui.o: atm/uni3.x/qsaal/as_ptui.c
	@${RM} as_ptui.o as_ptui.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_ptui.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

as_ptmi.o: atm/uni3.x/qsaal/as_ptmi.c
	@${RM} as_ptmi.o as_ptmi.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/qsaal/as_ptmi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

lm.o: atm/uni3.x/lm/lm.c
	@${RM} lm.o lm.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/lm/lm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

smambdy1.o: atm/uni3.x/lm/smambdy1.c
	@${RM} smambdy1.o smambdy1.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/lm/smambdy1.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

smasbdy1.o: atm/uni3.x/lm/smasbdy1.c
	@${RM} smasbdy1.o smasbdy1.o.d
	${KCC} ${CCNFLAGS} -g3 atm/uni3.x/lm/smasbdy1.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uni3x ; fi

bparm_cfg.o: arch/alpha/hal/bparm_cfg.c
	@${RM} bparm_cfg.o bparm_cfg.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/hal/bparm_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bparm ; fi

aclchk.o: lat/engine/aclchk.c
	@${RM} aclchk.o aclchk.o.d
	${KCC} ${CCNFLAGS}  lat/engine/aclchk.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

aclclr.o: lat/engine/aclclr.c
	@${RM} aclclr.o aclclr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/aclclr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

aclcmp.o: lat/engine/aclcmp.c
	@${RM} aclcmp.o aclcmp.o.d
	${KCC} ${CCNFLAGS}  lat/engine/aclcmp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

aclrep.o: lat/engine/aclrep.c
	@${RM} aclrep.o aclrep.o.d
	${KCC} ${CCNFLAGS}  lat/engine/aclrep.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

aclset.o: lat/engine/aclset.c
	@${RM} aclset.o aclset.o.d
	${KCC} ${CCNFLAGS}  lat/engine/aclset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

adpcre.o: lat/engine/adpcre.c
	@${RM} adpcre.o adpcre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/adpcre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

adpdel.o: lat/engine/adpdel.c
	@${RM} adpdel.o adpdel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/adpdel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

adplist.o: lat/engine/adplist.c
	@${RM} adplist.o adplist.o.d
	${KCC} ${CCNFLAGS}  lat/engine/adplist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

adpsh.o: lat/engine/adpsh.c
	@${RM} adpsh.o adpsh.o.d
	${KCC} ${CCNFLAGS}  lat/engine/adpsh.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asclro.o: lat/engine/asclro.c
	@${RM} asclro.o asclro.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asclro.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asclrp.o: lat/engine/asclrp.c
	@${RM} asclrp.o asclrp.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asclrp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ascre.o: lat/engine/ascre.c
	@${RM} ascre.o ascre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ascre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asdel.o: lat/engine/asdel.c
	@${RM} asdel.o asdel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asdel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

aslist.o: lat/engine/aslist.c
	@${RM} aslist.o aslist.o.d
	${KCC} ${CCNFLAGS}  lat/engine/aslist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asmsg.o: lat/engine/asmsg.c
	@${RM} asmsg.o asmsg.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asmsg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asrset.o: lat/engine/asrset.c
	@${RM} asrset.o asrset.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asrset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

assetf.o: lat/engine/assetf.c
	@${RM} assetf.o assetf.o.d
	${KCC} ${CCNFLAGS}  lat/engine/assetf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asseti.o: lat/engine/asseti.c
	@${RM} asseti.o asseti.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asseti.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asseto.o: lat/engine/asseto.c
	@${RM} asseto.o asseto.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asseto.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

assetp.o: lat/engine/assetp.c
	@${RM} assetp.o assetp.o.d
	${KCC} ${CCNFLAGS}  lat/engine/assetp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

asshow.o: lat/engine/asshow.c
	@${RM} asshow.o asshow.o.d
	${KCC} ${CCNFLAGS}  lat/engine/asshow.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbabo.o: lat/engine/cbabo.c
	@${RM} cbabo.o cbabo.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbabo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbcre.o: lat/engine/cbcre.c
	@${RM} cbcre.o cbcre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbcre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbdel.o: lat/engine/cbdel.c
	@${RM} cbdel.o cbdel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbdel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbhalt.o: lat/engine/cbhalt.c
	@${RM} cbhalt.o cbhalt.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbhalt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbhrun.o: lat/engine/cbhrun.c
	@${RM} cbhrun.o cbhrun.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbhrun.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbhstr.o: lat/engine/cbhstr.c
	@${RM} cbhstr.o cbhstr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbhstr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cborun.o: lat/engine/cborun.c
	@${RM} cborun.o cborun.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cborun.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbostr.o: lat/engine/cbostr.c
	@${RM} cbostr.o cbostr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbostr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbrout.o: lat/engine/cbrout.c
	@${RM} cbrout.o cbrout.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbrout.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbrxmt.o: lat/engine/cbrxmt.c
	@${RM} cbrxmt.o cbrxmt.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbrxmt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbsrun.o: lat/engine/cbsrun.c
	@${RM} cbsrun.o cbsrun.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbsrun.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

cbsstr.o: lat/engine/cbsstr.c
	@${RM} cbsstr.o cbsstr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/cbsstr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

dbchgc.o: lat/engine/dbchgc.c
	@${RM} dbchgc.o dbchgc.o.d
	${KCC} ${CCNFLAGS}  lat/engine/dbchgc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

dbrepb.o: lat/engine/dbrepb.c
	@${RM} dbrepb.o dbrepb.o.d
	${KCC} ${CCNFLAGS}  lat/engine/dbrepb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

dbrepc.o: lat/engine/dbrepc.c
	@${RM} dbrepc.o dbrepc.o.d
	${KCC} ${CCNFLAGS}  lat/engine/dbrepc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

dbreps.o: lat/engine/dbreps.c
	@${RM} dbreps.o dbreps.o.d
	${KCC} ${CCNFLAGS}  lat/engine/dbreps.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

dbsetc.o: lat/engine/dbsetc.c
	@${RM} dbsetc.o dbsetc.o.d
	${KCC} ${CCNFLAGS}  lat/engine/dbsetc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

dbsetm.o: lat/engine/dbsetm.c
	@${RM} dbsetm.o dbsetm.o.d
	${KCC} ${CCNFLAGS}  lat/engine/dbsetm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

exerr.o: lat/engine/exerr.c
	@${RM} exerr.o exerr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/exerr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hicre.o: lat/engine/hicre.c
	@${RM} hicre.o hicre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hicre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hidel.o: lat/engine/hidel.c
	@${RM} hidel.o hidel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hidel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiecan.o: lat/engine/hiecan.c
	@${RM} hiecan.o hiecan.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiecan.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hierpt.o: lat/engine/hierpt.c
	@${RM} hierpt.o hierpt.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hierpt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hifind.o: lat/engine/hifind.c
	@${RM} hifind.o hifind.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hifind.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hihra.o: lat/engine/hihra.c
	@${RM} hihra.o hihra.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hihra.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hihri.o: lat/engine/hihri.c
	@${RM} hihri.o hihri.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hihri.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hihsts.o: lat/engine/hihsts.c
	@${RM} hihsts.o hihsts.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hihsts.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiinit.o: lat/engine/hiinit.c
	@${RM} hiinit.o hiinit.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiinit.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiocmd.o: lat/engine/hiocmd.c
	@${RM} hiocmd.o hiocmd.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiocmd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiopen.o: lat/engine/hiopen.c
	@${RM} hiopen.o hiopen.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiopen.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiora.o: lat/engine/hiora.c
	@${RM} hiora.o hiora.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiora.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hioreq.o: lat/engine/hioreq.c
	@${RM} hioreq.o hioreq.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hioreq.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiori.o: lat/engine/hiori.c
	@${RM} hiori.o hiori.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiori.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiosi.o: lat/engine/hiosi.c
	@${RM} hiosi.o hiosi.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiosi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiosts.o: lat/engine/hiosts.c
	@${RM} hiosts.o hiosts.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiosts.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiqrpt.o: lat/engine/hiqrpt.c
	@${RM} hiqrpt.o hiqrpt.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiqrpt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiqsts.o: lat/engine/hiqsts.c
	@${RM} hiqsts.o hiqsts.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiqsts.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hirej.o: lat/engine/hirej.c
	@${RM} hirej.o hirej.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hirej.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hiscmd.o: lat/engine/hiscmd.c
	@${RM} hiscmd.o hiscmd.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hiscmd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hises.o: lat/engine/hises.c
	@${RM} hises.o hises.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hises.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hissi.o: lat/engine/hissi.c
	@${RM} hissi.o hissi.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hissi.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

histr.o: lat/engine/histr.c
	@${RM} histr.o histr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/histr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hsrset.o: lat/engine/hsrset.c
	@${RM} hsrset.o hsrset.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hsrset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hszero.o: lat/engine/hszero.c
	@${RM} hszero.o hszero.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hszero.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hxsts.o: lat/engine/hxsts.c
	@${RM} hxsts.o hxsts.o.d
	${KCC} ${CCNFLAGS}  lat/engine/hxsts.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

idlchk.o: lat/engine/idlchk.c
	@${RM} idlchk.o idlchk.o.d
	${KCC} ${CCNFLAGS}  lat/engine/idlchk.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

idlclr.o: lat/engine/idlclr.c
	@${RM} idlclr.o idlclr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/idlclr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

idlcmp.o: lat/engine/idlcmp.c
	@${RM} idlcmp.o idlcmp.o.d
	${KCC} ${CCNFLAGS}  lat/engine/idlcmp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

idlset.o: lat/engine/idlset.c
	@${RM} idlset.o idlset.o.d
	${KCC} ${CCNFLAGS}  lat/engine/idlset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ifchk.o: lat/engine/ifchk.c
	@${RM} ifchk.o ifchk.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ifchk.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ifmsg.o: lat/engine/ifmsg.c
	@${RM} ifmsg.o ifmsg.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ifmsg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latcom.o: lat/engine/latcom.c
	@${RM} latcom.o latcom.o.d
	${KCC} ${CCNFLAGS} -g3 lat/engine/latcom.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lscre.o: lat/engine/lscre.c
	@${RM} lscre.o lscre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lscre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsdel.o: lat/engine/lsdel.c
	@${RM} lsdel.o lsdel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsdel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsdups.o: lat/engine/lsdups.c
	@${RM} lsdups.o lsdups.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsdups.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lslist.o: lat/engine/lslist.c
	@${RM} lslist.o lslist.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lslist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lslook.o: lat/engine/lslook.c
	@${RM} lslook.o lslook.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lslook.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lslsth.o: lat/engine/lslsth.c
	@${RM} lslsth.o lslsth.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lslsth.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsmsg.o: lat/engine/lsmsg.c
	@${RM} lsmsg.o lsmsg.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsmsg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsperm.o: lat/engine/lsperm.c
	@${RM} lsperm.o lsperm.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsperm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsrem.o: lat/engine/lsrem.c
	@${RM} lsrem.o lsrem.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsrem.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsrset.o: lat/engine/lsrset.c
	@${RM} lsrset.o lsrset.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsrset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsscan.o: lat/engine/lsscan.c
	@${RM} lsscan.o lsscan.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsscan.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lsshow.o: lat/engine/lsshow.c
	@${RM} lsshow.o lsshow.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lsshow.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lstmo.o: lat/engine/lstmo.c
	@${RM} lstmo.o lstmo.o.d
	${KCC} ${CCNFLAGS}  lat/engine/lstmo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ndcre.o: lat/engine/ndcre.c
	@${RM} ndcre.o ndcre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ndcre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

nddel.o: lat/engine/nddel.c
	@${RM} nddel.o nddel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/nddel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ndfail.o: lat/engine/ndfail.c
	@${RM} ndfail.o ndfail.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ndfail.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ndlist.o: lat/engine/ndlist.c
	@${RM} ndlist.o ndlist.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ndlist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ndpur.o: lat/engine/ndpur.c
	@${RM} ndpur.o ndpur.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ndpur.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ndshow.o: lat/engine/ndshow.c
	@${RM} ndshow.o ndshow.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ndshow.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ndzero.o: lat/engine/ndzero.c
	@${RM} ndzero.o ndzero.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ndzero.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obclon.o: lat/engine/obclon.c
	@${RM} obclon.o obclon.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obclon.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obcre.o: lat/engine/obcre.c
	@${RM} obcre.o obcre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obcre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obdel.o: lat/engine/obdel.c
	@${RM} obdel.o obdel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obdel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obfind.o: lat/engine/obfind.c
	@${RM} obfind.o obfind.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obfind.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

oblist.o: lat/engine/oblist.c
	@${RM} oblist.o oblist.o.d
	${KCC} ${CCNFLAGS}  lat/engine/oblist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obrel.o: lat/engine/obrel.c
	@${RM} obrel.o obrel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obrel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obren.o: lat/engine/obren.c
	@${RM} obren.o obren.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obren.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obrset.o: lat/engine/obrset.c
	@${RM} obrset.o obrset.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obrset.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obsetf.o: lat/engine/obsetf.c
	@${RM} obsetf.o obsetf.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obsetf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

obshow.o: lat/engine/obshow.c
	@${RM} obshow.o obshow.o.d
	${KCC} ${CCNFLAGS}  lat/engine/obshow.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

oxses.o: lat/engine/oxses.c
	@${RM} oxses.o oxses.o.d
	${KCC} ${CCNFLAGS}  lat/engine/oxses.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

qrcre.o: lat/engine/qrcre.c
	@${RM} qrcre.o qrcre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/qrcre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

qrdel.o: lat/engine/qrdel.c
	@${RM} qrdel.o qrdel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/qrdel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

qrfind.o: lat/engine/qrfind.c
	@${RM} qrfind.o qrfind.o.d
	${KCC} ${CCNFLAGS}  lat/engine/qrfind.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

qrlist.o: lat/engine/qrlist.c
	@${RM} qrlist.o qrlist.o.d
	${KCC} ${CCNFLAGS}  lat/engine/qrlist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

qrscan.o: lat/engine/qrscan.c
	@${RM} qrscan.o qrscan.o.d
	${KCC} ${CCNFLAGS}  lat/engine/qrscan.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sb1inp.o: lat/engine/sb1inp.c
	@${RM} sb1inp.o sb1inp.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sb1inp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sb1out.o: lat/engine/sb1out.c
	@${RM} sb1out.o sb1out.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sb1out.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbacc.o: lat/engine/sbacc.c
	@${RM} sbacc.o sbacc.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbacc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbcre.o: lat/engine/sbcre.c
	@${RM} sbcre.o sbcre.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbcre.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbdel.o: lat/engine/sbdel.c
	@${RM} sbdel.o sbdel.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbdel.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbdups.o: lat/engine/sbdups.c
	@${RM} sbdups.o sbdups.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbdups.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbfind.o: lat/engine/sbfind.c
	@${RM} sbfind.o sbfind.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbfind.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbopen.o: lat/engine/sbopen.c
	@${RM} sbopen.o sbopen.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbopen.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbrej.o: lat/engine/sbrej.c
	@${RM} sbrej.o sbrej.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbrej.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbria.o: lat/engine/sbria.c
	@${RM} sbria.o sbria.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbria.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbsig.o: lat/engine/sbsig.c
	@${RM} sbsig.o sbsig.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbsig.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbstop.o: lat/engine/sbstop.c
	@${RM} sbstop.o sbstop.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbstop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sbstr.o: lat/engine/sbstr.c
	@${RM} sbstr.o sbstr.o.d
	${KCC} ${CCNFLAGS}  lat/engine/sbstr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ticelp.o: lat/engine/ticelp.c
	@${RM} ticelp.o ticelp.o.d
	${KCC} ${CCNFLAGS}  lat/engine/ticelp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

tocelp.o: lat/engine/tocelp.c
	@${RM} tocelp.o tocelp.o.d
	${KCC} ${CCNFLAGS}  lat/engine/tocelp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

vcshow.o: lat/engine/vcshow.c
	@${RM} vcshow.o vcshow.o.d
	${KCC} ${CCNFLAGS}  lat/engine/vcshow.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

axrate.o: lat/streams/axrate.c
	@${RM} axrate.o axrate.o.d
	${KCC} ${CCNFLAGS}  lat/streams/axrate.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

grpret.o: lat/streams/grpret.c
	@${RM} grpret.o grpret.o.d
	${KCC} ${CCNFLAGS}  lat/streams/grpret.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

hxses.o: lat/streams/hxses.c
	@${RM} hxses.o hxses.o.d
	${KCC} ${CCNFLAGS}  lat/streams/hxses.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ixerr.o: lat/streams/ixerr.c
	@${RM} ixerr.o ixerr.o.d
	${KCC} ${CCNFLAGS}  lat/streams/ixerr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latadpsubs.o: lat/streams/latadpsubs.c
	@${RM} latadpsubs.o latadpsubs.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latadpsubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latclose.o: lat/streams/latclose.c
	@${RM} latclose.o latclose.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latclose.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latdefsvc.o: lat/streams/latdefsvc.c
	@${RM} latdefsvc.o latdefsvc.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latdefsvc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lathashsubs.o: lat/streams/lathashsubs.c
	@${RM} lathashsubs.o lathashsubs.o.d
	${KCC} ${CCNFLAGS}  lat/streams/lathashsubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latlioc.o: lat/streams/latlioc.c
	@${RM} latlioc.o latlioc.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latlioc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latlog.o: lat/streams/latlog.c
	@${RM} latlog.o latlog.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latlog.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latlrput.o: lat/streams/latlrput.c
	@${RM} latlrput.o latlrput.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latlrput.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latlrsrv.o: lat/streams/latlrsrv.c
	@${RM} latlrsrv.o latlrsrv.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latlrsrv.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latmain.o: lat/streams/latmain.c
	@${RM} latmain.o latmain.o.d
	${KCC} ${CCNFLAGS} -g3 lat/streams/latmain.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latopen.o: lat/streams/latopen.c
	@${RM} latopen.o latopen.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latopen.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latsub.o: lat/streams/latsub.c
	@${RM} latsub.o latsub.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latsub.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lattimer.o: lat/streams/lattimer.c
	@${RM} lattimer.o lattimer.o.d
	${KCC} ${CCNFLAGS}  lat/streams/lattimer.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lattioc.o: lat/streams/lattioc.c
	@${RM} lattioc.o lattioc.o.d
	${KCC} ${CCNFLAGS}  lat/streams/lattioc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lattli.o: lat/streams/lattli.c
	@${RM} lattli.o lattli.o.d
	${KCC} ${CCNFLAGS}  lat/streams/lattli.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latursrv.o: lat/streams/latursrv.c
	@${RM} latursrv.o latursrv.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latursrv.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

latuwput.o: lat/streams/latuwput.c
	@${RM} latuwput.o latuwput.o.d
	${KCC} ${CCNFLAGS}  lat/streams/latuwput.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

ofmsg.o: lat/streams/ofmsg.c
	@${RM} ofmsg.o ofmsg.o.d
	${KCC} ${CCNFLAGS}  lat/streams/ofmsg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

strchk.o: lat/streams/strchk.c
	@${RM} strchk.o strchk.o.d
	${KCC} ${CCNFLAGS}  lat/streams/strchk.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

strcvt.o: lat/streams/strcvt.c
	@${RM} strcvt.o strcvt.o.d
	${KCC} ${CCNFLAGS}  lat/streams/strcvt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

strdif.o: lat/streams/strdif.c
	@${RM} strdif.o strdif.o.d
	${KCC} ${CCNFLAGS}  lat/streams/strdif.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

strequ.o: lat/streams/strequ.c
	@${RM} strequ.o strequ.o.d
	${KCC} ${CCNFLAGS}  lat/streams/strequ.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

strinp.o: lat/streams/strinp.c
	@${RM} strinp.o strinp.o.d
	${KCC} ${CCNFLAGS}  lat/streams/strinp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

strmov.o: lat/streams/strmov.c
	@${RM} strmov.o strmov.o.d
	${KCC} ${CCNFLAGS}  lat/streams/strmov.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

strret.o: lat/streams/strret.c
	@${RM} strret.o strret.o.d
	${KCC} ${CCNFLAGS}  lat/streams/strret.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sxgetc.o: lat/streams/sxgetc.c
	@${RM} sxgetc.o sxgetc.o.d
	${KCC} ${CCNFLAGS}  lat/streams/sxgetc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sxputc.o: lat/streams/sxputc.c
	@${RM} sxputc.o sxputc.o.d
	${KCC} ${CCNFLAGS}  lat/streams/sxputc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sxses.o: lat/streams/sxses.c
	@${RM} sxses.o sxses.o.d
	${KCC} ${CCNFLAGS}  lat/streams/sxses.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

sxsig.o: lat/streams/sxsig.c
	@${RM} sxsig.o sxsig.o.d
	${KCC} ${CCNFLAGS}  lat/streams/sxsig.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lat ; fi

lv_block.o: lvm/lv_block.c
	@${RM} lv_block.o lv_block.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_block.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_config.o: lvm/lv_config.c
	@${RM} lv_config.o lv_config.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_defect.o: lvm/lv_defect.c
	@${RM} lv_defect.o lv_defect.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_defect.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_ioctls.o: lvm/lv_ioctls.c
	@${RM} lv_ioctls.o lv_ioctls.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_ioctls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_kdb.o: lvm/lv_kdb.c
	@${RM} lv_kdb.o lv_kdb.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_kdb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_lvsubr.o: lvm/lv_lvsubr.c
	@${RM} lv_lvsubr.o lv_lvsubr.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_lvsubr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_mircons.o: lvm/lv_mircons.c
	@${RM} lv_mircons.o lv_mircons.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_mircons.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_pbuf.o: lvm/lv_pbuf.c
	@${RM} lv_pbuf.o lv_pbuf.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_pbuf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_phys.o: lvm/lv_phys.c
	@${RM} lv_phys.o lv_phys.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_phys.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_schedule.o: lvm/lv_schedule.c
	@${RM} lv_schedule.o lv_schedule.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_schedule.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_strategy.o: lvm/lv_strategy.c
	@${RM} lv_strategy.o lv_strategy.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_strategy.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_subr.o: lvm/lv_subr.c
	@${RM} lv_subr.o lv_subr.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_syscalls.o: lvm/lv_syscalls.c
	@${RM} lv_syscalls.o lv_syscalls.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_syscalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_vgda.o: lvm/lv_vgda.c
	@${RM} lv_vgda.o lv_vgda.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_vgda.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

lv_vgsa.o: lvm/lv_vgsa.c
	@${RM} lv_vgsa.o lv_vgsa.o.d
	${KCC} ${CCNFLAGS}  lvm/lv_vgsa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lv ; fi

bs_access.o: msfs/bs/bs_access.c
	@${RM} bs_access.o bs_access.o.d
	${KCC} ${CCNFLAGS} -g3 msfs/bs/bs_access.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_bitfile_sets.o: msfs/bs/bs_bitfile_sets.c
	@${RM} bs_bitfile_sets.o bs_bitfile_sets.o.d
	${KCC} ${CCNFLAGS} -g3 msfs/bs/bs_bitfile_sets.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_bmt_util.o: msfs/bs/bs_bmt_util.c
	@${RM} bs_bmt_util.o bs_bmt_util.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_bmt_util.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_buffer2.o: msfs/bs/bs_buffer2.c
	@${RM} bs_buffer2.o bs_buffer2.o.d
	${KCC} ${CCNFLAGS} -g3 msfs/bs/bs_buffer2.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_copy.o: msfs/bs/bs_copy.c
	@${RM} bs_copy.o bs_copy.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_copy.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_create.o: msfs/bs/bs_create.c
	@${RM} bs_create.o bs_create.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_create.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_delete.o: msfs/bs/bs_delete.c
	@${RM} bs_delete.o bs_delete.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_delete.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_domain.o: msfs/bs/bs_domain.c
	@${RM} bs_domain.o bs_domain.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_domain.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_errlst.o: msfs/bs/bs_errlst.c
	@${RM} bs_errlst.o bs_errlst.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_errlst.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_extents.o: msfs/bs/bs_extents.c
	@${RM} bs_extents.o bs_extents.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_extents.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_init.o: msfs/bs/bs_init.c
	@${RM} bs_init.o bs_init.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_init.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_inmem_map.o: msfs/bs/bs_inmem_map.c
	@${RM} bs_inmem_map.o bs_inmem_map.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_inmem_map.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_migrate.o: msfs/bs/bs_migrate.c
	@${RM} bs_migrate.o bs_migrate.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_migrate.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_misc.o: msfs/bs/bs_misc.c
	@${RM} bs_misc.o bs_misc.o.d
	${KCC} ${CCNFLAGS} -D_USE_KERNEL_INTRINSICS msfs/bs/bs_misc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_msg_queue.o: msfs/bs/bs_msg_queue.c
	@${RM} bs_msg_queue.o bs_msg_queue.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_msg_queue.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_params.o: msfs/bs/bs_params.c
	@${RM} bs_params.o bs_params.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_params.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_qio.o: msfs/bs/bs_qio.c
	@${RM} bs_qio.o bs_qio.o.d
	${KCC} ${CCNFLAGS} -g3 msfs/bs/bs_qio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_sbm.o: msfs/bs/bs_sbm.c
	@${RM} bs_sbm.o bs_sbm.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_sbm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_service_class.o: msfs/bs/bs_service_class.c
	@${RM} bs_service_class.o bs_service_class.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_service_class.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_shadow.o: msfs/bs/bs_shadow.c
	@${RM} bs_shadow.o bs_shadow.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_shadow.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_stg.o: msfs/bs/bs_stg.c
	@${RM} bs_stg.o bs_stg.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_stg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_stripe.o: msfs/bs/bs_stripe.c
	@${RM} bs_stripe.o bs_stripe.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_stripe.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bs_tagdir.o: msfs/bs/bs_tagdir.c
	@${RM} bs_tagdir.o bs_tagdir.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/bs_tagdir.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ftx_recovery.o: msfs/bs/ftx_recovery.c
	@${RM} ftx_recovery.o ftx_recovery.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/ftx_recovery.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ftx_routines.o: msfs/bs/ftx_routines.c
	@${RM} ftx_routines.o ftx_routines.o.d
	${KCC} ${CCNFLAGS} -g3 msfs/bs/ftx_routines.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ms_generic_locks.o: msfs/bs/ms_generic_locks.c
	@${RM} ms_generic_locks.o ms_generic_locks.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/ms_generic_locks.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ms_logger.o: msfs/bs/ms_logger.c
	@${RM} ms_logger.o ms_logger.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/ms_logger.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ms_mode.o: msfs/bs/ms_mode.c
	@${RM} ms_mode.o ms_mode.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/ms_mode.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ms_privates.o: msfs/bs/ms_privates.c
	@${RM} ms_privates.o ms_privates.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/ms_privates.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ms_public.o: msfs/bs/ms_public.c
	@${RM} ms_public.o ms_public.o.d
	${KCC} ${CCNFLAGS}  msfs/bs/ms_public.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

fs_create.o: msfs/fs/fs_create.c
	@${RM} fs_create.o fs_create.o.d
	${KCC} ${CCNFLAGS}  msfs/fs/fs_create.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

fs_dir_init.o: msfs/fs/fs_dir_init.c
	@${RM} fs_dir_init.o fs_dir_init.o.d
	${KCC} ${CCNFLAGS}  msfs/fs/fs_dir_init.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

fs_dir_lookup.o: msfs/fs/fs_dir_lookup.c
	@${RM} fs_dir_lookup.o fs_dir_lookup.o.d
	${KCC} ${CCNFLAGS}  msfs/fs/fs_dir_lookup.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

fs_file_sets.o: msfs/fs/fs_file_sets.c
	@${RM} fs_file_sets.o fs_file_sets.o.d
	${KCC} ${CCNFLAGS}  msfs/fs/fs_file_sets.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

fs_quota.o: msfs/fs/fs_quota.c
	@${RM} fs_quota.o fs_quota.o.d
	${KCC} ${CCNFLAGS}  msfs/fs/fs_quota.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

fs_read_write.o: msfs/fs/fs_read_write.c
	@${RM} fs_read_write.o fs_read_write.o.d
	${KCC} ${CCNFLAGS}  msfs/fs/fs_read_write.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_common.o: msfs/mss/mss_common.c
	@${RM} mss_common.o mss_common.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_entry.o: msfs/mss/mss_entry.c
	@${RM} mss_entry.o mss_entry.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_entry.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_fs.o: msfs/mss/mss_fs.c
	@${RM} mss_fs.o mss_fs.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_fs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_lock.o: msfs/mss/mss_lock.c
	@${RM} mss_lock.o mss_lock.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_lock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_log.o: msfs/mss/mss_log.c
	@${RM} mss_log.o mss_log.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_log.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_misc.o: msfs/mss/mss_misc.c
	@${RM} mss_misc.o mss_misc.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_misc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_pqd.o: msfs/mss/mss_pqd.c
	@${RM} mss_pqd.o mss_pqd.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_pqd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_send.o: msfs/mss/mss_send.c
	@${RM} mss_send.o mss_send.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_send.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_space.o: msfs/mss/mss_space.c
	@${RM} mss_space.o mss_space.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_space.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

mss_syscall.o: msfs/mss/mss_syscall.c
	@${RM} mss_syscall.o mss_syscall.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/mss_syscall.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ter_inmem_map.o: msfs/mss/ter_inmem_map.c
	@${RM} ter_inmem_map.o ter_inmem_map.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/ter_inmem_map.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ter_ondisk_map.o: msfs/mss/ter_ondisk_map.c
	@${RM} ter_ondisk_map.o ter_ondisk_map.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/ter_ondisk_map.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

ter_stg.o: msfs/mss/ter_stg.c
	@${RM} ter_stg.o ter_stg.o.d
	${KCC} ${CCNFLAGS}  msfs/mss/ter_stg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_cfg.o: msfs/osf/msfs_cfg.c
	@${RM} msfs_cfg.o msfs_cfg.o.d
	${KCC} ${CCNFLAGS}  msfs/osf/msfs_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_config.o: msfs/osf/msfs_config.c
	@${RM} msfs_config.o msfs_config.o.d
	${KCC} ${CCNFLAGS}  msfs/osf/msfs_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_io.o: msfs/osf/msfs_io.c
	@${RM} msfs_io.o msfs_io.o.d
	${KCC} ${CCNFLAGS} -g3 msfs/osf/msfs_io.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_lookup.o: msfs/osf/msfs_lookup.c
	@${RM} msfs_lookup.o msfs_lookup.o.d
	${KCC} ${CCNFLAGS}  msfs/osf/msfs_lookup.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_misc.o: msfs/osf/msfs_misc.c
	@${RM} msfs_misc.o msfs_misc.o.d
	${KCC} ${CCNFLAGS}  msfs/osf/msfs_misc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_proplist.o: msfs/osf/msfs_proplist.c
	@${RM} msfs_proplist.o msfs_proplist.o.d
	${KCC} ${CCNFLAGS}  msfs/osf/msfs_proplist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_vfsops.o: msfs/osf/msfs_vfsops.c
	@${RM} msfs_vfsops.o msfs_vfsops.o.d
	${KCC} ${CCNFLAGS}  msfs/osf/msfs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

msfs_vnops.o: msfs/osf/msfs_vnops.c
	@${RM} msfs_vnops.o msfs_vnops.o.d
	${KCC} ${CCNFLAGS} -g3 msfs/osf/msfs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_advfs ; fi

bpf_filter.o: net/bpf_filter.c
	@${RM} bpf_filter.o bpf_filter.o.d
	${KCC} ${CCNFLAGS}  net/bpf_filter.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_packetfilter ; fi

pfilt.o: net/pfilt.c
	@${RM} pfilt.o pfilt.o.d
	${KCC} ${CCNFLAGS}  net/pfilt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_packetfilter ; fi

pfilt_bpf.o: net/pfilt_bpf.c
	@${RM} pfilt_bpf.o pfilt_bpf.o.d
	${KCC} ${CCNFLAGS}  net/pfilt_bpf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_packetfilter ; fi

net_cfg.o: net/net_cfg.c
	@${RM} net_cfg.o net_cfg.o.d
	${KCC} ${CCNFLAGS}  net/net_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_net ; fi

raw_cb.o: net/raw_cb.c
	@${RM} raw_cb.o raw_cb.o.d
	${KCC} ${CCNFLAGS}  net/raw_cb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_net ; fi

raw_usrreq.o: net/raw_usrreq.c
	@${RM} raw_usrreq.o raw_usrreq.o.d
	${KCC} ${CCNFLAGS}  net/raw_usrreq.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_net ; fi

route.o: net/route.c
	@${RM} route.o route.o.d
	${KCC} ${CCNFLAGS} -g3 net/route.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_net ; fi

netrain_cfg.o: net/netrain_cfg.c
	@${RM} netrain_cfg.o netrain_cfg.o.d
	${KCC} ${CCNFLAGS}  net/netrain_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_netrain ; fi

netrain.o: net/netrain.c
	@${RM} netrain.o netrain.o.d
	${KCC} ${CCNFLAGS}  net/netrain.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_netrain ; fi

if_nr.o: net/if_nr.c
	@${RM} if_nr.o if_nr.o.d
	${KCC} ${CCNFLAGS}  net/if_nr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_netrain ; fi

if_ethersubr.o: net/if_ethersubr.c
	@${RM} if_ethersubr.o if_ethersubr.o.d
	${KCC} ${CCNFLAGS}  net/if_ethersubr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ether ; fi

if_ether.o: netinet/if_ether.c
	@${RM} if_ether.o if_ether.o.d
	${KCC} ${CCNFLAGS} -g3 netinet/if_ether.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ether ; fi

if_loop.o: net/if_loop.c
	@${RM} if_loop.o if_loop.o.d
	${KCC} ${CCNFLAGS}  net/if_loop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_loop ; fi

if_sl.o: net/if_sl.c
	@${RM} if_sl.o if_sl.o.d
	${KCC} ${CCNFLAGS} -g3 net/if_sl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sl ; fi

ppp_init.o: streamsm/ppp_init.c
	@${RM} ppp_init.o ppp_init.o.d
	${KCC} ${CCNFLAGS}  streamsm/ppp_init.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ppp ; fi

ppp_if.o: streamsm/ppp_if.c
	@${RM} ppp_if.o ppp_if.o.d
	${KCC} ${CCNFLAGS}  streamsm/ppp_if.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ppp ; fi

ppp_async.o: streamsm/ppp_async.c
	@${RM} ppp_async.o ppp_async.o.d
	${KCC} ${CCNFLAGS}  streamsm/ppp_async.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ppp ; fi

ppp_comp.o: streamsm/ppp_comp.c
	@${RM} ppp_comp.o ppp_comp.o.d
	${KCC} ${CCNFLAGS}  streamsm/ppp_comp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ppp ; fi

vjcompress.o: streamsm/vjcompress.c
	@${RM} vjcompress.o vjcompress.o.d
	${KCC} ${CCNFLAGS}  streamsm/vjcompress.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ppp ; fi

bsd_comp.o: streamsm/bsd_comp.c
	@${RM} bsd_comp.o bsd_comp.o.d
	${KCC} ${CCNFLAGS}  streamsm/bsd_comp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ppp ; fi

inet_cfg.o: netinet/inet_cfg.c
	@${RM} inet_cfg.o inet_cfg.o.d
	${KCC} ${CCNFLAGS}  netinet/inet_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

igmp.o: netinet/igmp.c
	@${RM} igmp.o igmp.o.d
	${KCC} ${CCNFLAGS}  netinet/igmp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

in.o: netinet/in.c
	@${RM} in.o in.o.d
	${KCC} ${CCNFLAGS}  netinet/in.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

in_pcb.o: netinet/in_pcb.c
	@${RM} in_pcb.o in_pcb.o.d
	${KCC} ${CCNFLAGS}  netinet/in_pcb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

in_proto.o: netinet/in_proto.c
	@${RM} in_proto.o in_proto.o.d
	${KCC} ${CCNFLAGS}  netinet/in_proto.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

ip_icmp.o: netinet/ip_icmp.c
	@${RM} ip_icmp.o ip_icmp.o.d
	${KCC} ${CCNFLAGS}  netinet/ip_icmp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

ip_input.o: netinet/ip_input.c
	@${RM} ip_input.o ip_input.o.d
	${KCC} ${CCNFLAGS}  netinet/ip_input.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

ip_mroute.o: netinet/ip_mroute.c
	@${RM} ip_mroute.o ip_mroute.o.d
	${KCC} ${CCNFLAGS} -g3 netinet/ip_mroute.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

ip_output.o: netinet/ip_output.c
	@${RM} ip_output.o ip_output.o.d
	${KCC} ${CCNFLAGS}  netinet/ip_output.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

ip_screen.o: netinet/ip_screen.c
	@${RM} ip_screen.o ip_screen.o.d
	${KCC} ${CCNFLAGS}  netinet/ip_screen.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

pmtu.o: netinet/pmtu.c
	@${RM} pmtu.o pmtu.o.d
	${KCC} ${CCNFLAGS}  netinet/pmtu.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

raw_ip.o: netinet/raw_ip.c
	@${RM} raw_ip.o raw_ip.o.d
	${KCC} ${CCNFLAGS}  netinet/raw_ip.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

tcp_debug.o: netinet/tcp_debug.c
	@${RM} tcp_debug.o tcp_debug.o.d
	${KCC} ${CCNFLAGS}  netinet/tcp_debug.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

tcp_input.o: netinet/tcp_input.c
	@${RM} tcp_input.o tcp_input.o.d
	${KCC} ${CCNFLAGS}  netinet/tcp_input.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

tcp_output.o: netinet/tcp_output.c
	@${RM} tcp_output.o tcp_output.o.d
	${KCC} ${CCNFLAGS}  netinet/tcp_output.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

tcp_subr.o: netinet/tcp_subr.c
	@${RM} tcp_subr.o tcp_subr.o.d
	${KCC} ${CCNFLAGS}  netinet/tcp_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

tcp_timer.o: netinet/tcp_timer.c
	@${RM} tcp_timer.o tcp_timer.o.d
	${KCC} ${CCNFLAGS}  netinet/tcp_timer.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

tcp_usrreq.o: netinet/tcp_usrreq.c
	@${RM} tcp_usrreq.o tcp_usrreq.o.d
	${KCC} ${CCNFLAGS}  netinet/tcp_usrreq.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

udp_usrreq.o: netinet/udp_usrreq.c
	@${RM} udp_usrreq.o udp_usrreq.o.d
	${KCC} ${CCNFLAGS} -g3 netinet/udp_usrreq.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_inet ; fi

nfs3_vfsops.o: nfs/nfs3_vfsops.c
	@${RM} nfs3_vfsops.o nfs3_vfsops.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs3_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs3_vnodeops.o: nfs/nfs3_vnodeops.c
	@${RM} nfs3_vnodeops.o nfs3_vnodeops.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs3_vnodeops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs3_xdr.o: nfs/nfs3_xdr.c
	@${RM} nfs3_xdr.o nfs3_xdr.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs3_xdr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_client.o: nfs/nfs_client.c
	@${RM} nfs_client.o nfs_client.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_client.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_common.o: nfs/nfs_common.c
	@${RM} nfs_common.o nfs_common.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_config.o: nfs/nfs_config.c
	@${RM} nfs_config.o nfs_config.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_dump.o: nfs/nfs_dump.c
	@${RM} nfs_dump.o nfs_dump.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_dump.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_subr.o: nfs/nfs_subr.c
	@${RM} nfs_subr.o nfs_subr.o.d
	${KCC} ${CCNFLAGS} -g3 nfs/nfs_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_vfsops.o: nfs/nfs_vfsops.c
	@${RM} nfs_vfsops.o nfs_vfsops.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_vnodeops.o: nfs/nfs_vnodeops.c
	@${RM} nfs_vnodeops.o nfs_vnodeops.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_vnodeops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_xdr.o: nfs/nfs_xdr.c
	@${RM} nfs_xdr.o nfs_xdr.o.d
	${KCC} ${CCNFLAGS}  nfs/nfs_xdr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

prop_xdr.o: nfs/prop_xdr.c
	@${RM} prop_xdr.o prop_xdr.o.d
	${KCC} ${CCNFLAGS}  nfs/prop_xdr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

auth_kern.o: rpc/auth_kern.c
	@${RM} auth_kern.o auth_kern.o.d
	${KCC} ${CCNFLAGS}  rpc/auth_kern.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

authunix_prot.o: rpc/authunix_prot.c
	@${RM} authunix_prot.o authunix_prot.o.d
	${KCC} ${CCNFLAGS}  rpc/authunix_prot.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

clnt_kudp.o: rpc/clnt_kudp.c
	@${RM} clnt_kudp.o clnt_kudp.o.d
	${KCC} ${CCNFLAGS} -g3 rpc/clnt_kudp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

clnt_ktcp.o: rpc/clnt_ktcp.c
	@${RM} clnt_ktcp.o clnt_ktcp.o.d
	${KCC} ${CCNFLAGS} -g3 rpc/clnt_ktcp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

clnt_perror.o: rpc/clnt_perror.c
	@${RM} clnt_perror.o clnt_perror.o.d
	${KCC} ${CCNFLAGS}  rpc/clnt_perror.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

kudp_fastsend.o: rpc/kudp_fastsend.c
	@${RM} kudp_fastsend.o kudp_fastsend.o.d
	${KCC} ${CCNFLAGS} -g3 rpc/kudp_fastsend.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

pmap_kgetport.o: rpc/pmap_kgetport.c
	@${RM} pmap_kgetport.o pmap_kgetport.o.d
	${KCC} ${CCNFLAGS}  rpc/pmap_kgetport.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

pmap_prot.o: rpc/pmap_prot.c
	@${RM} pmap_prot.o pmap_prot.o.d
	${KCC} ${CCNFLAGS}  rpc/pmap_prot.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

pmap_rmt.o: rpc/pmap_rmt.c
	@${RM} pmap_rmt.o pmap_rmt.o.d
	${KCC} ${CCNFLAGS}  rpc/pmap_rmt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

rpc_callmsg.o: rpc/rpc_callmsg.c
	@${RM} rpc_callmsg.o rpc_callmsg.o.d
	${KCC} ${CCNFLAGS}  rpc/rpc_callmsg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

rpc_prot.o: rpc/rpc_prot.c
	@${RM} rpc_prot.o rpc_prot.o.d
	${KCC} ${CCNFLAGS}  rpc/rpc_prot.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

subr_kudp.o: rpc/subr_kudp.c
	@${RM} subr_kudp.o subr_kudp.o.d
	${KCC} ${CCNFLAGS}  rpc/subr_kudp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

svc.o: rpc/svc.c
	@${RM} svc.o svc.o.d
	${KCC} ${CCNFLAGS}  rpc/svc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

svc_auth.o: rpc/svc_auth.c
	@${RM} svc_auth.o svc_auth.o.d
	${KCC} ${CCNFLAGS}  rpc/svc_auth.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

svc_auth_unix.o: rpc/svc_auth_unix.c
	@${RM} svc_auth_unix.o svc_auth_unix.o.d
	${KCC} ${CCNFLAGS}  rpc/svc_auth_unix.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

svc_kudp.o: rpc/svc_kudp.c
	@${RM} svc_kudp.o svc_kudp.o.d
	${KCC} ${CCNFLAGS} -g3 rpc/svc_kudp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

svc_ktcp.o: rpc/svc_ktcp.c
	@${RM} svc_ktcp.o svc_ktcp.o.d
	${KCC} ${CCNFLAGS} -g3 rpc/svc_ktcp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

xdr.o: rpc/xdr.c
	@${RM} xdr.o xdr.o.d
	${KCC} ${CCNFLAGS}  rpc/xdr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

xdr_array.o: rpc/xdr_array.c
	@${RM} xdr_array.o xdr_array.o.d
	${KCC} ${CCNFLAGS}  rpc/xdr_array.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

xdr_mbuf.o: rpc/xdr_mbuf.c
	@${RM} xdr_mbuf.o xdr_mbuf.o.d
	${KCC} ${CCNFLAGS}  rpc/xdr_mbuf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

xdr_mem.o: rpc/xdr_mem.c
	@${RM} xdr_mem.o xdr_mem.o.d
	${KCC} ${CCNFLAGS}  rpc/xdr_mem.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

xdr_reference.o: rpc/xdr_reference.c
	@${RM} xdr_reference.o xdr_reference.o.d
	${KCC} ${CCNFLAGS}  rpc/xdr_reference.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

bootparam_xdr.o: rpcsvc/bootparam_xdr.c
	@${RM} bootparam_xdr.o bootparam_xdr.o.d
	${KCC} ${CCNFLAGS}  rpcsvc/bootparam_xdr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

mountxdr.o: rpcsvc/mountxdr.c
	@${RM} mountxdr.o mountxdr.o.d
	${KCC} ${CCNFLAGS}  rpcsvc/mountxdr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

klm_kprot.o: klm/klm_kprot.c
	@${RM} klm_kprot.o klm_kprot.o.d
	${KCC} ${CCNFLAGS}  klm/klm_kprot.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

klm_lockmgr.o: klm/klm_lockmgr.c
	@${RM} klm_lockmgr.o klm_lockmgr.o.d
	${KCC} ${CCNFLAGS}  klm/klm_lockmgr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs ; fi

nfs_server.o: nfs/nfs_server.c
	@${RM} nfs_server.o nfs_server.o.d
	${KCC} ${CCNFLAGS} -g3 nfs/nfs_server.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs_server ; fi

nfs3_server.o: nfs/nfs3_server.c
	@${RM} nfs3_server.o nfs3_server.o.d
	${KCC} ${CCNFLAGS} -g3 nfs/nfs3_server.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nfs_server ; fi

procfs_subrs.o: procfs/procfs_subrs.c
	@${RM} procfs_subrs.o procfs_subrs.o.d
	${KCC} ${CCNFLAGS} -g3 procfs/procfs_subrs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_procfs ; fi

procfs_vfsops.o: procfs/procfs_vfsops.c
	@${RM} procfs_vfsops.o procfs_vfsops.o.d
	${KCC} ${CCNFLAGS} -g3 procfs/procfs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_procfs ; fi

procfs_vnops.o: procfs/procfs_vnops.c
	@${RM} procfs_vnops.o procfs_vnops.o.d
	${KCC} ${CCNFLAGS} -g3 procfs/procfs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_procfs ; fi

procfs_ioctl.o: procfs/procfs_ioctl.c
	@${RM} procfs_ioctl.o procfs_ioctl.o.d
	${KCC} ${CCNFLAGS} -g3 procfs/procfs_ioctl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_procfs ; fi

procfs_vfsops_stubs.o: procfs/procfs_vfsops_stubs.c
	@${RM} procfs_vfsops_stubs.o procfs_vfsops_stubs.o.d
	${KCC} ${CCNFLAGS} -g3 procfs/procfs_vfsops_stubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_notprocfs ; fi

procfs_subrs_stubs.o: procfs/procfs_subrs_stubs.c
	@${RM} procfs_subrs_stubs.o procfs_subrs_stubs.o.d
	${KCC} ${CCNFLAGS} -g3 procfs/procfs_subrs_stubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_notprocfs ; fi

procfs_vnops_stubs.o: procfs/procfs_vnops_stubs.c
	@${RM} procfs_vnops_stubs.o procfs_vnops_stubs.o.d
	${KCC} ${CCNFLAGS} -g3 procfs/procfs_vnops_stubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_notprocfs ; fi

snmpinfo.o: bsd/snmpinfo.c
	@${RM} snmpinfo.o snmpinfo.o.d
	${KCC} ${CCNFLAGS}  bsd/snmpinfo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_snmpinfo ; fi

str_memory.o: streams/str_memory.c
	@${RM} str_memory.o str_memory.o.d
	${KCC} ${CCNFLAGS} -g3 streams/str_memory.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bufcall ; fi

nd.o: streams/nd.c
	@${RM} nd.o nd.o.d
	${KCC} ${CCNFLAGS}  streams/nd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_cfg.o: streams/str_cfg.c
	@${RM} str_cfg.o str_cfg.o.d
	${KCC} ${CCNFLAGS}  streams/str_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_env.o: streams/str_env.c
	@${RM} str_env.o str_env.o.d
	${KCC} ${CCNFLAGS}  streams/str_env.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_filesys.o: streams/str_filesys.c
	@${RM} str_filesys.o str_filesys.o.d
	${KCC} ${CCNFLAGS}  streams/str_filesys.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_init.o: streams/str_init.c
	@${RM} str_init.o str_init.o.d
	${KCC} ${CCNFLAGS}  streams/str_init.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_modsw.o: streams/str_modsw.c
	@${RM} str_modsw.o str_modsw.o.d
	${KCC} ${CCNFLAGS} -g3 streams/str_modsw.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_osr.o: streams/str_osr.c
	@${RM} str_osr.o str_osr.o.d
	${KCC} ${CCNFLAGS}  streams/str_osr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_runq.o: streams/str_runq.c
	@${RM} str_runq.o str_runq.o.d
	${KCC} ${CCNFLAGS} -g3 streams/str_runq.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_scalls.o: streams/str_scalls.c
	@${RM} str_scalls.o str_scalls.o.d
	${KCC} ${CCNFLAGS} -g3 streams/str_scalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_shead.o: streams/str_shead.c
	@${RM} str_shead.o str_shead.o.d
	${KCC} ${CCNFLAGS}  streams/str_shead.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_subr.o: streams/str_subr.c
	@${RM} str_subr.o str_subr.o.d
	${KCC} ${CCNFLAGS}  streams/str_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_support.o: streams/str_support.c
	@${RM} str_support.o str_support.o.d
	${KCC} ${CCNFLAGS}  streams/str_support.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_synch.o: streams/str_synch.c
	@${RM} str_synch.o str_synch.o.d
	${KCC} ${CCNFLAGS} -g3 streams/str_synch.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_tty.o: streams/str_tty.c
	@${RM} str_tty.o str_tty.o.d
	${KCC} ${CCNFLAGS}  streams/str_tty.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_util.o: streams/str_util.c
	@${RM} str_util.o str_util.o.d
	${KCC} ${CCNFLAGS}  streams/str_util.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_weld.o: streams/str_weld.c
	@${RM} str_weld.o str_weld.o.d
	${KCC} ${CCNFLAGS} -g3 streams/str_weld.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams ; fi

str_debug.o: streams/str_debug.c
	@${RM} str_debug.o str_debug.o.d
	${KCC} ${CCNFLAGS}  streams/str_debug.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_streams_debug ; fi

dlb.o: streamsm/dlb.c
	@${RM} dlb.o dlb.o.d
	${KCC} ${CCNFLAGS} -g3 streamsm/dlb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlb ; fi

dlpi_data.o: data/dlpi_data.c
	@${RM} dlpi_data.o dlpi_data.o.d
	${KCC} ${CCNFLAGS}  data/dlpi_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

dl.o: streamsm/dlpi/dl.c
	@${RM} dl.o dl.o.d
	${KCC} ${CCNFLAGS} -g3 streamsm/dlpi/dl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

dlhash.o: streamsm/dlpi/dlhash.c
	@${RM} dlhash.o dlhash.o.d
	${KCC} ${CCNFLAGS}  streamsm/dlpi/dlhash.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

dlioctl.o: streamsm/dlpi/dlioctl.c
	@${RM} dlioctl.o dlioctl.o.d
	${KCC} ${CCNFLAGS}  streamsm/dlpi/dlioctl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

dlprim.o: streamsm/dlpi/dlprim.c
	@${RM} dlprim.o dlprim.o.d
	${KCC} ${CCNFLAGS}  streamsm/dlpi/dlprim.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

dlproc.o: streamsm/dlpi/dlproc.c
	@${RM} dlproc.o dlproc.o.d
	${KCC} ${CCNFLAGS}  streamsm/dlpi/dlproc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

dltimer.o: streamsm/dlpi/dltimer.c
	@${RM} dltimer.o dltimer.o.d
	${KCC} ${CCNFLAGS}  streamsm/dlpi/dltimer.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

dlutil.o: streamsm/dlpi/dlutil.c
	@${RM} dlutil.o dlutil.o.d
	${KCC} ${CCNFLAGS}  streamsm/dlpi/dlutil.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dlpi ; fi

ifnet.o: streamsm/ifnet.c
	@${RM} ifnet.o ifnet.o.d
	${KCC} ${CCNFLAGS}  streamsm/ifnet.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ifnet ; fi

kinfo.o: streamsm/kinfo.c
	@${RM} kinfo.o kinfo.o.d
	${KCC} ${CCNFLAGS}  streamsm/kinfo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kinfo ; fi

log.o: streamsm/log.c
	@${RM} log.o log.o.d
	${KCC} ${CCNFLAGS}  streamsm/log.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_strstd ; fi

sad.o: streamsm/sad.c
	@${RM} sad.o sad.o.d
	${KCC} ${CCNFLAGS}  streamsm/sad.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_strstd ; fi

standard.o: streamsm/standard.c
	@${RM} standard.o standard.o.d
	${KCC} ${CCNFLAGS}  streamsm/standard.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_strstd ; fi

svvs.o: streamsm/svvs.c
	@${RM} svvs.o svvs.o.d
	${KCC} ${CCNFLAGS}  streamsm/svvs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_svvs ; fi

timod.o: streamsm/timod.c
	@${RM} timod.o timod.o.d
	${KCC} ${CCNFLAGS}  streamsm/timod.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_timod ; fi

tirdwr.o: streamsm/tirdwr.c
	@${RM} tirdwr.o tirdwr.o.d
	${KCC} ${CCNFLAGS}  streamsm/tirdwr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_tirdwr ; fi

ldtty.o: tty/ldtty.c
	@${RM} ldtty.o ldtty.o.d
	${KCC} ${CCNFLAGS} -g3 tty/ldtty.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ldtty ; fi

ldtty_compat.o: tty/ldtty_compat.c
	@${RM} ldtty_compat.o ldtty_compat.o.d
	${KCC} ${CCNFLAGS}  tty/ldtty_compat.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ldtty ; fi

ldtty_euc.o: tty/ldtty_euc.c
	@${RM} ldtty_euc.o ldtty_euc.o.d
	${KCC} ${CCNFLAGS}  tty/ldtty_euc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ldtty ; fi

xtiso.o: streamsm/xtiso.c
	@${RM} xtiso.o xtiso.o.d
	${KCC} ${CCNFLAGS} -g3 streamsm/xtiso.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_xtiso ; fi

pty.o: tty/pty.c
	@${RM} pty.o pty.o.d
	${KCC} ${CCNFLAGS} -g3 tty/pty.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pts ; fi

mfs_vfsops.o: ufs/mfs_vfsops.c
	@${RM} mfs_vfsops.o mfs_vfsops.o.d
	${KCC} ${CCNFLAGS}  ufs/mfs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

mfs_vnops.o: ufs/mfs_vnops.c
	@${RM} mfs_vnops.o mfs_vnops.o.d
	${KCC} ${CCNFLAGS}  ufs/mfs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_alloc.o: ufs/ufs_alloc.c
	@${RM} ufs_alloc.o ufs_alloc.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_alloc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_bmap.o: ufs/ufs_bmap.c
	@${RM} ufs_bmap.o ufs_bmap.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_bmap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_cfg.o: ufs/ufs_cfg.c
	@${RM} ufs_cfg.o ufs_cfg.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_disksubr.o: ufs/ufs_disksubr.c
	@${RM} ufs_disksubr.o ufs_disksubr.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_disksubr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_inode.o: ufs/ufs_inode.c
	@${RM} ufs_inode.o ufs_inode.o.d
	${KCC} ${CCNFLAGS} -g3 ufs/ufs_inode.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_lookup.o: ufs/ufs_lookup.c
	@${RM} ufs_lookup.o ufs_lookup.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_lookup.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_physio.o: ufs/ufs_physio.c
	@${RM} ufs_physio.o ufs_physio.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_physio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_proplist.o: ufs/ufs_proplist.c
	@${RM} ufs_proplist.o ufs_proplist.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_proplist.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_subr.o: ufs/ufs_subr.c
	@${RM} ufs_subr.o ufs_subr.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_tables.o: ufs/ufs_tables.c
	@${RM} ufs_tables.o ufs_tables.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_tables.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_vfsops.o: ufs/ufs_vfsops.c
	@${RM} ufs_vfsops.o ufs_vfsops.o.d
	${KCC} ${CCNFLAGS}  ufs/ufs_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_vnops.o: ufs/ufs_vnops.c
	@${RM} ufs_vnops.o ufs_vnops.o.d
	${KCC} ${CCNFLAGS} -g3 ufs/ufs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

ufs_quota.o: ufs/ufs_quota.c
	@${RM} ufs_quota.o ufs_quota.o.d
	${KCC} ${CCNFLAGS} -g3 ufs/ufs_quota.c

uipc_proto.o: bsd/uipc_proto.c
	@${RM} uipc_proto.o uipc_proto.o.d
	${KCC} ${CCNFLAGS}  bsd/uipc_proto.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uipc ; fi

uipc_usrreq.o: bsd/uipc_usrreq.c
	@${RM} uipc_usrreq.o uipc_usrreq.o.d
	${KCC} ${CCNFLAGS}  bsd/uipc_usrreq.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_uipc ; fi

dead_vfsops.o: vfs/dead_vfsops.c
	@${RM} dead_vfsops.o dead_vfsops.o.d
	${KCC} ${CCNFLAGS}  vfs/dead_vfsops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

dead_vnops.o: vfs/dead_vnops.c
	@${RM} dead_vnops.o dead_vnops.o.d
	${KCC} ${CCNFLAGS}  vfs/dead_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

fifo_vnops.o: vfs/fifo_vnops.c
	@${RM} fifo_vnops.o fifo_vnops.o.d
	${KCC} ${CCNFLAGS} -g3 vfs/fifo_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

spec_vnops.o: vfs/spec_vnops.c
	@${RM} spec_vnops.o spec_vnops.o.d
	${KCC} ${CCNFLAGS}  vfs/spec_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ufs ; fi

vfs_bio.o: vfs/vfs_bio.c
	@${RM} vfs_bio.o vfs_bio.o.d
	${KCC} ${CCNFLAGS} -g3 vfs/vfs_bio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_cache.o: vfs/vfs_cache.c
	@${RM} vfs_cache.o vfs_cache.o.d
	${KCC} ${CCNFLAGS} -g3 vfs/vfs_cache.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_cfg.o: vfs/vfs_cfg.c
	@${RM} vfs_cfg.o vfs_cfg.o.d
	${KCC} ${CCNFLAGS}  vfs/vfs_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_flock.o: vfs/vfs_flock.c
	@${RM} vfs_flock.o vfs_flock.o.d
	${KCC} ${CCNFLAGS} -g3 vfs/vfs_flock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_lookup.o: vfs/vfs_lookup.c
	@${RM} vfs_lookup.o vfs_lookup.o.d
	${KCC} ${CCNFLAGS}  vfs/vfs_lookup.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_subr.o: vfs/vfs_subr.c
	@${RM} vfs_subr.o vfs_subr.o.d
	${KCC} ${CCNFLAGS} -g3 vfs/vfs_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_syscalls.o: vfs/vfs_syscalls.c
	@${RM} vfs_syscalls.o vfs_syscalls.o.d
	${KCC} ${CCNFLAGS}  vfs/vfs_syscalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_ubc.o: vfs/vfs_ubc.c
	@${RM} vfs_ubc.o vfs_ubc.o.d
	${KCC} ${CCNFLAGS}  vfs/vfs_ubc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

vfs_vnops.o: vfs/vfs_vnops.c
	@${RM} vfs_vnops.o vfs_vnops.o.d
	${KCC} ${CCNFLAGS}  vfs/vfs_vnops.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vfs ; fi

k_mape_inv.o: vm/k_mape_inv.c
	@${RM} k_mape_inv.o k_mape_inv.o.d
	${KCC} ${CCNFLAGS}  vm/k_mape_inv.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

k_mape_io.o: vm/k_mape_io.c
	@${RM} k_mape_io.o k_mape_io.o.d
	${KCC} ${CCNFLAGS}  vm/k_mape_io.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

k_mape_mem.o: vm/k_mape_mem.c
	@${RM} k_mape_mem.o k_mape_mem.o.d
	${KCC} ${CCNFLAGS}  vm/k_mape_mem.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

u_mape_anon.o: vm/u_mape_anon.c
	@${RM} u_mape_anon.o u_mape_anon.o.d
	${KCC} ${CCNFLAGS}  vm/u_mape_anon.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

u_mape_dev.o: vm/u_mape_dev.c
	@${RM} u_mape_dev.o u_mape_dev.o.d
	${KCC} ${CCNFLAGS}  vm/u_mape_dev.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

u_mape_seg.o: vm/u_mape_seg.c
	@${RM} u_mape_seg.o u_mape_seg.o.d
	${KCC} ${CCNFLAGS}  vm/u_mape_seg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

u_mape_shm.o: vm/u_mape_shm.c
	@${RM} u_mape_shm.o u_mape_shm.o.d
	${KCC} ${CCNFLAGS}  vm/u_mape_shm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

u_mape_ssm.o: vm/u_mape_ssm.c
	@${RM} u_mape_ssm.o u_mape_ssm.o.d
	${KCC} ${CCNFLAGS}  vm/u_mape_ssm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

u_mape_vp.o: vm/u_mape_vp.c
	@${RM} u_mape_vp.o u_mape_vp.o.d
	${KCC} ${CCNFLAGS}  vm/u_mape_vp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_anon.o: vm/vm_anon.c
	@${RM} vm_anon.o vm_anon.o.d
	${KCC} ${CCNFLAGS} -g3 vm/vm_anon.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_anonpage.o: vm/vm_anonpage.c
	@${RM} vm_anonpage.o vm_anonpage.o.d
	${KCC} ${CCNFLAGS}  vm/vm_anonpage.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_cfg.o: vm/vm_cfg.c
	@${RM} vm_cfg.o vm_cfg.o.d
	${KCC} ${CCNFLAGS}  vm/vm_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_cmap.o: vm/vm_cmap.c
	@${RM} vm_cmap.o vm_cmap.o.d
	${KCC} ${CCNFLAGS}  vm/vm_cmap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_fault.o: vm/vm_fault.c
	@${RM} vm_fault.o vm_fault.o.d
	${KCC} ${CCNFLAGS}  vm/vm_fault.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_kern.o: vm/vm_kern.c
	@${RM} vm_kern.o vm_kern.o.d
	${KCC} ${CCNFLAGS}  vm/vm_kern.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_kmap.o: vm/vm_kmap.c
	@${RM} vm_kmap.o vm_kmap.o.d
	${KCC} ${CCNFLAGS}  vm/vm_kmap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_map.o: vm/vm_map.c
	@${RM} vm_map.o vm_map.o.d
	${KCC} ${CCNFLAGS}  vm/vm_map.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_object.o: vm/vm_object.c
	@${RM} vm_object.o vm_object.o.d
	${KCC} ${CCNFLAGS}  vm/vm_object.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_pagelru.o: vm/vm_pagelru.c
	@${RM} vm_pagelru.o vm_pagelru.o.d
	${KCC} ${CCNFLAGS} -g3 vm/vm_pagelru.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_resident.o: vm/vm_resident.c
	@${RM} vm_resident.o vm_resident.o.d
	${KCC} ${CCNFLAGS} -g3 vm/vm_resident.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_subr.o: vm/vm_subr.c
	@${RM} vm_subr.o vm_subr.o.d
	${KCC} ${CCNFLAGS}  vm/vm_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_swap.o: vm/vm_swap.c
	@${RM} vm_swap.o vm_swap.o.d
	${KCC} ${CCNFLAGS} -g3 vm/vm_swap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_umap.o: vm/vm_umap.c
	@${RM} vm_umap.o vm_umap.o.d
	${KCC} ${CCNFLAGS}  vm/vm_umap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_unix.o: vm/vm_unix.c
	@${RM} vm_unix.o vm_unix.o.d
	${KCC} ${CCNFLAGS}  vm/vm_unix.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_user.o: vm/vm_user.c
	@${RM} vm_user.o vm_user.o.d
	${KCC} ${CCNFLAGS}  vm/vm_user.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vm_vlock.o: vm/vm_vlock.c
	@${RM} vm_vlock.o vm_vlock.o.d
	${KCC} ${CCNFLAGS}  vm/vm_vlock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

vpage.o: vm/vpage.c
	@${RM} vpage.o vpage.o.d
	${KCC} ${CCNFLAGS}  vm/vpage.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vm ; fi

kern_lmf.o: bsd/kern_lmf.c
	@${RM} kern_lmf.o kern_lmf.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_lmf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE__lmf_ ; fi

pckt.o: tty/pckt.c
	@${RM} pckt.o pckt.o.d
	${KCC} ${CCNFLAGS}  tty/pckt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pckt ; fi

kern_ntptime.o: bsd/kern_ntptime.c
	@${RM} kern_ntptime.o kern_ntptime.o.d
	${KCC} ${CCNFLAGS}  bsd/kern_ntptime.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ntp_time ; fi

memlog.o: bsd/memlog.c
	@${RM} memlog.o memlog.o.d
	${KCC} ${CCNFLAGS}  bsd/memlog.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mlog ; fi

subr_mcount.o: bsd/subr_mcount.c
	@${RM} subr_mcount.o subr_mcount.o.d
	${KCC} ${CCNFLAGS}  bsd/subr_mcount.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_profiling ; fi

tty_pty.o: bsd/tty_pty.c
	@${RM} tty_pty.o tty_pty.o.d
	${KCC} ${CCNFLAGS}  bsd/tty_pty.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pty ; fi

prf.o: dec/prf/prf.c
	@${RM} prf.o prf.o.d
	${KCC} ${CCNFLAGS}  dec/prf/prf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_prf ; fi

callout_statistics.o: kern/callout_statistics.c
	@${RM} callout_statistics.o callout_statistics.o.d
	${KCC} ${CCNFLAGS}  kern/callout_statistics.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mach_co_stats ; fi

ipc_statistics.o: kern/ipc_statistics.c
	@${RM} ipc_statistics.o ipc_statistics.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_statistics.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mach_ipc_stats ; fi

gw_screen.o: net/gw_screen.c
	@${RM} gw_screen.o gw_screen.o.d
	${KCC} ${CCNFLAGS}  net/gw_screen.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_gwscreen ; fi

pwrmgr.o: dec/pwrmgr/pwrmgr.c
	@${RM} pwrmgr.o pwrmgr.o.d
	${KCC} ${CCNFLAGS}  dec/pwrmgr/pwrmgr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pwrmgr ; fi

kern_audit.o: dec/sec/kern_audit.c
	@${RM} kern_audit.o kern_audit.o.d
	${KCC} ${CCNFLAGS} -g3 dec/sec/kern_audit.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dec_audit ; fi

kern_auditcalls.o: dec/sec/kern_auditcalls.c
	@${RM} kern_auditcalls.o kern_auditcalls.o.d
	${KCC} ${CCNFLAGS}  dec/sec/kern_auditcalls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dec_audit ; fi

kern_auditdev.o: dec/sec/kern_auditdev.c
	@${RM} kern_auditdev.o kern_auditdev.o.d
	${KCC} ${CCNFLAGS} -g3 dec/sec/kern_auditdev.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dec_audit ; fi

sec_calls.o: sec/sec_calls.c
	@${RM} sec_calls.o sec_calls.o.d
	${KCC} ${CCNFLAGS}  sec/sec_calls.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_base ; fi

sec_socket.o: sec/sec_socket.c
	@${RM} sec_socket.o sec_socket.o.d
	${KCC} ${CCNFLAGS}  sec/sec_socket.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_base ; fi

sec_stream.o: sec/sec_stream.c
	@${RM} sec_stream.o sec_stream.o.d
	${KCC} ${CCNFLAGS}  sec/sec_stream.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_base ; fi

sec_driver.o: sec/sec_driver.c
	@${RM} sec_driver.o sec_driver.o.d
	${KCC} ${CCNFLAGS}  sec/sec_driver.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_driver ; fi

sec_mld.o: sec/sec_mld.c
	@${RM} sec_mld.o sec_mld.o.d
	${KCC} ${CCNFLAGS}  sec/sec_mld.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sec_mld ; fi

spd_pacl.o: sec/spd_pacl.c
	@${RM} spd_pacl.o spd_pacl.o.d
	${KCC} ${CCNFLAGS}  sec/spd_pacl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dec_acl ; fi

dce_acl_stubs.o: sec/dce_acl_stubs.c
	@${RM} dce_acl_stubs.o dce_acl_stubs.o.d
	${KCC} ${CCNFLAGS}  sec/dce_acl_stubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dce_acl_stubs ; fi

spd_cache.o: sec/spd_cache.c
	@${RM} spd_cache.o spd_cache.o.d
	${KCC} ${CCNFLAGS}  sec/spd_cache.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_spd_cache ; fi

acl_stubs.o: sec/acl_stubs.c
	@${RM} acl_stubs.o acl_stubs.o.d
	${KCC} ${CCNFLAGS}  sec/acl_stubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_acl_stubs ; fi

spd_mac.o: sec/spd_mac.c
	@${RM} spd_mac.o spd_mac.o.d
	${KCC} ${CCNFLAGS}  sec/spd_mac.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_spd_mac ; fi

spd_misc.o: sec/spd_misc.c
	@${RM} spd_misc.o spd_misc.o.d
	${KCC} ${CCNFLAGS}  sec/spd_misc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_spd_misc ; fi

kern_memcntl.o: svr4/kern_memcntl.c
	@${RM} kern_memcntl.o kern_memcntl.o.d
	${KCC} ${CCNFLAGS}  svr4/kern_memcntl.c

kern_swapctl.o: svr4/kern_swapctl.c
	@${RM} kern_swapctl.o kern_swapctl.o.d
	${KCC} ${CCNFLAGS} -g3 svr4/kern_swapctl.c

svr_four_init_sysent.c svr_four_syscalls.c svr_four_syscall.h: conf/makesyscalls.ksh \
		conf/svr_four_syscalls.master
	ksh conf/makesyscalls.ksh \
		-hk . conf/svr_four_syscalls.master svr_four_
	rm -f ../include/sys/svr_four_syscall.h
	mv ./svr_four_syscall.h ../include/sys/svr_four_syscall.h

init_sysent.c syscalls.c syscall.h: conf/makesyscalls.ksh \
		conf/syscalls.master
	ksh conf/makesyscalls.ksh \
		-hk . conf/syscalls.master 
	rm -f ../include/sys/syscall.h
	mv ./syscall.h ../include/sys/syscall.h

sysv_init_sysent.c sysv_syscalls.c sysv_syscall.h: conf/makesyscalls.ksh \
		conf/sysv_syscalls.master
	ksh conf/makesyscalls.ksh \
		-hk . conf/sysv_syscalls.master sysv_
	rm -f ../include/sys/sysv_syscall.h
	mv ./sysv_syscall.h ../include/sys/sysv_syscall.h

svid_three_init_sysent.c svid_three_syscalls.c svid_three_syscall.h: conf/makesyscalls.ksh \
		conf/svid_three_syscalls.master
	ksh conf/makesyscalls.ksh \
		-hk . conf/svid_three_syscalls.master svid_three_
	rm -f ../include/sys/svid_three_syscall.h
	mv ./svid_three_syscall.h ../include/sys/svid_three_syscall.h

soe_two_init_sysent.c soe_two_syscalls.c soe_two_syscall.h: conf/makesyscalls.ksh \
		conf/soe_two_syscalls.master
	ksh conf/makesyscalls.ksh \
		-hk . conf/soe_two_syscalls.master soe_two_
	rm -f ../include/sys/soe_two_syscall.h
	mv ./soe_two_syscall.h ../include/sys/soe_two_syscall.h

rt_init_sysent.c rt_syscalls.c rt_syscall.h: conf/makesyscalls.ksh \
		conf/rt_syscalls.master
	ksh conf/makesyscalls.ksh \
		-hk . conf/rt_syscalls.master rt_
	rm -f ../include/sys/rt_syscall.h
	mv ./rt_syscall.h ../include/sys/rt_syscall.h

rt_init_sysent.o: rt_init_sysent.c
	@${RM} rt_init_sysent.o rt_init_sysent.o.d
	${KCC} ${CCNFLAGS}  rt_init_sysent.c

rt_syscalls.o: rt_syscalls.c
	@${RM} rt_syscalls.o rt_syscalls.o.d
	${KCC} ${CCNFLAGS}  rt_syscalls.c

soe_two_init_sysent.o: soe_two_init_sysent.c
	@${RM} soe_two_init_sysent.o soe_two_init_sysent.o.d
	${KCC} ${CCNFLAGS}  soe_two_init_sysent.c

soe_two_syscalls.o: soe_two_syscalls.c
	@${RM} soe_two_syscalls.o soe_two_syscalls.o.d
	${KCC} ${CCNFLAGS}  soe_two_syscalls.c

svid_three_init_sysent.o: svid_three_init_sysent.c
	@${RM} svid_three_init_sysent.o svid_three_init_sysent.o.d
	${KCC} ${CCNFLAGS}  svid_three_init_sysent.c

svid_three_syscalls.o: svid_three_syscalls.c
	@${RM} svid_three_syscalls.o svid_three_syscalls.o.d
	${KCC} ${CCNFLAGS}  svid_three_syscalls.c

svr_four_init_sysent.o: svr_four_init_sysent.c
	@${RM} svr_four_init_sysent.o svr_four_init_sysent.o.d
	${KCC} ${CCNFLAGS}  svr_four_init_sysent.c

svr_four_syscalls.o: svr_four_syscalls.c
	@${RM} svr_four_syscalls.o svr_four_syscalls.o.d
	${KCC} ${CCNFLAGS}  svr_four_syscalls.c

sysv_init_sysent.o: sysv_init_sysent.c
	@${RM} sysv_init_sysent.o sysv_init_sysent.o.d
	${KCC} ${CCNFLAGS}  sysv_init_sysent.c

sysv_syscalls.o: sysv_syscalls.c
	@${RM} sysv_syscalls.o sysv_syscalls.o.d
	${KCC} ${CCNFLAGS}  sysv_syscalls.c

rt_hab_cfg.o: kmod/rt_hab/rt_hab_cfg.c
	@${RM} rt_hab_cfg.o rt_hab_cfg.o.d
	${KCC} ${CCNFLAGS}  kmod/rt_hab/rt_hab_cfg.c

soe_two_cfg.o: kmod/soe2_hab/soe_two_cfg.c
	@${RM} soe_two_cfg.o soe_two_cfg.o.d
	${KCC} ${CCNFLAGS}  kmod/soe2_hab/soe_two_cfg.c

svid_three_cfg.o: kmod/svid3_hab/svid_three_cfg.c
	@${RM} svid_three_cfg.o svid_three_cfg.o.d
	${KCC} ${CCNFLAGS}  kmod/svid3_hab/svid_three_cfg.c

svr_four_cfg.o: kmod/svr4_hab/svr_four_cfg.c
	@${RM} svr_four_cfg.o svr_four_cfg.o.d
	${KCC} ${CCNFLAGS}  kmod/svr4_hab/svr_four_cfg.c

sysv_hab_cfg.o: kmod/sysv_hab/sysv_hab_cfg.c
	@${RM} sysv_hab_cfg.o sysv_hab_cfg.o.d
	${KCC} ${CCNFLAGS}  kmod/sysv_hab/sysv_hab_cfg.c

vfs_svid2calls.o: kmod/sysv_hab/vfs_svid2calls.c
	@${RM} vfs_svid2calls.o vfs_svid2calls.o.d
	${KCC} ${CCNFLAGS}  kmod/sysv_hab/vfs_svid2calls.c

init_main.o: bsd/init_main.c
	@${RM} init_main.o init_main.o.d
	${KCC} ${CCNFLAGS} -g3 bsd/init_main.c

ipc_globals.o: kern/ipc_globals.c
	@${RM} ipc_globals.o ipc_globals.o.d
	${KCC} ${CCNFLAGS}  kern/ipc_globals.c

vm_init.o: vm/vm_init.c
	@${RM} vm_init.o vm_init.o.d
	${KCC} ${CCNFLAGS}  vm/vm_init.c

alpha_exception.o: arch/alpha/alpha_exception.c
	@${RM} alpha_exception.o alpha_exception.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/alpha_exception.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

alpha_init.o: arch/alpha/alpha_init.c
	@${RM} alpha_init.o alpha_init.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/alpha_init.c

alpha_ptrace.o: arch/alpha/alpha_ptrace.c
	@${RM} alpha_ptrace.o alpha_ptrace.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/alpha_ptrace.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

alpha_signal.o: arch/alpha/alpha_signal.c
	@${RM} alpha_signal.o alpha_signal.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/alpha_signal.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

atomic_ops.o: arch/alpha/atomic_ops.s
	@${RM} atomic_ops.o atomic_ops.o.d
	${KCC} ${CCASFLAGS} arch/alpha/atomic_ops.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

byte_swap.o: arch/alpha/byte_swap.s
	@${RM} byte_swap.o byte_swap.o.d
	${KCC} ${CCASFLAGS} arch/alpha/byte_swap.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

clock.o: arch/alpha/clock.c
	@${RM} clock.o clock.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/clock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

coff_subr.o: arch/alpha/coff_subr.c
	@${RM} coff_subr.o coff_subr.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/coff_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

context.o: arch/alpha/context.s
	@${RM} context.o context.o.d
	${KCC} ${CCASFLAGS} arch/alpha/context.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

copy.o: arch/alpha/copy.c
	@${RM} copy.o copy.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/copy.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

cpu.o: arch/alpha/cpu.c
	@${RM} cpu.o cpu.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/cpu.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

crc.o: arch/alpha/crc.c
	@${RM} crc.o crc.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/crc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__divl.o: arch/alpha/__divl.s
	@${RM} __divl.o __divl.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__divl.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__divq.o: arch/alpha/__divq.s
	@${RM} __divq.o __divq.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__divq.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__divlu.o: arch/alpha/__divlu.s
	@${RM} __divlu.o __divlu.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__divlu.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__divqu.o: arch/alpha/__divqu.s
	@${RM} __divqu.o __divqu.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__divqu.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__reml.o: arch/alpha/__reml.s
	@${RM} __reml.o __reml.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__reml.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__remq.o: arch/alpha/__remq.s
	@${RM} __remq.o __remq.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__remq.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__remlu.o: arch/alpha/__remlu.s
	@${RM} __remlu.o __remlu.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__remlu.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

__remqu.o: arch/alpha/__remqu.s
	@${RM} __remqu.o __remqu.o.d
	${KCC} ${CCASFLAGS} arch/alpha/__remqu.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_div_alpha.o: arch/alpha/ots_div_alpha.s
	@${RM} ots_div_alpha.o ots_div_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_div_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_div_data_alpha.o: arch/alpha/ots_div_data_alpha.s
	@${RM} ots_div_data_alpha.o ots_div_data_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_div_data_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_extv_alpha.o: arch/alpha/ots_extv_alpha.s
	@${RM} ots_extv_alpha.o ots_extv_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_extv_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_extv_vol_alpha.o: arch/alpha/ots_extv_vol_alpha.s
	@${RM} ots_extv_vol_alpha.o ots_extv_vol_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_extv_vol_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_extzv_alpha.o: arch/alpha/ots_extzv_alpha.s
	@${RM} ots_extzv_alpha.o ots_extzv_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_extzv_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_extzv_vol_alpha.o: arch/alpha/ots_extzv_vol_alpha.s
	@${RM} ots_extzv_vol_alpha.o ots_extzv_vol_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_extzv_vol_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_insv_alpha.o: arch/alpha/ots_insv_alpha.s
	@${RM} ots_insv_alpha.o ots_insv_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_insv_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_insv_vol_alpha.o: arch/alpha/ots_insv_vol_alpha.s
	@${RM} ots_insv_vol_alpha.o ots_insv_vol_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_insv_vol_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_location_alpha.o: arch/alpha/ots_location_alpha.s
	@${RM} ots_location_alpha.o ots_location_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_location_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_move_alpha.o: arch/alpha/ots_move_alpha.s
	@${RM} ots_move_alpha.o ots_move_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_move_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_movem_alpha.o: arch/alpha/ots_movem_alpha.s
	@${RM} ots_movem_alpha.o ots_movem_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_movem_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_fill_alpha.o: arch/alpha/ots_fill_alpha.s
	@${RM} ots_fill_alpha.o ots_fill_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_fill_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_zero_alpha.o: arch/alpha/ots_zero_alpha.s
	@${RM} ots_zero_alpha.o ots_zero_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_zero_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_translate_alpha.o: arch/alpha/ots_translate_alpha.s
	@${RM} ots_translate_alpha.o ots_translate_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_translate_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_strcmp_eql_alpha.o: arch/alpha/ots_strcmp_eql_alpha.s
	@${RM} ots_strcmp_eql_alpha.o ots_strcmp_eql_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_strcmp_eql_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_strcmp_eqlp_alpha.o: arch/alpha/ots_strcmp_eqlp_alpha.s
	@${RM} ots_strcmp_eqlp_alpha.o ots_strcmp_eqlp_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_strcmp_eqlp_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_strcmp_leq_alpha.o: arch/alpha/ots_strcmp_leq_alpha.s
	@${RM} ots_strcmp_leq_alpha.o ots_strcmp_leq_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_strcmp_leq_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_strcmp_leqp_alpha.o: arch/alpha/ots_strcmp_leqp_alpha.s
	@${RM} ots_strcmp_leqp_alpha.o ots_strcmp_leqp_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_strcmp_leqp_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_strcmp_lss_alpha.o: arch/alpha/ots_strcmp_lss_alpha.s
	@${RM} ots_strcmp_lss_alpha.o ots_strcmp_lss_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_strcmp_lss_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ots_strcmp_lssp_alpha.o: arch/alpha/ots_strcmp_lssp_alpha.s
	@${RM} ots_strcmp_lssp_alpha.o ots_strcmp_lssp_alpha.o.d
	${KCC} ${CCASFLAGS} arch/alpha/ots_strcmp_lssp_alpha.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

dumpsys.o: arch/alpha/dumpsys.c
	@${RM} dumpsys.o dumpsys.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/dumpsys.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

entry.o: arch/alpha/entry.s
	@${RM} entry.o entry.o.d
	${KCC} ${CCASFLAGS} arch/alpha/entry.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

exec_config.o: arch/alpha/exec_config.c
	@${RM} exec_config.o exec_config.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/exec_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

exec_subr.o: arch/alpha/exec_subr.c
	@${RM} exec_subr.o exec_subr.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/exec_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

fastcopy.o: arch/alpha/fastcopy.s
	@${RM} fastcopy.o fastcopy.o.d
	${KCC} ${CCASFLAGS} arch/alpha/fastcopy.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

in_checksum.o: arch/alpha/in_checksum.s
	@${RM} in_checksum.o in_checksum.o.d
	${KCC} ${CCASFLAGS} arch/alpha/in_checksum.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

in_cksum.o: arch/alpha/in_cksum.c
	@${RM} in_cksum.o in_cksum.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/in_cksum.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_in_cksum ; fi

intr.o: arch/alpha/intr.c
	@${RM} intr.o intr.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/intr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

kernargs.o: arch/alpha/kernargs.c
	@${RM} kernargs.o kernargs.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/kernargs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

locore.o: arch/alpha/locore.s
	@${RM} locore.o locore.o.d
	${KCC} ${CCASFLAGS} arch/alpha/locore.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

lockprim.o: arch/alpha/lockprim.s
	@${RM} lockprim.o lockprim.o.d
	${KCC} ${CCASFLAGS} arch/alpha/lockprim.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

addupc.o: arch/alpha/addupc.s
	@${RM} addupc.o addupc.o.d
	${KCC} ${CCASFLAGS} arch/alpha/addupc.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

machdep.o: arch/alpha/machdep.c
	@${RM} machdep.o machdep.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/machdep.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

mem.o: arch/alpha/mem.c
	@${RM} mem.o mem.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/mem.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

micro_time.o: arch/alpha/micro_time.c
	@${RM} micro_time.o micro_time.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/micro_time.c

pfm.o: arch/alpha/pfm.c
	@${RM} pfm.o pfm.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/pfm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pfm ; fi

ovbcopy.o: arch/alpha/ovbcopy.c
	@${RM} ovbcopy.o ovbcopy.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/ovbcopy.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

pal_lib.o: arch/alpha/pal_lib.s
	@${RM} pal_lib.o pal_lib.o.d
	${KCC} ${CCASFLAGS} arch/alpha/pal_lib.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

pcb.o: arch/alpha/pcb.c
	@${RM} pcb.o pcb.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/pcb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

pmap.o: arch/alpha/pmap.c
	@${RM} pmap.o pmap.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/pmap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alphapmap ; fi

pmap_debug.o: arch/alpha/pmap_debug.c
	@${RM} pmap_debug.o pmap_debug.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/pmap_debug.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alphapmap ; fi

pmap_update.o: arch/alpha/pmap_update.c
	@${RM} pmap_update.o pmap_update.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/pmap_update.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alphapmap ; fi

pmap_init.o: arch/alpha/pmap_init.c
	@${RM} pmap_init.o pmap_init.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/pmap_init.c

prom.o: arch/alpha/prom.c
	@${RM} prom.o prom.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/prom.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

startup.o: arch/alpha/startup.c
	@${RM} startup.o startup.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/startup.c

scb.o: arch/alpha/scb.s
	@${RM} scb.o scb.o.d
	${KCC} ${CCASFLAGS} arch/alpha/scb.s

spl.o: arch/alpha/spl.s
	@${RM} spl.o spl.o.d
	${KCC} ${CCASFLAGS} arch/alpha/spl.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

super.o: arch/alpha/super.c
	@${RM} super.o super.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/super.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

syscall_trap.o: arch/alpha/syscall_trap.c
	@${RM} syscall_trap.o syscall_trap.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/syscall_trap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

trap.o: arch/alpha/trap.c
	@${RM} trap.o trap.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/trap.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

softfp.o: arch/alpha/softfp.c
	@${RM} softfp.o softfp.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/softfp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ieee_float_math.o: arch/alpha/ieee_float_math.c
	@${RM} ieee_float_math.o ieee_float_math.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/ieee_float_math.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

64bit_math.o: arch/alpha/64bit_math.c
	@${RM} 64bit_math.o 64bit_math.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/64bit_math.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

bootio.o: arch/alpha/bootio.c
	@${RM} bootio.o bootio.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/bootio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

bootio_subrs.o: arch/alpha/bootio_subrs.c
	@${RM} bootio_subrs.o bootio_subrs.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/bootio_subrs.c

bootio_net.o: dec/sas/bootio_net.c
	@${RM} bootio_net.o bootio_net.o.d
	${KCC} ${CCNFLAGS}  dec/sas/bootio_net.c

io.o: dec/sas/io.c
	@${RM} io.o io.o.d
	${KCC} ${CCNFLAGS}  dec/sas/io.c

sys.o: dec/sas/sys.c
	@${RM} sys.o sys.o.d
	${KCC} ${CCNFLAGS}  dec/sas/sys.c

sys_advfs.o: dec/sas/sys_advfs.c
	@${RM} sys_advfs.o sys_advfs.o.d
	${KCC} ${CCNFLAGS}  dec/sas/sys_advfs.c

sys_cdfs.o: dec/sas/sys_cdfs.c
	@${RM} sys_cdfs.o sys_cdfs.o.d
	${KCC} ${CCNFLAGS}  dec/sas/sys_cdfs.c

fp_ieee.o: arch/alpha/fp/fp_ieee.c
	@${RM} fp_ieee.o fp_ieee.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_ieee.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_ieee_handler.o: arch/alpha/fp/fp_ieee_handler.c
	@${RM} fp_ieee_handler.o fp_ieee_handler.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_ieee_handler.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_ascii.o: arch/alpha/fp/fp_ascii.c
	@${RM} fp_ascii.o fp_ascii.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_ascii.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_result.o: arch/alpha/fp/fp_result.c
	@${RM} fp_result.o fp_result.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_result.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_scale.o: arch/alpha/fp/fp_scale.c
	@${RM} fp_scale.o fp_scale.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_scale.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_trigger.o: arch/alpha/fp/fp_trigger.c
	@${RM} fp_trigger.o fp_trigger.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_trigger.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_tables.o: arch/alpha/fp/fp_tables.c
	@${RM} fp_tables.o fp_tables.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_tables.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_emulator.o: arch/alpha/fp/fp_emulator.c
	@${RM} fp_emulator.o fp_emulator.o.d
	${KCC} ${CCFFLAGS}  arch/alpha/fp/fp_emulator.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

fp_emulate.o: arch/alpha/fp/fp_emulate.s
	@${RM} fp_emulate.o fp_emulate.o.d
	${KCC} ${CCASFFLAGS} arch/alpha/fp/fp_emulate.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fp ; fi

ul.o: arch/alpha/ul.c
	@${RM} ul.o ul.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/ul.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

usercopy.o: arch/alpha/usercopy.s
	@${RM} usercopy.o usercopy.o.d
	${KCC} ${CCASFLAGS} arch/alpha/usercopy.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

nofault.o: arch/alpha/nofault.s
	@${RM} nofault.o nofault.o.d
	${KCC} ${CCASFLAGS} arch/alpha/nofault.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

vm_machdep.o: arch/alpha/vm_machdep.c
	@${RM} vm_machdep.o vm_machdep.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/vm_machdep.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

mcount.o: arch/alpha/mcount.s
	@${RM} mcount.o mcount.o.d
	${KCC} ${CCASFLAGS} arch/alpha/mcount.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mcount ; fi

alpha_scrub.o: arch/alpha/alpha_scrub.s
	@${RM} alpha_scrub.o alpha_scrub.o.d
	${KCC} ${CCASFLAGS} arch/alpha/alpha_scrub.s

lww.o: arch/alpha/lww.s
	@${RM} lww.o lww.o.d
	${KCC} ${CCASFLAGS} arch/alpha/lww.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

lwu.o: arch/alpha/lwu.s
	@${RM} lwu.o lwu.o.d
	${KCC} ${CCASFLAGS} arch/alpha/lwu.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

autoconf.o: arch/alpha/hal/autoconf.c
	@${RM} autoconf.o autoconf.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/autoconf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

cons_sw.o: arch/alpha/hal/cons_sw.c
	@${RM} cons_sw.o cons_sw.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/cons_sw.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

console.o: arch/alpha/hal/console.c
	@${RM} console.o console.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/console.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

cpusw.o: arch/alpha/hal/cpusw.c
	@${RM} cpusw.o cpusw.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/cpusw.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

platform_switch.o: arch/alpha/hal/platform_switch.c
	@${RM} platform_switch.o platform_switch.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/platform_switch.c

io_access.o: arch/alpha/hal/io_access.c
	@${RM} io_access.o io_access.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/io_access.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

kn15aa_mult.o: arch/alpha/hal/kn15aa_mult.c
	@${RM} kn15aa_mult.o kn15aa_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn15aa_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn15aa_mult ; fi

kn15aa.o: arch/alpha/hal/kn15aa.c
	@${RM} kn15aa.o kn15aa.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn15aa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn15aa ; fi

kn16aa_mult.o: arch/alpha/hal/kn16aa_mult.c
	@${RM} kn16aa_mult.o kn16aa_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn16aa_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn16aa_mult ; fi

kn16aa.o: arch/alpha/hal/kn16aa.c
	@${RM} kn16aa.o kn16aa.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn16aa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn16aa ; fi

kn430_mult.o: arch/alpha/hal/kn430_mult.c
	@${RM} kn430_mult.o kn430_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn430_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn430_mult ; fi

kn430.o: arch/alpha/hal/kn430.c
	@${RM} kn430.o kn430.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn430.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn430 ; fi

dec4000_cons.o: arch/alpha/hal/dec4000_cons.c
	@${RM} dec4000_cons.o dec4000_cons.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/dec4000_cons.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn430_common ; fi

kn7aa_mult.o: arch/alpha/hal/kn7aa_mult.c
	@${RM} kn7aa_mult.o kn7aa_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn7aa_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn7aa_mult ; fi

kn7aa.o: arch/alpha/hal/kn7aa.c
	@${RM} kn7aa.o kn7aa.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn7aa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn7aa ; fi

lsbinit.o: io/dec/lsb/lsbinit.c
	@${RM} lsbinit.o lsbinit.o.d
	${KCC} ${CCDFLAGS}  io/dec/lsb/lsbinit.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn7aa_common ; fi

lsb_iop.o: io/dec/lsb/lsb_iop.c
	@${RM} lsb_iop.o lsb_iop.o.d
	${KCC} ${CCDFLAGS}  io/dec/lsb/lsb_iop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn7aa_common ; fi

kn8ae_mult.o: arch/alpha/hal/kn8ae_mult.c
	@${RM} kn8ae_mult.o kn8ae_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn8ae_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn8ae_mult ; fi

kn8ae.o: arch/alpha/hal/kn8ae.c
	@${RM} kn8ae.o kn8ae.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn8ae.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn8ae ; fi

tlsbinit.o: io/dec/lsb/tlsbinit.c
	@${RM} tlsbinit.o tlsbinit.o.d
	${KCC} ${CCDFLAGS}  io/dec/lsb/tlsbinit.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn8ae_common ; fi

tlsb_iop.o: io/dec/lsb/tlsb_iop.c
	@${RM} tlsb_iop.o tlsb_iop.o.d
	${KCC} ${CCDFLAGS}  io/dec/lsb/tlsb_iop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn8ae_common ; fi

dc21171_mult.o: arch/alpha/hal/dc21171_mult.c
	@${RM} dc21171_mult.o dc21171_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/dc21171_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dc21171_mult ; fi

dc21171.o: arch/alpha/hal/dc21171.c
	@${RM} dc21171.o dc21171.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/dc21171.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dc21171 ; fi

kn121_mult.o: arch/alpha/hal/kn121_mult.c
	@${RM} kn121_mult.o kn121_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn121_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn121_mult ; fi

kn121.o: arch/alpha/hal/kn121.c
	@${RM} kn121.o kn121.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn121.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn121 ; fi

kn25_mult.o: arch/alpha/hal/kn25_mult.c
	@${RM} kn25_mult.o kn25_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn25_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn25_mult ; fi

kn25.o: arch/alpha/hal/kn25.c
	@${RM} kn25.o kn25.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn25.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn25 ; fi

kn450_mult.o: arch/alpha/hal/kn450_mult.c
	@${RM} kn450_mult.o kn450_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn450_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn450_mult ; fi

kn450.o: arch/alpha/hal/kn450.c
	@${RM} kn450.o kn450.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn450.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn450 ; fi

cbus2_pci_mult.o: arch/alpha/hal/cbus2_pci_mult.c
	@${RM} cbus2_pci_mult.o cbus2_pci_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/cbus2_pci_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cbus2_pci_mult ; fi

cbus2_pci.o: arch/alpha/hal/cbus2_pci.c
	@${RM} cbus2_pci.o cbus2_pci.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/cbus2_pci.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cbus2_pci ; fi

kn470_mult.o: arch/alpha/hal/kn470_mult.c
	@${RM} kn470_mult.o kn470_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn470_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn470_mult ; fi

kn470.o: arch/alpha/hal/kn470.c
	@${RM} kn470.o kn470.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/kn470.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn470 ; fi

kn20aa_mult.o: arch/alpha/hal/kn20aa_mult.c
	@${RM} kn20aa_mult.o kn20aa_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn20aa_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn20aa_mult ; fi

kn20aa.o: arch/alpha/hal/kn20aa.c
	@${RM} kn20aa.o kn20aa.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn20aa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn20aa ; fi

kn22a_mult.o: arch/alpha/hal/kn22a_mult.c
	@${RM} kn22a_mult.o kn22a_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn22a_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn22a_mult ; fi

kn22a.o: arch/alpha/hal/kn22a.c
	@${RM} kn22a.o kn22a.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/kn22a.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn22a ; fi

ebp10_mult.o: arch/alpha/hal/ebp10_mult.c
	@${RM} ebp10_mult.o ebp10_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/ebp10_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebp10_mult ; fi

ebp10.o: arch/alpha/hal/ebp10.c
	@${RM} ebp10.o ebp10.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/ebp10.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebp10 ; fi

eb64p_mult.o: arch/alpha/hal/eb64p_mult.c
	@${RM} eb64p_mult.o eb64p_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/eb64p_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb64p_mult ; fi

eb64p.o: arch/alpha/hal/eb64p.c
	@${RM} eb64p.o eb64p.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/eb64p.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb64p ; fi

eb64p_pallib.o: arch/alpha/hal/eb64p_pallib.s
	@${RM} eb64p_pallib.o eb64p_pallib.o.d
	${KCC} ${CCASFLAGS} arch/alpha/hal/eb64p_pallib.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb64p_pallib ; fi

eb66_mult.o: arch/alpha/hal/eb66_mult.c
	@${RM} eb66_mult.o eb66_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/eb66_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb66_mult ; fi

eb66.o: arch/alpha/hal/eb66.c
	@${RM} eb66.o eb66.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/eb66.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb66 ; fi

eb66_pallib.o: arch/alpha/hal/eb66_pallib.s
	@${RM} eb66_pallib.o eb66_pallib.o.d
	${KCC} ${CCASFLAGS} arch/alpha/hal/eb66_pallib.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb66_pallib ; fi

eb164_mult.o: arch/alpha/hal/eb164_mult.c
	@${RM} eb164_mult.o eb164_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/eb164_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb164_mult ; fi

eb164.o: arch/alpha/hal/eb164.c
	@${RM} eb164.o eb164.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/eb164.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb164 ; fi

eb164_pallib.o: arch/alpha/hal/eb164_pallib.s
	@${RM} eb164_pallib.o eb164_pallib.o.d
	${KCC} ${CCASFLAGS} arch/alpha/hal/eb164_pallib.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eb164_pallib ; fi

ebv10_mult.o: arch/alpha/hal/ebv10_mult.c
	@${RM} ebv10_mult.o ebv10_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/ebv10_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv10_mult ; fi

ebv10.o: arch/alpha/hal/ebv10.c
	@${RM} ebv10.o ebv10.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/ebv10.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv10 ; fi

ebv10_pallib.o: arch/alpha/hal/ebv10_pallib.s
	@${RM} ebv10_pallib.o ebv10_pallib.o.d
	${KCC} ${CCASFLAGS} arch/alpha/hal/ebv10_pallib.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv10_common ; fi

ds1386clock_mult.o: arch/alpha/hal/ds1386clock_mult.c
	@${RM} ds1386clock_mult.o ds1386clock_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ds1386clock_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ds1386clock_mult ; fi

ds1386clock.o: arch/alpha/hal/ds1386clock.c
	@${RM} ds1386clock.o ds1386clock.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ds1386clock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ds1386 ; fi

ebv14_mult.o: arch/alpha/hal/ebv14_mult.c
	@${RM} ebv14_mult.o ebv14_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebv14_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv14_mult ; fi

ebv14.o: arch/alpha/hal/ebv14.c
	@${RM} ebv14.o ebv14.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebv14.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv14 ; fi

ebv14_pallib.o: arch/alpha/hal/ebv14_pallib.s
	@${RM} ebv14_pallib.o ebv14_pallib.o.d
	${KCC} ${CCASFLAGS} arch/alpha/hal/ebv14_pallib.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv14_pallib ; fi

ebv16_mult.o: arch/alpha/hal/ebv16_mult.c
	@${RM} ebv16_mult.o ebv16_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebv16_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv16_mult ; fi

ebv16.o: arch/alpha/hal/ebv16.c
	@${RM} ebv16.o ebv16.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebv16.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv16 ; fi

ebv16_pallib.o: arch/alpha/hal/ebv16_pallib.s
	@${RM} ebv16_pallib.o ebv16_pallib.o.d
	${KCC} ${CCASFLAGS} arch/alpha/hal/ebv16_pallib.s
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebv16_pallib ; fi

ebm10_mult.o: arch/alpha/hal/ebm10_mult.c
	@${RM} ebm10_mult.o ebm10_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebm10_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebm10_mult ; fi

ebm10.o: arch/alpha/hal/ebm10.c
	@${RM} ebm10.o ebm10.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebm10.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebm10 ; fi

ebm20_mult.o: arch/alpha/hal/ebm20_mult.c
	@${RM} ebm20_mult.o ebm20_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebm20_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebm20_mult ; fi

ebm20.o: arch/alpha/hal/ebm20.c
	@${RM} ebm20.o ebm20.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ebm20.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebm20 ; fi

dec7000_cons.o: arch/alpha/hal/dec7000_cons.c
	@${RM} dec7000_cons.o dec7000_cons.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/dec7000_cons.c

ruby_common_mult.o: arch/alpha/hal/ruby_common_mult.c
	@${RM} ruby_common_mult.o ruby_common_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ruby_common_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ruby_common_mult ; fi

ruby_common.o: arch/alpha/hal/ruby_common.c
	@${RM} ruby_common.o ruby_common.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/ruby_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ruby_common ; fi

kn300_mult.o: arch/alpha/hal/kn300_mult.c
	@${RM} kn300_mult.o kn300_mult.o.d
	${KCC} ${CCNFLAGS} -O0 arch/alpha/hal/kn300_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn300_mult ; fi

kn300.o: arch/alpha/hal/kn300.c
	@${RM} kn300.o kn300.o.d
	${KCC} ${CCNFLAGS} -O0 arch/alpha/hal/kn300.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn300 ; fi

kn600_mult.o: arch/alpha/hal/kn600_mult.c
	@${RM} kn600_mult.o kn600_mult.o.d
	${KCC} ${CCNFLAGS} -O0 arch/alpha/hal/kn600_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn600_mult ; fi

kn600.o: arch/alpha/hal/kn600.c
	@${RM} kn600.o kn600.o.d
	${KCC} ${CCNFLAGS} -O0 arch/alpha/hal/kn600.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kn600 ; fi

ebm30_mult.o: arch/alpha/hal/ebm30_mult.c
	@${RM} ebm30_mult.o ebm30_mult.o.d
	${KCC} ${CCNFLAGS} -O0 arch/alpha/hal/ebm30_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebm30_mult ; fi

ebm30.o: arch/alpha/hal/ebm30.c
	@${RM} ebm30.o ebm30.o.d
	${KCC} ${CCNFLAGS} -O0 arch/alpha/hal/ebm30.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ebm30 ; fi

alphabook_mult.o: arch/alpha/hal/alphabook_mult.c
	@${RM} alphabook_mult.o alphabook_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/alphabook_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_alphabook_mult ; fi

alphabook.o: arch/alpha/hal/alphabook.c
	@${RM} alphabook.o alphabook.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/alphabook.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_alphabook ; fi

mcbus.o: arch/alpha/hal/mcbus.c
	@${RM} mcbus.o mcbus.o.d
	${KCC} ${CCNFLAGS} -O0 arch/alpha/hal/mcbus.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mcbus ; fi

mcpcia_mult.o: io/dec/pci/mcpcia_mult.c
	@${RM} mcpcia_mult.o mcpcia_mult.o.d
	${KCC} ${CCNFLAGS}  io/dec/pci/mcpcia_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mcpcia_mult ; fi

mcpcia.o: io/dec/pci/mcpcia.c
	@${RM} mcpcia.o mcpcia.o.d
	${KCC} ${CCNFLAGS}  io/dec/pci/mcpcia.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mcpcia ; fi

dc104x.o: arch/alpha/hal/dc104x.c
	@${RM} dc104x.o dc104x.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/dc104x.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dc104x ; fi

dc104x_mult.o: arch/alpha/hal/dc104x_mult.c
	@${RM} dc104x_mult.o dc104x_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/dc104x_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dc104x_mult ; fi

linear_io_access.o: arch/alpha/hal/linear_io_access.c
	@${RM} linear_io_access.o linear_io_access.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/linear_io_access.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_linear_io_access ; fi

linear_io_access_mult.o: arch/alpha/hal/linear_io_access_mult.c
	@${RM} linear_io_access_mult.o linear_io_access_mult.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/linear_io_access_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_linear_io_access_mult ; fi

hal_lmf.o: arch/alpha/hal/hal_lmf.c
	@${RM} hal_lmf.o hal_lmf.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/hal_lmf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

hal_sysinfo.o: arch/alpha/hal/hal_sysinfo.c
	@${RM} hal_sysinfo.o hal_sysinfo.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/hal_sysinfo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

pc_bell_mult.o: arch/alpha/hal/pc_bell_mult.c
	@${RM} pc_bell_mult.o pc_bell_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/pc_bell_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pc_bell_mult ; fi

pc_bell.o: arch/alpha/hal/pc_bell.c
	@${RM} pc_bell.o pc_bell.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/pc_bell.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pc_bell ; fi

sio.o: arch/alpha/hal/sio.c
	@${RM} sio.o sio.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/sio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sio ; fi

dma_direct_map.o: arch/alpha/hal/dma_direct_map.c
	@${RM} dma_direct_map.o dma_direct_map.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/dma_direct_map.c

82357_pic.o: arch/alpha/hal/82357_pic.c
	@${RM} 82357_pic.o 82357_pic.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/82357_pic.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pic ; fi

mc146818clock_mult.o: arch/alpha/hal/mc146818clock_mult.c
	@${RM} mc146818clock_mult.o mc146818clock_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/mc146818clock_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mc146818_mult ; fi

mc146818clock.o: arch/alpha/hal/mc146818clock.c
	@${RM} mc146818clock.o mc146818clock.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/mc146818clock.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mc146818 ; fi

lca_mult.o: arch/alpha/hal/lca_mult.c
	@${RM} lca_mult.o lca_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/lca_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lca_mult ; fi

lca.o: arch/alpha/hal/lca.c
	@${RM} lca.o lca.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/lca.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lca ; fi

apecs_mult.o: arch/alpha/hal/apecs_mult.c
	@${RM} apecs_mult.o apecs_mult.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/apecs_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_apecs_mult ; fi

apecs.o: arch/alpha/hal/apecs.c
	@${RM} apecs.o apecs.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/apecs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_apecs ; fi

ebv10_vme.o: io/dec/vme/ebv10_vme.c
	@${RM} ebv10_vme.o ebv10_vme.o.d
	${KCC} ${CCNFLAGS}  io/dec/vme/ebv10_vme.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vba_vipvic ; fi

univ_vme.o: io/dec/vme/univ_vme.c
	@${RM} univ_vme.o univ_vme.o.d
	${KCC} ${CCNFLAGS}  io/dec/vme/univ_vme.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vba_univ ; fi

kdebug_ace_cons.o: arch/alpha/kdebug_ace_cons.c
	@${RM} kdebug_ace_cons.o kdebug_ace_cons.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/kdebug_ace_cons.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_misc.o: arch/alpha/kdebug_misc.c
	@${RM} kdebug_misc.o kdebug_misc.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/kdebug_misc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_cobra_cons.o: arch/alpha/kdebug_cobra_cons.c
	@${RM} kdebug_cobra_cons.o kdebug_cobra_cons.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/kdebug_cobra_cons.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_gbus_cons.o: arch/alpha/kdebug_gbus_cons.c
	@${RM} kdebug_gbus_cons.o kdebug_gbus_cons.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/kdebug_gbus_cons.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_scc_cons.o: arch/alpha/kdebug_scc_cons.c
	@${RM} kdebug_scc_cons.o kdebug_scc_cons.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/kdebug_scc_cons.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

kdebug_iscc_cons.o: arch/alpha/kdebug_iscc_cons.c
	@${RM} kdebug_iscc_cons.o kdebug_iscc_cons.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/kdebug_iscc_cons.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_alpha_aout.o: arch/alpha/db_alpha_aout.c
	@${RM} db_alpha_aout.o db_alpha_aout.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/db_alpha_aout.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_alpha_inst.o: arch/alpha/db_alpha_inst.c
	@${RM} db_alpha_inst.o db_alpha_inst.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/db_alpha_inst.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_alpha_sym.o: arch/alpha/db_alpha_sym.c
	@${RM} db_alpha_sym.o db_alpha_sym.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/db_alpha_sym.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_commands.o: arch/alpha/db_commands.c
	@${RM} db_commands.o db_commands.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/db_commands.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_disasm.o: arch/alpha/db_disasm.c
	@${RM} db_disasm.o db_disasm.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/db_disasm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_interface.o: arch/alpha/db_interface.c
	@${RM} db_interface.o db_interface.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/db_interface.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

db_trace.o: arch/alpha/db_trace.c
	@${RM} db_trace.o db_trace.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/db_trace.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kdebug ; fi

devz.o: arch/alpha/devz.c
	@${RM} devz.o devz.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/devz.c

driver_support.o: io/common/driver_support.c
	@${RM} driver_support.o driver_support.o.d
	${KCC} ${CCNFLAGS}  io/common/driver_support.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ldbl_driver_support.o: io/common/ldbl_driver_support.c
	@${RM} ldbl_driver_support.o ldbl_driver_support.o.d
	${KCC} ${CCNFLAGS}  io/common/ldbl_driver_support.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

ldbl_controller_support.o: io/common/ldbl_controller_support.c
	@${RM} ldbl_controller_support.o ldbl_controller_support.o.d
	${KCC} ${CCNFLAGS}  io/common/ldbl_controller_support.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

stanza_resolver.o: io/common/stanza_resolver.c
	@${RM} stanza_resolver.o stanza_resolver.o.d
	${KCC} ${CCNFLAGS}  io/common/stanza_resolver.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

topology.o: io/common/topology.c
	@${RM} topology.o topology.o.d
	${KCC} ${CCNFLAGS}  io/common/topology.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

handler.o: io/common/handler.c
	@${RM} handler.o handler.o.d
	${KCC} ${CCNFLAGS}  io/common/handler.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

tty_def.o: io/common/tty_def.c
	@${RM} tty_def.o tty_def.o.d
	${KCC} ${CCNFLAGS}  io/common/tty_def.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

io_resource.o: io/common/io_resource.c
	@${RM} io_resource.o io_resource.o.d
	${KCC} ${CCNFLAGS}  io/common/io_resource.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

lsbmem_mult.o: io/dec/lsb/lsbmem_mult.c
	@${RM} lsbmem_mult.o lsbmem_mult.o.d
	${KCC} ${CCNFLAGS}  io/dec/lsb/lsbmem_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsbmem_mult ; fi

lsbmem.o: io/dec/lsb/lsbmem.c
	@${RM} lsbmem.o lsbmem.o.d
	${KCC} ${CCNFLAGS}  io/dec/lsb/lsbmem.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsbmem ; fi

cma_dd.o: io/common/cma_dd.c
	@${RM} cma_dd.o cma_dd.o.d
	${KCC} ${CCNFLAGS}  io/common/cma_dd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cma_dd ; fi

cam_disk.o: io/cam/cam_disk.c
	@${RM} cam_disk.o cam_disk.o.d
	${KCC} ${CCNFLAGS} -g3 io/cam/cam_disk.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_disk ; fi

cam_tape.o: io/cam/cam_tape.c
	@${RM} cam_tape.o cam_tape.o.d
	${KCC} ${CCNFLAGS} -g3 io/cam/cam_tape.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_tape ; fi

cam_logger.o: io/cam/cam_logger.c
	@${RM} cam_logger.o cam_logger.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/cam_logger.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

cam_special.o: io/cam/cam_special.c
	@${RM} cam_special.o cam_special.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/cam_special.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

ccfg.o: io/cam/ccfg.c
	@${RM} ccfg.o ccfg.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/ccfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

camdb.o: io/cam/camdb.c
	@${RM} camdb.o camdb.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/camdb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

pdrv_common.o: io/cam/pdrv_common.c
	@${RM} pdrv_common.o pdrv_common.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/pdrv_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

special_audio.o: io/cam/special_audio.c
	@${RM} special_audio.o special_audio.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/special_audio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

special_direct.o: io/cam/special_direct.c
	@${RM} special_direct.o special_direct.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/special_direct.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

special_generic.o: io/cam/special_generic.c
	@${RM} special_generic.o special_generic.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/special_generic.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

special_sequential.o: io/cam/special_sequential.c
	@${RM} special_sequential.o special_sequential.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/special_sequential.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

uagt.o: io/cam/uagt.c
	@${RM} uagt.o uagt.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/uagt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

xpt.o: io/cam/xpt.c
	@${RM} xpt.o xpt.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/xpt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

dme_null.o: io/cam/dme_null.c
	@${RM} dme_null.o dme_null.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/dme_null.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

sim_common.o: io/cam/sim_common.c
	@${RM} sim_common.o sim_common.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/sim_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

cam_eei.o: io/cam/cam_eei.c
	@${RM} cam_eei.o cam_eei.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/cam_eei.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

cam_rci.o: io/cam/cam_rci.c
	@${RM} cam_rci.o cam_rci.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/cam_rci.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam ; fi

sim_xpt.o: io/cam/sim_xpt.c
	@${RM} sim_xpt.o sim_xpt.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/sim_xpt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_sim ; fi

sim_htm.o: io/cam/sim_htm.c
	@${RM} sim_htm.o sim_htm.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/sim_htm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_sim ; fi

sim_as.o: io/cam/sim_as.c
	@${RM} sim_as.o sim_as.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/sim_as.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_sim ; fi

sim_error.o: io/cam/sim_error.c
	@${RM} sim_error.o sim_error.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/sim_error.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_sim ; fi

sim_sched.o: io/cam/sim_sched.c
	@${RM} sim_sched.o sim_sched.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/sim_sched.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_sim ; fi

sim_sm.o: io/cam/sim_sm.c
	@${RM} sim_sm.o sim_sm.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/sim_sm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_sim ; fi

sim_target.o: io/cam/sim_target.c
	@${RM} sim_target.o sim_target.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/sim_target.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_sim ; fi

dme_tcds_94_dma.o: io/cam/dme_tcds_94_dma.c
	@${RM} dme_tcds_94_dma.o dme_tcds_94_dma.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/dme_tcds_94_dma.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_tcds ; fi

tcds_adapt.o: io/cam/tcds_adapt.c
	@${RM} tcds_adapt.o tcds_adapt.o.d
	${KCC} ${CCDFLAGS}  io/cam/tcds_adapt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_tcds ; fi

dme_turbo_94_ram.o: io/cam/dme_turbo_94_ram.c
	@${RM} dme_turbo_94_ram.o dme_turbo_94_ram.o.d
	${KCC} ${CCDFLAGS}  io/cam/dme_turbo_94_ram.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_94 ; fi

dme_common.o: io/cam/dme_common.c
	@${RM} dme_common.o dme_common.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/dme_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_94 ; fi

sim_94_fast.o: io/cam/sim_94_fast.c
	@${RM} sim_94_fast.o sim_94_fast.o.d
	${KCC} ${CCDFLAGS}  io/cam/sim_94_fast.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_94 ; fi

sim_94.o: io/cam/sim_94.c
	@${RM} sim_94.o sim_94.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/sim_94.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_94 ; fi

sim_kn02.o: io/cam/sim_kn02.c
	@${RM} sim_kn02.o sim_kn02.o.d
	${KCC} ${CCDFLAGS}  io/cam/sim_kn02.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_94 ; fi

aha1740.o: io/cam/aha1740.c
	@${RM} aha1740.o aha1740.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/aha1740.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_aha1740 ; fi

sim_ata.o: io/cam/ata/sim_ata.c
	@${RM} sim_ata.o sim_ata.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/ata/sim_ata.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

sim_ata_acer.o: io/cam/ata/sim_ata_acer.c
	@${RM} sim_ata_acer.o sim_ata_acer.o.d
	${KCC} ${CCDFLAGS}  io/cam/ata/sim_ata_acer.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

sim_ata_cmd.o: io/cam/ata/sim_ata_cmd.c
	@${RM} sim_ata_cmd.o sim_ata_cmd.o.d
	${KCC} ${CCDFLAGS}  io/cam/ata/sim_ata_cmd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

sim_ata_cypress.o: io/cam/ata/sim_ata_cypress.c
	@${RM} sim_ata_cypress.o sim_ata_cypress.o.d
	${KCC} ${CCDFLAGS}  io/cam/ata/sim_ata_cypress.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

sim_ata_datatech.o: io/cam/ata/sim_ata_datatech.c
	@${RM} sim_ata_datatech.o sim_ata_datatech.o.d
	${KCC} ${CCDFLAGS}  io/cam/ata/sim_ata_datatech.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

sim_ata_dma.o: io/cam/ata/sim_ata_dma.c
	@${RM} sim_ata_dma.o sim_ata_dma.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/ata/sim_ata_dma.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

sim_ata_symphony.o: io/cam/ata/sim_ata_symphony.c
	@${RM} sim_ata_symphony.o sim_ata_symphony.o.d
	${KCC} ${CCDFLAGS}  io/cam/ata/sim_ata_symphony.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

sim_ata_unknown.o: io/cam/ata/sim_ata_unknown.c
	@${RM} sim_ata_unknown.o sim_ata_unknown.o.d
	${KCC} ${CCDFLAGS}  io/cam/ata/sim_ata_unknown.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_ata ; fi

isp1020.o: io/cam/qlogic/isp1020.c
	@${RM} isp1020.o isp1020.o.d
	${KCC} ${CCNFLAGS} -g3 io/cam/qlogic/isp1020.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_isp ; fi

itpsa.o: io/cam/iti/itpsa.c
	@${RM} itpsa.o itpsa.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/iti/itpsa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_itpsa ; fi

itpsacfg.o: io/cam/iti/itpsacfg.c
	@${RM} itpsacfg.o itpsacfg.o.d
	${KCC} ${CCDFLAGS}  io/cam/iti/itpsacfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_itpsa ; fi

itpsahtm.o: io/cam/iti/itpsahtm.c
	@${RM} itpsahtm.o itpsahtm.o.d
	${KCC} ${CCDFLAGS}  io/cam/iti/itpsahtm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_itpsa ; fi

sim_pza.o: io/cam/spo/sim_pza.c
	@${RM} sim_pza.o sim_pza.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/spo/sim_pza.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_pza ; fi

sim_kztsa.o: io/cam/spo/sim_kztsa.c
	@${RM} sim_kztsa.o sim_kztsa.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/spo/sim_kztsa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_tza ; fi

simport.o: io/cam/spo/simport.c
	@${RM} simport.o simport.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/spo/simport.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_simport ; fi

simport_htm.o: io/cam/spo/simport_htm.c
	@${RM} simport_htm.o simport_htm.o.d
	${KCC} ${CCDFLAGS}  io/cam/spo/simport_htm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_simport ; fi

simport_dme.o: io/cam/spo/simport_dme.c
	@${RM} simport_dme.o simport_dme.o.d
	${KCC} ${CCDFLAGS}  io/cam/spo/simport_dme.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_simport ; fi

simport_subr.o: io/cam/spo/simport_subr.c
	@${RM} simport_subr.o simport_subr.o.d
	${KCC} ${CCDFLAGS}  io/cam/spo/simport_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_simport ; fi

psiop.o: io/cam/siop/psiop.c
	@${RM} psiop.o psiop.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/siop/psiop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_psiop ; fi

psiop_pci.o: io/cam/siop/pci/psiop_pci.c
	@${RM} psiop_pci.o psiop_pci.o.d
	${KCC} ${CCDFLAGS}  io/cam/siop/pci/psiop_pci.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_psiop ; fi

siop.o: io/cam/siop/siop.c
	@${RM} siop.o siop.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/siop/siop.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_siop ; fi

siop_kn430.o: io/cam/siop/kn430/siop_kn430.c
	@${RM} siop_kn430.o siop_kn430.o.d
	${KCC} ${CCDFLAGS}  io/cam/siop/kn430/siop_kn430.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_siop ; fi

skz_config.o: io/cam/xza/skz_config.c
	@${RM} skz_config.o skz_config.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_main.o: io/cam/xza/skz_main.c
	@${RM} skz_main.o skz_main.o.d
	${KCC} ${CCDFLAGS} -g3 io/cam/xza/skz_main.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_dme.o: io/cam/xza/skz_dme.c
	@${RM} skz_dme.o skz_dme.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_dme.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_error.o: io/cam/xza/skz_error.c
	@${RM} skz_error.o skz_error.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_error.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_sched.o: io/cam/xza/skz_sched.c
	@${RM} skz_sched.o skz_sched.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_sched.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_debug.o: io/cam/xza/skz_debug.c
	@${RM} skz_debug.o skz_debug.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_debug.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_nport.o: io/cam/xza/skz_nport.c
	@${RM} skz_nport.o skz_nport.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_nport.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_diag.o: io/cam/xza/skz_diag.c
	@${RM} skz_diag.o skz_diag.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_diag.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

skz_target.o: io/cam/xza/skz_target.c
	@${RM} skz_target.o skz_target.o.d
	${KCC} ${CCDFLAGS}  io/cam/xza/skz_target.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cam_xza ; fi

mips_dummy.o: io/cam/mips_dummy.c
	@${RM} mips_dummy.o mips_dummy.o.d
	${KCC} ${CCNFLAGS}  io/cam/mips_dummy.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

lsb_common.o: io/dec/lsb/lsb_common.c
	@${RM} lsb_common.o lsb_common.o.d
	${KCC} ${CCDFLAGS}  io/dec/lsb/lsb_common.c

fbus.o: io/dec/fbus/fbus.c
	@${RM} fbus.o fbus.o.d
	${KCC} ${CCDFLAGS}  io/dec/fbus/fbus.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fbus ; fi

fbus_loadable.o: io/dec/fbus/fbus_loadable.c
	@${RM} fbus_loadable.o fbus_loadable.o.d
	${KCC} ${CCDFLAGS}  io/dec/fbus/fbus_loadable.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fbus ; fi

flag.o: io/dec/fbus/flag.c
	@${RM} flag.o flag.o.d
	${KCC} ${CCDFLAGS}  io/dec/fbus/flag.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fbus ; fi

mbox.o: io/dec/mbox/mbox.c
	@${RM} mbox.o mbox.o.d
	${KCC} ${CCDFLAGS}  io/dec/mbox/mbox.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mbox ; fi

ibus.o: io/dec/ibus/ibus.c
	@${RM} ibus.o ibus.o.d
	${KCC} ${CCDFLAGS}  io/dec/ibus/ibus.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ibus ; fi

xmiinit.o: io/dec/xmi/xmiinit.c
	@${RM} xmiinit.o xmiinit.o.d
	${KCC} ${CCDFLAGS}  io/dec/xmi/xmiinit.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_xmi ; fi

xlamb.o: io/dec/xmi/xlamb.c
	@${RM} xlamb.o xlamb.o.d
	${KCC} ${CCDFLAGS}  io/dec/xmi/xlamb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_xmi ; fi

if_xna.o: io/dec/netif/if_xna.c
	@${RM} if_xna.o if_xna.o.d
	${KCC} ${CCDFLAGS}  io/dec/netif/if_xna.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_xna ; fi

if_mfa.o: io/dec/netif/if_mfa.c
	@${RM} if_mfa.o if_mfa.o.d
	${KCC} ${CCDFLAGS}  io/dec/netif/if_mfa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mfa ; fi

tc.o: io/dec/tc/tc.c
	@${RM} tc.o tc.o.d
	${KCC} ${CCDFLAGS}  io/dec/tc/tc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_tc ; fi

tc_loadable.o: io/dec/tc/tc_loadable.c
	@${RM} tc_loadable.o tc_loadable.o.d
	${KCC} ${CCDFLAGS}  io/dec/tc/tc_loadable.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_tc ; fi

scc.o: io/dec/tc/scc.c
	@${RM} scc.o scc.o.d
	${KCC} ${CCDFLAGS}  io/dec/tc/scc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_scc ; fi

nvtc.o: io/dec/tc/nvtc.c
	@${RM} nvtc.o nvtc.o.d
	${KCC} ${CCDFLAGS}  io/dec/tc/nvtc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_nvtc ; fi

amd79c30.o: io/dec/tc/amd79c30.c
	@${RM} amd79c30.o amd79c30.o.d
	${KCC} ${CCDFLAGS}  io/dec/tc/amd79c30.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bba ; fi

amd79c30_dummy.o: io/dec/tc/amd79c30_dummy.c
	@${RM} amd79c30_dummy.o amd79c30_dummy.o.d
	${KCC} ${CCDFLAGS}  io/dec/tc/amd79c30_dummy.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bba ; fi

amd79c30_hdlc.o: io/dec/tc/amd79c30_hdlc.c
	@${RM} amd79c30_hdlc.o amd79c30_hdlc.o.d
	${KCC} ${CCDFLAGS}  io/dec/tc/amd79c30_hdlc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bba ; fi

eisa.o: io/dec/eisa/eisa.c
	@${RM} eisa.o eisa.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/eisa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eisa ; fi

eisa_cnfg.o: io/dec/eisa/eisa_cnfg.c
	@${RM} eisa_cnfg.o eisa_cnfg.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/eisa_cnfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eisa ; fi

isp.o: arch/alpha/hal/isp.c
	@${RM} isp.o isp.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/isp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_eisa ; fi

i2c.o: io/dec/i2c/i2c.c
	@${RM} i2c.o i2c.o.d
	${KCC} ${CCNFLAGS}  io/dec/i2c/i2c.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_i2c ; fi

iscc.o: io/dec/eisa/iscc.c
	@${RM} iscc.o iscc.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/iscc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_iscc ; fi

isa.o: io/dec/eisa/isa.c
	@${RM} isa.o isa.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/isa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_isa ; fi

gpc.o: io/dec/eisa/gpc.c
	@${RM} gpc.o gpc.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/gpc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_gpc ; fi

ace.o: io/dec/eisa/ace.c
	@${RM} ace.o ace.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/ace.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ace ; fi

lp.o: io/dec/eisa/lp.c
	@${RM} lp.o lp.o.d
	${KCC} ${CCDFLAGS} -g3 io/dec/eisa/lp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lp ; fi

envram.o: io/dec/eisa/envram.c
	@${RM} envram.o envram.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/envram.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_envram ; fi

re_driver.o: io/dec/eisa/re_driver.c
	@${RM} re_driver.o re_driver.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/re_driver.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_re_xcr ; fi

xcr_logger.o: io/dec/eisa/xcr_logger.c
	@${RM} xcr_logger.o xcr_logger.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/xcr_logger.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_re_xcr ; fi

xcr_port.o: io/dec/eisa/xcr_port.c
	@${RM} xcr_port.o xcr_port.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/xcr_port.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_re_xcr ; fi

pci.o: io/dec/pci/pci.c
	@${RM} pci.o pci.o.d
	${KCC} ${CCDFLAGS}  io/dec/pci/pci.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pci ; fi

dma_sg_map.o: arch/alpha/hal/dma_sg_map.c
	@${RM} dma_sg_map.o dma_sg_map.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/dma_sg_map.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pci ; fi

shared_intr.o: arch/alpha/hal/shared_intr.c
	@${RM} shared_intr.o shared_intr.o.d
	${KCC} ${CCDFLAGS}  arch/alpha/hal/shared_intr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pci ; fi

pci_common_intr_handler.o: io/dec/pci/pci_common_intr_handler.c
	@${RM} pci_common_intr_handler.o pci_common_intr_handler.o.d
	${KCC} ${CCDFLAGS}  io/dec/pci/pci_common_intr_handler.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pci ; fi

pnvram.o: io/dec/pci/pnvram.c
	@${RM} pnvram.o pnvram.o.d
	${KCC} ${CCDFLAGS}  io/dec/pci/pnvram.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pnvram ; fi

mchan.o: io/dec/pci/mchan.c
	@${RM} mchan.o mchan.o.d
	${KCC} ${CCDFLAGS} -O2 io/dec/pci/mchan.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_mchan ; fi

pcia_mult.o: io/dec/pci/pcia_mult.c
	@${RM} pcia_mult.o pcia_mult.o.d
	${KCC} ${CCDFLAGS}  io/dec/pci/pcia_mult.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pcia_mult ; fi

pcia.o: io/dec/pci/pcia.c
	@${RM} pcia.o pcia.o.d
	${KCC} ${CCDFLAGS}  io/dec/pci/pcia.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pcia ; fi

pd6729.o: io/dec/pcmcia/pd6729.c
	@${RM} pd6729.o pd6729.o.d
	${KCC} ${CCDFLAGS}  io/dec/pcmcia/pd6729.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pd6729 ; fi

pcic.o: io/dec/pcmcia/pcic.c
	@${RM} pcic.o pcic.o.d
	${KCC} ${CCDFLAGS}  io/dec/pcmcia/pcic.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pcic ; fi

pcmcia_fnc.o: io/dec/pcmcia/pcmcia_fnc.c
	@${RM} pcmcia_fnc.o pcmcia_fnc.o.d
	${KCC} ${CCNFLAGS}  io/dec/pcmcia/pcmcia_fnc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

pcmcia.o: io/dec/pcmcia/pcmcia.c
	@${RM} pcmcia.o pcmcia.o.d
	${KCC} ${CCDFLAGS}  io/dec/pcmcia/pcmcia.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pcmcia ; fi

card_services.o: io/dec/pcmcia/card_services.c
	@${RM} card_services.o card_services.o.d
	${KCC} ${CCDFLAGS}  io/dec/pcmcia/card_services.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pcmcia ; fi

card_config.o: io/dec/pcmcia/card_config.c
	@${RM} card_config.o card_config.o.d
	${KCC} ${CCDFLAGS}  io/dec/pcmcia/card_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pcmcia ; fi

pcmcia_event.o: io/dec/pcmcia/pcmcia_event.c
	@${RM} pcmcia_event.o pcmcia_event.o.d
	${KCC} ${CCDFLAGS}  io/dec/pcmcia/pcmcia_event.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pcmcia ; fi

i2oexec.o: io/i2o/i2oexec.c
	@${RM} i2oexec.o i2oexec.o.d
	${KCC} ${CCNFLAGS} -g3 io/i2o/i2oexec.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_i2o ; fi

i2omsg.o: io/i2o/i2omsg.c
	@${RM} i2omsg.o i2omsg.o.d
	${KCC} ${CCNFLAGS} -g3 io/i2o/i2omsg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_i2o ; fi

i2opcixport.o: io/i2o/i2opcixport.c
	@${RM} i2opcixport.o i2opcixport.o.d
	${KCC} ${CCNFLAGS} -g3 io/i2o/i2opcixport.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_i2o ; fi

i2o.o: io/i2o/i2o.c
	@${RM} i2o.o i2o.o.d
	${KCC} ${CCNFLAGS} -g3 io/i2o/i2o.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_i2o ; fi

i2o_bs.o: io/i2o/i2o_bs.c
	@${RM} i2o_bs.o i2o_bs.o.d
	${KCC} ${CCNFLAGS} -g3 io/i2o/i2o_bs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_i2o_bs ; fi

i2o_logger.o: io/i2o/i2o_logger.c
	@${RM} i2o_logger.o i2o_logger.o.d
	${KCC} ${CCNFLAGS} -g3 io/i2o/i2o_logger.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_i2o_bs ; fi

if_ln.o: io/dec/netif/if_ln.c
	@${RM} if_ln.o if_ln.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_ln.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ln ; fi

if_le.o: io/dec/netif/if_le.c
	@${RM} if_le.o if_le.o.d
	${KCC} ${CCDFLAGS}  io/dec/netif/if_le.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_le ; fi

if_te.o: io/dec/netif/if_te.c
	@${RM} if_te.o if_te.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_te.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_te ; fi

if_tu.o: io/dec/netif/if_tu.c
	@${RM} if_tu.o if_tu.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_tu.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_tu ; fi

if_fza.o: io/dec/netif/if_fza.c
	@${RM} if_fza.o if_fza.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_fza.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fza ; fi

if_fta.o: io/dec/netif/if_fta.c
	@${RM} if_fta.o if_fta.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_fta.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fta ; fi

if_tra.o: io/dec/netif/if_tra.c
	@${RM} if_tra.o if_tra.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_tra.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_tra ; fi

if_faa.o: io/dec/netif/if_faa.c
	@${RM} if_faa.o if_faa.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_faa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_faa ; fi

if_vb.o: io/dec/netif/if_vb.c
	@${RM} if_vb.o if_vb.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/if_vb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vb ; fi

if_otto.o: io/atm/drivers/otto/if_otto.c
	@${RM} if_otto.o if_otto.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/otto/if_otto.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lta ; fi

if_otto_xilinx.o: io/atm/drivers/otto/if_otto_xilinx.c
	@${RM} if_otto_xilinx.o if_otto_xilinx.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/otto/if_otto_xilinx.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lta ; fi

if_ottodefs.o: io/atm/drivers/otto/if_ottodefs.c
	@${RM} if_ottodefs.o if_ottodefs.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/otto/if_ottodefs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lta ; fi

otto_platform.o: io/atm/drivers/otto/otto_platform.c
	@${RM} otto_platform.o otto_platform.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/otto/otto_platform.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lta ; fi

otto_flow.o: io/atm/drivers/otto/otto_flow.c
	@${RM} otto_flow.o otto_flow.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/otto/otto_flow.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lta ; fi

otto_fakesnmp.o: io/atm/drivers/otto/otto_fakesnmp.c
	@${RM} otto_fakesnmp.o otto_fakesnmp.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/otto/otto_fakesnmp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lta ; fi

aal5crc.o: io/atm/drivers/otto/aal5crc.c
	@${RM} aal5crc.o aal5crc.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/otto/aal5crc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lta ; fi

acr_tbl.o: io/atm/drivers/meteor/acr_tbl.c
	@${RM} acr_tbl.o acr_tbl.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/meteor/acr_tbl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lpa ; fi

adap_sw.o: io/atm/drivers/meteor/adap_sw.c
	@${RM} adap_sw.o adap_sw.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/meteor/adap_sw.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lpa ; fi

fm.o: io/atm/drivers/meteor/fm.c
	@${RM} fm.o fm.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/meteor/fm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lpa ; fi

if_lpa.o: io/atm/drivers/meteor/if_lpa.c
	@${RM} if_lpa.o if_lpa.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/meteor/if_lpa.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lpa ; fi

if_lpa_defs.o: io/atm/drivers/meteor/if_lpa_defs.c
	@${RM} if_lpa_defs.o if_lpa_defs.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/meteor/if_lpa_defs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lpa ; fi

if_lpa_platform.o: io/atm/drivers/meteor/if_lpa_platform.c
	@${RM} if_lpa_platform.o if_lpa_platform.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/meteor/if_lpa_platform.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lpa ; fi

met_sw.o: io/atm/drivers/meteor/met_sw.c
	@${RM} met_sw.o met_sw.o.d
	${KCC} ${CCNFLAGS}  io/atm/drivers/meteor/met_sw.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lpa ; fi

ciconfig.o: io/dec/ci/ciconfig.c
	@${RM} ciconfig.o ciconfig.o.d
	${KCC} ${CCDFLAGS}  io/dec/ci/ciconfig.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

cippd_error.o: io/dec/ci/cippd_error.c
	@${RM} cippd_error.o cippd_error.o.d
	${KCC} ${CCDFLAGS}  io/dec/ci/cippd_error.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

cippd_event.o: io/dec/ci/cippd_event.c
	@${RM} cippd_event.o cippd_event.o.d
	${KCC} ${CCDFLAGS}  io/dec/ci/cippd_event.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

cippd_pmaint.o: io/dec/ci/cippd_pmaint.c
	@${RM} cippd_pmaint.o cippd_pmaint.o.d
	${KCC} ${CCDFLAGS}  io/dec/ci/cippd_pmaint.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

cippd_protocol.o: io/dec/ci/cippd_protocol.c
	@${RM} cippd_protocol.o cippd_protocol.o.d
	${KCC} ${CCDFLAGS}  io/dec/ci/cippd_protocol.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

cippdvar.o: io/dec/ci/cippdvar.c
	@${RM} cippdvar.o cippdvar.o.d
	${KCC} ${CCDFLAGS}  io/dec/ci/cippdvar.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

gvp_block.o: io/dec/gvp/gvp_block.c
	@${RM} gvp_block.o gvp_block.o.d
	${KCC} ${CCDFLAGS}  io/dec/gvp/gvp_block.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

gvp_dg.o: io/dec/gvp/gvp_dg.c
	@${RM} gvp_dg.o gvp_dg.o.d
	${KCC} ${CCDFLAGS}  io/dec/gvp/gvp_dg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

gvp_msg.o: io/dec/gvp/gvp_msg.c
	@${RM} gvp_msg.o gvp_msg.o.d
	${KCC} ${CCDFLAGS}  io/dec/gvp/gvp_msg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

gvp_subr.o: io/dec/gvp/gvp_subr.c
	@${RM} gvp_subr.o gvp_subr.o.d
	${KCC} ${CCDFLAGS}  io/dec/gvp/gvp_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

gvpvar.o: io/dec/gvp/gvpvar.c
	@${RM} gvpvar.o gvpvar.o.d
	${KCC} ${CCDFLAGS}  io/dec/gvp/gvpvar.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd ; fi

np_block.o: io/dec/np/np_block.c
	@${RM} np_block.o np_block.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_block.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

np_dg.o: io/dec/np/np_dg.c
	@${RM} np_dg.o np_dg.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_dg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

np_error.o: io/dec/np/np_error.c
	@${RM} np_error.o np_error.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_error.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

np_init.o: io/dec/np/np_init.c
	@${RM} np_init.o np_init.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_init.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

np_isr.o: io/dec/np/np_isr.c
	@${RM} np_isr.o np_isr.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_isr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

np_lpmaint.o: io/dec/np/np_lpmaint.c
	@${RM} np_lpmaint.o np_lpmaint.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_lpmaint.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

np_msg.o: io/dec/np/np_msg.c
	@${RM} np_msg.o np_msg.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_msg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

np_subr.o: io/dec/np/np_subr.c
	@${RM} np_subr.o np_subr.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/np_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

npvar.o: io/dec/np/npvar.c
	@${RM} npvar.o npvar.o.d
	${KCC} ${CCDFLAGS}  io/dec/np/npvar.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

xminp.o: io/dec/xmi/xminp.c
	@${RM} xminp.o xminp.o.d
	${KCC} ${CCDFLAGS}  io/dec/xmi/xminp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_np ; fi

scs_block.o: io/dec/scs/scs_block.c
	@${RM} scs_block.o scs_block.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_block.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_configdb.o: io/dec/scs/scs_configdb.c
	@${RM} scs_configdb.o scs_configdb.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_configdb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_conn.o: io/dec/scs/scs_conn.c
	@${RM} scs_conn.o scs_conn.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_conn.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_dg.o: io/dec/scs/scs_dg.c
	@${RM} scs_dg.o scs_dg.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_dg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_error.o: io/dec/scs/scs_error.c
	@${RM} scs_error.o scs_error.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_error.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_event.o: io/dec/scs/scs_event.c
	@${RM} scs_event.o scs_event.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_event.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_info.o: io/dec/scs/scs_info.c
	@${RM} scs_info.o scs_info.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_info.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_maint.o: io/dec/scs/scs_maint.c
	@${RM} scs_maint.o scs_maint.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_maint.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_msg.o: io/dec/scs/scs_msg.c
	@${RM} scs_msg.o scs_msg.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_msg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_protocol.o: io/dec/scs/scs_protocol.c
	@${RM} scs_protocol.o scs_protocol.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_protocol.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_subr.o: io/dec/scs/scs_subr.c
	@${RM} scs_subr.o scs_subr.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scs_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scsvar.o: io/dec/scs/scsvar.c
	@${RM} scsvar.o scsvar.o.d
	${KCC} ${CCDFLAGS}  io/dec/scs/scsvar.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_scs ; fi

scs_directory.o: io/dec/sysap/scs_directory.c
	@${RM} scs_directory.o scs_directory.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/scs_directory.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_tape.o: io/dec/sysap/mscp_tape.c
	@${RM} mscp_tape.o mscp_tape.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_tape.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_disk.o: io/dec/sysap/mscp_disk.c
	@${RM} mscp_disk.o mscp_disk.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_disk.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_bbr.o: io/dec/sysap/mscp_bbr.c
	@${RM} mscp_bbr.o mscp_bbr.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_bbr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_bbrstates.o: io/dec/sysap/mscp_bbrstates.c
	@${RM} mscp_bbrstates.o mscp_bbrstates.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_bbrstates.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_config.o: io/dec/sysap/mscp_config.c
	@${RM} mscp_config.o mscp_config.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_conpol.o: io/dec/sysap/mscp_conpol.c
	@${RM} mscp_conpol.o mscp_conpol.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_conpol.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_diskvar.o: io/dec/sysap/mscp_diskvar.c
	@${RM} mscp_diskvar.o mscp_diskvar.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_diskvar.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_subr.o: io/dec/sysap/mscp_subr.c
	@${RM} mscp_subr.o mscp_subr.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_subr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

mscp_var.o: io/dec/sysap/mscp_var.c
	@${RM} mscp_var.o mscp_var.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/mscp_var.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

sysap_start.o: io/dec/sysap/sysap_start.c
	@${RM} sysap_start.o sysap_start.o.d
	${KCC} ${CCDFLAGS}  io/dec/sysap/sysap_start.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap ; fi

uba.o: io/dec/uba/uba.c
	@${RM} uba.o uba.o.d
	${KCC} ${CCDFLAGS}  io/dec/uba/uba.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_uba ; fi

uqserv.o: io/dec/uba/uqserv.c
	@${RM} uqserv.o uqserv.o.d
	${KCC} ${CCDFLAGS}  io/dec/uba/uqserv.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_uqserv ; fi

kdm.o: io/dec/uba/kdm.c
	@${RM} kdm.o kdm.o.d
	${KCC} ${CCDFLAGS}  io/dec/uba/kdm.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_dsa_kdm ; fi

fd.o: io/dec/fdi/fd.c
	@${RM} fd.o fd.o.d
	${KCC} ${CCDFLAGS}  io/dec/fdi/fd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fdi ; fi

fdcam.o: io/dec/fdi/fdcam.c
	@${RM} fdcam.o fdcam.o.d
	${KCC} ${CCDFLAGS}  io/dec/fdi/fdcam.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fdi ; fi

ws_driver.o: io/dec/ws/ws_driver.c
	@${RM} ws_driver.o ws_driver.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/ws_driver.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ws ; fi

lk201.o: io/dec/ws/lk201.c
	@${RM} lk201.o lk201.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/lk201.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_scc_input ; fi

vsxxx.o: io/dec/ws/vsxxx.c
	@${RM} vsxxx.o vsxxx.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/vsxxx.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_scc_input ; fi

pcxal.o: io/dec/ws/pcxal.c
	@${RM} pcxal.o pcxal.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/pcxal.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_gpc_input ; fi

pcxas.o: io/dec/ws/pcxas.c
	@${RM} pcxas.o pcxas.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/pcxas.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_gpc_input ; fi

qfont.o: io/dec/ws/qfont.c
	@${RM} qfont.o qfont.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/qfont.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_qfont ; fi

bt431.o: io/dec/ws/bt431.c
	@${RM} bt431.o bt431.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/bt431.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bt431 ; fi

bt459.o: io/dec/ws/bt459.c
	@${RM} bt459.o bt459.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/bt459.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bt459 ; fi

bt463.o: io/dec/ws/bt463.c
	@${RM} bt463.o bt463.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/bt463.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_bt463 ; fi

fb.o: io/dec/ws/fb.c
	@${RM} fb.o fb.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/fb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_fb ; fi

vga_support.o: io/dec/ws/vga_support.c
	@${RM} vga_support.o vga_support.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/vga_support.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ws ; fi

vga.o: io/dec/ws/vga.c
	@${RM} vga.o vga.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/vga.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vga ; fi

ati.o: io/dec/ws/ati.c
	@${RM} ati.o ati.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/ati.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ati32 ; fi

ati64.o: io/dec/ws/ati64.c
	@${RM} ati64.o ati64.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/ati64.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ati64 ; fi

cirrus.o: io/dec/ws/cirrus.c
	@${RM} cirrus.o cirrus.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/cirrus.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_cirrus ; fi

qvision.o: io/dec/ws/qvision.c
	@${RM} qvision.o qvision.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/qvision.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_qvision ; fi

s3v864.o: io/dec/ws/s3v864.c
	@${RM} s3v864.o s3v864.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/s3v864.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_s3v864 ; fi

s3trio.o: io/dec/ws/s3trio.c
	@${RM} s3trio.o s3trio.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/s3trio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_s3trio ; fi

wd.o: io/dec/ws/wd.c
	@${RM} wd.o wd.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/wd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_wd ; fi

comet.o: io/dec/ws/comet.c
	@${RM} comet.o comet.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/comet.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_comet ; fi

tga.o: io/dec/ws/tga.c
	@${RM} tga.o tga.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/tga.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_tga ; fi

pmagro.o: io/dec/ws/pmagro.c
	@${RM} pmagro.o pmagro.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/pmagro.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sfbp ; fi

sfb.o: io/dec/ws/sfb.c
	@${RM} sfb.o sfb.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/sfb.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_sfbp ; fi

pv.o: io/dec/ws/pv.c
	@${RM} pv.o pv.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/pv.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pv ; fi

pvl.o: io/dec/ws/pvl.c
	@${RM} pvl.o pvl.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/pvl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pvl ; fi

pvp.o: io/dec/ws/pvp.c
	@${RM} pvp.o pvp.o.d
	${KCC} ${CCDFLAGS}  io/dec/ws/pvp.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pvp ; fi

pr.o: io/dec/presto/pr.c
	@${RM} pr.o pr.o.d
	${KCC} ${CCNFLAGS} -g3 io/dec/presto/pr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_presto ; fi

presto_cfg.o: io/dec/presto/presto_cfg.c
	@${RM} presto_cfg.o presto_cfg.o.d
	${KCC} ${CCNFLAGS}  io/dec/presto/presto_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_presto ; fi

mbox_data.o: data/mbox_data.c
	@${RM} mbox_data.o mbox_data.o.d
	${KCC} ${CCNFLAGS}  data/mbox_data.c

error_event.o: io/common/error_event.c
	@${RM} error_event.o error_event.o.d
	${KCC} ${CCNFLAGS}  io/common/error_event.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

alloc_smt.o: io/common/alloc_smt.c
	@${RM} alloc_smt.o alloc_smt.o.d
	${KCC} ${CCNFLAGS}  io/common/alloc_smt.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_arch_alpha ; fi

trn_sr.o: net/trn_sr.c
	@${RM} trn_sr.o trn_sr.o.d
	${KCC} ${CCNFLAGS} -g3 net/trn_sr.c

dki_osf.o: vxvm/dki_osf.c
	@${RM} dki_osf.o dki_osf.o.d
	${KCC} ${CCNFLAGS}  vxvm/dki_osf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

plex.o: vxvm/plex/plex.c
	@${RM} plex.o plex.o.d
	${KCC} ${CCNFLAGS}  vxvm/plex/plex.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

volspec.o: vxvm/volspec/volspec.c
	@${RM} volspec.o volspec.o.d
	${KCC} ${CCNFLAGS}  vxvm/volspec/volspec.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

vol.o: vxvm/vol/vol.c
	@${RM} vol.o vol.o.d
	${KCC} ${CCNFLAGS} -g3 vxvm/vol/vol.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

volblog.o: vxvm/vol/volblog.c
	@${RM} volblog.o volblog.o.d
	${KCC} ${CCNFLAGS}  vxvm/vol/volblog.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

volioctl.o: vxvm/vol/volioctl.c
	@${RM} volioctl.o volioctl.o.d
	${KCC} ${CCNFLAGS}  vxvm/vol/volioctl.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

volklog.o: vxvm/vol/volklog.c
	@${RM} volklog.o volklog.o.d
	${KCC} ${CCNFLAGS}  vxvm/vol/volklog.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

volted.o: vxvm/vol/volted.c
	@${RM} volted.o volted.o.d
	${KCC} ${CCNFLAGS}  vxvm/vol/volted.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

volSpace.o: vxvm/vol/volSpace.c
	@${RM} volSpace.o volSpace.o.d
	${KCC} ${CCNFLAGS}  vxvm/vol/volSpace.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

volroot.o: vxvm/vol/volroot.c
	@${RM} volroot.o volroot.o.d
	${KCC} ${CCNFLAGS}  vxvm/vol/volroot.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

vol_cfg.o: vxvm/vol/vol_cfg.c
	@${RM} vol_cfg.o vol_cfg.o.d
	${KCC} ${CCNFLAGS}  vxvm/vol/vol_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lsm ; fi

ted.o: ted/ted.c
	@${RM} ted.o ted.o.d
	${KCC} ${CCNFLAGS}  ted/ted.c

tedSpace.o: ted/tedSpace.c
	@${RM} tedSpace.o tedSpace.o.d
	${KCC} ${CCNFLAGS}  ted/tedSpace.c

vba_generic.o: io/dec/vme/vba_generic.c
	@${RM} vba_generic.o vba_generic.o.d
	${KCC} ${CCNFLAGS}  io/dec/vme/vba_generic.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vme_vba ; fi

vba_tc.o: io/dec/vme/vba_tc.c
	@${RM} vba_tc.o vba_tc.o.d
	${KCC} ${CCNFLAGS}  io/dec/vme/vba_tc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vme_vba ; fi

vba_pci.o: io/dec/vme/vba_pci.c
	@${RM} vba_pci.o vba_pci.o.d
	${KCC} ${CCNFLAGS}  io/dec/vme/vba_pci.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vme_vba ; fi

vba_dispatch.o: io/dec/vme/vba_dispatch.c
	@${RM} vba_dispatch.o vba_dispatch.o.d
	${KCC} ${CCNFLAGS}  io/dec/vme/vba_dispatch.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_vme_vba ; fi

ddr.o: io/common/ddr.c
	@${RM} ddr.o ddr.o.d
	${KCC} ${CCNFLAGS}  io/common/ddr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ddr ; fi

kio.o: io/common/kio.c
	@${RM} kio.o kio.o.d
	${KCC} ${CCNFLAGS}  io/common/kio.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kio ; fi

kds.o: io/common/kds.c
	@${RM} kds.o kds.o.d
	${KCC} ${CCNFLAGS}  io/common/kds.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_kds ; fi

envmon.o: arch/alpha/hal/envmon.c
	@${RM} envmon.o envmon.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/envmon.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_envmon ; fi

distint_cfg.o: arch/alpha/hal/distint_cfg.c
	@${RM} distint_cfg.o distint_cfg.o.d
	${KCC} ${CCNFLAGS} -g3 arch/alpha/hal/distint_cfg.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_distint ; fi

if_el.o: io/dec/netif/if_el.c
	@${RM} if_el.o if_el.o.d
	${KCC} ${CCDFLAGS}  io/dec/netif/if_el.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_el ; fi

lan_common.o: io/dec/netif/lan_common.c
	@${RM} lan_common.o lan_common.o.d
	${KCC} ${CCNFLAGS}  io/dec/netif/lan_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_lan_common ; fi

hmc.o: io/dec/eisa/hmc.c
	@${RM} hmc.o hmc.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/hmc.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_hmc ; fi

hmc_support.o: io/dec/eisa/hmc_support.c
	@${RM} hmc_support.o hmc_support.o.d
	${KCC} ${CCDFLAGS}  io/dec/eisa/hmc_support.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_hmc ; fi

pci_isa_intr.o: io/dec/pci/pci_isa_intr.c
	@${RM} pci_isa_intr.o pci_isa_intr.o.d
	${KCC} ${CCNFLAGS}  io/dec/pci/pci_isa_intr.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_pci_isa_intr ; fi

ev6_common.o: arch/alpha/hal/ev6_common.c
	@${RM} ev6_common.o ev6_common.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/ev6_common.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ev6_common ; fi

usbd.o: io/dec/usb/usbd.c
	@${RM} usbd.o usbd.o.d
	${KCC} ${CCNFLAGS} -g3 io/dec/usb/usbd.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_usb ; fi

usb_ohci.o: io/dec/usb/usb_ohci.c
	@${RM} usb_ohci.o usb_ohci.o.d
	${KCC} ${CCDFLAGS}  io/dec/usb/usb_ohci.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_usb_ohci ; fi

usb_hub.o: io/dec/usb/usb_hub.c
	@${RM} usb_hub.o usb_hub.o.d
	${KCC} ${CCNFLAGS} -g3 io/dec/usb/usb_hub.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_usb_hub ; fi

usb_hid.o: io/dec/usb/usb_hid.c
	@${RM} usb_hid.o usb_hid.o.d
	${KCC} ${CCNFLAGS} -g3 io/dec/usb/usb_hid.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_usb_hid ; fi

usb_keyboard.o: io/dec/usb/usb_keyboard.c
	@${RM} usb_keyboard.o usb_keyboard.o.d
	${KCC} ${CCNFLAGS} -g3 io/dec/usb/usb_keyboard.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_usb_keyboard ; fi

usb_mouse.o: io/dec/usb/usb_mouse.c
	@${RM} usb_mouse.o usb_mouse.o.d
	${KCC} ${CCNFLAGS} -g3 io/dec/usb/usb_mouse.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_usb_mouse ; fi

usb_printer.o: io/dec/usb/usb_printer.c
	@${RM} usb_printer.o usb_printer.o.d
	${KCC} ${CCNFLAGS} -g3 io/dec/usb/usb_printer.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_usb_printer ; fi

emx.mod: io/cam/emx/emx.mod
	@${RM} emx.mod
	${CP} io/cam/emx/emx.mod emx.mod

alt.mod: io/dec/netif/gb/alt.mod
	@${RM} alt.mod
	${CP} io/dec/netif/gb/alt.mod alt.mod

lfa.mod: io/atm/drivers/fore/lfa.mod
	@${RM} lfa.mod
	${CP} io/atm/drivers/fore/lfa.mod lfa.mod


cm.mod: Makefile cm_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_cm
MODULE_cm:
	${RM} cm.mod
	${LD} -dc -r -o cm.mod cm_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cm.mod ; fi

generic.mod: Makefile generic_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_generic
MODULE_generic:
	${RM} generic.mod
	${LD} -dc -r -o generic.mod generic_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ generic.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ generic.mod ; fi

io.mod: Makefile io_cfg.o kern_devsw.o
	@${MAKE} -${MAKEFLAGS} MODULE_io
MODULE_io:
	${RM} io.mod
	${LD} -dc -r -o io.mod io_cfg.o kern_devsw.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ io.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ io.mod ; fi

ipc.mod: Makefile ipc_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_ipc
MODULE_ipc:
	${RM} ipc.mod
	${LD} -dc -r -o ipc.mod ipc_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ipc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ipc.mod ; fi

proc.mod: Makefile proc_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_proc
MODULE_proc:
	${RM} proc.mod
	${LD} -dc -r -o proc.mod proc_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ proc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ proc.mod ; fi

sec.mod: Makefile sec_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_sec
MODULE_sec:
	${RM} sec.mod
	${LD} -dc -r -o sec.mod sec_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec.mod ; fi

socket.mod: Makefile socket_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_socket
MODULE_socket:
	${RM} socket.mod
	${LD} -dc -r -o socket.mod socket_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ socket.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ socket.mod ; fi

sec_min.mod: Makefile spd_proplist.o spd_udac.o sec_conf.o sec_subrs.o \
	 sec_acl.o
	@${MAKE} -${MAKEFLAGS} MODULE_sec_min
MODULE_sec_min:
	${RM} sec_min.mod
	${LD} -dc -r -o sec_min.mod spd_proplist.o spd_udac.o sec_conf.o \
	 sec_subrs.o sec_acl.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_min.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_min.mod ; fi

rt.mod: Makefile rt_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_rt
MODULE_rt:
	${RM} rt.mod
	${LD} -dc -r -o rt.mod rt_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ rt.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ rt.mod ; fi

std_kern.mod: Makefile init_sysent.o exc_server.o exc_user.o \
	 mach_host_server.o mach_server.o syscalls.o cmu_syscalls.o \
	 coff_exec.o interp_exec.o kern_acct.o kern_aio.o kern_clock.o \
	 kern_class.o kern_compat.o kern_descrip.o kern_exec.o \
	 kern_execargs.o kern_execconfig.o kern_exit.o kern_fork.o \
	 kern_kmodcall.o kern_malloc.o contig_malloc.o kern_mman.o \
	 kern_proc.o kern_prot.o kern_resource.o kern_sig.o \
	 kern_sigqueue.o kern_subr.o kern_subsys.o kern_synch.o \
	 kern_time.o kern_utctime.o kern_xxx.o ldr_kload.o lwc.o \
	 mach_process.o mach_signal.o subr_binlog.o subr_log.o \
	 subr_prf.o subr_rmap.o subr_select.o subr_xxx.o subsys_conf.o \
	 svipc_ipc.o svipc_msg.o svipc_sem.o svipc_shm.o sys_generic.o \
	 sys_socket.o sys_sysinfo.o tty_tty.o uipc_domain.o uipc_mbuf.o \
	 uipc_socket.o uipc_socket2.o uipc_syscalls.o ux_exception.o \
	 ddi_subr.o kdebug_kern.o event.o exception.o host.o \
	 ipc_basics.o ipc_copyin.o ipc_copyout.o ipc_host.o ipc_kport.o \
	 ipc_kreply.o ipc_kset.o ipc_mports.o ipc_pobj.o ipc_port.o \
	 ipc_prims.o ipc_ptraps.o ipc_tt.o kalloc.o lock.o lockdev.o \
	 mach_factor.o mach_sysdev.o mach_user_internal.o machine.o \
	 mig_support.o parallel.o processor.o queue.o sched_prim.o \
	 syscall_emulation.o syscall_subr.o syscall_sw.o task.o \
	 task_swap.o thread.o thread_swap.o threadcall.o timer.o \
	 zalloc.o msfs_syscalls.o if.o netisr.o nfs_hooks.o \
	 fdfs_vfsops.o fdfs_vnops.o kern_fuser.o kern_sigsend.o \
	 kern_sysfs.o kern_sysinfo.o kern_uadmin.o kern_wait.o \
	 priocntl.o procset.o tty_common.o
	@${MAKE} -${MAKEFLAGS} MODULE_std_kern
MODULE_std_kern:
	${RM} std_kern.mod
	${LD} -dc -r -o std_kern.mod init_sysent.o exc_server.o exc_user.o \
	 mach_host_server.o mach_server.o syscalls.o cmu_syscalls.o \
	 coff_exec.o interp_exec.o kern_acct.o kern_aio.o kern_clock.o \
	 kern_class.o kern_compat.o kern_descrip.o kern_exec.o \
	 kern_execargs.o kern_execconfig.o kern_exit.o kern_fork.o \
	 kern_kmodcall.o kern_malloc.o contig_malloc.o kern_mman.o \
	 kern_proc.o kern_prot.o kern_resource.o kern_sig.o \
	 kern_sigqueue.o kern_subr.o kern_subsys.o kern_synch.o \
	 kern_time.o kern_utctime.o kern_xxx.o ldr_kload.o lwc.o \
	 mach_process.o mach_signal.o subr_binlog.o subr_log.o \
	 subr_prf.o subr_rmap.o subr_select.o subr_xxx.o subsys_conf.o \
	 svipc_ipc.o svipc_msg.o svipc_sem.o svipc_shm.o sys_generic.o \
	 sys_socket.o sys_sysinfo.o tty_tty.o uipc_domain.o uipc_mbuf.o \
	 uipc_socket.o uipc_socket2.o uipc_syscalls.o ux_exception.o \
	 ddi_subr.o kdebug_kern.o event.o exception.o host.o \
	 ipc_basics.o ipc_copyin.o ipc_copyout.o ipc_host.o ipc_kport.o \
	 ipc_kreply.o ipc_kset.o ipc_mports.o ipc_pobj.o ipc_port.o \
	 ipc_prims.o ipc_ptraps.o ipc_tt.o kalloc.o lock.o lockdev.o \
	 mach_factor.o mach_sysdev.o mach_user_internal.o machine.o \
	 mig_support.o parallel.o processor.o queue.o sched_prim.o \
	 syscall_emulation.o syscall_subr.o syscall_sw.o task.o \
	 task_swap.o thread.o thread_swap.o threadcall.o timer.o \
	 zalloc.o msfs_syscalls.o if.o netisr.o nfs_hooks.o \
	 fdfs_vfsops.o fdfs_vnops.o kern_fuser.o kern_sigsend.o \
	 kern_sysfs.o kern_sysinfo.o kern_uadmin.o kern_wait.o \
	 priocntl.o procset.o tty_common.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ std_kern.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ std_kern.mod ; fi

bsd_tty.mod: Makefile tty_cfg.o tty.o tty_compat.o tty_subr.o
	@${MAKE} -${MAKEFLAGS} MODULE_bsd_tty
MODULE_bsd_tty:
	${RM} bsd_tty.mod
	${LD} -dc -r -o bsd_tty.mod tty_cfg.o tty.o tty_compat.o tty_subr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bsd_tty.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bsd_tty.mod ; fi

xpr.mod: Makefile xpr.o
	@${MAKE} -${MAKEFLAGS} MODULE_xpr
MODULE_xpr:
	${RM} xpr.mod
	${LD} -dc -r -o xpr.mod xpr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xpr.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xpr.mod ; fi

mach_xp.mod: Makefile memory_object_default_user.o
	@${MAKE} -${MAKEFLAGS} MODULE_mach_xp
MODULE_mach_xp:
	${RM} mach_xp.mod
	${LD} -dc -r -o mach_xp.mod memory_object_default_user.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mach_xp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mach_xp.mod ; fi

cdfs.mod: Makefile cdfs_bmap.o cdfs_config.o cdfs_lookup.o cdfs_node.o \
	 cdfs_subr.o cdfs_vfsops.o cdfs_vnops.o
	@${MAKE} -${MAKEFLAGS} MODULE_cdfs
MODULE_cdfs:
	${RM} cdfs.mod
	${LD} -dc -r -o cdfs.mod cdfs_bmap.o cdfs_config.o cdfs_lookup.o \
	 cdfs_node.o cdfs_subr.o cdfs_vfsops.o cdfs_vnops.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cdfs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cdfs.mod ; fi

dvdfs.mod: Makefile dvdfs_vfsops.o dvdfs_node.o dvdfs_vnops.o
	@${MAKE} -${MAKEFLAGS} MODULE_dvdfs
MODULE_dvdfs:
	${RM} dvdfs.mod
	${LD} -dc -r -o dvdfs.mod dvdfs_vfsops.o dvdfs_node.o dvdfs_vnops.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dvdfs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dvdfs.mod ; fi

ess.mod: Makefile ess.o eventTypes.o groupEventFuncs.o macroFuncs.o \
	 eventTypes_extensions.o macroFuncs_extensions.o
	@${MAKE} -${MAKEFLAGS} MODULE_ess
MODULE_ess:
	${RM} ess.mod
	${LD} -dc -r -o ess.mod ess.o eventTypes.o groupEventFuncs.o \
	 macroFuncs.o eventTypes_extensions.o macroFuncs_extensions.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ess.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ess.mod ; fi

ess_stub.mod: Makefile event_simulation.o
	@${MAKE} -${MAKEFLAGS} MODULE_ess_stub
MODULE_ess_stub:
	${RM} ess_stub.mod
	${LD} -dc -r -o ess_stub.mod event_simulation.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ess_stub.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ess_stub.mod ; fi

kdebug.mod: Makefile kdebug_brkpt.o kdebug_conf.o kdebug_cfg.o \
	 kdebug_io.o kdebug_main.o kdebug_proto.o db_access.o db_aout.o \
	 db_break.o db_command.o db_cond.o db_doprnt.o db_examine.o \
	 db_expr.o db_ext_symtab.o db_input.o db_lex.o db_macro.o \
	 db_output.o db_print.o db_run.o db_sym.o db_task_thread.o \
	 db_tr.o db_trap.o db_variables.o db_watch.o db_write_cmd.o \
	 kdebug_ace_cons.o kdebug_misc.o kdebug_cobra_cons.o \
	 kdebug_gbus_cons.o kdebug_scc_cons.o kdebug_iscc_cons.o \
	 db_alpha_aout.o db_alpha_inst.o db_alpha_sym.o db_commands.o \
	 db_disasm.o db_interface.o db_trace.o
	@${MAKE} -${MAKEFLAGS} MODULE_kdebug
MODULE_kdebug:
	${RM} kdebug.mod
	${LD} -dc -r -o kdebug.mod kdebug_brkpt.o kdebug_conf.o kdebug_cfg.o \
	 kdebug_io.o kdebug_main.o kdebug_proto.o db_access.o db_aout.o \
	 db_break.o db_command.o db_cond.o db_doprnt.o db_examine.o \
	 db_expr.o db_ext_symtab.o db_input.o db_lex.o db_macro.o \
	 db_output.o db_print.o db_run.o db_sym.o db_task_thread.o \
	 db_tr.o db_trap.o db_variables.o db_watch.o db_write_cmd.o \
	 kdebug_ace_cons.o kdebug_misc.o kdebug_cobra_cons.o \
	 kdebug_gbus_cons.o kdebug_scc_cons.o kdebug_iscc_cons.o \
	 db_alpha_aout.o db_alpha_inst.o db_alpha_sym.o db_commands.o \
	 db_disasm.o db_interface.o db_trace.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kdebug.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kdebug.mod ; fi

dli.mod: Makefile dli_bind.o dli_filter.o dli_init.o dli_input.o \
	 dli_mopctrs.o dli_netsync.o dli_output.o dli_proto.o \
	 dli_sockopt.o dli_subr.o dli_timer.o dli_usrreq.o
	@${MAKE} -${MAKEFLAGS} MODULE_dli
MODULE_dli:
	${RM} dli.mod
	${LD} -dc -r -o dli.mod dli_bind.o dli_filter.o dli_init.o \
	 dli_input.o dli_mopctrs.o dli_netsync.o dli_output.o \
	 dli_proto.o dli_sockopt.o dli_subr.o dli_timer.o dli_usrreq.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dli.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dli.mod ; fi

ffm_fs.mod: Makefile ffm_cfg.o ffm_vfsops.o ffm_vnops.o
	@${MAKE} -${MAKEFLAGS} MODULE_ffm_fs
MODULE_ffm_fs:
	${RM} ffm_fs.mod
	${LD} -dc -r -o ffm_fs.mod ffm_cfg.o ffm_vfsops.o ffm_vnops.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ffm_fs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ffm_fs.mod ; fi

atm.mod: Makefile cmm.o cmm_subr.o cmm_adi.o cmm_smi.o cmm_cmi.o \
	 cmm_ppa.o cmm_esi.o cmm_manage.o cmm_state.o
	@${MAKE} -${MAKEFLAGS} MODULE_atm
MODULE_atm:
	${RM} atm.mod
	${LD} -dc -r -o atm.mod cmm.o cmm_subr.o cmm_adi.o cmm_smi.o \
	 cmm_cmi.o cmm_ppa.o cmm_esi.o cmm_manage.o cmm_state.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atm.mod ; fi

atmip.mod: Makefile atm_arp.o ip_converge.o
	@${MAKE} -${MAKEFLAGS} MODULE_atmip
MODULE_atmip:
	${RM} atmip.mod
	${LD} -dc -r -o atmip.mod atm_arp.o ip_converge.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmip.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmip.mod ; fi

lane.mod: Makefile cm_sap_shim.o le_disp.o lec_arp.o lec_ctrl.o \
	 lec_data.o lec_upper.o map.o svc_info.o utl.o utl_os.o \
	 g_event.o
	@${MAKE} -${MAKEFLAGS} MODULE_lane
MODULE_lane:
	${RM} lane.mod
	${LD} -dc -r -o lane.mod cm_sap_shim.o le_disp.o lec_arp.o \
	 lec_ctrl.o lec_data.o lec_upper.o map.o svc_info.o utl.o \
	 utl_os.o g_event.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lane.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lane.mod ; fi

atmifmp.mod: Makefile ipsh_dunix.o ipshost.o
	@${MAKE} -${MAKEFLAGS} MODULE_atmifmp
MODULE_atmifmp:
	${RM} atmifmp.mod
	${LD} -dc -r -o atmifmp.mod ipsh_dunix.o ipshost.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmifmp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmifmp.mod ; fi

atmtm.mod: Makefile atmtm.o
	@${MAKE} -${MAKEFLAGS} MODULE_atmtm
MODULE_atmtm:
	${RM} atmtm.mod
	${LD} -dc -r -o atmtm.mod atmtm.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmtm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmtm.mod ; fi

atmuni.mod: Makefile atmuni_addrmgr.o atmuni_connect.o atmuni_data.o \
	 atmuni_devmanip.o atmuni_except.o atmuni_ilmi.o atmuni_loader.o \
	 atmuni_mmi.o atmuni_receive.o atmuni_sig.o atmuni_sigstubs.o \
	 atmuni_unimanip.o
	@${MAKE} -${MAKEFLAGS} MODULE_atmuni
MODULE_atmuni:
	${RM} atmuni.mod
	${LD} -dc -r -o atmuni.mod atmuni_addrmgr.o atmuni_connect.o \
	 atmuni_data.o atmuni_devmanip.o atmuni_except.o atmuni_ilmi.o \
	 atmuni_loader.o atmuni_mmi.o atmuni_receive.o atmuni_sig.o \
	 atmuni_sigstubs.o atmuni_unimanip.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmuni.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmuni.mod ; fi

atmilmi3x.mod: Makefile ilmi_manage.o ilmi_loader.o ilmi_data.o \
	 ilmi_receive.o agent.o codec.o dec_atm.o fsm.o netpref.o \
	 system.o
	@${MAKE} -${MAKEFLAGS} MODULE_atmilmi3x
MODULE_atmilmi3x:
	${RM} atmilmi3x.mod
	${LD} -dc -r -o atmilmi3x.mod ilmi_manage.o ilmi_loader.o \
	 ilmi_data.o ilmi_receive.o agent.o codec.o dec_atm.o fsm.o \
	 netpref.o system.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmilmi3x.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ atmilmi3x.mod ; fi

uni3x.mod: Makefile atmsig_manage.o atmsig_loader.o \
	 atmsig_cmm_callbacks.o atmsig_qsaalrx.o atmsig_mainloop.o \
	 atmsig_receive.o atmsig_data.o atmsig_ies.o atmsig_status.o \
	 atmsig_add.o atmsig_drop.o atmsig_release.o atmsig_restart.o \
	 atmsig_callrefs.o atmsig_misc.o atmsig_setup.o atmsig_addrman.o \
	 atmsig_trill_as.o aal.o asd.o asi.o cm_lib.o las.o cm_atm.o \
	 cm_bdy5.o cm_gen.o cm_hash.o ss_ptsp.o am_bdy1.o am_bdy2.o \
	 am_bdy3.o am_bdy4.o am_bdy5.o am_db1.o am_db2.o am_id.o \
	 am_ex_pt.o am_ptli.o am_mf.o am_ptmi.o as_bdy1.o as_bdy2.o \
	 as_bdy3.o as_bdy4.o as_bdy5.o as_bdy6.o as_ex_pt.o as_id.o \
	 as_ptui.o as_ptmi.o lm.o smambdy1.o smasbdy1.o
	@${MAKE} -${MAKEFLAGS} MODULE_uni3x
MODULE_uni3x:
	${RM} uni3x.mod
	${LD} -dc -r -o uni3x.mod atmsig_manage.o atmsig_loader.o \
	 atmsig_cmm_callbacks.o atmsig_qsaalrx.o atmsig_mainloop.o \
	 atmsig_receive.o atmsig_data.o atmsig_ies.o atmsig_status.o \
	 atmsig_add.o atmsig_drop.o atmsig_release.o atmsig_restart.o \
	 atmsig_callrefs.o atmsig_misc.o atmsig_setup.o atmsig_addrman.o \
	 atmsig_trill_as.o aal.o asd.o asi.o cm_lib.o las.o cm_atm.o \
	 cm_bdy5.o cm_gen.o cm_hash.o ss_ptsp.o am_bdy1.o am_bdy2.o \
	 am_bdy3.o am_bdy4.o am_bdy5.o am_db1.o am_db2.o am_id.o \
	 am_ex_pt.o am_ptli.o am_mf.o am_ptmi.o as_bdy1.o as_bdy2.o \
	 as_bdy3.o as_bdy4.o as_bdy5.o as_bdy6.o as_ex_pt.o as_id.o \
	 as_ptui.o as_ptmi.o lm.o smambdy1.o smasbdy1.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ uni3x.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ uni3x.mod ; fi

bparm.mod: Makefile bparm_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_bparm
MODULE_bparm:
	${RM} bparm.mod
	${LD} -dc -r -o bparm.mod bparm_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bparm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bparm.mod ; fi

lat.mod: Makefile aclchk.o aclclr.o aclcmp.o aclrep.o aclset.o adpcre.o \
	 adpdel.o adplist.o adpsh.o asclro.o asclrp.o ascre.o asdel.o \
	 aslist.o asmsg.o asrset.o assetf.o asseti.o asseto.o assetp.o \
	 asshow.o cbabo.o cbcre.o cbdel.o cbhalt.o cbhrun.o cbhstr.o \
	 cborun.o cbostr.o cbrout.o cbrxmt.o cbsrun.o cbsstr.o dbchgc.o \
	 dbrepb.o dbrepc.o dbreps.o dbsetc.o dbsetm.o exerr.o hicre.o \
	 hidel.o hiecan.o hierpt.o hifind.o hihra.o hihri.o hihsts.o \
	 hiinit.o hiocmd.o hiopen.o hiora.o hioreq.o hiori.o hiosi.o \
	 hiosts.o hiqrpt.o hiqsts.o hirej.o hiscmd.o hises.o hissi.o \
	 histr.o hsrset.o hszero.o hxsts.o idlchk.o idlclr.o idlcmp.o \
	 idlset.o ifchk.o ifmsg.o latcom.o lscre.o lsdel.o lsdups.o \
	 lslist.o lslook.o lslsth.o lsmsg.o lsperm.o lsrem.o lsrset.o \
	 lsscan.o lsshow.o lstmo.o ndcre.o nddel.o ndfail.o ndlist.o \
	 ndpur.o ndshow.o ndzero.o obclon.o obcre.o obdel.o obfind.o \
	 oblist.o obrel.o obren.o obrset.o obsetf.o obshow.o oxses.o \
	 qrcre.o qrdel.o qrfind.o qrlist.o qrscan.o sb1inp.o sb1out.o \
	 sbacc.o sbcre.o sbdel.o sbdups.o sbfind.o sbopen.o sbrej.o \
	 sbria.o sbsig.o sbstop.o sbstr.o ticelp.o tocelp.o vcshow.o \
	 axrate.o grpret.o hxses.o ixerr.o latadpsubs.o latclose.o \
	 latdefsvc.o lathashsubs.o latlioc.o latlog.o latlrput.o \
	 latlrsrv.o latmain.o latopen.o latsub.o lattimer.o lattioc.o \
	 lattli.o latursrv.o latuwput.o ofmsg.o strchk.o strcvt.o \
	 strdif.o strequ.o strinp.o strmov.o strret.o sxgetc.o sxputc.o \
	 sxses.o sxsig.o
	@${MAKE} -${MAKEFLAGS} MODULE_lat
MODULE_lat:
	${RM} lat.mod
	${LD} -dc -r -o lat.mod aclchk.o aclclr.o aclcmp.o aclrep.o aclset.o \
	 adpcre.o adpdel.o adplist.o adpsh.o asclro.o asclrp.o ascre.o \
	 asdel.o aslist.o asmsg.o asrset.o assetf.o asseti.o asseto.o \
	 assetp.o asshow.o cbabo.o cbcre.o cbdel.o cbhalt.o cbhrun.o \
	 cbhstr.o cborun.o cbostr.o cbrout.o cbrxmt.o cbsrun.o cbsstr.o \
	 dbchgc.o dbrepb.o dbrepc.o dbreps.o dbsetc.o dbsetm.o exerr.o \
	 hicre.o hidel.o hiecan.o hierpt.o hifind.o hihra.o hihri.o \
	 hihsts.o hiinit.o hiocmd.o hiopen.o hiora.o hioreq.o hiori.o \
	 hiosi.o hiosts.o hiqrpt.o hiqsts.o hirej.o hiscmd.o hises.o \
	 hissi.o histr.o hsrset.o hszero.o hxsts.o idlchk.o idlclr.o \
	 idlcmp.o idlset.o ifchk.o ifmsg.o latcom.o lscre.o lsdel.o \
	 lsdups.o lslist.o lslook.o lslsth.o lsmsg.o lsperm.o lsrem.o \
	 lsrset.o lsscan.o lsshow.o lstmo.o ndcre.o nddel.o ndfail.o \
	 ndlist.o ndpur.o ndshow.o ndzero.o obclon.o obcre.o obdel.o \
	 obfind.o oblist.o obrel.o obren.o obrset.o obsetf.o obshow.o \
	 oxses.o qrcre.o qrdel.o qrfind.o qrlist.o qrscan.o sb1inp.o \
	 sb1out.o sbacc.o sbcre.o sbdel.o sbdups.o sbfind.o sbopen.o \
	 sbrej.o sbria.o sbsig.o sbstop.o sbstr.o ticelp.o tocelp.o \
	 vcshow.o axrate.o grpret.o hxses.o ixerr.o latadpsubs.o \
	 latclose.o latdefsvc.o lathashsubs.o latlioc.o latlog.o \
	 latlrput.o latlrsrv.o latmain.o latopen.o latsub.o lattimer.o \
	 lattioc.o lattli.o latursrv.o latuwput.o ofmsg.o strchk.o \
	 strcvt.o strdif.o strequ.o strinp.o strmov.o strret.o sxgetc.o \
	 sxputc.o sxses.o sxsig.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lat.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lat.mod ; fi

lv.mod: Makefile lv_block.o lv_config.o lv_defect.o lv_ioctls.o lv_kdb.o \
	 lv_lvsubr.o lv_mircons.o lv_pbuf.o lv_phys.o lv_schedule.o \
	 lv_strategy.o lv_subr.o lv_syscalls.o lv_vgda.o lv_vgsa.o
	@${MAKE} -${MAKEFLAGS} MODULE_lv
MODULE_lv:
	${RM} lv.mod
	${LD} -dc -r -o lv.mod lv_block.o lv_config.o lv_defect.o \
	 lv_ioctls.o lv_kdb.o lv_lvsubr.o lv_mircons.o lv_pbuf.o \
	 lv_phys.o lv_schedule.o lv_strategy.o lv_subr.o lv_syscalls.o \
	 lv_vgda.o lv_vgsa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lv.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lv.mod ; fi

advfs.mod: Makefile bs_access.o bs_bitfile_sets.o bs_bmt_util.o \
	 bs_buffer2.o bs_copy.o bs_create.o bs_delete.o bs_domain.o \
	 bs_errlst.o bs_extents.o bs_init.o bs_inmem_map.o bs_migrate.o \
	 bs_misc.o bs_msg_queue.o bs_params.o bs_qio.o bs_sbm.o \
	 bs_service_class.o bs_shadow.o bs_stg.o bs_stripe.o bs_tagdir.o \
	 ftx_recovery.o ftx_routines.o ms_generic_locks.o ms_logger.o \
	 ms_mode.o ms_privates.o ms_public.o fs_create.o fs_dir_init.o \
	 fs_dir_lookup.o fs_file_sets.o fs_quota.o fs_read_write.o \
	 mss_common.o mss_entry.o mss_fs.o mss_lock.o mss_log.o \
	 mss_misc.o mss_pqd.o mss_send.o mss_space.o mss_syscall.o \
	 ter_inmem_map.o ter_ondisk_map.o ter_stg.o msfs_cfg.o \
	 msfs_config.o msfs_io.o msfs_lookup.o msfs_misc.o \
	 msfs_proplist.o msfs_vfsops.o msfs_vnops.o
	@${MAKE} -${MAKEFLAGS} MODULE_advfs
MODULE_advfs:
	${RM} advfs.mod
	${LD} -dc -r -o advfs.mod bs_access.o bs_bitfile_sets.o \
	 bs_bmt_util.o bs_buffer2.o bs_copy.o bs_create.o bs_delete.o \
	 bs_domain.o bs_errlst.o bs_extents.o bs_init.o bs_inmem_map.o \
	 bs_migrate.o bs_misc.o bs_msg_queue.o bs_params.o bs_qio.o \
	 bs_sbm.o bs_service_class.o bs_shadow.o bs_stg.o bs_stripe.o \
	 bs_tagdir.o ftx_recovery.o ftx_routines.o ms_generic_locks.o \
	 ms_logger.o ms_mode.o ms_privates.o ms_public.o fs_create.o \
	 fs_dir_init.o fs_dir_lookup.o fs_file_sets.o fs_quota.o \
	 fs_read_write.o mss_common.o mss_entry.o mss_fs.o mss_lock.o \
	 mss_log.o mss_misc.o mss_pqd.o mss_send.o mss_space.o \
	 mss_syscall.o ter_inmem_map.o ter_ondisk_map.o ter_stg.o \
	 msfs_cfg.o msfs_config.o msfs_io.o msfs_lookup.o msfs_misc.o \
	 msfs_proplist.o msfs_vfsops.o msfs_vnops.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ advfs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ advfs.mod ; fi

packetfilter.mod: Makefile bpf_filter.o pfilt.o pfilt_bpf.o
	@${MAKE} -${MAKEFLAGS} MODULE_packetfilter
MODULE_packetfilter:
	${RM} packetfilter.mod
	${LD} -dc -r -o packetfilter.mod bpf_filter.o pfilt.o pfilt_bpf.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ packetfilter.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ packetfilter.mod ; fi

net.mod: Makefile net_cfg.o raw_cb.o raw_usrreq.o route.o
	@${MAKE} -${MAKEFLAGS} MODULE_net
MODULE_net:
	${RM} net.mod
	${LD} -dc -r -o net.mod net_cfg.o raw_cb.o raw_usrreq.o route.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ net.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ net.mod ; fi

netrain.mod: Makefile netrain_cfg.o netrain.o if_nr.o
	@${MAKE} -${MAKEFLAGS} MODULE_netrain
MODULE_netrain:
	${RM} netrain.mod
	${LD} -dc -r -o netrain.mod netrain_cfg.o netrain.o if_nr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ netrain.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ netrain.mod ; fi

ether.mod: Makefile if_ethersubr.o if_ether.o
	@${MAKE} -${MAKEFLAGS} MODULE_ether
MODULE_ether:
	${RM} ether.mod
	${LD} -dc -r -o ether.mod if_ethersubr.o if_ether.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ether.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ether.mod ; fi

loop.mod: Makefile if_loop.o
	@${MAKE} -${MAKEFLAGS} MODULE_loop
MODULE_loop:
	${RM} loop.mod
	${LD} -dc -r -o loop.mod if_loop.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ loop.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ loop.mod ; fi

sl.mod: Makefile if_sl.o
	@${MAKE} -${MAKEFLAGS} MODULE_sl
MODULE_sl:
	${RM} sl.mod
	${LD} -dc -r -o sl.mod if_sl.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sl.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sl.mod ; fi

ppp.mod: Makefile ppp_init.o ppp_if.o ppp_async.o ppp_comp.o \
	 vjcompress.o bsd_comp.o
	@${MAKE} -${MAKEFLAGS} MODULE_ppp
MODULE_ppp:
	${RM} ppp.mod
	${LD} -dc -r -o ppp.mod ppp_init.o ppp_if.o ppp_async.o ppp_comp.o \
	 vjcompress.o bsd_comp.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ppp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ppp.mod ; fi

inet.mod: Makefile inet_cfg.o igmp.o in.o in_pcb.o in_proto.o ip_icmp.o \
	 ip_input.o ip_mroute.o ip_output.o ip_screen.o pmtu.o raw_ip.o \
	 tcp_debug.o tcp_input.o tcp_output.o tcp_subr.o tcp_timer.o \
	 tcp_usrreq.o udp_usrreq.o
	@${MAKE} -${MAKEFLAGS} MODULE_inet
MODULE_inet:
	${RM} inet.mod
	${LD} -dc -r -o inet.mod inet_cfg.o igmp.o in.o in_pcb.o in_proto.o \
	 ip_icmp.o ip_input.o ip_mroute.o ip_output.o ip_screen.o pmtu.o \
	 raw_ip.o tcp_debug.o tcp_input.o tcp_output.o tcp_subr.o \
	 tcp_timer.o tcp_usrreq.o udp_usrreq.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ inet.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ inet.mod ; fi

nfs.mod: Makefile nfs3_vfsops.o nfs3_vnodeops.o nfs3_xdr.o nfs_client.o \
	 nfs_common.o nfs_config.o nfs_dump.o nfs_subr.o nfs_vfsops.o \
	 nfs_vnodeops.o nfs_xdr.o prop_xdr.o auth_kern.o authunix_prot.o \
	 clnt_kudp.o clnt_ktcp.o clnt_perror.o kudp_fastsend.o \
	 pmap_kgetport.o pmap_prot.o pmap_rmt.o rpc_callmsg.o rpc_prot.o \
	 subr_kudp.o svc.o svc_auth.o svc_auth_unix.o svc_kudp.o \
	 svc_ktcp.o xdr.o xdr_array.o xdr_mbuf.o xdr_mem.o \
	 xdr_reference.o bootparam_xdr.o mountxdr.o klm_kprot.o \
	 klm_lockmgr.o
	@${MAKE} -${MAKEFLAGS} MODULE_nfs
MODULE_nfs:
	${RM} nfs.mod
	${LD} -dc -r -o nfs.mod nfs3_vfsops.o nfs3_vnodeops.o nfs3_xdr.o \
	 nfs_client.o nfs_common.o nfs_config.o nfs_dump.o nfs_subr.o \
	 nfs_vfsops.o nfs_vnodeops.o nfs_xdr.o prop_xdr.o auth_kern.o \
	 authunix_prot.o clnt_kudp.o clnt_ktcp.o clnt_perror.o \
	 kudp_fastsend.o pmap_kgetport.o pmap_prot.o pmap_rmt.o \
	 rpc_callmsg.o rpc_prot.o subr_kudp.o svc.o svc_auth.o \
	 svc_auth_unix.o svc_kudp.o svc_ktcp.o xdr.o xdr_array.o \
	 xdr_mbuf.o xdr_mem.o xdr_reference.o bootparam_xdr.o mountxdr.o \
	 klm_kprot.o klm_lockmgr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ nfs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ nfs.mod ; fi

nfs_server.mod: Makefile nfs_server.o nfs3_server.o
	@${MAKE} -${MAKEFLAGS} MODULE_nfs_server
MODULE_nfs_server:
	${RM} nfs_server.mod
	${LD} -dc -r -o nfs_server.mod nfs_server.o nfs3_server.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ nfs_server.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ nfs_server.mod ; fi

procfs.mod: Makefile procfs_subrs.o procfs_vfsops.o procfs_vnops.o \
	 procfs_ioctl.o
	@${MAKE} -${MAKEFLAGS} MODULE_procfs
MODULE_procfs:
	${RM} procfs.mod
	${LD} -dc -r -o procfs.mod procfs_subrs.o procfs_vfsops.o \
	 procfs_vnops.o procfs_ioctl.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ procfs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ procfs.mod ; fi

notprocfs.mod: Makefile procfs_vfsops_stubs.o procfs_subrs_stubs.o \
	 procfs_vnops_stubs.o
	@${MAKE} -${MAKEFLAGS} MODULE_notprocfs
MODULE_notprocfs:
	${RM} notprocfs.mod
	${LD} -dc -r -o notprocfs.mod procfs_vfsops_stubs.o \
	 procfs_subrs_stubs.o procfs_vnops_stubs.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ notprocfs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ notprocfs.mod ; fi

snmpinfo.mod: Makefile snmpinfo.o
	@${MAKE} -${MAKEFLAGS} MODULE_snmpinfo
MODULE_snmpinfo:
	${RM} snmpinfo.mod
	${LD} -dc -r -o snmpinfo.mod snmpinfo.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ snmpinfo.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ snmpinfo.mod ; fi

bufcall.mod: Makefile str_memory.o
	@${MAKE} -${MAKEFLAGS} MODULE_bufcall
MODULE_bufcall:
	${RM} bufcall.mod
	${LD} -dc -r -o bufcall.mod str_memory.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bufcall.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bufcall.mod ; fi

streams.mod: Makefile nd.o str_cfg.o str_env.o str_filesys.o str_init.o \
	 str_modsw.o str_osr.o str_runq.o str_scalls.o str_shead.o \
	 str_subr.o str_support.o str_synch.o str_tty.o str_util.o \
	 str_weld.o
	@${MAKE} -${MAKEFLAGS} MODULE_streams
MODULE_streams:
	${RM} streams.mod
	${LD} -dc -r -o streams.mod nd.o str_cfg.o str_env.o str_filesys.o \
	 str_init.o str_modsw.o str_osr.o str_runq.o str_scalls.o \
	 str_shead.o str_subr.o str_support.o str_synch.o str_tty.o \
	 str_util.o str_weld.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ streams.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ streams.mod ; fi

streams_debug.mod: Makefile str_debug.o
	@${MAKE} -${MAKEFLAGS} MODULE_streams_debug
MODULE_streams_debug:
	${RM} streams_debug.mod
	${LD} -dc -r -o streams_debug.mod str_debug.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ streams_debug.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ streams_debug.mod ; fi

dlb.mod: Makefile dlb.o
	@${MAKE} -${MAKEFLAGS} MODULE_dlb
MODULE_dlb:
	${RM} dlb.mod
	${LD} -dc -r -o dlb.mod dlb.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dlb.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dlb.mod ; fi

dlpi.mod: Makefile dlpi_data.o dl.o dlhash.o dlioctl.o dlprim.o dlproc.o \
	 dltimer.o dlutil.o
	@${MAKE} -${MAKEFLAGS} MODULE_dlpi
MODULE_dlpi:
	${RM} dlpi.mod
	${LD} -dc -r -o dlpi.mod dlpi_data.o dl.o dlhash.o dlioctl.o \
	 dlprim.o dlproc.o dltimer.o dlutil.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dlpi.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dlpi.mod ; fi

ifnet.mod: Makefile ifnet.o
	@${MAKE} -${MAKEFLAGS} MODULE_ifnet
MODULE_ifnet:
	${RM} ifnet.mod
	${LD} -dc -r -o ifnet.mod ifnet.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ifnet.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ifnet.mod ; fi

kinfo.mod: Makefile kinfo.o
	@${MAKE} -${MAKEFLAGS} MODULE_kinfo
MODULE_kinfo:
	${RM} kinfo.mod
	${LD} -dc -r -o kinfo.mod kinfo.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kinfo.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kinfo.mod ; fi

strstd.mod: Makefile log.o sad.o standard.o
	@${MAKE} -${MAKEFLAGS} MODULE_strstd
MODULE_strstd:
	${RM} strstd.mod
	${LD} -dc -r -o strstd.mod log.o sad.o standard.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ strstd.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ strstd.mod ; fi

svvs.mod: Makefile svvs.o
	@${MAKE} -${MAKEFLAGS} MODULE_svvs
MODULE_svvs:
	${RM} svvs.mod
	${LD} -dc -r -o svvs.mod svvs.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ svvs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ svvs.mod ; fi

timod.mod: Makefile timod.o
	@${MAKE} -${MAKEFLAGS} MODULE_timod
MODULE_timod:
	${RM} timod.mod
	${LD} -dc -r -o timod.mod timod.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ timod.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ timod.mod ; fi

tirdwr.mod: Makefile tirdwr.o
	@${MAKE} -${MAKEFLAGS} MODULE_tirdwr
MODULE_tirdwr:
	${RM} tirdwr.mod
	${LD} -dc -r -o tirdwr.mod tirdwr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tirdwr.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tirdwr.mod ; fi

ldtty.mod: Makefile ldtty.o ldtty_compat.o ldtty_euc.o
	@${MAKE} -${MAKEFLAGS} MODULE_ldtty
MODULE_ldtty:
	${RM} ldtty.mod
	${LD} -dc -r -o ldtty.mod ldtty.o ldtty_compat.o ldtty_euc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ldtty.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ldtty.mod ; fi

xtiso.mod: Makefile xtiso.o
	@${MAKE} -${MAKEFLAGS} MODULE_xtiso
MODULE_xtiso:
	${RM} xtiso.mod
	${LD} -dc -r -o xtiso.mod xtiso.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xtiso.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xtiso.mod ; fi

pts.mod: Makefile pty.o
	@${MAKE} -${MAKEFLAGS} MODULE_pts
MODULE_pts:
	${RM} pts.mod
	${LD} -dc -r -o pts.mod pty.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pts.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pts.mod ; fi

ufs.mod: Makefile mfs_vfsops.o mfs_vnops.o ufs_alloc.o ufs_bmap.o \
	 ufs_cfg.o ufs_disksubr.o ufs_inode.o ufs_lookup.o ufs_physio.o \
	 ufs_proplist.o ufs_subr.o ufs_tables.o ufs_vfsops.o ufs_vnops.o \
	 spec_vnops.o
	@${MAKE} -${MAKEFLAGS} MODULE_ufs
MODULE_ufs:
	${RM} ufs.mod
	${LD} -dc -r -o ufs.mod mfs_vfsops.o mfs_vnops.o ufs_alloc.o \
	 ufs_bmap.o ufs_cfg.o ufs_disksubr.o ufs_inode.o ufs_lookup.o \
	 ufs_physio.o ufs_proplist.o ufs_subr.o ufs_tables.o \
	 ufs_vfsops.o ufs_vnops.o spec_vnops.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ufs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ufs.mod ; fi

uipc.mod: Makefile uipc_proto.o uipc_usrreq.o
	@${MAKE} -${MAKEFLAGS} MODULE_uipc
MODULE_uipc:
	${RM} uipc.mod
	${LD} -dc -r -o uipc.mod uipc_proto.o uipc_usrreq.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ uipc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ uipc.mod ; fi

vfs.mod: Makefile dead_vfsops.o dead_vnops.o fifo_vnops.o vfs_bio.o \
	 vfs_cache.o vfs_cfg.o vfs_flock.o vfs_lookup.o vfs_subr.o \
	 vfs_syscalls.o vfs_ubc.o vfs_vnops.o
	@${MAKE} -${MAKEFLAGS} MODULE_vfs
MODULE_vfs:
	${RM} vfs.mod
	${LD} -dc -r -o vfs.mod dead_vfsops.o dead_vnops.o fifo_vnops.o \
	 vfs_bio.o vfs_cache.o vfs_cfg.o vfs_flock.o vfs_lookup.o \
	 vfs_subr.o vfs_syscalls.o vfs_ubc.o vfs_vnops.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vfs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vfs.mod ; fi

vm.mod: Makefile k_mape_inv.o k_mape_io.o k_mape_mem.o u_mape_anon.o \
	 u_mape_dev.o u_mape_seg.o u_mape_shm.o u_mape_ssm.o u_mape_vp.o \
	 vm_anon.o vm_anonpage.o vm_cfg.o vm_cmap.o vm_fault.o vm_kern.o \
	 vm_kmap.o vm_map.o vm_object.o vm_pagelru.o vm_resident.o \
	 vm_subr.o vm_swap.o vm_umap.o vm_unix.o vm_user.o vm_vlock.o \
	 vpage.o
	@${MAKE} -${MAKEFLAGS} MODULE_vm
MODULE_vm:
	${RM} vm.mod
	${LD} -dc -r -o vm.mod k_mape_inv.o k_mape_io.o k_mape_mem.o \
	 u_mape_anon.o u_mape_dev.o u_mape_seg.o u_mape_shm.o \
	 u_mape_ssm.o u_mape_vp.o vm_anon.o vm_anonpage.o vm_cfg.o \
	 vm_cmap.o vm_fault.o vm_kern.o vm_kmap.o vm_map.o vm_object.o \
	 vm_pagelru.o vm_resident.o vm_subr.o vm_swap.o vm_umap.o \
	 vm_unix.o vm_user.o vm_vlock.o vpage.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vm.mod ; fi

_lmf_.mod: Makefile kern_lmf.o
	@${MAKE} -${MAKEFLAGS} MODULE__lmf_
MODULE__lmf_:
	${RM} _lmf_.mod
	${LD} -dc -r -o _lmf_.mod kern_lmf.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ _lmf_.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ _lmf_.mod ; fi

pckt.mod: Makefile pckt.o
	@${MAKE} -${MAKEFLAGS} MODULE_pckt
MODULE_pckt:
	${RM} pckt.mod
	${LD} -dc -r -o pckt.mod pckt.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pckt.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pckt.mod ; fi

ntp_time.mod: Makefile kern_ntptime.o
	@${MAKE} -${MAKEFLAGS} MODULE_ntp_time
MODULE_ntp_time:
	${RM} ntp_time.mod
	${LD} -dc -r -o ntp_time.mod kern_ntptime.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ntp_time.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ntp_time.mod ; fi

mlog.mod: Makefile memlog.o
	@${MAKE} -${MAKEFLAGS} MODULE_mlog
MODULE_mlog:
	${RM} mlog.mod
	${LD} -dc -r -o mlog.mod memlog.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mlog.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mlog.mod ; fi

profiling.mod: Makefile subr_mcount.o
	@${MAKE} -${MAKEFLAGS} MODULE_profiling
MODULE_profiling:
	${RM} profiling.mod
	${LD} -dc -r -o profiling.mod subr_mcount.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ profiling.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ profiling.mod ; fi

pty.mod: Makefile tty_pty.o
	@${MAKE} -${MAKEFLAGS} MODULE_pty
MODULE_pty:
	${RM} pty.mod
	${LD} -dc -r -o pty.mod tty_pty.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pty.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pty.mod ; fi

prf.mod: Makefile prf.o
	@${MAKE} -${MAKEFLAGS} MODULE_prf
MODULE_prf:
	${RM} prf.mod
	${LD} -dc -r -o prf.mod prf.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ prf.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ prf.mod ; fi

mach_co_stats.mod: Makefile callout_statistics.o
	@${MAKE} -${MAKEFLAGS} MODULE_mach_co_stats
MODULE_mach_co_stats:
	${RM} mach_co_stats.mod
	${LD} -dc -r -o mach_co_stats.mod callout_statistics.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mach_co_stats.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mach_co_stats.mod ; fi

mach_ipc_stats.mod: Makefile ipc_statistics.o
	@${MAKE} -${MAKEFLAGS} MODULE_mach_ipc_stats
MODULE_mach_ipc_stats:
	${RM} mach_ipc_stats.mod
	${LD} -dc -r -o mach_ipc_stats.mod ipc_statistics.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mach_ipc_stats.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mach_ipc_stats.mod ; fi

gwscreen.mod: Makefile gw_screen.o
	@${MAKE} -${MAKEFLAGS} MODULE_gwscreen
MODULE_gwscreen:
	${RM} gwscreen.mod
	${LD} -dc -r -o gwscreen.mod gw_screen.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ gwscreen.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ gwscreen.mod ; fi

pwrmgr.mod: Makefile pwrmgr.o
	@${MAKE} -${MAKEFLAGS} MODULE_pwrmgr
MODULE_pwrmgr:
	${RM} pwrmgr.mod
	${LD} -dc -r -o pwrmgr.mod pwrmgr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pwrmgr.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pwrmgr.mod ; fi

dec_audit.mod: Makefile kern_audit.o kern_auditcalls.o kern_auditdev.o
	@${MAKE} -${MAKEFLAGS} MODULE_dec_audit
MODULE_dec_audit:
	${RM} dec_audit.mod
	${LD} -dc -r -o dec_audit.mod kern_audit.o kern_auditcalls.o \
	 kern_auditdev.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dec_audit.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dec_audit.mod ; fi

sec_base.mod: Makefile sec_calls.o sec_socket.o sec_stream.o
	@${MAKE} -${MAKEFLAGS} MODULE_sec_base
MODULE_sec_base:
	${RM} sec_base.mod
	${LD} -dc -r -o sec_base.mod sec_calls.o sec_socket.o sec_stream.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_base.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_base.mod ; fi

sec_driver.mod: Makefile sec_driver.o
	@${MAKE} -${MAKEFLAGS} MODULE_sec_driver
MODULE_sec_driver:
	${RM} sec_driver.mod
	${LD} -dc -r -o sec_driver.mod sec_driver.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_driver.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_driver.mod ; fi

sec_mld.mod: Makefile sec_mld.o
	@${MAKE} -${MAKEFLAGS} MODULE_sec_mld
MODULE_sec_mld:
	${RM} sec_mld.mod
	${LD} -dc -r -o sec_mld.mod sec_mld.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_mld.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sec_mld.mod ; fi

dec_acl.mod: Makefile spd_pacl.o
	@${MAKE} -${MAKEFLAGS} MODULE_dec_acl
MODULE_dec_acl:
	${RM} dec_acl.mod
	${LD} -dc -r -o dec_acl.mod spd_pacl.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dec_acl.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dec_acl.mod ; fi

dce_acl_stubs.mod: Makefile dce_acl_stubs.o
	@${MAKE} -${MAKEFLAGS} MODULE_dce_acl_stubs
MODULE_dce_acl_stubs:
	${RM} dce_acl_stubs.mod
	${LD} -dc -r -o dce_acl_stubs.mod dce_acl_stubs.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dce_acl_stubs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dce_acl_stubs.mod ; fi

spd_cache.mod: Makefile spd_cache.o
	@${MAKE} -${MAKEFLAGS} MODULE_spd_cache
MODULE_spd_cache:
	${RM} spd_cache.mod
	${LD} -dc -r -o spd_cache.mod spd_cache.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ spd_cache.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ spd_cache.mod ; fi

acl_stubs.mod: Makefile acl_stubs.o
	@${MAKE} -${MAKEFLAGS} MODULE_acl_stubs
MODULE_acl_stubs:
	${RM} acl_stubs.mod
	${LD} -dc -r -o acl_stubs.mod acl_stubs.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ acl_stubs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ acl_stubs.mod ; fi

spd_mac.mod: Makefile spd_mac.o
	@${MAKE} -${MAKEFLAGS} MODULE_spd_mac
MODULE_spd_mac:
	${RM} spd_mac.mod
	${LD} -dc -r -o spd_mac.mod spd_mac.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ spd_mac.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ spd_mac.mod ; fi

spd_misc.mod: Makefile spd_misc.o
	@${MAKE} -${MAKEFLAGS} MODULE_spd_misc
MODULE_spd_misc:
	${RM} spd_misc.mod
	${LD} -dc -r -o spd_misc.mod spd_misc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ spd_misc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ spd_misc.mod ; fi

arch_alpha.mod: Makefile alpha_exception.o alpha_ptrace.o alpha_signal.o \
	 atomic_ops.o byte_swap.o clock.o coff_subr.o context.o copy.o \
	 cpu.o crc.o __divl.o __divq.o __divlu.o __divqu.o __reml.o \
	 __remq.o __remlu.o __remqu.o ots_div_alpha.o \
	 ots_div_data_alpha.o ots_extv_alpha.o ots_extv_vol_alpha.o \
	 ots_extzv_alpha.o ots_extzv_vol_alpha.o ots_insv_alpha.o \
	 ots_insv_vol_alpha.o ots_location_alpha.o ots_move_alpha.o \
	 ots_movem_alpha.o ots_fill_alpha.o ots_zero_alpha.o \
	 ots_translate_alpha.o ots_strcmp_eql_alpha.o \
	 ots_strcmp_eqlp_alpha.o ots_strcmp_leq_alpha.o \
	 ots_strcmp_leqp_alpha.o ots_strcmp_lss_alpha.o \
	 ots_strcmp_lssp_alpha.o dumpsys.o entry.o exec_config.o \
	 exec_subr.o fastcopy.o in_checksum.o intr.o kernargs.o locore.o \
	 lockprim.o addupc.o machdep.o mem.o ovbcopy.o pal_lib.o pcb.o \
	 prom.o spl.o super.o syscall_trap.o trap.o softfp.o \
	 ieee_float_math.o 64bit_math.o bootio.o ul.o usercopy.o \
	 nofault.o vm_machdep.o lww.o lwu.o autoconf.o cons_sw.o \
	 console.o cpusw.o io_access.o hal_lmf.o hal_sysinfo.o \
	 driver_support.o ldbl_driver_support.o \
	 ldbl_controller_support.o stanza_resolver.o topology.o \
	 handler.o tty_def.o io_resource.o mips_dummy.o pcmcia_fnc.o \
	 error_event.o alloc_smt.o
	@${MAKE} -${MAKEFLAGS} MODULE_arch_alpha
MODULE_arch_alpha:
	${RM} arch_alpha.mod
	${LD} -dc -r -o arch_alpha.mod alpha_exception.o alpha_ptrace.o \
	 alpha_signal.o atomic_ops.o byte_swap.o clock.o coff_subr.o \
	 context.o copy.o cpu.o crc.o __divl.o __divq.o __divlu.o \
	 __divqu.o __reml.o __remq.o __remlu.o __remqu.o ots_div_alpha.o \
	 ots_div_data_alpha.o ots_extv_alpha.o ots_extv_vol_alpha.o \
	 ots_extzv_alpha.o ots_extzv_vol_alpha.o ots_insv_alpha.o \
	 ots_insv_vol_alpha.o ots_location_alpha.o ots_move_alpha.o \
	 ots_movem_alpha.o ots_fill_alpha.o ots_zero_alpha.o \
	 ots_translate_alpha.o ots_strcmp_eql_alpha.o \
	 ots_strcmp_eqlp_alpha.o ots_strcmp_leq_alpha.o \
	 ots_strcmp_leqp_alpha.o ots_strcmp_lss_alpha.o \
	 ots_strcmp_lssp_alpha.o dumpsys.o entry.o exec_config.o \
	 exec_subr.o fastcopy.o in_checksum.o intr.o kernargs.o locore.o \
	 lockprim.o addupc.o machdep.o mem.o ovbcopy.o pal_lib.o pcb.o \
	 prom.o spl.o super.o syscall_trap.o trap.o softfp.o \
	 ieee_float_math.o 64bit_math.o bootio.o ul.o usercopy.o \
	 nofault.o vm_machdep.o lww.o lwu.o autoconf.o cons_sw.o \
	 console.o cpusw.o io_access.o hal_lmf.o hal_sysinfo.o \
	 driver_support.o ldbl_driver_support.o \
	 ldbl_controller_support.o stanza_resolver.o topology.o \
	 handler.o tty_def.o io_resource.o mips_dummy.o pcmcia_fnc.o \
	 error_event.o alloc_smt.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ arch_alpha.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ arch_alpha.mod ; fi

in_cksum.mod: Makefile in_cksum.o
	@${MAKE} -${MAKEFLAGS} MODULE_in_cksum
MODULE_in_cksum:
	${RM} in_cksum.mod
	${LD} -dc -r -o in_cksum.mod in_cksum.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ in_cksum.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ in_cksum.mod ; fi

pfm.mod: Makefile pfm.o
	@${MAKE} -${MAKEFLAGS} MODULE_pfm
MODULE_pfm:
	${RM} pfm.mod
	${LD} -dc -r -o pfm.mod pfm.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pfm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pfm.mod ; fi

arch_alphapmap.mod: Makefile pmap.o pmap_debug.o pmap_update.o
	@${MAKE} -${MAKEFLAGS} MODULE_arch_alphapmap
MODULE_arch_alphapmap:
	${RM} arch_alphapmap.mod
	${LD} -dc -r -o arch_alphapmap.mod pmap.o pmap_debug.o pmap_update.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ arch_alphapmap.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ arch_alphapmap.mod ; fi

fp.mod: Makefile fp_ieee.o fp_ieee_handler.o fp_ascii.o fp_result.o \
	 fp_scale.o fp_trigger.o fp_tables.o fp_emulator.o fp_emulate.o
	@${MAKE} -${MAKEFLAGS} MODULE_fp
MODULE_fp:
	${RM} fp.mod
	${LD} -dc -r -o fp.mod fp_ieee.o fp_ieee_handler.o fp_ascii.o \
	 fp_result.o fp_scale.o fp_trigger.o fp_tables.o fp_emulator.o \
	 fp_emulate.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fp.mod ; fi

mcount.mod: Makefile mcount.o
	@${MAKE} -${MAKEFLAGS} MODULE_mcount
MODULE_mcount:
	${RM} mcount.mod
	${LD} -dc -r -o mcount.mod mcount.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcount.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcount.mod ; fi

kn15aa_mult.mod: Makefile kn15aa_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn15aa_mult
MODULE_kn15aa_mult:
	${RM} kn15aa_mult.mod
	${LD} -dc -r -o kn15aa_mult.mod kn15aa_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn15aa_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn15aa_mult.mod ; fi

kn15aa.mod: Makefile kn15aa.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn15aa
MODULE_kn15aa:
	${RM} kn15aa.mod
	${LD} -dc -r -o kn15aa.mod kn15aa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn15aa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn15aa.mod ; fi

kn16aa_mult.mod: Makefile kn16aa_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn16aa_mult
MODULE_kn16aa_mult:
	${RM} kn16aa_mult.mod
	${LD} -dc -r -o kn16aa_mult.mod kn16aa_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn16aa_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn16aa_mult.mod ; fi

kn16aa.mod: Makefile kn16aa.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn16aa
MODULE_kn16aa:
	${RM} kn16aa.mod
	${LD} -dc -r -o kn16aa.mod kn16aa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn16aa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn16aa.mod ; fi

kn430_mult.mod: Makefile kn430_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn430_mult
MODULE_kn430_mult:
	${RM} kn430_mult.mod
	${LD} -dc -r -o kn430_mult.mod kn430_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn430_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn430_mult.mod ; fi

kn430.mod: Makefile kn430.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn430
MODULE_kn430:
	${RM} kn430.mod
	${LD} -dc -r -o kn430.mod kn430.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn430.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn430.mod ; fi

kn430_common.mod: Makefile dec4000_cons.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn430_common
MODULE_kn430_common:
	${RM} kn430_common.mod
	${LD} -dc -r -o kn430_common.mod dec4000_cons.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn430_common.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn430_common.mod ; fi

kn7aa_mult.mod: Makefile kn7aa_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn7aa_mult
MODULE_kn7aa_mult:
	${RM} kn7aa_mult.mod
	${LD} -dc -r -o kn7aa_mult.mod kn7aa_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn7aa_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn7aa_mult.mod ; fi

kn7aa.mod: Makefile kn7aa.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn7aa
MODULE_kn7aa:
	${RM} kn7aa.mod
	${LD} -dc -r -o kn7aa.mod kn7aa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn7aa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn7aa.mod ; fi

kn7aa_common.mod: Makefile lsbinit.o lsb_iop.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn7aa_common
MODULE_kn7aa_common:
	${RM} kn7aa_common.mod
	${LD} -dc -r -o kn7aa_common.mod lsbinit.o lsb_iop.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn7aa_common.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn7aa_common.mod ; fi

kn8ae_mult.mod: Makefile kn8ae_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn8ae_mult
MODULE_kn8ae_mult:
	${RM} kn8ae_mult.mod
	${LD} -dc -r -o kn8ae_mult.mod kn8ae_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn8ae_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn8ae_mult.mod ; fi

kn8ae.mod: Makefile kn8ae.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn8ae
MODULE_kn8ae:
	${RM} kn8ae.mod
	${LD} -dc -r -o kn8ae.mod kn8ae.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn8ae.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn8ae.mod ; fi

kn8ae_common.mod: Makefile tlsbinit.o tlsb_iop.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn8ae_common
MODULE_kn8ae_common:
	${RM} kn8ae_common.mod
	${LD} -dc -r -o kn8ae_common.mod tlsbinit.o tlsb_iop.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn8ae_common.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn8ae_common.mod ; fi

dc21171_mult.mod: Makefile dc21171_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_dc21171_mult
MODULE_dc21171_mult:
	${RM} dc21171_mult.mod
	${LD} -dc -r -o dc21171_mult.mod dc21171_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc21171_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc21171_mult.mod ; fi

dc21171.mod: Makefile dc21171.o
	@${MAKE} -${MAKEFLAGS} MODULE_dc21171
MODULE_dc21171:
	${RM} dc21171.mod
	${LD} -dc -r -o dc21171.mod dc21171.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc21171.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc21171.mod ; fi

kn121_mult.mod: Makefile kn121_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn121_mult
MODULE_kn121_mult:
	${RM} kn121_mult.mod
	${LD} -dc -r -o kn121_mult.mod kn121_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn121_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn121_mult.mod ; fi

kn121.mod: Makefile kn121.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn121
MODULE_kn121:
	${RM} kn121.mod
	${LD} -dc -r -o kn121.mod kn121.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn121.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn121.mod ; fi

kn25_mult.mod: Makefile kn25_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn25_mult
MODULE_kn25_mult:
	${RM} kn25_mult.mod
	${LD} -dc -r -o kn25_mult.mod kn25_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn25_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn25_mult.mod ; fi

kn25.mod: Makefile kn25.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn25
MODULE_kn25:
	${RM} kn25.mod
	${LD} -dc -r -o kn25.mod kn25.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn25.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn25.mod ; fi

kn450_mult.mod: Makefile kn450_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn450_mult
MODULE_kn450_mult:
	${RM} kn450_mult.mod
	${LD} -dc -r -o kn450_mult.mod kn450_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn450_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn450_mult.mod ; fi

kn450.mod: Makefile kn450.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn450
MODULE_kn450:
	${RM} kn450.mod
	${LD} -dc -r -o kn450.mod kn450.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn450.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn450.mod ; fi

cbus2_pci_mult.mod: Makefile cbus2_pci_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_cbus2_pci_mult
MODULE_cbus2_pci_mult:
	${RM} cbus2_pci_mult.mod
	${LD} -dc -r -o cbus2_pci_mult.mod cbus2_pci_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cbus2_pci_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cbus2_pci_mult.mod ; fi

cbus2_pci.mod: Makefile cbus2_pci.o
	@${MAKE} -${MAKEFLAGS} MODULE_cbus2_pci
MODULE_cbus2_pci:
	${RM} cbus2_pci.mod
	${LD} -dc -r -o cbus2_pci.mod cbus2_pci.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cbus2_pci.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cbus2_pci.mod ; fi

kn470_mult.mod: Makefile kn470_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn470_mult
MODULE_kn470_mult:
	${RM} kn470_mult.mod
	${LD} -dc -r -o kn470_mult.mod kn470_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn470_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn470_mult.mod ; fi

kn470.mod: Makefile kn470.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn470
MODULE_kn470:
	${RM} kn470.mod
	${LD} -dc -r -o kn470.mod kn470.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn470.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn470.mod ; fi

kn20aa_mult.mod: Makefile kn20aa_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn20aa_mult
MODULE_kn20aa_mult:
	${RM} kn20aa_mult.mod
	${LD} -dc -r -o kn20aa_mult.mod kn20aa_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn20aa_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn20aa_mult.mod ; fi

kn20aa.mod: Makefile kn20aa.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn20aa
MODULE_kn20aa:
	${RM} kn20aa.mod
	${LD} -dc -r -o kn20aa.mod kn20aa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn20aa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn20aa.mod ; fi

kn22a_mult.mod: Makefile kn22a_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn22a_mult
MODULE_kn22a_mult:
	${RM} kn22a_mult.mod
	${LD} -dc -r -o kn22a_mult.mod kn22a_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn22a_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn22a_mult.mod ; fi

kn22a.mod: Makefile kn22a.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn22a
MODULE_kn22a:
	${RM} kn22a.mod
	${LD} -dc -r -o kn22a.mod kn22a.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn22a.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn22a.mod ; fi

ebp10_mult.mod: Makefile ebp10_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebp10_mult
MODULE_ebp10_mult:
	${RM} ebp10_mult.mod
	${LD} -dc -r -o ebp10_mult.mod ebp10_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebp10_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebp10_mult.mod ; fi

ebp10.mod: Makefile ebp10.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebp10
MODULE_ebp10:
	${RM} ebp10.mod
	${LD} -dc -r -o ebp10.mod ebp10.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebp10.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebp10.mod ; fi

eb64p_mult.mod: Makefile eb64p_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb64p_mult
MODULE_eb64p_mult:
	${RM} eb64p_mult.mod
	${LD} -dc -r -o eb64p_mult.mod eb64p_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb64p_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb64p_mult.mod ; fi

eb64p.mod: Makefile eb64p.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb64p
MODULE_eb64p:
	${RM} eb64p.mod
	${LD} -dc -r -o eb64p.mod eb64p.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb64p.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb64p.mod ; fi

eb64p_pallib.mod: Makefile eb64p_pallib.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb64p_pallib
MODULE_eb64p_pallib:
	${RM} eb64p_pallib.mod
	${LD} -dc -r -o eb64p_pallib.mod eb64p_pallib.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb64p_pallib.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb64p_pallib.mod ; fi

eb66_mult.mod: Makefile eb66_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb66_mult
MODULE_eb66_mult:
	${RM} eb66_mult.mod
	${LD} -dc -r -o eb66_mult.mod eb66_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb66_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb66_mult.mod ; fi

eb66.mod: Makefile eb66.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb66
MODULE_eb66:
	${RM} eb66.mod
	${LD} -dc -r -o eb66.mod eb66.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb66.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb66.mod ; fi

eb66_pallib.mod: Makefile eb66_pallib.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb66_pallib
MODULE_eb66_pallib:
	${RM} eb66_pallib.mod
	${LD} -dc -r -o eb66_pallib.mod eb66_pallib.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb66_pallib.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb66_pallib.mod ; fi

eb164_mult.mod: Makefile eb164_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb164_mult
MODULE_eb164_mult:
	${RM} eb164_mult.mod
	${LD} -dc -r -o eb164_mult.mod eb164_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb164_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb164_mult.mod ; fi

eb164.mod: Makefile eb164.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb164
MODULE_eb164:
	${RM} eb164.mod
	${LD} -dc -r -o eb164.mod eb164.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb164.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb164.mod ; fi

eb164_pallib.mod: Makefile eb164_pallib.o
	@${MAKE} -${MAKEFLAGS} MODULE_eb164_pallib
MODULE_eb164_pallib:
	${RM} eb164_pallib.mod
	${LD} -dc -r -o eb164_pallib.mod eb164_pallib.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb164_pallib.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eb164_pallib.mod ; fi

ebv10_mult.mod: Makefile ebv10_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv10_mult
MODULE_ebv10_mult:
	${RM} ebv10_mult.mod
	${LD} -dc -r -o ebv10_mult.mod ebv10_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv10_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv10_mult.mod ; fi

ebv10.mod: Makefile ebv10.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv10
MODULE_ebv10:
	${RM} ebv10.mod
	${LD} -dc -r -o ebv10.mod ebv10.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv10.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv10.mod ; fi

ebv10_common.mod: Makefile ebv10_pallib.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv10_common
MODULE_ebv10_common:
	${RM} ebv10_common.mod
	${LD} -dc -r -o ebv10_common.mod ebv10_pallib.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv10_common.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv10_common.mod ; fi

ds1386clock_mult.mod: Makefile ds1386clock_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ds1386clock_mult
MODULE_ds1386clock_mult:
	${RM} ds1386clock_mult.mod
	${LD} -dc -r -o ds1386clock_mult.mod ds1386clock_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ds1386clock_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ds1386clock_mult.mod ; fi

ds1386.mod: Makefile ds1386clock.o
	@${MAKE} -${MAKEFLAGS} MODULE_ds1386
MODULE_ds1386:
	${RM} ds1386.mod
	${LD} -dc -r -o ds1386.mod ds1386clock.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ds1386.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ds1386.mod ; fi

ebv14_mult.mod: Makefile ebv14_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv14_mult
MODULE_ebv14_mult:
	${RM} ebv14_mult.mod
	${LD} -dc -r -o ebv14_mult.mod ebv14_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv14_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv14_mult.mod ; fi

ebv14.mod: Makefile ebv14.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv14
MODULE_ebv14:
	${RM} ebv14.mod
	${LD} -dc -r -o ebv14.mod ebv14.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv14.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv14.mod ; fi

ebv14_pallib.mod: Makefile ebv14_pallib.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv14_pallib
MODULE_ebv14_pallib:
	${RM} ebv14_pallib.mod
	${LD} -dc -r -o ebv14_pallib.mod ebv14_pallib.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv14_pallib.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv14_pallib.mod ; fi

ebv16_mult.mod: Makefile ebv16_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv16_mult
MODULE_ebv16_mult:
	${RM} ebv16_mult.mod
	${LD} -dc -r -o ebv16_mult.mod ebv16_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv16_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv16_mult.mod ; fi

ebv16.mod: Makefile ebv16.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv16
MODULE_ebv16:
	${RM} ebv16.mod
	${LD} -dc -r -o ebv16.mod ebv16.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv16.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv16.mod ; fi

ebv16_pallib.mod: Makefile ebv16_pallib.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebv16_pallib
MODULE_ebv16_pallib:
	${RM} ebv16_pallib.mod
	${LD} -dc -r -o ebv16_pallib.mod ebv16_pallib.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv16_pallib.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebv16_pallib.mod ; fi

ebm10_mult.mod: Makefile ebm10_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebm10_mult
MODULE_ebm10_mult:
	${RM} ebm10_mult.mod
	${LD} -dc -r -o ebm10_mult.mod ebm10_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm10_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm10_mult.mod ; fi

ebm10.mod: Makefile ebm10.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebm10
MODULE_ebm10:
	${RM} ebm10.mod
	${LD} -dc -r -o ebm10.mod ebm10.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm10.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm10.mod ; fi

ebm20_mult.mod: Makefile ebm20_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebm20_mult
MODULE_ebm20_mult:
	${RM} ebm20_mult.mod
	${LD} -dc -r -o ebm20_mult.mod ebm20_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm20_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm20_mult.mod ; fi

ebm20.mod: Makefile ebm20.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebm20
MODULE_ebm20:
	${RM} ebm20.mod
	${LD} -dc -r -o ebm20.mod ebm20.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm20.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm20.mod ; fi

ruby_common_mult.mod: Makefile ruby_common_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ruby_common_mult
MODULE_ruby_common_mult:
	${RM} ruby_common_mult.mod
	${LD} -dc -r -o ruby_common_mult.mod ruby_common_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ruby_common_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ruby_common_mult.mod ; fi

ruby_common.mod: Makefile ruby_common.o
	@${MAKE} -${MAKEFLAGS} MODULE_ruby_common
MODULE_ruby_common:
	${RM} ruby_common.mod
	${LD} -dc -r -o ruby_common.mod ruby_common.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ruby_common.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ruby_common.mod ; fi

kn300_mult.mod: Makefile kn300_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn300_mult
MODULE_kn300_mult:
	${RM} kn300_mult.mod
	${LD} -dc -r -o kn300_mult.mod kn300_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn300_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn300_mult.mod ; fi

kn300.mod: Makefile kn300.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn300
MODULE_kn300:
	${RM} kn300.mod
	${LD} -dc -r -o kn300.mod kn300.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn300.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn300.mod ; fi

kn600_mult.mod: Makefile kn600_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn600_mult
MODULE_kn600_mult:
	${RM} kn600_mult.mod
	${LD} -dc -r -o kn600_mult.mod kn600_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn600_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn600_mult.mod ; fi

kn600.mod: Makefile kn600.o
	@${MAKE} -${MAKEFLAGS} MODULE_kn600
MODULE_kn600:
	${RM} kn600.mod
	${LD} -dc -r -o kn600.mod kn600.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn600.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kn600.mod ; fi

ebm30_mult.mod: Makefile ebm30_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebm30_mult
MODULE_ebm30_mult:
	${RM} ebm30_mult.mod
	${LD} -dc -r -o ebm30_mult.mod ebm30_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm30_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm30_mult.mod ; fi

ebm30.mod: Makefile ebm30.o
	@${MAKE} -${MAKEFLAGS} MODULE_ebm30
MODULE_ebm30:
	${RM} ebm30.mod
	${LD} -dc -r -o ebm30.mod ebm30.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm30.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ebm30.mod ; fi

alphabook_mult.mod: Makefile alphabook_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_alphabook_mult
MODULE_alphabook_mult:
	${RM} alphabook_mult.mod
	${LD} -dc -r -o alphabook_mult.mod alphabook_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ alphabook_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ alphabook_mult.mod ; fi

alphabook.mod: Makefile alphabook.o
	@${MAKE} -${MAKEFLAGS} MODULE_alphabook
MODULE_alphabook:
	${RM} alphabook.mod
	${LD} -dc -r -o alphabook.mod alphabook.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ alphabook.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ alphabook.mod ; fi

mcbus.mod: Makefile mcbus.o
	@${MAKE} -${MAKEFLAGS} MODULE_mcbus
MODULE_mcbus:
	${RM} mcbus.mod
	${LD} -dc -r -o mcbus.mod mcbus.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcbus.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcbus.mod ; fi

mcpcia_mult.mod: Makefile mcpcia_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_mcpcia_mult
MODULE_mcpcia_mult:
	${RM} mcpcia_mult.mod
	${LD} -dc -r -o mcpcia_mult.mod mcpcia_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcpcia_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcpcia_mult.mod ; fi

mcpcia.mod: Makefile mcpcia.o
	@${MAKE} -${MAKEFLAGS} MODULE_mcpcia
MODULE_mcpcia:
	${RM} mcpcia.mod
	${LD} -dc -r -o mcpcia.mod mcpcia.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcpcia.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mcpcia.mod ; fi

dc104x.mod: Makefile dc104x.o
	@${MAKE} -${MAKEFLAGS} MODULE_dc104x
MODULE_dc104x:
	${RM} dc104x.mod
	${LD} -dc -r -o dc104x.mod dc104x.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc104x.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc104x.mod ; fi

dc104x_mult.mod: Makefile dc104x_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_dc104x_mult
MODULE_dc104x_mult:
	${RM} dc104x_mult.mod
	${LD} -dc -r -o dc104x_mult.mod dc104x_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc104x_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dc104x_mult.mod ; fi

linear_io_access.mod: Makefile linear_io_access.o
	@${MAKE} -${MAKEFLAGS} MODULE_linear_io_access
MODULE_linear_io_access:
	${RM} linear_io_access.mod
	${LD} -dc -r -o linear_io_access.mod linear_io_access.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ linear_io_access.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ linear_io_access.mod ; fi

linear_io_access_mult.mod: Makefile linear_io_access_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_linear_io_access_mult
MODULE_linear_io_access_mult:
	${RM} linear_io_access_mult.mod
	${LD} -dc -r -o linear_io_access_mult.mod linear_io_access_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ linear_io_access_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ linear_io_access_mult.mod ; fi

pc_bell_mult.mod: Makefile pc_bell_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_pc_bell_mult
MODULE_pc_bell_mult:
	${RM} pc_bell_mult.mod
	${LD} -dc -r -o pc_bell_mult.mod pc_bell_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pc_bell_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pc_bell_mult.mod ; fi

pc_bell.mod: Makefile pc_bell.o
	@${MAKE} -${MAKEFLAGS} MODULE_pc_bell
MODULE_pc_bell:
	${RM} pc_bell.mod
	${LD} -dc -r -o pc_bell.mod pc_bell.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pc_bell.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pc_bell.mod ; fi

sio.mod: Makefile sio.o
	@${MAKE} -${MAKEFLAGS} MODULE_sio
MODULE_sio:
	${RM} sio.mod
	${LD} -dc -r -o sio.mod sio.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sio.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sio.mod ; fi

pic.mod: Makefile 82357_pic.o
	@${MAKE} -${MAKEFLAGS} MODULE_pic
MODULE_pic:
	${RM} pic.mod
	${LD} -dc -r -o pic.mod 82357_pic.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pic.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pic.mod ; fi

mc146818_mult.mod: Makefile mc146818clock_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_mc146818_mult
MODULE_mc146818_mult:
	${RM} mc146818_mult.mod
	${LD} -dc -r -o mc146818_mult.mod mc146818clock_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mc146818_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mc146818_mult.mod ; fi

mc146818.mod: Makefile mc146818clock.o
	@${MAKE} -${MAKEFLAGS} MODULE_mc146818
MODULE_mc146818:
	${RM} mc146818.mod
	${LD} -dc -r -o mc146818.mod mc146818clock.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mc146818.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mc146818.mod ; fi

lca_mult.mod: Makefile lca_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_lca_mult
MODULE_lca_mult:
	${RM} lca_mult.mod
	${LD} -dc -r -o lca_mult.mod lca_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lca_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lca_mult.mod ; fi

lca.mod: Makefile lca.o
	@${MAKE} -${MAKEFLAGS} MODULE_lca
MODULE_lca:
	${RM} lca.mod
	${LD} -dc -r -o lca.mod lca.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lca.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lca.mod ; fi

apecs_mult.mod: Makefile apecs_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_apecs_mult
MODULE_apecs_mult:
	${RM} apecs_mult.mod
	${LD} -dc -r -o apecs_mult.mod apecs_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ apecs_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ apecs_mult.mod ; fi

apecs.mod: Makefile apecs.o
	@${MAKE} -${MAKEFLAGS} MODULE_apecs
MODULE_apecs:
	${RM} apecs.mod
	${LD} -dc -r -o apecs.mod apecs.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ apecs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ apecs.mod ; fi

vba_vipvic.mod: Makefile ebv10_vme.o
	@${MAKE} -${MAKEFLAGS} MODULE_vba_vipvic
MODULE_vba_vipvic:
	${RM} vba_vipvic.mod
	${LD} -dc -r -o vba_vipvic.mod ebv10_vme.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vba_vipvic.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vba_vipvic.mod ; fi

vba_univ.mod: Makefile univ_vme.o
	@${MAKE} -${MAKEFLAGS} MODULE_vba_univ
MODULE_vba_univ:
	${RM} vba_univ.mod
	${LD} -dc -r -o vba_univ.mod univ_vme.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vba_univ.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vba_univ.mod ; fi

lsbmem_mult.mod: Makefile lsbmem_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_lsbmem_mult
MODULE_lsbmem_mult:
	${RM} lsbmem_mult.mod
	${LD} -dc -r -o lsbmem_mult.mod lsbmem_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lsbmem_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lsbmem_mult.mod ; fi

lsbmem.mod: Makefile lsbmem.o
	@${MAKE} -${MAKEFLAGS} MODULE_lsbmem
MODULE_lsbmem:
	${RM} lsbmem.mod
	${LD} -dc -r -o lsbmem.mod lsbmem.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lsbmem.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lsbmem.mod ; fi

cma_dd.mod: Makefile cma_dd.o
	@${MAKE} -${MAKEFLAGS} MODULE_cma_dd
MODULE_cma_dd:
	${RM} cma_dd.mod
	${LD} -dc -r -o cma_dd.mod cma_dd.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cma_dd.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cma_dd.mod ; fi

cam_disk.mod: Makefile cam_disk.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_disk
MODULE_cam_disk:
	${RM} cam_disk.mod
	${LD} -dc -r -o cam_disk.mod cam_disk.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_disk.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_disk.mod ; fi

cam_tape.mod: Makefile cam_tape.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_tape
MODULE_cam_tape:
	${RM} cam_tape.mod
	${LD} -dc -r -o cam_tape.mod cam_tape.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_tape.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_tape.mod ; fi

cam.mod: Makefile cam_logger.o cam_special.o ccfg.o camdb.o \
	 pdrv_common.o special_audio.o special_direct.o \
	 special_generic.o special_sequential.o uagt.o xpt.o dme_null.o \
	 sim_common.o cam_eei.o cam_rci.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam
MODULE_cam:
	${RM} cam.mod
	${LD} -dc -r -o cam.mod cam_logger.o cam_special.o ccfg.o camdb.o \
	 pdrv_common.o special_audio.o special_direct.o \
	 special_generic.o special_sequential.o uagt.o xpt.o dme_null.o \
	 sim_common.o cam_eei.o cam_rci.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam.mod ; fi

cam_sim.mod: Makefile sim_xpt.o sim_htm.o sim_as.o sim_error.o \
	 sim_sched.o sim_sm.o sim_target.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_sim
MODULE_cam_sim:
	${RM} cam_sim.mod
	${LD} -dc -r -o cam_sim.mod sim_xpt.o sim_htm.o sim_as.o sim_error.o \
	 sim_sched.o sim_sm.o sim_target.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_sim.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_sim.mod ; fi

cam_tcds.mod: Makefile dme_tcds_94_dma.o tcds_adapt.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_tcds
MODULE_cam_tcds:
	${RM} cam_tcds.mod
	${LD} -dc -r -o cam_tcds.mod dme_tcds_94_dma.o tcds_adapt.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_tcds.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_tcds.mod ; fi

cam_94.mod: Makefile dme_turbo_94_ram.o dme_common.o sim_94_fast.o \
	 sim_94.o sim_kn02.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_94
MODULE_cam_94:
	${RM} cam_94.mod
	${LD} -dc -r -o cam_94.mod dme_turbo_94_ram.o dme_common.o \
	 sim_94_fast.o sim_94.o sim_kn02.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_94.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_94.mod ; fi

cam_aha1740.mod: Makefile aha1740.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_aha1740
MODULE_cam_aha1740:
	${RM} cam_aha1740.mod
	${LD} -dc -r -o cam_aha1740.mod aha1740.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_aha1740.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_aha1740.mod ; fi

cam_ata.mod: Makefile sim_ata.o sim_ata_acer.o sim_ata_cmd.o \
	 sim_ata_cypress.o sim_ata_datatech.o sim_ata_dma.o \
	 sim_ata_symphony.o sim_ata_unknown.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_ata
MODULE_cam_ata:
	${RM} cam_ata.mod
	${LD} -dc -r -o cam_ata.mod sim_ata.o sim_ata_acer.o sim_ata_cmd.o \
	 sim_ata_cypress.o sim_ata_datatech.o sim_ata_dma.o \
	 sim_ata_symphony.o sim_ata_unknown.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_ata.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_ata.mod ; fi

isp.mod: Makefile isp1020.o
	@${MAKE} -${MAKEFLAGS} MODULE_isp
MODULE_isp:
	${RM} isp.mod
	${LD} -dc -r -o isp.mod isp1020.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ isp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ isp.mod ; fi

itpsa.mod: Makefile itpsa.o itpsacfg.o itpsahtm.o
	@${MAKE} -${MAKEFLAGS} MODULE_itpsa
MODULE_itpsa:
	${RM} itpsa.mod
	${LD} -dc -r -o itpsa.mod itpsa.o itpsacfg.o itpsahtm.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ itpsa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ itpsa.mod ; fi

cam_pza.mod: Makefile sim_pza.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_pza
MODULE_cam_pza:
	${RM} cam_pza.mod
	${LD} -dc -r -o cam_pza.mod sim_pza.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_pza.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_pza.mod ; fi

cam_tza.mod: Makefile sim_kztsa.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_tza
MODULE_cam_tza:
	${RM} cam_tza.mod
	${LD} -dc -r -o cam_tza.mod sim_kztsa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_tza.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_tza.mod ; fi

cam_simport.mod: Makefile simport.o simport_htm.o simport_dme.o \
	 simport_subr.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_simport
MODULE_cam_simport:
	${RM} cam_simport.mod
	${LD} -dc -r -o cam_simport.mod simport.o simport_htm.o \
	 simport_dme.o simport_subr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_simport.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_simport.mod ; fi

cam_psiop.mod: Makefile psiop.o psiop_pci.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_psiop
MODULE_cam_psiop:
	${RM} cam_psiop.mod
	${LD} -dc -r -o cam_psiop.mod psiop.o psiop_pci.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_psiop.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_psiop.mod ; fi

cam_siop.mod: Makefile siop.o siop_kn430.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_siop
MODULE_cam_siop:
	${RM} cam_siop.mod
	${LD} -dc -r -o cam_siop.mod siop.o siop_kn430.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_siop.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_siop.mod ; fi

cam_xza.mod: Makefile skz_config.o skz_main.o skz_dme.o skz_error.o \
	 skz_sched.o skz_debug.o skz_nport.o skz_diag.o skz_target.o
	@${MAKE} -${MAKEFLAGS} MODULE_cam_xza
MODULE_cam_xza:
	${RM} cam_xza.mod
	${LD} -dc -r -o cam_xza.mod skz_config.o skz_main.o skz_dme.o \
	 skz_error.o skz_sched.o skz_debug.o skz_nport.o skz_diag.o \
	 skz_target.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_xza.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cam_xza.mod ; fi

fbus.mod: Makefile fbus.o fbus_loadable.o flag.o
	@${MAKE} -${MAKEFLAGS} MODULE_fbus
MODULE_fbus:
	${RM} fbus.mod
	${LD} -dc -r -o fbus.mod fbus.o fbus_loadable.o flag.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fbus.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fbus.mod ; fi

mbox.mod: Makefile mbox.o
	@${MAKE} -${MAKEFLAGS} MODULE_mbox
MODULE_mbox:
	${RM} mbox.mod
	${LD} -dc -r -o mbox.mod mbox.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mbox.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mbox.mod ; fi

ibus.mod: Makefile ibus.o
	@${MAKE} -${MAKEFLAGS} MODULE_ibus
MODULE_ibus:
	${RM} ibus.mod
	${LD} -dc -r -o ibus.mod ibus.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ibus.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ibus.mod ; fi

xmi.mod: Makefile xmiinit.o xlamb.o
	@${MAKE} -${MAKEFLAGS} MODULE_xmi
MODULE_xmi:
	${RM} xmi.mod
	${LD} -dc -r -o xmi.mod xmiinit.o xlamb.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xmi.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xmi.mod ; fi

xna.mod: Makefile if_xna.o
	@${MAKE} -${MAKEFLAGS} MODULE_xna
MODULE_xna:
	${RM} xna.mod
	${LD} -dc -r -o xna.mod if_xna.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xna.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ xna.mod ; fi

mfa.mod: Makefile if_mfa.o
	@${MAKE} -${MAKEFLAGS} MODULE_mfa
MODULE_mfa:
	${RM} mfa.mod
	${LD} -dc -r -o mfa.mod if_mfa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mfa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mfa.mod ; fi

tc.mod: Makefile tc.o tc_loadable.o
	@${MAKE} -${MAKEFLAGS} MODULE_tc
MODULE_tc:
	${RM} tc.mod
	${LD} -dc -r -o tc.mod tc.o tc_loadable.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tc.mod ; fi

scc.mod: Makefile scc.o
	@${MAKE} -${MAKEFLAGS} MODULE_scc
MODULE_scc:
	${RM} scc.mod
	${LD} -dc -r -o scc.mod scc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ scc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ scc.mod ; fi

nvtc.mod: Makefile nvtc.o
	@${MAKE} -${MAKEFLAGS} MODULE_nvtc
MODULE_nvtc:
	${RM} nvtc.mod
	${LD} -dc -r -o nvtc.mod nvtc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ nvtc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ nvtc.mod ; fi

bba.mod: Makefile amd79c30.o amd79c30_dummy.o amd79c30_hdlc.o
	@${MAKE} -${MAKEFLAGS} MODULE_bba
MODULE_bba:
	${RM} bba.mod
	${LD} -dc -r -o bba.mod amd79c30.o amd79c30_dummy.o amd79c30_hdlc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bba.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bba.mod ; fi

eisa.mod: Makefile eisa.o eisa_cnfg.o isp.o
	@${MAKE} -${MAKEFLAGS} MODULE_eisa
MODULE_eisa:
	${RM} eisa.mod
	${LD} -dc -r -o eisa.mod eisa.o eisa_cnfg.o isp.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eisa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ eisa.mod ; fi

i2c.mod: Makefile i2c.o
	@${MAKE} -${MAKEFLAGS} MODULE_i2c
MODULE_i2c:
	${RM} i2c.mod
	${LD} -dc -r -o i2c.mod i2c.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ i2c.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ i2c.mod ; fi

iscc.mod: Makefile iscc.o
	@${MAKE} -${MAKEFLAGS} MODULE_iscc
MODULE_iscc:
	${RM} iscc.mod
	${LD} -dc -r -o iscc.mod iscc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ iscc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ iscc.mod ; fi

isa.mod: Makefile isa.o
	@${MAKE} -${MAKEFLAGS} MODULE_isa
MODULE_isa:
	${RM} isa.mod
	${LD} -dc -r -o isa.mod isa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ isa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ isa.mod ; fi

gpc.mod: Makefile gpc.o
	@${MAKE} -${MAKEFLAGS} MODULE_gpc
MODULE_gpc:
	${RM} gpc.mod
	${LD} -dc -r -o gpc.mod gpc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ gpc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ gpc.mod ; fi

ace.mod: Makefile ace.o
	@${MAKE} -${MAKEFLAGS} MODULE_ace
MODULE_ace:
	${RM} ace.mod
	${LD} -dc -r -o ace.mod ace.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ace.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ace.mod ; fi

lp.mod: Makefile lp.o
	@${MAKE} -${MAKEFLAGS} MODULE_lp
MODULE_lp:
	${RM} lp.mod
	${LD} -dc -r -o lp.mod lp.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lp.mod ; fi

envram.mod: Makefile envram.o
	@${MAKE} -${MAKEFLAGS} MODULE_envram
MODULE_envram:
	${RM} envram.mod
	${LD} -dc -r -o envram.mod envram.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ envram.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ envram.mod ; fi

re_xcr.mod: Makefile re_driver.o xcr_logger.o xcr_port.o
	@${MAKE} -${MAKEFLAGS} MODULE_re_xcr
MODULE_re_xcr:
	${RM} re_xcr.mod
	${LD} -dc -r -o re_xcr.mod re_driver.o xcr_logger.o xcr_port.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ re_xcr.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ re_xcr.mod ; fi

pci.mod: Makefile pci.o dma_sg_map.o shared_intr.o \
	 pci_common_intr_handler.o
	@${MAKE} -${MAKEFLAGS} MODULE_pci
MODULE_pci:
	${RM} pci.mod
	${LD} -dc -r -o pci.mod pci.o dma_sg_map.o shared_intr.o \
	 pci_common_intr_handler.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pci.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pci.mod ; fi

pnvram.mod: Makefile pnvram.o
	@${MAKE} -${MAKEFLAGS} MODULE_pnvram
MODULE_pnvram:
	${RM} pnvram.mod
	${LD} -dc -r -o pnvram.mod pnvram.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pnvram.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pnvram.mod ; fi

mchan.mod: Makefile mchan.o
	@${MAKE} -${MAKEFLAGS} MODULE_mchan
MODULE_mchan:
	${RM} mchan.mod
	${LD} -dc -r -o mchan.mod mchan.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mchan.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ mchan.mod ; fi

pcia_mult.mod: Makefile pcia_mult.o
	@${MAKE} -${MAKEFLAGS} MODULE_pcia_mult
MODULE_pcia_mult:
	${RM} pcia_mult.mod
	${LD} -dc -r -o pcia_mult.mod pcia_mult.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcia_mult.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcia_mult.mod ; fi

pcia.mod: Makefile pcia.o
	@${MAKE} -${MAKEFLAGS} MODULE_pcia
MODULE_pcia:
	${RM} pcia.mod
	${LD} -dc -r -o pcia.mod pcia.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcia.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcia.mod ; fi

pd6729.mod: Makefile pd6729.o
	@${MAKE} -${MAKEFLAGS} MODULE_pd6729
MODULE_pd6729:
	${RM} pd6729.mod
	${LD} -dc -r -o pd6729.mod pd6729.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pd6729.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pd6729.mod ; fi

pcic.mod: Makefile pcic.o
	@${MAKE} -${MAKEFLAGS} MODULE_pcic
MODULE_pcic:
	${RM} pcic.mod
	${LD} -dc -r -o pcic.mod pcic.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcic.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcic.mod ; fi

pcmcia.mod: Makefile pcmcia.o card_services.o card_config.o \
	 pcmcia_event.o
	@${MAKE} -${MAKEFLAGS} MODULE_pcmcia
MODULE_pcmcia:
	${RM} pcmcia.mod
	${LD} -dc -r -o pcmcia.mod pcmcia.o card_services.o card_config.o \
	 pcmcia_event.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcmcia.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pcmcia.mod ; fi

i2o.mod: Makefile i2oexec.o i2omsg.o i2opcixport.o i2o.o
	@${MAKE} -${MAKEFLAGS} MODULE_i2o
MODULE_i2o:
	${RM} i2o.mod
	${LD} -dc -r -o i2o.mod i2oexec.o i2omsg.o i2opcixport.o i2o.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ i2o.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ i2o.mod ; fi

i2o_bs.mod: Makefile i2o_bs.o i2o_logger.o
	@${MAKE} -${MAKEFLAGS} MODULE_i2o_bs
MODULE_i2o_bs:
	${RM} i2o_bs.mod
	${LD} -dc -r -o i2o_bs.mod i2o_bs.o i2o_logger.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ i2o_bs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ i2o_bs.mod ; fi

ln.mod: Makefile if_ln.o
	@${MAKE} -${MAKEFLAGS} MODULE_ln
MODULE_ln:
	${RM} ln.mod
	${LD} -dc -r -o ln.mod if_ln.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ln.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ln.mod ; fi

le.mod: Makefile if_le.o
	@${MAKE} -${MAKEFLAGS} MODULE_le
MODULE_le:
	${RM} le.mod
	${LD} -dc -r -o le.mod if_le.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ le.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ le.mod ; fi

te.mod: Makefile if_te.o
	@${MAKE} -${MAKEFLAGS} MODULE_te
MODULE_te:
	${RM} te.mod
	${LD} -dc -r -o te.mod if_te.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ te.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ te.mod ; fi

tu.mod: Makefile if_tu.o
	@${MAKE} -${MAKEFLAGS} MODULE_tu
MODULE_tu:
	${RM} tu.mod
	${LD} -dc -r -o tu.mod if_tu.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tu.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tu.mod ; fi

fza.mod: Makefile if_fza.o
	@${MAKE} -${MAKEFLAGS} MODULE_fza
MODULE_fza:
	${RM} fza.mod
	${LD} -dc -r -o fza.mod if_fza.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fza.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fza.mod ; fi

fta.mod: Makefile if_fta.o
	@${MAKE} -${MAKEFLAGS} MODULE_fta
MODULE_fta:
	${RM} fta.mod
	${LD} -dc -r -o fta.mod if_fta.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fta.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fta.mod ; fi

tra.mod: Makefile if_tra.o
	@${MAKE} -${MAKEFLAGS} MODULE_tra
MODULE_tra:
	${RM} tra.mod
	${LD} -dc -r -o tra.mod if_tra.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tra.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tra.mod ; fi

faa.mod: Makefile if_faa.o
	@${MAKE} -${MAKEFLAGS} MODULE_faa
MODULE_faa:
	${RM} faa.mod
	${LD} -dc -r -o faa.mod if_faa.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ faa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ faa.mod ; fi

vb.mod: Makefile if_vb.o
	@${MAKE} -${MAKEFLAGS} MODULE_vb
MODULE_vb:
	${RM} vb.mod
	${LD} -dc -r -o vb.mod if_vb.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vb.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vb.mod ; fi

lta.mod: Makefile if_otto.o if_otto_xilinx.o if_ottodefs.o \
	 otto_platform.o otto_flow.o otto_fakesnmp.o aal5crc.o
	@${MAKE} -${MAKEFLAGS} MODULE_lta
MODULE_lta:
	${RM} lta.mod
	${LD} -dc -r -o lta.mod if_otto.o if_otto_xilinx.o if_ottodefs.o \
	 otto_platform.o otto_flow.o otto_fakesnmp.o aal5crc.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lta.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lta.mod ; fi

lpa.mod: Makefile acr_tbl.o adap_sw.o fm.o if_lpa.o if_lpa_defs.o \
	 if_lpa_platform.o met_sw.o
	@${MAKE} -${MAKEFLAGS} MODULE_lpa
MODULE_lpa:
	${RM} lpa.mod
	${LD} -dc -r -o lpa.mod acr_tbl.o adap_sw.o fm.o if_lpa.o \
	 if_lpa_defs.o if_lpa_platform.o met_sw.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lpa.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lpa.mod ; fi

dsa_cippd.mod: Makefile ciconfig.o cippd_error.o cippd_event.o \
	 cippd_pmaint.o cippd_protocol.o cippdvar.o gvp_block.o gvp_dg.o \
	 gvp_msg.o gvp_subr.o gvpvar.o
	@${MAKE} -${MAKEFLAGS} MODULE_dsa_cippd
MODULE_dsa_cippd:
	${RM} dsa_cippd.mod
	${LD} -dc -r -o dsa_cippd.mod ciconfig.o cippd_error.o cippd_event.o \
	 cippd_pmaint.o cippd_protocol.o cippdvar.o gvp_block.o gvp_dg.o \
	 gvp_msg.o gvp_subr.o gvpvar.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_cippd.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_cippd.mod ; fi

dsa_np.mod: Makefile np_block.o np_dg.o np_error.o np_init.o np_isr.o \
	 np_lpmaint.o np_msg.o np_subr.o npvar.o xminp.o
	@${MAKE} -${MAKEFLAGS} MODULE_dsa_np
MODULE_dsa_np:
	${RM} dsa_np.mod
	${LD} -dc -r -o dsa_np.mod np_block.o np_dg.o np_error.o np_init.o \
	 np_isr.o np_lpmaint.o np_msg.o np_subr.o npvar.o xminp.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_np.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_np.mod ; fi

dsa_scs.mod: Makefile scs_block.o scs_configdb.o scs_conn.o scs_dg.o \
	 scs_error.o scs_event.o scs_info.o scs_maint.o scs_msg.o \
	 scs_protocol.o scs_subr.o scsvar.o
	@${MAKE} -${MAKEFLAGS} MODULE_dsa_scs
MODULE_dsa_scs:
	${RM} dsa_scs.mod
	${LD} -dc -r -o dsa_scs.mod scs_block.o scs_configdb.o scs_conn.o \
	 scs_dg.o scs_error.o scs_event.o scs_info.o scs_maint.o \
	 scs_msg.o scs_protocol.o scs_subr.o scsvar.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_scs.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_scs.mod ; fi

dsa_sysap.mod: Makefile scs_directory.o mscp_tape.o mscp_disk.o \
	 mscp_bbr.o mscp_bbrstates.o mscp_config.o mscp_conpol.o \
	 mscp_diskvar.o mscp_subr.o mscp_var.o sysap_start.o
	@${MAKE} -${MAKEFLAGS} MODULE_dsa_sysap
MODULE_dsa_sysap:
	${RM} dsa_sysap.mod
	${LD} -dc -r -o dsa_sysap.mod scs_directory.o mscp_tape.o \
	 mscp_disk.o mscp_bbr.o mscp_bbrstates.o mscp_config.o \
	 mscp_conpol.o mscp_diskvar.o mscp_subr.o mscp_var.o \
	 sysap_start.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_sysap.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_sysap.mod ; fi

dsa_uba.mod: Makefile uba.o
	@${MAKE} -${MAKEFLAGS} MODULE_dsa_uba
MODULE_dsa_uba:
	${RM} dsa_uba.mod
	${LD} -dc -r -o dsa_uba.mod uba.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_uba.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_uba.mod ; fi

dsa_uqserv.mod: Makefile uqserv.o
	@${MAKE} -${MAKEFLAGS} MODULE_dsa_uqserv
MODULE_dsa_uqserv:
	${RM} dsa_uqserv.mod
	${LD} -dc -r -o dsa_uqserv.mod uqserv.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_uqserv.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_uqserv.mod ; fi

dsa_kdm.mod: Makefile kdm.o
	@${MAKE} -${MAKEFLAGS} MODULE_dsa_kdm
MODULE_dsa_kdm:
	${RM} dsa_kdm.mod
	${LD} -dc -r -o dsa_kdm.mod kdm.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_kdm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ dsa_kdm.mod ; fi

fdi.mod: Makefile fd.o fdcam.o
	@${MAKE} -${MAKEFLAGS} MODULE_fdi
MODULE_fdi:
	${RM} fdi.mod
	${LD} -dc -r -o fdi.mod fd.o fdcam.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fdi.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fdi.mod ; fi

ws.mod: Makefile ws_driver.o vga_support.o
	@${MAKE} -${MAKEFLAGS} MODULE_ws
MODULE_ws:
	${RM} ws.mod
	${LD} -dc -r -o ws.mod ws_driver.o vga_support.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ws.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ws.mod ; fi

scc_input.mod: Makefile lk201.o vsxxx.o
	@${MAKE} -${MAKEFLAGS} MODULE_scc_input
MODULE_scc_input:
	${RM} scc_input.mod
	${LD} -dc -r -o scc_input.mod lk201.o vsxxx.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ scc_input.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ scc_input.mod ; fi

gpc_input.mod: Makefile pcxal.o pcxas.o
	@${MAKE} -${MAKEFLAGS} MODULE_gpc_input
MODULE_gpc_input:
	${RM} gpc_input.mod
	${LD} -dc -r -o gpc_input.mod pcxal.o pcxas.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ gpc_input.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ gpc_input.mod ; fi

qfont.mod: Makefile qfont.o
	@${MAKE} -${MAKEFLAGS} MODULE_qfont
MODULE_qfont:
	${RM} qfont.mod
	${LD} -dc -r -o qfont.mod qfont.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ qfont.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ qfont.mod ; fi

bt431.mod: Makefile bt431.o
	@${MAKE} -${MAKEFLAGS} MODULE_bt431
MODULE_bt431:
	${RM} bt431.mod
	${LD} -dc -r -o bt431.mod bt431.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bt431.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bt431.mod ; fi

bt459.mod: Makefile bt459.o
	@${MAKE} -${MAKEFLAGS} MODULE_bt459
MODULE_bt459:
	${RM} bt459.mod
	${LD} -dc -r -o bt459.mod bt459.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bt459.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bt459.mod ; fi

bt463.mod: Makefile bt463.o
	@${MAKE} -${MAKEFLAGS} MODULE_bt463
MODULE_bt463:
	${RM} bt463.mod
	${LD} -dc -r -o bt463.mod bt463.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bt463.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ bt463.mod ; fi

fb.mod: Makefile fb.o
	@${MAKE} -${MAKEFLAGS} MODULE_fb
MODULE_fb:
	${RM} fb.mod
	${LD} -dc -r -o fb.mod fb.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fb.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ fb.mod ; fi

vga.mod: Makefile vga.o
	@${MAKE} -${MAKEFLAGS} MODULE_vga
MODULE_vga:
	${RM} vga.mod
	${LD} -dc -r -o vga.mod vga.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vga.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vga.mod ; fi

ati32.mod: Makefile ati.o
	@${MAKE} -${MAKEFLAGS} MODULE_ati32
MODULE_ati32:
	${RM} ati32.mod
	${LD} -dc -r -o ati32.mod ati.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ati32.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ati32.mod ; fi

ati64.mod: Makefile ati64.o
	@${MAKE} -${MAKEFLAGS} MODULE_ati64
MODULE_ati64:
	${RM} ati64.mod
	${LD} -dc -r -o ati64.mod ati64.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ati64.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ati64.mod ; fi

cirrus.mod: Makefile cirrus.o
	@${MAKE} -${MAKEFLAGS} MODULE_cirrus
MODULE_cirrus:
	${RM} cirrus.mod
	${LD} -dc -r -o cirrus.mod cirrus.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cirrus.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ cirrus.mod ; fi

qvision.mod: Makefile qvision.o
	@${MAKE} -${MAKEFLAGS} MODULE_qvision
MODULE_qvision:
	${RM} qvision.mod
	${LD} -dc -r -o qvision.mod qvision.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ qvision.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ qvision.mod ; fi

s3v864.mod: Makefile s3v864.o
	@${MAKE} -${MAKEFLAGS} MODULE_s3v864
MODULE_s3v864:
	${RM} s3v864.mod
	${LD} -dc -r -o s3v864.mod s3v864.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ s3v864.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ s3v864.mod ; fi

s3trio.mod: Makefile s3trio.o
	@${MAKE} -${MAKEFLAGS} MODULE_s3trio
MODULE_s3trio:
	${RM} s3trio.mod
	${LD} -dc -r -o s3trio.mod s3trio.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ s3trio.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ s3trio.mod ; fi

wd.mod: Makefile wd.o
	@${MAKE} -${MAKEFLAGS} MODULE_wd
MODULE_wd:
	${RM} wd.mod
	${LD} -dc -r -o wd.mod wd.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ wd.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ wd.mod ; fi

comet.mod: Makefile comet.o
	@${MAKE} -${MAKEFLAGS} MODULE_comet
MODULE_comet:
	${RM} comet.mod
	${LD} -dc -r -o comet.mod comet.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ comet.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ comet.mod ; fi

tga.mod: Makefile tga.o
	@${MAKE} -${MAKEFLAGS} MODULE_tga
MODULE_tga:
	${RM} tga.mod
	${LD} -dc -r -o tga.mod tga.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tga.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ tga.mod ; fi

sfbp.mod: Makefile pmagro.o sfb.o
	@${MAKE} -${MAKEFLAGS} MODULE_sfbp
MODULE_sfbp:
	${RM} sfbp.mod
	${LD} -dc -r -o sfbp.mod pmagro.o sfb.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sfbp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ sfbp.mod ; fi

pv.mod: Makefile pv.o
	@${MAKE} -${MAKEFLAGS} MODULE_pv
MODULE_pv:
	${RM} pv.mod
	${LD} -dc -r -o pv.mod pv.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pv.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pv.mod ; fi

pvl.mod: Makefile pvl.o
	@${MAKE} -${MAKEFLAGS} MODULE_pvl
MODULE_pvl:
	${RM} pvl.mod
	${LD} -dc -r -o pvl.mod pvl.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pvl.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pvl.mod ; fi

pvp.mod: Makefile pvp.o
	@${MAKE} -${MAKEFLAGS} MODULE_pvp
MODULE_pvp:
	${RM} pvp.mod
	${LD} -dc -r -o pvp.mod pvp.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pvp.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pvp.mod ; fi

presto.mod: Makefile pr.o presto_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_presto
MODULE_presto:
	${RM} presto.mod
	${LD} -dc -r -o presto.mod pr.o presto_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ presto.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ presto.mod ; fi

lsm.mod: Makefile dki_osf.o plex.o volspec.o vol.o volblog.o volioctl.o \
	 volklog.o volted.o volSpace.o volroot.o vol_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_lsm
MODULE_lsm:
	${RM} lsm.mod
	${LD} -dc -r -o lsm.mod dki_osf.o plex.o volspec.o vol.o volblog.o \
	 volioctl.o volklog.o volted.o volSpace.o volroot.o vol_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lsm.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lsm.mod ; fi

vme_vba.mod: Makefile vba_generic.o vba_tc.o vba_pci.o vba_dispatch.o
	@${MAKE} -${MAKEFLAGS} MODULE_vme_vba
MODULE_vme_vba:
	${RM} vme_vba.mod
	${LD} -dc -r -o vme_vba.mod vba_generic.o vba_tc.o vba_pci.o \
	 vba_dispatch.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vme_vba.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ vme_vba.mod ; fi

ddr.mod: Makefile ddr.o
	@${MAKE} -${MAKEFLAGS} MODULE_ddr
MODULE_ddr:
	${RM} ddr.mod
	${LD} -dc -r -o ddr.mod ddr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ddr.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ddr.mod ; fi

kio.mod: Makefile kio.o
	@${MAKE} -${MAKEFLAGS} MODULE_kio
MODULE_kio:
	${RM} kio.mod
	${LD} -dc -r -o kio.mod kio.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kio.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kio.mod ; fi

kds.mod: Makefile kds.o
	@${MAKE} -${MAKEFLAGS} MODULE_kds
MODULE_kds:
	${RM} kds.mod
	${LD} -dc -r -o kds.mod kds.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kds.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ kds.mod ; fi

envmon.mod: Makefile envmon.o
	@${MAKE} -${MAKEFLAGS} MODULE_envmon
MODULE_envmon:
	${RM} envmon.mod
	${LD} -dc -r -o envmon.mod envmon.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ envmon.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ envmon.mod ; fi

distint.mod: Makefile distint_cfg.o
	@${MAKE} -${MAKEFLAGS} MODULE_distint
MODULE_distint:
	${RM} distint.mod
	${LD} -dc -r -o distint.mod distint_cfg.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ distint.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ distint.mod ; fi

el.mod: Makefile if_el.o
	@${MAKE} -${MAKEFLAGS} MODULE_el
MODULE_el:
	${RM} el.mod
	${LD} -dc -r -o el.mod if_el.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ el.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ el.mod ; fi

lan_common.mod: Makefile lan_common.o
	@${MAKE} -${MAKEFLAGS} MODULE_lan_common
MODULE_lan_common:
	${RM} lan_common.mod
	${LD} -dc -r -o lan_common.mod lan_common.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lan_common.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ lan_common.mod ; fi

hmc.mod: Makefile hmc.o hmc_support.o
	@${MAKE} -${MAKEFLAGS} MODULE_hmc
MODULE_hmc:
	${RM} hmc.mod
	${LD} -dc -r -o hmc.mod hmc.o hmc_support.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ hmc.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ hmc.mod ; fi

pci_isa_intr.mod: Makefile pci_isa_intr.o
	@${MAKE} -${MAKEFLAGS} MODULE_pci_isa_intr
MODULE_pci_isa_intr:
	${RM} pci_isa_intr.mod
	${LD} -dc -r -o pci_isa_intr.mod pci_isa_intr.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pci_isa_intr.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ pci_isa_intr.mod ; fi

ev6_common.mod: Makefile ev6_common.o
	@${MAKE} -${MAKEFLAGS} MODULE_ev6_common
MODULE_ev6_common:
	${RM} ev6_common.mod
	${LD} -dc -r -o ev6_common.mod ev6_common.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ev6_common.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ev6_common.mod ; fi

usb.mod: Makefile usbd.o
	@${MAKE} -${MAKEFLAGS} MODULE_usb
MODULE_usb:
	${RM} usb.mod
	${LD} -dc -r -o usb.mod usbd.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb.mod ; fi

usb_ohci.mod: Makefile usb_ohci.o
	@${MAKE} -${MAKEFLAGS} MODULE_usb_ohci
MODULE_usb_ohci:
	${RM} usb_ohci.mod
	${LD} -dc -r -o usb_ohci.mod usb_ohci.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_ohci.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_ohci.mod ; fi

usb_hub.mod: Makefile usb_hub.o
	@${MAKE} -${MAKEFLAGS} MODULE_usb_hub
MODULE_usb_hub:
	${RM} usb_hub.mod
	${LD} -dc -r -o usb_hub.mod usb_hub.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_hub.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_hub.mod ; fi

usb_hid.mod: Makefile usb_hid.o
	@${MAKE} -${MAKEFLAGS} MODULE_usb_hid
MODULE_usb_hid:
	${RM} usb_hid.mod
	${LD} -dc -r -o usb_hid.mod usb_hid.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_hid.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_hid.mod ; fi

usb_keyboard.mod: Makefile usb_keyboard.o
	@${MAKE} -${MAKEFLAGS} MODULE_usb_keyboard
MODULE_usb_keyboard:
	${RM} usb_keyboard.mod
	${LD} -dc -r -o usb_keyboard.mod usb_keyboard.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_keyboard.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_keyboard.mod ; fi

usb_mouse.mod: Makefile usb_mouse.o
	@${MAKE} -${MAKEFLAGS} MODULE_usb_mouse
MODULE_usb_mouse:
	${RM} usb_mouse.mod
	${LD} -dc -r -o usb_mouse.mod usb_mouse.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_mouse.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_mouse.mod ; fi

usb_printer.mod: Makefile usb_printer.o
	@${MAKE} -${MAKEFLAGS} MODULE_usb_printer
MODULE_usb_printer:
	${RM} usb_printer.mod
	${LD} -dc -r -o usb_printer.mod usb_printer.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_printer.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ usb_printer.mod ; fi

MODULES: MODULE_cm MODULE_generic MODULE_io \
	 MODULE_ipc MODULE_proc MODULE_sec \
	 MODULE_socket MODULE_sec_min MODULE_rt \
	 MODULE_std_kern MODULE_bsd_tty MODULE_xpr \
	 MODULE_mach_xp MODULE_cdfs MODULE_dvdfs \
	 MODULE_ess MODULE_ess_stub MODULE_kdebug \
	 MODULE_dli MODULE_ffm_fs MODULE_atm \
	 MODULE_atmip MODULE_lane MODULE_atmifmp \
	 MODULE_atmtm MODULE_atmuni MODULE_atmilmi3x \
	 MODULE_uni3x MODULE_bparm MODULE_lat \
	 MODULE_lv MODULE_advfs MODULE_packetfilter \
	 MODULE_net MODULE_netrain MODULE_ether \
	 MODULE_loop MODULE_sl MODULE_ppp \
	 MODULE_inet MODULE_nfs MODULE_nfs_server \
	 MODULE_procfs MODULE_notprocfs MODULE_snmpinfo \
	 MODULE_bufcall MODULE_streams \
	 MODULE_streams_debug MODULE_dlb MODULE_dlpi \
	 MODULE_ifnet MODULE_kinfo MODULE_strstd \
	 MODULE_svvs MODULE_timod MODULE_tirdwr \
	 MODULE_ldtty MODULE_xtiso MODULE_pts \
	 MODULE_ufs MODULE_uipc MODULE_vfs MODULE_vm \
	 MODULE__lmf_ MODULE_pckt MODULE_ntp_time \
	 MODULE_mlog MODULE_profiling MODULE_pty \
	 MODULE_prf MODULE_mach_co_stats \
	 MODULE_mach_ipc_stats MODULE_gwscreen \
	 MODULE_pwrmgr MODULE_dec_audit MODULE_sec_base \
	 MODULE_sec_driver MODULE_sec_mld MODULE_dec_acl \
	 MODULE_dce_acl_stubs MODULE_spd_cache \
	 MODULE_acl_stubs MODULE_spd_mac MODULE_spd_misc \
	 MODULE_arch_alpha MODULE_in_cksum MODULE_pfm \
	 MODULE_arch_alphapmap MODULE_fp MODULE_mcount \
	 MODULE_kn15aa_mult MODULE_kn15aa \
	 MODULE_kn16aa_mult MODULE_kn16aa \
	 MODULE_kn430_mult MODULE_kn430 \
	 MODULE_kn430_common MODULE_kn7aa_mult \
	 MODULE_kn7aa MODULE_kn7aa_common \
	 MODULE_kn8ae_mult MODULE_kn8ae \
	 MODULE_kn8ae_common MODULE_dc21171_mult \
	 MODULE_dc21171 MODULE_kn121_mult MODULE_kn121 \
	 MODULE_kn25_mult MODULE_kn25 MODULE_kn450_mult \
	 MODULE_kn450 MODULE_cbus2_pci_mult \
	 MODULE_cbus2_pci MODULE_kn470_mult MODULE_kn470 \
	 MODULE_kn20aa_mult MODULE_kn20aa \
	 MODULE_kn22a_mult MODULE_kn22a MODULE_ebp10_mult \
	 MODULE_ebp10 MODULE_eb64p_mult MODULE_eb64p \
	 MODULE_eb64p_pallib MODULE_eb66_mult MODULE_eb66 \
	 MODULE_eb66_pallib MODULE_eb164_mult \
	 MODULE_eb164 MODULE_eb164_pallib \
	 MODULE_ebv10_mult MODULE_ebv10 \
	 MODULE_ebv10_common MODULE_ds1386clock_mult \
	 MODULE_ds1386 MODULE_ebv14_mult MODULE_ebv14 \
	 MODULE_ebv14_pallib MODULE_ebv16_mult \
	 MODULE_ebv16 MODULE_ebv16_pallib \
	 MODULE_ebm10_mult MODULE_ebm10 MODULE_ebm20_mult \
	 MODULE_ebm20 MODULE_ruby_common_mult \
	 MODULE_ruby_common MODULE_kn300_mult \
	 MODULE_kn300 MODULE_kn600_mult MODULE_kn600 \
	 MODULE_ebm30_mult MODULE_ebm30 \
	 MODULE_alphabook_mult MODULE_alphabook \
	 MODULE_mcbus MODULE_mcpcia_mult MODULE_mcpcia \
	 MODULE_dc104x MODULE_dc104x_mult \
	 MODULE_linear_io_access MODULE_linear_io_access_mult \
	 MODULE_pc_bell_mult MODULE_pc_bell MODULE_sio \
	 MODULE_pic MODULE_mc146818_mult MODULE_mc146818 \
	 MODULE_lca_mult MODULE_lca MODULE_apecs_mult \
	 MODULE_apecs MODULE_vba_vipvic MODULE_vba_univ \
	 MODULE_lsbmem_mult MODULE_lsbmem MODULE_cma_dd \
	 MODULE_cam_disk MODULE_cam_tape MODULE_cam \
	 MODULE_cam_sim MODULE_cam_tcds MODULE_cam_94 \
	 MODULE_cam_aha1740 MODULE_cam_ata MODULE_isp \
	 MODULE_itpsa MODULE_cam_pza MODULE_cam_tza \
	 MODULE_cam_simport MODULE_cam_psiop \
	 MODULE_cam_siop MODULE_cam_xza MODULE_fbus \
	 MODULE_mbox MODULE_ibus MODULE_xmi \
	 MODULE_xna MODULE_mfa MODULE_tc MODULE_scc \
	 MODULE_nvtc MODULE_bba MODULE_eisa \
	 MODULE_i2c MODULE_iscc MODULE_isa \
	 MODULE_gpc MODULE_ace MODULE_lp \
	 MODULE_envram MODULE_re_xcr MODULE_pci \
	 MODULE_pnvram MODULE_mchan MODULE_pcia_mult \
	 MODULE_pcia MODULE_pd6729 MODULE_pcic \
	 MODULE_pcmcia MODULE_i2o MODULE_i2o_bs \
	 MODULE_ln MODULE_le MODULE_te MODULE_tu \
	 MODULE_fza MODULE_fta MODULE_tra MODULE_faa \
	 MODULE_vb MODULE_lta MODULE_lpa \
	 MODULE_dsa_cippd MODULE_dsa_np MODULE_dsa_scs \
	 MODULE_dsa_sysap MODULE_dsa_uba \
	 MODULE_dsa_uqserv MODULE_dsa_kdm MODULE_fdi \
	 MODULE_ws MODULE_scc_input MODULE_gpc_input \
	 MODULE_qfont MODULE_bt431 MODULE_bt459 \
	 MODULE_bt463 MODULE_fb MODULE_vga \
	 MODULE_ati32 MODULE_ati64 MODULE_cirrus \
	 MODULE_qvision MODULE_s3v864 MODULE_s3trio \
	 MODULE_wd MODULE_comet MODULE_tga \
	 MODULE_sfbp MODULE_pv MODULE_pvl MODULE_pvp \
	 MODULE_presto MODULE_lsm MODULE_vme_vba \
	 MODULE_ddr MODULE_kio MODULE_kds \
	 MODULE_envmon MODULE_distint MODULE_el \
	 MODULE_lan_common MODULE_hmc MODULE_pci_isa_intr \
	 MODULE_ev6_common MODULE_usb MODULE_usb_ohci \
	 MODULE_usb_hub MODULE_usb_hid \
	 MODULE_usb_keyboard MODULE_usb_mouse \
	 MODULE_usb_printer


include makelint
include makedep

