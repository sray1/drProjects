	Subroutine QQ_StrainDispMat(Qx,Qy,Wt,nQc,R,Rad,B,nB,Det,
     &								Nel,NelType,Iout)
!	Inputs
!		R			= r-directional root domain value	
!		S			= r-directional root domain value
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		B(3,nB)		= Strain Displacement Matrix
!						at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	B
	Dimension		B(3,nB)
	Real(kind=8)	Qx,     Qy     ,Wt
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc)
	Real(kind=8)	Det,R,S,RadOfCur
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum,xMult
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D     ,Axes      	 
	Dimension		H1D(nQc),Axes(3,3)
	Real(kind=8)	AJ,     AJI 
!-------------------------------------------------- Geometric Props	  
	call RatGeometryProps(Qx,Qy,Wt,nQc,R,Det,RadOfCur,Axes,Nel,Iout)
	call Rat_TMB_Cart(Qx,Qy,Wt,nQc,3,R,Det,Axes,
     &								Nel,Iout,iPrt)
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
	call Bernstein_IstDerivative(H1D,nQc,r,iOut)
!--------------------------------------------------
!	Strain displacement Matrix
!	w:		j=1,5
!	u:		j=6,10
!	theta:	j=11,15
!----------------------------------- Actual
!	pi		= DATAN(1.D0)*4.0D0
!	det			= pi*RadOfCur/4.D0
!	------------------------------
	AJI			= 1.D0/det
	nQ2			= nQc*2
	B = 0.0D0	!ALL
	
	do 70 j = 1,nQc	! For 1D Curve Beam with axial & shear strains 
	B(1,j)		= 0.D0					!Bending Strain		
	B(1,j+nQc)	= 0.D0
	B(1,j+nQ2)	= AJI*H1D(j)
!
	B(2,j)		= Br(j)/RadOfCur		!Axial Strain	
	B(2,j+nQc)	= AJI*H1D(j)
	B(2,j+nQ2)	= 0.D0
!
	B(3,j)		= AJI*H1D(j)			!Shear Strain	
	B(3,j+nQc)	= -Br(j)/RadOfCur
	B(3,j+nQ2)	= Br(j)
   70	continue
!
	write(iOut,1002) Nel,R,det,RadOfCur
	write(iOut,1003) (i,(Axes(i,j),j = 1,3),i=1,3)
!
!	write(*,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1002 format("Element ",I2,
     &        5X,"r = ",f10.6,2X,"det = ",f10.6,2X,"Radius = ",f10.6)
 1003 format("TMB Axes: Axes(3,3)"/(3(I5,5X,3(f10.7,1X)/)) )
 1010 format("Strain-Displacement Matrix B(3,15)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,3(5(f10.7,1X)/)))
	end
