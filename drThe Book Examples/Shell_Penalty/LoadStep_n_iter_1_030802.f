	Subroutine LoadStep_n_iter_1(D)
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	real(kind = 8)	D     
	dimension		D(6,6)
!========================================================================
	common A(1000000)
!
	common/LoadStepIter/iStep,iNut,bReset
	common/general/	   Trace
	common/Wpointers/  nSx,nRoCOld,nCuCOld,nRoKSav,nCKKSav,n1a,n1b,
     &				   n2,n2a,n2b,n3a,n3b,n3,n4,n4b,n5,nxo,nx,nBfors,
     &                   nStifK,nBo,nB,nPLoad,nGuLam,nUm,nUmO,nxmR,
     &				   nxm,nxmO,ndeltaUi,ndeltaUi1,ndeltaUi2,ndelUi,
     &				   ndelUiO,ndelUip11,ndelUip12,n7,n6,n6R,n2c,
     &				   nEndwSav	
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
!		---------------------------------------------------- Stiffness Matrix
!		-------------------------------------| Stiffness:Elem 1
!		Form Stiffness Matrix: Ist Elem 
!
		call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),nCInt,
     &			A(nxm),A(n1a),nQc,1,
!		call Quad_QQ_STIF(A(nxm),A(nQdOld),A(n1a),nQc,1,
     &			NelType,Nint,
     &			D,A(n2a),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble Ist Elem:nSTfK only has body force integral part
!
		call Assemble_Stif(A(n2c),A(n2a),
     &    		nStifEL,A(n2),nStifS,1,Iout,Trace)
!------------------------------------------------------------------------------- Residual & End Loads
!		----|------|----------------- Surface/End Load Vector
!		Get Load Vector 
!		call Set_ExtLoad_Y(A(n5),3,Iout)
!		call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!
!		Assemble Ist Elem:nBFors only has Residual & body force integral part
!
		call Assemble_Load(A(n2c),A(n7),
     &    		nStifEL,A(nB),nStifS,1,Iout)
!		-------------------------------------| Stiffness:Elem 2
		if(nElem == 2) Then
			call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),nCInt,
     &			A(nxm),A(n1b),nQc,2,
!			call Quad_QQ_STIF(A(nxm),A(nQdOld),A(n1b),nQc,2,
     &			NelType,Nint,
     &			D,A(n2b),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!		Assemble 2nd Elem:nSTfK only has body force integral part
!
			call Assemble_Stif(A(n2c),A(n2b),		
     &    		nStifEL,A(n2),nStifS,Nel,Iout,Trace)
!
!		Assemble 2nd Elem:nBFors only has Residual & body force integral part
!
			call Assemble_Load(A(n2c),A(nBFors),
     &    		nStifEL,A(nB),nStifS,2,Iout)
		endif
!------------------------------------------------------------------------------- Supported Stiff/Load/State
!		-----------|------|----------------- NonSingular Stiffness
!		Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
!		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
!     &						nStifN,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Solve:Current Iteration
!		call Factor_Determinant(A(n3),A(n4),A(n6),A(n7),29,29,29)
!		call Factor_ConditionNumber(A(n6),A(n2),A(n4),nStifN,
!     &										nStifN,nStifN,iOut)
!		call Solve_AxEqB(A(n6),A(nx),A(n4),nStifN,nStifN,iOut)
!		--------------------------------------------------------- Invert:Current Iteration
		detKO = detK
		call RealSym_Determinant(A(n6),A(n3),NStifN,NStifN,NStifN,
     &								detK,iOut)
		call Invert_A(A(n6),nStifN,nStifN,iOut,iFileStiff)
!------------------------------------------------------------------ Initialize
!		! Step 3ai: eqn x
		if(Imaginary.NE..TRUE.) Then
			call Calc_ArcLength_Stepm(delLmO,DelLm,
     &							iTermO,iTerRef,iStep,iOut)
		endif
!  450		continue
!		! Step 3aii: eqn 7
		call Calc_deltaUi2(A(n6),A(nPLoad),A(ndeltaUi2),
     &						nStifN,iOut)
!		! Step 3aiii: eqn xx
		call Calc_Lamda1_Stepm(iStep,A(ndeltaUi2),nStifN,delLamdaiO,
     &						DelLm,DetK,DetKO,iOut)
!		! Step 2b: eqn 10: At the beginning of each Loadstep Linear Solution
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)		! state
		call Calc_delUi(DelLamdaiO,A(ndeltaUi1),A(ndeltaUi2),
     &					A(ndelUiO),NStifN,iOut)
		if(Imaginary) Then
			SLamdam		= SLamdamO + delLamdaiO
!			SLamdamO	= SLamdam
			Imaginary	= .FALSE.
		else		
			DelLm		= DelLmO
		endif
		DeltaLamdai = delLamdaiO
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!===========================================================================================
  500		continue
!	---------------
	return
	end

