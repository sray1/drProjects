!
	Subroutine BZ_Coords_EL2(Qc,nR,nC,xLx,xUx,xLy,iGeo,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
	real(kind = 8)	Qc
	Dimension		Qc(nR,nC)
	real(kind = 8)	xLx,xUx,xLy,xLy4,x2Ly4,x3Ly4,bb,aa
	integer			nR,nC
!
	Qc			= 0.			! zero all
!
!------------------------------ 
	if(iGeo == 0) Then			!---------------------- C0
		Qc(1,2)		= xLx/4.
		Qc(1,3)		= 2.*xLx/4.
		Qc(1,4)		= 3.*xLx/4.
		Qc(1,5)		= xLx
!	------------------------------
		bb			= (xLx - xUx)/4.
		aa			= xLx - bb 
!	------------------------------ 
		Qc(1,6)		= bb
		Qc(1,7)		= bb + aa/4.
		Qc(1,8)		= bb + 2.*aa/4.
		Qc(1,9)		= bb + 3.*aa/4.
		Qc(1,10)	= bb + aa
!	------------------------------
		bb			= 2.*(xLx - xUx)/4.
		aa			= xLx - bb 
!	------------------------------ 
		Qc(1,11)	= bb
		Qc(1,12)	= bb + aa/4.
		Qc(1,13)	= bb + 2.*aa/4.
		Qc(1,14)	= bb + 3.*aa/4.
		Qc(1,15)	= bb + aa
!	------------------------------
		bb			= 3.*(xLx - xUx)/4.
		aa			= xLx - bb 
!	------------------------------ 
		Qc(1,16)	= bb
		Qc(1,17)	= bb + aa/4.
		Qc(1,18)	= bb + 2.*aa/4.
		Qc(1,19)	= bb + 3.*aa/4.
		Qc(1,20)	= bb + aa
!	-----------------------------
	bb				= (xLx - xUx)
	aa				= xLx - bb 
!	------------------------------ 
		Qc(1,21)	= bb
		Qc(1,22)	= bb + xUx/4.
		Qc(1,23)	= bb + 2.*xUx/4.
		Qc(1,24)	= bb + 3.*xUx/4.
		Qc(1,25)	= bb + xUx
	else if(iGeo == 2) Then	!---------------------- C2 todo
		Qc(1,2)		= 8.0
		Qc(1,3)		= 20.0
		Qc(1,4)		= xLx
!	------------------------------ 
		bb			= (xLx - xUx)/3.
		aa			= xLx - bb 
!	------------------------------ 
		Qc(1,5)		= bb
		Qc(1,6)		= bb + 8.0
		Qc(1,7)		= 24.0
		Qc(1,8)		= xLx
!	------------------------------
		bb			= 2.*(xLx - xUx)/3.
		aa			= xLx - bb 
!	------------------------------ 
		Qc(1,9)		= bb
		Qc(1,10)	= bb + 8.0
		Qc(1,11)	= 26.0
		Qc(1,12)	= xLx
!	-----------------------------
	bb			= (xLx - xUx)
	aa			= xLx - bb 
!	------------------------------ 
	Qc(1,13)	= bb
	Qc(1,14)	= bb + 8.0
	Qc(1,15)	= xLx - 4.0
	Qc(1,16)	= xLx
	else if(iGeo == 1) Then	!---------------------- C1 todo
		Qc(1,2)		= 8.0
		Qc(1,3)		= 56.0D0/3.0D0
		Qc(1,4)		= xLx
!	------------------------------ 
		bb			= (xLx - xUx)/3.
		aa			= xLx - bb 
!	------------------------------ 
		Qc(1,5)		= bb
		Qc(1,6)		= bb + 8.0
		Qc(1,7)		= 200.0D0/9.0D0
		Qc(1,8)		= xLx
!	------------------------------
		bb			= 2.*(xLx - xUx)/3.
		aa			= xLx - bb 
!	------------------------------ 
		Qc(1,9)		= bb
		Qc(1,10)	= bb + 8.0
		Qc(1,11)	= 232.0D0/9.0D0
		Qc(1,12)	= xLx
!	-----------------------------
	bb			= (xLx - xUx)
	aa			= xLx - bb 
!	------------------------------ 
		Qc(1,13)	= bb
		Qc(1,14)	= bb + 8.0
		Qc(1,15)	= xLx - 8.0D0/3.0D0
		Qc(1,16)	= xLx
	end if
!----------------------- Zero Twist Override
!	Qc(1,6)		= 16.0D0
!	Qc(1,7)		= 32.0D0-(32.0D0/3.0D0)
!----------------------- Zero Twist Override
!	Qc(1,10)	= 16.0D0
!	Qc(1,11)	= 32.0D0-(16.0D0/3.0D0)
!-----------------------------
!
	xLy4		= xLy/4.
	x2Ly4		= 2.*xLy4
	x3Ly4		= 3.*xLy4
!
!	Qc(2,1)		= 0.
!	Qc(2,2)		= 0.
!	Qc(2,3)		= 0.
!	Qc(2,4)		= 0
!	Qc(2,5)		= 0
!
	Qc(2,6)		= xLy4
	Qc(2,7)		= xLy4
	Qc(2,8)		= xLy4
	Qc(2,9)		= xLy4
	Qc(2,10)	= xLy4
!
	Qc(2,11)	= x2Ly4
	Qc(2,12)	= x2Ly4
	Qc(2,13)	= x2Ly4
	Qc(2,14)	= x2Ly4
	Qc(2,15)	= x2Ly4
!
	Qc(2,16)	= x3Ly4
	Qc(2,17)	= x3Ly4
	Qc(2,18)	= x3Ly4
	Qc(2,19)	= x3Ly4
	Qc(2,20)	= x3Ly4
!
	Qc(2,21)	= xLy
	Qc(2,22)	= xLy
	Qc(2,23)	= xLy
	Qc(2,24)	= xLy
	Qc(2,25)	= xLy
  100 continue
!
	return
	end
	
