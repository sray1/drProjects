!
	Subroutine Set_ExtLoad_X(Qf,nDim,iOut)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf(1)	= +3.0
	Qf(2)	= +1.0
	Qf(3)	= -1.0
	Qf(4)	= -3.0
!
	return
	end
	Subroutine Quad_CC_LVX(Qf,F,nF,xLenX,xLenY,iOut)
!
!	Root Side:LOAD VECTOR in X-direction
!
!
!	Inputs
!		Qf(4)		= Load Ceffs at Bez. Pts at r = 0 Side
!		xLenY		= Length of side at r = 0
!		 	
!	Outputs 
!		F(32)	1= Desired Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	Real(kind=8)	Qf   ,xLenX,xLenY
	Dimension		Qf(4)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F
	Dimension		F(nF)
	
	Real(kind=8)	T3i,T3j,T6iPj,fmult,dum
	Real(kind=8)	tem	    ,temF
	Dimension		tem(4,4),temF(4)
	integer			i,j
!
	
	do 10 i= 1,4
	do 10 j= 1,4
	ii = i-1
	jj = j-1
	T3i		= Factorial(3)/Factorial(ii)/Factorial(3-ii) 
	T3j		= Factorial(3)/Factorial(jj)/Factorial(3-jj) 
	T6iPj	= Factorial(6)/Factorial(ii+jj)/Factorial(6-(ii+jj))
!
	tem(i,j)= (1./7.)*T3i*T3j/T6iPj
   10 continue
!   
!	Now fill up Load Vector for X values at r = 0 side
!		ie., nodes 1,5,9,13
!
	fmult = -8.00D0
	do 30 i= 1,4
	dum = 0.
	do 20 j= 1,4
	dum = dum + tem(i,j)*Qf(j)
   20	continue
	temF(i) = fmult*dum
   30 continue
!---------------------------
	F = 0.		! zero All
!---------------------------
	F(1)	= temF(1)    
	F(5)	= temF(2)    
	F(9)	= temF(3)    
	F(13)	= temF(4)    
!   
!	Done
!
	write(iOut,1000)
	write(iOut,1010) (F(i),i = 1,nF)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Quad_CC_LVX"/)
 1010 Format(/2x,"Load Vector"/7(2x,8F10.7/) )
	end 
	
	real(kind=8) function Factorial(num)
	integer num
	
	Factorial = 1.D0
	do 40 i = num,1,-1
	Factorial = Factorial*i
   40	continue
!
	end 	  		