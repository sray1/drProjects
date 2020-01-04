	Subroutine FormRot2Quaternion(Ro,Qu,nC,nQu,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		Ro(nC)			= theta-Rotation vector
!		nC				= 3
! 	
!	Outputs 
!		A(nC,nC)		= Rotation Matrix
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'LoadStepIter.h'

	Real(kind=8)	Ro    ,Qu                       
	Dimension		Ro(nC),Qu(nQu)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,half/0.5D0/ 
!----------------------------------------------------------------------- Check theta = 0
	call VectorNorm(Ro,tNorm,nC,Iout)
!	----------------
	if(tNorm == zero) Then
		Qu = zero
		Qu(4) = one			! Identity Matrix
		b = zero
		go to 10
	endif
!----------------------------------------------------------------------- Form Rodrigue's Vector
	sint = DSIN(half*tNorm)		!= sin(||theta||/2)
	cost = DCOS(half*tNorm)		!= sin(||theta||/2)
!
!----------------------------------------------------------------------- Form Qu(aternion)
	Qu(1) = sint*Ro(1)/tNorm
	Qu(2) = sint*Ro(2)/tNorm
	Qu(3) = sint*Ro(3)/tNorm
	Qu(4) = cost
!	----------------------------------------------------- 
   10 continue
!	------------------------------
   	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1040) tNorm
	endif
!---------------------------------------------------------- Write:
	iPrt = 0
	if((iStep == 1).AND.(iNut == 2)) Then
		iPrt = 0
	endif
	if (iPrt == 1) Then
		write(Iout,1010) (Ro(j),j = 1,nC)
		write(Iout,1020) (Qu(j),j = 1,nQu)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current Rotation Axis vector: Theta(3)"/2X,3(f10.7,1X))
 1020 format(1X,"Current Quaternion vector: Qu(4)"/2X,4(f10.7,1X))
 1040 format(/1X,"tNorm = ", f16.7/)
	end
