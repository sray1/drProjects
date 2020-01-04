	Subroutine BZ_Coords_EL1_Str_TT_D(Qc,nR,nC1,nC2,Radius,iOut)
!	Straight Problem by rectangle 	
!	Degree Elevate to nC1 and nC2
	Implicit Real(kind=8) (a-h,o-z)
	integer, parameter::nCs1 = 2, nCs2 = 2
	real(kind = 8)	Qc            ,QcI              ,QcO
	Dimension		Qc(nR,nC1,nC2),QcI(nR,nCs1,nCs2),QcO(nR,nC1,nC2)
	real(kind = 8)	Radius
	real(kind = 8)	xK,xK3,pi,Si,sinSi,cosSi
	integer			nR,nC1,nC2
!--------------------------------------------------- x & y: rectangle 4 nodes: Input
!			 y
!			 |
!			 |
!			 |   input linear
!			12-----------------22
!			 |                  |
!			 |                  |
!			 |                  | input linear
!			 |                  |
!			11-----------------21  --------> x
!
!---------------------------------------------------- x & y linear Starting
!	nCs1				= 2
!	nCs2				= 2
!	-----------------------
	Qci					= 0.D0
!
	QcI(1,2,1)		= 1.0D0				!control 21 - x

	QcI(1,2,2)		= 1.0D0				!control 22 - x
	QcI(2,2,2)		= 0.25D0			!control 22 - y

	QcI(2,1,2)		= 0.25D0			!control 12 - y
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
