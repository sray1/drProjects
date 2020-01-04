	Subroutine FormTransformationMatrix_C1(T,nStifN,nStifC)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C1- Contraints:
!	 old Row         new Cols	
!		i3  = (1/2){ i2  + i22)
!		i7  = (1/2){ i5  + i25)
!		i11 = (1/2){ i8  + i28)
!		i14 = (1/2){ i10 + i31)
!		i17 = (1/2){ i12 + i34)
!		i21 = (1/2){ i15 + i37)
!		i25 = (1/2){ i18 + i40)
!		i29 = (1/2){ i21 + i43)
!-----------------------------------
!
!	Inputs
!		nStifN					= Row or Col size of NonStiffness matrix 
!		nStifC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		T(nStifN,nStifC)		= C0 Transformation Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	T				,half
	Dimension		T(nStifN,nStifC)
	
	Integer DofR(8),Loc1(8),Loc2(8), nDof
	DATA DofR  /3 ,7 ,11,14,17,21,25,29/	!To be removed by
	DATA Loc1  /2 ,5 , 8,10,12,15,18,21/	! these and
	DATA Loc2  /22,25,28,31,34,37,40,43/	! these
	DATA nDof/8/
!	//////////////////////
!	Transformation Matrix 
!
	half	= 0.5D0
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifN
		do 10 k = 1,nDof
			if(i == DofR(k)) Then
				T(i,Loc1(k)) = half
				T(i,Loc2(k)) = half
				iremoved = iremoved + 1
				go to 20
			end if
   10     continue
		T(i,i-iremoved) = 1.0D0 
   20		continue
   30 continue
   40 continue		 
!
!
	OPEN (unit = 17, FILE = 'Tran_C1.prt', STATUS = 'NEW')
	do 110 i = 1,nStifN
	write(17,1010) nStifN,nStifC,i,(T(i,j),j = 1,nStifC)
  110	continue
  120 continue
!
!
 1010 format("C1 Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(5(9(f5.2,1X)/)))
!   		 
!   		 
	return
	end   		