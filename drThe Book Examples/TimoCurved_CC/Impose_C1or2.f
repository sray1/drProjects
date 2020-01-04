	Subroutine Impose_Continuity(StifS,FS,nStifS,T,StifC,FC,nStifC
     &														,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		T(nStifA,nStifC)		= C1 or C2 Transformation Matrix
!		nStifS					= Row or Col size of SingStiffness matrix 
!		StifS(nStifS,nStifS)	= Singular global Stiffness Matrix
!		FS(nStifS)				= global Load Vector
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
	Real(kind=8)	StifS			    ,FS        ,T
	Dimension		StifS(nStifS,nStifS),FS(nStifS),T(nStifS,nStifC)
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
	do 20 k = 1,nStifS
	do 20 l = 1,nStifS
	sum = sum + T(k,i)*StifS(k,l)*T(l,j)
   20	continue
   	StifC(i,j) = sum
   30 continue		 
!
!	done
!
	write(Iout,1000) nStifC,nStifC
	do 110 i = 1,nStifC
	write(Iout,1010) i,(StifC(i,j),j = 1,nStifC)
!	Pause
  110	continue
!
!	Load Vector Calculation
!
	do 50 i = 1,nStifC
	sum =0.0D0
	do 40 k = 1,nStifS
	sum = sum + T(k,i)*FS(k)
   40	continue
   	FC(i) = sum
   50 continue
!   		 
	return
!
 1000 format("Full Stiffness Matrix:Stif(",I2,",",I2,")"/)
 1010 format(I5/(3(5(f10.6,1X)/)/))
	end   		