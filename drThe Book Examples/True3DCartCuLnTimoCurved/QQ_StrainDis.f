	Subroutine QQ_StrainDispMat(Qc,nQc,R,Rad,B,nB,Det,Axes,
     &					Cur,Tor,Nel,NelType,Iout)
!======================================================================
! TRUE 3D CANTILEVERED: CURVILINEAR FORMULATION/CARTESIAN INTERPOLATION
!								LOCKING???
!======================================================================
!	Inputs
!		Qc(1,nQc)	= Bezier X-Coordinates
!					=	(qc00x qc10x...qc33x)
!		Qc(2,nQc)	= Bezier Y-Coordinates
!					=	(qc00y qc10y...qc33y)
!		R			= r-directional root domain value	
!		S			= r-directional root domain value
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
! 	
!	Outputs 
!		B(3,nB)		= Strain Displacement Matrix
!						at a point (R,S)
!		Det			= determinant of The Jacobian
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc       ,B      ,Bu
	Dimension		Qc(3,nQc),B(6,nB),Bu(6,nB)
	Real(kind=8)	Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum,xMult,dxbardr,Curvature,Torsion,Radius
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D     ,Axes     ,A      	 
	Dimension		H1D(nQc),Axes(3,3),A(3,3)
	Real(kind=8)	AJ,     AJI 
	Real(kind=8)	AP     ,AxeP     ,XK     ,A6
	Dimension		AP(3,3),AxeP(3,3),XK(3,3),A6(6,6)
!--------------	
	nDof = 6	  
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!------------------------------------------------------
!	Inverse & determinant of Jacobian
!
!	call QQ_Jacobian_Cart(Qc,nQc,nQc,R,H1D,AJI,Det,Rad,
!     &    	delCx,delCy,Nel,Iout,0)
	call QQ_TMB_CuLn(Qc,nQc,nQc,R,H1D,Det,Cur,Tor,Axes,
     &						dxbardr,Nel,Iout,iPrt)
!
	Rad_O_Cur = 1.D0/Cur
!	=====================
	A6 = 0.D0
	do 10 i = 1,3
	do 10 j = 1,3
	A6(i,j)		= Axes(i,j)
	A6(i+3,j+3)	= Axes(i,j)
   10 continue
!	=====================
!--------------------------------------------
!	Strain displacement Matrix for Quartic
!	u:		j= 1, 2, 3, 4, 5		| eps_X
!	v:		j= 6, 7, 8, 9,10		| gam_XY
!	w:		j=11,12,13,14,15		| gam_XZ
!	thetaX:	j=16,17,18,19,20		| tor_X
!	thetaY:	j=21,22,23,24,25		| ki_XZ
!	thetaZ:	j=26,27,28,29,30		| ki_XY
!----------------------------------
!	Axis(1,..)	= T	---> x
!	Axis(2,..)	= B	---> y
!	Axis(3,..)	= M	---> z
!----------------------------------
!	XZ - In-Plane		(Depth)
!	Y  - Out-of-Plane	(Width)
!----------------------------------
	AJ1			= 1.D0/det
	AJI			= 1.D0/dxbardr
	nQ2			= nQc*2
	Bu			 = 0.0D0	!ALL
!================================================================= Axes primed  
!	do 5 j = 1,3
!	AxeP(1,j) =  -Cur*Axes(2,j)!*AJI
!	AxeP(2,j) = (Cur*Axes(1,j) - Tor*Axes(3,j))!*AJI
!	AxeP(3,j) = (Tor*Axes(2,j))!*AJI
!    5 continue
!=========================================================        S A M E  A S       
!-------------------- Curvature matrix
	XK = 0.D0 !ALL
	XK(1,2) = -Cur
	XK(2,1) =  Cur
	XK(2,3) = -Tor
	XK(3,2) =  Tor
!
	AxeP = MATMUL(XK,Axes)
!=============================================================================
!	AP = -MATMUL(Axes,MATMUL(TRANSPOSE(AxeP),Axes) )			S A M E  A S
	AP = AxeP
!=======================================================================
!============================ Assumed Quintic -> from 18+ strarts thetas
	jt = nQc*3	
	A = Axes
!=======================================================================
	do 70 j = 1,nQc	! For 3D Curve Beam: Axial & Shear Deformations 
!	================
	ha	= H1D(j)*AJI
	bj	= Br(j)
	tb	= Tor*bj	
	cb	= Cur*bj
!	================
	do 50 k = 1,3
!	================
	jkd		= j+(k-1)*nQc	
	jkt		= jt + jkd
	ap1b	= AP(1,k)*bj
	ap2b	= AP(2,k)*bj
	ap3b	= AP(3,k)*bj
	a2br	= A(2,k)*bj
	a3br	= A(3,k)*bj
	a1cb	= A(1,k)*cb
	a2cb	= A(2,k)*cb
	a2tb	= A(2,k)*tb
	a3tb	= A(3,k)*tb
	a1ha	= A(1,k)*ha
	a2ha	= A(2,k)*ha
	a3ha	= A(3,k)*ha
!
!	ap1b	= 0.D0
!	ap2b	= 0.D0
!	ap3b	= 0.D0
!	==================================
	Bu(1,jkd)	=  -a2cb    +a1ha		! Eps_t: Axial
     &				+ap1b			
	Bu(2,jkd)	=  a1cb-a3tb+a2ha		! Gam_tm: Shear	
     &				+ap2b			
	Bu(2,jkt)	=  -a3br				               	
	Bu(3,jkd)	=  a2tb     +a3ha		! Gam_tb: Shear	
     &				+ap3b			
	Bu(3,jkt)	=  a2br		
	Bu(4,jkt)	=  -a2cb    +a1ha		! Tors_X: Torsion
     &				+ap1b			
	Bu(5,jkt)	=  a1cb-a3tb+a2ha		! Ki_XZ: Flexure
     &				+ap2b			
	Bu(6,jkt)	=  a2tb     +a3ha		! Ki_XY: Flexure
     &				+ap3b			
!	==================================
   50 continue
   70 continue			
!	============================
!	B = MATMUL(TRANSPOSE(A6),Bu)
	B = Bu
!	============================
  100	continue
!
	iPrtStrDis = 0
	if(iPrtStrDis == 1) Then
		write(Iout,1010) R,det,(i,(B(i,j),j = 1,nB),i=1,6)
!		Pause
	endif
!
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(6,15)"/
     &        "R = ",f20.16,2X,"det = ",f20.16/(I5/,6(5(f10.7,1X)/)))
	end
