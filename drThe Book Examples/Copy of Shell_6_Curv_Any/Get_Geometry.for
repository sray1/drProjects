	Subroutine Get_Geometry(iPrt,iOut)
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'Drill.h'
	include 'Output.h'
	include 'geometry.h'
	include 'Examples.h'
	include 'SizeVar.h'
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!
	piby4	= datan(1.D0)
	pi		= piby4*4.D0
!-------------------------------------------- for Check with Quintic
!	=======================================================
	iGeom	= 0 
	iCont	= 0					! 0 = C0/1 = C1/ 2 = C2
	nDim	= 3					! 2 = 2D Flat Plate/3= 3D Shell
	nDof	= 6					! dof per node: u,v,w,th_1,th_2,th_n
!	================================================================
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			DEPTH	= 1.0D0				! Depth = thickness
			WIDTH	= 1.0D0				! Width	= Dir. 2
			THETAP	= 53.13D0				! degree	Dir. 1
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
			XLENGTH = RADIUS*THETAL
			nQc1	= 4 
			nQc2	= 2
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 2					! 2 = linear with Poisson's = 0
			nElem	=  1					! no. of Elements
			nStif3  = 20						! UnSupported Theta3 DOFs
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 2					! 2 = linear with Poisson's = 0
			nSup	= 16					! Hinge/Slide Symmetric: 2D Arch   
			nLod    = 2						! No. of Loaded DOFs
	nPStep		= 10
	nPtsi		= 49	! for Plot Loop
	nPtsj		=  2	! for Plot Loop
	nPtsDef		= nPtsi*nPtsj
	nDis		= 49	! for Print Loop
	nStr		= 49	! for Print Loop
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			THETAP	= 53.13D0				! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
			XLENGTH = RADIUS*THETAL
			nQc1	= 4 
			nQc2	= 2
			nElem	=  1					! no. of Elements
			nStif3  = 20						! UnSupported Theta3 DOFs
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 2					! 2 = linear with Poisson's = 0
!			nQd2		= 4					! 4 = cubic with Poisson's = 0
			nSup	= 16					! Hinge/Slide Symmetric: 2D Arch   DRILL SAVE       01/28/04
			nLod    = 2						! No. of Loaded DOFs:DRILL
!			nSup	= 44					! Hinge/Slide Symmetric: 2D Arch   SAVE
!			nLod    = 2						! No. of Loaded DOFs
	nPStep		= 10
	nPtsi		= 49	! for Plot Loop
	nPtsj		=  2	! for Plot Loop
	nPtsDef		= nPtsi*nPtsj
	nDis		= 49	! for Print Loop
	nStr		= 49	! for Print Loop
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			XLENGTH = 10.D0			! **** Straight Beam ****! L = 10
			nQc1	= 2 
			nQc2	= 2
			nElem	=  1					! no. of Elements
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 2					! 2 = linear with Poisson's = 0
!			nSup	= 28 + 8 !(Theta3)		!  for Quartic							NODRILL SAVE												
			nSup	= 32 + 10 !(Theta3)		!  for Quintic							NODRILL SAVE
			nSup	= 12 + 10 !(Theta3)		!  for Quintic							NODRILL SAVE
			nSup	= 12 +  0 !(Theta3)		!  for Quintic							NODRILL SAVE
			nStif3  = 0						! UnSupported Theta3 DOFs
			nLod    = 2						! No. of Loaded DOFs: Tip Mom along y
	nPtsi		= 49	! for Plot Loop
	nPtsj		=  2	! for Plot Loop
	nPtsDef		= nPtsi*nPtsj + 1			! extra 1 to close loop
	nDis		= 49	! for Print Loop
	nStr		= 49	! for Print Loop
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4 
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			THETAP	= 45.0D0				! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 10.0D0	! Radius
			nQc1	= 6 
			nQc2	= 2
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 2					! 2 = linear with Poisson's = 0
			nElem	=  2					! no. of Elements
			nSup	=  6				
			nLod    = 1						! No. of Loaded DOFs
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5 
			DEPTH	= 1.0D0		! Depth
			WIDTH	= 1.0D0		! Width
			THETAP	= 45.0D0				! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 100.0D0	! Radius
			nQc1	= 2 
			nQc2	= 2
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 6					! 5 = Quartic/ 6 = Quintic
			nElem	=  1					! no. of Elements
			nSup	=  6				
			nLod    = 1						! No. of Loaded DOFs
		CASE (6)							! 2D Frame Buckle. Argyris: Ex_6 
			DEPTH	= 30.0D0		! Depth
			WIDTH	= 0.6D0			! Width
			THETAP	= 0.0D0					! degree
			THETAL	= THETAP*piby4/45.D0	! Radian
			RADIUS	= 10000.0D0	! Radius
			nQc1	= 2 
			nQc2	= 2
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 6					! 5 = Quartic/ 6 = Quintic
			nElem	=  2					! no. of Elements
			nSup	=  6				
			nLod    = 1						! No. of Loaded DOFs
		CASE (7:9)    ! FALL THRO'           Other: Ex_7-10...
			return 
		CASE (10)							! Hemisphere w. hole         Ex_10
			DEPTH	= 0.02D0				! Depth = thickness in mm dor		R/h = 500
			DEPTH	= 0.04D0				! Depth = thickness in mm dor		R/h = 250
			WIDTH	= 1.0D0					! Width	= Dir. 2 in mm				NOT NEEDED
			THETAL	= 0.1D0					! Radian
			THETAP	= THETAL*180.D0/pi		! degree	Dir. 1
			RADIUS	= 10.0D0				! Radius in mm
			XLENGTH = RADIUS*THETAL
			nQc1	= 4 
			nQc2	= 4
!			===========================================================
			nLod	= 2					! No. of Loaded DOFs
!			=========================================================== # of Elements
			nElem	=  4					! no. of Elements
			nElem	=  1					! no. of Elements
!			=========================================================== Septic/Septic
			nQd1		= 8					! 8 = Septic/ 6 = Quintic
			nQd2		= 8					! 4 = Cubic 
			nSup		= 48				! free Symmetric: Shell   
!			===========================================================
!			=========================================================== Octic/Octic
			nQd1		= 9					! 9 = Octic/ 6 = Quintic
			nQd2		= 9					! 4 = Cubic 
			nSup		= 54				! free Symmetric: Shell   
!			=========================================================== Quintic/Quintic
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 6					! 4 = Cubic 
			if(nElem == 1) then
!				nSup		= 36				! free Symmetric: Shell   
				nSup		= 37				! free Symmetric: Shell  
! 
	nPtsi		= 49	! for Plot Loop
	nPtsj		=  2	! for Plot Loop
	nPtsDef		= nPtsi*(nPtsj+1)
	nDis		= 49	! for Print Loop
	nStr		= 49	! for Print Loop
			elseif(nElem == 4) then
!				nSup		= 66				! free Symmetric: Shell   
				nSup		= 67				! free Symmetric: Shell  
! 
	nPtsi		= 49	! for Plot Loop
!	nPtsi		=  5	! for Plot Loop
	nPtsj		=  2	! for Plot Loop
	nPtsDef		= 4*nPtsi + 1
	nDis		= 49	! for Print Loop
	nStr		= 49	! for Print Loop
			endif
!			===========================================================
!			===========================================================
			nStif3  = 20						! UnSupported Theta3 DOFs
		CASE (11)							! Scordelis Low             Ex_1
			DEPTH	= 6.35D0				! Depth = thickness in mm dor		R/h = 400
			DEPTH	= 12.7D0				! Depth = thickness in mm dor		R/h = 200
			WIDTH	= 254.0D0				! Width	= Dir. 2 in mm
			THETAL	= 0.1D0					! Radian
			THETAP	= THETAL*180.D0/pi		! degree	Dir. 1
			RADIUS	= 2540.0D0				! Radius in mm
			XLENGTH = RADIUS*THETAL
			nQc1	= 4 
			nQc2	= 2
!			=========================================================== Quintic/Cubic
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 4					! 4 = Cubic 
			nSup		= 40				! Hinge/Slide Symmetric: Shell   
!			=========================================================== Quintic/Quintic
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 6					! 4 = Cubic 
			nSup		= 52				! Hinge/Slide Symmetric: Shell   
!			===========================================================
			nElem	=  1					! no. of Elements
			nStif3  = 20						! UnSupported Theta3 DOFs
			nLod    = 1						! No. of Loaded DOFs
	nPtsi		= 49	! for Plot Loop
	nPtsj		=  2	! for Plot Loop
	nPtsDef		= nPtsi*(nPtsj+1)
	nDis		= 49	! for Print Loop
	nStr		= 49	! for Print Loop
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12
			DEPTH	= 0.1D0		! Depth
			WIDTH	= 0.25D0		! Width
			XLENGTH = 1.D0			! **** Straight Beam ****! L = 1
			nQc1	= 2 
			nQc2	= 2
!			==================================================
			nElem	=  1					! no. of Elements
!			nElem	=  2					! no. of Elements
!			==================================================
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
	if(bDrill) then
			nQd2		= 4					! 4 = Cubic with Poisson's = 0
			nSup	= 24 +  0 !(Theta3)		!  for Cubic/Quintic				DRILL SAVE
			nLod    = 4						! No. of Loaded DOFs: Tip Twist
			nPtsj	= 2						! for Plot Loop
	else
			nQd2		= 2					! 2 = linear with Poisson's = 0
			nSup	= 12 +  0 !(Theta3)		!  for Quintic							NODRILL SAVE
			nLod    = 2						! No. of Loaded DOFs: Tip Twist 
			nPtsj	= 2						! for Plot Loop
	endif
			nStif3  = 0						! UnSupported Theta3 DOFs
	nPtsi		= 49	! for Plot Loop
	nPtsDef		= nPtsi*nPtsj + 1			! extra 1 to close loop
	nDis		= 49	! for Print Loop
	nStr		= 49	! for Print Loop
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
	write(iOut,1020) THETAP,THETAL,RADIUS,XLENGTH,DEPTH,WIDTH,
     &		nQc1,nQc2,nQd1,nQd2,nSup,nLod
!	-------------
	return
!
 1020 Format(/ 5x,"Geometry and DOFs Controls"/
     &	2x,"Total Elemental Angle       = ",F10.5,1X,"degree"/
     &	2x,"Total Elemental Angle       = ",F10.5,1X,"radian"/
     &	2x,"Radius                      = ",F12.2/
     &	2x,"Length                      = ",F12.2/
     &	2x,"Depth                       = ",F10.5/
     &	2x,"Width                       = ",F10.5/
     &	2x,"Element Geometry Order      = ",I10, 1X,"nQc1"/
     &	2x,"Element Geometry Order      = ",I10, 1X,"nQc2"/
     &	2x,"Displacement Order          = ",I10, 1X,"nQd1"/
     &	2x,"Displacement Order          = ",I10, 1X,"nQd2"/
     &	2x,"No. of Supported DOFs       = ",I10/,
     &	2x,"No. of Loaded DOFs          = ",I10/
     &	)
!	--------     		
	end
