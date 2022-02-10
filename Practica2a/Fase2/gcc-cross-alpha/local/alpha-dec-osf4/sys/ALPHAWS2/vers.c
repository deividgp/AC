#ifdef __STDC__
#define CONST const
#else
#define CONST
#endif
CONST int  version_major      = 4;
CONST int  version_minor      = 0;
CONST char version_version[32]  = "1229";
CONST char version_release[32]  = "V4.0";
#ifdef KERNEL_UNI
CONST char version[] = "Digital UNIX [UNI] V4.0F  (Rev. 1229); Mon Apr 10 17:39:12 GMT+0500 2006 \n";
#else
CONST char version[] = "Digital UNIX V4.0F  (Rev. 1229); Mon Apr 10 17:39:12 GMT+0500 2006 \n";
#endif
CONST char copyright[] = "\
=====\n\
(c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.\n\
ALL RIGHTS RESERVED\n\
+++++\n\
Copyright (c) 1980, 1986, 1989 Regents of the University of California.\n\
All rights reserved.\n\
+++++\n\
Mach Operating System\n\
Copyright (c) 1989 Carnegie-Mellon University\n\
All rights reserved.  The CMU software License Agreement specifies\n\
the terms and conditions for use and redistribution.\n\
+++++\n\
Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved\n\
Property of Encore Computer Corporation.\n\
This software is made available solely pursuant to the terms of\n\
a software license agreement which governs its use. Unauthorized\n\
duplication, distribution or sale are strictly prohibited.\n\
=====\n\
";
