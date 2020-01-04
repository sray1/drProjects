	Subroutine FormThetaConstants(t,nS,c1,c2,c1b,c2b,Iout)
!	----------------------------------------------------------------------------- 
!	t		= theta column vector
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
	Real(kind=8)	t                    
	Dimension		t(nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	-----------------------------------------------------------------------------
	t1 = t(1)
	t2 = t(2)
	t3 = t(3)
!
	tL	= sqrt(t1*t1+t2*t2+t3*t3)
!
	if(tL == zero) Then
		c1	= zero
		c2	= zero
		c1b	= zero
		c2b	= zero
		go to 10
	endif

	tL2 = tL*tL
	tL3 = tL*tL2
	ct	= cos(tL)
	st	= sin(tL)
	a	= st/tL
	c1	= (one - ct)/tL2
	c2	= (one - a)/tL2
	c1b	= ((one - tL2*c2) - two*c1)/tL2
	c2b	= (c1 - three*c2)/tL2
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
