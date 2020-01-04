	Subroutine Direct_StateVector(xo,x,xs,Arclen,nSC,kode,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	x     ,xo
	Dimension		x(nSC),xo(nSC),xs(nSc) 
	Data			two/2.D0/                         
	
!
	if(kode == 1) Then					! initialize	 
		xs		= 0.D0	! zero all	this one for restrting iteration with cut
		x		= 0.D0	! zero all
		xo		= 0.D0
		x(nSC)	= ArcLen
		xs(nSC)	= ArcLen
!
	elseif(kode == 2) Then				! Update for LoadStep
		do 10 i = 1,nSC
		temp	= xo(i)	 
		xo(i)	= x(i)
		x(i)	= two*x(i) - temp
		xs(i)	= x(i)
   10		continue
!
	elseif(kode == 3) Then			! Reset for restart iteration/Cut ArcLen
		do 20 i = 1,nSC	 
		x(i)	= xs(i) 
   20		continue
	endif
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nSC,(x(i), i=1,nSC)
	endif 
!
	return
!
 1010 format("State Vector(",I2,")"/(5(f16.6,1X)/))
	end
