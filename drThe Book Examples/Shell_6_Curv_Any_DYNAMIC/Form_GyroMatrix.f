	Subroutine Form_Gyro_Matrix(W,Wd,Td,XG,nS,nD,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	XMass		= Mass matrix = (6x6)  Symmetric
!				= |TMass*I		0              |
!				  |  0		RMass*W_Transpose*W|
!	----------------------------------------------------------------------------- 
!	Inputs
!		nD		= 6
!		nS		= 3
!		W		= (nS,nS)	linearized rot. Xformation matrix
!		Td		= (nS)		Current ThetaDot
!		TMass	= Translational Mass density	
!		RMass	= Rotational Mass density	
!	Outputs 
!		XM		= Mass Matrix: XM(6,6)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'mass.h'

!
	Real(kind=8)	W       ,Wd       ,XG       ,TG       ,RG                
	Dimension		W(nS,nS),Wd(nS,nS),XG(nD,nD),TG(nS,nS),RG(nS,nS)
	Real(kind=8)	Td      
	Dimension		Td(nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ TransGyroMatrix
	call Form_TranGyro_Matrix(TG,TMass,nS,Iout)
!	------------------------------------------------------ RotGyroMatrix
	call Form_RotGyro_Matrix(W,Wd,Td,RG,RMass,nS,Iout)
!	------------------------------------------------------ Gyro Matrix
	XG = 0.D0
!
	do ix = 1,3
		do jx = 1,3
			XG(ix,jx) = TG(ix,jx)
		end do
	end do
!
	do ix = 1,3
		do jx = 1,3
			XG(ix+nS,jx+nS) = RG(ix,jx)
		end do
	end do
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(XG(i,j),j = 1,nD),i=1,nD)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Gyroscopic Matrix XG(6,6)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
