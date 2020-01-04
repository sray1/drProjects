	Subroutine FormThetaConstants(t,nS,c1,c2,c1b,c2b,Iout)
!	----------------------------------------------------------------------------- 
!	t		= thetaRotation column vector
!	tL		= sqrt(t(1)*t(1)+t(2)*t(2)+t(3)*t(3))
!	tL2		= tL*tL
!	tL3		= tL*tL2
!	c1		= (1-cos(tL))/tL2
!	c2		= (tL-sin(tL))/tL3
!	c1Bar	= ((1-tL2*c2) - 2*c1)/tL2
!	c2Bar	= (c1 - 3*c2)/tL2
!	----------------------------------------------------------------------------- 
!	Inputs
!		t				= Current Rotation: t(3)
! 	
!	Outputs 
!		constants		= c1, c2, c1Bar, c2Bar
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!==========================================		
	include 'LoadStepIter.h'
!	common/LoadStepIter/iStep,iNut,bReset
!==========================================		
	Real(kind=8)	t                    
	Dimension		t(nS)
!==========================================		
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,six/6.0D0/ 
!	-----------------------------------------------------------------------------
	t1 = t(1)
	t2 = t(2)
	t3 = t(3)
!--------------------------------------------------------------------------- check for theta = 0
	tL	= dsqrt(t1*t1+t2*t2+t3*t3)
!
	if(tL == zero) Then
!		in actuality:	c1->half and c2->one-sixth
!						but product terms with theta and thetasqured->zero
!						similar argument for c1b and c2b
		c1	= zero
		c2	= zero
		c1b	= zero
		c2b	= zero
		go to 10
	endif
!--------------------------------------------------------------------------- check end
	tL2 = tL*tL
	tL3 = tL*tL2
	ct	= dcos(tL)
	st	= dsin(tL)
	c1	= (one - ct)/tL2
	c2	= (tL - st)/tL3
	c1b	= ((one - tL2*c2) - two*c1)/tL2
	c2b	= (c1 - three*c2)/tL2
!	===================================================================== Debug
!		if((iStep == 2).AND.(iNut == 1)) Then
!			iPrt = 1
!			call DumpStringVar("Beg:FormThetaConstants",iPrt,iOut)
!			call DumpIntegerVar(iStep,"iStep",iPrt,iOut)
!			call DumpIntegerVar(iNut,"iNut",iPrt,iOut)
!			call DumpRealArray(t,3,"Rotation",iPrt,iOut)
!			call DumpRealVar(c1,"c1",iPrt,iOut)
!			call DumpRealVar(c2,"c2",iPrt,iOut)
!			call DumpRealVar(c1b,"c1b",iPrt,iOut)
!			call DumpRealVar(c2b,"c2b",iPrt,iOut)
!			call DumpStringVar("End:FormThetaConstants",iPrt,iOut)
!		endif
!	===================================================================== Debug : End
!---------------------------------------------------------- Write:
   10	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (t(j),j = 1,3),c1,c2,c1b,c2b
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current Theta vector..."/
     &        2X,3(f10.7,1X)/
     &		1X,"Constants..."/
     &		2X,"c1 = ",F20.7,2X,"c2 = ",F20.7/
     &		2X,"c1b = ",F20.7,2X,"c2b = ",F20.7)
	end
