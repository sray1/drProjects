	Subroutine Set_ExtLoad_Y(Qf,nQ,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qf
	Dimension		Qf(nQ)
!	
	Qf		= 0.		! All Zero
	Qf(1)	= 1.0		! M-Load
!
	return
	end
	Subroutine Quad_QQ_LVY(Qc,nQc,Qf,nQ,F,nF,nLoadLoc,iOut)
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
	Real(kind=8)	Qc       ,Det,Axes     ,dxbardr
	Dimension		Qc(3,nQc)    ,Axes(3,3)
	Real(kind=8)	Qx,     Qy     ,Wt
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc)
	Real(kind=8)	Qf   
	Dimension		Qf(nQ)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	F    ,fmult
	Dimension		F(nF)
	
!	Hard Coded ri: Load Location on the parabola
	ri	= 0.7D0
	Nel = 2
	call RatControlsWts(Qc,Qx,Qy,Wt,nQc,Nel,Iout)
	call Rat_TMB_Cart(Qx,Qy,Wt,nQc,3,ri,Det,Axes,
     &						dxbardr,Nel,Iout,iPrt)	
!
	Fw			= Qf(1)*Axes(2,2)
	Fu			= -Qf(1)*Axes(2,1)
	F			= 0.D0	! All
	fmult		= 1.D0
!	F(5)		= fmult*Fw	! Fw    
!	F(10)		= fmult*Fu	! Fu    
	F(5)		= fmult	! Fw    
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
