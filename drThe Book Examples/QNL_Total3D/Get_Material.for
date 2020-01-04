	Subroutine Get_Material(iPrt,iOut)
!	Inverts A(nA,nA) with dimension (nDim,nDim)	
	Implicit Real(kind=8) (a-h,o-z)
!-------------------------------------------- 
	common/Material/E,G,PR
	common/Examples/cEx(10),nEx
	character (30)	cEx
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/ 
!-------------------------------------------- for Check with Quintic
	SELECT CASE (nEx)
		CASE (1)							! PALAZOTTO:c0=0:           Ex_1
			E		= 10.0D6	! c = 0	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
		CASE (2)							! PALAZOTTO:c0=0.01:        Ex_2
			E		= 10.0D1	! c = .01	 	
			G		= E/two
			PR		= (E/G/2.D0)-1.D0	! Poisson's Ratio
		CASE (3)							! 2D Str. Cantilever-TipMom:Ex_3
			E		= 1.0D6	!  	
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
		CASE (6:10)    ! FALL THRO'           Other: Ex_5... 
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
