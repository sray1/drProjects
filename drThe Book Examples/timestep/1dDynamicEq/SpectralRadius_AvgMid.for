	Subroutine SpectralRadius_AvgMid(srad,tp,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
!	include 'CubicData.h'

      complex(8)		sol
	Dimension		sol(3)
	Real(kind=8)	srad,tp,pi,pi2,ratO,rat,rat2,geta,alfa,gama
	Real(kind=8)	a,b,c,d,inc

	integer			nlup

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!	--------------------------------------
	pi	= 4.D0*atan(1.)
	pi2	= pi*pi
!	-----------------------
	nlup	= 10
!	nlup	= 2
	inc		= 10
	ratO	= .1D0
	ratO	= .00001D0
	a		= 1.D0
!	---------------------------------------------------------- LOOP
	write(iOut,500) 
	do i = 1,nlup
		if(i.eq.1) then
			rat = 0.D0
		else
			inc		= .5D0*(i-1)
			inc		= 10.D0**(i-1)
			rat		= ratO*inc 
		endif
		rat2	= rat*rat
		if(rat.lt.10001.D0) then
!		-------------------------------------------- calc a,b,c,d
			pi2rat2	= pi2*rat2
			alfa	= 2.D0 + 2.D0*pi2rat2
			gama	= 1.D0/alfa
			beta	= 4.D0*gama*pi2rat2
!
			b = beta-4.D0*gama - 1.D0		
			c =      8.D0*gama - 1.D0
			d =-beta-4.D0*gama + 1.D0
!
			write(iOut,1000) rat,alfa,beta,gama,a,b,c,d
			call CubicSolver(sol,a,b,c,d,iOut)
		endif
	end do			
	write(iOut,600) 
!	-------------------------------------------- calc spectral radius

	return
  500 format(/" Spectral Radius Output===============BEGIN"//)
  600 format(/" Spectral Radius Output===============END"//)
 1000 format(//2x,"Ratio =",f20.7/
     & "alfa =",f20.5,2x,"beta =",f20.5,2x,"gama =",f20.5/
     & "a =",f10.5,2x,"b =",f10.5,2x,"c =",f10.5,2x,"d =",f10.5/)
	end
!


