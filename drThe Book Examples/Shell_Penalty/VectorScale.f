	Subroutine ScaleVector(A,B,sf,nV,Iout)
!	----------------------------------------------------------------------------- 
!	A,B,C		= column vectorc
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nV)				= vector
!		sf					= scale factor
! 	
!	Outputs 
!		B					= B=sf*A
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A    ,B                     
	Dimension		A(nV),B(nV)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Do it
	do 10 i = 1,nV
	B(i) = sf*A(i)
   10 continue
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Extracted vector..."/2X,3(f10.7,1X))
	end
