	Subroutine BZ_Coords_EL2_Bat(Qc,nR,nC,Radius,iOut)
!	HardCoded Angle for Bathe	
!	Degree Elevate to Quintic
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc       ,QcI       ,QcS      ,QcO
	Dimension		Qc(nR,nC),QcI(nR,nC),QcS(nR,4),QcO(nR,nC)
	real(kind = 8)	Radius,xLen
	real(kind = 8)	xK,pi,Si
	integer			nR,nC
!--------------------------------------------------- x & y: Cubic Starting
	nCs				= 4
!	----------------------------- True 3D
!------------------------------------------------------------------ HardCoded for 3DBat
	QcI			= 0.D0		!zero all
!
	QcI(1,1)	=  7.6120467
	QcI(2,1)	= 38.2683432
	QcI(1,2)	= 12.6375171
	QcI(2,2)	= 50.4009021
	QcI(1,3)	= 24.2638514
	QcI(2,3)	= 58.5781192
	QcI(1,4)	= 29.2893213
	QcI(2,4)	= 70.7106781
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
!------------------------------------  	
	return
	end
