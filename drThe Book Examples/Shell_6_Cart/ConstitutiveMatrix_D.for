	Subroutine Form_ConstitutiveMatrix(D,nDof,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	D
	Dimension		D(nDof,nDof)
!	                          
	common/Material/E,G,PR
	include 'geometry.h'
!	common/Geometry/THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH
	common/Examples/cEx(10),nEx
	character (30)	cEx
!----------------------------------------------------------
	D	   = 0.D0 !ALL
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			D(1,1) = E					!EA
			D(2,2) = .5D0*E				!GA
			D(3,3) = .5D0*E				!GA
			D(4,4) = D(1,1)/12.D0		!EI
			D(5,5) = D(1,1)/12.D0		!EI
			D(6,6) = D(1,1)/12.D0		!EI
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			D(1,1) = E					!EA
			D(2,2) = .5D0*E				!GA
			D(3,3) = .5D0*E				!GA
			D(4,4) = 256.*D(1)			!EI
			D(5,5) = 256.*D(1)			!EI
			D(6,6) = 256.*D(1)			!EI
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			D(1,1) = E					!EA
			D(2,2) = E					!GA
			D(3,3) = E					!GA
			D(6,6) = 1000.				!EI		
		CASE (4)							! 3D Str. Cantilever-LINMOD:Ex_4
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
		CASE (6:10)									!  
		CASE DEFAULT
			XK = 1.D0								! Shear Factor = 1	
			XK = 5.D0/6.D0							! Shear Factor	
		!	-----
			XI = Width*Depth*Depth*Depth/12.D0	! II
			XO = Depth*Width*Width*Width/12.D0	! IO
			XJ = (XI+XO)						! J 
			AI = E*Width*Depth*Depth*Depth/12.D0	! EII
			AO = E*Depth*Width*Width*Width/12.D0	! EIO
			GJ = (AI+AO)/(2.D0*(1.D0+PR))			! GJ 
			BM = E*Width*Depth						! EA 
			CM = XK*BM/(2.D0*(1.D0+PR))				! kGA
		!
			D(1,1) = BM
			D(2,2) = CM
			D(3,3) = CM
			D(4,4) = GJ
			D(5,5) = AI
			D(6,6) = AO
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
