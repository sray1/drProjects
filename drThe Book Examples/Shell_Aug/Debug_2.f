	subroutine Debug_2(Iout)
!-------------------------
	include 'Implicit.h'
!========================================================================
	include 'Blank.h'
	include 'LoadStepIter.h'
	include 'Wpointers.h'
	include 'Addpoints.h'
	include 'SizeVar.h'
!========================================================================
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
	call DumpStringVar("End:aftLoadParamChange",iPrt,iOut)
		endif
!	=========
	return
	end 
