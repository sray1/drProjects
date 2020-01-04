	Subroutine CQ_Jacobian(Qc,iCol,nOrderR,nOrderS,R,S,H1D,AJI,Det,
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
	Real(kind=8)	Qc        ,H1D        ,AJI
	Dimension		Qc(2,iCol),H1D(2,iCol),AJI(2,2)
	Real(kind=8)	Det,R,S
	integer			Nel,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
	Integer			nDegR,nDegS
!
	Real(kind=8)	dum,RR,SS
	Real(kind=8)	Br   ,Bs
	Dimension		Br(4),Bs(3)
	Real(kind=8)	B1Dr   ,B1Ds
	Dimension		B1Dr(4),B1Ds(3)
	Real(kind=8)	AJ 
	Dimension		AJ(2,2)
!---------------------------------- NOTE
	iRule = 0
!----------------------------------
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.D0-r)*(1.D0-r)*(1.D0-r)
	Br(2) = 3.D0*(1.D0-r)*(1.D0-r)*r
	Br(3) = 3.D0*(1.D0-r)*r*r
	Br(4) = r*r*r
!	 
	Bs(1) = (1.D0-s)*(1.D0-s)
	Bs(2) = 2.D0*(1.D0-s)*s
	Bs(3) = s*s
!	
!	Define Derivative Bernstein: delH wrt r & s
!
	dum		= 3.D0*r*r
	B1Dr(1) = -3.D0*(1.D0-r)*(1.D0-r)
	B1Dr(2) = 3.D0*(1.D0-4.D0*r+dum)
	B1Dr(3) = 3.D0*(2.D0*r-dum)
	B1Dr(4) = dum
!	 
	dum		= 2.D0*s
	B1Ds(1) = -2.D0+ dum
	B1Ds(2) = 2.D0 - 2.D0* dum
	B1Ds(3) = dum
!
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!		H1D(2,*)	= delH/dels
!
	do 10 i = 1,nOrderR 
	do 10 j = 1,nOrderS
	k = i+(j-1)*nOrderR
	H1D(1,k) = B1Dr(i)*Bs(j)
	H1D(2,k) = Br(i)*B1Ds(j)
   10 continue
!
!	Jacobian
!----------------------------------
	do 30 j = 1,2
	do 30 i = 1,2
	dum = 0.0
	do 20 k = 1,iCol
	dum = dum + H1D(i,k)*Qc(j,k)
	AJ(i,j) = dum
   20 continue
   30 continue
!-------------------------------------------- iRule = 1
	if( iRule == 1) Then
		AJ		= 0.0D0
		AJ(1,1) = 24.0D0
		AJ(2,2) = 12.0D0
	endif
!--------------------------------------------
!	Determinant of Jacobian
!
	det = AJ(1,1)*AJ(2,2) - AJ(1,2)*AJ(2,1)
	if(iPrt == 1) Then
		if(iRule == 0) Then
			write(Iout,1020) R,S,det
		else if (iRule == 1) Then
			write(Iout,1010) R,S,det
		endif
	endif
	if(det.gt.0.0000001) go to 40
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
!
!	Inverse of Jacobian
!
   40 continue
	dum = 1.D0/det
	AJI(1,1) =  AJ(2,2)*dum
	AJI(1,2) = -AJ(1,2)*dum
	AJI(2,2) =  AJ(1,1)*dum
	AJI(2,1) = -AJ(2,1)*dum	
!
   50	continue
!
	return
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
