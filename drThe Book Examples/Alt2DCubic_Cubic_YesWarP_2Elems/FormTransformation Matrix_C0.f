	Subroutine FormTransformationMatrix_C0(T,nStifN,nStifC)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C0- Contraints:
!	 old Row         new Cols	
!		i36 = i8)
!		i40 = i12)
!		i50 = i24)
!		i54 = i28)
!-----------------------------------
!
!	Inputs
!		nStifN					= Row or Col size of AssStiffness matrix 
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
	
	Integer DofR(8),Loc1(8), nDof
	DATA DofR  /33,37,41,45,49,53,57,61/	!To be removed by
	DATA Loc1  /4 ,8 ,12,16,20,24,28,32/	! these
	DATA nDof/8/
!	//////////////////////
!	Transformation Matrix 
!
	same	= 1.0D0
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifN
		do 10 k = 1,nDof
			if(i == DofR(k)) Then
				T(i,Loc1(k)) = same
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
	OPEN (unit = 18, FILE = 'Tran_C0.prt', STATUS = 'NEW')
	do 110 i = 1,nStifN
	write(18,1010) nStifN,nStifC,i,(T(i,j),j = 1,nStifC)
  110	continue
  120 continue
!
!
 1010 format("C0 Transformation Matrix:T(",I3,",",I3,")"/
     &        I5/(5(9(f5.2,1X)/)))
!   		 
!   		 
	return
	end   		