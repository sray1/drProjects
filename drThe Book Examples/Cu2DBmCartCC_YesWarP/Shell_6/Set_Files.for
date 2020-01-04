	Subroutine Set_Files()
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'Drill.h'
	include 'LogParams.h'
	include 'files.h'
!      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd
!      common/files/     iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
	if (bDrill) then
		if(bOpt1) then		
     			OPEN(UNIT=10,
     &FILE='c:\The Book Examples\Shell_6\Shell_DrillOpt1.dat')
		else
     			OPEN(UNIT=10,
     &FILE='c:\The Book Examples\Shell_6\Shell_Drill.dat')
		endif
	else
     		OPEN(UNIT=10,
     &FILE='c:\The Book Examples\Shell_6\Shell.dat')
	endif
	OPEN(UNIT=3,FILE='c:\The Book Examples\Shell_6\PlotDef.txt')
	OPEN(UNIT=4,FILE='c:\The Book Examples\Shell_6\PlotEnd.txt')
	Iout		= 10
	IoutDef		= 3
	IoutEnd		= 4
!	-------------
	return
	end
