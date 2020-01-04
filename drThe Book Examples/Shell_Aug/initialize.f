	subroutine initialize(iAugRead,iAugWrit)
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'Output.h'
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
	data			pos/'+'/,neg/'-'/
	data			iDebug/0/
!=================================================================================== Phase II: BEG
	TRUEE			= .TRUE.
	FALSE			= .FALSE.
!	-------------------------------------|------|----------------- State Vector:Initialize
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
!	=============================================================== Augmented Multiplier Method
	if(bAug) then
!     -------------------------------------------------------------- Augment Initialize
		iAugRead = iAugTape1	! just the other one 
		iAugWrit = iAugTape2	!  
		call Initialize_Penalty(A(nPenalt),Nint1,Nint2,iOut)
		call Initialize_AugMultipliers(A(nAugMul),Nint1,Nint2,iOut)
		call Initialize_Constraints(A(nOldCon),Nint1,Nint2,iOut)
!
		do 7 iEL = 1,nElem
		call PutGetAugMultiplier(A(nPenalt),A(nAugMul),A(nOldCon),
     &				Nint1,Nint2,iAugWrit,iEL,1,iOut)
    7		continue
	endif
!=============================================================================STEP 1 INITIALIZE
		iNut		= 0		!	Set for Curvature Initialization in
		DelLamdaiO  = ArcLen
!===========================================================================================
	iTerRef		= 5
!	---------------
	iDetSChange = 0		! determinant sign change
!	=========
	return
	end 
