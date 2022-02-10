#ifdef ASSEMBLER
#define	MACHINE_SLOT_SIZE 80
#define	MACHINE_RUNNING 12
#define	MACHINE_PANICSTR 64
#define	MACHINE_ERROR_RESTART 60
#define	P_SIG 40
#define	P_FLAG 8
#define	P_UAC 392
#define	NBPW 8
#define	RU_MINFLT 48
#define	STACK_BASE 14904
#define	PCB_BASE 14904
#define	UTHREAD_BASE 15672
#define	UTHREAD_UNIX_LOCK 16152
#define	STACK_LAYOUT_SIZE 16384
#define	PCB_REGS 72
#define	PCB_USP 8
#define	PCB_OWNEDFP 672
#define	PCB_PADDR 600
#define	PCB_FEN 40
#define	PCB_NOFAULT 680
#define	PCB_NOFAULT_BADVADDR 696
#define	PCB_NOFAULT_CAUSE 688
#define	PCB_FPREGS 336
#define	PCB_FPCR 592
#define	PCB_AST 736
#define	PCB_CURCPU_LOCK 744
#define	PCB_CURRENT_CPU 748
#define	PCB_SLOCK_COUNT 752
#define	PCB_SLOCK_HIERARCHY 756
#define	PCB_SLOCK_UNORDERED 760
#define	PCB_AT_INTR_LEVEL 764
#define	U_UPROC 624
#define	U_UTHREAD 632
#define	U_NPUTHREAD 608
#define	U_UTASK 616
#define	U_FBHANDLER 1440
#define	U_CURSIG 12
#define	U_SPTR 112
#define	U_SIG 8
#define	SD_ADDR 0
#define	SD_TIME 256
#define	MAX_SLOCK 32
#define	LI_COUNT 8
#define	LI_FLGSPL 12
#define	LI_SPLMASK 7
#define	LI_RWS	8
#define	LI_ORDERED 16
#define	LI_ORDNEXT 32
#define	LI_DOHIER 64
#define	LI_VALID 128
#define	LOCKINFO_SHIFT 4
#define	RWS_BYTE_STRIDE 64
#define	RWS_BLOCK_SIZE_SHIFT 6
#define	LS_TRIES 0
#define	LS_READS 8
#define	LS_TRMAX 16
#define	LS_MISSES 24
#define	LS_WAITMAX 40
#define	LS_WAITMIN 48
#define	LS_WAITSUM 56
#define	LOCKSTATS_SHIFT 6
#define	U_AR0 0
#define	THREAD_TASK 40
#define	THREAD_STACK 96
#define	THREAD_STATE 144
#define	TH_SWAPPED 8
#define	THREAD_PMAP 216
#define	THREAD_LW_VA 224
#define	THREAD_LW_PAGES 232
#define	THREAD_NXM_FLAGS 72
#define	NXM_IDLE 	  1
#define	PR_BASE 0
#define	PR_SIZE 8
#define	PR_OFF 16
#define	PR_SCALE 24
#define	PR_STRUCT_SIZE 32
#define	RPB_SELFREF 0
#define	RPB_EXT_VA_SIZE 52
#define	RPB_PERCPU_OFF 160
#define	RPB_SLOTSIZE 152
#define	RPB_STATE 128
#define	RPB_HALTPB 232
#define	RPB_HALTPC 240
#define	RPB_HALTPS 248
#define	RPB_HALTAL 256
#define	RPB_HALTRA 264
#define	RPB_HALTPV 272
#define	BOOTPCB_KSP 0
#define	BOOTPCB_KSP_BACKUP 32
#define	TASK_MAP 16
#define	MAP_PMAP 96
#define	PMAP_ACTIVE_ON 16
#define	PMAP_LOCK 0
#define	PMAP_LW_TRANS 32
#define	PGSHIFT 13
#define	NVABITS 43
#define	SAR_SIZE 256
#define	SAR_DEVINTR 0
#define	SAR_PASSREL 8
#define	SAR_SYSCALLS 16
#endif /* ASSEMBLER */
