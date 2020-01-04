	Subroutine Initialize_AugMultipliers(Augmult,Nint1,Nint2,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!	===================
	include 'Augment.h'
!	===================
	Real(kind=8)	Augmult
	Dimension		Augmult(Nint1,Nint2) 
	
!
!	Augmult	= zero
	Augmult	= AugThet
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
