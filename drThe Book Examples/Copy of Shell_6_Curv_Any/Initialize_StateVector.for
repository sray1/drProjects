	Subroutine Initialize_StateVector(xo,x,nSC,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	x     ,xo
	Dimension		x(nSC),xo(nSC),xs(nSc) 
	Data			two/2.D0/                         
	
!
	x		= 0.D0	! zero all
	xo		= 0.D0
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
