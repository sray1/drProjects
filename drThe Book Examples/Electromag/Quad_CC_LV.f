	Subroutine Quad_CC_LV(Nint,F,nF)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element:LOAD VECTOR
!
!
!	Inputs
!		Qf(4)		= Load Coeffs at Bez. Pts at r = 1 Side
!		xLenY		= Length of side at r = 1
!		 	
!	Outputs 
!		F(nF)	1= Desired Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
!	Output Variables & Arrays	
!
	Real(kind=8)	F
	Dimension		F(nF)
	
!
	Call Quad_CC_Charg(Nint,F,nF,Iout)
!   
!--------------------------------------------------------
!	Done
!
	return
	end 
	
