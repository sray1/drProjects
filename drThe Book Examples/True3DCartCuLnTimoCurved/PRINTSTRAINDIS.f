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
	Real(kind=8)	Qc,     B
	Dimension		Qc(3,nQc),B(6,nB)
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
	Real(kind=8)	AP     ,AxeP     ,XK 
	Dimension		AP(3,3),AxeP(3,3),XK(3,3)
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
!--------------------------------------------
	AJ1			= 1.D0/det
	AJI			= 1.D0/dxbardr
	nQ2			= nQc*2
	B = 0.0D0	!ALL
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
	A = Axes
!=======================================================================
	do 70 j = 1,nQc	! For 3D Curve Beam: Axial & Shear Deformations 
!
	do 50 k = 1,3
!		
	B(1,j+(k-1)*nQc)	=  -Cur*A(2,k)*Br(j)+A(1,k)*H1D(j)*AJI		! Eps_t: Axial
     &						+	AP(1,k)*Br(j)
!
	B(2,j+(k-1)*nQc)	=  A(1,k)*Cur*Br(j)-A(3,k)*Tor*Br(j)		! Gam_tm: Shear	
     &						+	A(2,k)*H1D(j)*AJI				               	
     &						+	AP(2,k)*Br(j)
	B(2,18+j+(k-1)*nQc)	=  -A(3,k)*Br(j)				               	
!
	B(3,j+(k-1)*nQc)	=  A(2,k)*Tor*Br(j)+A(3,k)*H1D(j)*AJI		! Gam_tb: Shear	
     &						+	AP(3,k)*Br(j)
	B(3,18+j+(k-1)*nQc)	=  A(2,k)*Br(j)		
!
	B(4,18+j+(k-1)*nQc)	=  -Cur*A(2,k)*Br(j)+A(1,k)*H1D(j)*AJI		! Tors_X: Torsion
     &						+	AP(1,k)*Br(j)
!
	B(5,18+j+(k-1)*nQc)	=  A(1,k)*Cur*Br(j)-A(3,k)*Tor*Br(j)		! Ki_XZ: Flexure
     &						+ A(2,k)*H1D(j)*AJI				               	
     &						+	AP(2,k)*Br(j)
!
	B(6,18+j+(k-1)*nQc)	=  A(2,k)*Tor*Br(j)+A(3,k)*H1D(j)*AJI		! Ki_XY: Flexure
     &						+	AP(3,k)*Br(j)
!
   50 continue
!
   70 continue			
!--------------------------
  100	continue
!
	return
	end

	Subroutine QQ_StrainDispMat(Qc,nQc,R,Rad,B,nB,Det,
     &								Nel,NelType,Iout)
!====================================================================
! TRUE 3D CANTILEVERED: CARTESIAN FORMULATION/CARTESIAN INTERPOLATION
!								EXCELLENT
!====================================================================
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc,     B
	Dimension		Qc(3,nQc),B(6,nB)
	Real(kind=8)	Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum,xMult,dxbardr
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D     ,Axes      	 
	Dimension		H1D(nQc),Axes(3,3)
	Real(kind=8)	AJ,     AJI 
!--------------	
	nDof = 6	  
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!------------------------------------------------------
	call QQ_TMB_Cart(Qc,nQc,nQc,R,H1D,Det,Rad,Axes,
     &							dxbardr,Nel,Iout,iPrt)
!
!----------------------------------
	AJ1			= 1.D0/det
	AJI			= 1.D0/dxbardr
	nQ2			= nQc*2
	B = 0.0D0	!ALL
	
	do 70 j = 1,nQc	! For 3D Curve Beam: Axial & Shear Deformations 
!
	do 50 k = 1,3
!		
	B(1,j+(k-1)*nQc)	=  H1D(j)*Axes(1,k)*AJI		! Eps_X: Axial
!
	B(2,j+(k-1)*nQc)	=  H1D(j)*Axes(2,k)*AJI		! Gam_XY: Shear	
	B(2,15+j+(k-1)*nQc)	=  Br(j) *Axes(3,k)		
!
	B(3,j+(k-1)*nQc)	= -H1D(j)*Axes(3,k)*AJI		! Gam_XZ: Shear	
	B(3,15+j+(k-1)*nQc)	=  Br(j) *Axes(2,k)		
!
	B(4,15+j+(k-1)*nQc)	=  H1D(j)*Axes(1,k)*AJI		! Tors_X: Torsion
!
	B(5,15+j+(k-1)*nQc)	=  H1D(j)*Axes(2,k)*AJI		! Ki_XZ: Flexure
!
	B(6,15+j+(k-1)*nQc)	=  H1D(j)*Axes(3,k)*AJI		! Ki_XY: Flexure
!
   50 continue
!
   70 continue			
!
  100	continue
!-----------------------------------------------
	return
	end

	Subroutine QQ_StrainDispMat(Qc,nQc,R,Rad,B,nB,Det,Axes,
     &					Curvature,Torsion,Nel,NelType,Iout)
!========================================================================
! TRUE 3D CANTILEVERED: CURVILINEAR FORMULATION/CURVILINEAR INTERPOLATION
!								EXCELLENT
!========================================================================
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Qc,     B
	Dimension		Qc(3,nQc),B(6,nB)
	Real(kind=8)	Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum,xMult,dxbardr,Curvature,Torsion,Radius
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D     ,Axes      	 
	Dimension		H1D(nQc),Axes(3,3)
	Real(kind=8)	AJ,     AJI 
!--------------	
	nDof = 6	  
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!------------------------------------------------------
	call QQ_TMB_CuLn(Qc,nQc,nQc,R,H1D,Det,Curvature,Torsion,Axes,
     &						dxbardr,Nel,Iout,iPrt)
!
	Rad_O_Cur = 1.D0/Curvature
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
	B = 0.0D0	!ALL
	
	do 70 j = 1,nQc	! For 3D Curve Beam: Axial & Shear Deformations 
!
	B(1,j          )	=  H1D(j)*AJI			! Eps_t: Axial
	B(1,j+    2*nQc)	=  -Curvature*Br(j)		
!
	B(2,j+    1*nQc)	=  H1D(j)*AJI			! Gam_tb: Shear	
	B(2,j+    2*nQc)	=  Torsion*Br(j)		
	B(2,j+    5*nQc)	=  Br(j)		
!
	B(3,j          )	=  Curvature*Br(j)		! Gam_tm: Shear	
	B(3,j+    1*nQc)	= -Torsion*Br(j) 		
	B(3,j+    2*nQc)	=  H1D(j)*AJI				               	
	B(3,j+    4*nQc)	=  -Br(j) 		
!
	B(4,j+    3*nQc)	=  H1D(j)*AJI			! Tors_t: Torsion
	B(4,j+    5*nQc)	=  -Curvature*Br(j)				
!
	B(5,j+    4*nQc)	=  H1D(j)*AJI
	B(5,j+    5*nQc)	=  Torsion*Br(j)		! Ki_b: Flexure (in-plane)
!
	B(6,j+    3*nQc)	=  Curvature*Br(j)		! Ki_m: Flexure (out-of-plane)
	B(6,j+    4*nQc)	= -Torsion*Br(j)			
	B(6,j+    5*nQc)	=  H1D(j)*AJI				
   70 continue			
!--------------------------
  100	continue
	return
	end
