	Subroutine BZ_Coords_EL1_Hem(Qc,nR,nC1,nC2,Rad,iConFEA,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
!	HardCoded for 53.13 deg Circle by Cubic 
!	Data obtained from MathCad solution	
!	Degree Elevate to nC
!	====================
	include 'geometry.h'
!	====================
	integer, parameter::nCs1 = 4, nCs2 = 4
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
!			14-----24----34----44
!			 |   input cubic (approx. circular)
!			13-----23----33----43
!			 |                  |
!			12-----22----32----42
!			 |                  |
!			11-----21----31----41  --------> x
!					Plan View
!=================================================== Read from ConFEA.dtb file created by NetCoon Program
	read (iConFEA)
     &	 ((QcI(1,i,j),QcI(2,i,j),QcI(3,i,j),i = 1,nC1),j = 1,nC2)
!	--------------------------------------------------------------- Print
	write (iOut,1030)
	do j = 1,nC2
		do i = 1,nC1
			write (iOut,1040) i,j,QcI(1,i,j),QcI(2,i,j),QcI(3,i,j)
		end do
	end do
!	--------------------------------------------------------------- Print end
!--------------------------------------------------- xy: Cubic Starting
!												   xz" Cubic	
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
 1030 format( 10x,"QcO(3,4,4) .. FORM NETCOONS 
     &			NOT USED. SPHERICAL SURFACE HARDCODED "/ )
 1040 format( 10x,4(5x,2i4,2x,4(2x,F10.4)/) )
	end
