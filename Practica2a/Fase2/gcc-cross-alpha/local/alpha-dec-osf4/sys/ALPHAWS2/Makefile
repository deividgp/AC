IDENT=-DIDENT=ALPHAWS2 -DDEC6600 -DSWAPTYPE=1 -DUERF -DOSF -DCOMPAT_43 -DMACH -DUFS -DFFM_FS -DATM -DATM -DATM -DATM -DATM -DRT_SEM
BINDIR=../BINARY
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
#	@(#)$RCSfile: template.std.mk,v $ $Revision: 4.6.74.3 $ (DEC) $Date: 1999/03/01 18:42:49 $
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

alpha_CC_SUITE  = ACC
alpha_cc_suite  = acc
mips_CC_SUITE   = MCC
mips_cc_suite   = mcc
alpha_TARGET_MACHINE    = ALPHA
mips_TARGET_MACHINE     = MIPS
alpha_CURRENT_MACHINE   = ALPHA
mips_CURRENT_MACHINE    = MIPS

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

#  Lots of tools and files needed by config and the Makefile (that builds
#  a system are located in the directory where config lives.  That directory
#  is:
CONFIG_DIR=	conf

#
#  Tools needed
#
AWK=		awk
BASENAME=	basename
CAT=		cat
CHMOD=		chmod
CP=		cp
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

OBJECT_FORMAT = ${OBJECT_FORMAT?${OBJECT_FORMAT}:COFF}
_CC_EXEC_PREFIX = ${${OBJECT_FORMAT}_${CC_SUITE}_EXEC_PREFIX}

CC	= ${_CC_EXEC_PREFIX}cc
CPP	= ${CC} -ES
LD	= ${_CC_EXEC_PREFIX}ld
NM	= ${_CC_EXEC_PREFIX}nm

ENCODE=	uuencode
DECODE=	uudecode

GCC_VOLATILE =
MCC_VOLATILE = "-Dvolatile= "
ACC_VOLATILE =
VOLATILE=${${CC_SUITE}_VOLATILE}
FORCE_VOLATILE=

KCPP	= ${KCC} -E

DLD=		${LD}
DLD_FLAGS=	-r -d
VMUNIX_LIB=

NM=		${KERNEL_SH?${COFF_GCC_EXEC_PREFIX}nm:nm}

#
#  This changed in the 4.3 CPP from .n to .d
#
MD_SUFFIX=d

#
#  Pre-processor environment
#
DEPENDS=
INCLUDES= -I -I. -I.. -I../include
ALLDEFINES= -DKERNEL -D_KERNEL -D_BSD
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
MCC_CFLAGS =
GCC_CFLASG =
ACC_DCFLAGS = -no_excpt -Wco,-nofloat -Olimit 3000
ACC_DCFOPTS = -no_excpt -Olimit 3000

CFLAGS	= ${COPTS_P} ${${CC_SUITE}_CFLAGS}
COPTS	= ${COPTS_P} ${${CC_SUITE}_CFLAGS}
CFOPTS	= ${COPTS_P} ${${CC_SUITE}_CFOPTS}
DCFLAGS = ${COPTS_P} ${${CC_SUITE}_DCFLAGS}
DCOPTS  = ${COPTS_P} ${${CC_SUITE}_DCFLAGS}
DCFOPTS = ${COPTS_P} ${${CC_SUITE}_DCFOPTS}

#
#  Common assembly flags
#
SFLAGS=	${DEPENDS} ${ALLOPTS} ${${CC_SUITE}_OPTS} -DASSEMBLER

#
#  Path name of the version identification file.
#
FEATURES=FEATURES.h
VERSION_FILES= \
	${CONFIG_DIR}/version.type \
	${CONFIG_DIR}/version.major \
	${CONFIG_DIR}/version.minor \
	${CONFIG_DIR}/version.variant \
	${CONFIG_DIR}/version.build \
	${CONFIG_DIR}/version.patch

#  LOBJS is a list of files that are unique to builds from BINARY systems.
#  That is, systems which do not have access to source code.  These files
#  are the files which will be compiled on each system because they tend
#  to be "tuned" to the specific system.

ALPHA_LOBJS=	param.o ioconf.o conf.o
MIPS_LOBJS= ioconf.o scb_vec.o param.o conf.o
LOBJS=${${_T_M_}_LOBJS}

MIPS_LCFILES= conf.c ioconf.c param.c scb_vec.c
ALPHA_LCFILES= conf.c ioconf.c param.c

LCFILES=${${_T_M_}_LCFILES}

#
#  LDOBJS is the set of object files which comprise the kernel.
#  It is used both in the dependency list for each *vmunix.swap
#  rule emitted by config and also in the .sys.swap rule
#  below which links the kernel from these objects.
#  
#  LDOBJS_PREFIX and LDOBJS_SUFFIX are defined in the machine
#  dependent Makefile (if necessary).
#
LDOBJS=${LDOBJS_PREFIX} ${OBJS} ${LDOBJS_SUFFIX}
#
# LDOBJS2 is the set of objects we will actually link with.
# EXTRAS.mod replaces all non-MODULE files in ${OBJS},
# and is built automatically at kernel link time.
# The modules (in MOBJS) are pointed to by LDOBJS_SUFFIX.
#
LDOBJS2=${LDOBJS_PREFIX} EXTRAS.mod ${LDOBJS_SUFFIX}

#
#  LDDEPS is the set of extra dependencies associated with each
#  *vmunix.swap rule (in addition to $LDOBJS and the swap*.o file).
#
#  LDDEPS_PREFIX is defined in the machine dependent Makefile
#  (if necessary).
#
LDDEPS=${LDDEPS_PREFIX} ${VERSION_FILES} \
	${CONFIG_DIR}/version.banner ${CONFIG_DIR}/newvers.sh ${CONFIG_DIR}/copyright

#
#  PRELDDEPS is another set of extra dependencies associated with each
#  *vmunix.swap rule (in addition to $LDOBJS and the swap*.o file).
#  It is defined in the machine dependent Makefile (if necessary).
#
#  The generated rule looks like
#	vmunix.sys: ${PRELDDEPS} ${LDOBJS} ${LDDEPS}
#

#
#  SWAPDEPS is the set of extra dependencies associated with each
#  swap*.o rule emitted by config (in addition to the
#  ../swap*.c file).
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
ALPHA_TEXTBASE=${LOADADDR?${LOADADDR}:fffffc0000230000}
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
	svr_four_cfg.o sysv_hab_cfg.o vfs_svid2calls.o dma_direct_map.o \
	devz.o 

MOBJS = cm.mod generic.mod io.mod ipc.mod proc.mod sec.mod socket.mod \
	sec_min.mod rt.mod std_kern.mod bsd_tty.mod xpr.mod cdfs.mod \
	dvdfs.mod kdebug.mod dli.mod ffm_fs.mod atm.mod atmip.mod \
	lane.mod atmifmp.mod atmuni.mod atmilmi3x.mod uni3x.mod \
	bparm.mod lv.mod advfs.mod packetfilter.mod net.mod netrain.mod \
	ether.mod loop.mod sl.mod ppp.mod inet.mod nfs.mod \
	nfs_server.mod procfs.mod snmpinfo.mod bufcall.mod streams.mod \
	dlb.mod kinfo.mod strstd.mod timod.mod tirdwr.mod ldtty.mod \
	xtiso.mod pts.mod ufs.mod uipc.mod vfs.mod vm.mod _lmf_.mod \
	pckt.mod ntp_time.mod prf.mod pwrmgr.mod dec_audit.mod \
	dec_acl.mod dce_acl_stubs.mod spd_cache.mod arch_alpha.mod \
	in_cksum.mod arch_alphapmap.mod fp.mod kn600.mod dc104x.mod \
	linear_io_access.mod pc_bell.mod sio.mod pic.mod mc146818.mod \
	cma_dd.mod cam_disk.mod cam_tape.mod cam.mod cam_sim.mod \
	cam_ata.mod isp.mod itpsa.mod i2c.mod isa.mod gpc.mod ace.mod \
	lp.mod pci.mod tu.mod fdi.mod ws.mod gpc_input.mod qfont.mod \
	vga.mod lsm.mod ddr.mod kio.mod kds.mod lan_common.mod \
	ev6_common.mod per.mod 

DMOBJS = envmon.mod 

CFILES1=\
	ufs/ufs_quota_stubs.c \
	data/audit_data.c \
	data/cm_data.c \
	data/dcedfs_data.c \
	data/gw_screen_data.c \
	data/sec_data.c \
	data/time_data.c \
	kern/lockinfo.c 

CFILES2=\
	net/netaf_config.c \
	streams/str_config.c \
	vfs/vfs_conf.c \
	bsd/tty_conf.c \
	data/steal_mem.c \
	arch/alpha/hal/cpuconf.c \
	io/cam/cam_config.c \
	io/cam/cam_debug.c 

CFILES3=\
	io/cam/sim_config.c \
	data/cam_data.c \
	data/cam_special_data.c \
	data/if_tu_data.c \
	data/pcxal_data.c \
	data/pcxas_data.c \
	data/ws_data.c \
	data/autoconf_data.c 

CFILES4=\
	data/cons_sw_data.c \
	./pci_option_data.c \
	./isa_option_data.c \
	data/binlog_data.c \
	data/pmap_data.c \
	data/presto_data.c \
	data/ace_data.c \
	data/trn_sr_data.c 

COBJS=ufs_quota.o kern_memcntl.o kern_swapctl.o rt_init_sysent.o \
	rt_syscalls.o soe_two_init_sysent.o soe_two_syscalls.o \
	svid_three_init_sysent.o svid_three_syscalls.o \
	svr_four_init_sysent.o svr_four_syscalls.o sysv_init_sysent.o \
	sysv_syscalls.o rt_hab_cfg.o soe_two_cfg.o svid_three_cfg.o \
	svr_four_cfg.o sysv_hab_cfg.o vfs_svid2calls.o init_main.o \
	ipc_globals.o vm_init.o alpha_init.o pmap_init.o startup.o \
	bootio_subrs.o bootio_net.o io.o sys.o sys_advfs.o sys_cdfs.o \
	dma_direct_map.o devz.o 

SFILES=
SOBJS=scb.o 

ORDERED=init_main.o ipc_globals.o vm_init.o lockinfo.o alpha_init.o \
	pmap_init.o startup.o steal_mem.o scb.o bootio_subrs.o \
	bootio_net.o io.o sys.o sys_advfs.o sys_cdfs.o 
LDOBJS_PREFIX=ALPHAWS2.mod
LDOBJS_SUFFIX=${MOBJS}

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
CDEBUGOPTS=-g3
CCOMPRESS=-compress
PROFOPTS=-DPROFILING -DPROFTYPE=4
CDEBUGOPTS=-g3
CCOMPRESS=-compress
PROFOPTS=-DPROFILING -DPROFTYPE=4

CFILES=${CFILES1} ${CFILES2} ${CFILES3} ${CFILES4}

##
# echo the list of CFILES, OBJECTS, or MODULES used to build the system
##
cfiles:
	@${ECHO} ${CFILES}
objfiles:
	@${ECHO} ${LDOBJS}
modlist:
	@${ECHO} ${LDOBJS2}

#
# Rules to install MODULES in a known place, and to update a sysconfigtab
#
DEFMODINSTALL_DIR=/sys/BINARY
MODINSTALL_DIR=${MODINSTALL_DIR?${MODINSTALL_DIR}:${DEFMODINSTALL_DIR}}
DEFSCTAB_NAME=sysconfigtab
SCTAB_NAME=${SCTAB_NAME?${SCTAB_NAME}:${DEFSCTAB_NAME}}
modinstall:
	${CP} ${LDOBJS2} ${MODINSTALL_DIR}
sctab:
	@${ECHO} Building ${SCTAB_NAME}
	@${RM} ${SCTAB_NAME}
	@${ECHO} "vmunix:" >> ${SCTAB_NAME}
	@${ECHO} "	Module_List = ${LDOBJS2}" >> ${SCTAB_NAME}
	@-if [ -n "${DMOBJS}" ]; then \
		${ECHO} "	Dynamic_Module_List = ${DMOBJS}" >> ${SCTAB_NAME}; \
	fi
	@-${LN} -f ${SCTAB_NAME} ${SCTAB_NAME}`${CAT} vers.suffix`
	@-if [ -n "${RPB_VALUE}" ]; then \
		${LN} -f ${SCTAB_NAME} ${SCTAB_NAME}.${RPB_VALUE}; \
	fi

#
#  Default rule used to build a *vmunix.sys configuration from the
#  object list and a particular *vmunix.swap module.  The *vmunix.swap
#  module is a normal object file compiled from the appropriate swap*.c
#  file and then copied to the *vmunix.swap name to trigger the full
#  kernel link using this default rule.
#
# alpha jestabro - 17-oct-91
#  Added fsmrg and pmerge steps here
#	on Alpha/Ultrix this went into config...
#	but on OSF the link rules are here in template.std.mk!!!!
#

ALPHA_LDCMD 	= 
MIPS_LDCMD 	= ${LIB_SEARCH} ${LIBS}
LDCMD		= ${${_T_M_}_LDCMD}
.swap.sys: 
	${SHELL} ${CONFIG_DIR}/newvers.sh \
			 ${CONFIG_DIR}/copyright \
			`${CAT} ${VERSION_FILES}` \
			"`${CAT} ${CONFIG_DIR}/version.banner`"
	@${RM} vers.o vers.o.d
	${KCC} ${CCNFLAGS} -c vers.c
	${RM} $* $*.sys
	@${ECHO} loading $*.sys
	@${LD} -r -o EXTRAS.mod ${OBJS} vers.o
	@if [ "${CCOMPRESS}" = "-compress" ]; then ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ EXTRAS.mod; fi
	@-${LD} ${LDFLAGS} ${LDOBJS2} ${LDCMD} ; \
	case "$$?" in \
	    0) \
		true \
		;; \
	    17) \
		echo Relinking ${CONFIG} with trampoline code ; \
		${LD} ${LDFLAGS} -trampoline_braddr ${LDOBJS2} ${LDCMD} ; \
		case "$$?" in \
		    0) \
			true \
			;; \
		    *) \
			${RM} a.out ; \
			false \
			;; \
		esac \
		;; \
	    *) \
		${RM} a.out ; \
		false \
		;; \
	esac
	${CHMOD} 755 a.out
	-${SWAPSYS}
	-${MV} a.out $*.sys

loadvmunix: relink

relink: vmunix.relink 

vmunix.relink: ${LDDEPS}
	${SHELL} ${CONFIG_DIR}/newvers.sh \
			 ${CONFIG_DIR}/copyright \
			`${CAT} ${VERSION_FILES}` \
			"`${CAT} ${CONFIG_DIR}/version.banner`"
	@${RM} vers.o vers.o.d
	${KCC} ${CCNFLAGS} -c vers.c
	${RM} vmunix vmunix.sys
	@${ECHO} loading vmunix.sys
	@${LD} -r -o EXTRAS.mod ${OBJS} vers.o
	@if [ "${CCOMPRESS}" = "-compress" ]; then ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ EXTRAS.mod; fi
	@-${LD} ${LDFLAGS} ${LDOBJS2} ${LDCMD} ; \
	case "$$?" in \
	    0) \
		true \
		;; \
	    17) \
		echo Relinking ${CONFIG} with trampoline code ; \
		${LD} ${LDFLAGS} -trampoline_braddr ${LDOBJS2} ${LDCMD} ; \
		case "$$?" in \
		    0) \
			true \
			;; \
		    *) \
			${RM} a.out ; \
			false \
			;; \
		esac \
		;; \
	    *) \
		${RM} a.out ; \
		false \
		;; \
	esac
	${CHMOD} 755 a.out
	-${SWAPSYS}
	-${MV} a.out vmunix.sys

	@eval `${AWK} 'NR==1{S=$$1;next;};\
	 END {\
	   C = "ln vmunix.sys vmunix";\
	   if (S != "") {\
	     C = C "; ln vmunix vmunix" S; \
	     printf "rm -f vmunix%s; ", S; \
	   }\
	   printf "echo \"%s\"; %s\n", C, C; \
	 }' vers.suffix`

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

vmunix .ORDER: vmunix.sys ${SYSDEPS}
	${SYS_RULE_1}
	${SYS_RULE_2}
	${SYS_RULE_3}
	${SYS_RULE_4}

vmunix.sys: ${PRELDDEPS} ${LDOBJS} ${LDDEPS}

vmunix.swap: swapgeneric.o
	@cp swapgeneric.o $@
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

swapgeneric.o: arch/alpha/swapgeneric.c ${SWAPDEPS}
	@${RM} swapgeneric.o swapgeneric.o.d
	${KCC} ${CCSFLAGS} arch/alpha/swapgeneric.c

LOAD= vmunix


SYSENT=rt_init_sysent.c soe_two_init_sysent.c \
	svid_three_init_sysent.c sysv_init_sysent.c init_sysent.c \
	svr_four_init_sysent.c 

all: ${LOAD}


#
#  Rules for components which are not part of the kernel proper or that
#  need to be built in a special manner.
#

ioconf.o: ioconf.c
	@${RM} ioconf.o ioconf.o.d
	${KCC} ${CCNFLAGS} ioconf.c

param.c: ${CONFIG_DIR}/param.c
	@${RM} param.c
	${CP} ${CONFIG_DIR}/param.c .

param.o: param.c 
	@${RM} param.o param.o.d
	${KCC} ${CCNFLAGS} ${PARAM} param.c

conf.o: conf.c 
	@${RM} conf.o conf.o.d
	${KCC} ${CCNFLAGS} conf.c

scb_vec.o: scb_vec.c
	@${RM} scb_vec.o scb_vec.o.d
	${KCC} ${CCNFLAGS} scb_vec.c

HOST_CC	= env - COMP_HOST_ROOT=/ COMP_TARGET_ROOT=/ /bin/cc

ACC_GENASSYM_CFLAGS = -no_excpt
MCC_GENASSYM_CFLAGS =

GENASSYM_CFLAGS = -std0 -EL ${ALLOPTS} ${VOLATILE} ${${CC_SUITE}_GENASSYM_CFLAGS} -MD

genassym.o: ${cpu}/genassym.c
	${CC} ${GENASSYM_CFLAGS} -c ${cpu}/genassym.c


CROSS_genassym.o: ${cpu}/genassym.c
	@${RM} genassym.o genassym.o.d
	${CC} ${GENASSYM_CFLAGS} -c ${cpu}/genassym.c

NATIVE_genassym.o: ${cpu}/genassym.c
	@${RM} genassym.o genassym.o.d
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

PMAX_CC_PREFIX=
MMAX_CC_PREFIX=LPATH=/usr/lib:/lib; export LPATH; 
I386_CC_PREFIX=LPATH=/usr/lib:/lib; export LPATH; 
CC_PREFIX=${${TARGET_MACHINE}_CC_PREFIX}


LINTFILES=
LINTFLAGS= -n -whpCDPR -XE -Nn6000 -Nd8000 ${LINTOPTS}
LINTFILTER= ${GREP} -v 'struct/union .* never defined' | \
	    ${GREP} -v 'possible pointer alignment problem'


DEPFILES= ${cpu}/swapgeneric.c \
		${LCFILES} ${CFILES} ${SFILES} 

depend: makedep

makedep: makedepfiles
	${CAT} /dev/null >makedeptmp
	-for i in `${CAT} makedepfiles` ; do \
		${CAT} $$i >> makedeptmp ; \
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
	${ECHO} genassym.o.d > makedepfiles
	${ECHO} arch/alpha/Locore.c Locore > makelinttmp
	-for i in ${DEPFILES} ; do \
		${ECHO} `${BASENAME} "$$i" .c`.o.d >> makedepfiles; \
		${ECHO} "$$i `${BASENAME} $$i .c`" >> makelinttmp; \
	done
	-${SED} -e 's+^.*/src/kernel/++' \
		-e 's+\.\./++' makelinttmp | ${SORT} +1 -u > makelintfiles
	${CAT} /dev/null > makelint
	@${AWK} '{ print $$2 }' makelintfiles > makelinttmp
	@${CAT} /dev/null > makelinttmp1
	@for i in ${COBJS} ; do \
		${ECHO} "`${BASENAME} $$i .o`" >> makelinttmp1; \
	done
	@${SORT} makelinttmp makelinttmp makelinttmp1 | ${UNIQ} -u > makelintobjs
	@${RM} makelinttmp*
	${AWK} 'BEGIN { printf("\nLINTOBJS=") } \
		{ printf(" \\\n\t%s.ln", $$2) } \
		END { printf("\n\n") }' makelintfiles >> makelint
	${AWK} 'BEGIN { printf("LINTOBJS1=") } \
		{ printf(" \\\n\t%s.ln", $$1) } \
		END { printf("\n\n") }' makelintobjs >> makelint
	${AWK} 'BEGIN { DOL=36; \
		printf("lint:\t%c{LINTOBJS} %c{LINTOBJS1}\n", DOL, DOL); \
		printf("\t@%c{ECHO} \"%c{LINT} %c{LINTFLAGS} *.ln > linterrs 2>&1\"\n", DOL, DOL, DOL); \
		printf("\t@%c{LINT} %c{LINTFLAGS} %c{LINTOBJS} %c{LINTOBJS1} > linterrs 2>&1\n", DOL, DOL, DOL, DOL); \
		printf("\t%c{TOUCH} lint\n\n", DOL) }' /dev/null >> makelint
	${AWK} 'BEGIN { DOL=36; \
		printf("flint:\t%c{LINTFILES}\n", DOL); \
		printf("\t@%c{ECHO} \"%c{LINT} %c{LINTFLAGS} *.ln > linterrs 2>&1\"\n", DOL, DOL, DOL); \
		printf("\t@%c{LINT} %c{LINTFLAGS} %c{LINTOBJS} %c{LINTOBJS1} > linterrs 2>&1\n", DOL, DOL, DOL, DOL); \
		printf("\n") }' /dev/null >> makelint
	${AWK} '{ DOL=36; \
		printf("%s.ln: %s\n", $$2, $$1); \
		printf("\t-%c{LINT} -c %c{LINTFLAGS} %s | \\\n", DOL, DOL, $$1); \
		printf("\t\t(%c{LINTFILTER} ; exit 0) > %s.lint 2>&1\n\n", DOL, $$2) }' \
		makelintfiles >> makelint
	${AWK} '{ DOL=36; \
		printf("%s.ln:\n", $$1); \
		printf("\t@%c{RM} %s.ln\n", DOL, $$1); \
		printf("\t@%c{LN} -s %s/%s.ln %s.ln\n\n", DOL, BINDIR, $$1, $$1) }' \
		"BINDIR=${BINDIR}" \
		makelintobjs >> makelint
	${RM} makelintobjs makelintfiles

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
		errs linterrs makelinks *.log *LOG* ${CLEAN_EXTRA}
	${RM} makedep makedepfiles *.o.d
	${RM} makelint makelintfiles makelintobjs lint *.ln *.lint
	${RM} sysconfigtab*
	${CAT} /dev/null >makedep
	${CAT} /dev/null >makelint


#
#  This macro is replaced by the set of rules which build everything in
#  OBJS.
#

ufs_quota.o:
	@${RM} ufs_quota.o ufs_quota.o.d
	@${LN} -s ../BINARY/ufs_quota.o ufs_quota.o

ufs_quota_stubs.o: ufs/ufs_quota_stubs.c
	@${RM} ufs_quota_stubs.o ufs_quota_stubs.o.d
	${KCC} ${CCNFLAGS} -g3 ufs/ufs_quota_stubs.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

kern_memcntl.o:
	@${RM} kern_memcntl.o kern_memcntl.o.d
	@${LN} -s ../BINARY/kern_memcntl.o kern_memcntl.o

kern_swapctl.o:
	@${RM} kern_swapctl.o kern_swapctl.o.d
	@${LN} -s ../BINARY/kern_swapctl.o kern_swapctl.o

rt_init_sysent.o:
	@${RM} rt_init_sysent.o rt_init_sysent.o.d
	@${LN} -s ../BINARY/rt_init_sysent.o rt_init_sysent.o

rt_syscalls.o:
	@${RM} rt_syscalls.o rt_syscalls.o.d
	@${LN} -s ../BINARY/rt_syscalls.o rt_syscalls.o

soe_two_init_sysent.o:
	@${RM} soe_two_init_sysent.o soe_two_init_sysent.o.d
	@${LN} -s ../BINARY/soe_two_init_sysent.o soe_two_init_sysent.o

soe_two_syscalls.o:
	@${RM} soe_two_syscalls.o soe_two_syscalls.o.d
	@${LN} -s ../BINARY/soe_two_syscalls.o soe_two_syscalls.o

svid_three_init_sysent.o:
	@${RM} svid_three_init_sysent.o svid_three_init_sysent.o.d
	@${LN} -s ../BINARY/svid_three_init_sysent.o svid_three_init_sysent.o

svid_three_syscalls.o:
	@${RM} svid_three_syscalls.o svid_three_syscalls.o.d
	@${LN} -s ../BINARY/svid_three_syscalls.o svid_three_syscalls.o

svr_four_init_sysent.o:
	@${RM} svr_four_init_sysent.o svr_four_init_sysent.o.d
	@${LN} -s ../BINARY/svr_four_init_sysent.o svr_four_init_sysent.o

svr_four_syscalls.o:
	@${RM} svr_four_syscalls.o svr_four_syscalls.o.d
	@${LN} -s ../BINARY/svr_four_syscalls.o svr_four_syscalls.o

sysv_init_sysent.o:
	@${RM} sysv_init_sysent.o sysv_init_sysent.o.d
	@${LN} -s ../BINARY/sysv_init_sysent.o sysv_init_sysent.o

sysv_syscalls.o:
	@${RM} sysv_syscalls.o sysv_syscalls.o.d
	@${LN} -s ../BINARY/sysv_syscalls.o sysv_syscalls.o

rt_hab_cfg.o:
	@${RM} rt_hab_cfg.o rt_hab_cfg.o.d
	@${LN} -s ../BINARY/rt_hab_cfg.o rt_hab_cfg.o

soe_two_cfg.o:
	@${RM} soe_two_cfg.o soe_two_cfg.o.d
	@${LN} -s ../BINARY/soe_two_cfg.o soe_two_cfg.o

svid_three_cfg.o:
	@${RM} svid_three_cfg.o svid_three_cfg.o.d
	@${LN} -s ../BINARY/svid_three_cfg.o svid_three_cfg.o

svr_four_cfg.o:
	@${RM} svr_four_cfg.o svr_four_cfg.o.d
	@${LN} -s ../BINARY/svr_four_cfg.o svr_four_cfg.o

sysv_hab_cfg.o:
	@${RM} sysv_hab_cfg.o sysv_hab_cfg.o.d
	@${LN} -s ../BINARY/sysv_hab_cfg.o sysv_hab_cfg.o

vfs_svid2calls.o:
	@${RM} vfs_svid2calls.o vfs_svid2calls.o.d
	@${LN} -s ../BINARY/vfs_svid2calls.o vfs_svid2calls.o

init_main.o:
	@${RM} init_main.o init_main.o.d
	@${LN} -s ../BINARY/init_main.o init_main.o

ipc_globals.o:
	@${RM} ipc_globals.o ipc_globals.o.d
	@${LN} -s ../BINARY/ipc_globals.o ipc_globals.o

vm_init.o:
	@${RM} vm_init.o vm_init.o.d
	@${LN} -s ../BINARY/vm_init.o vm_init.o

audit_data.o: data/audit_data.c
	@${RM} audit_data.o audit_data.o.d
	${KCC} ${CCNFLAGS}  data/audit_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

cm_data.o: data/cm_data.c
	@${RM} cm_data.o cm_data.o.d
	${KCC} ${CCNFLAGS}  data/cm_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

dcedfs_data.o: data/dcedfs_data.c
	@${RM} dcedfs_data.o dcedfs_data.o.d
	${KCC} ${CCNFLAGS}  data/dcedfs_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

gw_screen_data.o: data/gw_screen_data.c
	@${RM} gw_screen_data.o gw_screen_data.o.d
	${KCC} ${CCNFLAGS}  data/gw_screen_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

sec_data.o: data/sec_data.c
	@${RM} sec_data.o sec_data.o.d
	${KCC} ${CCNFLAGS}  data/sec_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

time_data.o: data/time_data.c
	@${RM} time_data.o time_data.o.d
	${KCC} ${CCNFLAGS}  data/time_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

lockinfo.o: kern/lockinfo.c
	@${RM} lockinfo.o lockinfo.o.d
	${KCC} ${CCNFLAGS}  kern/lockinfo.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

netaf_config.o: net/netaf_config.c
	@${RM} netaf_config.o netaf_config.o.d
	${KCC} ${CCNFLAGS}  net/netaf_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

str_config.o: streams/str_config.c
	@${RM} str_config.o str_config.o.d
	${KCC} ${CCNFLAGS}  streams/str_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

vfs_conf.o: vfs/vfs_conf.c
	@${RM} vfs_conf.o vfs_conf.o.d
	${KCC} ${CCNFLAGS}  vfs/vfs_conf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

tty_conf.o: bsd/tty_conf.c
	@${RM} tty_conf.o tty_conf.o.d
	${KCC} ${CCNFLAGS}  bsd/tty_conf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

alpha_init.o:
	@${RM} alpha_init.o alpha_init.o.d
	@${LN} -s ../BINARY/alpha_init.o alpha_init.o

pmap_init.o:
	@${RM} pmap_init.o pmap_init.o.d
	@${LN} -s ../BINARY/pmap_init.o pmap_init.o

startup.o:
	@${RM} startup.o startup.o.d
	@${LN} -s ../BINARY/startup.o startup.o

steal_mem.o: data/steal_mem.c
	@${RM} steal_mem.o steal_mem.o.d
	${KCC} ${CCNFLAGS}  data/steal_mem.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

scb.o:
	@${RM} scb.o scb.o.d
	@${LN} -s ../BINARY/scb.o scb.o

bootio_subrs.o:
	@${RM} bootio_subrs.o bootio_subrs.o.d
	@${LN} -s ../BINARY/bootio_subrs.o bootio_subrs.o

bootio_net.o:
	@${RM} bootio_net.o bootio_net.o.d
	@${LN} -s ../BINARY/bootio_net.o bootio_net.o

io.o:
	@${RM} io.o io.o.d
	@${LN} -s ../BINARY/io.o io.o

sys.o:
	@${RM} sys.o sys.o.d
	@${LN} -s ../BINARY/sys.o sys.o

sys_advfs.o:
	@${RM} sys_advfs.o sys_advfs.o.d
	@${LN} -s ../BINARY/sys_advfs.o sys_advfs.o

sys_cdfs.o:
	@${RM} sys_cdfs.o sys_cdfs.o.d
	@${LN} -s ../BINARY/sys_cdfs.o sys_cdfs.o

cpuconf.o: arch/alpha/hal/cpuconf.c
	@${RM} cpuconf.o cpuconf.o.d
	${KCC} ${CCNFLAGS}  arch/alpha/hal/cpuconf.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

dma_direct_map.o:
	@${RM} dma_direct_map.o dma_direct_map.o.d
	@${LN} -s ../BINARY/dma_direct_map.o dma_direct_map.o

devz.o:
	@${RM} devz.o devz.o.d
	@${LN} -s ../BINARY/devz.o devz.o

cam_config.o: io/cam/cam_config.c
	@${RM} cam_config.o cam_config.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/cam_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

cam_debug.o: io/cam/cam_debug.c
	@${RM} cam_debug.o cam_debug.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/cam_debug.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

sim_config.o: io/cam/sim_config.c
	@${RM} sim_config.o sim_config.o.d
	${KCC} ${CCDFLAGS} -O2 io/cam/sim_config.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

cam_data.o: data/cam_data.c
	@${RM} cam_data.o cam_data.o.d
	${KCC} ${CCNFLAGS}  data/cam_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

cam_special_data.o: data/cam_special_data.c
	@${RM} cam_special_data.o cam_special_data.o.d
	${KCC} ${CCNFLAGS}  data/cam_special_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

if_tu_data.o: data/if_tu_data.c
	@${RM} if_tu_data.o if_tu_data.o.d
	${KCC} ${CCNFLAGS}  data/if_tu_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

pcxal_data.o: data/pcxal_data.c
	@${RM} pcxal_data.o pcxal_data.o.d
	${KCC} ${CCNFLAGS}  data/pcxal_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

pcxas_data.o: data/pcxas_data.c
	@${RM} pcxas_data.o pcxas_data.o.d
	${KCC} ${CCNFLAGS}  data/pcxas_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

ws_data.o: data/ws_data.c
	@${RM} ws_data.o ws_data.o.d
	${KCC} ${CCNFLAGS}  data/ws_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

autoconf_data.o: data/autoconf_data.c
	@${RM} autoconf_data.o autoconf_data.o.d
	${KCC} ${CCNFLAGS}  data/autoconf_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

cons_sw_data.o: data/cons_sw_data.c
	@${RM} cons_sw_data.o cons_sw_data.o.d
	${KCC} ${CCNFLAGS}  data/cons_sw_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

pci_option_data.o: pci_option_data.c
	@${RM} pci_option_data.o pci_option_data.o.d
	${KCC} ${CCNFLAGS}  pci_option_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

isa_option_data.o: isa_option_data.c
	@${RM} isa_option_data.o isa_option_data.o.d
	${KCC} ${CCNFLAGS}  isa_option_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

binlog_data.o: data/binlog_data.c
	@${RM} binlog_data.o binlog_data.o.d
	${KCC} ${CCNFLAGS}  data/binlog_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

pmap_data.o: data/pmap_data.c
	@${RM} pmap_data.o pmap_data.o.d
	${KCC} ${CCNFLAGS}  data/pmap_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

presto_data.o: data/presto_data.c
	@${RM} presto_data.o presto_data.o.d
	${KCC} ${CCNFLAGS}  data/presto_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

ace_data.o: data/ace_data.c
	@${RM} ace_data.o ace_data.o.d
	${KCC} ${CCDFLAGS}  data/ace_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

trn_sr_data.o: data/trn_sr_data.c
	@${RM} trn_sr_data.o trn_sr_data.o.d
	${KCC} ${CCNFLAGS}  data/trn_sr_data.c
	@if [ "${DO_MODULES}" = "AUTO" ]; then ${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2 ; fi

ALPHAWS2.mod: Makefile ${ORDERED} ${LOBJS} vmunix.swap ufs_quota_stubs.o \
	 audit_data.o cm_data.o dcedfs_data.o gw_screen_data.o \
	 sec_data.o time_data.o netaf_config.o str_config.o vfs_conf.o \
	 tty_conf.o cpuconf.o cam_config.o cam_debug.o sim_config.o \
	 cam_data.o cam_special_data.o if_tu_data.o pcxal_data.o \
	 pcxas_data.o ws_data.o autoconf_data.o cons_sw_data.o \
	 pci_option_data.o isa_option_data.o binlog_data.o pmap_data.o \
	 presto_data.o ace_data.o trn_sr_data.o
	@${MAKE} -${MAKEFLAGS} MODULE_ALPHAWS2
MODULE_ALPHAWS2:
	${RM} ALPHAWS2.mod
	${LD} -dc -r -o ALPHAWS2.mod ${ORDERED} ${LOBJS} vmunix.swap \
	 ufs_quota_stubs.o audit_data.o cm_data.o dcedfs_data.o \
	 gw_screen_data.o sec_data.o time_data.o netaf_config.o \
	 str_config.o vfs_conf.o tty_conf.o cpuconf.o cam_config.o \
	 cam_debug.o sim_config.o cam_data.o cam_special_data.o \
	 if_tu_data.o pcxal_data.o pcxas_data.o ws_data.o \
	 autoconf_data.o cons_sw_data.o pci_option_data.o \
	 isa_option_data.o binlog_data.o pmap_data.o presto_data.o \
	 ace_data.o trn_sr_data.o
	@if [ "${CCOMPRESS}" = "-compress" ] ; then echo ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ALPHAWS2.mod && ${COMP_HOST_ROOT}/usr/lib/cmplrs/cc/objZ ALPHAWS2.mod ; fi

cm.mod:
	@${RM} cm.mod
	@${LN} -s ../BINARY/cm.mod cm.mod

generic.mod:
	@${RM} generic.mod
	@${LN} -s ../BINARY/generic.mod generic.mod

io.mod:
	@${RM} io.mod
	@${LN} -s ../BINARY/io.mod io.mod

ipc.mod:
	@${RM} ipc.mod
	@${LN} -s ../BINARY/ipc.mod ipc.mod

proc.mod:
	@${RM} proc.mod
	@${LN} -s ../BINARY/proc.mod proc.mod

sec.mod:
	@${RM} sec.mod
	@${LN} -s ../BINARY/sec.mod sec.mod

socket.mod:
	@${RM} socket.mod
	@${LN} -s ../BINARY/socket.mod socket.mod

sec_min.mod:
	@${RM} sec_min.mod
	@${LN} -s ../BINARY/sec_min.mod sec_min.mod

rt.mod:
	@${RM} rt.mod
	@${LN} -s ../BINARY/rt.mod rt.mod

std_kern.mod:
	@${RM} std_kern.mod
	@${LN} -s ../BINARY/std_kern.mod std_kern.mod

bsd_tty.mod:
	@${RM} bsd_tty.mod
	@${LN} -s ../BINARY/bsd_tty.mod bsd_tty.mod

xpr.mod:
	@${RM} xpr.mod
	@${LN} -s ../BINARY/xpr.mod xpr.mod

cdfs.mod:
	@${RM} cdfs.mod
	@${LN} -s ../BINARY/cdfs.mod cdfs.mod

dvdfs.mod:
	@${RM} dvdfs.mod
	@${LN} -s ../BINARY/dvdfs.mod dvdfs.mod

kdebug.mod:
	@${RM} kdebug.mod
	@${LN} -s ../BINARY/kdebug.mod kdebug.mod

dli.mod:
	@${RM} dli.mod
	@${LN} -s ../BINARY/dli.mod dli.mod

ffm_fs.mod:
	@${RM} ffm_fs.mod
	@${LN} -s ../BINARY/ffm_fs.mod ffm_fs.mod

atm.mod:
	@${RM} atm.mod
	@${LN} -s ../BINARY/atm.mod atm.mod

atmip.mod:
	@${RM} atmip.mod
	@${LN} -s ../BINARY/atmip.mod atmip.mod

lane.mod:
	@${RM} lane.mod
	@${LN} -s ../BINARY/lane.mod lane.mod

atmifmp.mod:
	@${RM} atmifmp.mod
	@${LN} -s ../BINARY/atmifmp.mod atmifmp.mod

atmuni.mod:
	@${RM} atmuni.mod
	@${LN} -s ../BINARY/atmuni.mod atmuni.mod

atmilmi3x.mod:
	@${RM} atmilmi3x.mod
	@${LN} -s ../BINARY/atmilmi3x.mod atmilmi3x.mod

uni3x.mod:
	@${RM} uni3x.mod
	@${LN} -s ../BINARY/uni3x.mod uni3x.mod

bparm.mod:
	@${RM} bparm.mod
	@${LN} -s ../BINARY/bparm.mod bparm.mod

lv.mod:
	@${RM} lv.mod
	@${LN} -s ../BINARY/lv.mod lv.mod

advfs.mod:
	@${RM} advfs.mod
	@${LN} -s ../BINARY/advfs.mod advfs.mod

packetfilter.mod:
	@${RM} packetfilter.mod
	@${LN} -s ../BINARY/packetfilter.mod packetfilter.mod

net.mod:
	@${RM} net.mod
	@${LN} -s ../BINARY/net.mod net.mod

netrain.mod:
	@${RM} netrain.mod
	@${LN} -s ../BINARY/netrain.mod netrain.mod

ether.mod:
	@${RM} ether.mod
	@${LN} -s ../BINARY/ether.mod ether.mod

loop.mod:
	@${RM} loop.mod
	@${LN} -s ../BINARY/loop.mod loop.mod

sl.mod:
	@${RM} sl.mod
	@${LN} -s ../BINARY/sl.mod sl.mod

ppp.mod:
	@${RM} ppp.mod
	@${LN} -s ../BINARY/ppp.mod ppp.mod

inet.mod:
	@${RM} inet.mod
	@${LN} -s ../BINARY/inet.mod inet.mod

nfs.mod:
	@${RM} nfs.mod
	@${LN} -s ../BINARY/nfs.mod nfs.mod

nfs_server.mod:
	@${RM} nfs_server.mod
	@${LN} -s ../BINARY/nfs_server.mod nfs_server.mod

procfs.mod:
	@${RM} procfs.mod
	@${LN} -s ../BINARY/procfs.mod procfs.mod

snmpinfo.mod:
	@${RM} snmpinfo.mod
	@${LN} -s ../BINARY/snmpinfo.mod snmpinfo.mod

bufcall.mod:
	@${RM} bufcall.mod
	@${LN} -s ../BINARY/bufcall.mod bufcall.mod

streams.mod:
	@${RM} streams.mod
	@${LN} -s ../BINARY/streams.mod streams.mod

dlb.mod:
	@${RM} dlb.mod
	@${LN} -s ../BINARY/dlb.mod dlb.mod

kinfo.mod:
	@${RM} kinfo.mod
	@${LN} -s ../BINARY/kinfo.mod kinfo.mod

strstd.mod:
	@${RM} strstd.mod
	@${LN} -s ../BINARY/strstd.mod strstd.mod

timod.mod:
	@${RM} timod.mod
	@${LN} -s ../BINARY/timod.mod timod.mod

tirdwr.mod:
	@${RM} tirdwr.mod
	@${LN} -s ../BINARY/tirdwr.mod tirdwr.mod

ldtty.mod:
	@${RM} ldtty.mod
	@${LN} -s ../BINARY/ldtty.mod ldtty.mod

xtiso.mod:
	@${RM} xtiso.mod
	@${LN} -s ../BINARY/xtiso.mod xtiso.mod

pts.mod:
	@${RM} pts.mod
	@${LN} -s ../BINARY/pts.mod pts.mod

ufs.mod:
	@${RM} ufs.mod
	@${LN} -s ../BINARY/ufs.mod ufs.mod

uipc.mod:
	@${RM} uipc.mod
	@${LN} -s ../BINARY/uipc.mod uipc.mod

vfs.mod:
	@${RM} vfs.mod
	@${LN} -s ../BINARY/vfs.mod vfs.mod

vm.mod:
	@${RM} vm.mod
	@${LN} -s ../BINARY/vm.mod vm.mod

_lmf_.mod:
	@${RM} _lmf_.mod
	@${LN} -s ../BINARY/_lmf_.mod _lmf_.mod

pckt.mod:
	@${RM} pckt.mod
	@${LN} -s ../BINARY/pckt.mod pckt.mod

ntp_time.mod:
	@${RM} ntp_time.mod
	@${LN} -s ../BINARY/ntp_time.mod ntp_time.mod

prf.mod:
	@${RM} prf.mod
	@${LN} -s ../BINARY/prf.mod prf.mod

pwrmgr.mod:
	@${RM} pwrmgr.mod
	@${LN} -s ../BINARY/pwrmgr.mod pwrmgr.mod

dec_audit.mod:
	@${RM} dec_audit.mod
	@${LN} -s ../BINARY/dec_audit.mod dec_audit.mod

dec_acl.mod:
	@${RM} dec_acl.mod
	@${LN} -s ../BINARY/dec_acl.mod dec_acl.mod

dce_acl_stubs.mod:
	@${RM} dce_acl_stubs.mod
	@${LN} -s ../BINARY/dce_acl_stubs.mod dce_acl_stubs.mod

spd_cache.mod:
	@${RM} spd_cache.mod
	@${LN} -s ../BINARY/spd_cache.mod spd_cache.mod

arch_alpha.mod:
	@${RM} arch_alpha.mod
	@${LN} -s ../BINARY/arch_alpha.mod arch_alpha.mod

in_cksum.mod:
	@${RM} in_cksum.mod
	@${LN} -s ../BINARY/in_cksum.mod in_cksum.mod

arch_alphapmap.mod:
	@${RM} arch_alphapmap.mod
	@${LN} -s ../BINARY/arch_alphapmap.mod arch_alphapmap.mod

fp.mod:
	@${RM} fp.mod
	@${LN} -s ../BINARY/fp.mod fp.mod

kn600.mod:
	@${RM} kn600.mod
	@${LN} -s ../BINARY/kn600.mod kn600.mod

dc104x.mod:
	@${RM} dc104x.mod
	@${LN} -s ../BINARY/dc104x.mod dc104x.mod

linear_io_access.mod:
	@${RM} linear_io_access.mod
	@${LN} -s ../BINARY/linear_io_access.mod linear_io_access.mod

pc_bell.mod:
	@${RM} pc_bell.mod
	@${LN} -s ../BINARY/pc_bell.mod pc_bell.mod

sio.mod:
	@${RM} sio.mod
	@${LN} -s ../BINARY/sio.mod sio.mod

pic.mod:
	@${RM} pic.mod
	@${LN} -s ../BINARY/pic.mod pic.mod

mc146818.mod:
	@${RM} mc146818.mod
	@${LN} -s ../BINARY/mc146818.mod mc146818.mod

cma_dd.mod:
	@${RM} cma_dd.mod
	@${LN} -s ../BINARY/cma_dd.mod cma_dd.mod

cam_disk.mod:
	@${RM} cam_disk.mod
	@${LN} -s ../BINARY/cam_disk.mod cam_disk.mod

cam_tape.mod:
	@${RM} cam_tape.mod
	@${LN} -s ../BINARY/cam_tape.mod cam_tape.mod

cam.mod:
	@${RM} cam.mod
	@${LN} -s ../BINARY/cam.mod cam.mod

cam_sim.mod:
	@${RM} cam_sim.mod
	@${LN} -s ../BINARY/cam_sim.mod cam_sim.mod

cam_ata.mod:
	@${RM} cam_ata.mod
	@${LN} -s ../BINARY/cam_ata.mod cam_ata.mod

isp.mod:
	@${RM} isp.mod
	@${LN} -s ../BINARY/isp.mod isp.mod

itpsa.mod:
	@${RM} itpsa.mod
	@${LN} -s ../BINARY/itpsa.mod itpsa.mod

i2c.mod:
	@${RM} i2c.mod
	@${LN} -s ../BINARY/i2c.mod i2c.mod

isa.mod:
	@${RM} isa.mod
	@${LN} -s ../BINARY/isa.mod isa.mod

gpc.mod:
	@${RM} gpc.mod
	@${LN} -s ../BINARY/gpc.mod gpc.mod

ace.mod:
	@${RM} ace.mod
	@${LN} -s ../BINARY/ace.mod ace.mod

lp.mod:
	@${RM} lp.mod
	@${LN} -s ../BINARY/lp.mod lp.mod

pci.mod:
	@${RM} pci.mod
	@${LN} -s ../BINARY/pci.mod pci.mod

tu.mod:
	@${RM} tu.mod
	@${LN} -s ../BINARY/tu.mod tu.mod

fdi.mod:
	@${RM} fdi.mod
	@${LN} -s ../BINARY/fdi.mod fdi.mod

ws.mod:
	@${RM} ws.mod
	@${LN} -s ../BINARY/ws.mod ws.mod

gpc_input.mod:
	@${RM} gpc_input.mod
	@${LN} -s ../BINARY/gpc_input.mod gpc_input.mod

qfont.mod:
	@${RM} qfont.mod
	@${LN} -s ../BINARY/qfont.mod qfont.mod

vga.mod:
	@${RM} vga.mod
	@${LN} -s ../BINARY/vga.mod vga.mod

lsm.mod:
	@${RM} lsm.mod
	@${LN} -s ../BINARY/lsm.mod lsm.mod

ddr.mod:
	@${RM} ddr.mod
	@${LN} -s ../BINARY/ddr.mod ddr.mod

kio.mod:
	@${RM} kio.mod
	@${LN} -s ../BINARY/kio.mod kio.mod

kds.mod:
	@${RM} kds.mod
	@${LN} -s ../BINARY/kds.mod kds.mod

lan_common.mod:
	@${RM} lan_common.mod
	@${LN} -s ../BINARY/lan_common.mod lan_common.mod

ev6_common.mod:
	@${RM} ev6_common.mod
	@${LN} -s ../BINARY/ev6_common.mod ev6_common.mod

per.mod:
	@${RM} per.mod
	@${LN} -s /usr/opt/PER/per.mod per.mod


MODULES: MODULE_ALPHAWS2 cm.mod generic.mod io.mod ipc.mod \
	 proc.mod sec.mod socket.mod sec_min.mod rt.mod \
	 std_kern.mod bsd_tty.mod xpr.mod cdfs.mod dvdfs.mod \
	 kdebug.mod dli.mod ffm_fs.mod atm.mod atmip.mod lane.mod \
	 atmifmp.mod atmuni.mod atmilmi3x.mod uni3x.mod bparm.mod \
	 lv.mod advfs.mod packetfilter.mod net.mod netrain.mod \
	 ether.mod loop.mod sl.mod ppp.mod inet.mod nfs.mod \
	 nfs_server.mod procfs.mod snmpinfo.mod bufcall.mod \
	 streams.mod dlb.mod kinfo.mod strstd.mod timod.mod \
	 tirdwr.mod ldtty.mod xtiso.mod pts.mod ufs.mod uipc.mod \
	 vfs.mod vm.mod _lmf_.mod pckt.mod ntp_time.mod prf.mod \
	 pwrmgr.mod dec_audit.mod dec_acl.mod dce_acl_stubs.mod \
	 spd_cache.mod arch_alpha.mod in_cksum.mod \
	 arch_alphapmap.mod fp.mod kn600.mod dc104x.mod \
	 linear_io_access.mod pc_bell.mod sio.mod pic.mod \
	 mc146818.mod cma_dd.mod cam_disk.mod cam_tape.mod cam.mod \
	 cam_sim.mod cam_ata.mod isp.mod itpsa.mod i2c.mod isa.mod \
	 gpc.mod ace.mod lp.mod pci.mod tu.mod fdi.mod ws.mod \
	 gpc_input.mod qfont.mod vga.mod lsm.mod ddr.mod kio.mod \
	 kds.mod lan_common.mod ev6_common.mod per.mod


include makelint
include makedep

