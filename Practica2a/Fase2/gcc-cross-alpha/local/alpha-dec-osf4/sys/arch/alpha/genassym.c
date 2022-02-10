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
#pragma ident "@(#)$RCSfile: genassym.c,v $ $Revision: 1.2.71.2 $ (DEC) $Date: 1999/01/07 19:35:30 $"

/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

#include <mach_emulation.h>
#include <sys/proc.h>
#include <kern/lock.h>
#include <machine/pcb.h>
#include <machine/pmap.h>
#include <machine/rpb.h>
#include <svr4/sar.h>
#include <mach/machine.h>
#include <machine/machparam.h>
#include <machine/nxm.h>

#if	MACH_EMULATION
#include <kern/syscall_emulation.h>
#endif

#if PROFILING
#include <sys/gprof.h>
#endif

main()
{
	register struct proc *p = (struct proc *)0;
	register struct utask *utask = (struct utask *)0;
	register struct uthread *uthread = (struct uthread *)0;
	register struct np_uthread *nputhread = (struct np_uthread *)0;
	register struct ushared_state *ushare = (struct ushared_state *)0;
	register struct rusage *rup = (struct rusage *)0;
	struct thread *thread = (struct thread *) 0;
	struct task *task = (struct task *) 0;
	struct vm_map *vm_map = (struct vm_map *) 0;
	struct pmap *pmap = (struct pmap *)0;
	struct pcb *pcb = (struct pcb *)0;
        struct uuprof *uprof = (struct uuprof *)0;
	struct rpb_percpu *percpu = (struct rpb_percpu *)0;
	struct bootpcb *bootpcb = (struct bootpcb *)0;
	struct rpb *rpb = (struct rpb *)0;
#if	MACH_EMULATION
	struct eml_dispatch *disp = (struct eml_dispatch *)0;
#endif
	struct stack_layout *stack_layout=(struct stack_layout *)0;
	struct slock_debug *sdp = (struct slock_debug *)0;
	struct lockinfo *lip = (struct lockinfo *)0;
	struct lockstats *lsp = (struct lockstats *)0;
	struct sar_data *sar = (struct sar_data *)0;
	struct machine_slot *machine = (struct machine_slot *) 0;

	printf("#ifdef ASSEMBLER\n");

	printf("#define\tMACHINE_SLOT_SIZE %d\n", sizeof(struct machine_slot));
	printf("#define\tMACHINE_RUNNING %d\n",&machine->running);
	printf("#define\tMACHINE_PANICSTR %d\n",&machine->cpu_panicstr);
	printf("#define\tMACHINE_ERROR_RESTART %d\n",&machine->error_restart);
	printf("#define\tP_SIG %d\n", &p->p_sig);
	printf("#define\tP_FLAG %d\n", &p->p_flag);
	printf("#define\tP_UAC %d\n", &p->p_uac);
	printf("#define\tNBPW %d\n", NBPW);

	printf("#define\tRU_MINFLT %d\n", &rup->ru_minflt);

	printf("#define\tSTACK_BASE %d\n", &stack_layout->pcb);

	printf("#define\tPCB_BASE %d\n", &stack_layout->pcb);
	printf("#define\tUTHREAD_BASE %d\n", &stack_layout->uthread);
	printf("#define\tUTHREAD_UNIX_LOCK %d\n", &stack_layout->uthread.uu_unix_lock);

	printf("#define\tSTACK_LAYOUT_SIZE %d\n", sizeof(struct stack_layout));
	printf("#define\tPCB_REGS %d\n", &pcb->pcb_regs[0]);
	printf("#define\tPCB_USP %d\n", &pcb->pcb_usp);
	printf("#define\tPCB_OWNEDFP %d\n", &pcb->pcb_ownedfp);
	printf("#define\tPCB_PADDR %d\n", &pcb->pcb_paddr);
	printf("#define\tPCB_FEN %d\n", &pcb->pcb_fen);
	printf("#define\tPCB_NOFAULT %d\n", &pcb->pcb_nofault);
	printf("#define\tPCB_NOFAULT_BADVADDR %d\n",&pcb->pcb_nofault_badvaddr);
	printf("#define\tPCB_NOFAULT_CAUSE %d\n", &pcb->pcb_nofault_cause);
	printf("#define\tPCB_FPREGS %d\n", &pcb->pcb_fpregs[0]);
	printf("#define\tPCB_FPCR %d\n", &pcb->pcb_fpcr);
	printf("#define\tPCB_AST %d\n", &pcb->pcb_ast);
	printf("#define\tPCB_CURCPU_LOCK %d\n", &pcb->pcb_curcpu_lock);
	printf("#define\tPCB_CURRENT_CPU %d\n", &pcb->pcb_current_cpu);
	printf("#define\tPCB_SLOCK_COUNT %d\n", &pcb->pcb_slock_count);
	printf("#define\tPCB_SLOCK_HIERARCHY %d\n", &pcb->pcb_slock_hierarchy);
	printf("#define\tPCB_SLOCK_UNORDERED %d\n", &pcb->pcb_slock_unordered);
	printf("#define\tPCB_AT_INTR_LEVEL %d\n", &pcb->pcb_atintr_level);
	printf("#define\tU_UPROC %d\n",&uthread->proc);
	printf("#define\tU_UTHREAD %d\n",&uthread->thread);
	printf("#define\tU_NPUTHREAD %d\n",&uthread->np_uthread);
	printf("#define\tU_UTASK %d\n",&uthread->utask);
	printf("#define\tU_FBHANDLER %d\n",&utask->uu_fbhandler);

	printf("#define\tU_CURSIG %d\n", &nputhread->uu_cursig);
	printf("#define\tU_SPTR %d\n", &nputhread->uu_sptr);
	printf("#define\tU_SIG %d\n", &ushare->sig);

	printf("#define\tSD_ADDR %d\n", &sdp->sd_addr[0]);
	printf("#define\tSD_TIME %d\n", &sdp->sd_time[0]);
	printf("#define\tMAX_SLOCK %d\n", MAX_SLOCK);

	printf("#define\tLI_COUNT %d\n", &lip->li_count);
	printf("#define\tLI_FLGSPL %d\n", &lip->li_flgspl);
	printf("#define\tLI_SPLMASK %d\n", LI_SPLMASK);
	printf("#define\tLI_RWS	%d\n", LI_RWS);
	printf("#define\tLI_ORDERED %d\n", LI_ORDERED);
	printf("#define\tLI_ORDNEXT %d\n", LI_ORDNEXT);
	printf("#define\tLI_DOHIER %d\n", LI_DOHIER);
	printf("#define\tLI_VALID %d\n", LI_VALID);
	printf("#define\tLOCKINFO_SHIFT %d\n", LOCKINFO_SHIFT);

	printf("#define\tRWS_BYTE_STRIDE %d\n", 
					1<<RWS_BLOCK_SIZE_SHIFT);
	printf("#define\tRWS_BLOCK_SIZE_SHIFT %d\n", 
					RWS_BLOCK_SIZE_SHIFT);
	printf("#define\tLS_TRIES %d\n", &lsp->ls_tries);
	printf("#define\tLS_READS %d\n", &lsp->ls_reads);
	printf("#define\tLS_TRMAX %d\n", &lsp->ls_trmax);
	printf("#define\tLS_MISSES %d\n", &lsp->ls_misses);
	printf("#define\tLS_WAITMAX %d\n", &lsp->ls_waitmax);
	printf("#define\tLS_WAITMIN %d\n", &lsp->ls_waitmin);
	printf("#define\tLS_WAITSUM %d\n", &lsp->ls_waitsum);
	printf("#define\tLOCKSTATS_SHIFT %d\n", LOCKSTATS_SHIFT);

#if	SEC_BASE
	printf("#define\tU_ERROR %d\n", &nputhread->uu_error);
#endif
	printf("#define\tU_AR0 %d\n", &nputhread->uu_ar0);
	printf("#define\tTHREAD_TASK %d\n", &thread->task);
	printf("#define\tTHREAD_STACK %d\n", &thread->stack);
	printf("#define\tTHREAD_STATE %d\n", &thread->state);
	printf("#define\tTH_SWAPPED %d\n", TH_SWAPPED);
	printf("#define\tTHREAD_PMAP %d\n", &thread->pmap);
	printf("#define\tTHREAD_LW_VA %d\n", &thread->lw_va);
	printf("#define\tTHREAD_LW_PAGES %d\n", &thread->lw_pages);
	printf("#define\tTHREAD_NXM_FLAGS %d\n",&thread->nxm_flags);
	printf("#define\tNXM_IDLE 	  %d\n",NXM_IDLE);
	printf("#define\tPR_BASE %d\n", &uprof->pr_base);
	printf("#define\tPR_SIZE %d\n", &uprof->pr_size);
	printf("#define\tPR_OFF %d\n", &uprof->pr_off);
	printf("#define\tPR_SCALE %d\n", &uprof->pr_scale);
	printf("#define\tPR_STRUCT_SIZE %d\n", &uprof[1]);

	printf("#define\tRPB_SELFREF %d\n",&rpb->rpb_selfref);
	printf("#define\tRPB_EXT_VA_SIZE %d\n",&rpb->rpb_ext_va_size);
	printf("#define\tRPB_PERCPU_OFF %d\n",&rpb->rpb_percpu_off);
	printf("#define\tRPB_SLOTSIZE %d\n",&rpb->rpb_slotsize);
	printf("#define\tRPB_STATE %d\n", &percpu->rpb_state);
	printf("#define\tRPB_HALTPB %d\n", &percpu->rpb_haltpb);
	printf("#define\tRPB_HALTPC %d\n", &percpu->rpb_haltpc);
	printf("#define\tRPB_HALTPS %d\n", &percpu->rpb_haltps);
	printf("#define\tRPB_HALTAL %d\n", &percpu->rpb_haltal);
	printf("#define\tRPB_HALTRA %d\n", &percpu->rpb_haltra);
	printf("#define\tRPB_HALTPV %d\n", &percpu->rpb_haltpv);
	printf("#define\tBOOTPCB_KSP %d\n", &bootpcb->rpb_ksp);
	printf("#define\tBOOTPCB_KSP_BACKUP %d\n", &bootpcb->rpb_ksp_backup);

	printf("#define\tTASK_MAP %d\n", &task->map);
	printf("#define\tMAP_PMAP %d\n", &vm_map->vm_pmap);

	printf("#define\tPMAP_ACTIVE_ON %d\n", &pmap->active_on);
	printf("#define\tPMAP_LOCK %d\n", &pmap->lock);
	printf("#define\tPMAP_LW_TRANS %d\n", &pmap->lw_trans);
	printf("#define\tPGSHIFT %d\n", PGSHIFT);
	printf("#define\tNVABITS %d\n", NVABITS);

#if	MACH_EMULATION
	printf("#define\tEML_DISPATCH 0x%x\n", &task->eml_dispatch);
	printf("#define\tDISP_COUNT 0x%x\n", &disp->disp_count);
	printf("#define\tDISP_VECTOR 0x%x\n", &disp->disp_vector[0]);
#endif

#if	PROFILING && PROFTYPE == 4
	{   struct tostruct *tos = (struct tostruct *)0;
	    printf("#define\tTOS_LINK %d\n", &tos->link);
	    printf("#define\tTOS_COUNT %d\n", &tos->count);
	    printf("#define\tTOS_SELFPC %d\n", &tos->selfpc);
	    printf("#define\tTOS_SIZE %d\n", sizeof(*tos));
	    printf("#define\tHASHFRACTION %d\n", HASHFRACTION);
	}
#endif /* PROFILING && PROFTYPE == 4 */

	printf("#define\tSAR_SIZE %d\n", sizeof(struct sar_data));
	printf("#define\tSAR_DEVINTR %d\n", &sar->ts_devintr);
	printf("#define\tSAR_PASSREL %d\n", &sar->ts_passrel);
	printf("#define\tSAR_SYSCALLS %d\n", &sar->ts_syscalls);

	printf("#endif /* ASSEMBLER */\n");
	return (0);
}
