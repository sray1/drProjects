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
	if(bDrill) then
			nSup	= 36					! Hinge/Slide Symmetric: 2D Arch     DRILL SAVE
			nStif3  =  8					! UnSupported Theta3 DOFs
	else
			nSup	= 44					! Hinge/Slide Symmetric: 2D Arch   NODRILL SAVE
			nStif3  = 0						! UnSupported Theta3 DOFs
	endif
			nLod    = 2						! No. of Loaded DOFs
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
	if(bDrill) then
			nSup	= 32					! Hinge/Slide Symmetric: 2D Arch     DRILL SAVE
			nStif3  = 20					! UnSupported Theta3 DOFs
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 4					! 5 = Cubic with Poisson's = 0
			nLod    = 4						! No. of Loaded DOFs: for Quartic
	else
			nSup	= 44					! Hinge/Slide Symmetric: 2D Arch   NODRILL SAVE
			nStif3  = 0						! UnSupported Theta3 DOFs
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 2					! 2 = linear with Poisson's = 0
			nLod    = 2						! No. of Loaded DOFs
	endif
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
	if(bDrill) then
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 5					! 5 = Cuartic with Poisson's = 0
			nSup	= 30					!  for Quintic							DRILL SAVE
			nStif3  = 25					! UnSupported Theta3 DOFs
			nLod    = 5						! No. of Loaded DOFs: Tip Mom along y
	else
			nQd1		= 6					! 5 = Quartic/ 6 = Quintic
			nQd2		= 2					! 2 = linear with Poisson's = 0
!			nSup	= 28 + 8 !(Theta3)		!  for Quartic							NODRILL SAVE												
			nSup	= 32 + 10 !(Theta3)		!  for Quintic							NODRILL SAVE
			nStif3  = 0						! UnSupported Theta3 DOFs
			nLod    = 2						! No. of Loaded DOFs: Tip Mom along y
	endif
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
		CASE (7:10)    ! FALL THRO'           Other: Ex_5... 
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
