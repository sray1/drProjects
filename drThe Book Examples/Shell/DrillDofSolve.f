	Subroutine DrillDofSolve(Stif,F,nStiR,nSti3,Iout)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		Stif    		= Assembled Stiffness Matrix
!		F	    		= Assembled Load Vector
!		nStif			= Row or Col size of Stiffness matrix    
!		nSti3			= Col size of Drill DOF Bezier Controls:  d theta3 
!																   q
!		nStiR			= nStif - nSti3 
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		Trace			= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	Stif             ,F			 
	Dimension		Stif(nStif,nStif),F(nStif)
!	
!	Working Variables & Arrays	
!
	Real(kind=8)	StiR			 ,Sti3
	Dimension		StiR(nStiR,nStiR),Sti3(nStiR,nSti3)
	Real(kind=8)	FR		 ,F3
	Dimension		FR(nStiR),F3(nStiR,nSti2)
!	======================================================================== Break
!	Stiffness Matrix and Load Vector Break Apart
!
	Call Extract_Matrix2D
     &	(Stif,nStif,nStif,StiR,nStiR,nStiR,1,1,Iout)
	call Extract_Vector(F,nStif,FR,nStiR,1,Iout)
	Call Extract_Matrix2D
     &	(Stif,nStif,nStif,Sti3,nStiR,nSti3,nStiR+1,1,Iout)
	call Extract_Vector(F,nStif,F3,nSti3,nStiR+1,Iout)
!	======================================================================== Form
	MatMul(
!	======================================================================== Solv 1
	call Solve_AxEqB(StiR,FR,QRH,nStiR,nStiR,iOut)
		











	if (Nel.EQ.1) Then
		do 5 i = 1,nStif
		do 5 j = 1,nStif
    5		Stif(i,j) = 0.D0	! all elements = 0.
!
		do 10 i = 1,nStifEL
!		------------------------
		do 10 j = 1,nStifEL
   10		Stif(i,j) = StifEL(i,j) 
	else if (Nel.EQ.2) Then
		do 60 i = 1,nStifEL
		ii = Indx(i) 
!		------------------------
		do 60 j = 1,nStifEL
		jj = Indx(j) 
   60		Stif(ii,jj) = Stif(ii,jj)+ StifEL(i,j)
	end if
!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,nStif
	Trace = Trace + Stif(i,i)
   80 continue			
!
!	Check each col. vector for Null
!
	Add = 0.D0
	do 100 j = 1,nStif
	sum = 0.0 
	do  90 i = 1,nStif	
	sum = sum + Stif(i,j)
   90 continue
	Add(j) = sum
  100 continue			
!
!	done
!
!	 do 110 i = 1,nStif
!	 write(15,1010) i,(Stif(i,j),j = 1,nStif)
!  110 continue
!
	return
!
 1010 format("Full Stiffness Matrix:Stif(15,15)"/
     &        I5/(3(5(f10.6,1X)/)/))
	return
	end   	
