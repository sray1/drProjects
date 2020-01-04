	Subroutine CC_StrainDispMat(Qc,nQc,R,B,nB,Det,Nel,NelType,Iout)
!	Inputs
!		Qc(4)	= Bezier X-Coordinates
!		R			= r-directional root domain value	
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		B(2,8)		= Strain Displacement Matrix
!						at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc,     B
	Dimension		Qc(nQc),B(2,nB)
	Real(kind=8)	Det,R
	integer			Nel,NelType,Iout
!
	Real(kind=8)	dum
	Real(kind=8)	Br   ,AB   ,BW   ,BB
	Dimension		Br(4),AB(8),BW(8),BB(8)
	Real(kind=8)	B1Dr   
	Dimension		B1Dr(4)
	Real(kind=8)	AJ,AJInv 
!	
!	Define Bernstein Interpolations
!
	Br(1) = (1.-r)*(1.-r)*(1.-r)	! W & Beta variation
	Br(2) = 3.*(1.-r)*(1.-r)*r
	Br(3) = 3.*(1.-r)*r*r
	Br(4) = r*r*r
!	
!	Define Derivative Bernstein: delT wrt r
!
	dum		= 3.*r*r			! delW/delr or delBeta/delr
	B1Dr(1) = -3.*(1.-r)*(1.-r)
	B1Dr(2) = 3*(1.-4.*r+dum)
	B1Dr(3) = 3*(2.*r-dum)
	B1Dr(4) = dum
!
!	Jacobian: Straight Beam Length
!
	AJ = Qc(nQc) - Qc(1)
!
!	Determinant of Jacobian
!
	det = AJ
	if(det.gt.0.0000001) go to 40
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
!
!	Inverse of Jacobian
!
   40 continue
	AJInv = 1./det
!
!	Strain displacement Matrix for W & BETA
!	
	do 50 j = 1,4 
	BW(j)	= AJInv*B1Dr(j)
	BW(j+4)	= 0.0D0
	AB(j)	= 0.0D0
	AB(j+4)	= Br(j)
	BB(j)	= 0.0D0
	BB(j+4)	= AJInv*B1Dr(j)
!
   50	continue
!
!	Strain displacement Matrix
!
	do 60 j = 1,8 
	B(1,j)		= BB(j)
	B(2,j)		= AB(j)-BW(j)
   60	continue
!
!	write(*,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(2,8)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,4(8(f10.7,1X)/)))
	end
