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

#pragma ident "@(#)$RCSfile: llib-lc.c,v $ $Revision: 4.2.28.2 $ (DEC) $Date: 1998/09/14 18:29:22 $"

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * COMPONENT_NAME: (CMDPROG) Programming Utilities
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27; 10
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * llib-lc  1.2  R2/cmd/prog/lint,3.1,8943 10/16/89 10:30:32 
 */

/*NOTUSED*/
/*NOTDEFINED*/

/* Turn on reentrant to get the _r files */
#define _REENTRANT
#include <standards.h>
/* For non stdc uses, const causes trouble */
#if defined (_NONSTD_TYPES)
#define const
#endif
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#undef fileno
#include <stdlib.h>
#include <sys/types.h>
#include <a.out.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <float.h>
#include <fnmatch.h>
#include <fstab.h>
#include <ftw.h>
#include <glob.h>
#include <grp.h>
#include <limits.h>
#include <locale.h>
#include <sys/localedef.h>
#include <malloc.h>
#include <math.h>
#include <mbstr.h>
#include <mesg.h>
#include <mon.h>
#include <monetary.h>
#include <ndbm.h>
#include <sys/socket.h>
#include <net/route.h>
#include <netdb.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/if_ether.h>
#include <nl_types.h>
#include <pwd.h>
#include <regex.h>
#include <search.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <utime.h>
#include <ttyent.h>
#include <unistd.h>
#include <ustat.h>
#include <utmp.h>
#include <wordexp.h>
#include <wchar.h>
#include <sys/mbuf.h>
#include <sys/ipc.h>
#include <sys/method.h>
#include <sys/wait.h> 
#define _KERNEL /* This will for msg_wait to be defined */
#include <sys/msg.h>
#undef _KERNEL
#include <sys/procset.h> /* used by signal.h */
#include <sys/resource.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timers.h>  /* used by time.h */
#include <sys/times.h>
#include <sys/uio.h>
#include <sys/utsname.h>
/* The following 2 are added because they are referenced in the header files */
struct exception_info { long i; };
struct dli_ifnet { long i; };
/* Union wait is only defined if _BSD is set. Need for the wait3() function */
union wait { int i; }; 
sigset_t cantmasksigset;
/******** If the ctype functions are defined as macros, undef them */
#if defined (isalpha)
#undef isalpha
#endif
#if defined (isupper)
#undef isupper
#endif
#if defined (islower)
#undef islower
#endif
#if defined (isdigit)
#undef isdigit
#endif
#if defined (isxdigit)
#undef isxdigit
#endif
#if defined (isspace)
#undef isspace
#endif
#if defined (ispunct)
#undef ispunct
#endif
#if defined (isalnum)
#undef isalnum
#endif
#if defined (isprint)
#undef isprint
#endif
#if defined (isgraph)
#undef isgraph
#endif
#if defined (iscntrl)
#undef iscntrl
#endif
#if defined (toupper)
#undef toupper
#endif
#if defined (tolower)
#undef tolower
#endif
#if defined (_toupper)
#undef _toupper
#endif
#if defined (_tolower)
#undef _tolower
#endif
#if defined (isascii)
#undef isascii
#endif
#if defined (toascii)
#undef toascii
#endif

/* Variables declared in signal.h */
char *__sys_siglist[1];
int __sys_nsig;

/* ACCESS(2) */
int access(const char *f, int m) { return (m); }
/* ACCT(2) */
int acct(char *f) { return (0); }
/* ALARM(2) */
unsigned int alarm(unsigned int s) { return (s); }
unsigned int ualarm(unsigned int m, unsigned int i) { return (m); }
/* BRK(2) */
int brk(char *e) { return (0); }
void *sbrk(ssize_t i) { return NULL; }
/* CHDIR(2) */
int chdir(const char *s) { return (0); }
/* CHMOD(2) */
int chmod(const char *s, mode_t m) { return (0); }
/* CHOWN(2) */
int chown(const char *s, uid_t o, gid_t g) { return (0); }
int lchown(const char *s, uid_t o, gid_t g) { return (0); }
int fchown(int f, uid_t o, gid_t g) { return (0); }
/* CHROOT(2) */
int chroot(const char *p) { return (0); }
/* CLOSE(2) */
int close(int f) { return (f); }
/* CREAT(2) */
int creat(const char *s, mode_t m) { return (0); }
/* DUP(2) */
int dup(int f) { return (f); }
int dup2(int o, int n) { return (n); }
/* EXEC(2) */
int execl(const char *f, const char *a, ...) { return (0); }
int execv(const char *s, char * const v[]) { return (0); }
int execle(const char *f, const char *a, ...) { return (0); }
int execve(const char *f, char * const a[], char * const e[]) { return (0); }
int execlp(const char *f, const char *a, ...) { return (0); }
int execvp(const char *s, char * const v[]) { return (0); }

/* EXIT(2) */
void  exit(int s) {}
void _exit(int s) {}
int atexit(void (*function)(void)) { return 0; }
/* FCNTL(2) */
int fcntl(int f, int c, int a) { return (f); }
/* FORK(2) */
pid_t   fork(void) { return (0); }
/* FSYNC(2) */
int fsync(int f) { return (f); }
/* FTRUNCATE(2) */
int ftruncate(int f,  off_t len) { return (f); }
/* GETGROUPS(2) */
int getgroups(int n, gid_t g[]) { return (n); }
/* GETPID(2) */
pid_t   getpid(void) { return (0); }
pid_t   getpgrp(void) { return (0); }
pid_t   getppid(void) { return (0); }
/* GETUID(2) */
uid_t   getuid(void) { return (0); }
uid_t   geteuid(void) { return (0); }
gid_t   getgid(void) { return (0); }
gid_t   getegid(void) { return (0); }

/* HTONL, NTOHL, NTOHS, HTONS */
unsigned short	ntohs(unsigned short i ) { return i; }
unsigned short	htons(unsigned short i ) { return i; }
unsigned int	ntohl(unsigned int i) { return i; }
unsigned int	htonl(unsigned int i) { return i; }

/* IOCTL(2) */
int ioctl(int f, int r, ...) { return (f); }
/* KILL(2) */
int kill(pid_t i, int s) { return (i); }
/* LINK(2) */
int link(const char *a, const char *b) { return (0); }
/* LOCKF(2) */
int lockf(int f, int o, off_t n) { return (0); }
/* LSEEK(2) */
off_t   lseek(int f, off_t o, int w) { return (o); }
/* MKNOD(2) */
int mknod(const char *n, int m, dev_t d) { return (m); }
/* MOUNT(2) */
int mount(const char *s, const char *d, int r) { return (r); }
/* MSGCTL(2) */
int msgctl(int m, int c, struct msqid_ds *b) { return (m); }
/* MSGGET(2) */
int msgget(key_t k, int m) { return (m); }
/* MSGOP(2) */
int msgsnd(int q, void *p, size_t s, int f) { return (q); }
int msgrcv(int q, void *p, size_t s, long t, int f) { return (q); }
/* NICE(2) */
int nice(int i) { return (i); }
/* OPEN(2) */
int open(const char *f, int o, mode_t m) { return (o); }
/* PAUSE(2) */
int pause(void) { return (0); }
/* PIPE(2) */
int pipe(int f[2]) { return (0); }
/* PLOCK(2) */
int plock(int o) { return (o); }
/* PROFIL(2) */
void    profil(short *b, unsigned int s, void *o, unsigned int i) {}
/* PTRACE(2) */
int ptrace(long r, long p, ulong_t *a, ulong_t d) { return 0; }
/* READ(2) */
#ifdef  _NONSTD_TYPES
int read(int f, void *b, size_t n) { return (f); }
#else
ssize_t read(int f, void *b, size_t n) { return (f); }
#endif
ssize_t readv(int f, struct iovec *iov, int c) { return (f); }
/* READLINK(2) */
int     readlink(const char *p, char *b, int i) { return 0; }
/* REBOOT(2) */
void reboot(int h) { return; }
/* SEMCTL(2) */
int semctl(int i, int n, int c, ...) { return (i); }
/* SEMGET(2) */
int semget(key_t k, int n, int s) { return (n); }
/* SEMOP(2) */
int semop(int i, struct sembuf *o, size_t n) { return (i); }
/* SETGROUPS(2) */
int setgroups(int n, gid_t p[]) { return(n); }
/* SETPGRP(2) */
int setpgrp(pid_t p1, pid_t p2) { return 0; }
/* SETLOGIN(2) */
int  setlogin(char * p) { return 0; }
/* SETPGID(2) */
int setpgid(pid_t p1, pid_t p2) { return 0; }
/* SETSID(2) */
pid_t   setsid(void) { return (pid_t)0; } 
/* SETUID(2) */
int setuid(uid_t u) { return (u); }
int seteuid(uid_t u) { return (u); }
int setgid(gid_t g) { return (g); }
/* SHMCTL(2) */
int shmctl(int s, int c, struct shmid_ds *b) { return (s); }
/* SHMGET(2) */
int shmget(key_t k, size_t s, int f) { return f; }
/* SHMOP(2) */
void *shmat(int i, const void *a, int f) { return NULL; }
int shmdt(const void *a) { return (0); }
/* SIGBLOCK(2) */
int sigblock(int m) { return 0; }
/* SIGACTION(2) */
int sigaction(int sig, const struct sigaction *act, struct sigaction *oact) 
    { return 0; }
/* SIGHOLD(2) */
int sighold(int s) { return (s); }
/* SIGIGNORE(2) */
int sigignore(int s) { return 0; }
/* SIGPAUSE(2) */
int sigpause(int m) { return 0; }
/* SIGNAL(2) */
void (* signal(int s, void (*a)(int)))(int) { return (a); }
/* SIGPENDING(2) */
int sigpending(sigset_t *set) { return 0; }
/* SIGPROCMASK(2) */
int sigprocmask(int how, const sigset_t *set,sigset_t *oset) { return 0; }
/* SIGQUEUE(2) */
int sigqueue (pid_t pid, int i , const union sigval sv) { return 0; }
/* SIGRELSE(2) */
int sigrelse(int s) { return (s); }
/* SIGRETURN(2) */
int sigreturn(struct sigcontext *scp) { return 0; }
/* SIGSEND(2) */
int sigsend(idtype_t idtype, id_t id, int sig) { return sig; }
/* SIGSENDSET(2) */
int sigsendset(const procset_t *psetp, int sig) { return sig; }
/* SIGSET(2) */
void (* sigset(int s, void (*a)(int)))(int) { return (a); }
/* SIGSETMASK(2) */
int sigsetmask(int m) { return(0); }
/* SIGSTACK(2) */
int sigstack(struct sigstack *ss, struct sigstack *oss) { return(0); }
int sigaltstack(stack_t *a, stack_t *b) { return(0); }
/* SIGSUSPEND(2) */
int sigsuspend(const sigset_t *signal_mask) { return 0; }
/* SIGVEC(2) */
int sigvec(int s, struct sigvec *nv, struct sigvec *ov) { return (0); }
/* SIGWAIT(2) */
int sigwait(const sigset_t *set, int *sig) { return 0; }
/* SIGWAITINFO(2) */
int sigwaitinfo (const sigset_t *set, siginfo_t *inf) { return 0; }

/* SIGTIMEDWAIT(2) */
int sigtimedwait (const sigset_t *set, siginfo_t *inf,const struct timespec *tv) { return 0;} 
/* STAT(2) */

/* #include <sys/fcntl.h>
*  #include <sys/flock.h>
*/

int stat(const char *s, struct stat *b) { return (0); }
int fstat(int f, struct stat *b) { return (f); }
int lstat(const char *s, struct stat *b) { return (0); }

/* STIME(2) */
long    stime(long *t) { return (0); }
/* SYNC(2) */
void    sync(void) {}
/* SYMLINK (2) */
int symlink(const char *p1, const char *p2) { return 0; }
/* TCGETGRP(2) */
pid_t   tcgetpgrp(int i) { return (pid_t)0; }
int     tcsetpgrp(int i, pid_t p) { return 0; }
/* TIME */
time_t  time(time_t *t) { return (time_t)0; }
/* TIMES(2) */
clock_t times(struct tms *b) { return (clock_t)0; }
/* TRUNCATE(2) */
int truncate(const char *p, off_t l) { return 0; }
/* ULIMIT(2) */
off_t   ulimit(int c, off_t n) { return (n); }
/* UMASK(2) */
mode_t  umask(mode_t c) { return (c); }
/* UMOUNT(2) */
int umount(const char *s) { return (0); }
/* UNAME(2) */
int uname(struct utsname *n) { return (0); }
/* UNLINK(2) */
int unlink(const char *s) { return (0); }
/* USTAT(2) */
int ustat(dev_t d, struct ustat *b) { return (d); }
/* UTIME(2) */
int utime(const char *p, const struct utimbuf *t) { return (0); }
/* WAIT(2) */
pid_t   wait(int *s) { return (0); }
/* WRITE(2) */
#ifdef  _NONSTD_TYPES
int write(int f, const void *b, size_t n) { return (f); }
#else
ssize_t write(int f, const void *b, size_t n) { return n; }
#endif /* _NONSTD_TYPES */
ssize_t writev(int f, struct iovec *iov, int count) { return (f); }
/* A64L(3C) */
long    a64l(const char *s) { return (0L); }
char *  l64a(long l) { return (""); }
/* ABORT(3C) */
void    abort(void) {}
/* ABS(3C) */
int abs(int i) { return (i); }
/* ASSERT(3X) */
void __assert(char *a, char *f, int n) {}
/* BSEARCH(3C) */
void *bsearch(const void *k, const void *b, size_t n, size_t s,
              int (*c)(const void *, const void *)) { return (void *)""; }
/* CLEARENV(3) */
int clearenv(void) { return 0; }
/* CONV(3C) */
int toupper(int i) { return (i); }
int tolower(int i) { return (i); }
int _toupper(int i) { return (i); }
int _tolower(int i) { return (i); }
int toascii(int i) { return (i); }
/* CLOCK(3C) */
clock_t clock(void) { return (clock_t)0; }
/* CLOCK_GETDRIFT(2) */
int clock_getdrift(int clock_id, int *oppb) { return 0; }
/* CLOCK_GETRES(2) */
int clock_getres(int clock_id, struct timespec *res)
    { return 0; }
/* CLOCK_GETTIME(2) */
int clock_gettime(int clock_id, struct timespec *tp)
    { return 0; }
/* CLOCK_SETDRIFT(2) */
int clock_setdrift(int clock_id, const int drift, int *oppb) { return 0; }
/* CLOCK_SETTIME(2) */
int clock_settime(int clock_id, const struct timespec *tp)  { return 0; }
/* CRYPT(3C) */
char *  crypt(const char *k, const char *s) { return ""; }
void    setkey(const char *k)  {}
void    encrypt(char *b, int f){}
/* CTERMID(3S) */
char *  ctermid(char *s) { return (s); }
/* CTIME(3C) */
char *  ctime(const time_t *t) { return (""); }
char *ctime_r(const time_t *t, char *tb) { return tb; }
struct tm * localtime(const time_t *c)  { static struct tm x; return (&x); }
struct tm *localtime_r(const time_t *t, struct tm *tm) { return tm; }
struct tm * gmtime(const time_t *c) { static struct tm x; return (&x); }
struct tm *gmtime_r(const time_t *t, struct tm *tm) { return tm; }
time_t      mktime(struct tm *t) { return ((time_t) 0); }
char *      asctime(const struct tm *t) { return (""); }
char *asctime_r(const struct tm *tm, char *s) { return s; }
void        tzset(void) {}
long  timezone;
int daylight;
char *  tzname[2];
/* CTYPE(3C) */
int isalpha(int c) { return (c); }
int isupper(int c) { return (c); }
int islower(int c) { return (c); }
int isdigit(int c) { return (c); }
int isxdigit(int c) { return (c); }
int isalnum(int c) { return (c); }
int isspace(int c) { return (c); }
int ispunct(int c) { return (c); }
int isprint(int c) { return (c); }
int isgraph(int c) { return (c); }
int iscntrl(int c) { return (c); }
int isascii(int c) { return (c); }
char    _ctype[129];
/* CUSERID(3S) */
char *  cuserid(char *s) { return (s); }
/* DRAND48(3C) */
double  drand48(void) { return (0.0); }
double  erand48(unsigned short x[3]) { return (0.0); }
long    lrand48(void) { return (0L); }
long    nrand48(unsigned short x[3]) { return (0L); }
long    mrand48(void) { return (0L); }
long    jrand48(unsigned short x[3]) { return (0L); }
void    srand48(long s) {}
unsigned short *seed48(unsigned short s[3]) { return (s); }
void    lcong48(unsigned short p[7]) {}
/* DRAND48(3C) Reentrant*/
int     drand48_r(struct drand48_data *dp, double *randval) { return (0.0); }
int     erand48_r(unsigned short x[3],struct drand48_data *dp, double *randval) { return (0.0); }
int     lrand48_r(struct drand48_data *dp, long *randval) { return (0L); }
int     nrand48_r(unsigned short x[3],struct drand48_data *dp, long *randval) { return (0L); }
int     mrand48_r(struct drand48_data *dp, long *randval) { return (0L); }
int     jrand48_r(unsigned short x[3],struct drand48_data *dp, long *randval) { return (0L); }
int     srand48_r(long s, struct drand48_data *dp) {}
int     seed48_r(unsigned short s[3], struct drand48_data *dp) { return 0; }
int     lcong48_r(unsigned short p[7], struct drand48_data *dp) {}
/* ECVT(3C) */
char *  ecvt(double v, int n, int *d, int *s) { return (""); }
char *  fcvt(double v, int n, int *d, int *s) { return (""); }
char *  gcvt(double v, int n, char *b) { return (b); }
/* ECVT_r(3C) */
int     ecvt_r(double v, int n, int *d, int *s, char *buf, int len) { return 0; }
int     fcvt_r(double v, int n, int *d, int *s, char *buf, int len) { return 0; }
/* END(3C) */
int end, etext, edata;
/* FCLOSE(3S) */
int fclose(FILE *f) { return (0); }
int fflush(FILE *f) { return (0); }
int fclose_unlocked(FILE *f) { return (0); }
int fflush_unlocked(FILE *f) { return (0); }
/* FERROR(3S) */
#undef feof
#undef ferror
#undef clearerr
#undef fileno
int  feof(FILE *f)      { return (0); }
int  ferror(FILE *f)    { return (0); }
void clearerr(FILE *f)  {}
int  fileno(FILE *f)    { return (0); }
/* FOPEN(3S) */
FILE *  fopen(const char *f,const char *t) { return (stdin); }
FILE *  freopen(const char *f, const char *t, FILE *s) { return (s); }
FILE *  fdopen(int f, const char *t) { return (stdin); }
/* FREAD(3S) */
#ifdef  _NONSTD_TYPES
int fread(void *b, size_t s, size_t n, FILE *f) { return 0; }
int fwrite(const void *b, size_t s, size_t n, FILE *f) { return 0; }
#else
size_t  fread(void *b, size_t s, size_t n, FILE *f) { return (n); }
size_t  fwrite(const void *b, size_t s, size_t n, FILE *f) { return (n); }
#endif
size_t  fread_unlocked(void *b, size_t s, size_t n, FILE *f) { return (n); }
size_t  fwrite_unlocked(const void *b, size_t s, size_t n, FILE *f) { return (n); }
/* FSEEK(3S) */
int fseek(FILE *f, long int o, int p) { return (p); }
int fseek_unlocked(FILE *f, long int o, int p) { return (p); }
long int ftell(FILE *f) { return (0L); }
void rewind(FILE *f) {}
/* FTW(3C) */
int ftw(const char *p, int (*f)(const char *, const struct stat *, int), 
        int d) { return (d); }
int nftw(const char *p, int (*f)(char *, const struct stat *, int, struct FTW), 
         int d, int fl) { return (d); }
/* GETC(3S) */
#undef getc
#undef getchar
int getc(FILE *f) { return (0); }
int getchar(void) { return (0); }
int fgetc(FILE *f) { return (0); }
int getw(FILE *f) { return (0); }
/* GETCWD(3C) */
char *  getcwd(char *b, size_t s) { return (b); }
/* GETENV(3C) */
char *  getenv(const char *n) { return (""); }
/* GETGRENT(3C) */
struct group *  fgetgrent(FILE *f) { static struct group x; return (&x); }
struct group *  getgrent(void) { static struct group x; return (&x); }
struct group *  getgrgid(gid_t g) { static struct group x; return (&x); }
struct group *  getgrnam(const char *n) { static struct group x; return (&x); }
int   setgrent(void) { return (1); }
void  endgrent(void) {}
/* GETGRENT(3C) reentrant */
int     fgetgrent_r(FILE *f, struct group *r, char *b, int l) { return 0; }
int     getgrent_r(struct group *r, char *b, int l,FILE **gr_fp) { return 0; }
int	getgrgid_r(gid_t g, struct group *r, char *b, size_t l, struct group **re)
	{ return 0; }
int	getgrnam_r(const char *n, struct group *r, char *b, size_t l, struct group **re)
	{ return 0; }
int     setgrent_r(FILE **gr_fp) { return 0; }
void    endgrent_r(FILE **gr_fp) {}
/* GETLOGIN(3C) */
char *  getlogin(void) { return (""); }
int     getlogin_r(char *n, size_t len) { return 0; }
/* GETOPT(3C) */
int getopt(int c, char * const *v, const char *o) { return (c); }
char *  optarg;
int optind;
int opterr;
int optopt;
/* GETPASS(3C) */
char *  getpass(const char *s) { return ""; }
/* GETPW(3C) */
int getpw(uid_t u, char *b) { return (u); }
/* GETPWENT(3C) */
struct passwd * getpwent(void) { static struct passwd x; return (&x); }
struct passwd * getpwuid(uid_t u) { static struct passwd x; return (&x); }
struct passwd * getpwnam(const char *n) { static struct passwd x; return (&x); }
int   putpwent(struct passwd *s, FILE *f) { return (0); }
int   setpwent(void) { return (1); }
void  endpwent(void) {}
void  setpwfile(const char *f) {}
/* GETPWENT(3C) reentrant*/
int   getpwent_r(struct passwd *r, char *b, int l,FILE **p) 
      { return 0; }
int	getpwuid_r(uid_t u, struct passwd *r, char *b, size_t l, struct passwd **re)
	{ return 0; }
int	getpwnam_r(const char *n, struct passwd *r, char *b, size_t l, struct passwd **re)
	{ return 0; }
int   setpwent_r(FILE **p) { return 0; }
void  endpwent_r(FILE **p) {}
/* GETS(3S) */
char *gets(char *s) { return (s); }
char *fgets(char *s, int n, FILE *f) { return (s); }
/* HSEARCH(3C) */
ENTRY *hsearch(ENTRY i, ACTION a) { return (&i); }
int   hcreate(size_t n) { return (0); }
void  hdestroy(void) {}
/* HSEARCH(3C) reentrant */
int   hsearch_r(ENTRY i, ACTION a, ENTRY **t, struct hsearch_data *d) { return 0; }
int   hcreate_r(size_t n, struct hsearch_data *d) { return (0); }
void  hdestroy_r(struct hsearch_data *d) {}
/* L3TOL(3C) */
void    l3tol(long *l, char *c, int n) {}
void    ltol3(char *c, long *l, int n) {}

/* LSEARCH(3C) */
#ifdef  _NONSTD_TYPES
char  *  lsearch(const void *k, void *b, size_t *n, size_t w, 
                int (*c)(const void *, const void *))   { return NULL; }
char  *  lfind(const void *k, const void *b, size_t *n, size_t w, 
              int (*c)(const void *, const void *)) { return NULL; }
#else
void  *  lsearch(const void *k, void *b, size_t *n, size_t w, 
                int (*c)(const void *, const void *))   { return NULL; }
void  *  lfind(const void *k, const void *b, size_t *n, size_t w, 
              int (*c)(const void *, const void *)) { return NULL; }
#endif /* _NONSTD_TYPES */
/* MALLOC(3C) */
char *  alloca(int s) { return ""; }
void *  malloc(size_t s) { return (void *)""; }
void    free(void *s) {}
void *  realloc(void *s, size_t n) { return (s); }
void *  calloc(size_t n, size_t e) { return (""); }
void *  valloc(size_t s) { return (void *)""; }
int     mallopt(int c, int v) { return (0); }
struct mallinfo mallinfo(void) { struct mallinfo x; return x; }
/* MEMORY(3C) */
#ifdef  _NONSTD_TYPES
char *  memccpy(void *a, const void *b, int c, size_t n) { return (a); }
char *  memchr(const void *s, int c, size_t n) { return NULL; }
char *  memcpy(void *a, const void *b, size_t n) { return (a); }
char *  memset(void *s, int c, size_t n) { return (s); }
#else
void *  memccpy(void *a, const void *b, int c, size_t n) { return (a); }
void *  memchr(const void *s, int c, size_t n) { return NULL; }
void *  memcpy(void *a, const void *b, size_t n) { return (a); }
void *  memset(void *s, int c, size_t n) { return (s); }
#endif /* _NONSTD_TYPES */
int   memcmp(const void *a, const void *b, size_t n) { return 0; }
void  *memmove(void *s1, const void *s2, size_t n) { return s1; }
/* MKTEMP(3C) */
char *  mktemp(char *t) { return (t); }
int  mkstemp(char *t) { return 0; }
/* MONITOR(3C) */
int monitor(caddr_t l, ...) { return 0; } 
int monstartup(caddr_t l, caddr_t h) { return (0); }
int moncontrol(int mode) { return 0; }
/* NANOSLEEP(2) */
int nanosleep(const struct timespec *rqtp, struct timespec *rmtp) { return 0; }
/* NLIST(3C) */
int nlist(const char *f, struct nlist *n) { return (0); }
/* PERROR(3C) */
void    perror(const char *s) {}
#if defined (errno)
#undef errno
#endif
int errno;
char *  sys_errlist[1];
int sys_nerr;
/* PLOT(3X) not in libc */
/* POPEN(3S) */
FILE *  popen(const char *c, const char *t) { return (stdin); }
int pclose(FILE *f) { return (0); }
/* PRINTF(3S) */
int printf(const char *s, ...) { return (0); }
int fprintf(FILE *f, const char *s, ...) { return (0); }
int sprintf(char *p, const char *s, ...) { return (0); }
/* PUTC(3S) */
#undef putc
#undef putchar
int putc(int c, FILE *f) { return (c); }
int putchar(int c) { return (c); }
int fputc(int c, FILE *f) { return (c); }
int putw(int w, FILE *f) { return (w); }
/* PUTENV(3C) */
int putenv(const char *s) { return (0); }
/* PUTS(3S) */
int puts(const char *s) { return (0); }
int fputs(const char *s, FILE *f) { return (0); }
/* QSORT(3C) */
void    qsort(void *b, size_t n, size_t w, int (*c)(const void *, const void *)) {}
/* RAISE(3) */
int raise(int sig) { return sig; }
/* RAND(3C) */
void    srand(unsigned int s) {}
int rand(void) { return (0); }
int rand_r(unsigned int *seedptr) { return 0; }
/* REGCMP(3X) libPW */
/* RENAME(2) LIBC */
int rename(const char *from, const char *to) { return (0); }
/* RMDIR(2) */
int     rmdir(const char *p) { return 0; }
/* SCANF(3S) */
int scanf(const char *s, ...) { return (0); }
int fscanf(FILE *f, const char *s, ...) { return (0); }
int sscanf(const char *s, const char *f, ...) { return (0); }
/* SETBUF(3S) */
void    setbuf(FILE *f, char *b) {}
int setvbuf(FILE *f, char *t, int b, size_t s)
    { return 0; }
/* SETJMP(3C) */
int   setjmp(jmp_buf e) { return (0); }
int   sigsetjmp(sigjmp_buf e, int se) { return (0); }
void  longjmp(jmp_buf e, int v) {}
void  siglongjmp(sigjmp_buf e, int v) {}
/* SETREUID(2) */
int  setreuid(uid_t u1, uid_t u2) { return 0; }
/* SLEEP(3C) */
unsigned int sleep(unsigned int n) { return (n); }
/* USLEEP(3C) */
void    usleep(unsigned int n) {}
/* SSIGNAL(3C) */
int (*ssignal(int sig, int (*fn)(int)))(int) { return 0; }
int (* ssignal_r(int s, int (*a)(int), int (*sigs[])(int)))(int) { return 0; }
int gsignal(int s) { return (s); }
int gsignal_r(int s, int (*sigs[])(int)) { return (s); }
/* STDIO(3S) */
#ifndef _NIOBRW
#define _NIOBRW 16
#endif  /* _NIOBRW */
FILE    _iob[_NIOBRW];
unsigned char * _bufendtab[_NFILE];
/* STDIPC(3C) */
key_t   ftok(char *s, char i) { return ((key_t)0); }
/* STRING(3C) */
char    *strdup(const char *a) { return ""; }
int strcasecmp(const char *a, const char *b) { return (0); }
int strncasecmp(const char *a, const char *b, size_t n) { return (0); }
char *  strcat(char *a, const char *b) { return (a); }
char *  strncat(char *a, const char *b, size_t n) { return (a); }
int strcmp(const char *a, const char *b) { return (0); }
int strncmp(const char *a, const char *b, size_t n) { return (0); }
char *  strcpy(char *a, const char *b) { return (a); }
char *  strncpy(char *a, const char *b, size_t n) { return (a); }
#ifdef  _NONSTD_TYPES
int strlen(const char *s) { return (0); }
#else
size_t  strlen(const char *s) { return (0); }
#endif /*_NONSTD_TYPES*/
char *  strchr(const char *a, int b) { return (""); }
char *  strrchr(const char *a, int b) { return (""); }
char *  strpbrk(const char *a, const char *b) { return (""); }
#ifdef  _NONSTD_TYPES
int strspn(const char *a, const char *b) { return (0); }
int strcspn(const char *a, const char *b) { return (0); }
#else
size_t  strspn(const char *a, const char *b) { return (0); }
size_t  strcspn(const char *a, const char *b) { return (0); }
#endif /*_NONSTD_TYPES*/
char *  strtok(char *a, const char *b) { return (a); }
char    *strtok_r(char *a, const char *b, char **p) { return a; }
/* STRTOD(3C) */
double  strtod(const char *s, char **t) { return (0.0); }
double  atof(const char *s) { return (0.0); }
/* STRTOL(3C) */
long    strtol(const char *s, char **t, int b) { return (0L); }
long    atol(const char *s) { return (0L); }
int     atoi(const char *s) { return (0); }
/* SWAB(3C) */
void    swab(const void *f, void *t, ssize_t n) {}
/* SYSTEM(3S) */
int system(const char *s) { return (0); }
/* TIMER_CREATE(2) */
int timer_create(clockid_t clock_id, struct sigevent *evp, 
         timer_t *timer_created) { return 0; }
/* TIMER_DELETE(2) */
int timer_delete(timer_t timerid) { return 0; }
/* TIMER_getoverrun(2) */
int timer_getoverrun(timer_t timerid) { return 0; }
/* TIMER_GETTIME(2) */
int timer_gettime(timer_t timerid, struct itimerspec *value)
    { return 0; }
/* TIMER_SETTIME(2) */
int timer_settime(timer_t timerid, int flags, const struct itimerspec *value,
     struct itimerspec *ovalue) { return 0; }
/* TMPFILE(3S) */
FILE *  tmpfile(void) { return (stdin); }
/* TMPNAM(3S) */
char *  tmpnam(char *s) { return (s); }
char *  tempnam(const char *d, const char *s) { return ""; }
/* TSEARCH(3C) */
#ifdef  _NONSTD_TYPES
char *tsearch(const void *k, void **r, int (*c)(const void *, const void *)) { return NULL; }
char *tfind(const void *k, void * const *r, int (*c)(const void *, const void *)) { return NULL; }
char *tdelete(const void *k, void **r, int (*c)(const void *, const void *)) { return NULL; }
#else
void *tsearch(const void *k, void **r, int (*c)(const void *, const void *)) { return NULL; }
void *tfind(const void *k, void * const *r, int (*c)(const void *, const void *)) { return NULL; }
void *tdelete(const void *k, void **r, int (*c)(const void *, const void *)) { return NULL; }
#endif /*_NONSTD_TYPES*/
void twalk(const void *r, void (*f)(const void *, VISIT, int)) {}
/* TTYNAME(3C) */
char *  ttyname(int f) { return (""); }
int     ttyname_r(int f, char *a, size_t i) { return 0; }
int isatty(int f) { return (f); }
/* UNGETC(3S) */
int     ungetc(int c, FILE *f) { return (c); }
wint_t  ungetwc(wint_t c, FILE *f) { return (c); }
/* VPRINTF(3S) */
int vprintf(const char *s, va_list v) { return (0); }
int vfprintf(FILE *f, const char *s, va_list v) { return (0); }
int vsprintf(char *p, const char *s, va_list v) { return (0); }

/* UNDOCUMENTED (not for general use) */
int syscall(int n, int r, ...) { return (n); }
long    tell(int f) { return (0L); }
int ttyslot(void) { return (0); }
int _filbuf(FILE *f) { return (0); }
int _flsbuf(int c, FILE *f) { return (c); }
size_t confstr(int i, char *p, size_t sz) {return (size_t)0; }

char    *basename(char *path) { return (path); }
char    *dirname(char *path) { return (path); }
int     dirname_r (char *p, char *buf, int i) { return 0; }
void    endvfsent(void) {}
int fshelp(char *fsdev, char *vfsnam, int op, int mode, 
           int debuglevel, char *opflags, caddr_t opdata) { return (op); }
pid_t   getsid(pid_t p) { return p; }
char    *getwd(char *p) { return p; }
char    *getuinfo (char *name) { return (name); }
char    *getusershell (void) { return (""); }
int endusershell (void) {}
int setusershell (void) {}

int     initgroups (char *u, int agroup) { return agroup; }
int     openlog(const char *id, int l, int f) { return 0; }
int     openlog_r (const char *id, int l, int f, 
                   struct syslog_data *d) { return 0; }
void    closelog (void) {}
void    closelog_r (struct syslog_data *d) { return; }
int     putgrent (struct group *g, FILE *f) { return 0; }
int     setegid (gid_t gid) { return 0; }
int     setregid (gid_t i, gid_t j) { return i; }
int     setrgid (gid_t gid) { return 0; }
int     setruid (uid_t uid) { return 0; }

int     itrunc(double x) { return (0); }
long int labs(long int j) { return (j); }
unsigned long int strtoul(const char *np, char **ep, int b)
    { return (0UL); }
unsigned uitrunc(double x) { return (0u); }

int     bcmp(const char *b1, const char *b2, int l) { return(l); }
void    bcopy(const char *s, char *d, int l) {}
void    bzero(char *b, int l) {}
int     creadir(char *p, uid_t o, gid_t g, int m) { return(m); }
struct  div_t div(int n, int d) { struct div_t x; return x; }
struct  ldiv_t ldiv(long int n, long int d) { struct ldiv_t x; return x; }
int     ffs(int m) { return 0; }
struct  qelem {
        struct qelem *next;
        struct qelem *prev;
        char    data[1];
    };
void    insque(struct qelem *e, struct qelem *p) {}
void    remque(struct qelem *e) {}
struct lconv *localeconv(void) { return NULL; }
int     mkfifo(const char *p, mode_t m) { return (0); }
char    *nl_langinfo(nl_item i) { return (""); }
long    pathconf(const char *p, int n) { return (0L); }
long    fpathconf(int f, int n) { return (0L); }
int     psignal(unsigned sig, char *s) {}
int     random(void) { return (0); }
int     random_r (int *lp, struct random_data *rd)  { return 0; }
int     srandom(unsigned x) { return 0; }
int     srandom_r (unsigned x, struct random_data *d)  { return 0; }
char    *initstate(unsigned seed, char *state, size_t size) { return state; }
int     initstate_r (unsigned u, char *s, size_t i, char **p, 
                     struct random_data *d)  { return 0; }
char    *setstate(const char *state) { return (char *) state; }
int     setstate_r (const char *s, char **p, struct random_data *d)  { return 0; }
char    *re_comp(char *s) { return (s); }
char    *re_comp_r (char *s, REGEXD *R)  { return s; }
int     re_exec(char *p) { return (0); }
int     re_exec_r (char *s, REGEXD *R)  { return 0; }
void    longjmperror(void) {}
int     select(int nfds, fd_set *readfds, fd_set *writefds, 
           fd_set *exceptfds, struct timeval *timeout) { return 0; }
char    *setlocale(int c, const char *l) { return (""); }
int     siginterrupt(int s, int f) { return (s); }
int     sigfillset(sigset_t *s) { return (0); }
int     siginitset(sigset_t *s) { return (0); }
int     sigaddset(sigset_t *s, int n) { return(0); }
int     sigdelset(sigset_t *s, int n) { return (0); }
int     sigismember(const sigset_t *s, int n) { return (0); }
int     sigemptyset(sigset_t *s) { return (0); }
size_t  strftime(char *s, size_t m, const char *f,
                 const struct tm *t) { return (m); }
char    *strptime(const char *buf, const char *format,
                  struct tm *tm) { return ""; }
long    sysconf(int n) { return (0L); }
int     syslog(int pri, const char *f, ...) { return 0; }
int     syslog_r (int i, struct syslog_data *d, 
                  const char *fmt, ...) { return 0; }
int     setlogmask(int p) { return (p); }
int     tcb(int c, char *p) { return (c); }

u_int   inet_addr(char *cp) { return ((u_long) 0); }
u_int   inet_lnaof(struct in_addr in) { return (0); }
struct in_addr  inet_mkadr(int n, int h) { struct in_addr x; return (x); }
u_int   inet_netof(struct in_addr in) { return (0); }
u_int   inet_network(char *cp) { return ((u_long) 0); }
char    *inet_ntoa(struct in_addr in) { return (""); }

int     fgetpos(FILE *s, fpos_t *p) { return (0); }
wint_t  fgetwc(FILE *s) { return (0); }
wint_t  fputwc(wint_t c, FILE *f) { return (c); }
int     fsetpos(FILE *s, const fpos_t *p) { return (0); }

int     getdirentries(int f, caddr_t b, int s, off_t *o) { return (0); }
int     getdtablesize(void) { return (0); }
void    endttyent(void) {}
void    endttyent_r (FILE **f)  {}
int     setttyent(void) {}
int     setttyent_r (FILE **f)  { return 0; }
struct  ttyent *getttyent(void) { return ((struct ttyent *) 0); }
int     getttyent_r (struct ttyent *t, char *s, int i, FILE **f)  { return 0; }
struct  ttyent *getttynam(const char *tty) { return NULL; }
int     getttynam_r (const char *s, struct ttyent *t, char *c, int i)  { return 0; }

#ifdef getwchar /* This is sometimes defined as a macro */
#undef getwchar
#endif
wint_t  getwchar(void) { return (0); }

#ifdef        putwchar
#undef        putwchar
#endif
wint_t  putwchar(wint_t c) { return (c); }
int remove(const char *f) { return (0); }
int scandir(const char *d, struct dirent ***n, 
    int (*s)(struct dirent *), int (*dcmp)(struct dirent **, struct dirent **)) { return (0); }
int alphasort(struct dirent **d1, struct dirent **d2) { return (0); }
void setbuffer(FILE *f, char *b, int s) {}
void setlinebuf(FILE *f) {}

#if defined (catgets)
#undef  catgets
#endif
char    *catgets(nl_catd ctd, int sn, int mn, const char *d)    { return ""; }
int catclose(nl_catd catd) { return (0); }
#if defined(catgetmsg)
#undef  catgetmsg
#endif
char    *catgetmsg(nl_catd ctd, int sn, int mn, char *b, int l) { return (b); }
char    *fcatgetmsg(nl_catd ctd, int sn, int mn, char *b, int l) { return (b); }
char    *fcatgets(nl_catd ctd, int sn, int mn, char *d) { return (d); }
nl_catd catopen(const char *c, int d) { return ((nl_catd) 0); }
DBM     *dbm_open(char *f, int fg, int m) { return ((DBM *) 0); }
void    dbm_close(DBM *db) {}
long    dbm_forder(DBM *db, datum k) { return (0L); }
datum   dbm_fetch(DBM *db, datum key) { return (key); }
int     dbm_delete(DBM *db, datum k) { return (0); }
int     dbm_store(DBM *db, datum k, datum d, int r) { return (r); }
datum   dbm_firstkey(DBM *db) { datum k; return (k); }
datum   dbm_nextkey(DBM *db) { datum k; return (k); }

int     bindresvport(int n, struct sockaddr_in *s) { return (n); }
char    *ether_ntoa(struct ether_addr *e) { return (""); }
struct  ether_addr *ether_aton(char *s)  { return ((struct ether_addr *) 0); }
int     ether_hostton(char *h, struct ether_addr *e) { return(0); }
int     ether_ntohost(char *h, struct ether_addr *e) { return(0); }
void    sethostfile(char *n) {}
#undef n_name
struct netent *getnetbyaddr(int n, int t) { return((struct netent*) 0); }
int     getnetbyaddr_r (long n, int t, 
                        struct netent *e, struct netent_data *d)  { return 0; }
struct netent *getnetbyname(const char *a) { return((struct netent*) 0); }
int     getnetbyname_r (const char *s, struct netent *n, struct netent_data *d)  { return 0; }
struct rpcent *getrpcbynumber(int n) { return ((struct rpcent *) 0); }
struct rpcent *getrpcbyname(char *n) { return ((struct rpcent *) 0); }
int     rpmatch(const char *s) { return 0; }
struct servent *getservbyport(int p, const char *pr)    { return ((struct servent *) 0); }
int     getservbyport_r (int p,  const char *pr, 
                         struct servent *s, struct servent_data *d)  { return 0; }
struct servent *getservbyname(const char *n, const char *p) {return ((struct servent*) 0); }
int     getservbyname_r (const char *n,  const char *c, 
                         struct servent *s, struct servent_data *d)  { return 0; }
int setnetgrent(char *g) { return(0); }
int getnetgrent(char **m, char **n, char **d) { return (0); }
struct protoent *getprotobynumber(int n) { return ((struct protoent*) 0); }
int getprotobynumber_r (int i, struct protoent *p, struct protoent_data *d)  { return 0; }
struct protoent *getprotobyname(const char *n) { return ((struct protoent*) 0); }
int     getprotobyname_r (const char *n, 
                          struct protoent *p, struct protoent_data *d)  { return 0; }
int     herror(char *s) {}
int     rcmd(char **a, u_short r, char *l, char *ru, char *c, int *f) { return (0); }
void    fp_query(const u_char *m, FILE *f) {}
int     res_search(const char *n, int c, int t, u_char *a, int al)    { return (c); }
int     rexec(char **a, int r, char *n, char *p, char *c, int *f)
			{ return (r); }
int     mkpwunclear(char *s1, char m, char *s2) {}
int     mkpwclear(char *s1, char m, char *s2) {}

char    *mbsncat(char *s1, const char *s2, size_t n) { return (s1); }
char    *mbsncpy(char *s1, char *s2, size_t n) { return (s1); }
char    *mbsrchr(char *s, mbchar_t m) { return (s); }
int     mbstoint(char *m) { return (0); }
char    *mbschr(const char *s, const mbchar_t m) { return (""); }
char    *mbscat(char *s, char *t) { return (s); }
int     mbscmp(char *s, char *t) { return (0); }
int     wcscmp(const wchar_t *s, const wchar_t *t) { return (0); }
char    *mbscpy(char *s, char *t) { return (s); }
wchar_t *wcscpy(wchar_t *s, const wchar_t *t) { return (s); }
int     mbsncmp(char *s1, char *s2, size_t n) { return (0); }
int     wcsncmp(const wchar_t *s1, const wchar_t *s2, size_t n) { return (0); }
char    *mbspbrk(char *s, char *b) { return (""); }
size_t  mbstowcs(wchar_t *p, const char *s, size_t n)   { return (n); }
int     mbtowc(wchar_t *p, const char *s, size_t n) { return (0); }
int     mblen(const char *mbs, size_t n) { return 0; }
int     __getmbcurmax(void) { return 0; }
int    toujis(int c) { return (0); }
wchar_t *wcscat(wchar_t *s, const wchar_t *t) { return (s); }
wchar_t *wcschr(const wchar_t *s, wchar_t c) { return NULL; }
size_t  wcscspn(const wchar_t *s, const wchar_t *t) { return ((size_t) 0); }
size_t  wcslen(const wchar_t *s) { return ((size_t) 0); }
wchar_t *wcsncat(wchar_t *s, const wchar_t *t, size_t n) { return (s); }
wchar_t *wcsncpy(wchar_t *s, const wchar_t *t, size_t n) { return (s); }
wchar_t *wcspbrk(const wchar_t *s, const wchar_t *t) { return NULL; }
wchar_t *wcsrchr(const wchar_t *s, wchar_t c) { return NULL; }
size_t  wcsspn(const wchar_t *s, const wchar_t *t) { return ((size_t) 0); }
size_t  wcstombs(char *s, const wchar_t *t, size_t n)   { return (n); }
wchar_t *wcswcs(const wchar_t *s, const wchar_t *t) { return NULL; }
int     wctomb(char *s, wchar_t t) { return (0); }

int     wsprintf(char *p, const char *s) { return (0); }

char    *index(const char *s, int c) { return (""); }
char    *rindex(const char *s, int c) { return (""); }
int     strcoll(const char *a, const char *b) { return (0); }
char    *strerror(int e) { return (""); }
int     strerror_r(int i, char *s, int j) { return 0; }
char    *strstr(const char *a, const char *b) { return (""); }
size_t  strxfrm(char *a, const char *b, size_t n) { return n; }

int     exect(char *n, char *a[], char *e[]) { return (0); }
int     getpagesize(void) { return (0); }
int     killpg(int p, int s) { return (0); }
int     vfork(void) { return (0); }
int     vlimit(int l, int v) { return (0); }
pid_t   wait3(union wait *s, int o, struct rusage *r)   { return ((pid_t) 0 ); }
pid_t   waitpid(pid_t p, int *s, int o) { return (p); }

double  difftime(time_t s, time_t t) { return((double) 0 ); }

/* 
 * sys/time.h is included by time.h.
 */
int adjtime(struct timeval *t1, struct timeval *t2) { return 0; }
int getitimer(int w, struct itimerval *v) { return 0; }
int gettimeofday(struct timeval *t, struct timezone *tz)    { return (0); }
int setitimer(int w, struct itimerval *v, struct itimerval *o)  { return (0); }
int settimeofday(struct timeval *t, struct timezone *tz)    { return (0); }
int utimes(const char *p, struct timeval *t) { return 0; }

/* float.h is included indirectly by stdio.h */
unsigned   int SINFINITY;
unsigned   int DINFINITY[2];
unsigned   int SQNAN;
unsigned   int DQNAN[2];
unsigned   int SSNAN;
unsigned   int DSNAN[2];
unsigned   int read_rnd(void) { return (0u); }
unsigned   int write_rnd(unsigned rnd) { return (rnd); }

#if defined (iswalpha)
#undef iswalpha
#endif
#if defined (iswalnum)
#undef iswalnum
#endif
#if defined (iswcntrl)
#undef iswcntrl
#endif
#if defined (iswdigit)
#undef iswdigit
#endif
#if defined (iswgraph)
#undef iswgraph
#endif
#if defined (iswlower)
#undef iswlower
#endif
#if defined (iswprint)
#undef iswprint
#endif
#if defined (iswpunct)
#undef iswpunct
#endif
#if defined (iswspace)
#undef iswspace
#endif
#if defined (iswupper)
#undef iswupper
#endif
#if defined (iswxdigit)
#undef iswxdigit
#endif
#if defined (towupper)
#undef towupper
#endif
#if defined (towlower)
#undef towlower
#endif


int iswalpha (wint_t x) { return (0); }
int iswalnum (wint_t x) { return (0); }
int iswcntrl (wint_t x) { return (0); }
int iswdigit (wint_t x) { return (0); }
int iswgraph (wint_t x) { return (0); }
int iswlower (wint_t x) { return (0); }
int iswprint (wint_t x) { return (0); }
int iswpunct (wint_t x) { return (0); }
int iswspace (wint_t x) { return (0); }
int iswupper (wint_t x) { return (0); }
int iswxdigit (wint_t x) { return (0); }
wint_t towupper (wint_t x) { return (wint_t) (0); }
wint_t towlower (wint_t x) { return (wint_t) (0); }
int iswctype (wint_t x, wctype_t y) { return (0); }

wctype_t wctype (char *s) { return 0; }

wint_t getwc (FILE *f) { return (0); }
wint_t getwc_unlocked (FILE *f) { return (0); }
wint_t putwc (wint_t c, FILE *f) { return (0); }

wchar_t *fgetws (wchar_t *s, int x, FILE *f) { return (s); }
int fputws (const wchar_t *s, FILE *f) { return (0); }

double wcstod (const wchar_t *c, wchar_t **s) { return 0.0; }
long wcstol (const wchar_t *c, wchar_t **s, int x) { return  0L; }
unsigned long wcstoul (const wchar_t *c, wchar_t **s, int x) 
    { return 0L; }
int wcscoll (const wchar_t *c, const wchar_t *s) { return 0; }
#ifdef        wcstok
#undef        wcstok
#endif
wchar_t *wcstok (wchar_t *c, const wchar_t *s) { return NULL; }
wchar_t *wcstok_r (wchar_t *c, const wchar_t *s, wchar_t **ps)  { return c; }
int wcswidth (const wchar_t *c, size_t x) { return (0); }
size_t wcsxfrm (wchar_t *c, const wchar_t *s, size_t x) { return (x); }
int wcwidth (const wchar_t c) { return (0); }
#ifdef        wcsftime
#undef        wcsftime
#endif
size_t wcsftime (wchar_t *c,  size_t x, const char *s, const struct tm *y) { return (x);  }
int    fnmatch (const char *s1, const char *s2, int x)  { return (0); }


struct _catset *__cat_get_catset(nl_catd catd, int x)
        { return (0); }
struct _msgptr *__cat_get_msgptr(struct _catset *cset, int x)
        { return (0); }

int glob (const char *c, int x, int (*e)(const char *epath, int eerrno), glob_t *z) { return(x); }
void globfree(glob_t *x) { }


_LC_charmap_t  *__lc_charmap;
_LC_collate_t  *__lc_collate;
_LC_ctype_t    *__lc_ctype;
_LC_monetary_t *__lc_monetary;
_LC_numeric_t  *__lc_numeric;
_LC_resp_t     *__lc_resp;
_LC_time_t     *__lc_time;
_LC_locale_t   *__lc_locale;

char *mbsinvalid(const char *c) { return ""; }
size_t mbslen(const char *c) { return (0); }
mbchar_t mbstomb (const char * c) { return(0); }
int mbswidth (const char *c, size_t x) { return (0); }
char *mbsadvance (const char *a) { return ""; }

method_t *std_methods;
int method_class;
int mb_cur_max;

ssize_t strfmon(char *c, size_t x, const char *d, ...) { return(0); }

int regcomp (regex_t *a, const char *c, int x) { return (x); }
int regexec (const regex_t *a, const char *c, size_t x, regmatch_t *b, int y) { return(y); }
size_t  regerror (int x, const regex_t *a, char *c, size_t y) { return(y); }
void regfree(regex_t *a) { }

int wordexp (const char *c, wordexp_t *a, int x) { return (x); }
void wordfree (wordexp_t *a) { }

/****************  Reentrant & thread support functions in libc & libc_r *************************/

int _Geterrno (void) { return 0; }
int _Seterrno (int e) { return e; }

void endhostent_r (struct hostent_data *hd)  { return; }
void endnetent_r (struct netent_data *nd)  { return; }
void endprotoent_r (struct protoent_data *pd)  { return; }
void endservent_r (struct servent_data *sd)  { return; }
int fgetpwent_r (FILE *f, struct passwd *p, char *s, int i)  { return i; }
int gethostbyaddr_r (const char *s, int i, int j, 
    struct hostent *h, struct hostent_data *d)  { return 0; }
int gethostbyname_r (const char *s, struct hostent *h, struct hostent_data *d)  { return 0; }
int gethostent_r (struct hostent *h, struct hostent_data *d)  { return 0; }
int getnetent_r (struct netent *n, struct netent_data *nd)  { return 0; }
int getprotoent_r (struct protoent *p, struct protoent_data *pd)  { return 0; }
int getservent_r (struct servent *s, struct servent_data *sd)  { return 0; }
int hostalias_r(const char *s, char *t, int i) { return 0; }
const u_char *p_rr(const u_char *s, const u_char *t, FILE *f) { return s; }
int readdir_r (DIR *d, struct dirent *de, struct dirent **re) { return 0; }
int sethostent_r (int i, struct hostent_data *hd)  { return 0; }
int setnetent_r (int i, struct netent_data *nd)  { return 0; }
int setprotoent_r (int i, struct protoent_data *pd)  { return 0; }
int setservent_r (int i, struct servent_data *sd)  { return 0; }


int  getfsent_r (struct fstab *f, char *s, int i, FILE **st) { return 0; }
int  getfsspec_r (const char *s, struct fstab *f, 
        char *t, int i , FILE **st) { return 0; }
int  getfsfile_r (const char *s, struct fstab *f, 
        char *t, int i, FILE **st) { return 0; }
int  setfsent_r (FILE **st) { return 0; }
void endfsent_r (FILE **st) { return; }
int  setlogmask_r (int m, struct syslog_data *d) { return 0; }
int  getutent_r (struct utmp **u, struct utmp_data *d) { return 0; }
int  getutid_r (struct utmp *u, struct utmp **up, 
        struct utmp_data *d) { return 0; }
int  getutline_r (struct utmp *u, struct utmp **up, 
        struct utmp_data *d) { return 0; }
int pututline_r (struct utmp *u, struct utmp_data *d) { return 0; }
void setutent_r (struct utmp_data *d) { return; }
void endutent_r (struct utmp_data *d) { return; }
char *ptsname (int x) { return ""; }
int  getsubopt (char **a, char *const *b, char **c) { return 0; }
char *realpath (const char *a, char *b) { return b; }
int	unlockpt (int i) { return i; }
int grantpt (int i) { return i; }





