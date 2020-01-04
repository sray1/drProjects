	Subroutine BZ_CubicXY45deg_2(Qc,nDim,nQc1,nQc2,R_In,R_Out,
     &								Thk,nElems,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc       
	Dimension		Qc(nDim,nQc1,nQc2)
	real(kind = 8)	R_In,R_Out,Thk
	integer			nDim,nQc1,nQc2
!
	real*8			zero,one3,two3,one,two,half
!
	zero		= 0.D0
	one3		= 1.D0/3.D0
	two3		= 2.D0/3.D0
	three4		= 0.75D0
	one			= 1.D0
	one4		= 0.25D0
	two			= 2.D0
	half		= 0.5D0
	root2		= dsqrt(two)
	root2Inv	= one/root2
!
	Qc			= 0.D0			! zero all

	xK			= 4.0D0*(root2-one)*one3
	Depth		= R_Out - R_In
!	--------------------------------------------------- X:Inner Radius: 1=Dim/2=i/3=j
	Qc(1,2,1)		= Depth + R_In*(one - root2Inv)
	Qc(1,2,2)		= Depth + R_In*(three4-half*xk)
	Qc(1,2,3)		= Depth + R_In*(one - half*xk)
	Qc(1,2,4)		= Depth + R_In
!	--------------------------------------------------- Y
	Qc(2,2,1)		= R_In*root2Inv
	Qc(2,2,2)		= R_In*(three4+one4*xk)
	Qc(2,2,3)		= R_In
	Qc(2,2,4)		= R_In
!	--------------------------------------------------- X:Outer Radius
	Qc(1,1,1)		= R_Out*(one - root2Inv)
	Qc(1,1,2)		= R_Out*(three4-half*xk)
	Qc(1,1,3)		= R_Out*(one - half*xk)
	Qc(1,1,4)		= R_Out
!	--------------------------------------------------- Y
	Qc(2,1,1)		= R_Out*root2Inv
	Qc(2,1,2)		= R_Out*(three4+one4*xk)
	Qc(2,1,3)		= R_Out
	Qc(2,1,4)		= R_Out
!--------------------------------------------------- Print Controls
	write(iOut,"(//2x,A9,i2/A70,f10.7/)") "Element #",2,
     & " Cartesian Coordinates:Inside Radius -> Outside Radius. xK =",xK
!
		write(iOut,1000) (Qc(1,1,j), j =1, nQc2)	! X
		write(iOut,1010) (Qc(2,1,j), j =1, nQc2)
!
		write(iOut,1020) (Qc(1,2,j), j =1, nQc2)
		write(iOut,1030) (Qc(2,2,j), j =1, nQc2)
!--------------------------------------------------- Plot Geometry


	return

 1001 format(5x,4(2x,f10.5))
!
 1000 format(2x,"Outer Radius..."/5x,4(2x,f10.5),
     &			2x,"X-coordinates")
 1010 format(5x,4(2x,f10.5),2x,"Y-coordinates")
 1020 format(2x,"Inner Radius..."/5x,4(2x,f10.5),
     &			2x,"X-coordinates")
 1030 format(5x,4(2x,f10.5),2x,"Y-coordinates")
	end
