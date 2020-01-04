	Subroutine Calc_X22_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,X22hat)
!	actual degree m = nQc1 -1
!	actual degree n = nQc2 -1
!	Because indices run from 1,...nQc1 instead of i = 0,....m
!	Because indices run from 1,...nQc2 instead of j = 0,....n
!	so, range 0 to n-2 becomes 1 to nQc2-2, etc.
!	==============================================================
!                           n     m-2
!	X22hat = m*(m-1)  *  sum {  sum (Dif20*Qij*Bri(ri) ) } Brj(rj)
!                          j=0    i=0
!	==============================================================
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	X22hat      ,Dif02    
	Dimension		X22hat(nDim),Dif02(nDim)
	Real(kind=8)	Qc                ,Bri      ,Brj    
	Dimension		Qc(nDim,nQc1,nQc2),Bri(nQc1),Brj(nQc2)

!
	nQc2m1	= nQc2-1	! actual degree     = n
	nQc2m2	= nQc2-2	! actual degree - 1 = n-1
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQc1,ri,iOut)
	call Bernstein(Brj,nQc2m2,rj,iOut)
!	------------------------------
	X22hat	= 0.D0	

!	do 30 j= 1,nQc1
!	do 10 i= 1,nQc2m2
	do 30 i= 1,nQc1
	do 10 j= 1,nQc2m2
!	===================									Dif02 = (Type 3)
	call DifferenceOp_2(Qc,nDim,nQc1,nQc2,i,j,
     &								Dif02,3,iOut)
!	===================
	do 20 k= 1,nDim
	X22hat(k) = X22hat(k) + Dif02(k)*Bri(i)*Brj(j) 
   20	continue
!
   10	continue
   30	continue
!
	X22hat = nQc2m1 * nQc2m2 * X22hat
!
!	done
!
	return
	end
