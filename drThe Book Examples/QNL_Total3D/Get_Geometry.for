	Subroutine Get_Geometry(iPrt,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	common/Geometry/THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH
	common/Examples/cEx(10),nEx
	character (30)	cEx
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!
	piby4	= datan(1.D0)
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			THETAP	= 53.13D0				! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
			XLENGTH = RADIUS*THETAL
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			THETAP	= 53.13D0				! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			THETAL	= .001D0				! Radian						
			THETAP	= THETAL*45.D0/piby4    ! degree			
			RADIUS	= 10000.0D0	! Radius
			XLENGTH = RADIUS*THETAL			! **** Straight Beam ****! L = 10
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4 
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
		!	DEPTH	= .10D0		! Depth
		!	WIDTH	= .10D0		! Width
			THETAP	= 45.0D0				! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 10.0D0	! Radius
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5 
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			THETAP	= 45.0D0				! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
		CASE (6:10)    ! FALL THRO'           Other: Ex_5... 
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
	write(iOut,1020) THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH
!	-------------
	return
!
 1020 Format(/ 5x,"Geometry Controls"/
     &	2x,"Total Elemental Angle       = ",F10.5,1X,"degree"/
     &	2x,"Total Elemental Angle       = ",F10.5,1X,"radian"/
     &	2x,"Radius                      = ",F12.2/
     &	2x,"Length                      = ",F12.2/
     &	2x,"Depth                       = ",F10.5/
     &	2x,"Width                       = ",F10.5/
     &	)
!	--------     		
	end
