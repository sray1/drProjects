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
	return

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
!      CALL UMACH (2, NOUT)
!      WRITE (NOUT,99999) DET1, DET2
      WRITE (iOut,99999) DET1, DET2
C
99999 FORMAT (' The determinant of A is ',F6.3,' * 10E',F4.0)
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
!
	Subroutine Stiffness_EigenValues(N,A,B,LDA,EVAL,iOut)
 
      REAL(kind = 8)  A       ,B       ,EVAL   ,sum
      Dimension		A(LDA,n),B(LDA,n),EVAL(n)
!								Compute EigenValues
C                                 Find eigenvalues of AtranA
      CALL DEVLSF (N, A, LDA, EVAL)
      Write(iOut,1000) N, (EVAL(i),i = 1,N)
C                                 Find determinant of A
	sum = 1.0D0
	do 5 k = 1,N
    5	sum = sum*Eval(k)
	write(iOut,4000) sum
!------------------------------------------------------
!	Stiffness L2 Norm: sqrt(max Eigen) of A_transpose_A
!------------------------------------------------------
	do 20 i = 1,N
	do 20 j = 1,N
	sum = 0.0D0
	do 10 k = 1,N
   10	sum = sum + A(k,i)*A(k,j)
   20	B(i,j) = sum
C                                 Find eigenvalues of AtranA
      CALL DEVLSF (N, B, LDA, EVAL)
      Write(iOut,2000) N, (EVAL(i),i = 1,N)
C                                 Print Norm
	write(iOut,3000) dsqrt(Eval(1))
!
 1000 FORMAT (/5X,i3,' The EigenValues of K '/(2X,8F10.5))
 2000 FORMAT (/5X,i3,' The EigenValues of KtransK '/(2X,8F10.5))
 3000 FORMAT (/5X,'The L2 Norm of Stiffness Matrix   = ' F10.5/
     &        5X,'(Sqrt(Max.EigenValue) of KtransK)'   )
 4000 FORMAT (/5X,'Determinant of K   = ' G20.5/)

!
	return	
      END