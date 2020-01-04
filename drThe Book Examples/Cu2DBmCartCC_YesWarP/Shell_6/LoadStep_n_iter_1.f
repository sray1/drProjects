	Subroutine LoadStep_n_iter_1()
	Implicit Real(kind=8) (a-h,o-z)
!========================================================================
	include 'Blank.h'
	include 'Drill.h'
	include 'CurrentElem.h'
	include 'LoadStepIter.h'
	include 'general.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
	include 'files.h'
	include 'Scratch.h'
	include 'solve.h'
	include 'LogParams.h'
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:LoadStep_n_iter_1",0,iOut)
!		---------------------------------------------------------------------- Stiffness Matrix
		do 30 iEL = 1,nElem
!			-------------------------------------| Form Stiffness Matrix:
			iCEL = iEL 
!			-------------------------------------| Form Stiffness Matrix: 
			m2 =n2a
!		--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
	if(bOpt1) then
		call Opt1_Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	else		
		call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	endif
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
!=================================================================== Update
	if(iNut.LE.1) Then
		if(iRotCur == iRotCur1) Then
			iRotCur = iRotCur2
		else
			iRotCur = iRotCur1
		endif
	endif				
!===================================================================
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
		call RealSym_Determinant(A(n6),A(n3),A(n2),
     &					NStifN,NStifN,NStifN,detK,iOut)
		detKO = detK
!		call DumpRealVar(detKO,"Determinant = ",1,iOut)
!		call Invert_A(A(n6),nStifN,nStifN,iOut,iFileStiff)
!------------------------------------------------------------------ Initialize
!		! Step 3ai: eqn x
		if(Imaginary.NE..TRUE.) Then
			call Calc_ArcLength_Stepm(delLmO,DelLm,
     &							iTermO,iTerRef,iStep,iOut)
		endif
!  450		continue
!		================================================
!		! Step 3aii: eqn 7
!		call Calc_deltaUi2(A(n6),A(nPLoad),A(ndeltaUi2),
!     &						nStifN,iOut)
!		call Solve_AxEqB(A(n6),A(nPLoad),A(ndeltaUi2),
!     &			nStifN,nStifN,iOut)
!		================================================
!		===================
!		! Step 3aii: eqn 7
		if(bDrill) then
!			call Solve_AxEqB_Drill(A(n6),A(nPLoad),A(ndeltaUi2),
!     &			nStifN,nStifR,nStif3,Iout)
!		else
			call Solve_AxEqB(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,nStifN,iOut)
		endif
!		===================
!		! Step 3aiii: eqn xx
		call Calc_Lamda1_Stepm(iStep,A(ndeltaUi2),nStifN,delLamdaiO,
     &						DelLm,DetK,DetKO,iOut)
!		! Step 2b: eqn 10: At the beginning of each Loadstep Linear Solution
		call LV_Initialize(A(ndeltaUi1),nStifN,Iout)		! state
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
