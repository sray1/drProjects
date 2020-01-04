	Subroutine RatSubdivide(nDeg,Qc,Wt,nQc,ri,QL,QR,WL,WR,Nel,Iout)
!
!	subdivides ratbez curve at parameter t
!	
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc     ,Wt     ,QL     ,QR     ,WL     ,WR        
	Dimension		Qc(nQc),Wt(nQc),QL(nQc),QR(nQc),WL(nQc),WR(nQc)
	integer			Nel,Iout
!
	Integer			i,j,nDeg
!
	Real(kind=8)	w1,w2,t1
!	------------------------------- Parameter
	t	= ri
!------------------------------------ right subpolygon from rat de Casteljau
	t1	= 1.D0 - t													
!	--------------
	do 10 i=0,nDeg
	ip1 = i+1			! Fortran Location
   10	WR(ip1) = Wt(ip1)
	do 20 i=0,nDeg
	ip1 = i+1			! Fortran Location
   20	QR(ip1) = Qc(ip1)
!
	do 50 j=1,nDeg
	do 50 i=0,nDeg - j
	ip1 = i+1			! Fortran Location
	w1 = WR(ip1)
	w2 = WR(ip1+1)
!
	WR(ip1) =  t1*WR(ip1)    + t*WR(ip1+1)
	QR(ip1) = (t1*w1*QR(ip1) + t*w2*QR(ip1+1))/WR(ip1)
   50	continue
!	------------------- Standardizw Weights (Reparametrize)
	iCheck = 0
!	----------
	if(iCheck == 1) Then
		c = DSQRT(WR(1)/WR(3))
!		--
		w0		= WR(1)
		WR(1)	= 1.D0
		WR(2)	= c*WR(2)/w0
		WR(3)	= c*c*WR(3)/w0
	endif
!------------------------------------ left subpolygon from rat de Casteljau
!	reverse ordering gives left half
!	--------------------------------	
	t	= 1.D0 - t													
	t1	= 1.D0 - t													
!	--------------
	do 60 i=0,nDeg
	ip1 = nDeg-i+1			! Fortran Location
   60	WL(ip1) = Wt(i+1)
	do 70 i=0,nDeg
	ip1 = nDeg-i+1			! Fortran Location
   70	QL(ip1) = Qc(i+1)
!
	do 80 j=1,nDeg
	do 80 i=0,nDeg - j
	ip1 = i+1			! Fortran Location
	w1 = WL(ip1)
	w2 = WL(ip1+1)
!
	WL(ip1) =  t1*WL(ip1)    + t*WL(ip1+1)
	QL(ip1) = (t1*w1*QL(ip1) + t*w2*QL(ip1+1))/WL(ip1)
   80	continue
!	------------------- Standardizw Weights (Reparametrize)
	iCheck = 0
!	----------
	if(iCheck == 1) Then
		c = DSQRT(WL(1)/WL(3))
!		--
		w0		= WL(1)
		WL(1)	= 1.D0
		WL(2)	= c*WL(2)/w0
		WL(3)	= c*c*WL(3)/w0
	endif
!	--------
	return
 1000	format(A,I5,A)
 1010 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" TP Av.Knot")
 1020 format(2X,"R = ",f10.5,2X,"S = ",f10.5,2X,"det = ",f10.5,
     &				" Normal")
!
	end
