	Subroutine Compute_Curvature(Qc,nQc,nOrderR,R,H1D,Det,Cur,
     &						Nel,Iout,iPrt)
!	Inputs
!		iRule		=	0: Normal
!						1: Tensor-Product Av. Knots	
!		Qc(1,iCol)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,iCol)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		R			= r-directional root domain value	
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc            
	Dimension		Qc(2,nQc)
	Real(kind=8)	Det,R,Rad
	integer			Nel,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
	Integer			nDegR
!
	Real(kind=8)	dum,delCx,delCy,delCz,xMult,pi
	Real(kind=8)	    de2Cx,de2Cy,de2Cz
	Real(kind=8)	    de3Cx,de3Cy,de3Cz
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	B1Dr     ,dxbardr   
	Dimension		B1Dr(nQc)
	Real(kind=8)	H1D     ,H2D     ,H3D     	 
	Dimension		H1D(nQc),H2D(nQc),H3D(nQc)
	Real(kind=8)	xDot   ,xDo2   ,xDo3   	 
	Dimension		xDot(3),xDo2(3),xDo3(3)
	Real(kind=8)	AT   ,AM   ,AB      	 
	Dimension		AT(3),AM(3),AB(3)
	Real(kind=8)	AJ,     AJI   
!-------------------------------------------------- Temporary
!	r=0.D0
!	r=1.D0
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!-------------------------------------------------- Ist Derivative	
	call Bernstein_IstDerivative(B1Dr,nQc,r,iOut)
!---------------------------------------
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!
	do 10 i = 1,nQc 
	H1D(i) = B1Dr(i)
   10 continue
!-------------
!	Jacobian
!
	delCx = 0.0D0
	do 20 k = 1,nQc
	delCx = delCx + H1D(k)*Qc(1,k)
   20 continue
!
	delCy = 0.0D0
	do 30 k = 1,nQc
	delCy = delCy + H1D(k)*Qc(2,k)
   30 continue
!
	delCz = 0.0D0
!
	xDot(1) = delCx
	xDot(2) = delCy
	xDot(3) = delCz
!	---------------------------------------------
!	Determinant of Jacobian
!
	det = dsqrt((delCx*delCx)+(delCy*delCy)+(delCz*delCz))
!--------------------------------------------
	if(det.gt.0.0000001) go to 45
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
   45 continue
!-------------------------------------------------- 2nd Derivative	
	xn = Factorial(nQc-1)/Factorial(nQc-3)
!
	call Bernstein(B1Dr,nQc-2,r,iOut)
!	--------------
	H2D	= 0.D0	! ALL
	do 50 i = 1,nQc-2 
	H2D(i) = B1Dr(i)
   50 continue
!
	de2Cx = 0.0D0
	do 60 k = 1,nQc-2
	d2Qc = Qc(1,k+2) - 2.D0*Qc(1,k+1) + Qc(1,k) 
	de2Cx = de2Cx + xn*H2D(k)*d2Qc
   60 continue
!
	de2Cy = 0.0D0
	do 70 k = 1,nQc-2
	d2Qc = Qc(2,k+2) - 2.D0*Qc(2,k+1) + Qc(2,k) 
	de2Cy = de2Cy + xn*H2D(k)*d2Qc
   70 continue
!
	de2Cz = 0.0D0
!
	xDo2(1) = de2Cx
	xDo2(2) = de2Cy
	xDo2(3) = de2Cz
!	------------------------------------------------------------- Curvature & Torsion
	call CrossProduct(xDot,xDo2,AB,Iout)
!	------
	xNum = dsqrt(AB(1)*AB(1)+AB(2)*AB(2)+AB(3)*AB(3))
	xDen = dsqrt(xDot(1)*xDot(1)+xDot(2)*xDot(2)+xDot(3)*xDot(3))
	xDen = xDen*xDen*xDen
!
	Cur = xNum/xDen
!	---------------
	return
!
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
