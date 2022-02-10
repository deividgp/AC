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
 * @(#)$RCSfile: lock_probe.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 1995/02/17 01:33:34 $
 */
#ifndef _LOCK_PROBE_H 
#define _LOCK_PROBE_H

#ifdef _KERNEL
#include <kern/lock.h>

/*
 * PROBE_START and PROBE_END Macros.
 *
 * For the moment these are only place holders.
 * Also LOCK_PROBE is defined here to be true
 * for now.  It can also be set in the target
 * specific configuration files.
 */

//#define LOCK_PROBE	1
#ifdef LOCK_PROBE

extern int probe_smp;



/* probe configuration table:
 *   the goal is to allow multi-order level probe testing, without having
 *   to manually modify each probe statement;  i.e. we don't want to have
 *   to replicate the effort already used which put 1st level probes into
 *   the code.
 *   
 *   we build in a probe configuration table which describes how probes
 *   relate to other probes, so that we only need to change the table, and
 *   not every occurrence of a probe.  the probe table is a list of related
 *   probes (for a given probe), and counters which get incremented for the
 *   combination of probes.
 *
 */

/* You must change the PROBE_TABLE macro if you change these constants.
 */
#define PROBE_ORDERS    4
#define PROBE_COUNTERS  16   // n**2 counters; where n=PROBE_ORDERS

typedef struct {
        int             type;                   /* #probes   */
        lock_data_t     *probe[PROBE_ORDERS];   /* max(n)=4  */
        int             count[PROBE_COUNTERS];  /* n*(n-1)+1 */
} probe_config_t;

typedef struct {
        lock_data_t     pb_lock;
        probe_config_t  *pb_table;
} probe_desc_t;

#define PROBE_DECL(class,lname)         class probe_desc_t      lname;
#define PROBE_DECL_INFO(class,liname)   class struct lockinfo   *liname;

/* PROBE_START() macro.
 * For each probe that is active, a flag bit is set. 
 * The bit position set corresponds to the probe's offset in the table.
 * Example: probe[1] sets flag bit 0100; probe[3] sets flag bit 0001,
 *          assuming there are 4 probes as determined by PT->type value.
 */

#define PROBE_START(PD,a,b,c,d,e)                       \
MACRO_BEGIN                                             \
if (probe_smp) {                                        \
   probe_config_t *PT = (PD)->pb_table;                 \
   int np;                                              \
   np = (PT) ? PT->type : 0;                            \
   lock_read(&(PD)->pb_lock);                           \
   if (np > 1) {                                        \
      unsigned int flag;                                \
      int j;                                            \
      for (flag=0, j=0; j<np; j++)                      \
        if (lock_islocked((PT)->probe[j]))              \
          flag |= (unsigned int)1<<(np-1-j);            \
      PT->count[flag]++;                                \
   }                                                    \
}                                                       \
MACRO_END

#define PROBE_END(PD,a,b,c,d,e) if (probe_smp) lock_done(&(PD)->pb_lock)

#define PROBE_TABLE(PT,NUM,P1,P2,P3,P4)                                          \
MACRO_BEGIN                                                                      \
    if ((NUM) > 1) {                                                             \
       int i;                                                                    \
       (PT)->type = (NUM);                                                       \
       (PT)->probe[0] = (P1) ? (lock_data_t *)&((probe_desc_t *)(P1))->pb_lock : \
	                (lock_data_t *) 0;                                       \
       (PT)->probe[1] = (P2) ? (lock_data_t *)&((probe_desc_t *)(P2))->pb_lock : \
	                (lock_data_t *) 0;                                       \
       (PT)->probe[2] = (P3) ? (lock_data_t *)&((probe_desc_t *)(P3))->pb_lock : \
	                (lock_data_t *) 0;                                       \
       (PT)->probe[3] = (P4) ? (lock_data_t *)&((probe_desc_t *)(P4))->pb_lock : \
	                (lock_data_t *) 0;                                       \
       for (i=0; i<(PROBE_COUNTERS-1); i++)                                      \
          (PT)->count[i] = 0;                                                    \
    }                                                                            \
MACRO_END

#define PROBE_SETUP(PD,LI,FL,PT)                \
MACRO_BEGIN                                     \
    lock_setup(&(PD)->pb_lock, (LI), (FL));     \
    (PD)->pb_table = (PT);                      \
MACRO_END

#else   /* !LOCK_PROBE */
#define PROBE_DECL(class,name)
#define PROBE_DECL_INFO(class,name)
#define PROBE_START(a,b,c,d,e,f)   
#define PROBE_END(a,b,c,d,e,f)    
#define PROBE_TABLE(PT,NUM,P1,P2,P3,P4)
#define PROBE_SETUP(PD,LI,FL,PT)
#endif  /* LOCK_PROBE */

#endif	/* KERNEL */
#endif /* _LOCK_PROBE_H */









