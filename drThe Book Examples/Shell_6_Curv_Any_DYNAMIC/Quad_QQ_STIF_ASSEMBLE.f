	Subroutine Assemble_Stif(Indx,StifEL,nStifEL,
     &                        	Stif,nStif,Nel,Iout,Trace)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		Indx(nStifEL)	= Index of location for Element 2
!		Nel				= Element Number
!		StifEL(32,32)	= Element Stiffness Matrix
!		nStifEL			= Row or Col size of Stiffness matrix ( MUST BE 32)
!		nStif			= Row or Col size of Stiffness matrix ( MUST BE 64)
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		Stif(64,64)		= Desired Stiffness Matrix
!		Trace			= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	StifEL			       ,Trace
	Dimension		StifEL(nStifEL,nStifEL)
	integer			Indx(nStifEL),Nel,Iout,nStifEL,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Stif			 ,Add
	Dimension		Stif(nStif,nStif),Add(nStif)
!
!	Stiffness Matrix Assembly
!
	if (Nel.EQ.1) Then
		do 5 i = 1,nStif
		do 5 j = 1,nStif
    5		Stif(i,j) = 0.D0	! all elements = 0.
!
		do 10 i = 1,nStifEL
!		------------------------
		do 10 j = 1,nStifEL
   10		Stif(i,j) = StifEL(i,j) 
	else 
		do 60 i = 1,nStifEL
		ii = Indx(i) 
!		------------------------
		do 60 j = 1,nStifEL
		jj = Indx(j) 
   60		Stif(ii,jj) = Stif(ii,jj)+ StifEL(i,j)
	end if
!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,nStif
	Trace = Trace + Stif(i,i)
   80 continue			
!
!	Check each col. vector for Null
!
	Add = 0.D0
	do 100 j = 1,nStif
	sum = 0.0 
	do  90 i = 1,nStif	
	sum = sum + Stif(i,j)
   90 continue
	Add(j) = sum
  100 continue			
!
!	done
!
	iPrt = 0
	if(iPrt == 1) Then
		write(Iout,1010) nStif,nStif
		do 110 i = 1,nStif
		write(Iout,1020) i,(Stif(i,j),j = 1,nStif)
  110	continue
	endif 
!	/////////
	return
!
 1010 format("Assembled Stiffness Matrix:Stif(",I5,",",I5,")"/)
 1020 format(I5/(6(8(f12.1,1X)/)/))
	end   	
