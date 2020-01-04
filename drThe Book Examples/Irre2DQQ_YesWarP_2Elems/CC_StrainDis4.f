	Subroutine CC_StrainDispMat(Qc,nQc,R,S,B,nB,xLen1,xLen2,yLen,
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
	Real(kind=8)	xLen1,xLen2,yLen,Thk,Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum
	Real(kind=8)	Br       ,Bs           ,Gr      ,Gs   
	Dimension		Br(nDegR),Bs(nDegS)    ,Gr(2)   ,Gs(nDegS)
	Real(kind=8)	B1Dr       ,B1Ds       ,B1Gr   ,B1Gs
	Dimension		B1Dr(nDegR),B1Ds(nDegS),B1Gr(2),B1Gs(nDegS)
	Real(kind=8)	Hrs	 
	Dimension		Hrs(2,nQc)
	Real(kind=8)	H1D       ,H1G     ,QG		 	 
	Dimension		H1D(2,nQc),H1G(2,4),QG(2,4) !for Geometry r-dir is linear
!	Dimension		H1D(2,nQc),H1G(2,4),QG(2,4) !for Geometry r-dir is linear
	Real(kind=8)	AJ,     AJI   
	Dimension		AJ(2,2),AJI(2,2)
	Real(kind=8)	DTw     ,Twist	 
	Dimension		DTw(nQc),Twist(2)
!-------------------------------------------------- Displacement/Quartic
	Br(1) = (1.D0-r)*(1.D0-r)*(1.D0-r)*(1.D0-r)
	Br(2) = 4.D0*(1.D0-r)*(1.D0-r)*(1.D0-r)*r
	Br(3) = 6.D0*(1.D0-r)*(1.D0-r)*r*r
	Br(4) = 4.D0*(1.-r)*r*r*r
	Br(5) = r*r*r*r
!	 
	Bs(1) = (1.D0-s)*(1.D0-s)*(1.D0-s)*(1.D0-s)
	Bs(2) = 4.D0*(1.D0-s)*(1.D0-s)*(1.D0-s)*s
	Bs(3) = 6.D0*(1.D0-s)*(1.D0-s)*s*s
	Bs(4) = 4.D0*(1.D0-s)*s*s*s
	Bs(5) = s*s*s*s
!
!-------------------------------------------------- Displacement	
!	Define Derivative Bernstein: delH wrt r & s
!
	B1Dr(1) = -4.D0*(1.D0-r)*(1.D0-r)*(1.D0-r)
	B1Dr(2) = 4.D0*(-3.D0*(1.D0-r)*(1.D0-r)*r 
     &			+(1.D0-r)*(1.D0-r)*(1.D0-r))
	B1Dr(3) = 6.D0*(-2.D0*(1.0D0-r)*r*r
     &			+2.0D0*(1.0D0-r)*(1.0D0-r)*r)
	B1Dr(4) = 4.D0*(-r*r*r+3.0D0*(1.0D0-r)*r*r) 
	B1Dr(5) = 4.D0*r*r*r 
!	 
	B1Ds(1) = -4.D0*(1.D0-s)*(1.D0-s)*(1.D0-s)
	B1Ds(2) = 4.D0*(-3.D0*(1.D0-s)*(1.D0-s)*s 
     &			+(1.D0-s)*(1.D0-s)*(1.D0-s))
	B1Ds(3) = 6.0D0*(-2.D0*(1.0D0-s)*s*s
     &			+2.0D0*(1.0D0-s)*(1.0D0-s)*s)
	B1Ds(4) = 4.D0*(-s*s*s+3.0D0*(1.0D0-s)*s*s) 
	B1Ds(5) = 4.D0*s*s*s 
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
!-------------------------------------------------- Geometry	
!	Define Bernstein Interpolations:Geometry
!
	Gr(1) = (1.-r)
	Gr(2) = r
!	 
	Gs(1) = (1.-s)
	Gs(2) = s
!
!	Define Derivative Bernstein: delH wrt r & s
!
	B1Gr(1) = -1.D0
	B1Gr(2) = 1.0D0
!	 
	B1Gs(1) = -1.D0
	B1Gs(2) = 1.0D0
!	 
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!		H1D(2,*)	= delH/dels
!
!	do 20 i = 1,nDegS
!	H1G(1,i) = B1Gs(i)
!	H1G(2,i) = B1Gs(i)
!   20 continue
!-------------------------------------------------- Geometry Coords	
!	QG(1,1) = 0.5D0*(Qc(1,1) + Qc(1,13))
!	QG(1,2) = 0.5D0*(Qc(1,2) + Qc(1,14))
!	QG(1,3) = 0.5D0*(Qc(1,3) + Qc(1,15))
!	QG(1,4) = 0.5D0*(Qc(1,4) + Qc(1,16))
!
!	QG(2,1) = 0.5D0*(Qc(2,1) + Qc(2,13))
!	QG(2,2) = 0.5D0*(Qc(2,2) + Qc(2,14))
!	QG(2,3) = 0.5D0*(Qc(2,3) + Qc(2,15))
!	QG(2,4) = 0.5D0*(Qc(2,4) + Qc(2,16))
!------------------------------------------- for Error Analysis
!	Twist
!		Twist	for  delX/delrdels
!		Twist(2,*)	for  delY/delrdels
!
	do 15 i = 1,nDegR 
	do 15 j = 1,nDegS
	k = i+(j-1)*nDegR
	DTw(k) = B1Dr(i)*B1Ds(j)
   15 continue
!
	do 17 i = 1,2
	dum = 0.0
	do 16 k = 1,nQc
	dum = dum + DTw(k)*Qc(i,k)
	Twist(i) = dum
   16 continue
   17 continue
!--------------------------------------------
	AJ = 0.0D0	!ALL
!------------------------------------------------------ IsoParametric
!	Jacobian
!
	do 30 j = 1,2
	do 30 i = 1,2
	dum = 0.0
	do 20 k = 1,nQc
	dum = dum + H1D(i,k)*Qc(j,k)
	AJ(i,j) = dum
   20 continue
   30 continue
!------------------------------------------------------ SubParametric
!	Jacobian in R-dir
!
!	AJ(1,1) = (1.0D0-s)*xLen1+s*xLen2
!	AJ(1,2) = 0.0D0
!------------------------------------------------------
!	Jacobian in S-dir
!
!	AJ(2,1) = r*(xLen2-xLen1)
!	AJ(2,2) = yLen
!---------------------------------------------------------------------
!	Determinant of Jacobian
!
	det = AJ(1,1)*AJ(2,2) - AJ(1,2)*AJ(2,1)
!
	write(Iout,1020) R,S,det,Twist(1),Twist(2)
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
	B(1,j)		= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
	B(1,j+25)	= 0.0D0
!
	B(2,j)		= 0.0D0
	B(2,j+25)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)	! Quartic
!
	B(3,j)		= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
	B(3,j+25)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)
   50	continue
!
!	write(*,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,32)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,4(8(f10.7,1X)/)))
 1020 format(2X,"R = ",f7.4,2X,"S = ",f7.4,2X,"det = ",f7.3,
     &		2X,"X_Twist = ",f7.3,2X,"Y_Twist = ",f7.3)
	end
