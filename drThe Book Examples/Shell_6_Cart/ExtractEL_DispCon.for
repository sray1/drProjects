	Subroutine Extract_DispCon(XS,nStifS,XE,nStifEL,Nel,iOut)
!
!	HARD-CODED FOR A SPECIFIC PROBLEM
!-------------------------
	include 'Implicit.h'
	include 'LoadStepIter.h'
!========================================================================
!	XS(nStifS)	= Solved Bezier Displacement Controls (Input)
!	XE(nStifEL)	= Element Bezier Displacement Controls (Output)	
!	======================================
	real(kind = 8)	XS        ,XE     
	Dimension		XS(nStifS),XE(nStifEL)
	integer i,ii,EL1(nStifEL),EL2(nStifEL)
!--------------------------------------------------------------
!	call Initiate_ExtractionIndex(EL1,EL2,nStifEL,iOut)
	call Initiate_ExtractionIndex(EL1,EL2,nStifEL,iOut)
!--------------------------------------------------------------
	XE = 0.D0	! initialize
	ii = 0
!
	if (Nel == 1) Then			
		do 20 i = 1,nStifEL
		XE(i) = XS(EL1(i))
   20		continue
	elseif  (Nel == 2) Then
		do 30 i = 1,nStifEL
		XE(i) = XS(EL2(i))
   30		continue
	endif
  100 continue
!
	iPrt = 0
!	if (iPrt == 1) Then
!		write(iOut,1000)
!		write(iOut,1010) Nel,nStifEL,(XE(i),i = 1,nStifEL)
!	endif
	call DumpIntegerVar(iStep,"Step No.",iPrt,iOut)
	call DumpIntegerVar(iNut,"Iteration No.",iPrt,iOut)
	call DumpIntegerVar(Nel,"Element No.",iPrt,iOut)
	call DumpRealArray(XE,nStifEL,"EL DIsp:XE(n)",iPrt,iOut)
!	
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Extract_DispCon"/)
 1010 Format(/2x,"Extracted DisControls for Element ",I2,": 1x",I3/
     &										3(5(2x,F16.4)/) )
	end
