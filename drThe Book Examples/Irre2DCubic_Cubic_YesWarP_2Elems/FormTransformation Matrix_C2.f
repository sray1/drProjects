	Subroutine FormTransformationMatrix_C2(T,nStifN,nStifC)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C2- Contraints:
!	 old Rows        new Cols	  old Rows       new Cols
!		i2  = (1/2){ i1  + i2 ) |	i30 = (1/2){ i2  + i22)
!		i6  = (1/2){ i4  + i5 ) |	i33 = (1/2){ i5  + i24)
!		i10 = (1/2){ i7  + i8 ) |	i36 = (1/2){ i8  + i26)
!		i13 = (1/2){ i9  + i10) |	i39 = (1/2){ i10 + i28)
!		i16 = (1/2){ i11 + i12) |	i42 = (1/2){ i12 + i30)
!		i20 = (1/2){ i14 + i15) |	i45 = (1/2){ i15 + i32)
!		i24 = (1/2){ i17 + i18) |	i48 = (1/2){ i18 + i34)
!		i28 = (1/2){ i20 + i21) |	i51 = (1/2){ i21 + i36)
!---------------------------------|--------------------------
!	 old Rows        new Cols	  old Rows       new Cols
!		i3  = (1/4){ i1  } + (1/2){ i2  } + (1/4){ i22)
!		i7  = (1/4){ i4  } + (1/2){ i5  } + (1/4){ i24)
!		i11 = (1/4){ i7	 } + (1/2){ i8  } + (1/4){ i26)
!		i14 = (1/4){ i9	 } + (1/2){ i10 } + (1/4){ i28)
!		i17 = (1/4){ i11 } + (1/2){ i12 } + (1/4){ i30)
!		i21 = (1/4){ i14 } + (1/2){ i15 } + (1/4){ i32)
!		i25 = (1/4){ i17 } + (1/2){ i18 } + (1/4){ i34)
!		i29 = (1/4){ i20 } + (1/2){ i21 } + (1/4){ i36)
!---------------------------------|--------------------------
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
!	Output Variables & Arrays	
!
	Real(kind=8)	T				,half,quar
	Dimension		T(nStifN,nStifC)
	
	Integer DofR1(8),DofR2(8),DofR3(8),nDof
	Integer Loc1(8),Loc2(8),Loc3(8)
	DATA DofR1  / 2, 6,10,13,16,20,24,28/	!To be removed by (1/2){Loc1+Loc2}
	DATA DofR2  /30,33,36,39,42,45,48,51/	!To be removed by (1/2){Loc2+Loc3}
	DATA DofR3  / 3, 7,11,14,17,21,25,29/	!To be replaced with:
											!  (1/4)Loc1+(1/2)Loc2+(1/4)Loc3
	DATA Loc1   / 1, 4, 7, 9,11,14,17,20/	! these and
	DATA Loc2   / 2, 5, 8,10,12,15,18,21/	! these
	DATA Loc3   /22,24,26,28,30,32,34,36/	! these
	DATA nDof/8/
!---------------------------
	Stop ' need to change C2'
!	//////////////////////
!	Transformation Matrix 
!
	half	= 0.5D0
	quar	= 0.25D0
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifN
		do 10 k = 1,nDof
			if(i == DofR1(k)) Then
				T(i,Loc1(k)) = half
				T(i,Loc2(k)) = half
				iremoved = iremoved + 1
				go to 20
			else if(i == DofR2(k)) Then
				T(i,Loc2(k)) = half
				T(i,Loc3(k)) = half
				iremoved = iremoved + 1
				go to 20
			else if(i == DofR3(k)) Then
				T(i,Loc1(k)) = quar
				T(i,Loc2(k)) = half
				T(i,Loc3(k)) = quar
				go to 30
			end if
   10     continue
		T(i,i-iremoved) = 1.0D0 
   20		continue
   30 continue
   40 continue		 
!
!	OPEN (unit = 16, FILE = 'Tran_C2.prt', STATUS = 'NEW')
!	do 110 i = 1,nStifN
!	write(16,1010) nStifN,nStifC,i,(T(i,j),j = 1,nStifC)
!  110	continue
  120 continue
!
!
 1010 format("C2 Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(4(10(f5.2,1X)/)))
!   		 
	return
	end   		