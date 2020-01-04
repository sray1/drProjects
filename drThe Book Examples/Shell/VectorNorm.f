	Subroutine VectorNorm(A,xNorm,nV,Iout)
!	----------------------------------------------------------------------------- 
!	A		= column vectorc
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nV)				= vector
! 	
!	Outputs 
!		xNorm				=||A||
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A                      
	Dimension		A(nV)
	DATA zero/0.D0/ 
!	----------------------------------------------------------------------------- Do it
	sum = zero
	do 10 i = 1,nV
	sum = sum + A(i)*A(i)
   10 continue
	xNorm = dsqrt(sum)
!----------------------------------------------------------
	return
	end
