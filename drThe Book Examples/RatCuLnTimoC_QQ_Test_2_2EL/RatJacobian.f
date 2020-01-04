	DOUBLE PRECISION Function RatJacobian(nDeg,Qx,Qy,Wt,nQc,t,
     &										tangent,Nel,Iout)
!
!	signed curvature of a RatBez at parameter t
!	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qx     ,Qy     ,Wt     ,tangent        
	Dimension		Qx(nQc),Qy(nQc),Wt(nQc),tangent(2)
	Real(kind=8)	QLx    ,QRx    ,WL    ,WR        
	Dimension		QLx(10),QRx(10),WL(10),WR(10)
	Real(kind=8)	QLy    ,QRy
	Dimension		QLy(10),QRy(10)
	integer			Nel,Iout
	Integer			i,j,nDeg
!------------------------------------ 
	if(t.LT.0.5) Then
		call RatSubdivide(nDeg,Qx,Wt,nQc,t,QLx,QRx,WL,WR,Nel,Iout)
		call RatSubdivide(nDeg,Qy,Wt,nQc,t,QLy,QRy,WL,WR,Nel,Iout)
		RatJacobian = RatJacobian_0(nDeg,QRx,QRy,WR,nQc,tangent,t,
     &													Nel,Iout)
	else
		call RatSubdivide(nDeg,Qx,Wt,nQc,t,QLx,QRx,WL,WR,Nel,Iout)
		call RatSubdivide(nDeg,Qy,Wt,nQc,t,QLy,QRy,WL,WR,Nel,Iout)
		RatJacobian = RatJacobian_0(nDeg,QLx,QLy,WL,nQc,tangent,t,
     &													Nel,Iout)
	endif
!	--------------
	return
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
