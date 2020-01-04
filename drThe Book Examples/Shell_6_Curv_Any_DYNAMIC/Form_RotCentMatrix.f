	Subroutine Form_RotCent_Matrix(W,Wd,W2,T,Td,T2,AA,RC,RMass,
     &								nS,Iout)
!	----------------------------------------------------------------------------- S Matrix
!
!	RC		= Rotational Centrifugal matrix 
!			= U(AA)+(W-trans){W2d-(W*Td*Wd + Wd*Td*W) - WT2dW}
!	U(AA)	= c1*AA_skew +(-c2*I-c3*T_skew +c4*T_skew2)*(AA*T_tran)
!			 +c2{TtensorAA - AAtensorT + (TdotAA)I}
!	AA		= Angular Acceleeration
!			= Wd*Td + W*Tdd
!	----------------------------------------------------------------------------- 
!	Inputs
!	T		= current Rotation vector
!	Td		= rate of current Rotation vector
!	T2d		= second rate of current Rotation vector
!	W		= Rodrigues transformation matrix depends on current Rotation
!	Wd		= rate of Rodrigues transformation matrix
!	W2d		= second rate of Rodrigues transformation
!	AA		= Angular acceleration
! 	
!	Outputs 
!		RC			= Rot Centrifugal Matrix: RC(3,3)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	include 'ThetaConstants.h'
!	include 'mass.h'

!
	Real(kind=8)	W       ,Wd       ,W2       ,RC                
	Dimension		W(nS,nS),Wd(nS,nS),W2(nS,nS),RC(nS,nS)
	Dimension		T(nS)   ,Td(nS)   ,T2(nS)   ,AA(nS),U(nS,nS)
	Real(kind=8)	T       ,Td       ,T2       ,AA    ,U                           
	Dimension		TS(nS,nS),TdS(nS,nS),T2S(nS,nS),AAS(nS,nS)
	Real(kind=8)	TS       ,TdS       ,T2S       ,AAS                          
	Dimension		IM(nS,nS)
	Real(kind=8)	IM       ,AAdotT                          
	Real(kind=8)	AAtenT       ,TtenAA                
	Dimension		AAtenT(nS,nS),TtenAA(nS,nS)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	------------------------------------------------------ identity matrix (I)
	IM=0.D0
	IM(1,1) = 1.D0
	IM(2,2) = 1.D0
	IM(3,3) = 1.D0
!	------------------------------------------------------ theta-Skew (TS)
	call FormSkew(T,nS,TS,Iout)
!	------------------------------------------------------ thetadot-Skew (TdS)
	call FormSkew(Td,nS,TdS,Iout)
!	------------------------------------------------------ thetadotdot-Skew (T2dS)
	call FormSkew(T2,nS,T2S,Iout)
!	------------------------------------------------------ AA-Skew (AAS)
	call FormSkew(AA,nS,AAS,Iout)
!---------------------------------------------------------- 
	call DotProduct(AA,T,AAdotT,nS,Iout)
!
	call TensorProduct(AA,T,AAtenT,nS,Iout)
	call TensorProduct(T,AA,TtenAA,nS,Iout)
!---------------------------------------------------------- U
	c3	= c1b
	c4	= c2b
!
	U   = c1*AAS + (-c2*IM -c3*TS +c4*T2S)*AAtenT
     &     + c2*(TtenAA - AAtenT + AAdotT*IM)
!---------------------------------------------------------- Cent
	RC	= U + TRANSPOSE(W)*(W2 - (W*TdS*Wd+Wd*TdS*W) - W*T2S*W)
	RC	= RMass*RC	 
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(RC(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("Rotational Centrifugal Matrix RG(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
