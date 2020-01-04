! This example solves a linear system of equations.
! This is the simplest use of lin_sol_gen. 
! The equations are generated using a matrix of random numbers, 
! and a solution is obtained corresponding to a random right-hand side matrix. 
! Also, see operator_ex01 for this example using the operator notation.
	Subroutine Solve_AxEqB(A,b,n,nFc)
 
      use lin_sol_gen_int 
      use rand_gen_int 
      use error_option_packet 
 
      implicit none 
  
 
      integer, parameter :: n=32 
      real(kind(1e0)), parameter :: one=1e0 
      real(kind(1e0)) err 
      real(kind(1e0)) A(n,n), b(n,n), x(n,n), res(n,n), y(n**2) 
 
! Generate a random matrix. 
      call rand_gen(y) 
      A = reshape(y,(/n,n/)) 
 
! Generate random right-hand sides. 
      call rand_gen(y) 

      b = reshape(y,(/n,n/)) 
 
! Compute the solution matrix of Ax=b. 
      call lin_sol_gen(A, b, x) 
 
! Check the results for small residuals. 
      res = b - matmul(A,x) 
      err = maxval(abs(res))/sum(abs(A)+abs(b)) 
      if (err <= sqrt(epsilon(one))) then 
         write (*,*) 'Example 1 for LIN_SOL_GEN is correct.' 
      end if 
 
      end  


In this example, we obtain the approximate first derivative of the function

f(x) = -2 sin(3x/2)

at the point x = 2.
      INTEGER    KORDER, NCOUNT, NOUT

      REAL       BGSTEP, DERIV, DERV, FCN, TOL, X
      EXTERNAL   DERIV, FCN, UMACH
C                                 Get output unit number
      CALL UMACH (2, NOUT)
C
      X      = 2.0
      BGSTEP = 0.2
      TOL    = 0.01
      KORDER = 1
      NCOUNT = 1
      DERV   = DERIV(FCN,KORDER,X,BGSTEP,TOL)
      WRITE (NOUT,99999) DERV
99999 FORMAT (/, 1X, 'First derivative of FCN is ', 1PE10.3)
      END
C
      REAL FUNCTION FCN (X)
      REAL       X
      REAL       SIN
      INTRINSIC  SIN
      FCN = -2.0*SIN(1.5*X)
      RETURN
      END

Output

First derivative of FCN is  2.970E+00










