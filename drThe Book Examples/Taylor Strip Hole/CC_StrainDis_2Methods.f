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
	Real(kind=8)	Gr       ,Gs           
	Dimension		Gr(nQc1),Gs(nQc2)    
	Real(kind=8)	B1Dr       ,B1Ds       
	Dimension		B1Dr(nDegR),B1Ds(nDegS)
	Real(kind=8)	G1Dr       ,G1Ds       
	Dimension		G1Dr(nQc1),G1Ds(nQc2)
	Real(kind=8)	Hrs	      ,A1      ,A2
	Dimension		Hrs(2,nQd),A1(nDim),A2(nDim)
	Real(kind=8)	H1D       ,H1G       	 	 
	Dimension		H1D(2,nQd),H1G(nDim,nQc1,nQc2)
	Real(kind=8)	AJ,     AJI   
	Dimension		AJ(2,2),AJI(2,2)
!------------------------------------------------------------ RadOfCur_R
	RadOfCur_R = Rad_In + S * Depth
!******************
	iMethod = 1
!	**********************************************************************************
	if(iMethod == 1) then
!		------------------------------------------------------------ Geometry: Jacobian & Determinant
	
		call Jacobian_N_Determinant(Qc,nDim,nQc1,nQc2,R,S,
     &                 	              A1,A2,Det)

		if(det.gt.0.0000001) go to 99
		write(Iout,1000) "Zero or Negative determinant for the Element(",
     &		Nel,")"
		stop 'det 0'

   99		continue
!		-------------------------------------------------------------- Jacobian	
		AJ(1,1) = A1(1)
		AJ(1,2) = A1(2)
		AJ(2,1) = A2(1)
		AJ(2,2) = A2(2)
!	**********************************************************************************
	elseif(iMethod == 2) then
		!------------------------------------------------------------ Geometry Distribution	
		call Bernstein(Gr,nQc1,R,iOut)
		call Bernstein(Gs,nQc2,S,iOut)
!		------------------------------------------------------------ Ist Derivatives
		call Bernstein_IstDerivative(G1Dr,nQc1,R,iOut)
		call Bernstein_IstDerivative(G1Ds,nQc2,S,iOut)
!		Derivative of H wrt r and s
!		H1G(1,*)	= delH/delr
!		H1G(2,*)	= delH/dels
!
		do 10 i = 1,nQc1 
		do 10 j = 1,nQc2
		H1G(1,i,j) = G1Dr(i)*Gs(j)	! wrt 1
   10		continue
		do 11 i = 1,nQc1 
		do 11 j = 1,nQc2
!
		H1G(2,i,j) = Gr(i)*G1Ds(j)	! wrt 2
		iPrt = 0
		if(iPrt == 1) then
				write(iOut,1040) i,j,Gr(i),G1Ds(j),H1G(2,i,j)
		endif
   11		continue

		!-------------------------------------------------------------- Jacobian	
		AJ = 0.0D0	!ALL
!		------------------------------------------------------ Circumferential
!		Jacobian in Circumferential direction
!
		delCx = 0.0D0
		delCy = 0.0D0
		do 15 i = 1,nQc1
		do 14 j = 1,nQc2
		delCx = delCx + H1G(1,i,j)*QC(1,i,j)
		delCy = delCy + H1G(1,i,j)*QC(2,i,j)
   14		continue 
   15		continue
!
!		AJ(1,1) = dsqrt((delCx*delCx)+(delCy*delCy))
		AJ(1,1) = delCx
		AJ(1,2) = delCy
!		------------------------------------------------------ Radial
!		Jacobian in Radial direction
!
		delCx = 0.0D0
		delCy = 0.0D0
		do 19 i = 1,nQc1
		do 18 j = 1,nQc2
		delCx = delCx + H1G(2,i,j)*QC(1,i,j)
		delCy = delCy + H1G(2,i,j)*QC(2,i,j)
   18		continue
   19		continue
!
!		AJ(2,2) = dsqrt((delCx*delCx)+(delCy*delCy))
		AJ(2,1) = delCx
		AJ(2,2) = delCy
!
		det = AJ(1,1)*AJ(2,2) - AJ(1,2)*AJ(2,1)
!
		iPrt = 0
		if(iPrt == 1) then
			write(iOut,1029) 
			do i = 1,nDim
				do j = 1,nQc1
					write(iOut,1030) i,j,(H1G(i,j,k),k=1,nQc2)
				end do !j
			end do !i
		endif
!		--------------------------------------------
!		Determinant of Jacobian
!
		det = AJ(1,1)*AJ(2,2) - AJ(1,2)*AJ(2,1)
		if(det.gt.0.0000001) go to 40
		write(Iout,1000) "Zero or Negative determinant for the Element(",
     &	Nel,")"
		stop 'det 0'
!
!		Inverse of Jacobian
!
   40		continue
	endif
!	-------------------------------------------------------------- Inverse of Jacobian
	dum = 1./Det
	AJI(1,1) =  AJ(2,2)*dum
	AJI(1,2) = -AJ(1,2)*dum
	AJI(2,2) =  AJ(1,1)*dum
	AJI(2,1) = -AJ(2,1)*dum	
!!
	write(iOut,1020) iMethod,R,S,AJ(1,1),AJ(2,1),AJ(1,2),AJ(2,2),det,
     &	AJi(1,1),AJi(2,1),AJi(1,2),AJi(2,2)
!------------------------------------------------------------ Displacement Distribution	
	call Bernstein(Br,nDegR,R,iOut)
	call Bernstein(Bs,nDegS,S,iOut)
!---------------------------------------
!	uRad(ial) & uCir(cumference)
!	are same for any r,s
!
	do 42 i = 1,nDegR 
	do 42 j = 1,nDegS
	k = j+(i-1)*nDegS
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
	k = j+(i-1)*nDegS
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
!
	iPrt = 1
	if(iPrt == 1) then
		write(iOut,1050) (Br(i), i = 1,nDegR)
		write(iOut,1051) (Bs(i), i = 1,nDegS)
		write(iOut,1052) (B1Dr(i), i = 1,nDegR)
		write(iOut,1053) (B1Ds(i), i = 1,nDegS)
		write(iOut,1054) (ih,(Hrs(ih,i), i = 1,nQd),ih = 1,2)
		write(iOut,1055) (ih,(H1D(ih,i), i = 1,nQd),ih = 1,2)
		write(iOut,'(/A15,f10.7)') "RadOfCur_R = ",RadOfCur_R
		write(iOut,1060) (i,(B(i,j),j = 1,32),i=1,3)
	endif

!	Pause
	return
!
 1000	format(A,I5,A)
 1020 format( "iMet/R/S/J11/J21/J12/J22/Det/iJ11/iJ21/J12/iJ22..."
     &    ,i2,2(2x,f20.16,2X)/9(2x,f11.7)  )
 1029 format(2x,"H1G..."/)
 1030 format(2x,2i5,(2f20.16))
 1040 format(2x,"i,j,Gr(i),G1Ds(j),H1G(2,i,j)..",2i5,3f20.16)
 1050 format(/2x,"Br(nDegR)...",4(2x,F10.7))
 1051 format(/2x,"Bs(nDegS)...",4(2x,F10.7))
 1052 format(/2x,"B1Dr(nDegR)...",4(2x,F10.7))
 1053 format(/2x,"B1Ds(nDegR)...",4(2x,F10.7))
 1054 format("Hrs Matrix Hrs(2,nQd)"/(I5/,2(8(f10.7,1X)/)))
 1055 format("H1D Matrix H1D(2,nQd)"/(I5/,2(8(f10.7,1X)/)))
 1060 format("Strain-Displacement Matrix B(3,32)"/
     &                               (I5/,4(8(f10.7,1X)/)))
	end
