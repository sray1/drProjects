	Subroutine FormRotMatrix2Quaternion(Qu,A,nC,nQu,Iout)
!	----------------------------------------------------------------------------- 
!	Inputs
!		A(nC,nC)		= Rotation Matrix
!		nC				= 3
! 	
!	Outputs 
!		Qu(nQu)			= Quaternion 
!		nQu				= 4
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'LoadStepIter.h'

	Real(kind=8)	Qu     ,A                       
	Dimension		Qu(nQu),A(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,half/0.5D0/ 
!	------------------------------------------------------------------ Trace
	trA = A(1,1) + A(2,2) + A(3,3)
!----------------------------------------------------------------------- Form Quaternion
	QQ = .25D0*(one + trA)					!step 0
	if(QQ.gt.zero) then						!step 1
		Qu(4)	= DSQRT(QQ)
!	
		reci	= .25D0/Qu(4)
		Qu(1)	= (A(2,3)-A(3,2))*reci	
		Qu(2)	= (A(1,3)-A(3,1))*reci	
		Qu(3)	= (A(1,2)-A(2,1))*reci	
		goto 100
	else
		QQ	= -half*(A(2,2)+A(3,3))			!step 2	
		if(QQ.gt.zero) then					!step 3
			Qu(1)	= DSQRT(QQ)
!	
			reci	= half/Qu(1)
			Qu(2)	= A(1,2)*reci	
			Qu(3)	= A(1,3)*reci
			Qu(4)	= zero
			goto 100
		else
			QQ	= -half*(one-A(3,3))		!step 4	
			if(QQ.gt.zero) then				!step 5
				Qu(1)	= zero
				Qu(2)	= DSQRT(QQ)
!	
				reci	= half/Qu(2)
				Qu(3)	= A(2,3)*reci
				Qu(4)	= zero
				goto 100
			else							!step 6
				Qu(1)	= zero
				Qu(2)	= zero
				Qu(3)	= one
				Qu(4)	= zero
			endif
		endif
	endif
!	----------------------------------------------------- 
  100 continue
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
		write(Iout,1030) (i,(A(i,j),j = 1,nC),i=1,nC)
		write(Iout,1020) (Qu(j),j = 1,nQu)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1020 format(1X, "Rodrigues Quaternion vector: Qu(4)"/2X,4(f10.7,1X))
 1030 format(2X, "Rotation Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
 1040 format(/1X,"trA = ", f16.7/)
	end
