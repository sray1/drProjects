	Subroutine Form_Mass_Matrix(W,XM,nS,nD,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	XMass		= Mass matrix = (6x6)  Symmetric
!				= |TMass*I		0              |
!				  |  0		RMass*W_Transpose*W|
!	----------------------------------------------------------------------------- 
!	Inputs
!		nD		= 6
!		nS		= 3
!		W		= (nS,nS) linearized rot. Xformation matrix
!		TMass	= Translational Mass density	
!		RMass	= Rotational Mass density	
!	Outputs 
!		XM		= Mass Matrix: XM(6,6)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'mass.h'

!
	Real(kind=8)	W       ,XM       ,TM       ,RM                
	Dimension		W(nS,nS),XM(nD,nD),TM(nS,nS),RM(nS,nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ TransMassMatrix
	call Form_TranMass_Matrix(TM,TMass,nS,Iout)
!	------------------------------------------------------ RotMassMatrix
	call Form_RotMass_Matrix(W,RM,RMass,nS,Iout)
!	------------------------------------------------------ Translational Mass
	XM = 0.D0
!
	do ix = 1,3
		do jx = 1,3
			XM(ix,jx) = TM(ix,jx)
		end do
	end do
!
	do ix = 1,3
		do jx = 1,3
			XM(ix+nS,jx+nS) = RM(ix,jx)
		end do
	end do
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(XM(i,j),j = 1,nD),i=1,nD)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Translational Mass Matrix XM(6,6)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
