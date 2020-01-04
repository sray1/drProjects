	Subroutine Initialize_Penalty(Penalt,Nint1,Nint2,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!	===================
	include 'Augment.h'
!	===================
	Real(kind=8)	Penalt
	Dimension		Penalt(Nint1,Nint2) 
	Data			zero/0.D0/,two/2.D0/                         
	
!
	Penalt	= pen
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
	endif 
!
	return
!
 1010 format("AugMult(",I2,")"/(5(f16.6,1X)/))
	end
