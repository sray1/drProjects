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
	Real(kind=8)	T       ,B
	Dimension		T(nT,nD),B(nB,nD)				! T(6,6n),B(12,6n)
	Real(kind=8)	TC       ,BC
	Dimension		TC(nT,nD),BC(nT,nD)				! TC(6,6n),BC(6,6n)
!
!		ndegR					= Bezier degree in r-dir = 4
!		ndegS					= Bezier degree in s-dir = 4
!
	Real(kind=8)	dum,xMult
	Real(kind=8)	Axes     ,Axes6     ,Axes12  
	Dimension		Axes(3,3),Axes6(6,6),Axes12(12,12)
	Real(kind=8)	AxeP     ,AxeP6,BP  
	Dimension		AxeP(3,3),AxeP6(6,6),BP(nT,nD)
	Real(kind=8)	Br   
	Dimension		Br(nQc)
	Real(kind=8)	H1D           	 
	Dimension		H1D(nQc)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	--------------------------------------------- Check compatibility
	if (nB.NE.nT*2) Then
		stop 'nB.NE.nT*2 in Form__B_and_Tmatrices'
	endif
!-------------------------------------------------- T & B
	TC = zero
	BC = zero
!
	do 70 i = 1,nT	! For 3D Curve Beam with axial & shear strains
	k = (i-1)*nQc 
	do 60 j = 1,nQc	! 
!	do 60 m = 1,nT 
	TC(i,j+k)		= Br(j)				!u,w,v,tt,tm,tb
	BC(i,j+k)		= H1D(j)*AJI		!-primed
!	T(i,j+k)		= Br(j)				!u,w,v,tt,tm,tb
!	B(i,j+k)		= Br(j)				!u,w,v,tt,tm,tb
!	B(nT+i,j+k)		= H1D(j)*AJI		!-primed
   60 continue
   70	continue
!================================== Axes primed
	do 5 j = 1,3
	AxeP(1,j) =   Cur*Axes(2,j)!*AJI
	AxeP(2,j) = (-Cur*Axes(1,j) + Tor*Axes(3,j))!*AJI
	AxeP(3,j) = (-Tor*Axes(3,j))!*AJI
    5 continue
!================================== Augment Axes
	do 10 i = 1,3	.
	do 10 j = 1,3	.
	Axes6(i,j)		= Axes(i,j)
	Axes6(i+3,j+3)	= Axes(i,j)
	AxeP6(i,j)		= AxeP(i,j)
	AxeP6(i+3,j+3)	= AxeP(i,j)
   10 continue
!================================== T
	T	= MATMUL(Axes6,TC)
!================================== B
	BP	= MATMUL(Axes6,BC)! + MATMUL(AxeP6,TC)
!
	B = zero
	do 90 i = 1,nT	! For 3D Curve Beam with axial & shear strains
	k = (i-1)*nQc 
	do 80 j = 1,nQc	! 
	do 80 m = 1,nT 
	B(i,j+k)	=  T(i,j+k)		!u,w,v,tt,tm,tb
	B(nT+i,j+k)	= BP(i,j+k)		!-primed
   80 continue
   90	continue

!==================================
!
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
