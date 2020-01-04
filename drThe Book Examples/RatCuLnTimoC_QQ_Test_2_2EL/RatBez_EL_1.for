	Subroutine RatBZ_CoordsWts_EL1(Qc,nR,nC,Radius,Plot,nDim,
     &								nPts,nStart,Nel,iOut)
!	First Describe 45 deg Circle by Cubic 	
!	Degree Elevate to Quartic
!
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qc       
	Dimension		Qc(nR,nC)
	real(kind = 8)	Radius
	integer			nR,nC
	real(kind = 8)	Qx    ,Qy    ,Wt    ,Plot         
	Dimension		Qx(nC),Qy(nC),Wt(nC),Plot(nDim)
!	-----------------------------
	call RatGetGeometry_1(Qx,Qy,Wt,nC,Radius,Plot,nDim,iStart,
     &									nPts,iOut)
!	---------------------
	do 10 i = 1,nC
	Qc(1,i) = Qx(i)  	
	Qc(2,i) = Qy(i)  	
	Qc(3,i) = Wt(i)
   10 continue
!	--------    	  	
	return
	end
