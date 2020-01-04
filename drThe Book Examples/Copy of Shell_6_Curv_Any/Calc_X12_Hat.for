	Subroutine Calc_X12_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,X12hat)
!	actual degree m = nQc1 -1
!	actual degree n = nQc2 -1
!	Because indices run from 1,...nQc1 instead of i = 0,....m
!	Because indices run from 1,...nQc2 instead of j = 0,....n
!	so, range 0 to n-2 becomes 1 to nQc2-2, etc.
!	==============================================================
!                           n     m-2
!	X12hat = m*(m-1)  *  sum {  sum (Dif20*Qij*Bri(ri) ) } Brj(rj)
!                          j=0    i=0
!	==============================================================
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	X12hat      ,Dif11    
	Dimension		X12hat(nDim),Dif11(nDim)
	Real(kind=8)	Qc                ,Bri      ,Brj    
	Dimension		Qc(nDim,nQc1,nQc2),Bri(nQc1),Brj(nQc2)

!
	nQc1m1	= nQc1-1	! actual degree     = m
	nQc2m1	= nQc2-1	! actual degree     = n
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQc1m1,ri,iOut)
	call Bernstein(Brj,nQc2m1,rj,iOut)
!	------------------------------
	X12hat	= 0.D0	
!
	do 30 i= 1,nQc1m1
	do 10 j= 1,nQc2m1
!	===================									Dif02 = (Type 1)
	call DifferenceOp_2(Qc,nDim,nQc1,nQc2,i,j,
     &								Dif11,1,iOut)
!	===================
	do 20 k= 1,nDim
	X12hat(k) = X12hat(k) + Dif11(k)*Bri(i)*Brj(j) 
   20	continue
!
   10	continue
   30	continue
!
	X12hat = nQc1m1 * nQc2m1 * X12hat
!
!	done
!
	return
	end
