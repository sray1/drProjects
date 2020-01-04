	Subroutine CC_StrainDispMat
     &	(Qc,R,S,B,Det,Nel,NelType,Iout)
!	Inputs
!		Qc(1,16)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,16)	= Bezier Y-Coordinates
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
!		B(3,32)		= Strain Displacement Matrix
!						at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc,     B     ,xLen1,xLen2,yLen
	Dimension		Qc(2,*),B(3,*)
	Real(kind=8)	Det,R,S
	integer			Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
	Integer			nDegR,nDegS
!
	Real(kind=8)	H1D      	 
	Dimension		H1D(2,16)
	Real(kind=8)	AJI   
	Dimension		AJI(2,2)
!------------------------------------------------------ IsoParametric
!
!	Inverse & determinant of Jacobian
!
	call CC_Jacobian(Qc,16,4,4,R,S,H1D,AJI,Det,Nel,Iout,1)
!
!------------------------------------------------ IsoParametric
!	Strain displacement Matrix
!
	do 50 j = 1,16 
	B(1,j)		= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
	B(1,j+16)	= 0.
!
	B(2,j)		= 0.
	B(2,j+16)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
!
	B(3,j)		= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
	B(3,j+16)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
   50	continue
!
!	write(iOut,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,32)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,4(8(f10.7,1X)/)))
 1020 format(2X,"R = ",f7.4,2X,"S = ",f7.4,2X,"det = ",f7.3,
     &		2X,"X_Twist = ",f7.3,2X,"Y_Twist = ",f7.3)
	end
