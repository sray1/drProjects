	Subroutine Get_MaterialData(D,nDof,iDebug,iOut)
!	Inverts A(nA,nA) with dimension (nDim,nDim)	
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	Real(kind=8)	D       
	Dimension		D(nDof,nDof)
	common/Material/E,G,PR
	common/Geometry/THETAP,THETAL,RADIUS,DEPTH,WIDTH
	common/Examples/cEx(10),nEx
	character (30)	cEx
!      Data cEx/	"PALAZOTTO:c0=0:           Ex_1",
!     &			"PALAZOTTO:c0=0.01:        Ex_2",
!     &			"2D Str. Cantilever-TipMom:Ex_3",
!     &			"3D Str. Cantilever-Bathe: Ex_4",
!     &			"                              ",
!     &			"                              ",
!     &			"                              ",
!     &			"                              ",
!     &			"                              ",
!     &			"                              "/
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!
	piby4	= datan(1.D0)
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			E		= 10.0D6	! c = 0	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
			THETAP	= 53.13D0			! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			E		= 10.0D1	! c = .01	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
			THETAP	= 53.13D0			! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			E		= 10.0D6	! c = 0	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0		! Poisson's Ratio
			THETAP	= 0.D0					! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 10000.0D0	! Radius
		CASE (4:10)    ! FALL THRO'           3D Str. Cantilever-Bathe: Ex_4 
		CASE DEFAULT
			return
	END SELECT
!-------------------------------------------------------------------------------- Geometry: PALAZOTTO
!	E		= 10.0D6	! c = 0	 	
!	E		= 10.0D1	! c = .01	 	
!	G		= E/two
!	PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
!	THETAP	= 53.13D0			! degree
!	piby4		= datan(1.D0)
!	THETAL	= THETAP*piby4/45.D0	! Radian
!	RADIUS	= 100.0D0	! Radius
!-------------------------------------------------------------------------------- Geometry: Straight
!	E		= 1.0D6	 	
!	G		= E/two
!	PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
!	THETAL	= .001D0						! **** Straight Beam ****
!	THETAP	= THETAL*45.D0/piby4
!	RADIUS	= 10000.0D0	! Radius
!-----------------------------------------------------------------
	DEPTH	= 1.0D0		! Depth
	WIDTH	= 1.0D0		! Width
!	-------------------------------------|------|----------------- Constitutive
	if(iDebug == 1) write(iOut,2007)
	call ConstitutiveMatrix_D(D,E,PR,Width,Depth,nDof,iOut)
!	=======================================================
	write(iOut,1020) E,PR,THETAP,THETAL,RADIUS,DEPTH,WIDTH
!	-------------
	return
!
 1020 Format(/ 5x,"Real Controls"/
     &	2x,"Elasticity Modulus          = ",G12.5/
     &	2x,"Poisson's Ratio             = ",F10.5/
     &	2x,"Total Elemental Angle       = ",F10.5,1X,"degree"/
     &	2x,"Total Elemental Angle       = ",F10.5,1X,"radian"/
     &	2x,"Radius                      = ",F12.2/
     &	2x,"Depth                       = ",F10.5/
     &	2x,"Width                       = ",F10.5/
     &	)
 2007 Format(/2x,"Entering: Constitutive"/)
!	--------     		
	end
