	Subroutine DifferenceOp_2(Qc,nDim,nQc1,nQc2,i1,j2,
     &									Dif2,iTyp,iOut)
!	======================================================
	Implicit Real(kind=8) (a-h,o-z)
!	====================
	real(kind = 8)	Qc                
	Dimension		Qc(nDim,nQc1,nQc2)
	real(kind = 8)	Diff      ,Dif2
	Dimension		Diff(nDim),Dif2(nDim)
	integer			nQc1,nQc2,iOut
!---------------------------------------- 
	Dif2	= 0.D0
!		
	if(iTyp == 1) then
!		---------------------------------------- Dif11 = Dif10(i,j+1) - Dif10(i,j) (Type 1) 
!		-------------------------------------or: Dif11 = Dif01(i+1,j) - Dif01(i,j) (Type 2) SELECTED 
		do 20 k= 1,nDim
!	===================
		call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i1+1,j2,
     &									Diff,2,iOut)
!	===================
		Dif2(k) = Diff(k)
!	===================
		call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i1,j2,
     &									Diff,2,iOut)
!	===================
		Dif2(k) = Dif2(k) - Diff(k)
   20		continue
	elseif (iTyp == 2) then
!		---------------------------------------- Dif20 = Dif10(i+1,j) - Dif10(i,j) (Type 1)
		do 40 k= 1,nDim
!	===================
		call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i1+1,j2,
     &									Diff,1,iOut)
!	===================
		Dif2(k) = Diff(k)
!	===================
		call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i1,j2,
     &									Diff,1,iOut)
!	===================
		Dif2(k) = Dif2(k) - Diff(k)
   40		continue
	elseif (iTyp == 3) then
!		---------------------------------------- Dif02 = Dif01(i,j+1) - Dif01(i,j) (Type 2)
		do 60 k= 1,nDim
!	===================
		call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i1,j2+1,
     &									Diff,2,iOut)
!	===================
		Dif2(k) = Diff(k)
!	===================
		call DifferenceOp_1(Qc,nDim,nQc1,nQc2,i1,j2,
     &									Diff,2,iOut)
!	===================
		Dif2(k) = Dif2(k) - Diff(k)
   60		continue
	endif
!
!	done
!
!------------------------------------  	
	return
	end
