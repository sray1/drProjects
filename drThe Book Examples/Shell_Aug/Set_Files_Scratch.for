	Subroutine Set_Files_Scratch()
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'SizeVar.h'
	include 'files.h'
!      common/files/iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
	include 'Scratch.h'
!      common/Scratch/iRotCur1,iRotCur2
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
!	OPEN (unit = 17, FILE ='SupportedStiffness.prt',STATUS ='REPLACE')
!	nRL = 8*(2*nCInt)	!8=double precision bytes/2=rot and curvature
!	OPEN (unit = 21, ACCESS ='DIRECT',RECL=nRL, STATUS ='SCRATCH')
!	OPEN (unit = 22, ACCESS ='DIRECT',RECL=nRL, STATUS ='SCRATCH')
!   	iFileStiff	= 17
!	iRotCur1	= 21
!	iRotCur2	= 22
!	================== Initialize
!	iRotCur = iRotCur1   C01,C02,RutAhat
!	------------------------------------------------------------ C01,C02,RutAhat
!		B = nDof2*nStifEL
!		T = nDof *nStifEL
	iRefPro1 = 21
	nRL = nSzDbl*(3+3+1)	! 8 bytes Real
	OPEN (unit = 21, ACCESS ='DIRECT',FORM ='BINARY',
     &					RECL=nRL, STATUS ='SCRATCH')
!	------------------------------------------------------------ B & T
	iRefPro2 = 22
	nRL = nSzDbl*(nDof*nStifEL + nDof2*nStifEL)	! 8 bytes Real
	OPEN (unit = 22, ACCESS ='DIRECT',FORM ='BINARY',
     &					RECL=nRL, STATUS ='SCRATCH')
!	------------------------------------------------------------ B & T: END
!	------------------------------------------------------------ Penalty/Augment/Constraint
!		Penalt	= Nint1*Nint2
!		AugMult	= Nint1*Nint2
!		OldCon	= Nint1*Nint2
	iAugTape1 = 23
	nRL = nSzDbl*(Nint1*Nint2)*3	!  bytes Real
	OPEN (unit = 23, ACCESS ='DIRECT',FORM ='BINARY',
     &					RECL=nRL, STATUS ='SCRATCH')
!
	iAugTape2 = 24
	nRL = nSzDbl*(Nint1*Nint2)*3	!  bytes Real
	OPEN (unit = 24, ACCESS ='DIRECT',FORM ='BINARY',
     &					RECL=nRL, STATUS ='SCRATCH')
!	------------------------------------------------------------ temp Constraint
!		Penalt	= Nint1*Nint2
!		AugMult	= Nint1*Nint2
!		OldCon	= Nint1*Nint2
	iOldCon = 25
	nRL = nSzDbl*(Nint1*Nint2)*3	!  bytes Real
	OPEN (unit = 25, ACCESS ='DIRECT',FORM ='BINARY',
     &					RECL=nRL, STATUS ='SCRATCH')
!	------------------------------------------------------------ AugMul/OldCon: END
	return
	end
