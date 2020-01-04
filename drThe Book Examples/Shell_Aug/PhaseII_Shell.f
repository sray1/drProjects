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
	include 'Augment.h'
!	------------------------------------------
	character*1		sign,pos,neg
	Logical			DontSkip
	LOGICAL			IsUpdateNeeded,
     &			 	ThetaNeedUpdate_STR,bOK
!
	data			pos/'+'/,neg/'-'/
!========================================================================
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	data			pos/'+'/,neg/'-'/
	data			iDebug/0/
!=================================================================================== Phase II: BEG
!	------------------------------------------------------------------- Array sizes
	call Set_WorkArrayPointers()
!	--------------------------------------------------------------------
	if(nElem == 2) Then
		if(iDebug == 1) write(iOut,2006)
		call FormIndexEl_2(A(n2c),nStifEL,iOut)
	endif
!	-------------------------------------|------|----------------- State Vector:Initialize
	call Initialize(iAugRead,iAugWrit)
!	----------------------------------------------------------------------- For Printing End Results	
	write(iOut,1030) 
	call DeformOut_MatLab_ElLoop(Conv,pos,iOut)
!	=============================================================== Augmented Multiplier Method
	if(bAug) then
!		========================
!		call LoadStep_1_iter_1_AUG(iAugRead,iAugWrit)
!	=========================================================== Augment Tapes
		call Initialize_AugmentMethod(iAugRead,iAugWrit,iOut)
!		=================
		bOk = .FALSE.
	endif
!	=============================================================================== LOADSTEP: LOOP
	iDetSChange = 0		! determinant sign change
	do 500 iStep = 0, MaxSteps

  150 continue	! for Imaginary roots	
	DontSkip	= .TRUE.
	Imaginary	= .FALSE.
!	=====================
	call Initialize_2(Iout)
!	=============================================================================== LOOPS:Augment Solution
	do 400 kAugIter = 1, iAugIterMax
!	=========================================================== Augment Tapes
	iTem		= iAugRead
	iAugRead	= iAugWrit
	iAugWrit	= iTem
!	=============================================================================== NEWTON ITER: LOOP
	Rewind iAugRead
	Rewind iAugWrit
	Rewind iOldCon
!
	do 300 inut = 0, MaxIt
!	============================================ Debug
	iPrt = 1
	call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
	call DumpIntegerVar(kAugIter,"kAugIter",iPrt,iOut)
	call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
	iPrt = 0
!	============================================================= initialize
	call LV_Initialize(A(nB),nStifS,Iout)	! Current Load Vector
!		! Step 3ai: eqn x
!	if((iStep.gt.1).and.(iNut==1)) then
	if((iStep.gt.1).and.(iNut==0)) then
		if(Imaginary.NE..TRUE.) Then
			call Calc_ArcLength_Stepm(delLmO,DelLm,
     &							iTermO,iTerRef,iStep,iOut)
		endif
	endif
!	===================						! Stiffness/Solve
	call LoadStep_Aug(iAugRead,iAugWrit)
!	---------------------------------		Save tangent stiffness needed to start over
!												for possible Imaginary root
	if(inut.eq.0) Then
		call StateatStartofIter(A(nxm),A(nxmR),nStifS,1,iOut)			! 1 = Save
	endif
!	-------------------------------------------------------- Debug 
	if((iStep == 2).AND.(iNut == 1)) Then
		abc = 1
	endif
!		-------------------------------------------------------- Debug : End
!	! Step 3biii	
	call LoadParamChange(A(ndeltaUi1),A(ndeltaUi2),A(ndelUiO),	
     &						nStifN,DelLm,Imaginary,
     &					DeltaLamdai1,DeltaLamdai2,aa,bb,cc,iOut,
     &					A(nPLoad),DelLamdaiO)
!		-------------------------------------------------------- Debug 
	call Debug_1(aa,bb,cc,Iout)
!		-------------------------------------------------------- Debug : End
	if(Imaginary) Then
!	--------------------------------- Recover Inverted Tangent STiffness/Residue for the STEP
!			call InvertedTangentStiffness(A(n6),A(n6R),nStifN,2,iOut)		! 2 = Recall
		call StateatStartofIter(A(nxm),A(nxmR),nStifN,2,iOut)			! 2 = Recall
!		-----------------------------------------------			
		DelLm = 0.5D0*DelLm					
		go to 150
	endif
!	! Step 3biv: eqn 8
	call Check_PossibleDisplacement(A(nDelUiO),
     &						A(ndeltaUi1),A(ndeltaUi2),		
     &						A(ndelUip11),A(ndelUip12),NStifN,
     &						DeltaLamdai1,DeltaLamdai2,iOut)
!	! Step 3bv: eqn 11
!		-------------------------------------------------------- Debug 
	call Debug_2(Iout)
!	-------------------------------------------------------- Debug : End
	call Calc_Angles(A(ndelUiO),A(ndelUip11),A(ndelUip12),NStifN,
     &						Th1,Th2,iOut)
	call UpdateIter_Displace_Lambda(Th1,Th2,A(ndelUip11),
     &						A(ndelUip12),	
     &						A(ndelUi),A(ndelUiO),NStifN,DeltaLamdai,
     1						DeltaLamdai1,DeltaLamdai2,cc,bb,iOut)
!	-----------------
!	! Step 3bvi: eqn 9
	call UpdateStep_Displace_Lambda(A(ndelUi),A(ndelUiO),A(nUm),
     &		A(nUmO),NStifN,DeltaLamdai,DelLamdaiO,DelLamdai,inut,iOut)
!		SLamdam		= SLamdam + delLamdaiO 		
!		--------------------------------------------------------- Expand State vector for Support
	call Expand_BezierDisCon(Iout)
!	------------------------------------------------------------------------------- Test Convergence
	call Convergence_Residual(A(nxmO),A(nxm),
     &							nStifS,Conv,inut,iOut)
!	--------------------------------------------------------- Extract END Element DisRotCOntrols
	call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),nStifEL,
     &							nElem,iOut)
	call Compute_uwthetaAtEnd(DelLm,SLamdam+DelLamdai,A(ndelUiEL),
     &							inut,MaxIt,Conv,iOut)
!	=========================================== Strain/AugMult Convergence
	call Check_StrainConstrain_Element_ALL
     &					(iAugRead,iAugWrit,iOldCon,bOK)
!	==========
!	-------------------------
	if(Conv.LE.tol) go to 350
  300	continue
!	------------------------------------ Iteration Limit Hit: Try Cutting ArcLen
	write(iOut,4001) MaxIt
	stop 'ITERATION LIMIT HIT'
!=============================================================================== LOOPS:NEWTON ITER: END
!	------------------------------------ Iteration SUCCESSFUL
  350 continue
!	-------------------------------------------------------------- Check Augment Convergence
!	=========================================== Strain/AugMult Convergence
	call Check_StrainConstrain_Element_ALL
     &					(iAugRead,iAugWrit,iOldCon,bOK)
!	==========
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
 !		=========================================================== transfer to Augment Tapes
		Rewind iOldCon
		do 20 iEL = 1,nElem
!		-----------------------------| Read Current Penalt/Augment/Constraints
		call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &					Nint1,Nint2,iOldCon,iEL,2,iOut)
!		-----------------------------| Write Current Penalt/Augment/ConstraintsConstraints
		call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &			Nint1,Nint2,iAugWrit,iEL,1,iOut)
!		=======================
   20		continue
		if(xKbar.le.xKbyalfa) then
			xKK = xKbar
		endif
	endif
!=============================================================================== LOOPS:Augment Solution: END
  400	continue
!	------------------------------------ Print LoadStep Result
	SLamdam		= SLamdamO + delLamdaiO
	SLamdamO	= SLamdam
!
	sign = pos
	if(detK.LT.zero) sign = neg
!		------------------------------------ Elemental StepDisRot
	call DeformOut_MatLab_ElLoop(Conv,sign,iOut)
!	------------------------------------ Update State for next LoadStep
	DelLmO		= DelLm		
	iTermO		= inut
!=============================================================================== LOOPS:LoadStep: END
  500	continue
!===========================================================================================
 1030	format(/" Step",8x,"Load",8x,"u(L)",12x,"w(L)",9x,"  v(L)  ",3x,
     &        " iter",2x,"convergence"/)
 2006 Format(/2x,"Entering: FormIndexEl_2"/)
 2008 Format(/2x,"Entering: StateVector"/)
 4001 Format(/5x,"ITERATION LIMIT OF",I3," HIT: Back to Drawing Board!"
     &               /)
	end 
