	Subroutine CC_StrainDispMat(Qc,nDim,nQc1,nQc2,nQc,nQd,R,S,B,nB,
     &	Rad_In,Depth,nDegR,nDegS,Det,Nel,nElems,NelType,Iout)
!	Inputs
!		nQd			= nDegR x nDegS
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
	Real(kind=8)	Qc                ,B
	Dimension		Qc(nDim,nQc1,nQc2),B(3,nB)
	Real(kind=8)	Rad_In,Thk,Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
!
	Real(kind=8)	dum,RadOfCur_R,delCT,delCR,pi2
	Real(kind=8)	Br       ,Bs           
	Dimension		Br(nDegR),Bs(nDegS)    
	Real(kind=8)	B1Dr       ,B1Ds       
	Dimension		B1Dr(nDegR),B1Ds(nDegS)
	Real(kind=8)	Hrs	      ,A1      ,A2
	Dimension		Hrs(2,nQd),A1(nDim),A2(nDim)
	Real(kind=8)	H1D              	 	 
	Dimension		H1D(2,nQd)
	Real(kind=8)	AJ,     AJI   
	Dimension		AJ(2,2),AJI(2,2)
!------------------------------------------------------------ RadOfCur_R
	RadOfCur_R	= Rad_In + S * Depth
!--------------------
	iMethod		= 2
!*********************************************************************** Method 1
!	------------------------------------------------------------ Geometry: Jacobian & Determinant
	call Jacobian_N_Determinant(Qc,nDim,nQc1,nQc2,R,S,
     &                 	              A1,A2,Det)

	if(det.gt.0.0000001) go to 99
	write(Iout,1000) "Zero or Negative determinant for the Element(",
     &		Nel,")"
	stop 'det 0'

   99		continue
	call DotProduct(A1,A2,dot,2,Iout)
!	-------------------------------------------------------------- Jacobian	
	AJ(1,1) = A1(1)
	AJ(2,1) = A1(2)
	AJ(1,2) = A2(1)
	AJ(2,2) = A2(2)
	endif

	write(iOut,1020) R,S,AJ(1,1),AJ(2,1),AJ(1,2),AJ(2,2),det
!		-------------------------------------------------------------- Inverse of Jacobian
	dum = 1./Det
	AJI(1,1) =  AJ(2,2)*dum
	AJI(1,2) = -AJ(1,2)*dum
	AJI(2,2) =  AJ(1,1)*dum
	AJI(2,1) = -AJ(2,1)*dum	
!**********************************************************************************
!------------------------------------------------------------ Displacement Distribution	
	call Bernstein(Br,nDegR,R,iOut)
	call Bernstein(Bs,nDegS,S,iOut)
!---------------------------------------
!	uRad(ial) & uCir(cumference)
!	are same for any r,s
!
	do 42 i = 1,nDegR 
	do 42 j = 1,nDegS
	k = i+(j-1)*nDegS
	Hrs(1,k) = Br(i)*Bs(j)
	Hrs(2,k) = Hrs(1,k)
   42 continue
!------------------------------------------------------------ Ist Derivatives
	call Bernstein_IstDerivative(B1Dr,nDegR,R,iOut)
	call Bernstein_IstDerivative(B1Ds,nDegS,S,iOut)
!	Derivative of H wrt r and s
!		H1D(1,*)	= delH/delr
!		H1D(2,*)	= delH/dels
!
	do 45 i = 1,nDegR 
	do 45 j = 1,nDegS
	k = i+(j-1)*nDegS
	H1D(1,k) = B1Dr(i)*Bs(j)
	H1D(2,k) = Br(i)*B1Ds(j)
   45 continue
!------------------------------------------------------------ Strain Distribution	
!	Strain displacement Matrix
	B = 0.0D0
!
	do 50 j = 1,nQd 
	B(1,j)		= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)	! Circumferential
	B(1,j+nQd)	= Hrs(2,j)/RadOfCur_R	! Cubic
!
	B(2,j)		= 0.
	B(2,j+nQd)	= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)	! Radial usubr
!
	B(3,j)		= AJI(2,1)*H1D(1,j) + AJI(2,2)*H1D(2,j)
     &			- Hrs(1,j)/RadOfCur_R
	B(3,j+nQd)	= AJI(1,1)*H1D(1,j) + AJI(1,2)*H1D(2,j)	! Cubic
   50	continue
!
!	write(iOut,1010) R,S,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,32)"/
     &        "R = ",f20.16,2X,"S = ",f20.16/(I5/,4(8(f10.7,1X)/)))
 1020 format(/"R =  ",f20.16," S =",f20.16/5X," J11=",f11.7,
     & " J21=",f16.10," J12=",f16.10," J22=",f16.10," Det=",f16.10)
	write(iOut,1020) R,S,det,AJ(1,1),AJ(2,2)
	end
