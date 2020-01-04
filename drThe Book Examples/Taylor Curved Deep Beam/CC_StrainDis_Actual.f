	Subroutine CC_StrainDispMat(Qc,nDim,nQc1,nQc2,nQd,ri,rj,B,nB,
     &	R_InSide,Depth,nDegR,nDegS,Det,Nel,nElems,NelType,Iout)
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
	Real(kind=8)	Rad,Thk,Det,R,S
	integer			nDegR,nDegS,Nel,NelType,Iout
!
!		ndegR					= Bezier degree in r-dir = 3
!		ndegS					= Bezier degree in s-dir = 3
!
	Real(kind=8)	dum,RadOfCur_R,delCx,delCy,pi2
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
!------------------------------------------------------------ Geometry: Jacobian & Determinant	
!**********************************************************************************
!	Circular (Conic) geometry by Cubic approximation seems to produce
!	Unacceptable Error. We will stick with actual circular description
!********************************************************************************** Cubic
!	call Jacobian_N_Determinant(Qc,nDim,nQc1,nQc2,ri,rj,
!     &                 	              A1,A2,Det)
!
!	if(det.gt.0.0000001) go to 40
!	write(Iout,1000) "Zero or Negative determinant for the Element(",
!     &Nel,")"
!	stop 'det 0'
!
!   40 continue
!
!   	call VectorNorm(A1,AJ11,nDim,Iout)
!   	call VectorNorm(A2,AJ22,nDim,Iout)
!********************************************************************************** Actual
	RadOfCur_R = R_InSide + rj*Depth
!
	if(nElems == 1) then
		xMult = DATAN(1.D0)*2.D0	!piby2
	elseif(nElems == 2) then
		xMult = DATAN(1.D0)			!piby4
	endif
	AJ11 = xMult * RadOfCur_R  
	AJ22 = rj*DEPTH
	det	 = AJ11 * AJ22
!-------------------------------------------- Inverse of Jacobian
!
	AJI	= 0.D0
	dum = 1./Det
	AJI(1,1) =  AJ22*dum
	AJI(2,2) =  AJ11*dum
!**********************************************************************************
!------------------------------------------------------------ Displacement Distribution	
	call Bernstein(Br,nDegR,ri,iOut)
	call Bernstein(Bs,nDegS,rj,iOut)
!------------------------------------------------------------ Ist Derivatives
	call Bernstein_IstDerivative(B1Dr,nDegR,ri,iOut)
	call Bernstein_IstDerivative(B1Ds,nDegS,rj,iOut)
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
!--------------------------------------------------
!	uRad(ial) & uCir(cumference)
!	are same for any given ri,rj
!
	do 5 i = 1,nDegR 
	do 5 j = 1,nDegS
	k = i+(j-1)*nDegS
	Hrs(1,k) = Br(i)*Bs(j)
	Hrs(2,k) = Hrs(1,k)
    5 continue
!-------------------------------------------------- Displacement	
!
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
!	write(*,1010) ri,rj,(i,(B(i,j),j = 1,32),i=1,3)
!	Pause
	return
!
 1000	format(A,I5,A)
 1010 format("Strain-Displacement Matrix B(3,32)"/
     &        "ri = ",f20.16,2X,"rj = ",f20.16/(I5/,4(8(f10.7,1X)/)))
	end
