/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from;
 */

#include <unix_locks.h>
#include <sys/param.h>
#include <sys/systm.h>

#if	UNIX_LOCKS
#define	UPAR	1
#else
#define	UPAR	0
#endif

#include <sys/secdefines.h>

int	nosys();

int	memlk();
int	memunlk();
int	psx4_get_todtimer();
int	psx4_set_todtimer();
int	psx4_time_drift();
int	rt_getprio();
int	rt_setprio();
int	psx4_timer_create();
int	psx4_timer_delete();
int	psx4_sem_sleep();
int	psx4_sem_wakeup();
int	aio_init();
int	aio_transfer_old();
int	aio_transfer_done();
int	aio_done();
int	aio_transfer_cancel();
int	aio_info();
int	psx4_ipc_snd_sleep();
int	psx4_ipc_rcv_sleep();
int	psx4_ipc_wakeup_sender();
int	psx4_ipc_wakeup_receiver();
int	psx4_csem_sleep_wakeup();
int	aio_wait();
int	aioinit_lock_sleep();
int	aioinit_lock_wakeup();
int	psx4_ipc_notify();
int	psx4_sigqueue();
int	psx4_timer_overrun();
int	aio_transfer();
int	aio_group_init();
int	aio_group_info();

#if COMPAT_43
#ifdef __STDC__
#define compat(n, name, c) n, 0+c, o##name
#define pcompat(n, name, c) n, 1+c, o##name
#define upcompat(n, name, c) n, UPAR+c, o##name

#else
#define compat(n, name, c) n, 0+c, o/**/name
#define pcompat(n, name, c) n, 1+c, o/**/name
#define upcompat(n, name, c) n, UPAR+c, o/**/name

#endif

#else /* COMPAT_43 */
#define compat(n, name, c) 0, 0+c, nosys
#define pcompat(n, name, c) 0, 1+c, nosys
#define upcompat(n, name, c) 0, UPAR+c, nosys
#endif /* COMPAT_43 */

struct sysent rt_sysent[] = {
	3, 1, memlk,	{'a','0','0','0','0','0','0'},		/* 0 = memlk */
	3, 1, memunlk,	{'a','0','0','0','0','0','0'},		/* 1 = memunlk */
	2, 1, psx4_get_todtimer,	{'0','0','0','0','0','0','0'},		/* 2 = psx4_get_todtimer */
	4, 1, psx4_set_todtimer,	{'0','0','0','0','0','0','0'},		/* 3 = psx4_set_todtimer */
	3, 1, psx4_time_drift,	{'a','0','0','0','0','0','0'},		/* 4 = psx4_time_drift */
	5, 1, rt_getprio,	{'0','0','0','0','0','0','0'},		/* 5 = rt_getprio */
	6, 1, rt_setprio,	{'0','Q','a','0','0','0','0'},		/* 6 = rt_setprio */
	2, 1, psx4_timer_create,	{'0','0','0','0','0','0','0'},		/* 7 = psx4_timer_create */
	1, 1, psx4_timer_delete,	{'0','0','0','0','0','0','0'},		/* 8 = psx4_timer_delete */
	3, 3, psx4_sem_sleep,	{'0','0','0','0','0','0','0'},		/* 9 = psx4_sem_sleep */
	1, 1, psx4_sem_wakeup,	{'0','0','0','0','0','0','0'},		/* 10 = psx4_sem_wakeup */
	2, 1, aio_init,	{'0','0','0','0','0','0','0'},		/* 11 = aio_init */
	5, 1, aio_transfer_old,	{'0','0','0','0','0','0','0'},		/* 12 = aio_transfer_old */
	3, 1, aio_transfer_done,	{'0','0','0','0','0','0','0'},		/* 13 = aio_transfer_done */
	0, 1, nosys,	{'0','0','0','0','0','0','0'},		/* 14 = obsolete aio_wait_d11 */
	1, 1, aio_done,	{'0','0','0','0','0','0','0'},		/* 15 = aio_done */
	1, 1, aio_transfer_cancel,	{'0','0','0','0','0','0','0'},		/* 16 = aio_transfer_cancel */
	2, 1, aio_info,	{'0','0','0','0','0','0','0'},		/* 17 = aio_info */
	2, 3, psx4_ipc_snd_sleep,	{'0','0','0','0','0','0','0'},		/* 18 = psx4_ipc_snd_sleep */
	2, 3, psx4_ipc_rcv_sleep,	{'0','0','0','0','0','0','0'},		/* 19 = psx4_ipc_rcv_sleep */
	1, 1, psx4_ipc_wakeup_sender,	{'0','0','0','0','0','0','0'},		/* 20 = psx4_ipc_wakeup_sender */
	1, 1, psx4_ipc_wakeup_receiver,	{'0','0','0','0','0','0','0'},		/* 21 = psx4_ipc_wakeup_receiver */
	3, 3, psx4_csem_sleep_wakeup,	{'0','0','0','0','0','0','0'},		/* 22 = psx4_csem_sleep_wakeup */
	6, 3, aio_wait,	{'0','0','0','0','0','0','0'},		/* 23 = aio_wait */
	1, 1, aioinit_lock_sleep,	{'0','0','0','0','0','0','0'},		/* 24 = aioinit_lock_sleep */
	1, 1, aioinit_lock_wakeup,	{'0','0','0','0','0','0','0'},		/* 25 = aioinit_lock_wakeup */
	5, 1, psx4_ipc_notify,	{'0','0','0','0','0','0','0'},		/* 26 = psx4_ipc_notify */
	3, 1, psx4_sigqueue,	{'Q','a','3','0','0','0','0'},		/* 27 = psx4_sigqueue */
	1, 1, psx4_timer_overrun,	{'0','0','0','0','0','0','0'},		/* 28 = psx4_timer_overrun */
	5, 1, aio_transfer,	{'0','0','0','0','0','0','0'},		/* 29 = aio_transfer */
	3, 1, aio_group_init,	{'0','0','0','0','0','0','0'},		/* 30 = aio_group_init */
	0, 1, aio_group_info,	{'0','0','0','0','0','0','0'},		/* 31 = aio_group_info */
};

int	rt_nsysent = sizeof(rt_sysent) / sizeof(rt_sysent[0]);
