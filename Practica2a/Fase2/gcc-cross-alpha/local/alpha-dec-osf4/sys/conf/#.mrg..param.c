#!/bin/sh
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


MERGE_ROUTINE=DRI_Merge

SHELL_LIB=${SHELL_LIB:-/usr/share/lib/shell}
. $SHELL_LIB/libmrg

DefNchsz()
{
    RET=0
    grep -q "int	nchsz = 256;" $_FILE
    if [ $? -eq 0 ]
    then
        ed - $_FILE << EOF 1>/dev/null
/int	nchsz = 256;
s/256/0/
i
/*
 * nchsz overrides should be set with sysconfig using
 * stanza vfs and parameter name-cache-hash-size.  If no
 * override for vfs: name-cache-hash-size is set in
 * /etc/sysconfigtab, a default value will be
 * calculated that scales to the name-cache-size.
 */
.
w
q
EOF
        if [ "$?" = 0 ]
        then
                MRG_Echo "Removed nchsz 256 default.  New default will scale to nchsize."
        else
                MRG_Echo "\tFailed to remove nchsz 256 default."
                RET=1
        fi
    fi

    return $RET
}

DRI_Merge()
{
        RET=0
        DefNchsz || RET=1

        return $RET
}



[ "$CHECK_SYNTAX" ] || MRG_Merge "$@" 

