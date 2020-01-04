	DOUBLE PRECISION Function RatJacobian_0(nDeg,Qx,Qy,Wt,nQc,
     &										Tangent,t,Nel,Iout)
!
!	signed curvature of a RatBez at parameter t = 0
!	Farin: p180: Eqn.(11.10)
!	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qx     ,Qy     ,Wt     ,tangent        
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc),tangent(2)
	Real(kind=8)	Q0   ,Q1          
	Dimension		Q0(2),Q1(2)
	integer			Nel,Iout
!
	Integer			nDeg
!------------------------------------ 
	Q0(1)	= Qx(1)
	Q0(2)	= Qy(1)
	Q1(1)	= Qx(2)
	Q1(2)	= Qy(2)
!		--------------
	w0		= Wt(1)	
	w1		= Wt(2)	
!	--------------
	delX	= nDeg*w1*(Q1(1)-Q0(1))/w0
	delY	= nDeg*w1*(Q1(2)-Q0(2))/w0
!	---------------------------------- Left subdivided Polygon
	if(t.GE.0.5) Then
		delX = -delX
		delY = -delY
	endif
!
	tangent(1) = delX
	tangent(2) = delY
!
	RatJacobian_0 = dsqrt( delX*delX + delY*delY) 
!	--------
	return
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
