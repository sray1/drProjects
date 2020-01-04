	Subroutine Stif_Assemble(Indx,StifEL,nStifEL,Stif,nStif,Nel,Iout,
     &														Trace)
!
!	!
!	Inputs
!		Indx(nStifEL)			= Index of location for Element 2
!		Nel						= Element Number
!		StifEL(nStifEL,nStifEL)	= Element Stiffness Matrix
!		nStifEL					= Row or Col size of Stiffness matrix ( MUST BE 32)
!		nStif					= Row or Col size of Stiffness matrix ( MUST BE 64)
!		Iout					= Error Output file#
!		 	
!	Outputs 
!		Stif(nStif,nStif)		= Desired Stiffness Matrix
!		Trace					= trace of the matrix
!
	Implicit Real(kind=8) (a-h,o-z)
!
!	Input Variables & Arrays
!
	Real(kind=8)	StifEL			 ,Trace
	Dimension		StifEL(nStifEL,nStifEL)
	integer			Indx(nStifEL),nStifEL,nStif,Nel,Iout
!	
!	Output Variables & Arrays	
!
	Real(kind=8)	Stif			 ,Add
	Dimension		Stif(nStif,nStif),Add(nStif)
!	//////////////////////////////////////////////////////// Stiffness Matrix Assembly
	if (Nel.EQ.1) then
  		Stif = StifEL 
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
 1010 format("Full Stiffness Matrix:Stif(56,56)"/
     &        I5/(7(8(f10.6,1X)/)/))
	return
	end   		