	Subroutine Initiate_SolutionData(iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	
	include 'LogParams.h'
	include 'solve.h'
	include 'Examples.h'
	include 'SizeVar.h'
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
!	pen			= .1000D+10
!	pen			= .0995D+3	! giving best result for Pal
	pen			= .9950D+2		
!	pen			= .1000D+6
!			
	Tol			= .1000D-06
	Tol			= .1000D-07
!	Tol			= .1000D-09
	Tol			= .1000D-03
!	Tol			= .1000D-03
!
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			ArcLen		= 100.D0		! c = 0 
!			ArcLen		=  50.D0		! c = 0 
			MaxSteps	=  70			! c = 0 
!			MaxSteps	=  50			! c = 0 
			MaxIt		= 20
		!	ArcLen		= 100.D0		! c = 0 
		!	MaxSteps	= 70			! c = 0 
		!	ArcLen		= 500.D0		! c = 0 
		!	MaxSteps	= 15			! c = 0 
		!	ArcLen		= 200.D0		! c = 0 
		!	MaxSteps	= 35			! c = 0 
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			ArcLen		= 2.D0			! c = .01 
			ArcLen		= 2.D0			! c = .01 
			MaxSteps	= 35			! c = .01 
			MaxSteps	= 18			! c = .01 
			MaxIt		= 20
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
!			ArcLen		= 10.0D0		!

			ArcLen		=  7.0D0		!
			MaxSteps	= 30		!
			MaxSteps	= 13			!
			MaxIt		= 20
		!	MaxIt		=  2
		!	iCutMax		= 10
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
			ArcLen		= 500.D0		 
			MaxSteps	=  39			 
			MaxSteps	=  25			 
	!		MaxSteps	=  2			 
			MaxIt		=  50
	!		MaxIt		=  10
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
			ArcLen		= 314.5D0		!	1 Element	
			MaxSteps	= 40			!
			MaxIt		= 20
!			ArcLen		= 500.0D0		!	1 Element	
		CASE (6)							! 2D Frame Buckling-Argyris: Ex_6
			ArcLen		= .1D0			!	1 Element	
			MaxSteps	= 1			!
			MaxIt		= 20
!			ArcLen		= 500.0D0		!	1 Element	
		CASE (7:10)    ! FALL THRO'           Other: Ex_5... 
		CASE DEFAULT
			return
	END SELECT
!	-------------------------------------------------------
	Nint1		=  nQd1-1			! Gauss Order (OPTIMAL)   
	Nint2		=  nQd2-1			! Gauss Order (OPTIMAL)   
	Nint		=  Nint1*Nint2		! Gauss Order (OPTIMAL)		Total Gauss Pts
!	=======================================================
	write(iOut,1020) pen,TOL,ArcLen,MaxSteps,MaxIt,iCutMax,
     &				Nint1,Nint2,Nint
!	------
	return
 1020 Format(/ 5x,"Solution Controls"/
     &	2x,"Penalty								= ",G12.5/
     &	2x,"Convergence Tolerance				= ",G12.5/
     &	2x,"Arc Length							= ",F10.5/
     &	2x,"Max. Number of Load Steps			= ",I10/
     &	2x,"Max. Number of Iterations			= ",I10/
     &	2x,"Max. Subdivision of Iterations    = ",I10/
     &	2x,"No. of Gauss-Legendre Pts.(dir1)	= ",I10/
     &	2x,"No. of Gauss-Legendre Pts.(dir2)	= ",I10/
     &	2x,"No. of Gauss-Legendre Pts.(Total)	= ",I10/
     &	)		
	end
