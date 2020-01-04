	subroutine PhaseII_Shell()
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'Output.h'
	include 'CurParams.h'
	include 'Examples.h'
	include 'CurrentElem.h'
	include 'LoadStepIter.h'
	include 'general.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
	include 'material.h'
	include 'geometry.h'
	include 'files.h'
	include 'Scratch.h'
	include 'solve.h'
	include 'LogParams.h'
!	------------------------------------------
	character*1		sign,pos,neg
	Logical			DontSkip
	LOGICAL			IsUpdateNeeded,TRUEE,
     &			 	ThetaNeedUpdate_STR,bReset
!
	data			pos/'+'/,neg/'-'/
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	data			pos/'+'/,neg/'-'/
	data			iDebug/0/
!=================================================================================== Phase II: BEG
	TRUEE			= .TRUE.
	IsUpdateNeeded	= .FALSE.
	bReset			= .FALSE.
	Imaginary       = .FALSE.	
	if(bOpt1) then
	endif	
!		-------------------------------------|------|----------------- Connectivity
!------------------------------------------------------------------- Array sizes
	call Set_WorkArrayPointers()
!--------------------------------------------------------------------
		if(nElem == 2) Then
			if(iDebug == 1) write(iOut,2006)
			call FormIndexEl_2(A(n2c),nStifEL,iOut)
		endif
!		-------------------------------------|------|----------------- State Vector:Initialize
		if(iDebug == 1) write(iOut,2008)
		iStep = 0
		jStep = 0
		SLamdam		= zero
		SLamdamO	= zero
		call Initialize_StateVector(A(nRoCOld),A(nCuCOld),nCInt,iOut)	  
		call Initialize_StateVector(A(nRoKSav),A(nCKKSav),nCInt,iOut)	  
		call Initialize_StateVector(A(nxo),A(nx),nStifS,iOut)	  
		call Initialize_StateVector(A(nxmO),A(nxm),nStifS,iOut)	  
		call LV_Initialize(A(n4),nStifS,Iout)	! state
		call LV_Initialize(A(nBo),nStifS,Iout)	! Old Load Vector for Convergence
		call LV_Initialize(A(nxmO),nStifS,Iout)		! state
		call LV_Initialize(A(nxm),nStifS,Iout)		! state
!----------------------------------------------------------------------- For Printing End Results	
		if (jStep == 1) Then
			write(iOut,1030) 
		endif
!		--------------------------------------------------------- Print Undeformed Shape
!----------------------------------------------------------------------- For Plotting Results	
!------------------------------------------------------------------------- Elemental StepDisRot
		do 5 iEL = 1,nElem
			m1 =n1a
			if(iEL == 2) Then
				m1 =n1b
			elseif(iEL == 3) Then
				m1 =n1c
			endif
!			if(iEL.NE.nElem) then
!				goto 5
!			endif
!			--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
			call DeformOut_MatLab(A(m1),A(ndelUiEL),Conv,pos,
     &				A(nEndwSav),iEL)
    5		continue
!--------------------------------------------------------------
!============================================================================
  100		continue
		if(bReset == .FALSE.) Then
			jStep = iStep + 1
		else
			jStep = iStep
		endif
!===========================================================================================STEP 1 INITIALIZE
		iNut		= 0		!	Set for Curvature Initialization in
!								Get ReferenceInfo in QQ_Quad_Stif
!===========================================================================================STEP 1 INITIALIZE
		DelLamdaiO = ArcLen
		call LoadStep_1_iter_1()
!	-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!	IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!	if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call Update_StepQc(A(nxm),nStifS,A(n1a),nQc,Iout)
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!	endif
!		-------------------------------------------------------- Check for theta update: End
!===========================================================================================
!		-------------------------------------|------|----------------- LOOP:Linearized Solution
		iTerRef		= 5
!		---------------
		iDetSChange = 0		! determinant sign change
		do 500 iStep = jStep, MaxSteps
  150     continue	! for Imaginary roots	
!========================================================================================
!		-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!		IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!		if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!		go to 100
!		endif
!		-------------------------------------------------------- Check for theta update: End
!=============================================================================================
		DontSkip	= .TRUE.
		Imaginary	= .FALSE.
		call LV_Initialize(A(ndelUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)	! state
!		-------------------------------------| Newton Iterations for each LoadStep
		do 300 inut = 1, MaxIt
!		===================
		if(inut.eq.1) Then
!		---------------------------------------------------------------------- Stiffness Matrix
			if(iStep.GT.1) Then
				call LoadStep_n_iter_1()
			endif
!			--------------------------------- Save tangent stiffness needed to start over
!												for possible Imaginary root
!			--------------------------------- Save Inverted Tangent STiffness/Residue for the STEP
!			call InvertedTangentStiffness(A(n6),A(n6R),nStifN,1,iOut)	! 1 = Save
			call StateatStartofIter(A(nxm),A(nxmR),nStifS,1,iOut)			! 1 = Save
!			-----------------------------------------------			
			go to 250
		endif
!		===================
		call LV_Initialize(A(nB),nStifS,Iout)	! Current Load Vector
!		---------------------------------------------------------------------- Stiffness Matrix
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 2)) Then
			abc = 1
		endif
!		-------------------------------------------------------- Debug : End
		call LoadStep_n_iter_m()
!	-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!	IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!	if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call Update_StepQc(A(nxm),nStifS,A(n1a),nQc,Iout)
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!	endif
!		-------------------------------------------------------- Check for theta update: End
!------------------
  250		continue
!------------------
!		-------------------------------------------------------- Debug 
		if((iStep == 2).AND.(iNut == 1)) Then
			abc = 1
		endif
!		-------------------------------------------------------- Debug : End
!		! Step 3biii	
!		call LoadParamChange(A(ndeltaUi1),A(ndeltaUi2),A(ndelUiO),	
!     &						nStifN,DelLm,Imaginary,
!     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut)
		call LoadParamChange(A(ndeltaUi1),A(ndeltaUi2),A(ndelUiO),	
     &						nStifN,DelLm,Imaginary,
!     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut)
     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut,
     &					A(nPLoad),DelLamdaiO)
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 3)) Then
			iPrt = 0
!			call DumpVar(iOut)
			call DumpStringVar("Beg:aftLoadParamChange",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
			call DumpRealVar(DelLm,"DelLm",iPrt,iOut)
	call DumpRealVar(DeltaLamdai1,"DeltaLamdai1",iPrt,iOut)
	call DumpRealVar(DeltaLamdai2,"DeltaLamdai2",iPrt,iOut)
			call DumpRealVar(aa,"aa",iPrt,iOut)
			call DumpRealVar(bb,"bb",iPrt,iOut)
			call DumpRealVar(cc,"cc",iPrt,iOut)
	call DumpRealArray(A(nBFors),nStifEL,"A(nBFors)",iPrt,iOut)
	call DumpRealArray(A(nPLoad),nStifN,"A(nPLoad)",iPrt,iOut)
	call DumpRealArray(A(nGuLam),nStifN,"A(nGuLam)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi1),nStifN,"A(ndeltaUi1)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi2),nStifN,"A(ndeltaUi2)",iPrt,iOut)
	call DumpRealArray(A(ndelUiO),nStifN,"A(ndelUiO)",iPrt,iOut)
			call DumpStringVar("End:aftLoadParamChange",iPrt,iOut)
			iPrt = 0
		endif
!		-------------------------------------------------------- Debug : End
		if(Imaginary) Then
!			DontSkip = .FALSE.
!			Stop 'IIMAGINARY ROOTS'
!			--------------------------------- Recover Inverted Tangent STiffness/Residue for the STEP
!			call InvertedTangentStiffness(A(n6),A(n6R),nStifN,2,iOut)		! 2 = Recall
			call StateatStartofIter(A(nxm),A(nxmR),nStifN,2,iOut)			! 2 = Recall
!			-----------------------------------------------			
			DelLm = 0.5D0*DelLm					
			go to 150
		endif
!		! Step 3biv: eqn 8 part
!			call Calc_deltaUi(delLamdai,A(ndeltaUi1),A(ndeltaUi2),
!     &							A(ndeltaUi),NStifN,iOut)
!		! Step 3biv: eqn 8
		call Check_PossibleDisplacement(A(nDelUiO),
     &						A(ndeltaUi1),A(ndeltaUi2),		
     &						A(ndelUip11),A(ndelUip12),NStifN,
     &						DeltaLamdai1,DeltaLamdai2,iOut)
!		! Step 3bv: eqn 11
!		-------------------------------------------------------- Debug 
		if((iStep == 9999).AND.(iNut == 3)) Then
			iPrt = 0
!			call DumpVar(iOut)
		call DumpStringVar("Beg:aftPossibleDisplacement",iPrt,iOut)
			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
	call DumpRealVar(DeltaLamdai1,"DeltaLamdai1",iPrt,iOut)
	call DumpRealVar(DeltaLamdai2,"DeltaLamdai2",iPrt,iOut)
	call DumpRealArray(A(nDelUiO),nStifN,"A(nDelUiO)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi1),nStifN,"A(ndeltaUi1)",iPrt,iOut)
	call DumpRealArray(A(ndeltaUi2),nStifN,"A(ndeltaUi2)",iPrt,iOut)
	call DumpRealArray(A(ndelUip11),nStifN,"A(ndelUip11)",iPrt,iOut)
	call DumpRealArray(A(ndelUip12),nStifN,"A(ndelUip12)",iPrt,iOut)
	call DumpRealArray(A(ndelUiO),nStifN,"A(ndelUiO)",iPrt,iOut)
			call DumpStringVar("End:aftLoadParamChange",iPrt,iOut)
		endif
!		-------------------------------------------------------- Debug : End
		call Calc_Angles(A(ndelUiO),A(ndelUip11),A(ndelUip12),NStifN,
     &						Th1,Th2,iOut)
		call UpdateIter_Displace_Lambda(Th1,Th2,A(ndelUip11),
     &						A(ndelUip12),	
     &						A(ndelUi),A(ndelUiO),NStifN,DeltaLamdai,
     1						DeltaLamdai1,DeltaLamdai2,cc,bb,iOut)
!-----------------
!  250		continue
!-----------------
!		! Step 3bvi: eqn 9
		call UpdateStep_Displace_Lambda(A(ndelUi),A(ndelUiO),A(nUm),
     &		A(nUmO),NStifN,DeltaLamdai,DelLamdaiO,DelLamdai,inut,iOut)
!		SLamdam		= SLamdam + delLamdaiO 		
!		--------------------------------------------------------- Expand State vector for Support
		call Expand_BezierDispControls_C0(A(nUmO),nStifN,A(nxmO),
     &					nStifC,A(nSx),nSup,iCont,iOut)
		call Expand_BezierDispControls_C0(A(nUm),nStifN,A(nxm),
     &					nStifC,A(nSx),nSup,iCont,iOut)
		call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
		call Expand_BezierDispControls_C0(A(ndelUi),nStifN,A(nx),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!------------------------------------------------------------------------------- Test Convergence
		call Convergence_Residual(A(nxmO),A(nxm),
     &							nStifS,Conv,inut,iOut)
!		--------------------------------------------------------- Extract END Element DisRotCOntrols
		call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),nStifEL,
     &							nElem,iOut)
		call Compute_uwthetaAtEnd(DelLm,SLamdam+DelLamdai,A(ndelUiEL),
     &							inut,MaxIt,Conv,iOut)
!		-------------------------
		if(Conv.LE.tol) go to 400
  300		continue
!		--------------------------------------------------------- Iteration Limit Hit
!		------------------------------------ Try Cutting ArcLen
		write(iOut,4001) MaxIt
		stop 'ITERATION LIMIT HIT'
!		--------------------------------------------------------- Iteration SUCCESSFUL
  400		continue
!		--------------------------------------------------------- Print LoadStep Result
		SLamdam		= SLamdamO + delLamdaiO
		SLamdamO	= SLamdam
!
		sign = pos
		if(detK.LT.zero) sign = neg
!------------------------------------------------------------------------- Elemental StepDisRot
		do 25 iEL = 1,nElem
			m1 =n1a
			if(iEL == 2) Then
				m1 =n1b
			elseif(iEL == 3) Then
				m1 =n1c
			endif
!			if(iEL.NE.nElem) then
!				goto 25
!			endif!			--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
			call DeformOut_MatLab(A(m1),A(ndelUiEL),Conv,sign,
     &							A(nEndwSav),iEL)
   25		continue
!	--------------------------------------------------------------
!		--------------------------------------------------------- Update State for next LoadStep
!		DelLamdaiO	= zero
		DelLmO		= DelLm		
		iTermO		= inut
!========================================================================================
!=============================================================================================
!===========================================================================================
!	-------------------------------------------------------- Check for theta update
!		bReset = .FALSE.
!	IsUpdateNeeded = ThetaNeedUpdate_STR(A(nxm),nStifEL,nQc,Iout)
!	if(IsUpdateNeeded.EQ. TRUEE ) Then
!			call Update_StepQc(A(nxm),nStifS,A(n1a),nQc,Iout)
!			call ResetReference(A(nxmO),A(nxm),nStifS,nQc,
!     &					A(nRoCOld),A(nCuCOld),
!     &					A(nRoKSav),A(nCKKSav),nCInt,Iout)
!		bReset = TRUEE
!	endif
!		-------------------------------------------------------- Check for theta update: End
!===========================================================================================
  500		continue
  998 continue
!===========================================================================================
 1030	format(/" Step",8x,"Load",8x,"u(L)",12x,"w(L)",9x,"  v(L)  ",3x,
     &        " iter",2x,"convergence"/)
 2006 Format(/2x,"Entering: FormIndexEl_2"/)
 2008 Format(/2x,"Entering: StateVector"/)
 4001 Format(/5x,"ITERATION LIMIT OF",I3," HIT: Back to Drawing Board!"
     &               /)
	end 
