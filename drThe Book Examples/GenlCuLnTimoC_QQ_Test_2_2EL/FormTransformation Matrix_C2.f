	Subroutine FormTransformationMatrix_C2(Qc1,Qc2,nQc,T,
     &									nStifS,nStifC,iOut)
!
!	Coerced Isoparametric Circular Quartic Element
!------------------------------------------------------------
!	C2- Contraints:
!---------------------------------|-------------------------- A
!	 old Rows   new Cols     new Cols   new Cols
!		i 4 = (1/4){ i3  } + { i4  } - (1/4){ i13)
!		i 8 = (1/4){ i7  } + { i8  } - (1/4){ i16)
!		i14 = (1/4){ i11 } + { i12 } - (1/4){ i19)
!---------------------------------|-------------------------- B
!	 old Rows   new Cols     new Cols   new Cols
!		i16 =-(1/4){ i3  } + { i4  } + (1/4){ i13)
!		i20 =-(1/4){ i7  } + { i8  } + (1/4){ i16)
!		i24 =-(1/4){ i11 } + { i12 } + (1/4){ i19)
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
	Real(kind=8)	Qc1       ,Qc2   
	Dimension		Qc1(2,nQc),Qc2(2,nQc)
	Real(kind=8)	T				,Alfa   ,Beta   
	Dimension		T(nStifS,nStifC),Alfa(4),Beta(4)
	Real(kind=8)	unit,quap,quam
	
	Integer DofR1(3),DofR2(3),nDof
	Integer Loc1(3),Loc2(3),Loc3(3)
	DATA DofR1  / 4, 9,14/	!To be removed by A
	DATA Loc1   / 3, 7,11/	! these and
	DATA Loc2   / 4, 8,12/	! these and
	DATA Loc3   /13,16,19/	! these and
	DATA DofR2  /16,20,24/	!To be removed by B
	DATA nDof/3/
!	//////////////////////
!	Transformation Matrix 
!
	unit	= 1.0D0
	quap	= 0.25D0
	quam	= -0.25D0
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifS
		do 10 k = 1,nDof
			if(i == DofR1(k)) Then
				T(i,Loc1(k)) = quap
				T(i,Loc2(k)) = unit
				T(i,Loc3(k)) = quam
				iremoved = iremoved + 1
				go to 20
			else if(i == DofR2(k)) Then
				T(i,Loc1(k)) = quam
				T(i,Loc2(k)) = unit
				T(i,Loc3(k)) = quap
				iremoved = iremoved + 1
				go to 20
			end if
   10     continue
		T(i,i-iremoved) = 1.0D0 
   20		continue
   30 continue
   40 continue		 
!
!	do 110 i = 1,nStifS
!	write(16,1010) nStifS,nStifC,i,(T(i,j),j = 1,nStifC)
!  110	continue
  120 continue
!
!
 1010 format("C2 Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(4(10(f5.2,1X)/)))
!   		 
	return
	end   		