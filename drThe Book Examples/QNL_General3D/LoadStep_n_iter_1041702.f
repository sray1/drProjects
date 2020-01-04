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
	common/Addpoints/  ndelUiEL,n1c
	common/SizeVar/	  iGeom,iCont,nDim,nQc,nSup,nDof,nQd,nElem,
     &                  nStifEL,Nint,nCInt,nStifS,nStifC,
     &				  nStifN,nLoadLoc,NelType
      common/files/	  iFileStiff,Iout,IoutDef,IoutEnd,iRotCur
      common/Scratch/	  iRotCur1,iRotCur2,iDetRef
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:LoadStep_n_iter_1",0,iOut)
!		---------------------------------------------------------------------- Stiffness Matrix
		do 30 iEL = 1,nElem
!		-------------------------------------| Form Stiffness Matrix: 
		m1 = n1a
		if(iEL == 2) Then
			m1 = n1b
		endif		 
		m2 =n2a
		call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
		call Quad_QQ_STIF(A(m1),A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),nCInt,
     &			A(ndelUiEL),nQc,iEL,
!		call Quad_QQ_STIF(A(nxm),A(nQdOld),A(n1a),nQc,1,
     &			NelType,Nint,
     &			D,A(m2),A(nBfors),A(nStifK),
     &			nStifEL,Iout,Trace)
!
!			Assemble Ist Elem:nSTfK only has body force integral part
!
			call Assemble_Stif(A(n2c),A(m2),
     &    		nStifEL,A(n2),nStifS,iEL,Iout,Trace)
!			------------------------------------------------------------------ Residual & End Loads
!			----|------|----------------- Surface/End Load Vector
!			Get Load Vector 
!			call Set_ExtLoad_Y(A(n5),3,Iout)
!			call LV_EndLoad(A(n5),nQc,A(n7),nStifS,nLoadLoc,Iout)
!		----|------|----------------- Residual - lamda*P Load Vector
!			call Extract_DispCon(A(n7),nStifS,A(ndelUiEL),	!Extract LoadVector
!     &			nStifEL,iEL,iOut)
!
!			Assemble Elem:nBFors only has Residual & body force integral part
!
			call Assemble_Load(A(n2c),A(nBFors),
     &    		nStifEL,A(nB),nStifS,iEL,Iout)
   30		continue
!------------------------------------------------------------------------------- Supported Stiff/Load/State
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
		call RealSym_Determinant(A(n6),A(n3),A(n2),
     &					NStifN,NStifN,NStifN,detK)
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
!			Imaginary	= .FALSE.					!commented out for 3DBat
		else		
			DelLm		= DelLmO
		endif
		DeltaLamdai = delLamdaiO
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!===========================================================================================
	call DumpStringVar("Exit:LoadStep_n_iter_1",0,iOut)
	return
	end
