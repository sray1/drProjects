	Subroutine TensorProduct(A,B,AB,nV,Iout)
!	----------------------------------------------------------------------------- 
!	A,B		= column vectors
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nV)				= vector
!		B(nV)				= vector
! 	
!	Outputs 
!		AB=A B_transpose	= matrix(nV,nV)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A    ,B    ,AB                  
	Dimension		A(nV),B(nV),AB(nV,nV)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Do it
	do 10 i = 1,nV
	do 10 j = 1,nV
	AB(i,j) = A(i)*B(j)
   10 continue
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Extracted vector..."/2X,3(f10.7,1X))
	end
