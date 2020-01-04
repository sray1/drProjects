	Subroutine FormIndexEL_2(Indx,nStifEL,iOut)
!
!	Coerced Isoparametric Quadrilateral_Cubic_Cubic Element
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
	Indx( 1) = 4
	Indx( 2) = 33
	Indx( 3) = 34
	Indx( 4) = 35
	Indx( 5) = 8
	Indx( 6) = 36
	Indx( 7) = 37
	Indx( 8) = 38
	Indx( 9) = 12
	Indx(10) = 39
	Indx(11) = 40
	Indx(12) = 41
	Indx(13) = 16
	Indx(14) = 42
	Indx(15) = 43
	Indx(16) = 44
	Indx(17) = 20
	Indx(18) = 45
	Indx(19) = 46
	Indx(20) = 47
	Indx(21) = 24
	Indx(22) = 48
	Indx(23) = 49
	Indx(24) = 50
	Indx(25) = 28
	Indx(26) = 51
	Indx(27) = 52
	Indx(28) = 53
	Indx(29) = 32
	Indx(30) = 54
	Indx(31) = 55
	Indx(32) = 56
!
	write(iOut,1000)
	write(iOut,1010) nStifEL,(Indx(i),i = 1,nStifEL)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_2"/)
 1010 Format(/2x,"Indices for Element#2 for Global Assembly: 1x"I3/
     &										7(8(2x,I7)/) )
	end   		