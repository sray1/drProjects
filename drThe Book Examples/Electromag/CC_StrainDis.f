	Subroutine CC_StrainDispMat(R,T,B,nB,Det,Nel,NelType,Iout)
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
	Real(kind=8)	T    ,B
	Dimension		T(nB),B(nB)
	Real(kind=8)	Det,R,S
	integer			Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
	Integer			nDegR,nDegS
!
	Real(kind=8)	Br   
	Dimension		Br(4)
	Real(kind=8)	B1Dr   
	Dimension		B1Dr(4)
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.-r)*(1.-r)*(1.-r)
	Br(2) = 3.*(1.-r)*(1.-r)*r
	Br(3) = 3.*(1.-r)*r*r
	Br(4) = r*r*r
!---------------------------------------------------------	
!	Define Derivative Bernstein: delH wrt r & s
!
	dum		= 3.*r*r
	B1Dr(1) = -3.*(1.-r)*(1.-r)
	B1Dr(2) = 3*(1.-4.*r+dum)
	B1Dr(3) = 3*(2.*r-dum)
	B1Dr(4) = dum
!-----------------------------
!
!	Strain displacement Matrix
!
	Det = 1.D0
!
	B = 0.0D0	!ALL
	
	do 70 j = 1,4	! For 1D Electrostatics
	T(j)		= Br(j)
	B(j)		= B1Dr(j)
   70	continue
!
!	write(*,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,32)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,4(8(f10.7,1X)/)))
	end
