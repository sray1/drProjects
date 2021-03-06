	Subroutine Form_EtranDEplusGMatrix(nQc,Qd,nStifEL,DMat,C0,
     &				TMat,BMat,BVEC,SKLM,EDG,nC,nDof,nDof2,Iout)
!	Inputs
!		CU				= Current Curvature
!		nQc				= Order of the Bezier
!		Qd(nStifEL)		= Current Equilibrated Displacement Controls
!							nStifEL = 6*nQc				
!		DMat			= DMat(nDof =6,nDof =6)
!		C0				= C0(nC=3)= curvature Vector = {torsion,0,curvature}
!							Reference
!		TMat			= T(nDof =6,nStifEL=6*nQc)
!		BMat			= T(nDof2=12,nStifEL=6*nQc)
!
! 	
!	Outputs 
!		EDG(12,12)		= EtranDEplusG Matrix at integration point R
!		EF0(12)			= EtransposeF0 Vector at integration point R				
!		BVEC(nStifEL)	= BtransEtranF0-Ttrans_dFB/dLamda Vector at integration point R				
!		SKLM(nStifEL)	= kLamda Stiffness Vector at integration point R				
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	BVEC         ,SKLM         ,EFO       ,C0       
	Dimension		BVEC(nStifEL),SKLM(nStifEL),EFO(nDof2),C0(nC)
	Real(kind=8)	EDG             ,BF      ,dBF
	Dimension		EDG(nDof2,nDof2),BF(nDof),dBF(nDof)
	Real(kind=8)	Qd         ,DMat           ,FMn      ,FMt
	Dimension		Qd(nStifEL),DMat(nDof,nDof),FMn(nDof),FMt(nDof)
	Real(kind=8)	WMat       ,RMat       ,EMat            
	Dimension		WMat(nC,nC),RMat(nC,nC),EMat(nDof,nDof2)
	Real(kind=8)	TMat                                 
	Dimension		TMat(nDof,nStifEL)
	Real(kind=8)	BMat               ,HD       ,AMat                  
	Dimension		BMat(nDof2,nStifEL),HD(nDof2),AMat(nC,nC)
	Real(kind=8)	CK    ,AA    ,G             ,rE                         
	Dimension		CK(nC),AA(nC),G(nDof2,nDof2),rE(nDof)
!
	DATA zero/0.D0/,one/1.0D0/ 
!	--------------------------
!	nC		= 3	
!	nDof	= 6	
!	nDof2	= nDof*2
!--------------------------------------------------------------------- Displacement & Derivatives
	HD	= MATMUL(BMat,Qd)
!--------------------------------------------------------------------- Prepare: theta constants
!																		and AA,CK,AMat,WMat 
	call Form_a_N_kc_N_AMat(HD,nDof2,C0,AMat,WMat,nC,AA,CK,Iout)
!--------------------------------------------------------------------- Real Strains (n-Mn-Qn coords)
	call FormRealStrains_Ncoords(C0,nC,AA,CK,AMat,rE,nDof,Iout)
!--------------------------------------------------------------------- Force-Moments (t-m-b Coords)
!																		and (n-Mn-Qn coords)
	call FormForMom(DMat,rE,nDof,AMat,nC,FMt,FMn,Iout)
!--------------------------------------------------------------------- G(12x12)
	call FormGMatrix(HD,nDof2,FMt,nDof,C0,nC,G,WMat,RMat,AA,CK,Iout)
!--------------------------------------------------------------------- E(6x12)
	call FormEMatrix(AMat,C0,nC,EMat,nDof,WMat,RMat,AA,CK,nDof2,Iout)
!--------------------------------------------------------------------- ETransDE+G (12x12)
	EDG			= MATMUL(MATMUL(TRANSPOSE(EMat),DMat),EMat) + G
!--------------------------------------------------------------------- BtransEtranF0(6nx1)
!																	 associated with Load b
	EFO			= MATMUL(TRANSPOSE(EMat),FMn)	!EFO(12x1) = ETrans(12x6) FMn(6x1)
	BVEC		= MATMUL(TRANSPOSE(BMat),EFO)
!--------------------------------------------------------------------- Subtract Ttrans_FB
!	applied body forces associated with residual integral
!	call BodyForce(Ri,BFN,BFQ,BFM,1)		! 1= residual associated bodyforces
!	-----------------------------
	BF			= zero		! TEMPORARILY
!	----------------
	BVEC		= BVEC - MATMUL(TRANSPOSE(TMat),BF)
!--------------------------------------------------------------------- kLamda Stiffness Vector
!																	 associated with Matrix A
!	derivative associated with kLamda stiffness integral
!	call BodyForce(Ri,BFN,BFQ,BFM,2)		! 2= kLambda associated derivative
!	-----------------------------
	dBF = zero		! TEMPORARILY
!	----------------
	SKLM = MATMUL(TRANSPOSE(TMat),dBF) 	
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
 1010 format("EDG(12,12)"/(I5,3(4(f20.7,1X)/)))
 1020 format("BVEC Vector(",I2,")"/(6(f10.7,1X)))
 1030 format("SKLM Vector(",I2,")"/(6(f10.7,1X)))
	end
