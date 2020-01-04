	Subroutine Quad_LL_LV(Qf,F,xLenY,nOrder,nStif)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element:LOAD VECTOR
!
!
!	Inputs
!		Qf(nOrder)		= Load Ceffs at Bez. Pts at r = 1 Side
!		xLenY			= Length of side at r = 1
!		 	
!	Outputs 
!		F(nStif)		1= Desired Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	Real(kind=8)	Qf
	Dimension		Qf(nOrder)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F
	Dimension		F(nStif)
	
	Real(kind=8)	T3i,T3j,T6iPj,fmult,dum
	Real(kind=8)	tem	    ,temF
	Dimension		tem(4,4),temF(4)
	integer			i,j,nDegree,nDegree2
!
	nDegree = nOrder-1
	nDegree2 = 2*nDegree
	do 10 i= 1,nOrder
	do 10 j= 1,nOrder
	ii = i-1
	jj = j-1
	T3i		= Factorial(nDegree)/Factorial(ii)/Factorial(nDegree-ii) 
	T3j		= Factorial(nDegree)/Factorial(jj)/Factorial(nDegree-jj) 
	T6iPj	= Factorial(nDegree2)/Factorial(ii+jj)
     &									/Factorial(nDegree2-(ii+jj))
!
	tem(i,j)= (1./(nDegree2+1))*T3i*T3j/T6iPj
   10 continue
!
	fmult = 2.*xLenY
	do 30 i= 1,nOrder
	dum = 0.
	do 20 j= 1,nOrder
	dum = dum + tem(i,j)*Qf(j)
   20	continue
	temF(i) = fmult*dum
   30 continue
!   
!	Now fill up Load Vector for Y values at r = 1 side
!		ie., nodes 2,4
!
	F = 0.		! zero All
	F(2) = temF(1)    
	F(4) = temF(2)    
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