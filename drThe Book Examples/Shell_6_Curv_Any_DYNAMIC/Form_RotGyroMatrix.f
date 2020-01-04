	Subroutine Form_RotGyro_Matrix(W,Wdot,Thetadot,RG,RMass,nS,Iout)
!	----------------------------------------------------------------------------- S Matrix
!
!	RG		= Rotational Gyroscopic matrix 
!			= (W-trans){2*Wdot - W(thetadot)W 
!	----------------------------------------------------------------------------- 
!	Inputs
!	W			= Rodrigues transformation matrix depends on current Rotation
!	Wdot		= rate of Rodrigues transformation matrix depends on current Rotation
!	Thetadot	= rate of Current Rotation: Thetadot(3)
! 	
!	Outputs 
!		RG			= Rot Gyroscopic Matrix: RG(3,3)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'

!
	Real(kind=8)	W       ,Wdot       ,RG                
	Dimension		W(nS,nS),Wdot(nS,nS),RG(nS,nS)
	Dimension		Thetadot(nS),TdS(nS,nS)
	Real(kind=8)	Thetadot    ,TdS                       
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ thetadot-Skew (TD)
	call FormSkew(Thetadot,nS,TdS,Iout)
!---------------------------------------------------------- Gyro
	RG = RMass*(TRANSPOSE(W))*(2*Wdot - W*TdS*W)
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(RG(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Rotational Gyroscopic Matrix RG(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
