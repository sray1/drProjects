	Subroutine Define_ElementTypes(iOut)
	Implicit Real(kind=8) (a-h,o-z)

	common/ElementType/ElType(10),ElDeg(5)
	character (20)	ElType
	character(10)   ElDeg
!                       12345678901234567890
	DATA  ElDeg		/"LINEAR    ",
     &				 "QUADRATIC ", 
     &				 "CUBIC     ", 
     &				 "QUARTIC   ", 
     &				 "QUINTIC   "/ 
	DATA  ElType	/"2D Linear Truss     ", 
     &                 "3D Linear Truss     ", 
     &                 "2D NonLinear Truss  ", 
     &                 "3D NonLinear Truss  ", 
     &                 "2D Linear Beam      ", 
     &                 "2D Linear Beam      ", 
     &                 "2D NonLinear Beam   ", 
     &                 "3D NonLinear Beam   ", 
     &                 "Plain Strain        ", 
     &                 "Plain Stress        "/ 
!	-------------
	return
	end
