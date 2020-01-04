	Subroutine FormS_Matrix(t,p,S,nS,c1,c2,c1b,c2b,Iout)
!	----------------------------------------------------------------------------- S Matrix
!	t		= theta column vector
!	p		= arbitrary column vector
!
!	tL		= sqrt(t(1)*t(1)+t(2)*t(2)+t(3)*t(3))
!	tL2		= tL*tL
!	tL3		= tL*tL2
!	c1		= (1-cos(tL))/tL2
!	c2		= (tL-sin(tL))/tL3
!	c1Bar	= ((1-tL2*c2) - 2*c1)/tL2
!	c2Bar	= (c1 - 3*c2)/tL2
!
!	S(p)	= -c1*pMatrix + c2*{(p x theta) - (theta x p)	+ (theta dot p)I } 
!			  + (theta x p)(-c2*I + c1Bar*thetaMatrix* + c2Bar*thetaMatrix^^2
!	----------------------------------------------------------------------------- 
!	Inputs
!		t				= Current Rotation: t(3)
!		p				= an arbitrary vector: p(3)
! 	
!	Outputs 
!		S(p)			= S Matrix: S(3,3)
!	------------------------------------------------------------

	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	t    ,p    ,S                
	Dimension		t(nS),p(nS),S(nS,nS)
	Real(kind=8)	tm       ,pm       ,tpt       ,ttp                
	Dimension		tm(nS,nS),pm(nS,nS),tpt(nS,nS),ttp(nS,nS)
	Real(kind=8)	tmtpt       ,t2tpt                
	Dimension		tmtpt(nS,nS),t2tpt(nS,nS)
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
!	------------------------------------------------------ pMatrix
	pm = 0.D0
	pm(1,2) = -p3
	pm(1,3) = p2
	pm(2,1) = p3
	pm(2,3) = -p1
	pm(3,1) = p2
	pm(3,2) = p1
!	------------------------------------------------------ p x thetaTranspose
	tpt(1,1) = p1*t1
	tpt(1,2) = p1*t2
	tpt(1,3) = p1*t3
	tpt(2,1) = p2*t1
	tpt(2,2) = p2*t2
	tpt(2,3) = p2*t3
	tpt(3,1) = p3*t1
	tpt(3,2) = p3*t2
	tpt(3,3) = p3*t3
!	------------------------------------------------------ theta x pTranspose
	ttp = TRANSPOSE(tpt)
!	------------------------------------------------------ (theta x pTranspose)thetaMatrix
	tmtpt = MATMUL(ttp, tm)    
!	------------------------------------------------------ (theta x pTranspose)thetaMatrix^^2
	t2tpt = MATMUL(tmtpt,tm)    
!	----------------------------------------------------------------------------- R Matrix
	S = zero
!
	S = S -c1* pm + c2*(tpt - two*ttp) -+ c1b*tmtpt +c2b*t2tpt
	S(1,1) = S(1,1) + c2*tdotp		 
	S(2,2) = S(2,2) + c2*tdotp		 
	S(3,3) = S(3,3) + c2*tdotp	
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		write(Iout,1010) (i,(S(i,j),j = 1,3),i=1,3)
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("S Matrix S(3,3)"/
     &        (I5,3(3(f10.7,1X)/)))
	end
