	Subroutine FormTransformationMatrix_C1(T,nStifS,nStifC)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C1- Contraints:
!	 old Row         new Cols	
!		i4  = (1/2){ i3  + i25)
!		i8  = (1/2){ i6  + i28)
!		i12 = (1/2){ i9  + i31)
!		i16 = (1/2){ i12 + i34)
!		i20 = (1/2){ i15 + i37)
!		i24 = (1/2){ i18 + i40)
!		i28 = (1/2){ i21 + i43)
!		i32 = (1/2){ i24 + i46)
!-----------------------------------
!
!	Inputs
!		nStifS					= Row or Col size of SinStiffness matrix 
!		nStifC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		T(nStifS,nStifC)		= C0 Transformation Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	T				,half
	Dimension		T(nStifS,nStifC)
	
	Integer DofR(8),Loc1(8),Loc2(8), nDof
	DATA DofR  /4 ,8 ,12,16,20,24,28,32/	!To be removed by
	DATA Loc1  /3 ,6 , 9,12,15,18,21,24/	! these and
	DATA Loc2  /25,28,31,34,37,40,43,46/	! these
	DATA nDof/8/
!	//////////////////////
!	Transformation Matrix 
!
	half	= 0.5D0
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifS
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
!	OPEN (unit = 17, FILE = 'Tran_C1.prt', STATUS = 'NEW')
!	do 110 i = 1,nStifS
!	write(17,1010) nStifS,nStifC,i,(T(i,j),j = 1,nStifC)
!  110	continue
  120 continue
!
!
 1010 format("C1 Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(5(9(f5.2,1X)/)))
!   		 
!   		 
	return
	end   		