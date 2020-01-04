	Subroutine QC_StrainDispMat(Qc,R,S,B,Det,Nel,NelType,Iout)
!	Inputs
!		Qc(1,12)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,12)	= Bezier Y-Coordinates
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
!		B(3,24)		= Strain Displacement Matrix
!						at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc,     B
	Dimension		Qc(2,*),B(3,*)
	Real(kind=8)	Det,R,S
	integer			Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 2
	Integer			nDegR,nDegS
!
	Real(kind=8)	H1D	 
	Dimension		H1D(2,12)
	Real(kind=8)	AJI   
	Dimension		AJI(2,2)
!
!	Inverse & determinant of Jacobian
!
	call CQ_Jacobian(Qc,12,4,3,R,S,H1D,AJI,Det,Nel,Iout,1)
!
!	Strain displacement Matrix
!
	do 50 j = 1,12 
	B(1,j)		= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
	B(1,j+12)	= 0.
!
	B(2,j)		= 0.
	B(2,j+12)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
!
	B(3,j)		= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
	B(3,j+12)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
   50	continue
!
!	write(iOut,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,24)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,3(8(f10.7,1X)/)))
	end
