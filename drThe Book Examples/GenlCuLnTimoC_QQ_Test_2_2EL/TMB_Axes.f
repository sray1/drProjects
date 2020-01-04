	Subroutine QQ_TMB_Cart(Qc,nQc,nOrderR,R,H1D,Det,Rad,Axes,
     &										Nel,Iout,iPrt)
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
	Dimension		Qc(2,nQc),Axes(3,3)
	Real(kind=8)	Det,R,Rad
	integer			Nel,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
	Integer			nDegR
!
	Real(kind=8)	dum,delCx,delCy,de2Cx,de2Cy,xMult,pi
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	B1Dr   
	Dimension		B1Dr(nQc)
	Real(kind=8)	H1D     ,H2D     ,xNum,xDen     	 
	Dimension		H1D(nQc),H2D(nQc)
	Real(kind=8)	xDot   ,xDo2      	 
	Dimension		xDot(3),xDo2(3)
	Real(kind=8)	AT   ,AM   ,AB      	 
	Dimension		AT(3),AM(3),AB(3)
	Real(kind=8)	AJ,     AJI   
	Real(kind=8)	Qx     ,Qy     ,Qx1     ,Qy1             
	Dimension		Qx(nQc),Qy(nQc),Qx1(nQc),Qy1(nQc)
!	-------------------------------------------------------- Ist Derivative	
		call Bernstein_IstDerivative(B1Dr,nQc,r,iOut)
!	---------------------------------------
!		Derivative of H wrt r and s
!			H1D(1,*)	= delH/delr
!
		do 10 i = 1,nQc 
		H1D(i) = B1Dr(i)
   10		continue
!-------------
!//////////////////////////////////////////////:Alternate for Checking Purpose
	iOption = 1
!////////////////
	if(iOption == 0) Then
!		Jacobian
!
		delCxA = 0.0
		do 30 k = 1,nQc
		delCxA = delCxA + H1D(k)*Qc(1,k)
   30		continue
!
		delCyA = 0.0
		do 40 k = 1,nQc
		delCyA = delCyA + H1D(k)*Qc(2,k)
   40		continue
!
!		Determinant of Jacobian
!
		detA = dsqrt((delCxA*delCxA)+(delCyA*delCyA))
!--------------------------------------------
		if(detA.gt.0.0000001) go to 45
		write(Iout,1000) "Zero or Negative determinant for the Element(",
     &	Nel,")"
		stop 'det 0'
   45		continue
	endif
!----------------------------------------------------------------- T,M,B
	nQcm1 = nQc
!-------------------------------------------------- Ist Derivative	
	do 50 i = 1,nQcm1
    	Qx(i) = Qc(1,i)			
   50	Qy(i) = Qc(2,i)	
!   		
	nQcm1 = nQcm1 -1
	do 60 i = 1,nQcm1
    	Qx1(i) = nQcm1*(Qx(i+1) - Qx(i))	!Ist Derivative
   60	Qy1(i) = nQcm1*(Qy(i+1) - Qy(i))	!Ist Derivative
!	--------------
	call Bernstein(B1Dr,nQc-1,r,iOut)
!	--------------
	delCx = 0.0
	delCy = 0.0
	do 70 jj= 1,nQcm1
      delCx = delCx + B1Dr(jj)*Qx1(jj)
   70 delCy = delCy + B1Dr(jj)*Qy1(jj)
!--------------------------------------------
!
!	Determinant of Jacobian
!
	det = dsqrt((delCx*delCx)+(delCy*delCy))
!
	if(det.gt.0.0000001) go to 75
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
   75 continue
!

	xDot(1) = delCx
	xDot(2) = delCy
	xDot(3) = 0.D0
!-------------------------------------------------- 2nd Derivative	
	do 80 i = 1,nQcm1
    	Qx(i) = Qx1(i)			
   80	Qy(i) = Qy1(i)
!   			
	nQcm1 = nQcm1 -1
	do 90 i = 1,nQcm1
    	Qx1(i) = nQcm1*(Qx(i+1) - Qx(i))	!Ist Derivative
   90	Qy1(i) = nQcm1*(Qy(i+1) - Qy(i))	!Ist Derivative
!	--------------
	call Bernstein(B1Dr,nQc-2,r,iOut)
!	--------------
	de2Cx = 0.0
	de2Cy = 0.0
	do 95 jj= 1,nQcm1
      de2Cx = de2Cx + B1Dr(jj)*Qx1(jj)
   95 de2Cy = de2Cy + B1Dr(jj)*Qy1(jj)
!
	xDo2(1) = de2Cx
	xDo2(2) = de2Cy
	xDo2(3) = 0.D0
!----------------------------------------------------------------- T,M,B
!------------------------------------------ Degeneracy(T in y-dir)
	if(delCx == 0.D0) Then
		Axes(1,1) = 0.D0	! T in Y-dir
		Axes(1,2) = 1.D0
		Axes(1,3) = 0.D0
!
		Axes(2,1) =-1.D0	! M in -X-dir
		Axes(2,2) = 0.D0
		Axes(2,3) = 0.D0
!
		Axes(3,1) = 0.D0	! B in Z-dir
		Axes(3,2) = 0.D0
		Axes(3,3) = 1.D0
!		-------------------------------- Radius of Curvature
		call CrossProduct(xDot,xDo2,AB)
!		------
		xNum = dsqrt(AB(1)*AB(1)+AB(2)*AB(2)+AB(3)*AB(3))
		xDen = dsqrt(xDot(1)*xDot(1)+xDot(2)*xDot(2)+xDot(3)*xDot(3))
		xDen = xDen*xDen*xDen
!
		Rad = xDen/xNum
!		---------------
		return
	endif
!-------------------------------------------- (T,M & B) axes
	AJ	= det
	AJI = 1.D0/AJ
!
	AT(1) = xDot(1) * AJI
	AT(2) = xDot(2) * AJI
	AT(3) = 0.0D0
!
	Axes(1,1) = AT(1)
	Axes(1,2) = AT(2)
	Axes(1,3) = AT(3)
!	------------------------ B
	call CrossProduct(xDot,xDo2,AB)
!	------
	xNum = dsqrt(AB(1)*AB(1)+AB(2)*AB(2)+AB(3)*AB(3))
	xDen = dsqrt(xDot(1)*xDot(1)+xDot(2)*xDot(2)+xDot(3)*xDot(3))
	xDen = xDen*xDen*xDen
	Rad = xDen/xNum
!	---------------
	AJ	= dsqrt(AB(1)*AB(1)+AB(2)*AB(2)+AB(3)*AB(3))
	AJI = 1.D0/AJ
!
	AB(1) = AB(1) * AJI
	AB(2) = AB(2) * AJI
	AB(3) = AB(3) * AJI
!
	Axes (3,1) = AB(1)
	Axes (3,2) = AB(2)
	Axes (3,3) = AB(3)
!	------------------------ M
	call CrossProduct(AT,AB,AM)
!	------
	AJ	= dsqrt(AM(1)*AM(1)+AM(2)*AM(2)+AM(3)*AM(3))
	AJI = 1.D0/AJ
!
	AM(1) = AM(1) * AJI
	AM(2) = AM(2) * AJI
	AM(3) = AM(3) * AJI
!
	Axes (2,1) = AM(1)
	Axes (2,2) = AM(2)
	Axes (2,3) = AM(3)
!	-----------------------
	return
!
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
