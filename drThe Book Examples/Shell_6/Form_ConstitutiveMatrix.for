	Subroutine Form_ConstitutiveMatrix(DMat,nCMat,iOut)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	include 'Examples.h'
	include 'geometry.h'
	include 'Material.h'

	Real(kind=8)	DMat   
	Dimension		DMat(nCMat,nCMat)

	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
	DATA half/0.5D0/,quart/0.25D0/
!----------------------------------------------------------
	AlfaS = one
	AlfaT = .01D1		! for TipTwist/ Shallow Shell
!
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
	AlfaT = .01D3		! for TipMoment
	DMem = half*E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = 1000.D0					! Bending
	DBen = 500.D0					! Bending
!	DShe = XK*G*DEPTH				! Shear		 	
	DShe = G*DEPTH					! Shear		 	
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
		CASE (7:9)    ! FALL THRO'           Other: Ex_7... 
			return
		CASE (10)							! Hemisphere w/ Hole       Ex_10
	AlfaT = .01D0		! for Hemisphere
	DMem = E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = DMem*DEPTH*DEPTH/12.D0	! Bending
	DShe = G*DEPTH					! Shear	
		CASE (11)							! Scordelis Low            Ex_11
	AlfaT = .01D0		! for Shallow Shell
	DMem = E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = DMem*DEPTH*DEPTH/12.D0	! Bending
	DShe = XK*G*DEPTH					! Shear	
!	------------------------------------------
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12
	DMem = half*E*DEPTH/(1.D0-PR*PR)		! Membrane
	DBen = DMem*DEPTH*DEPTH/12.D0	! Bending
	DShe = G*DEPTH					! Shear	
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
	DMat = zero
!
	DMat(1,1)		= DMem			! N11	e11
	DMat(1,8)		= DMP			!		e22
	DMat(8,1)		= DMat(1,8)		! N22	e11
	DMat(8,8)		= DMem			!		e22
!
	DMat(2,2)		= Two*DM1P		!N12	e12
	DMat(7,7)		= Two*DM1P		!N21	e21

	DMat(3,3)		= DShe*AlfaS	!Q1		e13
	DMat(9,9)		= DShe*AlfaS	!Q2		e23

	DMat(4,4)		= Two*DB1P		!M11			: Twist
	DMat(11,11)		= Two*DB1P		!M22			: Twist

	DMat( 5, 5)		= DBen			!M12	k12		: Bending
	DMat( 5,10)		= DBP			!		k21
	DMat(10, 5)		= DMat( 5,10)	!M21	k12
	DMat(10,10)		= DBen			!		k21		: Bending

	DMat( 6, 6)		= DB1P*AlfaT	!M13	k13
	DMat(12,12)		= DB1P*AlfaT	!M23	k23
!	=======================================================
	write(iOut,1020) AlfaS,AlfaT,(i,(DMat(i,j),j=1,12),i=1,12)
!	------
	return
 1020 Format(/ 5x,"Condensed Constitutive Matrix "/
     &       / 5x,"AlfaS = ",f10.4/
     &         5x,"AlfaT = ",f10.4/
     &		(1x,I2,12(1x,F8.0))  )		
	end
