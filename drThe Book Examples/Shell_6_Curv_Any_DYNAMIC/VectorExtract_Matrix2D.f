	Subroutine VectorExtract_Matrix2D(B,nRb,nCb,E,nRe,nCe,nRs,nCs,
     &                                               	Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		B(nRb,nCb)			= Big Matrix
!		nRs					= starting Row index: 0<nRs<=nRb-nRe+1
!		nCs					= starting Col index: 0<nCs<=nCb-nCe+1
! 	
!	Outputs 
!		E(nRe,nCe)			= Extracted Matrix
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	B         ,E                   
	Dimension		B(nRb,nCb),E(nRe,nCe)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	----------------------------------------------------------------------------- Extract
	if ( (nRs.LT.1.OR.nRs+nRe-1.GT.nRb). OR.
     &     (nCs.LT.1.OR.nCs+nCe-1.GT.nCb)     ) Then
		stop 'Extraction Limit Problem in Extract_Matrix2D'
	endif
!	-----------------------------------
	do 10 i = 1,nRe
	do 10 j = 1,nCe
	E(i,j) = B(nRs+i-1,nCs+j-1)
   10 continue
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) ((B(i,j),j = 1,nCb),i = 1,nRb)
		write(Iout,1020) ((E(i,j),j = 1,nCe),i = 1,nRe)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Big Matrix..."/2X,(8f10.7,1X))
 1020 format(1X,"Extracted Matrix..."/2X,(8f10.7,1X))
	end
