	Subroutine BZ_Coords(Qc,nDim,nQc1,nQc2,R_In,R_Out,Thk,iOut)
	
	real(kind = 8)	Qc       
	Dimension		Qc(nDim,nQc1,nQc2)
	real(kind = 8)	R_In,R_Out,Thk
	integer			nDim,nQc1,nQc2
!
	Qc			= 0.			! zero all

!	-----------------------------
	xK			= 4.0D0*(dsqrt(2.0D0)-1.0D0)/3.0D0		! for 90 deg circle
!--------------------------------------------------- x:Inner Radius
	Qc(1,1,1)		= 0.0D0
	Qc(1,2,1)		= R_In*xK
	Qc(1,3,1)		= R_In
	Qc(1,4,1)		= R_In
!--------------------------------------------------- y
	Qc(2,1,1)		= 0.0D0
	Qc(2,2,1)		= 0.0D0
	Qc(2,3,1)		= -R_In*(1.0D0 - xK)
	Qc(2,4,1)		= -R_In
!--------------------------------------------------- x:Outer Radius
	Qc(1,1,2)		= 0.0D0
	Qc(1,2,2)		= R_Out*xK
	Qc(1,3,2)		= R_Out
	Qc(1,4,2)		= R_Out
!--------------------------------------------------- y
	Qc(2,1,2)		= Thk
	Qc(2,2,2)		= Thk
	Qc(2,3,2)		= -R_In + xK*R_Out
	Qc(2,4,2)		= -R_In
!--------------------------------------------------- Print
	return
	end
	
	Subroutine Set_ExtLoad(Qf,nDim)
	
	real(kind = 8)	Qf
	Dimension		Qf(nDim)
!	
	Qf		= 0.		! All Zero
	Qf(2)	= 1.0
	Qf(3)	= 1.0
!
	return
	end
!	  			
