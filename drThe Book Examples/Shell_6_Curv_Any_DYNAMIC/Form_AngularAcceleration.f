	Subroutine Form_AngularACC_Vector(W,Wd,Td,T2,AA,nS,Iout)
!	----------------------------------------------------------------------------- S Matrix
!
!	AV		= Angular Acceleration Vector 
!			= WDot*thetadot+W*theta2dot 
!	----------------------------------------------------------------------------- 
!	Inputs
!	W			= Rodrigues transformation matrix depends on current Rotation
!	Wd			= rate of Rodrigues transformation matrix depends on current Rotation
!	Td			= rate of Current Rotation: Thetadot(3)
!	T2			= Second rate of Current Rotation: Theta2dot(3)
! 	
!	Outputs 
!		RG			= Rot Gyroscopic Matrix: RG(3,3)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
!	include 'mass.h'

!
	Real(kind=8)	W       ,Wd       ,AA                
	Dimension		W(nS,nS),Wd(nS,nS),AA(nS)
	Dimension		Td(nS),T2(nS)
	Real(kind=8)	Td    ,T2                       
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!---------------------------------------------------------- Gyro
	AA = MATMUL(Wd,Td) + MATMUL(W,T2)
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		call DumpRealArray(AA,3,"Angular Acceleration",iPrt,iOut)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Rotational Gyroscopic Matrix RG(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
