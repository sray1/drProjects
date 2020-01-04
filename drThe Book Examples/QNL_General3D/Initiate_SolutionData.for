	Subroutine Initiate_SolutionData(iOut)
!	
	Implicit Real(kind=8) (a-h,o-z)
	common/SolVar/	  detKO,detK,delLmO,DelLm,iTermO,iTerRef,
     &				  delLamdaiO,SLamdam,SLamdamO,DeltaLamdai,ArcLen,
     &				  Tol,MaxSteps,MaxIt,iCutMax,Imaginary
	LOGICAL			  Imaginary		
!
	common/Examples/cEx(10),nEx
	character (30)	cEx
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
	Tol			= .1000D-03
!	Tol			= .1000D-06
!	Tol			= .1000D-02
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			ArcLen		= 100.D0		! c = 0 
			MaxSteps	=  70			! c = 0 
			MaxIt		= 20
		!	ArcLen		= 100.D0		! c = 0 
		!	MaxSteps	= 70			! c = 0 
		!	ArcLen		= 500.D0		! c = 0 
		!	MaxSteps	= 15			! c = 0 
		!	ArcLen		= 200.D0		! c = 0 
		!	MaxSteps	= 35			! c = 0 
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
		!	ArcLen		= 2.D0			! c = .01 
		!	MaxSteps	= 18			! c = .01 
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			ArcLen		= 10.0D0		!
			MaxSteps	= 30		!
		!	MaxSteps	= 20			!
			MaxIt		= 20
		!	MaxIt		=  2
		!	iCutMax		= 10
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
			ArcLen		= 1500.D0		 
			ArcLen		= 500.D0		 
			MaxSteps	=  60			 
			MaxSteps	=  10			 
			MaxIt		=  50
!			MaxIt		=  2
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
			ArcLen		= 314.5D0		!	1 Element	
			MaxSteps	= 20			!
			MaxIt		= 20
!			ArcLen		= 500.0D0		!	1 Element	
		CASE (6:10)    ! FALL THRO'           Other: Ex_5... 
		CASE DEFAULT
			return
	END SELECT
!	=======================================================
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
