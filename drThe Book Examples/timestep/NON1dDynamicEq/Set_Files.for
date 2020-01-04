	Subroutine Set_Files()
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'files.h'
!      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd
!      common/files/     iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
	OPEN(UNIT=10,
     &FILE='c:\drProjects\drThe Book Examples\
     &TimeStep\NON1DDynamicEq\NON1DDynamicEq.dat')
	OPEN(UNIT=3,
     &FILE='c:\drProjects\drThe Book Examples\
     &TimeStep\PlotDef.txt')
	OPEN(UNIT=4,
     &FILE='c:\drProjects\drThe Book Examples\
     &TimeStep\PlotEnd.txt')
!
	Iout		= 10
	IoutDef		= 3
	IoutEnd		= 4
!	-------------
	return
	end
