	Subroutine BZ_Coords_CircumConnect(Qc,nDim,nQc1,nQc2,R_In,R_Out,
     &								Thk,iEl,nElems,iOut)
!******************************************************************************
!	NOTE: DegreElevate2D needs to be fixed before this routine can be used
!******************************************************************************	
	Implicit Real(kind=8) (a-h,o-z)
!
	integer, parameter::nCs1 = 4, nCs2 = 2
	real(kind = 8)	QcI              ,QcO
	Dimension		QcI(nDim,nCs1,nCs2),QcO(nDim,nQc1,nQc2)
	real(kind = 8)	Qc       
	Dimension		Qc(nDim,nQc1,nQc2)
	real(kind = 8)	R_In,R_Out,Thk
	integer			nDim,nQc1,nQc2
!
	real*8			zero,one3,two3,one,two
!
	zero		= 0.D0
	one3		= 1.D0/3.D0
	two3		= 2.D0/3.D0
	one			= 1.D0
	two			= 2.D0
!
	Angle		= DATAN(one)*two/nElems
!
	QcI				= 0.D0			! zero all
!	--------------------------------------------------- Circum:Inner Radius
	QcI(1,1,1)		= (dble(iEl-1)      )*R_In*Angle
	QcI(1,2,1)		= (dble(iEl-1)+ one3)*R_In*Angle
	QcI(1,3,1)		= (dble(iEl-1)+ two3)*R_In*Angle
	QcI(1,4,1)		= (dble(iEl-1)+ one )*R_In*Angle
!	--------------------------------------------------- Radial
	QcI(2,1,1)		= 0.D0
	QcI(2,2,1)		= 0.D0
	QcI(2,3,1)		= 0.D0
	QcI(2,4,1)		= 0.D0
!	--------------------------------------------------- x:Outer Radius
	QcI(1,1,nCs2)	= (dble(iEl-1)      )*(R_In+Thk)*Angle
	QcI(1,2,nCs2)	= (dble(iEl-1)+ one3)*(R_In+Thk)*Angle
	QcI(1,3,nCs2)	= (dble(iEl-1)+ two3)*(R_In+Thk)*Angle
	QcI(1,4,nCs2)	= (dble(iEl-1)+ one )*(R_In+Thk)*Angle
!	--------------------------------------------------- y
	QcI(2,1,nCs2)	= Thk
	QcI(2,2,nCs2)	= Thk
	QcI(2,3,nCs2)	= Thk
	QcI(2,4,nCs2)	= Thk
!--------------------------------------------------- circumferential: Cubic Starting
!												   radial linear	
	nCs = 4
!--------------------------------------------------- Elevate
	Qc			= 0.0D0			! zero all
!------------------------------------ set control for iterative degre elevations
	nDegElev1	= nQC1 - nCs1
	nDegElev2	= nQC2 - nCs2
!	============================================
	if(nDegElev1 ==.0. AND. nDegElev2 == 0) then
		Qc = Qci
!		--------------------------------------------------- Print
		write(iOut,"(2x,A9,i2,A30/)") "Element #",iEl,
     &                        ": Curvilinear Coordinates..."
		write(iOut,1000) (Qc(1,i,1), i =1, nQc1)
		write(iOut,1010) (Qc(1,i,2), i =1, nQc1)
		write(iOut,1020) (Qc(2,i,1), i =1, nQc1)
		write(iOut,1030) (Qc(2,i,2), i =1, nQc1)
!		--------------------------------------------------- Print End
		return
	endif
!	============================================
	nCi1		= nCs1
	nCi2		= nCs2

	nCo1		= nCi1 + 1	
	nCo2		= nCi2 + 1
		
	do 100 i = 1,nDegElev1
	do 100 j = 1,nDegElev2
!		------------------------------------ Loop
		call DegreeElevate2D(QcI,nDim,nCi1,nCi2,QcO,nCo1,nCo2,iOut)
!		--------------------
		QcI			= QcO
		nCi1		= nCo1
		nCi2		= nCo2

		nCo1		= nCi1 + 1	
		nCo2		= nCi2 + 1	
  100 continue
!------------------------------------ Set
	do 200 i = 1,nDim
	do 200 j = 1,nQc1
	do 200 k = 1,nQc2
	Qc(i,j,k)		= QcO(i,j,k)
  200 continue
!--------------------------------------------------- Print
	write(iOut,"(//2x,A9,i2,A80/)") "Element #",iEl,
     & ": Curvilinear Coordinates:Inside Radius -> Outside Radius"
	do j = 1,nQc2
		write(iOut,1001) (Qc(1,i,j), i =1, nQc1)
	end do !j
!--------------------------------------------------- Print End
	return

 1001 format(5x,4(2x,f10.5))
!
 1000 format(2x,"Circumferential Coordinates..."/5x,4(2x,f10.5),
     &			2x,"Inner Radius")
 1010 format(5x,4(2x,f10.5),2x,"Outer Radius")
 1020 format(2x,"Radial Coordinates..."/5x,4(2x,f10.5),
     &			2x,"Inner Radius")
 1030 format(5x,4(2x,f10.5),2x,"Outer Radius")
	end
