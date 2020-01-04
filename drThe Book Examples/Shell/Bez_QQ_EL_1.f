	Subroutine BZ_Coords_EL1(Qc,nR,nC,Radius,iOut)
!	Straight Problem by Line 	
!	Degree Elevate to nC
	real(kind = 8)	Qc       ,QcI       ,QcO
	Dimension		Qc(nR,nC),QcI(nR,nC),QcO(3,nC)
	real(kind = 8)	Radius
	real(kind = 8)	xK,xK3,pi,Si,sinSi,cosSi
	integer			nR,nC
!--------------------------------------------------- x & y: Straight 2Node
	nCs				= 2
!
	QcI(1,1)		= 0.D0
	QcI(2,1)		= 0.D0
	QcI(3,1)		= 0.D0
	QcI(1,2)		= 10.D0
	QcI(2,2)		= QcI(2,1)
	QcI(3,2)		= QcI(3,1)
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
