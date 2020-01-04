	Subroutine Solve_AxEqB(A,b,x,LDA,n,iOut)
 
      USE NUMERICAL_LIBRARIES
 
	Implicit Real(kind=8) (a-h,o-z)
	common/LoadStepIter/iStep,iNut,bReset

      REAL(kind = 8)  A       , b   , x
      Dimension		A(LDA,n), b(n), x(n)
C
	Real(kind=8)	Add    
	Dimension		Add(n)
!============================================================== Check each col.
	iPrt = 0
	if(iPrt == 1) then
		call DumpRealMatrix(A,n,n,"Stif_Sol",iPrt,iOut)
	iPrt = 0
		Add = 0.D0
		do 100 j = 1,n
		sum = 0.0 
		do  90 i = 1,n	
		sum = sum + A(i,j)
   90		continue
		Add(j) = sum
  100		continue
		call DumpStringVar("Beg:From:Solve_AxEqB",iPrt,iOut)
		call DumpRealArray(Add,n,"Add_Col_Stiffness",1,iOut)
		call DumpStringVar("End:From:Solve_AxEqB",iPrt,iOut)
	endif
!============================================================== Check each col.
	iPrt = 0
	iPath = 1
	CALL DLSARG (n, A, LDA, b, iPath, X)
!
	iPrt = 1
	iPrt = 0
	if(iStep == 9999.and.iNut == 0) then
!	if(iStep == 0.and.iNut == 0) then
		iPrt = 1
	endif
	if(iPrt == 1) then
		call DumpRealArray(X,n,"Solution(n)",1,iOut)
C                                 Print results
!      CALL DWRRRN ('X', 1, N, X, 1, 0)
!	pause
!		write(iOut,1000)
!		write(iOut,1010) N,(X(i),i = 1,N)
	endif
	iPrt = 0
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Solve_AxEqB"/)
 1010 Format(/2x,"Solved DisplacementControls: 1x"I3/
     &								4(3(2x,F20.15)/) )
	end

	Subroutine RealSym_Determinant(A,Fac,IPVT,LDA,LDFAC,n,det,iOut)
!	The determinant for real symmetric 
	Implicit Real(kind=8) (a-h,o-z)
 
      REAL(kind = 8)  A       ,Fac
      Dimension		A(LDA,n),Fac(LDFAC,LDFAC)
      INTEGER		IPVT(n)
      REAL(kind = 8)  Det1,Det2
!
	iPrt = 0
	if(iPrt == 1) then
		call DumpRealMatrix(A,n,n,"Stif_Sol",iPrt,iOut)
	endif
	iPrt = 0
C                                 Factor A
      CALL DLFTSF (N, A, LDA, FAC, LDA, IPVT)
C                                 Compute the determinant
      CALL DLFDSF (N, FAC, LDA, IPVT, DET1, DET2)
C                                 Print the results
!	Output Only return Matessa for sign check
!	det = det1*(10.D0**Det2)
	det = det1
  100 continue
C
!	The determinant of A is -2.000 * 10**0.
	
!      CALL UMACH (2, NOUT)
!      WRITE (NOUT,99999) DET1, DET2
99999 FORMAT (' The determinant of A is ', F6.3, ' * 10**', F2.0)
	return
      END

	Subroutine PosDefRealSym_Determinant(A,Fac,LDA,LDFAC,n,det,iOut)
!	Real Symmetric Positive Definite
	Implicit Real(kind=8) (a-h,o-z)
 
      REAL(kind = 8)  A       ,Fac
      Dimension		A(LDA,n),Fac(LDFAC,LDFAC)
      REAL(kind = 8)  Det1,Det2
!
      CALL DLFTDS (N, A, LDA, FAC, LDFAC)
C                                 Compute the determinant
      CALL DLFDDS (N, FAC, LDFAC, DET1, DET2)
C                                 Print results
	det = det1*(10.D0**Det2)
  100 continue
C
99999 FORMAT (' The determinant of A is ',F6.3,' * 10**',F2.0)
!
	return	
      END


	Subroutine Factor_ConditionNumber(A,Fac,IPVT,LDA,LDFAC,n,iOut)
 
	Implicit Real(kind=8) (a-h,o-z)
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


	Subroutine Get_EigenValues(A,LDA,N,EVal,iOut)
 
	Implicit Real(kind=8) (a-h,o-z)
      REAL(kind = 8)		A(LDA,n),EVal(N)
!								Compute Eigen-Values
      CALL DEVLSF (N, A, LDA, EVal)
C                                 Print results
!      CALL UMACH (2, NOUT)
!	-------------------------------------------------- number of zero eigenvalues
	iZero = 0
	do i = 1,n
		if(dabs(Eval(i)).LT.1.D-10) iZero = iZero + 1
	end do !i
	iRank = N-iZero

      WRITE (iOut,1000) N,iZero,iRank
      WRITE (iOut,99999) (i,EVal(i),i= 1,N)
!
!
	return	
 1000	format(//
     &         5x,"Size of Global Singular Stiffness Matrix =",i5/
     &         5x,"Number of Zero Eigen-values              =",i5/
     &         5x,"Rank (=Size - Zero Eigen-values          =",i5/)
99999 FORMAT (" The eigen-values..."/3(2x,i3,2x,F24.14) )
      END