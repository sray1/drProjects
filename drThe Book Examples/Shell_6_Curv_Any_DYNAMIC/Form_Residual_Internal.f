	Subroutine Form_Residual_Internal(RInt,FMns,BMat,
     &							nCMat,nDof2,nStifEL,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	RInt		= Internal Residual Vector
!				= BMatTrans*EMatTrans*FMns 
!	----------------------------------------------------------------------------- 
!	Inputs
!		nCMat	= Full Constitutive Matrix Dimension = 12 
!		nDof2	= Generalized Nodal DOF = 18
!		nStifel	= Total Element DOF 
!		EMat	= Strain Transformation Matrix: EMat(nCMat,nDof2)	
!		BMat	= Generalized Control Transformation Matrix: BMat(nDof2,nStifEL)		
!		FMns	= Force (n-coordinate) Vector: FMns(nCMat)	
!		EFO		= Generalized Control Transformation Matrix: TMat(nDof,nStifEL)	
!	Outputs 
!		RInt	= Internal Residual Vector: RInt(nStifEL) at Integration Pt.
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'
!
	Real(kind=8)	FMns       ,EMat             ,BMat                                               
	Dimension		FMns(nCMat),EMat(nCMat,nDof2),BMat(nDof2,nStifEL)
	Real(kind=8)	RInt                                                                               
	Dimension		RInt(nStifEL)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!--------------------------------------------------------------------- BtransEtranF0(6nx1)
!																	 associated with Load b
!	EFO			= MATMUL(TRANSPOSE(EMat),FMns)	!EFO(18x1) = ETrans(18x12) FMns(12x1)
!	------------------------------------------------------ Residual Internal
	RInt	= MATMUL(TRANSPOSE(BMat),MATMUL(TRANSPOSE(EMat),FMns))
!---------------------------------------------------------- Write:
	iPrt = 0
	call DumpRealArray(RInt,nStifEL,"Residual_Internal",iPrt,iOut)
!----------------------------------------------------------
	return
!
	end
