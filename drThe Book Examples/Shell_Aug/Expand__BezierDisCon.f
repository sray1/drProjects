	subroutine Expand_BezierDisCon(Iout)
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'LoadStepIter.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
!========================================================================
	call Expand_BezierDispControls_C0(A(nUmO),nStifN,A(nxmO),
     &				nStifC,A(nSx),nSup,iCont,iOut)
	call Expand_BezierDispControls_C0(A(nUm),nStifN,A(nxm),
     &				nStifC,A(nSx),nSup,iCont,iOut)
	call Expand_BezierDispControls_C0(A(ndelUiO),nStifN,A(nxo),
     &				nStifC,A(nSx),nSup,iCont,iOut)
	call Expand_BezierDispControls_C0(A(ndelUi),nStifN,A(nx),
     &				nStifC,A(nSx),nSup,iCont,iOut)
!	=========
	return
	end 
