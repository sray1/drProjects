	Subroutine Form_RotMass_Matrix(W,RM,RMass,nS,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	S		= Rotational Mass matrix = Io*(W-trans*W)  Symmetric
!	----------------------------------------------------------------------------- 
!	Inputs
!	W			= Rodrigues transformation matrix depends on current Rotation
! 	
!	Outputs 
!		RM		= Rot Mass Matrix: RM(3,3)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'

!
	Real(kind=8)	W       ,RM                
	Dimension		W(nS,nS),RM(nS,nS)
	Real(kind=8)	Io                
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ theta x pTranspose
	RM = RMass*(TRANSPOSE(W))*W
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(RM(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Rotational Mass Matrix RM(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
