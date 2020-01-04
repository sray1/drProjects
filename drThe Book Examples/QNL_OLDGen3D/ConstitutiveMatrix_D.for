	Subroutine ConstitutiveMatrix_D(D,E,PR,Width,Depth,nDof,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	D
	Dimension		D(nDof,nDof)                          
	
!	 
	D	   = 0.D0 !ALL
!----------------------------------------------------------------- Bathe:3D/3DLINMOD
!	XK = 1.D0								! Shear Factor = 1	
	XK = 5.D0/6.D0							! Shear Factor	
!	-----
	AA = Width*Depth			! AA
	XI = AA*Depth*Depth/12.D0	! II
	XO = AA*Width*Width/12.D0	! IO
	XJ = (XI+XO)				! J
	G  = E/(2.D0*(1.D0+PR))		! G 
	AI = E*XI					! EII
	AO = E*XO					! EIO
	GJ = G*XJ					! GJ 
	BM = E*AA					! EA 
	CM = XK*G*AA				! kGA
!
	D(1,1) = BM
	D(2,2) = CM
	D(3,3) = CM
	D(4,4) = GJ
	D(5,5) = AI
	D(6,6) = AO
!------------------------------------------------------------------- Constitutive: PALAZOTTO
!	D(1) = E					!EA
!	D(2) = .5D0*E				!GA
!	D(3) = D(1)/12.D0			!EI		! c = 0
!	D(3) = 256.*D(1)			!EI		! c = 0..01
!----------------------------------------------------
!	D	   = 0.D0 !ALL
!	D(1,1) = E					!EA
!	D(2,2) = .5D0*E				!GA
!	D(6,6) = D(1,1)/12.D0			!EI
!------------------------------------------------------------------- Constitutive: Keith Moment
!	D	   = 0.D0 !ALL
!	D(1,1) = E					!EA
!	D(2,2) = E					!GA
!	D(6,6) = 1000.				!EI		
!---------------------------------------- Temporary Check End
!	------
	iPrt = 1
	if(iPrt == 1) Then
		write(iOut,1020) (D(i,i),i=1,nDof)
	endif
!	------
	return
 1020 Format(/ 5x,"Constitutive Matrix "/
     &	2x,"GA		= ",G12.5/
     &	2x,"EAM		= ",G12.5/
     &	2x,"EAB		= ",G12.5/
     &	2x,"GJ		= ",G12.5/
     &	2x,"EIM		= ",G12.5/
     &	2x,"EIB		= ",G12.5/
     &	)		
	end
