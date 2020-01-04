	Subroutine Form_Constitutive_Condensed(D,nCMat,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	include 'Examples.h'
	include 'geometry.h'
	include 'Material.h'
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA half/0.5D0/,quart/0.25D0/
!----------------------------------------------------------
	XK		= 5.D0/6.D0							! Shear Factor	
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
	DMem = E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = DMem*DEPTH*DEPTH/12.D0	! Bending
	DShe = G*DEPTH					! Shear	
!	------------------------------------------
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2		I/A = 256
	DMem = E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = DMem*DEPTH*DEPTH/12.D0	! Bending
	DBen = 256.D0*E			!EI
	DShe = Two*G*DEPTH					! Shear	
	DQad = DBen
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
	DMem = E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = 1000.D0					! Bending
	DShe = XK*G*DEPTH				! Shear		 	
!	------------------------------------------
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
!			D(1,1) = BM
!			D(2,2) = CM
!			D(3,3) = CM
!			D(4,4) = GJ
!			D(5,5) = AI
!			D(6,6) = AO
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
!			D(1,1) = BM
!			D(2,2) = CM
!			D(3,3) = CM
!			D(4,4) = GJ
!			D(5,5) = AI
!			D(6,6) = AO
		CASE (6)							! 2D Frame Buckle- Argyris: Ex_6
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
!			D(1,1) = BM
!			D(2,2) = CM
!			D(3,3) = CM
!			D(4,4) = GJ
!			D(5,5) = AI
!			D(6,6) = AO
		CASE (7:10)    ! FALL THRO'           Other: Ex_6... 
		CASE DEFAULT
			XK = 5.D0/6.D0							! Shear Factor	
		!	-----
			return
	END SELECT
!	=======================================================
	DMP		= DMem*PR
	DM1P	= DMem*(1.D0-PR)*half
	DBP		= DBen*PR
	DB1P	= DBen*(1.D0-PR)*half
!============================== condensed form
	CD = zero
	CD( 1, 1)	= DMem			! Membrane
	CD( 1, 2)	= DMP
	CD( 2, 1)	= CD(1,2)
	CD( 2, 2)	= DMem
	CD( 3, 3)	= DM1P

	CD( 1, 9)	= DBen			! Membrane due to Quadrat and vice versa
	CD( 1,10)	= DBP
	CD( 2, 9)	= DBP
	CD( 2,10)	= DBen
	CD( 3,11)	= DB1P
	CD( 9, 1)	= CD( 1, 9)		
	CD(10, 1)	= CD( 1,10)
	CD( 9, 2)	= CD( 2, 9)
	CD(10, 2)	= CD( 2,10)
	CD(11, 3)	= CD( 3,11)
!	----------------
	CD(4,4)	= DShe			! Shear
	CD(5,5)	= DShe

	CD(6,6)	= DBen			! Bending
	CD(6,7)	= DBP
	CD(7,6)	= CD(6,7)
	CD(7,7)	= DBen
	CD(8,8)	= DB1P
!	=======================================================
	write(iOut,1020) (i,(CD(i,j),j=1,11),i=1,11)
!	------
	return
 1020 Format(/ 5x,"Condensed Constitutive Matrix "/
     &	(2x,I2,11(2x,f7.0))  )		
	end
