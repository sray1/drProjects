	Subroutine Constitutive(D,E,PR,Width,Depth,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	D
	Dimension		D(3)                          
	
!	 
!----------------------------------------------------------
	XK = 1.D0								! Shear Factor = 1	
	AM = E*Width*Depth*Depth*Depth/12.D0	! EI
	BM = E*Width*Depth						! EA 
	CM = XK*BM/(2.D0*(1.D0+PR))				! kGA
!
	D	 = 0.D0 !ALL
	D(1) = BM
	D(2) = CM
	D(3) = AM
!------------------------------------------------------------------- Constitutive: PALAZOTTO
	D(1) = E					!EA
	D(2) = .5D0*E				!GA
	D(3) = D(1)/12.D0			!EI		! c = 0
!	D(3) = 256.*D(1)			!EI		! c = 0..01
!------------------------------------------------------------------- Constitutive: Keith
	D(1) = E					!EA
	D(2) = E					!GA
	D(3) = 1000.				!EI		
!--------------------------------------------------------------------------------------------	
!---------------------------------------- Temporary Check End
!	------
	iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1020) D(1),D(2),D(3)
	endif
!	------
	return
 1020 Format(/ 5x,"Constitutive Matrix "/
     &	2x,"EA		= ",G12.5/
     &	2x,"GA		= ",G12.5/
     &	2x,"EI		= ",G12.5/
     &	)		
	end
