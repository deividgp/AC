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
# @(#)$RCSfile: protect_headers_setup.sh,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1997/04/14 19:29:23 $
#
# NAME
#	protect_headers_setup.sh
#
# SYNOPSIS
#	protect_headers_setup.sh [-l|-d|-i|-v] [-f] [dirname]
#
# DESCRIPTION
#
#	This script can be used to "protect" header files when
#	compiling with -xtaso_short or -Zpn (where n is not equal to
#	8).  You must protect header files so that pointer size and
#	structure member alignment assumptions that are made when the
#	header file is included into a compilation unit using the
#	#include directive are the same as those made when the code
#	associated with the header file was compiled.
#
#	None of the system header files are protected.  Thus, most
#	programs will not work correctly when compiled with
# 	-xtaso_short or -Zpn (where n is not equal to 8), unless you
#	protect the system header files and any other header files
#	associated with code that assumes 64-bit pointers or the
#	default natural member alignment.
#
#	This script creates symbolic links to special header prologue
#	and epilogue files in all directories in a directory tree that
#	contain header files.  The default directory tree root is
#	/usr/include, but other roots can be specified.
#
#	The special header files are named __DECC_include_prologue.h
#	and __DECC_include_epilogue.h.  The compiler checks for files
#	with these special names when processing #includes.  If the
#	special prologue file exists in the same directory as a
#	#included file, the contents of the prologue file are
#	processed just before the #included file.  Similarly, if the
#	epilogue file exists in the same directory as the #included
#	file, it is processed just after the #included file.
#
#	See the protect_headers_setup(8) and cc(1) man pages for
#	more information.
#
# OPTIONS
#
#	If [dirname] specified, use that as the root, otherwise use
#	/usr/include as the root.
#
#       The command options are meant to match their counterparts in
#	the setld command in functionality.  See also man setld(8).
#
#	-l	Loads the protected header file links
#		This will not overwrite existing files or links
#
#	-d	Deletes the protected header file links only
#
#	-f	Force delete of protected header links and files
#
#	-i	Inventories the directories where protected
#		header files or links are installed
#
#	-v	Verifies the directories and lists subdirectories
#		that do not contain the protected header file links.
#
# NOTES
#
#  When adding links, any preexisting files or links with these files
#  are not replaced.
#
#  When removing links, real files are removed if -f is specified,
#  but not if -d is specified.
#
#  Optional switches may not be combined.
#
# ********************************************************************


USAGE="Usage:  $0 [-l|-d|-i|-v] [-f] [dirname]"

HOST_DIR=${COMP_HOST_ROOT}/usr/lib/cmplrs/cc

PROLOG=__DECC_include_prologue.h
EPILOG=__DECC_include_epilogue.h

TMPFILE1=/tmp/_protect_tmp1_$$
TMPFILE2=/tmp/_protect_tmp2_$$

OPTION=FALSE
FORCE=

case $1 in
   -l)	OPTION=LINK
	;;
   -lf)	OPTION=LINK
	FORCE=-f
	;;
   -d)	OPTION=DELETE
	;;
   -df)	OPTION=DELETE
	FORCE=-f
	;;
   -f)	echo "ERROR: -f must follow -l or -d option"
	echo $USAGE; exit 1
	;;
   -i)	OPTION=INVENTORY
	;;
   -v)	OPTION=VERIFY
	;;
   "")	echo "ERROR: Must specify an option"
	echo $USAGE; exit 1
	;;
   *)	echo "ERROR: Unknown option: $1"
	echo $USAGE; exit 1
	;;
  esac

shift

if [ "$1" = "-f" ]; then
   FORCE=-f
   shift
fi

if [ "$OPTION" = "LINK" ]; then

   if [ ! -d $HOST_DIR ]; then
      echo "Creating $HOST_DIR"
      mkdir -p $HOST_DIR
   fi

   if [ ! -f $HOST_DIR/$PROLOG ]; then
      echo "Creating $HOST_DIR/$PROLOG"
      cat << EOPROLOG >> $HOST_DIR/$PROLOG
#ifdef __PRAGMA_ENVIRONMENT
#pragma __environment save
#pragma __environment header_defaults
#else
#error "__DECC_include_prologue.h:  This compiler does not support pragma __environment"
#endif
EOPROLOG
   fi

   if [ ! -f $HOST_DIR/$EPILOG ]; then
      echo "Creating $HOST_DIR/$EPILOG"
      cat << EOEPILOG >> $HOST_DIR/$EPILOG
#ifdef __PRAGMA_ENVIRONMENT
#pragma __environment restore
#else
#error "__DECC_include_epilogue.h:  This compiler does not support pragma __environment"
#endif
EOEPILOG
   fi
fi

DIR=${1:-/usr/include}

echo "Running $OPTION $FORCE option under $DIR ..."

if [ -d $DIR ]; then
   echo "Using directory: $DIR"
else
   echo "ERROR: Directory $DIR does not exist."
   exit 3
fi

cd /tmp

trap "rm -f $TMPFILE1 $TMPFILE2; exit" 1 2 15
cat /dev/null > $TMPFILE1
cat /dev/null > $TMPFILE2

#
# Get list of directories
#
echo "Generating list of directories...\c"
PREV=$DIR
while [ -n "$PREV" ]
do
   NEXT=""
   for DIR in $PREV
   do
      if [ -d $DIR ]; then
	 find $DIR/ -type d >> $TMPFILE1
	 NEXT="$NEXT `find $DIR/ -type l -print`"
      fi
   done
   PREV=$NEXT
done

sort -u $TMPFILE1 | sed 's%\/$%%g' >> $TMPFILE2

echo "done."

#
# Go thru the list of directories and link/delete/verify
#
for dir in `cat $TMPFILE2`
do
   FILES=`ls $dir/*.h 2> /dev/null`
   if [ $? = 0 ]; then
      if [ "$OPTION" = "DELETE" ]; then
	 if [ -L $dir/$PROLOG ]; then
 	    echo "Removing $dir/$PROLOG"
            rm $dir/$PROLOG               
	 elif [ -f $dir/$PROLOG ]; then
            if [ "$FORCE" = "-f" ]; then
    	       echo "Removing $dir/$PROLOG"
               rm $dir/$PROLOG               
            else
               echo "Real file $dir/$PROLOG not removed"
            fi
	 else
	    echo "No prolog file found in $dir"
         fi
         if [ -L $dir/$EPILOG ]; then
 	    echo "Removing $dir/$EPILOG"
	    rm $dir/$EPILOG
	 elif [ -f $dir/$EPILOG ]; then
            if [ "$FORCE" = "-f" ]; then
 	       echo "Removing $dir/$EPILOG"
	       rm $dir/$EPILOG
            else
 	       echo "Real file $dir/$EPILOG not removed"
            fi
	 else
	    echo "No epilog file found in $dir"
	 fi
      elif [ "$OPTION" = "VERIFY" ]; then
	 if [ ! -f $dir/$PROLOG ] && [ ! -f $dir/$EPILOG ]; then
	    echo "Warning: No protected header files found in $dir"
	 elif [ ! -f $dir/$PROLOG ]; then
	    echo "Warning: No $PROLOG found in $dir"
	 elif [ ! -f $dir/$EPILOG ]; then
	    echo "Warning: No $EPILOG found in $dir"
	 fi
      elif [ "$OPTION" = "INVENTORY" ]; then
	 if [ -L $dir/$PROLOG ]; then
	    if [ -s $dir/$PROLOG ]; then
	       echo "Link verified: $dir/$PROLOG"
	    else
	       echo "Invalid link : $dir/$PROLOG"
	    fi
	 elif [ -f $dir/$PROLOG ]; then
 	    echo "File found   : $dir/$PROLOG"
	 else
	    echo "No prolog file found in $dir"
         fi
         if [ -L $dir/$EPILOG ]; then
            if [ -s $dir/$EPILOG ]; then
 	       echo "Link verified: $dir/$EPILOG"
            else
 	       echo "Invalid link : $dir/$EPILOG"
            fi
	 elif [ -f $dir/$EPILOG ]; then
 	    echo "File found   : $dir/$EPILOG"
	 else
	    echo "No epilog file found in $dir"
	 fi
      elif [ "$OPTION" = "LINK" ]; then
	 if [ ! -f $dir/$PROLOG ] || [ "$FORCE" = "-f" ]; then
	    echo "Linking $dir/$PROLOG"
            ln -sf $HOST_DIR/$PROLOG $dir
         else
	    echo "File exists: $dir/$PROLOG, not linked"
	 fi
	 if [ ! -f $dir/$EPILOG ] || [ "$FORCE" = "-f" ]; then
            echo "Linking $dir/$EPILOG"
	    ln -sf $HOST_DIR/$EPILOG $dir
         else
	    echo "File exists: $dir/$PROLOG, not linked"
	 fi
      fi
   fi
done

# Cleanup
rm -f $TMPFILE1 $TMPFILE2

