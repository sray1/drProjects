	Subroutine Set_ExtLoad_Y(Qf,nQ,iOut)
	
	real(kind = 8)	Qf
	Dimension		Qf(nQ)
!	
	Qf		= 0.		! All Zero
	Qf(1)	= -1.0		! B-Load
!
	return
	end
	Subroutine Quad_QQ_LVY(Qf,nQ,F,nF,nLoadLoc,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element:LOAD VECTOR
!
!
!	Inputs
!		Qf(3)		= Load Ceffs at Bez. Pts at r = 1 Side
!		xLenY		= Length of side at r = 1
!		 	
!	Outputs 
!		F(12)	1= Desired Load Vector
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays: Specifically for Shear Load At r = 1 Surface
!
	Real(kind=8)	Qf   
	Dimension		Qf(nQ)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F    ,fmult
	Dimension		F(nF)
	
!
	F			= 0.D0	! All
	fmult		= 1.D0
	F(nLoadLoc)	= fmult*Qf(1)    
!   
!	Done
!
	write(iOut,1000)
	write(iOut,1010) (F(i),i = 1,nF)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: Quad_CC_LVY"/)
 1010 Format(/2x,"Load Vector"/
     &        3(2x,5F10.7/) )
	end 
