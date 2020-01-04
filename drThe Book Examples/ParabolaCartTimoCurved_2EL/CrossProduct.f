	Subroutine CrossProduct(A,B,C)
!	
	Real(kind=8)	A   ,B   ,C      	 
	Dimension		A(3),B(3),C(3)
!
	C(1) = A(2)*B(3) - A(3)*B(2)
	C(2) = A(3)*B(1) - A(1)*B(3)
	C(3) = A(1)*B(2) - A(2)*B(1)
!
	return
	end
