	Subroutine BZ_Coords_EL2(Qc,nR,nC,Radius,iOut)
	
	real(kind = 8)	Qc
	Dimension		Qc(nR,nC)
	real(kind = 8)	xLx,xLy,xLxy2,x2Ly3
	real(kind = 8)	R0,R1,R2,R3,h0,h1,h2,h3,xK
	integer			nR,nC
!
!	-----------------------------
	xK			= 4.0D0*(dsqrt(2.0D0)-1.0D0)/3.0D0
!
	Qc			= 0.0D0			! zero all
!--------------------------------------------------- x
	Qc(1,3)		= (1.0D0 - xK)*RADIUS
	Qc(1,4)		= RADIUS
!--------------------------------------------------- y
	Qc(2,2)		= xK*RADIUS
	Qc(2,3)		= RADIUS
	Qc(2,4)		= RADIUS
!-------------------------------------
	return
	end
	
