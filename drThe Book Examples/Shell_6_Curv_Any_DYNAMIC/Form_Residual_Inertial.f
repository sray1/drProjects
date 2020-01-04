	Subroutine Form_Residual_Inertial(RIne,W,TAcc,AAcc,TMat,
     &						TMass,RMass,nS,nDof,nStifEL,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	RIne		= Inertial Residual Vector
!				= dbarTrans*Tmass*TAcc + ThetaBarTrans*RMass*(Wtrans*RAcc 
!	----------------------------------------------------------------------------- 
!	Inputs
!		nS		= 3
!		nDof	= Nodal DOF = 2*nS = 6
!		nStifel	= Total Element DOF = 
!		W		= Rotational Transformation Matrix: W(nS,nS)	
!		TACC	= Translational Acceleration Vector: TAcc(nS)	
!		AACC	= Angular Acceleration Vector: AAcc(nS)	
!		TMAT	= Generalized Control Transformation Matrix: TMat(nDof,nStifEL)	
!		TMass	= Translational Mass density	
!		RMass	= Rotational    Mass density	
!	Outputs 
!		RIne	= Inertial Residual Vector: RIne(nStifEL) at Integration Pt.
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'
!
	Real(kind=8)	W       ,TAcc    ,AAcc    ,TMat                                               
	Dimension		W(nS,nS),TAcc(nS),AAcc(nS),TMat(nDof,nStifEL)
	Real(kind=8)	RIne                                                                      
	Dimension		RIne(nStifEL)
	Real(kind=8)	Tem      ,TP    ,AP                                                                      
	Dimension		Tem(nDof),TP(nS),AP(nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ Translational Part
	TP		= TMass*TAcc
!	------------------------------------------------------ Angular Part
	AP		= RMass*MATMUL(TRANSPOSE(W),AAcc)
!	------------------------------------------------------ together
	do ii = 1,nS
		Tem(ii)		= TP(ii)
		Tem(ii+nS)	= AP(ii)
	end do		
!	------------------------------------------------------ Residual Inertial
	RIne = MATMUL(TRANSPOSE(TMat),Tem)
!---------------------------------------------------------- Write:
	iPrt = 0
	call DumpRealArray(RIne,nStifEL,"Residual_Inertial",iPrt,iOut)
!----------------------------------------------------------
	return
!
	end
