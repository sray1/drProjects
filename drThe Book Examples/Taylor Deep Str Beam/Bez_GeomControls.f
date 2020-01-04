	Subroutine BZ_Coords_EL1_Sco(Qc,nR,nC1,nC2,Rad,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
!	HardCoded for 53.13 deg Circle by Cubic 
!	Data obtained from MathCad solution	
!	Degree Elevate to nC
!	====================
	include 'geometry.h'
!	====================
	integer, parameter::nCs1 = 4, nCs2 = 2
	real(kind = 8)	Qc            ,QcI              ,QcO
	Dimension		Qc(nR,nC1,nC2),QcI(nR,nCs1,nCs2),QcO(nR,nC1,nC2)
	real(kind = 8)	Rad
	real(kind = 8)	xK,xK3,pi,Si,sinSi,cosSi
	integer			nR,nC1,nC2
!--------------------------------------------------- circular in xy 4 nodes: Input
!												   straight in xz 2 nodes
!												   total = 4x2 = 8
!			 y
!			 |
!			 |
!			 |   input cubic (approx. circular)
!			12-----22----32----42
!			 |                  |
!			 | -----> arch -->  |
!			 |                  | input linear
!			 |                  |
!			11-----21----31----41  --------> x
!					Plan View
!
!	nCs1				= 4
!	nCs2				= 2
!----------------------------------------------------
	Qci					= 0.D0
!	--------------------------
	b				= 253.576878282944D0
	d				= 12.6894201938144D0
!
	x1				= -7.83224910712775D-4
	x2				= 4.23607514299823D0
!
	y1				=  84.6666980122498D0
	y2				= 169.333239292437D0
!----------------------------------------------------
!	
	QcI(1,2,1)		= x1		!control 21 - x
	QcI(3,2,1)		= y1		!control 21 - z

	QcI(1,3,1)		= x2		!control 31 - x
	QcI(3,3,1)		= y2		!control 31 - z

	QcI(1,4,1)		= d			!control 41 - x
	QcI(3,4,1)		= b			!control 41 - z
!	-----------
	QcI(2,1,2)		= WIDTH		!control 12 - y

	QcI(1,2,2)		= x1		!control 22 - x
	QcI(2,2,2)		= WIDTH		!control 22 - y
	QcI(3,2,2)		= y1		!control 22 - z

	QcI(1,3,2)		= x2		!control 32 - x
	QcI(2,3,2)		= WIDTH		!control 32 - y
	QcI(3,3,2)		= y2		!control 32 - z

	QcI(1,4,2)		= d			!control 42 - x
	QcI(2,4,2)		= WIDTH		!control 42 - y
	QcI(3,4,2)		= b			!control 42 - z
!--------------------------------------------------- x & y: Elevate
!----------------------------------------------------
	Qci					= 0.D0
!--------------------------------------------------- xy: Cubic Starting
!												   xz" linear
	nCs = 4
	QcI(1,2,1)		= b-y2		!control 31 - x
	QcI(3,2,1)		= d-x2		!control 31 - z
!	
	QcI(1,3,1)		= b-y1		!control 21 - x
	QcI(3,3,1)		= d-x1		!control 21 - z
!
	QcI(1,4,1)		= b			!control 41 - x
	QcI(3,4,1)		= d			!control 41 - z
!	-----------
	QcI(2,1,2)		= WIDTH		!control 12 - y

	QcI(1,2,2)		= b-y2		!control 22 - x
	QcI(2,2,2)		= WIDTH		!control 22 - y
	QcI(3,2,2)		= d-x2		!control 22 - z

	QcI(1,3,2)		= b-y1		!control 32 - x
	QcI(2,3,2)		= WIDTH		!control 32 - y
	QcI(3,3,2)		= d-x1		!control 32 - z

	QcI(1,4,2)		= b			!control 42 - x
	QcI(2,4,2)		= WIDTH		!control 42 - y
	QcI(3,4,2)		= d			!control 42 - z
!--------------------------------------------------- xy: Cubic Starting
!												   xz" linear	
	nCs = 4
!--------------------------------------------------- x & y: Elevate
	Qc			= 0.0D0			! zero all
!------------------------------------ set control for iterative degre elevations
	nDegElev1	= nC1 - nCs1
	nDegElev2	= nC2 - nCs2
!	============================================
	if(nDegElev1 ==.0. AND. nDegElev2 == 0) then
		Qc = Qci
		return
	endif
!	============================================
	nCi1		= nCs1
	nCi2		= nCs2

	nCo1		= nCi1 + 1	
	nCo2		= nCi2 + 1
		
	do 100 i = 1,nDegElev1
	do 100 j = 1,nDegElev2
!------------------------------------ Loop
	call DegreeElevate2D(QcI,nR,nCi1,nCi2,QcO,nCo1,nCo2,iOut)
!	--------------------
	QcI			= QcO
	nCi1		= nCo1
	nCi2		= nCo2

	nCo1		= nCi1 + 1	
	nCo2		= nCi2 + 1	
  100 continue
!------------------------------------ Set
	do 200 i = 1,nR
	do 200 j = 1,nC1
	do 200 k = 1,nC2
	Qc(i,j,k)		= QcO(i,j,k)
  200 continue
!------------------------------------  	
	return
	end
