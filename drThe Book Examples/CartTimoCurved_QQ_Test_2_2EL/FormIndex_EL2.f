	Subroutine FormIndexEL_2(Indx,nStifEL,iOut)
!
!	Coerced Isoparametric Quartic Element
!
!
!	Outputs 
!		Indx(nStifEl)	= Indx of assembly for Element 2
!
	Implicit Real(kind=8) (a-h,o-z)
	integer Indx(nStifEL)
!
!	Indices of location in global stiffness
!
	if (nStifEL == 15) Then
		Indx( 1) = 5	!
		Indx( 2) = 16
		Indx( 3) = 17
		Indx( 4) = 18
		Indx( 5) = 19
		Indx( 6) = 10	!
		Indx( 7) = 20
		Indx( 8) = 21
		Indx( 9) = 22
		Indx(10) = 23
		Indx(11) = 15	!
		Indx(12) = 24
		Indx(13) = 25
		Indx(14) = 26
		Indx(15) = 27
	elseif (nStifEL == 18) Then
		Indx( 1) = 6	!
		Indx( 2) = 19
		Indx( 3) = 20
		Indx( 4) = 21
		Indx( 5) = 22
		Indx( 6) = 23	
		Indx( 7) = 12	!
		Indx( 8) = 24
		Indx( 9) = 25
		Indx(10) = 26
		Indx(11) = 27	
		Indx(12) = 28
		Indx(13) = 18	!
		Indx(14) = 29
		Indx(15) = 30
		Indx(16) = 31
		Indx(17) = 32
		Indx(18) = 33
	endif
!
	write(iOut,1000)
	write(iOut,1010) nStifEL,(Indx(i),i = 1,nStifEL)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_2"/)
 1010 Format(/2x,"Indices for Element#2 for Global Assembly: 1x"I3/
     &										3(5(2x,I7)/) )
	end   		