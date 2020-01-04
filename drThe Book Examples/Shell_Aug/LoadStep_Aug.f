	Subroutine LoadStep_Aug(iAugRead,iAugWrit)
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
!	------------------------------------------------------------------- Stiffness and Load
	call FormStiffness_Load_Aug(iAugRead,iAugWrit)
!	------------------------------------------------------------------- Solve:Current Iteration
	call Solve_CurrentIteration()
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
!	elseif((iStep.gt.1).and.(iNut==1)) then
	elseif((iStep.gt.0).and.(iNut==0)) then
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
!	elseif((iStep.gt.1).and.(iNut.gt.1)) then
	elseif((iStep.gt.0).and.(iNut.gt.0)) then
		return
	endif
!		
	call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &					nStifC,A(nSx),nSup,iCont,iOut)
!===========================================================================================
	call DumpStringVar("Exit:LoadStep",1,iOut)
	return
	end
