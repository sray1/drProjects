	Subroutine Rat_TMB_Cart(QxI,QyI,WtI,nQc,nOrderR,R,Det,Axes,
     &										Nel,Iout,iPrt)
!	Inputs
!		iRule		=	0: Normal
!						1: Tensor-Product Av. Knots	
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
	Real(kind=8)	QxI     ,QyI     ,WtI       
	Dimension		QxI(nQc),QyI(nQc),WtI(nQc)
	Real(kind=8)	Qx     ,Qy     ,Wt     ,Axes       
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc),Axes(3,3)
	Real(kind=8)	Det,R
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
	Real(kind=8)	Qx1     ,Qy1             
	Dimension		Qx1(nQc),Qy1(nQc)
!----------------------------------------------------------------- T,M,B
	nQcm1 = 3	! CONIC
	do 50 jj= 1,nQcm1
	Qx(jj) = QxI(jj)
	Qy(jj) = QyI(jj)
   50	Wt(jj) = WtI(jj)
!-------------------------------------------------- Ist Derivative	
	call Bernstein(Br,nQcm1,r,iOut)
!	--------------
	Cx1 = 0.0
	Cy1 = 0.0
	do 60 jj= 1,nQcm1
      Cx1 = Cx1 + Wt(jj)*Br(jj)*Qx(jj)
   60 Cy1 = Cy1 + Wt(jj)*Br(jj)*Qy(jj)
!	--------------
	Cx2 = 0.0
	Cy2 = 0.0
	do 70 jj= 1,nQcm1
      Cx2 = Cx2 + Wt(jj)*Br(jj)
   70 Cy2 = Cy2 + Wt(jj)*Br(jj)
!	--------------
	call Bernstein_IstDerivative(B1Dr,nQcm1,r,iOut)
!	--------------
	delCx1 = 0.0
	delCy1 = 0.0
	do 80 jj= 1,nQcm1
      delCx1 = delCx1 + Wt(jj)*B1Dr(jj)*Qx(jj)
   80 delCy1 = delCy1 + Wt(jj)*B1Dr(jj)*Qy(jj)
!	--------------
	delCx2 = 0.0
	delCy2 = 0.0
	do 90 jj= 1,nQcm1
      delCx2 = delCx2 + Wt(jj)*B1Dr(jj)
   90 delCy2 = delCy2 + Wt(jj)*B1Dr(jj)
!--------------------------------------------
	delCx = (delCx1*Cx2 - Cx1*delCx2)/Cx2/Cx2	
	delCy = (delCy1*Cy2 - Cy1*delCy2)/Cy2/Cy2	
!--------------------------------------------
!
!	Determinant of Jacobian
!
	det = dsqrt((delCx*delCx)+(delCy*delCy))
!
	if(det.gt.0.0000001) go to 95
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
   95 continue
!

	xDot(1) = delCx
	xDot(2) = delCy
	xDot(3) = 0.D0
!-------------------------------------------------- 2nd Derivative
	iSkip = 1
	if(iSkip == 1) Then	
		goto 200
	endif
!-------------------------
	do 100 i = 1,nQcm1
    	Qx(i) = Qx1(i)			
  100	Qy(i) = Qy1(i)
!   			
	nQcm1 = nQcm1 -1
	do 110 i = 1,nQcm1
    	Qx1(i) = nQcm1*(Qx(i+1) - Qx(i))	!Ist Derivative
  110	Qy1(i) = nQcm1*(Qy(i+1) - Qy(i))	!Ist Derivative
!	--------------
	call Bernstein(B1Dr,nQc-2,r,iOut)
!	--------------
	de2Cx = 0.0
	de2Cy = 0.0
	do 120 jj= 1,nQcm1
      de2Cx = de2Cx + B1Dr(jj)*Qx1(jj)
  120 de2Cy = de2Cy + B1Dr(jj)*Qy1(jj)
!
	xDo2(1) = de2Cx
	xDo2(2) = de2Cy
	xDo2(3) = 0.D0
!----------------------------------------------------------------- T,M,B
  200 continue
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
	if(iSkip == 1) Then	
		goto 300
!	-------------------
      endif
	call CrossProduct(xDot,xDo2,AB)
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
!----------------------- Temporary
  300 continue
	AB(1) = 0.D0
	AB(2) = 0.D0
	AB(3) = 1.D0
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
