	Subroutine BZ_Coords_EL1(Qc,nR,nC,Radius,iOut)
!	HardCoded for 53.13 deg Circle by Cubic 	
!	Degree Elevate to Quartic
	real(kind = 8)	Qc       ,QcI     ,QcO
	Dimension		Qc(nR,nC),QcI(3,8),QcO(3,8)
	real(kind = 8)	Radius
	real(kind = 8)	xK
	integer			nR,nC
!	We Will Start from nDegStart upto nC-1
!	For now, nDegStart = 3, cubic ALWAYS	

!	-----------------------------
	nCo = nC
!--------------------------------------------------- x & y: Cubic Starting
	nCs = 4
!
	QcI				= 0.D0
	QcI(1,2)		= -.2104D0
	QcI(1,3)		= 15.08038D0
	QcI(1,4)		= 40.D0
	QcI(2,2)		= 30.99158D0
	QcI(2,3)		= 61.57322D0
	QcI(2,4)		= 80.D0
!--------------------------------------------------- x & y: Elevate
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
