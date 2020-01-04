	Subroutine Form_TranMass_Matrix(TM,TMass,nS,Iout)
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
	Real(kind=8)	TM       ,IM                
	Dimension		TM(nS,nS),IM(nS,nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ identity matrix (I)
	IM=0.D0
	IM(1,1) = 1.D0
	IM(2,2) = 1.D0
	IM(3,3) = 1.D0
!	------------------------------------------------------ Translational Mass
	TM = TMass*IM
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(TM(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Translational Mass Matrix TM(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
