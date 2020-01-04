	Subroutine RatGetGeometry_1(Qx,Qy,Wt,nQc,Plot,nDim,iStart,
     &									nPts,iOut)
!	Describe Left subdivided Parabola by Rational Quadratic 
!	Michalos Problem p-300	
!
	Implicit Real(kind=8) (a-h,o-z)
!
	real(kind = 8)	Qx     ,Qy     ,Wt     ,Plot      ,Pt   ,Br      
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc),Plot(nDim),Pt(2),Br(3)
	integer			nOrder
!--------------------------------------------------- x & y: Conic:Parabola
	Qx(1)		=  0.0D0
	Qy(1)		=  0.0D0
	Qx(2)		= 35.0D0
	Qy(2)		= 28.0D0
	Qx(3)		= 70.0D0
	Qy(3)		= 16.8D0
!--------------------------------------------------- Weights:Parabola
	Wt(1)		= 1.D0
	Wt(2)		= 1.D0
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
   50	continue
!--------------------------------------------------- Check End
	return
	end
