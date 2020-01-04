	Subroutine Form_B_and_Tmatrices(Axes6,Axes12,Axep,Axes,
     &								Cur,Tor,Ri,T,nT,B,nB,nD,
     &								AJI,nQc,Iout)
!	Inputs
!		R			= r-directional root domain value	
!		Nel			= Element Number
!		NelType		= Element Type:
!						0 = Plane Stress
!						1 = Plane Strain
!						2 = Axi-symmtric	(NOT DONE YET)
!		nT			= 6 (nDof)
!		nB			= 12 (nDof*2)
!		nD			= 6*nQc (nDof*nQc) = 6n
! 	
!	Outputs 
!		T(nT,nD)	= Dis & Primed Transformation Matrix
!							at a point R
!		B(nB,nD)	= Dis & Primed Transformation Matrix
!							at a point R
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	Axes     ,T       ,B
	Dimension		Axes(3,3),T(nT,nD),B(nB,nD)				! T(6,6n),B(12,6n)
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	AxeP     ,Axes6     ,Axes12
	Dimension		AxeP(3,3),Axes6(6,6),Axes12(12,12)
	Real(kind=8)	TC      ,TP      ,RT      ,RB
	Dimension		TC(3,nD),TP(3,nD),RT(3,nD),RB(3,nD)				! 
	Real(kind=8)	dum,xMult
	Real(kind=8)	Br     ,SK  
	Dimension		Br(nQc),SK(3,3)
	Real(kind=8)	H1D           	 
	Dimension		H1D(nQc)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	--------------------------------------------- Check compatibility
	if (nB.NE.nT*2) Then
		stop 'nB.NE.nT*2 in Form__B_and_Tmatrices'
	endif
!================================================== TEMPORARY
	abc =0 
	if(abc == 1) Then
		Axes = zero
		Axes(1,1) = one
		Axes(2,2) = one
		Axes(3,3) = one
	endif
!================================================== TEMPORARY:END
!-------------------------------------------------- Displacement/Bernstein
	call Bernstein(Br,nQc,Ri,iOut)
!-------------------------------------------------- Ist Derivative	
	call Bernstein_IstDerivative(H1D,nQc,Ri,iOut)
!-------------------------------------------------- T & B
	TC = zero
	TP = zero
!
	do 70 i = 1,3	! For 3D Curve Beam with axial & shear strains
	k = (i-1)*nQc 
	do 60 j = 1,nQc	! 
	TC(i,j+k)	= Br(j)				!u,w,v,tt,tm,tb
	TP(i,j+k)	= H1D(j)*AJI		!-primed
   60 continue
   70	continue
!------------------------- rotation for curvilinear
!	RT = MATMUL(TRANSPOSE(Axes),TC)	
!	RB = MATMUL(TRANSPOSE(Axes),TP)	
	RT = MATMUL(Axes,TC)	
	RB = MATMUL(Axes,TP)	
!---------------------------------------------- Check:Skew:OK
!	SK = MATMUL(Axes,TRANSPOSE(Axes))
!------------------------------------------------------------ Augment Axes
	Axes6	= zero
	Axes12	= zero
	do 80 i = 1,3
	do 80 j = 1,3
	Axes6(i,j)		= Axes(i,j)
	Axes6(i+3,j+3)	= Axes(i,j)
	Axes12(i,j)		= Axes(i,j)
	Axes12(i+3,j+3)	= Axes(i,j)
	Axes12(i+6,j+6)	= Axes(i,j)
	Axes12(i+9,j+9)	= Axes(i,j)
   80 continue
!============================================================ T & B
	T = zero
	B = zero
	nQc3 = 3*nQc
	do 90 i = 1,3
	do 90 j = 1,nQc3
	T(i,j)			= RT(i,j)
	T(i+3,j+nQc3)	= RT(i,j)
!
	B(i,j)			= RT(i,j)
	B(i+3,j+nQc3)	= RT(i,j)
	B(i+6,j)		= RB(i,j)
	B(i+9,j+nQc3)	= RB(i,j)
   90 continue
!============================================================
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nT,nD,(i,(T(i,j),j = 1,nD),i=1,nT)
		write(Iout,1020) nB,nD,(i,(B(i,j),j = 1,nD),i=1,nB)
	endif
	return
!
 1000	format(A,I5,A)
 1010 format("T(",I2,",",I2,")"/(I5/,5(6(f10.7,1X)/)))
 1020 format("B(",I2,",",I2,")"/(I5/,5(6(f10.7,1X)/)))
	end
