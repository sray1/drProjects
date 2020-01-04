	Subroutine Form_Cent_Matrix(W,Wd,W2,T,Td,T2,AV,AA,XC,nS,nD,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	XMass		= Mass matrix = (6x6)  Symmetric
!				= |TMass*I		0              |
!				  |  0		RMass*W_Transpose*W|
!	----------------------------------------------------------------------------- 
!	Inputs
!		nD		= 6
!		nS		= 3
!		W		= (nS,nS) linearized rot. Xformation matrix
!		Wd		= (nS,nS) linearized rot. Xformation matrix_Derivative
!		W2		= (nS,nS) linearized rot. Xformation matrix_SecondDerivative
!		T		= (nS) Current Theta
!		Td		= (nS) Current ThetaDot
!		T2		= (nS) Current Theta2Dot
!		AV		= (nS) Current Angular Velocity		= W*Td
!		W2		= (nS) Current Angular Acceleration	= Wd*Td+W*T2
!		TMass	= Translational Mass density	
!		RMass	= Rotational Mass density	
!	Outputs 
!		XM		= Mass Matrix: XM(6,6)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'mass.h'

!
	Real(kind=8)	W       ,Wd       ,W2                      
	Dimension		W(nS,nS),Wd(nS,nS),W2(nS,nS)
	Real(kind=8)	T    ,Td    ,T2                      
	Dimension		T(nS),Td(nS),T2(nS)
	Real(kind=8)	AV    ,AA                          
	Dimension		AV(nS),AA(nS)
	Real(kind=8)	XC       ,TC       ,RC                
	Dimension		XC(nD,nD),TC(nS,nS),RC(nS,nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ TransCentMatrix
	call Form_TranCent_Matrix(TC,TMass,nS,Iout)
!	------------------------------------------------------ RotCentMatrix
	call Form_RotCent_Matrix(W,Wd,W2,T,Td,T2,AA,RC,RMass,nS,Iout)
!	------------------------------------------------------ Centrifugal 
	XG = 0.D0
!
	do ix = 1,3
		do jx = 1,3
			XC(ix,jx) = TC(ix,jx)
		end do
	end do
!
	do ix = 1,3
		do jx = 1,3
			XC(ix+nS,jx+nS) = RC(ix,jx)
		end do
	end do
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(XC(i,j),j = 1,nD),i=1,nD)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Centrifugal Matrix XG(6,6)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
