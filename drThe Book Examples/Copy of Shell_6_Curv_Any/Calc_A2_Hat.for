	Subroutine Calc_A2_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A2hat)
!	======================================================
!                   m     n-1
!	A2hat = n *  sum {  sum (Dif01*Qij*Brj(rj) ) } Bri(ri)
!                  i=0    j=0
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A2hat      ,Dif01    
	Dimension		A2hat(nDim),Dif01(nDim)
	Real(kind=8)	Qc                ,Bri      ,Brj    
	Dimension		Qc(nDim,nQc1,nQc2),Bri(nQc1),Brj(nQc2)
!
	nQc2m	= nQc2-1
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQc1,ri,iOut)
	call Bernstein(Brj,nQc2m,rj,iOut)
!	------------------------------
	A2hat = 0.D0	
!
	do 30 i= 1,nQc1
	do 30 j= 1,nQc2m
!	===================
	call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i,j,
     &								Dif01,2,iOut)
!	===================
	do 20 k= 1,nDim
	A2hat(k) = A2hat(k) + Dif01(k)*Bri(i)*Brj(j) 
   20	continue
!
!   10	continue
   30	continue
!
	A2hat = nQc2m * A2hat
!
!	done
!
	return
	end
