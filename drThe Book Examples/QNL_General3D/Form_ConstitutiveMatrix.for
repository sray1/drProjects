	Subroutine Form_ConstitutiveMatrix(D,nDof,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	D
	Dimension		D(nDof,nDof)
!	                          
	common/Material/E,G,PR
	common/Geometry/THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH
	common/Examples/cEx(10),nEx
	character (30)	cEx
!----------------------------------------------------------
	D	   = 0.D0 !ALL
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			D(1,1) = E					!EA
			D(2,2) = .5D0*E				!GA
			D(6,6) = D(1,1)/12.D0		!EI
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			D(1,1) = E					!EA
			D(2,2) = .5D0*E				!GA
			D(6,6) = 256.D0*E			!EI
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			D(1,1) = E					!EA
			D(2,2) = E					!GA
			D(6,6) = 1000.				!EI		
		CASE (4)
			AA = Width*Depth				! 3D Curved Cantilev.LINMOD: Ex_4 
!			XK = 1.D0								! Shear Factor = 1	
			XK = 5.D0/6.D0							! Shear Factor	
			XI = AA*Depth*Depth/12.D0				! II
			XO = AA*Width*Width/12.D0				! IO
			XJ = (XI+XO)							! J 
			AI = E*XI								! EII
			AO = E*XO								! EIO
			GJ = G*XJ								! GJ 
			BM = E*AA								! EA 
			CM = XK*G*AA								! kGA
		!
			D(1,1) = BM
			D(2,2) = CM
			D(3,3) = CM
			D(4,4) = GJ
			D(5,5) = AI
			D(6,6) = AO
		CASE (5)							! 3D Str. Cantilever-Bathe: Ex_5
		!	XK = 1.D0								! Shear Factor = 1	
			XK = 5.D0/6.D0							! Shear Factor	
!			-----
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
		CASE (6:10)    ! FALL THRO'           Other: Ex_6... 
		CASE DEFAULT
			XK = 5.D0/6.D0							! Shear Factor	
		!	-----
			return
	END SELECT
!	=======================================================
	write(iOut,1020) (D(i,i),i=1,nDof)
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
