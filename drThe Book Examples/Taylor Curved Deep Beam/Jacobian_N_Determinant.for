	Subroutine Jacobian_N_Determinant(Qc,nDim,nQc1,nQc2,ri,rj,
     &                 	              A1,A2,Det)
!	======================================================
!                   n     m-1
!	A1hat = m *  sum {  sum (Dif10*Qij*Bri(ri) ) } Brj(rj)
!                  j=0    i=0
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	Real(kind=8)	Qc(nDim,nQc1,nQc2),ri,rj,A1(nDim),A2(nDim)                   
	integer			nDim,nQc1,nQc2
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!=============================================================================== Temp Check
!	ri = 0.D0
!	rj = 0.D0
!	----------------------------------------------------------- metric Tensor
	nQcm = MAX(nQc1-1,nQc2-1)
!
	call Calc_A1_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A1)
	call Calc_A2_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A2)
!	---------------------------------------------------- Determinant
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
