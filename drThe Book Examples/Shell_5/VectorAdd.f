	Subroutine VectorAdd(A,B,C,nV,Iout)
!	----------------------------------------------------------------------------- 
!	A,B,C		= column vectorc
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nV)				= vector
!		B(nV)				= vector
! 	
!	Outputs 
!		C					= A+B
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A    ,B    ,C                  
	Dimension		A(nV),B(nV),C(nV)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Do it
	do 10 i = 1,nV
	C(i) = A(i) + B(i)
   10 continue
!	----------------------------------------------------------
	return
	end
