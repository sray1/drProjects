	Subroutine Form_ConstitutiveMatrix(D,nCMat,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	D
	Dimension		D(nCMat,nCMat) 
!	                          
	include 'Examples.h'
	include 'geometry.h'
	include 'Material.h'
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA half/0.5D0/,quart/0.25D0/
!----------------------------------------------------------
	D		= 0.D0 !ALL
	XK		= 5.D0/6.D0							! Shear Factor	
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
	DMem = E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = DMem*DEPTH*DEPTH/12.D0	! Bending
	DShe = G*DEPTH					! Shear	
!	------------------------------------------
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
	DMem = E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = DMem*DEPTH*DEPTH/12.D0	! Bending
	DBen = 256.D0*E			!EI
	DShe = G*DEPTH					! Shear	
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
			D(1,1) = BM
			D(2,2) = CM
			D(3,3) = CM
			D(4,4) = GJ
			D(5,5) = AI
			D(6,6) = AO
		CASE (7:10)    ! FALL THRO'           Other: Ex_6... 
		CASE DEFAULT
			XK = 5.D0/6.D0							! Shear Factor	
		!	-----
			return
	END SELECT
!	=======================================================
	DMP		= DMem*PR
	qDM1P	= quart*DMem*(1.D0-PR)*half
	qDM1P	= quart*DMem*(1.D0-PR)
	DBP		= DBen*PR
	qDB1P	= quart*DBen*(1.D0-PR)*half
	qDB1P	= quart*DBen*(1.D0-PR)
!============================== condensed form
!	D(1,1)	= DMem
!	D(1,2)	= DMP
!	D(2,1)	= D(1,2)
!	D(2,2)	= DMem
!	D(3,3)	= DM1P
!	D(4,4)	= DShe
!	D(5,5)	= DShe
!	D(6,6)	= DBen
!	D(6,7)	= DBP
!	D(7,6)	= D(6,7)
!	D(7,7)	= DBen
!	D(8,8)	= DB1P
!============================================================ expanded form
	D			= 0.D0
!
	D( 1, 1)	= DMem
	D( 1, 8)	= DMP
	D( 8, 1)	= D( 1, 8)
	D( 2, 2)	= qDM1P
	D( 2, 7)	= -qDM1P
	D( 7, 2)	= D( 2, 7)

	D( 3, 3)	= DShe

	D( 4, 4)	= qDB1P
	D( 4,11)	= -qDB1P
	D(11, 4)	= D( 4,11)

	D( 5, 5)	= DBen
	D( 5,10)	= DBP
	D(10, 5)	= D( 5,10)

	D( 7, 7)	= qDM1P

	D( 8, 8)	= DMem

	D( 9, 9)	= DShe

	D(10,10)	= DBen

	D(11,11)	= qDB1P

!	=======================================================
	write(iOut,1020) (i,(D(i,j),j=1,nCMat),i=1,nCMat)
!	------
	return
 1020 Format(/ 5x,"Constitutive Matrix "/
     &	(2x,I2,12(2x,f9.0))  )		
	end
