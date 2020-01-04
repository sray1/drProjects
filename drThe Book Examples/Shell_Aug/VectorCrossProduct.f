	Subroutine CrossProduct(A,B,C,Iout)
!	----------------------------------------------------------------------------- 
!	A,B,C		= column vectorc
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(3)				= vector
!		B(3)				= vector
! 	
!	Outputs 
!		C(3)				= A cross B
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A    ,B    ,C                  
	Dimension		A(3),B(3),C(3)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Do it
	C(1) = A(2)*B(3) - A(3)*B(2)
	C(2) = A(3)*B(1) - A(1)*B(3)
	C(3) = A(1)*B(2) - A(2)*B(1)
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Extracted vector..."/2X,3(f10.7,1X))
	end
