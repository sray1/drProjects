	Subroutine Form_AngularVEL_Vector(W,Thetadot,AV,nS,Iout)
!	----------------------------------------------------------------------------- S Matrix
!
!	AV		= Angular Velocity Vector 
!			= W*thetadot 
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
	Real(kind=8)	W       ,AV                
	Dimension		W(nS,nS),AV(nS)
	Dimension		Thetadot(nS)
	Real(kind=8)	Thetadot                           
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!---------------------------------------------------------- Gyro
	AV = MATMUL(W,Thetadot)
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		call DumpRealArray(AV,3,"Angular Velocity",iPrt,iOut)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Rotational Gyroscopic Matrix RG(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
