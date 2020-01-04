	Subroutine Form_WMatrix(t,W,nW,Iout)
!	---------------------------------------------------------------------------- W Matrix
!	tL	= sqrt(t(1)*t(1)+t(2)*t(2)+t(3)*t(3))
!	tL2 = tL*tL
!	tL3 = tL*tL2
!	C1	= (1-cos(tL))/tL2
!	C2	= (tL-sin(tL))/tL3
!	W	= I + c1*thetaMatrix + c2*thetaMatrix^^2
!		= (sin(tL)/tL)I + c1*thetaMatrix + c2* (theta x theta_Transpose)
!		|	a + c2*t1*t1            c1*(-t3) + c2*t1*t2     c1*t2 + c2*t1*t3	|
!		| c1*(t3) + c2*t1*t2			a + c2*t2*t2		c1*(-t1) + c2*t2*t3	| 
!		| c1*(-t2) + c2*t1*t3		c1*(t1) + c2*t2*t3			a + c2*t3*t3	| 
!	-----------------------------------------------------------------------------
!	Inputs
!		t				= Current Rotation: t(3)
!		nW				= 3
! 	
!	Outputs 
!		W				= W Matrix: W(3,3)
!
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	t    ,W                
	Dimension		t(nW),W(nW,nW)
!
	common/ThetaConstants/c1,c2,c1b,c2b
!
	DATA zero/0.D0/,one/1.0D0/ 
!	----------------------------------------------------------------------------- W Matrix	 
	t1 = t(1)
	t2 = t(2)
	t3 = t(3)
	tL	= dsqrt(t1*t1+t2*t2+t3*t3)
!	---------------------------------------------------------- check theta = zero
	if (tL==zero) Then
		a	= one			!limit (sin(tL)/tL) -> 1 as tL->0
	else
		st	= dsin(tL)
		a	= st/tL
	endif
!	--------------------
	t11	= t1*t1
	t12	= t1*t2
	t13	= t1*t3
	t22	= t2*t2
	t23	= t2*t3
	t33	= t3*t3
!	-----------------------------------------------------------------------------
	W(1,1) = a + c2*t11 
	W(1,2) = -c1*t3 + c2*t12  
	W(1,3) = c1*t2 + c2*t13
	W(2,1) = c1*t3 + c2*t12
	W(2,2) = a + c2*t22
	W(2,3) = -c1*t1 + c2*t23
	W(3,1) = -c1*t2 + c2*t13
	W(3,2) = c1*t1 + c2*t23
	W(3,3) = a + c2*t33 
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(W(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("W Matrix W(3,3)"/( (I5,3(f20.7,1X))  ))
	end
