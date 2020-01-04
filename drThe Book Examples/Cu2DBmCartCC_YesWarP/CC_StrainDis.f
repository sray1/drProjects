	Subroutine CC_StrainDispMat(Qc,nQc,R,S,B,nB,Rad,Depth,
     &							nDegR,nDegS,Det,Nel,NelType,Iout)
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
	Dimension		Qc(2,nQc),B(3,nB)
	Real(kind=8)	Rad,Thk,Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
!
	Real(kind=8)	dum,RadOfCur_R,delCx,delCy,pi2
	Real(kind=8)	Br       ,Bs           ,Gr      ,Gs   
	Dimension		Br(nDegR),Bs(nDegS)    ,Gr(2)   ,Gs(nDegS)
	Real(kind=8)	B1Dr       ,B1Ds       ,B1Gr   ,B1Gs
	Dimension		B1Dr(nDegR),B1Ds(nDegS),B1Gr(2),B1Gs(nDegS)
	Real(kind=8)	Hrs	 
	Dimension		Hrs(2,nQc)
	Real(kind=8)	H1D       ,H1G     ,QG		 	 
	Dimension		H1D(2,nQc),H1G(2,4),QG(2,4) !for Geometry r-dir is linear
	Real(kind=8)	AJ,     AJI   
	Dimension		AJ(2,2),AJI(2,2)
!-------------------------------------------------- Geometry	
!	Define Bernstein Interpolations:Geometry
!
	Gr(1) = (1.-r)
	Gr(2) = r
!	 
	Gs(1) = (1.-s)*(1.-s)*(1.-s)
	Gs(2) = 3.*(1.-s)*(1.-s)*s
	Gs(3) = 3.*(1.-s)*s*s
	Gs(4) = s*s*s
!-------------------------------------------------- Displacement	
!	Define Bernstein Interpolations:Displacement
!
	Br(1) = (1.D0-r)*(1.D0-r)*(1.D0-r)
	Br(2) = 3.D0*(1.D0-r)*(1.D0-r)*r
	Br(3) = 3.D0*(1.D0-r)*r*r
	Br(4) = r*r*r
!	 
	Bs(1) = (1.D0-s)*(1.D0-s)*(1.D0-s)
	Bs(2) = 3.D0*(1.D0-s)*(1.D0-s)*s
	Bs(3) = 3.D0*(1.D0-s)*s*s
	Bs(4) = s*s*s
!--------------------------------------------------
!	uRad(ial) & uCir(cumference)
!	are same for any r,s
!
	do 5 i = 1,nDegR 
	do 5 j = 1,nDegS
	k = i+(j-1)*nDegS
	Hrs(1,k) = Br(i)*Bs(j)
	Hrs(2,k) = Hrs(1,k)
    5 continue
!
!	RadOfCur_R
!
	RadOfCur_R = Rad + (s - 0.5)*Depth
!-------------------------------------------------- Displacement	
!	Define Derivative Bernstein: delH wrt r & s
!
	dum		= 3.D0*r*r
	B1Dr(1) = -3.D0*(1.D0-r)*(1.D0-r)
	B1Dr(2) = 3.D0*(1.D0-4.D0*r+dum)
	B1Dr(3) = 3.D0*(2.D0*r-dum)
	B1Dr(4) = dum
!	 
	dum		= 3.D0*s*s
	B1Ds(1) = -3.D0*(1.D0-s)*(1.D0-s)
	B1Ds(2) = 3.D0*(1.D0-4.D0*s+dum)
	B1Ds(3) = 3.D0*(2.D0*s-dum)
	B1Ds(4) = dum
!---------------------------------------
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!		H1D(2,*)	= delH/dels
!
	do 10 i = 1,nDegR 
	do 10 j = 1,nDegS
	k = i+(j-1)*nDegS
	H1D(1,k) = B1Dr(i)*Bs(j)
	H1D(2,k) = Br(i)*B1Ds(j)
   10 continue
!-------------------------------------------------- Jacobian	
	AJ = 0.0D0	!ALL
!------------------------------------------------------
!	Jacobian in Circumferential direction
!
	delCx = 0.0
	do 25 i = 1,nQc
	delCx = delCx + H1D(1,i)*QC(1,i)
   25 continue
!
	delCy = 0.0
	do 30 i = 1,nQc
	delCy = delCy + H1D(1,i)*QC(2,i)
   30 continue
!
	AJ(1,1) = dsqrt((delCx*delCx)+(delCy*delCy))
!------------------------------------------------------
!------------------------------------------------------
!	Jacobian in Radial direction
!
	delCx = 0.0
	do 35 i = 1,nQc
	delCx = delCx + H1D(2,i)*QC(1,i)
   35 continue
!
	delCy = 0.0
	do 39 i = 1,nQc
	delCy = delCy + H1D(2,i)*QC(2,i)
   39 continue
!
	AJ(2,2) = dsqrt((delCx*delCx)+(delCy*delCy))
!--------------------------------------------
!	pi2 = DATAN(1.0D0)*2.0D0
!	AJ(1,1) = pi2*Rad
!	AJ(2,2) = Depth
!--------------------------------------------
!	Determinant of Jacobian
!
	det = AJ(1,1)*AJ(2,2) - AJ(1,2)*AJ(2,1)
	if(det.gt.0.0000001) go to 40
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &Nel,")"
	stop 'det 0'
!
!	Inverse of Jacobian
!
   40 continue
	dum = 1./det
	AJI(1,1) =  AJ(2,2)*dum
	AJI(1,2) = -AJ(1,2)*dum
	AJI(2,2) =  AJ(1,1)*dum
	AJI(2,1) = -AJ(2,1)*dum	
!
!	Strain displacement Matrix
	B = 0.0D0
!
	do 50 j = 1,nQc 
	B(1,j)		= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)	! Circumferential
	B(1,j+16)	= Hrs(2,j)/RadOfCur_R	! Cubic
!
	B(2,j)		= 0.
	B(2,j+16)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)	! Radial usubr
!
	B(3,j)		= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
     &			- Hrs(1,j)/RadOfCur_R
	B(3,j+16)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)	! Cubic
   50	continue
!
!	write(iOut,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,32)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,4(8(f10.7,1X)/)))
	end