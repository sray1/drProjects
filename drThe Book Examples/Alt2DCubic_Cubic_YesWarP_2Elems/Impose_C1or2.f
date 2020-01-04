	Subroutine Impose_Continuity(StifN,FN,nStifN,T,StifC,FC,nStifC)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		T(nStifN,nStifC)		= C1 or C2 Transformation Matrix
!		nStifN					= Row or Col size of NonStiffness matrix 
!		StifN(nStifN,nStifN)	= Non-Singular global Stiffness Matrix
!		FN(nStifN)				= global Load Vector
!		nStifC					= Row or Col size of ConStiffness matrix
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
	Real(kind=8)	StifN			    ,FN        ,T
	Dimension		StifN(nStifN,nStifN),FN(nStifN),T(nStifN,nStifC)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	StifC			    ,FC        ,sum
	Dimension		StifC(nStifC,nStifC),FC(nStifC)
	
!	//////////////////////
!
!	Stiffness Matrix Calculation
!
	do 30 i = 1,nStifC
	do 30 j = 1,nStifC
	sum =0.0D0
	do 20 k = 1,nStifN
	do 20 l = 1,nStifN
	sum = sum + T(k,i)*StifN(k,l)*T(l,j)
   20	continue
   	StifC(i,j) = sum
   30 continue		 
!
!	Load Vector Calculation
!
	do 50 i = 1,nStifC
	sum =0.0D0
	do 40 k = 1,nStifN
	sum = sum + T(k,i)*FN(k)
   40	continue
   	FC(i) = sum
   50 continue
!   		 
	return
	end   		