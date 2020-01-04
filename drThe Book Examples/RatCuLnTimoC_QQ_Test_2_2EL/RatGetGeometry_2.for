	Subroutine RatGetGeometry_2(Qx,Qy,Wt,nQc,Radius,Plot,nDim,iStart,
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
	Si8		= pi/8.D0
	tanSi8	= DTAN(Si8)
	cosSi8	= DCOS(Si8)
!--------------------------------------------------- x & y: Conic:Circle
	rrut2			= 1.D0/dsqrt(2.0D0)
!
	Qx(1)		= (1.D0 - rrut2)*RADIUS
	Qy(1)		= rrut2*RADIUS
	Qx(2)		= (1.D0-tanSi8)*RADIUS
	Qy(2)		= 1.D0*RADIUS
	Qx(3)		= 1.D0*RADIUS
	Qy(3)		= 1.D0*RADIUS
!--------------------------------------------------- Weights:Circle
	Wt(1)		= 1.D0
	Wt(2)		= cosSi8
	Wt(3)		= 1.D0
!--------------------------------------------------- Check
	delri = 1.D0/(nPts-1)
!	------------------------ Loop
	do 50 i = 1,nPts
	ri = delri*(i-1)
!
	call Bernstein(Br,3,ri,iOut)
	call RatBezierPt(Br,Qx,Qy,Wt,3,ri,Pt,iOut)
!
	Plot(i+nStart) = Pt(2)
   50 continue
!--------------------------------------------------- Check End
	return
	end
