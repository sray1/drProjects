	Subroutine Form_TranCent_Matrix(TC,TMass,nS,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	TM		= Translational Mass matrix = TMass*Identity(3x3)  Symmetric
!	----------------------------------------------------------------------------- 
!	Inputs
!		nS		= 3
!		TMass	= Translational Mass density	
!	Outputs 
!		TM		= Tran Mass Matrix: TM(3,3)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'

!
	Real(kind=8)	TC       ,IM                
	Dimension		TC(nS,nS),IM(nS,nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ identity matrix (I)
	IM=0.D0
!	------------------------------------------------------ Translational Mass
	TC = TMass*IM
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(TC(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Translational Centri Matrix TC(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
