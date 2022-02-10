#include <sys/param.h>
#include <sys/buf.h>
#include <sys/map.h>
#include <sys/vm.h>
#include <sys/config.h>
#include <io/common/devdriver.h>

#include <io/dec/uba/ubavar.h>


int nulldev();

int (*pciint1[])() = { nulldev, 0 };	/* no interrupt routine for pci */
extern ispintr();
int	 (*ispint0[])()	= { ispintr, 0 } ;

extern struct driver scsidriver;
int (*scsiint0[])() = { nulldev, 0 };	/* no interrupt routine for scsi */
int (*pciint2001[])() = { nulldev, 0 };	/* no interrupt routine for pci */
extern itpsaintr();
int	 (*itpsaint0[])()	= { itpsaintr, 0 } ;

extern struct driver scsidriver;
int (*scsiint1[])() = { nulldev, 0 };	/* no interrupt routine for scsi */
extern struct driver tudriver;
int (*tuint0[])() = { nulldev, 0 };	/* no interrupt routine for tu */
int (*pciint0[])() = { nulldev, 0 };	/* no interrupt routine for pci */
int (*isaint0[])() = { nulldev, 0 };	/* no interrupt routine for isa */
extern struct driver gpcdriver;
extern gpcintr();
int	 (*gpcint0[])()	= { gpcintr, 0 } ;

extern struct driver acedriver;
extern aceintr();
int	 (*aceint0[])()	= { aceintr, 0 } ;

extern struct driver acedriver;
extern aceintr();
int	 (*aceint1[])()	= { aceintr, 0 } ;

extern struct driver lpdriver;
extern lpintr();
int	 (*lpint0[])()	= { lpintr, 0 } ;

extern struct driver fdidriver;
int (*fdiint0[])() = { nulldev, 0 };	/* no interrupt routine for fdi */
int (*ataint0[])() = { nulldev, 0 };	/* no interrupt routine for ata */
extern struct driver scsidriver;
int (*scsiint2[])() = { nulldev, 0 };	/* no interrupt routine for scsi */
int (*ataint1[])() = { nulldev, 0 };	/* no interrupt routine for ata */
extern struct driver scsidriver;
int (*scsiint3[])() = { nulldev, 0 };	/* no interrupt routine for scsi */
extern itpsaintr();
int	 (*itpsaint1[])()	= { itpsaintr, 0 } ;

extern struct driver scsidriver;
int (*scsiint4[])() = { nulldev, 0 };	/* no interrupt routine for scsi */
extern struct driver vgadriver;
int (*vgaint0[])() = { nulldev, 0 };	/* no interrupt routine for vga */
extern struct driver perdriver;
int (*perint0[])() = { nulldev, 0 };	/* no interrupt routine for per */
extern struct driver perdriver;
int (*perint1[])() = { nulldev, 0 };	/* no interrupt routine for per */

/* struct	port {	*/
/*	int	(*conf)();		/* config routine for this port */
/*};	*/





extern int pciconfl1();
extern int pciconfl2();
extern int ispconfl1();
extern int ispconfl2();
extern int itpsaconfl1();
extern int itpsaconfl2();
extern int isaconfl1();
extern int isaconfl2();
extern int ataconfl1();
extern int ataconfl2();


/* struct	bus {	*/
/*	u_long	        *bus_mbox	/* bus mail box */
/*	struct bus	*nxt_bus	/* next bus				*/
/*	struct controller *ctlr_list;	/* controllers connected to this bus */
/*	struct bus	*bus_hd;	/* pointer to bus this bus connected to */
/*	struct bus	*bus_list;	/* buses connected to this bus */
/*	int		bus_type;	/* bus type 			*/
/*	char		*bus_name;	/* bus name 			*/
/*	int		bus_num;	/* bus number			*/
/*	int		slot;		/* node or slot number		*/
/*	char		*connect_bus;	/* conected to bus name 	*/
/*	int		connect_num;	/* connected to bus number	*/
/*	int		(*confl1)();	/* Level 1 configuration routine */
/*	int		(*confl2)();	/* Level 2 configuration routine */
/*	char		*pname;		/* port name, if needed		*/
/*	struct port	*port;		/* pointer to port structure	*/
/*	int		(**intr)();	/* interrupt routine(s) for this bus  */
/*	int		alive;		/* alive indicator		*/
/*	struct bus_framework	*framework; /* Subsystem expansion routines */
/*	char		*driver_name;	/* name of controlling driver */
/*	void		*private[8];	/* Reserved for bus use		*/
/*	void		*conn_priv[8];	/* Reserved for connected bus use*/
/*	void 		*rsvd[8];	/* Reserved for future expansion */
/* };	*/


struct bus bus_list[] = {
	{ 0,0,0,0,0,0,"pci",1,1,"nexus",-1,pciconfl1,pciconfl2,"",0,pciint1,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"isp",0,6,"pci",1,ispconfl1,ispconfl2,"",0,ispint0,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"pci",2001,8,"pci",1,pciconfl1,pciconfl2,"",0,pciint2001,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"itpsa",0,9,"pci",2001,itpsaconfl1,itpsaconfl2,"",0,itpsaint0,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"pci",0,0,"nexus",-1,pciconfl1,pciconfl2,"",0,pciint0,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"isa",0,7,"pci",0,isaconfl1,isaconfl2,"",0,isaint0,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"ata",0,107,"pci",0,ataconfl1,ataconfl2,"",0,ataint0,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"ata",1,207,"pci",0,ataconfl1,ataconfl2,"",0,ataint1,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,"itpsa",1,12,"pci",0,itpsaconfl1,itpsaconfl2,"",0,itpsaint1,0,0,"",0,0,0},
	{ 0,0,0,0,0,0,(char *)0,0,0,"",0,0,0,"",0,0,0,0,(char *)0,0,0,0}
};

/* struct	controller {	*/
/*	u_long         *ctlr_mbox;	/* ctlr mailbox */
/*	struct controller *nxt_ctlr;	/* pointer to next ctlr on this bus */
/*	struct device	*dev_list;	/* devices connected to this ctlr */
/*	struct bus	*bus_hd;	/* pointer to bus for this ctlr   */
/*	struct driver	*driver;	/* pointer to driver structure for */
/*					/* this controller 		   */
/*	int		ctlr_type;	/* controller type		*/
/*	char		*ctlr_name;	/* controller name		*/
/*	int		ctlr_num;	/* controller number		*/
/*	char		*bus_name;	/* bus name			*/
/*	int		bus_num;	/* bus number connected to 	*/
/*	int		rctlr;		/* remote controller number	*/
/*					/* e.g. ci node or scsi id	*/
/*	int		slot;		/* node or slot number		*/
/*	int		alive;		/* alive indicator		*/
/*	char		*pname;		/* port name			*/
/*	struct port	*port;		/* port structure		*/
/*	int		(**intr)();	/* interrupt routine(s) for this ctlr */
/*	caddr_t		addr;		/* virtual address of controller */
/*	caddr_t		addr2;		/* virtual address of second ctlr */
/*					/* register space		  */
/*	int		flags;		/* flags from from config 	*/
/*	int		bus_priority;	/* bus priority from from config */
/*	int		ivnum;		/* interrupt vector number	*/
/*	int		priority;	/* system ipl level		*/
/*	int		cmd;		/* cmd for go routine		*/
/*	caddr_t		physaddr;	/* physical address of addr	*/
/*	caddr_t		physaddr2;	/* physical address of addr2	*/
/*	void 		*private[8];	/* Reserved for ctlr use	*/
/*	void 		*conn_priv[8];	/* Reserved for connected bus use*/
/*	void 		*rsvd[8];	/* reserved for future expansion */
/* };	*/




struct controller controller_list[] = {
	{ 0,0,0,0,&scsidriver,0,"scsi",0,"isp",0,0,0,0,"",0,scsiint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&scsidriver,0,"scsi",1,"itpsa",0,0,0,0,"",0,scsiint1,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&tudriver,0,"tu",0,"pci",1,0,3,0,"",0,tuint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&gpcdriver,0,"gpc",0,"isa",0,0,0,0,"",0,gpcint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&acedriver,0,"ace",0,"isa",0,0,2,0,"",0,aceint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&acedriver,0,"ace",1,"isa",0,0,3,0,"",0,aceint1,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&lpdriver,0,"lp",0,"isa",0,0,4,0,"",0,lpint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&fdidriver,0,"fdi",0,"isa",0,0,5,0,"",0,fdiint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&scsidriver,0,"scsi",2,"ata",0,0,0,0,"",0,scsiint2,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&scsidriver,0,"scsi",3,"ata",1,0,0,0,"",0,scsiint3,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&scsidriver,0,"scsi",4,"itpsa",1,0,0,0,"",0,scsiint4,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&vgadriver,0,"vga",0,"pci",0,0,13,0,"",0,vgaint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&perdriver,0,"per",0,"*",-99,0,-1,0,"",0,perint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&perdriver,0,"per",1,"*",-99,0,-1,0,"",0,perint1,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,&vgadriver,0,"vga",0,"*",-99,0,-1,0,"",0,vgaint0,0,0,0x0,0,0x0,0,0,0,0,0,0,0},
	{ 0,0,0,0,0,0,(char *)0,0,"",0,0,0,0,"",0,0,0,0,0,0,0,0,0,0,0,0,0}
};

/* struct	device_list {	*/
/*	struct device	*nxt_dev;	/* pointer to next dev on this ctlr */
/*	struct controller *ctlr_hd;	/* pointer to ctlr for this device */
/*	char		*dev_type;	/* device type			*/
/*	char		*dev_name;	/* device name			*/
/*	int		logunit;	/* logical unit	number		*/
/*	int		unit;		/* physical unit number		*/
/*	int		ctlr_num;	/* controller number for this device */
/*	char		*ctlr_name;	/* controller name connected to */
/*	int		alive;		/* alive indicator ( -1 if at   */
/*	                                /* nexus, -2 if dead, -4 if     */
/*	                                /* read only, -8 if write only )*/
/*	void		private[8];	/* reserved for device use	*/
/*	void 		conn_priv[8];	/* Reserved for connected ctlr use*/
/*	void 		rsvd[8];	/* reserved for future expansion */
/* };	*/


struct device device_list[] = {
	{ 0,0,"disk","fd",0,0,"fdi",0,0,0,0,0},
	{ 0,0,"",(char *)0,0,0,"",0,0,0,0,0}
};
