	Subroutine FormIndexEL_2(Indx,nStifEL)
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
	Indx( 5) = 36
	Indx( 6) = 37
	Indx( 7) = 38
	Indx( 8) = 39
	Indx( 9) = 40
	Indx(10) = 41
	Indx(11) = 42
	Indx(12) = 43
	Indx(13) = 16
	Indx(14) = 44
	Indx(15) = 45
	Indx(16) = 46
	Indx(17) = 20
	Indx(18) = 47
	Indx(19) = 48
	Indx(20) = 49
	Indx(21) = 50
	Indx(22) = 51
	Indx(23) = 52
	Indx(24) = 53
	Indx(25) = 54
	Indx(26) = 55
	Indx(27) = 56
	Indx(28) = 57
	Indx(29) = 32
	Indx(30) = 58
	Indx(31) = 59
	Indx(32) = 60
!
	return
	end   		