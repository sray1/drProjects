	Subroutine Quad_QC_LV(Qf,F,xLenY)
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
	Dimension		Qf(3)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F
	Dimension		F(24)
	
	Real(kind=8)	T2i,T2j,T4iPj,fmult,dum
	Real(kind=8)	tem	    ,temF
	Dimension		tem(3,3),temF(3)
	integer			i,j
!
	
	do 10 i= 1,3
	do 10 j= 1,3
	ii = i-1
	jj = j-1
	T2i		= Factorial(2)/Factorial(ii)/Factorial(2-ii) 
	T2j		= Factorial(2)/Factorial(jj)/Factorial(2-jj) 
	T4iPj	= Factorial(4)/Factorial(ii+jj)/Factorial(4-(ii+jj))
!
	tem(i,j)= (1./5.)*T2i*T2j/T4iPj
   10 continue
!
!	--------------
	fmult = 3.0D0
!	--------------
	do 30 i= 1,3
	dum = 0.
	do 20 j= 1,3
	dum = dum + tem(i,j)*Qf(j)
   20	continue
	temF(i) = fmult*dum
   30 continue
!   
!	Now fill up Load Vector for Y values at r = 1 side
!		ie., nodes 20,24,28,32
!
	F = 0.		! zero All
	F(16) = temF(1)    
	F(20) = temF(2)    
	F(24) = temF(3)    
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