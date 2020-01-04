	Subroutine FormF_a_PartMatrix(t,p,S,nS,iType,Iout)
!	----------------------------------------------------------------------------- 
! iType = 1
!	t		= F (force) column vector
!	p		= a = (e + [ko]d) column vector
!
!	S(F) = (F x aTrans) + (a x FTrans) -2*(F dot a)I
!
! iType = 2
!	t		= M (moment) column vector
!	p		= kc = ko + k column vector
!
!	S(M) = (M x kcTrans) + (kc x MTrans) -2*(M dot kc)I
!
!	----------------------------------------------------------------------------- 
!	Inputs
!		t				= t(3)
!		p				= p(3)
! 	
!	Outputs 
!		F_a part		if iType = 1
!		M_kc part		if iType = 2
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
!
	p1 = p(1)
	p2 = p(2)
	p3 = p(3)
!
	tdotp = t1*p1 +t2*p2 +t3*p3 	
!	------------------------------------------------------ a x FTranspose
	tpt(1,1) = p1*t1
	tpt(1,2) = p1*t2
	tpt(1,3) = p1*t3
	tpt(2,1) = p2*t1
	tpt(2,2) = p2*t2
	tpt(2,3) = p2*t3
	tpt(3,1) = p3*t1
	tpt(3,2) = p3*t2
	tpt(3,3) = p3*t3
!	------------------------------------------------------ F x aTranspose
	ttp = TRANSPOSE(tpt)
!	----------------------------------------------------------------------------- Matrix
	S = zero
!
	S = S + ttp + tpt
	S(1,1) = S(1,1) - two*tdotp		 
	S(2,2) = S(2,2) - two*tdotp		 
	S(3,3) = S(3,3) - two*tdotp	
!---------------------------------------------------------- Write:
	iPrt = 0
	if (iPrt == 1) Then
		if(iType == 1) Then
			write(Iout,1010) (i,(S(i,j),j = 1,3),i=1,3)
		elseif (iType == 2) Then
			write(Iout,1020) (i,(S(i,j),j = 1,3),i=1,3)
		endif
	endif
!----------------------------------------------------------
	return
!
 1000	format(A,I5,A)
 1010 format("F_a_PartMatrix(3,3)"/( (I5,3(f20.7,1X))  ))
 1020 format("M_kc_PartMatrix(3,3)"/( (I5,3(f20.7,1X))  ))
	end
