	Subroutine QQ_EtranDEplusGMatrix(Qc,nQc,Qd,nStifEL,R,Rad,D,Det,
     &				THETAL,BVEC,SKLM,EDG,Nel,NelType,Iout)
!	Inputs
!		CU				= Current Curvature
!		nQc				= Order of the Bezier
!		Qd(nStifEL)		= Current Equilibrated Displacement solutions				
!		R				= r-directional root domain value	
!		Det				= determinant of The Jacobian
!		Nel				= Element Number
!		NelType			= Element Type:
!							0 = Plane Stress
!							1 = Plane Strain
!							2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		EDG(6,6)		= EtranDEplusG Matrix at integration point R
!		EF0(6)			= EtransposeF0 Vector at integration point R				
!		BVEC(nStifEL)	= BtransEtranF0-Ttrans_dFB/dLamda Vector at integration point R				
!		SKLM(nStifEL)	= kLamda Stiffness Vector at integration point R				
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	BVEC         ,SKLM         ,EF0	  ,EDG
	Dimension		BVEC(nStifEL),SKLM(nStifEL),EF0(6),EDG(6,6)
	Real(kind=8)	Qc       ,Qd         ,D   
	Dimension		Qc(2,nQc),Qd(nStifEL),D(3)
	Real(kind=8)	Det,R
	integer			nDegR,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir
!
	Real(kind=8)	dum,xMult
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D     ,Axes           	 
	Dimension		H1D(nQc),Axes(3,3)
	Real(kind=8)	AJI
	DATA zero/0.D0/,one/1.0D0/  
!	-------------------------------------------- Basis Functions
	Br	= zero ! ALL
	h1D = zero ! ALL		 
	call Bernstein(Br,nQc,r,iOut)
	call Bernstein_IstDerivative(H1D,nQc,r,iOut)
!------------------------------------------------- Latest Curvature		 
	CU		= one/Rad
!	CU		= 0.D0						! **** Straight Beam ****
!---------------------------------------- 
	CCU		= CU*CU
	AJI		= one/det
!
	nQ0 = 0
	nQ1 = nQ0+nQc
	nQ2 = nQ1+nQc
	nQ3 = nQ2+nQc
	nQ4 = nQ3+nQc
	nQ5 = nQ4+nQc
!
!-------------------------------------------------- Prepare:Displacement/Derivatives
	u  = zero ! u
	w  = zero ! w
	t  = zero ! theta
	du = zero ! du
	dw = zero ! dw	
	dt = zero ! dtheta
!------------------------------------------------- displacements
	do 10 j = 1,nQc	! Current Displacements & derivatives 
	u	= u + Br(j)*Qd(j+nQ0)			!u	
	w	= w + Br(j)*Qd(j+nQ1)			!v	
	t	= t + Br(j)*Qd(j+nQ2)			!theta		
!------------------------------------------------- derivatives of displacements 
	du	= du + H1D(j)*Qd(j+nQ0)*AJI		!u-primed
	dw	= dw + H1D(j)*Qd(j+nQ1)*AJI		!v-primed
	dt	= dt + H1D(j)*Qd(j+nQ2)*AJI		!theta-primed	
   10	continue
!-------------------------------------------------- Prepare:Strains
	sn		= dsin(t)
	cn		= dcos(t)
	scn		= sn*cn
	ssn		= sn*sn
	ccn		= cn*cn
!
	du1 = du + one
	eps	= dw*sn + (du1*cn - one ) + CU*(u*sn-w*cn)
	gam	= dw*cn - (du1*sn - zero) + CU*(u*cn+w*sn)
	xKi	= dt
!	---------------
	ep1	= eps + one
	gm1 = gam - zero
!-------------------------------------------------- Prepare:Nt, Qt, M
	Axial_n = D(1)*eps	! Axial along normal to x-section
	Shear_n = D(2)*gam	! normal to axial
	Bendi_n = D(3)*xKi 
!
	Axial_t = Axial_n*cn - Shear_n*sn	! Axial along tangent to the curve
	Shear_t = Axial_n*sn + Shear_n*cn	! normal to axial
	Bendi_t = Bendi_n 
!-------------------------------------------------- Prepare:G
	g13		= CU*Axial_t
	g23		= CU*Shear_t
	g33		= CU*(-u*Shear_t + w*Axial_t) - du1*Axial_t - dw*Shear_t 
	g34		= -Shear_t
	g35		= Axial_t
!--------------------------------------------------------------------- EtransposeDE+G
	EDG			= zero		! zero all
!-------------------------------------------------- Prepare:sundries
	d1m2		= D(1) - D(2)
	d1p2		= D(1) + D(2)
	d1c2Pd2s2	= D(1)*cn*cn  + D(2)*sn*sn
	d1s2Pd2c2	= D(1)*sn*sn  + D(2)*cn*cn
	d1GcPd2Es	= D(1)*gm1*cn + D(2)*ep1*sn
	d1GsMd2Ec	= D(1)*gm1*sn - D(2)*ep1*cn
!-------------------------------------------------- Fill it in
	EDG(1,1)	= CCU*d1s2Pd2c2
	EDG(1,2)	= -CCU*d1m2*scn
	EDG(1,3)	= CU*d1GsMd2Ec + g13
	EDG(1,4)	= CU*d1m2*scn
	EDG(1,5)	= CU*d1s2Pd2c2
!
	EDG(2,2)	= CCU*d1c2Pd2s2
	EDG(2,3)	= -CU*d1GcPd2Es + g23
	EDG(2,4)	= -CU*d1c2Pd2s2
	EDG(2,5)	= -CU*d1m2*scn
!
	EDG(3,3)	= D(1)*gm1*gm1 + D(2)*ep1*ep1 + g33
	EDG(3,4)	= d1GcPd2Es + g34
	EDG(3,5)	= d1GsMd2Ec + g35
!
	EDG(4,4)	= d1c2Pd2s2
	EDG(4,5)	= d1m2*scn
!
	EDG(5,5)	= d1s2Pd2c2
!
	EDG(6,6)	= D(3)
!-------------------------------------------------- Symmetry:Lower Triangle
	do 50 i = 1,5
	do 50 j = i+1,6
	EDG(j,i) = EDG(i,j)
   50 continue	
!--------------------------------------------------------------------- BtransEtranF0
!																	 associated with Load b
	EF0(1)	= CU*Shear_t
	EF0(2)	= -CU*Axial_t
	EF0(3)	= dw*Axial_t - du1*Shear_t
     &		 + CU*(u*Axial_t + w*Shear_t)
	EF0(4)	= Axial_t
	EF0(5)	= Shear_t
	EF0(6)	= Bendi_t
!
	do 60 j = 1,nQc	!  
	BVEC(j+nQ0)	= Br(j)*EF0(1) + H1D(j)*EF0(4)*AJI			!	
	BVEC(j+nQ1)	= Br(j)*EF0(2) + H1D(j)*EF0(5)*AJI			!	
	BVEC(j+nQ2)	= Br(j)*EF0(3) + H1D(j)*EF0(6)*AJI			!		
   60	continue
!------------------------------------------ Subtract Ttrans_dFB/dLamda
!	applied body forces associated with residual integral
!	call BodyForce(Ri,dBFN,dBFQ,dBFM,1)		! 1= residual associated bodyforces
	dBFN = zero		! TEMPORARILY
	dBFQ = zero
	dBFM = zero
!	----------------
	do 70 j = 1,nQc	
	BVEC(j+nQ0)	= BVEC(j+nQ0) - Br(j)*dBFN			!BFN	
	BVEC(j+nQ1)	= BVEC(j+nQ1) - Br(j)*dBFQ			!BFQ	
	BVEC(j+nQ2)	= BVEC(j+nQ2) - Br(j)*dBFM			!BFM		
   70	continue
!--------------------------------------------------------------------- kLamda Stiffness Vector
!																	 associated with Matrix A
!	derivative associated with kLamda stiffness integral
!	call BodyForce(Ri,dBFN,dBFQ,dBFM,2)		! 2= kLambda associated derivative
	dBFN = zero		! TEMPORARILY
	dBFQ = zero
	dBFM = zero
!	----------------
	do 80 j = 1,nQc	
	SKLM(j+nQ0)	= -Br(j)*dBFN			!BFN	
	SKLM(j+nQ1)	= -Br(j)*dBFQ			!BFQ	
	SKLM(j+nQ2)	= -Br(j)*dBFM			!BFM		
   80	continue
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(EDG(i,j),j = 1,6),i=1,6)
		write(Iout,1020) nStifEL,(BVEC(i),i=1,nStifEL)
		write(Iout,1030) nStifEL,(SKLM(i),i=1,nStifEL)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("EtransposeDE+G Matrix EDG(6,6)"/
     &        (I5/,6(5(f10.7,1X)/)))
 1020 format("BVEC Vector(",I2,")"/(6(f10.7,1X)))
 1030 format("SKLM Vector(",I2,")"/(6(f10.7,1X)))
	end
