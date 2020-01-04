	Subroutine FormSkew(t,nS,st,Iout)
!	----------------------------------------------------------------------------- 
!	t		= column vector
!	----------------------------------------------------------------------------- 
!	Inputs
!		t				= t(3)
! 	
!	Outputs 
!		st				= skew[t]
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	t    ,st                   
	Dimension		t(nS),st(nS,nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	-----------------------------------------------------------------------------
	t1 = t(1)
	t2 = t(2)
	t3 = t(3)
!
	st		= zero
	st(1,2) = -t3
	st(2,1) = t3
	st(1,3) = t2
	st(3,1) = -t2
	st(2,3) = -t1
	st(3,2) = t1
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (t(j),j = 1,nS)
		write(Iout,1020) (i,(st(i,j),j = 1,nS),i=1,nS)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current vector..."/2X,3(f10.7,1X))
 1020 format("skew(t) Matrix st(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
