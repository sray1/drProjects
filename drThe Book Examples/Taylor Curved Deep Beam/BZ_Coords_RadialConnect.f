	Subroutine BZ_Coords_RadialConnect(Qc,nDim,nQc1,nQc2,R_In,R_Out,
     &								Thk,nElems,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
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
	piby2		= DATAN(one)*two
!
	Qc			= 0.D0			! zero all

!	--------------------------------------------------- Circum:Inner Radius
	Qc(1,1,1)		= 0.0D0
	Qc(1,2,1)		= one3*R_In*piby2
	Qc(1,3,1)		= two3*R_In*piby2
	Qc(1,4,1)		=      R_In*piby2
!	--------------------------------------------------- Radial
	Qc(2,1,1)		= 0.D0
	Qc(2,2,1)		= 0.D0
	Qc(2,3,1)		= 0.D0
	Qc(2,4,1)		= 0.D0
!	--------------------------------------------------- x:Outer Radius
	Qc(1,1,nQc2)	= 0.0D0
	Qc(1,2,nQc2)	= one3*(R_In+Thk)*piby2
	Qc(1,3,nQc2)	= two3*(R_In+Thk)*piby2
	Qc(1,4,nQc2)	=      (R_In+Thk)*piby2
!	--------------------------------------------------- y
	Qc(2,1,nQc2)	= Thk
	Qc(2,2,nQc2)	= Thk
	Qc(2,3,nQc2)	= Thk
	Qc(2,4,nQc2)	= Thk
!--------------------------------------------------- Print
	return
	end
