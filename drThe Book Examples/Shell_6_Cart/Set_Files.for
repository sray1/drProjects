	Subroutine Set_Files()
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'LogParams.h'
	include 'files.h'
!      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd
!      common/files/     iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
	if(bOpt1) then		
     			OPEN(UNIT=10,
     &FILE='c:\The Book Examples\Shell_6_Cart\Shell_DrillOpt1.dat')
	else
     			OPEN(UNIT=10,
     &FILE='c:\The Book Examples\Shell_6_Cart\Shell_Drill.dat')
	endif
	OPEN(UNIT=3,FILE='c:\The Book Examples\Shell_6_Cart\PlotDef.txt')
	OPEN(UNIT=4,FILE='c:\The Book Examples\Shell_6_Cart\PlotEnd.txt')
	OPEN(UNIT=9,FORM = 'UNFORMATTED',
     &FILE='c:\The Book Examples\Shell_6\NetCoon\ConFEA.dtb')
	Iout		= 10
	IoutDef		= 3
	IoutEnd		= 4
	IConFEA		= 9
!	-------------
	return
	end
