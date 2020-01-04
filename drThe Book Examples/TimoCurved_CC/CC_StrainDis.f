	Subroutine CC_StrainDispMat(Qc,nQc,R,Rad,B,nB,Det,Nel,NelType,Iout)
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
	Dimension		Qc(2,nQc),B(3,nB)
	Real(kind=8)	Det,R,S
	integer			Nel,NelType,Iout
!
!		ndegR					= Bezier degree in Circ-dir = 3
	Integer			nDegR
!
	Real(kind=8)	dum,delCx,delCy
	Real(kind=8)	Br   
	Dimension		Br(4)
	Real(kind=8)	B1Dr   
	Dimension		B1Dr(4)
	Real(kind=8)	H1D      	 
	Dimension		H1D(nQc)
	Real(kind=8)	AJ,     AJI   
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
!	
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!
	do 10 i = 1,4 
	H1D(i) = B1Dr(i)
   10 continue
!------------------------------------------------------
!	Jacobian
!
	delCx = 0.0
	do 30 k = 1,4
	delCx = delCx + H1D(k)*Qc(1,k)
   30 continue
!
	delCy = 0.0
	do 40 k = 1,4
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
!--------------------------------------------
!	Strain displacement Matrix
!
	B = 0.0D0	!ALL
	
	do 70 j = 1,4	! For 1D Curve Beam with axial & shear strains 
	B(1,j)		= 0.D0			!Bending Strain		
	B(1,j+4)	= 0.D0
	B(1,j+8)	= AJI*H1D(j)
!
	B(2,j)		= Br(j)/Rad		!Axial Strain	
	B(2,j+4)	= AJI*H1D(j)
	B(2,j+8)	= 0.D0
!
	B(3,j)		= AJI*H1D(j)		!Shear Strain	
	B(3,j+4)	= -Br(j)/Rad
	B(3,j+8)	= Br(j)
   70	continue
!
!	write(*,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,12)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,2(6(f10.7,1X)/)))
	end
