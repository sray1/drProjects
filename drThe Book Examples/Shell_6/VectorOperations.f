	Subroutine AddVectors(A,B,C,dot,nV,iOp,Iout)
!	----------------------------------------------------------------------------- 
!	A,B,C		= column vectorc
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nV)				= vector
!		B(nV)				= vector
!		iOp					= operation type
! 	
!	Outputs 
!		iOp					= 1: add	C=A+B
!							= 2: sub	C=A-B
!							= 3: dot	dot=A dot B
!							= 4: cross	C=A cross B
!							= 5: norm	dot=||A||
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
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Extracted vector..."/2X,3(f10.7,1X))
	end
