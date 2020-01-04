!	  			
	Subroutine Set_ExtLoad_Y(Qf,nDim,iOut)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
!
	Qf(2)	= 0.75D0
	Qf(3)	= 1.0
	Qf(4)	= 0.75D0
!
	return
	end
	Subroutine Quad_CC_LVY(Qf,F,nF,xLenY,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element:LOAD VECTOR
!
!
!	Inputs
!		Qf(5)		= Load Ceffs at Bez. Pts at r = 1 Side
!		xLenY		= Length of side at r = 1
!		 	
!	Outputs 
!		F(50)	1= Desired Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	Real(kind=8)	Qf   ,xLenY
	Dimension		Qf(5)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F
	Dimension		F(nF)
	
	Real(kind=8)	T4i,T4j,T8iPj,fmult,dum
	Real(kind=8)	tem	    ,temF
	Dimension		tem(5,5),temF(5)
	integer			i,j
!
	
	do 10 i= 1,5
	do 10 j= 1,5
	ii = i-1
	jj = j-1
	T4i		= Factorial(4)/Factorial(ii)/Factorial(4-ii) 
	T4j		= Factorial(4)/Factorial(jj)/Factorial(4-jj) 
	T8iPj	= Factorial(8)/Factorial(ii+jj)/Factorial(8-(ii+jj))
!
	tem(i,j)= (1./9.)*T4i*T4j/T8iPj
   10 continue
!
	fmult = 2.0D0
	do 30 i= 1,5
	dum = 0.
	do 20 j= 1,5
	dum = dum + tem(i,j)*Qf(j)
   20	continue
	temF(i) = fmult*dum
   30 continue
!   
!	Now fill up Load Vector for Y values at r = 0 side
!		ie., nodes 26,31,36,41,46
!
	sign  = -1.0D0
	F(26) = sign*temF(1)    
	F(31) = sign*temF(2)    
	F(36) = sign*temF(3)    
	F(41) = sign*temF(4)    
	F(46) = sign*temF(5)    
!   
!	Now fill up Load Vector for Y values at r = 1 side
!		ie., nodes 74,78,82,86,90
!
	sign  = +1.0D0
	F(74) = sign*temF(1)    
	F(78) = sign*temF(2)    
	F(82) = sign*temF(3)    
	F(86) = sign*temF(4)    
	F(90) = sign*temF(5)    
!   
!	Done
!
	write(iOut,1000)
	write(iOut,1010) (F(i),i = 1,nF)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Quad_CC_LVY"/)
 1010 Format(/2x,"Load Vector"/
     &        7(2x,8F10.7/) )
	end 
