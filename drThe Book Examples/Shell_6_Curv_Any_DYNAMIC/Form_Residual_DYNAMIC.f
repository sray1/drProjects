	Subroutine Form_Residual_DYNAMIC(BVec,SKLM,TMat,
     &								nC,nDof,nStifEL,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	RDyn		= Dynamic Residual Vector 
!				= RInertia - RExternal 
!	----------------------------------------------------------------------------- 
!	Inputs
!		nDof	= Nodal DOF = 6
!		nStifel	= Total Element DOF 
!		TMat	= Control Transformation Matrix: TMat(nDof,nStifEL)		
!		SKLM	= kLamda Stiffness Vector: SKLM(nStifEL)	
!	Outputs 
!		BVec	= External Residual Vector: RExt(nStifEL) at Integration Pt.
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'
!
	Real(kind=8)	BVec         ,SKLM
	Dimension		BVec(nStifEL),SKLM(nStifEL)
	Real(kind=8)	RExt         ,TMat                                                                               
	Dimension		RExt(nStifEL),TMat(nDof,nStifEL)

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!--------------------------------------------------------------------- Inertial Residual
	call Form_Residual_Inertial(RIne,W,TAcc,AAcc,TMat,
     &						TMass,RMass,nC,nDof,nStifEL,Iout)
!	-----------------------------
	call Form_Residual_External_Static(RExt,SKLM,TMat,
     &							nDof,nStifEL,Iout)
!	----------------
	BVEC		= BVEC - RExt
!---------------------------------------------------------- Write:
	iPrt = 0
	call DumpRealArray(BVec,nStifEL,"Residual_Static",iPrt,iOut)
!----------------------------------------------------------
	return
!
	end
