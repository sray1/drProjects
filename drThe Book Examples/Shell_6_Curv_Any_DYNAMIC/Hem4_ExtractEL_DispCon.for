	Subroutine Hem4_Extract_DispCon(XS,mStifS,XE,mStifEL,Nel,iOut)
!
	include 'Implicit.h'
!	HARD-CODED FOR A SPECIFIC PROBLEM
!-------------------------
	include 'LoadStepIter.h'
	include 'Scratch.h'
	include 'SizeVar.h'
	include 'Examples.h'
!========================================================================
!	XS(mStifS)	= Solved Bezier Displacement Controls (Input)
!	XE(mStifEL)	= Element Bezier Displacement Controls (Output)	
!	======================================
	real(kind = 8)	XS        ,XE     
	Dimension		XS(mStifS),XE(mStifEL)
	integer i,ii,EL1(mStifEL),EL2(mStifEL)
!--------------------------------------------------------------
	if(nEx == 10.AND.nElem == 4) then
		call PutGetIndxEL(iIndxEL,EL1,mStifEL,Nel,2,iOut)	! 2 = read
		do 10 i = 1,mStifEL
		XE(i) = XS(EL1(i))
   10		continue
		go to 100
	else
!	call Initiate_ExtractionIndex(EL1,EL2,mStifEL,iOut)
	call Initiate_ExtractionIndex(EL1,EL2,mStifEL,iOut)
	endif
!--------------------------------------------------------------
	XE = 0.D0	! initialize
	ii = 0
!
	if (Nel == 1) Then			
		do 20 i = 1,mStifEL
		XE(i) = XS(EL1(i))
   20		continue
	elseif  (Nel == 2) Then
		do 30 i = 1,mStifEL
		XE(i) = XS(EL2(i))
   30		continue
	endif
  100 continue
!
	iPrt = 0
!	if (iPrt == 1) Then
!		write(iOut,1000)
!		write(iOut,1010) Nel,mStifEL,(XE(i),i = 1,mStifEL)
!	endif
	call DumpIntegerVar(iStep,"Step No.",iPrt,iOut)
	call DumpIntegerVar(iNut,"Iteration No.",iPrt,iOut)
	call DumpIntegerVar(Nel,"Element No.",iPrt,iOut)
	call DumpRealArray(XE,mStifEL,"EL DIsp:XE(n)",iPrt,iOut)
!	
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Extract_DispCon"/)
 1010 Format(/2x,"Extracted DisControls for Element ",I2,": 1x",I3/
     &										3(5(2x,F16.4)/) )
	end
