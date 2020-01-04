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
	Indx( 1) = 5
	Indx( 2) = 51
	Indx( 3) = 52
	Indx( 4) = 53
	Indx( 5) = 54
	Indx( 6) = 10
	Indx( 7) = 55
	Indx( 8) = 56
	Indx( 9) = 57
	Indx(10) = 58
	Indx(11) = 15
	Indx(12) = 59
	Indx(13) = 60
	Indx(14) = 61
	Indx(15) = 62
	Indx(16) = 20
	Indx(17) = 63
	Indx(18) = 64
	Indx(19) = 65
	Indx(20) = 66
	Indx(21) = 25
	Indx(22) = 67
	Indx(23) = 68
	Indx(24) = 69
	Indx(25) = 70
	Indx(26) = 30
	Indx(27) = 71
	Indx(28) = 72
	Indx(29) = 73
	Indx(30) = 74
	Indx(31) = 35
	Indx(32) = 75
	Indx(33) = 76
	Indx(34) = 77
	Indx(35) = 78
	Indx(36) = 40
	Indx(37) = 79
	Indx(38) = 80
	Indx(39) = 81
	Indx(40) = 82
	Indx(41) = 45
	Indx(42) = 83
	Indx(43) = 84
	Indx(44) = 85
	Indx(45) = 86
	Indx(46) = 50
	Indx(47) = 87
	Indx(48) = 88
	Indx(49) = 89
	Indx(50) = 90
!
	write(iOut,1000)
	write(iOut,1010) nStifEL,(Indx(i),i = 1,nStifEL)
!   		 
	return
 1000 Format(/2x,"Just before Leaving: FormIndexEL_2"/)
 1010 Format(/2x,"Indices for Element#2 for Global Assembly: 1x"I3/
     &										7(8(2x,I7)/) )
	end   		