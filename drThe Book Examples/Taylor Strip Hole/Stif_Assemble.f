	Subroutine Stif_Assemble(Indx,StifEL,nStifEL,Stif,nStif,Nel,
     &							Iout,Trace)
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
		do i = 1,nStifEL
			do j = 1,nStifEL
   				Stif(i,j) = StifEL(i,j)
			end do !j
		end do !i	 
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
	iPrt = 1
	if(iPrt == 1) then
		write(iOut,1010) (j,Add(j),j = 1,nStif)
	endif
!
	return
!
 1010 format("Column Sums of Full Stiffness Matrix"/
     &         4(I5,2x,F15.5,5x) )
	return
	end   		