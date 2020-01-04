	Subroutine QQ_StrainDispMat(Qc,nQc,R,Rad,B,nB,Det,
     &								Nel,NelType,Iout)
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
!	Inverse & determinant of Jacobian
!
!	call QQ_Jacobian_Cart(Qc,nQc,nQc,R,H1D,AJI,Det,Rad,
!     &    	delCx,delCy,Nel,Iout,0)
	call QQ_TMB_Cart(Qc,nQc,nQc,R,H1D,Det,Rad,Axes,
     &							dxbardr,Nel,Iout,iPrt)
!
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
!	write(Iout,1010) R,det,(i,(B(i,j),j = 1,nB),i=1,6)
!-----------------------------------------------
	return
!-----------------------------------------------
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(6,15)"/
     &        "R = ",f20.16,2X,"det = ",f20.16/(I5/,6(5(f10.7,1X)/)))
	end
