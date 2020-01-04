	subroutine Debug_1(aa,bb,cc,Iout)
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
!	=========
	return
	end 
