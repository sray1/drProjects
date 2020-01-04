	Subroutine FormTransformationMatrix_C1(Qc1,Qc2,nQc,T,
     &									nStifS,nStifC,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C1- Contraints:
!	 old Row         new Cols	
!		i4  = alpha1*i3  + beta1*i30
!		i8  = alpha1*i6  + beta1*i33
!		i12 = alpha1*i9  + beta1*i36
!		i16 = alpha1*i12 + beta1*i39
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
	Real(kind=8)	Qc1       ,Qc2   
	Dimension		Qc1(2,nQc),Qc2(2,nQc)
	Real(kind=8)	T				,Alfa   ,Beta   
	Dimension		T(nStifS,nStifC),Alfa(4),Beta(4)
	
	Integer DofR0X,Loc0X(3)		! r=0 end s= 1/2 mid pt. 0 cond.
	Integer DofR0Y,Loc0Y(3)		! r=0 end s= 1/2 mid pt. 0 cond.
	Integer DofRX(4),Loc1X(4),Loc2X(4), nDof
	Integer DofRY(4),Loc1Y(4),Loc2Y(4)
	DATA DofR0X / 9/			!To be removed by
	DATA Loc0X  / 1, 4, 9/		! these and
	DATA DofR0Y /25/			!To be removed by
	DATA Loc0Y  /12,15,20/		! these and
	DATA DofRX  /4 ,8 ,12,16/	!To be removed by
	DATA Loc1X  /3 ,6 , 8,11/	! these and
	DATA Loc2X  /23,26,29,32/	! these
	DATA DofRY  /20,24,28,32/	!To be removed by
	DATA Loc1Y  /14,17,19,22/	! these and
	DATA Loc2Y  /35,38,41,44/	! these
	DATA nDof  /4/
!-----------------------------------------! HARDCODED FOR 16x32 & 32x16 ELEMENTS 
!--------------------------------------- Tangent Vector Continuity(delU/delR & delV/delR)
!	DOES WORK
	Alfa(1) = 3.D0/9.D0
	Alfa(2) = 4.D0/9.D0
	Alfa(3) = 5.D0/9.D0
	Alfa(4) = 6.D0/9.D0
!
	Beta(1) = 6.D0/9.D0
	Beta(2) = 5.D0/9.D0
	Beta(3) = 4.D0/9.D0
	Beta(4) = 3.D0/9.D0
!
!--------------------------------------- Continuity(delU/delX & delV/delX)
!	DOES NOT WORK!
	delQ1_0 = Qc1(1, 4) - Qc1(1, 1)		! s = 0
	delQ2_0 = Qc2(1, 4) - Qc2(1, 1)
	delQ_0	= delQ1_0 + delQ2_0
	Alfa(1) = delQ2_0/delQ_0  
	Beta(1) = delQ1_0/delQ_0
!
	delQ1_0 = Qc1(1, 8) - Qc1(1, 5)		! s = 1/3
	delQ2_0 = Qc2(1, 8) - Qc2(1, 5)
	delQ_0	= delQ1_0 + delQ2_0
	Alfa(2) = delQ2_0/delQ_0  
	Beta(2) = delQ1_0/delQ_0
!
	delQ1_0 = Qc1(1,12) - Qc1(1,9)		! s = 2/3
	delQ2_0 = Qc2(1,12) - Qc2(1,9)
	delQ_0	= delQ1_0 + delQ2_0
	Alfa(3) = delQ2_0/delQ_0  
	Beta(3) = delQ1_0/delQ_0
!
	delQ1_0 = Qc1(1,16) - Qc1(1,13)		! s = 3/3
	delQ2_0 = Qc2(1,16) - Qc2(1,13)
	delQ_0	= delQ1_0 + delQ2_0
	Alfa(4) = delQ2_0/delQ_0  
	Beta(4) = delQ1_0/delQ_0
!------------------------------------------
	write(iOut,1020) (Alfa(j),j = 1,4)
	write(iOut,1030) (Beta(j),j = 1,4)
			
!	//////////////////////
!	Transformation Matrix 
!
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifS
		do 10 k = 1,nDof
			if(i == DofRX(k)) Then
				T(i,Loc1X(k)) = Alfa(k)
				T(i,Loc2X(k)) = Beta(k)
				iremoved = iremoved + 1
				go to 20
			else if(i == DofRY(k)) Then
				T(i,Loc1Y(k)) = Alfa(k)
				T(i,Loc2Y(k)) = Beta(k)
				iremoved = iremoved + 1
				go to 20
			end if
   10     continue
	if(i == DofR0X) Then
		T(i,Loc0X(1)) = -1.0D0/3.0D0
		T(i,Loc0X(2)) = -1.0D0
		T(i,Loc0X(3)) = -1.0D0/3.0D0
		iremoved = iremoved + 1
		go to 20
	else if(i == DofR0Y) Then
		T(i,Loc0Y(1)) = -1.0D0/3.0D0
		T(i,Loc0Y(2)) = -1.0D0
		T(i,Loc0Y(3)) = -1.0D0/3.0D0
		iremoved = iremoved + 1
		go to 20
	end if
	T(i,i-iremoved) = 1.0D0 
   20	continue
   30 continue
   40 continue		 
!
	do 110 i = 1,nStifS
!		write(iOut,1010) nStifS,nStifC,i,(T(i,j),j = 1,nStifC)
  110	continue
  120 continue
!
!
 1010 format("C1 Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(5(9(f5.2,1X)/)))
 1020 format("Alfa(4)"/4(f10.7,1X)/)
 1030 format("Beta(4)"/4(f10.7,1X)/)
!   		 
!   		 
	return
	end   		