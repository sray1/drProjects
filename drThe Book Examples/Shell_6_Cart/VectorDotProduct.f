	Subroutine DotProduct(A,B,dot,nV,Iout)
!	----------------------------------------------------------------------------- 
!	A,B		= column vectors
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nV)				= vector
!		B(nV)				= vector
! 	
!	Outputs 
!		dot=A dot B
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A    ,B    ,C                  
	Dimension		A(nV),B(nV),C(nV)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Do it
	dot = zero
	do 10 i = 1,nV
	dot = dot + A(i)*B(i)
   10 continue
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Extracted vector..."/2X,3(f10.7,1X))
	end
