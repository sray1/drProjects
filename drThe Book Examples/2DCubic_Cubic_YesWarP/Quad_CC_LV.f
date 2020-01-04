	Subroutine Quad_CC_LV(Qf,F,xLenY)
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
	Real(kind=8)	Qf  
	Dimension		Qf(4)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F
	Dimension		F(32)
	
	Real(kind=8)	T3i,T3j,T6iPj,fmult,dum,sign
	Real(kind=8)	tem	    ,temF   ,Qfx
	Dimension		tem(4,4),temF(4),Qfx(4)
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
!	Now fill up Load Vector for Y values at r = 1 side
!		ie., nodes 20,24,28,32
!
	F = 0.		! zero All
	F(20) = temF(1)    
	F(24) = temF(2)    
	F(28) = temF(3)    
	F(32) = temF(4)    
!------------------------------------------------------- Root Section
	sign  = -1.0D0
	F(17) = sign*temF(1)    
	F(21) = sign*temF(2)    
	F(25) = sign*temF(3)    
	F(29) = sign*temF(4)    
!--------------------------- x dir
	fmult = 8.0D0
	Qfx(1) = -3.0D0
	Qfx(2) = -1.0D0
	Qfx(3) =  1.0D0
	Qfx(4) =  3.0D0
!--------------------	
	do 50 i= 1,4
	dum = 0.
	do 40 j= 1,4
	dum = dum + tem(i,j)*Qfx(j)
   40	continue
	temF(i) = fmult*dum
   50 continue
   
!	Now fill up Load Vector for X values at r = 0 side
!		ie., nodes 1,5,9,13
!
	F(1)  = temF(1)    
	F(5)  = temF(2)    
	F(9)  = temF(3)    
	F(13) = temF(4)    
!   
!	Done
!
	return
	end 
	
	real(kind=8) function Factorial(num)
	integer num
	
	Factorial = 1.D0
	do 40 i = num,1,-1
	Factorial = Factorial*i
   40	continue
!
	end 	  		