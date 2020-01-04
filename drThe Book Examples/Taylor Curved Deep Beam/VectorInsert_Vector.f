	Subroutine VectorInsert_Vector(B,nB,E,nE,nS,Iout)
!	----------------------------------------------------------------------------- 
!	B,E		= column vector
!	----------------------------------------------------------------------------- 
!	Inputs
!		B(nB)				= Big vector
!		nS					= starting index: 0<nS<=nB-nE+1
! 	
!	Outputs 
!		E(nE)				= Inserted vector
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	B    ,E                   
	Dimension		B(nB),E(nE)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Extract
	if (nS.LT.1.AND.nS+nE-1.GT.nB) Then
		stop 'Insertion Limit Problem:nS.LT.1.AND.nS+nE-1.GT.nB'
	endif
!	-----------------------------------
	do 10 i = 1,nE
	B(nS+i-1) = E(i)
   10 continue
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (B(j),j = 1,nB)
		write(Iout,1020) (E(j),j = 1,nE)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big vector..."/2X,3(f10.7,1X))
 1020 format(1X,"Inserted vector..."/2X,3(f10.7,1X))
	end
