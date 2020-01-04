	Subroutine RatGetGeometry_1(Qx,Qy,Wt,nQc,Radius,Plot,nDim,iStart,
     &									nPts,iOut)
!	Describe 45 deg Circle by Rational Quadratic 	
!
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qx     ,Qy     ,Wt     ,Plot      ,Pt   ,Br      
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc),Plot(nDim),Pt(2),Br(3)
	real(kind = 8)	Radius
	real(kind = 8)	pi,Si8,tanSi8,cosSi8
	integer			nOrder
!	-----------------------------
	pi		= DATAN(1.D0)*4.0D0
	rrut2	= 1.D0/dsqrt(2.0D0)
!--------------------------------------------------- x & y: Conic:Circle
	iCheck = 0
!	------------------------------------
	if(iCheck == 0) Then
		Si8		= pi/8.D0
		tanSi8	= DTAN(Si8)
		cosSi8	= DCOS(Si8)
!
		Qx(1)		= 0.D0
		Qy(1)		= 0.D0
		Qx(2)		= 0.D0
		Qy(2)		= tanSi8*RADIUS
		Qx(3)		= (1.D0 - rrut2)*RADIUS
		Qy(3)		= rrut2*RADIUS
!--------------------------------------------------- Weights:Circle
		Wt(1)		= 1.D0
		Wt(2)		= cosSi8
		Wt(3)		= 1.D0
	else
!
		Qx(1)		= 0.D0
		Qy(1)		= 0.D0
		Qx(2)		= 0.D0
		Qy(2)		= RADIUS
		Qx(3)		= RADIUS
		Qy(3)		= RADIUS
!--------------------------------------------------- Weights:Circle
		Si8		= pi/4.D0
		cosSi8	= DCOS(Si8)
!
		Wt(1)		= 1.D0
		Wt(2)		= cosSi8
		Wt(3)		= 1.D0
!		--------------------------------------------------- Check
		delri = 1.D0/(nPts-1)
!		------------------------ Loop
		do 50 i = 1,nPts
		ri = delri*(i-1)
!
		call Bernstein(Br,3,ri,iOut)
		call RatBezierPt(Br,Qx,Qy,Wt,3,ri,Pt,iOut)
!
		Plot(i+iStart) = Pt(2)
   50		continue
	endif
!--------------------------------------------------- Check End
	return
	end
