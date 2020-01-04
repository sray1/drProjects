	Subroutine LoadStep_1_iter_1_AUG(iAugRead,iAugWrit)
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
	call DumpStringVar("Enter:LoadStep_1_iter_1",1,iOut)
!		---------------------------------------------------------------------- Stiffness Matrix
!		----|------|----------------- Surface/End Load Vector
!		Get Load Vector 
!		call Set_ExtLoad_Y(A(n5),3,Iout)
		call LV_EndLoad(A(n5),A(n5V),nLod,A(n7),nStifS,Iout)
!================================================================================
		iAugIter = zero
		bOk = .FALSE.
		do 100 iCon = 1,iAugIterMax
!	=========================================================== Augment Tapes
	iTem		= iAugRead
	iAugRead	= iAugWrit
	iAugWrit	= iTem
!	if (iAugRead == iAugTape1) then
!		iAugRead = iAugTape2
!		iAugWrit = iAugTape1
!	elseif (iAugRead == iAugTape2) then
!		iAugRead = iAugTape1
!		iAugWrit = iAugTape2
!	endif
!
		Rewind iAugRead
		Rewind iAugWrit
		Rewind iOldCon
!	=========================================================== Augment Tapes end
		do 10 iEL = 1,nElem
!	-------------------------------------| Read Current Augment Multiplier/Constraints
	call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &			Nint1,Nint2,iAugRead,iEL,2,iOut)
!	-------------------------------------| :
			iCEL = iEL 
!			-------------------------------------| Form Stiffness Matrix: 
			m2 =n2a
	if(bOpt1) then
!		call Opt1_Quad_QQ_STIF_Aug(A(nAugMul),A(nOldCon),
		call Opt1_Quad_QQ_STIF(
     &			A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	else
		call Quad_QQ_STIF_Aug(A(nPenalt),A(nAugMul),A(nOldCon),
     &			A(nRoCOld),A(nCuCOld),
     &			A(nRoKSav),A(nCKKSav),
     &			A(ndelUiEL),iEL,A(nDMat),A(nBMat),A(nTMat),
     &			A(m2),A(nBfors),A(nStifK),nStifEL,Iout,Trace)
	endif
!	-------------------------------------| :
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
!
!			Assemble Ist Elem:nBFors only has Residual & body force integral part
!
			m7 = n7
			if(iEL.GT.1) Then
				m7 = nBFors
			endif
			call Assemble_Load(A(n2c),A(m7),
     &    		nStifEL,A(nB),nStifS,iEL,Iout)
   10		continue
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
!		-----------|------|----------------- NonSingular Stiffness
!		Add Supports: rigid body Out
!
		call Extract_NonSingularStif(A(n2),nStifC,nStifC,A(n6),nStifN,
     &								A(nSx),nSup,iCont,iOut)
!		----------|------|----------------- Supported Load Vector & State Vector
!		Add Supports: rigid body Out
!
		call Extract_ContractedLoadVector(A(n7),nStifC,A(nPLoad),	!P-EndLoad
     &						nStifN,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Solve:Current Iteration
!		! Step 2a: eqn 7
		if(bDrill) then
!			call Solve_AxEqB_Drill(A(n6),A(nPLoad),A(ndeltaUi2),
!     &			nStifN,nStifR,nStif3,Iout)
!		else
			call RealSym_Determinant(A(n6),A(n3),A(n7),
     &					NStifN,NStifN,NStifN,detK,iOut)
			detKO = detK
			call DumpRealVar(detKO,"Determinant = ",1,iOut)
!			===================
			call Solve_AxEqB(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,nStifN,iOut)
		endif
!		===================
		call Compute_StrainEnergy(A(n6),A(nPLoad),A(ndeltaUi2),
     &			nStifN,SEnergy,PEnergy,iOut)
!	-------------------------------------------------------------- Check Augment Convergence
!		=========================================== Strain/AugMult Convergence
		call Check_StrainConstrain_Element_ALL
     &					(iAugRead,iAugWrit,iOldCon,bOK)
!		==========
		if(bOK == .TRUE.) then
			Exit
		endif
!	-------------------------------------------------------------- Check xKbar
		xKbyalfa = xKK/alfa
		if(xKbar.ge.xKK) then
			call Reset_Penalty_ALL
     &					(iAugRead,iAugWrit,iOldCon,iOut)
			xKK = xKbar
			
		else
 !			=========================================================== transfer to Augment Tapes
			Rewind iOldCon
			do 20 iEL = 1,nElem
!			-----------------------------| Read Current Penalt/Augment/Constraints
			call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &					Nint1,Nint2,iOldCon,iEL,2,iOut)
!			-----------------------------| Write Current Penalt/Augment/ConstraintsConstraints
			call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &			Nint1,Nint2,iAugWrit,iEL,1,iOut)
!			=======================
   20			continue
			if(xKbar.le.xKbyalfa) then
				xKK = xKbar
			endif
		endif
  100 continue
!	!------------------------------------------------------------------ Initialize
!		! Step 2a: eqn 7
!		call Calc_deltaUi2(A(n6),A(nPLoad),A(ndeltaUi2),
!     &						nStifN,iOut)
!		! Step 2b: 
		call Calc_ArcLength_Step1(A(ndeltaUi2),nStifN,
     &					DelLamdaiO,DelLmO,iOut)
!		! Step 2b: eqn 10: At the beginning of each Loadstep Linear Solution
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)		! state
		call Calc_delUi(DelLamdaiO,A(ndeltaUi1),A(ndeltaUi2),
     &					A(ndelUiO),NStifN,iOut)
		DeltaLamdai = ArcLen
		DelLm		= DelLmO	
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!===========================================================================================
	call DumpStringVar("Exit:LoadStep_1_iter_1",1,iOut)
	return
	end
