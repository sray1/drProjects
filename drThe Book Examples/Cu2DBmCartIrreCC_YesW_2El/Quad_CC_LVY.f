	Subroutine Quad_CC_LVY(Qf,F,nF,xLenY)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element:LOAD VECTOR
!
!
!	Inputs
!		Qf(4)		= Load Ceffs at Bez. Pts at r = 1 Side
!		xLenY		= Length of side at r = 1
!		 	
!	Outputs 
!		F(32)	1= Desired Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	Real(kind=8)	Qf   ,xLenY
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
	fmult = 2.0D0
	do 30 i= 1,4
	dum = 0.
	do 20 j= 1,4
	dum = dum + tem(i,j)*Qf(j)
   20	continue
	temF(i) = fmult*dum
   30 continue
!   
!	Now fill up Load Vector for Y values at r = 0 side
!		ie., nodes 17,21,25,29
!
	sign  = -1.0D0
	F(17) = sign*temF(1)    
	F(21) = sign*temF(2)    
	F(25) = sign*temF(3)    
	F(29) = sign*temF(4)    
!   
!	Now fill up Load Vector for Y values at r = 1 side
!		ie., nodes 47,50,53,56
!
	F(47) = temF(1)    
	F(50) = temF(2)    
	F(53) = temF(3)    
	F(56) = temF(4)    
!   
!	Done
!
	return
	end 
