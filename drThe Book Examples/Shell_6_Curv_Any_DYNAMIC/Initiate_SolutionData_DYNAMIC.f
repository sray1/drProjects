	Subroutine Initiate_SolutionData_DYNAMIC(iOut)
	Implicit Real(kind=8) (a-h,o-z)
!	
	include 'LogParams.h'
	include 'solveDyn.h'
	include 'ExamplesDYN.h'
	include 'SizeVar.h'
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!	--------------------------------------- dynamic examples
	bDynamic	= .TRUE.
!-------------------------------------------- for Check with Quintic
!	pen			= .1000D+10
!	pen			= .0995D+3	! giving best result for Pal
	pen			= .9950D+2		
!	pen			= .1000D+6
!			
	Tol			= .1000D-06
	Tol			= .1000D-07
!	Tol			= .1000D-09
	Tol			= .1000D-06
!	Tol			= .1000D-03
!-------------------------------------------- Dynamic/Newmark
	beta		= 0.25D0
	gama		= 0.5D0
	begTim		= 0.D0
!-------------------------------------------- Dynamic/Newmark End
	SELECT CASE (nExD)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			MaxIt		= 20
			delTim		= .1
			begTim		= 0.D0
			endTim		= 5.D0
			totTim		= endtim - begtim	
			tem			= beta*delTim	
			velmul		= gama/tem
     			accmul		= one/tem/delTim
			MaxSteps	= integer(totTim/delTim)  

!
	Nint1		=  nQd1-1			! Gauss Order (OPTIMAL)   
	Nint2		=  nQd2-1			! Gauss Order (OPTIMAL)   
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			ArcLen		= 2.D0			! c = .01 
			ArcLen		= 2.D0			! c = .01 
			MaxSteps	= 35			! c = .01 
			MaxSteps	= 18			! c = .01 
			MaxIt		= 20
	Nint1		=  nQd1-1			! Gauss Order (OPTIMAL)   
	Nint2		=  nQd2-1			! Gauss Order (OPTIMAL)   
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3

!			ArcLen		=  7.0D0		!
			ArcLen		=  3.0D0		!
			MaxSteps	= 24		!
			ArcLen		=  5.0D0		!
			MaxSteps	= 16			!
			ArcLen		= 10.0D0		!
			MaxSteps	= 7			!			MAX SUCCESSFUL
			MaxIt		= 20
		!	MaxIt		=  2
		!	iCutMax		= 10
	Nint1		=  nQd1-1			! Gauss Order (OPTIMAL)   
	Nint2		=  nQd2-1			! Gauss Order (OPTIMAL)   
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4
			ArcLen		= 500.D0		 
			MaxSteps	=  39			 
			MaxSteps	=  25			 
	!		MaxSteps	=  2			 
			MaxIt		=  50
	!		MaxIt		=  10
	Nint1		=  nQd1  
	Nint2		=  nQd2   
		CASE (5)							! 3D Curved Cantilev.Bathe: Ex_5
			ArcLen		= 314.5D0		!	1 Element	
			MaxSteps	= 40			!
			MaxIt		= 20
!			ArcLen		= 500.0D0		!	1 Element	
	Nint1		=  nQd1  
	Nint2		=  nQd2   
		CASE (6)							! 2D Frame Buckling-Argyris: Ex_6
			ArcLen		= .1D0			!	1 Element	
			MaxSteps	= 1			!
			MaxIt		= 20
!			ArcLen		= 500.0D0		!	1 Element	
	Nint1		=  nQd1  
	Nint2		=  nQd2   
		CASE (7:9)    ! FALL THRO'           Other: Ex_7-10...
			return 
		CASE (10)							! Hemisphere w/ hole       Ex_10
!-------------------------------------------------------- NonLinear
			MaxSteps	= 1			! 
			MaxIt		= 3
			MaxSteps	= 11		! 2x2 
			MaxSteps	= 13		! 2x2
			ArcLen		= 5.D0		! 2x2 Quintics
			MaxIt		= 20
			MaxSteps	= 45		! 1 Quintic
			MaxSteps	= 13		! 1 Quintic
			ArcLen		= 3.D0		! 1 Quintics
!			MaxSteps	= 100	! c = 0 
!--------------------------------------------------------
!	Nint1		=  nQd1-1		! NO GOOD/TOOLOW  
!	Nint2		=  nQd2-1		! NO GOOD/TOOLOW     
!	Nint1		=  nQd1+1		! NO GOOD/TOOHigh   
!	Nint2		=  nQd2+1		! NO GOOD/TOOHigh    
	Nint1		=  nQd1  
	Nint2		=  nQd2   
		CASE (11)							! Scordelis Low            Ex_11
!-------------------------------------------------------- Nonlinear Check
			MaxSteps	= 1			! c = 0 
!--------------------------------------------------------
!-------------------------------------------------------- Nonlinear
			ArcLen		= 100.D0		! c = 0 
!			ArcLen		=  50.D0		! c = 0 
			MaxSteps	=  70			! c = 0 
!			MaxSteps	=  50			! c = 0 
			MaxIt		= 20
!			MaxSteps	= 2				! Print check
			ArcLen		= 0.17D0		! R/h = 200 
			ArcLen		= 5.D-2			! R/h = 400 
			MaxSteps	= 30			! c = 0 
!--------------------------------------------------------
	Nint1		=  nQd1  
	Nint2		=  nQd2   
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12

!			ArcLen		=  7.0D0		!
			ArcLen		=  3.0D0		!
			MaxSteps	= 24		!
			ArcLen		=  5.0D0		!
			MaxSteps	= 16			!
			ArcLen		= 10.0D0		!
			MaxSteps	= 7			
			MaxSteps	= 10			
			MaxSteps	= 5			
			MaxIt		= 20
		!	MaxIt		=  2
		!	iCutMax		= 10
	Nint1		=  nQd1  
	Nint2		=  nQd2   
		CASE DEFAULT
			return
	END SELECT
!	-------------------------------------------------------
	Nint		=  Nint1*Nint2		! Gauss Order (OPTIMAL)		Total Gauss Pts
!	=======================================================
	write(iOut,1020) pen,TOL,beta,gama,
     &				 delTim,begTim,endTim,totTim,
     &				 MaxSteps,MaxIt,Nint1,Nint2,Nint
!	------
	return
 1020 Format(/ 5x,"Solution Controls"/
     &	2x,"Penalty								= ",G12.5/
     &	2x,"Convergence Tolerance				= ",G12.5/
     &	2x,"beta     							= ",F10.5/
     &	2x,"gama     							= ",F10.5/
     &	2x,"Time Step  							= ",F10.5/
     &	2x,"Begin time 							= ",F10.5/
     &	2x,"End time 							= ",F10.5/
     &	2x,"Total time 							= ",F10.5/
     &	2x,"Max. Number of Load Steps			= ",I10/
     &	2x,"Max. Number of Iterations			= ",I10/
     &	2x,"No. of Gauss-Legendre Pts.(dir1)	= ",I10/
     &	2x,"No. of Gauss-Legendre Pts.(dir2)	= ",I10/
     &	2x,"No. of Gauss-Legendre Pts.(Total)	= ",I10/
     &	)		
	end
