	Subroutine QQ_StrainDispMat(Qc,nQc,R,Rad,ThetaL,B,nB,Det,
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
	Dimension		Qc(2,nQc),B(6,nB)
	Real(kind=8)	Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum,xMult
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D           	 
	Dimension		H1D(nQc)
	Real(kind=8)	AJI   
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!-------------------------------------------------- Ist Derivative	
	call Bernstein_IstDerivative(H1D,nQc,r,iOut)
!------------------------------------------------------
!	Inverse & determinant of Jacobian
!
	det = Rad*ThetaL
!---------------------------------------- Temporary Check: for Straight Beam
!	det = 10.D0
!---------------------------------------- Temporary Check End
	AJI	= 1.D0/det
!--------------------------------------------
!	Strain displacement Matrix
!	w:		j=1,5
!	u:		j=6,10
!	theta:	j=11,15
!--------------------
	B	= 0.0D0	!ALL
	nQ0 = 0
	nQ1 = nQ0+nQc
	nQ2 = nQ1+nQc
!
	do 70 j = 1,nQc	! For 1D Curve Beam with axial & shear strains 
	B(1,j+nQ0)	= Br(j)				!u	
	B(2,j+nQ1)	= Br(j)				!v	
	B(3,j+nQ2)	= Br(j)				!theta		
	B(4,j+nQ0)	= H1D(j)*AJI		!u-primed
	B(5,j+nQ1)	= H1D(j)*AJI		!v-primed
	B(6,j+nQ2)	= H1D(j)*AJI		!theta-primed	
   70	continue
!
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) R,det,(i,(B(i,j),j = 1,nB),i=1,6)
	endif
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,15)"/
     &        "R = ",f20.16,2X,"det = ",f20.16/(I5/,6(5(f10.7,1X)/)))
	end
