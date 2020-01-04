	Subroutine FormTransformationMatrix_C2(T,nStifN,nStifC)
!
!	Coerced Isoparametric Quadrilateral_Quadratic_Cubic Element
!------------------------------------------------------------
!	C2- Contraints:
!	 old Rows        new Cols	  old Rows       new Cols
!		i3  = (1/2){ i2  + i3 ) |	i25 = (1/2){ i3  + i19)
!		i7  = (1/2){ i5  + i6 ) |	i28 = (1/2){ i6  + i21)
!		i11 = (1/2){ i8  + i9 ) |	i31 = (1/2){ i9  + i23)
!		i15 = (1/2){ i11 + i12) |	i34 = (1/2){ i12 + i25)
!		i19 = (1/2){ i14 + i15) |	i37 = (1/2){ i15 + i27)
!		i23 = (1/2){ i17 + i18) |	i40 = (1/2){ i18 + i29)
!---------------------------------|--------------------------
!	 old Rows        new Cols	  old Rows       new Cols
!		i4  = (1/4){ i2  } + (1/2){ i3  } + (1/4){ i19)
!		i8  = (1/4){ i5  } + (1/2){ i6  } + (1/4){ i21)
!		i12 = (1/4){ i8	 } + (1/2){ i9  } + (1/4){ i23)
!		i16 = (1/4){ i11 } + (1/2){ i12 } + (1/4){ i25)
!		i20 = (1/4){ i14 } + (1/2){ i15 } + (1/4){ i27)
!		i24 = (1/4){ i17 } + (1/2){ i18 } + (1/4){ i29)
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
	
	Integer DofR1(6),DofR2(6),DofR3(6),nDof
	Integer Loc1(6),Loc2(6),Loc3(6)
	DATA DofR1  / 3, 7,11,15,19,23/	!To be removed by (1/2){Loc1+Loc2}
	DATA DofR2  /25,28,31,34,37,40/	!To be removed by (1/2){Loc2+Loc3}
	DATA DofR3  / 4, 8,12,16,20,24/	!To be replaced with:
											!  (1/4)Loc1+(1/2)Loc2+(1/4)Loc3
	DATA Loc1   / 2, 5, 8,11,14,17/	! these and
	DATA Loc2   / 3, 6, 9,12,15,18/	! these
	DATA Loc3   /19,21,23,25,27,29/	! these
	DATA nDof/6/
!---------------------------
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