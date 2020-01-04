	Subroutine Check_AugConvergence(AugMultOld,AugMult,Nint1,Nint2,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	AugMult
	Dimension		AugMult(Nint1,Nint2) 
	Data			zero/0.D0/,two/2.D0/                         
	
!
	AugMult		= 0.D0
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
	endif 
!
	return
!
 1010 format("State Vector(",I2,")"/(5(f16.6,1X)/))
	end
