	Subroutine Impose_Continuity(StifN,FN,nStifN,T,StifNC,
     &							FC,nStifNC,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		T(nStifA,nStifNC)		= C1 or C2 Transformation Matrix
!		nStifN					= Row or Col size of NonSingStiffness matrix 
!		StifS(nStifN,nStifN)	= NonSingular global Stiffness Matrix
!		FN(nStifN)				= global Load Vector
!		nStifNC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		StifC(nStifC,nStifC)	= C1 or C2-Constrained global Stiffness Matrix
!								= (T-trans)StiffN(T)
!		FC(nStifC)				= C1 or C2-Constrained global Load Vector
!								= (T-trans)FN
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	StifN(nStifN,nStifN),FN(nStifN),T(nStifN,nStifNC)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	StifNC(nStifNC,nStifNC),FC(nStifNC),sum
	
!	//////////////////////
!
!	Stiffness Matrix Calculation
!
	do 30 i = 1,nStifNC
	do 30 j = 1,nStifNC
	sum =0.0D0
	do 20 k = 1,nStifN
	do 20 l = 1,nStifN
	sum = sum + T(k,i)*StifN(k,l)*T(l,j)
   20	continue
   	StifNC(i,j) = sum
   30 continue		 
!
!	Load Vector Calculation
!
	do 50 i = 1,nStifNC
	sum =0.0D0
	do 40 k = 1,nStifN
	sum = sum + T(k,i)*FN(k)
   40	continue
   	FC(i) = sum
   50 continue
!
!	done
!
	iPrt = 0
	if(iPrt == 1) then
		write(iOut,1000) nStifNC,nStifNC
		do ii = 1,nStifNC
			write(iOut,1010) ii,(StifNC(ii,jj),jj = 1,nStifNC)
		end do !ii
		write(iOut,1020) (FC(jj),jj = 1,nStifNC)
	endif
!   		 
	return
 1000 format(///"C1or2 Constrained Stiffness:Stif(",i2,",",i2,")"/)
 1010 format(I5/(5(f16.3,1X)))
 1020 format("C1or2 Constrained Force vector"/ (6(5x,f10.4)))
	end
	
	
	
	
	
	   		