	subroutine PhaseII_Shell_NEWTON()
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
!		-------------------------------------|------|----------------- Connectivity
!------------------------------------------------------------------- Array sizes
	call Set_WorkArrayPointers()
!--------------------------------------------------------------------
	if(nEx == 10.AND.nElem == 4) then
		do i = 1,4
			call FormIndex_ELEM_Hem(A(n2c),nStifEL,i,iOut)
		end do ! i
	else
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
		if (jStep == 0) Then
			write(iOut,1030) 
		endif
!		--------------------------------------------------------- Print Undeformed Shape
!----------------------------------------------------------------------- For Plotting Results	
!------------------------------------------------------------------------- Elemental StepDisRot
		do 5 iEL = 1,nElem
			m1 =n1a
!			--------------------------------------------------------- 
			call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),	!Extract DisRotCOntrols
     &			nStifEL,iEL,iOut)
			call DeformOut_MatLab(A(m1),A(ndelUiEL),Conv,pos,
     &				A(nEndwSav),iEL)
    5		continue
!--------------------------------------------------------------
!===========================================================================================STEP 1 INITIALIZE
!		call LoadStep_1_iter_1()
		call LoadStep_Newton()
!------------------------------------------------------------------------------- Test Convergence
		call Convergence_Residual_NEWTON(A(nxmO),A(nxm),
     &							nStifS,Conv,inut,iOut)
!		--------------------------------------------------------- Extract END Element DisRotCOntrols
	if(nEx == 10.AND.nElem == 4) then
		do jel = 1,2
		call Hem4_Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),nStifEL,
     &							jel,iOut)
		if(bPrint) then
			call Hem4_Compute_uwthetaAtEnd(DelLm,ArcLen,
     &		A(ndelUiEL),inut,MaxIt,Conv,jel,iOut)
		endif
		end do !jel
	else
		call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),nStifEL,
     &							nElem,iOut)
		if(bPrint) then
		call Compute_uwthetaAtEnd(DelLm,ArcLen,
     &		A(ndelUiEL),inut,MaxIt,Conv,iOut)
		endif
	endif
!		-------------------------------------|------|----------------- LOOP:Linearized Solution
		iTerRef		= 7
!		---------------
		iDetSChange = 0		! determinant sign change
		do 500 iStep = 1, MaxSteps

	if(nEx == 10.AND.nElem == 1) then

!		======================================================= 1x1 Quintic
 				if(iStep == 5) delLmO = 5.
 				if(iStep == 7) delLmO = 10.
 				if(iStep == 15) delLmO = 20.
 				if(iStep == 29) delLmO = 10.
!		======================================================= 1x1 Quintic END

	elseif(nEx == 10.AND.nElem == 4) then

!		======================================================= 2x2 Quintic
 				if(iStep == 5) delLmO = 5.
! 				if(iStep == 7) delLmO = 10.
 				if(iStep == 29) delLmO = 10.
 				if(iStep == 55) delLmO = 5.
 				if(iStep == 60) delLmO = 3.
 				if(iStep == 75) delLmO = 5.
!		======================================================= 2x2 Quintic END
	endif

!		-------------------------------------| Newton Iterations for each LoadStep
		do 300 inut = 2, MaxIt
!		===================
!		-------------------------------------------------------- Debug : End
		call LoadStep_n_iter_m_NEWTON()
!		-------------------------------------------------------- Check for theta update: End
!		-------------------------------------------------------- Test Convergence
		call Convergence_Residual_NEWTON(A(nxmO),A(nxm),
     &							nStifS,Conv,inut,iOut)
!		--------------------------------------------------------- Extract END Element DisRotCOntrols
	if(nEx == 10.AND.nElem == 4) then
		do jel = 1,2
		call Hem4_Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),nStifEL,
     &							jel,iOut)
		if(bPrint) then
			call Hem4_Compute_uwthetaAtEnd(DelLm,ArcLen,
     &		A(ndelUiEL),inut,MaxIt,Conv,jel,iOut)
		endif
		end do !jel
	else
		call Extract_DispCon(A(nxm),nStifS,A(ndelUiEL),nStifEL,
     &							nElem,iOut)
		if(bPrint) then
		call Compute_uwthetaAtEnd(DelLm,ArcLen,
     &		A(ndelUiEL),inut,MaxIt,Conv,iOut)
		endif
	endif
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
