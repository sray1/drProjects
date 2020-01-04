	Subroutine FormR_Matrix(t,p,R,nR,c1,c2,c1b,c2b,Iout)
!	----------------------------------------------------------------------------- R Matrix
!	t		= theta column vector
!	tP		= theta_Primed column vector
!
!	tL		= sqrt(t(1)*t(1)+t(2)*t(2)+t(3)*t(3))
!	tL2		= tL*tL
!	tL3		= tL*tL2
!	c1		= (1-cos(tL))/tL2
!	c2		= (tL-sin(tL))/tL3
!	c1Bar	= ((1-tL2*c2) - 2*c1)/tL2
!	c2Bar	= (c1 - 3*c2)/tL2
!
!	R	= -c1*thetaMatrixPrimed + c2*{(theta x thetaPrimeTrans)-2*(thetaPrime x thetaTrans)
!			+ (theta dot thetaPrime)I } + c1Bar*thetaMatrix*(thetaPrime x thetaTrans)
!			+ c2Bar*thetaMatrix^^2*(thetaPrime x thetaTrans)
!	----------------------------------------------------------------------------- 
!	Inputs
!		t				= Current Rotation: t(3)
!		p				= Current Rotation_Primed: p(3)
! 	
!	Outputs 
!		R				= R Matrix: R(3,3)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	t    ,p    ,R                
	Dimension		t(nR),p(nR),R(nR,nR)
	Real(kind=8)	tm       ,pm       ,tpt       ,ttp                
	Dimension		tm(nR,nR),pm(nR,nR),tpt(nR,nR),ttp(nR,nR)
	Real(kind=8)	tmtpt       ,t2tpt                
	Dimension		tmtpt(nR,nR),t2tpt(nR,nR)
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!	-----------------------------------------------------------------------------
	t1 = t(1)
	t2 = t(2)
	t3 = t(3)
	p1 = p(1)
	p2 = p(2)
	p3 = p(3)
!
	tdotp = t1*p1 +t2*p2 +t3*p3 	
!	------------------------------------------------------ thetaMatrix
	tm = 0.D0
	tm(1,2) = -t3
	tm(1,3) = t2
	tm(2,1) = t3
	tm(2,3) = -t1
	tm(3,1) = t2
	tm(3,2) = t1
!	------------------------------------------------------ thetaMatrixPrimed
	pm = 0.D0
	pm(1,2) = -p3
	pm(1,3) = p2
	pm(2,1) = p3
	pm(2,3) = -p1
	pm(3,1) = p2
	pm(3,2) = p1
!	------------------------------------------------------ thetaPrime x thetaTrans
	tpt(1,1) = p1*t1
	tpt(1,2) = p1*t2
	tpt(1,3) = p1*t3
	tpt(2,1) = p2*t1
	tpt(2,2) = p2*t2
	tpt(2,3) = p2*t3
	tpt(3,1) = p3*t1
	tpt(3,2) = p3*t2
	tpt(3,3) = p3*t3
!	------------------------------------------------------ theta x thetaPrimeTranspose
	ttp = TRANSPOSE(tpt)
!	------------------------------------------------------ thetaMatrix x (thetaPrime x thetaTrans)
	tmtpt = MATMUL(tm, tpt)    
!	------------------------------------------------------ thetaMatrix^^2 x (thetaPrime x thetaTrans)
	t2tpt = MATMUL(tm, tmtpt)    
!	----------------------------------------------------------------------------- R Matrix
	R = zero
!
	R = R -c1* pm + c2*(ttp - two*tpt) + c1b*tmtpt +c2b*t2tpt
	R(1,1) = R(1,1) + c2*tdotp		 
	R(2,2) = R(2,2) + c2*tdotp		 
	R(3,3) = R(3,3) + c2*tdotp	
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(R(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("R Matrix R(3,3)"/( (I5,3(f20.7,1X))  ))
	end
