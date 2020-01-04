	Subroutine Bernstein(Br,nQc,r,iOut)
	
	real(kind = 8)	Br
	Dimension		Br(nQc)
	real(kind = 8)	r
	integer			nQc,iOut
	integer			nBr,im1
	real(kind = 8)	xMult
!-------------------------------------------------- Bernstein
	Br = 0.D0			! ALL
	if( r == 0.D0) Then
		Br(1) = 1.0D0
		return
	elseif( r == 1.D0) Then
		Br(nQc) = 1.0D0
		return
	endif
!
	nBr		= nQc-1		! Degree of Bernstein	
	do 5 i = 1,nQc
	im1		= i-1
	xMult	= Factorial(nBr)/Factorial(im1)/Factorial(nBr-im1)
	Br(i)	= xMult*((r**im1) * ((1.D0-r)**(nBr-im1)))
    5 continue	
!------------------------------------  	
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
