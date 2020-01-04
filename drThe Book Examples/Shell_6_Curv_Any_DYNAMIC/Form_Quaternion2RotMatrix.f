	Subroutine FormQuaternion2RotMatrix(Qu,A,nC,nQu,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		Qu(nQu)			= Quaternion 
!		nQu				= 4
! 	
!	Outputs 
!		A(nC,nC)		= Rotation Matrix
!		nC				= 3
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'LoadStepIter.h'

	Real(kind=8)	Qu     ,A                       
	Dimension		Qu(nQu),A(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,half/0.5D0/ 
!----------------------------------------------------------------------- Check theta = 0
		A = zero
!----------------------------------------------------------------------- Form AMat
	q11	= two*Qu(1)*Qu(1)
	q12	= Qu(1)*Qu(2)
	q13	= Qu(1)*Qu(3)
	q14	= Qu(1)*Qu(4)
	q22	= two*Qu(2)*Qu(2)
	q23	= Qu(2)*Qu(3)
	q24	= Qu(2)*Qu(4)
	q33	= two*Qu(3)*Qu(3)
	q34	= Qu(3)*Qu(4)
!	-------------------------------
	A(1,1) = one - q22 - q33
	A(2,2) = one - q11 - q33
	A(3,3) = one - q11 - q22
	A(1,2) = two*(q12-q34)
	A(2,1) = two*(q12+q34)
	A(1,3) = two*(q13+q24)
	A(3,1) = two*(q13-q24)
	A(2,3) = two*(q23-q14)
	A(3,2) = two*(q23+q14)
!	----------------------------------------------------- 
   10 continue
!	----------------------------------------------------- Trace
	trA = A(1,1) + A(2,2) + A(3,3)
!	------------------------------
   	iPrt = 0
	if ((iPrt == 1).AND.(trA.LE.-half)) Then
		write(Iout,1040) trA
	endif
!---------------------------------------------------------- Write:
   	iPrt = 0
	if((iStep == 1).AND.(iNut == 2)) Then
		iPrt = 0
	endif
	if (iPrt == 1) Then
		write(Iout,1020) (Qu(j),j = 1,nQu)
		write(Iout,1030) (i,(A(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1020 format(1X, "Rodrigues Quaternion vector: Qu(4)"/2X,4(f10.7,1X))
 1030 format(2X, "Rotation Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
 1040 format(/1X,"trA = ", f16.7/)
	end
