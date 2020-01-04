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
	if (nStifEL == 30) Then
		Indx( 1) =  5 
		Indx( 2) = 31
		Indx( 3) = 32
		Indx( 4) = 33
		Indx( 5) = 34
		Indx( 6) = 10	!
		Indx( 7) = 35
		Indx( 8) = 36
		Indx( 9) = 37
		Indx(10) = 38
		Indx(11) = 15	!
		Indx(12) = 39
		Indx(13) = 40
		Indx(14) = 41
		Indx(15) = 42
		Indx(16) = 20
		Indx(17) = 43	!
		Indx(18) = 44
		Indx(19) = 45
		Indx(20) = 46
		Indx(21) = 25
		Indx(22) = 47
		Indx(23) = 48	!
		Indx(24) = 49
		Indx(25) = 50
		Indx(26) = 30
		Indx(27) = 51
		Indx(28) = 52
		Indx(29) = 53
		Indx(30) = 54
	elseif (nStifEL == 36) Then
		Indx( 1) = 6	!
		Indx( 2) = 37
		Indx( 3) = 38
		Indx( 4) = 39
		Indx( 5) = 40
		Indx( 6) = 41	
		Indx( 7) = 12	!
		Indx( 8) = 42
		Indx( 9) = 43
		Indx(10) = 44
		Indx(11) = 45	
		Indx(12) = 46
		Indx(13) = 18	!
		Indx(14) = 47
		Indx(15) = 48
		Indx(16) = 49
		Indx(17) = 50
		Indx(18) = 51
		Indx(19) = 24	!
		Indx(20) = 52
		Indx(21) = 53
		Indx(22) = 54
		Indx(23) = 55
		Indx(24) = 56
		Indx(25) = 30	!
		Indx(26) = 57
		Indx(27) = 58
		Indx(28) = 59
		Indx(29) = 60
		Indx(30) = 61
		Indx(31) = 36	!
		Indx(32) = 62
		Indx(33) = 63
		Indx(34) = 64
		Indx(35) = 65
		Indx(36) = 66
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