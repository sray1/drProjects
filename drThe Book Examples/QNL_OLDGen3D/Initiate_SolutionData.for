	Subroutine Initiate_SolutionData(Tol,ArcLen,MaxSteps,
     &				MaxIt,iCutMax,iOut)
!     &				MaxIt,iCutMax,iOut,FacLoad)
	
	Implicit Real(kind=8) (a-h,o-z)
!
	Tol			= .1000D-05
	Tol			= .1000D-03
!-------------------------------------------------------------------------------- Geometry: PALAZOTTO
!	ArcLen		= 100.D0		! c = 0 
!	MaxSteps	=  12			! c = 0 
!	MaxIt		= 20
!	ArcLen		= 100.D0		! c = 0 
!	MaxSteps	= 70			! c = 0 
!	ArcLen		= 500.D0		! c = 0 
!	MaxSteps	= 15			! c = 0 
!	ArcLen		= 200.D0		! c = 0 
!	MaxSteps	= 35			! c = 0 
!	ArcLen		= 2.D0			! c = .01 
!	MaxSteps	= 18			! c = .01 
!-------------------------------------------------------------------------------- Geometry: Keith
!	ArcLen		= 10.0D0		!
!	MaxSteps	= 12			!
!	MaxSteps	=  1			!
!	MaxIt		= 20
!	MaxIt		=  2
!	iCutMax		= 10
!-------------------------------------------------------------------------------- Geometry: Bathe
!	ArcLen		= 330.0D0		!	2 Elements Model
!	-----------------------------------------
	ArcLen		= 314.5D0		!	1 Element	
	MaxSteps	= 20			!
	MaxIt		= 20
	ArcLen		= 500.0D0		!	1 Element	
!	-----------------------------------------
!	MaxIt		=  1
!	iCutMax		= 10
!-------------------------------------------------------------------------------- Geometry: 3DLIN
	ArcLen		= 500.0D0		!
	MaxSteps	= 39			!
	MaxIt		= 50
!	MaxSteps	=  1			!
!	MaxIt		=  2
!	iCutMax		= 10
!!----------------------------------------------------------------------------------------------------	 
	write(iOut,1020) TOL,ArcLen,MaxSteps,MaxIt,iCutMax
!	------
	return
 1020 Format(/ 5x,"Solution Controls"/
     &	2x,"Convergence Tolerance            = ",G12.5/
     &	2x,"Arc Length                       = ",F10.5/
     &	2x,"Max. Number of Load Steps        = ",I10/
     &	2x,"Max. Number of Iterations        = ",I10/
     &	2x,"Max. Subdivision of Iterations   = ",I10/
     &	)		
	end