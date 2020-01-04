	Subroutine Vector2Dim(A,B,nV,Iout)
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
	Dimension		A(nV,1),B(nV)
!	----------------------------------------------------------------------------- Do it
	do 10 i = 1,nV
	A(i,1) = B(i)
   10 continue
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Extracted vector..."/2X,3(f10.7,1X))
	end
