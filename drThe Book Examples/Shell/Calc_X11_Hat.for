	Subroutine Calc_X11_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,X11hat)
!	actual degree m = nQc1 -1
!	actual degree n = nQc2 -1
!	Because indices run from 1,...nQc1 instead of i = 0,....m
!	Because indices run from 1,...nQc2 instead of j = 0,....n
!	so, range 0 to m-2 becomes 1 to nQc1-2, etc.
!	==============================================================
!                           n     m-2
!	X11hat = m*(m-1)  *  sum {  sum (Dif20*Qij*Bri(ri) ) } Brj(rj)
!                          j=0    i=0
!	==============================================================
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	X11hat      ,Dif20    
	Dimension		X11hat(nDim),Dif20(nDim)
	Real(kind=8)	Qc                ,Bri      ,Brj    
	Dimension		Qc(nDim,nQc1,nQc2),Bri(nQc1),Brj(nQc2)

!
	nQc1m1	= nQc1-1	! actual degree     = m
	nQc1m2	= nQc1-2	! actual degree - 1 = m-1
!	-------------------------------------------- Basis Functions		 
	call Bernstein(Bri,nQc1m2,ri,iOut)
	call Bernstein(Brj,nQc2,rj,iOut)
!	------------------------------
	X11hat	= 0.D0	
!
	do 30 j= 1,nQc2
	do 10 i= 1,nQc1m2
!	===================								Dif20 = (Type 2)
	call DifferenceOp_2(Qc,nDim,nQc1,nQc2,i,j,
     &								Dif20,2,iOut)
!	===================
	do 20 k= 1,nDim
	X11hat(k) = X11hat(k) + Dif20(k)*Bri(i)*Brj(j) 
   20	continue
!
   10	continue
   30	continue
!
	X11hat = nQc1m1 * nQc1m2 * X11hat
!
!	done
!
	return
	end
