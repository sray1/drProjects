	Subroutine QQ_EtranDEplusGMatrix(nQc,Qd,nStifEL,R,DMat,Det,
     &				BVEC,SKLM,EDG,Nel,NelType,nC,nDof,nDof2,Iout)
!	Inputs
!		CU				= Current Curvature
!		nQc				= Order of the Bezier
!		Qd(nStifEL)		= Current Equilibrated Displacement solutions
!							nStifEL = 6*nQc				
!		R				= r-directional root domain value	
!		Det				= determinant of The Jacobian
!		Nel				= Element Number
!		NelType			= Element Type:
!							0 = Plane Stress
!							1 = Plane Strain
!							2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		EDG(12,12)		= EtranDEplusG Matrix at integration point R
!		EF0(12)			= EtransposeF0 Vector at integration point R				
!		BVEC(nStifEL)	= BtransEtranF0-Ttrans_dFB/dLamda Vector at integration point R				
!		SKLM(nStifEL)	= kLamda Stiffness Vector at integration point R				
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	BVEC         ,SKLM         ,EFO        
	Dimension		BVEC(nStifEL),SKLM(nStifEL),EFO(nDof2)
	Real(kind=8)	EF0	      ,EDG             ,BF      ,dBF
	Dimension		EF0(nDof2),EDG(nDof2,nDof2),BF(nDof),dBF(nDof)
	Real(kind=8)	Qd         ,DMat           ,FMn      ,FMt
	Dimension		Qd(nStifEL),DMat(nDof,nDof),FMn(nDof),FMt(nDof)
	Real(kind=8)	WMat       ,RMat       ,EMat            
	Dimension		WMat(nC,nC),RMat(nC,nC),EMat(nDof,nDof2)
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
!	--------------------------
!	nC		= 3	
!	nDof	= 6	
!	nDof2	= nDof*2
!	--------------------------		
	AJI = one/det 
!--------------------------------------------------------------------- Displacement/Derivatives
	call FormDisRot_N_Derivs(Qd,nStifEL,nQc,r,AJI,HD,nDof,nC,Iout)
!--------------------------------------------------------------------- Prepare 
	call Form_a_N_kc_Vectors(HD,nDof2,C0,nC,AA,CK,Iout)
!--------------------------------------------------------------------- Real Strains (n-Mn-Qn coords)
	call FormRealStrains_Ncoords(C0,nC,AA,CK,AMat,rE,nDof,Iout)
!--------------------------------------------------------------------- Force-Moments (t-m-b Coords)
	call FormForMom(D,rE,nDof,AMat,nC,FMt,FMn,Iout)
!--------------------------------------------------------------------- G(12x12)
	call FormGMatrix(HD,nDof2,FMt,nDof,C0,nC,G,WMat,RMat,AA,CK,Iout)
!--------------------------------------------------------------------- E(6x12)
	call FormEMatrix(HD,nDof2,C0,nC,EMat,nDof,WMat,RMat,AA,CK,Iout)
!--------------------------------------------------------------------- ETransDE+G (12x12)
	EDG			= MATMUL(TRANSPOSE(EMat),DMat)
	EDG			= MATMUL(EDG,EMat) + G
!--------------------------------------------------------------------- Finally: BTranETransDE+GB (12x12)
	BT			= TRANSPOSE(B)
	EDG			= MATMUL(BT,EDG)
	EDG			= MATMUL(EDG,B)
!--------------------------------------------------------------------- BtransEtranF0(6nx1)
!																	 associated with Load b
	EFO			= MATMUL(TRANSPOSE(EMat),FMn)	!EFO(12x1) = ETrans(12x6) FMn(6x1)
	BVEC		= MATMUL(BT,EFO)
!--------------------------------------------------------------------- Subtract Ttrans_FB
!	applied body forces associated with residual integral
!	call BodyForce(Ri,BFN,BFQ,BFM,1)		! 1= residual associated bodyforces
!	-----------------------------
	BF			= zero		! TEMPORARILY
!	----------------
	TT			= TRANSPOSE(T)
	BVEC		= BVEC - MATMUL(TT,BF)
!--------------------------------------------------------------------- kLamda Stiffness Vector
!																	 associated with Matrix A
!	derivative associated with kLamda stiffness integral
!	call BodyForce(Ri,BFN,BFQ,BFM,2)		! 2= kLambda associated derivative
!	-----------------------------
	dBF = zero		! TEMPORARILY
!	----------------
	SKLM = MATMUL(TT,dBF) 	
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(EDG(i,j),j = 1,nDof2),i=1,nDof2)
		write(Iout,1020) nStifEL,(BVEC(i),i=1,nStifEL)
		write(Iout,1030) nStifEL,(SKLM(i),i=1,nStifEL)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("EtransposeDE+G Matrix EDG(12,12)"/
     &        (I5/,6(5(f10.7,1X)/)))
 1020 format("BVEC Vector(",I2,")"/(6(f10.7,1X)))
 1030 format("SKLM Vector(",I2,")"/(6(f10.7,1X)))
	end
