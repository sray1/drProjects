	Subroutine DifferenceOp_1(Qc,nDim,nQc1,nQc2,i1,j2,
     &								Diff,iTyp,iOut)
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	real(kind = 8)	Qc                
	Dimension		Qc(nDim,nQc1,nQc2)
	real(kind = 8)	Diff
	Dimension		Diff(nDim)
	integer			nQc1,nQc2,iOut
!
	Diff	= 0.D0
!		
	if(iTyp == 1) then
!		---------------------------------------- Dif10 = Q(i+1,j) - Q(i,j) (Type 1)
		do 30 k= 1,nDim
		Diff(k) = Qc(k,i1+1,j2) - Qc(k,i1,j2)
   30		continue
!		---------------------------------------- Dif01 = Q(i,j+1) - Q(i,j) (Type 2)
	elseif (iTyp == 2) then
		do 40 k= 1,nDim
		Diff(k) = Qc(k,i1,j2+1) - Qc(k,i1,j2)
   40		continue
	endif
!
!	done
!
!------------------------------------  	
	return
	end
