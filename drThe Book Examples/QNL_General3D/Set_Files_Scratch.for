	Subroutine Set_Files_Scratch(nCInt)
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
      common/files/iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
      common/Scratch/iRotCur1,iRotCur2
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
!	OPEN (unit = 17, FILE ='SupportedStiffness.prt',STATUS ='REPLACE')
	nRL = 8*(2*nCInt)	!8=double precision bytes/2=rot and curvature
	OPEN (unit = 21, ACCESS ='DIRECT',RECL=nRL, STATUS ='SCRATCH')
	OPEN (unit = 22, ACCESS ='DIRECT',RECL=nRL, STATUS ='SCRATCH')
   	iFileStiff	= 17
	iRotCur1	= 21
	iRotCur2	= 22
!	================== Initialize
	iRotCur = iRotCur1
!	-------------
	return
	end
