	Subroutine Form_EtranDEplusGMatrix(DMat,
     &				TMat,BMat,BVEC,SKLM,EDG,Iout)
!	Subroutine Form_EtranDEplusGMatrix(RoOld,Hd,nStifEL,DMat,RK,
!     &				TMat,BMat,BVEC,SKLM,EDG,nC,nDof,nDof2,Iout)
!	Inputs
!		nDof			= 6
!		nDof2			= 18
!		CK				= Current Curvature
!		nQc				= Order of the Bezier
!		DMat			= DMat(nCMat =12,nCMat =12)
!		C01				= C01(nC=3)= curvature Vector Reference in dir 1
!		C02				= C02(nC=3)= curvature Vector Reference in dir 2
!		TMat			= T(nDof  =  6,nStifEL = 6*nQd1*nQd2)
!		BMat			= T(nDof2 = 18,nStifEL = 6*nQd1*nQd2)
!
! 	
!	Outputs 
!		EDG(18,18)		= EtranDEplusG Matrix at integration point R
!		EF0(18)			= EtransposeF0 Vector at integration point R				
!		BVEC(nStifEL)	= BtransEtranF0-Ttrans_dFB/dLamda Vector at integration point R				
!		SKLM(nStifEL)	= kLamda Stiffness Vector at integration point R				
!
	Implicit Real(kind=8) (a-h,o-z)
!============================================
	include 'SizeVar.h'
	include 'LoadStepIter.h'
	include 'CurParams.h'
	include 'ThetaConstants.h'
	include 'BeamParams.h'
	include 'ShellParams.h'
!==============================================
	Real(kind=8)	BVEC         ,SKLM         ,EFO              
	Dimension		BVEC(nStifEL),SKLM(nStifEL),EFO(nDof2)
	Real(kind=8)	EDG             ,BF      ,dBF
	Dimension		EDG(nDof2,nDof2),BF(nDof),dBF(nDof)
	Real(kind=8)	DMat           
	Dimension		DMat(nCMat,nCMat)
	Real(kind=8)	TMat              ,BMat                                               
	Dimension		TMat(nDof,nStifEL),BMat(nDof2,nStifEL)
	Real(kind=8)	RK      ,G             ,EMat                                        
	Dimension		RK(nDim),G(nDof2,nDof2),EMat(nCMat,nDof2)
	Real(kind=8)	FMns       ,FMn                               
	Dimension		FMns(nCMat),FMn(nCMat)
	Real(kind=8)	Hat1   ,Hat2   ,rE    ,FMtt                                                
	Dimension		Hat1(3),Hat2(3),rE(12),FMtt(12)                                               
!
	Equivalence (rE(1),rE1(1)),(rE(7),rE2(1))
	Equivalence (FMtt,FMt1(1)),(FMtt(7),FMt2(1))
!
	DATA zero/0.D0/,one/1.0D0/ 
	DATA Hat1/1.0D0,0.D0,0.D0/
	DATA Hat2/0.0D0,1.D0,0.D0/
!============================================
!	nCMat	= 12	
!	nC		= 3	
!	nDof	= 6	
!	nDof2	= 18
	nC		= nDim	
	nG		= nDof2
!	====================================== Debug
!	if((iStep == 1).AND.(iNut == 2)) Then
	if((iStep == 1).AND.(iNut == 2)) Then
		abc = 1
	endif
!-------------------------------------------------------------------------------------------- Prepare: theta constants
!																				c1,c2,c1b,c2b
	Di		= DD
	Ro		= RR
	call FormThetaConstants(Ro,nC,c1,c2,c1b,c2b,Iout)
!======================================================================================= Direction 1
	C0		= C01
	Hat		= Hat1
	Dp		= Dp1
	Rp		= Rp1
!	-------------------------------
	call Form_a_N_kc_N_AMat(1,Iout)
!	-------------------------------
	call FormR_Matrix(Ro,Rp,RMat1,nC,c1,c2,c1b,c2b,Iout) !R matrix
!	--------------------------------------------------- E(12x18): direction 1 part
	RMat = RMat1
	call FormEMatrix_1(EMat,nCMat,nDof2,nDim,1,Iout)
!	-------------------------------
	CK1		= CK
	AA1		= AA
	AMat1	= AMat		
	WMat1	= WMat		
!	--------------------------------------------------- Real Strains (n-Mn-Qn coords)
	call FormRealStrains_Ncoords(rE1,nDof,3,1,Iout)	! strain in shell coords
!======================================================================================= Direction 2
	C0		= C02
	Hat		= Hat2
	Dp		= Dp2
	Rp		= Rp2
!	-------------------------------
	call Form_a_N_kc_N_AMat(2,Iout)
!	-------------------------------
	call FormR_Matrix(Ro,Rp,RMat2,nC,c1,c2,c1b,c2b,Iout) !R matrix
!	--------------------------------------------------- E(12x18): Add direction 2 part
	RMat = RMat2
	call FormEMatrix_2(EMat,nCMat,nDof2,nDim,2,Iout)
!	-------------------------------
	CK2		= CK
	AA2		= AA
	AMat2	= AMat		
	WMat2	= WMat		
!	--------------------------------------------------------------------- Real Strains (n-Mn-Qn coords)
	call FormRealStrains_Ncoords(rE2,nDof,3,2,Iout)	! strain in shell coords
!	---------------------------------------------- SYMMETRIzE
	call Form_RealStrains_Ncoords_Symm(rE,12,iout)
!======================================================================================= G and E
!--------------------------------------------------------------------- Force-Moments (t-m-b Coords)
!																	and (n-Mn-Qn coords) for G Mat
	call FormForMom(DMat,rE,nCMat,AMat1,AMat2,nC,nDof,FMt1,FMt2,
     &											FMn,FMns,Iout)
!--------------------------------------------------------------------- G(18x18)
	call FormGMatrix(G,nDof2,nDim,nDof,Iout)
!--------------------------------------------------------------------- ETransDE+G (18x18)
	EDG			= MATMUL(MATMUL(TRANSPOSE(EMat),DMat),EMat) + G
!---------------------------------------------------------- Write:
	iPrt = 0
	if((iStep == 9999).AND.(iNut == 2)) Then
!	if((iStep == 1).AND.(iNut == 2)) Then
		write(Iout,1005) (i,(EMat(i,j),j = 1,nDof2),i=1,nCMat)
		write(Iout,1050) (i,(  G(i,j),j = 1,nDof2),i=1,nDof2)
		write(Iout,1040) (i,(EDG(i,j),j = 1,nDof2),i=1,nDof2)
	endif
!--------------------------------------------------------------------- BtransEtranF0(6nx1)
!																	 associated with Load b
	EFO			= MATMUL(TRANSPOSE(EMat),FMns)	!EFO(18x1) = ETrans(18x12) FMns(12x1)
	BVEC		= MATMUL(TRANSPOSE(BMat),EFO)
!--------------------------------------------------------------------- Subtract Ttrans_FB
!	applied body forces associated with residual integral
!	call BodyForce(Ri,BFN,BFQ,BFM,1)		! 1= residual associated bodyforces
!	-----------------------------
	BF			= zero		! TEMPORARILY
!	----------------
!	BVEC		= BVEC - MATMUL(TRANSPOSE(TMat),BF) ! will add when BF is nonzero *******
!--------------------------------------------------------------------- kLamda Stiffness Vector
!																	 associated with Matrix A
!	derivative associated with kLamda stiffness integral
!	call BodyForce(Ri,BFN,BFQ,BFM,2)		! 2= kLambda associated derivative
!	-----------------------------
	dBF = zero		! TEMPORARILY
!	----------------
	SKLM = zero
!	SKLM = MATMUL(TRANSPOSE(TMat),dBF)				! will add when dBF is nonzero *******	
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 0)) Then
			iPrt = 1
			call DumpStringVar("Beg:Form_EtranDEplusGMatrix",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpIntegerVar(lr,"GaussIndex",iPrt,iOut)
			call DumpRealVar(Ri,"GaussPt.",iPrt,iOut)
			call DumpRealArray(C01,nC,"C01",iPrt,iOut)
			call DumpRealArray(C02,nC,"C02",iPrt,iOut)
			call DumpRealMatrix(WMat,nC,nC,"WMat",iPrt,iOut)
			call DumpRealMatrix(RMat,nC,nC,"RMat",iPrt,iOut)
			call DumpRealMatrix(G,nDof2,nDof2,"GMat",iPrt,iOut)
			call DumpRealMatrix(EMat,nDof,nDof2,"EMat",iPrt,iOut)
			call DumpRealArray(EFO,nDof2,"EFO",iPrt,iOut)
			call DumpRealArray(BVEC,nStifEL,"BVEC",iPrt,iOut)
			call DumpRealArray(SKLM,nStifEL,"SKLM",iPrt,iOut)
			call DumpRealMatrix(EDG,nDof2,nDof2,"EDG",iPrt,iOut)
			call DumpStringVar("End:Form_EtranDEplusGMatrix",iPrt,iOut)
			iPrt = 0
		endif
!		-------------------------------------------------------- Debug : End
!		---------------------------------------------------------- Write:
			iPrt = 0
			if(iPrt == 1) Then
				write(Iout,1040) (i,(EDG(i,j),j = 1,nDof2),i=1,nDof2)
				write(Iout,1020) nStifEL,(BVEC(i),i=1,nStifEL)
				write(Iout,1030) nStifEL,(SKLM(i),i=1,nStifEL)
			endif
!		----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1005 format("EMat(12,18)"/(I3,18(f7.2,1X)))
 1020 format("BVEC Vector(",I2,")"/(6(f13.7,1X)))
 1030 format("SKLM Vector(",I2,")"/(6(f13.7,1X)))
 1040 format(2X, "EDG Matrix(18,18)"/(I3,18(f7.0,1X)))
 1050 format(2X, "G Matrix(18,18)"  /(I3,18(f7.2,1X)))
	end
