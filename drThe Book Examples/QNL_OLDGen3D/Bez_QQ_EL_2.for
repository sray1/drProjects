	Subroutine BZ_Coords_EL2(Qc,nR,nC,Radius,iOut)
!	First Describe 45 deg Circle by Cubic 	
!	Degree Elevate to Quartic
	real(kind = 8)	Qc       ,QcI     ,QcO
	Dimension		Qc(nR,nC),QcI(3,8),QcO(3,8)
	real(kind = 8)	Radius
	real(kind = 8)	xK,xK3,pi,Si,sinSi,cosSi
	integer			nR,nC
!--------------------------------------------------- x & y: Cubic Starting
	nCs				= 4
!	----------------------------- True 3D
	QcI(1,1)		= 5.0D0
	QcI(3,1)		= -1.25D0
	QcI(2,1)		= 8.75D0
	QcI(1,2)		= 7.5D0
	QcI(3,2)		= -2.5D0
	QcI(2,2)		= 10.0D0
	QcI(1,3)		= 10.0D0
	QcI(3,3)		= -5.0D0
	QcI(2,3)		= 10.0D0
	QcI(1,4)		= 10.0D0
	QcI(3,4)		= -10.0D0
	QcI(2,4)		= 10.0D0
!------------------------------------------------------------------------ Planar:TEST
!	QcI		= 0.D0		! ALL
!	-------------------------				
!	pi		= DATAN(1.D0)*4.0D0
!	Si		= pi/4.D0
!	sinSi	= DSIN(Si)
!	cosSi	= DCOS(Si)
!
!	call Cubic_TangentLength(Radius,Si,xK,4,iOut)
!--------------------------------------------------- x & y: Cubic Starting
!	rut2			= dsqrt(2.0D0)
!	xK3				= xK/3.D0
!
!	QcI(1,1)		= (1.D0 - 1.D0/rut2)*RADIUS
!	QcI(3,1)		= (       1.D0/rut2)*RADIUS
!	QcI(1,2)		= QcI(1,1) + (xK3*sinSi)*RADIUS
!	QcI(3,2)		= QcI(3,1) + (xK3*cosSi)*RADIUS
!	QcI(1,4)		= RADIUS
!	QcI(3,4)		= RADIUS
!	QcI(1,3)		= QcI(1,4) - xK3*RADIUS	
!	QcI(3,3)		= QcI(3,4)
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
