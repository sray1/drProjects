	Subroutine TMB_CuLn(Qc,nQc,nOrderR,R,Br,H1D,Det,Cur,Tor,
     &						Axes,dxbardr,Nel,Iout,iPrt)
!	Inputs
!		iRule		=	0: Normal
!						1: Tensor-Product Av. Knots	
!		Qc(1,iCol)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,iCol)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		R			= r-directional root domain value	
!		S			= r-directional root domain value
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		H(2,iCol)	= Derivative Matrix
!						at a point (R,S)
!		AJI(2,2)	= Inverse of Jacobian Matrix
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc       ,Axes       
	Dimension		Qc(3,nQc),Axes(3,3)
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
	do 40 k = 1,nQc
	delCz = delCz + H1D(k)*Qc(3,k)
   40 continue
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
	do 80 k = 1,nQc-2
	d2Qc = Qc(3,k+2) - 2.D0*Qc(3,k+1) + Qc(3,k) 
	de2Cz = de2Cz + xn*H2D(k)*d2Qc
   80 continue
!
	xDo2(1) = de2Cx
	xDo2(2) = de2Cy
	xDo2(3) = de2Cz
!-------------------------------------------------- 3rd Derivative (for torsion)
	xn = Factorial(nQc-1)/Factorial(nQc-4)
!
	call Bernstein(B1Dr,nQc-3,r,iOut)
!	--------------
	H3D	= 0.D0	! ALL
	do 51 i = 1,nQc-3 
	H3D(i) = B1Dr(i)
   51 continue
!
	de3Cx = 0.0D0
	do 61 k = 1,nQc-3
	d2Qc = Qc(1,k+3) - 3.D0*Qc(1,k+2) + 3.D0*Qc(1,k+1) - Qc(1,k) 
	de3Cx = de3Cx + xn*H3D(k)*d2Qc
   61 continue
!
	de3Cy = 0.0D0
	do 71 k = 1,nQc-3
	d2Qc = Qc(2,k+3) - 3.D0*Qc(2,k+2) + 3.D0*Qc(2,k+1) - Qc(2,k) 
	de3Cy = de3Cy + xn*H3D(k)*d2Qc
   71 continue
!
	de3Cz = 0.0D0
	do 81 k = 1,nQc-3
	d2Qc = Qc(3,k+3) - 3.D0*Qc(3,k+2) + 3.D0*Qc(3,k+1) - Qc(3,k) 
	de3Cz = de3Cz + xn*H3D(k)*d2Qc
   81 continue
!
	xDo3(1) = de3Cx
	xDo3(2) = de3Cy
	xDo3(3) = de3Cz
!-------------------------------------------- (T,M & B) axes
	AJ	= det
	AJI = 1.D0/AJ
!
	AT(1) = xDot(1) * AJI
	AT(2) = xDot(2) * AJI
	AT(3) = xDot(3) * AJI
!
	Axes(1,1) = AT(1)
	Axes(1,2) = AT(2)
	Axes(1,3) = AT(3)
!	------------------------ B
	call CrossProduct(xDot,xDo2,AB,Iout)
!	------
	AJ	= dsqrt(AB(1)*AB(1)+AB(2)*AB(2)+AB(3)*AB(3))
!----------------------------------------------------- xDot & xDo2 not lin.indep
	if(AJ ==0.D0) Then
		AB(1) = 0.D0
		AB(2) = 0.D0
		AB(3) = 0.D0
		Axes (2,1) = AB(1)
		Axes (2,2) = AB(2)
		Axes (2,3) = AB(3)
		Axes (3,1) = AB(1)
		Axes (3,2) = AB(2)
		Axes (3,3) = AB(3)
!
		return
	endif
!----------------------------------------------------- xDot & xDo2 not lin.indep:End
	AJI = 1.D0/AJ
!
	AB(1) = AB(1) * AJI
	AB(2) = AB(2) * AJI
	AB(3) = AB(3) * AJI
!
	Axes (2,1) = AB(1)
	Axes (2,2) = AB(2)
	Axes (2,3) = AB(3)
!	------------------------ M
	call CrossProduct(AB,AT,AM,Iout)
!	------
	AJ	= dsqrt(AM(1)*AM(1)+AM(2)*AM(2)+AM(3)*AM(3))
	AJI = 1.D0/AJ
!
	AM(1) = AM(1) * AJI
	AM(2) = AM(2) * AJI
	AM(3) = AM(3) * AJI
!
	Axes (3,1) = AM(1)
	Axes (3,2) = AM(2)
	Axes (3,3) = AM(3)
!	----------------------- find dxbar/dr
!	 = [t|m|b]transpose.{dx/dr  dy/dr  dz/dr}transpose
	dxbardr = Axes(1,1)*delCx + Axes(1,2)*delCy + Axes(1,3)*delCz
!	------------------------------------------------------------- Curvature & Torsion
	call CrossProduct(xDot,xDo2,AB,Iout)
!	------
	xNum = dsqrt(AB(1)*AB(1)+AB(2)*AB(2)+AB(3)*AB(3))
	xDen = dsqrt(xDot(1)*xDot(1)+xDot(2)*xDot(2)+xDot(3)*xDot(3))
	xDen = xDen*xDen*xDen
!
	Cur = xNum/xDen
!	-------------------------------- Torsion
	xDen = xNum*xNum
	xNum = AB(1)*xDo3(1)+AB(2)*xDo3(2)+AB(3)*xDo3(3)
!
	Tor = xNum/xDen
!	---------------
!
	iPrt = 0
	if(iPrt == 1) then
		call DumpStringVar("Beg:TMB_CuLn",iPrt,iOut)
		call DumpRealVar(Cur,"Cur:vature",iPrt,iOut)
		call DumpRealVar(Tor,"Tor:sion",iPrt,iOut)
		call DumpRealVar(det,"det:erminant",iPrt,iOut)
		call DumpStringVar("End:TMB_CuLn",iPrt,iOut)
	endif
	iPrt = 0
!
	return
!
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
