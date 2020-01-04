	Subroutine CC_StrainDispMat(Qc,nQc,R,S,B,nB,Det,Nel,NelType,Iout)
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
	Real(kind=8)	Qc,       B
	Dimension		Qc(2,nQc),B(nB)
	Real(kind=8)	Det,R,S
	integer			Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
	Integer			nDegR,nDegS
!
	Real(kind=8)	dum,delCx,delCy,de2Cx,de2Cy
	Real(kind=8)	Br   ,Bs
	Dimension		Br(4),Bs(4)
	Real(kind=8)	B1Dr   ,B1Ds
	Dimension		B1Dr(4),B1Ds(4)
	Real(kind=8)	B2Dr   ,B2Ds
	Dimension		B2Dr(4),B2Ds(4)
	Real(kind=8)	H1D      ,H2D	 
	Dimension		H1D(2,nQc),H2D(2,nQc)
	Real(kind=8)	AJ,     AJI   
	Dimension		AJ(2,2),AJI(2,2)
	Real(kind=8)	DJ,     DJI   
	Dimension		DJ(2,2),DJI(2,2)
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.-r)*(1.-r)*(1.-r)
	Br(2) = 3.*(1.-r)*(1.-r)*r
	Br(3) = 3.*(1.-r)*r*r
	Br(4) = r*r*r
!	 
	Bs(1) = (1.-s)*(1.-s)*(1.-s)
	Bs(2) = 3.*(1.-s)*(1.-s)*s
	Bs(3) = 3.*(1.-s)*s*s
	Bs(4) = s*s*s
!---------------------------------------------------------	
!	Define Derivative Bernstein: delH wrt r & s
!
	dum		= 3.*r*r
	B1Dr(1) = -3.*(1.-r)*(1.-r)
	B1Dr(2) = 3*(1.-4.*r+dum)
	B1Dr(3) = 3*(2.*r-dum)
	B1Dr(4) = dum
!	 
	dum		= 3.*s*s
	B1Ds(1) = -3.*(1.-s)*(1.-s)
	B1Ds(2) = 3.*(1.-4.*s+dum)
	B1Ds(3) = 3.*(2.*s-dum)
	B1Ds(4) = dum
!	
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!		H1D(2,*)	= delH/dels
!
!	do 10 i = 1,4 
!	do 10 j = 1,4
!	k = i+(j-1)*4
!	H1D(1,k) = B1Dr(i)*Bs(j)
!	H1D(2,k) = Br(i)*B1Ds(j)
!   10 continue
	do 10 i = 1,4 
	do 10 j = 1,1	! ALWAYS for 1D Curve Beam
	k = i+(j-1)*4
	H1D(1,k) = B1Dr(i)
!	H1D(2,k) = Br(i)*B1Ds(j)
   10 continue
!------------------------------------------------------------
!	Define 2nd Derivative Bernstein: del2H wrt r & s
!
	B2Dr(1) = 6.*(1.-r)
	B2Dr(2) = 6.*(-2.+3.*r)
	B2Dr(3) = 6.*(1.-3.*r)
	B2Dr(4) = 6.*r
!	 
	B2Ds(1) = 6.*(1.-s)
	B2Ds(2) = 6.*(-2.+3.*s)
	B2Ds(3) = 6.*(1.-3.*s)
	B2Ds(4) = 6.*s
!	
!	2nd Derivative of H wrt r and s
!		H2D(1,*)	= del2H/delr
!		H2D(2,*)	= del2H/dels
!
!	do 10 i = 1,4 
!	do 10 j = 1,4
!	k = i+(j-1)*4
!	H1D(1,k) = B1Dr(i)*Bs(j)
!	H1D(2,k) = Br(i)*B1Ds(j)
!   10 continue
	do 20 i = 1,4 
	do 20 j = 1,1	! ALWAYS for 1D Curve Beam
	k = i+(j-1)*4
	H2D(1,k) = B2Dr(i)
!	H1D(2,k) = Br(i)*B2Ds(j)
   20 continue
!------------------------------------------------------
!	Jacobian
!
	AJ = 0.0	!ALL
!
	delCx = 0.0
	do 30 k = 1,4
	delCx = delCx + H1D(1,k)*Qc(1,k)
   30 continue
!
	delCy = 0.0
	do 40 k = 1,4
	delCy = delCy + H1D(1,k)*Qc(2,k)
   40 continue
!
	AJ(1,1) = dsqrt((delCx*delCx)+(delCy*delCy))
	AJ(2,2) = 1.0D0
!	do 30 j = 1,2
!	do 30 i = 1,2
!	dum = 0.0
!	do 20 k = 1,16
!	dum = dum + H1D(i,k)*Qc(j,k)
!	AJ(i,j) = dum
!  20 continue
!  30 continue
!
!	Determinant of Jacobian
!
	det = AJ(1,1)*AJ(2,2) - AJ(1,2)*AJ(2,1)
!--------------------------------------------
	if(det.gt.0.0000001) go to 45
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
   45 continue
!--------------------------------------------
!	Derivative of Jacobian
!
	DJ = 0.0	!ALL
!
	de2Cx = 0.0
	do 50 k = 1,4
	de2Cx = de2Cx + H2D(1,k)*Qc(1,k)
   50 continue
!
	de2Cy = 0.0
	do 60 k = 1,4
	de2Cy = de2Cy + H2D(1,k)*Qc(2,k)
   60 continue
!
	DJ(1,1) = (delCx*de2Cx + delCy*de2Cy)/det
	DJ(2,2) = 1.0D0
!	do 30 j = 1,2
!	do 30 i = 1,2
!	dum = 0.0
!	do 20 k = 1,16
!	dum = dum + H1D(i,k)*Qc(j,k)
!	AJ(i,j) = dum
!  20 continue
!  30 continue
!-------------------------
!	Inverse of Jacobian
!
!   40 continue
!	dum = 1./det
!	AJI(1,1) =  AJ(2,2)*dum
!	AJI(1,2) = -AJ(2,1)*dum
!	AJI(2,2) =  AJ(1,1)*dum
!	AJI(2,1) = -AJ(1,2)*dum	
!-----------------------------
!
!	Strain displacement Matrix
!
!
	B = 0.0D0	!ALL
	
!	do 70 j = 1,16	! 
	do 70 j = 1,4	! For 1D Curve Beam 
	B(j)		= ((AJ(1,1)*H2D(1,j) - DJ(1,1)*H1D(1,j))/det/det/det)
     &			+ Br(j)		
!	B(2,j+16)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
!
!	B(3,j)		= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
!	B(3,j+16)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
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
