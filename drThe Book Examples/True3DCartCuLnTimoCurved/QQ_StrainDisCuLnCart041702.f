	Subroutine QQ_StrainDispMat(Qc,nQc,R,Rad,B,nB,Det,Axes,
     &					Curvature,Torsion,Nel,NelType,Iout)
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
!--------------	
	nDof = 6	  
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,r,iOut)
!------------------------------------------------------
!	Inverse & determinant of Jacobian
!
!	call QQ_Jacobian_Cart(Qc,nQc,nQc,R,H1D,AJI,Det,Rad,
!     &    	delCx,delCy,Nel,Iout,0)
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
!=======================================================================
!============================ Assumed Quintic -> from 18+ strarts thetas	
	A = Axes
!=======================================================================
	do 70 j = 1,nQc	! For 3D Curve Beam: Axial & Shear Deformations 
!
	do 50 k = 1,3
!		
	B(1,j+(k-1)*nQc)	=  -Curvature*A(2,k)*Br(j)+A(1,k)*H1D(j)*AJI			! Eps_t: Axial
!
	B(2,j+(k-1)*nQc)	=  A(1,k)*Curvature*Br(j)-A(3,k)*Torsion*Br(j)		! Gam_tm: Shear	
     &						+ A(2,k)*H1D(j)*AJI				               	
	B(2,18+j+(k-1)*nQc)	=  -A(3,k)*Br(j)				               	
!
	B(3,j+(k-1)*nQc)	=  A(2,k)*Torsion*Br(j)+A(3,k)*H1D(j)*AJI			! Gam_tb: Shear	
	B(3,18+j+(k-1)*nQc)	=  A(2,k)*Br(j)		
!
	B(4,18+j+(k-1)*nQc)	=  -Curvature*A(2,k)*Br(j)+A(1,k)*H1D(j)*AJI		! Tors_X: Torsion
!
	B(5,18+j+(k-1)*nQc)	=  A(1,k)*Curvature*Br(j)-A(3,k)*Torsion*Br(j)		! Ki_XZ: Flexure
     &						+ A(2,k)*H1D(j)*AJI				               	
!
	B(6,18+j+(k-1)*nQc)	=  A(2,k)*Torsion*Br(j)+A(3,k)*H1D(j)*AJI		! Ki_XY: Flexure
!
   50 continue
!
   70 continue			
!--------------------------
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
