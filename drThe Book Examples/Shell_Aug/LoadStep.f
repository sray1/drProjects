	Subroutine LoadStep()
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
	include 'Augment.h'
	LOGICAL bOK
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!========================================================================
	call DumpStringVar("Enter:LoadStep",1,iOut)
!	----|------|---------------------------------------------------------- Surface/End Load Vector
	if((iStep==0).and.(iNut==0)) then
		call LV_EndLoad(A(n5),A(n5V),nLod,A(n7),nStifS,Iout)
	elseif((iStep.gt.1).and.(iNut.gt.1)) then
		call LV_Initialize(A(nB),nStifS,Iout)	! Current Load Vector
	endif
!	---------------------------------------------------------------------- Stiffness Matrix
	do 10 iEL = 1,nElem
!	-------------------------------------| Read Current Augment Multiplier/Constraints
	call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &			Nint1,Nint2,iAugRead,iEL,2,iOut)
!	----------
	iCEL = iEL 
	m2 =n2a
	if((iStep.gt.1)) then
		call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &		nStifEL,iEL,iOut)
	endif
	if(bOpt1) then
		call Opt1_Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	elseif(bAug) then
		call Quad_QQ_STIF_Aug(A(nPenalt),A(nAugMul),A(nOldCon),
     &			A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	else
		call Quad_QQ_STIF(A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	endif
!	Assemble Ist Elem:nSTfK only has body force integral part
	call Assemble_Stif(A(n2c),A(m2),
     &   		nStifEL,A(n2),nStifS,iEL,Iout,Trace)
!	------------------------------------------------------------------ Residual & End Loads
!	Assemble Ist Elem:nBFors only has Residual & body force integral part
	if((iStep.gt.1).and.(iNut.gt.1)) then
!		----|------|----------------- Residual - lamda*P Load Vector
		call Extract_DispCon(A(n7),nStifS,A(ndelUiEL),	!Extract LoadVector
     &			nStifEL,iEL,iOut)
		call LV_minus_EndLoad(SLamdam+delLamdaiO,A(ndelUiEL),
     &			A(nBfors),nStifEL,iOut)
	endif
!
	if((iStep==0).and.(iNut==0)) then
		m7 = n7
		if(iEL.GT.1) Then
			m7 = nBFors
		endif
	elseif((iStep.gt.1)) then
		m7 = nBFors
	endif
!
	call Assemble_Load(A(n2c),A(m7),
     &   		nStifEL,A(nB),nStifS,iEL,Iout)
   10	continue
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
!	-----------|------|----------------- NonSingular Stiffness: rigid body Out
	call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &							A(nSx),nSup,iCont,iOut)
!	----------|------|----------------- Supported Load Vector & State Vector: rigid body Out
	if((iStep==0).and.(iNut==0)) then
		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
     &						nStifN,A(nSx),nSup,iCont,iOut)
	elseif((iStep.gt.1).and.(iNut.gt.1)) then
		call Extract_ContractedLoadVector(A(nB),nStifC,A(nGuLam),	!Residual
     &						nStifN,A(nSx),nSup,iCont,iOut)
		call Extract_ContractedLoadVector(A(nxO),nStifC,A(ndelUiO),	!State
     &						nStifN,A(nSx),nSup,iCont,iOut)
	endif		
!	------------------------------------------------------------------------------- Solve:Current Iteration
	nxxx = n2
	if((iStep==0).and.(iNut==0)) then
		nxxx = n7
	endif
!	============================================ Debug End
	call RealSym_Determinant(A(n6),A(n3),A(nxxx),
     &					NStifN,NStifN,NStifN,detK,iOut)
	detKO = detK
	call DumpRealVar(detKO,"Determinant = ",1,iOut)
!	------------------------------------------------------------------ Initialize
!		! Step 3ai: eqn x
	if((iStep.gt.1).and.(iNut==1)) then
		if(Imaginary.NE..TRUE.) Then
			call Calc_ArcLength_Stepm(delLmO,DelLm,
     &							iTermO,iTerRef,iStep,iOut)
		endif
	endif
!		! Step 2a: eqn 7
!		! Step 3aii: eqn 7
	if(bDrill) then
!			call Solve_AxEqB_Drill(A(n6),A(nPLoad),A(ndeltaUi2),
!     &			nStifN,nStifR,nStif3,Iout)
!		else
!	===================
		call Solve_AxEqB(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,nStifN,iOut)
	endif
	if((iStep.gt.1).and.(iNut.gt.1)) then
!		===================
		if(bDrill) then
!			call Solve_AxEqB_Drill(A(n6),A(nGuLam),A(ndeltaUi1),
!     &			nStifN,nStifR,nStif3,Iout)
!		else
			call Solve_AxEqB(A(n6),A(nGuLam),A(ndeltaUi1),
     &			nStifN,nStifN,iOut)
		endif
		call ScaleVector(A(ndeltaUi1),A(ndeltaUi1),-1.D0,nStifN,Iout)
	endif
!		=========================================================
!		===================
	call Compute_StrainEnergy(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,SEnergy,PEnergy,iOut)
!	!------------------------------------------------------------------ Initialize
	if((iStep==0).and.(iNut==0)) then
!		! Step 2b: 
		call Calc_ArcLength_Step1(A(ndeltaUi2),nStifN,
     &					DelLamdaiO,DelLmO,iOut)
!		! Step 2b: eqn 10: At the beginning of each Loadstep Linear Solution
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)		! state
		call Calc_delUi(DelLamdaiO,A(ndeltaUi1),A(ndeltaUi2),
     &					A(ndelUiO),NStifN,iOut)
		DeltaLamdai = ArcLen
		DelLm		= DelLmO
	elseif((iStep.gt.1).and.(iNut==1)) then
!		===================
!		! Step 3aiii: eqn xx
		call Calc_Lamda1_Stepm(A(ndeltaUi2),nStifN,delLamdaiO,
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
	elseif((iStep.gt.1).and.(iNut.gt.1)) then
		return
	endif
!		
	call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!===========================================================================================
	call DumpStringVar("Exit:LoadStep",1,iOut)
	return
	end
