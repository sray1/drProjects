	Subroutine Get_Material(iPrt,iOut)
!	Inverts A(nA,nA) with dimension (nDim,nDim)	
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	include 'material.h'
	include 'Examples.h'
	include 'SizeVar.h'
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
	DATA half/0.5D0/,quart/0.25D0/
!-------------------------------------------- for Check with Quintic
	nCMat	= 12				! dimension for Constitutive Matrix

	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			E		= 10.0D6*half	! c = 0		! NODRILL	 	
!			E		= 10.0D6*one	! c = 0		! DRILL	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			E		= 10.0D1*half	! c = .01	! NODRILL	 	
!			E		= 10.0D1*one	! c = .01	! DRILL	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			E		= 1.0D6	!  	
!			E		= 1200.D0	!  	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0		! Poisson's Ratio
		CASE (4)							! 3D Curved CantilevLINMOD: Ex_4 
			E		= 10.5D6	! ORIGINAL	 	
			G		= 4.0D6		! ORIGINAL
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
		CASE (5)							! 3D Curved Cantilev-Bathe: Ex_5 
			E		= 10.0D6	! c = 0	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
		CASE (6)							! 2D Frame Buckle-Argyris:  Ex_6 
			E		= 71240.D0			! c = 0	 	
			PR		= 0.31D0				! Poisson's Ratio
			G		= E/(one+PR)/two
		CASE (7:9)    ! FALL THRO'           Other: Ex_7-10... 
			return
		CASE (10)							! Hemisphere w/ hole      :Ex_10
			E		= 6.825D7	! 	 	
			PR		= 0.3D0	! Poisson's Ratio
			G		= E/(two*(one+PR))
		CASE (11)							! Scordelis Low           :Ex_11
			E		= 3.10275D0	! 	 	kN/mm squared
			PR		= 0.3D0	! Poisson's Ratio
			G		= E/(two*(one+PR))
		CASE (12)							! 2D Str. Cantil-Tip Twist:Ex_12
			E		= 12.0D6	! c = 0	 	
			PR		= 0.3D0	! Poisson's Ratio
			G		= E/(two*(one+PR))
		CASE DEFAULT
			return
	END SELECT
!	---------------------------------------------- 3D Linear
!	E		= 10.5D6	! ORIGINAL	 	
!	G		= 4.0D6		! ORIGINAL
!	PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
!	RADIUS	= 10.0D0	! Radius
!	=======================================================
	write(iOut,1020) E,G,PR
!	-------------
	return
!
 1020 Format(/ 5x,"Real Controls"/
     &	2x,"Elasticity Modulus          = ",G12.5/
     &	2x,"Shear Modulus               = ",G12.5/
     &	2x,"Poisson's Ratio             = ",F10.5/
     &	)
!	--------     		
	end
