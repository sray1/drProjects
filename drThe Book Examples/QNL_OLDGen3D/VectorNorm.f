	Subroutine VectorNorm(A,xNorm,nV,Iout)
!	----------------------------------------------------------------------------- 
!	A		= column vectorc
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nV)				= vector
!		B(nV)				= vector
!		iOp					= operation type
! 	
!	Outputs 
!		xNorm =||A||
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A    ,B    ,C                  
	Dimension		A(nV),B(nV),C(nV)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Do it
	sum = zero
	do 10 i = 1,nV
	sum = sum + A(i)*A(i)
   10 continue
	xNorm = dsqrt(sum)
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Extracted vector..."/2X,3(f10.7,1X))
	end
