	Subroutine Set_ExampleType(iOut)

	Implicit Real(kind=8) (a-h,o-z)
!----------------------------------------------------------------------------------------------- PALAZOTTO
!	Change in Initiate_SupportData for Hinge -Slider (Nsup = 4)
!------------------------------------------------------------ NOTE: For Compressibility Param, c
!	SET: for c = 0
!	E			= 10.0D6				in this NonLinear_Circular_Snap_RIKS	 
!	D(3)		= D(1)/12.D0	!EI		in Subroutine Constitutive
!	ArcLen		= 100.D0				in Subroutine Initiate_SolutionData		
!	MaxSteps	= 100					in Subroutine Initiate_SolutionData			
!	nLoadLoc    = 12					! Tip Force in w-dir in Initiate_DegreeData
!	===================================	
!	SET: for c = 0.01
!	E			= 10.0D1				in this NonLinear_Circular_Snap_RIKS	 	
!	D(3)		= D(1)*256		!EI		in Subroutine Constitutive 
!	ArcLen		= 2.D0					in Subroutine Initiate_SolutionData								 
!	MaxSteps	= 18					in Subroutine Initiate_SolutionData
!	nLoadLoc    = 12					! Tip Force in w-dir in Initiate_DegreeData
!-------------------------------------------------------------------------------------------------			 
!	Change in Initiate_SupportData for Cantilevered (Nsup = 3)
!---------------------------------------------- NOTE: For Cantilevered Straight Beam/Tip Moment
!	SET:
!		THETAL	= 1.D0					in NonLinear_Circular_Snap
!		CU		= 0.D0 					in QQ_EtranDEplusGMatrix
!	ThetaL		= .001					in this NonLinear_Circular_Snap_RIKS
!	Radius		= 10000					in this NonLinear_Circular_Snap_RIKS
!	EA			= 1.0D6					in Subroutine Constitutive	 
!	GA			= 1.0D6					in Subroutine Constitutive	 
!	EI			= 1000					in Subroutine Constitutive	 
!	ArcLen		= 10.D0					in Subroutine Initiate_SolutionData		
!	MaxSteps	= 10					in Subroutine Initiate_SolutionData	
!	nLoadLoc	= 18					! Tip Mom in Initiate_DegreeData
!-------------------------------------------------------------------------------------------------			 
	common/Examples/cEx(10),nEx
	character (30)	cEx
!				 123456789012345678901234567890
      Data cEx/	"PALAZOTTO:c0=0:           Ex_1",
     &			"PALAZOTTO:c0=0.01:        Ex_2",
     &			"2D Str. Cantilever-TipMom:Ex_3",
     &			"3D Curved CantilevLINMOD: Ex_4",
     &			"3D Curved CantilevBATBOL: Ex_5",
     &			"                              ",
     &			"                              ",
     &			"                              ",
     &			"                              ",
     &			"                              "/
!-------------------------------------------- 
	nEx = 3
	write(iOut,*) 'Example Problem is ',cEx(nEx)
!	-------------
	return
	end
