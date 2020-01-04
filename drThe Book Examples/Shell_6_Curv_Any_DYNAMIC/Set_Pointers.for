	Subroutine Set_Pointers()
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
!-------------------------------------------- for Check with Quintic
	OPEN(UNIT=10,FILE='c:\The Book Examples\Gauss\det.dat')
	OPEN(UNIT=3,FILE='c:\The Book Examples\QNL_Total3D\PlotDef.txt')
	OPEN(UNIT=4,FILE='c:\The Book Examples\QNL_Total3D\PlotEnd.txt')
	OPEN (unit = 17, FILE = 'SupportedStiffness.prt',STATUS ='REPLACE')
	iFileStiff = 17
	Iout	= 10
	IoutDef	= 3
	IoutEnd	= 4
!	-------------
	return
	end
