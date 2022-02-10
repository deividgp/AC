#!/sbin/sh -
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
# @(#)$RCSfile: voladm_lib.sh,v $ $Revision: 1.1.8.7 $ (DEC) $Date: 1995/12/20 16:09:09 $
# 
# @(#)src/common/cmd/vxvm/voladm/voladm_lib.sh	5.14 16 Mar 1993 01:20:44 - Copyright (c) 1993 VERITAS Software Corp.
#ident	"@(#)vxvm:common/cmd/vxvm/voladm/voladm_lib.sh	5.14"

# Copyright(C)1993 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
# UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
# LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
# IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
# OR DISCLOSURE.
# 
# THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
# TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
# OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
# EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
# 
#               RESTRICTED RIGHTS LEGEND
# USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
# SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
# (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
# COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
#               VERITAS SOFTWARE
# 4800 GREAT AMERICA PARKWAY, SANTA CLARA, CA 95054

DSPMSG="/sbin/lsm.d/bin/dspmsg -s 1 lsm_sh.cat"
Y=`$DSPMSG 4050 "y"`
YY=`$DSPMSG 4051 "yes"`
N=`$DSPMSG 4052 "n"`
NN=`$DSPMSG 4053 "no"`
YORN=`$DSPMSG 4054 "y,n"`

VOLADM_ROOT=${VOLADM_ROOT-/usr/lib/lsm}
VOLUSRBIN=${VOLUSRBIN-/usr/lib/lsm/bin}
VOLADM_BIN=${VOLADM_BIN-$VOLADM_ROOT/bin}
VOLADM_LIB=${VOLADM_LIB-$VOLADM_ROOT/lib}
VOLADM_HELP=${VOLADM_HELP-$VOLADM_ROOT/help}


export VOLADM_ROOT
export VOLADM_BIN
export VOLADM_LIB
export VOLADM_HELP

#NEED_PATH=/etc/vol/bin:$VOLADM_BIN:/usr/sbin:/sbin:/usr/bin
NEED_PATH=$VOLADM_BIN:/usr/sbin:/sbin:/usr/bin:/usr/lib/lsm/bin
case $PATH in
$NEED_PATH|$NEED_PATH:*) ;;
*)	PATH=$NEED_PATH:$PATH; export PATH;;
esac

voladm_menu_stack=
cleanup_list=cleanup_tempfiles
newline='
'

v_opt=
verbose=
if [ "X$1" = X-v ]
then
	verbose=yes
	v_opt=-v
	shift
fi

TMPDIR=/etc/vol/reconfig.d/tmp.d
export TMPDIR
[ -d $TMPDIR ] || mkdir -p /etc/vol/reconfig.d/tmp.d
tmpfile1=${TMPDIR:-/tmp}/vx1.$$
tmpfile2=${TMPDIR:-/tmp}/vx2.$$
tmpfile3=${TMPDIR:-/tmp}/vx3.$$
tmpdfile=${TMPDIR:-/tmp}/vx4.$$

cleanup_tempfiles()
{
	rm -f $tmpfile1 $tmpfile2 $tmpfile3 $tmpdfile
}

quit()
{
	trap "" 2 1 3 15
	for f in $cleanup_list
	do
		"$f"
	done
	exit $1
}

trap "quit 100" 2 1 3 15

exec 4<&0 5>&2

# doit - execute a command, printing the command in verbose mode
doit()
{
	[ "$verbose" ] && echo ! "$@" >&5
	"$@"
}

writemsg()
{
	echo "";
	for _wm_line in "$@"
	do
		echo "  $_wm_line"
	done
}

read_input()
{
	echo ""
	_once=
	if [ "X$1" = X-m ]
	then
		_once=yes
		shift
	fi
	_prompt="$1 "
	[ -z "$2" ] || _prompt="${_prompt}[$2,q,?] "
	[ -z "$3" ] || _prompt="${_prompt}(default: $3) "
	case $_prompt in
	??????????????????????????????????????????????????????????????????*)
		if [ ! -z "$2" ] || [ ! -z "$3" ]
		then
			_prompt="$1$newline"
			[ -z "$2" ] || _prompt="${_prompt}[$2,q,?] "
			[ -z "$3" ] || _prompt="${_prompt}(default: $3) "
		fi
		;;
	esac
	while true
	do
		echo "$_prompt\c"
		read input <&4
		case $input in
		"")	input=$3; return 0;;
		"!")	${SHELL:-sh} <&4
			echo !
			[ ! -z "$_once" ] && return 1;;
		"!"*)	${SHELL:-sh} -c "`expr "$input" : '!\(.*\)'" <&4
			echo !
			[ ! -z "$_once" ] && return 1;;
		'?')	voladm_help; [ ! -z "$_once" ] && return 1;;
#		'??')	voladm_help_help; [ ! -z "$_once" ] && return 1;;
		q)	quit 101;;
		x)	quit 100;;
		*)	return 0;;
		esac
	done
}

pop_list()
{
	_list=$1
	eval "set -- \$$_list"
	shift
	eval "$_list=\$*"
}

first_item()
{
	echo $1
}

list_item()
{
	_item=$1
	shift
	eval "echo \${$_item}"
}

list_count()
{
	echo $#
}

push_list()
{
	_list=$1
	shift
	eval "set -- \$* \$$_list"
	eval "$_list=\$*"
}

append_list()
{
	_list=$1
	shift
	eval "set -- \$$_list \$*"
	eval "$_list=\$*"
}

list_member()
{
	_want=$1
	shift
	for i in $@
	do
		[ "X$_want" = "X$i" ] && return 0
	done
	return 1
}

not()
{
	"$@"
	[ $? -eq 0 ] && return 1
	return 0
}

add_cleanup()
{
	push_list cleanup_list $*
}

voladm_menu_push()
{
	push_list voladm_menu_stack $VOLADM_CURRENT_MENU
	if [ -z "$VOLADM_CURRENT_MENU" ]
	then
		VOLADM_CURRENT_MENU=$1
	else
		VOLADM_CURRENT_MENU=$VOLADM_CURRENT_MENU/$1
	fi
	export VOLADM_CURRENT_MENU
}

voladm_menu_pop()
{
	VOLADM_CURRENT_MENU=`first_item $voladm_menu_stack`
	export VOLADM_CURRENT_MENU
	pop_list voladm_menu_stack
}

voladm_menu_set()
{
	voladm_menu_pop
	voladm_menu_push $1
}

voladm_help_push()
{
	voladm_help_stack="$VOLADM_CURRENT_HELP $voladm_help_stack"
	VOLADM_CURRENT_HELP=$1
	export VOLADM_CURRENT_HELP
}

voladm_help_pop()
{
	VOLADM_CURRENT_HELP=`first_item $voladm_help_stack`
	export VOLADM_CURRENT_HELP
	pop_list voladm_help_stack
}

voladm_help_set()
{
	voladm_help_pop
	voladm_help_push $1
}

voladm_help_help()
{
	voladm_help voladm.info
}

voladm_help()
{
	help=${1:-$VOLADM_CURRENT_HELP}
	if [ -x /usr/bin/tput ] && [ ! -z "$TERM" ]
	then
		tput clear
	fi
	( $DSPMSG 4000 "%s\nMenu: %s\n\n" \
		"$title" "$VOLADM_CURRENT_MENU"
	  grep -v "^#" $VOLADM_HELP/$help
	  echo "" ) > $TMPDIR/voladm_help.$$ 
	  voladm_display $TMPDIR/voladm_help.$$
	  rm -f $TMPDIR/voladm_help.$$
}

# display something, using a pager, if needed
voladm_display()
{
	cat "$@" > $tmpdfile
	lines=`tput lines`
	[ -z "$lines" ] && lines=24
	if [ "`wc -l < $tmpdfile`" -ge $lines ]
	then
		${PAGER:-pg} $tmpdfile <&4
	else
		cat $tmpdfile
	fi
}

voladm_call()
{
	_util=$1
	shift

	doit "$_util" $v_opt "$@" <&4
	status=$?
	if [ $status -eq 100 ] || [ $status -eq 101 ]
	then
		quit $status
	fi
	return $status
}

voladm_menu_call()
{
	_util=$1
	shift

	doit "$_util" $v_opt "$@" <&4
	status=$?
	if [ $status -eq 100 ]
	then
		quit 100
	fi
	return $status
}

voladm_begin_screen()
{
	if [ "$1" = "-M" ]
	then
		_vbs_catnum="$2"
		_vbs_def="$3"
		shift 3
		_vbs_msg=`$DSPMSG $_vbs_catnum "$_vbs_def"`
	else
		_vbs_msg="$1"
	fi
	tput clear
	$DSPMSG 4001 "\n%s\nMenu: %s\n\n" \
		"$_vbs_msg" "$VOLADM_CURRENT_MENU"
}

voladm_menu()
{
	_menu_h1=`$DSPMSG 4002 "Display help about menu"`
#	_menu_h2=`$DSPMSG 4003 "Display help about the menuing system"`
	_menu_h3=`$DSPMSG 4004 "Exit from menus"`
	_menu_h4=`$DSPMSG 4005 "Select an operation to perform"`
	_menu_h5=`$DSPMSG 4006 "default"`

	read _menu_title
	_menu_default=
	_menu=`$DSPMSG 4007 "%s\nMenu: %s\n\n" \
		"$_menu_title" "$VOLADM_CURRENT_MENU"`
	_menu="$_menu\n"
	_menu_select='case $input in'
	while read _menu_key _menu_item _menu_text
	do
		if [ -z "$_menu_key" ]
		then
			_menu="$_menu\n"
		elif [ "X$_menu_item" = Xdefault ]
		then
			_menu_default=$_menu_key
		else
			_menu_select="$_menu_select '$_menu_key')VOLADM_MENU_SELECT=$_menu_item;break 2;;"
			if [ ! -z "$_menu_text" ]
			then
				_menu="$_menu\n $_menu_key\t$_menu_text"
			fi
		fi
	done
	_menu_select="$_menu_select *) ;; esac"
	_menu="$_menu\n ?\t$_menu_h1"
#	_menu="$_menu\n ??\t$_menu_h2"
	_menu="\n$_menu\n q\t$_menu_h3"
	_menu_prompt="${1:-$_menu_h4:}"
	if [ ! -z "$_menu_default" ]
	then
		_menu_prompt="$_menu_prompt [$_menu_h5: $_menu_default]"
	fi

	while true
	do
		tput clear
		echo "$_menu"
		while true
		do
			read_input -m "$_menu_prompt" "" $_menu_default
			if [ $? -ne 0 ]
			then
				voladm_continue
				continue 2
			fi
			eval "$_menu_select"

			case $input in
			x)	quit 100;;
			q)	quit 101;;
			'?')	voladm_help; continue 2;;
			h)	voladm_help; continue 2;;
			help)	voladm_help; continue 2;;
#			'??')	voladm_help_help; continue 2;;
			esac
			$DSPMSG 4008 "  Selection not recognized, enter ? for help\n"
		done
	done

	echo ""
}

# voladm_yorn question default
voladm_yorn()
{
	if [ "$1" = "-M" ]
	then
		_vadm_catnum="$2"
		_vadm_def="$3"
		_vadm_yon="$4"
		shift 4
		_vadm_msg=`$DSPMSG $_vadm_catnum "$_vadm_def"`
	else
		_vadm_msg="$1"
		_vadm_yon="$2"
	fi
	while true
	do
		read_input "$_vadm_msg" "$YORN" $_vadm_yon
		case $input in
		$Y|$YY)	return 0;;
		$N|$NN)	return 1;;
		*)	$DSPMSG 4009 "  Please respond with \"y\" or \"n\"\n"
			continue;;
		esac
	done
}

# voladm_continue purpose
voladm_continue()
{
	_vc_opt=`$DSPMSG 4010 "Hit RETURN to continue."`
	echo "${1:-$_vc_opt}\c"
	read _continue <&4
	case $_continue in
	q)	quit 101;;
	x)	quit 100;;
	*)	return 0;;
	esac
}

# Like voladm_continue, but no quit option.
voladm_do_continue()
{
	_vc_opt=`$DSPMSG 4010 "Hit RETURN to continue."`
	echo "${1:-$_vc_opt}\c"
	read _continue <&4
	return 0
}

# voladm_disk_device purpose [default [select-list]]
voladm_disk_device()
{
	if [ "$1" = "-M" ]
	then
		_vdskd_catnum="$2"
		_vdskd_def="$3"
		shift 2		# this makes $3=addr/list $2 as otherwise
		_vdskd_msg=`$DSPMSG $_vdskd_catnum "$_vdskd_def"`
	else
		_vdskd_msg="$1"
	fi
	while true
	do
		_vdskd_opt=`$DSPMSG 4011 "<disk/partition name>,list"`
		read_input "$_vdskd_msg" "${3:-$_vdskd_opt}" $2
		device=$input
		[ "X$device" = "X$2" ] && return 0
		case $device in
#		rz*) daname=${device}; return 0;;
#		ra*) daname=${device}; return 0;;
#		re*) daname=${device}; return 0;;
		list|l)	voldevlist > $TMPDIR/voladm_disk_device.$$
			voladm_display $TMPDIR/voladm_disk_device.$$
			rm -f $TMPDIR/voladm_disk_device.$$
			continue;;
		*) daname=${device}; return 0;;
#		*) "Input not recognized, enter ? for help";;
		esac
	done
}

# voladm_disk_group purpose default
voladm_disk_group()
{
	_new_group_okay=
	if [ X$1 = X-n ]
	then
		_new_group_okay=yes
		shift
	fi
	_opt=`$DSPMSG 4012 "<group>,list"`
	[ $# -eq 3 ] && _opt=`$DSPMSG 4013 "<group>,none,list"`
	_default=$2
	_prompt=$1
	while true
	do
		_mess=`$DSPMSG 4014 "Which disk group"`
		read_input "$_mess" "$_opt" $_default
		dgname=$input
		case $dgname in
		"")	$DSPMSG 4015 "  A disk group name is required.\n"
			continue;;
		list|l)	voldg list > $TMPDIR/voladm_disk_group.$$
			voladm_display $TMPDIR/voladm_disk_group.$$
			rm -f $TMPDIR/voladm_disk_group.$$
			continue;;
		*" "* | *"	"*)
			$DSPMSG 4016 "  Disk group name %s is not valid.\n" $dgname
			continue;;
		none)	[ $# -eq 3 ] && return 0;;
		esac
		_voldg_output=`voldg -q list | grep "^\$dgname[ 	]"`
		if [ `list_count $_voldg_output` -ne 3 ]
		then
			$DSPMSG 4017 "  There is no active disk group named %s.\n" $dgname
			message=`$DSPMSG 4018 "Create a new group named %s?" $dgname`
			if [ -n "$_new_group_okay" ] &&
			   voladm_yorn "$message" y
			then
				return 10
			fi
			continue
		fi
		if [ "X`list_item 2 $_voldg_output`" != Xenabled ]
		then
		 $DSPMSG 4019 "\n  Disk group %s is not currently usable due to errors.\n" $dgname
			continue
		fi
		return 0
	done
}

voladm_new_disk_dmname()
{
	if [ -x $VOLUSRBIN/volparms ]; then 
		_default_dmname=`volnewdmname "$1"`
	else
		_default_dmname="$2"
	fi

	_vndd_prompt=`$DSPMSG 4020 "Enter disk name"`
	_vndd_opt=`$DSPMSG 4021 "<name>"`
	read_input "$_vndd_prompt" "$_vndd_opt"  $_default_dmname
	dmname=$input
	return 0
}

voladm_get_disk_dmname()
{
	_dm_want_removed=
	if [ "X$1" = X-r ]
	then
		_dm_want_removed=yes
		shift
	fi
	_dm_want_spec_dg=
	if [ "X$1" = X-g ]
	then
		shift
		_dm_want_spec_dg=$1
		shift
	fi
	_dm_opt=`$DSPMSG 4022 "Enter disk name"`
	_dm_prompt="${1:-$_dm_opt}"
	_default=$2

	while true
	do
		_dm_opt=`$DSPMSG 4023 "<disk>,list"`
		read_input "$_dm_prompt" "$_dm_opt" $_default
		dmname=$input
		case $input in
		"")	$DSPMSG 4024 "\n  Please enter a disk name, or type \"list\" to list all disks.\n"
			continue;;
		$_default)
			return 0;;
		list|l)	if [ "$_dm_want_removed" ]
			then
				(echo ""
				 if [ -z "$_dm_want_spec_dg" ]
				 then
				 	volprint -Atd
				 else
				 	volprint -td -g "$_dm_want_spec_dg"
				 fi |
					awk '$1!="dm" || $3=="-" {print $0;}'
				 echo "") > $TMPDIR/voladm_get_disk_dmname.$$
				 voladm_display $TMPDIR/voladm_get_disk_dmname.$$
				 rm -f $TMPDIR/voladm_get_disk_dmname.$$
			else
				volprint -Atd > $TMPDIR/voladm_get_disk_dmname.$$
				voladm_display $TMPDIR/voladm_get_disk_dmname.$$
				rm -f $TMPDIR/voladm_get_disk_dmname.$$
			fi
			continue
			;;
		esac
		if [ -z "$_dm_want_spec_dg" ]
		then
			set -- `volprint -AQF "%dgname" "\$dmname" 2> /dev/null`
		else
			set -- `volprint -g "$_dm_want_spec_dg" \
					-F "%dgname" "\$dmname" 2> /dev/null`
		fi
		if [ $# -eq 0 ] && [ -z "$_dm_want_spec_dg" ]
		then
	 $DSPMSG 4025 "\n  There is no disk named %s in any disk group configuration.\n" $dmname
	 $DSPMSG 4026 "  To get a list of disks enter \"list\".\n"
			continue
		elif [ $# -eq 0 ]
		then
	 $DSPMSG 4027 "\n  There is no disk named %s in disk group %s.\n" $dmname $_dm_want_spec_dg
	 $DSPMSG 4026 "  To get a list of disks enter \"list\".\n"
		fi
		break
	done
	if [ $# -eq 1 ]
	then
		dgname=$1
		return 0
	fi
	break
	 $DSPMSG 4028 "\n  There is a disk named %s in each of the following disk groups:\n\t\%s\n" \
		$dmname "$*"
	while true
	do
		_dm_prompt=`$DSPMSG 4029 "Enter the disk group to use"`
		_dm_opt=`$DSPMSG 4030 "group"`
		read_input "$_dm_prompt" "$_dm_opt" $1
		for dgname in $*
		do
			if [ "X$dgname" = "X$input" ]
			then
				return 0
			fi
		done
		$DSPMSG 4031 "  Please choose a disk group from the list:\n\n\t%s\n" \
			"$*"
	done
}

# re-online all online disks
voladm_reonline_all()
{
	voldisk -q list |
	while read daname type disk group status
	do
		if [ "X$group" = X- ] && not list_member offline $status
		then
			doit voldisk online $device 2> /dev/null
		fi
	done
}

# get the system hostid from the volboot file in system_hostid
voladm_system_hostid()
{
	system_hostid=
	system_hostid=`voldctl list | grep '^hostid:' |
			{ read key hostid; echo "$hostid"; }`
	if [ -z "$system_hostid" ]
	then
	 $DSPMSG 4032 "\n  Unexpected internal error -- Cannot get the system's hostid.\n"
		return 1
	fi
	return 0
}


# Determine optimal values of nconfig and nlog based on the number of 
# disks already present in the diskgroup. 
get_disk_params()
{
	dgname=$1

	# Get the largest private region size in the diskgroup. 
	# "nopriv" disks have a privlen of 0 and hence should not 
	# be used in getting the privlen value below. 
	privlen=`volprint -htdq -g $dgname | awk '{if($5 != 0 && ($5 != "-")) print $5}' | sort -n -r | head -1`
	# Set the nconfig and nlog values dependent on the number 
        # of disks already added to the diskgroup.
	# Do not include "nopriv" disks that could have been added 
	# to the diskgroup. 
	numdm=`voldg list $dgname | grep 'config disk' | \
		awk '{print $3}' | sort -u | wc -l`
	if [ $numdm -lt 4 ]; then
		numcf=2
	elif [ $numdm -lt 8 ]; then
		numcf=1
	else
		numcf=0
	fi
	# Adjust the nconfig and nlog values to the lowest number of
        # config copies per disk in the diskgroup. 
	disks=`volprint -htdq -g $dgname | grep -E "simple|sliced" | \
		awk '{print $3}'`		
	nc=`voldisk list $disks | grep 'configs:' | \
		sed -e 's/.*count=//' | sed -e 's/ .*//' | sort | head -1`
	[ $nc -lt $numcf ] && numcf=$nc
	attrs="nconfig=$numcf nlog=$numcf"
}


# Used in disk.init.sh to get an estimate on the size 
# of the new diskgroup being created. 
get_diskgroup_params()
{
	dgname=$1

	numdisks=
	while [ -z "$numdisks" ]; do
		$DSPMSG 4033 "\n  Approximate maximum number of physical disks that\n"
		$DSPMSG 4034 "  will be added to the %s diskgroup.\n" $dgname
		_dp_prompt=`$DSPMSG 4035 "Number of disks"`
		_dp_opt=`$DSPMSG 4036 "e.g. 5,10,30,60"`
		read_input "$_dp_prompt" "$_dp_opt"  10
		numdisks=$input
	done

	privlen=1024;
	attrs="nconfig=1 nlog=1"
	if [ $numdisks -le 4 ]; then
		attrs="nconfig=2 nlog=2"
	elif [ $numdisks -gt 256 ]; then
		privlen=2048
	elif [ $numdisks -gt 128 ]; then
		privlen=1536
	fi
}
