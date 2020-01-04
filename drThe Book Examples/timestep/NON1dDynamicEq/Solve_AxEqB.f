	Subroutine Solve_AxEqB(A,b,x,LDA,n,iOut)
 
      USE NUMERICAL_LIBRARIES
 
	Implicit Real(kind=8) (a-h,o-z)
	common/LoadStepIter/iStep,iNut,bReset

      REAL(kind = 8)  A       , b   , x
      Dimension		A(LDA,n), b(n), x(n)
C
	Real(kind=8)	Add    
	Dimension		Add(n)
!
	iPrt = 0
	iPath = 1
	CALL DLSARG (n, A, LDA, b, iPath, X)
!
	iPrt = 1
	iPrt = 0
!
!		write(iOut,1000)
!		write(iOut,1010) N,(X(i),i = 1,N)
	iPrt = 0
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Solve_AxEqB"/)
 1010 Format(/2x,"Solved DisplacementControls: 1x"I3/
     &								4(3(2x,F20.15)/) )
	end

