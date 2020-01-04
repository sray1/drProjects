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
	AlfaS = one
	AlfaT = .001D0
!
	CD = zero
	CD(1,1)		= DMem			! N11	e11
	CD(1,8)		= DMP			!		e22
	CD(8,1)		= CD(1,2)		! N22	e11
	CD(8,8)		= DMem			!		e22
!
	CD(2,2)		= Two*DM1P		!N12	e12
	CD(7,7)		= Two*DM1P		!N21	e21

	CD(3,3)		= DShe*AlfaS	!Q1		e13
	CD(9,9)		= DShe*AlfaS	!Q2		e23

	CD(4,4)		= Two*DB1P		!M11
	CD(11,11)	= Two*DB1P		!M22

	CD( 5, 5)	= DBen			!M12	k12
	CD( 5,10)	= DBP			!		k21
	CD(10, 5)	= CD( 9,10)		!M21	k12
	CD(10,10)	= DBen			!		k21	

	CD( 6, 6)	= DB1P*AlfaT	!M13	k13
	CD(12,12)	= DB1P*AlfaT	!M23	k23
!	=======================================================
	write(iOut,1020) (i,(CD(i,j),j=1,12),i=1,12)
!	------
	return
 1020 Format(/ 5x,"Condensed Constitutive Matrix "/
     &	(1x,I2,12(1x,f7.0))  )		
	end
