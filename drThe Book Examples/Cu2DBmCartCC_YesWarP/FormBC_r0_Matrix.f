	Subroutine FormBC_r0_ConMatrix(T,nStifS,nStifC)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!------------------------------------------------------------
!	C1- Contraints:
!	 old Row         new Cols	
!		i9   =         -(1/3)i1  -i5  +(1/3)i12
!		i25  =         -(1/3)i16 -i20 +(1/3)i27
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
	
	Integer DofR1,DofR2,Loc1(3),Loc2(3), nDof
	DATA DofR1  /9/	!To be removed by
	DATA Loc1  /1, 5 ,12/	! these 
	DATA DofR2  /25/	!To be removed by
	DATA Loc2  /16,20,27/	! these 
!	DATA nDof/2/
!	//////////////////////
!	Transformation Matrix 
!
	T		= 0.0D0	! everything zeroed
!
	iremoved = 0
	do 30 i = 1,nStifS
		if(i == DofR1) Then
			T(i,Loc1(1)) = -1.0D0/3.0D0
			T(i,Loc1(2)) = -1.0D0
			T(i,Loc1(3)) = -1.0D0/3.0D0
			iremoved = iremoved + 1
			go to 20
		else if(i == DofR2) Then
			T(i,Loc2(1)) = -1.0D0/3.0D0
			T(i,Loc2(2)) = -1.0D0
			T(i,Loc2(3)) = -1.0D0/3.0D0
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