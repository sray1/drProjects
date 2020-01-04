	Subroutine BZ_Coords_EL2_ARG(Qc,nR,nC,Radius,iOut)
!	HardCoded Angle for Bathe	
!	Degree Elevate to Quintic
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc       ,QcI       ,QcS      ,QcO
	Dimension		Qc(nR,nC),QcI(nR,nC),QcS(nR,4),QcO(nR,nC)
	real(kind = 8)	Radius,xLen
	real(kind = 8)	xK,pi,Si
	integer			nR,nC
!--------------------------------------------------- x & y: Linear Starting
	nCs				= 2
!	----------------------------- True 3D
!------------------------------------------------------------------ HardCoded for ARGYRIS
	QcI			= 0.D0		!zero all
!
	QcI(1,1)	= 240.0D0
	QcI(2,1)	= 240.0D0
	QcI(1,2)	= 240.0D0
	QcI(2,2)	=	0.0D0
!-------------------------------------------------------------------------- x & y: Elevate
	Qc			= 0.0D0			! zero all
!------------------------------------ Loop
	nDegElev	= nC - nCs
	nCi			= nCs
	nCo			= nCi + 1	
	do 100 i = 1,nDegElev
!
	call DegreeElevate(QcI,nR,nCi,QcO,nCo,iOut)
!
	QcI			= QcO
	nCi			= nCo
	nCo			= nCi + 1	
  100 continue
!------------------------------------ Set
	do 200 i = 1,nR
	do 200 j = 1,nC
	Qc(i,j)		= QcO(i,j)
  200 continue
!===========================================================
	Nel = 1
	call DumpIntegerVar(iNel,"Elem#",1,iOut)
	call DumpRealMatrix(Qc,nR,nC,"QC(nR,nC)",1,iOut)
!------------------------------------  	
	return
	end
