	Subroutine FormTransformationMatrix_C1(T,nStifN,nStifNC,iOut)
!
!	Cubic_Cubic Element
!------------------------------------------------------------
!	C1- Contraints:
!	 old Row         new Cols	
!		i9  = (1/2){ i5  + i20)
!		i10 = (1/2){ i6  + i21)
!		i11 = (1/2){ i7  + i22)
!		i12 = (1/2){ i8  + i23)
!		i24 = (1/2){ i16 + i32)
!		i25 = (1/2){ i17 + i33)
!		i26 = (1/2){ i18 + i34)
!		i27 = (1/2){ i19 + i35)
!-----------------------------------
!
!	Inputs
!		nStifN					= Row or Col size of NonStiffness matrix 
!		nStifC					= Row or Col size of ConStiffness matrix
!		 	
!	Outputs 
!		T(nStifS,nStifNC)		= C1 Transformation Matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	T				 ,fMul1   ,fMul2   ,half
	Dimension		T(nStifN,nStifNC),fMul1(8),fMul2(8)
	
	Integer DofR(8),Loc1(8),Loc2(8), nDof
	DATA DofR  /9 ,10,11,12,24,25,26,27/	!To be removed by
	DATA Loc1  /5 ,6 , 7, 8,16,17,18,19/	! these dofs (new location and
!	DATA fMul1 /.3,.5,.5,.7,.3,.5,.5,.7/
	DATA Loc2  /20,21,22,23,32,33,34,35/	! these new
!	DATA fMul2 /.7,.5,.5,.3,.7,.5,.5,.3/
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
 1000 format("C1 Transformation Matrix:T(",I3,",",I3,")"/)
 1010 format(i3/16(2x,f5.2))
!   		 
	end   		