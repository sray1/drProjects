	Subroutine Jacobian_N_DeterminantRAT(W,Qc,nDim,nQc1,nQc2,ri,rj,
     &                 	              A1,A2,Det)
!	======================================================
!                   n     m-1
!	A1hat = m *  sum {  sum (Dif10*Qij*Bri(ri) ) } Brj(rj)
!                  j=0    i=0
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	Real(kind=8)	W(nDim,nQc1,nQc2),W1(nDim),W2(nDim)                  
	Real(kind=8)	P1(nDim),P2(nDim),Cod(nDim),Wod(nDim)                  
	Real(kind=8)	Qc(nDim,nQc1,nQc2),ri,rj,A1(nDim),A2(nDim)                   
	integer			nDim,nQc1,nQc2
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!=============================================================================== Temp Check
!	ri = 0.D0
!	rj = 0.D0
!	----------------------------------------------------------- Part metric Tensor
	nQcm = MAX(nQc1-1,nQc2-1)
!
	call Calc_P1_Hat(W,Qc,nDim,nQc1,nQc2,nQcm,ri,rj,P1)
	call Calc_P2_Hat(W,Qc,nDim,nQc1,nQc2,nQcm,ri,rj,P2)
!	----------------------------------------------------------- Fake metric Tensor with Weights
	call Calc_A1_Hat(W,nDim,nQc1,nQc2,nQcm,ri,rj,W1)
	call Calc_A2_Hat(W,nDim,nQc1,nQc2,nQcm,ri,rj,W2)
!	----------------------------------------------------------- Get Rat Surface
	call Calc_Coords_at_a_Pt_RAT(Cod,Qc,W,nDim,nQc1,nQc2,
     &									ri,rj)
!	----------------------------------------------------------- Get W Surface
	call Calc_Coords_at_a_Pt(Wod,W,nDim,nQc1,nQc2,
     &									ri,rj)
!	----------------------------------------------------------- metric tensor
	do k = 1,nDim
		A1(k) = (P1(k) - Cod(k)*W1(k))/Wod(k)
		A2(k) = (P2(k) - Cod(k)*W2(k))/Wod(k)
	end do !k
!	----------------------------------------------------------- Determinant
	call DotProduct(A1,A1,E,nDim,Iout)
	call DotProduct(A1,A2,F,nDim,Iout)
	call DotProduct(A2,A2,G,nDim,Iout)
!
	Det = DSQRT(E*G - F*F)
!
!	done
!
	return
	end
