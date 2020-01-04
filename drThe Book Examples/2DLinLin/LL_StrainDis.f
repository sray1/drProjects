	Subroutine LL_StrainDispMat(Qc,R,S,B,Det,Nel,NelType,Iout,nOrder,
     &							nSize,nStif)
!	Inputs
!		Qc(1,nSize)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc11x)
!		Qc(2,nSize)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc11y)
!		R			= r-directional root domain value	
!		S			= r-directional root domain value
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		nOrder		= nDegree+1 of Element: 
!						2 for Linear
!						3 for Quadratic
!						4 for Cubic
!		nStif		= Stiffness size nStifxnStif 
!		nSize		= nStif/2
! 	
!	Outputs 
!		B(3,nStif)	= Strain Displacement Matrix
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
!		ndegS					= Bezier degree in s-dir = 3
	Integer			nDegR,nDegS
!
	Real(kind=8)	dum
	Real(kind=8)	Br   ,Bs
	Dimension		Br(nOrder),Bs(nOrder)
	Real(kind=8)	B1Dr   ,B1Ds
	Dimension		B1Dr(nOrder),B1Ds(nOrder)
	Real(kind=8)	H1D	 
	Dimension		H1D(2,nSize)
	Real(kind=8)	AJ,     AJI   
	Dimension		AJ(2,2),AJI(2,2)
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.-r)
	Br(2) = r
!	 
	Bs(1) = (1.-s)
	Bs(2) = s
!	
!	Define Derivative Bernstein: delH wrt r & s
!
	B1Dr(1) = -1
	B1Dr(2) = 1
!	 
	B1Ds(1) = -1
	B1Ds(2) = 1
!
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!		H1D(2,*)	= delH/dels
!
	do 10 i = 1,nOrder 
	do 10 j = 1,nOrder
	k = i+(j-1)*nOrder
	H1D(1,k) = B1Dr(i)*Bs(j)
	H1D(2,k) = Br(i)*B1Ds(j)
   10 continue
!
!	Jacobian
!
	do 30 j = 1,2
	do 30 i = 1,2
	dum = 0.0
	do 20 k = 1,nSize
	dum = dum + H1D(i,k)*Qc(j,k)
	AJ(i,j) = dum
   20 continue
   30 continue
!
!	Determinant of Jacobian
!
	det = AJ(1,1)*AJ(2,2) - AJ(1,2)*AJ(2,1)
	if(det.gt.0.0000001) go to 40
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
!
!	Inverse of Jacobian
!
   40 continue
	dum = 1./det
	AJI(1,1) =  AJ(2,2)*dum
	AJI(1,2) = -AJ(2,1)*dum
	AJI(2,2) =  AJ(1,1)*dum
	AJI(2,1) = -AJ(1,2)*dum	
!
!	Strain displacement Matrix

!
	do 50 j = 1,nSize 
	B(1,j)			= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
	B(1,j+nSize)	= 0.
!
	B(2,j)			= 0.
	B(2,j+nSize)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
!
	B(3,j)			= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
	B(3,j+nSize)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
   50	continue
!
!	write(*,1010) nStif
!	write(*,1020) R,S,(i,(B(i,j),j = 1,nStif),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,",I5,")")
 1020 format("R = ",f20.16,2X,"S = ",f20.16/(I5/,(8(f10.7,1X)/)))
	end
