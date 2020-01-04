	Subroutine BZ_Coords_EL1(Qc,nR,nC,Radius,nElem,iOut)
!	First Describe 45 deg Circle by Cubic 	
!	Degree Elevate to Quartic
	real(kind = 8)	Qc       ,QcI     ,QcO
	Dimension		Qc(nR,nC),QcI(3,8),QcO(3,8)
	real(kind = 8)	Radius
	real(kind = 8)	xK,xK3,pi,Si,sinSi,cosSi
	integer			nR,nC
!--------------------------------------------------- x & y: Cubic Starting
	nCs				= 4
!-------------------------------- True 3D
!--------------------------------------------------- 1 Element
	if(nElem == 1) Then
		QcI(1,1)		=  0.D0
		QcI(2,1)		=  0.D0
		QcI(3,1)		=  0.D0
		QcI(1,2)		=  0.D0
		QcI(2,2)		=  0.D0
		QcI(3,2)		=  5.D0
		QcI(1,3)		= 10.D0
		QcI(2,3)		=  5.D0
		QcI(3,3)		= 10.D0
		QcI(1,4)		= 10.D0
		QcI(2,4)		= 10.D0
		QcI(3,4)		= 10.D0
	elseif(nElem == 2) Then
		QcI(1,1)		= 0.D0
		QcI(2,1)		= 0.D0
		QcI(3,1)		= 0.D0
		QcI(1,2)		= 0.D0
		QcI(2,2)		= 0.D0
		QcI(3,2)		= 5.D0
		QcI(1,3)		= 2.5D0
		QcI(2,3)		= 0.D0
		QcI(3,3)		= 7.5D0
		QcI(1,4)		= 5.0D0
		QcI(2,4)		= 1.25D0
		QcI(3,4)		= 8.75D0
	endif
!----------------------------------------------------------- planar: TEST
!	QcI		= 0.D0	! ALL
!	-----------------------------
!	pi		= DATAN(1.D0)*4.0D0
!	Si		= pi/4.D0
!	sinSi	= DSIN(Si)
!	cosSi	= DCOS(Si)
!
!	call Cubic_TangentLength(Radius,Si,xK,4,iOut)
!--------------------------------------------------- x & y: Cubic Starting
	rut2			= dsqrt(2.0D0)
!	xK3				= xK/3.D0
!
!	QcI(1,1)		= 0.D0
!	QcI(3,1)		= 0.D0
!	QcI(1,2)		= QcI(1,1)
!	QcI(3,2)		= QcI(3,1) + xK3*RADIUS
!	QcI(1,4)		= (1.D0 - 1.D0/rut2)*RADIUS
!	QcI(3,4)		= (       1.D0/rut2)*RADIUS
!	QcI(1,3)		= QcI(1,4) - (xK3*sinSi)*RADIUS	
!	QcI(3,3)		= QcI(3,4) - (xK3*cosSi)*RADIUS
!--------------------------------------------------- 1 Element
!	if(nElem == 1) Then
!	-----------------------------
!		xK			= 4.0D0*(rut2 -1.0D0)/3.0D0
!		QcI		= 0.D0	! ALL
!
!		QcI(1,3)		= (1.0D0 - xK)*RADIUS
!		QcI(1,4)		= RADIUS
!		QcI(3,2)		= xK*RADIUS
!		QcI(3,3)		= RADIUS
!		QcI(3,4)		= RADIUS
!	endif
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
