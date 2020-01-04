	Subroutine Calc_ReferenceProps(Qc,nDim,nQc1,nQc2,ri,rj,Det)
!	======================================================
!                   n     m-1
!	A1hat = m *  sum {  sum (Dif10*Qij*Bri(ri) ) } Brj(rj)
!                  j=0    i=0
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	Real(kind=8)	Qc(nDim,nQc1,nQc2),ri,rj                   
	integer			nDim,nQc1,nQc2
!
	DATA zero/0.D0/,one/1.0D0/,two/2.0D0/,three/3.0D0/ 
!=============================================================================== Temp Check
!	ri = 0.D0
!	rj = 0.D0
!	----------------------------------------------------------- metric Tensor
	nQcm = MAX(nQc1-1,nQc2-1)
!
	call Calc_A1_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A1hat)
	call Calc_A2_Hat(Qc,nDim,nQc1,nQc2,nQcm,ri,rj,A2hat)

!	call VectorNorm(A2hat,A,3,Iout)
!	call ScaleVector(A2hat,uA2hat,1.D0/A,3,Iout)
!	---------------------------------------------------- RootAhat
	call DotProduct(A1hat,A1hat,E,nDim,Iout)
	call DotProduct(A1hat,A2hat,F,nDim,Iout)
	call DotProduct(A2hat,A2hat,G,nDim,Iout)
!
	Det = DSQRT(E*G - F*F)
!
!	done
!
	return
	end
