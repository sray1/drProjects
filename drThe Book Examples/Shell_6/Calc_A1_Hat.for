	Subroutine Calc_A1_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A1hat)
!	======================================================
!                   n     m-1
!	A1hat = m *  sum {  sum (Dif10*Qij*Bri(ri) ) } Brj(rj)
!                  j=0    i=0
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!
	Real(kind=8)	A1hat      ,Dif10    
	Dimension		A1hat(nDim),Dif10(nDim)
	Real(kind=8)	Qc                ,Bri      ,Brj    
	Dimension		Qc(nDim,nQc1,nQc2),Bri(nQc1),Brj(nQc2)
!
	nQc1m	= nQc1-1
!	-------------------------------------------- Basis Functions
	Bri = 0.D0		 
	call Bernstein(Bri,nQc1m,ri,iOut)
	call Bernstein(Brj,nQc2,rj,iOut)
!	------------------------------
	A1hat = 0.D0	
!
	do 30 i= 1,nQc1m
	do 30 j= 1,nQc2
!	===================
	call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i,j,
     &								Dif10,1,iOut)
!	===================
	do 20 k= 1,nDim
	A1hat(k) = A1hat(k) + Dif10(k)*Bri(i)*Brj(j) 
   20	continue
!
!   10	continue
   30	continue
!
	A1hat = nQc1m * A1hat
!
!	done
!
	return
	end
