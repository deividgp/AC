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
#pragma ident "@(#)$RCSfile: trn_sr_data.c,v $ $Revision: 1.1.4.5 $ (DEC) $Date: 1994/05/20 18:03:38 $"

#include "sys/errno.h"
#include "tra.h"
#include "trsrcf.h"

void (*trn_init_dli)();
int srtab_entry_size;

#if NTRA || TRSRCF
extern int sr_search();
extern void srtab_update();
extern int sr_ioctl();
extern void sr_init();
int sr_entry_disable();
int sr_entry_delete();
void sr_read_attrs();
void sr_set_attrs();
int sr_find_entity();
void sr_read_table();

	int (*sr_search_func)() = sr_search;
	void (*srtab_update_func)() = srtab_update;
	int (*sr_ioctl_func)() = sr_ioctl;
	void (*sr_init_func)() = sr_init;
	int (*sr_entry_disable_func)() = sr_entry_disable;
	int (*sr_entry_delete_func)() = sr_entry_delete;
	void (*sr_read_attrs_func)() = sr_read_attrs;
	void (*sr_set_attrs_func)() = sr_set_attrs;
	int (*sr_find_entity_func)() = sr_find_entity;
	void (*sr_read_table_func)() = sr_read_table;

#else
extern int nulldev();
void nullvoid();
int sr_ioctl_nulldev();
	int (*sr_search_func)() = nulldev;
	void (*srtab_update_func)() = nullvoid;
	int (*sr_ioctl_func)() = sr_ioctl_nulldev;
	void (*sr_init_func)() = nullvoid;
	int (*sr_entry_disable_func)() = 0;
	int (*sr_entry_delete_func)() = 0;
	void (*sr_read_attrs_func)() = 0;
	void (*sr_set_attrs_func)() = 0;
	int (*sr_find_entity_func)() = 0;
	void (*sr_read_table_func)() = 0;

void
nullvoid()
{
	return;
}

int
sr_ioctl_nulldev()
{
	return(ENODEV);
}
#endif
