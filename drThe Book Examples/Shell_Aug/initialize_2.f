	subroutine initialize_2(Iout)
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'LoadStepIter.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
!========================================================================
		call LV_Initialize(A(ndelUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi),nStifS,Iout)		! state
		call LV_Initialize(A(ndeltaUi1),nStifS,Iout)	! state
!	=========
	return
	end 
