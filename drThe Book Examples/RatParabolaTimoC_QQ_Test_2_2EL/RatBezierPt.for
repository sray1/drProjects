	Subroutine RatBezierPt(Br,Qx,Qy,Wt,nQc,r,Pt,iOut)
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qx,     Qy     ,Wt
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc)
	real(kind = 8)	Br     ,Pt
	Dimension		Br(nQc),Pt(2)
	real(kind = 8)	r
	integer			nQc,iOut
	real(kind = 8)	Deno,sumX,sumY
!-------------------------------------------------- Bernstein
	Deno = 0.D0	
	do 5 i = 1,nQc
	Deno	= Deno + Wt(i)*Br(i)
    5 continue
	sumX = 0.D0	
	sumY = 0.D0	
	do 10 i = 1,nQc
	sumX	= sumX + Wt(i)*Br(i)*Qx(i)
	sumY	= sumY + Wt(i)*Br(i)*Qy(i)
   10 continue
!
	Pt(1)	= sumX/Deno   	
	Pt(2)	= sumY/Deno   	
!------------------------------------  	
	return
	end
