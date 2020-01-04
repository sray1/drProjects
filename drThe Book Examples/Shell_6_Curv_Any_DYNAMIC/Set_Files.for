	Subroutine Set_Files()
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'LogParams.h'
	include 'files.h'
!      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd
!      common/files/     iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
	OPEN(UNIT=10,
     &FILE='c:\drProjects\drThe Book Examples\
     &Shell_6_Curv_Any_DYNAMIC\Shell_Drill.dat')
	OPEN(UNIT=3,
     &FILE='c:\drProjects\drThe Book Examples\
     &Shell_6_Curv_Any_DYNAMIC\PlotDef.txt')
	OPEN(UNIT=4,
     &FILE='c:\drProjects\drThe Book Examples\
     &Shell_6_Curv_Any_DYNAMIC\PlotEnd.txt')
	OPEN(UNIT=9,FORM = 'UNFORMATTED',
     &FILE='c:\drProjects\drThe Book Examples\
     &Shell_6\NetCoon\ConFEA.dtb')
!
	Iout		= 10
	IoutDef		= 3
	IoutEnd		= 4
	IConFEA		= 9
!	-------------
	return
	end
