	Subroutine QC_Disps_EL(Qd,nStifEL,nLoop,Nel,NelType,Iout)
!	Inputs
!		Qc(1,12)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,12)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
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
	Real(kind=8)	Qd         
	Dimension		Qd(nStifEL)
	Real(kind=8)	Det,R,S
	integer			Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
	Integer			nDegR,nDegS
!
	Real(kind=8)	Br   ,Bs   ,T         
	Dimension		Br(4),Bs(3),T(nStifel)
	Real(kind=8)	Dis
	Dimension		Dis(2,nLoop)
	Real(kind=8)	dum,sumU,sumV,SValues(3)
	DATA SValues	/0.0D0,0.5D0,1.0D0/
!---------------------
	nOrderR	= 4
	nOrderS	= 3
!
	delR	= 0.1D0
!--------------------------------------------------------- loop for SValues
	do 200 iS = 1,3
	S = SValues(iS)
!-------------------------------------------------------- loop for RValues
	do 100 iR = 1,nLoop
	R = delR*(iR-1)
!---------------------------------------------------------
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
	do 10 i = 1,nOrderR 
	do 10 j = 1,nOrderS
	k = i+(j-1)*nOrderR
	T(k) = Br(i)*Bs(j)
   10 continue
!	---------------
	sumU = 0.0D0
	sumV = 0.0D0
	do 60 j = 1,12 
   	sumU = sumU + T(j)*Qd(j)
   60	sumV = sumV + T(j)*Qd(j+12)
	Dis(1,iR) = sumU
	Dis(2,iR) = sumV
!	---------------------------------------------------- nLoop:RVal
  100 continue
!
	write(iOut,1000) Nel,S
	write(iOut,1010) (Dis(1,j),j = 1,nLoop)
	write(iOut,1020) (Dis(2,j),j = 1,nLoop)
!--------------------------------------------------------  Loop : SValues
  200 continue
!
	return
!
 1000 format(//2X," Displacements of Element ",I2," At S = ",F5.2/)
 1010 format(/5x,"u-Disp "/ 5(2X,F16.10))
 1020 format(/5x,"v-Disp "/ 5(2X,F16.10))
	end
