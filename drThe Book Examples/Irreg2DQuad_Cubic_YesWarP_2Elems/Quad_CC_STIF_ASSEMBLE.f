	Subroutine Assemble_Stif(Indx,StifEL,nStifEL,Stif,nStif,Nel,Iout,
     &														Trace)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
!
!
!	Inputs
!		Indx(nStifEL)	= Index of location for Element 2
!		Nel				= Element Number
!		StifEL(24,24)	= Element Stiffness Matrix
!		nStifEL			= Row or Col size of Stiffness matrix ( MUST BE 32)
!		nStif			= Row or Col size of Stiffness matrix ( MUST BE 64)
!		Iout			= Error Output file#
!		 	
!	Outputs 
!		Stif(48,48)		= Desired Stiffness Matrix
!		Trace			= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	StifEL			 ,Trace
	Dimension		StifEL(nStifEL,nStifEL)
	integer			Indx(nStifEL),Nel,Iout,nStifEL,nStif
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Stif			 ,Add
	Dimension		Stif(nStif,nStif),Add(nStif)
!	//////////////////////
	if(nStif.NE.42) Then
		stop 'nStif !=42'
	end if
	if(nStifEL.NE.24) Then
		stop 'nStif !=24'
	end if
!	//////////////////////
!
!	Stiffness Matrix Assembly
!
	if (Nel.EQ.1) Then
		do 5 i = 1,nStif
		do 5 j = 1,nStif
    5		Stif(i,j) = 0.D0	! all elements = 0.
!
		do 10 i = 1,nStifEL
		do 10 j = 1,nStifEL
   10		Stif(i,j) = StifEL(i,j) 
	else if (Nel.EQ.2) Then
		do 60 i = 1,nStifEL
		do 60 j = 1,nStifEL
		ii = Indx(i) 
		jj = Indx(j) 
!	
   60		Stif(ii,jj) = Stif(ii,jj)+ StifEL(i,j)
	end if

!
!	Get Trace
!
	Trace = 0.D0
	do 80 i = 1,32
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
 1000 continue 			
!
!	done
!
!	if (NEL == 2) then
!		OPEN (unit = 15, FILE = 'Stiffness.prt', STATUS = 'NEW')
!		do 110 i = 1,56
!		write(15,1010) i,(Stif(i,j),j = 1,56)
!  110		continue
!	end if
!
	return
!
 1010 format("Full Stiffness Matrix:Stif(nStif,nStif)"/
     &        I5/(7(8(f10.6,1X)/)/))
	return
	end   		