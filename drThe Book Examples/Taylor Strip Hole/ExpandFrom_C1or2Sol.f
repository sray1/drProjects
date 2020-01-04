	Subroutine ExpandFrom_C1or2Sol(QE,nStifN,T,QC,nStifNC,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		T(nStifN,nStifCC)		= C1 or C2 Transformation Matrix
!		nStifNC					= Row or Col size of NonStiffness matrix 
!		QC(nStifNC)				= Solution
!		nStifC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		QE(nStifC)				= Expanded from C1 or C2-Constrained
									! global Solution
!								= (T)QC
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	QC        ,T
	Dimension		QC(nStifNC),T(nStifN,nStifNC)
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	QE        ,sum
	Dimension		QE(nStifN)
	
!	//////////////////////
!
	do 50 i = 1,nStifN
	sum =0.0D0
	do 40 k = 1,nStifNC
	sum = sum + T(i,k)*QC(k)
   40	continue
   	QE(i) = sum
   50 continue
  100 continue
!   		 
	return
	end   		