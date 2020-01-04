	Subroutine Bernstein_IstDerivative(Br,nQc,r,iOut)
	
	real(kind = 8)	Br     ,Brm1
	Dimension		Br(nQc),Brm1(10)
	real(kind = 8)	r
	integer			nQc,iOut
	integer			nBr,im1
	real(kind = 8)	xMult
!-------------------------------------------------- Bernstein_Derivative
	nBr		= nQc-1		!Degree of Curve	
	call Bernstein(Brm1,nBr,r,iOut)
!
	Br(1)	= -nBr*Brm1(1)
	Br(nQc)	=  nBr*Brm1(nBr)
	do 5 i = 2,nBr
	Br(i)	= nBr*(Brm1(i-1) - Brm1(i))
    5 continue	
!------------------------------------  	
	return
	end
