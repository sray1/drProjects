	Subroutine QQ_Jacobian_Cart(Qc,nQc,nOrderR,R,H1D,AJI,Det,Rad,
     &							delCx,delCy,Nel,Iout,iPrt)
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
	Real(kind=8)	Qc        
	Dimension		Qc(2,nQc)
	Real(kind=8)	Det,R,Rad
	integer			Nel,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
	Integer			nDegR
!
	Real(kind=8)	dum,delCx,delCy,xMult,pi
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	B1Dr   
	Dimension		B1Dr(nQc)
	Real(kind=8)	H1D      	 
	Dimension		H1D(nQc)
	Real(kind=8)	AJ,     AJI   
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!-------------------------------------------------- Derivative	
	call Bernstein_IstDerivative(B1Dr,nQc,r,iOut)
!---------------------------------------
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!
	do 10 i = 1,nQc 
	H1D(i) = B1Dr(i)
   10 continue
!------------------------------------------------------
!	Jacobian
!
	delCx = 0.0
	do 30 k = 1,nQc
	delCx = delCx + H1D(k)*Qc(1,k)
   30 continue
!
	delCy = 0.0
	do 40 k = 1,nQc
	delCy = delCy + H1D(k)*Qc(2,k)
   40 continue
!
	AJ = dsqrt((delCx*delCx)+(delCy*delCy))
!
!	Determinant of Jacobian
!
	det = AJ
!--------------------------------------------
	if(det.gt.0.0000001) go to 45
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
   45 continue
!
	AJI = 1.D0/det
!	------------------------ !Exact
!	pi = DATAN(1.D0)*4.0D0
!	AJI =  4.D0/pi/Rad	
!-------------------------------------------------- 2nd Derivative	
	call Bernstein_IstDerivative(B1Dr,nQc-1,r,iOut)
!
	do 50 i = 1,nQc 
	H2D(i) = B1Dr(i)
   50 continue
!
	del2Cx = 0.0
	do 60 k = 1,nQc
	del2Cx = del2Cx + H2D(k)*Qc(1,k)
   60 continue
!
	del2Cy = 0.0
	do 70 k = 1,nQc
	del2Cy = del2Cy + H2D(k)*Qc(2,k)
   70 continue

!
	AJ = dsqrt((del2Cx*del2Cx)+(del2Cy*del2Cy))
!
!-------------------------------------------- (T,M & B) axes
	Axes (1,1) = delCx * AJI
	Axes (1,2) = delCy * AJI
!
	Axes (3,1) = cdotxc2dot_X/cdotxc2dot
	Axes (3,2) = cdotxc2dot_Y/cdotxc2dot
!
	Axes (3,1) = BxT_X
	Axes (3,2) = BxT_Y
!
	return
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
