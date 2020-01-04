	Subroutine FormRotationMatrix(Ro,A,nC,Iout)
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
	Real(kind=8)	Ro    ,b    ,A                       
	Dimension		Ro(nC),b(nC),A(nC,nC)
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/,half/0.5D0/ 
	DATA zeropoint9/0.9D0/
!----------------------------------------------------------------------- Check theta = 0
	call VectorNorm(Ro,tNorm,nC,Iout)
!	----------------
	if(tNorm == zero) Then
		A = zero
		A(1,1) = one			! Identity Matrix
		A(2,2) = one
		A(3,3) = one
		b = zero
		go to 10
	endif
!----------------------------------------------------------------------- Form Rodrigue's Vector
	Tant = DTAN(half*tNorm)		!= tan(||theta||/2)
!
	rNorm = one/tNorm
!
	b = rNorm*Tant*Ro
!	-----------------
	b1	= b(1)
	b2	= b(2)
	b3	= b(3)
!
	b11 = b1*b1
	b22 = b2*b2
	b33 = b3*b3
	b12 = b1*b2
	b13 = b1*b3
	b23 = b2*b3
!
	rdel	= one/(one+b11+b22+b33)
	r2del	= two*rdel
!----------------------------------------------------------------------- Form AMat
	A(1,1) = rdel*(one+b11-b22-b33)
	A(2,2) = rdel*(one-b11+b22-b33)
	A(3,3) = rdel*(one-b11-b22+b33)
	A(1,2) = r2del*(b12-b3)
	A(2,1) = r2del*(b12+b3)
	A(1,3) = r2del*(b13+b2)
	A(3,1) = r2del*(b13-b2)
	A(2,3) = r2del*(b23-b1)
	A(3,2) = r2del*(b23+b1)
!	----------------------------------------------------- 
   10 continue
!	----------------------------------------------------- Trace
	trA = A(1,1) + A(2,2) + A(3,3)
	call VectorNorm(b,bNorm,nC,Iout)
!	------------------------------
   	iPrt = 1
	if ((iPrt == 1).AND.(trA.LE.-zeropoint9)) Then
		write(Iout,1040) tNorm,Tant,bNorm,trA
	endif
   	iPrt = 0
!---------------------------------------------------------- Write:
   	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (Ro(j),j = 1,nC)
		write(Iout,1020) (b(j),j = 1,nC)
		write(Iout,1030) (i,(A(i,j),j = 1,nC),i=1,nC)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format(1X,"Current Rotation Axis vector: Theta(3)"/2X,3(f10.7,1X))
 1020 format(1X,"Current Rodrigues vector: B(3)"/2X,3(f10.7,1X))
 1030 format(2X, "Rotation Matrix(3,3)"/( (I5,3(f20.7,1X))  ))
 1040 format(1X,"tNorm = ", f16.7,1X,"Tant = ", f16.7,
     &			1X,"bNorm = ", f16.7,1X,"trA = ", f16.7)
	end
