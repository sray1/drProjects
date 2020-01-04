	DOUBLE PRECISION Function RatCurvature_0(nDeg,Qx,Qy,Wt,nQc,Nel,
     &										Iout)
!
!	signed curvature of a RatBez at parameter t = 0
!	Farin: p180: Eqn.(11.10)
!	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qx     ,Qy     ,Wt        
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc)
	Real(kind=8)	Q0   ,Q1   ,Q2       
	Dimension		Q0(2),Q1(2),Q2(2)
	integer			Nel,Iout
!
	Integer			i,j,nDeg
!------------------------------------ 
	Q0(1)	= Qx(1)
	Q1(1)	= Qx(2)
	Q2(1)	= Qx(3)
	Q0(2)	= Qy(1)
	Q1(2)	= Qy(2)
	Q2(2)	= Qy(3)
!	--------------
	w0		= Wt(1)	
	w1		= Wt(2)	
	w2		= Wt(3)	
!	--------------
	dist = dsqrt( 
     &				(Q1(1)-Q0(1))*(Q1(1)-Q0(1)) +
     &				(Q1(2)-Q0(2))*(Q1(2)-Q0(2)) 
     &			)
!
	RatCurvature_0 = 2.D0*(nDeg-1)*w0*w2*Area(Q0,Q1,Q2,Nel,Iout)/
     &					(ndeg*w1*w1*dist*dist*dist)
!	--------
	return
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
