	Subroutine QQ_StrainDispMat(Qc,nQc,R,Rad,B,nB,Det,
     &								Nel,NelType,Iout)
!	Inputs
!		Qc(1,nQc)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,nQc)	= Bezier Y-Coordinates
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
!		B(3,nB)		= Strain Displacement Matrix
!						at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc,     B
	Dimension		Qc(2,nQc),B(3,nB)
	Real(kind=8)	Det,R,S
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
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!------------------------------------------------------
!	Inverse & determinant of Jacobian
!
!	call QQ_Jacobian_Cart(Qc,nQc,nQc,R,H1D,AJI,Det,Rad,
!     &    	delCx,delCy,Nel,Iout,0)
	call QQ_TMB_Cart(Qc,nQc,nQc,R,H1D,Det,Rad,Axes,
     &									Nel,Iout,iPrt)
!
!--------------------------------------------
!	Strain displacement Matrix
!	w:		j=1,5
!	u:		j=6,10
!	theta:	j=11,15
!--------------------
	AJI			= 1.D0/det
	nQ2			= nQc*2
	B = 0.0D0	!ALL
	
	do 70 j = 1,nQc	! For 1D Curve Beam with axial & shear strains 
	B(1,j)		= H1D(j)*Axes(3,2)*AJI		!Bending Strain		
	B(1,j+nQc)	= H1D(j)*Axes(3,1)*AJI
	B(1,j+nQ2)	= H1D(j)*Axes(3,3)*AJI
!
	B(2,j)		= H1D(j)*Axes(1,2)*AJI		!Axial Strain	
	B(2,j+nQc)	= H1D(j)*Axes(1,1)*AJI
	B(2,j+nQ2)	= H1D(j)*Axes(1,3)*AJI
!
	B(3,j)		=-H1D(j)*Axes(2,2)*AJI		!Shear Strain	
	B(3,j+nQc)	=-H1D(j)*Axes(2,1)*AJI
	B(3,j+nQ2)	= Br(j)
   70	continue
!
!	write(*,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,15)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,3(5(f10.7,1X)/)))
	end
