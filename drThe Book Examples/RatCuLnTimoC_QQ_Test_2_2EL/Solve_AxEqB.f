	Subroutine Solve_AxEqB(A,b,x,LDA,n,iOut)
 
      USE NUMERICAL_LIBRARIES
 

      REAL(kind = 8)  A       , b   , x
      Dimension		A(LDA,n), b(n), x(n)
C
!     CALL DLSLSF (n, A, LDA, b, x)
!	CALL DLSLRG (N, A, LDA, B, IPATH, X)
!	CALL DLSLRG (n, A, LDA, b, 1, X)
	CALL DLSARG (n, A, LDA, b, 1, X)


C                                 Print results
!      CALL DWRRRN ('X', 1, N, X, 1, 0)
!	pause
	write(iOut,1000)
	write(iOut,1010) N,(X(i),i = 1,N)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Solve_AxEqB"/)
 1010 Format(/2x,"Solved DisplacementControls: 1x"I3/
     &								4(3(2x,F20.4)/) )
	end


	Subroutine Factor_Determinant(A,b,x,Fac,LDA,LDFAC,n,iOut)
 
      REAL(kind = 8)  A       , b   , x   ,Fac
      Dimension		A(LDA,n), b(n), x(n),Fac(LDFAC,LDFAC)
      REAL(kind = 8)  Det1,Det2
!
      CALL DLFTDS (N, A, LDA, FAC, LDFAC)
C                                 Compute the determinant
      CALL DLFDDS (N, FAC, LDFAC, DET1, DET2)
C                                 Print results
      CALL UMACH (2, NOUT)
      WRITE (NOUT,99999) DET1, DET2
C
99999 FORMAT (' The determinant of A is ',F6.3,' * 10**',F2.0)
!
	return	
      END


	Subroutine Factor_ConditionNumber(A,Fac,IPVT,LDA,LDFAC,n,iOut)
 
      REAL(kind = 8)  A       ,IPVT    , x   ,Fac
      Dimension		A(LDA,n),IPVT(n) , x(n),Fac(LDFAC,LDFAC)
      REAL(kind = 8)  RCOND
!								Compute Condition Number
      CALL DLFCSF (N, A, LDA, FAC, LDFAC,IPVT,RCOND)
C                                 Print results
      CALL UMACH (2, NOUT)


      WRITE (iOut,99999) RCOND,1.0E0/RCOND,DLOG10(1.0E0/RCOND)
!
99999 FORMAT (' The RCond = ',F10.5,/,'L1 Condition Number = ',F10.3,/,
     1		'logbase10(Condition Number) = ',F10.3)
!
	return	
      END