	Subroutine BZ_Coords_EL1(Qc,nR,nC,xLx,xUx,xLy,
     &					xKnot0,xknot1,xKnot2,xLxTot,iGeo,iOut)
!	xLx=16/xUx=32	
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Qc
	Dimension		Qc(nR,nC)
	real(kind = 8)	xLx,xUx,xLy,xLy3,x2Ly3,aa
	real(kind = 8)	del0,del1,alf,x0,x1,x2,dx0,dx1,xm0,xm1,xm2	! for C1
	integer			nR,nC
!
	Qc			= 0.D0			! zero all
!
	del0		= xKnot1 - xKnot0
	del1		= xKnot2 - xKnot1
	alf			= del0/(del0+del1)
!	------------------------------ 
	if(iGeo == 0) Then			!---------------------- C0
		Qc(1,1)		= 0.0D0
		Qc(1,2)		= xLx/3.
		Qc(1,3)		= 2.D0*xLx/3.D0
		Qc(1,4)		= xLx
!	-----------------------------
		aa			= xLx + (xUx - xLx)/2.D0
!	-----------------------------
		Qc(1,5)		= 0.0D0
		Qc(1,6)		= aa/3.D0
		Qc(1,7)		= 2.D0*aa/3.D0
		Qc(1,8)		= aa
!	-----------------------------
		aa			= xLx + (xUx - xLx)
!	-----------------------------
		Qc(1,9)		= 0.0D0
		Qc(1,10)	= aa/3.D0
		Qc(1,11)	= 2.D0*aa/3.D0
		Qc(1,12)	= aa
!------------------------------ 
	else if(iGeo == 2) Then		!---------------------- C2
		Qc(1,2)		= 4.0
		Qc(1,3)		= 8.0
		Qc(1,4)		= xLx
!	-----------------------------
		aa			= xLx + (xUx - xLx)/3.
!	-----------------------------
		Qc(1,6)		= 6.0
		Qc(1,7)		= aa - 8.0
		Qc(1,8)		= aa
!	-----------------------------
		aa			= xLx + 2.*(xUx - xLx)/3.
!	-----------------------------
		Qc(1,10)	= 8.0
		Qc(1,11)	= aa - 8.0
		Qc(1,12)	= aa
		Qc(1,14)	= 12.0
		Qc(1,15)	= xUx - 8.0
		Qc(1,16)	= xUx
!------------------------------ 
	else if(iGeo == 1) Then		!---------------------- C1(Farin:p118)
!	------------------------------------------ data for Bessel Tangent
		x0			= 0.0D0
		x1			= xLx
		x2			= xLxTot
		dx0			= x1 - x0
		dx1			= x2 - x1
!	-------------------------- temporary
!		del0		= dx0
!		del1		= dx1
!		alf			= del0/(del0+del1)
!	--------------------------
!
		xm1			= (1.D0-alf)*(dx0/del0) + alf*(dx1/del1)
		xm0			= 2.D0* (dx0/del0) - xm1
		xm2			= 2.D0* (dx1/del1) - xm1 
!	------------------------------
		Qc(1,1)		= x0
		Qc(1,4)		= x1
		Qc(1,2)		= Qc(1,1) + (del0/3.D0)*xm0
		Qc(1,3)		= Qc(1,4) - (del0/3.D0)*xm1
!	------------------------------------------ data for Bessel Tangent
		x0			= 0.0D0
		x1			= xLx + (xUx - xLx)/2.D0
		x2			= xLxTot
		dx0			= x1 - x0
		dx1			= x2 - x1
!	-------------------------- temporary
!		del0		= dx0
!		del1		= dx1
!		alf			= del0/(del0+del1)
!	--------------------------
!
		xm1			= (1.D0-alf)*(dx0/del0) + alf*(dx1/del1)
		xm0			= 2.D0* (dx0/del0) - xm1
		xm2			= 2.D0* (dx1/del1) - xm1 
!	------------------------------
		Qc(1,5)		= x0
		Qc(1,8)		= x1
		Qc(1,6)		= Qc(1,5) + (del0/3.D0)*xm0
		Qc(1,7)		= Qc(1,8) - (del0/3.D0)*xm1
!	------------------------------------------ data for Bessel Tangent
		x0			= 0.0D0
		x1			= xUx
		x2			= xLxTot
		dx0			= x1 - x0
		dx1			= x2 - x1
!	-------------------------- temporary
!		del0		= dx0
!		del1		= dx1
!		alf			= del0/(del0+del1)
!	--------------------------
!
		xm1			= (1.D0-alf)*(dx0/del0) + alf*(dx1/del1)
		xm0			= 2.D0* (dx0/del0) - xm1
		xm2			= 2.D0* (dx1/del1) - xm1 
!	------------------------------
		Qc(1,9)		= x0
		Qc(1,12)	= x1
		Qc(1,10)	= Qc(1,9) + (del0/3.D0)*xm0
		Qc(1,11)	= Qc(1,12) - (del0/3.D0)*xm1
	end if
!----------------------- Zero Twist Override
!	Qc(1,6)		= 16.0D0/3.0D0
!	Qc(1,7)		= 16.0D0
!	Qc(1,10)	= 32.0D0/3.0D0
!	Qc(1,11)	= 16.0D0
!-----------------------------
!
	xLy3		= xLy/2.
!
!	Qc(2,1)		= 0.
!	Qc(2,2)		= 0.
!	Qc(2,3)		= 0.
!	Qc(2,4)		= 0
!
	Qc(2,5)		= xLy3
	Qc(2,6)		= xLy3
	Qc(2,7)		= xLy3
	Qc(2,8)		= xLy3

!
	Qc(2,9)		= xLy
	Qc(2,10)	= xLy
	Qc(2,11)	= xLy
	Qc(2,12)	= xLy
  100 continue
!
	return
	end
	
