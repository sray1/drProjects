	Subroutine FormTransformationMatrix_C2(T,nStifN,nStifNC,iOut)
!
!	Cubic Element
!------------------------------------------------------------
!	C2- Contraints:
!	 old Rows        new Cols	  old Rows       new Cols
!		i5  = (1/2){ i1  + i5 ) |	i28 = (1/2){ i5  + i20)
!		i6  = (1/2){ i2  + i6 ) |	i29 = (1/2){ i6  + i21)
!		i7  = (1/2){ i3  + i7 ) |	i30 = (1/2){ i7  + i22)
!		i8  = (1/2){ i4  + i8 ) |	i31 = (1/2){ i8  + i23)
!		i20 = (1/2){ i12 + i16) |	i40 = (1/2){ i16 + i28)
!		i21 = (1/2){ i13 + i17) |	i41 = (1/2){ i17 + i29)
!		i22 = (1/2){ i14 + i18) |	i42 = (1/2){ i18 + i30)
!		i23 = (1/2){ i15 + i19) |	i43 = (1/2){ i19 + i31)
!---------------------------------|--------------------------
!	 old Rows        new Cols	  New Cols       new Cols
!		i9  = (1/4){ i1  } + (1/2){ i5  } + (1/4){ i20)
!		i10 = (1/4){ i2  } + (1/2){ i6  } + (1/4){ i21)
!		i11 = (1/4){ i3	 } + (1/2){ i7  } + (1/4){ i22)
!		i12 = (1/4){ i4  } + (1/2){ i8  } + (1/4){ i23)
!		i24 = (1/4){ i12 } + (1/2){ i16 } + (1/4){ i28)
!		i25 = (1/4){ i13 } + (1/2){ i17 } + (1/4){ i29)
!		i26 = (1/4){ i14 } + (1/2){ i18 } + (1/4){ i30)
!		i27 = (1/4){ i15 } + (1/2){ i19 } + (1/4){ i31)
!---------------------------------|--------------------------
!
!	Inputs
!		nStifN					= Row or Col size of NonStiffness matrix 
!		nStifNC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		T(nStifN,nStifNC)		= C2 Transformation Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	T				 ,half,quar
	Dimension		T(nStifN,nStifNC)
	
	Integer DofR1(8),DofR2(8),DofR3(8),nDof
	Integer Loc1(8),Loc2(8),Loc3(8)
	DATA DofR1  / 5, 6, 7, 8,20,21,22,23/	!To be removed by (1/2){Loc1+Loc2}
	DATA DofR2  /28,29,30,31,40,41,42,43/	!To be removed by (1/2){Loc2+Loc3}
	DATA DofR3  / 9,10,11,12,24,25,26,27/	!To be replaced with:
											!  (1/4)Loc1+(1/2)Loc2+(1/4)Loc3
	DATA Loc1   / 1, 2, 3, 4,12,13,14,15/	! these and
	DATA Loc2   / 5, 6, 7, 8,16,17,18,19/	! these
	DATA Loc3   /20,21,22,23,28,29,30,31/	! these
	DATA nDof/8/
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
		jNew		= i-iremoved
		T(i,jNew)	= 1.0D0 
   20		continue
   30 continue
	if(jNew.NE.nStifNC) Stop 'jNew.NE.nStifNC'
!
!
	iPrt = 0
	if(iPrt == 1) then
		write(iOut,1000) nStifN,nStifNC
		do i = 1,nStifN
			write(iOut,1010) i,(T(i,j),j = 1,nStifNC)
		end do !i
	endif
!
	return
!
 1000 format("C2 Transformation Matrix:T(",I3,",",I3,")"/)
 1010 format(i3/16(2x,f5.2))
!   		 
	end   		