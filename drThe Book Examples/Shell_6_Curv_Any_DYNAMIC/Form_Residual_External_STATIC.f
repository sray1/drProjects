	Subroutine Form_Residual_External_Static(BVec,SKLM,TMat,
     &							nDof,nStifEL,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	RExt		= External Residual Vector: BODY FORCE ONLY because of
!						the way the arc length constraint is treated in iteration
!				= dbarTrans*Tmass*TAcc + ThetaBarTrans*RMass*(Wtrans*RAcc 
!	----------------------------------------------------------------------------- 
!	Inputs
!		nDof	= Nodal DOF = 6
!		nStifel	= Total Element DOF 
!		TMat	= Control Transformation Matrix: TMat(nDof,nStifEL)		
!		SKLM	= kLamda Stiffness Vector: SKLM(nStifEL)	
!	Outputs 
!		BVec	= External Body Force ONLY Residual Vector: RExt(nStifEL) at Integration Pt.
!	------------------------------------------------------------
!		BF		= Nodal Body Force Vector: BF(nDof)	
!		dBF		= Nodal Body Force Derivative Vector: dBF(nDof)	

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'
!
	Real(kind=8)	BF      ,dBF      ,SKLM
	Dimension		BF(nDof),dBF(nDof),SKLM(nStifEL)
	Real(kind=8)	BVec         ,TMat                                                                               
	Dimension		BVec(nStifEL),TMat(nDof,nStifEL)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
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
!	------------------------------------------------------ Residual Internal
	BVec		= MATMUL(TRANSPOSE(TMat),BF) ! will add when BF is nonzero *******
!---------------------------------------------------------- Write:
	iPrt = 0
	call DumpRealArray(BVec,nStifEL,"Res_Ext_Body",iPrt,iOut)
!----------------------------------------------------------
	return
!
	end
